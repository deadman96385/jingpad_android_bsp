/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-18 10:54:34
 *
 */


#ifndef MM_DVFS_AHB_H
#define MM_DVFS_AHB_H

#define CTL_BASE_MM_DVFS_AHB 0x62600000


#define REG_MM_DVFS_AHB_MM_DVFS_HOLD_CTRL                 ( CTL_BASE_MM_DVFS_AHB + 0x0000 )
#define REG_MM_DVFS_AHB_MM_DVFS_WAIT_WINDOW_CFG           ( CTL_BASE_MM_DVFS_AHB + 0x0004 )
#define REG_MM_DVFS_AHB_MM_DFS_EN_CTRL                    ( CTL_BASE_MM_DVFS_AHB + 0x0008 )
#define REG_MM_DVFS_AHB_MM_MIN_VOLTAGE_CFG                ( CTL_BASE_MM_DVFS_AHB + 0x0010 )
#define REG_MM_DVFS_AHB_MM_DFS_SW_TRIG_CFG                ( CTL_BASE_MM_DVFS_AHB + 0x0014 )
#define REG_MM_DVFS_AHB_MM_SW_DVFS_CTRL                   ( CTL_BASE_MM_DVFS_AHB + 0x002C )
#define REG_MM_DVFS_AHB_MM_FREQ_UPDATE_BYPASS             ( CTL_BASE_MM_DVFS_AHB + 0x0030 )
#define REG_MM_DVFS_AHB_CGM_MM_DVFS_CLK_GATE_CTRL         ( CTL_BASE_MM_DVFS_AHB + 0x0034 )
#define REG_MM_DVFS_AHB_MM_DVFS_VOLTAGE_DBG               ( CTL_BASE_MM_DVFS_AHB + 0x0038 )
#define REG_MM_DVFS_AHB_MM_DVFS_CGM_CFG_DBG               ( CTL_BASE_MM_DVFS_AHB + 0x0048 )
#define REG_MM_DVFS_AHB_MM_DVFS_STATE_DBG                 ( CTL_BASE_MM_DVFS_AHB + 0x004C )
#define REG_MM_DVFS_AHB_ISP_INDEX0_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x0050 )
#define REG_MM_DVFS_AHB_ISP_INDEX1_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x0054 )
#define REG_MM_DVFS_AHB_ISP_INDEX2_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x0058 )
#define REG_MM_DVFS_AHB_ISP_INDEX3_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x005C )
#define REG_MM_DVFS_AHB_ISP_INDEX4_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x0060 )
#define REG_MM_DVFS_AHB_ISP_INDEX5_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x0064 )
#define REG_MM_DVFS_AHB_ISP_INDEX6_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x0068 )
#define REG_MM_DVFS_AHB_ISP_INDEX7_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x006C )
#define REG_MM_DVFS_AHB_JPG_INDEX0_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x0070 )
#define REG_MM_DVFS_AHB_JPG_INDEX1_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x0074 )
#define REG_MM_DVFS_AHB_JPG_INDEX2_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x0078 )
#define REG_MM_DVFS_AHB_JPG_INDEX3_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x007C )
#define REG_MM_DVFS_AHB_JPG_INDEX4_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x0080 )
#define REG_MM_DVFS_AHB_JPG_INDEX5_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x0084 )
#define REG_MM_DVFS_AHB_JPG_INDEX6_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x0088 )
#define REG_MM_DVFS_AHB_JPG_INDEX7_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x008C )
#define REG_MM_DVFS_AHB_CPP_INDEX0_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x0090 )
#define REG_MM_DVFS_AHB_CPP_INDEX1_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x0094 )
#define REG_MM_DVFS_AHB_CPP_INDEX2_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x0098 )
#define REG_MM_DVFS_AHB_CPP_INDEX3_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x009C )
#define REG_MM_DVFS_AHB_CPP_INDEX4_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x0100 )
#define REG_MM_DVFS_AHB_CPP_INDEX5_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x0104 )
#define REG_MM_DVFS_AHB_CPP_INDEX6_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x0108 )
#define REG_MM_DVFS_AHB_CPP_INDEX7_MAP                    ( CTL_BASE_MM_DVFS_AHB + 0x010C )
#define REG_MM_DVFS_AHB_DCAM_IF_INDEX0_MAP                ( CTL_BASE_MM_DVFS_AHB + 0x0110 )
#define REG_MM_DVFS_AHB_DCAM_IF_INDEX1_MAP                ( CTL_BASE_MM_DVFS_AHB + 0x0114 )
#define REG_MM_DVFS_AHB_DCAM_IF_INDEX2_MAP                ( CTL_BASE_MM_DVFS_AHB + 0x0118 )
#define REG_MM_DVFS_AHB_DCAM_IF_INDEX3_MAP                ( CTL_BASE_MM_DVFS_AHB + 0x011C )
#define REG_MM_DVFS_AHB_DCAM_IF_INDEX4_MAP                ( CTL_BASE_MM_DVFS_AHB + 0x0120 )
#define REG_MM_DVFS_AHB_DCAM_IF_INDEX5_MAP                ( CTL_BASE_MM_DVFS_AHB + 0x0124 )
#define REG_MM_DVFS_AHB_DCAM_IF_INDEX6_MAP                ( CTL_BASE_MM_DVFS_AHB + 0x0128 )
#define REG_MM_DVFS_AHB_DCAM_IF_INDEX7_MAP                ( CTL_BASE_MM_DVFS_AHB + 0x012C )
#define REG_MM_DVFS_AHB_DCAM_AXI_INDEX0_MAP               ( CTL_BASE_MM_DVFS_AHB + 0x0130 )
#define REG_MM_DVFS_AHB_DCAM_AXI_INDEX1_MAP               ( CTL_BASE_MM_DVFS_AHB + 0x0134 )
#define REG_MM_DVFS_AHB_DCAM_AXI_INDEX2_MAP               ( CTL_BASE_MM_DVFS_AHB + 0x0138 )
#define REG_MM_DVFS_AHB_DCAM_AXI_INDEX3_MAP               ( CTL_BASE_MM_DVFS_AHB + 0x013C )
#define REG_MM_DVFS_AHB_DCAM_AXI_INDEX4_MAP               ( CTL_BASE_MM_DVFS_AHB + 0x0140 )
#define REG_MM_DVFS_AHB_DCAM_AXI_INDEX5_MAP               ( CTL_BASE_MM_DVFS_AHB + 0x0144 )
#define REG_MM_DVFS_AHB_DCAM_AXI_INDEX6_MAP               ( CTL_BASE_MM_DVFS_AHB + 0x0148 )
#define REG_MM_DVFS_AHB_DCAM_AXI_INDEX7_MAP               ( CTL_BASE_MM_DVFS_AHB + 0x014C )
#define REG_MM_DVFS_AHB_MM_MTX_INDEX0_MAP                 ( CTL_BASE_MM_DVFS_AHB + 0x0150 )
#define REG_MM_DVFS_AHB_MM_MTX_INDEX1_MAP                 ( CTL_BASE_MM_DVFS_AHB + 0x0154 )
#define REG_MM_DVFS_AHB_MM_MTX_INDEX2_MAP                 ( CTL_BASE_MM_DVFS_AHB + 0x0158 )
#define REG_MM_DVFS_AHB_MM_MTX_INDEX3_MAP                 ( CTL_BASE_MM_DVFS_AHB + 0x015C )
#define REG_MM_DVFS_AHB_MM_MTX_INDEX4_MAP                 ( CTL_BASE_MM_DVFS_AHB + 0x0160 )
#define REG_MM_DVFS_AHB_MM_MTX_INDEX5_MAP                 ( CTL_BASE_MM_DVFS_AHB + 0x0164 )
#define REG_MM_DVFS_AHB_MM_MTX_INDEX6_MAP                 ( CTL_BASE_MM_DVFS_AHB + 0x0168 )
#define REG_MM_DVFS_AHB_MM_MTX_INDEX7_MAP                 ( CTL_BASE_MM_DVFS_AHB + 0x016C )
#define REG_MM_DVFS_AHB_ISP_DVFS_INDEX_CFG                ( CTL_BASE_MM_DVFS_AHB + 0x0170 )
#define REG_MM_DVFS_AHB_ISP_DVFS_INDEX_IDLE_CFG           ( CTL_BASE_MM_DVFS_AHB + 0x0174 )
#define REG_MM_DVFS_AHB_JPG_DVFS_INDEX_CFG                ( CTL_BASE_MM_DVFS_AHB + 0x0178 )
#define REG_MM_DVFS_AHB_JPG_DVFS_INDEX_IDLE_CFG           ( CTL_BASE_MM_DVFS_AHB + 0x017C )
#define REG_MM_DVFS_AHB_CPP_DVFS_INDEX_CFG                ( CTL_BASE_MM_DVFS_AHB + 0x0180 )
#define REG_MM_DVFS_AHB_CPP_DVFS_INDEX_IDLE_CFG           ( CTL_BASE_MM_DVFS_AHB + 0x0184 )
#define REG_MM_DVFS_AHB_MM_MTX_DVFS_INDEX_CFG             ( CTL_BASE_MM_DVFS_AHB + 0x0188 )
#define REG_MM_DVFS_AHB_MM_MTX_DVFS_INDEX_IDLE_CFG        ( CTL_BASE_MM_DVFS_AHB + 0x018C )
#define REG_MM_DVFS_AHB_DCAM_IF_DVFS_INDEX_CFG            ( CTL_BASE_MM_DVFS_AHB + 0x0190 )
#define REG_MM_DVFS_AHB_DCAM_IF_DVFS_INDEX_IDLE_CFG       ( CTL_BASE_MM_DVFS_AHB + 0x0194 )
#define REG_MM_DVFS_AHB_DCAM_AXI_DVFS_INDEX_CFG           ( CTL_BASE_MM_DVFS_AHB + 0x0198 )
#define REG_MM_DVFS_AHB_DCAM_AXI_DVFS_INDEX_IDLE_CFG      ( CTL_BASE_MM_DVFS_AHB + 0x019C )
#define REG_MM_DVFS_AHB_FREQ_UPD_STATE                    ( CTL_BASE_MM_DVFS_AHB + 0x01A0 )
#define REG_MM_DVFS_AHB_MM_GFREE_WAIT_DELAY_CFG0          ( CTL_BASE_MM_DVFS_AHB + 0x01A4 )
#define REG_MM_DVFS_AHB_MM_GFREE_WAIT_DELAY_CFG1          ( CTL_BASE_MM_DVFS_AHB + 0x01A8 )
#define REG_MM_DVFS_AHB_MM_FREQ_UPD_TYPE_CFG              ( CTL_BASE_MM_DVFS_AHB + 0x01AC )
#define REG_MM_DVFS_AHB_FD_INDEX0_MAP                     ( CTL_BASE_MM_DVFS_AHB + 0x01B0 )
#define REG_MM_DVFS_AHB_FD_INDEX1_MAP                     ( CTL_BASE_MM_DVFS_AHB + 0x01B4 )
#define REG_MM_DVFS_AHB_FD_INDEX2_MAP                     ( CTL_BASE_MM_DVFS_AHB + 0x01B8 )
#define REG_MM_DVFS_AHB_FD_INDEX3_MAP                     ( CTL_BASE_MM_DVFS_AHB + 0x01BC )
#define REG_MM_DVFS_AHB_FD_INDEX4_MAP                     ( CTL_BASE_MM_DVFS_AHB + 0x01C0 )
#define REG_MM_DVFS_AHB_FD_INDEX5_MAP                     ( CTL_BASE_MM_DVFS_AHB + 0x01C4 )
#define REG_MM_DVFS_AHB_FD_INDEX6_MAP                     ( CTL_BASE_MM_DVFS_AHB + 0x01C8 )
#define REG_MM_DVFS_AHB_FD_INDEX7_MAP                     ( CTL_BASE_MM_DVFS_AHB + 0x01CC )
#define REG_MM_DVFS_AHB_FD_DVFS_INDEX_CFG                 ( CTL_BASE_MM_DVFS_AHB + 0x01D0 )
#define REG_MM_DVFS_AHB_FD_DVFS_INDEX_IDLE_CFG            ( CTL_BASE_MM_DVFS_AHB + 0x01D4 )
#define REG_MM_DVFS_AHB_MM_GFREE_WAIT_DELAY_CFG2          ( CTL_BASE_MM_DVFS_AHB + 0x01D8 )
#define REG_MM_DVFS_AHB_MM_DFS_IDLE_DISABLE_CFG           ( CTL_BASE_MM_DVFS_AHB + 0x01DC )
#define REG_MM_DVFS_AHB_MM_DVFS_RESERVED_REG_CFG0         ( CTL_BASE_MM_DVFS_AHB + 0x01E0 )
#define REG_MM_DVFS_AHB_MM_DVFS_RESERVED_REG_CFG1         ( CTL_BASE_MM_DVFS_AHB + 0x01E4 )
#define REG_MM_DVFS_AHB_MM_DVFS_RESERVED_REG_CFG2         ( CTL_BASE_MM_DVFS_AHB + 0x01E8 )
#define REG_MM_DVFS_AHB_MM_DVFS_RESERVED_REG_CFG3         ( CTL_BASE_MM_DVFS_AHB + 0x01EC )

