/*
 * Copyright (C) 2018 Spreadtrum Communications Inc.
 */

#include <timer.h>
#include <common.h>
#include <adi.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_chipram_env.h>

typedef unsigned int u32;


/* ADC controller registers definition */
#define SC27XX_ADC_CTL			(ANA_ADC_BASE + 0x0004)
#define SC27XX_ADC_CH_CFG		(ANA_ADC_BASE + 0x0008)
#define SC27XX_ADC_DATA			(ANA_ADC_BASE + 0x0050)
#define SC27XX_ADC_INT_EN		(ANA_ADC_BASE + 0x0054)
#define SC27XX_ADC_INT_CLR		(ANA_ADC_BASE + 0x0058)
#define SC27XX_ADC_INT_STS		(ANA_ADC_BASE + 0x005c)
#define SC27XX_ADC_INT_RAW		(ANA_ADC_BASE + 0x0060)
#define SC27XX_ADC_CTL0			(ANA_ADC_BASE + 0x00b0)

/* SC27XX_ADC_CTL */
#define SC27XX_ADC_OFFSET_CAL_EN	BIT(12)
#define SC27XX_AUXAD_AVERAGE(x)		(((x) & 0x7) << 8)
#define SC27XX_SW_CH_RUN_NUM(x)		((((x) - 1) & 0xF ) << 4)
#define SC27XX_SW_CH_NUM_MSK		(BIT(4) | BIT(5) | BIT(6) | BIT(7))
#define SC27XX_ADC_MODE_12B		BIT(2)
#define SC27XX_SW_CH_ON_BIT		BIT(1)
#define SC27XX_ADC_EN_BIT		BIT(0)

/* SC27XX_ADC_CH_CFG */
#define SC27XX_CH_SCALE(x)		(((x) & 0x3) << 9)
#define SC27XX_ADC_CS_MSK		0x1f

#define SC27XX_ADC_IRQ_EN		BIT(0)
#define SC27XX_ADC_IRQ_CLR		BIT(0)
#define SC27XX_ADC_IRQ_RAW		BIT(0)
#define SC27XX_ADC_DATA_MSK		0xfff

/* SC27XX_ADC_CTL0 */
#define SC27XX_ADC_CUR_EN		BIT(0)

#define SC27XX_ADC_MESURE_NUMBER	15
#define SC27XX_ADC_CHAN_MAX		31

/* ADC voltage ratio definition */
#define SC27XX_VOLT_RATIO(n, d)		(n << 16 | d)
#define SC27XX_RATIO_NUMERATOR_OFFSET	16
#define SC27XX_RATIO_DENOMINATOR_MASK	0xffff
#define SC27XX_SMALL_CAL_BLK		19
#define SC27XX_BIG_CAL_BLK		18

extern u32 sc27xx_efuse_read(int blk_index, u32 *val);
extern void udelay(uint32 us);

u32 efuse_data = 0, adc_data = 0;
int vol_data = 0;

struct sc27xx_adc_linear_graph {
	int volt0;
	int adc0;
	int volt1;
	int adc1;
};

/*
 * According to the datasheet, we can convert one ADC value to one voltage value
 * through 2 points in the linear graph. If the voltage is less than 1.2v, we
 * should use the small-scale graph, and if more than 1.2v, we should use the
 * big-scale graph.
 */
static struct sc27xx_adc_linear_graph big_scale_graph = {
	4200, 3310,
	3600, 2832,
};

static struct sc27xx_adc_linear_graph small_scale_graph = {
	1000, 3413,
	100, 341,
};

static const struct sc27xx_adc_linear_graph big_scale_graph_calib = {
	4200, 856,
	3600, 733,
};

static const struct sc27xx_adc_linear_graph small_scale_graph_calib = {
	1000, 833,
	100, 80,
};

static int sc27xx_adc_get_calib_data(u32 calib_data, int calib_adc)
{
	return ((calib_data & 0xff) + calib_adc - 128) * 4;
}

static int sc27xx_adc_scale_calibration(bool big_scale)
{
	const struct sc27xx_adc_linear_graph *calib_graph;
	struct sc27xx_adc_linear_graph *graph;
	u32 calib_data = 0;
	int blk_num, ret;

	if (big_scale) {
		calib_graph = &big_scale_graph_calib;
		graph = &big_scale_graph;
		blk_num = SC27XX_BIG_CAL_BLK;
	} else {
		calib_graph = &small_scale_graph_calib;
		graph = &small_scale_graph;
		blk_num = SC27XX_SMALL_CAL_BLK;
	}

	ret = sc27xx_efuse_read(blk_num, &calib_data);
	if(ret)
		return ret;
	calib_data &= 0xFFFF;
	efuse_data = calib_data;

	/* Only need to calibrate the adc values in the linear graph. */
	graph->adc0 = sc27xx_adc_get_calib_data(calib_data, calib_graph->adc0);
	graph->adc1 = sc27xx_adc_get_calib_data(calib_data >> 8, calib_graph->adc1);
	return 0;
}

