/*
 * Copyright (C) 2019 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2019-01-07 15:09:47
 *
 */


#ifndef CENTRAL_PIN_H
#define CENTRAL_PIN_H

#define CTL_BASE_CENTRAL_PIN 0x402A0000


#define REG_CENTRAL_PIN_PIN_CTRL_REG0      ( CTL_BASE_CENTRAL_PIN + 0x0000 )
#define REG_CENTRAL_PIN_PIN_CTRL_REG1      ( CTL_BASE_CENTRAL_PIN + 0x0004 )
#define REG_CENTRAL_PIN_PIN_CTRL_REG2      ( CTL_BASE_CENTRAL_PIN + 0x0008 )
#define REG_CENTRAL_PIN_PIN_CTRL_REG3      ( CTL_BASE_CENTRAL_PIN + 0x000C )
#define REG_CENTRAL_PIN_PIN_CTRL_REG4      ( CTL_BASE_CENTRAL_PIN + 0x0010 )
#define REG_CENTRAL_PIN_PIN_CTRL_REG5      ( CTL_BASE_CENTRAL_PIN + 0x0014 )
#define REG_CENTRAL_PIN_IIS1DI             ( CTL_BASE_CENTRAL_PIN + 0x0020 )
#define REG_CENTRAL_PIN_IIS1DO             ( CTL_BASE_CENTRAL_PIN + 0x0024 )
#define REG_CENTRAL_PIN_IIS1CLK            ( CTL_BASE_CENTRAL_PIN + 0x0028 )
#define REG_CENTRAL_PIN_IIS1LRCK           ( CTL_BASE_CENTRAL_PIN + 0x002C )
#define REG_CENTRAL_PIN_SCL2               ( CTL_BASE_CENTRAL_PIN + 0x0030 )
#define REG_CENTRAL_PIN_SDA2               ( CTL_BASE_CENTRAL_PIN + 0x0034 )
#define REG_CENTRAL_PIN_CLK_AUX0           ( CTL_BASE_CENTRAL_PIN + 0x0038 )
#define REG_CENTRAL_PIN_T_DIG              ( CTL_BASE_CENTRAL_PIN + 0x003C )
#define REG_CENTRAL_PIN_GNSS_LNA_EN        ( CTL_BASE_CENTRAL_PIN + 0x0040 )
#define REG_CENTRAL_PIN_EXTINT0            ( CTL_BASE_CENTRAL_PIN + 0x0044 )
#define REG_CENTRAL_PIN_EXTINT1            ( CTL_BASE_CENTRAL_PIN + 0x0048 )
#define REG_CENTRAL_PIN_SCL3               ( CTL_BASE_CENTRAL_PIN + 0x004C )
#define REG_CENTRAL_PIN_SDA3               ( CTL_BASE_CENTRAL_PIN + 0x0050 )
#define REG_CENTRAL_PIN_SCL0               ( CTL_BASE_CENTRAL_PIN + 0x0054 )
#define REG_CENTRAL_PIN_SDA0               ( CTL_BASE_CENTRAL_PIN + 0x0058 )
#define REG_CENTRAL_PIN_SCL1               ( CTL_BASE_CENTRAL_PIN + 0x005C )
#define REG_CENTRAL_PIN_SDA1               ( CTL_BASE_CENTRAL_PIN + 0x0060 )
#define REG_CENTRAL_PIN_CMPD2              ( CTL_BASE_CENTRAL_PIN + 0x0064 )
#define REG_CENTRAL_PIN_CMRST2             ( CTL_BASE_CENTRAL_PIN + 0x0068 )
#define REG_CENTRAL_PIN_CMMCLK0            ( CTL_BASE_CENTRAL_PIN + 0x006C )
#define REG_CENTRAL_PIN_CMRST0             ( CTL_BASE_CENTRAL_PIN + 0x0070 )
#define REG_CENTRAL_PIN_CMPD0              ( CTL_BASE_CENTRAL_PIN + 0x0074 )
#define REG_CENTRAL_PIN_CMMCLK1            ( CTL_BASE_CENTRAL_PIN + 0x0078 )
#define REG_CENTRAL_PIN_CMRST1             ( CTL_BASE_CENTRAL_PIN + 0x007C )
#define REG_CENTRAL_PIN_CMPD1              ( CTL_BASE_CENTRAL_PIN + 0x0080 )
#define REG_CENTRAL_PIN_U0TXD              ( CTL_BASE_CENTRAL_PIN + 0x0084 )
#define REG_CENTRAL_PIN_U0RXD              ( CTL_BASE_CENTRAL_PIN + 0x0088 )
#define REG_CENTRAL_PIN_U0CTS              ( CTL_BASE_CENTRAL_PIN + 0x008C )
#define REG_CENTRAL_PIN_U0RTS              ( CTL_BASE_CENTRAL_PIN + 0x0090 )
#define REG_CENTRAL_PIN_U1TXD              ( CTL_BASE_CENTRAL_PIN + 0x0094 )
#define REG_CENTRAL_PIN_U1RXD              ( CTL_BASE_CENTRAL_PIN + 0x0098 )
#define REG_CENTRAL_PIN_U2TXD              ( CTL_BASE_CENTRAL_PIN + 0x009C )
#define REG_CENTRAL_PIN_U2RXD              ( CTL_BASE_CENTRAL_PIN + 0x00A0 )
#define REG_CENTRAL_PIN_EXTINT9            ( CTL_BASE_CENTRAL_PIN + 0x00A4 )
#define REG_CENTRAL_PIN_EXTINT10           ( CTL_BASE_CENTRAL_PIN + 0x00A8 )
#define REG_CENTRAL_PIN_EMMC_D2            ( CTL_BASE_CENTRAL_PIN + 0x00AC )
#define REG_CENTRAL_PIN_EMMC_D5            ( CTL_BASE_CENTRAL_PIN + 0x00B0 )
#define REG_CENTRAL_PIN_EMMC_D1            ( CTL_BASE_CENTRAL_PIN + 0x00B4 )
#define REG_CENTRAL_PIN_EMMC_D4            ( CTL_BASE_CENTRAL_PIN + 0x00B8 )
#define REG_CENTRAL_PIN_EMMC_DUMMY         ( CTL_BASE_CENTRAL_PIN + 0x00BC )
#define REG_CENTRAL_PIN_EMMC_DS            ( CTL_BASE_CENTRAL_PIN + 0x00C0 )
#define REG_CENTRAL_PIN_EMMC_CLK           ( CTL_BASE_CENTRAL_PIN + 0x00C4 )
#define REG_CENTRAL_PIN_EMMC_D6            ( CTL_BASE_CENTRAL_PIN + 0x00C8 )
#define REG_CENTRAL_PIN_EMMC_D3            ( CTL_BASE_CENTRAL_PIN + 0x00CC )
#define REG_CENTRAL_PIN_EMMC_D0            ( CTL_BASE_CENTRAL_PIN + 0x00D0 )
#define REG_CENTRAL_PIN_EMMC_CMD           ( CTL_BASE_CENTRAL_PIN + 0x00D4 )
#define REG_CENTRAL_PIN_EMMC_D7            ( CTL_BASE_CENTRAL_PIN + 0x00D8 )
#define REG_CENTRAL_PIN_EMMC_RST           ( CTL_BASE_CENTRAL_PIN + 0x00DC )
#define REG_CENTRAL_PIN_NF_DATA_2          ( CTL_BASE_CENTRAL_PIN + 0x00E0 )
#define REG_CENTRAL_PIN_NF_DATA_0          ( CTL_BASE_CENTRAL_PIN + 0x00E4 )
#define REG_CENTRAL_PIN_NF_DATA_1          ( CTL_BASE_CENTRAL_PIN + 0x00E8 )
#define REG_CENTRAL_PIN_NF_WEN             ( CTL_BASE_CENTRAL_PIN + 0x00EC )
#define REG_CENTRAL_PIN_NF_CEN0            ( CTL_BASE_CENTRAL_PIN + 0x00F0 )
#define REG_CENTRAL_PIN_LCM_RSTN           ( CTL_BASE_CENTRAL_PIN + 0x00F4 )
#define REG_CENTRAL_PIN_DSI_TE             ( CTL_BASE_CENTRAL_PIN + 0x00F8 )
#define REG_CENTRAL_PIN_PTEST              ( CTL_BASE_CENTRAL_PIN + 0x00FC )
#define REG_CENTRAL_PIN_ANA_INT            ( CTL_BASE_CENTRAL_PIN + 0x0100 )
#define REG_CENTRAL_PIN_EXT_RST_B          ( CTL_BASE_CENTRAL_PIN + 0x0104 )
#define REG_CENTRAL_PIN_CHIP_SLEEP         ( CTL_BASE_CENTRAL_PIN + 0x0108 )
#define REG_CENTRAL_PIN_XTL_BUF_EN0        ( CTL_BASE_CENTRAL_PIN + 0x010C )
#define REG_CENTRAL_PIN_XTL_BUF_EN1        ( CTL_BASE_CENTRAL_PIN + 0x0110 )
#define REG_CENTRAL_PIN_CLK_32K            ( CTL_BASE_CENTRAL_PIN + 0x0114 )
#define REG_CENTRAL_PIN_AUD_SCLK           ( CTL_BASE_CENTRAL_PIN + 0x0118 )
#define REG_CENTRAL_PIN_AUD_ADD0           ( CTL_BASE_CENTRAL_PIN + 0x011C )
#define REG_CENTRAL_PIN_AUD_ADSYNC         ( CTL_BASE_CENTRAL_PIN + 0x0120 )
#define REG_CENTRAL_PIN_AUD_DAD1           ( CTL_BASE_CENTRAL_PIN + 0x0124 )
#define REG_CENTRAL_PIN_AUD_DAD0           ( CTL_BASE_CENTRAL_PIN + 0x0128 )
#define REG_CENTRAL_PIN_AUD_DASYNC         ( CTL_BASE_CENTRAL_PIN + 0x012C )
#define REG_CENTRAL_PIN_ADI_D              ( CTL_BASE_CENTRAL_PIN + 0x0130 )
#define REG_CENTRAL_PIN_ADI_SYNC           ( CTL_BASE_CENTRAL_PIN + 0x0134 )
#define REG_CENTRAL_PIN_ADI_SCLK           ( CTL_BASE_CENTRAL_PIN + 0x0138 )
#define REG_CENTRAL_PIN_SD0_D3             ( CTL_BASE_CENTRAL_PIN + 0x013C )
#define REG_CENTRAL_PIN_SD0_D2             ( CTL_BASE_CENTRAL_PIN + 0x0140 )
#define REG_CENTRAL_PIN_SD0_CMD            ( CTL_BASE_CENTRAL_PIN + 0x0144 )
#define REG_CENTRAL_PIN_SD0_D0             ( CTL_BASE_CENTRAL_PIN + 0x0148 )
#define REG_CENTRAL_PIN_SD0_D1             ( CTL_BASE_CENTRAL_PIN + 0x014C )
#define REG_CENTRAL_PIN_SD0_CLK0           ( CTL_BASE_CENTRAL_PIN + 0x0150 )
#define REG_CENTRAL_PIN_SD0_DUMMY          ( CTL_BASE_CENTRAL_PIN + 0x0154 )
#define REG_CENTRAL_PIN_SD2_CLK            ( CTL_BASE_CENTRAL_PIN + 0x0158 )
#define REG_CENTRAL_PIN_SD2_CMD            ( CTL_BASE_CENTRAL_PIN + 0x015C )
#define REG_CENTRAL_PIN_SD2_D0             ( CTL_BASE_CENTRAL_PIN + 0x0160 )
#define REG_CENTRAL_PIN_SD2_D1             ( CTL_BASE_CENTRAL_PIN + 0x0164 )
#define REG_CENTRAL_PIN_SD2_D2             ( CTL_BASE_CENTRAL_PIN + 0x0168 )
#define REG_CENTRAL_PIN_SD2_D3             ( CTL_BASE_CENTRAL_PIN + 0x016C )
#define REG_CENTRAL_PIN_SD2_DUMMY          ( CTL_BASE_CENTRAL_PIN + 0x0170 )
#define REG_CENTRAL_PIN_SIMCLK0            ( CTL_BASE_CENTRAL_PIN + 0x0174 )
#define REG_CENTRAL_PIN_SIMDA0             ( CTL_BASE_CENTRAL_PIN + 0x0178 )
#define REG_CENTRAL_PIN_SIMRST0            ( CTL_BASE_CENTRAL_PIN + 0x017C )
#define REG_CENTRAL_PIN_SIMCLK1            ( CTL_BASE_CENTRAL_PIN + 0x0180 )
#define REG_CENTRAL_PIN_SIMDA1             ( CTL_BASE_CENTRAL_PIN + 0x0184 )
#define REG_CENTRAL_PIN_SIMRST1            ( CTL_BASE_CENTRAL_PIN + 0x0188 )
#define REG_CENTRAL_PIN_SIMCLK2            ( CTL_BASE_CENTRAL_PIN + 0x018C )
#define REG_CENTRAL_PIN_SIMDA2             ( CTL_BASE_CENTRAL_PIN + 0x0190 )
#define REG_CENTRAL_PIN_SIMRST2            ( CTL_BASE_CENTRAL_PIN + 0x0194 )
#define REG_CENTRAL_PIN_KEYOUT0            ( CTL_BASE_CENTRAL_PIN + 0x0198 )
#define REG_CENTRAL_PIN_KEYOUT1            ( CTL_BASE_CENTRAL_PIN + 0x019C )
#define REG_CENTRAL_PIN_KEYOUT2            ( CTL_BASE_CENTRAL_PIN + 0x01A0 )
#define REG_CENTRAL_PIN_KEYIN0             ( CTL_BASE_CENTRAL_PIN + 0x01A4 )
#define REG_CENTRAL_PIN_KEYIN1             ( CTL_BASE_CENTRAL_PIN + 0x01A8 )
#define REG_CENTRAL_PIN_KEYIN2             ( CTL_BASE_CENTRAL_PIN + 0x01AC )
#define REG_CENTRAL_PIN_RFFE0_SCK          ( CTL_BASE_CENTRAL_PIN + 0x01B0 )
#define REG_CENTRAL_PIN_RFFE0_SDA          ( CTL_BASE_CENTRAL_PIN + 0x01B4 )
#define REG_CENTRAL_PIN_RFCTL0             ( CTL_BASE_CENTRAL_PIN + 0x01B8 )
#define REG_CENTRAL_PIN_RFCTL1             ( CTL_BASE_CENTRAL_PIN + 0x01BC )
#define REG_CENTRAL_PIN_RFCTL2             ( CTL_BASE_CENTRAL_PIN + 0x01C0 )
#define REG_CENTRAL_PIN_RFCTL3             ( CTL_BASE_CENTRAL_PIN + 0x01C4 )
#define REG_CENTRAL_PIN_RFCTL4             ( CTL_BASE_CENTRAL_PIN + 0x01C8 )
#define REG_CENTRAL_PIN_RFCTL5             ( CTL_BASE_CENTRAL_PIN + 0x01CC )
#define REG_CENTRAL_PIN_RFCTL6             ( CTL_BASE_CENTRAL_PIN + 0x01D0 )
#define REG_CENTRAL_PIN_RFCTL7             ( CTL_BASE_CENTRAL_PIN + 0x01D4 )
#define REG_CENTRAL_PIN_RFCTL8             ( CTL_BASE_CENTRAL_PIN + 0x01D8 )
#define REG_CENTRAL_PIN_RFCTL9             ( CTL_BASE_CENTRAL_PIN + 0x01DC )
#define REG_CENTRAL_PIN_RFCTL10            ( CTL_BASE_CENTRAL_PIN + 0x01E0 )
#define REG_CENTRAL_PIN_RFCTL11            ( CTL_BASE_CENTRAL_PIN + 0x01E4 )
#define REG_CENTRAL_PIN_RFCTL12            ( CTL_BASE_CENTRAL_PIN + 0x01E8 )
#define REG_CENTRAL_PIN_RFCTL13            ( CTL_BASE_CENTRAL_PIN + 0x01EC )
#define REG_CENTRAL_PIN_RFCTL14            ( CTL_BASE_CENTRAL_PIN + 0x01F0 )
#define REG_CENTRAL_PIN_RFCTL15            ( CTL_BASE_CENTRAL_PIN + 0x01F4 )
#define REG_CENTRAL_PIN_RFCTL16            ( CTL_BASE_CENTRAL_PIN + 0x01F8 )
#define REG_CENTRAL_PIN_RFCTL17            ( CTL_BASE_CENTRAL_PIN + 0x01FC )
#define REG_CENTRAL_PIN_RFCTL18            ( CTL_BASE_CENTRAL_PIN + 0x0200 )
#define REG_CENTRAL_PIN_RFCTL19            ( CTL_BASE_CENTRAL_PIN + 0x0204 )
#define REG_CENTRAL_PIN_RFSDA0             ( CTL_BASE_CENTRAL_PIN + 0x0208 )
#define REG_CENTRAL_PIN_RFSCK0             ( CTL_BASE_CENTRAL_PIN + 0x020C )
#define REG_CENTRAL_PIN_RFSEN0             ( CTL_BASE_CENTRAL_PIN + 0x0210 )
#define REG_CENTRAL_PIN_LVDS0_ADC_ON    ( CTL_BASE_CENTRAL_PIN + 0x0214 )
#define REG_CENTRAL_PIN_LVDS0_DAC_ON    ( CTL_BASE_CENTRAL_PIN + 0x0218 )
#define REG_CENTRAL_PIN_SPI2_CSN           ( CTL_BASE_CENTRAL_PIN + 0x021C )
#define REG_CENTRAL_PIN_SPI2_DO            ( CTL_BASE_CENTRAL_PIN + 0x0220 )
#define REG_CENTRAL_PIN_SPI2_DI            ( CTL_BASE_CENTRAL_PIN + 0x0224 )
#define REG_CENTRAL_PIN_SPI2_CLK           ( CTL_BASE_CENTRAL_PIN + 0x0228 )
#define REG_CENTRAL_PIN_SPI0_CSN           ( CTL_BASE_CENTRAL_PIN + 0x022C )
#define REG_CENTRAL_PIN_SPI0_DO            ( CTL_BASE_CENTRAL_PIN + 0x0230 )
#define REG_CENTRAL_PIN_SPI0_DI            ( CTL_BASE_CENTRAL_PIN + 0x0234 )
#define REG_CENTRAL_PIN_SPI0_CLK           ( CTL_BASE_CENTRAL_PIN + 0x0238 )
#define REG_CENTRAL_PIN_DTDO_LTE           ( CTL_BASE_CENTRAL_PIN + 0x023C )
#define REG_CENTRAL_PIN_DTDI_LTE           ( CTL_BASE_CENTRAL_PIN + 0x0240 )
#define REG_CENTRAL_PIN_DTCK_LTE           ( CTL_BASE_CENTRAL_PIN + 0x0244 )
#define REG_CENTRAL_PIN_DTMS_LTE           ( CTL_BASE_CENTRAL_PIN + 0x0248 )
#define REG_CENTRAL_PIN_DRTCK_LTE          ( CTL_BASE_CENTRAL_PIN + 0x024C )
#define REG_CENTRAL_PIN_MTCK_ARM           ( CTL_BASE_CENTRAL_PIN + 0x0250 )
#define REG_CENTRAL_PIN_MTMS_ARM           ( CTL_BASE_CENTRAL_PIN + 0x0254 )
#define REG_CENTRAL_PIN_MEMS_MIC_CLK0      ( CTL_BASE_CENTRAL_PIN + 0x0258 )
#define REG_CENTRAL_PIN_MEMS_MIC_DATA0     ( CTL_BASE_CENTRAL_PIN + 0x025C )
#define REG_CENTRAL_PIN_MEMS_MIC_CLK1      ( CTL_BASE_CENTRAL_PIN + 0x0260 )
#define REG_CENTRAL_PIN_MEMS_MIC_DATA1     ( CTL_BASE_CENTRAL_PIN + 0x0264 )

