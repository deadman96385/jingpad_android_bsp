/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-06 15:47:51
 *
 */

#ifndef AON_CLK_CORE_H
#define AON_CLK_CORE_H

#define CTL_BASE_AON_CLK_CORE 0x32080200

#define REG_AON_CLK_CORE_CGM_AON_APB_CFG                ( CTL_BASE_AON_CLK_CORE + 0x0020 )
#define REG_AON_CLK_CORE_CGM_ADI_CFG                    ( CTL_BASE_AON_CLK_CORE + 0x0024 )
#define REG_AON_CLK_CORE_CGM_AUX0_CFG                   ( CTL_BASE_AON_CLK_CORE + 0x0028 )
#define REG_AON_CLK_CORE_CGM_AUX1_CFG                   ( CTL_BASE_AON_CLK_CORE + 0x002C )
#define REG_AON_CLK_CORE_CGM_AUX2_CFG                   ( CTL_BASE_AON_CLK_CORE + 0x0030 )
#define REG_AON_CLK_CORE_CGM_PROBE_CFG                  ( CTL_BASE_AON_CLK_CORE + 0x0034 )
#define REG_AON_CLK_CORE_CGM_PWM0_CFG                   ( CTL_BASE_AON_CLK_CORE + 0x0038 )
#define REG_AON_CLK_CORE_CGM_PWM1_CFG                   ( CTL_BASE_AON_CLK_CORE + 0x003C )
#define REG_AON_CLK_CORE_CGM_PWM2_CFG                   ( CTL_BASE_AON_CLK_CORE + 0x0040 )
#define REG_AON_CLK_CORE_CGM_PWM3_CFG                   ( CTL_BASE_AON_CLK_CORE + 0x0044 )
#define REG_AON_CLK_CORE_CGM_EFUSE_CFG                  ( CTL_BASE_AON_CLK_CORE + 0x0048 )
#define REG_AON_CLK_CORE_CGM_UART0_CFG                  ( CTL_BASE_AON_CLK_CORE + 0x004C )
#define REG_AON_CLK_CORE_CGM_UART1_CFG                  ( CTL_BASE_AON_CLK_CORE + 0x0050 )
#define REG_AON_CLK_CORE_CGM_32K_OUT_CFG                ( CTL_BASE_AON_CLK_CORE + 0x0054 )
#define REG_AON_CLK_CORE_CGM_3K2_OUT_CFG                ( CTL_BASE_AON_CLK_CORE + 0x0058 )
#define REG_AON_CLK_CORE_CGM_1K_OUT_CFG                 ( CTL_BASE_AON_CLK_CORE + 0x005C )
#define REG_AON_CLK_CORE_CGM_THM0_CFG                   ( CTL_BASE_AON_CLK_CORE + 0x0060 )
#define REG_AON_CLK_CORE_CGM_THM1_CFG                   ( CTL_BASE_AON_CLK_CORE + 0x0064 )
#define REG_AON_CLK_CORE_CGM_THM2_CFG                   ( CTL_BASE_AON_CLK_CORE + 0x0068 )
#define REG_AON_CLK_CORE_CGM_THM3_CFG                   ( CTL_BASE_AON_CLK_CORE + 0x006C )
#define REG_AON_CLK_CORE_CGM_CM4_I3C0_CFG               ( CTL_BASE_AON_CLK_CORE + 0x0070 )
#define REG_AON_CLK_CORE_CGM_CM4_I3C1_CFG               ( CTL_BASE_AON_CLK_CORE + 0x0074 )
#define REG_AON_CLK_CORE_CGM_CM4_SPI_CFG                ( CTL_BASE_AON_CLK_CORE + 0x0078 )
#define REG_AON_CLK_CORE_CGM_AON_I2C_CFG                ( CTL_BASE_AON_CLK_CORE + 0x007C )
#define REG_AON_CLK_CORE_CGM_AON_IIS_CFG                ( CTL_BASE_AON_CLK_CORE + 0x0080 )
#define REG_AON_CLK_CORE_CGM_SCC_CFG                    ( CTL_BASE_AON_CLK_CORE + 0x0084 )
#define REG_AON_CLK_CORE_CGM_APCPU_DAP_CFG              ( CTL_BASE_AON_CLK_CORE + 0x0088 )
#define REG_AON_CLK_CORE_CGM_APCPU_DAP_MTCK_CFG         ( CTL_BASE_AON_CLK_CORE + 0x008C )
#define REG_AON_CLK_CORE_CGM_APCPU_TS_CFG               ( CTL_BASE_AON_CLK_CORE + 0x0090 )
#define REG_AON_CLK_CORE_CGM_DEBUG_TS_CFG               ( CTL_BASE_AON_CLK_CORE + 0x0094 )
#define REG_AON_CLK_CORE_CGM_DSI_TEST_S_CFG             ( CTL_BASE_AON_CLK_CORE + 0x0098 )
#define REG_AON_CLK_CORE_CGM_RFTI_SBI_CFG               ( CTL_BASE_AON_CLK_CORE + 0x009C )
#define REG_AON_CLK_CORE_CGM_RFTI1_XO_CFG               ( CTL_BASE_AON_CLK_CORE + 0x00A0 )
#define REG_AON_CLK_CORE_CGM_RFTI_LTH_CFG               ( CTL_BASE_AON_CLK_CORE + 0x00A4 )
#define REG_AON_CLK_CORE_CGM_RFTI2_XO_CFG               ( CTL_BASE_AON_CLK_CORE + 0x00A8 )
#define REG_AON_CLK_CORE_CGM_RCO100M_REF_CFG            ( CTL_BASE_AON_CLK_CORE + 0x00AC )
#define REG_AON_CLK_CORE_CGM_RCO100M_FDK_CFG            ( CTL_BASE_AON_CLK_CORE + 0x00B0 )
#define REG_AON_CLK_CORE_CGM_DJTAG_TCK_CFG              ( CTL_BASE_AON_CLK_CORE + 0x00B4 )
#define REG_AON_CLK_CORE_CGM_DJTAG_TCK_HW_CFG           ( CTL_BASE_AON_CLK_CORE + 0x00B8 )
#define REG_AON_CLK_CORE_CGM_SP_AHB_CFG                 ( CTL_BASE_AON_CLK_CORE + 0x00BC )
#define REG_AON_CLK_CORE_CGM_TMR_CFG                    ( CTL_BASE_AON_CLK_CORE + 0x00C0 )
#define REG_AON_CLK_CORE_CGM_DET_32K_CFG                ( CTL_BASE_AON_CLK_CORE + 0x00C4 )
#define REG_AON_CLK_CORE_CGM_PMU_CFG                    ( CTL_BASE_AON_CLK_CORE + 0x00C8 )
#define REG_AON_CLK_CORE_CGM_DEBOUNCE_CFG               ( CTL_BASE_AON_CLK_CORE + 0x00CC )
#define REG_AON_CLK_CORE_CGM_APCPU_PMU_CFG              ( CTL_BASE_AON_CLK_CORE + 0x00D0 )
#define REG_AON_CLK_CORE_CGM_FUNC_DMA_CFG               ( CTL_BASE_AON_CLK_CORE + 0x00D4 )
#define REG_AON_CLK_CORE_CGM_TOP_DVFS_CFG               ( CTL_BASE_AON_CLK_CORE + 0x00D8 )
#define REG_AON_CLK_CORE_CGM_OTG_UTMI_CFG               ( CTL_BASE_AON_CLK_CORE + 0x00DC )
#define REG_AON_CLK_CORE_CGM_OTG_REF_CFG                ( CTL_BASE_AON_CLK_CORE + 0x00E0 )
#define REG_AON_CLK_CORE_CGM_CSSYS_CFG                  ( CTL_BASE_AON_CLK_CORE + 0x00E4 )
#define REG_AON_CLK_CORE_CGM_CSSYS_PUB_CFG              ( CTL_BASE_AON_CLK_CORE + 0x00E8 )
#define REG_AON_CLK_CORE_CGM_CSSYS_APB_CFG              ( CTL_BASE_AON_CLK_CORE + 0x00EC )
#define REG_AON_CLK_CORE_CGM_AP_AXI_CFG                 ( CTL_BASE_AON_CLK_CORE + 0x00F0 )
#define REG_AON_CLK_CORE_CGM_AP_MM_CFG                  ( CTL_BASE_AON_CLK_CORE + 0x00F4 )
#define REG_AON_CLK_CORE_CGM_SDIO2_2X_CFG               ( CTL_BASE_AON_CLK_CORE + 0x00F8 )
#define REG_AON_CLK_CORE_CGM_SDIO2_1X_CFG               ( CTL_BASE_AON_CLK_CORE + 0x00FC )
#define REG_AON_CLK_CORE_CGM_ANALOG_IO_APB_CFG          ( CTL_BASE_AON_CLK_CORE + 0x0100 )
#define REG_AON_CLK_CORE_CGM_DMC_REF_CFG                ( CTL_BASE_AON_CLK_CORE + 0x0104 )
#define REG_AON_CLK_CORE_CGM_USB20_SCAN_ONLY_CFG        ( CTL_BASE_AON_CLK_CORE + 0x0108 )
#define REG_AON_CLK_CORE_CGM_EMC_CFG                    ( CTL_BASE_AON_CLK_CORE + 0x010C )
#define REG_AON_CLK_CORE_CGM_USB_CFG                    ( CTL_BASE_AON_CLK_CORE + 0x0110 )
#define REG_AON_CLK_CORE_CGM_AAPC_TEST_CFG              ( CTL_BASE_AON_CLK_CORE + 0x0114 )
#define REG_AON_CLK_CORE_CGM_26M_PMU_CFG                ( CTL_BASE_AON_CLK_CORE + 0x0118 )
#define REG_AON_CLK_CORE_CGM_CPHY_CFG_CFG               ( CTL_BASE_AON_CLK_CORE + 0x011C )
#define REG_AON_CLK_CORE_CGM_CSI_PHY_SCAN_ONLY_CFG      ( CTL_BASE_AON_CLK_CORE + 0x0120 )
#define REG_AON_CLK_CORE_CGM_WCDMA_SLICE_SCAN_ONLY_CFG  ( CTL_BASE_AON_CLK_CORE + 0x0124 )
#define REG_AON_CLK_CORE_CGM_26M_ETC_CFG                ( CTL_BASE_AON_CLK_CORE + 0x0128 )

