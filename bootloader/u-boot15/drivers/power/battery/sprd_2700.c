
#include "sprd_chg_helper.h"
typedef unsigned char BYTE;
/******************************************************************************
* Register addresse
******************************************************************************/
#define SPRD2700_CONR_CTL				(0)
#define SPRD2700_STATER_CTL				(1)
#define SPRD2700_CHG_CUR_CTL			(2)
#define SPRD2700_CHG_VOL_CTL			(3)
#define SPRD2700_CHG_PROTR_CTL			(4)

/******************************************************************************
* Register bits
******************************************************************************/
#define CHG_EN_BIT						(0xff)
#define CHG_ENABLE_VAL					(0x00)
#define CHG_DISABLE_VAL					(0x01)
#define CHG_EN_SHIFT					(0x06)
#define TERMINA_CUR_BIT					(0x1f)
#define TERMINA_CUR_SHIFT				(0x05)
#define CHG_CUR_BIT						(0x0f)
#define CHG_CUR_SHIFT					(0x00)

/******************************************************************************
* I2c Configuration
******************************************************************************/

#define I2C_SPEED						(100000)
#define SLAVE_ADDR						(0x2d)

uint16_t sprd_2700_i2c_init(void)
{
	i2c_set_bus_num(CONFIG_SPRDCHG_I2C_BUS);
	i2c_init(I2C_SPEED, SLAVE_ADDR);
	return 0;
}

static int sprd_2700_write_reg(int reg, u8 val)
{
	i2c_reg_write(SLAVE_ADDR,reg,val);
	return 0;
}

int sprd_2700_read_reg(int reg, u8 *value)
{
	int ret;

	ret = i2c_reg_read(SLAVE_ADDR , reg);
	if (ret < 0) {
		debugf("%s reg(0x%x), ret(%d)\n", __func__, reg, ret);
		return ret;
	}

	ret &= 0xff;
	*value = ret;
	debugf("######sprd_2700readreg reg  = %d value =%d/%x\n",reg, ret, ret);
	return 0;
}

static void sprd_2700_set_value(BYTE reg, BYTE reg_bit,BYTE reg_shift, BYTE val)
{
	BYTE tmp;

	sprd_2700_read_reg(reg, &tmp);
	tmp = tmp & (~reg_bit) | (val << reg_shift);
	debugf("sprd_2700_set_value tmp =0x%x,val=0x%x\n",tmp,val);
	sprd_2700_write_reg(reg,tmp);
}

static BYTE sprd_2700_get_value(BYTE reg, BYTE reg_bit, BYTE reg_shift)
{
	BYTE data = 0;
	int ret = 0 ;

	ret = sprd_2700_read_reg(reg, &data);
	ret = (data & reg_bit) >> reg_shift;
	return ret;
}

void sprdchg_2700_start_chg(int value)
{
	sprd_2700_set_value(SPRD2700_CONR_CTL, CHG_EN_BIT,
		CHG_EN_SHIFT, CHG_ENABLE_VAL);
}

void sprdchg_2700_stop_chg(int value)
{
	debugf("stop charge\n");
	sprd_2700_set_value(SPRD2700_CONR_CTL, CHG_EN_BIT,
		CHG_EN_SHIFT, CHG_DISABLE_VAL);
}

void sprdchg_2700_ic_init(void)
{
	sprd_2700_i2c_init();
}

void sprd_2700_termina_cur_set(BYTE reg_val)
{
	sprd_2700_set_value(SPRD2700_CHG_CUR_CTL, TERMINA_CUR_BIT,
		TERMINA_CUR_SHIFT, reg_val);
}

void  sprdchg_2700_chg_current_termination(int termina_cur)
{

	debugf("sprdchg_2700_termina_cur_set cur =%d\n",termina_cur);
	unsigned char reg_val;

	if (termina_cur < 100)
		reg_val=0x00;
	else if (termina_cur >= 400)
		reg_val=0x07;
	else
		reg_val = (termina_cur - 50) / 50;
	sprd_2700_termina_cur_set(reg_val);
}

void sprdchg_2700_reset_timer(void)
{

}

 void sprd_2700_set_chg_current(int chg_cur)
{
	unsigned char reg_val;

	if (chg_cur > 100)
		reg_val = (chg_cur / 100) - 1;
	else
		reg_val = 0;
	sprd_2700_set_value(SPRD2700_CHG_CUR_CTL,CHG_CUR_BIT,
		CHG_CUR_SHIFT ,reg_val);
}

static int sprdchg_2700_cmd(enum sprdchg_cmd cmd,int value)
{
	switch (cmd) {
	case CHG_SET_CURRENT:
		sprd_2700_set_chg_current(value);
		break;
	default:
		break;
	}
	return 0;
}

static struct sprdchg_ic_operations sprd_extic_op = {
	.ic_init = sprdchg_2700_ic_init,
	.chg_start = sprdchg_2700_start_chg,
	.chg_stop = sprdchg_2700_stop_chg,
	.timer_callback = sprdchg_2700_reset_timer,
	.chg_cmd = sprdchg_2700_cmd,
};

void sprdchg_2700_init(void)
{
	BYTE data = 0;
	int i = 0;

	debugf("2700init\n");
	sprd_2700_i2c_init();

	/* identify device*/
	sprd_2700_read_reg(2, &data);

	if (data != 0x23) {
		printf("sc2700 is not found,not register ops!!!\n");
		return;
	}

	for(i = 0;  i < 5;  i++){
		sprd_2700_read_reg(i, &data);
		debugf("sprd_2700_ReadReg i = %d, data = %x\n",i,data);
	}

	printf("sc2700 register charge ops\n");
	sprdchg_register_ops(&sprd_extic_op);
}

