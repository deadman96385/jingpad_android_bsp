/*
 * UFS host controller driver for SPL.
 *
 * Copyright (C) 2016 Spreadtrum Communications, Inc.
 *
 * Authors:
 *	Wang Ding <justin.wang@spreadtrum.com>
 *
 */

#include <asm/types.h>
#include <common.h>
#include <linux/types.h>
#include <part.h>
#include <sci_types.h>
#include <asm/arch/sprd_reg.h>
#include <asm/io.h>
#include "ufs_hal.h"
#include "simfd_ufshcd.h"
#include "simfd_ufs.h"

#define UFS_SPL_DEBUG
#define UFSHCI_BASE_ADDR SPRD_UFS_HCI_PHYS

static struct ufs_hinfo ufshcd;
static struct ufshci_utrd utrd __attribute__((aligned(1024)));
static struct ufshci_utmd utmd __attribute__((aligned(1024)));
static struct ufshci_ucd ucd __attribute__((aligned(128)));
block_dev_desc_t sprd_ufs_dev;


#define UPIU_HEADER_DWORD(byte3, byte2, byte1, byte0)\
			cpu_to_be32((byte3 << 24) | (byte2 << 16) |\
			 (byte1 << 8) | (byte0))
#define memset sprd_memset

#ifdef UFS_SPL_DEBUG
#define MAX_DBG_BUF 512
static char ufs_dbg_buf[MAX_DBG_BUF];

static u32 strlen(const char * s)
{
	const char *sc;

	for (sc = s; *sc != '\0'; ++sc)
		/* nothing */;
	return sc - s;
}

static char * strcat(char * dest, const char * src)
{
	char *tmp = dest;

	while (*dest)
		dest++;
	while ((*dest++ = *src++) != '\0')
		;

	return tmp;
}

static void ufs_spl_dbg_p4(const char *func, const char *p1,
						const char *p2, const char *p3)
{
	char *buf = ufs_dbg_buf;

	if (!func) func = ""; if (!p1) p1 = "";
	if (!p2) p2 = ""; if (!p3) p3 = "";

	if ((strlen(buf)+ strlen(p1) + strlen(p2) +
			strlen(p3) + strlen(func) + 6) >= MAX_DBG_BUF)
		buf[0] = 0;

	strcat(buf, "##");	strcat(buf, func);	strcat(buf, " ");
	strcat(buf, p1);	strcat(buf, " ");	strcat(buf, p2);
	strcat(buf, " ");	strcat(buf, p3);	strcat(buf, "##");
}
#else
#define ufs_spl_dbg_p4(p1, p2, p3, p4)
#endif

#define UFS_BUG() do { \
	ufs_spl_dbg_p4(__func__, ": BUG !!!", "", ""); \
	do {} while (1); \
} while (0)

block_dev_desc_t *ufs_get_dev()
{
	return ((block_dev_desc_t *) & sprd_ufs_dev);
}


static void ufs_mphy_config(void)
{
	//TODO:
}

static int ufs_send_uic_cmd(struct ufs_hinfo *h,
						struct ufshci_uic_cmd *uic_cmd)
{
	int ret;
	u32 intr_status, enabled_intr_status;

	udelay(1);

	ret = ufs_readl(h->mmio_base, REG_CONTROLLER_STATUS) &
				UIC_COMMAND_READY;
	if (!ret)
		return -1;

	ufs_writel(h->mmio_base, uic_cmd->arg1,
		REG_UIC_COMMAND_ARG_1);
	ufs_writel(h->mmio_base, uic_cmd->arg2,
		REG_UIC_COMMAND_ARG_2);
	ufs_writel(h->mmio_base, uic_cmd->arg3,
		REG_UIC_COMMAND_ARG_3);

	ufs_writel(h->mmio_base, uic_cmd->cmd & COMMAND_OPCODE_MASK,
		REG_UIC_COMMAND);

	return 0;
}