/* REG_MM_DVFS_AHB_MM_DVFS_HOLD_CTRL */

#define BIT_MM_DVFS_AHB_MM_DVFS_HOLD                      BIT(0)

/* REG_MM_DVFS_AHB_MM_DVFS_WAIT_WINDOW_CFG */

#define BIT_MM_DVFS_AHB_MM_DVFS_UP_WINDOW(x)              (((x) & 0xFFFF) << 16)
#define BIT_MM_DVFS_AHB_MM_DVFS_DOWN_WINDOW(x)            (((x) & 0xFFFF))

/* REG_MM_DVFS_AHB_MM_DFS_EN_CTRL */

#define BIT_MM_DVFS_AHB_MM_DCAM_AXI_AUTO_TUNE_EN          BIT(7)
#define BIT_MM_DVFS_AHB_FD_DFS_EN                         BIT(6)
#define BIT_MM_DVFS_AHB_DCAM_DFS_EN                       BIT(5)
#define BIT_MM_DVFS_AHB_JPG_DFS_EN                        BIT(3)
#define BIT_MM_DVFS_AHB_CPP_DFS_EN                        BIT(2)
#define BIT_MM_DVFS_AHB_ISP_DFS_EN                        BIT(1)
#define BIT_MM_DVFS_AHB_MM_MTX_AUTO_TUNE_EN               BIT(0)

