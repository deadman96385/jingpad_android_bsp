/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _DISP_AHB_REG_H
#define _DISP_AHB_REG_H

#define CTL_BASE_DISP_AHB SPRD_DISPAHB_BASE


#define REG_DISP_AHB_AHB_EB      ( CTL_BASE_DISP_AHB + 0x0000 )
#define REG_DISP_AHB_DSI_CTRL    ( CTL_BASE_DISP_AHB + 0x0004 )
#define REG_DISP_AHB_CACHE_CFG   ( CTL_BASE_DISP_AHB + 0x0008 )

/*---------------------------------------------------------------------------
// Register Name   : REG_DISP_AHB_AHB_EB
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DISP_AHB_QOS_AR_DISPC(x)                     (((x) & 0xF) << 12)
#define BIT_DISP_AHB_QOS_AW_DISPC(x)                     (((x) & 0xF) << 8)
#define BIT_DISP_AHB_CKG_SOFT_RST                        BIT(7)
#define BIT_DISP_AHB_DSI0_SOFT_RST                       BIT(6)
#define BIT_DISP_AHB_DISPC0_SOFT_RST                     BIT(5)
#define BIT_DISP_AHB_DHY0_CFG_CKG_EN                     BIT(4)
#define BIT_DISP_AHB_SYS_MTX_EB                          BIT(3)
#define BIT_DISP_AHB_CKG_EB                              BIT(2)
#define BIT_DISP_AHB_DSI0_EB                             BIT(1)
#define BIT_DISP_AHB_DISPC0_EB                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_DISP_AHB_DSI_CTRL
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DISP_AHB_DSI0_DLN_TIMER_VALUE(x)             (((x) & 0x1FF) << 16)
#define BIT_DISP_AHB_DSI0_CLN_TIMER_VALUE(x)             (((x) & 0x1FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DISP_AHB_CACHE_CFG
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DISP_AHB_ARCACHE_DPU(x)                      (((x) & 0xF) << 4)
#define BIT_DISP_AHB_AWCACHE_DPU(x)                      (((x) & 0xF))


#endif // _DISP_AHB_REG_H
