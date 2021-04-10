/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _REDEFINE_H
#define _REDEFINE_H

/* macro definition for compatible */

/* referenced by mmc_v40.c */
#define AON_CLK_FREQ_26M                        (0x1)
#define AON_CLK_FREQ_384M       0X02
#define BIT_AON_APB_EFUSE_NORMAL_EB		BIT_AON_APB_EFUSE_EB
/* bit redefinition for compatible */

/* referenced by efuse.c */
#define BIT_EFUSE_SOFT_RST                      BIT_AON_APB_EFUSE_SOFT_RST
#define BIT_EFUSE_EB                            BIT_AON_APB_EFUSE_NORMAL_EB

/* referenced by adi.c */
#define BIT_ADI_SOFT_RST                        BIT_AON_APB_ADI_SOFT_RST
#define BIT_ADI_EB                              BIT_AON_APB_ADI_EB
#define REG_ADI_EB				REG_AON_APB_APB_EB2

/* referenced by mmc_v40.c */
#define BIT_AP_AHB_EMMC_EB			BIT_AP_APB_EMMC_EB
#define BIT_AP_AHB_EMMC_SOFT_RST		BIT_AP_APB_EMMC_SOFT_RST
#define BIT_AP_AHB_SDIO0_EB			BIT_AP_APB_SDIO0_EB
#define BIT_AP_AHB_SDIO0_SOFT_RST		BIT_AP_APB_SDIO0_SOFT_RST

/* referenced by aon_apb.h */
#define REG_AON_APB_APB_RTC_EB			REG_AON_APB_APB_RTC_EB0

/* referenced by timer.c */
#define BIT_AON_APB_TMR_EB			BIT_AON_APB_AON_TMR_EB

/* referenced by gpio.c */
#define REG_GPIO_EB                             REG_AON_APB_APB_EB1
#define BIT_GPIO_EB                             BIT_AON_APB_GPIO_EB

/* referenced by eic.c */
#define REG_EIC_EB                              REG_AON_APB_APB_EB2
#define BIT_EIC_EB                              BIT_AON_APB_EIC_EB
#define BIT_EIC_RTC_EB                          BIT_AON_APB_EIC_RTC_EB
#define BIT_EIC_RTCDV5_EB                       BIT_AON_APB_EIC_RTCDV5_EB
#define SPRD_EIC_PHYS                           SPRD_AON_EIC_EXT2_PHYS
#define SPRD_EIC1_PHYS                          SPRD_AON_EIC_EXT3_PHYS

/* referenced by serial_sprd.c */
#define BIT_UART0_EB                            BIT_AP_APB_UART0_EB
#define BIT_UART1_EB                            BIT_AP_APB_UART1_EB

/* referenced by sprd_musb2_driver.c */
#define BIT_USB_EB                              BIT_AON_APB_OTG_UTMI_EB

/* referenced by sharkl5_usb_phy.c */

/* referenced by ums510_haps.c */
#define REG_PMU_APB_PD_GPU_TOP_CFG		REG_PMU_APB_PD_GPU_TOP_CFG0

/* register redefiniton for compatible */

/* referenced by mmc_v40.c */
#define AON_SDIO0_CLK_2X_CFG                    0x80
#define AON_EMMC_CLK_2X_CFG                     0x90

/* for ce */
#define REG_AP_CLK_CORE_CGM_CE_CFG              ( CTL_BASE_AP_CLK_CORE + 0x0068 )
#define REG_AP_AHB_CE_SEC_EB                    REG_AP_APB_APB_EB
#define BIT_AP_AHB_CE_SEC_EB                    BIT_AP_APB_CE_SEC_EB
#define REG_AP_AHB_CE_SEC_SOFT_RST              REG_AP_APB_APB_RST
#define BIT_AP_AHB_CE_SEC_SOFT_RST              BIT_AP_APB_CE_SEC_SOFT_RST


#endif
