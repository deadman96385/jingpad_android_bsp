/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2017-05-30 15:03:06
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
#define REG_AP_AHB_AP_MTX_WQOS_CFG             ( CTL_BASE_AP_AHB + 0x3008 )
#define REG_AP_AHB_AP_MTX_RQOS_CFG             ( CTL_BASE_AP_AHB + 0x3010 )
#define REG_AP_AHB_AP_QOS_CFG                  ( CTL_BASE_AP_AHB + 0x301C )
#define REG_AP_AHB_OTG_PHY_TUNE                ( CTL_BASE_AP_AHB + 0x3020 )
#define REG_AP_AHB_OTG_PHY_TEST                ( CTL_BASE_AP_AHB + 0x3024 )
#define REG_AP_AHB_OTG_PHY_CTRL                ( CTL_BASE_AP_AHB + 0x3028 )
#define REG_AP_AHB_OTG_CTRL0                   ( CTL_BASE_AP_AHB + 0x302C )
#define REG_AP_AHB_OTG_CTRL1                   ( CTL_BASE_AP_AHB + 0x3030 )
#define REG_AP_AHB_MST_FRC_LSLP                ( CTL_BASE_AP_AHB + 0x3034 )
#define REG_AP_AHB_MST_PUB_FRC_DSLP            ( CTL_BASE_AP_AHB + 0x3038 )
#define REG_AP_AHB_CE_EFUSE_STATUS             ( CTL_BASE_AP_AHB + 0x303C )
#define REG_AP_AHB_M1_LPC                      ( CTL_BASE_AP_AHB + 0x3064 )
#define REG_AP_AHB_M2_LPC                      ( CTL_BASE_AP_AHB + 0x3068 )
#define REG_AP_AHB_M3_LPC                      ( CTL_BASE_AP_AHB + 0x306C )
#define REG_AP_AHB_M4_LPC                      ( CTL_BASE_AP_AHB + 0x3070 )
#define REG_AP_AHB_M5_LPC                      ( CTL_BASE_AP_AHB + 0x3074 )
#define REG_AP_AHB_M6_LPC                      ( CTL_BASE_AP_AHB + 0x3078 )
#define REG_AP_AHB_M7_LPC                      ( CTL_BASE_AP_AHB + 0x307C )
#define REG_AP_AHB_M8_LPC                      ( CTL_BASE_AP_AHB + 0x3080 )
#define REG_AP_AHB_M9_LPC                      ( CTL_BASE_AP_AHB + 0x3084 )
#define REG_AP_AHB_MAIN_LPC                    ( CTL_BASE_AP_AHB + 0x3088 )
#define REG_AP_AHB_S0_LPC                      ( CTL_BASE_AP_AHB + 0x308C )
#define REG_AP_AHB_S1_LPC                      ( CTL_BASE_AP_AHB + 0x3090 )
#define REG_AP_AHB_S2_LPC                      ( CTL_BASE_AP_AHB + 0x3094 )
#define REG_AP_AHB_S3_LPC                      ( CTL_BASE_AP_AHB + 0x3098 )
#define REG_AP_AHB_S4_LPC                      ( CTL_BASE_AP_AHB + 0x309C )
#define REG_AP_AHB_S5_LPC                      ( CTL_BASE_AP_AHB + 0x30A0 )
#define REG_AP_AHB_M10_LPC                     ( CTL_BASE_AP_AHB + 0x30A4 )
#define REG_AP_AHB_DISP_GSP_FRC_LSLP           ( CTL_BASE_AP_AHB + 0x30A8 )
#define REG_AP_AHB_DISP_M0_LPC                 ( CTL_BASE_AP_AHB + 0x30AC )
#define REG_AP_AHB_DISP_M1_LPC                 ( CTL_BASE_AP_AHB + 0x30B0 )
#define REG_AP_AHB_DISP_S0_LPC                 ( CTL_BASE_AP_AHB + 0x30B8 )
#define REG_AP_AHB_GSP_M0_LPC                  ( CTL_BASE_AP_AHB + 0x30BC )

/* REG_AP_AHB_AHB_EB */

