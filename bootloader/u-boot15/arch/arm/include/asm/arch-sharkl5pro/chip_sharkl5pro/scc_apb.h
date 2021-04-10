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

#ifndef SCC_APB_H
#define SCC_APB_H

#define CTL_BASE_SCC_APB 0x324D0000

#define REG_SCC_APB_SCC_TUNE_LMT_CFG   ( CTL_BASE_SCC_APB + 0x0000 )
#define REG_SCC_APB_SCC_TUNE_STATUS    ( CTL_BASE_SCC_APB + 0x0004 )
#define REG_SCC_APB_SCC_CFG            ( CTL_BASE_SCC_APB + 0x0008 )
#define REG_SCC_APB_SCC_TUNE_STEP_CFG  ( CTL_BASE_SCC_APB + 0x000C )
#define REG_SCC_APB_SCC_WAIT_CFG       ( CTL_BASE_SCC_APB + 0x0010 )
#define REG_SCC_APB_SCC_INT_CFG        ( CTL_BASE_SCC_APB + 0x0014 )
#define REG_SCC_APB_SCC_TUNE_MARK      ( CTL_BASE_SCC_APB + 0x0024 )
#define REG_SCC_APB_SCC_FSM_STS        ( CTL_BASE_SCC_APB + 0x0028 )
#define REG_SCC_APB_SCC_ROSC_MODE      ( CTL_BASE_SCC_APB + 0x0100 )
#define REG_SCC_APB_SCC_ROSC_CFG       ( CTL_BASE_SCC_APB + 0x0104 )
#define REG_SCC_APB_SCC_ROSC_CTRL      ( CTL_BASE_SCC_APB + 0x0108 )
#define REG_SCC_APB_SCC_ROSC_RPT       ( CTL_BASE_SCC_APB + 0x010C )
#define REG_SCC_APB_SCC_ROSC_SW_RST    ( CTL_BASE_SCC_APB + 0x0110 )

/* REG_SCC_APB_SCC_TUNE_LMT_CFG */

#define BIT_SCC_APB_VOLT_TUNE_VAL_MAX(x)           (((x) & 0x1FF) << 9)
#define BIT_SCC_APB_VOLT_TUNE_VAL_MIN(x)           (((x) & 0x1FF))

/* REG_SCC_APB_SCC_TUNE_STATUS */

#define BIT_SCC_APB_VOLT_TUNE_VAL(x)               (((x) & 0x1FF) << 9)
#define BIT_SCC_APB_VOLT_OBS_VAL(x)                (((x) & 0x1FF))

/* REG_SCC_APB_SCC_CFG */

#define BIT_SCC_APB_VOLT0_SELECT_OVERRIDE          BIT(31)
#define BIT_SCC_APB_VOLT1_SELECT_OVERRIDE          BIT(30)
#define BIT_SCC_APB_PAUSE_OCCUR_ERR_EN             BIT(8)
#define BIT_SCC_APB_VOLT_TUNE_FORBID_EN            BIT(4)
#define BIT_SCC_APB_VOLT_OBS_FORBID_EN             BIT(0)

/* REG_SCC_APB_SCC_TUNE_STEP_CFG */

#define BIT_SCC_APB_VOLT_TUNE_DOWN_STEP(x)         (((x) & 0x3FF) << 16)
#define BIT_SCC_APB_VOLT_TUNE_UP_STEP(x)           (((x) & 0x3FF))

/* REG_SCC_APB_SCC_WAIT_CFG */

#define BIT_SCC_APB_RND_INTVAL_WAIT_NUM(x)         (((x) & 0xFFFF) << 16)
#define BIT_SCC_APB_VOLT_STB_WAIT_NUM(x)           (((x) & 0xFFFF))

/* REG_SCC_APB_SCC_INT_CFG */

#define BIT_SCC_APB_SCC_TUNE_DONE_INT_MASK_STATUS  BIT(13)
#define BIT_SCC_APB_SCC_TUNE_ERR_INT_MASK_STATUS   BIT(12)
#define BIT_SCC_APB_SCC_TUNE_DONE_INT_RAW_STATUS   BIT(9)
#define BIT_SCC_APB_SCC_TUNE_ERR_INT_RAW_STATUS    BIT(8)
#define BIT_SCC_APB_SCC_TUNE_DONE_INT_CLR          BIT(5)
#define BIT_SCC_APB_SCC_TUNE_ERR_INT_CLR           BIT(4)
#define BIT_SCC_APB_SCC_TUNE_DONE_INT_EN           BIT(1)
#define BIT_SCC_APB_SCC_TUNE_ERR_INT_EN            BIT(0)

/* REG_SCC_APB_SCC_TUNE_MARK */

#define BIT_SCC_APB_SCC_TUNE_DWN_MARK(x)           (((x) & 0xFFFF) << 16)
#define BIT_SCC_APB_SCC_TUNE_UP_MARK(x)            (((x) & 0xFFFF))

/* REG_SCC_APB_SCC_FSM_STS */

#define BIT_SCC_APB_SCC_FSM_STS(x)                 (((x) & 0x1F))

/* REG_SCC_APB_SCC_ROSC_MODE */

#define BIT_SCC_APB_SCC_IDLE_MODE                  BIT(31)
#define BIT_SCC_APB_SCC_TUNE_BYPASS                BIT(30)
#define BIT_SCC_APB_SCC_INIT_HALT_BYPASS           BIT(29)
#define BIT_SCC_APB_SCC_AM_CLK_DIVIDER(x)          (((x) & 0x3) << 27)
#define BIT_SCC_APB_SCC_AM_ENABLE                  BIT(26)
#define BIT_SCC_APB_SCC_AM_OBS_EN                  BIT(25)
#define BIT_SCC_APB_SCC_RPT_READ_CTRL              BIT(12)
#define BIT_SCC_APB_SCC_ALL_ROSC_CHAIN             BIT(2)
#define BIT_SCC_APB_SCC_ALL_ROSC_SEQ               BIT(1)
#define BIT_SCC_APB_SCC_ROSC_REPEAT_MODE           BIT(0)

/* REG_SCC_APB_SCC_ROSC_CFG */

#define BIT_SCC_APB_SCC_ROSC_DURATION(x)           (((x) & 0xFFFFF) << 12)
#define BIT_SCC_APB_SCC_ROSC_SEL_Z(x)              (((x) & 0xF) << 8)
#define BIT_SCC_APB_SCC_ROSC_SEL_Y(x)              (((x) & 0xF) << 4)
#define BIT_SCC_APB_SCC_ROSC_SEL_X(x)              (((x) & 0xF))

/* REG_SCC_APB_SCC_ROSC_CTRL */

#define BIT_SCC_APB_SCC_RPT_READ_NXT               BIT(31)
#define BIT_SCC_APB_SCC_ROSC_GR_ENABLE             BIT(1)
#define BIT_SCC_APB_SCC_ROSC_RUN                   BIT(0)

/* REG_SCC_APB_SCC_ROSC_RPT */

#define BIT_SCC_APB_SCC_INIT_PAT_FAIL              BIT(31)
#define BIT_SCC_APB_SCC_ROSC_RPT_VALID             BIT(30)
#define BIT_SCC_APB_SCC_ROSC_SETTING(x)            (((x) & 0x1F) << 20)
#define BIT_SCC_APB_SCC_ROSC_CNT(x)                (((x) & 0xFFFFF))

/* REG_SCC_APB_SCC_ROSC_SW_RST */

#define BIT_SCC_APB_SCC_ROSC_SW_RST(x)             (((x) & 0xF))

#endif