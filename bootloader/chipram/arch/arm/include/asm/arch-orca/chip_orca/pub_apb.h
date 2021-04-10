/*
 * Copyright (C) 2019 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2019-02-11 15:07:05
 *
 */


#ifndef PUB_APB_REG_H
#define PUB_APB_REG_H

#define CTL_BASE_PUB_APB_REG 0x61050000


#define REG_PUB_APB_REG_DDR_EB                        ( CTL_BASE_PUB_APB_REG + 0x0000 )
#define REG_PUB_APB_REG_DDR_SOFT_RST                  ( CTL_BASE_PUB_APB_REG + 0x0004 )
#define REG_PUB_APB_REG_DDL_MASK_CTRL                 ( CTL_BASE_PUB_APB_REG + 0x1000 )
#define REG_PUB_APB_REG_PUB_DDR_CHN_LP_CTRL           ( CTL_BASE_PUB_APB_REG + 0x3104 )
#define REG_PUB_APB_REG_DMC_EXT_LPCTRL_CFG            ( CTL_BASE_PUB_APB_REG + 0x31A0 )
#define REG_PUB_APB_REG_DMC_EXT_LPCTRL_SEQL           ( CTL_BASE_PUB_APB_REG + 0x31A4 )
#define REG_PUB_APB_REG_DMC_EXT_LPCTRL_SEQH           ( CTL_BASE_PUB_APB_REG + 0x31A8 )
#define REG_PUB_APB_REG_DMC_EXT_LPCTRL_STEP           ( CTL_BASE_PUB_APB_REG + 0x31AC )
#define REG_PUB_APB_REG_QOS_SELECT                    ( CTL_BASE_PUB_APB_REG + 0x31B0 )
#define REG_PUB_APB_REG_DPLL_PRE_DIV_STATUS           ( CTL_BASE_PUB_APB_REG + 0x31C0 )
#define REG_PUB_APB_REG_DFI_BWMON_TIMER               ( CTL_BASE_PUB_APB_REG + 0x31C4 )
#define REG_PUB_APB_REG_QOS_SWITCH                    ( CTL_BASE_PUB_APB_REG + 0x31C8 )
#define REG_PUB_APB_REG_PUB_BUS_CK_EB                 ( CTL_BASE_PUB_APB_REG + 0x31CC )
#define REG_PUB_APB_REG_AXI_LPC_CTRL_3                ( CTL_BASE_PUB_APB_REG + 0x31D0 )
#define REG_PUB_APB_REG_PUB_INT_CG_EN                 ( CTL_BASE_PUB_APB_REG + 0x31D4 )
#define REG_PUB_APB_REG_TIMER_ENABLE                  ( CTL_BASE_PUB_APB_REG + 0x31D8 )
#define REG_PUB_APB_REG_VOTE_CTRL                     ( CTL_BASE_PUB_APB_REG + 0x31E0 )
#define REG_PUB_APB_REG_VOTE_STATUS                   ( CTL_BASE_PUB_APB_REG + 0x31E4 )
#define REG_PUB_APB_REG_DFS_HW_CTRL3                  ( CTL_BASE_PUB_APB_REG + 0x31F0 )
#define REG_PUB_APB_REG_QOS_FIXED_CTRL0               ( CTL_BASE_PUB_APB_REG + 0x31F4 )
#define REG_PUB_APB_REG_QOS_FIXED_CTRL1               ( CTL_BASE_PUB_APB_REG + 0x31F8 )
#define REG_PUB_APB_REG_QOS_FIXED_CTRL2               ( CTL_BASE_PUB_APB_REG + 0x31FC )
#define REG_PUB_APB_REG_PUB_AXI_QOS_URGENT_REG_0      ( CTL_BASE_PUB_APB_REG + 0x3200 )
#define REG_PUB_APB_REG_PUB_AXI_QOS_URGENT_REG_1      ( CTL_BASE_PUB_APB_REG + 0x3204 )
#define REG_PUB_APB_REG_PUB_INT_CTRL                  ( CTL_BASE_PUB_APB_REG + 0x32F0 )
#define REG_PUB_APB_REG_DFS_STATUS                    ( CTL_BASE_PUB_APB_REG + 0x32F4 )
#define REG_PUB_APB_REG_DFS_STATUS1                   ( CTL_BASE_PUB_APB_REG + 0x32F8 )
#define REG_PUB_APB_REG_DFS_FC_REQ_DELAY              ( CTL_BASE_PUB_APB_REG + 0x32FC )
#define REG_PUB_APB_REG_PUB_LP_GEN_CTRL               ( CTL_BASE_PUB_APB_REG + 0x333C )
#define REG_PUB_APB_REG_AXI_LPC_CTRL_0                ( CTL_BASE_PUB_APB_REG + 0x334C )
#define REG_PUB_APB_REG_AXI_LPC_CTRL_1                ( CTL_BASE_PUB_APB_REG + 0x3350 )
#define REG_PUB_APB_REG_AXI_LPC_CTRL_2                ( CTL_BASE_PUB_APB_REG + 0x3354 )
#define REG_PUB_APB_REG_FENCING_CTRL                  ( CTL_BASE_PUB_APB_REG + 0x3358 )
#define REG_PUB_APB_REG_CP_BASE_ADDR                  ( CTL_BASE_PUB_APB_REG + 0x3360 )
#define REG_PUB_APB_REG_CLK_PUB_DFS_CTRL              ( CTL_BASE_PUB_APB_REG + 0x3364 )
#define REG_PUB_APB_REG_AXI_LPC_CTRL_4                ( CTL_BASE_PUB_APB_REG + 0x3368 )
#define REG_PUB_APB_REG_AXI_LPC_CTRL_5                ( CTL_BASE_PUB_APB_REG + 0x336C )
#define REG_PUB_APB_REG_BIST_CTRL                     ( CTL_BASE_PUB_APB_REG + 0x3400 )
#define REG_PUB_APB_REG_DMC_SOFT_RST_CTRL             ( CTL_BASE_PUB_APB_REG + 0x3404 )
#define REG_PUB_APB_REG_MC_IDLE_WAIT_CTRL             ( CTL_BASE_PUB_APB_REG + 0x3414 )
#define REG_PUB_APB_REG_QOS_THRESHOLD_0               ( CTL_BASE_PUB_APB_REG + 0x3418 )
#define REG_PUB_APB_REG_QOS_THRESHOLD_1               ( CTL_BASE_PUB_APB_REG + 0x341C )
#define REG_PUB_APB_REG_DMC_DDR_CLK_CTRL              ( CTL_BASE_PUB_APB_REG + 0x4000 )
#define REG_PUB_APB_REG_DMC_CLK_INIT_SW_START         ( CTL_BASE_PUB_APB_REG + 0x4004 )
#define REG_PUB_APB_REG_DMC_CLK_STATE                 ( CTL_BASE_PUB_APB_REG + 0x4008 )
#define REG_PUB_APB_REG_DMC_CLK_INIT_CFG              ( CTL_BASE_PUB_APB_REG + 0x400C )
#define REG_PUB_APB_REG_DMC_DESKEW_WAIT_CFG           ( CTL_BASE_PUB_APB_REG + 0x4010 )
#define REG_PUB_APB_REG_DMC_DESKEW_WAIT_CNT0          ( CTL_BASE_PUB_APB_REG + 0x4014 )
#define REG_PUB_APB_REG_DMC_DESKEW_WAIT_CNT1          ( CTL_BASE_PUB_APB_REG + 0x4018 )
#define REG_PUB_APB_REG_DMC_DESKEW_WAIT_CNT2          ( CTL_BASE_PUB_APB_REG + 0x401C )
#define REG_PUB_APB_REG_DMC_DESKEW_WAIT_CNT3          ( CTL_BASE_PUB_APB_REG + 0x4020 )
#define REG_PUB_APB_REG_DMC_DDL_CTRL                  ( CTL_BASE_PUB_APB_REG + 0x402C )
#define REG_PUB_APB_REG_DFS_PURE_SW_CTRL              ( CTL_BASE_PUB_APB_REG + 0x4100 )
#define REG_PUB_APB_REG_DFS_SW_CTRL                   ( CTL_BASE_PUB_APB_REG + 0x4104 )
#define REG_PUB_APB_REG_DFS_SW_CTRL1                  ( CTL_BASE_PUB_APB_REG + 0x4108 )
#define REG_PUB_APB_REG_DFS_SW_CTRL2                  ( CTL_BASE_PUB_APB_REG + 0x410C )
#define REG_PUB_APB_REG_DFS_SW_CTRL3                  ( CTL_BASE_PUB_APB_REG + 0x4110 )
#define REG_PUB_APB_REG_DFS_HW_CTRL                   ( CTL_BASE_PUB_APB_REG + 0x4114 )
#define REG_PUB_APB_REG_DFS_HW_CTRL1                  ( CTL_BASE_PUB_APB_REG + 0x4118 )
#define REG_PUB_APB_REG_DFS_HW_CTRL2                  ( CTL_BASE_PUB_APB_REG + 0x411C )
#define REG_PUB_APB_REG_DFS_HW_RATIO_SET0             ( CTL_BASE_PUB_APB_REG + 0x4120 )
#define REG_PUB_APB_REG_DFS_HW_RATIO_SET1             ( CTL_BASE_PUB_APB_REG + 0x4124 )
#define REG_PUB_APB_REG_DFS_HW_RATIO_SET2             ( CTL_BASE_PUB_APB_REG + 0x4128 )
#define REG_PUB_APB_REG_DFS_HW_RATIO_SET3             ( CTL_BASE_PUB_APB_REG + 0x412C )
#define REG_PUB_APB_REG_DFS_HW_RATIO_SET4             ( CTL_BASE_PUB_APB_REG + 0x4130 )
#define REG_PUB_APB_REG_DFS_HW_RATIO_SET5             ( CTL_BASE_PUB_APB_REG + 0x4134 )
#define REG_PUB_APB_REG_DFS_HW_RATIO_SET6             ( CTL_BASE_PUB_APB_REG + 0x4138 )
#define REG_PUB_APB_REG_DFS_HW_RATIO_SET7             ( CTL_BASE_PUB_APB_REG + 0x413C )
#define REG_PUB_APB_REG_DFS_HW_RATIO_SET8             ( CTL_BASE_PUB_APB_REG + 0x4140 )
#define REG_PUB_APB_REG_HW_DESKEWPLL_PD_CTRL0         ( CTL_BASE_PUB_APB_REG + 0x4144 )
#define REG_PUB_APB_REG_HW_DESKEWPLL_PD_CTRL1         ( CTL_BASE_PUB_APB_REG + 0x4148 )
#define REG_PUB_APB_REG_DVS_CTRL_0                    ( CTL_BASE_PUB_APB_REG + 0x4150 )
#define REG_PUB_APB_REG_DVS_CTRL_1                    ( CTL_BASE_PUB_APB_REG + 0x4154 )
#define REG_PUB_APB_REG_DVS_CTRL_2                    ( CTL_BASE_PUB_APB_REG + 0x4158 )
#define REG_PUB_APB_REG_VOTE_MASTER_EN                ( CTL_BASE_PUB_APB_REG + 0x4310 )
#define REG_PUB_APB_REG_VOTE_FSM_CNT                  ( CTL_BASE_PUB_APB_REG + 0x4314 )
#define REG_PUB_APB_REG_THRESHOLD_INC_FREQ_0          ( CTL_BASE_PUB_APB_REG + 0x4318 )
#define REG_PUB_APB_REG_THRESHOLD_INC_FREQ_1          ( CTL_BASE_PUB_APB_REG + 0x431C )
#define REG_PUB_APB_REG_THRESHOLD_INC_FREQ_2          ( CTL_BASE_PUB_APB_REG + 0x4320 )
#define REG_PUB_APB_REG_THRESHOLD_INC_FREQ_3          ( CTL_BASE_PUB_APB_REG + 0x4324 )
#define REG_PUB_APB_REG_THRESHOLD_INC_FREQ_4          ( CTL_BASE_PUB_APB_REG + 0x4328 )
#define REG_PUB_APB_REG_THRESHOLD_INC_FREQ_5          ( CTL_BASE_PUB_APB_REG + 0x432C )
#define REG_PUB_APB_REG_THRESHOLD_INC_FREQ_6          ( CTL_BASE_PUB_APB_REG + 0x4330 )
#define REG_PUB_APB_REG_THRESHOLD_INC_FREQ_7          ( CTL_BASE_PUB_APB_REG + 0x4334 )
#define REG_PUB_APB_REG_TEST_DSKPLL_BIST_CNT          ( CTL_BASE_PUB_APB_REG + 0x4340 )
#define REG_PUB_APB_REG_PUB_STATUS_MON_CTRL           ( CTL_BASE_PUB_APB_REG + 0x6200 )
#define REG_PUB_APB_REG_PUB_ST_IDLE_CYC_CNT           ( CTL_BASE_PUB_APB_REG + 0x6204 )
#define REG_PUB_APB_REG_PUB_ST_WR_CYC_CNT             ( CTL_BASE_PUB_APB_REG + 0x6208 )
#define REG_PUB_APB_REG_PUB_ST_RD_CYC_CNT             ( CTL_BASE_PUB_APB_REG + 0x620C )
#define REG_PUB_APB_REG_PUB_ST_SR_CYC_CNT             ( CTL_BASE_PUB_APB_REG + 0x6210 )
#define REG_PUB_APB_REG_PUB_ST_LS_CYC_CNT             ( CTL_BASE_PUB_APB_REG + 0x6214 )
#define REG_PUB_APB_REG_PUB_ST_LS_TIME_CNT            ( CTL_BASE_PUB_APB_REG + 0x6218 )
#define REG_PUB_APB_REG_PUB_DFS_F0_CYC_CNT            ( CTL_BASE_PUB_APB_REG + 0x621C )
#define REG_PUB_APB_REG_PUB_DFS_F1_CYC_CNT            ( CTL_BASE_PUB_APB_REG + 0x6220 )
#define REG_PUB_APB_REG_PUB_DFS_F2_CYC_CNT            ( CTL_BASE_PUB_APB_REG + 0x6224 )
#define REG_PUB_APB_REG_PUB_DFS_F3_CYC_CNT            ( CTL_BASE_PUB_APB_REG + 0x6228 )
#define REG_PUB_APB_REG_PUB_DFS_F4_CYC_CNT            ( CTL_BASE_PUB_APB_REG + 0x622C )
#define REG_PUB_APB_REG_PUB_DFS_F5_CYC_CNT            ( CTL_BASE_PUB_APB_REG + 0x6230 )
#define REG_PUB_APB_REG_PUB_DFS_F6_CYC_CNT            ( CTL_BASE_PUB_APB_REG + 0x6234 )
#define REG_PUB_APB_REG_PUB_DFS_F7_CYC_CNT            ( CTL_BASE_PUB_APB_REG + 0x6238 )
#define REG_PUB_APB_REG_PUB_DFS_CNT                   ( CTL_BASE_PUB_APB_REG + 0x623C )
#define REG_PUB_APB_REG_VOTE_CTRL_APCPU               ( CTL_BASE_PUB_APB_REG + 0x6400 )
#define REG_PUB_APB_REG_VOTE_CTRL_MINIAP              ( CTL_BASE_PUB_APB_REG + 0x6404 )
#define REG_PUB_APB_REG_VOTE_CTRL_NRCPU               ( CTL_BASE_PUB_APB_REG + 0x6408 )
#define REG_PUB_APB_REG_VOTE_CTRL_NRACC               ( CTL_BASE_PUB_APB_REG + 0x640C )
#define REG_PUB_APB_REG_VOTE_CTRL_V3CPU               ( CTL_BASE_PUB_APB_REG + 0x6410 )
#define REG_PUB_APB_REG_VOTE_CTRL_AGCP                ( CTL_BASE_PUB_APB_REG + 0x6414 )
#define REG_PUB_APB_REG_VOTE_CTRL_SW                  ( CTL_BASE_PUB_APB_REG + 0x6418 )
#define REG_PUB_APB_REG_VOTE_CTRL_V3ACC               ( CTL_BASE_PUB_APB_REG + 0x641C )
#define REG_PUB_APB_REG_VOTE_CTRL_PSCP                ( CTL_BASE_PUB_APB_REG + 0x6420 )
#define REG_PUB_APB_REG_VOTE_CTRL_WCDMA_PS            ( CTL_BASE_PUB_APB_REG + 0x6424 )
#define REG_PUB_APB_REG_VOTE_CTRL_TDS_PS              ( CTL_BASE_PUB_APB_REG + 0x6428 )
#define REG_PUB_APB_REG_VOTE_CTRL_GSM_PS              ( CTL_BASE_PUB_APB_REG + 0x642C )
#define REG_PUB_APB_REG_VOTE_CTRL_WCDMA_PHY           ( CTL_BASE_PUB_APB_REG + 0x6430 )
#define REG_PUB_APB_REG_VOTE_CTRL_TDS_PHY             ( CTL_BASE_PUB_APB_REG + 0x6434 )
#define REG_PUB_APB_REG_VOTE_CTRL_GSM_PHY             ( CTL_BASE_PUB_APB_REG + 0x6438 )
#define REG_PUB_APB_REG_DFS_GFREE_CTRL                ( CTL_BASE_PUB_APB_REG + 0x6500 )
#define REG_PUB_APB_REG_DFS_SW_CTRL_APPEND            ( CTL_BASE_PUB_APB_REG + 0x6600 )
#define REG_PUB_APB_REG_AWURGENT_DBG_CTRL             ( CTL_BASE_PUB_APB_REG + 0x6800 )
#define REG_PUB_APB_REG_ARURGENT_DBG_CTRL             ( CTL_BASE_PUB_APB_REG + 0x6804 )
#define REG_PUB_APB_REG_LSLP_SRE_SIM                  ( CTL_BASE_PUB_APB_REG + 0x6808 )
#define REG_PUB_APB_REG_VOTE_BW_APCPU                 ( CTL_BASE_PUB_APB_REG + 0x680C )
#define REG_PUB_APB_REG_VOTE_BW_MINIAP                ( CTL_BASE_PUB_APB_REG + 0x6810 )
#define REG_PUB_APB_REG_VOTE_BW_AGCP                  ( CTL_BASE_PUB_APB_REG + 0x6814 )
#define REG_PUB_APB_REG_VOTE_BW_PSCP                  ( CTL_BASE_PUB_APB_REG + 0x6818 )
#define REG_PUB_APB_REG_VOTE_BW_NRACC                 ( CTL_BASE_PUB_APB_REG + 0x681C )
#define REG_PUB_APB_REG_VOTE_BW_NRCPU                 ( CTL_BASE_PUB_APB_REG + 0x6820 )
#define REG_PUB_APB_REG_VOTE_BW_V3ACC                 ( CTL_BASE_PUB_APB_REG + 0x6824 )
#define REG_PUB_APB_REG_VOTE_BW_V3CPU                 ( CTL_BASE_PUB_APB_REG + 0x6828 )
#define REG_PUB_APB_REG_VOTE_BW_WACC                  ( CTL_BASE_PUB_APB_REG + 0x682C )
#define REG_PUB_APB_REG_VOTE_BW_WCPU                  ( CTL_BASE_PUB_APB_REG + 0x6830 )
#define REG_PUB_APB_REG_VOTE_BW_TDACC                 ( CTL_BASE_PUB_APB_REG + 0x6834 )
#define REG_PUB_APB_REG_VOTE_BW_TDCPU                 ( CTL_BASE_PUB_APB_REG + 0x6838 )
#define REG_PUB_APB_REG_VOTE_BW_GSMACC                ( CTL_BASE_PUB_APB_REG + 0x683C )
#define REG_PUB_APB_REG_VOTE_BW_GSMCPU                ( CTL_BASE_PUB_APB_REG + 0x6840 )
#define REG_PUB_APB_REG_VOTE_BW_SW                    ( CTL_BASE_PUB_APB_REG + 0x6844 )
#define REG_PUB_APB_REG_MTX_BUSMON_CTRL               ( CTL_BASE_PUB_APB_REG + 0x6848 )
#define REG_PUB_APB_REG_HIGH_URGENCY_CTRL             ( CTL_BASE_PUB_APB_REG + 0x684C )
#define REG_PUB_APB_REG_LPC_PU_NUM_CTRL_0             ( CTL_BASE_PUB_APB_REG + 0x6850 )
#define REG_PUB_APB_REG_LPC_PU_NUM_CTRL_1             ( CTL_BASE_PUB_APB_REG + 0x6854 )
#define REG_PUB_APB_REG_LPC_PU_NUM_CTRL_2             ( CTL_BASE_PUB_APB_REG + 0x6858 )
#define REG_PUB_APB_REG_LPC_PU_NUM_CTRL_3             ( CTL_BASE_PUB_APB_REG + 0x685C )
#define REG_PUB_APB_REG_DMC_BIST_MST_AXUSER_CFG_0     ( CTL_BASE_PUB_APB_REG + 0x6860 )
#define REG_PUB_APB_REG_DMC_BIST_MST_AXUSER_CFG_1     ( CTL_BASE_PUB_APB_REG + 0x6864 )
#define REG_PUB_APB_REG_PUB0_DUMMY_REG0               ( CTL_BASE_PUB_APB_REG + 0x8000 )
#define REG_PUB_APB_REG_PUB0_DUMMY_REG1               ( CTL_BASE_PUB_APB_REG + 0x8004 )

