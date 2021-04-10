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


#ifndef G3_PIN_H
#define G3_PIN_H

#define CTL_BASE_G3_PIN 0x402A0000


#define REG_G3_PIN_EMMC_D7         ( CTL_BASE_G3_PIN + 0x04AC )
#define REG_G3_PIN_EMMC_D3         ( CTL_BASE_G3_PIN + 0x04B0 )
#define REG_G3_PIN_EMMC_CMD        ( CTL_BASE_G3_PIN + 0x04B4 )
#define REG_G3_PIN_EMMC_D2         ( CTL_BASE_G3_PIN + 0x04B8 )
#define REG_G3_PIN_EMMC_DUMMY      ( CTL_BASE_G3_PIN + 0x04BC )
#define REG_G3_PIN_EMMC_D4         ( CTL_BASE_G3_PIN + 0x04C0 )
#define REG_G3_PIN_EMMC_CLK        ( CTL_BASE_G3_PIN + 0x04C4 )
#define REG_G3_PIN_EMMC_D0         ( CTL_BASE_G3_PIN + 0x04C8 )
#define REG_G3_PIN_EMMC_DS         ( CTL_BASE_G3_PIN + 0x04CC )
#define REG_G3_PIN_EMMC_RST        ( CTL_BASE_G3_PIN + 0x04D0 )
#define REG_G3_PIN_EMMC_D6         ( CTL_BASE_G3_PIN + 0x04D4 )
#define REG_G3_PIN_EMMC_D1         ( CTL_BASE_G3_PIN + 0x04D8 )
#define REG_G3_PIN_EMMC_D5         ( CTL_BASE_G3_PIN + 0x04DC )
#define REG_G3_PIN_NF_DATA_2       ( CTL_BASE_G3_PIN + 0x04E0 )
#define REG_G3_PIN_NF_DATA_0       ( CTL_BASE_G3_PIN + 0x04E4 )
#define REG_G3_PIN_NF_DATA_1       ( CTL_BASE_G3_PIN + 0x04E8 )
#define REG_G3_PIN_NF_WEN          ( CTL_BASE_G3_PIN + 0x04EC )
#define REG_G3_PIN_NF_CEN0         ( CTL_BASE_G3_PIN + 0x04F0 )

/* REG_G3_PIN_EMMC_D7 */

#define BIT_G3_PIN_EMMC_D7_FUN_DRV(x)     (((x) & 0x7) << 19)
#define BIT_G3_PIN_EMMC_D7_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G3_PIN_EMMC_D7_FUN_WPUS       BIT(12)
#define BIT_G3_PIN_EMMC_D7_FUN_SE         BIT(11)
#define BIT_G3_PIN_EMMC_D7_DUMY           BIT(10)
#define BIT_G3_PIN_EMMC_D7_FUN_WPU        BIT(7)
#define BIT_G3_PIN_EMMC_D7_FUN_WPDO       BIT(6)
#define BIT_G3_PIN_EMMC_D7_SLP_WPU        BIT(3)
#define BIT_G3_PIN_EMMC_D7_SLP_WPDO       BIT(2)
#define BIT_G3_PIN_EMMC_D7_SLP_IE         BIT(1)
#define BIT_G3_PIN_EMMC_D7_SLP_OE         BIT(0)

/* REG_G3_PIN_EMMC_D3 */

#define BIT_G3_PIN_EMMC_D3_FUN_DRV(x)     (((x) & 0x7) << 19)
#define BIT_G3_PIN_EMMC_D3_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G3_PIN_EMMC_D3_FUN_WPUS       BIT(12)
#define BIT_G3_PIN_EMMC_D3_FUN_SE         BIT(11)
#define BIT_G3_PIN_EMMC_D3_DUMY           BIT(10)
#define BIT_G3_PIN_EMMC_D3_FUN_WPU        BIT(7)
#define BIT_G3_PIN_EMMC_D3_FUN_WPDO       BIT(6)
#define BIT_G3_PIN_EMMC_D3_SLP_WPU        BIT(3)
#define BIT_G3_PIN_EMMC_D3_SLP_WPDO       BIT(2)
#define BIT_G3_PIN_EMMC_D3_SLP_IE         BIT(1)
#define BIT_G3_PIN_EMMC_D3_SLP_OE         BIT(0)

