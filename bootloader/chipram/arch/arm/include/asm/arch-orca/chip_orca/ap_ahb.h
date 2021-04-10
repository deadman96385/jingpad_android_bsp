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


#ifndef AP_AHB_H
#define AP_AHB_H

#define CTL_BASE_AP_AHB 0x21000000


#define REG_AP_AHB_AHB_EB                      ( CTL_BASE_AP_AHB + 0x0000 )
#define REG_AP_AHB_AHB_RST                     ( CTL_BASE_AP_AHB + 0x0004 )
#define REG_AP_AHB_AP_SYS_SLEEP_CFG            ( CTL_BASE_AP_AHB + 0x0008 )
#define REG_AP_AHB_CLOCK_FREQUENCY_DOWN        ( CTL_BASE_AP_AHB + 0x0018 )
#define REG_AP_AHB_USB0_CTRL                   ( CTL_BASE_AP_AHB + 0x0020 )
#define REG_AP_AHB_USB0_DBG0                   ( CTL_BASE_AP_AHB + 0x0024 )
#define REG_AP_AHB_USB0_DBG1                   ( CTL_BASE_AP_AHB + 0x0028 )
#define REG_AP_AHB_USB0_DBG2                   ( CTL_BASE_AP_AHB + 0x002C )
#define REG_AP_AHB_APB_PCLK_AUTO_GATE_EB       ( CTL_BASE_AP_AHB + 0x003C )
#define REG_AP_AHB_APB_PCLK_AUTO_SLOW_SEL      ( CTL_BASE_AP_AHB + 0x0040 )
#define REG_AP_AHB_AP_SYS_CLK_FRC_OFF0         ( CTL_BASE_AP_AHB + 0x0044 )
#define REG_AP_AHB_AP_SYS_CLK_FRC_ON0          ( CTL_BASE_AP_AHB + 0x0048 )
#define REG_AP_AHB_AP_SYS_CLK_BUS_AUTO_EN      ( CTL_BASE_AP_AHB + 0x004C )
#define REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG       ( CTL_BASE_AP_AHB + 0x0050 )
#define REG_AP_AHB_MMTX_M0_LPC                 ( CTL_BASE_AP_AHB + 0x0100 )
#define REG_AP_AHB_MMTX_M1_LPC                 ( CTL_BASE_AP_AHB + 0x0104 )
#define REG_AP_AHB_MMTX_M2_LPC                 ( CTL_BASE_AP_AHB + 0x0108 )
#define REG_AP_AHB_MMTX_M3_LPC                 ( CTL_BASE_AP_AHB + 0x010C )
#define REG_AP_AHB_MMTX_M4_LPC                 ( CTL_BASE_AP_AHB + 0x0110 )
#define REG_AP_AHB_MMTX_M5_LPC                 ( CTL_BASE_AP_AHB + 0x0114 )
#define REG_AP_AHB_MMTX_M6_LPC                 ( CTL_BASE_AP_AHB + 0x0118 )
#define REG_AP_AHB_MMTX_MAIN_LPC               ( CTL_BASE_AP_AHB + 0x013C )
#define REG_AP_AHB_MMTX_S0_LPC                 ( CTL_BASE_AP_AHB + 0x0140 )
#define REG_AP_AHB_MMTX_S1_LPC                 ( CTL_BASE_AP_AHB + 0x0144 )
#define REG_AP_AHB_MMTX_S2_LPC                 ( CTL_BASE_AP_AHB + 0x0148 )
#define REG_AP_AHB_MMTX_S3_LPC                 ( CTL_BASE_AP_AHB + 0x014C )
#define REG_AP_AHB_MMTX_S4_LPC                 ( CTL_BASE_AP_AHB + 0x0150 )
#define REG_AP_AHB_MMTX_S5_LPC                 ( CTL_BASE_AP_AHB + 0x0154 )
#define REG_AP_AHB_MMTX_S6_LPC                 ( CTL_BASE_AP_AHB + 0x0158 )
#define REG_AP_AHB_MMTX_MST_FRC_LSLP           ( CTL_BASE_AP_AHB + 0x0180 )
#define REG_AP_AHB_MMTX_LSLP_LPC_BYPASS        ( CTL_BASE_AP_AHB + 0x0184 )
#define REG_AP_AHB_MMTX_MST_FRC_PUB_DSLP       ( CTL_BASE_AP_AHB + 0x0188 )
#define REG_AP_AHB_MMTX_PUB_DSLP_LPC_BYPASS    ( CTL_BASE_AP_AHB + 0x018C )
#define REG_AP_AHB_MMTX_MST_FRC_DOZE           ( CTL_BASE_AP_AHB + 0x0190 )
#define REG_AP_AHB_MMTX_DOZE_LPC_BYPASS        ( CTL_BASE_AP_AHB + 0x0194 )
#define REG_AP_AHB_MMTX_AXI_FREQ_ALLOW0        ( CTL_BASE_AP_AHB + 0x0198 )
#define REG_AP_AHB_MMTX_AXI_FREQ_ALLOW1        ( CTL_BASE_AP_AHB + 0x019C )
#define REG_AP_AHB_MMTX_AXI_FREQ_LSLP_ALLOW0   ( CTL_BASE_AP_AHB + 0x01A0 )
#define REG_AP_AHB_MMTX_AXI_FREQ_LSLP_ALLOW1   ( CTL_BASE_AP_AHB + 0x01A4 )
#define REG_AP_AHB_AP_QOS0                     ( CTL_BASE_AP_AHB + 0x0300 )
#define REG_AP_AHB_AP_QOS1                     ( CTL_BASE_AP_AHB + 0x0304 )
#define REG_AP_AHB_AP_URGENCY                  ( CTL_BASE_AP_AHB + 0x0308 )
#define REG_AP_AHB_AP_USER0                    ( CTL_BASE_AP_AHB + 0x030C )
#define REG_AP_AHB_AP_USER1                    ( CTL_BASE_AP_AHB + 0x0310 )
#define REG_AP_AHB_MMTX_CTRL                   ( CTL_BASE_AP_AHB + 0x0314 )
#define REG_AP_AHB_MMTX_PU_NUM0                ( CTL_BASE_AP_AHB + 0x0318 )
#define REG_AP_AHB_MMTX_PU_NUM1                ( CTL_BASE_AP_AHB + 0x031C )
#define REG_AP_AHB_MMTX_PU_NUM2                ( CTL_BASE_AP_AHB + 0x0320 )
#define REG_AP_AHB_MMTX_PU_NUM3                ( CTL_BASE_AP_AHB + 0x0324 )
#define REG_AP_AHB_USE_IP_BUSY_GATING          ( CTL_BASE_AP_AHB + 0x0328 )
#define REG_AP_AHB_RESERVE0                    ( CTL_BASE_AP_AHB + 0x0400 )
#define REG_AP_AHB_RESERVE1                    ( CTL_BASE_AP_AHB + 0x0404 )
#define REG_AP_AHB_CHIP_ID                     ( CTL_BASE_AP_AHB + 0x30FC )

