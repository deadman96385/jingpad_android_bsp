/*
 * Copyright (c) 2013-2014, spreadtrum.com.
 *
 */

#include "uboot_sec_drv.h"
#include <mmc.h>
#include <sprd_rpmb.h>
#include <common.h>
#include <chipram_env.h>
#include <sprd_ufs.h>

DECLARE_GLOBAL_DATA_PTR;

static u64 rpmb_size __attribute__((aligned(4096)));
static int is_rpmb_key __attribute__((aligned(4096)));
static u8 check_rpmb_key_pac[RPMB_DATA_FRAME_SIZE] __attribute__((aligned(4096)));

uint8_t rpmb_blk_read(char *blk_data, uint16_t blk_index, uint8_t block_count)
{
	uint8_t ret = 0;

#ifdef CONFIG_MMC
	if (gd->boot_device == BOOT_DEVICE_EMMC)
		ret = mmc_rpmb_blk_read(blk_data, blk_index, block_count);
#endif
#ifdef CONFIG_UFS
	if (gd->boot_device == BOOT_DEVICE_UFS)
		ret = ufs_rpmb_blk_read(blk_data, blk_index, block_count);
#endif

	return ret;
}

int check_rpmb_key(uint8_t *package, int package_size)
{
	int ret = 0;

#ifdef CONFIG_MMC
	if (gd->boot_device == BOOT_DEVICE_EMMC)
		ret = check_mmc_rpmb_key(package, package_size);
#endif
#ifdef CONFIG_UFS
	if (gd->boot_device == BOOT_DEVICE_UFS)
		ret = check_ufs_rpmb_key(package, package_size);
#endif

	return ret;
}

int is_wr_rpmb_key(void)
{
	int ret = 0;

#ifdef CONFIG_MMC
	if (gd->boot_device == BOOT_DEVICE_EMMC)
		ret = is_wr_mmc_rpmb_key();
#endif
#ifdef CONFIG_UFS
	if (gd->boot_device == BOOT_DEVICE_UFS)
		ret = is_wr_ufs_rpmb_key();
#endif

	return ret;
}

int uboot_set_rpmb_size()
{
#ifdef CONFIG_MMC
	if (gd->boot_device == BOOT_DEVICE_EMMC)
		rpmb_size = emmc_get_capacity(PARTITION_RPMB);
#endif
#ifdef CONFIG_UFS
	if (gd->boot_device == BOOT_DEVICE_UFS) {
		prepare_rpmb_lu();
		rpmb_size = (1 << rpmb_lu_info.log2blksz) *
			    (rpmb_lu_info.blkcnt);
	}
#endif
	printf("%s: rpmb size %lld\n", __func__, rpmb_size);
	smc_param *param = tee_common_call(FUNCTYPE_SET_RPMB_SIZE,
					   (uint32_t)(&rpmb_size),
					   sizeof(rpmb_size));

	return param->a0;
}


int uboot_is_wr_rpmb_key()
{
	is_rpmb_key = -1;
	is_rpmb_key = is_wr_rpmb_key();

	if (is_rpmb_key == 0) {
		printf("%s rpmb unwritten, call tos \n", __func__);
		smc_param *param = tee_common_call(FUNCTYPE_IS_WR_RPMB_KEY,
						   (uint32_t)(&is_rpmb_key),
						   sizeof(is_rpmb_key));
		return param->a0;
	} else {
		return -1;
	}
}

int uboot_check_rpmb_key()
{
	int ret = 0;

	ret = check_rpmb_key(check_rpmb_key_pac, RPMB_DATA_FRAME_SIZE);
	if (ret == 0) {
		printf("%s get rpmb package, call tos to check rpmb key \n",
			__func__);
		smc_param *param = tee_common_call(FUNCTYPE_CHECK_RPMB_KEY,
						   (uint32_t)check_rpmb_key_pac,
						   RPMB_DATA_FRAME_SIZE);
		return param->a0;
	} else {
		printf("%s get rpmb package fail\n", __func__);
		return -1;
	}
}

