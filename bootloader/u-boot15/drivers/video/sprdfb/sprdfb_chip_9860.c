/******************************************************************************
 ** File Name:    sprdfb_chip_9860.c                                     *
 ** Author:       leon.he                                           *
 ** DATE:         14/01/2016                                        *
 ** Copyright:    2013 Spreatrum, Incoporated. All Rights Reserved. *
 ** Description:                                                    *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                               *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                       *

 ******************************************************************************/

#include "sprdfb_chip_common.h"
#include "sprdfb.h"

void misc_noc_ctrl(unsigned long base, unsigned int mode, unsigned int sel)
{
	unsigned int val;

	val = *(volatile unsigned int *)base;
	val &= ~(INTERLEAVE_MODE_MASK | INTERLEAVE_SEL_MASK);
	val |= (mode << INTERLEAVE_MODE_OFFSET) |
		(sel << INTERLEAVE_SEL_OFFSET);
	*(volatile unsigned int *)base = val;
}

int disp_domain_power_ctrl(int enable)
{
	if (enable) {
		__raw_bits_and(~BIT_PMU_APB_PD_DISP_SYS_FORCE_SHUTDOWN, REG_PMU_APB_PD_DISP_SYS_CFG);
		mdelay(10);
		__raw_bits_or(BIT_AON_APB_DISP_EMC_EB | BIT_AON_APB_DISP_EB, REG_AON_APB_APB_EB1);
	} else {
		__raw_bits_and(~(BIT_AON_APB_DISP_EB | BIT_AON_APB_DISP_EMC_EB), REG_AON_APB_APB_EB1);
		mdelay(10);
		__raw_bits_or(BIT_PMU_APB_PD_DISP_SYS_FORCE_SHUTDOWN, REG_PMU_APB_PD_DISP_SYS_CFG);
	}

	return 0;
}

void dsi_enable(void)
{
	__raw_bits_or(BIT_DISP_AHB_DSI0_EB, REG_DISP_AHB_AHB_EB);
	__raw_bits_or(BIT_DISP_AHB_DPHY0_CFG_CKG_EN, REG_DISP_AHB_GEN_CKG_CFG);
}

void dsi_disable(void)
{
	__raw_bits_and(~BIT_DISP_AHB_DSI0_EB, REG_DISP_AHB_AHB_EB);
}

void dispc_early_configs(void)
{
	disp_domain_power_ctrl(1);
	__raw_bits_or(BIT_DISP_AHB_CKG_EB |
			BIT_DISP_AHB_DISPC_MTX_EB |
			BIT_DISP_AHB_DISPC_MMU_EB |
			BIT_DISP_AHB_DISPC0_EB, REG_DISP_AHB_AHB_EB); 
	__raw_bits_or(BIT_DISP_AHB_DISPC_MTX_FORCE_CKG_EN |
			BIT_DISP_AHB_DISPC_MTX_AUTO_CKG_EN |
			BIT_DISP_AHB_DISPC_NOC_AUTO_CKG_EN |
			BIT_DISP_AHB_DISPC_NOC_FORCE_CKG_EN, REG_DISP_AHB_GEN_CKG_CFG);
}

void dispc_print_clk(void)
{
#if 0
	FB_PRINT("0x7120002c = 0x%x\n", __raw_readl(0x7120002c));
	FB_PRINT("0x71200030 = 0x%x\n", __raw_readl(0x71200030));
	FB_PRINT("0x71200034 = 0x%x\n", __raw_readl(0x71200034));
	FB_PRINT("0x20d00000 = 0x%x\n", __raw_readl(0x20d00000));
	FB_PRINT("0x71300000 = 0x%x\n", __raw_readl(0x71300000));
	FB_PRINT("0x402e0004 = 0x%x\n", __raw_readl(0x402e0004));
#endif
}