/* REG_CENTRAL_PIN_PIN_CTRL_REG0 */

#define BIT_CENTRAL_PIN_PIN_CTRL_REG0_FUNC_CFG(x)  (((x) & 0xFFFFFFFF))

/* REG_CENTRAL_PIN_PIN_CTRL_REG1 */

#define BIT_CENTRAL_PIN_PIN_CTRL_REG1_FUNC_CFG(x)  (((x) & 0xFFFFFFFF))

/* REG_CENTRAL_PIN_PIN_CTRL_REG2 */

#define BIT_CENTRAL_PIN_PIN_CTRL_REG2_FUNC_CFG(x)  (((x) & 0xFFFFFFFF))

/* REG_CENTRAL_PIN_PIN_CTRL_REG3 */

#define BIT_CENTRAL_PIN_PIN_CTRL_REG3_FUNC_CFG(x)  (((x) & 0xFFFFFFFF))

/* REG_CENTRAL_PIN_PIN_CTRL_REG4 */

#define BIT_CENTRAL_PIN_PIN_CTRL_REG4_FUNC_CFG(x)  (((x) & 0xFFFFFFFF))

/* REG_CENTRAL_PIN_PIN_CTRL_REG5 */

#define BIT_CENTRAL_PIN_PIN_CTRL_REG5_FUNC_CFG(x)  (((x) & 0xFFFFFFFF))

