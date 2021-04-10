/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-18 10:53:50
 *
 */


#ifndef PIPE_CFGA_H
#define PIPE_CFGA_H

#define CTL_BASE_PIPE_CFGA 0x3240C000


#define REG_PIPE_CFGA_DIG_CFG0   ( CTL_BASE_PIPE_CFGA + 0x0000 )
#define REG_PIPE_CFGA_DIG_CFG1   ( CTL_BASE_PIPE_CFGA + 0x0004 )
#define REG_PIPE_CFGA_DIG_CFG2   ( CTL_BASE_PIPE_CFGA + 0x0008 )
#define REG_PIPE_CFGA_DIG_CFG3   ( CTL_BASE_PIPE_CFGA + 0x000C )
#define REG_PIPE_CFGA_DIG_CFG4   ( CTL_BASE_PIPE_CFGA + 0x0010 )
#define REG_PIPE_CFGA_DIG_CFG5   ( CTL_BASE_PIPE_CFGA + 0x0014 )
#define REG_PIPE_CFGA_DIG_CFG6   ( CTL_BASE_PIPE_CFGA + 0x0018 )
#define REG_PIPE_CFGA_DIG_CFG7   ( CTL_BASE_PIPE_CFGA + 0x001C )
#define REG_PIPE_CFGA_DIG_CFG8   ( CTL_BASE_PIPE_CFGA + 0x0020 )
#define REG_PIPE_CFGA_DIG_CFG9   ( CTL_BASE_PIPE_CFGA + 0x0024 )
#define REG_PIPE_CFGA_DIG_CFG10  ( CTL_BASE_PIPE_CFGA + 0x0028 )
#define REG_PIPE_CFGA_DIG_CFG11  ( CTL_BASE_PIPE_CFGA + 0x002C )
#define REG_PIPE_CFGA_DIG_CFG12  ( CTL_BASE_PIPE_CFGA + 0x0030 )
#define REG_PIPE_CFGA_TST_CFG0   ( CTL_BASE_PIPE_CFGA + 0x0040 )
#define REG_PIPE_CFGA_TST_CFG1   ( CTL_BASE_PIPE_CFGA + 0x0044 )
#define REG_PIPE_CFGA_TST_CFG2   ( CTL_BASE_PIPE_CFGA + 0x0048 )
#define REG_PIPE_CFGA_TST_CFG3   ( CTL_BASE_PIPE_CFGA + 0x004C )
#define REG_PIPE_CFGA_TST_CFG4   ( CTL_BASE_PIPE_CFGA + 0x0050 )
#define REG_PIPE_CFGA_DBG_STS0   ( CTL_BASE_PIPE_CFGA + 0x0060 )
#define REG_PIPE_CFGA_DBG_STS1   ( CTL_BASE_PIPE_CFGA + 0x0064 )
#define REG_PIPE_CFGA_DBG_STS2   ( CTL_BASE_PIPE_CFGA + 0x0068 )
#define REG_PIPE_CFGA_DIG_STS3   ( CTL_BASE_PIPE_CFGA + 0x006C )
#define REG_PIPE_CFGA_ANA_CFG0   ( CTL_BASE_PIPE_CFGA + 0x0080 )
#define REG_PIPE_CFGA_ANA_CFG1   ( CTL_BASE_PIPE_CFGA + 0x0084 )
#define REG_PIPE_CFGA_ANA_CFG2   ( CTL_BASE_PIPE_CFGA + 0x0088 )
#define REG_PIPE_CFGA_ANA_CFG3   ( CTL_BASE_PIPE_CFGA + 0x008C )
#define REG_PIPE_CFGA_ANA_CFG4   ( CTL_BASE_PIPE_CFGA + 0x0090 )
#define REG_PIPE_CFGA_ANA_CFG5   ( CTL_BASE_PIPE_CFGA + 0x0094 )
#define REG_PIPE_CFGA_ANA_CFG6   ( CTL_BASE_PIPE_CFGA + 0x0098 )
#define REG_PIPE_CFGA_ANA_CFG7   ( CTL_BASE_PIPE_CFGA + 0x009C )
#define REG_PIPE_CFGA_ANA_CFG8   ( CTL_BASE_PIPE_CFGA + 0x00A0 )
#define REG_PIPE_CFGA_ANA_CFG9   ( CTL_BASE_PIPE_CFGA + 0x00A4 )
#define REG_PIPE_CFGA_ANA_CFG10  ( CTL_BASE_PIPE_CFGA + 0x00A8 )
#define REG_PIPE_CFGA_ANA_CFG11  ( CTL_BASE_PIPE_CFGA + 0x00AC )
#define REG_PIPE_CFGA_ANA_CFG12  ( CTL_BASE_PIPE_CFGA + 0x00B0 )
#define REG_PIPE_CFGA_ANA_CFG13  ( CTL_BASE_PIPE_CFGA + 0x00B4 )
#define REG_PIPE_CFGA_ANA_CFG14  ( CTL_BASE_PIPE_CFGA + 0x00B8 )

/* REG_PIPE_CFGA_DIG_CFG0 */

