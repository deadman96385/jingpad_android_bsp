/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-18 10:53:50
 *
 */


#ifndef MPHY_CFGA_H
#define MPHY_CFGA_H

#define CTL_BASE_MPHY_CFGA 0x323B8000


#define REG_MPHY_CFGA_DIG_CFG0   ( CTL_BASE_MPHY_CFGA + 0x0000 )
#define REG_MPHY_CFGA_DIG_CFG1   ( CTL_BASE_MPHY_CFGA + 0x0004 )
#define REG_MPHY_CFGA_DIG_CFG2   ( CTL_BASE_MPHY_CFGA + 0x0008 )
#define REG_MPHY_CFGA_DIG_CFG3   ( CTL_BASE_MPHY_CFGA + 0x000C )
#define REG_MPHY_CFGA_DIG_CFG4   ( CTL_BASE_MPHY_CFGA + 0x0010 )
#define REG_MPHY_CFGA_DIG_CFG5   ( CTL_BASE_MPHY_CFGA + 0x0014 )
#define REG_MPHY_CFGA_DIG_CFG6   ( CTL_BASE_MPHY_CFGA + 0x0018 )
#define REG_MPHY_CFGA_DIG_CFG7   ( CTL_BASE_MPHY_CFGA + 0x001C )
#define REG_MPHY_CFGA_DIG_CFG8   ( CTL_BASE_MPHY_CFGA + 0x0020 )
#define REG_MPHY_CFGA_DIG_CFG9   ( CTL_BASE_MPHY_CFGA + 0x0024 )
#define REG_MPHY_CFGA_DIG_CFG10  ( CTL_BASE_MPHY_CFGA + 0x0028 )
#define REG_MPHY_CFGA_DIG_CFG11  ( CTL_BASE_MPHY_CFGA + 0x002C )
#define REG_MPHY_CFGA_DIG_CFG12  ( CTL_BASE_MPHY_CFGA + 0x0030 )
#define REG_MPHY_CFGA_DIG_CFG13  ( CTL_BASE_MPHY_CFGA + 0x0034 )
#define REG_MPHY_CFGA_DIG_CFG14  ( CTL_BASE_MPHY_CFGA + 0x0038 )
#define REG_MPHY_CFGA_DIG_CFG15  ( CTL_BASE_MPHY_CFGA + 0x003C )
#define REG_MPHY_CFGA_DIG_CFG16  ( CTL_BASE_MPHY_CFGA + 0x0040 )
#define REG_MPHY_CFGA_DIG_CFG17  ( CTL_BASE_MPHY_CFGA + 0x0044 )
#define REG_MPHY_CFGA_DIG_CFG18  ( CTL_BASE_MPHY_CFGA + 0x0048 )
#define REG_MPHY_CFGA_DIG_CFG19  ( CTL_BASE_MPHY_CFGA + 0x004C )
#define REG_MPHY_CFGA_DIG_CFG20  ( CTL_BASE_MPHY_CFGA + 0x0050 )
#define REG_MPHY_CFGA_DIG_CFG21  ( CTL_BASE_MPHY_CFGA + 0x0054 )
#define REG_MPHY_CFGA_DIG_CFG22  ( CTL_BASE_MPHY_CFGA + 0x0058 )
#define REG_MPHY_CFGA_DIG_CFG23  ( CTL_BASE_MPHY_CFGA + 0x005C )
#define REG_MPHY_CFGA_DIG_CFG24  ( CTL_BASE_MPHY_CFGA + 0x0060 )
#define REG_MPHY_CFGA_DIG_CFG25  ( CTL_BASE_MPHY_CFGA + 0x0064 )
#define REG_MPHY_CFGA_DIG_CFG26  ( CTL_BASE_MPHY_CFGA + 0x0068 )
#define REG_MPHY_CFGA_DIG_CFG27  ( CTL_BASE_MPHY_CFGA + 0x006C )
#define REG_MPHY_CFGA_DIG_CFG28  ( CTL_BASE_MPHY_CFGA + 0x0070 )
#define REG_MPHY_CFGA_DIG_CFG29  ( CTL_BASE_MPHY_CFGA + 0x0074 )
#define REG_MPHY_CFGA_DIG_CFG30  ( CTL_BASE_MPHY_CFGA + 0x0078 )
#define REG_MPHY_CFGA_DIG_CFG31  ( CTL_BASE_MPHY_CFGA + 0x007C )
#define REG_MPHY_CFGA_DIG_CFG32  ( CTL_BASE_MPHY_CFGA + 0x0080 )
#define REG_MPHY_CFGA_DIG_CFG33  ( CTL_BASE_MPHY_CFGA + 0x0084 )
#define REG_MPHY_CFGA_DIG_CFG34  ( CTL_BASE_MPHY_CFGA + 0x0088 )
#define REG_MPHY_CFGA_DIG_CFG35  ( CTL_BASE_MPHY_CFGA + 0x008C )
#define REG_MPHY_CFGA_DIG_CFG36  ( CTL_BASE_MPHY_CFGA + 0x0090 )
#define REG_MPHY_CFGA_DIG_CFG37  ( CTL_BASE_MPHY_CFGA + 0x0094 )
#define REG_MPHY_CFGA_DIG_CFG38  ( CTL_BASE_MPHY_CFGA + 0x0098 )
#define REG_MPHY_CFGA_DIG_CFG39  ( CTL_BASE_MPHY_CFGA + 0x009C )
#define REG_MPHY_CFGA_DIG_CFG40  ( CTL_BASE_MPHY_CFGA + 0x00A0 )
#define REG_MPHY_CFGA_DIG_CFG41  ( CTL_BASE_MPHY_CFGA + 0x00A4 )
#define REG_MPHY_CFGA_DIG_CFG42  ( CTL_BASE_MPHY_CFGA + 0x00A8 )
#define REG_MPHY_CFGA_DIG_CFG43  ( CTL_BASE_MPHY_CFGA + 0x00AC )
#define REG_MPHY_CFGA_DIG_CFG44  ( CTL_BASE_MPHY_CFGA + 0x00B0 )
#define REG_MPHY_CFGA_DIG_CFG45  ( CTL_BASE_MPHY_CFGA + 0x00B4 )
#define REG_MPHY_CFGA_DIG_CFG46  ( CTL_BASE_MPHY_CFGA + 0x00B8 )
#define REG_MPHY_CFGA_DIG_CFG47  ( CTL_BASE_MPHY_CFGA + 0x00BC )
#define REG_MPHY_CFGA_DIG_CFG48  ( CTL_BASE_MPHY_CFGA + 0x00C0 )
#define REG_MPHY_CFGA_DIG_CFG49  ( CTL_BASE_MPHY_CFGA + 0x00C4 )
#define REG_MPHY_CFGA_DIG_CFG50  ( CTL_BASE_MPHY_CFGA + 0x00C8 )
#define REG_MPHY_CFGA_DIG_CFG51  ( CTL_BASE_MPHY_CFGA + 0x00CC )
#define REG_MPHY_CFGA_DIG_CFG52  ( CTL_BASE_MPHY_CFGA + 0x00D0 )
#define REG_MPHY_CFGA_DIG_CFG53  ( CTL_BASE_MPHY_CFGA + 0x00D4 )
#define REG_MPHY_CFGA_DIG_CFG54  ( CTL_BASE_MPHY_CFGA + 0x00D8 )
#define REG_MPHY_CFGA_DIG_CFG55  ( CTL_BASE_MPHY_CFGA + 0x00DC )
#define REG_MPHY_CFGA_DIG_CFG56  ( CTL_BASE_MPHY_CFGA + 0x00E0 )
#define REG_MPHY_CFGA_DIG_CFG57  ( CTL_BASE_MPHY_CFGA + 0x00E4 )
#define REG_MPHY_CFGA_DIG_CFG58  ( CTL_BASE_MPHY_CFGA + 0x00E8 )
#define REG_MPHY_CFGA_DIG_CFG59  ( CTL_BASE_MPHY_CFGA + 0x00EC )
#define REG_MPHY_CFGA_DIG_CFG60  ( CTL_BASE_MPHY_CFGA + 0x00F0 )
#define REG_MPHY_CFGA_DIG_CFG61  ( CTL_BASE_MPHY_CFGA + 0x00F4 )
#define REG_MPHY_CFGA_DIG_CFG62  ( CTL_BASE_MPHY_CFGA + 0x00F8 )
#define REG_MPHY_CFGA_DIG_CFG63  ( CTL_BASE_MPHY_CFGA + 0x00FC )
#define REG_MPHY_CFGA_DIG_CFG64  ( CTL_BASE_MPHY_CFGA + 0x0100 )
#define REG_MPHY_CFGA_DIG_CFG65  ( CTL_BASE_MPHY_CFGA + 0x0104 )
#define REG_MPHY_CFGA_DIG_CFG66  ( CTL_BASE_MPHY_CFGA + 0x0108 )

