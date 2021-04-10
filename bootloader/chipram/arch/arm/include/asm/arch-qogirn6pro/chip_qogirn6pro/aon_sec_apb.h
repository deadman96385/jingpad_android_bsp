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

#ifndef AON_SEC_APB_H
#define AON_SEC_APB_H

#define CTL_BASE_AON_SEC_APB 0x32880000

#define REG_AON_SEC_APB_CHIP_KPRTL_0                ( CTL_BASE_AON_SEC_APB + 0x0000 )
#define REG_AON_SEC_APB_CHIP_KPRTL_1                ( CTL_BASE_AON_SEC_APB + 0x0004 )
#define REG_AON_SEC_APB_CHIP_KPRTL_2                ( CTL_BASE_AON_SEC_APB + 0x0008 )
#define REG_AON_SEC_APB_CHIP_KPRTL_3                ( CTL_BASE_AON_SEC_APB + 0x000C )
#define REG_AON_SEC_APB_SEC_EB                      ( CTL_BASE_AON_SEC_APB + 0x0010 )
#define REG_AON_SEC_APB_SEC_SOFT_RST                ( CTL_BASE_AON_SEC_APB + 0x0014 )
#define REG_AON_SEC_APB_FUNC_DMA_EN                 ( CTL_BASE_AON_SEC_APB + 0x0018 )
#define REG_AON_SEC_APB_AON_SEC_EB                  ( CTL_BASE_AON_SEC_APB + 0x001C )
#define REG_AON_SEC_APB_SECURE_EFUSE_BOUNDRY        ( CTL_BASE_AON_SEC_APB + 0x0020 )
#define REG_AON_SEC_APB_APCPU_APB_EB                ( CTL_BASE_AON_SEC_APB + 0x0024 )
#define REG_AON_SEC_APB_APCPU_SOFT_RST              ( CTL_BASE_AON_SEC_APB + 0x0028 )
#define REG_AON_SEC_APB_APCPU_CORE0_3_CLK_CFG       ( CTL_BASE_AON_SEC_APB + 0x002C )
#define REG_AON_SEC_APB_APCPU_CORE4_7_CLK_CFG       ( CTL_BASE_AON_SEC_APB + 0x0030 )
#define REG_AON_SEC_APB_APCPU_BUS_CLK_CFG           ( CTL_BASE_AON_SEC_APB + 0x0038 )
#define REG_AON_SEC_APB_APCPU_TOP_MISC_CLK_CFG      ( CTL_BASE_AON_SEC_APB + 0x003C )
#define REG_AON_SEC_APB_RVBARADDR0                  ( CTL_BASE_AON_SEC_APB + 0x0040 )
#define REG_AON_SEC_APB_RVBARADDR1                  ( CTL_BASE_AON_SEC_APB + 0x0044 )
#define REG_AON_SEC_APB_RVBARADDR2                  ( CTL_BASE_AON_SEC_APB + 0x0048 )
#define REG_AON_SEC_APB_RVBARADDR3                  ( CTL_BASE_AON_SEC_APB + 0x004C )
#define REG_AON_SEC_APB_RVBARADDR4                  ( CTL_BASE_AON_SEC_APB + 0x0050 )
#define REG_AON_SEC_APB_RVBARADDR5                  ( CTL_BASE_AON_SEC_APB + 0x0054 )
#define REG_AON_SEC_APB_RVBARADDR6                  ( CTL_BASE_AON_SEC_APB + 0x0058 )
#define REG_AON_SEC_APB_RVBARADDR7                  ( CTL_BASE_AON_SEC_APB + 0x005C )
#define REG_AON_SEC_APB_APCPU_CFG_CTRL              ( CTL_BASE_AON_SEC_APB + 0x0060 )
#define REG_AON_SEC_APB_AON_SEC_APB_RSV_0           ( CTL_BASE_AON_SEC_APB + 0x0070 )
#define REG_AON_SEC_APB_AON_SEC_APB_RSV_1           ( CTL_BASE_AON_SEC_APB + 0x0074 )

/* REG_AON_SEC_APB_CHIP_KPRTL_0 */

#define BIT_AON_SEC_APB_KPRTL_0(x)                 (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_CHIP_KPRTL_1 */

#define BIT_AON_SEC_APB_KPRTL_1(x)                 (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_CHIP_KPRTL_2 */

#define BIT_AON_SEC_APB_KPRTL_2(x)                 (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_CHIP_KPRTL_3 */

#define BIT_AON_SEC_APB_KPRTL_3(x)                 (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_SEC_EB */

