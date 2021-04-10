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
#include "sprdfb_chip_9833.h"
#include "sprdfb.h"


void dsi_enable(void)
{
	__raw_bits_or(DSI_BIT_EB, DSI_REG_EB);
	__raw_bits_and(~(BIT_MIPI_DSI_PS_PD_S),DPHY_PW_CONFIG_REG);
	udelay(10);
	__raw_bits_and(~(BIT_MIPI_DSI_PS_PD_L),DPHY_PW_CONFIG_REG);
	__raw_bits_or(BIT_DPHY_REF_CKG_EN|BIT_DPHY_CFG_CKG_EN,DPHY_CKG_EN);

}

void dsi_disable(void)
{
	__raw_bits_and(~DSI_BIT_EB, DSI_REG_EB);
}


void dispc_print_clk(void)
{
	FB_PRINT("dispc_print_clk\n");
}


void dispc_early_configs(void)
{
	__raw_bits_or(BIT(1),G_DISPC_AHB_BASE);
}


