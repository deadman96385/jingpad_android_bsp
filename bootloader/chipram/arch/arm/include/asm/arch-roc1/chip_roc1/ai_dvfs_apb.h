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


#ifndef AI_DVFS_APB_H
#define AI_DVFS_APB_H

#define CTL_BASE_AI_DVFS_APB 0x6FD0C000


#define REG_AI_DVFS_APB_AI_DVFS_HOLD_CTRL                  ( CTL_BASE_AI_DVFS_APB + 0x0000 )
#define REG_AI_DVFS_APB_AI_DVFS_WAIT_WINDOW_CFG            ( CTL_BASE_AI_DVFS_APB + 0x0004 )
#define REG_AI_DVFS_APB_AI_MIN_VOLTAGE_CFG                 ( CTL_BASE_AI_DVFS_APB + 0x0008 )
#define REG_AI_DVFS_APB_AI_SW_DVFS_CTRL                    ( CTL_BASE_AI_DVFS_APB + 0x000C )
#define REG_AI_DVFS_APB_AI_FREQ_UPDATE_BYPASS              ( CTL_BASE_AI_DVFS_APB + 0x0010 )
#define REG_AI_DVFS_APB_CGM_AI_DVFS_CLK_GATE_CTRL          ( CTL_BASE_AI_DVFS_APB + 0x0014 )
#define REG_AI_DVFS_APB_AI_DFS_EN_CTRL                     ( CTL_BASE_AI_DVFS_APB + 0x0018 )
#define REG_AI_DVFS_APB_AI_DVFS_VOLTAGE_DBG                ( CTL_BASE_AI_DVFS_APB + 0x001C )
#define REG_AI_DVFS_APB_AI_DVFS_CGM_CFG_DBG                ( CTL_BASE_AI_DVFS_APB + 0x0020 )
#define REG_AI_DVFS_APB_AI_DVFS_STATE_DBG                  ( CTL_BASE_AI_DVFS_APB + 0x0024 )
#define REG_AI_DVFS_APB_AI_CAMBRICON_INDEX0_MAP            ( CTL_BASE_AI_DVFS_APB + 0x0030 )
#define REG_AI_DVFS_APB_AI_POWERVR_INDEX0_MAP              ( CTL_BASE_AI_DVFS_APB + 0x0034 )
#define REG_AI_DVFS_APB_AI_AI_MTX_INDEX0_MAP               ( CTL_BASE_AI_DVFS_APB + 0x0038 )
#define REG_AI_DVFS_APB_AI_CAMBRICON_INDEX1_MAP            ( CTL_BASE_AI_DVFS_APB + 0x0040 )
#define REG_AI_DVFS_APB_AI_POWERVR_INDEX1_MAP              ( CTL_BASE_AI_DVFS_APB + 0x0044 )
#define REG_AI_DVFS_APB_AI_AI_MTX_INDEX1_MAP               ( CTL_BASE_AI_DVFS_APB + 0x0048 )
#define REG_AI_DVFS_APB_AI_CAMBRICON_INDEX2_MAP            ( CTL_BASE_AI_DVFS_APB + 0x0050 )
#define REG_AI_DVFS_APB_AI_POWERVR_INDEX2_MAP              ( CTL_BASE_AI_DVFS_APB + 0x0054 )
#define REG_AI_DVFS_APB_AI_AI_MTX_INDEX2_MAP               ( CTL_BASE_AI_DVFS_APB + 0x0058 )
#define REG_AI_DVFS_APB_AI_CAMBRICON_INDEX3_MAP            ( CTL_BASE_AI_DVFS_APB + 0x0060 )
#define REG_AI_DVFS_APB_AI_POWERVR_INDEX3_MAP              ( CTL_BASE_AI_DVFS_APB + 0x0064 )
#define REG_AI_DVFS_APB_AI_AI_MTX_INDEX3_MAP               ( CTL_BASE_AI_DVFS_APB + 0x0068 )
#define REG_AI_DVFS_APB_AI_CAMBRICON_INDEX4_MAP            ( CTL_BASE_AI_DVFS_APB + 0x0070 )
#define REG_AI_DVFS_APB_AI_POWERVR_INDEX4_MAP              ( CTL_BASE_AI_DVFS_APB + 0x0074 )
#define REG_AI_DVFS_APB_AI_AI_MTX_INDEX4_MAP               ( CTL_BASE_AI_DVFS_APB + 0x0078 )
#define REG_AI_DVFS_APB_AI_CAMBRICON_INDEX5_MAP            ( CTL_BASE_AI_DVFS_APB + 0x0080 )
#define REG_AI_DVFS_APB_AI_POWERVR_INDEX5_MAP              ( CTL_BASE_AI_DVFS_APB + 0x0084 )
#define REG_AI_DVFS_APB_AI_AI_MTX_INDEX5_MAP               ( CTL_BASE_AI_DVFS_APB + 0x0088 )
#define REG_AI_DVFS_APB_AI_CAMBRICON_INDEX6_MAP            ( CTL_BASE_AI_DVFS_APB + 0x0090 )
#define REG_AI_DVFS_APB_AI_POWERVR_INDEX6_MAP              ( CTL_BASE_AI_DVFS_APB + 0x0094 )
#define REG_AI_DVFS_APB_AI_AI_MTX_INDEX6_MAP               ( CTL_BASE_AI_DVFS_APB + 0x0098 )
#define REG_AI_DVFS_APB_AI_CAMBRICON_INDEX7_MAP            ( CTL_BASE_AI_DVFS_APB + 0x00A0 )
#define REG_AI_DVFS_APB_AI_POWERVR_INDEX7_MAP              ( CTL_BASE_AI_DVFS_APB + 0x00A4 )
#define REG_AI_DVFS_APB_AI_AI_MTX_INDEX7_MAP               ( CTL_BASE_AI_DVFS_APB + 0x00A8 )
#define REG_AI_DVFS_APB_POWERVR_DVFS_INDEX_CFG             ( CTL_BASE_AI_DVFS_APB + 0x00B0 )
#define REG_AI_DVFS_APB_POWERVR_DVFS_INDEX_IDLE_CFG        ( CTL_BASE_AI_DVFS_APB + 0x00B4 )
#define REG_AI_DVFS_APB_CAMBRICON_DVFS_INDEX_CFG           ( CTL_BASE_AI_DVFS_APB + 0x00B8 )
#define REG_AI_DVFS_APB_CAMBRICON_DVFS_INDEX_IDLE_CFG      ( CTL_BASE_AI_DVFS_APB + 0x00BC )
#define REG_AI_DVFS_APB_AI_MTX_DVFS_INDEX_CFG              ( CTL_BASE_AI_DVFS_APB + 0x00C0 )
#define REG_AI_DVFS_APB_AI_MTX_DVFS_INDEX_IDLE_CFG         ( CTL_BASE_AI_DVFS_APB + 0x00C4 )
#define REG_AI_DVFS_APB_AI_FREQ_UPD_STATE                  ( CTL_BASE_AI_DVFS_APB + 0x00C8 )
#define REG_AI_DVFS_APB_AI_GFREE_WAIT_DELAY_CFG0           ( CTL_BASE_AI_DVFS_APB + 0x00CC )
#define REG_AI_DVFS_APB_AI_GFREE_WAIT_DELAY_CFG1           ( CTL_BASE_AI_DVFS_APB + 0x00D0 )
#define REG_AI_DVFS_APB_AI_GFREE_WAIT_DELAY_CFG2           ( CTL_BASE_AI_DVFS_APB + 0x00D4 )
#define REG_AI_DVFS_APB_AI_FREQ_UPD_TYPE_CFG               ( CTL_BASE_AI_DVFS_APB + 0x00D8 )
#define REG_AI_DVFS_APB_AI_DFS_IDLE_DISABLE_CFG            ( CTL_BASE_AI_DVFS_APB + 0x00DC )
#define REG_AI_DVFS_APB_AI_DVFS_RESERVED_REG_CFG0          ( CTL_BASE_AI_DVFS_APB + 0x00E0 )
#define REG_AI_DVFS_APB_AI_DVFS_RESERVED_REG_CFG1          ( CTL_BASE_AI_DVFS_APB + 0x00E4 )
#define REG_AI_DVFS_APB_AI_DVFS_RESERVED_REG_CFG2          ( CTL_BASE_AI_DVFS_APB + 0x00E8 )
#define REG_AI_DVFS_APB_AI_DVFS_RESERVED_REG_CFG3          ( CTL_BASE_AI_DVFS_APB + 0x00EC )

