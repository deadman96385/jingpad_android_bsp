/******************************************************************************
 ** File Name:    sprdfb_chip_8825.c                                     *
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


#include "sprdfb_chip_8825.h"
#include "sprdfb_chip_common.h"
#include "sprdfb.h"


void dsi_enable(void)
{
	__raw_bits_or(DSI_BIT_EB, DSI_REG_EB);  //enable dphy
}

void dispc_print_clk(void)
{
	FB_PRINT("0x20900200 = 0x%x\n", __raw_readl(0x20900200));
	FB_PRINT("0x20900208 = 0x%x\n", __raw_readl(0x20900208));
	FB_PRINT("0x20900220 = 0x%x\n", __raw_readl(0x20900220));
}