/* REG_AP_AHB_AHB_EB */

#define BIT_AP_AHB_EMMC_32K_EB                       BIT(12)
#define BIT_AP_AHB_EMMC_EB                           BIT(11)
#define BIT_AP_AHB_SDIO_MST_32K_EB                   BIT(10)
#define BIT_AP_AHB_SDIO_MST_EB                       BIT(9)
#define BIT_AP_AHB_USB0_REF_EB                       BIT(8)
#define BIT_AP_AHB_USB0_SUSPEND_EB                   BIT(7)
#define BIT_AP_AHB_USB0_EB                           BIT(6)
#define BIT_AP_AHB_DMA_EB2                           BIT(5)
#define BIT_AP_AHB_DMA_EB                            BIT(4)
#define BIT_AP_AHB_NANDC_26M_EB                      BIT(3)
#define BIT_AP_AHB_NANDC_ECC_EB                      BIT(2)
#define BIT_AP_AHB_NANDC_EB                          BIT(1)
#define BIT_AP_AHB_CKG_EB                            BIT(0)

/* REG_AP_AHB_AHB_RST */

#define BIT_AP_AHB_EMMC_SOFT_RST                     BIT(4)
#define BIT_AP_AHB_SDIO_MST_SOFT_RST                 BIT(3)
#define BIT_AP_AHB_DMA_SOFT_RST                      BIT(2)
#define BIT_AP_AHB_USB0_SOFT_RST                     BIT(1)
#define BIT_AP_AHB_NANDC_SOFT_RST                    BIT(0)

/* REG_AP_AHB_AP_SYS_SLEEP_CFG */

#define BIT_AP_AHB_SLEEP_FOLLOW_APCPU_EN             BIT(5)
#define BIT_AP_AHB_APCPU_SYS_SW_SLEEP                BIT(4)
#define BIT_AP_AHB_DMA_ACT_LIGHT_EN                  BIT(3)
#define BIT_AP_AHB_AP_APB_FRC_SLP                    BIT(2)
#define BIT_AP_AHB_AP_PERI_FRC_SLP                   BIT(1)
#define BIT_AP_AHB_AP_PERI_FRC_ON                    BIT(0)

/* REG_AP_AHB_CLOCK_FREQUENCY_DOWN */

#define BIT_AP_AHB_APB2APB_SCLK_AUTO_GATE_EN         BIT(13)
#define BIT_AP_AHB_APB2APB_MCLK_AUTO_GATE_EN         BIT(12)
#define BIT_AP_AHB_CGM_CLK_AON_AXI_AUTO_GATE_EN      BIT(11)
#define BIT_AP_AHB_CGM_CLK_APCPU_AXI_AUTO_GATE_EN    BIT(10)
#define BIT_AP_AHB_AP_AXI_BUS_IDLE_BYPASS_USB0       BIT(9)
#define BIT_AP_AHB_AP_AXI_BUS_IDLE_BYPASS_NANDC      BIT(8)
#define BIT_AP_AHB_AP_AXI_BUS_IDLE_BYPASS_SDIO_MST   BIT(7)
#define BIT_AP_AHB_AP_AXI_BUS_IDLE_BYPASS_EMMC       BIT(6)
#define BIT_AP_AHB_AP_AXI_BUS_IDLE_BYPASS_APCPU      BIT(5)
#define BIT_AP_AHB_AP_AXI_BUS_IDLE_BYPASS_DMA        BIT(4)
#define BIT_AP_AHB_AP_PERI_APB_AUTO_CONTROL_SEL      BIT(3)
#define BIT_AP_AHB_AP_PERI_APB_AUTO_MUX_SEL(x)       (((x) & 0x3) << 1)
#define BIT_AP_AHB_AP_PERI_APB_AUTO_MUX_EN           BIT(0)