/* REG_AI_DVFS_APB_AI_DVFS_HOLD_CTRL */

#define BIT_AI_DVFS_APB_AI_DVFS_HOLD                        BIT(0)

/* REG_AI_DVFS_APB_AI_DVFS_WAIT_WINDOW_CFG */

#define BIT_AI_DVFS_APB_AI_DVFS_UP_WINDOW(x)                (((x) & 0xFFFF) << 16)
#define BIT_AI_DVFS_APB_AI_DVFS_DOWN_WINDOW(x)              (((x) & 0xFFFF))

/* REG_AI_DVFS_APB_AI_MIN_VOLTAGE_CFG */

#define BIT_AI_DVFS_APB_AI_SYS_MIN_VOLTAGE(x)               (((x) & 0x7))

/* REG_AI_DVFS_APB_AI_SW_DVFS_CTRL */

#define BIT_AI_DVFS_APB_AI_DVFS_ACK                         BIT(8)
#define BIT_AI_DVFS_APB_AI_DVFS_VOLTAGE_SW(x)               (((x) & 0x7) << 4)
#define BIT_AI_DVFS_APB_AI_CURRENT_VOLTAGE_SW(x)            (((x) & 0x7) << 1)
#define BIT_AI_DVFS_APB_AI_DVFS_REQ_SW                      BIT(0)