/* REG_MPHY_CFGA_DIG_CFG0 */

#define BIT_MPHY_CFGA_DIG_CFG0_REG_OFFK_INIT_AFE(x)            (((x) & 0xFF) << 20)
#define BIT_MPHY_CFGA_DIG_CFG0_REG_OFFK_MANUAL_SLICER          BIT(18)
#define BIT_MPHY_CFGA_DIG_CFG0_REG_OFFK_RSTN                   BIT(17)
#define BIT_MPHY_CFGA_DIG_CFG0_REG_OFFK_EN                     BIT(16)
#define BIT_MPHY_CFGA_DIG_CFG0_REG_OFFK_MANUAL_AFE             BIT(15)
#define BIT_MPHY_CFGA_DIG_CFG0_REG_OFFK_BIAS_HALF              BIT(14)
#define BIT_MPHY_CFGA_DIG_CFG0_REG_OFFK_RATE(x)                (((x) & 0xF) << 10)
#define BIT_MPHY_CFGA_DIG_CFG0_REG_OFFK_RATE_EN                BIT(9)
#define BIT_MPHY_CFGA_DIG_CFG0_REG_OFFK_INV_SLICER             BIT(8)
#define BIT_MPHY_CFGA_DIG_CFG0_REG_OFFK_INV_AFE                BIT(7)
#define BIT_MPHY_CFGA_DIG_CFG0_REG_OFFK_STABLE_MODE_SLICER(x)  (((x) & 0x7) << 4)
#define BIT_MPHY_CFGA_DIG_CFG0_REG_OFFK_STABLE_MODE_AFE(x)     (((x) & 0x7) << 1)
#define BIT_MPHY_CFGA_DIG_CFG0_REG_OFFK_MODE                   BIT(0)

/* REG_MPHY_CFGA_DIG_CFG1 */

#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_TAP0_MANUAL             BIT(31)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_TAP0_INIT               BIT(30)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_DFE_ANA_EN              BIT(29)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_LS_LDO_STABLE           BIT(28)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_PGAINC                  BIT(27)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_PLL_LATCHEN             BIT(26)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_CDR_MODE_CTRL           BIT(25)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_TXLDOZP9_EN             BIT(24)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_TXLDOZP4_EN             BIT(23)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_HS_LDO_STABLE           BIT(22)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_TRIM_RXTERM             BIT(21)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_TRIM_TXTERM             BIT(20)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_TRIM_BG                 BIT(19)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_DCO_CAL_EN              BIT(18)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_DCO_EN                  BIT(17)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_DCO_CTRLBIT             BIT(16)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_REFCLK_OEN              BIT(15)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_PLL_PRECHARGE           BIT(14)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_PLL_PU                  BIT(13)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_CDR_DIV2_EN             BIT(12)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_PEAK2G5                 BIT(11)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_TAP1_HOLD               BIT(10)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_TAP0_HOLD               BIT(9)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_LEQ_HOLD                BIT(8)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_TAP1_ADAPT_EN           BIT(7)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_TAP0_ADAPT_EN           BIT(6)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_LEQ_ADAPT_EN            BIT(5)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_READ_COEF_SEL           BIT(4)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_OFFK_INIT_AFE           BIT(3)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_OFFK_RSTN               BIT(2)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_OFFK_EN                 BIT(1)
#define BIT_MPHY_CFGA_DIG_CFG1_OVR_REG_OFFK_MANUAL_AFE         BIT(0)

/* REG_MPHY_CFGA_DIG_CFG2 */

#define BIT_MPHY_CFGA_DIG_CFG2_REG_TAP1_HOLD                   BIT(31)
#define BIT_MPHY_CFGA_DIG_CFG2_REG_TAP0_HOLD                   BIT(30)
#define BIT_MPHY_CFGA_DIG_CFG2_REG_LEQ_HOLD                    BIT(29)
#define BIT_MPHY_CFGA_DIG_CFG2_REG_LEQ_ADAPT_EN                BIT(28)
#define BIT_MPHY_CFGA_DIG_CFG2_REG_LEQ_READ_LIMIT              BIT(27)
#define BIT_MPHY_CFGA_DIG_CFG2_REG_LEQ_INIT(x)                 (((x) & 0x1F) << 22)
#define BIT_MPHY_CFGA_DIG_CFG2_REG_LEQ_MAX(x)                  (((x) & 0x1F) << 17)
#define BIT_MPHY_CFGA_DIG_CFG2_REG_LEQ_MIN(x)                  (((x) & 0x1F) << 12)
#define BIT_MPHY_CFGA_DIG_CFG2_REG_LEQ_LOOP_GAIN(x)            (((x) & 0x7) << 9)
#define BIT_MPHY_CFGA_DIG_CFG2_REG_LEQ_MANUAL                  BIT(8)
#define BIT_MPHY_CFGA_DIG_CFG2_REG_LEQ_ADAPT_RSTN              BIT(7)
#define BIT_MPHY_CFGA_DIG_CFG2_REG_LEQ_ADAPT_INV               BIT(6)
#define BIT_MPHY_CFGA_DIG_CFG2_REG_LEQ_SLICE_EN                BIT(5)
#define BIT_MPHY_CFGA_DIG_CFG2_REG_LEQ_RATE_EN                 BIT(4)
#define BIT_MPHY_CFGA_DIG_CFG2_REG_LEQ_RATE(x)                 (((x) & 0xF))

/* REG_MPHY_CFGA_DIG_CFG3 */

#define BIT_MPHY_CFGA_DIG_CFG3_OVR_REG_DFE_ADAPT_EN            BIT(26)
#define BIT_MPHY_CFGA_DIG_CFG3_REG_READ_COEF_SEL(x)            (((x) & 0xFF) << 18)
#define BIT_MPHY_CFGA_DIG_CFG3_REG_DFE_ADAPT_EN                BIT(17)
#define BIT_MPHY_CFGA_DIG_CFG3_REG_DFE_ANA_EN                  BIT(16)
#define BIT_MPHY_CFGA_DIG_CFG3_REG_DFE_ADAPT_RSTN              BIT(15)
#define BIT_MPHY_CFGA_DIG_CFG3_REG_BIAS_BOOST(x)               (((x) & 0xFF) << 7)
#define BIT_MPHY_CFGA_DIG_CFG3_REG_PEAK2G5                     BIT(6)
#define BIT_MPHY_CFGA_DIG_CFG3_REG_HIGHGAIN                    BIT(5)
#define BIT_MPHY_CFGA_DIG_CFG3_REG_CONSTGM_EN                  BIT(4)
#define BIT_MPHY_CFGA_DIG_CFG3_REG_LEQ_OFFSET_IN(x)            (((x) & 0xF))

/* REG_MPHY_CFGA_DIG_CFG4 */

#define BIT_MPHY_CFGA_DIG_CFG4_REG_TAP0_READ_LIMIT             BIT(30)
#define BIT_MPHY_CFGA_DIG_CFG4_REG_TAP0_ADAPT_INV              BIT(29)
#define BIT_MPHY_CFGA_DIG_CFG4_REG_TAP0_INIT(x)                (((x) & 0x1F) << 24)
#define BIT_MPHY_CFGA_DIG_CFG4_REG_TAP0_LOOP_GAIN(x)           (((x) & 0x7) << 21)
#define BIT_MPHY_CFGA_DIG_CFG4_REG_TAP0_MANUAL                 BIT(20)
#define BIT_MPHY_CFGA_DIG_CFG4_REG_TAP0_MAX(x)                 (((x) & 0x1F) << 15)
#define BIT_MPHY_CFGA_DIG_CFG4_REG_TAP0_MIN(x)                 (((x) & 0x1F) << 10)
#define BIT_MPHY_CFGA_DIG_CFG4_REG_TAP0_NOTRANS                BIT(9)
#define BIT_MPHY_CFGA_DIG_CFG4_REG_TAP0_RATE(x)                (((x) & 0xF) << 5)
#define BIT_MPHY_CFGA_DIG_CFG4_REG_TAP0_RATE_EN                BIT(4)
#define BIT_MPHY_CFGA_DIG_CFG4_REG_TAP0_RUNLENGTH(x)           (((x) & 0x3) << 2)
#define BIT_MPHY_CFGA_DIG_CFG4_REG_TAP0_SLICE_EN               BIT(1)
#define BIT_MPHY_CFGA_DIG_CFG4_REG_TAP0_ADAPT_EN               BIT(0)

