/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _AP_AHB_REG_H
#define _AP_AHB_REG_H

#define CTL_BASE_AP_AHB SPRD_AHB_PHYS


#define REG_AP_AHB_AHB_EB                             ( CTL_BASE_AP_AHB + 0x0000 )
#define REG_AP_AHB_AHB_RST                            ( CTL_BASE_AP_AHB + 0x0004 )
#define REG_AP_AHB_CA7_RST_SET                        ( CTL_BASE_AP_AHB + 0x0008 )
#define REG_AP_AHB_AP_SYS_FORCE_SLEEP_CFG             ( CTL_BASE_AP_AHB + 0x000C )
#define REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG              ( CTL_BASE_AP_AHB + 0x0010 )
#define REG_AP_AHB_HOLDING_PEN                        ( CTL_BASE_AP_AHB + 0x0014 )
#define REG_AP_AHB_JMP_ADDR_CA7_C0                    ( CTL_BASE_AP_AHB + 0x0018 )
#define REG_AP_AHB_JMP_ADDR_CA7_C1                    ( CTL_BASE_AP_AHB + 0x001C )
#define REG_AP_AHB_JMP_ADDR_CA7_C2                    ( CTL_BASE_AP_AHB + 0x0020 )
#define REG_AP_AHB_JMP_ADDR_CA7_C3                    ( CTL_BASE_AP_AHB + 0x0024 )
#define REG_AP_AHB_CA7_C0_PU_LOCK                     ( CTL_BASE_AP_AHB + 0x0028 )
#define REG_AP_AHB_CA7_C1_PU_LOCK                     ( CTL_BASE_AP_AHB + 0x002C )
#define REG_AP_AHB_CA7_C2_PU_LOCK                     ( CTL_BASE_AP_AHB + 0x0030 )
#define REG_AP_AHB_CA7_C3_PU_LOCK                     ( CTL_BASE_AP_AHB + 0x0034 )
#define REG_AP_AHB_CA7_CKG_DIV_CFG                    ( CTL_BASE_AP_AHB + 0x0038 )
#define REG_AP_AHB_MCU_PAUSE                          ( CTL_BASE_AP_AHB + 0x003C )
#define REG_AP_AHB_MISC_CKG_EN                        ( CTL_BASE_AP_AHB + 0x0040 )
#define REG_AP_AHB_CA7_C0_AUTO_FORCE_SHUTDOWN_EN      ( CTL_BASE_AP_AHB + 0x0044 )
#define REG_AP_AHB_CA7_C1_AUTO_FORCE_SHUTDOWN_EN      ( CTL_BASE_AP_AHB + 0x0048 )
#define REG_AP_AHB_CA7_C2_AUTO_FORCE_SHUTDOWN_EN      ( CTL_BASE_AP_AHB + 0x004C )
#define REG_AP_AHB_CA7_C3_AUTO_FORCE_SHUTDOWN_EN      ( CTL_BASE_AP_AHB + 0x0050 )
#define REG_AP_AHB_CA7_CKG_SEL_CFG                    ( CTL_BASE_AP_AHB + 0x0054 )
#define REG_AP_AHB_MST_FRC_LSLP                       ( CTL_BASE_AP_AHB + 0x0058 )
#define REG_AP_AHB_MST_PUB_FRC_DSLP                   ( CTL_BASE_AP_AHB + 0x005C )
#define REG_AP_AHB_M0_LPC                             ( CTL_BASE_AP_AHB + 0x0060 )
#define REG_AP_AHB_M1_LPC                             ( CTL_BASE_AP_AHB + 0x0064 )
#define REG_AP_AHB_M2_LPC                             ( CTL_BASE_AP_AHB + 0x0068 )
#define REG_AP_AHB_M3_LPC                             ( CTL_BASE_AP_AHB + 0x006C )
#define REG_AP_AHB_M4_LPC                             ( CTL_BASE_AP_AHB + 0x0070 )
#define REG_AP_AHB_M5_LPC                             ( CTL_BASE_AP_AHB + 0x0074 )
#define REG_AP_AHB_M6_LPC                             ( CTL_BASE_AP_AHB + 0x0078 )
#define REG_AP_AHB_M7_LPC                             ( CTL_BASE_AP_AHB + 0x007C )
#define REG_AP_AHB_M8_LPC                             ( CTL_BASE_AP_AHB + 0x0080 )
#define REG_AP_AHB_M9_LPC                             ( CTL_BASE_AP_AHB + 0x0084 )
#define REG_AP_AHB_MAIN_LPC                           ( CTL_BASE_AP_AHB + 0x0088 )
#define REG_AP_AHB_S0_LPC                             ( CTL_BASE_AP_AHB + 0x008C )
#define REG_AP_AHB_S1_LPC                             ( CTL_BASE_AP_AHB + 0x0090 )
#define REG_AP_AHB_S2_LPC                             ( CTL_BASE_AP_AHB + 0x0094 )
#define REG_AP_AHB_S3_LPC                             ( CTL_BASE_AP_AHB + 0x0098 )
#define REG_AP_AHB_S4_LPC                             ( CTL_BASE_AP_AHB + 0x009C )
#define REG_AP_AHB_CA7_STANDBY_STATUS                 ( CTL_BASE_AP_AHB + 0x3008 )
#define REG_AP_AHB_LVDS_CFG                           ( CTL_BASE_AP_AHB + 0x3010 )
#define REG_AP_AHB_LVDS_PLL_CFG0                      ( CTL_BASE_AP_AHB + 0x3014 )
#define REG_AP_AHB_LVDS_PLL_CFG1                      ( CTL_BASE_AP_AHB + 0x3018 )
#define REG_AP_AHB_AP_QOS_CFG                         ( CTL_BASE_AP_AHB + 0x301C )
#define REG_AP_AHB_OTG_PHY_TUNE                       ( CTL_BASE_AP_AHB + 0x3020 )
#define REG_AP_AHB_OTG_PHY_TEST                       ( CTL_BASE_AP_AHB + 0x3024 )
#define REG_AP_AHB_OTG_PHY_CTRL                       ( CTL_BASE_AP_AHB + 0x3028 )
#define REG_AP_AHB_OTG_CTRL0                          ( CTL_BASE_AP_AHB + 0x302C )
#define REG_AP_AHB_OTG_CTRL1                          ( CTL_BASE_AP_AHB + 0x3030 )
#define REG_AP_AHB_CHIP_ID                            ( CTL_BASE_AP_AHB + 0x30FC )

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_AHB_EB
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_SDIO2_32K_EB                               BIT(30)
#define BIT_AP_AHB_SDIO1_32K_EB                               BIT(29)
#define BIT_AP_AHB_SDIO0_32K_EB                               BIT(28)
#define BIT_AP_AHB_EMMC_32K_EB                                BIT(27)
#define BIT_AP_AHB_CE_EFUSE_EB                                BIT(23)
#define BIT_AP_AHB_SPINLOCK_EB                                BIT(13)
#define BIT_AP_AHB_CE_SEC_EB                                  BIT(12)
#define BIT_AP_AHB_EMMC_EB                                    BIT(11)
#define BIT_AP_AHB_SDIO2_EB                                   BIT(10)
#define BIT_AP_AHB_SDIO1_EB                                   BIT(9)
#define BIT_AP_AHB_SDIO0_EB                                   BIT(8)
#define BIT_AP_AHB_DRM_EB                                     BIT(7)
#define BIT_AP_AHB_CE_PUB_EB                                  BIT(6)
#define BIT_AP_AHB_DMA_EB                                     BIT(5)
#define BIT_AP_AHB_OTG_EB                                     BIT(4)
#define BIT_AP_AHB_GSP_EB                                     BIT(3)
#define BIT_AP_AHB_DISPC_EB                                   BIT(1)
#define BIT_AP_AHB_DSI_EB                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_AHB_RST
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CE_EFUSE_SOFT_RST                          BIT(29)
#define BIT_AP_AHB_LVDS_SOFT_RST                              BIT(25)
#define BIT_AP_AHB_SPINLOCK_SOFT_RST                          BIT(16)
#define BIT_AP_AHB_CE_SEC_SOFT_RST                            BIT(15)
#define BIT_AP_AHB_EMMC_SOFT_RST                              BIT(14)
#define BIT_AP_AHB_SDIO2_SOFT_RST                             BIT(13)
#define BIT_AP_AHB_SDIO1_SOFT_RST                             BIT(12)
#define BIT_AP_AHB_SDIO0_SOFT_RST                             BIT(11)
#define BIT_AP_AHB_DRM_SOFT_RST                               BIT(10)
#define BIT_AP_AHB_CE_PUB_SOFT_RST                            BIT(9)
#define BIT_AP_AHB_DMA_SOFT_RST                               BIT(8)
#define BIT_AP_AHB_OTG_PHY_SOFT_RST                           BIT(6)
#define BIT_AP_AHB_OTG_UTMI_SOFT_RST                          BIT(5)
#define BIT_AP_AHB_OTG_SOFT_RST                               BIT(4)
#define BIT_AP_AHB_GSP_SOFT_RST                               BIT(3)
#define BIT_AP_AHB_DISP_MTX_SOFT_RST                          BIT(2)
#define BIT_AP_AHB_DISPC_SOFT_RST                             BIT(1)
#define BIT_AP_AHB_DSI_SOFT_RST                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_CA7_RST_SET
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CA7_CS_DBG_SOFT_RST                        BIT(14)
#define BIT_AP_AHB_CA7_L2_SOFT_RST                            BIT(13)
#define BIT_AP_AHB_CA7_SOCDBG_SOFT_RST                        BIT(12)
#define BIT_AP_AHB_CA7_ETM_SOFT_RST(x)                        (((x) & 0xF) << 8)
#define BIT_AP_AHB_CA7_DBG_SOFT_RST(x)                        (((x) & 0xF) << 4)
#define BIT_AP_AHB_CA7_CORE_SOFT_RST(x)                       (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_AP_SYS_FORCE_SLEEP_CFG
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CA7_C3_AUTO_SLP_EN                         BIT(15)
#define BIT_AP_AHB_CA7_C2_AUTO_SLP_EN                         BIT(14)
#define BIT_AP_AHB_CA7_C1_AUTO_SLP_EN                         BIT(13)
#define BIT_AP_AHB_CA7_C0_AUTO_SLP_EN                         BIT(12)
#define BIT_AP_AHB_CA7_C3_WFI_SHUTDOWN_EN                     BIT(11)
#define BIT_AP_AHB_CA7_C2_WFI_SHUTDOWN_EN                     BIT(10)
#define BIT_AP_AHB_CA7_C1_WFI_SHUTDOWN_EN                     BIT(9)
#define BIT_AP_AHB_CA7_C0_WFI_SHUTDOWN_EN                     BIT(8)
#define BIT_AP_AHB_MCU_CA7_C3_SLEEP                           BIT(7)
#define BIT_AP_AHB_MCU_CA7_C2_SLEEP                           BIT(6)
#define BIT_AP_AHB_MCU_CA7_C1_SLEEP                           BIT(5)
#define BIT_AP_AHB_MCU_CA7_C0_SLEEP                           BIT(4)
#define BIT_AP_AHB_AP_PERI_FORCE_ON                           BIT(2)
#define BIT_AP_AHB_AP_PERI_FORCE_SLP                          BIT(1)
#define BIT_AP_AHB_AP_APB_SLEEP                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CACTIVE_SLV3_WAKEUP_EN                     BIT(10)
#define BIT_AP_AHB_GSP_CKG_FORCE_EN                           BIT(9)
#define BIT_AP_AHB_GSP_AUTO_GATE_EN                           BIT(8)
#define BIT_AP_AHB_LP_AUTO_CTRL_EN                            BIT(7)
#define BIT_AP_AHB_AP_MAINMTX_LP_DISABLE                      BIT(6)
#define BIT_AP_AHB_AP_AHB_AUTO_GATE_EN                        BIT(5)
#define BIT_AP_AHB_AP_EMC_AUTO_GATE_EN                        BIT(4)
#define BIT_AP_AHB_CA7_EMC_AUTO_GATE_EN                       BIT(3)
#define BIT_AP_AHB_CA7_DBG_FORCE_SLEEP                        BIT(2)
#define BIT_AP_AHB_CA7_DBG_AUTO_GATE_EN                       BIT(1)
#define BIT_AP_AHB_CA7_CORE_AUTO_GATE_EN                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_HOLDING_PEN
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_HOLDING_PEN(x)                             (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_JMP_ADDR_CA7_C0
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_JMP_ADDR_CA7_C0(x)                         (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_JMP_ADDR_CA7_C1
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_JMP_ADDR_CA7_C1(x)                         (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_JMP_ADDR_CA7_C2
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_JMP_ADDR_CA7_C2(x)                         (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_JMP_ADDR_CA7_C3
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_JMP_ADDR_CA7_C3(x)                         (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_CA7_C0_PU_LOCK
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CA7_C0_PU_LOCK                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_CA7_C1_PU_LOCK
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CA7_C1_PU_LOCK                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_CA7_C2_PU_LOCK
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CA7_C2_PU_LOCK                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_CA7_C3_PU_LOCK
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CA7_C3_PU_LOCK                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_CA7_CKG_DIV_CFG
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CA7_DBG_CKG_DIV(x)                         (((x) & 0x7) << 16)
#define BIT_AP_AHB_CA7_AXI_CKG_DIV(x)                         (((x) & 0x7) << 8)
#define BIT_AP_AHB_CA7_MCU_CKG_DIV(x)                         (((x) & 0x7) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_MCU_PAUSE
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_MMTX_DEEP_STOP_EN                          BIT(6)
#define BIT_AP_AHB_DMA_ACT_LIGHT_EN                           BIT(5)
#define BIT_AP_AHB_MCU_SLEEP_FOLLOW_CA7_EN                    BIT(4)
#define BIT_AP_AHB_MCU_LIGHT_SLEEP_EN                         BIT(3)
#define BIT_AP_AHB_MCU_DEEP_SLEEP_EN                          BIT(2)
#define BIT_AP_AHB_MCU_SYS_SLEEP_EN                           BIT(1)
#define BIT_AP_AHB_MCU_CORE_SLEEP                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_MISC_CKG_EN
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_ASHB_CA7_DBG_VLD                           BIT(9)
#define BIT_AP_AHB_ASHB_CA7_DBG_EN                            BIT(8)
#define BIT_AP_AHB_DISP_TMC_CKG_EN                            BIT(4)
#define BIT_AP_AHB_DPHY_REF_CKG_EN                            BIT(1)
#define BIT_AP_AHB_DPHY_CFG_CKG_EN                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_CA7_C0_AUTO_FORCE_SHUTDOWN_EN
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CA7_C0_AUTO_FORCE_SHUTDOWN_EN              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_CA7_C1_AUTO_FORCE_SHUTDOWN_EN
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CA7_C1_AUTO_FORCE_SHUTDOWN_EN              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_CA7_C2_AUTO_FORCE_SHUTDOWN_EN
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CA7_C2_AUTO_FORCE_SHUTDOWN_EN              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_CA7_C3_AUTO_FORCE_SHUTDOWN_EN
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CA7_C3_AUTO_FORCE_SHUTDOWN_EN              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_CA7_CKG_SEL_CFG
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CA7_MCU_CKG_SEL(x)                         (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_MST_FRC_LSLP
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_SLV3_FRC_LSLP                              BIT(10)
#define BIT_AP_AHB_MST9_FRC_LSLP                              BIT(9)
#define BIT_AP_AHB_MST8_FRC_LSLP                              BIT(8)
#define BIT_AP_AHB_MST7_FRC_LSLP                              BIT(7)
#define BIT_AP_AHB_MST6_FRC_LSLP                              BIT(6)
#define BIT_AP_AHB_MST5_FRC_LSLP                              BIT(5)
#define BIT_AP_AHB_MST4_FRC_LSLP                              BIT(4)
#define BIT_AP_AHB_MST3_FRC_LSLP                              BIT(3)
#define BIT_AP_AHB_MST2_FRC_LSLP                              BIT(2)
#define BIT_AP_AHB_MST1_FRC_LSLP                              BIT(1)
#define BIT_AP_AHB_MST0_FRC_LSLP                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_MST_PUB_FRC_DSLP
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_MST9_PUB_FRC_DSLP                          BIT(9)
#define BIT_AP_AHB_MST8_PUB_FRC_DSLP                          BIT(8)
#define BIT_AP_AHB_MST7_PUB_FRC_DSLP                          BIT(7)
#define BIT_AP_AHB_MST6_PUB_FRC_DSLP                          BIT(6)
#define BIT_AP_AHB_MST5_PUB_FRC_DSLP                          BIT(5)
#define BIT_AP_AHB_MST4_PUB_FRC_DSLP                          BIT(4)
#define BIT_AP_AHB_MST3_PUB_FRC_DSLP                          BIT(3)
#define BIT_AP_AHB_MST2_PUB_FRC_DSLP                          BIT(2)
#define BIT_AP_AHB_MST1_PUB_FRC_DSLP                          BIT(1)
#define BIT_AP_AHB_MST0_PUB_FRC_DSLP                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M0_LPC
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M0_LP_ACTIVE_SYNC_SEL                      BIT(18)
#define BIT_AP_AHB_M0_LP_EB                                   BIT(16)
#define BIT_AP_AHB_M0_LP_NUM(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M1_LPC
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M1_LP_ACTIVE_SYNC_SEL                      BIT(18)
#define BIT_AP_AHB_M1_LP_FORCE                                BIT(17)
#define BIT_AP_AHB_M1_LP_EB                                   BIT(16)
#define BIT_AP_AHB_M1_LP_NUM(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M2_LPC
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M2_LP_ACTIVE_SYNC_SEL                      BIT(18)
#define BIT_AP_AHB_M2_LP_FORCE                                BIT(17)
#define BIT_AP_AHB_M2_LP_EB                                   BIT(16)
#define BIT_AP_AHB_M2_LP_NUM(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M3_LPC
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M3_LP_ACTIVE_SYNC_SEL                      BIT(18)
#define BIT_AP_AHB_M3_LP_FORCE                                BIT(17)
#define BIT_AP_AHB_M3_LP_EB                                   BIT(16)
#define BIT_AP_AHB_M3_LP_NUM(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M4_LPC
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M4_LP_ACTIVE_SYNC_SEL                      BIT(18)
#define BIT_AP_AHB_M4_LP_FORCE                                BIT(17)
#define BIT_AP_AHB_M4_LP_EB                                   BIT(16)
#define BIT_AP_AHB_M4_LP_NUM(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M5_LPC
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M5_LP_ACTIVE_SYNC_SEL                      BIT(18)
#define BIT_AP_AHB_M5_LP_FORCE                                BIT(17)
#define BIT_AP_AHB_M5_LP_EB                                   BIT(16)
#define BIT_AP_AHB_M5_LP_NUM(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M6_LPC
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M6_LP_ACTIVE_SYNC_SEL                      BIT(18)
#define BIT_AP_AHB_M6_LP_FORCE                                BIT(17)
#define BIT_AP_AHB_M6_LP_EB                                   BIT(16)
#define BIT_AP_AHB_M6_LP_NUM(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M7_LPC
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M7_LP_ACTIVE_SYNC_SEL                      BIT(18)
#define BIT_AP_AHB_M7_LP_FORCE                                BIT(17)
#define BIT_AP_AHB_M7_LP_EB                                   BIT(16)
#define BIT_AP_AHB_M7_LP_NUM(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M8_LPC
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M8_LP_ACTIVE_SYNC_SEL                      BIT(18)
#define BIT_AP_AHB_M8_LP_FORCE                                BIT(17)
#define BIT_AP_AHB_M8_LP_EB                                   BIT(16)
#define BIT_AP_AHB_M8_LP_NUM(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M9_LPC
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M9_LP_ACTIVE_SYNC_SEL                      BIT(18)
#define BIT_AP_AHB_M9_LP_FORCE                                BIT(17)
#define BIT_AP_AHB_M9_LP_EB                                   BIT(16)
#define BIT_AP_AHB_M9_LP_NUM(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_MAIN_LPC
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_MAIN_LP_ACTIVE_SYNC_SEL                    BIT(18)
#define BIT_AP_AHB_MAIN_LP_FORCE                              BIT(17)
#define BIT_AP_AHB_MAIN_LP_EB                                 BIT(16)
#define BIT_AP_AHB_MAIN_LP_NUM(x)                             (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_S0_LPC
// Register Offset : 0x008C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_S0_LP_ACTIVE_SYNC_SEL                      BIT(18)
#define BIT_AP_AHB_S0_LP_FORCE                                BIT(17)
#define BIT_AP_AHB_S0_LP_EB                                   BIT(16)
#define BIT_AP_AHB_S0_LP_NUM(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_S1_LPC
// Register Offset : 0x0090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_S1_LP_ACTIVE_SYNC_SEL                      BIT(18)
#define BIT_AP_AHB_S1_LP_FORCE                                BIT(17)
#define BIT_AP_AHB_S1_LP_EB                                   BIT(16)
#define BIT_AP_AHB_S1_LP_NUM(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_S2_LPC
// Register Offset : 0x0094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_S2_LP_ACTIVE_SYNC_SEL                      BIT(18)
#define BIT_AP_AHB_S2_LP_FORCE                                BIT(17)
#define BIT_AP_AHB_S2_LP_EB                                   BIT(16)
#define BIT_AP_AHB_S2_LP_NUM(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_S3_LPC
// Register Offset : 0x0098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_S3_LP_ACTIVE_SYNC_SEL                      BIT(18)
#define BIT_AP_AHB_S3_LP_EB                                   BIT(16)
#define BIT_AP_AHB_S3_LP_NUM(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_S4_LPC
// Register Offset : 0x009C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_S4_LP_ACTIVE_SYNC_SEL                      BIT(18)
#define BIT_AP_AHB_S4_LP_FORCE                                BIT(17)
#define BIT_AP_AHB_S4_LP_EB                                   BIT(16)
#define BIT_AP_AHB_S4_LP_NUM(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_CA7_STANDBY_STATUS
// Register Offset : 0x3008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CA7_STANDBYWFIL2                           BIT(12)
#define BIT_AP_AHB_CA7_ETMSTANDBYWFX(x)                       (((x) & 0xF) << 8)
#define BIT_AP_AHB_CA7_STANDBYWFE(x)                          (((x) & 0xF) << 4)
#define BIT_AP_AHB_CA7_STANDBYWFI(x)                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_LVDS_CFG
// Register Offset : 0x3010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_LVDS_TXCLKDATA(x)                          (((x) & 0x7F) << 16)
#define BIT_AP_AHB_LVDS_TXCOM(x)                              (((x) & 0x3) << 12)
#define BIT_AP_AHB_LVDS_TXSLEW(x)                             (((x) & 0x3) << 10)
#define BIT_AP_AHB_LVDS_TXSW(x)                               (((x) & 0x3) << 8)
#define BIT_AP_AHB_LVDS_TXRERSER(x)                           (((x) & 0x1F) << 3)
#define BIT_AP_AHB_LVDS_PRE_EMP(x)                            (((x) & 0x3) << 1)
#define BIT_AP_AHB_LVDS_TXPD                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_LVDS_PLL_CFG0
// Register Offset : 0x3014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_LVDS_PLL_LOCK_DET                          BIT(31)
#define BIT_AP_AHB_LVDS_PLL_REFIN(x)                          (((x) & 0x3) << 24)
#define BIT_AP_AHB_LVDS_PLL_LPF(x)                            (((x) & 0x7) << 20)
#define BIT_AP_AHB_LVDS_PLL_DIV_S                             BIT(18)
#define BIT_AP_AHB_LVDS_PLL_IBIAS(x)                          (((x) & 0x3) << 16)
#define BIT_AP_AHB_LVDS_PLLN(x)                               (((x) & 0x7FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_LVDS_PLL_CFG1
// Register Offset : 0x3018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_LVDS_PLL_KINT(x)                           (((x) & 0xFFFFF) << 12)
#define BIT_AP_AHB_LVDS_PLL_RSV(x)                            (((x) & 0x3) << 8)
#define BIT_AP_AHB_LVDS_PLL_MOD_EN                            BIT(7)
#define BIT_AP_AHB_LVDS_PLL_SDM_EN                            BIT(6)
#define BIT_AP_AHB_LVDS_PLL_NINT(x)                           (((x) & 0x3F))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_AP_QOS_CFG
// Register Offset : 0x301C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_QOS_R_TMC(x)                               (((x) & 0xF) << 20)
#define BIT_AP_AHB_QOS_W_TMC(x)                               (((x) & 0xF) << 16)
#define BIT_AP_AHB_QOS_R_DISPC(x)                             (((x) & 0xF) << 4)
#define BIT_AP_AHB_QOS_W_DISPC(x)                             (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_OTG_PHY_TUNE
// Register Offset : 0x3020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_OTG_TXPREEMPPULSETUNE                      BIT(20)
#define BIT_AP_AHB_OTG_TXRESTUNE(x)                           (((x) & 0x3) << 18)
#define BIT_AP_AHB_OTG_TXHSXVTUNE(x)                          (((x) & 0x3) << 16)
#define BIT_AP_AHB_OTG_TXVREFTUNE(x)                          (((x) & 0xF) << 12)
#define BIT_AP_AHB_OTG_TXPREEMPAMPTUNE(x)                     (((x) & 0x3) << 10)
#define BIT_AP_AHB_OTG_TXRISETUNE(x)                          (((x) & 0x3) << 8)
#define BIT_AP_AHB_OTG_TXFSLSTUNE(x)                          (((x) & 0xF) << 4)
#define BIT_AP_AHB_OTG_SQRXTUNE(x)                            (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_OTG_PHY_TEST
// Register Offset : 0x3024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_OTG_ATERESET                               BIT(31)
#define BIT_AP_AHB_OTG_VBUS_VALID_PHYREG                      BIT(24)
#define BIT_AP_AHB_OTG_VBUS_VALID_PHYREG_SEL                  BIT(23)
#define BIT_AP_AHB_OTG_VBUS_VALID_EXT                         BIT(22)
#define BIT_AP_AHB_OTG_TESTBURNIN                             BIT(21)
#define BIT_AP_AHB_OTG_LOOPBACKENB                            BIT(20)
#define BIT_AP_AHB_OTG_TESTDATAOUT(x)                         (((x) & 0xF) << 16)
#define BIT_AP_AHB_OTG_VATESTENB(x)                           (((x) & 0x3) << 14)
#define BIT_AP_AHB_OTG_TESTCLK                                BIT(13)
#define BIT_AP_AHB_OTG_TESTDATAOUTSEL                         BIT(12)
#define BIT_AP_AHB_OTG_TESTADDR(x)                            (((x) & 0xF) << 8)
#define BIT_AP_AHB_OTG_TESTDATAIN(x)                          (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_OTG_PHY_CTRL
// Register Offset : 0x3028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_USB2_CON_TESTMODE                          BIT(31)
#define BIT_AP_AHB_UTMI_WIDTH_SEL                             BIT(30)
#define BIT_AP_AHB_USB2_DATABUS16_8                           BIT(29)
#define BIT_AP_AHB_OTG_SS_SCALEDOWNMODE(x)                    (((x) & 0x3) << 25)
#define BIT_AP_AHB_OTG_TXBITSTUFFENH                          BIT(23)
#define BIT_AP_AHB_OTG_TXBITSTUFFEN                           BIT(22)
#define BIT_AP_AHB_OTG_DMPULLDOWN                             BIT(21)
#define BIT_AP_AHB_OTG_DPPULLDOWN                             BIT(20)
#define BIT_AP_AHB_OTG_DMPULLUP                               BIT(9)
#define BIT_AP_AHB_OTG_COMMONONN                              BIT(8)
#define BIT_AP_AHB_USB2_PHY_IDDIG                             BIT(3)
#define BIT_AP_AHB_OTG_FSEL(x)                                (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_OTG_CTRL0
// Register Offset : 0x302C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_USB20_TUNEHSAMP(x)                         (((x) & 0x3) << 30)
#define BIT_AP_AHB_USB20_TUNEPLLS(x)                          (((x) & 0x3) << 28)
#define BIT_AP_AHB_USB20_TUNERISE(x)                          (((x) & 0x3) << 26)
#define BIT_AP_AHB_USB20_TUNEDSC(x)                           (((x) & 0x3) << 24)
#define BIT_AP_AHB_USB20_TUNEOTG(x)                           (((x) & 0x7) << 21)
#define BIT_AP_AHB_USB20_TUNESQ(x)                            (((x) & 0xF) << 17)
#define BIT_AP_AHB_USB20_RESERVED(x)                          (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_OTG_CTRL1
// Register Offset : 0x3030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_USB20_BIST_MODE(x)                         (((x) & 0x1F) << 23)
#define BIT_AP_AHB_USB20_BYPASS_DRV_DM                        BIT(22)
#define BIT_AP_AHB_USB20_BYPASS_DRV_DP                        BIT(21)
#define BIT_AP_AHB_USB20_SAMPLER_SEL                          BIT(20)
#define BIT_AP_AHB_HSIC_PLLON                                 BIT(16)
#define BIT_AP_AHB_USB20_REXTENABLE                           BIT(15)
#define BIT_AP_AHB_USB20_S_ID                                 BIT(14)
#define BIT_AP_AHB_USB20_TFREGRES(x)                          (((x) & 0x3F) << 8)
#define BIT_AP_AHB_USB20_TFHSRES(x)                           (((x) & 0x1F) << 3)
#define BIT_AP_AHB_USB20_TUNEEQ(x)                            (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_CHIP_ID
// Register Offset : 0x30FC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CHIP_ID(x)                                 (((x) & 0xFFFFFFFF))


#endif // _AP_AHB_REG_H