/* REG_AP_AHB_USB0_CTRL */

#define BIT_AP_AHB_PIPE3_POWERPRESENT0               BIT(16)
#define BIT_AP_AHB_UTMISRP_BVALID_REG0               BIT(15)
#define BIT_AP_AHB_OTG_VBUS_VALID_PHYREG0            BIT(14)
#define BIT_AP_AHB_OTG_VBUS_VALID_PHYREG_SEL0        BIT(13)
#define BIT_AP_AHB_HOST_SYSTEM_ERR0                  BIT(12)
#define BIT_AP_AHB_HOST_PORT_POWER_CONTROL_PRESENT0  BIT(11)
#define BIT_AP_AHB_FLADJ_30MHZ_REG0(x)               (((x) & 0x3F) << 5)
#define BIT_AP_AHB_PME_EN0                           BIT(4)
#define BIT_AP_AHB_BUS_FILTER_BYPASS0(x)             (((x) & 0xF))

/* REG_AP_AHB_USB0_DBG0 */

#define BIT_AP_AHB_USB0_DUG_0(x)                     (((x) & 0xFFFFFFFF))

/* REG_AP_AHB_USB0_DBG1 */

#define BIT_AP_AHB_USB0_DUG_1(x)                     (((x) & 0xFFFFFFFF))

/* REG_AP_AHB_USB0_DBG2 */

#define BIT_AP_AHB_USB0_HOST_CURRENT_BELT(x)         (((x) & 0xFFF) << 6)
#define BIT_AP_AHB_USB0_CLK_GATE_CTRL(x)             (((x) & 0x7) << 3)
#define BIT_AP_AHB_USB0_DUG_2(x)                     (((x) & 0x7))

/* REG_AP_AHB_APB_PCLK_AUTO_GATE_EB */

#define BIT_AP_AHB_SDIO_MST_PCLK_AUTO_GATE_EB        BIT(1)
#define BIT_AP_AHB_EMMC_PCLK_AUTO_GATE_EB            BIT(0)

/* REG_AP_AHB_APB_PCLK_AUTO_SLOW_SEL */

#define BIT_AP_AHB_SDIO_MST_PCLK_AUTO_SLOW_EN        BIT(7)
#define BIT_AP_AHB_SDIO_MST_PCLK_AUTO_SLOW_SEL(x)    (((x) & 0x7) << 4)
#define BIT_AP_AHB_EMMC_PCLK_AUTO_SLOW_EN            BIT(3)
#define BIT_AP_AHB_EMMC_PCLK_AUTO_SLOW_SEL(x)        (((x) & 0x7))

/* REG_AP_AHB_AP_SYS_CLK_FRC_OFF0 */

#define BIT_AP_AHB_PCIE_AUX_CLK_FRC_OFF              BIT(29)
#define BIT_AP_AHB_USB1_SUSPEND_CLK_FRC_OFF          BIT(28)
#define BIT_AP_AHB_USB1_REF_CLK_FRC_OFF              BIT(27)
#define BIT_AP_AHB_USB0_SUSPEND_CLK_FRC_OFF          BIT(26)
#define BIT_AP_AHB_USB0_REF_CLK_FRC_OFF              BIT(25)
#define BIT_AP_AHB_NANDC_CLK_FRC_OFF                 BIT(24)
#define BIT_AP_AHB_NANDC_ECC_CLK_FRC_OFF             BIT(23)
#define BIT_AP_AHB_NANDC_26M_CLK_FRC_OFF             BIT(22)
#define BIT_AP_AHB_EMMC_CLK_FRC_OFF                  BIT(21)
#define BIT_AP_AHB_EMMC_32K_CLK_FRC_OFF              BIT(20)
#define BIT_AP_AHB_SDIO_SLV_CLK_FRC_OFF              BIT(19)
#define BIT_AP_AHB_SDIO_SLV_FRUN_CLK_FRC_OFF         BIT(18)
#define BIT_AP_AHB_SDIO_MST_CLK_FRC_OFF              BIT(17)
#define BIT_AP_AHB_SDIO_MST_32K_CLK_FRC_OFF          BIT(16)
#define BIT_AP_AHB_SIM0_32K_CLK_FRC_OFF              BIT(15)
#define BIT_AP_AHB_SIM0_CLK_FRC_OFF                  BIT(14)
#define BIT_AP_AHB_PWM3_CLK_FRC_OFF                  BIT(13)
#define BIT_AP_AHB_PWM2_CLK_FRC_OFF                  BIT(12)
#define BIT_AP_AHB_PWM1_CLK_FRC_OFF                  BIT(11)
#define BIT_AP_AHB_PWM0_CLK_FRC_OFF                  BIT(10)
#define BIT_AP_AHB_SPI2_CLK_FRC_OFF                  BIT(9)
#define BIT_AP_AHB_SPI1_CLK_FRC_OFF                  BIT(8)
#define BIT_AP_AHB_SPI0_CLK_FRC_OFF                  BIT(7)
#define BIT_AP_AHB_I2C4_CLK_FRC_OFF                  BIT(6)
#define BIT_AP_AHB_I2C3_CLK_FRC_OFF                  BIT(5)
#define BIT_AP_AHB_I2C2_CLK_FRC_OFF                  BIT(4)
#define BIT_AP_AHB_I2C1_CLK_FRC_OFF                  BIT(3)
#define BIT_AP_AHB_I2C0_CLK_FRC_OFF                  BIT(2)
#define BIT_AP_AHB_UART0_CLK_FRC_OFF                 BIT(1)
#define BIT_AP_AHB_AP_APB_CLK_FRC_OFF                BIT(0)

