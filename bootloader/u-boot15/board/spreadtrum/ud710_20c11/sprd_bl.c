#include <common.h>
#include <asm/arch/hardware.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>

#include "sc2703_bllcd.h"
#include <i2c.h>

#define SC2703_LCD_I2C_ADDRESS	0x4b
#define SC2703_LCD_I2C_BUS 	6

#define I2C_SPEED	100000
#define BL_POWER_I2C_ADDRESS          0x36
#define BL_POWER_MODE_ADDRESS         0x02
#define BL_CURRENT_RATIO_LSB_ADDRESS         0x04
#define BL_CURRENT_RATIO_MSB_ADDRESS          0x05
#define BL_POWER_PWM_ADDRESS         		 0x06
#define BL_POWER_TURNON_RAMP_ADDRESS          0x07

#define LCD_POWER_I2C_ADDRESS          0x3E
#define LCD_POWER_VPOS_ADDRESS         0x00
#define LCD_POWER_VNEG_ADDRESS         0x01
#define LCD_POWER_DIS_ADDRESS          0x03
#define LCD_POWER_CTL_ADDRESS          0xFF
/* sc2703 power on */
void lcd_use_sc2703l_to_power_on(void)
{
	int loop = 100;

	i2c_set_bus_num(SC2703_LCD_I2C_BUS);
	/* set lcd power on -avdd/avee +5.6/-5.6 ... */
	i2c_reg_write(SC2703_LCD_I2C_ADDRESS, SC2703_DISPLAY_BOOST_VOLTAGE, 0x74);
	i2c_reg_write(SC2703_LCD_I2C_ADDRESS, SC2703_DISPLAY_LDO_VOLTAGE, 0x6f);
        i2c_reg_write(SC2703_LCD_I2C_ADDRESS, SC2703_DISPLAY_CP_VOLTAGE, 0x6f);
	i2c_reg_write(SC2703_LCD_I2C_ADDRESS, SC2703_SYSCTRL_DISPLAY_ACTIVE, SC2703_DISPLAY_EN_MASK);
	printf("SC2703 status is %d\n", \
			i2c_reg_read(SC2703_LCD_I2C_ADDRESS, SC2703_SYSCTRL_DISPLAY_STATUS));
	while(loop --);
}


void set_backlight(uint32_t brightness)
{
	uint8_t temp=0;
	uint8_t val =0;

	temp &= ~0x07;
	temp |= brightness & 0x07;

	sprd_gpio_request(NULL, CONFIG_LCM_GPIO_BL_EN);
	sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_BL_EN, 1);
	mdelay(40);

	i2c_set_bus_num(3);
	i2c_init(I2C_SPEED, BL_POWER_I2C_ADDRESS);

	temp &= ~0x07;
	temp |= brightness & 0x07;
	i2c_reg_write(BL_POWER_I2C_ADDRESS, BL_CURRENT_RATIO_LSB_ADDRESS, 0x07);
	val = i2c_reg_read(BL_POWER_I2C_ADDRESS, BL_CURRENT_RATIO_LSB_ADDRESS);
	temp=0;
	temp &= ~0xff;
	temp |= brightness & 0xff;
	i2c_reg_write(BL_POWER_I2C_ADDRESS, BL_CURRENT_RATIO_MSB_ADDRESS, 0xff);
	val = i2c_reg_read(BL_POWER_I2C_ADDRESS, BL_CURRENT_RATIO_MSB_ADDRESS);
	i2c_reg_write(BL_POWER_I2C_ADDRESS, BL_POWER_PWM_ADDRESS, 0x5B);
	if (brightness > 0) {
		i2c_reg_write(BL_POWER_I2C_ADDRESS, BL_POWER_MODE_ADDRESS, 0x99);//open backlight
		printf( "LCD backlight KTD3133 on  ... brightness = %d\n", brightness);
	} else {
		i2c_reg_write(BL_POWER_I2C_ADDRESS, BL_POWER_MODE_ADDRESS, 0x98);//close backlight
		printf( "LCD backlight KTD3133 closed  ...\n");
	}
}

