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


#ifndef SCC_APB_H
#define SCC_APB_H

#define CTL_BASE_SCC_APB 0x403B0000


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
#define REG_SCC_APB_HWM_CTRL_0         ( CTL_BASE_SCC_APB + 0x0200 )
#define REG_SCC_APB_HWM_CTRL_1         ( CTL_BASE_SCC_APB + 0x0204 )
#define REG_SCC_APB_HWM_CTRL_2         ( CTL_BASE_SCC_APB + 0x0208 )
#define REG_SCC_APB_HWM_CTRL_3         ( CTL_BASE_SCC_APB + 0x020C )
#define REG_SCC_APB_HWM_CTRL_4         ( CTL_BASE_SCC_APB + 0x0210 )
#define REG_SCC_APB_HWM_CTRL_5         ( CTL_BASE_SCC_APB + 0x0214 )
#define REG_SCC_APB_HWM_CTRL_6         ( CTL_BASE_SCC_APB + 0x0218 )
#define REG_SCC_APB_HWM_CTRL_7         ( CTL_BASE_SCC_APB + 0x021C )
#define REG_SCC_APB_HWM_CTRL_8         ( CTL_BASE_SCC_APB + 0x0220 )
#define REG_SCC_APB_HWM_CTRL_9         ( CTL_BASE_SCC_APB + 0x0224 )
#define REG_SCC_APB_HWM_CTRL_10        ( CTL_BASE_SCC_APB + 0x0228 )
#define REG_SCC_APB_HWM_RPT_SEL        ( CTL_BASE_SCC_APB + 0x0300 )
#define REG_SCC_APB_HWM_RPT            ( CTL_BASE_SCC_APB + 0x0304 )
#define REG_SCC_APB_HWM3S_RPT0         ( CTL_BASE_SCC_APB + 0x0400 )
#define REG_SCC_APB_HWM3S_RPT1         ( CTL_BASE_SCC_APB + 0x0404 )
#define REG_SCC_APB_HWM3H_RPT0         ( CTL_BASE_SCC_APB + 0x0408 )
#define REG_SCC_APB_HWM3H_RPT1         ( CTL_BASE_SCC_APB + 0x040C )
#define REG_SCC_APB_HWM4S_RPT0         ( CTL_BASE_SCC_APB + 0x0500 )
#define REG_SCC_APB_HWM4S_RPT1         ( CTL_BASE_SCC_APB + 0x0504 )
#define REG_SCC_APB_HWM4S_RPT2         ( CTL_BASE_SCC_APB + 0x0508 )
#define REG_SCC_APB_HWM4S_RPT3         ( CTL_BASE_SCC_APB + 0x050C )
#define REG_SCC_APB_HWM4H_RPT0         ( CTL_BASE_SCC_APB + 0x0600 )
#define REG_SCC_APB_HWM4H_RPT1         ( CTL_BASE_SCC_APB + 0x0604 )
#define REG_SCC_APB_HWM4H_RPT2         ( CTL_BASE_SCC_APB + 0x0608 )
#define REG_SCC_APB_HWM4H_RPT3         ( CTL_BASE_SCC_APB + 0x060C )

/* REG_SCC_APB_SCC_TUNE_LMT_CFG */

#define BIT_SCC_APB_SCC_TUNE_LMT_CFG_VOLT_TUNE_VAL_MAX(x)      (((x) & 0xFF) << 8)
#define BIT_SCC_APB_SCC_TUNE_LMT_CFG_VOLT_TUNE_VAL_MIN(x)      (((x) & 0xFF))

/* REG_SCC_APB_SCC_TUNE_STATUS */

#define BIT_SCC_APB_SCC_TUNE_STATUS_VOLT_TUNE_VAL(x)           (((x) & 0xFF) << 8)
#define BIT_SCC_APB_SCC_TUNE_STATUS_VOLT_OBS_VAL(x)            (((x) & 0xFF))

/* REG_SCC_APB_SCC_CFG */

#define BIT_SCC_APB_SCC_CFG_VOLT0_SELECT_OVERRIDE              BIT(31)
#define BIT_SCC_APB_SCC_CFG_VOLT1_SELECT_OVERRIDE              BIT(30)
#define BIT_SCC_APB_SCC_CFG_PAUSE_OCCUR_ERR_EN                 BIT(8)
#define BIT_SCC_APB_SCC_CFG_VOLT_TUNE_FORBID_EN                BIT(4)
#define BIT_SCC_APB_SCC_CFG_VOLT_OBS_FORBID_EN                 BIT(0)

/* REG_SCC_APB_SCC_TUNE_STEP_CFG */

