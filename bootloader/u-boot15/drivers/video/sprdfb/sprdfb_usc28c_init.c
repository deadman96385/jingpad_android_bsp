/*
 * Copyright (C) 2014 Spreadtrum Communications Inc.
 *
 * modules/DISPC/usc28c_dsi_init.c
 *
 * Author: Haibing.Yang <haibing.yang@spreadtrum.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>

#ifndef CTL_BASE_GPIO
#define CTL_BASE_GPIO 0x40280000
#endif

#define CTL_BASE_ENABLE_USC28C_DSI 0x403f0008

#define pr_info printf

#define CHIP_GPIO_BASE			CTL_BASE_GPIO
#define ARM_GPIO_BASE_CNT              (192)

#define SPI_USC28C_SCK_GPIO_PIN        (200)
#define SPI_USC28C_SEN_GPIO_PIN        (201)
#define SPI_USC28C_DAT_GPIO_PIN        (202)

#define SPI_USC28C_SCK_GPIO_MASK       (1<<(SPI_USC28C_SCK_GPIO_PIN-ARM_GPIO_BASE_CNT))
#define SPI_USC28C_SEN_GPIO_MASK       (1<<(SPI_USC28C_SEN_GPIO_PIN-ARM_GPIO_BASE_CNT))
#define SPI_USC28C_DAT_GPIO_MASK       (1<<(SPI_USC28C_DAT_GPIO_PIN-ARM_GPIO_BASE_CNT))
#define SPI_CLK_DELAY					0
#define SPI_READ_REG					0x3F

#define GPIO_CHIP_USC28C_OFFSET			(CHIP_GPIO_BASE + 0x600)

#define DSI_SCAN_MODE_0					252
#define DSI_SCAN_MODE_1					394

struct gpio_ctrl_reg {
	volatile u32 data; /* bits data */
	volatile u32 msk; /* bits data mask */
	volatile u32 dir; /* bits data direction */
	volatile u32 is; /* bits interrupt sense */
	volatile u32 ibe; /* bits both edges interrupt */
	volatile u32 iev; /* bits interrupt event */
	volatile u32 ie; /* bits interrupt enable */
	volatile u32 ris; /* bits raw interrupt status */
	volatile u32 mis; /* bits masked interrupt status */
	volatile u32 inen; /* input enable */
};

static void gpio_set_dir(u8 port, u8 dir)
{
	volatile struct gpio_ctrl_reg *reg;

	reg = (volatile struct gpio_ctrl_reg *)(GPIO_CHIP_USC28C_OFFSET);
	if (dir) {
		reg->dir |= 1 << ((u32) (port - ARM_GPIO_BASE_CNT)); // OUTPUT MODE.
	} else {
		reg->dir &= ~((u32)(1 << ((u32) (port - ARM_GPIO_BASE_CNT)))); // INPUT MODE.
	}
	reg->msk |= (1 << (u32)(port - ARM_GPIO_BASE_CNT)); // OUTPUT MODE.
}

static void gpio_out(u8 port, u8 data)
{
	volatile struct gpio_ctrl_reg *reg;

	reg = (volatile struct gpio_ctrl_reg *)(GPIO_CHIP_USC28C_OFFSET);
	if (data) {
		reg->data |= (1 << (u32)(port - ARM_GPIO_BASE_CNT)); // set 1.
	} else {
		reg->data &= ~(1 << (u32)(port - ARM_GPIO_BASE_CNT)); // set 0.
	}
}

static void gpio_out_combo(u32 sclk, u32 sen, u32 dat)
{
	volatile struct gpio_ctrl_reg *reg;
	u32 read_dat;
	u32 reg_set = 0;

	reg = (volatile struct gpio_ctrl_reg *)(GPIO_CHIP_USC28C_OFFSET);

	if (sclk) {
		reg_set |= SPI_USC28C_SCK_GPIO_MASK;
	}
	if (sen) {
		reg_set |= SPI_USC28C_SEN_GPIO_MASK;
	}
	if (dat) {
		reg_set |= SPI_USC28C_DAT_GPIO_MASK;
	}
	read_dat = reg->data;
	read_dat &= ~(SPI_USC28C_SCK_GPIO_MASK | SPI_USC28C_SEN_GPIO_MASK
			| SPI_USC28C_DAT_GPIO_MASK);
	read_dat |= reg_set;
	reg->data = read_dat;
}

static u8 gpio_in(u8 port)
{
	volatile struct gpio_ctrl_reg *reg;
	u32 data;

	reg = (volatile struct gpio_ctrl_reg *)(GPIO_CHIP_USC28C_OFFSET);

	data = reg->data;
	if (data & (1 << (port - ARM_GPIO_BASE_CNT))) {
		return 1;
	}
	return 0;
}

static void __usc28c_spi_init(void)
{
	gpio_set_dir(SPI_USC28C_SCK_GPIO_PIN, 1);
	gpio_set_dir(SPI_USC28C_SEN_GPIO_PIN, 1);
	gpio_set_dir(SPI_USC28C_DAT_GPIO_PIN, 1);

	gpio_out(SPI_USC28C_SCK_GPIO_PIN, 0);
	gpio_out(SPI_USC28C_SEN_GPIO_PIN, 1);
	gpio_out(SPI_USC28C_DAT_GPIO_PIN, 0);
}