static int ufs_wait_uic_cmd_done(struct ufs_hinfo *h)
{
	int retry = RETRY_CNT;

	do {
		if((ufs_readl(h->mmio_base, REG_INTERRUPT_STATUS) &
				UIC_COMMAND_COMPL)) {
			ufs_writel(h->mmio_base, UIC_COMMAND_COMPL,
				REG_INTERRUPT_STATUS);
			break;
		}
		udelay(10);
	} while (--retry);

	if (!retry)
		return -1;
	else
		return 0;
}

static inline int ufs_uic_linkstartup_check(struct ufs_hinfo *h)
{
	return ufs_readl(h->mmio_base, REG_UIC_COMMAND_ARG_2) & 0xFF;
}

static int ufs_link_startup(struct ufs_hinfo *h)
{
	int ret = -1;
	int retry = DME_LINKSTARTUP_RETRIES;
	struct ufshci_uic_cmd uic_cmd = {0};

	uic_cmd.cmd = UIC_CMD_DME_LINK_STARTUP;

	do {
		if(!ufs_send_uic_cmd(h, &uic_cmd) &&
			!ufs_wait_uic_cmd_done(h) &&
			!ufs_uic_linkstartup_check(h))
			ret = 0;

		if (!ret && !((ufs_readl(h->mmio_base, REG_CONTROLLER_STATUS) &
						DEVICE_PRESENT) ? 1 : 0)) {
			ufs_spl_dbg_p4(__func__,"ufs device not present!","","");
			ret = -1;
		}
	} while (ret && retry--);

	return ret;
}

static int ufs_setup_power(struct ufs_hinfo *h)
{
	//TODO:
}

static int ufs_setup_clock(struct ufs_hinfo *h)
{
	//TODO:
}

static int ufs_hc_reset(struct ufs_hinfo *h)
{
	int retry = 1000;

	ufs_writel(h->mmio_base, CONTROLLER_DISABLE,
		REG_CONTROLLER_ENABLE);
	udelay(2);
	ufs_writel(h->mmio_base, CONTROLLER_ENABLE,
		REG_CONTROLLER_ENABLE);
	udelay(2);

	while(!ufs_readl(h->mmio_base, REG_CONTROLLER_ENABLE)) {
		if (retry--)
			udelay(1);
		else
			return -1;
	}

	return 0;
}

static inline int ufs_get_tr_ocs(struct ufshci_utrd *utrd)
{
	return le32_to_cpu(utrd->header.dw2) & MASK_OCS;
}

