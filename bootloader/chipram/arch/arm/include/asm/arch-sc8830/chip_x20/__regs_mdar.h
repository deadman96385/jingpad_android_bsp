/*
 * Copyright (C) 2014 Spreadtrum Communications Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 *************************************************
 * Automatically generated C header: do not edit *
 *************************************************
 */

#if 0
#ifndef __SCI_GLB_REGS_H__
#error  "Don't include this file directly, Pls include sci_glb_regs.h"
#endif
#endif

#ifndef _MDAR_APB_REG_H
#define _MDAR_APB_REG_H

#define	REG_MDAR_APB


/*

Base address: 
	AP_AHB/AON　          		0x4009_0000;
	CP0_ARM                    	0x0209_0000;
	CP0_DSP/CP0_DSP1 			0x2209_0000;
	CP1_ARM                    	0x0209_0000;
	CP1_DSP                     0x0209_0000.

*/

#define CTL_BASE_MDAR               0x40090000
#define CTL_BASE_MDAR_APB       	CTL_BASE_MDAR

/* registers definitions for MDAR_APB */
#define REG_MDAR_CFG0                                     (CTL_BASE_MDAR_APB + 0x0000)
#define REG_MDAR_CFG1                                     (CTL_BASE_MDAR_APB + 0x0004)
#define REG_MDAR_CFG3                                     (CTL_BASE_MDAR_APB + 0x000C)
#define REG_MDAR_DAC1_CTR1                                (CTL_BASE_MDAR_APB + 0x0010)
#define REG_MDAR_DAC1_CTR2                                (CTL_BASE_MDAR_APB + 0x0014)
#define REG_MDAR_DAC1_CTR3                                (CTL_BASE_MDAR_APB + 0x0018)
#define REG_MDAR_DAC1_CTR4                                (CTL_BASE_MDAR_APB + 0x001C)
#define REG_MDAR_DAC1_STS0                                (CTL_BASE_MDAR_APB + 0x0020)
#define REG_MDAR_DAC1_STS1                                (CTL_BASE_MDAR_APB + 0x0024)
#define REG_MDAR_CAL1_CTR0                                (CTL_BASE_MDAR_APB + 0x0028)
#define REG_MDAR_CAL1_CTR1                                (CTL_BASE_MDAR_APB + 0x002C)
#define REG_MDAR_CAL1_CTR3                                (CTL_BASE_MDAR_APB + 0x0030)
#define REG_MDAR_CAL1_STS0                                (CTL_BASE_MDAR_APB + 0x0034)
#define REG_MDAR_CAL1_STS1                                (CTL_BASE_MDAR_APB + 0x0038)
#define REG_MDAR_DAC1_CTR00                               (CTL_BASE_MDAR_APB + 0x003C)
#define REG_MDAR_DAC1_CTR10                               (CTL_BASE_MDAR_APB + 0x0040)
#define REG_MDAR_ADC1_CTR0                                (CTL_BASE_MDAR_APB + 0x0044)
#define REG_MDAR_ADC1_CTR00                               (CTL_BASE_MDAR_APB + 0x0048)
#define REG_MDAR_ADC1_CTR01                               (CTL_BASE_MDAR_APB + 0x004C)
#define REG_MDAR_ADC1_CTR02                               (CTL_BASE_MDAR_APB + 0x0050)
#define REG_MDAR_ADC1_CTR10                               (CTL_BASE_MDAR_APB + 0x0054)
#define REG_MDAR_ADC1_CTR11                               (CTL_BASE_MDAR_APB + 0x0058)
#define REG_MDAR_ADC1_CTR12                               (CTL_BASE_MDAR_APB + 0x005C)
#define REG_MDAR_ADC1_CTR20                               (CTL_BASE_MDAR_APB + 0x0060)
#define REG_MDAR_ADC1_CTR21                               (CTL_BASE_MDAR_APB + 0x0064)
#define REG_MDAR_ADC1_CTR22                               (CTL_BASE_MDAR_APB + 0x0068)
#define REG_MDAR_DAC2_CTR1                                (CTL_BASE_MDAR_APB + 0x0070)
#define REG_MDAR_DAC2_CTR2                                (CTL_BASE_MDAR_APB + 0x0074)
#define REG_MDAR_DAC2_CTR3                                (CTL_BASE_MDAR_APB + 0x0078)
#define REG_MDAR_DAC2_CTR4                                (CTL_BASE_MDAR_APB + 0x007C)
#define REG_MDAR_DAC2_STS0                                (CTL_BASE_MDAR_APB + 0x0080)
#define REG_MDAR_DAC2_STS1                                (CTL_BASE_MDAR_APB + 0x0084)
#define REG_MDAR_CAL2_CTR0                                (CTL_BASE_MDAR_APB + 0x0088)
#define REG_MDAR_CAL2_CTR1                                (CTL_BASE_MDAR_APB + 0x008C)
#define REG_MDAR_CAL2_CTR3                                (CTL_BASE_MDAR_APB + 0x0090)
#define REG_MDAR_CAL2_STS0                                (CTL_BASE_MDAR_APB + 0x0094)
#define REG_MDAR_CAL2_STS1                                (CTL_BASE_MDAR_APB + 0x0098)
#define REG_MDAR_DAC2_CTR00                               (CTL_BASE_MDAR_APB + 0x009C)
#define REG_MDAR_DAC2_CTR10                               (CTL_BASE_MDAR_APB + 0x00A0)
#define REG_MDAR_ADC2_CTR0                                (CTL_BASE_MDAR_APB + 0x00A4)
#define REG_MDAR_ADC2_CTR00                               (CTL_BASE_MDAR_APB + 0x00A8)
#define REG_MDAR_ADC2_CTR01                               (CTL_BASE_MDAR_APB + 0x00AC)
#define REG_MDAR_ADC2_CTR02                               (CTL_BASE_MDAR_APB + 0x00B0)
#define REG_MDAR_ADC2_CTR10                               (CTL_BASE_MDAR_APB + 0x00B4)
#define REG_MDAR_ADC2_CTR11                               (CTL_BASE_MDAR_APB + 0x00B8)
#define REG_MDAR_ADC2_CTR12                               (CTL_BASE_MDAR_APB + 0x00BC)
#define REG_MDAR_ADC2_CTR20                               (CTL_BASE_MDAR_APB + 0x00C0)
#define REG_MDAR_ADC2_CTR21                               (CTL_BASE_MDAR_APB + 0x00C4)
#define REG_MDAR_ADC2_CTR22                               (CTL_BASE_MDAR_APB + 0x00C8)
#define REG_MDAR_DAC3_CTR1                                (CTL_BASE_MDAR_APB + 0x00D0)
#define REG_MDAR_DAC3_CTR2                                (CTL_BASE_MDAR_APB + 0x00D4)
#define REG_MDAR_DAC3_CTR3                                (CTL_BASE_MDAR_APB + 0x00D8)
#define REG_MDAR_DAC3_CTR4                                (CTL_BASE_MDAR_APB + 0x00DC)
#define REG_MDAR_DAC3_STS0                                (CTL_BASE_MDAR_APB + 0x00E0)
#define REG_MDAR_DAC3_STS1                                (CTL_BASE_MDAR_APB + 0x00E4)
#define REG_MDAR_CAL3_CTR0                                (CTL_BASE_MDAR_APB + 0x00E8)
#define REG_MDAR_CAL3_CTR1                                (CTL_BASE_MDAR_APB + 0x00EC)
#define REG_MDAR_CAL3_CTR3                                (CTL_BASE_MDAR_APB + 0x00F0)
#define REG_MDAR_CAL3_STS0                                (CTL_BASE_MDAR_APB + 0x00F4)
#define REG_MDAR_CAL3_STS1                                (CTL_BASE_MDAR_APB + 0x00F8)
#define REG_MDAR_DAC3_CTR00                               (CTL_BASE_MDAR_APB + 0x00FC)
#define REG_MDAR_DAC3_CTR10                               (CTL_BASE_MDAR_APB + 0x0100)
#define REG_MDAR_ADC3_CTR0                                (CTL_BASE_MDAR_APB + 0x0104)
#define REG_MDAR_ADC3_CTR00                               (CTL_BASE_MDAR_APB + 0x0108)
#define REG_MDAR_ADC3_CTR01                               (CTL_BASE_MDAR_APB + 0x010C)
#define REG_MDAR_ADC3_CTR02                               (CTL_BASE_MDAR_APB + 0x0110)
#define REG_MDAR_ADC3_CTR10                               (CTL_BASE_MDAR_APB + 0x0114)
#define REG_MDAR_ADC3_CTR11                               (CTL_BASE_MDAR_APB + 0x0118)
#define REG_MDAR_ADC3_CTR12                               (CTL_BASE_MDAR_APB + 0x011C)
#define REG_MDAR_ADC3_CTR20                               (CTL_BASE_MDAR_APB + 0x0120)
#define REG_MDAR_ADC3_CTR21                               (CTL_BASE_MDAR_APB + 0x0124)
#define REG_MDAR_ADC3_CTR22                               (CTL_BASE_MDAR_APB + 0x0128)
#define REG_MDAR_AFCDAC1_CFG                              (CTL_BASE_MDAR_APB + 0x012C)
#define REG_MDAR_AFCDAC2_CFG                              (CTL_BASE_MDAR_APB + 0x0130)
#define REG_MDAR_APCDAC1_CFG                              (CTL_BASE_MDAR_APB + 0x0134)
#define REG_MDAR_APCDAC2_CFG                              (CTL_BASE_MDAR_APB + 0x0138)
#define REG_MDAR_RFSPI_CFG                                (CTL_BASE_MDAR_APB + 0x13C)
#define REG_MDAR_RFMIPI_CFG                               (CTL_BASE_MDAR_APB + 0x140)
#define REG_MDAR_APCDAC_OUTSEL                            (CTL_BASE_MDAR_APB + 0x144)
#define REG_MDAR_CLASH_CHK                                (CTL_BASE_MDAR_APB + 0x148)
#define REG_MDAR_CLASH_SNAP                               (CTL_BASE_MDAR_APB + 0x14C)
#define REG_MDAR_CLASH_STATUS1                            (CTL_BASE_MDAR_APB + 0x150)
#define REG_MDAR_CLASH_STATUS2                            (CTL_BASE_MDAR_APB + 0x154)
#define REG_MDAR_CLASH_STATUS3                            (CTL_BASE_MDAR_APB + 0x158)
#define REG_MDAR_EXTRA_CFG0                               (CTL_BASE_MDAR_APB + 0x160)
#define REG_MDAR_EXTRA_CFG1                               (CTL_BASE_MDAR_APB + 0x164)
#define REG_MDAR_RFCTRL15_INF0                            (CTL_BASE_MDAR_APB + 0x168)
#define REG_MDAR_RFCTRL15_INF1                            (CTL_BASE_MDAR_APB + 0x16C)
#define REG_MDAR_RFCTRL15_INF2                            (CTL_BASE_MDAR_APB + 0x170)
#define REG_MDAR_RFCTRL15_INF3                            (CTL_BASE_MDAR_APB + 0x174)
#define REG_MDAR_RFCTRL15_INF4                            (CTL_BASE_MDAR_APB + 0x178)
#define REG_MDAR_RFCTRL15_INF5                            (CTL_BASE_MDAR_APB + 0x17C)
#define REG_MDAR_RFCTRL15_INF6                            (CTL_BASE_MDAR_APB + 0x180)
#define REG_MDAR_CFG4                                     (CTL_BASE_MDAR_APB + 0x0184)
#define REG_MDAR_CFG5                                     (CTL_BASE_MDAR_APB + 0x0188)
#define REG_MDAR_CFG6                                     (CTL_BASE_MDAR_APB + 0x018C)
#define REG_MDAR_CFG7                                     (CTL_BASE_MDAR_APB + 0x0190)
#define REG_MDAR_CFG8                                     (CTL_BASE_MDAR_APB + 0x0194)
#define REG_MDAR_CFG9                                     (CTL_BASE_MDAR_APB + 0x0198)
#define REG_MDAR_CFG10                                    (CTL_BASE_MDAR_APB + 0x019C)
#define REG_MDAR_CFG11                                    (CTL_BASE_MDAR_APB + 0x01B0)
#define REG_MDAR_CFG12                                    (CTL_BASE_MDAR_APB + 0x01B4)
#define REG_MDAR_CFG13                                    (CTL_BASE_MDAR_APB + 0x01B8)
#define REG_MDAR_CFG14                                    (CTL_BASE_MDAR_APB + 0x01BC)
#define REG_MDAR_CFG15                                    (CTL_BASE_MDAR_APB + 0x1C0)
#define REG_MDAR_IMB_CFG10                                (CTL_BASE_MDAR_APB + 0x1C4)
#define REG_MDAR_IMB_CFG11                                (CTL_BASE_MDAR_APB + 0x1C8)
#define REG_MDAR_IMB_CFG12                                (CTL_BASE_MDAR_APB + 0x1CC)
#define REG_MDAR_IMB_CFG13                                (CTL_BASE_MDAR_APB + 0x1D0)
#define REG_MDAR_IMB_CFG14                                (CTL_BASE_MDAR_APB + 0x1D4)
#define REG_MDAR_IMB_CFG20                                (CTL_BASE_MDAR_APB + 0x1D8)
#define REG_MDAR_IMB_CFG21                                (CTL_BASE_MDAR_APB + 0x1DC)
#define REG_MDAR_IMB_CFG22                                (CTL_BASE_MDAR_APB + 0x1E0)
#define REG_MDAR_IMB_CFG23                                (CTL_BASE_MDAR_APB + 0x1E4)
#define REG_MDAR_IMB_CFG24                                (CTL_BASE_MDAR_APB + 0x1E8)
#define REG_MDAR_IMB_CFG30                                (CTL_BASE_MDAR_APB + 0x1EC)
#define REG_MDAR_IMB_CFG31                                (CTL_BASE_MDAR_APB + 0x1F0)
#define REG_MDAR_IMB_CFG32                                (CTL_BASE_MDAR_APB + 0x1F4)
#define REG_MDAR_IMB_CFG33                                (CTL_BASE_MDAR_APB + 0x1F8)
#define REG_MDAR_IMB_CFG34                                (CTL_BASE_MDAR_APB + 0x1FC)
#define REG_MDAR_RFTI_CFG0                                (CTL_BASE_MDAR_APB + 0x0200)
#define REG_MDAR_RFTI_CFG1                                (CTL_BASE_MDAR_APB + 0x0204)
#define REG_MDAR_RFTI_CFG2                                (CTL_BASE_MDAR_APB + 0x0208)
#define REG_MDAR_RFTI_CFG3                                (CTL_BASE_MDAR_APB + 0x020C)
#define REG_MDAR_RFTI_SBI1_CFG0                           (CTL_BASE_MDAR_APB + 0x0210)
#define REG_MDAR_RFTI_SBI1_CFG1                           (CTL_BASE_MDAR_APB + 0x0214)
#define REG_MDAR_RFTI_SBI1_CMD0                           (CTL_BASE_MDAR_APB + 0x0218)
#define REG_MDAR_RFTI_SBI1_CMD1                           (CTL_BASE_MDAR_APB + 0x021C)
#define REG_MDAR_RFTI_SBI1_CMD2                           (CTL_BASE_MDAR_APB + 0x0220)
#define REG_MDAR_RFTI_SBI1_RDATA                          (CTL_BASE_MDAR_APB + 0x0224)
#define REG_MDAR_RFTI_SBI2_CFG0                           (CTL_BASE_MDAR_APB + 0x0228)
#define REG_MDAR_RFTI_SBI2_CFG1                           (CTL_BASE_MDAR_APB + 0x022C)
#define REG_MDAR_RFTI_SBI2_CMD0                           (CTL_BASE_MDAR_APB + 0x0230)
#define REG_MDAR_RFTI_SBI2_CMD1                           (CTL_BASE_MDAR_APB + 0x0234)
#define REG_MDAR_RFTI_SBI2_CMD2                           (CTL_BASE_MDAR_APB + 0x0238)
#define REG_MDAR_RFTI_SBI2_RDATA                          (CTL_BASE_MDAR_APB + 0x023C)
#define REG_MDAR_RFTI1_INFO0                              (CTL_BASE_MDAR_APB + 0x0240)
#define REG_MDAR_RFTI1_INFO1                              (CTL_BASE_MDAR_APB + 0x0244)
#define REG_MDAR_RFTI1_INFO2                              (CTL_BASE_MDAR_APB + 0x0248)
#define REG_MDAR_RFTI1_INFO3                              (CTL_BASE_MDAR_APB + 0x024C)
#define REG_MDAR_RFTI2_INFO0                              (CTL_BASE_MDAR_APB + 0x0250)
#define REG_MDAR_RFTI2_INFO1                              (CTL_BASE_MDAR_APB + 0x0254)
#define REG_MDAR_RFTI2_INFO2                              (CTL_BASE_MDAR_APB + 0x0258)
#define REG_MDAR_RFTI2_INFO3                              (CTL_BASE_MDAR_APB + 0x025C)
#define REG_MDAR_RFTI11_DUG_BUS                           (CTL_BASE_MDAR_APB + 0x0260)
#define REG_MDAR_RFTI12_DUG_BUS                           (CTL_BASE_MDAR_APB + 0x0264)



