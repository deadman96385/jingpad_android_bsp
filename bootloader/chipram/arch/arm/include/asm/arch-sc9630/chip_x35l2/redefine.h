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
#define BIT_EFUSE_EB                            BIT_AON_APB_EFUSE_EB

/* referenced by timer.c */
#define BIT_AON_TMR_26M_EB			BIT_AON_APB_TMR_EB

/* register redefiniton for compatible */
#define SPRD_AON_TIMER_PHYS    SPRD_GPTIMER0_PHYS

/* referemced by timer.c */
#define REG_AON_TMR_CLK_EN			REG_AON_APB_APB_EB0
#define REG_AON_TMR_CLK_RTC_EN			REG_AON_APB_APB_RTC_EB
#define REG_AON_TMR_26M_EN			REG_AON_APB_CLK_EB0
#endif