#define BIT_PIPE_CFGA_DIG_CFG0_CFG_SRSTN_ANA                  BIT(17)
#define BIT_PIPE_CFGA_DIG_CFG0_CFG_SRSTN_PMCLK                BIT(16)
#define BIT_PIPE_CFGA_DIG_CFG0_CFG_SRSTN_MTCLK                BIT(15)
#define BIT_PIPE_CFGA_DIG_CFG0_CFG_SRSTN_RXCLK                BIT(14)
#define BIT_PIPE_CFGA_DIG_CFG0_CFG_SRSTN_DPCLK                BIT(13)
#define BIT_PIPE_CFGA_DIG_CFG0_CFG_SRSTN_REFCLK               BIT(12)
#define BIT_PIPE_CFGA_DIG_CFG0_CFG_RXLOCK_IGN                 BIT(8)
#define BIT_PIPE_CFGA_DIG_CFG0_CFG_REFCLK_26M                 BIT(5)
#define BIT_PIPE_CFGA_DIG_CFG0_CFG_MTCLK_INV                  BIT(3)
#define BIT_PIPE_CFGA_DIG_CFG0_CFG_RXCLK_INV                  BIT(2)
#define BIT_PIPE_CFGA_DIG_CFG0_CFG_DPCLK_INV                  BIT(1)

/* REG_PIPE_CFGA_DIG_CFG1 */

#define BIT_PIPE_CFGA_DIG_CFG1_CFG_PM_ENTRY_CNT(x)            (((x) & 0x3) << 12)
#define BIT_PIPE_CFGA_DIG_CFG1_CFG_PM_SYNC_CNT(x)             (((x) & 0xF) << 8)
#define BIT_PIPE_CFGA_DIG_CFG1_CFG_PM_PSUB_WAIT_CM            BIT(6)
#define BIT_PIPE_CFGA_DIG_CFG1_CFG_PM_FORCE                   BIT(5)
#define BIT_PIPE_CFGA_DIG_CFG1_CFG_PM_TDR_EN                  BIT(4)
#define BIT_PIPE_CFGA_DIG_CFG1_CFG_PM_BEACON_EN               BIT(3)
#define BIT_PIPE_CFGA_DIG_CFG1_CFG_PM_LPBK_EN                 BIT(2)
#define BIT_PIPE_CFGA_DIG_CFG1_CFG_PM_TXDATA_EN               BIT(1)
#define BIT_PIPE_CFGA_DIG_CFG1_CFG_PM_PCLK_ON                 BIT(0)

/* REG_PIPE_CFGA_DIG_CFG2 */

#define BIT_PIPE_CFGA_DIG_CFG2_CFG_CDR_LOCK_IGN               BIT(20)
#define BIT_PIPE_CFGA_DIG_CFG2_CFG_CDR_LOCK_NUM(x)            (((x) & 0x7) << 17)
#define BIT_PIPE_CFGA_DIG_CFG2_CFG_RXVALID_DLY(x)             (((x) & 0xF) << 12)
#define BIT_PIPE_CFGA_DIG_CFG2_CFG_BEACON_PER(x)              (((x) & 0x3) << 4)
#define BIT_PIPE_CFGA_DIG_CFG2_CFG_RXDATA_SWAP                BIT(1)
#define BIT_PIPE_CFGA_DIG_CFG2_CFG_TXDATA_SWAP                BIT(0)

/* REG_PIPE_CFGA_DIG_CFG3 */

#define BIT_PIPE_CFGA_DIG_CFG3_CFG_BIST_STATUS_MASK(x)        (((x) & 0x3F) << 24)
#define BIT_PIPE_CFGA_DIG_CFG3_CFG_BIST_STATE_PRE(x)          (((x) & 0xF) << 20)
#define BIT_PIPE_CFGA_DIG_CFG3_CFG_BIST_STATE_CUR(x)          (((x) & 0xF) << 16)
#define BIT_PIPE_CFGA_DIG_CFG3_CFG_BIST_STATUS(x)             (((x) & 0x3) << 8)
#define BIT_PIPE_CFGA_DIG_CFG3_CFG_BIST_EN                    BIT(4)
#define BIT_PIPE_CFGA_DIG_CFG3_CFG_ALP_SRC(x)                 (((x) & 0x3) << 2)
#define BIT_PIPE_CFGA_DIG_CFG3_CFG_DLP_SRC(x)                 (((x) & 0x3))

/* REG_PIPE_CFGA_DIG_CFG4 */

#define BIT_PIPE_CFGA_DIG_CFG4_CFG_DBG_BNUM(x)                (((x) & 0xF) << 20)
#define BIT_PIPE_CFGA_DIG_CFG4_CFG_DBG_PNUM(x)                (((x) & 0xF) << 16)
#define BIT_PIPE_CFGA_DIG_CFG4_CFG_DBG_TNUM(x)                (((x) & 0xF) << 12)
#define BIT_PIPE_CFGA_DIG_CFG4_CFG_DBG_PER1(x)                (((x) & 0xF) << 8)
#define BIT_PIPE_CFGA_DIG_CFG4_CFG_DBG_PER0(x)                (((x) & 0xF) << 4)
#define BIT_PIPE_CFGA_DIG_CFG4_CFG_DBG_DTYPE(x)               (((x) & 0x3) << 2)
#define BIT_PIPE_CFGA_DIG_CFG4_CFG_DBG_10B                    BIT(1)
#define BIT_PIPE_CFGA_DIG_CFG4_CFG_DBG_EN                     BIT(0)

