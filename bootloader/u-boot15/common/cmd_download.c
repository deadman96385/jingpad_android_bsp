/*
 * Copyright (C) 2014 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Authors: Justin Wang <justin.wang@spreadtrum.com>
 */

#include <common.h>
#include <command.h>
#include "packet.h"
#include "dl_cmd_def.h"
#include <dl_cmd_proc.h>
#include <malloc.h>
#include <chipram_env.h>

#ifdef CONFIG_SOC_IWHALE2
#include <asm/arch/chip_id.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

typedef enum {
	E_DISABLE_TRAN_CODE = 0,
	E_IS_OLD_MEMORY,
	E_SUPPORT_RAW_DATA,
	E_FLUSH_SIZE,
	E_RSA, //0: not support; 1:AES CBC  2: RSA2048
	E_TIME_STAMP,
#ifdef CONFIG_SEND_STORAGE_TYPE
	E_STORAGE_TYPE,
#endif
	E_SUPPORT_DUMP_UBOOT_LOG = 7,
	E_MAX_ID = 0xFFFF
} E_DA_INFO_ID;


static int dl_times=0;
static struct dl_cmd *cmdlist = NULL;
extern int sprd_clean_rtc(void);
extern void usb_init (uint32_t autodl_mode);
typedef struct _DA_INFO_T_
{
	uint32_t   dwVersion;
	uint32_t   bDisableHDLC;	//0: Enable hdl; 1:Disable hdl
	uint8_t    bIsOldMemory;
	uint8_t    bSupportRawData;
	uint8_t    bReserve[2];
	uint32_t   dwFlushSize;		//unit KB
#ifdef CONFIG_SEND_STORAGE_TYPE
	uint32_t   dwStorageType;
	uint32_t   dwReserve[59];	//Reserve
#else
	uint32_t   dwReserve[60];   //Reserve
#endif
}DA_INFO_T;

#ifdef CONFIG_SEND_STORAGE_TYPE
typedef enum storage_type {
	STORAGE_TYPE_NAND = 0x101,
	STORAGE_TYPE_EMMC = 0x102,
	STORAGE_TYPE_UFS  = 0x103
}storage_type_t;
#endif

void dl_cmd_register(enum dl_cmd_type type,
		       int (*handle)(struct dl_packet *pkt, void *arg))
{
	struct dl_cmd *cmd = (void *)0;

	cmd = (struct dl_cmd *)malloc(sizeof(struct dl_cmd));
	//printf("%s:malloc %d to %p mem\n", __FUNCTION__ , sizeof(struct dl_cmd), cmd);
	if (cmd) {
		cmd->type = type;
		cmd->handle = handle;
		cmd->next = cmdlist;
		cmdlist = cmd;
	}
	return;
}
void dl_cmd_handler(void)
{
	struct dl_cmd *cmd;
	struct dl_packet *pkt;
	printf("%s:enter\n", __FUNCTION__);
	for (;;) {
		pkt = dl_get_packet();

		pkt->body.type = (pkt->body.type >> 8 | pkt->body.type << 8);
		pkt->body.size = (pkt->body.size >> 8 | pkt->body.size << 8);
		for (cmd = cmdlist; cmd; cmd = cmd->next) {
			if(cmd->type != pkt->body.type)
				continue;
			cmd->handle(pkt,NULL);
			dl_free_packet(pkt);

		/*
		 * in for(;;) loop, there should be no other log except handle func,
		 * otherwise common_raw_write() will be called all the time and will
		 * slow the download speed
		 */
			write_log();
			break;
		}
		/* cannot found the cmd in cmdlist */
		if (NULL == cmd)
			dl_send_ack(BSL_UNSUPPORTED_CMD);
	}
	return 0;
}

#ifdef CONFIG_DL_POWER_CONTROL
extern void dl_power_control(void);
#endif

static int dl_da_tlv(uint8_t *content, uint16_t type, uint16_t len,
	uint8_t *value)
{
	uint16_t *pt;
	uint16_t *pl;
	uint8_t *pv;

	pt = (uint16_t *)content;
	pl = pt + 1;
	pv = (uint8_t *)(pl + 1);

	*pt = type;
	*pl = len;
	if (len == 1)
		*pv = *value;
	else
		memcpy(pv, value, len);

	return sizeof(*pt) + sizeof(*pl) + len;
}

