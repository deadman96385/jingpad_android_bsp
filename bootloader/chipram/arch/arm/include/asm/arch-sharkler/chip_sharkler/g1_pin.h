/*
 * Copyright (C) 2019 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2019-01-07 15:09:47
 *
 */


#ifndef G1_PIN_H
#define G1_PIN_H

#define CTL_BASE_G1_PIN 0x402A0000


#define REG_G1_PIN_IIS1CLK          ( CTL_BASE_G1_PIN + 0x0420 )
#define REG_G1_PIN_IIS1DI           ( CTL_BASE_G1_PIN + 0x0424 )
#define REG_G1_PIN_IIS1DO           ( CTL_BASE_G1_PIN + 0x0428 )
#define REG_G1_PIN_IIS1LRCK         ( CTL_BASE_G1_PIN + 0x042C )
#define REG_G1_PIN_SCL2             ( CTL_BASE_G1_PIN + 0x0430 )
#define REG_G1_PIN_SDA2             ( CTL_BASE_G1_PIN + 0x0434 )
#define REG_G1_PIN_CLK_AUX0         ( CTL_BASE_G1_PIN + 0x0438 )
#define REG_G1_PIN_T_DIG            ( CTL_BASE_G1_PIN + 0x043C )
#define REG_G1_PIN_GNSS_LNA_EN      ( CTL_BASE_G1_PIN + 0x0440 )
#define REG_G1_PIN_EXTINT0          ( CTL_BASE_G1_PIN + 0x0444 )
#define REG_G1_PIN_EXTINT1          ( CTL_BASE_G1_PIN + 0x0448 )
#define REG_G1_PIN_SCL3             ( CTL_BASE_G1_PIN + 0x044C )
#define REG_G1_PIN_SDA3             ( CTL_BASE_G1_PIN + 0x0450 )
#define REG_G1_PIN_SCL0             ( CTL_BASE_G1_PIN + 0x0454 )
#define REG_G1_PIN_SDA0             ( CTL_BASE_G1_PIN + 0x0458 )
#define REG_G1_PIN_SCL1             ( CTL_BASE_G1_PIN + 0x045C )
#define REG_G1_PIN_SDA1             ( CTL_BASE_G1_PIN + 0x0460 )
#define REG_G1_PIN_CMPD2            ( CTL_BASE_G1_PIN + 0x0464 )
#define REG_G1_PIN_CMRST2           ( CTL_BASE_G1_PIN + 0x0468 )
#define REG_G1_PIN_CMMCLK0          ( CTL_BASE_G1_PIN + 0x046C )
#define REG_G1_PIN_CMRST0           ( CTL_BASE_G1_PIN + 0x0470 )
#define REG_G1_PIN_CMPD0            ( CTL_BASE_G1_PIN + 0x0474 )
#define REG_G1_PIN_CMMCLK1          ( CTL_BASE_G1_PIN + 0x0478 )
#define REG_G1_PIN_CMRST1           ( CTL_BASE_G1_PIN + 0x047C )
#define REG_G1_PIN_CMPD1            ( CTL_BASE_G1_PIN + 0x0480 )

/* REG_G1_PIN_IIS1CLK */

#define BIT_G1_PIN_IIS1CLK_FUN_DRV(x)      (((x) & 0x3) << 19)
#define BIT_G1_PIN_IIS1CLK_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G1_PIN_IIS1CLK_FUN_WPUS        BIT(12)
#define BIT_G1_PIN_IIS1CLK_FUN_SE          BIT(11)
#define BIT_G1_PIN_IIS1CLK_DUMY            BIT(10)
#define BIT_G1_PIN_IIS1CLK_FUN_WPU         BIT(7)
#define BIT_G1_PIN_IIS1CLK_FUN_WPDO        BIT(6)
#define BIT_G1_PIN_IIS1CLK_SLP_WPU         BIT(3)
#define BIT_G1_PIN_IIS1CLK_SLP_WPDO        BIT(2)
#define BIT_G1_PIN_IIS1CLK_SLP_IE          BIT(1)
#define BIT_G1_PIN_IIS1CLK_SLP_OE          BIT(0)

