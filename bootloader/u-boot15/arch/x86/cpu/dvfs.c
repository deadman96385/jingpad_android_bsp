/*
 * Copyright (C) 2016, Intel Corporation
 *
 * SPDX-License-Identifier:     GPL-2.0+
 *
 */

#include <common.h>
#include <asm/io.h>
#include <asm/msr.h>
#include <asm/msr-index.h>
#include <linux/compat.h>
#include <linux/kernel.h>
#include <otp_helper.h>
#include <asm/arch/hardware.h>
#include <dvfs.h>
#include <asm/arch/sprd_reg.h>
#include "adi_hal_internal.h"
#include <chipram_env.h>

#define FUSE_DVFS_BINNING_BLKNO				26 /*[9:6]: 0011-OD 0010-SS 0001-TT*/
#define FUSE_ISHARKL2_DVFS_BINNING_BLKNO		27 /*[19:16]: 0011-SS 0010-TT 0001-FF*/
#define FUSE_LFM_MODULE0_BLKNO		55
#define FUSE_HFM_MODULE0_BLKNO		56
#define FUSE_LFM_MODULE1_BLKNO		57
#define FUSE_HFM_MODULE1_BLKNO		58
#define FUSE_IDV_BLKNO			59

#define FUSE_DVFS_BINNING_VAL(efusedata) (((efusedata)>>6)&0xF)
#define FUSE_DVFS_BINNING_OD  0x3
#define FUSE_DVFS_BINNING_SS  0x2
#define FUSE_DVFS_BINNING_TT  0x1
#define FUSE_DVFS_BINNING_NULL  0x0


#define FUSE_ISHARKL2_DVFS_BINNING_VAL(efusedata) (((efusedata)>>16)&0xF)
#define FUSE_ISHARKL2_DVFS_BINNING_SS  0x3
#define FUSE_ISHARKL2_DVFS_BINNING_TT  0x2
#define FUSE_ISHARKL2_DVFS_BINNING_FF  0x1
#define FUSE_ISHARKL2_DVFS_BINNING_NULL  0x0


#define VID_TABLE_DATA (CONFIG_BASEIA_SRAM + CONFIG_VID_OFFSET)

static void *dvfs_mod0 = (void *)ADDR_DVFS_EN_MOD0;
static void *dvfs_mod1 = (void *)ADDR_DVFS_EN_MOD1;
static struct pmic_vid *vt_mod0 = (struct pmic_vid *)VT_MOD0;
static struct pmic_vid *vt_mod1 = (struct pmic_vid *)VT_MOD1;
static unsigned short hfm_vid_mod0, hfm_vid_mod1;

static u32 freq[] = {0, 936, 1248, 1560, 1872, 0};
u32 vmi_offsets [] = {0x0, 0x14, 0x20, 0x24, 0x28, 0x2c, 0x30,
			0x34, 0x38, 0x3c, 0x60, 0x64};


/** Host Bus Frequency
 * In intel platforms MSR 0xcd is used to calculate the FSB.
 * However in butter platform this MSR is not avaialable so
   hard coding it.
 */

static inline int host_bus_freq(void)
{
	return FSB_FREQ_MHZ;
}

static inline int get_guar_ratio(void)
{
	/*
	u32 low, high;

	rdmsr(MSR_IACORE_RATIOS, low, high);
	low >>= 16;
	low &= 0xFF;
	return low;
	*/
	/*workaround,set max freq to be 2028*/
	return 26;
}

static inline int get_lfm_ratio(void)
{
	u32 low, high;

	rdmsr(MSR_IACORE_RATIOS, low, high);
	low >>= 8;
	low &= 0xFF;
	return low;
}

