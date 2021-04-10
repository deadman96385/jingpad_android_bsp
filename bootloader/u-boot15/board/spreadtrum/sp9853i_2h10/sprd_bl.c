#include <common.h>
#include <asm/arch/hardware.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>

#include "sc2705_bllcd.h"

//#####################
enum {
	SC2705_WLED_BYPASS = 0,
	SC2705_WLED_DIRECT = 1,
	SC2705_WLED_DUTY_DET_PWM = 2,
	SC2705_WLED_DUTY_DET_ANALOG = 3,
	SC2705_WLED_DUTY_DET_MIXED = 4,
	SC2705_WLED_MODE_MAX,
};

#define SC2705_LCD_I2C_ADDRESS	0x48
#define SC2705_LCD_I2C_BUS	3
#define SC2705_WLED_IDAC_MAX 2047
#define MAX_BRIGHTNESS 255

//###########
void set_backlight(uint32_t brightness)
{

	int value;
	int pwm_out_duty = 0x80;
	brightness = (brightness * SC2705_WLED_IDAC_MAX)/MAX_BRIGHTNESS;

	i2c_set_bus_num(SC2705_LCD_I2C_BUS);
	value = (SC2705_WLED_DIRECT << SC2705_WLED_MODE_SHIFT)
		| SC2705_WLED_STR1_EN_MASK
		| SC2705_WLED_STR2_EN_MASK;
	/* direct mode */
	i2c_reg_write(SC2705_LCD_I2C_ADDRESS, SC2705_WLED_CONFIG1, value);

	i2c_reg_write(SC2705_LCD_I2C_ADDRESS, SC2705_WLED_CONFIG7, pwm_out_duty);

	value = (brightness >> 8) & 0x7;
	i2c_reg_write(SC2705_LCD_I2C_ADDRESS, SC2705_WLED_CONFIG2, SC2705_IDAC_LINEAR_MASK | value);

	value = brightness & 0xFF;
	i2c_reg_write(SC2705_LCD_I2C_ADDRESS, SC2705_WLED_CONFIG3, value);

	value = i2c_reg_read(SC2705_LCD_I2C_ADDRESS, SC2705_SUPPLY_ACTIVE);
	if(brightness > 0)
		value |= SC2705_WLED_EN_MASK;
	else
		value &= ~SC2705_WLED_EN_MASK;
	i2c_reg_write(SC2705_LCD_I2C_ADDRESS, SC2705_SUPPLY_ACTIVE, value);
	value = i2c_reg_read(SC2705_LCD_I2C_ADDRESS, SC2705_SUPPLY_STATUS);
	printf("read SC2705_SUPPLY_STATUS = 0x%x brightness:%d\n", value,brightness);
}