/* REG_AON_CLK_CORE_CGM_AON_APB_CFG */

#define BIT_AON_CLK_CORE_CGM_AON_APB_CFG_CGM_AON_APB_DIV(x)                           (((x) & 0x3) << 8)
#define BIT_AON_CLK_CORE_CGM_AON_APB_CFG_CGM_AON_APB_SEL(x)                           (((x) & 0x7))

/* REG_AON_CLK_CORE_CGM_ADI_CFG */

#define BIT_AON_CLK_CORE_CGM_ADI_CFG_CGM_ADI_SEL(x)                                   (((x) & 0x7))

/* REG_AON_CLK_CORE_CGM_AUX0_CFG */

#define BIT_AON_CLK_CORE_CGM_AUX0_CFG_CGM_AUX0_DIV(x)                                 (((x) & 0xF) << 8)
#define BIT_AON_CLK_CORE_CGM_AUX0_CFG_CGM_AUX0_SEL(x)                                 (((x) & 0x1F))

/* REG_AON_CLK_CORE_CGM_AUX1_CFG */

#define BIT_AON_CLK_CORE_CGM_AUX1_CFG_CGM_AUX1_DIV(x)                                 (((x) & 0xF) << 8)
#define BIT_AON_CLK_CORE_CGM_AUX1_CFG_CGM_AUX1_SEL(x)                                 (((x) & 0x1F))