/* REG_MM_DVFS_AHB_MM_MIN_VOLTAGE_CFG */

#define BIT_MM_DVFS_AHB_MM_SYS_MIN_VOLTAGE(x)             (((x) & 0x7))

/* REG_MM_DVFS_AHB_MM_DFS_SW_TRIG_CFG */

#define BIT_MM_DVFS_AHB_DCAM_DFS_SW_TRIG                  BIT(4)
#define BIT_MM_DVFS_AHB_CPP_DFS_SW_TRIG                   BIT(3)
#define BIT_MM_DVFS_AHB_JPG_DFS_SW_TRIG                   BIT(2)
#define BIT_MM_DVFS_AHB_FD_DFS_SW_TRIG                    BIT(1)
#define BIT_MM_DVFS_AHB_ISP_DFS_SW_TRIG                   BIT(0)

/* REG_MM_DVFS_AHB_MM_SW_DVFS_CTRL */

#define BIT_MM_DVFS_AHB_MM_DVFS_ACK                       BIT(8)
#define BIT_MM_DVFS_AHB_MM_DVFS_VOLTAGE_SW(x)             (((x) & 0x7) << 4)
#define BIT_MM_DVFS_AHB_MM_DVFS_REQ_SW                    BIT(0)

/* REG_MM_DVFS_AHB_MM_FREQ_UPDATE_BYPASS */

#define BIT_MM_DVFS_AHB_REG_FD_FREQ_UPD_EN_BYP            BIT(6)
#define BIT_MM_DVFS_AHB_REG_DCAM_IF_FREQ_UPD_EN_BYP       BIT(5)
#define BIT_MM_DVFS_AHB_REG_JPG_FREQ_UPD_EN_BYP           BIT(4)
#define BIT_MM_DVFS_AHB_REG_CPP_FREQ_UPD_EN_BYP           BIT(3)
#define BIT_MM_DVFS_AHB_REG_ISP_FREQ_UPD_EN_BYP           BIT(2)
#define BIT_MM_DVFS_AHB_REG_MM_MTX_FREQ_UPD_EN_BYP        BIT(1)
#define BIT_MM_DVFS_AHB_REG_DCAM_AXI_FREQ_UPD_EN_BYP      BIT(0)

/* REG_MM_DVFS_AHB_CGM_MM_DVFS_CLK_GATE_CTRL */

#define BIT_MM_DVFS_AHB_CGM_MM_DVFS_FORCE_EN              BIT(1)
#define BIT_MM_DVFS_AHB_CGM_MM_DVFS_AUTO_GATE_SEL         BIT(0)

/* REG_MM_DVFS_AHB_MM_DVFS_VOLTAGE_DBG */

#define BIT_MM_DVFS_AHB_MM_CURRENT_VOLTAGE(x)             (((x) & 0x7) << 24)
#define BIT_MM_DVFS_AHB_FD_VOLTAGE(x)                     (((x) & 0x7) << 21)
#define BIT_MM_DVFS_AHB_DCAM_IF_VOLTAGE(x)                (((x) & 0x7) << 18)
#define BIT_MM_DVFS_AHB_DCAM_AXI_VOLTAGE(x)               (((x) & 0x7) << 15)
#define BIT_MM_DVFS_AHB_JPG_VOLTAGE(x)                    (((x) & 0x7) << 12)
#define BIT_MM_DVFS_AHB_CPP_VOLTAGE(x)                    (((x) & 0x7) << 9)
#define BIT_MM_DVFS_AHB_ISP_VOLTAGE(x)                    (((x) & 0x7) << 6)
#define BIT_MM_DVFS_AHB_MM_MTX_VOLTAGE(x)                 (((x) & 0x7) << 3)
#define BIT_MM_DVFS_AHB_MM_INTERNAL_VOTE_VOLTAGE(x)       (((x) & 0x7))

/* REG_MM_DVFS_AHB_MM_DVFS_CGM_CFG_DBG */

