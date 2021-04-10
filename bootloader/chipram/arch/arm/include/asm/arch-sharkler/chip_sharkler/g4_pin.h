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


#ifndef G4_PIN_H
#define G4_PIN_H

#define CTL_BASE_G4_PIN 0x402A0000


#define REG_G4_PIN_LCM_RSTN         ( CTL_BASE_G4_PIN + 0x04F4 )
#define REG_G4_PIN_DSI_TE           ( CTL_BASE_G4_PIN + 0x04F8 )
#define REG_G4_PIN_CHIP_SLEEP       ( CTL_BASE_G4_PIN + 0x04FC )
#define REG_G4_PIN_PTEST            ( CTL_BASE_G4_PIN + 0x0500 )
#define REG_G4_PIN_EXT_RST_B        ( CTL_BASE_G4_PIN + 0x0504 )
#define REG_G4_PIN_XTL_BUF_EN1      ( CTL_BASE_G4_PIN + 0x0508 )
#define REG_G4_PIN_CLK_32K          ( CTL_BASE_G4_PIN + 0x050C )
#define REG_G4_PIN_AUD_SCLK         ( CTL_BASE_G4_PIN + 0x0510 )
#define REG_G4_PIN_AUD_ADD0         ( CTL_BASE_G4_PIN + 0x0514 )
#define REG_G4_PIN_XTL_BUF_EN0      ( CTL_BASE_G4_PIN + 0x0518 )
#define REG_G4_PIN_ANA_INT          ( CTL_BASE_G4_PIN + 0x051C )
#define REG_G4_PIN_AUD_ADSYNC       ( CTL_BASE_G4_PIN + 0x0520 )
#define REG_G4_PIN_ADI_SCLK         ( CTL_BASE_G4_PIN + 0x0524 )
#define REG_G4_PIN_AUD_DAD1         ( CTL_BASE_G4_PIN + 0x0528 )
#define REG_G4_PIN_AUD_DAD0         ( CTL_BASE_G4_PIN + 0x052C )
#define REG_G4_PIN_AUD_DASYNC       ( CTL_BASE_G4_PIN + 0x0530 )
#define REG_G4_PIN_ADI_SYNC         ( CTL_BASE_G4_PIN + 0x0534 )
#define REG_G4_PIN_ADI_D            ( CTL_BASE_G4_PIN + 0x0538 )
#define REG_G4_PIN_SD0_D3           ( CTL_BASE_G4_PIN + 0x053C )
#define REG_G4_PIN_SD0_D2           ( CTL_BASE_G4_PIN + 0x0540 )
#define REG_G4_PIN_SD0_CMD          ( CTL_BASE_G4_PIN + 0x0544 )
#define REG_G4_PIN_SD0_D0           ( CTL_BASE_G4_PIN + 0x0548 )
#define REG_G4_PIN_SD0_D1           ( CTL_BASE_G4_PIN + 0x054C )
#define REG_G4_PIN_SD0_CLK0         ( CTL_BASE_G4_PIN + 0x0550 )
#define REG_G4_PIN_SD0_DUMMY        ( CTL_BASE_G4_PIN + 0x0554 )
#define REG_G4_PIN_SD2_CLK          ( CTL_BASE_G4_PIN + 0x0558 )
#define REG_G4_PIN_SD2_CMD          ( CTL_BASE_G4_PIN + 0x055C )
#define REG_G4_PIN_SD2_D0           ( CTL_BASE_G4_PIN + 0x0560 )
#define REG_G4_PIN_SD2_D1           ( CTL_BASE_G4_PIN + 0x0564 )
#define REG_G4_PIN_SD2_D2           ( CTL_BASE_G4_PIN + 0x0568 )
#define REG_G4_PIN_SD2_D3           ( CTL_BASE_G4_PIN + 0x056C )
#define REG_G4_PIN_SD2_DUMMY        ( CTL_BASE_G4_PIN + 0x0570 )

/* REG_G4_PIN_LCM_RSTN */

#define BIT_G4_PIN_LCM_RSTN_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G4_PIN_LCM_RSTN_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G4_PIN_LCM_RSTN_FUN_WPUS       BIT(12)
#define BIT_G4_PIN_LCM_RSTN_FUN_SE         BIT(11)
#define BIT_G4_PIN_LCM_RSTN_DUMY           BIT(10)
#define BIT_G4_PIN_LCM_RSTN_FUN_WPU        BIT(7)
#define BIT_G4_PIN_LCM_RSTN_FUN_WPDO       BIT(6)
#define BIT_G4_PIN_LCM_RSTN_SLP_WPU        BIT(3)
#define BIT_G4_PIN_LCM_RSTN_SLP_WPDO       BIT(2)
#define BIT_G4_PIN_LCM_RSTN_SLP_IE         BIT(1)
#define BIT_G4_PIN_LCM_RSTN_SLP_OE         BIT(0)

/* REG_G4_PIN_DSI_TE */