#define BIT_SCC_APB_SCC_TUNE_STEP_CFG_VOLT_TUNE_DOWN_STEP(x)   (((x) & 0x1FF) << 16)
#define BIT_SCC_APB_SCC_TUNE_STEP_CFG_VOLT_TUNE_UP_STEP(x)     (((x) & 0x1FF))

/* REG_SCC_APB_SCC_WAIT_CFG */

#define BIT_SCC_APB_SCC_WAIT_CFG_RND_INTVAL_WAIT_NUM(x)        (((x) & 0xFFFF) << 16)
#define BIT_SCC_APB_SCC_WAIT_CFG_VOLT_STB_WAIT_NUM(x)          (((x) & 0xFFFF))

/* REG_SCC_APB_SCC_INT_CFG */

#define BIT_SCC_APB_SCC_INT_CFG_SCC_TUNE_DONE_INT_MASK_STATUS  BIT(13)
#define BIT_SCC_APB_SCC_INT_CFG_SCC_TUNE_ERR_INT_MASK_STATUS   BIT(12)
#define BIT_SCC_APB_SCC_INT_CFG_SCC_TUNE_DONE_INT_RAW_STATUS   BIT(9)
#define BIT_SCC_APB_SCC_INT_CFG_SCC_TUNE_ERR_INT_RAW_STATUS    BIT(8)
#define BIT_SCC_APB_SCC_INT_CFG_SCC_TUNE_DONE_INT_CLR          BIT(5)
#define BIT_SCC_APB_SCC_INT_CFG_SCC_TUNE_ERR_INT_CLR           BIT(4)
#define BIT_SCC_APB_SCC_INT_CFG_SCC_TUNE_DONE_INT_EN           BIT(1)
#define BIT_SCC_APB_SCC_INT_CFG_SCC_TUNE_ERR_INT_EN            BIT(0)

/* REG_SCC_APB_SCC_TUNE_MARK */

#define BIT_SCC_APB_SCC_TUNE_MARK_SCC_TUNE_DWN_MARK(x)         (((x) & 0xFFFF) << 16)
#define BIT_SCC_APB_SCC_TUNE_MARK_SCC_TUNE_UP_MARK(x)          (((x) & 0xFFFF))

/* REG_SCC_APB_SCC_FSM_STS */

#define BIT_SCC_APB_SCC_FSM_STS_SCC_FSM_STS(x)                 (((x) & 0x1F))

/* REG_SCC_APB_SCC_ROSC_MODE */

#define BIT_SCC_APB_SCC_ROSC_MODE_SCC_IDLE_MODE                BIT(31)
#define BIT_SCC_APB_SCC_ROSC_MODE_SCC_TUNE_BYPASS              BIT(30)
#define BIT_SCC_APB_SCC_ROSC_MODE_SCC_INIT_HALT_BYPASS         BIT(29)
#define BIT_SCC_APB_SCC_ROSC_MODE_SCC_AM_CLK_DIVIDER(x)        (((x) & 0x3) << 27)
#define BIT_SCC_APB_SCC_ROSC_MODE_SCC_AM_ENABLE                BIT(26)
#define BIT_SCC_APB_SCC_ROSC_MODE_SCC_AM_OBS_EN                BIT(25)
#define BIT_SCC_APB_SCC_ROSC_MODE_SCC_RPT_READ_CTRL            BIT(12)
#define BIT_SCC_APB_SCC_ROSC_MODE_SCC_ROSC_SW_RST(x)           (((x) & 0xFF) << 4)
#define BIT_SCC_APB_SCC_ROSC_MODE_SCC_ALL_ROSC_CHAIN           BIT(2)
#define BIT_SCC_APB_SCC_ROSC_MODE_SCC_ALL_ROSC_SEQ             BIT(1)
#define BIT_SCC_APB_SCC_ROSC_MODE_SCC_ROSC_REPEAT_MODE         BIT(0)

/* REG_SCC_APB_SCC_ROSC_CFG */

#define BIT_SCC_APB_SCC_ROSC_CFG_SCC_ROSC_DURATION(x)          (((x) & 0xFFFFF) << 12)
#define BIT_SCC_APB_SCC_ROSC_CFG_SCC_ROSC_SEL_Z(x)             (((x) & 0xF) << 8)
#define BIT_SCC_APB_SCC_ROSC_CFG_SCC_ROSC_SEL_Y(x)             (((x) & 0xF) << 4)
#define BIT_SCC_APB_SCC_ROSC_CFG_SCC_ROSC_SEL_X(x)             (((x) & 0xF))

/* REG_SCC_APB_SCC_ROSC_CTRL */