#define BIT_MM_DVFS_AHB_CGM_FD_SEL_DVFS(x)                (((x) & 0x3) << 23)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_FDIV_DENOM_DVFS(x)    (((x) & 0xF) << 19)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_FDIV_NUM_DVFS(x)      (((x) & 0xF) << 15)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_SEL_DVFS(x)           (((x) & 0x7) << 12)
#define BIT_MM_DVFS_AHB_CGM_DCAM_AXI_SEL_DVFS(x)          (((x) & 0x3) << 10)
#define BIT_MM_DVFS_AHB_CGM_JPG_SEL_DVFS(x)               (((x) & 0x3) << 8)
#define BIT_MM_DVFS_AHB_CGM_CPP_SEL_DVFS(x)               (((x) & 0x3) << 6)
#define BIT_MM_DVFS_AHB_CGM_ISP_SEL_DVFS(x)               (((x) & 0x7) << 3)
#define BIT_MM_DVFS_AHB_CGM_MM_MTX_SEL_DVFS(x)            (((x) & 0x7))

/* REG_MM_DVFS_AHB_MM_DVFS_STATE_DBG */

#define BIT_MM_DVFS_AHB_MM_DVFS_BUSY                      BIT(19)
#define BIT_MM_DVFS_AHB_MM_DVFS_WINDOW_CNT(x)             (((x) & 0xFFFF) << 3)
#define BIT_MM_DVFS_AHB_MM_DVFS_STATE(x)                  (((x) & 0x7))

/* REG_MM_DVFS_AHB_ISP_INDEX0_MAP */

#define BIT_MM_DVFS_AHB_ISP_VOL_INDEX0(x)                 (((x) & 0x7) << 6)
#define BIT_MM_DVFS_AHB_ISP_VOTE_MTX_INDEX0(x)            (((x) & 0x7) << 3)
#define BIT_MM_DVFS_AHB_CGM_ISP_SEL_INDEX0(x)             (((x) & 0x7))

/* REG_MM_DVFS_AHB_ISP_INDEX1_MAP */

#define BIT_MM_DVFS_AHB_ISP_VOL_INDEX1(x)                 (((x) & 0x7) << 6)
#define BIT_MM_DVFS_AHB_ISP_VOTE_MTX_INDEX1(x)            (((x) & 0x7) << 3)
#define BIT_MM_DVFS_AHB_CGM_ISP_SEL_INDEX1(x)             (((x) & 0x7))

/* REG_MM_DVFS_AHB_ISP_INDEX2_MAP */

#define BIT_MM_DVFS_AHB_ISP_VOL_INDEX2(x)                 (((x) & 0x7) << 6)
#define BIT_MM_DVFS_AHB_ISP_VOTE_MTX_INDEX2(x)            (((x) & 0x7) << 3)
#define BIT_MM_DVFS_AHB_CGM_ISP_SEL_INDEX2(x)             (((x) & 0x7))

/* REG_MM_DVFS_AHB_ISP_INDEX3_MAP */

#define BIT_MM_DVFS_AHB_ISP_VOL_INDEX3(x)                 (((x) & 0x7) << 6)
#define BIT_MM_DVFS_AHB_ISP_VOTE_MTX_INDEX3(x)            (((x) & 0x7) << 3)
#define BIT_MM_DVFS_AHB_CGM_ISP_SEL_INDEX3(x)             (((x) & 0x7))

/* REG_MM_DVFS_AHB_ISP_INDEX4_MAP */

#define BIT_MM_DVFS_AHB_ISP_VOL_INDEX4(x)                 (((x) & 0x7) << 6)
#define BIT_MM_DVFS_AHB_ISP_VOTE_MTX_INDEX4(x)            (((x) & 0x7) << 3)
#define BIT_MM_DVFS_AHB_CGM_ISP_SEL_INDEX4(x)             (((x) & 0x7))

/* REG_MM_DVFS_AHB_ISP_INDEX5_MAP */

#define BIT_MM_DVFS_AHB_ISP_VOL_INDEX5(x)                 (((x) & 0x7) << 6)
#define BIT_MM_DVFS_AHB_ISP_VOTE_MTX_INDEX5(x)            (((x) & 0x7) << 3)
#define BIT_MM_DVFS_AHB_CGM_ISP_SEL_INDEX5(x)             (((x) & 0x7))

/* REG_MM_DVFS_AHB_ISP_INDEX6_MAP */

#define BIT_MM_DVFS_AHB_ISP_VOL_INDEX6(x)                 (((x) & 0x7) << 6)
#define BIT_MM_DVFS_AHB_ISP_VOTE_MTX_INDEX6(x)            (((x) & 0x7) << 3)
#define BIT_MM_DVFS_AHB_CGM_ISP_SEL_INDEX6(x)             (((x) & 0x7))

/* REG_MM_DVFS_AHB_ISP_INDEX7_MAP */

#define BIT_MM_DVFS_AHB_ISP_VOL_INDEX7(x)                 (((x) & 0x7) << 6)
#define BIT_MM_DVFS_AHB_ISP_VOTE_MTX_INDEX7(x)            (((x) & 0x7) << 3)
#define BIT_MM_DVFS_AHB_CGM_ISP_SEL_INDEX7(x)             (((x) & 0x7))

/* REG_MM_DVFS_AHB_JPG_INDEX0_MAP */

#define BIT_MM_DVFS_AHB_JPG_VOL_INDEX0(x)                 (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_JPG_VOTE_MTX_INDEX0(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_JPG_SEL_INDEX0(x)             (((x) & 0x3))

/* REG_MM_DVFS_AHB_JPG_INDEX1_MAP */

#define BIT_MM_DVFS_AHB_JPG_VOL_INDEX1(x)                 (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_JPG_VOTE_MTX_INDEX1(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_JPG_SEL_INDEX1(x)             (((x) & 0x3))

/* REG_MM_DVFS_AHB_JPG_INDEX2_MAP */

#define BIT_MM_DVFS_AHB_JPG_VOL_INDEX2(x)                 (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_JPG_VOTE_MTX_INDEX2(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_JPG_SEL_INDEX2(x)             (((x) & 0x3))

/* REG_MM_DVFS_AHB_JPG_INDEX3_MAP */

#define BIT_MM_DVFS_AHB_JPG_VOL_INDEX3(x)                 (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_JPG_VOTE_MTX_INDEX3(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_JPG_SEL_INDEX3(x)             (((x) & 0x3))

/* REG_MM_DVFS_AHB_JPG_INDEX4_MAP */

