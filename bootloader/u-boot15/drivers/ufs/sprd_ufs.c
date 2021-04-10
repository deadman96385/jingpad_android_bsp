#include <common.h>
#include <sprd_ufs.h>
#include "protocol_util.h"
#include "uiccmd.h"
#include "ip_env.h"
#include <malloc.h>
#include <linux/io.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/ufs_cfg.h>
#include "asm/cache.h"

struct   ufs_driver_info ufs_info;

uint32_t fatal_err = 0;

struct backstage_recovery bs_recv;

struct lu_specific_cfg_tbl factory_lu_tbl[UFS_PLATFORM_LU_NUM] = {
	/*lu_index, bootable,               log2blksz,  blkcnt,  lu_context, memory_type*/
	{0x00,             NONE_BOOT, 	    0x0C, 		0        ,    	0xFF,		NORMAL_MEMORY},
	{0x01,              MAIN_BOOT, 		    0x0C, 		1024,    	0x0,			ENHANCED_MEMORY_1},
	{0x02,              ALTERNATE_BOOT, 0x0C, 		1024,    	0x0,			ENHANCED_MEMORY_1}
};

struct lu_common_cfg_tbl lu_common_tbl = {
	/*write_protect, 		      provisioning_type,              data_reliability*/
	WRITE_PROTECT_POWERON,  PROV_ENABLE_WITH_TPRZ, DATA_PROTECTED
};

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
			debugf("Reset UFS host controller success\n");
			return UFS_SUCCESS;
		}

		retry--;
		udelay(1); /* Platform Specific Implementation */
	}

	return UFS_TIMEOUT;
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

	flush_dcache_all();
	/* Set the doorbell for processing the request */
	ufs_writel(DW_UFS_UTRLDBR, BIT(0));

	/* Wait for the DoorBell to clear */
	while(1) {
		udelay(50);
		is_status = ufs_readl(DW_UFS_IS);
		if (0 != is_status)
			ufs_writel(DW_UFS_IS, is_status);
		if (0 != (is_status & IS_FATAL_ERROR)) {
			errorf("Meet UFS fatal error, Interrupt Status=0x%x\n", is_status);
			ufs_writel(DW_UFS_UTRLCLR, 0xfffffffe);
			/*for stress test*/
			fatal_err++;
			return UFS_FATAL_ERROR;
		}
		if((ufs_readl(DW_UFS_UTRLDBR) & BIT(0)) == 0)
			break;
		retry--;
		if(retry == 0) {
			debugf("DoorBell Not Cleared and Timed Out\n");
			return UFS_TIMEOUT;
		}
	}

#ifdef CONFIG_X86
	/*instruction "invd" must be excuted inline, it's strange*/
	invd();
#else
	invalidate_dcache_range(0, 0);
#endif

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
			errorf("Meet UFS fatal error, Interrupt Status=0x%x\n", is_status);
			ufs_writel(DW_UFS_UTRLCLR, 0xfffffffe);
			/*for stress test*/
			fatal_err++;
			return UFS_FATAL_ERROR;
		}
		if((ufs_readl(DW_UFS_UTRLDBR) & BIT(0)) == 0)
			break;
		retry--;
		if(retry == 0) {
			debugf("DoorBell Not Cleared and Timed Out\n");
			return UFS_TIMEOUT;
		}
		udelay(5); /* Platform Specific Implementation */
	}

#ifdef CONFIG_X86
	/*instruction "invd" must be excuted inline, it's strange*/
	//invd();
#else
	invalidate_dcache_range(0, 0);
#endif

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
 * read_attribute
 * Description: The functon sends the query command to read an
 *              attribute and updates the ret_value with the 
 *              content of the attribute
 *
 ***************************************************************/
int read_attribute(enum attr_id idn, uint8_t *ret_value, uint8_t selector)
{
	int ret = 0;
	int retry = 4;
	int i = 0;

	for(i=0;i < 4;i++)
		ret_value[i] = 0x00;
	debugf("read idn=0x%x\n", idn);
	do {
		create_query_upiu(READ_ATTR_OPCODE, STANDARD_RD_REQ, selector, idn, ret_value);
		ret = wait_for_cmd_completion();
		if (ret != UFS_SUCCESS)
			reset_and_restore_hc();
		else
			ret = handle_query_response(ret_value);
		retry--;
	} while (UFS_SUCCESS != ret && retry > 0);

	return ret;
}


/***************************************************************
 *
 * write_attribute
 * Description: The functon sends the query command to write an
 *              attribute with the value passed as second argument
 *
 ***************************************************************/
int write_attribute(enum attr_id idn, uint8_t *value, uint8_t selector)
{
	int ret = 0;
	int retry = 4;

	debugf("write idn=0x%x\n", idn);
	do {
		create_query_upiu(WRITE_ATTR_OPCODE, STANDARD_WR_REQ, selector, idn, value);
		ret = wait_for_cmd_completion();
		if (ret != UFS_SUCCESS)
			reset_and_restore_hc();
		else
			ret = handle_query_response(value);
		retry--;
	} while (UFS_SUCCESS != ret && retry > 0);

	return ret;
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
		status = resp_upiu->status;
		if(status == SAM_STAT_GOOD)
			return UFS_SUCCESS;
		/* 0x20 is added to sense key to return unique error code */
		if(status == SAM_STAT_CHECK_CONDITION) {
			errorf("SCSI Command error, sense data=0x%x, see more in SPEC 10.5.4\n",
				resp_upiu->sense_data[SENSE_KEY_INDEX]);
			return -(0x20 + (resp_upiu->sense_data[SENSE_KEY_INDEX] & 0xf));
		}
	} else {
		errorf("Returned OCS value is 0x%x\n",ufs_info.utrd_desc->ocs);
		return -(ufs_info.utrd_desc->ocs);
	}

	return UFS_SUCCESS;
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
		errorf("NOP OUT No response\n");
		return UFS_INVALID_RESPONSE;
	}

	if((resp_upiu->response != UFS_SUCCESS) || (resp_upiu->trans_type != NOP_TRANS_TYPE)) {
		errorf("NOP OUT response fail\n");
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
		debugf("NOP OUT response ret = 0x%x\n", ret);
	} while (ret != UFS_SUCCESS && retry > 0);

	return ret;
}

