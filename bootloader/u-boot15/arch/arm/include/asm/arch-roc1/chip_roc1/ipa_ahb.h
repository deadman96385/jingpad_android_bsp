/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-18 10:55:02
 *
 */


#ifndef IPA_AHB_H
#define IPA_AHB_H

#define CTL_BASE_IPA_AHB 0x21040000


#define REG_IPA_AHB_IPA_RST                       ( CTL_BASE_IPA_AHB + 0x0000 )
#define REG_IPA_AHB_IPA_EB                        ( CTL_BASE_IPA_AHB + 0x0004 )
#define REG_IPA_AHB_PCIE3_CTL0                    ( CTL_BASE_IPA_AHB + 0x0008 )
#define REG_IPA_AHB_PCIE2_CTL0                    ( CTL_BASE_IPA_AHB + 0x000C )
#define REG_IPA_AHB_USB_CTL0                      ( CTL_BASE_IPA_AHB + 0x0010 )
#define REG_IPA_AHB_M0_LPC                        ( CTL_BASE_IPA_AHB + 0x0014 )
#define REG_IPA_AHB_M1_LPC                        ( CTL_BASE_IPA_AHB + 0x0018 )
#define REG_IPA_AHB_M2_LPC                        ( CTL_BASE_IPA_AHB + 0x001C )
#define REG_IPA_AHB_M3_LPC                        ( CTL_BASE_IPA_AHB + 0x0020 )
#define REG_IPA_AHB_M4_LPC                        ( CTL_BASE_IPA_AHB + 0x0024 )
#define REG_IPA_AHB_M5_LPC                        ( CTL_BASE_IPA_AHB + 0x0028 )
#define REG_IPA_AHB_M6_LPC                        ( CTL_BASE_IPA_AHB + 0x002C )
#define REG_IPA_AHB_M7_LPC                        ( CTL_BASE_IPA_AHB + 0x0030 )
#define REG_IPA_AHB_MAIN_MTX_LPC                  ( CTL_BASE_IPA_AHB + 0x0034 )
#define REG_IPA_AHB_S0_LPC                        ( CTL_BASE_IPA_AHB + 0x0038 )
#define REG_IPA_AHB_S1_LPC                        ( CTL_BASE_IPA_AHB + 0x003C )
#define REG_IPA_AHB_S2_LPC                        ( CTL_BASE_IPA_AHB + 0x0040 )
#define REG_IPA_AHB_S3_LPC                        ( CTL_BASE_IPA_AHB + 0x0044 )
#define REG_IPA_AHB_S4_LPC                        ( CTL_BASE_IPA_AHB + 0x0048 )
#define REG_IPA_AHB_S5_LPC                        ( CTL_BASE_IPA_AHB + 0x004C )
#define REG_IPA_AHB_S6_LPC                        ( CTL_BASE_IPA_AHB + 0x0050 )
#define REG_IPA_AHB_S7_LPC                        ( CTL_BASE_IPA_AHB + 0x0054 )
#define REG_IPA_AHB_S8_LPC                        ( CTL_BASE_IPA_AHB + 0x0058 )
#define REG_IPA_AHB_ASYNC_BRG_G2_LPC              ( CTL_BASE_IPA_AHB + 0x005C )
#define REG_IPA_AHB_ASYNC_BRG_G3_LPC              ( CTL_BASE_IPA_AHB + 0x0060 )
#define REG_IPA_AHB_MTX_QOS_0                     ( CTL_BASE_IPA_AHB + 0x0064 )
#define REG_IPA_AHB_MTX_QOS_1                     ( CTL_BASE_IPA_AHB + 0x0068 )
#define REG_IPA_AHB_MATRIX_LPC_CTRL               ( CTL_BASE_IPA_AHB + 0x006C )
#define REG_IPA_AHB_IPA_MTX_FREQ_ALLOW            ( CTL_BASE_IPA_AHB + 0x0070 )
#define REG_IPA_AHB_IPA_MTX_FREQ_LSLP_ALLOW       ( CTL_BASE_IPA_AHB + 0x0074 )
#define REG_IPA_AHB_MISC_CFG                      ( CTL_BASE_IPA_AHB + 0x0078 )
#define REG_IPA_AHB_IPA_SYS_STATUS                ( CTL_BASE_IPA_AHB + 0x007C )
#define REG_IPA_AHB_AP2IPA_BRIDGE_DEBUG_SIGNAL_R  ( CTL_BASE_IPA_AHB + 0x0080 )
#define REG_IPA_AHB_GEN2_BRIDGE_DEBUG_SIGNAL_W    ( CTL_BASE_IPA_AHB + 0x0084 )
#define REG_IPA_AHB_GEN3_BRIDGE_DEBUG_SIGNAL_W    ( CTL_BASE_IPA_AHB + 0x0088 )
#define REG_IPA_AHB_USB3_DEBUG_0                  ( CTL_BASE_IPA_AHB + 0x008C )
#define REG_IPA_AHB_USB3_DEBUG_1                  ( CTL_BASE_IPA_AHB + 0x0090 )
#define REG_IPA_AHB_USB3_DEBUG_2                  ( CTL_BASE_IPA_AHB + 0x0094 )
#define REG_IPA_AHB_PCIE2_DEBUG                   ( CTL_BASE_IPA_AHB + 0x0098 )
#define REG_IPA_AHB_PCIE3_DEBUG                   ( CTL_BASE_IPA_AHB + 0x009C )
#define REG_IPA_AHB_CM4_SYS_SOFT_RST              ( CTL_BASE_IPA_AHB + 0x0100 )
#define REG_IPA_AHB_CM4_CORE_CFG1                 ( CTL_BASE_IPA_AHB + 0x0104 )
#define REG_IPA_AHB_CM4_CORE_SYSTICK_CFG          ( CTL_BASE_IPA_AHB + 0x0108 )
#define REG_IPA_AHB_CM4_CORE_AUXFAULT_CFG         ( CTL_BASE_IPA_AHB + 0x010C )
#define REG_IPA_AHB_CM4_MAIN_STATOUT              ( CTL_BASE_IPA_AHB + 0x0110 )
#define REG_IPA_AHB_CM4_INT_STAT                  ( CTL_BASE_IPA_AHB + 0x0114 )
#define REG_IPA_AHB_CM4_WDG_RST_FLAG              ( CTL_BASE_IPA_AHB + 0x0118 )
#define REG_IPA_AHB_CM4_ICACHE_CTRL_REG           ( CTL_BASE_IPA_AHB + 0x011C )
#define REG_IPA_AHB_CM4_DCACHE_CTRL_REG           ( CTL_BASE_IPA_AHB + 0x0120 )
#define REG_IPA_AHB_CM4_IPORT_REMAP_CTRL_REG      ( CTL_BASE_IPA_AHB + 0x0124 )
#define REG_IPA_AHB_CM4_DPORT_REMAP_CTRL_REG      ( CTL_BASE_IPA_AHB + 0x0128 )
#define REG_IPA_AHB_CM4_SPORT_REMAP_CTRL_REG      ( CTL_BASE_IPA_AHB + 0x012C )
#define REG_IPA_AHB_INT_TO_AP_STATUS_REG          ( CTL_BASE_IPA_AHB + 0x0130 )
#define REG_IPA_AHB_INT_TO_CM4_STATUS_REG         ( CTL_BASE_IPA_AHB + 0x0134 )
#define REG_IPA_AHB_INT_TO_AP_EN_REG              ( CTL_BASE_IPA_AHB + 0x0138 )
#define REG_IPA_AHB_INT_TO_CM4_EN_REG             ( CTL_BASE_IPA_AHB + 0x013C )

