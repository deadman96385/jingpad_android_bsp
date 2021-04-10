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


#ifndef PUB_TOP_AHB_H
#define PUB_TOP_AHB_H

#define CTL_BASE_PUB_TOP_AHB 0x30200000


#define REG_PUB_TOP_AHB_DMC_DDR_CLK_CTRL           ( CTL_BASE_PUB_TOP_AHB + 0x0000 )
#define REG_PUB_TOP_AHB_DDR_CHN_SLEEP_CTRL0        ( CTL_BASE_PUB_TOP_AHB + 0x0010 )
#define REG_PUB_TOP_AHB_DDR_CHN_SLEEP_CTRL1        ( CTL_BASE_PUB_TOP_AHB + 0x0014 )
#define REG_PUB_TOP_AHB_DMC_AUTO_EN_X1             ( CTL_BASE_PUB_TOP_AHB + 0x007C )
#define REG_PUB_TOP_AHB_DMC_RST_CTL                ( CTL_BASE_PUB_TOP_AHB + 0x0080 )
#define REG_PUB_TOP_AHB_DMC_EMC_REF_SEL            ( CTL_BASE_PUB_TOP_AHB + 0x0084 )
#define REG_PUB_TOP_AHB_HSEL_IDLE_CNT              ( CTL_BASE_PUB_TOP_AHB + 0x0088 )
#define REG_PUB_TOP_AHB_DMC_CLK_INIT_SW_START      ( CTL_BASE_PUB_TOP_AHB + 0x0100 )
#define REG_PUB_TOP_AHB_DMC_CLK_STATE              ( CTL_BASE_PUB_TOP_AHB + 0x0104 )
#define REG_PUB_TOP_AHB_DMC_CLK_INIT_CFG           ( CTL_BASE_PUB_TOP_AHB + 0x0108 )
#define REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CFG        ( CTL_BASE_PUB_TOP_AHB + 0x0200 )
#define REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CNT0       ( CTL_BASE_PUB_TOP_AHB + 0x0204 )
#define REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CNT1       ( CTL_BASE_PUB_TOP_AHB + 0x0208 )
#define REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CNT2       ( CTL_BASE_PUB_TOP_AHB + 0x020C )
#define REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CNT3       ( CTL_BASE_PUB_TOP_AHB + 0x0210 )
#define REG_PUB_TOP_AHB_DMC_DDL_CTRL               ( CTL_BASE_PUB_TOP_AHB + 0x0300 )
#define REG_PUB_TOP_AHB_DMC_MON_CNT0               ( CTL_BASE_PUB_TOP_AHB + 0x0400 )
#define REG_PUB_TOP_AHB_DMC_MON_CNT1               ( CTL_BASE_PUB_TOP_AHB + 0x0404 )
#define REG_PUB_TOP_AHB_DMC_MON_CNT2               ( CTL_BASE_PUB_TOP_AHB + 0x0408 )
#define REG_PUB_TOP_AHB_DMC_MON_CNT3               ( CTL_BASE_PUB_TOP_AHB + 0x040C )
#define REG_PUB_TOP_AHB_DMC_MON_CNT4               ( CTL_BASE_PUB_TOP_AHB + 0x0410 )
#define REG_PUB_TOP_AHB_DMC_MON_CNT5               ( CTL_BASE_PUB_TOP_AHB + 0x0414 )

/* REG_PUB_TOP_AHB_DMC_DDR_CLK_CTRL */

