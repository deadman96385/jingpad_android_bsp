/*
 * Copyright (C) 2017 spreadtrum.com
 */

#include <linux/types.h>
#include <malloc.h>
#include <common.h>
#include <mmc.h>


#include <sprd_imgversion.h>
#include <sprd_rpmb.h>
#include <secureboot/sec_common.h>
#include "sprd_rpmb_blk_rng.h"

#define SPRD_IMGVER_MAGIC 0xA50000A5

struct sprd_img_ver_t {
    uint32_t magic;
    uint32_t system_imgver;
    uint32_t vendor_imgver;
};

struct sprd_modem_img_ver_t {
    uint32_t magic;
    uint32_t l_modem_imgver;
    uint32_t l_ldsp_imgver;
    uint32_t l_lgdsp_imgver;
    uint32_t pm_sys_imgver;
    uint32_t agdsp_imgver;
    uint32_t wcn_imgver;
    uint32_t gps_imgver;
    uint32_t gpu_imgver;
    uint32_t vbmeta_imgver;
    uint32_t boot_imgver;
    uint32_t recovery_imgver;
};

#ifdef CONFIG_SPRD_RPMB
int sprd_get_rpmb_block_cnt(void)
{
    u64 rpmb_size = 0;

    rpmb_size = emmc_get_capacity(PARTITION_RPMB);

    return (rpmb_size / RPMB_DATA_SIZE);
}
#endif


int get_sprdimgver_blk_ind(void)
{
#ifdef CONFIG_SPRD_RPMB
	int ret;

	ret = sprd_get_rpmb_block_cnt();
	if (0 > ret ){
		printf("%s: get rpmb block count error! return code %d \n", __func__, ret);
		return -1;
	}
	//The last two blocks save struct sprd_img_ver_t and are compatible with previous versions
	return ret - 2;

#else
	return SPRD_IMGVERSION_BLK;
#endif
}

int get_sprdmodemimgver_blk_ind(void)
{
#ifdef CONFIG_SPRD_RPMB
	int ret;

	ret = sprd_get_rpmb_block_cnt();
	if (0 > ret ){
		printf("%s: get rpmb block count error! return code %d \n", __func__, ret);
		return -1;
	}

	//The last four blocks save struct sprd_modem_img_ver_t and are compatible with previous versions
	return ret - 4;
#else
	return SPRD_MODEM_IMGVERSION_BLK;
#endif
}

int sprd_get_imgversion(antirb_image_type imgType, unsigned int* swVersion)
{
    struct sprd_img_ver_t imgver;
    struct sprd_modem_img_ver_t modem_imgver;
    uint8_t data_rd[RPMB_DATA_SIZE]; //change data to 256-size,some emmc do not support size 512 at a time
    uint16_t block_ind, block_count;
    int ret;

    if (IMAGE_SYSTEM == imgType || IMAGE_VENDOR == imgType) {
        block_ind = get_sprdimgver_blk_ind();
    } else {
        block_ind = get_sprdmodemimgver_blk_ind();
    }

    memset(data_rd, 0x0, sizeof(data_rd));
    block_count = sizeof(data_rd) / RPMB_DATA_SIZE;
    ret = rpmb_blk_read(data_rd, block_ind, block_count);
    if(ret < 0) {
        printf("%s: rpmb read blk %d fail! ret %d \n", __func__, block_ind, ret);
        return ret;
    }

    printf("%s: rpmb read blk %d successful \n", __func__, block_ind);

    if (IMAGE_SYSTEM == imgType || IMAGE_VENDOR == imgType) {
        memcpy((void *)&imgver, data_rd, sizeof(struct sprd_img_ver_t));

        if(imgver.magic != SPRD_IMGVER_MAGIC) {
            printf("invalid sprd imgversion magic %x exp %x \n",
                imgver.magic, SPRD_IMGVER_MAGIC);
            return -1;
        }
    } else {
        memcpy((void *)&modem_imgver, data_rd, sizeof(struct sprd_modem_img_ver_t));

        if(modem_imgver.magic != SPRD_IMGVER_MAGIC) {
            printf("invalid sprd imgversion magic %x exp %x \n",
                modem_imgver.magic, SPRD_IMGVER_MAGIC);
            return -1;
        }

    }

    switch(imgType) {
        case IMAGE_SYSTEM:
            *swVersion = imgver.system_imgver;
            break;
        case IMAGE_VENDOR:
            *swVersion = imgver.vendor_imgver;
            break;
        case IMAGE_L_MODEM:
            *swVersion = modem_imgver.l_modem_imgver;
            break;
        case IMAGE_L_LDSP:
            *swVersion = modem_imgver.l_ldsp_imgver;
            break;
        case IMAGE_L_LGDSP:
            *swVersion = modem_imgver.l_lgdsp_imgver;
            break;
        case IMAGE_PM_SYS:
            *swVersion = modem_imgver.pm_sys_imgver;
            break;
        case IMAGE_AGDSP:
            *swVersion = modem_imgver.agdsp_imgver;
            break;
        case IMAGE_WCN:
            *swVersion = modem_imgver.wcn_imgver;
            break;
        case IMAGE_GPS:
            *swVersion = modem_imgver.gps_imgver;
            break;
        case IMAGE_GPU:
		case IMAGE_TYPE_END:
            *swVersion = modem_imgver.gpu_imgver;
            break;
        case IMAGE_VBMETA:
            *swVersion = modem_imgver.vbmeta_imgver;
            break;
        case IMAGE_BOOT:
            *swVersion = modem_imgver.boot_imgver;
            break;
        case IMAGE_RECOVERY:
            *swVersion = modem_imgver.recovery_imgver;
            break;
        default:
            printf("invalid sprd image type %d\n", imgType);
            return -1;
    }

#ifdef IMGVER_DEBUG
    printf("sprd image type %d, swVersion:0x%x\n", imgType, *swVersion);
#endif
    return 0;
}

