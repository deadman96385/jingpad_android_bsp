/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2017-12-07 16:03:11
 *
 */


#ifndef COM_AHB_H
#define COM_AHB_H

#define CTL_BASE_COM_AHB 0xD0010000


#define REG_COM_AHB_COM_RST         ( CTL_BASE_COM_AHB + 0x0000 )
#define REG_COM_AHB_SYS_SOFT_RST    ( CTL_BASE_COM_AHB + 0x0004 )
#define REG_COM_AHB_BTWF_CM4_RST    ( CTL_BASE_COM_AHB + 0x0008 )
#define REG_COM_AHB_GNSS_CM4_RST    ( CTL_BASE_COM_AHB + 0x000C )
#define REG_COM_AHB_BUS_MON         ( CTL_BASE_COM_AHB + 0x0010 )
#define REG_COM_AHB_COM_EB0         ( CTL_BASE_COM_AHB + 0x0014 )
#define REG_COM_AHB_COM_EB1         ( CTL_BASE_COM_AHB + 0x0018 )
#define REG_COM_AHB_CM4_CTRL0       ( CTL_BASE_COM_AHB + 0x001C )
#define REG_COM_AHB_SLP_CTRL0       ( CTL_BASE_COM_AHB + 0x0020 )
#define REG_COM_AHB_SLP_CTRL1       ( CTL_BASE_COM_AHB + 0x0024 )
#define REG_COM_AHB_SLP_CTRL2       ( CTL_BASE_COM_AHB + 0x0028 )
#define REG_COM_AHB_SLP_CTRL3       ( CTL_BASE_COM_AHB + 0x002C )
#define REG_COM_AHB_MAINMXT_CTRL0   ( CTL_BASE_COM_AHB + 0x0030 )
#define REG_COM_AHB_MAINMXT_CTRL1   ( CTL_BASE_COM_AHB + 0x0034 )
#define REG_COM_AHB_MAINMXT_CTRL2   ( CTL_BASE_COM_AHB + 0x0038 )
#define REG_COM_AHB_MAINMXT_CTRL3   ( CTL_BASE_COM_AHB + 0x003C )
#define REG_COM_AHB_MAINMXT_CTRL4   ( CTL_BASE_COM_AHB + 0x0040 )
#define REG_COM_AHB_MAINMXT_CTRL5   ( CTL_BASE_COM_AHB + 0x0044 )
#define REG_COM_AHB_MAINMXT_CTRL6   ( CTL_BASE_COM_AHB + 0x0048 )
#define REG_COM_AHB_IRAMMXT_CTRL0   ( CTL_BASE_COM_AHB + 0x004C )
#define REG_COM_AHB_IRAMMXT_CTRL1   ( CTL_BASE_COM_AHB + 0x0050 )
#define REG_COM_AHB_IRAMMXT_CTRL2   ( CTL_BASE_COM_AHB + 0x0054 )
#define REG_COM_AHB_IRAMMXT_CTRL3   ( CTL_BASE_COM_AHB + 0x0058 )
#define REG_COM_AHB_IRAMMXT_CTRL4   ( CTL_BASE_COM_AHB + 0x005C )
#define REG_COM_AHB_SLP_STS0        ( CTL_BASE_COM_AHB + 0x0060 )
#define REG_COM_AHB_SLP_STS1        ( CTL_BASE_COM_AHB + 0x0064 )
#define REG_COM_AHB_LP_CTRL0        ( CTL_BASE_COM_AHB + 0x0070 )
#define REG_COM_AHB_LP_CTRL1        ( CTL_BASE_COM_AHB + 0x0074 )
#define REG_COM_AHB_LP_CTRL2        ( CTL_BASE_COM_AHB + 0x0078 )
#define REG_COM_AHB_QOS_CTRL        ( CTL_BASE_COM_AHB + 0x0080 )
#define REG_COM_AHB_DUMY_IN         ( CTL_BASE_COM_AHB + 0x0084 )
#define REG_COM_AHB_DUMY_OUT        ( CTL_BASE_COM_AHB + 0x0088 )
#define REG_COM_AHB_CM4_CTRL1       ( CTL_BASE_COM_AHB + 0x008C )
#define REG_COM_AHB_CM4_CTRL2       ( CTL_BASE_COM_AHB + 0x0090 )
#define REG_COM_AHB_AON_TIMER31_0   ( CTL_BASE_COM_AHB + 0x0094 )
#define REG_COM_AHB_AON_TIMER47_32  ( CTL_BASE_COM_AHB + 0x0098 )
#define REG_COM_AHB_BTWF_INT_DIS    ( CTL_BASE_COM_AHB + 0x00A0 )
#define REG_COM_AHB_GNSS_INT_DIS    ( CTL_BASE_COM_AHB + 0x00A4 )
#define REG_COM_AHB_EXTCK_INT_DIS   ( CTL_BASE_COM_AHB + 0x00A8 )
#define REG_COM_AHB_PMU_DBG0        ( CTL_BASE_COM_AHB + 0x00B0 )
#define REG_COM_AHB_PMU_DBG1        ( CTL_BASE_COM_AHB + 0x00B4 )

