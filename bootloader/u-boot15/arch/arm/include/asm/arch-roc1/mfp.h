/*
 * arch/arm/mach-sprd/include/mach/pm.h
 *
 * Pin Map Definitions
 *
 * Copyright (C) 2010 Spreadtrum International Ltd.
 *
 * 2010-03-05: yingchun li <yingchun.li@spreadtrum.com>
 *            initial version
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */

#ifndef __ASM_ARCH_MFP_H
#define __ASM_ARCH_MFP_H

/*
	This is identical to the order of pin's register map.
	NOTE: if the pin register is not countinus, you should
	intest a RESEVERED pin between them;
*/
#define PIN_SIMCLK0_REG_OFFS                          (0x008C)
#define PIN_SIMDA0_REG_OFFS                          (0x0090)
#define PIN_SIMRST0_REG_OFFS                          (0x0094)
#define PIN_SIMCLK1_REG_OFFS                          (0x0098)
#define PIN_SIMDA1_REG_OFFS                          (0x009C)
#define PIN_SIMRST1_REG_OFFS                          (0x00A0)
#define PIN_SD0_CLK_REG_OFFS                          (0x0030)
#define PIN_SD0_CMD_REG_OFFS                          (0x0034)
#define PIN_SD0_D0_REG_OFFS                          (0x0038)
#define PIN_SD0_D1_REG_OFFS                          (0x003c)
#define PIN_SD0_D2_REG_OFFS                          (0x0040)
#define PIN_SD0_D3_REG_OFFS                          (0x0044)
#define PIN_SD1_CLK_REG_OFFS                          (0x01fc)
#define PIN_SD1_CMD_REG_OFFS                          (0x0200)
#define PIN_SD1_D0_REG_OFFS                          (0x0204)
#define PIN_SD1_D1_REG_OFFS                          (0x0208)
#define PIN_SD1_D2_REG_OFFS                          (0x020c)
#define PIN_SD1_D3_REG_OFFS                          (0x0210)
#define PIN_KEYOUT0_REG_OFFS                          (0x011C)
#define PIN_KEYOUT1_REG_OFFS                          (0x0120)
#define PIN_KEYOUT2_REG_OFFS                          (0x0124)
#define PIN_KEYOUT3_REG_OFFS                          (0x0128)
#define PIN_KEYOUT4_REG_OFFS                          (0x012C)
#define PIN_KEYOUT5_REG_OFFS                          (0x0130)
#define PIN_KEYOUT6_REG_OFFS                          (0x014C)
#define PIN_KEYOUT7_REG_OFFS                          (0x0150)
#define PIN_KEYIN0_REG_OFFS                          (0x0154)
#define PIN_KEYIN1_REG_OFFS                          (0x0158)
#define PIN_KEYIN2_REG_OFFS                          (0x015C)
#define PIN_KEYIN3_REG_OFFS                          (0x0160)
#define PIN_KEYIN4_REG_OFFS                          (0x0164)
#define PIN_KEYIN5_REG_OFFS                          (0x0168)
#define PIN_KEYIN6_REG_OFFS                          (0x016C)
#define PIN_KEYIN7_REG_OFFS                          (0x0170)
#define PIN_SPI_DI_REG_OFFS                          (0x0100)
#define PIN_SPI_CLK_REG_OFFS                          (0x0104)
#define PIN_SPI_DO_REG_OFFS                          (0x0108)
#define PIN_SPI_CSN0_REG_OFFS                          (0x010C)
#define PIN_SPI_CSN1_REG_OFFS                          (0x0110)
#define PIN_MTDO_REG_OFFS                          (0x0114)
#define PIN_MTDI_REG_OFFS                          (0x0118)
#define PIN_MTCK_REG_OFFS                          (0x011C)
#define PIN_MTMS_REG_OFFS                          (0x0120)
#define PIN_MTRST_N_REG_OFFS                          (0x0124)
#define PIN_U0TXD_REG_OFFS                          (0x0128)
#define PIN_U0RXD_REG_OFFS                          (0x012C)
#define PIN_U0CTS_REG_OFFS                          (0x0130)
#define PIN_U0RTS_REG_OFFS                          (0x0134)
#define PIN_U1TXD_REG_OFFS                          (0x0138)
#define PIN_U1RXD_REG_OFFS                          (0x013C)
#define PIN_NFWPN_REG_OFFS                          (0x0140)
#define PIN_NFRB_REG_OFFS                          (0x0144)
#define PIN_NFCLE_REG_OFFS                          (0x0148)
#define PIN_NFALE_REG_OFFS                          (0x014C)
#define PIN_NFCEN_REG_OFFS                          (0x0150)
#define PIN_NFWEN_REG_OFFS                          (0x0154)
#define PIN_NFREN_REG_OFFS                          (0x0158)
#define PIN_NFD0_REG_OFFS                          (0x015C)
#define PIN_NFD1_REG_OFFS                          (0x0160)
#define PIN_NFD2_REG_OFFS                          (0x0164)
#define PIN_NFD3_REG_OFFS                          (0x0168)
#define PIN_NFD4_REG_OFFS                          (0x016C)
#define PIN_NFD5_REG_OFFS                          (0x0170)
#define PIN_NFD6_REG_OFFS                          (0x0174)
#define PIN_NFD7_REG_OFFS                          (0x0178)
#define PIN_NFD8_REG_OFFS                          (0x017C)
#define PIN_NFD9_REG_OFFS                          (0x0180)
#define PIN_NFD10_REG_OFFS                          (0x0184)
#define PIN_NFD11_REG_OFFS                          (0x0188)
#define PIN_NFD12_REG_OFFS                          (0x018C)
#define PIN_NFD13_REG_OFFS                          (0x0190)
#define PIN_NFD14_REG_OFFS                          (0x0194)
#define PIN_NFD15_REG_OFFS                          (0x0198)
#define PIN_EMRST_N_REG_OFFS                          (0x019C)
#define PIN_EMA0_REG_OFFS                          (0x01A0)
#define PIN_EMA1_REG_OFFS                          (0x01A4)
#define PIN_EMA2_REG_OFFS                          (0x01A8)
#define PIN_EMA3_REG_OFFS                          (0x01AC)
#define PIN_EMA4_REG_OFFS                          (0x01B0)
#define PIN_EMA5_REG_OFFS                          (0x01B4)
#define PIN_EMA6_REG_OFFS                          (0x01B8)
#define PIN_EMA7_REG_OFFS                          (0x01BC)
#define PIN_EMA8_REG_OFFS                          (0x01C0)
#define PIN_EMA9_REG_OFFS                          (0x01C4)
#define PIN_EMA10_REG_OFFS                          (0x01C8)
#define PIN_EMA11_REG_OFFS                          (0x01CC)
#define PIN_EMA12_REG_OFFS                          (0x01D0)
#define PIN_EMA13_REG_OFFS                          (0x01D4)
#define PIN_EMCKE1_REG_OFFS                          (0x01D8)
#define PIN_EMD0_REG_OFFS                          (0x01DC)
#define PIN_EMD1_REG_OFFS                          (0x01E0)
#define PIN_EMD2_REG_OFFS                          (0x01E4)
#define PIN_EMD3_REG_OFFS                          (0x01E8)
#define PIN_EMD4_REG_OFFS                          (0x01EC)
#define PIN_EMD5_REG_OFFS                          (0x01F0)
#define PIN_EMD6_REG_OFFS                          (0x01F4)
#define PIN_EMD7_REG_OFFS                          (0x01F8)
#define PIN_EMDQM0_REG_OFFS                          (0x01FC)
#define PIN_EMDQS0_REG_OFFS                          (0x0200)
#define PIN_EMD8_REG_OFFS                          (0x0204)
#define PIN_EMD9_REG_OFFS                          (0x0208)
#define PIN_EMD10_REG_OFFS                          (0x020C)
#define PIN_EMD11_REG_OFFS                          (0x0210)
#define PIN_EMD12_REG_OFFS                          (0x0214)
#define PIN_EMD13_REG_OFFS                          (0x0218)
#define PIN_EMD14_REG_OFFS                          (0x021C)
#define PIN_EMD15_REG_OFFS                          (0x0220)
#define PIN_EMDQM1_REG_OFFS                          (0x0224)
#define PIN_EMDQS1_REG_OFFS                          (0x0228)
#define PIN_EMD16_REG_OFFS                          (0x022C)
#define PIN_EMD17_REG_OFFS                          (0x0230)
#define PIN_EMD18_REG_OFFS                          (0x0234)
#define PIN_EMD19_REG_OFFS                          (0x0238)
#define PIN_EMD20_REG_OFFS                          (0x023C)
#define PIN_EMD21_REG_OFFS                          (0x0240)
#define PIN_EMD22_REG_OFFS                          (0x0244)
#define PIN_EMD23_REG_OFFS                          (0x0248)
#define PIN_EMDQM2_REG_OFFS                          (0x024C)
#define PIN_EMDQS2_REG_OFFS                          (0x0250)
#define PIN_EMD24_REG_OFFS                          (0x0254)
#define PIN_EMD25_REG_OFFS                          (0x0258)
#define PIN_EMD26_REG_OFFS                          (0x025C)
#define PIN_EMD27_REG_OFFS                          (0x0260)
#define PIN_EMD28_REG_OFFS                          (0x0264)
#define PIN_EMD29_REG_OFFS                          (0x0268)
#define PIN_EMD30_REG_OFFS                          (0x026C)
#define PIN_EMD31_REG_OFFS                          (0x0270)
#define PIN_EMDQM3_REG_OFFS                          (0x0274)
#define PIN_EMDQS3_REG_OFFS                          (0x0278)
#define PIN_CLKDPMEM_REG_OFFS                          (0x027C)
#define PIN_CLKDMMEM_REG_OFFS                          (0x0280)
#define PIN_EMRAS_N_REG_OFFS                          (0x0284)
#define PIN_EMCAS_N_REG_OFFS                          (0x0288)
#define PIN_EMWE_N_REG_OFFS                          (0x028C)
#define PIN_EMCS_N0_REG_OFFS                          (0x0290)
#define PIN_EMCS_N1_REG_OFFS                          (0x0294)
#define PIN_EMCS_N2_REG_OFFS                          (0x0298)
#define PIN_EMCS_N3_REG_OFFS                          (0x029C)
#define PIN_EMBA0_REG_OFFS                          (0x02A0)
#define PIN_EMBA1_REG_OFFS                          (0x02A4)
#define PIN_EMCKE0_REG_OFFS                          (0x02A8)
#define PIN_LCD_CSN1_REG_OFFS                          (0x02AC)
#define PIN_LCD_RSTN_REG_OFFS                          (0x02B0)
#define PIN_LCD_CD_REG_OFFS                          (0x02B4)
#define PIN_LCD_D0_REG_OFFS                          (0x02B8)
#define PIN_LCD_D1_REG_OFFS                          (0x02BC)
#define PIN_LCD_D2_REG_OFFS                          (0x02C0)
#define PIN_LCD_D3_REG_OFFS                          (0x02C4)
#define PIN_LCD_D4_REG_OFFS                          (0x02C8)
#define PIN_LCD_D5_REG_OFFS                          (0x02CC)
#define PIN_LCD_D6_REG_OFFS                          (0x02D0)
#define PIN_LCD_D7_REG_OFFS                          (0x02D4)
#define PIN_LCD_D8_REG_OFFS                          (0x02D8)
#define PIN_LCD_WRN_REG_OFFS                          (0x02DC)
#define PIN_LCD_RDN_REG_OFFS                          (0x02E0)
#define PIN_LCD_CSN0_REG_OFFS                          (0x02E4)
#define PIN_LCD_D9_REG_OFFS                          (0x02E8)
#define PIN_LCD_D10_REG_OFFS                          (0x02EC)
#define PIN_LCD_D11_REG_OFFS                          (0x02F0)
#define PIN_LCD_D12_REG_OFFS                          (0x02F4)
#define PIN_LCD_D13_REG_OFFS                          (0x02F8)
#define PIN_LCD_D14_REG_OFFS                          (0x02FC)
#define PIN_LCD_D15_REG_OFFS                          (0x0300)
#define PIN_LCD_D16_REG_OFFS                          (0x0304)
#define PIN_LCD_D17_REG_OFFS                          (0x0308)
#define PIN_LCD_FMARK_REG_OFFS                          (0x030C)
#define PIN_CCIRMCLK_REG_OFFS                          (0x0310)
#define PIN_CCIRCK_REG_OFFS                          (0x0314)
#define PIN_CCIRHS_REG_OFFS                          (0x0318)
#define PIN_CCIRVS_REG_OFFS                          (0x031C)
#define PIN_CCIRD0_REG_OFFS                          (0x0320)
#define PIN_CCIRD1_REG_OFFS                          (0x0324)
#define PIN_CCIRD2_REG_OFFS                          (0x0328)
#define PIN_CCIRD3_REG_OFFS                          (0x032C)
#define PIN_CCIRD4_REG_OFFS                          (0x0330)
#define PIN_CCIRD5_REG_OFFS                          (0x0334)
#define PIN_CCIRD6_REG_OFFS                          (0x0338)
#define PIN_CCIRD7_REG_OFFS                          (0x033C)
#define PIN_CCIRRST_REG_OFFS                          (0x0340)
#define PIN_CCIRPD1_REG_OFFS                          (0x0344)
#define PIN_CCIRPD0_REG_OFFS                          (0x0348)
#define PIN_SCL_REG_OFFS                          (0x034C)
#define PIN_SDA_REG_OFFS                          (0x0350)
#define PIN_CLK_AUX0_REG_OFFS                          (0x0354)
#define PIN_IISDI_REG_OFFS                          (0x0358)
#define PIN_IISDO_REG_OFFS                          (0x035C)
#define PIN_IISCLK_REG_OFFS                          (0x0360)
#define PIN_IISLRCK_REG_OFFS                          (0x0364)
#define PIN_IISMCK_REG_OFFS                          (0x0368)
#define PIN_RFSDA0_REG_OFFS                          (0x036C)
#define PIN_RFSCK0_REG_OFFS                          (0x0370)
#define PIN_RFSEN0_REG_OFFS                          (0x0374)
#define PIN_RFCTL0_REG_OFFS                          (0x0378)
#define PIN_RFCTL1_REG_OFFS                          (0x037C)
#define PIN_RFCTL2_REG_OFFS                          (0x0380)
#define PIN_RFCTL3_REG_OFFS                          (0x0384)
#define PIN_RFCTL4_REG_OFFS                          (0x0388)
#define PIN_RFCTL5_REG_OFFS                          (0x038C)
#define PIN_RFCTL6_REG_OFFS                          (0x0390)
#define PIN_RFCTL7_REG_OFFS                          (0x0394)
#define PIN_RFCTL8_REG_OFFS                          (0x0398)
#define PIN_RFCTL9_REG_OFFS                          (0x039C)
#define PIN_RFCTL10_REG_OFFS                          (0x03A0)
#define PIN_RFCTL11_REG_OFFS                          (0x03A4)
#define PIN_RFCTL12_REG_OFFS                          (0x03A8)
#define PIN_RFCTL13_REG_OFFS                          (0x03AC)
#define PIN_RFCTL14_REG_OFFS                          (0x03B0)
#define PIN_RFCTL15_REG_OFFS                          (0x03B4)
#define PIN_XTL_EN_REG_OFFS                          (0x03B8)
#define PIN_PTEST_REG_OFFS                          (0x03BC)
#define PIN_GPIO135_REG_OFFS                          (0x03C0)
#define PIN_GPIO136_REG_OFFS                          (0x03C4)
#define PIN_GPIO137_REG_OFFS                          (0x03C8)
#define PIN_GPIO138_REG_OFFS                          (0x03CC)
#define PIN_GPIO139_REG_OFFS                          (0x03D0)
#define PIN_GPIO140_REG_OFFS                          (0x03D4)
#define PIN_OPTION2_REG_OFFS                          (0x03D8)
#define PIN_OPTION3_REG_OFFS                          (0x03DC)
#define PIN_GPIO141_REG_OFFS                          (0x03E0)
#define PIN_GPIO142_REG_OFFS                          (0x03E4)
#define PIN_GPIO143_REG_OFFS                          (0x03E8)
#define PIN_GPIO144_REG_OFFS                          (0x03EC)

