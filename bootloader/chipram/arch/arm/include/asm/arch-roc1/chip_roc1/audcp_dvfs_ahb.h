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


#ifndef AUDCP_DVFS_AHB_H
#define AUDCP_DVFS_AHB_H

#define CTL_BASE_AUDCP_DVFS_AHB 0x015A0000


#define REG_AUDCP_DVFS_AHB_AUDCP_DVFS_HOLD_CTRL              ( CTL_BASE_AUDCP_DVFS_AHB + 0x0000 )
#define REG_AUDCP_DVFS_AHB_AUDCP_DVFS_WAIT_WINDOW_CFG        ( CTL_BASE_AUDCP_DVFS_AHB + 0x0004 )
#define REG_AUDCP_DVFS_AHB_AUDCP_SW_DVFS_CTRL                ( CTL_BASE_AUDCP_DVFS_AHB + 0x001C )
#define REG_AUDCP_DVFS_AHB_AUDCP_FREQ_UPDATE_BYPASS          ( CTL_BASE_AUDCP_DVFS_AHB + 0x0020 )
#define REG_AUDCP_DVFS_AHB_CGM_AUDCP_DVFS_CLK_GATE_CTRL      ( CTL_BASE_AUDCP_DVFS_AHB + 0x0024 )
#define REG_AUDCP_DVFS_AHB_AUDCP_DVFS_VOLTAGE_DBG            ( CTL_BASE_AUDCP_DVFS_AHB + 0x0028 )
#define REG_AUDCP_DVFS_AHB_AUDCP_DVFS_CGM_CFG_DBG            ( CTL_BASE_AUDCP_DVFS_AHB + 0x0030 )
#define REG_AUDCP_DVFS_AHB_AUDCP_DVFS_STATE_DBG              ( CTL_BASE_AUDCP_DVFS_AHB + 0x0034 )
#define REG_AUDCP_DVFS_AHB_AUDDSP_INDEX0_MAP                 ( CTL_BASE_AUDCP_DVFS_AHB + 0x0038 )
#define REG_AUDCP_DVFS_AHB_AUDDSP_INDEX1_MAP                 ( CTL_BASE_AUDCP_DVFS_AHB + 0x003C )
#define REG_AUDCP_DVFS_AHB_AUDDSP_INDEX2_MAP                 ( CTL_BASE_AUDCP_DVFS_AHB + 0x0040 )
#define REG_AUDCP_DVFS_AHB_AUDDSP_INDEX3_MAP                 ( CTL_BASE_AUDCP_DVFS_AHB + 0x0044 )
#define REG_AUDCP_DVFS_AHB_AUDDSP_INDEX4_MAP                 ( CTL_BASE_AUDCP_DVFS_AHB + 0x0048 )
#define REG_AUDCP_DVFS_AHB_AUDDSP_INDEX5_MAP                 ( CTL_BASE_AUDCP_DVFS_AHB + 0x004C )
#define REG_AUDCP_DVFS_AHB_AUDDSP_INDEX6_MAP                 ( CTL_BASE_AUDCP_DVFS_AHB + 0x0050 )
#define REG_AUDCP_DVFS_AHB_AUDDSP_INDEX7_MAP                 ( CTL_BASE_AUDCP_DVFS_AHB + 0x0054 )
#define REG_AUDCP_DVFS_AHB_DSP_DVFS_INDEX_CFG                ( CTL_BASE_AUDCP_DVFS_AHB + 0x0058 )
#define REG_AUDCP_DVFS_AHB_DSP_DVFS_INDEX_IDLE_CFG           ( CTL_BASE_AUDCP_DVFS_AHB + 0x005C )
#define REG_AUDCP_DVFS_AHB_AUDCP_FREQ_UPD_STATE              ( CTL_BASE_AUDCP_DVFS_AHB + 0x0060 )
#define REG_AUDCP_DVFS_AHB_AUDCP_GFREE_WAIT_DELAY_CFG        ( CTL_BASE_AUDCP_DVFS_AHB + 0x0064 )
#define REG_AUDCP_DVFS_AHB_AUDCP_FREQ_UPD_TYPE_CFG           ( CTL_BASE_AUDCP_DVFS_AHB + 0x0068 )
#define REG_AUDCP_DVFS_AHB_AUDCP_DFS_IDLE_DISABLE_CFG        ( CTL_BASE_AUDCP_DVFS_AHB + 0x0070 )
#define REG_AUDCP_DVFS_AHB_AUDCP_DVFS_RESERVED_REG_CFG0      ( CTL_BASE_AUDCP_DVFS_AHB + 0x0080 )
#define REG_AUDCP_DVFS_AHB_AUDCP_DVFS_RESERVED_REG_CFG1      ( CTL_BASE_AUDCP_DVFS_AHB + 0x0084 )
#define REG_AUDCP_DVFS_AHB_AUDCP_DVFS_RESERVED_REG_CFG2      ( CTL_BASE_AUDCP_DVFS_AHB + 0x0088 )
#define REG_AUDCP_DVFS_AHB_AUDCP_DVFS_RESERVED_REG_CFG3      ( CTL_BASE_AUDCP_DVFS_AHB + 0x008C )

