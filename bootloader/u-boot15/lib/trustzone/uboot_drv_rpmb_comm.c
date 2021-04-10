/*
 * Copyright (c) 2013-2014, spreadtrum.com.
 *
 */

#include <linux/compiler.h>
#include "uboot_sec_drv.h"


int __weak uboot_set_rpmb_size()
{
    return -1;
}


int __weak uboot_is_wr_rpmb_key()
{
    return -1;
}

int __weak uboot_check_rpmb_key()
{
    return -1;
}

