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
#define WLED_CE_2705		(25)
#define SC2705_LCD_I2C_ADDRESS	0x48
#define SC2705_LCD_I2C_BUS	3

//###########
void set_backlight(uint32_t brightness)
{
	int value;
	int wled_idac = 1666;

	sprd_gpio_request(NULL, WLED_CE_2705);
	sprd_gpio_direction_output(NULL, WLED_CE_2705, brightness > 0? 1: 0);

	i2c_set_bus_num(SC2705_LCD_I2C_BUS);
	value = (SC2705_WLED_DIRECT << SC2705_WLED_MODE_SHIFT)
		| SC2705_WLED_STR1_EN_MASK
		| SC2705_WLED_STR2_EN_MASK;
	/* by-pass mode */
	i2c_reg_write(SC2705_LCD_I2C_ADDRESS, SC2705_WLED_CONFIG1, value);

	value = SC2705_WLED_EN_MASK | SC2705_DISPLAY_EN_MASK;
	value = brightness > 0? value: 0;
	i2c_reg_write(SC2705_LCD_I2C_ADDRESS, SC2705_SUPPLY_ACTIVE, value);
	value = i2c_reg_read(SC2705_LCD_I2C_ADDRESS, SC2705_SUPPLY_STATUS);
	/* wled-idac */
	value = (wled_idac >> 8);
	i2c_reg_write(SC2705_LCD_I2C_ADDRESS, SC2705_WLED_CONFIG2, value);
	value = (wled_idac & 0xFF);
	i2c_reg_write(SC2705_LCD_I2C_ADDRESS, SC2705_WLED_CONFIG3, value);

	/*set brightness*/
	value = (brightness >> 1) & 0x7f;
	i2c_reg_write(SC2705_LCD_I2C_ADDRESS, SC2705_WLED_CONFIG7, value);
	printf("read SC2705_SUPPLY_STATUS = 0x%x\n", SC2705_SUPPLY_STATUS);
}