/* REG_PIPE_CFGA_DIG_CFG5 */

#define BIT_PIPE_CFGA_DIG_CFG5_CFG_DBG_SYM0(x)                (((x) & 0xFFFFFFFF))

/* REG_PIPE_CFGA_DIG_CFG6 */

#define BIT_PIPE_CFGA_DIG_CFG6_CFG_DBG_SYM1(x)                (((x) & 0xFFFFFFFF))

/* REG_PIPE_CFGA_DIG_CFG7 */

#define BIT_PIPE_CFGA_DIG_CFG7_CFG_PRBS_SEED(x)               (((x) & 0x7FFFFFFF))

/* REG_PIPE_CFGA_DIG_CFG8 */

#define BIT_PIPE_CFGA_DIG_CFG8_CFG_PU_CNT_MPLL(x)             (((x) & 0x7) << 24)
#define BIT_PIPE_CFGA_DIG_CFG8_CFG_PU_CNT_RX_LOS(x)           (((x) & 0xF) << 16)
#define BIT_PIPE_CFGA_DIG_CFG8_CFG_PU_CNT_TX(x)               (((x) & 0xF) << 12)
#define BIT_PIPE_CFGA_DIG_CFG8_CFG_PU_CNT_TDR_CM(x)           (((x) & 0x3) << 10)
#define BIT_PIPE_CFGA_DIG_CFG8_CFG_PU_CNT_TX_CM(x)            (((x) & 0x3) << 8)
#define BIT_PIPE_CFGA_DIG_CFG8_CFG_PU_CNT_TDR(x)              (((x) & 0x3) << 2)
#define BIT_PIPE_CFGA_DIG_CFG8_CFG_DO_CNT_RATE(x)             (((x) & 0x3))

/* REG_PIPE_CFGA_DIG_CFG9 */

#define BIT_PIPE_CFGA_DIG_CFG9_CFG_CNT_DPRX_ERR(x)            (((x) & 0xFF) << 16)
#define BIT_PIPE_CFGA_DIG_CFG9_CFG_CNT_DPRX_TOT(x)            (((x) & 0xFFF))

/* REG_PIPE_CFGA_DIG_CFG10 */

#define BIT_PIPE_CFGA_DIG_CFG10_CFG_CNT_TEST_ERR(x)           (((x) & 0xFF) << 16)
#define BIT_PIPE_CFGA_DIG_CFG10_CFG_CNT_TEST_TOT(x)           (((x) & 0xFFF))

/* REG_PIPE_CFGA_DIG_CFG11 */

#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_TXINTF_SEL           BIT(31)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_TXDEEMPH(x)          (((x) & 0x3) << 21)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_TXDEEMPH_OVRD        BIT(20)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_MACPCLKREQ(x)        (((x) & 0x3) << 18)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_MACPCLKREQ_OVRD      BIT(17)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_POWERDOWN(x)         (((x) & 0x3) << 15)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_POWERDOWN_OVRD       BIT(14)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_RXEIDLEDISABLE       BIT(13)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_RXEIDLEDISABLE_OVRD  BIT(12)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_COMMONDISABLE        BIT(11)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_COMMONDISABLE_OVRD   BIT(10)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_TXDETECTRX           BIT(9)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_TXDETECTRX_OVRD      BIT(8)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_TXELECIDLE           BIT(7)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_TXELECIDLE_OVRD      BIT(6)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_RXPOLARITY           BIT(5)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_RXPOLARITY_OVRD      BIT(4)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_TXCOMPLIANCE         BIT(3)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_TXCOMPLIANCE_OVRD    BIT(2)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_RATE                 BIT(1)
#define BIT_PIPE_CFGA_DIG_CFG11_CFG_PIPE_RATE_OVRD            BIT(0)

/* REG_PIPE_CFGA_DIG_CFG12 */

#define BIT_PIPE_CFGA_DIG_CFG12_CFG_SAL_UNLOCK_BC(x)          (((x) & 0xF) << 28)
#define BIT_PIPE_CFGA_DIG_CFG12_CFG_SAL_UNLOCK_BS(x)          (((x) & 0xF) << 24)
#define BIT_PIPE_CFGA_DIG_CFG12_CFG_SAL_UNLOCK_GC(x)          (((x) & 0xF) << 20)
#define BIT_PIPE_CFGA_DIG_CFG12_CFG_SAL_UNLOCK_GS(x)          (((x) & 0xF) << 16)
#define BIT_PIPE_CFGA_DIG_CFG12_CFG_SAL_LOCK_BC(x)            (((x) & 0xF) << 12)
#define BIT_PIPE_CFGA_DIG_CFG12_CFG_SAL_LOCK_BS(x)            (((x) & 0xF) << 8)
#define BIT_PIPE_CFGA_DIG_CFG12_CFG_SAL_LOCK_GC(x)            (((x) & 0xF) << 4)
#define BIT_PIPE_CFGA_DIG_CFG12_CFG_SAL_LOCK_GS(x)            (((x) & 0xF))

/* REG_PIPE_CFGA_TST_CFG0 */