/* bits definitions for register REG_MDAR_CFG0 */
#define BIT_MDAR_APB_MDAR_ADA_MODE                        ( BIT_(31) )
#define BIT_MDAR_APB_ADC3_CHANNEL_SSET(_X_)               ( (_X_) << 26 & (BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)) )
#define BIT_MDAR_APB_ADC2_CHANNEL_SSET(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)) )
#define BIT_MDAR_APB_ADC1_CHANNEL_SSET(_X_)               ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_MDAR_WTG_MODE                        ( BIT_(15) )
#define BIT_MDAR_APB_ADC3_CHANNEL_MASK(_X_)               ( (_X_) << 10 & (BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)) )
#define BIT_MDAR_APB_ADC2_CHANNEL_MASK(_X_)               ( (_X_) << 5 & (BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)) )
#define BIT_MDAR_APB_ADC1_CHANNEL_MASK(_X_)               ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)) )

/* bits definitions for register REG_MDAR_CFG1 */
#define BIT_MDAR_APB_DAC3_CHANNEL_SSET(_X_)               ( (_X_) << 26 & (BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)) )
#define BIT_MDAR_APB_DAC2_CHANNEL_SSET(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)) )
#define BIT_MDAR_APB_DAC1_CHANNEL_SSET(_X_)               ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_DAC3_CHANNEL_MASK(_X_)               ( (_X_) << 10 & (BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)) )
#define BIT_MDAR_APB_DAC2_CHANNEL_MASK(_X_)               ( (_X_) << 5 & (BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)) )
#define BIT_MDAR_APB_DAC1_CHANNEL_MASK(_X_)               ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)) )

/* bits definitions for register REG_MDAR_CFG3 */
#define BIT_MDAR_APB_DACX_SBC_SET(_X_)                    ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)) )
#define BIT_MDAR_APB_ADCX_SBC_SET(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)) )

/* bits definitions for register REG_MDAR_DAC1_CTR1 */
#define BIT_MDAR_APB_DAC1_WD_OVR(_X_)                     ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_DAC1_WADDR_OVR(_X_)                  ( (_X_) << 4 & (BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)) )
#define BIT_MDAR_APB_DAC1_WLE_OVR                         ( BIT_(2) )
#define BIT_MDAR_APB_DAC1_W_OVR_I_QN                      ( BIT_(1) )
#define BIT_MDAR_APB_DAC1_W_OVR_EN                        ( BIT_(0) )

/* bits definitions for register REG_MDAR_DAC1_CTR2 */
#define BIT_MDAR_APB_DAC1_AUTO_RST                        ( BIT_(23) )
#define BIT_MDAR_APB_DAC1_SOFT_RST                        ( BIT_(22) )
#define BIT_MDAR_APB_DAC1_OSBC                            ( BIT_(21) )
#define BIT_MDAR_APB_DAC1_ISBC                            ( BIT_(20) )
#define BIT_MDAR_APB_DAC1_OVR_EN_CAL                      ( BIT_(19) )
#define BIT_MDAR_APB_DAC1_EN_OOSCAL                       ( BIT_(18) )
#define BIT_MDAR_APB_DAC1_IQSWAP                          ( BIT_(17) )
#define BIT_MDAR_APB_DAC1_CAL_START                       ( BIT_(16) )
#define BIT_MDAR_APB_DAC1_OFFSETI(_X_)                    ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )
#define BIT_MDAR_APB_DAC1_OFFSETQ(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)) )

/* bits definitions for register REG_MDAR_DAC1_CTR3 */
#define BIT_MDAR_APB_DAC1_Q_DC(_X_)                       ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)) )
#define BIT_MDAR_APB_DAC1_I_DC(_X_)                       ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)) )

/* bits definitions for register REG_MDAR_DAC1_CTR4 */
#define BIT_MDAR_APB_DAC1_I_CAL(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)) )
#define BIT_MDAR_APB_DAC1_Q_CAL(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)) )

/* bits definitions for register REG_MDAR_DAC1_STS0 */
#define BIT_MDAR_APB_DAC1_WTI(_X_)                        ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_DAC1_WTQ(_X_)                        ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_DAC1_STS1 */
#define BIT_MDAR_APB_DAC1_DA_STATE(_X_)                   ( (_X_) << 17 & (BIT_(17)|BIT_(18)) )
#define BIT_MDAR_APB_DAC1_DONE                            ( BIT_(16) )
#define BIT_MDAR_APB_DAC1_WQ_OVR(_X_)                     ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_CAL1_CTR0 */
#define BIT_MDAR_APB_ADC1_CLK_CAL_DLY(_X_)                ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)) )
#define BIT_MDAR_APB_ADA1_CAL_WAIT(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )
#define BIT_MDAR_APB_CLK_ADA1_CAL_EN                      ( BIT_(6) )
#define BIT_MDAR_APB_DAC1_PD_CAL                          ( BIT_(5) )
#define BIT_MDAR_APB_ADC1_EN_CAL                          ( BIT_(3) )
#define BIT_MDAR_APB_ADC1_CAL                             ( BIT_(1) )
#define BIT_MDAR_APB_ADA1_MODE_SEL                        ( BIT_(0) )

/* bits definitions for register REG_MDAR_CAL1_CTR1 */
#define BIT_MDAR_APB_ADC1_Q_DC(_X_)                       ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC1_I_DC(_X_)                       ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)) )

/* bits definitions for register REG_MDAR_CAL1_CTR3 */
#define BIT_MDAR_APB_ADA1_CAL_START                       ( BIT_(0) )

/* bits definitions for register REG_MDAR_CAL1_STS0 */
#define BIT_MDAR_APB_ADA1_CAL_DONE                        ( BIT_(31) )
#define BIT_MDAR_APB_ADC1_CAL_I_SUM(_X_)                  ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)) )

/* bits definitions for register REG_MDAR_CAL1_STS1 */
#define BIT_MDAR_APB_ADC1_CAL_Q_SUM(_X_)                  ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)) )

/* bits definitions for register REG_MDAR_DAC1_CTR00 */
#define BIT_MDAR_APB_DAC1_OUT_SEL_2                       ( BIT_(26) )
#define BIT_MDAR_APB_DAC1_RSV_2(_X_)                      ( (_X_) << 22 & (BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)) )
#define BIT_MDAR_APB_DAC1_PCTRL_2(_X_)                    ( (_X_) << 19 & (BIT_(19)|BIT_(20)|BIT_(21)) )
#define BIT_MDAR_APB_DAC1_CLK_SEL_2                       ( BIT_(18) )
#define BIT_MDAR_APB_DAC1_OUT_SEL_1                       ( BIT_(17) )
#define BIT_MDAR_APB_DAC1_RSV_1(_X_)                      ( (_X_) << 13 & (BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)) )
#define BIT_MDAR_APB_DAC1_PCTRL_1(_X_)                    ( (_X_) << 10 & (BIT_(10)|BIT_(11)|BIT_(12)) )
#define BIT_MDAR_APB_DAC1_CLK_SEL_1                       ( BIT_(9) )
#define BIT_MDAR_APB_DAC1_OUT_SEL_0                       ( BIT_(8) )
#define BIT_MDAR_APB_DAC1_RSV_0(_X_)                      ( (_X_) << 4 & (BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)) )
#define BIT_MDAR_APB_DAC1_PCTRL_0(_X_)                    ( (_X_) << 1 & (BIT_(1)|BIT_(2)|BIT_(3)) )
#define BIT_MDAR_APB_DAC1_CLK_SEL_0                       ( BIT_(0) )

/* bits definitions for register REG_MDAR_DAC1_CTR10 */
#define BIT_MDAR_APB_DAC1_OUT_SEL_5                       ( BIT_(26) )
#define BIT_MDAR_APB_DAC1_RSV_5(_X_)                      ( (_X_) << 22 & (BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)) )
#define BIT_MDAR_APB_DAC1_PCTRL_5(_X_)                    ( (_X_) << 19 & (BIT_(19)|BIT_(20)|BIT_(21)) )
#define BIT_MDAR_APB_DAC1_CLK_SEL_5                       ( BIT_(18) )
#define BIT_MDAR_APB_DAC1_OUT_SEL_4                       ( BIT_(17) )
#define BIT_MDAR_APB_DAC1_RSV_4(_X_)                      ( (_X_) << 13 & (BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)) )
#define BIT_MDAR_APB_DAC1_PCTRL_4(_X_)                    ( (_X_) << 10 & (BIT_(10)|BIT_(11)|BIT_(12)) )
#define BIT_MDAR_APB_DAC1_CLK_SEL_4                       ( BIT_(9) )
#define BIT_MDAR_APB_DAC1_OUT_SEL_3                       ( BIT_(8) )
#define BIT_MDAR_APB_DAC1_RSV_3(_X_)                      ( (_X_) << 4 & (BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)) )
#define BIT_MDAR_APB_DAC1_PCTRL_3(_X_)                    ( (_X_) << 1 & (BIT_(1)|BIT_(2)|BIT_(3)) )
#define BIT_MDAR_APB_DAC1_CLK_SEL_3                       ( BIT_(0) )

/* bits definitions for register REG_MDAR_ADC1_CTR0 */
#define BIT_MDAR_APB_ADC1_SOFT_RST                        ( BIT_(31) )
#define BIT_MDAR_APB_ADC1_DLL_OUT(_X_)                    ( (_X_) << 25 & (BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)) )
#define BIT_MDAR_APB_ADC1_CALRDOUT(_X_)                   ( (_X_) << 11 & (BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC1_DLL_SOFT_RST                    ( BIT_(10) )
#define BIT_MDAR_APB_ADC1_CAL_SOFT_RST                    ( BIT_(9) )
#define BIT_MDAR_APB_ADC1_CALRD                           ( BIT_(8) )
#define BIT_MDAR_APB_ADC1_CALEN                           ( BIT_(7) )
#define BIT_MDAR_APB_ADC1_CALADDR(_X_)                    ( (_X_) << 1 & (BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)) )
#define BIT_MDAR_APB_ADC1_DEBUG_EN                        ( BIT_(0) )

/* bits definitions for register REG_MDAR_ADC1_CTR00 */
#define BIT_MDAR_APB_ADC1_RSV_1(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_ADC1_RSV_0(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_ADC1_CTR01 */
#define BIT_MDAR_APB_ADC1_DIG_CLK_SEL_0                   ( BIT_(30) )
#define BIT_MDAR_APB_ADC1_VCM_SEL_0                       ( BIT_(29) )
#define BIT_MDAR_APB_ADC1_DELAY_CAP_0(_X_)                ( (_X_) << 27 & (BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC1_BIT_SEL_0(_X_)                  ( (_X_) << 25 & (BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_ADC1_VREF_SEL_0(_X_)                 ( (_X_) << 23 & (BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC1_VREF_BOOST_0(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_ADC1_QUANT_BOOST_0(_X_)              ( (_X_) << 19 & (BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_ADC1_DLLRD_0                         ( BIT_(18) )
#define BIT_MDAR_APB_ADC1_DLLWR_0                         ( BIT_(17) )
#define BIT_MDAR_APB_ADC1_DLLEN_0                         ( BIT_(16) )
#define BIT_MDAR_APB_ADC1_CSBC                            ( BIT_(15) )
#define BIT_MDAR_APB_ADC1_IQSWAP                          ( BIT_(14) )
#define BIT_MDAR_APB_ADC1_DLLOOF_0(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_ADC1_OSBC                            ( BIT_(7) )
#define BIT_MDAR_APB_ADC1_ISBC                            ( BIT_(6) )
#define BIT_MDAR_APB_ADC1_DLLIN_0(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)) )

