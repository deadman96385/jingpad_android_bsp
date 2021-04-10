#include <common.h>
#include <asm/io.h>
#include "sprd_adc.h"
#include "adi_hal_internal.h"
#include <asm/arch/sprd_reg.h>

#ifdef DEBUG
#undef debug
#define debug(format, arg...) printf("\t" format, ## arg)
#define debug2(format, arg...) printf("\t\t" format, ## arg)
#else
#define debug(format, arg...)
#define debug2(format, arg...)
#endif
#define debug0(format, arg...)

/* abs() handles unsigned and signed longs, ints, shorts and chars.  For all input types abs()
 * returns a signed long.
 * abs() should not be used for 64-bit types (s64, u64, long long) - use abs64() for those.*/
#define abs(x) ({									\
				long ret;							\
				if (sizeof(x) == sizeof(long)) {		\
					long __x = (x);				\
					ret = (__x < 0) ? -__x : __x;		\
				} else {							\
					int __x = (x);					\
					ret = (__x < 0) ? -__x : __x;		\
				}								\
				ret;								\
			})


#undef ffs
#undef fls

/* On ARMv5 and above those functions can be implemented around the clz instruction for
 * much better code efficiency.		*/

static inline int fls(int x)
{
	int ret;

	asm("clz\t%0, %1": "=r"(ret):"r"(x));
	ret = 32 - ret;
	return ret;
}

#define __fls(x) (fls(x) - 1)
#define ffs(x) ({ unsigned long __t = (x); fls(__t & -__t); })
#define __ffs(x) (ffs(x) - 1)
#define ffz(x) __ffs( ~(x) )

#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))

#define MEASURE_TIMES				(15)

#define ADC_DROP_CNT	( DIV_ROUND_CLOSEST(MEASURE_TIMES, 5) )
static int __average(int a[], int N)
{
	int i, sum = 0;
	for (i = 0; i < N; i++)
		sum += a[i];
	return DIV_ROUND_CLOSEST(sum, N);
}

