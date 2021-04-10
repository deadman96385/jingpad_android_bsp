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


#ifndef SP_AHB_H
#define SP_AHB_H

#define CTL_BASE_SP_AHB 0x50000000


#define REG_SP_AHB_CFG_CLK_EB                ( CTL_BASE_SP_AHB + 0x0000 )
#define REG_SP_AHB_SOFT_RST                  ( CTL_BASE_SP_AHB + 0x0004 )
#define REG_SP_AHB_DMA_CTRL                  ( CTL_BASE_SP_AHB + 0x0008 )
#define REG_SP_AHB_SLP_CTL                   ( CTL_BASE_SP_AHB + 0x000C )
#define REG_SP_AHB_CM3_CORE_CFG1             ( CTL_BASE_SP_AHB + 0x0010 )
#define REG_SP_AHB_CM3_CORE_SYSTICK_CFG      ( CTL_BASE_SP_AHB + 0x0014 )
#define REG_SP_AHB_CM3_CORE_AUXFAULT_CFG     ( CTL_BASE_SP_AHB + 0x0018 )
#define REG_SP_AHB_CM3_MAIN_STATOUT          ( CTL_BASE_SP_AHB + 0x001C )
#define REG_SP_AHB_CM3_HWDATAD_STAT          ( CTL_BASE_SP_AHB + 0x0020 )
#define REG_SP_AHB_CM3_INT_STAT              ( CTL_BASE_SP_AHB + 0x0024 )
#define REG_SP_AHB_WDG_ENABLE                ( CTL_BASE_SP_AHB + 0x0028 )
#define REG_SP_AHB_SW_CM3_CGM_CFG            ( CTL_BASE_SP_AHB + 0x0030 )
#define REG_SP_AHB_FPU_CFG                   ( CTL_BASE_SP_AHB + 0x0034 )
#define REG_SP_AHB_CLK_AUTO_GATE_DIV_CTRL    ( CTL_BASE_SP_AHB + 0x0040 )
#define REG_SP_AHB_CLK_AUTO_GATE_CTRL        ( CTL_BASE_SP_AHB + 0x0044 )
#define REG_SP_AHB_RES_REG                   ( CTL_BASE_SP_AHB + 0x00FF )

/* REG_SP_AHB_CFG_CLK_EB */

#define BIT_SP_AHB_EIC_PUB1_EB                 BIT(20)
#define BIT_SP_AHB_EIC_PUB1_RTC_EB             BIT(19)
#define BIT_SP_AHB_EIC_PUB1_RTCDV5_EB          BIT(18)
#define BIT_SP_AHB_EIC_GPIO_EB                 BIT(17)
#define BIT_SP_AHB_EIC_GPIO_RTC_EB             BIT(16)
#define BIT_SP_AHB_EIC_GPIO_RTCDV5_EB          BIT(15)
#define BIT_SP_AHB_SPI_EB                      BIT(14)
#define BIT_SP_AHB_I2C1_EB                     BIT(13)
#define BIT_SP_AHB_I2C0_EB                     BIT(12)
#define BIT_SP_AHB_GPIO_EB                     BIT(11)
#define BIT_SP_AHB_UART1_EB                    BIT(10)
#define BIT_SP_AHB_UART0_EB                    BIT(9)
#define BIT_SP_AHB_TMR_EB                      BIT(8)
#define BIT_SP_AHB_SYST_EB                     BIT(7)
#define BIT_SP_AHB_EIC_RTCDV5_EB               BIT(6)
#define BIT_SP_AHB_EIC_EB                      BIT(5)
#define BIT_SP_AHB_INTC_EB                     BIT(4)
#define BIT_SP_AHB_EIC_RTC_EB                  BIT(3)
#define BIT_SP_AHB_IMC_EB                      BIT(2)
#define BIT_SP_AHB_TIC_EB                      BIT(1)

/* REG_SP_AHB_SOFT_RST */

#define BIT_SP_AHB_EIC_PUB1_SOFT_RST           BIT(16)
#define BIT_SP_AHB_EIC_GPIO_SOFT_RST           BIT(15)
#define BIT_SP_AHB_SPI_SOFT_RST                BIT(14)
#define BIT_SP_AHB_I2C1_SOFT_RST               BIT(13)
#define BIT_SP_AHB_I2C0_SOFT_RST               BIT(12)
#define BIT_SP_AHB_GPIO_SOFT_RST               BIT(11)
#define BIT_SP_AHB_UART1_SOFT_RST              BIT(10)
#define BIT_SP_AHB_UART0_SOFT_RST              BIT(9)
#define BIT_SP_AHB_TMR_SOFT_RST                BIT(8)
#define BIT_SP_AHB_SYST_SOFT_RST               BIT(7)
#define BIT_SP_AHB_WDG_SOFT_RST                BIT(6)
#define BIT_SP_AHB_EIC_SOFT_RST                BIT(5)
#define BIT_SP_AHB_INTC_SOFT_RST               BIT(4)
#define BIT_SP_AHB_IMC_SOFT_RST                BIT(2)
#define BIT_SP_AHB_TIC_SOFT_RST                BIT(1)
#define BIT_SP_AHB_ARCH_SOFT_RST               BIT(0)

