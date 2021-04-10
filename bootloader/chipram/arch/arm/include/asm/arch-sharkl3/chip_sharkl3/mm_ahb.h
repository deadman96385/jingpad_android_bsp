/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2017-12-27 15:24:15
 *
 */


#ifndef MM_AHB_H
#define MM_AHB_H

#define CTL_BASE_MM_AHB 0x60800000


#define REG_MM_AHB_AHB_EB                ( CTL_BASE_MM_AHB + 0x0000 )
#define REG_MM_AHB_AHB_RST               ( CTL_BASE_MM_AHB + 0x0004 )
#define REG_MM_AHB_GEN_CKG_CFG           ( CTL_BASE_MM_AHB + 0x0008 )
#define REG_MM_AHB_MIPI_CSI2_CTRL        ( CTL_BASE_MM_AHB + 0x000C )
#define REG_MM_AHB_CGM_DCAM_FDIV         ( CTL_BASE_MM_AHB + 0x0010 )
#define REG_MM_AHB_CGM_BPC_FDIV          ( CTL_BASE_MM_AHB + 0x0014 )
#define REG_MM_AHB_CGM_ISP_FDIV          ( CTL_BASE_MM_AHB + 0x0018 )
#define REG_MM_AHB_LP_CTRL_DCAM          ( CTL_BASE_MM_AHB + 0x001C )
#define REG_MM_AHB_LP_CTRL_ISP           ( CTL_BASE_MM_AHB + 0x0020 )
#define REG_MM_AHB_LP_CTRL_MM_0          ( CTL_BASE_MM_AHB + 0x0024 )
#define REG_MM_AHB_LP_CTRL_MM_1          ( CTL_BASE_MM_AHB + 0x0028 )
#define REG_MM_AHB_LP_CTRL_ASYNC_BRIDGE  ( CTL_BASE_MM_AHB + 0x002C )
#define REG_MM_AHB_MTX_MOD_CTRL          ( CTL_BASE_MM_AHB + 0x0030 )

/* REG_MM_AHB_AHB_EB */

#define BIT_MM_AHB_CSI_T_EB                     BIT(5)
#define BIT_MM_AHB_CSI_S_EB                     BIT(4)
#define BIT_MM_AHB_CSI_EB                       BIT(3)
#define BIT_MM_AHB_ISP_EB                       BIT(2)
#define BIT_MM_AHB_DCAM_EB                      BIT(1)
#define BIT_MM_AHB_CKG_EB                       BIT(0)

/* REG_MM_AHB_AHB_RST */

#define BIT_MM_AHB_CSI_T_SOFT_RST               BIT(10)
#define BIT_MM_AHB_CSI_S_SOFT_RST               BIT(9)
#define BIT_MM_AHB_CSI_SOFT_RST                 BIT(8)
#define BIT_MM_AHB_ISP_LOG_SOFT_RST             BIT(7)
#define BIT_MM_AHB_DCAM_ALL_SOFT_RST            BIT(6)
#define BIT_MM_AHB_DCAM_AXIM_SOFT_RST           BIT(5)
#define BIT_MM_AHB_DCAM2_SOFT_RST               BIT(4)
#define BIT_MM_AHB_DCAM1_SOFT_RST               BIT(3)
#define BIT_MM_AHB_DCAM0_SOFT_RST               BIT(2)
#define BIT_MM_AHB_AXI_MM_EMC_SOFT_RST          BIT(1)
#define BIT_MM_AHB_CKG_SOFT_RST                 BIT(0)

/* REG_MM_AHB_GEN_CKG_CFG */

#define BIT_MM_AHB_CPHY_CFG_CKG_EN              BIT(8)
#define BIT_MM_AHB_SENSOR2_CKG_EN               BIT(7)
#define BIT_MM_AHB_SENSOR1_CKG_EN               BIT(6)
#define BIT_MM_AHB_SENSOR0_CKG_EN               BIT(5)
#define BIT_MM_AHB_MIPI_CSI_T_CKG_EN            BIT(4)
#define BIT_MM_AHB_MIPI_CSI_S_CKG_EN            BIT(3)
#define BIT_MM_AHB_MIPI_CSI_CKG_EN              BIT(2)
#define BIT_MM_AHB_ISP_AXI_CKG_EN               BIT(1)
#define BIT_MM_AHB_DCAM_AXI_CKG_EN              BIT(0)