/* REG_G1_PIN_IIS1DI */

#define BIT_G1_PIN_IIS1DI_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G1_PIN_IIS1DI_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G1_PIN_IIS1DI_FUN_WPUS         BIT(12)
#define BIT_G1_PIN_IIS1DI_FUN_SE           BIT(11)
#define BIT_G1_PIN_IIS1DI_DUMY             BIT(10)
#define BIT_G1_PIN_IIS1DI_FUN_WPU          BIT(7)
#define BIT_G1_PIN_IIS1DI_FUN_WPDO         BIT(6)
#define BIT_G1_PIN_IIS1DI_SLP_WPU          BIT(3)
#define BIT_G1_PIN_IIS1DI_SLP_WPDO         BIT(2)
#define BIT_G1_PIN_IIS1DI_SLP_IE           BIT(1)
#define BIT_G1_PIN_IIS1DI_SLP_OE           BIT(0)

/* REG_G1_PIN_IIS1DO */

#define BIT_G1_PIN_IIS1DO_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G1_PIN_IIS1DO_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G1_PIN_IIS1DO_FUN_WPUS         BIT(12)
#define BIT_G1_PIN_IIS1DO_FUN_SE           BIT(11)
#define BIT_G1_PIN_IIS1DO_DUMY             BIT(10)
#define BIT_G1_PIN_IIS1DO_FUN_WPU          BIT(7)
#define BIT_G1_PIN_IIS1DO_FUN_WPDO         BIT(6)
#define BIT_G1_PIN_IIS1DO_SLP_WPU          BIT(3)
#define BIT_G1_PIN_IIS1DO_SLP_WPDO         BIT(2)
#define BIT_G1_PIN_IIS1DO_SLP_IE           BIT(1)
#define BIT_G1_PIN_IIS1DO_SLP_OE           BIT(0)

/* REG_G1_PIN_IIS1LRCK */

#define BIT_G1_PIN_IIS1LRCK_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G1_PIN_IIS1LRCK_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G1_PIN_IIS1LRCK_FUN_WPUS       BIT(12)
#define BIT_G1_PIN_IIS1LRCK_FUN_SE         BIT(11)
#define BIT_G1_PIN_IIS1LRCK_DUMY           BIT(10)
#define BIT_G1_PIN_IIS1LRCK_FUN_WPU        BIT(7)
#define BIT_G1_PIN_IIS1LRCK_FUN_WPDO       BIT(6)
#define BIT_G1_PIN_IIS1LRCK_SLP_WPU        BIT(3)
#define BIT_G1_PIN_IIS1LRCK_SLP_WPDO       BIT(2)
#define BIT_G1_PIN_IIS1LRCK_SLP_IE         BIT(1)
#define BIT_G1_PIN_IIS1LRCK_SLP_OE         BIT(0)

/* REG_G1_PIN_SCL2 */

#define BIT_G1_PIN_SCL2_FUN_DRV(x)         (((x) & 0x3) << 19)
#define BIT_G1_PIN_SCL2_DSLP_EN(x)         (((x) & 0x1F) << 13)
#define BIT_G1_PIN_SCL2_FUN_WPUS           BIT(12)
#define BIT_G1_PIN_SCL2_FUN_SE             BIT(11)
#define BIT_G1_PIN_SCL2_DUMY               BIT(10)
#define BIT_G1_PIN_SCL2_FUN_WPU            BIT(7)
#define BIT_G1_PIN_SCL2_FUN_WPDO           BIT(6)
#define BIT_G1_PIN_SCL2_SLP_WPU            BIT(3)
#define BIT_G1_PIN_SCL2_SLP_WPDO           BIT(2)
#define BIT_G1_PIN_SCL2_SLP_IE             BIT(1)
#define BIT_G1_PIN_SCL2_SLP_OE             BIT(0)

