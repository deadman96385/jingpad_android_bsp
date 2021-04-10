/*
 * Copyright (C) 2017 spreadtrum.com
 */
#include <linux/compiler.h>
#include <sprd_imgversion.h>

int __weak sprd_get_imgversion(antirb_image_type imgType, unsigned int* swVersion)
{
    return -1;
}
