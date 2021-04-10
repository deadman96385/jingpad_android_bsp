#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
#include <adi_hal_internal.h>

#define FAN53555_EN_GPIO 163

#define BUS_NUM         (3)
#define I2C_SPEED			(100000)
#define SLAVE_ADDR 		(0x60)

static int power_on_gpu()
{
	sprd_gpio_request(NULL, FAN53555_EN_GPIO);
	sprd_gpio_direction_output(NULL, FAN53555_EN_GPIO, 0);
	udelay(100); //wait 100us
	sprd_gpio_direction_output(NULL, FAN53555_EN_GPIO, 1);
	udelay(100); //wait 100us


	i2c_set_bus_num(BUS_NUM);
	i2c_init(I2C_SPEED, SLAVE_ADDR);
	udelay(100); //wait 100us
	i2c_reg_write(SLAVE_ADDR, 0x0, 0xaa);//enable fan53555 via i2c
	return 0;
}
static int power_on_voltage_init(void)
{
	power_on_gpu();
	regulator_set_voltage("dcdcrf",1500);
	regulator_set_voltage("vddvldo",2800);
	regulator_set_voltage("vddcon",1250);
	return 0;
}

int regulator_init(void)
{
	power_on_voltage_init();
	return 0;
}
