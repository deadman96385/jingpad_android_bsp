/**
 * sprd_usb3_hw.c - Spreadtrum USB3 HW glue file
 *
 * Copyright (C) 2015 SPREADTRUM  - http://www.spreadtrum.com
 *
 * Authors: Miao.Zhu <miao.zhu@spreadtrum.com>,
 *
 * SPDX-License-Identifier:     GPL-2.0
 */

#include <common.h>
#include <malloc.h>
#include <asm/arch/sprd_reg.h>
#include <asm/io.h>
#include <sprd_regulator.h>
#include "linux-compat.h"

static void usb_enable()
{
	u32 val;

	debugf("%s, enter !\n", __func__);
	/*enable analog*/
	val = readl(REG_AON_APB_APB_EB1);
	writel(val | BIT_AON_APB_ANA_EB, REG_AON_APB_APB_EB1);

	/* USB2/USB3 PHY power on */
	val = readl(REG_PMU_APB_ANALOG_PHY_PD_CFG);
	val &= ~(BIT_PMU_APB_USB3_PHY_PD_REG | BIT_PMU_APB_USB2_PHY_PD_REG);
	writel(val, REG_PMU_APB_ANALOG_PHY_PD_CFG);

	/*disable IPA_SYS shutdown*/
	val = readl(REG_PMU_APB_PD_IPA_SYS_CFG);
	writel(val & ~BIT_PMU_APB_PD_IPA_SYS_FORCE_SHUTDOWN, REG_PMU_APB_PD_IPA_SYS_CFG);

	/* disable low power */
	val = readl(REG_IPA_AHB_M7_LPC);
	writel(val & ~BIT_IPA_AHB_MAIN_M7_LP_EB, REG_IPA_AHB_M7_LPC);

	udelay(10 * 1000);

	/* select the IPA_SYS USB controller */
	val = readl(REG_AON_APB_AON_SOC_USB_CTRL);
	writel(val | BIT_AON_APB_USB20_CTRL_MUX_REG, REG_AON_APB_AON_SOC_USB_CTRL);

	/* purpose: set bvalid vbus_valid and clear vbus_valid_sel */
	val = readl(REG_IPA_AHB_USB_CTL0);
	val |= BIT_IPA_AHB_UTMISRP_BVALID_REG | BIT_IPA_AHB_OTG_VBUS_VALID_PHYREG;
	writel(val , REG_IPA_AHB_USB_CTL0);

	val = readl(REG_IPA_AHB_USB_CTL0);
	writel(val & ~BIT_IPA_AHB_OTG_VBUS_VALID_PHYREG_SEL, REG_IPA_AHB_USB_CTL0);

	/* diable power management event */
	val = readl(REG_IPA_AHB_USB_CTL0);
	writel(val & ~BIT_IPA_AHB_PME_EN, REG_IPA_AHB_USB_CTL0);

	/* reset power present to default value */
	val = readl(REG_AON_APB_OTG_PHY_TEST);
	writel(val | BIT_AON_APB_USB30_POWER_PRESENT, REG_AON_APB_OTG_PHY_TEST);

	/* Purpose: To set IPA AHB USB enable interface: Little Endian */
	val = readl(REG_IPA_AHB_IPA_EB);
	val |= BIT_IPA_AHB_USB_EB | BIT_IPA_AHB_USB_SUSPEND_EB | BIT_IPA_AHB_USB_REF_EB;
	writel(val , REG_IPA_AHB_IPA_EB);

	/* Purpose: To soft-reset USB control */
	val = readl(REG_IPA_AHB_IPA_RST);
	writel(val | BIT_IPA_AHB_USB_SOFT_RST, REG_IPA_AHB_IPA_RST);

	udelay(10 * 1000);
	val = readl(REG_IPA_AHB_IPA_RST);
	writel(val & ~BIT_IPA_AHB_USB_SOFT_RST, REG_IPA_AHB_IPA_RST);

	/* enable USB2 PHY 16bit */
	val = readl(REG_ANLG_PHY_G3_ANALOG_USB20_USB20_UTMI_CTL1);
	writel(val | BIT_ANLG_PHY_G3_ANALOG_USB20_USB20_DATABUS16_8,
				REG_ANLG_PHY_G3_ANALOG_USB20_USB20_UTMI_CTL1);

	/* vbus valid */
	val = readl(REG_AON_APB_OTG_PHY_TEST);
	writel(val | BIT_AON_APB_OTG_VBUS_VALID_PHYREG,
				REG_AON_APB_OTG_PHY_TEST);
	val = readl(REG_ANLG_PHY_G3_ANALOG_USB20_USB20_UTMI_CTL1);
	writel(val | BIT_ANLG_PHY_G3_ANALOG_USB20_USB20_VBUSVLDEXT,
				REG_ANLG_PHY_G3_ANALOG_USB20_USB20_UTMI_CTL1);

	/* Purpose: To soft-reset USB2 PHY */
	val = readl(REG_AON_APB_APB_RST1);
	val |= (BIT_AON_APB_OTG_UTMI_SOFT_RST | BIT_AON_APB_OTG_PHY_SOFT_RST);
	writel(val , REG_AON_APB_APB_RST1);
	udelay(10 * 1000);
	val = readl(REG_AON_APB_APB_RST1);
	val &= ~(BIT_AON_APB_OTG_UTMI_SOFT_RST | BIT_AON_APB_OTG_PHY_SOFT_RST);
	writel(val , REG_AON_APB_APB_RST1);

	/* please wait for a moment */
	udelay(30 * 1000);
}

static void usb_disable()
{
	u32 val;

	debugf("%s, enter !\n", __func__);

	/* Purpose: To set IPA AHB USB disable interface: Little Endian */
	val = readl(REG_IPA_AHB_IPA_EB);
	writel(val & ~(BIT_IPA_AHB_USB_EB | BIT_IPA_AHB_USB_SUSPEND_EB
		 | BIT_IPA_AHB_USB_REF_EB), REG_IPA_AHB_IPA_EB);

	/* USB2/USB3 PHY power off */
	val = readl(REG_PMU_APB_ANALOG_PHY_PD_CFG);
	val |= (BIT_PMU_APB_USB3_PHY_PD_REG | BIT_PMU_APB_USB2_PHY_PD_REG);
	writel(val, REG_PMU_APB_ANALOG_PHY_PD_CFG);

	/*disable analog*/
	val = readl(REG_USB_EB);
	writel(val & ~BIT_USB_EB, REG_USB_EB);

}
void usb_phy_enable(u32 is_on)
{
	if (is_on) {
		usb_enable();
	} else {
		usb_disable();
	}
}

