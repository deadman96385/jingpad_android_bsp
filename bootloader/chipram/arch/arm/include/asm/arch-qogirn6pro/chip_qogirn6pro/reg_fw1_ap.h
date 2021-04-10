/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-06 15:47:51
 *
 */

#ifndef REG_FW1_AP_H
#define REG_FW1_AP_H

#define CTL_BASE_REG_FW1_AP 0x3280A000

#define REG_REG_FW1_AP_REG_RD_CTRL_0          ( CTL_BASE_REG_FW1_AP + 0x0000 )
#define REG_REG_FW1_AP_REG_RD_CTRL_1          ( CTL_BASE_REG_FW1_AP + 0x0004 )
#define REG_REG_FW1_AP_REG_WR_CTRL_0          ( CTL_BASE_REG_FW1_AP + 0x0008 )
#define REG_REG_FW1_AP_REG_WR_CTRL_1          ( CTL_BASE_REG_FW1_AP + 0x000C )
#define REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY0   ( CTL_BASE_REG_FW1_AP + 0x0010 )
#define REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY1   ( CTL_BASE_REG_FW1_AP + 0x0014 )
#define REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY2   ( CTL_BASE_REG_FW1_AP + 0x0018 )
#define REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY3   ( CTL_BASE_REG_FW1_AP + 0x001C )
#define REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY4   ( CTL_BASE_REG_FW1_AP + 0x0020 )
#define REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY5   ( CTL_BASE_REG_FW1_AP + 0x0024 )
#define REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY6   ( CTL_BASE_REG_FW1_AP + 0x0028 )
#define REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY7   ( CTL_BASE_REG_FW1_AP + 0x002C )
#define REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY8   ( CTL_BASE_REG_FW1_AP + 0x0030 )
#define REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY9   ( CTL_BASE_REG_FW1_AP + 0x0034 )
#define REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY10  ( CTL_BASE_REG_FW1_AP + 0x0038 )
#define REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY11  ( CTL_BASE_REG_FW1_AP + 0x003C )
#define REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY12  ( CTL_BASE_REG_FW1_AP + 0x0040 )
#define REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY13  ( CTL_BASE_REG_FW1_AP + 0x0044 )
#define REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY14  ( CTL_BASE_REG_FW1_AP + 0x0048 )
#define REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY15  ( CTL_BASE_REG_FW1_AP + 0x004C )
#define REG_REG_FW1_AP_BIT_CTRL_ARRAY0        ( CTL_BASE_REG_FW1_AP + 0x0050 )
#define REG_REG_FW1_AP_BIT_CTRL_ARRAY1        ( CTL_BASE_REG_FW1_AP + 0x0054 )
#define REG_REG_FW1_AP_BIT_CTRL_ARRAY2        ( CTL_BASE_REG_FW1_AP + 0x0058 )
#define REG_REG_FW1_AP_BIT_CTRL_ARRAY3        ( CTL_BASE_REG_FW1_AP + 0x005C )
#define REG_REG_FW1_AP_BIT_CTRL_ARRAY4        ( CTL_BASE_REG_FW1_AP + 0x0060 )
#define REG_REG_FW1_AP_BIT_CTRL_ARRAY5        ( CTL_BASE_REG_FW1_AP + 0x0064 )
#define REG_REG_FW1_AP_BIT_CTRL_ARRAY6        ( CTL_BASE_REG_FW1_AP + 0x0068 )
#define REG_REG_FW1_AP_BIT_CTRL_ARRAY7        ( CTL_BASE_REG_FW1_AP + 0x006C )
#define REG_REG_FW1_AP_BIT_CTRL_ARRAY8        ( CTL_BASE_REG_FW1_AP + 0x0070 )
#define REG_REG_FW1_AP_BIT_CTRL_ARRAY9        ( CTL_BASE_REG_FW1_AP + 0x0074 )
#define REG_REG_FW1_AP_BIT_CTRL_ARRAY10       ( CTL_BASE_REG_FW1_AP + 0x0078 )
#define REG_REG_FW1_AP_BIT_CTRL_ARRAY11       ( CTL_BASE_REG_FW1_AP + 0x007C )
#define REG_REG_FW1_AP_BIT_CTRL_ARRAY12       ( CTL_BASE_REG_FW1_AP + 0x0080 )
#define REG_REG_FW1_AP_BIT_CTRL_ARRAY13       ( CTL_BASE_REG_FW1_AP + 0x0084 )
#define REG_REG_FW1_AP_BIT_CTRL_ARRAY14       ( CTL_BASE_REG_FW1_AP + 0x0088 )
#define REG_REG_FW1_AP_BIT_CTRL_ARRAY15       ( CTL_BASE_REG_FW1_AP + 0x008C )