static int ufs_try_nop_out(struct ufs_hinfo *h)
{
	struct ufshci_utrd *utrd = h->utrdl;
	struct ufshci_ucd *ucd = h->ucdl;
	struct ufs_upiu_hd *upiu_hd;
	u16 rep_upiu_off, prdt_off;
	u32 retry = 2000;
	u32 dw;
	int ret;

	rep_upiu_off = offsetof(struct ufshci_ucd, rsp_upiu);
	prdt_off = offsetof(struct ufshci_ucd, sglist);

	memset(utrd, 0, sizeof(struct ufshci_utrd));
	dw = (0x1 << UTRD_COMMAND_TYPE_OFFSET) | UFS_BIT(24);
	utrd->header.dw0 = cpu_to_le32(dw);
	utrd->header.dw2 = cpu_to_le32(OCS_INVALID_COMMAND_STATUS);
	utrd->ucd_ba = cpu_to_le32(LOWER_32_BITS((ulong)(ucd))); //TODO: align needed
	utrd->ucd_bau = cpu_to_le32(UPPER_32_BITS((ulong)(ucd)));
	utrd->rep_upiu_off = cpu_to_le16(rep_upiu_off >> 0x2);
	utrd->rsp_upiu_len = cpu_to_le16(32 >> 0x2);
	//utrd->rsp_upiu_len = cpu_to_le16((uint16_t)(sizeof(struct dwc_ufs_xfer_resp_upiu) >> 2));
	utrd->prdt_off = cpu_to_le16(prdt_off >> 0x2);
	utrd->prdt_len = 0x0;

	memset(ucd, 0x0, sizeof(struct ufshci_ucd));
	upiu_hd = (struct ufshci_ucd *)ucd->cmd_upiu;
	upiu_hd->dw0 = UPIU_HEADER_DWORD(0x0, 0x0, 0x0, 0x1);
	ufs_writel(h->mmio_base, UFS_BIT(0),
			REG_UTP_TRANSFER_REQ_DOOR_BELL);
	udelay(10);

	do {
		if ((ufs_readl(h->mmio_base, REG_INTERRUPT_STATUS) &
			UTP_TRANSFER_REQ_COMPL) &&
			(ufs_readl(h->mmio_base, REG_UTP_TRANSFER_REQ_DOOR_BELL) &
					UFS_BIT(0)) == 0) {
			ufs_writel(h->mmio_base, UTP_TRANSFER_REQ_COMPL,
					REG_INTERRUPT_STATUS);
			break;
		}

		if (retry-- == 0) {
			ufs_writel(h->mmio_base, ~(u32)UFS_BIT(0),
					REG_UTP_TRANSFER_REQ_LIST_CLEAR);
			return -1;
		}

		udelay(10);
	} while(1);

	ret = ufs_get_tr_ocs(utrd);
	if (ret != OCS_SUCCESS) {
		//TODO: step forward or just reset?
		return -1;
	}

	return 0;
}

static int ufs_device_connection_check(struct ufs_hinfo *h)
{
	int ret = 0;
	int retry;

	for (retry = NOP_OUT_RETRIES; retry > 0; retry--) {
		ret = ufs_try_nop_out(h);

		if (!ret)
			break;
	}

	return ret;
}

static int ufs_exec_tr(struct ufs_hinfo *h)
{
	u32 retry = 2000;
	int ret;

	ufs_writel(h->mmio_base, UFS_BIT(0),
			REG_UTP_TRANSFER_REQ_DOOR_BELL);

	do {
		udelay(100);
		ret = ufs_readl(h->mmio_base, REG_INTERRUPT_STATUS);
		if (0 != ret)
			ufs_writel(h->mmio_base, ret, REG_INTERRUPT_STATUS);
		if (0 == (ufs_readl(h->mmio_base, REG_UTP_TRANSFER_REQ_DOOR_BELL) & UFS_BIT(0)))
			break;

		if (retry-- == 0) {
			ufs_writel(h->mmio_base, ~(u32)UFS_BIT(0),
					REG_UTP_TRANSFER_REQ_LIST_CLEAR);
			return FALSE;
		}

	} while(1);

	ret = ufs_get_tr_ocs(h->utrdl);
	if (ret != OCS_SUCCESS) {
		//TODO: step forward or just reset?
		return FALSE;
	}

	return TRUE;
}