/* REG_AON_CLK_CORE_CGM_AUX2_CFG */

#define BIT_AON_CLK_CORE_CGM_AUX2_CFG_CGM_AUX2_DIV(x)                                 (((x) & 0xF) << 8)
#define BIT_AON_CLK_CORE_CGM_AUX2_CFG_CGM_AUX2_SEL(x)                                 (((x) & 0x1F))

/* REG_AON_CLK_CORE_CGM_PROBE_CFG */

#define BIT_AON_CLK_CORE_CGM_PROBE_CFG_CGM_PROBE_DIV(x)                               (((x) & 0xF) << 8)
#define BIT_AON_CLK_CORE_CGM_PROBE_CFG_CGM_PROBE_SEL(x)                               (((x) & 0x1F))

/* REG_AON_CLK_CORE_CGM_PWM0_CFG */

#define BIT_AON_CLK_CORE_CGM_PWM0_CFG_CGM_PWM0_SEL(x)                                 (((x) & 0x7))

/* REG_AON_CLK_CORE_CGM_PWM1_CFG */

#define BIT_AON_CLK_CORE_CGM_PWM1_CFG_CGM_PWM1_SEL(x)                                 (((x) & 0x7))

/* REG_AON_CLK_CORE_CGM_PWM2_CFG */

