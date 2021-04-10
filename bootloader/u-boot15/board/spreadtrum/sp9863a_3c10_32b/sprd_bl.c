#include <common.h>
#include <asm/arch/hardware.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>

#include "sc2703_bllcd.h"

enum {
	SC2703_WLED_BYPASS = 0,
	SC2703_WLED_DIRECT = 1,
	SC2703_WLED_DUTY_DET_PWM = 2,
	SC2703_WLED_DUTY_DET_ANALOG = 3,
	SC2703_WLED_DUTY_DET_MIXED = 4,
	SC2703_WLED_EXT_R_SINK = 5,
	SC2703_WLED_MODE_MAX,
};

/*       SC2703 I2C Register Address Space                      */
/* Reg_Addr_Range    Device_ID    Reg_Block                     */
/*  0x0000 ~ 0x00FF    0x48        Display Virtual/OTP Register */
/*  0x0100 ~ 0x01FF    0x49        CoreBuck                     */
/*  0x0200 ~ 0x02FF    0x4A        Flash Driver                 */
/*  0x0300 ~ 0x03FF    0x4B        Display/Wled/...             */
/*  0x0400 ~ 0x04FF    0x4C        Charger                      */
#define SC2703_OTP_I2C_ADDRESS	0x48
#define SC2703_LCD_I2C_ADDRESS	0x4b
#define SC2703_LCD_I2C_BUS 	7
#define SC2703_WLED_IDAC_MAX 2047
#define MAX_BRIGHTNESS 255

#define PWM_INDEX  1

/*r3p0*/

#define PWM_PRESCALE	(0x0000)
#define PWM_MOD		(0x0004)
#define PWM_DUTY		(0x0008)
#define PWM_DIV			(0x000c)
#define PWM_PAT_LOW	(0x0010)
#define PWM_PAT_HIGH	(0x0014)
#define PWM_ENABLE 	(0x0018)
#define PWM_VERSION	(0x001c)

#define PWM2_SCALE		0x3
#define PWM_MOD_MAX 0xff
#define PWM_REG_MSK 0xffff

static inline uint32_t pwm_read(int index, uint32_t reg)
{
	return __raw_readl(CTL_BASE_PWM + index * 0x20 + reg);
}

static void pwm_write(int index, uint32_t value, uint32_t reg)
{
	__raw_writel(value, CTL_BASE_PWM + index * 0x20 + reg);
}

static void __raw_bits_or(unsigned int v, unsigned int a)
{
	__raw_writel((__raw_readl(a) | v), a);
}

void set_backlight_pwms(uint32_t brightness)
{

	int index = PWM_INDEX;

	__raw_bits_or((0x1 << 0), REG_AON_CLK_CORE_CGM_PWM0_CFG + index * 4);//ext_26m select
	__raw_bits_or(((1 << PWM_INDEX) << 4), REG_AON_APB_APB_EB0); //PWMx EN


	if (0 == brightness) {
		pwm_write(index, 0, PWM_ENABLE);
		printf("sprd backlight power off. pwm_index=%d  brightness=%d\n", index, brightness);
	} else {
		pwm_write(index, PWM2_SCALE, PWM_PRESCALE);
		pwm_write(index, PWM_MOD_MAX, PWM_MOD);
		pwm_write(index,  brightness, PWM_DUTY);

		pwm_write(index, PWM_REG_MSK, PWM_PAT_LOW);
		pwm_write(index, PWM_REG_MSK, PWM_PAT_HIGH);
		pwm_write(index, 1, PWM_ENABLE);
		printf("sprd backlight power on. pwm_index=%d  brightness=%d\n", index, brightness);
	}
}

/* sc2703 power on */
void lcd_use_sc2703l_to_power_on(void)
{
	int loop = 100;
	uint8_t scval = 0;

	i2c_set_bus_num(SC2703_LCD_I2C_BUS);

	/* Workaround as the clamp is still in place */
	i2c_reg_write(SC2703_OTP_I2C_ADDRESS, SC2703_OTP_HIDE_0069, 0x30);
	i2c_reg_write(SC2703_OTP_I2C_ADDRESS, SC2703_OTP_HIDE_0069, 0x70);
	i2c_reg_write(SC2703_OTP_I2C_ADDRESS, SC2703_OTP_HIDE_0069, 0x35);
	i2c_reg_write(SC2703_OTP_I2C_ADDRESS, SC2703_OTP_HIDE_0069, 0x34);
	scval = i2c_reg_read(SC2703_LCD_I2C_ADDRESS, SC2703_DISPLAY_HIDE_035A);
	i2c_reg_write(SC2703_LCD_I2C_ADDRESS, SC2703_DISPLAY_HIDE_035A, (scval & 0xEF));
	i2c_reg_write(SC2703_OTP_I2C_ADDRESS, SC2703_OTP_HIDE_0069, 0x00);

	i2c_reg_write(SC2703_LCD_I2C_ADDRESS, SC2703_SYSCTRL_DISPLAY_ACTIVE, SC2703_DISPLAY_EN_MASK);
	printf("SC2703 status is %d\n", \
			i2c_reg_read(SC2703_LCD_I2C_ADDRESS, SC2703_SYSCTRL_DISPLAY_STATUS));
	while(loop --);
}

void set_backlight(uint32_t brightness)
{

	/* set WLED_MODE to duty-detect-analog-mode */
	i2c_reg_write(SC2703_LCD_I2C_ADDRESS, SC2703_WLED_CONFIG1, 0x1b);

	/* disable IDAC RAMP to avoid backlight flash when power on */
	i2c_reg_write(SC2703_LCD_I2C_ADDRESS, SC2703_WLED_CONFIG7, 0x73);

	/* set SEL_POC_LIMIT to 1.5A for WLED boost current limit */
	i2c_reg_write(SC2703_LCD_I2C_ADDRESS, SC2703_WLED_BOOST_CONTROL1, 0x01);

	set_backlight_pwms(brightness);

	printf("read SC2703_SYSCTRL_DISPLAY_STATUS = 0x%x\n",
		i2c_reg_read(SC2703_LCD_I2C_ADDRESS, SC2703_SYSCTRL_DISPLAY_STATUS));
}
