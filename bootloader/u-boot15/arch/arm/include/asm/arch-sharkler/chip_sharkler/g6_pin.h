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


#ifndef G6_PIN_H
#define G6_PIN_H

#define CTL_BASE_G6_PIN 0x402A0000


#define REG_G6_PIN_SIMCLK0              ( CTL_BASE_G6_PIN + 0x0574 )
#define REG_G6_PIN_SIMDA0               ( CTL_BASE_G6_PIN + 0x0578 )
#define REG_G6_PIN_SIMRST0              ( CTL_BASE_G6_PIN + 0x057C )
#define REG_G6_PIN_SIMCLK1              ( CTL_BASE_G6_PIN + 0x0580 )
#define REG_G6_PIN_SIMDA1               ( CTL_BASE_G6_PIN + 0x0584 )
#define REG_G6_PIN_SIMRST1              ( CTL_BASE_G6_PIN + 0x0588 )
#define REG_G6_PIN_SIMCLK2              ( CTL_BASE_G6_PIN + 0x058C )
#define REG_G6_PIN_SIMDA2               ( CTL_BASE_G6_PIN + 0x0590 )
#define REG_G6_PIN_SIMRST2              ( CTL_BASE_G6_PIN + 0x0594 )
#define REG_G6_PIN_KEYOUT0              ( CTL_BASE_G6_PIN + 0x0598 )
#define REG_G6_PIN_KEYOUT1              ( CTL_BASE_G6_PIN + 0x059C )
#define REG_G6_PIN_KEYOUT2              ( CTL_BASE_G6_PIN + 0x05A0 )
#define REG_G6_PIN_KEYIN0               ( CTL_BASE_G6_PIN + 0x05A4 )
#define REG_G6_PIN_KEYIN1               ( CTL_BASE_G6_PIN + 0x05A8 )
#define REG_G6_PIN_KEYIN2               ( CTL_BASE_G6_PIN + 0x05AC )
#define REG_G6_PIN_RFFE0_SCK            ( CTL_BASE_G6_PIN + 0x05B0 )
#define REG_G6_PIN_RFFE0_SDA            ( CTL_BASE_G6_PIN + 0x05B4 )
#define REG_G6_PIN_RFCTL0               ( CTL_BASE_G6_PIN + 0x05B8 )
#define REG_G6_PIN_RFCTL1               ( CTL_BASE_G6_PIN + 0x05BC )
#define REG_G6_PIN_RFCTL2               ( CTL_BASE_G6_PIN + 0x05C0 )
#define REG_G6_PIN_RFCTL3               ( CTL_BASE_G6_PIN + 0x05C4 )
#define REG_G6_PIN_RFCTL4               ( CTL_BASE_G6_PIN + 0x05C8 )
#define REG_G6_PIN_RFCTL5               ( CTL_BASE_G6_PIN + 0x05CC )
#define REG_G6_PIN_RFCTL6               ( CTL_BASE_G6_PIN + 0x05D0 )
#define REG_G6_PIN_RFCTL7               ( CTL_BASE_G6_PIN + 0x05D4 )
#define REG_G6_PIN_RFCTL8               ( CTL_BASE_G6_PIN + 0x05D8 )
#define REG_G6_PIN_RFCTL9               ( CTL_BASE_G6_PIN + 0x05DC )
#define REG_G6_PIN_RFCTL10              ( CTL_BASE_G6_PIN + 0x05E0 )
#define REG_G6_PIN_RFCTL11              ( CTL_BASE_G6_PIN + 0x05E4 )
#define REG_G6_PIN_RFCTL12              ( CTL_BASE_G6_PIN + 0x05E8 )
#define REG_G6_PIN_RFCTL13              ( CTL_BASE_G6_PIN + 0x05EC )
#define REG_G6_PIN_RFCTL14              ( CTL_BASE_G6_PIN + 0x05F0 )
#define REG_G6_PIN_RFCTL15              ( CTL_BASE_G6_PIN + 0x05F4 )
#define REG_G6_PIN_RFCTL16              ( CTL_BASE_G6_PIN + 0x05F8 )
#define REG_G6_PIN_RFCTL17              ( CTL_BASE_G6_PIN + 0x05FC )
#define REG_G6_PIN_RFCTL18              ( CTL_BASE_G6_PIN + 0x0600 )
#define REG_G6_PIN_RFCTL19              ( CTL_BASE_G6_PIN + 0x0604 )
#define REG_G6_PIN_RFSDA0               ( CTL_BASE_G6_PIN + 0x0608 )
#define REG_G6_PIN_RFSCK0               ( CTL_BASE_G6_PIN + 0x060C )
#define REG_G6_PIN_RFSEN0               ( CTL_BASE_G6_PIN + 0x0610 )
#define REG_G6_PIN_LVDS0_ADC_ON      ( CTL_BASE_G6_PIN + 0x0614 )
#define REG_G6_PIN_LVDS0_DAC_ON      ( CTL_BASE_G6_PIN + 0x0618 )
#define REG_G6_PIN_SPI2_CSN             ( CTL_BASE_G6_PIN + 0x061C )
#define REG_G6_PIN_SPI2_DO              ( CTL_BASE_G6_PIN + 0x0620 )
#define REG_G6_PIN_SPI2_DI              ( CTL_BASE_G6_PIN + 0x0624 )
#define REG_G6_PIN_SPI2_CLK             ( CTL_BASE_G6_PIN + 0x0628 )
#define REG_G6_PIN_SPI0_CSN             ( CTL_BASE_G6_PIN + 0x062C )
#define REG_G6_PIN_SPI0_DO              ( CTL_BASE_G6_PIN + 0x0630 )
#define REG_G6_PIN_SPI0_DI              ( CTL_BASE_G6_PIN + 0x0634 )
#define REG_G6_PIN_SPI0_CLK             ( CTL_BASE_G6_PIN + 0x0638 )
#define REG_G6_PIN_DTDO_LTE             ( CTL_BASE_G6_PIN + 0x063C )
#define REG_G6_PIN_DTDI_LTE             ( CTL_BASE_G6_PIN + 0x0640 )
#define REG_G6_PIN_DTCK_LTE             ( CTL_BASE_G6_PIN + 0x0644 )
#define REG_G6_PIN_DTMS_LTE             ( CTL_BASE_G6_PIN + 0x0648 )
#define REG_G6_PIN_DRTCK_LTE            ( CTL_BASE_G6_PIN + 0x064C )
#define REG_G6_PIN_MTCK_ARM             ( CTL_BASE_G6_PIN + 0x0650 )
#define REG_G6_PIN_MTMS_ARM             ( CTL_BASE_G6_PIN + 0x0654 )