/* REG_IPA_AHB_IPA_RST */

#define BIT_IPA_AHB_WDG_SOFT_RST                         BIT(13)
#define BIT_IPA_AHB_TIMER_SOFT_RST                       BIT(12)
#define BIT_IPA_AHB_UART_SOFT_RST                        BIT(11)
#define BIT_IPA_AHB_INTC_SOFT_RST                        BIT(10)
#define BIT_IPA_AHB_BUSMON_PERF_IPA_TOP_SOFT_RST         BIT(9)
#define BIT_IPA_AHB_BUSMON_PERF_PAM_IPA_SOFT_RST         BIT(8)
#define BIT_IPA_AHB_BUSMON_PERF_PAM_U3_SOFT_RST          BIT(7)
#define BIT_IPA_AHB_PCIE2_SOFT_RST                       BIT(6)
#define BIT_IPA_AHB_PCIE3_SOFT_RST                       BIT(5)
#define BIT_IPA_AHB_IPA_SOFT_RST                         BIT(4)
#define BIT_IPA_AHB_PAM_WIFI_SOFT_RST                    BIT(3)
#define BIT_IPA_AHB_PAM_IPA_SOFT_RST                     BIT(2)
#define BIT_IPA_AHB_PAM_U3_SOFT_RST                      BIT(1)
#define BIT_IPA_AHB_USB_SOFT_RST                         BIT(0)

/* REG_IPA_AHB_IPA_EB */

#define BIT_IPA_AHB_CM4_EB                               BIT(17)
#define BIT_IPA_AHB_WDG_EB                               BIT(16)
#define BIT_IPA_AHB_TIMER_EB                             BIT(15)
#define BIT_IPA_AHB_UART_EB                              BIT(14)
#define BIT_IPA_AHB_BUSMON_DEBUG_EB                      BIT(13)
#define BIT_IPA_AHB_INTC_EB                              BIT(12)
#define BIT_IPA_AHB_BUSMON_PERF_IPA_TOP_EB               BIT(11)
#define BIT_IPA_AHB_BUSMON_PERF_PAM_IPA_EB               BIT(10)
#define BIT_IPA_AHB_BUSMON_PERF_PAM_U3_EB                BIT(9)
#define BIT_IPA_AHB_PCIE2_EB                             BIT(8)
#define BIT_IPA_AHB_PCIE3_EB                             BIT(7)
#define BIT_IPA_AHB_PAM_WIFI_EB                          BIT(6)
#define BIT_IPA_AHB_PAM_IPA_EB                           BIT(5)
#define BIT_IPA_AHB_PAM_USB_EB                           BIT(4)
#define BIT_IPA_AHB_IPA_EB                               BIT(3)
#define BIT_IPA_AHB_USB_REF_EB                           BIT(2)
#define BIT_IPA_AHB_USB_SUSPEND_EB                       BIT(1)
#define BIT_IPA_AHB_USB_EB                               BIT(0)