/* REG_AP_AHB_AP_SYS_CLK_FRC_ON0 */

#define BIT_AP_AHB_PCIE_AUX_CLK_FRC_ON               BIT(29)
#define BIT_AP_AHB_USB1_SUSPEND_CLK_FRC_ON           BIT(28)
#define BIT_AP_AHB_USB1_REF_CLK_FRC_ON               BIT(27)
#define BIT_AP_AHB_USB0_SUSPEND_CLK_FRC_ON           BIT(26)
#define BIT_AP_AHB_USB0_REF_CLK_FRC_ON               BIT(25)
#define BIT_AP_AHB_NANDC_CLK_FRC_ON                  BIT(24)
#define BIT_AP_AHB_NANDC_ECC_CLK_FRC_ON              BIT(23)
#define BIT_AP_AHB_NANDC_26M_CLK_FRC_ON              BIT(22)
#define BIT_AP_AHB_EMMC_CLK_FRC_ON                   BIT(21)
#define BIT_AP_AHB_EMMC_32K_CLK_FRC_ON               BIT(20)
#define BIT_AP_AHB_SDIO_SLV_CLK_FRC_ON               BIT(19)
#define BIT_AP_AHB_SDIO_SLV_FRUN_CLK_FRC_ON          BIT(18)
#define BIT_AP_AHB_SDIO_MST_CLK_FRC_ON               BIT(17)
#define BIT_AP_AHB_SDIO_MST_32K_CLK_FRC_ON           BIT(16)
#define BIT_AP_AHB_SIM0_32K_CLK_FRC_ON               BIT(15)
#define BIT_AP_AHB_SIM0_CLK_FRC_ON                   BIT(14)
#define BIT_AP_AHB_PWM3_CLK_FRC_ON                   BIT(13)
#define BIT_AP_AHB_PWM2_CLK_FRC_ON                   BIT(12)
#define BIT_AP_AHB_PWM1_CLK_FRC_ON                   BIT(11)
#define BIT_AP_AHB_PWM0_CLK_FRC_ON                   BIT(10)
#define BIT_AP_AHB_SPI2_CLK_FRC_ON                   BIT(9)
#define BIT_AP_AHB_SPI1_CLK_FRC_ON                   BIT(8)
#define BIT_AP_AHB_SPI0_CLK_FRC_ON                   BIT(7)
#define BIT_AP_AHB_I2C4_CLK_FRC_ON                   BIT(6)
#define BIT_AP_AHB_I2C3_CLK_FRC_ON                   BIT(5)
#define BIT_AP_AHB_I2C2_CLK_FRC_ON                   BIT(4)
#define BIT_AP_AHB_I2C1_CLK_FRC_ON                   BIT(3)
#define BIT_AP_AHB_I2C0_CLK_FRC_ON                   BIT(2)
#define BIT_AP_AHB_UART0_CLK_FRC_ON                  BIT(1)
#define BIT_AP_AHB_AP_APB_CLK_FRC_ON                 BIT(0)

/* REG_AP_AHB_AP_SYS_CLK_BUS_AUTO_EN */

