/*
 * Copyright (C) 2014-2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */

#ifndef _SC2723_REG_BASE_H_
#define _SC2723_REG_BASE_H_

#define ANA_PWM_BASE			(SPRD_MISC_PHYS + 0x8020)
#define ANA_WDG_BASE			(SPRD_MISC_PHYS + 0x8040)
#define ANA_RTC_BASE			(SPRD_MISC_PHYS + 0x8080)
#define ANA_EIC_BASE			(SPRD_MISC_PHYS + 0x8100)
#define ANA_PIN_BASE			(SPRD_MISC_PHYS + 0x8180)
#define ANA_EFS_BASE		        (SPRD_MISC_PHYS + 0x8200 )
#define ANA_THM_BASE			(SPRD_MISC_PHYS + 0x8280)
#define ADC_BASE			(SPRD_MISC_PHYS + 0x8300)
#define ANA_CTL_INT_BASE		(SPRD_MISC_PHYS + 0x8380)
#define ANA_BTLC_INT_BASE		(SPRD_MISC_PHYS + 0x83C0)
#define ANA_AUDIFA_INT_BASE		(SPRD_MISC_PHYS + 0x8400)
#define ANA_GPIO_INT_BASE		(SPRD_MISC_PHYS + 0x8480)
#define ANA_FPU_INT_BASE		(SPRD_MISC_PHYS + 0x8500)
#define ANA_AUDCFGA_INT_BASE	        (SPRD_MISC_PHYS + 0x8600)
#define ANA_HDT_INT_BASE		(SPRD_MISC_PHYS + 0x8700)

#define ANA_CTL_GLB_BASE		( SPRD_MISC_PHYS + 0x8800 )

#define SPRD_ANA_EIC_PHYS		ANA_EIC_BASE
#define SPRD_ANA_GPIO_PHYS		ANA_GPIO_INT_BASE
#define SPRD_ANA_FPU_PHYS		ANA_FPU_INT_BASE
#define ANA_FGU_BASE	ANA_FPU_INT_BASE

#define ANA_REGS_GLB_BASE	( ANA_CTL_GLB_BASE )

#endif