#define BIT_SCC_APB_SCC_ROSC_CTRL_SCC_RPT_READ_NXT             BIT(31)
#define BIT_SCC_APB_SCC_ROSC_CTRL_SCC_ROSC_GR_ENABLE           BIT(1)
#define BIT_SCC_APB_SCC_ROSC_CTRL_SCC_ROSC_RUN                 BIT(0)

/* REG_SCC_APB_SCC_ROSC_RPT */

#define BIT_SCC_APB_SCC_ROSC_RPT_SCC_INIT_PAT_FAIL             BIT(31)
#define BIT_SCC_APB_SCC_ROSC_RPT_SCC_ROSC_RPT_VALID            BIT(30)
#define BIT_SCC_APB_SCC_ROSC_RPT_SCC_ROSC_SETTING(x)           (((x) & 0x1F) << 20)
#define BIT_SCC_APB_SCC_ROSC_RPT_SCC_ROSC_CNT(x)               (((x) & 0xFFFFF))

/* REG_SCC_APB_HWM_CTRL_0 */

#define BIT_SCC_APB_HWM_CTRL_0_HWM2_DRDY_0_0                   BIT(31)
#define BIT_SCC_APB_HWM_CTRL_0_HWM2_TRIG_0_0                   BIT(17)
#define BIT_SCC_APB_HWM_CTRL_0_HWM2_RST_N_0_0                  BIT(16)
#define BIT_SCC_APB_HWM_CTRL_0_HWM2_SO_0_0                     BIT(12)
#define BIT_SCC_APB_HWM_CTRL_0_HWM2_SI_0_0                     BIT(11)
#define BIT_SCC_APB_HWM_CTRL_0_HWM2_CKSEL_0_0(x)               (((x) & 0x7) << 8)
#define BIT_SCC_APB_HWM_CTRL_0_HWM2_OFFSET_0_0(x)              (((x) & 0x1F) << 3)
#define BIT_SCC_APB_HWM_CTRL_0_HWM2_ACC_0_0                    BIT(2)
#define BIT_SCC_APB_HWM_CTRL_0_HWM2_EN_0_0                     BIT(1)
#define BIT_SCC_APB_HWM_CTRL_0_HWM2_SE_0_0                     BIT(0)

/* REG_SCC_APB_HWM_CTRL_1 */

#define BIT_SCC_APB_HWM_CTRL_1_HWM1_DRDY_2_0                   BIT(31)
#define BIT_SCC_APB_HWM_CTRL_1_HWM1_TRIG_2_0                   BIT(17)
#define BIT_SCC_APB_HWM_CTRL_1_HWM1_RST_N_2_0                  BIT(16)
#define BIT_SCC_APB_HWM_CTRL_1_HWM1_SO_2_0                     BIT(12)
#define BIT_SCC_APB_HWM_CTRL_1_HWM1_SI_2_0                     BIT(11)
#define BIT_SCC_APB_HWM_CTRL_1_HWM1_CKSEL_2_0(x)               (((x) & 0x7) << 8)
#define BIT_SCC_APB_HWM_CTRL_1_HWM1_OFFSET_2_0(x)              (((x) & 0x1F) << 3)
#define BIT_SCC_APB_HWM_CTRL_1_HWM1_ACC_2_0                    BIT(2)
#define BIT_SCC_APB_HWM_CTRL_1_HWM1_EN_2_0                     BIT(1)
#define BIT_SCC_APB_HWM_CTRL_1_HWM1_SE_2_0                     BIT(0)

/* REG_SCC_APB_HWM_CTRL_2 */

#define BIT_SCC_APB_HWM_CTRL_2_HWM1_DRDY_6_0                   BIT(31)
#define BIT_SCC_APB_HWM_CTRL_2_HWM1_TRIG_6_0                   BIT(17)
#define BIT_SCC_APB_HWM_CTRL_2_HWM1_RST_N_6_0                  BIT(16)
#define BIT_SCC_APB_HWM_CTRL_2_HWM1_SO_6_0                     BIT(12)
#define BIT_SCC_APB_HWM_CTRL_2_HWM1_SI_6_0                     BIT(11)
#define BIT_SCC_APB_HWM_CTRL_2_HWM1_CKSEL_6_0(x)               (((x) & 0x7) << 8)
#define BIT_SCC_APB_HWM_CTRL_2_HWM1_OFFSET_6_0(x)              (((x) & 0x1F) << 3)
#define BIT_SCC_APB_HWM_CTRL_2_HWM1_ACC_6_0                    BIT(2)
#define BIT_SCC_APB_HWM_CTRL_2_HWM1_EN_6_0                     BIT(1)
#define BIT_SCC_APB_HWM_CTRL_2_HWM1_SE_6_0                     BIT(0)

