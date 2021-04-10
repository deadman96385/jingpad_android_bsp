#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
#include <adi_hal_internal.h>

#define CONFIG_DA9121_I2C_BUS	5
#define I2C_SPEED		100000
#define SLAVE_ADDR		0x68
#define CH1_B_VOUT		0x26
#define BUCK_VALUE		0x3c
#define SYS_GPIO1_0		0x12
#define GPIO1_MODE		0x8
#define SYS_GPIO1_1		0x13
#define GPIO1_POL		0x4

static int power_on_voltage_init(void)
{
	regulator_set_voltage("vddsim2",2800);
	regulator_set_voltage("vddrf1v25",1250);
	regulator_set_voltage("vddrf1v8",1800);
	regulator_set_voltage("vddcamd0",1200);
	return 0;
}

static int da9121_set_voltage(u8 reg, u8 val)
{
	i2c_set_bus_num(CONFIG_DA9121_I2C_BUS);
	i2c_init(I2C_SPEED, SLAVE_ADDR);

	i2c_reg_write(SLAVE_ADDR, SYS_GPIO1_1, GPIO1_POL);
	i2c_reg_write(SLAVE_ADDR, SYS_GPIO1_0, GPIO1_MODE);
	udelay(100);
	i2c_reg_write(SLAVE_ADDR, reg, val);
}

int regulator_init(void)
{
	power_on_voltage_init();
	da9121_set_voltage(CH1_B_VOUT, BUCK_VALUE);
	return 0;
}