/* REG_G1_PIN_SDA2 */

#define BIT_G1_PIN_SDA2_FUN_DRV(x)         (((x) & 0x3) << 19)
#define BIT_G1_PIN_SDA2_DSLP_EN(x)         (((x) & 0x1F) << 13)
#define BIT_G1_PIN_SDA2_FUN_WPUS           BIT(12)
#define BIT_G1_PIN_SDA2_FUN_SE             BIT(11)
#define BIT_G1_PIN_SDA2_DUMY               BIT(10)
#define BIT_G1_PIN_SDA2_FUN_WPU            BIT(7)
#define BIT_G1_PIN_SDA2_FUN_WPDO           BIT(6)
#define BIT_G1_PIN_SDA2_SLP_WPU            BIT(3)
#define BIT_G1_PIN_SDA2_SLP_WPDO           BIT(2)
#define BIT_G1_PIN_SDA2_SLP_IE             BIT(1)
#define BIT_G1_PIN_SDA2_SLP_OE             BIT(0)

/* REG_G1_PIN_CLK_AUX0 */

#define BIT_G1_PIN_CLK_AUX0_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G1_PIN_CLK_AUX0_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G1_PIN_CLK_AUX0_FUN_WPUS       BIT(12)
#define BIT_G1_PIN_CLK_AUX0_FUN_SE         BIT(11)
#define BIT_G1_PIN_CLK_AUX0_DUMY           BIT(10)
#define BIT_G1_PIN_CLK_AUX0_FUN_WPU        BIT(7)
#define BIT_G1_PIN_CLK_AUX0_FUN_WPDO       BIT(6)
#define BIT_G1_PIN_CLK_AUX0_SLP_WPU        BIT(3)
#define BIT_G1_PIN_CLK_AUX0_SLP_WPDO       BIT(2)
#define BIT_G1_PIN_CLK_AUX0_SLP_IE         BIT(1)
#define BIT_G1_PIN_CLK_AUX0_SLP_OE         BIT(0)

/* REG_G1_PIN_T_DIG */

#define BIT_G1_PIN_T_DIG_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G1_PIN_T_DIG_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G1_PIN_T_DIG_FUN_WPUS          BIT(12)
#define BIT_G1_PIN_T_DIG_FUN_SE            BIT(11)
#define BIT_G1_PIN_T_DIG_DUMY              BIT(10)
#define BIT_G1_PIN_T_DIG_FUN_WPU           BIT(7)
#define BIT_G1_PIN_T_DIG_FUN_WPDO          BIT(6)
#define BIT_G1_PIN_T_DIG_SLP_WPU           BIT(3)
#define BIT_G1_PIN_T_DIG_SLP_WPDO          BIT(2)
#define BIT_G1_PIN_T_DIG_SLP_IE            BIT(1)
#define BIT_G1_PIN_T_DIG_SLP_OE            BIT(0)

/* REG_G1_PIN_GNSS_LNA_EN */

#define BIT_G1_PIN_GNSS_LNA_EN_FUN_DRV(x)  (((x) & 0x3) << 19)
#define BIT_G1_PIN_GNSS_LNA_EN_DSLP_EN(x)  (((x) & 0x1F) << 13)
#define BIT_G1_PIN_GNSS_LNA_EN_FUN_WPUS    BIT(12)
#define BIT_G1_PIN_GNSS_LNA_EN_FUN_SE      BIT(11)
#define BIT_G1_PIN_GNSS_LNA_EN_DUMY        BIT(10)
#define BIT_G1_PIN_GNSS_LNA_EN_FUN_WPU     BIT(7)
#define BIT_G1_PIN_GNSS_LNA_EN_FUN_WPDO    BIT(6)
#define BIT_G1_PIN_GNSS_LNA_EN_SLP_WPU     BIT(3)
#define BIT_G1_PIN_GNSS_LNA_EN_SLP_WPDO    BIT(2)
#define BIT_G1_PIN_GNSS_LNA_EN_SLP_IE      BIT(1)
#define BIT_G1_PIN_GNSS_LNA_EN_SLP_OE      BIT(0)