/* REG_PUB_APB_REG_DDR_EB */


/* REG_PUB_APB_REG_DDR_SOFT_RST */


/* REG_PUB_APB_REG_DDL_MASK_CTRL */

#define BIT_PUB_APB_REG_DDL_MASK_CTRL(x)                             (((x) & 0x7))

/* REG_PUB_APB_REG_PUB_DDR_CHN_LP_CTRL */

#define BIT_PUB_APB_REG_DDR_CHN6_AXI_LP_EN                           BIT(14)
#define BIT_PUB_APB_REG_DDR_CHN5_AXI_LP_EN                           BIT(13)
#define BIT_PUB_APB_REG_DDR_CHN4_AXI_LP_EN                           BIT(12)
#define BIT_PUB_APB_REG_DDR_CHN3_AXI_LP_EN                           BIT(11)
#define BIT_PUB_APB_REG_DDR_CHN2_AXI_LP_EN                           BIT(10)
#define BIT_PUB_APB_REG_DDR_CHN1_AXI_LP_EN                           BIT(9)
#define BIT_PUB_APB_REG_DDR_CHN0_AXI_LP_EN                           BIT(8)
#define BIT_PUB_APB_REG_DDR_CH6_AXI_STOP_SEL                         BIT(6)
#define BIT_PUB_APB_REG_DDR_CH5_AXI_STOP_SEL                         BIT(5)
#define BIT_PUB_APB_REG_DDR_CH4_AXI_STOP_SEL                         BIT(4)
#define BIT_PUB_APB_REG_DDR_CH3_AXI_STOP_SEL                         BIT(3)
#define BIT_PUB_APB_REG_DDR_CH2_AXI_STOP_SEL                         BIT(2)
#define BIT_PUB_APB_REG_DDR_CH1_AXI_STOP_SEL                         BIT(1)
#define BIT_PUB_APB_REG_DDR_CH0_AXI_STOP_SEL                         BIT(0)

/* REG_PUB_APB_REG_DMC_EXT_LPCTRL_CFG */

#define BIT_PUB_APB_REG_SOFT_CMD_NUM(x)                              (((x) & 0x7) << 8)
#define BIT_PUB_APB_REG_SOFT_CMD_FC_SEL(x)                           (((x) & 0x3) << 4)
#define BIT_PUB_APB_REG_SOFT_CMD_RESP                                BIT(3)
#define BIT_PUB_APB_REG_SOFT_CMD_DONE                                BIT(2)
#define BIT_PUB_APB_REG_SOFT_CMD_START                               BIT(0)

/* REG_PUB_APB_REG_DMC_EXT_LPCTRL_SEQL */

#define BIT_PUB_APB_REG_SOFT_CMD_SEQL(x)                             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_DMC_EXT_LPCTRL_SEQH */

#define BIT_PUB_APB_REG_SOFT_CMD_SEQH(x)                             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_DMC_EXT_LPCTRL_STEP */

#define BIT_PUB_APB_REG_SOFT_CMD_STEP(x)                             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_QOS_SELECT */


/* REG_PUB_APB_REG_DPLL_PRE_DIV_STATUS */

#define BIT_PUB_APB_REG_DPLL_PRE_DIV_MONITOR_GATE_AUTO_EN_STATUS(x)  (((x) & 0x3) << 2)
#define BIT_PUB_APB_REG_DPLL_PRE_DIV_MONITOR_WAIT_EN_STATUS(x)       (((x) & 0x3))

/* REG_PUB_APB_REG_DFI_BWMON_TIMER */

#define BIT_PUB_APB_REG_DFI_MON_IDLE_CNT(x)                          (((x) & 0xFF) << 8)
#define BIT_PUB_APB_REG_DFI_MON_TIMER_DELAY(x)                       (((x) & 0xFF))

/* REG_PUB_APB_REG_QOS_SWITCH */

#define BIT_PUB_APB_REG_URGENT_CHN_SEL                               BIT(1)
#define BIT_PUB_APB_REG_QOS_URGENT_SEL                               BIT(0)

/* REG_PUB_APB_REG_PUB_BUS_CK_EB */

#define BIT_PUB_APB_REG_PUB_CLK_PTM_26M_EB                           BIT(12)
#define BIT_PUB_APB_REG_LP_STAT_MTX_CG_EN                            BIT(11)
#define BIT_PUB_APB_REG_CHN_DMC_STOP_CG_EN                           BIT(10)
#define BIT_PUB_APB_REG_TRANS_MON_ENABLE                             BIT(9)
#define BIT_PUB_APB_REG_PUB_CLK_CSSYS_PTM_EB                         BIT(8)
#define BIT_PUB_APB_REG_PUB_APB_PTM_REG_EB                           BIT(7)
#define BIT_PUB_APB_REG_PUB_CLK_DMC_PTM_EB                           BIT(6)
#define BIT_PUB_APB_REG_PUB_APB_INT_EB                               BIT(5)
#define BIT_PUB_APB_REG_PUB_APB_BIST_REG_EB                          BIT(4)
#define BIT_PUB_APB_REG_PUB_AHB_QOSC_REG_EB                          BIT(3)
#define BIT_PUB_APB_REG_PUB_AHB_REG_EB                               BIT(2)
#define BIT_PUB_APB_REG_PUB_AHB_BUS_EB                               BIT(1)
#define BIT_PUB_APB_REG_PUB_PHY_REG_EB                               BIT(0)

