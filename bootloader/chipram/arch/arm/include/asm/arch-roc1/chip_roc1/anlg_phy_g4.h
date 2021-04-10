/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-18 10:53:49
 *
 */


#ifndef ANLG_PHY_G4_H
#define ANLG_PHY_G4_H

#define CTL_BASE_ANLG_PHY_G4 0x323C0000


#define REG_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CTRL0                 ( CTL_BASE_ANLG_PHY_G4 + 0x0000 )
#define REG_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CTRL1                 ( CTL_BASE_ANLG_PHY_G4 + 0x0004 )
#define REG_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CTRL2                 ( CTL_BASE_ANLG_PHY_G4 + 0x0008 )
#define REG_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CTRL3                 ( CTL_BASE_ANLG_PHY_G4 + 0x000C )
#define REG_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CTRL4                 ( CTL_BASE_ANLG_PHY_G4 + 0x0010 )
#define REG_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CTRL5                 ( CTL_BASE_ANLG_PHY_G4 + 0x0014 )
#define REG_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CTRL6                 ( CTL_BASE_ANLG_PHY_G4 + 0x0018 )
#define REG_ANLG_PHY_G4_ANALOG_MPLL1_WRAP_GLUE_CTRL              ( CTL_BASE_ANLG_PHY_G4 + 0x001C )
#define REG_ANLG_PHY_G4_ANALOG_MPLL1_PROMETHEUS_DVFS_INDEX0      ( CTL_BASE_ANLG_PHY_G4 + 0x0020 )
#define REG_ANLG_PHY_G4_ANALOG_MPLL1_PROMETHEUS_DVFS_INDEX1      ( CTL_BASE_ANLG_PHY_G4 + 0x0024 )
#define REG_ANLG_PHY_G4_ANALOG_MPLL1_PROMETHEUS_DVFS_INDEX2      ( CTL_BASE_ANLG_PHY_G4 + 0x0028 )
#define REG_ANLG_PHY_G4_ANALOG_MPLL1_PROMETHEUS_DVFS_INDEX3      ( CTL_BASE_ANLG_PHY_G4 + 0x002C )
#define REG_ANLG_PHY_G4_ANALOG_MPLL1_PROMETHEUS_DVFS_INDEX4      ( CTL_BASE_ANLG_PHY_G4 + 0x0030 )
#define REG_ANLG_PHY_G4_ANALOG_MPLL1_PROMETHEUS_DVFS_INDEX5      ( CTL_BASE_ANLG_PHY_G4 + 0x0034 )
#define REG_ANLG_PHY_G4_ANALOG_MPLL1_PROMETHEUS_DVFS_INDEX6      ( CTL_BASE_ANLG_PHY_G4 + 0x0038 )
#define REG_ANLG_PHY_G4_ANALOG_MPLL1_PROMETHEUS_DVFS_INDEX7      ( CTL_BASE_ANLG_PHY_G4 + 0x003C )
#define REG_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CTRL_DBG_SEL          ( CTL_BASE_ANLG_PHY_G4 + 0x0040 )
#define REG_ANLG_PHY_G4_ANALOG_THM2_0_THM2_CTL                   ( CTL_BASE_ANLG_PHY_G4 + 0x0044 )
#define REG_ANLG_PHY_G4_ANALOG_THM2_0_THM2_RESERVED_CTL          ( CTL_BASE_ANLG_PHY_G4 + 0x0048 )
#define REG_ANLG_PHY_G4_ANALOG_THM2_0_WRAP_GLUE_CTRL             ( CTL_BASE_ANLG_PHY_G4 + 0x004C )

/* REG_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CTRL0 */

#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_N(x)                                (((x) & 0x7FF) << 8)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_ICP(x)                              (((x) & 0x7) << 5)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CP_EN                               BIT(4)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_LDO_TRIM(x)                         (((x) & 0xF))

/* REG_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CTRL1 */

#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_R2_SEL(x)                           (((x) & 0x3) << 17)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_R3_SEL(x)                           (((x) & 0x3) << 15)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_C1_SEL(x)                           (((x) & 0x3) << 13)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_C2_SEL(x)                           (((x) & 0x3) << 11)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_KVCO_SEL(x)                         (((x) & 0x3) << 9)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_VCO_TEST_EN                         BIT(8)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_VCO_TEST_INT                        BIT(7)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_VCO_TEST_INTSEL(x)                  (((x) & 0x7) << 4)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_FBDIV_EN                            BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_VCOBUF_EN                           BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CP_OFFSET(x)                        (((x) & 0x3))

/* REG_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CTRL2 */

#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_NINT(x)                             (((x) & 0x7F) << 23)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_KINT(x)                             (((x) & 0x7FFFFF))

/* REG_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CTRL3 */

#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_SDM_EN                              BIT(26)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CCS_CTRL(x)                         (((x) & 0xFF) << 18)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_MOD_EN                              BIT(17)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_DIV_S                               BIT(16)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_RESERVED(x)                         (((x) & 0xFFFF))

/* REG_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CTRL4 */

#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_BIST_EN                             BIT(25)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_BIST_CTRL(x)                        (((x) & 0xFF) << 17)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_POSTDIV                             BIT(16)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_BIST_CNT(x)                         (((x) & 0xFFFF))

/* REG_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CTRL5 */