#define BIT_AP_AHB_PCIE_AUX_CLK_BUS_AUTO_EN          BIT(23)
#define BIT_AP_AHB_USB1_REF_CLK_BUS_AUTO_EN          BIT(22)
#define BIT_AP_AHB_USB0_REF_CLK_BUS_AUTO_EN          BIT(21)
#define BIT_AP_AHB_NANDC_ECC_CLK_BUS_AUTO_EN         BIT(20)
#define BIT_AP_AHB_NANDC_26M_CLK_BUS_AUTO_EN         BIT(19)
#define BIT_AP_AHB_EMMC_32K_CLK_BUS_AUTO_EN          BIT(18)
#define BIT_AP_AHB_SDIO_SLV_FRUN_CLK_BUS_AUTO_EN     BIT(17)
#define BIT_AP_AHB_SDIO_MST_32K_CLK_BUS_AUTO_EN      BIT(16)
#define BIT_AP_AHB_SIM0_32K_CLK_BUS_AUTO_EN          BIT(15)
#define BIT_AP_AHB_SIM0_CLK_BUS_AUTO_EN              BIT(14)
#define BIT_AP_AHB_PWM3_CLK_BUS_AUTO_EN              BIT(13)
#define BIT_AP_AHB_PWM2_CLK_BUS_AUTO_EN              BIT(12)
#define BIT_AP_AHB_PWM1_CLK_BUS_AUTO_EN              BIT(11)
#define BIT_AP_AHB_PWM0_CLK_BUS_AUTO_EN              BIT(10)
#define BIT_AP_AHB_SPI2_CLK_BUS_AUTO_EN              BIT(9)
#define BIT_AP_AHB_SPI1_CLK_BUS_AUTO_EN              BIT(8)
#define BIT_AP_AHB_SPI0_CLK_BUS_AUTO_EN              BIT(7)
#define BIT_AP_AHB_I2C4_CLK_BUS_AUTO_EN              BIT(6)
#define BIT_AP_AHB_I2C3_CLK_BUS_AUTO_EN              BIT(5)
#define BIT_AP_AHB_I2C2_CLK_BUS_AUTO_EN              BIT(4)
#define BIT_AP_AHB_I2C1_CLK_BUS_AUTO_EN              BIT(3)
#define BIT_AP_AHB_I2C0_CLK_BUS_AUTO_EN              BIT(2)
#define BIT_AP_AHB_UART0_CLK_BUS_AUTO_EN             BIT(1)
#define BIT_AP_AHB_AP_APB_CLK_BUS_AUTO_EN            BIT(0)

/* REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG */

#define BIT_AP_AHB_CACTIVE_SLV3_WAKEUP_EN            BIT(3)
#define BIT_AP_AHB_AP_CLK_GATE_LPC_BYP               BIT(2)
#define BIT_AP_AHB_LP_AUTO_CTRL_EN                   BIT(1)
#define BIT_AP_AHB_MMTX_LPC_DISABLE                  BIT(0)

/* REG_AP_AHB_MMTX_M0_LPC */

#define BIT_AP_AHB_MMTX_M0_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_AHB_MMTX_M0_LP_EB                     BIT(16)
#define BIT_AP_AHB_MMTX_M0_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_AHB_MMTX_M1_LPC */

#define BIT_AP_AHB_MMTX_M1_LP_EB                     BIT(16)
#define BIT_AP_AHB_MMTX_M1_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_AHB_MMTX_M2_LPC */

#define BIT_AP_AHB_MMTX_M2_LP_EB                     BIT(16)
#define BIT_AP_AHB_MMTX_M2_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_AHB_MMTX_M3_LPC */

#define BIT_AP_AHB_MMTX_M3_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_AHB_MMTX_M3_LP_EB                     BIT(16)
#define BIT_AP_AHB_MMTX_M3_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_AHB_MMTX_M4_LPC */

#define BIT_AP_AHB_MMTX_M4_LP_EB                     BIT(16)
#define BIT_AP_AHB_MMTX_M4_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_AHB_MMTX_M5_LPC */

#define BIT_AP_AHB_MMTX_M5_LP_EB                     BIT(16)
#define BIT_AP_AHB_MMTX_M5_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_AHB_MMTX_M6_LPC */

#define BIT_AP_AHB_MMTX_M6_LP_EB                     BIT(16)
#define BIT_AP_AHB_MMTX_M6_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_AHB_MMTX_MAIN_LPC */

#define BIT_AP_AHB_CGM_MMTX_AUTO_GATE_EN             BIT(17)
#define BIT_AP_AHB_MMTX_MAIN_LP_EB                   BIT(16)
#define BIT_AP_AHB_MMTX_MAIN_LP_NUM(x)               (((x) & 0xFFFF))

/* REG_AP_AHB_MMTX_S0_LPC */

#define BIT_AP_AHB_MMTX_S0_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_AHB_CGM_MMTX_S0_AUTO_GATE_EN          BIT(17)
#define BIT_AP_AHB_MMTX_S0_LP_EB                     BIT(16)
#define BIT_AP_AHB_MMTX_S0_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_AHB_MMTX_S1_LPC */

#define BIT_AP_AHB_MMTX_S1_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_AHB_CGM_MMTX_S1_AUTO_GATE_EN          BIT(17)
#define BIT_AP_AHB_MMTX_S1_LP_EB                     BIT(16)
#define BIT_AP_AHB_MMTX_S1_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_AHB_MMTX_S2_LPC */

#define BIT_AP_AHB_MMTX_S2_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_AHB_CGM_MMTX_S2_AUTO_GATE_EN          BIT(17)
#define BIT_AP_AHB_MMTX_S2_LP_EB                     BIT(16)
#define BIT_AP_AHB_MMTX_S2_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_AHB_MMTX_S3_LPC */

#define BIT_AP_AHB_MMTX_S3_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_AHB_CGM_MMTX_S3_AUTO_GATE_EN          BIT(17)
#define BIT_AP_AHB_MMTX_S3_LP_EB                     BIT(16)
#define BIT_AP_AHB_MMTX_S3_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_AHB_MMTX_S4_LPC */

#define BIT_AP_AHB_MMTX_S4_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_AHB_CGM_MMTX_S4_AUTO_GATE_EN          BIT(17)
#define BIT_AP_AHB_MMTX_S4_LP_EB                     BIT(16)
#define BIT_AP_AHB_MMTX_S4_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_AHB_MMTX_S5_LPC */

