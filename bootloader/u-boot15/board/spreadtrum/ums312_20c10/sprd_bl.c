#include <common.h>
#include <asm/arch/hardware.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>

#include "sc2703l_bllcd.h"

#define SC2703L_LCD_I2C_ADDRESS  0x4b
#define SC2703L_LCD_I2C_BUS  5

#define PWM_INDEX  2

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
	__raw_bits_or(((1 << PWM_INDEX) << 25), REG_AON_APB_APB_EB2); //PWMx EN

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

	i2c_set_bus_num(SC2703L_LCD_I2C_BUS);
	i2c_reg_write(SC2703L_LCD_I2C_ADDRESS, SC2703L_SYSCTRL_DISPLAY_ACTIVE, SC2703L_DISPLAY_EN_MASK);
	printf("SC2703L status is %d\n", \
			i2c_reg_read(SC2703L_LCD_I2C_ADDRESS, SC2703L_SYSCTRL_DISPLAY_STATUS));
	while(loop --);
}

void set_backlight(uint32_t brightness)
{
	u8 value;

	i2c_set_bus_num(SC2703L_LCD_I2C_BUS);

	value = SC2703L_IDAC_LINEAR_MASK
		| SC2703L_WLED_IDAC_EN_MASK
		| 0x2 << SC2703L_WLED_MODE_SHIFT
		| 0x1 << SC2703L_WLED_MODE_SHIFT;

	/* set WLED_MODE to duty-detect-analog-mode */
	i2c_reg_write(SC2703L_LCD_I2C_ADDRESS, SC2703L_WLED_CONFIG1, value);

	/* disable IDAC RAMP to avoid backlight flash when power on */
	value = i2c_reg_read(SC2703L_LCD_I2C_ADDRESS, SC2703L_WLED_CONFIG7);
	i2c_reg_write(SC2703L_LCD_I2C_ADDRESS, SC2703L_WLED_CONFIG7, value | SC2703L_IDAC_RAMP_DIS_MASK);

	/* set SEL_POC_LIMIT to 1.5A for WLED boost current limit */
	value = i2c_reg_read(SC2703L_LCD_I2C_ADDRESS, SC2703L_WLED_BOOST_CONTROL1);
	value |= 1 << SC2703L_SEL_POC_LIMIT_SHIFT;
	i2c_reg_write(SC2703L_LCD_I2C_ADDRESS, SC2703L_WLED_BOOST_CONTROL1, value);

	set_backlight_pwms(brightness);

	printf("read SC2703L_SYSCTRL_DISPLAY_STATUS = 0x%x\n",
		i2c_reg_read(SC2703L_LCD_I2C_ADDRESS, SC2703L_SYSCTRL_DISPLAY_STATUS));
}
