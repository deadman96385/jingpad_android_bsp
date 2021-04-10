/*
 * Copyright (C) 2019 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2019-01-07 15:09:47
 *
 */


#ifndef MM_CLK_CORE_H
#define MM_CLK_CORE_H

#define CTL_BASE_MM_CLK_CORE 0x60E00000


#define REG_MM_CLK_CORE_CGM_MM_AHB_CFG             ( CTL_BASE_MM_CLK_CORE + 0x0020 )
#define REG_MM_CLK_CORE_CGM_SENSOR0_CFG            ( CTL_BASE_MM_CLK_CORE + 0x0024 )
#define REG_MM_CLK_CORE_CGM_SENSOR1_CFG            ( CTL_BASE_MM_CLK_CORE + 0x0028 )
#define REG_MM_CLK_CORE_CGM_DCAM_IF_CFG            ( CTL_BASE_MM_CLK_CORE + 0x002C )
#define REG_MM_CLK_CORE_CGM_JPG_CFG                ( CTL_BASE_MM_CLK_CORE + 0x0030 )
#define REG_MM_CLK_CORE_CGM_MIPI_CSI_CFG           ( CTL_BASE_MM_CLK_CORE + 0x0034 )
#define REG_MM_CLK_CORE_CGM_CPHY_CFG_CFG           ( CTL_BASE_MM_CLK_CORE + 0x0038 )
#define REG_MM_CLK_CORE_CGM_MIPI_CSI_S_CFG         ( CTL_BASE_MM_CLK_CORE + 0x003C )
#define REG_MM_CLK_CORE_CGM_CSI_PHY_SCAN_ONLY_CFG  ( CTL_BASE_MM_CLK_CORE + 0x0040 )
#define REG_MM_CLK_CORE_CGM_CCIR_P_CFG             ( CTL_BASE_MM_CLK_CORE + 0x0044 )

/* REG_MM_CLK_CORE_CGM_MM_AHB_CFG */

#define BIT_MM_CLK_CORE_CGM_MM_AHB_CFG_CGM_MM_AHB_SEL(x)                     (((x) & 0x3))

/* REG_MM_CLK_CORE_CGM_SENSOR0_CFG */

#define BIT_MM_CLK_CORE_CGM_SENSOR0_CFG_CGM_SENSOR0_DIV(x)                   (((x) & 0x7) << 8)
#define BIT_MM_CLK_CORE_CGM_SENSOR0_CFG_CGM_SENSOR0_SEL(x)                   (((x) & 0x3))

/* REG_MM_CLK_CORE_CGM_SENSOR1_CFG */

#define BIT_MM_CLK_CORE_CGM_SENSOR1_CFG_CGM_SENSOR1_DIV(x)                   (((x) & 0x7) << 8)
#define BIT_MM_CLK_CORE_CGM_SENSOR1_CFG_CGM_SENSOR1_SEL(x)                   (((x) & 0x3))

/* REG_MM_CLK_CORE_CGM_DCAM_IF_CFG */

#define BIT_MM_CLK_CORE_CGM_DCAM_IF_CFG_CGM_DCAM_IF_SEL(x)                   (((x) & 0x7))

/* REG_MM_CLK_CORE_CGM_JPG_CFG */

#define BIT_MM_CLK_CORE_CGM_JPG_CFG_CGM_JPG_SEL(x)                           (((x) & 0x3))

/* REG_MM_CLK_CORE_CGM_MIPI_CSI_CFG */

#define BIT_MM_CLK_CORE_CGM_MIPI_CSI_CFG_CGM_MIPI_CSI_PAD_SEL                BIT(16)
#define BIT_MM_CLK_CORE_CGM_MIPI_CSI_CFG_CGM_MIPI_CSI_SEL(x)                 (((x) & 0x3))

/* REG_MM_CLK_CORE_CGM_CPHY_CFG_CFG */

#define BIT_MM_CLK_CORE_CGM_CPHY_CFG_CFG_CGM_CPHY_CFG_SEL                    BIT(0)

/* REG_MM_CLK_CORE_CGM_MIPI_CSI_S_CFG */

#define BIT_MM_CLK_CORE_CGM_MIPI_CSI_S_CFG_CGM_MIPI_CSI_S_PAD_SEL            BIT(16)
#define BIT_MM_CLK_CORE_CGM_MIPI_CSI_S_CFG_CGM_MIPI_CSI_S_SEL(x)             (((x) & 0x3))

/* REG_MM_CLK_CORE_CGM_CSI_PHY_SCAN_ONLY_CFG */

#define BIT_MM_CLK_CORE_CGM_CSI_PHY_SCAN_ONLY_CFG_CGM_CSI_PHY_SCAN_ONLY_SEL  BIT(0)

/* REG_MM_CLK_CORE_CGM_CCIR_P_CFG */

#define BIT_MM_CLK_CORE_CGM_CCIR_P_CFG_CGM_CCIR_P_PAD_SEL                    BIT(16)
#define BIT_MM_CLK_CORE_CGM_CCIR_P_CFG_CGM_CCIR_P_SEL                        BIT(0)


#endif /* MM_CLK_CORE_H */