/***************************************************************
 *
 * check_config_desclock
 * Description: The function reads the bConfigDescLock attribute
 *              and returns UFS_SUCCESS if unlocked.
 *
 ***************************************************************/
int check_config_desclock()
{
	uint8_t attr[4];
	int ret = 0;

	/* read bConfigDescLock */
	ret = read_attribute(B_CONFIG_DESC_LOCK,attr,0);
	if (ret != UFS_SUCCESS) {
		errorf("Read attribute(bConfigDescrLock) fail, fail code=0x%x\n", ret);
		return ret;
	}

	if(attr[3] != 0) {
		debugf("Attribute(bConfigDescrLock) been locked!\n");
		return UFS_CONFIG_DESC_LOCKED;
	}
	return UFS_SUCCESS;
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

/***************************************************************
 *
 * read_descriptor
 * Description: The functon populates the request upiu structure
 		with upiu info passed in 1st argument
 *
 ***************************************************************/
int write_read_descriptor(void *req_upiu)
{
	int ret;
	int     i;
	uint8_t *ptr;

	/* UTRD Descriptor Programming for processing command */
	if ((ufs_info.dwc_ufs_version == DWC_UFS_HC_VERSION_2_0) || (ufs_info.dwc_ufs_version == DWC_UFS_HC_VERSION_2_1))
		ufs_info.utrd_desc->ct_and_flags = (uint8_t)(UTP_NO_DATA_TRANSFER | UTP_UFS_STORAGE_COMMAND);
	else
		ufs_info.utrd_desc->ct_and_flags = (UTP_NO_DATA_TRANSFER | UTP_DEVICE_MANAGEMENT_FUNCTION);

	/*why use dwc_ufs_query_upiu size? there are always attached data follow the response upiu*/
	ufs_info.utrd_desc->resp_upiu_length = (ALIGNED_UPIU_SIZE) >> 2;
	ufs_info.utrd_desc->prdt_length = 0;

	ret = wait_for_cmd_completion();
	if(ret != UFS_SUCCESS)
		return ret;

	ptr = ufs_info.cmd_desc->response_upiu;

	ret = handle_query_response(NULL);
	return ret;
}


int get_descriptor_data(void ** desc_ptr, uint8_t idn, uint8_t index)
{
	int      ret;
	int retry = 3;
	struct   dwc_ufs_query_upiu *req_upiu;
	uint8_t * resp_upiu;

	do {
		req_upiu = (struct dwc_ufs_query_upiu *)(ufs_info.cmd_desc->command_upiu);
		prepare_read_desc_upiu(req_upiu, idn, index);
		ret = write_read_descriptor(req_upiu);
		if (UFS_SUCCESS != ret) {
			reset_and_restore_hc();
		} else {
			resp_upiu = ufs_info.cmd_desc->response_upiu;
			*desc_ptr = (uint8_t *)resp_upiu + sizeof(struct dwc_ufs_query_upiu);
		}
		retry--;
	} while (UFS_SUCCESS != ret && retry > 0);

	return ret;
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

	dme_hibernate_exit();

	/* Reset the UFS Host Controller */
	ret = dwc_reset_hc();
	if(ret != 0)
		return ret;

	ufs_info.dwc_ufs_version = DWC_UFS_HC_VERSION_2_1;

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
			debugf("Send link startup UIC command\n");
			dme_link_startup();
		} else {
			dwc_reset_hc();
			retry--;
			continue;
		}

		if(ufs_readl(DW_UFS_HCS) & DW_UFS_HCS_DP) {
			debugf("Connection been established with UFS device!\n");
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

	ufs_info.cmd_desc = (struct dwc_ufs_tcd *) memalign(SZ_128, sizeof(struct dwc_ufs_tcd));
	ufs_info.utrd_desc = (struct dwc_ufs_utrd *) memalign(SZ_1K, sizeof(struct dwc_ufs_utrd));
	ufs_info.utm_desc = (struct dwc_ufs_utmrd *) memalign(SZ_1K, sizeof(struct dwc_ufs_utmrd));

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
		errorf("Send nop out command fail, ret = 0x%x\n", ret);
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
			debugf("fDeviceInit flag==0, UFS device init complete\n");
			break;
		} else {
			ufs_writel(DW_UFS_UTRLCLR,0xfffffffe);
		}
	} while (retry > 0);

	if(flags_ret_val != 0) {
		errorf("UFS device init fail!\n");
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
		errorf("invalid connected lanes value. rx=%d, tx=%d\n", pwr_info.lane_rx, pwr_info.lane_tx);
		return;
	}

	pwr_info.gear_rx = dme_get(PA_MAXRXHSGEAR);
	if (0 == pwr_info.gear_rx) {
		pwr_info.gear_rx = dme_get(PA_MAXRXPWMGEAR);
		if (0 == pwr_info.gear_rx) {
			errorf("invalid max pwm rx gear read = %d\n", pwr_info.gear_rx);
			return;
		}
		pwr_info.pwr_rx = SLOWAUTO_MODE;
	}

	pwr_info.gear_tx = dme_peer_get(PA_MAXRXHSGEAR);
	if (0 == pwr_info.gear_tx) {
		pwr_info.gear_tx = dme_peer_get(PA_MAXRXPWMGEAR);
		if (0 == pwr_info.gear_tx) {
			errorf("invalid max pwm tx gear read = %d\n", pwr_info.gear_tx);
			return;
		}
		pwr_info.pwr_tx = SLOWAUTO_MODE;
	}
	debugf("Power mode:pwr_rx(%d), pwr_tx(%d), lane_rx(%d), lane_tx(%d), gear_rx(%d), gear_tx(%d), hs_rate(%d)\n",
		pwr_info.pwr_rx, pwr_info.pwr_tx, pwr_info.lane_rx, pwr_info.lane_tx,
		pwr_info.gear_rx, pwr_info.gear_tx, pwr_info.hs_rate);

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
		errorf("Change power mode fail!!\n");
		return;
	}

	ret = (ufs_readl(DW_UFS_HCS) >> 8) & 0x7;
	if (PWR_LOCAL != ret)
		errorf("Fail to change power mode, power status is %d\n", ret);

	return;
}


