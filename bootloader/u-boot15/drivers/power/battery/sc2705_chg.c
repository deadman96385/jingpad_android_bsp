/*
 * Copyright (C) 2016-2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */

#include "sprd_chg_helper.h"
#include "sc2705_chg_registers.h"
#include <asm/arch/sprd_reg.h>

#define SC2705_CHG_B_IMIN		500000
#define SC2705_CHG_B_ISTEP		50000
#define SC2705_CHG_B_IMAX		3500000
#define SC2705_CHG_B_VMIN		3800000
#define SC2705_CHG_B_VSTEP		20000
#define SC2705_CHG_B_VMAX		4800000
#define SC2705_VIN_DROP_MIN		4300000
#define SC2705_VIN_DROP_STEP	50000
#define SC2705_VIN_DROP_MAX		12000000
#define SC2705_CHGV_MAX		13500000

#define I2C_SPEED			(100000)
#define SLAVE_ADDR 		(0x49)

typedef unsigned char u8;

static unsigned int iin_lim_tbl[] = {
	100000,
	150000,
	500000,
	900000,
	1500000,
	2000000,
	2500000,
	3000000,
};

static uint16_t sc2705_i2c_init(void)
{
	i2c_set_bus_num(CONFIG_SPRDCHG_I2C_BUS);
	i2c_init(I2C_SPEED, SLAVE_ADDR);
	return 0;
}
static int sc2705_write_reg(int reg, u8 val)
{
	i2c_reg_write(SLAVE_ADDR,reg,val);
	return 0;
}

static int sc2705_read_reg(int reg, u8 *value)
{
	int ret;
	ret = i2c_reg_read(SLAVE_ADDR , reg);
	if (ret < 0) {
		debugf("%s reg(0x%x), ret(%d)\n", __func__, reg, ret);
		return ret;
	}

	ret &= 0xff;
	*value = ret;
	debugf("sc2705_read_reg reg = %d value =%d/%x\n",reg, ret, ret);
	return 0;
}

static int sc2705_update_reg_bits(unsigned int reg,
		       unsigned int mask, unsigned int val)
{
	int ret;
	u8 tmp;

	sc2705_read_reg(reg, &tmp);
	tmp = tmp & (~mask) |(val & mask);
	debugf("sc2705_update_reg_bits tmp =0x%x,val=0x%x,mask=0x%x\n",
		tmp, val, mask);
	sc2705_write_reg(reg,tmp);
	return ret;
}

static void sc2705_charger_ic_init(void)
{
	/* disable watchdog */
	sc2705_update_reg_bits(SC2705_CONF_A,
				 SC2705_WD_EN_MASK,
				 0);
}

static void sc2705_charger_start(void)
{
	sc2705_update_reg_bits(SC2705_DCDC_CTRL_A,
				  SC2705_CHG_EN_MASK|SC2705_DCDC_EN_MASK,
				  SC2705_CHG_EN_MASK|SC2705_DCDC_EN_MASK);
}

static void sc2705_charger_stop(unsigned int flag)
{
	sc2705_update_reg_bits(SC2705_DCDC_CTRL_A,
				SC2705_CHG_EN_MASK|SC2705_DCDC_EN_MASK,
				0);
}

static void sc2705_charger_cc_current_set(unsigned int val)
{
	u8 reg = 0;

	/* mA to uA */
	val *= 1000;

	if (val < SC2705_CHG_B_IMIN)
		val = SC2705_CHG_B_IMIN;

	if (val > SC2705_CHG_B_IMAX)
		val = SC2705_CHG_B_IMAX;

	reg = (val - SC2705_CHG_B_IMIN) / SC2705_CHG_B_ISTEP;

	debugf("%s,reg:%d\n",__func__, reg);
	sc2705_update_reg_bits(SC2705_CHG_CTRL_B, SC2705_IBAT_CHG_MASK,
			(reg << SC2705_IBAT_CHG_SHIFT));
}

static void sc2705_charger_input_current_set(unsigned int val)
{
	unsigned int iin_lim0;
	int i;

	val *= 1000;
	for (i = 1; i < ARRAY_SIZE(iin_lim_tbl); ++i)
		if (val < iin_lim_tbl[i])
			break;
	iin_lim0 = i - 1;
	debugf("%s,iin_lim0:%d\n",__func__, iin_lim0);
	sc2705_update_reg_bits(SC2705_DCDC_CTRL_D,
				  SC2705_IIN_LIM0_MASK | SC2705_IIN_LIM1_MASK,
				  iin_lim0 | iin_lim0 << SC2705_IIN_LIM1_SHIFT);
}

static void sprdchg_2705_reset_timer(void)
{
	/* TODO */
	debugf("2705 reset timer\n");
}

static void sprdchg_2705_stop_charging(unsigned int flag)
{
	debugf("%s,flag:%d\n",__func__, flag);
	sc2705_charger_stop(flag);
}

static void sprdchg_2705_set_chg_cur(unsigned int cur)
{
	debugf("%s,cur:%d\n",__func__, cur);
	sc2705_charger_cc_current_set(cur);
}

static void sprdchg_2705_chgr_cur_limit(unsigned int limit)
{
	debugf("%s,limit:%d\n",__func__, limit);
	sc2705_charger_input_current_set(limit);
}

static void sprdchg_2705_enable_chg(void)
{
	sc2705_charger_start();
}

static void sprdchg_2705_chip_init(void)
{
	debugf("%s\n",__func__);
	sc2705_i2c_init();
	sc2705_charger_ic_init();
	sci_adi_write(ANA_REG_GLB_MIXED_CTRL0, BITS_OVLO_V(0x1) | BITS_OVLO_T(0x3),
		BITS_OVLO_V(0x3) | BITS_OVLO_T(0x3));
}

static int sc2705_cmd(enum sprdchg_cmd cmd,int value)
{
	switch (cmd) {
	case CHG_SET_CURRENT:
		sprdchg_2705_set_chg_cur(value);
		break;
	case CHG_SET_LIMIT_CURRENT:
		sprdchg_2705_chgr_cur_limit(value);
		break;
	default:
		break;
	}

	return 0;
}

static struct sprdchg_ic_operations sprd_extic_op ={
	.ic_init = sprdchg_2705_chip_init,
	.chg_start = sprdchg_2705_enable_chg,
	.chg_stop = sprdchg_2705_stop_charging,
	.timer_callback = sprdchg_2705_reset_timer,
	.chg_cmd = sc2705_cmd,
};

void sprdchg_2705_init(void)
{
	sprdchg_register_ops(&sprd_extic_op);
}

