#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
#include <adi_hal_internal.h>

static int power_on_voltage_init(void)
{
	regulator_set_voltage("vddsim2",2800);
	regulator_set_voltage("vddgen",1880);
	return 0;
}

static int regulator_mode_init(void)
{
	return 0;
}

int regulator_init(void)
{
	power_on_voltage_init();
	regulator_mode_init();
	return 0;
}