#define BIT_PUB_TOP_AHB_PUB_CLK_DFS_SLEEP_AUTO_GATE_EN      BIT(31)
#define BIT_PUB_TOP_AHB_CLK_APB_AUTO_GATE_EN                BIT(30)
#define BIT_PUB_TOP_AHB_CLK_EMC_REF_AUTO_GATE_EN            BIT(29)
#define BIT_PUB_TOP_AHB_PUB_CLK_DFS_AUTO_GATE_EN            BIT(28)
#define BIT_PUB_TOP_AHB_DMC_DFI_MON_AUTO_GATE_EN            BIT(27)
#define BIT_PUB_TOP_AHB_DMC_SREF_AUTO_GATE_EN               BIT(26)
#define BIT_PUB_TOP_AHB_DDR_PHY_AUTO_GATE_EN                BIT(25)
#define BIT_PUB_TOP_AHB_DDR_UMCTL_AUTO_GATE_EN              BIT(24)
#define BIT_PUB_TOP_AHB_PUB_TOP_MON_EN                      BIT(23)
#define BIT_PUB_TOP_AHB_PUB_CLK_EMC_REF_EB                  BIT(22)
#define BIT_PUB_TOP_AHB_PUB_CLK_CSSYS_EB                    BIT(21)
#define BIT_PUB_TOP_AHB_PUB_CLK_APB_EB                      BIT(20)
#define BIT_PUB_TOP_AHB_PUB_CLK_PHY_X2_FORCE_PHASE(x)       (((x) & 0x3) << 18)
#define BIT_PUB_TOP_AHB_PUB_CLK_PHY_X2_FORCE_PHASE_SEL      BIT(17)
#define BIT_PUB_TOP_AHB_PUB_CLK_PHY_X2_FORCE_BYP            BIT(16)
#define BIT_PUB_TOP_AHB_PUB_CLK_DFS_EB                      BIT(15)
#define BIT_PUB_TOP_AHB_PUB_CLK_DMC_D2_CPU_EB               BIT(14)
#define BIT_PUB_TOP_AHB_PUB_CLK_MLB_D2_EB                   BIT(13)
#define BIT_PUB_TOP_AHB_PUB_CLK_DMC_D2_EB                   BIT(12)
#define BIT_PUB_TOP_AHB_PUB_CLK_DMC_X1_EB                   BIT(11)
#define BIT_PUB_TOP_AHB_PUB_CLK_PHY_X2_EB                   BIT(10)
#define BIT_PUB_TOP_AHB_PUB_CLK_DCC_EB                      BIT(9)
#define BIT_PUB_TOP_AHB_PUB_DDR_CLK_EB                      BIT(8)
#define BIT_PUB_TOP_AHB_PUB_CLK_DMC_D2_CPU_CGM_SEL          BIT(6)
#define BIT_PUB_TOP_AHB_PUB_CLK_MLB_D2_CGM_SEL              BIT(5)
#define BIT_PUB_TOP_AHB_PUB_CLK_DMC_D2_CGM_SEL              BIT(4)
#define BIT_PUB_TOP_AHB_PUB_CLK_DMC_X1_CGM_SEL              BIT(3)
#define BIT_PUB_TOP_AHB_PUB_CLK_PHY_X2_CGM_SEL              BIT(2)
#define BIT_PUB_TOP_AHB_PUB_CLK_DCC_CGM_SEL                 BIT(1)
#define BIT_PUB_TOP_AHB_PUB_DDR_CLK_CGM_SEL                 BIT(0)

/* REG_PUB_TOP_AHB_DDR_CHN_SLEEP_CTRL0 */

#define BIT_PUB_TOP_AHB_DDR_CHN7_AXI_LP_EN                  BIT(23)
#define BIT_PUB_TOP_AHB_DDR_CHN6_AXI_LP_EN                  BIT(22)
#define BIT_PUB_TOP_AHB_DDR_CHN5_AXI_LP_EN                  BIT(21)
#define BIT_PUB_TOP_AHB_DDR_CHN4_AXI_LP_EN                  BIT(20)
#define BIT_PUB_TOP_AHB_DDR_CHN3_AXI_LP_EN                  BIT(19)
#define BIT_PUB_TOP_AHB_DDR_CHN2_AXI_LP_EN                  BIT(18)
#define BIT_PUB_TOP_AHB_DDR_CHN1_AXI_LP_EN                  BIT(17)
#define BIT_PUB_TOP_AHB_DDR_CHN0_AXI_LP_EN                  BIT(16)
#define BIT_PUB_TOP_AHB_DDR_CHN7_CGM_SEL                    BIT(7)
#define BIT_PUB_TOP_AHB_DDR_CHN6_CGM_SEL                    BIT(6)
#define BIT_PUB_TOP_AHB_DDR_CHN5_CGM_SEL                    BIT(5)
#define BIT_PUB_TOP_AHB_DDR_CHN4_CGM_SEL                    BIT(4)
#define BIT_PUB_TOP_AHB_DDR_CHN3_CGM_SEL                    BIT(3)
#define BIT_PUB_TOP_AHB_DDR_CHN2_CGM_SEL                    BIT(2)
#define BIT_PUB_TOP_AHB_DDR_CHN1_CGM_SEL                    BIT(1)
#define BIT_PUB_TOP_AHB_DDR_CHN0_CGM_SEL                    BIT(0)

