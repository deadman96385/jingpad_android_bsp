/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef HARDWARE_H
#define HARDWARE_H

#define SPRD_CORESIGHT_STM_PHYS                            0x01000000
#define SPRD_GIC600_PHYS                                   0x14000000
#define SPRD_DMA0_PHYS                                     0x20100000
#define SPRD_USB_OTG_PHYS                                  0x20200000
#define SPRD_SDIO0_PHYS                                    0x20300000
#define SPRD_SDIO1_PHYS                                    0x20400000
#define SPRD_SDIO2_PHYS                                    0x20500000
#define SPRD_EMMC_PHYS                                     0x20600000
#define SPRD_AHB_PHYS                                      0x20E00000
#define SPRD_NANDC_PHYS                                    0x20F00000
#define SPRD_PUBLIC_CE_PHYS                                0x21300000
#define SPRD_SECURE_CE_PHYS                                0x21400000
#define SPRD_APCLK_PHYS                                    0x21500000
#define SPRD_DDR_PHYS                                      0x30000000
#define SPRD_PERF_TRACE_PHYS                               0x30010000
#define SPRD_DDR_BIST_CHN0_PHYS                            0x30080000
#define SPRD_DDR_BIST_CHN1_PHYS                            0x30084000
#define SPRD_DDR_BIST_CHN2_PHYS                            0x30088000
#define SPRD_DDR_BIST_CHN3_PHYS                            0x3008C000
#define SPRD_MEM_FW_PUB_PHYS                               0x30090000
#define SPRD_DFI_PHYS                                      0x300C0000
#define SPRD_PUB_PHYS                                      0x300E0000
#define SPRD_PUB_WRAP_PHYS                                 0x300F0000
#define SPRD_PUBSYS_PHYS                                   0x30200000
#define SPRD_QOSC_PHYS                                     0x30210000
#define SPRD_DDRPHY_CHN0_PHYS                              0x30400000
#define SPRD_DDRPHY_CHN1_PHYS                              0x30410000
#define SPRD_AUDIO_PHYS                                    0x40000000
#define SPRD_CHIP_RESET_PHYS                               0x40010000
#define SPRD_VBC_PHYS                                      0x40020000
#define SPRD_SYSTIMER_PHYS                                 0x40040000
#define SPRD_AON_TIMER_PHYS                                0x40050000
#define SPRD_HWLOCK1_PHYS                                  0x40060000
#define SPRD_RFTI_PHYS                                     0x40070000
#define SPRD_I2C_PHYS                                      0x40080000
#define SPRD_MBOX_PHYS                                     0x400A0000
#define SPRD_CP_TMR_PHYS                                   0x400B0000
#define SPRD_CP_SYST_PHYS                                  0x400C0000
#define SPRD_CP_WDG_PHYS                                   0x400D0000
#define SPRD_CPALL_EIC_PHYS                                0x400E0000
#define SPRD_DEF_PHYS                                      0x400F0000
#define SPRD_DMA_PHYS                                      0x40100000
#define SPRD_INT_PHYS                                      0x40200000
#define SPRD_EIC_PHYS                                      0x40210000
#define SPRD_SYSCNT_PHYS                                   0x40230000
#define SPRD_UIDEFUSE_PHYS                                 0x40240000
#define SPRD_KPD_PHYS                                      0x40250000
#define SPRD_PWM_PHYS                                      0x40260000
#define SPRD_BUS_MON_TIMER_PHYS                            0x40270000
#define SPRD_GPIO_PHYS                                     0x40280000
#define SPRD_WDG_PHYS                                      0x40290000
#define SPRD_PIN_PHYS                                      0x402A0000
#define SPRD_PMU_PHYS                                      0x402B0000
#define SPRD_GPIO_PLUS_PHYS                                0x402C0000
#define SPRD_AONCKG_PHYS                                   0x402D0200
#define SPRD_AONAPB_PHYS                                   0x402E0000
#define SPRD_THM0_PHYS                                     0x402F0000
#define SPRD_DVFS_CTRL_PHYS                                0x40300000
#define SPRD_APWDG_PHYS                                    0x40310000
#define SPRD_DJTAG_PHYS                                    0x40340000
#define SPRD_ANALOG_TEST0_PHYS                             0x40350000
#define SPRD_ANALOG_TEST1_PHYS                             0x40360000
#define SPRD_EIC1_PHYS                                     0x40370000
#define SPRD_SEC_EIC_PHYS                                  0x40380000
#define SPRD_THM1_PHYS                                     0x40390000
#define SPRD_WCN_PHYS                                      0x403A0000
#define SPRD_SCC_PHYS                                      0x403B0000
#define SPRD_APCPUTS0_PHYS                                 0x40400000
#define SPRD_SEC_TZPC_PHYS                                 0x40420000
#define SPRD_SEC_TIMER_PHYS                                0x40430000
#define SPRD_SEC_RTC_PHYS                                  0x40440000
#define SPRD_SEC_WDG_PHYS                                  0x40450000
#define SPRD_SEC_REG_PHYS                                  0x40460000
#define SPRD_CROSS_TRIGGER_PHYS                            0x40480000
#define SPRD_SEC_GPIO_PHYS                                 0x40490000
#define SPRD_PUB_CP_INTC_PHYS                              0x404C0000
#define SPRD_WTL_CP_INTC_PHYS                              0x404D0000
#define SPRD_TGDSP_INTC_PHYS                               0x404E0000
#define SPRD_LDSP_INTC_PHYS                                0x404F0000
#define SPRD_AP_INTC0_PHYS                                 0x40500000
#define SPRD_AP_INTC1_PHYS                                 0x40510000
#define SPRD_AP_INTC2_PHYS                                 0x40520000
#define SPRD_AP_INTC3_PHYS                                 0x40530000
#define SPRD_AP_INTC4_PHYS                                 0x40540000
#define SPRD_AP_INTC5_PHYS                                 0x40550000
#define SPRD_ADI_PHYS                                      0x41800000
#define SPRD_ADISLAVE_PHYS                                 0x41808000
#define SPRD_IMG_GE8322_PHYS                               0x60000000
#define SPRD_GPUAPB_PHYS                                   0x60100000
#define SPRD_MMAHB_PHYS                                    0x60800000
#define SPRD_MMCKG_PHYS                                    0x60900000
#define SPRD_DCAM_PHYS                                     0x60A00000
#define SPRD_ISP_PHYS                                      0x60B00000
#define SPRD_CSI2_PHYS                                     0x60C00000
#define SPRD_CSI2X2_PHYS                                   0x60D00000
#define SPRD_CSI2X3_PHYS                                   0x60E00000
#define SPRD_MMVSP_AHB_PHYS                                0x62000000
#define SPRD_MMVSP_CKG_PHYS                                0x62100000
#define SPRD_VSP_PHYS                                      0x62200000
#define SPRD_JPG_PHYS                                      0x62300000
#define SPRD_CPP_PHYS                                      0x62400000
#define SPRD_DPU_PHYS                                      0x63000000
#define SPRD_DSI_PHYS                                      0x63100000
#define SPRD_UART0_PHYS                                    0x70000000
#define SPRD_UART1_PHYS                                    0x70100000
#define SPRD_UART2_PHYS                                    0x70200000
#define SPRD_UART3_PHYS                                    0x70300000
#define SPRD_UART4_PHYS                                    0x70400000
#define SPRD_I2C0_PHYS                                     0x70500000
#define SPRD_I2C1_PHYS                                     0x70600000
#define SPRD_I2C2_PHYS                                     0x70700000
#define SPRD_I2C3_PHYS                                     0x70800000
#define SPRD_I2C4_PHYS                                     0x70900000
#define SPRD_SPI0_PHYS                                     0x70A00000
#define SPRD_SPI1_PHYS                                     0x70B00000
#define SPRD_SPI2_PHYS                                     0x70C00000
#define SPRD_IIS0_PHYS                                     0x70D00000
#define SPRD_IIS1_PHYS                                     0x70E00000
#define SPRD_IIS2_PHYS                                     0x70F00000
#define SPRD_SIM0_PHYS                                     0x71100000
#define SPRD_APBREG_PHYS                                   0x71300000
#define SPRD_SPI3_PHYS                                     0x71400000
#define SPRD_I2C5_PHYS                                     0x71500000
#define SPRD_I2C6_PHYS                                     0x71600000

/* referenced by mmc_v40.c */
#define EMMC_BASE_ADDR                                     SPRD_EMMC_PHYS
#define SDIO0_BASE_ADDR                                    SPRD_SDIO0_PHYS
#define SPRD_AONCKG_BASE                                   SPRD_AONCKG_PHYS
/* referenced by adi.c */
#define SPRD_MISC_PHYS                                     SPRD_ADI_PHYS
/* referenced by serial_sc8800x.c */
#define ARM_UART0_BASE					   SPRD_UART0_PHYS
#define ARM_UART1_BASE                                     SPRD_UART1_PHYS
/* referenced by fdl_main.c */
#define USB_REG_BASE                                       SPRD_USB_OTG_PHYS

#endif