/* REG_G3_PIN_EMMC_CMD */

#define BIT_G3_PIN_EMMC_CMD_FUN_DRV(x)    (((x) & 0x7) << 19)
#define BIT_G3_PIN_EMMC_CMD_DSLP_EN(x)    (((x) & 0x1F) << 13)
#define BIT_G3_PIN_EMMC_CMD_FUN_WPUS      BIT(12)
#define BIT_G3_PIN_EMMC_CMD_FUN_SE        BIT(11)
#define BIT_G3_PIN_EMMC_CMD_DUMY          BIT(10)
#define BIT_G3_PIN_EMMC_CMD_FUN_WPU       BIT(7)
#define BIT_G3_PIN_EMMC_CMD_FUN_WPDO      BIT(6)
#define BIT_G3_PIN_EMMC_CMD_SLP_WPU       BIT(3)
#define BIT_G3_PIN_EMMC_CMD_SLP_WPDO      BIT(2)
#define BIT_G3_PIN_EMMC_CMD_SLP_IE        BIT(1)
#define BIT_G3_PIN_EMMC_CMD_SLP_OE        BIT(0)

/* REG_G3_PIN_EMMC_D2 */

#define BIT_G3_PIN_EMMC_D2_FUN_DRV(x)     (((x) & 0x7) << 19)
#define BIT_G3_PIN_EMMC_D2_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G3_PIN_EMMC_D2_FUN_WPUS       BIT(12)
#define BIT_G3_PIN_EMMC_D2_FUN_SE         BIT(11)
#define BIT_G3_PIN_EMMC_D2_DUMY           BIT(10)
#define BIT_G3_PIN_EMMC_D2_FUN_WPU        BIT(7)
#define BIT_G3_PIN_EMMC_D2_FUN_WPDO       BIT(6)
#define BIT_G3_PIN_EMMC_D2_SLP_WPU        BIT(3)
#define BIT_G3_PIN_EMMC_D2_SLP_WPDO       BIT(2)
#define BIT_G3_PIN_EMMC_D2_SLP_IE         BIT(1)
#define BIT_G3_PIN_EMMC_D2_SLP_OE         BIT(0)

/* REG_G3_PIN_EMMC_DUMMY */

#define BIT_G3_PIN_EMMC_DUMMY_FUN_DRV(x)  (((x) & 0x7) << 19)
#define BIT_G3_PIN_EMMC_DUMMY_DSLP_EN(x)  (((x) & 0x1F) << 13)
#define BIT_G3_PIN_EMMC_DUMMY_FUN_WPUS    BIT(12)
#define BIT_G3_PIN_EMMC_DUMMY_FUN_SE      BIT(11)
#define BIT_G3_PIN_EMMC_DUMMY_DUMY        BIT(10)
#define BIT_G3_PIN_EMMC_DUMMY_FUN_WPU     BIT(7)
#define BIT_G3_PIN_EMMC_DUMMY_FUN_WPDO    BIT(6)
#define BIT_G3_PIN_EMMC_DUMMY_SLP_WPU     BIT(3)
#define BIT_G3_PIN_EMMC_DUMMY_SLP_WPDO    BIT(2)
#define BIT_G3_PIN_EMMC_DUMMY_SLP_IE      BIT(1)
#define BIT_G3_PIN_EMMC_DUMMY_SLP_OE      BIT(0)

/* REG_G3_PIN_EMMC_D4 */

#define BIT_G3_PIN_EMMC_D4_FUN_DRV(x)     (((x) & 0x7) << 19)
#define BIT_G3_PIN_EMMC_D4_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G3_PIN_EMMC_D4_FUN_WPUS       BIT(12)
#define BIT_G3_PIN_EMMC_D4_FUN_SE         BIT(11)
#define BIT_G3_PIN_EMMC_D4_DUMY           BIT(10)
#define BIT_G3_PIN_EMMC_D4_FUN_WPU        BIT(7)
#define BIT_G3_PIN_EMMC_D4_FUN_WPDO       BIT(6)
#define BIT_G3_PIN_EMMC_D4_SLP_WPU        BIT(3)
#define BIT_G3_PIN_EMMC_D4_SLP_WPDO       BIT(2)
#define BIT_G3_PIN_EMMC_D4_SLP_IE         BIT(1)
#define BIT_G3_PIN_EMMC_D4_SLP_OE         BIT(0)

