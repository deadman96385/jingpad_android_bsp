/*
 * Copyright (C) 2018 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-11-07 10:41:46
 *
 */


#ifndef AP_AHB_H
#define AP_AHB_H

#define CTL_BASE_AP_AHB 0x20100000


#define REG_AP_AHB_AHB_EB                            ( CTL_BASE_AP_AHB + 0x0000 )
#define REG_AP_AHB_AHB_RST                           ( CTL_BASE_AP_AHB + 0x0004 )
#define REG_AP_AHB_AP_SYS_FORCE_SLEEP_CFG            ( CTL_BASE_AP_AHB + 0x000C )
#define REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG             ( CTL_BASE_AP_AHB + 0x0010 )
#define REG_AP_AHB_HOLDING_PEN                       ( CTL_BASE_AP_AHB + 0x0014 )
#define REG_AP_AHB_CLOCK_FREQUENCY_DOWN              ( CTL_BASE_AP_AHB + 0x0018 )
#define REG_AP_AHB_AP_SYS_CLK_EN_FRC_OFF_0           ( CTL_BASE_AP_AHB + 0x0020 )
#define REG_AP_AHB_AP_SYS_CLK_EN_FRC_OFF_1           ( CTL_BASE_AP_AHB + 0x0024 )
#define REG_AP_AHB_AP_SYS_CLK_EN_FRC_ON_0            ( CTL_BASE_AP_AHB + 0x0028 )
#define REG_AP_AHB_AP_SYS_CLK_EN_FRC_ON_1            ( CTL_BASE_AP_AHB + 0x002C )
#define REG_AP_AHB_MISC_CKG_EN                       ( CTL_BASE_AP_AHB + 0x0040 )
#define REG_AP_AHB_DISP_ASYNC_BRG                    ( CTL_BASE_AP_AHB + 0x0050 )
#define REG_AP_AHB_S6_LPC                            ( CTL_BASE_AP_AHB + 0x0054 )
#define REG_AP_AHB_S5_LPC                            ( CTL_BASE_AP_AHB + 0x0058 )
#define REG_AP_AHB_AP_ASYNC_BRG                      ( CTL_BASE_AP_AHB + 0x005C )
#define REG_AP_AHB_M0_LPC                            ( CTL_BASE_AP_AHB + 0x0060 )
#define REG_AP_AHB_M1_LPC                            ( CTL_BASE_AP_AHB + 0x0064 )
#define REG_AP_AHB_M2_LPC                            ( CTL_BASE_AP_AHB + 0x0068 )
#define REG_AP_AHB_M3_LPC                            ( CTL_BASE_AP_AHB + 0x006C )
#define REG_AP_AHB_M4_LPC                            ( CTL_BASE_AP_AHB + 0x0070 )
#define REG_AP_AHB_M5_LPC                            ( CTL_BASE_AP_AHB + 0x0074 )
#define REG_AP_AHB_M6_LPC                            ( CTL_BASE_AP_AHB + 0x0078 )
#define REG_AP_AHB_MAIN_LPC                          ( CTL_BASE_AP_AHB + 0x0088 )
#define REG_AP_AHB_S0_LPC                            ( CTL_BASE_AP_AHB + 0x008C )
#define REG_AP_AHB_S1_LPC                            ( CTL_BASE_AP_AHB + 0x0090 )
#define REG_AP_AHB_S2_LPC                            ( CTL_BASE_AP_AHB + 0x0094 )
#define REG_AP_AHB_S3_LPC                            ( CTL_BASE_AP_AHB + 0x0098 )
#define REG_AP_AHB_S4_LPC                            ( CTL_BASE_AP_AHB + 0x009C )
#define REG_AP_AHB_MERGE_M0_LPC                      ( CTL_BASE_AP_AHB + 0x00A0 )
#define REG_AP_AHB_MERGE_M1_LPC                      ( CTL_BASE_AP_AHB + 0x00A4 )
#define REG_AP_AHB_MERGE_S0_LPC                      ( CTL_BASE_AP_AHB + 0x00AC )
#define REG_AP_AHB_AP_QOS0                           ( CTL_BASE_AP_AHB + 0x00B0 )
#define REG_AP_AHB_AP_QOS1                           ( CTL_BASE_AP_AHB + 0x00B8 )
#define REG_AP_AHB_AP_QOS2                           ( CTL_BASE_AP_AHB + 0x00BC )
#define REG_AP_AHB_ASYNC_BRIDGE_IDLE_OVERFLOW        ( CTL_BASE_AP_AHB + 0x00C0 )
#define REG_AP_AHB_ASYNC_BRIDGE_DEBUG_SIGNAL_W_VDSP  ( CTL_BASE_AP_AHB + 0x00C4 )
#define REG_AP_AHB_ASYNC_BRIDGE_DEBUG_SIGNAL_W_DISP  ( CTL_BASE_AP_AHB + 0x00C8 )
#define REG_AP_AHB_ASYNC_BRIDGE_DEBUG_SIGNAL_W_AP    ( CTL_BASE_AP_AHB + 0x00CC )
#define REG_AP_AHB_SYS_RST                           ( CTL_BASE_AP_AHB + 0x3010 )
#define REG_AP_AHB_CACHE_EMMC_SDIO                   ( CTL_BASE_AP_AHB + 0x3014 )
#define REG_AP_AHB_AP_QOS_CFG                        ( CTL_BASE_AP_AHB + 0x301C )
#define REG_AP_AHB_DSI_PHY                           ( CTL_BASE_AP_AHB + 0x3034 )
#define REG_AP_AHB_CHIP_ID                           ( CTL_BASE_AP_AHB + 0x30FC )