/* REG_PUB_APB_REG_AXI_LPC_CTRL_3 */

#define BIT_PUB_APB_REG_CSYSACK_SYNC_SEL_PUB_MERGE_MTX_M0            BIT(29)
#define BIT_PUB_APB_REG_CACTIVE_SYNC_SEL_PUB_MERGE_MTX_M0            BIT(28)
#define BIT_PUB_APB_REG_CSYSACK_SYNC_SEL_PUB_MERGE_MTX_M1            BIT(27)
#define BIT_PUB_APB_REG_CACTIVE_SYNC_SEL_PUB_MERGE_MTX_M1            BIT(26)
#define BIT_PUB_APB_REG_CSYSACK_SYNC_SEL_PUB_MERGE_MTX_M2            BIT(25)
#define BIT_PUB_APB_REG_CACTIVE_SYNC_SEL_PUB_MERGE_MTX_M2            BIT(24)
#define BIT_PUB_APB_REG_CSYSACK_SYNC_SEL_PUB_MERGE_MTX_M3            BIT(23)
#define BIT_PUB_APB_REG_CACTIVE_SYNC_SEL_PUB_MERGE_MTX_M3            BIT(22)
#define BIT_PUB_APB_REG_CSYSACK_SYNC_SEL_PUB_MERGE_MTX_S0            BIT(21)
#define BIT_PUB_APB_REG_CACTIVE_SYNC_SEL_PUB_MERGE_MTX_S0            BIT(20)
#define BIT_PUB_APB_REG_CSYSACK_SYNC_SEL_NRCPU_DDR                   BIT(19)
#define BIT_PUB_APB_REG_CACTIVE_SYNC_SEL_NRCPU_DDR                   BIT(18)
#define BIT_PUB_APB_REG_CSYSACK_SYNC_SEL_NRACC_DDR                   BIT(17)
#define BIT_PUB_APB_REG_CACTIVE_SYNC_SEL_NRACC_DDR                   BIT(16)
#define BIT_PUB_APB_REG_CSYSACK_SYNC_SEL_PSCP_DDR                    BIT(15)
#define BIT_PUB_APB_REG_CACTIVE_SYNC_SEL_PSCP_DDR                    BIT(14)
#define BIT_PUB_APB_REG_CSYSACK_SYNC_SEL_AGCP_DDR                    BIT(13)
#define BIT_PUB_APB_REG_CACTIVE_SYNC_SEL_AGCP_DDR                    BIT(12)
#define BIT_PUB_APB_REG_CSYSACK_SYNC_SEL_PUB_CFG_S4                  BIT(11)
#define BIT_PUB_APB_REG_CACTIVE_SYNC_SEL_PUB_CFG_S4                  BIT(10)
#define BIT_PUB_APB_REG_CSYSACK_SYNC_SEL_PUB_CFG_S3                  BIT(9)
#define BIT_PUB_APB_REG_CACTIVE_SYNC_SEL_PUB_CFG_S3                  BIT(8)
#define BIT_PUB_APB_REG_CSYSACK_SYNC_SEL_PUB_CFG_S2                  BIT(7)
#define BIT_PUB_APB_REG_CACTIVE_SYNC_SEL_PUB_CFG_S2                  BIT(6)
#define BIT_PUB_APB_REG_CSYSACK_SYNC_SEL_PUB_CFG_S1                  BIT(5)
#define BIT_PUB_APB_REG_CACTIVE_SYNC_SEL_PUB_CFG_S1                  BIT(4)
#define BIT_PUB_APB_REG_CSYSACK_SYNC_SEL_PUB_CFG_S0                  BIT(3)
#define BIT_PUB_APB_REG_CACTIVE_SYNC_SEL_PUB_CFG_S0                  BIT(2)
#define BIT_PUB_APB_REG_CSYSACK_SYNC_SEL_PUB_CFG_M0                  BIT(1)
#define BIT_PUB_APB_REG_CACTIVE_SYNC_SEL_PUB_CFG_M0                  BIT(0)

/* REG_PUB_APB_REG_PUB_INT_CG_EN */

#define BIT_PUB_APB_REG_INT_DFS_VOTE_DONE_CG_EN                      BIT(10)
#define BIT_PUB_APB_REG_MEM_FW_PUB_CACTIVE_CG_EN                     BIT(9)
#define BIT_PUB_APB_REG_INT_DMC_MPU_VIO_CG_EN                        BIT(8)
#define BIT_PUB_APB_REG_INT_MEM_FW_CG_EN                             BIT(7)
#define BIT_PUB_APB_REG_INT_DFS_GIVEUP_CG_EN                         BIT(6)
#define BIT_PUB_APB_REG_INT_DFS_DENY_CG_EN                           BIT(5)
#define BIT_PUB_APB_REG_INT_DFS_ERROR_CG_EN                          BIT(4)
#define BIT_PUB_APB_REG_INT_HARDWARE_DFS_EXIT_CG_EN                  BIT(3)
#define BIT_PUB_APB_REG_INT_DFS_COMPLETE_CG_EN                       BIT(2)
#define BIT_PUB_APB_REG_INT_DFI_BUS_MONITOR_CG_EN                    BIT(1)
#define BIT_PUB_APB_REG_INT_REQ_PUB_PTM_CG_EN                        BIT(0)

/* REG_PUB_APB_REG_TIMER_ENABLE */

#define BIT_PUB_APB_REG_PTM_TIMER_EN                                 BIT(3)
#define BIT_PUB_APB_REG_LATMON_TIMER_EN                              BIT(2)
#define BIT_PUB_APB_REG_BWMON_TIMER_EN                               BIT(1)
#define BIT_PUB_APB_REG_DBM_TIMER_EN                                 BIT(0)

/* REG_PUB_APB_REG_VOTE_CTRL */

#define BIT_PUB_APB_REG_BWVOTE_SUB_BWMON_EN                          BIT(30)
#define BIT_PUB_APB_REG_BV_FV_EQUAL_INC_EN                           BIT(29)
#define BIT_PUB_APB_REG_DBM_PERCENT_SEL(x)                           (((x) & 0x7) << 26)
#define BIT_PUB_APB_REG_DFS_VOTE_DMC_REF_AG_EN                       BIT(25)
#define BIT_PUB_APB_REG_DFS_APB_ACCESS_CLK_AUTO_EN                   BIT(24)
#define BIT_PUB_APB_REG_VOTE_CK_OPEN_CNT(x)                          (((x) & 0xFF) << 13)
#define BIT_PUB_APB_REG_TIMING_WINDOW_SEL(x)                         (((x) & 0x7) << 10)
#define BIT_PUB_APB_REG_VOTE_UNIT_TRANS_EN                           BIT(9)
#define BIT_PUB_APB_REG_SW_FORCE_VOTE_MASK_EN                        BIT(8)
#define BIT_PUB_APB_REG_SW_FORCE_VOTE_MASK(x)                        (((x) & 0xFF))

/* REG_PUB_APB_REG_VOTE_STATUS */

#define BIT_PUB_APB_REG_VOTE_TAR_FRQ(x)                              (((x) & 0x7) << 9)
#define BIT_PUB_APB_REG_VOTE_NEXT_STATE(x)                           (((x) & 0xF) << 5)
#define BIT_PUB_APB_REG_VOTE_CUR_STATE(x)                            (((x) & 0xF) << 1)
#define BIT_PUB_APB_REG_VOTE_BW_OVERFLOW                             BIT(0)

/* REG_PUB_APB_REG_DFS_HW_CTRL3 */

#define BIT_PUB_APB_REG_DFS_LOCK_DELAY_EN                            BIT(31)
#define BIT_PUB_APB_REG_REG_DFS_LOCK_DELAY_CNT(x)                    (((x) & 0xF) << 27)
#define BIT_PUB_APB_REG_DFI_MASK_WAIT_LSLP_EN                        BIT(24)
#define BIT_PUB_APB_REG_DFI_MASK_WAIT_TIME_LSLP(x)                   (((x) & 0xFF) << 16)
#define BIT_PUB_APB_REG_DFI_MASK_WAIT_EN                             BIT(8)
#define BIT_PUB_APB_REG_DFI_MASK_WAIT_TIME(x)                        (((x) & 0xFF))

/* REG_PUB_APB_REG_QOS_FIXED_CTRL0 */

#define BIT_PUB_APB_REG_DMC_FIXED_QOS_EN(x)                          (((x) & 0x7F))

/* REG_PUB_APB_REG_QOS_FIXED_CTRL1 */

#define BIT_PUB_APB_REG_DMC_FIXED_ARQOS_CH3(x)                       (((x) & 0xF) << 28)
#define BIT_PUB_APB_REG_DMC_FIXED_AWQOS_CH3(x)                       (((x) & 0xF) << 24)
#define BIT_PUB_APB_REG_DMC_FIXED_ARQOS_CH2(x)                       (((x) & 0xF) << 20)
#define BIT_PUB_APB_REG_DMC_FIXED_AWQOS_CH2(x)                       (((x) & 0xF) << 16)
#define BIT_PUB_APB_REG_DMC_FIXED_ARQOS_CH1(x)                       (((x) & 0xF) << 12)
#define BIT_PUB_APB_REG_DMC_FIXED_AWQOS_CH1(x)                       (((x) & 0xF) << 8)
#define BIT_PUB_APB_REG_DMC_FIXED_ARQOS_CH0(x)                       (((x) & 0xF) << 4)
#define BIT_PUB_APB_REG_DMC_FIXED_AWQOS_CH0(x)                       (((x) & 0xF))

/* REG_PUB_APB_REG_QOS_FIXED_CTRL2 */

#define BIT_PUB_APB_REG_DMC_FIXED_ARQOS_CH6(x)                       (((x) & 0xF) << 20)
#define BIT_PUB_APB_REG_DMC_FIXED_AWQOS_CH6(x)                       (((x) & 0xF) << 16)
#define BIT_PUB_APB_REG_DMC_FIXED_ARQOS_CH5(x)                       (((x) & 0xF) << 12)
#define BIT_PUB_APB_REG_DMC_FIXED_AWQOS_CH5(x)                       (((x) & 0xF) << 8)
#define BIT_PUB_APB_REG_DMC_FIXED_ARQOS_CH4(x)                       (((x) & 0xF) << 4)
#define BIT_PUB_APB_REG_DMC_FIXED_AWQOS_CH4(x)                       (((x) & 0xF))

/* REG_PUB_APB_REG_PUB_AXI_QOS_URGENT_REG_0 */

#define BIT_PUB_APB_REG_ARQOS_URGENT_CH3(x)                          (((x) & 0xF) << 28)
#define BIT_PUB_APB_REG_AWQOS_URGENT_CH3(x)                          (((x) & 0xF) << 24)
#define BIT_PUB_APB_REG_ARQOS_URGENT_CH2(x)                          (((x) & 0xF) << 20)
#define BIT_PUB_APB_REG_AWQOS_URGENT_CH2(x)                          (((x) & 0xF) << 16)
#define BIT_PUB_APB_REG_ARQOS_URGENT_CH1(x)                          (((x) & 0xF) << 12)
#define BIT_PUB_APB_REG_AWQOS_URGENT_CH1(x)                          (((x) & 0xF) << 8)
#define BIT_PUB_APB_REG_ARQOS_URGENT_CH0(x)                          (((x) & 0xF) << 4)
#define BIT_PUB_APB_REG_AWQOS_URGENT_CH0(x)                          (((x) & 0xF))

/* REG_PUB_APB_REG_PUB_AXI_QOS_URGENT_REG_1 */

#define BIT_PUB_APB_REG_ARQOS_URGENT_CH7(x)                          (((x) & 0xF) << 28)
#define BIT_PUB_APB_REG_AWQOS_URGENT_CH7(x)                          (((x) & 0xF) << 24)
#define BIT_PUB_APB_REG_ARQOS_URGENT_CH6(x)                          (((x) & 0xF) << 20)
#define BIT_PUB_APB_REG_AWQOS_URGENT_CH6(x)                          (((x) & 0xF) << 16)
#define BIT_PUB_APB_REG_ARQOS_URGENT_CH5(x)                          (((x) & 0xF) << 12)
#define BIT_PUB_APB_REG_AWQOS_URGENT_CH5(x)                          (((x) & 0xF) << 8)
#define BIT_PUB_APB_REG_ARQOS_URGENT_CH4(x)                          (((x) & 0xF) << 4)
#define BIT_PUB_APB_REG_AWQOS_URGENT_CH4(x)                          (((x) & 0xF))

/* REG_PUB_APB_REG_PUB_INT_CTRL */

