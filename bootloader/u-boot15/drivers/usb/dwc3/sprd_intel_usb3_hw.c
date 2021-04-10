/**
 * sprd_intel_usb3_hw.c - Spreadtrum USB3 HW glue file
 *
 * Copyright (C) 2016 SPREADTRUM  - http://www.spreadtrum.com
 *
 * Authors: Cheng.Zeng <cheng.zeng@spreadtrum.com>,
 *
 * SPDX-License-Identifier:     GPL-2.0
 */

#include <common.h>
#include <malloc.h>

#ifdef CONFIG_SOC_IWHALE2
#include <asm/arch-iwhale/sprd_reg.h>
#else
#include <asm/arch/sprd_reg.h>
#endif

#include <asm/io.h>
#include <sprd_regulator.h>
#include "linux-compat.h"
#include "core.h"

//#define TMSC_28NM_HPM		0x5533286e /* USB3.0_PHY_TSMC_28MN */
//#define TMSC_16NM_FFPLL	0x5533166e /* USB3.0_PHY_TSMC_16MN */

extern int regulator_enable(const char con_id[]);
extern int regulator_disable(const char con_id[]);

#define LDO_USB3 "vddusb33"

#define REG_PHY_SIDECLK (0xE41F00AC)
#define BIT_SIDECLK_GLITCH_FIX BIT(23)

static struct dwc3_device dwc3_dev = {
	.base = SPRD_USB_BASE,
	.maximum_speed = USB_SPEED_HIGH,
	.dis_u3_susphy_quirk = 1,
	.dis_u2_susphy_quirk = 1,
};

static void usb_clk_enable(u32 is_on)
{
	u32 val;

	val = readl(REG_AP_AHB_AHB_EB);
	if (is_on)
		writel(val | (BIT_AP_AHB_USB3_EB | BIT_AP_AHB_USB3_SUSPEND_EB
			 | BIT_AP_AHB_USB3_REF_EB), REG_AP_AHB_AHB_EB);
	else
		writel(val & ~(BIT_AP_AHB_USB3_EB | BIT_AP_AHB_USB3_SUSPEND_EB
			 | BIT_AP_AHB_USB3_REF_EB), REG_AP_AHB_AHB_EB);
}

#ifdef CONFIG_FPGA
static void usb_phy_enable(u32 is_on)
{
}
#else
static void usb_phy_enable(u32 is_on)
{
	u32 val;

	if (is_on) {
		/* regulator enable vddusb33 and phy ldo */
		regulator_enable(LDO_USB3);
		udelay(5 * 1000);

		/* Core Soft Reset, PHY Reset */
		val = readl(REG_AP_AHB_AHB_RST);
		writel(val | BIT_AP_AHB_USB3_SOFT_RST, REG_AP_AHB_AHB_RST);
		udelay(5 * 1000);
		writel(val & ~BIT_AP_AHB_USB3_SOFT_RST, REG_AP_AHB_AHB_RST);

		/* Enable PowerPresent */
		val = readl(REG_ANLG_PHY_G4_ANALOG_USB3_WRAP_GLUE_CTRL);
		val |= BIT_ANLG_PHY_G4_ANALOG_USB3_USB3_POWER_PRESENT;
		writel(val, REG_ANLG_PHY_G4_ANALOG_USB3_WRAP_GLUE_CTRL);

		/* Set Sideclk Register */
		val = readl(REG_PHY_SIDECLK);
		val |= BIT_SIDECLK_GLITCH_FIX;
		writel(val, REG_PHY_SIDECLK);
	} else {
		regulator_disable(LDO_USB3);

		/* Disable PowerPresent */
		val = readl(REG_ANLG_PHY_G4_ANALOG_USB3_WRAP_GLUE_CTRL);
		writel(val & ~(BIT_ANLG_PHY_G4_ANALOG_USB3_USB3_POWER_PRESENT),
			REG_ANLG_PHY_G4_ANALOG_USB3_WRAP_GLUE_CTRL);
	}
}
#endif

