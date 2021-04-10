/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2017-12-27 15:24:15
 *
 */


#ifndef AP_AHB_H
#define AP_AHB_H

#define CTL_BASE_AP_AHB 0x20E00000


#define REG_AP_AHB_AHB_EB                      ( CTL_BASE_AP_AHB + 0x0000 )
#define REG_AP_AHB_AHB_RST                     ( CTL_BASE_AP_AHB + 0x0004 )
#define REG_AP_AHB_AP_SYS_FORCE_SLEEP_CFG      ( CTL_BASE_AP_AHB + 0x000C )
#define REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG       ( CTL_BASE_AP_AHB + 0x0010 )
#define REG_AP_AHB_RESERVED0_REG               ( CTL_BASE_AP_AHB + 0x0018 )
#define REG_AP_AHB_RESERVED1_REG               ( CTL_BASE_AP_AHB + 0x001C )
#define REG_AP_AHB_RESERVED2_REG               ( CTL_BASE_AP_AHB + 0x0020 )
#define REG_AP_AHB_AP_MTX_WQOS_CFG             ( CTL_BASE_AP_AHB + 0x3004 )
#define REG_AP_AHB_AP_MTX_RQOS_CFG             ( CTL_BASE_AP_AHB + 0x3008 )
#define REG_AP_AHB_AP_QOS_CFG                  ( CTL_BASE_AP_AHB + 0x3010 )
#define REG_AP_AHB_AP_URGENCY_BYPASS_ADDRESS   ( CTL_BASE_AP_AHB + 0x3018 )
#define REG_AP_AHB_AP_FRC_URGENCY              ( CTL_BASE_AP_AHB + 0x301C )
#define REG_AP_AHB_OTG_PHY_TUNE                ( CTL_BASE_AP_AHB + 0x3020 )
#define REG_AP_AHB_OTG_PHY_TEST                ( CTL_BASE_AP_AHB + 0x3024 )
#define REG_AP_AHB_OTG_PHY_CTRL                ( CTL_BASE_AP_AHB + 0x3028 )
#define REG_AP_AHB_OTG_CTRL1                   ( CTL_BASE_AP_AHB + 0x3030 )
#define REG_AP_AHB_MST_FRC_LSLP                ( CTL_BASE_AP_AHB + 0x3034 )
#define REG_AP_AHB_MTX_LSLP_LPC_BYPASS         ( CTL_BASE_AP_AHB + 0x3038 )
#define REG_AP_AHB_MST_PUB_FRC_DSLP            ( CTL_BASE_AP_AHB + 0x303C )
#define REG_AP_AHB_MTX_PUB_DSLP_LPC_BYPASS     ( CTL_BASE_AP_AHB + 0x3040 )
#define REG_AP_AHB_MTX_FRC_DOZE_SLEEP          ( CTL_BASE_AP_AHB + 0x3044 )
#define REG_AP_AHB_MTX_DOZE_LPC_BYPASS         ( CTL_BASE_AP_AHB + 0x3048 )
#define REG_AP_AHB_MTX_AXI_FREQ_ALLOW          ( CTL_BASE_AP_AHB + 0x304C )
#define REG_AP_AHB_M1_LPC                      ( CTL_BASE_AP_AHB + 0x3064 )
#define REG_AP_AHB_M2_LPC                      ( CTL_BASE_AP_AHB + 0x3068 )
#define REG_AP_AHB_M3_LPC                      ( CTL_BASE_AP_AHB + 0x306C )
#define REG_AP_AHB_M4_LPC                      ( CTL_BASE_AP_AHB + 0x3070 )
#define REG_AP_AHB_M5_LPC                      ( CTL_BASE_AP_AHB + 0x3074 )
#define REG_AP_AHB_M6_LPC                      ( CTL_BASE_AP_AHB + 0x3078 )
#define REG_AP_AHB_M7_LPC                      ( CTL_BASE_AP_AHB + 0x307C )
#define REG_AP_AHB_M8_LPC                      ( CTL_BASE_AP_AHB + 0x3080 )
#define REG_AP_AHB_MAIN_LPC                    ( CTL_BASE_AP_AHB + 0x3088 )
#define REG_AP_AHB_S0_LPC                      ( CTL_BASE_AP_AHB + 0x308C )
#define REG_AP_AHB_S1_LPC                      ( CTL_BASE_AP_AHB + 0x3090 )
#define REG_AP_AHB_S2_LPC                      ( CTL_BASE_AP_AHB + 0x3094 )
#define REG_AP_AHB_S3_LPC                      ( CTL_BASE_AP_AHB + 0x3098 )
#define REG_AP_AHB_S4_LPC                      ( CTL_BASE_AP_AHB + 0x309C )
#define REG_AP_AHB_S5_LPC                      ( CTL_BASE_AP_AHB + 0x30A0 )
#define REG_AP_AHB_M10_LPC                     ( CTL_BASE_AP_AHB + 0x30A4 )
#define REG_AP_AHB_ASYNC_BRIDGE_AP2DDR_LPC     ( CTL_BASE_AP_AHB + 0x30A8 )