#define BIT_G4_PIN_DSI_TE_FUN_DRV(x)       (((x) & 0x3) << 19)
#define BIT_G4_PIN_DSI_TE_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G4_PIN_DSI_TE_FUN_WPUS         BIT(12)
#define BIT_G4_PIN_DSI_TE_FUN_SE           BIT(11)
#define BIT_G4_PIN_DSI_TE_DUMY             BIT(10)
#define BIT_G4_PIN_DSI_TE_FUN_WPU          BIT(7)
#define BIT_G4_PIN_DSI_TE_FUN_WPDO         BIT(6)
#define BIT_G4_PIN_DSI_TE_SLP_WPU          BIT(3)
#define BIT_G4_PIN_DSI_TE_SLP_WPDO         BIT(2)
#define BIT_G4_PIN_DSI_TE_SLP_IE           BIT(1)
#define BIT_G4_PIN_DSI_TE_SLP_OE           BIT(0)

/* REG_G4_PIN_CHIP_SLEEP */

#define BIT_G4_PIN_CHIP_SLEEP_FUN_DRV(x)   (((x) & 0x3) << 19)
#define BIT_G4_PIN_CHIP_SLEEP_DSLP_EN(x)   (((x) & 0x1F) << 13)
#define BIT_G4_PIN_CHIP_SLEEP_FUN_WPUS     BIT(12)
#define BIT_G4_PIN_CHIP_SLEEP_FUN_SE       BIT(11)
#define BIT_G4_PIN_CHIP_SLEEP_DUMY         BIT(10)
#define BIT_G4_PIN_CHIP_SLEEP_FUN_WPU      BIT(7)
#define BIT_G4_PIN_CHIP_SLEEP_FUN_WPDO     BIT(6)
#define BIT_G4_PIN_CHIP_SLEEP_SLP_WPU      BIT(3)
#define BIT_G4_PIN_CHIP_SLEEP_SLP_WPDO     BIT(2)
#define BIT_G4_PIN_CHIP_SLEEP_SLP_IE       BIT(1)
#define BIT_G4_PIN_CHIP_SLEEP_SLP_OE       BIT(0)

/* REG_G4_PIN_PTEST */

#define BIT_G4_PIN_PTEST_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G4_PIN_PTEST_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G4_PIN_PTEST_FUN_WPUS          BIT(12)
#define BIT_G4_PIN_PTEST_FUN_SE            BIT(11)
#define BIT_G4_PIN_PTEST_DUMY              BIT(10)
#define BIT_G4_PIN_PTEST_FUN_WPU           BIT(7)
#define BIT_G4_PIN_PTEST_FUN_WPDO          BIT(6)
#define BIT_G4_PIN_PTEST_SLP_WPU           BIT(3)
#define BIT_G4_PIN_PTEST_SLP_WPDO          BIT(2)
#define BIT_G4_PIN_PTEST_SLP_IE            BIT(1)
#define BIT_G4_PIN_PTEST_SLP_OE            BIT(0)

/* REG_G4_PIN_EXT_RST_B */

#define BIT_G4_PIN_EXT_RST_B_FUN_DRV(x)    (((x) & 0x3) << 19)
#define BIT_G4_PIN_EXT_RST_B_DSLP_EN(x)    (((x) & 0x1F) << 13)
#define BIT_G4_PIN_EXT_RST_B_FUN_WPUS      BIT(12)
#define BIT_G4_PIN_EXT_RST_B_FUN_SE        BIT(11)
#define BIT_G4_PIN_EXT_RST_B_DUMY          BIT(10)
#define BIT_G4_PIN_EXT_RST_B_FUN_WPU       BIT(7)
#define BIT_G4_PIN_EXT_RST_B_FUN_WPDO      BIT(6)
#define BIT_G4_PIN_EXT_RST_B_SLP_WPU       BIT(3)
#define BIT_G4_PIN_EXT_RST_B_SLP_WPDO      BIT(2)
#define BIT_G4_PIN_EXT_RST_B_SLP_IE        BIT(1)
#define BIT_G4_PIN_EXT_RST_B_SLP_OE        BIT(0)

/* REG_G4_PIN_XTL_BUF_EN1 */

#define BIT_G4_PIN_XTL_BUF_EN1_FUN_DRV(x)  (((x) & 0x3) << 19)
#define BIT_G4_PIN_XTL_BUF_EN1_DSLP_EN(x)  (((x) & 0x1F) << 13)
#define BIT_G4_PIN_XTL_BUF_EN1_FUN_WPUS    BIT(12)
#define BIT_G4_PIN_XTL_BUF_EN1_FUN_SE      BIT(11)
#define BIT_G4_PIN_XTL_BUF_EN1_DUMY        BIT(10)
#define BIT_G4_PIN_XTL_BUF_EN1_FUN_WPU     BIT(7)
#define BIT_G4_PIN_XTL_BUF_EN1_FUN_WPDO    BIT(6)
#define BIT_G4_PIN_XTL_BUF_EN1_SLP_WPU     BIT(3)
#define BIT_G4_PIN_XTL_BUF_EN1_SLP_WPDO    BIT(2)
#define BIT_G4_PIN_XTL_BUF_EN1_SLP_IE      BIT(1)
#define BIT_G4_PIN_XTL_BUF_EN1_SLP_OE      BIT(0)

