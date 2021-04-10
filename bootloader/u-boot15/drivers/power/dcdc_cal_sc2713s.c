#include <common.h>
#include <asm/io.h>
#include "sprd_adc.h"
#include "adi_hal_internal.h"
#include <asm/arch/sprd_reg.h>
#include <chipram_env.h>

int regulator_default_get(const char con_id[]);
void regulator_default_set(const char con_id[], int vol);
int regulator_default_set_all(void);
u32 regulator_get_calibration_mask(void);

typedef void (*pfun)(int);
static pfun calibrate_post = NULL;

#define REGU_CALI_DEBUG

#ifdef REGU_CALI_DEBUG
#define regu_debug(fmt, arg...)		printf(fmt, ## arg)
#else
#define regu_debug(fmt, arg...)
#endif

#undef debug
#define debug0(format, arg...)
#define debug(format, arg...)		regu_debug(format, ## arg)
#define debug1(format, arg...)		regu_debug("\t" format, ## arg)
#define debug2(format, arg...)		regu_debug("\t\t" format, ## arg)


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

typedef struct {
	u16 ideal_vol;
	const char name[14];
}vol_para_t;

vol_para_t *ppvol_para;
extern chipram_env_t  local_chipram_env;
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

/*************************************************************************
Reg: 0x40038800 + 0x00E4
--------------------------------------------
BIT    |    FieldName    |    Description
--------------------------------------------
BIT7~BIT15  Reserved
BIT6	BONDOPT6		28nm/40nm dcdccore/dcdcarm default voltage select:
						0: dcdccore/dcdcarm = 1.1v, vdd25 = 2.5v
						1: dcdccore/dcdcarm = 0.9v, vdd25 = 1.8v
BIT5	BONDOPT5		crystal 32k buffer select:
						0: new low power 32k buffer output, 1: backup 32k buffer output
BIT4	BONDOPT4		dcdcwrf out voltage select:  dcdc_wrf_ctl[2]
BIT3	BONDOPT3		charge mode option:
						0: continues charging, 1: dcdc mode charging
BIT2	BONDOPT2		dcdcmem option 2:  dcdc_mem_ctl[2]
BIT1	BONDOPT1		dcdcmem option 1:  dcdc_mem_ctl[1]
						00: DDR2 (1.2v)
						01: DDR3L (1.35v)
						10: DDR3 (1.5v)
						11: DDR1 (1.8v)
BIT0	BONDOPT0		New power on reset option:
						0: manual power on without hardware debounce
						1: auto power on with 1s hardware debounce
**************************************************************************/
static u16 ana_status;

//static volatile int loop = 1;

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

static int sci_adc_request(int channel, int scale)
{
	int results[MEASURE_TIMES];

	if (-1 == pmic_adc_get_values(channel, scale, MEASURE_TIMES, results)) {
		return 0;
	}

	bubble_sort(results, MEASURE_TIMES);

#if 0
{
	int i;

	/* dump results */
	for (i = 0; i < MEASURE_TIMES; i++) {
		printf("%d ", results[i]);
	}
	printf("\n");
}
#endif

	return __average(&results[ADC_DROP_CNT], MEASURE_TIMES - ADC_DROP_CNT * 2);
}

#define RATIO(_n_, _d_) (_n_ << 16 | _d_)

static int sci_adc_ratio(int channel, int scale, int mux)
{
	switch (channel) {
	case 0x00:
	case 0x01:
	case 0x02:
	case 0x03:
		return ((ADC_SCALE_3V == scale) ? RATIO(16, 41) : RATIO(1, 1));
	case 0x05:	//vbat
	case 0x08:	//isense
		return RATIO(7, 29);
	case 0x06:	//charge sense
		return RATIO(77, 1024);
	case 0x09:	//TP YD
	case 0x0A:	//TP YU
	case 0x0B:	//TP XR
	case 0x0C:	//TP XL
		return ((ADC_SCALE_3V == scale) ? RATIO(2, 5) : RATIO(3, 5));
	case 0x0D:	//dcdccore
	case 0x0E:	//dcdcarm
		return ((ADC_SCALE_3V == scale) ? RATIO(4, 5) : RATIO(1, 1));
	case 0x0F:	//dcdcmem
		return ((ADC_SCALE_3V == scale) ? RATIO(3, 5) : RATIO(4, 5));
    case 0x10: //dcdcgen
		return RATIO(4, 9);
	case 0x11: //dcdcgpu
		return ((ADC_SCALE_3V == scale) ? RATIO(4, 5) : RATIO(1, 1));
	case 0x12: //dcdcwrf
		return ((ADC_SCALE_3V == scale) ? RATIO(1, 3) : RATIO(4, 5));
	case 0x13: //VBATBK
	case 0x15: //ldo_mux0
	case 0x17: //ldo_mux2
	case 0x1E: //USBDP
	case 0x1F: //USBDM
		return RATIO(1, 3);
	case 0x16: //ldo_mux1
		if ((mux & 0xFFFF) == BIT(5))
			return RATIO(1, 3);
		else
			return RATIO(1, 2);
	default:
		return RATIO(1, 1);
	}

	return RATIO(1, 1);
}