/* REG_AP_AHB_AHB_EB */

#define BIT_AP_AHB_NANDC_26M_EB                   BIT(31)
#define BIT_AP_AHB_SDIO2_32K_EB                   BIT(30)
#define BIT_AP_AHB_SDIO1_32K_EB                   BIT(29)
#define BIT_AP_AHB_SDIO0_32K_EB                   BIT(28)
#define BIT_AP_AHB_EMMC_32K_EB                    BIT(27)
#define BIT_AP_AHB_EMMC_EB                        BIT(11)
#define BIT_AP_AHB_SDIO2_EB                       BIT(10)
#define BIT_AP_AHB_SDIO1_EB                       BIT(9)
#define BIT_AP_AHB_SDIO0_EB                       BIT(8)
#define BIT_AP_AHB_NANDC_EB                       BIT(7)
#define BIT_AP_AHB_CE_EB                          BIT(6)
#define BIT_AP_AHB_DMA_EB                         BIT(5)
#define BIT_AP_AHB_OTG_EB                         BIT(4)

/* REG_AP_AHB_AHB_RST */

#define BIT_AP_AHB_EMMC_32K_SOFT_RST              BIT(20)
#define BIT_AP_AHB_SDIO2_32K_SOFT_RST             BIT(19)
#define BIT_AP_AHB_SDIO1_32K_SOFT_RST             BIT(18)
#define BIT_AP_AHB_SDIO0_32K_SOFT_RST             BIT(17)
#define BIT_AP_AHB_CE_SEC_SOFT_RST                BIT(15)
#define BIT_AP_AHB_EMMC_SOFT_RST                  BIT(14)
#define BIT_AP_AHB_SDIO2_SOFT_RST                 BIT(13)
#define BIT_AP_AHB_SDIO1_SOFT_RST                 BIT(12)
#define BIT_AP_AHB_SDIO0_SOFT_RST                 BIT(11)
#define BIT_AP_AHB_NANDC_SOFT_RST                 BIT(10)
#define BIT_AP_AHB_CE_PUB_SOFT_RST                BIT(9)
#define BIT_AP_AHB_DMA_SOFT_RST                   BIT(8)
#define BIT_AP_AHB_OTG_UTMI_SOFT_RST              BIT(5)
#define BIT_AP_AHB_OTG_SOFT_RST                   BIT(4)

/* REG_AP_AHB_AP_SYS_FORCE_SLEEP_CFG */

#define BIT_AP_AHB_RESERVED3_REG(x)               (((x) & 0x7FFFFF) << 9)
#define BIT_AP_AHB_CGM_AP_APB_SEL_SLOW(x)         (((x) & 0x3) << 7)
#define BIT_AP_AHB_AP_DOZE_SLEEP_SLOW_DOWN_EN     BIT(6)
#define BIT_AP_AHB_MCU_SLEEP_FOLLOW_CA53_EN       BIT(5)
#define BIT_AP_AHB_MCU_CORE_SLEEP                 BIT(4)
#define BIT_AP_AHB_DMA_ACT_LIGHT_EN               BIT(3)
#define BIT_AP_AHB_AP_PERI_FORCE_ON               BIT(2)
#define BIT_AP_AHB_AP_PERI_FORCE_SLP              BIT(1)
#define BIT_AP_AHB_AP_APB_SLEEP                   BIT(0)

/* REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG */

#define BIT_AP_AHB_CACTIVE_SLV3_WAKEUP_EN         BIT(10)
#define BIT_AP_AHB_AP_CLK_GATE_LPC_BYP            BIT(8)
#define BIT_AP_AHB_LP_AUTO_CTRL_EN                BIT(7)
#define BIT_AP_AHB_AP_MAINMTX_LP_DISABLE          BIT(6)

/* REG_AP_AHB_RESERVED0_REG */

#define BIT_AP_AHB_RESERVED0_REG(x)               (((x) & 0x3FFFFFFF) << 2)
#define BIT_AP_AHB_CE_EB2                         BIT(1)
#define BIT_AP_AHB_DMA_EB2                        BIT(0)

/* REG_AP_AHB_RESERVED1_REG */

#define BIT_AP_AHB_RESERVED1_REG(x)               (((x) & 0xFFFFFFFF))

/* REG_AP_AHB_RESERVED2_REG */

#define BIT_AP_AHB_RESERVED2_REG(x)               (((x) & 0xFFFFFFFF))

/* REG_AP_AHB_AP_MTX_WQOS_CFG */

#define BIT_AP_AHB_AWQOS_M10(x)                   (((x) & 0xF) << 28)
#define BIT_AP_AHB_AWQOS_M8(x)                    (((x) & 0xF) << 24)
#define BIT_AP_AHB_AWQOS_M7(x)                    (((x) & 0xF) << 20)
#define BIT_AP_AHB_AWQOS_M6(x)                    (((x) & 0xF) << 16)
#define BIT_AP_AHB_AWQOS_M5(x)                    (((x) & 0xF) << 12)
#define BIT_AP_AHB_AWQOS_M4(x)                    (((x) & 0xF) << 8)
#define BIT_AP_AHB_AWQOS_M3(x)                    (((x) & 0xF) << 4)
#define BIT_AP_AHB_AWQOS_M2(x)                    (((x) & 0xF))

/* REG_AP_AHB_AP_MTX_RQOS_CFG */

#define BIT_AP_AHB_ARQOS_M10(x)                   (((x) & 0xF) << 28)
#define BIT_AP_AHB_ARQOS_M8(x)                    (((x) & 0xF) << 24)
#define BIT_AP_AHB_ARQOS_M7(x)                    (((x) & 0xF) << 20)
#define BIT_AP_AHB_ARQOS_M6(x)                    (((x) & 0xF) << 16)
#define BIT_AP_AHB_ARQOS_M5(x)                    (((x) & 0xF) << 12)
#define BIT_AP_AHB_ARQOS_M4(x)                    (((x) & 0xF) << 8)
#define BIT_AP_AHB_ARQOS_M3(x)                    (((x) & 0xF) << 4)
#define BIT_AP_AHB_ARQOS_M2(x)                    (((x) & 0xF))

/* REG_AP_AHB_AP_QOS_CFG */

#define BIT_AP_AHB_ARQOS_THRESHHOLD(x)            (((x) & 0xF) << 4)
#define BIT_AP_AHB_AWQOS_THRESHHOLD(x)            (((x) & 0xF))

/* REG_AP_AHB_AP_URGENCY_BYPASS_ADDRESS */

