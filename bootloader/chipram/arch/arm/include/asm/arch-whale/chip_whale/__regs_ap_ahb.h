/* the head file modifier:     g   2014-12-04 11:16:02*/

/*  
* Copyright (C) 2013 Spreadtrum Communications Inc.  
*
* This program is free software; you can redistribute it and/or  
* modify it under the terms of the GNU General Public License 
* as published by the Free Software Foundation; either version 2 
* of the License, or (at your option) any later version.  
* 
* This program is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty of 
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  
* GNU General Public License for more details.  
* 
*************************************************  
* Automatically generated C header: do not edit *  
*************************************************  
*/  
#ifndef __H_REGS_AP_AHB_HEADFILE_H__
#define __H_REGS_AP_AHB_HEADFILE_H__ __FILE__

#define  REGS_AP_AHB

/* registers definitions for AP_AHB */
#define REG_AP_AHB_AHB_EB				SCI_ADDR(REGS_AP_AHB_BASE, 0x0000)/*AHB_EB*/
#define REG_AP_AHB_AHB_RST				SCI_ADDR(REGS_AP_AHB_BASE, 0x0004)/*AHB_RST*/
#define REG_AP_AHB_AP_SYS_FORCE_SLEEP_CFG		SCI_ADDR(REGS_AP_AHB_BASE, 0x0008)/*AP_SYS_FORCE_SLEEP_CFG*/
#define REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG		SCI_ADDR(REGS_AP_AHB_BASE, 0x000C)/*AP_SYS_AUTO_SLEEP_CFG*/
#define REG_AP_AHB_HOLDING_PEN				SCI_ADDR(REGS_AP_AHB_BASE, 0x0010)/*HOLDING_PEN*/
#define REG_AP_AHB_MISC_CKG_EN				SCI_ADDR(REGS_AP_AHB_BASE, 0x0014)/*MISC_CKG_EN*/
#define REG_AP_AHB_MISC_CFG				SCI_ADDR(REGS_AP_AHB_BASE, 0x0018)/*MISC_CFG*/
#define REG_AP_AHB_NANC_CLK_CFG				SCI_ADDR(REGS_AP_AHB_BASE, 0x3000)/*NANDC_CLK_CFG*/
#define REG_AP_AHB_AP_QOS_CFG				SCI_ADDR(REGS_AP_AHB_BASE, 0x3004)/*AP_QOS_CFG*/
#define REG_AP_AHB_OTG_PHY_TUNE				SCI_ADDR(REGS_AP_AHB_BASE, 0x3008)/*USB_PHY_TUNE*/
#define REG_AP_AHB_OTG_PHY_TEST				SCI_ADDR(REGS_AP_AHB_BASE, 0x300C)/*MISC_CKG_EN*/
#define REG_AP_AHB_OTG_PHY_CTRL				SCI_ADDR(REGS_AP_AHB_BASE, 0x3010)/*USB_PHY_CTRL*/
#define REG_AP_AHB_HSIC_PHY_TUNE			SCI_ADDR(REGS_AP_AHB_BASE, 0x3014)/*USB_PHY_TUNE*/
#define REG_AP_AHB_HSIC_PHY_TEST			SCI_ADDR(REGS_AP_AHB_BASE, 0x3018)/*MISC_CKG_EN*/
#define REG_AP_AHB_HSIC_PHY_CTRL			SCI_ADDR(REGS_AP_AHB_BASE, 0x301C)/*USB_PHY_CTRL*/
#define REG_AP_AHB_USB3_CTRL				SCI_ADDR(REGS_AP_AHB_BASE, 0x3020)/*USB3_CTRL*/
#define REG_AP_AHB_MISC_CTRL				SCI_ADDR(REGS_AP_AHB_BASE, 0x3024)/*MISC_CTRL*/
#define REG_AP_AHB_MISC_STATUS				SCI_ADDR(REGS_AP_AHB_BASE, 0x3028)/*MISC_STATUS*/
#define REG_AP_AHB_NOC_CTRL0				SCI_ADDR(REGS_AP_AHB_BASE, 0x302C)/*noc masters qos0*/
#define REG_AP_AHB_NOC_CTRL1				SCI_ADDR(REGS_AP_AHB_BASE, 0x3030)/*noc masters qos1*/
#define REG_AP_AHB_NOC_CTRL2				SCI_ADDR(REGS_AP_AHB_BASE, 0x3034)/*noc masters arcache*/
#define REG_AP_AHB_NOC_CTRL3				SCI_ADDR(REGS_AP_AHB_BASE, 0x3038)/*noc masters awcache*/
#define REG_AP_AHB_USB3_DBG0				SCI_ADDR(REGS_AP_AHB_BASE, 0x303C)/*USB3_DBG0*/
#define REG_AP_AHB_USB3_DBG1				SCI_ADDR(REGS_AP_AHB_BASE, 0x3040)/*USB3_DBG1*/
#define REG_AP_AHB_USB3_DBG2				SCI_ADDR(REGS_AP_AHB_BASE, 0x3044)/*USB3_DBG2*/