#define BIT_MM_DVFS_AHB_JPG_VOL_INDEX4(x)                 (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_JPG_VOTE_MTX_INDEX4(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_JPG_SEL_INDEX4(x)             (((x) & 0x3))

/* REG_MM_DVFS_AHB_JPG_INDEX5_MAP */

#define BIT_MM_DVFS_AHB_JPG_VOL_INDEX5(x)                 (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_JPG_VOTE_MTX_INDEX5(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_JPG_SEL_INDEX5(x)             (((x) & 0x3))

/* REG_MM_DVFS_AHB_JPG_INDEX6_MAP */

#define BIT_MM_DVFS_AHB_JPG_VOL_INDEX6(x)                 (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_JPG_VOTE_MTX_INDEX6(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_JPG_SEL_INDEX6(x)             (((x) & 0x3))

/* REG_MM_DVFS_AHB_JPG_INDEX7_MAP */

#define BIT_MM_DVFS_AHB_JPG_VOL_INDEX7(x)                 (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_JPG_VOTE_MTX_INDEX7(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_JPG_SEL_INDEX7(x)             (((x) & 0x3))

/* REG_MM_DVFS_AHB_CPP_INDEX0_MAP */

#define BIT_MM_DVFS_AHB_CPP_VOL_INDEX0(x)                 (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_CPP_VOTE_MTX_INDEX0(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_CPP_SEL_INDEX0(x)             (((x) & 0x3))

/* REG_MM_DVFS_AHB_CPP_INDEX1_MAP */

#define BIT_MM_DVFS_AHB_CPP_VOL_INDEX1(x)                 (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_CPP_VOTE_MTX_INDEX1(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_CPP_SEL_INDEX1(x)             (((x) & 0x3))

/* REG_MM_DVFS_AHB_CPP_INDEX2_MAP */

#define BIT_MM_DVFS_AHB_CPP_VOL_INDEX2(x)                 (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_CPP_VOTE_MTX_INDEX2(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_CPP_SEL_INDEX2(x)             (((x) & 0x3))

/* REG_MM_DVFS_AHB_CPP_INDEX3_MAP */

#define BIT_MM_DVFS_AHB_CPP_VOL_INDEX3(x)                 (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_CPP_VOTE_MTX_INDEX3(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_CPP_SEL_INDEX3(x)             (((x) & 0x3))

/* REG_MM_DVFS_AHB_CPP_INDEX4_MAP */

#define BIT_MM_DVFS_AHB_CPP_VOL_INDEX4(x)                 (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_CPP_VOTE_MTX_INDEX4(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_CPP_SEL_INDEX4(x)             (((x) & 0x3))

/* REG_MM_DVFS_AHB_CPP_INDEX5_MAP */

#define BIT_MM_DVFS_AHB_CPP_VOL_INDEX5(x)                 (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_CPP_VOTE_MTX_INDEX5(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_CPP_SEL_INDEX5(x)             (((x) & 0x3))

/* REG_MM_DVFS_AHB_CPP_INDEX6_MAP */

#define BIT_MM_DVFS_AHB_CPP_VOL_INDEX6(x)                 (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_CPP_VOTE_MTX_INDEX6(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_CPP_SEL_INDEX6(x)             (((x) & 0x3))

/* REG_MM_DVFS_AHB_CPP_INDEX7_MAP */

#define BIT_MM_DVFS_AHB_CPP_VOL_INDEX7(x)                 (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_CPP_VOTE_MTX_INDEX7(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_CPP_SEL_INDEX7(x)             (((x) & 0x3))

/* REG_MM_DVFS_AHB_DCAM_IF_INDEX0_MAP */

#define BIT_MM_DVFS_AHB_DCAM_IF_VOTE_AXI_INDEX0(x)        (((x) & 0x7) << 14)
#define BIT_MM_DVFS_AHB_DCAM_IF_VOL_INDEX0(x)             (((x) & 0x7) << 11)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_FDIV_DENOM_INDEX0(x)  (((x) & 0xF) << 7)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_FDIV_NUM_INDEX0(x)    (((x) & 0xF) << 3)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_SEL_INDEX0(x)         (((x) & 0x7))

/* REG_MM_DVFS_AHB_DCAM_IF_INDEX1_MAP */

#define BIT_MM_DVFS_AHB_DCAM_IF_VOTE_AXI_INDEX1(x)        (((x) & 0x7) << 14)
#define BIT_MM_DVFS_AHB_DCAM_IF_VOL_INDEX1(x)             (((x) & 0x7) << 11)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_FDIV_DENOM_INDEX1(x)  (((x) & 0xF) << 7)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_FDIV_NUM_INDEX1(x)    (((x) & 0xF) << 3)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_SEL_INDEX1(x)         (((x) & 0x7))

/* REG_MM_DVFS_AHB_DCAM_IF_INDEX2_MAP */

#define BIT_MM_DVFS_AHB_DCAM_IF_VOTE_AXI_INDEX2(x)        (((x) & 0x7) << 14)
#define BIT_MM_DVFS_AHB_DCAM_IF_VOL_INDEX2(x)             (((x) & 0x7) << 11)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_FDIV_DENOM_INDEX2(x)  (((x) & 0xF) << 7)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_FDIV_NUM_INDEX2(x)    (((x) & 0xF) << 3)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_SEL_INDEX2(x)         (((x) & 0x7))

/* REG_MM_DVFS_AHB_DCAM_IF_INDEX3_MAP */

#define BIT_MM_DVFS_AHB_DCAM_IF_VOTE_AXI_INDEX3(x)        (((x) & 0x7) << 14)
#define BIT_MM_DVFS_AHB_DCAM_IF_VOL_INDEX3(x)             (((x) & 0x7) << 11)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_FDIV_DENOM_INDEX3(x)  (((x) & 0xF) << 7)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_FDIV_NUM_INDEX3(x)    (((x) & 0xF) << 3)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_SEL_INDEX3(x)         (((x) & 0x7))

/* REG_MM_DVFS_AHB_DCAM_IF_INDEX4_MAP */

#define BIT_MM_DVFS_AHB_DCAM_IF_VOTE_AXI_INDEX4(x)        (((x) & 0x7) << 14)
#define BIT_MM_DVFS_AHB_DCAM_IF_VOL_INDEX4(x)             (((x) & 0x7) << 11)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_FDIV_DENOM_INDEX4(x)  (((x) & 0xF) << 7)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_FDIV_NUM_INDEX4(x)    (((x) & 0xF) << 3)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_SEL_INDEX4(x)         (((x) & 0x7))