/* REG_SCC_APB_HWM_CTRL_3 */

#define BIT_SCC_APB_HWM_CTRL_3_HWM1_DRDY_7_0                   BIT(31)
#define BIT_SCC_APB_HWM_CTRL_3_HWM1_TRIG_7_0                   BIT(17)
#define BIT_SCC_APB_HWM_CTRL_3_HWM1_RST_N_7_0                  BIT(16)
#define BIT_SCC_APB_HWM_CTRL_3_HWM1_SO_7_0                     BIT(12)
#define BIT_SCC_APB_HWM_CTRL_3_HWM1_SI_7_0                     BIT(11)
#define BIT_SCC_APB_HWM_CTRL_3_HWM1_CKSEL_7_0(x)               (((x) & 0x7) << 8)
#define BIT_SCC_APB_HWM_CTRL_3_HWM1_OFFSET_7_0(x)              (((x) & 0x1F) << 3)
#define BIT_SCC_APB_HWM_CTRL_3_HWM1_ACC_7_0                    BIT(2)
#define BIT_SCC_APB_HWM_CTRL_3_HWM1_EN_7_0                     BIT(1)
#define BIT_SCC_APB_HWM_CTRL_3_HWM1_SE_7_0                     BIT(0)

/* REG_SCC_APB_HWM_CTRL_4 */

#define BIT_SCC_APB_HWM_CTRL_4_HWM2_DRDY_1_0                   BIT(31)
#define BIT_SCC_APB_HWM_CTRL_4_HWM2_TRIG_1_0                   BIT(17)
#define BIT_SCC_APB_HWM_CTRL_4_HWM2_RST_N_1_0                  BIT(16)
#define BIT_SCC_APB_HWM_CTRL_4_HWM2_SO_1_0                     BIT(12)
#define BIT_SCC_APB_HWM_CTRL_4_HWM2_SI_1_0                     BIT(11)
#define BIT_SCC_APB_HWM_CTRL_4_HWM2_CKSEL_1_0(x)               (((x) & 0x7) << 8)
#define BIT_SCC_APB_HWM_CTRL_4_HWM2_OFFSET_1_0(x)              (((x) & 0x1F) << 3)
#define BIT_SCC_APB_HWM_CTRL_4_HWM2_ACC_1_0                    BIT(2)
#define BIT_SCC_APB_HWM_CTRL_4_HWM2_EN_1_0                     BIT(1)
#define BIT_SCC_APB_HWM_CTRL_4_HWM2_SE_1_0                     BIT(0)

/* REG_SCC_APB_HWM_CTRL_5 */

#define BIT_SCC_APB_HWM_CTRL_5_HWM2_DRDY_1_1                   BIT(31)
#define BIT_SCC_APB_HWM_CTRL_5_HWM2_TRIG_1_1                   BIT(17)
#define BIT_SCC_APB_HWM_CTRL_5_HWM2_RST_N_1_1                  BIT(16)
#define BIT_SCC_APB_HWM_CTRL_5_HWM2_SO_1_1                     BIT(12)
#define BIT_SCC_APB_HWM_CTRL_5_HWM2_SI_1_1                     BIT(11)
#define BIT_SCC_APB_HWM_CTRL_5_HWM2_CKSEL_1_1(x)               (((x) & 0x7) << 8)
#define BIT_SCC_APB_HWM_CTRL_5_HWM2_OFFSET_1_1(x)              (((x) & 0x1F) << 3)
#define BIT_SCC_APB_HWM_CTRL_5_HWM2_ACC_1_1                    BIT(2)
#define BIT_SCC_APB_HWM_CTRL_5_HWM2_EN_1_1                     BIT(1)
#define BIT_SCC_APB_HWM_CTRL_5_HWM2_SE_1_1                     BIT(0)

/* REG_SCC_APB_HWM_CTRL_6 */

#define BIT_SCC_APB_HWM_CTRL_6_HWM2_DRDY_3_0                   BIT(31)
#define BIT_SCC_APB_HWM_CTRL_6_HWM2_TRIG_3_0                   BIT(17)
#define BIT_SCC_APB_HWM_CTRL_6_HWM2_RST_N_3_0                  BIT(16)
#define BIT_SCC_APB_HWM_CTRL_6_HWM2_SO_3_0                     BIT(12)
#define BIT_SCC_APB_HWM_CTRL_6_HWM2_SI_3_0                     BIT(11)
#define BIT_SCC_APB_HWM_CTRL_6_HWM2_CKSEL_3_0(x)               (((x) & 0x7) << 8)
#define BIT_SCC_APB_HWM_CTRL_6_HWM2_OFFSET_3_0(x)              (((x) & 0x1F) << 3)
#define BIT_SCC_APB_HWM_CTRL_6_HWM2_ACC_3_0                    BIT(2)
#define BIT_SCC_APB_HWM_CTRL_6_HWM2_EN_3_0                     BIT(1)
#define BIT_SCC_APB_HWM_CTRL_6_HWM2_SE_3_0                     BIT(0)