/* REG_CENTRAL_PIN_IIS1DI */

#define BIT_CENTRAL_PIN_IIS1DI_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_IIS1DO */

#define BIT_CENTRAL_PIN_IIS1DO_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_IIS1CLK */

#define BIT_CENTRAL_PIN_IIS1CLK_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_IIS1LRCK */

#define BIT_CENTRAL_PIN_IIS1LRCK_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SCL2 */

#define BIT_CENTRAL_PIN_SCL2_FUN_SEL(x)            (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SDA2 */

#define BIT_CENTRAL_PIN_SDA2_FUN_SEL(x)            (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_CLK_AUX0 */

#define BIT_CENTRAL_PIN_CLK_AUX0_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_T_DIG */

#define BIT_CENTRAL_PIN_T_DIG_FUN_SEL(x)           (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_GNSS_LNA_EN */

#define BIT_CENTRAL_PIN_GNSS_LNA_EN_FUN_SEL(x)     (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_EXTINT0 */

#define BIT_CENTRAL_PIN_EXTINT0_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_EXTINT1 */

#define BIT_CENTRAL_PIN_EXTINT1_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SCL3 */

#define BIT_CENTRAL_PIN_SCL3_FUN_SEL(x)            (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SDA3 */

#define BIT_CENTRAL_PIN_SDA3_FUN_SEL(x)            (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SCL0 */