/* bits definitions for register REG_MDAR_ADC1_CTR02 */
#define BIT_MDAR_APB_ADC1_DIG_CLK_SEL_1                   ( BIT_(30) )
#define BIT_MDAR_APB_ADC1_VCM_SEL_1                       ( BIT_(29) )
#define BIT_MDAR_APB_ADC1_DELAY_CAP_1(_X_)                ( (_X_) << 27 & (BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC1_BIT_SEL_1(_X_)                  ( (_X_) << 25 & (BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_ADC1_VREF_SEL_1(_X_)                 ( (_X_) << 23 & (BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC1_VREF_BOOST_1(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_ADC1_QUANT_BOOST_1(_X_)              ( (_X_) << 19 & (BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_ADC1_DLLRD_1                         ( BIT_(18) )
#define BIT_MDAR_APB_ADC1_DLLWR_1                         ( BIT_(17) )
#define BIT_MDAR_APB_ADC1_DLLEN_1                         ( BIT_(16) )
#define BIT_MDAR_APB_ADC1_DLLOOF_1(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_ADC1_DLLIN_1(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)) )

/* bits definitions for register REG_MDAR_ADC1_CTR10 */
#define BIT_MDAR_APB_ADC1_RSV_3(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_ADC1_RSV_2(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_ADC1_CTR11 */
#define BIT_MDAR_APB_ADC1_DIG_CLK_SEL_2                   ( BIT_(30) )
#define BIT_MDAR_APB_ADC1_VCM_SEL_2                       ( BIT_(29) )
#define BIT_MDAR_APB_ADC1_DELAY_CAP_2(_X_)                ( (_X_) << 27 & (BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC1_BIT_SEL_2(_X_)                  ( (_X_) << 25 & (BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_ADC1_VREF_SEL_2(_X_)                 ( (_X_) << 23 & (BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC1_VREF_BOOST_2(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_ADC1_QUANT_BOOST_2(_X_)              ( (_X_) << 19 & (BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_ADC1_DLLRD_2                         ( BIT_(18) )
#define BIT_MDAR_APB_ADC1_DLLWR_2                         ( BIT_(17) )
#define BIT_MDAR_APB_ADC1_DLLEN_2                         ( BIT_(16) )
#define BIT_MDAR_APB_ADC1_DLLOOF_2(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_ADC1_DLLIN_2(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)) )

/* bits definitions for register REG_MDAR_ADC1_CTR12 */
#define BIT_MDAR_APB_ADC1_DIG_CLK_SEL_3                   ( BIT_(30) )
#define BIT_MDAR_APB_ADC1_VCM_SEL_3                       ( BIT_(29) )
#define BIT_MDAR_APB_ADC1_DELAY_CAP_3(_X_)                ( (_X_) << 27 & (BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC1_BIT_SEL_3(_X_)                  ( (_X_) << 25 & (BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_ADC1_VREF_SEL_3(_X_)                 ( (_X_) << 23 & (BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC1_VREF_BOOST_3(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_ADC1_QUANT_BOOST_3(_X_)              ( (_X_) << 19 & (BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_ADC1_DLLRD_3                         ( BIT_(18) )
#define BIT_MDAR_APB_ADC1_DLLWR_3                         ( BIT_(17) )
#define BIT_MDAR_APB_ADC1_DLLEN_3                         ( BIT_(16) )
#define BIT_MDAR_APB_ADC1_DLLOOF_3(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_ADC1_DLLIN_3(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)) )

/* bits definitions for register REG_MDAR_ADC1_CTR20 */
#define BIT_MDAR_APB_ADC1_RSV_5(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_ADC1_RSV_4(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_ADC1_CTR21 */
#define BIT_MDAR_APB_ADC1_DIG_CLK_SEL_4                   ( BIT_(30) )
#define BIT_MDAR_APB_ADC1_VCM_SEL_4                       ( BIT_(29) )
#define BIT_MDAR_APB_ADC1_DELAY_CAP_4(_X_)                ( (_X_) << 27 & (BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC1_BIT_SEL_4(_X_)                  ( (_X_) << 25 & (BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_ADC1_VREF_SEL_4(_X_)                 ( (_X_) << 23 & (BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC1_VREF_BOOST_4(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_ADC1_QUANT_BOOST_4(_X_)              ( (_X_) << 19 & (BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_ADC1_DLLRD_4                         ( BIT_(18) )
#define BIT_MDAR_APB_ADC1_DLLWR_4                         ( BIT_(17) )
#define BIT_MDAR_APB_ADC1_DLLEN_4                         ( BIT_(16) )
#define BIT_MDAR_APB_ADC1_DLLOOF_4(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_ADC1_DLLIN_4(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)) )

/* bits definitions for register REG_MDAR_ADC1_CTR22 */
#define BIT_MDAR_APB_ADC1_DIG_CLK_SEL_5                   ( BIT_(30) )
#define BIT_MDAR_APB_ADC1_VCM_SEL_5                       ( BIT_(29) )
#define BIT_MDAR_APB_ADC1_DELAY_CAP_5(_X_)                ( (_X_) << 27 & (BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC1_BIT_SEL_5(_X_)                  ( (_X_) << 25 & (BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_ADC1_VREF_SEL_5(_X_)                 ( (_X_) << 23 & (BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC1_VREF_BOOST_5(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_ADC1_QUANT_BOOST_5(_X_)              ( (_X_) << 19 & (BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_ADC1_DLLRD_5                         ( BIT_(18) )
#define BIT_MDAR_APB_ADC1_DLLWR_5                         ( BIT_(17) )
#define BIT_MDAR_APB_ADC1_DLLEN_5                         ( BIT_(16) )
#define BIT_MDAR_APB_ADC1_DLLOOF_5(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_ADC1_DLLIN_5(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)) )

/* bits definitions for register REG_MDAR_DAC2_CTR1 */
#define BIT_MDAR_APB_DAC2_WD_OVR(_X_)                     ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_DAC2_WADDR_OVR(_X_)                  ( (_X_) << 4 & (BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)) )
#define BIT_MDAR_APB_DAC2_WLE_OVR                         ( BIT_(2) )
#define BIT_MDAR_APB_DAC2_W_OVR_I_QN                      ( BIT_(1) )
#define BIT_MDAR_APB_DAC2_W_OVR_EN                        ( BIT_(0) )

/* bits definitions for register REG_MDAR_DAC2_CTR2 */
#define BIT_MDAR_APB_DAC2_AUTO_RST                        ( BIT_(23) )
#define BIT_MDAR_APB_DAC2_SOFT_RST                        ( BIT_(22) )
#define BIT_MDAR_APB_DAC2_OSBC                            ( BIT_(21) )
#define BIT_MDAR_APB_DAC2_ISBC                            ( BIT_(20) )
#define BIT_MDAR_APB_DAC2_OVR_EN_CAL                      ( BIT_(19) )
#define BIT_MDAR_APB_DAC2_EN_OOSCAL                       ( BIT_(18) )
#define BIT_MDAR_APB_DAC2_IQSWAP                          ( BIT_(17) )
#define BIT_MDAR_APB_DAC2_CAL_START                       ( BIT_(16) )
#define BIT_MDAR_APB_DAC2_OFFSETI(_X_)                    ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )
#define BIT_MDAR_APB_DAC2_OFFSETQ(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)) )

/* bits definitions for register REG_MDAR_DAC2_CTR3 */
#define BIT_MDAR_APB_DAC2_Q_DC(_X_)                       ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)) )
#define BIT_MDAR_APB_DAC2_I_DC(_X_)                       ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)) )

/* bits definitions for register REG_MDAR_DAC2_CTR4 */
#define BIT_MDAR_APB_DAC2_I_CAL(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)) )
#define BIT_MDAR_APB_DAC2_Q_CAL(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)) )

/* bits definitions for register REG_MDAR_DAC2_STS0 */
#define BIT_MDAR_APB_DAC2_WTI(_X_)                        ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_DAC2_WTQ(_X_)                        ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_DAC2_STS1 */
#define BIT_MDAR_APB_DAC2_DA_STATE(_X_)                   ( (_X_) << 17 & (BIT_(17)|BIT_(18)) )
#define BIT_MDAR_APB_DAC2_DONE                            ( BIT_(16) )
#define BIT_MDAR_APB_DAC2_WQ_OVR(_X_)                     ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_CAL2_CTR0 */
#define BIT_MDAR_APB_ADC2_CLK_CAL_DLY(_X_)                ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)) )
#define BIT_MDAR_APB_ADA2_CAL_WAIT(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )
#define BIT_MDAR_APB_CLK_ADA2_CAL_EN                      ( BIT_(6) )
#define BIT_MDAR_APB_DAC2_PD_CAL                          ( BIT_(5) )
#define BIT_MDAR_APB_ADC2_EN_CAL                          ( BIT_(3) )
#define BIT_MDAR_APB_ADC2_CAL                             ( BIT_(1) )
#define BIT_MDAR_APB_ADA2_MODE_SEL                        ( BIT_(0) )

/* bits definitions for register REG_MDAR_CAL2_CTR1 */
#define BIT_MDAR_APB_ADC2_Q_DC(_X_)                       ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC2_I_DC(_X_)                       ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)) )

/* bits definitions for register REG_MDAR_CAL2_CTR3 */
#define BIT_MDAR_APB_ADA2_CAL_START                       ( BIT_(0) )

/* bits definitions for register REG_MDAR_CAL2_STS0 */
#define BIT_MDAR_APB_ADA2_CAL_DONE                        ( BIT_(31) )
#define BIT_MDAR_APB_ADC2_CAL_I_SUM(_X_)                  ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)) )

/* bits definitions for register REG_MDAR_CAL2_STS1 */
#define BIT_MDAR_APB_ADC2_CAL_Q_SUM(_X_)                  ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)) )

/* bits definitions for register REG_MDAR_DAC2_CTR00 */
#define BIT_MDAR_APB_DAC2_OUT_SEL_2                       ( BIT_(26) )
#define BIT_MDAR_APB_DAC2_RSV_2(_X_)                      ( (_X_) << 22 & (BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)) )
#define BIT_MDAR_APB_DAC2_PCTRL_2(_X_)                    ( (_X_) << 19 & (BIT_(19)|BIT_(20)|BIT_(21)) )
#define BIT_MDAR_APB_DAC2_CLK_SEL_2                       ( BIT_(18) )
#define BIT_MDAR_APB_DAC2_OUT_SEL_1                       ( BIT_(17) )
#define BIT_MDAR_APB_DAC2_RSV_1(_X_)                      ( (_X_) << 13 & (BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)) )
#define BIT_MDAR_APB_DAC2_PCTRL_1(_X_)                    ( (_X_) << 10 & (BIT_(10)|BIT_(11)|BIT_(12)) )
#define BIT_MDAR_APB_DAC2_CLK_SEL_1                       ( BIT_(9) )
#define BIT_MDAR_APB_DAC2_OUT_SEL_0                       ( BIT_(8) )
#define BIT_MDAR_APB_DAC2_RSV_0(_X_)                      ( (_X_) << 4 & (BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)) )
#define BIT_MDAR_APB_DAC2_PCTRL_0(_X_)                    ( (_X_) << 1 & (BIT_(1)|BIT_(2)|BIT_(3)) )
#define BIT_MDAR_APB_DAC2_CLK_SEL_0                       ( BIT_(0) )

/* bits definitions for register REG_MDAR_DAC2_CTR10 */
#define BIT_MDAR_APB_DAC2_OUT_SEL_5                       ( BIT_(26) )
#define BIT_MDAR_APB_DAC2_RSV_5(_X_)                      ( (_X_) << 22 & (BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)) )
#define BIT_MDAR_APB_DAC2_PCTRL_5(_X_)                    ( (_X_) << 19 & (BIT_(19)|BIT_(20)|BIT_(21)) )
#define BIT_MDAR_APB_DAC2_CLK_SEL_5                       ( BIT_(18) )
#define BIT_MDAR_APB_DAC2_OUT_SEL_4                       ( BIT_(17) )
#define BIT_MDAR_APB_DAC2_RSV_4(_X_)                      ( (_X_) << 13 & (BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)) )
#define BIT_MDAR_APB_DAC2_PCTRL_4(_X_)                    ( (_X_) << 10 & (BIT_(10)|BIT_(11)|BIT_(12)) )
#define BIT_MDAR_APB_DAC2_CLK_SEL_4                       ( BIT_(9) )
#define BIT_MDAR_APB_DAC2_OUT_SEL_3                       ( BIT_(8) )
#define BIT_MDAR_APB_DAC2_RSV_3(_X_)                      ( (_X_) << 4 & (BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)) )
#define BIT_MDAR_APB_DAC2_PCTRL_3(_X_)                    ( (_X_) << 1 & (BIT_(1)|BIT_(2)|BIT_(3)) )
#define BIT_MDAR_APB_DAC2_CLK_SEL_3                       ( BIT_(0) )

/* bits definitions for register REG_MDAR_ADC2_CTR0 */
#define BIT_MDAR_APB_ADC2_SOFT_RST                        ( BIT_(31) )
#define BIT_MDAR_APB_ADC2_DLL_OUT(_X_)                    ( (_X_) << 25 & (BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)) )
#define BIT_MDAR_APB_ADC2_CALRDOUT(_X_)                   ( (_X_) << 11 & (BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC2_DLL_SOFT_RST                    ( BIT_(10) )
#define BIT_MDAR_APB_ADC2_CAL_SOFT_RST                    ( BIT_(9) )
#define BIT_MDAR_APB_ADC2_CALRD                           ( BIT_(8) )
#define BIT_MDAR_APB_ADC2_CALEN                           ( BIT_(7) )
#define BIT_MDAR_APB_ADC2_CALADDR(_X_)                    ( (_X_) << 1 & (BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)) )
#define BIT_MDAR_APB_ADC2_DEBUG_EN                        ( BIT_(0) )