/*----------Analog Die Pin Control Register----------*/


#define ANA_PIN_CHIP_RSTN_REG_OFFS           (0x008C)
#define ANA_PIN_PBINT_REG_OFFS               (0x0094)
#define ANA_PIN_TP_XL_REG_OFFS               (0x0098)
#define ANA_PIN_TP_XR_REG_OFFS               (0x009C)
#define ANA_PIN_TP_YU_REG_OFFS               (0x00A0)
#define ANA_PIN_TP_YD_REG_OFFS               (0x00A4)

//The pin is in A die
#define A_DIE_PIN	BIT_31

#define MFP_PIN(x)	(((x##_REG_OFFS) & 0xffff) << 16)

#define MFP_ANA_PIN(x) ((((x##_REG_OFFS) & 0xffff) << 16) | A_DIE_PIN)

#define MFP_CFG_TO_REG_OFFS(x)  ((x) >> 16)

//special bit for setting, for the default value of is not same
//with all registers
#define MFP_IO_SET				(0x1 << 15)
#define MFP_S_PULL_SET 	(0x1 << 14)
#define MFP_AF_SET   			(0x1 << 13)
#define MFP_F_PULL_SET 		(0x1 << 12)
#define MFP_DS_SET 				(0x1 << 11)

/* Pinmap ctrl register Bit field value
--------------------------------------------------------------------------------------------------------------------------
|                 |                 |            |            |              |       |       |            |              |
| Reserved[31:10] | Drv str sel[9:8]| func PU[7] | func PD[6] | func sel[5:4]| PU[3] | PD[2] | input En[1]| output En[0] |
|                 |                 |            |            |              |       |       |            |              |
--------------------------------------------------------------------------------------------------------------------------
*/