/* REG_AP_AHB_AHB_EB */

#define BIT_AP_AHB_CKG_EB                           BIT(7)
#define BIT_AP_AHB_DMA_EB                           BIT(5)
#define BIT_AP_AHB_DMA_ENABLE                       BIT(4)
#define BIT_AP_AHB_VSP_EB                           BIT(2)
#define BIT_AP_AHB_DISPC_EB                         BIT(1)
#define BIT_AP_AHB_DSI_EB                           BIT(0)

/* REG_AP_AHB_AHB_RST */

#define BIT_AP_AHB_VSP_SOFT_RST                     BIT(13)
#define BIT_AP_AHB_VPP_SOFT_RST                     BIT(12)
#define BIT_AP_AHB_VSP_GLOBAL_SOFT_RST              BIT(11)
#define BIT_AP_AHB_DMA_SOFT_RST                     BIT(8)
#define BIT_AP_AHB_DISPC_SOFT_RST                   BIT(1)
#define BIT_AP_AHB_DSI_SOFT_RST                     BIT(0)

/* REG_AP_AHB_AP_SYS_FORCE_SLEEP_CFG */

#define BIT_AP_AHB_AXI_LP_CTRL_DISABLE              BIT(3)
#define BIT_AP_AHB_PERI_FORCE_ON                    BIT(2)
#define BIT_AP_AHB_PERI_FORCE_OFF                   BIT(1)
#define BIT_AP_AHB_CGM_CLK_AP_AXI_AUTO_GATE_EN      BIT(0)

/* REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG */

#define BIT_AP_AHB_AP_MAINMTX_LP_DISABLE            BIT(6)
#define BIT_AP_AHB_AP_AHB_AUTO_GATE_EN              BIT(5)
#define BIT_AP_AHB_AP_EMC_AUTO_GATE_EN              BIT(4)

/* REG_AP_AHB_HOLDING_PEN */

#define BIT_AP_AHB_HOLDING_PEN(x)                   (((x) & 0xFFFFFFFF))

/* REG_AP_AHB_CLOCK_FREQUENCY_DOWN */

#define BIT_AP_AHB_AP_AXI_BUS_IDLE_BYPASS_SDIO2     BIT(9)
#define BIT_AP_AHB_AP_AXI_BUS_IDLE_BYPASS_SDIO1     BIT(8)
#define BIT_AP_AHB_AP_AXI_BUS_IDLE_BYPASS_SDIO0     BIT(7)
#define BIT_AP_AHB_AP_AXI_BUS_IDLE_BYPASS_EMMC      BIT(6)
#define BIT_AP_AHB_AP_AXI_BUS_IDLE_BYPASS_APCPU     BIT(5)
#define BIT_AP_AHB_AP_AXI_BUS_IDLE_BYPASS_DMA       BIT(4)
#define BIT_AP_AHB_AP_APB_AUTO_CONTROL_SEL          BIT(3)
#define BIT_AP_AHB_AP_APB_AUTO_MUX_SEL(x)           (((x) & 0x3) << 1)
#define BIT_AP_AHB_AP_APB_AUTO_MUX_EN               BIT(0)

