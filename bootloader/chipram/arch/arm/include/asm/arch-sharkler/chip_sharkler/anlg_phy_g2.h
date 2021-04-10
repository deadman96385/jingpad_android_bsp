/*
 * Copyright (C) 2019 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2019-01-07 15:09:47
 *
 */


#ifndef ANLG_PHY_G2_H
#define ANLG_PHY_G2_H

#define CTL_BASE_ANLG_PHY_G2 0x403D0000


#define REG_ANLG_PHY_G2_ANALOG_THM_THM0_CTRL_0      ( CTL_BASE_ANLG_PHY_G2 + 0x0000 )
#define REG_ANLG_PHY_G2_ANALOG_THM_THM0_CTRL_1      ( CTL_BASE_ANLG_PHY_G2 + 0x0004 )

/* REG_ANLG_PHY_G2_ANALOG_THM_THM0_CTRL_0 */

#define BIT_ANLG_PHY_G2_ANALOG_THM_THM_BG_RBIAS_MODE  BIT(2)
#define BIT_ANLG_PHY_G2_ANALOG_THM_THM_TEST_SEL(x)    (((x) & 0x3))

/* REG_ANLG_PHY_G2_ANALOG_THM_THM0_CTRL_1 */

#define BIT_ANLG_PHY_G2_ANALOG_THM_THM_BP_MODE        BIT(24)
#define BIT_ANLG_PHY_G2_ANALOG_THM_THM_BP_DATA(x)     (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G2_ANALOG_THM_THM_RESERVED(x)    (((x) & 0xFFFF))


#endif /* ANLG_PHY_G2_H */