#define BIT_CENTRAL_PIN_SCL0_FUN_SEL(x)            (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SDA0 */

#define BIT_CENTRAL_PIN_SDA0_FUN_SEL(x)            (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SCL1 */

#define BIT_CENTRAL_PIN_SCL1_FUN_SEL(x)            (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SDA1 */

#define BIT_CENTRAL_PIN_SDA1_FUN_SEL(x)            (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_CMPD2 */

#define BIT_CENTRAL_PIN_CMPD2_FUN_SEL(x)           (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_CMRST2 */

#define BIT_CENTRAL_PIN_CMRST2_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_CMMCLK0 */

#define BIT_CENTRAL_PIN_CMMCLK0_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_CMRST0 */

#define BIT_CENTRAL_PIN_CMRST0_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_CMPD0 */

#define BIT_CENTRAL_PIN_CMPD0_FUN_SEL(x)           (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_CMMCLK1 */

#define BIT_CENTRAL_PIN_CMMCLK1_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_CMRST1 */

#define BIT_CENTRAL_PIN_CMRST1_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_CMPD1 */

#define BIT_CENTRAL_PIN_CMPD1_FUN_SEL(x)           (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_U0TXD */

#define BIT_CENTRAL_PIN_U0TXD_FUN_SEL(x)           (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_U0RXD */