/* REG_G1_PIN_EXTINT0 */

#define BIT_G1_PIN_EXTINT0_FUN_DRV(x)      (((x) & 0x3) << 19)
#define BIT_G1_PIN_EXTINT0_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G1_PIN_EXTINT0_FUN_WPUS        BIT(12)
#define BIT_G1_PIN_EXTINT0_FUN_SE          BIT(11)
#define BIT_G1_PIN_EXTINT0_DUMY            BIT(10)
#define BIT_G1_PIN_EXTINT0_FUN_WPU         BIT(7)
#define BIT_G1_PIN_EXTINT0_FUN_WPDO        BIT(6)
#define BIT_G1_PIN_EXTINT0_SLP_WPU         BIT(3)
#define BIT_G1_PIN_EXTINT0_SLP_WPDO        BIT(2)
#define BIT_G1_PIN_EXTINT0_SLP_IE          BIT(1)
#define BIT_G1_PIN_EXTINT0_SLP_OE          BIT(0)

/* REG_G1_PIN_EXTINT1 */

#define BIT_G1_PIN_EXTINT1_FUN_DRV(x)      (((x) & 0x3) << 19)
#define BIT_G1_PIN_EXTINT1_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G1_PIN_EXTINT1_FUN_WPUS        BIT(12)
#define BIT_G1_PIN_EXTINT1_FUN_SE          BIT(11)
#define BIT_G1_PIN_EXTINT1_DUMY            BIT(10)
#define BIT_G1_PIN_EXTINT1_FUN_WPU         BIT(7)
#define BIT_G1_PIN_EXTINT1_FUN_WPDO        BIT(6)
#define BIT_G1_PIN_EXTINT1_SLP_WPU         BIT(3)
#define BIT_G1_PIN_EXTINT1_SLP_WPDO        BIT(2)
#define BIT_G1_PIN_EXTINT1_SLP_IE          BIT(1)
#define BIT_G1_PIN_EXTINT1_SLP_OE          BIT(0)

/* REG_G1_PIN_SCL3 */

#define BIT_G1_PIN_SCL3_FUN_DRV(x)         (((x) & 0x3) << 19)
#define BIT_G1_PIN_SCL3_DSLP_EN(x)         (((x) & 0x1F) << 13)
#define BIT_G1_PIN_SCL3_FUN_WPUS           BIT(12)
#define BIT_G1_PIN_SCL3_FUN_SE             BIT(11)
#define BIT_G1_PIN_SCL3_DUMY               BIT(10)
#define BIT_G1_PIN_SCL3_FUN_WPU            BIT(7)
#define BIT_G1_PIN_SCL3_FUN_WPDO           BIT(6)
#define BIT_G1_PIN_SCL3_SLP_WPU            BIT(3)
#define BIT_G1_PIN_SCL3_SLP_WPDO           BIT(2)
#define BIT_G1_PIN_SCL3_SLP_IE             BIT(1)
#define BIT_G1_PIN_SCL3_SLP_OE             BIT(0)

/* REG_G1_PIN_SDA3 */

#define BIT_G1_PIN_SDA3_FUN_DRV(x)         (((x) & 0x3) << 19)
#define BIT_G1_PIN_SDA3_DSLP_EN(x)         (((x) & 0x1F) << 13)
#define BIT_G1_PIN_SDA3_FUN_WPUS           BIT(12)
#define BIT_G1_PIN_SDA3_FUN_SE             BIT(11)
#define BIT_G1_PIN_SDA3_DUMY               BIT(10)
#define BIT_G1_PIN_SDA3_FUN_WPU            BIT(7)
#define BIT_G1_PIN_SDA3_FUN_WPDO           BIT(6)
#define BIT_G1_PIN_SDA3_SLP_WPU            BIT(3)
#define BIT_G1_PIN_SDA3_SLP_WPDO           BIT(2)
#define BIT_G1_PIN_SDA3_SLP_IE             BIT(1)
#define BIT_G1_PIN_SDA3_SLP_OE             BIT(0)

