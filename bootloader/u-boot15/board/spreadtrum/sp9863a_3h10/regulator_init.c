#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
#include <adi_hal_internal.h>

#define CONFIG_SPRDCHG_I2C_BUS	7
#define I2C_SPEED				100000
#define SLAVE_ADDR				0x49
#define BUCK_ADDR				0x03
#define BUCK_VALUE				0x50

static int power_on_voltage_init(void)
{
	regulator_set_voltage("vddsim2",2800);
	return 0;
}

static int sc2703_set_voltage(u8 reg, u8 val)
{
	i2c_set_bus_num(CONFIG_SPRDCHG_I2C_BUS);
	i2c_init(I2C_SPEED, SLAVE_ADDR);
	i2c_reg_write(SLAVE_ADDR, reg, val);
}

int regulator_init(void)
{
	power_on_voltage_init();
	sc2703_set_voltage(BUCK_ADDR, BUCK_VALUE);
	return 0;
}