#define BIT_AP_AHB_URGENCY_BYPASS_M10_RD_ADDRESS  BIT(15)
#define BIT_AP_AHB_URGENCY_BYPASS_M8_RD_ADDRESS   BIT(14)
#define BIT_AP_AHB_URGENCY_BYPASS_M7_RD_ADDRESS   BIT(13)
#define BIT_AP_AHB_URGENCY_BYPASS_M6_RD_ADDRESS   BIT(12)
#define BIT_AP_AHB_URGENCY_BYPASS_M5_RD_ADDRESS   BIT(11)
#define BIT_AP_AHB_URGENCY_BYPASS_M4_RD_ADDRESS   BIT(10)
#define BIT_AP_AHB_URGENCY_BYPASS_M3_RD_ADDRESS   BIT(9)
#define BIT_AP_AHB_URGENCY_BYPASS_M2_RD_ADDRESS   BIT(8)
#define BIT_AP_AHB_URGENCY_BYPASS_M10_WR_ADDRESS  BIT(7)
#define BIT_AP_AHB_URGENCY_BYPASS_M8_WR_ADDRESS   BIT(6)
#define BIT_AP_AHB_URGENCY_BYPASS_M7_WR_ADDRESS   BIT(5)
#define BIT_AP_AHB_URGENCY_BYPASS_M6_WR_ADDRESS   BIT(4)
#define BIT_AP_AHB_URGENCY_BYPASS_M5_WR_ADDRESS   BIT(3)
#define BIT_AP_AHB_URGENCY_BYPASS_M4_WR_ADDRESS   BIT(2)
#define BIT_AP_AHB_URGENCY_BYPASS_M3_WR_ADDRESS   BIT(1)
#define BIT_AP_AHB_URGENCY_BYPASS_M2_WR_ADDRESS   BIT(0)

/* REG_AP_AHB_AP_FRC_URGENCY */

#define BIT_AP_AHB_FRC_M10_RD_URGENCY             BIT(15)
#define BIT_AP_AHB_FRC_M8_RD_URGENCY              BIT(14)
#define BIT_AP_AHB_FRC_M7_RD_URGENCY              BIT(13)
#define BIT_AP_AHB_FRC_M6_RD_URGENCY              BIT(12)
#define BIT_AP_AHB_FRC_M5_RD_URGENCY              BIT(11)
#define BIT_AP_AHB_FRC_M4_RD_URGENCY              BIT(10)
#define BIT_AP_AHB_FRC_M3_RD_URGENCY              BIT(9)
#define BIT_AP_AHB_FRC_M2_RD_URGENCY              BIT(8)
#define BIT_AP_AHB_FRC_M10_WR_URGENCY             BIT(7)
#define BIT_AP_AHB_FRC_M8_WR_URGENCY              BIT(6)
#define BIT_AP_AHB_FRC_M7_WR_URGENCY              BIT(5)
#define BIT_AP_AHB_FRC_M6_WR_URGENCY              BIT(4)
#define BIT_AP_AHB_FRC_M5_WR_URGENCY              BIT(3)
#define BIT_AP_AHB_FRC_M4_WR_URGENCY              BIT(2)
#define BIT_AP_AHB_FRC_M3_WR_URGENCY              BIT(1)
#define BIT_AP_AHB_FRC_M2_WR_URGENCY              BIT(0)

/* REG_AP_AHB_OTG_PHY_TUNE */


/* REG_AP_AHB_OTG_PHY_TEST */

#define BIT_AP_AHB_OTG_VBUS_VALID_PHYREG          BIT(28)
#define BIT_AP_AHB_OTG_VBUS_VALID_PHYREG_SEL      BIT(27)

/* REG_AP_AHB_OTG_PHY_CTRL */

#define BIT_AP_AHB_USB2_CON_TESTMODE              BIT(31)
#define BIT_AP_AHB_UTMI_WIDTH_SEL                 BIT(30)

/* REG_AP_AHB_OTG_CTRL1 */


/* REG_AP_AHB_MST_FRC_LSLP */

#define BIT_AP_AHB_SLV3_FRC_LSLP                  BIT(11)
#define BIT_AP_AHB_MST10_FRC_LSLP                 BIT(10)
#define BIT_AP_AHB_MST8_FRC_LSLP                  BIT(8)
#define BIT_AP_AHB_MST7_FRC_LSLP                  BIT(7)
#define BIT_AP_AHB_MST6_FRC_LSLP                  BIT(6)
#define BIT_AP_AHB_MST5_FRC_LSLP                  BIT(5)
#define BIT_AP_AHB_MST4_FRC_LSLP                  BIT(4)
#define BIT_AP_AHB_MST3_FRC_LSLP                  BIT(3)
#define BIT_AP_AHB_MST2_FRC_LSLP                  BIT(2)
#define BIT_AP_AHB_MST1_FRC_LSLP                  BIT(1)

/* REG_AP_AHB_MTX_LSLP_LPC_BYPASS */