/* REG_MPHY_CFGA_DIG_CFG5 */

#define BIT_MPHY_CFGA_DIG_CFG5_REG_TAP1_READ_LIMIT             BIT(28)
#define BIT_MPHY_CFGA_DIG_CFG5_REG_TAP1_ADAPT_INV              BIT(27)
#define BIT_MPHY_CFGA_DIG_CFG5_REG_TAP1_INIT(x)                (((x) & 0x1F) << 22)
#define BIT_MPHY_CFGA_DIG_CFG5_REG_TAP1_LOOP_GAIN(x)           (((x) & 0x7) << 19)
#define BIT_MPHY_CFGA_DIG_CFG5_REG_TAP1_MANUAL                 BIT(18)
#define BIT_MPHY_CFGA_DIG_CFG5_REG_TAP1_MAX(x)                 (((x) & 0x1F) << 13)
#define BIT_MPHY_CFGA_DIG_CFG5_REG_TAP1_MIN(x)                 (((x) & 0x1F) << 8)
#define BIT_MPHY_CFGA_DIG_CFG5_REG_TAP1_RATE(x)                (((x) & 0xF) << 4)
#define BIT_MPHY_CFGA_DIG_CFG5_REG_TAP1_RATE_EN                BIT(3)
#define BIT_MPHY_CFGA_DIG_CFG5_REG_TAP1_SLICE_EN               BIT(2)
#define BIT_MPHY_CFGA_DIG_CFG5_REG_TAP1_TRANS                  BIT(1)
#define BIT_MPHY_CFGA_DIG_CFG5_REG_TAP1_ADAPT_EN               BIT(0)

/* REG_MPHY_CFGA_DIG_CFG6 */

#define BIT_MPHY_CFGA_DIG_CFG6_REG_VTH_ADAPT_EN                BIT(29)
#define BIT_MPHY_CFGA_DIG_CFG6_REG_VTH_INIT(x)                 (((x) & 0x3F) << 23)
#define BIT_MPHY_CFGA_DIG_CFG6_REG_VTH_MANUAL                  BIT(22)
#define BIT_MPHY_CFGA_DIG_CFG6_REG_VTH_MAX(x)                  (((x) & 0x3F) << 16)
#define BIT_MPHY_CFGA_DIG_CFG6_REG_VTH_MIN(x)                  (((x) & 0x3F) << 10)
#define BIT_MPHY_CFGA_DIG_CFG6_REG_VTH_RATE(x)                 (((x) & 0xF) << 6)
#define BIT_MPHY_CFGA_DIG_CFG6_REG_VTH_SIGN_IN                 BIT(5)
#define BIT_MPHY_CFGA_DIG_CFG6_REG_VTH_SIGN_TOGGLE_EN          BIT(4)
#define BIT_MPHY_CFGA_DIG_CFG6_REG_VTH_SIGN_TOGGLE_RATE(x)     (((x) & 0xF))

/* REG_MPHY_CFGA_DIG_CFG7 */

#define BIT_MPHY_CFGA_DIG_CFG7_REG_PI_MANUAL(x)                (((x) & 0x7F) << 25)
#define BIT_MPHY_CFGA_DIG_CFG7_REG_CDR_MONITOR_BYPASS          BIT(24)
#define BIT_MPHY_CFGA_DIG_CFG7_REG_CDR_JUMP_VTH(x)             (((x) & 0x3) << 22)
#define BIT_MPHY_CFGA_DIG_CFG7_REG_CDR_JUMP_CASE               BIT(21)
#define BIT_MPHY_CFGA_DIG_CFG7_REG_CDR_JUMP_INIT               BIT(20)
#define BIT_MPHY_CFGA_DIG_CFG7_REG_CDR_JUMP_STEP               BIT(19)
#define BIT_MPHY_CFGA_DIG_CFG7_REG_CDR_SCENARIO(x)             (((x) & 0x3) << 17)
#define BIT_MPHY_CFGA_DIG_CFG7_REG_PGAINC(x)                   (((x) & 0x7) << 14)
#define BIT_MPHY_CFGA_DIG_CFG7_REG_FGAINC(x)                   (((x) & 0x7) << 11)
#define BIT_MPHY_CFGA_DIG_CFG7_REG_FPATH_OFF                   BIT(10)
#define BIT_MPHY_CFGA_DIG_CFG7_REG_CDR_MODE_CTRL               BIT(9)
#define BIT_MPHY_CFGA_DIG_CFG7_REG_MIX_RST                     BIT(8)
#define BIT_MPHY_CFGA_DIG_CFG7_REG_CDR_DIV2_EN                 BIT(7)
#define BIT_MPHY_CFGA_DIG_CFG7_REG_PPM_CTRL(x)                 (((x) & 0x3) << 5)
#define BIT_MPHY_CFGA_DIG_CFG7_REG_FIRST_ORDER_N               BIT(4)
#define BIT_MPHY_CFGA_DIG_CFG7_REG_SAT_CTRL                    BIT(3)
#define BIT_MPHY_CFGA_DIG_CFG7_REG_PI_MANUAL_EN                BIT(2)
#define BIT_MPHY_CFGA_DIG_CFG7_REG_FREQOS_CASE                 BIT(1)
#define BIT_MPHY_CFGA_DIG_CFG7_REG_FREQOSIN                    BIT(0)

/* REG_MPHY_CFGA_DIG_CFG8 */

#define BIT_MPHY_CFGA_DIG_CFG8_RSTN_DEVICE_OVR_VAL             BIT(27)
#define BIT_MPHY_CFGA_DIG_CFG8_RSTN_DEVICE_OVR                 BIT(26)
#define BIT_MPHY_CFGA_DIG_CFG8_RSTN_ANA_OVR_VAL                BIT(25)
#define BIT_MPHY_CFGA_DIG_CFG8_RSTN_ANA_OVR                    BIT(24)
#define BIT_MPHY_CFGA_DIG_CFG8_PWM_CFGRDY_IGNORE_EXT           BIT(23)
#define BIT_MPHY_CFGA_DIG_CFG8_STARTUP_TIME(x)                 (((x) & 0x7FFF) << 8)
#define BIT_MPHY_CFGA_DIG_CFG8_REG_FREQ_INTEG_IN(x)            (((x) & 0xFF))

/* REG_MPHY_CFGA_DIG_CFG9 */

#define BIT_MPHY_CFGA_DIG_CFG9_REG_STEP4_CFG(x)                (((x) & 0xFF) << 24)
#define BIT_MPHY_CFGA_DIG_CFG9_REG_STEP3_CFG(x)                (((x) & 0xFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG9_REG_STEP2_CFG(x)                (((x) & 0xFF) << 8)
#define BIT_MPHY_CFGA_DIG_CFG9_REG_STEP1_CFG(x)                (((x) & 0xFF))

/* REG_MPHY_CFGA_DIG_CFG10 */

#define BIT_MPHY_CFGA_DIG_CFG10_REG_STEP4_CYCLE(x)             (((x) & 0xFFFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG10_REG_STEP3_CYCLE(x)             (((x) & 0xFFFF))

/* REG_MPHY_CFGA_DIG_CFG11 */

#define BIT_MPHY_CFGA_DIG_CFG11_REG_STEP2_CYCLE(x)             (((x) & 0xFFFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG11_REG_STEP1_CYCLE(x)             (((x) & 0xFFFF))

/* REG_MPHY_CFGA_DIG_CFG12 */

#define BIT_MPHY_CFGA_DIG_CFG12_REG_MOD_EN                     BIT(31)
#define BIT_MPHY_CFGA_DIG_CFG12_REG_KDELTA(x)                  (((x) & 0xFFF) << 19)
#define BIT_MPHY_CFGA_DIG_CFG12_REG_KSTEP(x)                   (((x) & 0x7FFFF))

/* REG_MPHY_CFGA_DIG_CFG13 */

#define BIT_MPHY_CFGA_DIG_CFG13_REG_RATEB                      BIT(31)
#define BIT_MPHY_CFGA_DIG_CFG13_REG_FDK_S                      BIT(30)
#define BIT_MPHY_CFGA_DIG_CFG13_REG_HOP_TRIG                   BIT(29)
#define BIT_MPHY_CFGA_DIG_CFG13_REG_HOP_EN                     BIT(28)
#define BIT_MPHY_CFGA_DIG_CFG13_REG_NINT(x)                    (((x) & 0xFF) << 20)
#define BIT_MPHY_CFGA_DIG_CFG13_REG_KINT(x)                    (((x) & 0xFFFFF))

