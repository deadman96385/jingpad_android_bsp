/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _ANA_APB_RF_REG_H
#define _ANA_APB_RF_REG_H

#define CTL_BASE_ANA_APB_RF SPRD_SERDES_TESTREG_PHYS


#define REG_ANA_APB_RF_TEST_CTRL          ( CTL_BASE_ANA_APB_RF + 0x0000 )
#define REG_ANA_APB_RF_TEST_DIN           ( CTL_BASE_ANA_APB_RF + 0x0004 )
#define REG_ANA_APB_RF_TEST_DOUT          ( CTL_BASE_ANA_APB_RF + 0x0008 )
#define REG_ANA_APB_RF_DBG_PHY_CTRL_0     ( CTL_BASE_ANA_APB_RF + 0x000C )
#define REG_ANA_APB_RF_DBG_PHY_CTRL_1     ( CTL_BASE_ANA_APB_RF + 0x0010 )
#define REG_ANA_APB_RF_DBG_PHY_CTRL_2     ( CTL_BASE_ANA_APB_RF + 0x0014 )
#define REG_ANA_APB_RF_DBG_PHY_CTRL_3     ( CTL_BASE_ANA_APB_RF + 0x0018 )
#define REG_ANA_APB_RF_DBG_PHY_CTRL_4     ( CTL_BASE_ANA_APB_RF + 0x001C )
#define REG_ANA_APB_RF_DBG_PHY_CTRL_5     ( CTL_BASE_ANA_APB_RF + 0x0020 )
#define REG_ANA_APB_RF_DBG_PHY_CTRL_RO_0  ( CTL_BASE_ANA_APB_RF + 0x0024 )
#define REG_ANA_APB_RF_DBG_PHY_CTRL_RO_1  ( CTL_BASE_ANA_APB_RF + 0x0028 )
#define REG_ANA_APB_RF_DBG_PHY_CTRL_RO_2  ( CTL_BASE_ANA_APB_RF + 0x002C )
#define REG_ANA_APB_RF_DBG_PHY_CTRL_RO_3  ( CTL_BASE_ANA_APB_RF + 0x0030 )
#define REG_ANA_APB_RF_DBG_PHY_CTRL_RO_4  ( CTL_BASE_ANA_APB_RF + 0x0034 )

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RF_TEST_CTRL
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RF_TEST_CTRL_DBG_TESTCLK                                    BIT(2)
#define BIT_ANA_APB_RF_TEST_CTRL_DBG_TESTCLR                                    BIT(1)
#define BIT_ANA_APB_RF_TEST_CTRL_DBG_TESTEN                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RF_TEST_DIN
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RF_TEST_DIN_DBG_TESTDIN(x)                                  (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RF_TEST_DOUT
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RF_TEST_DOUT_DBG_TESTOUT(x)                                 (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RF_DBG_PHY_CTRL_0
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RF_DBG_PHY_CTRL_0_SHUTDOWN_DB                               BIT(4)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_0_RSTZ_DB                                   BIT(3)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_0_TXCLKESC_DB                               BIT(2)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_0_TXULPSCLK_DB                              BIT(1)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_0_TXULPSEXITCLK_DB                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RF_DBG_PHY_CTRL_1
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXREQUESTESC_3_DB                         BIT(31)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXREQUESTESC_2_DB                         BIT(30)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXREQUESTESC_1_DB                         BIT(29)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXREQUESTESC_0_DB                         BIT(28)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXLPDTESC_3_DB                            BIT(27)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXLPDTESC_2_DB                            BIT(26)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXLPDTESC_1_DB                            BIT(25)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXLPDTESC_0_DB                            BIT(24)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXULPSESC_3_DB                            BIT(23)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXULPSESC_2_DB                            BIT(22)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXULPSESC_1_DB                            BIT(21)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXULPSESC_0_DB                            BIT(20)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXULPSEXIT_3_DB                           BIT(19)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXULPSEXIT_2_DB                           BIT(18)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXULPSEXIT_1_DB                           BIT(17)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXULPSEXIT_0_DB                           BIT(16)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXTRIGGERESC_3_DB(x)                      (((x) & 0xF) << 12)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXTRIGGERESC_2_DB(x)                      (((x) & 0xF) << 8)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXTRIGGERESC_1_DB(x)                      (((x) & 0xF) << 4)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_1_TXTRIGGERESC_0_DB(x)                      (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RF_DBG_PHY_CTRL_2
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RF_DBG_PHY_CTRL_2_TXDATAESC_3_DB(x)                         (((x) & 0xFF) << 24)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_2_TXDATAESC_2_DB(x)                         (((x) & 0xFF) << 16)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_2_TXDATAESC_1_DB(x)                         (((x) & 0xFF) << 8)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_2_TXDATAESC_0_DB(x)                         (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RF_DBG_PHY_CTRL_3
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RF_DBG_PHY_CTRL_3_TXVALIDESC_3_DB                           BIT(3)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_3_TXVALIDESC_2_DB                           BIT(2)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_3_TXVALIDESC_1_DB                           BIT(1)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_3_TXVALIDESC_0_DB                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RF_DBG_PHY_CTRL_4
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RF_DBG_PHY_CTRL_4_TURNREQUEST_3_DB                          BIT(15)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_4_TURNREQUEST_2_DB                          BIT(14)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_4_TURNREQUEST_1_DB                          BIT(13)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_4_TURNREQUEST_0_DB                          BIT(12)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_4_TURNDISABLE_3_DB                          BIT(11)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_4_TURNDISABLE_2_DB                          BIT(10)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_4_TURNDISABLE_1_DB                          BIT(9)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_4_TURNDISABLE_0_DB                          BIT(8)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_4_FORCERXMODE_3_DB                          BIT(7)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_4_FORCERXMODE_2_DB                          BIT(6)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_4_FORCERXMODE_1_DB                          BIT(5)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_4_FORCERXMODE_0_DB                          BIT(4)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_4_FORCETXSTOPMODE_3_DB                      BIT(3)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_4_FORCETXSTOPMODE_2_DB                      BIT(2)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_4_FORCETXSTOPMODE_1_DB                      BIT(1)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_4_FORCETXSTOPMODE_0_DB                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RF_DBG_PHY_CTRL_5
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RF_DBG_PHY_CTRL_5_ENABLE_3_DB                               BIT(6)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_5_ENABLE_2_DB                               BIT(5)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_5_ENABLE_1_DB                               BIT(4)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_5_ENABLE_0_DB                               BIT(3)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_5_ENABLECLK_DB                              BIT(2)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_5_FORCEPLL_DB                               BIT(1)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_5_BISTON_DB                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RF_DBG_PHY_CTRL_RO_0
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_DIRECTION_3_DB                         BIT(23)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_DIRECTION_2_DB                         BIT(22)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_DIRECTION_1_DB                         BIT(21)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_DIRECTION_0_DB                         BIT(20)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRCONTENTIONLP0_3_DB                  BIT(19)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRCONTENTIONLP0_2_DB                  BIT(18)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRCONTENTIONLP0_1_DB                  BIT(17)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRCONTENTIONLP0_0_DB                  BIT(16)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRCONTENTIONLP1_3_DB                  BIT(15)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRCONTENTIONLP1_2_DB                  BIT(14)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRCONTENTIONLP1_1_DB                  BIT(13)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRCONTENTIONLP1_0_DB                  BIT(12)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRCONTROL_3_DB                        BIT(11)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRCONTROL_2_DB                        BIT(10)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRCONTROL_1_DB                        BIT(9)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRCONTROL_0_DB                        BIT(8)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRESC_3_DB                            BIT(7)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRESC_2_DB                            BIT(6)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRESC_1_DB                            BIT(5)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRESC_0_DB                            BIT(4)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRSYNCESC_3_DB                        BIT(3)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRSYNCESC_2_DB                        BIT(2)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRSYNCESC_1_DB                        BIT(1)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_0_ERRSYNCESC_0_DB                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RF_DBG_PHY_CTRL_RO_1
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_1_PLLLOCK_DB                             BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RF_DBG_PHY_CTRL_RO_2
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXCLKESC_3_DB                          BIT(31)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXCLKESC_2_DB                          BIT(30)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXCLKESC_1_DB                          BIT(29)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXCLKESC_0_DB                          BIT(28)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXLPDTESC_3_DB                         BIT(27)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXLPDTESC_2_DB                         BIT(26)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXLPDTESC_1_DB                         BIT(25)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXLPDTESC_0_DB                         BIT(24)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXTRIGGERESC_3_DB(x)                   (((x) & 0xF) << 20)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXTRIGGERESC_2_DB(x)                   (((x) & 0xF) << 16)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXTRIGGERESC_1_DB(x)                   (((x) & 0xF) << 12)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXTRIGGERESC_0_DB(x)                   (((x) & 0xF) << 8)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXULPSESC_3_DB                         BIT(7)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXULPSESC_2_DB                         BIT(6)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXULPSESC_1_DB                         BIT(5)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXULPSESC_0_DB                         BIT(4)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXVALIDESC_3_DB                        BIT(3)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXVALIDESC_2_DB                        BIT(2)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXVALIDESC_1_DB                        BIT(1)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_2_RXVALIDESC_0_DB                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RF_DBG_PHY_CTRL_RO_3
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_3_RXDATAESC_3_DB(x)                      (((x) & 0xFF) << 24)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_3_RXDATAESC_2_DB(x)                      (((x) & 0xFF) << 16)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_3_RXDATAESC_1_DB(x)                      (((x) & 0xFF) << 8)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_3_RXDATAESC_0_DB(x)                      (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RF_DBG_PHY_CTRL_RO_4
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_4_STOPSTATECLK_DB                        BIT(13)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_4_STOPSTATEDATA_3_DB                     BIT(12)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_4_STOPSTATEDATA_2_DB                     BIT(11)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_4_STOPSTATEDATA_1_DB                     BIT(10)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_4_STOPSTATEDATA_0_DB                     BIT(9)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_4_TXREADYESC_3_DB                        BIT(8)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_4_TXREADYESC_2_DB                        BIT(7)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_4_TXREADYESC_1_DB                        BIT(6)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_4_TXREADYESC_0_DB                        BIT(5)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_4_ULPSACTIVENOTCLK_DB                    BIT(4)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_4_ULPSACTIVENOT_3_DB                     BIT(3)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_4_ULPSACTIVENOT_2_DB                     BIT(2)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_4_ULPSACTIVENOT_1_DB                     BIT(1)
#define BIT_ANA_APB_RF_DBG_PHY_CTRL_RO_4_ULPSACTIVENOT_0_DB                     BIT(0)


#endif // _ANA_APB_RF_REG_H
