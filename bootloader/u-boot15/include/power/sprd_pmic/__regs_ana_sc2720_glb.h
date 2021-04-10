/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 ************************************************************
 * Auto generated code from asic documentation, DO NOT EDIT *
 ************************************************************
 */

#ifndef _SC2720_GLB_H
#define _SC2720_GLB_H

#define CTL_BASE_ANA_GLB (ANA_REGS_GLB_BASE)

#define ANA_REG_GLB_CHIP_ID_LOW                 (CTL_BASE_ANA_GLB + 0x0000)
#define ANA_REG_GLB_CHIP_ID_HIGH                (CTL_BASE_ANA_GLB + 0x0004)
#define ANA_REG_GLB_MODULE_EN0                  (CTL_BASE_ANA_GLB + 0x0008)
#define ANA_REG_GLB_ARM_CLK_EN0                 (CTL_BASE_ANA_GLB + 0x000C)
#define ANA_REG_GLB_RTC_CLK_EN0                 (CTL_BASE_ANA_GLB + 0x0010)
#define ANA_REG_GLB_SOFT_RST0                   (CTL_BASE_ANA_GLB + 0x0014)
#define ANA_REG_GLB_SOFT_RST1                   (CTL_BASE_ANA_GLB + 0x0018)
#define ANA_REG_GLB_POWER_PD_SW                 (CTL_BASE_ANA_GLB + 0x001C)
#define ANA_REG_GLB_POWER_PD_HW                 (CTL_BASE_ANA_GLB + 0x0020)
#define ANA_REG_GLB_SOFT_RST_HW                 (CTL_BASE_ANA_GLB + 0x0024)
#define ANA_REG_GLB_RESERVED_REG1               (CTL_BASE_ANA_GLB + 0x0028)
#define ANA_REG_GLB_RESERVED_REG2               (CTL_BASE_ANA_GLB + 0x002C)
#define ANA_REG_GLB_RESERVED_REG3               (CTL_BASE_ANA_GLB + 0x0030)
#define ANA_REG_GLB_DCDC_CLK_REG0               (CTL_BASE_ANA_GLB + 0x0034)
#define ANA_REG_GLB_DCDC_CORE_REG0              (CTL_BASE_ANA_GLB + 0x0038)
#define ANA_REG_GLB_DCDC_CORE_REG1              (CTL_BASE_ANA_GLB + 0x003C)
#define ANA_REG_GLB_DCDC_CORE_REG2              (CTL_BASE_ANA_GLB + 0x0040)
#define ANA_REG_GLB_DCDC_CORE_VOL               (CTL_BASE_ANA_GLB + 0x0044)
#define ANA_REG_GLB_DCDC_GEN_REG0               (CTL_BASE_ANA_GLB + 0x0048)
#define ANA_REG_GLB_DCDC_GEN_REG1               (CTL_BASE_ANA_GLB + 0x004C)
#define ANA_REG_GLB_DCDC_GEN_REG2               (CTL_BASE_ANA_GLB + 0x0050)
#define ANA_REG_GLB_DCDC_GEN_VOL                (CTL_BASE_ANA_GLB + 0x0054)
#define ANA_REG_GLB_DCDC_WPA_REG0               (CTL_BASE_ANA_GLB + 0x0058)
#define ANA_REG_GLB_DCDC_WPA_REG1               (CTL_BASE_ANA_GLB + 0x005C)
#define ANA_REG_GLB_DCDC_WPA_REG2               (CTL_BASE_ANA_GLB + 0x0060)
#define ANA_REG_GLB_DCDC_WPA_VOL                (CTL_BASE_ANA_GLB + 0x0064)
#define ANA_REG_GLB_DCDC_WPA_DCM_HW             (CTL_BASE_ANA_GLB + 0x0068)
#define ANA_REG_GLB_DCDC_CH_CTRL                (CTL_BASE_ANA_GLB + 0x006C)
#define ANA_REG_GLB_RESERVED_REG6               (CTL_BASE_ANA_GLB + 0x0070)
#define ANA_REG_GLB_RESERVED_REG7               (CTL_BASE_ANA_GLB + 0x0074)
#define ANA_REG_GLB_RESERVED_REG8               (CTL_BASE_ANA_GLB + 0x0078)
#define ANA_REG_GLB_RESERVED_REG9               (CTL_BASE_ANA_GLB + 0x007C)
#define ANA_REG_GLB_RESERVED_REG10              (CTL_BASE_ANA_GLB + 0x0080)
#define ANA_REG_GLB_LDO_AVDD18_REG0             (CTL_BASE_ANA_GLB + 0x0084)
#define ANA_REG_GLB_LDO_AVDD18_REG1             (CTL_BASE_ANA_GLB + 0x0088)
#define ANA_REG_GLB_LDO_CAMIO_REG0              (CTL_BASE_ANA_GLB + 0x008C)
#define ANA_REG_GLB_LDO_CAMIO_REG1              (CTL_BASE_ANA_GLB + 0x0090)
#define ANA_REG_GLB_LDO_RF18A_REG0              (CTL_BASE_ANA_GLB + 0x0094)
#define ANA_REG_GLB_LDO_RF18A_REG1              (CTL_BASE_ANA_GLB + 0x0098)
#define ANA_REG_GLB_LDO_RF18B_REG0              (CTL_BASE_ANA_GLB + 0x009C)
#define ANA_REG_GLB_LDO_RF18B_REG1              (CTL_BASE_ANA_GLB + 0x00A0)
#define ANA_REG_GLB_LDO_CAMD_REG0               (CTL_BASE_ANA_GLB + 0x00A4)
#define ANA_REG_GLB_LDO_CAMD_REG1               (CTL_BASE_ANA_GLB + 0x00A8)
#define ANA_REG_GLB_LDO_CON_REG0                (CTL_BASE_ANA_GLB + 0x00AC)
#define ANA_REG_GLB_LDO_CON_REG1                (CTL_BASE_ANA_GLB + 0x00B0)
#define ANA_REG_GLB_LDO_MEM_REG0                (CTL_BASE_ANA_GLB + 0x00B4)
#define ANA_REG_GLB_LDO_MEM_REG1                (CTL_BASE_ANA_GLB + 0x00B8)
#define ANA_REG_GLB_LDO_SIM0_REG0               (CTL_BASE_ANA_GLB + 0x00BC)
#define ANA_REG_GLB_LDO_SIM0_PD_REG             (CTL_BASE_ANA_GLB + 0x00C0)
#define ANA_REG_GLB_LDO_SIM0_REG1               (CTL_BASE_ANA_GLB + 0x00C4)
#define ANA_REG_GLB_LDO_SIM1_REG0               (CTL_BASE_ANA_GLB + 0x00C8)
#define ANA_REG_GLB_LDO_SIM1_PD_REG             (CTL_BASE_ANA_GLB + 0x00CC)
#define ANA_REG_GLB_LDO_SIM1_REG1               (CTL_BASE_ANA_GLB + 0x00D0)
#define ANA_REG_GLB_LDO_SIM2_REG0               (CTL_BASE_ANA_GLB + 0x00D4)
#define ANA_REG_GLB_LDO_SIM2_PD_REG             (CTL_BASE_ANA_GLB + 0x00D8)
#define ANA_REG_GLB_LDO_SIM2_REG1               (CTL_BASE_ANA_GLB + 0x00DC)
#define ANA_REG_GLB_LDO_CAMA_REG0               (CTL_BASE_ANA_GLB + 0x00E0)
#define ANA_REG_GLB_LDO_CAMA_REG1               (CTL_BASE_ANA_GLB + 0x00E4)
#define ANA_REG_GLB_LDO_CAMMOT_REG0             (CTL_BASE_ANA_GLB + 0x00E8)
#define ANA_REG_GLB_LDO_CAMMOT_REG1             (CTL_BASE_ANA_GLB + 0x00EC)
#define ANA_REG_GLB_LDO_EMMCCORE_REG0           (CTL_BASE_ANA_GLB + 0x00F0)
#define ANA_REG_GLB_LDO_EMMCCORE_PD_REG         (CTL_BASE_ANA_GLB + 0x00F4)
#define ANA_REG_GLB_LDO_EMMCCORE_REG1           (CTL_BASE_ANA_GLB + 0x00F8)
#define ANA_REG_GLB_LDO_SD_REG0                 (CTL_BASE_ANA_GLB + 0x00FC)
#define ANA_REG_GLB_LDO_SD_PD_REG               (CTL_BASE_ANA_GLB + 0x0100)
#define ANA_REG_GLB_LDO_SD_REG1                 (CTL_BASE_ANA_GLB + 0x0104)
#define ANA_REG_GLB_LDO_SDIO_REG0               (CTL_BASE_ANA_GLB + 0x0108)
#define ANA_REG_GLB_LDO_SDIO_PD_REG             (CTL_BASE_ANA_GLB + 0x010C)
#define ANA_REG_GLB_LDO_SDIO_REG1               (CTL_BASE_ANA_GLB + 0x0110)
#define ANA_REG_GLB_LDO_VDD28_REG0              (CTL_BASE_ANA_GLB + 0x0114)
#define ANA_REG_GLB_LDO_VDD28_REG1              (CTL_BASE_ANA_GLB + 0x0118)
#define ANA_REG_GLB_LDO_WIFIPA_REG0             (CTL_BASE_ANA_GLB + 0x011C)
#define ANA_REG_GLB_LDO_WIFIPA_REG1             (CTL_BASE_ANA_GLB + 0x0120)
#define ANA_REG_GLB_LDO_DCXO_REG0               (CTL_BASE_ANA_GLB + 0x0124)
#define ANA_REG_GLB_LDO_DCXO_REG1               (CTL_BASE_ANA_GLB + 0x0128)
#define ANA_REG_GLB_LDO_USB_REG0                (CTL_BASE_ANA_GLB + 0x012C)
#define ANA_REG_GLB_LDO_USB_PD_REG              (CTL_BASE_ANA_GLB + 0x0130)
#define ANA_REG_GLB_LDO_USB_REG1                (CTL_BASE_ANA_GLB + 0x0134)
#define ANA_REG_GLB_RESERVED_REG17              (CTL_BASE_ANA_GLB + 0x0138)
#define ANA_REG_GLB_RESERVED_REG18              (CTL_BASE_ANA_GLB + 0x013C)
#define ANA_REG_GLB_RESERVED_REG19              (CTL_BASE_ANA_GLB + 0x0140)
#define ANA_REG_GLB_RESERVED_REG20              (CTL_BASE_ANA_GLB + 0x0144)
#define ANA_REG_GLB_LDO_TRIM_REG                (CTL_BASE_ANA_GLB + 0x0148)
#define ANA_REG_GLB_LDO_RTC_CTRL                (CTL_BASE_ANA_GLB + 0x014C)
#define ANA_REG_GLB_LDO_CH_CTRL                 (CTL_BASE_ANA_GLB + 0x0150)
#define ANA_REG_GLB_RESERVED_REG23              (CTL_BASE_ANA_GLB + 0x0154)
#define ANA_REG_GLB_RESERVED_REG24              (CTL_BASE_ANA_GLB + 0x0158)
#define ANA_REG_GLB_RESERVED_REG25              (CTL_BASE_ANA_GLB + 0x015C)
#define ANA_REG_GLB_RESERVED_REG26              (CTL_BASE_ANA_GLB + 0x0160)
#define ANA_REG_GLB_RESERVED_REG27              (CTL_BASE_ANA_GLB + 0x0164)
#define ANA_REG_GLB_SLP_CTRL                    (CTL_BASE_ANA_GLB + 0x0168)
#define ANA_REG_GLB_SLP_DCDC_PD_CTRL            (CTL_BASE_ANA_GLB + 0x016C)
#define ANA_REG_GLB_SLP_LDO_PD_CTRL0            (CTL_BASE_ANA_GLB + 0x0170)
#define ANA_REG_GLB_SLP_LDO_PD_CTRL1            (CTL_BASE_ANA_GLB + 0x0174)
#define ANA_REG_GLB_SLP_DCDC_LP_CTRL            (CTL_BASE_ANA_GLB + 0x0178)
#define ANA_REG_GLB_SLP_LDO_LP_CTRL0            (CTL_BASE_ANA_GLB + 0x017C)
#define ANA_REG_GLB_SLP_LDO_LP_CTRL1            (CTL_BASE_ANA_GLB + 0x0180)
#define ANA_REG_GLB_DCDC_CORE_SLP_CTRL0         (CTL_BASE_ANA_GLB + 0x0184)
#define ANA_REG_GLB_DCDC_CORE_SLP_CTRL1         (CTL_BASE_ANA_GLB + 0x0188)
#define ANA_REG_GLB_DCDC_XTL_EN0                (CTL_BASE_ANA_GLB + 0x018C)
#define ANA_REG_GLB_RESEVED_DCDC_XTL_EN4        (CTL_BASE_ANA_GLB + 0x0190)
#define ANA_REG_GLB_LDO_XTL_EN0                 (CTL_BASE_ANA_GLB + 0x0194)
#define ANA_REG_GLB_LDO_XTL_EN1                 (CTL_BASE_ANA_GLB + 0x0198)
#define ANA_REG_GLB_LDO_XTL_EN2                 (CTL_BASE_ANA_GLB + 0x019C)
#define ANA_REG_GLB_LDO_XTL_EN3                 (CTL_BASE_ANA_GLB + 0x01A0)
#define ANA_REG_GLB_LDO_XTL_EN4                 (CTL_BASE_ANA_GLB + 0x01A4)
#define ANA_REG_GLB_LDO_XTL_EN5                 (CTL_BASE_ANA_GLB + 0x01A8)
#define ANA_REG_GLB_LDO_XTL_EN6                 (CTL_BASE_ANA_GLB + 0x01AC)
#define ANA_REG_GLB_LDO_XTL_EN7                 (CTL_BASE_ANA_GLB + 0x01B0)
#define ANA_REG_GLB_LDO_XTL_EN8                 (CTL_BASE_ANA_GLB + 0x01B4)
#define ANA_REG_GLB_LDO_XTL_EN9                 (CTL_BASE_ANA_GLB + 0x01B8)
#define ANA_REG_GLB_LDO_XTL_EN10                (CTL_BASE_ANA_GLB + 0x01BC)
#define ANA_REG_GLB_RESERVED_REG30              (CTL_BASE_ANA_GLB + 0x01C0)
#define ANA_REG_GLB_RESERVED_REG31              (CTL_BASE_ANA_GLB + 0x01C4)
#define ANA_REG_GLB_RESERVED_REG32              (CTL_BASE_ANA_GLB + 0x01C8)
#define ANA_REG_GLB_RESERVED_REG_CORE           (CTL_BASE_ANA_GLB + 0x01CC)
#define ANA_REG_GLB_RESERVED_REG_RTC            (CTL_BASE_ANA_GLB + 0x01D0)
#define ANA_REG_GLB_BG_CTRL                     (CTL_BASE_ANA_GLB + 0x01D4)
#define ANA_REG_GLB_DCDC_VLG_SEL                (CTL_BASE_ANA_GLB + 0x01D8)
#define ANA_REG_GLB_LDO_VLG_SEL0                (CTL_BASE_ANA_GLB + 0x01DC)
#define ANA_REG_GLB_CLK32KLESS_CTRL0            (CTL_BASE_ANA_GLB + 0x01E0)
#define ANA_REG_GLB_CLK32KLESS_CTRL1            (CTL_BASE_ANA_GLB + 0x01E4)
#define ANA_REG_GLB_XTL_WAIT_CTRL0              (CTL_BASE_ANA_GLB + 0x01E8)
#define ANA_REG_GLB_RGB_CTRL                    (CTL_BASE_ANA_GLB + 0x01EC)
#define ANA_REG_GLB_IB_CTRL                     (CTL_BASE_ANA_GLB + 0x01F0)
#define ANA_REG_GLB_FLASH_CTRL                  (CTL_BASE_ANA_GLB + 0x01F4)
#define ANA_REG_GLB_KPLED_CTRL0                 (CTL_BASE_ANA_GLB + 0x01F8)
#define ANA_REG_GLB_KPLED_CTRL1                 (CTL_BASE_ANA_GLB + 0x01FC)
#define ANA_REG_GLB_VIBR_CTRL0                  (CTL_BASE_ANA_GLB + 0x0200)
#define ANA_REG_GLB_VIBR_CTRL1                  (CTL_BASE_ANA_GLB + 0x0204)
#define ANA_REG_GLB_AUDIO_CTRL0                 (CTL_BASE_ANA_GLB + 0x0208)
#define ANA_REG_GLB_CHGR_CTRL0                  (CTL_BASE_ANA_GLB + 0x020C)
#define ANA_REG_GLB_CHGR_CTRL1                  (CTL_BASE_ANA_GLB + 0x0210)
#define ANA_REG_GLB_CHGR_STATUS                 (CTL_BASE_ANA_GLB + 0x0214)
#define ANA_REG_GLB_CHGR_DET_FGU_CTRL           (CTL_BASE_ANA_GLB + 0x0218)
#define ANA_REG_GLB_OVLO_CTRL                   (CTL_BASE_ANA_GLB + 0x021C)
#define ANA_REG_GLB_MIXED_CTRL                  (CTL_BASE_ANA_GLB + 0x0220)
#define ANA_REG_GLB_POR_RST_MONITOR             (CTL_BASE_ANA_GLB + 0x0224)
#define ANA_REG_GLB_WDG_RST_MONITOR             (CTL_BASE_ANA_GLB + 0x0228)
#define ANA_REG_GLB_POR_PIN_RST_MONITOR         (CTL_BASE_ANA_GLB + 0x022C)
#define ANA_REG_GLB_POR_SRC_FLAG                (CTL_BASE_ANA_GLB + 0x0230)
#define ANA_REG_GLB_POR_OFF_FLAG                (CTL_BASE_ANA_GLB + 0x0234)
#define ANA_REG_GLB_POR_7S_CTRL                 (CTL_BASE_ANA_GLB + 0x0238)
#define ANA_REG_GLB_HWRST_RTC                   (CTL_BASE_ANA_GLB + 0x023C)
#define ANA_REG_GLB_ARCH_EN                     (CTL_BASE_ANA_GLB + 0x0240)
#define ANA_REG_GLB_MCU_WR_PROT_VALUE           (CTL_BASE_ANA_GLB + 0x0244)
#define ANA_REG_GLB_PWR_WR_PROT_VALUE           (CTL_BASE_ANA_GLB + 0x0248)
#define ANA_REG_GLB_SMPL_CTRL0                  (CTL_BASE_ANA_GLB + 0x024C)
#define ANA_REG_GLB_SMPL_CTRL1                  (CTL_BASE_ANA_GLB + 0x0250)
#define ANA_REG_GLB_RTC_RST0                    (CTL_BASE_ANA_GLB + 0x0254)
#define ANA_REG_GLB_RTC_RST1                    (CTL_BASE_ANA_GLB + 0x0258)
#define ANA_REG_GLB_RTC_RST2                    (CTL_BASE_ANA_GLB + 0x025C)
#define ANA_REG_GLB_RTC_CLK_STOP                (CTL_BASE_ANA_GLB + 0x0260)
#define ANA_REG_GLB_VBAT_DROP_CNT               (CTL_BASE_ANA_GLB + 0x0264)
#define ANA_REG_GLB_SWRST_CTRL0                 (CTL_BASE_ANA_GLB + 0x0268)
#define ANA_REG_GLB_SWRST_CTRL1                 (CTL_BASE_ANA_GLB + 0x026C)
#define ANA_REG_GLB_OTP_CTRL                    (CTL_BASE_ANA_GLB + 0x0270)
#define ANA_REG_GLB_FREE_TIMER_LOW              (CTL_BASE_ANA_GLB + 0x0274)
#define ANA_REG_GLB_FREE_TIMER_HIGH             (CTL_BASE_ANA_GLB + 0x0278)
#define ANA_REG_GLB_VOL_TUNE_CTRL_CORE          (CTL_BASE_ANA_GLB + 0x027C)