static void bubble_sort(int a[], int N)
{
	int i, j, t;
	for (i = 0; i < N - 1; i++) {
		for (j = i + 1; j < N; j++) {
			if (a[i] > a[j]) {
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
		}
	}
}

int sci_adc_request(int channel)
{
	int i;
	int results[MEASURE_TIMES];

	if (-1 == pmic_adc_get_values(channel, ADC_SCALE_3V, MEASURE_TIMES, results)) {
		return 0;
	}

	bubble_sort(results, MEASURE_TIMES);

	/* dump results */
	for (i = 0; i < MEASURE_TIMES; i++) {
		printf("%d ", results[i]);
	}
	printf("\n");

	return results[MEASURE_TIMES / 2];
}

#define RATIO(_n_, _d_) (_n_ << 16 | _d_)

static int sci_adc_ratio(int channel, int mux)
{
	switch (channel) {
		case 5://vbat
			return RATIO(7, 29);
		case 13://dcdcarm
		case 14://dcdccore
			return RATIO(4, 5);
		case 15://dcdcmem
			return RATIO(3, 5);
		case 16://dcdcgen
			return RATIO(4, 9);
		case 18://dcdcwrf
			return RATIO(1, 3);
		case 21://ldo_mux0
			return RATIO(1, 3);
		case 22://ldo_mux1
			if ((mux & 0xFFFF) == BIT(5))
				return RATIO(1, 3);
			else
				return RATIO(1, 2);
		case 23://ldo_mux2
			return RATIO(1, 3);
		default:
			return RATIO(1, 1);
	}
	return RATIO(1, 1);
}

static u32 bat_numerators, bat_denominators = 0;
extern uint16_t sprdbat_auxadc2vbatvol (uint16_t adcvalue);

int sci_adc_vol_request(int channel, int mux)
{
	int adc_res;
	adc_res = sci_adc_request(channel);
	if (adc_res) {
		u32 res, chan_numerators, chan_denominators;
		res = (u32) sci_adc_ratio(channel, mux);
		chan_numerators = res >> 16;
		chan_denominators = res & 0xffff;
		return sprdbat_auxadc2vbatvol(adc_res)
		    * (bat_numerators * chan_denominators)
		    / (bat_denominators * chan_numerators);
	}
	return 0;
}

/* Simple shorthand for a section definition */
#ifndef __section
# define __section(S) __attribute__ ((__section__(#S)))
#endif

#define __init0	__section(.rodata.regu.init0)
#define __init1	__section(.rodata.regu.init1)
#define __init2	__section(.rodata.regu.init2)

const u32 __init0 __init_begin = 0xeeeebbbb;
const u32 __init2 __init_end = 0xddddeeee;

struct regulator_regs {
	int typ;
	u32 pd_set, pd_set_bit;
	/* at new feature, some LDOs had only set, no rst bits.
	 * and DCDCs voltage and trimming controller is the same register */
	u32 pd_rst, pd_rst_bit;
	u32 slp_ctl, slp_ctl_bit;
	u32 vol_trm, vol_trm_bits;
	u32 cal_ctl, cal_ctl_bits;
	u32 vol_def;
	u32 vol_ctl, vol_ctl_bits;
	u32 vol_sel_cnt, vol_sel[];
};

struct regulator_desc {
	int id;
	const char *name;
	const struct regulator_regs *regs;
};

#define REGU_VERIFY_DLY	(1000)	/*ms */
#define SCI_REGU_REG(VDD, TYP, PD_SET, SET_BIT, PD_RST, RST_BIT, SLP_CTL, SLP_CTL_BIT, \
                     VOL_TRM, VOL_TRM_BITS, CAL_CTL, CAL_CTL_BITS, VOL_DEF,	\
                     VOL_CTL, VOL_CTL_BITS, VOL_SEL_CNT, ...)					\
	static const struct regulator_regs REGS_##VDD = {						\
		.typ = TYP,							\
		.pd_set = PD_SET, 					\
		.pd_set_bit = SET_BIT,					\
		.pd_rst = PD_RST,						\
		.pd_rst_bit = RST_BIT,					\
		.slp_ctl = SLP_CTL,						\
		.slp_ctl_bit = SLP_CTL_BIT,				\
		.vol_trm = VOL_TRM,					\
		.vol_trm_bits = VOL_TRM_BITS,			\
		.cal_ctl = CAL_CTL,					\
		.cal_ctl_bits = CAL_CTL_BITS,			\
		.vol_def = VOL_DEF,					\
		.vol_ctl = VOL_CTL,					\
		.vol_ctl_bits = VOL_CTL_BITS,			\
		.vol_sel_cnt = VOL_SEL_CNT,			\
		.vol_sel = {__VA_ARGS__},				\
	};										\
	struct regulator_desc __init1 DESC_##VDD = {	\
		.id = -1,								\
		.name = #VDD,						\
		.regs = &REGS_##VDD,					\
	};										\


#include "sprd_reg_regulator_map.h"


typedef struct dcdc_cali_tag
{
	char name[32];
	int	cali_vol;								/* ctl_vol - to_vol */
} dcdc_cali_t;

#define CALI_VOL_ADDR						0x1F00
#define CALI_VOL_ADDR_NUM					8

static dcdc_cali_t* get_cali_addr()
{
	dcdc_cali_t *p = (dcdc_cali_t *)CALI_VOL_ADDR;
	u32 i = 0;

	while ((*(u32 *)p != 0) && (i < 4))
	{
		p++;
		i++;
	}

	if (i >= 4)
		return (dcdc_cali_t*)0;
	else
		return p;
}

/* standard dcdc ops*/
static int __dcdc_is_orig(struct regulator_desc *desc)
{
	if (0 == strcmp(desc->name, "vddmem") || 0 == strcmp(desc->name, "vddwrf"))
		if (ANA_REG_GET(ANA_REG_GLB_CHIP_ID_LOW) & 0xff) /* BA CHIP */
			return 0;
	return 1;
}

static int dcdc_get_trimming_step(struct regulator_desc *desc, int to_vol)
{
	/* FIXME: vddmem step 200/32mV */
	if (0 == strcmp(desc->name, "vddmem") || 0 == strcmp(desc->name, "vddwrf"))
	{
		return 1000 * 200 / 32;	/*uV */
	}
	return 1000 * 100 / 32;	/*uV */
}