static u32 bat_numerators, bat_denominators = 0;
extern uint16_t sprdbat_auxadc2vbatvol (uint16_t adcvalue);

static int sci_adc_vol_request(int channel, int scale, int mux, int* adc)
{
	int chan_adc, chan_vol;

	if(0 == bat_denominators) {
		u32 res;
		/* FIXME: Update CHGMNG_AdcvalueToVoltage table before setup vbat ratio. */
		/* ADC_CHANNEL_VBAT is 5 */
		res = (u32) sci_adc_ratio(5, ADC_SCALE_3V, 0);
		bat_numerators = res >> 16;
		bat_denominators = res & 0xffff;
	}

	chan_adc = sci_adc_request(channel, scale);
	if (chan_adc) {
		if(adc)
			*adc = chan_adc;

		chan_vol = sprdbat_auxadc2vbatvol(chan_adc);
		if(ADC_SCALE_3V == scale) {
			u32 res, chan_numerators, chan_denominators;
			res = (u32) sci_adc_ratio(channel, scale, mux);
			chan_numerators = res >> 16;
			chan_denominators = res & 0xffff;

		    chan_vol *= (bat_numerators * chan_denominators);
			chan_vol /= (bat_denominators * chan_numerators);
		}
		return chan_vol;
	}
	return 0;
}

/* Simple shorthand for a section definition */
#ifndef __section
# define __section(S) __attribute__ ((__section__(#S)))
#endif

#define __init0	__section(.rodata.regu_2713s.init0)
#define __init1	__section(.rodata.regu_2713s.init1)
#define __init2	__section(.rodata.regu_2713s.init2)

static const u32 __init0 __init_begin = 0xeeeebbbb;
static const u32 __init2 __init_end = 0xddddeeee;

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
	struct regulator_regs *regs;
};

#define REGU_VERIFY_DLY	(1000)	/*ms */
#define SCI_REGU_REG(VDD, TYP, PD_SET, SET_BIT, PD_RST, RST_BIT, SLP_CTL, SLP_CTL_BIT, \
                     VOL_TRM, VOL_TRM_BITS, CAL_CTL, CAL_CTL_BITS, VOL_DEF,	\
                     VOL_CTL, VOL_CTL_BITS, VOL_SEL_CNT, ...)					\
	static struct regulator_regs REGS_##VDD = {						\
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
	struct regulator_desc __init1 S_DESC_##VDD = {	\
		.id = -1,								\
		.name = #VDD,						\
		.regs = &REGS_##VDD,					\
	};										\

#include "__sc2713s_regulator_map.h"

/* standard dcdc ops*/
static int dcdc_initial_value(struct regulator_desc *desc)
{
	return ((0 == strcmp(desc->name, "vddmem")) ? 0x10 : 0);
}

static int dcdc_get_trimming_step(struct regulator_desc *desc, int to_vol)
{
	if ((0 == strcmp(desc->name, "vddmem")) ||
		(0 == strcmp(desc->name, "vddwrf"))) { /* FIXME: vddmem/vddwrf step 200/32mV */
		return 1000 * 200 / 32;	/*uV */
	}
	return 1000 * 100 / 32;	/*uV */
}

