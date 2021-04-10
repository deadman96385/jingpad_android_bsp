/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-18 10:55:38
 *
 */


#ifndef REG_FW0_IPA_H
#define REG_FW0_IPA_H

#define CTL_BASE_REG_FW0_IPA 0x32832000


#define REG_REG_FW0_IPA_REG_RD_CTRL_0          ( CTL_BASE_REG_FW0_IPA + 0x0000 )
#define REG_REG_FW0_IPA_REG_RD_CTRL_1          ( CTL_BASE_REG_FW0_IPA + 0x0004 )
#define REG_REG_FW0_IPA_REG_WR_CTRL_0          ( CTL_BASE_REG_FW0_IPA + 0x0008 )
#define REG_REG_FW0_IPA_REG_WR_CTRL_1          ( CTL_BASE_REG_FW0_IPA + 0x000C )
#define REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY0   ( CTL_BASE_REG_FW0_IPA + 0x0010 )
#define REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY1   ( CTL_BASE_REG_FW0_IPA + 0x0014 )
#define REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY2   ( CTL_BASE_REG_FW0_IPA + 0x0018 )
#define REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY3   ( CTL_BASE_REG_FW0_IPA + 0x001C )
#define REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY4   ( CTL_BASE_REG_FW0_IPA + 0x0020 )
#define REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY5   ( CTL_BASE_REG_FW0_IPA + 0x0024 )
#define REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY6   ( CTL_BASE_REG_FW0_IPA + 0x0028 )
#define REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY7   ( CTL_BASE_REG_FW0_IPA + 0x002C )
#define REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY8   ( CTL_BASE_REG_FW0_IPA + 0x0030 )
#define REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY9   ( CTL_BASE_REG_FW0_IPA + 0x0034 )
#define REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY10  ( CTL_BASE_REG_FW0_IPA + 0x0038 )
#define REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY11  ( CTL_BASE_REG_FW0_IPA + 0x003C )
#define REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY12  ( CTL_BASE_REG_FW0_IPA + 0x0040 )
#define REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY13  ( CTL_BASE_REG_FW0_IPA + 0x0044 )
#define REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY14  ( CTL_BASE_REG_FW0_IPA + 0x0048 )
#define REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY15  ( CTL_BASE_REG_FW0_IPA + 0x004C )
#define REG_REG_FW0_IPA_BIT_CTRL_ARRAY0        ( CTL_BASE_REG_FW0_IPA + 0x0050 )
#define REG_REG_FW0_IPA_BIT_CTRL_ARRAY1        ( CTL_BASE_REG_FW0_IPA + 0x0054 )
#define REG_REG_FW0_IPA_BIT_CTRL_ARRAY2        ( CTL_BASE_REG_FW0_IPA + 0x0058 )
#define REG_REG_FW0_IPA_BIT_CTRL_ARRAY3        ( CTL_BASE_REG_FW0_IPA + 0x005C )
#define REG_REG_FW0_IPA_BIT_CTRL_ARRAY4        ( CTL_BASE_REG_FW0_IPA + 0x0060 )
#define REG_REG_FW0_IPA_BIT_CTRL_ARRAY5        ( CTL_BASE_REG_FW0_IPA + 0x0064 )
#define REG_REG_FW0_IPA_BIT_CTRL_ARRAY6        ( CTL_BASE_REG_FW0_IPA + 0x0068 )
#define REG_REG_FW0_IPA_BIT_CTRL_ARRAY7        ( CTL_BASE_REG_FW0_IPA + 0x006C )
#define REG_REG_FW0_IPA_BIT_CTRL_ARRAY8        ( CTL_BASE_REG_FW0_IPA + 0x0070 )
#define REG_REG_FW0_IPA_BIT_CTRL_ARRAY9        ( CTL_BASE_REG_FW0_IPA + 0x0074 )
#define REG_REG_FW0_IPA_BIT_CTRL_ARRAY10       ( CTL_BASE_REG_FW0_IPA + 0x0078 )
#define REG_REG_FW0_IPA_BIT_CTRL_ARRAY11       ( CTL_BASE_REG_FW0_IPA + 0x007C )
#define REG_REG_FW0_IPA_BIT_CTRL_ARRAY12       ( CTL_BASE_REG_FW0_IPA + 0x0080 )
#define REG_REG_FW0_IPA_BIT_CTRL_ARRAY13       ( CTL_BASE_REG_FW0_IPA + 0x0084 )
#define REG_REG_FW0_IPA_BIT_CTRL_ARRAY14       ( CTL_BASE_REG_FW0_IPA + 0x0088 )
#define REG_REG_FW0_IPA_BIT_CTRL_ARRAY15       ( CTL_BASE_REG_FW0_IPA + 0x008C )

