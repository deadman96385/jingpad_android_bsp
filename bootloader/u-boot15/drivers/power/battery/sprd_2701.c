
#include "sprd_chg_helper.h"

typedef unsigned char BYTE;

#define CHG_TIME_OUT					(3)
#define IN_DETECT_FAIL				(1)
#define CHG_COLD_FALUT				(1)
#define CHG_HOT_FALUT				(2)
#define CHG_VBAT_FAULT				(1)
#define CHG_WHATCHDOG_FAULT		(1)
#define CHG_SYS_FAULT				(1)

#define INPUT_SRC_CTL	(0)
#define POWER_ON_CTL	(1)
#define CHG_CUR_CTL		(2)
#define TRICK_CHG_CTL	(3)
#define CHG_VOL_CTL		(4)
#define TIMER_CTL		(5)
#define LED_DRV_CTL		(6)
#define LED_CUR_REF_CTL	(7)
#define MISC_CTL			(8)
#define SYS_STATUS_REG	(9)
#define FAULT_REG		(10)

#define VIN_DPM_BIT					(0x78)
#define SW_RESET_BIT					(0x80)
#define TMR_RST_BIT					(0x40)
#define CHG_CUR_BIT					(0xfc)
#define CHG_EN_BIT					(0x30)
#define IN_VOL_LIMIT_BIT				(0x78)
#define IN_CUR_LIMIT_BIT				(0x07)
#define MIN_SYS_VOL_BIT 				(0x0e)
#define PRE_CHG_CUR_BIT				(0xf0)
#define TERMINA_CUR_BIT				(0x0f)
#define CHG_VOL_LIMIT_BIT			(0xfc)
#define PRE_CHG_VOL_BIT				(0x02)
#define RECHG_VOL_BIT				(0x01)
#define CHG_TERMINA_EN_BIT			(0x80)
#define WATCH_DOG_TIMER_BIT			(0x60)
#define CHG_SAFE_TIMER_EN_BIT		(0x10)
#define CHG_SAFE_TIMER_BIT			(0x0c)
#define OTG_CUR_LIMIT_BIT			(0x04)
#define LED_MODE_CTL_BIT				(0x06)
#define FLASH_MODE_CUR_BIT			(0x0f)
#define TORCH_MODE_CUR_BIT			(0xf0)
#define JEITA_ENABLE_BIT				(0x01)
#define VIN_STAT_BIT					(0xc0)
#define CHG_STAT_BIT					(0x30)
//fault reg bit
#define SYS_FAULT_BIT					(0x01)
#define NTC_FAULT_BIT				(0x03)
#define BAT_FAULT_BIT				(0x08)
#define CHG_FAULT_BIT				(0x30)
#define WHATCH_DOG_FAULT_BIT		(0x40)
#define LED_FAULT_BIT				(0x80)

#define VIN_DPM_SHIFT				(0x03)
#define SW_RESET_SHIFT				(0x07)
#define TMR_RST_SHIFT				(0x06)
#define CHG_CUR_SHIFT				(0x02)
#define CHG_EN_SHIFT					(0x04)
#define IN_VOL_LIMIT_SHIFT			(0x03)
#define IN_CUR_LIMIT_SHIFT			(0x00)
#define MIN_SYS_VOL_SHIFT			(0x01)
#define PRE_CHG_CUR_SHIFT			(0x04)
#define TERMINA_CUR_SHIFT			(0x00)
#define CHG_VOL_LIMIT_SHIFT			(0x02)
#define PRE_CHG_VOL_SHIFT			(0x01)
#define RECHG_VOL_SHIFT				(0x00)
#define CHG_TERMINA_EN_SHIFT		(0x07)
#define WATCH_DOG_TIMER_SHIFT		(0x05)
#define CHG_SAFE_TIMER_EN_SHIFT		(0x04)
#define CHG_SAFE_TIMER_SHIFT			(0x02)
#define OTG_CUR_LIMIT_SHIFT			(0x02)
#define LED_MODE_CTL_SHIFT			(0x01)
#define FLASH_MODE_CUR_SHIFT		(0x00)
#define TORCH_MODE_CUR_SHIFT		(0x04)
#define JEITA_ENABLE_SHIFT			(0x00)
#define VIN_STAT_SHIFT				(0x06)
#define CHG_STAT_SHIFT				(0x04)
//fault reg shift
#define SYS_FAULT_SHIFT				(0x00)
#define NTC_FAULT_SHIFT				(0x01)
#define BAT_FAULT_SHIFT				(0x03)
#define CHG_FAULT_SHIFT				(0x04)
#define WHATCH_DOG_FAULT_SHIFT		(0x06)
#define LED_FAULT_SHIFT				(0x07)