/* REG_G4_PIN_CLK_32K */

#define BIT_G4_PIN_CLK_32K_FUN_DRV(x)      (((x) & 0x3) << 19)
#define BIT_G4_PIN_CLK_32K_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G4_PIN_CLK_32K_FUN_WPUS        BIT(12)
#define BIT_G4_PIN_CLK_32K_FUN_SE          BIT(11)
#define BIT_G4_PIN_CLK_32K_DUMY            BIT(10)
#define BIT_G4_PIN_CLK_32K_FUN_WPU         BIT(7)
#define BIT_G4_PIN_CLK_32K_FUN_WPDO        BIT(6)
#define BIT_G4_PIN_CLK_32K_SLP_WPU         BIT(3)
#define BIT_G4_PIN_CLK_32K_SLP_WPDO        BIT(2)
#define BIT_G4_PIN_CLK_32K_SLP_IE          BIT(1)
#define BIT_G4_PIN_CLK_32K_SLP_OE          BIT(0)

/* REG_G4_PIN_AUD_SCLK */

#define BIT_G4_PIN_AUD_SCLK_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G4_PIN_AUD_SCLK_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G4_PIN_AUD_SCLK_FUN_WPUS       BIT(12)
#define BIT_G4_PIN_AUD_SCLK_FUN_SE         BIT(11)
#define BIT_G4_PIN_AUD_SCLK_DUMY           BIT(10)
#define BIT_G4_PIN_AUD_SCLK_FUN_WPU        BIT(7)
#define BIT_G4_PIN_AUD_SCLK_FUN_WPDO       BIT(6)
#define BIT_G4_PIN_AUD_SCLK_SLP_WPU        BIT(3)
#define BIT_G4_PIN_AUD_SCLK_SLP_WPDO       BIT(2)
#define BIT_G4_PIN_AUD_SCLK_SLP_IE         BIT(1)
#define BIT_G4_PIN_AUD_SCLK_SLP_OE         BIT(0)

/* REG_G4_PIN_AUD_ADD0 */

#define BIT_G4_PIN_AUD_ADD0_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G4_PIN_AUD_ADD0_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G4_PIN_AUD_ADD0_FUN_WPUS       BIT(12)
#define BIT_G4_PIN_AUD_ADD0_FUN_SE         BIT(11)
#define BIT_G4_PIN_AUD_ADD0_DUMY           BIT(10)
#define BIT_G4_PIN_AUD_ADD0_FUN_WPU        BIT(7)
#define BIT_G4_PIN_AUD_ADD0_FUN_WPDO       BIT(6)
#define BIT_G4_PIN_AUD_ADD0_SLP_WPU        BIT(3)
#define BIT_G4_PIN_AUD_ADD0_SLP_WPDO       BIT(2)
#define BIT_G4_PIN_AUD_ADD0_SLP_IE         BIT(1)
#define BIT_G4_PIN_AUD_ADD0_SLP_OE         BIT(0)

/* REG_G4_PIN_XTL_BUF_EN0 */

#define BIT_G4_PIN_XTL_BUF_EN0_FUN_DRV(x)  (((x) & 0x3) << 19)
#define BIT_G4_PIN_XTL_BUF_EN0_DSLP_EN(x)  (((x) & 0x1F) << 13)
#define BIT_G4_PIN_XTL_BUF_EN0_FUN_WPUS    BIT(12)
#define BIT_G4_PIN_XTL_BUF_EN0_FUN_SE      BIT(11)
#define BIT_G4_PIN_XTL_BUF_EN0_DUMY        BIT(10)
#define BIT_G4_PIN_XTL_BUF_EN0_FUN_WPU     BIT(7)
#define BIT_G4_PIN_XTL_BUF_EN0_FUN_WPDO    BIT(6)
#define BIT_G4_PIN_XTL_BUF_EN0_SLP_WPU     BIT(3)
#define BIT_G4_PIN_XTL_BUF_EN0_SLP_WPDO    BIT(2)
#define BIT_G4_PIN_XTL_BUF_EN0_SLP_IE      BIT(1)
#define BIT_G4_PIN_XTL_BUF_EN0_SLP_OE      BIT(0)

/* REG_G4_PIN_ANA_INT */

