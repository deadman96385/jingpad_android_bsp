/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-18 10:53:50
 *
 */


#ifndef ANLG_PHY_G8_H
#define ANLG_PHY_G8_H

#define CTL_BASE_ANLG_PHY_G8 0x32400000


#define REG_ANLG_PHY_G8_ANALOG_THM2_1_THM2_CTL            ( CTL_BASE_ANLG_PHY_G8 + 0x0000 )
#define REG_ANLG_PHY_G8_ANALOG_THM2_1_WRAP_GLUE_CTRL      ( CTL_BASE_ANLG_PHY_G8 + 0x0008 )

/* REG_ANLG_PHY_G8_ANALOG_THM2_1_THM2_CTL */

#define BIT_ANLG_PHY_G8_ANALOG_THM2_1_THM_BG_RBIAS_MODE                        BIT(13)
#define BIT_ANLG_PHY_G8_ANALOG_THM2_1_THM_TEST_SEL(x)                          (((x) & 0x3) << 11)
#define BIT_ANLG_PHY_G8_ANALOG_THM2_1_THM_BP_MODE                              BIT(10)
#define BIT_ANLG_PHY_G8_ANALOG_THM2_1_THM_BP_DATA(x)                           (((x) & 0x3FF))

/* REG_ANLG_PHY_G8_ANALOG_THM2_1_WRAP_GLUE_CTRL */

#define BIT_ANLG_PHY_G8_ANALOG_THM2_1_DGB_SEL_THM_RESERVED_BIT0_CONVERT_CYCLE  BIT(1)
#define BIT_ANLG_PHY_G8_ANALOG_THM2_1_DGB_SEL_THM_RESERVED_BIT3_SENSOR_SEL     BIT(0)


#endif /* ANLG_PHY_G8_H */