#define BIT_AON_CLK_CORE_CGM_PWM2_CFG_CGM_PWM2_SEL(x)                                 (((x) & 0x7))

/* REG_AON_CLK_CORE_CGM_PWM3_CFG */

#define BIT_AON_CLK_CORE_CGM_PWM3_CFG_CGM_PWM3_SEL(x)                                 (((x) & 0x7))

/* REG_AON_CLK_CORE_CGM_EFUSE_CFG */

#define BIT_AON_CLK_CORE_CGM_EFUSE_CFG_CGM_EFUSE_SEL                                  BIT(0)

/* REG_AON_CLK_CORE_CGM_UART0_CFG */

#define BIT_AON_CLK_CORE_CGM_UART0_CFG_CGM_UART0_SEL(x)                               (((x) & 0x7))

/* REG_AON_CLK_CORE_CGM_UART1_CFG */

#define BIT_AON_CLK_CORE_CGM_UART1_CFG_CGM_UART1_SEL(x)                               (((x) & 0x7))

/* REG_AON_CLK_CORE_CGM_32K_OUT_CFG */

#define BIT_AON_CLK_CORE_CGM_32K_OUT_CFG_CGM_32K_OUT_SEL                              BIT(0)

/* REG_AON_CLK_CORE_CGM_3K2_OUT_CFG */


/* REG_AON_CLK_CORE_CGM_1K_OUT_CFG */


/* REG_AON_CLK_CORE_CGM_THM0_CFG */

#define BIT_AON_CLK_CORE_CGM_THM0_CFG_CGM_THM0_SEL                                    BIT(0)

/* REG_AON_CLK_CORE_CGM_THM1_CFG */

#define BIT_AON_CLK_CORE_CGM_THM1_CFG_CGM_THM1_SEL                                    BIT(0)

/* REG_AON_CLK_CORE_CGM_THM2_CFG */

#define BIT_AON_CLK_CORE_CGM_THM2_CFG_CGM_THM2_SEL                                    BIT(0)

/* REG_AON_CLK_CORE_CGM_THM3_CFG */

#define BIT_AON_CLK_CORE_CGM_THM3_CFG_CGM_THM3_SEL                                    BIT(0)

/* REG_AON_CLK_CORE_CGM_CM4_I3C0_CFG */

#define BIT_AON_CLK_CORE_CGM_CM4_I3C0_CFG_CGM_CM4_I3C0_SEL(x)                         (((x) & 0x7))

/* REG_AON_CLK_CORE_CGM_CM4_I3C1_CFG */

#define BIT_AON_CLK_CORE_CGM_CM4_I3C1_CFG_CGM_CM4_I3C1_SEL(x)                         (((x) & 0x7))

/* REG_AON_CLK_CORE_CGM_CM4_SPI_CFG */