static int __match_dcdc_vol(struct regulator_desc *desc, u32 vol)
{
	int i, j = -1;
	int ds, min_ds = 100;	/* mV, the max range of small voltage */
	const struct regulator_regs *regs = desc->regs;

	for (i = 0; i < regs->vol_sel_cnt; i++) {
		ds = vol - regs->vol_sel[i];
		if (ds >= 0 && ds < min_ds) {
			min_ds = ds;
			j = i;
		}
	}

	if (j < 0 && !__dcdc_is_orig(desc)) {
		for (i = 0; i < regs->vol_sel_cnt; i++) {
			ds = abs(vol - regs->vol_sel[i]);
			if (ds < min_ds) {
				min_ds = ds;
				j = i;
			}
		}
	}

	return j;
}

static int dcdc_get_voltage(struct regulator_desc *desc)
{
	const struct regulator_regs *regs = desc->regs;
	u32 mv;
	int cal = 0;		/* uV */
	int i, shft = __ffs(regs->vol_ctl_bits);

	i = (ANA_REG_GET(regs->vol_ctl) & regs->vol_ctl_bits) >> shft;
	mv = regs->vol_sel[i];

	cal = (ANA_REG_GET(regs->vol_trm) & regs->vol_trm_bits) >> __ffs(regs->vol_trm_bits);
	if (!__dcdc_is_orig(desc)) {
		cal -= 0x10;
	}
	cal *= dcdc_get_trimming_step(desc, 0);	/*uV */

	debug0("%s %d +%dmv\n", desc->name, mv, cal / 1000);
	return mv + cal / 1000;
}

static int dcdc_set_voltage(struct regulator_desc *desc, int min_mV, int max_mV)
{
	const struct regulator_regs *regs = desc->regs;
	int i, mv = min_mV;

	/* found the closely vol ctrl bits */
	i = __match_dcdc_vol(desc, mv);
	if (i < 0) {
		debug2("%s: %s failed to match voltage: %d\n",__func__,desc->name,mv);
		return -1;
	}

	/* dcdc calibration control bits (default 0) small adjust voltage: 100/32mv ~= 3.125mv */
	{
		int shft = __ffs(regs->vol_ctl_bits);
		int j = (mv - (int)regs->vol_sel[i]) * 1000 / dcdc_get_trimming_step(desc, mv);

		if (!__dcdc_is_orig(desc))
			j += 0x10;

		debug2("regu_dcdc %p (%s) %d = %d %+dmv (trim=%d);\n", regs, desc->name,
			   mv, regs->vol_sel[i], mv - regs->vol_sel[i], j);

		if (j >= 0 && j < 32)
			ANA_REG_MSK_OR(regs->vol_ctl, j | (i << shft),
				regs->vol_trm_bits | regs->vol_ctl_bits);
	}
	return 0;
}

static int dcdc_set_trimming(struct regulator_desc *desc, int def_vol, int to_vol, int adc_vol)
{
	dcdc_cali_t *p = NULL;
	int acc_vol = dcdc_get_trimming_step(desc, to_vol) / 1000;

	/*FIXME: no need division?
	int ctl_vol = DIV_ROUND_UP(def_vol * to_vol * 1000, adc_vol) + acc_vol;	*/
	int ctl_vol = (def_vol - (adc_vol - to_vol)) + acc_vol;

	p = get_cali_addr();
	if (p != 0) {
		strcpy(p->name, desc->name);
		p->cali_vol = ctl_vol - to_vol;
	}

	return dcdc_set_voltage(desc, ctl_vol, ctl_vol);
}

static int ldo_get_voltage(struct regulator_desc *desc)
{
	const struct regulator_regs *regs = desc->regs;
	u32 vol;

	if (regs->vol_trm && regs->vol_sel_cnt == 2) {
		int shft = __ffs(regs->vol_trm_bits);
		u32 trim =
		    (ANA_REG_GET(regs->vol_trm) & regs->vol_trm_bits) >> shft;
		vol = regs->vol_sel[0] * 1000 + trim * regs->vol_sel[1];
		vol /= 1000;
		debug0("%s voltage %dmv\n", desc->name, vol);
		return vol;
	}

	return -1;
}