/* REG_G6_PIN_SIMCLK0 */

#define BIT_G6_PIN_SIMCLK0_FUN_DRV(x)       (((x) & 0xF) << 19)
#define BIT_G6_PIN_SIMCLK0_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_SIMCLK0_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_SIMCLK0_FUN_SE           BIT(11)
#define BIT_G6_PIN_SIMCLK0_MS               BIT(10)
#define BIT_G6_PIN_SIMCLK0_MSEN             BIT(9)
#define BIT_G6_PIN_SIMCLK0_MSOUT            BIT(8)
#define BIT_G6_PIN_SIMCLK0_FUN_WPU          BIT(7)
#define BIT_G6_PIN_SIMCLK0_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_SIMCLK0_SLP_WPU          BIT(3)
#define BIT_G6_PIN_SIMCLK0_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_SIMCLK0_SLP_IE           BIT(1)
#define BIT_G6_PIN_SIMCLK0_SLP_OE           BIT(0)

/* REG_G6_PIN_SIMDA0 */

#define BIT_G6_PIN_SIMDA0_FUN_DRV(x)        (((x) & 0xF) << 19)
#define BIT_G6_PIN_SIMDA0_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_SIMDA0_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_SIMDA0_FUN_SE            BIT(11)
#define BIT_G6_PIN_SIMDA0_MS                BIT(10)
#define BIT_G6_PIN_SIMDA0_MSEN              BIT(9)
#define BIT_G6_PIN_SIMDA0_MSOUT             BIT(8)
#define BIT_G6_PIN_SIMDA0_FUN_WPU           BIT(7)
#define BIT_G6_PIN_SIMDA0_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_SIMDA0_SLP_WPU           BIT(3)
#define BIT_G6_PIN_SIMDA0_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_SIMDA0_SLP_IE            BIT(1)
#define BIT_G6_PIN_SIMDA0_SLP_OE            BIT(0)

/* REG_G6_PIN_SIMRST0 */

#define BIT_G6_PIN_SIMRST0_FUN_DRV(x)       (((x) & 0xF) << 19)
#define BIT_G6_PIN_SIMRST0_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_SIMRST0_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_SIMRST0_FUN_SE           BIT(11)
#define BIT_G6_PIN_SIMRST0_MS               BIT(10)
#define BIT_G6_PIN_SIMRST0_MSEN             BIT(9)
#define BIT_G6_PIN_SIMRST0_MSOUT            BIT(8)
#define BIT_G6_PIN_SIMRST0_FUN_WPU          BIT(7)
#define BIT_G6_PIN_SIMRST0_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_SIMRST0_SLP_WPU          BIT(3)
#define BIT_G6_PIN_SIMRST0_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_SIMRST0_SLP_IE           BIT(1)
#define BIT_G6_PIN_SIMRST0_SLP_OE           BIT(0)

/* REG_G6_PIN_SIMCLK1 */

#define BIT_G6_PIN_SIMCLK1_FUN_DRV(x)       (((x) & 0xF) << 19)
#define BIT_G6_PIN_SIMCLK1_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_SIMCLK1_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_SIMCLK1_FUN_SE           BIT(11)
#define BIT_G6_PIN_SIMCLK1_MS               BIT(10)
#define BIT_G6_PIN_SIMCLK1_MSEN             BIT(9)
#define BIT_G6_PIN_SIMCLK1_MSOUT            BIT(8)
#define BIT_G6_PIN_SIMCLK1_FUN_WPU          BIT(7)
#define BIT_G6_PIN_SIMCLK1_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_SIMCLK1_SLP_WPU          BIT(3)
#define BIT_G6_PIN_SIMCLK1_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_SIMCLK1_SLP_IE           BIT(1)
#define BIT_G6_PIN_SIMCLK1_SLP_OE           BIT(0)

/* REG_G6_PIN_SIMDA1 */

#define BIT_G6_PIN_SIMDA1_FUN_DRV(x)        (((x) & 0xF) << 19)
#define BIT_G6_PIN_SIMDA1_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_SIMDA1_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_SIMDA1_FUN_SE            BIT(11)
#define BIT_G6_PIN_SIMDA1_MS                BIT(10)
#define BIT_G6_PIN_SIMDA1_MSEN              BIT(9)
#define BIT_G6_PIN_SIMDA1_MSOUT             BIT(8)
#define BIT_G6_PIN_SIMDA1_FUN_WPU           BIT(7)
#define BIT_G6_PIN_SIMDA1_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_SIMDA1_SLP_WPU           BIT(3)
#define BIT_G6_PIN_SIMDA1_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_SIMDA1_SLP_IE            BIT(1)
#define BIT_G6_PIN_SIMDA1_SLP_OE            BIT(0)

/* REG_G6_PIN_SIMRST1 */

#define BIT_G6_PIN_SIMRST1_FUN_DRV(x)       (((x) & 0xF) << 19)
#define BIT_G6_PIN_SIMRST1_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_SIMRST1_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_SIMRST1_FUN_SE           BIT(11)
#define BIT_G6_PIN_SIMRST1_MS               BIT(10)
#define BIT_G6_PIN_SIMRST1_MSEN             BIT(9)
#define BIT_G6_PIN_SIMRST1_MSOUT            BIT(8)
#define BIT_G6_PIN_SIMRST1_FUN_WPU          BIT(7)
#define BIT_G6_PIN_SIMRST1_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_SIMRST1_SLP_WPU          BIT(3)
#define BIT_G6_PIN_SIMRST1_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_SIMRST1_SLP_IE           BIT(1)
#define BIT_G6_PIN_SIMRST1_SLP_OE           BIT(0)

/* REG_G6_PIN_SIMCLK2 */

#define BIT_G6_PIN_SIMCLK2_FUN_DRV(x)       (((x) & 0xF) << 19)
#define BIT_G6_PIN_SIMCLK2_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_SIMCLK2_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_SIMCLK2_FUN_SE           BIT(11)
#define BIT_G6_PIN_SIMCLK2_MS               BIT(10)
#define BIT_G6_PIN_SIMCLK2_MSEN             BIT(9)
#define BIT_G6_PIN_SIMCLK2_MSOUT            BIT(8)
#define BIT_G6_PIN_SIMCLK2_FUN_WPU          BIT(7)
#define BIT_G6_PIN_SIMCLK2_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_SIMCLK2_SLP_WPU          BIT(3)
#define BIT_G6_PIN_SIMCLK2_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_SIMCLK2_SLP_IE           BIT(1)
#define BIT_G6_PIN_SIMCLK2_SLP_OE           BIT(0)

/* REG_G6_PIN_SIMDA2 */