/* REG_IPA_AHB_PCIE3_CTL0 */

#define BIT_IPA_AHB_G3_IPA_CTL_PCIE_REG(x)               (((x) & 0xFF) << 8)
#define BIT_IPA_AHB_MSI2IPA_SEL                          BIT(7)
#define BIT_IPA_AHB_G3_APP_RAS_DES_SD_HOLD_LTSSM         BIT(6)
#define BIT_IPA_AHB_G3_APP_RAS_DES_TBA_CTRL(x)           (((x) & 0x3) << 4)
#define BIT_IPA_AHB_G3_APP_L1_PWR_OFF_EN                 BIT(3)
#define BIT_IPA_AHB_G3_APP_XFER_PENDING                  BIT(2)
#define BIT_IPA_AHB_G3_DBG_TABLE                         BIT(1)
#define BIT_IPA_AHB_G3_DBG_PBA                           BIT(0)

/* REG_IPA_AHB_PCIE2_CTL0 */

#define BIT_IPA_AHB_G2_IPA_CTL_PCIE_REG(x)               (((x) & 0xFF) << 8)
#define BIT_IPA_AHB_G2_APP_RAS_DES_SD_HOLD_LTSSM         BIT(6)
#define BIT_IPA_AHB_G2_APP_RAS_DES_TBA_CTRL(x)           (((x) & 0x3) << 4)
#define BIT_IPA_AHB_G2_APP_L1_PWR_OFF_EN                 BIT(3)
#define BIT_IPA_AHB_G2_APP_XFER_PENDING                  BIT(2)
#define BIT_IPA_AHB_G2_DBG_TABLE                         BIT(1)
#define BIT_IPA_AHB_G2_DBG_PBA                           BIT(0)

/* REG_IPA_AHB_USB_CTL0 */

#define BIT_IPA_AHB_UTMISRP_BVALID_REG                   BIT(15)
#define BIT_IPA_AHB_OTG_VBUS_VALID_PHYREG                BIT(14)
#define BIT_IPA_AHB_OTG_VBUS_VALID_PHYREG_SEL            BIT(13)
#define BIT_IPA_AHB_XHC_BME                              BIT(12)
#define BIT_IPA_AHB_BUS_FILTER_BYPASS(x)                 (((x) & 0xF) << 8)
#define BIT_IPA_AHB_PME_EN                               BIT(7)
#define BIT_IPA_AHB_USB_FLADJ_30MHZ_REG(x)               (((x) & 0x3F) << 1)
#define BIT_IPA_AHB_USB_HOST_PORT_POWER_CONTROL_PRESENT  BIT(0)

/* REG_IPA_AHB_M0_LPC */

#define BIT_IPA_AHB_MAIN_M0_PU_NUM(x)                    (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_MAIN_M0_LP_EB                        BIT(16)
#define BIT_IPA_AHB_MAIN_M0_LP_NUM(x)                    (((x) & 0xFFFF))

/* REG_IPA_AHB_M1_LPC */

#define BIT_IPA_AHB_MAIN_M1_PU_NUM(x)                    (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_MAIN_M1_LP_EB                        BIT(16)
#define BIT_IPA_AHB_MAIN_M1_LP_NUM(x)                    (((x) & 0xFFFF))

/* REG_IPA_AHB_M2_LPC */

#define BIT_IPA_AHB_MAIN_M2_PU_NUM(x)                    (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_MAIN_M2_LP_EB                        BIT(16)
#define BIT_IPA_AHB_MAIN_M2_LP_NUM(x)                    (((x) & 0xFFFF))

/* REG_IPA_AHB_M3_LPC */

#define BIT_IPA_AHB_MAIN_M3_PU_NUM(x)                    (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_MAIN_M3_LP_EB                        BIT(16)
#define BIT_IPA_AHB_MAIN_M3_LP_NUM(x)                    (((x) & 0xFFFF))

/* REG_IPA_AHB_M4_LPC */

#define BIT_IPA_AHB_MAIN_M4_PU_NUM(x)                    (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_MAIN_M4_LP_EB                        BIT(16)
#define BIT_IPA_AHB_MAIN_M4_LP_NUM(x)                    (((x) & 0xFFFF))

/* REG_IPA_AHB_M5_LPC */