static void ufs_init_query_tr(struct ufs_hinfo *h,
		u8 opcode, u8 query_func, u8 idn, u8 index, u8 selector)
{
	struct ufshci_utrd *utrd = h->utrdl;
	struct ufshci_ucd *ucd = h->ucdl;
	struct ufs_query_req_rsp_upiu *qr_upiu;
	u16 rep_upiu_off, prdt_off;
	u32 dw;
	int ret;

	rep_upiu_off = offsetof(struct ufshci_ucd, rsp_upiu);
	prdt_off = offsetof(struct ufshci_ucd, sglist);

	memset(utrd, 0, sizeof(struct ufshci_utrd));
	dw = (0x1 << UTRD_COMMAND_TYPE_OFFSET) | UFS_BIT(24);
	utrd->header.dw0 = cpu_to_le32(dw);
	utrd->header.dw2 = cpu_to_le32(OCS_INVALID_COMMAND_STATUS);
	utrd->ucd_ba = cpu_to_le32(LOWER_32_BITS((ulong)(h->ucdl))); //TODO: align needed
	utrd->ucd_bau = cpu_to_le32(UPPER_32_BITS((ulong)(h->ucdl)));
	utrd->rep_upiu_off = cpu_to_le16(rep_upiu_off >> 0x2);
	utrd->rsp_upiu_len = cpu_to_le16(ALIGNED_UPIU_SIZE >> 0x2);
	utrd->prdt_off = cpu_to_le16(prdt_off >> 0x2);
	utrd->prdt_len = 0x0;

	memset(ucd, 0x0, sizeof(struct ufshci_ucd));
	qr_upiu = (struct ufs_query_req_rsp_upiu *)ucd->cmd_upiu;
	qr_upiu->header.dw0 =
			UPIU_HEADER_DWORD(UPIU_TRANSACTION_QUERY_REQ, 0x0, 0x0, 0x1);
	qr_upiu->header.dw1 =
			UPIU_HEADER_DWORD(0x0, query_func, 0x0, 0x0);
	qr_upiu->header.dw2 =
			UPIU_HEADER_DWORD(0x0, 0x0, 0x0, 0x0);
	qr_upiu->req_rdflag.opcode = opcode;
	qr_upiu->req_rdflag.idn = idn;
	qr_upiu->req_rdflag.index = index;
	qr_upiu->req_rdflag.selector = selector;

	return;
}

static int ufs_query_flag(struct ufs_hinfo *h, u8 opcode,
			u8 query_func, u8 idn, u8 *flag_res)
{
	struct ufs_query_req_rsp_upiu *rsp;
	int ret, index = 0, selector = 0;

	rsp = (struct ufs_query_req_rsp_upiu *)h->ucdl->rsp_upiu;

	ufs_init_query_tr(h, opcode, query_func, idn, index, selector);

	ret = ufs_exec_tr(h);

	if (ret && flag_res)
		*flag_res = rsp->rsp_rdflag.value & 0x1;

	return ret;
}

static int ufs_query_flag_retry(struct ufs_hinfo *h, u8 opcode,
	u8 query_func, u8 idn, u8 *flag_res)
{
	int ret;
	int retries;

	for (retries = 0; retries < QUERY_REQ_RETRIES; retries++) {
		ret = ufs_query_flag(h, opcode, query_func, idn, flag_res);
		if (!ret)
			ufs_spl_dbg_p4(__func__,
				"query flag failed ++","", "");
		else
			break;
	}

	if (!ret)
		ufs_spl_dbg_p4(__func__,
			":query flag failed after Max retires", "", "");
	return ret;
}