/* REG_MPHY_CFGA_DIG_CFG14 */

#define BIT_MPHY_CFGA_DIG_CFG14_REG_PLL_LATCHEN                BIT(31)
#define BIT_MPHY_CFGA_DIG_CFG14_CB_REFCLKON_BYP                BIT(30)
#define BIT_MPHY_CFGA_DIG_CFG14_CB_REFCLKON                    BIT(29)
#define BIT_MPHY_CFGA_DIG_CFG14_PLL_GEAR(x)                    (((x) & 0x3) << 27)
#define BIT_MPHY_CFGA_DIG_CFG14_PLL_SERIES(x)                  (((x) & 0x3) << 25)
#define BIT_MPHY_CFGA_DIG_CFG14_REG_REFCLK_OEN                 BIT(24)
#define BIT_MPHY_CFGA_DIG_CFG14_REG_PLL_PRECHARGE              BIT(23)
#define BIT_MPHY_CFGA_DIG_CFG14_REG_PLL_PU                     BIT(22)
#define BIT_MPHY_CFGA_DIG_CFG14_REG_SSC_DIV2                   BIT(21)
#define BIT_MPHY_CFGA_DIG_CFG14_REG_NS(x)                      (((x) & 0xFF) << 13)
#define BIT_MPHY_CFGA_DIG_CFG14_REG_LPF(x)                     (((x) & 0x3) << 11)
#define BIT_MPHY_CFGA_DIG_CFG14_REG_DIVN(x)                    (((x) & 0x7) << 8)
#define BIT_MPHY_CFGA_DIG_CFG14_REG_CP(x)                      (((x) & 0x3) << 6)
#define BIT_MPHY_CFGA_DIG_CFG14_REG_RCLK_OUT_SEL               BIT(5)
#define BIT_MPHY_CFGA_DIG_CFG14_REG_PRESEL(x)                  (((x) & 0x3) << 3)
#define BIT_MPHY_CFGA_DIG_CFG14_REG_SDM_EN                     BIT(2)
#define BIT_MPHY_CFGA_DIG_CFG14_REG_VCO_BAND                   BIT(1)
#define BIT_MPHY_CFGA_DIG_CFG14_REG_HSG1SEL                    BIT(0)

/* REG_MPHY_CFGA_DIG_CFG15 */

#define BIT_MPHY_CFGA_DIG_CFG15_CFG_REG_SEL                    BIT(31)
#define BIT_MPHY_CFGA_DIG_CFG15_OVR_REG_PLL_PRELOCK            BIT(30)
#define BIT_MPHY_CFGA_DIG_CFG15_REG_PLL_PRELOCK                BIT(29)
#define BIT_MPHY_CFGA_DIG_CFG15_REG_PWMGEAR_KEEP               BIT(28)
#define BIT_MPHY_CFGA_DIG_CFG15_REG_RSTN_EN_SEL                BIT(27)
#define BIT_MPHY_CFGA_DIG_CFG15_REG_CP_OFFSET(x)               (((x) & 0x3) << 25)
#define BIT_MPHY_CFGA_DIG_CFG15_REFCLKMODE(x)                  (((x) & 0x3) << 23)
#define BIT_MPHY_CFGA_DIG_CFG15_DCOEXPNUMOVR                   BIT(22)
#define BIT_MPHY_CFGA_DIG_CFG15_DCOEXPNUMOVRVAL(x)             (((x) & 0x1FF) << 13)
#define BIT_MPHY_CFGA_DIG_CFG15_REG_DCO_CAL_EN                 BIT(12)
#define BIT_MPHY_CFGA_DIG_CFG15_REG_DCO_EN                     BIT(11)
#define BIT_MPHY_CFGA_DIG_CFG15_REG_DCO_NOM_FUNC               BIT(10)
#define BIT_MPHY_CFGA_DIG_CFG15_REG_DCO_CLK_SEL(x)             (((x) & 0x3) << 8)
#define BIT_MPHY_CFGA_DIG_CFG15_REG_DCO_CTRLBIT(x)             (((x) & 0xFF))

/* REG_MPHY_CFGA_DIG_CFG16 */

#define BIT_MPHY_CFGA_DIG_CFG16_REG_TRIM_SQVREF(x)             (((x) & 0xF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG16_REG_TRIM_PLLLDO(x)             (((x) & 0xF) << 12)
#define BIT_MPHY_CFGA_DIG_CFG16_REG_TRIM_RXTERM(x)             (((x) & 0xF) << 8)
#define BIT_MPHY_CFGA_DIG_CFG16_REG_TRIM_TXTERM(x)             (((x) & 0xF) << 4)
#define BIT_MPHY_CFGA_DIG_CFG16_REG_TRIM_BG(x)                 (((x) & 0xF))

/* REG_MPHY_CFGA_DIG_CFG17 */

#define BIT_MPHY_CFGA_DIG_CFG17_OVR_REG_DCO_READY              BIT(28)
#define BIT_MPHY_CFGA_DIG_CFG17_REG_DCO_READY                  BIT(27)
#define BIT_MPHY_CFGA_DIG_CFG17_REG_PI_CURRENT_SEL(x)          (((x) & 0x3) << 25)
#define BIT_MPHY_CFGA_DIG_CFG17_PLL_LOCKTIME_MULTI(x)          (((x) & 0x7) << 22)
#define BIT_MPHY_CFGA_DIG_CFG17_REG_LS_BIAS_VAL                BIT(21)
#define BIT_MPHY_CFGA_DIG_CFG17_REG_LS_BIAS_OVR                BIT(20)
#define BIT_MPHY_CFGA_DIG_CFG17_REG_HS_BIAS_VAL                BIT(19)
#define BIT_MPHY_CFGA_DIG_CFG17_REG_HS_BIAS_OVR                BIT(18)
#define BIT_MPHY_CFGA_DIG_CFG17_REG_LS_LDO_STABLE              BIT(17)
#define BIT_MPHY_CFGA_DIG_CFG17_REG_PLLLDO_TEST_EN             BIT(16)
#define BIT_MPHY_CFGA_DIG_CFG17_REG_PLLLDO_TEST_SEL            BIT(15)
#define BIT_MPHY_CFGA_DIG_CFG17_REG_LDO_ZP9_SEL(x)             (((x) & 0x7) << 12)
#define BIT_MPHY_CFGA_DIG_CFG17_REG_LDO_ZP4_SEL(x)             (((x) & 0x7) << 9)
#define BIT_MPHY_CFGA_DIG_CFG17_REG_LDO_PI_REF(x)              (((x) & 0x3) << 7)
#define BIT_MPHY_CFGA_DIG_CFG17_REG_LDO_RX_REF(x)              (((x) & 0x3) << 5)
#define BIT_MPHY_CFGA_DIG_CFG17_REG_TXLDOCK_FILTER(x)          (((x) & 0x3) << 3)
#define BIT_MPHY_CFGA_DIG_CFG17_REG_TXLDOZP9_EN                BIT(2)
#define BIT_MPHY_CFGA_DIG_CFG17_REG_TXLDOZP4_EN                BIT(1)
#define BIT_MPHY_CFGA_DIG_CFG17_REG_HS_LDO_STABLE              BIT(0)

/* REG_MPHY_CFGA_DIG_CFG18 */

#define BIT_MPHY_CFGA_DIG_CFG18_PREPAREDEBUG                   BIT(31)
#define BIT_MPHY_CFGA_DIG_CFG18_CB_CFGINLNSHDWZ                BIT(30)
#define BIT_MPHY_CFGA_DIG_CFG18_CFGSTARTUPCTRL(x)              (((x) & 0x3) << 28)
#define BIT_MPHY_CFGA_DIG_CFG18_REDOTERMCAL                    BIT(27)
#define BIT_MPHY_CFGA_DIG_CFG18_REDODCOCAL                     BIT(26)
#define BIT_MPHY_CFGA_DIG_CFG18_POWERUPOVR                     BIT(25)
#define BIT_MPHY_CFGA_DIG_CFG18_POWERUPOVRVAL                  BIT(24)
#define BIT_MPHY_CFGA_DIG_CFG18_PLLTIMER(x)                    (((x) & 0xFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG18_TIMERCLKDIV(x)                 (((x) & 0xFF) << 8)
#define BIT_MPHY_CFGA_DIG_CFG18_PLLLOCK_SEL                    BIT(7)
#define BIT_MPHY_CFGA_DIG_CFG18_CFGDIV_SRC                     BIT(6)
#define BIT_MPHY_CFGA_DIG_CFG18_CB_REFOUT_SRC                  BIT(5)
#define BIT_MPHY_CFGA_DIG_CFG18_MODE_SET_SEL                   BIT(4)
#define BIT_MPHY_CFGA_DIG_CFG18_HIBERN8_SRC_SEL                BIT(3)
#define BIT_MPHY_CFGA_DIG_CFG18_DCO_CB_SET                     BIT(2)
#define BIT_MPHY_CFGA_DIG_CFG18_PLL_CB_SET                     BIT(1)
#define BIT_MPHY_CFGA_DIG_CFG18_STARTUPCTRL_UPDATE             BIT(0)