#define ANA_REG_GLB_ARM_MODULE_EN	        ANA_REG_GLB_MODULE_EN0
#define ANA_REG_GLB_ARM_CLK_EN		        ANA_REG_GLB_ARM_CLK_EN0
#define ANA_REG_GLB_RTC_CLK_EN		        ANA_REG_GLB_RTC_CLK_EN0
#define ANA_REG_GLB_XTL_WAIT_CTRL		ANA_REG_GLB_XTL_WAIT_CTRL0

/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_CHIP_ID_LOW
//Register Offset        :   0x0000
//Register Description   :
-----------------------------------------------------------*/

#define BITS_CHIP_ID_LOW(x)                     (((x) & 0xFFFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_CHIP_ID_HIGH
//Register Offset        :   0x0004
//Register Description   :
-----------------------------------------------------------*/

#define BITS_CHIP_ID_HIGH(x)                    (((x) & 0xFFFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_MODULE_EN0
//Register Offset        :   0x0008
//Register Description   :
-----------------------------------------------------------*/

#define BIT_TYPEC_EN                            BIT(14)
#define BIT_TMR_EN                              BIT(12)
#define BIT_BLTC_EN                             BIT(9)
#define BIT_PINREG_EN                           BIT(8)
#define BIT_FGU_EN                              BIT(7)
#define BIT_EFS_EN                              BIT(6)
#define BIT_ADC_EN                              BIT(5)
#define BIT_AUD_EN                              BIT(4)
#define BIT_EIC_EN                              BIT(3)
#define BIT_WDG_EN                              BIT(2)
#define BIT_RTC_EN                              BIT(1)
#define BIT_CAL_EN                              BIT(0)

