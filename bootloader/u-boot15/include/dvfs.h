/*
 * Copyright (C) 2016, Intel Corporation
 *
 * SPDX-License-Identifier:     GPL-2.0+
 *
 */

#ifndef __DVFS_H__
#define __DVFS_H__

#define NO_OF_PSTATES                   0x6
#define LFM_INDEX                       0x0
#define HFM_INDEX                       0x5
#define FSB_FREQ_MHZ			0x4E
#define VT_BASE_OFF			0x20
#define MODULE0				0x00
#define MODULE1				0x01
#define ADDR_DVFS_EN_MOD0		0xE44B0000
#define ADDR_DVFS_EN_MOD1		0xE44C0000
#define VT_MOD0				(ADDR_DVFS_EN_MOD0 + VT_BASE_OFF)
#define VT_MOD1				(ADDR_DVFS_EN_MOD1 + VT_BASE_OFF)
#define OFF_ADI_DLY1			0x14
#define OFF_ADI_DLY2			0x60
#define OFF_ADI_DLY3			0x64
#define REG_ADI_CHNL2			(2)
#define REG_ADI_CHNL5			(5)
#define REG_ADI_CHNL11			(11)
/*0x40038c00 + 0x00000054 */
#define DCDC_ARM0_VOL_ADI_ADDR			(0x8C54)
 /*0x40038c00 + 0x00000064 */
#define DCDC_ARM1_VOL_ADI_ADDR			(0x8C64)
/*0x40038c00 + 0x00000178 */
#define LDO_SRAM_PD_ADI_ADDR			(0x8D78)

/* ADI mode is by default. Hence no need to set it again */
#define ADI_MODE_EN	(0x1 << 0)
#define DVFS_ENABLE			(0x1 << VDDCPU_SHUTDWN_BIT) | \
					(0x1 << BAD_REQ_INT_BIT)

/* The default value is 0x1800 and delay time is about 50us
 * (for 128MHz AON APB clock) or 200us (for default 26MHz AON APB clock).  
 * During fine tune DVFS function, these delay times shall
 * be modified according to voltage response latency of PMIC.
 * Delay1 is VDDCPU modification latency(2us).
 * Delay2 is VDDCPU shutdown latency (500us – 1ms).
 * Delay3 is VDDCPU open latency(200us).
*/

/* For AON APB clock 128 MHZ
 * 128 x 10^6 -> 10^6us
 * Delay 1 is 2us
 * Delay 1 = (128 x 10^6 / 10^6) x 2
 *	   =  128 x 2 = 256
 * Delay 2 is 500us
 *	   = 128 * 500 = 64000
 * Delay 3 is 200us
 *	   = 128 * 200 = 25600
*/

/* For AON APB clock 26 MHZ
 * 26 x 10^6 -> 10^6us
 * Delay 1 is 2us
 * Delay 1 = (26 x 10^6 / 10^6) x 2
 *	   =  26 x 2 = 52
 * Delay 2 is 500us
 *	   = 26 * 500 = 13000
 * Delay 3 is 200us
 *	   = 26 * 200 = 5200
*/

/* Assuming 128MHz is currently used */
#define LAT_2_UPDATE_VDDCPU		0x00001800
#define LAT_2_RAMPDN_VDDCPU_TO_0	0x00001800
#define LAT_2_RAMPUP_VDDCPU_TO_V2	0x00006400

#define VLT_MAP_WORK_MODE_BIT		0x0
#define	ADI_MODE			0x1
#define SOFT_MODE			0x3

#define VDDCPU_SHUTDWN_BIT		0x5
#define BAD_CFG_VLT			0xBAD
#define BAD_CFG_BIT			16
#define BAD_REQ_INT_BIT                 4

#define VF_TABLE_LOCK_BIT		7
#define	VF_TABLE_LOCK			1
#define	VF_TABLE_UNLOCK			0

#define PMIC_VLT_AVAIL_BIT		31
#define PMIC_CTRL_BIT			5
#define PMIC_CAL_BIT			0

#define PMIC_VLT_INTERCEPT		400
#define PMIC_CTRL_MUL			100

/* FIXED POINT CAL PRECISION	3.125 * 256*/
#define PMIC_CAL_PRECISION		800

#define FRAC_BITS 8
#define int_tofp(X) ((int64_t)(X) << FRAC_BITS)
#define fp_toint(X) ((X) >> FRAC_BITS)

enum vid_encode {
	VID_V0 = 0x0,
	VID_V1,
	VID_V2,
	VID_V3,
	VID_V4,
	VID_V5,
	VID_V6,
	VID_V7,
	VID_INVALID,
};

struct pmic_vid {
	u32 cal:5;
	u32 ctrl:5;
	u32 res:21;
	u32 avail:1;
};

static inline int32_t mul_fp(int32_t x, int32_t y)
{
	return ((int64_t)x * (int64_t)y) >> FRAC_BITS;
}

static inline int32_t div_fp(int32_t x, int32_t y)
{
	return ((int64_t)x << FRAC_BITS) / y;
}

static inline int ceiling_fp(int32_t x)
{
	int mask, ret;

	ret = fp_toint(x);
	mask = (1 << FRAC_BITS) - 1;
	if (x & mask)
		ret += 1;
	return ret;
}

extern int adi_hwchannel_set(unsigned int chn, unsigned int config);
#endif