/* REG_AUDCP_DVFS_AHB_AUDCP_DVFS_HOLD_CTRL */

#define BIT_AUDCP_DVFS_AHB_AUDCP_DVFS_HOLD                      BIT(0)

/* REG_AUDCP_DVFS_AHB_AUDCP_DVFS_WAIT_WINDOW_CFG */

#define BIT_AUDCP_DVFS_AHB_AUDCP_DVFS_UP_WINDOW(x)              (((x) & 0xFFFF) << 16)
#define BIT_AUDCP_DVFS_AHB_AUDCP_DVFS_DOWN_WINDOW(x)            (((x) & 0xFFFF))

/* REG_AUDCP_DVFS_AHB_AUDCP_SW_DVFS_CTRL */

#define BIT_AUDCP_DVFS_AHB_AUDCP_DVFS_ACK                       BIT(8)
#define BIT_AUDCP_DVFS_AHB_AUDCP_DVFS_VOLTAGE_SW(x)             (((x) & 0x7) << 4)
#define BIT_AUDCP_DVFS_AHB_AUDCP_CURRENT_VOLTAGE_SW(x)          (((x) & 0x7) << 1)
#define BIT_AUDCP_DVFS_AHB_AUDCP_DVFS_REQ_SW                    BIT(0)

/* REG_AUDCP_DVFS_AHB_AUDCP_FREQ_UPDATE_BYPASS */

#define BIT_AUDCP_DVFS_AHB_REG_DSP_FREQ_UPD_EN_BYP              BIT(0)

/* REG_AUDCP_DVFS_AHB_CGM_AUDCP_DVFS_CLK_GATE_CTRL */

#define BIT_AUDCP_DVFS_AHB_CGM_AUDCP_DVFS_FORCE_EN              BIT(1)
#define BIT_AUDCP_DVFS_AHB_CGM_AUDCP_DVFS_AUTO_GATE_SEL         BIT(0)

/* REG_AUDCP_DVFS_AHB_AUDCP_DVFS_VOLTAGE_DBG */

#define BIT_AUDCP_DVFS_AHB_AUDCP_CURRENT_VOLTAGE(x)             (((x) & 0x7) << 15)
#define BIT_AUDCP_DVFS_AHB_AUDCP_INTERNAL_VOTE_VOLTAGE(x)       (((x) & 0x7))

/* REG_AUDCP_DVFS_AHB_AUDCP_DVFS_CGM_CFG_DBG */

#define BIT_AUDCP_DVFS_AHB_CGM_DSP_CORE_SEL_DVFS(x)             (((x) & 0x7) << 10)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_CORE_DIV_DVFS(x)             (((x) & 0x3) << 8)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_AXI_DIV_DVFS(x)              (((x) & 0x3) << 6)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_AHB_DIV_DVFS(x)              (((x) & 0x7) << 3)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_APB_DIV_DVFS(x)              (((x) & 0x7))

/* REG_AUDCP_DVFS_AHB_AUDCP_DVFS_STATE_DBG */