/* REG_G3_PIN_EMMC_CLK */

#define BIT_G3_PIN_EMMC_CLK_FUN_DRV(x)    (((x) & 0x7) << 19)
#define BIT_G3_PIN_EMMC_CLK_DSLP_EN(x)    (((x) & 0x1F) << 13)
#define BIT_G3_PIN_EMMC_CLK_FUN_WPUS      BIT(12)
#define BIT_G3_PIN_EMMC_CLK_FUN_SE        BIT(11)
#define BIT_G3_PIN_EMMC_CLK_DUMY          BIT(10)
#define BIT_G3_PIN_EMMC_CLK_FUN_WPU       BIT(7)
#define BIT_G3_PIN_EMMC_CLK_FUN_WPDO      BIT(6)
#define BIT_G3_PIN_EMMC_CLK_SLP_WPU       BIT(3)
#define BIT_G3_PIN_EMMC_CLK_SLP_WPDO      BIT(2)
#define BIT_G3_PIN_EMMC_CLK_SLP_IE        BIT(1)
#define BIT_G3_PIN_EMMC_CLK_SLP_OE        BIT(0)

/* REG_G3_PIN_EMMC_D0 */

#define BIT_G3_PIN_EMMC_D0_FUN_DRV(x)     (((x) & 0x7) << 19)
#define BIT_G3_PIN_EMMC_D0_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G3_PIN_EMMC_D0_FUN_WPUS       BIT(12)
#define BIT_G3_PIN_EMMC_D0_FUN_SE         BIT(11)
#define BIT_G3_PIN_EMMC_D0_DUMY           BIT(10)
#define BIT_G3_PIN_EMMC_D0_FUN_WPU        BIT(7)
#define BIT_G3_PIN_EMMC_D0_FUN_WPDO       BIT(6)
#define BIT_G3_PIN_EMMC_D0_SLP_WPU        BIT(3)
#define BIT_G3_PIN_EMMC_D0_SLP_WPDO       BIT(2)
#define BIT_G3_PIN_EMMC_D0_SLP_IE         BIT(1)
#define BIT_G3_PIN_EMMC_D0_SLP_OE         BIT(0)

/* REG_G3_PIN_EMMC_DS */

#define BIT_G3_PIN_EMMC_DS_FUN_DRV(x)     (((x) & 0x7) << 19)
#define BIT_G3_PIN_EMMC_DS_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G3_PIN_EMMC_DS_FUN_WPUS       BIT(12)
#define BIT_G3_PIN_EMMC_DS_FUN_SE         BIT(11)
#define BIT_G3_PIN_EMMC_DS_DUMY           BIT(10)
#define BIT_G3_PIN_EMMC_DS_FUN_WPU        BIT(7)
#define BIT_G3_PIN_EMMC_DS_FUN_WPDO       BIT(6)
#define BIT_G3_PIN_EMMC_DS_SLP_WPU        BIT(3)
#define BIT_G3_PIN_EMMC_DS_SLP_WPDO       BIT(2)
#define BIT_G3_PIN_EMMC_DS_SLP_IE         BIT(1)
#define BIT_G3_PIN_EMMC_DS_SLP_OE         BIT(0)

/* REG_G3_PIN_EMMC_RST */

#define BIT_G3_PIN_EMMC_RST_FUN_DRV(x)    (((x) & 0x7) << 19)
#define BIT_G3_PIN_EMMC_RST_DSLP_EN(x)    (((x) & 0x1F) << 13)
#define BIT_G3_PIN_EMMC_RST_FUN_WPUS      BIT(12)
#define BIT_G3_PIN_EMMC_RST_FUN_SE        BIT(11)
#define BIT_G3_PIN_EMMC_RST_DUMY          BIT(10)
#define BIT_G3_PIN_EMMC_RST_FUN_WPU       BIT(7)
#define BIT_G3_PIN_EMMC_RST_FUN_WPDO      BIT(6)
#define BIT_G3_PIN_EMMC_RST_SLP_WPU       BIT(3)
#define BIT_G3_PIN_EMMC_RST_SLP_WPDO      BIT(2)
#define BIT_G3_PIN_EMMC_RST_SLP_IE        BIT(1)
#define BIT_G3_PIN_EMMC_RST_SLP_OE        BIT(0)

