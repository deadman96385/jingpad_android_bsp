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

static u16 ana_mixed_ctl;

#define REGU_CALI_DEBUG

#ifdef REGU_CALI_DEBUG
#define regu_debug(fmt, arg...)		debugf(fmt, ## arg)
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


#if !(CONFIG_X86)
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
#endif
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
extern u32 sprd_pmic_efuse_read(int blk_index);
extern chipram_env_t* get_chipram_env(void);

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

#include "__sc2723_regulator_map.h"
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

		if ((trim >= 0) && (trim <= (regs->vol_trm_bits >> shft))) {
			ANA_REG_MSK_OR(regs->vol_trm,
					trim << shft,
					regs->vol_trm_bits);
			ret = 0;
		}
	}

	return ret;
}

static int reconfig_regulator(struct regulator_desc *desc)
{
	struct regulator_regs *regs = desc->regs;

	/* Fixme: Config DCDC  linear/no linear control
	 *   accoring to BIT14 of Reg(0x40038800 + 0x0118)
	 */
	if (ana_mixed_ctl & BIT_DCDC_V_CTRL_MODE) {
		/* dcdc linear control */
		if ((0 == strcmp(desc->name, "vddcore"))
			 || (0 == strcmp(desc->name, "vddarm"))) {
			regs->vol_trm_bits = (BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4) \
										|BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9));
			regs->vol_ctl = 0;
			regs->vol_ctl_bits = 0;

			regs->vol_sel_cnt = 2;
			regs->vol_sel[0] = 600;
			regs->vol_sel[1] = 3125;
		}
	} else {
		/* dcdc Non-linear control */
		if ((0 == strcmp(desc->name, "vddcore"))
			 || (0 == strcmp(desc->name, "vddarm"))) {
			regs->vol_ctl = regs->vol_trm;
			regs->vol_trm_bits = (BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4));
			regs->vol_ctl_bits = (BIT(5)|BIT(6)|BIT(7));

			regs->vol_sel_cnt = 8;
			regs->vol_sel[0] = 1100;
			regs->vol_sel[1] = 700;
			regs->vol_sel[2] = 800;
			regs->vol_sel[3] = 900;
			regs->vol_sel[4] = 1000;
			regs->vol_sel[5] = 650;
			regs->vol_sel[6] = 1200;
			regs->vol_sel[7] = 1300;
		}
	}
	return 0;
}