/* bits definitions for register REG_AHB_EB */
#define BIT_AP_AHB_CC63P_EB					(BIT(23))
#define BIT_AP_AHB_CC63S_EB					(BIT(22))
#define BIT_AP_AHB_ZIPMTX_EB				(BIT(21))
#define BIT_AP_AHB_ZIPDEC_EB					(BIT(20))
#define BIT_AP_AHB_ZIPENC_EB					(BIT(19))
#define BIT_AP_AHB_NANDC_ECC_EB					(BIT(18))
#define BIT_AP_AHB_NANDC_2X_EB					(BIT(17))
#define BIT_AP_AHB_NANDC_EB					(BIT(16))
#define BIT_AP_AHB_BUSMON_EB					(BIT(13))
#define BIT_AP_AHB_ROM_EB					(BIT(12))
#define BIT_AP_AHB_EMMC_EB					(BIT(10))
#define BIT_AP_AHB_SDIO2_EB					(BIT(9))
#define BIT_AP_AHB_SDIO1_EB					(BIT(8))
#define BIT_AP_AHB_SDIO0_EB					(BIT(7))
#define BIT_AP_AHB_NFC_EB					(BIT(6))
#define BIT_AP_AHB_DMA_EB					(BIT(5))
#define BIT_AP_AHB_USB3_REF_EB					(BIT(4))
#define BIT_AP_AHB_USB3_SUSPEND_EB				(BIT(3))
#define BIT_AP_AHB_USB3_EB					(BIT(2))
#define BIT_AP_AHB_OTG_EB					(BIT(1))
#define BIT_USB_EB                                      (BIT_OTG_EB)
#define BIT_AP_AHB_HSIC_EB					(BIT(0))

/* bits definitions for register REG_AHB_RST */
#define BIT_AP_AHB_CC63P_SOFT_RST				(BIT(31))
#define BIT_AP_AHB_CC63S_SOFT_RST				(BIT(30))
#define BIT_AP_AHB_HSIC_PHY_SOFT_RST				(BIT(29))
#define BIT_AP_AHB_HSIC_UTMI_SOFT_RST				(BIT(28))
#define BIT_AP_AHB_HSIC_SOFT_RST				(BIT(27))
#define BIT_AP_AHB_ZIP_MTX_SOFT_RST				(BIT(21))
#define BIT_AP_AHB_ZIPDEC_SOFT_RST				(BIT(20))
#define BIT_AP_AHB_ZIPENC_SOFT_RST				(BIT(19))
#define BIT_AP_AHB_BUSMON_SOFT_RST				(BIT(14))
#define BIT_AP_AHB_SPINLOCK_SOFT_RST				(BIT(13))
#define BIT_AP_AHB_EMMC_SOFT_RST				(BIT(11))
#define BIT_AP_AHB_SDIO2_SOFT_RST				(BIT(10))
#define BIT_AP_AHB_SDIO1_SOFT_RST				(BIT(9))
#define BIT_AP_AHB_SDIO0_SOFT_RST				(BIT(8))
#define BIT_AP_AHB_DRM_SOFT_RST					(BIT(7))
#define BIT_AP_AHB_NFC_SOFT_RST					(BIT(6))
#define BIT_AP_AHB_DMA_SOFT_RST					(BIT(5))
#define BIT_AP_AHB_OTG_PHY_SOFT_RST				(BIT(3))
#define BIT_AP_AHB_OTG_UTMI_SOFT_RST				(BIT(2))
#define BIT_AP_AHB_USB3_SOFT_RST				(BIT(1))
#define BIT_AP_AHB_OTG_SOFT_RST					(BIT(0))