/*
 pmic formula to calculate voltage in mv
 mv = 400 + ctrl[9:5] * 100 + cal[4:0] * 3.125
*/
static int get_pmic_voltage(int module, int index)
{
	int cal, ctrl, mv;
	struct pmic_vid *v;

	v = (module == MODULE0) ? (vt_mod0 + index) : (vt_mod1 + index);

	debug("Accessing Register [%p] Value [%x]\n", v, *v);
	/* cal[4:0] * 3.125	*/
	cal = mul_fp(int_tofp(v->cal), PMIC_CAL_PRECISION);
	/* v->ctrl * 100 */
	ctrl = mul_fp(int_tofp(v->ctrl), int_tofp(PMIC_CTRL_MUL));
	/*
	   pmic formula to calculate voltage in mv
	   mv = 400 + ctrl[9:5] * 100 + cal[4:0] * 3.125
	 */
	mv = int_tofp(PMIC_VLT_INTERCEPT) + cal + ctrl;
	mv = ceiling_fp(mv);

	return mv;
}

static int get_pmic_max_voltage(int module)
{
	return get_pmic_voltage(module, VID_V7);
}

static int get_pmic_min_voltage(int module)
{
	return get_pmic_voltage(module, VID_V2);
}

/*
 VDDCPU  V = 0.4 + CAL[4:0]*0.003125 + CTRL[9:5] * 0.1
 0      N/A             0.0V
 1      0x0070          0.75V
 2      0x008D          0.84V
 3      0x00a0          0.9V
 4      0x00b0          0.95V
 5      0x00c0          1.00V
 6      0x00e0          1.10V
 7      0x0100          1.20V
*/

static int next_vid(int module, int next_freq)
{
	int mv_min, mv_max, mv_range;
	int mv, df, freq_range;

	freq_range = get_guar_ratio() - get_lfm_ratio();
	mv_max = get_pmic_max_voltage(module);
	mv_min = get_pmic_min_voltage(module);
	mv_range = mv_max - mv_min;

	/* Change in freq ratio*/
	df = (next_freq - freq[LFM_INDEX]) / host_bus_freq();

	/* vid = min vid +  change in vid for a unit change in
	   freq ratio times the change in freq ratio
	 */

	mv = mul_fp(int_tofp(mv_range), int_tofp(df));
	mv = div_fp(mv, int_tofp(freq_range));
	mv = ceiling_fp(mv);
	debug("df [%d] dmv [%d]\n", df, mv);
	return mv;
}

/*
 pmic formula to calculate voltage in mv
 mv = 400 + ctrl[9:5] * 100 + cal[4:0] * 3.125
*/

static void set_pmic_voltage(struct pmic_vid *v, u32 mv)
{
	int ctrl, cal;
	int val, vddcpu = mv;

	vddcpu -= PMIC_VLT_INTERCEPT;
	ctrl = vddcpu / PMIC_CTRL_MUL;
	vddcpu -= (ctrl * PMIC_CTRL_MUL);

	cal = div_fp(int_tofp(vddcpu), PMIC_CAL_PRECISION);
	cal = ceiling_fp(cal);
	if(cal >= (1 << PMIC_CTRL_BIT)) {
		ctrl++;
		cal=0;
	}
	WARN_ON(cal < 0);
	val = (cal << PMIC_CAL_BIT) | (ctrl << PMIC_CTRL_BIT)
		| (1 << PMIC_VLT_AVAIL_BIT);
	debug("mv [%u] val [%x] ctrl [%d] cal [%d] addr [%p]\n", mv, val, ctrl, cal, v);
	writel(val, v);
}