#define BIT_AP_AHB_SDIO2_32K_EB                BIT(30)
#define BIT_AP_AHB_SDIO1_32K_EB                BIT(29)
#define BIT_AP_AHB_SDIO0_32K_EB                BIT(28)
#define BIT_AP_AHB_EMMC_32K_EB                 BIT(27)
#define BIT_AP_AHB_CE_EFUSE_EB                 BIT(23)
#define BIT_AP_AHB_CE_SEC_EB                   BIT(12)
#define BIT_AP_AHB_EMMC_EB                     BIT(11)
#define BIT_AP_AHB_SDIO2_EB                    BIT(10)
#define BIT_AP_AHB_SDIO1_EB                    BIT(9)
#define BIT_AP_AHB_SDIO0_EB                    BIT(8)
#define BIT_AP_AHB_NANDC_EB                    BIT(7)
#define BIT_AP_AHB_CE_PUB_EB                   BIT(6)
#define BIT_AP_AHB_DMA_EB                      BIT(5)
#define BIT_AP_AHB_OTG_EB                      BIT(4)
#define BIT_AP_AHB_GSP_EB                      BIT(3)
#define BIT_AP_AHB_DISPC_EB                    BIT(1)
#define BIT_AP_AHB_DSI_EB                      BIT(0)

/* REG_AP_AHB_AHB_RST */

#define BIT_AP_AHB_CE_EFUSE_SOFT_RST           BIT(29)
#define BIT_AP_AHB_EMMC_32K_SOFT_RST           BIT(20)
#define BIT_AP_AHB_SDIO2_32K_SOFT_RST          BIT(19)
#define BIT_AP_AHB_SDIO1_32K_SOFT_RST          BIT(18)
#define BIT_AP_AHB_SDIO0_32K_SOFT_RST          BIT(17)
#define BIT_AP_AHB_CE_SEC_SOFT_RST             BIT(15)
#define BIT_AP_AHB_EMMC_SOFT_RST               BIT(14)
#define BIT_AP_AHB_SDIO2_SOFT_RST              BIT(13)
#define BIT_AP_AHB_SDIO1_SOFT_RST              BIT(12)
#define BIT_AP_AHB_SDIO0_SOFT_RST              BIT(11)
#define BIT_AP_AHB_NANDC_SOFT_RST              BIT(10)
#define BIT_AP_AHB_CE_PUB_SOFT_RST             BIT(9)
#define BIT_AP_AHB_DMA_SOFT_RST                BIT(8)
#define BIT_AP_AHB_OTG_UTMI_SOFT_RST           BIT(5)
#define BIT_AP_AHB_OTG_SOFT_RST                BIT(4)
#define BIT_AP_AHB_GSP_SOFT_RST                BIT(3)
#define BIT_AP_AHB_DISP_MTX_SOFT_RST           BIT(2)
#define BIT_AP_AHB_DISPC_SOFT_RST              BIT(1)
#define BIT_AP_AHB_DSI_SOFT_RST                BIT(0)

/* REG_AP_AHB_AP_SYS_FORCE_SLEEP_CFG */

#define BIT_AP_AHB_FRC_DISP_LIGHT              BIT(7)
#define BIT_AP_AHB_FRC_GSP_LIGHT               BIT(6)
#define BIT_AP_AHB_MCU_SLEEP_FOLLOW_CA53_EN    BIT(5)
#define BIT_AP_AHB_MCU_CORE_SLEEP              BIT(4)
#define BIT_AP_AHB_DMA_ACT_LIGHT_EN            BIT(3)
#define BIT_AP_AHB_AP_PERI_FORCE_ON            BIT(2)
#define BIT_AP_AHB_AP_PERI_FORCE_SLP           BIT(1)
#define BIT_AP_AHB_AP_APB_SLEEP                BIT(0)

/* REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG */

#define BIT_AP_AHB_CACTIVE_SLV3_WAKEUP_EN      BIT(10)
#define BIT_AP_AHB_AP_CLK_GATE_LPC_BYP         BIT(8)
#define BIT_AP_AHB_LP_AUTO_CTRL_EN             BIT(7)
#define BIT_AP_AHB_AP_MAINMTX_LP_DISABLE       BIT(6)
#define BIT_AP_AHB_DISP_CLK_GATE_LPC_BYP       BIT(5)
#define BIT_AP_AHB_DISP_LP_AUTO_CTRL_EN        BIT(4)
#define BIT_AP_AHB_DISP_MAINMTX_LP_DISABLE     BIT(3)
#define BIT_AP_AHB_GSP_CLK_GATE_LPC_BYP        BIT(2)
#define BIT_AP_AHB_GSP_LP_AUTO_CTRL_EN         BIT(1)
#define BIT_AP_AHB_GSP_MAINMTX_LP_DISABLE      BIT(0)