/* REG_AI_DVFS_APB_AI_FREQ_UPDATE_BYPASS */

#define BIT_AI_DVFS_APB_REG_POWERVR_FREQ_UPD_EN_BYP         BIT(2)
#define BIT_AI_DVFS_APB_REG_CAMBRICON_FREQ_UPD_EN_BYP       BIT(1)
#define BIT_AI_DVFS_APB_REG_AI_MTX_FREQ_UPD_EN_BYP          BIT(0)

/* REG_AI_DVFS_APB_CGM_AI_DVFS_CLK_GATE_CTRL */

#define BIT_AI_DVFS_APB_CGM_AI_DVFS_FORCE_EN                BIT(1)
#define BIT_AI_DVFS_APB_CGM_AI_DVFS_AUTO_GATE_SEL           BIT(0)

/* REG_AI_DVFS_APB_AI_DFS_EN_CTRL */

#define BIT_AI_DVFS_APB_AI_MTX_AUTO_TUNE_EN                 BIT(0)

/* REG_AI_DVFS_APB_AI_DVFS_VOLTAGE_DBG */

#define BIT_AI_DVFS_APB_AI_CURRENT_VOLTAGE(x)               (((x) & 0x7) << 12)
#define BIT_AI_DVFS_APB_POWERVR_VOLTAGE(x)                  (((x) & 0x7) << 9)
#define BIT_AI_DVFS_APB_CAMBRICON_VOLTAGE(x)                (((x) & 0x7) << 6)
#define BIT_AI_DVFS_APB_AI_MTX_VOLTAGE(x)                   (((x) & 0x7) << 3)
#define BIT_AI_DVFS_APB_AI_INTERNAL_VOTE_VOLTAGE(x)         (((x) & 0x7))

/* REG_AI_DVFS_APB_AI_DVFS_CGM_CFG_DBG */

#define BIT_AI_DVFS_APB_CGM_POWERVR_FDIV_DENOM_DVFS(x)      (((x) & 0xF) << 26)
#define BIT_AI_DVFS_APB_CGM_POWERVR_FDIV_NUM_DVFS(x)        (((x) & 0xF) << 22)
#define BIT_AI_DVFS_APB_CGM_POWERVR_SEL_DVFS                BIT(21)
#define BIT_AI_DVFS_APB_CGM_POWERVR_DIV_DVFS(x)             (((x) & 0x7) << 18)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_FDIV_DENOM_DVFS(x)    (((x) & 0xF) << 14)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_FDIV_NUM_DVFS(x)      (((x) & 0xF) << 10)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_SEL_DVFS(x)           (((x) & 0x3) << 8)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_DIV_DVFS(x)           (((x) & 0x7) << 5)
#define BIT_AI_DVFS_APB_CGM_AI_MTX_SEL_DVFS(x)              (((x) & 0x3) << 3)
#define BIT_AI_DVFS_APB_CGM_AI_MTX_DIV_DVFS(x)              (((x) & 0x7))

/* REG_AI_DVFS_APB_AI_DVFS_STATE_DBG */

