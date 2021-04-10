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


#ifndef AON_SEC_APB_H
#define AON_SEC_APB_H

#define CTL_BASE_AON_SEC_APB 0x40460000


#define REG_AON_SEC_APB_SEC_EB                  ( CTL_BASE_AON_SEC_APB + 0x0000 )
#define REG_AON_SEC_APB_SEC_SOFT_RST            ( CTL_BASE_AON_SEC_APB + 0x0004 )
#define REG_AON_SEC_APB_FUNC_DMA_EN             ( CTL_BASE_AON_SEC_APB + 0x0008 )
#define REG_AON_SEC_APB_CA53_CFG_CTRL           ( CTL_BASE_AON_SEC_APB + 0x000C )
#define REG_AON_SEC_APB_CA53_SOFT_RST           ( CTL_BASE_AON_SEC_APB + 0x0010 )
#define REG_AON_SEC_APB_CCI_CFG0                ( CTL_BASE_AON_SEC_APB + 0x001C )
#define REG_AON_SEC_APB_CCI_CFG1                ( CTL_BASE_AON_SEC_APB + 0x0020 )
#define REG_AON_SEC_APB_RVBARADDR0_LIT          ( CTL_BASE_AON_SEC_APB + 0x0024 )
#define REG_AON_SEC_APB_RVBARADDR1_LIT          ( CTL_BASE_AON_SEC_APB + 0x0028 )
#define REG_AON_SEC_APB_RVBARADDR2_LIT          ( CTL_BASE_AON_SEC_APB + 0x002C )
#define REG_AON_SEC_APB_RVBARADDR3_LIT          ( CTL_BASE_AON_SEC_APB + 0x0030 )
#define REG_AON_SEC_APB_RVBARADDR0_BIG          ( CTL_BASE_AON_SEC_APB + 0x0034 )
#define REG_AON_SEC_APB_RVBARADDR1_BIG          ( CTL_BASE_AON_SEC_APB + 0x0038 )
#define REG_AON_SEC_APB_RVBARADDR2_BIG          ( CTL_BASE_AON_SEC_APB + 0x003C )
#define REG_AON_SEC_APB_RVBARADDR3_BIG          ( CTL_BASE_AON_SEC_APB + 0x0040 )
#define REG_AON_SEC_APB_SEC_EFUSE_BOUNDARY      ( CTL_BASE_AON_SEC_APB + 0x0050 )
#define REG_AON_SEC_APB_GIC_ACC_EN              ( CTL_BASE_AON_SEC_APB + 0x0054 )
#define REG_AON_SEC_APB_DBG_RECOVERY_EN         ( CTL_BASE_AON_SEC_APB + 0x0058 )

/* REG_AON_SEC_APB_SEC_EB */

#define BIT_AON_SEC_APB_DMA_SEC_EB                 BIT(12)
#define BIT_AON_SEC_APB_EFUSE_SEC_EB               BIT(11)
#define BIT_AON_SEC_APB_SEC_EIC_RTCDV5_EB          BIT(10)
#define BIT_AON_SEC_APB_SEC_EIC_RTC_EB             BIT(9)
#define BIT_AON_SEC_APB_SEC_EIC_EB                 BIT(8)
#define BIT_AON_SEC_APB_SEC_GPIO_EB                BIT(7)
#define BIT_AON_SEC_APB_SEC_RTC_CLK_GATE_EB        BIT(6)
#define BIT_AON_SEC_APB_SEC_WDG_EB                 BIT(5)
#define BIT_AON_SEC_APB_SEC_WDG_RTC_EB             BIT(4)
#define BIT_AON_SEC_APB_SEC_RTC_EB                 BIT(3)
#define BIT_AON_SEC_APB_SEC_TMR_EB                 BIT(2)
#define BIT_AON_SEC_APB_SEC_TMR_RTC_EB             BIT(1)
#define BIT_AON_SEC_APB_SEC_TZPC_EB                BIT(0)

/* REG_AON_SEC_APB_SEC_SOFT_RST */

#define BIT_AON_SEC_APB_SEC_EIC_SOFT_RST           BIT(5)
#define BIT_AON_SEC_APB_SEC_GPIO_RST               BIT(4)
#define BIT_AON_SEC_APB_SEC_WDG_SOFT_RST           BIT(3)
#define BIT_AON_SEC_APB_SEC_RTC_SOFT_RST           BIT(2)
#define BIT_AON_SEC_APB_SEC_TMR_SOFT_RST           BIT(1)
#define BIT_AON_SEC_APB_SEC_TZPC_SOFT_RST          BIT(0)