/* REG_MPHY_CFGA_DIG_CFG19 */

#define BIT_MPHY_CFGA_DIG_CFG19_REG_FORCE_SA_IDC_EN            BIT(31)
#define BIT_MPHY_CFGA_DIG_CFG19_LSLINKDIVIDERLB(x)             (((x) & 0x1F) << 26)
#define BIT_MPHY_CFGA_DIG_CFG19_LSLINKDIVIDER(x)               (((x) & 0x1F) << 21)
#define BIT_MPHY_CFGA_DIG_CFG19_HSLINKDIVIDER(x)               (((x) & 0x1F) << 16)
#define BIT_MPHY_CFGA_DIG_CFG19_LSTXSCLKINV1                   BIT(15)
#define BIT_MPHY_CFGA_DIG_CFG19_LSTXSCLKINV0                   BIT(14)
#define BIT_MPHY_CFGA_DIG_CFG19_HSTXSCLKINV1                   BIT(13)
#define BIT_MPHY_CFGA_DIG_CFG19_HSTXSCLKINV0                   BIT(12)
#define BIT_MPHY_CFGA_DIG_CFG19_RXLINKSRCINV1                  BIT(11)
#define BIT_MPHY_CFGA_DIG_CFG19_RXLINKSRCINV0                  BIT(10)
#define BIT_MPHY_CFGA_DIG_CFG19_TXLINKSRCINV1                  BIT(9)
#define BIT_MPHY_CFGA_DIG_CFG19_TXLINKSRCINV0                  BIT(8)
#define BIT_MPHY_CFGA_DIG_CFG19_CB_RX_MODE(x)                  (((x) & 0xF) << 4)
#define BIT_MPHY_CFGA_DIG_CFG19_CB_TX_MODE(x)                  (((x) & 0xF))

/* REG_MPHY_CFGA_DIG_CFG20 */

#define BIT_MPHY_CFGA_DIG_CFG20_CB_RX_GLOBALHIBERN8            BIT(29)
#define BIT_MPHY_CFGA_DIG_CFG20_CB_TX_GLOBALHIBERN8            BIT(28)
#define BIT_MPHY_CFGA_DIG_CFG20_CB_TX_PWMGEAR(x)               (((x) & 0x7) << 24)
#define BIT_MPHY_CFGA_DIG_CFG20_RXOFSTCALENOVRVAL              BIT(21)
#define BIT_MPHY_CFGA_DIG_CFG20_RXOFSTCALENOVR                 BIT(20)
#define BIT_MPHY_CFGA_DIG_CFG20_DCOCALENABLEOVRVAL             BIT(19)
#define BIT_MPHY_CFGA_DIG_CFG20_DCOCALENABLEOVR                BIT(18)
#define BIT_MPHY_CFGA_DIG_CFG20_OFSTCLKDIV(x)                  (((x) & 0x3) << 16)
#define BIT_MPHY_CFGA_DIG_CFG20_PLLPRECHARGETIMER(x)           (((x) & 0x3) << 14)
#define BIT_MPHY_CFGA_DIG_CFG20_HSLINKDELAY(x)                 (((x) & 0x3) << 12)
#define BIT_MPHY_CFGA_DIG_CFG20_RXOFFSETCAL1DONEOVRVAL         BIT(11)
#define BIT_MPHY_CFGA_DIG_CFG20_RXOFFSETCAL0DONEOVRVAL         BIT(10)
#define BIT_MPHY_CFGA_DIG_CFG20_PLLLOCKDONEOVRVAL              BIT(9)
#define BIT_MPHY_CFGA_DIG_CFG20_DCOCALDONEOVRVAL               BIT(8)
#define BIT_MPHY_CFGA_DIG_CFG20_RXTERMCALDONEOVRVAL            BIT(7)
#define BIT_MPHY_CFGA_DIG_CFG20_TXTERMCALDONEOVRVAL            BIT(6)
#define BIT_MPHY_CFGA_DIG_CFG20_RXOFFSETCAL1DONEOVR            BIT(5)
#define BIT_MPHY_CFGA_DIG_CFG20_RXOFFSETCAL0DONEOVR            BIT(4)
#define BIT_MPHY_CFGA_DIG_CFG20_PLLLOCKDONEOVR                 BIT(3)
#define BIT_MPHY_CFGA_DIG_CFG20_DCOCALDONEOVR                  BIT(2)
#define BIT_MPHY_CFGA_DIG_CFG20_RXTERMCALDONEOVR               BIT(1)
#define BIT_MPHY_CFGA_DIG_CFG20_TXTERMCALDONEOVR               BIT(0)

/* REG_MPHY_CFGA_DIG_CFG21 */

#define BIT_MPHY_CFGA_DIG_CFG21_RX_CFGRXBIASLSSTBSEL(x)        (((x) & 0x3) << 30)
#define BIT_MPHY_CFGA_DIG_CFG21_RX_CFGRXBIASHSSTBSEL(x)        (((x) & 0x3) << 28)
#define BIT_MPHY_CFGA_DIG_CFG21_RX_REG_PREPARE_DELAY_SEL(x)    (((x) & 0xF) << 24)
#define BIT_MPHY_CFGA_DIG_CFG21_RX_CFGRESYNCEN                 BIT(23)
#define BIT_MPHY_CFGA_DIG_CFG21_RX_CHECKTYPE                   BIT(22)
#define BIT_MPHY_CFGA_DIG_CFG21_RX_CJTPATMODE                  BIT(21)
#define BIT_MPHY_CFGA_DIG_CFG21_RX_CRPATMODE                   BIT(20)
#define BIT_MPHY_CFGA_DIG_CFG21_RX_CUSTOMMODE                  BIT(19)
#define BIT_MPHY_CFGA_DIG_CFG21_RX_PRBS9MODE                   BIT(18)
#define BIT_MPHY_CFGA_DIG_CFG21_RX_ENTESTMODE                  BIT(17)
#define BIT_MPHY_CFGA_DIG_CFG21_RX_CFGMSBFIRST                 BIT(16)
#define BIT_MPHY_CFGA_DIG_CFG21_RX_BERT_BURST_MODE             BIT(12)
#define BIT_MPHY_CFGA_DIG_CFG21_RX_BIST_CMP_WIDTH(x)           (((x) & 0xF) << 8)
#define BIT_MPHY_CFGA_DIG_CFG21_RX_IGNORE_FSM                  BIT(7)
#define BIT_MPHY_CFGA_DIG_CFG21_RX_BIST_MODE                   BIT(6)
#define BIT_MPHY_CFGA_DIG_CFG21_RX_BIST_OBSEL(x)               (((x) & 0x3) << 4)
#define BIT_MPHY_CFGA_DIG_CFG21_RX_BIST_TYPE_SYMBOL(x)         (((x) & 0x3) << 2)
#define BIT_MPHY_CFGA_DIG_CFG21_RX_BIST_START                  BIT(1)
#define BIT_MPHY_CFGA_DIG_CFG21_RX_BIST_RESET                  BIT(0)

/* REG_MPHY_CFGA_DIG_CFG22 */

#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGRDYSEL_OP                BIT(30)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGRDYSEL                   BIT(29)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGMUTEAREAZ                BIT(28)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGLCC_IGNOREZ              BIT(27)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_PWMGEAR_KEEP                BIT(26)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGRTENOVR                  BIT(25)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGRTENVAL                  BIT(24)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGTESTPHASE(x)             (((x) & 0xF) << 20)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGCDRTESTEN                BIT(19)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGSYMBOLCLKEXTZ            BIT(18)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGH8EXITOUTSEL             BIT(17)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGSQENSEL                  BIT(16)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGRXLINKCLKEXTDIV          BIT(15)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGLINERSTDIVIDER(x)        (((x) & 0x3F) << 9)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGLINERSTDISABLE           BIT(8)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGTYPEI                    BIT(7)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGSQCTRL                   BIT(6)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGENABERGATINGZ            BIT(5)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGINVPOLARITY              BIT(4)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGH8EXITTYPE               BIT(3)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGWIDEIF(x)                (((x) & 0x3) << 1)
#define BIT_MPHY_CFGA_DIG_CFG22_RX_CFGINLNSHDWZ                BIT(0)