/* REG_REG_FW1_AP_REG_RD_CTRL_0 */

#define BIT_REG_FW1_AP_MERGE_M1_LPC_RD_SEC                      BIT(31)
#define BIT_REG_FW1_AP_MERGE_M0_LPC_RD_SEC                      BIT(30)
#define BIT_REG_FW1_AP_S4_LPC_RD_SEC                            BIT(29)
#define BIT_REG_FW1_AP_S3_LPC_RD_SEC                            BIT(28)
#define BIT_REG_FW1_AP_S2_LPC_RD_SEC                            BIT(27)
#define BIT_REG_FW1_AP_S1_LPC_RD_SEC                            BIT(26)
#define BIT_REG_FW1_AP_S0_LPC_RD_SEC                            BIT(25)
#define BIT_REG_FW1_AP_MAIN_LPC_RD_SEC                          BIT(24)
#define BIT_REG_FW1_AP_M7_LPC_RD_SEC                            BIT(23)
#define BIT_REG_FW1_AP_M6_LPC_RD_SEC                            BIT(22)
#define BIT_REG_FW1_AP_M5_LPC_RD_SEC                            BIT(21)
#define BIT_REG_FW1_AP_M4_LPC_RD_SEC                            BIT(20)
#define BIT_REG_FW1_AP_M3_LPC_RD_SEC                            BIT(19)
#define BIT_REG_FW1_AP_M2_LPC_RD_SEC                            BIT(18)
#define BIT_REG_FW1_AP_M1_LPC_RD_SEC                            BIT(17)
#define BIT_REG_FW1_AP_M0_LPC_RD_SEC                            BIT(16)
#define BIT_REG_FW1_AP_AP_ASYNC_BRG_RD_SEC                      BIT(15)
#define BIT_REG_FW1_AP_S5_LPC_RD_SEC                            BIT(14)
#define BIT_REG_FW1_AP_S6_LPC_RD_SEC                            BIT(13)
#define BIT_REG_FW1_AP_DISP_ASYNC_BRG_RD_SEC                    BIT(12)
#define BIT_REG_FW1_AP_VDSP_ASYNC_BRG_RD_SEC                    BIT(11)
#define BIT_REG_FW1_AP_MISC_CKG_EN_RD_SEC                       BIT(10)
#define BIT_REG_FW1_AP_AP_SYS_CLK_EN_FRC_ON_1_RD_SEC            BIT(9)
#define BIT_REG_FW1_AP_AP_SYS_CLK_EN_FRC_ON_0_RD_SEC            BIT(8)
#define BIT_REG_FW1_AP_AP_SYS_CLK_EN_FRC_OFF_1_RD_SEC           BIT(7)
#define BIT_REG_FW1_AP_AP_SYS_CLK_EN_FRC_OFF_0_RD_SEC           BIT(6)
#define BIT_REG_FW1_AP_CLOCK_FREQUENCY_DOWN_RD_SEC              BIT(5)
#define BIT_REG_FW1_AP_HOLDING_PEN_RD_SEC                       BIT(4)
#define BIT_REG_FW1_AP_AP_SYS_AUTO_SLEEP_CFG_RD_SEC             BIT(3)
#define BIT_REG_FW1_AP_AP_SYS_FORCE_SLEEP_CFG_RD_SEC            BIT(2)
#define BIT_REG_FW1_AP_AHB_RST_RD_SEC                           BIT(1)
#define BIT_REG_FW1_AP_AHB_EB_RD_SEC                            BIT(0)

/* REG_REG_FW1_AP_REG_RD_CTRL_1 */