/* bits definitions for register REG_MDAR_ADC2_CTR00 */
#define BIT_MDAR_APB_ADC2_RSV_1(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_ADC2_RSV_0(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_ADC2_CTR01 */
#define BIT_MDAR_APB_ADC2_DIG_CLK_SEL_0                   ( BIT_(30) )
#define BIT_MDAR_APB_ADC2_VCM_SEL_0                       ( BIT_(29) )
#define BIT_MDAR_APB_ADC2_DELAY_CAP_0(_X_)                ( (_X_) << 27 & (BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC2_BIT_SEL_0(_X_)                  ( (_X_) << 25 & (BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_ADC2_VREF_SEL_0(_X_)                 ( (_X_) << 23 & (BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC2_VREF_BOOST_0(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_ADC2_QUANT_BOOST_0(_X_)              ( (_X_) << 19 & (BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_ADC2_DLLRD_0                         ( BIT_(18) )
#define BIT_MDAR_APB_ADC2_DLLWR_0                         ( BIT_(17) )
#define BIT_MDAR_APB_ADC2_DLLEN_0                         ( BIT_(16) )
#define BIT_MDAR_APB_ADC2_CSBC                            ( BIT_(15) )
#define BIT_MDAR_APB_ADC2_IQSWAP                          ( BIT_(14) )
#define BIT_MDAR_APB_ADC2_DLLOOF_0(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_ADC2_OSBC                            ( BIT_(7) )
#define BIT_MDAR_APB_ADC2_ISBC                            ( BIT_(6) )
#define BIT_MDAR_APB_ADC2_DLLIN_0(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)) )

/* bits definitions for register REG_MDAR_ADC2_CTR02 */
#define BIT_MDAR_APB_ADC2_DIG_CLK_SEL_1                   ( BIT_(30) )
#define BIT_MDAR_APB_ADC2_VCM_SEL_1                       ( BIT_(29) )
#define BIT_MDAR_APB_ADC2_DELAY_CAP_1(_X_)                ( (_X_) << 27 & (BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC2_BIT_SEL_1(_X_)                  ( (_X_) << 25 & (BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_ADC2_VREF_SEL_1(_X_)                 ( (_X_) << 23 & (BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC2_VREF_BOOST_1(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_ADC2_QUANT_BOOST_1(_X_)              ( (_X_) << 19 & (BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_ADC2_DLLRD_1                         ( BIT_(18) )
#define BIT_MDAR_APB_ADC2_DLLWR_1                         ( BIT_(17) )
#define BIT_MDAR_APB_ADC2_DLLEN_1                         ( BIT_(16) )
#define BIT_MDAR_APB_ADC2_DLLOOF_1(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_ADC2_DLLIN_1(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)) )

/* bits definitions for register REG_MDAR_ADC2_CTR10 */
#define BIT_MDAR_APB_ADC2_RSV_3(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_ADC2_RSV_2(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_ADC2_CTR11 */
#define BIT_MDAR_APB_ADC2_DIG_CLK_SEL_2                   ( BIT_(30) )
#define BIT_MDAR_APB_ADC2_VCM_SEL_2                       ( BIT_(29) )
#define BIT_MDAR_APB_ADC2_DELAY_CAP_2(_X_)                ( (_X_) << 27 & (BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC2_BIT_SEL_2(_X_)                  ( (_X_) << 25 & (BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_ADC2_VREF_SEL_2(_X_)                 ( (_X_) << 23 & (BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC2_VREF_BOOST_2(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_ADC2_QUANT_BOOST_2(_X_)              ( (_X_) << 19 & (BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_ADC2_DLLRD_2                         ( BIT_(18) )
#define BIT_MDAR_APB_ADC2_DLLWR_2                         ( BIT_(17) )
#define BIT_MDAR_APB_ADC2_DLLEN_2                         ( BIT_(16) )
#define BIT_MDAR_APB_ADC2_DLLOOF_2(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_ADC2_DLLIN_2(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)) )

/* bits definitions for register REG_MDAR_ADC2_CTR12 */
#define BIT_MDAR_APB_ADC2_DIG_CLK_SEL_3                   ( BIT_(30) )
#define BIT_MDAR_APB_ADC2_VCM_SEL_3                       ( BIT_(29) )
#define BIT_MDAR_APB_ADC2_DELAY_CAP_3(_X_)                ( (_X_) << 27 & (BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC2_BIT_SEL_3(_X_)                  ( (_X_) << 25 & (BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_ADC2_VREF_SEL_3(_X_)                 ( (_X_) << 23 & (BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC2_VREF_BOOST_3(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_ADC2_QUANT_BOOST_3(_X_)              ( (_X_) << 19 & (BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_ADC2_DLLRD_3                         ( BIT_(18) )
#define BIT_MDAR_APB_ADC2_DLLWR_3                         ( BIT_(17) )
#define BIT_MDAR_APB_ADC2_DLLEN_3                         ( BIT_(16) )
#define BIT_MDAR_APB_ADC2_DLLOOF_3(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_ADC2_DLLIN_3(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)) )

/* bits definitions for register REG_MDAR_ADC2_CTR20 */
#define BIT_MDAR_APB_ADC2_RSV_5(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_ADC2_RSV_4(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_ADC2_CTR21 */
#define BIT_MDAR_APB_ADC2_DIG_CLK_SEL_4                   ( BIT_(30) )
#define BIT_MDAR_APB_ADC2_VCM_SEL_4                       ( BIT_(29) )
#define BIT_MDAR_APB_ADC2_DELAY_CAP_4(_X_)                ( (_X_) << 27 & (BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC2_BIT_SEL_4(_X_)                  ( (_X_) << 25 & (BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_ADC2_VREF_SEL_4(_X_)                 ( (_X_) << 23 & (BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC2_VREF_BOOST_4(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_ADC2_QUANT_BOOST_4(_X_)              ( (_X_) << 19 & (BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_ADC2_DLLRD_4                         ( BIT_(18) )
#define BIT_MDAR_APB_ADC2_DLLWR_4                         ( BIT_(17) )
#define BIT_MDAR_APB_ADC2_DLLEN_4                         ( BIT_(16) )
#define BIT_MDAR_APB_ADC2_DLLOOF_4(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_ADC2_DLLIN_4(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)) )

/* bits definitions for register REG_MDAR_ADC2_CTR22 */
#define BIT_MDAR_APB_ADC2_DIG_CLK_SEL_5                   ( BIT_(30) )
#define BIT_MDAR_APB_ADC2_VCM_SEL_5                       ( BIT_(29) )
#define BIT_MDAR_APB_ADC2_DELAY_CAP_5(_X_)                ( (_X_) << 27 & (BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC2_BIT_SEL_5(_X_)                  ( (_X_) << 25 & (BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_ADC2_VREF_SEL_5(_X_)                 ( (_X_) << 23 & (BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC2_VREF_BOOST_5(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_ADC2_QUANT_BOOST_5(_X_)              ( (_X_) << 19 & (BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_ADC2_DLLRD_5                         ( BIT_(18) )
#define BIT_MDAR_APB_ADC2_DLLWR_5                         ( BIT_(17) )
#define BIT_MDAR_APB_ADC2_DLLEN_5                         ( BIT_(16) )
#define BIT_MDAR_APB_ADC2_DLLOOF_5(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_ADC2_DLLIN_5(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)) )

/* bits definitions for register REG_MDAR_DAC3_CTR1 */
#define BIT_MDAR_APB_DAC3_WD_OVR(_X_)                     ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_DAC3_WADDR_OVR(_X_)                  ( (_X_) << 4 & (BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)) )
#define BIT_MDAR_APB_DAC3_WLE_OVR                         ( BIT_(2) )
#define BIT_MDAR_APB_DAC3_W_OVR_I_QN                      ( BIT_(1) )
#define BIT_MDAR_APB_DAC3_W_OVR_EN                        ( BIT_(0) )

/* bits definitions for register REG_MDAR_DAC3_CTR2 */
#define BIT_MDAR_APB_DAC3_AUTO_RST                        ( BIT_(23) )
#define BIT_MDAR_APB_DAC3_SOFT_RST                        ( BIT_(22) )
#define BIT_MDAR_APB_DAC3_OSBC                            ( BIT_(21) )
#define BIT_MDAR_APB_DAC3_ISBC                            ( BIT_(20) )
#define BIT_MDAR_APB_DAC3_OVR_EN_CAL                      ( BIT_(19) )
#define BIT_MDAR_APB_DAC3_EN_OOSCAL                       ( BIT_(18) )
#define BIT_MDAR_APB_DAC3_IQSWAP                          ( BIT_(17) )
#define BIT_MDAR_APB_DAC3_CAL_START                       ( BIT_(16) )
#define BIT_MDAR_APB_DAC3_OFFSETI(_X_)                    ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )
#define BIT_MDAR_APB_DAC3_OFFSETQ(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)) )

/* bits definitions for register REG_MDAR_DAC3_CTR3 */
#define BIT_MDAR_APB_DAC3_Q_DC(_X_)                       ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)) )
#define BIT_MDAR_APB_DAC3_I_DC(_X_)                       ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)) )

/* bits definitions for register REG_MDAR_DAC3_CTR4 */
#define BIT_MDAR_APB_DAC3_I_CAL(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)) )
#define BIT_MDAR_APB_DAC3_Q_CAL(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)) )

/* bits definitions for register REG_MDAR_DAC3_STS0 */
#define BIT_MDAR_APB_DAC3_WTI(_X_)                        ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_DAC3_WTQ(_X_)                        ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_DAC3_STS1 */
#define BIT_MDAR_APB_DAC3_DA_STATE(_X_)                   ( (_X_) << 17 & (BIT_(17)|BIT_(18)) )
#define BIT_MDAR_APB_DAC3_DONE                            ( BIT_(16) )
#define BIT_MDAR_APB_DAC3_WQ_OVR(_X_)                     ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_CAL3_CTR0 */
#define BIT_MDAR_APB_ADC3_CLK_CAL_DLY(_X_)                ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)) )
#define BIT_MDAR_APB_ADA3_CAL_WAIT(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )
#define BIT_MDAR_APB_CLK_ADA3_CAL_EN                      ( BIT_(6) )
#define BIT_MDAR_APB_DAC3_PD_CAL                          ( BIT_(5) )
#define BIT_MDAR_APB_ADC3_EN_CAL                          ( BIT_(3) )
#define BIT_MDAR_APB_ADC3_CAL                             ( BIT_(1) )
#define BIT_MDAR_APB_ADA3_MODE_SEL                        ( BIT_(0) )

/* bits definitions for register REG_MDAR_CAL3_CTR1 */
#define BIT_MDAR_APB_ADC3_Q_DC(_X_)                       ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC3_I_DC(_X_)                       ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)) )

/* bits definitions for register REG_MDAR_CAL3_CTR3 */
#define BIT_MDAR_APB_ADA3_CAL_START                       ( BIT_(0) )

/* bits definitions for register REG_MDAR_CAL3_STS0 */
#define BIT_MDAR_APB_ADA3_CAL_DONE                        ( BIT_(31) )
#define BIT_MDAR_APB_ADC3_CAL_I_SUM(_X_)                  ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)) )

/* bits definitions for register REG_MDAR_CAL3_STS1 */
#define BIT_MDAR_APB_ADC3_CAL_Q_SUM(_X_)                  ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)) )

/* bits definitions for register REG_MDAR_DAC3_CTR00 */
#define BIT_MDAR_APB_DAC3_OUT_SEL_2                       ( BIT_(26) )
#define BIT_MDAR_APB_DAC3_RSV_2(_X_)                      ( (_X_) << 22 & (BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)) )
#define BIT_MDAR_APB_DAC3_PCTRL_2(_X_)                    ( (_X_) << 19 & (BIT_(19)|BIT_(20)|BIT_(21)) )
#define BIT_MDAR_APB_DAC3_CLK_SEL_2                       ( BIT_(18) )
#define BIT_MDAR_APB_DAC3_OUT_SEL_1                       ( BIT_(17) )
#define BIT_MDAR_APB_DAC3_RSV_1(_X_)                      ( (_X_) << 13 & (BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)) )
#define BIT_MDAR_APB_DAC3_PCTRL_1(_X_)                    ( (_X_) << 10 & (BIT_(10)|BIT_(11)|BIT_(12)) )
#define BIT_MDAR_APB_DAC3_CLK_SEL_1                       ( BIT_(9) )
#define BIT_MDAR_APB_DAC3_OUT_SEL_0                       ( BIT_(8) )
#define BIT_MDAR_APB_DAC3_RSV_0(_X_)                      ( (_X_) << 4 & (BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)) )
#define BIT_MDAR_APB_DAC3_PCTRL_0(_X_)                    ( (_X_) << 1 & (BIT_(1)|BIT_(2)|BIT_(3)) )
#define BIT_MDAR_APB_DAC3_CLK_SEL_0                       ( BIT_(0) )