/* ldo trimming step about 0.625%, range 90% ~ 109.375%. that all maps as follow.

	0x1F :  +9.375 : 109.375
	0x1E :  +8.750 : 108.750
	0x1D :  +8.125 : 108.125
	0x1C :  +7.500 : 107.500
	0x1B :  +6.875 : 106.875
	0x1A :  +6.250 : 106.250
	0x19 :  +5.625 : 105.625
	0x18 :  +5.000 : 105.000
	0x17 :  +4.375 : 104.375
	0x16 :  +3.750 : 103.750
	0x15 :  +3.125 : 103.125
	0x14 :  +2.500 : 102.500
	0x13 :  +1.875 : 101.875
	0x12 :  +1.250 : 101.250
	0x11 :  +0.625 : 100.625
	0x10 :  +0.000 : 100.000
	0x0F :  -0.625 : 99.375
	0x0E :  -1.250 : 98.750
	0x0D :  -1.875 : 98.125
	0x0C :  -2.500 : 97.500
	0x0B :  -3.125 : 96.875
	0x0A :  -3.750 : 96.250
	0x09 :  -4.375 : 95.625
	0x08 :  -5.000 : 95.000
	0x07 :  -5.625 : 94.375
	0x06 :  -6.250 : 93.750
	0x05 :  -6.875 : 93.125
	0x04 :  -7.500 : 92.500
	0x03 :  -8.125 : 91.875
	0x02 :  -8.750 : 91.250
	0x01 :  -9.375 : 90.625
	0x00 : -10.000 : 90.000
*/
static int ldo_set_trimming(struct regulator_desc *desc, int def_vol, int to_vol, int adc_vol)
{
	const struct regulator_regs *regs = desc->regs;
	int ret = -1;

	if (regs->vol_trm) {
		/* assert 5 valid trim bits, R = V_IDEAL / V_ADCIN - 1 */
		u32 trim = DIV_ROUND_UP((to_vol * 100 - adc_vol * 90) * 32, (adc_vol * 20));
		if (trim > BIT(5) - 1)
			goto exit;
		debug2("regu %p (%s) trimming %d = %d %+d%%, got [%02X]\n",
			regs, desc->name, to_vol, adc_vol, (trim * 20 / 32 - 10), trim);

		ANA_REG_MSK_OR(regs->vol_trm,
						trim << __ffs(regs->vol_trm_bits),
						regs->vol_trm_bits);
		ret = 0;
	}

exit:
	return ret;
}

static int dcdc_get_trimming_vol(struct regulator_desc *desc)
{
	int shft, trm_vol = 0;
	int tmpVal;

	shft = __ffs(desc->regs->vol_trm_bits);
	tmpVal = (ANA_REG_GET(desc->regs->vol_trm) & desc->regs->vol_trm_bits) >> shft;

	if (!__dcdc_is_orig(desc))
		tmpVal -= 0x10;

	trm_vol = tmpVal * (dcdc_get_trimming_step(desc, trm_vol))/1000;

	return trm_vol;
}

static int DCDC_Cal_One(struct regulator_desc *desc, int is_cal)
{
	struct regulator_regs *regs = desc->regs;
	int def_vol = 0, to_vol = 0;
	int adc_vol = 0, cal_vol = 0;
	int ret = -1, adc_chan = regs->cal_ctl_bits >> 16;
	u16 ldo_cal_sel = regs->cal_ctl_bits & 0xFFFF;

	if (!adc_chan || !regs->vol_def)
		return -1;

	if (ldo_cal_sel)
		ANA_REG_OR(regs->cal_ctl, ldo_cal_sel);

	{
		u16 tmpVal;
		tmpVal = (ANA_REG_GET(regs->vol_ctl) & regs->vol_ctl_bits) >> __ffs(regs->vol_ctl_bits);
		if (regs->typ == 2)
			def_vol = to_vol = (int)regs->vol_sel[tmpVal] + dcdc_get_trimming_vol(desc);
		else if (regs->typ == 0)
			def_vol = to_vol = regs->vol_sel[tmpVal];
	}

	adc_vol = sci_adc_vol_request(adc_chan, ldo_cal_sel);
	if (adc_vol <= 0) {
		debug("%s default %dmv, maybe not enable\n", desc->name, def_vol);
		goto exit;
	}

	cal_vol = abs(adc_vol - to_vol);
	debug("%s default %dmv, from %dmv to %dmv, bias %c%d.%03d%%\n",
	      desc->name, def_vol, adc_vol, to_vol,
	      (adc_vol > to_vol) ? '+' : '-',
	      cal_vol * 100 / to_vol, cal_vol * 100 * 1000 / to_vol % 1000);

	if (!def_vol || !to_vol || adc_vol <= 0)
		goto exit;

	if (abs(adc_vol - def_vol) >= def_vol / 10)	/* adjust limit 10% */
		goto exit;
	else if (cal_vol < to_vol / 100) {	/* bias 1% */
		goto exit;
	}
	else if (is_cal) {
		if (regs->typ == 2/*VDD_TYP_DCDC*/)
			ret = dcdc_set_trimming(desc, def_vol, to_vol, adc_vol);
		else if (regs->typ == 0/*VDD_TYP_LDO*/)
			ret = ldo_set_trimming(desc, def_vol, to_vol, adc_vol);
	}

exit:
	if (ldo_cal_sel)
		ANA_REG_BIC(regs->cal_ctl, ldo_cal_sel);

	return 0;
}

