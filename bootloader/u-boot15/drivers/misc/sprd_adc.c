/*
 * Copyright (C) 2014 Spreadtrum Communications Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
#include <asm/errno.h>
#include <asm/io.h>
#include <linux/kernel.h>
#include <linux/compat.h>
#include <otp_helper.h>
#include <sprd_adc.h>
#include "adi_hal_internal.h"
#include <common.h>

typedef unsigned int u32;
#if defined(CONFIG_ADIE_SC2720) || defined(CONFIG_ADIE_SC2730)
#define ADC_REG_BASE                       (ADC_BASE + 0x0004)
#else
#define ADC_REG_BASE                        ADC_BASE
#endif

#define ADC_CTRL                            (ADC_REG_BASE + 0x0000)
#define ADC_SW_CH_CFG                       (ADC_REG_BASE + 0x0004)
#define ADC_HW_CH_CFG_SLOW(x)               (ADC_REG_BASE + 0x0008 + ((x)-1)*0x04)
#define ADC_HW_CH_CFG_FAST(x)               (ADC_REG_BASE + 0x0028 + ((x)-1)*0x04)
#define ADC_HW_CH_DELAY                     (ADC_REG_BASE + 0x0048)
#define ADC_DAT                             (ADC_REG_BASE + 0x004C)
#define ADC_INT_EN                          (ADC_REG_BASE + 0x0050)
#define ADC_INT_CLR                         (ADC_REG_BASE + 0x0054)
#define ADC_INT_STAT                        (ADC_REG_BASE + 0x0058)
#define ADC_INT_SRC                         (ADC_REG_BASE + 0x005C)
#define ADC_CTL0                            (ADC_REG_BASE + 0x00AC)
#define ADC_CTL1                            (ADC_REG_BASE + 0x00B0)

/* ADC_CTRL */
#define BIT_ADC_OFFSET_CAL_EN		BIT(12)
#define BIT_AUXAD_AVERAGE(_X_)		(((_X_) & 0x7) << 8)
#define BIT_SW_CH_RUN_NUM(_X_)		((((_X_) - 1) & 0xF ) << 4)
#define SW_CH_NUM_MSK				(BIT(4) | BIT(5) | BIT(6) | BIT(7))
#define ADC_MODE_12B                        BIT_2
#define SW_CH_ON_BIT                        BIT_1
#define ADC_EN_BIT                          BIT_0

/* ADC_SW_CH_CFG */

#if defined(CONFIG_ADIE_SC2720) || defined(CONFIG_ADIE_SC2730)
#define BIT_CH_SCALE(_X_)			(((_X_) & 0x3) << 9)
#else
#define BIT_CH_SCALE(_X_)			(((_X_) & 0x1) << 5)
#endif

#define ADC_CS_BIT_MSK                      0x1F

#define ADC_IRQ_EN_BIT                      BIT_0

#define ADC_IRQ_CLR_BIT                     BIT_0

#define ADC_IRQ_RAW_BIT                     BIT_0
#define ADC_DATA_MSK                        0xFFF

#define BIT_ADC_CUR_EN             BIT(0)
#define SC2731_ADC0_SELECT_BIT     BIT(11)
#define BITS_AUXAD_NTC_MUX(x)      (((x) & 0x3) << 0)

#define TPC_CHANNEL_X    2
#define TPC_CHANNEL_Y    3
#define ADC_MESURE_NUMBER       15
#define ADC_CHAN_MAX 31

#define BITSINDEX(b, o)	( (b) * para.blk_width + (o) )
#define RATIO(_n_, _d_) (_n_ << 16 | _d_)

static u32 ana_chip_id;
extern void tmr_udelay (unsigned long usec);

__attribute__((weak))
void tmr_udelay (unsigned long usec)
{
	volatile int32_t i;
	unsigned long cnt = 255 * usec;
	for (i = 0; i < cnt; i++) ;
}

struct sprd_adc_cal big_scale_cal = {
	4200, 3310,
	3600, 2832,
	SPRD_AUXADC_CAL_NO,
};

struct sprd_adc_cal small_sclae_cal = {
	1000, 3413,
	100, 341,
	SPRD_AUXADC_CAL_NO,
};

#if defined(CONFIG_ADIE_SC2723) || defined(CONFIG_ADIE_SC2723S)