static int ufs_verify_dev_init(struct ufs_hinfo *h)
{
	int i, ret;
	u8 flag_res = 1;

	ret = ufs_query_flag_retry(h, 0x6, 0x81, 0x1, NULL);
	if (!ret) {
		ufs_spl_dbg_p4(__func__,
			"Set fDeviceInit flag failed", "", "");
		goto out;
	}

	for (i = 0; i < 1000 && !ret && flag_res; i++)
		ret = ufs_query_flag_retry(h, 0x5, 0x1, 0x1, &flag_res);

	if (!ret)
		ufs_spl_dbg_p4(__func__,
			"Read fDeviceInit flag failed", "", "");
	else if (flag_res)
		ufs_spl_dbg_p4(__func__,
			"fDeviceInit was not cleared by the device\n", "", "");

out:
	return ret || flag_res;
}
static void ufs_test_unit_ready(struct ufs_hinfo *h,u8 lun)
{
	struct ufshci_utrd *utrd = h->utrdl;
	struct ufshci_ucd *ucd = h->ucdl;
	struct ufs_cmd_req_upiu *req_upiu;
	struct ufs_upiu_hd *upiu_hd;
	u16 rep_upiu_off, prdt_off;
	u32 dw;
	int ret;
	u32 retry = 2000;


	rep_upiu_off = offsetof(struct ufshci_ucd, rsp_upiu);
	prdt_off = offsetof(struct ufshci_ucd, sglist);

	memset(utrd, 0, sizeof(struct ufshci_utrd));
	dw = (0x1 << UTRD_COMMAND_TYPE_OFFSET) | UFS_BIT(24);
	utrd->header.dw0 = cpu_to_le32(dw);
	utrd->header.dw2 = cpu_to_le32(OCS_INVALID_COMMAND_STATUS);
	utrd->ucd_ba = cpu_to_le32(LOWER_32_BITS((ulong)(ucd))); //TODO: align needed
	utrd->ucd_bau = cpu_to_le32(UPPER_32_BITS((ulong)(ucd)));
	utrd->rep_upiu_off = cpu_to_le16(rep_upiu_off >> 0x2);
	utrd->rsp_upiu_len = cpu_to_le16(ALIGNED_UPIU_SIZE >> 0x2);
	utrd->prdt_off = cpu_to_le16(prdt_off >> 0x2);
	utrd->prdt_len = 0x0;

	memset(ucd, 0x0, sizeof(struct ufshci_ucd));
	req_upiu = (struct ufs_query_req_rsp_upiu *)ucd->cmd_upiu;
	upiu_hd = (struct ufshci_ucd *)ucd->cmd_upiu;
	req_upiu->header.dw0 =
			UPIU_HEADER_DWORD(UPIU_TRANSACTION_COMMAND, 0, lun, 0x1);
	req_upiu->header.dw1 =
				UPIU_HEADER_DWORD(UPIU_COMMAND_SET_TYPE_SCSI, 0x0, 0x0, 0x0);
	req_upiu->header.dw2 =
				UPIU_HEADER_DWORD(0x0, 0x0, 0x0, 0x0);

	ufs_writel(h->mmio_base, UFS_BIT(0),
			REG_UTP_TRANSFER_REQ_DOOR_BELL);
	udelay(10);

	do {
		if ((ufs_readl(h->mmio_base, REG_INTERRUPT_STATUS) &
			UTP_TRANSFER_REQ_COMPL) &&
			(ufs_readl(h->mmio_base, REG_UTP_TRANSFER_REQ_DOOR_BELL) &
					UFS_BIT(0)) == 0) {
			ufs_writel(h->mmio_base, UTP_TRANSFER_REQ_COMPL, 
					REG_INTERRUPT_STATUS);
			break;
		}
	
		if (retry-- == 0) {
			ufs_writel(h->mmio_base, ~(u32)UFS_BIT(0),
					REG_UTP_TRANSFER_REQ_LIST_CLEAR);
			return -1;
		}

		udelay(10);
	} while(1);

	ret = ufs_get_tr_ocs(utrd);
	if (ret != OCS_SUCCESS) {
		//TODO: step forward or just reset?
		return -1;
	}

	return 0;
}
static void ufs_init_scsi_read_tr(struct ufs_hinfo *h,
		int lun, ulong start_lba, ulong lb_num, void *buf)
{
	struct ufshci_utrd *utrd = h->utrdl;
	struct ufshci_ucd *ucd = h->ucdl;
	struct ufshci_prdt *prdt;
	struct ufs_cmd_req_upiu *req_upiu;
	u16 rep_upiu_off, prdt_off;
	u32 dw;
	int ret, i, rq_sz;

	rep_upiu_off = offsetof(struct ufshci_ucd, rsp_upiu);
	prdt_off = offsetof(struct ufshci_ucd, sglist);

	memset(utrd, 0, sizeof(struct ufshci_utrd));
	dw = (0x1 << UTRD_COMMAND_TYPE_OFFSET) | UFS_BIT(26);
	utrd->header.dw0 = cpu_to_le32(dw);
	utrd->header.dw2 = cpu_to_le32(OCS_INVALID_COMMAND_STATUS);
	utrd->ucd_ba = cpu_to_le32(LOWER_32_BITS((ulong)h->ucdl)); //TODO: align needed
	utrd->ucd_bau = cpu_to_le32(UPPER_32_BITS((ulong)h->ucdl));
	utrd->rep_upiu_off = cpu_to_le16(rep_upiu_off >> 0x2);
	utrd->rsp_upiu_len = cpu_to_le16(52 >> 0x2);
	utrd->prdt_off = cpu_to_le16(prdt_off >> 0x2);
	rq_sz = lb_num*LOGICAL_BLK_SIZE;
	utrd->prdt_len = cpu_to_le16((u16)((rq_sz & (MAX_PRDT_BUFFER_SIZE - 1)) ?
					((rq_sz/MAX_PRDT_BUFFER_SIZE) + 1) :
					(rq_sz/MAX_PRDT_BUFFER_SIZE)));

	/* Check whether request size is larger than 16*256K */
	if (utrd->prdt_len > MAX_PRDT_ENTRY)
		UFS_BUG();// Hungup

	memset(ucd, 0x0, sizeof(struct ufshci_ucd));
	req_upiu = (struct ufs_query_req_rsp_upiu *)ucd->cmd_upiu;
	req_upiu->header.dw0 =
			UPIU_HEADER_DWORD(UPIU_TRANSACTION_COMMAND, UPIU_CMD_FLAGS_READ, lun, 0x1);
	req_upiu->header.dw1 =
			UPIU_HEADER_DWORD(UPIU_COMMAND_SET_TYPE_SCSI, 0x0, 0x0, 0x0);
	req_upiu->header.dw2 =
			UPIU_HEADER_DWORD(0x0, 0x0, 0x0, 0x0);
	req_upiu->exp_data_transfer_len = cpu_to_be32(lb_num * LOGICAL_BLK_SIZE); //TODO: blk size should read from device
	req_upiu->cdb[0] = 0x28; //scsi read 10
	req_upiu->cdb[1] = 0x0;
	req_upiu->cdb[2] = (u8)((start_lba & 0xff000000) >> 24); /* MSB */
	req_upiu->cdb[3] = (u8)((start_lba & 0x00ff0000) >> 16);
	req_upiu->cdb[4] = (u8)((start_lba & 0x0000ff00) >> 8);
	req_upiu->cdb[5] = (u8)(start_lba & 0x000000ff); /* LSB */
	req_upiu->cdb[6] = 0x0;
	req_upiu->cdb[7] = (u8)((lb_num >> 8) & 0xff); /* MSB */
	req_upiu->cdb[8] = (u8)((lb_num) & 0xff); /* LSB */
	req_upiu->cdb[9] = 0x0;

	for (i=0; i<utrd->prdt_len; i++) {
		prdt = &ucd->sglist[i];
		prdt->base =
			cpu_to_le32(LOWER_32_BITS((ulong)(buf + i * MAX_PRDT_BUFFER_SIZE)));
		prdt->upper =
			cpu_to_le32(UPPER_32_BITS((ulong)(buf + i * MAX_PRDT_BUFFER_SIZE)));
		prdt->resv = 0x0;
		prdt->size =
			(rq_sz > MAX_PRDT_BUFFER_SIZE) ? cpu_to_le32(MAX_PRDT_BUFFER_SIZE - 1) :
						cpu_to_le32(rq_sz - 1);

		if(rq_sz > MAX_PRDT_BUFFER_SIZE)
			rq_sz -= MAX_PRDT_BUFFER_SIZE;
		else
			rq_sz = 0;
	}

	return;
}