#define BIT_AP_AHB_MMTX_S5_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_AHB_CGM_MMTX_S5_AUTO_GATE_EN          BIT(17)
#define BIT_AP_AHB_MMTX_S5_LP_EB                     BIT(16)
#define BIT_AP_AHB_MMTX_S5_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_AHB_MMTX_S6_LPC */

#define BIT_AP_AHB_MMTX_S6_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_AHB_CGM_MMTX_S6_AUTO_GATE_EN          BIT(17)
#define BIT_AP_AHB_MMTX_S6_LP_EB                     BIT(16)
#define BIT_AP_AHB_MMTX_S6_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_AHB_MMTX_MST_FRC_LSLP */

#define BIT_AP_AHB_MMTX_S6_FRC_LSLP                  BIT(7)
#define BIT_AP_AHB_MMTX_M6_FRC_LSLP                  BIT(6)
#define BIT_AP_AHB_MMTX_M5_FRC_LSLP                  BIT(5)
#define BIT_AP_AHB_MMTX_M4_FRC_LSLP                  BIT(4)
#define BIT_AP_AHB_MMTX_M3_FRC_LSLP                  BIT(3)
#define BIT_AP_AHB_MMTX_M2_FRC_LSLP                  BIT(2)
#define BIT_AP_AHB_MMTX_M1_FRC_LSLP                  BIT(1)

/* REG_AP_AHB_MMTX_LSLP_LPC_BYPASS */

#define BIT_AP_AHB_LSLP_MMTX_S6_LPC_BYPASS           BIT(7)
#define BIT_AP_AHB_LSLP_MMTX_M6_LPC_BYPASS           BIT(6)
#define BIT_AP_AHB_LSLP_MMTX_M5_LPC_BYPASS           BIT(5)
#define BIT_AP_AHB_LSLP_MMTX_M4_LPC_BYPASS           BIT(4)
#define BIT_AP_AHB_LSLP_MMTX_M3_LPC_BYPASS           BIT(3)
#define BIT_AP_AHB_LSLP_MMTX_M2_LPC_BYPASS           BIT(2)
#define BIT_AP_AHB_LSLP_MMTX_M1_LPC_BYPASS           BIT(1)

/* REG_AP_AHB_MMTX_MST_FRC_PUB_DSLP */

#define BIT_AP_AHB_MMTX_S6_FRC_PUB_DSLP              BIT(7)
#define BIT_AP_AHB_MMTX_M6_FRC_PUB_DSLP              BIT(6)
#define BIT_AP_AHB_MMTX_M5_FRC_PUB_DSLP              BIT(5)
#define BIT_AP_AHB_MMTX_M4_FRC_PUB_DSLP              BIT(4)
#define BIT_AP_AHB_MMTX_M3_FRC_PUB_DSLP              BIT(3)
#define BIT_AP_AHB_MMTX_M2_FRC_PUB_DSLP              BIT(2)
#define BIT_AP_AHB_MMTX_M1_FRC_PUB_DSLP              BIT(1)

/* REG_AP_AHB_MMTX_PUB_DSLP_LPC_BYPASS */

#define BIT_AP_AHB_PUB_DSLP_MMTX_S6_LPC_BYPASS       BIT(7)
#define BIT_AP_AHB_PUB_DSLP_MMTX_M6_LPC_BYPASS       BIT(6)
#define BIT_AP_AHB_PUB_DSLP_MMTX_M5_LPC_BYPASS       BIT(5)
#define BIT_AP_AHB_PUB_DSLP_MMTX_M4_LPC_BYPASS       BIT(4)
#define BIT_AP_AHB_PUB_DSLP_MMTX_M3_LPC_BYPASS       BIT(3)
#define BIT_AP_AHB_PUB_DSLP_MMTX_M2_LPC_BYPASS       BIT(2)
#define BIT_AP_AHB_PUB_DSLP_MMTX_M1_LPC_BYPASS       BIT(1)

/* REG_AP_AHB_MMTX_MST_FRC_DOZE */

#define BIT_AP_AHB_MMTX_M6_FRC_DOZE                  BIT(6)
#define BIT_AP_AHB_MMTX_M5_FRC_DOZE                  BIT(5)
#define BIT_AP_AHB_MMTX_M4_FRC_DOZE                  BIT(4)
#define BIT_AP_AHB_MMTX_M3_FRC_DOZE                  BIT(3)
#define BIT_AP_AHB_MMTX_M2_FRC_DOZE                  BIT(2)
#define BIT_AP_AHB_MMTX_M1_FRC_DOZE                  BIT(1)
#define BIT_AP_AHB_MMTX_M0_FRC_DOZE                  BIT(0)

/* REG_AP_AHB_MMTX_DOZE_LPC_BYPASS */

