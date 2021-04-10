/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-18 10:53:49
 *
 */


#ifndef ANLG_PHY_G18_H
#define ANLG_PHY_G18_H

#define CTL_BASE_ANLG_PHY_G18 0x3241C000


#define REG_ANLG_PHY_G18_ANALOG_THM1_THM1_CTL            ( CTL_BASE_ANLG_PHY_G18 + 0x0000 )
#define REG_ANLG_PHY_G18_ANALOG_THM1_THM1_RESERVED_CTL   ( CTL_BASE_ANLG_PHY_G18 + 0x0004 )
#define REG_ANLG_PHY_G18_ANALOG_THM1_WRAP_GLUE_CTRL      ( CTL_BASE_ANLG_PHY_G18 + 0x0008 )
#define REG_ANLG_PHY_G18_ANALOG_THM1_REG_SEL_CFG_0       ( CTL_BASE_ANLG_PHY_G18 + 0x000C )

/* REG_ANLG_PHY_G18_ANALOG_THM1_THM1_CTL */

#define BIT_ANLG_PHY_G18_ANALOG_THM1_THM_RSTN                                 BIT(27)
#define BIT_ANLG_PHY_G18_ANALOG_THM1_THM_RUN                                  BIT(26)
#define BIT_ANLG_PHY_G18_ANALOG_THM1_THM_PD                                   BIT(25)
#define BIT_ANLG_PHY_G18_ANALOG_THM1_THM_VALID                                BIT(24)
#define BIT_ANLG_PHY_G18_ANALOG_THM1_THM_BG_RBIAS_MODE                        BIT(23)
#define BIT_ANLG_PHY_G18_ANALOG_THM1_THM_TEST_SEL(x)                          (((x) & 0x3) << 21)
#define BIT_ANLG_PHY_G18_ANALOG_THM1_THM_BP_MODE                              BIT(20)
#define BIT_ANLG_PHY_G18_ANALOG_THM1_THM_DATA(x)                              (((x) & 0x3FF) << 10)
#define BIT_ANLG_PHY_G18_ANALOG_THM1_THM_BP_DATA(x)                           (((x) & 0x3FF))

/* REG_ANLG_PHY_G18_ANALOG_THM1_THM1_RESERVED_CTL */

#define BIT_ANLG_PHY_G18_ANALOG_THM1_THM_RESERVED(x)                          (((x) & 0xFFFF))

/* REG_ANLG_PHY_G18_ANALOG_THM1_WRAP_GLUE_CTRL */

#define BIT_ANLG_PHY_G18_ANALOG_THM1_DGB_SEL_THM_RESERVED_BIT0_CONVERT_CYCLE  BIT(1)
#define BIT_ANLG_PHY_G18_ANALOG_THM1_DGB_SEL_THM_RESERVED_BIT3_SENSOR_SEL     BIT(0)

/* REG_ANLG_PHY_G18_ANALOG_THM1_REG_SEL_CFG_0 */

#define BIT_ANLG_PHY_G18_DBG_SEL_ANALOG_THM1_THM_RSTN                         BIT(2)
#define BIT_ANLG_PHY_G18_DBG_SEL_ANALOG_THM1_THM_RUN                          BIT(1)
#define BIT_ANLG_PHY_G18_DBG_SEL_ANALOG_THM1_THM_PD                           BIT(0)


#endif /* ANLG_PHY_G18_H */