/*
pin output/input enable.
NOTE, this is not applied to GPIO pins, GPIO pin's input/output direction have specific
	registers and specfic bits.
	BIT 0, 1
*/
#define MFP_IO_NONE  (0x0 << 0)
#define MFP_IO_Z		MFP_IO_NONE
#define MFP_IO_OE		(0x1	<< 0)
#define MFP_IO_IE		(0x2 << 0)
#define MFP_IO_BOTH   (0x3 << 0)
#define MFP_IO_MASK  MFP_IO_BOTH

/*
	pin weak pull up/down in sleep mode
	BIT 2, 3
*/
#define MFP_S_PULL_NONE	(0x0  << 2)
#define MFP_S_PULL_DOWN   	(0x1 << 2)
#define MFP_S_PULL_UP		(0x2  << 2)
#define MFP_S_PULL_BOTH	(0x3  << 2)
#define MFP_S_PULL_MASK 	MFP_S_PULL_BOTH

/*
	pin alternate function
	BIT 4, 5
*/
#define MFP_AF0			(0x0 << 4)
#define MFP_AF1			(0x1 << 4)
#define MFP_AF2			(0x2 << 4)
#define MFP_AF3			(0x3 << 4)
#define MFP_AF_MASK		(0x3 << 4)
#define MFP_GPIO  MFP_AF3