/* REG_G3_PIN_EMMC_D6 */

#define BIT_G3_PIN_EMMC_D6_FUN_DRV(x)     (((x) & 0x7) << 19)
#define BIT_G3_PIN_EMMC_D6_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G3_PIN_EMMC_D6_FUN_WPUS       BIT(12)
#define BIT_G3_PIN_EMMC_D6_FUN_SE         BIT(11)
#define BIT_G3_PIN_EMMC_D6_DUMY           BIT(10)
#define BIT_G3_PIN_EMMC_D6_FUN_WPU        BIT(7)
#define BIT_G3_PIN_EMMC_D6_FUN_WPDO       BIT(6)
#define BIT_G3_PIN_EMMC_D6_SLP_WPU        BIT(3)
#define BIT_G3_PIN_EMMC_D6_SLP_WPDO       BIT(2)
#define BIT_G3_PIN_EMMC_D6_SLP_IE         BIT(1)
#define BIT_G3_PIN_EMMC_D6_SLP_OE         BIT(0)

/* REG_G3_PIN_EMMC_D1 */

#define BIT_G3_PIN_EMMC_D1_FUN_DRV(x)     (((x) & 0x7) << 19)
#define BIT_G3_PIN_EMMC_D1_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G3_PIN_EMMC_D1_FUN_WPUS       BIT(12)
#define BIT_G3_PIN_EMMC_D1_FUN_SE         BIT(11)
#define BIT_G3_PIN_EMMC_D1_DUMY           BIT(10)
#define BIT_G3_PIN_EMMC_D1_FUN_WPU        BIT(7)
#define BIT_G3_PIN_EMMC_D1_FUN_WPDO       BIT(6)
#define BIT_G3_PIN_EMMC_D1_SLP_WPU        BIT(3)
#define BIT_G3_PIN_EMMC_D1_SLP_WPDO       BIT(2)
#define BIT_G3_PIN_EMMC_D1_SLP_IE         BIT(1)
#define BIT_G3_PIN_EMMC_D1_SLP_OE         BIT(0)

/* REG_G3_PIN_EMMC_D5 */

#define BIT_G3_PIN_EMMC_D5_FUN_DRV(x)     (((x) & 0x7) << 19)
#define BIT_G3_PIN_EMMC_D5_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G3_PIN_EMMC_D5_FUN_WPUS       BIT(12)
#define BIT_G3_PIN_EMMC_D5_FUN_SE         BIT(11)
#define BIT_G3_PIN_EMMC_D5_DUMY           BIT(10)
#define BIT_G3_PIN_EMMC_D5_FUN_WPU        BIT(7)
#define BIT_G3_PIN_EMMC_D5_FUN_WPDO       BIT(6)
#define BIT_G3_PIN_EMMC_D5_SLP_WPU        BIT(3)
#define BIT_G3_PIN_EMMC_D5_SLP_WPDO       BIT(2)
#define BIT_G3_PIN_EMMC_D5_SLP_IE         BIT(1)
#define BIT_G3_PIN_EMMC_D5_SLP_OE         BIT(0)

/* REG_G3_PIN_NF_DATA_2 */

#define BIT_G3_PIN_NF_DATA_2_FUN_DRV(x)   (((x) & 0x7) << 19)
#define BIT_G3_PIN_NF_DATA_2_DSLP_EN(x)   (((x) & 0x1F) << 13)
#define BIT_G3_PIN_NF_DATA_2_FUN_WPUS     BIT(12)
#define BIT_G3_PIN_NF_DATA_2_FUN_SE       BIT(11)
#define BIT_G3_PIN_NF_DATA_2_DUMY         BIT(10)
#define BIT_G3_PIN_NF_DATA_2_FUN_WPU      BIT(7)
#define BIT_G3_PIN_NF_DATA_2_FUN_WPDO     BIT(6)
#define BIT_G3_PIN_NF_DATA_2_SLP_WPU      BIT(3)
#define BIT_G3_PIN_NF_DATA_2_SLP_WPDO     BIT(2)
#define BIT_G3_PIN_NF_DATA_2_SLP_IE       BIT(1)
#define BIT_G3_PIN_NF_DATA_2_SLP_OE       BIT(0)

/* REG_G3_PIN_NF_DATA_0 */

