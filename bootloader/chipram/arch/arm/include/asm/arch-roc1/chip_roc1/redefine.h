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
#define AP_CLK_FREO_26M          (0x1)
#define AP_CLK_FREQ_384M         0x03

#define BIT_AON_APB_EFUSE_NORMAL_EB		BIT_AON_APB_EFUSE_EB
/* bit redefinition for compatible */

/* referenced by efuse.c */
#define BIT_EFUSE_SOFT_RST                      BIT_AON_APB_EFUSE_SOFT_RST
#define BIT_EFUSE_EB                            BIT_AON_APB_EFUSE_NORMAL_EB

/* referenced by adi.c */
#define BIT_ADI_SOFT_RST                        BIT_AON_APB_ADI_SOFT_RST
#define BIT_ADI_EB                              BIT_AON_APB_ADI_EB
#define REG_ADI_EB				REG_AON_APB_APB_EB2
#define REG_ADI_RST				REG_AON_APB_APB_RST2

/* referenced by mmc_v40.c */
#define BIT_AP_AHB_EMMC_EB			BIT_AP_APB_EMMC_EB
#define BIT_AP_AHB_EMMC_SOFT_RST		BIT_AP_APB_EMMC_SOFT_RST
#define BIT_AP_AHB_SDIO0_EB			BIT_AP_APB_SDIO0_EB
#define BIT_AP_AHB_SDIO0_SOFT_RST		BIT_AP_APB_SDIO0_SOFT_RST

/* referenced by timer.c */
#define BIT_AON_TMR_26M_EB			BIT_AON_APB_CGM_TMR_EN

/* referenced by aon_apb.h */
#define REG_AON_APB_APB_RTC_EB			REG_AON_APB_APB_RTC_EB0

/* register redefiniton for compatible */

/* referenced by mmc_v40.c */
#define AP_SDIO0_CLK_2X_CFG                    0x70
#define AP_EMMC_CLK_2X_CFG                     0x80

/* referemced by timer.c */
#define REG_AON_TMR_CLK_EN			REG_AON_APB_APB_EB1
#define REG_AON_TMR_CLK_RTC_EN			REG_AON_APB_APB_RTC_EB0
#define REG_AON_TMR_26M_EN			REG_AON_APB_CGM_REG1

/* for ce */
#define REG_AP_CLK_CORE_CGM_CE_CFG		SPRD_APCLK_PHYS + 0x0068
#define REG_AP_AHB_CE_SEC_EB			REG_AP_APB_APB_EB
#define REG_AP_AHB_CE_SEC_SOFT_RST		REG_AP_APB_APB_RST
#define BIT_AP_AHB_CE_SEC_EB			BIT_AP_APB_CE_SEC_EB
#define BIT_AP_AHB_CE_SEC_SOFT_RST		BIT_AP_APB_CE_SEC_SOFT_RST
#define BIT_AP_AHB_CE_PUB_SOFT_RST		BIT_AP_APB_CE_PUB_SOFT_RST

#endif