static struct pmic_adc_para para = {
	.small_adc_p0 = 819,
	.small_adc_p1 = 82,
	.small_vol_p0 = 1000,
	.small_vol_p1 = 100,
	.small_cal_efuse_blk = 9,
	.small_cal_efuse_bit = 16,
	.big_adc_p0 = 711,
	.big_adc_p1 = 830,
	.big_vol_p0 = 3600,
	.big_vol_p1 = 4200,
	.big_cal_efuse_blk = 7,
	.big_cal_efuse_bit = 16,
	.blk_width = 8,
	.adc_data_off = 128,
};
#elif defined(CONFIG_ADIE_SC2731) || defined(CONFIG_ADIE_SC2721)

static struct pmic_adc_para para = {
	.small_adc_p0 = 838,
	.small_adc_p1 = 84,
	.small_vol_p0 = 1000,
	.small_vol_p1 = 100,
	.small_cal_efuse_blk = 19,
	.small_cal_efuse_bit = 16,
	.big_adc_p0 = 728,
	.big_adc_p1 = 850,
	.big_vol_p0 = 3600,
	.big_vol_p1 = 4200,
	.big_cal_efuse_blk = 18,
	.small_cal_efuse_bit = 16,
	.blk_width = 16,
	.adc_data_off = 128,
};
#elif defined(CONFIG_ADIE_SC2720) || defined(CONFIG_ADIE_SC2730)

static struct pmic_adc_para para = {
	.small_adc_p0 = 833,
	.small_adc_p1 = 80,
	.small_vol_p0 = 1000,
	.small_vol_p1 = 100,
	.small_cal_efuse_blk = 19,
	.small_cal_efuse_bit = 16,
	.big_adc_p0 = 733,
	.big_adc_p1 = 856,
	.big_vol_p0 = 3600,
	.big_vol_p1 = 4200,
	.big_cal_efuse_blk = 18,
	.small_cal_efuse_bit = 16,
	.blk_width = 16,
	.adc_data_off = 128,
};
#endif
static int pmic_adc_data_average(int a[], int N)
{
	int i, sum = 0;
	for (i = 0; i < N; i++)
		sum += a[i];
	return DIV_ROUND_CLOSEST(sum, N);
}

static void pmic_adc_set_channel(uint16_t channel)
{
	if (channel >= ADC_CHANNEL_MAX) {
		sprd_err("adc limits to 0~%d\n", ADC_CHANNEL_MAX);
		return;
	}

	ANA_REG_MSK_OR(ADC_SW_CH_CFG, channel, ADC_CS_BIT_MSK);
}

static void pmic_adc_set_scale(int scale)
{
	ANA_REG_MSK_OR(ADC_SW_CH_CFG, BIT_CH_SCALE(scale), BIT_CH_SCALE(~0));
}

int32_t pmic_adc_get_values(uint16_t channel, int scale, uint8_t num,
			    int32_t * p_buf)
{
	int32_t count, i;

	ANA_REG_OR(ADC_INT_CLR, ADC_IRQ_CLR_BIT);

	pmic_adc_set_channel(channel);
	pmic_adc_set_scale(scale);
	ANA_REG_MSK_OR(ADC_CTRL, BIT_SW_CH_RUN_NUM(num), SW_CH_NUM_MSK);
	ANA_REG_OR(ADC_CTRL, SW_CH_ON_BIT);

	/* wait adc complete */
	count = 3000;
	while (!(ANA_REG_GET(ADC_INT_SRC) & ADC_IRQ_RAW_BIT) && count--) {
		tmr_udelay(10);
	}
	if (count <= 0) {
		sprd_warning("warn: read adc value timeout....\n");
		return -1;
	}

	for (count = 0; count < num; count++) {
		p_buf[count] = ANA_REG_GET(ADC_DAT) & ADC_DATA_MSK;
	}

	/* turn off adc soft channel */
	ANA_REG_AND(ADC_CTRL, ~SW_CH_ON_BIT);
	ANA_REG_MSK_OR(ADC_CTRL, BIT_SW_CH_RUN_NUM(1), SW_CH_NUM_MSK);
	ANA_REG_OR(ADC_INT_CLR, ADC_IRQ_CLR_BIT);

	return 0;
}

static int sprd_get_efuse_ib_trim(unsigned int *p_cal_data)
{
	unsigned int data,blk0;

	blk0 = sprd_pmic_efuse_read(0);
	if (blk0 & (1 << 7)) {
		return 0;
	}
	data = sprd_pmic_efuse_read_bits(BITSINDEX(15, 0), 7);
	*p_cal_data = data;
	return 1;
}