static int DCDC_Cal_One(struct regulator_desc *desc, int is_cal)
{
	struct regulator_regs *regs = desc->regs;
	int def_vol = 0, to_vol = 0, ref_vol = 0;
	int adc = 0, adc_vol = 0, cal_vol = 0;
	int ret = -1, adc_chan = 0;
	u16 ldo_cal_sel = 0, adc_scale = 0;
	int vdd_type = desc->regs->typ & (BIT(4) - 1);

	reconfig_regulator(desc);

	if (!regs->cal_ctl_bits)
		return -1;

	adc_chan = regs->cal_ctl_bits >> 16;
	ldo_cal_sel = regs->cal_ctl_bits & 0xFFFF;

	if (!adc_chan || !regs->vol_def)
		return -2;

	/* only verify dcdc/ldo default on calibration */
	if (!is_cal && !(regs->typ & BIT(4)))
		return -3;

	if (is_cal)
		debug("\nCalibrate %s ...\n", desc->name);
	else
		debug("\nVerify %s ...\n", desc->name);

	adc_scale = (((adc_chan != 13) && (adc_chan != 14)) ? ADC_SCALE_3V : ADC_SCALE_1V2);

	if (ldo_cal_sel)
		ANA_REG_OR(regs->cal_ctl, ldo_cal_sel);

	/*
	 * FIXME: force get dcdc&ldo voltage from ana global regs
	 * and get ideal voltage from vol para.
	 */
	if (vdd_type == 2 /*DCDC*/) {
		def_vol = dcdc_get_voltage(desc);
	}
	else if (vdd_type == 0 /*LDO*/) {
		def_vol = ldo_get_voltage(desc);
	}

	to_vol = regulator_default_get(desc->name);
	if (!to_vol)
		to_vol = regs->vol_def;

	adc_vol = sci_adc_vol_request(adc_chan, adc_scale, ldo_cal_sel, &adc);
	if (adc_vol <= 0) {
		debug1("%s default %dmv, adc channel %d, maybe not enable\n", desc->name, def_vol, adc_chan);
		goto exit;
	}

	ref_vol = (is_cal ? def_vol : to_vol);
	cal_vol = abs(adc_vol - ref_vol);

	debug1("%s chan[%d] adc %d, default %dmv, from %dmv to %dmv, bias %c%01d.%03d%%\n",
	      desc->name, adc_chan, adc, def_vol, adc_vol, to_vol,
	      (adc_vol > to_vol) ? '+' : '-',
	      cal_vol * 100 / ref_vol, cal_vol * 100 * 1000 / ref_vol % 1000);

	if (!def_vol || !to_vol || adc_vol <= 0)
		goto exit;
	if (cal_vol >= ref_vol / 9)	/* adjust limit 9% */
		goto exit;
	else if (cal_vol < ref_vol / 100) {	/* bias 1% */
		goto exit;
	}

	if (is_cal) {
		if (vdd_type == 2 /*VDD_TYP_DCDC*/)
			ret = dcdc_set_trimming(desc, def_vol, to_vol, adc_vol);
		else if (vdd_type == 0 /*VDD_TYP_LDO*/)
			ret = ldo_set_trimming(desc, def_vol, to_vol, adc_vol);

		if(ret < 0)
			regulator_default_set(desc->name, 0);
	}

exit:
	if (ldo_cal_sel)
		ANA_REG_BIC(regs->cal_ctl, ldo_cal_sel);

	return ret;
}

int DCDC_Cal_ArmCore(void)
{
	u16 regval_dcdc_store, regval_ldo_store, otp_pwr_sel;
	struct regulator_desc *desc = NULL;
	struct regulator_desc *desc_end = NULL;

	chipram_env_t* cr_env = get_chipram_env();
	ppvol_para = (vol_para_t *)(cr_env->vol_para_addr);
	debugf("get ppvol_para from chipram, ppvol_para=%p\n", ppvol_para);

	u32 cali_mask = regulator_get_calibration_mask();
	u32 chip_id = ANA_GET_CHIP_ID();
	int vbat_adc = 0;
	int vbat_vol = sci_adc_vol_request(5, ADC_SCALE_3V, 0, &vbat_adc);
	u16 otp_ana_flag = (u8)sprd_pmic_efuse_read(0) & BIT(7);

	ana_mixed_ctl = ANA_REG_GET(ANA_REG_GLB_MIXED_CTRL0);
	otp_pwr_sel = ANA_REG_GET(ANA_REG_GLB_PWR_SEL);

	debugf("%s; adie chipid:(0x%08x), mixed_ctl:(0x%08x), otp_sel:(0x%08x), cali_mask:(0x%08x), VBAT(vol %d, adc %d)\n",
		__func__, chip_id, ana_mixed_ctl, otp_pwr_sel, cali_mask, vbat_vol, vbat_adc);

	if(!otp_ana_flag) {
		/* TODO: verify all DCDCs */
		desc = (struct regulator_desc *)(&__init_begin + 1);
		desc_end = (struct regulator_desc *)(&__init_end) - 1;
		while (desc_end >= desc) { /* reverse order */
			DCDC_Cal_One(desc_end, 0);
			desc_end--;
		}

		goto exit;
	}

	cali_mask &= 0x3FFFFFF1;

	regval_dcdc_store = ANA_REG_GET(ANA_REG_GLB_LDO_DCDC_PD) & 0xFFFF;
	ANA_REG_MSK_OR(ANA_REG_GLB_PWR_WR_PROT_VALUE, BITS_PWR_WR_PROT_VALUE(0x6e7f), 0x7FFF);
	ANA_REG_BIC(ANA_REG_GLB_LDO_DCDC_PD, (cali_mask >> 16));
	ANA_REG_MSK_OR(ANA_REG_GLB_PWR_WR_PROT_VALUE, 0, 0x7FFF);

	regval_ldo_store = ANA_REG_GET(ANA_REG_GLB_LDO_PD_CTRL) & 0xFFFF;
	ANA_REG_BIC(ANA_REG_GLB_LDO_PD_CTRL, cali_mask & 0xFFFF);

	debugf("REG_DCDC_PD(0x%08x): (0x%08x), REG_LDO_PD(0x%08x): (0x%08x), \n",
		ANA_REG_GLB_LDO_DCDC_PD, regval_dcdc_store, ANA_REG_GLB_LDO_PD_CTRL, regval_ldo_store);

	/* TODO: calibrate all DCDCs */
	desc = (struct regulator_desc *)(&__init_begin + 1);
	desc_end = (struct regulator_desc *)(&__init_end) - 1;

	debugf("%p (%x) -- %p -- %p (%x)\n", &__init_begin, __init_begin,
		desc, &__init_end, __init_end);

	while (desc_end >= desc) { /* reverse order */
		DCDC_Cal_One(desc_end, 1);
		desc_end--;
	}

#if defined(REGU_CALI_DEBUG)
	/* wait a moment for LDOs ready */
	udelay(10 * 1000); //wait 10ms

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
	ANA_REG_MSK_OR(ANA_REG_GLB_PWR_WR_PROT_VALUE, BITS_PWR_WR_PROT_VALUE(0x6e7f), 0x7FFF);
	ANA_REG_SET(ANA_REG_GLB_LDO_DCDC_PD, regval_dcdc_store);
	ANA_REG_MSK_OR(ANA_REG_GLB_PWR_WR_PROT_VALUE, 0, 0x7FFF);

exit:
	if(calibrate_post)
		calibrate_post(1);

	return 0;
}