/* REG_MPHY_CFGA_DIG_CFG23 */

#define BIT_MPHY_CFGA_DIG_CFG23_RX_TESTSEQ7(x)                 (((x) & 0x3FF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG23_RX_TESTSEQ6(x)                 (((x) & 0x3FF))

/* REG_MPHY_CFGA_DIG_CFG24 */

#define BIT_MPHY_CFGA_DIG_CFG24_RX_TESTSEQ5(x)                 (((x) & 0x3FF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG24_RX_TESTSEQ4(x)                 (((x) & 0x3FF))

/* REG_MPHY_CFGA_DIG_CFG25 */

#define BIT_MPHY_CFGA_DIG_CFG25_RX_TESTSEQ3(x)                 (((x) & 0x3FF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG25_RX_TESTSEQ2(x)                 (((x) & 0x3FF))

/* REG_MPHY_CFGA_DIG_CFG26 */

#define BIT_MPHY_CFGA_DIG_CFG26_RX_TESTSEQ1(x)                 (((x) & 0x3FF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG26_RX_TESTSEQ0(x)                 (((x) & 0x3FF))

/* REG_MPHY_CFGA_DIG_CFG27 */

#define BIT_MPHY_CFGA_DIG_CFG27_RX_TESTSEQCYCLE7(x)            (((x) & 0x3FF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG27_RX_TESTSEQCYCLE6(x)            (((x) & 0x3FF))

/* REG_MPHY_CFGA_DIG_CFG28 */

#define BIT_MPHY_CFGA_DIG_CFG28_RX_TESTSEQCYCLE5(x)            (((x) & 0x3FF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG28_RX_TESTSEQCYCLE4(x)            (((x) & 0x3FF))

/* REG_MPHY_CFGA_DIG_CFG29 */

#define BIT_MPHY_CFGA_DIG_CFG29_RX_TESTSEQCYCLE3(x)            (((x) & 0x3FF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG29_RX_TESTSEQCYCLE2(x)            (((x) & 0x3FF))

/* REG_MPHY_CFGA_DIG_CFG30 */

#define BIT_MPHY_CFGA_DIG_CFG30_RX_TESTSEQCYCLE1(x)            (((x) & 0x3FF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG30_RX_TESTSEQCYCLE0(x)            (((x) & 0x3FF))

/* REG_MPHY_CFGA_DIG_CFG31 */

#define BIT_MPHY_CFGA_DIG_CFG31_RX_REG_R100_CNT_HS(x)          (((x) & 0x1F) << 25)
#define BIT_MPHY_CFGA_DIG_CFG31_RX_REG_R100_CNT_LS(x)          (((x) & 0x1F) << 20)
#define BIT_MPHY_CFGA_DIG_CFG31_RX_CFGLINERSTCOUNTER(x)        (((x) & 0x1FFFF))

/* REG_MPHY_CFGA_DIG_CFG32 */

#define BIT_MPHY_CFGA_DIG_CFG32_RX_CRREG_RXDETOFF              BIT(28)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_BYPDEBOUNCE                 BIT(27)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGRXCHOENOVR               BIT(26)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGRXDETCHOENOVR            BIT(25)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGRXDETECTENOVR            BIT(24)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGSQENOVR                  BIT(23)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGSQCHOENOVR               BIT(22)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGRXBIASLSENOVR            BIT(21)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGRXBIASHSENOVR            BIT(20)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGRXHSENOVR                BIT(19)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGRXLSENOVR                BIT(18)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGHSR100OVR                BIT(17)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGLSR100OVR                BIT(16)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGRXCHOENVAL               BIT(10)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGRXDETCHOENVAL            BIT(9)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGRXDETECTENVAL            BIT(8)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGSQENVAL                  BIT(7)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGSQCHOENVAL               BIT(6)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGRXBIASLSENVAL            BIT(5)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGRXBIASHSENVAL            BIT(4)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGRXHSENVAL                BIT(3)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGRXLSENVAL                BIT(2)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGHSR100VAL                BIT(1)
#define BIT_MPHY_CFGA_DIG_CFG32_RX_CFGLSR100VAL                BIT(0)

/* REG_MPHY_CFGA_DIG_CFG33 */

#define BIT_MPHY_CFGA_DIG_CFG33_RX_THRESDEBOUNCE(x)            (((x) & 0xFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG33_RX_CFGSQENABLEDELAY(x)         (((x) & 0xFFFF))

/* REG_MPHY_CFGA_DIG_CFG34 */

#define BIT_MPHY_CFGA_DIG_CFG34_TX_LINERSTOFST(x)              (((x) & 0xFF) << 20)
#define BIT_MPHY_CFGA_DIG_CFG34_TX_TACTIVATE(x)                (((x) & 0x1FFFF))

/* REG_MPHY_CFGA_DIG_CFG35 */

#define BIT_MPHY_CFGA_DIG_CFG35_TX_DITHERPRBSINI(x)            (((x) & 0xFF) << 24)
#define BIT_MPHY_CFGA_DIG_CFG35_TX_CUSTOMMODE                  BIT(18)
#define BIT_MPHY_CFGA_DIG_CFG35_TX_PRBS9MODE                   BIT(17)
#define BIT_MPHY_CFGA_DIG_CFG35_TX_ENTESTMODE                  BIT(16)
#define BIT_MPHY_CFGA_DIG_CFG35_TX_FIFOMODE                    BIT(15)
#define BIT_MPHY_CFGA_DIG_CFG35_TX_CJTPATMODE                  BIT(14)
#define BIT_MPHY_CFGA_DIG_CFG35_TX_CRPATMODE                   BIT(13)
#define BIT_MPHY_CFGA_DIG_CFG35_TX_SYNCLENCFG                  BIT(12)
#define BIT_MPHY_CFGA_DIG_CFG35_TX_DITHERINTEXTZ               BIT(11)
#define BIT_MPHY_CFGA_DIG_CFG35_TX_DITHEREXTVAL(x)             (((x) & 0x7) << 8)
#define BIT_MPHY_CFGA_DIG_CFG35_TX_CFGINLNSHDWZ                BIT(7)
#define BIT_MPHY_CFGA_DIG_CFG35_TX_CFGWIDEIF(x)                (((x) & 0x3) << 5)
#define BIT_MPHY_CFGA_DIG_CFG35_TX_CFGMSBFIRST                 BIT(4)
#define BIT_MPHY_CFGA_DIG_CFG35_TX_TGGLSINV                    BIT(3)
#define BIT_MPHY_CFGA_DIG_CFG35_TX_H8EXITTYPE                  BIT(2)
#define BIT_MPHY_CFGA_DIG_CFG35_TX_PRBSERR                     BIT(1)
#define BIT_MPHY_CFGA_DIG_CFG35_TX_CDRTESTEN                   BIT(0)

/* REG_MPHY_CFGA_DIG_CFG36 */

#define BIT_MPHY_CFGA_DIG_CFG36_TX_TLINERESETMIN(x)            (((x) & 0x1FFFF))

/* REG_MPHY_CFGA_DIG_CFG37 */

#define BIT_MPHY_CFGA_DIG_CFG37_TX_ENABLE_TMR(x)               (((x) & 0xFF) << 24)
#define BIT_MPHY_CFGA_DIG_CFG37_TX_LDO_TMR(x)                  (((x) & 0xFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG37_TX_BIST_AUTO_NUM(x)            (((x) & 0xFF) << 8)
#define BIT_MPHY_CFGA_DIG_CFG37_TX_IGNORE_FSM                  BIT(7)
#define BIT_MPHY_CFGA_DIG_CFG37_TX_BIST_TYPE_SYMBOL(x)         (((x) & 0x3) << 5)
#define BIT_MPHY_CFGA_DIG_CFG37_TX_BIST_MODE                   BIT(4)
#define BIT_MPHY_CFGA_DIG_CFG37_TX_BIST_LOOP                   BIT(3)
#define BIT_MPHY_CFGA_DIG_CFG37_TX_BIST_AUTO                   BIT(2)
#define BIT_MPHY_CFGA_DIG_CFG37_TX_BIST_START                  BIT(1)
#define BIT_MPHY_CFGA_DIG_CFG37_TX_BIST_RESET                  BIT(0)