#define BIT_PUB_APB_REG_DFS_VOTE_DONE_INT_CLR                        BIT(15)
#define BIT_PUB_APB_REG_DFS_VOTE_DONE_INT_EN                         BIT(14)
#define BIT_PUB_APB_REG_DFS_GIVEUP_INT_CLR                           BIT(13)
#define BIT_PUB_APB_REG_DFS_GIVEUP_INT_EN                            BIT(12)
#define BIT_PUB_APB_REG_DFS_DENY_INT_CLR                             BIT(11)
#define BIT_PUB_APB_REG_DFS_DENY_INT_EN                              BIT(10)
#define BIT_PUB_APB_REG_DMC_MPU_VIO_INT_CLR                          BIT(9)
#define BIT_PUB_APB_REG_DMC_MPU_VIO_INT_EN                           BIT(8)
#define BIT_PUB_APB_REG_MEM_FW_INT_CLR                               BIT(7)
#define BIT_PUB_APB_REG_MEM_FW_INT_EN                                BIT(6)
#define BIT_PUB_APB_REG_DFS_ERROR_INT_CLR                            BIT(5)
#define BIT_PUB_APB_REG_DFS_ERROR_INT_EN                             BIT(4)
#define BIT_PUB_APB_REG_DFS_COMPLETE_INT_CLR                         BIT(3)
#define BIT_PUB_APB_REG_DFS_COMPLETE_INT_EN                          BIT(2)
#define BIT_PUB_APB_REG_HW_DFS_EXIT_INT_CLR                          BIT(1)
#define BIT_PUB_APB_REG_HW_DFS_EXIT_INT_EN                           BIT(0)

/* REG_PUB_APB_REG_DFS_STATUS */

#define BIT_PUB_APB_REG_DFS_HW_MIN_FREQ_UP_FORCE_TRIG_ACK            BIT(30)
#define BIT_PUB_APB_REG_DFS_USED_PLL(x)                              (((x) & 0x7) << 27)
#define BIT_PUB_APB_REG_DFS_FC_SEL(x)                                (((x) & 0x7) << 24)
#define BIT_PUB_APB_REG_SRC_AVAIL_PLL(x)                             (((x) & 0x7) << 21)
#define BIT_PUB_APB_REG_DFS_URGENT_WAIT_TIMEOUT_FLAG                 BIT(20)
#define BIT_PUB_APB_REG_DFS_GIVEUP_INT_RAW                           BIT(19)
#define BIT_PUB_APB_REG_INT_DFS_GIVEUP                               BIT(18)
#define BIT_PUB_APB_REG_DFS_DENY_INT_RAW                             BIT(17)
#define BIT_PUB_APB_REG_INT_DFS_DENY                                 BIT(16)
#define BIT_PUB_APB_REG_HW_DFS_FSM_STATE(x)                          (((x) & 0x1F) << 11)
#define BIT_PUB_APB_REG_HW_DFS_FSM_IDLE                              BIT(10)
#define BIT_PUB_APB_REG_INT_DMC_MPU_VIO_RAW                          BIT(9)
#define BIT_PUB_APB_REG_INT_DMC_MPU_VIO                              BIT(8)
#define BIT_PUB_APB_REG_INT_MEM_FW_RAW                               BIT(7)
#define BIT_PUB_APB_REG_INT_MEM_FW                                   BIT(6)
#define BIT_PUB_APB_REG_DFS_ERROR_INT_RAW                            BIT(5)
#define BIT_PUB_APB_REG_INT_DFS_ERROR                                BIT(4)
#define BIT_PUB_APB_REG_DFS_COMPLETE_INT_RAW                         BIT(3)
#define BIT_PUB_APB_REG_INT_DFS_COMPLETE                             BIT(2)
#define BIT_PUB_APB_REG_HW_DFS_EXIT_INT_RAW                          BIT(1)
#define BIT_PUB_APB_REG_INT_HW_DFS_EXIT                              BIT(0)

/* REG_PUB_APB_REG_DFS_STATUS1 */

#define BIT_PUB_APB_REG_DFS_SW_FSM_STATE(x)                          (((x) & 0x7) << 4)
#define BIT_PUB_APB_REG_DFS_VOTE_DONE_INT_RAW                        BIT(1)
#define BIT_PUB_APB_REG_INT_DFS_VOTE_DONE                            BIT(0)

/* REG_PUB_APB_REG_DFS_FC_REQ_DELAY */

#define BIT_PUB_APB_REG_DFS_FC_REQ_DELAY(x)                          (((x) & 0x7))

/* REG_PUB_APB_REG_PUB_LP_GEN_CTRL */

#define BIT_PUB_APB_REG_DFS_SW_MODE                                  BIT(6)
#define BIT_PUB_APB_REG_HW_DFS_STOP_ENABLE                           BIT(5)
#define BIT_PUB_APB_REG_HW_DFS_RESTART_ENABLE                        BIT(4)
#define BIT_PUB_APB_REG_AUTO_STOP_NOC_ENABLE                         BIT(3)
#define BIT_PUB_APB_REG_AUTO_STOP_DFS_ENABLE                         BIT(2)
#define BIT_PUB_APB_REG_PUB_DFS_EN                                   BIT(1)
#define BIT_PUB_APB_REG_PUB_LP_EN                                    BIT(0)

/* REG_PUB_APB_REG_AXI_LPC_CTRL_0 */

#define BIT_PUB_APB_REG_CSYSACK_SYNC_SEL_WTL_AG_S0                   BIT(15)
#define BIT_PUB_APB_REG_CACTIVE_SYNC_SEL_WTL_AG_S0                   BIT(14)
#define BIT_PUB_APB_REG_CSYSACK_SYNC_SEL_WTL_AG_M1                   BIT(13)
#define BIT_PUB_APB_REG_CACTIVE_SYNC_SEL_WTL_AG_M1                   BIT(12)
#define BIT_PUB_APB_REG_CSYSACK_SYNC_SEL_WTL_AG_M0                   BIT(11)
#define BIT_PUB_APB_REG_CACTIVE_SYNC_SEL_WTL_AG_M0                   BIT(10)
#define BIT_PUB_APB_REG_LP_FORCE_ISP_VDSP_S0                         BIT(5)
#define BIT_PUB_APB_REG_LP_EB_ISP_VDSP_S0                            BIT(4)
#define BIT_PUB_APB_REG_LP_FORCE_ISP_VDSP_M1                         BIT(3)
#define BIT_PUB_APB_REG_LP_EB_ISP_VDSP_M1                            BIT(2)
#define BIT_PUB_APB_REG_LP_FORCE_ISP_VDSP_M0                         BIT(1)
#define BIT_PUB_APB_REG_LP_EB_ISP_VDSP_M0                            BIT(0)

/* REG_PUB_APB_REG_AXI_LPC_CTRL_1 */

#define BIT_PUB_APB_REG_LP_FORCE_PUB_CFG_S4                          BIT(29)
#define BIT_PUB_APB_REG_LP_EB_PUB_CFG_S4                             BIT(28)
#define BIT_PUB_APB_REG_LP_FORCE_PUB_CFG_S3                          BIT(27)
#define BIT_PUB_APB_REG_LP_EB_PUB_CFG_S3                             BIT(26)
#define BIT_PUB_APB_REG_LP_FORCE_PUB_CFG_S2                          BIT(25)
#define BIT_PUB_APB_REG_LP_EB_PUB_CFG_S2                             BIT(24)
#define BIT_PUB_APB_REG_LP_FORCE_PUB_CFG_S1                          BIT(23)
#define BIT_PUB_APB_REG_LP_EB_PUB_CFG_S1                             BIT(22)
#define BIT_PUB_APB_REG_LP_FORCE_PUB_CFG_S0                          BIT(21)
#define BIT_PUB_APB_REG_LP_EB_PUB_CFG_S0                             BIT(20)
#define BIT_PUB_APB_REG_LP_FORCE_PUB_CFG_M0                          BIT(19)
#define BIT_PUB_APB_REG_LP_EB_PUB_CFG_M0                             BIT(18)
#define BIT_PUB_APB_REG_LP_FORCE_PUB_MERGE_MTX_M0                    BIT(17)
#define BIT_PUB_APB_REG_LP_EB_MERGE_MTX_M0                           BIT(16)
#define BIT_PUB_APB_REG_LP_FORCE_PUB_MERGE_MTX_M1                    BIT(15)
#define BIT_PUB_APB_REG_LP_EB_MERGE_MTX_M1                           BIT(14)
#define BIT_PUB_APB_REG_LP_FORCE_PUB_MERGE_MTX_M2                    BIT(13)
#define BIT_PUB_APB_REG_LP_EB_MERGE_MTX_M2                           BIT(12)
#define BIT_PUB_APB_REG_LP_FORCE_PUB_MERGE_MTX_M3                    BIT(11)
#define BIT_PUB_APB_REG_LP_EB_MERGE_MTX_M3                           BIT(10)
#define BIT_PUB_APB_REG_LP_FORCE_PUB_MERGE_MTX_S0                    BIT(9)
#define BIT_PUB_APB_REG_LP_EB_MERGE_MTX_S0                           BIT(8)
#define BIT_PUB_APB_REG_LP_FORCE_NRCPU_DDR                           BIT(7)
#define BIT_PUB_APB_REG_LP_EB_NRCPU_DDR                              BIT(6)
#define BIT_PUB_APB_REG_LP_FORCE_NRACC_DDR                           BIT(5)
#define BIT_PUB_APB_REG_LP_EB_NRACC_DDR                              BIT(4)
#define BIT_PUB_APB_REG_LP_FORCE_PSCP_DDR                            BIT(3)
#define BIT_PUB_APB_REG_LP_EB_PSCP_DDR                               BIT(2)
#define BIT_PUB_APB_REG_LP_FORCE_AGCP_DDR                            BIT(1)
#define BIT_PUB_APB_REG_LP_EB_AGCP_DDR                               BIT(0)

/* REG_PUB_APB_REG_AXI_LPC_CTRL_2 */

#define BIT_PUB_APB_REG_LP_NUM_PUB_CFG(x)                            (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_REG_LP_NUM_DDR(x)                                (((x) & 0xFFFF))

/* REG_PUB_APB_REG_FENCING_CTRL */

#define BIT_PUB_APB_REG_PUB_CLK_DDR_EN_BY_FENCING_RELEASE            BIT(31)
#define BIT_PUB_APB_REG_DDR_FENCING_EN                               BIT(30)
#define BIT_PUB_APB_REG_FENCING_CHNL_IDLE_CNT(x)                     (((x) & 0x3FFFFFFF))

/* REG_PUB_APB_REG_CP_BASE_ADDR */

#define BIT_PUB_APB_REG_NRCPU_BASE_ADDR(x)                           (((x) & 0xF) << 20)
#define BIT_PUB_APB_REG_NRACC_BASE_ADDR(x)                           (((x) & 0xF) << 16)
#define BIT_PUB_APB_REG_V3CPU_BASE_ADDR(x)                           (((x) & 0xF) << 12)
#define BIT_PUB_APB_REG_V3ACC_BASE_ADDR(x)                           (((x) & 0xF) << 8)
#define BIT_PUB_APB_REG_PSCP_BASE_ADDR(x)                            (((x) & 0xF) << 4)
#define BIT_PUB_APB_REG_AGCP_BASE_ADDR(x)                            (((x) & 0xF))

/* REG_PUB_APB_REG_CLK_PUB_DFS_CTRL */

#define BIT_PUB_APB_REG_LP_WAIT_CGM_BUSY_SEL                         BIT(2)
#define BIT_PUB_APB_REG_CGM_PUB_DFS_SEL                              BIT(1)
#define BIT_PUB_APB_REG_CGM_PUB_DFS_EN                               BIT(0)

/* REG_PUB_APB_REG_AXI_LPC_CTRL_4 */

#define BIT_PUB_APB_REG_LP_NUM_MERGE_MTX_M3(x)                       (((x) & 0xFFFF))

/* REG_PUB_APB_REG_AXI_LPC_CTRL_5 */

#define BIT_PUB_APB_REG_LP_NUM_MERGE_MTX_M2(x)                       (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_REG_LP_NUM_MERGE_MTX_M1(x)                       (((x) & 0xFFFF))

/* REG_PUB_APB_REG_BIST_CTRL */

#define BIT_PUB_APB_REG_BIST_FAIL_FLAG_CH3                           BIT(11)
#define BIT_PUB_APB_REG_BIST_FAIL_FLAG_CH2                           BIT(10)
#define BIT_PUB_APB_REG_BIST_FAIL_FLAG_CH1                           BIT(9)
#define BIT_PUB_APB_REG_BIST_FAIL_FLAG_CH0                           BIT(8)
#define BIT_PUB_APB_REG_BIST_PORT6_EN                                BIT(6)
#define BIT_PUB_APB_REG_BIST_PORT5_EN                                BIT(5)
#define BIT_PUB_APB_REG_BIST_PORT4_EN                                BIT(4)
#define BIT_PUB_APB_REG_BIST_PORT3_EN                                BIT(3)
#define BIT_PUB_APB_REG_BIST_PORT2_EN                                BIT(2)
#define BIT_PUB_APB_REG_BIST_PORT1_EN                                BIT(1)
#define BIT_PUB_APB_REG_BIST_PORT0_EN                                BIT(0)

/* REG_PUB_APB_REG_DMC_SOFT_RST_CTRL */

#define BIT_PUB_APB_REG_DMC_SOFT_RST                                 BIT(2)
#define BIT_PUB_APB_REG_DCC_SOFT_RST                                 BIT(1)
#define BIT_PUB_APB_REG_DDRPHY_SOFT_RST                              BIT(0)

/* REG_PUB_APB_REG_MC_IDLE_WAIT_CTRL */

#define BIT_PUB_APB_REG_MC_IDLE_WAIT_CTRL(x)                         (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_QOS_THRESHOLD_0 */