/* REG_G1_PIN_SCL0 */

#define BIT_G1_PIN_SCL0_FUN_DRV(x)         (((x) & 0x3) << 19)
#define BIT_G1_PIN_SCL0_DSLP_EN(x)         (((x) & 0x1F) << 13)
#define BIT_G1_PIN_SCL0_FUN_WPUS           BIT(12)
#define BIT_G1_PIN_SCL0_FUN_SE             BIT(11)
#define BIT_G1_PIN_SCL0_DUMY               BIT(10)
#define BIT_G1_PIN_SCL0_FUN_WPU            BIT(7)
#define BIT_G1_PIN_SCL0_FUN_WPDO           BIT(6)
#define BIT_G1_PIN_SCL0_SLP_WPU            BIT(3)
#define BIT_G1_PIN_SCL0_SLP_WPDO           BIT(2)
#define BIT_G1_PIN_SCL0_SLP_IE             BIT(1)
#define BIT_G1_PIN_SCL0_SLP_OE             BIT(0)

/* REG_G1_PIN_SDA0 */

#define BIT_G1_PIN_SDA0_FUN_DRV(x)         (((x) & 0x3) << 19)
#define BIT_G1_PIN_SDA0_DSLP_EN(x)         (((x) & 0x1F) << 13)
#define BIT_G1_PIN_SDA0_FUN_WPUS           BIT(12)
#define BIT_G1_PIN_SDA0_FUN_SE             BIT(11)
#define BIT_G1_PIN_SDA0_DUMY               BIT(10)
#define BIT_G1_PIN_SDA0_FUN_WPU            BIT(7)
#define BIT_G1_PIN_SDA0_FUN_WPDO           BIT(6)
#define BIT_G1_PIN_SDA0_SLP_WPU            BIT(3)
#define BIT_G1_PIN_SDA0_SLP_WPDO           BIT(2)
#define BIT_G1_PIN_SDA0_SLP_IE             BIT(1)
#define BIT_G1_PIN_SDA0_SLP_OE             BIT(0)

/* REG_G1_PIN_SCL1 */

#define BIT_G1_PIN_SCL1_FUN_DRV(x)         (((x) & 0x3) << 19)
#define BIT_G1_PIN_SCL1_DSLP_EN(x)         (((x) & 0x1F) << 13)
#define BIT_G1_PIN_SCL1_FUN_WPUS           BIT(12)
#define BIT_G1_PIN_SCL1_FUN_SE             BIT(11)
#define BIT_G1_PIN_SCL1_DUMY               BIT(10)
#define BIT_G1_PIN_SCL1_FUN_WPU            BIT(7)
#define BIT_G1_PIN_SCL1_FUN_WPDO           BIT(6)
#define BIT_G1_PIN_SCL1_SLP_WPU            BIT(3)
#define BIT_G1_PIN_SCL1_SLP_WPDO           BIT(2)
#define BIT_G1_PIN_SCL1_SLP_IE             BIT(1)
#define BIT_G1_PIN_SCL1_SLP_OE             BIT(0)

/* REG_G1_PIN_SDA1 */

#define BIT_G1_PIN_SDA1_FUN_DRV(x)         (((x) & 0x3) << 19)
#define BIT_G1_PIN_SDA1_DSLP_EN(x)         (((x) & 0x1F) << 13)
#define BIT_G1_PIN_SDA1_FUN_WPUS           BIT(12)
#define BIT_G1_PIN_SDA1_FUN_SE             BIT(11)
#define BIT_G1_PIN_SDA1_DUMY               BIT(10)
#define BIT_G1_PIN_SDA1_FUN_WPU            BIT(7)
#define BIT_G1_PIN_SDA1_FUN_WPDO           BIT(6)
#define BIT_G1_PIN_SDA1_SLP_WPU            BIT(3)
#define BIT_G1_PIN_SDA1_SLP_WPDO           BIT(2)
#define BIT_G1_PIN_SDA1_SLP_IE             BIT(1)
#define BIT_G1_PIN_SDA1_SLP_OE             BIT(0)