#define BIT_G4_PIN_ANA_INT_FUN_DRV(x)      (((x) & 0x3) << 19)
#define BIT_G4_PIN_ANA_INT_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G4_PIN_ANA_INT_FUN_WPUS        BIT(12)
#define BIT_G4_PIN_ANA_INT_FUN_SE          BIT(11)
#define BIT_G4_PIN_ANA_INT_DUMY            BIT(10)
#define BIT_G4_PIN_ANA_INT_FUN_WPU         BIT(7)
#define BIT_G4_PIN_ANA_INT_FUN_WPDO        BIT(6)
#define BIT_G4_PIN_ANA_INT_SLP_WPU         BIT(3)
#define BIT_G4_PIN_ANA_INT_SLP_WPDO        BIT(2)
#define BIT_G4_PIN_ANA_INT_SLP_IE          BIT(1)
#define BIT_G4_PIN_ANA_INT_SLP_OE          BIT(0)

/* REG_G4_PIN_AUD_ADSYNC */

#define BIT_G4_PIN_AUD_ADSYNC_FUN_DRV(x)   (((x) & 0x3) << 19)
#define BIT_G4_PIN_AUD_ADSYNC_DSLP_EN(x)   (((x) & 0x1F) << 13)
#define BIT_G4_PIN_AUD_ADSYNC_FUN_WPUS     BIT(12)
#define BIT_G4_PIN_AUD_ADSYNC_FUN_SE       BIT(11)
#define BIT_G4_PIN_AUD_ADSYNC_DUMY         BIT(10)
#define BIT_G4_PIN_AUD_ADSYNC_FUN_WPU      BIT(7)
#define BIT_G4_PIN_AUD_ADSYNC_FUN_WPDO     BIT(6)
#define BIT_G4_PIN_AUD_ADSYNC_SLP_WPU      BIT(3)
#define BIT_G4_PIN_AUD_ADSYNC_SLP_WPDO     BIT(2)
#define BIT_G4_PIN_AUD_ADSYNC_SLP_IE       BIT(1)
#define BIT_G4_PIN_AUD_ADSYNC_SLP_OE       BIT(0)

/* REG_G4_PIN_ADI_SCLK */

#define BIT_G4_PIN_ADI_SCLK_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G4_PIN_ADI_SCLK_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G4_PIN_ADI_SCLK_FUN_WPUS       BIT(12)
#define BIT_G4_PIN_ADI_SCLK_FUN_SE         BIT(11)
#define BIT_G4_PIN_ADI_SCLK_DUMY           BIT(10)
#define BIT_G4_PIN_ADI_SCLK_FUN_WPU        BIT(7)
#define BIT_G4_PIN_ADI_SCLK_FUN_WPDO       BIT(6)
#define BIT_G4_PIN_ADI_SCLK_SLP_WPU        BIT(3)
#define BIT_G4_PIN_ADI_SCLK_SLP_WPDO       BIT(2)
#define BIT_G4_PIN_ADI_SCLK_SLP_IE         BIT(1)
#define BIT_G4_PIN_ADI_SCLK_SLP_OE         BIT(0)

/* REG_G4_PIN_AUD_DAD1 */

#define BIT_G4_PIN_AUD_DAD1_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G4_PIN_AUD_DAD1_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G4_PIN_AUD_DAD1_FUN_WPUS       BIT(12)
#define BIT_G4_PIN_AUD_DAD1_FUN_SE         BIT(11)
#define BIT_G4_PIN_AUD_DAD1_DUMY           BIT(10)
#define BIT_G4_PIN_AUD_DAD1_FUN_WPU        BIT(7)
#define BIT_G4_PIN_AUD_DAD1_FUN_WPDO       BIT(6)
#define BIT_G4_PIN_AUD_DAD1_SLP_WPU        BIT(3)
#define BIT_G4_PIN_AUD_DAD1_SLP_WPDO       BIT(2)
#define BIT_G4_PIN_AUD_DAD1_SLP_IE         BIT(1)
#define BIT_G4_PIN_AUD_DAD1_SLP_OE         BIT(0)

/* REG_G4_PIN_AUD_DAD0 */

#define BIT_G4_PIN_AUD_DAD0_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G4_PIN_AUD_DAD0_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G4_PIN_AUD_DAD0_FUN_WPUS       BIT(12)
#define BIT_G4_PIN_AUD_DAD0_FUN_SE         BIT(11)
#define BIT_G4_PIN_AUD_DAD0_DUMY           BIT(10)
#define BIT_G4_PIN_AUD_DAD0_FUN_WPU        BIT(7)
#define BIT_G4_PIN_AUD_DAD0_FUN_WPDO       BIT(6)
#define BIT_G4_PIN_AUD_DAD0_SLP_WPU        BIT(3)
#define BIT_G4_PIN_AUD_DAD0_SLP_WPDO       BIT(2)
#define BIT_G4_PIN_AUD_DAD0_SLP_IE         BIT(1)
#define BIT_G4_PIN_AUD_DAD0_SLP_OE         BIT(0)

/* REG_G4_PIN_AUD_DASYNC */

