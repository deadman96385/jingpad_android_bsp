/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _ANLG_PHY_G4_REG_H
#define _ANLG_PHY_G4_REG_H

#define CTL_BASE_ANLG_PHY_G4 SPRD_ANLG_PHY_G4


#define REG_ANLG_PHY_G4_ANALOG_USB2_UTMI_PIN1           ( CTL_BASE_ANLG_PHY_G4 + 0x0000 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_TX_UTMI_PIN2        ( CTL_BASE_ANLG_PHY_G4 + 0x0004 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_TX_UTMI_PIN3        ( CTL_BASE_ANLG_PHY_G4 + 0x0008 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_TXDATA_PIN          ( CTL_BASE_ANLG_PHY_G4 + 0x000C )
#define REG_ANLG_PHY_G4_ANALOG_USB2_PWR_CTRL_0          ( CTL_BASE_ANLG_PHY_G4 + 0x0010 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_DFX_CTRL_0          ( CTL_BASE_ANLG_PHY_G4 + 0x0014 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_WRAP_GLUE_CTRL      ( CTL_BASE_ANLG_PHY_G4 + 0x0018 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_DUMY_RW0            ( CTL_BASE_ANLG_PHY_G4 + 0x001C )
#define REG_ANLG_PHY_G4_ANALOG_USB2_DUMY_RW1            ( CTL_BASE_ANLG_PHY_G4 + 0x0020 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_DUMY_RO0            ( CTL_BASE_ANLG_PHY_G4 + 0x0024 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_DUMY_RO1            ( CTL_BASE_ANLG_PHY_G4 + 0x0028 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_CGM_CTRL_0          ( CTL_BASE_ANLG_PHY_G4 + 0x002C )
#define REG_ANLG_PHY_G4_ANALOG_USB2_REG_SEL_CFG_0       ( CTL_BASE_ANLG_PHY_G4 + 0x0030 )

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_UTMI_PIN1
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_DMPULLDOWN                             BIT(6)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_DPPULLDOWN                             BIT(5)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_L1_SUSPENDM                            BIT(4)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_OPMODE(x)                              (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_SUSPENDM                               BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_TERMSELECT                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_TX_UTMI_PIN2
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_TXDATA(x)                              (((x) & 0xFF) << 7)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_TXVALID                                BIT(6)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_XCVRSELECT(x)                          (((x) & 0x3) << 4)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_HSDISC                                 BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_LINESTATE(x)                           (((x) & 0x3) << 1)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_RXACTIVE                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_TX_UTMI_PIN3
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_RXDATA(x)                              (((x) & 0xFF) << 5)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_RXERROR                                BIT(4)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_RXVALID                                BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_TXREADY                                BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_BVALID                                 BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_VBUSVALID                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_TXDATA_PIN
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_IDPULLUP                               BIT(5)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_USBWAKEDETECT_HOST_VNNAON                   BIT(4)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_AVALID                                 BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_IDDIG                                  BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_SESSEND                                BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_MAINRESET                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_PWR_CTRL_0
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_SOC_COLDBOOTED                                 BIT(21)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_SOC_PLLRUNNING                                 BIT(20)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_SOC_PHY_SUS_RSTB                               BIT(19)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PHY_PWRGOOD                                    BIT(18)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PHY_FWENB                                      BIT(17)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_DFX_PWRACK_OVRD                                BIT(16)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_BRDPWRGOOD_H                                   BIT(15)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_SPARE(x)                                       (((x) & 0x1F) << 10)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PWRGATE_EN                                     BIT(9)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PWRGATE_EN_OVRD                                BIT(8)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PWRGATE_ACK                                    BIT(7)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PWRGATEBYPASS_EN                               BIT(6)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PWRGATEVNNFW_ENB                               BIT(5)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_PWRGATE_CLKREQ                                 BIT(4)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_PWRACK_PWRGATE                                 BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PP0_SPARE(x)                                   (((x) & 0x3) << 1)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_FDFX_POWERGOOD                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_DFX_CTRL_0
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_DFX_SPARE(x)                                   (((x) & 0x7) << 16)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_DFX_SPARE(x)                                   (((x) & 0x7) << 13)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_SPARE_POWER_GATING(x)                          (((x) & 0x1F) << 8)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_SPARE_POWER_GATING(x)                          (((x) & 0x1F) << 3)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_OABSCAN_TDO_F                                  BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PLL_DFX_ASCAN_PRECLK_REFCLK                        BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PMC_PHY_DNX_DISABLE                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_WRAP_GLUE_CTRL
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_USB2_SOFT_RSTN                                          BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_USB2_REF_SEL                                            BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_USB2_REF_DIV_CGM_EN                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_DUMY_RW0
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_USB2_DUMMY_RW0(x)                                       (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_DUMY_RW1
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_USB2_DUMMY_RW1(x)                                       (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_DUMY_RO0
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_USB2_DUMMY_RO0(x)                                       (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_DUMY_RO1
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_USB2_DUMMY_RO1(x)                                       (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_CGM_CTRL_0
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_CGM_USB_REF_EN                                          BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_CGM_FSCAN_REFCGM_EN                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_REG_SEL_CFG_0
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P0_UTMI_L1_SUSPENDM                    BIT(17)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P0_UTMI_OPMODE                         BIT(16)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P0_UTMI_SUSPENDM                       BIT(15)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P0_UTMI_TERMSELECT                     BIT(14)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P0_UTMI_TXDATA                         BIT(13)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P0_UTMI_TXVALID                        BIT(12)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P0_UTMI_XCVRSELECT                     BIT(11)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P0_UTMI_MAINRESET                      BIT(10)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_SOC_PHY_SUS_RSTB                       BIT(9)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_PHY_PWRGOOD                            BIT(8)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_PHY_FWENB                              BIT(7)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_BRDPWRGOOD_H                           BIT(6)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_PWRGATE_EN                             BIT(5)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_PWRGATE_ACK                            BIT(4)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_PWRGATEVNNFW_ENB                       BIT(3)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_FDFX_POWERGOOD                         BIT(2)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_DFX_SPARE                              BIT(1)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_SPARE_POWER_GATING                     BIT(0)


#endif // _ANLG_PHY_G4_REG_H