#define BIT_PIPE_CFGA_TST_CFG0_CFG_TRIG_SOFT                  BIT(20)
#define BIT_PIPE_CFGA_TST_CFG0_CFG_TRIG_PM_STATE(x)           (((x) & 0xF) << 16)
#define BIT_PIPE_CFGA_TST_CFG0_CFG_TOUT3_SEL(x)               (((x) & 0xF) << 12)
#define BIT_PIPE_CFGA_TST_CFG0_CFG_TOUT2_SEL(x)               (((x) & 0xF) << 8)
#define BIT_PIPE_CFGA_TST_CFG0_CFG_TOUT1_SEL(x)               (((x) & 0xF) << 4)
#define BIT_PIPE_CFGA_TST_CFG0_CFG_TOUT0_SEL(x)               (((x) & 0xF))

/* REG_PIPE_CFGA_TST_CFG1 */

#define BIT_PIPE_CFGA_TST_CFG1_CFG_PLL_BIST_EXP_CNT(x)        (((x) & 0xFFFF) << 16)
#define BIT_PIPE_CFGA_TST_CFG1_CFG_PLL_BIST_REF_CNT(x)        (((x) & 0x3FFF))

/* REG_PIPE_CFGA_TST_CFG2 */

#define BIT_PIPE_CFGA_TST_CFG2_CFG_PLL_AUTO_BIST              BIT(5)
#define BIT_PIPE_CFGA_TST_CFG2_CFG_PLL_BIST_EN                BIT(4)
#define BIT_PIPE_CFGA_TST_CFG2_CFG_PLL_BIST_DELTA_CNT(x)      (((x) & 0xF))

/* REG_PIPE_CFGA_TST_CFG3 */

#define BIT_PIPE_CFGA_TST_CFG3_CFG_TEST_ADD_ERR               BIT(13)
#define BIT_PIPE_CFGA_TST_CFG3_CFG_TEST_PRBS_INV              BIT(11)
#define BIT_PIPE_CFGA_TST_CFG3_CFG_TEST_PRBS_MODE(x)          (((x) & 0x7F) << 4)
#define BIT_PIPE_CFGA_TST_CFG3_CFG_TEST_START_RX              BIT(3)
#define BIT_PIPE_CFGA_TST_CFG3_CFG_TEST_START_TX              BIT(2)
#define BIT_PIPE_CFGA_TST_CFG3_CFG_TEST_SELF_TEST_MODE        BIT(1)

/* REG_PIPE_CFGA_TST_CFG4 */

#define BIT_PIPE_CFGA_TST_CFG4_CFG_DBG_SYM2(x)                (((x) & 0xFFFF))

/* REG_PIPE_CFGA_DBG_STS0 */

#define BIT_PIPE_CFGA_DBG_STS0_DBG_STATE_RX(x)                (((x) & 0x7) << 28)
#define BIT_PIPE_CFGA_DBG_STS0_DBG_STATE_BN(x)                (((x) & 0x7) << 24)
#define BIT_PIPE_CFGA_DBG_STS0_DBG_STATE_OFFK(x)              (((x) & 0x3) << 22)
#define BIT_PIPE_CFGA_DBG_STS0_DBG_STATE_TDR(x)               (((x) & 0xF) << 16)
#define BIT_PIPE_CFGA_DBG_STS0_DBG_STATE_CM(x)                (((x) & 0xF) << 12)
#define BIT_PIPE_CFGA_DBG_STS0_DBG_CDR_LOCK                   BIT(8)
#define BIT_PIPE_CFGA_DBG_STS0_DBG_BIST_STATE(x)              (((x) & 0xF) << 4)
#define BIT_PIPE_CFGA_DBG_STS0_DBG_PM_STATE(x)                (((x) & 0xF))

/* REG_PIPE_CFGA_DBG_STS1 */

#define BIT_PIPE_CFGA_DBG_STS1_DBG_TDR_PRESENT                BIT(5)
#define BIT_PIPE_CFGA_DBG_STS1_DBG_TDR_VALID                  BIT(4)
#define BIT_PIPE_CFGA_DBG_STS1_DBG_RX_LOS                     BIT(3)
#define BIT_PIPE_CFGA_DBG_STS1_DBG_RX_LOCK                    BIT(2)
#define BIT_PIPE_CFGA_DBG_STS1_DBG_PLL_LOCK                   BIT(1)
#define BIT_PIPE_CFGA_DBG_STS1_DBG_OFFK_DONE                  BIT(0)

/* REG_PIPE_CFGA_DBG_STS2 */

#define BIT_PIPE_CFGA_DBG_STS2_DBG_PLL_BIST_OK                BIT(17)
#define BIT_PIPE_CFGA_DBG_STS2_DBG_PLL_BIST_DONE              BIT(16)
#define BIT_PIPE_CFGA_DBG_STS2_DBG_PLL_BIST_CNT(x)            (((x) & 0xFFFF))

/* REG_PIPE_CFGA_DIG_STS3 */

#define BIT_PIPE_CFGA_DIG_STS3_DBG_TEST_PATTERN_LOCK          BIT(16)
#define BIT_PIPE_CFGA_DIG_STS3_DBG_TEST_ERR_CNT(x)            (((x) & 0xFFFF))

/* REG_PIPE_CFGA_ANA_CFG0 */

