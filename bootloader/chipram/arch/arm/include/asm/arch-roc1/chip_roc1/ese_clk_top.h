/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-18 10:54:39
 *
 */


#ifndef ESE_CLK_TOP_H
#define ESE_CLK_TOP_H

#define CTL_BASE_ESE_CLK_TOP 0x50020000


#define REG_ESE_CLK_TOP_CLK_EN_CTRL1             ( CTL_BASE_ESE_CLK_TOP + 0x0000 )
#define REG_ESE_CLK_TOP_CGM_ESE_SYS_1X_DIV       ( CTL_BASE_ESE_CLK_TOP + 0x0008 )
#define REG_ESE_CLK_TOP_CGM_ESE_SYS_CFG          ( CTL_BASE_ESE_CLK_TOP + 0x000C )
#define REG_ESE_CLK_TOP_CGM_ESE_SPI_CFG          ( CTL_BASE_ESE_CLK_TOP + 0x0010 )
#define REG_ESE_CLK_TOP_CLK_STATUS0              ( CTL_BASE_ESE_CLK_TOP + 0x0018 )
#define REG_ESE_CLK_TOP_CLK_STATUS1              ( CTL_BASE_ESE_CLK_TOP + 0x001C )
#define REG_ESE_CLK_TOP_ESE_SYS_MAIN_CLK_STATUS  ( CTL_BASE_ESE_CLK_TOP + 0x0020 )
#define REG_ESE_CLK_TOP_CGM_ESE_SFC_DIV          ( CTL_BASE_ESE_CLK_TOP + 0x0024 )
#define REG_ESE_CLK_TOP_CGM_ESE_SFC_1X_DIV       ( CTL_BASE_ESE_CLK_TOP + 0x0028 )
#define REG_ESE_CLK_TOP_CGM_ESE_GPIO_DIV         ( CTL_BASE_ESE_CLK_TOP + 0x002C )
#define REG_ESE_CLK_TOP_CGM_ESE_I2C0_DIV         ( CTL_BASE_ESE_CLK_TOP + 0x0030 )
#define REG_ESE_CLK_TOP_CGM_ESE_I2C1_DIV         ( CTL_BASE_ESE_CLK_TOP + 0x0034 )
#define REG_ESE_CLK_TOP_CGM_ESE_SWP_DIV          ( CTL_BASE_ESE_CLK_TOP + 0x0038 )
#define REG_ESE_CLK_TOP_CGM_ESE_UART_DIV         ( CTL_BASE_ESE_CLK_TOP + 0x003C )
#define REG_ESE_CLK_TOP_CLK_SFC_STATUS           ( CTL_BASE_ESE_CLK_TOP + 0x0040 )

/* REG_ESE_CLK_TOP_CLK_EN_CTRL1 */

#define BIT_ESE_CLK_TOP_CGM_ESE_UART_EN           BIT(17)
#define BIT_ESE_CLK_TOP_CGM_ESE_SWP_EN            BIT(16)
#define BIT_ESE_CLK_TOP_CGM_ESE_I2C1_EN           BIT(15)
#define BIT_ESE_CLK_TOP_CGM_ESE_I2C0_EN           BIT(14)
#define BIT_ESE_CLK_TOP_CGM_ESE_GPIO_EN           BIT(13)
#define BIT_ESE_CLK_TOP_CGM_ESE_SFC_1X_EN         BIT(12)
#define BIT_ESE_CLK_TOP_CGM_ESE_SFC_EN            BIT(11)
#define BIT_ESE_CLK_TOP_CGM_ESE_SPI_EN            BIT(10)
#define BIT_ESE_CLK_TOP_CGM_ESE_26M_EN            BIT(9)
#define BIT_ESE_CLK_TOP_CGM_ESE_32K_OUT_EN        BIT(8)
#define BIT_ESE_CLK_TOP_CGM_ESE_WDG_EN            BIT(7)
#define BIT_ESE_CLK_TOP_CGM_ESE_TMR3_EN           BIT(6)
#define BIT_ESE_CLK_TOP_CGM_ESE_TMR2_EN           BIT(5)
#define BIT_ESE_CLK_TOP_CGM_ESE_TMR1_EN           BIT(4)
#define BIT_ESE_CLK_TOP_CGM_ESE_TMR0_EN           BIT(3)
#define BIT_ESE_CLK_TOP_CGM_ESE_SYS_1X_EN         BIT(1)
#define BIT_ESE_CLK_TOP_CGM_ESE_SYS_EN            BIT(0)