#define BIT_G6_PIN_SIMDA2_FUN_DRV(x)        (((x) & 0xF) << 19)
#define BIT_G6_PIN_SIMDA2_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_SIMDA2_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_SIMDA2_FUN_SE            BIT(11)
#define BIT_G6_PIN_SIMDA2_MS                BIT(10)
#define BIT_G6_PIN_SIMDA2_MSEN              BIT(9)
#define BIT_G6_PIN_SIMDA2_MSOUT             BIT(8)
#define BIT_G6_PIN_SIMDA2_FUN_WPU           BIT(7)
#define BIT_G6_PIN_SIMDA2_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_SIMDA2_SLP_WPU           BIT(3)
#define BIT_G6_PIN_SIMDA2_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_SIMDA2_SLP_IE            BIT(1)
#define BIT_G6_PIN_SIMDA2_SLP_OE            BIT(0)

/* REG_G6_PIN_SIMRST2 */

#define BIT_G6_PIN_SIMRST2_FUN_DRV(x)       (((x) & 0xF) << 19)
#define BIT_G6_PIN_SIMRST2_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_SIMRST2_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_SIMRST2_FUN_SE           BIT(11)
#define BIT_G6_PIN_SIMRST2_MS               BIT(10)
#define BIT_G6_PIN_SIMRST2_MSEN             BIT(9)
#define BIT_G6_PIN_SIMRST2_MSOUT            BIT(8)
#define BIT_G6_PIN_SIMRST2_FUN_WPU          BIT(7)
#define BIT_G6_PIN_SIMRST2_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_SIMRST2_SLP_WPU          BIT(3)
#define BIT_G6_PIN_SIMRST2_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_SIMRST2_SLP_IE           BIT(1)
#define BIT_G6_PIN_SIMRST2_SLP_OE           BIT(0)

/* REG_G6_PIN_KEYOUT0 */

#define BIT_G6_PIN_KEYOUT0_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G6_PIN_KEYOUT0_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_KEYOUT0_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_KEYOUT0_FUN_SE           BIT(11)
#define BIT_G6_PIN_KEYOUT0_DUMY             BIT(10)
#define BIT_G6_PIN_KEYOUT0_FUN_WPU          BIT(7)
#define BIT_G6_PIN_KEYOUT0_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_KEYOUT0_SLP_WPU          BIT(3)
#define BIT_G6_PIN_KEYOUT0_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_KEYOUT0_SLP_IE           BIT(1)
#define BIT_G6_PIN_KEYOUT0_SLP_OE           BIT(0)

/* REG_G6_PIN_KEYOUT1 */

#define BIT_G6_PIN_KEYOUT1_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G6_PIN_KEYOUT1_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_KEYOUT1_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_KEYOUT1_FUN_SE           BIT(11)
#define BIT_G6_PIN_KEYOUT1_DUMY             BIT(10)
#define BIT_G6_PIN_KEYOUT1_FUN_WPU          BIT(7)
#define BIT_G6_PIN_KEYOUT1_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_KEYOUT1_SLP_WPU          BIT(3)
#define BIT_G6_PIN_KEYOUT1_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_KEYOUT1_SLP_IE           BIT(1)
#define BIT_G6_PIN_KEYOUT1_SLP_OE           BIT(0)

/* REG_G6_PIN_KEYOUT2 */

#define BIT_G6_PIN_KEYOUT2_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G6_PIN_KEYOUT2_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_KEYOUT2_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_KEYOUT2_FUN_SE           BIT(11)
#define BIT_G6_PIN_KEYOUT2_DUMY             BIT(10)
#define BIT_G6_PIN_KEYOUT2_FUN_WPU          BIT(7)
#define BIT_G6_PIN_KEYOUT2_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_KEYOUT2_SLP_WPU          BIT(3)
#define BIT_G6_PIN_KEYOUT2_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_KEYOUT2_SLP_IE           BIT(1)
#define BIT_G6_PIN_KEYOUT2_SLP_OE           BIT(0)

/* REG_G6_PIN_KEYIN0 */

#define BIT_G6_PIN_KEYIN0_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G6_PIN_KEYIN0_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_KEYIN0_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_KEYIN0_FUN_SE            BIT(11)
#define BIT_G6_PIN_KEYIN0_DUMY              BIT(10)
#define BIT_G6_PIN_KEYIN0_FUN_WPU           BIT(7)
#define BIT_G6_PIN_KEYIN0_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_KEYIN0_SLP_WPU           BIT(3)
#define BIT_G6_PIN_KEYIN0_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_KEYIN0_SLP_IE            BIT(1)
#define BIT_G6_PIN_KEYIN0_SLP_OE            BIT(0)

/* REG_G6_PIN_KEYIN1 */

#define BIT_G6_PIN_KEYIN1_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G6_PIN_KEYIN1_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_KEYIN1_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_KEYIN1_FUN_SE            BIT(11)
#define BIT_G6_PIN_KEYIN1_DUMY              BIT(10)
#define BIT_G6_PIN_KEYIN1_FUN_WPU           BIT(7)
#define BIT_G6_PIN_KEYIN1_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_KEYIN1_SLP_WPU           BIT(3)
#define BIT_G6_PIN_KEYIN1_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_KEYIN1_SLP_IE            BIT(1)
#define BIT_G6_PIN_KEYIN1_SLP_OE            BIT(0)

/* REG_G6_PIN_KEYIN2 */

#define BIT_G6_PIN_KEYIN2_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G6_PIN_KEYIN2_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_KEYIN2_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_KEYIN2_FUN_SE            BIT(11)
#define BIT_G6_PIN_KEYIN2_DUMY              BIT(10)
#define BIT_G6_PIN_KEYIN2_FUN_WPU           BIT(7)
#define BIT_G6_PIN_KEYIN2_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_KEYIN2_SLP_WPU           BIT(3)
#define BIT_G6_PIN_KEYIN2_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_KEYIN2_SLP_IE            BIT(1)
#define BIT_G6_PIN_KEYIN2_SLP_OE            BIT(0)

/* REG_G6_PIN_RFFE0_SCK */

#define BIT_G6_PIN_RFFE0_SCK_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFFE0_SCK_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFFE0_SCK_FUN_WPUS       BIT(12)
#define BIT_G6_PIN_RFFE0_SCK_FUN_SE         BIT(11)
#define BIT_G6_PIN_RFFE0_SCK_DUMY           BIT(10)
#define BIT_G6_PIN_RFFE0_SCK_FUN_WPU        BIT(7)
#define BIT_G6_PIN_RFFE0_SCK_FUN_WPDO       BIT(6)
#define BIT_G6_PIN_RFFE0_SCK_SLP_WPU        BIT(3)
#define BIT_G6_PIN_RFFE0_SCK_SLP_WPDO       BIT(2)
#define BIT_G6_PIN_RFFE0_SCK_SLP_IE         BIT(1)
#define BIT_G6_PIN_RFFE0_SCK_SLP_OE         BIT(0)