#define BIT_AP_AHB_DOZE_MMTX_MAIN_LPC_BYPASS         BIT(14)
#define BIT_AP_AHB_DOZE_MMTX_S6_LPC_BYPASS           BIT(13)
#define BIT_AP_AHB_DOZE_MMTX_S5_LPC_BYPASS           BIT(12)
#define BIT_AP_AHB_DOZE_MMTX_S4_LPC_BYPASS           BIT(11)
#define BIT_AP_AHB_DOZE_MMTX_S3_LPC_BYPASS           BIT(10)
#define BIT_AP_AHB_DOZE_MMTX_S2_LPC_BYPASS           BIT(9)
#define BIT_AP_AHB_DOZE_MMTX_S1_LPC_BYPASS           BIT(8)
#define BIT_AP_AHB_DOZE_MMTX_S0_LPC_BYPASS           BIT(7)
#define BIT_AP_AHB_DOZE_MMTX_M6_LPC_BYPASS           BIT(6)
#define BIT_AP_AHB_DOZE_MMTX_M5_LPC_BYPASS           BIT(5)
#define BIT_AP_AHB_DOZE_MMTX_M4_LPC_BYPASS           BIT(4)
#define BIT_AP_AHB_DOZE_MMTX_M3_LPC_BYPASS           BIT(3)
#define BIT_AP_AHB_DOZE_MMTX_M2_LPC_BYPASS           BIT(2)
#define BIT_AP_AHB_DOZE_MMTX_M1_LPC_BYPASS           BIT(1)
#define BIT_AP_AHB_DOZE_MMTX_M0_LPC_BYPASS           BIT(0)

/* REG_AP_AHB_MMTX_AXI_FREQ_ALLOW0 */

#define BIT_AP_AHB_MMTX_AXI_FREQ_DFS_SW(x)           (((x) & 0xF) << 28)
#define BIT_AP_AHB_MMTX_M6_AXI_FREQ_ALLOW(x)         (((x) & 0xF) << 24)
#define BIT_AP_AHB_MMTX_M5_AXI_FREQ_ALLOW(x)         (((x) & 0xF) << 20)
#define BIT_AP_AHB_MMTX_M4_AXI_FREQ_ALLOW(x)         (((x) & 0xF) << 16)
#define BIT_AP_AHB_MMTX_M3_AXI_FREQ_ALLOW(x)         (((x) & 0xF) << 12)
#define BIT_AP_AHB_MMTX_M2_AXI_FREQ_ALLOW(x)         (((x) & 0xF) << 8)
#define BIT_AP_AHB_MMTX_M1_AXI_FREQ_ALLOW(x)         (((x) & 0xF) << 4)
#define BIT_AP_AHB_MMTX_M0_AXI_FREQ_ALLOW(x)         (((x) & 0xF))

/* REG_AP_AHB_MMTX_AXI_FREQ_ALLOW1 */

#define BIT_AP_AHB_MMTX_AXI_FREQ_DFS_MODE(x)         (((x) & 0x3))

/* REG_AP_AHB_MMTX_AXI_FREQ_LSLP_ALLOW0 */

#define BIT_AP_AHB_MMTX_AXI_FREQ_LSLP_DFS_SW(x)      (((x) & 0xF) << 28)
#define BIT_AP_AHB_MMTX_M6_AXI_FREQ_LSLP_ALLOW(x)    (((x) & 0xF) << 24)
#define BIT_AP_AHB_MMTX_M5_AXI_FREQ_LSLP_ALLOW(x)    (((x) & 0xF) << 20)
#define BIT_AP_AHB_MMTX_M4_AXI_FREQ_LSLP_ALLOW(x)    (((x) & 0xF) << 16)
#define BIT_AP_AHB_MMTX_M3_AXI_FREQ_LSLP_ALLOW(x)    (((x) & 0xF) << 12)
#define BIT_AP_AHB_MMTX_M2_AXI_FREQ_LSLP_ALLOW(x)    (((x) & 0xF) << 8)
#define BIT_AP_AHB_MMTX_M1_AXI_FREQ_LSLP_ALLOW(x)    (((x) & 0xF) << 4)
#define BIT_AP_AHB_MMTX_M0_AXI_FREQ_LSLP_ALLOW(x)    (((x) & 0xF))

/* REG_AP_AHB_MMTX_AXI_FREQ_LSLP_ALLOW1 */

#define BIT_AP_AHB_MMTX_AXI_FREQ_LSLP_DFS_MODE(x)    (((x) & 0x3))

/* REG_AP_AHB_AP_QOS0 */

#define BIT_AP_AHB_ARQOS_USB0(x)                     (((x) & 0xF) << 28)
#define BIT_AP_AHB_AWQOS_USB0(x)                     (((x) & 0xF) << 24)
#define BIT_AP_AHB_ARQOS_EMMC(x)                     (((x) & 0xF) << 20)
#define BIT_AP_AHB_AWQOS_EMMC(x)                     (((x) & 0xF) << 16)
#define BIT_AP_AHB_ARQOS_SDIO_MST(x)                 (((x) & 0xF) << 12)
#define BIT_AP_AHB_AWQOS_SDIO_MST(x)                 (((x) & 0xF) << 8)
#define BIT_AP_AHB_ARQOS_NANDC(x)                    (((x) & 0xF) << 4)
#define BIT_AP_AHB_AWQOS_NANDC(x)                    (((x) & 0xF))

/* REG_AP_AHB_AP_QOS1 */

#define BIT_AP_AHB_ARQOS_DMA(x)                      (((x) & 0xF) << 4)
#define BIT_AP_AHB_AWQOS_DMA(x)                      (((x) & 0xF))