static void sprd_current_source_cal(void)
{
	unsigned int ib_trim_cal_data = 0;
#if defined(CONFIG_ADIE_SC2723) || defined(CONFIG_ADIE_SC2723S)
     if (sprd_get_efuse_ib_trim(&ib_trim_cal_data)) {
      sci_adi_write(ANA_REG_GLB_WHTLED_CTRL, BITS_IB_TRIM(ib_trim_cal_data),BITS_IB_TRIM(~0));
      sci_adi_clr(ANA_REG_GLB_RGB_CTRL, BIT_IB_TRIM_EM_SEL);
      sprd_info("ib_trim_cal_data:%d\n",ib_trim_cal_data);
    }
#else
	sprd_info("ib_trim_cal_data:%d\n",ib_trim_cal_data);
#endif
}

/*for sc2731/sc2721/2720 if set 1.25uA, parameter isen is 125uA */
static int pmic_adc_isen_set(int isen)
{
	int isen_set = 0;
	switch (isen) {
	case 125:
		isen_set = 0x0;
		break;
	case 250:
		isen_set = 0x1;
		break;
	case 500:
		isen_set = 0x2;
		break;
	case 1000:
		isen_set = 0x3;
		break;
	case 2000:
		isen_set = 0x4;
		break;
	case 4000:
		isen_set = 0x5;
		break;
	case 8000:
		isen_set = 0x6;
		break;
	case 16000:
		isen_set = 0x7;
		break;
	default:
		isen_set = 0x0;
		break;
	}
	return isen_set;
}

#if defined(CONFIG_ADIE_SC2723) || defined(CONFIG_ADIE_SC2723S)

/* BITS_AUXAD_CURRENT_IBS = (isen * 100 / 250 -1) */
static int pmic_adc_set_current(u8 enable, int isen)
{
	if (enable) {
		isen = (isen * 100 / 250 - 1);
		if (isen > BITS_AUXAD_CURRENT_IBS(-1))
			isen = BITS_AUXAD_CURRENT_IBS(-1);
		sci_adi_write(ANA_REG_GLB_AUXAD_CTL,
			      (BIT_AUXAD_CURRENTSEN_EN |
			       BITS_AUXAD_CURRENT_IBS(isen)),
			      BIT_AUXAD_CURRENTSEN_EN |
			      BITS_AUXAD_CURRENT_IBS(-1));
	} else {
		sci_adi_clr(ANA_REG_GLB_AUXAD_CTL, BIT_AUXAD_CURRENTSEN_EN);
	}

	return 0;
}

#elif defined(CONFIG_ADIE_SC2731)

#define BITS_BATDET_CUR_I(x)     (((x) & 0x7) << 1)
static int pmic_adc_set_current(u8 enable, int isen)
{
	int isen_bit;
	if (enable) {
		isen_bit = pmic_adc_isen_set(isen);
		sci_adi_set(ANA_REG_GLB_BATDET_CUR_CTRL,BIT_BATDET_CUR_EN);
		sci_adi_set(ANA_REG_GLB_AUXAD_CTL,BIT_AUXAD_CURRENTSEN_EN);
		sci_adi_set(ANA_REG_GLB_BATDET_CUR_CTRL,BITS_BATDET_CUR_I(isen_bit));
	}else {
		sci_adi_clr(ANA_REG_GLB_BATDET_CUR_CTRL,BITS_BATDET_CUR_I(~0));
		sci_adi_clr(ANA_REG_GLB_AUXAD_CTL, BIT_AUXAD_CURRENTSEN_EN);
		sci_adi_clr(ANA_REG_GLB_BATDET_CUR_CTRL,BIT_BATDET_CUR_EN);
	}
	debugf("ANA_REG_GLB_BATDET_CUR_CTRL =0x%x\n",sci_adi_read(ANA_REG_GLB_BATDET_CUR_CTRL));
	return 0;
}

#elif defined(CONFIG_ADIE_SC2721) || defined(CONFIG_ADIE_SC2720) || \
	defined(CONFIG_ADIE_SC2730)

static int pmic_adc_set_isen(u8 enable, int isen)
{
	int isen_bit;

	if (enable) {
		isen_bit = pmic_adc_isen_set(isen);
		sci_adi_clr(ANA_REG_GLB_IB_CTRL, BIT_IB_REX_EN);
		sci_adi_set(ANA_REG_GLB_IB_CTRL, BIT_BATDET_CUR_EN);
		sci_adi_set(ANA_REG_GLB_IB_CTRL, BITS_BATDET_CUR_I(isen_bit));
		tmr_udelay(150);
	} else {
		sci_adi_clr(ANA_REG_GLB_IB_CTRL, BITS_BATDET_CUR_I(~0));
		sci_adi_clr(ANA_REG_GLB_IB_CTRL, BIT_BATDET_CUR_EN);
	}
	return 0;
}

