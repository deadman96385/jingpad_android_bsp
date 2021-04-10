/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _ANLG_PHY_G1_REG_H
#define _ANLG_PHY_G1_REG_H

#define CTL_BASE_ANLG_PHY_G1 SPRD_ANLG_PHY_G1


#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_ANA_BB_PWR_CTRL       ( CTL_BASE_ANLG_PHY_G1 + 0x0000 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_ANA_BB_RST_CTRL       ( CTL_BASE_ANLG_PHY_G1 + 0x0004 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_ANA_BB_SINE_CTRL      ( CTL_BASE_ANLG_PHY_G1 + 0x0008 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_BB_BG_CTRL            ( CTL_BASE_ANLG_PHY_G1 + 0x000C )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_ANALOG_TEST           ( CTL_BASE_ANLG_PHY_G1 + 0x0010 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_CTRL0            ( CTL_BASE_ANLG_PHY_G1 + 0x0014 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_CTRL1            ( CTL_BASE_ANLG_PHY_G1 + 0x0018 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_CTRL2            ( CTL_BASE_ANLG_PHY_G1 + 0x001C )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_BIST_CTRL        ( CTL_BASE_ANLG_PHY_G1 + 0x0020 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_CTRL0           ( CTL_BASE_ANLG_PHY_G1 + 0x0024 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_CTRL1           ( CTL_BASE_ANLG_PHY_G1 + 0x0028 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_CTRL2           ( CTL_BASE_ANLG_PHY_G1 + 0x002C )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_BIST_CTRL       ( CTL_BASE_ANLG_PHY_G1 + 0x0030 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_CTRL0            ( CTL_BASE_ANLG_PHY_G1 + 0x0034 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_CTRL1            ( CTL_BASE_ANLG_PHY_G1 + 0x0038 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_CTRL2            ( CTL_BASE_ANLG_PHY_G1 + 0x003C )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_BIST_CTRL        ( CTL_BASE_ANLG_PHY_G1 + 0x0040 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_CTRL0            ( CTL_BASE_ANLG_PHY_G1 + 0x0044 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_CTRL1            ( CTL_BASE_ANLG_PHY_G1 + 0x0048 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_CTRL2            ( CTL_BASE_ANLG_PHY_G1 + 0x004C )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_BIST_CTRL        ( CTL_BASE_ANLG_PHY_G1 + 0x0050 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_CTRL0           ( CTL_BASE_ANLG_PHY_G1 + 0x0054 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_CTRL1           ( CTL_BASE_ANLG_PHY_G1 + 0x0058 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_CTRL2           ( CTL_BASE_ANLG_PHY_G1 + 0x005C )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_BIST_CTRL       ( CTL_BASE_ANLG_PHY_G1 + 0x0060 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_CTRL1            ( CTL_BASE_ANLG_PHY_G1 + 0x0064 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_CTRL2            ( CTL_BASE_ANLG_PHY_G1 + 0x0068 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_ANA_BB_RSVD           ( CTL_BASE_ANLG_PHY_G1 + 0x006C )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_RTC4M_CTRL            ( CTL_BASE_ANLG_PHY_G1 + 0x0070 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_TEST_CLK_CTRL         ( CTL_BASE_ANLG_PHY_G1 + 0x0074 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_TEST_0           ( CTL_BASE_ANLG_PHY_G1 + 0x0078 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_WRAP_GLUE_CTRL        ( CTL_BASE_ANLG_PHY_G1 + 0x007C )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_TEST_1           ( CTL_BASE_ANLG_PHY_G1 + 0x0080 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_TEST_2           ( CTL_BASE_ANLG_PHY_G1 + 0x0084 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_TEST_3           ( CTL_BASE_ANLG_PHY_G1 + 0x0088 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_TEST_4           ( CTL_BASE_ANLG_PHY_G1 + 0x008C )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_REG_SEL_CFG_0         ( CTL_BASE_ANLG_PHY_G1 + 0x0090 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_REG_SEL_CFG_1         ( CTL_BASE_ANLG_PHY_G1 + 0x0094 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_REG_SEL_CFG_2         ( CTL_BASE_ANLG_PHY_G1 + 0x0098 )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_REG_SEL_CFG_3         ( CTL_BASE_ANLG_PHY_G1 + 0x009C )
#define REG_ANLG_PHY_G1_ANALOG_BB_TOP_REG_SEL_CFG_4         ( CTL_BASE_ANLG_PHY_G1 + 0x00A0 )
#define REG_ANLG_PHY_G1_ANALOG_THM0_THM0_CTRL_0             ( CTL_BASE_ANLG_PHY_G1 + 0x00A4 )
#define REG_ANLG_PHY_G1_ANALOG_THM0_THM0_CTRL_1             ( CTL_BASE_ANLG_PHY_G1 + 0x00A8 )
#define REG_ANLG_PHY_G1_ANALOG_THM0_REG_SEL_CFG_0           ( CTL_BASE_ANLG_PHY_G1 + 0x00AC )

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_ANA_BB_PWR_CTRL
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_REC_26MHZ_0_BUF_PD                            BIT(9)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_REC_32MHZ_0_BUF_PD                            BIT(8)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_BB_BG_PD                                      BIT(7)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_PD                                       BIT(6)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_PD                                      BIT(5)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_PD                                       BIT(4)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_PD                                       BIT(3)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_PD                                      BIT(2)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_S_AAPC_PD                                     BIT(1)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_M_AAPC_PD                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_ANA_BB_RST_CTRL
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_RST                                      BIT(5)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_RST                                     BIT(4)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_RST                                      BIT(3)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_RST                                      BIT(2)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RTC4M0_RSTB                                   BIT(1)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_RST                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_ANA_BB_SINE_CTRL
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_REC_26MHZ_0_CUR_SEL                           BIT(25)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_REC_32MHZ_0_CUR_SEL                           BIT(24)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_PROBE_SEL(x)                                  (((x) & 0x3F) << 18)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_SINDRV_ENA                                    BIT(17)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_SINDRV_ENA_SQUARE                             BIT(16)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CLK26M_RESERVED(x)                            (((x) & 0x7FF) << 5)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CLK26M_TUNED_SEL                              BIT(4)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_REC_26MHZ_SR_TRIM(x)                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_BB_BG_CTRL
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_BB_BG_RBIAS_EN                                BIT(1)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_BB_CON_BG                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_ANALOG_TEST
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_ANALOG_TESTMUX(x)                             (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_ANALOG_PLL_RESERVED(x)                        (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_CTRL0
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_N(x)                                     (((x) & 0x7FF) << 11)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_IBIAS(x)                                 (((x) & 0x3) << 9)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_LPF(x)                                   (((x) & 0x7) << 6)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_SDM_EN                                   BIT(5)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_MOD_EN                                   BIT(4)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_DIV_S                                    BIT(3)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_REF_SEL(x)                               (((x) & 0x3) << 1)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_26M_SEL                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_CTRL1
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_NINT(x)                                  (((x) & 0x7F) << 23)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_KINT(x)                                  (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_CTRL2
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_RESERVED(x)                              (((x) & 0xFFFF) << 9)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_DIV1_EN                                  BIT(8)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_BIST_EN                                  BIT(7)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_26M_DIV(x)                               (((x) & 0x3F) << 1)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_LOCK_DONE                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_BIST_CTRL
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_BIST_CTRL(x)                             (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_BIST_CNT(x)                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_CTRL0
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_N(x)                                    (((x) & 0x7FF) << 10)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_IBIAS(x)                                (((x) & 0x3) << 8)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_LPF(x)                                  (((x) & 0x7) << 5)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_SDM_EN                                  BIT(4)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_MOD_EN                                  BIT(3)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_DIV_S                                   BIT(2)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_REF_SEL(x)                              (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_CTRL1
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_NINT(x)                                 (((x) & 0x7F) << 23)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_KINT(x)                                 (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_CTRL2
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_RESERVED(x)                             (((x) & 0xFF) << 7)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_CLKOUT_EN                               BIT(6)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_DIV1_EN                                 BIT(5)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_DIV2_EN                                 BIT(4)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_DIV3_EN                                 BIT(3)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_DIV5_EN                                 BIT(2)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_DIV7_EN                                 BIT(1)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_LOCK_DONE                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_BIST_CTRL
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_BIST_EN                                 BIT(24)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_BIST_CTRL(x)                            (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TWPLL_BIST_CNT(x)                             (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_CTRL0
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_N(x)                                     (((x) & 0x7FF) << 10)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_IBIAS(x)                                 (((x) & 0x3) << 8)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_LPF(x)                                   (((x) & 0x7) << 5)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_SDM_EN                                   BIT(4)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_MOD_EN                                   BIT(3)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_DIV_S                                    BIT(2)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_REF_SEL(x)                               (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_CTRL1
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_NINT(x)                                  (((x) & 0x7F) << 23)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_KINT(x)                                  (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_CTRL2
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_RESERVED(x)                              (((x) & 0xFF) << 6)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_CLKOUT_EN                                BIT(5)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_DIV1_EN                                  BIT(4)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_DIV2_EN                                  BIT(3)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_DIV3_EN                                  BIT(2)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_DIV5_EN                                  BIT(1)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_LOCK_DONE                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_BIST_CTRL
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_BIST_EN                                  BIT(24)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_BIST_CTRL(x)                             (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_LPLL_BIST_CNT(x)                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_CTRL0
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_N(x)                                     (((x) & 0x7FF) << 9)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_IBIAS(x)                                 (((x) & 0x3) << 7)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_LPF(x)                                   (((x) & 0x7) << 4)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_SDM_EN                                   BIT(3)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_MOD_EN                                   BIT(2)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_DIV_S                                    BIT(1)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_REF_SEL                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_CTRL1
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_NINT(x)                                  (((x) & 0x7F) << 23)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_KINT(x)                                  (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_CTRL2
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_RESERVED(x)                              (((x) & 0xFF) << 11)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_POSTDIV                                  BIT(10)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_CLKOUT_EN                                BIT(9)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_LOCK_DONE                                BIT(8)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_CCS_CTRL(x)                              (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_BIST_CTRL
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_BIST_EN                                  BIT(24)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_BIST_CTRL(x)                             (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_GPLL_BIST_CNT(x)                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_CTRL0
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_N(x)                                    (((x) & 0x7FF) << 9)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_IBIAS(x)                                (((x) & 0x3) << 7)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_LPF(x)                                  (((x) & 0x7) << 4)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_SDM_EN                                  BIT(3)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_MOD_EN                                  BIT(2)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_DIV_S                                   BIT(1)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_REF_SEL                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_CTRL1
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_NINT(x)                                 (((x) & 0x7F) << 23)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_KINT(x)                                 (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_CTRL2
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_RESERVED(x)                             (((x) & 0xFF) << 5)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_POSTDIV                                 BIT(4)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_CLKOUT_EN                               BIT(3)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_DIV1_EN                                 BIT(2)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_DIV32_EN                                BIT(1)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_LOCK_DONE                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_BIST_CTRL
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_BIST_EN                                 BIT(24)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_BIST_CTRL(x)                            (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_CPPLL_BIST_CNT(x)                             (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_CTRL1
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_G0(x)                                    (((x) & 0x3) << 24)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_G1(x)                                    (((x) & 0x3) << 22)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_G2(x)                                    (((x) & 0x3) << 20)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_S_AAPC_LOW_V_CON                              BIT(19)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_S_AAPC_D(x)                                   (((x) & 0x3FFF) << 5)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_S_AAPC_BPRES                                  BIT(4)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_S_APCOUT_SEL(x)                               (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_S_AAPC_RESERVED(x)                            (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_CTRL2
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_M_AAPC_D(x)                                   (((x) & 0x3FFF) << 6)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_M_AAPC_LOW_V_CON                              BIT(5)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_M_AAPC_BPRES                                  BIT(4)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_M_APCOUT_SEL(x)                               (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_M_AAPC_RESERVED(x)                            (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_ANA_BB_RSVD
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_ANA_BB_RESERVED(x)                            (((x) & 0xFFFF) << 2)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TO_LVDS_SEL(x)                                (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_RTC4M_CTRL
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RTC4M0_EN                                     BIT(22)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RTC4M0_I_C(x)                                 (((x) & 0xF) << 18)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RTC4M0_RC_C(x)                                (((x) & 0x1FF) << 9)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RTC4M0_CHOP_EN                                BIT(8)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RTC4M0_RESERVED(x)                            (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_TEST_CLK_CTRL
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TEST_CLK_EN                                   BIT(3)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TEST_CLK_OD                                   BIT(2)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_TEST_CLK_DIV(x)                               (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_TEST_0
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_STEP_SEL                                 BIT(31)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_MAX_RANGE(x)                             (((x) & 0x3FFF) << 17)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_MIN_RANGE(x)                             (((x) & 0x3FFF) << 3)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_RSTN                                     BIT(2)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_GEN_SEL(x)                               (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_WRAP_GLUE_CTRL
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_PD_SEL                                   BIT(1)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_RPLL_RST_SEL                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_TEST_1
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_SQUA_D0(x)                               (((x) & 0x3FFF) << 14)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_SQUA_D1(x)                               (((x) & 0x3FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_TEST_2
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_SQUA_D2(x)                               (((x) & 0x3FFF) << 14)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_SQUA_D3(x)                               (((x) & 0x3FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_TEST_3
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_SQUA_D4(x)                               (((x) & 0x3FFF) << 14)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_SQUA_D5(x)                               (((x) & 0x3FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_TEST_4
// Register Offset : 0x008C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_SQUA_D6(x)                               (((x) & 0x3FFF) << 14)
#define BIT_ANLG_PHY_G1_ANALOG_BB_TOP_AAPC_SQUA_D7(x)                               (((x) & 0x3FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_REG_SEL_CFG_0
// Register Offset : 0x0090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_REC_26MHZ_0_BUF_PD                    BIT(31)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_REC_32MHZ_0_BUF_PD                    BIT(30)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_BB_BG_PD                              BIT(29)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RPLL_PD                               BIT(28)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_PD                              BIT(27)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_PD                               BIT(26)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_GPLL_PD                               BIT(25)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CPPLL_PD                              BIT(24)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_S_AAPC_PD                             BIT(23)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_M_AAPC_PD                             BIT(22)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RPLL_RST                              BIT(21)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_RST                             BIT(20)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_RST                              BIT(19)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_GPLL_RST                              BIT(18)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RTC4M0_RSTB                           BIT(17)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CPPLL_RST                             BIT(16)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_REC_26MHZ_0_CUR_SEL                   BIT(15)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_REC_32MHZ_0_CUR_SEL                   BIT(14)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_PROBE_SEL                             BIT(13)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_SINDRV_ENA                            BIT(12)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_SINDRV_ENA_SQUARE                     BIT(11)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CLK26M_RESERVED                       BIT(10)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CLK26M_TUNED_SEL                      BIT(9)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_REC_26MHZ_SR_TRIM                     BIT(8)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_BB_BG_RBIAS_EN                        BIT(7)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_BB_CON_BG                             BIT(6)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_ANALOG_TESTMUX                        BIT(5)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_ANALOG_PLL_RESERVED                   BIT(4)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RPLL_N                                BIT(3)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RPLL_IBIAS                            BIT(2)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RPLL_LPF                              BIT(1)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RPLL_SDM_EN                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_REG_SEL_CFG_1
// Register Offset : 0x0094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RPLL_MOD_EN                           BIT(31)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RPLL_DIV_S                            BIT(30)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RPLL_REF_SEL                          BIT(29)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RPLL_26M_SEL                          BIT(28)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RPLL_NINT                             BIT(27)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RPLL_KINT                             BIT(26)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RPLL_RESERVED                         BIT(25)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RPLL_DIV1_EN                          BIT(24)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RPLL_BIST_EN                          BIT(23)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RPLL_26M_DIV                          BIT(22)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RPLL_BIST_CTRL                        BIT(21)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_N                               BIT(20)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_IBIAS                           BIT(19)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_LPF                             BIT(18)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_SDM_EN                          BIT(17)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_MOD_EN                          BIT(16)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_DIV_S                           BIT(15)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_REF_SEL                         BIT(14)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_NINT                            BIT(13)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_KINT                            BIT(12)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_RESERVED                        BIT(11)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_CLKOUT_EN                       BIT(10)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_DIV1_EN                         BIT(9)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_DIV2_EN                         BIT(8)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_DIV3_EN                         BIT(7)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_DIV5_EN                         BIT(6)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_DIV7_EN                         BIT(5)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_BIST_EN                         BIT(4)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TWPLL_BIST_CTRL                       BIT(3)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_N                                BIT(2)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_IBIAS                            BIT(1)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_LPF                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_REG_SEL_CFG_2
// Register Offset : 0x0098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_SDM_EN                           BIT(31)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_MOD_EN                           BIT(30)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_DIV_S                            BIT(29)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_REF_SEL                          BIT(28)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_NINT                             BIT(27)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_KINT                             BIT(26)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_RESERVED                         BIT(25)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_CLKOUT_EN                        BIT(24)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_DIV1_EN                          BIT(23)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_DIV2_EN                          BIT(22)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_DIV3_EN                          BIT(21)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_DIV5_EN                          BIT(20)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_BIST_EN                          BIT(19)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_LPLL_BIST_CTRL                        BIT(18)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_GPLL_N                                BIT(17)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_GPLL_IBIAS                            BIT(16)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_GPLL_LPF                              BIT(15)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_GPLL_SDM_EN                           BIT(14)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_GPLL_MOD_EN                           BIT(13)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_GPLL_DIV_S                            BIT(12)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_GPLL_REF_SEL                          BIT(11)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_GPLL_NINT                             BIT(10)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_GPLL_KINT                             BIT(9)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_GPLL_RESERVED                         BIT(8)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_GPLL_POSTDIV                          BIT(7)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_GPLL_CLKOUT_EN                        BIT(6)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_GPLL_CCS_CTRL                         BIT(5)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_GPLL_BIST_EN                          BIT(4)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_GPLL_BIST_CTRL                        BIT(3)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CPPLL_N                               BIT(2)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CPPLL_IBIAS                           BIT(1)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CPPLL_LPF                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_REG_SEL_CFG_3
// Register Offset : 0x009C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CPPLL_SDM_EN                          BIT(31)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CPPLL_MOD_EN                          BIT(30)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CPPLL_DIV_S                           BIT(29)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CPPLL_REF_SEL                         BIT(28)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CPPLL_NINT                            BIT(27)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CPPLL_KINT                            BIT(26)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CPPLL_RESERVED                        BIT(25)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CPPLL_POSTDIV                         BIT(24)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CPPLL_CLKOUT_EN                       BIT(23)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CPPLL_DIV1_EN                         BIT(22)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CPPLL_DIV32_EN                        BIT(21)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CPPLL_BIST_EN                         BIT(20)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_CPPLL_BIST_CTRL                       BIT(19)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_AAPC_G0                               BIT(18)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_AAPC_G1                               BIT(17)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_AAPC_G2                               BIT(16)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_S_AAPC_LOW_V_CON                      BIT(15)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_S_AAPC_D                              BIT(14)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_S_AAPC_BPRES                          BIT(13)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_S_APCOUT_SEL                          BIT(12)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_S_AAPC_RESERVED                       BIT(11)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_M_AAPC_D                              BIT(10)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_M_AAPC_LOW_V_CON                      BIT(9)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_M_AAPC_BPRES                          BIT(8)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_M_APCOUT_SEL                          BIT(7)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_M_AAPC_RESERVED                       BIT(6)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_ANA_BB_RESERVED                       BIT(5)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_TO_LVDS_SEL                           BIT(4)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RTC4M0_EN                             BIT(3)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RTC4M0_I_C                            BIT(2)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RTC4M0_RC_C                           BIT(1)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RTC4M0_CHOP_EN                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_BB_TOP_REG_SEL_CFG_4
// Register Offset : 0x00A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_BB_TOP_RTC4M0_RESERVED                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_THM0_THM0_CTRL_0
// Register Offset : 0x00A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_THM0_THM0_PD                                         BIT(23)
#define BIT_ANLG_PHY_G1_ANALOG_THM0_THM0_RSTN                                       BIT(22)
#define BIT_ANLG_PHY_G1_ANALOG_THM0_THM0_RUN                                        BIT(21)
#define BIT_ANLG_PHY_G1_ANALOG_THM0_THM0_CALI_EN                                    BIT(20)
#define BIT_ANLG_PHY_G1_ANALOG_THM0_THM0_ITUNE(x)                                   (((x) & 0xF) << 16)
#define BIT_ANLG_PHY_G1_ANALOG_THM0_THM0_RESERVED(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_THM0_THM0_CTRL_1
// Register Offset : 0x00A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_ANALOG_THM0_THM0_DATA(x)                                    (((x) & 0xFF) << 1)
#define BIT_ANLG_PHY_G1_ANALOG_THM0_THM0_VALID                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G1_ANALOG_THM0_REG_SEL_CFG_0
// Register Offset : 0x00AC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_THM0_THM0_PD                                 BIT(5)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_THM0_THM0_RSTN                               BIT(4)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_THM0_THM0_RUN                                BIT(3)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_THM0_THM0_CALI_EN                            BIT(2)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_THM0_THM0_ITUNE                              BIT(1)
#define BIT_ANLG_PHY_G1_DBG_SEL_ANALOG_THM0_THM0_RESERVED                           BIT(0)


#endif // _ANLG_PHY_G1_REG_H