#define BIT_REG_FW1_AP_CHIP_ID_RD_SEC                           BIT(30)
#define BIT_REG_FW1_AP_VDSP_INT_CTRL_RD_SEC                     BIT(29)
#define BIT_REG_FW1_AP_VDSP_LP_CTRL_RD_SEC                      BIT(28)
#define BIT_REG_FW1_AP_VDSP_FATAL_INFO_HIGH_RD_SEC              BIT(27)
#define BIT_REG_FW1_AP_VDSP_FATAL_INFO_LOW_RD_SEC               BIT(26)
#define BIT_REG_FW1_AP_VDSP_FUNC_CTRL_RD_SEC                    BIT(25)
#define BIT_REG_FW1_AP_DSI_PHY_RD_SEC                           BIT(24)
#define BIT_REG_FW1_AP_AP_QOS_CFG_RD_SEC                        BIT(23)
#define BIT_REG_FW1_AP_CACHE_EMMC_SDIO_RD_SEC                   BIT(22)
#define BIT_REG_FW1_AP_SYS_RST_RD_SEC                           BIT(21)
#define BIT_REG_FW1_AP_MERGE_VDMA_S0_LPC_RD_SEC                 BIT(20)
#define BIT_REG_FW1_AP_MERGE_VDMA_M1_LPC_RD_SEC                 BIT(19)
#define BIT_REG_FW1_AP_MERGE_VDMA_M0_LPC_RD_SEC                 BIT(18)
#define BIT_REG_FW1_AP_MERGE_VDSP_S1_LPC_RD_SEC                 BIT(17)
#define BIT_REG_FW1_AP_MERGE_VDSP_S0_LPC_RD_SEC                 BIT(16)
#define BIT_REG_FW1_AP_MERGE_VDSP_MAIN_LPC_RD_SEC               BIT(15)
#define BIT_REG_FW1_AP_MERGE_VDSP_M3_LPC_RD_SEC                 BIT(14)
#define BIT_REG_FW1_AP_MERGE_VDSP_M2_LPC_RD_SEC                 BIT(13)
#define BIT_REG_FW1_AP_MERGE_VDSP_M1_LPC_RD_SEC                 BIT(12)
#define BIT_REG_FW1_AP_MERGE_VDSP_M0_LPC_RD_SEC                 BIT(11)
#define BIT_REG_FW1_AP_AP_QOS3_SEL_RD_SEC                       BIT(10)
#define BIT_REG_FW1_AP_AP_QOS3_RD_SEC                           BIT(9)
#define BIT_REG_FW1_AP_ASYNC_BRIDGE_DEBUG_SIGNAL_W_VDSP_RD_SEC  BIT(8)
#define BIT_REG_FW1_AP_ASYNC_BRIDGE_DEBUG_SIGNAL_W_AP_RD_SEC    BIT(7)
#define BIT_REG_FW1_AP_ASYNC_BRIDGE_DEBUG_SIGNAL_W_DISP_RD_SEC  BIT(6)
#define BIT_REG_FW1_AP_ASYNC_BRIDGE_IDLE_OVERFLOW_RD_SEC        BIT(5)
#define BIT_REG_FW1_AP_AP_QOS2_RD_SEC                           BIT(4)
#define BIT_REG_FW1_AP_AP_QOS1_RD_SEC                           BIT(3)
#define BIT_REG_FW1_AP_AP_QOS0_RD_SEC                           BIT(2)
#define BIT_REG_FW1_AP_MERGE_S0_LPC_RD_SEC                      BIT(1)
#define BIT_REG_FW1_AP_S7_LPC_RD_SEC                            BIT(0)

/* REG_REG_FW1_AP_REG_WR_CTRL_0 */

#define BIT_REG_FW1_AP_MERGE_M1_LPC_WR_SEC                      BIT(31)
#define BIT_REG_FW1_AP_MERGE_M0_LPC_WR_SEC                      BIT(30)
#define BIT_REG_FW1_AP_S4_LPC_WR_SEC                            BIT(29)
#define BIT_REG_FW1_AP_S3_LPC_WR_SEC                            BIT(28)
#define BIT_REG_FW1_AP_S2_LPC_WR_SEC                            BIT(27)
#define BIT_REG_FW1_AP_S1_LPC_WR_SEC                            BIT(26)
#define BIT_REG_FW1_AP_S0_LPC_WR_SEC                            BIT(25)
#define BIT_REG_FW1_AP_MAIN_LPC_WR_SEC                          BIT(24)
#define BIT_REG_FW1_AP_M7_LPC_WR_SEC                            BIT(23)
#define BIT_REG_FW1_AP_M6_LPC_WR_SEC                            BIT(22)
#define BIT_REG_FW1_AP_M5_LPC_WR_SEC                            BIT(21)
#define BIT_REG_FW1_AP_M4_LPC_WR_SEC                            BIT(20)
#define BIT_REG_FW1_AP_M3_LPC_WR_SEC                            BIT(19)
#define BIT_REG_FW1_AP_M2_LPC_WR_SEC                            BIT(18)
#define BIT_REG_FW1_AP_M1_LPC_WR_SEC                            BIT(17)
#define BIT_REG_FW1_AP_M0_LPC_WR_SEC                            BIT(16)
#define BIT_REG_FW1_AP_AP_ASYNC_BRG_WR_SEC                      BIT(15)
#define BIT_REG_FW1_AP_S5_LPC_WR_SEC                            BIT(14)
#define BIT_REG_FW1_AP_S6_LPC_WR_SEC                            BIT(13)
#define BIT_REG_FW1_AP_DISP_ASYNC_BRG_WR_SEC                    BIT(12)
#define BIT_REG_FW1_AP_VDSP_ASYNC_BRG_WR_SEC                    BIT(11)
#define BIT_REG_FW1_AP_MISC_CKG_EN_WR_SEC                       BIT(10)
#define BIT_REG_FW1_AP_AP_SYS_CLK_EN_FRC_ON_1_WR_SEC            BIT(9)
#define BIT_REG_FW1_AP_AP_SYS_CLK_EN_FRC_ON_0_WR_SEC            BIT(8)
#define BIT_REG_FW1_AP_AP_SYS_CLK_EN_FRC_OFF_1_WR_SEC           BIT(7)
#define BIT_REG_FW1_AP_AP_SYS_CLK_EN_FRC_OFF_0_WR_SEC           BIT(6)
#define BIT_REG_FW1_AP_CLOCK_FREQUENCY_DOWN_WR_SEC              BIT(5)
#define BIT_REG_FW1_AP_HOLDING_PEN_WR_SEC                       BIT(4)
#define BIT_REG_FW1_AP_AP_SYS_AUTO_SLEEP_CFG_WR_SEC             BIT(3)
#define BIT_REG_FW1_AP_AP_SYS_FORCE_SLEEP_CFG_WR_SEC            BIT(2)
#define BIT_REG_FW1_AP_AHB_RST_WR_SEC                           BIT(1)
#define BIT_REG_FW1_AP_AHB_EB_WR_SEC                            BIT(0)