/* REG_MPHY_CFGA_DIG_CFG38 */

#define BIT_MPHY_CFGA_DIG_CFG38_TX_TESTSEQ7(x)                 (((x) & 0x3FF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG38_TX_TESTSEQ6(x)                 (((x) & 0x3FF))

/* REG_MPHY_CFGA_DIG_CFG39 */

#define BIT_MPHY_CFGA_DIG_CFG39_TX_TESTSEQ5(x)                 (((x) & 0x3FF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG39_TX_TESTSEQ4(x)                 (((x) & 0x3FF))

/* REG_MPHY_CFGA_DIG_CFG40 */

#define BIT_MPHY_CFGA_DIG_CFG40_TX_TESTSEQ3(x)                 (((x) & 0x3FF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG40_TX_TESTSEQ2(x)                 (((x) & 0x3FF))

/* REG_MPHY_CFGA_DIG_CFG41 */

#define BIT_MPHY_CFGA_DIG_CFG41_TX_TESTSEQ1(x)                 (((x) & 0x3FF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG41_TX_TESTSEQ0(x)                 (((x) & 0x3FF))

/* REG_MPHY_CFGA_DIG_CFG42 */

#define BIT_MPHY_CFGA_DIG_CFG42_TX_TESTSEQCYCLE7(x)            (((x) & 0x3FF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG42_TX_TESTSEQCYCLE6(x)            (((x) & 0x3FF))

/* REG_MPHY_CFGA_DIG_CFG43 */

#define BIT_MPHY_CFGA_DIG_CFG43_TX_TESTSEQCYCLE5(x)            (((x) & 0x3FF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG43_TX_TESTSEQCYCLE4(x)            (((x) & 0x3FF))

/* REG_MPHY_CFGA_DIG_CFG44 */

#define BIT_MPHY_CFGA_DIG_CFG44_TX_TESTSEQCYCLE3(x)            (((x) & 0x3FF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG44_TX_TESTSEQCYCLE2(x)            (((x) & 0x3FF))

/* REG_MPHY_CFGA_DIG_CFG45 */

#define BIT_MPHY_CFGA_DIG_CFG45_TX_TESTSEQCYCLE1(x)            (((x) & 0x3FF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG45_TX_TESTSEQCYCLE0(x)            (((x) & 0x3FF))

/* REG_MPHY_CFGA_DIG_CFG46 */

#define BIT_MPHY_CFGA_DIG_CFG46_TX_ANALSTXENOVR                BIT(18)
#define BIT_MPHY_CFGA_DIG_CFG46_TX_ANAHSTXENOVR                BIT(17)
#define BIT_MPHY_CFGA_DIG_CFG46_TX_ANATXENOVR                  BIT(16)
#define BIT_MPHY_CFGA_DIG_CFG46_TX_ANALSTXENVAL                BIT(2)
#define BIT_MPHY_CFGA_DIG_CFG46_TX_ANAHSTXENVAL                BIT(1)
#define BIT_MPHY_CFGA_DIG_CFG46_TX_ANATXENVAL                  BIT(0)

/* REG_MPHY_CFGA_DIG_CFG47 */

#define BIT_MPHY_CFGA_DIG_CFG47_TX_PREDRV_TMR(x)               (((x) & 0x1F) << 24)
#define BIT_MPHY_CFGA_DIG_CFG47_TX_PREDRV_HS_IDC_EN_OVR        BIT(22)
#define BIT_MPHY_CFGA_DIG_CFG47_TX_PREDRV_HS_IDC_EN            BIT(21)
#define BIT_MPHY_CFGA_DIG_CFG47_TX_PREDRV_SEL                  BIT(20)
#define BIT_MPHY_CFGA_DIG_CFG47_TX_PREDRV_HS_IDC(x)            (((x) & 0x7) << 17)
#define BIT_MPHY_CFGA_DIG_CFG47_TX_FORCE_HS_IDC_EN             BIT(16)
#define BIT_MPHY_CFGA_DIG_CFG47_TX_SLEWRATE_SEL                BIT(13)
#define BIT_MPHY_CFGA_DIG_CFG47_TX_SR_CONFIG                   BIT(12)
#define BIT_MPHY_CFGA_DIG_CFG47_TX_SR_SEL                      BIT(11)
#define BIT_MPHY_CFGA_DIG_CFG47_TX_TXSR(x)                     (((x) & 0x7) << 8)
#define BIT_MPHY_CFGA_DIG_CFG47_TX_EQ_SEL                      BIT(5)
#define BIT_MPHY_CFGA_DIG_CFG47_TX_HALF_CELL_EN                BIT(4)
#define BIT_MPHY_CFGA_DIG_CFG47_TX_EMPHASIS_HALF               BIT(3)
#define BIT_MPHY_CFGA_DIG_CFG47_TX_EMPHASIS(x)                 (((x) & 0x7))

/* REG_MPHY_CFGA_DIG_CFG48 */

#define BIT_MPHY_CFGA_DIG_CFG48_RX_OBSERVECTRL_0(x)            (((x) & 0xFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG48_TX_OBSERVECTRL_0(x)            (((x) & 0xFF) << 8)
#define BIT_MPHY_CFGA_DIG_CFG48_CB_OBSERVECTRL(x)              (((x) & 0xFF))

/* REG_MPHY_CFGA_DIG_CFG49 */

#define BIT_MPHY_CFGA_DIG_CFG49_RX_STEP1_CFG_0_G1(x)           (((x) & 0xFF) << 24)
#define BIT_MPHY_CFGA_DIG_CFG49_RX_STEP2_CFG_0_G1(x)           (((x) & 0xFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG49_RX_STEP3_CFG_0_G1(x)           (((x) & 0xFF) << 8)
#define BIT_MPHY_CFGA_DIG_CFG49_RX_STEP4_CFG_0_G1(x)           (((x) & 0xFF))

/* REG_MPHY_CFGA_DIG_CFG50 */

#define BIT_MPHY_CFGA_DIG_CFG50_RX_STEP1_CFG_0_G2(x)           (((x) & 0xFF) << 24)
#define BIT_MPHY_CFGA_DIG_CFG50_RX_STEP2_CFG_0_G2(x)           (((x) & 0xFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG50_RX_STEP3_CFG_0_G2(x)           (((x) & 0xFF) << 8)
#define BIT_MPHY_CFGA_DIG_CFG50_RX_STEP4_CFG_0_G2(x)           (((x) & 0xFF))

/* REG_MPHY_CFGA_DIG_CFG51 */

#define BIT_MPHY_CFGA_DIG_CFG51_RX_STEP1_CFG_0_G3(x)           (((x) & 0xFF) << 24)
#define BIT_MPHY_CFGA_DIG_CFG51_RX_STEP2_CFG_0_G3(x)           (((x) & 0xFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG51_RX_STEP3_CFG_0_G3(x)           (((x) & 0xFF) << 8)
#define BIT_MPHY_CFGA_DIG_CFG51_RX_STEP4_CFG_0_G3(x)           (((x) & 0xFF))

/* REG_MPHY_CFGA_DIG_CFG52 */

#define BIT_MPHY_CFGA_DIG_CFG52_RX_CDR_MODE_CTRL_0_G3          BIT(23)
#define BIT_MPHY_CFGA_DIG_CFG52_RX_EN_DIV2_0_G3                BIT(22)
#define BIT_MPHY_CFGA_DIG_CFG52_RX_PEAK2G5_0_G3                BIT(21)
#define BIT_MPHY_CFGA_DIG_CFG52_RX_LEQ_INIT_0_G3(x)            (((x) & 0x1F) << 16)
#define BIT_MPHY_CFGA_DIG_CFG52_RX_CDR_MODE_CTRL_0_G2          BIT(15)
#define BIT_MPHY_CFGA_DIG_CFG52_RX_EN_DIV2_0_G2                BIT(14)
#define BIT_MPHY_CFGA_DIG_CFG52_RX_PEAK2G5_0_G2                BIT(13)
#define BIT_MPHY_CFGA_DIG_CFG52_RX_LEQ_INIT_0_G2(x)            (((x) & 0x1F) << 8)
#define BIT_MPHY_CFGA_DIG_CFG52_RX_CDR_MODE_CTRL_0_G1          BIT(7)
#define BIT_MPHY_CFGA_DIG_CFG52_RX_EN_DIV2_0_G1                BIT(6)
#define BIT_MPHY_CFGA_DIG_CFG52_RX_PEAK2G5_0_G1                BIT(5)
#define BIT_MPHY_CFGA_DIG_CFG52_RX_LEQ_INIT_0_G1(x)            (((x) & 0x1F))