static int pmic_adc_set_current(u8 enable, int isen)
{
	if (enable) {
		pmic_adc_set_isen(enable, isen);
		ANA_REG_OR(ADC_CTL0, BIT_ADC_CUR_EN);
	} else {
		ANA_REG_AND(ADC_CTL0, ~BIT_ADC_CUR_EN);
		pmic_adc_set_isen(enable, isen);
	}

	return 0;
}
#endif

int32_t pmic_adc_get_value_by_isen(uint16_t channel, int scale, uint8_t num,
				   int isen)
{
	int32_t results[ADC_MESURE_NUMBER + 1] = { 0 };
	int32_t values = 0;
	int ret = 0, i = 0;

	pmic_adc_set_current(1, isen);

	if (0 == pmic_adc_get_values(channel, scale, num, results)) {
		values =
		    pmic_adc_data_average(&results[num / 5],
					  (num - num * 2 / 5));
	}
	pmic_adc_set_current(0, 0);

	for (i = 0; i < ARRAY_SIZE(results); i++) {
		debugf("%d\t", results[i]);
	}
	debugf("adc[%d] isen: %d, value: %d\n", channel, isen, values);

	return values;
}

#if defined(CONFIG_ADIE_SC2723) || defined(CONFIG_ADIE_SC2723S)

static int pmic_adc_get_ratio(uint16_t channel, int scale, int mux)
{
	switch (channel) {
	case ADC_CHANNEL_0:
		return RATIO(1, 1);
	case ADC_CHANNEL_1:
	case ADC_CHANNEL_2:
	case ADC_CHANNEL_3:
		return (scale ? RATIO(400, 1025) : RATIO(1, 1));
	case ADC_CHANNEL_VBAT_SENSE:
	case ADC_CHANNEL_ISENSE:
		return RATIO(7, 29);
	case ADC_CHANNEL_VCHGSEN:
		return RATIO(77, 1024);
	case ADC_CHANNEL_DCDCCORE:
		mux = mux >> 13;
		switch (mux) {
		case 1:
		case 2:
			return (scale ? RATIO(36, 55) : RATIO(9, 11));
		case 3:
		case 5:
			return (scale ? RATIO(12, 25) : RATIO(3, 5));
		case 4:
			return (scale ? RATIO(3, 10) : RATIO(3, 8));
		case 6:
			return (scale ? RATIO(9, 20) : RATIO(9, 16));
		case 7:
			return (scale ? RATIO(12, 55) : RATIO(3, 11));
		default:
			return RATIO(1, 1);
		}
	case 0xE:
		return (scale ? RATIO(4, 5) : RATIO(1, 1));
	case 0x14:
		return RATIO(1, 3);

	case ADC_CHANNEL_LDO0:
		return RATIO(1, 2);
	case ADC_CHANNEL_VBATBK:
	case ADC_CHANNEL_LDO1:
	case ADC_CHANNEL_LDO2:
	case ADC_CHANNEL_WHTLED:
	case ADC_CHANNEL_WHTLED_VFB:
	case ADC_CHANNEL_USBDP:
	case ADC_CHANNEL_USBDM:
		return RATIO(1, 3);

	default:
		return RATIO(1, 1);
	}
	return RATIO(1, 1);
}