void ufs_init()
{
	init_global_reg();
	init_ufs_hostc();
	init_ufs_device();
	ufs_update_native();
	change_ufs_power_mode();
}

void release_desc_mem()
{
	free(ufs_info.cmd_desc);
	free(ufs_info.utrd_desc);
	free(ufs_info.utm_desc);
	return;
}

void reset_and_restore_hc()
{
	release_desc_mem();
	init_global_reg();
	init_ufs_hostc();
	init_ufs_device();
	change_ufs_power_mode();
}

uint32_t enhance_memory_alloc_unit(enum lu_memory_type memory_type,uint64_t blk_cnt, uint32_t log2_blk_sz)
{
	uint32_t au_num = 0;
	uint64_t total_size = 0;
	uint16_t alloc_adj = 1;

	if (memory_type == ENHANCED_MEMORY_1)
		alloc_adj = ufs_info.bootAdjFac;
	else
		alloc_adj = 1;

	total_size = blk_cnt * (1 << log2_blk_sz);
	au_num = total_size * alloc_adj / (ufs_info.alloc_unit_sz * SZ_512);

	return au_num;
}

int compare_cfg_lu_table(struct lu_specific_cfg_tbl *lu_cfg, struct lu_common_cfg_tbl *common_cfg)
{
	int ret = LU_INFO_SAME;
	uint32_t aligned_au_new = 0;
	uint32_t aligned_au_old = 0;
	int lun_index = 0;
	int last_lu = 0;
	if (0 == ufs_info.lu_num) {
		debugf("No lu config in old table,diff\n");
		return LU_INFO_DIFF;
	}

	for (lun_index = 0; lun_index < UFS_PLATFORM_LU_NUM; lun_index++) {
		if (lu_cfg[lun_index].lu_index != ufs_info.lu_info[lun_index].lu_index
				|| lu_cfg[lun_index].bootable != ufs_info.lu_info[lun_index].bootable
				|| lu_cfg[lun_index].log2blksz != ufs_info.lu_info[lun_index].log2blksz
				|| lu_cfg[lun_index].memory_type != ufs_info.lu_info[lun_index].memory_type) {
			debugf("lun_index(%d) different...\n ", ufs_info.lu_info[lun_index].lu_index);
			ret = LU_INFO_DIFF;
			break;
		}

		if (lu_cfg[lun_index].lu_context != ufs_info.lu_info[lun_index].lu_context
				&& 0xFF != lu_cfg[lun_index].lu_context) {
			debugf("lun_index(%d) different in lu_context...\n ", ufs_info.lu_info[lun_index].lu_index);
			ret = LU_INFO_DIFF;
			break;
		}

		if (common_cfg->write_protect != ufs_info.lu_info[lun_index].write_protect
				|| common_cfg->provisioning_type != ufs_info.lu_info[lun_index].provisioning_type
				|| common_cfg->data_reliability != ufs_info.lu_info[lun_index].data_reliability) {
			debugf("lun_index(%d) different in common config...\n ", ufs_info.lu_info[lun_index].lu_index);
			ret = LU_INFO_DIFF;
			break;
		} else {
			break;
		}

		if (ufs_info.lu_info[lun_index].memory_type == ENHANCED_MEMORY_1) {
			aligned_au_new = enhance_memory_alloc_unit(lu_cfg[lun_index].memory_type, lu_cfg[lun_index].blkcnt, lu_cfg[lun_index].log2blksz);
			aligned_au_old = enhance_memory_alloc_unit(ufs_info.lu_info[lun_index].memory_type, ufs_info.lu_info[lun_index].blkcnt, ufs_info.lu_info[lun_index].log2blksz);

			if (aligned_au_new != aligned_au_old) {
				debugf("lun_index(%d) blkcnt diff with old one\n", lun_index);
				ret = LU_INFO_DIFF;
				break;
			}
		}
	}

	return ret;
}

void prepare_write_desc_upiu(struct dwc_ufs_query_upiu *req_upiu, 
			struct ufs_cfg_desc_tbl *default_desc, struct lu_specific_cfg_tbl *new_cfg,
			struct lu_common_cfg_tbl *common_cfg)
{
	uint16_t data_len = 0;
	int lu_index = 0;
	uint32_t au_num = 0;
	uint32_t id = 0;
	uint64_t assigned_au = 0;
	struct ufs_cfg_desc_tbl *req_cfg_desc;
	uint16_t assigned_context = 0;
	uint16_t context = 0;

	/* Command Descriptor Programming */
	req_upiu->trans_type        = 0x16;
	req_upiu->flags             = UPIU_CMD_FLAGS_NONE;
	req_upiu->reserved_1	    = 0x00;
	req_upiu->task_tag          = 0x01;
	req_upiu->reserved_2	    = 0x00;

	req_upiu->query_func        = STANDARD_WR_REQ;

	req_upiu->query_resp        = 0x00;
	req_upiu->reserved_3        = 0x00;
	req_upiu->tot_ehs_len       = 0x00;

	data_len = (uint16_t) (sizeof(struct ufs_cfg_desc_tbl) & 0xFFFF);
	/*in big endian*/
	req_upiu->data_seg_len      = cpu_to_be16(data_len);

	req_upiu->tsf[0]            = WRITE_DESC_OPCODE;
	req_upiu->tsf[1]            = CONFIGURATION_DESC;  /*idn*/
	req_upiu->tsf[2]            = 0; /* index */
	req_upiu->tsf[3]            = 0x0;                /* selector */
	req_upiu->tsf[4]            = 0x0;
	req_upiu->tsf[5]            = 0x0;