#define BIT_PUB_APB_REG_AWQOS_THRESHOLD_WTL_AG(x)                    (((x) & 0xF) << 28)
#define BIT_PUB_APB_REG_ARQOS_THRESHOLD_WTL_AG(x)                    (((x) & 0xF) << 24)
#define BIT_PUB_APB_REG_AWQOS_THRESHOLD_DPU_ISP(x)                   (((x) & 0xF) << 20)
#define BIT_PUB_APB_REG_ARQOS_THRESHOLD_DPU_ISP(x)                   (((x) & 0xF) << 16)
#define BIT_PUB_APB_REG_AWQOS_THRESHOLD_AP_AON(x)                    (((x) & 0xF) << 12)
#define BIT_PUB_APB_REG_ARQOS_THRESHOLD_AP_AON(x)                    (((x) & 0xF) << 8)
#define BIT_PUB_APB_REG_AON_AWQOS(x)                                 (((x) & 0xF) << 4)
#define BIT_PUB_APB_REG_AON_ARQOS(x)                                 (((x) & 0xF))

/* REG_PUB_APB_REG_QOS_THRESHOLD_1 */

#define BIT_PUB_APB_REG_AWQOS_THRESHOLD_ISP_VDSP(x)                  (((x) & 0xF) << 4)
#define BIT_PUB_APB_REG_ARQOS_THRESHOLD_ISP_VDSP(x)                  (((x) & 0xF))

/* REG_PUB_APB_REG_DMC_DDR_CLK_CTRL */

#define BIT_PUB_APB_REG_PUB_CLK_DFS_SLEEP_AUTO_GATE_EN               BIT(31)
#define BIT_PUB_APB_REG_CLK_AON_APB_AUTO_GATE_EN                     BIT(30)
#define BIT_PUB_APB_REG_CLK_DMC_REF_AUTO_GATE_EN                     BIT(29)
#define BIT_PUB_APB_REG_PUB_CLK_DFS_AUTO_GATE_EN                     BIT(28)
#define BIT_PUB_APB_REG_DMC_DFI_MON_AUTO_GATE_EN                     BIT(27)
#define BIT_PUB_APB_REG_DMC_SREF_AUTO_GATE_EN                        BIT(26)
#define BIT_PUB_APB_REG_DDR_PHY_AUTO_GATE_EN                         BIT(25)
#define BIT_PUB_APB_REG_DDR_UMCTL_AUTO_GATE_EN                       BIT(24)
#define BIT_PUB_APB_REG_PUB_CLK_DMC_BIST_EB                          BIT(23)
#define BIT_PUB_APB_REG_PUB_CLK_DMC_REF_EB                           BIT(22)
#define BIT_PUB_APB_REG_PUB_CLK_CSSYS_EB                             BIT(21)
#define BIT_PUB_APB_REG_PUB_CLK_AON_APB_EB                           BIT(20)
#define BIT_PUB_APB_REG_PUB_CLK_PHY_X2_FORCE_PHASE(x)                (((x) & 0x3) << 18)
#define BIT_PUB_APB_REG_PUB_CLK_PHY_X2_FORCE_PHASE_SEL               BIT(17)
#define BIT_PUB_APB_REG_PUB_CLK_PHY_X2_FORCE_BYP                     BIT(16)
#define BIT_PUB_APB_REG_PUB_CLK_DFS_EB                               BIT(15)
#define BIT_PUB_APB_REG_PUB_CLK_DMC_X1_PTM_EB                        BIT(14)
#define BIT_PUB_APB_REG_PUB_CLK_MLB_D2_EB                            BIT(13)
#define BIT_PUB_APB_REG_PUB_CLK_DMC_D2_EB                            BIT(12)
#define BIT_PUB_APB_REG_PUB_CLK_DMC_X1_EB                            BIT(11)
#define BIT_PUB_APB_REG_PUB_CLK_PHY_X2_EB                            BIT(10)
#define BIT_PUB_APB_REG_PUB_CLK_DCC_EB                               BIT(9)
#define BIT_PUB_APB_REG_PUB_DDR_CLK_EB                               BIT(8)
#define BIT_PUB_APB_REG_TIMER_CLK_AON_APB_OPEN_EN                    BIT(7)
#define BIT_PUB_APB_REG_PUB_CLK_DMC_X1_PTM_AUTO_GATE_EN              BIT(6)
#define BIT_PUB_APB_REG_PUB_CLK_MLB_D2_CGM_SEL                       BIT(5)
#define BIT_PUB_APB_REG_PUB_CLK_DMC_D2_CGM_SEL                       BIT(4)
#define BIT_PUB_APB_REG_PUB_CLK_DMC_X1_CGM_SEL                       BIT(3)
#define BIT_PUB_APB_REG_PUB_CLK_PHY_X2_CGM_SEL                       BIT(2)
#define BIT_PUB_APB_REG_PUB_CLK_DCC_CGM_SEL                          BIT(1)
#define BIT_PUB_APB_REG_PUB_DDR_CLK_CGM_SEL                          BIT(0)

/* REG_PUB_APB_REG_DMC_CLK_INIT_SW_START */

#define BIT_PUB_APB_REG_DMC_CLK_INIT_SW_START                        BIT(0)

/* REG_PUB_APB_REG_DMC_CLK_STATE */

#define BIT_PUB_APB_REG_DFS_LP_CTRL_CUR_STATE(x)                     (((x) & 0x7) << 12)
#define BIT_PUB_APB_REG_DMC_CLK_HW_CUR_STATE(x)                      (((x) & 0xF) << 4)
#define BIT_PUB_APB_REG_DMC_CUR_CLK_MODE(x)                          (((x) & 0x3) << 2)
#define BIT_PUB_APB_REG_DMC_CLK_INIT_SW_DONE                         BIT(0)

/* REG_PUB_APB_REG_DMC_CLK_INIT_CFG */

#define BIT_PUB_APB_REG_PTM_LSLP_CLK_KEEP_ON_EN                      BIT(25)
#define BIT_PUB_APB_REG_DMC_DFI_MON_LSLP_AG_EN                       BIT(24)
#define BIT_PUB_APB_REG_DMC_STOP_WAIT_CNT(x)                         (((x) & 0xFF) << 16)
#define BIT_PUB_APB_REG_DMC_SLEEP_FORCE_FINISH_MODE                  BIT(8)
#define BIT_PUB_APB_REG_DESKEW_PLL_PD_DEFAULT_SW                     BIT(5)
#define BIT_PUB_APB_REG_DESKEW_PLL_PD_DEFAULT_SEL                    BIT(4)
#define BIT_PUB_APB_REG_DMC_SLEEP_CLK_AUTO_MODE                      BIT(1)
#define BIT_PUB_APB_REG_DFS_CLK_AUTO_MODE                            BIT(0)

/* REG_PUB_APB_REG_DMC_DESKEW_WAIT_CFG */

#define BIT_PUB_APB_REG_DSKDLL_DCC_FINE_WAIT_SRC_SW                  BIT(10)
#define BIT_PUB_APB_REG_DSKDLL_DCC_COARSE_WAIT_SRC_SW                BIT(9)
#define BIT_PUB_APB_REG_DSKPLL_LOCK_WAIT_SRC_SW                      BIT(8)
#define BIT_PUB_APB_REG_DDL_ADJS_V_WAIT_EN                           BIT(3)
#define BIT_PUB_APB_REG_DSKDLL_DCC_FINE_WAIT_EN                      BIT(2)
#define BIT_PUB_APB_REG_DSKDLL_DCC_COARSE_WAIT_EN                    BIT(1)
#define BIT_PUB_APB_REG_DSKPLL_LOCK_WAIT_EN                          BIT(0)

/* REG_PUB_APB_REG_DMC_DESKEW_WAIT_CNT0 */

#define BIT_PUB_APB_REG_WAIT_CNT_DSKPLL_PWRON_TIME(x)                (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_REG_WAIT_CNT_DSKPLL_LOCK_TIME(x)                 (((x) & 0xFFFF))

/* REG_PUB_APB_REG_DMC_DESKEW_WAIT_CNT1 */

#define BIT_PUB_APB_REG_WAIT_CNT_DSKDLL_DCC_FINE_TIME(x)             (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_REG_WAIT_CNT_DSKDLL_DCC_COARSE_TIME(x)           (((x) & 0xFFFF))

/* REG_PUB_APB_REG_DMC_DESKEW_WAIT_CNT2 */

#define BIT_PUB_APB_REG_WAIT_CNT_DFS_RESET_OFF_TIME(x)               (((x) & 0xFF) << 24)
#define BIT_PUB_APB_REG_WAIT_CNT_DFS_RESET_ON_TIME(x)                (((x) & 0xFF) << 16)
#define BIT_PUB_APB_REG_WAIT_CNT_DFS_CLK_OFF_TIME(x)                 (((x) & 0xFF))

/* REG_PUB_APB_REG_DMC_DESKEW_WAIT_CNT3 */

#define BIT_PUB_APB_REG_WAIT_CNT_DDL_ADJS_V_HIGH_TIME(x)             (((x) & 0xFF) << 16)
#define BIT_PUB_APB_REG_WAIT_CNT_DDL_ADJS_V_LOW_TIME(x)              (((x) & 0xFF))

/* REG_PUB_APB_REG_DMC_DDL_CTRL */

#define BIT_PUB_APB_REG_PTEST_DDL_SCOUT                              BIT(26)
#define BIT_PUB_APB_REG_PTEST_DDL_SCIN                               BIT(25)
#define BIT_PUB_APB_REG_PTEST_DDL_SE                                 BIT(24)
#define BIT_PUB_APB_REG_DMC_DDL_SW_ADJS(x)                           (((x) & 0x1FF) << 8)
#define BIT_PUB_APB_REG_DMC_DDL_SW_UPDATE                            BIT(7)
#define BIT_PUB_APB_REG_DMC_DDL_SW_BYPASS                            BIT(6)
#define BIT_PUB_APB_REG_DMC_DDL_SW_RESET                             BIT(5)
#define BIT_PUB_APB_REG_DMC_DDL_SW_ADJS_VALID                        BIT(4)
#define BIT_PUB_APB_REG_DMC_DDL_CFG_SRC_PURE_SW                      BIT(1)
#define BIT_PUB_APB_REG_DMC_DDL_CFG_SRC_SW                           BIT(0)

/* REG_PUB_APB_REG_DFS_PURE_SW_CTRL */

#define BIT_PUB_APB_REG_PUB_DFS_SW_LOCK_REQ                          BIT(27)
#define BIT_PUB_APB_REG_PUB_DFS_SW_LOCK_MODE                         BIT(26)
#define BIT_PUB_APB_REG_EMC_CKG_MODE_PURE_SW(x)                      (((x) & 0x3) << 24)
#define BIT_PUB_APB_REG_EMC_CKG_D2_SEL_PURE_SW(x)                    (((x) & 0xF) << 20)
#define BIT_PUB_APB_REG_PURE_SW_DFS_CLK_MODE(x)                      (((x) & 0x3) << 18)
#define BIT_PUB_APB_REG_PURE_SW_DFS_DENY                             BIT(16)
#define BIT_PUB_APB_REG_PURE_SW_DFS_ACK                              BIT(15)
#define BIT_PUB_APB_REG_PURE_SW_DFS_RESP                             BIT(14)
#define BIT_PUB_APB_REG_PURE_SW_DFS_FC_REQ                           BIT(13)
#define BIT_PUB_APB_REG_PURE_SW_DFS_REQ                              BIT(12)
#define BIT_PUB_APB_REG_PURE_SW_DFS_FC_ACK                           BIT(11)
#define BIT_PUB_APB_REG_PURE_SW_DFS_FRQ_SEL(x)                       (((x) & 0x7) << 8)
#define BIT_PUB_APB_REG_EMC_CKG_SEL_PURE_SW(x)                       (((x) & 0x7F) << 1)
#define BIT_PUB_APB_REG_DFS_SW_DFS_MODE                              BIT(0)

/* REG_PUB_APB_REG_DFS_SW_CTRL */

#define BIT_PUB_APB_REG_PUB_DFS_SWITCH_TYPE                          BIT(31)
#define BIT_PUB_APB_REG_PUB_DFS_SW_SWITCH_PERIOD(x)                  (((x) & 0xFF) << 22)
#define BIT_PUB_APB_REG_PUB_DFS_SW_RATIO_DEFAULT(x)                  (((x) & 0x7F) << 15)
#define BIT_PUB_APB_REG_PUB_DFS_SW_RATIO(x)                          (((x) & 0x7F) << 8)
#define BIT_PUB_APB_REG_PUB_DFS_SW_DENY                              BIT(7)
#define BIT_PUB_APB_REG_PUB_DFS_SW_FRQ_SEL(x)                        (((x) & 0x7) << 4)
#define BIT_PUB_APB_REG_PUB_DFS_SW_RESP                              BIT(3)
#define BIT_PUB_APB_REG_PUB_DFS_SW_ACK                               BIT(2)
#define BIT_PUB_APB_REG_PUB_DFS_SW_REQ                               BIT(1)
#define BIT_PUB_APB_REG_PUB_DFS_SW_ENABLE                            BIT(0)

/* REG_PUB_APB_REG_DFS_SW_CTRL1 */

