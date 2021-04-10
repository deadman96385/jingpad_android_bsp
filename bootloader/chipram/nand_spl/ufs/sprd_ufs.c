#include <asm/types.h>
#include <common.h>
#include <linux/types.h>
#include <part.h>
#include <sci_types.h>
#include <asm/arch/sprd_reg.h>
#include <asm/io.h>
#include "sprd_ufs.h"
#include "protocol_util.h"

struct   ufs_driver_info ufs_info;

uint32_t fatal_err = 0;

static struct dwc_ufs_utrd utrd __attribute__((aligned(1024)));
static struct dwc_ufs_utmrd utmd __attribute__((aligned(1024)));
static struct dwc_ufs_tcd ucd __attribute__((aligned(128)));
block_dev_desc_t sprd_ufs_dev;

static inline uint32_t ufs_readl(int reg)
{
	return readl((void *)REG_BASE_ADDRESS + reg);
}

static inline void ufs_writel(int reg, uint32_t val)
{
	writel(val, (void *)REG_BASE_ADDRESS + reg);
}


/***************************************************************
 *
 * dwc_reset_hc
 * Description: resets the Host Controller. Enable's sending of
 *              DME_RESET and DME_ENABLE commands. Also polls for
 *              the completion of the initialization sequence
 *
 ***************************************************************/
int dwc_reset_hc()
{
	int retry = RETRY_CNT;

	/*
	 * Enable the Host Controller.
	 * DME_RESET and DME_ENABLE commands are sent automatically on DW_UFS_HCE write
	 */
	ufs_writel(DW_UFS_HCE, 0);
	udelay(1000); /* Platform Specific Implementation */
	ufs_writel(DW_UFS_HCE, HCE_RESET);

	/*poll untill (DW_UFS_HCE == 1) i'e initialization sequence has completed*/
	while (retry != 0) {
		if(1 == ufs_readl(DW_UFS_HCE)) {
			return UFS_SUCCESS;
		}

		retry--;
		udelay(1); /* Platform Specific Implementation */
	}

	return UFS_TIMEOUT;
}

/***************************************************************
 *
 * send_uic_command
 * Description: Programs the Command Argument and the Command
 *     Register to send the DME_LINK_STARTUP command
 *     to the device
 *
 ***************************************************************/
void send_uic_command(uint32_t command, uint32_t arg1, uint32_t arg2, uint32_t arg3)
{

	ufs_writel(DW_UFS_UICCMDARG1,arg1);
	ufs_writel(DW_UFS_UICCMDARG2,arg2);
	ufs_writel(DW_UFS_UICCMDARG3,arg3);

	ufs_writel(DW_UFS_UICCMD,(command & 0xFF));
}

int wait_uic_complete()
{
	int retry = 100;
	uint32_t uccs_intr_res = 0;

	/*wait for the UIC Command to complete by checking UCCS field*/
	while(retry > 0) {
		udelay(1000);
		uccs_intr_res = ufs_readl(DW_UFS_IS) & DW_UFS_IS_UCCS;
		if (uccs_intr_res) {
			ufs_writel(DW_UFS_IS, uccs_intr_res);
			break;
		}
		retry--;
	}

	if (0 == retry)
		return UFS_TIMEOUT;
	else
		return UFS_SUCCESS;

}

void send_dme_link_startup(void)
{

	ufs_writel(DW_UFS_UICCMDARG1,0);
	ufs_writel(DW_UFS_UICCMDARG2,0);
	ufs_writel(DW_UFS_UICCMDARG3,0);

	ufs_writel(DW_UFS_UICCMD,(UIC_LINK_STARTUP_CMD & 0xFF));
}

uint32_t dme_get(uint32_t mib)
{
	mib = (mib << 16) | ((mib >> 16) & 0x0000FFFF);
	send_uic_command(UIC_GET_CMD, mib, 0, 0);
	wait_uic_complete();

	return ufs_readl(DW_UFS_UICCMDARG3);
}

uint32_t dme_peer_get(uint32_t mib)
{
	mib = (mib << 16) | ((mib >> 16) & 0x0000FFFF);
	send_uic_command(UIC_PEER_GET_CMD, mib, 0, 0);
	wait_uic_complete();

	return ufs_readl(DW_UFS_UICCMDARG3);
}

void dme_set(uint32_t mib, uint32_t value)
{
	mib = (mib << 16) | ((mib >> 16) & 0x0000FFFF);
	send_uic_command(UIC_SET_CMD, mib, 0, value);

	wait_uic_complete();

	/*return with no error*/
	return;
}

/****************************************************************
 *
 * check_uic_link_startup_result
 * Description: The function returns the result of the sent
 * UIC Command, Returns 0 on success , non zero number on failure
 *
 ***************************************************************/
static int check_uic_link_startup_result()
{
	return ((0xFF & ufs_readl(DW_UFS_UICCMDARG2)));
}

void clear_cmd_desc(struct dwc_ufs_tcd * cmd_upiu_ptr)
{
	memset(cmd_upiu_ptr, 0, sizeof(struct dwc_ufs_tcd));
	return;
}