	req_upiu->tsf[6]            = (uint8_t) ((sizeof(struct ufs_cfg_desc_tbl) >> 8)  & 0xFF);
	req_upiu->tsf[7]            = (uint8_t) (sizeof(struct ufs_cfg_desc_tbl) & 0xFF);

	for(id = 8; id < 15 ;id++)
		req_upiu->tsf[id]    = 0x00;

	for(id = 0; id < 3 ;id++)
		req_upiu->reserved_5[id] = 0x00;
	req_cfg_desc = (struct ufs_cfg_desc_tbl *)((uchar *)req_upiu + sizeof(struct dwc_ufs_query_upiu));
	if (req_cfg_desc != default_desc)
		memcpy(req_cfg_desc, default_desc, sizeof(struct ufs_cfg_desc_tbl));
	req_cfg_desc->bBootEnable = 0x01;
	req_cfg_desc->bDescrAccessEn = 0x01;
	assigned_au = 0;

	/*pre allocate allocation_unit*/
	for(id = 0; id < UFS_PLATFORM_LU_NUM; id++) {
		if (0 != new_cfg[id].blkcnt) {
		au_num = enhance_memory_alloc_unit(new_cfg[id].memory_type, new_cfg[id].blkcnt, new_cfg[id].log2blksz);
		assigned_au += au_num;
		}
	}

	id = 0;
	for (lu_index = 0; lu_index < UFS_MAX_LU_NUM; lu_index++) {
		if (UFS_PLATFORM_LU_NUM == id)
			break;
		if (lu_index == new_cfg[id].lu_index) {
			req_cfg_desc->unit_cfg[lu_index].bLUEnable = 0x01;
			req_cfg_desc->unit_cfg[lu_index].bBootLunID = new_cfg[id].bootable;
			req_cfg_desc->unit_cfg[lu_index].bLogicalBlockSize = new_cfg[id].log2blksz;
			req_cfg_desc->unit_cfg[lu_index].bMemoryType = new_cfg[id].memory_type;

			if (0xFF == new_cfg[id].lu_context) {
				context = (uint16_t)ufs_info.max_context - assigned_context;
			} else {
				context = new_cfg[id].lu_context;
				assigned_context += context;
			}
			context = cpu_to_be16(context & 0xF);
			req_cfg_desc->unit_cfg[lu_index].wContextCapabilities = context;

			req_cfg_desc->unit_cfg[lu_index].bLUWriteProtect = common_cfg->write_protect;
			req_cfg_desc->unit_cfg[lu_index].bProvisioningType = common_cfg->provisioning_type;
			req_cfg_desc->unit_cfg[lu_index].bDataReliability = common_cfg->data_reliability;

			if (0 == new_cfg[id].blkcnt) {
				au_num = (ufs_info.dev_total_cap / ufs_info.alloc_unit_sz) - assigned_au;
				req_cfg_desc->unit_cfg[lu_index].dNumAllocUnits = cpu_to_be32(au_num);
				debugf("Use all remain space, alloc unit=0x%x, big endian=0x%x\n", au_num, req_cfg_desc->unit_cfg[lu_index].dNumAllocUnits);
			} else {
				au_num = enhance_memory_alloc_unit(new_cfg[id].memory_type, new_cfg[id].blkcnt, new_cfg[id].log2blksz);
				req_cfg_desc->unit_cfg[lu_index].dNumAllocUnits = cpu_to_be32(au_num);
				debugf("Assign space, alloc unit=0x%x, big endian=0x%x\n", au_num, req_cfg_desc->unit_cfg[lu_index].dNumAllocUnits);
			}
		id++;
		}
	}

	return;
}


int set_descriptor_data(struct ufs_cfg_desc_tbl *default_desc, struct lu_specific_cfg_tbl *new_cfg,
		struct lu_common_cfg_tbl *common_cfg)
{
	int ret = 0;
	int retry = 3;
	struct   dwc_ufs_query_upiu *req_upiu;

	do {
		req_upiu = (struct dwc_ufs_query_upiu *)(ufs_info.cmd_desc->command_upiu);
		prepare_write_desc_upiu(req_upiu, default_desc, new_cfg, common_cfg);
		ret = write_read_descriptor(req_upiu);
		if (UFS_SUCCESS != ret)
			reset_and_restore_hc();
		retry--;
	} while (UFS_SUCCESS != ret && retry > 0);

	return ret;
}

int verify_lu_cfg(struct lu_specific_cfg_tbl *lu_cfg)
{
	int ret = 0;
	int loop = 0;
	int multi = 0;
	int boota_occupied = 0;
	int bootb_occupied = 0;
	uint64_t assigned_size = 0;
	uint16_t assigned_context = 0;
	int context_exhaust = 0;

	if (0 == lu_cfg[0].log2blksz)
		return LU_INFO_ILLEGAL;
	
	for (loop = 0; loop < UFS_PLATFORM_LU_NUM; loop++) {
		if (MAIN_BOOT == lu_cfg[loop].bootable) {
			if (1 == boota_occupied)
				return LU_INFO_ILLEGAL;
			else
				boota_occupied = 1;
		}

		if (ALTERNATE_BOOT == lu_cfg[loop].bootable) {
			if (1 == bootb_occupied)
				return LU_INFO_ILLEGAL;
			else
				bootb_occupied = 1;
		}
		
		if (0 == lu_cfg[loop].blkcnt) {
			if (0xFF != lu_cfg[loop].lu_context)
				assigned_context += lu_cfg[loop].lu_context;
			break;
		}
		
		if (loop != 0 && lu_cfg[loop].lu_index <= lu_cfg[loop-1].lu_index)
			return LU_INFO_ILLEGAL;
		
		if (0 == lu_cfg[loop].log2blksz)
			return LU_INFO_ILLEGAL;
		multi = (1 << lu_cfg[loop].log2blksz) / SZ_512;
		assigned_size += lu_cfg[loop].blkcnt * multi;

		if (0xFF != lu_cfg[loop].lu_context)
			assigned_context += lu_cfg[loop].lu_context;
		else
			context_exhaust = 1;

		if (1 == context_exhaust && 0 != lu_cfg[loop].lu_context)
			return LU_INFO_ILLEGAL;
	}

	if (assigned_size > ufs_info.dev_total_cap)
		return LU_INFO_ILLEGAL;

	if (assigned_context > (uint16_t)ufs_info.max_context)
		return LU_INFO_ILLEGAL;
	
	return 0;
}