#define BIT_AI_DVFS_APB_AI_SYS_DVFS_BUSY                    BIT(19)
#define BIT_AI_DVFS_APB_AI_DVFS_WINDOW_CNT(x)               (((x) & 0xFFFF) << 3)
#define BIT_AI_DVFS_APB_AI_DVFS_STATE(x)                    (((x) & 0x7))

/* REG_AI_DVFS_APB_AI_CAMBRICON_INDEX0_MAP */

#define BIT_AI_DVFS_APB_CAMBRICON_VOL_INDEX0(x)             (((x) & 0x7) << 16)
#define BIT_AI_DVFS_APB_CAMBRICON_VOTE_MTX_INDEX0(x)        (((x) & 0x7) << 13)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_FDIV_DENOM_INDEX0(x)  (((x) & 0xF) << 9)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_FDIV_NUM_INDEX0(x)    (((x) & 0xF) << 5)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_DIV_INDEX0(x)         (((x) & 0x7) << 2)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_SEL_INDEX0(x)         (((x) & 0x3))

/* REG_AI_DVFS_APB_AI_POWERVR_INDEX0_MAP */

#define BIT_AI_DVFS_APB_POWERVR_VOL_INDEX0(x)               (((x) & 0x7) << 15)
#define BIT_AI_DVFS_APB_POWERVR_VOTE_MTX_INDEX0(x)          (((x) & 0x7) << 12)
#define BIT_AI_DVFS_APB_CGM_POWERVR_FDIV_DENOM_INDEX0(x)    (((x) & 0xF) << 8)
#define BIT_AI_DVFS_APB_CGM_POWERVR_FDIV_NUM_INDEX0(x)      (((x) & 0xF) << 4)
#define BIT_AI_DVFS_APB_CGM_POWERVR_DIV_INDEX0(x)           (((x) & 0x7) << 1)
#define BIT_AI_DVFS_APB_CGM_POWERVR_SEL_INDEX0              BIT(0)

/* REG_AI_DVFS_APB_AI_AI_MTX_INDEX0_MAP */

#define BIT_AI_DVFS_APB_AI_MTX_VOL_INDEX0(x)                (((x) & 0x7) << 5)
#define BIT_AI_DVFS_APB_CGM_AI_MTX_DIV_INDEX0(x)            (((x) & 0x7) << 2)
#define BIT_AI_DVFS_APB_CGM_AI_MTX_SEL_INDEX0(x)            (((x) & 0x3))

/* REG_AI_DVFS_APB_AI_CAMBRICON_INDEX1_MAP */

#define BIT_AI_DVFS_APB_CAMBRICON_VOL_INDEX1(x)             (((x) & 0x7) << 16)
#define BIT_AI_DVFS_APB_CAMBRICON_VOTE_MTX_INDEX1(x)        (((x) & 0x7) << 13)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_FDIV_DENOM_INDEX1(x)  (((x) & 0xF) << 9)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_FDIV_NUM_INDEX1(x)    (((x) & 0xF) << 5)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_DIV_INDEX1(x)         (((x) & 0x7) << 2)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_SEL_INDEX1(x)         (((x) & 0x3))

/* REG_AI_DVFS_APB_AI_POWERVR_INDEX1_MAP */

#define BIT_AI_DVFS_APB_POWERVR_VOL_INDEX1(x)               (((x) & 0x7) << 15)
#define BIT_AI_DVFS_APB_POWERVR_VOTE_MTX_INDEX1(x)          (((x) & 0x7) << 12)
#define BIT_AI_DVFS_APB_CGM_POWERVR_FDIV_DENOM_INDEX1(x)    (((x) & 0xF) << 8)
#define BIT_AI_DVFS_APB_CGM_POWERVR_FDIV_NUM_INDEX1(x)      (((x) & 0xF) << 4)
#define BIT_AI_DVFS_APB_CGM_POWERVR_DIV_INDEX1(x)           (((x) & 0x7) << 1)
#define BIT_AI_DVFS_APB_CGM_POWERVR_SEL_INDEX1              BIT(0)

/* REG_AI_DVFS_APB_AI_AI_MTX_INDEX1_MAP */

#define BIT_AI_DVFS_APB_AI_MTX_VOL_INDEX1(x)                (((x) & 0x7) << 5)
#define BIT_AI_DVFS_APB_CGM_AI_MTX_DIV_INDEX1(x)            (((x) & 0x7) << 2)
#define BIT_AI_DVFS_APB_CGM_AI_MTX_SEL_INDEX1(x)            (((x) & 0x3))