#define BIT_G3_PIN_NF_DATA_0_FUN_DRV(x)   (((x) & 0x7) << 19)
#define BIT_G3_PIN_NF_DATA_0_DSLP_EN(x)   (((x) & 0x1F) << 13)
#define BIT_G3_PIN_NF_DATA_0_FUN_WPUS     BIT(12)
#define BIT_G3_PIN_NF_DATA_0_FUN_SE       BIT(11)
#define BIT_G3_PIN_NF_DATA_0_DUMY         BIT(10)
#define BIT_G3_PIN_NF_DATA_0_FUN_WPU      BIT(7)
#define BIT_G3_PIN_NF_DATA_0_FUN_WPDO     BIT(6)
#define BIT_G3_PIN_NF_DATA_0_SLP_WPU      BIT(3)
#define BIT_G3_PIN_NF_DATA_0_SLP_WPDO     BIT(2)
#define BIT_G3_PIN_NF_DATA_0_SLP_IE       BIT(1)
#define BIT_G3_PIN_NF_DATA_0_SLP_OE       BIT(0)

/* REG_G3_PIN_NF_DATA_1 */

#define BIT_G3_PIN_NF_DATA_1_FUN_DRV(x)   (((x) & 0x7) << 19)
#define BIT_G3_PIN_NF_DATA_1_DSLP_EN(x)   (((x) & 0x1F) << 13)
#define BIT_G3_PIN_NF_DATA_1_FUN_WPUS     BIT(12)
#define BIT_G3_PIN_NF_DATA_1_FUN_SE       BIT(11)
#define BIT_G3_PIN_NF_DATA_1_DUMY         BIT(10)
#define BIT_G3_PIN_NF_DATA_1_FUN_WPU      BIT(7)
#define BIT_G3_PIN_NF_DATA_1_FUN_WPDO     BIT(6)
#define BIT_G3_PIN_NF_DATA_1_SLP_WPU      BIT(3)
#define BIT_G3_PIN_NF_DATA_1_SLP_WPDO     BIT(2)
#define BIT_G3_PIN_NF_DATA_1_SLP_IE       BIT(1)
#define BIT_G3_PIN_NF_DATA_1_SLP_OE       BIT(0)

/* REG_G3_PIN_NF_WEN */

#define BIT_G3_PIN_NF_WEN_FUN_DRV(x)      (((x) & 0x7) << 19)
#define BIT_G3_PIN_NF_WEN_DSLP_EN(x)      (((x) & 0x1F) << 13)
#define BIT_G3_PIN_NF_WEN_FUN_WPUS        BIT(12)
#define BIT_G3_PIN_NF_WEN_FUN_SE          BIT(11)
#define BIT_G3_PIN_NF_WEN_DUMY            BIT(10)
#define BIT_G3_PIN_NF_WEN_FUN_WPU         BIT(7)
#define BIT_G3_PIN_NF_WEN_FUN_WPDO        BIT(6)
#define BIT_G3_PIN_NF_WEN_SLP_WPU         BIT(3)
#define BIT_G3_PIN_NF_WEN_SLP_WPDO        BIT(2)
#define BIT_G3_PIN_NF_WEN_SLP_IE          BIT(1)
#define BIT_G3_PIN_NF_WEN_SLP_OE          BIT(0)

/* REG_G3_PIN_NF_CEN0 */

#define BIT_G3_PIN_NF_CEN0_FUN_DRV(x)     (((x) & 0x7) << 19)
#define BIT_G3_PIN_NF_CEN0_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G3_PIN_NF_CEN0_FUN_WPUS       BIT(12)
#define BIT_G3_PIN_NF_CEN0_FUN_SE         BIT(11)
#define BIT_G3_PIN_NF_CEN0_DUMY           BIT(10)
#define BIT_G3_PIN_NF_CEN0_FUN_WPU        BIT(7)
#define BIT_G3_PIN_NF_CEN0_FUN_WPDO       BIT(6)
#define BIT_G3_PIN_NF_CEN0_SLP_WPU        BIT(3)
#define BIT_G3_PIN_NF_CEN0_SLP_WPDO       BIT(2)
#define BIT_G3_PIN_NF_CEN0_SLP_IE         BIT(1)
#define BIT_G3_PIN_NF_CEN0_SLP_OE         BIT(0)


#endif /* G3_PIN_H */