/* REG_G6_PIN_RFFE0_SDA */

#define BIT_G6_PIN_RFFE0_SDA_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFFE0_SDA_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFFE0_SDA_FUN_WPUS       BIT(12)
#define BIT_G6_PIN_RFFE0_SDA_FUN_SE         BIT(11)
#define BIT_G6_PIN_RFFE0_SDA_DUMY           BIT(10)
#define BIT_G6_PIN_RFFE0_SDA_FUN_WPU        BIT(7)
#define BIT_G6_PIN_RFFE0_SDA_FUN_WPDO       BIT(6)
#define BIT_G6_PIN_RFFE0_SDA_SLP_WPU        BIT(3)
#define BIT_G6_PIN_RFFE0_SDA_SLP_WPDO       BIT(2)
#define BIT_G6_PIN_RFFE0_SDA_SLP_IE         BIT(1)
#define BIT_G6_PIN_RFFE0_SDA_SLP_OE         BIT(0)

/* REG_G6_PIN_RFCTL0 */

#define BIT_G6_PIN_RFCTL0_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL0_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL0_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_RFCTL0_FUN_SE            BIT(11)
#define BIT_G6_PIN_RFCTL0_DUMY              BIT(10)
#define BIT_G6_PIN_RFCTL0_FUN_WPU           BIT(7)
#define BIT_G6_PIN_RFCTL0_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_RFCTL0_SLP_WPU           BIT(3)
#define BIT_G6_PIN_RFCTL0_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_RFCTL0_SLP_IE            BIT(1)
#define BIT_G6_PIN_RFCTL0_SLP_OE            BIT(0)

/* REG_G6_PIN_RFCTL1 */

#define BIT_G6_PIN_RFCTL1_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL1_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL1_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_RFCTL1_FUN_SE            BIT(11)
#define BIT_G6_PIN_RFCTL1_DUMY              BIT(10)
#define BIT_G6_PIN_RFCTL1_FUN_WPU           BIT(7)
#define BIT_G6_PIN_RFCTL1_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_RFCTL1_SLP_WPU           BIT(3)
#define BIT_G6_PIN_RFCTL1_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_RFCTL1_SLP_IE            BIT(1)
#define BIT_G6_PIN_RFCTL1_SLP_OE            BIT(0)

/* REG_G6_PIN_RFCTL2 */

#define BIT_G6_PIN_RFCTL2_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL2_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL2_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_RFCTL2_FUN_SE            BIT(11)
#define BIT_G6_PIN_RFCTL2_DUMY              BIT(10)
#define BIT_G6_PIN_RFCTL2_FUN_WPU           BIT(7)
#define BIT_G6_PIN_RFCTL2_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_RFCTL2_SLP_WPU           BIT(3)
#define BIT_G6_PIN_RFCTL2_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_RFCTL2_SLP_IE            BIT(1)
#define BIT_G6_PIN_RFCTL2_SLP_OE            BIT(0)

/* REG_G6_PIN_RFCTL3 */

#define BIT_G6_PIN_RFCTL3_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL3_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL3_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_RFCTL3_FUN_SE            BIT(11)
#define BIT_G6_PIN_RFCTL3_DUMY              BIT(10)
#define BIT_G6_PIN_RFCTL3_FUN_WPU           BIT(7)
#define BIT_G6_PIN_RFCTL3_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_RFCTL3_SLP_WPU           BIT(3)
#define BIT_G6_PIN_RFCTL3_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_RFCTL3_SLP_IE            BIT(1)
#define BIT_G6_PIN_RFCTL3_SLP_OE            BIT(0)

/* REG_G6_PIN_RFCTL4 */

#define BIT_G6_PIN_RFCTL4_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL4_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL4_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_RFCTL4_FUN_SE            BIT(11)
#define BIT_G6_PIN_RFCTL4_DUMY              BIT(10)
#define BIT_G6_PIN_RFCTL4_FUN_WPU           BIT(7)
#define BIT_G6_PIN_RFCTL4_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_RFCTL4_SLP_WPU           BIT(3)
#define BIT_G6_PIN_RFCTL4_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_RFCTL4_SLP_IE            BIT(1)
#define BIT_G6_PIN_RFCTL4_SLP_OE            BIT(0)

/* REG_G6_PIN_RFCTL5 */

#define BIT_G6_PIN_RFCTL5_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL5_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL5_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_RFCTL5_FUN_SE            BIT(11)
#define BIT_G6_PIN_RFCTL5_DUMY              BIT(10)
#define BIT_G6_PIN_RFCTL5_FUN_WPU           BIT(7)
#define BIT_G6_PIN_RFCTL5_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_RFCTL5_SLP_WPU           BIT(3)
#define BIT_G6_PIN_RFCTL5_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_RFCTL5_SLP_IE            BIT(1)
#define BIT_G6_PIN_RFCTL5_SLP_OE            BIT(0)

/* REG_G6_PIN_RFCTL6 */

#define BIT_G6_PIN_RFCTL6_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL6_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL6_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_RFCTL6_FUN_SE            BIT(11)
#define BIT_G6_PIN_RFCTL6_DUMY              BIT(10)
#define BIT_G6_PIN_RFCTL6_FUN_WPU           BIT(7)
#define BIT_G6_PIN_RFCTL6_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_RFCTL6_SLP_WPU           BIT(3)
#define BIT_G6_PIN_RFCTL6_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_RFCTL6_SLP_IE            BIT(1)
#define BIT_G6_PIN_RFCTL6_SLP_OE            BIT(0)

/* REG_G6_PIN_RFCTL7 */

#define BIT_G6_PIN_RFCTL7_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL7_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL7_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_RFCTL7_FUN_SE            BIT(11)
#define BIT_G6_PIN_RFCTL7_DUMY              BIT(10)
#define BIT_G6_PIN_RFCTL7_FUN_WPU           BIT(7)
#define BIT_G6_PIN_RFCTL7_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_RFCTL7_SLP_WPU           BIT(3)
#define BIT_G6_PIN_RFCTL7_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_RFCTL7_SLP_IE            BIT(1)
#define BIT_G6_PIN_RFCTL7_SLP_OE            BIT(0)

/* REG_G6_PIN_RFCTL8 */

