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
#define REG_AON_APB_APB_RTC_EB					REG_AON_APB_APB_RTC_EB0

/* referenced by gpio.c */
#define REG_GPIO_EB                             REG_AON_APB_APB_EB1
#define BIT_GPIO_EB                             BIT_AON_APB_GPIO_EB

/* referenced by eic.c */
#define REG_EIC_EB				REG_AON_APB_APB_EB2
#define BIT_EIC_EB                              BIT_AON_APB_EIC_EB
#define BIT_EIC_RTC_EB                          BIT_AON_APB_EIC_RTC_EB
#define BIT_EIC_RTCDV5_EB                       BIT_AON_APB_EIC_RTCDV5_EB
#define SPRD_EIC_PHYS				SPRD_AON_PERI_EIC_EXT2_PHYS
#define SPRD_EIC1_PHYS				SPRD_AON_PERI_EIC_EXT3_PHYS

/* bit redefinition for compatible */
#define BIT_EFUSE_EB                            BIT_AON_APB_EFUSE_EB
#define BIT_EFUSE_SOFT_RST                      BIT_AON_APB_EFUSE_SOFT_RST
/* there is no uart0 on sharkle, just tricky */
#define BIT_UART0_EB                            BIT_AP_APB_UART0_EB
#define BIT_UART1_EB                            BIT_AP_APB_UART0_EB
#define BIT_USB_EB                              BIT_AP_AHB_USB0_EB
#define BIT_OTG_SOFT_RST                        BIT_AP_AHB_OTG_SOFT_RST
#define BIT_OTG_UTMI_SOFT_RST                   BIT_AP_AHB_OTG_UTMI_SOFT_RST
#define BIT_OTG_PHY_SOFT_RST                    BIT_AP_AHB_OTG_PHY_SOFT_RST
#define BIT_I2C_EB                              BIT_AP_APB_I2C0_EB
#define BIT_ADI_EB                              BIT_AON_APB_ADI_EB
#define REG_ADI_EB				REG_AON_APB_APB_EB2

/* referenced by dwc3 */
#define	EVT_BUF_ADDR				0x28002A00

#endif