#define BIT_G4_PIN_AUD_DASYNC_FUN_DRV(x)   (((x) & 0x3) << 19)
#define BIT_G4_PIN_AUD_DASYNC_DSLP_EN(x)   (((x) & 0x1F) << 13)
#define BIT_G4_PIN_AUD_DASYNC_FUN_WPUS     BIT(12)
#define BIT_G4_PIN_AUD_DASYNC_FUN_SE       BIT(11)
#define BIT_G4_PIN_AUD_DASYNC_DUMY         BIT(10)
#define BIT_G4_PIN_AUD_DASYNC_FUN_WPU      BIT(7)
#define BIT_G4_PIN_AUD_DASYNC_FUN_WPDO     BIT(6)
#define BIT_G4_PIN_AUD_DASYNC_SLP_WPU      BIT(3)
#define BIT_G4_PIN_AUD_DASYNC_SLP_WPDO     BIT(2)
#define BIT_G4_PIN_AUD_DASYNC_SLP_IE       BIT(1)
#define BIT_G4_PIN_AUD_DASYNC_SLP_OE       BIT(0)

/* REG_G4_PIN_ADI_SYNC */

#define BIT_G4_PIN_ADI_SYNC_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G4_PIN_ADI_SYNC_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G4_PIN_ADI_SYNC_FUN_WPUS       BIT(12)
#define BIT_G4_PIN_ADI_SYNC_FUN_SE         BIT(11)
#define BIT_G4_PIN_ADI_SYNC_DUMY           BIT(10)
#define BIT_G4_PIN_ADI_SYNC_FUN_WPU        BIT(7)
#define BIT_G4_PIN_ADI_SYNC_FUN_WPDO       BIT(6)
#define BIT_G4_PIN_ADI_SYNC_SLP_WPU        BIT(3)
#define BIT_G4_PIN_ADI_SYNC_SLP_WPDO       BIT(2)
#define BIT_G4_PIN_ADI_SYNC_SLP_IE         BIT(1)
#define BIT_G4_PIN_ADI_SYNC_SLP_OE         BIT(0)

/* REG_G4_PIN_ADI_D */

#define BIT_G4_PIN_ADI_D_FUN_DRV(x)        (((x) & 0x3) << 19)
#define BIT_G4_PIN_ADI_D_DSLP_EN(x)        (((x) & 0x1F) << 13)
#define BIT_G4_PIN_ADI_D_FUN_WPUS          BIT(12)
#define BIT_G4_PIN_ADI_D_FUN_SE            BIT(11)
#define BIT_G4_PIN_ADI_D_DUMY              BIT(10)
#define BIT_G4_PIN_ADI_D_FUN_WPU           BIT(7)
#define BIT_G4_PIN_ADI_D_FUN_WPDO          BIT(6)
#define BIT_G4_PIN_ADI_D_SLP_WPU           BIT(3)
#define BIT_G4_PIN_ADI_D_SLP_WPDO          BIT(2)
#define BIT_G4_PIN_ADI_D_SLP_IE            BIT(1)
#define BIT_G4_PIN_ADI_D_SLP_OE            BIT(0)

/* REG_G4_PIN_SD0_D3 */

#define BIT_G4_PIN_SD0_D3_FUN_DRV(x)       (((x) & 0xF) << 19)
#define BIT_G4_PIN_SD0_D3_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G4_PIN_SD0_D3_FUN_WPUS         BIT(12)
#define BIT_G4_PIN_SD0_D3_FUN_SE           BIT(11)
#define BIT_G4_PIN_SD0_D3_MS               BIT(10)
#define BIT_G4_PIN_SD0_D3_MSEN             BIT(9)
#define BIT_G4_PIN_SD0_D3_MSOUT            BIT(8)
#define BIT_G4_PIN_SD0_D3_FUN_WPU          BIT(7)
#define BIT_G4_PIN_SD0_D3_FUN_WPDO         BIT(6)
#define BIT_G4_PIN_SD0_D3_SLP_WPU          BIT(3)
#define BIT_G4_PIN_SD0_D3_SLP_WPDO         BIT(2)
#define BIT_G4_PIN_SD0_D3_SLP_IE           BIT(1)
#define BIT_G4_PIN_SD0_D3_SLP_OE           BIT(0)

/* REG_G4_PIN_SD0_D2 */

#define BIT_G4_PIN_SD0_D2_FUN_DRV(x)       (((x) & 0xF) << 19)
#define BIT_G4_PIN_SD0_D2_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G4_PIN_SD0_D2_FUN_WPUS         BIT(12)
#define BIT_G4_PIN_SD0_D2_FUN_SE           BIT(11)
#define BIT_G4_PIN_SD0_D2_MS               BIT(10)
#define BIT_G4_PIN_SD0_D2_MSEN             BIT(9)
#define BIT_G4_PIN_SD0_D2_MSOUT            BIT(8)
#define BIT_G4_PIN_SD0_D2_FUN_WPU          BIT(7)
#define BIT_G4_PIN_SD0_D2_FUN_WPDO         BIT(6)
#define BIT_G4_PIN_SD0_D2_SLP_WPU          BIT(3)
#define BIT_G4_PIN_SD0_D2_SLP_WPDO         BIT(2)
#define BIT_G4_PIN_SD0_D2_SLP_IE           BIT(1)
#define BIT_G4_PIN_SD0_D2_SLP_OE           BIT(0)