/* bits definitions for register REG_MDAR_DAC3_CTR10 */
#define BIT_MDAR_APB_DAC3_OUT_SEL_5                       ( BIT_(26) )
#define BIT_MDAR_APB_DAC3_RSV_5(_X_)                      ( (_X_) << 22 & (BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)) )
#define BIT_MDAR_APB_DAC3_PCTRL_5(_X_)                    ( (_X_) << 19 & (BIT_(19)|BIT_(20)|BIT_(21)) )
#define BIT_MDAR_APB_DAC3_CLK_SEL_5                       ( BIT_(18) )
#define BIT_MDAR_APB_DAC3_OUT_SEL_4                       ( BIT_(17) )
#define BIT_MDAR_APB_DAC3_RSV_4(_X_)                      ( (_X_) << 13 & (BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)) )
#define BIT_MDAR_APB_DAC3_PCTRL_4(_X_)                    ( (_X_) << 10 & (BIT_(10)|BIT_(11)|BIT_(12)) )
#define BIT_MDAR_APB_DAC3_CLK_SEL_4                       ( BIT_(9) )
#define BIT_MDAR_APB_DAC3_OUT_SEL_3                       ( BIT_(8) )
#define BIT_MDAR_APB_DAC3_RSV_3(_X_)                      ( (_X_) << 4 & (BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)) )
#define BIT_MDAR_APB_DAC3_PCTRL_3(_X_)                    ( (_X_) << 1 & (BIT_(1)|BIT_(2)|BIT_(3)) )
#define BIT_MDAR_APB_DAC3_CLK_SEL_3                       ( BIT_(0) )

/* bits definitions for register REG_MDAR_ADC3_CTR0 */
#define BIT_MDAR_APB_ADC3_SOFT_RST                        ( BIT_(31) )
#define BIT_MDAR_APB_ADC3_DLL_OUT(_X_)                    ( (_X_) << 25 & (BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)) )
#define BIT_MDAR_APB_ADC3_CALRDOUT(_X_)                   ( (_X_) << 11 & (BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC3_DLL_SOFT_RST                    ( BIT_(10) )
#define BIT_MDAR_APB_ADC3_CAL_SOFT_RST                    ( BIT_(9) )
#define BIT_MDAR_APB_ADC3_CALRD                           ( BIT_(8) )
#define BIT_MDAR_APB_ADC3_CALEN                           ( BIT_(7) )
#define BIT_MDAR_APB_ADC3_CALADDR(_X_)                    ( (_X_) << 1 & (BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)) )
#define BIT_MDAR_APB_ADC3_DEBUG_EN                        ( BIT_(0) )

/* bits definitions for register REG_MDAR_ADC3_CTR00 */
#define BIT_MDAR_APB_ADC3_RSV_1(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_ADC3_RSV_0(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_ADC3_CTR01 */
#define BIT_MDAR_APB_ADC3_DIG_CLK_SEL_0                   ( BIT_(30) )
#define BIT_MDAR_APB_ADC3_VCM_SEL_0                       ( BIT_(29) )
#define BIT_MDAR_APB_ADC3_DELAY_CAP_0(_X_)                ( (_X_) << 27 & (BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC3_BIT_SEL_0(_X_)                  ( (_X_) << 25 & (BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_ADC3_VREF_SEL_0(_X_)                 ( (_X_) << 23 & (BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC3_VREF_BOOST_0(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_ADC3_QUANT_BOOST_0(_X_)              ( (_X_) << 19 & (BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_ADC3_DLLRD_0                         ( BIT_(18) )
#define BIT_MDAR_APB_ADC3_DLLWR_0                         ( BIT_(17) )
#define BIT_MDAR_APB_ADC3_DLLEN_0                         ( BIT_(16) )
#define BIT_MDAR_APB_ADC3_CSBC                            ( BIT_(15) )
#define BIT_MDAR_APB_ADC3_IQSWAP                          ( BIT_(14) )
#define BIT_MDAR_APB_ADC3_DLLOOF_0(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_ADC3_OSBC                            ( BIT_(7) )
#define BIT_MDAR_APB_ADC3_ISBC                            ( BIT_(6) )
#define BIT_MDAR_APB_ADC3_DLLIN_0(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)) )

/* bits definitions for register REG_MDAR_ADC3_CTR02 */
#define BIT_MDAR_APB_ADC3_DIG_CLK_SEL_1                   ( BIT_(30) )
#define BIT_MDAR_APB_ADC3_VCM_SEL_1                       ( BIT_(29) )
#define BIT_MDAR_APB_ADC3_DELAY_CAP_1(_X_)                ( (_X_) << 27 & (BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC3_BIT_SEL_1(_X_)                  ( (_X_) << 25 & (BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_ADC3_VREF_SEL_1(_X_)                 ( (_X_) << 23 & (BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC3_VREF_BOOST_1(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_ADC3_QUANT_BOOST_1(_X_)              ( (_X_) << 19 & (BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_ADC3_DLLRD_1                         ( BIT_(18) )
#define BIT_MDAR_APB_ADC3_DLLWR_1                         ( BIT_(17) )
#define BIT_MDAR_APB_ADC3_DLLEN_1                         ( BIT_(16) )
#define BIT_MDAR_APB_ADC3_DLLOOF_1(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_ADC3_DLLIN_1(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)) )

/* bits definitions for register REG_MDAR_ADC3_CTR10 */
#define BIT_MDAR_APB_ADC3_RSV_3(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_ADC3_RSV_2(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_ADC3_CTR11 */
#define BIT_MDAR_APB_ADC3_DIG_CLK_SEL_2                   ( BIT_(30) )
#define BIT_MDAR_APB_ADC3_VCM_SEL_2                       ( BIT_(29) )
#define BIT_MDAR_APB_ADC3_DELAY_CAP_2(_X_)                ( (_X_) << 27 & (BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC3_BIT_SEL_2(_X_)                  ( (_X_) << 25 & (BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_ADC3_VREF_SEL_2(_X_)                 ( (_X_) << 23 & (BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC3_VREF_BOOST_2(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_ADC3_QUANT_BOOST_2(_X_)              ( (_X_) << 19 & (BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_ADC3_DLLRD_2                         ( BIT_(18) )
#define BIT_MDAR_APB_ADC3_DLLWR_2                         ( BIT_(17) )
#define BIT_MDAR_APB_ADC3_DLLEN_2                         ( BIT_(16) )
#define BIT_MDAR_APB_ADC3_DLLOOF_2(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_ADC3_DLLIN_2(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)) )

/* bits definitions for register REG_MDAR_ADC3_CTR12 */
#define BIT_MDAR_APB_ADC3_DIG_CLK_SEL_3                   ( BIT_(30) )
#define BIT_MDAR_APB_ADC3_VCM_SEL_3                       ( BIT_(29) )
#define BIT_MDAR_APB_ADC3_DELAY_CAP_3(_X_)                ( (_X_) << 27 & (BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC3_BIT_SEL_3(_X_)                  ( (_X_) << 25 & (BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_ADC3_VREF_SEL_3(_X_)                 ( (_X_) << 23 & (BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC3_VREF_BOOST_3(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_ADC3_QUANT_BOOST_3(_X_)              ( (_X_) << 19 & (BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_ADC3_DLLRD_3                         ( BIT_(18) )
#define BIT_MDAR_APB_ADC3_DLLWR_3                         ( BIT_(17) )
#define BIT_MDAR_APB_ADC3_DLLEN_3                         ( BIT_(16) )
#define BIT_MDAR_APB_ADC3_DLLOOF_3(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_ADC3_DLLIN_3(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)) )

/* bits definitions for register REG_MDAR_ADC3_CTR20 */
#define BIT_MDAR_APB_ADC3_RSV_5(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_ADC3_RSV_4(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_ADC3_CTR21 */
#define BIT_MDAR_APB_ADC3_DIG_CLK_SEL_4                   ( BIT_(30) )
#define BIT_MDAR_APB_ADC3_VCM_SEL_4                       ( BIT_(29) )
#define BIT_MDAR_APB_ADC3_DELAY_CAP_4(_X_)                ( (_X_) << 27 & (BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC3_BIT_SEL_4(_X_)                  ( (_X_) << 25 & (BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_ADC3_VREF_SEL_4(_X_)                 ( (_X_) << 23 & (BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC3_VREF_BOOST_4(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_ADC3_QUANT_BOOST_4(_X_)              ( (_X_) << 19 & (BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_ADC3_DLLRD_4                         ( BIT_(18) )
#define BIT_MDAR_APB_ADC3_DLLWR_4                         ( BIT_(17) )
#define BIT_MDAR_APB_ADC3_DLLEN_4                         ( BIT_(16) )
#define BIT_MDAR_APB_ADC3_DLLOOF_4(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_ADC3_DLLIN_4(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)) )

/* bits definitions for register REG_MDAR_ADC3_CTR22 */
#define BIT_MDAR_APB_ADC3_DIG_CLK_SEL_5                   ( BIT_(30) )
#define BIT_MDAR_APB_ADC3_VCM_SEL_5                       ( BIT_(29) )
#define BIT_MDAR_APB_ADC3_DELAY_CAP_5(_X_)                ( (_X_) << 27 & (BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_ADC3_BIT_SEL_5(_X_)                  ( (_X_) << 25 & (BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_ADC3_VREF_SEL_5(_X_)                 ( (_X_) << 23 & (BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_ADC3_VREF_BOOST_5(_X_)               ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_ADC3_QUANT_BOOST_5(_X_)              ( (_X_) << 19 & (BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_ADC3_DLLRD_5                         ( BIT_(18) )
#define BIT_MDAR_APB_ADC3_DLLWR_5                         ( BIT_(17) )
#define BIT_MDAR_APB_ADC3_DLLEN_5                         ( BIT_(16) )
#define BIT_MDAR_APB_ADC3_DLLOOF_5(_X_)                   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_ADC3_DLLIN_5(_X_)                    ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)) )

/* bits definitions for register REG_MDAR_AFCDAC1_CFG */
#define BIT_MDAR_APB_AFCDAC1_CHANNEL_MASK(_X_)            ( (_X_) << 28 & (BIT_(28)|BIT_(29)|BIT_(30)) )
#define BIT_MDAR_APB_AFCDAC1_CHANNEL_SSET(_X_)            ( (_X_) << 24 & (BIT_(24)|BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_AFCDAC1_LOW_V_CON_SST                ( BIT_(23) )
#define BIT_MDAR_APB_AFCDAC1_BP_RES_SST                   ( BIT_(20) )
#define BIT_MDAR_APB_AFCDAC1_G_SST(_X_)                   ( (_X_) << 18 & (BIT_(18)|BIT_(19)) )
#define BIT_MDAR_APB_AFCDAC1_CTL_SST(_X_)                 ( (_X_) << 16 & (BIT_(16)|BIT_(17)) )
#define BIT_MDAR_APB_AFCDAC1_PD_SST                       ( BIT_(15) )
#define BIT_MDAR_APB_AFCDAC1_D_SST(_X_)                   ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )

/* bits definitions for register REG_MDAR_AFCDAC2_CFG */
#define BIT_MDAR_APB_AFCDAC2_CHANNEL_MASK(_X_)            ( (_X_) << 28 & (BIT_(28)|BIT_(29)|BIT_(30)) )
#define BIT_MDAR_APB_AFCDAC2_CHANNEL_SSET(_X_)            ( (_X_) << 24 & (BIT_(24)|BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_AFCDAC2_LOW_V_CON_SST                ( BIT_(23) )
#define BIT_MDAR_APB_AFCDAC2_BP_RES_SST                   ( BIT_(20) )
#define BIT_MDAR_APB_AFCDAC2_G_SST(_X_)                   ( (_X_) << 18 & (BIT_(18)|BIT_(19)) )
#define BIT_MDAR_APB_AFCDAC2_CTL_SST(_X_)                 ( (_X_) << 16 & (BIT_(16)|BIT_(17)) )
#define BIT_MDAR_APB_AFCDAC2_PD_SST                       ( BIT_(15) )
#define BIT_MDAR_APB_AFCDAC2_D_SST(_X_)                   ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )

/* bits definitions for register REG_MDAR_APCDAC1_CFG */
#define BIT_MDAR_APB_APCDAC1_CHANNEL_MASK(_X_)            ( (_X_) << 28 & (BIT_(28)|BIT_(29)|BIT_(30)) )
#define BIT_MDAR_APB_APCDAC1_CHANNEL_SSET(_X_)            ( (_X_) << 24 & (BIT_(24)|BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_APCDAC1_LOW_V_CON_SST                ( BIT_(23) )
#define BIT_MDAR_APB_APCDAC1_OUTSEL_SST(_X_)              ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_APCDAC1_BP_RES_SST                   ( BIT_(20) )
#define BIT_MDAR_APB_APCDAC1_G_SST(_X_)                   ( (_X_) << 18 & (BIT_(18)|BIT_(19)) )
#define BIT_MDAR_APB_APCDAC1_CTL_SST(_X_)                 ( (_X_) << 16 & (BIT_(16)|BIT_(17)) )
#define BIT_MDAR_APB_APCDAC1_PD_SST                       ( BIT_(15) )
#define BIT_MDAR_APB_APCDAC1_SEL_SST                      ( BIT_(14) )
#define BIT_MDAR_APB_APCDAC1_D_SST(_X_)                   ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )

/* bits definitions for register REG_MDAR_APCDAC2_CFG */
#define BIT_MDAR_APB_APCDAC2_CHANNEL_MASK(_X_)            ( (_X_) << 28 & (BIT_(28)|BIT_(29)|BIT_(30)) )
#define BIT_MDAR_APB_APCDAC2_CHANNEL_SSET(_X_)            ( (_X_) << 24 & (BIT_(24)|BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_APCDAC2_LOW_V_CON_SST                ( BIT_(23) )
#define BIT_MDAR_APB_APCDAC2_OUTSEL_SST(_X_)              ( (_X_) << 21 & (BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_APCDAC2_BP_RES_SST                   ( BIT_(20) )
#define BIT_MDAR_APB_APCDAC2_G_SST(_X_)                   ( (_X_) << 18 & (BIT_(18)|BIT_(19)) )
#define BIT_MDAR_APB_APCDAC2_CTL_SST(_X_)                 ( (_X_) << 16 & (BIT_(16)|BIT_(17)) )
#define BIT_MDAR_APB_APCDAC2_PD_SST                       ( BIT_(15) )
#define BIT_MDAR_APB_APCDAC2_SEL_SST                      ( BIT_(14) )
#define BIT_MDAR_APB_APCDAC2_D_SST(_X_)                   ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )

/* bits definitions for register REG_MDAR_RFSPI_CFG */
#define BIT_MDAR_APB_RFSBI2_CHANNEL_MASK(_X_)             ( (_X_) << 29 & (BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_RFSBI2_CHANNEL_SSET(_X_)             ( (_X_) << 26 & (BIT_(26)|BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_RFSBI2_IDATA_SST                     ( BIT_(25) )
#define BIT_MDAR_APB_RFSBI2_ODATA_SST                     ( BIT_(24) )
#define BIT_MDAR_APB_RFSBI2_DATA_OE_SST                   ( BIT_(23) )
#define BIT_MDAR_APB_RFSBI2_DATA_IE_SST                   ( BIT_(22) )
#define BIT_MDAR_APB_RFSBI2_CLK_SST                       ( BIT_(21) )
#define BIT_MDAR_APB_RFSBI2_CLK_OE_SST                    ( BIT_(20) )
#define BIT_MDAR_APB_RFSBI2_EN0_SST                       ( BIT_(19) )
#define BIT_MDAR_APB_RFSBI2_EN0_OE_SST                    ( BIT_(18) )
#define BIT_MDAR_APB_RFSBI2_EN1_SST                       ( BIT_(17) )
#define BIT_MDAR_APB_RFSBI2_EN1_OE_SST                    ( BIT_(16) )
#define BIT_MDAR_APB_RFSBI1_CHANNEL_MASK(_X_)             ( (_X_) << 13 & (BIT_(13)|BIT_(14)|BIT_(15)) )
#define BIT_MDAR_APB_RFSBI1_CHANNEL_SSET(_X_)             ( (_X_) << 10 & (BIT_(10)|BIT_(11)|BIT_(12)) )
#define BIT_MDAR_APB_RFSBI1_IDATA_SST                     ( BIT_(9) )
#define BIT_MDAR_APB_RFSBI1_ODATA_SST                     ( BIT_(8) )
#define BIT_MDAR_APB_RFSBI1_DATA_OE_SST                   ( BIT_(7) )
#define BIT_MDAR_APB_RFSBI1_DATA_IE_SST                   ( BIT_(6) )
#define BIT_MDAR_APB_RFSBI1_CLK_SST                       ( BIT_(5) )
#define BIT_MDAR_APB_RFSBI1_CLK_OE_SST                    ( BIT_(4) )
#define BIT_MDAR_APB_RFSBI1_EN0_SST                       ( BIT_(3) )
#define BIT_MDAR_APB_RFSBI1_EN0_OE_SST                    ( BIT_(2) )
#define BIT_MDAR_APB_RFSBI1_EN1_SST                       ( BIT_(1) )
#define BIT_MDAR_APB_RFSBI1_EN1_OE_SST                    ( BIT_(0) )

/* bits definitions for register REG_MDAR_RFMIPI_CFG */
#define BIT_MDAR_APB_RFMIPI2_CHANNEL_MASK(_X_)            ( (_X_) << 28 & (BIT_(28)|BIT_(29)|BIT_(30)) )
#define BIT_MDAR_APB_RFMIPI2_CHANNEL_SSET(_X_)            ( (_X_) << 24 & (BIT_(24)|BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_PAD_OUT_RFFE2_CLK_SST                ( BIT_(20) )
#define BIT_MDAR_APB_PAD_OUT_RFFE2_DATA_SST               ( BIT_(19) )
#define BIT_MDAR_APB_PAD_IN_RFFE2_DATA_SST                ( BIT_(18) )
#define BIT_MDAR_APB_PAD_OE_RFFE2_DATA_SST                ( BIT_(17) )
#define BIT_MDAR_APB_PAD_IE_RFFE2_DATA_SST                ( BIT_(16) )
#define BIT_MDAR_APB_RFMIPI1_CHANNEL_MASK(_X_)            ( (_X_) << 12 & (BIT_(12)|BIT_(13)|BIT_(14)) )
#define BIT_MDAR_APB_RFMIPI1_CHANNEL_SSET(_X_)            ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)) )
#define BIT_MDAR_APB_PAD_OUT_RFFE1_CLK_SST                ( BIT_(4) )
#define BIT_MDAR_APB_PAD_OUT_RFFE1_DATA_SST               ( BIT_(3) )
#define BIT_MDAR_APB_PAD_IN_RFFE1_DATA_SST                ( BIT_(2) )
#define BIT_MDAR_APB_PAD_OE_RFFE1_DATA_SST                ( BIT_(1) )
#define BIT_MDAR_APB_PAD_IE_RFFE1_DATA_SST                ( BIT_(0) )

/* bits definitions for register REG_MDAR_APCDAC_OUTSEL */
#define BIT_MDAR_APB_AFCDAC_LOW_V_CON_GGE                 ( BIT_(31) )
#define BIT_MDAR_APB_AFCDAC_LOW_V_CON_WG                  ( BIT_(30) )
#define BIT_MDAR_APB_AFCDAC_LOW_V_CON_WD                  ( BIT_(29) )
#define BIT_MDAR_APB_AFCDAC_LOW_V_CON_TG                  ( BIT_(28) )
#define BIT_MDAR_APB_AFCDAC_LOW_V_CON_TD                  ( BIT_(27) )
#define BIT_MDAR_APB_AFCDAC_LOW_V_CON_LTE                 ( BIT_(26) )
#define BIT_MDAR_APB_APCDACX_G3_SST(_X_)                  ( (_X_) << 24 & (BIT_(24)|BIT_(25)) )
#define BIT_MDAR_APB_APCDACX_G2_SST(_X_)                  ( (_X_) << 22 & (BIT_(22)|BIT_(23)) )
#define BIT_MDAR_APB_APCDACX_G1_SST(_X_)                  ( (_X_) << 20 & (BIT_(20)|BIT_(21)) )
#define BIT_MDAR_APB_APCDACX_G0_SST(_X_)                  ( (_X_) << 18 & (BIT_(18)|BIT_(19)) )
#define BIT_MDAR_APB_APCDAC_LOW_V_CON_GGE                 ( BIT_(17) )
#define BIT_MDAR_APB_APCDAC_LOW_V_CON_WG                  ( BIT_(16) )
#define BIT_MDAR_APB_APCDAC_LOW_V_CON_WD                  ( BIT_(15) )
#define BIT_MDAR_APB_APCDAC_LOW_V_CON_TG                  ( BIT_(14) )
#define BIT_MDAR_APB_APCDAC_LOW_V_CON_TD                  ( BIT_(13) )
#define BIT_MDAR_APB_APCDAC_LOW_V_CON_LTE                 ( BIT_(12) )
#define BIT_MDAR_APB_APCDAC_OUTSEL_GGE(_X_)               ( (_X_) << 10 & (BIT_(10)|BIT_(11)) )
#define BIT_MDAR_APB_APCDAC_OUTSEL_WG(_X_)                ( (_X_) << 8 & (BIT_(8)|BIT_(9)) )
#define BIT_MDAR_APB_APCDAC_OUTSEL_WD(_X_)                ( (_X_) << 6 & (BIT_(6)|BIT_(7)) )
#define BIT_MDAR_APB_APCDAC_OUTSEL_TG(_X_)                ( (_X_) << 4 & (BIT_(4)|BIT_(5)) )
#define BIT_MDAR_APB_APCDAC_OUTSEL_TD(_X_)                ( (_X_) << 2 & (BIT_(2)|BIT_(3)) )
#define BIT_MDAR_APB_APCDAC_OUTSEL_LTE(_X_)               ( (_X_) & (BIT_(0)|BIT_(1)) )

/* bits definitions for register REG_MDAR_CLASH_CHK */
#define BIT_MDAR_APB_RFSBI2_CLASH_CHK_INTRP_EN            ( BIT_(29) )
#define BIT_MDAR_APB_RFSBI1_CLASH_CHK_INTRP_EN            ( BIT_(28) )
#define BIT_MDAR_APB_RFMIPI2_CLASH_CHK_INTRP_EN           ( BIT_(27) )
#define BIT_MDAR_APB_RFMIPI1_CLASH_CHK_INTRP_EN           ( BIT_(26) )
#define BIT_MDAR_APB_APCDAC2_CLASH_CHK_INTRP_EN           ( BIT_(25) )
#define BIT_MDAR_APB_APCDAC1_CLASH_CHK_INTRP_EN           ( BIT_(24) )
#define BIT_MDAR_APB_AFCDAC2_CLASH_CHK_INTRP_EN           ( BIT_(23) )
#define BIT_MDAR_APB_AFCDAC1_CLASH_CHK_INTRP_EN           ( BIT_(22) )
#define BIT_MDAR_APB_ADA3_TX_CLASH_CHK_INTRP_EN           ( BIT_(21) )
#define BIT_MDAR_APB_ADA3_RX_CLASH_CHK_INTRP_EN           ( BIT_(20) )
#define BIT_MDAR_APB_ADA2_TX_CLASH_CHK_INTRP_EN           ( BIT_(19) )
#define BIT_MDAR_APB_ADA2_RX_CLASH_CHK_INTRP_EN           ( BIT_(18) )
#define BIT_MDAR_APB_ADA1_TX_CLASH_CHK_INTRP_EN           ( BIT_(17) )
#define BIT_MDAR_APB_ADA1_RX_CLASH_CHK_INTRP_EN           ( BIT_(16) )
#define BIT_MDAR_APB_CHK_CLASH_STFREE                     ( BIT_(8) )
#define BIT_MDAR_APB_CHK_CLASH_CLR                        ( BIT_(7) )
#define BIT_MDAR_APB_CHK_CLASH_RTC_SNAP_MODE              ( BIT_(4) )
#define BIT_MDAR_APB_CHK_CLASH_RTC_SNAP_EDGE              ( BIT_(3) )
#define BIT_MDAR_APB_CHK_CLASH_RTC_SNAP_INTRP_TYPE        ( BIT_(2) )
#define BIT_MDAR_APB_CHK_CLASH_RTC_SNAP_INTRP_CLR         ( BIT_(1) )
#define BIT_MDAR_APB_CHK_CLASH_RTC_SNAP_INTRP             ( BIT_(0) )

/* bits definitions for register REG_MDAR_CLASH_SNAP */
#define BIT_MDAR_APB_CHK_CLASH_RTC_SNAP_TIME(_X_)         (_X_)

/* bits definitions for register REG_MDAR_CLASH_STATUS1 */
#define BIT_MDAR_APB_CHK_CLASH_ADA3_TX_CHANNEL_SEL(_X_)   ( (_X_) << 25 & (BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_CHK_CLASH_ADA3_RX_CHANNEL_SEL(_X_)   ( (_X_) << 20 & (BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)) )
#define BIT_MDAR_APB_CHK_CLASH_ADA2_TX_CHANNEL_SEL(_X_)   ( (_X_) << 15 & (BIT_(15)|BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)) )
#define BIT_MDAR_APB_CHK_CLASH_ADA2_RX_CHANNEL_SEL(_X_)   ( (_X_) << 10 & (BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)) )
#define BIT_MDAR_APB_CHK_CLASH_ADA1_TX_CHANNEL_SEL(_X_)   ( (_X_) << 5 & (BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)) )
#define BIT_MDAR_APB_CHK_CLASH_ADA1_RX_CHANNEL_SEL(_X_)   ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)) )

/* bits definitions for register REG_MDAR_CLASH_STATUS2 */
#define BIT_MDAR_APB_CHK_CLASH_APCDAC2_CHANNEL_SEL(_X_)   ( (_X_) << 11 & (BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_CHK_CLASH_APCDAC1_CHANNEL_SEL(_X_)   ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)) )
#define BIT_MDAR_APB_CHK_CLASH_AFCDAC2_CHANNEL_SEL(_X_)   ( (_X_) << 3 & (BIT_(3)|BIT_(4)|BIT_(5)) )
#define BIT_MDAR_APB_CHK_CLASH_AFCDAC1_CHANNEL_SEL(_X_)   ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)) )

/* bits definitions for register REG_MDAR_CLASH_STATUS3 */
#define BIT_MDAR_APB_CHK_CLASH_RFSBI2_CHANNEL_SEL(_X_)    ( (_X_) << 11 & (BIT_(11)|BIT_(12)|BIT_(13)) )
#define BIT_MDAR_APB_CHK_CLASH_RFSBI1_CHANNEL_SEL(_X_)    ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)) )
#define BIT_MDAR_APB_CHK_CLASH_RFMIPI2_CHANNEL_SEL(_X_)   ( (_X_) << 3 & (BIT_(3)|BIT_(4)|BIT_(5)) )
#define BIT_MDAR_APB_CHK_CLASH_RFMIPI1_CHANNEL_SEL(_X_)   ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)) )

/* bits definitions for register REG_MDAR_EXTRA_CFG0 */
#define BIT_MDAR_APB_APT_DCM2_EXTRA_CFG(_X_)              ( (_X_) << 24 & (BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_APT_DCM2_ADI_EN                      ( BIT_(23) )
#define BIT_MDAR_APB_APT_DCM2_CHANNEL_SSET(_X_)           ( (_X_) << 20 & (BIT_(20)|BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_APT_DCM2_SST                         ( BIT_(19) )
#define BIT_MDAR_APB_APT_DCM2_CHANNEL_MASK(_X_)           ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)) )
#define BIT_MDAR_APB_APT_DCM1_EXTRA_CFG(_X_)              ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )
#define BIT_MDAR_APB_APT_DCM1_ADI_EN                      ( BIT_(7) )
#define BIT_MDAR_APB_APT_DCM1_CHANNEL_SSET(_X_)           ( (_X_) << 4 & (BIT_(4)|BIT_(5)|BIT_(6)) )
#define BIT_MDAR_APB_APT_DCM1_SST                         ( BIT_(3) )
#define BIT_MDAR_APB_APT_DCM1_CHANNEL_MASK(_X_)           ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)) )

/* bits definitions for register REG_MDAR_EXTRA_CFG1 */
#define BIT_MDAR_APB_MDAR_EXTRA_CFG1(_X_)                 ( (_X_) << 10 & (BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_MDAR_BB_LDO_REFCTRL(_X_)             ( (_X_) << 8 & (BIT_(8)|BIT_(9)) )
#define BIT_MDAR_APB_MDAR_BB_LDO_SLEEP_PD_EN              ( BIT_(6) )
#define BIT_MDAR_APB_MDAR_BB_LDO_FORCE_ON                 ( BIT_(5) )
#define BIT_MDAR_APB_MDAR_BB_LDO_FORCE_PD                 ( BIT_(4) )
#define BIT_MDAR_APB_MDAR_BB_BG_SLEEP_PD_EN               ( BIT_(2) )
#define BIT_MDAR_APB_MDAR_BB_BG_FORCE_ON                  ( BIT_(1) )
#define BIT_MDAR_APB_MDAR_BB_BG_FORCE_PD                  ( BIT_(0) )

