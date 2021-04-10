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


#define REG_ANLG_PHY_G4_ANALOG_USB2_UTMI_PIN1             ( CTL_BASE_ANLG_PHY_G4 + 0x0000 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_TX_UTMI_PIN2          ( CTL_BASE_ANLG_PHY_G4 + 0x0004 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_TX_UTMI_PIN3          ( CTL_BASE_ANLG_PHY_G4 + 0x0008 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_TXDATA_PIN            ( CTL_BASE_ANLG_PHY_G4 + 0x000C )
#define REG_ANLG_PHY_G4_ANALOG_USB2_PWR_CTRL_0            ( CTL_BASE_ANLG_PHY_G4 + 0x0010 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_CLK_CTRL_0            ( CTL_BASE_ANLG_PHY_G4 + 0x0014 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_RESET_CTRL_0          ( CTL_BASE_ANLG_PHY_G4 + 0x0018 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_DFX_CTRL_0            ( CTL_BASE_ANLG_PHY_G4 + 0x001C )
#define REG_ANLG_PHY_G4_ANALOG_USB2_WRAP_GLUE_CTRL        ( CTL_BASE_ANLG_PHY_G4 + 0x0020 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_DUMY_RW0              ( CTL_BASE_ANLG_PHY_G4 + 0x0024 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_DUMY_RW1              ( CTL_BASE_ANLG_PHY_G4 + 0x0028 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_DUMY_RO0              ( CTL_BASE_ANLG_PHY_G4 + 0x002C )
#define REG_ANLG_PHY_G4_ANALOG_USB2_DUMY_RO1              ( CTL_BASE_ANLG_PHY_G4 + 0x0030 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_REG_SEL_CFG_0         ( CTL_BASE_ANLG_PHY_G4 + 0x0034 )
#define REG_ANLG_PHY_G4_ANALOG_USB2_REG_SEL_CFG_1         ( CTL_BASE_ANLG_PHY_G4 + 0x0038 )
#define REG_ANLG_PHY_G4_ANALOG_USB3_REF_CLK_CTRL_0        ( CTL_BASE_ANLG_PHY_G4 + 0x003C )
#define REG_ANLG_PHY_G4_ANALOG_USB3_PHY_CTRL_STS_0        ( CTL_BASE_ANLG_PHY_G4 + 0x0040 )
#define REG_ANLG_PHY_G4_ANALOG_USB3_TXDATA                ( CTL_BASE_ANLG_PHY_G4 + 0x0044 )
#define REG_ANLG_PHY_G4_ANALOG_USB3_TXDATA_CTRL2          ( CTL_BASE_ANLG_PHY_G4 + 0x0048 )
#define REG_ANLG_PHY_G4_ANALOG_USB3_TXDATA_CTRL3          ( CTL_BASE_ANLG_PHY_G4 + 0x004C )
#define REG_ANLG_PHY_G4_ANALOG_USB3_TXDATA_CTRL           ( CTL_BASE_ANLG_PHY_G4 + 0x0050 )
#define REG_ANLG_PHY_G4_ANALOG_USB3_RXDATA_CTRL2          ( CTL_BASE_ANLG_PHY_G4 + 0x0054 )
#define REG_ANLG_PHY_G4_ANALOG_USB3_RXDATA                ( CTL_BASE_ANLG_PHY_G4 + 0x0058 )
#define REG_ANLG_PHY_G4_ANALOG_USB3_RXDATA_CTRL3          ( CTL_BASE_ANLG_PHY_G4 + 0x005C )
#define REG_ANLG_PHY_G4_ANALOG_USB3_RXDATA_CTRL           ( CTL_BASE_ANLG_PHY_G4 + 0x0060 )
#define REG_ANLG_PHY_G4_ANALOG_USB3_PCS_CTRL_0            ( CTL_BASE_ANLG_PHY_G4 + 0x0064 )
#define REG_ANLG_PHY_G4_ANALOG_USB3_PMA_CTRL_0            ( CTL_BASE_ANLG_PHY_G4 + 0x0068 )
#define REG_ANLG_PHY_G4_ANALOG_USB3_RESET_CTRL_0          ( CTL_BASE_ANLG_PHY_G4 + 0x006C )
#define REG_ANLG_PHY_G4_ANALOG_USB3_WRAP_GLUE_CTRL        ( CTL_BASE_ANLG_PHY_G4 + 0x0070 )
#define REG_ANLG_PHY_G4_ANALOG_USB3_DUMY_RW0              ( CTL_BASE_ANLG_PHY_G4 + 0x0074 )
#define REG_ANLG_PHY_G4_ANALOG_USB3_DUMY_RW1              ( CTL_BASE_ANLG_PHY_G4 + 0x0078 )
#define REG_ANLG_PHY_G4_ANALOG_USB3_DUMY_RO0              ( CTL_BASE_ANLG_PHY_G4 + 0x007C )
#define REG_ANLG_PHY_G4_ANALOG_USB3_DUMY_RO1              ( CTL_BASE_ANLG_PHY_G4 + 0x0080 )
#define REG_ANLG_PHY_G4_ANALOG_USB3_REG_SEL_CFG_0         ( CTL_BASE_ANLG_PHY_G4 + 0x0084 )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_REF_CLK_CTRL_0        ( CTL_BASE_ANLG_PHY_G4 + 0x0088 )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_M_TX_RMMI_CTRL_0      ( CTL_BASE_ANLG_PHY_G4 + 0x008C )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_M_TX_RMMI_CTRL_1      ( CTL_BASE_ANLG_PHY_G4 + 0x0090 )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_M_TX_RMMI_CTRL_2      ( CTL_BASE_ANLG_PHY_G4 + 0x0094 )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_M_RX_RMMI_CTRL_0      ( CTL_BASE_ANLG_PHY_G4 + 0x0098 )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_M_RX_RMMI_CTRL_1      ( CTL_BASE_ANLG_PHY_G4 + 0x009C )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_M_RX_RMMI_CTRL_2      ( CTL_BASE_ANLG_PHY_G4 + 0x00A0 )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_PHY_CTRL_0            ( CTL_BASE_ANLG_PHY_G4 + 0x00A4 )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_PMS_TEST_CTRL_0       ( CTL_BASE_ANLG_PHY_G4 + 0x00A8 )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_M_TX_CFG_0            ( CTL_BASE_ANLG_PHY_G4 + 0x00AC )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_M_FREQ_CFG_0          ( CTL_BASE_ANLG_PHY_G4 + 0x00B0 )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_RESET_CTRL_0          ( CTL_BASE_ANLG_PHY_G4 + 0x00B4 )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_WRAP_GLUE_CTRL        ( CTL_BASE_ANLG_PHY_G4 + 0x00B8 )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_HOP_REQ               ( CTL_BASE_ANLG_PHY_G4 + 0x00BC )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_INT_HOP_CLR           ( CTL_BASE_ANLG_PHY_G4 + 0x00C0 )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_HOP_SSC_CTRL          ( CTL_BASE_ANLG_PHY_G4 + 0x00C4 )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_RMMI_CLK_CTRL         ( CTL_BASE_ANLG_PHY_G4 + 0x00C8 )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_SLICE_CTRL            ( CTL_BASE_ANLG_PHY_G4 + 0x00CC )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_DUMY_RW0              ( CTL_BASE_ANLG_PHY_G4 + 0x00D0 )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_DUMY_RW1              ( CTL_BASE_ANLG_PHY_G4 + 0x00D4 )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_DUMY_RO0              ( CTL_BASE_ANLG_PHY_G4 + 0x00D8 )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_DUMY_RO1              ( CTL_BASE_ANLG_PHY_G4 + 0x00DC )
#define REG_ANLG_PHY_G4_ANALOG_MPHY_REG_SEL_CFG_0         ( CTL_BASE_ANLG_PHY_G4 + 0x00E0 )
#define REG_ANLG_PHY_G4_ANALOG_26M_DRIVER_PHY_CTRL        ( CTL_BASE_ANLG_PHY_G4 + 0x00E4 )

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_UTMI_PIN1
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_DMPULLDOWN                                       BIT(13)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P1_UTMI_DMPULLDOWN                                       BIT(12)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_DPPULLDOWN                                       BIT(11)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P1_UTMI_DPPULLDOWN                                       BIT(10)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_L1_SUSPENDM                                      BIT(9)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P1_UTMI_L1_SUSPENDM                                      BIT(8)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_OPMODE(x)                                        (((x) & 0x3) << 6)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P1_UTMI_OPMODE(x)                                        (((x) & 0x3) << 4)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_SUSPENDM                                         BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P1_UTMI_SUSPENDM                                         BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_TERMSELECT                                       BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P1_UTMI_TERMSELECT                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_TX_UTMI_PIN2
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_TXDATA(x)                                        (((x) & 0xFF) << 22)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P1_UTMI_TXDATA(x)                                        (((x) & 0xFF) << 14)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_TXVALID                                          BIT(13)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P1_UTMI_TXVALID                                          BIT(12)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_XCVRSELECT(x)                                    (((x) & 0x3) << 10)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P1_UTMI_XCVRSELECT(x)                                    (((x) & 0x3) << 8)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_HSDISC                                           BIT(7)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P1_UTMI_HSDISC                                           BIT(6)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_LINESTATE(x)                                     (((x) & 0x3) << 4)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P1_UTMI_LINESTATE(x)                                     (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_RXACTIVE                                         BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P1_UTMI_RXACTIVE                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_TX_UTMI_PIN3
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_RXDATA(x)                                        (((x) & 0xFF) << 18)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P1_UTMI_RXDATA(x)                                        (((x) & 0xFF) << 10)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_RXERROR                                          BIT(9)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P1_UTMI_RXERROR                                          BIT(8)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_RXVALID                                          BIT(7)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P1_UTMI_RXVALID                                          BIT(6)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_TXREADY                                          BIT(5)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P1_UTMI_TXREADY                                          BIT(4)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_BVALID                                           BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P1_UTMI_BVALID                                           BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_VBUSVALID                                        BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P1_UTMI_VBUSVALID                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_TXDATA_PIN
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_IDPULLUP                                         BIT(11)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P1_UTMI_IDPULLUP                                         BIT(10)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_USBWAKEDETECT_HOST_VNNAON                             BIT(9)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P1_USBWAKEDETECT_HOST_VNNAON                             BIT(8)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_AVALID                                           BIT(7)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P1_UTMI_AVALID                                           BIT(6)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_IDDIG                                            BIT(5)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P1_UTMI_IDDIG                                            BIT(4)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P0_UTMI_SESSEND                                          BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_P1_UTMI_SESSEND                                          BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P0_UTMI_MAINRESET                                        BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_P1_UTMI_MAINRESET                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_PWR_CTRL_0
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_SOC_COLDBOOTED                                           BIT(23)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_SOC_PLLRUNNING                                           BIT(22)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_SOC_PHY_SUS_RSTB                                         BIT(21)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PHY_PWRGOOD                                              BIT(20)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PHY_FWENB                                                BIT(19)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_DFX_PWRACK_OVRD                                          BIT(18)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_BRDPWRGOOD_H                                             BIT(17)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_SPARE(x)                                                 (((x) & 0x1F) << 12)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PWRGATE_EN                                               BIT(11)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PWRGATE_EN_OVRD                                          BIT(10)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PWRGATE_ACK                                              BIT(9)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PWRGATEBYPASS_EN                                         BIT(8)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PWRGATEVNNFW_ENB                                         BIT(7)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_PWRGATE_CLKREQ                                           BIT(6)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_PWRACK_PWRGATE                                           BIT(5)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PP0_SPARE(x)                                             (((x) & 0x3) << 3)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PP1_SPARE(x)                                             (((x) & 0x3) << 1)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_FDFX_POWERGOOD                                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_CLK_CTRL_0
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_CCC_USHIPSUS_PLL_CLKACK                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_RESET_CTRL_0
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PLL_FTAP_TRST_B                                              BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_FTAP_TRST_B                                              BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_APB_RST_B                                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_DFX_CTRL_0
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_DFX_SPARE(x)                                             (((x) & 0x7) << 16)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_DFX_SPARE(x)                                             (((x) & 0x7) << 13)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_SPARE_POWER_GATING(x)                                    (((x) & 0x1F) << 8)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_SPARE_POWER_GATING(x)                                    (((x) & 0x1F) << 3)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PHY_OABSCAN_TDO_F                                            BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_OUSB2PLL_DFX_ASCAN_PRECLK_REFCLK                                  BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_IUSB2PHY_PMC_PHY_DNX_DISABLE                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_WRAP_GLUE_CTRL
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_USB2_SOFT_RSTN                                                    BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_USB2_REF_SEL                                                      BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB2_USB2_REF_DIV_CGM_EN                                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_DUMY_RW0
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_USB2_DUMMY_RW0(x)                                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_DUMY_RW1
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_USB2_DUMMY_RW1(x)                                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_DUMY_RO0
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_USB2_DUMMY_RO0(x)                                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_DUMY_RO1
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB2_USB2_DUMMY_RO1(x)                                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_REG_SEL_CFG_0
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P0_UTMI_DMPULLDOWN                               BIT(31)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P1_UTMI_DMPULLDOWN                               BIT(30)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P0_UTMI_DPPULLDOWN                               BIT(29)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P1_UTMI_DPPULLDOWN                               BIT(28)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P0_UTMI_L1_SUSPENDM                              BIT(27)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P1_UTMI_L1_SUSPENDM                              BIT(26)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P0_UTMI_OPMODE                                   BIT(25)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P1_UTMI_OPMODE                                   BIT(24)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P0_UTMI_SUSPENDM                                 BIT(23)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P1_UTMI_SUSPENDM                                 BIT(22)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P0_UTMI_TERMSELECT                               BIT(21)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P1_UTMI_TERMSELECT                               BIT(20)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P0_UTMI_TXDATA                                   BIT(19)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P1_UTMI_TXDATA                                   BIT(18)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P0_UTMI_TXVALID                                  BIT(17)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P1_UTMI_TXVALID                                  BIT(16)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P0_UTMI_XCVRSELECT                               BIT(15)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P1_UTMI_XCVRSELECT                               BIT(14)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P0_UTMI_MAINRESET                                BIT(13)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_P1_UTMI_MAINRESET                                BIT(12)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_SOC_PHY_SUS_RSTB                                 BIT(11)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_PHY_PWRGOOD                                      BIT(10)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_PHY_FWENB                                        BIT(9)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_BRDPWRGOOD_H                                     BIT(8)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_PWRGATE_EN                                       BIT(7)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_PWRGATE_ACK                                      BIT(6)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_PWRGATEVNNFW_ENB                                 BIT(5)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_FDFX_POWERGOOD                                   BIT(4)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_CCC_USHIPSUS_PLL_CLKACK                          BIT(3)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PLL_FTAP_TRST_B                                      BIT(2)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_FTAP_TRST_B                                      BIT(1)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_APB_RST_B                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB2_REG_SEL_CFG_1
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_DFX_SPARE                                        BIT(1)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB2_IUSB2PHY_SPARE_POWER_GATING                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_REF_CLK_CTRL_0
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PMA_REF_SEL_NT_(x)                                           (((x) & 0x7) << 4)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PMA_REFBUSLEFT2RIGHT_MODE_NT_(x)                             (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PMA_REFBUSRIGHT2LEFT_MODE_NT_(x)                             (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_PHY_CTRL_STS_0
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB3_OCTL_PIPE_PHYSTATUS_L0                                            BIT(15)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_TYPEC_IOSEL_L0_A                                             BIT(14)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_POWERDOWN_L0_(x)                                        (((x) & 0x7) << 11)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_BLOCKALIGNCONTROL_L0                                    BIT(10)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PMA_KEEPALIVE_DISABLE_A                                      BIT(9)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_IPD_PMA_KEEPALIVE_B_NT                                            BIT(8)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_RATE_L0_(x)                                             (((x) & 0x3) << 6)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_DATABUSWIDTH_L0_(x)                                     (((x) & 0x3) << 4)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_PHY_MODE_L0_NT_(x)                                      (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_IRST_PIPE_RST_L0_B_A                                              BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_IRST_POR_B_A                                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_TXDATA
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB3_IDAT_PIPE_TXDATA_L0_(x)                                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_TXDATA_CTRL2
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_TXDATAK_L0_(x)                                          (((x) & 0xF) << 24)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_TXELECIDLE_L0                                           BIT(23)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_TXDTCTRX_LB_L0                                          BIT(22)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_TXDEEMPH_L0_(x)                                         (((x) & 0x3FFFF) << 4)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_TXMARGIN_L0_(x)                                         (((x) & 0x7) << 1)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_TXSWING_L0                                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_TXDATA_CTRL3
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_TXONESZEROS_L0                                          BIT(24)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_GETLOCALPRESETCOEFFICIENTS_L0                           BIT(23)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_LOCALPRESETINDEX_L0_(x)                                 (((x) & 0xF) << 19)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_OCTL_PIPE_LOCALTXCOEFFICIENTSVALID_L0                             BIT(18)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_OCTL_PIPE_LOCALTXPRESETCOEFFICIENTS_L0_(x)                        (((x) & 0x3FFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_TXDATA_CTRL
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_TXSYNCHEADER_L0_(x)                                     (((x) & 0xF) << 3)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_TXDATAVALID_L0                                          BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_TXSTARTBLOCK_L0                                         BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_TXCOMPLIANCE_L0                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_RXDATA_CTRL2
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_RXPOLARITY_L0                                           BIT(5)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_RXTERMINATION_L0                                        BIT(4)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ODAT_PIPE_RXDATAK_L0_(x)                                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_RXDATA
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB3_ODAT_PIPE_RXDATA_L0_(x)                                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_RXDATA_CTRL3
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB3_OCTL_PIPE_RXELECIDLE_L0_A                                         BIT(19)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_OCTL_PIPE_RXVALID_L0                                              BIT(18)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_OCTL_PIPE_RXSTATUS_L0_(x)                                         (((x) & 0x7) << 15)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_OCTL_PIPE_RXSTANDBYSTATUS_L0                                      BIT(14)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_OCTL_PIPE_RXSTARTBLOCK_L0                                         BIT(13)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_OCTL_PIPE_RXSYNCHEADER_L0_(x)                                     (((x) & 0xF) << 9)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_OCTL_PIPE_RXDATAVALID_L0                                          BIT(8)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ODAT_PIPE_LINKEVALUATIONFEEDBACKFIGUREMERIT_L0_(x)                (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_RXDATA_CTRL
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_RXSTANDBY_L0                                            BIT(5)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_RXPRESETHINT_L0_(x)                                     (((x) & 0x7) << 2)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_RXEQCLR_L0                                              BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PIPE_RXEQEVAL_L0                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_PCS_CTRL_0
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PCS_DISCONNECT_NT                                            BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PCS_ISOLATE_NT                                               BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_IRST_PCS_MEM_B_A                                                  BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_OCTL_PCS_DISCONNECT_ACK_NT                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_PMA_CTRL_0
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB3_OCTL_PMA_DISCONNECT_STATUS_A                                      BIT(9)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PMA_SYNTHCKBYPASSEN_NT                                       BIT(8)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PMA_DISCONNECT_A                                             BIT(7)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_IDAT_PMA_RAWPADTX_L0_A                                            BIT(6)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_IDAT_PMA_RAWPADTX_L1_A                                            BIT(5)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ICTL_PMA_1P8VDD2_EN_NT                                            BIT(4)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ODAT_PMA_RAWPADRX_N_L0_A                                          BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ODAT_PMA_RAWPADRX_N_L1_A                                          BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ODAT_PMA_RAWPADRX_P_L0_A                                          BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_ODAT_PMA_RAWPADRX_P_L1_A                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_RESET_CTRL_0
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB3_IRST_TAP_TRST_B_A                                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_WRAP_GLUE_CTRL
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB3_USB3_DATABUSWIDTH(x)                                              (((x) & 0x3) << 3)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_USB3_POWER_PRESENT                                                BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_USB3_SOFT_RSTN                                                    BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_USB3_USB3_TYPEC_INVERT_SEL                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_DUMY_RW0
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB3_USB3_DUMMY_RW0(x)                                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_DUMY_RW1
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB3_USB3_DUMMY_RW1(x)                                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_DUMY_RO0
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB3_USB3_DUMMY_RO0(x)                                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_DUMY_RO1
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_USB3_USB3_DUMMY_RO1(x)                                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_USB3_REG_SEL_CFG_0
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_TYPEC_IOSEL_L0_A                                     BIT(29)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_POWERDOWN_L0_                                   BIT(28)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_BLOCKALIGNCONTROL_L0                            BIT(27)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PMA_KEEPALIVE_DISABLE_A                              BIT(26)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_IPD_PMA_KEEPALIVE_B_NT                                    BIT(25)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_DATABUSWIDTH_L0_                                BIT(24)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_PHY_MODE_L0_NT_                                 BIT(23)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_IRST_PIPE_RST_L0_B_A                                      BIT(22)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_IRST_POR_B_A                                              BIT(21)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_IDAT_PIPE_TXDATA_L0_                                      BIT(20)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_TXDATAK_L0_                                     BIT(19)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_TXELECIDLE_L0                                   BIT(18)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_TXDTCTRX_LB_L0                                  BIT(17)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_TXDEEMPH_L0_                                    BIT(16)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_TXMARGIN_L0_                                    BIT(15)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_TXSWING_L0                                      BIT(14)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_TXONESZEROS_L0                                  BIT(13)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_GETLOCALPRESETCOEFFICIENTS_L0                   BIT(12)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_LOCALPRESETINDEX_L0_                            BIT(11)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_TXSYNCHEADER_L0_                                BIT(10)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_TXDATAVALID_L0                                  BIT(9)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_TXSTARTBLOCK_L0                                 BIT(8)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_TXCOMPLIANCE_L0                                 BIT(7)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_RXPOLARITY_L0                                   BIT(6)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_RXTERMINATION_L0                                BIT(5)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_RXSTANDBY_L0                                    BIT(4)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PIPE_RXEQEVAL_L0                                     BIT(3)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_IRST_PCS_MEM_B_A                                          BIT(2)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_ICTL_PMA_DISCONNECT_A                                     BIT(1)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_USB3_IRST_TAP_TRST_B_A                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_REF_CLK_CTRL_0
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_MPHY_REF_SEL_NT_(x)                                          (((x) & 0x7) << 4)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_MPHY_REFBUSLEFT2RIGHT_MODE_NT_(x)                            (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_MPHY_REFBUSRIGHT2LEFT_MODE_NT_(x)                            (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_M_TX_RMMI_CTRL_0
// Register Offset : 0x008C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_RMMI_TX_ATTRID_L0_(x)                                        (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_RMMI_TX_ATTRWRVAL_L0_(x)                                     (((x) & 0xFF) << 8)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_RMMI_TX_ATTRWRN_L0                                           BIT(7)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_RMMI_TX_INLNCFG_L0                                           BIT(6)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_RMMI_TX_CFGENBL_L0                                           BIT(5)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_RMMI_TX_CFGUPDT_L0                                           BIT(4)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_RMMI_TX_LINERESET_L0                                         BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_RMMI_TX_CONTROLLED_ACTTIMER_L0                               BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_RMMI_TX_DIFNDRIVE_L0                                         BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_IRST_RMMI_TX_RESET_L0_A                                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_M_TX_RMMI_CTRL_1
// Register Offset : 0x0090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_OCTL_RMMI_TX_CFGRDYN_L0                                           BIT(8)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_OCTL_RMMI_TX_ATTRRDVAL_L0_(x)                                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_M_TX_RMMI_CTRL_2
// Register Offset : 0x0094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_IDAT_RMMI_TX_PROTDORDY_L0_(x)                                     (((x) & 0xF) << 7)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_IDAT_RMMI_TX_DATANCTRL_L0_(x)                                     (((x) & 0xF) << 3)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_IDAT_RMMI_TX_BURST_L0                                             BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ODAT_RMMI_TX_SAVESTATE_STATUS_L0_B                                BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ODAT_RMMI_TX_PHYDIRDY_L0                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_M_RX_RMMI_CTRL_0
// Register Offset : 0x0098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_RMMI_RX_ATTRID_L0_(x)                                        (((x) & 0xFF) << 13)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_RMMI_RX_ATTRWRVAL_L0_(x)                                     (((x) & 0xFF) << 5)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_RMMI_RX_ATTRWRN_L0                                           BIT(4)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_RMMI_RX_INLNCFG_L0                                           BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_RMMI_RX_CFGENBL_L0                                           BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_RMMI_RX_CFGUPDT_L0                                           BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_IRST_RMMI_RX_RESET_L0_A                                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_M_RX_RMMI_CTRL_1
// Register Offset : 0x009C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_OCTL_RMMI_RX_LINERESET_L0                                         BIT(11)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_OCTL_RMMI_RX_CFGRDYN_L0                                           BIT(10)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_OCTL_RMMI_RX_HIBERN8_EXIT_TYPE1_L0                                BIT(9)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_OCTL_RMMI_RX_LCCRDDET_L0                                          BIT(8)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_OCTL_RMMI_RX_ATTRRDVAL_L0_(x)                                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_M_RX_RMMI_CTRL_2
// Register Offset : 0x00A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ODAT_RMMI_RX_DATANCTRL_L0_(x)                                     (((x) & 0xF) << 9)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ODAT_RMMI_RX_SYMBOLERR_L0_(x)                                     (((x) & 0xF) << 5)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ODAT_RMMI_RX_BURST_L0                                             BIT(4)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ODAT_RMMI_RX_PHYDORDY_L0_(x)                                      (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_PHY_CTRL_0
// Register Offset : 0x00A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_OCTL_MPHY_DISCONNECT_ACK_NT                                       BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_MPHY_DISCONNECT_NT                                           BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_MPHY_ISOLATE_NT                                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_PMS_TEST_CTRL_0
// Register Offset : 0x00A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_IRST_MPHY_POR_B_A                                                 BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_MPHY_1P8VDD2_EN_NT                                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_M_TX_CFG_0
// Register Offset : 0x00AC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_MPHY_TX_REF_FREQSEL_NT_(x)                                   (((x) & 0x3) << 4)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_MPHY_RX_REF_FREQSEL_L0_NT_(x)                                (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_MPHY_TX_READY_L0                                             BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_OCTL_MPHY_TX_READY_L0                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_M_FREQ_CFG_0
// Register Offset : 0x00B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_MPHY_SYNTHFREQ_HOP_NT_(x)                                    (((x) & 0x3) << 6)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_MPHY_SYNTHFREQ_REQ_A                                         BIT(5)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_MPHY_SYNTHFREQ_SSC_EN_A                                      BIT(4)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_MPHY_SYNTHPWR_REQ_A                                          BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_ICTL_MPHY_SYNTHPWR_STATE_NT                                       BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_OCTL_MPHY_SYNTHFREQ_ACK_A                                         BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_OCTL_MPHY_SYNTHPWR_ACK_A                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_RESET_CTRL_0
// Register Offset : 0x00B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_IRST_MPHY_TRST_B_A                                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_WRAP_GLUE_CTRL
// Register Offset : 0x00B8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_MPHY_CLK_MUX_SEL                                                  BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_MPHY_SOFT_RSTN                                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_HOP_REQ
// Register Offset : 0x00BC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_MPHY_HOP_REQ                                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_INT_HOP_CLR
// Register Offset : 0x00C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_MPHY_INT_HOP_CLEAR                                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_HOP_SSC_CTRL
// Register Offset : 0x00C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_MPHY_INT_HOP_OK_RAW                                               BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_MPHY_INT_HOP_MASK                                                 BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_MPHY_PLL_STATE_REQ                                                BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_MPHY_PLL_STATE_ACTUAL                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_RMMI_CLK_CTRL
// Register Offset : 0x00C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_C2G_RMMI_TX_SYMBOL_SEL                                            BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_G2C_RMMI_TX_SYMBOL_SEL                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_SLICE_CTRL
// Register Offset : 0x00CC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_RX_PIPE_MODE(x)                                                   (((x) & 0x3) << 1)
#define BIT_ANLG_PHY_G4_ANALOG_MPHY_RX_PIPE_SW_BYP                                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_DUMY_RW0
// Register Offset : 0x00D0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_MPHY_DUMMY_RW0(x)                                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_DUMY_RW1
// Register Offset : 0x00D4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_MPHY_DUMMY_RW1(x)                                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_DUMY_RO0
// Register Offset : 0x00D8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_MPHY_DUMMY_RO0(x)                                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_DUMY_RO1
// Register Offset : 0x00DC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_MPHY_MPHY_DUMMY_RO1(x)                                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_MPHY_REG_SEL_CFG_0
// Register Offset : 0x00E0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_RMMI_TX_ATTRID_L0_                                   BIT(25)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_RMMI_TX_ATTRWRVAL_L0_                                BIT(24)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_RMMI_TX_ATTRWRN_L0                                   BIT(23)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_RMMI_TX_INLNCFG_L0                                   BIT(22)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_RMMI_TX_CFGENBL_L0                                   BIT(21)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_RMMI_TX_CFGUPDT_L0                                   BIT(20)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_RMMI_TX_LINERESET_L0                                 BIT(19)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_RMMI_TX_CONTROLLED_ACTTIMER_L0                       BIT(18)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_RMMI_TX_DIFNDRIVE_L0                                 BIT(17)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_IRST_RMMI_TX_RESET_L0_A                                   BIT(16)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_IDAT_RMMI_TX_PROTDORDY_L0_                                BIT(15)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_IDAT_RMMI_TX_DATANCTRL_L0_                                BIT(14)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_IDAT_RMMI_TX_BURST_L0                                     BIT(13)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_RMMI_RX_ATTRID_L0_                                   BIT(12)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_RMMI_RX_ATTRWRVAL_L0_                                BIT(11)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_RMMI_RX_ATTRWRN_L0                                   BIT(10)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_RMMI_RX_INLNCFG_L0                                   BIT(9)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_RMMI_RX_CFGENBL_L0                                   BIT(8)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_RMMI_RX_CFGUPDT_L0                                   BIT(7)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_IRST_RMMI_RX_RESET_L0_A                                   BIT(6)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_IRST_MPHY_POR_B_A                                         BIT(5)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_MPHY_TX_READY_L0                                     BIT(4)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_MPHY_SYNTHFREQ_REQ_A                                 BIT(3)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_MPHY_SYNTHPWR_REQ_A                                  BIT(2)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_ICTL_MPHY_SYNTHPWR_STATE_NT                               BIT(1)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_MPHY_IRST_MPHY_TRST_B_A                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G4_ANALOG_26M_DRIVER_PHY_CTRL
// Register Offset : 0x00E4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G4_ANALOG_26M_DRIVER_CLK26M_UFS_PD                                               BIT(12)
#define BIT_ANLG_PHY_G4_ANALOG_26M_DRIVER_CLK26M_OUT_PD                                               BIT(11)
#define BIT_ANLG_PHY_G4_ANALOG_26M_DRIVER_CLK26M_USB30_PD                                             BIT(10)
#define BIT_ANLG_PHY_G4_ANALOG_26M_DRIVER_DRIVER_26MHZ_RESERVED(x)                                    (((x) & 0x3FF))


#endif // _ANLG_PHY_G4_REG_H
