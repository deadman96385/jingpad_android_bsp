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


#ifndef MM_VSP_AHB_H
#define MM_VSP_AHB_H

#define CTL_BASE_MM_VSP_AHB 0x62000000


#define REG_MM_VSP_AHB_AHB_EB                ( CTL_BASE_MM_VSP_AHB + 0x0000 )
#define REG_MM_VSP_AHB_AHB_RST               ( CTL_BASE_MM_VSP_AHB + 0x0004 )
#define REG_MM_VSP_AHB_CGM_VSP_FDIV          ( CTL_BASE_MM_VSP_AHB + 0x0008 )
#define REG_MM_VSP_AHB_CGM_CPP_FDIV          ( CTL_BASE_MM_VSP_AHB + 0x000C )
#define REG_MM_VSP_AHB_CGM_JPG_FDIV          ( CTL_BASE_MM_VSP_AHB + 0x0010 )
#define REG_MM_VSP_AHB_LP_CTRL_VSP           ( CTL_BASE_MM_VSP_AHB + 0x0014 )
#define REG_MM_VSP_AHB_LP_CTRL_JPG           ( CTL_BASE_MM_VSP_AHB + 0x0018 )
#define REG_MM_VSP_AHB_LP_CTRL_CPP           ( CTL_BASE_MM_VSP_AHB + 0x001C )
#define REG_MM_VSP_AHB_LP_CTRL_MM_VSP_0      ( CTL_BASE_MM_VSP_AHB + 0x0020 )
#define REG_MM_VSP_AHB_LP_CTRL_MM_VSP_1      ( CTL_BASE_MM_VSP_AHB + 0x0024 )
#define REG_MM_VSP_AHB_MTX_MOD_CTRL          ( CTL_BASE_MM_VSP_AHB + 0x0028 )

/* REG_MM_VSP_AHB_AHB_EB */

#define BIT_MM_VSP_AHB_CPP_EB                          BIT(3)
#define BIT_MM_VSP_AHB_JPG_EB                          BIT(2)
#define BIT_MM_VSP_AHB_VSP_EB                          BIT(1)
#define BIT_MM_VSP_AHB_CKG_EB                          BIT(0)

/* REG_MM_VSP_AHB_AHB_RST */

#define BIT_MM_VSP_AHB_CPP_DMA_SOFT_RST                BIT(9)
#define BIT_MM_VSP_AHB_CPP_PATH1_SOFT_RST              BIT(8)
#define BIT_MM_VSP_AHB_CPP_PATH0_SOFT_RST              BIT(7)
#define BIT_MM_VSP_AHB_CPP_SOFT_RST                    BIT(6)
#define BIT_MM_VSP_AHB_JPG_SOFT_RST                    BIT(5)
#define BIT_MM_VSP_AHB_VPP_SOFT_RST                    BIT(4)
#define BIT_MM_VSP_AHB_VSP_SOFT_RST                    BIT(3)
#define BIT_MM_VSP_AHB_VSP_GLB_SOFT_RST                BIT(2)
#define BIT_MM_VSP_AHB_AXI_MM_VSP_EMC_SOFT_RST         BIT(1)
#define BIT_MM_VSP_AHB_CKG_SOFT_RST                    BIT(0)

/* REG_MM_VSP_AHB_CGM_VSP_FDIV */

#define BIT_MM_VSP_AHB_CGM_VSP_FDIV_NUM(x)             (((x) & 0xF) << 16)
#define BIT_MM_VSP_AHB_CGM_VSP_FDIV_DENOM(x)           (((x) & 0xF))

/* REG_MM_VSP_AHB_CGM_CPP_FDIV */

#define BIT_MM_VSP_AHB_CGM_CPP_FDIV_NUM(x)             (((x) & 0xF) << 16)
#define BIT_MM_VSP_AHB_CGM_CPP_FDIV_DENOM(x)           (((x) & 0xF))

/* REG_MM_VSP_AHB_CGM_JPG_FDIV */

#define BIT_MM_VSP_AHB_CGM_JPG_FDIV_NUM(x)             (((x) & 0xF) << 16)
#define BIT_MM_VSP_AHB_CGM_JPG_FDIV_DENOM(x)           (((x) & 0xF))

/* REG_MM_VSP_AHB_LP_CTRL_VSP */

#define BIT_MM_VSP_AHB_LP_NUM_VSP(x)                   (((x) & 0xFFFF) << 16)
#define BIT_MM_VSP_AHB_LP_EB_VSP                       BIT(0)

/* REG_MM_VSP_AHB_LP_CTRL_JPG */

#define BIT_MM_VSP_AHB_LP_NUM_JPG(x)                   (((x) & 0xFFFF) << 16)
#define BIT_MM_VSP_AHB_LP_EB_JPG                       BIT(0)

/* REG_MM_VSP_AHB_LP_CTRL_CPP */

#define BIT_MM_VSP_AHB_LP_NUM_CPP(x)                   (((x) & 0xFFFF) << 16)
#define BIT_MM_VSP_AHB_LP_EB_CPP                       BIT(0)

/* REG_MM_VSP_AHB_LP_CTRL_MM_VSP_0 */

#define BIT_MM_VSP_AHB_LP_NUM_MM_VSP(x)                (((x) & 0xFFFF) << 16)
#define BIT_MM_VSP_AHB_LP_EB_MM_VSP                    BIT(0)

/* REG_MM_VSP_AHB_LP_CTRL_MM_VSP_1 */

#define BIT_MM_VSP_AHB_ARQOS_THRESHOLD_MM_VSP(x)       (((x) & 0xF) << 20)
#define BIT_MM_VSP_AHB_AWQOS_THRESHOLD_MM_VSP(x)       (((x) & 0xF) << 16)
#define BIT_MM_VSP_AHB_QACTIVE_EB_CPP                  BIT(4)
#define BIT_MM_VSP_AHB_QACTIVE_EB_JPG                  BIT(3)
#define BIT_MM_VSP_AHB_QACTIVE_EB_VSP                  BIT(2)
#define BIT_MM_VSP_AHB_CGM_MM_VSP_MTX_S0_AUTO_GATE_EN  BIT(1)
#define BIT_MM_VSP_AHB_MM_VSP_LPC_DISABLE              BIT(0)

/* REG_MM_VSP_AHB_MTX_MOD_CTRL */

#define BIT_MM_VSP_AHB_MOD_CTRL_CPP_AR(x)              (((x) & 0x3) << 10)
#define BIT_MM_VSP_AHB_MOD_CTRL_CPP_AW(x)              (((x) & 0x3) << 8)
#define BIT_MM_VSP_AHB_MOD_CTRL_JPG_AR(x)              (((x) & 0x3) << 6)
#define BIT_MM_VSP_AHB_MOD_CTRL_JPG_AW(x)              (((x) & 0x3) << 4)
#define BIT_MM_VSP_AHB_MOD_CTRL_VSP_AR(x)              (((x) & 0x3) << 2)
#define BIT_MM_VSP_AHB_MOD_CTRL_VSP_AW(x)              (((x) & 0x3))


#endif /* MM_VSP_AHB_H */

