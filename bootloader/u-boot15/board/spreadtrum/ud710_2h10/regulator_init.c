#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
#include <adi_hal_internal.h>

#define REF_OUT_26M_EN				0x3
#define CONFIG_SPRDCHG_I2C_BUS			6
#define I2C_SPEED				100000
#define SLAVE_ADDR				0x49
#define BUCK_ADDR				0x03
#define BUCK_VALUE_1_1				0x50
#define BUCK_VALUE_0_8				0x32
#define ROC1_CHIP_VER_AA			1
#define ROC1_CHIP_VER_AB			3

static int power_on_voltage_init(void)
{
	regulator_set_voltage("vddrf1v25",1100);
	regulator_set_voltage("vddgen1",1300);
	regulator_set_voltage("vddwcn",1000);
	regulator_set_voltage("vddldo1",3300);
	regulator_set_voltage("vddldo2",3300);
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
	/*enable DCXO_26M_REF_OUT*/
	ANA_REG_OR(ANA_REG_GLB_TSX_CTRL0, BITS_DCXO_26M_REF_OUT_EN(REF_OUT_26M_EN));

	if (ROC1_CHIP_VER_AA == CHIP_REG_GET(REG_AON_APB_AON_VER_ID)) {
		sc2703_set_voltage(BUCK_ADDR, BUCK_VALUE_1_1);
	} else {
		sc2703_set_voltage(BUCK_ADDR, BUCK_VALUE_0_8);
	}

	return 0;
}