/* REG_SP_AHB_DMA_CTRL */

#define BIT_SP_AHB_CM3_DMA_SOFT_RST            BIT(9)
#define BIT_SP_AHB_CM3_DMA_EB                  BIT(8)
#define BIT_SP_AHB_HPROT_CM3_PUB_WR(x)         (((x) & 0xF) << 4)
#define BIT_SP_AHB_HPROT_CM3_PUB_RD(x)         (((x) & 0xF))

/* REG_SP_AHB_SLP_CTL */

#define BIT_SP_AHB_CM3_EIC_NOTLAT_INT_WAKE_EN  BIT(9)
#define BIT_SP_AHB_ANA_INT_WAKE_EN             BIT(8)
#define BIT_SP_AHB_CM3_GPIO_INT_WAKE_EN        BIT(7)
#define BIT_SP_AHB_CM3_WDG_INT_WAKE_EN         BIT(6)
#define BIT_SP_AHB_CM3_SYST_INT_WAKE_EN        BIT(5)
#define BIT_SP_AHB_CM3_TMR_INT_WAKE_EN         BIT(4)
#define BIT_SP_AHB_CM3_EIC_LAT_INT_WAKE_EN     BIT(3)
#define BIT_SP_AHB_SYS_AUTO_GATE_EN            BIT(2)
#define BIT_SP_AHB_CORE_AUTO_GATE_EN           BIT(0)

/* REG_SP_AHB_CM3_CORE_CFG1 */

#define BIT_SP_AHB_SOFT_EXRESPD                BIT(9)
#define BIT_SP_AHB_SOFT_TSCLK_CHG              BIT(7)
#define BIT_SP_AHB_SOFT_FIX_MSTTYPE            BIT(6)
#define BIT_SP_AHB_SOFT_DBG_RESTART            BIT(5)
#define BIT_SP_AHB_SOFT_EDBGRQ                 BIT(4)
#define BIT_SP_AHB_SOFT_SLEEP_HOLD_REQ_N       BIT(3)
#define BIT_SP_AHB_SOFT_EXRESPS                BIT(2)
#define BIT_SP_AHB_SOFT_CGBYPASS               BIT(1)
#define BIT_SP_AHB_SOFT_RSTBYPASS              BIT(0)

/* REG_SP_AHB_CM3_CORE_SYSTICK_CFG */

#define BIT_SP_AHB_SOFT_STCALIB(x)             (((x) & 0x3FFFFFF) << 1)
#define BIT_SP_AHB_SOFT_STCLK                  BIT(0)

/* REG_SP_AHB_CM3_CORE_AUXFAULT_CFG */

#define BIT_SP_AHB_SOFT_AUXFAULT(x)            (((x) & 0xFFFFFFFF))

/* REG_SP_AHB_CM3_MAIN_STATOUT */

#define BIT_SP_AHB_WICENACK_STAT               BIT(31)
#define BIT_SP_AHB_GATEHCLK_STAT               BIT(30)
#define BIT_SP_AHB_WAKEUP_STAT                 BIT(29)
#define BIT_SP_AHB_SLEEPHOLDACKN_STAT          BIT(28)
#define BIT_SP_AHB_SLEEPINGDEEP_STAT           BIT(27)
#define BIT_SP_AHB_SLEEPING_STAT               BIT(26)
#define BIT_SP_AHB_DBGRESTARTED_STAT           BIT(24)
#define BIT_SP_AHB_HALTED_STAT                 BIT(23)
#define BIT_SP_AHB_BRCHSTAT_STAT(x)            (((x) & 0xF) << 19)
#define BIT_SP_AHB_EXREQS_STAT                 BIT(18)
#define BIT_SP_AHB_MEMATTRS_STAT(x)            (((x) & 0x3) << 16)
#define BIT_SP_AHB_HMASTLOCKS_STAT             BIT(15)
#define BIT_SP_AHB_HMASTERS_STAT(x)            (((x) & 0x3) << 13)
#define BIT_SP_AHB_HWRITED_STAT                BIT(12)
#define BIT_SP_AHB_EXREQD_STAT                 BIT(11)
#define BIT_SP_AHB_MEMATTRD_STAT(x)            (((x) & 0x3) << 9)
#define BIT_SP_AHB_HMASTERD_STAT(x)            (((x) & 0x3) << 7)
#define BIT_SP_AHB_MEMATTRI_STAT(x)            (((x) & 0x3) << 5)
#define BIT_SP_AHB_SWV_STAT                    BIT(4)
#define BIT_SP_AHB_CDBGPWRUPREQ_STAT           BIT(0)

/* REG_SP_AHB_CM3_HWDATAD_STAT */

#define BIT_SP_AHB_HWDATAD_STAT(x)             (((x) & 0xFFFFFFFF))