#define BIT_AON_SEC_APB_SEC_32K_DET_EB             BIT(11)
#define BIT_AON_SEC_APB_SEC_EIC_RTCDV5_EB          BIT(10)
#define BIT_AON_SEC_APB_SEC_EIC_RTC_EB             BIT(9)
#define BIT_AON_SEC_APB_SEC_EIC_EB                 BIT(8)
#define BIT_AON_SEC_APB_SEC_RTC_CLK_GATE_EB        BIT(7)
#define BIT_AON_SEC_APB_SEC_GPIO_EB                BIT(6)
#define BIT_AON_SEC_APB_SEC_WDG_EB                 BIT(5)
#define BIT_AON_SEC_APB_SEC_WDG_RTC_EB             BIT(4)
#define BIT_AON_SEC_APB_SEC_RTC_EB                 BIT(3)
#define BIT_AON_SEC_APB_SEC_TMR0_EB                BIT(2)
#define BIT_AON_SEC_APB_SEC_TMR0_RTC_EB            BIT(1)
#define BIT_AON_SEC_APB_SEC_TZPC_EB                BIT(0)

/* REG_AON_SEC_APB_SEC_SOFT_RST */

#define BIT_AON_SEC_APB_SEC_32K_DET_SOFT_RST       BIT(6)
#define BIT_AON_SEC_APB_SEC_EIC_SOFT_RST           BIT(5)
#define BIT_AON_SEC_APB_SEC_GPIO_SOFT_RST          BIT(4)
#define BIT_AON_SEC_APB_SEC_WDG_SOFT_RST           BIT(3)
#define BIT_AON_SEC_APB_SEC_RTC_SOFT_RST           BIT(2)
#define BIT_AON_SEC_APB_SEC_TMR0_SOFT_RST          BIT(1)
#define BIT_AON_SEC_APB_SEC_TZPC_SOFT_RST          BIT(0)

/* REG_AON_SEC_APB_FUNC_DMA_EN */

#define BIT_AON_SEC_APB_FUNC_DMA_EN                BIT(0)

/* REG_AON_SEC_APB_AON_SEC_EB */

#define BIT_AON_SEC_APB_ETC_SEC_EB                 BIT(2)
#define BIT_AON_SEC_APB_I2C_SEC_EB                 BIT(1)
#define BIT_AON_SEC_APB_EFUSE_SEC_EB               BIT(0)

/* REG_AON_SEC_APB_SECURE_EFUSE_BOUNDRY */

#define BIT_AON_SEC_APB_SEC_EFUSE_BOUNDRY(x)       (((x) & 0xFF))

/* REG_AON_SEC_APB_APCPU_APB_EB */

#define BIT_AON_SEC_APB_APCPU_CSSYS_EB             BIT(0)

/* REG_AON_SEC_APB_APCPU_SOFT_RST */

#define BIT_AON_SEC_APB_APCPU_CSSYS_APB_SOFT_RST   BIT(14)
#define BIT_AON_SEC_APB_APCPU_CSSYS_SOFT_RST       BIT(13)
#define BIT_AON_SEC_APB_APCPU_SCU_SOFT_RST         BIT(12)
#define BIT_AON_SEC_APB_APCPU_DEBUG_APB_SOFT_RST   BIT(11)
#define BIT_AON_SEC_APB_APCPU_PERIPH_SOFT_RST      BIT(10)
#define BIT_AON_SEC_APB_APCPU_GIC_SOFT_RST         BIT(9)
#define BIT_AON_SEC_APB_APCPU_ATB_SOFT_RST         BIT(8)
#define BIT_AON_SEC_APB_APCPU_CORE_SOFT_RST(x)     (((x) & 0xFF))

/* REG_AON_SEC_APB_APCPU_CORE0_3_CLK_CFG */

#define BIT_AON_SEC_APB_CGM_CORE3_DIV(x)           (((x) & 0x7) << 28)
#define BIT_AON_SEC_APB_CGM_CORE3_SEL(x)           (((x) & 0x7) << 24)
#define BIT_AON_SEC_APB_CGM_CORE2_DIV(x)           (((x) & 0x7) << 20)
#define BIT_AON_SEC_APB_CGM_CORE2_SEL(x)           (((x) & 0x7) << 16)
#define BIT_AON_SEC_APB_CGM_CORE1_DIV(x)           (((x) & 0x7) << 12)
#define BIT_AON_SEC_APB_CGM_CORE1_SEL(x)           (((x) & 0x7) << 8)
#define BIT_AON_SEC_APB_CGM_CORE0_DIV(x)           (((x) & 0x7) << 4)
#define BIT_AON_SEC_APB_CGM_CORE0_SEL(x)           (((x) & 0x7))