/* REG_AI_DVFS_APB_AI_CAMBRICON_INDEX2_MAP */

#define BIT_AI_DVFS_APB_CAMBRICON_VOL_INDEX2(x)             (((x) & 0x7) << 16)
#define BIT_AI_DVFS_APB_CAMBRICON_VOTE_MTX_INDEX2(x)        (((x) & 0x7) << 13)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_FDIV_DENOM_INDEX2(x)  (((x) & 0xF) << 9)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_FDIV_NUM_INDEX2(x)    (((x) & 0xF) << 5)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_DIV_INDEX2(x)         (((x) & 0x7) << 2)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_SEL_INDEX2(x)         (((x) & 0x3))

/* REG_AI_DVFS_APB_AI_POWERVR_INDEX2_MAP */

#define BIT_AI_DVFS_APB_POWERVR_VOL_INDEX2(x)               (((x) & 0x7) << 15)
#define BIT_AI_DVFS_APB_POWERVR_VOTE_MTX_INDEX2(x)          (((x) & 0x7) << 12)
#define BIT_AI_DVFS_APB_CGM_POWERVR_FDIV_DENOM_INDEX2(x)    (((x) & 0xF) << 8)
#define BIT_AI_DVFS_APB_CGM_POWERVR_FDIV_NUM_INDEX2(x)      (((x) & 0xF) << 4)
#define BIT_AI_DVFS_APB_CGM_POWERVR_DIV_INDEX2(x)           (((x) & 0x7) << 1)
#define BIT_AI_DVFS_APB_CGM_POWERVR_SEL_INDEX2              BIT(0)

/* REG_AI_DVFS_APB_AI_AI_MTX_INDEX2_MAP */

#define BIT_AI_DVFS_APB_AI_MTX_VOL_INDEX2(x)                (((x) & 0x7) << 5)
#define BIT_AI_DVFS_APB_CGM_AI_MTX_DIV_INDEX2(x)            (((x) & 0x7) << 2)
#define BIT_AI_DVFS_APB_CGM_AI_MTX_SEL_INDEX2(x)            (((x) & 0x3))

/* REG_AI_DVFS_APB_AI_CAMBRICON_INDEX3_MAP */

#define BIT_AI_DVFS_APB_CAMBRICON_VOL_INDEX3(x)             (((x) & 0x7) << 16)
#define BIT_AI_DVFS_APB_CAMBRICON_VOTE_MTX_INDEX3(x)        (((x) & 0x7) << 13)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_FDIV_DENOM_INDEX3(x)  (((x) & 0xF) << 9)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_FDIV_NUM_INDEX3(x)    (((x) & 0xF) << 5)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_DIV_INDEX3(x)         (((x) & 0x7) << 2)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_SEL_INDEX3(x)         (((x) & 0x3))

/* REG_AI_DVFS_APB_AI_POWERVR_INDEX3_MAP */

#define BIT_AI_DVFS_APB_POWERVR_VOL_INDEX3(x)               (((x) & 0x7) << 15)
#define BIT_AI_DVFS_APB_POWERVR_VOTE_MTX_INDEX3(x)          (((x) & 0x7) << 12)
#define BIT_AI_DVFS_APB_CGM_POWERVR_FDIV_DENOM_INDEX3(x)    (((x) & 0xF) << 8)
#define BIT_AI_DVFS_APB_CGM_POWERVR_FDIV_NUM_INDEX3(x)      (((x) & 0xF) << 4)
#define BIT_AI_DVFS_APB_CGM_POWERVR_DIV_INDEX3(x)           (((x) & 0x7) << 1)
#define BIT_AI_DVFS_APB_CGM_POWERVR_SEL_INDEX3              BIT(0)

/* REG_AI_DVFS_APB_AI_AI_MTX_INDEX3_MAP */

#define BIT_AI_DVFS_APB_AI_MTX_VOL_INDEX3(x)                (((x) & 0x7) << 5)
#define BIT_AI_DVFS_APB_CGM_AI_MTX_DIV_INDEX3(x)            (((x) & 0x7) << 2)
#define BIT_AI_DVFS_APB_CGM_AI_MTX_SEL_INDEX3(x)            (((x) & 0x3))

/* REG_AI_DVFS_APB_AI_CAMBRICON_INDEX4_MAP */