static void setup_vid_table(int module)
{
	int i, mv_range;
	struct pmic_vid *v0, *v;
	int mv_v2, mv_v7, mv;
	u32 binning;

	v0 = (module == MODULE0) ? vt_mod0 : vt_mod1;
	/* WA. on zebu module, there's no efuse table, so we will set one
	value as default. will remove this if efuse supported.*/
	v = v0 + VID_V2;
	if(!v->avail) {
		if (ANA_REG_GET(ANA_REG_GLB_CHIP_ID_LOW) < 0xC003) {
			set_pmic_voltage(v, 1200);
			debug("no VID_V2 on efuse, write 1200mv as default\n");
		} else {
#if defined(CONFIG_SOC_IWHALE2)
			set_pmic_voltage(v, 800);
			debug("no VID_V2 on efuse, write 840mv as default\n");
#elif defined(CONFIG_SPRD_SOC_SP9853I)
			set_pmic_voltage(v, 840);
			debug("no VID_V2 on efuse, write 840mv as default\n");
#endif
		}
	}
	 if (ANA_REG_GET(ANA_REG_GLB_CHIP_ID_LOW) < 0xC003) {
		v = v0 + VID_V7;
		if(!v->avail) {
			set_pmic_voltage(v, 1200);
			debug("no VID_V7 on efuse, write 1200mv as default\n");
		}

		/*Programme the V0 to 750mv	*/
		set_pmic_voltage(v0 + VID_V0, 750);
		mv_v2 = get_pmic_min_voltage(module);
		mv_v7 = get_pmic_max_voltage(module);

		mv_range  = mv_v7 - mv_v2;
		WARN_ON(0 >= mv_range);
		/* First entry to be programmed */
		v =  (v0 + VID_V3);
		for (i = 0; i < NO_OF_PSTATES - 2; i++) {
			mv = mv_v2 + next_vid(module, freq[i + 1]);
			mv = clamp_t(int32_t, mv, mv_v2, mv_v7);
			debug("Programming milli volt %u\n", mv);
			set_pmic_voltage(v, mv);
			v++;
		}
	}
	else{
#if defined(CONFIG_SOC_IWHALE2)
		binning = sprd_ap_efuse_read(FUSE_DVFS_BINNING_BLKNO);
		debug("setup_vid_table  BINNING_BLK=%u, BINING_VAL=%u\n", binning, FUSE_DVFS_BINNING_VAL(binning));

		if (FUSE_DVFS_BINNING_VAL(binning) == FUSE_DVFS_BINNING_OD) {
			set_pmic_voltage(v0 + VID_V0, 770);
			set_pmic_voltage(v0 + VID_V1, 770);
			set_pmic_voltage(v0 + VID_V2, 770);
			set_pmic_voltage(v0 + VID_V3, 863);
			set_pmic_voltage(v0 + VID_V4, 977);
			set_pmic_voltage(v0 + VID_V5, 1092);
			set_pmic_voltage(v0 + VID_V6, 1206);
			set_pmic_voltage(v0 + VID_V7, 1263);
		} else if (FUSE_DVFS_BINNING_VAL(binning) == FUSE_DVFS_BINNING_SS) {
			set_pmic_voltage(v0 + VID_V0, 732);
			set_pmic_voltage(v0 + VID_V1, 732);
			set_pmic_voltage(v0 + VID_V2, 732);
			set_pmic_voltage(v0 + VID_V3, 833);
			set_pmic_voltage(v0 + VID_V4, 947);
			set_pmic_voltage(v0 + VID_V5, 1062);
			set_pmic_voltage(v0 + VID_V6, 1176);
			set_pmic_voltage(v0 + VID_V7, 1233);
		} else if (FUSE_DVFS_BINNING_VAL(binning) == FUSE_DVFS_BINNING_TT) {
			set_pmic_voltage(v0 + VID_V0, 732);
			set_pmic_voltage(v0 + VID_V1, 732);
			set_pmic_voltage(v0 + VID_V2, 732);
			set_pmic_voltage(v0 + VID_V3, 820);
			set_pmic_voltage(v0 + VID_V4, 921);
			set_pmic_voltage(v0 + VID_V5, 1022);
			set_pmic_voltage(v0 + VID_V6, 1123);
			set_pmic_voltage(v0 + VID_V7, 1173);
		} else {
			set_pmic_voltage(v0 + VID_V0, 800);
			set_pmic_voltage(v0 + VID_V1, 800);
			set_pmic_voltage(v0 + VID_V2, 800);
			set_pmic_voltage(v0 + VID_V3, 840);
			set_pmic_voltage(v0 + VID_V4, 947);
			set_pmic_voltage(v0 + VID_V5, 1061);
			set_pmic_voltage(v0 + VID_V6, 1176);
			set_pmic_voltage(v0 + VID_V7, 1233);
		}

#elif defined(CONFIG_SPRD_SOC_SP9853I)

		binning = sprd_ap_efuse_read(FUSE_ISHARKL2_DVFS_BINNING_BLKNO);
		debug("setup_vid_table  BINNING_BLK=%u, BINING_VAL=%u\n", binning, FUSE_ISHARKL2_DVFS_BINNING_VAL(binning));

		if (FUSE_ISHARKL2_DVFS_BINNING_VAL(binning) == FUSE_ISHARKL2_DVFS_BINNING_FF) {
			set_pmic_voltage(v0 + VID_V0, 726);
			set_pmic_voltage(v0 + VID_V1, 726);
			set_pmic_voltage(v0 + VID_V2, 726);
			set_pmic_voltage(v0 + VID_V3, 798);
			set_pmic_voltage(v0 + VID_V4, 895);
			set_pmic_voltage(v0 + VID_V5, 992);
			set_pmic_voltage(v0 + VID_V6, 1089);
			set_pmic_voltage(v0 + VID_V7, 1138);
		} else if (FUSE_ISHARKL2_DVFS_BINNING_VAL(binning) == FUSE_ISHARKL2_DVFS_BINNING_TT) {
			set_pmic_voltage(v0 + VID_V0, 736);
			set_pmic_voltage(v0 + VID_V1, 736);
			set_pmic_voltage(v0 + VID_V2, 736);
			set_pmic_voltage(v0 + VID_V3, 818);
			set_pmic_voltage(v0 + VID_V4, 921);
			set_pmic_voltage(v0 + VID_V5, 1024);
			set_pmic_voltage(v0 + VID_V6, 1127);
			set_pmic_voltage(v0 + VID_V7, 1178);
		} else if (FUSE_ISHARKL2_DVFS_BINNING_VAL(binning) == FUSE_ISHARKL2_DVFS_BINNING_SS) {
			set_pmic_voltage(v0 + VID_V0, 754);
			set_pmic_voltage(v0 + VID_V1, 754);
			set_pmic_voltage(v0 + VID_V2, 754);
			set_pmic_voltage(v0 + VID_V3, 838);
			set_pmic_voltage(v0 + VID_V4, 947);
			set_pmic_voltage(v0 + VID_V5, 1055);
			set_pmic_voltage(v0 + VID_V6, 1164);
			set_pmic_voltage(v0 + VID_V7, 1218);
		} else {
			set_pmic_voltage(v0 + VID_V0, 840);
			set_pmic_voltage(v0 + VID_V1, 840);
			set_pmic_voltage(v0 + VID_V2, 840);
			set_pmic_voltage(v0 + VID_V3, 840);
			set_pmic_voltage(v0 + VID_V4, 947);
			set_pmic_voltage(v0 + VID_V5, 1061);
			set_pmic_voltage(v0 + VID_V6, 1176);
			set_pmic_voltage(v0 + VID_V7, 1233);
		}
#endif
	}
}