/* bits definitions for register REG_AP_SYS_FORCE_SLEEP_CFG */
#define BIT_AP_AHB_AP_PERI_FORCE_ON				(BIT(2))
#define BIT_AP_AHB_AP_PERI_FORCE_SLP				(BIT(1))
#define BIT_AP_AHB_AP_APB_SLEEP					(BIT(0))

/* bits definitions for register REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG */
#define BIT_AP_AHB_DMA_ACT_LIGHT_EN				(BIT(2))
#define BIT_AP_AHB_AP_AHB_AUTO_GATE_EN				(BIT(1))
#define BIT_AP_AHB_AP_EMC_AUTO_GATE_EN				(BIT(0))

/* bits definitions for register REG_AP_AHB_HOLDING_PEN */
#define BITS_AP_AHB_HOLDING_PEN(_X_)				(_X_)

/* bits definitions for register REG_AP_AHB_MISC_CKG_EN */
#define BITS_AP_AHB_BUS_CLK_FORCE_ON(_X_)			((_X_) << 2 & (BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15)))
#define BIT_AP_AHB_DPHY_REF_CKG_EN				(BIT(1))
#define BIT_AP_AHB_DPHY_CFG_CKG_EN				(BIT(0))

/* bits definitions for register REG_AP_AHB_MISC_CFG */
#define BITS_AP_AHB_AP_R_RES(_X_)				((_X_) << 27 & (BIT(27)|BIT(28)|BIT(29)|BIT(30)|BIT(31)))
#define BITS_AP_AHB_OTG_HADDR_EXT(_X_)				((_X_) << 24 & (BIT(24)|BIT(25)|BIT(26)))
#define BITS_AP_AHB_HSIC_HADDR_EXT(_X_)				((_X_) << 21 & (BIT(21)|BIT(22)|BIT(23)))
#define BIT_AP_AHB_SDIO2_SLV_SEL				(BIT(20))
#define BITS_AP_AHB_EMMC_SLOT_SEL(_X_)				((_X_) << 18 & (BIT(18)|BIT(19)))
#define BITS_AP_AHB_SDIO0_SLOT_SEL(_X_)				((_X_) << 16 & (BIT(16)|BIT(17)))
#define BITS_AP_AHB_AP_RW_RES(_X_)				((_X_) << 10 & (BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15)))
#define BIT_AP_AHB_M0_NIU_IDLE_DET_DIS				(BIT(9))
#define BITS_AP_AHB_BUS_VALID_CNT(_X_)				((_X_) << 4 & (BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8)))
#define BITS_AP_AHB_SDIO2_SLOT_SEL(_X_)				((_X_) << 2 & (BIT(2)|BIT(3)))
#define BITS_AP_AHB_SDIO1_SLOT_SEL(_X_)				((_X_) & (BIT(0)|BIT(1)))

/* bits definitions for register REG_AP_AHB_NANC_CLK_CFG */
#define BITS_AP_AHB_CLK_NANDC2X_DIV(_X_)			((_X_) << 2 & (BIT(2)|BIT(3)))
#define BITS_AP_AHB_CLK_NANDC2X_SEL(_X_)			((_X_) & (BIT(0)|BIT(1)))

/* bits definitions for register REG_AP_AHB_AP_QOS_CFG */
#define BITS_AP_AHB_AP_QOS_ID7(_X_)				((_X_) << 28 & (BIT(28)|BIT(29)|BIT(30)|BIT(31)))
#define BITS_AP_AHB_AP_QOS_ID6(_X_)				((_X_) << 24 & (BIT(24)|BIT(25)|BIT(26)|BIT(27)))
#define BITS_AP_AHB_AP_QOS_ID5(_X_)				((_X_) << 20 & (BIT(20)|BIT(21)|BIT(22)|BIT(23)))
#define BITS_AP_AHB_AP_QOS_ID4(_X_)				((_X_) << 16 & (BIT(16)|BIT(17)|BIT(18)|BIT(19)))
#define BITS_AP_AHB_AP_QOS_ID3(_X_)				((_X_) << 12 & (BIT(12)|BIT(13)|BIT(14)|BIT(15)))
#define BITS_AP_AHB_AP_QOS_ID2(_X_)				((_X_) << 8 & (BIT(8)|BIT(9)|BIT(10)|BIT(11)))
#define BITS_AP_AHB_AP_QOS_ID1(_X_)				((_X_) << 4 & (BIT(4)|BIT(5)|BIT(6)|BIT(7)))
#define BITS_AP_AHB_AP_QOS_ID0(_X_)				((_X_) & (BIT(0)|BIT(1)|BIT(2)|BIT(3)))

