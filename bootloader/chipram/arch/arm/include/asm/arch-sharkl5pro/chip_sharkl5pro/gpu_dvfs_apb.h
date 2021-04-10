/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-06 15:47:51
 *
 */

#ifndef GPU_DVFS_APB_H
#define GPU_DVFS_APB_H

#define CTL_BASE_GPU_DVFS_APB 0x60110000

#define REG_GPU_DVFS_APB_GPU_DVFS_HOLD_CTRL                ( CTL_BASE_GPU_DVFS_APB + 0x0000 )
#define REG_GPU_DVFS_APB_GPU_MIN_VOLTAGE_CFG               ( CTL_BASE_GPU_DVFS_APB + 0x0010 )
#define REG_GPU_DVFS_APB_GPU_SW_DVFS_CTRL                  ( CTL_BASE_GPU_DVFS_APB + 0x0020 )
#define REG_GPU_DVFS_APB_GPU_FREQ_UPDATE_BYPASS            ( CTL_BASE_GPU_DVFS_APB + 0x0024 )
#define REG_GPU_DVFS_APB_CGM_GPU_DVFS_CLK_GATE_CTRL        ( CTL_BASE_GPU_DVFS_APB + 0x0028 )
#define REG_GPU_DVFS_APB_GPU_DVFS_VOLTAGE_DBG              ( CTL_BASE_GPU_DVFS_APB + 0x002C )
#define REG_GPU_DVFS_APB_GPU_DVFS_CGM_CFG_DBG              ( CTL_BASE_GPU_DVFS_APB + 0x0034 )
#define REG_GPU_DVFS_APB_GPU_DVFS_STATE_DBG                ( CTL_BASE_GPU_DVFS_APB + 0x0038 )
#define REG_GPU_DVFS_APB_GPU_CORE_INDEX0_MAP               ( CTL_BASE_GPU_DVFS_APB + 0x0048 )
#define REG_GPU_DVFS_APB_GPU_CORE_INDEX1_MAP               ( CTL_BASE_GPU_DVFS_APB + 0x004C )
#define REG_GPU_DVFS_APB_GPU_CORE_INDEX2_MAP               ( CTL_BASE_GPU_DVFS_APB + 0x0050 )
#define REG_GPU_DVFS_APB_GPU_CORE_INDEX3_MAP               ( CTL_BASE_GPU_DVFS_APB + 0x0054 )
#define REG_GPU_DVFS_APB_GPU_CORE_INDEX4_MAP               ( CTL_BASE_GPU_DVFS_APB + 0x0058 )
#define REG_GPU_DVFS_APB_GPU_CORE_INDEX5_MAP               ( CTL_BASE_GPU_DVFS_APB + 0x005C )
#define REG_GPU_DVFS_APB_GPU_CORE_INDEX6_MAP               ( CTL_BASE_GPU_DVFS_APB + 0x0060 )
#define REG_GPU_DVFS_APB_GPU_CORE_INDEX7_MAP               ( CTL_BASE_GPU_DVFS_APB + 0x0064 )
#define REG_GPU_DVFS_APB_GPU_DVFS_INDEX_CFG                ( CTL_BASE_GPU_DVFS_APB + 0x008C )
#define REG_GPU_DVFS_APB_GPU_CORE_DVFS_INDEX_IDLE_CFG      ( CTL_BASE_GPU_DVFS_APB + 0x0090 )
#define REG_GPU_DVFS_APB_GPU_FREQ_UPD_STATE                ( CTL_BASE_GPU_DVFS_APB + 0x0098 )
#define REG_GPU_DVFS_APB_GPU_GFREE_WAIT_DELAY_CFG          ( CTL_BASE_GPU_DVFS_APB + 0x009C )
#define REG_GPU_DVFS_APB_GPU_FREQ_UPD_TYPE_CFG             ( CTL_BASE_GPU_DVFS_APB + 0x00A4 )
#define REG_GPU_DVFS_APB_GPU_DVFS_RESERVED_REG_CFG0        ( CTL_BASE_GPU_DVFS_APB + 0x00A8 )
#define REG_GPU_DVFS_APB_GPU_DVFS_RESERVED_REG_CFG1        ( CTL_BASE_GPU_DVFS_APB + 0x00AC )
#define REG_GPU_DVFS_APB_GPU_DVFS_RESERVED_REG_CFG2        ( CTL_BASE_GPU_DVFS_APB + 0x00B0 )
#define REG_GPU_DVFS_APB_GPU_DVFS_RESERVED_REG_CFG3        ( CTL_BASE_GPU_DVFS_APB + 0x00B4 )
#define REG_GPU_DVFS_APB_GPU_DVFS_WAIT_WINDOW_CFG2         ( CTL_BASE_GPU_DVFS_APB + 0x00C0 )
#define REG_GPU_DVFS_APB_GPU_DFS_IDLE_DISABLE_CFG          ( CTL_BASE_GPU_DVFS_APB + 0x00D0 )