/* REG_REG_FW1_AP_REG_WR_CTRL_1 */

#define BIT_REG_FW1_AP_CHIP_ID_WR_SEC                           BIT(30)
#define BIT_REG_FW1_AP_VDSP_INT_CTRL_WR_SEC                     BIT(29)
#define BIT_REG_FW1_AP_VDSP_LP_CTRL_WR_SEC                      BIT(28)
#define BIT_REG_FW1_AP_VDSP_FATAL_INFO_HIGH_WR_SEC              BIT(27)
#define BIT_REG_FW1_AP_VDSP_FATAL_INFO_LOW_WR_SEC               BIT(26)
#define BIT_REG_FW1_AP_VDSP_FUNC_CTRL_WR_SEC                    BIT(25)
#define BIT_REG_FW1_AP_DSI_PHY_WR_SEC                           BIT(24)
#define BIT_REG_FW1_AP_AP_QOS_CFG_WR_SEC                        BIT(23)
#define BIT_REG_FW1_AP_CACHE_EMMC_SDIO_WR_SEC                   BIT(22)
#define BIT_REG_FW1_AP_SYS_RST_WR_SEC                           BIT(21)
#define BIT_REG_FW1_AP_MERGE_VDMA_S0_LPC_WR_SEC                 BIT(20)
#define BIT_REG_FW1_AP_MERGE_VDMA_M1_LPC_WR_SEC                 BIT(19)
#define BIT_REG_FW1_AP_MERGE_VDMA_M0_LPC_WR_SEC                 BIT(18)
#define BIT_REG_FW1_AP_MERGE_VDSP_S1_LPC_WR_SEC                 BIT(17)
#define BIT_REG_FW1_AP_MERGE_VDSP_S0_LPC_WR_SEC                 BIT(16)
#define BIT_REG_FW1_AP_MERGE_VDSP_MAIN_LPC_WR_SEC               BIT(15)
#define BIT_REG_FW1_AP_MERGE_VDSP_M3_LPC_WR_SEC                 BIT(14)
#define BIT_REG_FW1_AP_MERGE_VDSP_M2_LPC_WR_SEC                 BIT(13)
#define BIT_REG_FW1_AP_MERGE_VDSP_M1_LPC_WR_SEC                 BIT(12)
#define BIT_REG_FW1_AP_MERGE_VDSP_M0_LPC_WR_SEC                 BIT(11)
#define BIT_REG_FW1_AP_AP_QOS3_SEL_WR_SEC                       BIT(10)
#define BIT_REG_FW1_AP_AP_QOS3_WR_SEC                           BIT(9)
#define BIT_REG_FW1_AP_ASYNC_BRIDGE_DEBUG_SIGNAL_W_VDSP_WR_SEC  BIT(8)
#define BIT_REG_FW1_AP_ASYNC_BRIDGE_DEBUG_SIGNAL_W_AP_WR_SEC    BIT(7)
#define BIT_REG_FW1_AP_ASYNC_BRIDGE_DEBUG_SIGNAL_W_DISP_WR_SEC  BIT(6)
#define BIT_REG_FW1_AP_ASYNC_BRIDGE_IDLE_OVERFLOW_WR_SEC        BIT(5)
#define BIT_REG_FW1_AP_AP_QOS2_WR_SEC                           BIT(4)
#define BIT_REG_FW1_AP_AP_QOS1_WR_SEC                           BIT(3)
#define BIT_REG_FW1_AP_AP_QOS0_WR_SEC                           BIT(2)
#define BIT_REG_FW1_AP_MERGE_S0_LPC_WR_SEC                      BIT(1)
#define BIT_REG_FW1_AP_S7_LPC_WR_SEC                            BIT(0)

/* REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY0 */

#define BIT_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY0(x)                  (((x) & 0xFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY1 */

#define BIT_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY1(x)                  (((x) & 0xFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY2 */

#define BIT_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY2(x)                  (((x) & 0xFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY3 */

#define BIT_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY3(x)                  (((x) & 0xFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY4 */

#define BIT_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY4(x)                  (((x) & 0xFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY5 */

#define BIT_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY5(x)                  (((x) & 0xFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY6 */

#define BIT_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY6(x)                  (((x) & 0xFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY7 */

#define BIT_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY7(x)                  (((x) & 0xFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY8 */

#define BIT_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY8(x)                  (((x) & 0xFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY9 */

#define BIT_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY9(x)                  (((x) & 0xFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY10 */

#define BIT_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY10(x)                 (((x) & 0xFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY11 */

#define BIT_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY11(x)                 (((x) & 0xFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY12 */

#define BIT_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY12(x)                 (((x) & 0xFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY13 */

#define BIT_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY13(x)                 (((x) & 0xFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY14 */

#define BIT_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY14(x)                 (((x) & 0xFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY15 */

#define BIT_REG_FW1_AP_BIT_CTRL_ADDR_ARRAY15(x)                 (((x) & 0xFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ARRAY0 */

#define BIT_REG_FW1_AP_BIT_CTRL_ARRAY0(x)                       (((x) & 0xFFFFFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ARRAY1 */

#define BIT_REG_FW1_AP_BIT_CTRL_ARRAY1(x)                       (((x) & 0xFFFFFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ARRAY2 */

#define BIT_REG_FW1_AP_BIT_CTRL_ARRAY2(x)                       (((x) & 0xFFFFFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ARRAY3 */

#define BIT_REG_FW1_AP_BIT_CTRL_ARRAY3(x)                       (((x) & 0xFFFFFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ARRAY4 */

#define BIT_REG_FW1_AP_BIT_CTRL_ARRAY4(x)                       (((x) & 0xFFFFFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ARRAY5 */

#define BIT_REG_FW1_AP_BIT_CTRL_ARRAY5(x)                       (((x) & 0xFFFFFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ARRAY6 */

#define BIT_REG_FW1_AP_BIT_CTRL_ARRAY6(x)                       (((x) & 0xFFFFFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ARRAY7 */

#define BIT_REG_FW1_AP_BIT_CTRL_ARRAY7(x)                       (((x) & 0xFFFFFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ARRAY8 */

#define BIT_REG_FW1_AP_BIT_CTRL_ARRAY8(x)                       (((x) & 0xFFFFFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ARRAY9 */

#define BIT_REG_FW1_AP_BIT_CTRL_ARRAY9(x)                       (((x) & 0xFFFFFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ARRAY10 */

#define BIT_REG_FW1_AP_BIT_CTRL_ARRAY10(x)                      (((x) & 0xFFFFFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ARRAY11 */

#define BIT_REG_FW1_AP_BIT_CTRL_ARRAY11(x)                      (((x) & 0xFFFFFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ARRAY12 */

#define BIT_REG_FW1_AP_BIT_CTRL_ARRAY12(x)                      (((x) & 0xFFFFFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ARRAY13 */

#define BIT_REG_FW1_AP_BIT_CTRL_ARRAY13(x)                      (((x) & 0xFFFFFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ARRAY14 */

#define BIT_REG_FW1_AP_BIT_CTRL_ARRAY14(x)                      (((x) & 0xFFFFFFFF))

/* REG_REG_FW1_AP_BIT_CTRL_ARRAY15 */

#define BIT_REG_FW1_AP_BIT_CTRL_ARRAY15(x)                      (((x) & 0xFFFFFFFF))

#endif