/* bits definitions for register REG_AP_AHB_OTG_PHY_TUNE */
#define BIT_AP_AHB_OTG_TXPREEMPPULSETUNE			(BIT(20))
#define BITS_AP_AHB_OTG_TXRESTUNE(_X_)				((_X_) << 18 & (BIT(18)|BIT(19)))
#define BITS_AP_AHB_OTG_TXHSXVTUNE(_X_)				((_X_) << 16 & (BIT(16)|BIT(17)))
#define BITS_AP_AHB_OTG_TXVREFTUNE(_X_)				((_X_) << 12 & (BIT(12)|BIT(13)|BIT(14)|BIT(15)))
#define BITS_AP_AHB_OTG_TXPREEMPAMPTUNE(_X_)			((_X_) << 10 & (BIT(10)|BIT(11)))
#define BITS_AP_AHB_OTG_TXRISETUNE(_X_)				((_X_) << 8 & (BIT(8)|BIT(9)))
#define BITS_AP_AHB_OTG_TXFSLSTUNE(_X_)				((_X_) << 4 & (BIT(4)|BIT(5)|BIT(6)|BIT(7)))
#define BITS_AP_AHB_OTG_SQRXTUNE(_X_)				((_X_) & (BIT(0)|BIT(1)|BIT(2)))

/* bits definitions for register REG_AP_AHB_OTG_PHY_TEST */
#define BIT_AP_AHB_OTG_ATERESET					(BIT(31))
#define BIT_AP_AHB_OTG_VBUS_VALID_EXT_SEL			(BIT(26))
#define BIT_AP_AHB_OTG_VBUS_VALID_EXT				(BIT(25))
#define BIT_AP_AHB_OTG_OTGDISABLE				(BIT(24))
#define BIT_AP_AHB_OTG_TESTBURNIN				(BIT(21))
#define BIT_AP_AHB_OTG_LOOPBACKENB				(BIT(20))
#define BITS_AP_AHB_OTG_TESTDATAOUT(_X_)			((_X_) << 16 & (BIT(16)|BIT(17)|BIT(18)|BIT(19)))
#define BITS_AP_AHB_OTG_VATESTENB(_X_)				((_X_) << 14 & (BIT(14)|BIT(15)))
#define BIT_AP_AHB_OTG_TESTCLK					(BIT(13))
#define BIT_AP_AHB_OTG_TESTDATAOUTSEL				(BIT(12))
#define BITS_AP_AHB_OTG_TESTADDR(_X_)				((_X_) << 8 & (BIT(8)|BIT(9)|BIT(10)|BIT(11)))
#define BITS_AP_AHB_OTG_TESTDATAIN(_X_)				((_X_) & (BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)))

/* bits definitions for register REG_AP_AHB_OTG_PHY_CTRL */
#define BITS_AP_AHB_OTG_SS_SCALEDOWNMODE(_X_)			((_X_) << 25 & (BIT(25)|BIT(26)))
#define BIT_AP_AHB_OTG_TXBITSTUFFENH				(BIT(23))
#define BIT_AP_AHB_OTG_TXBITSTUFFEN				(BIT(22))
#define BIT_AP_AHB_OTG_DMPULLDOWN				(BIT(21))
#define BIT_AP_AHB_OTG_DPPULLDOWN				(BIT(20))
#define BIT_AP_AHB_OTG_DMPULLUP					(BIT(9))
#define BIT_AP_AHB_OTG_COMMONONN				(BIT(8))
#define BITS_AP_AHB_OTG_REFCLKSEL(_X_)				((_X_) << 4 & (BIT(4)|BIT(5)))
#define BITS_AP_AHB_OTG_FSEL(_X_)				((_X_) & (BIT(0)|BIT(1)|BIT(2)))

