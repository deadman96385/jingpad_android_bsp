/*
 * Copyright (c) 2013-2014, spreadtrum.com.
 *
 */

#include "uboot_sec_drv.h"
#include <mmc.h>
#include <sprd_rpmb.h>

static u64 rpmb_size __attribute__((aligned(4096)));
static int is_rpmb_key __attribute__((aligned(4096)));
static u8 check_rpmb_key_pac[RPMB_DATA_FRAME_SIZE] __attribute__((aligned(4096)));


int uboot_set_rpmb_size()
{
    rpmb_size = emmc_get_capacity(PARTITION_RPMB);
    printf("%s: rpmb size %lld\n", __func__, rpmb_size);
    smc_param *param = tee_common_call(FUNCTYPE_SET_RPMB_SIZE, (uint32_t)(&rpmb_size), sizeof(rpmb_size));

    return param->a0;
}


int uboot_is_wr_rpmb_key()
{
    is_rpmb_key = -1;
    is_rpmb_key = is_wr_rpmb_key();
    if (0 == is_rpmb_key) {
        printf("%s rpmb unwritten, call tos \n", __func__);
        smc_param *param = tee_common_call(FUNCTYPE_IS_WR_RPMB_KEY, (uint32_t)(&is_rpmb_key), sizeof(is_rpmb_key));
        return param->a0;
    } else {
        return -1;
    }
}

int uboot_check_rpmb_key()
{
    int ret = 0;

    ret = check_rpmb_key(check_rpmb_key_pac, RPMB_DATA_FRAME_SIZE);
    if (0 == ret) {
        printf("%s get rpmb package, call tos to check rpmb key \n", __func__);
        smc_param *param = tee_common_call(FUNCTYPE_CHECK_RPMB_KEY, (uint32_t)check_rpmb_key_pac, RPMB_DATA_FRAME_SIZE);
        return param->a0;
    } else {
        printf("%s get rpmb package fail\n", __func__);
        return -1;
    }
}