/***************************************************************
 * create_nop_out_upiu
 * Description: Fills the UPIU memory for NOP OUT command
 *
 ***************************************************************/
static void create_nop_out_upiu()
{
	struct dwc_ufs_nop_req_upiu *cmd_upiu_ptr;
	int i;
	void *tmp_ptr;

	tmp_ptr = ufs_info.cmd_desc->command_upiu;
	cmd_upiu_ptr = (struct dwc_ufs_nop_req_upiu*)tmp_ptr;

	if ((ufs_info.dwc_ufs_version == DWC_UFS_HC_VERSION_2_0) || (ufs_info.dwc_ufs_version == DWC_UFS_HC_VERSION_2_1))
		ufs_info.utrd_desc->ct_and_flags = (uint8_t)(UTP_NO_DATA_TRANSFER | UTP_UFS_STORAGE_COMMAND);
	else
		ufs_info.utrd_desc->ct_and_flags = (UTP_NO_DATA_TRANSFER | UTP_DEVICE_MANAGEMENT_FUNCTION);
	ufs_info.utrd_desc->resp_upiu_length = cpu_to_le16(sizeof(struct dwc_ufs_nop_resp_upiu) >> 2);
	ufs_info.utrd_desc->prdt_length = 0;

	cmd_upiu_ptr->trans_type        = 0x00;
	cmd_upiu_ptr->flags             = 0x00;
	cmd_upiu_ptr->reserved_1	= 0x00;
	cmd_upiu_ptr->task_tag          = 0x01;
	for(i = 0;i < 4; i++) {
		cmd_upiu_ptr->reserved_2[i]	= 0x00;
	}
	cmd_upiu_ptr->tot_ehs_len       = 0x00;
	cmd_upiu_ptr->reserved_3	= 0x00;
	cmd_upiu_ptr->data_seg_len      = 0x00;
	for(i = 0;i < 20; i++) {
		cmd_upiu_ptr->reserved_4[i] = 0x00;
	}

	return;
}

/***************************************************************
 *
 * handle_query_response
 * Description: The functon does the following 
 *              1. validates the query command's response received
 *              2.updates the ret argument with query data
 *              3. returns the status
 ***************************************************************/
static int handle_query_response(uint8_t *ret)
{
	struct dwc_ufs_query_upiu *resp_upiu;
	void *tmp_ptr;

	tmp_ptr = ufs_info.cmd_desc->response_upiu;
	resp_upiu = (struct dwc_ufs_query_upiu *)tmp_ptr;


	/* Update the return value */
	if(ret) {
		ret[0] = resp_upiu->tsf[8];
		ret[1] = resp_upiu->tsf[9];
		ret[2] = resp_upiu->tsf[10];
		ret[3] = resp_upiu->tsf[11];
	}

	if(resp_upiu->query_resp == UFS_SUCCESS)
		return UFS_SUCCESS;

	return -(resp_upiu->query_resp);
}

/***************************************************************
 *
 * create_query_upiu
 * Description: Populates the UPIU memory for all query Operations
 *
 ***************************************************************/
static void create_query_upiu(uint8_t opcode, uint8_t query_func, uint8_t selector, uint8_t idn, uint8_t *val)
{
	struct dwc_ufs_query_upiu *cmd_upiu_ptr;
	void *tmp_ptr;
	int i;

	tmp_ptr = ufs_info.cmd_desc->command_upiu;
	cmd_upiu_ptr = (struct dwc_ufs_query_upiu *)tmp_ptr;

	/* UTRD Descriptor Programming for processing command */
	if ((ufs_info.dwc_ufs_version == DWC_UFS_HC_VERSION_2_0) || (ufs_info.dwc_ufs_version == DWC_UFS_HC_VERSION_2_1))
		ufs_info.utrd_desc->ct_and_flags = (uint8_t)(UTP_NO_DATA_TRANSFER | UTP_UFS_STORAGE_COMMAND);
	else
		ufs_info.utrd_desc->ct_and_flags = (UTP_NO_DATA_TRANSFER | UTP_DEVICE_MANAGEMENT_FUNCTION);
	ufs_info.utrd_desc->resp_upiu_length = cpu_to_le16(sizeof(struct dwc_ufs_query_upiu) >> 2);
	ufs_info.utrd_desc->prdt_length = 0;


	/* Command Descriptor Programming */
	cmd_upiu_ptr->trans_type        = 0x16;
	cmd_upiu_ptr->flags             = UPIU_CMD_FLAGS_NONE;
	cmd_upiu_ptr->reserved_1	= 0x00;
	cmd_upiu_ptr->task_tag          = 0x01;
	cmd_upiu_ptr->reserved_2	= 0x00;
	cmd_upiu_ptr->query_func        = query_func;
	cmd_upiu_ptr->query_resp        = 0x00;
	cmd_upiu_ptr->reserved_3        = 0x00;
	cmd_upiu_ptr->tot_ehs_len       = 0x00;
	cmd_upiu_ptr->data_seg_len      = 0x00;
	cmd_upiu_ptr->tsf[0]            = opcode;
	cmd_upiu_ptr->tsf[1]            = idn;
	cmd_upiu_ptr->tsf[2]            = 0x00;      /* index */
	cmd_upiu_ptr->tsf[3]            = selector; /* selector */
	cmd_upiu_ptr->tsf[4]            = 0x00;
	cmd_upiu_ptr->tsf[5]            = 0x00;
	cmd_upiu_ptr->tsf[6]            = 0x00;
	cmd_upiu_ptr->tsf[7]            = 0x00;

	/* Value/Flag Updation */
	cmd_upiu_ptr->tsf[8]            = val[0];
	cmd_upiu_ptr->tsf[9]            = val[1];
	cmd_upiu_ptr->tsf[10]           = val[2];
	cmd_upiu_ptr->tsf[11]           = val[3];

	for(i=12; i < 15 ;i++) {
		cmd_upiu_ptr->tsf[i]    = 0x00;
	}
	for(i=0; i < 3 ;i++)
		cmd_upiu_ptr->reserved_5[i] = 0x00;

}

