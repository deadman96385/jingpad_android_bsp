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
		__raw_bits_and(~BIT_PMU_APB_PD_CAM_SYS_FORCE_SHUTDOWN, REG_PMU_APB_PD_CAM_SYS_PWR_CFG);
		mdelay(10);
		__raw_bits_or(BIT_AON_APB_DISP_EMC_EB | BIT_AON_APB_AON_DISP_EB, REG_AON_APB_APB_EB1);
	} else {
		__raw_bits_and(~(BIT_AON_APB_AON_DISP_EB | BIT_AON_APB_DISP_EMC_EB), REG_AON_APB_APB_EB1);
		mdelay(10);
		__raw_bits_or(BIT_PMU_APB_PD_CAM_SYS_FORCE_SHUTDOWN, REG_PMU_APB_PD_CAM_SYS_PWR_CFG);
	}

	return 0;
}

void dsi_enable(void)
{
	unsigned int reg = 0;
	__raw_writel(0x6c87,0xD2100064);//counter
	__raw_writel(0x6c87,0xD2100068);
//	__raw_writel(0x8,0xd3100008);
	__raw_bits_or(BIT_DISP_AHB_DSI0_EB, REG_DISP_AHB_AHB_EB);
	__raw_bits_or(BIT_DISP_AHB_DPHY0_CFG_CKG_EN, REG_DISP_AHB_GEN_CKG_CFG);
}

void dsi_disable(void)
{
	__raw_bits_and(~BIT_DISP_AHB_DSI0_EB, REG_DISP_AHB_AHB_EB);
}

void dispc_early_configs(void)
{

	unsigned int reg = 0;
	disp_domain_power_ctrl(1);

	__raw_bits_or(1<<30, 0xe42e0004);
	__raw_bits_or(1<<29, 0xe42e0004);
	mdelay(20);
	__raw_bits_or(BIT_DISP_AHB_CKG_EB |
			BIT_DISP_AHB_DISPC_MTX_EB |
			BIT_DISP_AHB_DISPC_MMU_EB |
			BIT_DISP_AHB_DISPC0_EB |
            BIT_DISP_AHB_DISP_MTX_EB |
            BIT_DISP_AHB_SYS_MTX_EB, REG_DISP_AHB_AHB_EB);
	reg = __raw_readl(REG_DISP_AHB_AHB_EB);
	printf("DISPC EB %x %x\n",REG_DISP_AHB_AHB_EB,reg);
	__raw_bits_or(BIT_DISP_AHB_DISPC_MTX_FORCE_CKG_EN |
			BIT_DISP_AHB_DISPC_MTX_AUTO_CKG_EN |
			BIT_DISP_AHB_DISPC_NOC_AUTO_CKG_EN |
			BIT_DISP_AHB_DISPC_NOC_FORCE_CKG_EN, REG_DISP_AHB_GEN_CKG_CFG);
	reg =  __raw_readl(REG_DISP_AHB_GEN_CKG_CFG);
	printf("DISPC REG_DISP_AHB_GEN_CKG_CFG %x %x\n",REG_DISP_AHB_GEN_CKG_CFG,reg);
	__raw_bits_or(1<<19 | 1<<20, REG_AON_APB_RES_REG0);
	__raw_bits_or(BIT_PUB_APB_PUB0_RF_CHN_HW_LP_EN_2, REG_PUB_APB_PUB0_PUB_CHN2_LP_CTRL);
}

void dispc_print_clk(void)
{
#if 1
	FB_PRINT("0xe42b0094 = 0x%x\n", __raw_readl(0xe42b0094));
	FB_PRINT("0xe42b009c = 0x%x\n", __raw_readl(0xe42b009c));
	FB_PRINT("0xe42e0004 = 0x%x\n", __raw_readl(0xe42e0004));
	FB_PRINT("0xE7B00000 = 0x%x\n", __raw_readl(0xE7B00000));
	FB_PRINT("0xd3100000 = 0x%x\n", __raw_readl(0xd3100000));
	FB_PRINT("0xd3100008 = 0x%x\n", __raw_readl(0xd3100008));
	FB_PRINT("0xd2100000 = 0x%x\n", __raw_readl(0xd2100000));
	FB_PRINT("0xd3000020 = 0x%x\n", __raw_readl(0xd3000020));
	FB_PRINT("0xd3000024 = 0x%x\n", __raw_readl(0xd3000024));
	FB_PRINT("0xd3000028 = 0x%x\n", __raw_readl(0xd3000028));
	FB_PRINT("0xd2100064 = 0x%x\n", __raw_readl(0xd2100064));
#endif
}


