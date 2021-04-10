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

#define CTL_BASE_AON_CLK SPRD_AONCKG_BASE


#define REG_CLKTOP_CGM_CTL_CFG           ( CTL_BASE_AON_CLK + 0x0010 )
#define REG_CLKTOP_CGM_AON_APB_CFG       ( CTL_BASE_AON_CLK + 0x0020 )
#define REG_CLKTOP_CGM_ADI_CFG           ( CTL_BASE_AON_CLK + 0x0024 )
#define REG_CLKTOP_CGM_AUX0_CFG          ( CTL_BASE_AON_CLK + 0x0028 )
#define REG_CLKTOP_CGM_AUX1_CFG          ( CTL_BASE_AON_CLK + 0x002C )
#define REG_CLKTOP_CGM_AUX2_CFG          ( CTL_BASE_AON_CLK + 0x0030 )
#define REG_CLKTOP_CGM_PROBE_CFG         ( CTL_BASE_AON_CLK + 0x0034 )
#define REG_CLKTOP_CGM_PWM0_CFG          ( CTL_BASE_AON_CLK + 0x0038 )
#define REG_CLKTOP_CGM_PWM1_CFG          ( CTL_BASE_AON_CLK + 0x003C )
#define REG_CLKTOP_CGM_PWM2_CFG          ( CTL_BASE_AON_CLK + 0x0040 )
#define REG_CLKTOP_CGM_PWM3_CFG          ( CTL_BASE_AON_CLK + 0x0044 )
#define REG_CLKTOP_CGM_EFUSE_CFG         ( CTL_BASE_AON_CLK + 0x0048 )
#define REG_CLKTOP_CGM_SP_UART0_CFG      ( CTL_BASE_AON_CLK + 0x004C )
#define REG_CLKTOP_CGM_SP_UART1_CFG      ( CTL_BASE_AON_CLK + 0x0050 )
#define REG_CLKTOP_CGM_32K_OUT_CFG       ( CTL_BASE_AON_CLK + 0x0054 )
#define REG_CLKTOP_CGM_3K2_OUT_CFG       ( CTL_BASE_AON_CLK + 0x0058 )
#define REG_CLKTOP_CGM_1K_OUT_CFG        ( CTL_BASE_AON_CLK + 0x005C )
#define REG_CLKTOP_CGM_THM_CFG           ( CTL_BASE_AON_CLK + 0x0060 )
#define REG_CLKTOP_CGM_BIA_THM0_CFG      ( CTL_BASE_AON_CLK + 0x0064 )
#define REG_CLKTOP_CGM_BIA_THM1_CFG      ( CTL_BASE_AON_CLK + 0x0068 )
#define REG_CLKTOP_CGM_SP_I2C0_CFG       ( CTL_BASE_AON_CLK + 0x006C )
#define REG_CLKTOP_CGM_SP_I2C1_CFG       ( CTL_BASE_AON_CLK + 0x0070 )
#define REG_CLKTOP_CGM_SP_SPI_CFG        ( CTL_BASE_AON_CLK + 0x0074 )
#define REG_CLKTOP_CGM_AP_HS_SPI_CFG     ( CTL_BASE_AON_CLK + 0x0078 )
#define REG_CLKTOP_CGM_AON_I2C_CFG       ( CTL_BASE_AON_CLK + 0x007C )
#define REG_CLKTOP_CGM_AVS_CFG           ( CTL_BASE_AON_CLK + 0x0080 )
#define REG_CLKTOP_CGM_DAP_CFG           ( CTL_BASE_AON_CLK + 0x0084 )
#define REG_CLKTOP_CGM_DAP_MTCK_CFG      ( CTL_BASE_AON_CLK + 0x0088 )
#define REG_CLKTOP_CGM_TS_CFG            ( CTL_BASE_AON_CLK + 0x008C )
#define REG_CLKTOP_CGM_RFTI_SBI_CFG      ( CTL_BASE_AON_CLK + 0x0090 )
#define REG_CLKTOP_CGM_RFTI1_XO_CFG      ( CTL_BASE_AON_CLK + 0x0094 )
#define REG_CLKTOP_CGM_RFTI1_LTH_CFG     ( CTL_BASE_AON_CLK + 0x0098 )
#define REG_CLKTOP_CGM_RFTI2_XO_CFG      ( CTL_BASE_AON_CLK + 0x009C )
#define REG_CLKTOP_CGM_RFTI2_LTH_CFG     ( CTL_BASE_AON_CLK + 0x00A0 )
#define REG_CLKTOP_CGM_LVDSRF_CALI_CFG   ( CTL_BASE_AON_CLK + 0x00A4 )
#define REG_CLKTOP_CGM_MDAR_CHK_CFG      ( CTL_BASE_AON_CLK + 0x00A8 )
#define REG_CLKTOP_CGM_RCO100M_REF_CFG   ( CTL_BASE_AON_CLK + 0x00AC )
#define REG_CLKTOP_CGM_RCO100M_FDK_CFG   ( CTL_BASE_AON_CLK + 0x00B0 )
#define REG_CLKTOP_CGM_DJTAG_TCK_CFG     ( CTL_BASE_AON_CLK + 0x00B4 )
#define REG_CLKTOP_CGM_DAP4_TCK_CFG      ( CTL_BASE_AON_CLK + 0x00B8 )
#define REG_CLKTOP_CGM_SP_AHB_CFG        ( CTL_BASE_AON_CLK + 0x00BC )
#define REG_CLKTOP_CGM_SP_TMR_CFG        ( CTL_BASE_AON_CLK + 0x00C0 )
#define REG_CLKTOP_CGM_DET_32K_CFG       ( CTL_BASE_AON_CLK + 0x00C4 )
#define REG_CLKTOP_CGM_PMU_CFG           ( CTL_BASE_AON_CLK + 0x00C8 )
#define REG_CLKTOP_CGM_DEBOUNCE_CFG      ( CTL_BASE_AON_CLK + 0x00CC )
#define REG_CLKTOP_CGM_FUNCTEST_CFG      ( CTL_BASE_AON_CLK + 0x00D0 )
#define REG_CLKTOP_CGM_GPU_TS_CFG        ( CTL_BASE_AON_CLK + 0x00D4 )
#define REG_CLKTOP_CGM_BIA_LBAXI_CFG     ( CTL_BASE_AON_CLK + 0x00D8 )
#define REG_CLKTOP_CGM_BIA_IC_CFG        ( CTL_BASE_AON_CLK + 0x00DC )
#define REG_CLKTOP_CGM_BIA_26M_CFG       ( CTL_BASE_AON_CLK + 0x00E0 )
#define REG_CLKTOP_CGM_BIA_32K_CFG       ( CTL_BASE_AON_CLK + 0x00E4 )
#define REG_CLKTOP_CGM_ANALOG_APB_CFG    ( CTL_BASE_AON_CLK + 0x00E8 )
#define REG_CLKTOP_CGM_IO_APB_CFG        ( CTL_BASE_AON_CLK + 0x00EC )
#define REG_CLKTOP_CGM_DPHY0_REF_CFG     ( CTL_BASE_AON_CLK + 0x00F0 )
#define REG_CLKTOP_CGM_DPHY1_REF_CFG     ( CTL_BASE_AON_CLK + 0x00F4 )
#define REG_CLKTOP_CGM_USB2_REF_CFG      ( CTL_BASE_AON_CLK + 0x00F8 )
#define REG_CLKTOP_CGM_CSI0_RXDFE_CFG    ( CTL_BASE_AON_CLK + 0x00FC )
#define REG_CLKTOP_CGM_CSI1_RXDFE_CFG    ( CTL_BASE_AON_CLK + 0x0100 )
#define REG_CLKTOP_CGM_CSI2_RXDFE_CFG    ( CTL_BASE_AON_CLK + 0x0104 )
#define REG_CLKTOP_CGM_WCDMA_CFG         ( CTL_BASE_AON_CLK + 0x0108 )
#define REG_CLKTOP_CGM_WCDMA_WTLCP_CFG   ( CTL_BASE_AON_CLK + 0x010C )
#define REG_CLKTOP_CGM_WCDMA_PUBCP_CFG   ( CTL_BASE_AON_CLK + 0x0110 )
#define REG_CLKTOP_CGM_AON_CP_APB_CFG    ( CTL_BASE_AON_CLK + 0x0114 )
#define REG_CLKTOP_CGM_AON_MDAR_APB_CFG  ( CTL_BASE_AON_CLK + 0x0118 )
#define REG_CLKTOP_CGM_AON_PUB_APB_CFG   ( CTL_BASE_AON_CLK + 0x011C )
#define REG_CLKTOP_CGM_AP_MM_CFG         ( CTL_BASE_AON_CLK + 0x0120 )
#define REG_CLKTOP_CGM_SDIO0_2X_CFG      ( CTL_BASE_AON_CLK + 0x0124 )
#define REG_CLKTOP_CGM_SDIO0_1X_CFG      ( CTL_BASE_AON_CLK + 0x0128 )
#define REG_CLKTOP_CGM_SDIO1_2X_CFG      ( CTL_BASE_AON_CLK + 0x012C )
#define REG_CLKTOP_CGM_SDIO1_1X_CFG      ( CTL_BASE_AON_CLK + 0x0130 )
#define REG_CLKTOP_CGM_SDIO2_2X_CFG      ( CTL_BASE_AON_CLK + 0x0134 )
#define REG_CLKTOP_CGM_SDIO2_1X_CFG      ( CTL_BASE_AON_CLK + 0x0138 )
#define REG_CLKTOP_CGM_EMMC_2X_CFG       ( CTL_BASE_AON_CLK + 0x013C )
#define REG_CLKTOP_CGM_EMMC_1X_CFG       ( CTL_BASE_AON_CLK + 0x0140 )
#define REG_CLKTOP_CGM_DEBUG_DSI_CFG     ( CTL_BASE_AON_CLK + 0x0144 )
#define REG_CLKTOP_CGM_MDAR_SERDES_CFG   ( CTL_BASE_AON_CLK + 0x0148 )
#define REG_CLKTOP_CGM_RFTI_SERDES_CFG   ( CTL_BASE_AON_CLK + 0x014C )
#define REG_CLKTOP_CGM_AUD_CFG           ( CTL_BASE_AON_CLK + 0x0150 )
#define REG_CLKTOP_CGM_AUDIF_CFG         ( CTL_BASE_AON_CLK + 0x0154 )
#define REG_CLKTOP_CGM_VBC_CFG           ( CTL_BASE_AON_CLK + 0x0158 )
#define REG_CLKTOP_CGM_SCAN_BISR_CFG     ( CTL_BASE_AON_CLK + 0x015C )

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_CTL_CFG
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_DOZE_MODE_EN                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_AON_APB_CFG
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_AON_APB_DOZE_EN                    BIT(17)
#define BIT_CGM_AON_APB_DIV(x)                     (((x) & 0x3) << 8)
#define BIT_CGM_AON_APB_SEL(x)                     (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_ADI_CFG
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_ADI_DOZE_EN                        BIT(17)
#define BIT_CGM_ADI_SEL(x)                         (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_AUX0_CFG
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_AUX0_DOZE_EN                       BIT(17)
#define BIT_CGM_AUX0_DIV(x)                        (((x) & 0xF) << 8)
#define BIT_CGM_AUX0_SEL(x)                        (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_AUX1_CFG
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_AUX1_DOZE_EN                       BIT(17)
#define BIT_CGM_AUX1_DIV(x)                        (((x) & 0xF) << 8)
#define BIT_CGM_AUX1_SEL(x)                        (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_AUX2_CFG
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_AUX2_DOZE_EN                       BIT(17)
#define BIT_CGM_AUX2_DIV(x)                        (((x) & 0xF) << 8)
#define BIT_CGM_AUX2_SEL(x)                        (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_PROBE_CFG
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_PROBE_DOZE_EN                      BIT(17)
#define BIT_CGM_PROBE_DIV(x)                       (((x) & 0xF) << 8)
#define BIT_CGM_PROBE_SEL(x)                       (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_PWM0_CFG
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_PWM0_DOZE_EN                       BIT(17)
#define BIT_CGM_PWM0_SEL(x)                        (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_PWM1_CFG
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_PWM1_DOZE_EN                       BIT(17)
#define BIT_CGM_PWM1_SEL(x)                        (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_PWM2_CFG
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_PWM2_DOZE_EN                       BIT(17)
#define BIT_CGM_PWM2_SEL(x)                        (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_PWM3_CFG
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_PWM3_DOZE_EN                       BIT(17)
#define BIT_CGM_PWM3_SEL(x)                        (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_EFUSE_CFG
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_EFUSE_DOZE_EN                      BIT(17)
#define BIT_CGM_EFUSE_SEL                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_SP_UART0_CFG
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_SP_UART0_DOZE_EN                   BIT(17)
#define BIT_CGM_SP_UART0_SEL(x)                    (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_SP_UART1_CFG
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_SP_UART1_DOZE_EN                   BIT(17)
#define BIT_CGM_SP_UART1_SEL(x)                    (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_32K_OUT_CFG
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_32K_OUT_DOZE_EN                    BIT(17)
#define BIT_CGM_32K_OUT_SEL                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_3K2_OUT_CFG
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_1K_OUT_CFG
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_THM_CFG
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_THM_DOZE_EN                        BIT(17)
#define BIT_CGM_THM_SEL                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_BIA_THM0_CFG
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_BIA_THM0_DOZE_EN                   BIT(17)
#define BIT_CGM_BIA_THM0_SEL                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_BIA_THM1_CFG
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_BIA_THM1_DOZE_EN                   BIT(17)
#define BIT_CGM_BIA_THM1_SEL                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_SP_I2C0_CFG
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_SP_I2C0_DOZE_EN                    BIT(17)
#define BIT_CGM_SP_I2C0_SEL(x)                     (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_SP_I2C1_CFG
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_SP_I2C1_DOZE_EN                    BIT(17)
#define BIT_CGM_SP_I2C1_SEL(x)                     (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_SP_SPI_CFG
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_SP_SPI_DOZE_EN                     BIT(17)
#define BIT_CGM_SP_SPI_PAD_SEL                     BIT(16)
#define BIT_CGM_SP_SPI_DIV(x)                      (((x) & 0x7) << 8)
#define BIT_CGM_SP_SPI_SEL(x)                      (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_AP_HS_SPI_CFG
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_AP_HS_SPI_DOZE_EN                  BIT(17)
#define BIT_CGM_AP_HS_SPI_PAD_SEL                  BIT(16)
#define BIT_CGM_AP_HS_SPI_DIV(x)                   (((x) & 0x7) << 8)
#define BIT_CGM_AP_HS_SPI_SEL(x)                   (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_AON_I2C_CFG
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_AON_I2C_DOZE_EN                    BIT(17)
#define BIT_CGM_AON_I2C_SEL(x)                     (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_AVS_CFG
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_AVS_DOZE_EN                        BIT(17)
#define BIT_CGM_AVS_SEL(x)                         (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_DAP_CFG
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_DAP_DOZE_EN                        BIT(17)
#define BIT_CGM_DAP_SEL(x)                         (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_DAP_MTCK_CFG
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_DAP_MTCK_PAD_SEL                   BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_TS_CFG
// Register Offset : 0x008C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_TS_DOZE_EN                         BIT(17)
#define BIT_CGM_TS_SEL(x)                          (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_RFTI_SBI_CFG
// Register Offset : 0x0090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_RFTI_SBI_DOZE_EN                   BIT(17)
#define BIT_CGM_RFTI_SBI_SEL(x)                    (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_RFTI1_XO_CFG
// Register Offset : 0x0094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_RFTI1_XO_DOZE_EN                   BIT(17)
#define BIT_CGM_RFTI1_XO_SEL                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_RFTI1_LTH_CFG
// Register Offset : 0x0098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_RFTI1_LTH_DOZE_EN                  BIT(17)
#define BIT_CGM_RFTI1_LTH_SEL                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_RFTI2_XO_CFG
// Register Offset : 0x009C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_RFTI2_XO_DOZE_EN                   BIT(17)
#define BIT_CGM_RFTI2_XO_SEL                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_RFTI2_LTH_CFG
// Register Offset : 0x00A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_RFTI2_LTH_DOZE_EN                  BIT(17)
#define BIT_CGM_RFTI2_LTH_SEL                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_LVDSRF_CALI_CFG
// Register Offset : 0x00A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_LVDSRF_CALI_DOZE_EN                BIT(17)
#define BIT_CGM_LVDSRF_CALI_SEL                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_MDAR_CHK_CFG
// Register Offset : 0x00A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_MDAR_CHK_DOZE_EN                   BIT(17)
#define BIT_CGM_MDAR_CHK_SEL                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_RCO100M_REF_CFG
// Register Offset : 0x00AC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_RCO100M_REF_DOZE_EN                BIT(17)
#define BIT_CGM_RCO100M_REF_SEL                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_RCO100M_FDK_CFG
// Register Offset : 0x00B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_RCO100M_FDK_DOZE_EN                BIT(17)
#define BIT_CGM_RCO100M_FDK_SEL                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_DJTAG_TCK_CFG
// Register Offset : 0x00B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_DJTAG_TCK_DOZE_EN                  BIT(17)
#define BIT_CGM_DJTAG_TCK_PAD_SEL                  BIT(16)
#define BIT_CGM_DJTAG_TCK_SEL                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_DAP4_TCK_CFG
// Register Offset : 0x00B8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_DAP4_TCK_PAD_SEL                   BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_SP_AHB_CFG
// Register Offset : 0x00BC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_SP_AHB_DOZE_EN                     BIT(17)
#define BIT_CGM_SP_AHB_DIV(x)                      (((x) & 0x3) << 8)
#define BIT_CGM_SP_AHB_SEL(x)                      (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_SP_TMR_CFG
// Register Offset : 0x00C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_SP_TMR_DOZE_EN                     BIT(17)
#define BIT_CGM_SP_TMR_SEL(x)                      (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_DET_32K_CFG
// Register Offset : 0x00C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_DET_32K_DOZE_EN                    BIT(17)
#define BIT_CGM_DET_32K_SEL                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_PMU_CFG
// Register Offset : 0x00C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_PMU_DOZE_EN                        BIT(17)
#define BIT_CGM_PMU_SEL(x)                         (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_DEBOUNCE_CFG
// Register Offset : 0x00CC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_DEBOUNCE_DOZE_EN                   BIT(17)
#define BIT_CGM_DEBOUNCE_SEL(x)                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_FUNCTEST_CFG
// Register Offset : 0x00D0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_FUNCTEST_PAD_SEL                   BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_GPU_TS_CFG
// Register Offset : 0x00D4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_GPU_TS_DOZE_EN                     BIT(17)
#define BIT_CGM_GPU_TS_SEL(x)                      (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_BIA_LBAXI_CFG
// Register Offset : 0x00D8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_BIA_LBAXI_DOZE_EN                  BIT(17)
#define BIT_CGM_BIA_LBAXI_SEL                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_BIA_IC_CFG
// Register Offset : 0x00DC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_BIA_IC_DOZE_EN                     BIT(17)
#define BIT_CGM_BIA_IC_SEL                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_BIA_26M_CFG
// Register Offset : 0x00E0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_BIA_26M_DOZE_EN                    BIT(17)
#define BIT_CGM_BIA_26M_SEL                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_BIA_32K_CFG
// Register Offset : 0x00E4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_BIA_32K_DOZE_EN                    BIT(17)
#define BIT_CGM_BIA_32K_SEL                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_ANALOG_APB_CFG
// Register Offset : 0x00E8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_ANALOG_APB_DOZE_EN                 BIT(17)
#define BIT_CGM_ANALOG_APB_SEL(x)                  (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_IO_APB_CFG
// Register Offset : 0x00EC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_IO_APB_DOZE_EN                     BIT(17)
#define BIT_CGM_IO_APB_DIV(x)                      (((x) & 0x3) << 8)
#define BIT_CGM_IO_APB_SEL(x)                      (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_DPHY0_REF_CFG
// Register Offset : 0x00F0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_DPHY0_REF_DOZE_EN                  BIT(17)
#define BIT_CGM_DPHY0_REF_SEL                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_DPHY1_REF_CFG
// Register Offset : 0x00F4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_DPHY1_REF_DOZE_EN                  BIT(17)
#define BIT_CGM_DPHY1_REF_SEL                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_USB2_REF_CFG
// Register Offset : 0x00F8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_USB2_REF_DOZE_EN                   BIT(17)
#define BIT_CGM_USB2_REF_SEL                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_CSI0_RXDFE_CFG
// Register Offset : 0x00FC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_CSI0_RXDFE_DOZE_EN                 BIT(17)
#define BIT_CGM_CSI0_RXDFE_SEL                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_CSI1_RXDFE_CFG
// Register Offset : 0x0100
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_CSI1_RXDFE_DOZE_EN                 BIT(17)
#define BIT_CGM_CSI1_RXDFE_SEL                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_CSI2_RXDFE_CFG
// Register Offset : 0x0104
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_CSI2_RXDFE_DOZE_EN                 BIT(17)
#define BIT_CGM_CSI2_RXDFE_SEL                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_WCDMA_CFG
// Register Offset : 0x0108
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_WCDMA_DOZE_EN                      BIT(17)
#define BIT_CGM_WCDMA_SEL                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_WCDMA_WTLCP_CFG
// Register Offset : 0x010C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_WCDMA_WTLCP_DOZE_EN                BIT(17)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_WCDMA_PUBCP_CFG
// Register Offset : 0x0110
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_WCDMA_PUBCP_DOZE_EN                BIT(17)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_AON_CP_APB_CFG
// Register Offset : 0x0114
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_AON_CP_APB_DOZE_EN                 BIT(17)
#define BIT_CGM_AON_CP_APB_DIV(x)                  (((x) & 0x3) << 8)
#define BIT_CGM_AON_CP_APB_SEL(x)                  (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_AON_MDAR_APB_CFG
// Register Offset : 0x0118
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_AON_MDAR_APB_DOZE_EN               BIT(17)
#define BIT_CGM_AON_MDAR_APB_DIV(x)                (((x) & 0x3) << 8)
#define BIT_CGM_AON_MDAR_APB_SEL(x)                (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_AON_PUB_APB_CFG
// Register Offset : 0x011C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_AON_PUB_APB_DOZE_EN                BIT(17)
#define BIT_CGM_AON_PUB_APB_DIV(x)                 (((x) & 0x3) << 8)
#define BIT_CGM_AON_PUB_APB_SEL(x)                 (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_AP_MM_CFG
// Register Offset : 0x0120
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_AP_MM_DOZE_EN                      BIT(17)
#define BIT_CGM_AP_MM_DIV(x)                       (((x) & 0x3) << 8)
#define BIT_CGM_AP_MM_SEL(x)                       (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_SDIO0_2X_CFG
// Register Offset : 0x0124
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_SDIO0_2X_DOZE_EN                   BIT(17)
#define BIT_CGM_SDIO0_2X_SEL(x)                    (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_SDIO0_1X_CFG
// Register Offset : 0x0128
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_SDIO0_1X_DOZE_EN                   BIT(17)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_SDIO1_2X_CFG
// Register Offset : 0x012C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_SDIO1_2X_DOZE_EN                   BIT(17)
#define BIT_CGM_SDIO1_2X_SEL(x)                    (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_SDIO1_1X_CFG
// Register Offset : 0x0130
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_SDIO1_1X_DOZE_EN                   BIT(17)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_SDIO2_2X_CFG
// Register Offset : 0x0134
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_SDIO2_2X_DOZE_EN                   BIT(17)
#define BIT_CGM_SDIO2_2X_SEL(x)                    (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_SDIO2_1X_CFG
// Register Offset : 0x0138
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_SDIO2_1X_DOZE_EN                   BIT(17)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_EMMC_2X_CFG
// Register Offset : 0x013C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_EMMC_2X_DOZE_EN                    BIT(17)
#define BIT_CGM_EMMC_2X_SEL(x)                     (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_EMMC_1X_CFG
// Register Offset : 0x0140
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_EMMC_1X_DOZE_EN                    BIT(17)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_DEBUG_DSI_CFG
// Register Offset : 0x0144
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_DEBUG_DSI_PAD_SEL                  BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_MDAR_SERDES_CFG
// Register Offset : 0x0148
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_MDAR_SERDES_DOZE_EN                BIT(17)
#define BIT_CGM_MDAR_SERDES_SEL                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_RFTI_SERDES_CFG
// Register Offset : 0x014C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_RFTI_SERDES_DOZE_EN                BIT(17)
#define BIT_CGM_RFTI_SERDES_SEL                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_AUD_CFG
// Register Offset : 0x0150
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_AUD_DOZE_EN                        BIT(17)
#define BIT_CGM_AUD_SEL                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_AUDIF_CFG
// Register Offset : 0x0154
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_AUDIF_DOZE_EN                      BIT(17)
#define BIT_CGM_AUDIF_SEL(x)                       (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_VBC_CFG
// Register Offset : 0x0158
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_VBC_DOZE_EN                        BIT(17)
#define BIT_CGM_VBC_SEL                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_CLK_CLKTOP_CGM_SCAN_BISR_CFG
// Register Offset : 0x015C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_SCAN_BISR_DOZE_EN                  BIT(17)
#define BIT_CGM_SCAN_BISR_SEL                      BIT(0)


#endif // _AON_CLK_REG_H