#define BIT_PIPE_CFGA_ANA_CFG0_CFG_TEST_IVREF_EN              BIT(31)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_FORCE_IVREF_EN             BIT(30)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_TEST_TX_BIAS_EN            BIT(29)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_FORCE_TX_BIAS_EN           BIT(28)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_TEST_TX_IDLE               BIT(27)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_FORCE_TX_IDLE              BIT(26)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_TEST_RX_LOS                BIT(25)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_FORCE_RX_LOS               BIT(24)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_TEST_BEACON_EN             BIT(23)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_FORCE_BEACON_EN            BIT(22)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_TEST_BEACON_IN             BIT(21)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_FORCE_BEACON_IN            BIT(20)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_TEST_MPLL_EN               BIT(19)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_FORCE_MPLL_EN              BIT(18)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_TEST_RATE_SEL              BIT(17)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_FORCE_RATE_SEL             BIT(16)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_TEST_PLL_PRE_LOCK          BIT(15)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_FORCE_PLL_PRE_LOCK         BIT(14)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_TEST_RX_LOS_EN             BIT(13)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_FORCE_RX_LOS_EN            BIT(12)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_TEST_TDR_CIR_EN            BIT(11)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_FORCE_TDR_CIR_EN           BIT(10)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_TEST_TDR_EN                BIT(9)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_FORCE_TDR_EN               BIT(8)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_TEST_TDR_PRESENT           BIT(7)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_FORCE_TDR_PRESENT          BIT(6)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_TEST_TX_CM_EN              BIT(5)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_FORCE_TX_CM_EN             BIT(4)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_TEST_TX_DATA_EN            BIT(3)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_FORCE_TX_DATA_EN           BIT(2)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_TEST_TX_EN                 BIT(1)
#define BIT_PIPE_CFGA_ANA_CFG0_CFG_FORCE_TX_EN                BIT(0)

/* REG_PIPE_CFGA_ANA_CFG1 */

#define BIT_PIPE_CFGA_ANA_CFG1_CFG_TEST_PLL_LATCHEN           BIT(29)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_PLL_LATCHEN          BIT(28)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_CP                   BIT(27)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_HIGHGAIN             BIT(26)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_PEAK2G5              BIT(25)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_POSTDIV_EN           BIT(24)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_PREDIV               BIT(23)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_VCO_BAND             BIT(22)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_CDR_MODE_CTRL        BIT(21)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_PI_DIV2              BIT(20)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_TEST_RX_LDO_STABLE         BIT(19)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_RX_LDO_STABLE        BIT(18)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_TEST_RX_LDO_EN             BIT(17)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_RX_LDO_EN            BIT(16)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_TEST_OFFK_RSTN             BIT(15)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_OFFK_RSTN            BIT(14)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_TEST_OFFK_EN               BIT(13)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_OFFK_EN              BIT(12)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_TEST_CDR_ACTIVE_N          BIT(11)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_CDR_ACTIVE_N         BIT(10)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_TEST_RX_DATA_EN            BIT(9)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_RX_DATA_EN           BIT(8)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_TEST_OFFK_FINISH           BIT(7)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_OFFK_FINISH          BIT(6)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_TEST_TX_SW_EN              BIT(5)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_TX_SW_EN             BIT(4)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_TEST_TX_LDO_EN             BIT(3)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_TX_LDO_EN            BIT(2)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_TEST_RXTERM_EN             BIT(1)
#define BIT_PIPE_CFGA_ANA_CFG1_CFG_FORCE_RXTERM_EN            BIT(0)

/* REG_PIPE_CFGA_ANA_CFG2 */

#define BIT_PIPE_CFGA_ANA_CFG2_CFG_TEST_DEEMPH_HALFX2         BIT(31)
#define BIT_PIPE_CFGA_ANA_CFG2_CFG_FORCE_DEEMPH_HALFX2        BIT(30)
#define BIT_PIPE_CFGA_ANA_CFG2_CFG_TEST_DEEMPH_HALFX1         BIT(29)
#define BIT_PIPE_CFGA_ANA_CFG2_CFG_FORCE_DEEMPH_HALFX1        BIT(28)
#define BIT_PIPE_CFGA_ANA_CFG2_CFG_TEST_HALF_CELLX2_EN        BIT(27)
#define BIT_PIPE_CFGA_ANA_CFG2_CFG_FORCE_HALF_CELLX2_EN       BIT(26)
#define BIT_PIPE_CFGA_ANA_CFG2_CFG_TEST_HALF_CELLX1_EN        BIT(25)
#define BIT_PIPE_CFGA_ANA_CFG2_CFG_FORCE_HALF_CELLX1_EN       BIT(24)
#define BIT_PIPE_CFGA_ANA_CFG2_CFG_FORCE_DEEMPHX2             BIT(23)
#define BIT_PIPE_CFGA_ANA_CFG2_CFG_TEST_DEEMPHX2(x)           (((x) & 0x7) << 20)
#define BIT_PIPE_CFGA_ANA_CFG2_CFG_FORCE_DEEMPHX1             BIT(19)
#define BIT_PIPE_CFGA_ANA_CFG2_CFG_TEST_DEEMPHX1(x)           (((x) & 0x7) << 16)
#define BIT_PIPE_CFGA_ANA_CFG2_CFG_FORCE_TRIM_BG              BIT(14)
#define BIT_PIPE_CFGA_ANA_CFG2_CFG_FORCE_TRIM_TXRCTL          BIT(13)
#define BIT_PIPE_CFGA_ANA_CFG2_CFG_FORCE_TRIM_RXRCTL          BIT(12)
#define BIT_PIPE_CFGA_ANA_CFG2_CFG_TRIM_BG(x)                 (((x) & 0xF) << 8)
#define BIT_PIPE_CFGA_ANA_CFG2_CFG_TRIM_TXRCTL(x)             (((x) & 0xF) << 4)
#define BIT_PIPE_CFGA_ANA_CFG2_CFG_TRIM_RXRCTL(x)             (((x) & 0xF))

