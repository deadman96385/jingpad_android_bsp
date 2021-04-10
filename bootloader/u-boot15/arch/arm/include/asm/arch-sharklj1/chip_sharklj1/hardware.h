/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */

#ifndef HARDWARE_H
#define HARDWARE_H

#define REGS_AON_APB_BASE		SPRD_AONAPB_PHYS

#define SPRD_CORESIGHT_STM_PHYS                            0x01000000
#define SPRD_CORESIGHT_PHYS                                0x10000000
#define SPRD_GIC400_PHYS                                   0x12000000
#define SPRD_CCI400_PHYS                                   0x12190000
#define SPRD_DMA0_PHYS                                     0x20100000
#define SPRD_USB_OTG_PHYS                                  0x20200000
#define SPRD_SDIO0_PHYS                                    0x20300000
#define SPRD_SDIO1_PHYS                                    0x20400000
#define SPRD_SDIO2_PHYS                                    0x20500000
#define SPRD_EMMC_PHYS                                     0x20600000
#define SPRD_DISPC0_PHYS                                   0x20800000
#define SPRD_GSP_PHYS                                      0x20A00000
#define SPRD_AHB_PHYS                                      0x20E00000
#define SPRD_NANDC_PHYS                                    0x20F00000
#define SPRD_PUBLIC_CE_PHYS                                0x21300000
#define SPRD_SECURE_CE_PHYS                                0x21400000
#define SPRD_APCLK_PHYS                                    0x21500000
#define SPRD_DSI_PHYS                                      0x21800000
#define SPRD_CE_EFUSE_PHYS                                 0x21C00000
#define SPRD_DDR_PHYS                                      0x30000000
#define SPRD_AXIBM0_PHYS                                   0x30040000
#define SPRD_AXIBM1_PHYS                                   0x30050000
#define SPRD_AXIBM2_PHYS                                   0x30060000
#define SPRD_AXIBM3_PHYS                                   0x30070000
#define SPRD_AXIBM4_PHYS                                   0x30080000
#define SPRD_AXIBM5_PHYS                                   0x30090000
#define SPRD_AXIBM6_PHYS                                   0x300A0000
#define SPRD_AXIBM7_PHYS                                   0x300B0000
#define SPRD_DFI_PHYS                                      0x300C0000
#define SPRD_PUB_PHYS                                      0x300E0000
#define SPRD_QOS400_PHYS                                   0x30100000
#define SPRD_AUDIO_PHYS                                    0x40000000
#define SPRD_VBC_PHYS                                      0x40020000
#define SPRD_SYSTIMER_PHYS                                 0x40040000
#define SPRD_AON_TIMER_PHYS                                0x40050000
#define SPRD_HWLOCK1_PHYS                                  0x40060000
#define SPRD_RFTI_PHYS                                     0x40070000
#define SPRD_MBOX_PHYS                                     0x400A0000
#define SPRD_CP_TMR_PHYS                                   0x400B0000
#define SPRD_CP_SYST_PHYS                                  0x400C0000
#define SPRD_CP_WDG_PHYS                                   0x400D0000
#define SPRD_CPALL_EIC_PHYS                                0x400E0000
#define SPRD_DEF_PHYS                                      0x400F0000
#define SPRD_DMA_PHYS                                      0x40100000
#define SPRD_INT_PHYS                                      0x40200000
#define SPRD_EIC_PHYS                                      0x40210000
#define SPRD_APTIMER0_PHYS                                 0x40220000
#define SPRD_SYSCNT_PHYS                                   0x40230000
#define SPRD_UIDEFUSE_PHYS                                 0x40240000
#define SPRD_KPD_PHYS                                      0x40250000
#define SPRD_PWM_PHYS                                      0x40260000
#define SPRD_BUS_MON_TIMER_PHYS                            0x40270000
#define SPRD_GPIO_PHYS                                     0x40280000
#define SPRD_WDG_PHYS                                      0x40290000
#define SPRD_PIN_PHYS                                      0x402A0000
#define SPRD_PMU_PHYS                                      0x402B0000
#define SPRD_AONCKG_PHYS                                   0x402D0200
#define SPRD_AONAPB_PHYS                                   0x402E0000
#define SPRD_THM_PHYS                                      0x402F0000
#define SPRD_APWDG_PHYS                                    0x40310000
#define SPRD_APTIMER1_PHYS                                 0x40320000
#define SPRD_APTIMER2_PHYS                                 0x40330000
#define SPRD_DJTAG_PHYS                                    0x40340000
#define SPRD_ANA_TEST0_PHYS                                0x40350000
#define SPRD_ANLG_PHY_G1                                   0x40350000
#define SPRD_ANLG_PHY_G2                                   0x40353000
#define SPRD_ANLG_PHY_G3                                   0x40356000
#define SPRD_ANLG_PHY_G4                                   0x4035C000
#define SPRD_ANLG_PHY_G5                                   0x40359000
#define SPRD_ANA_TEST1_PHYS                                0x40360000
#define SPRD_EIC1_PHYS                                     0x40370000
#define SPRD_SEC_EIC_PHYS                                  0x40380000
#define SPRD_THM1_PHYS                                     0x40390000
#define SPRD_SCC_PHYS                                      0x403B0000
#define SPRD_ADI_PHYS                                      0x403C0000
#define SPRD_ADISLAVE_PHYS                                 0x403C8000
#define SPRD_APCPUTS0_PHYS                                 0x40400000
#define SPRD_SEC_TZPC_PHYS                                 0x40420000
#define SPRD_SEC_TIMER_PHYS                                0x40430000
#define SPRD_SEC_RTC_PHYS                                  0x40440000
#define SPRD_SEC_WDG_PHYS                                  0x40450000
#define SPRD_SEC_REG_PHYS                                  0x40460000
#define SPRD_SERDES_CTL_PHYS                               0x40470000
#define SPRD_CROSS_TRIGGER_PHYS                            0x40480000
#define SPRD_SEC_GPIO_PHYS                                 0x40490000
#define SPRD_SERDES_APB_PHYS                               0x404A0000
#define SPRD_SERDES_TESTREG_PHYS                           0x404B0000
#define SPRD_PUB_CP_INTC_PHYS                              0x404C0000
#define SPRD_WTL_CP_INTC_PHYS                              0x404D0000
#define SPRD_TGDSP_INTC_PHYS                               0x404E0000
#define SPRD_LDSP_INTC_PHYS                                0x404F0000
#define SPRD_AP_INT0                                       0x40500000
#define SPRD_AP_INT1                                       0x40510000
#define SPRD_AP_INT2                                       0x40520000
#define SPRD_AP_INT3                                       0x40530000
#define SPRD_AP_INT4                                       0x40540000
#define SPRD_AP_INT5                                       0x40550000
#define SPRD_MALI_PHYS                                     0x60000000
#define SPRD_GPUAPB_PHYS                                   0x60100000
#define SPRD_DCAM_PHYS                                     0x60800000
#define SPRD_VSP_PHYS                                      0x60900000
#define SPRD_ISP_PHYS                                      0x60A00000
#define SPRD_JPG_PHYS                                      0x60B00000
#define SPRD_CSI2_PHYS                                     0x60C00000
#define SPRD_MMAHB_PHYS                                    0x60D00000
#define SPRD_MMCKG_PHYS                                    0x60E00000
#define SPRD_CAM_MXT_PHYS                                  0x60F00000
#define SPRD_CPP_PHYS                                      0x61000000
#define SPRD_CSI2X2_PHYS                                   0x61200000
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
#define SPRD_IIS3_PHYS                                     0x71000000
#define SPRD_SIM0_PHYS                                     0x71100000
#define SPRD_APBREG_PHYS                                   0x71300000

/* referenced by sdio_cfg.c */
#define SPRD_EMMC_BASE                                     SPRD_EMMC_PHYS
#define SPRD_SDIO0_BASE                                    SPRD_SDIO0_PHYS
/* referenced by sprd_musb2_def.h */
#define SPRD_USB_BASE                                      SPRD_USB_OTG_PHYS
/* referenced by adi.c */
#define SPRD_MISC_PHYS                                     SPRD_ADI_PHYS
/* referenced by sprdfb_chip_9851.h */
#define SPRD_DSI_BASE                                      SPRD_DSI_PHYS
/* referenced by sprd_i2c.c, just tricky */
#define SPRD_I2C_BASE                                      SPRD_I2C0_PHYS
/* referenced by timer.c */
#define SPRD_APCPUTS0_BASE                                 SPRD_APCPUTS0_PHYS
/* referenced by timer_reg_r4p0.h */
#define SPRD_AON_TIMER_BASE                                SPRD_AON_TIMER_PHYS
/* referenced by pmic.h */
#define SPRD_ADISLAVE_BASE                                 SPRD_ADISLAVE_PHYS
/* referenced by sprd_bl.c */
#define CTL_BASE_PWM                                       SPRD_PWM_PHYS

#endif