static void create_cmd_upiu(uint32_t opcode, enum dma_data_direction direction, 
							struct lu_info_tbl *lu_info, void *buf_addr,
							lbaint_t start, lbaint_t blkcnt, uint8_t cmd_set_type)
{
	struct   dwc_ufs_cmd_upiu *cmd_upiu_ptr = NULL;
	uint32_t data_direction = 0;
	uint8_t  upiu_flags = 0;
	uint32_t prdt_buf_size = ufs_info.prdt_entry_size;
	void     *tmp_ptr = NULL;
	uint32_t i = 0;
	uint32_t transfer_size = 0;
	uint8_t  *ptr = NULL;
	lbaint_t size = 0;
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
	cmd_upiu_ptr->lun               = lu_info->lu_index;
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
		size = blkcnt << lu_info->log2blksz;
		get_cmnd(opcode, 0, size, cmd_upiu_ptr->cdb);
		prdt_buf_size = RPMB_FRAME_SIZE;
	} else if (UFS_OP_UNMAP == opcode) {
		list_len = sizeof(struct unmap_para_list);
		get_cmnd(opcode, 0, list_len, cmd_upiu_ptr->cdb);
	} else {
		get_cmnd(opcode, start, blkcnt, cmd_upiu_ptr->cdb);
	}

	if (direction != DMA_NONE) {
		transfer_size = blkcnt << lu_info->log2blksz;
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


int send_scsi_cmd(uint32_t opcode, enum dma_data_direction direction,
						struct lu_info_tbl *lu_info, void *buf_addr,
						lbaint_t start, lbaint_t blkcnt, uint8_t cmd_set_type)
{
	int ret;
	int retry = 4;
	do {
		create_cmd_upiu(opcode, direction, lu_info, buf_addr, start, blkcnt, cmd_set_type);

		ret = wait_for_cmd_completion();
		if (UFS_SUCCESS != ret)
			reset_and_restore_hc();
		else
			ret = handle_scsi_completion();

		retry--;
	} while (UFS_SUCCESS != ret && retry > 0);

	return ret;
}

int send_scsi_cmd_backstage(uint32_t opcode, enum dma_data_direction direction,
						struct lu_info_tbl *lu_info, void *buf_addr,
						lbaint_t start, lbaint_t blkcnt, uint8_t cmd_set_type)
{
	int ret;

	create_cmd_upiu(opcode, direction, lu_info, buf_addr, start, blkcnt, cmd_set_type);

	flush_dcache_all();
	/* Set the doorbell for processing the request */
	ufs_writel(DW_UFS_UTRLDBR, BIT(0));

	return UFS_SUCCESS;
}


int test_unit_ready(struct lu_info_tbl *lu_info)
{
	int ret = 0;
	int retry = 3;
	do {
		ret = send_scsi_cmd(UFS_OP_TEST_UNIT_READY, DMA_NONE, lu_info, NULL, 0, 0, 0);
		retry--;
	} while (UFS_SUCCESS != ret && retry > 0);

	return ret;
}


struct lu_info_tbl *find_lu_info(int lun)
{
	int id = 0;
	for (id = 0; id < UFS_MAX_LU_NUM; id++) {
		if (lun == ufs_info.lu_info[id].lu_index)
			return &ufs_info.lu_info[id];
	}

	return NULL;
}

int ufs_lu_reconstruct(struct lu_specific_cfg_tbl *lu_cfg, struct lu_common_cfg_tbl *common_cfg)
{
	int ret = 0;
	uint8_t val[4] = {0, 0, 0, 0};

	struct ufs_cfg_desc_tbl *cfg_desc;

	ret = verify_lu_cfg(lu_cfg);
	if (LU_INFO_ILLEGAL == ret) {
		errorf("UFS LU configuration table illegal!\n");
		return UFS_INVALID_PARTITIONING;
	}

	/*Enable boot from Boot LU A*/
	val[3] = BOOT_LU_A_ENABLE;
	ret = write_attribute(B_BOOT_LUNEN, val, 0);
	if (UFS_SUCCESS != ret) {
		errorf("Write Attribute bBootLunEn to enable boot from boot LU A fail!ret=%d\n",ret);
		return ret;
	}

	ret = get_descriptor_data((void **)(&cfg_desc), CONFIGURATION_DESC, 0);
	if (UFS_SUCCESS != ret) {
		errorf("UFS get config desc fail!ret=%d\n", ret);
		return ret;
	}

	ret = compare_cfg_lu_table(lu_cfg, common_cfg);
	if (LU_INFO_SAME == ret) {
		debugf("UFS LU configuration table same with device, no need of reconstruction\n");
		return UFS_SUCCESS;
	}

	if (UFS_SUCCESS != check_config_desclock())
		return UFS_CONFIG_DESC_LOCKED;

	ret = set_descriptor_data(cfg_desc, lu_cfg, common_cfg);
	if (UFS_SUCCESS != ret) {
		errorf("UFS set config desc fail!ret=%d\n", ret);
		return ret;
	} else {
		debugf("UFS set config desc success!\n");
	}

/*Be careful to handle this attribute!!!*/
#if 0
	val[3] = LOCK_CONFIGURATION;
	ret = write_attribute(B_CONFIG_DESC_LOCK, val, 0);
	if (UFS_SUCCESS != ret) {
		errorf("UFS lock config desc fail!ret=%d\n",ret);
		return ret;
	}
#endif

/*endpoint reset is not enough, soft reset AON UFS in init_ufs_hostc instead*/
#if 0
	/*TODO for option*/
	//ret = poweron_reset();
	ret = dme_endpoint_reset();
	if (UFS_SUCCESS != ret) {
		errorf("UFS rreset device fail!ret=%d\n",ret);
		return ret;
	}
#endif
	/*init ufs host controller and device again after lu reconstruct*/
	release_desc_mem();
	ufs_init();

	ret = compare_cfg_lu_table(lu_cfg, common_cfg);
	if (LU_INFO_SAME == ret) {
		debugf("LU reconstruct OK!!\n");
		return UFS_SUCCESS;
	} else {
		errorf("LU reconstruct fail, fatal error!!!\n");
		return UFS_FATAL_ERROR;
	}
}


static ulong ufs_bread(int dev_num, lbaint_t start, lbaint_t blkcnt, void *dst)
{
	int ret;
	lbaint_t blocks_todo = blkcnt;
	lbaint_t cur = 0;
	uint32_t max_read_size = 0;
	lbaint_t max_read_blk = 0;
	void * temp_buff;

	struct lu_info_tbl *lu_info = find_lu_info(dev_num);
	if ( NULL == lu_info)
		return 0;

	ret = test_unit_ready(lu_info);
	if (UFS_SUCCESS != ret) {
		errorf("TEST UNIT READY fail!Can not read UFS device\n");
		return 0;
	}

	if (0 != (ulong)dst % 4) {
		errorf("UFS read destination addr not aligned to 4 bytes, it will harm the read efficiency!\n");
		max_read_size = ufs_info.max_prdt_cap > SZ_1M ? SZ_1M : ufs_info.max_prdt_cap;
		max_read_blk = max_read_size >> lu_info->log2blksz;
		/*malloc can guarantee 8 bytes aligned*/
		temp_buff = malloc(max_read_size);
		if (NULL == temp_buff)
			return 0;
		do {
			cur = (blocks_todo > max_read_blk) ? max_read_blk : blocks_todo;
			/* Send Read 10 Command and handle its completion */
			ret = send_scsi_cmd(UFS_OP_READ_10, DMA_FROM_DEVICE, lu_info, temp_buff, start, cur, 0);
			if (ret != UFS_SUCCESS) {
				free(temp_buff);
				return 0;
			}
	
			blocks_todo -= cur;
			start += cur;
			memcpy(dst, temp_buff, cur << lu_info->log2blksz);
			dst += cur << lu_info->log2blksz;
		} while (blocks_todo > 0);
		free(temp_buff);
	} else {
		max_read_blk = ufs_info.max_prdt_cap >> lu_info->log2blksz;
		do {
			cur = (blocks_todo > max_read_blk) ? max_read_blk : blocks_todo;
			/* Send Read 10 Command and handle its completion */
			ret = send_scsi_cmd(UFS_OP_READ_10, DMA_FROM_DEVICE, lu_info, dst, start, cur, 0);
			if (ret != UFS_SUCCESS)
				return 0;
			
			blocks_todo -= cur;
			start += cur;
			dst += cur << lu_info->log2blksz;
		} while (blocks_todo > 0);
	}

	return blkcnt;
}

static ulong ufs_bwrite(int dev_num, lbaint_t start, lbaint_t blkcnt, const void *src)
{
	int ret;
	lbaint_t blocks_todo = blkcnt;
	lbaint_t cur = 0;
	uint32_t max_write_size = 0;
	lbaint_t max_write_blk = 0;
	void * temp_buff;

	struct lu_info_tbl *lu_info = find_lu_info(dev_num);
	if ( NULL == lu_info)
		return 0;

	ret = test_unit_ready(lu_info);
	if (UFS_SUCCESS != ret) {
		errorf("TEST UNIT READY fail!Can not write UFS device\n");
		return 0;
	}
	if (0 != (ulong)src % 4) {
		errorf("UFS write source addr not aligned to 4 bytes, it will harm the write efficiency!\n");
		max_write_size = ufs_info.max_prdt_cap > SZ_1M ? SZ_1M : ufs_info.max_prdt_cap;
		max_write_blk = max_write_size >> lu_info->log2blksz;
		/*malloc can guarantee 8 bytes aligned*/
		temp_buff = malloc(max_write_size);
		if (NULL == temp_buff)
			return 0;
		do {
			cur = (blocks_todo > max_write_blk) ? max_write_blk : blocks_todo;
			memcpy(temp_buff, src, cur << lu_info->log2blksz);
			/* Send Write 10 Command and handle its completion */
			ret = send_scsi_cmd(UFS_OP_WRITE_10, DMA_TO_DEVICE, lu_info, temp_buff, start, cur, 0);
			if (ret != UFS_SUCCESS) {
				free(temp_buff);
				return 0;
			}
	
			blocks_todo -= cur;
			start += cur;
			src += cur << lu_info->log2blksz;
		} while (blocks_todo > 0);
		free(temp_buff);
	} else {
		max_write_blk = ufs_info.max_prdt_cap >> lu_info->log2blksz;
		do {
			cur = (blocks_todo > max_write_blk) ? max_write_blk : blocks_todo;
			/* Send Write 10 Command and handle its completion */
			debugf("write lun(%d), start(0x%x), write_block(0x%x)\n", lu_info->lu_index, start, cur);
			ret = send_scsi_cmd(UFS_OP_WRITE_10, DMA_TO_DEVICE, lu_info, src, start, cur, 0);
			if (ret != UFS_SUCCESS)
				return 0;

			blocks_todo -= cur;
			start += cur;
			src += cur << lu_info->log2blksz;
		} while (blocks_todo > 0);
	}

	return blkcnt;
}

static long ufs_sync(int dev_num)
{
	int ret = 0;

	struct lu_info_tbl *lu_info = find_lu_info(dev_num);
	if (NULL == lu_info)
		return 0;

	ret = test_unit_ready(lu_info);
	if (UFS_SUCCESS != ret) {
		errorf("TEST UNIT READY fail!Can not erase UFS device\n");
		return -1;
	}

	ret = send_scsi_cmd(UFS_OP_SYNCHRONIZE_CACHE_10, DMA_NONE, lu_info, NULL, 0, 0, 0);
	if (ret != UFS_SUCCESS)
		return -1;

	return 0;
}

static ulong ufs_erase(int dev_num, lbaint_t start, lbaint_t blkcnt)
{
	int ret;
	struct unmap_para_list *um_list = NULL;
	struct lu_info_tbl *lu_info = find_lu_info(dev_num);
	if ( NULL == lu_info)
		return 0;

	ret = test_unit_ready(lu_info);
	if (UFS_SUCCESS != ret) {
		errorf("TEST UNIT READY fail!Can not erase UFS device\n");
		return 0;
	}

	if (start % lu_info->erase_block_sz != 0 || blkcnt % lu_info->erase_block_sz != 0)
		debugf("UFS erase area not aligned to dEraseBlockSize, \
		it will harm the erase efficiency, see more in 12.2.3\n");

	um_list = (struct unmap_para_list *)malloc(sizeof(struct unmap_para_list));
	if (NULL == um_list)
		return 0;
	/*TODO, future extension, consider the "MAXIMUM UNMAP BLOCK DESCRIPTOR COUNT" and
		"MAXIMUM UNMAP LBA COUNT" field in VPD page*/
	um_list->um_data_len = cpu_to_be16(sizeof(struct unmap_para_list) - 2);
	um_list->um_block_desc_len = cpu_to_be16(sizeof(struct um_block_descriptor));
	if (8 == sizeof(lbaint_t))
		um_list->ub_desc.um_block_addr = cpu_to_be64(start);
	else
		um_list->ub_desc.um_block_addr = cpu_to_be64((uint64_t)start);
	um_list->ub_desc.um_block_sz = cpu_to_be32((uint32_t)blkcnt);

	debugf("erase lun(%d), start(0x%lx), erase_block(0x%lx)\n", lu_info->lu_index, start, blkcnt);
	ret = send_scsi_cmd(UFS_OP_UNMAP, DMA_TO_DEVICE, lu_info, (void *)um_list, start, blkcnt, 0);
	free(um_list);
	if (ret != UFS_SUCCESS)
		return 0;

	return blkcnt;
}

ulong ufs_write_backstage(int dev_num, lbaint_t start, lbaint_t blkcnt, const void *src)
{
	int ret;
	static int tested = 0;
	lbaint_t max_write_blk = 0;

	/*for disaster recovery*/
	bs_recv.dev = dev_num;
	bs_recv.start = start;
	bs_recv.blkcnt = blkcnt;
	bs_recv.src = src;

	struct lu_info_tbl *lu_info = find_lu_info(dev_num);
	if ( NULL == lu_info)
		return 0;

	max_write_blk = ufs_info.max_prdt_cap >> lu_info->log2blksz;
	if (blkcnt > max_write_blk) {
		errorf("Backstage write block count(0x%lx) can not over the max PRDT capacity(0x%lx)\n",
			blkcnt, max_write_blk);
		return 0;
	}

	/*test unit ready only once in backstage write*/
	if (0 == tested) {
		ret = test_unit_ready(lu_info);
		if (UFS_SUCCESS != ret) {
			errorf("TEST UNIT READY fail!Can not write UFS device\n");
			return 0;
		}
		tested++;
	}

	/* Send Write 10 Command and don't wait for its completion*/
	debugf("backstage write lun(%d), start(0x%lx), write_block(0x%lx), buffer(0x%lx)\n", lu_info->lu_index, start, blkcnt, src);
	ret = send_scsi_cmd_backstage(UFS_OP_WRITE_10, DMA_TO_DEVICE, lu_info, src, start, blkcnt, 0);
	if (ret != UFS_SUCCESS)
		return 0;

	return blkcnt;
}

ulong ufs_query_backstage(int dev_num, lbaint_t blkcnt, const void *src)
{
	int ret = 0;

	bs_recv.dev = dev_num;
	ret = wait_for_previous_scsi_completion();
	if (UFS_SUCCESS != ret)
		reset_and_restore_hc();
	else
		ret = handle_scsi_completion();
	if (UFS_SUCCESS != ret) {
		/*if backstage write fail, try normal write*/
		return ufs_bwrite(bs_recv.dev, bs_recv.start, bs_recv.blkcnt, bs_recv.src);
	}

	return blkcnt;
}


void ufs_register_blk_device(int lun_index, uint32_t log2_blk_sz, uint64_t blk_count, enum lu_bootable type)
{
	ufs_info.block_dev[lun_index].if_type = IF_TYPE_UFS;
	ufs_info.block_dev[lun_index].dev = lun_index;  /*consider each lun as one block device*/
	if (NONE_BOOT == type)
		ufs_info.block_dev[lun_index].part_type = PART_TYPE_EFI;
	else
		ufs_info.block_dev[lun_index].part_type = PART_TYPE_UNKNOWN;
	ufs_info.block_dev[lun_index].target = 0xFF;
	ufs_info.block_dev[lun_index].lun = lun_index;
	ufs_info.block_dev[lun_index].type = DEV_TYPE_UNKNOWN;
	ufs_info.block_dev[lun_index].removable = 1;
	ufs_info.block_dev[lun_index].lba = blk_count;
	ufs_info.block_dev[lun_index].blksz = 1 << log2_blk_sz;
	ufs_info.block_dev[lun_index].log2blksz = log2_blk_sz;
	ufs_info.block_dev[lun_index].block_read = ufs_bread;
	ufs_info.block_dev[lun_index].block_write = ufs_bwrite;
	ufs_info.block_dev[lun_index].block_erase = ufs_erase;
	ufs_info.block_dev[lun_index].block_sync = ufs_sync;

	if (NONE_BOOT == type) {
	ufs_info.block_dev[lun_index].backstage_block_write = ufs_write_backstage;
	ufs_info.block_dev[lun_index].backstage_write_query = ufs_query_backstage;
	}
	return;
}

int ufs_update_native(void)
{
	int lun_index = 0;
	int ret = 0;
	int id = 0;
	uint64_t block_count = 0;
	uint32_t segment_size = 0;
	struct ufs_dev_desc_tbl *main_desc;
	struct ufs_geo_desc_tbl *geo_desc;
	struct ufs_unit_desc_tbl *unit_desc;

	ufs_info.prdt_entry_size = PRDT_BUFFER_SIZE;
	ufs_info.max_prdt_cap =  TOTAL_PRDT_CAP;
	ret = get_descriptor_data((void **)(&main_desc), DEVICE_DESC, 0);
	if (UFS_SUCCESS != ret) {
		errorf("get device descriptor data fail!\n");
		return;
	}
	ufs_info.unit_offset = main_desc->bUD0BaseOffset;
	ufs_info.unit_length = main_desc->bUDConfigPLength;
	ufs_info.lu_num = main_desc->bNumberLU;
	ufs_info.wlu_num = main_desc->bNumberWLU;
	ufs_info.boot_enable = main_desc->bBootEnable;
	ufs_info.wSpecVersion = be16_to_cpu(main_desc->wSpecVersion);

	ret = get_descriptor_data((void **)(&geo_desc), GEOMETRY_DESC, 0);
	if (UFS_SUCCESS != ret) {
		errorf("get geometry descriptor data fail!\n");
		return;
	}

	segment_size = be32_to_cpu(geo_desc->dSegmentSize);
	ufs_info.alloc_unit_sz = geo_desc->bAllocationUnitSize * segment_size;
	ufs_info.dev_total_cap = be64_to_cpu(geo_desc->qTotalRawDeviceCapacity);
	ufs_info.max_context = geo_desc->bMaxContexIDNumber;
	ufs_info.bootAdjFac = be16_to_cpu(geo_desc->wEnhanced1CapAdjFac) / SZ_256;
	debugf("UFS device total cap=0x%llx,allocation unit size=0x%x\n", ufs_info.dev_total_cap, ufs_info.alloc_unit_sz);

	for (lun_index = 0; lun_index < UFS_MAX_LU_NUM; lun_index++)	{
		memset(&ufs_info.block_dev[lun_index], 0 ,sizeof(block_dev_desc_t));
		memset(&ufs_info.lu_info[lun_index], 0 ,sizeof(struct lu_info_tbl));
		ret = get_descriptor_data((void **)(&unit_desc), UNIT_DESC, lun_index);
		if (UFS_SUCCESS != ret)
			continue;

		block_count = be64_to_cpu(unit_desc->qLogicalBlockCount);
		if (0 != block_count) {
			ufs_info.lu_info[id].lu_index = lun_index;
			ufs_info.lu_info[id].blkcnt = block_count;
			ufs_info.lu_info[id].log2blksz = unit_desc->bLogicalBlockSize;
			ufs_info.lu_info[id].memory_type = unit_desc->bMemoryType;
			ufs_info.lu_info[id].bootable = unit_desc->bBootLunID;
			ufs_info.lu_info[id].write_protect = unit_desc->bLUWriteProtect;
			ufs_info.lu_info[id].provisioning_type = unit_desc->bProvisioningType;
			ufs_info.lu_info[id].data_reliability = unit_desc->bDataReliability;
			ufs_info.lu_info[id].erase_block_sz = be32_to_cpu(unit_desc->dEraseBlockSize);
			ufs_info.lu_info[id].lu_context = be16_to_cpu(unit_desc->wContextCapabilities) & 0xF;
			id++;
			ufs_register_blk_device(lun_index, unit_desc->bLogicalBlockSize, block_count, unit_desc->bBootLunID);
		}

	}
	ret = ufs_lu_reconstruct(factory_lu_tbl, &lu_common_tbl);
	if (UFS_SUCCESS != ret)
		return -1;
	return 0;
}

int get_lun_by_bootable(enum lu_bootable target)
{
	int id = 0;
	for (id = 0; id < UFS_MAX_LU_NUM; id++) {
		if (0 == factory_lu_tbl[id].log2blksz)
			break;
		/*TODO, only support single user lu now*/
		if (factory_lu_tbl[id].bootable == target)
			return factory_lu_tbl[id].lu_index;
	}
	return -1;
}

block_dev_desc_t *ufs_get_dev(int dev)
{
	if (dev >= UFS_MAX_DEV_NUM) {
		errorf("Required UFS device id exceed the max ufs device number(%d)\n", UFS_MAX_DEV_NUM);
		return NULL;
	}
	if (IF_TYPE_UFS == ufs_info.block_dev[dev].if_type) {
		return &ufs_info.block_dev[dev];
	}

	errorf("CANNOT find UFS device %d\n", dev);
	return NULL;
}

int ufs_get_dev_id(int bootable_part)
{
	int id = 0;

	for (id = 0; id < UFS_MAX_LU_NUM; id++) {
		if (0 == factory_lu_tbl[id].log2blksz)
			break;
		if (factory_lu_tbl[id].bootable == bootable_part)
			return factory_lu_tbl[id].lu_index;
	}
	return -1;
}

u64 ufs_get_hwpartsize(int bootable_part)
{
	int id = 0;
	int lu_index;

	for (id = 0; id < UFS_MAX_LU_NUM; id++) {
		if (0 == factory_lu_tbl[id].log2blksz)
			break;
		if (factory_lu_tbl[id].bootable == bootable_part)
			lu_index = factory_lu_tbl[id].lu_index;
	}

	if (IF_TYPE_UFS == ufs_info.block_dev[lu_index].if_type) {
		return ufs_info.block_dev[lu_index].lba * ufs_info.block_dev[lu_index].blksz;
	}

}

