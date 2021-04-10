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

#define CBANK_VALUE 0x5
#define WR_UNLOCK 0x6e7f
#define TSX_WR_UNLOCK 0x1990
#define TRANS_26M_EN 1
#define DIV_COEF 0x750
#define IB_ZCD_THRESHOLD_MAX 111
#define IB_ZCD_THRESHOLD_MIN 67

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
	//u32 min_mV, step_uV;
	u32 vol_def;
	u32 vol_sel_cnt, vol_sel[];
};

struct regulator_desc {
	int id;
	const char *name;
	struct regulator_regs *regs;
};

#define REGU_VERIFY_DLY	(1000)	/*ms */
#define SCI_REGU_REG(VDD, TYP, PD_SET, SET_BIT, \
                     VOL_TRM, VOL_TRM_BITS,  VOL_DEF, VOL_SEL_CNT, ...)	\
	static struct regulator_regs REGS_##VDD = {						\
		.typ = TYP,							\
		.pd_set = PD_SET, 					\
		.pd_set_bit = SET_BIT,				\
		.vol_trm = VOL_TRM,					\
		.vol_trm_bits = VOL_TRM_BITS,		\
		.vol_def = VOL_DEF,					\
		.vol_sel_cnt = VOL_SEL_CNT,			\
		.vol_sel = {__VA_ARGS__},			\
	};										\
	struct regulator_desc __init1 DESC_##VDD = {	\
		.id = -1,								\
		.name = #VDD,						\
		.regs = &REGS_##VDD,					\
	};										\

struct regulator_desc __init0 __init_begin = {0};

#include "__sc2730_regulator_map.h"
struct regulator_desc __init2 __init_end = {0};