#define BIT_IPA_AHB_MAIN_M5_PU_NUM(x)                    (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_MAIN_M5_LP_EB                        BIT(16)
#define BIT_IPA_AHB_MAIN_M5_LP_NUM(x)                    (((x) & 0xFFFF))

/* REG_IPA_AHB_M6_LPC */

#define BIT_IPA_AHB_MAIN_M6_PU_NUM(x)                    (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_MAIN_M6_LP_EB                        BIT(16)
#define BIT_IPA_AHB_MAIN_M6_LP_NUM(x)                    (((x) & 0xFFFF))

/* REG_IPA_AHB_M7_LPC */

#define BIT_IPA_AHB_MAIN_M7_PU_NUM(x)                    (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_MAIN_M7_LP_EB                        BIT(16)
#define BIT_IPA_AHB_MAIN_M7_LP_NUM(x)                    (((x) & 0xFFFF))

/* REG_IPA_AHB_MAIN_MTX_LPC */

#define BIT_IPA_AHB_MAIN_PU_NUM(x)                       (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_CGM_MATRIX_AUTO_GATE_EN              BIT(17)
#define BIT_IPA_AHB_MAIN_LP_EB                           BIT(16)
#define BIT_IPA_AHB_MAIN_LP_NUM(x)                       (((x) & 0xFFFF))

/* REG_IPA_AHB_S0_LPC */

#define BIT_IPA_AHB_MAIN_S0_PU_NUM(x)                    (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_CGM_MTX_S0_AUTO_GATE_EN              BIT(17)
#define BIT_IPA_AHB_MAIN_S0_LP_EB                        BIT(16)
#define BIT_IPA_AHB_MAIN_S0_LP_NUM(x)                    (((x) & 0xFFFF))

/* REG_IPA_AHB_S1_LPC */

#define BIT_IPA_AHB_MAIN_S1_PU_NUM(x)                    (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_CGM_MTX_S1_AUTO_GATE_EN              BIT(17)
#define BIT_IPA_AHB_MAIN_S1_LP_EB                        BIT(16)
#define BIT_IPA_AHB_MAIN_S1_LP_NUM(x)                    (((x) & 0xFFFF))

/* REG_IPA_AHB_S2_LPC */

#define BIT_IPA_AHB_MAIN_S2_PU_NUM(x)                    (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_CGM_MTX_S2_AUTO_GATE_EN              BIT(17)
#define BIT_IPA_AHB_MAIN_S2_LP_EB                        BIT(16)
#define BIT_IPA_AHB_MAIN_S2_LP_NUM(x)                    (((x) & 0xFFFF))

/* REG_IPA_AHB_S3_LPC */

#define BIT_IPA_AHB_MAIN_S3_PU_NUM(x)                    (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_CGM_MTX_S3_AUTO_GATE_EN              BIT(17)
#define BIT_IPA_AHB_MAIN_S3_LP_EB                        BIT(16)
#define BIT_IPA_AHB_MAIN_S3_LP_NUM(x)                    (((x) & 0xFFFF))

/* REG_IPA_AHB_S4_LPC */

#define BIT_IPA_AHB_MAIN_S4_PU_NUM(x)                    (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_CGM_MTX_S4_AUTO_GATE_EN              BIT(17)
#define BIT_IPA_AHB_MAIN_S4_LP_EB                        BIT(16)
#define BIT_IPA_AHB_MAIN_S4_LP_NUM(x)                    (((x) & 0xFFFF))

/* REG_IPA_AHB_S5_LPC */

#define BIT_IPA_AHB_MAIN_S5_PU_NUM(x)                    (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_CGM_MTX_S5_AUTO_GATE_EN              BIT(17)
#define BIT_IPA_AHB_MAIN_S5_LP_EB                        BIT(16)
#define BIT_IPA_AHB_MAIN_S5_LP_NUM(x)                    (((x) & 0xFFFF))

/* REG_IPA_AHB_S6_LPC */

#define BIT_IPA_AHB_MAIN_S6_PU_NUM(x)                    (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_CGM_MTX_S6_AUTO_GATE_EN              BIT(17)
#define BIT_IPA_AHB_MAIN_S6_LP_EB                        BIT(16)
#define BIT_IPA_AHB_MAIN_S6_LP_NUM(x)                    (((x) & 0xFFFF))

/* REG_IPA_AHB_S7_LPC */

#define BIT_IPA_AHB_MAIN_S7_PU_NUM(x)                    (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_CGM_MTX_S7_AUTO_GATE_EN              BIT(17)
#define BIT_IPA_AHB_MAIN_S7_LP_EB                        BIT(16)
#define BIT_IPA_AHB_MAIN_S7_LP_NUM(x)                    (((x) & 0xFFFF))

/* REG_IPA_AHB_S8_LPC */

#define BIT_IPA_AHB_MAIN_S8_PU_NUM(x)                    (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_CGM_MTX_S8_AUTO_GATE_EN              BIT(17)
#define BIT_IPA_AHB_MAIN_S8_LP_EB                        BIT(16)
#define BIT_IPA_AHB_MAIN_S8_LP_NUM(x)                    (((x) & 0xFFFF))