#ifdef DEBUG
static void dump_table(int module)
{
	int mv, i;
	struct pmic_vid *v0;

	v0 = (module == MODULE0) ? vt_mod0 : vt_mod1;
	debug("module %d\n", module);
	for (i = 0; i < (NO_OF_PSTATES + 2); i++) {
		mv = get_pmic_voltage(module, i);
		debug("Addr [%p] vid [%x] mv[%d]\n",
		      v0 + i, *(v0 + i), mv);
	}
}

static void dump_vmi(void)
{
	int i;
	u32 no_entries = sizeof(vmi_offsets) / sizeof(u32);
	u32 *tbl0 = (u32*)VID_TABLE_DATA;
	u32 *tbl1 = tbl0 + no_entries;

	for (i = 0; i < no_entries; i++) {
		debug("module 0 vmi_offset %x %x\n", vmi_offsets[i], *(tbl0 + i));
		debug("module 1 vmi_offset %x %x\n", vmi_offsets[i], *(tbl1 + i));
	}
}
#else
static void dump_table(int module) {}
static void dump_vmi(void) {}
#endif

void init_vid_table(void)
{
	freq[LFM_INDEX] = get_lfm_ratio() * host_bus_freq();
	freq[HFM_INDEX] = get_guar_ratio() * host_bus_freq();
	debug("LFM freq %7d MHz HFM freq %7d MHz\n",
	      freq[LFM_INDEX], freq[HFM_INDEX]);
	setup_vid_table(MODULE0);
	dump_table(MODULE0);
	setup_vid_table(MODULE1);
	dump_table(MODULE1);
}

