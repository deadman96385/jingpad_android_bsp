#include <common.h>
#include <asm/io.h>
#include "adc_drvapi.h"
#include "adi_hal_internal.h"
#include <asm/arch/sprd_reg.h>
#include <sprd_adc.h>

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
#define DIV_ROUND(n,d)		(((n) + ((d)/2)) / (d))

#define MEASURE_TIMES				(15)

#define ADC_DROP_CNT	( DIV_ROUND(MEASURE_TIMES, 5) )
static int __average(int a[], int N)
{
	int i, sum = 0;
	for (i = 0; i < N; i++)
		sum += a[i];
	return DIV_ROUND(sum, N);
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

//#define ADC_CALI_DEBUG

#ifdef ADC_CALI_DEBUG
static short adc_data[4][2] = {
	/* same as nv adc_t */
	{4200, 3360}, /* 4.2@VBAT Reserved IdealA Value */
	{3600, 2877}, /* 3.6@VBAT Reserved IdealB Value */
	{900, 0}, /* 0.9@VBAT, Reserved IdealC Value */
	{300, 0}, /* 0.3@VBAT, Reserved IdealD Value */
};

static int adc2vbat(int adc_res, int scale)
{
	int t = 0;

	if (scale) {
		t = adc_data[0][0] - adc_data[1][0];
		t *= (adc_res - adc_data[0][1]);
		t /= (adc_data[0][1] - adc_data[1][1]);
		t += adc_data[0][0];
	} else {
		t = adc_data[2][0] - adc_data[3][0];
		t *= (adc_res - adc_data[2][1]);
		t /= (adc_data[2][1] - adc_data[3][1]);
		t += adc_data[2][0];
	}

	return t;
}
#endif

static int sci_adc_request(int channel, int scale)
{
	int results[MEASURE_TIMES];

	if (-1 == pmic_adc_get_values(channel, scale, MEASURE_TIMES, results)) {
		return 0;
	}

	bubble_sort(results, MEASURE_TIMES);

#if defined(ADC_CALI_DEBUG)
{
	int i = 0;
	/* dump results */
	for (i = 0; i < MEASURE_TIMES; i++) {
		debug("%d ", results[i]);
	}
	debug("\n");
}
#endif

	return __average(&results[ADC_DROP_CNT], MEASURE_TIMES - ADC_DROP_CNT * 2);
}

#define RATIO(_n_, _d_) (_n_ << 16 | _d_)

static int sci_adc_ratio(int channel, int scale, int mux)
{
	switch (channel) {
	case 0x00:
		return RATIO(1, 1);
	case 0x01:
	case 0x02:
	case 0x03:
		return ((ADC_SCALE_3V == scale) ? RATIO(400, 1025) : RATIO(1, 1));
	case 0x05:		//Vbat
	case 0x08:
		return RATIO(7, 29);
	case 0x06:
		return RATIO(77, 1024);
	case 0x0D:  //dcdc core/arm/mem/gen/rf/con/wpa
		mux = mux >> 13;
		switch (mux) {
		case 1: //dcdcarm
		case 2: //dcdccore
			return ((ADC_SCALE_3V == scale) ? RATIO(36, 55) : RATIO(9, 11));
		case 3: //dcdcmem
		case 5: //dcdcrf
			return ((ADC_SCALE_3V == scale) ? RATIO(12, 25) : RATIO(3, 5));
		case 4: //dcdcgen
			return ((ADC_SCALE_3V == scale) ? RATIO(3, 10) : RATIO(3, 8));
		case 6: //dcdccon
			return ((ADC_SCALE_3V == scale) ? RATIO(9, 20) : RATIO(9, 16));
		case 7: //dcdwpa
			return ((ADC_SCALE_3V == scale) ? RATIO(12, 55) : RATIO(3, 11));
		default:
			return RATIO(1, 1);
		}
	case 0xE:	//LP dcxo
		return ((ADC_SCALE_3V == scale) ? RATIO(4, 5) : RATIO(1, 1));
	case 0x14:	//headmic
		return RATIO(1, 3);

	case 0x15:	//dcdc supply LDO, vdd18/vddcamd/vddcamio/vddrf0/vddgen1/vddgen0
		return RATIO(1, 2);
	case 0x13:	//VbatBK
	case 0x16:	//VbatD Domain LDO, vdd25/vddcama/vddsim2/vddsim1/vddsim0
	case 0x17:	//VbatA Domain LDO,  vddwifipa/vddcammot/vddemmccore/vdddcxo/vddsdcore/vdd28
	case 0x18:	//kpled/vibr
	case 0x1D://vddsdio/vddusb/vddfgu
	case 0x1E:		//DP from terminal
	case 0x1F:		//DM from terminal
		return RATIO(1, 3);

	default:
		return RATIO(1, 1);
	}
	return RATIO(1, 1);
}


static u32 bat_numerators, bat_denominators = 0;
extern uint16_t sprdbat_auxadc2vbatvol (uint16_t adcvalue);
extern u32 __adie_efuse_read(int blk_index);

static int sci_adc_vol_request(int channel, int scale, int mux, int* adc)
{
	int chan_adc, chan_vol;

	if(0 == bat_denominators) {
		u32 res;
		/* FIXME: Update CHGMNG_AdcvalueToVoltage table before setup vbat ratio. */
		/*ADC_CHANNEL_VBAT is 5*/
		res = (u32) sci_adc_ratio(5, ADC_SCALE_3V, 0);
		bat_numerators = res >> 16;
		bat_denominators = res & 0xffff;
	}

	chan_adc = sci_adc_request(channel, scale);
	if (chan_adc) {
		u32 res, chan_numerators, chan_denominators;
		res = (u32) sci_adc_ratio(channel, scale, mux);
		chan_numerators = res >> 16;
		chan_denominators = res & 0xffff;

		if(adc)
			*adc = chan_adc;

	#ifdef ADC_CALI_DEBUG
		chan_vol = adc2vbat(chan_adc, 1);
	#else
		chan_vol = sprdbat_auxadc2vbatvol(chan_adc);
	#endif

		chan_vol *= (bat_numerators * chan_denominators);
		chan_vol /= (bat_denominators * chan_numerators);

		return chan_vol;
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




struct regulator_regs {
	int typ; /* BIT4: default on/off(0: off, 1: on); BIT0~BIT3: dcdc/ldo type(0: ldo; 2: dcdc) */
	unsigned long pd_set;
	u32 pd_set_bit;
	unsigned long vol_trm;
	u32 vol_trm_bits;
	unsigned long cal_ctl;
	u32 cal_ctl_bits;
	//u32 min_mV, step_uV;
	u32 vol_def;
	unsigned long vol_ctl;
	u32 vol_ctl_bits;
	u32 vol_sel_cnt, vol_sel[];
};


struct regulator_desc {
	int id;
	const char *name;
	struct regulator_regs *regs;
};

#define REGU_VERIFY_DLY	(1000)	/*ms */
#define SCI_REGU_REG(VDD, TYP, PD_SET, SET_BIT, \
                     VOL_TRM, VOL_TRM_BITS, CAL_CTL, CAL_CTL_BITS, VOL_DEF,	\
                     VOL_CTL, VOL_CTL_BITS, VOL_SEL_CNT, ...)		\
	static struct regulator_regs REGS_##VDD = {						\
		.typ = TYP,							\
		.pd_set = PD_SET, 					\
		.pd_set_bit = SET_BIT,				\
		.vol_trm = VOL_TRM,					\
		.vol_trm_bits = VOL_TRM_BITS,		\
		.cal_ctl = CAL_CTL,					\
		.cal_ctl_bits = CAL_CTL_BITS,		\
		.vol_def = VOL_DEF,					\
		.vol_ctl = VOL_CTL,					\
		.vol_ctl_bits = VOL_CTL_BITS,		\
		.vol_sel_cnt = VOL_SEL_CNT,			\
		.vol_sel = {__VA_ARGS__},			\
	};										\
	struct regulator_desc __init1 DESC_##VDD = {	\
		.id = -1,								\
		.name = #VDD,						\
		.regs = &REGS_##VDD,					\
	};										\