/* REG_COM_AHB_COM_RST */

#define BIT_COM_AHB_SPINLOCK_SOFT_RST                 BIT(12)
#define BIT_COM_AHB_COM_AHB_SOFT_RST                  BIT(11)
#define BIT_COM_AHB_26M_GNSS_SOFT_RST                 BIT(10)
#define BIT_COM_AHB_26M_BTWF_SOFT_RST                 BIT(9)
#define BIT_COM_AHB_WCN_APB_SOFT_RST                  BIT(8)
#define BIT_COM_AHB_GNSS_APB_SOFT_RST                 BIT(7)
#define BIT_COM_AHB_GNSS_AHB_SOFT_RST                 BIT(6)
#define BIT_COM_AHB_BTWF_APB_SOFT_RST                 BIT(5)
#define BIT_COM_AHB_BTWF_AHB_SOFT_RST                 BIT(4)
#define BIT_COM_AHB_BUSMON3_SOFT_RST                  BIT(3)
#define BIT_COM_AHB_BUSMON2_SOFT_RST                  BIT(2)
#define BIT_COM_AHB_BUSMON1_SOFT_RST                  BIT(1)
#define BIT_COM_AHB_BUSMON0_SOFT_RST                  BIT(0)

/* REG_COM_AHB_SYS_SOFT_RST */

#define BIT_COM_AHB_WCN_SYS_SOFT_RST_SET              BIT(0)

/* REG_COM_AHB_BTWF_CM4_RST */

#define BIT_COM_AHB_BTWF_CM4_SOFT_RST_SET             BIT(0)

/* REG_COM_AHB_GNSS_CM4_RST */

#define BIT_COM_AHB_GNSS_CM4_SOFT_RST_SET             BIT(0)

/* REG_COM_AHB_BUS_MON */

#define BIT_COM_AHB_BUSMON3_CHN_SEL                   BIT(5)
#define BIT_COM_AHB_BUSMON0_CHN_SEL                   BIT(4)
#define BIT_COM_AHB_BUSMON3_EB                        BIT(3)
#define BIT_COM_AHB_BUSMON2_EB                        BIT(2)
#define BIT_COM_AHB_BUSMON1_EB                        BIT(1)
#define BIT_COM_AHB_BUSMON0_EB                        BIT(0)

/* REG_COM_AHB_COM_EB0 */

#define BIT_COM_AHB_SPINLOCK_EB                       BIT(10)
#define BIT_COM_AHB_WCN_DB_TEST_MUX(x)                (((x) & 0x3F) << 4)
#define BIT_COM_AHB_IRAM_MEM_MUX_SEL(x)               (((x) & 0x3) << 2)
#define BIT_COM_AHB_WCN_DEBUG_DUMP_SEL(x)             (((x) & 0x3))