#define BIT_AON_CLK_CORE_CGM_CM4_SPI_CFG_CGM_CM4_SPI_PAD_SEL                          BIT(16)
#define BIT_AON_CLK_CORE_CGM_CM4_SPI_CFG_CGM_CM4_SPI_DIV(x)                           (((x) & 0x7) << 8)
#define BIT_AON_CLK_CORE_CGM_CM4_SPI_CFG_CGM_CM4_SPI_SEL(x)                           (((x) & 0x7))

/* REG_AON_CLK_CORE_CGM_AON_I2C_CFG */

#define BIT_AON_CLK_CORE_CGM_AON_I2C_CFG_CGM_AON_I2C_SEL(x)                           (((x) & 0x7))

/* REG_AON_CLK_CORE_CGM_AON_IIS_CFG */

#define BIT_AON_CLK_CORE_CGM_AON_IIS_CFG_CGM_AON_IIS_SEL(x)                           (((x) & 0x3))

/* REG_AON_CLK_CORE_CGM_SCC_CFG */

#define BIT_AON_CLK_CORE_CGM_SCC_CFG_CGM_SCC_SEL(x)                                   (((x) & 0x3))

/* REG_AON_CLK_CORE_CGM_APCPU_DAP_CFG */

#define BIT_AON_CLK_CORE_CGM_APCPU_DAP_CFG_CGM_APCPU_DAP_SEL(x)                       (((x) & 0x7))

/* REG_AON_CLK_CORE_CGM_APCPU_DAP_MTCK_CFG */

#define BIT_AON_CLK_CORE_CGM_APCPU_DAP_MTCK_CFG_CGM_APCPU_DAP_MTCK_PAD_SEL            BIT(16)

/* REG_AON_CLK_CORE_CGM_APCPU_TS_CFG */

#define BIT_AON_CLK_CORE_CGM_APCPU_TS_CFG_CGM_APCPU_TS_SEL(x)                         (((x) & 0x3))

/* REG_AON_CLK_CORE_CGM_DEBUG_TS_CFG */

#define BIT_AON_CLK_CORE_CGM_DEBUG_TS_CFG_CGM_DEBUG_TS_SEL(x)                         (((x) & 0x3))

/* REG_AON_CLK_CORE_CGM_DSI_TEST_S_CFG */

#define BIT_AON_CLK_CORE_CGM_DSI_TEST_S_CFG_CGM_DSI_TEST_S_PAD_SEL                    BIT(16)

/* REG_AON_CLK_CORE_CGM_RFTI_SBI_CFG */

#define BIT_AON_CLK_CORE_CGM_RFTI_SBI_CFG_CGM_RFTI_SBI_SEL(x)                         (((x) & 0x7))

/* REG_AON_CLK_CORE_CGM_RFTI1_XO_CFG */

#define BIT_AON_CLK_CORE_CGM_RFTI1_XO_CFG_CGM_RFTI1_XO_SEL                            BIT(0)

/* REG_AON_CLK_CORE_CGM_RFTI_LTH_CFG */

#define BIT_AON_CLK_CORE_CGM_RFTI_LTH_CFG_CGM_RFTI_LTH_SEL                            BIT(0)

/* REG_AON_CLK_CORE_CGM_RFTI2_XO_CFG */

#define BIT_AON_CLK_CORE_CGM_RFTI2_XO_CFG_CGM_RFTI2_XO_SEL                            BIT(0)

/* REG_AON_CLK_CORE_CGM_RCO100M_REF_CFG */

#define BIT_AON_CLK_CORE_CGM_RCO100M_REF_CFG_CGM_RCO100M_REF_SEL                      BIT(0)

/* REG_AON_CLK_CORE_CGM_RCO100M_FDK_CFG */

#define BIT_AON_CLK_CORE_CGM_RCO100M_FDK_CFG_CGM_RCO100M_FDK_SEL                      BIT(0)

/* REG_AON_CLK_CORE_CGM_DJTAG_TCK_CFG */

