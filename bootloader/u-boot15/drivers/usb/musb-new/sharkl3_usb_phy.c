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
	CHIP_REG_OR(REG_AP_AHB_AHB_EB, BIT_USB_EB);
	CHIP_REG_OR(REG_AON_APB_APB_EB2,
				BIT_AON_APB_ANLG_APB_EB | BIT_AON_APB_ANLG_EB);


	CHIP_REG_OR(REG_ANLG_PHY_G4_ANALOG_USB20_IDDG,
				BIT_ANLG_PHY_G4_ANALOG_USB20_UTMIOTG_IDDG);
	/*PHY bus valid*/
	CHIP_REG_OR(REG_AP_AHB_OTG_PHY_TEST,
				BIT_AP_AHB_OTG_VBUS_VALID_PHYREG);
	CHIP_REG_OR(REG_ANLG_PHY_G4_ANALOG_USB20_USB20_UTMI_CTL1,
				BIT_ANLG_PHY_G4_ANALOG_USB20_USB20_DATABUS16_8 |
				BIT_ANLG_PHY_G4_ANALOG_USB20_USB20_VBUSVLDEXT);

	/*PHY width: 16 bit*/
	CHIP_REG_OR(REG_AP_AHB_OTG_PHY_CTRL,
				BIT_AP_AHB_UTMI_WIDTH_SEL);

	/*Soft reset phy*/
	CHIP_REG_OR(REG_AP_AHB_AHB_RST,
				BIT_OTG_SOFT_RST | BIT_OTG_UTMI_SOFT_RST);
	CHIP_REG_OR(REG_AON_APB_APB_RST2,  BIT_OTG_PHY_SOFT_RST);
	Musb_mdelay(5);
	CHIP_REG_AND(REG_AP_AHB_AHB_RST,
				~(BIT_OTG_SOFT_RST | BIT_OTG_UTMI_SOFT_RST));
	CHIP_REG_AND(REG_AON_APB_APB_RST2,
				~BIT_OTG_PHY_SOFT_RST);
}

