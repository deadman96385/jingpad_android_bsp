/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */

#ifndef _SC2731_REG_BASE_H_
#define _SC2731_REG_BASE_H_

#define ANA_SWICHG_BASE		(SPRD_ADISLAVE_BASE + 0x00 )
#define ANA_TIMER_BASE		(SPRD_ADISLAVE_BASE + 0x40 )
#define ANA_FSCHG_BASE		(SPRD_ADISLAVE_BASE + 0x60 )
#define ANA_WDG_BASE		(SPRD_ADISLAVE_BASE + 0x80 )
#define ANA_CHGWDG_BASE		(SPRD_ADISLAVE_BASE + 0xC0 )
#define ANA_TYPEC_BASE		(SPRD_ADISLAVE_BASE + 0x100 )
#define ANA_INTC_BASE	(SPRD_ADISLAVE_BASE + 0x140 )
#define ANA_CAL_BASE	(SPRD_ADISLAVE_BASE + 0x180 )
#define ANA_AUDIFA_BASE	(SPRD_ADISLAVE_BASE + 0x1C0 )
#define ANA_BLTC_BASE	(SPRD_ADISLAVE_BASE + 0x200 )
#define ANA_FLASH_BASE	(SPRD_ADISLAVE_BASE + 0x240 )
#define ANA_RTC_BASE		(SPRD_ADISLAVE_BASE + 0x280 )
#define ANA_EIC_BASE		(SPRD_ADISLAVE_BASE + 0x300 )
#define ANA_EFS_BASE		(SPRD_ADISLAVE_BASE + 0x380 )
#define ANA_THM_BASE		(SPRD_ADISLAVE_BASE + 0x400 )
#define ANA_ADC_BASE		(SPRD_ADISLAVE_BASE + 0x480 )
#define ANA_PIN_BASE		(SPRD_ADISLAVE_BASE + 0x600 )
#define ANA_AUDCFGA_BASE	(SPRD_ADISLAVE_BASE + 0x700 )
#define ANA_AUDDIG_BASE	(SPRD_ADISLAVE_BASE + 0x800 )
#define ANA_BIF_BASE	(SPRD_ADISLAVE_BASE + 0x900 )
#define ANA_FGU_BASE	(SPRD_ADISLAVE_BASE + 0xA00 )
#define ANA_REGS_GLB_BASE	(SPRD_ADISLAVE_BASE + 0xC00)


#define ANA_GPIO_INT_BASE      (SPRD_ADISLAVE_BASE + 0x480 )  //TODO2731 and 2723 need to remove

#define SPRD_ANA_EIC_PHYS		ANA_EIC_BASE
#define SPRD_ANA_GPIO_PHYS      ANA_GPIO_INT_BASE	//TODO2731 and 2723 need to remove  2731 and 2723 do not have gpio module
#define ADC_BASE 			ANA_ADC_BASE

#endif