/* REG_GPU_DVFS_APB_GPU_DVFS_HOLD_CTRL */

#define BIT_GPU_DVFS_APB_GPU_DVFS_HOLD                    BIT(0)

/* REG_GPU_DVFS_APB_GPU_MIN_VOLTAGE_CFG */

#define BIT_GPU_DVFS_APB_GPU_TOP_MIN_VOLTAGE(x)           (((x) & 0x7))

/* REG_GPU_DVFS_APB_GPU_SW_DVFS_CTRL */

#define BIT_GPU_DVFS_APB_GPU_DVFS_ACK                     BIT(8)
#define BIT_GPU_DVFS_APB_GPU_DVFS_VOLTAGE_SW(x)           (((x) & 0x7) << 4)
#define BIT_GPU_DVFS_APB_GPU_CURRENT_VOLTAGE_SW(x)        (((x) & 0x7) << 1)
#define BIT_GPU_DVFS_APB_GPU_DVFS_REQ_SW                  BIT(0)

/* REG_GPU_DVFS_APB_GPU_FREQ_UPDATE_BYPASS */

#define BIT_GPU_DVFS_APB_REG_GPU_CORE_FREQ_UPD_EN_BYP     BIT(2)

/* REG_GPU_DVFS_APB_CGM_GPU_DVFS_CLK_GATE_CTRL */

#define BIT_GPU_DVFS_APB_CGM_GPU_DVFS_FORCE_EN            BIT(1)
#define BIT_GPU_DVFS_APB_CGM_GPU_DVFS_AUTO_GATE_SEL       BIT(0)

/* REG_GPU_DVFS_APB_GPU_DVFS_VOLTAGE_DBG */

#define BIT_GPU_DVFS_APB_GPU_CURRENT_VOLTAGE(x)           (((x) & 0x7) << 12)
#define BIT_GPU_DVFS_APB_GPU_INTERNAL_VOTE_VOLTAGE(x)     (((x) & 0x7))

/* REG_GPU_DVFS_APB_GPU_DVFS_CGM_CFG_DBG */

#define BIT_GPU_DVFS_APB_CGM_GPU_CORE_SEL_DVFS(x)         (((x) & 0x7) << 12)
#define BIT_GPU_DVFS_APB_CGM_GPU_CORE_DIV_DVFS(x)         (((x) & 0x7) << 9)
#define BIT_GPU_DVFS_APB_CGM_GPU_MEM_DIV_DVFS(x)          (((x) & 0x7) << 3)
#define BIT_GPU_DVFS_APB_CGM_GPU_SYS_DIV_DVFS(x)          (((x) & 0x7))

/* REG_GPU_DVFS_APB_GPU_DVFS_STATE_DBG */

#define BIT_GPU_DVFS_APB_GPU_TOP_DVFS_BUSY                BIT(19)
#define BIT_GPU_DVFS_APB_GPU_DVFS_WINDOW_CNT(x)           (((x) & 0xFFFF) << 3)
#define BIT_GPU_DVFS_APB_GPU_DVFS_STATE(x)                (((x) & 0x7))

/* REG_GPU_DVFS_APB_GPU_CORE_INDEX0_MAP */

#define BIT_GPU_DVFS_APB_CGM_GPU_SYS_DIV_INDEX0(x)        (((x) & 0x7) << 20)
#define BIT_GPU_DVFS_APB_CGM_GPU_MEM_DIV_INDEX0(x)        (((x) & 0x7) << 17)
#define BIT_GPU_DVFS_APB_GPU_CORE_VOL_INDEX0(x)           (((x) & 0x7) << 14)
#define BIT_GPU_DVFS_APB_CGM_GPU_CORE_DIV_INDEX0(x)       (((x) & 0x7) << 3)
#define BIT_GPU_DVFS_APB_CGM_GPU_CORE_SEL_INDEX0(x)       (((x) & 0x7))

