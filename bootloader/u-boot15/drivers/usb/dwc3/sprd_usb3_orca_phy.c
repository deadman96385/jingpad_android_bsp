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
	val |= BIT_AON_APB_ANA_EB | BIT_AON_APB_CKG_EB | BIT_AON_APB_APCPU_CLK_EB;
	writel(val, REG_AON_APB_APB_EB1);

	/* perpose: to select IPA usb clk:24M */
	val = readl(REG_AP_CLK_CORE_CGM_USB1_REF_CFG);
	val |= BIT_AP_CLK_CORE_CGM_USB1_REF_CFG_CGM_USB1_REF_SEL;
	writel(val , REG_AP_CLK_CORE_CGM_USB1_REF_CFG);

	/* perpose: to select usb suspend clk:1M */
	val = readl(REG_AON_CLK_CORE_CGM_USB3B_SUSPEND_CFG);
	val |= BIT_AON_CLK_CORE_CGM_USB3B_SUSPEND_CFG_CGM_USB3B_SUSPEND_SEL;
	writel(val , REG_AON_CLK_CORE_CGM_USB3B_SUSPEND_CFG);

	/* perpose: to soft-reset USB control */
	val = readl(REG_AP_IPA_AHB_AHB_RST);
	val |= BIT_AP_IPA_AHB_USB1_SOFT_RST;
	writel(val , REG_AP_IPA_AHB_AHB_RST);
	udelay(10 * 1000);
	val = readl(REG_AP_IPA_AHB_AHB_RST);
	val &= ~BIT_AP_IPA_AHB_USB1_SOFT_RST;
	writel(val , REG_AP_IPA_AHB_AHB_RST);

	/* perpose: to set IPA AHB USB enable interface: Little Endian */
	val = readl(REG_AP_IPA_AHB_AHB_EB);
	val |= BIT_AP_IPA_AHB_USB1_EB | BIT_AP_IPA_AHB_USB1_SUSPEND_EB | BIT_AP_IPA_AHB_USB1_REF_EB;
	writel(val , REG_AP_IPA_AHB_AHB_EB);

	/* perpose: enable usb2 phy 16bit and vbus valid_ext */
	val = readl(REG_ANLG_PHY_G4_ANALOG_USB20_1_USB20_UTMI_CTL1);
	val |= BIT_ANLG_PHY_G4_ANALOG_USB20_1_USB20_DATABUS16_8 | BIT_ANLG_PHY_G4_ANALOG_USB20_1_USB20_VBUSVLDEXT;
	writel(val , REG_ANLG_PHY_G4_ANALOG_USB20_1_USB20_UTMI_CTL1);

	/* perpose: vbus valid */
	val = readl(REG_AON_APB_OTG_PHY_TEST);
	val |= BIT_AON_APB_OTG_VBUS_VALID_PHYREG;
	writel(val , REG_AON_APB_OTG_PHY_TEST);

	/* perpose: set utmisrp_bvalid_reg, otg_vbus_valid_phyreg and pipe3_powerpresent*/
	val = readl(REG_AP_IPA_AHB_USB1_CTRL);
	val |= BIT_AP_IPA_AHB_UTMISRP_BVALID_REG1 | BIT_AP_IPA_AHB_OTG_VBUS_VALID_PHYREG1;
	val |= BIT_AP_IPA_AHB_PIPE3_POWERPRESENT1;
	writel(val , REG_AP_IPA_AHB_USB1_CTRL);
	/* perpose: otg_vbus_valid_phyreg_sel */
	val &= ~BIT_AP_IPA_AHB_OTG_VBUS_VALID_PHYREG_SEL1;
	writel(val , REG_AP_IPA_AHB_USB1_CTRL);
}

static void usb_disable()
{
	u32 val;

	debugf("%s, enter !\n", __func__);

	/* Purpose: To set IPA AHB USB disable interface: Little Endian */
	val = readl(REG_AP_IPA_AHB_AHB_EB);
	writel(val & ~(BIT_AP_IPA_AHB_USB1_EB | BIT_AP_IPA_AHB_USB1_SUSPEND_EB
		 | BIT_AP_IPA_AHB_USB1_REF_EB), REG_AP_IPA_AHB_AHB_EB);

}
void usb_phy_enable(u32 is_on)
{
	if (is_on) {
		usb_enable();
	} else {
		usb_disable();
	}
}