/* REG_ESE_CLK_TOP_CGM_ESE_SYS_1X_DIV */

#define BIT_ESE_CLK_TOP_CGM_ESE_SYS_1X_DIV(x)     (((x) & 0x3))

/* REG_ESE_CLK_TOP_CGM_ESE_SYS_CFG */

#define BIT_ESE_CLK_TOP_CGM_ESE_SYS_DIV(x)        (((x) & 0x7))

/* REG_ESE_CLK_TOP_CGM_ESE_SPI_CFG */

#define BIT_ESE_CLK_TOP_CGM_SPI_PAD_SEL           BIT(4)
#define BIT_ESE_CLK_TOP_CGM_ESE_SPI_DIV(x)        (((x) & 0x7))

/* REG_ESE_CLK_TOP_CLK_STATUS0 */

#define BIT_ESE_CLK_TOP_CGM_RATIO_ESE_SYS_1X_CUR  BIT(1)
#define BIT_ESE_CLK_TOP_CGM_RATIO_ESE_SYS_1X_ADV  BIT(0)

/* REG_ESE_CLK_TOP_CLK_STATUS1 */

#define BIT_ESE_CLK_TOP_CGM_BUSY_26M              BIT(2)
#define BIT_ESE_CLK_TOP_CGM_BUSY_128M             BIT(1)
#define BIT_ESE_CLK_TOP_CGM_BUSY_32K              BIT(0)

/* REG_ESE_CLK_TOP_ESE_SYS_MAIN_CLK_STATUS */

#define BIT_ESE_CLK_TOP_ESE_SYS_RCO_PLL_FLAG      BIT(0)

/* REG_ESE_CLK_TOP_CGM_ESE_SFC_DIV */

#define BIT_ESE_CLK_TOP_CGM_ESE_SFC_DIV(x)        (((x) & 0x7))

/* REG_ESE_CLK_TOP_CGM_ESE_SFC_1X_DIV */

#define BIT_ESE_CLK_TOP_CGM_ESE_SFC_1X_DIV(x)     (((x) & 0x3))

/* REG_ESE_CLK_TOP_CGM_ESE_GPIO_DIV */

#define BIT_ESE_CLK_TOP_CGM_ESE_GPIO_DIV(x)       (((x) & 0x7))

/* REG_ESE_CLK_TOP_CGM_ESE_I2C0_DIV */

#define BIT_ESE_CLK_TOP_CGM_ESE_I2C0_DIV(x)       (((x) & 0x7))

/* REG_ESE_CLK_TOP_CGM_ESE_I2C1_DIV */

#define BIT_ESE_CLK_TOP_CGM_ESE_I2C1_DIV(x)       (((x) & 0x7))

/* REG_ESE_CLK_TOP_CGM_ESE_SWP_DIV */

#define BIT_ESE_CLK_TOP_CGM_ESE_SWP_DIV(x)        (((x) & 0x7))

/* REG_ESE_CLK_TOP_CGM_ESE_UART_DIV */

#define BIT_ESE_CLK_TOP_CGM_ESE_UART_DIV(x)       (((x) & 0x7))

/* REG_ESE_CLK_TOP_CLK_SFC_STATUS */

#define BIT_ESE_CLK_TOP_CGM_RATIO_ESE_SFC_1X_CUR  BIT(1)
#define BIT_ESE_CLK_TOP_CGM_RATIO_ESE_SFC_1X_ADV  BIT(0)


#endif /* ESE_CLK_TOP_H */


