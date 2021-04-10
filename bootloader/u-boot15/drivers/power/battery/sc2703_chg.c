/*
 * Copyright (C) 2017-2018 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */

#include "sprd_chg_helper.h"
#include "sc2703_chg_registers.h"
#include <asm/arch/sprd_reg.h>

#define SC2703_CHG_B_IMIN		500000
#define SC2703_CHG_B_ISTEP		50000
#define SC2703_CHG_B_IMAX		3500000
#define SC2703_CHG_B_VMIN		3800000
#define SC2703_CHG_B_VSTEP		20000
#define SC2703_CHG_B_VMAX		4800000
#define SC2703_VIN_DROP_MIN		4300000
#define SC2703_VIN_DROP_STEP		50000
#define SC2703_VIN_DROP_MAX		12000000
#define SC2703_CHGV_MAX			13500000

#define I2C_SPEED			100000
#define SLAVE_ADDR			0x4c
#define I2C_DATA_MASK			0xff

static u32 iin_lim_tbl[] = {
	100000,
	150000,
	500000,
	900000,
	1500000,
	2000000,
	2500000,
	3000000,
};

static u32 sc2703_i2c_init(void)
{
	i2c_set_bus_num(CONFIG_SPRDCHG_I2C_BUS);
	i2c_init(I2C_SPEED, SLAVE_ADDR);
	return 0;
}
static int sc2703_write_reg(u8 reg, u8 val)
{
	i2c_reg_write(SLAVE_ADDR, reg, val);
	return 0;
}

static int sc2703_read_reg(u8 reg, u8 *value)
{
	int ret;

	ret = i2c_reg_read(SLAVE_ADDR, reg);
	if (ret < 0) {
		debugf("%s reg(0x%x), ret(%d)\n", __func__, reg, ret);
		return ret;
	}

	*value = ret & I2C_DATA_MASK;
	debugf("sc2703_read_reg reg = %d value =%d/%x\n",reg, ret, ret);
	return 0;
}

static int sc2703_update_reg_bits(u8 reg, u8 mask, u8 val)
{
	u8 tmp;

	sc2703_read_reg(reg, &tmp);
	tmp &= ~mask;
	tmp |= val & mask;
	debugf("sc2703_update_reg_bits tmp =0x%x, val=0x%x, mask=0x%x\n",
		tmp, val, mask);
	sc2703_write_reg(reg, tmp);
	return 0;
}

static void sc2703_charger_ic_init(void)
{
	/* disable watchdog */
	sc2703_update_reg_bits(SC2703_CONF_A,
				 SC2703_WD_EN_MASK,
				 0);
	sc2703_update_reg_bits(SC2703_REG_UNLOCK,
		SC2703_CHG_REG_MASK_ALL, SC2703_REG_UNLOCK_VAL);
	sc2703_update_reg_bits(SC2703_VSYS_UV_SWITCH,
		SC2703_CHG_REG_MASK_ALL, SC2703_VSYS_UV_SWITCH_VAL);
	sc2703_update_reg_bits(SC2703_REG_UNLOCK,
		SC2703_CHG_REG_MASK_ALL, SC2703_CHG_REG_DISABLE_VAL);

	/* Set flash voltage output 4.8v */
	sc2703_update_reg_bits(SC2703_DCDC_CTRL_F,
		SC2703_DCDC_REV_VOUT_MASK, 0);
}

/*
 * There is an issue in factory production line. for entering factory mode,
 * we can't limit the operation sequence, which means firstly power supply
 * VBAT then plug in USB cable or firstly plug in USB cable then power supply VBAT,
 * both should be ok.but now if firstly plug in USB cable,
 * software will detect the battery absence and disable buck, VSYS drops then quickly
 * goes back to higher than PMIC's UVLO, so we disable buck force mandatory.
 * we expect VSYS falls to 0V and system in shutdown mode, until vbat supplied,
 * system starts boot up to entering factory mode.
 */
static void sc2703_charger_start(void)
{
	sc2703_update_reg_bits(SC2703_DCDC_CTRL_A, SC2703_CHG_EN_MASK | SC2703_DCDC_EN_MASK, SC2703_CHG_EN_MASK | SC2703_DCDC_EN_MASK);
	sc2703_update_reg_bits(SC2703_REG_UNLOCK,
		SC2703_CHG_REG_MASK_ALL, SC2703_REG_UNLOCK_VAL);
	sc2703_update_reg_bits(SC2703_VSYS_UV_SWITCH,
		SC2703_CHG_REG_MASK_ALL, SC2703_VSYS_UV_SWITCH_VAL);
	sc2703_update_reg_bits(SC2703_CHG_BUCK_SWITCH,
		SC2703_CHG_REG_MASK_ALL, SC2703_CHG_REG_DISABLE_VAL);
	sc2703_update_reg_bits(SC2703_REG_UNLOCK,
		SC2703_CHG_REG_MASK_ALL, SC2703_CHG_REG_DISABLE_VAL);
}

