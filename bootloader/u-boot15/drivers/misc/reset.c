/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Alex Zuepke <azu@sysgo.de>
 *
 * (C) Copyright 2002
 * Gary Jennejohn, DENX Software Engineering, <gj@denx.de>
 *
 * (C) Copyright 2009
 * Ilya Yanok, Emcraft Systems Ltd, <yanok@emcraft.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <asm/io.h>
#include <sprd_regulator.h>
#include <asm/arch/sprd_reg.h>
#include "sprd_wdt.h"

/*
 * Reset the cpu by setting up the watchdog timer and let it time out
 */

int (*arch_poweroff)(void) = NULL;

void reset_cpu (ulong ignored)
{
	start_watchdog(5);
	while (1) ;
}

void rtc_clean_all_int(void);
void power_down_cpu(ulong ignored)
{
	int v = 0;
	v = ANA_REG_GET(ANA_REG_GLB_POR_SRC_FLAG);
	printf("power on src = 0x%.8x\n", v);
	if(arch_poweroff)
	{
		arch_poweroff();
	}
	v = 0x1000000;
	while (v--); // log delay

	rtc_clean_all_int();
#if defined(CONFIG_ADIE_SC2723)
	sci_adi_set(ANA_REG_GLB_DCDC_SLP_CTRL0,  BIT_PWR_OFF_SEQ_EN); //auto poweroff by chip
#else
	sci_adi_write(ANA_REG_GLB_PWR_WR_PROT_VALUE,BITS_PWR_WR_PROT_VALUE(0x6e7F),BITS_PWR_WR_PROT_VALUE(~0));

	while (!(sci_adi_read(ANA_REG_GLB_PWR_WR_PROT_VALUE)&BIT_PWR_WR_PROT))printf("powerdown wait key\n");

	sci_adi_set(ANA_REG_GLB_POWER_PD_HW,  BIT_PWR_OFF_SEQ_EN); //auto poweroff by chip
#endif
	while(1);


}
