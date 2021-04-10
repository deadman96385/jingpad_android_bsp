#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
#include <adi_hal_internal.h>

#define DDIE_ID_AA	0x00
#define DDIE_ID_AB	0x01
#define DDIE_ID_MASK	0xFF

static int power_on_voltage_init(void)
{
	uint32_t ddie_id;

	ddie_id = CHIP_REG_GET(REG_AON_APB_AON_VER_ID) & DDIE_ID_MASK;
	if (ddie_id == DDIE_ID_AA)
		regulator_set_voltage("vddsram", 1000);
	else if (ddie_id == DDIE_ID_AB)
		regulator_set_voltage("vddsram", 900);

	regulator_set_voltage("vddrf1v25",1245);
	return 0;
}

int regulator_init(void)
{
	power_on_voltage_init();
	return 0;
}