/* REG_AP_AHB_AP_URGENCY */

#define BIT_AP_AHB_ARURGENCY_DMA(x)                  (((x) & 0x3) << 18)
#define BIT_AP_AHB_AWURGENCY_DMA(x)                  (((x) & 0x3) << 16)
#define BIT_AP_AHB_ARURGENCY_USB0(x)                 (((x) & 0x3) << 14)
#define BIT_AP_AHB_AWURGENCY_USB0(x)                 (((x) & 0x3) << 12)
#define BIT_AP_AHB_ARURGENCY_EMMC(x)                 (((x) & 0x3) << 10)
#define BIT_AP_AHB_AWURGENCY_EMMC(x)                 (((x) & 0x3) << 8)
#define BIT_AP_AHB_ARURGENCY_SDIO_MST(x)             (((x) & 0x3) << 6)
#define BIT_AP_AHB_AWURGENCY_SDIO_MST(x)             (((x) & 0x3) << 4)
#define BIT_AP_AHB_ARURGENCY_NANDC(x)                (((x) & 0x3) << 2)
#define BIT_AP_AHB_AWURGENCY_NANDC(x)                (((x) & 0x3))

/* REG_AP_AHB_AP_USER0 */

#define BIT_AP_AHB_ARUSER_EMMC(x)                    (((x) & 0xFF) << 24)
#define BIT_AP_AHB_AWUSER_EMMC(x)                    (((x) & 0xFF) << 16)
#define BIT_AP_AHB_ARUSER_SDIO_MST(x)                (((x) & 0xFF) << 8)
#define BIT_AP_AHB_AWUSER_SDIO_MST(x)                (((x) & 0xFF))

/* REG_AP_AHB_AP_USER1 */

#define BIT_AP_AHB_ARUSER_USB0(x)                    (((x) & 0xFF) << 24)
#define BIT_AP_AHB_AWUSER_USB0(x)                    (((x) & 0xFF) << 16)
#define BIT_AP_AHB_ARUSER_NANDC(x)                   (((x) & 0xFF) << 8)
#define BIT_AP_AHB_AWUSER_NANDC(x)                   (((x) & 0xFF))

/* REG_AP_AHB_MMTX_CTRL */

#define BIT_AP_AHB_MMTX_BUSMON_ENABLE                BIT(0)

/* REG_AP_AHB_MMTX_PU_NUM0 */

#define BIT_AP_AHB_MMTX_M3_PU_NUM(x)                 (((x) & 0xFF) << 24)
#define BIT_AP_AHB_MMTX_M2_PU_NUM(x)                 (((x) & 0xFF) << 16)
#define BIT_AP_AHB_MMTX_M1_PU_NUM(x)                 (((x) & 0xFF) << 8)
#define BIT_AP_AHB_MMTX_M0_PU_NUM(x)                 (((x) & 0xFF))

/* REG_AP_AHB_MMTX_PU_NUM1 */

#define BIT_AP_AHB_MMTX_MAIN_PU_NUM(x)               (((x) & 0xFF) << 24)
#define BIT_AP_AHB_MMTX_M6_PU_NUM(x)                 (((x) & 0xFF) << 16)
#define BIT_AP_AHB_MMTX_M5_PU_NUM(x)                 (((x) & 0xFF) << 8)
#define BIT_AP_AHB_MMTX_M4_PU_NUM(x)                 (((x) & 0xFF))

/* REG_AP_AHB_MMTX_PU_NUM2 */

#define BIT_AP_AHB_MMTX_S3_PU_NUM(x)                 (((x) & 0xFF) << 24)
#define BIT_AP_AHB_MMTX_S2_PU_NUM(x)                 (((x) & 0xFF) << 16)
#define BIT_AP_AHB_MMTX_S1_PU_NUM(x)                 (((x) & 0xFF) << 8)
#define BIT_AP_AHB_MMTX_S0_PU_NUM(x)                 (((x) & 0xFF))

/* REG_AP_AHB_MMTX_PU_NUM3 */

#define BIT_AP_AHB_MMTX_S6_PU_NUM(x)                 (((x) & 0xFF) << 16)
#define BIT_AP_AHB_MMTX_S5_PU_NUM(x)                 (((x) & 0xFF) << 8)
#define BIT_AP_AHB_MMTX_S4_PU_NUM(x)                 (((x) & 0xFF))

/* REG_AP_AHB_USE_IP_BUSY_GATING */

#define BIT_AP_AHB_DDR_BUSY_GATING_EB                BIT(1)
#define BIT_AP_AHB_DMA_BUSY_GATING_EB                BIT(0)

/* REG_AP_AHB_RESERVE0 */

#define BIT_AP_AHB_RESERVE0(x)                       (((x) & 0xFFFFFFFF))

/* REG_AP_AHB_RESERVE1 */

#define BIT_AP_AHB_RESERVE1(x)                       (((x) & 0xFFFFFFFF))

/* REG_AP_AHB_CHIP_ID */

#define BIT_AP_AHB_CHIP_ID(x)                        (((x) & 0xFFFFFFFF))


#endif /* AP_AHB_H */


