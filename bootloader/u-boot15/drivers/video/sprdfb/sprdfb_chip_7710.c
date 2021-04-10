/******************************************************************************
 ** File Name:    sprdfb_chip_7710.c                                     *
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


#include "sprdfb_chip_7710.h"
#include "sprdfb_chip_common.h"
#include "sprdfb.h"


void dispc_print_clk(void)
{
	FB_PRINT("0x2090023c = 0x%x\n", __raw_readl(0x2090023c));
}



