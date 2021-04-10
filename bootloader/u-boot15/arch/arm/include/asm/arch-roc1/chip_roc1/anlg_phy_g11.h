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


#ifndef ANLG_PHY_G11_H
#define ANLG_PHY_G11_H

#define CTL_BASE_ANLG_PHY_G11 0x323E0000


#define REG_ANLG_PHY_G11_ANALOG_EFUSE0_0_EFUSE_PIN_PW_CTL      ( CTL_BASE_ANLG_PHY_G11 + 0x0000 )
#define REG_ANLG_PHY_G11_ANALOG_EFUSE0_0_REG_SEL_CFG_0         ( CTL_BASE_ANLG_PHY_G11 + 0x0004 )

/* REG_ANLG_PHY_G11_ANALOG_EFUSE0_0_EFUSE_PIN_PW_CTL */

#define BIT_ANLG_PHY_G11_ANALOG_EFUSE0_0_EFS_ENK1          BIT(4)
#define BIT_ANLG_PHY_G11_ANALOG_EFUSE0_0_EFS_ENK2          BIT(3)
#define BIT_ANLG_PHY_G11_ANALOG_EFUSE0_0_EFS_TRCS          BIT(2)
#define BIT_ANLG_PHY_G11_ANALOG_EFUSE0_0_EFS_AT1           BIT(1)
#define BIT_ANLG_PHY_G11_ANALOG_EFUSE0_0_EFS_AT0           BIT(0)

/* REG_ANLG_PHY_G11_ANALOG_EFUSE0_0_REG_SEL_CFG_0 */

#define BIT_ANLG_PHY_G11_DBG_SEL_ANALOG_EFUSE0_0_EFS_ENK1  BIT(1)
#define BIT_ANLG_PHY_G11_DBG_SEL_ANALOG_EFUSE0_0_EFS_ENK2  BIT(0)


#endif /* ANLG_PHY_G11_H */


