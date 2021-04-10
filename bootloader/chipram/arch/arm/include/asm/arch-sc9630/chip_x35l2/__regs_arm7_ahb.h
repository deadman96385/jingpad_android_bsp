/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _ARM7_AHB_REG_H
#define _ARM7_AHB_REG_H

#define CTL_BASE_ARM7_AHB SPRD_ARM7_AHB_PHYS


#define REG_ARM7_AHB_ARM7_EB            ( CTL_BASE_ARM7_AHB + 0x0000 )
#define REG_ARM7_AHB_ARM7_SOFT_RST      ( CTL_BASE_ARM7_AHB + 0x0004 )
#define REG_ARM7_AHB_AHB_PAUSE          ( CTL_BASE_ARM7_AHB + 0x0008 )
#define REG_ARM7_AHB_ARM7_SLP_CTL       ( CTL_BASE_ARM7_AHB + 0x000C )
#define REG_ARM7_AHB_ARM7_CLK_EMC_CTRL  ( CTL_BASE_ARM7_AHB + 0x0010 )

/*---------------------------------------------------------------------------
// Register Name   : REG_ARM7_AHB_ARM7_EB
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ARM7_AHB_ARM7_GPIO_EB                          BIT(10)
#define BIT_ARM7_AHB_ARM7_UART_EB                          BIT(9)
#define BIT_ARM7_AHB_ARM7_TMR_EB                           BIT(8)
#define BIT_ARM7_AHB_ARM7_SYST_EB                          BIT(7)
#define BIT_ARM7_AHB_ARM7_WDG_EB                           BIT(6)
#define BIT_ARM7_AHB_ARM7_EIC_EB                           BIT(5)
#define BIT_ARM7_AHB_ARM7_INTC_EB                          BIT(4)
#define BIT_ARM7_AHB_ARM7_EFUSE_EB                         BIT(3)
#define BIT_ARM7_AHB_ARM7_IMC_EB                           BIT(2)
#define BIT_ARM7_AHB_ARM7_TIC_EB                           BIT(1)
#define BIT_ARM7_AHB_ARM7_DMA_EB                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ARM7_AHB_ARM7_SOFT_RST
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ARM7_AHB_ARM7_GPIO_SOFT_RST                    BIT(10)
#define BIT_ARM7_AHB_ARM7_UART_SOFT_RST                    BIT(9)
#define BIT_ARM7_AHB_ARM7_TMR_SOFT_RST                     BIT(8)
#define BIT_ARM7_AHB_ARM7_SYST_SOFT_RST                    BIT(7)
#define BIT_ARM7_AHB_ARM7_WDG_SOFT_RST                     BIT(6)
#define BIT_ARM7_AHB_ARM7_EIC_SOFT_RST                     BIT(5)
#define BIT_ARM7_AHB_ARM7_INTC_SOFT_RST                    BIT(4)
#define BIT_ARM7_AHB_ARM7_EFUSE_SOFT_RST                   BIT(3)
#define BIT_ARM7_AHB_ARM7_IMC_SOFT_RST                     BIT(2)
#define BIT_ARM7_AHB_ARM7_TIC_SOFT_RST                     BIT(1)
#define BIT_ARM7_AHB_ARM7_ARCH_SOFT_RST                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ARM7_AHB_AHB_PAUSE
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ARM7_AHB_ARM7_DEEP_SLEEP_EN                    BIT(2)
#define BIT_ARM7_AHB_ARM7_SYS_SLEEP_EN                     BIT(1)
#define BIT_ARM7_AHB_ARM7_CORE_SLEEP                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ARM7_AHB_ARM7_SLP_CTL
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ARM7_AHB_ARM7_SYS_AUTO_GATE_EN                 BIT(2)
#define BIT_ARM7_AHB_ARM7_AHB_AUTO_GATE_EN                 BIT(1)
#define BIT_ARM7_AHB_ARM7_CORE_AUTO_GATE_EN                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ARM7_AHB_ARM7_CLK_EMC_CTRL
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ARM7_AHB_ARM7_CLK_EMC_SEL(x)                   (((x) & 0x7) << 2)
#define BIT_ARM7_AHB_ARM7_CLK_EMC_DIV(x)                   (((x) & 0x3))


#endif // _ARM7_AHB_REG_H