#define BIT_PUB_APB_REG_PUB_DFS_SW_UG_DENY_EN                        BIT(22)
#define BIT_PUB_APB_REG_PUB_DFS_SW_LP_DENY_EN                        BIT(21)
#define BIT_PUB_APB_REG_PUB_DFS_SW_UG_CHK_EN                         BIT(20)
#define BIT_PUB_APB_REG_PUB_DFS_SW_CLK_MODE_DEFAULT(x)               (((x) & 0x3) << 18)
#define BIT_PUB_APB_REG_PUB_DFS_SW_CLK_MODE(x)                       (((x) & 0x3) << 16)
#define BIT_PUB_APB_REG_PUB_DFS_SW_RATIO_D2_DEFAULT(x)               (((x) & 0xF) << 8)
#define BIT_PUB_APB_REG_PUB_DFS_SW_RATIO_D2(x)                       (((x) & 0xF))

/* REG_PUB_APB_REG_DFS_SW_CTRL2 */

#define BIT_PUB_APB_REG_PUB_DFS_SW_DDL_ADJS_DEFAULT(x)               (((x) & 0x1FF) << 16)
#define BIT_PUB_APB_REG_PUB_DFS_SW_DDL_ADJS(x)                       (((x) & 0x1FF))

/* REG_PUB_APB_REG_DFS_SW_CTRL3 */

#define BIT_PUB_APB_REG_PUB_DFS_URGENT_WAIT_TIMEOUT_PERIOD(x)        (((x) & 0x3FF) << 18)
#define BIT_PUB_APB_REG_PUB_DFS_URGENT_WAIT_TIMEOUT_EN               BIT(17)
#define BIT_PUB_APB_REG_PUB_DFS_SW_URGENT_WAIT_EN                    BIT(16)
#define BIT_PUB_APB_REG_PUB_DFS_SW_URGENT_DENY_EN(x)                 (((x) & 0xFFFF))

/* REG_PUB_APB_REG_DFS_HW_CTRL */

#define BIT_PUB_APB_REG_PUB_DFS_HW_DDL_ADJS_DEFAULT(x)               (((x) & 0x1FF) << 22)
#define BIT_PUB_APB_REG_PUB_DFS_HW_CLK_MODE_DEFAULT(x)               (((x) & 0x3) << 20)
#define BIT_PUB_APB_REG_PUB_DFS_HW_RATIO_D2_DEFAULT(x)               (((x) & 0xF) << 16)
#define BIT_PUB_APB_REG_PUB_DFS_HW_RATIO_DEFAULT(x)                  (((x) & 0x7F) << 8)
#define BIT_PUB_APB_REG_PUB_DFS_HW_INITIAL_FREQ(x)                   (((x) & 0x7) << 4)
#define BIT_PUB_APB_REG_PUB_DFS_HW_STOP                              BIT(2)
#define BIT_PUB_APB_REG_PUB_DFS_HW_START                             BIT(1)
#define BIT_PUB_APB_REG_PUB_DFS_HW_ENABLE                            BIT(0)

/* REG_PUB_APB_REG_DFS_HW_CTRL1 */

#define BIT_PUB_APB_REG_SW_FORCE_EXIT_SW_LP_WAIT_ACK                 BIT(31)
#define BIT_PUB_APB_REG_SW_FORCE_EXIT_HW_LP_WAIT_ACK                 BIT(30)
#define BIT_PUB_APB_REG_SW_FORCE_EXIT_LP_WAIT_REQ                    BIT(29)
#define BIT_PUB_APB_REG_PUB_DFS_HW_MIN_FREQ_UP_FORCE_TRIG            BIT(28)
#define BIT_PUB_APB_REG_PUB_DFS_HW_BWMON_MIN_EN                      BIT(27)
#define BIT_PUB_APB_REG_PUB_DFS_HW_BWMON_MIN_FREQ(x)                 (((x) & 0x7) << 24)
#define BIT_PUB_APB_REG_PUB_DFS_HW_AVAIL_FREQ_EN(x)                  (((x) & 0xFF) << 16)
#define BIT_PUB_APB_REG_PUB_DFS_HW_CHECK_PLL_EN                      BIT(12)
#define BIT_PUB_APB_REG_PUB_DFS_HW_MIN_FREQ_UP(x)                    (((x) & 0x7) << 8)
#define BIT_PUB_APB_REG_PUB_DFS_HW_MIN_FREQ_DN(x)                    (((x) & 0x7) << 4)
#define BIT_PUB_APB_REG_PUB_DFS_HW_MIN_EN_UP                         BIT(3)
#define BIT_PUB_APB_REG_PUB_DFS_HW_MIN_EN_DN                         BIT(2)
#define BIT_PUB_APB_REG_PUB_DFS_HW_MIN_LOAD                          BIT(1)
#define BIT_PUB_APB_REG_PUB_DFS_LP_PROT_EN                           BIT(0)

/* REG_PUB_APB_REG_DFS_HW_CTRL2 */

#define BIT_PUB_APB_REG_DFS_INC_REQ_HOLD_EN                          BIT(31)
#define BIT_PUB_APB_REG_DFS_DEC_TO_INC_EN                            BIT(30)
#define BIT_PUB_APB_REG_PUB_DFS_HW_DEC_UG_DENY_EN                    BIT(29)
#define BIT_PUB_APB_REG_PUB_DFS_HW_INC_UG_DENY_EN                    BIT(28)
#define BIT_PUB_APB_REG_PUB_DFS_HW_DEC_LP_DENY_EN                    BIT(27)
#define BIT_PUB_APB_REG_PUB_DFS_HW_INC_LP_DENY_EN                    BIT(26)
#define BIT_PUB_APB_REG_PUB_DFS_HW_DEC_UG_CHK_EN                     BIT(25)
#define BIT_PUB_APB_REG_PUB_DFS_HW_INC_UG_CHK_EN                     BIT(24)
#define BIT_PUB_APB_REG_PUB_DFS_HW_URGENT_WAIT_EN                    BIT(16)
#define BIT_PUB_APB_REG_PUB_DFS_HW_URGENT_DENY_EN(x)                 (((x) & 0xFFFF))

/* REG_PUB_APB_REG_DFS_HW_RATIO_SET0 */

#define BIT_PUB_APB_REG_PUB_DFS_HW_F3_RATIO(x)                       (((x) & 0x7F) << 24)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F2_RATIO(x)                       (((x) & 0x7F) << 16)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F1_RATIO(x)                       (((x) & 0x7F) << 8)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F0_RATIO(x)                       (((x) & 0x7F))

/* REG_PUB_APB_REG_DFS_HW_RATIO_SET1 */

#define BIT_PUB_APB_REG_PUB_DFS_HW_F7_RATIO(x)                       (((x) & 0x7F) << 24)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F6_RATIO(x)                       (((x) & 0x7F) << 16)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F5_RATIO(x)                       (((x) & 0x7F) << 8)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F4_RATIO(x)                       (((x) & 0x7F))

/* REG_PUB_APB_REG_DFS_HW_RATIO_SET2 */

#define BIT_PUB_APB_REG_PUB_DFS_HW_F7_RATIO_D2(x)                    (((x) & 0xF) << 28)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F6_RATIO_D2(x)                    (((x) & 0xF) << 24)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F5_RATIO_D2(x)                    (((x) & 0xF) << 20)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F4_RATIO_D2(x)                    (((x) & 0xF) << 16)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F3_RATIO_D2(x)                    (((x) & 0xF) << 12)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F2_RATIO_D2(x)                    (((x) & 0xF) << 8)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F1_RATIO_D2(x)                    (((x) & 0xF) << 4)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F0_RATIO_D2(x)                    (((x) & 0xF))

/* REG_PUB_APB_REG_DFS_HW_RATIO_SET3 */

#define BIT_PUB_APB_REG_PUB_DFS_HW_F7_CLK_MODE(x)                    (((x) & 0x3) << 14)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F6_CLK_MODE(x)                    (((x) & 0x3) << 12)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F5_CLK_MODE(x)                    (((x) & 0x3) << 10)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F4_CLK_MODE(x)                    (((x) & 0x3) << 8)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F3_CLK_MODE(x)                    (((x) & 0x3) << 6)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F2_CLK_MODE(x)                    (((x) & 0x3) << 4)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F1_CLK_MODE(x)                    (((x) & 0x3) << 2)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F0_CLK_MODE(x)                    (((x) & 0x3))

/* REG_PUB_APB_REG_DFS_HW_RATIO_SET4 */

#define BIT_PUB_APB_REG_PUB_DFS_HW_F1_DDL_ADJS(x)                    (((x) & 0x1FF) << 16)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F0_DDL_ADJS(x)                    (((x) & 0x1FF))

/* REG_PUB_APB_REG_DFS_HW_RATIO_SET5 */

#define BIT_PUB_APB_REG_PUB_DFS_HW_F3_DDL_ADJS(x)                    (((x) & 0x1FF) << 16)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F2_DDL_ADJS(x)                    (((x) & 0x1FF))

/* REG_PUB_APB_REG_DFS_HW_RATIO_SET6 */

#define BIT_PUB_APB_REG_PUB_DFS_HW_F5_DDL_ADJS(x)                    (((x) & 0x1FF) << 16)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F4_DDL_ADJS(x)                    (((x) & 0x1FF))

/* REG_PUB_APB_REG_DFS_HW_RATIO_SET7 */

#define BIT_PUB_APB_REG_PUB_DFS_HW_F7_DDL_ADJS(x)                    (((x) & 0x1FF) << 16)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F6_DDL_ADJS(x)                    (((x) & 0x1FF))

/* REG_PUB_APB_REG_DFS_HW_RATIO_SET8 */

#define BIT_PUB_APB_REG_PUB_DFS_HW_F7_REQ_DURATION(x)                (((x) & 0xF) << 28)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F6_REQ_DURATION(x)                (((x) & 0xF) << 24)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F5_REQ_DURATION(x)                (((x) & 0xF) << 20)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F4_REQ_DURATION(x)                (((x) & 0xF) << 16)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F3_REQ_DURATION(x)                (((x) & 0xF) << 12)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F2_REQ_DURATION(x)                (((x) & 0xF) << 8)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F1_REQ_DURATION(x)                (((x) & 0xF) << 4)
#define BIT_PUB_APB_REG_PUB_DFS_HW_F0_REQ_DURATION(x)                (((x) & 0xF))

/* REG_PUB_APB_REG_HW_DESKEWPLL_PD_CTRL0 */

#define BIT_PUB_APB_REG_HW_DESKEW_PLL_PD_DEEP_SLEEP_MODE(x)          (((x) & 0xFF) << 24)
#define BIT_PUB_APB_REG_HW_DESKEW_PLL_PD_AUTO_LIGHT_SLEEP_MODE(x)    (((x) & 0xFF) << 16)
#define BIT_PUB_APB_REG_HW_DESKEW_PLL_PD_SMART_LIGHT_SLEEP_MODE(x)   (((x) & 0xFF) << 8)
#define BIT_PUB_APB_REG_HW_DESKEW_PLL_PD_DEFAULT_BYP_MODE(x)         (((x) & 0xFF))

/* REG_PUB_APB_REG_HW_DESKEWPLL_PD_CTRL1 */

#define BIT_PUB_APB_REG_DFS_FC_ACK_ASSERT_WAIT_CNT(x)                (((x) & 0xFF) << 8)
#define BIT_PUB_APB_REG_DFS_HW_FRQ_SEL_SW(x)                         (((x) & 0x7) << 4)
#define BIT_PUB_APB_REG_DFS_HW_FRQ_SEL_SET                           BIT(3)
#define BIT_PUB_APB_REG_DFS_CUR_CLK_MODE_TOGGLE                      BIT(2)
#define BIT_PUB_APB_REG_HW_DESKEW_PLL_PD_DEFAULT_HIGH                BIT(1)
#define BIT_PUB_APB_REG_HW_DESKEW_PLL_PO_AHEAD_EN                    BIT(0)

/* REG_PUB_APB_REG_DVS_CTRL_0 */

#define BIT_PUB_APB_REG_VDDCORE_VOL_F7(x)                            (((x) & 0x7) << 28)
#define BIT_PUB_APB_REG_VDDCORE_VOL_F6(x)                            (((x) & 0x7) << 24)
#define BIT_PUB_APB_REG_VDDCORE_VOL_F5(x)                            (((x) & 0x7) << 20)
#define BIT_PUB_APB_REG_VDDCORE_VOL_F4(x)                            (((x) & 0x7) << 16)
#define BIT_PUB_APB_REG_VDDCORE_VOL_F3(x)                            (((x) & 0x7) << 12)
#define BIT_PUB_APB_REG_VDDCORE_VOL_F2(x)                            (((x) & 0x7) << 8)
#define BIT_PUB_APB_REG_VDDCORE_VOL_F1(x)                            (((x) & 0x7) << 4)
#define BIT_PUB_APB_REG_VDDCORE_VOL_F0(x)                            (((x) & 0x7))

/* REG_PUB_APB_REG_DVS_CTRL_1 */

