
#include "sprd_chg_helper.h"

typedef unsigned char BYTE;

/* Fault */
#define CHG_WATCHDOG_FAULT			(1)
#define BOOST_FAULT				(1)
#define INPUT_FAULT				(1)
#define CHG_SAFETY_TIMER_EXPIRE			(3)
#define CHG_VBAT_FAULT				(1)
#define CHG_COLD_FALUT				(5)
#define CHG_HOT_FALUT				(6)

/* Register definition */
#define REG00	(0)
#define REG01	(1)
#define REG02	(2)
#define REG03	(3)
#define REG04	(4)
#define REG05	(5)
#define REG06	(6)
#define REG07	(7)
#define REG08	(8)
#define REG09	(9)
#define REG0A	(10)
#define REG0B	(11)
#define REG0C	(12)
#define REG0D	(13)
#define REG0E	(14)
#define REG0F	(15)
#define REG10	(16)
#define REG11	(17)
#define REG12	(18)
#define REG13	(19)
#define REG14	(20)

/* BITS for REG00 */
#define EN_HIZ_BIT					(0x80)
#define EN_ILIM_BIT					(0x40)
#define IINLIM_BIT					(0x3f)
/* BITS for REG01 */
#define BHOT_BIT					(0xc0)
#define BCOLD_BIT					(0x20)
#define VINDPM_OS_BIT					(0x1f)
/* BITS for REG02 */
#define CONV_START_BIT					(0x80)
#define CONV_RATE_BIT				(0x40)
#define BOOST_FREQ_BIT				(0x20)
#define ICO_EN_BIT				(0x10)
#define FORCE_DPDM_BIT				(0x02)
#define AUTO_DPDM_EN_BIT			(0x01)
/* BITS for REG03 */
#define BAT_LOADEN_BIT			(0x80)
#define WD_RST_BIT				(0x40)
#define OTG_CONFIG_BIT				(0x20)
#define CHG_CONFIG_BIT			(0x10)
#define SYS_MIN_BIT			(0x0E)
#define MIN_VBAT_SEL_BIT		(0x01)
/* BITS for REG04 */
#define EN_PUMPX_BIT		(0x80)
#define ICHG_BIT			(0x7F)
/* BITS for REG05 */
#define IPRECHG_BIT		(0xF0)
#define ITERM_BIT			(0x0F)
/* BITS for REG06 */
#define VREG_BIT		(0xFC)
#define BATLOWV_BIT			(0x02)
#define VRECHG_BIT			(0x01)
/* BITS for REG07 */
#define EN_TERM_BIT		(0x80)
#define STAT_DS_BIT			(0x40)
#define WATCHDOG_BIT			(0x30)
#define EN_TIMER_BIT				(0X08)
#define CHG_TIMER_BIT				(0x06)
#define JEITA_ISET_BIT			(0x01)
/* BITS for REG08 TODO */
/* BITS for REG09  */
#define BATFET_DIS_BIT			(0x20)
/* BITS for REG0A TODO */
/* BITS for REG0B */
#define VBUS_STAT_BIT			(0xe0)
#define CHRG_STAT_BIT			(0x18)
#define PG_STAT_BIT				(0x04)
#define VSYS_STAT_BIT					(0x01)
/* BITS for REG0C */
#define WATCHDOG_FAULT_BIT					(0x80)
#define BOOST_FAULT_BIT					(0x40)
#define CHRG_FAULT_BIT					(0x3F)
#define BAT_FAULT_BIT					(0x08)
#define NTC_FAULT_BIT					(0x07)
/* BITS for REG0D TODO */
/* BITS for REG0E TODO */
/* BITS for REG0F TODO */
/* BITS for REG10 TODO */
/* BITS for REG11 TODO */
/* BITS for REG12 TODO */
/* BITS for REG13 */
#define VDPM_STAT_BIT					(0x80)
#define IDPM_STAT_BIT					(0x40)
#define IDPM_LIM_BIT					(0x3F)
/* BITS for REG14 */
#define REG_RST_BIT					(0x80)

