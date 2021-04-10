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

#define CTL_BASE_AP_AHB SPRD_AHB_BASE


#define REG_AP_AHB_AHB_EB                      ( CTL_BASE_AP_AHB + 0x0000 )
#define REG_AP_AHB_AHB_RST                     ( CTL_BASE_AP_AHB + 0x0004 )
#define REG_AP_AHB_AP_SYS_FORCE_SLEEP_CFG      ( CTL_BASE_AP_AHB + 0x0008 )
#define REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG       ( CTL_BASE_AP_AHB + 0x000C )
#define REG_AP_AHB_HOLDING_PEN                 ( CTL_BASE_AP_AHB + 0x0010 )
#define REG_AP_AHB_MISC_CKG_EN                 ( CTL_BASE_AP_AHB + 0x0014 )
#define REG_AP_AHB_MISC_CFG                    ( CTL_BASE_AP_AHB + 0x0018 )
#define REG_AP_AHB_PUB0_FRC_LSLP               ( CTL_BASE_AP_AHB + 0x001C )
#define REG_AP_AHB_PUB1_FRC_LSLP               ( CTL_BASE_AP_AHB + 0x0020 )
#define REG_AP_AHB_PUB0_FRC_DSLP               ( CTL_BASE_AP_AHB + 0x0024 )
#define REG_AP_AHB_PUB1_FRC_DSLP               ( CTL_BASE_AP_AHB + 0x0028 )
#define REG_AP_AHB_FRC_DOZE                    ( CTL_BASE_AP_AHB + 0x002C )
#define REG_AP_AHB_NANC_CLK_CFG                ( CTL_BASE_AP_AHB + 0x3000 )
#define REG_AP_AHB_RESERVED_REG_1              ( CTL_BASE_AP_AHB + 0x3008 )
#define REG_AP_AHB_RESERVED_REG_0              ( CTL_BASE_AP_AHB + 0x300C )
#define REG_AP_AHB_USB3_CTRL                   ( CTL_BASE_AP_AHB + 0x3020 )
#define REG_AP_AHB_NOC_CTRL0                   ( CTL_BASE_AP_AHB + 0x302C )
#define REG_AP_AHB_NOC_CTRL1                   ( CTL_BASE_AP_AHB + 0x3030 )
#define REG_AP_AHB_NOC_CTRL2                   ( CTL_BASE_AP_AHB + 0x3034 )
#define REG_AP_AHB_NOC_CTRL3                   ( CTL_BASE_AP_AHB + 0x3038 )
#define REG_AP_AHB_USB3_DBG0                   ( CTL_BASE_AP_AHB + 0x303C )
#define REG_AP_AHB_USB3_DBG1                   ( CTL_BASE_AP_AHB + 0x3040 )
#define REG_AP_AHB_USB3_DBG2                   ( CTL_BASE_AP_AHB + 0x3044 )
#define REG_AP_AHB_UFS_DBG0                    ( CTL_BASE_AP_AHB + 0x3048 )
#define REG_AP_AHB_UFS_DBG1                    ( CTL_BASE_AP_AHB + 0x304C )
#define REG_AP_AHB_UFS_DBG2                    ( CTL_BASE_AP_AHB + 0x3050 )
#define REG_AP_AHB_UFS_DBGUP0                  ( CTL_BASE_AP_AHB + 0x3054 )
#define REG_AP_AHB_UFS_DBGUP1                  ( CTL_BASE_AP_AHB + 0x3058 )
#define REG_AP_AHB_M0_LPC                      ( CTL_BASE_AP_AHB + 0x3060 )
#define REG_AP_AHB_M1_LPC                      ( CTL_BASE_AP_AHB + 0x3064 )
#define REG_AP_AHB_M2_LPC                      ( CTL_BASE_AP_AHB + 0x3068 )
#define REG_AP_AHB_M3_LPC                      ( CTL_BASE_AP_AHB + 0x306C )
#define REG_AP_AHB_M4_LPC                      ( CTL_BASE_AP_AHB + 0x3070 )
#define REG_AP_AHB_M5_LPC                      ( CTL_BASE_AP_AHB + 0x3074 )
#define REG_AP_AHB_M6_LPC                      ( CTL_BASE_AP_AHB + 0x3078 )
#define REG_AP_AHB_M7_LPC                      ( CTL_BASE_AP_AHB + 0x307C )
#define REG_AP_AHB_M8_LPC                      ( CTL_BASE_AP_AHB + 0x3080 )
#define REG_AP_AHB_M9_LPC                      ( CTL_BASE_AP_AHB + 0x3084 )
#define REG_AP_AHB_M10_LPC                     ( CTL_BASE_AP_AHB + 0x3088 )
#define REG_AP_AHB_ASYNC_BRG_LPC               ( CTL_BASE_AP_AHB + 0x308C )
#define REG_AP_AHB_ASYNC_BRG_DBG0              ( CTL_BASE_AP_AHB + 0x3090 )
#define REG_AP_AHB_ASYNC_BRG_DBG1              ( CTL_BASE_AP_AHB + 0x3094 )
#define REG_AP_AHB_ASYNC_BRG_CFG               ( CTL_BASE_AP_AHB + 0x3098 )
#define REG_AP_AHB_REG_RESV                    ( CTL_BASE_AP_AHB + 0x30A0 )

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_AHB_EB
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_DAP_EB                                       BIT(29)
#define BIT_AP_AHB_BUS_ALIGN_DET_EB                             BIT(28)
#define BIT_AP_AHB_PTI_EB                                       BIT(27)
#define BIT_AP_AHB_CE_EFS_EB                                    BIT(26)
#define BIT_AP_AHB_CE1_EB                                       BIT(25)
#define BIT_AP_AHB_CE0_EB                                       BIT(24)
#define BIT_AP_AHB_UFS_EB                                       BIT(23)
#define BIT_AP_AHB_BIA_LP_EB                                    BIT(22)
#define BIT_AP_AHB_EMMC_32K_EB                                  BIT(20)
#define BIT_AP_AHB_SDIO2_32K_EB                                 BIT(19)
#define BIT_AP_AHB_SDIO1_32K_EB                                 BIT(18)
#define BIT_AP_AHB_SDIO0_32K_EB                                 BIT(17)
#define BIT_AP_AHB_BUSMON3_EB                                   BIT(16)
#define BIT_AP_AHB_BUSMON2_EB                                   BIT(15)
#define BIT_AP_AHB_BUSMON1_EB                                   BIT(14)
#define BIT_AP_AHB_BUSMON0_EB                                   BIT(13)
#define BIT_AP_AHB_ROM_EB                                       BIT(12)
#define BIT_AP_AHB_EMMC_EB                                      BIT(10)
#define BIT_AP_AHB_SDIO2_EB                                     BIT(9)
#define BIT_AP_AHB_SDIO1_EB                                     BIT(8)
#define BIT_AP_AHB_SDIO0_EB                                     BIT(7)
#define BIT_AP_AHB_DMA_EB                                       BIT(5)
#define BIT_AP_AHB_USB3_REF_EB                                  BIT(4)
#define BIT_AP_AHB_USB3_SUSPEND_EB                              BIT(3)
#define BIT_AP_AHB_USB3_EB                                      BIT(2)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_AHB_RST
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_PTI_SOFT_RST                                 BIT(28)
#define BIT_AP_AHB_CE_EFS_SOFT_RST                              BIT(27)
#define BIT_AP_AHB_CE1_SOFT_RST                                 BIT(26)
#define BIT_AP_AHB_CE0_SOFT_RST                                 BIT(25)
#define BIT_AP_AHB_BUSMON3_SOFT_RST                             BIT(17)
#define BIT_AP_AHB_BUSMON2_SOFT_RST                             BIT(16)
#define BIT_AP_AHB_BUSMON1_SOFT_RST                             BIT(15)
#define BIT_AP_AHB_BUSMON0_SOFT_RST                             BIT(14)
#define BIT_AP_AHB_EMMC_SOFT_RST                                BIT(11)
#define BIT_AP_AHB_SDIO2_SOFT_RST                               BIT(10)
#define BIT_AP_AHB_SDIO1_SOFT_RST                               BIT(9)
#define BIT_AP_AHB_SDIO0_SOFT_RST                               BIT(8)
#define BIT_AP_AHB_DMA_SOFT_RST                                 BIT(5)
#define BIT_AP_AHB_UFS_SOFT_RST                                 BIT(2)
#define BIT_AP_AHB_USB3_SOFT_RST                                BIT(1)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_AP_SYS_FORCE_SLEEP_CFG
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_DMA_FRC_SLEEP                                BIT(5)
#define BIT_AP_AHB_AXI_LP_CTRL_DISABLE                          BIT(4)
#define BIT_AP_AHB_AP_PERI_FRC_ON                               BIT(2)
#define BIT_AP_AHB_AP_PERI_FRC_OFF                              BIT(1)
#define BIT_AP_AHB_AP_APB_SLEEP                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_DMA_ACT_LIGHT_EN                             BIT(2)
#define BIT_AP_AHB_AP_AHB_AUTO_GATE_EN                          BIT(1)
#define BIT_AP_AHB_AP_EMC_AUTO_GATE_EN                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_HOLDING_PEN
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_HOLDING_PEN(x)                               (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_MISC_CKG_EN
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_BUS_CLK_FORCE_ON(x)                          (((x) & 0x3FFF) << 2)
#define BIT_AP_AHB_NOC_SERVICE_ACCESS_EN                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_MISC_CFG
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_AP_R_RES(x)                                  (((x) & 0x1F) << 27)
#define BIT_AP_AHB_AP_RW_RES(x)                                 (((x) & 0x3F) << 10)
#define BIT_AP_AHB_M0_NIU_IDLE_DET_DIS                          BIT(9)
#define BIT_AP_AHB_BUS_VALID_CNT(x)                             (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_PUB0_FRC_LSLP
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_ASB_PUB0_FRC_LSLP                            BIT(16)
#define BIT_AP_AHB_PUB0_FRC_LSLP(x)                             (((x) & 0x7FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_PUB1_FRC_LSLP
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_ASB_PUB1_FRC_LSLP                            BIT(16)
#define BIT_AP_AHB_PUB1_FRC_LSLP(x)                             (((x) & 0x7FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_PUB0_FRC_DSLP
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_ASB_PUB0_FRC_DSLP                            BIT(16)
#define BIT_AP_AHB_PUB0_FRC_DSLP(x)                             (((x) & 0x7FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_PUB1_FRC_DSLP
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_ASB_PUB1_FRC_DSLP                            BIT(16)
#define BIT_AP_AHB_PUB1_FRC_DSLP(x)                             (((x) & 0x7FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_FRC_DOZE
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_ASB_FRC_DOZE                                 BIT(16)
#define BIT_AP_AHB_FRC_DOZE(x)                                  (((x) & 0x7FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_NANC_CLK_CFG
// Register Offset : 0x3000
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_RESERVED_REG_1
// Register Offset : 0x3008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_RESERVED1_REG(x)                             (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_RESERVED_REG_0
// Register Offset : 0x300C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_RESERVED0_REG(x)                             (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_USB3_CTRL
// Register Offset : 0x3020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_HOST_SYSTEM_ERR                              BIT(12)
#define BIT_AP_AHB_HOST_PORT_POWER_CONTROL_PRESENT              BIT(11)
#define BIT_AP_AHB_FLADJ_30MHZ_REG(x)                           (((x) & 0x3F) << 5)
#define BIT_AP_AHB_PME_EN                                       BIT(4)
#define BIT_AP_AHB_BUS_FILTER_BYPASS(x)                         (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_NOC_CTRL0
// Register Offset : 0x302C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M7_QOS(x)                                    (((x) & 0xF) << 28)
#define BIT_AP_AHB_M6_QOS(x)                                    (((x) & 0xF) << 24)
#define BIT_AP_AHB_M5_QOS(x)                                    (((x) & 0xF) << 20)
#define BIT_AP_AHB_M4_QOS(x)                                    (((x) & 0xF) << 16)
#define BIT_AP_AHB_M3_QOS(x)                                    (((x) & 0xF) << 12)
#define BIT_AP_AHB_M2_QOS(x)                                    (((x) & 0xF) << 8)
#define BIT_AP_AHB_M1_QOS(x)                                    (((x) & 0xF) << 4)
#define BIT_AP_AHB_M0_QOS(x)                                    (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_NOC_CTRL1
// Register Offset : 0x3030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_S8_T_MAINEXTEN                               BIT(24)
#define BIT_AP_AHB_S7_T_MAINEXTEN                               BIT(23)
#define BIT_AP_AHB_S6_T_MAINEXTEN                               BIT(22)
#define BIT_AP_AHB_S5_T_MAINEXTEN                               BIT(21)
#define BIT_AP_AHB_S4_T_MAINEXTEN                               BIT(20)
#define BIT_AP_AHB_S3_T_MAINEXTEN                               BIT(19)
#define BIT_AP_AHB_S2_T_MAINEXTEN                               BIT(18)
#define BIT_AP_AHB_S1_T_MAINEXTEN                               BIT(17)
#define BIT_AP_AHB_S0_T_MAINEXTEN                               BIT(16)
#define BIT_AP_AHB_M10_QOS(x)                                   (((x) & 0xF) << 8)
#define BIT_AP_AHB_M9_QOS(x)                                    (((x) & 0xF) << 4)
#define BIT_AP_AHB_M8_QOS(x)                                    (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_NOC_CTRL2
// Register Offset : 0x3034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M6_ARCACHE(x)                                (((x) & 0xF) << 16)
#define BIT_AP_AHB_M5_ARCACHE(x)                                (((x) & 0xF) << 12)
#define BIT_AP_AHB_M4_ARCACHE(x)                                (((x) & 0xF) << 8)
#define BIT_AP_AHB_M3_ARCACHE(x)                                (((x) & 0xF) << 4)
#define BIT_AP_AHB_M2_ARCACHE(x)                                (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_NOC_CTRL3
// Register Offset : 0x3038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M6_AWCACHE(x)                                (((x) & 0xF) << 16)
#define BIT_AP_AHB_M5_AWCACHE(x)                                (((x) & 0xF) << 12)
#define BIT_AP_AHB_M4_AWCACHE(x)                                (((x) & 0xF) << 8)
#define BIT_AP_AHB_M3_AWCACHE(x)                                (((x) & 0xF) << 4)
#define BIT_AP_AHB_M2_AWCACHE(x)                                (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_USB3_DBG0
// Register Offset : 0x303C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_USB3_DBG_0(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_USB3_DBG1
// Register Offset : 0x3040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_USB3_DBG_1(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_USB3_DBG2
// Register Offset : 0x3044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_USB3_CLK_GATE_CTRL(x)                        (((x) & 0x7) << 5)
#define BIT_AP_AHB_USB3_OPERATIONAL_MODE(x)                     (((x) & 0x3) << 3)
#define BIT_AP_AHB_USB3_DBG_2(x)                                (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_UFS_DBG0
// Register Offset : 0x3048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_UFS_DBG_0(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_UFS_DBG1
// Register Offset : 0x304C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_UFS_DBG_1(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_UFS_DBG2
// Register Offset : 0x3050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_UFS_DBG_2                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_UFS_DBGUP0
// Register Offset : 0x3054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_UFS_DBGUP_0(x)                               (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_UFS_DBGUP1
// Register Offset : 0x3058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_UFS_DBGUP_1(x)                               (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M0_LPC
// Register Offset : 0x3060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M0_LP_ACTIVE_SYNC_SEL                        BIT(18)
#define BIT_AP_AHB_M0_LP_FORCE                                  BIT(17)
#define BIT_AP_AHB_M0_LP_EB                                     BIT(16)
#define BIT_AP_AHB_M0_LP_NUM(x)                                 (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M1_LPC
// Register Offset : 0x3064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M1_LP_ACTIVE_SYNC_SEL                        BIT(18)
#define BIT_AP_AHB_M1_LP_FORCE                                  BIT(17)
#define BIT_AP_AHB_M1_LP_EB                                     BIT(16)
#define BIT_AP_AHB_M1_LP_NUM(x)                                 (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M2_LPC
// Register Offset : 0x3068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M2_LP_ACTIVE_SYNC_SEL                        BIT(18)
#define BIT_AP_AHB_M2_LP_FORCE                                  BIT(17)
#define BIT_AP_AHB_M2_LP_EB                                     BIT(16)
#define BIT_AP_AHB_M2_LP_NUM(x)                                 (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M3_LPC
// Register Offset : 0x306C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M3_LP_ACTIVE_SYNC_SEL                        BIT(18)
#define BIT_AP_AHB_M3_LP_FORCE                                  BIT(17)
#define BIT_AP_AHB_M3_LP_EB                                     BIT(16)
#define BIT_AP_AHB_M3_LP_NUM(x)                                 (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M4_LPC
// Register Offset : 0x3070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M4_LP_ACTIVE_SYNC_SEL                        BIT(18)
#define BIT_AP_AHB_M4_LP_FORCE                                  BIT(17)
#define BIT_AP_AHB_M4_LP_EB                                     BIT(16)
#define BIT_AP_AHB_M4_LP_NUM(x)                                 (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M5_LPC
// Register Offset : 0x3074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M5_LP_ACTIVE_SYNC_SEL                        BIT(18)
#define BIT_AP_AHB_M5_LP_FORCE                                  BIT(17)
#define BIT_AP_AHB_M5_LP_EB                                     BIT(16)
#define BIT_AP_AHB_M5_LP_NUM(x)                                 (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M6_LPC
// Register Offset : 0x3078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M6_LP_ACTIVE_SYNC_SEL                        BIT(18)
#define BIT_AP_AHB_M6_LP_FORCE                                  BIT(17)
#define BIT_AP_AHB_M6_LP_EB                                     BIT(16)
#define BIT_AP_AHB_M6_LP_NUM(x)                                 (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M7_LPC
// Register Offset : 0x307C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M7_LP_ACTIVE_SYNC_SEL                        BIT(18)
#define BIT_AP_AHB_M7_LP_FORCE                                  BIT(17)
#define BIT_AP_AHB_M7_LP_EB                                     BIT(16)
#define BIT_AP_AHB_M7_LP_NUM(x)                                 (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M8_LPC
// Register Offset : 0x3080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M8_LP_ACTIVE_SYNC_SEL                        BIT(18)
#define BIT_AP_AHB_M8_LP_FORCE                                  BIT(17)
#define BIT_AP_AHB_M8_LP_EB                                     BIT(16)
#define BIT_AP_AHB_M8_LP_NUM(x)                                 (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M9_LPC
// Register Offset : 0x3084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M9_LP_ACTIVE_SYNC_SEL                        BIT(18)
#define BIT_AP_AHB_M9_LP_FORCE                                  BIT(17)
#define BIT_AP_AHB_M9_LP_EB                                     BIT(16)
#define BIT_AP_AHB_M9_LP_NUM(x)                                 (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_M10_LPC
// Register Offset : 0x3088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M10_LP_ACTIVE_SYNC_SEL                       BIT(18)
#define BIT_AP_AHB_M10_LP_FORCE                                 BIT(17)
#define BIT_AP_AHB_M10_LP_EB                                    BIT(16)
#define BIT_AP_AHB_M10_LP_NUM(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_ASYNC_BRG_LPC
// Register Offset : 0x308C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_ASYNC_BRG_LP_ACTIVE_SYNC_SEL                 BIT(18)
#define BIT_AP_AHB_ASYNC_BRG_LP_FORCE                           BIT(17)
#define BIT_AP_AHB_ASYNC_BRG_LP_EB                              BIT(16)
#define BIT_AP_AHB_ASYNC_BRG_LP_NUM(x)                          (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_ASYNC_BRG_DBG0
// Register Offset : 0x3090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_ASYNC_BRG_DBG(x)                             (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_ASYNC_BRG_DBG1
// Register Offset : 0x3094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_ASYNC_BRG_TRANS_IDLE                         BIT(1)
#define BIT_AP_AHB_ASYNC_BRG_AXI_DETECTOR_OVFL                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_ASYNC_BRG_CFG
// Register Offset : 0x3098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_ASYNC_BRG_AF_AW_CH(x)                        (((x) & 0x7) << 27)
#define BIT_AP_AHB_ASYNC_BRG_AE_AW_CH(x)                        (((x) & 0x7) << 24)
#define BIT_AP_AHB_ASYNC_BRG_AF_W_CH(x)                         (((x) & 0x7) << 21)
#define BIT_AP_AHB_ASYNC_BRG_AE_W_CH(x)                         (((x) & 0x7) << 18)
#define BIT_AP_AHB_ASYNC_BRG_AF_B_CH(x)                         (((x) & 0x7) << 15)
#define BIT_AP_AHB_ASYNC_BRG_AE_B_CH(x)                         (((x) & 0x7) << 12)
#define BIT_AP_AHB_ASYNC_BRG_AF_AR_CH(x)                        (((x) & 0x7) << 9)
#define BIT_AP_AHB_ASYNC_BRG_AE_AR_CH(x)                        (((x) & 0x7) << 6)
#define BIT_AP_AHB_ASYNC_BRG_AF_R_CH(x)                         (((x) & 0x7) << 3)
#define BIT_AP_AHB_ASYNC_BRG_AE_R_CH(x)                         (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_REG_RESV
// Register Offset : 0x30A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_REG_RESERVED(x)                              (((x) & 0xFFFFFFFF))


#endif // _AP_AHB_REG_H