struct regulator_desc __init0 __init_begin = {0};

#include "__sc2721_regulator_map.h"
struct regulator_desc __init2 __init_end = {0};


/* standard dcdc ops*/

static int dcdc_get_trimming_step(struct regulator_desc *desc, int to_vol)
{
#if 0
	if (0 == strcmp(desc->name, "vddmem")) {
		/* FIXME: vddmem step 200/32mV */
		return 1000 * 200 / 32;	/*uV */
	}
#endif
	return 1000 * 100 / 32;	/*uV */
}

static int __match_vol(struct regulator_desc *desc, u32 vol)
{
	int i, j = -1;
	int ds, min_ds = 100;	/* mV, the max range of small voltage */
	struct regulator_regs *regs = desc->regs;

	for (i = 0; i < regs->vol_sel_cnt; i++) {
		ds = (int)(vol - regs->vol_sel[i]);
		if (ds >= 0 && ds < min_ds) {
			min_ds = ds;
			j = i;
		}
	}

	if ((2 == (regs->typ & (BIT(4) - 1))) && (j < 0)) {
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
	struct regulator_regs *regs = desc->regs;
	u32 mv = 0;
	int cal = 0; /* uV */
	int i = 0;

	BUG_ON(regs->vol_sel_cnt > 8);

	if (regs->vol_ctl) {
		int shft_ctl = __ffs(regs->vol_ctl_bits);
		int shft_trm = __ffs(regs->vol_trm_bits);

		i = (ANA_REG_GET(regs->vol_ctl) & regs->vol_ctl_bits) >> shft_ctl;
		mv = regs->vol_sel[i];

		if (regs->vol_trm) {
			cal = (ANA_REG_GET(regs->vol_trm) & regs->vol_trm_bits) >> shft_trm;
			cal *= dcdc_get_trimming_step(desc, 0);	/*uV */
		}

		debug0("%s %d +%dmv(trim %#x)\n", desc->name, mv, cal / 1000, cal / dcdc_get_trimming_step(desc, 0));

	} else if (regs->vol_trm && regs->vol_sel_cnt == 2) {
		int shft_trm = __ffs(regs->vol_trm_bits);
		u32 trim =
		    (ANA_REG_GET(regs->vol_trm) & regs->vol_trm_bits) >> shft_trm;
		mv = regs->vol_sel[0] + trim * regs->vol_sel[1] / 1000;

		debug0("%s %d +%dmv(trim %#x)\n", desc->name, regs->vol_sel[0], (mv - regs->vol_sel[0]), trim);
	}

	return (mv + cal / 1000);
}

static int dcdc_set_voltage(struct regulator_desc *desc, int min_mV, int max_mV)
{
	struct regulator_regs *regs = desc->regs;
	int i = 0, mv = min_mV;

	if (regs->vol_ctl) {
		/* found the closely vol ctrl bits */
		i = __match_vol(desc, mv);
		if (i < 0) {
			debug2("%s: %s failed to match voltage: %d\n", __func__, desc->name, mv);
			return -1;
		}
	}

	/* dcdc calibration control bits (default 0) small adjust voltage: 100/32mv ~= 3.125mv */
	{
		int shft_trm = __ffs(regs->vol_trm_bits);
		int shft_ctl = 0;
		int step = 0;
		int j = 0;

		if (regs->vol_ctl) {
			shft_ctl = __ffs(regs->vol_ctl_bits);
			step = dcdc_get_trimming_step(desc, mv);

			j = (int)(mv - (int)regs->vol_sel[i]) * 1000 / step;
		} else {
			if(regs->vol_sel_cnt == 2) {
				step = regs->vol_sel[1];
				j = DIV_ROUND_UP((mv - regs->vol_sel[0]) * 1000, step);
			}
		}

		debug2("regu_dcdc %p (%s) %d = %d %+dmv (trim=%d step=%duv);\n", regs, desc->name,
			   mv, regs->vol_sel[i], mv - regs->vol_sel[i], j, step);

		if ((regs->vol_trm == regs->vol_ctl) && regs->vol_ctl) {
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
	int ctl_vol = (to_vol - (adc_vol - def_vol));

	return dcdc_set_voltage(desc, ctl_vol, ctl_vol);
}

static int ldo_get_voltage(struct regulator_desc *desc)
{
	struct regulator_regs *regs = desc->regs;
	u32 vol;

	if (regs->vol_trm && regs->vol_sel_cnt == 2) {
		int shft = __ffs(regs->vol_trm_bits);
		u32 trim =
		    (ANA_REG_GET(regs->vol_trm) & regs->vol_trm_bits) >> shft;
		vol = regs->vol_sel[0] * 1000 + trim * regs->vol_sel[1];
		vol /= 1000;

		debug0("%s get voltage %dmv(trim %#x)\n", desc->name, vol, trim);

		return vol;
	}

	return -1;
}

static int ldo_set_trimming(struct regulator_desc *desc, int def_vol, int to_vol, int adc_vol)
{
	struct regulator_regs *regs = desc->regs;
	int ret = -1;

	if (!regs->vol_ctl && regs->vol_sel_cnt == 2) {
		/* ctl_vol = vol_base + reg[vol_trm] * vol_step  */
		int shft = __ffs(regs->vol_trm_bits);
		int ctl_vol = (to_vol - (adc_vol - def_vol));
		u32 trim = 0;

		if(adc_vol > def_vol)
			trim = DIV_ROUND_UP((ctl_vol - regs->vol_sel[0]) * 1000, regs->vol_sel[1]);
		else
			trim = ((ctl_vol - regs->vol_sel[0]) * 1000 / regs->vol_sel[1]);

		debug2("regu_ldo %p (%s) %d = %d %+dmv (trim=%d step=%duv)\n", regs, desc->name,
			ctl_vol, regs->vol_sel[0], ctl_vol - regs->vol_sel[0], trim, regs->vol_sel[1]);

		if (trim <= (regs->vol_trm_bits >> shft)) {
			ANA_REG_MSK_OR(regs->vol_trm,
					trim << shft,
					regs->vol_trm_bits);
			ret = 0;
		}
	}

	return ret;
}

struct regulator_desc *regulator_get(void/*struct device*/ *dev, const char *id)
{
	struct regulator_desc *desc =
		(struct regulator_desc *)(&__init_begin + 1);

	if(!id)
		return 0;

	while (desc < (struct regulator_desc *)&__init_end) {
		if (0 == strcmp(desc->name, id))
			return desc;
		desc++;
	}
	return 0;
}

int regulator_disable_all(void)
{
	ANA_REG_OR(ANA_REG_GLB_POWER_PD_SW, 0x7fff);
	ANA_REG_OR(ANA_REG_GLB_POWER_PD_HW, 0x1);
	return 0;
}

int regulator_enable_all(void)
{
	ANA_REG_BIC(ANA_REG_GLB_POWER_PD_HW, 0x1);
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
		int vdd_type = regs->typ & (BIT(4) - 1);

		if (vdd_type == 2 /*VDD_TYP_DCDC*/)
			ret = dcdc_set_voltage(desc, to_vol, 0);
		else if (vdd_type == 0 /*VDD_TYP_LDO*/)
			ret = ldo_set_trimming(desc, 0, to_vol, 0);
	}
	return ret;
}

int regulator_default_get(const char con_id[])
{
	return 0;
}

void regulator_default_set(const char con_id[], int vol)
{
	return 0;
}

int regulator_default_set_all(void)
{
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

int regulator_pmic_init(void)
{
	unsigned int efuse_data;

	efuse_data = sprd_pmic_efuse_read(16);
	if ( efuse_data & BIT(15)){
		unsigned int temp = efuse_data & 0x0F;

		ANA_REG_SET(ANA_REG_GLB_LDO_VLG_SEL1, 0x0140);

		if( temp > 2)
			efuse_data = 0xD0 + temp - 2;
		else
			efuse_data = 0xD0;

		ANA_REG_SET(ANA_REG_GLB_DCDC_GEN_REG2,efuse_data);
	}else{
		ANA_REG_SET(ANA_REG_GLB_LDO_VLG_SEL1, 0x07C0);
		ANA_REG_SET(ANA_REG_GLB_DCDC_GEN_REG2,0x00D6);
	}

		ANA_REG_SET(ANA_REG_GLB_DCDC_WPA_REG3,0x0891);

	return 0;
}