/* REG_SCC_APB_HWM_CTRL_7 */

#define BIT_SCC_APB_HWM_CTRL_7_HWM2_DRDY_4_0                   BIT(31)
#define BIT_SCC_APB_HWM_CTRL_7_HWM2_TRIG_4_0                   BIT(17)
#define BIT_SCC_APB_HWM_CTRL_7_HWM2_RST_N_4_0                  BIT(16)
#define BIT_SCC_APB_HWM_CTRL_7_HWM2_SO_4_0                     BIT(12)
#define BIT_SCC_APB_HWM_CTRL_7_HWM2_SI_4_0                     BIT(11)
#define BIT_SCC_APB_HWM_CTRL_7_HWM2_CKSEL_4_0(x)               (((x) & 0x7) << 8)
#define BIT_SCC_APB_HWM_CTRL_7_HWM2_OFFSET_4_0(x)              (((x) & 0x1F) << 3)
#define BIT_SCC_APB_HWM_CTRL_7_HWM2_ACC_4_0                    BIT(2)
#define BIT_SCC_APB_HWM_CTRL_7_HWM2_EN_4_0                     BIT(1)
#define BIT_SCC_APB_HWM_CTRL_7_HWM2_SE_4_0                     BIT(0)

/* REG_SCC_APB_HWM_CTRL_8 */

#define BIT_SCC_APB_HWM_CTRL_8_HWM2_DRDY_5_0                   BIT(31)
#define BIT_SCC_APB_HWM_CTRL_8_HWM2_TRIG_5_0                   BIT(17)
#define BIT_SCC_APB_HWM_CTRL_8_HWM2_RST_N_5_0                  BIT(16)
#define BIT_SCC_APB_HWM_CTRL_8_HWM2_SO_5_0                     BIT(12)
#define BIT_SCC_APB_HWM_CTRL_8_HWM2_SI_5_0                     BIT(11)
#define BIT_SCC_APB_HWM_CTRL_8_HWM2_CKSEL_5_0(x)               (((x) & 0x7) << 8)
#define BIT_SCC_APB_HWM_CTRL_8_HWM2_OFFSET_5_0(x)              (((x) & 0x1F) << 3)
#define BIT_SCC_APB_HWM_CTRL_8_HWM2_ACC_5_0                    BIT(2)
#define BIT_SCC_APB_HWM_CTRL_8_HWM2_EN_5_0                     BIT(1)
#define BIT_SCC_APB_HWM_CTRL_8_HWM2_SE_5_0                     BIT(0)

/* REG_SCC_APB_HWM_CTRL_9 */

#define BIT_SCC_APB_HWM_CTRL_9_HWM2_DRDY_6_1                   BIT(31)
#define BIT_SCC_APB_HWM_CTRL_9_HWM2_TRIG_6_1                   BIT(17)
#define BIT_SCC_APB_HWM_CTRL_9_HWM2_RST_N_6_1                  BIT(16)
#define BIT_SCC_APB_HWM_CTRL_9_HWM2_SO_6_1                     BIT(12)
#define BIT_SCC_APB_HWM_CTRL_9_HWM2_SI_6_1                     BIT(11)
#define BIT_SCC_APB_HWM_CTRL_9_HWM2_CKSEL_6_1(x)               (((x) & 0x7) << 8)
#define BIT_SCC_APB_HWM_CTRL_9_HWM2_OFFSET_6_1(x)              (((x) & 0x1F) << 3)
#define BIT_SCC_APB_HWM_CTRL_9_HWM2_ACC_6_1                    BIT(2)
#define BIT_SCC_APB_HWM_CTRL_9_HWM2_EN_6_1                     BIT(1)
#define BIT_SCC_APB_HWM_CTRL_9_HWM2_SE_6_1                     BIT(0)

/* REG_SCC_APB_HWM_CTRL_10 */