static int __match_vol(struct regulator_desc *desc, u32 vol)
{
	int i, j = -1;
	int ds, min_ds = 100;	/* mV, the max range of small voltage */
	struct regulator_regs *regs = desc->regs;

	for (i = 0; i < regs->vol_sel_cnt; i++) {
		ds = vol - regs->vol_sel[i];
		if (ds >= 0 && ds < min_ds) {
			min_ds = ds;
			j = i;
		}
	}

	if ((2 == regs->typ) && (j < 0)) {
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
	int cal = 0; /* uV */
	int i, shft = __ffs(regs->vol_ctl_bits);

	BUG_ON(regs->vol_sel_cnt > 8);

	i = (ANA_REG_GET(regs->vol_ctl) & regs->vol_ctl_bits) >> shft;
	mv = regs->vol_sel[i];

	if (regs->vol_trm) {
		cal = (ANA_REG_GET(regs->vol_trm) & regs->vol_trm_bits) >> __ffs(regs->vol_trm_bits);
		cal -= dcdc_initial_value(desc);

		cal *= dcdc_get_trimming_step(desc, 0);	/*uV */
	}

	debug0("%s %d +%dmv\n", desc->name, mv, cal / 1000);
	return (mv + cal / 1000);
}

static int dcdc_set_voltage(struct regulator_desc *desc, int min_mV, int max_mV)
{
	const struct regulator_regs *regs = desc->regs;
	int i, mv = min_mV;

	/* found the closely vol ctrl bits */
	i = __match_vol(desc, mv);
	if (i < 0) {
		debug2("%s: %s failed to match voltage: %d\n",__func__,desc->name,mv);
		return -1;
	}

	/* dcdc calibration control bits (default 0) small adjust voltage: 100/32mv ~= 3.125mv */
	{
		int shft_ctl = __ffs(regs->vol_ctl_bits);
		int shft_trm = __ffs(regs->vol_trm_bits);
		int step = dcdc_get_trimming_step(desc, mv);
		int j = (int)(mv - (int)regs->vol_sel[i]) * 1000 / step;
		j += dcdc_initial_value(desc);

		debug2("regu_dcdc %d = %d %+dmv (trim=%d step=%duv);\n",
			   mv, regs->vol_sel[i], mv - regs->vol_sel[i], j, step);

		if (regs->vol_trm == regs->vol_ctl) {
			if (j >= 0 && j <= (regs->vol_trm_bits >> shft_trm)) {
				ANA_REG_MSK_OR(regs->vol_ctl, (j << shft_trm) | (i << shft_ctl),
					regs->vol_trm_bits | regs->vol_ctl_bits);
			}
		} else {
			if (regs->vol_trm) { /* small adjust first */
				if (j >= 0 && j <= (regs->vol_trm_bits >> shft_trm)) {
					ANA_REG_MSK_OR(regs->vol_trm, j << shft_trm, regs->vol_trm_bits);
				}
			}

			if (regs->vol_ctl) {
				ANA_REG_MSK_OR(regs->vol_ctl, i << shft_ctl, regs->vol_ctl_bits);
			}
		}
	}
	return 0;
}

static int dcdc_set_trimming(struct regulator_desc *desc, int def_vol, int to_vol, int adc_vol)
{
	//int acc_vol = dcdc_get_trimming_step(desc, to_vol) / 1000;
	int ctl_vol = (def_vol - (adc_vol - to_vol));

	return dcdc_set_voltage(desc, ctl_vol, ctl_vol);
}

static int ldo_get_voltage(struct regulator_desc *desc)
{
	const struct regulator_regs *regs = desc->regs;
	int i = 0, shft = 0;
	u32 vol;

	BUG_ON(!(regs->vol_ctl || regs->vol_ctl_bits));

	shft = __ffs(regs->vol_ctl_bits);
	i = ((ANA_REG_GET(regs->vol_ctl) & regs->vol_ctl_bits) >> shft);
	vol = regs->vol_sel[i];

	debug0("%s get voltage %dmv, idx %d\n", desc->name, vol, i);

	return vol;
}

#if 0
static int ldo_set_voltage(struct regulator_desc *desc, int min_mV, int max_mV)
{
	const struct regulator_regs *regs = desc->regs;
	int i, mv = min_mV;
	int shft_ctl = __ffs(regs->vol_ctl_bits);

	BUG_ON(!regs->vol_ctl || (regs->vol_sel_cnt > 4));

	/* found the closely vol ctrl bits */
	i = __match_vol(desc, mv);
	if (i < 0) {
		debug2("%s: %s failed to match voltage: %d\n",__func__,desc->name,mv);
		return -1;
	}

	ANA_REG_MSK_OR(regs->vol_ctl,
					i << shft_ctl,
					regs->vol_ctl_bits);

	return 0;
}
#endif


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
		int shft_trm = __ffs(regs->vol_trm_bits);
		u32 trim = DIV_ROUND_UP((to_vol * 100 - adc_vol * 90) * 32, (adc_vol * 20));

		if (trim > BIT(5) - 1)
			return ret;

		debug2("regu_ldo %d = %d %+d.%03d%%, trim(0x%02x)\n",
			to_vol, adc_vol, (int)(trim * 20 - 320) / 32, (int)abs((int)(trim * 20 - 320) * 1000 / 32) % 1000, trim);

		ANA_REG_MSK_OR(regs->vol_trm,
						trim << shft_trm,
						regs->vol_trm_bits);
		ret = 0;
	}

	return ret;
}

