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

#ifndef DBG_APB_H
#define DBG_APB_H

#define CTL_BASE_DBG_APB 0x3C00A000

#define REG_DBG_APB_SUB_SYS_DBG_BUSY_TIMER_FOR_BUSMON  ( CTL_BASE_DBG_APB + 0x0000 )
#define REG_DBG_APB_SUB_SYS_DBG_MISC_SIGNAL            ( CTL_BASE_DBG_APB + 0x0004 )
#define REG_DBG_APB_SUB_SYS_DBG_PWR_CTRL               ( CTL_BASE_DBG_APB + 0x0008 )
#define REG_DBG_APB_SUB_SYS_DBG_DBG_CTRL               ( CTL_BASE_DBG_APB + 0x000C )
#define REG_DBG_APB_SUB_SYS_DBG_STM_SOFT_RST           ( CTL_BASE_DBG_APB + 0x0010 )
#define REG_DBG_APB_SUB_SYS_DBG_RCO_CLK_CTRL           ( CTL_BASE_DBG_APB + 0x0014 )
#define REG_DBG_APB_SUB_SYS_DBG_SEL_CFG0               ( CTL_BASE_DBG_APB + 0x0018 )
#define REG_DBG_APB_SUB_SYS_DBG_SEL_CFG1               ( CTL_BASE_DBG_APB + 0x001C )
#define REG_DBG_APB_SUB_SYS_DBG_SEL_CFG2               ( CTL_BASE_DBG_APB + 0x0020 )
#define REG_DBG_APB_SUB_SYS_DBG_SEL_CFG3               ( CTL_BASE_DBG_APB + 0x0024 )
#define REG_DBG_APB_SUB_SYS_DBG_SEL_CFG4               ( CTL_BASE_DBG_APB + 0x0028 )
#define REG_DBG_APB_SUB_SYS_DBG_PAD_SEL_CFG0           ( CTL_BASE_DBG_APB + 0x002C )
#define REG_DBG_APB_SUB_SYS_DBG_PAD_SEL_CFG1           ( CTL_BASE_DBG_APB + 0x0030 )
#define REG_DBG_APB_SUB_SYS_DBG_PAD_SEL_CFG2           ( CTL_BASE_DBG_APB + 0x0034 )
#define REG_DBG_APB_SUB_SYS_DBG_PAD_SEL_CFG3           ( CTL_BASE_DBG_APB + 0x0038 )
#define REG_DBG_APB_SUB_SYS_DBG_PAD_SEL_CFG4           ( CTL_BASE_DBG_APB + 0x003C )
#define REG_DBG_APB_SUB_SYS_DBG_PAD_SEL_CFG5           ( CTL_BASE_DBG_APB + 0x0040 )
#define REG_DBG_APB_SUB_SYS_DBG_PAD_SEL_CFG6           ( CTL_BASE_DBG_APB + 0x0044 )
#define REG_DBG_APB_PAD_DBG_BUS_DATA_A                 ( CTL_BASE_DBG_APB + 0x0048 )
#define REG_DBG_APB_PAD_DBG_BUS_DATA_B                 ( CTL_BASE_DBG_APB + 0x004C )
#define REG_DBG_APB_PAD_DBG_BUS_DATA_OUT               ( CTL_BASE_DBG_APB + 0x0050 )
#define REG_DBG_APB_ETR_AXI_MON_INT_EN                 ( CTL_BASE_DBG_APB + 0x0054 )
#define REG_DBG_APB_ETR_AXI_MON_INT_CLR                ( CTL_BASE_DBG_APB + 0x0058 )
#define REG_DBG_APB_ETR_AXI_MON_INT_RAW                ( CTL_BASE_DBG_APB + 0x005C )
#define REG_DBG_APB_ETR_AXI_MON_INT_STAT               ( CTL_BASE_DBG_APB + 0x0060 )
#define REG_DBG_APB_ETR_AXI_MON_AWADDR0                ( CTL_BASE_DBG_APB + 0x0064 )
#define REG_DBG_APB_ETR_AXI_MON_AWADDR1                ( CTL_BASE_DBG_APB + 0x0068 )
#define REG_DBG_APB_ETR_AXI_MON_AWADDR2                ( CTL_BASE_DBG_APB + 0x006C )
#define REG_DBG_APB_ETR_AXI_MON_AWADDR3                ( CTL_BASE_DBG_APB + 0x0070 )

/* REG_DBG_APB_SUB_SYS_DBG_BUSY_TIMER_FOR_BUSMON */

#define BIT_DBG_APB_BUS_BUSY_TIMER_EN              BIT(8)
#define BIT_DBG_APB_BUS_BUSY_TIMER_DIVIDER(x)      (((x) & 0xFF))