/***************************************************************
 *
 * wait_for_cmd_completion
 * Description: Sets the DoorBell Register and waits for the 
 *              Doorbell to Clear. Returns Zero on Success or
 *		error number on Failure
 *
 ***************************************************************/
static int wait_for_cmd_completion()
{
	int retry = RW_RETRY_CNT;
	uint32_t is_status = 0;

	/* Set the doorbell for processing the request */
	ufs_writel(DW_UFS_UTRLDBR, BIT(0));

	/* Wait for the DoorBell to clear */
	while(1) {
		udelay(50);
		is_status = ufs_readl(DW_UFS_IS);
		if (0 != is_status)
			ufs_writel(DW_UFS_IS, is_status);
		if (0 != (is_status & IS_FATAL_ERROR)) {
			ufs_writel(DW_UFS_UTRLCLR, 0xfffffffe);
			/*for stress test*/
			fatal_err++;
			return UFS_FATAL_ERROR;
		}
		if((ufs_readl(DW_UFS_UTRLDBR) & BIT(0)) == 0)
			break;
		retry--;
		if(retry == 0) {
			return UFS_TIMEOUT;
		}
	}

	return UFS_SUCCESS;
}

static int wait_for_previous_scsi_completion()
{
	int retry = RW_RETRY_CNT;
	uint32_t is_status = 0;

	/* Wait for the DoorBell to clear */
	while(1) {
		is_status = ufs_readl(DW_UFS_IS);
		if (0 != is_status)
			ufs_writel(DW_UFS_IS, is_status);
		if (0 != (is_status & IS_FATAL_ERROR)) {
			ufs_writel(DW_UFS_UTRLCLR, 0xfffffffe);
			/*for stress test*/
			fatal_err++;
			return UFS_FATAL_ERROR;
		}
		if((ufs_readl(DW_UFS_UTRLDBR) & BIT(0)) == 0)
			break;
		retry--;
		if(retry == 0) {
			return UFS_TIMEOUT;
		}
		udelay(5); /* Platform Specific Implementation */
	}

	return UFS_SUCCESS;
}


/***************************************************************
 *
 * handle_scsi_completion
 * Description: The functon validates the SCSI command's 
 *              response received
 *
 ***************************************************************/
static int handle_scsi_completion()
{
	struct dwc_ufs_xfer_resp_upiu *resp_upiu;
	uint8_t status;
	void *tmp_ptr;

	tmp_ptr = ufs_info.cmd_desc->response_upiu;
	resp_upiu = (struct dwc_ufs_xfer_resp_upiu *)tmp_ptr;

	/* read the OCS value */
	if(ufs_info.utrd_desc->ocs == UFS_SUCCESS) {
		return UFS_SUCCESS;
	} else {
		return -(ufs_info.utrd_desc->ocs);
	}

	return UFS_SUCCESS;
}

/***************************************************************
 * do_flag_operation
 * Description: The function can be used for any operation on flags
                1. fills the query upiu memory content
		2. Handles the response of query command sent
		3. updates the flag return value
 ***************************************************************/
static int do_flag_operation(int opcode, int query_func, enum flags_id idn, uint8_t *flags_ret)
{
	int ret = 0;
	int retry = 4;
	int i = 0;
	uint8_t val[4];

	for (i = 0; i < 4; i++)
		val[i] = 0x00;

	do {
		create_query_upiu((uint8_t)opcode, (uint8_t)query_func, (uint8_t)0, (uint8_t)idn, val);
		ret = wait_for_cmd_completion();
		if (UFS_SUCCESS != ret)
			reset_and_restore_hc();
		else
			ret = handle_query_response(val);
		retry--;
	} while (UFS_SUCCESS != ret && retry > 0);

	*flags_ret = val[3];

	return ret;
}

/***************************************************************
 *
 * set_flag
 * Description: The function invokes do_flag_operation for set flag
 *              operation
 ***************************************************************/