static int sc2730_adc_get_ratio(int channel, int scale)
{
	switch (channel) {
	case 14:
		switch (scale) {
		case 0:
			return SC27XX_VOLT_RATIO(68, 900);
		case 1:
			return SC27XX_VOLT_RATIO(68, 1760);
		case 2:
			return SC27XX_VOLT_RATIO(68, 2327);
		case 3:
			return SC27XX_VOLT_RATIO(68, 3654);
		default:
			return SC27XX_VOLT_RATIO(1, 1);
		}
	case 15:
		switch (scale) {
		case 0:
			return SC27XX_VOLT_RATIO(1, 3);
		case 1:
			return SC27XX_VOLT_RATIO(1000, 5865);
		case 2:
			return SC27XX_VOLT_RATIO(500, 3879);
		case 3:
			return SC27XX_VOLT_RATIO(500, 6090);
		default:
			return SC27XX_VOLT_RATIO(1, 1);
		}
	case 16:
		switch (scale) {
		case 0:
			return SC27XX_VOLT_RATIO(48, 100);
		case 1:
			return SC27XX_VOLT_RATIO(480, 1955);
		case 2:
			return SC27XX_VOLT_RATIO(480, 2586);
		case 3:
			return SC27XX_VOLT_RATIO(48, 406);
		default:
			return SC27XX_VOLT_RATIO(1, 1);
		}
	case 21:
	case 22:
	case 23:
		switch (scale) {
		case 0:
			return SC27XX_VOLT_RATIO(3, 8);
		case 1:
			return SC27XX_VOLT_RATIO(375, 1955);
		case 2:
			return SC27XX_VOLT_RATIO(375, 2586);
		case 3:
			return SC27XX_VOLT_RATIO(300, 3248);
		default:
			return SC27XX_VOLT_RATIO(1, 1);
		}
	default:
		switch (scale) {
		case 0:
			return SC27XX_VOLT_RATIO(1, 1);
		case 1:
			return SC27XX_VOLT_RATIO(1000, 1955);
		case 2:
			return SC27XX_VOLT_RATIO(1000, 2586);
		case 3:
			return SC27XX_VOLT_RATIO(1000, 4060);
		default:
			return SC27XX_VOLT_RATIO(1, 1);
		}
	}
	return SC27XX_VOLT_RATIO(1, 1);
}

static void sc27xx_adc_volt_ratio(int channel, int scale,
				  u32 *div_numerator, u32 *div_denominator)
{
	u32 ratio;

	ratio = sc2730_adc_get_ratio(channel, scale);
	*div_numerator = ratio >> SC27XX_RATIO_NUMERATOR_OFFSET;
	*div_denominator = ratio & SC27XX_RATIO_DENOMINATOR_MASK;
}

static int sc27xx_adc_to_volt(struct sc27xx_adc_linear_graph *graph,
			      int raw_adc)
{
	int tmp;

	tmp = (graph->volt0 - graph->volt1) * (raw_adc - graph->adc1);
	tmp /= (graph->adc0 - graph->adc1);
	tmp += graph->volt1;

	return tmp < 0 ? 0 : tmp;
}

static u32 sc27xx_adc_read(int channel, int scale, int num, u32 *val)
{
	u32 count;

	ANA_REG_OR(SC27XX_ADC_INT_CLR, SC27XX_ADC_IRQ_CLR);
	ANA_REG_MSK_OR(SC27XX_ADC_CH_CFG, channel, SC27XX_ADC_CS_MSK);
	ANA_REG_MSK_OR(SC27XX_ADC_CH_CFG, SC27XX_CH_SCALE(scale), SC27XX_CH_SCALE(~0));
	ANA_REG_MSK_OR(SC27XX_ADC_CTL, SC27XX_SW_CH_RUN_NUM(num), SC27XX_SW_CH_NUM_MSK);
	ANA_REG_OR(SC27XX_ADC_CTL, SC27XX_SW_CH_ON_BIT);

	/* wait adc complete */
	count = 3000;
	while (!(ANA_REG_GET(SC27XX_ADC_INT_RAW) & SC27XX_ADC_IRQ_RAW) && count--) {
		udelay(10);
	}
	if (count <= 0) {
		return -1;
	}

	*val = ANA_REG_GET(SC27XX_ADC_DATA) & SC27XX_ADC_DATA_MSK;

	/* turn off adc soft channel */
	ANA_REG_AND(SC27XX_ADC_CTL, ~SC27XX_SW_CH_ON_BIT);
	ANA_REG_MSK_OR(SC27XX_ADC_CTL, SC27XX_SW_CH_RUN_NUM(1), SC27XX_SW_CH_NUM_MSK);
	ANA_REG_OR(SC27XX_ADC_INT_CLR, SC27XX_ADC_IRQ_CLR);

	return 0;
}