/* REG_MM_AHB_MIPI_CSI2_CTRL */

#define BIT_MM_AHB_CSI_2P2L_TESTDOUT_MS_SEL(x)  (((x) & 0x3) << 12)
#define BIT_MM_AHB_MIPI_CPHY_SEL2(x)            (((x) & 0x7) << 8)
#define BIT_MM_AHB_MIPI_CPHY_SEL1(x)            (((x) & 0x7) << 4)
#define BIT_MM_AHB_MIPI_CPHY_SEL0(x)            (((x) & 0x7))

/* REG_MM_AHB_CGM_DCAM_FDIV */

#define BIT_MM_AHB_CGM_DCAM_FDIV_NUM(x)         (((x) & 0xF) << 16)
#define BIT_MM_AHB_CGM_DCAM_FDIV_DENOM(x)       (((x) & 0xF))

/* REG_MM_AHB_CGM_BPC_FDIV */

#define BIT_MM_AHB_CGM_BPC_FDIV_NUM(x)          (((x) & 0xF) << 16)
#define BIT_MM_AHB_CGM_BPC_FDIV_DENOM(x)        (((x) & 0xF))

/* REG_MM_AHB_CGM_ISP_FDIV */

#define BIT_MM_AHB_CGM_ISP_FDIV_NUM(x)          (((x) & 0xF) << 16)
#define BIT_MM_AHB_CGM_ISP_FDIV_DENOM(x)        (((x) & 0xF))

/* REG_MM_AHB_LP_CTRL_DCAM */

#define BIT_MM_AHB_LP_NUM_DCAM(x)               (((x) & 0xFFFF) << 16)
#define BIT_MM_AHB_LP_EB_DCAM                   BIT(0)

/* REG_MM_AHB_LP_CTRL_ISP */

#define BIT_MM_AHB_LP_NUM_ISP(x)                (((x) & 0xFFFF) << 16)
#define BIT_MM_AHB_LP_EB_ISP                    BIT(0)

/* REG_MM_AHB_LP_CTRL_MM_0 */

#define BIT_MM_AHB_LP_NUM_MM(x)                 (((x) & 0xFFFF) << 16)
#define BIT_MM_AHB_LP_EB_MM                     BIT(0)

/* REG_MM_AHB_LP_CTRL_MM_1 */

#define BIT_MM_AHB_ARQOS_THRESHOLD_MM(x)        (((x) & 0xF) << 20)
#define BIT_MM_AHB_AWQOS_THRESHOLD_MM(x)        (((x) & 0xF) << 16)
#define BIT_MM_AHB_QACTIVE_EB_ISP               BIT(3)
#define BIT_MM_AHB_QACTIVE_EB_DCAM              BIT(2)
#define BIT_MM_AHB_CGM_MM_MTX_S0_AUTO_GATE_EN   BIT(1)
#define BIT_MM_AHB_MM_LPC_DISABLE               BIT(0)

/* REG_MM_AHB_LP_CTRL_ASYNC_BRIDGE */

#define BIT_MM_AHB_LP_NUM_ASYNC_BRIDGE_W(x)     (((x) & 0xFFFF) << 16)
#define BIT_MM_AHB_LP_EB_ASYNC_BRIDGE_W         BIT(0)

/* REG_MM_AHB_MTX_MOD_CTRL */

#define BIT_MM_AHB_MOD_CTRL_DCAM_AR(x)          (((x) & 0x3) << 6)
#define BIT_MM_AHB_MOD_CTRL_DCAM_AW(x)          (((x) & 0x3) << 4)
#define BIT_MM_AHB_MOD_CTRL_ISP_AR(x)           (((x) & 0x3) << 2)
#define BIT_MM_AHB_MOD_CTRL_ISP_AW(x)           (((x) & 0x3))


#endif /* MM_AHB_H */