#define BIT_CENTRAL_PIN_U0RXD_FUN_SEL(x)           (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_U0CTS */

#define BIT_CENTRAL_PIN_U0CTS_FUN_SEL(x)           (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_U0RTS */

#define BIT_CENTRAL_PIN_U0RTS_FUN_SEL(x)           (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_U1TXD */

#define BIT_CENTRAL_PIN_U1TXD_FUN_SEL(x)           (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_U1RXD */

#define BIT_CENTRAL_PIN_U1RXD_FUN_SEL(x)           (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_U2TXD */

#define BIT_CENTRAL_PIN_U2TXD_FUN_SEL(x)           (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_U2RXD */

#define BIT_CENTRAL_PIN_U2RXD_FUN_SEL(x)           (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_EXTINT9 */

#define BIT_CENTRAL_PIN_EXTINT9_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_EXTINT10 */

#define BIT_CENTRAL_PIN_EXTINT10_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_EMMC_D2 */

#define BIT_CENTRAL_PIN_EMMC_D2_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_EMMC_D5 */

#define BIT_CENTRAL_PIN_EMMC_D5_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_EMMC_D1 */

#define BIT_CENTRAL_PIN_EMMC_D1_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_EMMC_D4 */

#define BIT_CENTRAL_PIN_EMMC_D4_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_EMMC_DUMMY */

