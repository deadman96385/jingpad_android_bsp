/*
 * Copyright (C) 2016 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */

#ifndef _SC2730_REG_BASE_H_
#define _SC2730_REG_BASE_H_

#define SPRD_ADISLAVE_BASE  SPRD_ADISLAVE_PHYS
#define ANA_TIMER_BASE		(SPRD_ADISLAVE_BASE + 0x00)
#define ANA_WDG_BASE		(SPRD_ADISLAVE_BASE + 0x40)
#define ANA_INTC_BASE		(SPRD_ADISLAVE_BASE + 0x80)
#define ANA_CAL_BASE		(SPRD_ADISLAVE_BASE + 0xC0)
#define ANA_AUD_BASE		(SPRD_ADISLAVE_BASE + 0x100)
#define ANA_BLTC_BASE		(SPRD_ADISLAVE_BASE + 0x180)
#define ANA_RTC_BASE		(SPRD_ADISLAVE_BASE + 0x200)
#define ANA_EIC_BASE		(SPRD_ADISLAVE_BASE + 0x280)
#define ANA_EFS_BASE		(SPRD_ADISLAVE_BASE + 0x300)
#define ANA_TYPEC_BASE		(SPRD_ADISLAVE_BASE + 0x380)
#define ANA_FSCHG_BASE		(SPRD_ADISLAVE_BASE + 0x400)
#define ANA_PIN_BASE		(SPRD_ADISLAVE_BASE + 0x480)
#define ANA_ADC_BASE		(SPRD_ADISLAVE_BASE + 0x500)
#define ANA_PTEST_BASE		(SPRD_ADISLAVE_BASE + 0x600)
#define ANA_FGU_BASE		(SPRD_ADISLAVE_BASE + 0xC00)
#define ANA_PD_BASE		(SPRD_ADISLAVE_BASE + 0xE00)
#define ANA_AUDANA_BASE		(SPRD_ADISLAVE_BASE + 0x1000)
#define ANA_REGS_GLB_BASE	(SPRD_ADISLAVE_BASE + 0x1800)

#endif

