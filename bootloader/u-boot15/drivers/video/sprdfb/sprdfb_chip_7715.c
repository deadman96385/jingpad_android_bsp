/******************************************************************************
 ** File Name:    sprdfb_chip_7715.c                                     *
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


#include "sprdfb_chip_7715.h"
#include "sprdfb_chip_common.h"


void dispc_print_clk(void)
{
	printf("0x7120002c = 0x%x\n", __raw_readl(0x7120002c));
	printf("0x71200030 = 0x%x\n", __raw_readl(0x71200030));
	printf("0x71200034 = 0x%x\n", __raw_readl(0x71200034));
	printf("0x20d00000 = 0x%x\n", __raw_readl(0x20d00000));
	printf("0x71300000 = 0x%x\n", __raw_readl(0x71300000));
	printf("0x402e0004 = 0x%x\n", __raw_readl(0x402e0004));
}