/* REG_PUB_TOP_AHB_DDR_CHN_SLEEP_CTRL1 */

#define BIT_PUB_TOP_AHB_DDR_CHN7_AXI_STOP_SEL               BIT(7)
#define BIT_PUB_TOP_AHB_DDR_CHN6_AXI_STOP_SEL               BIT(6)
#define BIT_PUB_TOP_AHB_DDR_CHN5_AXI_STOP_SEL               BIT(5)
#define BIT_PUB_TOP_AHB_DDR_CHN4_AXI_STOP_SEL               BIT(4)
#define BIT_PUB_TOP_AHB_DDR_CHN3_AXI_STOP_SEL               BIT(3)
#define BIT_PUB_TOP_AHB_DDR_CHN2_AXI_STOP_SEL               BIT(2)
#define BIT_PUB_TOP_AHB_DDR_CHN1_AXI_STOP_SEL               BIT(1)
#define BIT_PUB_TOP_AHB_DDR_CHN0_AXI_STOP_SEL               BIT(0)

/* REG_PUB_TOP_AHB_DMC_AUTO_EN_X1 */

#define BIT_PUB_TOP_AHB_PUB_TOP_DUMMY(x)                    (((x) & 0xFFFF) << 16)
#define BIT_PUB_TOP_AHB_EXIT_SELF_REFRESH_AUTO_EN_FW        BIT(13)
#define BIT_PUB_TOP_AHB_EXIT_SELF_REFRESH_AUTO_EN_ETR       BIT(12)
#define BIT_PUB_TOP_AHB_EXIT_SELF_REFRESH_AUTO_EN_INT       BIT(11)
#define BIT_PUB_TOP_AHB_EXTERNAL_ENABLE_AUTO_EN             BIT(10)
#define BIT_PUB_TOP_AHB_INT_MEM_FW_AUTO_EN                  BIT(9)
#define BIT_PUB_TOP_AHB_INT_REQ_PTM_AUTO_EN                 BIT(8)
#define BIT_PUB_TOP_AHB_INT_HW_DFS_EXIT_AUTO_EN             BIT(7)
#define BIT_PUB_TOP_AHB_INT_DFS_GIVEUP_AUTO_EN              BIT(6)
#define BIT_PUB_TOP_AHB_INT_DFS_DENY_AUTO_EN                BIT(5)
#define BIT_PUB_TOP_AHB_INT_DFS_COMPLETE_AUTO_EN            BIT(4)
#define BIT_PUB_TOP_AHB_INT_DFS_ERROR_AUTO_EN               BIT(3)
#define BIT_PUB_TOP_AHB_INT_DMC_MPU_AUTO_EN                 BIT(2)
#define BIT_PUB_TOP_AHB_INT_DFI_BUS_AUTO_EN                 BIT(1)
#define BIT_PUB_TOP_AHB_INT_BUSMIN_AUTO_EN                  BIT(0)

/* REG_PUB_TOP_AHB_DMC_RST_CTL */

#define BIT_PUB_TOP_AHB_DCC_SOFT_RST                        BIT(1)
#define BIT_PUB_TOP_AHB_DDRPHY_SOFT_RST                     BIT(0)

/* REG_PUB_TOP_AHB_DMC_EMC_REF_SEL */

