/******************************************************************************
 ** File Name:      sprd_musb2_driver.c                                        *
 ** Author:         chunhou.wang                                              *
 ** DATE:           07/11/2016                                                *
 ** Copyright:      2010 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:                                                              *
 ******************************************************************************/
/**---------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **---------------------------------------------------------------------------*/



#include <common.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include <sprd_regulator.h>
#include <usb/usb200_fdl.h>
#include <packet.h>
#include <dl_crc.h>

static void __raw_bits_and(unsigned int v, unsigned int a)
{
	__raw_writel((__raw_readl(a) & v), a);
}

static void __raw_bits_or(unsigned int v, unsigned int a)
{
	__raw_writel((__raw_readl(a) | v), a);
}

void usb_phy_init(void)
{
	__raw_bits_or(BIT_24|BIT_22, REG_AP_AHB_OTG_PHY_TEST);

#ifdef CONFIG_FPGA
	__raw_bits_or((BIT_29|BIT_30), REG_AP_AHB_OTG_PHY_CTRL);//Tiger PHY width: 16 bit
#else
	__raw_bits_and(~(BIT_29|BIT_30), REG_AP_AHB_OTG_PHY_CTRL);//SPRD USB PHY width: 8 bit
#endif

	__raw_bits_or(BIT_20, REG_AP_AHB_OTG_CTRL1);//utmi_rst

	__raw_bits_and(~BIT_AP_AHB_USB20_TUNEHSAMP(3),REG_AP_AHB_OTG_CTRL0);
	__raw_bits_or(BIT_AP_AHB_USB20_TUNEHSAMP(2),REG_AP_AHB_OTG_CTRL0);
	__raw_bits_and(~BIT_AP_AHB_USB20_TUNEOTG(7),REG_AP_AHB_OTG_CTRL0);

	__raw_bits_and(~BIT_AP_AHB_USB20_TFREGRES(0x3F),REG_AP_AHB_OTG_CTRL1);
	__raw_bits_or(BIT_AP_AHB_USB20_TFREGRES(7),REG_AP_AHB_OTG_CTRL1);
	__raw_bits_or(BIT_AP_AHB_USB20_TFHSRES(0x1F),REG_AP_AHB_OTG_CTRL1);

	__raw_bits_or(BIT_OTG_SOFT_RST|BIT_OTG_UTMI_SOFT_RST|BIT_OTG_PHY_SOFT_RST, REG_AP_AHB_AHB_RST);
	Musb_mdelay(5);
	__raw_bits_and(~(BIT_OTG_SOFT_RST|BIT_OTG_UTMI_SOFT_RST|BIT_OTG_PHY_SOFT_RST),REG_AP_AHB_AHB_RST);
}

