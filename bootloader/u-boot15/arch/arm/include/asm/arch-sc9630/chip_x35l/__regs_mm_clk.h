/*
 * Copyright (C) 2014-2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */

#ifndef __REGS_MM_CLK_H__
#define __REGS_MM_CLK_H__

#define REGS_MM_CLK

/* registers definitions for controller REGS_MM_CLK */
#define REG_MM_CLK_MM_AHB_CFG           SCI_ADDR(REGS_MM_CLK_BASE, 0x0020)
#define REG_MM_CLK_SENSOR_CFG           SCI_ADDR(REGS_MM_CLK_BASE, 0x0024)
#define REG_MM_CLK_CCIR_CFG             SCI_ADDR(REGS_MM_CLK_BASE, 0x0028)
#define REG_MM_CLK_DCAM_CFG             SCI_ADDR(REGS_MM_CLK_BASE, 0x002c)
#define REG_MM_CLK_VSP_CFG              SCI_ADDR(REGS_MM_CLK_BASE, 0x0030)
#define REG_MM_CLK_ISP_CFG              SCI_ADDR(REGS_MM_CLK_BASE, 0x0034)
#define REG_MM_CLK_JPG_CFG              SCI_ADDR(REGS_MM_CLK_BASE, 0x0038)
#define REG_MM_CLK_MIPI_CSI_CFG         SCI_ADDR(REGS_MM_CLK_BASE, 0x003c)
#define REG_MM_CLK_CPHY_CFG_CFG         SCI_ADDR(REGS_MM_CLK_BASE, 0x0040)
#define REG_MM_CLK_ORP_TCK_CFG          SCI_ADDR(REGS_MM_CLK_BASE, 0x0044)

/* vars definitions for controller REGS_MM_CLK */

#endif //__REGS_MM_CLK_H__