int set_flag(enum flags_id idn, uint8_t *flags_ret)
{
	int ret;

	ret = do_flag_operation(SET_FLAG_OPCODE, STANDARD_WR_REQ, idn, flags_ret);
	return ret;
}

/***************************************************************
 *
 * ToggleFlag
 * Description: The function invokes do_flag_operation for Toggle
 *               flag operation
 *
 ***************************************************************/
int ToggleFlag(enum flags_id idn, uint8_t *flags_ret)
{
	int ret;

	ret = do_flag_operation(TOGGLE_FLAG_OPCODE, STANDARD_WR_REQ, idn, flags_ret);
	return ret;
}

/***************************************************************
 *
 * ReadFlag 
 * Description: The function invokes do_flag_operation for Read 
 *               flag operation
 *
 ***************************************************************/
int read_flag(enum flags_id idn, uint8_t *flags_ret)
{
	int ret;

	ret = do_flag_operation(READ_FLAG_OPCODE, STANDARD_RD_REQ, idn, flags_ret);
	return ret;
}

/***************************************************************
 *
 * ClearFlag
 * Description: The function invokes do_flag_operation for Clear
 *               flag operation
 *
 ***************************************************************/
int ClearFlag(enum flags_id idn, uint8_t *flags_ret)
{
	int ret;

	ret = do_flag_operation(CLEAR_FLAG_OPCODE, STANDARD_WR_REQ, idn, flags_ret);
	return ret;
}

/***************************************************************
 *
 * read_nop_rsp
 * Description: The function reads and validates the response
 *              received for NOP command
 *
 ***************************************************************/
static int read_nop_rsp()
{
	struct dwc_ufs_nop_resp_upiu *resp_upiu;
	void   *tmp_ptr;

	tmp_ptr = ufs_info.cmd_desc->response_upiu;
	resp_upiu = (struct dwc_ufs_nop_resp_upiu *)tmp_ptr;

	/* read the OCS value */
	if(ufs_info.utrd_desc->ocs != UFS_SUCCESS) {
		return UFS_INVALID_RESPONSE;
	}

	if((resp_upiu->response != UFS_SUCCESS) || (resp_upiu->trans_type != NOP_TRANS_TYPE)) {
		return UFS_INVALID_RESPONSE;
	}

	return UFS_SUCCESS;
}

/***************************************************************
 *
 * send_nop_out_cmd()
 * Description: Invokes API for UPIU creation for nop out command
 * and sends it to the device by setting the DoorBell.
 *
 ****************************************************************/
int send_nop_out_cmd()
{
	int retry = RETRY_CNT;
	int ret;

	do {
		create_nop_out_upiu();
		retry--;
		ret = wait_for_cmd_completion();
		if(ret != UFS_SUCCESS) {
			ufs_writel(DW_UFS_UTRLCLR,0xfffffffe);
			continue;
		}

		ret = read_nop_rsp();
	} while (ret != UFS_SUCCESS && retry > 0);

	return ret;
}

void prepare_read_desc_upiu(struct dwc_ufs_query_upiu *req_upiu, uint8_t idn, uint8_t index)
{
	int     i;

	/* Command Descriptor Programming */
	req_upiu->trans_type        = 0x16;
	req_upiu->flags             = UPIU_CMD_FLAGS_NONE;
	req_upiu->reserved_1	    = 0x00;
	req_upiu->task_tag          = 0x01;
	req_upiu->reserved_2	    = 0x00;

	req_upiu->query_func        = STANDARD_RD_REQ;

	req_upiu->query_resp        = 0x00;
	req_upiu->reserved_3        = 0x00;
	req_upiu->tot_ehs_len       = 0x00;

	/*in big endian*/
	req_upiu->data_seg_len      = 0x00;

	req_upiu->tsf[0]            = READ_DESC_OPCODE;
	req_upiu->tsf[1]            = idn;
	req_upiu->tsf[2]            = index; /* index */
	req_upiu->tsf[3]            = 0x0;                /* selector */
	req_upiu->tsf[4]            = 0x0;
	req_upiu->tsf[5]            = 0x0;

	/*0xFF larger than all types of desc, so the response will provide the exact desc size*/
	req_upiu->tsf[6]            = 0x0;
	req_upiu->tsf[7]            = 0xFF;

	for(i=8; i < 15 ;i++)
		req_upiu->tsf[i]    = 0x00;

	for(i=0; i < 3 ;i++)
		req_upiu->reserved_5[i] = 0x00;

	return;
}

void preconfig_utrd_descriptor(void)
{
	ufs_info.utrd_desc->ucdba            = cpu_to_le32(LOWER_32_BITS((ulong)ufs_info.cmd_desc));
	ufs_info.utrd_desc->ucdbau           = cpu_to_le32(UPPER_32_BITS((ulong)ufs_info.cmd_desc));
	ufs_info.utrd_desc->resp_upiu_offset = cpu_to_le16(offsetof(struct dwc_ufs_tcd, response_upiu) >> 2);
	ufs_info.utrd_desc->prdt_offset      = cpu_to_le16(offsetof(struct dwc_ufs_tcd, prdt_table) >> 2);
	ufs_info.utrd_desc->ocs = 0xf;
}