/* REG_G4_PIN_SD0_CMD */

#define BIT_G4_PIN_SD0_CMD_FUN_DRV(x)      (((x) & 0xF) << 19)
#define BIT_G4_PIN_SD0_CMD_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G4_PIN_SD0_CMD_FUN_WPUS        BIT(12)
#define BIT_G4_PIN_SD0_CMD_FUN_SE          BIT(11)
#define BIT_G4_PIN_SD0_CMD_MS              BIT(10)
#define BIT_G4_PIN_SD0_CMD_MSEN            BIT(9)
#define BIT_G4_PIN_SD0_CMD_MSOUT           BIT(8)
#define BIT_G4_PIN_SD0_CMD_FUN_WPU         BIT(7)
#define BIT_G4_PIN_SD0_CMD_FUN_WPDO        BIT(6)
#define BIT_G4_PIN_SD0_CMD_SLP_WPU         BIT(3)
#define BIT_G4_PIN_SD0_CMD_SLP_WPDO        BIT(2)
#define BIT_G4_PIN_SD0_CMD_SLP_IE          BIT(1)
#define BIT_G4_PIN_SD0_CMD_SLP_OE          BIT(0)

/* REG_G4_PIN_SD0_D0 */

#define BIT_G4_PIN_SD0_D0_FUN_DRV(x)       (((x) & 0xF) << 19)
#define BIT_G4_PIN_SD0_D0_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G4_PIN_SD0_D0_FUN_WPUS         BIT(12)
#define BIT_G4_PIN_SD0_D0_FUN_SE           BIT(11)
#define BIT_G4_PIN_SD0_D0_MS               BIT(10)
#define BIT_G4_PIN_SD0_D0_MSEN             BIT(9)
#define BIT_G4_PIN_SD0_D0_MSOUT            BIT(8)
#define BIT_G4_PIN_SD0_D0_FUN_WPU          BIT(7)
#define BIT_G4_PIN_SD0_D0_FUN_WPDO         BIT(6)
#define BIT_G4_PIN_SD0_D0_SLP_WPU          BIT(3)
#define BIT_G4_PIN_SD0_D0_SLP_WPDO         BIT(2)
#define BIT_G4_PIN_SD0_D0_SLP_IE           BIT(1)
#define BIT_G4_PIN_SD0_D0_SLP_OE           BIT(0)

/* REG_G4_PIN_SD0_D1 */

#define BIT_G4_PIN_SD0_D1_FUN_DRV(x)       (((x) & 0xF) << 19)
#define BIT_G4_PIN_SD0_D1_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G4_PIN_SD0_D1_FUN_WPUS         BIT(12)
#define BIT_G4_PIN_SD0_D1_FUN_SE           BIT(11)
#define BIT_G4_PIN_SD0_D1_MS               BIT(10)
#define BIT_G4_PIN_SD0_D1_MSEN             BIT(9)
#define BIT_G4_PIN_SD0_D1_MSOUT            BIT(8)
#define BIT_G4_PIN_SD0_D1_FUN_WPU          BIT(7)
#define BIT_G4_PIN_SD0_D1_FUN_WPDO         BIT(6)
#define BIT_G4_PIN_SD0_D1_SLP_WPU          BIT(3)
#define BIT_G4_PIN_SD0_D1_SLP_WPDO         BIT(2)
#define BIT_G4_PIN_SD0_D1_SLP_IE           BIT(1)
#define BIT_G4_PIN_SD0_D1_SLP_OE           BIT(0)

/* REG_G4_PIN_SD0_CLK0 */

#define BIT_G4_PIN_SD0_CLK0_FUN_DRV(x)     (((x) & 0xF) << 19)
#define BIT_G4_PIN_SD0_CLK0_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G4_PIN_SD0_CLK0_FUN_WPUS       BIT(12)
#define BIT_G4_PIN_SD0_CLK0_FUN_SE         BIT(11)
#define BIT_G4_PIN_SD0_CLK0_MS             BIT(10)
#define BIT_G4_PIN_SD0_CLK0_MSEN           BIT(9)
#define BIT_G4_PIN_SD0_CLK0_MSOUT          BIT(8)
#define BIT_G4_PIN_SD0_CLK0_FUN_WPU        BIT(7)
#define BIT_G4_PIN_SD0_CLK0_FUN_WPDO       BIT(6)
#define BIT_G4_PIN_SD0_CLK0_SLP_WPU        BIT(3)
#define BIT_G4_PIN_SD0_CLK0_SLP_WPDO       BIT(2)
#define BIT_G4_PIN_SD0_CLK0_SLP_IE         BIT(1)
#define BIT_G4_PIN_SD0_CLK0_SLP_OE         BIT(0)

