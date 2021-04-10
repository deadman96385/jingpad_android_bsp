/* -*- C -*- ****************************************************************
 *
 *  System        : 
 *  Module        : 
 *  Object Name   : $RCSfile$
 *  Revision      : $Revision$
 *  Date          : $Date$
 *  Author        : $Author$
 *  Created By    : zhenxiong.lai
 *  Created       : Thu Dec 6 08:32:13 2018
 *  Last Modified : <190228.1634>
 *
 *  Description	
 *
 *  Notes
 *
 *  History
 *	
 ****************************************************************************
 *
 *  Copyright (c) 2018 sprd.
 * 
 *  All Rights Reserved.
 * 
 * This  document  may  not, in  whole  or in  part, be  copied,  photocopied,
 * reproduced,  translated,  or  reduced to any  electronic  medium or machine
 * readable form without prior written consent from sprd.
 *
 ****************************************************************************/
#include <common.h>
#include <malloc.h>
#include <part.h>
#include <sprd_common_rw.h>
#include <ext4fs.h>
#include <mmc.h>
#include <chipram_env.h>

#ifdef SUPPORT_WAIT_RC_LOAD_IMG
#include <asm/arch/sprd_reg.h>
#ifdef CONFIG_PCIE_SPRD
#include <linux/pci/pcie_sprd.h>
#endif
#endif

enum {
	IMG_BOOT = 0,
	IMG_DTB,
	IMG_DTBO,
	IMG_MODEM
};

typedef struct ddr_partition {
	char part_name[32];
	uint64_t partition_address;
	uint32_t img_type;
} ddr_partition_t;

static const ddr_partition_t ddr_partition_info[] = {
#ifdef CONFIG_DDR_BOOT_BOOTIMAGE_ADR
	{"boot", CONFIG_DDR_BOOT_BOOTIMAGE_ADR, IMG_BOOT},
#endif
#ifdef CONFIG_DDR_BOOT_DTBIMAGE_ADR
	{"dtb", CONFIG_DDR_BOOT_DTBIMAGE_ADR, IMG_DTB},
#endif
#ifdef CONFIG_DDR_BOOT_DTBOIMAGE_ADR
	{"dtbo", CONFIG_DDR_BOOT_DTBOIMAGE_ADR, IMG_DTBO},
#endif
#ifdef CONFIG_PSCP_IMG_ADDR
	{"nr_modem", CONFIG_PSCP_IMG_ADDR, IMG_MODEM},
#endif
#ifdef CONFIG_NRPHY_IMG_ADDR
	{"nr_nrphy", CONFIG_NRPHY_IMG_ADDR, IMG_MODEM},
#endif
#ifdef CONFIG_V3PHY_IMG_ADDR
	{"nr_v3phy", CONFIG_V3PHY_IMG_ADDR, IMG_MODEM},
#endif
};

int get_img_partition_id(char *part_name, unsigned int *id)
{
	return -1;
}

#ifdef CONFIG_PARTITION_UUIDS
int get_img_partition_uuid(char *part_name, char* uuid)
{
	return -1;
}
#endif

int get_img_partition_size(char *part_name, uint64_t *size)
{
	return -1;
}

#ifdef SUPPORT_WAIT_RC_LOAD_IMG
#define BOOT_IMG_DONE	BIT(10)
#define MODEM_HEAD_DONE	BIT(11)

#ifdef CONFIG_PCIE_SPRD
#define EP_SET_BAR_DONE_FLAG	BIT(7) /* ep to rc, mux ddr read bit */
#define EP_RESCAN_DONE_FLAG	BIT(7) /* rc to ep, mux ddr read bit, 0 active */
#define BIT_SET_OFFSET		0x1000

static void reset_pcie_bar(void)
{
	uint32_t ret;

	debugf("wait reset pcie bar...\n");
	do {
		if (0 == sprd_pcie_split_bar())
			break;
	} while(1);

	debugf("set ep bar done.\n");
	/* set EP_SET_BAR_DONE_FLAG */
	*(volatile u32 *)(REG_PMU_APB_PCIE_SLP_CFG + BIT_SET_OFFSET) =
		EP_SET_BAR_DONE_FLAG;

	debugf("wait rc rescan ep...\n");
	/* wait EP_RESCAN_DONE_FLAG 1 ==> 0 */
	do {
		ret = *(volatile uint32_t *)REG_PMU_APB_PCIE_SLP_CFG;
	} while (ret & EP_RESCAN_DONE_FLAG);
}
#endif

static void wait_modem_head_done(void)
{
	uint32_t ret;
	static int modem_done = 0;

	if (modem_done) return;

	debugf("wait modem head done ...\n");

	do {
		ret = *(volatile uint32_t *)REG_PMU_APB_PCIE_SLP_CFG;
	} while (!(ret & MODEM_HEAD_DONE));

	modem_done = 1;

	/* after rc load modem head, rest pcie bar */
#ifdef CONFIG_PCIE_SPRD
	reset_pcie_bar();
#endif
}

static void wait_boot_img_done(void)
{
	uint32_t ret;
	static int boot_done = 0;

	if (boot_done) return;

	debugf("wait boot img done ...\n");

	do {
		ret = *(volatile uint32_t *)REG_PMU_APB_PCIE_SLP_CFG;
	} while (!(ret & BOOT_IMG_DONE));

	boot_done = 1;
}

void wait_rc_load_img(uint32_t img_type)
{
	if (img_type == IMG_BOOT)
		wait_boot_img_done();
	else if (img_type == IMG_MODEM)
		wait_modem_head_done();
}
#endif

int common_raw_read(char *part_name, uint64_t size, uint64_t offset, char *buf)
{
	uint64_t part_start = 0;
	uint64_t i = 0;
	uint32_t img_type;

	if ((!part_name) || (!size) || (!buf))
		return -1;

	for (i = 0; i < ARRAY_SIZE(ddr_partition_info); i++) {
		if (!strcmp(part_name, ddr_partition_info[i].part_name)) {
			part_start = ddr_partition_info[i].partition_address;
			img_type = ddr_partition_info[i].img_type;
			goto copy_flag;
		}
	}

	return -2;

copy_flag:
#ifdef SUPPORT_WAIT_RC_LOAD_IMG
	wait_rc_load_img(img_type);
#endif
	offset += part_start;
	memcpy(buf, offset, size);

	return 0;
}

int common_raw_write(char *part_name, uint64_t size, uint64_t updsize, uint64_t offset, char *buf)
{
	return -1;
}

int common_raw_erase(char *part_name, uint64_t size, uint64_t offset)
{
	return -1;
}

int common_write_backstage(char *part_name, uint32_t size, uint64_t offset, char *buf)
{
	return -1;
}


int common_query_backstage(char *part_name, uint32_t size, char *buf)
{
	return -1;
}


int common_repartition(disk_partition_t *partitions, int parts_count)
{
	return -1;
}

int common_partition_sync(char *part_name)
{
	return -1;
}

int32_t common_get_lba_size(void)
{
	return -1;
}

int do_fs_file_read(char *mpart, char *filenm, void *buf, int len)
{
	return -1;
}

int do_fs_file_write(char *mpart, char *filenm, void *buf, int len)
{
	return -1;
}

int do_raw_data_write(char *part, u32 updsz, u32 size, u32 off, char *buf)
{
	return -1;
}