/*
	pin weak pull up/down in function mode
	BIT 6, 7
*/
#define MFP_F_PULL_NONE	(0x0  << 6)
#define MFP_F_PULL_DOWN   	(0x1 << 6)
#define MFP_F_PULL_UP		(0x2  << 6)
#define MFP_F_PULL_BOTH	(0x3  << 6)
#define MFP_F_PULL_MASK 	MFP_F_PULL_BOTH

/*
	pin driver strenth
	BIT 8, 9
*/

#define MFP_DS0		(0x0 << 8)
#define MFP_DS1		(0x1 << 8)
#define MFP_DS2		(0x2 << 8)
#define MFP_DS3		(0x3 << 8)
#define MFP_DS_MASK	(0x3 << 8)


#define MFP_CFG(pin, af)		\
	(MFP_AF_SET |\
	 (MFP_PIN(PIN_##pin) | MFP_##af))

#define MFP_CFG_DRV(pin, af, drv)	\
	((MFP_AF_SET |MFP_DS_SET) |\
	 (MFP_PIN(PIN_##pin) | MFP_##af | MFP_##drv))

#define MFP_CFG_SLEEP_UPDOWN(pin, af, updown)	\
	((MFP_AF_SET | MFP_S_PULL_SET) |\
	 (MFP_PIN(PIN_##pin) | MFP_##af | MFP_##updown))

#define MFP_CFG_IOE(pin, af, io)	\
	((MFP_AF_SET |MFP_IO_SET)  |\
	 (MFP_PIN(PIN_##pin) | MFP_##af | MFP_##io))

#define MFP_SET_ALL	\
	(MFP_AF_SET |MFP_IO_SET | MFP_S_PULL_SET | MFP_DS_SET | \
	MFP_F_PULL_SET)

#define MFP_CFG_X(pin, af, drv, func_updown, sleep_updown, io)	\
	(MFP_SET_ALL |\
	 (MFP_PIN(PIN_##pin) | MFP_##af | MFP_##drv |\
	 MFP_##func_updown  | MFP_##sleep_updown| MFP_##io))

#define MFP_ANA_CFG_X(pin, drv, func_updown, af, sleep_updown, io)	\
	(MFP_SET_ALL |\
	 (MFP_ANA_PIN(ANA_PIN_##pin) |  MFP_##af | MFP_##drv |\
	 MFP_##func_updown | MFP_##sleep_updown| MFP_##io))

extern unsigned long mfp_to_gpio(int pin);
extern void sprd_mfp_config(unsigned long *mfp_cfgs, int num);
#endif