/* REG_DBG_APB_SUB_SYS_DBG_MISC_SIGNAL */

#define BIT_DBG_APB_APCPU_CSSYS_EN                 BIT(3)
#define BIT_DBG_APB_APCPU_APB_TRANS_CSYSREQ        BIT(2)
#define BIT_DBG_APB_CPWRUPREQ_CDBGPWRUP            BIT(1)
#define BIT_DBG_APB_DBGCONNECTED                   BIT(0)

/* REG_DBG_APB_SUB_SYS_DBG_PWR_CTRL */

#define BIT_DBG_APB_CSYSPWRUPREQ_RCO_EN            BIT(3)
#define BIT_DBG_APB_CSYSPWRUPREQ_CR5_EN            BIT(2)
#define BIT_DBG_APB_CSYSPWRUPREQ_AON_CM4_EN        BIT(1)
#define BIT_DBG_APB_CSYSPWRUPREQ_APCPU_EN          BIT(0)

/* REG_DBG_APB_SUB_SYS_DBG_DBG_CTRL */

#define BIT_DBG_APB_TPIU2SERDES_CGM_EN             BIT(17)
#define BIT_DBG_APB_CSSYS_EN_REG                   BIT(16)
#define BIT_DBG_APB_APCPU_DAP_EN_REG               BIT(15)
#define BIT_DBG_APB_CROSS_TRIGGER_EN               BIT(14)
#define BIT_DBG_APB_APCPU_MTX_SOFT_RST             BIT(13)
#define BIT_DBG_APB_APCPU_AB_SOFT_RST              BIT(12)
#define BIT_DBG_APB_APCPU_APB_TRANS_BLKR_BYPASS    BIT(11)
#define BIT_DBG_APB_APCPU_CORINTH_DEBUG_EN_FOR_LP  BIT(10)
#define BIT_DBG_APB_AUTO_REG_SAVE_SEL              BIT(9)
#define BIT_DBG_APB_AUTO_REG_SAVE_SOFT_TRIG        BIT(8)
#define BIT_DBG_APB_AUTO_REG_SAVE_EN               BIT(7)
#define BIT_DBG_APB_CSSYS_SOFT_RST_EN              BIT(6)
#define BIT_DBG_APB_AON_MTX_SOFT_RST_EN            BIT(5)
#define BIT_DBG_APB_DAP_SOFT_RST_EN                BIT(4)
#define BIT_DBG_APB_APCPU_CSSYS_EN_REG             BIT(3)
#define BIT_DBG_APB_APCPU_DBG_CONNECTED_SW         BIT(2)
#define BIT_DBG_APB_APCPU_DBG_CONNECTED_CTRL(x)    (((x) & 0x3))

/* REG_DBG_APB_SUB_SYS_DBG_STM_SOFT_RST */

#define BIT_DBG_APB_STM_SOFT_RESET                 BIT(0)

/* REG_DBG_APB_SUB_SYS_DBG_RCO_CLK_CTRL */

#define BIT_DBG_APB_AON_APB_CLK_RCO_SEL(x)         (((x) & 0x7) << 9)
#define BIT_DBG_APB_CSSYS_CLK_RCO_SEL(x)           (((x) & 0x7) << 6)
#define BIT_DBG_APB_DAP_CLK_RCO_SEL(x)             (((x) & 0x7) << 3)
#define BIT_DBG_APB_AON_APB_CLK_RCO_CTRL_EN        BIT(2)
#define BIT_DBG_APB_CSSYS_CLK_RCO_CTRL_EN          BIT(1)
#define BIT_DBG_APB_DAP_CLK_RCO_CTRL_EN            BIT(0)

/* REG_DBG_APB_SUB_SYS_DBG_SEL_CFG0 */

#define BIT_DBG_APB_REG_DBG_SYS_SEL_B(x)           (((x) & 0xFF) << 8)
#define BIT_DBG_APB_REG_DBG_SYS_SEL_A(x)           (((x) & 0xFF))

/* REG_DBG_APB_SUB_SYS_DBG_SEL_CFG1 */

#define BIT_DBG_APB_REG_DBG_BUS_SEL_GPU(x)         (((x) & 0xFF) << 24)
#define BIT_DBG_APB_REG_DBG_BUS_SEL_MM(x)          (((x) & 0xFF) << 16)
#define BIT_DBG_APB_REG_DBG_BUS_SEL_AP(x)          (((x) & 0xFF) << 8)
#define BIT_DBG_APB_REG_DBG_BUS_SEL_APCPU(x)       (((x) & 0xFF))