static int DCDC_Cal_One(struct regulator_desc *desc, int is_cal)
{
	struct regulator_regs *regs = desc->regs;
	int def_vol = 0, to_vol = 0;
	int adc = 0, adc_vol = 0, cal_vol = 0;
	int ret = -1, adc_chan = regs->cal_ctl_bits >> 16;
	u16 ldo_cal_sel = regs->cal_ctl_bits & 0xFFFF;

	if (!adc_chan || !regs->vol_def)
		return -1;

	/* only verify dcdc calibration */
	if (!is_cal && (2 != desc->regs->typ))
		return -2;

	if (is_cal)
		debug("\nCalibrate %s ...\n", desc->name);
	else
		debug("\nVerify %s ...\n", desc->name);

	/* Fixme: Config dynamically dcdc/ldo
	 *   accoring to bit BONDOPT4 & BONDOPT6 for Reg(0x40038800 + 0x00E4)
	 */
	/* BONDOPT6 */
	if ((ana_status >> 6) & 0x1) {
		if (0 == strcmp(desc->name, "vddcore")) {
			desc->regs->vol_def = 900;
			desc->regs->vol_ctl = (u32)ANA_REG_GLB_MP_MISC_CTRL;
			desc->regs->vol_ctl_bits = BIT(3)|BIT(4)|BIT(5);
		} else if (0 == strcmp(desc->name, "vddarm")) {
			desc->regs->vol_def = 900;
			desc->regs->vol_ctl = (u32)ANA_REG_GLB_MP_MISC_CTRL;
			desc->regs->vol_ctl_bits = BIT(6)|BIT(7)|BIT(8);
		} else if (0 == strcmp(desc->name, "vdd25")) {
			desc->regs->vol_def = 1800;
			desc->regs->vol_ctl = (u32)ANA_REG_GLB_MP_MISC_CTRL;
			desc->regs->vol_ctl_bits = BIT(9)|BIT(10);
			desc->regs->vol_sel[0] = 2500;
			desc->regs->vol_sel[1] = 2750;
			desc->regs->vol_sel[2] = 1800;
			desc->regs->vol_sel[3] = 1900;
		}
	} else {
		if (0 == strcmp(desc->name, "vddcore")) {
			desc->regs->vol_def = 1100;
			desc->regs->vol_ctl = (u32)ANA_REG_GLB_DCDC_CORE_ADI;
			desc->regs->vol_ctl_bits = BIT(5)|BIT(6)|BIT(7);
		} else if (0 == strcmp(desc->name, "vddarm")) {
			desc->regs->vol_def = 1100;
			desc->regs->vol_ctl = (u32)ANA_REG_GLB_DCDC_ARM_ADI;
			desc->regs->vol_ctl_bits = BIT(5)|BIT(6)|BIT(7);
		} else if (0 == strcmp(desc->name, "vdd25")) {
			desc->regs->vol_def = 2500;
			desc->regs->vol_ctl = (u32)ANA_REG_GLB_LDO_V_CTRL0;
			desc->regs->vol_ctl_bits = BIT(4)|BIT(5);
			desc->regs->vol_sel[0] = 2500;
			desc->regs->vol_sel[1] = 2750;
			desc->regs->vol_sel[2] = 3000;
			desc->regs->vol_sel[3] = 2900;
		}
	}

	/* BONDOPT4 */
	if ((ana_status >> 4) & 0x1) {
		if (0 == strcmp(desc->name, "vddwrf")) {
			desc->regs->vol_def = 2800;
			desc->regs->vol_sel[0] = 2600;
			desc->regs->vol_sel[1] = 2700;
			desc->regs->vol_sel[2] = 2800;
			desc->regs->vol_sel[3] = 2900;
		} else if (0 == strcmp(desc->name, "vddrf1")) {
			desc->regs->vol_def = 2850;
			desc->regs->vol_ctl = (u32)ANA_REG_GLB_LDO_V_CTRL0;
			desc->regs->vol_ctl_bits = BIT(8)|BIT(9);
		}
	} else {
		if (0 == strcmp(desc->name, "vddwrf")) {
			desc->regs->vol_def = 1500;
			desc->regs->vol_sel[0] = 1300;
			desc->regs->vol_sel[1] = 1400;
			desc->regs->vol_sel[2] = 1500;
			desc->regs->vol_sel[3] = 1600;
		} else if (0 == strcmp(desc->name, "vddrf1")) {
			desc->regs->vol_def = 1200;
			desc->regs->vol_ctl = (u32)ANA_REG_GLB_MP_MISC_CTRL;
			desc->regs->vol_ctl_bits = BIT(11)|BIT(12);
		}
	}
	if (ldo_cal_sel)
		ANA_REG_OR(regs->cal_ctl, ldo_cal_sel);

	/*
	 * FIXME: force get dcdc&ldo voltage from ana global regs
	 * and get ideal voltage from vol para.
	 */
	if (desc->regs->typ == 2 /*DCDC*/) {
		def_vol = dcdc_get_voltage(desc);
	}
	else if (desc->regs->typ == 0 /*LDO*/) {
		def_vol = ldo_get_voltage(desc);
	}

	to_vol = regulator_default_get(desc->name);
	if (!to_vol){
		to_vol = regs->vol_def;
        }
	adc_vol = sci_adc_vol_request(adc_chan, ADC_SCALE_3V, ldo_cal_sel, &adc);
	if (adc_vol <= 0) {
		debug1("%s default %dmv, adc channel %d, maybe not enable\n", desc->name, def_vol, adc_chan);
		goto exit;
	}

	cal_vol = abs(adc_vol - to_vol);
	debug1("%s chan[%d] adc %d, default %dmv, from %dmv to %dmv, bias %c%d.%03d%%\n",
	      desc->name, adc_chan, adc, def_vol, adc_vol, to_vol,
	      (adc_vol > to_vol) ? '+' : '-',
	      cal_vol * 100 / to_vol, cal_vol * 100 * 1000 / to_vol % 1000);

	if (!def_vol || !to_vol || adc_vol <= 0)
		goto exit;
	if (abs(adc_vol - def_vol) >= def_vol / 9)	/* adjust limit 9% */
		goto exit;
	else if (cal_vol < to_vol / 100) {	/* bias 1% */
		goto exit;
	}

	if (is_cal) {
		if (regs->typ == 2 /*VDD_TYP_DCDC*/)
			ret = dcdc_set_trimming(desc, def_vol, to_vol, adc_vol);
		else if (regs->typ == 0 /*VDD_TYP_LDO*/)
			ret = ldo_set_trimming(desc, def_vol, to_vol, adc_vol);

		if(ret < 0)
			regulator_default_set(desc->name, 0);
	}

exit:
	if (ldo_cal_sel)
		ANA_REG_BIC(regs->cal_ctl, ldo_cal_sel);

	return ret;
}