void preconfig_utm_descriptor()
{
	int i;

	for(i = 0; i < 3; i++)
		ufs_info.utm_desc->reserved_1[i] = 0x0;

	ufs_info.utm_desc->intr_flag  = 0x0;
	ufs_info.utm_desc->reserved_2 = 0x0;
	ufs_info.utm_desc->ocs = 0xf;

	for(i = 0; i < 3; i++)
		ufs_info.utm_desc->reserved_3[i] = 0x0;

	ufs_info.utm_desc->reserved_4 = 0x0;
	return;
}


void init_global_reg()
{
	uint32_t temp = 0;

	temp = readl((void *)REG_AP_APB_APB_EB1);
	temp |= BIT_AP_APB_UFS_UTP_EB | BIT_AP_APB_UFS_HCI_EB |
				BIT_AP_APB_UFS_UNIPRO_EB | BIT_AP_APB_UFS_EB;
	writel(temp, (void *)REG_AP_APB_APB_EB1);

	temp = readl((void *)REG_AON_APB_APB_EB1);
	temp |= BIT_AON_APB_UFS_AO_EB;
	writel(temp, (void *)REG_AON_APB_APB_EB1);

	// PRESETn_mphy
	REG32(0x323b4014 ) &= ~(BIT_3);
	REG32(0x323b4014 ) &= ~(BIT_3);
	udelay(1000);
	REG32(0x323b4014 ) |= (BIT_3);

	// [26]: PRESETn_utp, [25]: PRESETn_hci, [24]: PRESETn_unipro, [23]: ARESETn_ufs
	REG32(0x71000004) |= (BIT_23|BIT_24|BIT_25|BIT_26);
	udelay(1000);
	REG32(0x71000004) &= ~(BIT_23|BIT_24|BIT_25|BIT_26);

	// PRESETn_ao
	REG32(0x32090010)|=BIT_15;
	udelay(1000);
	REG32(0x32090010)&=~BIT_15;

	// DL reset
	REG32(0x71800040) |= BIT_0;
	udelay(1000);
	REG32(0x71800040) &= ~BIT_0;

	// N reset
	REG32(0x71800084) |= BIT_1;
	udelay(1000);
	REG32(0x71800084) &= ~BIT_1;

	// T reset
	REG32(0x718000c0) |= BIT_4;
	udelay(1000);
	REG32(0x718000c0) &= ~BIT_4;

	// DME reset
	REG32(0x718000d0) |= BIT_2;
	udelay(1000);
	REG32(0x718000d0) &= ~BIT_2;

	// HCI reset
	REG32(0x719000b0 ) |= (BIT_12|BIT_28);

	// UTP reset
	REG32(0x71A00100 ) &= ~(BIT_0 |BIT_1);
	udelay(1000);
	REG32(0x71A00100 ) |= (BIT_0 |BIT_1);

	udelay(1000);
	REG32(0x719000b0 ) &= ~(BIT_12|BIT_28);

	// AO reset
	REG32(0x3251001c) |= BIT_1;
	udelay(1000);
	REG32(0x3251001c) &= ~BIT_1;

	// [29]: PA reset, [28]: CB reset, [27]: RX1 reset, [26]: RX0 reset, [25]: TX1 reset, [24]: TX0 reset
	REG32(0x7180003c) |= (BIT_24|BIT_25|BIT_26|BIT_27|BIT_28|BIT_29);
	udelay(1000);
	REG32(0x7180003c) &= ~(BIT_24|BIT_25|BIT_26|BIT_27|BIT_28|BIT_29);

	//fix osc error
	REG32(0x719000A4) |= BIT_29;

	//WORKAROUND no rsp data abort error
	REG32(0x71a00104) &= ~0xff;
	REG32(0x71a00104) |= 0x4;

	//WORKAROUND no rsp data abort error
	REG32(0x323b4008) |= 0xff;
	REG32(0x323b801c) &= ~(0x7 << 14);
	REG32(0x323b801c) |= 0x4 << 14;
}

/****************************************************************
 *
 * init_ufs_hostc
 * Description: The Function does the following
 *            1. Sets Clock Divider
 *            2. Resets the Host Controller
 *            3. Performs Loopback Configuration if enabled
 *            4. Sends the LinkStartUp command
 *            5. Allocates and configures UTRD's
 *
 ****************************************************************/