/* REG_MM_DVFS_AHB_DCAM_IF_INDEX5_MAP */

#define BIT_MM_DVFS_AHB_DCAM_IF_VOTE_AXI_INDEX5(x)        (((x) & 0x7) << 14)
#define BIT_MM_DVFS_AHB_DCAM_IF_VOL_INDEX5(x)             (((x) & 0x7) << 11)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_FDIV_DENOM_INDEX5(x)  (((x) & 0xF) << 7)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_FDIV_NUM_INDEX5(x)    (((x) & 0xF) << 3)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_SEL_INDEX5(x)         (((x) & 0x7))

/* REG_MM_DVFS_AHB_DCAM_IF_INDEX6_MAP */

#define BIT_MM_DVFS_AHB_DCAM_IF_VOTE_AXI_INDEX6(x)        (((x) & 0x7) << 14)
#define BIT_MM_DVFS_AHB_DCAM_IF_VOL_INDEX6(x)             (((x) & 0x7) << 11)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_FDIV_DENOM_INDEX6(x)  (((x) & 0xF) << 7)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_FDIV_NUM_INDEX6(x)    (((x) & 0xF) << 3)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_SEL_INDEX6(x)         (((x) & 0x7))

/* REG_MM_DVFS_AHB_DCAM_IF_INDEX7_MAP */

#define BIT_MM_DVFS_AHB_DCAM_IF_VOTE_AXI_INDEX7(x)        (((x) & 0x7) << 14)
#define BIT_MM_DVFS_AHB_DCAM_IF_VOL_INDEX7(x)             (((x) & 0x7) << 11)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_FDIV_DENOM_INDEX7(x)  (((x) & 0xF) << 7)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_FDIV_NUM_INDEX7(x)    (((x) & 0xF) << 3)
#define BIT_MM_DVFS_AHB_CGM_DCAM_IF_SEL_INDEX7(x)         (((x) & 0x7))

/* REG_MM_DVFS_AHB_DCAM_AXI_INDEX0_MAP */

#define BIT_MM_DVFS_AHB_DCAM_AXI_VOL_INDEX0(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_DCAM_AXI_SEL_INDEX0(x)        (((x) & 0x3))

/* REG_MM_DVFS_AHB_DCAM_AXI_INDEX1_MAP */

#define BIT_MM_DVFS_AHB_DCAM_AXI_VOL_INDEX1(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_DCAM_AXI_SEL_INDEX1(x)        (((x) & 0x3))

/* REG_MM_DVFS_AHB_DCAM_AXI_INDEX2_MAP */

#define BIT_MM_DVFS_AHB_DCAM_AXI_VOL_INDEX2(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_DCAM_AXI_SEL_INDEX2(x)        (((x) & 0x3))

/* REG_MM_DVFS_AHB_DCAM_AXI_INDEX3_MAP */

#define BIT_MM_DVFS_AHB_DCAM_AXI_VOL_INDEX3(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_DCAM_AXI_SEL_INDEX3(x)        (((x) & 0x3))

/* REG_MM_DVFS_AHB_DCAM_AXI_INDEX4_MAP */

#define BIT_MM_DVFS_AHB_DCAM_AXI_VOL_INDEX4(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_DCAM_AXI_SEL_INDEX4(x)        (((x) & 0x3))

/* REG_MM_DVFS_AHB_DCAM_AXI_INDEX5_MAP */

#define BIT_MM_DVFS_AHB_DCAM_AXI_VOL_INDEX5(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_DCAM_AXI_SEL_INDEX5(x)        (((x) & 0x3))

/* REG_MM_DVFS_AHB_DCAM_AXI_INDEX6_MAP */

#define BIT_MM_DVFS_AHB_DCAM_AXI_VOL_INDEX6(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_DCAM_AXI_SEL_INDEX6(x)        (((x) & 0x3))

/* REG_MM_DVFS_AHB_DCAM_AXI_INDEX7_MAP */

#define BIT_MM_DVFS_AHB_DCAM_AXI_VOL_INDEX7(x)            (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_DCAM_AXI_SEL_INDEX7(x)        (((x) & 0x3))

/* REG_MM_DVFS_AHB_MM_MTX_INDEX0_MAP */

#define BIT_MM_DVFS_AHB_MM_MTX_VOL_INDEX0(x)              (((x) & 0x7) << 3)
#define BIT_MM_DVFS_AHB_CGM_MM_MTX_SEL_INDEX0(x)          (((x) & 0x7))

/* REG_MM_DVFS_AHB_MM_MTX_INDEX1_MAP */

#define BIT_MM_DVFS_AHB_MM_MTX_VOL_INDEX1(x)              (((x) & 0x7) << 3)
#define BIT_MM_DVFS_AHB_CGM_MM_MTX_SEL_INDEX1(x)          (((x) & 0x7))

/* REG_MM_DVFS_AHB_MM_MTX_INDEX2_MAP */

#define BIT_MM_DVFS_AHB_MM_MTX_VOL_INDEX2(x)              (((x) & 0x7) << 3)
#define BIT_MM_DVFS_AHB_CGM_MM_MTX_SEL_INDEX2(x)          (((x) & 0x7))

/* REG_MM_DVFS_AHB_MM_MTX_INDEX3_MAP */

#define BIT_MM_DVFS_AHB_MM_MTX_VOL_INDEX3(x)              (((x) & 0x7) << 3)
#define BIT_MM_DVFS_AHB_CGM_MM_MTX_SEL_INDEX3(x)          (((x) & 0x7))

/* REG_MM_DVFS_AHB_MM_MTX_INDEX4_MAP */

#define BIT_MM_DVFS_AHB_MM_MTX_VOL_INDEX4(x)              (((x) & 0x7) << 3)
#define BIT_MM_DVFS_AHB_CGM_MM_MTX_SEL_INDEX4(x)          (((x) & 0x7))

/* REG_MM_DVFS_AHB_MM_MTX_INDEX5_MAP */

#define BIT_MM_DVFS_AHB_MM_MTX_VOL_INDEX5(x)              (((x) & 0x7) << 3)
#define BIT_MM_DVFS_AHB_CGM_MM_MTX_SEL_INDEX5(x)          (((x) & 0x7))