static void __spi_reg_w(u16 reg, u16 val)
{
	s8 i;
	u8 temp = 0;

	gpio_set_dir(SPI_USC28C_SCK_GPIO_PIN, 1);
	gpio_set_dir(SPI_USC28C_SEN_GPIO_PIN, 1);
	gpio_set_dir(SPI_USC28C_DAT_GPIO_PIN, 1);

	gpio_out_combo(0, 1, 0);
	udelay(SPI_CLK_DELAY);
	if (val & (1 << 15)) {
		gpio_out_combo(0, 0, 1);
	} else {
		gpio_out_combo(0, 0, 0);
	}
	udelay(SPI_CLK_DELAY);
	gpio_out(SPI_USC28C_SCK_GPIO_PIN, 1);
	udelay(SPI_CLK_DELAY);

	for (i = 14; i >= 0; i--) {
		gpio_out_combo(0, 0, val & (1 << i));
		udelay(SPI_CLK_DELAY);
		gpio_out(SPI_USC28C_SCK_GPIO_PIN, 1);
		udelay(SPI_CLK_DELAY);
	}

	for (i = 1; i >= 0; i--) {
		gpio_out_combo(0, 0, temp & (1 << i));
		udelay(SPI_CLK_DELAY);
		gpio_out(SPI_USC28C_SCK_GPIO_PIN, 1);
		udelay(SPI_CLK_DELAY);
	}

	for (i = 15; i >= 0; i--) {
		gpio_out_combo(0, 0, reg & (1 << i));
		udelay(SPI_CLK_DELAY);
		gpio_out(SPI_USC28C_SCK_GPIO_PIN, 1);
		udelay(SPI_CLK_DELAY);
	}
	udelay(SPI_CLK_DELAY);
	gpio_out_combo(0, 1, 1);
}

static u16 __spi_reg_r(u16 reg)
{
	s8 i;
	u16 recv = 0;

	__spi_reg_w(SPI_READ_REG, reg);
	gpio_set_dir(SPI_USC28C_DAT_GPIO_PIN, 0);

	gpio_out(SPI_USC28C_SCK_GPIO_PIN, 1);
	udelay(SPI_CLK_DELAY);
	gpio_out(SPI_USC28C_SCK_GPIO_PIN, 0);

	for (i = 15; i >= 0; i--) {
		udelay(SPI_CLK_DELAY);
		gpio_out(SPI_USC28C_SCK_GPIO_PIN, 1);
		recv <<= 1;
		udelay(SPI_CLK_DELAY);
		recv |= gpio_in(SPI_USC28C_DAT_GPIO_PIN);
		gpio_out(SPI_USC28C_SCK_GPIO_PIN, 0);
	}

	return recv;
}

void usc28c_dsi_init(void)
{
	u16 phy_regs;

	writel(0x2880, CTL_BASE_ENABLE_USC28C_DSI);

	__usc28c_spi_init();
	/* DSI */
	__spi_reg_w(0x00, 0x01);
	__spi_reg_w(0x10, 0x02);
/*
 * choose CSI
	__spi_reg_w(0x00, 0x07);
	__spi_reg_w(0x10, 0x03);
 * choose CSI
 */
	pr_info("%s: chip usc28c dsi mode is chosen\n", __func__);

	/* scan mode config: d252 and d394 bit[6] = 1 */
	__spi_reg_w(DSI_SCAN_MODE_0, __spi_reg_r(DSI_SCAN_MODE_0) | BIT(6));
	__spi_reg_w(DSI_SCAN_MODE_1, __spi_reg_r(DSI_SCAN_MODE_1) | BIT(6));

#ifdef CONFIG_IMPROVE_PHY_DRIVE_CAPAILITY
	for (phy_regs = 64; phy_regs <= 484; ++phy_regs)
		__spi_reg_w(phy_regs, __spi_reg_r(phy_regs) |
				BIT(15) | BIT(14) & ~(BIT(5) | BIT(4)));

	for (phy_regs = 493; phy_regs <= 497; ++phy_regs)
		__spi_reg_w(phy_regs, __spi_reg_r(phy_regs) |
				BIT(15) | BIT(14) & ~(BIT(5) | BIT(4)));
#endif

	pr_info("Reg0x%04x, value: 0x%04x and Reg0x%04x, value: 0x%04x\n",
			0x0, __spi_reg_r(0x0), 0x10, __spi_reg_r(0x10));
	pr_info("Reg0x%04x, value: 0x%04x and Reg0x%04x, value: 0x%04x\n",
			DSI_SCAN_MODE_0, __spi_reg_r(DSI_SCAN_MODE_0),
			DSI_SCAN_MODE_1, __spi_reg_r(DSI_SCAN_MODE_1));
}

void __usc28c_usb_init(void)
{
	u16 reg_addr;

	for (reg_addr = 64; reg_addr <= 484; reg_addr++) {
		__spi_reg_w(reg_addr, (__spi_reg_r(reg_addr) & (~BIT(5))) | BIT(4));
	}

	for (reg_addr = 493; reg_addr <= 497; reg_addr++) {
		__spi_reg_w(reg_addr, (__spi_reg_r(reg_addr) & (~BIT(5))) | BIT(4));
	}
}