/* REG_AON_SEC_APB_FUNC_DMA_EN */

#define BIT_AON_SEC_APB_FUNC_DMA_EN                BIT(0)

/* REG_AON_SEC_APB_CA53_CFG_CTRL */

#define BIT_AON_SEC_APB_CA53_GIC_CFGSDISABLE       BIT(8)
#define BIT_AON_SEC_APB_CA53_BIG_CP15SDISABLE(x)   (((x) & 0x3) << 4)
#define BIT_AON_SEC_APB_CA53_LIT_CP15SDISABLE(x)   (((x) & 0x3))

/* REG_AON_SEC_APB_CA53_SOFT_RST */

#define BIT_AON_SEC_APB_CA53_BIG_DBG_SOFT_RST      BIT(25)
#define BIT_AON_SEC_APB_CA53_BIG_L2_SOFT_RST       BIT(24)
#define BIT_AON_SEC_APB_CA53_BIG_ATB_SOFT_RST(x)   (((x) & 0x3) << 20)
#define BIT_AON_SEC_APB_CA53_BIG_CORE_SOFT_RST(x)  (((x) & 0x3) << 16)
#define BIT_AON_SEC_APB_CA53_LIT_DBG_SOFT_RST      BIT(9)
#define BIT_AON_SEC_APB_CA53_LIT_L2_SOFT_RST       BIT(8)
#define BIT_AON_SEC_APB_CA53_LIT_ATB_SOFT_RST(x)   (((x) & 0x3) << 4)
#define BIT_AON_SEC_APB_CA53_LIT_CORE_SOFT_RST(x)  (((x) & 0x3))

/* REG_AON_SEC_APB_CCI_CFG0 */

#define BIT_AON_SEC_APB_CCI_PERIPHBASE_H25(x)      (((x) & 0x1FFFFFF))

/* REG_AON_SEC_APB_CCI_CFG1 */

#define BIT_AON_SEC_APB_CCI_AWQOS_BIG(x)           (((x) & 0xF) << 28)
#define BIT_AON_SEC_APB_CCI_ARQOS_BIG(x)           (((x) & 0xF) << 24)
#define BIT_AON_SEC_APB_CCI_AWQOS_LIT(x)           (((x) & 0xF) << 20)
#define BIT_AON_SEC_APB_CCI_ARQOS_LIT(x)           (((x) & 0xF) << 16)
#define BIT_AON_SEC_APB_CCI_QOSOVERRIDE(x)         (((x) & 0x1F) << 3)
#define BIT_AON_SEC_APB_CCI_BUFFERABLEOVERRIDE(x)  (((x) & 0x7))

/* REG_AON_SEC_APB_RVBARADDR0_LIT */

#define BIT_AON_SEC_APB_RVBARADDR0_LIT(x)          (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_RVBARADDR1_LIT */

#define BIT_AON_SEC_APB_RVBARADDR1_LIT(x)          (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_RVBARADDR2_LIT */

#define BIT_AON_SEC_APB_RVBARADDR2_LIT(x)          (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_RVBARADDR3_LIT */

#define BIT_AON_SEC_APB_RVBARADDR3_LIT(x)          (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_RVBARADDR0_BIG */

#define BIT_AON_SEC_APB_RVBARADDR0_BIG(x)          (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_RVBARADDR1_BIG */

#define BIT_AON_SEC_APB_RVBARADDR1_BIG(x)          (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_RVBARADDR2_BIG */

#define BIT_AON_SEC_APB_RVBARADDR2_BIG(x)          (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_RVBARADDR3_BIG */

#define BIT_AON_SEC_APB_RVBARADDR3_BIG(x)          (((x) & 0xFFFFFFFF))

/* REG_AON_SEC_APB_SEC_EFUSE_BOUNDARY */

#define BIT_AON_SEC_APB_SEC_EFUSE_BOUNDARY(x)      (((x) & 0xFF))

/* REG_AON_SEC_APB_GIC_ACC_EN */

#define BIT_AON_SEC_APB_GICP_ALLOW_NS              BIT(1)
#define BIT_AON_SEC_APB_GICT_ALLOW_NS              BIT(0)

/* REG_AON_SEC_APB_DBG_RECOVERY_EN */

#define BIT_AON_SEC_APB_DBGRCV_TRIG_OUT_EN         BIT(2)
#define BIT_AON_SEC_APB_AUTO_SAVE_TRIG_OUT_EN      BIT(1)
#define BIT_AON_SEC_APB_AUTO_SAVE_GATED_OUT_EN     BIT(0)


#endif /* AON_SEC_APB_H */