#ifndef CONFIG_ADIE_SC2713
int DCDC_Cal_ArmCore(void)
#else
int SC2713S_DCDC_Cal_ArmCore(void)
#endif
{
	u16 regval_dcdc_store, regval_ldo_store;
	struct regulator_desc *desc = NULL;
	struct regulator_desc *desc_end = NULL;
	u32 cali_mask = regulator_get_calibration_mask(); //0xFFFF0FE2
	u32 chip_id = ANA_GET_CHIP_ID();
	int vbat_adc = 0;
	int vbat_vol = sci_adc_vol_request(5, ADC_SCALE_3V, 0, &vbat_adc);
	chipram_env_t* cr_env = get_chipram_env();
	ppvol_para = (vol_para_t *)(cr_env->vol_para_addr);
	printf("get ppvol_para from chipram, ppvol_para=%p\n", ppvol_para);

	ana_status = ANA_REG_GET(ANA_REG_GLB_ANA_STATUS);

	printf("%s; adie chip id: (0x%08x), bond opt: (0x%08x), cali_mask: (0x%08x), VBAT(vol %d, adc %d)\n",
		__FUNCTION__, chip_id, ana_status, cali_mask, vbat_vol, vbat_adc);

	cali_mask &= 0x01E00FFF;

	regval_dcdc_store = ANA_REG_GET(ANA_REG_GLB_LDO_DCDC_PD_RTCSET) & 0xFFFF;
	ANA_REG_BIC(ANA_REG_GLB_LDO_DCDC_PD_RTCSET, (cali_mask >> 16));

	regval_ldo_store = ANA_REG_GET(ANA_REG_GLB_LDO_PD_CTRL) & 0xFFFF;
	ANA_REG_BIC(ANA_REG_GLB_LDO_PD_CTRL, cali_mask & 0xFFFF);


	/* TODO: calibrate all DCDCs */
	desc = (struct regulator_desc *)(&__init_begin + 1);

	printf("%p (%x) -- %p -- %p (%x)\n", &__init_begin, __init_begin,
		desc, &__init_end, __init_end);

	desc_end = (struct regulator_desc *)(&__init_end) - 1;
	while (desc_end >= desc) { /* reverse order */
		DCDC_Cal_One(desc_end, 1);
		desc_end--;
	}


#if defined(REGU_CALI_DEBUG)
	/* wait a moment for LDOs ready */
	udelay(10 * 1000); //delay 10ms

	/* TODO: verify all DCDCs */
	desc = (struct regulator_desc *)(&__init_begin + 1);
	desc_end = (struct regulator_desc *)(&__init_end) - 1;
	while (desc_end >= desc) { /* reverse order */
		DCDC_Cal_One(desc_end, 0);
		desc_end--;
	}
#endif

	/* restore adie dcdc/ldo PD bits */
	ANA_REG_SET(ANA_REG_GLB_LDO_PD_CTRL, regval_ldo_store);
	ANA_REG_SET(ANA_REG_GLB_LDO_DCDC_PD_RTCSET, regval_dcdc_store);

	if(calibrate_post)
		calibrate_post(1);

	return 0;
}