#define BIT_ANA_BLTC_EN                  BIT_BLTC_EN
#define BIT_ANA_PINREG_EN                BIT_PINREG_EN
#define BIT_ANA_FGU_EN                   BIT_FGU_EN
#define BIT_ANA_EFS_EN                   BIT_EFS_EN
#define BIT_ANA_ADC_EN                   BIT_ADC_EN
#define BIT_ANA_AUD_EN                   BIT_AUD_EN
#define BIT_ANA_EIC_EN                   BIT_EIC_EN
#define BIT_ANA_WDG_EN                   BIT_WDG_EN
#define BIT_ANA_RTC_EN                   BIT_RTC_EN
#define BIT_ANA_CAL_EN                   BIT_CAL_EN

/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_ARM_CLK_EN0
//Register Offset        :   0x000C
//Register Description   :
-----------------------------------------------------------*/

#define BIT_CLK_AUXAD_EN                        BIT(6)
#define BIT_CLK_AUXADC_EN                       BIT(5)
#define BITS_CLK_CAL_SRC_SEL(x)                 (((x) & 0x3) << 3)
#define BIT_CLK_CAL_EN                          BIT(2)
#define BIT_CLK_AUD_IF_6P5M_EN                  BIT(1)
#define BIT_CLK_AUD_IF_EN                       BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RTC_CLK_EN0
//Register Offset        :   0x0010
//Register Description   :
-----------------------------------------------------------*/

#define BIT_RTC_TYPEC_EN                        BIT(15)
#define BIT_RTC_TMR_EN                          BIT(13)
#define BIT_RTC_FLASH_EN                        BIT(12)
#define BIT_RTC_EFS_EN                          BIT(11)
#define BIT_RTC_BLTC_EN                         BIT(7)
#define BIT_RTC_FGU_EN                          BIT(6)
#define BIT_RTC_EIC_EN                          BIT(3)
#define BIT_RTC_WDG_EN                          BIT(2)
#define BIT_RTC_RTC_EN                          BIT(1)
#define BIT_RTC_ARCH_EN                         BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_SOFT_RST0
//Register Offset        :   0x0014
//Register Description   :
-----------------------------------------------------------*/

#define BIT_AUDRX_SOFT_RST                      BIT(13)
#define BIT_AUDTX_SOFT_RST                      BIT(12)
#define BIT_BLTC_SOFT_RST                       BIT(9)
#define BIT_AUD_IF_SOFT_RST                     BIT(8)
#define BIT_EFS_SOFT_RST                        BIT(7)
#define BIT_ADC_SOFT_RST                        BIT(6)
#define BIT_FGU_SOFT_RST                        BIT(4)
#define BIT_EIC_SOFT_RST                        BIT(3)
#define BIT_WDG_SOFT_RST                        BIT(2)
#define BIT_RTC_SOFT_RST                        BIT(1)
#define BIT_CAL_SOFT_RST                        BIT(0)

#define BIT_ANA_AUDTX_SOFT_RST           BIT_AUDTX_SOFT_RST
#define BIT_ANA_AUDRX_SOFT_RST           BIT_AUDRX_SOFT_RST
#define BIT_ANA_EFS_SOFT_RST             BIT_EFS_SOFT_RST
#define BIT_ANA_ADC_SOFT_RST             BIT_ADC_SOFT_RST
#define BIT_ANA_FGU_SOFT_RST             BIT_FGU_SOFT_RST
#define BIT_ANA_EIC_SOFT_RST             BIT_EIC_SOFT_RST
#define BIT_ANA_WDG_SOFT_RST             BIT_WDG_SOFT_RST
#define BIT_ANA_RTC_SOFT_RST             BIT_RTC_SOFT_RST
#define BIT_ANA_CAL_SOFT_RST             BIT_CAL_SOFT_RST

/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_SOFT_RST1
//Register Offset        :   0x0018
//Register Description   :
-----------------------------------------------------------*/

#define BIT_TYPEC_SOFT_RST                      BIT(3)
#define BIT_TMR_SOFT_RST                        BIT(1)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_POWER_PD_SW
//Register Offset        :   0x001C
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_DCXO_PD                         BIT(10)
#define BIT_LDO_EMM_PD                          BIT(9)
#define BIT_LDO_CP_PD                           BIT(8)
#define BIT_DCDC_GEN_PD                         BIT(7)
#define BIT_DCDC_CORE_PD                        BIT(5)
#define BIT_OSC3M_EN                            BIT(4)
#define BIT_LDO_MEM_PD                          BIT(3)
#define BIT_LDO_AVDD18_PD                       BIT(2)
#define BIT_LDO_VDD28_PD                        BIT(1)
#define BIT_BG_PD                               BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_POWER_PD_HW
//Register Offset        :   0x0020
//Register Description   :
-----------------------------------------------------------*/

#define BIT_PWR_OFF_SEQ_EN                      BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_SOFT_RST_HW
//Register Offset        :   0x0024
//Register Description   :
-----------------------------------------------------------*/

#define BIT_REG_SOFT_RST                        BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG1
//Register Offset        :   0x0028
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG2
//Register Offset        :   0x002C
//Register Description   :
-----------------------------------------------------------*/

/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG3
//Register Offset        :   0x0030
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_CLK_REG0
//Register Offset        :   0x0034
//Register Description   :
-----------------------------------------------------------*/

#define BIT_CLK3M_OUT_EN                        BIT(11)
#define BIT_CLKOUT_UNIPHASE                     BIT(10)
#define BITS_CLKOUT_SEL(x)                      (((x) & 0x7) << 7)
#define BIT_DCDC_GEN_CLK_RST                    BIT(4)
#define BITS_OSC3M_FREQ(x)                      (((x) & 0xF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_CORE_REG0
//Register Offset        :   0x0038
//Register Description   :
-----------------------------------------------------------*/

#define BITS_CURLIMIT_R_VCORE(x)                (((x) & 0x3) << 14)
#define BITS_CURSES_R_VCORE(x)                  (((x) & 0x3) << 12)
#define BITS_PFM_VH_VCORE(x)                    (((x) & 0x3) << 10)
#define BITS_RCOMP_VCORE(x)                     (((x) & 0x3) << 8)
#define BITS_SLOPE_VCORE(x)                     (((x) & 0x3) << 6)
#define BITS_SR_HS_VCORE(x)                     (((x) & 0x3) << 4)
#define BITS_SR_LS_VCORE(x)                     (((x) & 0x3) << 2)
#define BITS_ZX_OFFSET_VCORE(x)                 (((x) & 0x3) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_CORE_REG1
//Register Offset        :   0x003C
//Register Description   :
-----------------------------------------------------------*/

#define BITS_VOTRIM_VCORE(x)                    (((x) & 0x7) << 3)
#define BIT_ZX_DISABLE_VCORE                    BIT(2)
#define BIT_FORCE_PWM_VCORE                     BIT(1)
#define BIT_ANRITING_EN_VCORE                   BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_CORE_REG2
//Register Offset        :   0x0040
//Register Description   :
-----------------------------------------------------------*/

#define BIT_DIV_CLK_VCORE_EN                    BIT(12)
#define BITS_PHASE_SEL_VCORE(x)                 (((x) & 0x3F) << 6)
#define BITS_DIV_BASE_VCORE(x)                  (((x) & 0x3F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_CORE_VOL
//Register Offset        :   0x0044
//Register Description   :
-----------------------------------------------------------*/

#define BITS_VOSEL_VCORE(x)                     (((x) & 0x1FF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_GEN_REG0
//Register Offset        :   0x0048
//Register Description   :
-----------------------------------------------------------*/

#define BITS_CURLIMIT_R_VGEN(x)                 (((x) & 0x3) << 14)
#define BITS_CURSES_R_VGEN(x)                   (((x) & 0x3) << 12)
#define BITS_PFM_VH_VGEN(x)                     (((x) & 0x3) << 10)
#define BITS_RCOMP_VGEN(x)                      (((x) & 0x3) << 8)
#define BITS_SLOPE_VGEN(x)                      (((x) & 0x3) << 6)
#define BITS_SR_HS_VGEN(x)                      (((x) & 0x3) << 4)
#define BITS_SR_LS_VGEN(x)                      (((x) & 0x3) << 2)
#define BITS_ZX_OFFSET_VGEN(x)                  (((x) & 0x3) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_GEN_REG1
//Register Offset        :   0x004C
//Register Description   :
-----------------------------------------------------------*/

#define BIT_ZX_DISABLE_VGEN                     BIT(3)
#define BIT_MAXDUTY_SEL_VGEN                    BIT(2)
#define BIT_FORCE_PWM_VGEN                      BIT(1)
#define BIT_ANRITING_EN_VGEN                    BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_GEN_REG2
//Register Offset        :   0x0050
//Register Description   :
-----------------------------------------------------------*/