int ufs_lu_read(int lun, ulong start_lba, ulong lb_num, void *buf)
{
	int ret;
	int retry = 3;
	struct ufs_hinfo *h = &ufshcd;

	ufs_test_unit_ready(h,lun);

retry:
	ufs_init_scsi_read_tr(h, lun, start_lba, lb_num, buf);

	ret = ufs_exec_tr(h);
	if (!ret && retry--)
		goto retry;

	return ret;
}

void sprd_ufs_block_dev_config()
{	sprd_ufs_dev.part_type = PART_TYPE_EFI;
	sprd_ufs_dev.dev = 2;
	sprd_ufs_dev.blksz = UFS_SECTOR_SIZE;
	sprd_ufs_dev.block_read = ufs_lu_read;
}

void enable_apb_aon_ufs(void)
{
	uint32_t temp = 0;

	temp = readl((void *)REG_AP_APB_APB_EB1);
	temp |= BIT_AP_APB_UFS_UTP_EB | BIT_AP_APB_UFS_HCI_EB |
				BIT_AP_APB_UFS_UNIPRO_EB | BIT_AP_APB_UFS_EB;
	writel(temp, (void *)REG_AP_APB_APB_EB1);

	temp = readl((void *)REG_AON_APB_APB_EB1);
	temp |= BIT_AON_APB_UFS_AO_EB;
	writel(temp, (void *)REG_AON_APB_APB_EB1);

	return;
}