#define BIT_AI_DVFS_APB_CAMBRICON_VOL_INDEX4(x)             (((x) & 0x7) << 16)
#define BIT_AI_DVFS_APB_CAMBRICON_VOTE_MTX_INDEX4(x)        (((x) & 0x7) << 13)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_FDIV_DENOM_INDEX4(x)  (((x) & 0xF) << 9)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_FDIV_NUM_INDEX4(x)    (((x) & 0xF) << 5)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_DIV_INDEX4(x)         (((x) & 0x7) << 2)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_SEL_INDEX4(x)         (((x) & 0x3))

/* REG_AI_DVFS_APB_AI_POWERVR_INDEX4_MAP */

#define BIT_AI_DVFS_APB_POWERVR_VOL_INDEX4(x)               (((x) & 0x7) << 15)
#define BIT_AI_DVFS_APB_POWERVR_VOTE_MTX_INDEX4(x)          (((x) & 0x7) << 12)
#define BIT_AI_DVFS_APB_CGM_POWERVR_FDIV_DENOM_INDEX4(x)    (((x) & 0xF) << 8)
#define BIT_AI_DVFS_APB_CGM_POWERVR_FDIV_NUM_INDEX4(x)      (((x) & 0xF) << 4)
#define BIT_AI_DVFS_APB_CGM_POWERVR_DIV_INDEX4(x)           (((x) & 0x7) << 1)
#define BIT_AI_DVFS_APB_CGM_POWERVR_SEL_INDEX4              BIT(0)

/* REG_AI_DVFS_APB_AI_AI_MTX_INDEX4_MAP */

#define BIT_AI_DVFS_APB_AI_MTX_VOL_INDEX4(x)                (((x) & 0x7) << 5)
#define BIT_AI_DVFS_APB_CGM_AI_MTX_DIV_INDEX4(x)            (((x) & 0x7) << 2)
#define BIT_AI_DVFS_APB_CGM_AI_MTX_SEL_INDEX4(x)            (((x) & 0x3))

/* REG_AI_DVFS_APB_AI_CAMBRICON_INDEX5_MAP */

#define BIT_AI_DVFS_APB_CAMBRICON_VOL_INDEX5(x)             (((x) & 0x7) << 16)
#define BIT_AI_DVFS_APB_CAMBRICON_VOTE_MTX_INDEX5(x)        (((x) & 0x7) << 13)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_FDIV_DENOM_INDEX5(x)  (((x) & 0xF) << 9)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_FDIV_NUM_INDEX5(x)    (((x) & 0xF) << 5)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_DIV_INDEX5(x)         (((x) & 0x7) << 2)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_SEL_INDEX5(x)         (((x) & 0x3))

/* REG_AI_DVFS_APB_AI_POWERVR_INDEX5_MAP */

#define BIT_AI_DVFS_APB_POWERVR_VOL_INDEX5(x)               (((x) & 0x7) << 15)
#define BIT_AI_DVFS_APB_POWERVR_VOTE_MTX_INDEX5(x)          (((x) & 0x7) << 12)
#define BIT_AI_DVFS_APB_CGM_POWERVR_FDIV_DENOM_INDEX5(x)    (((x) & 0xF) << 8)
#define BIT_AI_DVFS_APB_CGM_POWERVR_FDIV_NUM_INDEX5(x)      (((x) & 0xF) << 4)
#define BIT_AI_DVFS_APB_CGM_POWERVR_DIV_INDEX5(x)           (((x) & 0x7) << 1)
#define BIT_AI_DVFS_APB_CGM_POWERVR_SEL_INDEX5              BIT(0)

/* REG_AI_DVFS_APB_AI_AI_MTX_INDEX5_MAP */

#define BIT_AI_DVFS_APB_AI_MTX_VOL_INDEX5(x)                (((x) & 0x7) << 5)
#define BIT_AI_DVFS_APB_CGM_AI_MTX_DIV_INDEX5(x)            (((x) & 0x7) << 2)
#define BIT_AI_DVFS_APB_CGM_AI_MTX_SEL_INDEX5(x)            (((x) & 0x3))

/* REG_AI_DVFS_APB_AI_CAMBRICON_INDEX6_MAP */