static void populate_min_max_voltage(void)
{
	u32 block, *v;

	block = sprd_ap_efuse_read(FUSE_LFM_MODULE0_BLKNO);
	v = (u32 *)(vt_mod0 + VID_V2);
	*v = block;
	debug("FUSE LFM MODULE0 # %x\n", block);

	block = sprd_ap_efuse_read(FUSE_HFM_MODULE0_BLKNO);
	v = (u32 *)(vt_mod0 + VID_V7);
	*v = block;
	hfm_vid_mod0 = block & 0xFFFF;
	if(hfm_vid_mod0 == 0)
	{
		/* Set this 1200mv	*/
		hfm_vid_mod0 = 0x100;
		printf("no efuse value\n");
	}
	debug("FUSE HFM MODULE0 # %x\n", block);

	block = sprd_ap_efuse_read(FUSE_LFM_MODULE1_BLKNO);
	v = (u32 *)(vt_mod1 + VID_V2);
	*v = block;
	debug("FUSE LFM MODULE1 # %x\n", block);

	block = sprd_ap_efuse_read(FUSE_HFM_MODULE1_BLKNO);
	v = (u32 *)(vt_mod1 + VID_V7);
	*v = block;
	hfm_vid_mod1 = block & 0xFFFF;
	if(hfm_vid_mod1 == 0)
	{
		/* Set this 1200mv	*/
		hfm_vid_mod1 = 0x100;
		printf("no efuse value\n");
	}
	debug("FUSE HFM MODULE1 # %x\n", block);

	block = sprd_ap_efuse_read(FUSE_IDV_BLKNO);
	debug("FUSE IDV %x\n", block);
}

/* 0xe44b0000/0xe44c0000 VMI control
   0xe44b0014/0xe44c0014 VMI delay1 (DVFS delay)
   0xe44b0020/0xe44c0020 VMI table
   0xe44b0024/0xe44c0024
   0xe44b0028/0xe44c0028
   0xe44b002C/0xe44c002c
   0xe44b0030/0xe44c0030
   0xe44b0034/0xe44c0034
   0xe44b0038/0xe44c0038
   0xe44b003C/0xe44c003c
   0xe44b0060/0xe44c0060 VMI delay 2 VDDCPU close ramp down to 0V delay
   0xe44b0064/0xe44c0064 VMI delay 3 VDDCPU open ramp up to VID2 delay
*/


void save_vids(void)
{
	int i;
	u32 no_entries = sizeof(vmi_offsets) / sizeof(u32);
	u32 *tbl0 = (u32*)VID_TABLE_DATA;
	u32 *tbl1 = tbl0 + no_entries;

	for (i = 0; i < no_entries; i++) {
		*(tbl0 + i) = *(u32 *)(dvfs_mod0 + vmi_offsets[i]);
		*(tbl1 + i) = *(u32 *)(dvfs_mod1 + vmi_offsets[i]);
	}
	dump_vmi();
}