/* REG_AP_AHB_AP_SYS_CLK_EN_FRC_OFF_0 */

#define BIT_AP_AHB_VSP_FRC_OFF                      BIT(28)
#define BIT_AP_AHB_SIM0_32K_FRC_OFF                 BIT(27)
#define BIT_AP_AHB_SDIO2_32K_FRC_OFF                BIT(26)
#define BIT_AP_AHB_SDIO1_32K_FRC_OFF                BIT(25)
#define BIT_AP_AHB_SDIO0_32K_FRC_OFF                BIT(24)
#define BIT_AP_AHB_EMMC_32K_FRC_OFF                 BIT(23)
#define BIT_AP_AHB_CE_FRC_OFF                       BIT(22)
#define BIT_AP_AHB_IIS2_FRC_OFF                     BIT(21)
#define BIT_AP_AHB_IIS1_FRC_OFF                     BIT(20)
#define BIT_AP_AHB_IIS0_FRC_OFF                     BIT(19)
#define BIT_AP_AHB_SPI3_FRC_OFF                     BIT(18)
#define BIT_AP_AHB_SPI2_FRC_OFF                     BIT(17)
#define BIT_AP_AHB_SPI1_FRC_OFF                     BIT(16)
#define BIT_AP_AHB_SPI0_FRC_OFF                     BIT(15)
#define BIT_AP_AHB_I2C4_FRC_OFF                     BIT(14)
#define BIT_AP_AHB_I2C3_FRC_OFF                     BIT(13)
#define BIT_AP_AHB_I2C2_FRC_OFF                     BIT(12)
#define BIT_AP_AHB_I2C1_FRC_OFF                     BIT(11)
#define BIT_AP_AHB_I2C0_FRC_OFF                     BIT(10)
#define BIT_AP_AHB_UART2_FRC_OFF                    BIT(9)
#define BIT_AP_AHB_UART1_FRC_OFF                    BIT(8)
#define BIT_AP_AHB_UART0_FRC_OFF                    BIT(7)
#define BIT_AP_AHB_AP_APB_FRC_OFF                   BIT(6)
#define BIT_AP_AHB_EMMC_1X_FRC_OFF                  BIT(5)
#define BIT_AP_AHB_EMMC_2X_FRC_OFF                  BIT(4)
#define BIT_AP_AHB_SDIO1_1X_FRC_OFF                 BIT(3)
#define BIT_AP_AHB_SDIO1_2X_FRC_OFF                 BIT(2)
#define BIT_AP_AHB_SDIO0_1X_FRC_OFF                 BIT(1)
#define BIT_AP_AHB_SDIO0_2X_FRC_OFF                 BIT(0)

/* REG_AP_AHB_AP_SYS_CLK_EN_FRC_OFF_1 */

#define BIT_AP_AHB_SIM_FRC_OFF                      BIT(5)
#define BIT_AP_AHB_DSI_APB_FRC_OFF                  BIT(4)
#define BIT_AP_AHB_DPHY_CFG_FRC_OFF                 BIT(3)
#define BIT_AP_AHB_DPHY_REF_FRC_OFF                 BIT(2)
#define BIT_AP_AHB_DISP_DPI_FRC_OFF                 BIT(1)
#define BIT_AP_AHB_DISP_FRC_OFF                     BIT(0)

/* REG_AP_AHB_AP_SYS_CLK_EN_FRC_ON_0 */