#define BIT_AI_DVFS_APB_CAMBRICON_VOL_INDEX6(x)             (((x) & 0x7) << 16)
#define BIT_AI_DVFS_APB_CAMBRICON_VOTE_MTX_INDEX6(x)        (((x) & 0x7) << 13)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_FDIV_DENOM_INDEX6(x)  (((x) & 0xF) << 9)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_FDIV_NUM_INDEX6(x)    (((x) & 0xF) << 5)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_DIV_INDEX6(x)         (((x) & 0x7) << 2)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_SEL_INDEX6(x)         (((x) & 0x3))

/* REG_AI_DVFS_APB_AI_POWERVR_INDEX6_MAP */

#define BIT_AI_DVFS_APB_POWERVR_VOL_INDEX6(x)               (((x) & 0x7) << 15)
#define BIT_AI_DVFS_APB_POWERVR_VOTE_MTX_INDEX6(x)          (((x) & 0x7) << 12)
#define BIT_AI_DVFS_APB_CGM_POWERVR_FDIV_DENOM_INDEX6(x)    (((x) & 0xF) << 8)
#define BIT_AI_DVFS_APB_CGM_POWERVR_FDIV_NUM_INDEX6(x)      (((x) & 0xF) << 4)
#define BIT_AI_DVFS_APB_CGM_POWERVR_DIV_INDEX6(x)           (((x) & 0x7) << 1)
#define BIT_AI_DVFS_APB_CGM_POWERVR_SEL_INDEX6              BIT(0)

/* REG_AI_DVFS_APB_AI_AI_MTX_INDEX6_MAP */

#define BIT_AI_DVFS_APB_AI_MTX_VOL_INDEX6(x)                (((x) & 0x7) << 5)
#define BIT_AI_DVFS_APB_CGM_AI_MTX_DIV_INDEX6(x)            (((x) & 0x7) << 2)
#define BIT_AI_DVFS_APB_CGM_AI_MTX_SEL_INDEX6(x)            (((x) & 0x3))

/* REG_AI_DVFS_APB_AI_CAMBRICON_INDEX7_MAP */

#define BIT_AI_DVFS_APB_CAMBRICON_VOL_INDEX7(x)             (((x) & 0x7) << 16)
#define BIT_AI_DVFS_APB_CAMBRICON_VOTE_MTX_INDEX7(x)        (((x) & 0x7) << 13)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_FDIV_DENOM_INDEX7(x)  (((x) & 0xF) << 9)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_FDIV_NUM_INDEX7(x)    (((x) & 0xF) << 5)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_DIV_INDEX7(x)         (((x) & 0x7) << 2)
#define BIT_AI_DVFS_APB_CGM_CAMBRICON_SEL_INDEX7(x)         (((x) & 0x3))

/* REG_AI_DVFS_APB_AI_POWERVR_INDEX7_MAP */

#define BIT_AI_DVFS_APB_POWERVR_VOL_INDEX7(x)               (((x) & 0x7) << 15)
#define BIT_AI_DVFS_APB_POWERVR_VOTE_MTX_INDEX7(x)          (((x) & 0x7) << 12)
#define BIT_AI_DVFS_APB_CGM_POWERVR_FDIV_DENOM_INDEX7(x)    (((x) & 0xF) << 8)
#define BIT_AI_DVFS_APB_CGM_POWERVR_FDIV_NUM_INDEX7(x)      (((x) & 0xF) << 4)
#define BIT_AI_DVFS_APB_CGM_POWERVR_DIV_INDEX7(x)           (((x) & 0x7) << 1)
#define BIT_AI_DVFS_APB_CGM_POWERVR_SEL_INDEX7              BIT(0)

/* REG_AI_DVFS_APB_AI_AI_MTX_INDEX7_MAP */

#define BIT_AI_DVFS_APB_AI_MTX_VOL_INDEX7(x)                (((x) & 0x7) << 5)
#define BIT_AI_DVFS_APB_CGM_AI_MTX_DIV_INDEX7(x)            (((x) & 0x7) << 2)
#define BIT_AI_DVFS_APB_CGM_AI_MTX_SEL_INDEX7(x)            (((x) & 0x3))

/* REG_AI_DVFS_APB_POWERVR_DVFS_INDEX_CFG */

#define BIT_AI_DVFS_APB_POWERVR_DVFS_INDEX(x)               (((x) & 0x7))

/* REG_AI_DVFS_APB_POWERVR_DVFS_INDEX_IDLE_CFG */

#define BIT_AI_DVFS_APB_POWERVR_DVFS_INDEX_IDLE(x)          (((x) & 0x7))