/* REG_PIPE_CFGA_ANA_CFG3 */

#define BIT_PIPE_CFGA_ANA_CFG3_CFG_TEST_TXSWING               BIT(29)
#define BIT_PIPE_CFGA_ANA_CFG3_CFG_FORCE_TXSWING              BIT(28)
#define BIT_PIPE_CFGA_ANA_CFG3_CFG_FORCE_TXRCTLX2             BIT(27)
#define BIT_PIPE_CFGA_ANA_CFG3_CFG_TEST_TXRCTLX2(x)           (((x) & 0x7) << 24)
#define BIT_PIPE_CFGA_ANA_CFG3_CFG_FORCE_TXRCTLX1             BIT(23)
#define BIT_PIPE_CFGA_ANA_CFG3_CFG_TEST_TXRCTLX1(x)           (((x) & 0x7) << 20)
#define BIT_PIPE_CFGA_ANA_CFG3_CFG_PI_DIV2                    BIT(17)
#define BIT_PIPE_CFGA_ANA_CFG3_CFG_HIGHGAIN                   BIT(16)
#define BIT_PIPE_CFGA_ANA_CFG3_CFG_BIAS_BOOST(x)              (((x) & 0xF) << 8)
#define BIT_PIPE_CFGA_ANA_CFG3_CFG_PEAK2G5                    BIT(7)
#define BIT_PIPE_CFGA_ANA_CFG3_CFG_CONSTGM_EN                 BIT(6)
#define BIT_PIPE_CFGA_ANA_CFG3_CFG_LDO_PI_REF(x)              (((x) & 0x3) << 4)
#define BIT_PIPE_CFGA_ANA_CFG3_CFG_LDO_RX_REF(x)              (((x) & 0x3) << 2)
#define BIT_PIPE_CFGA_ANA_CFG3_CFG_SQ_CTRL(x)                 (((x) & 0x3))

/* REG_PIPE_CFGA_ANA_CFG4 */

#define BIT_PIPE_CFGA_ANA_CFG4_CFG_LEQ_HOLD                   BIT(28)
#define BIT_PIPE_CFGA_ANA_CFG4_CFG_LEQ_ADAPT_EN               BIT(27)
#define BIT_PIPE_CFGA_ANA_CFG4_CFG_LEQ_MAX(x)                 (((x) & 0x1F) << 22)
#define BIT_PIPE_CFGA_ANA_CFG4_CFG_LEQ_MIN(x)                 (((x) & 0x1F) << 17)
#define BIT_PIPE_CFGA_ANA_CFG4_CFG_LEQ_INIT(x)                (((x) & 0x1F) << 12)
#define BIT_PIPE_CFGA_ANA_CFG4_CFG_LEQ_MANUAL                 BIT(11)
#define BIT_PIPE_CFGA_ANA_CFG4_CFG_LEQ_LOOP_GAIN(x)           (((x) & 0x7) << 8)
#define BIT_PIPE_CFGA_ANA_CFG4_CFG_LEQ_RATE(x)                (((x) & 0xF) << 4)
#define BIT_PIPE_CFGA_ANA_CFG4_CFG_LEQ_RATE_EN                BIT(3)
#define BIT_PIPE_CFGA_ANA_CFG4_CFG_LEQ_SLICE_EN               BIT(2)
#define BIT_PIPE_CFGA_ANA_CFG4_CFG_LEQ_ADAPT_INV              BIT(1)
#define BIT_PIPE_CFGA_ANA_CFG4_CFG_LEQ_ADAPT_RSTN             BIT(0)

/* REG_PIPE_CFGA_ANA_CFG5 */

#define BIT_PIPE_CFGA_ANA_CFG5_CFG_LEQ_OFFSET_IN(x)           (((x) & 0xF) << 24)
#define BIT_PIPE_CFGA_ANA_CFG5_CFG_READ_LEQ_LIMIT             BIT(20)
#define BIT_PIPE_CFGA_ANA_CFG5_CFG_OFFK_RATE(x)               (((x) & 0xF) << 16)
#define BIT_PIPE_CFGA_ANA_CFG5_CFG_OFFK_RATE_EN               BIT(15)
#define BIT_PIPE_CFGA_ANA_CFG5_CFG_STABLE_MODE_SLICER(x)      (((x) & 0x7) << 12)
#define BIT_PIPE_CFGA_ANA_CFG5_CFG_OFFK_INV_SLICER            BIT(11)
#define BIT_PIPE_CFGA_ANA_CFG5_CFG_STABLE_MODE_AFE(x)         (((x) & 0x7) << 8)
#define BIT_PIPE_CFGA_ANA_CFG5_CFG_OFFK_INV_AFE               BIT(7)
#define BIT_PIPE_CFGA_ANA_CFG5_CFG_OFFK_MODE                  BIT(6)
#define BIT_PIPE_CFGA_ANA_CFG5_CFG_OFFK_BIAS_HALF             BIT(5)
#define BIT_PIPE_CFGA_ANA_CFG5_CFG_LEQ_INIT_G1(x)             (((x) & 0x1F))