/* REG_DBG_APB_SUB_SYS_DBG_SEL_CFG2 */

#define BIT_DBG_APB_REG_DBG_BUS_SEL_AON(x)         (((x) & 0xFF) << 16)
#define BIT_DBG_APB_REG_DBG_BUS_SEL_AON_LP(x)      (((x) & 0xFF) << 8)
#define BIT_DBG_APB_REG_DBG_BUS_SEL_PUB(x)         (((x) & 0xFF))

/* REG_DBG_APB_SUB_SYS_DBG_SEL_CFG3 */

#define BIT_DBG_APB_REG_DBG_BUS_SEL_MDAR(x)        (((x) & 0xFF) << 24)
#define BIT_DBG_APB_REG_DBG_BUS_SEL_WTLCP(x)       (((x) & 0xFF) << 16)
#define BIT_DBG_APB_REG_DBG_BUS_SEL_PUBCP(x)       (((x) & 0xFF) << 8)
#define BIT_DBG_APB_REG_DBG_BUS_SEL_AUDCP(x)       (((x) & 0xFF))

/* REG_DBG_APB_SUB_SYS_DBG_SEL_CFG4 */

#define BIT_DBG_APB_REG_DBG_MOD_SEL_LP(x)          (((x) & 0xFF) << 24)
#define BIT_DBG_APB_REG_DBG_MOD_SEL_APCPU(x)       (((x) & 0xFF) << 16)
#define BIT_DBG_APB_REG_DBG_MOD_SEL_WTLCP(x)       (((x) & 0xFF) << 8)
#define BIT_DBG_APB_REG_DBG_MOD_SEL_PUBCP(x)       (((x) & 0xFF))

/* REG_DBG_APB_SUB_SYS_DBG_PAD_SEL_CFG0 */

#define BIT_DBG_APB_DBG_BUS4_SEL(x)                (((x) & 0x3F) << 24)
#define BIT_DBG_APB_DBG_BUS3_SEL(x)                (((x) & 0x3F) << 18)
#define BIT_DBG_APB_DBG_BUS2_SEL(x)                (((x) & 0x3F) << 12)
#define BIT_DBG_APB_DBG_BUS1_SEL(x)                (((x) & 0x3F) << 6)
#define BIT_DBG_APB_DBG_BUS0_SEL(x)                (((x) & 0x3F))

/* REG_DBG_APB_SUB_SYS_DBG_PAD_SEL_CFG1 */

#define BIT_DBG_APB_DBG_BUS9_SEL(x)                (((x) & 0x3F) << 24)
#define BIT_DBG_APB_DBG_BUS8_SEL(x)                (((x) & 0x3F) << 18)
#define BIT_DBG_APB_DBG_BUS7_SEL(x)                (((x) & 0x3F) << 12)
#define BIT_DBG_APB_DBG_BUS6_SEL(x)                (((x) & 0x3F) << 6)
#define BIT_DBG_APB_DBG_BUS5_SEL(x)                (((x) & 0x3F))

/* REG_DBG_APB_SUB_SYS_DBG_PAD_SEL_CFG2 */

#define BIT_DBG_APB_DBG_BUS14_SEL(x)               (((x) & 0x3F) << 24)
#define BIT_DBG_APB_DBG_BUS13_SEL(x)               (((x) & 0x3F) << 18)
#define BIT_DBG_APB_DBG_BUS12_SEL(x)               (((x) & 0x3F) << 12)
#define BIT_DBG_APB_DBG_BUS11_SEL(x)               (((x) & 0x3F) << 6)
#define BIT_DBG_APB_DBG_BUS10_SEL(x)               (((x) & 0x3F))

/* REG_DBG_APB_SUB_SYS_DBG_PAD_SEL_CFG3 */

#define BIT_DBG_APB_DBG_BUS19_SEL(x)               (((x) & 0x3F) << 24)
#define BIT_DBG_APB_DBG_BUS18_SEL(x)               (((x) & 0x3F) << 18)
#define BIT_DBG_APB_DBG_BUS17_SEL(x)               (((x) & 0x3F) << 12)
#define BIT_DBG_APB_DBG_BUS16_SEL(x)               (((x) & 0x3F) << 6)
#define BIT_DBG_APB_DBG_BUS15_SEL(x)               (((x) & 0x3F))

/* REG_DBG_APB_SUB_SYS_DBG_PAD_SEL_CFG4 */