int regulator_init(void)
{
	/*
	 * FIXME: turn on all DCDC/LDOs if need
	 */
	return 0;
}

struct regulator_desc *regulator_get(void/*struct device*/ *dev, const char *id)
{
	struct regulator_desc *desc =
		(struct regulator_desc *)(&__init_begin + 1);
	while (desc < (struct regulator_desc *)&__init_end) {
		if (0 == strcmp(desc->name, id))
			return desc;
		desc++;
	}
	return 0;
}

int regulator_disable_all(void)
{
	ANA_REG_OR(ANA_REG_GLB_LDO_PD_CTRL, 0xFFF);
	ANA_REG_OR(ANA_REG_GLB_LDO_DCDC_PD_RTCSET, 0xFFFF);
	ANA_REG_BIC(ANA_REG_GLB_LDO_DCDC_PD_RTCCLR, 0xFFFF);
	return 0;
}

int regulator_enable_all(void)
{
	ANA_REG_BIC(ANA_REG_GLB_LDO_DCDC_PD_RTCSET, 0xFFFF);
	ANA_REG_OR(ANA_REG_GLB_LDO_DCDC_PD_RTCCLR, 0xFFFF);
	ANA_REG_BIC(ANA_REG_GLB_LDO_PD_CTRL, 0xFFF);
	return 0;
}

int regulator_disable(const char con_id[])
{
	struct regulator_desc *desc = regulator_get(0, con_id);
	if (desc) {
		struct regulator_regs *regs = desc->regs;
		ANA_REG_OR(regs->pd_set, regs->pd_set_bit);
	}
	return 0;
}

int regulator_enable(const char con_id[])
{
	struct regulator_desc *desc = regulator_get(0, con_id);
	if (desc) {
		struct regulator_regs *regs = desc->regs;
		ANA_REG_BIC(regs->pd_set, regs->pd_set_bit);
	}
	return 0;
}