/* bits definitions for register REG_AP_AHB_HSIC_PHY_TUNE */
#define BITS_AP_AHB_HSIC_REFCLK_DIV(_X_)			((_X_) << 24 & (BIT(24)|BIT(25)|BIT(26)|BIT(27)|BIT(28)|BIT(29)|BIT(30)))
#define BIT_AP_AHB_HSIC_TXPREEMPPULSETUNE			(BIT(20))
#define BITS_AP_AHB_HSIC_TXRESTUNE(_X_)				((_X_) << 18 & (BIT(18)|BIT(19)))
#define BITS_AP_AHB_HSIC_TXHSXVTUNE(_X_)			((_X_) << 16 & (BIT(16)|BIT(17)))
#define BITS_AP_AHB_HSIC_TXVREFTUNE(_X_)			((_X_) << 12 & (BIT(12)|BIT(13)|BIT(14)|BIT(15)))
#define BITS_AP_AHB_HSIC_TXPREEMPAMPTUNE(_X_)			((_X_) << 10 & (BIT(10)|BIT(11)))
#define BITS_AP_AHB_HSIC_TXRISETUNE(_X_)			((_X_) << 8 & (BIT(8)|BIT(9)))
#define BITS_AP_AHB_HSIC_TXFSLSTUNE(_X_)			((_X_) << 4 & (BIT(4)|BIT(5)|BIT(6)|BIT(7)))
#define BITS_AP_AHB_HSIC_SQRXTUNE(_X_)				((_X_) & (BIT(0)|BIT(1)|BIT(2)))

/* bits definitions for register REG_AP_AHB_HSIC_PHY_TEST */
#define BIT_AP_AHB_HSIC_ATERESET				(BIT(31))
#define BIT_AP_AHB_HSIC_VBUS_VALID_EXT_SEL			(BIT(26))
#define BIT_AP_AHB_HSIC_VBUS_VALID_EXT				(BIT(25))
#define BIT_AP_AHB_HSIC_OTGDISABLE				(BIT(24))
#define BIT_AP_AHB_HSIC_TESTBURNIN				(BIT(21))
#define BIT_AP_AHB_HSIC_LOOPBACKENB				(BIT(20))
#define BITS_AP_AHB_HSIC_TESTDATAOUT(_X_)			((_X_) << 16 & (BIT(16)|BIT(17)|BIT(18)|BIT(19)))
#define BITS_AP_AHB_HSIC_VATESTENB(_X_)				((_X_) << 14 & (BIT(14)|BIT(15)))
#define BIT_AP_AHB_HSIC_TESTCLK					(BIT(13))
#define BIT_AP_AHB_HSIC_TESTDATAOUTSEL				(BIT(12))
#define BITS_AP_AHB_HSIC_TESTADDR(_X_)				((_X_) << 8 & (BIT(8)|BIT(9)|BIT(10)|BIT(11)))
#define BITS_AP_AHB_HSIC_TESTDATAIN(_X_)			((_X_) & (BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)))

/* bits definitions for register REG_AP_AHB_HSIC_PHY_CTRL */
#define BITS_AP_AHB_HSIC_SS_SCALEDOWNMODE(_X_)			((_X_) << 25 & (BIT(25)|BIT(26)))
#define BIT_AP_AHB_HSIC_TXBITSTUFFENH				(BIT(23))
#define BIT_AP_AHB_HSIC_TXBITSTUFFEN				(BIT(22))
#define BIT_AP_AHB_HSIC_DMPULLDOWN				(BIT(21))
#define BIT_AP_AHB_HSIC_DPPULLDOWN				(BIT(20))
#define BIT_AP_AHB_HSIC_IF_MODE					(BIT(16))
#define BIT_AP_AHB_IF_SELECT_HSIC				(BIT(13))
#define BIT_AP_AHB_HSIC_DBNCE_FLTR_BYPASS			(BIT(12))
#define BIT_AP_AHB_HSIC_DMPULLUP				(BIT(9))
#define BIT_AP_AHB_HSIC_COMMONONN				(BIT(8))
#define BITS_AP_AHB_HSIC_REFCLKSEL(_X_)				((_X_) << 4 & (BIT(4)|BIT(5)))
#define BITS_AP_AHB_HSIC_FSEL(_X_)				((_X_) & (BIT(0)|BIT(1)|BIT(2)))