/* REG_AI_DVFS_APB_CAMBRICON_DVFS_INDEX_CFG */

#define BIT_AI_DVFS_APB_CAMBRICON_DVFS_INDEX(x)             (((x) & 0x7))

/* REG_AI_DVFS_APB_CAMBRICON_DVFS_INDEX_IDLE_CFG */

#define BIT_AI_DVFS_APB_CAMBRICON_DVFS_INDEX_IDLE(x)        (((x) & 0x7))

/* REG_AI_DVFS_APB_AI_MTX_DVFS_INDEX_CFG */

#define BIT_AI_DVFS_APB_AI_MTX_DVFS_INDEX(x)                (((x) & 0x7))

/* REG_AI_DVFS_APB_AI_MTX_DVFS_INDEX_IDLE_CFG */

#define BIT_AI_DVFS_APB_AI_MTX_DVFS_INDEX_IDLE(x)           (((x) & 0x7))

/* REG_AI_DVFS_APB_AI_FREQ_UPD_STATE */

#define BIT_AI_DVFS_APB_POWERVR_DVFS_FREQ_UPD_STATE(x)      (((x) & 0xF) << 8)
#define BIT_AI_DVFS_APB_CAMBRICON_DVFS_FREQ_UPD_STATE(x)    (((x) & 0xF) << 4)
#define BIT_AI_DVFS_APB_AI_MTX_DVFS_FREQ_UPD_STATE(x)       (((x) & 0xF))

/* REG_AI_DVFS_APB_AI_GFREE_WAIT_DELAY_CFG0 */

#define BIT_AI_DVFS_APB_POWERVR_GFREE_WAIT_DELAY(x)         (((x) & 0x3FF))

/* REG_AI_DVFS_APB_AI_GFREE_WAIT_DELAY_CFG1 */

#define BIT_AI_DVFS_APB_CAMBRICON_GFREE_WAIT_DELAY(x)       (((x) & 0x3FF))

/* REG_AI_DVFS_APB_AI_GFREE_WAIT_DELAY_CFG2 */

#define BIT_AI_DVFS_APB_AI_MTX_GFREE_WAIT_DELAY(x)          (((x) & 0x3FF))

/* REG_AI_DVFS_APB_AI_FREQ_UPD_TYPE_CFG */

#define BIT_AI_DVFS_APB_POWERVR_FREQ_UPD_DELAY_EN           BIT(5)
#define BIT_AI_DVFS_APB_CAMBRICON_FREQ_UPD_DELAY_EN         BIT(4)
#define BIT_AI_DVFS_APB_AI_MTX_FREQ_UPD_DELAY_EN            BIT(3)
#define BIT_AI_DVFS_APB_POWERVR_FREQ_UPD_HDSK_EN            BIT(2)
#define BIT_AI_DVFS_APB_CAMBRICON_FREQ_UPD_HDSK_EN          BIT(1)
#define BIT_AI_DVFS_APB_AI_MTX_FREQ_UPD_HDSK_EN             BIT(0)

/* REG_AI_DVFS_APB_AI_DFS_IDLE_DISABLE_CFG */

#define BIT_AI_DVFS_APB_AI_POWERVR_DFS_IDLE_DISABLE         BIT(2)
#define BIT_AI_DVFS_APB_AI_CAMBRICON_DFS_IDLE_DISABLE       BIT(1)
#define BIT_AI_DVFS_APB_AI_MTX_DFS_IDLE_DISABLE             BIT(0)

/* REG_AI_DVFS_APB_AI_DVFS_RESERVED_REG_CFG0 */

#define BIT_AI_DVFS_APB_DVFS_RES_REG0(x)                    (((x) & 0xFFFFFFFF))

/* REG_AI_DVFS_APB_AI_DVFS_RESERVED_REG_CFG1 */

#define BIT_AI_DVFS_APB_DVFS_RES_REG1(x)                    (((x) & 0xFFFFFFFF))

/* REG_AI_DVFS_APB_AI_DVFS_RESERVED_REG_CFG2 */

#define BIT_AI_DVFS_APB_DVFS_RES_REG2(x)                    (((x) & 0xFFFFFFFF))

/* REG_AI_DVFS_APB_AI_DVFS_RESERVED_REG_CFG3 */

#define BIT_AI_DVFS_APB_DVFS_RES_REG3(x)                    (((x) & 0xFFFFFFFF))


#endif /* AI_DVFS_APB_H */