#define BIT_DIV_CLK_VGEN_EN                     BIT(12)
#define BITS_PHASE_SEL_VGEN(x)                  (((x) & 0x3F) << 6)
#define BITS_DIV_BASE_VGEN(x)                   (((x) & 0x3F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_GEN_VOL
//Register Offset        :   0x0054
//Register Description   :
-----------------------------------------------------------*/

#define BITS_VOSEL_VGEN(x)                      (((x) & 0xFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_WPA_REG0
//Register Offset        :   0x0058
//Register Description   :
-----------------------------------------------------------*/

#define BITS_CURLIMIT_R_VPA(x)                  (((x) & 0x3) << 14)
#define BITS_CURSES_M_VPA(x)                    (((x) & 0x3) << 12)
#define BITS_CCOMP3_VPA(x)                      (((x) & 0x3) << 10)
#define BITS_PFM_THRESHOLD_VPA(x)               (((x) & 0x3) << 8)
#define BITS_RCOMP2_VPA(x)                      (((x) & 0x3) << 6)
#define BITS_RCOMP3_VPA(x)                      (((x) & 0x3) << 4)
#define BITS_SAWTOOTH_SLOPE_VPA(x)              (((x) & 0x3) << 2)
#define BITS_SR_HS_VPA(x)                       (((x) & 0x3) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_WPA_REG1
//Register Offset        :   0x005C
//Register Description   :
-----------------------------------------------------------*/

#define BITS_SR_LS_VPA(x)                       (((x) & 0x3) << 14)
#define BITS_VOTRIM_VPA(x)                      (((x) & 0x7) << 11)
#define BITS_ZX_OFFSET_VPA(x)                   (((x) & 0x3) << 9)
#define BIT_ANRITING_EN_VPA                     BIT(8)
#define BIT_APC_ENABLE_VPA                      BIT(7)
#define BIT_APC_RAMP_SEL_VPA                    BIT(6)
#define BIT_BYPASS_DISABLE_VPA                  BIT(5)
#define BIT_BYPASS_FORCEON_VPA                  BIT(4)
#define BITS_BYPASS_THRESHOLD_VPA(x)            (((x) & 0x3) << 2)
#define BIT_DVS_ON_VPA                          BIT(1)
#define BIT_MAXDUTY_SEL_VPA                     BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_WPA_REG2
//Register Offset        :   0x0060
//Register Description   :
-----------------------------------------------------------*/

#define BIT_DIV_CLK_VPA_EN                      BIT(15)
#define BITS_PHASE_SEL_VPA(x)                   (((x) & 0x3F) << 9)
#define BITS_DIV_BASE_VPA(x)                    (((x) & 0x3F) << 3)
#define BIT_ZX_DISABLE_VPA                      BIT(2)
#define BIT_SAWTOOTHCAL_RST_VPA                 BIT(1)
#define BIT_PD_BUCK_VPA                         BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_WPA_VOL
//Register Offset        :   0x0064
//Register Description   :
-----------------------------------------------------------*/

#define BITS_VOSEL_VPA(x)                       (((x) & 0x7F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_WPA_DCM_HW
//Register Offset        :   0x0068
//Register Description   :
-----------------------------------------------------------*/

#define BIT_FORCE_PWM_VPA                       BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_CH_CTRL
//Register Offset        :   0x006C
//Register Description   :
-----------------------------------------------------------*/

