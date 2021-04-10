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


#ifndef ANLG_PHY_G19_H
#define ANLG_PHY_G19_H

#define CTL_BASE_ANLG_PHY_G19 0x323E8000


#define REG_ANLG_PHY_G19_ANALOG_EFUSE1_EFUSE_PIN_PW_CTL      ( CTL_BASE_ANLG_PHY_G19 + 0x0000 )

/* REG_ANLG_PHY_G19_ANALOG_EFUSE1_EFUSE_PIN_PW_CTL */

#define BIT_ANLG_PHY_G19_ANALOG_EFUSE1_EFS_TRCS  BIT(2)
#define BIT_ANLG_PHY_G19_ANALOG_EFUSE1_EFS_AT1   BIT(1)
#define BIT_ANLG_PHY_G19_ANALOG_EFUSE1_EFS_AT0   BIT(0)


#endif /* ANLG_PHY_G19_H */