#define BIT_AON_CLK_CORE_CGM_DJTAG_TCK_CFG_CGM_DJTAG_TCK_PAD_SEL                      BIT(16)
#define BIT_AON_CLK_CORE_CGM_DJTAG_TCK_CFG_CGM_DJTAG_TCK_SEL                          BIT(0)

/* REG_AON_CLK_CORE_CGM_DJTAG_TCK_HW_CFG */

#define BIT_AON_CLK_CORE_CGM_DJTAG_TCK_HW_CFG_CGM_DJTAG_TCK_HW_PAD_SEL                BIT(16)

/* REG_AON_CLK_CORE_CGM_SP_AHB_CFG */

#define BIT_AON_CLK_CORE_CGM_SP_AHB_CFG_CGM_SP_AHB_DIV(x)                             (((x) & 0x3) << 8)
#define BIT_AON_CLK_CORE_CGM_SP_AHB_CFG_CGM_SP_AHB_SEL(x)                             (((x) & 0x7))

/* REG_AON_CLK_CORE_CGM_TMR_CFG */

#define BIT_AON_CLK_CORE_CGM_TMR_CFG_CGM_TMR_SEL(x)                                   (((x) & 0x3))

/* REG_AON_CLK_CORE_CGM_DET_32K_CFG */

#define BIT_AON_CLK_CORE_CGM_DET_32K_CFG_CGM_DET_32K_SEL                              BIT(0)

/* REG_AON_CLK_CORE_CGM_PMU_CFG */

#define BIT_AON_CLK_CORE_CGM_PMU_CFG_CGM_PMU_SEL(x)                                   (((x) & 0x3))

/* REG_AON_CLK_CORE_CGM_DEBOUNCE_CFG */

#define BIT_AON_CLK_CORE_CGM_DEBOUNCE_CFG_CGM_DEBOUNCE_SEL(x)                         (((x) & 0x3))

/* REG_AON_CLK_CORE_CGM_APCPU_PMU_CFG */

#define BIT_AON_CLK_CORE_CGM_APCPU_PMU_CFG_CGM_APCPU_PMU_SEL(x)                       (((x) & 0x3))

/* REG_AON_CLK_CORE_CGM_FUNC_DMA_CFG */

#define BIT_AON_CLK_CORE_CGM_FUNC_DMA_CFG_CGM_FUNC_DMA_PAD_SEL                        BIT(16)

/* REG_AON_CLK_CORE_CGM_TOP_DVFS_CFG */

#define BIT_AON_CLK_CORE_CGM_TOP_DVFS_CFG_CGM_TOP_DVFS_SEL(x)                         (((x) & 0x3))

/* REG_AON_CLK_CORE_CGM_OTG_UTMI_CFG */

#define BIT_AON_CLK_CORE_CGM_OTG_UTMI_CFG_CGM_OTG_UTMI_PAD_SEL                        BIT(16)

/* REG_AON_CLK_CORE_CGM_OTG_REF_CFG */

#define BIT_AON_CLK_CORE_CGM_OTG_REF_CFG_CGM_OTG_REF_SEL                              BIT(0)

/* REG_AON_CLK_CORE_CGM_CSSYS_CFG */

#define BIT_AON_CLK_CORE_CGM_CSSYS_CFG_CGM_CSSYS_DIV(x)                               (((x) & 0x3) << 8)
#define BIT_AON_CLK_CORE_CGM_CSSYS_CFG_CGM_CSSYS_SEL(x)                               (((x) & 0x7))

/* REG_AON_CLK_CORE_CGM_CSSYS_PUB_CFG */

#define BIT_AON_CLK_CORE_CGM_CSSYS_PUB_CFG_CGM_CSSYS_PUB_DIV(x)                       (((x) & 0x3) << 8)

/* REG_AON_CLK_CORE_CGM_CSSYS_APB_CFG */

#define BIT_AON_CLK_CORE_CGM_CSSYS_APB_CFG_CGM_CSSYS_APB_DIV(x)                       (((x) & 0x3) << 8)

/* REG_AON_CLK_CORE_CGM_AP_AXI_CFG */

