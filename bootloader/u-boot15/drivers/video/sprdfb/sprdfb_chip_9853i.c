/******************************************************************************
 ** File Name:    sprdfb_chip_9851.c                                *
 ** Author:       billly.zhang                                      *
 ** DATE:         07/11/2016                                        *
 ** Copyright:    2016 Spreatrum, Incoporated. All Rights Reserved. *
 ** Description:                                                    *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                               *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                       *

 ******************************************************************************/

#include "sprdfb_chip_common.h"
#include "sprdfb_chip_9853i.h"
#include "sprdfb.h"

#define  PRINT(fmt, args...) printf("[%20s] <%d> "fmt, __FUNCTION__, __LINE__, ##args)
#define  REG_DUMP(r)  PRINT(#r" (0x%x) = 0x%x\n", r, __raw_readl(r))

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
	int mask, value;

	mask = BIT_PMU_APB_PD_CAM_SYS_FORCE_SHUTDOWN;
	value = ~mask;
	REG_DUMP(REG_PMU_APB_PD_CAM_SYS_PWR_CFG);
	__raw_bits_and(value, REG_PMU_APB_PD_CAM_SYS_PWR_CFG);
	REG_DUMP(REG_PMU_APB_PD_CAM_SYS_PWR_CFG);
	mdelay(10);

	return 0;
}

void dsi_enable(void)
{
	int mask, value;

	__raw_bits_or(BIT_PMU_APB_DSPLL_FRC_ON, REG_PMU_APB_DSPLL_REL_CFG);
	REG_DUMP(REG_PMU_APB_DSPLL_REL_CFG);
	mask = BIT_DISP_AHB_DSI0_EB
		|BIT_DISP_AHB_DHY0_CFG_CKG_EN;
	value = mask;
	__raw_bits_or(value, REG_DISP_AHB_AHB_EB);
	__raw_writel((0x39 <<16)|(0x87 << 0), REG_DISP_AHB_DSI_CTRL);
}

void dsi_disable(void)
{
}

void dispc_early_configs(void)
{
	int mask, value;

	disp_domain_power_ctrl(1);

	mask =	BIT_AON_APB_AON_DISP_EB |
		BIT_AON_APB_AON_CAM_EB |
		BIT_AON_APB_DISP_EMC_EB;
	value = mask;
	__raw_bits_or(value, REG_AON_APB_APB_EB1);
	REG_DUMP(REG_AON_APB_APB_EB1);

	REG_DUMP(0xe42b0128);

	REG_DUMP(REG_DISP_AHB_AHB_EB);
	/* 0xd3100000 bit 0/1/2/3/4 */
	mask = BIT_DISP_AHB_DISPC0_EB
		| BIT_DISP_AHB_DSI0_EB
		| BIT_DISP_AHB_CKG_EB
		| BIT_DISP_AHB_SYS_MTX_EB
		| BIT_DISP_AHB_DHY0_CFG_CKG_EN;
	value = mask;

	__raw_bits_or(value, REG_DISP_AHB_AHB_EB);
	REG_DUMP(REG_DISP_AHB_AHB_EB);
}

void dispc_print_clk(void)
{
	REG_DUMP(0xd3000020);
	REG_DUMP(0xd3000024);
	REG_DUMP(0xd3000028);
}