/* REG_REG_FW0_IPA_REG_RD_CTRL_0 */

#define BIT_REG_FW0_IPA_IPA_SYS_STATUS_RD_SEC                BIT(31)
#define BIT_REG_FW0_IPA_MISC_CFG_RD_SEC                      BIT(30)
#define BIT_REG_FW0_IPA_IPA_MTX_FREQ_LSLP_ALLOW_RD_SEC       BIT(29)
#define BIT_REG_FW0_IPA_IPA_MTX_FREQ_ALLOW_RD_SEC            BIT(28)
#define BIT_REG_FW0_IPA_MATRIX_LPC_CTRL_RD_SEC               BIT(27)
#define BIT_REG_FW0_IPA_MTX_QOS_1_RD_SEC                     BIT(26)
#define BIT_REG_FW0_IPA_MTX_QOS_0_RD_SEC                     BIT(25)
#define BIT_REG_FW0_IPA_ASYNC_BRG_G3_LPC_RD_SEC              BIT(24)
#define BIT_REG_FW0_IPA_ASYNC_BRG_G2_LPC_RD_SEC              BIT(23)
#define BIT_REG_FW0_IPA_S8_LPC_RD_SEC                        BIT(22)
#define BIT_REG_FW0_IPA_S7_LPC_RD_SEC                        BIT(21)
#define BIT_REG_FW0_IPA_S6_LPC_RD_SEC                        BIT(20)
#define BIT_REG_FW0_IPA_S5_LPC_RD_SEC                        BIT(19)
#define BIT_REG_FW0_IPA_S4_LPC_RD_SEC                        BIT(18)
#define BIT_REG_FW0_IPA_S3_LPC_RD_SEC                        BIT(17)
#define BIT_REG_FW0_IPA_S2_LPC_RD_SEC                        BIT(16)
#define BIT_REG_FW0_IPA_S1_LPC_RD_SEC                        BIT(15)
#define BIT_REG_FW0_IPA_S0_LPC_RD_SEC                        BIT(14)
#define BIT_REG_FW0_IPA_MAIN_MTX_LPC_RD_SEC                  BIT(13)
#define BIT_REG_FW0_IPA_M7_LPC_RD_SEC                        BIT(12)
#define BIT_REG_FW0_IPA_M6_LPC_RD_SEC                        BIT(11)
#define BIT_REG_FW0_IPA_M5_LPC_RD_SEC                        BIT(10)
#define BIT_REG_FW0_IPA_M4_LPC_RD_SEC                        BIT(9)
#define BIT_REG_FW0_IPA_M3_LPC_RD_SEC                        BIT(8)
#define BIT_REG_FW0_IPA_M2_LPC_RD_SEC                        BIT(7)
#define BIT_REG_FW0_IPA_M1_LPC_RD_SEC                        BIT(6)
#define BIT_REG_FW0_IPA_M0_LPC_RD_SEC                        BIT(5)
#define BIT_REG_FW0_IPA_USB_CTL0_RD_SEC                      BIT(4)
#define BIT_REG_FW0_IPA_PCIE2_CTL0_RD_SEC                    BIT(3)
#define BIT_REG_FW0_IPA_PCIE3_CTL0_RD_SEC                    BIT(2)
#define BIT_REG_FW0_IPA_IPA_EB_RD_SEC                        BIT(1)
#define BIT_REG_FW0_IPA_IPA_RST_RD_SEC                       BIT(0)