#define BIT_DBG_APB_DBG_BUS24_SEL(x)               (((x) & 0x3F) << 24)
#define BIT_DBG_APB_DBG_BUS23_SEL(x)               (((x) & 0x3F) << 18)
#define BIT_DBG_APB_DBG_BUS22_SEL(x)               (((x) & 0x3F) << 12)
#define BIT_DBG_APB_DBG_BUS21_SEL(x)               (((x) & 0x3F) << 6)
#define BIT_DBG_APB_DBG_BUS20_SEL(x)               (((x) & 0x3F))

/* REG_DBG_APB_SUB_SYS_DBG_PAD_SEL_CFG5 */

#define BIT_DBG_APB_DBG_BUS29_SEL(x)               (((x) & 0x3F) << 24)
#define BIT_DBG_APB_DBG_BUS28_SEL(x)               (((x) & 0x3F) << 18)
#define BIT_DBG_APB_DBG_BUS27_SEL(x)               (((x) & 0x3F) << 12)
#define BIT_DBG_APB_DBG_BUS26_SEL(x)               (((x) & 0x3F) << 6)
#define BIT_DBG_APB_DBG_BUS25_SEL(x)               (((x) & 0x3F))

/* REG_DBG_APB_SUB_SYS_DBG_PAD_SEL_CFG6 */

#define BIT_DBG_APB_DBG_BUS31_SEL(x)               (((x) & 0x3F) << 6)
#define BIT_DBG_APB_DBG_BUS30_SEL(x)               (((x) & 0x3F))

/* REG_DBG_APB_PAD_DBG_BUS_DATA_A */

#define BIT_DBG_APB_PAD_DBG_BUS_DATA_A(x)          (((x) & 0xFFFFFFFF))

/* REG_DBG_APB_PAD_DBG_BUS_DATA_B */

#define BIT_DBG_APB_PAD_DBG_BUS_DATA_B(x)          (((x) & 0xFFFFFFFF))

/* REG_DBG_APB_PAD_DBG_BUS_DATA_OUT */

#define BIT_DBG_APB_PAD_DBG_BUS_DATA_OUT(x)        (((x) & 0xFFFFFFFF))

/* REG_DBG_APB_ETR_AXI_MON_INT_EN */

#define BIT_DBG_APB_AWADDR3_MATCH_INT_EN           BIT(3)
#define BIT_DBG_APB_AWADDR2_MATCH_INT_EN           BIT(2)
#define BIT_DBG_APB_AWADDR1_MATCH_INT_EN           BIT(1)
#define BIT_DBG_APB_AWADDR0_MATCH_INT_EN           BIT(0)

/* REG_DBG_APB_ETR_AXI_MON_INT_CLR */

#define BIT_DBG_APB_AWADDR3_MATCH_INT_CLR          BIT(3)
#define BIT_DBG_APB_AWADDR2_MATCH_INT_CLR          BIT(2)
#define BIT_DBG_APB_AWADDR1_MATCH_INT_CLR          BIT(1)
#define BIT_DBG_APB_AWADDR0_MATCH_INT_CLR          BIT(0)

/* REG_DBG_APB_ETR_AXI_MON_INT_RAW */

#define BIT_DBG_APB_AWADDR3_MATCH_INT_RAW          BIT(3)
#define BIT_DBG_APB_AWADDR2_MATCH_INT_RAW          BIT(2)
#define BIT_DBG_APB_AWADDR1_MATCH_INT_RAW          BIT(1)
#define BIT_DBG_APB_AWADDR0_MATCH_INT_RAW          BIT(0)

/* REG_DBG_APB_ETR_AXI_MON_INT_STAT */

#define BIT_DBG_APB_AWADDR3_MATCH_INT_STAT         BIT(3)
#define BIT_DBG_APB_AWADDR2_MATCH_INT_STAT         BIT(2)
#define BIT_DBG_APB_AWADDR1_MATCH_INT_STAT         BIT(1)
#define BIT_DBG_APB_AWADDR0_MATCH_INT_STAT         BIT(0)

/* REG_DBG_APB_ETR_AXI_MON_AWADDR0 */

#define BIT_DBG_APB_ETR_AXI_MON_AWADDR0(x)         (((x) & 0xFFFFFFF))

/* REG_DBG_APB_ETR_AXI_MON_AWADDR1 */

#define BIT_DBG_APB_ETR_AXI_MON_AWADDR1(x)         (((x) & 0xFFFFFFF))

/* REG_DBG_APB_ETR_AXI_MON_AWADDR2 */

#define BIT_DBG_APB_ETR_AXI_MON_AWADDR2(x)         (((x) & 0xFFFFFFF))

/* REG_DBG_APB_ETR_AXI_MON_AWADDR3 */

#define BIT_DBG_APB_ETR_AXI_MON_AWADDR3(x)         (((x) & 0xFFFFFFF))

#endif