/* bits definitions for register REG_AP_AHB_USB3_CTRL */
#define BIT_AP_AHB_HOST_SYSTEM_ERR				(BIT(12))
#define BIT_AP_AHB_HOST_PORT_POWER_CONTROL_PRESENT		(BIT(11))
#define BITS_AP_AHB_FLADJ_30MHZ_REG(_X_)			((_X_) << 5 & (BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9)|BIT(10)))
#define BIT_AP_AHB_PME_EN					(BIT(4))
#define BITS_AP_AHB_BUS_FILTER_BYPASS(_X_)			((_X_) & (BIT(0)|BIT(1)|BIT(2)|BIT(3)))

/* bits definitions for register REG_AP_AHB_MISC_CTRL */
#define BITS_AP_AHB_MAINHURRY_HSIC(_X_)				((_X_) << 27 & (BIT(27)|BIT(28)|BIT(29)))
#define BITS_AP_AHB_MAINPRESS_HSIC(_X_)				((_X_) << 24 & (BIT(24)|BIT(25)|BIT(26)))
#define BITS_AP_AHB_MAINHURRY_OTG(_X_)				((_X_) << 21 & (BIT(21)|BIT(22)|BIT(23)))
#define BITS_AP_AHB_MAINPRESS_OTG(_X_)				((_X_) << 18 & (BIT(18)|BIT(19)|BIT(20)))
#define BITS_AP_AHB_CC63P_APBS_PPROT(_X_)			((_X_) << 15 & (BIT(15)|BIT(16)|BIT(17)))
#define BITS_AP_AHB_CC63S_APBS_PPROT(_X_)			((_X_) << 12 & (BIT(12)|BIT(13)|BIT(14)))
#define BITS_AP_AHB_AWPROT_ZIPDEC(_X_)				((_X_) << 9 & (BIT(9)|BIT(10)|BIT(11)))
#define BITS_AP_AHB_ARPROT_ZIPDEC(_X_)				((_X_) << 6 & (BIT(6)|BIT(7)|BIT(8)))
#define BITS_AP_AHB_AWPROT_ZIPENC(_X_)				((_X_) << 3 & (BIT(3)|BIT(4)|BIT(5)))
#define BITS_AP_AHB_ARPROT_ZIPENC(_X_)				((_X_) & (BIT(0)|BIT(1)|BIT(2)))

/* bits definitions for register REG_AP_AHB_MISC_STATUS */
#define BIT_AP_AHB_INT_REQ_CC63P				(BIT(1))
#define BIT_AP_AHB_INT_REQ_CC63S				(BIT(0))

/* bits definitions for register REG_AP_AHB_NOC_CTRL0 */
#define BITS_AP_AHB_M9_QOS(_X_)					((_X_) << 28 & (BIT(28)|BIT(29)|BIT(30)|BIT(31)))
#define BITS_AP_AHB_M7_QOS(_X_)					((_X_) << 24 & (BIT(24)|BIT(25)|BIT(26)|BIT(27)))
#define BITS_AP_AHB_M6_QOS(_X_)					((_X_) << 20 & (BIT(20)|BIT(21)|BIT(22)|BIT(23)))
#define BITS_AP_AHB_M5_QOS(_X_)					((_X_) << 16 & (BIT(16)|BIT(17)|BIT(18)|BIT(19)))
#define BITS_AP_AHB_M4_QOS(_X_)					((_X_) << 12 & (BIT(12)|BIT(13)|BIT(14)|BIT(15)))
#define BITS_AP_AHB_M3_QOS(_X_)					((_X_) << 8 & (BIT(8)|BIT(9)|BIT(10)|BIT(11)))
#define BITS_AP_AHB_M2_QOS(_X_)					((_X_) << 4 & (BIT(4)|BIT(5)|BIT(6)|BIT(7)))
#define BITS_AP_AHB_M1_QOS(_X_)					((_X_) & (BIT(0)|BIT(1)|BIT(2)|BIT(3)))