#define BIT_AP_AHB_LIGHT_S3_LPC_BYPASS            BIT(11)
#define BIT_AP_AHB_LIGHT_M10_LPC_BYPASS           BIT(10)
#define BIT_AP_AHB_LIGHT_M8_LPC_BYPASS            BIT(8)
#define BIT_AP_AHB_LIGHT_M7_LPC_BYPASS            BIT(7)
#define BIT_AP_AHB_LIGHT_M6_LPC_BYPASS            BIT(6)
#define BIT_AP_AHB_LIGHT_M5_LPC_BYPASS            BIT(5)
#define BIT_AP_AHB_LIGHT_M4_LPC_BYPASS            BIT(4)
#define BIT_AP_AHB_LIGHT_M3_LPC_BYPASS            BIT(3)
#define BIT_AP_AHB_LIGHT_M2_LPC_BYPASS            BIT(2)
#define BIT_AP_AHB_LIGHT_M1_LPC_BYPASS            BIT(1)

/* REG_AP_AHB_MST_PUB_FRC_DSLP */

#define BIT_AP_AHB_MST10_PUB_FRC_DSLP             BIT(10)
#define BIT_AP_AHB_MST8_PUB_FRC_DSLP              BIT(8)
#define BIT_AP_AHB_MST7_PUB_FRC_DSLP              BIT(7)
#define BIT_AP_AHB_MST6_PUB_FRC_DSLP              BIT(6)
#define BIT_AP_AHB_MST5_PUB_FRC_DSLP              BIT(5)
#define BIT_AP_AHB_MST4_PUB_FRC_DSLP              BIT(4)
#define BIT_AP_AHB_MST3_PUB_FRC_DSLP              BIT(3)
#define BIT_AP_AHB_MST2_PUB_FRC_DSLP              BIT(2)
#define BIT_AP_AHB_MST1_PUB_FRC_DSLP              BIT(1)

/* REG_AP_AHB_MTX_PUB_DSLP_LPC_BYPASS */

#define BIT_AP_AHB_PUB_DSLP_S3_LPC_BYPASS         BIT(11)
#define BIT_AP_AHB_PUB_DSLP_M10_LPC_BYPASS        BIT(10)
#define BIT_AP_AHB_PUB_DSLP_M8_LPC_BYPASS         BIT(8)
#define BIT_AP_AHB_PUB_DSLP_M7_LPC_BYPASS         BIT(7)
#define BIT_AP_AHB_PUB_DSLP_M6_LPC_BYPASS         BIT(6)
#define BIT_AP_AHB_PUB_DSLP_M5_LPC_BYPASS         BIT(5)
#define BIT_AP_AHB_PUB_DSLP_M4_LPC_BYPASS         BIT(4)
#define BIT_AP_AHB_PUB_DSLP_M3_LPC_BYPASS         BIT(3)
#define BIT_AP_AHB_PUB_DSLP_M2_LPC_BYPASS         BIT(2)
#define BIT_AP_AHB_PUB_DSLP_M1_LPC_BYPASS         BIT(1)

/* REG_AP_AHB_MTX_FRC_DOZE_SLEEP */

#define BIT_AP_AHB_M10_FRC_DOZE                   BIT(15)
#define BIT_AP_AHB_M8_FRC_DOZE                    BIT(14)
#define BIT_AP_AHB_M7_FRC_DOZE                    BIT(13)
#define BIT_AP_AHB_M6_FRC_DOZE                    BIT(12)
#define BIT_AP_AHB_M5_FRC_DOZE                    BIT(11)
#define BIT_AP_AHB_M4_FRC_DOZE                    BIT(10)
#define BIT_AP_AHB_M3_FRC_DOZE                    BIT(9)
#define BIT_AP_AHB_M2_FRC_DOZE                    BIT(8)
#define BIT_AP_AHB_M1_FRC_DOZE                    BIT(7)
#define BIT_AP_AHB_MAIN_FRC_DOZE                  BIT(6)
#define BIT_AP_AHB_S5_FRC_DOZE                    BIT(5)
#define BIT_AP_AHB_S4_FRC_DOZE                    BIT(4)
#define BIT_AP_AHB_S3_FRC_DOZE                    BIT(3)
#define BIT_AP_AHB_S2_FRC_DOZE                    BIT(2)
#define BIT_AP_AHB_S1_FRC_DOZE                    BIT(1)
#define BIT_AP_AHB_S0_FRC_DOZE                    BIT(0)