#define BIT_PUB_TOP_AHB_PUB_CLK_DMC_BRIDGE_CG_EN            BIT(2)
#define BIT_PUB_TOP_AHB_PUB_CLK_DMC_BRIDGE_SEL_EN           BIT(1)
#define BIT_PUB_TOP_AHB_DMC_EMC_REF_SEL                     BIT(0)

/* REG_PUB_TOP_AHB_HSEL_IDLE_CNT */

#define BIT_PUB_TOP_AHB_DFI_MON_TIMER_DELAY(x)              (((x) & 0xFF) << 24)
#define BIT_PUB_TOP_AHB_DFI_MON_IDLE_CNT(x)                 (((x) & 0xFF) << 16)
#define BIT_PUB_TOP_AHB_PUB_LATMON2_TRIGGER_SEL(x)          (((x) & 0x7) << 13)
#define BIT_PUB_TOP_AHB_DMC_ST_MON_SEL(x)                   (((x) & 0x3) << 10)
#define BIT_PUB_TOP_AHB_HSEL_IDLE_CNT(x)                    (((x) & 0xFF))

/* REG_PUB_TOP_AHB_DMC_CLK_INIT_SW_START */

#define BIT_PUB_TOP_AHB_DMC_CLK_INIT_SW_START               BIT(0)

/* REG_PUB_TOP_AHB_DMC_CLK_STATE */

#define BIT_PUB_TOP_AHB_DFS_LP_CTRL_CUR_STATE(x)            (((x) & 0x7) << 12)
#define BIT_PUB_TOP_AHB_DMC_CLK_HW_CUR_STATE(x)             (((x) & 0xF) << 4)
#define BIT_PUB_TOP_AHB_DMC_CUR_CLK_MODE(x)                 (((x) & 0x3) << 2)
#define BIT_PUB_TOP_AHB_DMC_CLK_INIT_SW_DONE                BIT(0)

/* REG_PUB_TOP_AHB_DMC_CLK_INIT_CFG */

#define BIT_PUB_TOP_AHB_DMC_STOP_WAIT_CNT(x)                (((x) & 0xFF) << 16)
#define BIT_PUB_TOP_AHB_DFI_MASK_WAIT_TIME(x)               (((x) & 0xF) << 12)
#define BIT_PUB_TOP_AHB_DUMMY_REG(x)                        (((x) & 0x7) << 9)
#define BIT_PUB_TOP_AHB_DMC_SLEEP_FORCE_FINISH_MODE         BIT(8)
#define BIT_PUB_TOP_AHB_DESKEW_PLL_PD_DEFAULT_SW            BIT(5)
#define BIT_PUB_TOP_AHB_DESKEW_PLL_PD_DEFAULT_SEL           BIT(4)
#define BIT_PUB_TOP_AHB_DMC_SLEEP_CLK_AUTO_MODE             BIT(1)
#define BIT_PUB_TOP_AHB_DFS_CLK_AUTO_MODE                   BIT(0)

/* REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CFG */

#define BIT_PUB_TOP_AHB_DSKDLL_DCC_FINE_WAIT_SRC_SW         BIT(10)
#define BIT_PUB_TOP_AHB_DSKDLL_DCC_COARSE_WAIT_SRC_SW       BIT(9)
#define BIT_PUB_TOP_AHB_DSKPLL_LOCK_WAIT_SRC_SW             BIT(8)
#define BIT_PUB_TOP_AHB_DDL_ADJS_V_WAIT_EN                  BIT(3)
#define BIT_PUB_TOP_AHB_DSKDLL_DCC_FINE_WAIT_EN             BIT(2)
#define BIT_PUB_TOP_AHB_DSKDLL_DCC_COARSE_WAIT_EN           BIT(1)
#define BIT_PUB_TOP_AHB_DSKPLL_LOCK_WAIT_EN                 BIT(0)

/* REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CNT0 */