/* REG_IPA_AHB_ASYNC_BRG_G2_LPC */

#define BIT_IPA_AHB_ASYNC_BRG_G2_PU_NUM(x)               (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_ASYNC_BRG_G2_LP_EB                   BIT(16)
#define BIT_IPA_AHB_ASYNC_BRG_G2_LP_NUM(x)               (((x) & 0xFFFF))

/* REG_IPA_AHB_ASYNC_BRG_G3_LPC */

#define BIT_IPA_AHB_ASYNC_BRG_G3_PU_NUM(x)               (((x) & 0xFF) << 24)
#define BIT_IPA_AHB_ASYNC_BRG_G3_LP_EB                   BIT(16)
#define BIT_IPA_AHB_ASYNC_BRG_G3_LP_NUM(x)               (((x) & 0xFFFF))

/* REG_IPA_AHB_MTX_QOS_0 */

#define BIT_IPA_AHB_AWQOS_M3(x)                          (((x) & 0xF) << 28)
#define BIT_IPA_AHB_ARQOS_M3(x)                          (((x) & 0xF) << 24)
#define BIT_IPA_AHB_AWQOS_M2(x)                          (((x) & 0xF) << 20)
#define BIT_IPA_AHB_ARQOS_M2(x)                          (((x) & 0xF) << 16)
#define BIT_IPA_AHB_AWQOS_M1(x)                          (((x) & 0xF) << 12)
#define BIT_IPA_AHB_ARQOS_M1(x)                          (((x) & 0xF) << 8)
#define BIT_IPA_AHB_AWQOS_M0(x)                          (((x) & 0xF) << 4)
#define BIT_IPA_AHB_ARQOS_M0(x)                          (((x) & 0xF))

/* REG_IPA_AHB_MTX_QOS_1 */

#define BIT_IPA_AHB_AWQOS_M7(x)                          (((x) & 0xF) << 28)
#define BIT_IPA_AHB_ARQOS_M7(x)                          (((x) & 0xF) << 24)
#define BIT_IPA_AHB_AWQOS_M6(x)                          (((x) & 0xF) << 20)
#define BIT_IPA_AHB_ARQOS_M6(x)                          (((x) & 0xF) << 16)
#define BIT_IPA_AHB_AWQOS_M5(x)                          (((x) & 0xF) << 12)
#define BIT_IPA_AHB_ARQOS_M5(x)                          (((x) & 0xF) << 8)
#define BIT_IPA_AHB_AWQOS_M4(x)                          (((x) & 0xF) << 4)
#define BIT_IPA_AHB_ARQOS_M4(x)                          (((x) & 0xF))

/* REG_IPA_AHB_MATRIX_LPC_CTRL */

#define BIT_IPA_AHB_APB_AUTO_DPSLP_EN                    BIT(26)
#define BIT_IPA_AHB_CM4_AUTO_DPSLP_EN                    BIT(25)
#define BIT_IPA_AHB_CM4_AUTO_LTSLP_EN                    BIT(24)
#define BIT_IPA_AHB_M8910_LPC_BYPASS                     BIT(23)
#define BIT_IPA_AHB_PCIE3_AUTO_DPSLP_EN                  BIT(22)
#define BIT_IPA_AHB_PCIE2_AUTO_DPSLP_EN                  BIT(21)
#define BIT_IPA_AHB_PCIE3_AUTO_LTSLP_EN                  BIT(20)
#define BIT_IPA_AHB_PCIE2_AUTO_LTSLP_EN                  BIT(19)
#define BIT_IPA_AHB_IPA_APB_FRC_OFF                      BIT(18)
#define BIT_IPA_AHB_IPA_APB_FRC_ON                       BIT(17)
#define BIT_IPA_AHB_IPA_MTX_FRC_OFF                      BIT(16)
#define BIT_IPA_AHB_IPA_MTX_FRC_ON                       BIT(15)
#define BIT_IPA_AHB_IPA_MTX_FREQ_LSLP_DFS_SEL(x)         (((x) & 0x3) << 13)
#define BIT_IPA_AHB_IPA_MTX_FREQ_LSLP_DFS_EN             BIT(12)
#define BIT_IPA_AHB_IPA_MTX_FREQ_LSLP_DFS_MODE           BIT(11)
#define BIT_IPA_AHB_IPA_MTX_FREQ_DFS_MASTER_HW_EN(x)     (((x) & 0x1FF) << 2)
#define BIT_IPA_AHB_IPA_MTX_FREQ_DFS_MODE                BIT(1)
#define BIT_IPA_AHB_AXI_LP_CTRL_DISABLE                  BIT(0)

/* REG_IPA_AHB_IPA_MTX_FREQ_ALLOW */