/* REG_COM_AHB_COM_EB1 */

#define BIT_COM_AHB_BTWF_IRAM_DEEP_SLEEP_EN_AUTO2     BIT(13)
#define BIT_COM_AHB_GNSS_IRAM_DEEP_SLEEP_EN_AUTO2     BIT(12)
#define BIT_COM_AHB_BTWF_CACHE_DEEP_SLEEP_EN_AUTO2    BIT(11)
#define BIT_COM_AHB_GNSS_CACHE_DEEP_SLEEP_EN_AUTO2    BIT(10)
#define BIT_COM_AHB_BTWF_IRAM_DEEP_SLEEP_EN_AUTO      BIT(9)
#define BIT_COM_AHB_BTWF_IRAM_DEEP_SLEEP_EN_FRC       BIT(8)
#define BIT_COM_AHB_GNSS_IRAM_DEEP_SLEEP_EN_AUTO      BIT(7)
#define BIT_COM_AHB_GNSS_IRAM_DEEP_SLEEP_EN_FRC       BIT(6)
#define BIT_COM_AHB_BTWF_CACHE_DEEP_SLEEP_EN_AUTO     BIT(5)
#define BIT_COM_AHB_BTWF_CACHE_DEEP_SLEEP_EN_FRC      BIT(4)
#define BIT_COM_AHB_GNSS_CACHE_DEEP_SLEEP_EN_AUTO     BIT(3)
#define BIT_COM_AHB_GNSS_CACHE_DEEP_SLEEP_EN_FRC      BIT(2)

/* REG_COM_AHB_CM4_CTRL0 */


/* REG_COM_AHB_SLP_CTRL0 */

#define BIT_COM_AHB_BBPLL_FC_EN_AUTO                  BIT(30)
#define BIT_COM_AHB_GPLL_FC_EN_AUTO                   BIT(29)
#define BIT_COM_AHB_XTL_FC_EN_AUTO                    BIT(28)
#define BIT_COM_AHB_BBPLL1_EN_AUTO                    BIT(26)
#define BIT_COM_AHB_BBPLL2_EN_AUTO                    BIT(25)
#define BIT_COM_AHB_GPLL_EN_AUTO                      BIT(24)
#define BIT_COM_AHB_WF_EN_AUTO                        BIT(23)
#define BIT_COM_AHB_BT_EN_AUTO                        BIT(22)
#define BIT_COM_AHB_FM_EN_AUTO                        BIT(21)
#define BIT_COM_AHB_GS_EN_AUTO                        BIT(20)
#define BIT_COM_AHB_PD_GPS_SHUTDOWN_EN_AUTO           BIT(19)
#define BIT_COM_AHB_PD_GPS_SHUTDOWN_EN_FRC            BIT(18)
#define BIT_COM_AHB_PD_WIFI_SHUTDOWN_EN_AUTO          BIT(17)
#define BIT_COM_AHB_PD_WIFI_SHUTDOWN_EN_FRC           BIT(16)
#define BIT_COM_AHB_GNSS_DEEP_SLEEP_EN_AUTO           BIT(15)
#define BIT_COM_AHB_GNSS_DEEP_SLEEP_EN_FRC            BIT(14)
#define BIT_COM_AHB_BTWF_DEEP_SLEEP_EN_AUTO           BIT(13)
#define BIT_COM_AHB_BTWF_DEEP_SLEEP_EN_FRC            BIT(12)
#define BIT_COM_AHB_WIFI_CORE_SLEEP_EN_AUTO           BIT(11)
#define BIT_COM_AHB_WIFI_CORE_SLEEP_EN_FRC            BIT(10)
#define BIT_COM_AHB_GNSS_CORE_SLEEP_EN_AUTO           BIT(9)
#define BIT_COM_AHB_BTWF_CORE_SLEEP_EN_AUTO           BIT(8)
#define BIT_COM_AHB_BTWF_DMA_MBUS_SLEEP_EN_AUTO       BIT(7)
#define BIT_COM_AHB_BTWF_DMA_MBUS_SLEEP_EN_FRC        BIT(6)
#define BIT_COM_AHB_GNSS_CM4_MBUS_SLEEP_EN_AUTO       BIT(5)
#define BIT_COM_AHB_GNSS_CM4_MBUS_SLEEP_EN_FRC        BIT(4)
#define BIT_COM_AHB_BTWF_CM4_MBUS_SLEEP_EN_AUTO       BIT(3)
#define BIT_COM_AHB_BTWF_CM4_MBUS_SLEEP_EN_FRC        BIT(2)
#define BIT_COM_AHB_GNSS_SLEEP_XTL_ON                 BIT(1)
#define BIT_COM_AHB_BTWF_SLEEP_XTL_ON                 BIT(0)