#define BIT_SCC_APB_HWM_CTRL_10_HWM2_DRDY_6_2                  BIT(31)
#define BIT_SCC_APB_HWM_CTRL_10_HWM2_TRIG_6_2                  BIT(17)
#define BIT_SCC_APB_HWM_CTRL_10_HWM2_RST_N_6_2                 BIT(16)
#define BIT_SCC_APB_HWM_CTRL_10_HWM2_SO_6_2                    BIT(12)
#define BIT_SCC_APB_HWM_CTRL_10_HWM2_SI_6_2                    BIT(11)
#define BIT_SCC_APB_HWM_CTRL_10_HWM2_CKSEL_6_2(x)              (((x) & 0x7) << 8)
#define BIT_SCC_APB_HWM_CTRL_10_HWM2_OFFSET_6_2(x)             (((x) & 0x1F) << 3)
#define BIT_SCC_APB_HWM_CTRL_10_HWM2_ACC_6_2                   BIT(2)
#define BIT_SCC_APB_HWM_CTRL_10_HWM2_EN_6_2                    BIT(1)
#define BIT_SCC_APB_HWM_CTRL_10_HWM2_SE_6_2                    BIT(0)

/* REG_SCC_APB_HWM_RPT_SEL */

#define BIT_SCC_APB_HWM_RPT_SEL_HWM_SHFT_CNT(x)                (((x) & 0xFFFF) << 16)
#define BIT_SCC_APB_HWM_RPT_SEL_HWM_SHFT_EN                    BIT(15)
#define BIT_SCC_APB_HWM_RPT_SEL_HWM_RPT_SEL(x)                 (((x) & 0xF))

/* REG_SCC_APB_HWM_RPT */

#define BIT_SCC_APB_HWM_RPT_HWM_RPT(x)                         (((x) & 0xFFFFFFFF))

/* REG_SCC_APB_HWM3S_RPT0 */

#define BIT_SCC_APB_HWM3S_RPT0_HWM3S_ERR_0_0(x)                (((x) & 0x1F) << 27)
#define BIT_SCC_APB_HWM3S_RPT0_HWM3S_ERR_1_0(x)                (((x) & 0x1F) << 22)
#define BIT_SCC_APB_HWM3S_RPT0_HWM3S_ERR_1_1(x)                (((x) & 0x1F) << 17)
#define BIT_SCC_APB_HWM3S_RPT0_HWM3S_ERR_2_0(x)                (((x) & 0x1F) << 12)
#define BIT_SCC_APB_HWM3S_RPT0_HWM3S_ERR_3_0(x)                (((x) & 0x1F) << 7)

/* REG_SCC_APB_HWM3S_RPT1 */

#define BIT_SCC_APB_HWM3S_RPT1_HWM3S_ERR_4_0(x)                (((x) & 0x1F) << 27)
#define BIT_SCC_APB_HWM3S_RPT1_HWM3S_ERR_5_0(x)                (((x) & 0x1F) << 22)
#define BIT_SCC_APB_HWM3S_RPT1_HWM3S_ERR_6_0(x)                (((x) & 0x1F) << 17)
#define BIT_SCC_APB_HWM3S_RPT1_HWM3S_ERR_6_1(x)                (((x) & 0x1F) << 12)
#define BIT_SCC_APB_HWM3S_RPT1_HWM3S_ERR_7_0(x)                (((x) & 0x1F) << 7)

/* REG_SCC_APB_HWM3H_RPT0 */

#define BIT_SCC_APB_HWM3H_RPT0_HWM3H_ERR_0_0(x)                (((x) & 0x1F) << 27)
#define BIT_SCC_APB_HWM3H_RPT0_HWM3H_ERR_1_0(x)                (((x) & 0x1F) << 22)
#define BIT_SCC_APB_HWM3H_RPT0_HWM3H_ERR_1_1(x)                (((x) & 0x1F) << 17)
#define BIT_SCC_APB_HWM3H_RPT0_HWM3H_ERR_2_0(x)                (((x) & 0x1F) << 12)
#define BIT_SCC_APB_HWM3H_RPT0_HWM3H_ERR_3_0(x)                (((x) & 0x1F) << 7)

/* REG_SCC_APB_HWM3H_RPT1 */

#define BIT_SCC_APB_HWM3H_RPT1_HWM3H_ERR_4_0(x)                (((x) & 0x1F) << 27)
#define BIT_SCC_APB_HWM3H_RPT1_HWM3H_ERR_5_0(x)                (((x) & 0x1F) << 22)
#define BIT_SCC_APB_HWM3H_RPT1_HWM3H_ERR_6_0(x)                (((x) & 0x1F) << 17)
#define BIT_SCC_APB_HWM3H_RPT1_HWM3H_ERR_6_1(x)                (((x) & 0x1F) << 12)
#define BIT_SCC_APB_HWM3H_RPT1_HWM3H_ERR_7_0(x)                (((x) & 0x1F) << 7)