/* REG_AP_AHB_RESERVED0_REG */

#define BIT_AP_AHB_RESERVED0_REG(x)            (((x) & 0xFFFFFFFF))

/* REG_AP_AHB_RESERVED1_REG */

#define BIT_AP_AHB_RESERVED1_REG(x)            (((x) & 0xFFFFFFFF))

/* REG_AP_AHB_RESERVED2_REG */

#define BIT_AP_AHB_RESERVED2_REG(x)            (((x) & 0xFFFFFFFF))

/* REG_AP_AHB_AP_MTX_WQOS_CFG */

#define BIT_AP_AHB_AWQOS_M9(x)                 (((x) & 0xF) << 28)
#define BIT_AP_AHB_AWQOS_M8(x)                 (((x) & 0xF) << 24)
#define BIT_AP_AHB_AWQOS_M7(x)                 (((x) & 0xF) << 20)
#define BIT_AP_AHB_AWQOS_M6(x)                 (((x) & 0xF) << 16)
#define BIT_AP_AHB_AWQOS_M5(x)                 (((x) & 0xF) << 12)
#define BIT_AP_AHB_AWQOS_M4(x)                 (((x) & 0xF) << 8)
#define BIT_AP_AHB_AWQOS_M3(x)                 (((x) & 0xF) << 4)
#define BIT_AP_AHB_AWQOS_M2(x)                 (((x) & 0xF))

/* REG_AP_AHB_AP_MTX_RQOS_CFG */

#define BIT_AP_AHB_ARQOS_M9(x)                 (((x) & 0xF) << 28)
#define BIT_AP_AHB_ARQOS_M8(x)                 (((x) & 0xF) << 24)
#define BIT_AP_AHB_ARQOS_M7(x)                 (((x) & 0xF) << 20)
#define BIT_AP_AHB_ARQOS_M6(x)                 (((x) & 0xF) << 16)
#define BIT_AP_AHB_ARQOS_M5(x)                 (((x) & 0xF) << 12)
#define BIT_AP_AHB_ARQOS_M4(x)                 (((x) & 0xF) << 8)
#define BIT_AP_AHB_ARQOS_M3(x)                 (((x) & 0xF) << 4)
#define BIT_AP_AHB_ARQOS_M2(x)                 (((x) & 0xF))

/* REG_AP_AHB_AP_QOS_CFG */

#define BIT_AP_AHB_ARQOS_TMC(x)                (((x) & 0xF) << 20)
#define BIT_AP_AHB_AWQOS_TMC(x)                (((x) & 0xF) << 16)
#define BIT_AP_AHB_ARQOS_M10(x)                (((x) & 0xF) << 4)
#define BIT_AP_AHB_AWQOS_M10(x)                (((x) & 0xF))

/* REG_AP_AHB_OTG_PHY_TUNE */


/* REG_AP_AHB_OTG_PHY_TEST */

#define BIT_AP_AHB_OTG_VBUS_VALID_PHYREG       BIT(28)
#define BIT_AP_AHB_OTG_VBUS_VALID_PHYREG_SEL   BIT(27)

/* REG_AP_AHB_OTG_PHY_CTRL */

#define BIT_AP_AHB_USB2_CON_TESTMODE           BIT(31)
#define BIT_AP_AHB_UTMI_WIDTH_SEL              BIT(30)
#define BIT_AP_AHB_USB2_PHY_IDDIG              BIT(3)

/* REG_AP_AHB_OTG_CTRL0 */


/* REG_AP_AHB_OTG_CTRL1 */


/* REG_AP_AHB_MST_FRC_LSLP */

#define BIT_AP_AHB_SLV3_FRC_LSLP               BIT(11)
#define BIT_AP_AHB_MST10_FRC_LSLP              BIT(10)
#define BIT_AP_AHB_MST9_FRC_LSLP               BIT(9)
#define BIT_AP_AHB_MST8_FRC_LSLP               BIT(8)
#define BIT_AP_AHB_MST7_FRC_LSLP               BIT(7)
#define BIT_AP_AHB_MST6_FRC_LSLP               BIT(6)
#define BIT_AP_AHB_MST5_FRC_LSLP               BIT(5)
#define BIT_AP_AHB_MST4_FRC_LSLP               BIT(4)
#define BIT_AP_AHB_MST3_FRC_LSLP               BIT(3)
#define BIT_AP_AHB_MST2_FRC_LSLP               BIT(2)
#define BIT_AP_AHB_MST1_FRC_LSLP               BIT(1)