#define CHG_CUR_TA_VAL			(0x10)
#define CHG_CUR_USB_VAL			(0x00)
#define CHG_DISABLE_VAL			(0x03)
#define CHG_BAT_VAL				(0x01)
#define CHG_OTG_VAL				(0x02)
#define CHG_OFF_RBF_VAL			(0x03)
#define LED_FLASH_EN_VAL			(0x02)
#define LED_TORCH_EN_VAL		(0x01)


#define I2C_SPEED			(100000)
#define SLAVE_ADDR 		(0x6b)

uint16_t sprd_2701_i2c_init(void)
{
	i2c_set_bus_num(CONFIG_SPRDCHG_I2C_BUS);
	i2c_init(I2C_SPEED, SLAVE_ADDR);
	return 0;
}
static int sprd_2701_write_reg(int reg, u8 val)
{
	i2c_reg_write(SLAVE_ADDR,reg,val);
   	return 0;
}

int sprd_2701_read_reg(int reg, u8 *value)
{
	int ret;
	ret = i2c_reg_read(SLAVE_ADDR , reg);
	if (ret < 0) {
		debugf("%s reg(0x%x), ret(%d)\n", __func__, reg, ret);
		return ret;
	}

	ret &= 0xff;
	*value = ret;
	debugf("######sprd_2701readreg reg  = %d value =%d/%x\n",reg, ret, ret);
	return 0;
}

static void sprd_2701_set_value(BYTE reg, BYTE reg_bit,BYTE reg_shift, BYTE val)
{
	BYTE tmp;
	sprd_2701_read_reg(reg, &tmp);
	tmp = tmp & (~reg_bit) |(val << reg_shift);
	debugf("sprd_2701_set_value tmp =0x%x,val=0x%x\n",tmp,val);
	sprd_2701_write_reg(reg,tmp);
}

static BYTE sprd_2701_get_value(BYTE reg, BYTE reg_bit, BYTE reg_shift)
{
	BYTE data = 0;
	int ret = 0 ;
	ret = sprd_2701_read_reg(reg, &data);
	ret = (data & reg_bit) >> reg_shift;

	return ret;
}
void sprd_2701_limit_usb_cur()
{
	sprd_2701_set_value(INPUT_SRC_CTL,IN_CUR_LIMIT_BIT ,IN_CUR_LIMIT_SHIFT ,1 );
}
void sprd_2701_usb_start_charging(void)
{
	//sprd_2701_set_value(INPUT_SRC_CTL,IN_CUR_LIMIT_BIT ,IN_CUR_LIMIT_SHIFT ,1 );
	sprd_2701_set_value(CHG_CUR_CTL,CHG_CUR_BIT ,CHG_CUR_SHIFT , CHG_CUR_USB_VAL);
}

void sprd_2701_ta_start_charging(void)
{
	sprd_2701_set_value(CHG_CUR_CTL,CHG_CUR_BIT ,CHG_CUR_SHIFT , CHG_CUR_TA_VAL);
}

void sprdchg_2701_start_chg(int value)
{
	sprd_2701_set_value(POWER_ON_CTL, CHG_EN_BIT , CHG_EN_SHIFT, 1);
}