#define BIT_AON_CLK_CORE_CGM_AP_AXI_CFG_CGM_AP_AXI_SEL(x)                             (((x) & 0x3))

/* REG_AON_CLK_CORE_CGM_AP_MM_CFG */

#define BIT_AON_CLK_CORE_CGM_AP_MM_CFG_CGM_AP_MM_SEL(x)                               (((x) & 0x3))

/* REG_AON_CLK_CORE_CGM_SDIO2_2X_CFG */

#define BIT_AON_CLK_CORE_CGM_SDIO2_2X_CFG_CGM_SDIO2_2X_SEL(x)                         (((x) & 0x7))

/* REG_AON_CLK_CORE_CGM_SDIO2_1X_CFG */


/* REG_AON_CLK_CORE_CGM_ANALOG_IO_APB_CFG */

#define BIT_AON_CLK_CORE_CGM_ANALOG_IO_APB_CFG_CGM_ANALOG_IO_APB_DIV(x)               (((x) & 0x3) << 8)
#define BIT_AON_CLK_CORE_CGM_ANALOG_IO_APB_CFG_CGM_ANALOG_IO_APB_SEL                  BIT(0)

/* REG_AON_CLK_CORE_CGM_DMC_REF_CFG */

#define BIT_AON_CLK_CORE_CGM_DMC_REF_CFG_CGM_DMC_REF_SEL(x)                           (((x) & 0x3))

/* REG_AON_CLK_CORE_CGM_USB20_SCAN_ONLY_CFG */

#define BIT_AON_CLK_CORE_CGM_USB20_SCAN_ONLY_CFG_CGM_USB20_SCAN_ONLY_SEL              BIT(0)

/* REG_AON_CLK_CORE_CGM_EMC_CFG */

#define BIT_AON_CLK_CORE_CGM_EMC_CFG_CGM_EMC_SEL(x)                                   (((x) & 0x3))

/* REG_AON_CLK_CORE_CGM_USB_CFG */

#define BIT_AON_CLK_CORE_CGM_USB_CFG_CGM_USB_PAD_SEL                                  BIT(16)
#define BIT_AON_CLK_CORE_CGM_USB_CFG_CGM_USB_DIV(x)                                   (((x) & 0x3) << 8)
#define BIT_AON_CLK_CORE_CGM_USB_CFG_CGM_USB_SEL(x)                                   (((x) & 0x7))

/* REG_AON_CLK_CORE_CGM_AAPC_TEST_CFG */

#define BIT_AON_CLK_CORE_CGM_AAPC_TEST_CFG_CGM_AAPC_TEST_DIV(x)                       (((x) & 0xF) << 8)
#define BIT_AON_CLK_CORE_CGM_AAPC_TEST_CFG_CGM_AAPC_TEST_SEL                          BIT(0)

/* REG_AON_CLK_CORE_CGM_26M_PMU_CFG */

#define BIT_AON_CLK_CORE_CGM_26M_PMU_CFG_CGM_26M_PMU_SEL                              BIT(0)

/* REG_AON_CLK_CORE_CGM_CPHY_CFG_CFG */

#define BIT_AON_CLK_CORE_CGM_CPHY_CFG_CFG_CGM_CPHY_CFG_SEL                            BIT(0)

/* REG_AON_CLK_CORE_CGM_CSI_PHY_SCAN_ONLY_CFG */

#define BIT_AON_CLK_CORE_CGM_CSI_PHY_SCAN_ONLY_CFG_CGM_CSI_PHY_SCAN_ONLY_SEL          BIT(0)

/* REG_AON_CLK_CORE_CGM_WCDMA_SLICE_SCAN_ONLY_CFG */

#define BIT_AON_CLK_CORE_CGM_WCDMA_SLICE_SCAN_ONLY_CFG_CGM_WCDMA_SLICE_SCAN_ONLY_SEL  BIT(0)

/* REG_AON_CLK_CORE_CGM_26M_ETC_CFG */

#define BIT_AON_CLK_CORE_CGM_26M_ETC_CFG_CGM_26M_ETC_SEL                              BIT(0)

#endif