/* REG_G4_PIN_SD0_DUMMY */

#define BIT_G4_PIN_SD0_DUMMY_FUN_DRV(x)    (((x) & 0xF) << 19)
#define BIT_G4_PIN_SD0_DUMMY_DSLP_EN(x)    (((x) & 0x1F) << 13)
#define BIT_G4_PIN_SD0_DUMMY_FUN_WPUS      BIT(12)
#define BIT_G4_PIN_SD0_DUMMY_FUN_SE        BIT(11)
#define BIT_G4_PIN_SD0_DUMMY_MS            BIT(10)
#define BIT_G4_PIN_SD0_DUMMY_MSEN          BIT(9)
#define BIT_G4_PIN_SD0_DUMMY_MSOUT         BIT(8)
#define BIT_G4_PIN_SD0_DUMMY_FUN_WPU       BIT(7)
#define BIT_G4_PIN_SD0_DUMMY_FUN_WPDO      BIT(6)
#define BIT_G4_PIN_SD0_DUMMY_SLP_WPU       BIT(3)
#define BIT_G4_PIN_SD0_DUMMY_SLP_WPDO      BIT(2)
#define BIT_G4_PIN_SD0_DUMMY_SLP_IE        BIT(1)
#define BIT_G4_PIN_SD0_DUMMY_SLP_OE        BIT(0)

/* REG_G4_PIN_SD2_CLK */

#define BIT_G4_PIN_SD2_CLK_FUN_DRV(x)      (((x) & 0xF) << 19)
#define BIT_G4_PIN_SD2_CLK_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G4_PIN_SD2_CLK_FUN_WPUS        BIT(12)
#define BIT_G4_PIN_SD2_CLK_FUN_SE          BIT(11)
#define BIT_G4_PIN_SD2_CLK_MS              BIT(10)
#define BIT_G4_PIN_SD2_CLK_MSEN            BIT(9)
#define BIT_G4_PIN_SD2_CLK_MSOUT           BIT(8)
#define BIT_G4_PIN_SD2_CLK_FUN_WPU         BIT(7)
#define BIT_G4_PIN_SD2_CLK_FUN_WPDO        BIT(6)
#define BIT_G4_PIN_SD2_CLK_SLP_WPU         BIT(3)
#define BIT_G4_PIN_SD2_CLK_SLP_WPDO        BIT(2)
#define BIT_G4_PIN_SD2_CLK_SLP_IE          BIT(1)
#define BIT_G4_PIN_SD2_CLK_SLP_OE          BIT(0)

/* REG_G4_PIN_SD2_CMD */

#define BIT_G4_PIN_SD2_CMD_FUN_DRV(x)      (((x) & 0xF) << 19)
#define BIT_G4_PIN_SD2_CMD_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G4_PIN_SD2_CMD_FUN_WPUS        BIT(12)
#define BIT_G4_PIN_SD2_CMD_FUN_SE          BIT(11)
#define BIT_G4_PIN_SD2_CMD_MS              BIT(10)
#define BIT_G4_PIN_SD2_CMD_MSEN            BIT(9)
#define BIT_G4_PIN_SD2_CMD_MSOUT           BIT(8)
#define BIT_G4_PIN_SD2_CMD_FUN_WPU         BIT(7)
#define BIT_G4_PIN_SD2_CMD_FUN_WPDO        BIT(6)
#define BIT_G4_PIN_SD2_CMD_SLP_WPU         BIT(3)
#define BIT_G4_PIN_SD2_CMD_SLP_WPDO        BIT(2)
#define BIT_G4_PIN_SD2_CMD_SLP_IE          BIT(1)
#define BIT_G4_PIN_SD2_CMD_SLP_OE          BIT(0)

/* REG_G4_PIN_SD2_D0 */

#define BIT_G4_PIN_SD2_D0_FUN_DRV(x)       (((x) & 0xF) << 19)
#define BIT_G4_PIN_SD2_D0_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G4_PIN_SD2_D0_FUN_WPUS         BIT(12)
#define BIT_G4_PIN_SD2_D0_FUN_SE           BIT(11)
#define BIT_G4_PIN_SD2_D0_MS               BIT(10)
#define BIT_G4_PIN_SD2_D0_MSEN             BIT(9)
#define BIT_G4_PIN_SD2_D0_MSOUT            BIT(8)
#define BIT_G4_PIN_SD2_D0_FUN_WPU          BIT(7)
#define BIT_G4_PIN_SD2_D0_FUN_WPDO         BIT(6)
#define BIT_G4_PIN_SD2_D0_SLP_WPU          BIT(3)
#define BIT_G4_PIN_SD2_D0_SLP_WPDO         BIT(2)
#define BIT_G4_PIN_SD2_D0_SLP_IE           BIT(1)
#define BIT_G4_PIN_SD2_D0_SLP_OE           BIT(0)

