/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _MM_CLK_CORE_REG_H
#define _MM_CLK_CORE_REG_H

#define CTL_BASE_MM_CLK_CORE 0x60E00000


#define REG_MM_CLK_CORE_CGM_MM_AHB_CFG      ( CTL_BASE_MM_CLK_CORE + 0x0020 )
#define REG_MM_CLK_CORE_CGM_SENSOR0_CFG     ( CTL_BASE_MM_CLK_CORE + 0x0024 )
#define REG_MM_CLK_CORE_CGM_SENSOR1_CFG     ( CTL_BASE_MM_CLK_CORE + 0x0028 )
#define REG_MM_CLK_CORE_CGM_DCAM_IF_CFG     ( CTL_BASE_MM_CLK_CORE + 0x002C )
#define REG_MM_CLK_CORE_CGM_VSP_CFG         ( CTL_BASE_MM_CLK_CORE + 0x0030 )
#define REG_MM_CLK_CORE_CGM_ISP_CFG         ( CTL_BASE_MM_CLK_CORE + 0x0034 )
#define REG_MM_CLK_CORE_CGM_JPG_CFG         ( CTL_BASE_MM_CLK_CORE + 0x0038 )
#define REG_MM_CLK_CORE_CGM_MIPI_CSI_CFG    ( CTL_BASE_MM_CLK_CORE + 0x003C )
#define REG_MM_CLK_CORE_CGM_CPP_CFG         ( CTL_BASE_MM_CLK_CORE + 0x0040 )
#define REG_MM_CLK_CORE_CGM_MIPI_CSI_S_CFG  ( CTL_BASE_MM_CLK_CORE + 0x0044 )

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_CLK_CORE_CGM_MM_AHB_CFG
// Register Offset : 0x0020
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_CLK_CORE_CGM_MM_AHB_CFG_CGM_MM_AHB_SEL(x)                            (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_CLK_CORE_CGM_SENSOR0_CFG
// Register Offset : 0x0024
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_CLK_CORE_CGM_SENSOR0_CFG_CGM_SENSOR0_DIV(x)                          (((x) & 0x7) << 8)
#define BIT_MM_CLK_CORE_CGM_SENSOR0_CFG_CGM_SENSOR0_SEL(x)                          (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_CLK_CORE_CGM_SENSOR1_CFG
// Register Offset : 0x0028
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_CLK_CORE_CGM_SENSOR1_CFG_CGM_SENSOR1_DIV(x)                          (((x) & 0x7) << 8)
#define BIT_MM_CLK_CORE_CGM_SENSOR1_CFG_CGM_SENSOR1_SEL(x)                          (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_CLK_CORE_CGM_DCAM_IF_CFG
// Register Offset : 0x002C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_CLK_CORE_CGM_DCAM_IF_CFG_CGM_DCAM_IF_SEL(x)                          (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_CLK_CORE_CGM_VSP_CFG
// Register Offset : 0x0030
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_CLK_CORE_CGM_VSP_CFG_CGM_VSP_SEL(x)                                  (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_CLK_CORE_CGM_ISP_CFG
// Register Offset : 0x0034
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_CLK_CORE_CGM_ISP_CFG_CGM_ISP_SEL(x)                                  (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_CLK_CORE_CGM_JPG_CFG
// Register Offset : 0x0038
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_CLK_CORE_CGM_JPG_CFG_CGM_JPG_SEL(x)                                  (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_CLK_CORE_CGM_MIPI_CSI_CFG
// Register Offset : 0x003C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_CLK_CORE_CGM_MIPI_CSI_CFG_CGM_MIPI_CSI_PAD_SEL                       BIT(16)
#define BIT_MM_CLK_CORE_CGM_MIPI_CSI_CFG_CGM_MIPI_CSI_SEL                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_CLK_CORE_CGM_CPP_CFG
// Register Offset : 0x0040
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_CLK_CORE_CGM_CPP_CFG_CGM_CPP_SEL(x)                                  (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_CLK_CORE_CGM_MIPI_CSI_S_CFG
// Register Offset : 0x0044
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_CLK_CORE_CGM_MIPI_CSI_S_CFG_CGM_MIPI_CSI_S_PAD_SEL                   BIT(16)
#define BIT_MM_CLK_CORE_CGM_MIPI_CSI_S_CFG_CGM_MIPI_CSI_S_SEL                       BIT(0)


#endif // _MM_CLK_CORE_REG_H