#elif defined(CONFIG_ADIE_SC2731)
static int pmic_adc_get_ratio(uint16_t channel, int scale, int mux)
{
	switch (channel) {
	case ADC_CHANNEL_0:
		return RATIO(1, 1);
	case ADC_CHANNEL_1:
	case ADC_CHANNEL_2:
	case ADC_CHANNEL_3:
	case ADC_CHANNEL_4:
		return (scale ? RATIO(400, 1025) : RATIO(1, 1));
	case ADC_CHANNEL_VBAT_SENSE:
	case ADC_CHANNEL_ISENSE:
		return RATIO(7, 29);
	case ADC_CHANNEL_VCHGSEN:
			return RATIO(375, 9000);
	case ADC_CHANNEL_VCHGBG:
	case ADC_CHANNEL_TPYD:
		return (scale ? RATIO(100, 125) : RATIO(1, 1));
	case ADC_CHANNEL_DCDCCORE:
		switch (mux) {
		case 1:
		case 2:
			return (scale ? RATIO(4, 5) : RATIO(1, 1));
		case 3:
			return (scale ? RATIO(3, 5) : RATIO(3, 4));
		case 4:
			return (scale ? RATIO(49, 125) : RATIO(49, 100));
		case 5:
			return (scale ? RATIO(9, 20) : RATIO(9, 16));
		case 6:
			return (scale ? RATIO(4, 5) : RATIO(1, 1));
		case 7:
			return (scale ? RATIO(36, 170) : RATIO(9, 34));
		case 8:
			return (scale ? RATIO(4, 5) : RATIO(1, 1));
		default:
			return RATIO(1, 1);
		}
	case ADC_CHANNEL_VBATBK:
		return RATIO(1, 3);
	case ADC_CHANNEL_HEADMIC:
		switch (mux) {
		case 1:
		case 2:
		case 3:
		case 4:
			return (scale ? RATIO(1, 3) : RATIO(1, 1));
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
			return (scale ? RATIO(1, 12) : RATIO(1, 4));
		default:
			return RATIO(1, 1);
		}
	case ADC_CHANNEL_LDO0:
	case ADC_CHANNEL_LDO1:
	case ADC_CHANNEL_LDO2:
		return RATIO(9, 25);
	case ADC_CHANNEL_USBDP:
	case ADC_CHANNEL_USBDM:
		return RATIO(1, 1);

	default:
		return RATIO(1, 1);
	}
	return RATIO(1, 1);
}

#elif defined(CONFIG_ADIE_SC2721)
static int pmic_adc_get_ratio(uint16_t channel, int scale, int mux)
{
	switch (channel) {
		case ADC_CHANNEL0:
			return RATIO(1, 1);
		case ADC_CHANNEL1:
		case ADC_CHANNEL2:
		case ADC_CHANNEL3:
		case ADC_CHANNEL4:
			return (scale ? RATIO(400, 1025) : RATIO(1, 1));
		case ADC_CHANNEL5:
			return RATIO(7, 29);
		case ADC_CHANNEL7:
		case ADC_CHANNEL9:
			return (scale ? RATIO(100, 125) : RATIO(1, 1));
		case ADC_CHANNEL8:
		case ADC_CHANNEL15:
			return RATIO(1, 1);
		case ADC_CHANNEL13:
			switch (mux) {
			case 1:
			case 4:
				return (scale ? RATIO(4, 5) : RATIO(1, 1));
			case 2:
				return (scale ? RATIO(3, 5) : RATIO(3, 4));
			case 3:
				return (scale ? RATIO(49, 125) : RATIO(49, 100));
			case 5:
				return (scale ? RATIO(36, 170) : RATIO(9, 34));
			default:
				return RATIO(1, 1);
			}
		case ADC_CHANNEL14:
			return RATIO(68, 900);
		case ADC_CHANNEL16:
			return RATIO(48, 100);
		case ADC_CHANNEL19:
			return RATIO(1, 3);
		case ADC_CHANNEL20:
			switch (mux) {
			case 1:
			case 2:
			case 3:
				return (scale ? RATIO(1, 3) : RATIO(1, 1));
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
				return (scale ? RATIO(1, 12) : RATIO(1, 4));
			default:
				return RATIO(1, 1);
			}
		case ADC_CHANNEL21:
		case ADC_CHANNEL22:
		case ADC_CHANNEL23:
			return RATIO(3, 8);
		case ADC_CHANNEL30:
		case ADC_CHANNEL31:
			return RATIO(1, 1);

		default:
			return RATIO(1, 1);
	}
	return RATIO(1, 1);
}

#elif defined(CONFIG_ADIE_SC2720)
static int pmic_adc_get_ratio(uint16_t channel, int scale, int mux)
{
	if(channel > ADC_CHAN_MAX)
		return RATIO(1, 1);

	switch (channel) {
		case ADC_CHANNEL14:
			switch (scale) {
			case 0:
				return RATIO(68, 900);
			case 1:
				return RATIO(68, 1760);
			case 2:
				return RATIO(68, 2327);
			case 3:
				return RATIO(68, 3654);
			default:
				return RATIO(1, 1);
			}
		case ADC_CHANNEL16:
			switch (scale) {
			case 0:
				return RATIO(48, 100);
			case 1:
				return RATIO(480, 1955);
			case 2:
				return RATIO(480, 2586);
			case 3:
				return RATIO(48, 406);
			default:
				return RATIO(1, 1);
			}
		case ADC_CHANNEL21:
		case ADC_CHANNEL22:
		case ADC_CHANNEL23:
			switch (scale) {
			case 0:
				return RATIO(3, 8);
			case 1:
				return RATIO(375, 1955);
			case 2:
				return RATIO(375, 2586);
			case 3:
				return RATIO(300, 3248);
			default:
				return RATIO(1, 1);
			}
		default:
			switch (scale) {
			case 0:
				return RATIO(1, 1);
			case 1:
				return RATIO(1000, 1955);
			case 2:
				return RATIO(1000, 2586);
			case 3:
				return RATIO(100, 406);
			default:
				return RATIO(1, 1);
			}
	}
	return RATIO(1, 1);
}

