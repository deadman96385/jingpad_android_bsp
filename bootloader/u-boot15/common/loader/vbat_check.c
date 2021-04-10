#include <common.h>
#include "sprd_adc.h"
#include <boot_mode.h>
#include <sprd_battery.h>

int charger_connected(void);

int32_t ADC_GetValue(unsigned int id, int scale)
{
	int32_t result;

	if (-1 == pmic_adc_get_values(id, scale, 1, &result)) {
		return -1;
	}

	return result;
}

int is_bat_low(void)
{
	int32_t vbat_vol;
	uint16_t comp_vbat;

#ifdef CONFIG_UDX710_1H10
	return 0;
#else
	if (charger_connected()) {
		comp_vbat = LOW_BAT_VOL_CHG;
	} else {
		comp_vbat = LOW_BAT_VOL;
	}

	vbat_vol = sprdfgu_read_vbat_vol();
	printf("%s vbat_vol:%d,comp_vbat:%d\n",
		__func__, vbat_vol, comp_vbat);

	if (vbat_vol < comp_vbat)
		return 1;
	else
		return 0;
#endif

}
