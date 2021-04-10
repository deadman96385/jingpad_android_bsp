/*
 * Copyright (C) 2018 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-11-07 10:41:46
 *
 */


#ifndef MM_CLK_CORE_H
#define MM_CLK_CORE_H

#define CTL_BASE_MM_CLK_CORE 0x62100000


#define REG_MM_CLK_CORE_CGM_MM_AHB_CFG             ( CTL_BASE_MM_CLK_CORE + 0x0020 )
#define REG_MM_CLK_CORE_CGM_MM_MTX_CFG             ( CTL_BASE_MM_CLK_CORE + 0x0024 )
#define REG_MM_CLK_CORE_CGM_SENSOR0_CFG            ( CTL_BASE_MM_CLK_CORE + 0x0028 )
#define REG_MM_CLK_CORE_CGM_SENSOR1_CFG            ( CTL_BASE_MM_CLK_CORE + 0x002C )
#define REG_MM_CLK_CORE_CGM_SENSOR2_CFG            ( CTL_BASE_MM_CLK_CORE + 0x0030 )
#define REG_MM_CLK_CORE_CGM_CPP_CFG                ( CTL_BASE_MM_CLK_CORE + 0x0034 )
#define REG_MM_CLK_CORE_CGM_JPG_CFG                ( CTL_BASE_MM_CLK_CORE + 0x0038 )
#define REG_MM_CLK_CORE_CGM_FD_CFG                 ( CTL_BASE_MM_CLK_CORE + 0x003C )
#define REG_MM_CLK_CORE_CGM_DCAM_IF_CFG            ( CTL_BASE_MM_CLK_CORE + 0x0040 )
#define REG_MM_CLK_CORE_CGM_DCAM_AXI_CFG           ( CTL_BASE_MM_CLK_CORE + 0x0044 )
#define REG_MM_CLK_CORE_CGM_ISP_CFG                ( CTL_BASE_MM_CLK_CORE + 0x0048 )
#define REG_MM_CLK_CORE_CGM_MIPI_CSI0_CFG          ( CTL_BASE_MM_CLK_CORE + 0x004C )
#define REG_MM_CLK_CORE_CGM_MIPI_CSI1_CFG          ( CTL_BASE_MM_CLK_CORE + 0x0050 )
#define REG_MM_CLK_CORE_CGM_MIPI_CSI2_CFG          ( CTL_BASE_MM_CLK_CORE + 0x0054 )
#define REG_MM_CLK_CORE_CGM_CPHY_CFG_CFG           ( CTL_BASE_MM_CLK_CORE + 0x0058 )
#define REG_MM_CLK_CORE_CGM_CSI_PHY_SCAN_ONLY_CFG  ( CTL_BASE_MM_CLK_CORE + 0x005C )

/* REG_MM_CLK_CORE_CGM_MM_AHB_CFG */

#define BIT_MM_CLK_CORE_CGM_MM_AHB_CFG_CGM_MM_AHB_SEL(x)                     (((x) & 0x3))

/* REG_MM_CLK_CORE_CGM_MM_MTX_CFG */

#define BIT_MM_CLK_CORE_CGM_MM_MTX_CFG_CGM_MM_MTX_SEL(x)                     (((x) & 0x7))

/* REG_MM_CLK_CORE_CGM_SENSOR0_CFG */

#define BIT_MM_CLK_CORE_CGM_SENSOR0_CFG_CGM_SENSOR0_DIV(x)                   (((x) & 0x7) << 8)
#define BIT_MM_CLK_CORE_CGM_SENSOR0_CFG_CGM_SENSOR0_SEL(x)                   (((x) & 0x3))

/* REG_MM_CLK_CORE_CGM_SENSOR1_CFG */

#define BIT_MM_CLK_CORE_CGM_SENSOR1_CFG_CGM_SENSOR1_DIV(x)                   (((x) & 0x7) << 8)
#define BIT_MM_CLK_CORE_CGM_SENSOR1_CFG_CGM_SENSOR1_SEL(x)                   (((x) & 0x3))

/* REG_MM_CLK_CORE_CGM_SENSOR2_CFG */

#define BIT_MM_CLK_CORE_CGM_SENSOR2_CFG_CGM_SENSOR2_DIV(x)                   (((x) & 0x7) << 8)
#define BIT_MM_CLK_CORE_CGM_SENSOR2_CFG_CGM_SENSOR2_SEL(x)                   (((x) & 0x3))

/* REG_MM_CLK_CORE_CGM_CPP_CFG */

#define BIT_MM_CLK_CORE_CGM_CPP_CFG_CGM_CPP_SEL(x)                           (((x) & 0x3))

/* REG_MM_CLK_CORE_CGM_JPG_CFG */

#define BIT_MM_CLK_CORE_CGM_JPG_CFG_CGM_JPG_SEL(x)                           (((x) & 0x3))

/* REG_MM_CLK_CORE_CGM_FD_CFG */

#define BIT_MM_CLK_CORE_CGM_FD_CFG_CGM_FD_SEL(x)                             (((x) & 0x3))

/* REG_MM_CLK_CORE_CGM_DCAM_IF_CFG */

#define BIT_MM_CLK_CORE_CGM_DCAM_IF_CFG_CGM_DCAM_IF_SEL(x)                   (((x) & 0x3))

/* REG_MM_CLK_CORE_CGM_DCAM_AXI_CFG */

#define BIT_MM_CLK_CORE_CGM_DCAM_AXI_CFG_CGM_DCAM_AXI_SEL(x)                 (((x) & 0x3))

/* REG_MM_CLK_CORE_CGM_ISP_CFG */

#define BIT_MM_CLK_CORE_CGM_ISP_CFG_CGM_ISP_SEL(x)                           (((x) & 0x3))

/* REG_MM_CLK_CORE_CGM_MIPI_CSI0_CFG */

#define BIT_MM_CLK_CORE_CGM_MIPI_CSI0_CFG_CGM_MIPI_CSI0_PAD_SEL              BIT(16)
#define BIT_MM_CLK_CORE_CGM_MIPI_CSI0_CFG_CGM_MIPI_CSI0_SEL(x)               (((x) & 0x7))

/* REG_MM_CLK_CORE_CGM_MIPI_CSI1_CFG */

#define BIT_MM_CLK_CORE_CGM_MIPI_CSI1_CFG_CGM_MIPI_CSI1_PAD_SEL              BIT(16)
#define BIT_MM_CLK_CORE_CGM_MIPI_CSI1_CFG_CGM_MIPI_CSI1_SEL(x)               (((x) & 0x7))

/* REG_MM_CLK_CORE_CGM_MIPI_CSI2_CFG */

#define BIT_MM_CLK_CORE_CGM_MIPI_CSI2_CFG_CGM_MIPI_CSI2_PAD_SEL              BIT(16)
#define BIT_MM_CLK_CORE_CGM_MIPI_CSI2_CFG_CGM_MIPI_CSI2_SEL(x)               (((x) & 0x7))

/* REG_MM_CLK_CORE_CGM_CPHY_CFG_CFG */

#define BIT_MM_CLK_CORE_CGM_CPHY_CFG_CFG_CGM_CPHY_CFG_SEL                    BIT(0)

/* REG_MM_CLK_CORE_CGM_CSI_PHY_SCAN_ONLY_CFG */

#define BIT_MM_CLK_CORE_CGM_CSI_PHY_SCAN_ONLY_CFG_CGM_CSI_PHY_SCAN_ONLY_SEL  BIT(0)


#endif /* MM_CLK_CORE_H */