static void sc2703_charger_stop(unsigned int flag)
{
	if (!sprdbat_is_battery_connected()) {
		sc2703_update_reg_bits(SC2703_DCDC_CTRL_A, SC2703_CHG_EN_MASK, 0);
		sc2703_update_reg_bits(SC2703_REG_UNLOCK,
			SC2703_CHG_REG_MASK_ALL, SC2703_REG_UNLOCK_VAL);
		sc2703_update_reg_bits(SC2703_VSYS_UV_SWITCH,
			SC2703_CHG_REG_MASK_ALL, SC2703_VSYS_UV_SWITCH_VAL);
		sc2703_update_reg_bits(SC2703_CHG_BUCK_SWITCH,
			SC2703_CHG_REG_MASK_ALL, SC2703_CHG_BUCK_SWITCH_VAL);
		sc2703_update_reg_bits(SC2703_REG_UNLOCK,
			SC2703_CHG_REG_MASK_ALL, SC2703_CHG_REG_DISABLE_VAL);
	} else {
		sc2703_update_reg_bits(SC2703_DCDC_CTRL_A, SC2703_CHG_EN_MASK, 0);
	}
}

static void sc2703_charger_cc_current_set(int val)
{
	u8 reg;

	/* mA to uA */
	val *= 1000;

	if (val < SC2703_CHG_B_IMIN)
		val = SC2703_CHG_B_IMIN;
	else if (val > SC2703_CHG_B_IMAX)
		val = SC2703_CHG_B_IMAX;

	reg = (val - SC2703_CHG_B_IMIN) / SC2703_CHG_B_ISTEP;

	debugf("%s,reg:%d\n", __func__, reg);
	sc2703_update_reg_bits(SC2703_CHG_CTRL_B, SC2703_IBAT_CHG_MASK,
			reg << SC2703_IBAT_CHG_SHIFT);
}

static void sc2703_charger_input_current_set(int val)
{
	u8 iin_lim0;
	int i;

	val *= 1000;
	for (i = 1; i < ARRAY_SIZE(iin_lim_tbl); ++i)
		if (val < iin_lim_tbl[i])
			break;
	/* When the val is less than the judgment value,
	 * so to set last judgment cur value.
	 */
	iin_lim0 = i - 1;
	debugf("%s,iin_lim0:%d\n",__func__, iin_lim0);
	sc2703_update_reg_bits(SC2703_DCDC_CTRL_D,
				  SC2703_IIN_LIM0_MASK | SC2703_IIN_LIM1_MASK,
				  iin_lim0 | iin_lim0 << SC2703_IIN_LIM1_SHIFT);
}

static void sprdchg_2703_reset_timer(void)
{
	debugf("2703 reset timer\n");
}

static void sprdchg_2703_stop_charging(int flag)
{
	debugf("%s,flag:%d\n",__func__, flag);
	sc2703_charger_stop(flag);
}

static void sprdchg_2703_set_chg_cur(int cur)
{
	debugf("%s,cur:%d\n",__func__, cur);
	sc2703_charger_cc_current_set(cur);
}

static void sprdchg_2703_chgr_cur_limit(int limit)
{
	debugf("%s,limit:%d\n",__func__, limit);
	sc2703_charger_input_current_set(limit);
}

static void sc2703_clr_event(void)
{
	sc2703_write_reg(SC2703_EVENT_A, SC2703_EVENT_CLR_MASK);
	sc2703_write_reg(SC2703_EVENT_B, SC2703_EVENT_CLR_MASK);
	sc2703_write_reg(SC2703_EVENT_C,
			 SC2703_EVENT_CLR_MASK & (~SC2703_E_ADC_DONE_MASK));
	sc2703_write_reg(SC2703_EVENT_D, SC2703_EVENT_CLR_MASK);
	sc2703_write_reg(SC2703_EVENT_E, SC2703_EVENT_CLR_MASK);
}

static void sprdchg_2703_enable_chg(void)
{
	sc2703_clr_event();
	sc2703_charger_start();
}

static void sprdchg_2703_chip_init(void)
{
	debugf("%s\n",__func__);
	sc2703_i2c_init();
	sc2703_charger_ic_init();
}

static int sc2703_cmd(enum sprdchg_cmd cmd, int value)
{
	switch (cmd) {
	case CHG_SET_CURRENT:
		sprdchg_2703_set_chg_cur(value);
		break;
	case CHG_SET_LIMIT_CURRENT:
		sprdchg_2703_chgr_cur_limit(value);
		break;
	default:
		break;
	}

	return 0;
}

static struct sprdchg_ic_operations sprd_extic_op ={
	.ic_init = sprdchg_2703_chip_init,
	.chg_start = sprdchg_2703_enable_chg,
	.chg_stop = sprdchg_2703_stop_charging,
	.timer_callback = sprdchg_2703_reset_timer,
	.chg_cmd = sc2703_cmd,
};

void sprdchg_2703_init(void)
{
	sprdchg_register_ops(&sprd_extic_op);
}

