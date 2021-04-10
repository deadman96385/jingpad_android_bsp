#include <common.h>
#include <asm/io.h>
#include "adc_drvapi.h"
#include "adi_hal_internal.h"
#include <asm/arch/sprd_reg.h>

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

#define WR_UNLOCK 0x6e7f

#define GENMASK(h, l) \
	(((~0UL) << (l)) & (~0UL >> (BITS_PER_LONG - 1 - (h))))

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

#include "__sc2720_regulator_map.h"
struct regulator_desc __init2 __init_end = {0};

static struct {
	int id;
	const char* name;
	int efuse_block_id;
	int efuse_bit_mask;
	int pmic_regs_addr;
	int pmic_regs_mask;
} reinit_node[] = {
	{0,"DCDC_3M",		0,	GENMASK(11,8),	ANA_REG_GLB_DCDC_CLK_REG0,	BITS_OSC3M_FREQ(0xF)},
	{1,"DCDC_CORE_PFM",	15,	GENMASK(1,0),	ANA_REG_GLB_DCDC_CORE_REG0,	BITS_PFM_VH_VCORE(0x3)},
	{2,"DCDC_GEN_PFM",	15,	GENMASK(3,2),	ANA_REG_GLB_DCDC_GEN_REG0,	BITS_PFM_VH_VGEN(0x3)},
	{3,"DCDC_WPA_PFM",	15,	GENMASK(5,4),	ANA_REG_GLB_DCDC_WPA_REG0,	BITS_PFM_THRESHOLD_VPA(0x3)},
	{4,"RESERVED_RTC",	6,	GENMASK(14,10),	ANA_REG_GLB_RESERVED_REG_RTC,	GENMASK(4,0)},
	{-1,NULL,0,0},
};

/* standard dcdc ops*/

static int dcdc_get_trimming_step(struct regulator_desc *desc, int to_vol)
{
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

static int reload_regulator_config()
{
	int i,shft,reload_val;
	u32 efuse_val;

	for(i = 0; reinit_node[i].id != -1; i++) {
		efuse_val = sprd_pmic_efuse_read(reinit_node[i].efuse_block_id);
		shft = __ffs(reinit_node[i].efuse_bit_mask);
		reload_val = (efuse_val & reinit_node[i].efuse_bit_mask)
			>> shft;
		shft = __ffs(reinit_node[i].pmic_regs_mask);
		ANA_REG_MSK_OR(reinit_node[i].pmic_regs_addr,
			       reload_val << shft,
			       reinit_node[i].pmic_regs_mask);
	}
/*
 * reset DCDC_CORE PFM/PWM for pmic issue workaround
 * pmic efuse block15[0] 1'.
 */
	efuse_val = sprd_pmic_efuse_read(15);
	if( efuse_val & BIT(0)) {
		ANA_REG_SET(ANA_REG_GLB_DCDC_CORE_REG0, 0x1443);
	}
	return 0;
}

int regulator_pmic_init(void)
{
	ANA_REG_SET(ANA_REG_GLB_PWR_WR_PROT_VALUE, BITS_PWR_WR_PROT_VALUE(WR_UNLOCK));
	reload_regulator_config();
	return 0;
}