/*for sc2731/sc2721/2730 if set 1.25uA, parameter isen is 125uA */
static int sc27xx_adc_para_isen(int isen)
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

static void sc27xx_adc_set_isen(u8 enable, int isen)
{
	int isen_bit;

	if (enable) {
		isen_bit = sc27xx_adc_para_isen(isen);
		ANA_REG_AND(ANA_REG_GLB_IB_CTRL, ~BIT_IB_REX_EN);
		ANA_REG_OR(ANA_REG_GLB_IB_CTRL, BIT_BATDET_CUR_EN);
		ANA_REG_MSK_OR(ANA_REG_GLB_IB_CTRL, BITS_BATDET_CUR_I(isen_bit),
					   BITS_BATDET_CUR_I(~0));
		udelay(150);
	} else {
		ANA_REG_AND(ANA_REG_GLB_IB_CTRL, ~(BITS_BATDET_CUR_I(~0)));
		ANA_REG_AND(ANA_REG_GLB_IB_CTRL, ~BIT_BATDET_CUR_EN);
	}
}

static int sc27xx_adc_set_current(u8 enable, int isen)
{
	if (enable) {
		sc27xx_adc_set_isen(enable, isen);
		ANA_REG_OR(SC27XX_ADC_CTL0, SC27XX_ADC_CUR_EN);
	} else {
		ANA_REG_AND(SC27XX_ADC_CTL0, ~SC27XX_ADC_CUR_EN);
		sc27xx_adc_set_isen(enable, isen);
	}

	return 0;
}

int sc27xx_adc_get_value_by_isen(int chan, int scale, int num,
				   int isen, u32 *val)
{
	int ret;

	sc27xx_adc_set_current(1, isen);
	ret = sc27xx_adc_read(chan, scale, num, val);
	sc27xx_adc_set_current(0, 0);

	return ret;
}

static int sc27xx_adc_convert_volt(int channel, int scale, int raw_adc)
{
	u32 numerator, denominator;
	u32 volt;

	/*
	 * Convert ADC values to voltage values according to the linear graph,
	 * and channel 5 and channel 1 has been calibrated, so we can just
	 * return the voltage values calculated by the linear graph. But other
	 * channels need be calculated to the real voltage values with the
	 * voltage ratio.
	 */
	switch (channel) {
	case 5:
		return sc27xx_adc_to_volt(&big_scale_graph, raw_adc);

	case 1:
		return sc27xx_adc_to_volt(&small_scale_graph, raw_adc);

	default:
		volt = sc27xx_adc_to_volt(&small_scale_graph, raw_adc);
		break;
	}

	sc27xx_adc_volt_ratio(channel, scale, &numerator, &denominator);

	return (volt * denominator + numerator / 2) / numerator;
}

int sc27xx_adc_init(void)
{
	int ret;

	ANA_REG_OR(ANA_REG_GLB_MODULE_EN0, BIT_ADC_EN);
	ANA_REG_OR(ANA_REG_GLB_ARM_CLK_EN0, BIT_CLK_AUXAD_EN | BIT_CLK_AUXADC_EN);
	ANA_REG_OR(ANA_REG_GLB_XTL_WAIT_CTRL0, BIT_XTL_EN);
	ANA_REG_OR(SC27XX_ADC_CTL, SC27XX_ADC_EN_BIT);
	ANA_REG_OR(SC27XX_ADC_CTL, SC27XX_ADC_OFFSET_CAL_EN);
	ANA_REG_MSK_OR(SC27XX_ADC_CTL, SC27XX_AUXAD_AVERAGE(0x5), SC27XX_AUXAD_AVERAGE(~0));

	/* ADC channel scales' calibration from nvmem device */
	ret = sc27xx_adc_scale_calibration(true);
	if (ret)
		return ret;

	ret = sc27xx_adc_scale_calibration(false);
	if (ret)
		return ret;

	return 0;
}

int sc27xx_adc_read_processed(int channel, int scale, int *val)
{
	u32 raw_adc = 0;
	int ret;

	ret = sc27xx_adc_read(channel, scale, 1, &raw_adc);
	*val = sc27xx_adc_convert_volt(channel, scale, raw_adc);

	return ret;
}

int sc27xx_adc_current_mode_vol(int chan, int scale, int isen, int *val)
{
	u32 raw_adc = 0;
	int ret;

	ret = sc27xx_adc_get_value_by_isen(chan, scale, 1, isen, &raw_adc);
	*val = sc27xx_adc_convert_volt(chan, scale, raw_adc);

	adc_data = raw_adc;
	vol_data = *val;

	return ret;
}
