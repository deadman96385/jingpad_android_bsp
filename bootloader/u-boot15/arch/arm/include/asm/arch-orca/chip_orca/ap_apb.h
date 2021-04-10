/*
 * Copyright (C) 2019 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2019-02-11 15:07:05
 *
 */


#ifndef AP_APB_H
#define AP_APB_H

#define CTL_BASE_AP_APB 0x24000000


#define REG_AP_APB_APB_EB                        ( CTL_BASE_AP_APB + 0x0000 )
#define REG_AP_APB_APB_RST                       ( CTL_BASE_AP_APB + 0x0004 )
#define REG_AP_APB_APB_MISC_CTRL                 ( CTL_BASE_AP_APB + 0x0008 )
#define REG_AP_APB_APB_PCLK_AUTO_GATE_EB         ( CTL_BASE_AP_APB + 0x000C )
#define REG_AP_APB_APB_PCLK_AUTO_SLOW_SEL1       ( CTL_BASE_AP_APB + 0x0014 )
#define REG_AP_APB_APB_PCLK_AUTO_SLOW_SEL2       ( CTL_BASE_AP_APB + 0x0018 )
#define REG_AP_APB_APB_PERI_FRC_DOZE             ( CTL_BASE_AP_APB + 0x001C )
#define REG_AP_APB_APB2APB_CLK_AUTO_GATE_EN      ( CTL_BASE_AP_APB + 0x0020 )
#define REG_AP_APB_RESERVE0                      ( CTL_BASE_AP_APB + 0x0040 )
#define REG_AP_APB_RESERVE1                      ( CTL_BASE_AP_APB + 0x0044 )

/* REG_AP_APB_APB_EB */

#define BIT_AP_APB_SIM0_32K_EB                  BIT(18)
#define BIT_AP_APB_SIM0_EB                      BIT(17)
#define BIT_AP_APB_PWM3_EB                      BIT(16)
#define BIT_AP_APB_PWM2_EB                      BIT(15)
#define BIT_AP_APB_PWM1_EB                      BIT(14)
#define BIT_AP_APB_PWM0_EB                      BIT(13)
#define BIT_AP_APB_SPI2_LCD_FMARK_IN_EB         BIT(12)
#define BIT_AP_APB_SPI2_EB                      BIT(11)
#define BIT_AP_APB_SPI1_LCD_FMARK_IN_EB         BIT(10)
#define BIT_AP_APB_SPI1_EB                      BIT(9)
#define BIT_AP_APB_SPI0_LCD_FMARK_IN_EB         BIT(8)
#define BIT_AP_APB_SPI0_EB                      BIT(7)
#define BIT_AP_APB_I2C4_EB                      BIT(6)
#define BIT_AP_APB_I2C3_EB                      BIT(5)
#define BIT_AP_APB_I2C2_EB                      BIT(4)
#define BIT_AP_APB_I2C1_EB                      BIT(3)
#define BIT_AP_APB_I2C0_EB                      BIT(2)
#define BIT_AP_APB_UART0_EB                     BIT(1)
#define BIT_AP_APB_APB_REG_EB                   BIT(0)

/* REG_AP_APB_APB_RST */

#define BIT_AP_APB_SIM0_SOFT_RST                BIT(13)
#define BIT_AP_APB_PWM3_SOFT_RST                BIT(12)
#define BIT_AP_APB_PWM2_SOFT_RST                BIT(11)
#define BIT_AP_APB_PWM1_SOFT_RST                BIT(10)
#define BIT_AP_APB_PWM0_SOFT_RST                BIT(9)
#define BIT_AP_APB_SPI2_SOFT_RST                BIT(8)
#define BIT_AP_APB_SPI1_SOFT_RST                BIT(7)
#define BIT_AP_APB_SPI0_SOFT_RST                BIT(6)
#define BIT_AP_APB_I2C4_SOFT_RST                BIT(5)
#define BIT_AP_APB_I2C3_SOFT_RST                BIT(4)
#define BIT_AP_APB_I2C2_SOFT_RST                BIT(3)
#define BIT_AP_APB_I2C1_SOFT_RST                BIT(2)
#define BIT_AP_APB_I2C0_SOFT_RST                BIT(1)
#define BIT_AP_APB_UART0_SOFT_RST               BIT(0)

/* REG_AP_APB_APB_MISC_CTRL */

#define BIT_AP_APB_SIM_CLK_POLARITY             BIT(3)
#define BIT_AP_APB_SPI2_FMARK_POLARITY_INV      BIT(2)
#define BIT_AP_APB_SPI1_FMARK_POLARITY_INV      BIT(1)
#define BIT_AP_APB_SPI0_FMARK_POLARITY_INV      BIT(0)

/* REG_AP_APB_APB_PCLK_AUTO_GATE_EB */