#define BIT_PUB_APB_REG_VDDCORE_VOL_CUR(x)                           (((x) & 0x7) << 26)
#define BIT_PUB_APB_REG_VDDCORE_VOL_DFLT(x)                          (((x) & 0x7) << 23)
#define BIT_PUB_APB_REG_VDDCORE_VOL_SET                              BIT(22)
#define BIT_PUB_APB_REG_VDDCORE_DVS_ACK                              BIT(21)
#define BIT_PUB_APB_REG_VDDCORE_DVS_REQ_SW                           BIT(20)
#define BIT_PUB_APB_REG_VDDCORE_DVS_VOL_SW(x)                        (((x) & 0x7) << 17)
#define BIT_PUB_APB_REG_VDDCORE_DVS_SW_EN                            BIT(16)
#define BIT_PUB_APB_REG_VDDCORE_DVS_DEC_EN(x)                        (((x) & 0xFF) << 8)
#define BIT_PUB_APB_REG_VDDCORE_DVS_INC_EN(x)                        (((x) & 0xFF))

/* REG_PUB_APB_REG_DVS_CTRL_2 */

#define BIT_PUB_APB_REG_HW_DFS_AUTO_DIS                              BIT(19)
#define BIT_PUB_APB_REG_HW_DFS_TARGET_FSP(x)                         (((x) & 0x7) << 16)
#define BIT_PUB_APB_REG_VDDCORE_DVS_DN_SW_EN(x)                      (((x) & 0xFF) << 8)
#define BIT_PUB_APB_REG_VDDCORE_DVS_UP_SW_EN(x)                      (((x) & 0xFF))

/* REG_PUB_APB_REG_VOTE_MASTER_EN */

#define BIT_PUB_APB_REG_DFS_VOTE_DEC_EN                              BIT(31)
#define BIT_PUB_APB_REG_VOTE_HW_DFS_DEC_MASK_EN                      BIT(30)
#define BIT_PUB_APB_REG_VOTE_HW_DFS_INC_MASK_EN                      BIT(29)

/* REG_PUB_APB_REG_VOTE_FSM_CNT */

#define BIT_PUB_APB_REG_DFS_INTERVAL_CNT(x)                          (((x) & 0x7FFF) << 15)
#define BIT_PUB_APB_REG_VOTE_INTERVAL_CNT(x)                         (((x) & 0x7FFF))

/* REG_PUB_APB_REG_THRESHOLD_INC_FREQ_0 */

#define BIT_PUB_APB_REG_THRD_INC_F0(x)                               (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_THRESHOLD_INC_FREQ_1 */

#define BIT_PUB_APB_REG_THRD_INC_F1(x)                               (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_THRESHOLD_INC_FREQ_2 */

#define BIT_PUB_APB_REG_THRD_INC_F2(x)                               (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_THRESHOLD_INC_FREQ_3 */

#define BIT_PUB_APB_REG_THRD_INC_F3(x)                               (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_THRESHOLD_INC_FREQ_4 */

#define BIT_PUB_APB_REG_THRD_INC_F4(x)                               (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_THRESHOLD_INC_FREQ_5 */

#define BIT_PUB_APB_REG_THRD_INC_F5(x)                               (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_THRESHOLD_INC_FREQ_6 */

#define BIT_PUB_APB_REG_THRD_INC_F6(x)                               (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_THRESHOLD_INC_FREQ_7 */

#define BIT_PUB_APB_REG_THRD_INC_F7(x)                               (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_TEST_DSKPLL_BIST_CNT */

#define BIT_PUB_APB_REG_TEST_DSKPLL_BIST_CNT(x)                      (((x) & 0xFFFF))

/* REG_PUB_APB_REG_PUB_STATUS_MON_CTRL */

#define BIT_PUB_APB_REG_DFS_COUNT_EN                                 BIT(9)
#define BIT_PUB_APB_REG_PUB_DFS_STA_EN                               BIT(8)
#define BIT_PUB_APB_REG_DMC_ST_MON_SEL(x)                            (((x) & 0x3) << 1)
#define BIT_PUB_APB_REG_PUB_TOP_MON_EN                               BIT(0)

/* REG_PUB_APB_REG_PUB_ST_IDLE_CYC_CNT */

#define BIT_PUB_APB_REG_DMC_ST_IDLE_CYCLE_CNT(x)                     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_PUB_ST_WR_CYC_CNT */

#define BIT_PUB_APB_REG_DMC_ST_WRITE_CYCLE_CNT(x)                    (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_PUB_ST_RD_CYC_CNT */

#define BIT_PUB_APB_REG_DMC_ST_READ_CYCLE_CNT(x)                     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_PUB_ST_SR_CYC_CNT */

#define BIT_PUB_APB_REG_DMC_ST_SREF_CYCLE_CNT(x)                     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_PUB_ST_LS_CYC_CNT */

#define BIT_PUB_APB_REG_DMC_ST_LIGHT_CYCLE_CNT(x)                    (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_PUB_ST_LS_TIME_CNT */

#define BIT_PUB_APB_REG_DMC_ST_SREF_CNT(x)                           (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_REG_DMC_ST_LIGHT_CNT(x)                          (((x) & 0xFFFF))

/* REG_PUB_APB_REG_PUB_DFS_F0_CYC_CNT */

#define BIT_PUB_APB_REG_DFS_F0_CYCLE_CNT(x)                          (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_PUB_DFS_F1_CYC_CNT */

#define BIT_PUB_APB_REG_DFS_F1_CYCLE_CNT(x)                          (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_PUB_DFS_F2_CYC_CNT */

#define BIT_PUB_APB_REG_DFS_F2_CYCLE_CNT(x)                          (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_PUB_DFS_F3_CYC_CNT */

#define BIT_PUB_APB_REG_DFS_F3_CYCLE_CNT(x)                          (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_PUB_DFS_F4_CYC_CNT */

#define BIT_PUB_APB_REG_DFS_F4_CYCLE_CNT(x)                          (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_PUB_DFS_F5_CYC_CNT */

#define BIT_PUB_APB_REG_DFS_F5_CYCLE_CNT(x)                          (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_PUB_DFS_F6_CYC_CNT */

#define BIT_PUB_APB_REG_DFS_F6_CYCLE_CNT(x)                          (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_PUB_DFS_F7_CYC_CNT */

#define BIT_PUB_APB_REG_DFS_F7_CYCLE_CNT(x)                          (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_PUB_DFS_CNT */

#define BIT_PUB_APB_REG_DFS_COUNT(x)                                 (((x) & 0x3FF))

/* REG_PUB_APB_REG_VOTE_CTRL_APCPU */

#define BIT_PUB_APB_REG_APCPU_BV_EN                                  BIT(31)
#define BIT_PUB_APB_REG_APCPU_FV_EN                                  BIT(30)
#define BIT_PUB_APB_REG_VOTE_APCPU_ACK                               BIT(23)
#define BIT_PUB_APB_REG_FREQ_VOTE_APCPU_FLAG                         BIT(19)
#define BIT_PUB_APB_REG_FREQ_VOTE_APCPU(x)                           (((x) & 0x7) << 16)
#define BIT_PUB_APB_REG_BW_VOTE_APCPU_FLAG                           BIT(14)

/* REG_PUB_APB_REG_VOTE_CTRL_MINIAP */

#define BIT_PUB_APB_REG_MINIAP_BV_EN                                 BIT(31)
#define BIT_PUB_APB_REG_MINIAP_FV_EN                                 BIT(30)
#define BIT_PUB_APB_REG_VOTE_MINIAP_ACK                              BIT(23)
#define BIT_PUB_APB_REG_FREQ_VOTE_MINIAP_FLAG                        BIT(19)
#define BIT_PUB_APB_REG_FREQ_VOTE_MINIAP(x)                          (((x) & 0x7) << 16)
#define BIT_PUB_APB_REG_BW_VOTE_MINIAP_FLAG                          BIT(14)

/* REG_PUB_APB_REG_VOTE_CTRL_NRCPU */

#define BIT_PUB_APB_REG_NRCPU_BV_EN                                  BIT(31)
#define BIT_PUB_APB_REG_NRCPU_FV_EN                                  BIT(30)
#define BIT_PUB_APB_REG_VOTE_NRCPU_ACK                               BIT(23)
#define BIT_PUB_APB_REG_FREQ_VOTE_NRCPU_FLAG                         BIT(19)
#define BIT_PUB_APB_REG_FREQ_VOTE_NRCPU(x)                           (((x) & 0x7) << 16)
#define BIT_PUB_APB_REG_BW_VOTE_NRCPU_FLAG                           BIT(14)

/* REG_PUB_APB_REG_VOTE_CTRL_NRACC */

#define BIT_PUB_APB_REG_NRACC_BV_EN                                  BIT(31)
#define BIT_PUB_APB_REG_NRACC_FV_EN                                  BIT(30)
#define BIT_PUB_APB_REG_VOTE_NRACC_ACK                               BIT(23)
#define BIT_PUB_APB_REG_FREQ_VOTE_NRACC_FLAG                         BIT(19)
#define BIT_PUB_APB_REG_FREQ_VOTE_NRACC(x)                           (((x) & 0x7) << 16)
#define BIT_PUB_APB_REG_BW_VOTE_NRACC_FLAG                           BIT(14)

/* REG_PUB_APB_REG_VOTE_CTRL_V3CPU */

#define BIT_PUB_APB_REG_V3CPU_BV_EN                                  BIT(31)
#define BIT_PUB_APB_REG_V3CPU_FV_EN                                  BIT(30)
#define BIT_PUB_APB_REG_VOTE_V3CPU_ACK                               BIT(23)
#define BIT_PUB_APB_REG_FREQ_VOTE_V3CPU_FLAG                         BIT(19)
#define BIT_PUB_APB_REG_FREQ_VOTE_V3CPU(x)                           (((x) & 0x7) << 16)
#define BIT_PUB_APB_REG_BW_VOTE_V3CPU_FLAG                           BIT(14)

/* REG_PUB_APB_REG_VOTE_CTRL_AGCP */

#define BIT_PUB_APB_REG_AGCP_BV_EN                                   BIT(31)
#define BIT_PUB_APB_REG_AGCP_FV_EN                                   BIT(30)
#define BIT_PUB_APB_REG_VOTE_AGCP_ACK                                BIT(23)
#define BIT_PUB_APB_REG_FREQ_VOTE_AGCP_FLAG                          BIT(19)
#define BIT_PUB_APB_REG_FREQ_VOTE_AGCP(x)                            (((x) & 0x7) << 16)
#define BIT_PUB_APB_REG_BW_VOTE_AGCP_FLAG                            BIT(14)

/* REG_PUB_APB_REG_VOTE_CTRL_SW */

#define BIT_PUB_APB_REG_SW_BV_EN                                     BIT(31)
#define BIT_PUB_APB_REG_SW_FV_EN                                     BIT(30)
#define BIT_PUB_APB_REG_VOTE_SW_ACK                                  BIT(23)
#define BIT_PUB_APB_REG_FREQ_VOTE_SW_FLAG                            BIT(19)
#define BIT_PUB_APB_REG_FREQ_VOTE_SW(x)                              (((x) & 0x7) << 16)
#define BIT_PUB_APB_REG_BW_VOTE_SW_FLAG                              BIT(14)

/* REG_PUB_APB_REG_VOTE_CTRL_V3ACC */

#define BIT_PUB_APB_REG_V3ACC_BV_EN                                  BIT(31)
#define BIT_PUB_APB_REG_V3ACC_FV_EN                                  BIT(30)
#define BIT_PUB_APB_REG_VOTE_V3ACC_ACK                               BIT(23)
#define BIT_PUB_APB_REG_FREQ_VOTE_V3ACC_FLAG                         BIT(19)
#define BIT_PUB_APB_REG_FREQ_VOTE_V3ACC(x)                           (((x) & 0x7) << 16)
#define BIT_PUB_APB_REG_BW_VOTE_V3ACC_FLAG                           BIT(14)

/* REG_PUB_APB_REG_VOTE_CTRL_PSCP */

#define BIT_PUB_APB_REG_PSCP_BV_EN                                   BIT(31)
#define BIT_PUB_APB_REG_PSCP_FV_EN                                   BIT(30)
#define BIT_PUB_APB_REG_VOTE_PSCP_ACK                                BIT(23)
#define BIT_PUB_APB_REG_FREQ_VOTE_PSCP_FLAG                          BIT(19)
#define BIT_PUB_APB_REG_FREQ_VOTE_PSCP(x)                            (((x) & 0x7) << 16)
#define BIT_PUB_APB_REG_BW_VOTE_PSCP_FLAG                            BIT(14)

/* REG_PUB_APB_REG_VOTE_CTRL_WCDMA_PS */

#define BIT_PUB_APB_REG_WCPU_BV_EN                                   BIT(31)
#define BIT_PUB_APB_REG_WCPU_FV_EN                                   BIT(30)
#define BIT_PUB_APB_REG_VOTE_WCPU_ACK                                BIT(23)
#define BIT_PUB_APB_REG_FREQ_VOTE_WCPU_FLAG                          BIT(19)
#define BIT_PUB_APB_REG_FREQ_VOTE_WCPU(x)                            (((x) & 0x7) << 16)
#define BIT_PUB_APB_REG_BW_VOTE_WCPU_FLAG                            BIT(14)

/* REG_PUB_APB_REG_VOTE_CTRL_TDS_PS */

