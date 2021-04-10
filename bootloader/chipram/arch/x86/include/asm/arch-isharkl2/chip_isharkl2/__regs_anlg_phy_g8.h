/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _ANLG_PHY_G8_REG_H
#define _ANLG_PHY_G8_REG_H

#define CTL_BASE_ANLG_PHY_G8 SPRD_ANLG_PHY_G8


#define REG_ANLG_PHY_G8_ANALOG_DSI_1_CTRL_REG0                 ( CTL_BASE_ANLG_PHY_G8 + 0x0000 )
#define REG_ANLG_PHY_G8_ANALOG_DSI_1_WRAP_GLUE_CTRL            ( CTL_BASE_ANLG_PHY_G8 + 0x0004 )
#define REG_ANLG_PHY_G8_ANALOG_DSI_1_26M_RECEIVER_CTRL         ( CTL_BASE_ANLG_PHY_G8 + 0x0008 )
#define REG_ANLG_PHY_G8_ANALOG_DSI_1_WRAP_GLUE_CTRL2           ( CTL_BASE_ANLG_PHY_G8 + 0x000C )
#define REG_ANLG_PHY_G8_ANALOG_DSI_1_REG_SEL_CFG_0             ( CTL_BASE_ANLG_PHY_G8 + 0x0010 )
#define REG_ANLG_PHY_G8_ANALOG_CSI_0_PWR_CTRL_REG0             ( CTL_BASE_ANLG_PHY_G8 + 0x0014 )
#define REG_ANLG_PHY_G8_ANALOG_CSI_0_PPI_CTRL_REG0             ( CTL_BASE_ANLG_PHY_G8 + 0x0018 )
#define REG_ANLG_PHY_G8_ANALOG_CSI_0_REG_SEL_CFG_0             ( CTL_BASE_ANLG_PHY_G8 + 0x001C )
#define REG_ANLG_PHY_G8_ANALOG_CSI_1_PWR_CTRL_REG0             ( CTL_BASE_ANLG_PHY_G8 + 0x0020 )
#define REG_ANLG_PHY_G8_ANALOG_CSI_1_PPI_CTRL_REG0             ( CTL_BASE_ANLG_PHY_G8 + 0x0024 )
#define REG_ANLG_PHY_G8_ANALOG_CSI_1_REG_SEL_CFG_0             ( CTL_BASE_ANLG_PHY_G8 + 0x0028 )
#define REG_ANLG_PHY_G8_ANALOG_26M_RECEIVER_PHY_CTRL           ( CTL_BASE_ANLG_PHY_G8 + 0x002C )
#define REG_ANLG_PHY_G8_ANALOG_26M_RECEIVER_LDO_CTRL           ( CTL_BASE_ANLG_PHY_G8 + 0x0030 )
#define REG_ANLG_PHY_G8_ANALOG_26M_RECEIVER_REG_SEL_CFG_0      ( CTL_BASE_ANLG_PHY_G8 + 0x0034 )

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G8_ANALOG_DSI_1_CTRL_REG0
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_O_DSPLL_LOCK_STATUS                              BIT(22)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_I_RST_APB_N                                      BIT(21)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_I_RST_SYS_N                                      BIT(20)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_I_CTL_PHYFORCEPLL                                BIT(19)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_I_FTAP_FDFX_POWERGOOD                            BIT(18)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_O_STS_PLLOK                                      BIT(17)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_O_STS_RXULPSACTIVENOT_DLN                        BIT(16)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_O_STS_AFELATCHOUTCP                              BIT(15)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_I_CTL_TXLATCHEN_N                                BIT(14)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_I_CTL_LATCHRESET_B                               BIT(13)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_I_CTL_FORCERXMODE                                BIT(12)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_I_CTL_TURNDISABLE                                BIT(11)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_I_CTL_FORCETXSTOPMODE(x)                         (((x) & 0xF) << 7)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_I_CTL_TXSKEWCALHS(x)                             (((x) & 0xF) << 3)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_I_CTL_FWEN_B                                     BIT(2)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_I_CTL_PGEN                                       BIT(1)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_O_CTL_PGENOUT                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G8_ANALOG_DSI_1_WRAP_GLUE_CTRL
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_DSI2_I_CTL_ENABLE_CLN                            BIT(26)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_DSI2_I_CTL_PHYFORCEPLL                           BIT(25)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_DSI2_I_CTL_TURNREQUEST                           BIT(24)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_DSI2_I_CTL_TXLPDTESC                             BIT(23)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_DSI2_I_CTL_TXULPSCLK_CLN                         BIT(22)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_DSI2_I_CTL_TXULPSEXIT_CLN                        BIT(21)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_DSI2_I_CTL_TXVALIDESC                            BIT(20)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_DSI2_I_CTL_ENABLE_DLN(x)                         (((x) & 0xF) << 16)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_DSI2_I_CTL_TXREQUESTESC(x)                       (((x) & 0xF) << 12)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_DSI2_I_CTL_TXTRIGGERESC(x)                       (((x) & 0xF) << 8)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_DSI2_I_RST_SYS_N                                 BIT(7)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_CSIDSI_I_CTL_CSICLKSEL(x)                        (((x) & 0x3) << 5)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_REFCLK_SEL                                       BIT(4)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_CSI_OBS_SEL(x)                                   (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_DSI_OBS_SEL(x)                                   (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G8_ANALOG_DSI_1_26M_RECEIVER_CTRL
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_RECEIVER_26MHZ_CUR_SEL                           BIT(17)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_RECEIVER_26MHZ_PD                                BIT(16)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_RECEIVER_26MHZ_BG_TRIM(x)                        (((x) & 0x3F) << 10)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_RECEIVER_26MHZ_RESERVED(x)                       (((x) & 0x3FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G8_ANALOG_DSI_1_WRAP_GLUE_CTRL2
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_TXESCCLK_SEL(x)                                  (((x) & 0x3) << 16)
#define BIT_ANLG_PHY_G8_ANALOG_DSI_1_DUMMY_RW(x)                                      (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G8_ANALOG_DSI_1_REG_SEL_CFG_0
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G8_DBG_SEL_ANALOG_DSI_1_I_RST_APB_N                              BIT(3)
#define BIT_ANLG_PHY_G8_DBG_SEL_ANALOG_DSI_1_I_RST_SYS_N                              BIT(2)
#define BIT_ANLG_PHY_G8_DBG_SEL_ANALOG_DSI_1_I_CTL_PHYFORCEPLL                        BIT(1)
#define BIT_ANLG_PHY_G8_DBG_SEL_ANALOG_DSI_1_I_CTL_TXSKEWCALHS                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G8_ANALOG_CSI_0_PWR_CTRL_REG0
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G8_ANALOG_CSI_0_I_SYS_RST_B                                      BIT(4)
#define BIT_ANLG_PHY_G8_ANALOG_CSI_0_I_DFX_PWRGOOD                                    BIT(3)
#define BIT_ANLG_PHY_G8_ANALOG_CSI_0_I_CTL_FWEN_B                                     BIT(2)
#define BIT_ANLG_PHY_G8_ANALOG_CSI_0_I_CTL_PGEN                                       BIT(1)
#define BIT_ANLG_PHY_G8_ANALOG_CSI_0_O_CTL_PGENOUT                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G8_ANALOG_CSI_0_PPI_CTRL_REG0
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G8_ANALOG_CSI_0_I_CTL_ENABLE_CLN                                 BIT(13)
#define BIT_ANLG_PHY_G8_ANALOG_CSI_0_O_STS_ULPSACTIVECLKNOT_CLN                       BIT(12)
#define BIT_ANLG_PHY_G8_ANALOG_CSI_0_O_STS_ERRCONTROL_DLN(x)                          (((x) & 0xF) << 8)
#define BIT_ANLG_PHY_G8_ANALOG_CSI_0_O_STS_ULPSACTIVENOT_DLN(x)                       (((x) & 0xF) << 4)
#define BIT_ANLG_PHY_G8_ANALOG_CSI_0_O_STS_RXACTIVEHS_DLN(x)                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G8_ANALOG_CSI_0_REG_SEL_CFG_0
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G8_DBG_SEL_ANALOG_CSI_0_I_SYS_RST_B                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G8_ANALOG_CSI_1_PWR_CTRL_REG0
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G8_ANALOG_CSI_1_I_SYS_RST_B                                      BIT(4)
#define BIT_ANLG_PHY_G8_ANALOG_CSI_1_I_DFX_PWRGOOD                                    BIT(3)
#define BIT_ANLG_PHY_G8_ANALOG_CSI_1_I_CTL_FWEN_B                                     BIT(2)
#define BIT_ANLG_PHY_G8_ANALOG_CSI_1_I_CTL_PGEN                                       BIT(1)
#define BIT_ANLG_PHY_G8_ANALOG_CSI_1_O_CTL_PGENOUT                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G8_ANALOG_CSI_1_PPI_CTRL_REG0
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G8_ANALOG_CSI_1_I_CTL_ENABLE_CLN                                 BIT(7)
#define BIT_ANLG_PHY_G8_ANALOG_CSI_1_O_STS_ULPSACTIVECLKNOT_CLN                       BIT(6)
#define BIT_ANLG_PHY_G8_ANALOG_CSI_1_O_STS_ERRCONTROL_DLN(x)                          (((x) & 0x3) << 4)
#define BIT_ANLG_PHY_G8_ANALOG_CSI_1_O_STS_ULPSACTIVENOT_DLN(x)                       (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G8_ANALOG_CSI_1_O_STS_RXACTIVEHS_DLN(x)                          (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G8_ANALOG_CSI_1_REG_SEL_CFG_0
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G8_DBG_SEL_ANALOG_CSI_1_I_SYS_RST_B                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G8_ANALOG_26M_RECEIVER_PHY_CTRL
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G8_ANALOG_26M_RECEIVER_RECEIVER_26MHZ_CUR_SEL                    BIT(17)
#define BIT_ANLG_PHY_G8_ANALOG_26M_RECEIVER_RECEIVER_26MHZ_PD                         BIT(16)
#define BIT_ANLG_PHY_G8_ANALOG_26M_RECEIVER_RECEIVER_26MHZ_BG_TRIM(x)                 (((x) & 0x3F) << 10)
#define BIT_ANLG_PHY_G8_ANALOG_26M_RECEIVER_RECEIVER_26MHZ_RESERVED(x)                (((x) & 0x3FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G8_ANALOG_26M_RECEIVER_LDO_CTRL
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G8_ANALOG_26M_RECEIVER_LDO1P2_PD                                 BIT(7)
#define BIT_ANLG_PHY_G8_ANALOG_26M_RECEIVER_LDO1P2_SHPT_PD                            BIT(6)
#define BIT_ANLG_PHY_G8_ANALOG_26M_RECEIVER_LDO1P2_SHT_CTRL                           BIT(5)
#define BIT_ANLG_PHY_G8_ANALOG_26M_RECEIVER_LDO1P2_V(x)                               (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G8_ANALOG_26M_RECEIVER_REG_SEL_CFG_0
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G8_DBG_SEL_ANALOG_26M_RECEIVER_LDO1P2_PD                         BIT(0)


#endif // _ANLG_PHY_G8_REG_H
