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

#define CTL_BASE_CAM_CLK SPRD_DCAMPCKG_BASE


#define REG_CAM_CLK_CGM_AHB_DISP_CFG       ( CTL_BASE_CAM_CLK + 0x0020 )
#define REG_CAM_CLK_CGM_DISPC0_CFG         ( CTL_BASE_CAM_CLK + 0x0024 )
#define REG_CAM_CLK_CGM_DISPC0_DPI_CFG     ( CTL_BASE_CAM_CLK + 0x0028 )
#define REG_CAM_CLK_CGM_DISPC1_CFG         ( CTL_BASE_CAM_CLK + 0x002C )
#define REG_CAM_CLK_CGM_DISPC1_DPI_CFG     ( CTL_BASE_CAM_CLK + 0x0030 )
#define REG_CAM_CLK_CGM_DSI0_RXESC_CFG     ( CTL_BASE_CAM_CLK + 0x0034 )
#define REG_CAM_CLK_CGM_DSI0_LANEBYTE_CFG  ( CTL_BASE_CAM_CLK + 0x0038 )
#define REG_CAM_CLK_CGM_DPHY0_CFG_CFG      ( CTL_BASE_CAM_CLK + 0x003C )
#define REG_CAM_CLK_CGM_DSI1_RXESC_CFG     ( CTL_BASE_CAM_CLK + 0x0040 )
#define REG_CAM_CLK_CGM_DSI1_LANEBYTE_CFG  ( CTL_BASE_CAM_CLK + 0x0044 )
#define REG_CAM_CLK_CGM_DPHY1_CFG_CFG      ( CTL_BASE_CAM_CLK + 0x0048 )
#define REG_CAM_CLK_CGM_DISP_MTX_CFG       ( CTL_BASE_CAM_CLK + 0x004C )
#define REG_CAM_CLK_CGM_SYS_MTX_CFG        ( CTL_BASE_CAM_CLK + 0x0050 )
#define REG_CAM_CLK_CGM_SENSOR0_CFG        ( CTL_BASE_CAM_CLK + 0x0054 )
#define REG_CAM_CLK_CGM_SENSOR1_CFG        ( CTL_BASE_CAM_CLK + 0x0058 )
#define REG_CAM_CLK_CGM_SENSOR2_CFG        ( CTL_BASE_CAM_CLK + 0x005C )
#define REG_CAM_CLK_CGM_DCAM0_CFG          ( CTL_BASE_CAM_CLK + 0x0060 )
#define REG_CAM_CLK_CGM_DCAM1_CFG          ( CTL_BASE_CAM_CLK + 0x0064 )
#define REG_CAM_CLK_CGM_DCAM0_IF_CFG       ( CTL_BASE_CAM_CLK + 0x0068 )
#define REG_CAM_CLK_CGM_JPG0_CFG           ( CTL_BASE_CAM_CLK + 0x006C )
#define REG_CAM_CLK_CGM_JPG1_CFG           ( CTL_BASE_CAM_CLK + 0x0070 )
#define REG_CAM_CLK_CGM_MIPI_CSI0_CFG      ( CTL_BASE_CAM_CLK + 0x0074 )
#define REG_CAM_CLK_CGM_MIPI_CSI1_CFG      ( CTL_BASE_CAM_CLK + 0x0078 )
#define REG_CAM_CLK_CGM_CPHY0_CFG_CFG      ( CTL_BASE_CAM_CLK + 0x007C )
#define REG_CAM_CLK_CGM_CPHY1_CFG_CFG      ( CTL_BASE_CAM_CLK + 0x0080 )
#define REG_CAM_CLK_CGM_CAM_MTX_CFG        ( CTL_BASE_CAM_CLK + 0x0084 )
#define REG_CAM_CLK_CGM_CPP_CFG            ( CTL_BASE_CAM_CLK + 0x0088 )
#define REG_CAM_CLK_CGM_ISP_MCK_CFG        ( CTL_BASE_CAM_CLK + 0x008C )
#define REG_CAM_CLK_CGM_ISP_PCK_CFG        ( CTL_BASE_CAM_CLK + 0x0090 )
#define REG_CAM_CLK_CGM_ISP_ICK_CFG        ( CTL_BASE_CAM_CLK + 0x0094 )
#define REG_CAM_CLK_CGM_ISP_LCK_CFG        ( CTL_BASE_CAM_CLK + 0x0098 )
#define REG_CAM_CLK_CGM_CI_ISP0_CFG        ( CTL_BASE_CAM_CLK + 0x009C )
#define REG_CAM_CLK_CGM_CI_ISP1_CFG        ( CTL_BASE_CAM_CLK + 0x00A0 )
#define REG_CAM_CLK_CGM_CI_ISP2_CFG        ( CTL_BASE_CAM_CLK + 0x00A4 )
#define REG_CAM_CLK_ISP_JTAG_TCK_CFG       ( CTL_BASE_CAM_CLK + 0x00A8 )

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_AHB_DISP_CFG
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_AHB_DISP_SEL(x)                     (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_DISPC0_CFG
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_DISPC0_SEL(x)                       (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_DISPC0_DPI_CFG
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_DISPC0_DPI_DIV(x)                   (((x) & 0x7) << 8)
#define BIT_CAM_CLK_CGM_DISPC0_DPI_SEL(x)                   (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_DISPC1_CFG
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_DISPC1_SEL(x)                       (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_DISPC1_DPI_CFG
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_DISPC1_DPI_DIV(x)                   (((x) & 0x7) << 8)
#define BIT_CAM_CLK_CGM_DISPC1_DPI_SEL(x)                   (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_DSI0_RXESC_CFG
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_DSI0_RXESC_PAD_SEL                  BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_DSI0_LANEBYTE_CFG
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_DSI0_LANEBYTE_PAD_SEL               BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_DPHY0_CFG_CFG
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_DPHY0_CFG_SEL                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_DSI1_RXESC_CFG
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_DSI1_RXESC_PAD_SEL                  BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_DSI1_LANEBYTE_CFG
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_DSI1_LANEBYTE_PAD_SEL               BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_DPHY1_CFG_CFG
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_DPHY1_CFG_SEL                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_DISP_MTX_CFG
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_DISP_MTX_SEL(x)                     (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_SYS_MTX_CFG
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_SYS_MTX_SEL(x)                      (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_SENSOR0_CFG
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_SENSOR0_DIV(x)                      (((x) & 0x7) << 8)
#define BIT_CAM_CLK_CGM_SENSOR0_SEL(x)                      (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_SENSOR1_CFG
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_SENSOR1_DIV(x)                      (((x) & 0x7) << 8)
#define BIT_CAM_CLK_CGM_SENSOR1_SEL(x)                      (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_SENSOR2_CFG
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_SENSOR2_DIV(x)                      (((x) & 0x7) << 8)
#define BIT_CAM_CLK_CGM_SENSOR2_SEL(x)                      (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_DCAM0_CFG
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_DCAM0_SEL(x)                        (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_DCAM1_CFG
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_DCAM1_SEL(x)                        (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_DCAM0_IF_CFG
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_DCAM0_IF_SEL(x)                     (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_JPG0_CFG
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_JPG0_SEL(x)                         (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_JPG1_CFG
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_JPG1_SEL(x)                         (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_MIPI_CSI0_CFG
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_MIPI_CSI0_PAD_SEL                   BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_MIPI_CSI1_CFG
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_MIPI_CSI1_PAD_SEL                   BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_CPHY0_CFG_CFG
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_CPHY0_CFG_SEL                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_CPHY1_CFG_CFG
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_CPHY1_CFG_SEL                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_CAM_MTX_CFG
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_CAM_MTX_SEL(x)                      (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_CPP_CFG
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_CPP_SEL(x)                          (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_ISP_MCK_CFG
// Register Offset : 0x008C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_ISP_MCK_SEL(x)                      (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_ISP_PCK_CFG
// Register Offset : 0x0090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_ISP_PCK_SEL(x)                      (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_ISP_ICK_CFG
// Register Offset : 0x0094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_ISP_ICK_SEL(x)                      (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_ISP_LCK_CFG
// Register Offset : 0x0098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_ISP_LCK_SEL(x)                      (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_CI_ISP0_CFG
// Register Offset : 0x009C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_CI_ISP0_SEL(x)                      (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_CI_ISP1_CFG
// Register Offset : 0x00A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_CI_ISP1_SEL(x)                      (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_CGM_CI_ISP2_CFG
// Register Offset : 0x00A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_CGM_CI_ISP2_SEL(x)                      (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_CLK_ISP_JTAG_TCK_CFG
// Register Offset : 0x00A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_CLK_ISP_JTAG_TCK_PAD_SEL                    BIT(16)


#endif // _CAM_CLK_REG_H