#define BIT_AP_APB_SIM0_PCLK_AUTO_GATE_EB       BIT(13)
#define BIT_AP_APB_PWM3_PCLK_AUTO_GATE_EB       BIT(12)
#define BIT_AP_APB_PWM2_PCLK_AUTO_GATE_EB       BIT(11)
#define BIT_AP_APB_PWM1_PCLK_AUTO_GATE_EB       BIT(10)
#define BIT_AP_APB_PWM0_PCLK_AUTO_GATE_EB       BIT(9)
#define BIT_AP_APB_SPI2_PCLK_AUTO_GATE_EB       BIT(8)
#define BIT_AP_APB_SPI1_PCLK_AUTO_GATE_EB       BIT(7)
#define BIT_AP_APB_SPI0_PCLK_AUTO_GATE_EB       BIT(6)
#define BIT_AP_APB_I2C4_PCLK_AUTO_GATE_EB       BIT(5)
#define BIT_AP_APB_I2C3_PCLK_AUTO_GATE_EB       BIT(4)
#define BIT_AP_APB_I2C2_PCLK_AUTO_GATE_EB       BIT(3)
#define BIT_AP_APB_I2C1_PCLK_AUTO_GATE_EB       BIT(2)
#define BIT_AP_APB_I2C0_PCLK_AUTO_GATE_EB       BIT(1)
#define BIT_AP_APB_UART0_PCLK_AUTO_GATE_EB      BIT(0)

/* REG_AP_APB_APB_PCLK_AUTO_SLOW_SEL1 */

#define BIT_AP_APB_SIM0_PCLK_AUTO_SLOW_EN       BIT(23)
#define BIT_AP_APB_SIM0_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 20)
#define BIT_AP_APB_PWM3_PCLK_AUTO_SLOW_EN       BIT(19)
#define BIT_AP_APB_PWM3_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 16)
#define BIT_AP_APB_PWM2_PCLK_AUTO_SLOW_EN       BIT(15)
#define BIT_AP_APB_PWM2_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 12)
#define BIT_AP_APB_PWM1_PCLK_AUTO_SLOW_EN       BIT(11)
#define BIT_AP_APB_PWM1_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 8)
#define BIT_AP_APB_PWM0_PCLK_AUTO_SLOW_EN       BIT(7)
#define BIT_AP_APB_PWM0_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 4)
#define BIT_AP_APB_SPI2_PCLK_AUTO_SLOW_EN       BIT(3)
#define BIT_AP_APB_SPI2_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7))

/* REG_AP_APB_APB_PCLK_AUTO_SLOW_SEL2 */

#define BIT_AP_APB_SPI1_PCLK_AUTO_SLOW_EN       BIT(31)
#define BIT_AP_APB_SPI1_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 28)
#define BIT_AP_APB_SPI0_PCLK_AUTO_SLOW_EN       BIT(27)
#define BIT_AP_APB_SPI0_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 24)
#define BIT_AP_APB_I2C4_PCLK_AUTO_SLOW_EN       BIT(23)
#define BIT_AP_APB_I2C4_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 20)
#define BIT_AP_APB_I2C3_PCLK_AUTO_SLOW_EN       BIT(19)
#define BIT_AP_APB_I2C3_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 16)
#define BIT_AP_APB_I2C2_PCLK_AUTO_SLOW_EN       BIT(15)
#define BIT_AP_APB_I2C2_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 12)
#define BIT_AP_APB_I2C1_PCLK_AUTO_SLOW_EN       BIT(11)
#define BIT_AP_APB_I2C1_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 8)
#define BIT_AP_APB_I2C0_PCLK_AUTO_SLOW_EN       BIT(7)
#define BIT_AP_APB_I2C0_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 4)
#define BIT_AP_APB_UART0_PCLK_AUTO_SLOW_EN      BIT(3)
#define BIT_AP_APB_UART0_PCLK_AUTO_SLOW_SEL(x)  (((x) & 0x7))

/* REG_AP_APB_APB_PERI_FRC_DOZE */

#define BIT_AP_APB_SIM0_FRC_DOZE                BIT(13)
#define BIT_AP_APB_PWM3_FRC_DOZE                BIT(12)
#define BIT_AP_APB_PWM2_FRC_DOZE                BIT(11)
#define BIT_AP_APB_PWM1_FRC_DOZE                BIT(10)
#define BIT_AP_APB_PWM0_FRC_DOZE                BIT(9)
#define BIT_AP_APB_SPI2_FRC_DOZE                BIT(8)
#define BIT_AP_APB_SPI1_FRC_DOZE                BIT(7)
#define BIT_AP_APB_SPI0_FRC_DOZE                BIT(6)
#define BIT_AP_APB_I2C4_FRC_DOZE                BIT(5)
#define BIT_AP_APB_I2C3_FRC_DOZE                BIT(4)
#define BIT_AP_APB_I2C2_FRC_DOZE                BIT(3)
#define BIT_AP_APB_I2C1_FRC_DOZE                BIT(2)
#define BIT_AP_APB_I2C0_FRC_DOZE                BIT(1)
#define BIT_AP_APB_UART0_FRC_DOZE               BIT(0)

/* REG_AP_APB_APB2APB_CLK_AUTO_GATE_EN */

#define BIT_AP_APB_MCLK_AUTO_GATE_EN            BIT(1)
#define BIT_AP_APB_SCLK_AUTO_GATE_EN            BIT(0)

/* REG_AP_APB_RESERVE0 */

#define BIT_AP_APB_RESERVE0(x)                  (((x) & 0xFFFFFFFF))

/* REG_AP_APB_RESERVE1 */

#define BIT_AP_APB_RESERVE1(x)                  (((x) & 0xFFFFFFFF))


#endif /* AP_APB_H */