/* REG_AP_AHB_MTX_DOZE_LPC_BYPASS */

#define BIT_AP_AHB_DOZE_M10_LPC_BYPASS            BIT(15)
#define BIT_AP_AHB_DOZE_M8_LPC_BYPASS             BIT(14)
#define BIT_AP_AHB_DOZE_M7_LPC_BYPASS             BIT(13)
#define BIT_AP_AHB_DOZE_M6_LPC_BYPASS             BIT(12)
#define BIT_AP_AHB_DOZE_M5_LPC_BYPASS             BIT(11)
#define BIT_AP_AHB_DOZE_M4_LPC_BYPASS             BIT(10)
#define BIT_AP_AHB_DOZE_M3_LPC_BYPASS             BIT(9)
#define BIT_AP_AHB_DOZE_M2_LPC_BYPASS             BIT(8)
#define BIT_AP_AHB_DOZE_M1_LPC_BYPASS             BIT(7)
#define BIT_AP_AHB_DOZE_MAIN_LPC_BYPASS           BIT(6)
#define BIT_AP_AHB_DOZE_S5_LPC_BYPASS             BIT(5)
#define BIT_AP_AHB_DOZE_S4_LPC_BYPASS             BIT(4)
#define BIT_AP_AHB_DOZE_S3_LPC_BYPASS             BIT(3)
#define BIT_AP_AHB_DOZE_S2_LPC_BYPASS             BIT(2)
#define BIT_AP_AHB_DOZE_S1_LPC_BYPASS             BIT(1)
#define BIT_AP_AHB_DOZE_S0_LPC_BYPASS             BIT(0)

/* REG_AP_AHB_MTX_AXI_FREQ_ALLOW */

#define BIT_AP_AHB_M10_AXI_FREQ_ALLOW(x)          (((x) & 0x7) << 24)
#define BIT_AP_AHB_M8_AXI_FREQ_ALLOW(x)           (((x) & 0x7) << 21)
#define BIT_AP_AHB_M7_AXI_FREQ_ALLOW(x)           (((x) & 0x7) << 18)
#define BIT_AP_AHB_M6_AXI_FREQ_ALLOW(x)           (((x) & 0x7) << 15)
#define BIT_AP_AHB_M5_AXI_FREQ_ALLOW(x)           (((x) & 0x7) << 12)
#define BIT_AP_AHB_M4_AXI_FREQ_ALLOW(x)           (((x) & 0x7) << 9)
#define BIT_AP_AHB_M3_AXI_FREQ_ALLOW(x)           (((x) & 0x7) << 6)
#define BIT_AP_AHB_M2_AXI_FREQ_ALLOW(x)           (((x) & 0x7) << 3)
#define BIT_AP_AHB_M1_AXI_FREQ_ALLOW(x)           (((x) & 0x7))

/* REG_AP_AHB_M1_LPC */

#define BIT_AP_AHB_M1_LP_EB                       BIT(16)
#define BIT_AP_AHB_M1_LP_NUM(x)                   (((x) & 0xFFFF))

/* REG_AP_AHB_M2_LPC */

#define BIT_AP_AHB_M2_LP_FORCE                    BIT(17)
#define BIT_AP_AHB_M2_LP_EB                       BIT(16)
#define BIT_AP_AHB_M2_LP_NUM(x)                   (((x) & 0xFFFF))

/* REG_AP_AHB_M3_LPC */

#define BIT_AP_AHB_M3_LP_FORCE                    BIT(17)
#define BIT_AP_AHB_M3_LP_EB                       BIT(16)
#define BIT_AP_AHB_M3_LP_NUM(x)                   (((x) & 0xFFFF))

/* REG_AP_AHB_M4_LPC */