#define BIT_AUDCP_DVFS_AHB_AUDCP_SYS_DVFS_BUSY                  BIT(19)
#define BIT_AUDCP_DVFS_AHB_AUDCP_DVFS_WINDOW_CNT(x)             (((x) & 0xFFFF) << 3)
#define BIT_AUDCP_DVFS_AHB_AUDCP_DVFS_STATE(x)                  (((x) & 0x7))

/* REG_AUDCP_DVFS_AHB_AUDDSP_INDEX0_MAP */

#define BIT_AUDCP_DVFS_AHB_DSP_VOL_INDEX0(x)                    (((x) & 0x7) << 13)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_APB_DIV_INDEX0(x)            (((x) & 0x7) << 10)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_AHB_DIV_INDEX0(x)            (((x) & 0x7) << 7)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_AXI_DIV_INDEX0(x)            (((x) & 0x3) << 5)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_CORE_DIV_INDEX0(x)           (((x) & 0x3) << 3)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_CORE_SEL_INDEX0(x)           (((x) & 0x7))

/* REG_AUDCP_DVFS_AHB_AUDDSP_INDEX1_MAP */

#define BIT_AUDCP_DVFS_AHB_DSP_VOL_INDEX1(x)                    (((x) & 0x7) << 13)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_APB_DIV_INDEX1(x)            (((x) & 0x7) << 10)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_AHB_DIV_INDEX1(x)            (((x) & 0x7) << 7)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_AXI_DIV_INDEX1(x)            (((x) & 0x3) << 5)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_CORE_DIV_INDEX1(x)           (((x) & 0x3) << 3)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_CORE_SEL_INDEX1(x)           (((x) & 0x7))

/* REG_AUDCP_DVFS_AHB_AUDDSP_INDEX2_MAP */

#define BIT_AUDCP_DVFS_AHB_DSP_VOL_INDEX2(x)                    (((x) & 0x7) << 13)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_APB_DIV_INDEX2(x)            (((x) & 0x7) << 10)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_AHB_DIV_INDEX2(x)            (((x) & 0x7) << 7)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_AXI_DIV_INDEX2(x)            (((x) & 0x3) << 5)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_CORE_DIV_INDEX2(x)           (((x) & 0x3) << 3)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_CORE_SEL_INDEX2(x)           (((x) & 0x7))

/* REG_AUDCP_DVFS_AHB_AUDDSP_INDEX3_MAP */

#define BIT_AUDCP_DVFS_AHB_DSP_VOL_INDEX3(x)                    (((x) & 0x7) << 13)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_APB_DIV_INDEX3(x)            (((x) & 0x7) << 10)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_AHB_DIV_INDEX3(x)            (((x) & 0x7) << 7)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_AXI_DIV_INDEX3(x)            (((x) & 0x3) << 5)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_CORE_DIV_INDEX3(x)           (((x) & 0x3) << 3)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_CORE_SEL_INDEX3(x)           (((x) & 0x7))

/* REG_AUDCP_DVFS_AHB_AUDDSP_INDEX4_MAP */

#define BIT_AUDCP_DVFS_AHB_DSP_VOL_INDEX4(x)                    (((x) & 0x7) << 13)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_APB_DIV_INDEX4(x)            (((x) & 0x7) << 10)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_AHB_DIV_INDEX4(x)            (((x) & 0x7) << 7)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_AXI_DIV_INDEX4(x)            (((x) & 0x3) << 5)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_CORE_DIV_INDEX4(x)           (((x) & 0x3) << 3)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_CORE_SEL_INDEX4(x)           (((x) & 0x7))

/* REG_AUDCP_DVFS_AHB_AUDDSP_INDEX5_MAP */

#define BIT_AUDCP_DVFS_AHB_DSP_VOL_INDEX5(x)                    (((x) & 0x7) << 13)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_APB_DIV_INDEX5(x)            (((x) & 0x7) << 10)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_AHB_DIV_INDEX5(x)            (((x) & 0x7) << 7)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_AXI_DIV_INDEX5(x)            (((x) & 0x3) << 5)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_CORE_DIV_INDEX5(x)           (((x) & 0x3) << 3)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_CORE_SEL_INDEX5(x)           (((x) & 0x7))

