/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _BASEIA_DVFS_REG_H
#define _BASEIA_DVFS_REG_H

#define CTL_BASE_BASEIA_DVFS SPRD_BIA_FREQ_BASE


#define REG_BASEIA_DVFS_BIA_DVFS_CTRL               ( CTL_BASE_BASEIA_DVFS + 0x0000 )
#define REG_BASEIA_DVFS_BIA_DVFS_WAIT_TIME0         ( CTL_BASE_BASEIA_DVFS + 0x0004 )
#define REG_BASEIA_DVFS_BIA_DVFS_WAIT_TIME1         ( CTL_BASE_BASEIA_DVFS + 0x0008 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE0_CTL         ( CTL_BASE_BASEIA_DVFS + 0x0010 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE0_CAL         ( CTL_BASE_BASEIA_DVFS + 0x0014 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE4_CTL         ( CTL_BASE_BASEIA_DVFS + 0x0018 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE4_CAL         ( CTL_BASE_BASEIA_DVFS + 0x001C )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE8_CTL         ( CTL_BASE_BASEIA_DVFS + 0x0020 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE8_CAL         ( CTL_BASE_BASEIA_DVFS + 0x0024 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE10_CTL        ( CTL_BASE_BASEIA_DVFS + 0x0028 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE10_CAL        ( CTL_BASE_BASEIA_DVFS + 0x002C )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE12_CTL        ( CTL_BASE_BASEIA_DVFS + 0x0030 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE12_CAL        ( CTL_BASE_BASEIA_DVFS + 0x0034 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE14_CTL        ( CTL_BASE_BASEIA_DVFS + 0x0038 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE14_CAL        ( CTL_BASE_BASEIA_DVFS + 0x003C )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE16_CTL        ( CTL_BASE_BASEIA_DVFS + 0x0040 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE16_CAL        ( CTL_BASE_BASEIA_DVFS + 0x0044 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE18_CTL        ( CTL_BASE_BASEIA_DVFS + 0x0048 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE18_CAL        ( CTL_BASE_BASEIA_DVFS + 0x004C )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE20_CTL        ( CTL_BASE_BASEIA_DVFS + 0x0050 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE20_CAL        ( CTL_BASE_BASEIA_DVFS + 0x0054 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE22_CTL        ( CTL_BASE_BASEIA_DVFS + 0x0058 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE22_CAL        ( CTL_BASE_BASEIA_DVFS + 0x005C )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE24_CTL        ( CTL_BASE_BASEIA_DVFS + 0x0060 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE24_CAL        ( CTL_BASE_BASEIA_DVFS + 0x0064 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE26_CTL        ( CTL_BASE_BASEIA_DVFS + 0x0068 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE26_CAL        ( CTL_BASE_BASEIA_DVFS + 0x006C )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE28_CTL        ( CTL_BASE_BASEIA_DVFS + 0x0070 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE28_CAL        ( CTL_BASE_BASEIA_DVFS + 0x0074 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE30_CTL        ( CTL_BASE_BASEIA_DVFS + 0x0078 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE30_CAL        ( CTL_BASE_BASEIA_DVFS + 0x007C )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE32_CTL        ( CTL_BASE_BASEIA_DVFS + 0x0080 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE32_CAL        ( CTL_BASE_BASEIA_DVFS + 0x0084 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE_DEF_CTL      ( CTL_BASE_BASEIA_DVFS + 0x0088 )
#define REG_BASEIA_DVFS_BIA_DVFS_TABLE_DEF_CAL      ( CTL_BASE_BASEIA_DVFS + 0x008C )
#define REG_BASEIA_DVFS_BIA_DVFS_DEBUG_CODE         ( CTL_BASE_BASEIA_DVFS + 0x00A0 )
#define REG_BASEIA_DVFS_BIA_DVFS_DEBUG_BUS          ( CTL_BASE_BASEIA_DVFS + 0x00A4 )
#define REG_BASEIA_DVFS_BIA_DVFS_DUMMY              ( CTL_BASE_BASEIA_DVFS + 0x00A8 )
#define REG_BASEIA_DVFS_BIA_DVFS_INT_EN             ( CTL_BASE_BASEIA_DVFS + 0x00C0 )
#define REG_BASEIA_DVFS_BIA_DVFS_INT_CLR            ( CTL_BASE_BASEIA_DVFS + 0x00C4 )
#define REG_BASEIA_DVFS_BIA_DVFS_INT_SET            ( CTL_BASE_BASEIA_DVFS + 0x00C8 )
#define REG_BASEIA_DVFS_BIA_DVFS_INT_RAW            ( CTL_BASE_BASEIA_DVFS + 0x00CC )
#define REG_BASEIA_DVFS_BIA_DVFS_INT                ( CTL_BASE_BASEIA_DVFS + 0x00D0 )

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_CTRL
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_CPUCLK_LOCK_PHASE                                BIT(21)
#define BIT_BASEIA_DVFS_DVFS_TABLE_LOCK                                  BIT(20)
#define BIT_BASEIA_DVFS_CTL_DIS2EN_NO_WAIT                               BIT(19)
#define BIT_BASEIA_DVFS_CTL_RELOCK_REQ_SEL                               BIT(18)
#define BIT_BASEIA_DVFS_PLL01_EN_SIMULT                                  BIT(17)
#define BIT_BASEIA_DVFS_CTL_WAKEUP_TIMING                                BIT(16)
#define BIT_BASEIA_DVFS_CPUCLK0_FREQ_4_SEL(x)                            (((x) & 0x3) << 14)
#define BIT_BASEIA_DVFS_CPUCLK0_FREQ_DEF_SEL(x)                          (((x) & 0x3) << 12)
#define BIT_BASEIA_DVFS_CPUCLK1_FREQ_4_SEL(x)                            (((x) & 0x3) << 10)
#define BIT_BASEIA_DVFS_CPUCLK1_FREQ_DEF_SEL(x)                          (((x) & 0x3) << 8)
#define BIT_BASEIA_DVFS_TABLE_MODE(x)                                    (((x) & 0x3) << 6)
#define BIT_BASEIA_DVFS_MASK_MODE                                        BIT(5)
#define BIT_BASEIA_DVFS_CTL_PLL_NO_PD                                    BIT(4)
#define BIT_BASEIA_DVFS_BIA_DVFS_RESET                                   BIT(3)
#define BIT_BASEIA_DVFS_CTL_DVFS_USER_SET                                BIT(2)
#define BIT_BASEIA_DVFS_CTL_REFPLL_SYNTHLOCK_DONT_CARE                   BIT(1)
#define BIT_BASEIA_DVFS_CTL_SYNTHLOCK_DONT_CARE                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_WAIT_TIME0
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_REQ_DELAY_CNT_NUM(x)                             (((x) & 0xFF) << 24)
#define BIT_BASEIA_DVFS_DOING_DELAY_CNT_NUM(x)                           (((x) & 0xFF) << 16)
#define BIT_BASEIA_DVFS_CAL_DELAY_CNT_NUM(x)                             (((x) & 0xFF) << 8)

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_WAIT_TIME1
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_PLL_DISCONNECT4_NUM(x)                           (((x) & 0xFF) << 24)
#define BIT_BASEIA_DVFS_PLL_DISCONNECT0_NUM(x)                           (((x) & 0xFF) << 16)
#define BIT_BASEIA_DVFS_PLL_PWRON_INTERVAL(x)                            (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_LOCK_DELAY_CNT_NUM(x)                            (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE0_CTL
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_0_CODE(x)                               (((x) & 0x3F) << 24)
#define BIT_BASEIA_DVFS_BIA_FREQ_0_CLKSLICE0_ENABLE                      BIT(22)
#define BIT_BASEIA_DVFS_BIA_FREQ_0_REFDIV(x)                             (((x) & 0x3F) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_0_MDIV(x)                               (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_0_CLKSLICE0_DIV(x)                      (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE0_CAL
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_0_FASTREF_EN                            BIT(21)
#define BIT_BASEIA_DVFS_BIA_FREQ_0_FEFB_EN                               BIT(20)
#define BIT_BASEIA_DVFS_BIA_FREQ_0_MODDIV(x)                             (((x) & 0xF) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_0_CALVCOMEASCOUNT(x)                    (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_0_CALVCOHSCOUNT(x)                      (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE4_CTL
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_4_CODE(x)                               (((x) & 0x3F) << 24)
#define BIT_BASEIA_DVFS_BIA_FREQ_4_CLKSLICE0_ENABLE                      BIT(22)
#define BIT_BASEIA_DVFS_BIA_FREQ_4_REFDIV(x)                             (((x) & 0x3F) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_4_MDIV(x)                               (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_4_CLKSLICE0_DIV(x)                      (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE4_CAL
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_4_FASTREF_EN                            BIT(21)
#define BIT_BASEIA_DVFS_BIA_FREQ_4_FEFB_EN                               BIT(20)
#define BIT_BASEIA_DVFS_BIA_FREQ_4_MODDIV(x)                             (((x) & 0xF) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_4_CALVCOMEASCOUNT(x)                    (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_4_CALVCOHSCOUNT(x)                      (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE8_CTL
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_8_CODE(x)                               (((x) & 0x3F) << 24)
#define BIT_BASEIA_DVFS_BIA_FREQ_8_CLKSLICE0_ENABLE                      BIT(22)
#define BIT_BASEIA_DVFS_BIA_FREQ_8_REFDIV(x)                             (((x) & 0x3F) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_8_MDIV(x)                               (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_8_CLKSLICE0_DIV(x)                      (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE8_CAL
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_8_FASTREF_EN                            BIT(21)
#define BIT_BASEIA_DVFS_BIA_FREQ_8_FEFB_EN                               BIT(20)
#define BIT_BASEIA_DVFS_BIA_FREQ_8_MODDIV(x)                             (((x) & 0xF) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_8_CALVCOMEASCOUNT(x)                    (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_8_CALVCOHSCOUNT(x)                      (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE10_CTL
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_10_CODE(x)                              (((x) & 0x3F) << 24)
#define BIT_BASEIA_DVFS_BIA_FREQ_10_CLKSLICE0_ENABLE                     BIT(22)
#define BIT_BASEIA_DVFS_BIA_FREQ_10_REFDIV(x)                            (((x) & 0x3F) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_10_MDIV(x)                              (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_10_CLKSLICE0_DIV(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE10_CAL
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_10_FASTREF_EN                           BIT(21)
#define BIT_BASEIA_DVFS_BIA_FREQ_10_FEFB_EN                              BIT(20)
#define BIT_BASEIA_DVFS_BIA_FREQ_10_MODDIV(x)                            (((x) & 0xF) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_10_CALVCOMEASCOUNT(x)                   (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_10_CALVCOHSCOUNT(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE12_CTL
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_12_CODE(x)                              (((x) & 0x3F) << 24)
#define BIT_BASEIA_DVFS_BIA_FREQ_12_CLKSLICE0_ENABLE                     BIT(22)
#define BIT_BASEIA_DVFS_BIA_FREQ_12_REFDIV(x)                            (((x) & 0x3F) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_12_MDIV(x)                              (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_12_CLKSLICE0_DIV(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE12_CAL
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_12_FASTREF_EN                           BIT(21)
#define BIT_BASEIA_DVFS_BIA_FREQ_12_FEFB_EN                              BIT(20)
#define BIT_BASEIA_DVFS_BIA_FREQ_12_MODDIV(x)                            (((x) & 0xF) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_12_CALVCOMEASCOUNT(x)                   (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_12_CALVCOHSCOUNT(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE14_CTL
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_14_CODE(x)                              (((x) & 0x3F) << 24)
#define BIT_BASEIA_DVFS_BIA_FREQ_14_CLKSLICE0_ENABLE                     BIT(22)
#define BIT_BASEIA_DVFS_BIA_FREQ_14_REFDIV(x)                            (((x) & 0x3F) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_14_MDIV(x)                              (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_14_CLKSLICE0_DIV(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE14_CAL
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_14_FASTREF_EN                           BIT(21)
#define BIT_BASEIA_DVFS_BIA_FREQ_14_FEFB_EN                              BIT(20)
#define BIT_BASEIA_DVFS_BIA_FREQ_14_MODDIV(x)                            (((x) & 0xF) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_14_CALVCOMEASCOUNT(x)                   (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_14_CALVCOHSCOUNT(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE16_CTL
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_16_CODE(x)                              (((x) & 0x3F) << 24)
#define BIT_BASEIA_DVFS_BIA_FREQ_16_CLKSLICE0_ENABLE                     BIT(22)
#define BIT_BASEIA_DVFS_BIA_FREQ_16_REFDIV(x)                            (((x) & 0x3F) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_16_MDIV(x)                              (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_16_CLKSLICE0_DIV(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE16_CAL
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_16_FASTREF_EN                           BIT(21)
#define BIT_BASEIA_DVFS_BIA_FREQ_16_FEFB_EN                              BIT(20)
#define BIT_BASEIA_DVFS_BIA_FREQ_16_MODDIV(x)                            (((x) & 0xF) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_16_CALVCOMEASCOUNT(x)                   (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_16_CALVCOHSCOUNT(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE18_CTL
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_18_CODE(x)                              (((x) & 0x3F) << 24)
#define BIT_BASEIA_DVFS_BIA_FREQ_18_CLKSLICE0_ENABLE                     BIT(22)
#define BIT_BASEIA_DVFS_BIA_FREQ_18_REFDIV(x)                            (((x) & 0x3F) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_18_MDIV(x)                              (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_18_CLKSLICE0_DIV(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE18_CAL
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_18_FASTREF_EN                           BIT(21)
#define BIT_BASEIA_DVFS_BIA_FREQ_18_FEFB_EN                              BIT(20)
#define BIT_BASEIA_DVFS_BIA_FREQ_18_MODDIV(x)                            (((x) & 0xF) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_18_CALVCOMEASCOUNT(x)                   (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_18_CALVCOHSCOUNT(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE20_CTL
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_20_CODE(x)                              (((x) & 0x3F) << 24)
#define BIT_BASEIA_DVFS_BIA_FREQ_20_CLKSLICE0_ENABLE                     BIT(22)
#define BIT_BASEIA_DVFS_BIA_FREQ_20_REFDIV(x)                            (((x) & 0x3F) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_20_MDIV(x)                              (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_20_CLKSLICE0_DIV(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE20_CAL
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_20_FASTREF_EN                           BIT(21)
#define BIT_BASEIA_DVFS_BIA_FREQ_20_FEFB_EN                              BIT(20)
#define BIT_BASEIA_DVFS_BIA_FREQ_20_MODDIV(x)                            (((x) & 0xF) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_20_CALVCOMEASCOUNT(x)                   (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_20_CALVCOHSCOUNT(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE22_CTL
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_22_CODE(x)                              (((x) & 0x3F) << 24)
#define BIT_BASEIA_DVFS_BIA_FREQ_22_CLKSLICE0_ENABLE                     BIT(22)
#define BIT_BASEIA_DVFS_BIA_FREQ_22_REFDIV(x)                            (((x) & 0x3F) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_22_MDIV(x)                              (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_22_CLKSLICE0_DIV(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE22_CAL
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_22_FASTREF_EN                           BIT(21)
#define BIT_BASEIA_DVFS_BIA_FREQ_22_FEFB_EN                              BIT(20)
#define BIT_BASEIA_DVFS_BIA_FREQ_22_MODDIV(x)                            (((x) & 0xF) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_22_CALVCOMEASCOUNT(x)                   (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_22_CALVCOHSCOUNT(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE24_CTL
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_24_CODE(x)                              (((x) & 0x3F) << 24)
#define BIT_BASEIA_DVFS_BIA_FREQ_24_CLKSLICE0_ENABLE                     BIT(22)
#define BIT_BASEIA_DVFS_BIA_FREQ_24_REFDIV(x)                            (((x) & 0x3F) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_24_MDIV(x)                              (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_24_CLKSLICE0_DIV(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE24_CAL
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_24_FASTREF_EN                           BIT(21)
#define BIT_BASEIA_DVFS_BIA_FREQ_24_FEFB_EN                              BIT(20)
#define BIT_BASEIA_DVFS_BIA_FREQ_24_MODDIV(x)                            (((x) & 0xF) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_24_CALVCOMEASCOUNT(x)                   (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_24_CALVCOHSCOUNT(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE26_CTL
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_26_CODE(x)                              (((x) & 0x3F) << 24)
#define BIT_BASEIA_DVFS_BIA_FREQ_26_CLKSLICE0_ENABLE                     BIT(22)
#define BIT_BASEIA_DVFS_BIA_FREQ_26_REFDIV(x)                            (((x) & 0x3F) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_26_MDIV(x)                              (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_26_CLKSLICE0_DIV(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE26_CAL
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_26_FASTREF_EN                           BIT(21)
#define BIT_BASEIA_DVFS_BIA_FREQ_26_FEFB_EN                              BIT(20)
#define BIT_BASEIA_DVFS_BIA_FREQ_26_MODDIV(x)                            (((x) & 0xF) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_26_CALVCOMEASCOUNT(x)                   (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_26_CALVCOHSCOUNT(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE28_CTL
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_28_CODE(x)                              (((x) & 0x3F) << 24)
#define BIT_BASEIA_DVFS_BIA_FREQ_28_CLKSLICE0_ENABLE                     BIT(22)
#define BIT_BASEIA_DVFS_BIA_FREQ_28_REFDIV(x)                            (((x) & 0x3F) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_28_MDIV(x)                              (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_28_CLKSLICE0_DIV(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE28_CAL
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_28_FASTREF_EN                           BIT(21)
#define BIT_BASEIA_DVFS_BIA_FREQ_28_FEFB_EN                              BIT(20)
#define BIT_BASEIA_DVFS_BIA_FREQ_28_MODDIV(x)                            (((x) & 0xF) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_28_CALVCOMEASCOUNT(x)                   (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_28_CALVCOHSCOUNT(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE30_CTL
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_30_CODE(x)                              (((x) & 0x3F) << 24)
#define BIT_BASEIA_DVFS_BIA_FREQ_30_CLKSLICE0_ENABLE                     BIT(22)
#define BIT_BASEIA_DVFS_BIA_FREQ_30_REFDIV(x)                            (((x) & 0x3F) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_30_MDIV(x)                              (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_30_CLKSLICE0_DIV(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE30_CAL
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_30_FASTREF_EN                           BIT(21)
#define BIT_BASEIA_DVFS_BIA_FREQ_30_FEFB_EN                              BIT(20)
#define BIT_BASEIA_DVFS_BIA_FREQ_30_MODDIV(x)                            (((x) & 0xF) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_30_CALVCOMEASCOUNT(x)                   (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_30_CALVCOHSCOUNT(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE32_CTL
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_32_CODE(x)                              (((x) & 0x3F) << 24)
#define BIT_BASEIA_DVFS_BIA_FREQ_32_CLKSLICE0_ENABLE                     BIT(22)
#define BIT_BASEIA_DVFS_BIA_FREQ_32_REFDIV(x)                            (((x) & 0x3F) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_32_MDIV(x)                              (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_32_CLKSLICE0_DIV(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE32_CAL
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_32_FASTREF_EN                           BIT(21)
#define BIT_BASEIA_DVFS_BIA_FREQ_32_FEFB_EN                              BIT(20)
#define BIT_BASEIA_DVFS_BIA_FREQ_32_MODDIV(x)                            (((x) & 0xF) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_32_CALVCOMEASCOUNT(x)                   (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_32_CALVCOHSCOUNT(x)                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE_DEF_CTL
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_DEF_CLKSLICE0_ENABLE                    BIT(22)
#define BIT_BASEIA_DVFS_BIA_FREQ_DEF_REFDIV(x)                           (((x) & 0x3F) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_DEF_MDIV(x)                             (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_DEF_CLKSLICE0_DIV(x)                    (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_TABLE_DEF_CAL
// Register Offset : 0x008C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_FREQ_DEF_FASTREF_EN                          BIT(21)
#define BIT_BASEIA_DVFS_BIA_FREQ_DEF_FEFB_EN                             BIT(20)
#define BIT_BASEIA_DVFS_BIA_FREQ_DEF_MODDIV(x)                           (((x) & 0xF) << 16)
#define BIT_BASEIA_DVFS_BIA_FREQ_DEF_CALVCOMEASCOUNT(x)                  (((x) & 0xFF) << 8)
#define BIT_BASEIA_DVFS_BIA_FREQ_DEF_CALVCOHSCOUNT(x)                    (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_DEBUG_CODE
// Register Offset : 0x00A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_CPU1_USE_CODE(x)                                 (((x) & 0x3F) << 18)
#define BIT_BASEIA_DVFS_CPU1_REQ_CODE(x)                                 (((x) & 0x3F) << 12)
#define BIT_BASEIA_DVFS_CPU0_USE_CODE(x)                                 (((x) & 0x3F) << 6)
#define BIT_BASEIA_DVFS_CPU0_REQ_CODE(x)                                 (((x) & 0x3F))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_DEBUG_BUS
// Register Offset : 0x00A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_DEBUG_BUS(x)                                     (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_DUMMY
// Register Offset : 0x00A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_BIA_DVFS_DUMMY(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_INT_EN
// Register Offset : 0x00C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_INT_DVFS1_BADCODE_EN                             BIT(1)
#define BIT_BASEIA_DVFS_INT_DVFS0_BADCODE_EN                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_INT_CLR
// Register Offset : 0x00C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_INT_DVFS1_BADCODE_CLR                            BIT(1)
#define BIT_BASEIA_DVFS_INT_DVFS0_BADCODE_CLR                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_INT_SET
// Register Offset : 0x00C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_INT_DVFS1_BADCODE_SET                            BIT(1)
#define BIT_BASEIA_DVFS_INT_DVFS0_BADCODE_SET                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_INT_RAW
// Register Offset : 0x00CC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_INT_DVFS1_BADCODE_RAW                            BIT(1)
#define BIT_BASEIA_DVFS_INT_DVFS0_BADCODE_RAW                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_BASEIA_DVFS_BIA_DVFS_INT
// Register Offset : 0x00D0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_BASEIA_DVFS_INT_DVFS1_BADCODE                                BIT(1)
#define BIT_BASEIA_DVFS_INT_DVFS0_BADCODE                                BIT(0)


#endif // _BASEIA_DVFS_REG_H
