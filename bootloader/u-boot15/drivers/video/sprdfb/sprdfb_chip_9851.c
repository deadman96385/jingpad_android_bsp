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
#include "sprdfb.h"

#define BIT(x)  (1<<x)

void dsi_enable(void)
{
	__raw_bits_or(DSI_BIT_EB, DSI_REG_EB);
	__raw_bits_and(~(BIT_MIPI_DSI_PS_PD_S),DPHY_PW_CONFIG_REG);
	udelay(10);
	__raw_bits_and(~(BIT_MIPI_DSI_PS_PD_L),DPHY_PW_CONFIG_REG);
	__raw_bits_or(BIT_DPHY_REF_CKG_EN|BIT_DPHY_CFG_CKG_EN,DPHY_CKG_EN);
	__raw_bits_or(BIT(27)|BIT(28),0x40353034);
	__raw_bits_and(~(BIT(20)|BIT(21)) ,0x40353020);
	__raw_bits_or(BIT(14),0x40353034);
	__raw_bits_or(BIT(16),0x40353024);

	__raw_bits_or(BIT(25)|BIT(26),0x40353034);
	__raw_bits_and(~(BIT(18)|BIT(19)) ,0x40353020);
	mdelay(3);
	__raw_bits_or(BIT(18)|BIT(19),0x40353020);

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