/* REG_AUDCP_DVFS_AHB_AUDDSP_INDEX6_MAP */

#define BIT_AUDCP_DVFS_AHB_DSP_VOL_INDEX6(x)                    (((x) & 0x7) << 13)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_APB_DIV_INDEX6(x)            (((x) & 0x7) << 10)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_AHB_DIV_INDEX6(x)            (((x) & 0x7) << 7)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_AXI_DIV_INDEX6(x)            (((x) & 0x3) << 5)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_CORE_DIV_INDEX6(x)           (((x) & 0x3) << 3)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_CORE_SEL_INDEX6(x)           (((x) & 0x7))

/* REG_AUDCP_DVFS_AHB_AUDDSP_INDEX7_MAP */

#define BIT_AUDCP_DVFS_AHB_DSP_VOL_INDEX7(x)                    (((x) & 0x7) << 13)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_APB_DIV_INDEX7(x)            (((x) & 0x7) << 10)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_AHB_DIV_INDEX7(x)            (((x) & 0x7) << 7)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_AXI_DIV_INDEX7(x)            (((x) & 0x3) << 5)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_CORE_DIV_INDEX7(x)           (((x) & 0x3) << 3)
#define BIT_AUDCP_DVFS_AHB_CGM_DSP_CORE_SEL_INDEX7(x)           (((x) & 0x7))

/* REG_AUDCP_DVFS_AHB_DSP_DVFS_INDEX_CFG */

#define BIT_AUDCP_DVFS_AHB_DSP_DVFS_INDEX(x)                    (((x) & 0x7))

/* REG_AUDCP_DVFS_AHB_DSP_DVFS_INDEX_IDLE_CFG */

#define BIT_AUDCP_DVFS_AHB_DSP_DVFS_INDEX_IDLE(x)               (((x) & 0x7))

/* REG_AUDCP_DVFS_AHB_AUDCP_FREQ_UPD_STATE */

#define BIT_AUDCP_DVFS_AHB_DSP_DVFS_FREQ_UPD_STATE(x)           (((x) & 0xF))

/* REG_AUDCP_DVFS_AHB_AUDCP_GFREE_WAIT_DELAY_CFG */

#define BIT_AUDCP_DVFS_AHB_DSP_GFREE_WAIT_DELAY(x)              (((x) & 0x3FF))

/* REG_AUDCP_DVFS_AHB_AUDCP_FREQ_UPD_TYPE_CFG */

#define BIT_AUDCP_DVFS_AHB_DSP_FREQ_UPD_DELAY_EN                BIT(1)
#define BIT_AUDCP_DVFS_AHB_DSP_FREQ_UPD_HDSK_EN                 BIT(0)

/* REG_AUDCP_DVFS_AHB_AUDCP_DFS_IDLE_DISABLE_CFG */

#define BIT_AUDCP_DVFS_AHB_AUDCP_DSP_CORE_GRP_DFS_IDLE_DISABLE  BIT(0)

/* REG_AUDCP_DVFS_AHB_AUDCP_DVFS_RESERVED_REG_CFG0 */

#define BIT_AUDCP_DVFS_AHB_DVFS_RES_REG0(x)                     (((x) & 0xFFFFFFFF))

/* REG_AUDCP_DVFS_AHB_AUDCP_DVFS_RESERVED_REG_CFG1 */

#define BIT_AUDCP_DVFS_AHB_DVFS_RES_REG1(x)                     (((x) & 0xFFFFFFFF))

/* REG_AUDCP_DVFS_AHB_AUDCP_DVFS_RESERVED_REG_CFG2 */

#define BIT_AUDCP_DVFS_AHB_DVFS_RES_REG2(x)                     (((x) & 0xFFFFFFFF))

/* REG_AUDCP_DVFS_AHB_AUDCP_DVFS_RESERVED_REG_CFG3 */

#define BIT_AUDCP_DVFS_AHB_DVFS_RES_REG3(x)                     (((x) & 0xFFFFFFFF))


#endif /* AUDCP_DVFS_AHB_H */