#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_FREQ_DOUBLE_EN                      BIT(19)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CALI_MODE(x)                        (((x) & 0x3) << 17)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CALI_INI(x)                         (((x) & 0x1F) << 12)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CALI_TRIG                           BIT(11)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_FREQ_DIFF_EN                        BIT(10)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CALI_WAITCNT(x)                     (((x) & 0x3) << 8)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CALI_POLARITY                       BIT(7)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CALI_DONE                           BIT(6)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CALI_OUT(x)                         (((x) & 0x1F) << 1)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CALI_CPPD                           BIT(0)

/* REG_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CTRL6 */

#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_VCTRLH_SEL(x)                       (((x) & 0x7) << 18)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_VCTRLL_SEL(x)                       (((x) & 0x7) << 15)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_RG_CLOSELOOP_EN                     BIT(14)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_VCO_BANK_SEL(x)                     (((x) & 0x1F) << 9)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CALI_VCTRL_HIGH                     BIT(8)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CALI_VCTRL_LOW                      BIT(7)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_VCO_BANK_SEL_OFFSET                 BIT(6)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_ADJ_MANUAL_PD                       BIT(5)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_ISO_SW_EN                           BIT(4)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CLKIN_SEL                           BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_TEST_CLK_EN                               BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_TEST_SEL                                  BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_26MBUFFER_PD                        BIT(0)

/* REG_ANLG_PHY_G4_ANALOG_MPLL1_WRAP_GLUE_CTRL */

#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_DGB_SEL_MPLL1_26M_PD                      BIT(0)

/* REG_ANLG_PHY_G4_ANALOG_MPLL1_PROMETHEUS_DVFS_INDEX0 */

#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_N_INDEX0(x)                         (((x) & 0x7FF) << 4)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_POSTDIV_INDEX0                      BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_ICP_INDEX0(x)                       (((x) & 0x7))

/* REG_ANLG_PHY_G4_ANALOG_MPLL1_PROMETHEUS_DVFS_INDEX1 */

#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_N_INDEX1(x)                         (((x) & 0x7FF) << 4)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_POSTDIV_INDEX1                      BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_ICP_INDEX1(x)                       (((x) & 0x7))

/* REG_ANLG_PHY_G4_ANALOG_MPLL1_PROMETHEUS_DVFS_INDEX2 */

#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_N_INDEX2(x)                         (((x) & 0x7FF) << 4)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_POSTDIV_INDEX2                      BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_ICP_INDEX2(x)                       (((x) & 0x7))

/* REG_ANLG_PHY_G4_ANALOG_MPLL1_PROMETHEUS_DVFS_INDEX3 */

#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_N_INDEX3(x)                         (((x) & 0x7FF) << 4)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_POSTDIV_INDEX3                      BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_ICP_INDEX3(x)                       (((x) & 0x7))

/* REG_ANLG_PHY_G4_ANALOG_MPLL1_PROMETHEUS_DVFS_INDEX4 */

#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_N_INDEX4(x)                         (((x) & 0x7FF) << 4)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_POSTDIV_INDEX4                      BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_ICP_INDEX4(x)                       (((x) & 0x7))

/* REG_ANLG_PHY_G4_ANALOG_MPLL1_PROMETHEUS_DVFS_INDEX5 */

#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_N_INDEX5(x)                         (((x) & 0x7FF) << 4)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_POSTDIV_INDEX5                      BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_ICP_INDEX5(x)                       (((x) & 0x7))

/* REG_ANLG_PHY_G4_ANALOG_MPLL1_PROMETHEUS_DVFS_INDEX6 */

#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_N_INDEX6(x)                         (((x) & 0x7FF) << 4)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_POSTDIV_INDEX6                      BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_ICP_INDEX6(x)                       (((x) & 0x7))

/* REG_ANLG_PHY_G4_ANALOG_MPLL1_PROMETHEUS_DVFS_INDEX7 */

#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_N_INDEX7(x)                         (((x) & 0x7FF) << 4)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_POSTDIV_INDEX7                      BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_ICP_INDEX7(x)                       (((x) & 0x7))

/* REG_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CTRL_DBG_SEL */

#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_DBG_SEL_ANALOG_MPLL1_MPLL1_ICP            BIT(4)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_DBG_SEL_ANALOG_MPLL1_MPLL1_N              BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_DBG_SEL_ANALOG_MPLL1_MPLL1_POSTDIV        BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CLK_JITTER_MON_SEL(x)               (((x) & 0x3))

/* REG_ANLG_PHY_G4_ANALOG_THM2_0_THM2_CTL */

#define BIT_ANLG_PHY_G4_ANALOG_THM2_0_THM_BG_RBIAS_MODE                        BIT(13)
#define BIT_ANLG_PHY_G4_ANALOG_THM2_0_THM_TEST_SEL(x)                          (((x) & 0x3) << 11)
#define BIT_ANLG_PHY_G4_ANALOG_THM2_0_THM_BP_MODE                              BIT(10)
#define BIT_ANLG_PHY_G4_ANALOG_THM2_0_THM_BP_DATA(x)                           (((x) & 0x3FF))

/* REG_ANLG_PHY_G4_ANALOG_THM2_0_THM2_RESERVED_CTL */

#define BIT_ANLG_PHY_G4_ANALOG_THM2_0_THM_RESERVED(x)                          (((x) & 0xFFFF))

/* REG_ANLG_PHY_G4_ANALOG_THM2_0_WRAP_GLUE_CTRL */

#define BIT_ANLG_PHY_G4_ANALOG_THM2_0_DGB_SEL_THM_RESERVED_BIT0_CONVERT_CYCLE  BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_THM2_0_DGB_SEL_THM_RESERVED_BIT3_SENSOR_SEL     BIT(0)


#endif /* ANLG_PHY_G4_H */


