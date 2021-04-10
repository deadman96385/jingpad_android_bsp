/*
 *  arch/arm/cpu/armv8/TsharkL/intc.c
 *
 *  enable sprd intc0---3 and aon intc
 *
 *  Author:	Wei Qiao(wei.qiao@spreadtrum.com)
 *  Created:	May 7, 2015
 *  Copyright:	Spreadtrum Inc.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */
#include <common.h>
#include <div64.h>
#include <asm/io.h>
#include <linux/types.h>
#include <asm/arch/sprd_reg.h>
#include "asm/arch/common.h"

void sprd_intc_enable(void)
{
	writel(readl(REG_AON_APB_APB_EB0) | BIT_INTC_EB, REG_AON_APB_APB_EB0);
	writel(readl(REG_AP_APB_APB_EB) | BIT_INTC0_EB | BIT_INTC1_EB
			| BIT_INTC2_EB | BIT_INTC3_EB, REG_AP_APB_APB_EB);
}