int regulator_init(void)
{
	//regulator_set_voltage("vddrf0",1900);
	regulator_set_voltage("vddrf",1800);
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
	ANA_REG_OR(ANA_REG_GLB_LDO_PD_CTRL, 0x7fff);
	ANA_REG_OR(ANA_REG_GLB_LDO_DCDC_PD, 0xbfff);
	return 0;
}

int regulator_enable_all(void)
{
	ANA_REG_BIC(ANA_REG_GLB_LDO_DCDC_PD, 0xbfff);
	ANA_REG_BIC(ANA_REG_GLB_LDO_PD_CTRL, 0x7fff);
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
* bit[15] : ldoemm
* bit[14] : dcdctopclk6M
* bit[13] : dcdcrf
* bit[12] : dcdcgen
* bit[11] : dcdcmem
* bit[10] : dcdcarm
* bit[9]   : dcdccore
* bit[8]   : vddrf0
* bit[7]   : vddemmccore
* bit[6]   : vddgen1
* bit[5]   : vdddcxo
* bit[4]   : vddgen0
* bit[3]   : vdd25
* bit[2]   : vdd28
* bit[1]   : vdd18
* bit[0]   : vddbg

//
//Low 16bit: ldo ctrl calibration flag
//
* bit[15] : ldolpref
* bit[14] : dcdcwpa
* bit[13] : dcdccon
* bit[12] : reserved
* bit[11] : vddwifipa
* bit[10] : vddsdcore
* bit[9]   : reserved
* bit[8]   : vddusb
* bit[7]   : vddcammot
* bit[6]   : vddcamio
* bit[5]   : vddcamd
* bit[4]   : vddcama
* bit[3]   : vddsim2
* bit[2]   : vddsim1
* bit[1]   : vddsim0
* bit[0]   : vddsdio
********************************************************************/
u32 regulator_get_calibration_mask(void)
{
	int len = get_vol_para_num();
	volatile vol_para_t *pvol_para = (volatile vol_para_t *)ppvol_para;
	volatile u32* pdebug_flag = (u32*)(&pvol_para[len-1]);

	if(len > 2) {
		debugf("%s, vol_para_tbl_len %d, ldo_pd_mask 0x%08x; \n", __func__, len, *pdebug_flag);
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

int regulator_pmic_init(void)
{
	return 0;
}
