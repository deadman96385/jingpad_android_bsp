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


#define SPRD_DMA_CTRL_PHYS                                 0x20000000
#define SPRD_AHB_PHYS                                      0x20100000
#define SPRD_APCLK_PHYS                                    0x20200000
#define SPRD_DPU_PHYS                                      0x20300000
#define SPRD_DSI_PHYS                                      0x20400000
#define SPRD_VSP_PHYS                                      0x20500000
#define SPRD_PUB_PHYS                                      0x31000000
#define SPRD_DFI_PHYS                                      0x31010000
#define SPRD_PUB_QOSC_AHB_PHYS                             0x31020000
#define SPRD_PUB_AHB_PHYS                                  0x31030000
#define SPRD_PUB_APB_PHYS                                  0x31050000
#define SPRD_PERF_TRACE_PHYS                               0x31060000
#define SPRD_DDR_BIST_TEST_PHYS                            0x31070000
#define SPRD_AON_EIC_EXT0_PHYS                             0x32000000
#define SPRD_AON_EIC_EXT1_PHYS                             0x32010000
#define SPRD_AON_EIC_EXT2_PHYS                             0x32020000
#define SPRD_AON_EIC_EXT3_PHYS                             0x32030000
#define SPRD_AON_SYSTIMER_PHYS                             0x32040000
#define SPRD_AON_TIMER_PHYS                                0x32050000
#define SPRD_AON_I2C_PHYS                                  0x32060000
#define SPRD_AON_GPIO_PHYS                                 0x32070000
#define SPRD_AONCKG_PHYS                                   0x32080000
#define SPRD_MBOX_PHYS                                     0x320A0000
#define SPRD_WTL_CP_INTC_PHYS                              0x320B0000
#define SPRD_LDSP_INTC_PHYS                                0x320C0000
#define SPRD_TGDSP_INTC_PHYS                               0x320D0000
#define SPRD_PUB_CP_INTC_PHYS                              0x320E0000
#define SPRD_AUD_CP_INTC_PHYS                              0x320F0000
#define SPRD_ADI_PHYS                                      0x32100000
#ifdef ADI_15BIT_MODE
#define SPRD_ADISLAVE_PHYS                                 0x32120000
#else
#define SPRD_ADISLAVE_PHYS                                 0x32108000
#endif
#define SPRD_THM0_PHYS                                     0x32200000
#define SPRD_THM1_PHYS                                     0x32210000
#define SPRD_THM2_PHYS                                     0x32220000
#define SPRD_AON_EIC_EXT4_PHYS                             0x32230000
#define SPRD_UIDEFUSE_PHYS                                 0x32240000
#define SPRD_KPD_PHYS                                      0x32250000
#define SPRD_PWM_PHYS                                      0x32260000
#define SPRD_AON_EIC_EXT5_PHYS                             0x32270000
#define SPRD_CHIP_RESET_PHYS                               0x32290000
#define SPRD_DVFS_TOP_PHYS                                 0x322A0000
#define SPRD_AP_TIMER0_PHYS                                0x322B0000
#define SPRD_AP_TIMER1_PHYS                                0x322C0000
#define SPRD_AP_TIMER2_PHYS                                0x322D0000
#define SPRD_SYSCNT_PHYS                                   0x322E0000
#define SPRD_APCPU_WDG_PHYS                                0x322F0000
#define SPRD_APWDG_PHYS                                    0x32300000
#define SPRD_AP_INTC0_PHYS                                 0x32310000
#define SPRD_AP_INTC1_PHYS                                 0x32320000
#define SPRD_AP_INTC2_PHYS                                 0x32330000
#define SPRD_AP_INTC3_PHYS                                 0x32340000
#define SPRD_AP_INTC4_PHYS                                 0x32350000
#define SPRD_AP_INTC5_PHYS                                 0x32360000
#define SPRD_ESE_PHYS                                      0x32380000
#define SPRD_ANALOG_PHYS                                   0x32390000
#define SPRD_PIN_PHYS                                      0x32450000
#define SPRD_RFTI_PHYS                                     0x32460000
#define SPRD_CPALL_EIC_PHYS                                0x32470000
#define SPRD_CP_WDG_PHYS                                   0x32480000
#define SPRD_CP_SYST_PHYS                                  0x32490000
#define SPRD_CP_TMR_PHYS                                   0x324A0000
#define SPRD_BUS_MON_TIMER1_PHYS                           0x324B0000
#define SPRD_BUS_MON_TIMER2_PHYS                           0x324C0000
#define SPRD_SCC_PHYS                                      0x324D0000
#define SPRD_CENTRAL_DEBUG_PHYS                            0x324E0000
#define SPRD_SERDES_PHYS                                   0x324F0000
#define SPRD_USB_AUDIO_IIS_PHYS                            0x32600000
#define SPRD_APCPUTS0_PHYS                          	   0x32610000
#define SPRD_AON_APB_PHYS                                  0x327D0000
#define SPRD_PMU_PHYS                                      0x327E0000
#define SPRD_SPINLOCK_PHYS                                 0x327F0000
#define SPRD_SEC_TZPC_PHYS                                 0x32800000
#define SPRD_SEC_EIC_PHYS                                  0x32810000
#define SPRD_CLK_32K_DET_PHYS                              0x32820000
#define SPRD_SEC_TIMER_PHYS                                0x32840000
#define SPRD_SEC_RTC_PHYS                                  0x32850000
#define SPRD_SEC_WDG_PHYS                                  0x32860000
#define SPRD_SEC_GPIO_PHYS                                 0x32870000
#define SPRD_SEC_REG_PHYS                                  0x32880000
#define SPRD_SEC_DEBUG_REG_PHYS                            0x32890000
#define SPRD_AUDCP_PERI_PHYS                               0x33000000
#define SPRD_CORESIGHT_STM_PHYS                            0x34000000
#define SPRD_CORESIGHT_SEC_PHYS                            0x3C000000
#define SPRD_SP_AHB_REG_PHYS                               0x51000000
#define SPRD_SP_SYSTIMER_PHYS                              0x51020000
#define SPRD_SP_TIMER_PHYS                                 0x51030000
#define SPRD_SP_EIC_GPIO_PHYS                              0x51060000
#define SPRD_SP_EIC_PHYS                                   0x51070000
#define SPRD_SP_WDG_PHYS                                   0x51080000
#define SPRD_SP_UART0_PHYS                                 0x51090000
#define SPRD_SP_UART1_PHYS                                 0x510A0000
#define SPRD_SP_GPIO_PHYS                                  0x510B0000
#define SPRD_SP_I3C0_PHYS                                  0x510C0000
#define SPRD_SP_I3C1_PHYS                                  0x510D0000
#define SPRD_SP_SPI_PHYS                                   0x510F0000
#define SPRD_SP_DMA_PHYS                                   0x52000000
#define SPRD_USB_REG_PHYS                                  0x5FFF0000
#define SPRD_GPU_PHYS                                      0x60000000
#define SPRD_GPUAPB_PHYS                                   0x60100000
#define SPRD_DVFS_APB_PHYS                                 0x60110000
#define SPRD_ISP_PHYS                                      0x62000000
#define SPRD_MMCKG_PHYS                                    0x62100000
#define SPRD_MMAHB_PHYS                                    0x62200000
#define SPRD_CSI0_PHYS                                     0x62300000
#define SPRD_CSI1_PHYS                                     0x62400000
#define SPRD_CSI2_PHYS                                     0x62500000
#define SPRD_DVFS_CTRL_PHYS                                0x62600000
#define SPRD_JPG_PHYS                                      0x62700000
#define SPRD_CPP_PHYS                                      0x62800000
#define SPRD_DCAM_PHYS                                     0x62900000
#define SPRD_FD_PHYS                                       0x62A00000
#define SPRD_UART0_PHYS                                    0x70000000
#define SPRD_UART1_PHYS                                    0x70100000
#define SPRD_UART2_PHYS                                    0x70200000
#define SPRD_I2C0_PHYS                                     0x70300000
#define SPRD_I2C1_PHYS                                     0x70400000
#define SPRD_I2C2_PHYS                                     0x70500000
#define SPRD_I2C3_PHYS                                     0x70600000
#define SPRD_I2C4_PHYS                                     0x70700000
#define SPRD_SPI0_PHYS                                     0x70800000
#define SPRD_SPI1_PHYS                                     0x70900000
#define SPRD_SPI2_PHYS                                     0x70A00000
#define SPRD_SPI3_PHYS                                     0x70B00000
#define SPRD_IIS0_PHYS                                     0x70C00000
#define SPRD_IIS1_PHYS                                     0x70D00000
#define SPRD_IIS2_PHYS                                     0x70E00000
#define SPRD_SIM0_PHYS                                     0x70F00000
#define SPRD_APBREG_PHYS                                   0x71000000
#define SPRD_SDIO0_PHYS                                    0x71100000
#define SPRD_SDIO1_PHYS                                    0x71200000
#define SPRD_SDIO2_PHYS                                    0x71300000
#define SPRD_EMMC_PHYS                                     0x71400000
#define SPRD_PUBLIC_CE_PHYS                                0x71500000
#define SPRD_SECURE_CE_PHYS                                0x71600000
#define SPRD_AP_DVFS_PHYS                                  0x71700000


/* referenced by mmc_v40.c */
#define EMMC_BASE_ADDR                                     SPRD_EMMC_PHYS
#define SDIO0_BASE_ADDR                                    SPRD_SDIO0_PHYS
#define SPRD_AONCKG_BASE                                   SPRD_AONCKG_PHYS
/* referenced by adi.c */
#define SPRD_MISC_PHYS                                     SPRD_ADI_PHYS
/* referenced by serial_sc8800x.c */
#define ARM_UART0_BASE				           SPRD_UART0_PHYS
#define ARM_UART1_BASE                                     SPRD_UART1_PHYS
/* referenced by fdl_main.c */
#define USB_REG_BASE                                       SPRD_USB_REG_PHYS

#endif
