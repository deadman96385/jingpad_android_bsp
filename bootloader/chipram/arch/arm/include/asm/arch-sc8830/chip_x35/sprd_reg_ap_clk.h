/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 *************************************************
 * Automatically generated C header: do not edit *
 *************************************************
 */

#ifndef __REGS_AP_CLK_H__
#define __REGS_AP_CLK_H__

#define REGS_AP_CLK

/* registers definitions for controller REGS_AP_CLK */
#define REG_AP_CLK_AP_AHB_CFG           SCI_ADDR(REGS_AP_CLK_BASE, 0x0020)
#define REG_AP_CLK_AP_APB_CFG           SCI_ADDR(REGS_AP_CLK_BASE, 0x0024)
#define REG_AP_CLK_GSP_CFG              SCI_ADDR(REGS_AP_CLK_BASE, 0x0028)
#define REG_AP_CLK_DISPC0_CFG           SCI_ADDR(REGS_AP_CLK_BASE, 0x002c)
#define REG_AP_CLK_DISPC0_DBI_CFG       SCI_ADDR(REGS_AP_CLK_BASE, 0x0030)
#define REG_AP_CLK_DISPC0_DPI_CFG       SCI_ADDR(REGS_AP_CLK_BASE, 0x0034)
#define REG_AP_CLK_DISPC1_CFG           SCI_ADDR(REGS_AP_CLK_BASE, 0x0038)
#define REG_AP_CLK_DISPC1_DBI_CFG       SCI_ADDR(REGS_AP_CLK_BASE, 0x003c)
#define REG_AP_CLK_DISPC1_DPI_CFG       SCI_ADDR(REGS_AP_CLK_BASE, 0x0040)
#define REG_AP_CLK_NFC_CFG              SCI_ADDR(REGS_AP_CLK_BASE, 0x0044)
#define REG_AP_CLK_SDIO0_CFG            SCI_ADDR(REGS_AP_CLK_BASE, 0x0048)
#define REG_AP_CLK_SDIO1_CFG            SCI_ADDR(REGS_AP_CLK_BASE, 0x004c)
#define REG_AP_CLK_SDIO2_CFG            SCI_ADDR(REGS_AP_CLK_BASE, 0x0050)
#define REG_AP_CLK_EMMC_CFG             SCI_ADDR(REGS_AP_CLK_BASE, 0x0054)
#define REG_AP_CLK_GPS_CFG              SCI_ADDR(REGS_AP_CLK_BASE, 0x0058)
#define REG_AP_CLK_GPS_TCXO_CFG         SCI_ADDR(REGS_AP_CLK_BASE, 0x005c)
#define REG_AP_CLK_USB_REF_CFG          SCI_ADDR(REGS_AP_CLK_BASE, 0x0060)
#define REG_AP_CLK_UART0_CFG            SCI_ADDR(REGS_AP_CLK_BASE, 0x0064)
#define REG_AP_CLK_UART1_CFG            SCI_ADDR(REGS_AP_CLK_BASE, 0x0068)
#define REG_AP_CLK_UART2_CFG            SCI_ADDR(REGS_AP_CLK_BASE, 0x006c)
#define REG_AP_CLK_UART3_CFG            SCI_ADDR(REGS_AP_CLK_BASE, 0x0070)
#define REG_AP_CLK_UART4_CFG            SCI_ADDR(REGS_AP_CLK_BASE, 0x0074)
#define REG_AP_CLK_I2C0_CFG             SCI_ADDR(REGS_AP_CLK_BASE, 0x0078)
#define REG_AP_CLK_I2C1_CFG             SCI_ADDR(REGS_AP_CLK_BASE, 0x007c)
#define REG_AP_CLK_I2C2_CFG             SCI_ADDR(REGS_AP_CLK_BASE, 0x0080)
#define REG_AP_CLK_I2C3_CFG             SCI_ADDR(REGS_AP_CLK_BASE, 0x0084)
#define REG_AP_CLK_I2C4_CFG             SCI_ADDR(REGS_AP_CLK_BASE, 0x0088)
#define REG_AP_CLK_SPI0_CFG             SCI_ADDR(REGS_AP_CLK_BASE, 0x008c)
#define REG_AP_CLK_SPI1_CFG             SCI_ADDR(REGS_AP_CLK_BASE, 0x0090)
#define REG_AP_CLK_SPI2_CFG             SCI_ADDR(REGS_AP_CLK_BASE, 0x0094)
#define REG_AP_CLK_IIS0_CFG             SCI_ADDR(REGS_AP_CLK_BASE, 0x0098)
#define REG_AP_CLK_IIS1_CFG             SCI_ADDR(REGS_AP_CLK_BASE, 0x009c)
#define REG_AP_CLK_IIS2_CFG             SCI_ADDR(REGS_AP_CLK_BASE, 0x00a0)
#define REG_AP_CLK_IIS3_CFG             SCI_ADDR(REGS_AP_CLK_BASE, 0x00a4)

/* vars definitions for controller REGS_AP_CLK */

/* vars definitions for REG_AP_CLK_AP_AHB_CFG */
#define AP_AHB_CLK_SEL_SHIFT		(0)
#define AP_AHB_CLK_SEL_MASK		(0x3 << AP_AHB_CLK_SEL_SHIFT)

#define AP_APB_CLK_SEL_SHIFT            (0)
#define AP_APB_CLK_SEL_MASK             (0x3 << AP_AHB_CLK_SEL_SHIFT)

#endif //__REGS_AP_CLK_H__