#define BITS_DCDC_AUXTRIM_SEL(x)                (((x) & 0x7) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG6
//Register Offset        :   0x0070
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG7
//Register Offset        :   0x0074
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG8
//Register Offset        :   0x0078
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG9
//Register Offset        :   0x007C
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG10
//Register Offset        :   0x0080
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_AVDD18_REG0
//Register Offset        :   0x0084
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_AVDD18_SHPT_PD                  BIT(6)
#define BIT_LDO_AVDD18_BP                       BIT(5)
#define BITS_LDO_AVDD18_STB(x)                  (((x) & 0x3) << 3)
#define BIT_LDO_AVDD18_SHPT_ADJ                 BIT(2)
#define BIT_LDO_AVDD18_CL_ADJ                   BIT(1)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_AVDD18_REG1
//Register Offset        :   0x0088
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_AVDD18_V(x)                    (((x) & 0x3F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_CAMIO_REG0
//Register Offset        :   0x008C
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_CAMIO_SHPT_PD                   BIT(6)
#define BIT_LDO_CAMIO_BP                        BIT(5)
#define BITS_LDO_CAMIO_STB(x)                   (((x) & 0x3) << 3)
#define BIT_LDO_CAMIO_SHPT_ADJ                  BIT(2)
#define BIT_LDO_CAMIO_CL_ADJ                    BIT(1)
#define BIT_LDO_CAMIO_PD                        BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_CAMIO_REG1
//Register Offset        :   0x0090
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_CAMIO_V(x)                     (((x) & 0x3F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_RF18A_REG0
//Register Offset        :   0x0094
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_RF18A_SHPT_PD                   BIT(6)
#define BIT_LDO_RF18A_BP                        BIT(5)
#define BITS_LDO_RF18A_STB(x)                   (((x) & 0x3) << 3)
#define BIT_LDO_RF18A_SHPT_ADJ                  BIT(2)
#define BIT_LDO_RF18A_CL_ADJ                    BIT(1)
#define BIT_LDO_RF18A_PD                        BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_RF18A_REG1
//Register Offset        :   0x0098
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_RF18A_V(x)                     (((x) & 0x3F) << 0)

/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_RF18B_REG0
//Register Offset        :   0x009C
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_RF18B_SHPT_PD                   BIT(6)
#define BIT_LDO_RF18B_BP                        BIT(5)
#define BITS_LDO_RF18B_STB(x)                   (((x) & 0x3) << 3)
#define BIT_LDO_RF18B_SHPT_ADJ                  BIT(2)
#define BIT_LDO_RF18B_CL_ADJ                    BIT(1)
#define BIT_LDO_RF18B_PD                        BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_RF18B_REG1
//Register Offset        :   0x00A0
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_RF18B_V(x)                     (((x) & 0x3F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_CAMD_REG0
//Register Offset        :   0x00A4
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_CAMD_SHPT_PD                    BIT(6)
#define BIT_LDO_CAMD_BP                         BIT(5)
#define BITS_LDO_CAMD_STB(x)                    (((x) & 0x3) << 3)
#define BIT_LDO_CAMD_SHPT_ADJ                   BIT(2)
#define BIT_LDO_CAMD_CL_ADJ                     BIT(1)
#define BIT_LDO_CAMD_PD                         BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_CAMD_REG1
//Register Offset        :   0x00A8
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_CAMD_V(x)                      (((x) & 0x3F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_CON_REG0
//Register Offset        :   0x00AC
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_CON_SHPT_PD                     BIT(6)
#define BIT_LDO_CON_BP                          BIT(5)
#define BITS_LDO_CON_STB(x)                     (((x) & 0x3) << 3)
#define BIT_LDO_CON_SHPT_ADJ                    BIT(2)
#define BIT_LDO_CON_CL_ADJ                      BIT(1)
#define BIT_LDO_CON_PD                          BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_CON_REG1
//Register Offset        :   0x00B0
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_CON_V(x)                       (((x) & 0x3F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_MEM_REG0
//Register Offset        :   0x00B4
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_MEM_SHPT_PD                     BIT(6)
#define BIT_LDO_MEM_BP                          BIT(5)
#define BITS_LDO_MEM_STB(x)                     (((x) & 0x3) << 3)
#define BIT_LDO_MEM_SHPT_ADJ                    BIT(2)
#define BIT_LDO_MEM_CL_ADJ                      BIT(1)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_MEM_REG1
//Register Offset        :   0x00B8
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_MEM_V(x)                       (((x) & 0x3F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_SIM0_REG0
//Register Offset        :   0x00BC
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_SIM0_SHPT_PD                    BIT(6)
#define BIT_LDO_SIM0_CAP_SEL                    BIT(5)
#define BITS_LDO_SIM0_STB(x)                    (((x) & 0x3) << 3)
#define BIT_LDO_SIM0_SHPT_ADJ                   BIT(2)
#define BIT_LDO_SIM0_CL_ADJ                     BIT(1)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_SIM0_PD_REG
//Register Offset        :   0x00C0
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_SIM0_PD                         BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_SIM0_REG1
//Register Offset        :   0x00C4
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_SIM0_V(x)                      (((x) & 0x7F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_SIM1_REG0
//Register Offset        :   0x00C8
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_SIM1_SHPT_PD                    BIT(6)
#define BIT_LDO_SIM1_CAP_SEL                    BIT(5)
#define BITS_LDO_SIM1_STB(x)                    (((x) & 0x3) << 3)
#define BIT_LDO_SIM1_SHPT_ADJ                   BIT(2)
#define BIT_LDO_SIM1_CL_ADJ                     BIT(1)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_SIM1_PD_REG
//Register Offset        :   0x00CC
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_SIM1_PD                         BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_SIM1_REG1
//Register Offset        :   0x00D0
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_SIM1_V(x)                      (((x) & 0x7F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_SIM2_REG0
//Register Offset        :   0x00D4
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_SIM2_SHPT_PD                    BIT(6)
#define BIT_LDO_SIM2_CAP_SEL                    BIT(5)
#define BITS_LDO_SIM2_STB(x)                    (((x) & 0x3) << 3)
#define BIT_LDO_SIM2_SHPT_ADJ                   BIT(2)
#define BIT_LDO_SIM2_CL_ADJ                     BIT(1)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_SIM2_PD_REG
//Register Offset        :   0x00D8
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_SIM2_PD                         BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_SIM2_REG1
//Register Offset        :   0x00DC
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_SIM2_V(x)                      (((x) & 0x7F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_CAMA_REG0
//Register Offset        :   0x00E0
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_CAMA_SHPT_PD                    BIT(6)
#define BIT_LDO_CAMA_CAP_SEL                    BIT(5)
#define BITS_LDO_CAMA_STB(x)                    (((x) & 0x3) << 3)
#define BIT_LDO_CAMA_SHPT_ADJ                   BIT(2)
#define BIT_LDO_CAMA_CL_ADJ                     BIT(1)
#define BIT_LDO_CAMA_PD                         BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_CAMA_REG1
//Register Offset        :   0x00E4
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_CAMA_V(x)                      (((x) & 0x7F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_CAMMOT_REG0
//Register Offset        :   0x00E8
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_CAMMOT_SHPT_PD                  BIT(6)
#define BIT_LDO_CAMMOT_CAP_SEL                  BIT(5)
#define BITS_LDO_CAMMOT_STB(x)                  (((x) & 0x3) << 3)
#define BIT_LDO_CAMMOT_SHPT_ADJ                 BIT(2)
#define BIT_LDO_CAMMOT_CL_ADJ                   BIT(1)
#define BIT_LDO_CAMMOT_PD                       BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_CAMMOT_REG1
//Register Offset        :   0x00EC
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_CAMMOT_V(x)                    (((x) & 0x7F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_EMMCCORE_REG0
//Register Offset        :   0x00F0
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_EMMCCORE_SHPT_PD                BIT(6)
#define BIT_LDO_EMMCCORE_CAP_SEL                BIT(5)
#define BITS_LDO_EMMCCORE_STB(x)                (((x) & 0x3) << 3)
#define BIT_LDO_EMMCCORE_SHPT_ADJ               BIT(2)
#define BIT_LDO_EMMCCORE_CL_ADJ                 BIT(1)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_EMMCCORE_PD_REG
//Register Offset        :   0x00F4
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_EMMCCORE_PD                     BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_EMMCCORE_REG1
//Register Offset        :   0x00F8
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_EMMCCORE_V(x)                  (((x) & 0x7F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_SD_REG0
//Register Offset        :   0x00FC
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_SDCORE_SHPT_PD                  BIT(6)
#define BIT_LDO_SDCORE_CAP_SEL                  BIT(5)
#define BITS_LDO_SDCORE_STB(x)                  (((x) & 0x3) << 3)
#define BIT_LDO_SDCORE_SHPT_ADJ                 BIT(2)
#define BIT_LDO_SDCORE_CL_ADJ                   BIT(1)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_SD_PD_REG
//Register Offset        :   0x0100
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_SDCORE_PD                       BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_SD_REG1
//Register Offset        :   0x0104
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_SDCORE_V(x)                    (((x) & 0x7F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_SDIO_REG0
//Register Offset        :   0x0108
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_SDIO_SHPT_PD                    BIT(6)
#define BIT_LDO_SDIO_CAP_SEL                    BIT(5)
#define BITS_LDO_SDIO_STB(x)                    (((x) & 0x3) << 3)
#define BIT_LDO_SDIO_SHPT_ADJ                   BIT(2)
#define BIT_LDO_SDIO_CL_ADJ                     BIT(1)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_SDIO_PD_REG
//Register Offset        :   0x010C
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_SDIO_PD                         BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_SDIO_REG1
//Register Offset        :   0x0110
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_SDIO_V(x)                      (((x) & 0x7F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_VDD28_REG0
//Register Offset        :   0x0114
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_VDD28_SHPT_PD                   BIT(6)
#define BIT_LDO_VDD28_CAP_SEL                   BIT(5)
#define BITS_LDO_VDD28_STB(x)                   (((x) & 0x3) << 3)
#define BIT_LDO_VDD28_SHPT_ADJ                  BIT(2)
#define BIT_LDO_VDD28_CL_ADJ                    BIT(1)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_VDD28_REG1
//Register Offset        :   0x0118
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_VDD28_V(x)                     (((x) & 0x7F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_WIFIPA_REG0
//Register Offset        :   0x011C
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_WIFIPA_SHPT_PD                  BIT(6)
#define BIT_LDO_WIFIPA_CAP_SEL                  BIT(5)
#define BITS_LDO_WIFIPA_STB(x)                  (((x) & 0x3) << 3)
#define BIT_LDO_WIFIPA_SHPT_ADJ                 BIT(2)
#define BIT_LDO_WIFIPA_CL_ADJ                   BIT(1)
#define BIT_LDO_WIFIPA_PD                       BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_WIFIPA_REG1
//Register Offset        :   0x0120
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_WIFIPA_V(x)                    (((x) & 0x7F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_DCXO_REG0
//Register Offset        :   0x0124
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_DCXO_TRIM(x)                   (((x) & 0x1F) << 7)
#define BIT_LDO_DCXO_SHPT_PD                    BIT(6)
#define BIT_LDO_DCXO_CAP_SEL                    BIT(5)
#define BITS_LDO_DCXO_STB(x)                    (((x) & 0x3) << 3)
#define BIT_LDO_DCXO_SHPT_ADJ                   BIT(2)
#define BIT_LDO_DCXO_CL_ADJ                     BIT(1)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_DCXO_REG1
//Register Offset        :   0x0128
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_DCXO_V(x)                      (((x) & 0x7F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_USB_REG0
//Register Offset        :   0x012C
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_USB33_SHPT_PD                   BIT(6)
#define BIT_LDO_USB33_CAP_SEL                   BIT(5)
#define BITS_LDO_USB33_STB(x)                   (((x) & 0x3) << 3)
#define BIT_LDO_USB33_SHPT_ADJ                  BIT(2)
#define BIT_LDO_USB33_CL_ADJ                    BIT(1)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_USB_PD_REG
//Register Offset        :   0x0130
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_USB33_PD                        BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_USB_REG1
//Register Offset        :   0x0134
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_USB33_V(x)                     (((x) & 0x7F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG17
//Register Offset        :   0x0138
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG18
//Register Offset        :   0x013C
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG19
//Register Offset        :   0x0140
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG20
//Register Offset        :   0x0144
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_TRIM_REG
//Register Offset        :   0x0148
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_TRIM_B(x)                      (((x) & 0x1F) << 5)
#define BITS_LDO_TRIM_A(x)                      (((x) & 0x1F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_RTC_CTRL
//Register Offset        :   0x014C
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_RTC_CAL(x)                     (((x) & 0x1F) << 4)
#define BITS_LDO_RTC_V(x)                       (((x) & 0x3) << 2)
#define BITS_VBATBK_V(x)                        (((x) & 0x3) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_CH_CTRL
//Register Offset        :   0x0150
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_CAL2(x)                        (((x) & 0x7) << 8)
#define BITS_LDO_CAL1(x)                        (((x) & 0x7) << 5)
#define BITS_LDO_CAL(x)                         (((x) & 0x7) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG23
//Register Offset        :   0x0154
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG24
//Register Offset        :   0x0158
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG25
//Register Offset        :   0x015C
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG26
//Register Offset        :   0x0160
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG27
//Register Offset        :   0x0164
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_SLP_CTRL
//Register Offset        :   0x0168
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_XTL_EN                          BIT(2)
#define BIT_SLP_IO_EN                           BIT(1)
#define BIT_SLP_LDO_PD_EN                       BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_SLP_DCDC_PD_CTRL
//Register Offset        :   0x016C
//Register Description   :
-----------------------------------------------------------*/

#define BIT_SLP_DCDCCORE_DROP_EN                BIT(3)
#define BIT_SLP_DCDCWPA_PD_EN                   BIT(2)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_SLP_LDO_PD_CTRL0
//Register Offset        :   0x0170
//Register Description   :
-----------------------------------------------------------*/

#define BIT_SLP_LDORF18A_PD_EN                  BIT(14)
#define BIT_SLP_LDORF18B_PD_EN                  BIT(13)
#define BIT_SLP_LDOEMMCCORE_PD_EN               BIT(12)
#define BIT_SLP_LDODCXO_PD_EN                   BIT(11)
#define BIT_SLP_LDOWIFIPA_PD_EN                 BIT(10)
#define BIT_SLP_LDOVDD28_PD_EN                  BIT(9)
#define BIT_SLP_LDOSDCORE_PD_EN                 BIT(8)
#define BIT_SLP_LDOSDIO_PD_EN                   BIT(7)
#define BIT_SLP_LDOUSB33_PD_EN                  BIT(6)
#define BIT_SLP_LDOCAMMOT_PD_EN                 BIT(5)
#define BIT_SLP_LDOCAMIO_PD_EN                  BIT(4)
#define BIT_SLP_LDOCAMD_PD_EN                   BIT(3)
#define BIT_SLP_LDOCAMA_PD_EN                   BIT(2)
#define BIT_SLP_LDOSIM2_PD_EN                   BIT(1)
#define BIT_SLP_LDOSIM1_PD_EN                   BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_SLP_LDO_PD_CTRL1
//Register Offset        :   0x0174
//Register Description   :
-----------------------------------------------------------*/

#define BIT_SLP_LDOCP_PD_EN                     BIT(4)
#define BIT_SLP_LDOCON_PD_EN                    BIT(3)
#define BIT_SLP_LDOSIM0_PD_EN                   BIT(2)
#define BIT_SLP_LDOAVDD18_PD_EN                 BIT(1)
#define BIT_SLP_LDOMEM_PD_EN                    BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_SLP_DCDC_LP_CTRL
//Register Offset        :   0x0178
//Register Description   :
-----------------------------------------------------------*/

#define BIT_SLP_DCDCCORE_LP_EN                  BIT(4)
#define BIT_SLP_DCDCGEN_LP_EN                   BIT(1)
#define BIT_SLP_DCDCWPA_LP_EN                   BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_SLP_LDO_LP_CTRL0
//Register Offset        :   0x017C
//Register Description   :
-----------------------------------------------------------*/

#define BIT_SLP_LDORF18A_LP_EN                  BIT(14)
#define BIT_SLP_LDORF18B_LP_EN                  BIT(13)
#define BIT_SLP_LDOEMMCCORE_LP_EN               BIT(12)
#define BIT_SLP_LDODCXO_LP_EN                   BIT(11)
#define BIT_SLP_LDOWIFIPA_LP_EN                 BIT(10)
#define BIT_SLP_LDOVDD28_LP_EN                  BIT(9)
#define BIT_SLP_LDOSDCORE_LP_EN                 BIT(8)
#define BIT_SLP_LDOSDIO_LP_EN                   BIT(7)
#define BIT_SLP_LDOUSB33_LP_EN                  BIT(6)
#define BIT_SLP_LDOCAMMOT_LP_EN                 BIT(5)
#define BIT_SLP_LDOCAMIO_LP_EN                  BIT(4)
#define BIT_SLP_LDOCAMD_LP_EN                   BIT(3)
#define BIT_SLP_LDOCAMA_LP_EN                   BIT(2)
#define BIT_SLP_LDOSIM2_LP_EN                   BIT(1)
#define BIT_SLP_LDOSIM1_LP_EN                   BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_SLP_LDO_LP_CTRL1
//Register Offset        :   0x0180
//Register Description   :
-----------------------------------------------------------*/

#define BIT_SLP_LDOCON_LP_EN                    BIT(3)
#define BIT_SLP_LDOSIM0_LP_EN                   BIT(2)
#define BIT_SLP_LDOAVDD18_LP_EN                 BIT(1)
#define BIT_SLP_LDOMEM_LP_EN                    BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_CORE_SLP_CTRL0
//Register Offset        :   0x0184
//Register Description   :
-----------------------------------------------------------*/

#define BITS_DCDC_CORE_SLP_STEP_DELAY(x)        (((x) & 0x3) << 12)
#define BITS_DCDC_CORE_SLP_STEP_NUM(x)          (((x) & 0xF) << 8)
#define BITS_DCDC_CORE_SLP_STEP_VOL(x)          (((x) & 0x1F) << 3)
#define BIT_DCDC_CORE_SLP_STEP_EN               BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_CORE_SLP_CTRL1
//Register Offset        :   0x0188
//Register Description   :
-----------------------------------------------------------*/

#define BITS_DCDC_CORE_VOSEL_DS_SW(x)           (((x) & 0x1FF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_XTL_EN0
//Register Offset        :   0x018C
//Register Description   :
-----------------------------------------------------------*/

#define BIT_DCDC_CORE_EXT_XTL0_EN               BIT(15)
#define BIT_DCDC_CORE_EXT_XTL1_EN               BIT(14)
#define BIT_DCDC_CORE_EXT_XTL2_EN               BIT(13)
#define BIT_DCDC_CORE_EXT_XTL3_EN               BIT(12)
#define BIT_DCDC_GEN_EXT_XTL0_EN                BIT(7)
#define BIT_DCDC_GEN_EXT_XTL1_EN                BIT(6)
#define BIT_DCDC_GEN_EXT_XTL2_EN                BIT(5)
#define BIT_DCDC_GEN_EXT_XTL3_EN                BIT(4)
#define BIT_DCDC_WPA_EXT_XTL0_EN                BIT(3)
#define BIT_DCDC_WPA_EXT_XTL1_EN                BIT(2)
#define BIT_DCDC_WPA_EXT_XTL2_EN                BIT(1)
#define BIT_DCDC_WPA_EXT_XTL3_EN                BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESEVED_DCDC_XTL_EN4
//Register Offset        :   0x0190
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_XTL_EN0
//Register Offset        :   0x0194
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_DCXO_EXT_XTL0_EN                BIT(15)
#define BIT_LDO_DCXO_EXT_XTL1_EN                BIT(14)
#define BIT_LDO_DCXO_EXT_XTL2_EN                BIT(13)
#define BIT_LDO_DCXO_EXT_XTL3_EN                BIT(12)
#define BIT_LDO_VDD28_EXT_XTL0_EN               BIT(3)
#define BIT_LDO_VDD28_EXT_XTL1_EN               BIT(2)
#define BIT_LDO_VDD28_EXT_XTL2_EN               BIT(1)
#define BIT_LDO_VDD28_EXT_XTL3_EN               BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_XTL_EN1
//Register Offset        :   0x0198
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_RF18A_EXT_XTL0_EN               BIT(15)
#define BIT_LDO_RF18A_EXT_XTL1_EN               BIT(14)
#define BIT_LDO_RF18A_EXT_XTL2_EN               BIT(13)
#define BIT_LDO_RF18A_EXT_XTL3_EN               BIT(12)
#define BIT_LDO_RF18B_EXT_XTL0_EN               BIT(3)
#define BIT_LDO_RF18B_EXT_XTL1_EN               BIT(2)
#define BIT_LDO_RF18B_EXT_XTL2_EN               BIT(1)
#define BIT_LDO_RF18B_EXT_XTL3_EN               BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_XTL_EN2
//Register Offset        :   0x019C
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_SIM0_EXT_XTL0_EN                BIT(15)
#define BIT_LDO_SIM0_EXT_XTL1_EN                BIT(14)
#define BIT_LDO_SIM0_EXT_XTL2_EN                BIT(13)
#define BIT_LDO_SIM0_EXT_XTL3_EN                BIT(12)
#define BIT_LDO_SIM1_EXT_XTL0_EN                BIT(3)
#define BIT_LDO_SIM1_EXT_XTL1_EN                BIT(2)
#define BIT_LDO_SIM1_EXT_XTL2_EN                BIT(1)
#define BIT_LDO_SIM1_EXT_XTL3_EN                BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_XTL_EN3
//Register Offset        :   0x01A0
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_SIM2_EXT_XTL0_EN                BIT(15)
#define BIT_LDO_SIM2_EXT_XTL1_EN                BIT(14)
#define BIT_LDO_SIM2_EXT_XTL2_EN                BIT(13)
#define BIT_LDO_SIM2_EXT_XTL3_EN                BIT(12)
#define BIT_LDO_MEM_EXT_XTL0_EN                 BIT(3)
#define BIT_LDO_MEM_EXT_XTL1_EN                 BIT(2)
#define BIT_LDO_MEM_EXT_XTL2_EN                 BIT(1)
#define BIT_LDO_MEM_EXT_XTL3_EN                 BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_XTL_EN4
//Register Offset        :   0x01A4
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_CAMMOT_EXT_XTL0_EN              BIT(15)
#define BIT_LDO_CAMMOT_EXT_XTL1_EN              BIT(14)
#define BIT_LDO_CAMMOT_EXT_XTL2_EN              BIT(13)
#define BIT_LDO_CAMMOT_EXT_XTL3_EN              BIT(12)
#define BIT_LDO_CAMIO_EXT_XTL0_EN               BIT(3)
#define BIT_LDO_CAMIO_EXT_XTL1_EN               BIT(2)
#define BIT_LDO_CAMIO_EXT_XTL2_EN               BIT(1)
#define BIT_LDO_CAMIO_EXT_XTL3_EN               BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_XTL_EN5
//Register Offset        :   0x01A8
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_CAMA_EXT_XTL0_EN                BIT(15)
#define BIT_LDO_CAMA_EXT_XTL1_EN                BIT(14)
#define BIT_LDO_CAMA_EXT_XTL2_EN                BIT(13)
#define BIT_LDO_CAMA_EXT_XTL3_EN                BIT(12)
#define BIT_LDO_CAMD_EXT_XTL0_EN                BIT(3)
#define BIT_LDO_CAMD_EXT_XTL1_EN                BIT(2)
#define BIT_LDO_CAMD_EXT_XTL2_EN                BIT(1)
#define BIT_LDO_CAMD_EXT_XTL3_EN                BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_XTL_EN6
//Register Offset        :   0x01AC
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_SDIO_EXT_XTL0_EN                BIT(15)
#define BIT_LDO_SDIO_EXT_XTL1_EN                BIT(14)
#define BIT_LDO_SDIO_EXT_XTL2_EN                BIT(13)
#define BIT_LDO_SDIO_EXT_XTL3_EN                BIT(12)
#define BIT_LDO_SDCORE_EXT_XTL0_EN              BIT(3)
#define BIT_LDO_SDCORE_EXT_XTL1_EN              BIT(2)
#define BIT_LDO_SDCORE_EXT_XTL2_EN              BIT(1)
#define BIT_LDO_SDCORE_EXT_XTL3_EN              BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_XTL_EN7
//Register Offset        :   0x01B0
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_EMMCCORE_EXT_XTL0_EN            BIT(15)
#define BIT_LDO_EMMCCORE_EXT_XTL1_EN            BIT(14)
#define BIT_LDO_EMMCCORE_EXT_XTL2_EN            BIT(13)
#define BIT_LDO_EMMCCORE_EXT_XTL3_EN            BIT(12)
#define BIT_LDO_USB33_EXT_XTL0_EN               BIT(3)
#define BIT_LDO_USB33_EXT_XTL1_EN               BIT(2)
#define BIT_LDO_USB33_EXT_XTL2_EN               BIT(1)
#define BIT_LDO_USB33_EXT_XTL3_EN               BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_XTL_EN8
//Register Offset        :   0x01B4
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_KPLED_EXT_XTL0_EN               BIT(15)
#define BIT_LDO_KPLED_EXT_XTL1_EN               BIT(14)
#define BIT_LDO_KPLED_EXT_XTL2_EN               BIT(13)
#define BIT_LDO_KPLED_EXT_XTL3_EN               BIT(12)
#define BIT_LDO_VIBR_EXT_XTL0_EN                BIT(3)
#define BIT_LDO_VIBR_EXT_XTL1_EN                BIT(2)
#define BIT_LDO_VIBR_EXT_XTL2_EN                BIT(1)
#define BIT_LDO_VIBR_EXT_XTL3_EN                BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_XTL_EN9
//Register Offset        :   0x01B8
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_CON_EXT_XTL0_EN                 BIT(15)
#define BIT_LDO_CON_EXT_XTL1_EN                 BIT(14)
#define BIT_LDO_CON_EXT_XTL2_EN                 BIT(13)
#define BIT_LDO_CON_EXT_XTL3_EN                 BIT(12)
#define BIT_LDO_AVDD18_EXT_XTL0_EN              BIT(3)
#define BIT_LDO_AVDD18_EXT_XTL1_EN              BIT(2)
#define BIT_LDO_AVDD18_EXT_XTL2_EN              BIT(1)
#define BIT_LDO_AVDD18_EXT_XTL3_EN              BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_XTL_EN10
//Register Offset        :   0x01BC
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_CP_EXT_XTL0_EN                  BIT(15)
#define BIT_LDO_CP_EXT_XTL1_EN                  BIT(14)
#define BIT_LDO_CP_EXT_XTL2_EN                  BIT(13)
#define BIT_LDO_CP_EXT_XTL3_EN                  BIT(12)
#define BIT_LDO_WIFIPA_EXT_XTL0_EN              BIT(3)
#define BIT_LDO_WIFIPA_EXT_XTL1_EN              BIT(2)
#define BIT_LDO_WIFIPA_EXT_XTL2_EN              BIT(1)
#define BIT_LDO_WIFIPA_EXT_XTL3_EN              BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG30
//Register Offset        :   0x01C0
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG31
//Register Offset        :   0x01C4
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG32
//Register Offset        :   0x01C8
//Register Description   :
-----------------------------------------------------------*/



/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG_CORE
//Register Offset        :   0x01CC
//Register Description   :
-----------------------------------------------------------*/

#define BITS_RESERVED_CORE(x)                   (((x) & 0xFFFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RESERVED_REG_RTC
//Register Offset        :   0x01D0
//Register Description   :
-----------------------------------------------------------*/

#define BITS_RESERVED_RTC(x)                    (((x) & 0xFFFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_BG_CTRL
//Register Offset        :   0x01D4
//Register Description   :
-----------------------------------------------------------*/

#define BIT_BG_CHOP_EN                          BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_DCDC_VLG_SEL
//Register Offset        :   0x01D8
//Register Description   :
-----------------------------------------------------------*/

#define BIT_DCDC_WPA_VOTRIM_SW_SEL              BIT(5)
#define BIT_DCDC_WPA_SW_SEL                     BIT(4)
#define BIT_DCDC_GEN_SW_SEL                     BIT(3)
#define BIT_DCDC_CORE_VOTRIM_SW_SEL             BIT(2)
#define BIT_DCDC_CORE_SLP_SW_SEL                BIT(1)
#define BIT_DCDC_CORE_NOR_SW_SEL                BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_LDO_VLG_SEL0
//Register Offset        :   0x01DC
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_KPLED_SW_SEL                    BIT(5)
#define BIT_LDO_VIBR_SW_SEL                     BIT(4)
#define BIT_LDO_RTC_CAL_SW_SEL                  BIT(3)
#define BIT_LDO_DCXO_SW_SEL                     BIT(2)
#define BIT_LDO_TRIM_A_SW_SEL                   BIT(1)
#define BIT_LDO_TRIM_B_SW_SEL                   BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_CLK32KLESS_CTRL0
//Register Offset        :   0x01E0
//Register Description   :
-----------------------------------------------------------*/

#define BIT_RC_MODE_WR_ACK_FLAG                 BIT(14)
#define BIT_RC_MODE_WR_ACK_FLAG_CLR             BIT(10)
#define BIT_LDO_DCXO_LP_EN_RTCSET               BIT(7)
#define BIT_LDO_DCXO_LP_EN_RTCCLR               BIT(6)
#define BIT_RTC_MODE                            BIT(4)
#define BIT_RC_32K_SEL                          BIT(1)
#define BIT_RC_32K_EN                           BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_CLK32KLESS_CTRL1
//Register Offset        :   0x01E4
//Register Description   :
-----------------------------------------------------------*/

#define BITS_RC_MODE(x)                         (((x) & 0xFFFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_XTL_WAIT_CTRL0
//Register Offset        :   0x01E8
//Register Description   :
-----------------------------------------------------------*/

#define BIT_EXT_XTL3_FOR_26M_EN                 BIT(13)
#define BIT_EXT_XTL2_FOR_26M_EN                 BIT(12)
#define BIT_EXT_XTL1_FOR_26M_EN                 BIT(11)
#define BIT_EXT_XTL0_FOR_26M_EN                 BIT(10)
#define BIT_SLP_XTLBUF_PD_EN                    BIT(9)
#define BIT_XTL_EN                              BIT(8)
#define BITS_XTL_WAIT(x)                        (((x) & 0xFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RGB_CTRL
//Register Offset        :   0x01EC
//Register Description   :
-----------------------------------------------------------*/

#define BIT_SLP_RGB_PD_EN                       BIT(2)
#define BIT_RGB_PD_HW_EN                        BIT(1)
#define BIT_RGB_PD_SW                           BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_IB_CTRL
//Register Offset        :   0x01F0
//Register Description   :
-----------------------------------------------------------*/

#define BIT_BATDET_CUR_EN                       BIT(13)
#define BITS_BATDET_CUR_I(x)                    (((x) & 0x7) << 9)
#define BITS_IB_TRIM(x)                         (((x) & 0x7F) << 2)
#define BIT_IB_TRIM_EM_SEL                      BIT(1)
#define BIT_IB_REX_EN                           BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_FLASH_CTRL
//Register Offset        :   0x01F4
//Register Description   :
-----------------------------------------------------------*/

#define BIT_FLASH_PON                           BIT(15)
#define BIT_FLASH_V_HW_EN                       BIT(6)
#define BITS_FLASH_V_HW_STEP(x)                 (((x) & 0x3) << 4)
#define BITS_FLASH_V_SW(x)                      (((x) & 0xF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_KPLED_CTRL0
//Register Offset        :   0x01F8
//Register Description   :
-----------------------------------------------------------*/

#define BITS_KPLED_V(x)                         (((x) & 0xF) << 12)
#define BIT_KPLED_PD                            BIT(11)
#define BIT_KPLED_PULLDOWN_EN                   BIT(10)
#define BIT_SLP_LDOKPLED_PD_EN                  BIT(9)
#define BIT_LDO_KPLED_CAP_SEL                   BIT(4)
#define BITS_LDO_KPLED_STB(x)                   (((x) & 0x3) << 2)
#define BIT_LDO_KPLED_SHPT_ADJ                  BIT(1)
#define BIT_LDO_KPLED_CL_ADJ                    BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_KPLED_CTRL1
//Register Offset        :   0x01FC
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_KPLED_PD                        BIT(15)
#define BITS_LDO_KPLED_V(x)                     (((x) & 0x7) << 7)
#define BITS_LDO_KPLED_REFTRIM(x)               (((x) & 0x1F) << 2)
#define BIT_LDO_KPLED_SHPT_PD                   BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_VIBR_CTRL0
//Register Offset        :   0x0200
//Register Description   :
-----------------------------------------------------------*/

#define BIT_LDO_VIBR_CAP_SEL                    BIT(15)
#define BITS_LDO_VIBR_STB(x)                    (((x) & 0x3) << 13)
#define BIT_LDO_VIBR_SHPT_ADJ                   BIT(12)
#define BIT_LDO_VIBR_CL_ADJ                     BIT(11)
#define BIT_LDO_VIBR_SHPT_PD                    BIT(10)
#define BIT_SLP_LDOVIBR_PD_EN                   BIT(9)
#define BIT_LDO_VIBR_PD                         BIT(8)
#define BITS_LDO_VIBR_V(x)                      (((x) & 0x7) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_VIBR_CTRL1
//Register Offset        :   0x0204
//Register Description   :
-----------------------------------------------------------*/

#define BITS_LDO_VIBR_REFTRIM(x)                (((x) & 0x1F) << 1)
#define BIT_LDO_VIBR_EADBIAS_EN                 BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_AUDIO_CTRL0
//Register Offset        :   0x0208
//Register Description   :
-----------------------------------------------------------*/

#define BIT_CLK_AUD_IF_TX_INV_EN                BIT(3)
#define BIT_CLK_AUD_IF_RX_INV_EN                BIT(2)
#define BIT_CLK_AUD_IF_6P5M_TX_INV_EN           BIT(1)
#define BIT_CLK_AUD_IF_6P5M_RX_INV_EN           BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_CHGR_CTRL0
//Register Offset        :   0x020C
//Register Description   :
-----------------------------------------------------------*/

#define BITS_CHGR_DPM(x)                        (((x) & 0x3) << 13)
#define BIT_CHGR_CC_EN                          BIT(12)
#define BITS_CHGR_CV_V(x)                       (((x) & 0x3F) << 5)
#define BITS_CHGR_END_V(x)                      (((x) & 0x3) << 3)
#define BITS_CHGR_ITERM(x)                      (((x) & 0x3) << 1)
#define BIT_CHGR_PD                             BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_CHGR_CTRL1
//Register Offset        :   0x0210
//Register Description   :
-----------------------------------------------------------*/

#define BIT_CHGR_EXPOWER_DEVICE                 BIT(15)
#define BITS_CHGR_CC_I(x)                       (((x) & 0xF) << 10)
#define BITS_VCHG_OVP_V(x)                      (((x) & 0x3) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_CHGR_STATUS
//Register Offset        :   0x0214
//Register Description   :
-----------------------------------------------------------*/

#define BIT_CHGR_INT_EN                         BIT(13)
#define BIT_NON_DCP_INT                         BIT(12)
#define BIT_CHG_DET_DONE                        BIT(11)
#define BIT_DP_LOW                              BIT(10)
#define BIT_DCP_DET                             BIT(9)
#define BIT_CHG_DET                             BIT(8)
#define BIT_SDP_INT                             BIT(7)
#define BIT_DCP_INT                             BIT(6)
#define BIT_CDP_INT                             BIT(5)
#define BIT_CHGR_CV_STATUS                      BIT(4)
#define BIT_CHGR_ON                             BIT(3)
#define BIT_CHGR_INT                            BIT(2)
#define BIT_DCP_SWITCH_EN                       BIT(1)
#define BIT_VCHG_OVI                            BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_CHGR_DET_FGU_CTRL
//Register Offset        :   0x0218
//Register Description   :
-----------------------------------------------------------*/

#define BIT_FGUA_SOFT_RST                       BIT(13)
#define BIT_LDO_FGU_PD                          BIT(12)
#define BITS_CHG_INT_DELAY(x)                   (((x) & 0x7) << 9)
#define BIT_SD_CHOP_CAP_EN                      BIT(8)
#define BITS_SD_CLK_P(x)                        (((x) & 0x3) << 6)
#define BIT_SD_ADC0_RC_PD                       BIT(5)
#define BIT_SD_CHOP_EN                          BIT(4)
#define BIT_SD_DCOFFSET_B_EN                    BIT(3)
#define BIT_SD_DCOFFSET_A_EN                    BIT(2)
#define BIT_DP_DM_AUX_EN                        BIT(1)
#define BIT_DP_DM_BC_ENB                        BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_OVLO_CTRL
//Register Offset        :   0x021C
//Register Description   :
-----------------------------------------------------------*/

#define BITS_VBAT_CRASH_V(x)                    (((x) & 0x3) << 10)
#define BIT_OVLO_EN                             BIT(9)
#define BITS_OVLO_V(x)                          (((x) & 0x3) << 2)
#define BITS_OVLO_T(x)                          (((x) & 0x3) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_MIXED_CTRL
//Register Offset        :   0x0220
//Register Description   :
-----------------------------------------------------------*/

#define BIT_XOSC32K_CTL                         BIT(12)
#define BITS_BATON_T(x)                         (((x) & 0x3) << 10)
#define BIT_VPP_5V_SEL                          BIT(9)
#define BIT_BATDET_OK                           BIT(8)
#define BIT_VBAT_OK                             BIT(4)
#define BIT_ALL_GPI_DEB                         BIT(3)
#define BIT_GPI_DEBUG_EN                        BIT(2)
#define BIT_ALL_INT_DEB                         BIT(1)
#define BIT_INT_DEBUG_EN                        BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_POR_RST_MONITOR
//Register Offset        :   0x0224
//Register Description   :
-----------------------------------------------------------*/

#define BITS_POR_RST_MONITOR(x)                 (((x) & 0xFFFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_WDG_RST_MONITOR
//Register Offset        :   0x0228
//Register Description   :
-----------------------------------------------------------*/

#define BITS_WDG_RST_MONITOR(x)                 (((x) & 0xFFFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_POR_PIN_RST_MONITOR
//Register Offset        :   0x022C
//Register Description   :
-----------------------------------------------------------*/

#define BITS_POR_PIN_RST_MONITOR(x)             (((x) & 0xFFFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_POR_SRC_FLAG
//Register Offset        :   0x0230
//Register Description   :
-----------------------------------------------------------*/

#define BIT_POR_SW_FORCE_ON                     BIT(15)
#define BIT_REG_SOFT_RST_FLG_CLR                BIT(14)
#define BITS_POR_SRC_FLAG(x)                    (((x) & 0x3FFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_POR_OFF_FLAG
//Register Offset        :   0x0234
//Register Description   :
-----------------------------------------------------------*/

#define BIT_POR_CHIP_PD_FLAG                    BIT(13)
#define BIT_POR_CHIP_PD_FLAG_CLR                BIT(12)
#define BIT_UVLO_CHIP_PD_FLAG                   BIT(11)
#define BIT_UVLO_CHIP_PD_FLAG_CLR               BIT(10)
#define BIT_HARD_7S_CHIP_PD_FLAG                BIT(9)
#define BIT_HARD_7S_CHIP_PD_FLAG_CLR            BIT(8)
#define BIT_SW_CHIP_PD_FLAG                     BIT(7)
#define BIT_SW_CHIP_PD_FLAG_CLR                 BIT(6)
#define BIT_HW_CHIP_PD_FLAG                     BIT(5)
#define BIT_HW_CHIP_PD_FLAG_CLR                 BIT(4)
#define BIT_OTP_CHIP_PD_FLAG                    BIT(3)
#define BIT_OTP_CHIP_PD_FLAG_CLR                BIT(2)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_POR_7S_CTRL
//Register Offset        :   0x0238
//Register Description   :
-----------------------------------------------------------*/

#define BIT_PBINT_7S_FLAG_CLR                   BIT(15)
#define BIT_EXT_RSTN_FLAG_CLR                   BIT(14)
#define BIT_CHGR_INT_FLAG_CLR                   BIT(13)
#define BIT_PBINT2_FLAG_CLR                     BIT(12)
#define BIT_PBINT_FLAG_CLR                      BIT(11)
#define BIT_KEY2_7S_RST_EN                      BIT(9)
#define BIT_PBINT_7S_RST_SWMODE                 BIT(8)
#define BITS_PBINT_7S_RST_THRESHOLD(x)          (((x) & 0xF) << 4)
#define BIT_EXT_RSTN_MODE                       BIT(3)
#define BIT_PBINT_7S_AUTO_ON_EN                 BIT(2)
#define BIT_PBINT_7S_RST_DISABLE                BIT(1)
#define BIT_PBINT_7S_RST_MODE                   BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_HWRST_RTC
//Register Offset        :   0x023C
//Register Description   :
-----------------------------------------------------------*/

#define BITS_HWRST_RTC_REG_STS(x)               (((x) & 0xFF) << 8)
#define BITS_HWRST_RTC_REG_SET(x)               (((x) & 0xFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_ARCH_EN
//Register Offset        :   0x0240
//Register Description   :
-----------------------------------------------------------*/

#define BIT_ARCH_EN                             BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_MCU_WR_PROT_VALUE
//Register Offset        :   0x0244
//Register Description   :
-----------------------------------------------------------*/

#define BIT_MCU_WR_PROT                         BIT(15)
#define BITS_MCU_WR_PROT_VALUE(x)               (((x) & 0x7FFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_PWR_WR_PROT_VALUE
//Register Offset        :   0x0248
//Register Description   :
-----------------------------------------------------------*/

#define BIT_PWR_WR_PROT                         BIT(15)
#define BITS_PWR_WR_PROT_VALUE(x)               (((x) & 0x7FFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_SMPL_CTRL0
//Register Offset        :   0x024C
//Register Description   :
-----------------------------------------------------------*/

#define BITS_SMPL_MODE(x)                       (((x) & 0xFFFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_SMPL_CTRL1
//Register Offset        :   0x0250
//Register Description   :
-----------------------------------------------------------*/

#define BIT_SMPL_PWR_ON_FLAG                    BIT(15)
#define BIT_SMPL_MODE_WR_ACK_FLAG               BIT(14)
#define BIT_SMPL_PWR_ON_FLAG_CLR                BIT(13)
#define BIT_SMPL_MODE_WR_ACK_FLAG_CLR           BIT(12)
#define BIT_SMPL_PWR_ON_SET                     BIT(11)
#define BIT_SMPL_EN                             BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RTC_RST0
//Register Offset        :   0x0254
//Register Description   :
-----------------------------------------------------------*/

#define BITS_RTC_CLK_FLAG_SET(x)                (((x) & 0xFFFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RTC_RST1
//Register Offset        :   0x0258
//Register Description   :
-----------------------------------------------------------*/

#define BITS_RTC_CLK_FLAG_CLR(x)                (((x) & 0xFFFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RTC_RST2
//Register Offset        :   0x025C
//Register Description   :
-----------------------------------------------------------*/

#define BITS_RTC_CLK_FLAG_RTC(x)                (((x) & 0xFFFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_RTC_CLK_STOP
//Register Offset        :   0x0260
//Register Description   :
-----------------------------------------------------------*/

#define BIT_RTC_CLK_STOP_FLAG                   BIT(7)
#define BITS_RTC_CLK_STOP_THRESHOLD(x)          (((x) & 0x7F) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_VBAT_DROP_CNT
//Register Offset        :   0x0264
//Register Description   :
-----------------------------------------------------------*/

#define BITS_VBAT_DROP_CNT(x)                   (((x) & 0xFFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_SWRST_CTRL0
//Register Offset        :   0x0268
//Register Description   :
-----------------------------------------------------------*/

#define BIT_EXT_RSTN_PD_EN                      BIT(10)
#define BIT_PB_7S_RST_PD_EN                     BIT(9)
#define BIT_REG_RST_PD_EN                       BIT(8)
#define BIT_WDG_RST_PD_EN                       BIT(7)
#define BIT_REG_RST_EN                          BIT(4)
#define BITS_SW_RST_PD_THRESHOLD(x)             (((x) & 0xF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_SWRST_CTRL1
//Register Offset        :   0x026C
//Register Description   :
-----------------------------------------------------------*/

#define BIT_SW_RST_DCDCGEN_PD_EN                BIT(10)
#define BIT_SW_RST_DCDCCORE_PD_EN               BIT(9)
#define BIT_SW_RST_MEM_PD_EN                    BIT(8)
#define BIT_SW_RST_DCXO_PD_EN                   BIT(7)
#define BIT_SW_RST_VDD28_PD_EN                  BIT(6)
#define BIT_SW_RST_AVDD18_PD_EN                 BIT(5)
#define BIT_SW_RST_RF18A_PD_EN                  BIT(4)
#define BIT_SW_RST_USB33_PD_EN                  BIT(3)
#define BIT_SW_RST_EMMCCORE_PD_EN               BIT(2)
#define BIT_SW_RST_SDIO_PD_EN                   BIT(1)
#define BIT_SW_RST_SDCORE_PD_EN                 BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_OTP_CTRL
//Register Offset        :   0x0270
//Register Description   :
-----------------------------------------------------------*/

#define BITS_OTP_OP(x)                          (((x) & 0x3) << 1)
#define BIT_OTP_EN                              BIT(0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_FREE_TIMER_LOW
//Register Offset        :   0x0274
//Register Description   :
-----------------------------------------------------------*/

#define BITS_TIMER_LOW(x)                       (((x) & 0xFFFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_FREE_TIMER_HIGH
//Register Offset        :   0x0278
//Register Description   :
-----------------------------------------------------------*/

#define BITS_TIMER_HIGH(x)                      (((x) & 0xFFFF) << 0)


/*-----------------------------------------------------------
//Register Name          :   ANA_REG_GLB_VOL_TUNE_CTRL_CORE
//Register Offset        :   0x027C
//Register Description   :
-----------------------------------------------------------*/

#define BIT_CORE_CLK_SEL                        BIT(14)
#define BITS_CORE_STEP_DELAY(x)                 (((x) & 0x3) << 12)
#define BITS_CORE_STEP_NUM(x)                   (((x) & 0xF) << 8)
#define BITS_CORE_STEP_VOL(x)                   (((x) & 0x1F) << 3)
#define BIT_CORE_VOL_TUNE_START                 BIT(2)
#define BIT_CORE_VOL_TUNE_FLAG                  BIT(1)
#define BIT_CORE_VOL_TUNE_EN                    BIT(0)


#endif /* _SC2720_GLB_H */