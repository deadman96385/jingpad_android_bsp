/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _ANLG_PHY_G3_REG_H
#define _ANLG_PHY_G3_REG_H

#define CTL_BASE_ANLG_PHY_G3 SPRD_ANLG_PHY_G3


#define REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_CTRL0          ( CTL_BASE_ANLG_PHY_G3 + 0x0000 )
#define REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_CTRL1          ( CTL_BASE_ANLG_PHY_G3 + 0x0004 )
#define REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_CTRL2          ( CTL_BASE_ANLG_PHY_G3 + 0x0008 )
#define REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_BIST_CTRL      ( CTL_BASE_ANLG_PHY_G3 + 0x000C )
#define REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_CTRL0          ( CTL_BASE_ANLG_PHY_G3 + 0x0010 )
#define REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_CTRL1          ( CTL_BASE_ANLG_PHY_G3 + 0x0014 )
#define REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_CTRL2          ( CTL_BASE_ANLG_PHY_G3 + 0x0018 )
#define REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_CTRL3          ( CTL_BASE_ANLG_PHY_G3 + 0x001C )
#define REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_BIST_CTRL      ( CTL_BASE_ANLG_PHY_G3 + 0x0020 )
#define REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_DPLL_CTRL      ( CTL_BASE_ANLG_PHY_G3 + 0x0024 )
#define REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_REG_SEL_CFG_0       ( CTL_BASE_ANLG_PHY_G3 + 0x0028 )
#define REG_ANLG_PHY_G3_ANALOG_THM1_THM1_CTRL_0              ( CTL_BASE_ANLG_PHY_G3 + 0x002C )
#define REG_ANLG_PHY_G3_ANALOG_THM1_THM1_CTRL_1              ( CTL_BASE_ANLG_PHY_G3 + 0x0030 )
#define REG_ANLG_PHY_G3_ANALOG_THM1_REG_SEL_CFG_0            ( CTL_BASE_ANLG_PHY_G3 + 0x0034 )

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_CTRL0
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_N(x)                                     (((x) & 0x7FF) << 18)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_IBIAS(x)                                 (((x) & 0x3) << 16)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_LPF(x)                                   (((x) & 0x7) << 13)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_SDM_EN                                   BIT(12)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_MOD_EN                                   BIT(11)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_DIV_S                                    BIT(10)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_RESERVED(x)                              (((x) & 0xFF) << 2)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_CLKOUT_EN                                BIT(1)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_LOCK_DONE                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_CTRL1
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_NINT(x)                                  (((x) & 0x7F) << 25)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_KINT(x)                                  (((x) & 0x7FFFFF) << 2)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_PD                                       BIT(1)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_RST                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_CTRL2
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_CCS_CTRL(x)                              (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_BIST_CTRL
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_BIST_EN                                  BIT(24)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_BIST_CTRL(x)                             (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_DPLL_BIST_CNT(x)                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_CTRL0
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_N(x)                                     (((x) & 0x7FF) << 8)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_IBIAS(x)                                 (((x) & 0x3) << 6)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_LPF(x)                                   (((x) & 0x7) << 3)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_SDM_EN                                   BIT(2)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_MOD_EN                                   BIT(1)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_DIV_S                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_CTRL1
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_NINT(x)                                  (((x) & 0x7F) << 25)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_KINT(x)                                  (((x) & 0x7FFFFF) << 2)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_PD                                       BIT(1)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_RST                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_CTRL2
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_RESERVED(x)                              (((x) & 0xFF) << 3)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_POSTDIV                                  BIT(2)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_CLKOUT_EN                                BIT(1)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_LOCK_DONE                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_CTRL3
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_CCS_CTRL(x)                              (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_BIST_CTRL
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_BIST_EN                                  BIT(24)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_BIST_CTRL(x)                             (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_BIST_CNT(x)                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_MPLL_DPLL_CTRL
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_ANALOG_PLL_RESERVED(x)                        (((x) & 0x7FF) << 2)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_TEST_CLK_EN                                   BIT(1)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_DPLL_TEST_SEL                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_DPLL_REG_SEL_CFG_0
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_DPLL_N                                BIT(31)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_DPLL_IBIAS                            BIT(30)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_DPLL_LPF                              BIT(29)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_DPLL_SDM_EN                           BIT(28)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_DPLL_MOD_EN                           BIT(27)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_DPLL_DIV_S                            BIT(26)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_DPLL_RESERVED                         BIT(25)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_DPLL_CLKOUT_EN                        BIT(24)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_DPLL_NINT                             BIT(23)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_DPLL_KINT                             BIT(22)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_DPLL_PD                               BIT(21)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_DPLL_RST                              BIT(20)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_DPLL_CCS_CTRL                         BIT(19)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_DPLL_BIST_EN                          BIT(18)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_DPLL_BIST_CTRL                        BIT(17)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_MPLL_N                                BIT(16)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_MPLL_IBIAS                            BIT(15)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_MPLL_LPF                              BIT(14)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_MPLL_SDM_EN                           BIT(13)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_MPLL_MOD_EN                           BIT(12)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_MPLL_DIV_S                            BIT(11)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_MPLL_NINT                             BIT(10)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_MPLL_KINT                             BIT(9)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_MPLL_PD                               BIT(8)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_MPLL_RST                              BIT(7)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_MPLL_RESERVED                         BIT(6)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_MPLL_POSTDIV                          BIT(5)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_MPLL_CLKOUT_EN                        BIT(4)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_MPLL_CCS_CTRL                         BIT(3)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_MPLL_BIST_EN                          BIT(2)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_MPLL_BIST_CTRL                        BIT(1)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_DPLL_ANALOG_PLL_RESERVED                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_THM1_THM1_CTRL_0
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_THM1_THM1_PD                                            BIT(23)
#define BIT_ANLG_PHY_G3_ANALOG_THM1_THM1_RSTN                                          BIT(22)
#define BIT_ANLG_PHY_G3_ANALOG_THM1_THM1_RUN                                           BIT(21)
#define BIT_ANLG_PHY_G3_ANALOG_THM1_THM1_CALI_EN                                       BIT(20)
#define BIT_ANLG_PHY_G3_ANALOG_THM1_THM1_ITUNE(x)                                      (((x) & 0xF) << 16)
#define BIT_ANLG_PHY_G3_ANALOG_THM1_THM1_RESERVED(x)                                   (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_THM1_THM1_CTRL_1
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_THM1_THM1_DATA(x)                                       (((x) & 0xFF) << 1)
#define BIT_ANLG_PHY_G3_ANALOG_THM1_THM1_VALID                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_THM1_REG_SEL_CFG_0
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_THM1_THM1_PD                                    BIT(5)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_THM1_THM1_RSTN                                  BIT(4)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_THM1_THM1_RUN                                   BIT(3)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_THM1_THM1_CALI_EN                               BIT(2)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_THM1_THM1_ITUNE                                 BIT(1)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_THM1_THM1_RESERVED                              BIT(0)


#endif // _ANLG_PHY_G3_REG_H