#define BIT_PUB_APB_REG_TDCPU_BV_EN                                  BIT(31)
#define BIT_PUB_APB_REG_TDCPU_FV_EN                                  BIT(30)
#define BIT_PUB_APB_REG_VOTE_TDCPU_ACK                               BIT(23)
#define BIT_PUB_APB_REG_FREQ_VOTE_TDCPU_FLAG                         BIT(19)
#define BIT_PUB_APB_REG_FREQ_VOTE_TDCPU(x)                           (((x) & 0x7) << 16)
#define BIT_PUB_APB_REG_BW_VOTE_TDCPU_FLAG                           BIT(14)

/* REG_PUB_APB_REG_VOTE_CTRL_GSM_PS */

#define BIT_PUB_APB_REG_GSMCPU_BV_EN                                 BIT(31)
#define BIT_PUB_APB_REG_GSMCPU_FV_EN                                 BIT(30)
#define BIT_PUB_APB_REG_VOTE_GSMCPU_ACK                              BIT(23)
#define BIT_PUB_APB_REG_FREQ_VOTE_GSMCPU_FLAG                        BIT(19)
#define BIT_PUB_APB_REG_FREQ_VOTE_GSMCPU(x)                          (((x) & 0x7) << 16)
#define BIT_PUB_APB_REG_BW_VOTE_GSMCPU_FLAG                          BIT(14)

/* REG_PUB_APB_REG_VOTE_CTRL_WCDMA_PHY */

#define BIT_PUB_APB_REG_WACC_BV_EN                                   BIT(31)
#define BIT_PUB_APB_REG_WACC_FV_EN                                   BIT(30)
#define BIT_PUB_APB_REG_VOTE_WACC_ACK                                BIT(23)
#define BIT_PUB_APB_REG_FREQ_VOTE_WACC_FLAG                          BIT(19)
#define BIT_PUB_APB_REG_FREQ_VOTE_WACC(x)                            (((x) & 0x7) << 16)
#define BIT_PUB_APB_REG_BW_VOTE_WACC_FLAG                            BIT(14)

/* REG_PUB_APB_REG_VOTE_CTRL_TDS_PHY */

#define BIT_PUB_APB_REG_TDACC_BV_EN                                  BIT(31)
#define BIT_PUB_APB_REG_TDACC_FV_EN                                  BIT(30)
#define BIT_PUB_APB_REG_VOTE_TDACC_ACK                               BIT(23)
#define BIT_PUB_APB_REG_FREQ_VOTE_TDACC_FLAG                         BIT(19)
#define BIT_PUB_APB_REG_FREQ_VOTE_TDACC(x)                           (((x) & 0x7) << 16)
#define BIT_PUB_APB_REG_BW_VOTE_TDACC_FLAG                           BIT(14)

/* REG_PUB_APB_REG_VOTE_CTRL_GSM_PHY */

#define BIT_PUB_APB_REG_GSMACC_BV_EN                                 BIT(31)
#define BIT_PUB_APB_REG_GSMACC_FV_EN                                 BIT(30)
#define BIT_PUB_APB_REG_VOTE_GSMACC_ACK                              BIT(23)
#define BIT_PUB_APB_REG_FREQ_VOTE_GSMACC_FLAG                        BIT(19)
#define BIT_PUB_APB_REG_FREQ_VOTE_GSMACC(x)                          (((x) & 0x7) << 16)
#define BIT_PUB_APB_REG_BW_VOTE_GSMACC_FLAG                          BIT(14)

/* REG_PUB_APB_REG_DFS_GFREE_CTRL */

#define BIT_PUB_APB_REG_DFS_GFREE_HW_BYPASS_EN                       BIT(24)
#define BIT_PUB_APB_REG_DFS_GFREE_SW_OPEN_DELAY(x)                   (((x) & 0x1FF) << 10)
#define BIT_PUB_APB_REG_DFS_GFREE_SW_CLOSE_DELAY(x)                  (((x) & 0x1FF) << 1)
#define BIT_PUB_APB_REG_DFS_GFREE_SW_BYPASS                          BIT(0)

/* REG_PUB_APB_REG_DFS_SW_CTRL_APPEND */

#define BIT_PUB_APB_REG_PUB_DFS_SW_SWITCH_PERIOD_APPEND(x)           (((x) & 0xF))

/* REG_PUB_APB_REG_AWURGENT_DBG_CTRL */

#define BIT_PUB_APB_REG_AWURGENT_DBG_AGCP(x)                         (((x) & 0x3) << 18)
#define BIT_PUB_APB_REG_AWURGENT_DBG_PSCP(x)                         (((x) & 0x3) << 16)
#define BIT_PUB_APB_REG_AWURGENT_DBG_V3ACC(x)                        (((x) & 0x3) << 14)
#define BIT_PUB_APB_REG_AWURGENT_DBG_V3CPU(x)                        (((x) & 0x3) << 12)
#define BIT_PUB_APB_REG_AWURGENT_DBG_NRACC(x)                        (((x) & 0x3) << 10)
#define BIT_PUB_APB_REG_AWURGENT_DBG_NRCPU(x)                        (((x) & 0x3) << 8)
#define BIT_PUB_APB_REG_AWURGENT_DBG_AONSYS(x)                       (((x) & 0x3) << 6)
#define BIT_PUB_APB_REG_AWURGENT_DBG_CSSYS(x)                        (((x) & 0x3) << 4)
#define BIT_PUB_APB_REG_AWURGENT_DBG_MINIAP(x)                       (((x) & 0x3) << 2)
#define BIT_PUB_APB_REG_AWURGENT_DBG_APCPU(x)                        (((x) & 0x3))

/* REG_PUB_APB_REG_ARURGENT_DBG_CTRL */

#define BIT_PUB_APB_REG_ARURGENT_DBG_AGCP(x)                         (((x) & 0x3) << 18)
#define BIT_PUB_APB_REG_ARURGENT_DBG_PSCP(x)                         (((x) & 0x3) << 16)
#define BIT_PUB_APB_REG_ARURGENT_DBG_V3ACC(x)                        (((x) & 0x3) << 14)
#define BIT_PUB_APB_REG_ARURGENT_DBG_V3CPU(x)                        (((x) & 0x3) << 12)
#define BIT_PUB_APB_REG_ARURGENT_DBG_NRACC(x)                        (((x) & 0x3) << 10)
#define BIT_PUB_APB_REG_ARURGENT_DBG_NRCPU(x)                        (((x) & 0x3) << 8)
#define BIT_PUB_APB_REG_ARURGENT_DBG_AONSYS(x)                       (((x) & 0x3) << 6)
#define BIT_PUB_APB_REG_ARURGENT_DBG_CSSYS(x)                        (((x) & 0x3) << 4)
#define BIT_PUB_APB_REG_ARURGENT_DBG_MINIAP(x)                       (((x) & 0x3) << 2)
#define BIT_PUB_APB_REG_ARURGENT_DBG_APCPU(x)                        (((x) & 0x3))

/* REG_PUB_APB_REG_LSLP_SRE_SIM */

#define BIT_PUB_APB_REG_SRE_FLAG_DBG                                 BIT(1)
#define BIT_PUB_APB_REG_SRE_REQ_DBG                                  BIT(0)

/* REG_PUB_APB_REG_VOTE_BW_APCPU */

#define BIT_PUB_APB_REG_BW_VOTE_APCPU(x)                             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_VOTE_BW_MINIAP */

#define BIT_PUB_APB_REG_BW_VOTE_MINIAP(x)                            (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_VOTE_BW_AGCP */

#define BIT_PUB_APB_REG_BW_VOTE_AGCP(x)                              (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_VOTE_BW_PSCP */

#define BIT_PUB_APB_REG_BW_VOTE_PSCP(x)                              (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_VOTE_BW_NRACC */

#define BIT_PUB_APB_REG_BW_VOTE_NRACC(x)                             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_VOTE_BW_NRCPU */

#define BIT_PUB_APB_REG_BW_VOTE_NRCPU(x)                             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_VOTE_BW_V3ACC */

#define BIT_PUB_APB_REG_BW_VOTE_V3ACC(x)                             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_VOTE_BW_V3CPU */

#define BIT_PUB_APB_REG_BW_VOTE_V3CPU(x)                             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_VOTE_BW_WACC */

#define BIT_PUB_APB_REG_BW_VOTE_WACC(x)                              (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_VOTE_BW_WCPU */

#define BIT_PUB_APB_REG_BW_VOTE_WCPU(x)                              (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_VOTE_BW_TDACC */

#define BIT_PUB_APB_REG_BW_VOTE_TDACC(x)                             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_VOTE_BW_TDCPU */

#define BIT_PUB_APB_REG_BW_VOTE_TDCPU(x)                             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_VOTE_BW_GSMACC */

#define BIT_PUB_APB_REG_BW_VOTE_GSMACC(x)                            (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_VOTE_BW_GSMCPU */

#define BIT_PUB_APB_REG_BW_VOTE_GSMCPU(x)                            (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_VOTE_BW_SW */

#define BIT_PUB_APB_REG_BW_VOTE_SW(x)                                (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_MTX_BUSMON_CTRL */

#define BIT_PUB_APB_REG_MATRIX_BUSMON_EN                             BIT(0)

/* REG_PUB_APB_REG_HIGH_URGENCY_CTRL */

#define BIT_PUB_APB_REG_AGCP_HIGH_URGENCY_EN                         BIT(6)
#define BIT_PUB_APB_REG_PSCP_HIGH_URGENCY_EN                         BIT(5)
#define BIT_PUB_APB_REG_V3ACC_HIGH_URGENCY_EN                        BIT(4)
#define BIT_PUB_APB_REG_V3CPU_HIGH_URGENCY_EN                        BIT(3)
#define BIT_PUB_APB_REG_NRACC_HIGH_URGENCY_EN                        BIT(2)
#define BIT_PUB_APB_REG_NRCPU_HIGH_URGENCY_EN                        BIT(1)
#define BIT_PUB_APB_REG_APCPU_MINIAP_CS_AON_HIGH_URGENCY_EN          BIT(0)

/* REG_PUB_APB_REG_LPC_PU_NUM_CTRL_0 */

#define BIT_PUB_APB_REG_CFG_MTX_M0_PU_NUM(x)                         (((x) & 0xFF) << 24)
#define BIT_PUB_APB_REG_CFG_MTX_S0_MCTRL_PU_NUM(x)                   (((x) & 0xFF) << 16)
#define BIT_PUB_APB_REG_CFG_MTX_S1_GLBAPB_PU_NUM(x)                  (((x) & 0xFF) << 8)
#define BIT_PUB_APB_REG_CFG_MTX_S2_PTM_PU_NUM(x)                     (((x) & 0xFF))

/* REG_PUB_APB_REG_LPC_PU_NUM_CTRL_1 */

#define BIT_PUB_APB_REG_CFG_MTX_S4_REGU_PU_NUM(x)                    (((x) & 0xFF) << 8)
#define BIT_PUB_APB_REG_CFG_MTX_S3_DMC_BIST_PU_NUM(x)                (((x) & 0xFF))

/* REG_PUB_APB_REG_LPC_PU_NUM_CTRL_2 */

#define BIT_PUB_APB_REG_MERGE_MTX_M0_APCPU_PU_NUM(x)                 (((x) & 0xFF) << 24)
#define BIT_PUB_APB_REG_MERGE_MTX_M1_MINIAP_PU_NUM(x)                (((x) & 0xFF) << 16)
#define BIT_PUB_APB_REG_MERGE_MTX_M2_CS_PU_NUM(x)                    (((x) & 0xFF) << 8)
#define BIT_PUB_APB_REG_MERGE_MTX_M3_AON_PU_NUM(x)                   (((x) & 0xFF))

/* REG_PUB_APB_REG_LPC_PU_NUM_CTRL_3 */

#define BIT_PUB_APB_REG_MERGE_MTX_S0_PU_NUM(x)                       (((x) & 0xFF))

/* REG_PUB_APB_REG_DMC_BIST_MST_AXUSER_CFG_0 */

#define BIT_PUB_APB_REG_DMC_BIST_MST1_CFG_AWUSER(x)                  (((x) & 0xFF) << 24)
#define BIT_PUB_APB_REG_DMC_BIST_MST1_CFG_ARUSER(x)                  (((x) & 0xFF) << 16)
#define BIT_PUB_APB_REG_DMC_BIST_MST0_CFG_AWUSER(x)                  (((x) & 0xFF) << 8)
#define BIT_PUB_APB_REG_DMC_BIST_MST0_CFG_ARUSER(x)                  (((x) & 0xFF))

/* REG_PUB_APB_REG_DMC_BIST_MST_AXUSER_CFG_1 */

#define BIT_PUB_APB_REG_DMC_BIST_MST3_CFG_AWUSER(x)                  (((x) & 0xFF) << 24)
#define BIT_PUB_APB_REG_DMC_BIST_MST3_CFG_ARUSER(x)                  (((x) & 0xFF) << 16)
#define BIT_PUB_APB_REG_DMC_BIST_MST2_CFG_AWUSER(x)                  (((x) & 0xFF) << 8)
#define BIT_PUB_APB_REG_DMC_BIST_MST2_CFG_ARUSER(x)                  (((x) & 0xFF))

/* REG_PUB_APB_REG_PUB0_DUMMY_REG0 */

#define BIT_PUB_APB_REG_PUB0_DUMMY_REG0(x)                           (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_REG_PUB0_DUMMY_REG1 */

#define BIT_PUB_APB_REG_PUB0_DUMMY_REG1(x)                           (((x) & 0xFFFFFFFF))


#endif /* PUB_APB_REG_H */