/* REG_PIPE_CFGA_ANA_CFG6 */

#define BIT_PIPE_CFGA_ANA_CFG6_CFG_OFFK_FINISH                BIT(28)
#define BIT_PIPE_CFGA_ANA_CFG6_CFG_READ_COEF_OUT(x)           (((x) & 0xFF) << 20)
#define BIT_PIPE_CFGA_ANA_CFG6_CFG_OFFK_MANUAL_AFE            BIT(16)
#define BIT_PIPE_CFGA_ANA_CFG6_CFG_READ_COEF_SEL(x)           (((x) & 0xFF) << 8)
#define BIT_PIPE_CFGA_ANA_CFG6_CFG_OFFK_INIT_AFE(x)           (((x) & 0xFF))

/* REG_PIPE_CFGA_ANA_CFG7 */

#define BIT_PIPE_CFGA_ANA_CFG7_CFG_MIXER_RST                  BIT(29)
#define BIT_PIPE_CFGA_ANA_CFG7_CFG_FREQOSIN                   BIT(28)
#define BIT_PIPE_CFGA_ANA_CFG7_CFG_FREQ_INTEG_IN(x)           (((x) & 0xFF) << 20)
#define BIT_PIPE_CFGA_ANA_CFG7_CFG_FIRST_ORDER_N              BIT(19)
#define BIT_PIPE_CFGA_ANA_CFG7_CFG_FPATH_OFF                  BIT(18)
#define BIT_PIPE_CFGA_ANA_CFG7_CFG_PPM_CTRL(x)                (((x) & 0x3) << 16)
#define BIT_PIPE_CFGA_ANA_CFG7_CFG_SAT_CTRL                   BIT(15)
#define BIT_PIPE_CFGA_ANA_CFG7_CFG_FGAINC(x)                  (((x) & 0x7) << 12)
#define BIT_PIPE_CFGA_ANA_CFG7_CFG_CDR_MODE_CTRL              BIT(11)
#define BIT_PIPE_CFGA_ANA_CFG7_CFG_PGAINC(x)                  (((x) & 0x7) << 8)
#define BIT_PIPE_CFGA_ANA_CFG7_CFG_PI_MANUAL_EN               BIT(7)
#define BIT_PIPE_CFGA_ANA_CFG7_CFG_PI_MANUAL(x)               (((x) & 0x7F))

/* REG_PIPE_CFGA_ANA_CFG8 */

#define BIT_PIPE_CFGA_ANA_CFG8_CFG_STEP3_CFG(x)               (((x) & 0xFF) << 24)
#define BIT_PIPE_CFGA_ANA_CFG8_CFG_STEP2_CFG(x)               (((x) & 0xFF) << 16)
#define BIT_PIPE_CFGA_ANA_CFG8_CFG_STEP1_CFG(x)               (((x) & 0xFF) << 8)
#define BIT_PIPE_CFGA_ANA_CFG8_CFG_CDR_SCENARIO(x)            (((x) & 0x3) << 6)
#define BIT_PIPE_CFGA_ANA_CFG8_CFG_CDR_JUMP_STEP              BIT(5)
#define BIT_PIPE_CFGA_ANA_CFG8_CFG_CDR_JUMP_INIT              BIT(4)
#define BIT_PIPE_CFGA_ANA_CFG8_CFG_CDR_JUMP_VTH(x)            (((x) & 0x3) << 2)
#define BIT_PIPE_CFGA_ANA_CFG8_CFG_CDR_JUMP_CASE              BIT(1)
#define BIT_PIPE_CFGA_ANA_CFG8_CFG_CDR_MONITOR_BYPASS         BIT(0)

/* REG_PIPE_CFGA_ANA_CFG9 */

#define BIT_PIPE_CFGA_ANA_CFG9_CFG_STEP2_CYCLE(x)             (((x) & 0xFFFF) << 16)
#define BIT_PIPE_CFGA_ANA_CFG9_CFG_STEP1_CYCLE(x)             (((x) & 0xFFFF))

/* REG_PIPE_CFGA_ANA_CFG10 */

#define BIT_PIPE_CFGA_ANA_CFG10_CFG_STEP3_CFG_G1(x)           (((x) & 0xFF) << 24)
#define BIT_PIPE_CFGA_ANA_CFG10_CFG_STEP2_CFG_G1(x)           (((x) & 0xFF) << 16)
#define BIT_PIPE_CFGA_ANA_CFG10_CFG_STEP1_CFG_G1(x)           (((x) & 0xFF) << 8)
#define BIT_PIPE_CFGA_ANA_CFG10_CFG_HIGHGAIN_G1               BIT(6)
#define BIT_PIPE_CFGA_ANA_CFG10_CFG_PI_DIV2_G1                BIT(5)
#define BIT_PIPE_CFGA_ANA_CFG10_CFG_CDR_MODE_CTRL_G1          BIT(4)
#define BIT_PIPE_CFGA_ANA_CFG10_CFG_VCO_BAND_G1               BIT(3)
#define BIT_PIPE_CFGA_ANA_CFG10_CFG_PREDIV_G1                 BIT(2)
#define BIT_PIPE_CFGA_ANA_CFG10_CFG_POSTDIV_EN_G1             BIT(1)
#define BIT_PIPE_CFGA_ANA_CFG10_CFG_PEAK2G5_G1                BIT(0)