#define BIT_PUB_TOP_AHB_WAIT_CNT_DSKPLL_PWRON_TIME(x)       (((x) & 0xFFFF) << 16)
#define BIT_PUB_TOP_AHB_WAIT_CNT_DSKPLL_LOCK_TIME(x)        (((x) & 0xFFFF))

/* REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CNT1 */

#define BIT_PUB_TOP_AHB_WAIT_CNT_DSKDLL_DCC_FINE_TIME(x)    (((x) & 0xFFFF) << 16)
#define BIT_PUB_TOP_AHB_WAIT_CNT_DSKDLL_DCC_COARSE_TIME(x)  (((x) & 0xFFFF))

/* REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CNT2 */

#define BIT_PUB_TOP_AHB_WAIT_CNT_DFS_RESET_OFF_TIME(x)      (((x) & 0xFF) << 24)
#define BIT_PUB_TOP_AHB_WAIT_CNT_DFS_RESET_ON_TIME(x)       (((x) & 0xFF) << 16)
#define BIT_PUB_TOP_AHB_WAIT_CNT_DFS_CLK_OFF_TIME(x)        (((x) & 0xFF))

/* REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CNT3 */

#define BIT_PUB_TOP_AHB_WAIT_CNT_DDL_ADJS_V_HIGH_TIME(x)    (((x) & 0xFF) << 16)
#define BIT_PUB_TOP_AHB_WAIT_CNT_DDL_ADJS_V_LOW_TIME(x)     (((x) & 0xFF))

/* REG_PUB_TOP_AHB_DMC_DDL_CTRL */

#define BIT_PUB_TOP_AHB_PTEST_DDL_SCOUT                     BIT(26)
#define BIT_PUB_TOP_AHB_PTEST_DDL_SCIN                      BIT(25)
#define BIT_PUB_TOP_AHB_PTEST_DDL_SE                        BIT(24)
#define BIT_PUB_TOP_AHB_DMC_DDL_SW_ADJS(x)                  (((x) & 0x1FF) << 8)
#define BIT_PUB_TOP_AHB_DMC_DDL_SW_UPDATE                   BIT(7)
#define BIT_PUB_TOP_AHB_DMC_DDL_SW_BYPASS                   BIT(6)
#define BIT_PUB_TOP_AHB_DMC_DDL_SW_RESET                    BIT(5)
#define BIT_PUB_TOP_AHB_DMC_DDL_SW_ADJS_VALID               BIT(4)
#define BIT_PUB_TOP_AHB_DMC_DDL_CFG_SRC_PURE_SW             BIT(1)
#define BIT_PUB_TOP_AHB_DMC_DDL_CFG_SRC_SW                  BIT(0)

/* REG_PUB_TOP_AHB_DMC_MON_CNT0 */

#define BIT_PUB_TOP_AHB_DMC_ST_IDLE_CYCLE_CNT(x)            (((x) & 0xFFFFFFFF))

/* REG_PUB_TOP_AHB_DMC_MON_CNT1 */

#define BIT_PUB_TOP_AHB_DMC_ST_WRITE_CYCLE_CNT(x)           (((x) & 0xFFFFFFFF))

/* REG_PUB_TOP_AHB_DMC_MON_CNT2 */

#define BIT_PUB_TOP_AHB_DMC_ST_READ_CYCLE_CNT(x)            (((x) & 0xFFFFFFFF))

/* REG_PUB_TOP_AHB_DMC_MON_CNT3 */

#define BIT_PUB_TOP_AHB_DMC_ST_SREF_CYCLE_CNT(x)            (((x) & 0xFFFFFFFF))

/* REG_PUB_TOP_AHB_DMC_MON_CNT4 */

#define BIT_PUB_TOP_AHB_DMC_ST_LIGHT_CYCLE_CNT(x)           (((x) & 0xFFFFFFFF))

/* REG_PUB_TOP_AHB_DMC_MON_CNT5 */

#define BIT_PUB_TOP_AHB_DMC_ST_LIGHT_CNT(x)                 (((x) & 0xFFFF))


#endif /* PUB_TOP_AHB_H */