/* REG_COM_AHB_SLP_CTRL1 */

#define BIT_COM_AHB_XTLBUF_CNT_DONE                   BIT(26)
#define BIT_COM_AHB_XTLBUF_WAIT_CNT_NUM(x)            (((x) & 0x3FF) << 16)
#define BIT_COM_AHB_XTL_CNT_DONE                      BIT(10)
#define BIT_COM_AHB_XTL_WAIT_CNT_NUM(x)               (((x) & 0x3FF))

/* REG_COM_AHB_SLP_CTRL2 */

#define BIT_COM_AHB_GPLL_CNT_DONE                     BIT(26)
#define BIT_COM_AHB_GPLL_WAIT_CNT_NUM(x)              (((x) & 0x3FF) << 16)
#define BIT_COM_AHB_APLL_CNT_DONE                     BIT(11)
#define BIT_COM_AHB_BPLL_CNT_DONE                     BIT(10)
#define BIT_COM_AHB_BBPLL_WAIT_CNT_NUM(x)             (((x) & 0x3FF))

/* REG_COM_AHB_SLP_CTRL3 */

#define BIT_COM_AHB_LP_STAT_DDR_S0_EN_AUTO            BIT(17)
#define BIT_COM_AHB_LP_STAT_DDR_S0_EN_FRC             BIT(16)
#define BIT_COM_AHB_LP_STAT_FOR_WKUP_EN_AUTO          BIT(15)
#define BIT_COM_AHB_LP_STAT_FOR_WKUP_EN_FRC           BIT(14)
#define BIT_COM_AHB_LP_STAT_FOR_GATE_EN_AUTO          BIT(13)
#define BIT_COM_AHB_LP_STAT_FOR_GATE_EN_FRC           BIT(12)
#define BIT_COM_AHB_GNSS_CM4_BUS_LIGHT_SLEEP_EN_AUTO  BIT(11)
#define BIT_COM_AHB_GNSS_CM4_BUS_LIGHT_SLEEP_EN_FRC   BIT(10)
#define BIT_COM_AHB_WIFI_BUS_LIGHT_SLEEP_EN_AUTO      BIT(9)
#define BIT_COM_AHB_WIFI_BUS_LIGHT_SLEEP_EN_FRC       BIT(8)
#define BIT_COM_AHB_BTWF_DMA_BUS_LIGHT_SLEEP_EN_AUTO  BIT(7)
#define BIT_COM_AHB_BTWF_DMA_BUS_LIGHT_SLEEP_EN_FRC   BIT(6)
#define BIT_COM_AHB_BTWF_CM4_BUS_LIGHT_SLEEP_EN_AUTO  BIT(5)
#define BIT_COM_AHB_BTWF_CM4_BUS_LIGHT_SLEEP_EN_FRC   BIT(4)
#define BIT_COM_AHB_WIFI_DDR_LIGHT_SLEEP_EN_AUTO      BIT(3)
#define BIT_COM_AHB_WIFI_DDR_LIGHT_SLEEP_EN_FRC       BIT(2)
#define BIT_COM_AHB_BTWF_DMA_WAKEUP_EN                BIT(0)