/* REG_G4_PIN_SD2_D1 */

#define BIT_G4_PIN_SD2_D1_FUN_DRV(x)       (((x) & 0xF) << 19)
#define BIT_G4_PIN_SD2_D1_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G4_PIN_SD2_D1_FUN_WPUS         BIT(12)
#define BIT_G4_PIN_SD2_D1_FUN_SE           BIT(11)
#define BIT_G4_PIN_SD2_D1_MS               BIT(10)
#define BIT_G4_PIN_SD2_D1_MSEN             BIT(9)
#define BIT_G4_PIN_SD2_D1_MSOUT            BIT(8)
#define BIT_G4_PIN_SD2_D1_FUN_WPU          BIT(7)
#define BIT_G4_PIN_SD2_D1_FUN_WPDO         BIT(6)
#define BIT_G4_PIN_SD2_D1_SLP_WPU          BIT(3)
#define BIT_G4_PIN_SD2_D1_SLP_WPDO         BIT(2)
#define BIT_G4_PIN_SD2_D1_SLP_IE           BIT(1)
#define BIT_G4_PIN_SD2_D1_SLP_OE           BIT(0)

/* REG_G4_PIN_SD2_D2 */

#define BIT_G4_PIN_SD2_D2_FUN_DRV(x)       (((x) & 0xF) << 19)
#define BIT_G4_PIN_SD2_D2_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G4_PIN_SD2_D2_FUN_WPUS         BIT(12)
#define BIT_G4_PIN_SD2_D2_FUN_SE           BIT(11)
#define BIT_G4_PIN_SD2_D2_MS               BIT(10)
#define BIT_G4_PIN_SD2_D2_MSEN             BIT(9)
#define BIT_G4_PIN_SD2_D2_MSOUT            BIT(8)
#define BIT_G4_PIN_SD2_D2_FUN_WPU          BIT(7)
#define BIT_G4_PIN_SD2_D2_FUN_WPDO         BIT(6)
#define BIT_G4_PIN_SD2_D2_SLP_WPU          BIT(3)
#define BIT_G4_PIN_SD2_D2_SLP_WPDO         BIT(2)
#define BIT_G4_PIN_SD2_D2_SLP_IE           BIT(1)
#define BIT_G4_PIN_SD2_D2_SLP_OE           BIT(0)

/* REG_G4_PIN_SD2_D3 */

#define BIT_G4_PIN_SD2_D3_FUN_DRV(x)       (((x) & 0xF) << 19)
#define BIT_G4_PIN_SD2_D3_DSLP_EN(x)       (((x) & 0x1F) << 13)
#define BIT_G4_PIN_SD2_D3_FUN_WPUS         BIT(12)
#define BIT_G4_PIN_SD2_D3_FUN_SE           BIT(11)
#define BIT_G4_PIN_SD2_D3_MS               BIT(10)
#define BIT_G4_PIN_SD2_D3_MSEN             BIT(9)
#define BIT_G4_PIN_SD2_D3_MSOUT            BIT(8)
#define BIT_G4_PIN_SD2_D3_FUN_WPU          BIT(7)
#define BIT_G4_PIN_SD2_D3_FUN_WPDO         BIT(6)
#define BIT_G4_PIN_SD2_D3_SLP_WPU          BIT(3)
#define BIT_G4_PIN_SD2_D3_SLP_WPDO         BIT(2)
#define BIT_G4_PIN_SD2_D3_SLP_IE           BIT(1)
#define BIT_G4_PIN_SD2_D3_SLP_OE           BIT(0)

/* REG_G4_PIN_SD2_DUMMY */

#define BIT_G4_PIN_SD2_DUMMY_FUN_DRV(x)    (((x) & 0xF) << 19)
#define BIT_G4_PIN_SD2_DUMMY_DSLP_EN(x)    (((x) & 0x1F) << 13)
#define BIT_G4_PIN_SD2_DUMMY_FUN_WPUS      BIT(12)
#define BIT_G4_PIN_SD2_DUMMY_FUN_SE        BIT(11)
#define BIT_G4_PIN_SD2_DUMMY_MS            BIT(10)
#define BIT_G4_PIN_SD2_DUMMY_MSEN          BIT(9)
#define BIT_G4_PIN_SD2_DUMMY_MSOUT         BIT(8)
#define BIT_G4_PIN_SD2_DUMMY_FUN_WPU       BIT(7)
#define BIT_G4_PIN_SD2_DUMMY_FUN_WPDO      BIT(6)
#define BIT_G4_PIN_SD2_DUMMY_SLP_WPU       BIT(3)
#define BIT_G4_PIN_SD2_DUMMY_SLP_WPDO      BIT(2)
#define BIT_G4_PIN_SD2_DUMMY_SLP_IE        BIT(1)
#define BIT_G4_PIN_SD2_DUMMY_SLP_OE        BIT(0)


#endif /* G4_PIN_H */


