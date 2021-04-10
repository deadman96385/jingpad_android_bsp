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


#ifndef G2_PIN_H
#define G2_PIN_H

#define CTL_BASE_G2_PIN 0x402A0000


#define REG_G2_PIN_U0TXD         ( CTL_BASE_G2_PIN + 0x0484 )
#define REG_G2_PIN_U0RXD         ( CTL_BASE_G2_PIN + 0x0488 )
#define REG_G2_PIN_U0CTS         ( CTL_BASE_G2_PIN + 0x048C )
#define REG_G2_PIN_U0RTS         ( CTL_BASE_G2_PIN + 0x0490 )
#define REG_G2_PIN_U1TXD         ( CTL_BASE_G2_PIN + 0x0494 )
#define REG_G2_PIN_U1RXD         ( CTL_BASE_G2_PIN + 0x0498 )
#define REG_G2_PIN_U2TXD         ( CTL_BASE_G2_PIN + 0x049C )
#define REG_G2_PIN_U2RXD         ( CTL_BASE_G2_PIN + 0x04A0 )
#define REG_G2_PIN_EXTINT9       ( CTL_BASE_G2_PIN + 0x04A4 )
#define REG_G2_PIN_EXTINT10      ( CTL_BASE_G2_PIN + 0x04A8 )

/* REG_G2_PIN_U0TXD */

#define BIT_G2_PIN_U0TXD_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G2_PIN_U0TXD_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G2_PIN_U0TXD_FUN_WPUS       BIT(12)
#define BIT_G2_PIN_U0TXD_FUN_SE         BIT(11)
#define BIT_G2_PIN_U0TXD_DUMY           BIT(10)
#define BIT_G2_PIN_U0TXD_FUN_WPU        BIT(7)
#define BIT_G2_PIN_U0TXD_FUN_WPDO       BIT(6)
#define BIT_G2_PIN_U0TXD_SLP_WPU        BIT(3)
#define BIT_G2_PIN_U0TXD_SLP_WPDO       BIT(2)
#define BIT_G2_PIN_U0TXD_SLP_IE         BIT(1)
#define BIT_G2_PIN_U0TXD_SLP_OE         BIT(0)

/* REG_G2_PIN_U0RXD */

#define BIT_G2_PIN_U0RXD_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G2_PIN_U0RXD_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G2_PIN_U0RXD_FUN_WPUS       BIT(12)
#define BIT_G2_PIN_U0RXD_FUN_SE         BIT(11)
#define BIT_G2_PIN_U0RXD_DUMY           BIT(10)
#define BIT_G2_PIN_U0RXD_FUN_WPU        BIT(7)
#define BIT_G2_PIN_U0RXD_FUN_WPDO       BIT(6)
#define BIT_G2_PIN_U0RXD_SLP_WPU        BIT(3)
#define BIT_G2_PIN_U0RXD_SLP_WPDO       BIT(2)
#define BIT_G2_PIN_U0RXD_SLP_IE         BIT(1)
#define BIT_G2_PIN_U0RXD_SLP_OE         BIT(0)

/* REG_G2_PIN_U0CTS */

#define BIT_G2_PIN_U0CTS_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G2_PIN_U0CTS_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G2_PIN_U0CTS_FUN_WPUS       BIT(12)
#define BIT_G2_PIN_U0CTS_FUN_SE         BIT(11)
#define BIT_G2_PIN_U0CTS_DUMY           BIT(10)
#define BIT_G2_PIN_U0CTS_FUN_WPU        BIT(7)
#define BIT_G2_PIN_U0CTS_FUN_WPDO       BIT(6)
#define BIT_G2_PIN_U0CTS_SLP_WPU        BIT(3)
#define BIT_G2_PIN_U0CTS_SLP_WPDO       BIT(2)
#define BIT_G2_PIN_U0CTS_SLP_IE         BIT(1)
#define BIT_G2_PIN_U0CTS_SLP_OE         BIT(0)

/* REG_G2_PIN_U0RTS */

#define BIT_G2_PIN_U0RTS_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G2_PIN_U0RTS_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G2_PIN_U0RTS_FUN_WPUS       BIT(12)
#define BIT_G2_PIN_U0RTS_FUN_SE         BIT(11)
#define BIT_G2_PIN_U0RTS_DUMY           BIT(10)
#define BIT_G2_PIN_U0RTS_FUN_WPU        BIT(7)
#define BIT_G2_PIN_U0RTS_FUN_WPDO       BIT(6)
#define BIT_G2_PIN_U0RTS_SLP_WPU        BIT(3)
#define BIT_G2_PIN_U0RTS_SLP_WPDO       BIT(2)
#define BIT_G2_PIN_U0RTS_SLP_IE         BIT(1)
#define BIT_G2_PIN_U0RTS_SLP_OE         BIT(0)

/* REG_G2_PIN_U1TXD */

#define BIT_G2_PIN_U1TXD_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G2_PIN_U1TXD_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G2_PIN_U1TXD_FUN_WPUS       BIT(12)
#define BIT_G2_PIN_U1TXD_FUN_SE         BIT(11)
#define BIT_G2_PIN_U1TXD_DUMY           BIT(10)
#define BIT_G2_PIN_U1TXD_FUN_WPU        BIT(7)
#define BIT_G2_PIN_U1TXD_FUN_WPDO       BIT(6)
#define BIT_G2_PIN_U1TXD_SLP_WPU        BIT(3)
#define BIT_G2_PIN_U1TXD_SLP_WPDO       BIT(2)
#define BIT_G2_PIN_U1TXD_SLP_IE         BIT(1)
#define BIT_G2_PIN_U1TXD_SLP_OE         BIT(0)

