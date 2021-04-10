/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _PUB_CP_AHB_REG_H
#define _PUB_CP_AHB_REG_H

#define CTL_BASE_PUB_CP_AHB 0x20070000


#define REG_PUB_CP_AHB_MST_FRC_LSLP          ( CTL_BASE_PUB_CP_AHB + 0x0000 )
#define REG_PUB_CP_AHB_MST_PUB_FRC_DSLP      ( CTL_BASE_PUB_CP_AHB + 0x0004 )
#define REG_PUB_CP_AHB_MST_FRC_DOZE          ( CTL_BASE_PUB_CP_AHB + 0x0008 )
#define REG_PUB_CP_AHB_DMA_HPROT             ( CTL_BASE_PUB_CP_AHB + 0x000C )
#define REG_PUB_CP_AHB_AWCACHE_REG           ( CTL_BASE_PUB_CP_AHB + 0x0010 )
#define REG_PUB_CP_AHB_ARCACHE_REG           ( CTL_BASE_PUB_CP_AHB + 0x0014 )
#define REG_PUB_CP_AHB_ARCH_EB               ( CTL_BASE_PUB_CP_AHB + 0x0018 )
#define REG_PUB_CP_AHB_LP_EB                 ( CTL_BASE_PUB_CP_AHB + 0x0020 )
#define REG_PUB_CP_AHB_LP_FORCE              ( CTL_BASE_PUB_CP_AHB + 0x0024 )
#define REG_PUB_CP_AHB_ACTIVE_SYNC_SEL       ( CTL_BASE_PUB_CP_AHB + 0x0028 )
#define REG_PUB_CP_AHB_AHB_CTRL0             ( CTL_BASE_PUB_CP_AHB + 0x0034 )
#define REG_PUB_CP_AHB_WAKEUP_EN             ( CTL_BASE_PUB_CP_AHB + 0x0038 )
#define REG_PUB_CP_AHB_AHB_PAUSE             ( CTL_BASE_PUB_CP_AHB + 0x0040 )
#define REG_PUB_CP_AHB_AHB_SLP_CTL           ( CTL_BASE_PUB_CP_AHB + 0x0044 )
#define REG_PUB_CP_AHB_AHB_SLP_STS           ( CTL_BASE_PUB_CP_AHB + 0x0048 )
#define REG_PUB_CP_AHB_BUSMON_PERF_CTL       ( CTL_BASE_PUB_CP_AHB + 0x004C )
#define REG_PUB_CP_AHB_ROM_SEL_CTL           ( CTL_BASE_PUB_CP_AHB + 0x0054 )
#define REG_PUB_CP_AHB_AHB_RST0_STS          ( CTL_BASE_PUB_CP_AHB + 0x0060 )
#define REG_PUB_CP_AHB_CR5_DBG_CTRL          ( CTL_BASE_PUB_CP_AHB + 0x0068 )
#define REG_PUB_CP_AHB_AHB_RSV_REG0          ( CTL_BASE_PUB_CP_AHB + 0x006C )
#define REG_PUB_CP_AHB_SEL_VIC               ( CTL_BASE_PUB_CP_AHB + 0x0070 )
#define REG_PUB_CP_AHB_NIC400_AR_QOS0        ( CTL_BASE_PUB_CP_AHB + 0x0074 )
#define REG_PUB_CP_AHB_NIC400_AR_QOS1        ( CTL_BASE_PUB_CP_AHB + 0x0078 )
#define REG_PUB_CP_AHB_NIC400_AW_QOS0        ( CTL_BASE_PUB_CP_AHB + 0x007C )
#define REG_PUB_CP_AHB_NIC400_AW_QOS1        ( CTL_BASE_PUB_CP_AHB + 0x0080 )
#define REG_PUB_CP_AHB_ASYNC_BRIDGE_STS      ( CTL_BASE_PUB_CP_AHB + 0x0084 )
#define REG_PUB_CP_AHB_ASYNC_BRG_CFG_0       ( CTL_BASE_PUB_CP_AHB + 0x0088 )
#define REG_PUB_CP_AHB_ASYNC_BRG_CFG_1       ( CTL_BASE_PUB_CP_AHB + 0x008C )
#define REG_PUB_CP_AHB_LP_NUM_M0             ( CTL_BASE_PUB_CP_AHB + 0x0100 )
#define REG_PUB_CP_AHB_LP_NUM_M1             ( CTL_BASE_PUB_CP_AHB + 0x0104 )
#define REG_PUB_CP_AHB_LP_NUM_M2             ( CTL_BASE_PUB_CP_AHB + 0x0108 )
#define REG_PUB_CP_AHB_LP_NUM_M3             ( CTL_BASE_PUB_CP_AHB + 0x010C )
#define REG_PUB_CP_AHB_LP_NUM_M4             ( CTL_BASE_PUB_CP_AHB + 0x0110 )
#define REG_PUB_CP_AHB_LP_NUM_M5             ( CTL_BASE_PUB_CP_AHB + 0x0114 )
#define REG_PUB_CP_AHB_LP_NUM_M6             ( CTL_BASE_PUB_CP_AHB + 0x0118 )
#define REG_PUB_CP_AHB_LP_NUM_M7             ( CTL_BASE_PUB_CP_AHB + 0x011C )
#define REG_PUB_CP_AHB_LP_NUM_M8             ( CTL_BASE_PUB_CP_AHB + 0x0120 )
#define REG_PUB_CP_AHB_LP_NUM_M9             ( CTL_BASE_PUB_CP_AHB + 0x0124 )
#define REG_PUB_CP_AHB_LP_NUM_MAIN           ( CTL_BASE_PUB_CP_AHB + 0x0128 )
#define REG_PUB_CP_AHB_LP_NUM_S0             ( CTL_BASE_PUB_CP_AHB + 0x012C )
#define REG_PUB_CP_AHB_LP_NUM_S2             ( CTL_BASE_PUB_CP_AHB + 0x0130 )
#define REG_PUB_CP_AHB_LP_NUM_S3             ( CTL_BASE_PUB_CP_AHB + 0x0134 )
#define REG_PUB_CP_AHB_LP_NUM_S4             ( CTL_BASE_PUB_CP_AHB + 0x0138 )
#define REG_PUB_CP_AHB_LP_NUM_S5             ( CTL_BASE_PUB_CP_AHB + 0x013C )
#define REG_PUB_CP_AHB_LP_NUM_S6             ( CTL_BASE_PUB_CP_AHB + 0x0140 )
#define REG_PUB_CP_AHB_LP_NUM_ABM            ( CTL_BASE_PUB_CP_AHB + 0x0144 )
#define REG_PUB_CP_AHB_LP_NUM_ABS            ( CTL_BASE_PUB_CP_AHB + 0x0148 )
#define REG_PUB_CP_AHB_ASYNC_BRG_DBG0        ( CTL_BASE_PUB_CP_AHB + 0x3090 )

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_MST_FRC_LSLP
// Register Offset : 0x0000
// Description     : 32.0
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_ABS_FRC_LSLP                               BIT(10)
#define BIT_PUB_CP_AHB_MST9_FRC_LSLP                              BIT(9)
#define BIT_PUB_CP_AHB_MST8_FRC_LSLP                              BIT(8)
#define BIT_PUB_CP_AHB_MST7_FRC_LSLP                              BIT(7)
#define BIT_PUB_CP_AHB_MST6_FRC_LSLP                              BIT(6)
#define BIT_PUB_CP_AHB_MST5_FRC_LSLP                              BIT(5)
#define BIT_PUB_CP_AHB_MST4_FRC_LSLP                              BIT(4)
#define BIT_PUB_CP_AHB_MST3_FRC_LSLP                              BIT(3)
#define BIT_PUB_CP_AHB_MST2_FRC_LSLP                              BIT(2)
#define BIT_PUB_CP_AHB_MST1_FRC_LSLP                              BIT(1)
#define BIT_PUB_CP_AHB_MST0_FRC_LSLP                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_MST_PUB_FRC_DSLP
// Register Offset : 0x0004
// Description     : 32.0
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_ABS_PUB_FRC_DSLP                           BIT(10)
#define BIT_PUB_CP_AHB_MST9_PUB_FRC_DSLP                          BIT(9)
#define BIT_PUB_CP_AHB_MST8_PUB_FRC_DSLP                          BIT(8)
#define BIT_PUB_CP_AHB_MST7_PUB_FRC_DSLP                          BIT(7)
#define BIT_PUB_CP_AHB_MST6_PUB_FRC_DSLP                          BIT(6)
#define BIT_PUB_CP_AHB_MST5_PUB_FRC_DSLP                          BIT(5)
#define BIT_PUB_CP_AHB_MST4_PUB_FRC_DSLP                          BIT(4)
#define BIT_PUB_CP_AHB_MST3_PUB_FRC_DSLP                          BIT(3)
#define BIT_PUB_CP_AHB_MST2_PUB_FRC_DSLP                          BIT(2)
#define BIT_PUB_CP_AHB_MST1_PUB_FRC_DSLP                          BIT(1)
#define BIT_PUB_CP_AHB_MST0_PUB_FRC_DSLP                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_MST_FRC_DOZE
// Register Offset : 0x0008
// Description     : 32.0
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_SLV7_FRC_DOZE                              BIT(20)
#define BIT_PUB_CP_AHB_SLV6_FRC_DOZE                              BIT(19)
#define BIT_PUB_CP_AHB_SLV5_FRC_DOZE                              BIT(18)
#define BIT_PUB_CP_AHB_SLV4_FRC_DOZE                              BIT(17)
#define BIT_PUB_CP_AHB_SLV3_FRC_DOZE                              BIT(16)
#define BIT_PUB_CP_AHB_SLV2_FRC_DOZE                              BIT(15)
#define BIT_PUB_CP_AHB_SLV1_FRC_DOZE                              BIT(14)
#define BIT_PUB_CP_AHB_SLV0_FRC_DOZE                              BIT(13)
#define BIT_PUB_CP_AHB_MAIN_FRC_DOZE                              BIT(12)
#define BIT_PUB_CP_AHB_ABS_FRC_DOZE                               BIT(11)
#define BIT_PUB_CP_AHB_MST9_FRC_DOZE                              BIT(9)
#define BIT_PUB_CP_AHB_MST8_FRC_DOZE                              BIT(8)
#define BIT_PUB_CP_AHB_MST7_FRC_DOZE                              BIT(7)
#define BIT_PUB_CP_AHB_MST6_FRC_DOZE                              BIT(6)
#define BIT_PUB_CP_AHB_MST5_FRC_DOZE                              BIT(5)
#define BIT_PUB_CP_AHB_MST4_FRC_DOZE                              BIT(4)
#define BIT_PUB_CP_AHB_MST3_FRC_DOZE                              BIT(3)
#define BIT_PUB_CP_AHB_MST2_FRC_DOZE                              BIT(2)
#define BIT_PUB_CP_AHB_MST1_FRC_DOZE                              BIT(1)
#define BIT_PUB_CP_AHB_MST0_FRC_DOZE                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_DMA_HPROT
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_HPROT_DMA(x)                               (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_AWCACHE_REG
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_AWCACHE_REG_M9(x)                          (((x) & 0xF) << 28)
#define BIT_PUB_CP_AHB_AWCACHE_REG_M8(x)                          (((x) & 0xF) << 24)
#define BIT_PUB_CP_AHB_AWCACHE_REG_M7(x)                          (((x) & 0xF) << 20)
#define BIT_PUB_CP_AHB_AWCACHE_REG_M6(x)                          (((x) & 0xF) << 16)
#define BIT_PUB_CP_AHB_AWCACHE_REG_M5(x)                          (((x) & 0xF) << 12)
#define BIT_PUB_CP_AHB_AWCACHE_REG_M4(x)                          (((x) & 0xF) << 8)
#define BIT_PUB_CP_AHB_AWCACHE_REG_M3(x)                          (((x) & 0xF) << 4)
#define BIT_PUB_CP_AHB_AWCACHE_REG_M2(x)                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_ARCACHE_REG
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_ARCACHE_REG_M9(x)                          (((x) & 0xF) << 28)
#define BIT_PUB_CP_AHB_ARCACHE_REG_M8(x)                          (((x) & 0xF) << 24)
#define BIT_PUB_CP_AHB_ARCACHE_REG_M7(x)                          (((x) & 0xF) << 20)
#define BIT_PUB_CP_AHB_ARCACHE_REG_M6(x)                          (((x) & 0xF) << 16)
#define BIT_PUB_CP_AHB_ARCACHE_REG_M5(x)                          (((x) & 0xF) << 12)
#define BIT_PUB_CP_AHB_ARCACHE_REG_M4(x)                          (((x) & 0xF) << 8)
#define BIT_PUB_CP_AHB_ARCACHE_REG_M3(x)                          (((x) & 0xF) << 4)
#define BIT_PUB_CP_AHB_ARCACHE_REG_M2(x)                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_ARCH_EB
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_AHB_ARCH_EB                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_EB
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_EB_ABM                                  BIT(22)
#define BIT_PUB_CP_AHB_LP_EB_ABS                                  BIT(21)
#define BIT_PUB_CP_AHB_LP_EB_S7                                   BIT(19)
#define BIT_PUB_CP_AHB_LP_EB_S6                                   BIT(18)
#define BIT_PUB_CP_AHB_LP_EB_S5                                   BIT(17)
#define BIT_PUB_CP_AHB_LP_EB_S4                                   BIT(16)
#define BIT_PUB_CP_AHB_LP_EB_S3                                   BIT(15)
#define BIT_PUB_CP_AHB_LP_EB_S2                                   BIT(14)
#define BIT_PUB_CP_AHB_LP_EB_S1                                   BIT(13)
#define BIT_PUB_CP_AHB_LP_EB_S0                                   BIT(12)
#define BIT_PUB_CP_AHB_LP_EB_MAIN                                 BIT(11)
#define BIT_PUB_CP_AHB_LP_EB_M9                                   BIT(9)
#define BIT_PUB_CP_AHB_LP_EB_M8                                   BIT(8)
#define BIT_PUB_CP_AHB_LP_EB_M7                                   BIT(7)
#define BIT_PUB_CP_AHB_LP_EB_M6                                   BIT(6)
#define BIT_PUB_CP_AHB_LP_EB_M5                                   BIT(5)
#define BIT_PUB_CP_AHB_LP_EB_M4                                   BIT(4)
#define BIT_PUB_CP_AHB_LP_EB_M3                                   BIT(3)
#define BIT_PUB_CP_AHB_LP_EB_M2                                   BIT(2)
#define BIT_PUB_CP_AHB_LP_EB_M1                                   BIT(1)
#define BIT_PUB_CP_AHB_LP_EB_M0                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_FORCE
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_FORCE_ABM                               BIT(22)
#define BIT_PUB_CP_AHB_LP_FORCE_ABS                               BIT(21)
#define BIT_PUB_CP_AHB_LP_FORCE_S7                                BIT(19)
#define BIT_PUB_CP_AHB_LP_FORCE_S6                                BIT(18)
#define BIT_PUB_CP_AHB_LP_FORCE_S5                                BIT(17)
#define BIT_PUB_CP_AHB_LP_FORCE_S4                                BIT(16)
#define BIT_PUB_CP_AHB_LP_FORCE_S3                                BIT(15)
#define BIT_PUB_CP_AHB_LP_FORCE_S2                                BIT(14)
#define BIT_PUB_CP_AHB_LP_FORCE_S1                                BIT(13)
#define BIT_PUB_CP_AHB_LP_FORCE_S0                                BIT(12)
#define BIT_PUB_CP_AHB_LP_FORCE_MAIN                              BIT(11)
#define BIT_PUB_CP_AHB_LP_FORCE_M9                                BIT(9)
#define BIT_PUB_CP_AHB_LP_FORCE_M8                                BIT(8)
#define BIT_PUB_CP_AHB_LP_FORCE_M7                                BIT(7)
#define BIT_PUB_CP_AHB_LP_FORCE_M6                                BIT(6)
#define BIT_PUB_CP_AHB_LP_FORCE_M5                                BIT(5)
#define BIT_PUB_CP_AHB_LP_FORCE_M4                                BIT(4)
#define BIT_PUB_CP_AHB_LP_FORCE_M3                                BIT(3)
#define BIT_PUB_CP_AHB_LP_FORCE_M2                                BIT(2)
#define BIT_PUB_CP_AHB_LP_FORCE_M1                                BIT(1)
#define BIT_PUB_CP_AHB_LP_FORCE_M0                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_ACTIVE_SYNC_SEL
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_ABM                        BIT(22)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_ABS                        BIT(21)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_S7                         BIT(19)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_S6                         BIT(18)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_S5                         BIT(17)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_S4                         BIT(16)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_S3                         BIT(15)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_S2                         BIT(14)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_S1                         BIT(13)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_S0                         BIT(12)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_MAIN                       BIT(11)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_M9                         BIT(9)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_M8                         BIT(8)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_M7                         BIT(7)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_M6                         BIT(6)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_M5                         BIT(5)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_M4                         BIT(4)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_M3                         BIT(3)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_M2                         BIT(2)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_M1                         BIT(1)
#define BIT_PUB_CP_AHB_ACTIVE_SYNC_SEL_M0                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_AHB_CTRL0
// Register Offset : 0x0034
// Description     : 32.0
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_CLK_BUSMON9_EB                             BIT(29)
#define BIT_PUB_CP_AHB_CLK_BUSMON8_EB                             BIT(28)
#define BIT_PUB_CP_AHB_CLK_BUSMON7_EB                             BIT(27)
#define BIT_PUB_CP_AHB_CLK_BUSMON6_EB                             BIT(26)
#define BIT_PUB_CP_AHB_CLK_BUSMON5_EB                             BIT(25)
#define BIT_PUB_CP_AHB_CLK_BUSMON4_EB                             BIT(24)
#define BIT_PUB_CP_AHB_CLK_BUSMON3_EB                             BIT(23)
#define BIT_PUB_CP_AHB_CLK_BUSMON2_EB                             BIT(22)
#define BIT_PUB_CP_AHB_CLK_BUSMON1_EB                             BIT(21)
#define BIT_PUB_CP_AHB_CLK_BUSMON0_EB                             BIT(20)
#define BIT_PUB_CP_AHB_RTC_EB                                     BIT(19)
#define BIT_PUB_CP_AHB_TFT_EB                                     BIT(18)
#define BIT_PUB_CP_AHB_IRAM_EB                                    BIT(11)
#define BIT_PUB_CP_AHB_DMA_LINK1_EB                               BIT(10)
#define BIT_PUB_CP_AHB_STM_TS_EN                                  BIT(9)
#define BIT_PUB_CP_AHB_CSSYS_EN                                   BIT(8)
#define BIT_PUB_CP_AHB_BUSMON1_EN                                 BIT(7)
#define BIT_PUB_CP_AHB_BUSMON0_EN                                 BIT(6)
#define BIT_PUB_CP_AHB_SEC1_EB                                    BIT(5)
#define BIT_PUB_CP_AHB_DMA_LINK0_EB                               BIT(4)
#define BIT_PUB_CP_AHB_SEC0_EB                                    BIT(3)
#define BIT_PUB_CP_AHB_BUSMON_PERF_EB                             BIT(2)
#define BIT_PUB_CP_AHB_DMA_EB                                     BIT(1)
#define BIT_PUB_CP_AHB_VIC_EB                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_WAKEUP_EN
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_WAKEUP_EN(x)                               (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_AHB_PAUSE
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_MCU_DOZE_SLEEP_EN                          BIT(6)
#define BIT_PUB_CP_AHB_MCU_PUB_DEEP_SLEEP_EN                      BIT(5)
#define BIT_PUB_CP_AHB_MCU_LIGHT_SLEEP_EN                         BIT(4)
#define BIT_PUB_CP_AHB_APB_SLEEP                                  BIT(3)
#define BIT_PUB_CP_AHB_MCU_DEEP_SLEEP_EN                          BIT(2)
#define BIT_PUB_CP_AHB_MCU_SYS_SLEEP_EN                           BIT(1)
#define BIT_PUB_CP_AHB_MCU_CORE_SLEEP                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_AHB_SLP_CTL
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_PUBCP_WAKEUP_WTLCP_EN                      BIT(13)
#define BIT_PUB_CP_AHB_CACTIVE_SLV0_WAKEUP_EN                     BIT(12)
#define BIT_PUB_CP_AHB_LP_AUTO_CTRL_EN                            BIT(11)
#define BIT_PUB_CP_AHB_SYS_SLP_TCM_RET_AUTO_EN                    BIT(10)
#define BIT_PUB_CP_AHB_CR5_SLP_TCM_RET_AUTO_EN                    BIT(9)
#define BIT_PUB_CP_AHB_MTX_LP_DISABLE                             BIT(8)
#define BIT_PUB_CP_AHB_PUBCP_DSP_ACCESS_EN                        BIT(7)
#define BIT_PUB_CP_AHB_PUBCP_WCDMA_ACCESS_EN                      BIT(6)
#define BIT_PUB_CP_AHB_ARM_DAHB_SLEEP_EN                          BIT(5)
#define BIT_PUB_CP_AHB_MCUMTX_AUTO_GATE_EN                        BIT(4)
#define BIT_PUB_CP_AHB_CLK_APB_AUTO_GATE_EN                       BIT(3)
#define BIT_PUB_CP_AHB_CR5_AXI_DIV2_AUTO_GATE_EN                  BIT(2)
#define BIT_PUB_CP_AHB_CR5_AXI_AUTO_GATE_EN                       BIT(1)
#define BIT_PUB_CP_AHB_CR5_CORE_AUTO_GATE_EN                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_AHB_SLP_STS
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_APB_PERI_SLEEP                             BIT(3)
#define BIT_PUB_CP_AHB_DMA_LINK1_BUSY                             BIT(2)
#define BIT_PUB_CP_AHB_DMA_BUSY                                   BIT(1)
#define BIT_PUB_CP_AHB_DMA_LINK0_BUSY                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_BUSMON_PERF_CTL
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_PER_BUSMON_SEL(x)                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_ROM_SEL_CTL
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_ROM_SEL_1                                  BIT(1)
#define BIT_PUB_CP_AHB_ROM_SEL_0                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_AHB_RST0_STS
// Register Offset : 0x0060
// Description     : AHB software reset
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_IRAM_SOFT_RST                              BIT(14)
#define BIT_PUB_CP_AHB_DMA_LINK1_SOFT_RST                         BIT(13)
#define BIT_PUB_CP_AHB_DMA_LINK0_SOFT_RST                         BIT(12)
#define BIT_PUB_CP_AHB_TFT_SOFT_RST                               BIT(11)
#define BIT_PUB_CP_AHB_SEC1_CMD_PARSER_RST                        BIT(8)
#define BIT_PUB_CP_AHB_SEC0_CMD_PARSER_RST                        BIT(7)
#define BIT_PUB_CP_AHB_BUSMON_PERF_SOFT_RST                       BIT(6)
#define BIT_PUB_CP_AHB_SEC1_SOFT_RST                              BIT(5)
#define BIT_PUB_CP_AHB_SEC0_SOFT_RST                              BIT(4)
#define BIT_PUB_CP_AHB_BUSMON1_SOFT_RST                           BIT(3)
#define BIT_PUB_CP_AHB_VIC_SOFT_RST                               BIT(2)
#define BIT_PUB_CP_AHB_BUSMON0_SOFT_RST                           BIT(1)
#define BIT_PUB_CP_AHB_DMA_SOFT_RST                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_CR5_DBG_CTRL
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_NIDEN_CR5                                  BIT(1)
#define BIT_PUB_CP_AHB_DBGEN_CR5                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_AHB_RSV_REG0
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_AHB_RSV_REG0(x)                            (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_SEL_VIC
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_SEL_VIC                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_NIC400_AR_QOS0
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_ARQOS_M4(x)                                (((x) & 0xF) << 16)
#define BIT_PUB_CP_AHB_ARQOS_M3(x)                                (((x) & 0xF) << 12)
#define BIT_PUB_CP_AHB_ARQOS_M2(x)                                (((x) & 0xF) << 8)
#define BIT_PUB_CP_AHB_ARQOS_M1(x)                                (((x) & 0xF) << 4)
#define BIT_PUB_CP_AHB_ARQOS_M0(x)                                (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_NIC400_AR_QOS1
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_ARQOS_M9(x)                                (((x) & 0xF) << 16)
#define BIT_PUB_CP_AHB_ARQOS_M8(x)                                (((x) & 0xF) << 12)
#define BIT_PUB_CP_AHB_ARQOS_M7(x)                                (((x) & 0xF) << 8)
#define BIT_PUB_CP_AHB_ARQOS_M6(x)                                (((x) & 0xF) << 4)
#define BIT_PUB_CP_AHB_ARQOS_M5(x)                                (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_NIC400_AW_QOS0
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_AWQOS_M4(x)                                (((x) & 0xF) << 16)
#define BIT_PUB_CP_AHB_AWQOS_M3(x)                                (((x) & 0xF) << 12)
#define BIT_PUB_CP_AHB_AWQOS_M2(x)                                (((x) & 0xF) << 8)
#define BIT_PUB_CP_AHB_AWQOS_M1(x)                                (((x) & 0xF) << 4)
#define BIT_PUB_CP_AHB_AWQOS_M0(x)                                (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_NIC400_AW_QOS1
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_AWQOS_M9(x)                                (((x) & 0xF) << 16)
#define BIT_PUB_CP_AHB_AWQOS_M8(x)                                (((x) & 0xF) << 12)
#define BIT_PUB_CP_AHB_AWQOS_M7(x)                                (((x) & 0xF) << 8)
#define BIT_PUB_CP_AHB_AWQOS_M6(x)                                (((x) & 0xF) << 4)
#define BIT_PUB_CP_AHB_AWQOS_M5(x)                                (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_ASYNC_BRIDGE_STS
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_AXI_DETECTOR_OVERFLOW                      BIT(1)
#define BIT_PUB_CP_AHB_BRIDGE_TRANS_IDLE                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_ASYNC_BRG_CFG_0
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_ASYNC_BRG_AF_AR_CH(x)                      (((x) & 0xF) << 14)
#define BIT_PUB_CP_AHB_ASYNC_BRG_AE_AR_CH(x)                      (((x) & 0xF) << 10)
#define BIT_PUB_CP_AHB_ASYNC_BRG_AF_R_CH(x)                       (((x) & 0x1F) << 5)
#define BIT_PUB_CP_AHB_ASYNC_BRG_AE_R_CH(x)                       (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_ASYNC_BRG_CFG_1
// Register Offset : 0x008C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_ASYNC_BRG_AF_AW_CH(x)                      (((x) & 0xF) << 24)
#define BIT_PUB_CP_AHB_ASYNC_BRG_AE_AW_CH(x)                      (((x) & 0xF) << 20)
#define BIT_PUB_CP_AHB_ASYNC_BRG_AF_W_CH(x)                       (((x) & 0x1F) << 15)
#define BIT_PUB_CP_AHB_ASYNC_BRG_AE_W_CH(x)                       (((x) & 0x1F) << 10)
#define BIT_PUB_CP_AHB_ASYNC_BRG_AF_B_CH(x)                       (((x) & 0x1F) << 5)
#define BIT_PUB_CP_AHB_ASYNC_BRG_AE_B_CH(x)                       (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_M0
// Register Offset : 0x0100
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_M0(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_M1
// Register Offset : 0x0104
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_M1(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_M2
// Register Offset : 0x0108
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_M2(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_M3
// Register Offset : 0x010C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_M3(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_M4
// Register Offset : 0x0110
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_M4(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_M5
// Register Offset : 0x0114
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_M5(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_M6
// Register Offset : 0x0118
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_M6(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_M7
// Register Offset : 0x011C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_M7(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_M8
// Register Offset : 0x0120
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_M8(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_M9
// Register Offset : 0x0124
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_M9(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_MAIN
// Register Offset : 0x0128
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_MAIN(x)                             (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_S0
// Register Offset : 0x012C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_S0(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_S2
// Register Offset : 0x0130
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_S2(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_S3
// Register Offset : 0x0134
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_S3(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_S4
// Register Offset : 0x0138
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_S4(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_S5
// Register Offset : 0x013C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_S5(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_S6
// Register Offset : 0x0140
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_S6(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_ABM
// Register Offset : 0x0144
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_ABM(x)                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_LP_NUM_ABS
// Register Offset : 0x0148
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_LP_NUM_ABS(x)                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_AHB_ASYNC_BRG_DBG0
// Register Offset : 0x3090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_AHB_ASYNC_BRG_DBG(x)                           (((x) & 0xFFFFFFFF))


#endif // _PUB_CP_AHB_REG_H