#define BIT_AP_AHB_VSP_FRC_ON                       BIT(28)
#define BIT_AP_AHB_SIM0_32K_FRC_ON                  BIT(27)
#define BIT_AP_AHB_SDIO2_32K_FRC_ON                 BIT(26)
#define BIT_AP_AHB_SDIO1_32K_FRC_ON                 BIT(25)
#define BIT_AP_AHB_SDIO0_32K_FRC_ON                 BIT(24)
#define BIT_AP_AHB_EMMC_32K_FRC_ON                  BIT(23)
#define BIT_AP_AHB_CE_FRC_ON                        BIT(22)
#define BIT_AP_AHB_IIS2_FRC_ON                      BIT(21)
#define BIT_AP_AHB_IIS1_FRC_ON                      BIT(20)
#define BIT_AP_AHB_IIS0_FRC_ON                      BIT(19)
#define BIT_AP_AHB_SPI3_FRC_ON                      BIT(18)
#define BIT_AP_AHB_SPI2_FRC_ON                      BIT(17)
#define BIT_AP_AHB_SPI1_FRC_ON                      BIT(16)
#define BIT_AP_AHB_SPI0_FRC_ON                      BIT(15)
#define BIT_AP_AHB_I2C4_FRC_ON                      BIT(14)
#define BIT_AP_AHB_I2C3_FRC_ON                      BIT(13)
#define BIT_AP_AHB_I2C2_FRC_ON                      BIT(12)
#define BIT_AP_AHB_I2C1_FRC_ON                      BIT(11)
#define BIT_AP_AHB_I2C0_FRC_ON                      BIT(10)
#define BIT_AP_AHB_UART2_FRC_ON                     BIT(9)
#define BIT_AP_AHB_UART1_FRC_ON                     BIT(8)
#define BIT_AP_AHB_UART0_FRC_ON                     BIT(7)
#define BIT_AP_AHB_AP_APB_FRC_ON                    BIT(6)
#define BIT_AP_AHB_EMMC_1X_FRC_ON                   BIT(5)
#define BIT_AP_AHB_EMMC_2X_FRC_ON                   BIT(4)
#define BIT_AP_AHB_SDIO1_1X_FRC_ON                  BIT(3)
#define BIT_AP_AHB_SDIO1_2X_FRC_ON                  BIT(2)
#define BIT_AP_AHB_SDIO0_1X_FRC_ON                  BIT(1)
#define BIT_AP_AHB_SDIO0_2X_FRC_ON                  BIT(0)

/* REG_AP_AHB_AP_SYS_CLK_EN_FRC_ON_1 */

#define BIT_AP_AHB_SIM_FRC_ON                       BIT(5)
#define BIT_AP_AHB_DSI_APB_FRC_ON                   BIT(4)
#define BIT_AP_AHB_DPHY_CFG_FRC_ON                  BIT(3)
#define BIT_AP_AHB_DPHY_REF_FRC_ON                  BIT(2)
#define BIT_AP_AHB_DISP_DPI_FRC_ON                  BIT(1)
#define BIT_AP_AHB_DISP_FRC_ON                      BIT(0)

/* REG_AP_AHB_MISC_CKG_EN */

#define BIT_AP_AHB_DPHY_REF_CKG_EN                  BIT(1)
#define BIT_AP_AHB_DPHY_CFG_CKG_EN                  BIT(0)

/* REG_AP_AHB_DISP_ASYNC_BRG */

#define BIT_AP_AHB_DISP_CSYSACK_SYNC_SEL            BIT(18)
#define BIT_AP_AHB_DISP_CACTIVE_SYNC_SEL            BIT(17)
#define BIT_AP_AHB_DISP_ASYNC_BRG_LP_NUM(x)         (((x) & 0xFFFF) << 1)
#define BIT_AP_AHB_DISP_ASYNC_BRG_LP_EB             BIT(0)

/* REG_AP_AHB_S6_LPC */

#define BIT_AP_AHB_CGM_MTX_S6_AUTO_GATE_EN          BIT(17)
#define BIT_AP_AHB_MAIN_S6_LP_EB                    BIT(16)
#define BIT_AP_AHB_MAIN_S6_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_S5_LPC */

#define BIT_AP_AHB_CGM_MTX_S5_AUTO_GATE_EN          BIT(17)
#define BIT_AP_AHB_MAIN_S5_LP_EB                    BIT(16)
#define BIT_AP_AHB_MAIN_S5_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_AP_ASYNC_BRG */

#define BIT_AP_AHB_AP_ASYNC_BRG_LP_NUM(x)           (((x) & 0xFFFF) << 1)
#define BIT_AP_AHB_AP_ASYNC_BRG_LP_EB               BIT(0)

/* REG_AP_AHB_M0_LPC */

#define BIT_AP_AHB_MAIN_M0_LP_EB                    BIT(16)
#define BIT_AP_AHB_MAIN_M0_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_M1_LPC */

#define BIT_AP_AHB_MAIN_M1_LP_EB                    BIT(16)
#define BIT_AP_AHB_MAIN_M1_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_M2_LPC */

#define BIT_AP_AHB_MAIN_M2_LP_EB                    BIT(16)
#define BIT_AP_AHB_MAIN_M2_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_M3_LPC */

#define BIT_AP_AHB_MAIN_M3_LP_EB                    BIT(16)
#define BIT_AP_AHB_MAIN_M3_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_M4_LPC */