int init_ufs_hostc()
{
	int      ret    = 0;
	int      retry = RETRY_CNT;
	uint32_t temp = 0;

	/*Exit hibernate*/
	send_uic_command(UIC_EXIT_HIBERNATE, 0, 0, 0);
	wait_uic_complete();

	/* Reset the UFS Host Controller */
	ret = dwc_reset_hc();
	if(ret != 0)
		return ret;

	/* Update the DWC UFSHCI specification that the controller implementation supports*/	
	//ufs_info.dwc_ufs_version = ufs_readl(DW_UFS_VER);

	ufs_info.dwc_ufs_version = DWC_UFS_HC_VERSION_2_1;
	ufs_info.prdt_entry_size = PRDT_BUFFER_SIZE;
	ufs_info.max_prdt_cap =  TOTAL_PRDT_CAP;

#ifdef DWC_UFS_LOOPBACK_MODE /* For Debug Purpose Only */
	/* LOOP Back Configuration */
	ufs_writel(DW_UFS_LBMCFG, LOOPBACK_DEFAULT);
#else
	/*
	 * Send locally created DME_LINKSTARTUP UIC command to start the
	 * Link Startup Procedure
	 * keep sending the DME_LINKSTARTUP command until the device is detected
	 */
	while(retry > 0) {
		if(ufs_readl(DW_UFS_HCS) & DW_UFS_HCS_UCRDY) {
			send_dme_link_startup();
		} else {
			dwc_reset_hc();
			retry--;
			continue;
		}

		wait_uic_complete();

		if(ufs_readl(DW_UFS_HCS) & DW_UFS_HCS_DP) {
			break;
		}
		/* Do the HCE reset before sending next link startup command */
		dwc_reset_hc();
		retry--;

	}
	if(retry == 0)
		return UFS_TIMEOUT;

	if(0 != check_uic_link_startup_result())
		return UFS_INVALID_RESPONSE;
#endif

	ufs_info.cmd_desc = &ucd;
	ufs_info.utrd_desc = &utrd;
	ufs_info.utm_desc = &utmd;

	/* Initialize the transfer request descriptor */
	preconfig_utrd_descriptor();

	/* 
	 * Write the descriptor base address in the UTRLBA register
	 * for the Transfer Requests
	 */
	ufs_writel(DW_UFS_UTRLBA,  LOWER_32_BITS((ulong)ufs_info.utrd_desc));
	ufs_writel(DW_UFS_UTRLBAU, UPPER_32_BITS((ulong)ufs_info.utrd_desc));

	/* Initialize the task management descriptor */
	preconfig_utm_descriptor();

	/* 
	 * Write the descriptor base address in the UTRLBA register
	 * for the Transfer Requests
	 */
	ufs_writel(DW_UFS_UTMRLBA,  LOWER_32_BITS((ulong)ufs_info.utm_desc));
	ufs_writel(DW_UFS_UTMRLBAU, UPPER_32_BITS((ulong)ufs_info.utm_desc));

	/*
	 * Enable UTP Transfer request List by writing to UTRLRSR
	 */
	ufs_writel(DW_UFS_UTRLRSR, 0x1);

	/*
	 * Enable UFS Task Managament List by writing to DW_UFS_UTMRLRSR
	 */
	ufs_writel(DW_UFS_UTMRLRSR, 0x1);

	return UFS_SUCCESS;
}


/***************************************************************
 *
 * init_ufs_device()
 * Description: The function does the following
 *            1. Sends the NOP Out command continuosly till it passes
 *            2. Sets the Device init Flag for UFS Device initialization
 *
 ****************************************************************/
int init_ufs_device()
{
	int ret;
	uint8_t flags_ret_val;
	int retry = RETRY_CNT;

	/* Send continuos NOP OUT Command unless Response is Valid */
	ret = send_nop_out_cmd();
	if(ret != UFS_SUCCESS) {
		return ret;
	}

	/* Set the Device Init Flag */
	ret = set_flag(FDEVICE_INIT, &flags_ret_val);
	if(ret)
		return ret;
	do {
		retry--;
		ret = read_flag(FDEVICE_INIT, &flags_ret_val);
		if ((ret == UFS_SUCCESS) && (flags_ret_val == 0)) {
			break;
		} else {
			ufs_writel(DW_UFS_UTRLCLR,0xfffffffe);
		}
	} while (retry > 0);

	if(flags_ret_val != 0) {
		ret = UFS_FDEVICE_INIT_FAIL;
	}

	return ret;


}


