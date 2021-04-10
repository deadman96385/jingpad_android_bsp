/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _AON_CLK_CORE_REG_H
#define _AON_CLK_CORE_REG_H

#define CTL_BASE_AON_CLK_CORE 0x402D0200


#define REG_AON_CLK_EMC_4X_CFG           ( CTL_BASE_AON_CLK_CORE + 0x0020 )
#define REG_AON_CLK_EMC_2X_CFG           ( CTL_BASE_AON_CLK_CORE + 0x0024 )
#define REG_AON_CLK_EMC_1X_CFG           ( CTL_BASE_AON_CLK_CORE + 0x0028 )
#define REG_AON_CLK_PUB_AHB_CFG          ( CTL_BASE_AON_CLK_CORE + 0x002C )
#define REG_AON_CLK_AON_APB_CFG          ( CTL_BASE_AON_CLK_CORE + 0x0030 )
#define REG_AON_CLK_ADI_CFG              ( CTL_BASE_AON_CLK_CORE + 0x0034 )
#define REG_AON_CLK_AUX0_CFG             ( CTL_BASE_AON_CLK_CORE + 0x0038 )
#define REG_AON_CLK_AUX1_CFG             ( CTL_BASE_AON_CLK_CORE + 0x003C )
#define REG_AON_CLK_AUX2_CFG             ( CTL_BASE_AON_CLK_CORE + 0x0040 )
#define REG_AON_CLK_PROBE_CFG            ( CTL_BASE_AON_CLK_CORE + 0x0044 )
#define REG_AON_CLK_PWM0_CFG             ( CTL_BASE_AON_CLK_CORE + 0x0048 )
#define REG_AON_CLK_PWM1_CFG             ( CTL_BASE_AON_CLK_CORE + 0x004C )
#define REG_AON_CLK_PWM2_CFG             ( CTL_BASE_AON_CLK_CORE + 0x0050 )
#define REG_AON_CLK_PWM3_CFG             ( CTL_BASE_AON_CLK_CORE + 0x0054 )
#define REG_AON_CLK_EFUSE_CFG            ( CTL_BASE_AON_CLK_CORE + 0x0058 )
#define REG_AON_CLK_CM4_UART_CFG         ( CTL_BASE_AON_CLK_CORE + 0x005C )
#define REG_AON_CLK_32K_CFG              ( CTL_BASE_AON_CLK_CORE + 0x0060 )
#define REG_AON_CLK_1K_CFG               ( CTL_BASE_AON_CLK_CORE + 0x0064 )
#define REG_AON_CLK_THM_CFG              ( CTL_BASE_AON_CLK_CORE + 0x0068 )
#define REG_AON_CLK_I2C_CFG              ( CTL_BASE_AON_CLK_CORE + 0x006C )
#define REG_AON_CLK_AVS_CFG              ( CTL_BASE_AON_CLK_CORE + 0x0070 )
#define REG_AON_CLK_AUD_CFG              ( CTL_BASE_AON_CLK_CORE + 0x0074 )
#define REG_AON_CLK_AUDIF_CFG            ( CTL_BASE_AON_CLK_CORE + 0x0078 )
#define REG_AON_CLK_VBC_CFG              ( CTL_BASE_AON_CLK_CORE + 0x007C )
#define REG_AON_CLK_AUD_IIS_DA0_CFG      ( CTL_BASE_AON_CLK_CORE + 0x0080 )
#define REG_AON_CLK_AUD_IIS0_AD0_CFG     ( CTL_BASE_AON_CLK_CORE + 0x0084 )
#define REG_AON_CLK_AUD_IIS1_AD0_CFG     ( CTL_BASE_AON_CLK_CORE + 0x0088 )
#define REG_AON_CLK_CA7_DAP_CFG          ( CTL_BASE_AON_CLK_CORE + 0x008C )
#define REG_AON_CLK_CA7_DAP_MTCK_CFG     ( CTL_BASE_AON_CLK_CORE + 0x0090 )
#define REG_AON_CLK_CA7_TS_CFG           ( CTL_BASE_AON_CLK_CORE + 0x0094 )
#define REG_AON_CLK_DJTAG_TCK_CFG        ( CTL_BASE_AON_CLK_CORE + 0x0098 )
#define REG_AON_CLK_CM4_AHB_CFG          ( CTL_BASE_AON_CLK_CORE + 0x009C )
#define REG_AON_CLK_CA5_TS_CFG           ( CTL_BASE_AON_CLK_CORE + 0x00A0 )
#define REG_AON_CLK_FUNCDMA_CFG          ( CTL_BASE_AON_CLK_CORE + 0x00A4 )
#define REG_AON_CLK_EMC_CFG              ( CTL_BASE_AON_CLK_CORE + 0x00A8 )
#define REG_AON_CLK_CSSYS_CFG            ( CTL_BASE_AON_CLK_CORE + 0x00AC )
#define REG_AON_CLK_CSSYS_CA7_CFG        ( CTL_BASE_AON_CLK_CORE + 0x00B0 )
#define REG_AON_CLK_DET_32K_CFG          ( CTL_BASE_AON_CLK_CORE + 0x00B4 )
#define REG_AON_CLK_TMR_CFG              ( CTL_BASE_AON_CLK_CORE + 0x00B8 )
#define REG_AON_CLK_SDIO0_2X_CFG         ( CTL_BASE_AON_CLK_CORE + 0x00BC )
#define REG_AON_CLK_SDIO0_1X_CFG         ( CTL_BASE_AON_CLK_CORE + 0x00C0 )
#define REG_AON_CLK_NANDC_2X_CFG         ( CTL_BASE_AON_CLK_CORE + 0x00C4 )
#define REG_AON_CLK_NANDC_1X_CFG         ( CTL_BASE_AON_CLK_CORE + 0x00C8 )
#define REG_AON_CLK_EMMC_2X_CFG          ( CTL_BASE_AON_CLK_CORE + 0x00CC )
#define REG_AON_CLK_EMMC_1X_CFG          ( CTL_BASE_AON_CLK_CORE + 0x00D0 )
#define REG_AON_CLK_WCDMA_CFG            ( CTL_BASE_AON_CLK_CORE + 0x00D4 )
#define REG_AON_CLK_WCN_CFG              ( CTL_BASE_AON_CLK_CORE + 0x00D8 )
#define REG_AON_CLK_DSI_TEST_CFG         ( CTL_BASE_AON_CLK_CORE + 0x00DC )
#define REG_AON_CLK_AP_HS_SPI_CFG        ( CTL_BASE_AON_CLK_CORE + 0x00E0 )
#define REG_AON_CLK_SERDES_DPHY_APB_CFG  ( CTL_BASE_AON_CLK_CORE + 0x00E4 )
#define REG_AON_CLK_SERDES_DPHY_REF_CFG  ( CTL_BASE_AON_CLK_CORE + 0x00E8 )
#define REG_AON_CLK_SERDES_DPHY_CFG_CFG  ( CTL_BASE_AON_CLK_CORE + 0x00EC )
#define REG_AON_CLK_ANALOG_APB_CFG       ( CTL_BASE_AON_CLK_CORE + 0x00F0 )
#define REG_AON_CLK_IO_APB_CFG           ( CTL_BASE_AON_CLK_CORE + 0x00F4 )
#define REG_AON_CLK_DJTAG_TCK_HW_CFG     ( CTL_BASE_AON_CLK_CORE + 0x00F8 )

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_EMC_4X_CFG
// Register Offset : 0x0020
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_EMC_4X_CFG_EMC_4X_DIV(x)                                   (((x) & 0x3) << 8)
#define BIT_AON_CLK_EMC_4X_CFG_EMC_4X_SEL(x)                                   (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_EMC_2X_CFG
// Register Offset : 0x0024
// Description     :
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_EMC_1X_CFG
// Register Offset : 0x0028
// Description     :
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_PUB_AHB_CFG
// Register Offset : 0x002C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_PUB_AHB_CFG_PUB_AHB_DIV(x)                                 (((x) & 0x3) << 8)
#define BIT_AON_CLK_PUB_AHB_CFG_PUB_AHB_SEL(x)                                 (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_AON_APB_CFG
// Register Offset : 0x0030
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_AON_APB_CFG_AON_APB_DIV(x)                                 (((x) & 0x3) << 8)
#define BIT_AON_CLK_AON_APB_CFG_AON_APB_SEL(x)                                 (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_ADI_CFG
// Register Offset : 0x0034
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_ADI_CFG_ADI_SEL(x)                                         (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_AUX0_CFG
// Register Offset : 0x0038
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_AUX0_CFG_AUX0_SEL(x)                                       (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_AUX1_CFG
// Register Offset : 0x003C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_AUX1_CFG_AUX1_SEL(x)                                       (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_AUX2_CFG
// Register Offset : 0x0040
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_AUX2_CFG_AUX2_SEL(x)                                       (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_PROBE_CFG
// Register Offset : 0x0044
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_PROBE_CFG_PROBE_SEL(x)                                     (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_PWM0_CFG
// Register Offset : 0x0048
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_PWM0_CFG_PWM0_SEL(x)                                       (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_PWM1_CFG
// Register Offset : 0x004C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_PWM1_CFG_PWM1_SEL(x)                                       (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_PWM2_CFG
// Register Offset : 0x0050
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_PWM2_CFG_PWM2_SEL(x)                                       (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_PWM3_CFG
// Register Offset : 0x0054
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_PWM3_CFG_PWM3_SEL(x)                                       (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_EFUSE_CFG
// Register Offset : 0x0058
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_EFUSE_CFG_EFUSE_SEL                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CM4_UART_CFG
// Register Offset : 0x005C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CM4_UART_CFG_CM4_UART_SEL(x)                               (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_32K_CFG
// Register Offset : 0x0060
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_32K_CFG_32K_SEL                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_1K_CFG
// Register Offset : 0x0064
// Description     :
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_THM_CFG
// Register Offset : 0x0068
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_THM_CFG_THM_SEL                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_I2C_CFG
// Register Offset : 0x006C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_I2C_CFG_I2C_SEL(x)                                         (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_AVS_CFG
// Register Offset : 0x0070
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_AVS_CFG_AVS_SEL(x)                                         (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_AUD_CFG
// Register Offset : 0x0074
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_AUD_CFG_AUD_SEL                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_AUDIF_CFG
// Register Offset : 0x0078
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_AUDIF_CFG_AUDIF_SEL(x)                                     (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_VBC_CFG
// Register Offset : 0x007C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_VBC_CFG_VBC_SEL                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_AUD_IIS_DA0_CFG
// Register Offset : 0x0080
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_AUD_IIS_DA0_CFG_AUD_IIS_DA0_PAD_SEL                        BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_AUD_IIS0_AD0_CFG
// Register Offset : 0x0084
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_AUD_IIS0_AD0_CFG_AUD_IIS0_AD0_PAD_SEL                      BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_AUD_IIS1_AD0_CFG
// Register Offset : 0x0088
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_AUD_IIS1_AD0_CFG_AUD_IIS1_AD0_PAD_SEL                      BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CA7_DAP_CFG
// Register Offset : 0x008C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CA7_DAP_CFG_CA7_DAP_SEL(x)                                 (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CA7_DAP_MTCK_CFG
// Register Offset : 0x0090
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CA7_DAP_MTCK_CFG_CA7_DAP_MTCK_PAD_SEL                      BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CA7_TS_CFG
// Register Offset : 0x0094
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CA7_TS_CFG_CA7_TS_SEL(x)                                   (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_DJTAG_TCK_CFG
// Register Offset : 0x0098
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_DJTAG_TCK_CFG_DJTAG_TCK_PAD_SEL                            BIT(16)
#define BIT_AON_CLK_DJTAG_TCK_CFG_DJTAG_TCK_SEL                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CM4_AHB_CFG
// Register Offset : 0x009C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CM4_AHB_CFG_CM4_AHB_DIV(x)                                 (((x) & 0x3) << 8)
#define BIT_AON_CLK_CM4_AHB_CFG_CM4_AHB_SEL(x)                                 (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CA5_TS_CFG
// Register Offset : 0x00A0
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CA5_TS_CFG_CA5_TS_SEL(x)                                   (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_FUNCDMA_CFG
// Register Offset : 0x00A4
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_FUNCDMA_CFG_FUNCDMA_PAD_SEL                                BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_EMC_REF_CFG
// Register Offset : 0x00A8
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_EMC_REF_CFG_EMC_REF_SEL(x)                                 (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CSSYS_CFG
// Register Offset : 0x00AC
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CSSYS_CFG_CSSYS_DIV(x)                                     (((x) & 0x3) << 8)
#define BIT_AON_CLK_CSSYS_CFG_CSSYS_SEL(x)                                     (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CSSYS_CA7_CFG
// Register Offset : 0x00B0
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_CSSYS_CA7_CFG_CSSYS_CA7_DIV                                BIT(8)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_DET_32K_CFG
// Register Offset : 0x00B4
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_DET_32K_CFG_DET_32K_SEL                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_TMR_CFG
// Register Offset : 0x00B8
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_TMR_CFG_TMR_SEL                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_SDIO0_2X_CFG
// Register Offset : 0x00BC
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_SDIO0_2X_CFG_SDIO0_2X_SEL(x)                               (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_SDIO0_1X_CFG
// Register Offset : 0x00C0
// Description     :
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_NANDC_2X_CFG
// Register Offset : 0x00C4
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_NANDC_2X_CFG_NANDC_2X_SEL(x)                               (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_NANDC_1X_CFG
// Register Offset : 0x00C8
// Description     :
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_EMMC_2X_CFG
// Register Offset : 0x00CC
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_EMMC_2X_CFG_EMMC_2X_SEL(x)                                 (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_EMMC_1X_CFG
// Register Offset : 0x00D0
// Description     :
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_WCDMA_CFG
// Register Offset : 0x00D4
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_WCDMA_CFG_WCDMA_SEL                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_WCN_CFG
// Register Offset : 0x00D8
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_WCN_CFG_WCN_DIV(x)                                         (((x) & 0x7) << 8)
#define BIT_AON_CLK_WCN_CFG_WCN_SEL(x)                                         (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_DSI_TEST_CFG
// Register Offset : 0x00DC
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_DSI_TEST_CFG_DSI_TEST_PAD_SEL                              BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_AP_HS_SPI_CFG
// Register Offset : 0x00E0
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_AP_HS_SPI_CFG_AP_HS_SPI_PAD_SEL                            BIT(16)
#define BIT_AON_CLK_AP_HS_SPI_CFG_AP_HS_SPI_DIV(x)                             (((x) & 0x7) << 8)
#define BIT_AON_CLK_AP_HS_SPI_CFG_AP_HS_SPI_SEL(x)                             (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_SERDES_DPHY_APB_CFG
// Register Offset : 0x00E4
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_SERDES_DPHY_APB_CFG_SERDES_DPHY_APB_SEL(x)                 (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_SERDES_DPHY_REF_CFG
// Register Offset : 0x00E8
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_SERDES_DPHY_REF_CFG_SERDES_DPHY_REF_SEL                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_SERDES_DPHY_CFG_CFG
// Register Offset : 0x00EC
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_SERDES_DPHY_CFG_CFG_SERDES_DPHY_CFG_SEL                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_ANALOG_APB_CFG
// Register Offset : 0x00F0
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_ANALOG_APB_CFG_ANALOG_APB_SEL(x)                           (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_IO_APB_CFG
// Register Offset : 0x00F4
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_IO_APB_CFG_IO_APB_DIV(x)                                   (((x) & 0x3) << 8)
#define BIT_AON_CLK_IO_APB_CFG_IO_APB_SEL(x)                                   (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_DJTAG_TCK_HW_CFG
// Register Offset : 0x00F8
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AON_CLK_DJTAG_TCK_HW_CFG_DJTAG_TCK_HW_PAD_SEL                      BIT(16)


#endif // _AON_CLK_CORE_REG_H
