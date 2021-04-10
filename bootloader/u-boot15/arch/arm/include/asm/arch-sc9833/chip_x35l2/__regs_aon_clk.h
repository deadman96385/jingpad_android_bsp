/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _AON_CLK_REG_H
#define _AON_CLK_REG_H

#define CTL_BASE_AON_CLK SPRD_AONCKG_PHYS


#define REG_AON_CLK_CGM_EMC_4X_CFG           ( CTL_BASE_AON_CLK + 0x0020 )
#define REG_AON_CLK_CGM_EMC_2X_CFG           ( CTL_BASE_AON_CLK + 0x0024 )
#define REG_AON_CLK_CGM_EMC_1X_CFG           ( CTL_BASE_AON_CLK + 0x0028 )
#define REG_AON_CLK_CGM_PUB_AHB_CFG          ( CTL_BASE_AON_CLK + 0x002C )
#define REG_AON_CLK_CGM_AON_APB_CFG          ( CTL_BASE_AON_CLK + 0x0030 )
#define REG_AON_CLK_CGM_ADI_CFG              ( CTL_BASE_AON_CLK + 0x0034 )
#define REG_AON_CLK_CGM_AUX0_CFG             ( CTL_BASE_AON_CLK + 0x0038 )
#define REG_AON_CLK_CGM_AUX1_CFG             ( CTL_BASE_AON_CLK + 0x003C )
#define REG_AON_CLK_CGM_AUX2_CFG             ( CTL_BASE_AON_CLK + 0x0040 )
#define REG_AON_CLK_CGM_PROBE_CFG            ( CTL_BASE_AON_CLK + 0x0044 )
#define REG_AON_CLK_CGM_PWM0_CFG             ( CTL_BASE_AON_CLK + 0x0048 )
#define REG_AON_CLK_PWM0_CFG			REG_AON_CLK_CGM_PWM0_CFG
#define REG_AON_CLK_CGM_PWM1_CFG             ( CTL_BASE_AON_CLK + 0x004C )
#define REG_AON_CLK_CGM_PWM2_CFG             ( CTL_BASE_AON_CLK + 0x0050 )
#define REG_AON_CLK_CGM_PWM3_CFG             ( CTL_BASE_AON_CLK + 0x0054 )
#define REG_AON_CLK_CGM_EFUSE_CFG            ( CTL_BASE_AON_CLK + 0x0058 )
#define REG_AON_CLK_CGM_ARM7_UART_CFG        ( CTL_BASE_AON_CLK + 0x005C )
#define REG_AON_CLK_CGM_32K_CFG              ( CTL_BASE_AON_CLK + 0x0060 )
#define REG_AON_CLK_CGM_1K_CFG               ( CTL_BASE_AON_CLK + 0x0064 )
#define REG_AON_CLK_CGM_THM_CFG              ( CTL_BASE_AON_CLK + 0x0068 )
#define REG_AON_CLK_CGM_MSPI_CFG             ( CTL_BASE_AON_CLK + 0x006C )
#define REG_AON_CLK_CGM_I2C_CFG              ( CTL_BASE_AON_CLK + 0x0070 )
#define REG_AON_CLK_CGM_AVS_CFG              ( CTL_BASE_AON_CLK + 0x0074 )
#define REG_AON_CLK_CGM_AUD_CFG              ( CTL_BASE_AON_CLK + 0x0078 )
#define REG_AON_CLK_CGM_AUDIF_CFG            ( CTL_BASE_AON_CLK + 0x007C )
#define REG_AON_CLK_CGM_VBC_CFG              ( CTL_BASE_AON_CLK + 0x0080 )
#define REG_AON_CLK_CGM_AUD_IIS_DA0_CFG      ( CTL_BASE_AON_CLK + 0x0084 )
#define REG_AON_CLK_CGM_AUD_IIS0_AD0_CFG     ( CTL_BASE_AON_CLK + 0x0088 )
#define REG_AON_CLK_CGM_AUD_IIS1_AD0_CFG     ( CTL_BASE_AON_CLK + 0x008C )
#define REG_AON_CLK_CGM_CA7_DAP_CFG          ( CTL_BASE_AON_CLK + 0x0090 )
#define REG_AON_CLK_CGM_CA7_DAP_MTCK_CFG     ( CTL_BASE_AON_CLK + 0x0094 )
#define REG_AON_CLK_CGM_CA7_TS_CFG           ( CTL_BASE_AON_CLK + 0x0098 )
#define REG_AON_CLK_CGM_DAC1_CAL_CFG         ( CTL_BASE_AON_CLK + 0x009C )
#define REG_AON_CLK_CGM_DAC2_CAL_CFG         ( CTL_BASE_AON_CLK + 0x00A0 )
#define REG_AON_CLK_CGM_DAC3_CAL_CFG         ( CTL_BASE_AON_CLK + 0x00A4 )
#define REG_AON_CLK_CGM_MDAR_CHK_CFG         ( CTL_BASE_AON_CLK + 0x00A8 )
#define REG_AON_CLK_CGM_RTC4M0_REF_CFG       ( CTL_BASE_AON_CLK + 0x00AC )
#define REG_AON_CLK_CGM_RTC4M0_FDK_CFG       ( CTL_BASE_AON_CLK + 0x00B0 )
#define REG_AON_CLK_CGM_DJTAG_TCK_CFG        ( CTL_BASE_AON_CLK + 0x00B4 )
#define REG_AON_CLK_CGM_ARM7_AHB_CFG         ( CTL_BASE_AON_CLK + 0x00B8 )
#define REG_AON_CLK_CGM_CA5_TS_CFG           ( CTL_BASE_AON_CLK + 0x00BC )
#define REG_AON_CLK_CGM_FUNCDMA_CFG          ( CTL_BASE_AON_CLK + 0x00C0 )
#define REG_AON_CLK_CGM_EMC_REF_CFG          ( CTL_BASE_AON_CLK + 0x00C4 )
#define REG_AON_CLK_CGM_CSSYS_CFG            ( CTL_BASE_AON_CLK + 0x00C8 )
#define REG_AON_CLK_CGM_CSSYS_CA7_CFG        ( CTL_BASE_AON_CLK + 0x00CC )
#define REG_AON_CLK_CGM_DET_32K_CFG          ( CTL_BASE_AON_CLK + 0x00D0 )
#define REG_AON_CLK_CGM_TMR_CFG              ( CTL_BASE_AON_CLK + 0x00D4 )
#define REG_AON_CLK_CGM_SDIO0_2X_CFG         ( CTL_BASE_AON_CLK + 0x00D8 )
#define REG_AON_CLK_CGM_SDIO0_1X_CFG         ( CTL_BASE_AON_CLK + 0x00DC )
#define REG_AON_CLK_CGM_SDIO1_2X_CFG         ( CTL_BASE_AON_CLK + 0x00E0 )
#define REG_AON_CLK_CGM_SDIO1_1X_CFG         ( CTL_BASE_AON_CLK + 0x00E4 )
#define REG_AON_CLK_CGM_SDIO2_2X_CFG         ( CTL_BASE_AON_CLK + 0x00E8 )
#define REG_AON_CLK_CGM_SDIO2_1X_CFG         ( CTL_BASE_AON_CLK + 0x00EC )
#define REG_AON_CLK_CGM_EMMC_2X_CFG          ( CTL_BASE_AON_CLK + 0x00F0 )
#define REG_AON_CLK_CGM_EMMC_1X_CFG          ( CTL_BASE_AON_CLK + 0x00F4 )
#define REG_AON_CLK_CGM_WCDMA_ICI_CFG        ( CTL_BASE_AON_CLK + 0x00F8 )
#define REG_AON_CLK_CGM_WCDMA_CFG            ( CTL_BASE_AON_CLK + 0x00FC )
#define REG_AON_CLK_CGM_RFTI_TX_WD_CFG       ( CTL_BASE_AON_CLK + 0x0100 )
#define REG_AON_CLK_CGM_RFTI_RX_WD_CFG       ( CTL_BASE_AON_CLK + 0x0104 )
#define REG_AON_CLK_CGM_DSI_TEST_CFG         ( CTL_BASE_AON_CLK + 0x0108 )
#define REG_AON_CLK_CGM_AP_HS_SPI_CFG        ( CTL_BASE_AON_CLK + 0x010C )
#define REG_AON_CLK_CGM_RFTI_SBI_CFG         ( CTL_BASE_AON_CLK + 0x0110 )
#define REG_AON_CLK_CGM_RFTI1_XO_CFG         ( CTL_BASE_AON_CLK + 0x0114 )
#define REG_AON_CLK_CGM_RFTI_LTH_CFG         ( CTL_BASE_AON_CLK + 0x0118 )
#define REG_AON_CLK_CGM_RFTI2_XO_CFG         ( CTL_BASE_AON_CLK + 0x011C )
#define REG_AON_CLK_CGM_LVDSRF_CALI_CFG      ( CTL_BASE_AON_CLK + 0x0120 )
#define REG_AON_CLK_CGM_SERDES_DPHY_APB_CFG  ( CTL_BASE_AON_CLK + 0x0124 )
#define REG_AON_CLK_CGM_SERDES_DPHY_REF_CFG  ( CTL_BASE_AON_CLK + 0x0128 )
#define REG_AON_CLK_CGM_SERDES_DPHY_CFG_CFG  ( CTL_BASE_AON_CLK + 0x012C )
#define REG_AON_CLK_CGM_ANALOG_APB_CFG       ( CTL_BASE_AON_CLK + 0x0130 )
#define REG_AON_CLK_CGM_IO_APB_CFG           ( CTL_BASE_AON_CLK + 0x0134 )
#define REG_AON_CLK_CGM_DJTAG_TCK_HW_CFG     ( CTL_BASE_AON_CLK + 0x0138 )

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_EMC_4X_CFG
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_EMC_2X_CFG
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_EMC_1X_CFG
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_PUB_AHB_CFG
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_PUB_AHB_CFG_CGM_PUB_AHB_DIV(x)                            (((x) & 0x3) << 8)
#define BIT_AON_CLK_CGM_PUB_AHB_CFG_CGM_PUB_AHB_SEL(x)                            (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_AON_APB_CFG
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_AON_APB_CFG_CGM_AON_APB_DIV(x)                            (((x) & 0x3) << 8)
#define BIT_AON_CLK_CGM_AON_APB_CFG_CGM_AON_APB_SEL(x)                            (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_ADI_CFG
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_ADI_CFG_CGM_ADI_SEL(x)                                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_AUX0_CFG
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_AUX1_CFG
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_AUX2_CFG
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_PROBE_CFG
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_PWM0_CFG
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_PWM0_CFG_CGM_PWM0_SEL(x)                                  (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_PWM1_CFG
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_PWM1_CFG_CGM_PWM1_SEL(x)                                  (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_PWM2_CFG
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_PWM2_CFG_CGM_PWM2_SEL(x)                                  (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_PWM3_CFG
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_PWM3_CFG_CGM_PWM3_SEL(x)                                  (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_EFUSE_CFG
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_EFUSE_CFG_CGM_EFUSE_SEL                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_ARM7_UART_CFG
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_ARM7_UART_CFG_CGM_ARM7_UART_SEL(x)                        (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_32K_CFG
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_32K_CFG_CGM_32K_SEL                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_1K_CFG
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_THM_CFG
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_THM_CFG_CGM_THM_SEL                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_MSPI_CFG
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_MSPI_CFG_CGM_MSPI_SEL(x)                                  (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_I2C_CFG
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_I2C_CFG_CGM_I2C_SEL(x)                                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_AVS_CFG
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_AVS_CFG_CGM_AVS_SEL(x)                                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_AUD_CFG
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_AUD_CFG_CGM_AUD_SEL                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_AUDIF_CFG
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_AUDIF_CFG_CGM_AUDIF_SEL(x)                                (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_VBC_CFG
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_VBC_CFG_CGM_VBC_SEL                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_AUD_IIS_DA0_CFG
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_AUD_IIS_DA0_CFG_CGM_AUD_IIS_DA0_PAD_SEL                   BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_AUD_IIS0_AD0_CFG
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_AUD_IIS0_AD0_CFG_CGM_AUD_IIS0_AD0_PAD_SEL                 BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_AUD_IIS1_AD0_CFG
// Register Offset : 0x008C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_AUD_IIS1_AD0_CFG_CGM_AUD_IIS1_AD0_PAD_SEL                 BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_CA7_DAP_CFG
// Register Offset : 0x0090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_CA7_DAP_CFG_CGM_CA7_DAP_SEL(x)                            (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_CA7_DAP_MTCK_CFG
// Register Offset : 0x0094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_CA7_DAP_MTCK_CFG_CGM_CA7_DAP_MTCK_PAD_SEL                 BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_CA7_TS_CFG
// Register Offset : 0x0098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_CA7_TS_CFG_CGM_CA7_TS_SEL(x)                              (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_DAC1_CAL_CFG
// Register Offset : 0x009C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_DAC1_CAL_CFG_CGM_DAC1_CAL_SEL                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_DAC2_CAL_CFG
// Register Offset : 0x00A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_DAC2_CAL_CFG_CGM_DAC2_CAL_SEL                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_DAC3_CAL_CFG
// Register Offset : 0x00A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_DAC3_CAL_CFG_CGM_DAC3_CAL_SEL                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_MDAR_CHK_CFG
// Register Offset : 0x00A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_MDAR_CHK_CFG_CGM_MDAR_CHK_SEL                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_RTC4M0_REF_CFG
// Register Offset : 0x00AC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_RTC4M0_REF_CFG_CGM_RTC4M0_REF_SEL                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_RTC4M0_FDK_CFG
// Register Offset : 0x00B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_RTC4M0_FDK_CFG_CGM_RTC4M0_FDK_SEL                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_DJTAG_TCK_CFG
// Register Offset : 0x00B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_DJTAG_TCK_CFG_CGM_DJTAG_TCK_SEL                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_ARM7_AHB_CFG
// Register Offset : 0x00B8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_ARM7_AHB_CFG_CGM_ARM7_AHB_DIV(x)                          (((x) & 0x3) << 8)
#define BIT_AON_CLK_CGM_ARM7_AHB_CFG_CGM_ARM7_AHB_SEL(x)                          (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_CA5_TS_CFG
// Register Offset : 0x00BC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_CA5_TS_CFG_CGM_CA5_TS_SEL(x)                              (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_FUNCDMA_CFG
// Register Offset : 0x00C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_FUNCDMA_CFG_CGM_FUNCDMA_PAD_SEL                           BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_EMC_REF_CFG
// Register Offset : 0x00C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_EMC_REF_CFG_CGM_EMC_REF_SEL(x)                            (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_CSSYS_CFG
// Register Offset : 0x00C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_CSSYS_CFG_CGM_CSSYS_DIV(x)                                (((x) & 0x3) << 8)
#define BIT_AON_CLK_CGM_CSSYS_CFG_CGM_CSSYS_SEL(x)                                (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_CSSYS_CA7_CFG
// Register Offset : 0x00CC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_CSSYS_CA7_CFG_CGM_CSSYS_CA7_DIV                           BIT(8)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_DET_32K_CFG
// Register Offset : 0x00D0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_DET_32K_CFG_CGM_DET_32K_SEL                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_TMR_CFG
// Register Offset : 0x00D4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_TMR_CFG_CGM_TMR_SEL                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_SDIO0_2X_CFG
// Register Offset : 0x00D8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_SDIO0_2X_CFG_CGM_SDIO0_2X_SEL(x)                          (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_SDIO0_1X_CFG
// Register Offset : 0x00DC
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_SDIO1_2X_CFG
// Register Offset : 0x00E0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_SDIO1_2X_CFG_CGM_SDIO1_2X_SEL(x)                          (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_SDIO1_1X_CFG
// Register Offset : 0x00E4
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_SDIO2_2X_CFG
// Register Offset : 0x00E8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_SDIO2_2X_CFG_CGM_SDIO2_2X_SEL(x)                          (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_SDIO2_1X_CFG
// Register Offset : 0x00EC
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_EMMC_2X_CFG
// Register Offset : 0x00F0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_EMMC_2X_CFG_CGM_EMMC_2X_SEL(x)                            (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_EMMC_1X_CFG
// Register Offset : 0x00F4
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_WCDMA_ICI_CFG
// Register Offset : 0x00F8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_WCDMA_ICI_CFG_CGM_WCDMA_ICI_SEL                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_WCDMA_CFG
// Register Offset : 0x00FC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_WCDMA_CFG_CGM_WCDMA_SEL                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_RFTI_TX_WD_CFG
// Register Offset : 0x0100
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_RFTI_TX_WD_CFG_CGM_RFTI_TX_WD_SEL                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_RFTI_RX_WD_CFG
// Register Offset : 0x0104
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_RFTI_RX_WD_CFG_CGM_RFTI_RX_WD_SEL                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_DSI_TEST_CFG
// Register Offset : 0x0108
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_DSI_TEST_CFG_CGM_DSI_TEST_PAD_SEL                         BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_AP_HS_SPI_CFG
// Register Offset : 0x010C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_AP_HS_SPI_CFG_CGM_AP_HS_SPI_PAD_SEL                       BIT(16)
#define BIT_AON_CLK_CGM_AP_HS_SPI_CFG_CGM_AP_HS_SPI_DIV(x)                        (((x) & 0x7) << 8)
#define BIT_AON_CLK_CGM_AP_HS_SPI_CFG_CGM_AP_HS_SPI_SEL(x)                        (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_RFTI_SBI_CFG
// Register Offset : 0x0110
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_RFTI_SBI_CFG_CGM_RFTI_SBI_SEL(x)                          (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_RFTI1_XO_CFG
// Register Offset : 0x0114
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_RFTI1_XO_CFG_CGM_RFTI1_XO_SEL                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_RFTI_LTH_CFG
// Register Offset : 0x0118
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_RFTI_LTH_CFG_CGM_RFTI_LTH_SEL                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_RFTI2_XO_CFG
// Register Offset : 0x011C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_RFTI2_XO_CFG_CGM_RFTI2_XO_SEL                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_LVDSRF_CALI_CFG
// Register Offset : 0x0120
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_LVDSRF_CALI_CFG_CGM_LVDSRF_CALI_SEL                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_SERDES_DPHY_APB_CFG
// Register Offset : 0x0124
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_SERDES_DPHY_APB_CFG_CGM_SERDES_DPHY_APB_SEL               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_SERDES_DPHY_REF_CFG
// Register Offset : 0x0128
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_SERDES_DPHY_REF_CFG_CGM_SERDES_DPHY_REF_SEL               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_SERDES_DPHY_CFG_CFG
// Register Offset : 0x012C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_SERDES_DPHY_CFG_CFG_CGM_SERDES_DPHY_CFG_SEL               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_ANALOG_APB_CFG
// Register Offset : 0x0130
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_ANALOG_APB_CFG_CGM_ANALOG_APB_SEL(x)                      (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_IO_APB_CFG
// Register Offset : 0x0134
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_IO_APB_CFG_CGM_IO_APB_DIV(x)                              (((x) & 0x3) << 8)
#define BIT_AON_CLK_CGM_IO_APB_CFG_CGM_IO_APB_SEL(x)                              (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CGM_DJTAG_TCK_HW_CFG
// Register Offset : 0x0138
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CGM_DJTAG_TCK_HW_CFG_CGM_DJTAG_TCK_HW_PAD_SEL                 BIT(16)


#endif // _AON_CLK_REG_H