/* bits definitions for register REG_MDAR_RFCTRL15_INF0 */
#define BIT_MDAR_APB_CHK_CLASH_RFCTRL15_CHX_SEL(_X_)      ( (_X_) << 20 & (BIT_(20)|BIT_(21)|BIT_(22)) )
#define BIT_MDAR_APB_RFCTRL15_CHK_INTRP_EN                ( BIT_(16) )
#define BIT_MDAR_APB_RFCTRL15_RTC_REFRESH                 ( BIT_(12) )
#define BIT_MDAR_APB_RFCTRL15_SNAP_REFRESH                ( BIT_(8) )
#define BIT_MDAR_APB_RFCTRL15_SSET(_X_)                   ( (_X_) << 4 & (BIT_(4)|BIT_(5)|BIT_(6)) )
#define BIT_MDAR_APB_RFCTRL15_MASK(_X_)                   ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)) )

/* bits definitions for register REG_MDAR_RFCTRL15_INF1 */
#define BIT_MDAR_APB_RFCTRL15_CH0_SNAP1_RTC_TIME(_X_)     (_X_)

/* bits definitions for register REG_MDAR_RFCTRL15_INF2 */
#define BIT_MDAR_APB_RFCTRL15_CH0_SNAP0_RTC_TIME(_X_)     (_X_)

/* bits definitions for register REG_MDAR_RFCTRL15_INF3 */
#define BIT_MDAR_APB_RFCTRL15_CH1_SNAP1_RTC_TIME(_X_)     (_X_)

/* bits definitions for register REG_MDAR_RFCTRL15_INF4 */
#define BIT_MDAR_APB_RFCTRL15_CH1_SNAP0_RTC_TIME(_X_)     (_X_)

/* bits definitions for register REG_MDAR_RFCTRL15_INF5 */
#define BIT_MDAR_APB_RFCTRL15_CH2_SNAP1_RTC_TIME(_X_)     (_X_)

/* bits definitions for register REG_MDAR_RFCTRL15_INF6 */
#define BIT_MDAR_APB_RFCTRL15_CH2_SNAP0_RTC_TIME(_X_)     (_X_)

