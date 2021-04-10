#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
#include <adi_hal_internal.h>

static int power_on_voltage_init(void)
{
	regulator_set_voltage("vddcon",1250);
	regulator_set_voltage("vddvldo",2800);
	return 0;
}

int regulator_init(void)
{
	power_on_voltage_init();
	return 0;
}
