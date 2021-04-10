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


#ifndef ANLG_PHY_PCIE3_H
#define ANLG_PHY_PCIE3_H

#define CTL_BASE_ANLG_PHY_PCIE3 0x32438000


#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_COMMON_CTRL        ( CTL_BASE_ANLG_PHY_PCIE3 + 0x0000 )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_APB_MPLL_PMU_CTRL  ( CTL_BASE_ANLG_PHY_PCIE3 + 0x0004 )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PIPE_SRAM_CTRL     ( CTL_BASE_ANLG_PHY_PCIE3 + 0x0008 )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL0    ( CTL_BASE_ANLG_PHY_PCIE3 + 0x000C )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL1_2_CTRL   ( CTL_BASE_ANLG_PHY_PCIE3 + 0x0010 )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL00   ( CTL_BASE_ANLG_PHY_PCIE3 + 0x0014 )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL1    ( CTL_BASE_ANLG_PHY_PCIE3 + 0x0018 )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL2    ( CTL_BASE_ANLG_PHY_PCIE3 + 0x001C )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL3    ( CTL_BASE_ANLG_PHY_PCIE3 + 0x0020 )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL5    ( CTL_BASE_ANLG_PHY_PCIE3 + 0x0024 )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL6    ( CTL_BASE_ANLG_PHY_PCIE3 + 0x0028 )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL7    ( CTL_BASE_ANLG_PHY_PCIE3 + 0x002C )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL12   ( CTL_BASE_ANLG_PHY_PCIE3 + 0x0030 )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL13   ( CTL_BASE_ANLG_PHY_PCIE3 + 0x0034 )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL14   ( CTL_BASE_ANLG_PHY_PCIE3 + 0x0038 )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL15   ( CTL_BASE_ANLG_PHY_PCIE3 + 0x003C )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL16   ( CTL_BASE_ANLG_PHY_PCIE3 + 0x0040 )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL17   ( CTL_BASE_ANLG_PHY_PCIE3 + 0x0044 )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL18   ( CTL_BASE_ANLG_PHY_PCIE3 + 0x0048 )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL19   ( CTL_BASE_ANLG_PHY_PCIE3 + 0x004C )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL20   ( CTL_BASE_ANLG_PHY_PCIE3 + 0x0050 )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL21   ( CTL_BASE_ANLG_PHY_PCIE3 + 0x0054 )
#define REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_COMMON_CONFIG      ( CTL_BASE_ANLG_PHY_PCIE3 + 0x0058 )

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_COMMON_CTRL */

#define BIT_ANLG_PHY_PCIE3_UPCS_PIPE_CONFIG(x)              (((x) & 0xFFFF) << 13)
#define BIT_ANLG_PHY_PCIE3_PHY_RTUNE_REQ                    BIT(12)
#define BIT_ANLG_PHY_PCIE3_PHY_RTUNE_ACK                    BIT(11)
#define BIT_ANLG_PHY_PCIE3_PHY_RX0_TERM_ACDC                BIT(10)
#define BIT_ANLG_PHY_PCIE3_PHY_EXT_CTRL_SEL                 BIT(9)
#define BIT_ANLG_PHY_PCIE3_PHY0_TEST_FLYOVER_EN             BIT(8)
#define BIT_ANLG_PHY_PCIE3_PHY0_TEST_STOP_CLK_EN            BIT(7)
#define BIT_ANLG_PHY_PCIE3_PHY0_TEST_TX_REF_CLK_EN          BIT(6)
#define BIT_ANLG_PHY_PCIE3_PHY_TEST_BURNIN                  BIT(5)
#define BIT_ANLG_PHY_PCIE3_PHY_TEST_POWERDOWN               BIT(4)
#define BIT_ANLG_PHY_PCIE3_PHY_LANE0_RX2TX_PAR_LB_EN        BIT(3)
#define BIT_ANLG_PHY_PCIE3_EXT_PCLK_REQ                     BIT(2)
#define BIT_ANLG_PHY_PCIE3_PHY0_REF_REPEAT_CLK_EN           BIT(1)
#define BIT_ANLG_PHY_PCIE3_PHY_REF_USE_PAD                  BIT(0)

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_APB_MPLL_PMU_CTRL */

