/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _SPRD_BATTERY_H_
#define _SPRD_BATTERY_H_

#define SPRDBAT_CHG_POLLING_T	200

enum sprd_adapter_type {
	ADP_TYPE_UNKNOW = 0,	//unknow adapter type
	ADP_TYPE_CDP = 1,	//Charging Downstream Port,USB&standard charger
	ADP_TYPE_DCP = 2,	//Dedicated Charging Port, standard charger
	ADP_TYPE_SDP = 4,	//Standard Downstream Port,USB and nonstandard charge
};

int sprdchg_charger_is_adapter(void);
uint16_t sprdbat_auxadc2vbatvol(uint16_t adcvalue);
uint32_t sprdbat_get_vbatauxadc_caltype(void);
void sprdbat_get_vbatauxadc_caldata(void);
int charger_connected(void);
int get_mode_from_gpio(void);
void sprdbat_init(void);
void sprdbat_lowbat_chg(void);
int sprdbat_is_battery_connected(void);
void sprdbat_show_chglogo(void);
void sprdbat_chg_led(int on);
uint32_t sprdbat_get_aux_vbatvol(void);
void sprdchg_common_cfg(void);
uint32_t sprdfgu_read_vbat_vol(void);

/* ext chg ic init function*/
void sprdchg_fan54015_init(void);
void sprdchg_bq25896_init(void);
void sprdchg_2700_init(void);
void sprdchg_2701_init(void);
void sprdchg_2705_init(void);
void sprdchg_2703_init(void);
void sprdchg_2731_init(void);
void sprdchg_2721_init(void);
void sprdchg_2723_init(void);
void sprdchg_2720_init(void);


#endif

