/******************************************************************************
 ** File Name:    sprdfb_chip_8830.c                                     *
 ** Author:       congfu.zhao                                           *
 ** DATE:         30/04/2013                                        *
 ** Copyright:    2013 Spreatrum, Incoporated. All Rights Reserved. *
 ** Description:                                                    *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                               *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                       *

 ******************************************************************************/

#include "sprdfb_chip_common.h"
#include "sprdfb_chip_9630.h"
#include "sprdfb.h"


void dsi_enable(void)
{
	__raw_bits_or(DSI_BIT_EB, DSI_REG_EB);
	__raw_bits_and(~BIT_MIPI_DSI_PS_PD_S, REG_AON_APB_PWR_CTRL);
	__raw_bits_and(~BIT_MIPI_DSI_PS_PD_L, REG_AON_APB_PWR_CTRL);
	__raw_bits_or(BIT_DPHY_REF_CKG_EN, REG_AP_AHB_MISC_CKG_EN);
	__raw_bits_or(BIT_DPHY_CFG_CKG_EN, REG_AP_AHB_MISC_CKG_EN);
}

void dsi_disable(void)
{
	__raw_bits_or(BIT_MIPI_DSI_PS_PD_S, REG_AON_APB_PWR_CTRL);
	__raw_bits_or(BIT_MIPI_DSI_PS_PD_L, REG_AON_APB_PWR_CTRL);
	__raw_bits_and(~BIT_DPHY_REF_CKG_EN, REG_AP_AHB_MISC_CKG_EN);
	__raw_bits_and(~BIT_DPHY_CFG_CKG_EN, REG_AP_AHB_MISC_CKG_EN);

	__raw_bits_and(~DSI_BIT_EB, DSI_REG_EB);
}


void dispc_print_clk(void)
{
	FB_PRINT("0x7120002c = 0x%x\n", __raw_readl(0x7120002c));
	FB_PRINT("0x71200030 = 0x%x\n", __raw_readl(0x71200030));
	FB_PRINT("0x71200034 = 0x%x\n", __raw_readl(0x71200034));
	FB_PRINT("0x20d00000 = 0x%x\n", __raw_readl(0x20d00000));
	FB_PRINT("0x71300000 = 0x%x\n", __raw_readl(0x71300000));
	FB_PRINT("0x402e0004 = 0x%x\n", __raw_readl(0x402e0004));
}


void dispc_early_configs(void)
{
	__raw_bits_or(BIT_DISPC_CORE_EN, DISPC_CORE_EN);//core_clock_en 
	__raw_bits_or(BIT_DISPC_EMC_EN, DISPC_EMC_EN);  //matrix clock en 
	__raw_bits_or(BIT_DISPC_AHB_EN, DISPC_AHB_EN);//enable DISPC clock 
}