/* REG_AON_SEC_APB_APCPU_CORE4_7_CLK_CFG */

#define BIT_AON_SEC_APB_CGM_CORE7_DIV(x)           (((x) & 0x7) << 28)
#define BIT_AON_SEC_APB_CGM_CORE7_SEL(x)           (((x) & 0x7) << 24)
#define BIT_AON_SEC_APB_CGM_CORE6_DIV(x)           (((x) & 0x7) << 20)
#define BIT_AON_SEC_APB_CGM_CORE6_SEL(x)           (((x) & 0x7) << 16)
#define BIT_AON_SEC_APB_CGM_CORE5_DIV(x)           (((x) & 0x7) << 12)
#define BIT_AON_SEC_APB_CGM_CORE5_SEL(x)           (((x) & 0x7) << 8)
#define BIT_AON_SEC_APB_CGM_CORE4_DIV(x)           (((x) & 0x7) << 4)
#define BIT_AON_SEC_APB_CGM_CORE4_SEL(x)           (((x) & 0x7))

/* REG_AON_SEC_APB_APCPU_BUS_CLK_CFG */

#define BIT_AON_SEC_APB_CGM_AXI_ACP_DIV(x)         (((x) & 0x7) << 28)
#define BIT_AON_SEC_APB_CGM_AXI_PERIPH_DIV(x)      (((x) & 0x7) << 20)
#define BIT_AON_SEC_APB_CGM_ACE_DIV(x)             (((x) & 0x7) << 12)
#define BIT_AON_SEC_APB_CGM_SCU_DIV(x)             (((x) & 0x7) << 4)
#define BIT_AON_SEC_APB_CGM_SCU_SEL(x)             (((x) & 0x7))

/* REG_AON_SEC_APB_APCPU_TOP_MISC_CLK_CFG */

#define BIT_AON_SEC_APB_CGM_PERIPH_DIV(x)          (((x) & 0x7) << 28)
#define BIT_AON_SEC_APB_CGM_PERIPH_SEL(x)          (((x) & 0x3) << 24)
#define BIT_AON_SEC_APB_CGM_GIC_DIV(x)             (((x) & 0x7) << 20)
#define BIT_AON_SEC_APB_CGM_GIC_SEL(x)             (((x) & 0x3) << 16)
#define BIT_AON_SEC_APB_CGM_DEBUG_APB_DIV(x)       (((x) & 0x3) << 12)
#define BIT_AON_SEC_APB_CGM_ATB_DIV(x)             (((x) & 0x7) << 4)
#define BIT_AON_SEC_APB_CGM_ATB_SEL(x)             (((x) & 0x3))

/* REG_AON_SEC_APB_RVBARADDR0 */

#define BIT_AON_SEC_APB_RVBARADDR0(x)              (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_RVBARADDR1 */

#define BIT_AON_SEC_APB_RVBARADDR1(x)              (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_RVBARADDR2 */

#define BIT_AON_SEC_APB_RVBARADDR2(x)              (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_RVBARADDR3 */

#define BIT_AON_SEC_APB_RVBARADDR3(x)              (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_RVBARADDR4 */

#define BIT_AON_SEC_APB_RVBARADDR4(x)              (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_RVBARADDR5 */

#define BIT_AON_SEC_APB_RVBARADDR5(x)              (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_RVBARADDR6 */

#define BIT_AON_SEC_APB_RVBARADDR6(x)              (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_RVBARADDR7 */

#define BIT_AON_SEC_APB_RVBARADDR7(x)              (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_APCPU_CFG_CTRL */

#define BIT_AON_SEC_APB_APCPU_PWAKEUPDBG_FORCE_ON  BIT(4)
#define BIT_AON_SEC_APB_APCPU_GICP_ALLOW_NS        BIT(3)
#define BIT_AON_SEC_APB_APCPU_GICT_ALLOW_NS        BIT(2)
#define BIT_AON_SEC_APB_APCPU_GICCDISABLE          BIT(1)
#define BIT_AON_SEC_APB_APCPU_CRYPTODISABLE        BIT(0)

/* REG_AON_SEC_APB_AON_SEC_APB_RSV_0 */

#define BIT_AON_SEC_APB_AON_SEC_APB_RSV_0(x)       (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_AON_SEC_APB_RSV_1 */

#define BIT_AON_SEC_APB_AON_SEC_APB_RSV_1(x)       (((x) & 0xFFFFFFFF))

#endif