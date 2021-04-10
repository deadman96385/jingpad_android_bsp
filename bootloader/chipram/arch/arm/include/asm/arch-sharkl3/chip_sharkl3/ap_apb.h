/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2017-12-27 15:24:15
 *
 */


#ifndef AP_APB_H
#define AP_APB_H

#define CTL_BASE_AP_APB 0x71300000


#define REG_AP_APB_APB_EB                   ( CTL_BASE_AP_APB + 0x0000 )
#define REG_AP_APB_APB_RST                  ( CTL_BASE_AP_APB + 0x0004 )
#define REG_AP_APB_APB_MISC_CTRL            ( CTL_BASE_AP_APB + 0x3000 )
#define REG_AP_APB_APB_PERI_FRC_SLEEP       ( CTL_BASE_AP_APB + 0x3004 )
#define REG_AP_APB_APB_PCLK_AUTO_GATE       ( CTL_BASE_AP_APB + 0x3008 )
#define REG_AP_APB_APB_PCLK_AUTO_SLOW_SEL0  ( CTL_BASE_AP_APB + 0x300C )
#define REG_AP_APB_APB_PCLK_AUTO_SLOW_SEL1  ( CTL_BASE_AP_APB + 0x3010 )

/* REG_AP_APB_APB_EB */

#define BIT_AP_APB_I2C6_EB                      BIT(21)
#define BIT_AP_APB_I2C5_EB                      BIT(20)
#define BIT_AP_APB_SPI3_EB                      BIT(19)
#define BIT_AP_APB_SIM0_32K_EB                  BIT(18)
#define BIT_AP_APB_UART4_EB                     BIT(17)
#define BIT_AP_APB_UART3_EB                     BIT(16)
#define BIT_AP_APB_UART2_EB                     BIT(15)
#define BIT_AP_APB_UART1_EB                     BIT(14)
#define BIT_AP_APB_UART0_EB                     BIT(13)
#define BIT_AP_APB_I2C4_EB                      BIT(12)
#define BIT_AP_APB_I2C3_EB                      BIT(11)
#define BIT_AP_APB_I2C2_EB                      BIT(10)
#define BIT_AP_APB_I2C1_EB                      BIT(9)
#define BIT_AP_APB_I2C0_EB                      BIT(8)
#define BIT_AP_APB_SPI2_EB                      BIT(7)
#define BIT_AP_APB_SPI1_EB                      BIT(6)
#define BIT_AP_APB_SPI0_EB                      BIT(5)
#define BIT_AP_APB_IIS2_EB                      BIT(3)
#define BIT_AP_APB_IIS1_EB                      BIT(2)
#define BIT_AP_APB_IIS0_EB                      BIT(1)
#define BIT_AP_APB_SIM0_EB                      BIT(0)

/* REG_AP_APB_APB_RST */

#define BIT_AP_APB_I2C6_SOFT_RST                BIT(21)
#define BIT_AP_APB_I2C5_SOFT_RST                BIT(20)
#define BIT_AP_APB_SPI3_SOFT_RST                BIT(19)
#define BIT_AP_APB_SIM0_32K_SOFT_RST            BIT(18)
#define BIT_AP_APB_UART4_SOFT_RST               BIT(17)
#define BIT_AP_APB_UART3_SOFT_RST               BIT(16)
#define BIT_AP_APB_UART2_SOFT_RST               BIT(15)
#define BIT_AP_APB_UART1_SOFT_RST               BIT(14)
#define BIT_AP_APB_UART0_SOFT_RST               BIT(13)
#define BIT_AP_APB_I2C4_SOFT_RST                BIT(12)
#define BIT_AP_APB_I2C3_SOFT_RST                BIT(11)
#define BIT_AP_APB_I2C2_SOFT_RST                BIT(10)
#define BIT_AP_APB_I2C1_SOFT_RST                BIT(9)
#define BIT_AP_APB_I2C0_SOFT_RST                BIT(8)
#define BIT_AP_APB_SPI2_SOFT_RST                BIT(7)
#define BIT_AP_APB_SPI1_SOFT_RST                BIT(6)
#define BIT_AP_APB_SPI0_SOFT_RST                BIT(5)
#define BIT_AP_APB_IIS2_SOFT_RST                BIT(3)
#define BIT_AP_APB_IIS1_SOFT_RST                BIT(2)
#define BIT_AP_APB_IIS0_SOFT_RST                BIT(1)
#define BIT_AP_APB_SIM0_SOFT_RST                BIT(0)

/* REG_AP_APB_APB_MISC_CTRL */

#define BIT_AP_APB_SPI3_LCD_FMARK_IN_EB         BIT(11)
#define BIT_AP_APB_SPI2_LCD_FMARK_IN_EB         BIT(10)
#define BIT_AP_APB_SPI1_LCD_FMARK_IN_EB         BIT(9)
#define BIT_AP_APB_SPI0_LCD_FMARK_IN_EB         BIT(8)
#define BIT_AP_APB_SPI3_FMARK_POLARITY_INV      BIT(7)
#define BIT_AP_APB_SPI2_FMARK_POLARITY_INV      BIT(6)
#define BIT_AP_APB_SPI1_FMARK_POLARITY_INV      BIT(5)
#define BIT_AP_APB_SPI0_FMARK_POLARITY_INV      BIT(4)
#define BIT_AP_APB_SIM_CLK_POLARITY             BIT(0)

/* REG_AP_APB_APB_PERI_FRC_SLEEP */

