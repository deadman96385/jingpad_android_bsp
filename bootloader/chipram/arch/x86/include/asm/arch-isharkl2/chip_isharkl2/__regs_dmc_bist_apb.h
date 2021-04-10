/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _DMC_BIST_APB_REG_H
#define _DMC_BIST_APB_REG_H

#define CTL_BASE_DMC_BIST_APB	SPRD_DMC_BIST_APB_BASE


#define REG_DMC_BIST_APB_RF_BIST_CTRL                    ( CTL_BASE_DMC_BIST_APB + 0x0000 )
#define REG_DMC_BIST_APB_RF_BIST_TRANS_NUM               ( CTL_BASE_DMC_BIST_APB + 0x0004 )
#define REG_DMC_BIST_APB_RF_BIST_START_ADDR              ( CTL_BASE_DMC_BIST_APB + 0x0008 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_MASK               ( CTL_BASE_DMC_BIST_APB + 0x000C )
#define REG_DMC_BIST_APB_RF_BIST_SIPI_DATA_00            ( CTL_BASE_DMC_BIST_APB + 0x0010 )
#define REG_DMC_BIST_APB_RF_BIST_SIPI_DATA_01            ( CTL_BASE_DMC_BIST_APB + 0x0014 )
#define REG_DMC_BIST_APB_RF_BIST_SIPI_DATA_02            ( CTL_BASE_DMC_BIST_APB + 0x0018 )
#define REG_DMC_BIST_APB_RF_BIST_SIPI_DATA_03            ( CTL_BASE_DMC_BIST_APB + 0x001C )
#define REG_DMC_BIST_APB_RF_BIST_SIPI_DATA_04            ( CTL_BASE_DMC_BIST_APB + 0x0020 )
#define REG_DMC_BIST_APB_RF_BIST_SIPI_DATA_05            ( CTL_BASE_DMC_BIST_APB + 0x0024 )
#define REG_DMC_BIST_APB_RF_BIST_SIPI_BIT_PATTERN_0      ( CTL_BASE_DMC_BIST_APB + 0x0028 )
#define REG_DMC_BIST_APB_RF_BIST_SIPI_BIT_PATTERN_1      ( CTL_BASE_DMC_BIST_APB + 0x002C )
#define REG_DMC_BIST_APB_RF_BIST_DATA_00_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0030 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_01_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0034 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_02_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0038 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_03_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x003C )
#define REG_DMC_BIST_APB_RF_BIST_DATA_04_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0040 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_05_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0044 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_06_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0048 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_07_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x004C )
#define REG_DMC_BIST_APB_RF_BIST_DATA_08_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0050 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_09_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0054 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_10_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0058 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_11_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x005C )
#define REG_DMC_BIST_APB_RF_BIST_DATA_12_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0060 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_13_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0064 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_14_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0068 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_15_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x006C )
#define REG_DMC_BIST_APB_RF_BIST_DATA_16_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0070 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_17_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0074 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_18_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0078 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_19_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x007C )
#define REG_DMC_BIST_APB_RF_BIST_DATA_20_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0080 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_21_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0084 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_22_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0088 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_23_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x008C )
#define REG_DMC_BIST_APB_RF_BIST_DATA_24_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0090 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_25_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0094 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_26_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x0098 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_27_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x009C )
#define REG_DMC_BIST_APB_RF_BIST_DATA_28_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x00A0 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_29_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x00A4 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_30_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x00A8 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_31_PATTERN         ( CTL_BASE_DMC_BIST_APB + 0x00AC )
#define REG_DMC_BIST_APB_RF_BIST_RESULT                  ( CTL_BASE_DMC_BIST_APB + 0x00B0 )
#define REG_DMC_BIST_APB_RF_BIST_FAIL_ADDR               ( CTL_BASE_DMC_BIST_APB + 0x00B4 )
#define REG_DMC_BIST_APB_RF_BIST_FAIL_DATA_0             ( CTL_BASE_DMC_BIST_APB + 0x00B8 )
#define REG_DMC_BIST_APB_RF_BIST_FAIL_DATA_1             ( CTL_BASE_DMC_BIST_APB + 0x00BC )
#define REG_DMC_BIST_APB_RF_BIST_FAIL_DATA_2             ( CTL_BASE_DMC_BIST_APB + 0x00C0 )
#define REG_DMC_BIST_APB_RF_BIST_FAIL_DATA_3             ( CTL_BASE_DMC_BIST_APB + 0x00C4 )
#define REG_DMC_BIST_APB_RF_LFSR_POLY                    ( CTL_BASE_DMC_BIST_APB + 0x00C8 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_LFSR_SEED_L0       ( CTL_BASE_DMC_BIST_APB + 0x00CC )
#define REG_DMC_BIST_APB_RF_BIST_DATA_LFSR_SEED_L1       ( CTL_BASE_DMC_BIST_APB + 0x00D0 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_LFSR_SEED_H0       ( CTL_BASE_DMC_BIST_APB + 0x00D4 )
#define REG_DMC_BIST_APB_RF_BIST_DATA_LFSR_SEED_H1       ( CTL_BASE_DMC_BIST_APB + 0x00D8 )

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_CTRL
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_CTRL_RF_BIST_DATA_SIZE(x)                                            (((x) & 0x3) << 11)
#define BIT_DMC_BIST_APB_RF_BIST_CTRL_RF_BIST_BURST_LENGTH(x)                                         (((x) & 0xF) << 7)
#define BIT_DMC_BIST_APB_RF_BIST_CTRL_RF_BIST_DATA_PATTERN_MODE(x)                                    (((x) & 0x3) << 5)
#define BIT_DMC_BIST_APB_RF_BIST_CTRL_RF_BIST_MODE(x)                                                 (((x) & 0x3) << 3)
#define BIT_DMC_BIST_APB_RF_BIST_CTRL_RF_BIST_CLEAR                                                   BIT(2)
#define BIT_DMC_BIST_APB_RF_BIST_CTRL_RF_BIST_START                                                   BIT(1)
#define BIT_DMC_BIST_APB_RF_BIST_CTRL_RF_BIST_ENABLE                                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_TRANS_NUM
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_TRANS_NUM_RF_BIST_TRANS_NUM(x)                                       (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_START_ADDR
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_START_ADDR_RF_BIST_START_ADDR(x)                                     (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_MASK
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_MASK_RF_BIST_DATA_MASK(x)                                       (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_SIPI_DATA_00
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_SIPI_DATA_00_RF_BIST_SIPI_DATA_00(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_SIPI_DATA_01
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_SIPI_DATA_01_RF_BIST_SIPI_DATA_01(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_SIPI_DATA_02
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_SIPI_DATA_02_RF_BIST_SIPI_DATA_02(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_SIPI_DATA_03
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_SIPI_DATA_03_RF_BIST_SIPI_DATA_03(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_SIPI_DATA_04
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_SIPI_DATA_04_RF_BIST_SIPI_DATA_04(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_SIPI_DATA_05
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_SIPI_DATA_05_RF_BIST_SIPI_DATA_05(x)                                 (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_SIPI_BIT_PATTERN_0
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_SIPI_BIT_PATTERN_0_RF_BIST_SIPI_BIT_PATTERN_0(x)                     (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_SIPI_BIT_PATTERN_1
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_SIPI_BIT_PATTERN_1_RF_BIST_SIPI_BIT_PATTERN_1(x)                     (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_00_PATTERN
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_00_PATTERN_RF_BIST_DATA_00_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_01_PATTERN
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_01_PATTERN_RF_BIST_DATA_01_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_02_PATTERN
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_02_PATTERN_RF_BIST_DATA_02_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_03_PATTERN
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_03_PATTERN_RF_BIST_DATA_03_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_04_PATTERN
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_04_PATTERN_RF_BIST_DATA_04_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_05_PATTERN
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_05_PATTERN_RF_BIST_DATA_05_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_06_PATTERN
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_06_PATTERN_RF_BIST_DATA_06_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_07_PATTERN
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_07_PATTERN_RF_BIST_DATA_07_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_08_PATTERN
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_08_PATTERN_RF_BIST_DATA_08_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_09_PATTERN
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_09_PATTERN_RF_BIST_DATA_09_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_10_PATTERN
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_10_PATTERN_RF_BIST_DATA_10_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_11_PATTERN
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_11_PATTERN_RF_BIST_DATA_11_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_12_PATTERN
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_12_PATTERN_RF_BIST_DATA_12_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_13_PATTERN
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_13_PATTERN_RF_BIST_DATA_13_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_14_PATTERN
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_14_PATTERN_RF_BIST_DATA_14_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_15_PATTERN
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_15_PATTERN_RF_BIST_DATA_15_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_16_PATTERN
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_16_PATTERN_RF_BIST_DATA_16_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_17_PATTERN
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_17_PATTERN_RF_BIST_DATA_17_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_18_PATTERN
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_18_PATTERN_RF_BIST_DATA_18_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_19_PATTERN
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_19_PATTERN_RF_BIST_DATA_19_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_20_PATTERN
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_20_PATTERN_RF_BIST_DATA_20_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_21_PATTERN
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_21_PATTERN_RF_BIST_DATA_21_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_22_PATTERN
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_22_PATTERN_RF_BIST_DATA_22_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_23_PATTERN
// Register Offset : 0x008C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_23_PATTERN_RF_BIST_DATA_23_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_24_PATTERN
// Register Offset : 0x0090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_24_PATTERN_RF_BIST_DATA_24_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_25_PATTERN
// Register Offset : 0x0094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_25_PATTERN_RF_BIST_DATA_25_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_26_PATTERN
// Register Offset : 0x0098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_26_PATTERN_RF_BIST_DATA_26_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_27_PATTERN
// Register Offset : 0x009C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_27_PATTERN_RF_BIST_DATA_27_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_28_PATTERN
// Register Offset : 0x00A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_28_PATTERN_RF_BIST_DATA_28_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_29_PATTERN
// Register Offset : 0x00A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_29_PATTERN_RF_BIST_DATA_29_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_30_PATTERN
// Register Offset : 0x00A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_30_PATTERN_RF_BIST_DATA_30_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_31_PATTERN
// Register Offset : 0x00AC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_31_PATTERN_RF_BIST_DATA_31_PATTERN(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_RESULT
// Register Offset : 0x00B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_RESULT_RF_BIST_FINISH_FLAG                                           BIT(1)
#define BIT_DMC_BIST_APB_RF_BIST_RESULT_RF_BIST_FAIL_FLAG                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_FAIL_ADDR
// Register Offset : 0x00B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_FAIL_ADDR_RF_BIST_FAIL_ADDR(x)                                       (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_FAIL_DATA_0
// Register Offset : 0x00B8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_FAIL_DATA_0_RF_BIST_FAIL_DATA_0(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_FAIL_DATA_1
// Register Offset : 0x00BC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_FAIL_DATA_1_RF_BIST_FAIL_DATA_1(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_FAIL_DATA_2
// Register Offset : 0x00C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_FAIL_DATA_2_RF_BIST_FAIL_DATA_2(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_FAIL_DATA_3
// Register Offset : 0x00C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_FAIL_DATA_3_RF_BIST_FAIL_DATA_3(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_LFSR_POLY
// Register Offset : 0x00C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_LFSR_POLY_RF_LFSR_POLY_NEG(x)                                             (((x) & 0xFFFF) << 16)
#define BIT_DMC_BIST_APB_RF_LFSR_POLY_RF_LFSR_POLY_POS(x)                                             (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_LFSR_SEED_L0
// Register Offset : 0x00CC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_LFSR_SEED_L0_RF_BIST_DATA_LFSR_SEED_L0(x)                       (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_LFSR_SEED_L1
// Register Offset : 0x00D0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_LFSR_SEED_L1_RF_BIST_DATA_LFSR_SEED_L1(x)                       (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_LFSR_SEED_H0
// Register Offset : 0x00D4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_LFSR_SEED_H0_RF_BIST_DATA_LFSR_SEED_H0(x)                       (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DMC_BIST_APB_RF_BIST_DATA_LFSR_SEED_H1
// Register Offset : 0x00D8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DMC_BIST_APB_RF_BIST_DATA_LFSR_SEED_H1_RF_BIST_DATA_LFSR_SEED_H1(x)                       (((x) & 0xFFFFFFFF))


#endif // _DMC_BIST_APB_REG_H