#define BIT_AP_AHB_MAIN_M4_LP_EB                    BIT(16)
#define BIT_AP_AHB_MAIN_M4_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_M5_LPC */

#define BIT_AP_AHB_MAIN_M5_LP_EB                    BIT(16)
#define BIT_AP_AHB_MAIN_M5_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_M6_LPC */

#define BIT_AP_AHB_MAIN_M6_LP_EB                    BIT(16)
#define BIT_AP_AHB_MAIN_M6_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_MAIN_LPC */

#define BIT_AP_AHB_CGM_MATRIX_AUTO_GATE_EN          BIT(17)
#define BIT_AP_AHB_MAIN_LP_EB                       BIT(16)
#define BIT_AP_AHB_MAIN_LP_NUM(x)                   (((x) & 0xFFFF))

/* REG_AP_AHB_S0_LPC */

#define BIT_AP_AHB_CGM_MTX_S0_AUTO_GATE_EN          BIT(17)
#define BIT_AP_AHB_MAIN_S0_LP_EB                    BIT(16)
#define BIT_AP_AHB_MAIN_S0_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_S1_LPC */

#define BIT_AP_AHB_CGM_MTX_S1_AUTO_GATE_EN          BIT(17)
#define BIT_AP_AHB_MAIN_S1_LP_EB                    BIT(16)
#define BIT_AP_AHB_MAIN_S1_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_S2_LPC */

#define BIT_AP_AHB_CGM_MTX_S2_AUTO_GATE_EN          BIT(17)
#define BIT_AP_AHB_MAIN_S2_LP_EB                    BIT(16)
#define BIT_AP_AHB_MAIN_S2_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_S3_LPC */

#define BIT_AP_AHB_CGM_MTX_S3_AUTO_GATE_EN          BIT(17)
#define BIT_AP_AHB_MAIN_S3_LP_EB                    BIT(16)
#define BIT_AP_AHB_MAIN_S3_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_S4_LPC */

#define BIT_AP_AHB_CGM_MTX_S4_AUTO_GATE_EN          BIT(17)
#define BIT_AP_AHB_MAIN_S4_LP_EB                    BIT(16)
#define BIT_AP_AHB_MAIN_S4_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_MERGE_M0_LPC */

#define BIT_AP_AHB_MERGE_M0_LP_EB                   BIT(16)
#define BIT_AP_AHB_MERGE_M0_LP_NUM(x)               (((x) & 0xFFFF))

/* REG_AP_AHB_MERGE_M1_LPC */

#define BIT_AP_AHB_MERGE_M1_LP_EB                   BIT(16)
#define BIT_AP_AHB_MERGE_M1_LP_NUM(x)               (((x) & 0xFFFF))

/* REG_AP_AHB_MERGE_S0_LPC */

#define BIT_AP_AHB_CGM_MERGE_S0_AUTO_GATE_EN        BIT(17)
#define BIT_AP_AHB_MERGE_S0_LP_EB                   BIT(16)
#define BIT_AP_AHB_MERGE_S0_LP_NUM(x)               (((x) & 0xFFFF))

/* REG_AP_AHB_AP_QOS0 */

#define BIT_AP_AHB_ARQOS_CE(x)                      (((x) & 0xF) << 20)
#define BIT_AP_AHB_AWQOS_CE(x)                      (((x) & 0xF) << 16)
#define BIT_AP_AHB_ARQOS_DMA(x)                     (((x) & 0xF) << 12)
#define BIT_AP_AHB_AWQOS_DMA(x)                     (((x) & 0xF) << 8)

/* REG_AP_AHB_AP_QOS1 */

#define BIT_AP_AHB_ARQOS_SDIO0(x)                   (((x) & 0xF) << 28)
#define BIT_AP_AHB_AWQOS_SDIO0(x)                   (((x) & 0xF) << 24)
#define BIT_AP_AHB_ARQOS_SDIO1(x)                   (((x) & 0xF) << 20)
#define BIT_AP_AHB_AWQOS_SDIO1(x)                   (((x) & 0xF) << 16)
#define BIT_AP_AHB_ARQOS_SDIO2(x)                   (((x) & 0xF) << 12)
#define BIT_AP_AHB_AWQOS_SDIO2(x)                   (((x) & 0xF) << 8)
#define BIT_AP_AHB_ARQOS_EMMC(x)                    (((x) & 0xF) << 4)
#define BIT_AP_AHB_AWQOS_EMMC(x)                    (((x) & 0xF))