int DCDC_Cal_ArmCore(void)
{
	u16 regVal;
	u32 res;
	struct regulator_desc *desc = NULL;
	struct regulator_desc *desc_end = NULL;

	printf("%s\n", __FUNCTION__);

	/* mem arm core bits are [11:9]*/
	regVal = ANA_REG_GET(ANA_REG_GLB_LDO_DCDC_PD_RTCCLR);
	regVal |= BIT(11) | BIT(10) | BIT(9);
	ANA_REG_SET(ANA_REG_GLB_LDO_DCDC_PD_RTCCLR, regVal);

	/* enable sim0, sim2. */
	regVal = ANA_REG_GET(ANA_REG_GLB_LDO_PD_CTRL);
	regVal &= ~(BIT(2) | BIT(4));
	ANA_REG_SET(ANA_REG_GLB_LDO_PD_CTRL, regVal);

	/* FIXME: Update CHGMNG_AdcvalueToVoltage table before setup vbat ratio. */
	/*ADC_CHANNEL_VBAT is 5*/
	res = (u32) sci_adc_ratio(5, 0);
	bat_numerators = res >> 16;
	bat_denominators = res & 0xffff;

	/* initialize 4 struct free */
	memset((u8 *)CALI_VOL_ADDR , 0x00, (sizeof(dcdc_cali_t) * (CALI_VOL_ADDR_NUM)));

	/* TODO: calibrate all DCDCs */
	desc = (struct regulator_desc *)(&__init_begin + 1);

	printf("%p (%x) -- %p -- %p (%x)\n", &__init_begin, __init_begin,
		desc, &__init_end, __init_end);

	while (desc < (struct regulator_desc *)&__init_end) {
		if ((0 == strcmp("vddmem", desc->name))
			|| (0 == strcmp("vddarm", desc->name))
			|| (0 == strcmp("vddcore", desc->name))
			|| (0 == strcmp("vddsim0", desc->name))
			|| (0 == strcmp("vddsim2", desc->name))) {

			printf("\nCalibrate %s ...\n", desc->name);
			DCDC_Cal_One(desc, 1);
		}

		desc++;
	}

	/* wait a moment for LDOs ready */
	udelay(200 * 1000);

	/* TODO: verify all DCDCs */
	desc = (struct regulator_desc *)(&__init_begin + 1);

	while (desc < (struct regulator_desc *)&__init_end) {
		if ((0 == strcmp("vddmem", desc->name))
			|| (0 == strcmp("vddarm", desc->name))
			|| (0 == strcmp("vddcore", desc->name))
			|| (0 == strcmp("vddsim0", desc->name))
			|| (0 == strcmp("vddsim2", desc->name))) {

			printf("\nVerify %s ...\n", desc->name);
			DCDC_Cal_One(desc, 0);
		}

		desc++;
	}

	/* disable sim0, sim2. */
	regVal |= (BIT(2) | BIT(4));
	ANA_REG_SET(ANA_REG_GLB_LDO_PD_CTRL, regVal);

	return 0;
}