#elif defined(CONFIG_ADIE_SC2730)
static int pmic_adc_get_ratio(uint16_t channel, int scale, int mux)
{
	if(channel > ADC_CHAN_MAX)
		return RATIO(1, 1);

	switch (channel) {
		case ADC_CHANNEL14:
			switch (scale) {
			case 0:
				return RATIO(68, 900);
			case 1:
				return RATIO(68, 1760);
			case 2:
				return RATIO(68, 2327);
			case 3:
				return RATIO(68, 3654);
			default:
				return RATIO(1, 1);
			}
		case ADC_CHANNEL15:
			switch (scale) {
			case 0:
				return RATIO(1, 3);
			case 1:
				return RATIO(1000, 5865);
			case 2:
				return RATIO(500, 3879);
			case 3:
				return RATIO(500, 6090);
			default:
				return RATIO(1, 1);
			}
		case ADC_CHANNEL16:
			switch (scale) {
			case 0:
				return RATIO(48, 100);
			case 1:
				return RATIO(480, 1955);
			case 2:
				return RATIO(480, 2586);
			case 3:
				return RATIO(48, 406);
			default:
				return RATIO(1, 1);
			}
		case ADC_CHANNEL21:
		case ADC_CHANNEL22:
		case ADC_CHANNEL23:
			switch (scale) {
			case 0:
				return RATIO(3, 8);
			case 1:
				return RATIO(375, 1955);
			case 2:
				return RATIO(375, 2586);
			case 3:
				return RATIO(300, 3248);
			default:
				return RATIO(1, 1);
			}
		default:
			switch (scale) {
			case 0:
				return RATIO(1, 1);
			case 1:
				return RATIO(1000, 1955);
			case 2:
				return RATIO(1000, 2586);
			case 3:
				return RATIO(100, 406);
			default:
				return RATIO(1, 1);
			}
	}
	return RATIO(1, 1);
}
#endif

static int sprd_get_adc_small_scale_cal(uint32_t *p_cal_data)
{
	uint32_t deta = 0;
	uint32_t adc_data = 0;

	deta =
	    sprd_pmic_efuse_read_bits(BITSINDEX(para.small_cal_efuse_blk, 0),
				 para.small_cal_efuse_bit);
	debugf("get pmic efuse block %u, deta: 0x%08x\n",
		para.small_cal_efuse_blk, deta);
	deta &= 0xFFFFFF;
	if ((!deta) || (p_cal_data == NULL)) {
		return -1;
	}
#if defined(CONFIG_ADIE_SC2723) || defined(CONFIG_ADIE_SC2723S)
	/* adc 0.1V */
	adc_data =
	    ((deta & 0x00FF) + para.small_adc_p1 - para.adc_data_off) * 4;
	debugf("0.1V adc data 0x%x\n", adc_data);
	p_cal_data[1] = (para.small_vol_p1) | (adc_data << 16);

	/* adc 1.0V */
	adc_data =
	    (((deta >> 8) & 0x00FF) + para.small_adc_p0 - para.adc_data_off) * 4;
	debugf("1.0V adc data 0x%x\n", adc_data);
	p_cal_data[0] = (para.small_vol_p0) | (adc_data << 16);
#elif defined(CONFIG_ADIE_SC2731) || defined(CONFIG_ADIE_SC2721) || \
	defined(CONFIG_ADIE_SC2720) || defined(CONFIG_ADIE_SC2730)
	/* adc 0.1V */
	adc_data =
		 (((deta >> 8) & 0x00FF) + para.small_adc_p1 - para.adc_data_off) * 4;
	debugf("0.1V adc data 0x%x\n", adc_data);
	p_cal_data[1] = (para.small_vol_p1) | (adc_data << 16);

	/* adc 1.0V */
	adc_data =
		 ((deta & 0x00FF) + para.small_adc_p0 - para.adc_data_off) * 4;
	debugf("1.0V adc data 0x%x\n", adc_data);
	p_cal_data[0] = (para.small_vol_p0) | (adc_data << 16);
#endif

	return 0;
}