/* REG_GPU_DVFS_APB_GPU_CORE_INDEX1_MAP */

#define BIT_GPU_DVFS_APB_CGM_GPU_SYS_DIV_INDEX1(x)        (((x) & 0x7) << 20)
#define BIT_GPU_DVFS_APB_CGM_GPU_MEM_DIV_INDEX1(x)        (((x) & 0x7) << 17)
#define BIT_GPU_DVFS_APB_GPU_CORE_VOL_INDEX1(x)           (((x) & 0x7) << 14)
#define BIT_GPU_DVFS_APB_CGM_GPU_CORE_DIV_INDEX1(x)       (((x) & 0x7) << 3)
#define BIT_GPU_DVFS_APB_CGM_GPU_CORE_SEL_INDEX1(x)       (((x) & 0x7))

/* REG_GPU_DVFS_APB_GPU_CORE_INDEX2_MAP */

#define BIT_GPU_DVFS_APB_CGM_GPU_SYS_DIV_INDEX2(x)        (((x) & 0x7) << 20)
#define BIT_GPU_DVFS_APB_CGM_GPU_MEM_DIV_INDEX2(x)        (((x) & 0x7) << 17)
#define BIT_GPU_DVFS_APB_GPU_CORE_VOL_INDEX2(x)           (((x) & 0x7) << 14)
#define BIT_GPU_DVFS_APB_CGM_GPU_CORE_DIV_INDEX2(x)       (((x) & 0x7) << 3)
#define BIT_GPU_DVFS_APB_CGM_GPU_CORE_SEL_INDEX2(x)       (((x) & 0x7))

/* REG_GPU_DVFS_APB_GPU_CORE_INDEX3_MAP */

#define BIT_GPU_DVFS_APB_CGM_GPU_SYS_DIV_INDEX3(x)        (((x) & 0x7) << 20)
#define BIT_GPU_DVFS_APB_CGM_GPU_MEM_DIV_INDEX3(x)        (((x) & 0x7) << 17)
#define BIT_GPU_DVFS_APB_GPU_CORE_VOL_INDEX3(x)           (((x) & 0x7) << 14)
#define BIT_GPU_DVFS_APB_CGM_GPU_CORE_DIV_INDEX3(x)       (((x) & 0x7) << 3)
#define BIT_GPU_DVFS_APB_CGM_GPU_CORE_SEL_INDEX3(x)       (((x) & 0x7))

/* REG_GPU_DVFS_APB_GPU_CORE_INDEX4_MAP */

#define BIT_GPU_DVFS_APB_CGM_GPU_SYS_DIV_INDEX4(x)        (((x) & 0x7) << 20)
#define BIT_GPU_DVFS_APB_CGM_GPU_MEM_DIV_INDEX4(x)        (((x) & 0x7) << 17)
#define BIT_GPU_DVFS_APB_GPU_CORE_VOL_INDEX4(x)           (((x) & 0x7) << 14)
#define BIT_GPU_DVFS_APB_CGM_GPU_CORE_DIV_INDEX4(x)       (((x) & 0x7) << 3)
#define BIT_GPU_DVFS_APB_CGM_GPU_CORE_SEL_INDEX4(x)       (((x) & 0x7))

/* REG_GPU_DVFS_APB_GPU_CORE_INDEX5_MAP */

#define BIT_GPU_DVFS_APB_CGM_GPU_SYS_DIV_INDEX5(x)        (((x) & 0x7) << 20)
#define BIT_GPU_DVFS_APB_CGM_GPU_MEM_DIV_INDEX5(x)        (((x) & 0x7) << 17)
#define BIT_GPU_DVFS_APB_GPU_CORE_VOL_INDEX5(x)           (((x) & 0x7) << 14)
#define BIT_GPU_DVFS_APB_CGM_GPU_CORE_DIV_INDEX5(x)       (((x) & 0x7) << 3)
#define BIT_GPU_DVFS_APB_CGM_GPU_CORE_SEL_INDEX5(x)       (((x) & 0x7))

/* REG_GPU_DVFS_APB_GPU_CORE_INDEX6_MAP */

