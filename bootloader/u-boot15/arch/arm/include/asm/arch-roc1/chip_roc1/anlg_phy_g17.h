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


#ifndef ANLG_PHY_G17_H
#define ANLG_PHY_G17_H

#define CTL_BASE_ANLG_PHY_G17 0x32418000


#define REG_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CTRL0                 ( CTL_BASE_ANLG_PHY_G17 + 0x0000 )
#define REG_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CTRL1                 ( CTL_BASE_ANLG_PHY_G17 + 0x0004 )
#define REG_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CTRL2                 ( CTL_BASE_ANLG_PHY_G17 + 0x0008 )
#define REG_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CTRL3                 ( CTL_BASE_ANLG_PHY_G17 + 0x000C )
#define REG_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CTRL4                 ( CTL_BASE_ANLG_PHY_G17 + 0x0010 )
#define REG_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CTRL5                 ( CTL_BASE_ANLG_PHY_G17 + 0x0014 )
#define REG_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CTRL6                 ( CTL_BASE_ANLG_PHY_G17 + 0x0018 )
#define REG_ANLG_PHY_G17_ANALOG_MPLL0_WRAP_GLUE_CTRL              ( CTL_BASE_ANLG_PHY_G17 + 0x001C )
#define REG_ANLG_PHY_G17_ANALOG_MPLL0_ANANKE_BIG_DVFS_INDEX0      ( CTL_BASE_ANLG_PHY_G17 + 0x0020 )
#define REG_ANLG_PHY_G17_ANALOG_MPLL0_ANANKE_BIG_DVFS_INDEX1      ( CTL_BASE_ANLG_PHY_G17 + 0x0024 )
#define REG_ANLG_PHY_G17_ANALOG_MPLL0_ANANKE_BIG_DVFS_INDEX2      ( CTL_BASE_ANLG_PHY_G17 + 0x0028 )
#define REG_ANLG_PHY_G17_ANALOG_MPLL0_ANANKE_BIG_DVFS_INDEX3      ( CTL_BASE_ANLG_PHY_G17 + 0x002C )
#define REG_ANLG_PHY_G17_ANALOG_MPLL0_ANANKE_BIG_DVFS_INDEX4      ( CTL_BASE_ANLG_PHY_G17 + 0x0030 )
#define REG_ANLG_PHY_G17_ANALOG_MPLL0_ANANKE_BIG_DVFS_INDEX5      ( CTL_BASE_ANLG_PHY_G17 + 0x0034 )
#define REG_ANLG_PHY_G17_ANALOG_MPLL0_ANANKE_BIG_DVFS_INDEX6      ( CTL_BASE_ANLG_PHY_G17 + 0x0038 )
#define REG_ANLG_PHY_G17_ANALOG_MPLL0_ANANKE_BIG_DVFS_INDEX7      ( CTL_BASE_ANLG_PHY_G17 + 0x003C )
#define REG_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CTRL_DBG_SEL          ( CTL_BASE_ANLG_PHY_G17 + 0x0040 )
#define REG_ANLG_PHY_G17_ANALOG_MPLL0_REG_SEL_CFG_0               ( CTL_BASE_ANLG_PHY_G17 + 0x0044 )

/* REG_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CTRL0 */

#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_PD                            BIT(23)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_RST                           BIT(22)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CLKOUT_EN                     BIT(21)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_DIV32_EN                      BIT(20)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_LOCK_DONE                     BIT(19)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_N(x)                          (((x) & 0x7FF) << 8)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_ICP(x)                        (((x) & 0x7) << 5)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CP_EN                         BIT(4)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_LDO_TRIM(x)                   (((x) & 0xF))

/* REG_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CTRL1 */

#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_R2_SEL(x)                     (((x) & 0x3) << 17)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_R3_SEL(x)                     (((x) & 0x3) << 15)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_C1_SEL(x)                     (((x) & 0x3) << 13)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_C2_SEL(x)                     (((x) & 0x3) << 11)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_KVCO_SEL(x)                   (((x) & 0x3) << 9)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_VCO_TEST_EN                   BIT(8)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_VCO_TEST_INT                  BIT(7)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_VCO_TEST_INTSEL(x)            (((x) & 0x7) << 4)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_FBDIV_EN                      BIT(3)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_VCOBUF_EN                     BIT(2)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CP_OFFSET(x)                  (((x) & 0x3))

/* REG_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CTRL2 */

#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_NINT(x)                       (((x) & 0x7F) << 23)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_KINT(x)                       (((x) & 0x7FFFFF))

/* REG_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CTRL3 */

#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_SDM_EN                        BIT(26)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CCS_CTRL(x)                   (((x) & 0xFF) << 18)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_MOD_EN                        BIT(17)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_DIV_S                         BIT(16)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_RESERVED(x)                   (((x) & 0xFFFF))

/* REG_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CTRL4 */

#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_BIST_EN                       BIT(25)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_BIST_CTRL(x)                  (((x) & 0xFF) << 17)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_POSTDIV                       BIT(16)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_BIST_CNT(x)                   (((x) & 0xFFFF))

/* REG_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CTRL5 */

#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_FREQ_DOUBLE_EN                BIT(19)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CALI_MODE(x)                  (((x) & 0x3) << 17)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CALI_INI(x)                   (((x) & 0x1F) << 12)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CALI_TRIG                     BIT(11)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_FREQ_DIFF_EN                  BIT(10)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CALI_WAITCNT(x)               (((x) & 0x3) << 8)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CALI_POLARITY                 BIT(7)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CALI_DONE                     BIT(6)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CALI_OUT(x)                   (((x) & 0x1F) << 1)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CALI_CPPD                     BIT(0)

