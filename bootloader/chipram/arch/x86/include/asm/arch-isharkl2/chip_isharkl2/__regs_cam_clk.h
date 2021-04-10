/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _CAM_CLK_REG_H
#define _CAM_CLK_REG_H

#define CTL_BASE_CAM_CLK SPRD_CAMAHB_BASE


#define REG_CLKTOP_CGM_AHB_DISP_CFG       ( CTL_BASE_CAM_CLK + 0x0020 )
#define REG_CLKTOP_CGM_DISPC0_CFG         ( CTL_BASE_CAM_CLK + 0x0024 )
#define REG_CLKTOP_CGM_DISPC0_DPI_CFG     ( CTL_BASE_CAM_CLK + 0x0028 )
#define REG_CLKTOP_CGM_DSI0_RXESC_CFG     ( CTL_BASE_CAM_CLK + 0x002C )
#define REG_CLKTOP_CGM_DSI0_LANEBYTE_CFG  ( CTL_BASE_CAM_CLK + 0x0030 )
#define REG_CLKTOP_CGM_DPHY0_CFG_CFG      ( CTL_BASE_CAM_CLK + 0x0034 )
#define REG_CLKTOP_CGM_SYS_MTX_CFG        ( CTL_BASE_CAM_CLK + 0x0038 )
#define REG_CLKTOP_CGM_SENSOR0_CFG        ( CTL_BASE_CAM_CLK + 0x003C )
#define REG_CLKTOP_CGM_SENSOR1_CFG        ( CTL_BASE_CAM_CLK + 0x0040 )
#define REG_CLKTOP_CGM_DCAM0_IF_CFG       ( CTL_BASE_CAM_CLK + 0x0044 )
#define REG_CLKTOP_CGM_DCAM1_IF_CFG       ( CTL_BASE_CAM_CLK + 0x0048 )
#define REG_CLKTOP_CGM_JPG0_CFG           ( CTL_BASE_CAM_CLK + 0x004C )
#define REG_CLKTOP_CGM_MIPI_CSI0_CFG      ( CTL_BASE_CAM_CLK + 0x0050 )
#define REG_CLKTOP_CGM_MIPI_CSI1_CFG      ( CTL_BASE_CAM_CLK + 0x0054 )
#define REG_CLKTOP_CGM_CPHY0_CFG_CFG      ( CTL_BASE_CAM_CLK + 0x0058 )
#define REG_CLKTOP_CGM_CPHY1_CFG_CFG      ( CTL_BASE_CAM_CLK + 0x005C )
#define REG_CLKTOP_CGM_CAM_MTX_CFG        ( CTL_BASE_CAM_CLK + 0x0060 )
#define REG_CLKTOP_JPG_CPP_MTX_CFG        ( CTL_BASE_CAM_CLK + 0x0064 )
#define REG_CLKTOP_CGM_CPP_CFG            ( CTL_BASE_CAM_CLK + 0x0068 )
#define REG_CLKTOP_CGM_ISP_MCK_CFG        ( CTL_BASE_CAM_CLK + 0x006C )
#define REG_CLKTOP_CGM_ISP_ICK_CFG        ( CTL_BASE_CAM_CLK + 0x0070 )
#define REG_CLKTOP_CGM_ISP_MTX_CFG        ( CTL_BASE_CAM_CLK + 0x0074 )

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_AHB_DISP_CFG
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_AHB_DISP_SEL(x)                     (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_DISPC0_CFG
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_DISPC0_SEL(x)                       (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_DISPC0_DPI_CFG
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_DISPC0_DPI_DIV(x)                   (((x) & 0x7) << 8)
#define BIT_CGM_DISPC0_DPI_SEL(x)                   (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_DSI0_RXESC_CFG
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_DSI0_RXESC_PAD_SEL                  BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_DSI0_LANEBYTE_CFG
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_DSI0_LANEBYTE_PAD_SEL               BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_DPHY0_CFG_CFG
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_DPHY0_CFG_SEL                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_SYS_MTX_CFG
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_SYS_MTX_SEL(x)                      (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_SENSOR0_CFG
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_SENSOR0_DIV(x)                      (((x) & 0x7) << 8)
#define BIT_CGM_SENSOR0_SEL(x)                      (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_SENSOR1_CFG
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_SENSOR1_DIV(x)                      (((x) & 0x7) << 8)
#define BIT_CGM_SENSOR1_SEL(x)                      (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_DCAM0_IF_CFG
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_DCAM0_IF_SEL(x)                     (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_DCAM1_IF_CFG
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_DCAM1_IF_SEL(x)                     (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_JPG0_CFG
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_JPG0_SEL(x)                         (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_MIPI_CSI0_CFG
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_MIPI_CSI0_PAD_SEL                   BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_MIPI_CSI1_CFG
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_MIPI_CSI1_PAD_SEL                   BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_CPHY0_CFG_CFG
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_CPHY0_CFG_SEL                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_CPHY1_CFG_CFG
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_CPHY1_CFG_SEL                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_CAM_MTX_CFG
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_CAM_MTX_SEL(x)                      (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_JPG_CPP_MTX_CFG
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_JPG_CPP_MTX_SEL(x)                  (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_CPP_CFG
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_CPP_SEL(x)                          (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_ISP_MCK_CFG
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_ISP_MCK_SEL(x)                      (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_ISP_ICK_CFG
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_ISP_ICK_SEL(x)                      (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CLKTOP_CGM_ISP_MTX_CFG
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_ISP_MTX_SEL(x)                      (((x) & 0x3))


#endif // _CAM_CLK_REG_H
