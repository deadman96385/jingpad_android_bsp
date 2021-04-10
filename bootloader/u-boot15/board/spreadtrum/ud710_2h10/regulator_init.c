#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
#include <adi_hal_internal.h>

#define REF_OUT_26M_EN 0x3

static int power_on_voltage_init(void)
{
	regulator_set_voltage("vddrf1v25",1200);
	regulator_set_voltage("vddgen1",1300);
	return 0;
}

int regulator_init(void)
{
	power_on_voltage_init();
	/*enable DCXO_26M_REF_OUT*/
	ANA_REG_OR(ANA_REG_GLB_TSX_CTRL0, BITS_DCXO_26M_REF_OUT_EN(REF_OUT_26M_EN));
	return 0;
}