/* REG_MM_DVFS_AHB_MM_MTX_INDEX6_MAP */

#define BIT_MM_DVFS_AHB_MM_MTX_VOL_INDEX6(x)              (((x) & 0x7) << 3)
#define BIT_MM_DVFS_AHB_CGM_MM_MTX_SEL_INDEX6(x)          (((x) & 0x7))

/* REG_MM_DVFS_AHB_MM_MTX_INDEX7_MAP */

#define BIT_MM_DVFS_AHB_MM_MTX_VOL_INDEX7(x)              (((x) & 0x7) << 3)
#define BIT_MM_DVFS_AHB_CGM_MM_MTX_SEL_INDEX7(x)          (((x) & 0x7))

/* REG_MM_DVFS_AHB_ISP_DVFS_INDEX_CFG */

#define BIT_MM_DVFS_AHB_ISP_DVFS_INDEX(x)                 (((x) & 0x7))

/* REG_MM_DVFS_AHB_ISP_DVFS_INDEX_IDLE_CFG */

#define BIT_MM_DVFS_AHB_ISP_DVFS_INDEX_IDLE(x)            (((x) & 0x7))

/* REG_MM_DVFS_AHB_JPG_DVFS_INDEX_CFG */

#define BIT_MM_DVFS_AHB_JPG_DVFS_INDEX(x)                 (((x) & 0x7))

/* REG_MM_DVFS_AHB_JPG_DVFS_INDEX_IDLE_CFG */

#define BIT_MM_DVFS_AHB_JPG_DVFS_INDEX_IDLE(x)            (((x) & 0x7))

/* REG_MM_DVFS_AHB_CPP_DVFS_INDEX_CFG */

#define BIT_MM_DVFS_AHB_CPP_DVFS_INDEX(x)                 (((x) & 0x7))

/* REG_MM_DVFS_AHB_CPP_DVFS_INDEX_IDLE_CFG */

#define BIT_MM_DVFS_AHB_CPP_DVFS_INDEX_IDLE(x)            (((x) & 0x7))

/* REG_MM_DVFS_AHB_MM_MTX_DVFS_INDEX_CFG */

#define BIT_MM_DVFS_AHB_MM_MTX_DVFS_INDEX(x)              (((x) & 0x7))

/* REG_MM_DVFS_AHB_MM_MTX_DVFS_INDEX_IDLE_CFG */

#define BIT_MM_DVFS_AHB_MM_MTX_DVFS_INDEX_IDLE(x)         (((x) & 0x7))

/* REG_MM_DVFS_AHB_DCAM_IF_DVFS_INDEX_CFG */

#define BIT_MM_DVFS_AHB_DCAM_IF_DVFS_INDEX(x)             (((x) & 0x7))

/* REG_MM_DVFS_AHB_DCAM_IF_DVFS_INDEX_IDLE_CFG */

#define BIT_MM_DVFS_AHB_DCAM_IF_DVFS_INDEX_IDLE(x)        (((x) & 0x7))

/* REG_MM_DVFS_AHB_DCAM_AXI_DVFS_INDEX_CFG */

#define BIT_MM_DVFS_AHB_DCAM_AXI_DVFS_INDEX(x)            (((x) & 0x7))

/* REG_MM_DVFS_AHB_DCAM_AXI_DVFS_INDEX_IDLE_CFG */

#define BIT_MM_DVFS_AHB_DCAM_AXI_DVFS_INDEX_IDLE(x)       (((x) & 0x7))

/* REG_MM_DVFS_AHB_FREQ_UPD_STATE */

#define BIT_MM_DVFS_AHB_FD_DVFS_FREQ_UPD_STATE(x)         (((x) & 0xF) << 24)
#define BIT_MM_DVFS_AHB_JPG_DVFS_FREQ_UPD_STATE(x)        (((x) & 0xF) << 20)
#define BIT_MM_DVFS_AHB_CPP_DVFS_FREQ_UPD_STATE(x)        (((x) & 0xF) << 16)
#define BIT_MM_DVFS_AHB_ISP_DVFS_FREQ_UPD_STATE(x)        (((x) & 0xF) << 12)
#define BIT_MM_DVFS_AHB_MM_MTX_DVFS_FREQ_UPD_STATE(x)     (((x) & 0xF) << 8)
#define BIT_MM_DVFS_AHB_DCAM_AXI_DVFS_FREQ_UPD_STATE(x)   (((x) & 0xF) << 4)
#define BIT_MM_DVFS_AHB_DCAM_IF_DVFS_FREQ_UPD_STATE(x)    (((x) & 0xF))

/* REG_MM_DVFS_AHB_MM_GFREE_WAIT_DELAY_CFG0 */

#define BIT_MM_DVFS_AHB_ISP_GFREE_WAIT_DELAY(x)           (((x) & 0x3FF) << 20)
#define BIT_MM_DVFS_AHB_CPP_GFREE_WAIT_DELAY(x)           (((x) & 0x3FF) << 10)
#define BIT_MM_DVFS_AHB_JPG_GFREE_WAIT_DELAY(x)           (((x) & 0x3FF))

/* REG_MM_DVFS_AHB_MM_GFREE_WAIT_DELAY_CFG1 */

#define BIT_MM_DVFS_AHB_MM_MTX_GFREE_WAIT_DELAY(x)        (((x) & 0x3FF) << 20)
#define BIT_MM_DVFS_AHB_DCAM_AXI_GFREE_WAIT_DELAY(x)      (((x) & 0x3FF) << 10)
#define BIT_MM_DVFS_AHB_DCAM_IF_GFREE_WAIT_DELAY(x)       (((x) & 0x3FF))

/* REG_MM_DVFS_AHB_MM_FREQ_UPD_TYPE_CFG */

