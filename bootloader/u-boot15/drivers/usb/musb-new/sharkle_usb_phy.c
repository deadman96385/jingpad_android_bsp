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

extern void Musb_mdelay(uint32_t msecs);

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

	__raw_bits_and(~(BIT_29|BIT_30), REG_AP_AHB_OTG_PHY_CTRL);//SPRD USB PHY width: 8 bit

	__raw_bits_or(BIT_20, REG_AP_AHB_OTG_CTRL1);//utmi_rst

	__raw_bits_or(BIT_OTG_SOFT_RST|BIT_OTG_UTMI_SOFT_RST|BIT_OTG_PHY_SOFT_RST, REG_AP_AHB_AHB_RST);
	Musb_mdelay(5);
	__raw_bits_and(~(BIT_OTG_SOFT_RST|BIT_OTG_UTMI_SOFT_RST|BIT_OTG_PHY_SOFT_RST),REG_AP_AHB_AHB_RST);
}