/* bits definitions for register REG_MDAR_CFG4 */
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK3(_X_)            ( (_X_) << 27 & (BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK2(_X_)            ( (_X_) << 24 & (BIT_(24)|BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK1(_X_)            ( (_X_) << 21 & (BIT_(21)|BIT_(22)|BIT_(23)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK0(_X_)            ( (_X_) << 18 & (BIT_(18)|BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_RFCTRL150_SST(_X_)                   ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_CFG5 */
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK13(_X_)           ( (_X_) << 27 & (BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK12(_X_)           ( (_X_) << 24 & (BIT_(24)|BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK11(_X_)           ( (_X_) << 21 & (BIT_(21)|BIT_(22)|BIT_(23)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK10(_X_)           ( (_X_) << 18 & (BIT_(18)|BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK9(_X_)            ( (_X_) << 15 & (BIT_(15)|BIT_(16)|BIT_(17)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK8(_X_)            ( (_X_) << 12 & (BIT_(12)|BIT_(13)|BIT_(14)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK7(_X_)            ( (_X_) << 9 & (BIT_(9)|BIT_(10)|BIT_(11)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK6(_X_)            ( (_X_) << 6 & (BIT_(6)|BIT_(7)|BIT_(8)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK5(_X_)            ( (_X_) << 3 & (BIT_(3)|BIT_(4)|BIT_(5)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK4(_X_)            ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)) )

/* bits definitions for register REG_MDAR_CFG6 */
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET7(_X_)            ( (_X_) << 27 & (BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET6(_X_)            ( (_X_) << 24 & (BIT_(24)|BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET5(_X_)            ( (_X_) << 21 & (BIT_(21)|BIT_(22)|BIT_(23)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET4(_X_)            ( (_X_) << 18 & (BIT_(18)|BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET3(_X_)            ( (_X_) << 15 & (BIT_(15)|BIT_(16)|BIT_(17)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET2(_X_)            ( (_X_) << 12 & (BIT_(12)|BIT_(13)|BIT_(14)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET1(_X_)            ( (_X_) << 9 & (BIT_(9)|BIT_(10)|BIT_(11)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET0(_X_)            ( (_X_) << 6 & (BIT_(6)|BIT_(7)|BIT_(8)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK15(_X_)           ( (_X_) << 3 & (BIT_(3)|BIT_(4)|BIT_(5)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK14(_X_)           ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)) )

/* bits definitions for register REG_MDAR_CFG7 */
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET15(_X_)           ( (_X_) << 21 & (BIT_(21)|BIT_(22)|BIT_(23)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET14(_X_)           ( (_X_) << 18 & (BIT_(18)|BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET13(_X_)           ( (_X_) << 15 & (BIT_(15)|BIT_(16)|BIT_(17)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET12(_X_)           ( (_X_) << 12 & (BIT_(12)|BIT_(13)|BIT_(14)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET11(_X_)           ( (_X_) << 9 & (BIT_(9)|BIT_(10)|BIT_(11)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET10(_X_)           ( (_X_) << 6 & (BIT_(6)|BIT_(7)|BIT_(8)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET9(_X_)            ( (_X_) << 3 & (BIT_(3)|BIT_(4)|BIT_(5)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET8(_X_)            ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)) )

/* bits definitions for register REG_MDAR_CFG8 */
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK19(_X_)           ( (_X_) << 27 & (BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK18(_X_)           ( (_X_) << 24 & (BIT_(24)|BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK17(_X_)           ( (_X_) << 21 & (BIT_(21)|BIT_(22)|BIT_(23)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK16(_X_)           ( (_X_) << 18 & (BIT_(18)|BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_RFCTRL3130_SST(_X_)                  ( (_X_) << 14 & (BIT_(14)|BIT_(15)) )
#define BIT_MDAR_APB_RFCTRL2916_SST(_X_)                  ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )

/* bits definitions for register REG_MDAR_CFG9 */
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK29(_X_)           ( (_X_) << 27 & (BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK28(_X_)           ( (_X_) << 24 & (BIT_(24)|BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK27(_X_)           ( (_X_) << 21 & (BIT_(21)|BIT_(22)|BIT_(23)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK26(_X_)           ( (_X_) << 18 & (BIT_(18)|BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK25(_X_)           ( (_X_) << 15 & (BIT_(15)|BIT_(16)|BIT_(17)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK24(_X_)           ( (_X_) << 12 & (BIT_(12)|BIT_(13)|BIT_(14)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK23(_X_)           ( (_X_) << 9 & (BIT_(9)|BIT_(10)|BIT_(11)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK22(_X_)           ( (_X_) << 6 & (BIT_(6)|BIT_(7)|BIT_(8)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK21(_X_)           ( (_X_) << 3 & (BIT_(3)|BIT_(4)|BIT_(5)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK20(_X_)           ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)) )

/* bits definitions for register REG_MDAR_CFG10 */
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET23(_X_)           ( (_X_) << 27 & (BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET22(_X_)           ( (_X_) << 24 & (BIT_(24)|BIT_(25)|BIT_(26)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET21(_X_)           ( (_X_) << 21 & (BIT_(21)|BIT_(22)|BIT_(23)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET20(_X_)           ( (_X_) << 18 & (BIT_(18)|BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET19(_X_)           ( (_X_) << 15 & (BIT_(15)|BIT_(16)|BIT_(17)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET18(_X_)           ( (_X_) << 12 & (BIT_(12)|BIT_(13)|BIT_(14)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET17(_X_)           ( (_X_) << 9 & (BIT_(9)|BIT_(10)|BIT_(11)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET16(_X_)           ( (_X_) << 6 & (BIT_(6)|BIT_(7)|BIT_(8)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK31(_X_)           ( (_X_) << 3 & (BIT_(3)|BIT_(4)|BIT_(5)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_MASK30(_X_)           ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)) )

/* bits definitions for register REG_MDAR_CFG11 */
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET31(_X_)           ( (_X_) << 21 & (BIT_(21)|BIT_(22)|BIT_(23)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET30(_X_)           ( (_X_) << 18 & (BIT_(18)|BIT_(19)|BIT_(20)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET29(_X_)           ( (_X_) << 15 & (BIT_(15)|BIT_(16)|BIT_(17)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET28(_X_)           ( (_X_) << 12 & (BIT_(12)|BIT_(13)|BIT_(14)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET27(_X_)           ( (_X_) << 9 & (BIT_(9)|BIT_(10)|BIT_(11)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET26(_X_)           ( (_X_) << 6 & (BIT_(6)|BIT_(7)|BIT_(8)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET25(_X_)           ( (_X_) << 3 & (BIT_(3)|BIT_(4)|BIT_(5)) )
#define BIT_MDAR_APB_RFCTRL_CHANNEL_SSET24(_X_)           ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)) )

/* bits definitions for register REG_MDAR_CFG12 */
#define BIT_MDAR_APB_RFCTRL_WTGCFGH(_X_)                  ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)) )
#define BIT_MDAR_APB_RFCTRL_WTGCFGL(_X_)                  ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)) )

/* bits definitions for register REG_MDAR_CFG13 */
#define BIT_MDAR_APB_RFCTRL_GGECFGH(_X_)                  ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)) )
#define BIT_MDAR_APB_RFCTRL_GGECFGL(_X_)                  ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)) )

/* bits definitions for register REG_MDAR_CFG14 */
#define BIT_MDAR_APB_MDAR_CFG14(_X_)                      (_X_)

/* bits definitions for register REG_MDAR_CFG15 */
#define BIT_MDAR_APB_MDAR_ANALOG_BB_RSV(_X_)              ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)) )

/* bits definitions for register REG_MDAR_IMB_CFG10 */
#define BIT_MDAR_APB_ADC1_IMBP_CLK_SEL_5                  ( BIT_(21) )
#define BIT_MDAR_APB_ADC1_IMBP_CLK_SEL_4                  ( BIT_(20) )
#define BIT_MDAR_APB_ADC1_IMBP_CLK_SEL_3                  ( BIT_(19) )
#define BIT_MDAR_APB_ADC1_IMBP_CLK_SEL_2                  ( BIT_(18) )
#define BIT_MDAR_APB_ADC1_IMBP_CLK_SEL_1                  ( BIT_(17) )
#define BIT_MDAR_APB_ADC1_IMBP_CLK_SEL_0                  ( BIT_(16) )
#define BIT_MDAR_APB_DAC1_IMBP_BYPASS_5                   ( BIT_(13) )
#define BIT_MDAR_APB_DAC1_IMBP_BYPASS_4                   ( BIT_(12) )
#define BIT_MDAR_APB_DAC1_IMBP_BYPASS_3                   ( BIT_(11) )
#define BIT_MDAR_APB_DAC1_IMBP_BYPASS_2                   ( BIT_(10) )
#define BIT_MDAR_APB_DAC1_IMBP_BYPASS_1                   ( BIT_(9) )
#define BIT_MDAR_APB_DAC1_IMBP_BYPASS_0                   ( BIT_(8) )
#define BIT_MDAR_APB_ADC1_IMBP_BYPASS_5                   ( BIT_(5) )
#define BIT_MDAR_APB_ADC1_IMBP_BYPASS_4                   ( BIT_(4) )
#define BIT_MDAR_APB_ADC1_IMBP_BYPASS_3                   ( BIT_(3) )
#define BIT_MDAR_APB_ADC1_IMBP_BYPASS_2                   ( BIT_(2) )
#define BIT_MDAR_APB_ADC1_IMBP_BYPASS_1                   ( BIT_(1) )
#define BIT_MDAR_APB_ADC1_IMBP_BYPASS_0                   ( BIT_(0) )

/* bits definitions for register REG_MDAR_IMB_CFG11 */
#define BIT_MDAR_APB_ADC1_BAL_B(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_ADC1_BAL_A(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )

/* bits definitions for register REG_MDAR_IMB_CFG12 */
#define BIT_MDAR_APB_ADC1_BAL_D(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_ADC1_BAL_C(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )

/* bits definitions for register REG_MDAR_IMB_CFG13 */
#define BIT_MDAR_APB_DAC1_BAL_B(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_DAC1_BAL_A(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )

/* bits definitions for register REG_MDAR_IMB_CFG14 */
#define BIT_MDAR_APB_DAC1_BAL_D(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_DAC1_BAL_C(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )

/* bits definitions for register REG_MDAR_IMB_CFG20 */
#define BIT_MDAR_APB_ADC2_IMBP_CLK_SEL_5                  ( BIT_(21) )
#define BIT_MDAR_APB_ADC2_IMBP_CLK_SEL_4                  ( BIT_(20) )
#define BIT_MDAR_APB_ADC2_IMBP_CLK_SEL_3                  ( BIT_(19) )
#define BIT_MDAR_APB_ADC2_IMBP_CLK_SEL_2                  ( BIT_(18) )
#define BIT_MDAR_APB_ADC2_IMBP_CLK_SEL_1                  ( BIT_(17) )
#define BIT_MDAR_APB_ADC2_IMBP_CLK_SEL_0                  ( BIT_(16) )
#define BIT_MDAR_APB_DAC2_IMBP_BYPASS_5                   ( BIT_(13) )
#define BIT_MDAR_APB_DAC2_IMBP_BYPASS_4                   ( BIT_(12) )
#define BIT_MDAR_APB_DAC2_IMBP_BYPASS_3                   ( BIT_(11) )
#define BIT_MDAR_APB_DAC2_IMBP_BYPASS_2                   ( BIT_(10) )
#define BIT_MDAR_APB_DAC2_IMBP_BYPASS_1                   ( BIT_(9) )
#define BIT_MDAR_APB_DAC2_IMBP_BYPASS_0                   ( BIT_(8) )
#define BIT_MDAR_APB_ADC2_IMBP_BYPASS_5                   ( BIT_(5) )
#define BIT_MDAR_APB_ADC2_IMBP_BYPASS_4                   ( BIT_(4) )
#define BIT_MDAR_APB_ADC2_IMBP_BYPASS_3                   ( BIT_(3) )
#define BIT_MDAR_APB_ADC2_IMBP_BYPASS_2                   ( BIT_(2) )
#define BIT_MDAR_APB_ADC2_IMBP_BYPASS_1                   ( BIT_(1) )
#define BIT_MDAR_APB_ADC2_IMBP_BYPASS_0                   ( BIT_(0) )

/* bits definitions for register REG_MDAR_IMB_CFG21 */
#define BIT_MDAR_APB_ADC2_BAL_B(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_ADC2_BAL_A(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )

/* bits definitions for register REG_MDAR_IMB_CFG22 */
#define BIT_MDAR_APB_ADC2_BAL_D(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_ADC2_BAL_C(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )

/* bits definitions for register REG_MDAR_IMB_CFG23 */
#define BIT_MDAR_APB_DAC2_BAL_B(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_DAC2_BAL_A(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )

/* bits definitions for register REG_MDAR_IMB_CFG24 */
#define BIT_MDAR_APB_DAC2_BAL_D(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_DAC2_BAL_C(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )

/* bits definitions for register REG_MDAR_IMB_CFG30 */
#define BIT_MDAR_APB_ADC3_IMBP_CLK_SEL_5                  ( BIT_(21) )
#define BIT_MDAR_APB_ADC3_IMBP_CLK_SEL_4                  ( BIT_(20) )
#define BIT_MDAR_APB_ADC3_IMBP_CLK_SEL_3                  ( BIT_(19) )
#define BIT_MDAR_APB_ADC3_IMBP_CLK_SEL_2                  ( BIT_(18) )
#define BIT_MDAR_APB_ADC3_IMBP_CLK_SEL_1                  ( BIT_(17) )
#define BIT_MDAR_APB_ADC3_IMBP_CLK_SEL_0                  ( BIT_(16) )
#define BIT_MDAR_APB_DAC3_IMBP_BYPASS_5                   ( BIT_(13) )
#define BIT_MDAR_APB_DAC3_IMBP_BYPASS_4                   ( BIT_(12) )
#define BIT_MDAR_APB_DAC3_IMBP_BYPASS_3                   ( BIT_(11) )
#define BIT_MDAR_APB_DAC3_IMBP_BYPASS_2                   ( BIT_(10) )
#define BIT_MDAR_APB_DAC3_IMBP_BYPASS_1                   ( BIT_(9) )
#define BIT_MDAR_APB_DAC3_IMBP_BYPASS_0                   ( BIT_(8) )
#define BIT_MDAR_APB_ADC3_IMBP_BYPASS_5                   ( BIT_(5) )
#define BIT_MDAR_APB_ADC3_IMBP_BYPASS_4                   ( BIT_(4) )
#define BIT_MDAR_APB_ADC3_IMBP_BYPASS_3                   ( BIT_(3) )
#define BIT_MDAR_APB_ADC3_IMBP_BYPASS_2                   ( BIT_(2) )
#define BIT_MDAR_APB_ADC3_IMBP_BYPASS_1                   ( BIT_(1) )
#define BIT_MDAR_APB_ADC3_IMBP_BYPASS_0                   ( BIT_(0) )

/* bits definitions for register REG_MDAR_IMB_CFG31 */
#define BIT_MDAR_APB_ADC3_BAL_B(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_ADC3_BAL_A(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )

/* bits definitions for register REG_MDAR_IMB_CFG32 */
#define BIT_MDAR_APB_ADC3_BAL_D(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_ADC3_BAL_C(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )

/* bits definitions for register REG_MDAR_IMB_CFG33 */
#define BIT_MDAR_APB_DAC3_BAL_B(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_DAC3_BAL_A(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )

/* bits definitions for register REG_MDAR_IMB_CFG34 */
#define BIT_MDAR_APB_DAC3_BAL_D(_X_)                      ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)) )
#define BIT_MDAR_APB_DAC3_BAL_C(_X_)                      ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)) )

/* bits definitions for register REG_MDAR_RFTI_CFG0 */
#define BIT_MDAR_APB_RFTI1_SBI_MODE                       ( BIT_(31) )
#define BIT_MDAR_APB_RFTI1_SCENARIO_SSET(_X_)             ( (_X_) << 26 & (BIT_(26)|BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_RFTI1_UL_OSBC                        ( BIT_(25) )
#define BIT_MDAR_APB_RFTI1_UL_ISBC                        ( BIT_(24) )
#define BIT_MDAR_APB_RFTI1_UL_IQSWAP                      ( BIT_(23) )
#define BIT_MDAR_APB_RFTI1_DL_OSBC                        ( BIT_(22) )
#define BIT_MDAR_APB_RFTI1_DL_ISBC                        ( BIT_(21) )
#define BIT_MDAR_APB_RFTI1_DL_IQSWAP                      ( BIT_(20) )
#define BIT_MDAR_APB_RFTI1_UL_CHANNEL_SSET(_X_)           ( (_X_) << 15 & (BIT_(15)|BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)) )
#define BIT_MDAR_APB_RFTI1_UL_CHANNEL_MASK(_X_)           ( (_X_) << 10 & (BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)) )
#define BIT_MDAR_APB_RFTI1_DL_CHANNEL_SSET(_X_)           ( (_X_) << 5 & (BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)) )
#define BIT_MDAR_APB_RFTI1_DL_CHANNEL_MASK(_X_)           ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)) )

/* bits definitions for register REG_MDAR_RFTI_CFG1 */
#define BIT_MDAR_APB_RFTI2_SBI_MODE                       ( BIT_(31) )
#define BIT_MDAR_APB_RFTI2_SCENARIO_SSET(_X_)             ( (_X_) << 26 & (BIT_(26)|BIT_(27)|BIT_(28)) )
#define BIT_MDAR_APB_RFTI2_UL_OSBC                        ( BIT_(25) )
#define BIT_MDAR_APB_RFTI2_UL_ISBC                        ( BIT_(24) )
#define BIT_MDAR_APB_RFTI2_UL_IQSWAP                      ( BIT_(23) )
#define BIT_MDAR_APB_RFTI2_DL_OSBC                        ( BIT_(22) )
#define BIT_MDAR_APB_RFTI2_DL_ISBC                        ( BIT_(21) )
#define BIT_MDAR_APB_RFTI2_DL_IQSWAP                      ( BIT_(20) )
#define BIT_MDAR_APB_RFTI2_UL_CHANNEL_SSET(_X_)           ( (_X_) << 15 & (BIT_(15)|BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)) )
#define BIT_MDAR_APB_RFTI2_UL_CHANNEL_MASK(_X_)           ( (_X_) << 10 & (BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)) )
#define BIT_MDAR_APB_RFTI2_DL_CHANNEL_SSET(_X_)           ( (_X_) << 5 & (BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)) )
#define BIT_MDAR_APB_RFTI2_DL_CHANNEL_MASK(_X_)           ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)) )

/* bits definitions for register REG_MDAR_RFTI_CFG2 */
#define BIT_MDAR_APB_RFTI_DL_SBC_SET(_X_)                 ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_RFTI_UL_SBC_SET(_X_)                 ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_RFTI_CFG3 */
#define BIT_MDAR_APB_MDAR_RFTI_CFG3(_X_)                  ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_MDAR_RFTI2_SFIFO_SOFT_RST            ( BIT_(7) )
#define BIT_MDAR_APB_MDAR_RFTI2_STATUS_SOFT_RST           ( BIT_(6) )
#define BIT_MDAR_APB_MDAR_RFTI2_SPI_RESETB_SOFT_RST       ( BIT_(5) )
#define BIT_MDAR_APB_MDAR_RFTI2_RESETB_SOFT_RST           ( BIT_(4) )
#define BIT_MDAR_APB_MDAR_RFTI1_SFIFO_SOFT_RST            ( BIT_(3) )
#define BIT_MDAR_APB_MDAR_RFTI1_STATUS_SOFT_RST           ( BIT_(2) )
#define BIT_MDAR_APB_MDAR_RFTI1_SPI_RESETB_SOFT_RST       ( BIT_(1) )
#define BIT_MDAR_APB_MDAR_RFTI1_RESETB_SOFT_RST           ( BIT_(0) )

/* bits definitions for register REG_MDAR_RFTI_SBI1_CFG0 */
#define BIT_MDAR_APB_RFTI1_SBI_CFG0(_X_)                  (_X_)

/* bits definitions for register REG_MDAR_RFTI_SBI1_CFG1 */
#define BIT_MDAR_APB_RFTI1_SBI_CFG1(_X_)                  (_X_)

/* bits definitions for register REG_MDAR_RFTI_SBI1_CMD0 */
#define BIT_MDAR_APB_RFTI1_SBI_CMD_DATA(_X_)              (_X_)

/* bits definitions for register REG_MDAR_RFTI_SBI1_CMD1 */
#define BIT_MDAR_APB_RFTI1_SBI_EXTRA(_X_)                 ( (_X_) << 1 & (BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_RFTI1_SBI_SENX                       ( BIT_(0) )

/* bits definitions for register REG_MDAR_RFTI_SBI1_CMD2 */
#define BIT_MDAR_APB_RFTI1_SBI_STATE(_X_)                 ( (_X_) << 4 & (BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)) )
#define BIT_MDAR_APB_RFTI1_SBI_CMD_VLD                    ( BIT_(0) )

/* bits definitions for register REG_MDAR_RFTI_SBI1_RDATA */
#define BIT_MDAR_APB_RFTI1_SBI_RDATA(_X_)                 (_X_)

/* bits definitions for register REG_MDAR_RFTI_SBI2_CFG0 */
#define BIT_MDAR_APB_RFTI2_SBI_CFG0(_X_)                  (_X_)

/* bits definitions for register REG_MDAR_RFTI_SBI2_CFG1 */
#define BIT_MDAR_APB_RFTI2_SBI_CFG1(_X_)                  (_X_)

/* bits definitions for register REG_MDAR_RFTI_SBI2_CMD0 */
#define BIT_MDAR_APB_RFTI2_SBI_CMD_DATA(_X_)              (_X_)

/* bits definitions for register REG_MDAR_RFTI_SBI2_CMD1 */
#define BIT_MDAR_APB_RFTI2_SBI_EXTRA(_X_)                 ( (_X_) << 1 & (BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)|BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_RFTI2_SBI_SENX                       ( BIT_(0) )

/* bits definitions for register REG_MDAR_RFTI_SBI2_CMD2 */
#define BIT_MDAR_APB_RFTI2_SBI_STATE(_X_)                 ( (_X_) << 4 & (BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)) )
#define BIT_MDAR_APB_RFTI2_SBI_CMD_VLD                    ( BIT_(0) )

/* bits definitions for register REG_MDAR_RFTI_SBI2_RDATA */
#define BIT_MDAR_APB_RFTI2_SBI_RDATA(_X_)                 (_X_)

/* bits definitions for register REG_MDAR_RFTI1_INFO0 */
#define BIT_MDAR_APB_RFTI1_STATUS1(_X_)                   ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_RFTI1_STATUS0(_X_)                   ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_RFTI1_INFO1 */
#define BIT_MDAR_APB_RFTI1_STATUS3(_X_)                   ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_RFTI1_STATUS2(_X_)                   ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_RFTI1_INFO2 */
#define BIT_MDAR_APB_RFTI1_STATUS5(_X_)                   ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_RFTI1_STATUS4(_X_)                   ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_RFTI1_INFO3 */
#define BIT_MDAR_APB_RFTI1_STATUS7(_X_)                   ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_RFTI1_STATUS6(_X_)                   ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_RFTI2_INFO0 */
#define BIT_MDAR_APB_RFTI2_STATUS1(_X_)                   ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_RFTI2_STATUS0(_X_)                   ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_RFTI2_INFO1 */
#define BIT_MDAR_APB_RFTI2_STATUS3(_X_)                   ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_RFTI2_STATUS2(_X_)                   ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_RFTI2_INFO2 */
#define BIT_MDAR_APB_RFTI2_STATUS5(_X_)                   ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_RFTI2_STATUS4(_X_)                   ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_RFTI2_INFO3 */
#define BIT_MDAR_APB_RFTI2_STATUS7(_X_)                   ( (_X_) << 16 & (BIT_(16)|BIT_(17)|BIT_(18)|BIT_(19)|BIT_(20)|BIT_(21)|BIT_(22)|BIT_(23)|BIT_(24)|BIT_(25)|BIT_(26)|BIT_(27)|BIT_(28)|BIT_(29)|BIT_(30)|BIT_(31)) )
#define BIT_MDAR_APB_RFTI2_STATUS6(_X_)                   ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)|BIT_(5)|BIT_(6)|BIT_(7)|BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )

/* bits definitions for register REG_MDAR_RFTI11_DUG_BUS */
#define BIT_MDAR_APB_RFTI1_TBUS_DATA(_X_)                 ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )
#define BIT_MDAR_APB_RFTI1_TBUS_MODE                      ( BIT_(5) )
#define BIT_MDAR_APB_RFTI1_TBUS_ADDR(_X_)                 ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)) )

/* bits definitions for register REG_MDAR_RFTI12_DUG_BUS */
#define BIT_MDAR_APB_RFTI2_TBUS_DATA(_X_)                 ( (_X_) << 8 & (BIT_(8)|BIT_(9)|BIT_(10)|BIT_(11)|BIT_(12)|BIT_(13)|BIT_(14)|BIT_(15)) )
#define BIT_MDAR_APB_RFTI2_TBUS_MODE                      ( BIT_(5) )
#define BIT_MDAR_APB_RFTI2_TBUS_ADDR(_X_)                 ( (_X_) & (BIT_(0)|BIT_(1)|BIT_(2)|BIT_(3)|BIT_(4)) )

#endif

