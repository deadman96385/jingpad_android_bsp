/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _ANLG_PHY_G2_REG_H
#define _ANLG_PHY_G2_REG_H

#define CTL_BASE_ANLG_PHY_G2 SPRD_ANLG_PHY_G2


#define REG_ANLG_PHY_G2_ANALOG_PLL_0_CRIT_CTRL_0              ( CTL_BASE_ANLG_PHY_G2 + 0x0000 )
#define REG_ANLG_PHY_G2_ANALOG_PLL_0_PHASE_CTRL_0             ( CTL_BASE_ANLG_PHY_G2 + 0x0004 )
#define REG_ANLG_PHY_G2_ANALOG_PLL_0_PHASE_CTRL_1             ( CTL_BASE_ANLG_PHY_G2 + 0x0008 )
#define REG_ANLG_PHY_G2_ANALOG_PLL_0_PLL_DIRECT_CTRL_0        ( CTL_BASE_ANLG_PHY_G2 + 0x000C )
#define REG_ANLG_PHY_G2_ANALOG_PLL_0_PLL_DIRECT_CTRL_1        ( CTL_BASE_ANLG_PHY_G2 + 0x0010 )
#define REG_ANLG_PHY_G2_ANALOG_PLL_0_PLL_DIRECT_CTRL_JTAG     ( CTL_BASE_ANLG_PHY_G2 + 0x0014 )
#define REG_ANLG_PHY_G2_ANALOG_PLL_0_REG_SEL_CFG_0            ( CTL_BASE_ANLG_PHY_G2 + 0x0018 )
#define REG_ANLG_PHY_G2_ANALOG_PLL_1_CRIT_CTRL_0              ( CTL_BASE_ANLG_PHY_G2 + 0x001C )
#define REG_ANLG_PHY_G2_ANALOG_PLL_1_PHASE_CTRL_0             ( CTL_BASE_ANLG_PHY_G2 + 0x0020 )
#define REG_ANLG_PHY_G2_ANALOG_PLL_1_PHASE_CTRL_1             ( CTL_BASE_ANLG_PHY_G2 + 0x0024 )
#define REG_ANLG_PHY_G2_ANALOG_PLL_1_PLL_DIRECT_CTRL_0        ( CTL_BASE_ANLG_PHY_G2 + 0x0028 )
#define REG_ANLG_PHY_G2_ANALOG_PLL_1_PLL_DIRECT_CTRL_1        ( CTL_BASE_ANLG_PHY_G2 + 0x002C )
#define REG_ANLG_PHY_G2_ANALOG_PLL_1_PLL_DIRECT_CTRL_JTAG     ( CTL_BASE_ANLG_PHY_G2 + 0x0030 )
#define REG_ANLG_PHY_G2_ANALOG_PLL_1_REG_SEL_CFG_0            ( CTL_BASE_ANLG_PHY_G2 + 0x0034 )
#define REG_ANLG_PHY_G2_ANALOG_CZPLL_CRIT_CTRL_0              ( CTL_BASE_ANLG_PHY_G2 + 0x0038 )
#define REG_ANLG_PHY_G2_ANALOG_CZPLL_PHASE_CTRL_0             ( CTL_BASE_ANLG_PHY_G2 + 0x003C )
#define REG_ANLG_PHY_G2_ANALOG_CZPLL_PHASE_CTRL_1             ( CTL_BASE_ANLG_PHY_G2 + 0x0040 )
#define REG_ANLG_PHY_G2_ANALOG_CZPLL_PLL_DIRECT_CTRL_0        ( CTL_BASE_ANLG_PHY_G2 + 0x0044 )
#define REG_ANLG_PHY_G2_ANALOG_CZPLL_PLL_DIRECT_CTRL_1        ( CTL_BASE_ANLG_PHY_G2 + 0x0048 )
#define REG_ANLG_PHY_G2_ANALOG_CZPLL_PLL_DIRECT_CTRL_JTAG     ( CTL_BASE_ANLG_PHY_G2 + 0x004C )
#define REG_ANLG_PHY_G2_ANALOG_CZPLL_REG_SEL_CFG_0            ( CTL_BASE_ANLG_PHY_G2 + 0x0050 )
#define REG_ANLG_PHY_G2_ANALOG_EFUSE_0_PHY_EFUSE_OPT          ( CTL_BASE_ANLG_PHY_G2 + 0x0054 )
#define REG_ANLG_PHY_G2_ANALOG_EFUSE_1_PHY_EFUSE_OPT          ( CTL_BASE_ANLG_PHY_G2 + 0x0058 )
#define REG_ANLG_PHY_G2_ANALOG_EFUSE_2_PHY_EFUSE_OPT          ( CTL_BASE_ANLG_PHY_G2 + 0x005C )
#define REG_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO_CFG_0          ( CTL_BASE_ANLG_PHY_G2 + 0x0060 )
#define REG_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO_CFG_1          ( CTL_BASE_ANLG_PHY_G2 + 0x0064 )
#define REG_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO_CFG_2          ( CTL_BASE_ANLG_PHY_G2 + 0x0068 )
#define REG_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO_CFG_3          ( CTL_BASE_ANLG_PHY_G2 + 0x006C )
#define REG_ANLG_PHY_G2_ANALOG_LDO_RCO100M_CLK_CTRL_0         ( CTL_BASE_ANLG_PHY_G2 + 0x0070 )
#define REG_ANLG_PHY_G2_ANALOG_LDO_RCO100M_PWR_CTRL_0         ( CTL_BASE_ANLG_PHY_G2 + 0x0074 )
#define REG_ANLG_PHY_G2_ANALOG_LDO_RCO100M_REG_SEL_CFG_0      ( CTL_BASE_ANLG_PHY_G2 + 0x0078 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_PWR_CTRL_0              ( CTL_BASE_ANLG_PHY_G2 + 0x007C )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CFG_0               ( CTL_BASE_ANLG_PHY_G2 + 0x0080 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_PLL_TEST_0              ( CTL_BASE_ANLG_PHY_G2 + 0x0084 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_PLL_CLKCTL_0            ( CTL_BASE_ANLG_PHY_G2 + 0x0088 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_0              ( CTL_BASE_ANLG_PHY_G2 + 0x008C )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_MODU_CTRL_0             ( CTL_BASE_ANLG_PHY_G2 + 0x0090 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_DIV_CTRL_0              ( CTL_BASE_ANLG_PHY_G2 + 0x0094 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_PLL_BIST_0              ( CTL_BASE_ANLG_PHY_G2 + 0x0098 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_1              ( CTL_BASE_ANLG_PHY_G2 + 0x009C )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_MODU_CTRL_1             ( CTL_BASE_ANLG_PHY_G2 + 0x00A0 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_DIV_CTRL_1              ( CTL_BASE_ANLG_PHY_G2 + 0x00A4 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_PLL_BIST_1              ( CTL_BASE_ANLG_PHY_G2 + 0x00A8 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_2              ( CTL_BASE_ANLG_PHY_G2 + 0x00AC )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_MODU_CTRL_2             ( CTL_BASE_ANLG_PHY_G2 + 0x00B0 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_DIV_CTRL_2              ( CTL_BASE_ANLG_PHY_G2 + 0x00B4 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_PLL_BIST_2              ( CTL_BASE_ANLG_PHY_G2 + 0x00B8 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_3              ( CTL_BASE_ANLG_PHY_G2 + 0x00BC )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_MODU_CTRL_3             ( CTL_BASE_ANLG_PHY_G2 + 0x00C0 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_DIV_CTRL_3              ( CTL_BASE_ANLG_PHY_G2 + 0x00C4 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_PLL_BIST_3              ( CTL_BASE_ANLG_PHY_G2 + 0x00C8 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_4              ( CTL_BASE_ANLG_PHY_G2 + 0x00CC )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_MODU_CTRL_4             ( CTL_BASE_ANLG_PHY_G2 + 0x00D0 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_DIV_CTRL_4              ( CTL_BASE_ANLG_PHY_G2 + 0x00D4 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_PLL_BIST_4              ( CTL_BASE_ANLG_PHY_G2 + 0x00D8 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_5              ( CTL_BASE_ANLG_PHY_G2 + 0x00DC )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_MODU_CTRL_5             ( CTL_BASE_ANLG_PHY_G2 + 0x00E0 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_DIV_CTRL_5              ( CTL_BASE_ANLG_PHY_G2 + 0x00E4 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_PLL_BIST_5              ( CTL_BASE_ANLG_PHY_G2 + 0x00E8 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_6              ( CTL_BASE_ANLG_PHY_G2 + 0x00EC )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_MODU_CTRL_6             ( CTL_BASE_ANLG_PHY_G2 + 0x00F0 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_DIV_CTRL_6              ( CTL_BASE_ANLG_PHY_G2 + 0x00F4 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_PLL_BIST_6              ( CTL_BASE_ANLG_PHY_G2 + 0x00F8 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_MSTAPC_CTL_0            ( CTL_BASE_ANLG_PHY_G2 + 0x00FC )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_SLVAPC_CTL_0            ( CTL_BASE_ANLG_PHY_G2 + 0x0100 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_GAIN_CTL_0              ( CTL_BASE_ANLG_PHY_G2 + 0x0104 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_BG_TOP_0                ( CTL_BASE_ANLG_PHY_G2 + 0x0108 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK26M_CTL_0            ( CTL_BASE_ANLG_PHY_G2 + 0x010C )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_WRAP_GLUE_CTRL          ( CTL_BASE_ANLG_PHY_G2 + 0x0110 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_AAPC_TEST               ( CTL_BASE_ANLG_PHY_G2 + 0x0114 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_REG_SEL_CFG_0           ( CTL_BASE_ANLG_PHY_G2 + 0x0118 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_REG_SEL_CFG_1           ( CTL_BASE_ANLG_PHY_G2 + 0x011C )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_REG_SEL_CFG_2           ( CTL_BASE_ANLG_PHY_G2 + 0x0120 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_DUMY_RW0                ( CTL_BASE_ANLG_PHY_G2 + 0x0124 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_DUMY_RW1                ( CTL_BASE_ANLG_PHY_G2 + 0x0128 )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_DUMY_RO0                ( CTL_BASE_ANLG_PHY_G2 + 0x012C )
#define REG_ANLG_PHY_G2_ANALOG_BB_TOP_DUMY_RO1                ( CTL_BASE_ANLG_PHY_G2 + 0x0130 )

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_PLL_0_CRIT_CTRL_0
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_IRST_PLL_POR_B_A                                            BIT(2)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_IPD_PLL_KEEPALIVE_B_NT                                      BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_OCTL_PLL_SYNTHLOCKSTATUS_A                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_PLL_0_PHASE_CTRL_0
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_CLKSLICE0_DIV_A_(x)                                (((x) & 0xFF) << 8)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_CLKSLICE1_DIV_A_(x)                                (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_PLL_0_PHASE_CTRL_1
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_CLKSLICE0_ENABLE_A                                 BIT(23)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_CLKSLICE1_ENABLE_A                                 BIT(22)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_CLKSLICE0_BYPASS_EN_A                              BIT(21)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_CLKSLICE1_BYPASS_EN_A                              BIT(20)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_CLKSLICE0_CKMUTE_EN_A                              BIT(19)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_CLKSLICE1_CKMUTE_EN_A                              BIT(18)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_CLKSLICE0_PHINC_A                                  BIT(17)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_CLKSLICE1_PHINC_A                                  BIT(16)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_CALVCOHSCOUNT_NT_(x)                               (((x) & 0xFF) << 8)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_CALVCOMEASCOUNT_NT_(x)                             (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_PLL_0_PLL_DIRECT_CTRL_0
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_FDIV_NT_(x)                                        (((x) & 0xFFFFFF) << 8)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_MDIV_NT_(x)                                        (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_PLL_0_PLL_DIRECT_CTRL_1
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_KEEPALIVE_DISABLE_A                                BIT(18)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_EXTFB_EN_NT                                        BIT(17)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_REFDIV_NT_(x)                                      (((x) & 0x3F) << 11)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_CAL_CLR_A                                          BIT(10)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_DISCONNECT_A                                       BIT(9)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_MODDIV_NT_(x)                                      (((x) & 0xF) << 5)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_OCTL_PLL_CLKSLICE0_STATUS_A                                 BIT(4)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_OCTL_PLL_CLKSLICE1_STATUS_A                                 BIT(3)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_OCTL_PLL_DISCONNECT_STATUS_A                                BIT(2)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_FASTREF_EN_NT                                      BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_FEFB_EN_NT                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_PLL_0_PLL_DIRECT_CTRL_JTAG
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_PLL_0_ICTL_PLL_JTAGID_NT_(x)                                      (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_PLL_0_REG_SEL_CFG_0
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_0_IRST_PLL_POR_B_A                                    BIT(13)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_0_IPD_PLL_KEEPALIVE_B_NT                              BIT(12)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_0_ICTL_PLL_CLKSLICE0_DIV_A_                           BIT(11)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_0_ICTL_PLL_CLKSLICE0_ENABLE_A                         BIT(10)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_0_ICTL_PLL_CALVCOHSCOUNT_NT_                          BIT(9)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_0_ICTL_PLL_CALVCOMEASCOUNT_NT_                        BIT(8)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_0_ICTL_PLL_MDIV_NT_                                   BIT(7)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_0_ICTL_PLL_KEEPALIVE_DISABLE_A                        BIT(6)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_0_ICTL_PLL_REFDIV_NT_                                 BIT(5)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_0_ICTL_PLL_CAL_CLR_A                                  BIT(4)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_0_ICTL_PLL_DISCONNECT_A                               BIT(3)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_0_ICTL_PLL_MODDIV_NT_                                 BIT(2)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_0_ICTL_PLL_FASTREF_EN_NT                              BIT(1)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_0_ICTL_PLL_FEFB_EN_NT                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_PLL_1_CRIT_CTRL_0
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_IRST_PLL_POR_B_A                                            BIT(2)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_IPD_PLL_KEEPALIVE_B_NT                                      BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_OCTL_PLL_SYNTHLOCKSTATUS_A                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_PLL_1_PHASE_CTRL_0
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_CLKSLICE0_DIV_A_(x)                                (((x) & 0xFF) << 8)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_CLKSLICE1_DIV_A_(x)                                (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_PLL_1_PHASE_CTRL_1
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_CLKSLICE0_ENABLE_A                                 BIT(23)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_CLKSLICE1_ENABLE_A                                 BIT(22)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_CLKSLICE0_BYPASS_EN_A                              BIT(21)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_CLKSLICE1_BYPASS_EN_A                              BIT(20)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_CLKSLICE0_CKMUTE_EN_A                              BIT(19)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_CLKSLICE1_CKMUTE_EN_A                              BIT(18)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_CLKSLICE0_PHINC_A                                  BIT(17)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_CLKSLICE1_PHINC_A                                  BIT(16)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_CALVCOHSCOUNT_NT_(x)                               (((x) & 0xFF) << 8)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_CALVCOMEASCOUNT_NT_(x)                             (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_PLL_1_PLL_DIRECT_CTRL_0
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_FDIV_NT_(x)                                        (((x) & 0xFFFFFF) << 8)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_MDIV_NT_(x)                                        (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_PLL_1_PLL_DIRECT_CTRL_1
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_KEEPALIVE_DISABLE_A                                BIT(18)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_EXTFB_EN_NT                                        BIT(17)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_REFDIV_NT_(x)                                      (((x) & 0x3F) << 11)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_CAL_CLR_A                                          BIT(10)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_DISCONNECT_A                                       BIT(9)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_MODDIV_NT_(x)                                      (((x) & 0xF) << 5)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_OCTL_PLL_CLKSLICE0_STATUS_A                                 BIT(4)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_OCTL_PLL_CLKSLICE1_STATUS_A                                 BIT(3)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_OCTL_PLL_DISCONNECT_STATUS_A                                BIT(2)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_FASTREF_EN_NT                                      BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_FEFB_EN_NT                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_PLL_1_PLL_DIRECT_CTRL_JTAG
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_PLL_1_ICTL_PLL_JTAGID_NT_(x)                                      (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_PLL_1_REG_SEL_CFG_0
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_1_IRST_PLL_POR_B_A                                    BIT(13)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_1_IPD_PLL_KEEPALIVE_B_NT                              BIT(12)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_1_ICTL_PLL_CLKSLICE0_DIV_A_                           BIT(11)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_1_ICTL_PLL_CLKSLICE0_ENABLE_A                         BIT(10)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_1_ICTL_PLL_CALVCOHSCOUNT_NT_                          BIT(9)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_1_ICTL_PLL_CALVCOMEASCOUNT_NT_                        BIT(8)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_1_ICTL_PLL_MDIV_NT_                                   BIT(7)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_1_ICTL_PLL_KEEPALIVE_DISABLE_A                        BIT(6)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_1_ICTL_PLL_REFDIV_NT_                                 BIT(5)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_1_ICTL_PLL_CAL_CLR_A                                  BIT(4)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_1_ICTL_PLL_DISCONNECT_A                               BIT(3)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_1_ICTL_PLL_MODDIV_NT_                                 BIT(2)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_1_ICTL_PLL_FASTREF_EN_NT                              BIT(1)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_PLL_1_ICTL_PLL_FEFB_EN_NT                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_CZPLL_CRIT_CTRL_0
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_IRST_PLL_POR_B_A                                            BIT(2)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_IPD_PLL_KEEPALIVE_B_NT                                      BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_OCTL_PLL_SYNTHLOCKSTATUS_A                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_CZPLL_PHASE_CTRL_0
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_CLKSLICE0_DIV_A_(x)                                (((x) & 0xFF) << 8)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_CLKSLICE1_DIV_A_(x)                                (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_CZPLL_PHASE_CTRL_1
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_CLKSLICE0_ENABLE_A                                 BIT(23)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_CLKSLICE1_ENABLE_A                                 BIT(22)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_CLKSLICE0_BYPASS_EN_A                              BIT(21)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_CLKSLICE1_BYPASS_EN_A                              BIT(20)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_CLKSLICE0_CKMUTE_EN_A                              BIT(19)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_CLKSLICE1_CKMUTE_EN_A                              BIT(18)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_CLKSLICE0_PHINC_A                                  BIT(17)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_CLKSLICE1_PHINC_A                                  BIT(16)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_CALVCOHSCOUNT_NT_(x)                               (((x) & 0xFF) << 8)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_CALVCOMEASCOUNT_NT_(x)                             (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_CZPLL_PLL_DIRECT_CTRL_0
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_FDIV_NT_(x)                                        (((x) & 0xFFFFFF) << 8)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_MDIV_NT_(x)                                        (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_CZPLL_PLL_DIRECT_CTRL_1
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_KEEPALIVE_DISABLE_A                                BIT(18)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_EXTFB_EN_NT                                        BIT(17)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_REFDIV_NT_(x)                                      (((x) & 0x3F) << 11)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_CAL_CLR_A                                          BIT(10)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_DISCONNECT_A                                       BIT(9)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_MODDIV_NT_(x)                                      (((x) & 0xF) << 5)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_OCTL_PLL_CLKSLICE0_STATUS_A                                 BIT(4)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_OCTL_PLL_CLKSLICE1_STATUS_A                                 BIT(3)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_OCTL_PLL_DISCONNECT_STATUS_A                                BIT(2)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_FASTREF_EN_NT                                      BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_FEFB_EN_NT                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_CZPLL_PLL_DIRECT_CTRL_JTAG
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_CZPLL_ICTL_PLL_JTAGID_NT_(x)                                      (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_CZPLL_REG_SEL_CFG_0
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_CZPLL_IRST_PLL_POR_B_A                                    BIT(5)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_CZPLL_IPD_PLL_KEEPALIVE_B_NT                              BIT(4)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_CZPLL_ICTL_PLL_CLKSLICE0_ENABLE_A                         BIT(3)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_CZPLL_ICTL_PLL_CLKSLICE1_ENABLE_A                         BIT(2)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_CZPLL_ICTL_PLL_KEEPALIVE_DISABLE_A                        BIT(1)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_CZPLL_ICTL_PLL_DISCONNECT_A                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_EFUSE_0_PHY_EFUSE_OPT
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_EFUSE_0_ICLKGATEDT                                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_EFUSE_1_PHY_EFUSE_OPT
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_EFUSE_1_ICLKGATEDT                                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_EFUSE_2_PHY_EFUSE_OPT
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_EFUSE_2_ICLKGATEDT                                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO_CFG_0
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO0P84_PD                                            BIT(15)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO0P84_SHPT_PD                                       BIT(14)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO0P84_SHT_CTRL                                      BIT(13)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO0P84_V(x)                                          (((x) & 0x1F) << 8)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO1P2_PD                                             BIT(7)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO1P2_SHPT_PD                                        BIT(6)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO1P2_SHT_CTRL                                       BIT(5)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO1P2_V(x)                                           (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO_CFG_1
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO_BG_PD                                             BIT(10)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO_BG_RBIAS_EN                                       BIT(9)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO_CON_BG                                            BIT(8)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO1P2PLL_PD                                          BIT(7)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO1P2PLL_SHPT_PD                                     BIT(6)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO1P2PLL_SHT_CTRL                                    BIT(5)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO1P2PLL_V(x)                                        (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO_CFG_2
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO_CHOP(x)                                           (((x) & 0xFF) << 20)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO_EFFUSE_HVM_VCCF_SW_EN                             BIT(19)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO_EFFUSE_HVM_VCCFHV_SW_EN                           BIT(18)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO_EFFUSE_IFP_VCCF_SW_EN                             BIT(17)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO_EFFUSE_IFP_VCCFHV_SW_EN                           BIT(16)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO1P05_HVM_PD                                        BIT(15)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO1P05_HVM_SHPT_PD                                   BIT(14)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO1P05_HVM_SHT_CTRL                                  BIT(13)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO1P05_HVM_V(x)                                      (((x) & 0x1F) << 8)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO1P05_IFP_PD                                        BIT(7)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO1P05_IFP_SHPT_PD                                   BIT(6)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO1P05_IFP_SHT_CTRL                                  BIT(5)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO1P05_IFP_V(x)                                      (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO_CFG_3
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO2P4_IFP_PD                                         BIT(7)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO2P4_IFP_SHPT_PD                                    BIT(6)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO2P4_IFP_SHT_CTRL                                   BIT(5)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO2P4_IFP_V(x)                                       (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_LDO_RCO100M_CLK_CTRL_0
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_RTC100M_EN                                            BIT(10)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_RTC100M_RSTB                                          BIT(9)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_RTC100M_RC_C(x)                                       (((x) & 0x1FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_LDO_RCO100M_PWR_CTRL_0
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_LDO_REG(x)                                            (((x) & 0x1F) << 4)
#define BIT_ANLG_PHY_G2_ANALOG_LDO_RCO100M_RTC100M_I_C(x)                                        (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_LDO_RCO100M_REG_SEL_CFG_0
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_LDO0P84_PD                                    BIT(18)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_LDO0P84_V                                     BIT(17)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_LDO1P2_PD                                     BIT(16)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_LDO1P2_V                                      BIT(15)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_LDO1P2PLL_PD                                  BIT(14)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_LDO1P2PLL_V                                   BIT(13)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_LDO_EFFUSE_HVM_VCCF_SW_EN                     BIT(12)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_LDO_EFFUSE_HVM_VCCFHV_SW_EN                   BIT(11)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_LDO_EFFUSE_IFP_VCCF_SW_EN                     BIT(10)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_LDO_EFFUSE_IFP_VCCFHV_SW_EN                   BIT(9)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_LDO1P05_HVM_PD                                BIT(8)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_LDO1P05_IFP_PD                                BIT(7)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_LDO1P05_IFP_V                                 BIT(6)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_LDO2P4_IFP_PD                                 BIT(5)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_LDO2P4_IFP_V                                  BIT(4)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_RTC100M_EN                                    BIT(3)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_RTC100M_RSTB                                  BIT(2)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_RTC100M_RC_C                                  BIT(1)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_LDO_RCO100M_LDO_REG                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_PWR_CTRL_0
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_REC_26MHZ_0_BUF_PD                                         BIT(15)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_REC_32MHZ_0_BUF_PD                                         BIT(14)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_REC_32MHZ_1_BUF_PD                                         BIT(13)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_PD                                                   BIT(12)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_PD                                                   BIT(11)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_PD                                                   BIT(10)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_PD                                                   BIT(9)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_PD                                                   BIT(8)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_GPLL_PD                                                    BIT(7)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_PD                                                   BIT(6)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_M_AAPC_PD                                                  BIT(5)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_S_AAPC_PD                                                  BIT(4)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_BB_BG_PD                                                   BIT(3)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_REC_26MHZ_0_CUR_SEL                                        BIT(2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_REC_32MHZ_0_CUR_SEL                                        BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_REC_32MHZ_1_CUR_SEL                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CFG_0
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_PROBE_SEL(x)                                               (((x) & 0x3F) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_SINDRV_ENA                                                 BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_SINDRV_ENA_SQUARE                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_PLL_TEST_0
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_ANALOG_TESTMUX(x)                                          (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_ANALOG_PLL_RESERVED(x)                                     (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_PLL_CLKCTL_0
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TEST_CLK_EN                                                BIT(3)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TEST_CLK_OD                                                BIT(2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TEST_CLK_DIV(x)                                            (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_0
// Register Offset : 0x008C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_RST                                                  BIT(18)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_N(x)                                                 (((x) & 0x7F) << 11)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_LPF(x)                                               (((x) & 0x7) << 8)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_VSET(x)                                              (((x) & 0x7) << 5)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_REF_SEL(x)                                           (((x) & 0x3) << 3)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_IBIAS(x)                                             (((x) & 0x3) << 1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_LOCK_DONE                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_MODU_CTRL_0
// Register Offset : 0x0090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_NINT(x)                                              (((x) & 0x7F) << 25)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_KINT(x)                                              (((x) & 0x7FFFFF) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_SDM_EN                                               BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_MOD_EN                                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_DIV_CTRL_0
// Register Offset : 0x0094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_DIV_S                                                BIT(23)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_DIV1_EN                                              BIT(22)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_26M_DIV(x)                                           (((x) & 0x3F) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_RESERVED(x)                                          (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_PLL_BIST_0
// Register Offset : 0x0098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_BIST_EN                                              BIT(24)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_BIST_CTRL(x)                                         (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_BIST_CNT(x)                                          (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_1
// Register Offset : 0x009C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_RST                                                  BIT(18)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_IBIAS(x)                                             (((x) & 0x3) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_N(x)                                                 (((x) & 0x7F) << 9)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_LPF(x)                                               (((x) & 0x7) << 6)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_VSET(x)                                              (((x) & 0x7) << 3)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_REF_SEL(x)                                           (((x) & 0x3) << 1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_LOCK_DONE                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_MODU_CTRL_1
// Register Offset : 0x00A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_NINT(x)                                              (((x) & 0x7F) << 25)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_KINT(x)                                              (((x) & 0x7FFFFF) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_SDM_EN                                               BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_MOD_EN                                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_DIV_CTRL_1
// Register Offset : 0x00A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_DIV_S                                                BIT(23)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_DIV1_EN                                              BIT(22)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_26M_DIV(x)                                           (((x) & 0x3F) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_RESERVED(x)                                          (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_PLL_BIST_1
// Register Offset : 0x00A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_BIST_EN                                              BIT(24)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_BIST_CTRL(x)                                         (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_BIST_CNT(x)                                          (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_2
// Register Offset : 0x00AC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_RST                                                  BIT(28)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_IBIAS(x)                                             (((x) & 0x3) << 26)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_N(x)                                                 (((x) & 0x7F) << 19)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_LPF(x)                                               (((x) & 0x7) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_VSET(x)                                              (((x) & 0x7) << 13)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_REF_SEL(x)                                           (((x) & 0x7) << 10)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_RESERVED(x)                                          (((x) & 0xFF) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_LOCK_DONE                                            BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_CLKOUT_EN                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_MODU_CTRL_2
// Register Offset : 0x00B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_NINT(x)                                              (((x) & 0x7F) << 25)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_KINT(x)                                              (((x) & 0x7FFFFF) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_SDM_EN                                               BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_MOD_EN                                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_DIV_CTRL_2
// Register Offset : 0x00B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_DIV_S                                                BIT(5)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_DIV1_EN                                              BIT(4)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_DIV2_EN                                              BIT(3)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_DIV3_EN                                              BIT(2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_DIV5_EN                                              BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_DIV7_EN                                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_PLL_BIST_2
// Register Offset : 0x00B8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_BIST_EN                                              BIT(24)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_BIST_CTRL(x)                                         (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_BIST_CNT(x)                                          (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_3
// Register Offset : 0x00BC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_RST                                                  BIT(28)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_IBIAS(x)                                             (((x) & 0x3) << 26)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_N(x)                                                 (((x) & 0x7F) << 19)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_LPF(x)                                               (((x) & 0x7) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_VSET(x)                                              (((x) & 0x7) << 13)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_REF_SEL(x)                                           (((x) & 0x7) << 10)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_RESERVED(x)                                          (((x) & 0xFF) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_CLKOUT_EN                                            BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_LOCK_DONE                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_MODU_CTRL_3
// Register Offset : 0x00C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_NINT(x)                                              (((x) & 0x7F) << 25)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_KINT(x)                                              (((x) & 0x7FFFFF) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_SDM_EN                                               BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_MOD_EN                                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_DIV_CTRL_3
// Register Offset : 0x00C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_DIV_S                                                BIT(4)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_DIV1_EN                                              BIT(3)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_DIV2_EN                                              BIT(2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_DIV3_EN                                              BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_DIV5_EN                                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_PLL_BIST_3
// Register Offset : 0x00C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_BIST_EN                                              BIT(24)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_BIST_CTRL(x)                                         (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_BIST_CNT(x)                                          (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_4
// Register Offset : 0x00CC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_RST                                                  BIT(28)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_IBIAS(x)                                             (((x) & 0x3) << 26)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_N(x)                                                 (((x) & 0x7F) << 19)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_LPF(x)                                               (((x) & 0x7) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_VSET(x)                                              (((x) & 0x7) << 13)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_REF_SEL(x)                                           (((x) & 0x7) << 10)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_RESERVED(x)                                          (((x) & 0xFF) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_CLKOUT_EN                                            BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_LOCK_DONE                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_MODU_CTRL_4
// Register Offset : 0x00D0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_NINT(x)                                              (((x) & 0x7F) << 25)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_KINT(x)                                              (((x) & 0x7FFFFF) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_SDM_EN                                               BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_MOD_EN                                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_DIV_CTRL_4
// Register Offset : 0x00D4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_DIV_S                                                BIT(4)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_DIV1_EN                                              BIT(3)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_DIV2_EN                                              BIT(2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_DIV3_EN                                              BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_DIV5_EN                                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_PLL_BIST_4
// Register Offset : 0x00D8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_BIST_EN                                              BIT(24)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_BIST_CTRL(x)                                         (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL1_BIST_CNT(x)                                          (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_5
// Register Offset : 0x00DC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_GPLL_CLKOUT_EN                                             BIT(26)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_GPLL_RST                                                   BIT(25)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_GPLL_N(x)                                                  (((x) & 0x7F) << 18)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_GPLL_IBIAS(x)                                              (((x) & 0x3) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_GPLL_LPF(x)                                                (((x) & 0x7) << 13)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_GPLL_VSET(x)                                               (((x) & 0x7) << 10)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_GPLL_REF_SEL                                               BIT(9)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_GPLL_RESERVED(x)                                           (((x) & 0xFF) << 1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_GPLL_LOCK_DONE                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_MODU_CTRL_5
// Register Offset : 0x00E0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_GPLL_NINT(x)                                               (((x) & 0x7F) << 25)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_GPLL_KINT(x)                                               (((x) & 0x7FFFFF) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_GPLL_SDM_EN                                                BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_GPLL_MOD_EN                                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_DIV_CTRL_5
// Register Offset : 0x00E4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_GPLL_DIV_S                                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_PLL_BIST_5
// Register Offset : 0x00E8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_GPLL_BIST_EN                                               BIT(24)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_GPLL_BIST_CTRL(x)                                          (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_GPLL_BIST_CNT(x)                                           (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_6
// Register Offset : 0x00EC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_CLKOUT_EN                                            BIT(26)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_RST                                                  BIT(25)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_N(x)                                                 (((x) & 0x7F) << 18)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_IBIAS(x)                                             (((x) & 0x3) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_LPF(x)                                               (((x) & 0x7) << 13)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_VSET(x)                                              (((x) & 0x7) << 10)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_REF_SEL                                              BIT(9)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_RESERVED(x)                                          (((x) & 0xFF) << 1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_LOCK_DONE                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_MODU_CTRL_6
// Register Offset : 0x00F0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_NINT(x)                                              (((x) & 0x7F) << 25)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_KINT(x)                                              (((x) & 0x7FFFFF) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_SDM_EN                                               BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_MOD_EN                                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_DIV_CTRL_6
// Register Offset : 0x00F4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_POSTDIV                                              BIT(10)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_DIV_S                                                BIT(9)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_DIV1_EN                                              BIT(8)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_DIV32_EN                                             BIT(7)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_CLKUFS_EN                                            BIT(6)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_CLKUFS_DIV(x)                                        (((x) & 0x3F))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_PLL_BIST_6
// Register Offset : 0x00F8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_BIST_EN                                              BIT(24)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_BIST_CTRL(x)                                         (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_BIST_CNT(x)                                          (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_MSTAPC_CTL_0
// Register Offset : 0x00FC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_M_AAPC_SEL                                                 BIT(20)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_M_AAPC_D(x)                                                (((x) & 0x3FFF) << 6)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_M_AAPC_LOW_V_CON                                           BIT(5)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_M_AAPC_BPRES                                               BIT(4)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_M_APCOUT_SEL(x)                                            (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_M_AAPC_RESERVED(x)                                         (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_SLVAPC_CTL_0
// Register Offset : 0x0100
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_S_AAPC_SEL                                                 BIT(20)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_S_AAPC_LOW_V_CON                                           BIT(19)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_S_AAPC_D(x)                                                (((x) & 0x3FFF) << 5)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_S_AAPC_BPRES                                               BIT(4)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_S_APCOUT_SEL(x)                                            (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_S_AAPC_RESERVED(x)                                         (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_GAIN_CTL_0
// Register Offset : 0x0104
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_AAPC_G0(x)                                                 (((x) & 0x3) << 4)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_AAPC_G1(x)                                                 (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_AAPC_G2(x)                                                 (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_BG_TOP_0
// Register Offset : 0x0108
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_BB_BG_RBIAS_EN                                             BIT(17)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_BB_CON_BG                                                  BIT(16)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_ANA_BB_RESERVED(x)                                         (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK26M_CTL_0
// Register Offset : 0x010C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CLK26M_SINEO_DSI_EN                                        BIT(13)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CLK26MHZ_U3_EN                                             BIT(12)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CLK26MHZ_UFS_EN                                            BIT(11)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CLK26MHZ_UFS_SEL                                           BIT(10)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_26M_SEL                                              BIT(9)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_26M_SEL                                              BIT(8)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_SINE_DRV_SEL(x)                                            (((x) & 0x3) << 6)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_SR_TRIM(x)                                                 (((x) & 0xF) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_MPLL2_REF_SEL(x)                                           (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_WRAP_GLUE_CTRL
// Register Offset : 0x0110
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_PD_SEL                                               BIT(3)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_RST_SEL                                              BIT(2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_PD_SEL                                               BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL1_RST_SEL                                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_AAPC_TEST
// Register Offset : 0x0114
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_AAPC_STEP_SEL                                              BIT(30)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_AAPC_MAX_RANGE(x)                                          (((x) & 0x3FFF) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_AAPC_MIN_RANGE(x)                                          (((x) & 0x3FFF) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_AAPC_RSTN                                                  BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_AAPC_GEN_SEL                                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_REG_SEL_CFG_0
// Register Offset : 0x0118
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_REC_26MHZ_0_BUF_PD                                 BIT(31)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_REC_32MHZ_0_BUF_PD                                 BIT(30)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_REC_32MHZ_1_BUF_PD                                 BIT(29)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_PD                                           BIT(28)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL1_PD                                           BIT(27)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_TWPLL_PD                                           BIT(26)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_LPLL0_PD                                           BIT(25)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_LPLL1_PD                                           BIT(24)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_GPLL_PD                                            BIT(23)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_CPPLL_PD                                           BIT(22)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_M_AAPC_PD                                          BIT(21)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_S_AAPC_PD                                          BIT(20)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_BB_BG_PD                                           BIT(19)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_ANALOG_TESTMUX                                     BIT(18)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_ANALOG_PLL_RESERVED                                BIT(17)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_RST                                          BIT(16)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_N                                            BIT(15)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_LPF                                          BIT(14)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_VSET                                         BIT(13)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_REF_SEL                                      BIT(12)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_IBIAS                                        BIT(11)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_NINT                                         BIT(10)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_KINT                                         BIT(9)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_SDM_EN                                       BIT(8)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_MOD_EN                                       BIT(7)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_DIV_S                                        BIT(6)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_DIV1_EN                                      BIT(5)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_26M_DIV                                      BIT(4)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_RESERVED                                     BIT(3)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_BIST_EN                                      BIT(2)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_BIST_CTRL                                    BIT(1)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL1_RST                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_REG_SEL_CFG_1
// Register Offset : 0x011C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL1_IBIAS                                        BIT(31)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL1_N                                            BIT(30)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL1_LPF                                          BIT(29)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL1_VSET                                         BIT(28)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL1_REF_SEL                                      BIT(27)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL1_NINT                                         BIT(26)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL1_KINT                                         BIT(25)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL1_SDM_EN                                       BIT(24)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL1_MOD_EN                                       BIT(23)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL1_DIV_S                                        BIT(22)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL1_DIV1_EN                                      BIT(21)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL1_26M_DIV                                      BIT(20)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL1_RESERVED                                     BIT(19)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL1_BIST_EN                                      BIT(18)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL1_BIST_CTRL                                    BIT(17)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_TWPLL_RST                                          BIT(16)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_TWPLL_REF_SEL                                      BIT(15)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_TWPLL_CLKOUT_EN                                    BIT(14)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_TWPLL_DIV2_EN                                      BIT(13)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_TWPLL_DIV3_EN                                      BIT(12)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_TWPLL_DIV5_EN                                      BIT(11)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_LPLL0_RST                                          BIT(10)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_LPLL0_REF_SEL                                      BIT(9)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_LPLL0_CLKOUT_EN                                    BIT(8)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_LPLL0_DIV2_EN                                      BIT(7)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_LPLL0_DIV3_EN                                      BIT(6)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_LPLL0_DIV5_EN                                      BIT(5)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_LPLL1_RST                                          BIT(4)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_LPLL1_REF_SEL                                      BIT(3)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_LPLL1_CLKOUT_EN                                    BIT(2)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_LPLL1_DIV2_EN                                      BIT(1)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_LPLL1_DIV3_EN                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_REG_SEL_CFG_2
// Register Offset : 0x0120
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_LPLL1_DIV5_EN                                      BIT(21)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_GPLL_CLKOUT_EN                                     BIT(20)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_GPLL_RST                                           BIT(19)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_CPPLL_CLKOUT_EN                                    BIT(18)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_CPPLL_RST                                          BIT(17)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_CPPLL_DIV1_EN                                      BIT(16)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_M_AAPC_SEL                                         BIT(15)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_M_AAPC_D                                           BIT(14)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_M_AAPC_LOW_V_CON                                   BIT(13)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_M_AAPC_BPRES                                       BIT(12)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_M_APCOUT_SEL                                       BIT(11)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_M_AAPC_RESERVED                                    BIT(10)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_S_AAPC_SEL                                         BIT(9)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_S_AAPC_LOW_V_CON                                   BIT(8)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_S_AAPC_D                                           BIT(7)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_S_AAPC_BPRES                                       BIT(6)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_S_APCOUT_SEL                                       BIT(5)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_S_AAPC_RESERVED                                    BIT(4)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_AAPC_G0                                            BIT(3)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_AAPC_G1                                            BIT(2)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_AAPC_G2                                            BIT(1)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_ANA_BB_RESERVED                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_DUMY_RW0
// Register Offset : 0x0124
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_DUMMY_RW0(x)                                               (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_DUMY_RW1
// Register Offset : 0x0128
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_DUMMY_RW1(x)                                               (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_DUMY_RO0
// Register Offset : 0x012C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_DUMMY_RO0(x)                                               (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_BB_TOP_DUMY_RO1
// Register Offset : 0x0130
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_BB_TOP_DUMMY_RO1(x)                                               (((x) & 0xFFFFFFFF))


#endif // _ANLG_PHY_G2_REG_H