#define BIT_AP_APB_SIM0_FRC_SLEEP               BIT(19)
#define BIT_AP_APB_SPI3_FRC_SLEEP               BIT(18)
#define BIT_AP_APB_SPI2_FRC_SLEEP               BIT(17)
#define BIT_AP_APB_SPI1_FRC_SLEEP               BIT(16)
#define BIT_AP_APB_SPI0_FRC_SLEEP               BIT(15)
#define BIT_AP_APB_IIS2_FRC_SLEEP               BIT(14)
#define BIT_AP_APB_IIS1_FRC_SLEEP               BIT(13)
#define BIT_AP_APB_IIS0_FRC_SLEEP               BIT(12)
#define BIT_AP_APB_I2C6_FRC_SLEEP               BIT(11)
#define BIT_AP_APB_I2C5_FRC_SLEEP               BIT(10)
#define BIT_AP_APB_I2C4_FRC_SLEEP               BIT(9)
#define BIT_AP_APB_I2C3_FRC_SLEEP               BIT(8)
#define BIT_AP_APB_I2C2_FRC_SLEEP               BIT(7)
#define BIT_AP_APB_I2C1_FRC_SLEEP               BIT(6)
#define BIT_AP_APB_I2C0_FRC_SLEEP               BIT(5)
#define BIT_AP_APB_UART4_FRC_SLEEP              BIT(4)
#define BIT_AP_APB_UART3_FRC_SLEEP              BIT(3)
#define BIT_AP_APB_UART2_FRC_SLEEP              BIT(2)
#define BIT_AP_APB_UART1_FRC_SLEEP              BIT(1)
#define BIT_AP_APB_UART0_FRC_SLEEP              BIT(0)

/* REG_AP_APB_APB_PCLK_AUTO_GATE */

#define BIT_AP_APB_SIM0_PCLK_AUTO_GATE_EB       BIT(19)
#define BIT_AP_APB_SPI3_PCLK_AUTO_GATE_EB       BIT(18)
#define BIT_AP_APB_SPI2_PCLK_AUTO_GATE_EB       BIT(17)
#define BIT_AP_APB_SPI1_PCLK_AUTO_GATE_EB       BIT(16)
#define BIT_AP_APB_SPI0_PCLK_AUTO_GATE_EB       BIT(15)
#define BIT_AP_APB_IIS2_PCLK_AUTO_GATE_EB       BIT(14)
#define BIT_AP_APB_IIS1_PCLK_AUTO_GATE_EB       BIT(13)
#define BIT_AP_APB_IIS0_PCLK_AUTO_GATE_EB       BIT(12)
#define BIT_AP_APB_I2C6_PCLK_AUTO_GATE_EB       BIT(11)
#define BIT_AP_APB_I2C5_PCLK_AUTO_GATE_EB       BIT(10)
#define BIT_AP_APB_I2C4_PCLK_AUTO_GATE_EB       BIT(9)
#define BIT_AP_APB_I2C3_PCLK_AUTO_GATE_EB       BIT(8)
#define BIT_AP_APB_I2C2_PCLK_AUTO_GATE_EB       BIT(7)
#define BIT_AP_APB_I2C1_PCLK_AUTO_GATE_EB       BIT(6)
#define BIT_AP_APB_I2C0_PCLK_AUTO_GATE_EB       BIT(5)
#define BIT_AP_APB_UART4_PCLK_AUTO_GATE_EB      BIT(4)
#define BIT_AP_APB_UART3_PCLK_AUTO_GATE_EB      BIT(3)
#define BIT_AP_APB_UART2_PCLK_AUTO_GATE_EB      BIT(2)
#define BIT_AP_APB_UART1_PCLK_AUTO_GATE_EB      BIT(1)
#define BIT_AP_APB_UART0_PCLK_AUTO_GATE_EB      BIT(0)

/* REG_AP_APB_APB_PCLK_AUTO_SLOW_SEL0 */

#define BIT_AP_APB_I2C4_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 27)
#define BIT_AP_APB_I2C3_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 24)
#define BIT_AP_APB_I2C2_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 21)
#define BIT_AP_APB_I2C1_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 18)
#define BIT_AP_APB_I2C0_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 15)
#define BIT_AP_APB_UART4_PCLK_AUTO_SLOW_SEL(x)  (((x) & 0x7) << 12)
#define BIT_AP_APB_UART3_PCLK_AUTO_SLOW_SEL(x)  (((x) & 0x7) << 9)
#define BIT_AP_APB_UART2_PCLK_AUTO_SLOW_SEL(x)  (((x) & 0x7) << 6)
#define BIT_AP_APB_UART1_PCLK_AUTO_SLOW_SEL(x)  (((x) & 0x7) << 3)
#define BIT_AP_APB_UART0_PCLK_AUTO_SLOW_SEL(x)  (((x) & 0x7))

/* REG_AP_APB_APB_PCLK_AUTO_SLOW_SEL1 */

#define BIT_AP_APB_SIM0_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 27)
#define BIT_AP_APB_SPI3_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 24)
#define BIT_AP_APB_SPI2_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 21)
#define BIT_AP_APB_SPI1_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 18)
#define BIT_AP_APB_SPI0_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 15)
#define BIT_AP_APB_IIS2_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 12)
#define BIT_AP_APB_IIS1_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 9)
#define BIT_AP_APB_IIS0_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 6)
#define BIT_AP_APB_I2C6_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 3)
#define BIT_AP_APB_I2C5_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7))


#endif /* AP_APB_H */

