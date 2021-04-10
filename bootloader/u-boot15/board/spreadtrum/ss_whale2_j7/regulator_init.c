#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
#include <adi_hal_internal.h>

static int regulator_mode_init()
{
	ANA_REG_OR(ANA_REG_GLB_KPLED_CTRL, BIT_KPLED_PULLDOWN_EN);
	return 0;
}

static int power_on_voltage_init(void)
{
	regulator_set_voltage("vddvldo",2800);
	regulator_set_voltage("vddcon",1250);
	regulator_enable("vddcon");
	return 0;
}

int regulator_init(void)
{
	power_on_voltage_init();
	regulator_mode_init();
	return 0;
}