static void mpll_auto_close(void)
{
	unsigned int var;

	/*MPLL0*/
	var = readl(REG_PMU_APB_MPLL0_REL_CFG);
	var &= 0xfffffeff;
	var |= 0x1;
	writel(var, REG_PMU_APB_MPLL0_REL_CFG);
	/*MPLL1*/
	var = readl(REG_PMU_APB_MPLL1_REL_CFG);
	var &= 0xfffffeff;
	var |= 0x1;
	writel(var, REG_PMU_APB_MPLL1_REL_CFG);
	/*CTRL PLL NO PD*/
	var = readl(0xe4270000);
	var &= 0xffffffef;
	writel(var, 0xe4270000);
	/*Pll_disconnect4_num*/
	var = readl(0xe4270008);
	var &= 0x2020ffff;
	var |= 0x20200000;
	writel(var, 0xe4270008);
	/*MPLL_PWR_THM0*/
	var = readl(REG_COM_PMU_APB_MPLL0_LP_CTRL0);
	var &= 0xfff0000f;
	var |= 0x02060;
	writel(var, REG_COM_PMU_APB_MPLL0_LP_CTRL0);
	/*MPLL_PWR_THM1*/
	var = readl(REG_COM_PMU_APB_MPLL1_LP_CTRL0);
	var &= 0xfff0000f;
	var |= 0x02060;
	writel(var, REG_COM_PMU_APB_MPLL1_LP_CTRL0);
}

void dvfs_init(void)
{
	unsigned int dvfs_enable;

	/* module 0*/
	writel(LAT_2_UPDATE_VDDCPU, (dvfs_mod0 + OFF_ADI_DLY1));
	writel(LAT_2_RAMPDN_VDDCPU_TO_0, (dvfs_mod0 + OFF_ADI_DLY2));
	writel(LAT_2_RAMPUP_VDDCPU_TO_V2, (dvfs_mod0 + OFF_ADI_DLY3));
	/* module 1*/
	writel(LAT_2_UPDATE_VDDCPU, (dvfs_mod1 + OFF_ADI_DLY1));
	writel(LAT_2_RAMPDN_VDDCPU_TO_0, (dvfs_mod1 + OFF_ADI_DLY2));
	writel(LAT_2_RAMPUP_VDDCPU_TO_V2, (dvfs_mod1 + OFF_ADI_DLY3));

	populate_min_max_voltage();

	dvfs_enable = (hfm_vid_mod0) << BAD_CFG_BIT ;
	dvfs_enable |= DVFS_ENABLE | ADI_MODE_EN;
	writel(dvfs_enable, dvfs_mod0);

	dvfs_enable = (hfm_vid_mod1) << BAD_CFG_BIT ;
	dvfs_enable |= DVFS_ENABLE | ADI_MODE_EN;
	writel(dvfs_enable, dvfs_mod1);

	/* enable channel 2/5/11 */
	adi_hwchannel_set(REG_ADI_CHNL2,LDO_SRAM_PD_ADI_ADDR);
	adi_hwchannel_set(REG_ADI_CHNL5,DCDC_ARM0_VOL_ADI_ADDR);
	adi_hwchannel_set(REG_ADI_CHNL11,DCDC_ARM1_VOL_ADI_ADDR);

	mpll_auto_close();

}

/* For VMM build microcode is not patched during download
 * skip p-state change if ucode version is zero in this case
 */
static inline uint32_t microcode_read_rev(void)
{
	/*
	 * Some Intel CPUs can be very finicky about the CPUID sequence used.
	 * So this is implemented in assembly so that it works reliably.
	 */
	uint32_t low, high;

	asm volatile (
		"xorl %%eax, %%eax\n"
		"xorl %%edx, %%edx\n"
		"movl %2, %%ecx\n"
		"wrmsr\n"
		"movl $0x01, %%eax\n"
		"cpuid\n"
		"movl %2, %%ecx\n"
		"rdmsr\n"
		: /* outputs */
		"=a" (low), "=d" (high)
		: /* inputs */
		"i" (MSR_IA32_UCODE_REV)
		: /* clobbers */
		 "ebx", "ecx"
	);

	return high;
}