static struct {
	int id;
	const char* name;
	int efuse_block_id;
	int efuse_bit_mask;
	int pmic_regs_addr;
	int pmic_regs_mask;
} reinit_node[] = {
	{0, "DCDC_CPU_ZCD", 14, GENMASK(15,9), ANA_REG_GLB_DCDC_CPU_REG2, BITS_DCDC_CPU_ZCD(0x3)},
	{1, "DCDC_GPU_ZCD", 14, GENMASK(15,9), ANA_REG_GLB_DCDC_GPU_REG2, BITS_DCDC_GPU_ZCD(0x3)},
	{2, "DCDC_CORE_ZCD", 14, GENMASK(15,9), ANA_REG_GLB_DCDC_CORE_REG2, BITS_DCDC_CORE_ZCD(0x3)},
	{3, "DCDC_MODEM_ZCD", 14, GENMASK(15,9), ANA_REG_GLB_DCDC_MODEM_REG2, BITS_DCDC_MODEM_ZCD(0x3)},
	{4, "DCDC_MEM_ZCD", 14, GENMASK(15,9), ANA_REG_GLB_DCDC_MEM_REG2, BITS_DCDC_MEM_ZCD(0x3)},
	{5, "DCDC_MEMQ_ZCD", 14, GENMASK(15,9), ANA_REG_GLB_DCDC_MEMQ_REG2, BITS_DCDC_MEMQ_ZCD(0x3)},
	{6, "DCDC_GEN0_ZCD", 14, GENMASK(15,9), ANA_REG_GLB_DCDC_GEN0_REG2, BITS_DCDC_GEN0_ZCD(0x3)},
	{7, "DCDC_GEN1_ZCD", 14, GENMASK(15,9), ANA_REG_GLB_DCDC_GEN1_REG2, BITS_DCDC_GEN1_ZCD(0x3)},
	{8, "DCDC_WPA_ZCD", 14, GENMASK(15,9), ANA_REG_GLB_DCDC_WPA_REG3, BITS_DCDC_WPA_ZCD(0x3)},
	{9, "DCDC_SRAM_ZCD", 14, GENMASK(15,9), ANA_REG_GLB_DCDC_SRAM_REG2, BITS_DCDC_SRAM_ZCD(0x3)},
	{10, "LDO_DCXO_LP", 14, GENMASK(4,1), ANA_REG_GLB_LDO_VDD18_DCXO_REG2, BITS_LDO_VDD18_DCXO_REFTRIM_LP(0xF)},
	{-1, NULL, 0, 0, 0, 0},
};
static struct {
	int id;
	const char* name;
	int value;
	int pmic_regs_addr;
	int pmic_regs_mask;
} reinit_node_cfg[] = {
	{0, "DCDC_CPU_DTM", 0x2, ANA_REG_GLB_DCDC_CPU_REG0, BITS_DCDC_CPU_DEADTIME(0x3)},
	{1, "DCDC_GPU_DTM", 0x2, ANA_REG_GLB_DCDC_GPU_REG0, BITS_DCDC_GPU_DEADTIME(0x3)},
	{2, "DCDC_CORE_DTM", 0x2, ANA_REG_GLB_DCDC_CORE_REG0, BITS_DCDC_CORE_DEADTIME(0x3)},
	{3, "DCDC_MODEM_DTM", 0x2, ANA_REG_GLB_DCDC_MODEM_REG0, BITS_DCDC_MODEM_DEADTIME(0x3)},
	{4, "DCDC_MEM_DTM", 0x2, ANA_REG_GLB_DCDC_MEM_REG0, BITS_DCDC_MEM_DEADTIME(0x3)},
	{5, "DCDC_MEMQ_DTM", 0x2, ANA_REG_GLB_DCDC_MEMQ_REG0, BITS_DCDC_MEMQ_DEADTIME(0x3)},
	{6, "DCDC_GEN0_DTM", 0x2, ANA_REG_GLB_DCDC_GEN0_REG0, BITS_DCDC_GEN0_DEADTIME(0x3)},
	{7, "DCDC_GEN1_DTM", 0x2, ANA_REG_GLB_DCDC_GEN1_REG0, BITS_DCDC_GEN1_DEADTIME(0x3)},
	{8, "DCDC_SRAM_DTM", 0x2, ANA_REG_GLB_DCDC_SRAM_REG0, BITS_DCDC_SRAM_DEADTIME(0x3)},
	{9, "DCDC_WPA_DTM", 0x3, ANA_REG_GLB_DCDC_WPA_REG0, BITS_DCDC_WPA_DEADTIME(0x3)},
	{10, "DCDC_CPU_CF", 0x1, ANA_REG_GLB_DCDC_CPU_REG1, BITS_DCDC_CPU_CF(0x3)},
	{11, "DCDC_GPU_CF", 0x1, ANA_REG_GLB_DCDC_GPU_REG1, BITS_DCDC_GPU_CF(0x3)},
	{12, "DCDC_MODEM_CF", 0x1, ANA_REG_GLB_DCDC_MODEM_REG1, BITS_DCDC_MODEM_CF(0x3)},
	{13, "DCDC_WPA_CF", 0x1, ANA_REG_GLB_DCDC_WPA_REG0, BITS_DCDC_WPA_CF(0x3)},
	{14, "DCDC_CPU_STBOP", 0x2DF, ANA_REG_GLB_DCDC_CPU_REG2, GENMASK(12,0)},
	{15, "DCDC_GPU_STBOP", 0x2DF, ANA_REG_GLB_DCDC_GPU_REG2, GENMASK(12,0)},
	{16, "DCDC_CORE_STBOP", 0x2D8, ANA_REG_GLB_DCDC_CORE_REG2, GENMASK(12,0)},
	{17, "DCDC_MODEM_STBOP", 0xD9F, ANA_REG_GLB_DCDC_MODEM_REG2, GENMASK(12,0)},
	{18, "DCDC_SRAM_STBOP", 0x2D8, ANA_REG_GLB_DCDC_SRAM_REG2, GENMASK(12,0)},
	{-1, NULL, 0, 0, 0},
};
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

	if (regs->vol_trm && regs->vol_sel_cnt == 2) {
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
	/* dcdc calibration control bits (default 0) small adjust voltage: 100/32mv ~= 3.125mv */
	int shft_trm = __ffs(regs->vol_trm_bits);
	int shft_ctl = 0;
	int step = 0;
	int j = 0;


	if(regs->vol_sel_cnt == 2) {
		step = regs->vol_sel[1];
		j = DIV_ROUND_UP((mv - regs->vol_sel[0]) * 1000, step);
	}

	debug2("regu_dcdc %p (%s) %d = %d %+dmv (trim=%d step=%duv);\n", regs, desc->name,
		   mv, regs->vol_sel[i], mv - regs->vol_sel[i], j, step);

	if (regs->vol_trm) { /* small adjust first */
		if (j >= 0 && j <= (regs->vol_trm_bits >> shft_trm)) {
			ANA_REG_MSK_OR(regs->vol_trm, j << shft_trm, regs->vol_trm_bits);
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

	if (regs->vol_sel_cnt == 2) {
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
	int i,shft,ib_trim_val,reload_val;
	u32 efuse_val;

	for(i = 0; reinit_node_cfg[i].id != -1; i++){
		shft = __ffs(reinit_node_cfg[i].pmic_regs_mask);
		ANA_REG_MSK_OR(reinit_node_cfg[i].pmic_regs_addr,
				reinit_node_cfg[i].value << shft,
				reinit_node_cfg[i].pmic_regs_mask);
	}

	efuse_val = sprd_pmic_efuse_read(reinit_node[0].efuse_block_id);
	shft = __ffs(reinit_node[0].efuse_bit_mask);
	ib_trim_val = (efuse_val & reinit_node[0].efuse_bit_mask)
		>> shft;
	shft = __ffs(reinit_node[i].pmic_regs_mask);

	if(ib_trim_val >= IB_ZCD_THRESHOLD_MAX)
		reload_val = 2;
	else if(ib_trim_val <= IB_ZCD_THRESHOLD_MIN)
		reload_val = 0;
	else
		reload_val = 1;
	for(i = 0; reinit_node[i].id <= 9; i++)
		ANA_REG_MSK_OR(reinit_node[i].pmic_regs_addr,
				reload_val << shft,
				reinit_node[i].pmic_regs_mask);

	for(i = 10; reinit_node[i].id != -1; i++) {
		efuse_val = sprd_pmic_efuse_read(reinit_node[i].efuse_block_id);
		shft = __ffs(reinit_node[i].efuse_bit_mask);
		reload_val = (efuse_val & reinit_node[i].efuse_bit_mask)
			>> shft;
		shft = __ffs(reinit_node[i].pmic_regs_mask);
		ANA_REG_MSK_OR(reinit_node[i].pmic_regs_addr,
						reload_val << shft,
						reinit_node[i].pmic_regs_mask);

	}

	return 0;
}

void reset_cbank_value(void)
{
	u16 chip_id_low;
	chip_id_low = sci_adi_read(ANA_REG_GLB_CHIP_ID_LOW) & 0xffff;

	if(chip_id_low <= 0xb000) {
	ANA_REG_SET(ANA_REG_GLB_TSX_CTRL11, BITS_DCXO_CORE_CBANK_LP(CBANK_VALUE));
	}

}

int regulator_pmic_init(void)
{
	ANA_REG_SET(ANA_REG_GLB_PWR_WR_PROT_VALUE, BITS_PWR_WR_PROT_VALUE(WR_UNLOCK));
	ANA_REG_SET(ANA_REG_GLB_TSX_WR_PROT_VALUE, BITS_TSX_WR_PROT_VALUE(TSX_WR_UNLOCK));
	ANA_REG_SET(ANA_REG_GLB_TSX_CTRL12, BITS_DCXO_32K_FRAC_DIV_RATIO_CTRL_HP(DIV_COEF));
	ANA_REG_OR(ANA_REG_GLB_TSX_CTRL0, BITS_DCXO_26M_REF_OUT_EN(TRANS_26M_EN));
	reload_regulator_config();
	reset_cbank_value();
	return 0;
}