#define BIT_IPA_AHB_IMTX_M7_AXI_FREQ_ALLOW(x)            (((x) & 0xF) << 28)
#define BIT_IPA_AHB_IMTX_M6_AXI_FREQ_ALLOW(x)            (((x) & 0xF) << 24)
#define BIT_IPA_AHB_IMTX_M5_AXI_FREQ_ALLOW(x)            (((x) & 0xF) << 20)
#define BIT_IPA_AHB_IMTX_M4_AXI_FREQ_ALLOW(x)            (((x) & 0xF) << 16)
#define BIT_IPA_AHB_IMTX_M3_AXI_FREQ_ALLOW(x)            (((x) & 0xF) << 12)
#define BIT_IPA_AHB_IMTX_M2_AXI_FREQ_ALLOW(x)            (((x) & 0xF) << 8)
#define BIT_IPA_AHB_IMTX_M1_AXI_FREQ_ALLOW(x)            (((x) & 0xF) << 4)
#define BIT_IPA_AHB_IMTX_M0_AXI_FREQ_ALLOW(x)            (((x) & 0xF))

/* REG_IPA_AHB_IPA_MTX_FREQ_LSLP_ALLOW */

#define BIT_IPA_AHB_IMTX_M7_AXI_FREQ_LSLP_ALLOW(x)       (((x) & 0xF) << 28)
#define BIT_IPA_AHB_IMTX_M6_AXI_FREQ_LSLP_ALLOW(x)       (((x) & 0xF) << 24)
#define BIT_IPA_AHB_IMTX_M5_AXI_FREQ_LSLP_ALLOW(x)       (((x) & 0xF) << 20)
#define BIT_IPA_AHB_IMTX_M4_AXI_FREQ_LSLP_ALLOW(x)       (((x) & 0xF) << 16)
#define BIT_IPA_AHB_IMTX_M3_AXI_FREQ_LSLP_ALLOW(x)       (((x) & 0xF) << 12)
#define BIT_IPA_AHB_IMTX_M2_AXI_FREQ_LSLP_ALLOW(x)       (((x) & 0xF) << 8)
#define BIT_IPA_AHB_IMTX_M1_AXI_FREQ_LSLP_ALLOW(x)       (((x) & 0xF) << 4)
#define BIT_IPA_AHB_IMTX_M0_AXI_FREQ_LSLP_ALLOW(x)       (((x) & 0xF))

/* REG_IPA_AHB_MISC_CFG */

#define BIT_IPA_AHB_IPA_BUS_MONITOR_EN                   BIT(27)
#define BIT_IPA_AHB_USB_INT_CM4_EN                       BIT(26)
#define BIT_IPA_AHB_CM4_FCLK_ON                          BIT(25)
#define BIT_IPA_AHB_BUSMON_DEBUG_SEL                     BIT(24)
#define BIT_IPA_AHB_IMTX_M8_AXI_FREQ_LSLP_ALLOW(x)       (((x) & 0xF) << 20)
#define BIT_IPA_AHB_IMTX_M8_AXI_FREQ_ALLOW(x)            (((x) & 0xF) << 16)
#define BIT_IPA_AHB_AWQOS_THRESHOLD_IPA2(x)              (((x) & 0xF) << 12)
#define BIT_IPA_AHB_ARQOS_THRESHOLD_IPA2(x)              (((x) & 0xF) << 8)
#define BIT_IPA_AHB_AWQOS_THRESHOLD_IPA1(x)              (((x) & 0xF) << 4)
#define BIT_IPA_AHB_ARQOS_THRESHOLD_IPA1(x)              (((x) & 0xF))

/* REG_IPA_AHB_IPA_SYS_STATUS */

#define BIT_IPA_AHB_GEN3_BRIDGE_TRANS_IDLE               BIT(3)
#define BIT_IPA_AHB_GEN3_AXI_DETECTOR_OVERFLOW           BIT(2)
#define BIT_IPA_AHB_GEN2_BRIDGE_TRANS_IDLE               BIT(1)
#define BIT_IPA_AHB_GEN2_AXI_DETECTOR_OVERFLOW           BIT(0)

/* REG_IPA_AHB_AP2IPA_BRIDGE_DEBUG_SIGNAL_R */

#define BIT_IPA_AHB_AP2IPA_BRIDGE_DEBUG_SIGNAL_R(x)      (((x) & 0xFFFFFFFF))

/* REG_IPA_AHB_GEN2_BRIDGE_DEBUG_SIGNAL_W */

#define BIT_IPA_AHB_GEN2_BRIDGE_DEBUG_SIGNAL_W(x)        (((x) & 0xFFFFFFFF))

/* REG_IPA_AHB_GEN3_BRIDGE_DEBUG_SIGNAL_W */

#define BIT_IPA_AHB_GEN3_BRIDGE_DEBUG_SIGNAL_W(x)        (((x) & 0xFFFFFFFF))

/* REG_IPA_AHB_USB3_DEBUG_0 */

#define BIT_IPA_AHB_USB3_DEBUG_0_31(x)                   (((x) & 0xFFFFFFFF))

/* REG_IPA_AHB_USB3_DEBUG_1 */

