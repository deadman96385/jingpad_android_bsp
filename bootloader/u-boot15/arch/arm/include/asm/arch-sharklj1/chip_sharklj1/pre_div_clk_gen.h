/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _PRE_DIV_CLK_GEN_REG_H
#define _PRE_DIV_CLK_GEN_REG_H

#define CTL_BASE_PRE_DIV_CLK_GEN 0x402D0000


#define REG_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG                 ( CTL_BASE_PRE_DIV_CLK_GEN + 0x0020 )
#define REG_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG                  ( CTL_BASE_PRE_DIV_CLK_GEN + 0x0024 )
#define REG_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG               ( CTL_BASE_PRE_DIV_CLK_GEN + 0x0028 )
#define REG_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG                    ( CTL_BASE_PRE_DIV_CLK_GEN + 0x002C )
#define REG_PRE_DIV_CLK_GEN_DIV_EN_SEL1_CFG                    ( CTL_BASE_PRE_DIV_CLK_GEN + 0x0030 )
#define REG_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG                 ( CTL_BASE_PRE_DIV_CLK_GEN + 0x0034 )
#define REG_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL1_CFG                 ( CTL_BASE_PRE_DIV_CLK_GEN + 0x0038 )
#define REG_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG                   ( CTL_BASE_PRE_DIV_CLK_GEN + 0x003C )
#define REG_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG                   ( CTL_BASE_PRE_DIV_CLK_GEN + 0x0040 )
#define REG_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG                   ( CTL_BASE_PRE_DIV_CLK_GEN + 0x0044 )
#define REG_PRE_DIV_CLK_GEN_GATE_EN_SEL3_CFG                   ( CTL_BASE_PRE_DIV_CLK_GEN + 0x0048 )
#define REG_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG                ( CTL_BASE_PRE_DIV_CLK_GEN + 0x004C )
#define REG_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG                ( CTL_BASE_PRE_DIV_CLK_GEN + 0x0050 )
#define REG_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG                ( CTL_BASE_PRE_DIV_CLK_GEN + 0x0054 )
#define REG_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL3_CFG                ( CTL_BASE_PRE_DIV_CLK_GEN + 0x0058 )
#define REG_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG          ( CTL_BASE_PRE_DIV_CLK_GEN + 0x005C )
#define REG_PRE_DIV_CLK_GEN_MONITOR_WAIT_EN_STATUS0_CFG        ( CTL_BASE_PRE_DIV_CLK_GEN + 0x0060 )
#define REG_PRE_DIV_CLK_GEN_MONITOR_DIV_AUTO_EN_STATUS00_CFG   ( CTL_BASE_PRE_DIV_CLK_GEN + 0x0064 )
#define REG_PRE_DIV_CLK_GEN_MONITOR_DIV_AUTO_EN_STATUS10_CFG   ( CTL_BASE_PRE_DIV_CLK_GEN + 0x0068 )
#define REG_PRE_DIV_CLK_GEN_MONITOR_GATE_AUTO_EN_STATUS00_CFG  ( CTL_BASE_PRE_DIV_CLK_GEN + 0x006C )
#define REG_PRE_DIV_CLK_GEN_MONITOR_GATE_AUTO_EN_STATUS10_CFG  ( CTL_BASE_PRE_DIV_CLK_GEN + 0x0070 )
#define REG_PRE_DIV_CLK_GEN_MONITOR_GATE_AUTO_EN_STATUS20_CFG  ( CTL_BASE_PRE_DIV_CLK_GEN + 0x0074 )
#define REG_PRE_DIV_CLK_GEN_MONITOR_GATE_AUTO_EN_STATUS30_CFG  ( CTL_BASE_PRE_DIV_CLK_GEN + 0x0078 )

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG
// Register Offset : 0x0020
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG_GPLL_SOFT_CNT_DONE                                                BIT(16)
#define BIT_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG_CPPLL_468M_SOFT_CNT_DONE                                          BIT(15)
#define BIT_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG_CPPLL_14M_SOFT_CNT_DONE                                           BIT(14)
#define BIT_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG_TWPLL_1536M_SOFT_CNT_DONE                                         BIT(13)
#define BIT_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG_TWPLL_768M_SOFT_CNT_DONE                                          BIT(12)
#define BIT_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG_TWPLL_512M_SOFT_CNT_DONE                                          BIT(11)
#define BIT_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG_TWPLL_307M_SOFT_CNT_DONE                                          BIT(10)
#define BIT_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG_TWPLL_219M_SOFT_CNT_DONE                                          BIT(9)
#define BIT_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG_LTEPLL_1228M_SOFT_CNT_DONE                                        BIT(8)
#define BIT_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG_LTEPLL_614M_SOFT_CNT_DONE                                         BIT(7)
#define BIT_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG_LTEPLL_409M_SOFT_CNT_DONE                                         BIT(6)
#define BIT_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG_LTEPLL_245M_SOFT_CNT_DONE                                         BIT(5)
#define BIT_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG_RTC4M0_SOFT_CNT_DONE                                              BIT(4)
#define BIT_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG_XBUF0_SOFT_CNT_DONE                                               BIT(3)
#define BIT_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG_XBUF1_SOFT_CNT_DONE                                               BIT(2)
#define BIT_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG_RPLL_780M_SOFT_CNT_DONE                                           BIT(1)
#define BIT_PRE_DIV_CLK_GEN_SOFT_CNT_DONE0_CFG_RPLL_26M_SOFT_CNT_DONE                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG
// Register Offset : 0x0024
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG_GPLL_WAIT_AUTO_GATE_SEL                                            BIT(16)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG_CPPLL_468M_WAIT_AUTO_GATE_SEL                                      BIT(15)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG_CPPLL_14M_WAIT_AUTO_GATE_SEL                                       BIT(14)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG_TWPLL_1536M_WAIT_AUTO_GATE_SEL                                     BIT(13)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG_TWPLL_768M_WAIT_AUTO_GATE_SEL                                      BIT(12)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG_TWPLL_512M_WAIT_AUTO_GATE_SEL                                      BIT(11)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG_TWPLL_307M_WAIT_AUTO_GATE_SEL                                      BIT(10)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG_TWPLL_219M_WAIT_AUTO_GATE_SEL                                      BIT(9)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG_LTEPLL_1228M_WAIT_AUTO_GATE_SEL                                    BIT(8)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG_LTEPLL_614M_WAIT_AUTO_GATE_SEL                                     BIT(7)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG_LTEPLL_409M_WAIT_AUTO_GATE_SEL                                     BIT(6)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG_LTEPLL_245M_WAIT_AUTO_GATE_SEL                                     BIT(5)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG_RTC4M0_WAIT_AUTO_GATE_SEL                                          BIT(4)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG_XBUF0_WAIT_AUTO_GATE_SEL                                           BIT(3)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG_XBUF1_WAIT_AUTO_GATE_SEL                                           BIT(2)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG_RPLL_780M_WAIT_AUTO_GATE_SEL                                       BIT(1)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG_RPLL_26M_WAIT_AUTO_GATE_SEL                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG
// Register Offset : 0x0028
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG_GPLL_WAIT_FORCE_EN                                              BIT(16)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG_CPPLL_468M_WAIT_FORCE_EN                                        BIT(15)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG_CPPLL_14M_WAIT_FORCE_EN                                         BIT(14)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG_TWPLL_1536M_WAIT_FORCE_EN                                       BIT(13)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG_TWPLL_768M_WAIT_FORCE_EN                                        BIT(12)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG_TWPLL_512M_WAIT_FORCE_EN                                        BIT(11)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG_TWPLL_307M_WAIT_FORCE_EN                                        BIT(10)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG_TWPLL_219M_WAIT_FORCE_EN                                        BIT(9)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG_LTEPLL_1228M_WAIT_FORCE_EN                                      BIT(8)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG_LTEPLL_614M_WAIT_FORCE_EN                                       BIT(7)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG_LTEPLL_409M_WAIT_FORCE_EN                                       BIT(6)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG_LTEPLL_245M_WAIT_FORCE_EN                                       BIT(5)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG_RTC4M0_WAIT_FORCE_EN                                            BIT(4)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG_XBUF0_WAIT_FORCE_EN                                             BIT(3)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG_XBUF1_WAIT_FORCE_EN                                             BIT(2)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG_RPLL_780M_WAIT_FORCE_EN                                         BIT(1)
#define BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SW_CTL0_CFG_RPLL_26M_WAIT_FORCE_EN                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG
// Register Offset : 0x002C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_GPLL_DIV_40M6_AUTO_GATE_SEL                                          BIT(31)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_LTEPLL_DIV_245M_122M9_AUTO_GATE_SEL                                  BIT(30)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_LTEPLL_DIV_245M_61M4_AUTO_GATE_SEL                                   BIT(29)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_LTEPLL_DIV_245M_30M7_AUTO_GATE_SEL                                   BIT(28)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_LTEPLL_DIV_409M_204M8_AUTO_GATE_SEL                                  BIT(27)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_LTEPLL_DIV_409M_102M4_AUTO_GATE_SEL                                  BIT(26)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_LTEPLL_DIV_614M_307M2_AUTO_GATE_SEL                                  BIT(25)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_LTEPLL_DIV_614M_153M6_AUTO_GATE_SEL                                  BIT(24)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_RPLL_DIV_780M_390M_AUTO_GATE_SEL                                     BIT(23)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_RPLL_DIV_780M_195M_AUTO_GATE_SEL                                     BIT(22)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_RPLL_DIV_780M_260M_AUTO_GATE_SEL                                     BIT(21)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_RPLL_DIV_780M_130M_AUTO_GATE_SEL                                     BIT(20)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_RPLL_DIV_780M_86M7_AUTO_GATE_SEL                                     BIT(19)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_RPLL_DIV_780M_43M3_AUTO_GATE_SEL                                     BIT(18)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_RPLL_DIV_780M_156M_AUTO_GATE_SEL                                     BIT(17)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_RPLL_DIV_780M_78M_AUTO_GATE_SEL                                      BIT(16)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_RPLL_DIV_780M_111M4_AUTO_GATE_SEL                                    BIT(15)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_RPLL_DIV_780M_55M7_AUTO_GATE_SEL                                     BIT(14)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_RTC_DIV_1K_AUTO_GATE_SEL                                             BIT(13)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_RTC4M0_DIV_2M_AUTO_GATE_SEL                                          BIT(12)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_TWPLL_DIV_1536M_170M7_AUTO_GATE_SEL                                  BIT(11)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_TWPLL_DIV_307M_153M6_AUTO_GATE_SEL                                   BIT(10)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_TWPLL_DIV_307M_76M8_AUTO_GATE_SEL                                    BIT(9)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_TWPLL_DIV_307M_38M4_AUTO_GATE_SEL                                    BIT(8)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_TWPLL_DIV_307M_102M4_AUTO_GATE_SEL                                   BIT(7)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_TWPLL_DIV_307M_51M2_AUTO_GATE_SEL                                    BIT(6)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_TWPLL_DIV_512M_256M_AUTO_GATE_SEL                                    BIT(5)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_TWPLL_DIV_512M_128M_AUTO_GATE_SEL                                    BIT(4)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_TWPLL_DIV_512M_64M_AUTO_GATE_SEL                                     BIT(3)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_TWPLL_DIV_512M_170M7_AUTO_GATE_SEL                                   BIT(2)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_TWPLL_DIV_512M_85M3_AUTO_GATE_SEL                                    BIT(1)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL0_CFG_TWPLL_DIV_768M_384M_AUTO_GATE_SEL                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_DIV_EN_SEL1_CFG
// Register Offset : 0x0030
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL1_CFG_TWPLL_DIV_768M_192M_AUTO_GATE_SEL                                    BIT(11)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL1_CFG_TWPLL_DIV_768M_96M_AUTO_GATE_SEL                                     BIT(10)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL1_CFG_TWPLL_DIV_768M_48M_AUTO_GATE_SEL                                     BIT(9)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL1_CFG_TWPLL_DIV_768M_24M_AUTO_GATE_SEL                                     BIT(8)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL1_CFG_TWPLL_DIV_768M_12M_AUTO_GATE_SEL                                     BIT(7)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL1_CFG_XBUF0_DIV_2M_AUTO_GATE_SEL                                           BIT(6)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL1_CFG_XBUF0_DIV_1M_AUTO_GATE_SEL                                           BIT(5)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL1_CFG_XBUF0_DIV_250K_AUTO_GATE_SEL                                         BIT(4)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL1_CFG_XBUF0_DIV_13M_AUTO_GATE_SEL                                          BIT(3)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL1_CFG_XBUF0_DIV_6M5_AUTO_GATE_SEL                                          BIT(2)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL1_CFG_XBUF0_DIV_8M7_AUTO_GATE_SEL                                          BIT(1)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SEL1_CFG_XBUF0_DIV_4M3_AUTO_GATE_SEL                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG
// Register Offset : 0x0034
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_GPLL_DIV_40M6_FORCE_EN                                            BIT(31)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_LTEPLL_DIV_245M_122M9_FORCE_EN                                    BIT(30)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_LTEPLL_DIV_245M_61M4_FORCE_EN                                     BIT(29)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_LTEPLL_DIV_245M_30M7_FORCE_EN                                     BIT(28)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_LTEPLL_DIV_409M_204M8_FORCE_EN                                    BIT(27)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_LTEPLL_DIV_409M_102M4_FORCE_EN                                    BIT(26)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_LTEPLL_DIV_614M_307M2_FORCE_EN                                    BIT(25)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_LTEPLL_DIV_614M_153M6_FORCE_EN                                    BIT(24)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_RPLL_DIV_780M_390M_FORCE_EN                                       BIT(23)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_RPLL_DIV_780M_195M_FORCE_EN                                       BIT(22)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_RPLL_DIV_780M_260M_FORCE_EN                                       BIT(21)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_RPLL_DIV_780M_130M_FORCE_EN                                       BIT(20)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_RPLL_DIV_780M_86M7_FORCE_EN                                       BIT(19)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_RPLL_DIV_780M_43M3_FORCE_EN                                       BIT(18)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_RPLL_DIV_780M_156M_FORCE_EN                                       BIT(17)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_RPLL_DIV_780M_78M_FORCE_EN                                        BIT(16)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_RPLL_DIV_780M_111M4_FORCE_EN                                      BIT(15)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_RPLL_DIV_780M_55M7_FORCE_EN                                       BIT(14)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_RTC_DIV_1K_FORCE_EN                                               BIT(13)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_RTC4M0_DIV_2M_FORCE_EN                                            BIT(12)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_TWPLL_DIV_1536M_170M7_FORCE_EN                                    BIT(11)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_TWPLL_DIV_307M_153M6_FORCE_EN                                     BIT(10)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_TWPLL_DIV_307M_76M8_FORCE_EN                                      BIT(9)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_TWPLL_DIV_307M_38M4_FORCE_EN                                      BIT(8)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_TWPLL_DIV_307M_102M4_FORCE_EN                                     BIT(7)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_TWPLL_DIV_307M_51M2_FORCE_EN                                      BIT(6)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_TWPLL_DIV_512M_256M_FORCE_EN                                      BIT(5)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_TWPLL_DIV_512M_128M_FORCE_EN                                      BIT(4)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_TWPLL_DIV_512M_64M_FORCE_EN                                       BIT(3)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_TWPLL_DIV_512M_170M7_FORCE_EN                                     BIT(2)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_TWPLL_DIV_512M_85M3_FORCE_EN                                      BIT(1)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL0_CFG_TWPLL_DIV_768M_384M_FORCE_EN                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL1_CFG
// Register Offset : 0x0038
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL1_CFG_TWPLL_DIV_768M_192M_FORCE_EN                                      BIT(11)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL1_CFG_TWPLL_DIV_768M_96M_FORCE_EN                                       BIT(10)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL1_CFG_TWPLL_DIV_768M_48M_FORCE_EN                                       BIT(9)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL1_CFG_TWPLL_DIV_768M_24M_FORCE_EN                                       BIT(8)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL1_CFG_TWPLL_DIV_768M_12M_FORCE_EN                                       BIT(7)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL1_CFG_XBUF0_DIV_2M_FORCE_EN                                             BIT(6)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL1_CFG_XBUF0_DIV_1M_FORCE_EN                                             BIT(5)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL1_CFG_XBUF0_DIV_250K_FORCE_EN                                           BIT(4)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL1_CFG_XBUF0_DIV_13M_FORCE_EN                                            BIT(3)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL1_CFG_XBUF0_DIV_6M5_FORCE_EN                                            BIT(2)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL1_CFG_XBUF0_DIV_8M7_FORCE_EN                                            BIT(1)
#define BIT_PRE_DIV_CLK_GEN_DIV_EN_SW_CTL1_CFG_XBUF0_DIV_4M3_FORCE_EN                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG
// Register Offset : 0x003C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_26M_AP_AUTO_GATE_SEL                                            BIT(31)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_512M_AP_AUTO_GATE_SEL                                     BIT(30)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_384M_AP_AUTO_GATE_SEL                                     BIT(29)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_307M2_AP_AUTO_GATE_SEL                                    BIT(28)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_256M_AP_AUTO_GATE_SEL                                     BIT(27)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_192M_AP_AUTO_GATE_SEL                                     BIT(26)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_153M6_AP_AUTO_GATE_SEL                                    BIT(25)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_128M_AP_AUTO_GATE_SEL                                     BIT(24)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_96M_AP_AUTO_GATE_SEL                                      BIT(23)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_64M_AP_AUTO_GATE_SEL                                      BIT(22)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_51M2_AP_AUTO_GATE_SEL                                     BIT(21)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_48M_AP_AUTO_GATE_SEL                                      BIT(20)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_26M_MM_AUTO_GATE_SEL                                            BIT(19)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_CPPLL_468M_MM_AUTO_GATE_SEL                                     BIT(18)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_512M_MM_AUTO_GATE_SEL                                     BIT(17)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_384M_MM_AUTO_GATE_SEL                                     BIT(16)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_307M2_MM_AUTO_GATE_SEL                                    BIT(15)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_256M_MM_AUTO_GATE_SEL                                     BIT(14)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_192M_MM_AUTO_GATE_SEL                                     BIT(13)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_153M6_MM_AUTO_GATE_SEL                                    BIT(12)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_128M_MM_AUTO_GATE_SEL                                     BIT(11)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_96M_MM_AUTO_GATE_SEL                                      BIT(10)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_76M8_MM_AUTO_GATE_SEL                                     BIT(9)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_48M_MM_AUTO_GATE_SEL                                      BIT(8)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_GPLL_GPU_AUTO_GATE_SEL                                          BIT(7)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_512M_GPU_AUTO_GATE_SEL                                    BIT(6)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_384M_GPU_AUTO_GATE_SEL                                    BIT(5)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_307M2_GPU_AUTO_GATE_SEL                                   BIT(4)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_256M_GPU_AUTO_GATE_SEL                                    BIT(3)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_192M_GPU_AUTO_GATE_SEL                                    BIT(2)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_TWPLL_153M6_GPU_AUTO_GATE_SEL                                   BIT(1)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL0_CFG_CGM_LTEPLL_1228M8_AON_AUTO_GATE_SEL                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG
// Register Offset : 0x0040
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_LTEPLL_614M4_AON_AUTO_GATE_SEL                                  BIT(31)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_LTEPLL_409M6_AON_AUTO_GATE_SEL                                  BIT(30)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_LTEPLL_245M7_AON_AUTO_GATE_SEL                                  BIT(29)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_LTEPLL_30M72_AON_AUTO_GATE_SEL                                  BIT(28)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_TWPLL_768M_AON_AUTO_GATE_SEL                                    BIT(27)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_TWPLL_512M_AON_AUTO_GATE_SEL                                    BIT(26)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_TWPLL_384M_AON_AUTO_GATE_SEL                                    BIT(25)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_TWPLL_307M2_AON_AUTO_GATE_SEL                                   BIT(24)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_TWPLL_256M_AON_AUTO_GATE_SEL                                    BIT(23)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_TWPLL_219M4_AON_AUTO_GATE_SEL                                   BIT(22)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_TWPLL_192M_AON_AUTO_GATE_SEL                                    BIT(21)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_TWPLL_170M6_AON_AUTO_GATE_SEL                                   BIT(20)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_TWPLL_153M6_AON_AUTO_GATE_SEL                                   BIT(19)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_TWPLL_128M_AON_AUTO_GATE_SEL                                    BIT(18)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_TWPLL_96M_AON_AUTO_GATE_SEL                                     BIT(17)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_TWPLL_76M8_AON_AUTO_GATE_SEL                                    BIT(16)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_TWPLL_51M2_AON_AUTO_GATE_SEL                                    BIT(15)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_TWPLL_48M_AON_AUTO_GATE_SEL                                     BIT(14)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_TWPLL_38M4_AON_AUTO_GATE_SEL                                    BIT(13)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_TWPLL_24M_AON_AUTO_GATE_SEL                                     BIT(12)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_TWPLL_12M_AON_AUTO_GATE_SEL                                     BIT(11)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_RPLL_390M_AON_AUTO_GATE_SEL                                     BIT(10)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_RPLL_260M_AON_AUTO_GATE_SEL                                     BIT(9)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_RPLL_195M_AON_AUTO_GATE_SEL                                     BIT(8)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_RPLL_26M_AON_AUTO_GATE_SEL                                      BIT(7)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_GPLL_40M7_AON_AUTO_GATE_SEL                                     BIT(6)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_CPPLL_14M63_AON_AUTO_GATE_SEL                                   BIT(5)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_26M_AON_AUTO_GATE_SEL                                           BIT(4)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_26M_AUD_AON_AUTO_GATE_SEL                                       BIT(3)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_4M_RCO_AON_AUTO_GATE_SEL                                        BIT(2)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_2M_RCO_AON_AUTO_GATE_SEL                                        BIT(1)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_13M_AON_AUTO_GATE_SEL                                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG
// Register Offset : 0x0044
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_6M5_AON_AUTO_GATE_SEL                                           BIT(31)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_4M_AON_AUTO_GATE_SEL                                            BIT(30)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_2M_AON_AUTO_GATE_SEL                                            BIT(29)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_1M_AON_AUTO_GATE_SEL                                            BIT(28)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_250K_AON_AUTO_GATE_SEL                                          BIT(27)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_TWPLL_512M_WTLCP_AUTO_GATE_SEL                                  BIT(26)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_TWPLL_384M_WTLCP_AUTO_GATE_SEL                                  BIT(25)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_TWPLL_307M2_WTLCP_AUTO_GATE_SEL                                 BIT(24)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_TWPLL_256M_WTLCP_AUTO_GATE_SEL                                  BIT(23)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_TWPLL_153M6_WTLCP_AUTO_GATE_SEL                                 BIT(22)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_TWPLL_128M_WTLCP_AUTO_GATE_SEL                                  BIT(21)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_TWPLL_102M4_WTLCP_AUTO_GATE_SEL                                 BIT(20)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_TWPLL_96M_WTLCP_AUTO_GATE_SEL                                   BIT(19)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_TWPLL_85M3_WTLCP_AUTO_GATE_SEL                                  BIT(18)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_TWPLL_76M8_WTLCP_AUTO_GATE_SEL                                  BIT(17)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_TWPLL_64M_WTLCP_AUTO_GATE_SEL                                   BIT(16)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_TWPLL_51M2_WTLCP_AUTO_GATE_SEL                                  BIT(15)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_TWPLL_48M_WTLCP_AUTO_GATE_SEL                                   BIT(14)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_LPLL0_614M4_WTLCP_AUTO_GATE_SEL                                 BIT(13)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_LPLL0_409M6_WTLCP_AUTO_GATE_SEL                                 BIT(12)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_LPLL0_307M2_WTLCP_AUTO_GATE_SEL                                 BIT(11)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_LPLL0_245M76_WTLCP_AUTO_GATE_SEL                                BIT(10)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_LPLL0_204M8_WTLCP_AUTO_GATE_SEL                                 BIT(9)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_LPLL0_153M6_WTLCP_AUTO_GATE_SEL                                 BIT(8)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_LPLL0_122M88_WTLCP_AUTO_GATE_SEL                                BIT(7)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_LPLL0_102M4_WTLCP_AUTO_GATE_SEL                                 BIT(6)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_LPLL0_61M44_WTLCP_AUTO_GATE_SEL                                 BIT(5)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_XTL_26M_WTLCP_AUTO_GATE_SEL                                     BIT(4)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_TWPLL_512M_PUBCP_AUTO_GATE_SEL                                  BIT(3)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_TWPLL_384M_PUBCP_AUTO_GATE_SEL                                  BIT(2)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_TWPLL_307M2_PUBCP_AUTO_GATE_SEL                                 BIT(1)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL2_CFG_CGM_TWPLL_256M_PUBCP_AUTO_GATE_SEL                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_GATE_EN_SEL3_CFG
// Register Offset : 0x0048
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL3_CFG_CGM_TWPLL_153M6_PUBCP_AUTO_GATE_SEL                                 BIT(7)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL3_CFG_CGM_TWPLL_128M_PUBCP_AUTO_GATE_SEL                                  BIT(6)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL3_CFG_CGM_TWPLL_96M_PUBCP_AUTO_GATE_SEL                                   BIT(5)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL3_CFG_CGM_TWPLL_64M_PUBCP_AUTO_GATE_SEL                                   BIT(4)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL3_CFG_CGM_TWPLL_51M2_PUBCP_AUTO_GATE_SEL                                  BIT(3)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL3_CFG_CGM_TWPLL_48M_PUBCP_AUTO_GATE_SEL                                   BIT(2)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL3_CFG_CGM_XTL_26M_PUBCP_AUTO_GATE_SEL                                     BIT(1)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL3_CFG_CGM_RTC_32K_PUBCP_AUTO_GATE_SEL                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG
// Register Offset : 0x004C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_26M_AP_FORCE_EN                                              BIT(31)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_512M_AP_FORCE_EN                                       BIT(30)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_384M_AP_FORCE_EN                                       BIT(29)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_307M2_AP_FORCE_EN                                      BIT(28)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_256M_AP_FORCE_EN                                       BIT(27)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_192M_AP_FORCE_EN                                       BIT(26)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_153M6_AP_FORCE_EN                                      BIT(25)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_128M_AP_FORCE_EN                                       BIT(24)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_96M_AP_FORCE_EN                                        BIT(23)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_64M_AP_FORCE_EN                                        BIT(22)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_51M2_AP_FORCE_EN                                       BIT(21)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_48M_AP_FORCE_EN                                        BIT(20)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_26M_MM_FORCE_EN                                              BIT(19)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_CPPLL_468M_MM_FORCE_EN                                       BIT(18)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_512M_MM_FORCE_EN                                       BIT(17)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_384M_MM_FORCE_EN                                       BIT(16)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_307M2_MM_FORCE_EN                                      BIT(15)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_256M_MM_FORCE_EN                                       BIT(14)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_192M_MM_FORCE_EN                                       BIT(13)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_153M6_MM_FORCE_EN                                      BIT(12)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_128M_MM_FORCE_EN                                       BIT(11)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_96M_MM_FORCE_EN                                        BIT(10)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_76M8_MM_FORCE_EN                                       BIT(9)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_48M_MM_FORCE_EN                                        BIT(8)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_GPLL_GPU_FORCE_EN                                            BIT(7)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_512M_GPU_FORCE_EN                                      BIT(6)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_384M_GPU_FORCE_EN                                      BIT(5)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_307M2_GPU_FORCE_EN                                     BIT(4)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_256M_GPU_FORCE_EN                                      BIT(3)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_192M_GPU_FORCE_EN                                      BIT(2)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_TWPLL_153M6_GPU_FORCE_EN                                     BIT(1)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL0_CFG_CGM_LTEPLL_1228M8_AON_FORCE_EN                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG
// Register Offset : 0x0050
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_LTEPLL_614M4_AON_FORCE_EN                                    BIT(31)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_LTEPLL_409M6_AON_FORCE_EN                                    BIT(30)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_LTEPLL_245M7_AON_FORCE_EN                                    BIT(29)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_LTEPLL_30M72_AON_FORCE_EN                                    BIT(28)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_TWPLL_768M_AON_FORCE_EN                                      BIT(27)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_TWPLL_512M_AON_FORCE_EN                                      BIT(26)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_TWPLL_384M_AON_FORCE_EN                                      BIT(25)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_TWPLL_307M2_AON_FORCE_EN                                     BIT(24)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_TWPLL_256M_AON_FORCE_EN                                      BIT(23)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_TWPLL_219M4_AON_FORCE_EN                                     BIT(22)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_TWPLL_192M_AON_FORCE_EN                                      BIT(21)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_TWPLL_170M6_AON_FORCE_EN                                     BIT(20)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_TWPLL_153M6_AON_FORCE_EN                                     BIT(19)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_TWPLL_128M_AON_FORCE_EN                                      BIT(18)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_TWPLL_96M_AON_FORCE_EN                                       BIT(17)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_TWPLL_76M8_AON_FORCE_EN                                      BIT(16)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_TWPLL_51M2_AON_FORCE_EN                                      BIT(15)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_TWPLL_48M_AON_FORCE_EN                                       BIT(14)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_TWPLL_38M4_AON_FORCE_EN                                      BIT(13)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_TWPLL_24M_AON_FORCE_EN                                       BIT(12)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_TWPLL_12M_AON_FORCE_EN                                       BIT(11)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_RPLL_390M_AON_FORCE_EN                                       BIT(10)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_RPLL_260M_AON_FORCE_EN                                       BIT(9)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_RPLL_195M_AON_FORCE_EN                                       BIT(8)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_RPLL_26M_AON_FORCE_EN                                        BIT(7)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_GPLL_40M7_AON_FORCE_EN                                       BIT(6)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_CPPLL_14M63_AON_FORCE_EN                                     BIT(5)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_26M_AON_FORCE_EN                                             BIT(4)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_26M_AUD_AON_FORCE_EN                                         BIT(3)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_4M_RCO_AON_FORCE_EN                                          BIT(2)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_2M_RCO_AON_FORCE_EN                                          BIT(1)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL1_CFG_CGM_13M_AON_FORCE_EN                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG
// Register Offset : 0x0054
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_6M5_AON_FORCE_EN                                             BIT(31)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_4M_AON_FORCE_EN                                              BIT(30)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_2M_AON_FORCE_EN                                              BIT(29)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_1M_AON_FORCE_EN                                              BIT(28)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_250K_AON_FORCE_EN                                            BIT(27)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_TWPLL_512M_WTLCP_FORCE_EN                                    BIT(26)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_TWPLL_384M_WTLCP_FORCE_EN                                    BIT(25)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_TWPLL_307M2_WTLCP_FORCE_EN                                   BIT(24)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_TWPLL_256M_WTLCP_FORCE_EN                                    BIT(23)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_TWPLL_153M6_WTLCP_FORCE_EN                                   BIT(22)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_TWPLL_128M_WTLCP_FORCE_EN                                    BIT(21)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_TWPLL_102M4_WTLCP_FORCE_EN                                   BIT(20)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_TWPLL_96M_WTLCP_FORCE_EN                                     BIT(19)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_TWPLL_85M3_WTLCP_FORCE_EN                                    BIT(18)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_TWPLL_76M8_WTLCP_FORCE_EN                                    BIT(17)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_TWPLL_64M_WTLCP_FORCE_EN                                     BIT(16)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_TWPLL_51M2_WTLCP_FORCE_EN                                    BIT(15)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_TWPLL_48M_WTLCP_FORCE_EN                                     BIT(14)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_LPLL0_614M4_WTLCP_FORCE_EN                                   BIT(13)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_LPLL0_409M6_WTLCP_FORCE_EN                                   BIT(12)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_LPLL0_307M2_WTLCP_FORCE_EN                                   BIT(11)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_LPLL0_245M76_WTLCP_FORCE_EN                                  BIT(10)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_LPLL0_204M8_WTLCP_FORCE_EN                                   BIT(9)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_LPLL0_153M6_WTLCP_FORCE_EN                                   BIT(8)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_LPLL0_122M88_WTLCP_FORCE_EN                                  BIT(7)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_LPLL0_102M4_WTLCP_FORCE_EN                                   BIT(6)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_LPLL0_61M44_WTLCP_FORCE_EN                                   BIT(5)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_XTL_26M_WTLCP_FORCE_EN                                       BIT(4)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_TWPLL_512M_PUBCP_FORCE_EN                                    BIT(3)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_TWPLL_384M_PUBCP_FORCE_EN                                    BIT(2)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_TWPLL_307M2_PUBCP_FORCE_EN                                   BIT(1)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL2_CFG_CGM_TWPLL_256M_PUBCP_FORCE_EN                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL3_CFG
// Register Offset : 0x0058
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL3_CFG_CGM_TWPLL_153M6_PUBCP_FORCE_EN                                   BIT(7)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL3_CFG_CGM_TWPLL_128M_PUBCP_FORCE_EN                                    BIT(6)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL3_CFG_CGM_TWPLL_96M_PUBCP_FORCE_EN                                     BIT(5)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL3_CFG_CGM_TWPLL_64M_PUBCP_FORCE_EN                                     BIT(4)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL3_CFG_CGM_TWPLL_51M2_PUBCP_FORCE_EN                                    BIT(3)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL3_CFG_CGM_TWPLL_48M_PUBCP_FORCE_EN                                     BIT(2)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL3_CFG_CGM_XTL_26M_PUBCP_FORCE_EN                                       BIT(1)
#define BIT_PRE_DIV_CLK_GEN_GATE_EN_SW_CTL3_CFG_CGM_RTC_32K_PUBCP_FORCE_EN                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG
// Register Offset : 0x005C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG_CGM_TWPLL_192M_AP_SEL                                      BIT(16)
#define BIT_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG_CGM_TWPLL_96M_AP_SEL                                       BIT(15)
#define BIT_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG_CGM_TWPLL_64M_AP_SEL                                       BIT(14)
#define BIT_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG_CGM_TWPLL_48M_AP_SEL                                       BIT(13)
#define BIT_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG_CGM_TWPLL_192M_MM_SEL                                      BIT(12)
#define BIT_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG_CGM_TWPLL_96M_MM_SEL                                       BIT(11)
#define BIT_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG_CGM_TWPLL_48M_MM_SEL                                       BIT(10)
#define BIT_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG_CGM_TWPLL_192M_GPU_SEL                                     BIT(9)
#define BIT_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG_CGM_TWPLL_96M_AON_SEL                                      BIT(8)
#define BIT_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG_CGM_TWPLL_48M_AON_SEL                                      BIT(7)
#define BIT_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG_CGM_TWPLL_96M_WTLCP_SEL                                    BIT(6)
#define BIT_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG_CGM_TWPLL_64M_WTLCP_SEL                                    BIT(5)
#define BIT_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG_CGM_TWPLL_48M_WTLCP_SEL                                    BIT(4)
#define BIT_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG_CGM_XTL_26M_WTLCP_SEL                                      BIT(3)
#define BIT_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG_CGM_TWPLL_96M_PUBCP_SEL                                    BIT(2)
#define BIT_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG_CGM_TWPLL_64M_PUBCP_SEL                                    BIT(1)
#define BIT_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG_CGM_TWPLL_48M_PUBCP_SEL                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_MONITOR_WAIT_EN_STATUS0_CFG
// Register Offset : 0x0060
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_MONITOR_WAIT_EN_STATUS0_CFG_MONITOR_WAIT_EN_STATUS(x)                                (((x) & 0x1FFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_MONITOR_DIV_AUTO_EN_STATUS00_CFG
// Register Offset : 0x0064
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_MONITOR_DIV_AUTO_EN_STATUS00_CFG_MONITOR_DIV_AUTO_EN_STATUS0(x)                      (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_MONITOR_DIV_AUTO_EN_STATUS10_CFG
// Register Offset : 0x0068
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_MONITOR_DIV_AUTO_EN_STATUS10_CFG_MONITOR_DIV_AUTO_EN_STATUS1(x)                      (((x) & 0xFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_MONITOR_GATE_AUTO_EN_STATUS00_CFG
// Register Offset : 0x006C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_MONITOR_GATE_AUTO_EN_STATUS00_CFG_MONITOR_GATE_AUTO_EN_STATUS0(x)                    (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_MONITOR_GATE_AUTO_EN_STATUS10_CFG
// Register Offset : 0x0070
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_MONITOR_GATE_AUTO_EN_STATUS10_CFG_MONITOR_GATE_AUTO_EN_STATUS1(x)                    (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_MONITOR_GATE_AUTO_EN_STATUS20_CFG
// Register Offset : 0x0074
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_MONITOR_GATE_AUTO_EN_STATUS20_CFG_MONITOR_GATE_AUTO_EN_STATUS2(x)                    (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PRE_DIV_CLK_GEN_MONITOR_GATE_AUTO_EN_STATUS30_CFG
// Register Offset : 0x0078
// Description     :
---------------------------------------------------------------------------*/

#define BIT_PRE_DIV_CLK_GEN_MONITOR_GATE_AUTO_EN_STATUS30_CFG_MONITOR_GATE_AUTO_EN_STATUS3(x)                    (((x) & 0xFF))


#endif // _PRE_DIV_CLK_GEN_REG_H