/* REG_G1_PIN_CMPD2 */

#define BIT_G1_PIN_CMPD2_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G1_PIN_CMPD2_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G1_PIN_CMPD2_FUN_WPUS          BIT(12)
#define BIT_G1_PIN_CMPD2_FUN_SE            BIT(11)
#define BIT_G1_PIN_CMPD2_DUMY              BIT(10)
#define BIT_G1_PIN_CMPD2_FUN_WPU           BIT(7)
#define BIT_G1_PIN_CMPD2_FUN_WPDO          BIT(6)
#define BIT_G1_PIN_CMPD2_SLP_WPU           BIT(3)
#define BIT_G1_PIN_CMPD2_SLP_WPDO          BIT(2)
#define BIT_G1_PIN_CMPD2_SLP_IE            BIT(1)
#define BIT_G1_PIN_CMPD2_SLP_OE            BIT(0)

/* REG_G1_PIN_CMRST2 */

#define BIT_G1_PIN_CMRST2_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G1_PIN_CMRST2_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G1_PIN_CMRST2_FUN_WPUS         BIT(12)
#define BIT_G1_PIN_CMRST2_FUN_SE           BIT(11)
#define BIT_G1_PIN_CMRST2_DUMY             BIT(10)
#define BIT_G1_PIN_CMRST2_FUN_WPU          BIT(7)
#define BIT_G1_PIN_CMRST2_FUN_WPDO         BIT(6)
#define BIT_G1_PIN_CMRST2_SLP_WPU          BIT(3)
#define BIT_G1_PIN_CMRST2_SLP_WPDO         BIT(2)
#define BIT_G1_PIN_CMRST2_SLP_IE           BIT(1)
#define BIT_G1_PIN_CMRST2_SLP_OE           BIT(0)

/* REG_G1_PIN_CMMCLK0 */

#define BIT_G1_PIN_CMMCLK0_FUN_DRV(x)      (((x) & 0x3) << 19)
#define BIT_G1_PIN_CMMCLK0_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G1_PIN_CMMCLK0_FUN_WPUS        BIT(12)
#define BIT_G1_PIN_CMMCLK0_FUN_SE          BIT(11)
#define BIT_G1_PIN_CMMCLK0_DUMY            BIT(10)
#define BIT_G1_PIN_CMMCLK0_FUN_WPU         BIT(7)
#define BIT_G1_PIN_CMMCLK0_FUN_WPDO        BIT(6)
#define BIT_G1_PIN_CMMCLK0_SLP_WPU         BIT(3)
#define BIT_G1_PIN_CMMCLK0_SLP_WPDO        BIT(2)
#define BIT_G1_PIN_CMMCLK0_SLP_IE          BIT(1)
#define BIT_G1_PIN_CMMCLK0_SLP_OE          BIT(0)

/* REG_G1_PIN_CMRST0 */

#define BIT_G1_PIN_CMRST0_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G1_PIN_CMRST0_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G1_PIN_CMRST0_FUN_WPUS         BIT(12)
#define BIT_G1_PIN_CMRST0_FUN_SE           BIT(11)
#define BIT_G1_PIN_CMRST0_DUMY             BIT(10)
#define BIT_G1_PIN_CMRST0_FUN_WPU          BIT(7)
#define BIT_G1_PIN_CMRST0_FUN_WPDO         BIT(6)
#define BIT_G1_PIN_CMRST0_SLP_WPU          BIT(3)
#define BIT_G1_PIN_CMRST0_SLP_WPDO         BIT(2)
#define BIT_G1_PIN_CMRST0_SLP_IE           BIT(1)
#define BIT_G1_PIN_CMRST0_SLP_OE           BIT(0)

