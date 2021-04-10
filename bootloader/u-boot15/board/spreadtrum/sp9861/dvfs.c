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
#include <dvfs.h>

#define FUSE_LFM_MODULE0_BLKNO		55
#define FUSE_HFM_MODULE0_BLKNO		56
#define FUSE_LFM_MODULE1_BLKNO		57
#define FUSE_HFM_MODULE1_BLKNO		58
#define FUSE_IDV_BLKNO			59

static void *adi_base  = (void *)ADI_BASE_ADDR;
static void *dvfs_mod0 = (void *)ADDR_DVFS_EN_MOD0;
static void *dvfs_mod1 = (void *)ADDR_DVFS_EN_MOD1;
static struct pmic_vid *vt_mod0 = (struct pmic_vid *)VT_MOD0;
static struct pmic_vid *vt_mod1 = (struct pmic_vid *)VT_MOD1;

static u32 freq[] = {0, 936, 1248, 1560, 1872, 0};

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
	u32 low, high;

	rdmsr(MSR_IACORE_RATIOS, low, high);
	low >>= 16;
	low &= 0xFF;
	return low;
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
	WARN_ON(cal < 0);
	val = (cal << PMIC_CAL_BIT) | (ctrl << PMIC_CTRL_BIT)
		| (1 << PMIC_VLT_AVAIL_BIT);
	debug("val [%x] ctrl [%d] cal [%d] addr [%p]\n", val, ctrl, cal, v);
	writel(val, v);
}


static void setup_vid_table(int module)
{
	int i, mv_range;
	struct pmic_vid *v0, *v;
	int mv_v2, mv_v7, mv;

	v0 = (module == MODULE0) ? vt_mod0 : vt_mod1;
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
#else
static void dump_table(int module) {}
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
	debug("FUSE HFM MODULE0 # %x\n", block);

	block = sprd_ap_efuse_read(FUSE_LFM_MODULE1_BLKNO);
	v = (u32 *)(vt_mod1 + VID_V2);
	*v = block;
	debug("FUSE LFM MODULE1 # %x\n", block);

	block = sprd_ap_efuse_read(FUSE_HFM_MODULE1_BLKNO);
	v = (u32 *)(vt_mod1 + VID_V7);
	*v = block;
	debug("FUSE HFM MODULE1 # %x\n", block);

	block = sprd_ap_efuse_read(FUSE_IDV_BLKNO);
	debug("FUSE IDV %x\n", block);
}

void dvfs_init(void)
{
	/* Enable 2 wire	*/
	writel(ENABLE_2WIRE, (adi_base + OFF_ADI_RF_GSSI));
	writel(ENABLE_ADI_CHNL5 | ENABLE_ADI_CHNL11,
	       (adi_base + OFF_ADI_CHNLS));
	/* evt0 l2sram shutoff	*/
	writel(CHNL02_ADDR, (adi_base + OFF_PMU_CHNL02));
	/* VDD ARM0 */
	writel(CHNL05_ADDR, (adi_base + OFF_PMU_CHNL05));
	/* VDD ARM1 */
	writel(CHNL11_ADDR, (adi_base + OFF_PMU_CHNL11));
	/* module 0*/
	writel(DVFS_ENABLE, dvfs_mod0);
	writel(LAT_2_UPDATE_VDDCPU, (dvfs_mod0 + OFF_ADI_DLY1));
	writel(LAT_2_RAMPDN_VDDCPU_TO_0, (dvfs_mod0 + OFF_ADI_DLY2));
	writel(LAT_2_RAMPUP_VDDCPU_TO_V2, (dvfs_mod0 + OFF_ADI_DLY3));
	/* module 1*/
	writel(DVFS_ENABLE, dvfs_mod1);
	writel(LAT_2_UPDATE_VDDCPU, (dvfs_mod1 + OFF_ADI_DLY1));
	writel(LAT_2_RAMPDN_VDDCPU_TO_0, (dvfs_mod1 + OFF_ADI_DLY2));
	writel(LAT_2_RAMPUP_VDDCPU_TO_V2, (dvfs_mod1 + OFF_ADI_DLY3));
	populate_min_max_voltage();
}