/* REG_SCC_APB_HWM4S_RPT0 */

#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_0_0                   BIT(31)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_0_1                   BIT(30)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_0_2                   BIT(29)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_0_3                   BIT(28)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_0_4                   BIT(27)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_0_5                   BIT(26)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_0_6                   BIT(25)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_0_7                   BIT(24)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_0                   BIT(23)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_1                   BIT(22)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_2                   BIT(21)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_3                   BIT(20)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_4                   BIT(19)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_5                   BIT(18)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_6                   BIT(17)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_7                   BIT(16)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_8                   BIT(15)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_9                   BIT(14)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_10                  BIT(13)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_11                  BIT(12)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_12                  BIT(11)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_13                  BIT(10)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_14                  BIT(9)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_15                  BIT(8)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_16                  BIT(7)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_17                  BIT(6)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_18                  BIT(5)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_19                  BIT(4)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_20                  BIT(3)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_21                  BIT(2)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_22                  BIT(1)
#define BIT_SCC_APB_HWM4S_RPT0_HWM4S_ERR_1_23                  BIT(0)

/* REG_SCC_APB_HWM4S_RPT1 */

#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_1_24                  BIT(31)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_1_25                  BIT(30)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_1_26                  BIT(29)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_1_27                  BIT(28)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_1_28                  BIT(27)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_1_29                  BIT(26)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_1_30                  BIT(25)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_1_31                  BIT(24)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_0                   BIT(23)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_1                   BIT(22)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_2                   BIT(21)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_3                   BIT(20)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_4                   BIT(19)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_5                   BIT(18)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_6                   BIT(17)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_7                   BIT(16)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_8                   BIT(15)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_9                   BIT(14)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_10                  BIT(13)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_11                  BIT(12)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_12                  BIT(11)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_13                  BIT(10)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_14                  BIT(9)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_15                  BIT(8)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_16                  BIT(7)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_17                  BIT(6)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_18                  BIT(5)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_19                  BIT(4)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_20                  BIT(3)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_21                  BIT(2)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_22                  BIT(1)
#define BIT_SCC_APB_HWM4S_RPT1_HWM4S_ERR_2_23                  BIT(0)

/* REG_SCC_APB_HWM4S_RPT2 */

#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_2_24                  BIT(31)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_2_25                  BIT(30)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_2_26                  BIT(29)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_2_27                  BIT(28)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_2_28                  BIT(27)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_2_29                  BIT(26)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_2_30                  BIT(25)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_2_31                  BIT(24)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_3_0                   BIT(23)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_3_1                   BIT(22)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_3_2                   BIT(21)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_3_3                   BIT(20)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_3_4                   BIT(19)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_3_5                   BIT(18)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_3_6                   BIT(17)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_3_7                   BIT(16)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_4_0                   BIT(15)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_4_1                   BIT(14)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_4_2                   BIT(13)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_4_3                   BIT(12)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_4_4                   BIT(11)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_4_5                   BIT(10)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_4_6                   BIT(9)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_4_7                   BIT(8)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_5_0                   BIT(7)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_5_1                   BIT(6)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_5_2                   BIT(5)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_5_3                   BIT(4)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_5_4                   BIT(3)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_5_5                   BIT(2)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_5_6                   BIT(1)
#define BIT_SCC_APB_HWM4S_RPT2_HWM4S_ERR_5_7                   BIT(0)

/* REG_SCC_APB_HWM4S_RPT3 */

#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_6_0                   BIT(31)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_6_1                   BIT(30)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_6_2                   BIT(29)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_6_3                   BIT(28)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_6_4                   BIT(27)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_6_5                   BIT(26)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_6_6                   BIT(25)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_6_7                   BIT(24)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_6_8                   BIT(23)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_6_9                   BIT(22)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_6_10                  BIT(21)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_6_11                  BIT(20)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_6_12                  BIT(19)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_6_13                  BIT(18)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_6_14                  BIT(17)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_6_15                  BIT(16)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_7_0                   BIT(15)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_7_1                   BIT(14)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_7_2                   BIT(13)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_7_3                   BIT(12)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_7_4                   BIT(11)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_7_5                   BIT(10)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_7_6                   BIT(9)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_7_7                   BIT(8)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_7_8                   BIT(7)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_7_9                   BIT(6)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_7_10                  BIT(5)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_7_11                  BIT(4)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_7_12                  BIT(3)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_7_13                  BIT(2)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_7_14                  BIT(1)
#define BIT_SCC_APB_HWM4S_RPT3_HWM4S_ERR_7_15                  BIT(0)