void change_ufs_power_mode(void)
{
	int ret = 0;
	int retry = 100;
	uint32_t upms_intr_res = 0;
	struct ufs_pa_layer_attr pwr_info;

	pwr_info.pwr_rx = FAST_MODE;
	pwr_info.pwr_tx = FAST_MODE;
	pwr_info.hs_rate = PA_HS_MODE_A;

	/*Get max power mode*/
	pwr_info.lane_rx = dme_get(PA_CONNECTEDRXDATALANES);
	pwr_info.lane_tx = dme_get(PA_CONNECTEDTXDATALANES);
	if (0 == pwr_info.lane_rx || 0 == pwr_info.lane_tx) {
		return;
	}

	pwr_info.gear_rx = UFS_HS_G2;
	if (0 == pwr_info.gear_rx) {
		pwr_info.gear_rx = dme_get(PA_MAXRXPWMGEAR);
		if (0 == pwr_info.gear_rx) {
			return;
		}
		pwr_info.pwr_rx = SLOWAUTO_MODE;
	}

	pwr_info.gear_tx = UFS_HS_G2;
	if (0 == pwr_info.gear_tx) {
		pwr_info.gear_tx = dme_peer_get(PA_MAXRXPWMGEAR);
		if (0 == pwr_info.gear_tx) {
			return;
		}
		pwr_info.pwr_tx = SLOWAUTO_MODE;
	}

	/*Set power mode*/
	dme_set(PA_TXGEAR, pwr_info.gear_tx);
	dme_set(PA_RXGEAR, pwr_info.gear_rx);

	if (pwr_info.pwr_rx == FASTAUTO_MODE ||
	    pwr_info.pwr_tx == FASTAUTO_MODE ||
	    pwr_info.pwr_rx == FAST_MODE ||
	    pwr_info.pwr_tx == FAST_MODE)
		dme_set(PA_HSSERIES, pwr_info.hs_rate);

	dme_set(PA_ACTIVETXDATALANES, pwr_info.lane_tx);
	dme_set(PA_ACTIVERXDATALANES, pwr_info.lane_rx);

	if (FASTAUTO_MODE == pwr_info.pwr_tx || FAST_MODE == pwr_info.pwr_tx)
		dme_set(PA_TXTERMINATION, 1);
	else
		dme_set(PA_TXTERMINATION, 0);

	if (FASTAUTO_MODE == pwr_info.pwr_rx ||FAST_MODE == pwr_info.pwr_rx)
		dme_set(PA_RXTERMINATION, 1);
	else
		dme_set(PA_RXTERMINATION, 0);

	dme_set(PA_PWRMODE, (pwr_info.pwr_rx << 4) | pwr_info.pwr_tx);

	/*check set power mode result*/
	while(retry > 0) {
		upms_intr_res = ufs_readl(DW_UFS_IS) & DW_UFS_IS_UPMS;
		if (upms_intr_res) {
			ufs_writel(DW_UFS_IS, upms_intr_res);
			break;
		}
		udelay(1000);
		retry--;
	}

	if (0 == retry) {
		return;
	}

	ret = (ufs_readl(DW_UFS_HCS) >> 8) & 0x7;

	return;
}


int ufs_init()
{
	init_global_reg();
	init_ufs_hostc();
	init_ufs_device();
	sprd_ufs_block_dev_config();
	change_ufs_power_mode();

	return TRUE;
}

void reset_and_restore_hc()
{
	init_global_reg();
	init_ufs_hostc();
	init_ufs_device();
	change_ufs_power_mode();
}

static void create_cmd_upiu(uint32_t lun, uint32_t opcode, enum dma_data_direction direction,
							void *buf_addr,
							ulong start, ulong blkcnt, uint8_t cmd_set_type)
{
	struct   dwc_ufs_cmd_upiu *cmd_upiu_ptr = NULL;
	uint32_t data_direction = 0;
	uint8_t  upiu_flags = 0;
	uint32_t prdt_buf_size = ufs_info.prdt_entry_size;
	void     *tmp_ptr = NULL;
	uint32_t i = 0;
	uint32_t transfer_size = 0;
	uint8_t  *ptr = NULL;
	ulong size = 0;
	ulong list_len = 0;
	struct unmap_para_list *um_list = NULL;

	tmp_ptr = ufs_info.cmd_desc->command_upiu;
	clear_cmd_desc(tmp_ptr);
	cmd_upiu_ptr = (struct dwc_ufs_cmd_upiu *)(tmp_ptr);

	if (direction == DMA_FROM_DEVICE) {
		data_direction = UTP_DEVICE_TO_HOST;
		upiu_flags     = UPIU_CMD_FLAGS_READ;
	} else if (direction == DMA_TO_DEVICE) {
		data_direction = UTP_HOST_TO_DEVICE;
		upiu_flags     = UPIU_CMD_FLAGS_WRITE;
	} else {
		data_direction = UTP_NO_DATA_TRANSFER;
		upiu_flags     = UPIU_CMD_FLAGS_NONE;
	}

	/* Update cmd_type, flags and response upiu length for transfer requests */
	if ((ufs_info.dwc_ufs_version == DWC_UFS_HC_VERSION_2_0) || (ufs_info.dwc_ufs_version == DWC_UFS_HC_VERSION_2_1))
		ufs_info.utrd_desc->ct_and_flags = (uint8_t)(data_direction | UTP_UFS_STORAGE_COMMAND);
	else
		ufs_info.utrd_desc->ct_and_flags = (uint8_t)(data_direction | UTP_SCSI_COMMAND);
	ufs_info.utrd_desc->resp_upiu_length = cpu_to_le16((uint16_t)(sizeof(struct dwc_ufs_xfer_resp_upiu) >> 2));

	cmd_upiu_ptr->trans_type        = 0x01;
	cmd_upiu_ptr->flags             = upiu_flags;
	cmd_upiu_ptr->lun               = lun;
	cmd_upiu_ptr->task_tag          = 0x1;
	cmd_upiu_ptr->cmd_set_type      = cmd_set_type;
	cmd_upiu_ptr->reserved_1[0]     = 0x0;
	cmd_upiu_ptr->reserved_1[1]     = 0x0;
	cmd_upiu_ptr->reserved_1[2]     = 0x0;
	cmd_upiu_ptr->tot_ehs_len       = 0x0;
	cmd_upiu_ptr->reserved_2        = 0x0;
	cmd_upiu_ptr->data_seg_len = 0x0;

	if (opcode == UFS_OP_SECURITY_PROTOCOL_IN || opcode == UFS_OP_SECURITY_PROTOCOL_OUT) {
		/*TODO, for RPMB, size in unit of byte*/
		size = blkcnt << 0xc;
		get_cmnd(opcode, 0, size, cmd_upiu_ptr->cdb);
		prdt_buf_size = RPMB_FRAME_SIZE;
	} else if (UFS_OP_UNMAP == opcode) {
		list_len = sizeof(struct unmap_para_list);
		get_cmnd(opcode, 0, list_len, cmd_upiu_ptr->cdb);
	} else {
		get_cmnd(opcode, start, blkcnt, cmd_upiu_ptr->cdb);
	}

	if (direction != DMA_NONE) {
		transfer_size = blkcnt << 0xc;
		if (UFS_OP_UNMAP == opcode)
			transfer_size = sizeof(struct unmap_para_list);
		cmd_upiu_ptr->exp_data_xfer_len = cpu_to_be32(transfer_size);

		/* Update PRDT Length */
		/*the caller must guarantee that the transfer_size no more than max prdt capability*/
		ufs_info.utrd_desc->prdt_length = (uint16_t)((0 == transfer_size % prdt_buf_size) ?
						(transfer_size /prdt_buf_size) : (transfer_size /prdt_buf_size + 1));

		/* Fill PRD Table Info */
		for (i = 0; transfer_size > 0; i++) {
			ufs_info.cmd_desc->prdt_table[i].base_addr
				 = LOWER_32_BITS((ulong)(buf_addr + i * prdt_buf_size));
			ufs_info.cmd_desc->prdt_table[i].upper_addr
				 = UPPER_32_BITS((ulong)(buf_addr + i * prdt_buf_size));

			ufs_info.cmd_desc->prdt_table[i].reserved1  = 0x0;
			if (transfer_size > prdt_buf_size) {
				ufs_info.cmd_desc->prdt_table[i].size = prdt_buf_size - 1;
				transfer_size -= prdt_buf_size;
			} else {
				ufs_info.cmd_desc->prdt_table[i].size = transfer_size - 1;
				transfer_size = 0;
			}
		}
	} else {
		cmd_upiu_ptr->exp_data_xfer_len = 0;
		ufs_info.utrd_desc->prdt_length = 0;
	}

	return;
}