#define BIT_G6_PIN_RFCTL8_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL8_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL8_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_RFCTL8_FUN_SE            BIT(11)
#define BIT_G6_PIN_RFCTL8_DUMY              BIT(10)
#define BIT_G6_PIN_RFCTL8_FUN_WPU           BIT(7)
#define BIT_G6_PIN_RFCTL8_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_RFCTL8_SLP_WPU           BIT(3)
#define BIT_G6_PIN_RFCTL8_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_RFCTL8_SLP_IE            BIT(1)
#define BIT_G6_PIN_RFCTL8_SLP_OE            BIT(0)

/* REG_G6_PIN_RFCTL9 */

#define BIT_G6_PIN_RFCTL9_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL9_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL9_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_RFCTL9_FUN_SE            BIT(11)
#define BIT_G6_PIN_RFCTL9_DUMY              BIT(10)
#define BIT_G6_PIN_RFCTL9_FUN_WPU           BIT(7)
#define BIT_G6_PIN_RFCTL9_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_RFCTL9_SLP_WPU           BIT(3)
#define BIT_G6_PIN_RFCTL9_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_RFCTL9_SLP_IE            BIT(1)
#define BIT_G6_PIN_RFCTL9_SLP_OE            BIT(0)

/* REG_G6_PIN_RFCTL10 */

#define BIT_G6_PIN_RFCTL10_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL10_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL10_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_RFCTL10_FUN_SE           BIT(11)
#define BIT_G6_PIN_RFCTL10_DUMY             BIT(10)
#define BIT_G6_PIN_RFCTL10_FUN_WPU          BIT(7)
#define BIT_G6_PIN_RFCTL10_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_RFCTL10_SLP_WPU          BIT(3)
#define BIT_G6_PIN_RFCTL10_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_RFCTL10_SLP_IE           BIT(1)
#define BIT_G6_PIN_RFCTL10_SLP_OE           BIT(0)

/* REG_G6_PIN_RFCTL11 */

#define BIT_G6_PIN_RFCTL11_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL11_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL11_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_RFCTL11_FUN_SE           BIT(11)
#define BIT_G6_PIN_RFCTL11_DUMY             BIT(10)
#define BIT_G6_PIN_RFCTL11_FUN_WPU          BIT(7)
#define BIT_G6_PIN_RFCTL11_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_RFCTL11_SLP_WPU          BIT(3)
#define BIT_G6_PIN_RFCTL11_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_RFCTL11_SLP_IE           BIT(1)
#define BIT_G6_PIN_RFCTL11_SLP_OE           BIT(0)

/* REG_G6_PIN_RFCTL12 */

#define BIT_G6_PIN_RFCTL12_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL12_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL12_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_RFCTL12_FUN_SE           BIT(11)
#define BIT_G6_PIN_RFCTL12_DUMY             BIT(10)
#define BIT_G6_PIN_RFCTL12_FUN_WPU          BIT(7)
#define BIT_G6_PIN_RFCTL12_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_RFCTL12_SLP_WPU          BIT(3)
#define BIT_G6_PIN_RFCTL12_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_RFCTL12_SLP_IE           BIT(1)
#define BIT_G6_PIN_RFCTL12_SLP_OE           BIT(0)

/* REG_G6_PIN_RFCTL13 */

#define BIT_G6_PIN_RFCTL13_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL13_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL13_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_RFCTL13_FUN_SE           BIT(11)
#define BIT_G6_PIN_RFCTL13_DUMY             BIT(10)
#define BIT_G6_PIN_RFCTL13_FUN_WPU          BIT(7)
#define BIT_G6_PIN_RFCTL13_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_RFCTL13_SLP_WPU          BIT(3)
#define BIT_G6_PIN_RFCTL13_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_RFCTL13_SLP_IE           BIT(1)
#define BIT_G6_PIN_RFCTL13_SLP_OE           BIT(0)

/* REG_G6_PIN_RFCTL14 */

#define BIT_G6_PIN_RFCTL14_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL14_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL14_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_RFCTL14_FUN_SE           BIT(11)
#define BIT_G6_PIN_RFCTL14_DUMY             BIT(10)
#define BIT_G6_PIN_RFCTL14_FUN_WPU          BIT(7)
#define BIT_G6_PIN_RFCTL14_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_RFCTL14_SLP_WPU          BIT(3)
#define BIT_G6_PIN_RFCTL14_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_RFCTL14_SLP_IE           BIT(1)
#define BIT_G6_PIN_RFCTL14_SLP_OE           BIT(0)

/* REG_G6_PIN_RFCTL15 */

#define BIT_G6_PIN_RFCTL15_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL15_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL15_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_RFCTL15_FUN_SE           BIT(11)
#define BIT_G6_PIN_RFCTL15_DUMY             BIT(10)
#define BIT_G6_PIN_RFCTL15_FUN_WPU          BIT(7)
#define BIT_G6_PIN_RFCTL15_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_RFCTL15_SLP_WPU          BIT(3)
#define BIT_G6_PIN_RFCTL15_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_RFCTL15_SLP_IE           BIT(1)
#define BIT_G6_PIN_RFCTL15_SLP_OE           BIT(0)

/* REG_G6_PIN_RFCTL16 */

#define BIT_G6_PIN_RFCTL16_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL16_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL16_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_RFCTL16_FUN_SE           BIT(11)
#define BIT_G6_PIN_RFCTL16_DUMY             BIT(10)
#define BIT_G6_PIN_RFCTL16_FUN_WPU          BIT(7)
#define BIT_G6_PIN_RFCTL16_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_RFCTL16_SLP_WPU          BIT(3)
#define BIT_G6_PIN_RFCTL16_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_RFCTL16_SLP_IE           BIT(1)
#define BIT_G6_PIN_RFCTL16_SLP_OE           BIT(0)

/* REG_G6_PIN_RFCTL17 */

#define BIT_G6_PIN_RFCTL17_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL17_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL17_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_RFCTL17_FUN_SE           BIT(11)
#define BIT_G6_PIN_RFCTL17_DUMY             BIT(10)
#define BIT_G6_PIN_RFCTL17_FUN_WPU          BIT(7)
#define BIT_G6_PIN_RFCTL17_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_RFCTL17_SLP_WPU          BIT(3)
#define BIT_G6_PIN_RFCTL17_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_RFCTL17_SLP_IE           BIT(1)
#define BIT_G6_PIN_RFCTL17_SLP_OE           BIT(0)

/* REG_G6_PIN_RFCTL18 */

#define BIT_G6_PIN_RFCTL18_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL18_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL18_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_RFCTL18_FUN_SE           BIT(11)
#define BIT_G6_PIN_RFCTL18_DUMY             BIT(10)
#define BIT_G6_PIN_RFCTL18_FUN_WPU          BIT(7)
#define BIT_G6_PIN_RFCTL18_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_RFCTL18_SLP_WPU          BIT(3)
#define BIT_G6_PIN_RFCTL18_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_RFCTL18_SLP_IE           BIT(1)
#define BIT_G6_PIN_RFCTL18_SLP_OE           BIT(0)

