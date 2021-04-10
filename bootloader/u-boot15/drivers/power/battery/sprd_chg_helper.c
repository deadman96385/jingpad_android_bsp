#include "sprd_chg_helper.h"
#include <asm/arch/sprd_eic.h>
#include "sprd_adc.h"

#define ADC_CAL_TYPE_NO			0
#define ADC_CAL_TYPE_NV			1
#define ADC_CAL_TYPE_EFUSE		2

extern int read_adc_calibration_data(char *buffer, int size);
extern int sprd_get_adc_bat_cal(unsigned int *p_cal_data);
extern int sprd_eic_request(unsigned offset);
extern int sprd_eic_get(unsigned offset);

uint16_t adc_voltage_table[2][2] = {
	{3310, 4200},
	{2832, 3600},
};

uint32_t adc_cal_flag = 0;

uint16_t sprdbat_auxadc2vbatvol(uint16_t adcvalue)
{
	int32_t temp;
	temp = adc_voltage_table[0][1] - adc_voltage_table[1][1];
	temp = temp * (adcvalue - adc_voltage_table[0][0]);
	temp = temp / (adc_voltage_table[0][0] - adc_voltage_table[1][0]);

	debugf("uboot battery voltage:%d,adc4200:%d,adc3600:%d\n",
	       temp + adc_voltage_table[0][1], adc_voltage_table[0][0],
	       adc_voltage_table[1][0]);
	temp = temp + adc_voltage_table[0][1];
	if (temp < 0)
		temp = 0;
	return temp;
}

#define SAMPLE_CNT 5
uint32_t sprdbat_get_aux_vbatvol(void)
{
	int32_t results[SAMPLE_CNT] = {0};
	int32_t i, value = 0;

	if (pmic_adc_get_values(ADC_CHANNEL_VBAT_SENSE, false, SAMPLE_CNT, results)) {
		printf("ERR: read vbat adc fail!!!\n");
		return 0;
	}

	for (i = 0; i < SAMPLE_CNT; i++) {
		printf("vbat adc%d:%d\n",i,results[i]);
		value += results[i];
	}

	value /= SAMPLE_CNT;
	printf("vbat avg adc:%d\n", value);
	value = sprdbat_auxadc2vbatvol(value);
	printf("vbat vol:%d\n", value);
	return value;
}

uint32_t sprdbat_get_vbatauxadc_caltype(void)
{
	return adc_cal_flag;
}

/* used to get adc calibration data from nv or efuse */
void sprdbat_get_vbatauxadc_caldata(void)
{
	unsigned int adc_data[64];
	int ret = 0;

	adc_cal_flag = ADC_CAL_TYPE_NO;

	/* get voltage values from efuse */
	if (adc_cal_flag == ADC_CAL_TYPE_NO) {
		if (!sprd_get_adc_bat_cal(adc_data)) {
			debugf("adc_para from efuse is 0x%x 0x%x \n",
			       adc_data[0], adc_data[1]);
			adc_voltage_table[0][1] = adc_data[0] & 0xFFFF;
			adc_voltage_table[0][0] = (adc_data[0] >> 16) & 0xFFFF;
			adc_voltage_table[1][1] = adc_data[1] & 0xFFFF;
			adc_voltage_table[1][0] = (adc_data[1] >> 16) & 0xFFFF;
			adc_cal_flag = ADC_CAL_TYPE_EFUSE;
		}
	}
}

int sprdbat_is_battery_connected(void)
{
	printf("eica status bat%x\n", sprd_eic_get(EIC_BATDET));

	return ! !sprd_eic_get(EIC_BATDET);
}

void sprdbat_help_init(void)
{
	sprd_eic_request(EIC_BATDET);	//enable battery detect eic
	sprdbat_get_vbatauxadc_caldata();
}