/* REG_AP_AHB_MST_PUB_FRC_DSLP */

#define BIT_AP_AHB_MST10_PUB_FRC_DSLP          BIT(10)
#define BIT_AP_AHB_MST9_PUB_FRC_DSLP           BIT(9)
#define BIT_AP_AHB_MST8_PUB_FRC_DSLP           BIT(8)
#define BIT_AP_AHB_MST7_PUB_FRC_DSLP           BIT(7)
#define BIT_AP_AHB_MST6_PUB_FRC_DSLP           BIT(6)
#define BIT_AP_AHB_MST5_PUB_FRC_DSLP           BIT(5)
#define BIT_AP_AHB_MST4_PUB_FRC_DSLP           BIT(4)
#define BIT_AP_AHB_MST3_PUB_FRC_DSLP           BIT(3)
#define BIT_AP_AHB_MST2_PUB_FRC_DSLP           BIT(2)
#define BIT_AP_AHB_MST1_PUB_FRC_DSLP           BIT(1)

/* REG_AP_AHB_CE_EFUSE_STATUS */

#define BIT_AP_AHB_EFUSE_PWON_RD_END_FLAG      BIT(0)

/* REG_AP_AHB_M1_LPC */

#define BIT_AP_AHB_M1_LP_ACTIVE_SYNC_SEL       BIT(18)
#define BIT_AP_AHB_M1_LP_EB                    BIT(16)
#define BIT_AP_AHB_M1_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_M2_LPC */

#define BIT_AP_AHB_M2_LP_ACTIVE_SYNC_SEL       BIT(18)
#define BIT_AP_AHB_M2_LP_FORCE                 BIT(17)
#define BIT_AP_AHB_M2_LP_EB                    BIT(16)
#define BIT_AP_AHB_M2_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_M3_LPC */

#define BIT_AP_AHB_M3_LP_ACTIVE_SYNC_SEL       BIT(18)
#define BIT_AP_AHB_M3_LP_FORCE                 BIT(17)
#define BIT_AP_AHB_M3_LP_EB                    BIT(16)
#define BIT_AP_AHB_M3_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_M4_LPC */

#define BIT_AP_AHB_M4_LP_ACTIVE_SYNC_SEL       BIT(18)
#define BIT_AP_AHB_M4_LP_FORCE                 BIT(17)
#define BIT_AP_AHB_M4_LP_EB                    BIT(16)
#define BIT_AP_AHB_M4_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_M5_LPC */

#define BIT_AP_AHB_M5_LP_ACTIVE_SYNC_SEL       BIT(18)
#define BIT_AP_AHB_M5_LP_FORCE                 BIT(17)
#define BIT_AP_AHB_M5_LP_EB                    BIT(16)
#define BIT_AP_AHB_M5_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_M6_LPC */

#define BIT_AP_AHB_M6_LP_ACTIVE_SYNC_SEL       BIT(18)
#define BIT_AP_AHB_M6_LP_FORCE                 BIT(17)
#define BIT_AP_AHB_M6_LP_EB                    BIT(16)
#define BIT_AP_AHB_M6_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_M7_LPC */

#define BIT_AP_AHB_M7_LP_ACTIVE_SYNC_SEL       BIT(18)
#define BIT_AP_AHB_M7_LP_FORCE                 BIT(17)
#define BIT_AP_AHB_M7_LP_EB                    BIT(16)
#define BIT_AP_AHB_M7_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_M8_LPC */

#define BIT_AP_AHB_M8_LP_ACTIVE_SYNC_SEL       BIT(18)
#define BIT_AP_AHB_M8_LP_FORCE                 BIT(17)
#define BIT_AP_AHB_M8_LP_EB                    BIT(16)
#define BIT_AP_AHB_M8_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_M9_LPC */

#define BIT_AP_AHB_M9_LP_ACTIVE_SYNC_SEL       BIT(18)
#define BIT_AP_AHB_M9_LP_FORCE                 BIT(17)
#define BIT_AP_AHB_M9_LP_EB                    BIT(16)
#define BIT_AP_AHB_M9_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_MAIN_LPC */

#define BIT_AP_AHB_MAIN_LP_ACTIVE_SYNC_SEL     BIT(18)
#define BIT_AP_AHB_MAIN_LP_EB                  BIT(16)
#define BIT_AP_AHB_MAIN_LP_NUM(x)              (((x) & 0xFFFF))

/* REG_AP_AHB_S0_LPC */

