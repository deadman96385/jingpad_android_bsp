#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
#include <adi_hal_internal.h>
#include <asm/io.h>

static int power_on_voltage_init(void)
{
	unsigned int chip_version;

	chip_version = __raw_readl(REG_AON_APB_AON_VER_ID) & 0xFF;

	if (!chip_version) {
		regulator_set_voltage("vddgen", 1950);
		regulator_set_voltage("vddrf18a", 1850);
	} else {
		regulator_set_voltage("vddgen", 1875);
		regulator_set_voltage("vddrf18a", 1800);
	}

	regulator_set_voltage("avdd18", 1800);
	regulator_set_voltage("vddrf18b", 1800);

	/*only scaling voltage,didn't power on*/
	regulator_set_voltage("vddcamio", 1800);
	return 0;
}

int board_regulator_init(void)
{
	power_on_voltage_init();
	return 0;
}