/* REG_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CTRL6 */

#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_VCTRLH_SEL(x)                 (((x) & 0x7) << 18)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_VCTRLL_SEL(x)                 (((x) & 0x7) << 15)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_RG_CLOSELOOP_EN               BIT(14)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_VCO_BANK_SEL(x)               (((x) & 0x1F) << 9)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CALI_VCTRL_HIGH               BIT(8)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CALI_VCTRL_LOW                BIT(7)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_VCO_BANK_SEL_OFFSET           BIT(6)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_ADJ_MANUAL_PD                 BIT(5)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_ISO_SW_EN                     BIT(4)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CLKIN_SEL                     BIT(3)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_TEST_CLK_EN                         BIT(2)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_TEST_SEL                            BIT(1)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_26MBUFFER_PD                  BIT(0)

/* REG_ANLG_PHY_G17_ANALOG_MPLL0_WRAP_GLUE_CTRL */

#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_DGB_SEL_MPLL0_26M_PD                BIT(0)

/* REG_ANLG_PHY_G17_ANALOG_MPLL0_ANANKE_BIG_DVFS_INDEX0 */

#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_N_INDEX0(x)                   (((x) & 0x7FF) << 4)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_POSTDIV_INDEX0                BIT(3)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_ICP_INDEX0(x)                 (((x) & 0x7))

/* REG_ANLG_PHY_G17_ANALOG_MPLL0_ANANKE_BIG_DVFS_INDEX1 */

#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_N_INDEX1(x)                   (((x) & 0x7FF) << 4)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_POSTDIV_INDEX1                BIT(3)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_ICP_INDEX1(x)                 (((x) & 0x7))

/* REG_ANLG_PHY_G17_ANALOG_MPLL0_ANANKE_BIG_DVFS_INDEX2 */

#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_N_INDEX2(x)                   (((x) & 0x7FF) << 4)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_POSTDIV_INDEX2                BIT(3)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_ICP_INDEX2(x)                 (((x) & 0x7))

/* REG_ANLG_PHY_G17_ANALOG_MPLL0_ANANKE_BIG_DVFS_INDEX3 */

#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_N_INDEX3(x)                   (((x) & 0x7FF) << 4)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_POSTDIV_INDEX3                BIT(3)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_ICP_INDEX3(x)                 (((x) & 0x7))

/* REG_ANLG_PHY_G17_ANALOG_MPLL0_ANANKE_BIG_DVFS_INDEX4 */

#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_N_INDEX4(x)                   (((x) & 0x7FF) << 4)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_POSTDIV_INDEX4                BIT(3)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_ICP_INDEX4(x)                 (((x) & 0x7))

/* REG_ANLG_PHY_G17_ANALOG_MPLL0_ANANKE_BIG_DVFS_INDEX5 */

#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_N_INDEX5(x)                   (((x) & 0x7FF) << 4)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_POSTDIV_INDEX5                BIT(3)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_ICP_INDEX5(x)                 (((x) & 0x7))

/* REG_ANLG_PHY_G17_ANALOG_MPLL0_ANANKE_BIG_DVFS_INDEX6 */

#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_N_INDEX6(x)                   (((x) & 0x7FF) << 4)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_POSTDIV_INDEX6                BIT(3)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_ICP_INDEX6(x)                 (((x) & 0x7))

/* REG_ANLG_PHY_G17_ANALOG_MPLL0_ANANKE_BIG_DVFS_INDEX7 */

#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_N_INDEX7(x)                   (((x) & 0x7FF) << 4)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_POSTDIV_INDEX7                BIT(3)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_ICP_INDEX7(x)                 (((x) & 0x7))

/* REG_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CTRL_DBG_SEL */

#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_DBG_SEL_ANALOG_MPLL0_MPLL0_ICP      BIT(4)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_DBG_SEL_ANALOG_MPLL0_MPLL0_N        BIT(3)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_DBG_SEL_ANALOG_MPLL0_MPLL0_POSTDIV  BIT(2)
#define BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CLK_JITTER_MON_SEL(x)         (((x) & 0x3))

/* REG_ANLG_PHY_G17_ANALOG_MPLL0_REG_SEL_CFG_0 */

#define BIT_ANLG_PHY_G17_DBG_SEL_ANALOG_MPLL0_MPLL0_PD                    BIT(6)
#define BIT_ANLG_PHY_G17_DBG_SEL_ANALOG_MPLL0_MPLL0_RST                   BIT(5)
#define BIT_ANLG_PHY_G17_DBG_SEL_ANALOG_MPLL0_MPLL0_CLKOUT_EN             BIT(4)
#define BIT_ANLG_PHY_G17_DBG_SEL_ANALOG_MPLL0_MPLL0_DIV32_EN              BIT(3)
#define BIT_ANLG_PHY_G17_DBG_SEL_ANALOG_MPLL0_MPLL0_N                     BIT(2)
#define BIT_ANLG_PHY_G17_DBG_SEL_ANALOG_MPLL0_MPLL0_ICP                   BIT(1)
#define BIT_ANLG_PHY_G17_DBG_SEL_ANALOG_MPLL0_MPLL0_POSTDIV               BIT(0)


#endif /* ANLG_PHY_G17_H */