void soft_reset_apb_ufs()
{
	uint32_t temp = 0;
	uint32_t temp1 = 0;

	temp = readl((void *)REG_AP_APB_APB_RST);
	temp1 = temp |BIT_AP_APB_UFS_UTP_SOFT_RST | BIT_AP_APB_UFS_HCI_SOFT_RST | BIT_AP_APB_UFS_UNIPRO_SOFT_RST | BIT_AP_APB_UFS_SOFT_RST;
	writel(temp1, (void *)REG_AP_APB_APB_RST);
	udelay(1000);
	writel(temp, (void *)REG_AP_APB_APB_RST);

	return;
}

void dme_set(struct ufs_hinfo *h, uint32_t mib, uint32_t value)
{
	mib = (mib << 16) | ((mib >> 16) & 0x0000FFFF);

	struct ufshci_uic_cmd uic_cmd = {0};

	uic_cmd.cmd = UIC_CMD_DME_SET;
	uic_cmd.arg1 = mib;
	uic_cmd.arg2 = 0;
	uic_cmd.arg3 = value;

	ufs_send_uic_cmd(h, &uic_cmd);
	ufs_wait_uic_cmd_done(h);

	/*return with no error*/
	return;
}

uint32_t dme_peer_get(struct ufs_hinfo *h, uint32_t mib)
{
	mib = (mib << 16) | ((mib >> 16) & 0x0000FFFF);

	struct ufshci_uic_cmd uic_cmd = {0};
	uic_cmd.cmd = UIC_CMD_DME_PEER_GET;
	uic_cmd.arg1 = mib;
	uic_cmd.arg2 = 0;
	uic_cmd.arg3 = 0;

	ufs_send_uic_cmd(h, &uic_cmd);
	ufs_wait_uic_cmd_done(h);

	return ufs_readl(h->mmio_base, REG_UIC_COMMAND_ARG_3);
}

