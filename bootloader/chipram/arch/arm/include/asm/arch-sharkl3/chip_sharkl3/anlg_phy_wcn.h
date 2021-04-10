/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2017-12-27 15:24:15
 *
 */


#ifndef ANLG_PHY_WCN_H
#define ANLG_PHY_WCN_H

#define CTL_BASE_ANLG_PHY_WCN 0x40366000


#define REG_ANLG_PHY_WCN_WCN_ADC_CLK_SEL      ( CTL_BASE_ANLG_PHY_WCN + 0x0000 )
#define REG_ANLG_PHY_WCN_WCN_SYS_CFG1         ( CTL_BASE_ANLG_PHY_WCN + 0x0004 )
#define REG_ANLG_PHY_WCN_WCN_SYS_CFG2         ( CTL_BASE_ANLG_PHY_WCN + 0x0008 )

/* REG_ANLG_PHY_WCN_WCN_ADC_CLK_SEL */

#define BIT_ANLG_PHY_WCN_WCN_OSCADC_CLK_SEL           BIT(1)
#define BIT_ANLG_PHY_WCN_WCN_TSEADC_CLK_SEL           BIT(0)

/* REG_ANLG_PHY_WCN_WCN_SYS_CFG1 */

#define BIT_ANLG_PHY_WCN_WCN_CM4_ADDR_REMAP(x)        (((x) & 0x3) << 24)
#define BIT_ANLG_PHY_WCN_WCN_GNSS_CM4_ADDR_OFFSET(x)  (((x) & 0xFFFFFF))

/* REG_ANLG_PHY_WCN_WCN_SYS_CFG2 */

#define BIT_ANLG_PHY_WCN_WCN_RD_XTAL_REQ_SEL(x)       (((x) & 0x3) << 8)
#define BIT_ANLG_PHY_WCN_WCN_BTWF_SYS_EN              BIT(7)
#define BIT_ANLG_PHY_WCN_WCN_GNSS_SYS_EN              BIT(6)
#define BIT_ANLG_PHY_WCN_WCN_BTWF_CM4_DBGRESTART      BIT(5)
#define BIT_ANLG_PHY_WCN_WCN_BTWF_CM4_EDBGREQ         BIT(4)
#define BIT_ANLG_PHY_WCN_WCN_OFFCHIP_XTRL_EN          BIT(3)
#define BIT_ANLG_PHY_WCN_WCN_XTAL_DIF_SEL_H           BIT(2)
#define BIT_ANLG_PHY_WCN_WCN_GNSS_CM4_DBGRESTART      BIT(1)
#define BIT_ANLG_PHY_WCN_WCN_GNSS_CM4_EDBGREQ         BIT(0)


#endif /* ANLG_PHY_WCN_H */