#define BIT_IPA_AHB_USB3_DEBUG_32_63(x)                  (((x) & 0xFFFFFFFF))

/* REG_IPA_AHB_USB3_DEBUG_2 */

#define BIT_IPA_AHB_HOST_CURRENT_BELT(x)                 (((x) & 0xFFF) << 7)
#define BIT_IPA_AHB_USB3_CLK_GATE_CTRL(x)                (((x) & 0x7) << 4)
#define BIT_IPA_AHB_USB3_HOST_SYSTEM_ERR                 BIT(3)
#define BIT_IPA_AHB_USB3_DEBUG_64_66(x)                  (((x) & 0x7))

/* REG_IPA_AHB_PCIE2_DEBUG */

#define BIT_IPA_AHB_G2_CFG_INT_DISABLE                   BIT(24)
#define BIT_IPA_AHB_G2_CFG_PCIE_CAP_INT_MSG_NUM(x)       (((x) & 0x1F) << 19)
#define BIT_IPA_AHB_G2_CFG_AER_INT_MSG_NUM(x)            (((x) & 0x1F) << 14)
#define BIT_IPA_AHB_G2_CFG_PWR_IND(x)                    (((x) & 0x3) << 12)
#define BIT_IPA_AHB_G2_CFG_ATTEN_IND(x)                  (((x) & 0x3) << 10)
#define BIT_IPA_AHB_G2_CFG_PWR_CTRLER_CTRL               BIT(9)
#define BIT_IPA_AHB_G2_CFG_BUS_MASTER_EN                 BIT(8)
#define BIT_IPA_AHB_G2_PCIE_DBG_SIGNAL(x)                (((x) & 0xFF))

/* REG_IPA_AHB_PCIE3_DEBUG */

#define BIT_IPA_AHB_G3_CFG_INT_DISABLE                   BIT(24)
#define BIT_IPA_AHB_G3_CFG_PCIE_CAP_INT_MSG_NUM(x)       (((x) & 0x1F) << 19)
#define BIT_IPA_AHB_G3_CFG_AER_INT_MSG_NUM(x)            (((x) & 0x1F) << 14)
#define BIT_IPA_AHB_G3_CFG_PWR_IND(x)                    (((x) & 0x3) << 12)
#define BIT_IPA_AHB_G3_CFG_ATTEN_IND(x)                  (((x) & 0x3) << 10)
#define BIT_IPA_AHB_G3_CFG_PWR_CTRLER_CTRL               BIT(9)
#define BIT_IPA_AHB_G3_CFG_BUS_MASTER_EN                 BIT(8)
#define BIT_IPA_AHB_G3_PCIE_DBG_SIGNAL(x)                (((x) & 0xFF))

/* REG_IPA_AHB_CM4_SYS_SOFT_RST */

#define BIT_IPA_AHB_CM4_SYS_SOFT_RST                     BIT(1)
#define BIT_IPA_AHB_CM4_CORE_SOFT_RST                    BIT(0)

/* REG_IPA_AHB_CM4_CORE_CFG1 */

#define BIT_IPA_AHB_CM4_EXRESPD_STAT                     BIT(11)
#define BIT_IPA_AHB_CM4_SOFT_DEBUG_EN                    BIT(10)
#define BIT_IPA_AHB_CM4_SOFT_FPUDIS                      BIT(9)
#define BIT_IPA_AHB_CM4_SOFT_MPUDIS                      BIT(8)
#define BIT_IPA_AHB_CM4_SOFT_TSCLK_CHG                   BIT(7)
#define BIT_IPA_AHB_CM4_SOFT_FIXMASTERTYPE               BIT(6)
#define BIT_IPA_AHB_CM4_SOFT_DBGRESTART                  BIT(5)
#define BIT_IPA_AHB_CM4_SOFT_EDBGRQ                      BIT(4)
#define BIT_IPA_AHB_CM4_SOFT_SLEEPHOLDREQ_N              BIT(3)
#define BIT_IPA_AHB_CM4_SOFT_EXRESPS                     BIT(2)

/* REG_IPA_AHB_CM4_CORE_SYSTICK_CFG */

#define BIT_IPA_AHB_CM4_SOFT_STCALIB(x)                  (((x) & 0x3FFFFFF) << 1)
#define BIT_IPA_AHB_CM4_SOFT_STCLK                       BIT(0)

/* REG_IPA_AHB_CM4_CORE_AUXFAULT_CFG */

#define BIT_IPA_AHB_CM4_SOFT_AUXFAULT(x)                 (((x) & 0xFFFFFFFF))

/* REG_IPA_AHB_CM4_MAIN_STATOUT */