/* bits definitions for register REG_AP_AHB_NOC_CTRL1 */
#define BIT_AP_AHB_S5_T_MAINEXTEN				(BIT(21))
#define BIT_AP_AHB_S4_T_MAINEXTEN				(BIT(20))
#define BIT_AP_AHB_S3_T_MAINEXTEN				(BIT(19))
#define BIT_AP_AHB_S2_T_MAINEXTEN				(BIT(18))
#define BIT_AP_AHB_S1_T_MAINEXTEN				(BIT(17))
#define BIT_AP_AHB_S0_T_MAINEXTEN				(BIT(16))
#define BITS_AP_AHB_M14_QOS(_X_)				((_X_) << 12 & (BIT(12)|BIT(13)|BIT(14)|BIT(15)))
#define BITS_AP_AHB_M13_QOS(_X_)				((_X_) << 8 & (BIT(8)|BIT(9)|BIT(10)|BIT(11)))
#define BITS_AP_AHB_M12_QOS(_X_)				((_X_) << 4 & (BIT(4)|BIT(5)|BIT(6)|BIT(7)))
#define BITS_AP_AHB_M11_QOS(_X_)				((_X_) & (BIT(0)|BIT(1)|BIT(2)|BIT(3)))

/* bits definitions for register REG_AP_AHB_NOC_CTRL2 */
#define BITS_AP_AHB_M12_ARCACHE(_X_)				((_X_) << 28 & (BIT(28)|BIT(29)|BIT(30)|BIT(31)))
#define BITS_AP_AHB_M11_ARCACHE(_X_)				((_X_) << 24 & (BIT(24)|BIT(25)|BIT(26)|BIT(27)))
#define BITS_AP_AHB_M7_ARCACHE(_X_)				((_X_) << 20 & (BIT(20)|BIT(21)|BIT(22)|BIT(23)))
#define BITS_AP_AHB_M6_ARCACHE(_X_)				((_X_) << 16 & (BIT(16)|BIT(17)|BIT(18)|BIT(19)))
#define BITS_AP_AHB_M5_ARCACHE(_X_)				((_X_) << 12 & (BIT(12)|BIT(13)|BIT(14)|BIT(15)))
#define BITS_AP_AHB_M4_ARCACHE(_X_)				((_X_) << 8 & (BIT(8)|BIT(9)|BIT(10)|BIT(11)))
#define BITS_AP_AHB_M3_ARCACHE(_X_)				((_X_) << 4 & (BIT(4)|BIT(5)|BIT(6)|BIT(7)))
#define BITS_AP_AHB_M2_ARCACHE(_X_)				((_X_) & (BIT(0)|BIT(1)|BIT(2)|BIT(3)))

/* bits definitions for register REG_AP_AHB_NOC_CTRL3 */
#define BITS_AP_AHB_M12_AWCACHE(_X_)				((_X_) << 28 & (BIT(28)|BIT(29)|BIT(30)|BIT(31)))
#define BITS_AP_AHB_M11_AWCACHE(_X_)				((_X_) << 24 & (BIT(24)|BIT(25)|BIT(26)|BIT(27)))
#define BITS_AP_AHB_M7_AWCACHE(_X_)				((_X_) << 20 & (BIT(20)|BIT(21)|BIT(22)|BIT(23)))
#define BITS_AP_AHB_M6_AWCACHE(_X_)				((_X_) << 16 & (BIT(16)|BIT(17)|BIT(18)|BIT(19)))
#define BITS_AP_AHB_M5_AWCACHE(_X_)				((_X_) << 12 & (BIT(12)|BIT(13)|BIT(14)|BIT(15)))
#define BITS_AP_AHB_M4_AWCACHE(_X_)				((_X_) << 8 & (BIT(8)|BIT(9)|BIT(10)|BIT(11)))
#define BITS_AP_AHB_M3_AWCACHE(_X_)				((_X_) << 4 & (BIT(4)|BIT(5)|BIT(6)|BIT(7)))
#define BITS_AP_AHB_M2_AWCACHE(_X_)				((_X_) & (BIT(0)|BIT(1)|BIT(2)|BIT(3)))

/* bits definitions for register REG_AP_AHB_USB3_DBG0 */
#define BITS_AP_AHB_USB3_DUG_0(_X_)				(_X_)

/* bits definitions for register REG_AP_AHB_USB3_DBG1 */
#define BITS_AP_AHB_USB3_DUG_1(_X_)				(_X_)

/* bits definitions for register REG_AP_AHB_USB3_DBG2 */
#define BITS_AP_AHB_USB3_DUG_2(_X_)				((_X_) & (BIT(0)|BIT(1)))

#endif
