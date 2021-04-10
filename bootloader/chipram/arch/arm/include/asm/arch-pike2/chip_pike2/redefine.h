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

/* referenced by efuse.c */
#define BIT_EFUSE_SOFT_RST                      BIT_AON_APB_EFUSE_SOFT_RST
#define BIT_EFUSE_EB                            BIT_AON_APB_EFUSE_NORMAL_EB

/* referenced by adi.c */
#define BIT_ADI_SOFT_RST                        BIT_AON_APB_ADI_SOFT_RST
#define BIT_ADI_EB                              BIT_AON_APB_ADI_EB
#define REG_ADI_EB				REG_AON_APB_APB_EB0
#define REG_ADI_RST				REG_AON_APB_APB_RST0

/* referenced by timer.c */
#define BIT_AON_TMR_26M_EB			BIT_AON_APB_TMR_EB

/* register redefiniton for compatible */

/* referenced by mmc_v40.c */
#define AON_SDIO0_CLK_2X_CFG                    0xBC
#define AON_EMMC_CLK_2X_CFG                     0xCC
#define AON_CLK_FREQ_26M                        (0x1)
#define AON_CLK_FREQ_384M       0X03

/* referemced by timer.c */
#define REG_AON_TMR_CLK_EN			REG_AON_APB_APB_EB0
#define REG_AON_TMR_CLK_RTC_EN			REG_AON_APB_APB_RTC_EB
#define REG_AON_TMR_26M_EN			REG_AON_APB_CLK_EB0

#endif