#define BIT_CENTRAL_PIN_EMMC_DUMMY_FUN_SEL(x)      (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_EMMC_DS */

#define BIT_CENTRAL_PIN_EMMC_DS_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_EMMC_CLK */

#define BIT_CENTRAL_PIN_EMMC_CLK_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_EMMC_D6 */

#define BIT_CENTRAL_PIN_EMMC_D6_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_EMMC_D3 */

#define BIT_CENTRAL_PIN_EMMC_D3_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_EMMC_D0 */

#define BIT_CENTRAL_PIN_EMMC_D0_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_EMMC_CMD */

#define BIT_CENTRAL_PIN_EMMC_CMD_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_EMMC_D7 */

#define BIT_CENTRAL_PIN_EMMC_D7_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_EMMC_RST */

#define BIT_CENTRAL_PIN_EMMC_RST_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_NF_DATA_2 */

#define BIT_CENTRAL_PIN_NF_DATA_2_FUN_SEL(x)       (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_NF_DATA_0 */

#define BIT_CENTRAL_PIN_NF_DATA_0_FUN_SEL(x)       (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_NF_DATA_1 */

#define BIT_CENTRAL_PIN_NF_DATA_1_FUN_SEL(x)       (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_NF_WEN */

#define BIT_CENTRAL_PIN_NF_WEN_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_NF_CEN0 */

#define BIT_CENTRAL_PIN_NF_CEN0_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_LCM_RSTN */

