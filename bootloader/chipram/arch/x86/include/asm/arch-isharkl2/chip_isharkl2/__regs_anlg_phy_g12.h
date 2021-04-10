/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _ANLG_PHY_G12_REG_H
#define _ANLG_PHY_G12_REG_H

#define CTL_BASE_ANLG_PHY_G12 SPRD_ANLG_PHY_G12


#define REG_ANLG_PHY_G12_ANALOG_BIA_THM_1_PHY_BIA_THM_OPT        ( CTL_BASE_ANLG_PHY_G12 + 0x0000 )
#define REG_ANLG_PHY_G12_ANALOG_BIA_THM_1_PHY_BIA_THM_CTRL0      ( CTL_BASE_ANLG_PHY_G12 + 0x0004 )
#define REG_ANLG_PHY_G12_ANALOG_BIA_THM_1_REG_SEL_CFG_0          ( CTL_BASE_ANLG_PHY_G12 + 0x0008 )

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G12_ANALOG_BIA_THM_1_PHY_BIA_THM_OPT
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G12_ANALOG_BIA_THM_1_ICALGAMMA(x)                             (((x) & 0x1F) << 24)
#define BIT_ANLG_PHY_G12_ANALOG_BIA_THM_1_ICALDATOFFSET(x)                         (((x) & 0x7FF) << 13)
#define BIT_ANLG_PHY_G12_ANALOG_BIA_THM_1_ICALDATSLOPE(x)                          (((x) & 0x1FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G12_ANALOG_BIA_THM_1_PHY_BIA_THM_CTRL0
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G12_ANALOG_BIA_THM_1_ICALCONFIGSEL(x)                         (((x) & 0x3) << 5)
#define BIT_ANLG_PHY_G12_ANALOG_BIA_THM_1_OTSTEMPERATURETRIP                       BIT(4)
#define BIT_ANLG_PHY_G12_ANALOG_BIA_THM_1_ITSEN                                    BIT(3)
#define BIT_ANLG_PHY_G12_ANALOG_BIA_THM_1_ITSPOWERGOOD                             BIT(2)
#define BIT_ANLG_PHY_G12_ANALOG_BIA_THM_1_IANACHOPCTR                              BIT(1)
#define BIT_ANLG_PHY_G12_ANALOG_BIA_THM_1_ITSRST                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G12_ANALOG_BIA_THM_1_REG_SEL_CFG_0
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G12_DBG_SEL_ANALOG_BIA_THM_1_ICALGAMMA                        BIT(7)
#define BIT_ANLG_PHY_G12_DBG_SEL_ANALOG_BIA_THM_1_ICALDATOFFSET                    BIT(6)
#define BIT_ANLG_PHY_G12_DBG_SEL_ANALOG_BIA_THM_1_ICALDATSLOPE                     BIT(5)
#define BIT_ANLG_PHY_G12_DBG_SEL_ANALOG_BIA_THM_1_ICALCONFIGSEL                    BIT(4)
#define BIT_ANLG_PHY_G12_DBG_SEL_ANALOG_BIA_THM_1_ITSEN                            BIT(3)
#define BIT_ANLG_PHY_G12_DBG_SEL_ANALOG_BIA_THM_1_ITSPOWERGOOD                     BIT(2)
#define BIT_ANLG_PHY_G12_DBG_SEL_ANALOG_BIA_THM_1_IANACHOPCTR                      BIT(1)
#define BIT_ANLG_PHY_G12_DBG_SEL_ANALOG_BIA_THM_1_ITSRST                           BIT(0)


#endif // _ANLG_PHY_G12_REG_H