int sprd_get_adc_bat_cal(uint32_t *p_cal_data)
{
	uint32_t deta = 0;
	uint32_t cal_data = 0;

	deta = sprd_pmic_efuse_read_bits(BITSINDEX(para.big_cal_efuse_blk, 0), 16);
	deta &= 0xFFFFFF;
	if ((!deta) || (p_cal_data == NULL)) {
		return -1;
	}
	debugf("get pmic efuse block %u, deta: 0x%08x\n",
		para.big_cal_efuse_blk, deta);
	/*adc 3.6V */
	cal_data =
	    ((deta >> 8) & 0x00FF) + para.big_adc_p0 - para.adc_data_off;
	p_cal_data[1] = (para.big_vol_p0) | ((cal_data << 2) << 16);
	/*adc 4.2V */
	cal_data = (deta & 0x00FF) + para.big_adc_p1 - para.adc_data_off;
	p_cal_data[0] = (para.big_vol_p1) | ((cal_data << 2) << 16);

	return 0;
}


static int sprd_bat_scale_adc_efuse_get(void)
{
	uint32_t efuse_cal_data[2] = { 0 };

	if (!sprd_get_adc_bat_cal(efuse_cal_data)) {
		big_scale_cal.p0_vol = efuse_cal_data[0] & 0xffff;
		big_scale_cal.p0_adc = (efuse_cal_data[0] >> 16) & 0xffff;
		big_scale_cal.p1_vol = efuse_cal_data[1] & 0xffff;
		big_scale_cal.p1_adc = (efuse_cal_data[1] >> 16) & 0xffff;
		big_scale_cal.cal_type = SPRDBIG_AUXADC_CAL_CHIP;
		debugf("adc efuse big cal %d,%d,%d,%d,cal_type:%d\n",
			big_scale_cal.p0_vol, big_scale_cal.p0_adc,
			big_scale_cal.p1_vol, big_scale_cal.p1_adc,
			big_scale_cal.cal_type);
		return 0;
	}
	return -1;
}

static int sprd_small_scale_adc_efuse_get(void)
{
	uint32_t efuse_cal_data[2] = { 0 };

	if (!sprd_get_adc_small_scale_cal(efuse_cal_data)) {
		small_sclae_cal.p0_vol = efuse_cal_data[0] & 0xffff;
		small_sclae_cal.p0_adc = (efuse_cal_data[0] >> 16) & 0xffff;
		small_sclae_cal.p1_vol = efuse_cal_data[1] & 0xffff;
		small_sclae_cal.p1_adc = (efuse_cal_data[1] >> 16) & 0xffff;
		small_sclae_cal.cal_type = SPRDLIT_AUXADC_CAL_CHIP;
		debugf("adc efuse small cal %d,%d,%d,%d,cal_type:%d\n",
			small_sclae_cal.p0_vol, small_sclae_cal.p0_adc,
			small_sclae_cal.p1_vol, small_sclae_cal.p1_adc,
			small_sclae_cal.cal_type);
		return 0;
	}
	return -1;
}

void pmic_adc_Init(void)
{
	ANA_REG_OR(ANA_REG_GLB_ARM_MODULE_EN, BIT_ANA_ADC_EN);	//ADC enable
	ANA_REG_OR(ANA_REG_GLB_ARM_CLK_EN, BIT_CLK_AUXAD_EN | BIT_CLK_AUXADC_EN);	//enable auxad clock
	ANA_REG_OR(ANA_REG_GLB_XTL_WAIT_CTRL, BIT_XTL_EN);	//enable clk
	ANA_REG_OR( ANA_REG_GLB_SOFT_RST0, BIT_ADC_SOFT_RST);
	tmr_udelay(5);
	ANA_REG_AND( ANA_REG_GLB_SOFT_RST0, ~BIT_ADC_SOFT_RST);

	ANA_REG_OR(ADC_CTRL, ADC_EN_BIT);
	ANA_REG_OR(ADC_CTRL, ADC_MODE_12B);
#if defined(CONFIG_ADIE_SC2720) || defined(CONFIG_ADIE_SC2730)
	ANA_REG_OR(ADC_CTRL, BIT_ADC_OFFSET_CAL_EN);
	ANA_REG_MSK_OR(ADC_CTRL, BIT_AUXAD_AVERAGE(0x3), BIT_AUXAD_AVERAGE(~0));
#endif
	ana_chip_id =
	    ((u32) ANA_REG_GET(ANA_REG_GLB_CHIP_ID_HIGH) << 16) | ((u32)
								   ANA_REG_GET
								   (ANA_REG_GLB_CHIP_ID_LOW)
								   & 0xFFFF);
	if (0 == sprd_small_scale_adc_efuse_get())
		debugf("sprd small scale efuse have cal\n");
	if (0 == sprd_bat_scale_adc_efuse_get())
		debugf("sprd big scale efuse have cal\n");
	sprd_current_source_cal();
#if defined(CONFIG_ADIE_SC2731)
	sci_adi_set(ANA_REG_GLB_AUXAD_CTL, SC2731_ADC0_SELECT_BIT);
#elif defined(CONFIG_ADIE_SC2721)
       ANA_REG_OR(ADC_CTL1, BITS_AUXAD_NTC_MUX(0x1));
       debugf("ADC_CTL1 value of it 0x%x\n", ANA_REG_GET(ADC_CTL1));
#endif
}