/* REG_G6_PIN_RFCTL19 */

#define BIT_G6_PIN_RFCTL19_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFCTL19_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFCTL19_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_RFCTL19_FUN_SE           BIT(11)
#define BIT_G6_PIN_RFCTL19_DUMY             BIT(10)
#define BIT_G6_PIN_RFCTL19_FUN_WPU          BIT(7)
#define BIT_G6_PIN_RFCTL19_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_RFCTL19_SLP_WPU          BIT(3)
#define BIT_G6_PIN_RFCTL19_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_RFCTL19_SLP_IE           BIT(1)
#define BIT_G6_PIN_RFCTL19_SLP_OE           BIT(0)

/* REG_G6_PIN_RFSDA0 */

#define BIT_G6_PIN_RFSDA0_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFSDA0_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFSDA0_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_RFSDA0_FUN_SE            BIT(11)
#define BIT_G6_PIN_RFSDA0_DUMY              BIT(10)
#define BIT_G6_PIN_RFSDA0_FUN_WPU           BIT(7)
#define BIT_G6_PIN_RFSDA0_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_RFSDA0_SLP_WPU           BIT(3)
#define BIT_G6_PIN_RFSDA0_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_RFSDA0_SLP_IE            BIT(1)
#define BIT_G6_PIN_RFSDA0_SLP_OE            BIT(0)

/* REG_G6_PIN_RFSCK0 */

#define BIT_G6_PIN_RFSCK0_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFSCK0_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFSCK0_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_RFSCK0_FUN_SE            BIT(11)
#define BIT_G6_PIN_RFSCK0_DUMY              BIT(10)
#define BIT_G6_PIN_RFSCK0_FUN_WPU           BIT(7)
#define BIT_G6_PIN_RFSCK0_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_RFSCK0_SLP_WPU           BIT(3)
#define BIT_G6_PIN_RFSCK0_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_RFSCK0_SLP_IE            BIT(1)
#define BIT_G6_PIN_RFSCK0_SLP_OE            BIT(0)

/* REG_G6_PIN_RFSEN0 */

#define BIT_G6_PIN_RFSEN0_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G6_PIN_RFSEN0_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G6_PIN_RFSEN0_FUN_WPUS          BIT(12)
#define BIT_G6_PIN_RFSEN0_FUN_SE            BIT(11)
#define BIT_G6_PIN_RFSEN0_DUMY              BIT(10)
#define BIT_G6_PIN_RFSEN0_FUN_WPU           BIT(7)
#define BIT_G6_PIN_RFSEN0_FUN_WPDO          BIT(6)
#define BIT_G6_PIN_RFSEN0_SLP_WPU           BIT(3)
#define BIT_G6_PIN_RFSEN0_SLP_WPDO          BIT(2)
#define BIT_G6_PIN_RFSEN0_SLP_IE            BIT(1)
#define BIT_G6_PIN_RFSEN0_SLP_OE            BIT(0)

/* REG_G6_PIN_RF_LVDS0_ADC_ON */

#define BIT_G6_PIN_LVDS0_ADC_ON_FUN_DRV(x)  (((x) & 0x3) << 19)
#define BIT_G6_PIN_LVDS0_ADC_ON_DSLP_EN(x)  (((x) & 0x1F) << 13)
#define BIT_G6_PIN_LVDS0_ADC_ON_FUN_WPUS    BIT(12)
#define BIT_G6_PIN_LVDS0_ADC_ON_FUN_SE      BIT(11)
#define BIT_G6_PIN_LVDS0_ADC_ON_DUMY        BIT(10)
#define BIT_G6_PIN_LVDS0_ADC_ON_FUN_WPU     BIT(7)
#define BIT_G6_PIN_LVDS0_ADC_ON_FUN_WPDO    BIT(6)
#define BIT_G6_PIN_LVDS0_ADC_ON_SLP_WPU     BIT(3)
#define BIT_G6_PIN_LVDS0_ADC_ON_SLP_WPDO    BIT(2)
#define BIT_G6_PIN_LVDS0_ADC_ON_SLP_IE      BIT(1)
#define BIT_G6_PIN_LVDS0_ADC_ON_SLP_OE      BIT(0)

/* REG_G6_PIN_RF_LVDS0_DAC_ON */

#define BIT_G6_PIN_LVDS0_DAC_ON_FUN_DRV(x)  (((x) & 0x3) << 19)
#define BIT_G6_PIN_LVDS0_DAC_ON_DSLP_EN(x)  (((x) & 0x1F) << 13)
#define BIT_G6_PIN_LVDS0_DAC_ON_FUN_WPUS    BIT(12)
#define BIT_G6_PIN_LVDS0_DAC_ON_FUN_SE      BIT(11)
#define BIT_G6_PIN_LVDS0_DAC_ON_DUMY        BIT(10)
#define BIT_G6_PIN_LVDS0_DAC_ON_FUN_WPU     BIT(7)
#define BIT_G6_PIN_LVDS0_DAC_ON_FUN_WPDO    BIT(6)
#define BIT_G6_PIN_LVDS0_DAC_ON_SLP_WPU     BIT(3)
#define BIT_G6_PIN_LVDS0_DAC_ON_SLP_WPDO    BIT(2)
#define BIT_G6_PIN_LVDS0_DAC_ON_SLP_IE      BIT(1)
#define BIT_G6_PIN_LVDS0_DAC_ON_SLP_OE      BIT(0)

/* REG_G6_PIN_SPI2_CSN */

#define BIT_G6_PIN_SPI2_CSN_FUN_DRV(x)      (((x) & 0x3) << 19)
#define BIT_G6_PIN_SPI2_CSN_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G6_PIN_SPI2_CSN_FUN_WPUS        BIT(12)
#define BIT_G6_PIN_SPI2_CSN_FUN_SE          BIT(11)
#define BIT_G6_PIN_SPI2_CSN_DUMY            BIT(10)
#define BIT_G6_PIN_SPI2_CSN_FUN_WPU         BIT(7)
#define BIT_G6_PIN_SPI2_CSN_FUN_WPDO        BIT(6)
#define BIT_G6_PIN_SPI2_CSN_SLP_WPU         BIT(3)
#define BIT_G6_PIN_SPI2_CSN_SLP_WPDO        BIT(2)
#define BIT_G6_PIN_SPI2_CSN_SLP_IE          BIT(1)
#define BIT_G6_PIN_SPI2_CSN_SLP_OE          BIT(0)

/* REG_G6_PIN_SPI2_DO */