#define BIT_IPA_AHB_CM4_GATEHCLK_STAT                    BIT(30)
#define BIT_IPA_AHB_CM4_WAKEUP_STAT                      BIT(29)
#define BIT_IPA_AHB_CM4_SLEEPHOLDACKN_STAT               BIT(28)
#define BIT_IPA_AHB_CM4_SLEEPINGDEEP_STAT                BIT(27)
#define BIT_IPA_AHB_CM4_SLEEPING_STAT                    BIT(26)
#define BIT_IPA_AHB_CM4_LOCKUP_STAT                      BIT(25)
#define BIT_IPA_AHB_CM4_DBGRESTARTED_STAT                BIT(24)
#define BIT_IPA_AHB_CM4_HALTED_STAT                      BIT(23)
#define BIT_IPA_AHB_CM4_BRCHSTAT_STAT(x)                 (((x) & 0xF) << 19)
#define BIT_IPA_AHB_CM4_EXREQS_STAT                      BIT(18)
#define BIT_IPA_AHB_CM4_MEMATTRS_STAT(x)                 (((x) & 0x3) << 16)
#define BIT_IPA_AHB_CM4_HMASTLOCKS_STAT                  BIT(15)
#define BIT_IPA_AHB_CM4_HMASTERS_STAT(x)                 (((x) & 0x3) << 13)
#define BIT_IPA_AHB_CM4_HWRITED_STAT                     BIT(12)
#define BIT_IPA_AHB_CM4_EXREQD_STAT                      BIT(11)
#define BIT_IPA_AHB_CM4_MEMATTRD_STAT(x)                 (((x) & 0x3) << 9)
#define BIT_IPA_AHB_CM4_HMASTERD_STAT(x)                 (((x) & 0x3) << 7)
#define BIT_IPA_AHB_CM4_MEMATTRI_STAT(x)                 (((x) & 0x3) << 5)
#define BIT_IPA_AHB_CM4_SWV_STAT                         BIT(4)
#define BIT_IPA_AHB_CM4_WICENACK_STAT                    BIT(1)
#define BIT_IPA_AHB_CM4_CDBGPWRUPREQ_STAT                BIT(0)

/* REG_IPA_AHB_CM4_INT_STAT */

#define BIT_IPA_AHB_CM4_CURRPRI_STAT(x)                  (((x) & 0xFF))

/* REG_IPA_AHB_CM4_WDG_RST_FLAG */

#define BIT_IPA_AHB_RST_CM4_WDG_MUX_SYNC                 BIT(1)
#define BIT_IPA_AHB_CM4_WDG_RST_FLAG                     BIT(0)

/* REG_IPA_AHB_CM4_ICACHE_CTRL_REG */

#define BIT_IPA_AHB_CM4_ICACHE_BIGEND_SEL                BIT(8)
#define BIT_IPA_AHB_CM4_ICACHE_BASE_ADDR(x)              (((x) & 0xF) << 4)
#define BIT_IPA_AHB_CM4_ICACHE_BYPASS                    BIT(0)

/* REG_IPA_AHB_CM4_DCACHE_CTRL_REG */

#define BIT_IPA_AHB_CM4_DCACHE_BIGEND_SEL                BIT(8)
#define BIT_IPA_AHB_CM4_DCACHE_BASE_ADDR(x)              (((x) & 0xF) << 4)
#define BIT_IPA_AHB_CM4_DCACHE_BYPASS                    BIT(0)

/* REG_IPA_AHB_CM4_IPORT_REMAP_CTRL_REG */

#define BIT_IPA_AHB_CM4I_MAP_DDR_ADDR(x)                 (((x) & 0x3FFF) << 16)
#define BIT_IPA_AHB_CM4I_MAP_ORCA_ADDR(x)                (((x) & 0x3FFF))

/* REG_IPA_AHB_CM4_DPORT_REMAP_CTRL_REG */

#define BIT_IPA_AHB_CM4D_MAP_DDR_ADDR(x)                 (((x) & 0x3FFF) << 16)
#define BIT_IPA_AHB_CM4D_MAP_ORCA_ADDR(x)                (((x) & 0x3FFF))

/* REG_IPA_AHB_CM4_SPORT_REMAP_CTRL_REG */

#define BIT_IPA_AHB_CM4S_MAP_DDR_ADDR(x)                 (((x) & 0x3FFF) << 16)
#define BIT_IPA_AHB_CM4S_MAP_ORCA_ADDR(x)                (((x) & 0x3FFF))

/* REG_IPA_AHB_INT_TO_AP_STATUS_REG */

#define BIT_IPA_AHB_IPA_CM4_INT_TO_AP_STATUS(x)          (((x) & 0xFFFFFFFF))

/* REG_IPA_AHB_INT_TO_CM4_STATUS_REG */

#define BIT_IPA_AHB_AP_INT_TO_IPA_CM4_STATUS(x)          (((x) & 0xFFFFFFFF))

/* REG_IPA_AHB_INT_TO_AP_EN_REG */

#define BIT_IPA_AHB_IPA_CM4_INT_TO_AP_EN(x)              (((x) & 0xFFFFFFFF))

/* REG_IPA_AHB_INT_TO_CM4_EN_REG */

#define BIT_IPA_AHB_AP_INT_TO_IPA_CM4_EN(x)              (((x) & 0xFFFFFFFF))


#endif /* IPA_AHB_H */