int send_scsi_cmd(uint32_t lun, uint32_t opcode, enum dma_data_direction direction,
						void *buf_addr,
						ulong start, ulong blkcnt, uint8_t cmd_set_type)
{
	int ret;
	int retry = 4;
	do {
		create_cmd_upiu(lun, opcode, direction, buf_addr, start, blkcnt, cmd_set_type);

		ret = wait_for_cmd_completion();
		if (UFS_SUCCESS != ret)
			reset_and_restore_hc();
		else
			ret = handle_scsi_completion();

		retry--;
	} while (UFS_SUCCESS != ret && retry > 0);

	return ret;
}


int test_unit_ready(uint32_t lun)
{
	int ret = 0;
	int retry = 3;
	do {
		ret = send_scsi_cmd(lun, UFS_OP_TEST_UNIT_READY, DMA_NONE, NULL, 0, 0, 0);
		retry--;
	} while (UFS_SUCCESS != ret && retry > 0);

	return ret;
}

static ulong ufs_bread(uint32_t dev_num, ulong start, ulong blkcnt, void *dst)
{
	int ret;
	ulong blocks_todo = blkcnt;
	ulong cur = 0;
	uint32_t max_read_size = 0;
	ulong max_read_blk = 0;
	void * temp_buff;

	ret = test_unit_ready(dev_num);
	if (UFS_SUCCESS != ret) {
		return 0;
	}

		max_read_blk = ufs_info.max_prdt_cap >> 0xc;
		do {
			cur = (blocks_todo > max_read_blk) ? max_read_blk : blocks_todo;
			/* Send Read 10 Command and handle its completion */
			ret = send_scsi_cmd(dev_num, UFS_OP_READ_10, DMA_FROM_DEVICE, dst, start, cur, 0);
			if (ret != UFS_SUCCESS)
				return 0;
			blocks_todo -= cur;
			start += cur;
			dst += cur << 0xc;
		} while (blocks_todo > 0);

	return TRUE;
}

void sprd_ufs_block_dev_config()
{	sprd_ufs_dev.part_type = PART_TYPE_EFI;
	sprd_ufs_dev.dev = 0;
	sprd_ufs_dev.blksz = UFS_SECTOR_SIZE;
	sprd_ufs_dev.block_read = ufs_bread;
}

block_dev_desc_t *ufs_get_dev()
{
	return ((block_dev_desc_t *) & sprd_ufs_dev);
}

