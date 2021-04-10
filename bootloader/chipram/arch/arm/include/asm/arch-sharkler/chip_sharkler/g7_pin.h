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


#ifndef G7_PIN_H
#define G7_PIN_H

#define CTL_BASE_G7_PIN 0x402A0000


#define REG_G7_PIN_MEMS_MIC_CLK0       ( CTL_BASE_G7_PIN + 0x0658 )
#define REG_G7_PIN_MEMS_MIC_DATA0      ( CTL_BASE_G7_PIN + 0x065C )
#define REG_G7_PIN_MEMS_MIC_CLK1       ( CTL_BASE_G7_PIN + 0x0660 )
#define REG_G7_PIN_MEMS_MIC_DATA1      ( CTL_BASE_G7_PIN + 0x0664 )

/* REG_G7_PIN_MEMS_MIC_CLK0 */

#define BIT_G7_PIN_MEMS_MIC_CLK0_FUN_DRV(x)   (((x) & 0x3) << 19)
#define BIT_G7_PIN_MEMS_MIC_CLK0_DSLP_EN(x)   (((x) & 0x1F) << 13)
#define BIT_G7_PIN_MEMS_MIC_CLK0_FUN_WPUS     BIT(12)
#define BIT_G7_PIN_MEMS_MIC_CLK0_FUN_SE       BIT(11)
#define BIT_G7_PIN_MEMS_MIC_CLK0_DUMY         BIT(10)
#define BIT_G7_PIN_MEMS_MIC_CLK0_FUN_WPU      BIT(7)
#define BIT_G7_PIN_MEMS_MIC_CLK0_FUN_WPDO     BIT(6)
#define BIT_G7_PIN_MEMS_MIC_CLK0_SLP_WPU      BIT(3)
#define BIT_G7_PIN_MEMS_MIC_CLK0_SLP_WPDO     BIT(2)
#define BIT_G7_PIN_MEMS_MIC_CLK0_SLP_IE       BIT(1)
#define BIT_G7_PIN_MEMS_MIC_CLK0_SLP_OE       BIT(0)

/* REG_G7_PIN_MEMS_MIC_DATA0 */

#define BIT_G7_PIN_MEMS_MIC_DATA0_FUN_DRV(x)  (((x) & 0x3) << 19)
#define BIT_G7_PIN_MEMS_MIC_DATA0_DSLP_EN(x)  (((x) & 0x1F) << 13)
#define BIT_G7_PIN_MEMS_MIC_DATA0_FUN_WPUS    BIT(12)
#define BIT_G7_PIN_MEMS_MIC_DATA0_FUN_SE      BIT(11)
#define BIT_G7_PIN_MEMS_MIC_DATA0_DUMY        BIT(10)
#define BIT_G7_PIN_MEMS_MIC_DATA0_FUN_WPU     BIT(7)
#define BIT_G7_PIN_MEMS_MIC_DATA0_FUN_WPDO    BIT(6)
#define BIT_G7_PIN_MEMS_MIC_DATA0_SLP_WPU     BIT(3)
#define BIT_G7_PIN_MEMS_MIC_DATA0_SLP_WPDO    BIT(2)
#define BIT_G7_PIN_MEMS_MIC_DATA0_SLP_IE      BIT(1)
#define BIT_G7_PIN_MEMS_MIC_DATA0_SLP_OE      BIT(0)

/* REG_G7_PIN_MEMS_MIC_CLK1 */

#define BIT_G7_PIN_MEMS_MIC_CLK1_FUN_DRV(x)   (((x) & 0x3) << 19)
#define BIT_G7_PIN_MEMS_MIC_CLK1_DSLP_EN(x)   (((x) & 0x1F) << 13)
#define BIT_G7_PIN_MEMS_MIC_CLK1_FUN_WPUS     BIT(12)
#define BIT_G7_PIN_MEMS_MIC_CLK1_FUN_SE       BIT(11)
#define BIT_G7_PIN_MEMS_MIC_CLK1_DUMY         BIT(10)
#define BIT_G7_PIN_MEMS_MIC_CLK1_FUN_WPU      BIT(7)
#define BIT_G7_PIN_MEMS_MIC_CLK1_FUN_WPDO     BIT(6)
#define BIT_G7_PIN_MEMS_MIC_CLK1_SLP_WPU      BIT(3)
#define BIT_G7_PIN_MEMS_MIC_CLK1_SLP_WPDO     BIT(2)
#define BIT_G7_PIN_MEMS_MIC_CLK1_SLP_IE       BIT(1)
#define BIT_G7_PIN_MEMS_MIC_CLK1_SLP_OE       BIT(0)

/* REG_G7_PIN_MEMS_MIC_DATA1 */

#define BIT_G7_PIN_MEMS_MIC_DATA1_FUN_DRV(x)  (((x) & 0x3) << 19)
#define BIT_G7_PIN_MEMS_MIC_DATA1_DSLP_EN(x)  (((x) & 0x1F) << 13)
#define BIT_G7_PIN_MEMS_MIC_DATA1_FUN_WPUS    BIT(12)
#define BIT_G7_PIN_MEMS_MIC_DATA1_FUN_SE      BIT(11)
#define BIT_G7_PIN_MEMS_MIC_DATA1_DUMY        BIT(10)
#define BIT_G7_PIN_MEMS_MIC_DATA1_FUN_WPU     BIT(7)
#define BIT_G7_PIN_MEMS_MIC_DATA1_FUN_WPDO    BIT(6)
#define BIT_G7_PIN_MEMS_MIC_DATA1_SLP_WPU     BIT(3)
#define BIT_G7_PIN_MEMS_MIC_DATA1_SLP_WPDO    BIT(2)
#define BIT_G7_PIN_MEMS_MIC_DATA1_SLP_IE      BIT(1)
#define BIT_G7_PIN_MEMS_MIC_DATA1_SLP_OE      BIT(0)


#endif /* G7_PIN_H */