int do_download(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	extern int autodloader_mainhandler(void);
	boot_mode_t boot_role = get_boot_role();
	int chip_version = 0;
	dl_packet_t ack_packet;
	DA_INFO_T Da_Info = {0};
	int offset = 0;

#ifdef CONFIG_USB_ENUM_IN_UBOOT
	chip_version = sprd_get_chip_version();
	if ((dl_times==0) && (boot_role == BOOTLOADER_MODE_DOWNLOAD) && (chip_version < USB_FIX_VERSION))
	{
		dl_times=dl_times+1;
		autodloader_mainhandler();
	}
#endif

	printf("%s:enter\n", __FUNCTION__);
	dl_packet_init ();
#ifdef CONFIG_NAND_BOOT
	fdl_ubi_dev_init();
#endif
	sprd_clean_rtc();

#ifdef CONFIG_DL_POWER_CONTROL
	dl_power_control();
#endif

#ifdef CONFIG_DTS_MEM_LAYOUT
	dl_set_buf_base_size();
#endif

	/* register all cmd process functions */
	dl_cmd_register(BSL_CMD_START_DATA, dl_cmd_write_start);
	dl_cmd_register(BSL_CMD_MIDST_DATA, dl_cmd_write_midst);
	dl_cmd_register(BSL_CMD_END_DATA, dl_cmd_write_end);
	dl_cmd_register(BSL_CMD_READ_FLASH_START, dl_cmd_read_start);
	dl_cmd_register(BSL_CMD_READ_FLASH_MIDST, dl_cmd_read_midst);
	dl_cmd_register(BSL_CMD_READ_FLASH_END, dl_cmd_read_end);
	dl_cmd_register(BSL_ERASE_FLASH, dl_cmd_erase);
	dl_cmd_register(BSL_REPARTITION, dl_cmd_repartition);
	dl_cmd_register(BSL_CMD_NORMAL_RESET, dl_cmd_reboot);
	dl_cmd_register(BSL_CMD_POWER_DOWN_TYPE, dl_powerdown_device);
	//dl_cmd_register(BSL_CMD_READ_CHIP_TYPE, dl_cmd_mcu_read_chiptype);
	dl_cmd_register(BSL_CMD_READ_MCP_TYPE, dl_cmd_read_mcptype);
	dl_cmd_register(BSL_CMD_CHECK_ROOTFLAG, dl_cmd_check_rootflag);
#ifdef CONFIG_SPRD_UID
	dl_cmd_register(BSL_CMD_READ_UID, dl_cmd_get_chip_uid);
#else
#ifdef CONFIG_X86
	dl_cmd_register(BSL_CMD_READ_UID, dl_cmd_get_uid_x86);
#else
	dl_cmd_register(BSL_CMD_READ_UID, dl_cmd_get_uid);
#endif
#endif
	dl_cmd_register(BSL_CMD_END_PROCESS, dl_cmd_end_process);
	dl_cmd_register(BSL_CMD_READ_REFINFO, dl_cmd_read_ref_info);
	dl_cmd_register(BSL_CMD_DIS_HDLC, dl_cmd_disable_hdlc);
	dl_cmd_register(BSL_CMD_WRITE_DATETIME, dl_cmd_write_datetime);
	dl_cmd_register(BSL_CMD_SET_DEBUGINFO, dl_cmd_set_debuginfo);
#ifdef CONFIG_PCTOOL_CHECK_MULTI_FIXNV
	dl_cmd_register(BSL_CMD_CHECK_NV_TYPE, dl_cmd_check_NV_type);
#endif
#ifdef CONFIG_PCTOOL_CHECK_WRITE_PROTECT
	dl_cmd_register(BSL_CMD_ENABLE_WRITE_FLASH, dl_enable_write_flash);
#endif
#ifdef CONFIG_EMMC_DDR_CHECK_TYPE
	dl_cmd_register(BSL_CMD_READ_FLASH_TYPE, dl_cmd_read_flashtype);
#endif
#if !defined(CONFIG_NAND_BOOT) && !defined(CONFIG_DDR_BOOT)
	dl_cmd_register(BSL_CMD_CHECK_PARTITION, dl_cmd_check_partition);
#endif
	dl_cmd_register(BSL_CMD_SET_FIRST_MODE, dl_set_first_mode);
	dl_cmd_register(BSL_CMD_WRITE_RAW_DATA_ENABLE, dl_cmd_write_raw_data_enable);
	dl_cmd_register(BSL_CMD_DLOAD_RAW_START, dl_cmd_per_raw_packet_start);
	dl_cmd_register(BSL_CMD_DLOAD_RAW_START2, dl_cmd_whole_raw_file_start);
	dl_cmd_register(BSL_CMD_WRITE_FLUSH_DATA, dl_cmd_write_flush_raw_data);
	usb_init(0);

	/* uart download doesn't supoort disable hdlc, so need check it */
	if (FDL_get_DisableHDLC() == NULL)
		dl_send_ack (BSL_INCOMPATIBLE_PARTITION);
	else {
		if (FDL_get_SupportRawDataProc())
			Da_Info.dwVersion = 4;
		else
			Da_Info.dwVersion = 2;
		Da_Info.bDisableHDLC = 1;

#ifndef CONFIG_NAND_BOOT
	if (gd->boot_device == BOOT_DEVICE_EMMC)
		Da_Info.bIsOldMemory = emmc_2ndhand_detect();
	else
#endif
		Da_Info.bIsOldMemory = 0;
		if (FDL_get_SupportRawDataProc()) {
			/* support raw data transfer */
			Da_Info.bSupportRawData = 2;
			Da_Info.dwFlushSize = 2048;//KB
		}

#ifdef CONFIG_SEND_STORAGE_TYPE
#if defined(CONFIG_BLK_DEV_BOOT)
		if (get_bootdevice() == BOOT_DEVICE_EMMC)
			Da_Info.dwStorageType = STORAGE_TYPE_EMMC;
		else if (get_bootdevice() == BOOT_DEVICE_UFS)
			Da_Info.dwStorageType = STORAGE_TYPE_UFS;
#elif defined(CONFIG_EMMC_BOOT)
		Da_Info.dwStorageType = STORAGE_TYPE_EMMC;
#elif defined(CONFIG_NAND_BOOT)
		Da_Info.dwStorageType = STORAGE_TYPE_NAND;
#else
		#error Macros(CONFIG_BLK_DEV_BOOT\CONFIG_EMMC_BOOT\CONFIG_EMMC_BOOT) \
			need to be defined in this project
#endif
#endif

		ack_packet.body.type = BSL_INCOMPATIBLE_PARTITION;
#ifdef CONFIG_SEND_STORAGE_TYPE
		/* specify magic for new da_info */
		*(uint32_t *)ack_packet.body.content = 0x7477656e;
		offset += 4;
		offset += dl_da_tlv(ack_packet.body.content + offset,
					(uint16_t)E_DISABLE_TRAN_CODE, 4, &Da_Info.bDisableHDLC);
		offset += dl_da_tlv(ack_packet.body.content + offset,
			(uint16_t)E_IS_OLD_MEMORY, 1, &Da_Info.bIsOldMemory);
		offset += dl_da_tlv(ack_packet.body.content + offset,
					(uint16_t)E_SUPPORT_RAW_DATA, 1,
					&Da_Info.bSupportRawData);
		offset += dl_da_tlv(ack_packet.body.content + offset,
					(uint16_t)E_FLUSH_SIZE, 4, &Da_Info.dwFlushSize);
		offset += dl_da_tlv(ack_packet.body.content + offset,
					(uint16_t)E_STORAGE_TYPE, 4, &Da_Info.dwStorageType);
		ack_packet.body.size = offset;
#else
		memcpy((unchar *)ack_packet.body.content, (unchar *)&Da_Info,sizeof(Da_Info));
		ack_packet.body.size = sizeof(Da_Info);
#endif
		dl_send_packet(&ack_packet);
	}

	/* enter command handler */
	dl_cmd_handler();
        return 0;
}

U_BOOT_CMD(
	download,	CONFIG_SYS_MAXARGS,	1,	do_download,
	"download mode",
	"choose to enter download mode\n"
	"it is used for downloading firmwares to storage in factory or research purpose\n"
);
