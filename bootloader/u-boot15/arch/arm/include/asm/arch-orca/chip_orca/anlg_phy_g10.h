/*
 * Copyright (C) 2019 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2019-02-11 15:07:05
 *
 */


#ifndef ANLG_PHY_G10_H
#define ANLG_PHY_G10_H

#define CTL_BASE_ANLG_PHY_G10 0x63520000


#define REG_ANLG_PHY_G10_ANALOG_RCO100M_RTC100M_CTRL          ( CTL_BASE_ANLG_PHY_G10 + 0x0000 )
#define REG_ANLG_PHY_G10_ANALOG_RCO100M_WRAP_RCO_CTRL         ( CTL_BASE_ANLG_PHY_G10 + 0x0004 )
#define REG_ANLG_PHY_G10_ANALOG_EFUSE4K_EFUSE_PIN_PW_CTL      ( CTL_BASE_ANLG_PHY_G10 + 0x0008 )

/* REG_ANLG_PHY_G10_ANALOG_RCO100M_RTC100M_CTRL */

#define BIT_ANLG_PHY_G10_ANALOG_RCO100M_RCO100M_RESERVED(x)         (((x) & 0xFF) << 6)
#define BIT_ANLG_PHY_G10_ANALOG_RCO100M_RCO100M_LDO_EN              BIT(5)
#define BIT_ANLG_PHY_G10_ANALOG_RCO100M_RCO100M_LDO_BYPASS          BIT(4)
#define BIT_ANLG_PHY_G10_ANALOG_RCO100M_RCO100M_LDO_VOLTAGE_SEL(x)  (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G10_ANALOG_RCO100M_RCO100M_LDO_BIAS_SEL(x)     (((x) & 0x3))

/* REG_ANLG_PHY_G10_ANALOG_RCO100M_WRAP_RCO_CTRL */

#define BIT_ANLG_PHY_G10_ANALOG_RCO100M_DBG_SEL_RTC100M_LDO_BYPASS  BIT(2)
#define BIT_ANLG_PHY_G10_ANALOG_RCO100M_DBG_SEL_RTC100M_LDO_EN      BIT(1)
#define BIT_ANLG_PHY_G10_ANALOG_RCO100M_RCO100M_POWER_MODE_SEL      BIT(0)

/* REG_ANLG_PHY_G10_ANALOG_EFUSE4K_EFUSE_PIN_PW_CTL */

#define BIT_ANLG_PHY_G10_ANALOG_EFUSE4K_EFS_TRCS                    BIT(2)
#define BIT_ANLG_PHY_G10_ANALOG_EFUSE4K_EFS_AT1                     BIT(1)
#define BIT_ANLG_PHY_G10_ANALOG_EFUSE4K_EFS_AT0                     BIT(0)


#endif /* ANLG_PHY_G10_H */


