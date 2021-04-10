/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <sci_types.h>
#include <timer.h>
#include <asm/arch/sprd_reg.h>

#define TIMER_CTL_BASE			SPRD_AON_TIMER_PHYS
#define SYSTIMER_BASE		SPRD_SYSCNT_PHYS

/* timer registers define */
#define TIMER0_BASE			(TIMER_CTL_BASE)
#define TM0_LOAD_LO			(TIMER0_BASE + 0x0000)
#define TM0_LOAD_HI			(TIMER0_BASE + 0x0004)
#define TM0_VALUE_LO			(TIMER0_BASE + 0x0008)
#define TM0_VALUE_HI			(TIMER0_BASE + 0x000C)
#define TM0_CTL				(TIMER0_BASE + 0x0010)
#define TM0_CLR				(TIMER0_BASE + 0x0014)
#define TM0_SHDW_LO			(TIMER0_BASE + 0x0018)
#define TM0_SHDW_HI			(TIMER0_BASE + 0x001C)

#define TIMER1_BASE			(TIMER_CTL_BASE + 0x0020)
#define TM1_LOAD_LO			(TIMER1_BASE + 0x0000)
#define TM1_LOAD_HI			(TIMER1_BASE + 0x0004)
#define TM1_VALUE_LO			(TIMER1_BASE + 0x0008)
#define TM1_VALUE_HI			(TIMER1_BASE + 0x000C)
#define TM1_CTL				(TIMER1_BASE + 0x0010)
#define TM1_CLR				(TIMER1_BASE + 0x0014)
#define TM1_SHDW_LO			(TIMER1_BASE + 0x0018)
#define TM1_SHDW_HI			(TIMER1_BASE + 0x001C)

#define TIMER2_BASE			(TIMER_CTL_BASE + 0x0040)
#define TM2_LOAD_LO			(TIMER2_BASE + 0x0000)
#define TM2_LOAD_HI			(TIMER2_BASE + 0x0004)
#define TM2_VALUE_LO			(TIMER2_BASE + 0x0008)
#define TM2_VALUE_HI			(TIMER2_BASE + 0x000C)
#define TM2_CTL				(TIMER2_BASE + 0x0010)
#define TM2_CLR				(TIMER2_BASE + 0x0014)
#define TM2_SHDW_LO			(TIMER2_BASE + 0x0018)
#define TM2_SHDW_HI			(TIMER2_BASE + 0x001C)

/* system timer registers define */
#define SYSTMR_ALM			(SYSTIMER_BASE + 0x0000)
#define SYSTMR_CNT0			(SYSTIMER_BASE + 0x0004)
#define SYSTMR_CTL			(SYSTIMER_BASE + 0x0008)
#define SYSTMR_SHDW			(SYSTIMER_BASE + 0x000C)

#define BIT_TIMER_RUN			(BIT(1))
#define BIT_TIMER_PERIOD		(BIT(0))
#define TMR0_CNT_VAL			(32)
#define TMR1_CNT_VAL			(32)
#define TMR2_CNT_VAL			(26)
#define TMR_CNT_MAX			0xFFFFFFFF

/* udelay: use timer2 to cnt, its tick is 38.461ns */
void udelay(uint32 us)
{
	CHIP_REG_SET(TM2_LOAD_LO, TMR2_CNT_VAL * us);
	CHIP_REG_SET(TM2_CTL, BIT_TIMER_RUN);
	while(CHIP_REG_GET(TM2_SHDW_LO));
	CHIP_REG_AND(TM2_CTL, ~BIT_TIMER_RUN);
}

/* mdelay: use timer0 to cnt, its tick is 30.517us */
void mdelay(uint32 ms)
{
	CHIP_REG_SET(TM0_LOAD_LO, TMR0_CNT_VAL * ms);
	CHIP_REG_SET(TM0_CTL, BIT_TIMER_RUN);
	while(CHIP_REG_GET(TM0_SHDW_LO));
	CHIP_REG_AND(TM0_CTL, ~BIT_TIMER_RUN);
}

uint32 sprd_get_syscnt(void)
{
	uint32 tick1, tick2;

	tick1 = CHIP_REG_GET(SYSTMR_SHDW);
	tick2 = CHIP_REG_GET(SYSTMR_SHDW);

	while (tick1 != tick2) {
		tick1 = tick2;
		tick2 = CHIP_REG_GET(SYSTMR_SHDW);
	}
	return tick1;
}

static void timer_enable(void)
{
	CHIP_REG_OR(REG_AON_TMR_CLK_EN,
		BIT_AON_APB_AON_SYST_EB |
		BIT_AON_APB_AP_SYST_EB |
		BIT_AON_APB_AON_TMR_EB);
	CHIP_REG_OR(REG_AON_TMR_CLK_RTC_EN,
		BIT_AON_APB_AON_SYST_RTC_EB |
		BIT_AON_APB_AP_SYST_RTC_EB |
		BIT_AON_APB_AON_TMR_RTC_EB);
	CHIP_REG_OR(REG_AON_TMR_26M_EN, BIT_AON_TMR_26M_EB);
}

void timer_init(void)
{
	timer_enable();
}