#define BIT_G6_PIN_SPI2_DO_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G6_PIN_SPI2_DO_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_SPI2_DO_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_SPI2_DO_FUN_SE           BIT(11)
#define BIT_G6_PIN_SPI2_DO_DUMY             BIT(10)
#define BIT_G6_PIN_SPI2_DO_FUN_WPU          BIT(7)
#define BIT_G6_PIN_SPI2_DO_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_SPI2_DO_SLP_WPU          BIT(3)
#define BIT_G6_PIN_SPI2_DO_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_SPI2_DO_SLP_IE           BIT(1)
#define BIT_G6_PIN_SPI2_DO_SLP_OE           BIT(0)

/* REG_G6_PIN_SPI2_DI */

#define BIT_G6_PIN_SPI2_DI_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G6_PIN_SPI2_DI_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_SPI2_DI_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_SPI2_DI_FUN_SE           BIT(11)
#define BIT_G6_PIN_SPI2_DI_DUMY             BIT(10)
#define BIT_G6_PIN_SPI2_DI_FUN_WPU          BIT(7)
#define BIT_G6_PIN_SPI2_DI_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_SPI2_DI_SLP_WPU          BIT(3)
#define BIT_G6_PIN_SPI2_DI_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_SPI2_DI_SLP_IE           BIT(1)
#define BIT_G6_PIN_SPI2_DI_SLP_OE           BIT(0)

/* REG_G6_PIN_SPI2_CLK */

#define BIT_G6_PIN_SPI2_CLK_FUN_DRV(x)      (((x) & 0x3) << 19)
#define BIT_G6_PIN_SPI2_CLK_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G6_PIN_SPI2_CLK_FUN_WPUS        BIT(12)
#define BIT_G6_PIN_SPI2_CLK_FUN_SE          BIT(11)
#define BIT_G6_PIN_SPI2_CLK_DUMY            BIT(10)
#define BIT_G6_PIN_SPI2_CLK_FUN_WPU         BIT(7)
#define BIT_G6_PIN_SPI2_CLK_FUN_WPDO        BIT(6)
#define BIT_G6_PIN_SPI2_CLK_SLP_WPU         BIT(3)
#define BIT_G6_PIN_SPI2_CLK_SLP_WPDO        BIT(2)
#define BIT_G6_PIN_SPI2_CLK_SLP_IE          BIT(1)
#define BIT_G6_PIN_SPI2_CLK_SLP_OE          BIT(0)

/* REG_G6_PIN_SPI0_CSN */

#define BIT_G6_PIN_SPI0_CSN_FUN_DRV(x)      (((x) & 0x3) << 19)
#define BIT_G6_PIN_SPI0_CSN_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G6_PIN_SPI0_CSN_FUN_WPUS        BIT(12)
#define BIT_G6_PIN_SPI0_CSN_FUN_SE          BIT(11)
#define BIT_G6_PIN_SPI0_CSN_DUMY            BIT(10)
#define BIT_G6_PIN_SPI0_CSN_FUN_WPU         BIT(7)
#define BIT_G6_PIN_SPI0_CSN_FUN_WPDO        BIT(6)
#define BIT_G6_PIN_SPI0_CSN_SLP_WPU         BIT(3)
#define BIT_G6_PIN_SPI0_CSN_SLP_WPDO        BIT(2)
#define BIT_G6_PIN_SPI0_CSN_SLP_IE          BIT(1)
#define BIT_G6_PIN_SPI0_CSN_SLP_OE          BIT(0)

/* REG_G6_PIN_SPI0_DO */

#define BIT_G6_PIN_SPI0_DO_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G6_PIN_SPI0_DO_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_SPI0_DO_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_SPI0_DO_FUN_SE           BIT(11)
#define BIT_G6_PIN_SPI0_DO_DUMY             BIT(10)
#define BIT_G6_PIN_SPI0_DO_FUN_WPU          BIT(7)
#define BIT_G6_PIN_SPI0_DO_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_SPI0_DO_SLP_WPU          BIT(3)
#define BIT_G6_PIN_SPI0_DO_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_SPI0_DO_SLP_IE           BIT(1)
#define BIT_G6_PIN_SPI0_DO_SLP_OE           BIT(0)

/* REG_G6_PIN_SPI0_DI */

#define BIT_G6_PIN_SPI0_DI_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G6_PIN_SPI0_DI_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G6_PIN_SPI0_DI_FUN_WPUS         BIT(12)
#define BIT_G6_PIN_SPI0_DI_FUN_SE           BIT(11)
#define BIT_G6_PIN_SPI0_DI_DUMY             BIT(10)
#define BIT_G6_PIN_SPI0_DI_FUN_WPU          BIT(7)
#define BIT_G6_PIN_SPI0_DI_FUN_WPDO         BIT(6)
#define BIT_G6_PIN_SPI0_DI_SLP_WPU          BIT(3)
#define BIT_G6_PIN_SPI0_DI_SLP_WPDO         BIT(2)
#define BIT_G6_PIN_SPI0_DI_SLP_IE           BIT(1)
#define BIT_G6_PIN_SPI0_DI_SLP_OE           BIT(0)

/* REG_G6_PIN_SPI0_CLK */

#define BIT_G6_PIN_SPI0_CLK_FUN_DRV(x)      (((x) & 0x3) << 19)
#define BIT_G6_PIN_SPI0_CLK_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G6_PIN_SPI0_CLK_FUN_WPUS        BIT(12)
#define BIT_G6_PIN_SPI0_CLK_FUN_SE          BIT(11)
#define BIT_G6_PIN_SPI0_CLK_DUMY            BIT(10)
#define BIT_G6_PIN_SPI0_CLK_FUN_WPU         BIT(7)
#define BIT_G6_PIN_SPI0_CLK_FUN_WPDO        BIT(6)
#define BIT_G6_PIN_SPI0_CLK_SLP_WPU         BIT(3)
#define BIT_G6_PIN_SPI0_CLK_SLP_WPDO        BIT(2)
#define BIT_G6_PIN_SPI0_CLK_SLP_IE          BIT(1)
#define BIT_G6_PIN_SPI0_CLK_SLP_OE          BIT(0)

/* REG_G6_PIN_DTDO_LTE */

#define BIT_G6_PIN_DTDO_LTE_FUN_DRV(x)      (((x) & 0x3) << 19)
#define BIT_G6_PIN_DTDO_LTE_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G6_PIN_DTDO_LTE_FUN_WPUS        BIT(12)
#define BIT_G6_PIN_DTDO_LTE_FUN_SE          BIT(11)
#define BIT_G6_PIN_DTDO_LTE_DUMY            BIT(10)
#define BIT_G6_PIN_DTDO_LTE_FUN_WPU         BIT(7)
#define BIT_G6_PIN_DTDO_LTE_FUN_WPDO        BIT(6)
#define BIT_G6_PIN_DTDO_LTE_SLP_WPU         BIT(3)
#define BIT_G6_PIN_DTDO_LTE_SLP_WPDO        BIT(2)
#define BIT_G6_PIN_DTDO_LTE_SLP_IE          BIT(1)
#define BIT_G6_PIN_DTDO_LTE_SLP_OE          BIT(0)