/* REG_COM_AHB_MAINMXT_CTRL0 */

#define BIT_COM_AHB_MAINMTX_CTRL0(x)                  (((x) & 0xFFFFFFFF))

/* REG_COM_AHB_MAINMXT_CTRL1 */

#define BIT_COM_AHB_MAINMTX_CTRL1(x)                  (((x) & 0xFFFFFFFF))

/* REG_COM_AHB_MAINMXT_CTRL2 */

#define BIT_COM_AHB_MAINMTX_CTRL2(x)                  (((x) & 0xFFFFFFFF))

/* REG_COM_AHB_MAINMXT_CTRL3 */

#define BIT_COM_AHB_MAINMTX_CTRL3(x)                  (((x) & 0xFFFFFFFF))

/* REG_COM_AHB_MAINMXT_CTRL4 */

#define BIT_COM_AHB_MAINMTX_CTRL4(x)                  (((x) & 0xFFFFFFFF))

/* REG_COM_AHB_MAINMXT_CTRL5 */

#define BIT_COM_AHB_MAINMTX_CTRL5(x)                  (((x) & 0xFFFFFFFF))

/* REG_COM_AHB_MAINMXT_CTRL6 */

#define BIT_COM_AHB_MAINMTX_CTRL6(x)                  (((x) & 0xFFFFFFFF))

/* REG_COM_AHB_IRAMMXT_CTRL0 */

#define BIT_COM_AHB_IRAMMTX_CTRL0(x)                  (((x) & 0xFFFFFFFF))

/* REG_COM_AHB_IRAMMXT_CTRL1 */

#define BIT_COM_AHB_IRAMMTX_CTRL1(x)                  (((x) & 0xFFFFFFFF))

/* REG_COM_AHB_IRAMMXT_CTRL2 */

#define BIT_COM_AHB_IRAMMTX_CTRL2(x)                  (((x) & 0xFFFFFFFF))

/* REG_COM_AHB_IRAMMXT_CTRL3 */

#define BIT_COM_AHB_IRAMMTX_CTRL3(x)                  (((x) & 0xFFFFFFFF))

/* REG_COM_AHB_IRAMMXT_CTRL4 */

#define BIT_COM_AHB_IRAMMTX_CTRL4(x)                  (((x) & 0xFFFFFFFF))

/* REG_COM_AHB_SLP_STS0 */

#define BIT_COM_AHB_WCN_BRIDGE_TANS_IDLE              BIT(12)
#define BIT_COM_AHB_WCN_SYS_ASYNC_BRG_OVERFLOW        BIT(11)
#define BIT_COM_AHB_LP_STAT_DDRMTX_M6                 BIT(9)
#define BIT_COM_AHB_LP_STAT_DDRMTX_S0                 BIT(8)
#define BIT_COM_AHB_LP_STAT_TOAON                     BIT(7)
#define BIT_COM_AHB_LP_STAT_TODDR                     BIT(6)
#define BIT_COM_AHB_WCN_TOP_DDR_ACK_DSLEEP            BIT(5)
#define BIT_COM_AHB_WCN_TOP_DDR_REQ_DSLEEP            BIT(4)
#define BIT_COM_AHB_GNSS_INT_REQ_FIQ_N                BIT(3)
#define BIT_COM_AHB_GNSS_INT_REQ_IRQ_N                BIT(2)
#define BIT_COM_AHB_BTWF_INT_REQ_FIQ_N                BIT(1)
#define BIT_COM_AHB_BTWF_INT_REQ_IRQ_N                BIT(0)

/* REG_COM_AHB_SLP_STS1 */