/* REG_G2_PIN_U1RXD */

#define BIT_G2_PIN_U1RXD_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G2_PIN_U1RXD_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G2_PIN_U1RXD_FUN_WPUS       BIT(12)
#define BIT_G2_PIN_U1RXD_FUN_SE         BIT(11)
#define BIT_G2_PIN_U1RXD_DUMY           BIT(10)
#define BIT_G2_PIN_U1RXD_FUN_WPU        BIT(7)
#define BIT_G2_PIN_U1RXD_FUN_WPDO       BIT(6)
#define BIT_G2_PIN_U1RXD_SLP_WPU        BIT(3)
#define BIT_G2_PIN_U1RXD_SLP_WPDO       BIT(2)
#define BIT_G2_PIN_U1RXD_SLP_IE         BIT(1)
#define BIT_G2_PIN_U1RXD_SLP_OE         BIT(0)

/* REG_G2_PIN_U2TXD */

#define BIT_G2_PIN_U2TXD_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G2_PIN_U2TXD_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G2_PIN_U2TXD_FUN_WPUS       BIT(12)
#define BIT_G2_PIN_U2TXD_FUN_SE         BIT(11)
#define BIT_G2_PIN_U2TXD_DUMY           BIT(10)
#define BIT_G2_PIN_U2TXD_FUN_WPU        BIT(7)
#define BIT_G2_PIN_U2TXD_FUN_WPDO       BIT(6)
#define BIT_G2_PIN_U2TXD_SLP_WPU        BIT(3)
#define BIT_G2_PIN_U2TXD_SLP_WPDO       BIT(2)
#define BIT_G2_PIN_U2TXD_SLP_IE         BIT(1)
#define BIT_G2_PIN_U2TXD_SLP_OE         BIT(0)

/* REG_G2_PIN_U2RXD */

#define BIT_G2_PIN_U2RXD_FUN_DRV(x)     (((x) & 0x3) << 19)
#define BIT_G2_PIN_U2RXD_DSLP_EN(x)     (((x) & 0x1F) << 13)
#define BIT_G2_PIN_U2RXD_FUN_WPUS       BIT(12)
#define BIT_G2_PIN_U2RXD_FUN_SE         BIT(11)
#define BIT_G2_PIN_U2RXD_DUMY           BIT(10)
#define BIT_G2_PIN_U2RXD_FUN_WPU        BIT(7)
#define BIT_G2_PIN_U2RXD_FUN_WPDO       BIT(6)
#define BIT_G2_PIN_U2RXD_SLP_WPU        BIT(3)
#define BIT_G2_PIN_U2RXD_SLP_WPDO       BIT(2)
#define BIT_G2_PIN_U2RXD_SLP_IE         BIT(1)
#define BIT_G2_PIN_U2RXD_SLP_OE         BIT(0)

/* REG_G2_PIN_EXTINT9 */

#define BIT_G2_PIN_EXTINT9_FUN_DRV(x)   (((x) & 0x3) << 19)
#define BIT_G2_PIN_EXTINT9_DSLP_EN(x)   (((x) & 0x1F) << 13)
#define BIT_G2_PIN_EXTINT9_FUN_WPUS     BIT(12)
#define BIT_G2_PIN_EXTINT9_FUN_SE       BIT(11)
#define BIT_G2_PIN_EXTINT9_DUMY         BIT(10)
#define BIT_G2_PIN_EXTINT9_FUN_WPU      BIT(7)
#define BIT_G2_PIN_EXTINT9_FUN_WPDO     BIT(6)
#define BIT_G2_PIN_EXTINT9_SLP_WPU      BIT(3)
#define BIT_G2_PIN_EXTINT9_SLP_WPDO     BIT(2)
#define BIT_G2_PIN_EXTINT9_SLP_IE       BIT(1)
#define BIT_G2_PIN_EXTINT9_SLP_OE       BIT(0)

/* REG_G2_PIN_EXTINT10 */

#define BIT_G2_PIN_EXTINT10_FUN_DRV(x)  (((x) & 0x3) << 19)
#define BIT_G2_PIN_EXTINT10_DSLP_EN(x)  (((x) & 0x1F) << 13)
#define BIT_G2_PIN_EXTINT10_FUN_WPUS    BIT(12)
#define BIT_G2_PIN_EXTINT10_FUN_SE      BIT(11)
#define BIT_G2_PIN_EXTINT10_DUMY        BIT(10)
#define BIT_G2_PIN_EXTINT10_FUN_WPU     BIT(7)
#define BIT_G2_PIN_EXTINT10_FUN_WPDO    BIT(6)
#define BIT_G2_PIN_EXTINT10_SLP_WPU     BIT(3)
#define BIT_G2_PIN_EXTINT10_SLP_WPDO    BIT(2)
#define BIT_G2_PIN_EXTINT10_SLP_IE      BIT(1)
#define BIT_G2_PIN_EXTINT10_SLP_OE      BIT(0)


#endif /* G2_PIN_H */


