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

/* bit redefinition for compatible */
#define BIT_EFUSE_EB                            BIT_AON_APB_EFUSE_EB
#define BIT_AON_APB_EFUSE_NORMAL_EB             BIT_AON_APB_EFUSE_EB
#define BIT_EFUSE_SOFT_RST                      BIT_AON_APB_EFUSE_SOFT_RST
#define BIT_GPIO_EB                             BIT_AON_APB_GPIO_EB
#define BIT_EIC_EB                              BIT_AON_APB_EIC_EB
#define BIT_EIC_RTC_EB                          BIT_AON_APB_EIC_RTC_EB
#define BIT_EIC_RTCDV5_EB                       BIT_AON_APB_EIC_RTCDV5_EB

/* there is no uart0 on sharkle, just tricky */
#define BIT_UART0_EB                            BIT_AP_APB_UART1_EB
#define BIT_UART1_EB                            BIT_AP_APB_UART1_EB
#define BIT_USB_EB                              BIT_AP_AHB_OTG_EB
#define BIT_OTG_SOFT_RST                        BIT_AP_AHB_OTG_SOFT_RST
#define BIT_OTG_UTMI_SOFT_RST                   BIT_AP_AHB_OTG_UTMI_SOFT_RST
#define BIT_OTG_PHY_SOFT_RST                    BIT(6)
#define BIT_I2C_EB                              BIT_AP_APB_I2C0_EB
#define BIT_ADI_EB                              BIT_AON_APB_ADI_EB
#define REG_ADI_EB				REG_AON_APB_APB_EB0

/* for CE */
#define REG_AP_AHB_CE_SEC_EB                                           REG_AP_AHB_AHB_EB
#define BIT_AP_AHB_CE_SEC_EB                                           BIT_AP_AHB_CE_EB
#define REG_AP_AHB_CE_SEC_SOFT_RST                                     REG_AP_AHB_AHB_RST

#endif
