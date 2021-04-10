/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2017-05-30 15:03:07
 *
 */


#ifndef MM_AHB_H
#define MM_AHB_H

#define CTL_BASE_MM_AHB 0x60D00000


#define REG_MM_AHB_AHB_EB              ( CTL_BASE_MM_AHB + 0x0000 )
#define REG_MM_AHB_AHB_RST             ( CTL_BASE_MM_AHB + 0x0004 )
#define REG_MM_AHB_GEN_CKG_CFG         ( CTL_BASE_MM_AHB + 0x0008 )
#define REG_MM_AHB_MIPI_CSI2_CTRL      ( CTL_BASE_MM_AHB + 0x000C )
#define REG_MM_AHB_CSI_IDI_SW_CFG      ( CTL_BASE_MM_AHB + 0x0010 )
#define REG_MM_AHB_CSI_IDI_SW_INT_EN   ( CTL_BASE_MM_AHB + 0x0014 )
#define REG_MM_AHB_CSI_IDI_SW_INT_CLR  ( CTL_BASE_MM_AHB + 0x0018 )
#define REG_MM_AHB_CSI_IDI_SW_STATE    ( CTL_BASE_MM_AHB + 0x001C )
#define REG_MM_AHB_CSI_IDI_SW_INT      ( CTL_BASE_MM_AHB + 0x0020 )
#define REG_MM_AHB_CGM_ISP_FDIV        ( CTL_BASE_MM_AHB + 0x0024 )
#define REG_MM_AHB_CGM_DCAM_FDIV       ( CTL_BASE_MM_AHB + 0x0028 )
#define REG_MM_AHB_CGM_CPP_FDIV        ( CTL_BASE_MM_AHB + 0x002C )
#define REG_MM_AHB_CGM_JPG_FDIV        ( CTL_BASE_MM_AHB + 0x0030 )
#define REG_MM_AHB_CGM_VSP_FDIV        ( CTL_BASE_MM_AHB + 0x0034 )

/* REG_MM_AHB_AHB_EB */

#define BIT_MM_AHB_CBM_EB                    BIT(8)
#define BIT_MM_AHB_CPP_EB                    BIT(7)
#define BIT_MM_AHB_CKG_EB                    BIT(6)
#define BIT_MM_AHB_JPG_EB                    BIT(5)
#define BIT_MM_AHB_CSI_S_EB                  BIT(4)
#define BIT_MM_AHB_CSI_EB                    BIT(3)
#define BIT_MM_AHB_VSP_EB                    BIT(2)
#define BIT_MM_AHB_ISP_EB                    BIT(1)
#define BIT_MM_AHB_DCAM_EB                   BIT(0)

/* REG_MM_AHB_AHB_RST */

#define BIT_MM_AHB_ISP_FMCU_SOFT_RST         BIT(15)
#define BIT_MM_AHB_AXI_MTX_VSP_SOFT_RST      BIT(14)
#define BIT_MM_AHB_AXI_MTX_CAM_SOFT_RST      BIT(13)
#define BIT_MM_AHB_MIPI_S_SOFT_RST           BIT(12)
#define BIT_MM_AHB_CSI_IDI_SW_SOFT_RST       BIT(11)
#define BIT_MM_AHB_CSI_S_SOFT_RST            BIT(10)
#define BIT_MM_AHB_CPP_SOFT_RST              BIT(9)
#define BIT_MM_AHB_CKG_SOFT_RST              BIT(8)
#define BIT_MM_AHB_CAM0_SOFT_RST             BIT(7)
#define BIT_MM_AHB_JPG_SOFT_RST              BIT(6)
#define BIT_MM_AHB_CSI_SOFT_RST              BIT(5)
#define BIT_MM_AHB_VSP_SOFT_RST              BIT(4)
#define BIT_MM_AHB_ISP_CFG_SOFT_RST          BIT(3)
#define BIT_MM_AHB_ISP_LOG_SOFT_RST          BIT(2)
#define BIT_MM_AHB_MIPI_SOFT_RST             BIT(1)
#define BIT_MM_AHB_DCAM_SOFT_RST             BIT(0)

/* REG_MM_AHB_GEN_CKG_CFG */

#define BIT_MM_AHB_MIPI_CSI_S_CKG_EN         BIT(5)
#define BIT_MM_AHB_MIPI_CSI_CKG_EN           BIT(4)
#define BIT_MM_AHB_ISP_AXI_CKG_EN            BIT(3)
#define BIT_MM_AHB_SENSOR1_CKG_EN            BIT(2)
#define BIT_MM_AHB_SENSOR0_CKG_EN            BIT(1)

/* REG_MM_AHB_MIPI_CSI2_CTRL */

#define BIT_MM_AHB_CSI_2P2L_TESTDOUT_MS_SEL  BIT(1)
#define BIT_MM_AHB_MIPI_CPHY_SEL             BIT(0)

/* REG_MM_AHB_CSI_IDI_SW_CFG */

#define BIT_MM_AHB_AUTO_SMOOTH_SW            BIT(1)
#define BIT_MM_AHB_FORCE_TO_CSI1             BIT(0)

/* REG_MM_AHB_CSI_IDI_SW_INT_EN */

#define BIT_MM_AHB_CSI_IDI_SW_INT_EN         BIT(0)

/* REG_MM_AHB_CSI_IDI_SW_INT_CLR */

#define BIT_MM_AHB_CSI_IDI_SW_INT_CLR        BIT(0)

/* REG_MM_AHB_CSI_IDI_SW_STATE */

#define BIT_MM_AHB_CSI_IDI_SW_STATE(x)       (((x) & 0x7))

/* REG_MM_AHB_CSI_IDI_SW_INT */

#define BIT_MM_AHB_CSI_IDI_SW_DONE_STS       BIT(1)
#define BIT_MM_AHB_CSI_IDI_SW_DONE_RAW       BIT(0)

/* REG_MM_AHB_CGM_ISP_FDIV */

#define BIT_MM_AHB_CGM_ISP_FDIV_NUM(x)       (((x) & 0xF) << 16)
#define BIT_MM_AHB_CGM_ISP_FDIV_DENOM(x)     (((x) & 0xF))

/* REG_MM_AHB_CGM_DCAM_FDIV */

#define BIT_MM_AHB_CGM_DCAM_FDIV_NUM(x)      (((x) & 0xF) << 16)
#define BIT_MM_AHB_CGM_DCAM_FDIV_DENOM(x)    (((x) & 0xF))

/* REG_MM_AHB_CGM_CPP_FDIV */

#define BIT_MM_AHB_CGM_CPP_FDIV_NUM(x)       (((x) & 0xF) << 16)
#define BIT_MM_AHB_CGM_CPP_FDIV_DENOM(x)     (((x) & 0xF))

/* REG_MM_AHB_CGM_JPG_FDIV */

#define BIT_MM_AHB_CGM_JPG_FDIV_NUM(x)       (((x) & 0xF) << 16)
#define BIT_MM_AHB_CGM_JPG_FDIV_DENOM(x)     (((x) & 0xF))

/* REG_MM_AHB_CGM_VSP_FDIV */

#define BIT_MM_AHB_CGM_VSP_FDIV_NUM(x)       (((x) & 0xF) << 16)
#define BIT_MM_AHB_CGM_VSP_FDIV_DENOM(x)     (((x) & 0xF))


#endif /* MM_AHB_H */