#define BIT_COM_AHB_BRIDGE_DEBUG_SIGNAL_W(x)          (((x) & 0xFFFFFFFF))

/* REG_COM_AHB_LP_CTRL0 */

#define BIT_COM_AHB_LP_FORCE_DDRMTX_M6                BIT(7)
#define BIT_COM_AHB_LP_FORCE_DDRMTX_S0                BIT(6)
#define BIT_COM_AHB_LP_FORCE_TOAON                    BIT(5)
#define BIT_COM_AHB_LP_EB_DDRMTX_M6                   BIT(3)
#define BIT_COM_AHB_LP_EB_DDRMTX_S0                   BIT(2)
#define BIT_COM_AHB_LP_EB_TOAON                       BIT(1)
#define BIT_COM_AHB_LP_EB_TODDR                       BIT(0)

/* REG_COM_AHB_LP_CTRL1 */

#define BIT_COM_AHB_LP_NUM_TOAON(x)                   (((x) & 0xFFFF) << 16)
#define BIT_COM_AHB_LP_NUM_TODDR(x)                   (((x) & 0xFFFF))

/* REG_COM_AHB_LP_CTRL2 */

#define BIT_COM_AHB_LP_NUM_DDRMTX_M6(x)               (((x) & 0xFFFF) << 16)
#define BIT_COM_AHB_LP_NUM_DDRMTX_S0(x)               (((x) & 0xFFFF))

/* REG_COM_AHB_QOS_CTRL */

#define BIT_COM_AHB_DDRMTX_M3_HPROT(x)                (((x) & 0xF) << 8)
#define BIT_COM_AHB_DDRMTX_ARQOS_M6(x)                (((x) & 0xF) << 4)
#define BIT_COM_AHB_DDRMTX_AWQOS_M6(x)                (((x) & 0xF))

/* REG_COM_AHB_DUMY_IN */

#define BIT_COM_AHB_WCN_DUMMY_PORT_IN(x)              (((x) & 0xFFFFFFFF))

/* REG_COM_AHB_DUMY_OUT */

#define BIT_COM_AHB_WCN_DUMMY_PORT_OUT(x)             (((x) & 0xFFFFFFFF))

/* REG_COM_AHB_CM4_CTRL1 */

#define BIT_COM_AHB_GNSS_CM4_SLEEPHOLD_REQ_N          BIT(1)
#define BIT_COM_AHB_BTWF_CM4_SLEEPHOLD_REQ_N          BIT(0)

/* REG_COM_AHB_CM4_CTRL2 */

#define BIT_COM_AHB_GNSS_CM4_SLEEPHOLD_ACK_N          BIT(1)
#define BIT_COM_AHB_BTWF_CM4_SLEEPHOLD_ACK_N          BIT(0)

/* REG_COM_AHB_AON_TIMER31_0 */

#define BIT_COM_AHB_AON_TIMER31_0(x)                  (((x) & 0xFFFFFFFF))

/* REG_COM_AHB_AON_TIMER47_32 */

#define BIT_COM_AHB_AON_TIMER47_32(x)                 (((x) & 0xFFFF))

/* REG_COM_AHB_BTWF_INT_DIS */

#define BIT_COM_AHB_BTWF_INT_DIS_EN                   BIT(0)

/* REG_COM_AHB_GNSS_INT_DIS */

#define BIT_COM_AHB_GNSS_INT_DIS_EN                   BIT(0)

/* REG_COM_AHB_EXTCK_INT_DIS */

#define BIT_COM_AHB_EXTCK_INT_DIS_EN                  BIT(0)

/* REG_COM_AHB_PMU_DBG0 */

#define BIT_COM_AHB_PMU_DBG0(x)                       (((x) & 0xFFFFFFFF))

/* REG_COM_AHB_PMU_DBG1 */

#define BIT_COM_AHB_PMU_DBG1(x)                       (((x) & 0xFFFFFFFF))


#endif /* COM_AHB_H */