/* REG_MPHY_CFGA_DIG_CFG53 */

#define BIT_MPHY_CFGA_DIG_CFG53_CB_NS_G3B(x)                   (((x) & 0xFF) << 24)
#define BIT_MPHY_CFGA_DIG_CFG53_CB_NS_G3A(x)                   (((x) & 0xFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG53_TX_TXSR_0_G1(x)                (((x) & 0xF) << 12)
#define BIT_MPHY_CFGA_DIG_CFG53_TX_SR_SEL_0_G3                 BIT(11)
#define BIT_MPHY_CFGA_DIG_CFG53_TX_SR_SEL_0_G2                 BIT(10)
#define BIT_MPHY_CFGA_DIG_CFG53_TX_SR_SEL_0_G1                 BIT(9)
#define BIT_MPHY_CFGA_DIG_CFG53_TX_PREDRV_HS_IDC_0_G3(x)       (((x) & 0x7) << 6)
#define BIT_MPHY_CFGA_DIG_CFG53_TX_PREDRV_HS_IDC_0_G2(x)       (((x) & 0x7) << 3)
#define BIT_MPHY_CFGA_DIG_CFG53_TX_PREDRV_HS_IDC_0_G1(x)       (((x) & 0x7))

/* REG_MPHY_CFGA_DIG_CFG54 */

#define BIT_MPHY_CFGA_DIG_CFG54_TX_TXSR_0_G3(x)                (((x) & 0xF) << 28)
#define BIT_MPHY_CFGA_DIG_CFG54_TX_TXSR_0_G2(x)                (((x) & 0xF) << 24)
#define BIT_MPHY_CFGA_DIG_CFG54_CB_LPF_G3(x)                   (((x) & 0x3) << 22)
#define BIT_MPHY_CFGA_DIG_CFG54_CB_PRESEL_G3(x)                (((x) & 0x3) << 20)
#define BIT_MPHY_CFGA_DIG_CFG54_CB_VCOBAND_G3                  BIT(19)
#define BIT_MPHY_CFGA_DIG_CFG54_CB_HSG1_G3                     BIT(18)
#define BIT_MPHY_CFGA_DIG_CFG54_CB_CP_G3(x)                    (((x) & 0x3) << 16)
#define BIT_MPHY_CFGA_DIG_CFG54_CB_LPF_G2(x)                   (((x) & 0x3) << 14)
#define BIT_MPHY_CFGA_DIG_CFG54_CB_PRESEL_G2(x)                (((x) & 0x3) << 12)
#define BIT_MPHY_CFGA_DIG_CFG54_CB_VCOBAND_G2                  BIT(11)
#define BIT_MPHY_CFGA_DIG_CFG54_CB_HSG1_G2                     BIT(10)
#define BIT_MPHY_CFGA_DIG_CFG54_CB_CP_G2(x)                    (((x) & 0x3) << 8)
#define BIT_MPHY_CFGA_DIG_CFG54_CB_LPF_G1(x)                   (((x) & 0x3) << 6)
#define BIT_MPHY_CFGA_DIG_CFG54_CB_PRESEL_G1(x)                (((x) & 0x3) << 4)
#define BIT_MPHY_CFGA_DIG_CFG54_CB_VCOBAND_G1                  BIT(3)
#define BIT_MPHY_CFGA_DIG_CFG54_CB_HSG1_G1                     BIT(2)
#define BIT_MPHY_CFGA_DIG_CFG54_CB_CP_G1(x)                    (((x) & 0x3))

/* REG_MPHY_CFGA_DIG_CFG55 */

#define BIT_MPHY_CFGA_DIG_CFG55_CB_NS_G2B(x)                   (((x) & 0xFF) << 24)
#define BIT_MPHY_CFGA_DIG_CFG55_CB_NS_G2A(x)                   (((x) & 0xFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG55_CB_NS_G1B(x)                   (((x) & 0xFF) << 8)
#define BIT_MPHY_CFGA_DIG_CFG55_CB_NS_G1A(x)                   (((x) & 0xFF))

/* REG_MPHY_CFGA_DIG_CFG56 */

#define BIT_MPHY_CFGA_DIG_CFG56_RX_STEP4_CYCLE_0_G1(x)         (((x) & 0xFFFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG56_RX_STEP3_CYCLE_0_G1(x)         (((x) & 0xFFFF))

/* REG_MPHY_CFGA_DIG_CFG57 */

#define BIT_MPHY_CFGA_DIG_CFG57_RX_STEP2_CYCLE_0_G1(x)         (((x) & 0xFFFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG57_RX_STEP1_CYCLE_0_G1(x)         (((x) & 0xFFFF))

/* REG_MPHY_CFGA_DIG_CFG58 */

#define BIT_MPHY_CFGA_DIG_CFG58_RX_STEP4_CYCLE_0_G2(x)         (((x) & 0xFFFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG58_RX_STEP3_CYCLE_0_G2(x)         (((x) & 0xFFFF))

/* REG_MPHY_CFGA_DIG_CFG59 */

#define BIT_MPHY_CFGA_DIG_CFG59_RX_STEP2_CYCLE_0_G2(x)         (((x) & 0xFFFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG59_RX_STEP1_CYCLE_0_G2(x)         (((x) & 0xFFFF))

/* REG_MPHY_CFGA_DIG_CFG60 */

#define BIT_MPHY_CFGA_DIG_CFG60_RX_STEP4_CYCLE_0_G3(x)         (((x) & 0xFFFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG60_RX_STEP3_CYCLE_0_G3(x)         (((x) & 0xFFFF))

/* REG_MPHY_CFGA_DIG_CFG61 */

#define BIT_MPHY_CFGA_DIG_CFG61_RX_STEP2_CYCLE_0_G3(x)         (((x) & 0xFFFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG61_RX_STEP1_CYCLE_0_G3(x)         (((x) & 0xFFFF))

/* REG_MPHY_CFGA_DIG_CFG62 */

#define BIT_MPHY_CFGA_DIG_CFG62_DCO_CAL_RESULT(x)              (((x) & 0xFF) << 24)
#define BIT_MPHY_CFGA_DIG_CFG62_PLL_BIST_CNT(x)                (((x) & 0xFFFF) << 8)
#define BIT_MPHY_CFGA_DIG_CFG62_PLL_BIST_EN                    BIT(4)
#define BIT_MPHY_CFGA_DIG_CFG62_RX_ATE_COMP_BURST              BIT(3)
#define BIT_MPHY_CFGA_DIG_CFG62_TX_BIST_ATE                    BIT(2)
#define BIT_MPHY_CFGA_DIG_CFG62_REG_REFCLK_SEL(x)              (((x) & 0x3))

/* REG_MPHY_CFGA_DIG_CFG63 */

#define BIT_MPHY_CFGA_DIG_CFG63_TX_BIST_IDLE_FREQ(x)           (((x) & 0xFF) << 24)
#define BIT_MPHY_CFGA_DIG_CFG63_TX_BIST_IDLE_LEN(x)            (((x) & 0xFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG63_TX_BIST_BURST_LEN(x)           (((x) & 0xFF) << 8)
#define BIT_MPHY_CFGA_DIG_CFG63_TX_BIST_BURST_NUM(x)           (((x) & 0xFF))

/* REG_MPHY_CFGA_DIG_CFG64 */

#define BIT_MPHY_CFGA_DIG_CFG64_PLL_BIST_DELTA_CNT(x)          (((x) & 0xF) << 28)
#define BIT_MPHY_CFGA_DIG_CFG64_PLL_BIST_REF_CNT(x)            (((x) & 0xFFF) << 16)
#define BIT_MPHY_CFGA_DIG_CFG64_PLL_BIST_EXP_CNT(x)            (((x) & 0xFFFF))

/* REG_MPHY_CFGA_DIG_CFG65 */

#define BIT_MPHY_CFGA_DIG_CFG65_DCO_CNT_VALUE(x)               (((x) & 0x1FF) << 8)
#define BIT_MPHY_CFGA_DIG_CFG65_READ_COEF_OUT(x)               (((x) & 0xFF))

/* REG_MPHY_CFGA_DIG_CFG66 */

#define BIT_MPHY_CFGA_DIG_CFG66_PLL_BIST_OK_LATCH              BIT(16)
#define BIT_MPHY_CFGA_DIG_CFG66_PLL_BIST_CNT_LATCH(x)          (((x) & 0xFFFF))


#endif /* MPHY_CFGA_H */


