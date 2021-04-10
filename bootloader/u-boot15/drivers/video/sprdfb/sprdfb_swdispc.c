/******************************************************************************
 ** File Name:    sprdfb_dispc.c                                            *
 ** Author:                                                           *
 ** DATE:                                                           *
 ** Copyright:    2005 Spreatrum, Incoporated. All Rights Reserved.           *
 ** Description:                                                            *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                                         *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                                 *
 **
 ******************************************************************************/

#include "sprdfb_chip_common.h"
#include "sprdfb.h"
#include "sprdfb_panel.h"

extern int32_t sprdfb_spi_refresh(struct sprdfb_device *dev);

struct display_ctrl sprdfb_swdispc_ctrl = {
	.name		= "swdispc",
	.early_init	= NULL,
	.init		= NULL,
	.uninit		= NULL,
	.refresh	= sprdfb_spi_refresh,
	.update_clk     = NULL,
};