void change_cpu_freq()
{
	unsigned long long msr_bits;
	unsigned long long msr_value;
	unsigned long fid, vid;
	int rev;
	boot_mode_t boot_role;
	chipram_env_t* cr_env = get_chipram_env();

	boot_role = cr_env->mode;

	/* if ucode is not patched
	 * return directly
	 */
	rev = microcode_read_rev();
	if (rev == 0)
		return;

	/*IA32_CR_MISC_ENABLES :Enable_GS3  */
	rdmsrl(MSR_IA32_MISC_ENABLES, msr_bits);
	msr_bits &= 0xfffffffffffefff7; /* Enable_GS3 : bit [16], AutoThrottleEnable : bit [3] */
	msr_bits |= 0x10000;    /* Programmed for Enable_GS3 = 1, AutoThrottleEnable = 0 */
	wrmsrl(MSR_IA32_MISC_ENABLES, msr_bits);

	/*CLOCK_CR_CST_CONFIG_CONTROL :Dynamic_L2_Enable  */
	rdmsrl(MSR_PMG_CST_CONFIG_CTL, msr_bits);
	msr_bits &= 0x00000000fffffff7; /* Dynamic_L2_Enable : bit [3] */
	msr_bits |= 0x808;    /* Programmed for Dynamic_L2_Enable = 1 */
	wrmsrl(MSR_PMG_CST_CONFIG_CTL, msr_bits);


	/* CLOCK_CR_GEYSIII_CONTROL  */
	rdmsrl(MSR_IA32_PERF_CTL, msr_bits);
	msr_bits &= 0xffffffffffffc080; /* Clear the select bits  */
	if(boot_role == BOOTLOADER_MODE_DOWNLOAD){
		/*  set module0 default freq 624M(0x0802)*/
		msr_value = (0x8 & 0x3F)<<8;   /* BUS_RATIO_SEL : bits [13:8] */
		msr_bits |= msr_value;
		msr_value = (2 & 0x7F);    /* VID_SEL : bits [6:0] */
		msr_bits |= msr_value;
		wrmsrl(MSR_IA32_PERF_CTL, msr_bits);
		debug("set freq ratio and vid to:0x%4x in BOOTLOADER_MODE_DOWNLOAD\n", msr_bits & 0x3F7F);
		return;
	}else{
		/*  set module0 default freq 1560M(0x1405)*/
		msr_value = (0x14 & 0x3F)<<8;   /* BUS_RATIO_SEL : bits [13:8] */
		msr_bits |= msr_value;
		msr_value = (5 & 0x7F);    /* VID_SEL : bits [6:0] */
		msr_bits |= msr_value;
	}

	wrmsrl(MSR_IA32_PERF_CTL, msr_bits);

	if (ANA_REG_GET(ANA_REG_GLB_CHIP_ID_LOW) < 0xC003) {
		rdmsrl(MSR_IA32_PERF_STATUS, msr_bits);
		vid = (unsigned long)msr_bits & 0xff;
		fid = (unsigned long)msr_bits >> 8;
		while ((vid != 5) && (fid != 0x14)) {
			rdmsrl(MSR_IA32_PERF_STATUS, msr_bits);
			vid = (unsigned long)msr_bits & 0xff;
			fid = (unsigned long)msr_bits >> 8;
		}

		msr_bits = 0; /* Clear the select bits  */
		msr_value = (0x14 & 0x3F)<<8;   /* BUS_RATIO_SEL : bits [13:8] */
		msr_bits |= msr_value;
		msr_value = (2 & 0x7F);    /* VID_SEL : bits [6:0] */
		msr_bits |= msr_value;

		wrmsrl(MSR_IA32_PERF_CTL, msr_bits);
	}

	debug("set freq ratio and vid to:%4x\n", msr_bits & 0x3F7F);
}