/* REG_REG_FW0_IPA_REG_RD_CTRL_1 */

#define BIT_REG_FW0_IPA_INT_TO_CM4_EN_REG_RD_SEC             BIT(23)
#define BIT_REG_FW0_IPA_INT_TO_AP_EN_REG_RD_SEC              BIT(22)
#define BIT_REG_FW0_IPA_INT_TO_CM4_STATUS_REG_RD_SEC         BIT(21)
#define BIT_REG_FW0_IPA_INT_TO_AP_STATUS_REG_RD_SEC          BIT(20)
#define BIT_REG_FW0_IPA_CM4_SPORT_REMAP_CTRL_REG_RD_SEC      BIT(19)
#define BIT_REG_FW0_IPA_CM4_DPORT_REMAP_CTRL_REG_RD_SEC      BIT(18)
#define BIT_REG_FW0_IPA_CM4_IPORT_REMAP_CTRL_REG_RD_SEC      BIT(17)
#define BIT_REG_FW0_IPA_CM4_DCACHE_CTRL_REG_RD_SEC           BIT(16)
#define BIT_REG_FW0_IPA_CM4_ICACHE_CTRL_REG_RD_SEC           BIT(15)
#define BIT_REG_FW0_IPA_CM4_WDG_RST_FLAG_RD_SEC              BIT(14)
#define BIT_REG_FW0_IPA_CM4_INT_STAT_RD_SEC                  BIT(13)
#define BIT_REG_FW0_IPA_CM4_MAIN_STATOUT_RD_SEC              BIT(12)
#define BIT_REG_FW0_IPA_CM4_CORE_AUXFAULT_CFG_RD_SEC         BIT(11)
#define BIT_REG_FW0_IPA_CM4_CORE_SYSTICK_CFG_RD_SEC          BIT(10)
#define BIT_REG_FW0_IPA_CM4_CORE_CFG1_RD_SEC                 BIT(9)
#define BIT_REG_FW0_IPA_CM4_SYS_SOFT_RST_RD_SEC              BIT(8)
#define BIT_REG_FW0_IPA_PCIE3_DEBUG_RD_SEC                   BIT(7)
#define BIT_REG_FW0_IPA_PCIE2_DEBUG_RD_SEC                   BIT(6)
#define BIT_REG_FW0_IPA_USB3_DEBUG_2_RD_SEC                  BIT(5)
#define BIT_REG_FW0_IPA_USB3_DEBUG_1_RD_SEC                  BIT(4)
#define BIT_REG_FW0_IPA_USB3_DEBUG_0_RD_SEC                  BIT(3)
#define BIT_REG_FW0_IPA_GEN3_BRIDGE_DEBUG_SIGNAL_W_RD_SEC    BIT(2)
#define BIT_REG_FW0_IPA_GEN2_BRIDGE_DEBUG_SIGNAL_W_RD_SEC    BIT(1)
#define BIT_REG_FW0_IPA_AP2IPA_BRIDGE_DEBUG_SIGNAL_R_RD_SEC  BIT(0)

/* REG_REG_FW0_IPA_REG_WR_CTRL_0 */