#define BIT_ANLG_PHY_PCIE3_PG_MODE_EN                       BIT(14)
#define BIT_ANLG_PHY_PCIE3_PHY0_ANA_PWR_EN_REG              BIT(13)
#define BIT_ANLG_PHY_PCIE3_PHY0_PMA_PWR_STABLE_REG_CONTROL  BIT(12)
#define BIT_ANLG_PHY_PCIE3_PHY0_PCS_PWR_EN                  BIT(11)
#define BIT_ANLG_PHY_PCIE3_PHY0_PCS_PWR_STABEL              BIT(10)
#define BIT_ANLG_PHY_PCIE3_PHY_LANE0_POWER_PRESENT          BIT(9)
#define BIT_ANLG_PHY_PCIE3_UPCS_PWR_EN                      BIT(8)
#define BIT_ANLG_PHY_PCIE3_UPCS_PWR_STABLE                  BIT(7)
#define BIT_ANLG_PHY_PCIE3_PHY0_MPLLB_SSC_EN                BIT(6)
#define BIT_ANLG_PHY_PCIE3_PHY0_MPLLB_STATE                 BIT(5)
#define BIT_ANLG_PHY_PCIE3_PHY0_MPLLB_FORCE_EN              BIT(4)
#define BIT_ANLG_PHY_PCIE3_PHY0_MPLLA_SSC_EN                BIT(3)
#define BIT_ANLG_PHY_PCIE3_PHY0_MPLLA_STATE                 BIT(2)
#define BIT_ANLG_PHY_PCIE3_PHY0_MPLLA_FORCE_EN              BIT(1)
#define BIT_ANLG_PHY_PCIE3_PHY0_CR_PARA_SEL                 BIT(0)

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PIPE_SRAM_CTRL */

#define BIT_ANLG_PHY_PCIE3_PHY0_SRAM_INIT_DONE              BIT(18)
#define BIT_ANLG_PHY_PCIE3_PHY0_SRAM_EXT_LD_DONE            BIT(17)
#define BIT_ANLG_PHY_PCIE3_PHY0_SRAM_BYPASS                 BIT(16)
#define BIT_ANLG_PHY_PCIE3_PIPE_TX0_ONES_ZEROS              BIT(15)
#define BIT_ANLG_PHY_PCIE3_PIPE_TX0_PATTERN(x)              (((x) & 0x3) << 13)
#define BIT_ANLG_PHY_PCIE3_PIPE_RX0_TERMINATION             BIT(12)
#define BIT_ANLG_PHY_PCIE3_PIPE_RX0_SRIS_MODE_EN            BIT(11)
#define BIT_ANLG_PHY_PCIE3_PIPE_RX0_EQ_TRAINING             BIT(10)
#define BIT_ANLG_PHY_PCIE3_PIPE_LANE0_TX2RX_LOOPBK(x)       (((x) & 0x3) << 8)
#define BIT_ANLG_PHY_PCIE3_PIPE_LANE0_PROTOCOL(x)           (((x) & 0x3) << 6)
#define BIT_ANLG_PHY_PCIE3_PIPE_LANE0_PHY_SRC_SEL(x)        (((x) & 0x3) << 4)
#define BIT_ANLG_PHY_PCIE3_PIPE_LANE0_LINK_NUM(x)           (((x) & 0xF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL0 */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_TX_IBOOST_LVL(x)   (((x) & 0xF) << 23)
#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_TX_EQ_MAIN_G1(x)   (((x) & 0x1F) << 18)
#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_TX_EQ_MAIN_G2(x)   (((x) & 0x1F) << 13)
#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_TX_EQ_MAIN_G3(x)   (((x) & 0x1F) << 8)
#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_TX_EQ_POST_G1(x)   (((x) & 0xF) << 4)
#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_TX_EQ_POST_G2(x)   (((x) & 0xF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL1_2_CTRL */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL1_EXT_REG(x)             (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_PCIE3_PROTOCOL2_EXT_REG(x)             (((x) & 0xFFFF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL00 */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG(x)             (((x) & 0xFFFFFFF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL1 */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG1(x)            (((x) & 0x3FFFFF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL2 */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG2(x)            (((x) & 0xFFFFFFF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL3 */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG3(x)            (((x) & 0x7FFFFFF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL5 */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG5(x)            (((x) & 0x3FFFFF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL6 */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG6(x)            (((x) & 0x7FFFFFFF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL7 */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG11(x)           (((x) & 0xF) << 23)
#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG10(x)           (((x) & 0xF) << 19)
#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG9(x)            (((x) & 0xF) << 15)
#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG8(x)            (((x) & 0xF) << 11)
#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG7(x)            (((x) & 0x7FF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL12 */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG12(x)           (((x) & 0xFFFFFFFF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL13 */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG13(x)           (((x) & 0xFFFF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL14 */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG14(x)           (((x) & 0xFFFFFFFF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL15 */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG15(x)           (((x) & 0xFFFF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL16 */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG16(x)           (((x) & 0x7FFFFFF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL17 */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG17(x)           (((x) & 0x7FFFFFF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL18 */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG18(x)           (((x) & 0x7FFFFFF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL19 */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG19(x)           (((x) & 0x7FFFFFF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL20 */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG20(x)           (((x) & 0x7FFFFFF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_PROTOCOL0_CTRL21 */

#define BIT_ANLG_PHY_PCIE3_PROTOCOL0_EXT_REG21(x)           (((x) & 0xFF))

/* REG_ANLG_PHY_PCIE3_ANALOG_PCIE3_PHY_COMMON_CONFIG */

#define BIT_ANLG_PHY_PCIE3_PIPE_RX0_EBUFF_LOCATION(x)       (((x) & 0x1FF) << 1)
#define BIT_ANLG_PHY_PCIE3_PIPE_RX0_ALIGN_DETECT            BIT(0)


#endif /* ANLG_PHY_PCIE3_H */


