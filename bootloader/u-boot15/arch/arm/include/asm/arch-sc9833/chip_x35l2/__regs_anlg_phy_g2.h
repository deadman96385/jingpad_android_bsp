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


#define REG_ANLG_PHY_G2_ANALOG_USB20_USB20_TEST_PIN                     ( CTL_BASE_ANLG_PHY_G2 + 0x0000 )
#define REG_ANLG_PHY_G2_ANALOG_USB20_USB20_UTMI_CTL                     ( CTL_BASE_ANLG_PHY_G2 + 0x0004 )
#define REG_ANLG_PHY_G2_ANALOG_USB20_USB20_BATTER_PLL                   ( CTL_BASE_ANLG_PHY_G2 + 0x0008 )
#define REG_ANLG_PHY_G2_ANALOG_USB20_USB20_TRIMMING                     ( CTL_BASE_ANLG_PHY_G2 + 0x000C )
#define REG_ANLG_PHY_G2_ANALOG_USB20_USB20_PHY_BIST_TEST                ( CTL_BASE_ANLG_PHY_G2 + 0x0010 )
#define REG_ANLG_PHY_G2_ANALOG_USB20_REG_SEL_CFG_0                      ( CTL_BASE_ANLG_PHY_G2 + 0x0014 )
#define REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXCLKLANE          ( CTL_BASE_ANLG_PHY_G2 + 0x0018 )
#define REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATA_0           ( CTL_BASE_ANLG_PHY_G2 + 0x001C )
#define REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATA_1           ( CTL_BASE_ANLG_PHY_G2 + 0x0020 )
#define REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATA_2           ( CTL_BASE_ANLG_PHY_G2 + 0x0024 )
#define REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATA_3           ( CTL_BASE_ANLG_PHY_G2 + 0x0028 )
#define REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATAESC          ( CTL_BASE_ANLG_PHY_G2 + 0x002C )
#define REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_STATE_RX           ( CTL_BASE_ANLG_PHY_G2 + 0x0030 )
#define REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_ERR                ( CTL_BASE_ANLG_PHY_G2 + 0x0034 )
#define REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_CTRL               ( CTL_BASE_ANLG_PHY_G2 + 0x0038 )
#define REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_RES                ( CTL_BASE_ANLG_PHY_G2 + 0x003C )
#define REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_TEST               ( CTL_BASE_ANLG_PHY_G2 + 0x0040 )
#define REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_DATALANE_CTRL      ( CTL_BASE_ANLG_PHY_G2 + 0x0044 )
#define REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_REG_SEL_CFG_0             ( CTL_BASE_ANLG_PHY_G2 + 0x0048 )
#define REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_REG_SEL_CFG_1             ( CTL_BASE_ANLG_PHY_G2 + 0x004C )
#define REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_REG_SEL_CFG_2             ( CTL_BASE_ANLG_PHY_G2 + 0x0050 )

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_USB20_USB20_TEST_PIN
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_TESTCLK                                            BIT(24)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_TESTDATAIN(x)                                      (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_TESTADDR(x)                                        (((x) & 0xF) << 12)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_TESTDATAOUTSEL                                     BIT(11)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_TESTDATAOUT(x)                                     (((x) & 0xF) << 7)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_BIST_MODE(x)                                       (((x) & 0x1F) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_T2RCOMP                                            BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_LPBK_END                                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_USB20_USB20_UTMI_CTL
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_DATABUS16_8                                        BIT(28)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_SUSPENDM                                           BIT(27)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_PORN                                               BIT(26)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_RESET                                              BIT(25)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_RXERROR                                            BIT(24)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_BYPASS_DRV_DP                                      BIT(23)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_BYPASS_DRV_DM                                      BIT(22)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_BYPASS_FS                                          BIT(21)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_BYPASS_IN_DP                                       BIT(20)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_BYPASS_IN_DM                                       BIT(19)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_BYPASS_OUT_DP                                      BIT(18)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_BYPASS_OUT_DM                                      BIT(17)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_VBUSVLDEXT                                         BIT(16)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_RESERVED(x)                                        (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_USB20_USB20_BATTER_PLL
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_PS_PD_S                                            BIT(5)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_PS_PD_L                                            BIT(4)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_REXTENABLE                                         BIT(3)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_DMPULLUP                                           BIT(2)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_HSIC_PLLON                                               BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_SAMPLER_SEL                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_USB20_USB20_TRIMMING
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_TUNEHSAMP(x)                                       (((x) & 0x3) << 27)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_TFREGRES(x)                                        (((x) & 0x3F) << 21)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_TFHSRES(x)                                         (((x) & 0x1F) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_TUNERISE(x)                                        (((x) & 0x3) << 14)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_TUNEOTG(x)                                         (((x) & 0x7) << 11)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_TUNEDSC(x)                                         (((x) & 0x3) << 9)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_TUNESQ(x)                                          (((x) & 0xF) << 5)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_TUNEEQ(x)                                          (((x) & 0x7) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_TUNEPLLS(x)                                        (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_USB20_USB20_PHY_BIST_TEST
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_BIST_MODE_EN                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_USB20_REG_SEL_CFG_0
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_TESTCLK                                    BIT(30)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_TESTDATAIN                                 BIT(29)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_TESTADDR                                   BIT(28)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_TESTDATAOUTSEL                             BIT(27)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_BIST_MODE                                  BIT(26)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_DATABUS16_8                                BIT(25)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_SUSPENDM                                   BIT(24)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_PORN                                       BIT(23)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_RESET                                      BIT(22)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_BYPASS_DRV_DP                              BIT(21)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_BYPASS_DRV_DM                              BIT(20)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_BYPASS_FS                                  BIT(19)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_BYPASS_IN_DP                               BIT(18)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_BYPASS_IN_DM                               BIT(17)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_VBUSVLDEXT                                 BIT(16)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_RESERVED                                   BIT(15)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_PS_PD_S                                    BIT(14)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_PS_PD_L                                    BIT(13)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_REXTENABLE                                 BIT(12)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_DMPULLUP                                   BIT(11)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_HSIC_PLLON                                       BIT(10)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_SAMPLER_SEL                                BIT(9)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_TUNEHSAMP                                  BIT(8)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_TFREGRES                                   BIT(7)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_TFHSRES                                    BIT(6)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_TUNERISE                                   BIT(5)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_TUNEOTG                                    BIT(4)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_TUNEDSC                                    BIT(3)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_TUNESQ                                     BIT(2)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_TUNEEQ                                     BIT(1)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_USB20_USB20_TUNEPLLS                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXCLKLANE
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTHSCLK                              BIT(4)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSCLK                                   BIT(3)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXITCLK                               BIT(2)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_STOPSTATECLK                                BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ULPSACTIVENOTCLK                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATA_0
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTDATAHS_0                           BIT(10)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTESC_0                              BIT(9)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXLPDTESC_0                                 BIT(8)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSESC_0                                 BIT(7)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXIT_0                                BIT(6)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXTRIGGERESC_0(x)                           (((x) & 0xF) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXVALIDESC_0                                BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXREADYESC_0                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATA_1
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTDATAHS_1                           BIT(10)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTESC_1                              BIT(9)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXLPDTESC_1                                 BIT(8)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSESC_1                                 BIT(7)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXIT_1                                BIT(6)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXTRIGGERESC_1(x)                           (((x) & 0xF) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXVALIDESC_1                                BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXREADYESC_1                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATA_2
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTDATAHS_2                           BIT(10)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTESC_2                              BIT(9)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXLPDTESC_2                                 BIT(8)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSESC_2                                 BIT(7)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXIT_2                                BIT(6)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXTRIGGERESC_2(x)                           (((x) & 0xF) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXVALIDESC_2                                BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXREADYESC_2                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATA_3
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTDATAHS_3                           BIT(10)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTESC_3                              BIT(9)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXLPDTESC_3                                 BIT(8)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSESC_3                                 BIT(7)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXIT_3                                BIT(6)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXTRIGGERESC_3(x)                           (((x) & 0xF) << 2)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXVALIDESC_3                                BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXREADYESC_3                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATAESC
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXDATAESC_0(x)                              (((x) & 0xFF) << 24)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXDATAESC_1(x)                              (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXDATAESC_2(x)                              (((x) & 0xFF) << 8)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TXDATAESC_3(x)                              (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_STATE_RX
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RXCLKESC_0                                  BIT(27)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RXLPDTESC_0                                 BIT(26)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RXTRIGGERESC_0(x)                           (((x) & 0xF) << 22)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RXVALIDESC_0                                BIT(21)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RXCLKESC_1                                  BIT(20)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RXLPDTESC_1                                 BIT(19)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RXTRIGGERESC_1(x)                           (((x) & 0xF) << 15)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RXVALIDESC_1                                BIT(14)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RXCLKESC_2                                  BIT(13)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RXLPDTESC_2                                 BIT(12)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RXTRIGGERESC_2(x)                           (((x) & 0xF) << 8)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RXVALIDESC_2                                BIT(7)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RXCLKESC_3                                  BIT(6)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RXLPDTESC_3                                 BIT(5)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RXTRIGGERESC_3(x)                           (((x) & 0xF) << 1)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RXVALIDESC_3                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_ERR
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRESC_0                                    BIT(19)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRSYNCESC_0                                BIT(18)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRCONTROL_0                                BIT(17)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRCONTENTIONLP0_0                          BIT(16)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRCONTENTIONLP1_0                          BIT(15)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRESC_1                                    BIT(14)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRSYNCESC_1                                BIT(13)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRCONTROL_1                                BIT(12)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRCONTENTIONLP0_1                          BIT(11)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRCONTENTIONLP1_1                          BIT(10)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRESC_2                                    BIT(9)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRSYNCESC_2                                BIT(8)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRCONTROL_2                                BIT(7)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRCONTENTIONLP0_2                          BIT(6)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRCONTENTIONLP1_2                          BIT(5)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRESC_3                                    BIT(4)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRSYNCESC_3                                BIT(3)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRCONTROL_3                                BIT(2)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRCONTENTIONLP0_3                          BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ERRCONTENTIONLP1_3                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_CTRL
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_PS_PD_S                                     BIT(21)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_PS_PD_L                                     BIT(20)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_SHUTDOWNZ                                   BIT(19)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RSTZ                                        BIT(18)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ENABLE_0                                    BIT(17)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ENABLE_1                                    BIT(16)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ENABLE_2                                    BIT(15)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ENABLE_3                                    BIT(14)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_ENABLECLK                                   BIT(13)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_FORCEPLL                                    BIT(12)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_PLLLOCK                                     BIT(11)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_BISTON                                      BIT(10)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_BISTDONE                                    BIT(9)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_IF_SEL                                      BIT(8)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TRIMBG(x)                                   (((x) & 0xF) << 4)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TX_RCTL(x)                                  (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_RES
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RESERVED(x)                                 (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_RESERVEDO(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_TEST
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TESTDIN(x)                                  (((x) & 0xFF) << 11)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TESTDOUT(x)                                 (((x) & 0xFF) << 3)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TESTEN                                      BIT(2)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TESTCLK                                     BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TESTCLR                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_4L_DATALANE_CTRL
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TURNREQUEST_0                               BIT(22)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_DIRECTION_0                                 BIT(21)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TURNDISABLE_0                               BIT(20)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_FORCERXMODE_0                               BIT(19)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_FORCETXSTOPMODE_0                           BIT(18)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_STOPSTATEDATA_0                             BIT(17)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TURNREQUEST_1                               BIT(16)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TURNDISABLE_1                               BIT(15)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_FORCERXMODE_1                               BIT(14)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_FORCETXSTOPMODE_1                           BIT(13)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_STOPSTATEDATA_1                             BIT(12)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TURNREQUEST_2                               BIT(11)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_DIRECTION_2                                 BIT(10)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TURNDISABLE_2                               BIT(9)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_FORCERXMODE_2                               BIT(8)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_FORCETXSTOPMODE_2                           BIT(7)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_STOPSTATEDATA_2                             BIT(6)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TURNREQUEST_3                               BIT(5)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_DIRECTION_3                                 BIT(4)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_TURNDISABLE_3                               BIT(3)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_FORCERXMODE_3                               BIT(2)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_FORCETXSTOPMODE_3                           BIT(1)
#define BIT_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_DSI_STOPSTATEDATA_3                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_REG_SEL_CFG_0
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTHSCLK                      BIT(31)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSCLK                           BIT(30)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXITCLK                       BIT(29)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTDATAHS_0                   BIT(28)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTESC_0                      BIT(27)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXLPDTESC_0                         BIT(26)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSESC_0                         BIT(25)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXIT_0                        BIT(24)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXTRIGGERESC_0                      BIT(23)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXVALIDESC_0                        BIT(22)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTDATAHS_1                   BIT(21)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTESC_1                      BIT(20)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXLPDTESC_1                         BIT(19)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSESC_1                         BIT(18)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXIT_1                        BIT(17)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXTRIGGERESC_1                      BIT(16)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXVALIDESC_1                        BIT(15)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTDATAHS_2                   BIT(14)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTESC_2                      BIT(13)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXLPDTESC_2                         BIT(12)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSESC_2                         BIT(11)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXIT_2                        BIT(10)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXTRIGGERESC_2                      BIT(9)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXVALIDESC_2                        BIT(8)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTDATAHS_3                   BIT(7)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTESC_3                      BIT(6)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXLPDTESC_3                         BIT(5)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSESC_3                         BIT(4)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXIT_3                        BIT(3)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXTRIGGERESC_3                      BIT(2)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXVALIDESC_3                        BIT(1)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXDATAESC_0                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_REG_SEL_CFG_1
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXDATAESC_1                         BIT(31)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXDATAESC_2                         BIT(30)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXDATAESC_3                         BIT(29)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_PS_PD_S                             BIT(28)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_PS_PD_L                             BIT(27)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_SHUTDOWNZ                           BIT(26)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_RSTZ                                BIT(25)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_ENABLE_0                            BIT(24)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_ENABLE_1                            BIT(23)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_ENABLE_2                            BIT(22)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_ENABLE_3                            BIT(21)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_ENABLECLK                           BIT(20)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_FORCEPLL                            BIT(19)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_BISTON                              BIT(18)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_IF_SEL                              BIT(17)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TRIMBG                              BIT(16)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TX_RCTL                             BIT(15)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_RESERVED                            BIT(14)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TESTDIN                             BIT(13)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TESTEN                              BIT(12)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TESTCLK                             BIT(11)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TESTCLR                             BIT(10)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TURNREQUEST_0                       BIT(9)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TURNDISABLE_0                       BIT(8)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_FORCERXMODE_0                       BIT(7)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_FORCETXSTOPMODE_0                   BIT(6)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TURNREQUEST_1                       BIT(5)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TURNDISABLE_1                       BIT(4)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_FORCERXMODE_1                       BIT(3)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_FORCETXSTOPMODE_1                   BIT(2)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TURNREQUEST_2                       BIT(1)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TURNDISABLE_2                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G2_ANALOG_MIPI_DSI_4LANE_REG_SEL_CFG_2
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_FORCERXMODE_2                       BIT(5)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_FORCETXSTOPMODE_2                   BIT(4)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TURNREQUEST_3                       BIT(3)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TURNDISABLE_3                       BIT(2)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_FORCERXMODE_3                       BIT(1)
#define BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_FORCETXSTOPMODE_3                   BIT(0)


#endif // _ANLG_PHY_G2_REG_H