/* REG_SCC_APB_HWM4H_RPT0 */

#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_0_0                   BIT(31)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_0_1                   BIT(30)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_0_2                   BIT(29)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_0_3                   BIT(28)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_0_4                   BIT(27)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_0_5                   BIT(26)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_0_6                   BIT(25)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_0_7                   BIT(24)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_0                   BIT(23)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_1                   BIT(22)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_2                   BIT(21)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_3                   BIT(20)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_4                   BIT(19)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_5                   BIT(18)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_6                   BIT(17)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_7                   BIT(16)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_8                   BIT(15)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_9                   BIT(14)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_10                  BIT(13)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_11                  BIT(12)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_12                  BIT(11)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_13                  BIT(10)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_14                  BIT(9)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_15                  BIT(8)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_16                  BIT(7)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_17                  BIT(6)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_18                  BIT(5)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_19                  BIT(4)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_20                  BIT(3)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_21                  BIT(2)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_22                  BIT(1)
#define BIT_SCC_APB_HWM4H_RPT0_HWM4H_ERR_1_23                  BIT(0)

/* REG_SCC_APB_HWM4H_RPT1 */

#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_1_24                  BIT(31)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_1_25                  BIT(30)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_1_26                  BIT(29)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_1_27                  BIT(28)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_1_28                  BIT(27)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_1_29                  BIT(26)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_1_30                  BIT(25)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_1_31                  BIT(24)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_0                   BIT(23)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_1                   BIT(22)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_2                   BIT(21)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_3                   BIT(20)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_4                   BIT(19)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_5                   BIT(18)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_6                   BIT(17)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_7                   BIT(16)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_8                   BIT(15)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_9                   BIT(14)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_10                  BIT(13)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_11                  BIT(12)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_12                  BIT(11)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_13                  BIT(10)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_14                  BIT(9)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_15                  BIT(8)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_16                  BIT(7)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_17                  BIT(6)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_18                  BIT(5)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_19                  BIT(4)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_20                  BIT(3)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_21                  BIT(2)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_22                  BIT(1)
#define BIT_SCC_APB_HWM4H_RPT1_HWM4H_ERR_2_23                  BIT(0)

/* REG_SCC_APB_HWM4H_RPT2 */

#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_2_24                  BIT(31)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_2_25                  BIT(30)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_2_26                  BIT(29)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_2_27                  BIT(28)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_2_28                  BIT(27)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_2_29                  BIT(26)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_2_30                  BIT(25)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_2_31                  BIT(24)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_3_0                   BIT(23)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_3_1                   BIT(22)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_3_2                   BIT(21)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_3_3                   BIT(20)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_3_4                   BIT(19)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_3_5                   BIT(18)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_3_6                   BIT(17)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_3_7                   BIT(16)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_4_0                   BIT(15)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_4_1                   BIT(14)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_4_2                   BIT(13)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_4_3                   BIT(12)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_4_4                   BIT(11)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_4_5                   BIT(10)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_4_6                   BIT(9)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_4_7                   BIT(8)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_5_0                   BIT(7)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_5_1                   BIT(6)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_5_2                   BIT(5)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_5_3                   BIT(4)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_5_4                   BIT(3)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_5_5                   BIT(2)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_5_6                   BIT(1)
#define BIT_SCC_APB_HWM4H_RPT2_HWM4H_ERR_5_7                   BIT(0)

/* REG_SCC_APB_HWM4H_RPT3 */

#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_6_0                   BIT(31)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_6_1                   BIT(30)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_6_2                   BIT(29)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_6_3                   BIT(28)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_6_4                   BIT(27)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_6_5                   BIT(26)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_6_6                   BIT(25)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_6_7                   BIT(24)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_6_8                   BIT(23)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_6_9                   BIT(22)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_6_10                  BIT(21)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_6_11                  BIT(20)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_6_12                  BIT(19)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_6_13                  BIT(18)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_6_14                  BIT(17)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_6_15                  BIT(16)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_7_0                   BIT(15)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_7_1                   BIT(14)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_7_2                   BIT(13)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_7_3                   BIT(12)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_7_4                   BIT(11)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_7_5                   BIT(10)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_7_6                   BIT(9)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_7_7                   BIT(8)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_7_8                   BIT(7)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_7_9                   BIT(6)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_7_10                  BIT(5)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_7_11                  BIT(4)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_7_12                  BIT(3)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_7_13                  BIT(2)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_7_14                  BIT(1)
#define BIT_SCC_APB_HWM4H_RPT3_HWM4H_ERR_7_15                  BIT(0)


#endif /* SCC_APB_H */