/* REG_PIPE_CFGA_ANA_CFG11 */

#define BIT_PIPE_CFGA_ANA_CFG11_CFG_STEP3_CFG_G1_ONLY(x)      (((x) & 0xFF) << 24)
#define BIT_PIPE_CFGA_ANA_CFG11_CFG_STEP2_CFG_G1_ONLY(x)      (((x) & 0xFF) << 16)
#define BIT_PIPE_CFGA_ANA_CFG11_CFG_STEP1_CFG_G1_ONLY(x)      (((x) & 0xFF) << 8)
#define BIT_PIPE_CFGA_ANA_CFG11_CFG_HIGHGAIN_G1_ONLY          BIT(6)
#define BIT_PIPE_CFGA_ANA_CFG11_CFG_PI_DIV2_G1_ONLY           BIT(5)
#define BIT_PIPE_CFGA_ANA_CFG11_CFG_CDR_MODE_CTRL_G1_ONLY     BIT(4)
#define BIT_PIPE_CFGA_ANA_CFG11_CFG_VCO_BAND_G1_ONLY          BIT(3)
#define BIT_PIPE_CFGA_ANA_CFG11_CFG_PREDIV_G1_ONLY            BIT(2)
#define BIT_PIPE_CFGA_ANA_CFG11_CFG_POSTDIV_EN_G1_ONLY        BIT(1)
#define BIT_PIPE_CFGA_ANA_CFG11_CFG_PEAK2G5_G1_ONLY           BIT(0)

/* REG_PIPE_CFGA_ANA_CFG12 */

#define BIT_PIPE_CFGA_ANA_CFG12_CFG_LDO_0P9_REF_SEL           BIT(10)
#define BIT_PIPE_CFGA_ANA_CFG12_CFG_LDO_0P9_REF(x)            (((x) & 0x3) << 8)
#define BIT_PIPE_CFGA_ANA_CFG12_CFG_TXLDOCK_FILTER(x)         (((x) & 0x3) << 6)
#define BIT_PIPE_CFGA_ANA_CFG12_CFG_CK_PATH_CTRL              BIT(5)
#define BIT_PIPE_CFGA_ANA_CFG12_CFG_VCMHIZ_SEL                BIT(4)
#define BIT_PIPE_CFGA_ANA_CFG12_CFG_VCMZ_SEL                  BIT(3)
#define BIT_PIPE_CFGA_ANA_CFG12_CFG_VCM_HOLD_CTRL             BIT(2)
#define BIT_PIPE_CFGA_ANA_CFG12_CFG_TDR_REF(x)                (((x) & 0x3))

/* REG_PIPE_CFGA_ANA_CFG13 */

#define BIT_PIPE_CFGA_ANA_CFG13_CFG_G1_ONLY                   BIT(28)
#define BIT_PIPE_CFGA_ANA_CFG13_CFG_CP_G1_ONLY(x)             (((x) & 0x3) << 26)
#define BIT_PIPE_CFGA_ANA_CFG13_CFG_CP_G1(x)                  (((x) & 0x3) << 24)
#define BIT_PIPE_CFGA_ANA_CFG13_CFG_FORCE_REFCLK_EN           BIT(23)
#define BIT_PIPE_CFGA_ANA_CFG13_CFG_REFCLK_SINGLEIN           BIT(22)
#define BIT_PIPE_CFGA_ANA_CFG13_CFG_REFCLK_26M_SEL            BIT(21)
#define BIT_PIPE_CFGA_ANA_CFG13_CFG_LDO_PLL_VCO_BYPASS        BIT(20)
#define BIT_PIPE_CFGA_ANA_CFG13_CFG_LDO_PLL_VCO(x)            (((x) & 0x3) << 18)
#define BIT_PIPE_CFGA_ANA_CFG13_CFG_DIV_S                     BIT(17)
#define BIT_PIPE_CFGA_ANA_CFG13_CFG_POSTDIV_EN                BIT(16)
#define BIT_PIPE_CFGA_ANA_CFG13_CFG_PREDIV                    BIT(15)
#define BIT_PIPE_CFGA_ANA_CFG13_CFG_NS(x)                     (((x) & 0x7F) << 8)
#define BIT_PIPE_CFGA_ANA_CFG13_CFG_LPF(x)                    (((x) & 0xF) << 4)
#define BIT_PIPE_CFGA_ANA_CFG13_CFG_CP(x)                     (((x) & 0x3) << 2)
#define BIT_PIPE_CFGA_ANA_CFG13_CFG_VCO_BAND                  BIT(1)
#define BIT_PIPE_CFGA_ANA_CFG13_CFG_REFCLK_SEL                BIT(0)

/* REG_PIPE_CFGA_ANA_CFG14 */

#define BIT_PIPE_CFGA_ANA_CFG14_CFG_MISC_OUT(x)               (((x) & 0xF) << 4)
#define BIT_PIPE_CFGA_ANA_CFG14_CFG_MISC_IN(x)                (((x) & 0xF))


#endif /* PIPE_CFGA_H */