#define BIT_GPU_DVFS_APB_CGM_GPU_SYS_DIV_INDEX6(x)        (((x) & 0x7) << 20)
#define BIT_GPU_DVFS_APB_CGM_GPU_MEM_DIV_INDEX6(x)        (((x) & 0x7) << 17)
#define BIT_GPU_DVFS_APB_GPU_CORE_VOL_INDEX6(x)           (((x) & 0x7) << 14)
#define BIT_GPU_DVFS_APB_CGM_GPU_CORE_DIV_INDEX6(x)       (((x) & 0x7) << 3)
#define BIT_GPU_DVFS_APB_CGM_GPU_CORE_SEL_INDEX6(x)       (((x) & 0x7))

/* REG_GPU_DVFS_APB_GPU_CORE_INDEX7_MAP */

#define BIT_GPU_DVFS_APB_CGM_GPU_SYS_DIV_INDEX7(x)        (((x) & 0x7) << 20)
#define BIT_GPU_DVFS_APB_CGM_GPU_MEM_DIV_INDEX7(x)        (((x) & 0x7) << 17)
#define BIT_GPU_DVFS_APB_GPU_CORE_VOL_INDEX7(x)           (((x) & 0x7) << 14)
#define BIT_GPU_DVFS_APB_CGM_GPU_CORE_DIV_INDEX7(x)       (((x) & 0x7) << 3)
#define BIT_GPU_DVFS_APB_CGM_GPU_CORE_SEL_INDEX7(x)       (((x) & 0x7))

/* REG_GPU_DVFS_APB_GPU_DVFS_INDEX_CFG */

#define BIT_GPU_DVFS_APB_GPU_DVFS_INDEX(x)                (((x) & 0x7))

/* REG_GPU_DVFS_APB_GPU_CORE_DVFS_INDEX_IDLE_CFG */

#define BIT_GPU_DVFS_APB_GPU_CORE_DVFS_INDEX_IDLE(x)      (((x) & 0x7))

/* REG_GPU_DVFS_APB_GPU_FREQ_UPD_STATE */

#define BIT_GPU_DVFS_APB_GPU_CORE_DVFS_FREQ_UPD_STATE(x)  (((x) & 0xF))

/* REG_GPU_DVFS_APB_GPU_GFREE_WAIT_DELAY_CFG */

#define BIT_GPU_DVFS_APB_GPU_CORE_GFREE_WAIT_DELAY(x)     (((x) & 0x3FF))

/* REG_GPU_DVFS_APB_GPU_FREQ_UPD_TYPE_CFG */

#define BIT_GPU_DVFS_APB_GPU_CORE_FREQ_UPD_DELAY_EN       BIT(1)
#define BIT_GPU_DVFS_APB_GPU_CORE_FREQ_UPD_HDSK_EN        BIT(0)

/* REG_GPU_DVFS_APB_GPU_DVFS_RESERVED_REG_CFG0 */

#define BIT_GPU_DVFS_APB_DVFS_RES_REG0(x)                 (((x) & 0xFFFFFFFF))

/* REG_GPU_DVFS_APB_GPU_DVFS_RESERVED_REG_CFG1 */

#define BIT_GPU_DVFS_APB_DVFS_RES_REG1(x)                 (((x) & 0xFFFFFFFF))

/* REG_GPU_DVFS_APB_GPU_DVFS_RESERVED_REG_CFG2 */

#define BIT_GPU_DVFS_APB_DVFS_RES_REG2(x)                 (((x) & 0xFFFFFFFF))

/* REG_GPU_DVFS_APB_GPU_DVFS_RESERVED_REG_CFG3 */

#define BIT_GPU_DVFS_APB_DVFS_RES_REG3(x)                 (((x) & 0xFFFFFFFF))

/* REG_GPU_DVFS_APB_GPU_DVFS_WAIT_WINDOW_CFG2 */

#define BIT_GPU_DVFS_APB_GPU_DVFS_UP_WINDOW(x)            (((x) & 0xFFFF) << 16)
#define BIT_GPU_DVFS_APB_GPU_DVFS_DOWN_WINDOW(x)          (((x) & 0xFFFF))

/* REG_GPU_DVFS_APB_GPU_DFS_IDLE_DISABLE_CFG */

#define BIT_GPU_DVFS_APB_GPU_CORE_DFS_IDLE_DISABLE        BIT(0)

#endif