void sprdchg_2701_stop_charging(int value)
{
	debugf("stop charge\n");
	if (value) {
		/* disable BATFET */
		sprd_2701_set_value(POWER_ON_CTL, CHG_EN_BIT , CHG_EN_SHIFT, 0x0);
	} else {
		sprd_2701_set_value(TIMER_CTL, WATCH_DOG_TIMER_BIT,WATCH_DOG_TIMER_SHIFT, 0x00);
		sprd_2701_set_value(POWER_ON_CTL, CHG_EN_BIT , CHG_EN_SHIFT, CHG_DISABLE_VAL);
	}
}

static void sprdchg_2701_chg_current_limit(uint32_t cur)
{
	unsigned char reg_val;

	if (cur <= 300)
		reg_val = 0;
	else if (cur <= 500)
		reg_val = 1;
	else if (cur <= 900)
		reg_val = 2;
	else if (cur <= 1200)
		reg_val = 3;
	else if (cur <= 1500)
		reg_val = 4;
	else if (cur <= 2000)
		reg_val = 5;
	else if (cur <= 3000)
		reg_val = 6;
	else
		reg_val = 7;
	sprd_2701_set_value(INPUT_SRC_CTL,
		IN_CUR_LIMIT_BIT, IN_CUR_LIMIT_SHIFT, reg_val);
}

static void sprdchg_2701_set_chg_cur(unsigned int cur)
{
	unsigned char reg_val = 0;

	if (cur < 512)
		cur = 512;
	reg_val = (cur - 512) >> 6;

	sprd_2701_set_value(CHG_CUR_CTL, CHG_CUR_BIT, CHG_CUR_SHIFT, reg_val);
}

void  sprd_2701_sw_reset(void)
{
	debugf("sprdchg_2701_sw_reset");
	sprd_2701_set_value(POWER_ON_CTL, SW_RESET_BIT, SW_RESET_SHIFT, 1);
}

void sprdchg_2701_ic_init(void)
{
	BYTE data = 0;
	int i = 0;

	debugf("2701init\n");
	sprd_2701_i2c_init();
	sprd_2701_sw_reset();
	for(i = 0;  i < 11;  i++){
		sprd_2701_read_reg(i, &data);
		debugf("sprd_2701_ReadReg i = %d, data = %x\n",i,data);
	}

	sprd_2701_set_value(TIMER_CTL,WATCH_DOG_TIMER_BIT,WATCH_DOG_TIMER_SHIFT,0x01);
	//sprd_2701_set_value(MISC_CTL,JEITA_ENABLE_BIT,JEITA_ENABLE_SHIFT,1);//enable jeita
	//sprd_2701_set_value(TIMER_CTL,CHG_TERMINA_EN_BIT,CHG_TERMINA_EN_SHIFT,0); //disable chg termina
	sprd_2701_set_value(TIMER_CTL,CHG_SAFE_TIMER_EN_BIT,CHG_SAFE_TIMER_EN_SHIFT,0); //disable safety timer
}

void sprdchg_2701_reset_timer(void)
{
	debugf("2701 reset timer\n");
	sprd_2701_set_value(TIMER_CTL, WATCH_DOG_TIMER_BIT,
		WATCH_DOG_TIMER_SHIFT, 0x01);
	sprd_2701_set_value(POWER_ON_CTL, TMR_RST_BIT,
		TMR_RST_SHIFT, 0x01);
}

static int sprdchg_2701_cmd(enum sprdchg_cmd cmd,int value)
{
	switch (cmd) {
	case CHG_SET_CURRENT:
		sprdchg_2701_set_chg_cur(value);
		break;
	case CHG_SET_LIMIT_CURRENT:
		sprdchg_2701_chg_current_limit(value);
		break;
	default:
		break;
	}

	return 0;
}

struct sprdchg_ic_operations sprd_extic_op ={
	.ic_init = sprdchg_2701_ic_init,
	.chg_start = sprdchg_2701_start_chg,
	.chg_stop = sprdchg_2701_stop_charging,
	.timer_callback = sprdchg_2701_reset_timer,
	.chg_cmd = sprdchg_2701_cmd,
};

void sprdchg_2701_init(void)
{
	sprdchg_register_ops(&sprd_extic_op);
}