/* REG_SP_AHB_CM3_INT_STAT */

#define BIT_SP_AHB_CURRPRI_STAT(x)             (((x) & 0xFF))

/* REG_SP_AHB_WDG_ENABLE */

#define BIT_SP_AHB_WDG_EB                      BIT(0)

/* REG_SP_AHB_SW_CM3_CGM_CFG */

#define BIT_SP_AHB_CM3_DDR1_DFS_EN             BIT(26)
#define BIT_SP_AHB_DMC_DDR1_1X_CM3_EN          BIT(25)
#define BIT_SP_AHB_DMC_DDR1_2X_CM3_EN          BIT(24)
#define BIT_SP_AHB_CLK_DMC1_SEL_HW_CM3_EN      BIT(23)
#define BIT_SP_AHB_CLK_DMC1_CM3_SEL_EXT        BIT(22)
#define BIT_SP_AHB_CLK_DMC1_2X_CM3_DIV(x)      (((x) & 0xF) << 18)
#define BIT_SP_AHB_CLK_DMC1_1X_CM3_DIV         BIT(17)
#define BIT_SP_AHB_CLK_DMC1_CM3_SEL            BIT(16)
#define BIT_SP_AHB_CM3_DDR0_DFS_EN             BIT(10)
#define BIT_SP_AHB_DMC_DDR0_1X_CM3_EN          BIT(9)
#define BIT_SP_AHB_DMC_DDR0_2X_CM3_EN          BIT(8)
#define BIT_SP_AHB_CLK_DMC0_SEL_HW_CM3_EN      BIT(7)
#define BIT_SP_AHB_CLK_DMC0_CM3_SEL_EXT        BIT(6)
#define BIT_SP_AHB_CLK_DMC0_2X_CM3_DIV(x)      (((x) & 0xF) << 2)
#define BIT_SP_AHB_CLK_DMC0_1X_CM3_DIV         BIT(1)
#define BIT_SP_AHB_CLK_DMC0_CM3_SEL            BIT(0)

/* REG_SP_AHB_FPU_CFG */

#define BIT_SP_AHB_FPU_DISABLE                 BIT(0)

/* REG_SP_AHB_CLK_AUTO_GATE_DIV_CTRL */

#define BIT_SP_AHB_PCLK_EN_SLOW_EN             BIT(3)
#define BIT_SP_AHB_PCLK_EN_SLOW_SEL(x)         (((x) & 0x7))

/* REG_SP_AHB_CLK_AUTO_GATE_CTRL */

#define BIT_SP_AHB_IP_SLOW_EN_CM4_SPI          BIT(21)
#define BIT_SP_AHB_IP_AUTO_EN_CM4_SPI          BIT(20)
#define BIT_SP_AHB_IP_SLOW_EN_CM3_GPIO         BIT(19)
#define BIT_SP_AHB_IP_AUTO_EN_CM3_GPIO         BIT(18)
#define BIT_SP_AHB_IP_SLOW_EN_CM3_I2C1         BIT(17)
#define BIT_SP_AHB_IP_AUTO_EN_CM3_I2C1         BIT(16)
#define BIT_SP_AHB_IP_SLOW_EN_CM3_I2C0         BIT(15)
#define BIT_SP_AHB_IP_AUTO_EN_CM3_I2C0         BIT(14)
#define BIT_SP_AHB_IP_SLOW_EN_CM3_UART1        BIT(13)
#define BIT_SP_AHB_IP_AUTO_EN_CM3_UART1        BIT(12)
#define BIT_SP_AHB_IP_SLOW_EN_CM3_UART0        BIT(11)
#define BIT_SP_AHB_IP_AUTO_EN_CM3_UART0        BIT(10)
#define BIT_SP_AHB_IP_SLOW_EN_CM3_SYST         BIT(9)
#define BIT_SP_AHB_IP_AUTO_EN_CM3_SYST         BIT(8)
#define BIT_SP_AHB_IP_SLOW_EN_CM3_TMR          BIT(7)
#define BIT_SP_AHB_IP_AUTO_EN_CM3_TMR          BIT(6)
#define BIT_SP_AHB_IP_SLOW_EN_CM3_WDG          BIT(5)
#define BIT_SP_AHB_IP_AUTO_EN_CM3_WDG          BIT(4)
#define BIT_SP_AHB_IP_SLOW_EN_CM4_EIC_GPIO     BIT(3)
#define BIT_SP_AHB_IP_AUTO_EN_CM4_EIC_GPIO     BIT(2)
#define BIT_SP_AHB_IP_SLOW_EN_CM3_EIC          BIT(1)
#define BIT_SP_AHB_IP_AUTO_EN_CM3_EIC          BIT(0)

/* REG_SP_AHB_RES_REG */

#define BIT_SP_AHB_RES_REG_H(x)                (((x) & 0xFF) << 24)
#define BIT_SP_AHB_RES_REG_L(x)                (((x) & 0xFFFFFF))


#endif /* SP_AHB_H */