#define BIT_AP_AHB_S0_LP_ACTIVE_SYNC_SEL       BIT(18)
#define BIT_AP_AHB_S0_LP_EB                    BIT(16)
#define BIT_AP_AHB_S0_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_S1_LPC */

#define BIT_AP_AHB_S1_LP_ACTIVE_SYNC_SEL       BIT(18)
#define BIT_AP_AHB_S1_LP_FORCE                 BIT(17)
#define BIT_AP_AHB_S1_LP_EB                    BIT(16)
#define BIT_AP_AHB_S1_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_S2_LPC */

#define BIT_AP_AHB_S2_LP_ACTIVE_SYNC_SEL       BIT(18)
#define BIT_AP_AHB_S2_LP_FORCE                 BIT(17)
#define BIT_AP_AHB_S2_LP_EB                    BIT(16)
#define BIT_AP_AHB_S2_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_S3_LPC */

#define BIT_AP_AHB_S3_LP_ACTIVE_SYNC_SEL       BIT(18)
#define BIT_AP_AHB_S3_LP_FORCE                 BIT(17)
#define BIT_AP_AHB_S3_LP_EB                    BIT(16)
#define BIT_AP_AHB_S3_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_S4_LPC */

#define BIT_AP_AHB_S4_LP_ACTIVE_SYNC_SEL       BIT(18)
#define BIT_AP_AHB_S4_LP_FORCE                 BIT(17)
#define BIT_AP_AHB_S4_LP_EB                    BIT(16)
#define BIT_AP_AHB_S4_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_S5_LPC */

#define BIT_AP_AHB_S5_LP_ACTIVE_SYNC_SEL       BIT(18)
#define BIT_AP_AHB_S5_LP_FORCE                 BIT(17)
#define BIT_AP_AHB_S5_LP_EB                    BIT(16)
#define BIT_AP_AHB_S5_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_AHB_M10_LPC */

#define BIT_AP_AHB_M10_LP_ACTIVE_SYNC_SEL      BIT(18)
#define BIT_AP_AHB_M10_LP_FORCE                BIT(17)
#define BIT_AP_AHB_M10_LP_EB                   BIT(16)
#define BIT_AP_AHB_M10_LP_NUM(x)               (((x) & 0xFFFF))

/* REG_AP_AHB_DISP_GSP_FRC_LSLP */

#define BIT_AP_AHB_GSP_MST0_FRC_LSLP           BIT(4)
#define BIT_AP_AHB_DISP_SLV0_FRC_LSLP          BIT(3)
#define BIT_AP_AHB_DISP_MST1_FRC_LSLP          BIT(1)

/* REG_AP_AHB_DISP_M0_LPC */

#define BIT_AP_AHB_DISP_M0_LP_ACTIVE_SYNC_SEL  BIT(18)
#define BIT_AP_AHB_DISP_M0_LP_FORCE            BIT(17)
#define BIT_AP_AHB_DISP_M0_LP_EB               BIT(16)
#define BIT_AP_AHB_DISP_M0_LP_NUM(x)           (((x) & 0xFFFF))

/* REG_AP_AHB_DISP_M1_LPC */

#define BIT_AP_AHB_DISP_M1_LP_ACTIVE_SYNC_SEL  BIT(18)
#define BIT_AP_AHB_DISP_M1_LP_FORCE            BIT(17)
#define BIT_AP_AHB_DISP_M1_LP_EB               BIT(16)
#define BIT_AP_AHB_DISP_M1_LP_NUM(x)           (((x) & 0xFFFF))

/* REG_AP_AHB_DISP_S0_LPC */

#define BIT_AP_AHB_DISP_S0_LP_ACTIVE_SYNC_SEL  BIT(18)
#define BIT_AP_AHB_DISP_S0_LP_FORCE            BIT(17)
#define BIT_AP_AHB_DISP_S0_LP_EB               BIT(16)
#define BIT_AP_AHB_DISP_S0_LP_NUM(x)           (((x) & 0xFFFF))

/* REG_AP_AHB_GSP_M0_LPC */

#define BIT_AP_AHB_GSP_M0_LP_ACTIVE_SYNC_SEL   BIT(18)
#define BIT_AP_AHB_GSP_M0_LP_FORCE             BIT(17)
#define BIT_AP_AHB_GSP_M0_LP_EB                BIT(16)
#define BIT_AP_AHB_GSP_M0_LP_NUM(x)            (((x) & 0xFFFF))


#endif /* AP_AHB_H */