int sprd_get_all_imgversion(VbootVerInfo* vboot_ver_info)
{
    struct sprd_img_ver_t imgver;
    struct sprd_modem_img_ver_t modem_imgver;
    uint8_t data_rd[RPMB_DATA_SIZE]; //change data to 256-size,some emmc do not support size 512 at a time
    uint16_t block_ind, block_count;
    int ret;

    block_ind = get_sprdimgver_blk_ind();

    memset(data_rd, 0x0, sizeof(data_rd));
    block_count = sizeof(data_rd) / RPMB_DATA_SIZE;
    ret = rpmb_blk_read(data_rd, block_ind, block_count);
    if(ret < 0) {
        printf("%s: rpmb read blk %d fail! ret %d \n", __func__, block_ind, ret);
        return ret;
    }

    printf("%s: rpmb read blk %d successful \n", __func__, block_ind);

	memcpy((void *)&imgver, data_rd, sizeof(struct sprd_img_ver_t));

	if(imgver.magic != SPRD_IMGVER_MAGIC) {
		printf("invalid sprd imgversion magic %x exp %x \n",
		    imgver.magic, SPRD_IMGVER_MAGIC);
		return -1;
	} else {
		vboot_ver_info->img_ver[IMAGE_SYSTEM] = imgver.system_imgver;
		vboot_ver_info->img_ver[IMAGE_VENDOR] = imgver.vendor_imgver;
	} 

	block_ind = get_sprdmodemimgver_blk_ind();
    memset(data_rd, 0x0, sizeof(data_rd));
    block_count = sizeof(data_rd) / RPMB_DATA_SIZE;
    ret = rpmb_blk_read(data_rd, block_ind, block_count);
    if(ret < 0) {
        printf("%s: rpmb read blk %d fail! ret %d \n", __func__, block_ind, ret);
        return ret;
    }
	memcpy((void *)&modem_imgver, data_rd, sizeof(struct sprd_modem_img_ver_t));

	if(modem_imgver.magic != SPRD_IMGVER_MAGIC) {
		printf("invalid sprd imgversion magic %x exp %x \n",
			modem_imgver.magic, SPRD_IMGVER_MAGIC);
		return -1;
	} else {
		vboot_ver_info->img_ver[IMAGE_L_MODEM] = modem_imgver.l_modem_imgver;
		vboot_ver_info->img_ver[IMAGE_L_LDSP] = modem_imgver.l_ldsp_imgver;
		vboot_ver_info->img_ver[IMAGE_L_LGDSP] = modem_imgver.l_lgdsp_imgver;
		vboot_ver_info->img_ver[IMAGE_PM_SYS] = modem_imgver.pm_sys_imgver;
		vboot_ver_info->img_ver[IMAGE_AGDSP] = modem_imgver.agdsp_imgver;
		vboot_ver_info->img_ver[IMAGE_WCN] = modem_imgver.wcn_imgver;
		vboot_ver_info->img_ver[IMAGE_GPS] = modem_imgver.gps_imgver;
		vboot_ver_info->img_ver[IMAGE_GPU] = modem_imgver.gpu_imgver;
		vboot_ver_info->img_ver[IMAGE_VBMETA] = modem_imgver.vbmeta_imgver;
		vboot_ver_info->img_ver[IMAGE_BOOT] = modem_imgver.boot_imgver;
		vboot_ver_info->img_ver[IMAGE_RECOVERY] = modem_imgver.recovery_imgver;
	}

#ifdef IMGVER_DEBUG
	for(ret = IMAGE_VBMETA; ret < IMAGE_TYPE_END; ret++) {
		printf("vboot_ver_info->img_ver[%d] = 0x%x\n", ret, vboot_ver_info->img_ver[ret]);
	}
#endif

    return 0;
}