#define BIT_REG_FW0_IPA_IPA_SYS_STATUS_WR_SEC                BIT(31)
#define BIT_REG_FW0_IPA_MISC_CFG_WR_SEC                      BIT(30)
#define BIT_REG_FW0_IPA_IPA_MTX_FREQ_LSLP_ALLOW_WR_SEC       BIT(29)
#define BIT_REG_FW0_IPA_IPA_MTX_FREQ_ALLOW_WR_SEC            BIT(28)
#define BIT_REG_FW0_IPA_MATRIX_LPC_CTRL_WR_SEC               BIT(27)
#define BIT_REG_FW0_IPA_MTX_QOS_1_WR_SEC                     BIT(26)
#define BIT_REG_FW0_IPA_MTX_QOS_0_WR_SEC                     BIT(25)
#define BIT_REG_FW0_IPA_ASYNC_BRG_G3_LPC_WR_SEC              BIT(24)
#define BIT_REG_FW0_IPA_ASYNC_BRG_G2_LPC_WR_SEC              BIT(23)
#define BIT_REG_FW0_IPA_S8_LPC_WR_SEC                        BIT(22)
#define BIT_REG_FW0_IPA_S7_LPC_WR_SEC                        BIT(21)
#define BIT_REG_FW0_IPA_S6_LPC_WR_SEC                        BIT(20)
#define BIT_REG_FW0_IPA_S5_LPC_WR_SEC                        BIT(19)
#define BIT_REG_FW0_IPA_S4_LPC_WR_SEC                        BIT(18)
#define BIT_REG_FW0_IPA_S3_LPC_WR_SEC                        BIT(17)
#define BIT_REG_FW0_IPA_S2_LPC_WR_SEC                        BIT(16)
#define BIT_REG_FW0_IPA_S1_LPC_WR_SEC                        BIT(15)
#define BIT_REG_FW0_IPA_S0_LPC_WR_SEC                        BIT(14)
#define BIT_REG_FW0_IPA_MAIN_MTX_LPC_WR_SEC                  BIT(13)
#define BIT_REG_FW0_IPA_M7_LPC_WR_SEC                        BIT(12)
#define BIT_REG_FW0_IPA_M6_LPC_WR_SEC                        BIT(11)
#define BIT_REG_FW0_IPA_M5_LPC_WR_SEC                        BIT(10)
#define BIT_REG_FW0_IPA_M4_LPC_WR_SEC                        BIT(9)
#define BIT_REG_FW0_IPA_M3_LPC_WR_SEC                        BIT(8)
#define BIT_REG_FW0_IPA_M2_LPC_WR_SEC                        BIT(7)
#define BIT_REG_FW0_IPA_M1_LPC_WR_SEC                        BIT(6)
#define BIT_REG_FW0_IPA_M0_LPC_WR_SEC                        BIT(5)
#define BIT_REG_FW0_IPA_USB_CTL0_WR_SEC                      BIT(4)
#define BIT_REG_FW0_IPA_PCIE2_CTL0_WR_SEC                    BIT(3)
#define BIT_REG_FW0_IPA_PCIE3_CTL0_WR_SEC                    BIT(2)
#define BIT_REG_FW0_IPA_IPA_EB_WR_SEC                        BIT(1)
#define BIT_REG_FW0_IPA_IPA_RST_WR_SEC                       BIT(0)

/* REG_REG_FW0_IPA_REG_WR_CTRL_1 */

#define BIT_REG_FW0_IPA_INT_TO_CM4_EN_REG_WR_SEC             BIT(23)
#define BIT_REG_FW0_IPA_INT_TO_AP_EN_REG_WR_SEC              BIT(22)
#define BIT_REG_FW0_IPA_INT_TO_CM4_STATUS_REG_WR_SEC         BIT(21)
#define BIT_REG_FW0_IPA_INT_TO_AP_STATUS_REG_WR_SEC          BIT(20)
#define BIT_REG_FW0_IPA_CM4_SPORT_REMAP_CTRL_REG_WR_SEC      BIT(19)
#define BIT_REG_FW0_IPA_CM4_DPORT_REMAP_CTRL_REG_WR_SEC      BIT(18)
#define BIT_REG_FW0_IPA_CM4_IPORT_REMAP_CTRL_REG_WR_SEC      BIT(17)
#define BIT_REG_FW0_IPA_CM4_DCACHE_CTRL_REG_WR_SEC           BIT(16)
#define BIT_REG_FW0_IPA_CM4_ICACHE_CTRL_REG_WR_SEC           BIT(15)
#define BIT_REG_FW0_IPA_CM4_WDG_RST_FLAG_WR_SEC              BIT(14)
#define BIT_REG_FW0_IPA_CM4_INT_STAT_WR_SEC                  BIT(13)
#define BIT_REG_FW0_IPA_CM4_MAIN_STATOUT_WR_SEC              BIT(12)
#define BIT_REG_FW0_IPA_CM4_CORE_AUXFAULT_CFG_WR_SEC         BIT(11)
#define BIT_REG_FW0_IPA_CM4_CORE_SYSTICK_CFG_WR_SEC          BIT(10)
#define BIT_REG_FW0_IPA_CM4_CORE_CFG1_WR_SEC                 BIT(9)
#define BIT_REG_FW0_IPA_CM4_SYS_SOFT_RST_WR_SEC              BIT(8)
#define BIT_REG_FW0_IPA_PCIE3_DEBUG_WR_SEC                   BIT(7)
#define BIT_REG_FW0_IPA_PCIE2_DEBUG_WR_SEC                   BIT(6)
#define BIT_REG_FW0_IPA_USB3_DEBUG_2_WR_SEC                  BIT(5)
#define BIT_REG_FW0_IPA_USB3_DEBUG_1_WR_SEC                  BIT(4)
#define BIT_REG_FW0_IPA_USB3_DEBUG_0_WR_SEC                  BIT(3)
#define BIT_REG_FW0_IPA_GEN3_BRIDGE_DEBUG_SIGNAL_W_WR_SEC    BIT(2)
#define BIT_REG_FW0_IPA_GEN2_BRIDGE_DEBUG_SIGNAL_W_WR_SEC    BIT(1)
#define BIT_REG_FW0_IPA_AP2IPA_BRIDGE_DEBUG_SIGNAL_R_WR_SEC  BIT(0)

/* REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY0 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY0(x)              (((x) & 0x3FFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY1 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY1(x)              (((x) & 0x3FFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY2 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY2(x)              (((x) & 0x3FFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY3 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY3(x)              (((x) & 0x3FFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY4 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY4(x)              (((x) & 0x3FFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY5 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY5(x)              (((x) & 0x3FFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY6 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY6(x)              (((x) & 0x3FFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY7 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY7(x)              (((x) & 0x3FFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY8 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY8(x)              (((x) & 0x3FFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY9 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY9(x)              (((x) & 0x3FFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY10 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY10(x)             (((x) & 0x3FFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY11 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY11(x)             (((x) & 0x3FFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY12 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY12(x)             (((x) & 0x3FFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY13 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY13(x)             (((x) & 0x3FFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY14 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY14(x)             (((x) & 0x3FFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY15 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ADDR_ARRAY15(x)             (((x) & 0x3FFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ARRAY0 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ARRAY0(x)                   (((x) & 0xFFFFFFFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ARRAY1 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ARRAY1(x)                   (((x) & 0xFFFFFFFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ARRAY2 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ARRAY2(x)                   (((x) & 0xFFFFFFFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ARRAY3 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ARRAY3(x)                   (((x) & 0xFFFFFFFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ARRAY4 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ARRAY4(x)                   (((x) & 0xFFFFFFFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ARRAY5 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ARRAY5(x)                   (((x) & 0xFFFFFFFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ARRAY6 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ARRAY6(x)                   (((x) & 0xFFFFFFFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ARRAY7 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ARRAY7(x)                   (((x) & 0xFFFFFFFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ARRAY8 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ARRAY8(x)                   (((x) & 0xFFFFFFFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ARRAY9 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ARRAY9(x)                   (((x) & 0xFFFFFFFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ARRAY10 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ARRAY10(x)                  (((x) & 0xFFFFFFFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ARRAY11 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ARRAY11(x)                  (((x) & 0xFFFFFFFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ARRAY12 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ARRAY12(x)                  (((x) & 0xFFFFFFFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ARRAY13 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ARRAY13(x)                  (((x) & 0xFFFFFFFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ARRAY14 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ARRAY14(x)                  (((x) & 0xFFFFFFFF))

/* REG_REG_FW0_IPA_BIT_CTRL_ARRAY15 */

#define BIT_REG_FW0_IPA_BIT_CTRL_ARRAY15(x)                  (((x) & 0xFFFFFFFF))


#endif /* REG_FW0_IPA_H */