/* SHIFT for REG00 */
#define EN_HIZ_SHIFT					(0x07)
#define EN_ILIM_SHIFT					(0x06)
#define IINLIM_SHIFT					(0x00)
/* SHIFT for REG01 */
#define BHOT_SHIFT					(0x06)
#define BCOLD_SHIFT					(0x05)
#define VINDPM_OS_SHIFT					(0x00)
/* SHIFT for REG02 */
#define CONV_START_SHIFT					(0x07)
#define CONV_RATE_SHIFT				(0x06)
#define BOOST_FREQ_SHIFT				(0x05)
#define ICO_EN_SHIFT				(0x04)
#define FORCE_DPDM_SHIFT				(0x01)
#define AUTO_DPDM_EN_SHIFT			(0x00)
/* SHIFT for REG03 */
#define BAT_LOADEN_SHIFT			(0x07)
#define WD_RST_SHIFT				(0x06)
#define OTG_CONFIG_SHIFT				(0x05)
#define CHG_CONFIG_SHIFT			(0x04)
#define SYS_MIN_SHIFT			(0x01)
#define MIN_VBAT_SEL_SHIFT		(0x00)
/* SHIFT for REG04 */
#define EN_PUMPX_SHIFT		(0x07)
#define ICHG_SHIFT			(0x00)
/* SHIFT for REG05 */
#define IPRECHG_SHIFT		(0x04)
#define ITERM_SHIFT			(0x00)
/* SHIFT for REG06 */
#define VREG_SHIFT		(0x02)
#define BATLOWV_SHIFT			(0x01)
#define VRECHG_SHIFT			(0x00)
/* SHIFT for REG07 */
#define EN_TERM_SHIFT		(0x07)
#define STAT_DS_SHIFT			(0x06)
#define WATCHDOG_SHIFT			(0x04)
#define EN_TIMER_SHIFT				(0X03)
#define CHG_TIMER_SHIFT				(0x01)
#define JEITA_ISET_SHIFT			(0x00)
/* SHIFT for REG08 TODO */
/* SHIFT for REG09  */
#define BATFET_DIS_SHIFT			(0x05)
/* SHIFT for REG0A TODO */
/* SHIFT for REG0B */
#define VBUS_STAT_SHIFT			(0x05)
#define CHRG_STAT_SHIFT			(0x03)
#define PG_STAT_SHIFT				(0x02)
#define VSYS_STAT_SHIFT					(0x00)
/* SHIFT for REG0C */
#define WATCHDOG_FAULT_SHIFT					(0x07)
#define BOOST_FAULT_SHIFT					(0x06)
#define CHRG_FAULT_SHIFT					(0x04)
#define BAT_FAULT_SHIFT					(0x03)
#define NTC_FAULT_SHIFT					(0x00)
/* SHIFT for REG0D TODO */
/* SHIFT for REG0E TODO */
/* SHIFT for REG0F TODO */
/* SHIFT for REG10 TODO */
/* SHIFT for REG11 TODO */
/* SHIFT for REG12 TODO */
/* SHIFT for REG13 */
#define VDPM_STAT_SHIFT					(0x07)
#define IDPM_STAT_SHIFT					(0x06)
#define IDPM_LIM_SHIFT					(0x00)
/* SHIFT for REG14 */
#define REG_RST_SHIFT					(0x07)

#define CHG_DISABLE_VAL			(0x00)
#define CHG_ENABLE_VAL			(0x01)
#define CHG_BAT_VAL				(0x01)
#define CHG_OTG_VAL				(0x01)

#define I2C_SPEED			(100000)
#define SLAVE_ADDR 		(0x6b)

uint16_t bq25896_i2c_init(void)
{
	i2c_set_bus_num(CONFIG_SPRDCHG_I2C_BUS);
	i2c_init(I2C_SPEED, SLAVE_ADDR);
	return 0;
}
static int bq25896_write_reg(int reg, u8 val)
{
	i2c_reg_write(SLAVE_ADDR,reg,val);
   	return 0;
}

int bq25896_read_reg(int reg, u8 *value)
{
	int ret;
	ret = i2c_reg_read(SLAVE_ADDR , reg);
	if (ret < 0) {
		printf("%s reg(0x%x), ret(%d)\n", __func__, reg, ret);
		return ret;
	}

	ret &= 0xff;
	*value = ret;
	printf("######bq25896readreg reg  = %d value =%d/%x\n",reg, ret, ret);
	return 0;
}

static void bq25896_set_value(BYTE reg, BYTE reg_bit,BYTE reg_shift, BYTE val)
{
	BYTE tmp;
	bq25896_read_reg(reg, &tmp);
	tmp = tmp & (~reg_bit) |(val << reg_shift);
	printf("bq25896_set_value tmp =0x%x,val=0x%x\n",tmp,val);
	bq25896_write_reg(reg,tmp);
}