/* REG_AP_AHB_AP_QOS2 */

#define BIT_AP_AHB_ARQOS_THRESHHOLD_MAIN(x)         (((x) & 0xF) << 20)
#define BIT_AP_AHB_AWQOS_THRESHHOLD_MAIN(x)         (((x) & 0xF) << 16)
#define BIT_AP_AHB_ARQOS_THRESHHOLD_MERGE(x)        (((x) & 0xF) << 12)
#define BIT_AP_AHB_AWQOS_THRESHHOLD_MERGE(x)        (((x) & 0xF) << 8)
#define BIT_AP_AHB_ARQOS_THRESHHOLD_DISP(x)         (((x) & 0xF) << 4)
#define BIT_AP_AHB_AWQOS_THRESHHOLD_DISP(x)         (((x) & 0xF))

/* REG_AP_AHB_ASYNC_BRIDGE_IDLE_OVERFLOW */

#define BIT_AP_AHB_AXI_DETECTOR_OVERFLOW_AP         BIT(5)
#define BIT_AP_AHB_AXI_DETECTOR_OVERFLOW_DISP       BIT(4)
#define BIT_AP_AHB_BRIDGE_TRANS_IDLE_AP             BIT(2)
#define BIT_AP_AHB_BRIDGE_TRANS_IDLE_DISP           BIT(1)

/* REG_AP_AHB_ASYNC_BRIDGE_DEBUG_SIGNAL_W_VDSP */


/* REG_AP_AHB_ASYNC_BRIDGE_DEBUG_SIGNAL_W_DISP */

#define BIT_AP_AHB_DISP_BRIDGE_DEBUG_SIGNAL_W(x)    (((x) & 0xFFFFFFFF))

/* REG_AP_AHB_ASYNC_BRIDGE_DEBUG_SIGNAL_W_AP */

#define BIT_AP_AHB_AP_BRIDGE_DEBUG_SIGNAL_W(x)      (((x) & 0xFFFFFFFF))

/* REG_AP_AHB_SYS_RST */

#define BIT_AP_AHB_SYS_SOFT_RST_REQ_GSP             BIT(2)
#define BIT_AP_AHB_SYS_SOFT_RST_REQ_DISP            BIT(1)
#define BIT_AP_AHB_SYS_SOFT_RST_REQ_VSP             BIT(0)

/* REG_AP_AHB_CACHE_EMMC_SDIO */

#define BIT_AP_AHB_ARCACHE_SDIO2(x)                 (((x) & 0xF) << 28)
#define BIT_AP_AHB_AWCACHE_SDIO2(x)                 (((x) & 0xF) << 24)
#define BIT_AP_AHB_ARCACHE_SDIO1(x)                 (((x) & 0xF) << 20)
#define BIT_AP_AHB_AWCACHE_SDIO1(x)                 (((x) & 0xF) << 16)
#define BIT_AP_AHB_ARCACHE_SDIO0(x)                 (((x) & 0xF) << 12)
#define BIT_AP_AHB_AWCACHE_SDIO0(x)                 (((x) & 0xF) << 8)
#define BIT_AP_AHB_ARCACHE_EMMC(x)                  (((x) & 0xF) << 4)
#define BIT_AP_AHB_AWCACHE_EMMC(x)                  (((x) & 0xF))

/* REG_AP_AHB_AP_QOS_CFG */

#define BIT_AP_AHB_DISP_FRAME_LINE_SEL_FOR_DDR_DFS  BIT(9)
#define BIT_AP_AHB_DISP_FRAME_LINE_SEL_FOR_DVFS     BIT(8)

/* REG_AP_AHB_DSI_PHY */

#define BIT_AP_AHB_MIPI_DSI_RESERVED(x)             (((x) & 0xFFFF) << 9)
#define BIT_AP_AHB_MIPI_DSI_TX_RCTL(x)              (((x) & 0xF) << 5)
#define BIT_AP_AHB_MIPI_DSI_TRIMBG(x)               (((x) & 0xF) << 1)
#define BIT_AP_AHB_MIPI_DSI_IF_SEL                  BIT(0)

/* REG_AP_AHB_CHIP_ID */

#define BIT_AP_AHB_CHIP_ID(x)                       (((x) & 0xFFFFFFFF))


#endif /* AP_AHB_H */