#define BIT_AP_AHB_M4_LP_FORCE                    BIT(17)
#define BIT_AP_AHB_M4_LP_EB                       BIT(16)
#define BIT_AP_AHB_M4_LP_NUM(x)                   (((x) & 0xFFFF))

/* REG_AP_AHB_M5_LPC */

#define BIT_AP_AHB_M5_LP_FORCE                    BIT(17)
#define BIT_AP_AHB_M5_LP_EB                       BIT(16)
#define BIT_AP_AHB_M5_LP_NUM(x)                   (((x) & 0xFFFF))

/* REG_AP_AHB_M6_LPC */

#define BIT_AP_AHB_M6_LP_FORCE                    BIT(17)
#define BIT_AP_AHB_M6_LP_EB                       BIT(16)
#define BIT_AP_AHB_M6_LP_NUM(x)                   (((x) & 0xFFFF))

/* REG_AP_AHB_M7_LPC */

#define BIT_AP_AHB_M7_LP_FORCE                    BIT(17)
#define BIT_AP_AHB_M7_LP_EB                       BIT(16)
#define BIT_AP_AHB_M7_LP_NUM(x)                   (((x) & 0xFFFF))

/* REG_AP_AHB_M8_LPC */

#define BIT_AP_AHB_M8_LP_FORCE                    BIT(17)
#define BIT_AP_AHB_M8_LP_EB                       BIT(16)
#define BIT_AP_AHB_M8_LP_NUM(x)                   (((x) & 0xFFFF))

/* REG_AP_AHB_MAIN_LPC */

#define BIT_AP_AHB_MAIN_LP_EB                     BIT(16)
#define BIT_AP_AHB_MAIN_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_AHB_S0_LPC */

#define BIT_AP_AHB_S0_LP_EB                       BIT(16)
#define BIT_AP_AHB_S0_LP_NUM(x)                   (((x) & 0xFFFF))

/* REG_AP_AHB_S1_LPC */

#define BIT_AP_AHB_S1_LP_FORCE                    BIT(17)
#define BIT_AP_AHB_S1_LP_EB                       BIT(16)
#define BIT_AP_AHB_S1_LP_NUM(x)                   (((x) & 0xFFFF))

/* REG_AP_AHB_S2_LPC */

#define BIT_AP_AHB_S2_LP_FORCE                    BIT(17)
#define BIT_AP_AHB_S2_LP_EB                       BIT(16)
#define BIT_AP_AHB_S2_LP_NUM(x)                   (((x) & 0xFFFF))

/* REG_AP_AHB_S3_LPC */

#define BIT_AP_AHB_S3_LP_FORCE                    BIT(17)
#define BIT_AP_AHB_S3_LP_EB                       BIT(16)
#define BIT_AP_AHB_S3_LP_NUM(x)                   (((x) & 0xFFFF))

/* REG_AP_AHB_S4_LPC */

#define BIT_AP_AHB_S4_LP_FORCE                    BIT(17)
#define BIT_AP_AHB_S4_LP_EB                       BIT(16)
#define BIT_AP_AHB_S4_LP_NUM(x)                   (((x) & 0xFFFF))

/* REG_AP_AHB_S5_LPC */

#define BIT_AP_AHB_S5_LP_FORCE                    BIT(17)
#define BIT_AP_AHB_S5_LP_EB                       BIT(16)
#define BIT_AP_AHB_S5_LP_NUM(x)                   (((x) & 0xFFFF))

/* REG_AP_AHB_M10_LPC */

#define BIT_AP_AHB_M10_LP_FORCE                   BIT(17)
#define BIT_AP_AHB_M10_LP_EB                      BIT(16)
#define BIT_AP_AHB_M10_LP_NUM(x)                  (((x) & 0xFFFF))

/* REG_AP_AHB_ASYNC_BRIDGE_AP2DDR_LPC */

#define BIT_AP_AHB_ASYNC_BRIDGE_AP2DDR_LP_FORCE   BIT(17)
#define BIT_AP_AHB_ASYNC_BRIDGE_AP2DDR_LP_EB      BIT(16)
#define BIT_AP_AHB_ASYNC_BRIDGE_AP2DDR_LP_NUM(x)  (((x) & 0xFFFF))


#endif /* AP_AHB_H */