static BYTE bq25896_get_value(BYTE reg, BYTE reg_bit, BYTE reg_shift)
{
	BYTE data = 0;
	int ret = 0 ;
	ret = bq25896_read_reg(reg, &data);
	ret = (data & reg_bit) >> reg_shift;

	return ret;
}
void bq25896_limit_usb_cur()
{
	bq25896_set_value(REG00, IINLIM_BIT, IINLIM_SHIFT, 0x08);
}
void bq25896_usb_start_charging(void)
{
	//bq25896_set_value(INPUT_SRC_CTL,IN_CUR_LIMIT_BIT ,IN_CUR_LIMIT_SHIFT ,1 );
	bq25896_set_value(REG04, ICHG_BIT, ICHG_SHIFT, 0x08);
}

void bq25896_ta_start_charging(void)
{
	bq25896_set_value(REG04, ICHG_BIT, ICHG_SHIFT, 0x10);
}

void chg_bq25896_start_chg(int type)
{
	printf("chg_bq25896_start_chg\n type=%d\n",type);
	bq25896_set_value(REG03, CHG_CONFIG_BIT , CHG_CONFIG_SHIFT, CHG_ENABLE_VAL);
	if(type == ADP_TYPE_CDP || type == ADP_TYPE_DCP){
		printf("charge start with AC\n");
		bq25896_set_value(REG00,
				    IINLIM_BIT, IINLIM_SHIFT, 0X3F);
		bq25896_ta_start_charging();
	}else{
		printf("charge start with USB\n");
		bq25896_usb_start_charging();
	}
}
 void chg_bq25896_stop_charging(int value)
{	
	printf("stop charge\n");
	if (value) {
		bq25896_set_value(REG03, CHG_CONFIG_BIT , CHG_CONFIG_SHIFT, CHG_DISABLE_VAL);
	} else {
		bq25896_set_value(REG03, CHG_CONFIG_BIT , CHG_CONFIG_SHIFT, CHG_DISABLE_VAL);
		bq25896_set_value(REG00, EN_HIZ_BIT, EN_HIZ_SHIFT, 1);
	}
}
void  bq25896_sw_reset(void)
{
	printf("chg_bq25896_sw_reset");
	bq25896_set_value(REG14, REG_RST_BIT, REG_RST_SHIFT, 1);
}

void chg_bq25896_init(void)
{
	BYTE data = 0;
	int i = 0;

	printf("bq25896init\n");
	bq25896_i2c_init();
	bq25896_sw_reset();
	for(i = 0;  i <= 0x14;  i++){
		bq25896_read_reg(i, &data);
		printf("bq25896_ReadReg i = %d, data = %x\n",i,data);
	}

	bq25896_set_value(REG07, WATCHDOG_BIT,WATCHDOG_SHIFT,0); // disable whatchdog 
	bq25896_set_value(REG07, EN_TERM_BIT, EN_TERM_SHIFT,0); //disable chg termina
	bq25896_set_value(REG07, EN_TIMER_BIT, EN_TIMER_SHIFT,0); //disable safety timer
}

void chg_bq25896_reset_timer(void)
{
	printf("bq25896 reset rimer\n");
}

void chg_bq25896_set_chg_current_limit(uint32_t limit)
{
	/* max limit is 3.25A, min is 100mA  */
	if (limit > 3250)
		limit = 3250;
	else if (limit < 100)
		limit = 100;

	limit -= 100;

	bq25896_set_value(REG00, IINLIM_BIT, IINLIM_SHIFT, limit / 50);
}

void chg_bq25896_set_chg_cur(unsigned int cur)
{
	unsigned char reg_val = 0;

	if (cur > 3008)
		cur = 3008;
	reg_val = (cur >> 6);

	bq25896_set_value(REG04, ICHG_BIT, ICHG_SHIFT, reg_val);
}

static int chg_bq25896_cmd(enum sprdchg_cmd cmd,int value)
{
	switch (cmd) {
	case CHG_SET_CURRENT:
		chg_bq25896_set_chg_cur(value);
		break;
	case CHG_SET_LIMIT_CURRENT:
		chg_bq25896_set_chg_current_limit(value);
		break;
	default:
		break;
	}

	return 0;
}

struct sprdchg_ic_operations sprd_extic_op ={
	.ic_init = chg_bq25896_init,
	.chg_start = chg_bq25896_start_chg,
	.chg_stop = chg_bq25896_stop_charging,
	.timer_callback = chg_bq25896_reset_timer,
	.chg_cmd = chg_bq25896_cmd,
};

void sprdchg_bq25896_init(void)
{
	sprdchg_register_ops(&sprd_extic_op);
}