#define BIT_MM_DVFS_AHB_FD_FREQ_UPD_DELAY_EN              BIT(13)
#define BIT_MM_DVFS_AHB_FD_FREQ_UPD_HDSK_EN               BIT(12)
#define BIT_MM_DVFS_AHB_ISP_FREQ_UPD_DELAY_EN             BIT(11)
#define BIT_MM_DVFS_AHB_ISP_FREQ_UPD_HDSK_EN              BIT(10)
#define BIT_MM_DVFS_AHB_CPP_FREQ_UPD_DELAY_EN             BIT(9)
#define BIT_MM_DVFS_AHB_CPP_FREQ_UPD_HDSK_EN              BIT(8)
#define BIT_MM_DVFS_AHB_JPG_FREQ_UPD_DELAY_EN             BIT(7)
#define BIT_MM_DVFS_AHB_JPG_FREQ_UPD_HDSK_EN              BIT(6)
#define BIT_MM_DVFS_AHB_MM_MTX_FREQ_UPD_DELAY_EN          BIT(5)
#define BIT_MM_DVFS_AHB_MM_MTX_FREQ_UPD_HDSK_EN           BIT(4)
#define BIT_MM_DVFS_AHB_DCAM_AXI_FREQ_UPD_DELAY_EN        BIT(3)
#define BIT_MM_DVFS_AHB_DCAM_AXI_FREQ_UPD_HDSK_EN         BIT(2)
#define BIT_MM_DVFS_AHB_DCAM_IF_FREQ_UPD_DELAY_EN         BIT(1)
#define BIT_MM_DVFS_AHB_DCAM_IF_FREQ_UPD_HDSK_EN          BIT(0)

/* REG_MM_DVFS_AHB_FD_INDEX0_MAP */

#define BIT_MM_DVFS_AHB_FD_VOL_INDEX0(x)                  (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_FD_VOTE_MTX_INDEX0(x)             (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_FD_SEL_INDEX0(x)              (((x) & 0x3))

/* REG_MM_DVFS_AHB_FD_INDEX1_MAP */

#define BIT_MM_DVFS_AHB_FD_VOL_INDEX1(x)                  (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_FD_VOTE_MTX_INDEX1(x)             (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_FD_SEL_INDEX1(x)              (((x) & 0x3))

/* REG_MM_DVFS_AHB_FD_INDEX2_MAP */

#define BIT_MM_DVFS_AHB_FD_VOL_INDEX2(x)                  (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_FD_VOTE_MTX_INDEX2(x)             (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_FD_SEL_INDEX2(x)              (((x) & 0x3))

/* REG_MM_DVFS_AHB_FD_INDEX3_MAP */

#define BIT_MM_DVFS_AHB_FD_VOL_INDEX3(x)                  (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_FD_VOTE_MTX_INDEX3(x)             (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_FD_SEL_INDEX3(x)              (((x) & 0x3))

/* REG_MM_DVFS_AHB_FD_INDEX4_MAP */

#define BIT_MM_DVFS_AHB_FD_VOL_INDEX4(x)                  (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_FD_VOTE_MTX_INDEX4(x)             (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_FD_SEL_INDEX4(x)              (((x) & 0x3))

/* REG_MM_DVFS_AHB_FD_INDEX5_MAP */

#define BIT_MM_DVFS_AHB_FD_VOL_INDEX5(x)                  (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_FD_VOTE_MTX_INDEX5(x)             (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_FD_SEL_INDEX5(x)              (((x) & 0x3))

/* REG_MM_DVFS_AHB_FD_INDEX6_MAP */

#define BIT_MM_DVFS_AHB_FD_VOL_INDEX6(x)                  (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_FD_VOTE_MTX_INDEX6(x)             (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_FD_SEL_INDEX6(x)              (((x) & 0x3))

/* REG_MM_DVFS_AHB_FD_INDEX7_MAP */

#define BIT_MM_DVFS_AHB_FD_VOL_INDEX7(x)                  (((x) & 0x7) << 5)
#define BIT_MM_DVFS_AHB_FD_VOTE_MTX_INDEX7(x)             (((x) & 0x7) << 2)
#define BIT_MM_DVFS_AHB_CGM_FD_SEL_INDEX7(x)              (((x) & 0x3))

/* REG_MM_DVFS_AHB_FD_DVFS_INDEX_CFG */

#define BIT_MM_DVFS_AHB_FD_DVFS_INDEX(x)                  (((x) & 0x7))

/* REG_MM_DVFS_AHB_FD_DVFS_INDEX_IDLE_CFG */

#define BIT_MM_DVFS_AHB_FD_DVFS_INDEX_IDLE(x)             (((x) & 0x7))

/* REG_MM_DVFS_AHB_MM_GFREE_WAIT_DELAY_CFG2 */

#define BIT_MM_DVFS_AHB_FD_GFREE_WAIT_DELAY(x)            (((x) & 0x3FF))

/* REG_MM_DVFS_AHB_MM_DFS_IDLE_DISABLE_CFG */

#define BIT_MM_DVFS_AHB_MM_MTX_DFS_IDLE_DISABLE           BIT(6)
#define BIT_MM_DVFS_AHB_MM_FD_DFS_IDLE_DISABLE            BIT(5)
#define BIT_MM_DVFS_AHB_MM_ISP_DFS_IDLE_DISABLE           BIT(4)
#define BIT_MM_DVFS_AHB_MM_CPP_DFS_IDLE_DISABLE           BIT(3)
#define BIT_MM_DVFS_AHB_MM_JPG_DFS_IDLE_DISABLE           BIT(2)
#define BIT_MM_DVFS_AHB_MM_DCAM_AXI_DFS_IDLE_DISABLE      BIT(1)
#define BIT_MM_DVFS_AHB_MM_DCAM_IF_DFS_IDLE_DISABLE       BIT(0)

/* REG_MM_DVFS_AHB_MM_DVFS_RESERVED_REG_CFG0 */

#define BIT_MM_DVFS_AHB_DVFS_RES_REG0(x)                  (((x) & 0xFFFFFFFF))

/* REG_MM_DVFS_AHB_MM_DVFS_RESERVED_REG_CFG1 */

#define BIT_MM_DVFS_AHB_DVFS_RES_REG1(x)                  (((x) & 0xFFFFFFFF))

/* REG_MM_DVFS_AHB_MM_DVFS_RESERVED_REG_CFG2 */

#define BIT_MM_DVFS_AHB_DVFS_RES_REG2(x)                  (((x) & 0xFFFFFFFF))

/* REG_MM_DVFS_AHB_MM_DVFS_RESERVED_REG_CFG3 */

#define BIT_MM_DVFS_AHB_DVFS_RES_REG3(x)                  (((x) & 0xFFFFFFFF))


#endif /* MM_DVFS_AHB_H */