#define BIT_CENTRAL_PIN_LCM_RSTN_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_DSI_TE */

#define BIT_CENTRAL_PIN_DSI_TE_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_PTEST */

#define BIT_CENTRAL_PIN_PTEST_FUN_SEL(x)           (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_ANA_INT */

#define BIT_CENTRAL_PIN_ANA_INT_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_EXT_RST_B */

#define BIT_CENTRAL_PIN_EXT_RST_B_FUN_SEL(x)       (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_CHIP_SLEEP */

#define BIT_CENTRAL_PIN_CHIP_SLEEP_FUN_SEL(x)      (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_XTL_BUF_EN0 */

#define BIT_CENTRAL_PIN_XTL_BUF_EN0_FUN_SEL(x)     (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_XTL_BUF_EN1 */

#define BIT_CENTRAL_PIN_XTL_BUF_EN1_FUN_SEL(x)     (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_CLK_32K */

#define BIT_CENTRAL_PIN_CLK_32K_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_AUD_SCLK */

#define BIT_CENTRAL_PIN_AUD_SCLK_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_AUD_ADD0 */

#define BIT_CENTRAL_PIN_AUD_ADD0_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_AUD_ADSYNC */

#define BIT_CENTRAL_PIN_AUD_ADSYNC_FUN_SEL(x)      (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_AUD_DAD1 */

#define BIT_CENTRAL_PIN_AUD_DAD1_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_AUD_DAD0 */

#define BIT_CENTRAL_PIN_AUD_DAD0_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_AUD_DASYNC */

#define BIT_CENTRAL_PIN_AUD_DASYNC_FUN_SEL(x)      (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_ADI_D */

#define BIT_CENTRAL_PIN_ADI_D_FUN_SEL(x)           (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_ADI_SYNC */

#define BIT_CENTRAL_PIN_ADI_SYNC_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_ADI_SCLK */

#define BIT_CENTRAL_PIN_ADI_SCLK_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SD0_D3 */

#define BIT_CENTRAL_PIN_SD0_D3_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SD0_D2 */

#define BIT_CENTRAL_PIN_SD0_D2_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SD0_CMD */

#define BIT_CENTRAL_PIN_SD0_CMD_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SD0_D0 */

#define BIT_CENTRAL_PIN_SD0_D0_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SD0_D1 */

#define BIT_CENTRAL_PIN_SD0_D1_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SD0_CLK0 */

#define BIT_CENTRAL_PIN_SD0_CLK0_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SD0_DUMMY */

#define BIT_CENTRAL_PIN_SD0_DUMMY_FUN_SEL(x)       (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SD2_CLK */

#define BIT_CENTRAL_PIN_SD2_CLK_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SD2_CMD */

#define BIT_CENTRAL_PIN_SD2_CMD_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SD2_D0 */

#define BIT_CENTRAL_PIN_SD2_D0_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SD2_D1 */

#define BIT_CENTRAL_PIN_SD2_D1_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SD2_D2 */

#define BIT_CENTRAL_PIN_SD2_D2_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SD2_D3 */

#define BIT_CENTRAL_PIN_SD2_D3_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SD2_DUMMY */

#define BIT_CENTRAL_PIN_SD2_DUMMY_FUN_SEL(x)       (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SIMCLK0 */

#define BIT_CENTRAL_PIN_SIMCLK0_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SIMDA0 */

#define BIT_CENTRAL_PIN_SIMDA0_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SIMRST0 */

#define BIT_CENTRAL_PIN_SIMRST0_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SIMCLK1 */

#define BIT_CENTRAL_PIN_SIMCLK1_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SIMDA1 */

#define BIT_CENTRAL_PIN_SIMDA1_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SIMRST1 */

#define BIT_CENTRAL_PIN_SIMRST1_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SIMCLK2 */

#define BIT_CENTRAL_PIN_SIMCLK2_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SIMDA2 */

#define BIT_CENTRAL_PIN_SIMDA2_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SIMRST2 */

#define BIT_CENTRAL_PIN_SIMRST2_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_KEYOUT0 */

#define BIT_CENTRAL_PIN_KEYOUT0_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_KEYOUT1 */

#define BIT_CENTRAL_PIN_KEYOUT1_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_KEYOUT2 */

#define BIT_CENTRAL_PIN_KEYOUT2_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_KEYIN0 */

#define BIT_CENTRAL_PIN_KEYIN0_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_KEYIN1 */

#define BIT_CENTRAL_PIN_KEYIN1_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_KEYIN2 */

#define BIT_CENTRAL_PIN_KEYIN2_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFFE0_SCK */