/* REG_G1_PIN_CMPD0 */

#define BIT_G1_PIN_CMPD0_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G1_PIN_CMPD0_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G1_PIN_CMPD0_FUN_WPUS          BIT(12)
#define BIT_G1_PIN_CMPD0_FUN_SE            BIT(11)
#define BIT_G1_PIN_CMPD0_DUMY              BIT(10)
#define BIT_G1_PIN_CMPD0_FUN_WPU           BIT(7)
#define BIT_G1_PIN_CMPD0_FUN_WPDO          BIT(6)
#define BIT_G1_PIN_CMPD0_SLP_WPU           BIT(3)
#define BIT_G1_PIN_CMPD0_SLP_WPDO          BIT(2)
#define BIT_G1_PIN_CMPD0_SLP_IE            BIT(1)
#define BIT_G1_PIN_CMPD0_SLP_OE            BIT(0)

/* REG_G1_PIN_CMMCLK1 */

#define BIT_G1_PIN_CMMCLK1_FUN_DRV(x)      (((x) & 0x3) << 19)
#define BIT_G1_PIN_CMMCLK1_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G1_PIN_CMMCLK1_FUN_WPUS        BIT(12)
#define BIT_G1_PIN_CMMCLK1_FUN_SE          BIT(11)
#define BIT_G1_PIN_CMMCLK1_DUMY            BIT(10)
#define BIT_G1_PIN_CMMCLK1_FUN_WPU         BIT(7)
#define BIT_G1_PIN_CMMCLK1_FUN_WPDO        BIT(6)
#define BIT_G1_PIN_CMMCLK1_SLP_WPU         BIT(3)
#define BIT_G1_PIN_CMMCLK1_SLP_WPDO        BIT(2)
#define BIT_G1_PIN_CMMCLK1_SLP_IE          BIT(1)
#define BIT_G1_PIN_CMMCLK1_SLP_OE          BIT(0)

/* REG_G1_PIN_CMRST1 */

#define BIT_G1_PIN_CMRST1_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G1_PIN_CMRST1_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G1_PIN_CMRST1_FUN_WPUS         BIT(12)
#define BIT_G1_PIN_CMRST1_FUN_SE           BIT(11)
#define BIT_G1_PIN_CMRST1_DUMY             BIT(10)
#define BIT_G1_PIN_CMRST1_FUN_WPU          BIT(7)
#define BIT_G1_PIN_CMRST1_FUN_WPDO         BIT(6)
#define BIT_G1_PIN_CMRST1_SLP_WPU          BIT(3)
#define BIT_G1_PIN_CMRST1_SLP_WPDO         BIT(2)
#define BIT_G1_PIN_CMRST1_SLP_IE           BIT(1)
#define BIT_G1_PIN_CMRST1_SLP_OE           BIT(0)

/* REG_G1_PIN_CMPD1 */

#define BIT_G1_PIN_CMPD1_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G1_PIN_CMPD1_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G1_PIN_CMPD1_FUN_WPUS          BIT(12)
#define BIT_G1_PIN_CMPD1_FUN_SE            BIT(11)
#define BIT_G1_PIN_CMPD1_DUMY              BIT(10)
#define BIT_G1_PIN_CMPD1_FUN_WPU           BIT(7)
#define BIT_G1_PIN_CMPD1_FUN_WPDO          BIT(6)
#define BIT_G1_PIN_CMPD1_SLP_WPU           BIT(3)
#define BIT_G1_PIN_CMPD1_SLP_WPDO          BIT(2)
#define BIT_G1_PIN_CMPD1_SLP_IE            BIT(1)
#define BIT_G1_PIN_CMPD1_SLP_OE            BIT(0)


#endif /* G1_PIN_H */