int regulator_set_voltage(const char con_id[], int to_vol)
{
	int ret = 0;
	struct regulator_desc *desc = regulator_get(0, con_id);
	if (desc) {
		struct regulator_regs *regs = desc->regs;
		if (regs->typ == 2/*VDD_TYP_DCDC*/)
			ret = dcdc_set_voltage(desc, to_vol, 0);
		else if (regs->typ == 0/*VDD_TYP_LDO*/)
			ret = ldo_set_trimming(desc, 0, to_vol, 0);
	}
	return ret;
}


static int get_vol_para_num(void)
{
	int i = 0;

	if (!ppvol_para)
		return 0;
	if(strcmp(ppvol_para[0].name, "volpara_begin") || (0xfaed != ppvol_para[0].ideal_vol))
		return 0;

	while(0 != strcmp(ppvol_para[i++].name, "volpara_end"))
		;

	return (i+1);
}

static vol_para_t * match_vol_para(const char* vol_name)
{
	int i = 0;

	BUG_ON(NULL == vol_name);

	if (!ppvol_para)
		return NULL;

	if(strcmp(ppvol_para[0].name, "volpara_begin") || (0xfaed != ppvol_para[0].ideal_vol))
		return NULL;

	while(0 != strcmp(ppvol_para[i++].name, "volpara_end")) {
		if (0 == strcmp(ppvol_para[i].name, vol_name)) {
			debug0("%s name %s, ideal_vol %d\n", __func__, ppvol_para[i].name, ppvol_para[i].ideal_vol);
			return (vol_para_t*)(&ppvol_para[i]);
		}
	}

	return NULL;
}

int regulator_default_get(const char con_id[])
{
	vol_para_t * pvol_para = match_vol_para(con_id);

	return (int)(pvol_para ? pvol_para->ideal_vol : 0);
}

void regulator_default_set(const char con_id[], int vol)
{
	vol_para_t * pvol_para = match_vol_para(con_id);

	if(pvol_para) {
		pvol_para->ideal_vol = vol;
	}
}

int regulator_default_set_all(void)
{
	int i = 0, ret = 0;

	//dump & check all vol para
	if (!ppvol_para)
		return -1;

	if(strcmp(ppvol_para[0].name, "volpara_begin") || (0xfaed != ppvol_para[0].ideal_vol))
		return 0;

	while(0 != strcmp(ppvol_para[i++].name, "volpara_end")) {
		debug("regu: [%d] %s : %d\n", i, ppvol_para[i].name, ppvol_para[i].ideal_vol);

		ret |= regulator_set_voltage(ppvol_para[i].name, ppvol_para[i].ideal_vol);
	}

	return ret;
}

/********************************************************************
*
* regulator_get_calibration_mask - get dcdc/ldo calibration flag
*
//
//High 16bit: dcdc ctrl calibration flag
//
* bit[13] ~ bit[15] : reserved
* bit[12] : dcdcgen
* bit[11] : dcdcmem
* bit[10] : dcdcarm
* bit[9]   : dcdccore
* bit[8]   : vddrf0
* bit[7]   : vddemmccore
* bit[6]   : vddemmcio
* bit[5]   : vdddcxo
* bit[4]   : vddcon
* bit[3]   : vdd25
* bit[2]   : vdd28
* bit[1]   : vdd18
* bit[0]   : vddbg

//
//Low 16bit: ldo ctrl calibration flag
//
* bit[12] ~ bit[15] : reserved
* bit[11] : vddlpref
* bit[10] : dcdcwpa
* bit[9]   : vddclsg
* bit[8]   : vddusb
* bit[7]   : vddcammot
* bit[6]   : vddcamio
* bit[5]   : vddcamd
* bit[4]   : vddcama
* bit[3]   : vddsim2
* bit[2]   : vddsim1
* bit[1]   : vddsim0
* bit[0]   : vddsd
********************************************************************/
u32 regulator_get_calibration_mask(void)
{
	int len = get_vol_para_num();
	volatile vol_para_t *pvol_para = (volatile vol_para_t *)ppvol_para;
	volatile u32* pdebug_flag = (u32*)(&pvol_para[len-1]);

	if(len > 2) {
		printf("%s, vol_para_tbl_len %d, ldo_pd_mask 0x%08x; \n", __func__, len, *pdebug_flag);
		return (*pdebug_flag);
	}

	return 0;
}

/* register callback function after dcdc/ldo calibration  */
int calibrate_register_callback(void* callback_fun)
{
	if(callback_fun) {
		calibrate_post = (pfun)callback_fun;
		return 0;
	} else
		return -1;
}

