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

void usb_phy_init(void)
{
	/* enable usb module*/
	CHIP_REG_OR(REG_AON_APB_APB_EB1, BIT_USB_EB | BIT_AON_APB_ANA_EB);

	/*PHY bus valid*/
	CHIP_REG_OR(REG_AON_APB_OTG_PHY_TEST,
				BIT_AON_APB_OTG_VBUS_VALID_PHYREG);
	CHIP_REG_OR(REG_ANLG_PHY_G2_ANALOG_USB20_USB20_UTMI_CTL1,
				BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_VBUSVLDEXT);

	/*PHY width: 16 bit*/
	CHIP_REG_OR(REG_AON_APB_OTG_PHY_CTRL,
				BIT_AON_APB_UTMI_WIDTH_SEL);
	CHIP_REG_OR(REG_ANLG_PHY_G2_ANALOG_USB20_USB20_UTMI_CTL1,
				BIT_ANLG_PHY_G2_ANALOG_USB20_USB20_DATABUS16_8);

	/*Soft reset phy*/
	CHIP_REG_OR(REG_AON_APB_APB_RST1,
			BIT_AON_APB_OTG_PHY_SOFT_RST |
			BIT_AON_APB_OTG_UTMI_SOFT_RST);
	Musb_mdelay(5);
	CHIP_REG_AND(REG_AON_APB_APB_RST1,
			~(BIT_AON_APB_OTG_PHY_SOFT_RST |
			BIT_AON_APB_OTG_UTMI_SOFT_RST));
}