void change_ufs_power_mode(struct ufs_hinfo *h)
{
	int ret = 0;
	int retry = 100;
	uint32_t upms_intr_res = 0;
	struct ufs_pa_layer_attr pwr_info;

	pwr_info.pwr_rx = FAST_MODE;
	pwr_info.pwr_tx = FAST_MODE;
	pwr_info.hs_rate = PA_HS_MODE_B;

	/*Get max power mode*/
	pwr_info.lane_rx = 1;
	pwr_info.lane_tx = 1;


	pwr_info.gear_rx = 3;

	pwr_info.gear_tx = 3;

	/*Set power mode*/
	dme_set(h, PA_TXGEAR, pwr_info.gear_tx);
	dme_set(h, PA_RXGEAR, pwr_info.gear_rx);

	if (pwr_info.pwr_rx == FASTAUTO_MODE ||
	    pwr_info.pwr_tx == FASTAUTO_MODE ||
	    pwr_info.pwr_rx == FAST_MODE ||
	    pwr_info.pwr_tx == FAST_MODE)
		dme_set(h, PA_HSSERIES, pwr_info.hs_rate);

	dme_set(h, PA_ACTIVETXDATALANES, pwr_info.lane_tx);
	dme_set(h, PA_ACTIVERXDATALANES, pwr_info.lane_rx);


	if (FASTAUTO_MODE == pwr_info.pwr_tx || FAST_MODE == pwr_info.pwr_tx)
		dme_set(h, PA_TXTERMINATION, 1);
	else
		dme_set(h, PA_TXTERMINATION, 0);

	if (FASTAUTO_MODE == pwr_info.pwr_rx ||FAST_MODE == pwr_info.pwr_rx)
		dme_set(h, PA_RXTERMINATION, 1);
	else
		dme_set(h, PA_RXTERMINATION, 0);

	dme_set(h, PA_PWRMODE, (pwr_info.pwr_rx << 4) | pwr_info.pwr_tx);

	/*check set power mode result*/
	while(retry > 0) {
		upms_intr_res = ufs_readl(h->mmio_base, 0x20) & DW_UFS_IS_UPMS;
		if (upms_intr_res) {
			ufs_writel(h->mmio_base, upms_intr_res, 0x20);
			break;
		}
		udelay(100);
		retry--;
	}

	if (0 == retry)
		return;

	ret = (ufs_readl(h->mmio_base, 0x30) >> 8) & 0x7;
	if (1 != ret)
		return;

	//ret = dme_peer_get(PA_PWRMODE);


	return;
}

int ufs_init(void)
{
	int ret;
	u32 temp;
	struct ufs_hinfo *host = &ufshcd;

	host->mmio_base = UFSHCI_BASE_ADDR;
	host->utrdl = &utrd;
	host->utmrdl = &utmd;
	host->ucdl = &ucd;

	ufs_setup_power(host);
	ufs_setup_clock(host);

	enable_apb_aon_ufs();
	soft_reset_apb_ufs();
	ufs_mphy_config();

retry:

	if (ufs_hc_reset(host)) {
		goto retry;
	}

	ufs_writel(host->mmio_base,
			ufs_readl(host->mmio_base, REG_INTERRUPT_STATUS),
			REG_INTERRUPT_STATUS);
	ufs_writel(host->mmio_base, 0, REG_INTERRUPT_ENABLE);


	ret = ufs_link_startup(host);
	if (ret)
		goto retry;

	host->ufs_version = ufs_readl(host->mmio_base,REG_UFS_VERSION);
	host->capabilities = ufs_readl(host->mmio_base,
			REG_CONTROLLER_CAPABILITIES);

	ufs_writel(host->mmio_base, LOWER_32_BITS((ulong)host->utrdl),
			REG_UTP_TRANSFER_REQ_LIST_BASE_L);
	ufs_writel(host->mmio_base, UPPER_32_BITS((ulong)host->utrdl),
			REG_UTP_TRANSFER_REQ_LIST_BASE_H);
	ufs_writel(host->mmio_base, 0x1,
			REG_UTP_TRANSFER_REQ_LIST_RUN_STOP);

	ufs_writel(host->mmio_base, LOWER_32_BITS((ulong)host->utmrdl),
			REG_UTP_TASK_REQ_LIST_BASE_L);
	ufs_writel(host->mmio_base, UPPER_32_BITS((ulong)host->utmrdl),
			REG_UTP_TASK_REQ_LIST_BASE_H);
	ufs_writel(host->mmio_base, 0x1,
			REG_UTP_TASK_REQ_LIST_RUN_STOP);

	if (ufs_device_connection_check(host))
		goto retry;

	if (!ufs_verify_dev_init(host))
		goto retry;

	change_ufs_power_mode(host);

	sprd_ufs_block_dev_config();

	return TRUE;
}

