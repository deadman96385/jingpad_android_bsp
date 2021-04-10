/*
 * Copyright (C) 2016 Spreadtrum Communications, Inc.
 *
 */

#include <asm/types.h>
#include <common.h>
#include <sci_types.h>
#include "ufs_hal.h"


void ufs_writel(void* base, u32 val, u32 reg)
{
	*(( volatile u32 *)(base + reg)) = val;
}

u32 ufs_readl(void* base, u32 reg)
{
	return *(( volatile u32 *)(base + reg));
}