#define BIT_CENTRAL_PIN_RFFE0_SCK_FUN_SEL(x)       (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFFE0_SDA */

#define BIT_CENTRAL_PIN_RFFE0_SDA_FUN_SEL(x)       (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL0 */

#define BIT_CENTRAL_PIN_RFCTL0_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL1 */

#define BIT_CENTRAL_PIN_RFCTL1_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL2 */

#define BIT_CENTRAL_PIN_RFCTL2_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL3 */

#define BIT_CENTRAL_PIN_RFCTL3_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL4 */

#define BIT_CENTRAL_PIN_RFCTL4_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL5 */

#define BIT_CENTRAL_PIN_RFCTL5_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL6 */

#define BIT_CENTRAL_PIN_RFCTL6_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL7 */

#define BIT_CENTRAL_PIN_RFCTL7_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL8 */

#define BIT_CENTRAL_PIN_RFCTL8_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL9 */

#define BIT_CENTRAL_PIN_RFCTL9_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL10 */

#define BIT_CENTRAL_PIN_RFCTL10_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL11 */

#define BIT_CENTRAL_PIN_RFCTL11_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL12 */

#define BIT_CENTRAL_PIN_RFCTL12_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL13 */

#define BIT_CENTRAL_PIN_RFCTL13_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL14 */

#define BIT_CENTRAL_PIN_RFCTL14_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL15 */

#define BIT_CENTRAL_PIN_RFCTL15_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL16 */

#define BIT_CENTRAL_PIN_RFCTL16_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL17 */

#define BIT_CENTRAL_PIN_RFCTL17_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL18 */

#define BIT_CENTRAL_PIN_RFCTL18_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFCTL19 */

#define BIT_CENTRAL_PIN_RFCTL19_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFSDA0 */

#define BIT_CENTRAL_PIN_RFSDA0_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFSCK0 */

#define BIT_CENTRAL_PIN_RFSCK0_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RFSEN0 */

#define BIT_CENTRAL_PIN_RFSEN0_FUN_SEL(x)          (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RF_LVDS0_ADC_ON */

#define BIT_CENTRAL_PIN_LVDS0_ADC_ON_FUN_SEL(x)    (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_RF_LVDS0_DAC_ON */

#define BIT_CENTRAL_PIN_LVDS0_DAC_ON_FUN_SEL(x)    (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SPI2_CSN */

#define BIT_CENTRAL_PIN_SPI2_CSN_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SPI2_DO */

#define BIT_CENTRAL_PIN_SPI2_DO_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SPI2_DI */

#define BIT_CENTRAL_PIN_SPI2_DI_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SPI2_CLK */

#define BIT_CENTRAL_PIN_SPI2_CLK_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SPI0_CSN */

#define BIT_CENTRAL_PIN_SPI0_CSN_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SPI0_DO */

#define BIT_CENTRAL_PIN_SPI0_DO_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SPI0_DI */

#define BIT_CENTRAL_PIN_SPI0_DI_FUN_SEL(x)         (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_SPI0_CLK */

#define BIT_CENTRAL_PIN_SPI0_CLK_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_DTDO_LTE */

#define BIT_CENTRAL_PIN_DTDO_LTE_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_DTDI_LTE */

#define BIT_CENTRAL_PIN_DTDI_LTE_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_DTCK_LTE */

#define BIT_CENTRAL_PIN_DTCK_LTE_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_DTMS_LTE */

#define BIT_CENTRAL_PIN_DTMS_LTE_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_DRTCK_LTE */

#define BIT_CENTRAL_PIN_DRTCK_LTE_FUN_SEL(x)       (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_MTCK_ARM */

#define BIT_CENTRAL_PIN_MTCK_ARM_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_MTMS_ARM */

#define BIT_CENTRAL_PIN_MTMS_ARM_FUN_SEL(x)        (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_MEMS_MIC_CLK0 */

#define BIT_CENTRAL_PIN_MEMS_MIC_CLK0_FUN_SEL(x)   (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_MEMS_MIC_DATA0 */

#define BIT_CENTRAL_PIN_MEMS_MIC_DATA0_FUN_SEL(x)  (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_MEMS_MIC_CLK1 */

#define BIT_CENTRAL_PIN_MEMS_MIC_CLK1_FUN_SEL(x)   (((x) & 0x3) << 4)

/* REG_CENTRAL_PIN_MEMS_MIC_DATA1 */

#define BIT_CENTRAL_PIN_MEMS_MIC_DATA1_FUN_SEL(x)  (((x) & 0x3) << 4)


#endif /* CENTRAL_PIN_H */