static int32_t sprd_small_scale_to_vol(int32_t adcvalue)
{
	int32_t vol;
	vol = small_sclae_cal.p0_vol - small_sclae_cal.p1_vol;
	vol = vol * (adcvalue - small_sclae_cal.p0_adc);
	vol = vol / (small_sclae_cal.p0_adc - small_sclae_cal.p1_adc);
	vol = vol + small_sclae_cal.p0_vol;

	return vol;
}

static int32_t sprd_bat_scale_adc_to_vol(int32_t adcvalue)
{
	int32_t vol;

	vol = big_scale_cal.p0_vol - big_scale_cal.p1_vol;
	vol = vol * (adcvalue - big_scale_cal.p0_adc);
	vol = vol / (big_scale_cal.p0_adc - big_scale_cal.p1_adc);
	vol = vol + big_scale_cal.p0_vol;

	return vol;
}

int32_t sprd_chan_bat_adc_to_vol(uint16_t channel, int scale, int mux,
				  int32_t adcvalue)
{
	int32_t result;
	int32_t vol;
	int32_t ratio;
	int32_t m, n;
	int32_t bat_numerators, bat_denominators;
	int32_t numerators, denominators;

	vol = sprd_bat_scale_adc_to_vol(adcvalue);
	ratio = pmic_adc_get_ratio(ADC_CHANNEL_VBATSENSE, scale, mux);
	bat_numerators = ratio >> 16;
	bat_denominators = ratio << 16 >> 16;
	ratio = pmic_adc_get_ratio(channel, scale, mux);
	numerators = ratio >> 16;
	denominators = ratio << 16 >> 16;
	/* v1 = vbat_vol*0.268 = vol_bat_m * r2 /(r1+r2) */

	n = bat_denominators * numerators;
	m = vol * bat_numerators * (denominators);
	result = (m + n / 2) / n;
	debugf("big scale adc %d vol %d\n", adcvalue, result);
	return result;
}

int32_t sprd_chan_small_adc_to_vol(uint16_t channel, int scale, int mux,
				    int32_t adcvalue)
{
	int32_t result;
	int32_t vol;
	int32_t ratio;
	int32_t m, n;
	int32_t bat_numerators, bat_denominators;
	int32_t numerators, denominators;
	vol = sprd_small_scale_to_vol(adcvalue);
	bat_numerators = 1;
	bat_denominators = 1;
	ratio = pmic_adc_get_ratio(channel, scale, mux);
	numerators = ratio >> 16;
	denominators = ratio << 16 >> 16;

	/* v1 = vbat_vol*0.268 = vol_bat_m * r2 /(r1+r2) */

	n = bat_denominators * numerators;
	m = vol * bat_numerators * (denominators);
	result = (m + n / 2) / n;
	debugf("small scale adc %d vol %d\n", adcvalue, result);
	return result;
}

int32_t sprd_chan_adc_to_vol(uint16_t channel, int scale, int mux,
			      int cal_type)
{
	int32_t adc_value[ADC_MESURE_NUMBER + 1] = { 0 };
	int32_t adc_average = 0;
	int32_t vol = 0;
	uint8_t num = ADC_MESURE_NUMBER;

	if (0 == pmic_adc_get_values(channel, scale, num, adc_value)) {
		adc_average =
		    pmic_adc_data_average(&adc_value[num / 5],
					  (num - num * 2 / 5));
	}
	if (cal_type == ADC_SMALL_SCALE) {
		vol = sprd_chan_small_adc_to_vol(channel, scale, mux, adc_average);
	} else if (cal_type == ADC_BIG_SCALE) {
		vol = sprd_chan_bat_adc_to_vol(channel, scale, mux, adc_average);
	} else {
		sprd_err("cal is error\n");
	}

	return vol;
}
