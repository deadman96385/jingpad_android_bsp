/******************************************************************************
 ** File Name:      sprd_pmic_adc.h                                                  *
 ** Author:                                                    *
 ** DATE:                                                          *
 ** Copyright:      2015 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:    This file defines the basic input and output operations   *
 **                 on hardware, it can be treated as a hardware abstract     *
 **                 layer interface.                                          *
 
 ******************************************************************************/

#ifndef _SPRD_ADC_H_
#define _SPRD_ADC_H_

/* adc channel cal definition */
#define ADC_CHANNEL_INVALID	-1
#define SPRD_AUXADC_CAL_NO 0
#define SPRD_AUXADC_CAL_NV 1
#define SPRD_AUXADC_CAL_CHIP 2
#define SPRDBIG_AUXADC_CAL_CHIP 3
#define SPRDLIT_AUXADC_CAL_CHIP 4
#define ADC_CHANNEL_VBATSENSE	5

#define ADC_BIG_SCALE     1
#define ADC_SMALL_SCALE   0
#define ADC_MESURE_NUMBER       15
#define ADC_SCALE_0	0
#define ADC_SCALE_1	1
#define ADC_SCALE_2	2
#define ADC_SCALE_3	3

struct sprd_adc_cal {
	uint16_t p0_vol;	//4.2V
	uint16_t p0_adc;
	uint16_t p1_vol;	//3.6V
	uint16_t p1_adc;
	uint16_t cal_type;
};

struct pmic_adc_para {
	int small_adc_p0;
	int small_adc_p1;
	int small_vol_p0;
	int small_vol_p1;
	int small_cal_efuse_blk;
	int small_cal_efuse_bit;
	int big_adc_p0;
	int big_adc_p1;
	int big_vol_p0;
	int big_vol_p1;
	int big_cal_efuse_blk;
	int big_cal_efuse_bit;
	int blk_width;
	int adc_data_off;
};

enum adc_channel {
	ADC_CHANNEL_0 = 0,
	ADC_CHANNEL_1 = 1,
	ADC_CHANNEL_2 = 2,
	ADC_CHANNEL_3 = 3,
	ADC_CHANNEL_4 = 4,
	ADC_CHANNEL_VBAT_SENSE = 5,
	ADC_CHANNEL_VCHGSEN = 6,
	ADC_CHANNEL_VCHGBG = 7,
	ADC_CHANNEL_ISENSE = 8,
	ADC_CHANNEL_TPYD = 9,
	ADC_CHANNEL_TPYU = 10,
	ADC_CHANNEL_TPXR = 11,
	ADC_CHANNEL_TPXL = 12,
	ADC_CHANNEL_DCDCCORE = 13,
	ADC_CHANNEL_DCDCARM = 14,
	ADC_CHANNEL_DCDCMEM = 15,
	ADC_CHANNEL_DCDCLDO = 16,
	ADC_CHANNEL_DCDCGPU = 17,
	ADC_CHANNEL_DCDCWRF = 18,
	ADC_CHANNEL_VBATBK = 19,
	ADC_CHANNEL_HEADMIC = 20,
	ADC_CHANNEL_LDO0 = 21,
	ADC_CHANNEL_LDO1 = 22,
	ADC_CHANNEL_LDO2 = 23,
	ADC_CHANNEL_WHTLED = 24,
	ADC_CHANNEL_OTP = 25,
	ADC_CHANNEL_LPLDO0 = 26,
	ADC_CHANNEL_LPLDO1 = 27,
	ADC_CHANNEL_LPLDO2 = 28,
	ADC_CHANNEL_WHTLED_VFB  = 29,
	ADC_CHANNEL_USBDP = 30,
	ADC_CHANNEL_USBDM = 31,
	ADC_CHANNEL_MAX = 31,
};

enum sprd_adc_channel {
	ADC_CHANNEL0 = 0,
	ADC_CHANNEL1 = 1,
	ADC_CHANNEL2 = 2,
	ADC_CHANNEL3 = 3,
	ADC_CHANNEL4 = 4,
	ADC_CHANNEL5 = 5,
	ADC_CHANNEL6 = 6,
	ADC_CHANNEL7 = 7,
	ADC_CHANNEL8 = 8,
	ADC_CHANNEL9 = 9,
	ADC_CHANNEL10 = 10,
	ADC_CHANNEL11 = 11,
	ADC_CHANNEL12 = 12,
	ADC_CHANNEL13 = 13,
	ADC_CHANNEL14 = 14,
	ADC_CHANNEL15 = 15,
	ADC_CHANNEL16 = 16,
	ADC_CHANNEL17 = 17,
	ADC_CHANNEL18 = 18,
	ADC_CHANNEL19 = 19,
	ADC_CHANNEL20 = 20,
	ADC_CHANNEL21 = 21,
	ADC_CHANNEL22 = 22,
	ADC_CHANNEL23 = 23,
	ADC_CHANNEL24 = 24,
	ADC_CHANNEL25 = 25,
	ADC_CHANNEL26 = 26,
	ADC_CHANNEL27 = 27,
	ADC_CHANNEL28 = 28,
	ADC_CHANNEL29  = 29,
	ADC_CHANNEL30 = 30,
	ADC_CHANNEL31 = 31,
	ADC_CHANNELMAX = 31,
};

void pmic_adc_Init(void);

int32_t pmic_adc_get_values(uint16_t channel, int scale, uint8_t num,
			    int32_t * p_buf);

int32_t pmic_adc_get_value_by_isen(uint16_t channel, int scale, uint8_t num,
				   int isen);

int32_t sprd_chan_bat_adc_to_vol(uint16_t channel, int scale, int mux,
				  int32_t adcvalue);

int32_t sprd_chan_small_adc_to_vol(uint16_t channel, int scale, int mux,
				    int32_t adcvalue);

int32_t sprd_chan_adc_to_vol(uint16_t channel, int scale, int mux,
			      int cal_type);

#endif