/* REG_G6_PIN_DTDI_LTE */

#define BIT_G6_PIN_DTDI_LTE_FUN_DRV(x)      (((x) & 0x3) << 19)
#define BIT_G6_PIN_DTDI_LTE_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G6_PIN_DTDI_LTE_FUN_WPUS        BIT(12)
#define BIT_G6_PIN_DTDI_LTE_FUN_SE          BIT(11)
#define BIT_G6_PIN_DTDI_LTE_DUMY            BIT(10)
#define BIT_G6_PIN_DTDI_LTE_FUN_WPU         BIT(7)
#define BIT_G6_PIN_DTDI_LTE_FUN_WPDO        BIT(6)
#define BIT_G6_PIN_DTDI_LTE_SLP_WPU         BIT(3)
#define BIT_G6_PIN_DTDI_LTE_SLP_WPDO        BIT(2)
#define BIT_G6_PIN_DTDI_LTE_SLP_IE          BIT(1)
#define BIT_G6_PIN_DTDI_LTE_SLP_OE          BIT(0)

/* REG_G6_PIN_DTCK_LTE */

#define BIT_G6_PIN_DTCK_LTE_FUN_DRV(x)      (((x) & 0x3) << 19)
#define BIT_G6_PIN_DTCK_LTE_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G6_PIN_DTCK_LTE_FUN_WPUS        BIT(12)
#define BIT_G6_PIN_DTCK_LTE_FUN_SE          BIT(11)
#define BIT_G6_PIN_DTCK_LTE_DUMY            BIT(10)
#define BIT_G6_PIN_DTCK_LTE_FUN_WPU         BIT(7)
#define BIT_G6_PIN_DTCK_LTE_FUN_WPDO        BIT(6)
#define BIT_G6_PIN_DTCK_LTE_SLP_WPU         BIT(3)
#define BIT_G6_PIN_DTCK_LTE_SLP_WPDO        BIT(2)
#define BIT_G6_PIN_DTCK_LTE_SLP_IE          BIT(1)
#define BIT_G6_PIN_DTCK_LTE_SLP_OE          BIT(0)

/* REG_G6_PIN_DTMS_LTE */

#define BIT_G6_PIN_DTMS_LTE_FUN_DRV(x)      (((x) & 0x3) << 19)
#define BIT_G6_PIN_DTMS_LTE_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G6_PIN_DTMS_LTE_FUN_WPUS        BIT(12)
#define BIT_G6_PIN_DTMS_LTE_FUN_SE          BIT(11)
#define BIT_G6_PIN_DTMS_LTE_DUMY            BIT(10)
#define BIT_G6_PIN_DTMS_LTE_FUN_WPU         BIT(7)
#define BIT_G6_PIN_DTMS_LTE_FUN_WPDO        BIT(6)
#define BIT_G6_PIN_DTMS_LTE_SLP_WPU         BIT(3)
#define BIT_G6_PIN_DTMS_LTE_SLP_WPDO        BIT(2)
#define BIT_G6_PIN_DTMS_LTE_SLP_IE          BIT(1)
#define BIT_G6_PIN_DTMS_LTE_SLP_OE          BIT(0)

/* REG_G6_PIN_DRTCK_LTE */

#define BIT_G6_PIN_DRTCK_LTE_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G6_PIN_DRTCK_LTE_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G6_PIN_DRTCK_LTE_FUN_WPUS       BIT(12)
#define BIT_G6_PIN_DRTCK_LTE_FUN_SE         BIT(11)
#define BIT_G6_PIN_DRTCK_LTE_DUMY           BIT(10)
#define BIT_G6_PIN_DRTCK_LTE_FUN_WPU        BIT(7)
#define BIT_G6_PIN_DRTCK_LTE_FUN_WPDO       BIT(6)
#define BIT_G6_PIN_DRTCK_LTE_SLP_WPU        BIT(3)
#define BIT_G6_PIN_DRTCK_LTE_SLP_WPDO       BIT(2)
#define BIT_G6_PIN_DRTCK_LTE_SLP_IE         BIT(1)
#define BIT_G6_PIN_DRTCK_LTE_SLP_OE         BIT(0)

/* REG_G6_PIN_MTCK_ARM */

#define BIT_G6_PIN_MTCK_ARM_FUN_DRV(x)      (((x) & 0x3) << 19)
#define BIT_G6_PIN_MTCK_ARM_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G6_PIN_MTCK_ARM_FUN_WPUS        BIT(12)
#define BIT_G6_PIN_MTCK_ARM_FUN_SE          BIT(11)
#define BIT_G6_PIN_MTCK_ARM_DUMY            BIT(10)
#define BIT_G6_PIN_MTCK_ARM_FUN_WPU         BIT(7)
#define BIT_G6_PIN_MTCK_ARM_FUN_WPDO        BIT(6)
#define BIT_G6_PIN_MTCK_ARM_SLP_WPU         BIT(3)
#define BIT_G6_PIN_MTCK_ARM_SLP_WPDO        BIT(2)
#define BIT_G6_PIN_MTCK_ARM_SLP_IE          BIT(1)
#define BIT_G6_PIN_MTCK_ARM_SLP_OE          BIT(0)

/* REG_G6_PIN_MTMS_ARM */

#define BIT_G6_PIN_MTMS_ARM_FUN_DRV(x)      (((x) & 0x3) << 19)
#define BIT_G6_PIN_MTMS_ARM_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G6_PIN_MTMS_ARM_FUN_WPUS        BIT(12)
#define BIT_G6_PIN_MTMS_ARM_FUN_SE          BIT(11)
#define BIT_G6_PIN_MTMS_ARM_DUMY            BIT(10)
#define BIT_G6_PIN_MTMS_ARM_FUN_WPU         BIT(7)
#define BIT_G6_PIN_MTMS_ARM_FUN_WPDO        BIT(6)
#define BIT_G6_PIN_MTMS_ARM_SLP_WPU         BIT(3)
#define BIT_G6_PIN_MTMS_ARM_SLP_WPDO        BIT(2)
#define BIT_G6_PIN_MTMS_ARM_SLP_IE          BIT(1)
#define BIT_G6_PIN_MTMS_ARM_SLP_OE          BIT(0)


#endif /* G6_PIN_H */


