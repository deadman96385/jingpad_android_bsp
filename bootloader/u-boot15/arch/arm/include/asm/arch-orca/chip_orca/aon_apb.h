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


#ifndef AON_APB_H
#define AON_APB_H

#define CTL_BASE_AON_APB 0x64020000


#define REG_AON_APB_APB_EB0                          ( CTL_BASE_AON_APB + 0x0000 )
#define REG_AON_APB_APB_EB1                          ( CTL_BASE_AON_APB + 0x0004 )
#define REG_AON_APB_APB_EB2                          ( CTL_BASE_AON_APB + 0x0008 )
#define REG_AON_APB_APB_RTC_EB0                      ( CTL_BASE_AON_APB + 0x000C )
#define REG_AON_APB_PSCP_AON_EB                      ( CTL_BASE_AON_APB + 0x0010 )
#define REG_AON_APB_CGM_REG1                         ( CTL_BASE_AON_APB + 0x0020 )
#define REG_AON_APB_CGM_CLK_TOP_REG1                 ( CTL_BASE_AON_APB + 0x0024 )
#define REG_AON_APB_APCPU_INT_ENABLE_CTRL0           ( CTL_BASE_AON_APB + 0x0030 )
#define REG_AON_APB_APCPU_INT_ENABLE_CTRL1           ( CTL_BASE_AON_APB + 0x0034 )
#define REG_AON_APB_APCPU_INT_ENABLE_CTRL2           ( CTL_BASE_AON_APB + 0x0038 )
#define REG_AON_APB_APCPU_INT_ENABLE_CTRL3           ( CTL_BASE_AON_APB + 0x003C )
#define REG_AON_APB_APCPU_INT_ENABLE_CTRL4           ( CTL_BASE_AON_APB + 0x0040 )
#define REG_AON_APB_APCPU_INT_ENABLE_CTRL5           ( CTL_BASE_AON_APB + 0x0044 )
#define REG_AON_APB_SP_WAKEUP_MASK_EN0               ( CTL_BASE_AON_APB + 0x0050 )
#define REG_AON_APB_SP_WAKEUP_MASK_EN1               ( CTL_BASE_AON_APB + 0x0054 )
#define REG_AON_APB_SP_WAKEUP_MASK_EN2               ( CTL_BASE_AON_APB + 0x0058 )
#define REG_AON_APB_APB_RST0                         ( CTL_BASE_AON_APB + 0x0200 )
#define REG_AON_APB_APB_RST1                         ( CTL_BASE_AON_APB + 0x0204 )
#define REG_AON_APB_APB_RST2                         ( CTL_BASE_AON_APB + 0x0208 )
#define REG_AON_APB_APB_RST3                         ( CTL_BASE_AON_APB + 0x020C )
#define REG_AON_APB_CM4_SYS_SOFT_RST                 ( CTL_BASE_AON_APB + 0x0210 )
#define REG_AON_APB_PSCP_SOFT_RST                    ( CTL_BASE_AON_APB + 0x0214 )
#define REG_AON_APB_NRCP_SOFT_RST                    ( CTL_BASE_AON_APB + 0x0218 )
#define REG_AON_APB_V3PS_SOFT_RST                    ( CTL_BASE_AON_APB + 0x021C )
#define REG_AON_APB_V3PHY_SOFT_RST                   ( CTL_BASE_AON_APB + 0x0220 )
#define REG_AON_APB_WDG_RST_FLAG                     ( CTL_BASE_AON_APB + 0x0224 )
#define REG_AON_APB_APCPU_SOFT_RST                   ( CTL_BASE_AON_APB + 0x0228 )
#define REG_AON_APB_BOOT_MODE                        ( CTL_BASE_AON_APB + 0x0400 )
#define REG_AON_APB_CP_ARM_JTAG_CTRL                 ( CTL_BASE_AON_APB + 0x0404 )
#define REG_AON_APB_RC100M_CFG                       ( CTL_BASE_AON_APB + 0x0500 )
#define REG_AON_APB_CCIR_RCVR_CFG                    ( CTL_BASE_AON_APB + 0x0504 )
#define REG_AON_APB_PLL_BG_CFG                       ( CTL_BASE_AON_APB + 0x0508 )
#define REG_AON_APB_MBIST_EFUSE_CTRL                 ( CTL_BASE_AON_APB + 0x050C )
#define REG_AON_APB_OTG_PHY_TEST                     ( CTL_BASE_AON_APB + 0x0510 )
#define REG_AON_APB_OTG_PHY_CTRL                     ( CTL_BASE_AON_APB + 0x0514 )
#define REG_AON_APB_OTG_CTRL0                        ( CTL_BASE_AON_APB + 0x0518 )
#define REG_AON_APB_OTG_CTRL1                        ( CTL_BASE_AON_APB + 0x051C )
#define REG_AON_APB_USB_CLK_REF_SEL                  ( CTL_BASE_AON_APB + 0x0520 )
#define REG_AON_APB_V3_LVDSRF_CTRL                   ( CTL_BASE_AON_APB + 0x0524 )
#define REG_AON_APB_NR_LVDSRF_CTRL                   ( CTL_BASE_AON_APB + 0x0528 )
#define REG_AON_APB_WCN_ADDA_MEM_PD_CTRL             ( CTL_BASE_AON_APB + 0x052C )
#define REG_AON_APB_THM0_CTRL                        ( CTL_BASE_AON_APB + 0x0530 )
#define REG_AON_APB_THM1_CTRL                        ( CTL_BASE_AON_APB + 0x0534 )
#define REG_AON_APB_OVERHEAT_CTRL                    ( CTL_BASE_AON_APB + 0x0538 )
#define REG_AON_APB_MPLL0_CTRL                       ( CTL_BASE_AON_APB + 0x0540 )
#define REG_AON_APB_MPLL1_CTRL                       ( CTL_BASE_AON_APB + 0x0544 )
#define REG_AON_APB_NR_RPLL_CTRL_REG2                ( CTL_BASE_AON_APB + 0x0548 )
#define REG_AON_APB_DPLL_CTRL                        ( CTL_BASE_AON_APB + 0x0550 )
#define REG_AON_APB_PLL_LOCK_OUT_SEL                 ( CTL_BASE_AON_APB + 0x0554 )
#define REG_AON_APB_SINDRV_POWER_CTRL                ( CTL_BASE_AON_APB + 0x0560 )
#define REG_AON_APB_PHY_REF_CLK_EN                   ( CTL_BASE_AON_APB + 0x0564 )
#define REG_AON_APB_RPLL_CTL_SEL                     ( CTL_BASE_AON_APB + 0x0568 )
#define REG_AON_APB_V3_RPLL_CTRL_REG0                ( CTL_BASE_AON_APB + 0x0570 )
#define REG_AON_APB_V3_RPLL_CTRL_REG1                ( CTL_BASE_AON_APB + 0x0574 )
#define REG_AON_APB_V3_RPLL_CTRL_REG2                ( CTL_BASE_AON_APB + 0x0578 )
#define REG_AON_APB_V3_RPLL_CTRL_REG3                ( CTL_BASE_AON_APB + 0x057C )
#define REG_AON_APB_V3_RPLL_CTRL_SEL                 ( CTL_BASE_AON_APB + 0x0580 )
#define REG_AON_APB_NR_RPLL_CTRL_REG0                ( CTL_BASE_AON_APB + 0x0590 )
#define REG_AON_APB_NR_RPLL_CTRL_REG1                ( CTL_BASE_AON_APB + 0x0594 )
#define REG_AON_APB_NR_RPLL_CTRL_REG3                ( CTL_BASE_AON_APB + 0x059C )
#define REG_AON_APB_NR_RPLL_CTRL_SEL                 ( CTL_BASE_AON_APB + 0x05A0 )
#define REG_AON_APB_RFSPI_SEL                        ( CTL_BASE_AON_APB + 0x05B0 )
#define REG_AON_APB_BB_SW_RFSPI_FIFO_STATS           ( CTL_BASE_AON_APB + 0x05C0 )
#define REG_AON_APB_RPLL_PD_RST_SEL                  ( CTL_BASE_AON_APB + 0x05C4 )
#define REG_AON_APB_CLK_AUD26M_EN                    ( CTL_BASE_AON_APB + 0x05C8 )
#define REG_AON_APB_TS_CFG                           ( CTL_BASE_AON_APB + 0x0600 )
#define REG_AON_APB_DCXO_LC_REG0                     ( CTL_BASE_AON_APB + 0x0604 )
#define REG_AON_APB_DCXO_LC_REG1                     ( CTL_BASE_AON_APB + 0x0608 )
#define REG_AON_APB_AUDCP_BOOT_PROT                  ( CTL_BASE_AON_APB + 0x060C )
#define REG_AON_APB_NR_DSP0_REG_PROT                 ( CTL_BASE_AON_APB + 0x0610 )
#define REG_AON_APB_NR_DSP1_REG_PROT                 ( CTL_BASE_AON_APB + 0x0614 )
#define REG_AON_APB_DAP_DJTAG_SEL                    ( CTL_BASE_AON_APB + 0x0618 )
#define REG_AON_APB_SP_CFG_BUS                       ( CTL_BASE_AON_APB + 0x061C )
#define REG_AON_APB_AON_FUNC_CTRL_0                  ( CTL_BASE_AON_APB + 0x0620 )
#define REG_AON_APB_AON_FUNC_CTRL_1                  ( CTL_BASE_AON_APB + 0x0624 )
#define REG_AON_APB_FUNC_TEST_BOOT_ADDR              ( CTL_BASE_AON_APB + 0x0628 )
#define REG_AON_APB_LEAKAGE_MAGIC_WORD               ( CTL_BASE_AON_APB + 0x0630 )
#define REG_AON_APB_LEAKAGE_SWITCH                   ( CTL_BASE_AON_APB + 0x0634 )
#define REG_AON_APB_AUDCP_DSP_CTRL0                  ( CTL_BASE_AON_APB + 0x0640 )
#define REG_AON_APB_AUDCP_DSP_CTRL1                  ( CTL_BASE_AON_APB + 0x0644 )
#define REG_AON_APB_AUDCP_CTRL                       ( CTL_BASE_AON_APB + 0x0648 )
#define REG_AON_APB_V3_CTRL                          ( CTL_BASE_AON_APB + 0x0650 )
#define REG_AON_APB_V3_CR5_CTRL                      ( CTL_BASE_AON_APB + 0x0654 )
#define REG_AON_APB_V3PS_CR5_CTRL_1                  ( CTL_BASE_AON_APB + 0x0658 )
#define REG_AON_APB_V3PHY_CR5_CTRL_1                 ( CTL_BASE_AON_APB + 0x065C )
#define REG_AON_APB_PSCP_CR8_CTRL                    ( CTL_BASE_AON_APB + 0x0660 )
#define REG_AON_APB_NRCP_CTRL                        ( CTL_BASE_AON_APB + 0x0670 )
#define REG_AON_APB_NRCP_CR8_CTRL                    ( CTL_BASE_AON_APB + 0x0674 )
#define REG_AON_APB_NRCP_DSP0_CTRL                   ( CTL_BASE_AON_APB + 0x0678 )
#define REG_AON_APB_NRCP_DSP1_CTRL                   ( CTL_BASE_AON_APB + 0x067C )
#define REG_AON_APB_NRCP_DSP0_BOOT_VECTOR            ( CTL_BASE_AON_APB + 0x0680 )
#define REG_AON_APB_NRCP_DSP1_BOOT_VECTOR            ( CTL_BASE_AON_APB + 0x0684 )
#define REG_AON_APB_DBG_DJTAG_CTRL                   ( CTL_BASE_AON_APB + 0x0690 )
#define REG_AON_APB_PSCP_SIM1_TOP_CTRL               ( CTL_BASE_AON_APB + 0x06A0 )
#define REG_AON_APB_PSCP_SIM2_TOP_CTRL               ( CTL_BASE_AON_APB + 0x06A4 )
#define REG_AON_APB_PSCP_SIM3_TOP_CTRL               ( CTL_BASE_AON_APB + 0x06A8 )
#define REG_AON_APB_AP_SIM_TOP_CTRL                  ( CTL_BASE_AON_APB + 0x06AC )
#define REG_AON_APB_V3_PS_SIM1_TOP_CTRL              ( CTL_BASE_AON_APB + 0x06B0 )
#define REG_AON_APB_V3_PS_SIM2_TOP_CTRL              ( CTL_BASE_AON_APB + 0x06B4 )
#define REG_AON_APB_V3_PS_SIM3_TOP_CTRL              ( CTL_BASE_AON_APB + 0x06B8 )
#define REG_AON_APB_AON_SDIO                         ( CTL_BASE_AON_APB + 0x06C0 )
#define REG_AON_APB_MTX_URGENCY_CTRL                 ( CTL_BASE_AON_APB + 0x06C4 )
#define REG_AON_APB_MTX_URGENCY_STATS                ( CTL_BASE_AON_APB + 0x06C8 )
#define REG_AON_APB_NR_DSP0_CTRL0                    ( CTL_BASE_AON_APB + 0x06D0 )
#define REG_AON_APB_NR_DSP0_CTRL1                    ( CTL_BASE_AON_APB + 0x06D4 )
#define REG_AON_APB_NR_DSP1_CTRL0                    ( CTL_BASE_AON_APB + 0x06D8 )
#define REG_AON_APB_NR_DSP1_CTRL1                    ( CTL_BASE_AON_APB + 0x06DC )
#define REG_AON_APB_SDIO_SLV_ADDR_OFFSET             ( CTL_BASE_AON_APB + 0x06E0 )
#define REG_AON_APB_APCPU_CFG_CTRL                   ( CTL_BASE_AON_APB + 0x06E4 )
#define REG_AON_APB_SP_AON_DDR_EXTEND                ( CTL_BASE_AON_APB + 0x06E8 )
#define REG_AON_APB_AON_APB_CLK_SEL                  ( CTL_BASE_AON_APB + 0x0700 )
#define REG_AON_APB_AUTO_GATE_CTRL0                  ( CTL_BASE_AON_APB + 0x0704 )
#define REG_AON_APB_AUTO_GATE_CTRL1                  ( CTL_BASE_AON_APB + 0x0708 )
#define REG_AON_APB_AUTO_GATE_CTRL3                  ( CTL_BASE_AON_APB + 0x070C )
#define REG_AON_APB_V3_LPC_CTRL                      ( CTL_BASE_AON_APB + 0x0710 )
#define REG_AON_APB_PSCP_LPC_CTRL                    ( CTL_BASE_AON_APB + 0x0714 )
#define REG_AON_APB_AP_LPC_CTRL                      ( CTL_BASE_AON_APB + 0x0718 )
#define REG_AON_APB_AUDCP_LPC_CTRL                   ( CTL_BASE_AON_APB + 0x071C )
#define REG_AON_APB_NRCP_LPC_CTRL                    ( CTL_BASE_AON_APB + 0x0720 )
#define REG_AON_APB_APCPU_AXI_CTRL                   ( CTL_BASE_AON_APB + 0x0730 )
#define REG_AON_APB_APCPU_CLK_CTRL0                  ( CTL_BASE_AON_APB + 0x0734 )
#define REG_AON_APB_PUB_CLK_GATING_CTRL              ( CTL_BASE_AON_APB + 0x0740 )
#define REG_AON_APB_DDRPHY_VREP                      ( CTL_BASE_AON_APB + 0x0744 )
#define REG_AON_APB_CGM_RESCUE                       ( CTL_BASE_AON_APB + 0x0748 )
#define REG_AON_APB_AON_APB_FREQ_CTRL                ( CTL_BASE_AON_APB + 0x0750 )
#define REG_AON_APB_APCPU_MONITOR_STATUS             ( CTL_BASE_AON_APB + 0x0754 )
#define REG_AON_APB_APCPU_DEBUG_PWR_LP_CTRL          ( CTL_BASE_AON_APB + 0x0758 )
#define REG_AON_APB_APCPU_GIC_COL_LP_CTRL            ( CTL_BASE_AON_APB + 0x075C )
#define REG_AON_APB_APCPU_CLUSTER_ATB_LPC_CTRL       ( CTL_BASE_AON_APB + 0x0760 )
#define REG_AON_APB_APCPU_CLUSTER_APB_LPC_CTRL       ( CTL_BASE_AON_APB + 0x0764 )
#define REG_AON_APB_APCPU_CLUSTER_GIC_LPC_CTRL       ( CTL_BASE_AON_APB + 0x0768 )
#define REG_AON_APB_APCPU_GIC600_GIC_LPC_CTRL        ( CTL_BASE_AON_APB + 0x076C )
#define REG_AON_APB_APCPU_DBG_BLK_LPC_CTRL           ( CTL_BASE_AON_APB + 0x0770 )
#define REG_AON_APB_APCPU_TOP_MTX_M0_LPC_CTRL        ( CTL_BASE_AON_APB + 0x0774 )
#define REG_AON_APB_APCPU_CLUSTER_SCU_LPC_CTRL       ( CTL_BASE_AON_APB + 0x0778 )
#define REG_AON_APB_APCPU_DDR_AB_LPC_CTRL            ( CTL_BASE_AON_APB + 0x077C )
#define REG_AON_APB_APCPU_QOS_CTRL                   ( CTL_BASE_AON_APB + 0x0780 )
#define REG_AON_APB_APCPU_URGENCY_CTRL               ( CTL_BASE_AON_APB + 0x0784 )
#define REG_AON_APB_AON_MTX_PROT_CFG                 ( CTL_BASE_AON_APB + 0x0788 )
#define REG_AON_APB_APCU_LPC_CTRL                    ( CTL_BASE_AON_APB + 0x078C )
#define REG_AON_APB_CM42AON_LPC_CTRL                 ( CTL_BASE_AON_APB + 0x0790 )
#define REG_AON_APB_AON_MTX_MAIN_LPC_CTRL            ( CTL_BASE_AON_APB + 0x0794 )
#define REG_AON_APB_AON_MTX_M0_LPC_CTRL              ( CTL_BASE_AON_APB + 0x0798 )
#define REG_AON_APB_AON_MTX_M1_LPC_CTRL              ( CTL_BASE_AON_APB + 0x079C )
#define REG_AON_APB_AON_MTX_M2_LPC_CTRL              ( CTL_BASE_AON_APB + 0x07A0 )
#define REG_AON_APB_AON_MTX_M3_LPC_CTRL              ( CTL_BASE_AON_APB + 0x07A4 )
#define REG_AON_APB_AON_MTX_M4_LPC_CTRL              ( CTL_BASE_AON_APB + 0x07A8 )
#define REG_AON_APB_AON_MTX_M5_LPC_CTRL              ( CTL_BASE_AON_APB + 0x07AC )
#define REG_AON_APB_AON_MTX_M6_LPC_CTRL              ( CTL_BASE_AON_APB + 0x07B0 )
#define REG_AON_APB_AON_MTX_S0_LPC_CTRL              ( CTL_BASE_AON_APB + 0x07B4 )
#define REG_AON_APB_AON_MTX_S1_LPC_CTRL              ( CTL_BASE_AON_APB + 0x07B8 )
#define REG_AON_APB_AON_MTX_S2_LPC_CTRL              ( CTL_BASE_AON_APB + 0x07BC )
#define REG_AON_APB_AON_MTX_S3_LPC_CTRL              ( CTL_BASE_AON_APB + 0x07C0 )
#define REG_AON_APB_AON_MTX_S4_LPC_CTRL              ( CTL_BASE_AON_APB + 0x07C4 )
#define REG_AON_APB_AON_MTX_S5_LPC_CTRL              ( CTL_BASE_AON_APB + 0x07C8 )
#define REG_AON_APB_AON_MTX_S6_LPC_CTRL              ( CTL_BASE_AON_APB + 0x07CC )
#define REG_AON_APB_AON_MTX_S7_LPC_CTRL              ( CTL_BASE_AON_APB + 0x07D0 )
#define REG_AON_APB_EAXI_MTX_M0_LPC_CTRL             ( CTL_BASE_AON_APB + 0x07E0 )
#define REG_AON_APB_EAXI_MTX_M1_LPC_CTRL             ( CTL_BASE_AON_APB + 0x07E4 )
#define REG_AON_APB_EAXI_MTX_M2_LPC_CTRL             ( CTL_BASE_AON_APB + 0x07E8 )
#define REG_AON_APB_EAXI_MTX_S0_LPC_CTRL             ( CTL_BASE_AON_APB + 0x07EC )
#define REG_AON_APB_EAXI_MTX_S1_LPC_CTRL             ( CTL_BASE_AON_APB + 0x07F0 )
#define REG_AON_APB_EAXI_MTX_MAIN_LPC_CTRL           ( CTL_BASE_AON_APB + 0x07F4 )
#define REG_AON_APB_AON_SOC_USB_CTRL                 ( CTL_BASE_AON_APB + 0x07FC )
#define REG_AON_APB_PCIE_SLV_ADDR_OFFSET             ( CTL_BASE_AON_APB + 0x0800 )
#define REG_AON_APB_AP_EMMC_PHY_CTRL                 ( CTL_BASE_AON_APB + 0x0804 )
#define REG_AON_APB_AP_SDIO1_PHY_CTRL                ( CTL_BASE_AON_APB + 0x0808 )
#define REG_AON_APB_PS_SDIO2_PHY_CTRL                ( CTL_BASE_AON_APB + 0x080C )
#define REG_AON_APB_V3PS_SDIO2_PHY_CTRL              ( CTL_BASE_AON_APB + 0x0810 )
#define REG_AON_APB_RVBARADDR0                       ( CTL_BASE_AON_APB + 0x0820 )
#define REG_AON_APB_RVBARADDR1                       ( CTL_BASE_AON_APB + 0x0824 )
#define REG_AON_APB_APCPU_PU_NUM                     ( CTL_BASE_AON_APB + 0x0828 )
#define REG_AON_APB_APCPU_L3CACHE_RAM_PD_BYPASS      ( CTL_BASE_AON_APB + 0x082C )
#define REG_AON_APB_AON_TO_AUDCP_RS_LPC_CTRL         ( CTL_BASE_AON_APB + 0x0830 )
#define REG_AON_APB_AP_TO_NR_RS_LPC_CTRL             ( CTL_BASE_AON_APB + 0x0834 )
#define REG_AON_APB_AP_TO_PSCP_RS_LPC_CTRL           ( CTL_BASE_AON_APB + 0x0838 )
#define REG_AON_APB_APCPU_TO_AP_RS_LPC_CTRL          ( CTL_BASE_AON_APB + 0x083C )
#define REG_AON_APB_NR_TO_AP_RS_LPC_CTRL             ( CTL_BASE_AON_APB + 0x0840 )
#define REG_AON_APB_NR_TO_PSCP_RS_LPC_CTRL           ( CTL_BASE_AON_APB + 0x0844 )
#define REG_AON_APB_PSCP_TO_AP_RS_LPC_CTRL           ( CTL_BASE_AON_APB + 0x0848 )
#define REG_AON_APB_PSCP_TO_NR_RS_LPC_CTRL           ( CTL_BASE_AON_APB + 0x084C )
#define REG_AON_APB_PSCP_TO_V3_RS_LPC_CTRL           ( CTL_BASE_AON_APB + 0x0850 )
#define REG_AON_APB_AUDCP_TO_PUB_RS_LPC_CTRL         ( CTL_BASE_AON_APB + 0x0854 )
#define REG_AON_APB_AON_TO_PUB_RS_LPC_CTRL           ( CTL_BASE_AON_APB + 0x0858 )
#define REG_AON_APB_CSSYS_TO_PUB_RS_LPC_CTRL         ( CTL_BASE_AON_APB + 0x085C )
#define REG_AON_APB_APCPU_TO_PUB_RS_LPC_CTRL         ( CTL_BASE_AON_APB + 0x0860 )
#define REG_AON_APB_AP_TO_PUB_RS_LPC_CTRL            ( CTL_BASE_AON_APB + 0x0864 )
#define REG_AON_APB_NRACC_TO_PUB_RS_LPC_CTRL         ( CTL_BASE_AON_APB + 0x0868 )
#define REG_AON_APB_NRCPU_TO_PUB_RS_LPC_CTRL         ( CTL_BASE_AON_APB + 0x086C )
#define REG_AON_APB_V3CPU_TO_PUB_RS_LPC_CTRL         ( CTL_BASE_AON_APB + 0x0870 )
#define REG_AON_APB_V3ACC_TO_PUB_RS_LPC_CTRL         ( CTL_BASE_AON_APB + 0x0874 )
#define REG_AON_APB_PSCP_TO_PUB_RS_LPC_CTRL          ( CTL_BASE_AON_APB + 0x0878 )
#define REG_AON_APB_AB_W_AGCP2EMC_LPC_CTRL           ( CTL_BASE_AON_APB + 0x087C )
#define REG_AON_APB_AB_W_AONSYS2EMC_LPC_CTRL         ( CTL_BASE_AON_APB + 0x0880 )
#define REG_AON_APB_AB_W_APCPU2EMC_LPC_CTRL          ( CTL_BASE_AON_APB + 0x0884 )
#define REG_AON_APB_AB_W_CSSYS2EMC_LPC_CTRL          ( CTL_BASE_AON_APB + 0x0888 )
#define REG_AON_APB_AB_W_MINIAP2EMC_LPC_CTRL         ( CTL_BASE_AON_APB + 0x088C )
#define REG_AON_APB_AB_W_NRACC2EMC_LPC_CTRL          ( CTL_BASE_AON_APB + 0x0890 )
#define REG_AON_APB_AB_W_NRCPU2EMC_LPC_CTRL          ( CTL_BASE_AON_APB + 0x0894 )
#define REG_AON_APB_AB_W_V3ACC2EMC_LPC_CTRL          ( CTL_BASE_AON_APB + 0x0898 )
#define REG_AON_APB_AB_W_V3CPU2EMC_LPC_CTRL          ( CTL_BASE_AON_APB + 0x089C )
#define REG_AON_APB_AB_W_PSCP2EMC_LPC_CTRL           ( CTL_BASE_AON_APB + 0x08A0 )
#define REG_AON_APB_AHB2AHB_ASYNC_CTRL               ( CTL_BASE_AON_APB + 0x08A4 )
#define REG_AON_APB_APCPU_ATB_CLK_DFS_CTRL           ( CTL_BASE_AON_APB + 0x08A8 )
#define REG_AON_APB_AON_APB_DFS_CTRL                 ( CTL_BASE_AON_APB + 0x08AC )
#define REG_AON_APB_AON_TO_PUB_LPC_CTRL           ( CTL_BASE_AON_APB + 0x08B0 )
#define REG_AON_APB_EAXI_TO_APCPU_LPC_CTRL           ( CTL_BASE_AON_APB + 0x08B4 )
#define REG_AON_APB_EWARLY_WAKEUP_EN                 ( CTL_BASE_AON_APB + 0x08B8 )
#define REG_AON_APB_PWR_CTRL                         ( CTL_BASE_AON_APB + 0x0A00 )
#define REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG4           ( CTL_BASE_AON_APB + 0x0A0C )
#define REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG0           ( CTL_BASE_AON_APB + 0x0A10 )
#define REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG1           ( CTL_BASE_AON_APB + 0x0A14 )
#define REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG2           ( CTL_BASE_AON_APB + 0x0A18 )
#define REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG3           ( CTL_BASE_AON_APB + 0x0A1C )
#define REG_AON_APB_PAD_DBG_BUS_SEL_CFG1             ( CTL_BASE_AON_APB + 0x0A20 )
#define REG_AON_APB_PAD_DBG_BUS_SEL_CFG2             ( CTL_BASE_AON_APB + 0x0A24 )
#define REG_AON_APB_PAD_DBG_BUS_SEL_CFG3             ( CTL_BASE_AON_APB + 0x0A28 )
#define REG_AON_APB_PAD_DBG_BUS_SEL_CFG4             ( CTL_BASE_AON_APB + 0x0A2C )
#define REG_AON_APB_PAD_DBG_BUS_SEL_CFG5             ( CTL_BASE_AON_APB + 0x0A30 )
#define REG_AON_APB_PAD_DBG_BUS_SEL_CFG6             ( CTL_BASE_AON_APB + 0x0A34 )
#define REG_AON_APB_PAD_DBG_BUS_SEL_CFG7             ( CTL_BASE_AON_APB + 0x0A38 )
#define REG_AON_APB_PAD_DBG_BUS_DATA_A               ( CTL_BASE_AON_APB + 0x0A40 )
#define REG_AON_APB_PAD_DBG_BUS_DATA_B               ( CTL_BASE_AON_APB + 0x0A44 )
#define REG_AON_APB_PAD_DBG_BUS_DATA_OUT             ( CTL_BASE_AON_APB + 0x0A48 )
#define REG_AON_APB_DBG_BUS_DATA_V3                  ( CTL_BASE_AON_APB + 0x0A4C )
#define REG_AON_APB_DBG_BUS_DATA_PSCP                ( CTL_BASE_AON_APB + 0x0A50 )
#define REG_AON_APB_DBG_BUS_DATA_AUDCP               ( CTL_BASE_AON_APB + 0x0A54 )
#define REG_AON_APB_SCC_DBG_BUS                      ( CTL_BASE_AON_APB + 0x0A58 )
#define REG_AON_APB_DEBUG_FILTER_0                   ( CTL_BASE_AON_APB + 0x0A60 )
#define REG_AON_APB_DEBUG_FILTER_1                   ( CTL_BASE_AON_APB + 0x0A64 )
#define REG_AON_APB_DEBUG_FILTER_2                   ( CTL_BASE_AON_APB + 0x0A68 )
#define REG_AON_APB_DEBUG_FILTER_3                   ( CTL_BASE_AON_APB + 0x0A6C )
#define REG_AON_APB_DEBUG_FILTER_4                   ( CTL_BASE_AON_APB + 0x0A70 )
#define REG_AON_APB_DEBUG_FILTER_5                   ( CTL_BASE_AON_APB + 0x0A74 )
#define REG_AON_APB_TPIU_DATA_TO_SERDES_SEL          ( CTL_BASE_AON_APB + 0x0A80 )
#define REG_AON_APB_MTX_BUSMON_EB                    ( CTL_BASE_AON_APB + 0x0A84 )
#define REG_AON_APB_AON_CHIP_ID0                     ( CTL_BASE_AON_APB + 0x0C00 )
#define REG_AON_APB_AON_CHIP_ID1                     ( CTL_BASE_AON_APB + 0x0C04 )
#define REG_AON_APB_AON_PLAT_ID0                     ( CTL_BASE_AON_APB + 0x0C08 )
#define REG_AON_APB_AON_PLAT_ID1                     ( CTL_BASE_AON_APB + 0x0C0C )
#define REG_AON_APB_AON_IMPL_ID                      ( CTL_BASE_AON_APB + 0x0C10 )
#define REG_AON_APB_AON_MFT_ID                       ( CTL_BASE_AON_APB + 0x0C14 )
#define REG_AON_APB_AON_VER_ID                       ( CTL_BASE_AON_APB + 0x0C18 )
#define REG_AON_APB_AON_CHIP_ID                      ( CTL_BASE_AON_APB + 0x0C1C )
#define REG_AON_APB_USER_RSV_FLAG1                   ( CTL_BASE_AON_APB + 0x0C20 )
#define REG_AON_APB_BOND_OPT0                        ( CTL_BASE_AON_APB + 0x0C30 )
#define REG_AON_APB_DEVICE_LIFE_CYCLE                ( CTL_BASE_AON_APB + 0x0C34 )
#define REG_AON_APB_RES_REG0                         ( CTL_BASE_AON_APB + 0x0C40 )
#define REG_AON_APB_RES_REG1                         ( CTL_BASE_AON_APB + 0x0C44 )
#define REG_AON_APB_CP_RFFE_RES_REG0                 ( CTL_BASE_AON_APB + 0x0D00 )
#define REG_AON_APB_CP_RFFE_RES_REG1                 ( CTL_BASE_AON_APB + 0x0D04 )
#define REG_AON_APB_CP_RFFE_RES_REG2                 ( CTL_BASE_AON_APB + 0x0D08 )
#define REG_AON_APB_CP_RFFE_RES_REG3                 ( CTL_BASE_AON_APB + 0x0D0C )
#define REG_AON_APB_CP_RFFE_RES_REG4                 ( CTL_BASE_AON_APB + 0x0D10 )
#define REG_AON_APB_CP_RFFE_RES_REG5                 ( CTL_BASE_AON_APB + 0x0D14 )

/* REG_AON_APB_APB_EB0 */

#define BIT_AON_APB_APB_BUSMON_S5_EB                            BIT(31)
#define BIT_AON_APB_AON_NR_SPI_WRAP_EB                          BIT(30)
#define BIT_AON_APB_RTM_ATB_EB                                  BIT(29)
#define BIT_AON_APB_RTM_EB                                      BIT(28)
#define BIT_AON_APB_SERDES2_EB                                  BIT(27)
#define BIT_AON_APB_SERDES1_EB                                  BIT(26)
#define BIT_AON_APB_SERDES0_EB                                  BIT(25)
#define BIT_AON_APB_SERDES_DPHY2_REF_EB                         BIT(24)
#define BIT_AON_APB_SERDES_DPHY2_CFG_EB                         BIT(23)
#define BIT_AON_APB_SERDES_DPHY1_REF_EB                         BIT(22)
#define BIT_AON_APB_SERDES_DPHY1_CFG_EB                         BIT(21)
#define BIT_AON_APB_SERDES_DPHY0_REF_EB                         BIT(20)
#define BIT_AON_APB_SERDES_DPHY0_CFG_EB                         BIT(19)
#define BIT_AON_APB_WCN_ADDA_TEST_EB                            BIT(18)
#define BIT_AON_APB_CSSYS_PUB_EB                                BIT(17)
#define BIT_AON_APB_CSSYS_APB_EB                                BIT(16)
#define BIT_AON_APB_CSSYS_EB                                    BIT(15)
#define BIT_AON_APB_APCPU_DAP_EB                                BIT(14)
#define BIT_AON_APB_DEBUG_FILTER_EB                             BIT(13)
#define BIT_AON_APB_APCPU_CSSYS_EB                              BIT(12)
#define BIT_AON_APB_PMU_APB_BUSMON_EB                           BIT(11)
#define BIT_AON_APB_SP_AHB_CLK_SOFT_EB                          BIT(10)
#define BIT_AON_APB_AON_APB_BUSMON_EB                           BIT(9)
#define BIT_AON_APB_BSM_TMR_EB                                  BIT(8)
#define BIT_AON_APB_PROBE_EB                                    BIT(7)
#define BIT_AON_APB_AUX2_EB                                     BIT(6)
#define BIT_AON_APB_AUX1_EB                                     BIT(5)
#define BIT_AON_APB_AUX0_EB                                     BIT(4)
#define BIT_AON_APB_DJTAG_EB                                    BIT(3)
#define BIT_AON_APB_DJTAG_TCK_EB                                BIT(2)
#define BIT_AON_APB_AON_SPI_WRAP_EB                             BIT(1)
#define BIT_AON_APB_RC100M_CAL_EB                               BIT(0)

/* REG_AON_APB_APB_EB1 */

#define BIT_AON_APB_SC_CC_EB                                    BIT(31)
#define BIT_AON_APB_APB_BUSMON_S3_EB                            BIT(30)
#define BIT_AON_APB_SIM_AON_TOP_V3PS2                           BIT(29)
#define BIT_AON_APB_SIM_AON_TOP_V3PS1                           BIT(28)
#define BIT_AON_APB_SIM_AON_TOP_V3PS0                           BIT(27)
#define BIT_AON_APB_APCPU_AB_EB                                 BIT(26)
#define BIT_AON_APB_AP_SPI2_EB                                  BIT(25)
#define BIT_AON_APB_AP_SPI1_EB                                  BIT(24)
#define BIT_AON_APB_AP_SPI0_EB                                  BIT(23)
#define BIT_AON_APB_APB_DIRECT_ACC_PROT_AON_APB_EB              BIT(22)
#define BIT_AON_APB_APB_DIRECT_ACC_PROT_PMU_APB_EB              BIT(21)
#define BIT_AON_APB_SCC_EB                                      BIT(20)
#define BIT_AON_APB_NIC400_AON_CFG_EB                           BIT(19)
#define BIT_AON_APB_APCPU_TS0_EB                                BIT(17)
#define BIT_AON_APB_DJTAG_CTRL_EB                               BIT(16)
#define BIT_AON_APB_AON_RFSPI_SLV_NR_EB                         BIT(15)
#define BIT_AON_APB_AON_RFSPI_SLV_V3_EB                         BIT(14)
#define BIT_AON_APB_CKG_EB                                      BIT(13)
#define BIT_AON_APB_ANA_EB                                      BIT(12)
#define BIT_AON_APB_PIN_EB                                      BIT(11)
#define BIT_AON_APB_SPLK_EB                                     BIT(10)
#define BIT_AON_APB_APCPU_CLK_EB                                BIT(8)
#define BIT_AON_APB_DVFS_TOP_EB                                 BIT(7)
#define BIT_AON_APB_AON_TMR_EB                                  BIT(6)
#define BIT_AON_APB_AP_SYST_EB                                  BIT(5)
#define BIT_AON_APB_AON_SYST_EB                                 BIT(4)
#define BIT_AON_APB_KPD_EB                                      BIT(3)
#define BIT_AON_APB_MBOX_EB                                     BIT(2)
#define BIT_AON_APB_GPIO_EB                                     BIT(1)
#define BIT_AON_APB_EFUSE_EB                                    BIT(0)

/* REG_AON_APB_APB_EB2 */

#define BIT_AON_APB_THM2_EB                                     BIT(30)
#define BIT_AON_APB_APCPU_WDG_EB                                BIT(29)
#define BIT_AON_APB_AP_WDG_EB                                   BIT(28)
#define BIT_AON_APB_AP_TMR2_EB                                  BIT(27)
#define BIT_AON_APB_AP_TMR1_EB                                  BIT(26)
#define BIT_AON_APB_AP_TMR0_EB                                  BIT(25)
#define BIT_AON_APB_NR_CP_INTC_EB                               BIT(24)
#define BIT_AON_APB_NR_DSP1_INTC_EB                             BIT(23)
#define BIT_AON_APB_NR_DSP0_INTC_EB                             BIT(22)
#define BIT_AON_APB_NR_CR8_INTC_EB                              BIT(21)
#define BIT_AON_APB_V3PHY_INTC_EB                               BIT(20)
#define BIT_AON_APB_V3PS_INTC_EB                                BIT(19)
#define BIT_AON_APB_V3MODEM_INTC_EB                             BIT(18)
#define BIT_AON_APB_PSCP_INTC_EB                                BIT(17)
#define BIT_AON_APB_AUDCP_INTC_EB                               BIT(16)
#define BIT_AON_APB_AP_INTC5_EB                                 BIT(15)
#define BIT_AON_APB_AP_INTC4_EB                                 BIT(14)
#define BIT_AON_APB_AP_INTC3_EB                                 BIT(13)
#define BIT_AON_APB_AP_INTC2_EB                                 BIT(12)
#define BIT_AON_APB_AP_INTC1_EB                                 BIT(11)
#define BIT_AON_APB_AP_INTC0_EB                                 BIT(10)
#define BIT_AON_APB_EIC_EB                                      BIT(9)
#define BIT_AON_APB_ADI_EB                                      BIT(8)
#define BIT_AON_APB_PMU_EB                                      BIT(7)
#define BIT_AON_APB_I2C_EB                                      BIT(6)
#define BIT_AON_APB_PSCP_SIM2_AON_TOP_EB                        BIT(5)
#define BIT_AON_APB_PSCP_SIM1_AON_TOP_EB                        BIT(4)
#define BIT_AON_APB_PSCP_SIM0_AON_TOP_EB                        BIT(3)
#define BIT_AON_APB_AP_SIM_AON_TOP_EB                           BIT(2)
#define BIT_AON_APB_THM1_EB                                     BIT(1)
#define BIT_AON_APB_THM0_EB                                     BIT(0)

/* REG_AON_APB_APB_RTC_EB0 */

#define BIT_AON_APB_BB_CAL_RTC_EB                               BIT(13)
#define BIT_AON_APB_DCXO_LC_RTC_EB                              BIT(12)
#define BIT_AON_APB_AP_TMR2_RTC_EB                              BIT(11)
#define BIT_AON_APB_AP_TMR1_RTC_EB                              BIT(10)
#define BIT_AON_APB_AP_TMR0_RTC_EB                              BIT(9)
#define BIT_AON_APB_APCPU_WDG_RTC_EB                            BIT(8)
#define BIT_AON_APB_AP_WDG_RTC_EB                               BIT(7)
#define BIT_AON_APB_EIC_RTCDV5_EB                               BIT(6)
#define BIT_AON_APB_EIC_RTC_EB                                  BIT(5)
#define BIT_AON_APB_AON_TMR_RTC_EB                              BIT(4)
#define BIT_AON_APB_AP_SYST_RTC_EB                              BIT(3)
#define BIT_AON_APB_AON_SYST_RTC_EB                             BIT(2)
#define BIT_AON_APB_KPD_RTC_EB                                  BIT(1)
#define BIT_AON_APB_ARCH_RTC_EB                                 BIT(0)

/* REG_AON_APB_PSCP_AON_EB */

#define BIT_AON_APB_PSCP_SYST_RTC_EB                            BIT(11)
#define BIT_AON_APB_PSCP_TMR_EB                                 BIT(10)
#define BIT_AON_APB_PSCP_TMR_RTC_EB                             BIT(9)
#define BIT_AON_APB_PSCP_SYST_EB                                BIT(8)
#define BIT_AON_APB_PSCP_WDG_EB                                 BIT(7)
#define BIT_AON_APB_PSCP_WDG_RTC_EB                             BIT(6)
#define BIT_AON_APB_PSCP_ARCH_RTC_EB                            BIT(5)
#define BIT_AON_APB_CPALL_EIC_EB                                BIT(4)
#define BIT_AON_APB_CPALL_EIC_RTCDV5_EB                         BIT(3)
#define BIT_AON_APB_CPALL_EIC_RTC_EB                            BIT(2)

/* REG_AON_APB_CGM_REG1 */

#define BIT_AON_APB_CGM_CM4_TMR2_EN                             BIT(19)
#define BIT_AON_APB_DET_32K_EB                                  BIT(18)
#define BIT_AON_APB_CGM_DEBOUNCE_EN                             BIT(17)
#define BIT_AON_APB_CGM_RC100M_FDK_EN                           BIT(16)
#define BIT_AON_APB_CGM_RC100M_REF_EN                           BIT(15)
#define BIT_AON_APB_CGM_TMR_EN                                  BIT(14)
#define BIT_AON_APB_CGM_TSEN_EN                                 BIT(13)
#define BIT_AON_APB_CGM_OTG_REF_EN                              BIT(12)
#define BIT_AON_APB_CGM_DMC_REF_EN                              BIT(11)
#define BIT_AON_APB_CGM_DPHY_REF_EN                             BIT(10)
#define BIT_AON_APB_CGM_DJTAG_TCK_EN                            BIT(9)
#define BIT_AON_APB_CGM_DSI2_TEST_EB                            BIT(8)
#define BIT_AON_APB_CGM_DSI1_TEST_EB                            BIT(7)
#define BIT_AON_APB_CGM_DSI0_TEST_EB                            BIT(6)

/* REG_AON_APB_CGM_CLK_TOP_REG1 */

#define BIT_AON_APB_SOFT_DDR0_CKG_1X_EN                         BIT(26)
#define BIT_AON_APB_SOFT_DDR0_DATA_RET                          BIT(23)
#define BIT_AON_APB_LIGHT_SLEEP_DDR0_DATA_RET_EN                BIT(21)
#define BIT_AON_APB_EMC0_CKG_SEL_LOAD                           BIT(19)
#define BIT_AON_APB_CLK_DEBUG_TS_EB                             BIT(18)
#define BIT_AON_APB_AAPC_CLK_TEST_EB                            BIT(16)
#define BIT_AON_APB_CGM_CPHY_CFG_EN                             BIT(15)
#define BIT_AON_APB_ALL_PLL_TEST_EB                             BIT(14)
#define BIT_AON_APB_CGM_NANDC_2X_EN                             BIT(11)
#define BIT_AON_APB_CGM_NANDC_1X_EN                             BIT(10)
#define BIT_AON_APB_CGM_EMMC_2X_EN                              BIT(9)
#define BIT_AON_APB_CGM_EMMC_1X_EN                              BIT(8)
#define BIT_AON_APB_CGM_SDIO2_1X_EN                             BIT(7)
#define BIT_AON_APB_CGM_SDIO2_2X_EN                             BIT(6)
#define BIT_AON_APB_CGM_SDIO1_1X_EN                             BIT(5)
#define BIT_AON_APB_CGM_SDIO1_2X_EN                             BIT(4)
#define BIT_AON_APB_CGM_SDIO0_1X_EN                             BIT(3)
#define BIT_AON_APB_CGM_SDIO0_2X_EN                             BIT(2)
#define BIT_AON_APB_CGM_APCPU_AXI_EN                            BIT(1)
#define BIT_AON_APB_CGM_CSSYS_EN                                BIT(0)

/* REG_AON_APB_APCPU_INT_ENABLE_CTRL0 */

#define BIT_AON_APB_APCPU_INT_EN_31                             BIT(31)
#define BIT_AON_APB_APCPU_INT_EN_30                             BIT(30)
#define BIT_AON_APB_APCPU_INT_EN_29                             BIT(29)
#define BIT_AON_APB_APCPU_INT_EN_28                             BIT(28)
#define BIT_AON_APB_APCPU_INT_EN_27                             BIT(27)
#define BIT_AON_APB_APCPU_INT_EN_26                             BIT(26)
#define BIT_AON_APB_APCPU_INT_EN_25                             BIT(25)
#define BIT_AON_APB_APCPU_INT_EN_24                             BIT(24)
#define BIT_AON_APB_APCPU_INT_EN_23                             BIT(23)
#define BIT_AON_APB_APCPU_INT_EN_22                             BIT(22)
#define BIT_AON_APB_APCPU_INT_EN_21                             BIT(21)
#define BIT_AON_APB_APCPU_INT_EN_20                             BIT(20)
#define BIT_AON_APB_APCPU_INT_EN_19                             BIT(19)
#define BIT_AON_APB_APCPU_INT_EN_18                             BIT(18)
#define BIT_AON_APB_APCPU_INT_EN_17                             BIT(17)
#define BIT_AON_APB_APCPU_INT_EN_16                             BIT(16)
#define BIT_AON_APB_APCPU_INT_EN_15                             BIT(15)
#define BIT_AON_APB_APCPU_INT_EN_14                             BIT(14)
#define BIT_AON_APB_APCPU_INT_EN_13                             BIT(13)
#define BIT_AON_APB_APCPU_INT_EN_12                             BIT(12)
#define BIT_AON_APB_APCPU_INT_EN_11                             BIT(11)
#define BIT_AON_APB_APCPU_INT_EN_10                             BIT(10)
#define BIT_AON_APB_APCPU_INT_EN_9                              BIT(9)
#define BIT_AON_APB_APCPU_INT_EN_8                              BIT(8)
#define BIT_AON_APB_APCPU_INT_EN_7                              BIT(7)
#define BIT_AON_APB_APCPU_INT_EN_6                              BIT(6)
#define BIT_AON_APB_APCPU_INT_EN_5                              BIT(5)
#define BIT_AON_APB_APCPU_INT_EN_4                              BIT(4)
#define BIT_AON_APB_APCPU_INT_EN_3                              BIT(3)
#define BIT_AON_APB_APCPU_INT_EN_2                              BIT(2)
#define BIT_AON_APB_APCPU_INT_EN_1                              BIT(1)
#define BIT_AON_APB_APCPU_INT_EN_0                              BIT(0)

/* REG_AON_APB_APCPU_INT_ENABLE_CTRL1 */

#define BIT_AON_APB_APCPU_INT_EN_63                             BIT(31)
#define BIT_AON_APB_APCPU_INT_EN_62                             BIT(30)
#define BIT_AON_APB_APCPU_INT_EN_61                             BIT(29)
#define BIT_AON_APB_APCPU_INT_EN_60                             BIT(28)
#define BIT_AON_APB_APCPU_INT_EN_59                             BIT(27)
#define BIT_AON_APB_APCPU_INT_EN_58                             BIT(26)
#define BIT_AON_APB_APCPU_INT_EN_57                             BIT(25)
#define BIT_AON_APB_APCPU_INT_EN_56                             BIT(24)
#define BIT_AON_APB_APCPU_INT_EN_55                             BIT(23)
#define BIT_AON_APB_APCPU_INT_EN_54                             BIT(22)
#define BIT_AON_APB_APCPU_INT_EN_53                             BIT(21)
#define BIT_AON_APB_APCPU_INT_EN_52                             BIT(20)
#define BIT_AON_APB_APCPU_INT_EN_51                             BIT(19)
#define BIT_AON_APB_APCPU_INT_EN_50                             BIT(18)
#define BIT_AON_APB_APCPU_INT_EN_49                             BIT(17)
#define BIT_AON_APB_APCPU_INT_EN_48                             BIT(16)
#define BIT_AON_APB_APCPU_INT_EN_47                             BIT(15)
#define BIT_AON_APB_APCPU_INT_EN_46                             BIT(14)
#define BIT_AON_APB_APCPU_INT_EN_45                             BIT(13)
#define BIT_AON_APB_APCPU_INT_EN_44                             BIT(12)
#define BIT_AON_APB_APCPU_INT_EN_43                             BIT(11)
#define BIT_AON_APB_APCPU_INT_EN_42                             BIT(10)
#define BIT_AON_APB_APCPU_INT_EN_41                             BIT(9)
#define BIT_AON_APB_APCPU_INT_EN_40                             BIT(8)
#define BIT_AON_APB_APCPU_INT_EN_39                             BIT(7)
#define BIT_AON_APB_APCPU_INT_EN_38                             BIT(6)
#define BIT_AON_APB_APCPU_INT_EN_37                             BIT(5)
#define BIT_AON_APB_APCPU_INT_EN_36                             BIT(4)
#define BIT_AON_APB_APCPU_INT_EN_35                             BIT(3)
#define BIT_AON_APB_APCPU_INT_EN_34                             BIT(2)
#define BIT_AON_APB_APCPU_INT_EN_33                             BIT(1)
#define BIT_AON_APB_APCPU_INT_EN_32                             BIT(0)

/* REG_AON_APB_APCPU_INT_ENABLE_CTRL2 */

#define BIT_AON_APB_APCPU_INT_EN_95                             BIT(31)
#define BIT_AON_APB_APCPU_INT_EN_94                             BIT(30)
#define BIT_AON_APB_APCPU_INT_EN_93                             BIT(29)
#define BIT_AON_APB_APCPU_INT_EN_92                             BIT(28)
#define BIT_AON_APB_APCPU_INT_EN_91                             BIT(27)
#define BIT_AON_APB_APCPU_INT_EN_90                             BIT(26)
#define BIT_AON_APB_APCPU_INT_EN_89                             BIT(25)
#define BIT_AON_APB_APCPU_INT_EN_88                             BIT(24)
#define BIT_AON_APB_APCPU_INT_EN_87                             BIT(23)
#define BIT_AON_APB_APCPU_INT_EN_86                             BIT(22)
#define BIT_AON_APB_APCPU_INT_EN_85                             BIT(21)
#define BIT_AON_APB_APCPU_INT_EN_84                             BIT(20)
#define BIT_AON_APB_APCPU_INT_EN_83                             BIT(19)
#define BIT_AON_APB_APCPU_INT_EN_82                             BIT(18)
#define BIT_AON_APB_APCPU_INT_EN_81                             BIT(17)
#define BIT_AON_APB_APCPU_INT_EN_80                             BIT(16)
#define BIT_AON_APB_APCPU_INT_EN_79                             BIT(15)
#define BIT_AON_APB_APCPU_INT_EN_78                             BIT(14)
#define BIT_AON_APB_APCPU_INT_EN_77                             BIT(13)
#define BIT_AON_APB_APCPU_INT_EN_76                             BIT(12)
#define BIT_AON_APB_APCPU_INT_EN_75                             BIT(11)
#define BIT_AON_APB_APCPU_INT_EN_74                             BIT(10)
#define BIT_AON_APB_APCPU_INT_EN_73                             BIT(9)
#define BIT_AON_APB_APCPU_INT_EN_72                             BIT(8)
#define BIT_AON_APB_APCPU_INT_EN_71                             BIT(7)
#define BIT_AON_APB_APCPU_INT_EN_70                             BIT(6)
#define BIT_AON_APB_APCPU_INT_EN_69                             BIT(5)
#define BIT_AON_APB_APCPU_INT_EN_68                             BIT(4)
#define BIT_AON_APB_APCPU_INT_EN_67                             BIT(3)
#define BIT_AON_APB_APCPU_INT_EN_66                             BIT(2)
#define BIT_AON_APB_APCPU_INT_EN_65                             BIT(1)
#define BIT_AON_APB_APCPU_INT_EN_64                             BIT(0)

/* REG_AON_APB_APCPU_INT_ENABLE_CTRL3 */

#define BIT_AON_APB_APCPU_INT_EN_127                            BIT(31)
#define BIT_AON_APB_APCPU_INT_EN_126                            BIT(30)
#define BIT_AON_APB_APCPU_INT_EN_125                            BIT(29)
#define BIT_AON_APB_APCPU_INT_EN_124                            BIT(28)
#define BIT_AON_APB_APCPU_INT_EN_123                            BIT(27)
#define BIT_AON_APB_APCPU_INT_EN_122                            BIT(26)
#define BIT_AON_APB_APCPU_INT_EN_121                            BIT(25)
#define BIT_AON_APB_APCPU_INT_EN_120                            BIT(24)
#define BIT_AON_APB_APCPU_INT_EN_119                            BIT(23)
#define BIT_AON_APB_APCPU_INT_EN_118                            BIT(22)
#define BIT_AON_APB_APCPU_INT_EN_117                            BIT(21)
#define BIT_AON_APB_APCPU_INT_EN_116                            BIT(20)
#define BIT_AON_APB_APCPU_INT_EN_115                            BIT(19)
#define BIT_AON_APB_APCPU_INT_EN_114                            BIT(18)
#define BIT_AON_APB_APCPU_INT_EN_113                            BIT(17)
#define BIT_AON_APB_APCPU_INT_EN_112                            BIT(16)
#define BIT_AON_APB_APCPU_INT_EN_111                            BIT(15)
#define BIT_AON_APB_APCPU_INT_EN_110                            BIT(14)
#define BIT_AON_APB_APCPU_INT_EN_109                            BIT(13)
#define BIT_AON_APB_APCPU_INT_EN_108                            BIT(12)
#define BIT_AON_APB_APCPU_INT_EN_107                            BIT(11)
#define BIT_AON_APB_APCPU_INT_EN_106                            BIT(10)
#define BIT_AON_APB_APCPU_INT_EN_105                            BIT(9)
#define BIT_AON_APB_APCPU_INT_EN_104                            BIT(8)
#define BIT_AON_APB_APCPU_INT_EN_103                            BIT(7)
#define BIT_AON_APB_APCPU_INT_EN_102                            BIT(6)
#define BIT_AON_APB_APCPU_INT_EN_101                            BIT(5)
#define BIT_AON_APB_APCPU_INT_EN_100                            BIT(4)
#define BIT_AON_APB_APCPU_INT_EN_99                             BIT(3)
#define BIT_AON_APB_APCPU_INT_EN_98                             BIT(2)
#define BIT_AON_APB_APCPU_INT_EN_97                             BIT(1)
#define BIT_AON_APB_APCPU_INT_EN_96                             BIT(0)

/* REG_AON_APB_APCPU_INT_ENABLE_CTRL4 */

#define BIT_AON_APB_APCPU_INT_EN_159                            BIT(31)
#define BIT_AON_APB_APCPU_INT_EN_158                            BIT(30)
#define BIT_AON_APB_APCPU_INT_EN_157                            BIT(29)
#define BIT_AON_APB_APCPU_INT_EN_156                            BIT(28)
#define BIT_AON_APB_APCPU_INT_EN_155                            BIT(27)
#define BIT_AON_APB_APCPU_INT_EN_154                            BIT(26)
#define BIT_AON_APB_APCPU_INT_EN_153                            BIT(25)
#define BIT_AON_APB_APCPU_INT_EN_152                            BIT(24)
#define BIT_AON_APB_APCPU_INT_EN_151                            BIT(23)
#define BIT_AON_APB_APCPU_INT_EN_150                            BIT(22)
#define BIT_AON_APB_APCPU_INT_EN_149                            BIT(21)
#define BIT_AON_APB_APCPU_INT_EN_148                            BIT(20)
#define BIT_AON_APB_APCPU_INT_EN_147                            BIT(19)
#define BIT_AON_APB_APCPU_INT_EN_146                            BIT(18)
#define BIT_AON_APB_APCPU_INT_EN_145                            BIT(17)
#define BIT_AON_APB_APCPU_INT_EN_144                            BIT(16)
#define BIT_AON_APB_APCPU_INT_EN_143                            BIT(15)
#define BIT_AON_APB_APCPU_INT_EN_142                            BIT(14)
#define BIT_AON_APB_APCPU_INT_EN_141                            BIT(13)
#define BIT_AON_APB_APCPU_INT_EN_140                            BIT(12)
#define BIT_AON_APB_APCPU_INT_EN_139                            BIT(11)
#define BIT_AON_APB_APCPU_INT_EN_138                            BIT(10)
#define BIT_AON_APB_APCPU_INT_EN_137                            BIT(9)
#define BIT_AON_APB_APCPU_INT_EN_136                            BIT(8)
#define BIT_AON_APB_APCPU_INT_EN_135                            BIT(7)
#define BIT_AON_APB_APCPU_INT_EN_134                            BIT(6)
#define BIT_AON_APB_APCPU_INT_EN_133                            BIT(5)
#define BIT_AON_APB_APCPU_INT_EN_132                            BIT(4)
#define BIT_AON_APB_APCPU_INT_EN_131                            BIT(3)
#define BIT_AON_APB_APCPU_INT_EN_130                            BIT(2)
#define BIT_AON_APB_APCPU_INT_EN_129                            BIT(1)
#define BIT_AON_APB_APCPU_INT_EN_128                            BIT(0)

/* REG_AON_APB_APCPU_INT_ENABLE_CTRL5 */

#define BIT_AON_APB_APCPU_INT_EN_191                            BIT(31)
#define BIT_AON_APB_APCPU_INT_EN_190                            BIT(30)
#define BIT_AON_APB_APCPU_INT_EN_189                            BIT(29)
#define BIT_AON_APB_APCPU_INT_EN_188                            BIT(28)
#define BIT_AON_APB_APCPU_INT_EN_187                            BIT(27)
#define BIT_AON_APB_APCPU_INT_EN_186                            BIT(26)
#define BIT_AON_APB_APCPU_INT_EN_185                            BIT(25)
#define BIT_AON_APB_APCPU_INT_EN_184                            BIT(24)
#define BIT_AON_APB_APCPU_INT_EN_183                            BIT(23)
#define BIT_AON_APB_APCPU_INT_EN_182                            BIT(22)
#define BIT_AON_APB_APCPU_INT_EN_181                            BIT(21)
#define BIT_AON_APB_APCPU_INT_EN_180                            BIT(20)
#define BIT_AON_APB_APCPU_INT_EN_179                            BIT(19)
#define BIT_AON_APB_APCPU_INT_EN_178                            BIT(18)
#define BIT_AON_APB_APCPU_INT_EN_177                            BIT(17)
#define BIT_AON_APB_APCPU_INT_EN_176                            BIT(16)
#define BIT_AON_APB_APCPU_INT_EN_175                            BIT(15)
#define BIT_AON_APB_APCPU_INT_EN_174                            BIT(14)
#define BIT_AON_APB_APCPU_INT_EN_173                            BIT(13)
#define BIT_AON_APB_APCPU_INT_EN_172                            BIT(12)
#define BIT_AON_APB_APCPU_INT_EN_171                            BIT(11)
#define BIT_AON_APB_APCPU_INT_EN_170                            BIT(10)
#define BIT_AON_APB_APCPU_INT_EN_169                            BIT(9)
#define BIT_AON_APB_APCPU_INT_EN_168                            BIT(8)
#define BIT_AON_APB_APCPU_INT_EN_167                            BIT(7)
#define BIT_AON_APB_APCPU_INT_EN_166                            BIT(6)
#define BIT_AON_APB_APCPU_INT_EN_165                            BIT(5)
#define BIT_AON_APB_APCPU_INT_EN_164                            BIT(4)
#define BIT_AON_APB_APCPU_INT_EN_163                            BIT(3)
#define BIT_AON_APB_APCPU_INT_EN_162                            BIT(2)
#define BIT_AON_APB_APCPU_INT_EN_161                            BIT(1)
#define BIT_AON_APB_APCPU_INT_EN_160                            BIT(0)

/* REG_AON_APB_SP_WAKEUP_MASK_EN0 */

#define BIT_AON_APB_SP_INT_REQ_BUSMON_PSCP_WAKEUP_EN            BIT(31)
#define BIT_AON_APB_SP_INT_REQ_BUSMON_AUDCP_WAKEUP_EN           BIT(30)
#define BIT_AON_APB_SP_INT_REQ_ADI_WAKEUP_EN                    BIT(29)
#define BIT_AON_APB_SP_INT_REQ_PCP_WDG_WAKEUP_EN                BIT(28)
#define BIT_AON_APB_SP_INT_REQ_PWR_DOWN_ALL_WAKEUP_EN           BIT(27)
#define BIT_AON_APB_SP_INT_REQ_PWR_UP_ALL_WAKEUP_EN             BIT(26)
#define BIT_AON_APB_SP_INT_REQ_AP_WDG_RST_WAKEUP_EN             BIT(25)
#define BIT_AON_APB_SP_INT_REQ_APCPU_WDG_RST_WAKEUP_EN          BIT(24)
#define BIT_AON_APB_SP_INT_REQ_APCPU_BUSMON_WAKEUP_EN           BIT(23)
#define BIT_AON_APB_SP_INT_REQ_PSCP_BUSMON_WAKEUP_EN            BIT(22)
#define BIT_AON_APB_SP_INT_REQ_AUDCP_BUSMON_WAKEUP_EN           BIT(21)
#define BIT_AON_APB_SP_INT_REQ_AP_SYS_BUSMON_WAKEUP_EN          BIT(20)
#define BIT_AON_APB_SP_INT_REQ_MBOX_SRC_SIPC_SP_CM4_WAKEUP_EN   BIT(18)
#define BIT_AON_APB_SP_INT_REQ_MBOX_SRC_CM4_WAKEUP_EN           BIT(17)
#define BIT_AON_APB_SP_INT_REQ_MBOX_TAR_CM4_WAKEUP_EN           BIT(16)
#define BIT_AON_APB_SP_INT_REQ_CM4_SOFT_WAKEUP_EN               BIT(15)
#define BIT_AON_APB_SP_INT_FPU_EXCEPTION_WAKEUP_EN              BIT(14)
#define BIT_AON_APB_SP_INT_REQ_EIC_GPIO_NON_LAT_WAKEUP_EN       BIT(13)
#define BIT_AON_APB_SP_INT_REQ_EIC_GPIO_LAT_WAKEUP_EN           BIT(12)
#define BIT_AON_APB_SP_INT_REQ_EIC_NON_LAT_WAKEUP_EN            BIT(11)
#define BIT_AON_APB_SP_INT_REQ_EIC_LAT_WAKEUP_EN                BIT(10)
#define BIT_AON_APB_SP_INT_REQ_CM4_DMA_WAKEUP_EN                BIT(9)
#define BIT_AON_APB_SP_INT_REQ_GPIO_WAKEUP_EN                   BIT(8)
#define BIT_AON_APB_SP_INT_REQ_CM4_SYST_WAKEUP_EN               BIT(7)
#define BIT_AON_APB_SP_INT_REQ_CM4_I2C0_SLV_WAKEUP_EN           BIT(6)
#define BIT_AON_APB_SP_INT_REQ_CM4_WDG_WAKEUP_EN                BIT(5)
#define BIT_AON_APB_SP_INT_REQ_EIC1_NON_LAT_WAKEUP_EN           BIT(4)
#define BIT_AON_APB_SP_INT_REQ_EIC1_LAT_WAKEUP_EN               BIT(3)
#define BIT_AON_APB_SP_INT_REQ_CM4_UART0_WAKEUP_EN              BIT(2)

/* REG_AON_APB_SP_WAKEUP_MASK_EN1 */

#define BIT_AON_APB_SP_INT_REQ_AUDCP_VBC_AUDRCD_WAKEUP_EN       BIT(31)
#define BIT_AON_APB_SP_INT_REQ_AUDCP_MCDT_WAKEUP_EN             BIT(30)
#define BIT_AON_APB_SP_INT_REQ_AUDCP_DMA_WAKEUP_EN              BIT(29)
#define BIT_AON_APB_SP_INT_REQ_AUDCP_CHN_START_CHN3_WAKEUP_EN   BIT(28)
#define BIT_AON_APB_SP_INT_REQ_AUDCP_CHN_START_CHN2_WAKEUP_EN   BIT(27)
#define BIT_AON_APB_SP_INT_REQ_AUDCP_CHN_START_CHN1_WAKEUP_EN   BIT(26)
#define BIT_AON_APB_SP_INT_REQ_AUDCP_CHN_START_CHN0_WAKEUP_EN   BIT(25)
#define BIT_AON_APB_SP_INT_REQ_ANA_WAKEUP_EN                    BIT(24)
#define BIT_AON_APB_SP_INT_REQ_WTLCP_LTE_WDG_RST_WAKEUP_EN      BIT(23)
#define BIT_AON_APB_SP_INT_REQ_WTLCP_TG_WDG_RST_WAKEUP_EN       BIT(22)
#define BIT_AON_APB_SP_INT_REQ_PUB_DFS_DENY_EN                  BIT(18)
#define BIT_AON_APB_SP_INT_REQ_PUB_DMC_MPU_VIO_WAKEUP_EN        BIT(17)
#define BIT_AON_APB_SP_INT_REQ_PUB_DFI_BUSMON_WAKEUP_EN         BIT(15)
#define BIT_AON_APB_SP_INT_REQ_PUB_PTM_WAKEUP_EN                BIT(14)
#define BIT_AON_APB_SP_INT_REQ_PUB_HARDWARE_DFS_EXIT_WAKEUP_EN  BIT(13)
#define BIT_AON_APB_SP_INT_REQ_PUB_DFS_COMPLETE_WAKEUP_EN       BIT(12)
#define BIT_AON_APB_SP_INT_REQ_PUB_DFS_ERROR_WAKEUP_EN          BIT(11)
#define BIT_AON_APB_SP_INT_REQ_PUB_DFS_GIVEUP_EN                BIT(10)
#define BIT_AON_APB_SP_INT_REQ_CLK_32K_DET_WAKEUP_EN            BIT(9)
#define BIT_AON_APB_SP_INT_REQ_AON_I2C_WAKEUP_EN                BIT(8)
#define BIT_AON_APB_SP_INT_REQ_THM0_WAKEUP_EN                   BIT(7)
#define BIT_AON_APB_SP_INT_REQ_PWR_UP_PUB_WAKEUP_EN             BIT(6)
#define BIT_AON_APB_SP_INT_REQ_PWR_UP_AP_WAKEUP_EN              BIT(5)
#define BIT_AON_APB_SP_INT_REQ_BUSMON_TMC_WAKEUP_EN             BIT(4)
#define BIT_AON_APB_SP_INT_REQ_BUSMON_DAP_MTX_WAKEUP_EN         BIT(3)
#define BIT_AON_APB_SP_INT_REQ_BUSMON_NR_WAKEUP_EN              BIT(2)
#define BIT_AON_APB_SP_INT_REQ_BUSMON_AP_WAKEUP_EN              BIT(1)
#define BIT_AON_APB_SP_INT_REQ_BUSMON_V3_WAKEUP_EN              BIT(0)

/* REG_AON_APB_SP_WAKEUP_MASK_EN2 */

#define BIT_AON_APB_SP_INT_REQ_DFS_VOTE_DONE_WAKEUP_EN          BIT(9)
#define BIT_AON_APB_SP_INT_REQ_THM2_WAKEUP_EN                   BIT(8)
#define BIT_AON_APB_SP_INT_REQ_THM1_WAKEUP_EN                   BIT(7)
#define BIT_AON_APB_SP_INT_REQ_CM4_TMR2_WAKEUP_EN               BIT(6)
#define BIT_AON_APB_SP_INT_REQ_CM4_TMR1_WAKEUP_EN               BIT(5)
#define BIT_AON_APB_SP_INT_REQ_CM4_TMR0_WAKEUP_EN               BIT(4)
#define BIT_AON_APB_SP_INT_REQ_EXT_RSTB_SPCPU_WAKEUP_EN         BIT(3)
#define BIT_AON_APB_SP_INT_REQ_AUDCP_WDG_RST_WAKEUP_EN          BIT(1)
#define BIT_AON_APB_SP_INT_REQ_AUDCP_VBC_AUDPLY_WAKEUP_EN       BIT(0)

/* REG_AON_APB_APB_RST0 */

#define BIT_AON_APB_V3PS_SIM2_AON_TOP_SOFT_RST                  BIT(21)
#define BIT_AON_APB_V3PS_SIM1_AON_TOP_SOFT_RST                  BIT(20)
#define BIT_AON_APB_V3PS_SIM0_AON_TOP_SOFT_RST                  BIT(19)
#define BIT_AON_APB_WCN_ADDA_TEST_SOFT_RST                      BIT(18)
#define BIT_AON_APB_RTM_SOFT_RST                                BIT(17)
#define BIT_AON_APB_SERDES2_SOFT_RST                            BIT(16)
#define BIT_AON_APB_SERDES1_SOFT_RST                            BIT(15)
#define BIT_AON_APB_SERDES0_SOFT_RST                            BIT(14)
#define BIT_AON_APB_SERDES_DPHY2_APB_SOFT_RST                   BIT(13)
#define BIT_AON_APB_SERDES_DPHY2_SOFT_RST                       BIT(12)
#define BIT_AON_APB_SERDES_DPHY1_APB_SOFT_RST                   BIT(11)
#define BIT_AON_APB_SERDES_DPHY1_SOFT_RST                       BIT(10)
#define BIT_AON_APB_SERDES_DPHY0_APB_SOFT_RST                   BIT(9)
#define BIT_AON_APB_SERDES_DPHY0_SOFT_RST                       BIT(8)
#define BIT_AON_APB_DAP_MTX_SOFT_RST                            BIT(6)
#define BIT_AON_APB_AON_NR_SPI_SOFT_RST                         BIT(4)
#define BIT_AON_APB_BB_CAL_SOFT_RST                             BIT(3)
#define BIT_AON_APB_DCXO_LC_SOFT_RST                            BIT(2)
#define BIT_AON_APB_AON_SPI_SOFT_RST                            BIT(1)
#define BIT_AON_APB_RC100M_CAL_SOFT_RST                         BIT(0)

/* REG_AON_APB_APB_RST1 */

#define BIT_AON_APB_AON_RFSPI_SLV_NR_SOFT_RST                   BIT(28)
#define BIT_AON_APB_AON_RFSPI_SLV_V3_SOFT_RST                   BIT(27)
#define BIT_AON_APB_PMU_APB_BUSMON_SOFT_RST                     BIT(26)
#define BIT_AON_APB_AON_APB_BUSMON_SOFT_RST                     BIT(25)
#define BIT_AON_APB_CSSYS_SOFT_RST                              BIT(24)
#define BIT_AON_APB_BSMTMR_SOFT_RST                             BIT(23)
#define BIT_AON_APB_APB_DIRECT_ACC_PROT_AON_APB_SOFT_RST        BIT(22)
#define BIT_AON_APB_APB_DIRECT_ACC_PROT_PMU_APB_SOFT_RST        BIT(21)
#define BIT_AON_APB_SCC_SOFT_RST                                BIT(20)
#define BIT_AON_APB_DEBUG_FILTER_SOFT_RST                       BIT(19)
#define BIT_AON_APB_APB_DIRECT_ACC_PROT_SOFT_RST                BIT(18)
#define BIT_AON_APB_APCPU_TS0_SOFT_RST                          BIT(17)
#define BIT_AON_APB_DJTAG_CTRL_SOFT_RST                         BIT(16)
#define BIT_AON_APB_SEC_32K_DET_SOFT_RST                        BIT(14)
#define BIT_AON_APB_CKG_SOFT_RST                                BIT(13)
#define BIT_AON_APB_ANA_SOFT_RST                                BIT(12)
#define BIT_AON_APB_PIN_SOFT_RST                                BIT(11)
#define BIT_AON_APB_SPLK_SOFT_RST                               BIT(10)
#define BIT_AON_APB_APCPU_CLK_SOFT_RST                          BIT(8)
#define BIT_AON_APB_DVFS_TOP_SOFT_RST                           BIT(7)
#define BIT_AON_APB_AON_TMR_SOFT_RST                            BIT(6)
#define BIT_AON_APB_AP_SYST_SOFT_RST                            BIT(5)
#define BIT_AON_APB_AON_SYST_SOFT_RST                           BIT(4)
#define BIT_AON_APB_KPD_SOFT_RST                                BIT(3)
#define BIT_AON_APB_MBOX_SOFT_RST                               BIT(2)
#define BIT_AON_APB_GPIO_SOFT_RST                               BIT(1)
#define BIT_AON_APB_EFUSE_SOFT_RST                              BIT(0)

/* REG_AON_APB_APB_RST2 */

#define BIT_AON_APB_APCPU_WDG_SOFT_RST                          BIT(31)
#define BIT_AON_APB_AP_WDG_SOFT_RST                             BIT(30)
#define BIT_AON_APB_AP_TMR2_SOFT_RST                            BIT(29)
#define BIT_AON_APB_AP_TMR1_SOFT_RST                            BIT(28)
#define BIT_AON_APB_AP_TMR0_SOFT_RST                            BIT(27)
#define BIT_AON_APB_THM2_SOFT_RST                               BIT(25)
#define BIT_AON_APB_NR_INTC_SOFT_RST                            BIT(24)
#define BIT_AON_APB_NR_DSP1_INTC_SOFT_RST                       BIT(23)
#define BIT_AON_APB_NR_DSP0_INTC_SOFT_RST                       BIT(22)
#define BIT_AON_APB_NR_CR8_INTC_SOFT_RST                        BIT(21)
#define BIT_AON_APB_V3PHY_INTC_SOFT_RST                         BIT(20)
#define BIT_AON_APB_V3PS_INTC_SOFT_RST                          BIT(19)
#define BIT_AON_APB_V3MODEM_INTC_SOFT_RST                       BIT(18)
#define BIT_AON_APB_PSCP_INTC_SOFT_RST                          BIT(17)
#define BIT_AON_APB_AUDCP_INTC_SOFT_RST                         BIT(16)
#define BIT_AON_APB_AP_INTC5_SOFT_RST                           BIT(15)
#define BIT_AON_APB_AP_INTC4_SOFT_RST                           BIT(14)
#define BIT_AON_APB_AP_INTC3_SOFT_RST                           BIT(13)
#define BIT_AON_APB_AP_INTC2_SOFT_RST                           BIT(12)
#define BIT_AON_APB_AP_INTC1_SOFT_RST                           BIT(11)
#define BIT_AON_APB_AP_INTC0_SOFT_RST                           BIT(10)
#define BIT_AON_APB_EIC_SOFT_RST                                BIT(9)
#define BIT_AON_APB_ADI_SOFT_RST                                BIT(8)
#define BIT_AON_APB_PMU_SOFT_RST                                BIT(7)
#define BIT_AON_APB_I2C_SOFT_RST                                BIT(6)
#define BIT_AON_APB_PSCP_SIM2_AON_TOP_SOFT_RST                  BIT(5)
#define BIT_AON_APB_PSCP_SIM1_AON_TOP_SOFT_RST                  BIT(4)
#define BIT_AON_APB_PSCP_SIM0_AON_TOP_SOFT_RST                  BIT(3)
#define BIT_AON_APB_AP_SIM_AON_TOP_SOFT_RST                     BIT(2)
#define BIT_AON_APB_THM1_SOFT_RST                               BIT(1)
#define BIT_AON_APB_THM0_SOFT_RST                               BIT(0)

/* REG_AON_APB_APB_RST3 */

#define BIT_AON_APB_DJTAG_SOFT_RST                              BIT(10)
#define BIT_AON_APB_DJTAG_PUB0_SOFT_RST                         BIT(9)
#define BIT_AON_APB_DJTAG_AON_SOFT_RST                          BIT(8)
#define BIT_AON_APB_DJTAG_AUDCP_SOFT_RST                        BIT(7)
#define BIT_AON_APB_DJTAG_V3_SOFT_RST                           BIT(6)
#define BIT_AON_APB_DJTAG_PSCP_SOFT_RST                         BIT(5)
#define BIT_AON_APB_DJTAG_NRCP_SOFT_RST                         BIT(4)
#define BIT_AON_APB_DJTAG_APCPU_SOFT_RST                        BIT(1)
#define BIT_AON_APB_DJTAG_AP_SOFT_RST                           BIT(0)

/* REG_AON_APB_CM4_SYS_SOFT_RST */

#define BIT_AON_APB_CM4_SYS_SOFT_RST                            BIT(4)
#define BIT_AON_APB_CM4_CORE_SOFT_RST                           BIT(0)

/* REG_AON_APB_PSCP_SOFT_RST */

#define BIT_AON_APB_PSCP_CR8_BLK_CORE_SOFT_RST                  BIT(14)
#define BIT_AON_APB_PSCP_CR8_CORE_SOFT_RST(x)                   (((x) & 0x3) << 12)
#define BIT_AON_APB_PSCP_CR8_BLK_DBG_SOFT_RST                   BIT(11)
#define BIT_AON_APB_PSCP_CR8_DBG_SOFT_RST(x)                    (((x) & 0x3) << 9)
#define BIT_AON_APB_PSCP_CR8_ETM_SOFT_RST                       BIT(8)
#define BIT_AON_APB_PSCP_CR8_MP_SOFT_RST                        BIT(7)
#define BIT_AON_APB_PSCP_CR8_CS_DBG_SOFT_RST                    BIT(6)
#define BIT_AON_APB_PSCP_TMR_SOFT_RST                           BIT(5)
#define BIT_AON_APB_PSCP_SYST_SOFT_RST                          BIT(4)
#define BIT_AON_APB_PSCP_WDG_SOFT_RST                           BIT(3)
#define BIT_AON_APB_CPALL_EIC_SOFT_RST                          BIT(2)

/* REG_AON_APB_NRCP_SOFT_RST */

#define BIT_AON_APB_NRCP_CR8_BLK_CORE_SOFT_RST                  BIT(14)
#define BIT_AON_APB_NRCP_CR8_CORE_SOFT_RST(x)                   (((x) & 0x3) << 12)
#define BIT_AON_APB_NRCP_CR8_BLK_DBG_SOFT_RST                   BIT(11)
#define BIT_AON_APB_NRCP_CR8_DBG_SOFT_RST(x)                    (((x) & 0x3) << 9)

/* REG_AON_APB_V3PS_SOFT_RST */

#define BIT_AON_APB_V3_PS_CR5_DBG_SW_RST                        BIT(2)
#define BIT_AON_APB_V3_PS_CR5_BLK_SW_RST                        BIT(1)
#define BIT_AON_APB_V3_PS_CR5_CORE_SW_RST                       BIT(0)

/* REG_AON_APB_V3PHY_SOFT_RST */

#define BIT_AON_APB_V3_PHY_CR5_DBG_SW_RST                       BIT(2)
#define BIT_AON_APB_V3_PHY_CR5_BLK_SW_RST                       BIT(1)
#define BIT_AON_APB_V3_PHY_CR5_CORE_SW_RST                      BIT(0)

/* REG_AON_APB_WDG_RST_FLAG */

#define BIT_AON_APB_AP_WDG_RST_FLAG                             BIT(9)
#define BIT_AON_APB_PCP_WDG_RST_FLAG                            BIT(8)
#define BIT_AON_APB_NR_DSP1_WDG_RST_FLAG                        BIT(7)
#define BIT_AON_APB_NR_DSP0_WDG_RST_FLAG                        BIT(6)
#define BIT_AON_APB_NR_CR8_WDG_RST_FLAG                         BIT(5)
#define BIT_AON_APB_V3_PS_CR5_WDG_RST_FLAG                      BIT(4)
#define BIT_AON_APB_V3_PHY_CR5_WDG_RST_FLAG                     BIT(3)
#define BIT_AON_APB_AUDCP_WDG_RST_FLAG                          BIT(2)
#define BIT_AON_APB_APCPU_WDG_RST_FLAG                          BIT(1)
#define BIT_AON_APB_SEC_WDG_RST_FLAG                            BIT(0)

/* REG_AON_APB_APCPU_SOFT_RST */

#define BIT_AON_APB_APCPU_CSSYS_APB_SOFT_RST                    BIT(10)
#define BIT_AON_APB_APCPU_CSSYS_SOFT_RST                        BIT(9)
#define BIT_AON_APB_APCPU_SCU_SOFT_RST                          BIT(8)
#define BIT_AON_APB_APCPU_DEBUG_APB_SOFT_RST                    BIT(7)
#define BIT_AON_APB_APCPU_PERIPH_SOFT_RST                       BIT(6)
#define BIT_AON_APB_APCPU_GIC_SOFT_RST                          BIT(5)
#define BIT_AON_APB_APCPU_ATB_SOFT_RST                          BIT(4)
#define BIT_AON_APB_APCPU_CORE_SOFT_RST(x)                      (((x) & 0x3))

/* REG_AON_APB_BOOT_MODE */

#define BIT_AON_APB_PTEST_FUNC_ATSPEED_SEL                      BIT(8)
#define BIT_AON_APB_PTEST_FUNC_MODE                             BIT(7)
#define BIT_AON_APB_FUNCTST_DMA_EB                              BIT(6)
#define BIT_AON_APB_PTEST_BIST_MODE                             BIT(5)
#define BIT_AON_APB_USB_DLOAD_EN                                BIT(4)
#define BIT_AON_APB_ARM_BOOT_MD3                                BIT(3)
#define BIT_AON_APB_ARM_BOOT_MD2                                BIT(2)
#define BIT_AON_APB_ARM_BOOT_MD1                                BIT(1)
#define BIT_AON_APB_ARM_BOOT_MD0                                BIT(0)

/* REG_AON_APB_CP_ARM_JTAG_CTRL */

#define BIT_AON_APB_AGCP_DSP_JTAG_MODE                          BIT(3)
#define BIT_AON_APB_CP_ARM_JTAG_PIN_SEL(x)                      (((x) & 0x7))

/* REG_AON_APB_RC100M_CFG */

#define BIT_AON_APB_RTC_CAL_CTL(x)                              (((x) & 0x7F) << 22)
#define BIT_AON_APB_RTC_CAL_SEL                                 BIT(21)
#define BIT_AON_APB_RTC_CAL_PRECISION(x)                        (((x) & 0xFF) << 13)
#define BIT_AON_APB_RC100M_DIV(x)                               (((x) & 0x3F) << 7)
#define BIT_AON_APB_RC100M_CAL_DONE                             BIT(6)
#define BIT_AON_APB_RC100M_CAL_START                            BIT(5)
#define BIT_AON_APB_RC100M_ANA_SOFT_RST                         BIT(4)
#define BIT_AON_APB_RC100M_FORCE_EN                             BIT(1)
#define BIT_AON_APB_RC100M_AUTO_GATE_EN                         BIT(0)

/* REG_AON_APB_CCIR_RCVR_CFG */

#define BIT_AON_APB_ANALOG_PLL_RSV(x)                           (((x) & 0xFFFF) << 16)
#define BIT_AON_APB_ANALOG_TESTMUX(x)                           (((x) & 0xFFFF))

/* REG_AON_APB_PLL_BG_CFG */

#define BIT_AON_APB_PLL_BG_RSV(x)                               (((x) & 0x3F))

/* REG_AON_APB_MBIST_EFUSE_CTRL */

#define BIT_AON_APB_FUSEBOX_SEL_CTRL                            BIT(1)
#define BIT_AON_APB_FUSEBOX_SEL_BUF_SW                          BIT(0)

/* REG_AON_APB_OTG_PHY_TEST */

#define BIT_AON_APB_OTG_ATERESET                                BIT(31)
#define BIT_AON_APB_OTG_VBUS_VALID_PHYREG                       BIT(24)
#define BIT_AON_APB_OTG_VBUS_VALID_PHYREG_SEL                   BIT(23)
#define BIT_AON_APB_OTG_VBUS_VALID_EXT                          BIT(22)
#define BIT_AON_APB_OTG_TESTBURNIN                              BIT(21)
#define BIT_AON_APB_OTG_LOOPBACKENB                             BIT(20)
#define BIT_AON_APB_OTG_TESTDATAOUT(x)                          (((x) & 0xF) << 16)
#define BIT_AON_APB_OTG_VATESTENB(x)                            (((x) & 0x3) << 14)
#define BIT_AON_APB_OTG_TESTCLK                                 BIT(13)
#define BIT_AON_APB_OTG_TESTDATAOUTSEL                          BIT(12)
#define BIT_AON_APB_OTG_TESTADDR(x)                             (((x) & 0xF) << 8)
#define BIT_AON_APB_OTG_TESTDATAIN(x)                           (((x) & 0xFF))

/* REG_AON_APB_OTG_PHY_CTRL */

#define BIT_AON_APB_USB2_CON_TESTMODE                           BIT(31)
#define BIT_AON_APB_UTMI_WIDTH_SEL                              BIT(30)
#define BIT_AON_APB_USB2_DATABUS16_8                            BIT(29)
#define BIT_AON_APB_OTG_SS_SCALEDOWNMODE(x)                     (((x) & 0x3) << 25)
#define BIT_AON_APB_OTG_TXBITSTUFFENH                           BIT(23)
#define BIT_AON_APB_OTG_TXBITSTUFFEN                            BIT(22)
#define BIT_AON_APB_OTG_DMPULLDOWN                              BIT(21)
#define BIT_AON_APB_OTG_DPPULLDOWN                              BIT(20)
#define BIT_AON_APB_OTG_DMPULLUP                                BIT(9)
#define BIT_AON_APB_OTG_COMMONONN                               BIT(8)
#define BIT_AON_APB_USB2_PHY_IDDIG                              BIT(3)
#define BIT_AON_APB_OTG_FSEL(x)                                 (((x) & 0x7))

/* REG_AON_APB_OTG_CTRL0 */

#define BIT_AON_APB_USB20_TUNEHSAMP(x)                          (((x) & 0x3) << 30)
#define BIT_AON_APB_USB20_TUNEPLLS(x)                           (((x) & 0x3) << 28)
#define BIT_AON_APB_USB20_TUNERISE(x)                           (((x) & 0x3) << 26)
#define BIT_AON_APB_USB20_TUNEDSC(x)                            (((x) & 0x3) << 24)
#define BIT_AON_APB_USB20_TUNEOTG(x)                            (((x) & 0x7) << 21)
#define BIT_AON_APB_USB20_TUNESQ(x)                             (((x) & 0xF) << 17)
#define BIT_AON_APB_USB20_RESERVED(x)                           (((x) & 0xFFFF))

/* REG_AON_APB_OTG_CTRL1 */

#define BIT_AON_APB_USB20_BIST_MODE(x)                          (((x) & 0x1F) << 23)
#define BIT_AON_APB_USB20_BYPASS_DRV_DM                         BIT(22)
#define BIT_AON_APB_USB20_BYPASS_DRV_DP                         BIT(21)
#define BIT_AON_APB_USB20_SAMPLER_SEL                           BIT(20)
#define BIT_AON_APB_HSIC_PLLON                                  BIT(16)
#define BIT_AON_APB_USB20_REXTENABLE                            BIT(15)
#define BIT_AON_APB_USB20_S_ID                                  BIT(14)
#define BIT_AON_APB_USB20_TFREGRES(x)                           (((x) & 0x3F) << 8)
#define BIT_AON_APB_USB20_TFHSRES(x)                            (((x) & 0x1F) << 3)
#define BIT_AON_APB_USB20_TUNEEQ(x)                             (((x) & 0x7))

/* REG_AON_APB_USB_CLK_REF_SEL */

#define BIT_AON_APB_USB_REF_CLK_MUX_SEL                         BIT(0)

/* REG_AON_APB_V3_LVDSRF_CTRL */

#define BIT_AON_APB_V3_LVDSRF_ISO_EN                            BIT(2)
#define BIT_AON_APB_V3_LVDSRF_PD_PD_L                           BIT(1)
#define BIT_AON_APB_V3_LVDSRF_PS_PD_S                           BIT(0)

/* REG_AON_APB_NR_LVDSRF_CTRL */

#define BIT_AON_APB_NR_LVDSRF_ISO_EN                            BIT(2)
#define BIT_AON_APB_NR_LVDSRF_PD_PD_L                           BIT(1)
#define BIT_AON_APB_NR_LVDSRF_PS_PD_S                           BIT(0)

/* REG_AON_APB_WCN_ADDA_MEM_PD_CTRL */

#define BIT_AON_APB_RAM_LS_WCN_ADDA_TEST_0                      BIT(2)
#define BIT_AON_APB_RAM_RET_WCN_ADDA_TEST_0                     BIT(1)
#define BIT_AON_APB_RAM_PD_WCN_ADDA_TEST_0                      BIT(0)

/* REG_AON_APB_THM0_CTRL */

#define BIT_AON_APB_THM0_CALI_RSVD(x)                           (((x) & 0xFF))

/* REG_AON_APB_THM1_CTRL */

#define BIT_AON_APB_THM1_CALI_RSVD(x)                           (((x) & 0xFF))

/* REG_AON_APB_OVERHEAT_CTRL */

#define BIT_AON_APB_THM2_INT_ADIE_EN                            BIT(10)
#define BIT_AON_APB_THM1_INT_ADIE_EN                            BIT(9)
#define BIT_AON_APB_THM0_INT_ADIE_EN                            BIT(8)
#define BIT_AON_APB_THM2_OVERHEAT_ALARM_ADIE_EN                 BIT(6)
#define BIT_AON_APB_THM1_OVERHEAT_ALARM_ADIE_EN                 BIT(5)
#define BIT_AON_APB_THM0_OVERHEAT_ALARM_ADIE_EN                 BIT(4)
#define BIT_AON_APB_THM2_OVERHEAT_RST_DDIE_EN                   BIT(2)
#define BIT_AON_APB_THM1_OVERHEAT_RST_DDIE_EN                   BIT(1)
#define BIT_AON_APB_THM0_OVERHEAT_RST_DDIE_EN                   BIT(0)

/* REG_AON_APB_MPLL0_CTRL */

#define BIT_AON_APB_CGM_MPLL0_APCPU_FORCE_EN                    BIT(9)
#define BIT_AON_APB_CGM_MPLL0_APCPU_AUTO_GATE_SEL               BIT(8)
#define BIT_AON_APB_MPLL0_WAIT_FORCE_EN                         BIT(2)
#define BIT_AON_APB_MPLL0_WAIT_AUTO_GATE_SEL                    BIT(1)
#define BIT_AON_APB_MPLL0_SOFT_CNT_DONE                         BIT(0)

/* REG_AON_APB_MPLL1_CTRL */

#define BIT_AON_APB_CGM_MPLL1_APCPU_FORCE_EN                    BIT(9)
#define BIT_AON_APB_CGM_MPLL1_APCPU_AUTO_GATE_SEL               BIT(8)
#define BIT_AON_APB_MPLL1_WAIT_FORCE_EN                         BIT(2)
#define BIT_AON_APB_MPLL1_WAIT_AUTO_GATE_SEL                    BIT(1)
#define BIT_AON_APB_MPLL1_SOFT_CNT_DONE                         BIT(0)

/* REG_AON_APB_NR_RPLL_CTRL_REG2 */

#define BIT_AON_APB_NR_RPLL_POSTDIV_REG                         BIT(20)
#define BIT_AON_APB_NR_RPLL_26M_DIV_REG(x)                      (((x) & 0x3F) << 14)
#define BIT_AON_APB_NR_RPLL_N_REG(x)                            (((x) & 0x7FF) << 3)
#define BIT_AON_APB_NR_RPLL_DIV_S_REG                           BIT(2)
#define BIT_AON_APB_NR_RPLL_MOD_EN_REG                          BIT(1)
#define BIT_AON_APB_NR_RPLL_SDM_EN_REG                          BIT(0)

/* REG_AON_APB_DPLL_CTRL */

#define BIT_AON_APB_CGM_DPLL1_1600M_PUB_FORCE_EN                BIT(9)
#define BIT_AON_APB_CGM_DPLL0_2666M_PUB_FORCE_EN                BIT(8)
#define BIT_AON_APB_CGM_DPLL1_1600M_PUB_AUTO_GATE_SEL           BIT(7)
#define BIT_AON_APB_CGM_DPLL0_2666M_PUB_AUTO_GATE_SEL           BIT(6)
#define BIT_AON_APB_DPLL1_WAIT_FORCE_EN                         BIT(5)
#define BIT_AON_APB_DPLL0_WAIT_FORCE_EN                         BIT(4)
#define BIT_AON_APB_DPLL1_WAIT_AUTO_GATE_SEL                    BIT(3)
#define BIT_AON_APB_DPLL0_WAIT_AUTO_GATE_SEL                    BIT(2)
#define BIT_AON_APB_DPLL1_SOFT_CNT_DONE                         BIT(1)
#define BIT_AON_APB_DPLL0_SOFT_CNT_DONE                         BIT(0)

/* REG_AON_APB_PLL_LOCK_OUT_SEL */

#define BIT_AON_APB_REC_26MHZ_0_BUF_PD                          BIT(8)
#define BIT_AON_APB_SLEEP_PLLLOCK_SEL                           BIT(7)
#define BIT_AON_APB_PLL_LOCK_SEL(x)                             (((x) & 0x7) << 4)
#define BIT_AON_APB_SLEEP_DBG_SEL(x)                            (((x) & 0xF))

/* REG_AON_APB_SINDRV_POWER_CTRL */

#define BIT_AON_APB_R2G_ANALOG_BB_TOP_SINDRV_2_ENA_ADC          BIT(19)
#define BIT_AON_APB_R2G_ANALOG_BB_TOP_SINDRV_2_ENA_DVFS         BIT(18)
#define BIT_AON_APB_R2G_ANALOG_BB_TOP_SINDRV_2_ENA_CAL          BIT(17)
#define BIT_AON_APB_R2G_ANALOG_BB_TOP_SINDRV_1_ENA_ADC          BIT(16)
#define BIT_AON_APB_R2G_ANALOG_BB_TOP_SINDRV_1_ENA_DVFS         BIT(15)
#define BIT_AON_APB_R2G_ANALOG_BB_TOP_SINDRV_1_ENA_CAL          BIT(14)
#define BIT_AON_APB_R2G_ANALOG_BB_TOP_SINDRV_0_ENA_ADC          BIT(13)
#define BIT_AON_APB_R2G_ANALOG_BB_TOP_SINDRV_0_ENA_DVFS         BIT(12)
#define BIT_AON_APB_R2G_ANALOG_BB_TOP_SINDRV_0_ENA_CAL          BIT(11)
#define BIT_AON_APB_ANALOG_BB_TOP_SINDRV_2_ENA_AUTO_EN          BIT(10)
#define BIT_AON_APB_R2G_ANALOG_BB_TOP_SINDRV_2_ENA              BIT(9)
#define BIT_AON_APB_ANALOG_BB_TOP_SINDRV_1_ENA_AUTO_EN          BIT(8)
#define BIT_AON_APB_R2G_ANALOG_BB_TOP_SINDRV_1_ENA              BIT(7)
#define BIT_AON_APB_ANALOG_BB_TOP_SINDRV_0_ENA_AUTO_EN          BIT(6)
#define BIT_AON_APB_R2G_ANALOG_BB_TOP_SINDRV_0_ENA              BIT(5)
#define BIT_AON_APB_M2G_ANALOG_BB_TOP_SINDRV_ENA                BIT(4)
#define BIT_AON_APB_R2G_ANALOG_BB_TOP_SINDRV_ENA_SQUARE         BIT(3)
#define BIT_AON_APB_C2G_ANALOG_BB_TOP_CLK26MHZ_AUD_EN           BIT(2)
#define BIT_AON_APB_C2G_ANALOG_USB20_USB20_PS_PD_S              BIT(1)
#define BIT_AON_APB_C2G_ANALOG_USB20_USB20_PS_PD_L              BIT(0)

/* REG_AON_APB_PHY_REF_CLK_EN */

#define BIT_AON_APB_PCIE_PHY_REF_CLK_EN                         BIT(9)
#define BIT_AON_APB_DSI_2_PHY_REF_CLK_EN                        BIT(8)
#define BIT_AON_APB_DSI_1_PHY_REF_CLK_EN                        BIT(7)
#define BIT_AON_APB_DSI_0_PHY_REF_CLK_EN                        BIT(6)
#define BIT_AON_APB_U3_1_PHY_SUSPEND_CLK_EN                     BIT(5)
#define BIT_AON_APB_U3_1_PHY_REF_CLK_EN                         BIT(4)
#define BIT_AON_APB_U3_0_PHY_SUSPEND_CLK_EN                     BIT(3)
#define BIT_AON_APB_U3_0_PHY_REF_CLK_EN                         BIT(2)
#define BIT_AON_APB_U2_1_PHY_REF_CLK_EN                         BIT(1)
#define BIT_AON_APB_U2_0_PHY_REF_CLK_EN                         BIT(0)

/* REG_AON_APB_RPLL_CTL_SEL */

#define BIT_AON_APB_R2G_NR_RPLL_RST_SEL_SPI_AFC_OR_PMU          BIT(3)
#define BIT_AON_APB_R2G_NR_RPLL_PD_SEL_SPI_AFC_OR_PMU           BIT(2)
#define BIT_AON_APB_R2G_V3_RPLL_RST_SEL_SPI_AFC_OR_PMU          BIT(1)
#define BIT_AON_APB_R2G_V3_RPLL_PD_SEL_SPI_AFC_OR_PMU           BIT(0)

/* REG_AON_APB_V3_RPLL_CTRL_REG0 */

#define BIT_AON_APB_V3_RPLL_FREQ_DOUBEL_EN_REG                  BIT(30)
#define BIT_AON_APB_V3_RPLL_CP_OFFSET_REG(x)                    (((x) & 0x3) << 28)
#define BIT_AON_APB_V3_RPLL_VSET_REG(x)                         (((x) & 0x7) << 25)
#define BIT_AON_APB_V3_RPLL_FBDIV_EN_REG                        BIT(24)
#define BIT_AON_APB_V3_RPLL_VCO_TEST_EN_REG                     BIT(23)
#define BIT_AON_APB_V3_RPLL_LDO_TRIM_REG(x)                     (((x) & 0xF) << 19)
#define BIT_AON_APB_V3_RPLL_CP_EN_REG                           BIT(18)
#define BIT_AON_APB_V3_RPLL_ICP_REG(x)                          (((x) & 0x7) << 15)
#define BIT_AON_APB_V3_RPLL_SCC_CTRL_REG(x)                     (((x) & 0xFF) << 7)
#define BIT_AON_APB_V3_RPLL_REF_SEL_REG(x)                      (((x) & 0x3) << 5)
#define BIT_AON_APB_V3_RPLL_LPF_REG(x)                          (((x) & 0x7) << 2)
#define BIT_AON_APB_V3_RPLL_IBIAS_REG(x)                        (((x) & 0x3))

/* REG_AON_APB_V3_RPLL_CTRL_REG1 */

#define BIT_AON_APB_V3_RPLL_RESERVED_REG(x)                     (((x) & 0x1FFFFF))

/* REG_AON_APB_V3_RPLL_CTRL_REG2 */

#define BIT_AON_APB_V3_RPLL_POSTDIV_REG                         BIT(20)
#define BIT_AON_APB_V3_RPLL_26M_DIV_REG(x)                      (((x) & 0x3F) << 14)
#define BIT_AON_APB_V3_RPLL_N_REG(x)                            (((x) & 0x7FF) << 3)
#define BIT_AON_APB_V3_RPLL_DIV_S_REG                           BIT(2)
#define BIT_AON_APB_V3_RPLL_MOD_EN_REG                          BIT(1)
#define BIT_AON_APB_V3_RPLL_SDM_EN_REG                          BIT(0)

/* REG_AON_APB_V3_RPLL_CTRL_REG3 */

#define BIT_AON_APB_V3_RPLL_KINT_REG(x)                         (((x) & 0x7FFFFF) << 7)
#define BIT_AON_APB_V3_RPLL_NINT_REG(x)                         (((x) & 0x7F))

/* REG_AON_APB_V3_RPLL_CTRL_SEL */

#define BIT_AON_APB_V3_RPLL_CTRL_SEL_AON_BB_SW_RFSPI            BIT(8)
#define BIT_AON_APB_V3_RPLL_CTRL_SEL_AON_APB                    BIT(0)

/* REG_AON_APB_NR_RPLL_CTRL_REG0 */

#define BIT_AON_APB_NR_RPLL_FREQ_DOUBEL_EN_REG                  BIT(30)
#define BIT_AON_APB_NR_RPLL_CP_OFFSET_REG(x)                    (((x) & 0x3) << 28)
#define BIT_AON_APB_NR_RPLL_VSET_REG(x)                         (((x) & 0x7) << 25)
#define BIT_AON_APB_NR_RPLL_FBDIV_EN_REG                        BIT(24)
#define BIT_AON_APB_NR_RPLL_VCO_TEST_EN_REG                     BIT(23)
#define BIT_AON_APB_NR_RPLL_LDO_TRIM_REG(x)                     (((x) & 0xF) << 19)
#define BIT_AON_APB_NR_RPLL_CP_EN_REG                           BIT(18)
#define BIT_AON_APB_NR_RPLL_ICP_REG(x)                          (((x) & 0x7) << 15)
#define BIT_AON_APB_NR_RPLL_SCC_CTRL_REG(x)                     (((x) & 0xFF) << 7)
#define BIT_AON_APB_NR_RPLL_REF_SEL_REG(x)                      (((x) & 0x3) << 5)
#define BIT_AON_APB_NR_RPLL_LPF_REG(x)                          (((x) & 0x7) << 2)
#define BIT_AON_APB_NR_RPLL_IBIAS_REG(x)                        (((x) & 0x3))

/* REG_AON_APB_NR_RPLL_CTRL_REG1 */

#define BIT_AON_APB_NR_RPLL_RESERVED_REG(x)                     (((x) & 0x1FFFFF))

/* REG_AON_APB_NR_RPLL_CTRL_REG3 */

#define BIT_AON_APB_NR_RPLL_KINT_REG(x)                         (((x) & 0x7FFFFF) << 7)
#define BIT_AON_APB_NR_RPLL_NINT_REG(x)                         (((x) & 0x7F))

/* REG_AON_APB_NR_RPLL_CTRL_SEL */

#define BIT_AON_APB_NR_RPLL_CTRL_SEL_BB_SW_SPI                  BIT(8)
#define BIT_AON_APB_NR_RPLL_CTRL_SEL_AON_APB                    BIT(0)

/* REG_AON_APB_RFSPI_SEL */

#define BIT_AON_APB_RFSPI_SEL_AON_NR_RFSPI                      BIT(1)
#define BIT_AON_APB_RFSPI_SEL_AON_RFSPI                         BIT(0)

/* REG_AON_APB_BB_SW_RFSPI_FIFO_STATS */

#define BIT_AON_APB_NR_BB_SW_RFSPI_FIFO1_FULL                   BIT(11)
#define BIT_AON_APB_NR_BB_SW_RFSPI_FIFO1_EMPTY                  BIT(10)
#define BIT_AON_APB_NR_BB_SW_RFSPI_FIFO0_FULL                   BIT(9)
#define BIT_AON_APB_NR_BB_SW_RFSPI_FIFO0_EMPTY                  BIT(8)
#define BIT_AON_APB_V3_BB_SW_RFSPI_FIFO1_FULL                   BIT(3)
#define BIT_AON_APB_V3_BB_SW_RFSPI_FIFO1_EMPTY                  BIT(2)
#define BIT_AON_APB_V3_BB_SW_RFSPI_FIFO0_FULL                   BIT(1)
#define BIT_AON_APB_V3_BB_SW_RFSPI_FIFO0_EMPTY                  BIT(0)

/* REG_AON_APB_RPLL_PD_RST_SEL */

#define BIT_AON_APB_NR_RPLL_RST_SEL_SPI_AFC                     BIT(3)
#define BIT_AON_APB_NR_RPLL_PD_SEL_SPI_AFC                      BIT(2)
#define BIT_AON_APB_V3_RPLL_RST_SEL_SPI_AFC                     BIT(1)
#define BIT_AON_APB_V3_RPLL_PD_SEL_SPI_AFC                      BIT(0)

/* REG_AON_APB_CLK_AUD26M_EN */

#define BIT_AON_APB_CLK_AUD26M_EN_DVFS_AUDIO                    BIT(4)
#define BIT_AON_APB_CLK_AUD26M_EN_DVFS_CP_ADC                   BIT(3)
#define BIT_AON_APB_CLK_AUD26M_EN_AP_ADC                        BIT(2)
#define BIT_AON_APB_CLK_AUD26M_EN_CALIBRATION                   BIT(1)
#define BIT_AON_APB_CLK_AUD26M_EN_DVFS                          BIT(0)

/* REG_AON_APB_TS_CFG */

#define BIT_AON_APB_DBG_TRACE_CTRL_EN                           BIT(16)
#define BIT_AON_APB_EVENTACK_RESTARTREQ_TS01                    BIT(4)
#define BIT_AON_APB_EVENT_RESTARTREQ_TS01                       BIT(1)
#define BIT_AON_APB_EVENT_HALTREQ_TS01                          BIT(0)

/* REG_AON_APB_DCXO_LC_REG0 */

#define BIT_AON_APB_DCXO_LC_FLAG                                BIT(8)
#define BIT_AON_APB_DCXO_LC_FLAG_CLR                            BIT(1)
#define BIT_AON_APB_DCXO_LC_CNT_CLR                             BIT(0)

/* REG_AON_APB_DCXO_LC_REG1 */

#define BIT_AON_APB_DCXO_LC_CNT(x)                              (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AUDCP_BOOT_PROT */

#define BIT_AON_APB_AUDCP_BOOTCTRL_PROT                         BIT(31)
#define BIT_AON_APB_AUDCP_REG_PROT_VAL(x)                       (((x) & 0xFFFF))

/* REG_AON_APB_NR_DSP0_REG_PROT */

#define BIT_AON_APB_NR_DSP0_CTRL_PROT                           BIT(31)
#define BIT_AON_APB_NR_DSP0_REG_PROT_VAL(x)                     (((x) & 0xFFFF))

/* REG_AON_APB_NR_DSP1_REG_PROT */

#define BIT_AON_APB_NR_DSP1_CTRL_PROT                           BIT(31)
#define BIT_AON_APB_NR_DSP1_REG_PROT_VAL(x)                     (((x) & 0xFFFF))

/* REG_AON_APB_DAP_DJTAG_SEL */

#define BIT_AON_APB_DAP_DBGPWRUP_SOFT_EN                        BIT(2)
#define BIT_AON_APB_DAP_SYSPWRUP_SOFT_EN                        BIT(1)
#define BIT_AON_APB_DAP_DJTAG_EN                                BIT(0)

/* REG_AON_APB_SP_CFG_BUS */

#define BIT_AON_APB_SP_AHB_CLK_SOFT_EN                          BIT(7)
#define BIT_AON_APB_CM4_SLEEPING_STAT                           BIT(6)
#define BIT_AON_APB_CM4_LOCKUP_STAT                             BIT(5)
#define BIT_AON_APB_CM4_SOFT_MPUDIS                             BIT(4)
#define BIT_AON_APB_MMTX_SLEEP_CM4_PUB_WR                       BIT(3)
#define BIT_AON_APB_MMTX_SLEEP_CM4_PUB_RD                       BIT(2)
#define BIT_AON_APB_INT_REQ_CM4_SOFT                            BIT(1)
#define BIT_AON_APB_SP_CFG_BUS_SLEEP                            BIT(0)

/* REG_AON_APB_AON_FUNC_CTRL_0 */

#define BIT_AON_APB_AON_FUNC_CTRL_0(x)                          (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AON_FUNC_CTRL_1 */

#define BIT_AON_APB_AON_FUNC_CTRL_1(x)                          (((x) & 0xFFFFFFFF))

/* REG_AON_APB_FUNC_TEST_BOOT_ADDR */

#define BIT_AON_APB_FUNC_TEST_BOOT_ADDR(x)                      (((x) & 0xFFFFFFFF))

/* REG_AON_APB_LEAKAGE_MAGIC_WORD */

#define BIT_AON_APB_LEAKAGE_MAGIC_WORD(x)                       (((x) & 0xFFFFFFFF))

/* REG_AON_APB_LEAKAGE_SWITCH */

#define BIT_AON_APB_LEAKAGE_SWITCH                              BIT(0)

/* REG_AON_APB_AUDCP_DSP_CTRL0 */

#define BIT_AON_APB_AUDCP_DSP_BOOT_VECTOR(x)                    (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AUDCP_DSP_CTRL1 */

#define BIT_AON_APB_AUDCP_STCK_DSP                              BIT(13)
#define BIT_AON_APB_AUDCP_STMS_DSP                              BIT(12)
#define BIT_AON_APB_AUDCP_STDO_DSP                              BIT(11)
#define BIT_AON_APB_AUDCP_STDI_DSP                              BIT(10)
#define BIT_AON_APB_AUDCP_STRTCK_DSP                            BIT(9)
#define BIT_AON_APB_AUDCP_SW_JTAG_ENA_DSP                       BIT(8)
#define BIT_AON_APB_AUDCP_DSP_EXTERNAL_WAIT                     BIT(1)
#define BIT_AON_APB_AUDCP_DSP_BOOT                              BIT(0)

/* REG_AON_APB_AUDCP_CTRL */

#define BIT_AON_APB_NR_DSP1_2_AUD_ACCESS_EN                     BIT(9)
#define BIT_AON_APB_NR_DSP0_2_AUD_ACCESS_EN                     BIT(8)
#define BIT_AON_APB_NR_CR8_2_AUD_ACCESS_EN                      BIT(7)
#define BIT_AON_APB_CM4_2_AUD_ACCESS_EN                         BIT(6)
#define BIT_AON_APB_AP_2_AUD_ACCESS_EN                          BIT(5)
#define BIT_AON_APB_PS_CR8_2_AUD_ACCESS_EN                      BIT(4)
#define BIT_AON_APB_V3PS_CR5_2_AUD_ACCESS_EN                    BIT(3)
#define BIT_AON_APB_V3PHY_CR8_2_AUD_ACCESS_EN                   BIT(2)
#define BIT_AON_APB_AUDCP_FRC_CLK_DSP_EN                        BIT(1)
#define BIT_AON_APB_TOP_2_AUD_ACCESS_EN                         BIT(0)

/* REG_AON_APB_V3_CTRL */

#define BIT_AON_APB_V3_AON_FRC_WSYS_LT_STOP                     BIT(4)
#define BIT_AON_APB_V3_AON_FRC_WSYS_STOP                        BIT(3)
#define BIT_AON_APB_V3_DSP_DEEP_SLEEP_EN                        BIT(2)

/* REG_AON_APB_V3_CR5_CTRL */

#define BIT_AON_APB_V3PHY_CR5_SLBTCMSB                          BIT(14)
#define BIT_AON_APB_V3PHY_CR5_TEINIT                            BIT(13)
#define BIT_AON_APB_V3PHY_CR5_CFGNMFI0                          BIT(12)
#define BIT_AON_APB_V3PHY_CR5_CFGIE                             BIT(11)
#define BIT_AON_APB_V3PHY_CR5_CFGEE                             BIT(10)
#define BIT_AON_APB_V3PHY_CR5_DBGNOCLKSTOP                      BIT(9)
#define BIT_AON_APB_V3PHY_CR5_NCPUHALT0                         BIT(8)
#define BIT_AON_APB_V3PS_CR5_TEINIT                             BIT(5)
#define BIT_AON_APB_V3PS_CR5_CFGNMFI0                           BIT(4)
#define BIT_AON_APB_V3PS_CR5_CFGIE                              BIT(3)
#define BIT_AON_APB_V3PS_CR5_CFGEE                              BIT(2)
#define BIT_AON_APB_V3PS_CR5_DBGNOCLKSTOP                       BIT(1)
#define BIT_AON_APB_V3PS_CR5_NCPUHALT0                          BIT(0)

/* REG_AON_APB_V3PS_CR5_CTRL_1 */

#define BIT_AON_APB_V3PS_CR5_AXI_VP_BASE(x)                     (((x) & 0xFFFFF) << 8)
#define BIT_AON_APB_V3PS_CR5_AXI_VP_SIZE(x)                     (((x) & 0x1F) << 1)
#define BIT_AON_APB_V3PS_CR5_INITPPX                            BIT(0)

/* REG_AON_APB_V3PHY_CR5_CTRL_1 */

#define BIT_AON_APB_V3PHY_CR5_AXI_VP_BASE(x)                    (((x) & 0xFFFFF) << 8)
#define BIT_AON_APB_V3PHY_CR5_AXI_VP_SIZE(x)                    (((x) & 0x1F) << 1)
#define BIT_AON_APB_V3PHY_CR5_INITPPX                           BIT(0)

/* REG_AON_APB_PSCP_CR8_CTRL */

#define BIT_AON_APB_PSCP_CR8_FORCE_DIVN_ON                      BIT(9)
#define BIT_AON_APB_PSCP_CR8_MFILTEREN                          BIT(8)
#define BIT_AON_APB_PSCP_CR8_TEINIT(x)                          (((x) & 0x3) << 6)
#define BIT_AON_APB_PSCP_CR8_VINITHI(x)                         (((x) & 0x3) << 4)
#define BIT_AON_APB_PSCP_CR8_NMFI(x)                            (((x) & 0x3) << 2)
#define BIT_AON_APB_PSCP_CR8_CFGEE(x)                           (((x) & 0x3))

/* REG_AON_APB_NRCP_CTRL */


/* REG_AON_APB_NRCP_CR8_CTRL */

#define BIT_AON_APB_NRCP_CR8_FORCE_DIVN_ON                      BIT(9)
#define BIT_AON_APB_NRCP_CR8_MFILTEREN                          BIT(8)
#define BIT_AON_APB_NRCP_CR8_TEINIT(x)                          (((x) & 0x3) << 6)
#define BIT_AON_APB_NRCP_CR8_VINITHI(x)                         (((x) & 0x3) << 4)
#define BIT_AON_APB_NRCP_CR8_NMFI(x)                            (((x) & 0x3) << 2)
#define BIT_AON_APB_NRCP_CR8_CFGEE(x)                           (((x) & 0x3))

/* REG_AON_APB_NRCP_DSP0_CTRL */

#define BIT_AON_APB_NRDSP0_STOP_SD                              BIT(2)
#define BIT_AON_APB_NRDSP0_EXTERNAL_WAIT                        BIT(1)
#define BIT_AON_APB_NRDSP0_BOOT                                 BIT(0)

/* REG_AON_APB_NRCP_DSP1_CTRL */

#define BIT_AON_APB_NRDSP1_STOP_SD                              BIT(2)
#define BIT_AON_APB_NRDSP1_EXTERNAL_WAIT                        BIT(1)
#define BIT_AON_APB_NRDSP1_BOOT                                 BIT(0)

/* REG_AON_APB_NRCP_DSP0_BOOT_VECTOR */

#define BIT_AON_APB_NRDSP0_BOOT_VECTOR(x)                       (((x) & 0xFFFFFFFF))

/* REG_AON_APB_NRCP_DSP1_BOOT_VECTOR */

#define BIT_AON_APB_NRDSP1_BOOT_VECTOR(x)                       (((x) & 0xFFFFFFFF))

/* REG_AON_APB_DBG_DJTAG_CTRL */

#define BIT_AON_APB_DBGSYS_CSSYS_STM_NSGUAREN                   BIT(16)
#define BIT_AON_APB_DJTAG_SRC_MUX_SEL                           BIT(0)

/* REG_AON_APB_PSCP_SIM1_TOP_CTRL */

#define BIT_AON_APB_CP_SIM1_CLK_PL                              BIT(5)
#define BIT_AON_APB_CP_SIM1_DETECT_EN                           BIT(4)
#define BIT_AON_APB_CP_BAT1_DETECT_EN                           BIT(3)
#define BIT_AON_APB_CP_SIM1_DETECT_POL                          BIT(2)
#define BIT_AON_APB_CP_BAT1_DETECT_POL                          BIT(1)
#define BIT_AON_APB_CP_SIM1_OFF_PD_EN                           BIT(0)

/* REG_AON_APB_PSCP_SIM2_TOP_CTRL */

#define BIT_AON_APB_CP_SIM2_CLK_PL                              BIT(5)
#define BIT_AON_APB_CP_SIM2_DETECT_EN                           BIT(4)
#define BIT_AON_APB_CP_BAT2_DETECT_EN                           BIT(3)
#define BIT_AON_APB_CP_SIM2_DETECT_POL                          BIT(2)
#define BIT_AON_APB_CP_BAT2_DETECT_POL                          BIT(1)
#define BIT_AON_APB_CP_SIM2_OFF_PD_EN                           BIT(0)

/* REG_AON_APB_PSCP_SIM3_TOP_CTRL */

#define BIT_AON_APB_CP_SIM3_CLK_PL                              BIT(5)
#define BIT_AON_APB_CP_SIM3_DETECT_EN                           BIT(4)
#define BIT_AON_APB_CP_BAT3_DETECT_EN                           BIT(3)
#define BIT_AON_APB_CP_SIM3_DETECT_POL                          BIT(2)
#define BIT_AON_APB_CP_BAT3_DETECT_POL                          BIT(1)
#define BIT_AON_APB_CP_SIM3_OFF_PD_EN                           BIT(0)

/* REG_AON_APB_AP_SIM_TOP_CTRL */

#define BIT_AON_APB_AP_SIM_CLK_PL                               BIT(5)
#define BIT_AON_APB_AP_SIM_DETECT_EN                            BIT(4)
#define BIT_AON_APB_AP_BAT_DETECT_EN                            BIT(3)
#define BIT_AON_APB_AP_SIM_DETECT_POL                           BIT(2)
#define BIT_AON_APB_AP_BAT_DETECT_POL                           BIT(1)
#define BIT_AON_APB_AP_SIM_OFF_PD_EN                            BIT(0)

/* REG_AON_APB_V3_PS_SIM1_TOP_CTRL */

#define BIT_AON_APB_V3_SIM1_CLK_PL                              BIT(5)
#define BIT_AON_APB_V3_SIM1_DETECT_EN                           BIT(4)
#define BIT_AON_APB_V3_BAT1_DETECT_EN                           BIT(3)
#define BIT_AON_APB_V3_SIM1_DETECT_POL                          BIT(2)
#define BIT_AON_APB_V3_BAT1_DETECT_POL                          BIT(1)
#define BIT_AON_APB_V3_SIM1_OFF_PD_EN                           BIT(0)

/* REG_AON_APB_V3_PS_SIM2_TOP_CTRL */

#define BIT_AON_APB_V3_SIM2_CLK_PL                              BIT(5)
#define BIT_AON_APB_V3_SIM2_DETECT_EN                           BIT(4)
#define BIT_AON_APB_V3_BAT2_DETECT_EN                           BIT(3)
#define BIT_AON_APB_V3_SIM2_DETECT_POL                          BIT(2)
#define BIT_AON_APB_V3_BAT2_DETECT_POL                          BIT(1)
#define BIT_AON_APB_V3_SIM2_OFF_PD_EN                           BIT(0)

/* REG_AON_APB_V3_PS_SIM3_TOP_CTRL */

#define BIT_AON_APB_V3_SIM3_CLK_PL                              BIT(5)
#define BIT_AON_APB_V3_SIM3_DETECT_EN                           BIT(4)
#define BIT_AON_APB_V3_BAT3_DETECT_EN                           BIT(3)
#define BIT_AON_APB_V3_SIM3_DETECT_POL                          BIT(2)
#define BIT_AON_APB_V3_BAT3_DETECT_POL                          BIT(1)
#define BIT_AON_APB_V3_SIM3_OFF_PD_EN                           BIT(0)

/* REG_AON_APB_AON_SDIO */

#define BIT_AON_APB_SDIO2_SLICE_EN                              BIT(3)
#define BIT_AON_APB_PSCP_SDIO_ENABLE                            BIT(2)
#define BIT_AON_APB_V3PS_SDIO_ENABLE                            BIT(1)
#define BIT_AON_APB_SDIO_MODULE_SEL                             BIT(0)

/* REG_AON_APB_MTX_URGENCY_CTRL */

#define BIT_AON_APB_ARURGENCY_M6(x)                             (((x) & 0x3) << 26)
#define BIT_AON_APB_AWURGENCY_M6(x)                             (((x) & 0x3) << 24)
#define BIT_AON_APB_ARURGENCY_M5(x)                             (((x) & 0x3) << 22)
#define BIT_AON_APB_AWURGENCY_M5(x)                             (((x) & 0x3) << 20)
#define BIT_AON_APB_ARURGENCY_M4(x)                             (((x) & 0x3) << 18)
#define BIT_AON_APB_AWURGENCY_M4(x)                             (((x) & 0x3) << 16)
#define BIT_AON_APB_ARURGENCY_M3(x)                             (((x) & 0x3) << 14)
#define BIT_AON_APB_AWURGENCY_M3(x)                             (((x) & 0x3) << 12)
#define BIT_AON_APB_ARURGENCY_M2(x)                             (((x) & 0x3) << 10)
#define BIT_AON_APB_AWURGENCY_M2(x)                             (((x) & 0x3) << 8)
#define BIT_AON_APB_ARURGENCY_M1(x)                             (((x) & 0x3) << 6)
#define BIT_AON_APB_AWURGENCY_M1(x)                             (((x) & 0x3) << 4)
#define BIT_AON_APB_ARURGENCY_M0(x)                             (((x) & 0x3) << 2)
#define BIT_AON_APB_AWURGENCY_M0(x)                             (((x) & 0x3))

/* REG_AON_APB_MTX_URGENCY_STATS */

#define BIT_AON_APB_ARURGENCY_AON_MAIN_MTX(x)                   (((x) & 0x3) << 2)
#define BIT_AON_APB_AWURGENCY_AON_MAIN_MTX(x)                   (((x) & 0x3))

/* REG_AON_APB_NR_DSP0_CTRL0 */

#define BIT_AON_APB_NR_DSP0_BOOT_VECTOR(x)                      (((x) & 0xFFFFFFFF))

/* REG_AON_APB_NR_DSP0_CTRL1 */

#define BIT_AON_APB_NR_DSP0_STCK_DSP                            BIT(13)
#define BIT_AON_APB_NR_DSP0_STMS_DSP                            BIT(12)
#define BIT_AON_APB_NR_DSP0_STDO_DSP                            BIT(11)
#define BIT_AON_APB_NR_DSP0_STDI_DSP                            BIT(10)
#define BIT_AON_APB_NR_DSP0_STRTCK_DSP                          BIT(9)
#define BIT_AON_APB_NR_DSP0_SW_JTAG_ENA_DSP                     BIT(8)
#define BIT_AON_APB_NR_DSP0_DSP_EXTERNAL_WAIT                   BIT(1)
#define BIT_AON_APB_NR_DSP0_DSP_BOOT                            BIT(0)

/* REG_AON_APB_NR_DSP1_CTRL0 */

#define BIT_AON_APB_NR_DSP1_BOOT_VECTOR(x)                      (((x) & 0xFFFFFFFF))

/* REG_AON_APB_NR_DSP1_CTRL1 */

#define BIT_AON_APB_NR_DSP1_STCK_DSP                            BIT(13)
#define BIT_AON_APB_NR_DSP1_STMS_DSP                            BIT(12)
#define BIT_AON_APB_NR_DSP1_STDO_DSP                            BIT(11)
#define BIT_AON_APB_NR_DSP1_STDI_DSP                            BIT(10)
#define BIT_AON_APB_NR_DSP1_STRTCK_DSP                          BIT(9)
#define BIT_AON_APB_NR_DSP1_SW_JTAG_ENA_DSP                     BIT(8)
#define BIT_AON_APB_NR_DSP1_DSP_EXTERNAL_WAIT                   BIT(1)
#define BIT_AON_APB_NR_DSP1_DSP_BOOT                            BIT(0)

/* REG_AON_APB_SDIO_SLV_ADDR_OFFSET */

#define BIT_AON_APB_SDIO_SLV_ADDR_OFFSET                        BIT(0)

/* REG_AON_APB_APCPU_CFG_CTRL */

#define BIT_AON_APB_APCPU_PWAKEUPDBG_FORCE_OON                  BIT(4)
#define BIT_AON_APB_APCPU_GICP_ALLOW_NS                         BIT(3)
#define BIT_AON_APB_APCPU_GICT_ALLOW_NS                         BIT(2)
#define BIT_AON_APB_APCPU_GICCDISABLE                           BIT(1)
#define BIT_AON_APB_APCPU_CRYPTDODISABLE                        BIT(0)

/* REG_AON_APB_SP_AON_DDR_EXTEND */

#define BIT_AON_APB_SP_AON_DDR_EXTEND(x)                        (((x) & 0x3))

/* REG_AON_APB_AON_APB_CLK_SEL */

#define BIT_AON_APB_CGM_AON_APB_LP_SEL(x)                       (((x) & 0x7))

/* REG_AON_APB_AUTO_GATE_CTRL0 */

#define BIT_AON_APB_CGM_AP_AXI_APCPU_AUTO_GATE_SEL              BIT(31)
#define BIT_AON_APB_CGM_EMC_FORCE_EN                            BIT(28)
#define BIT_AON_APB_CGM_EMC_AUTO_GATE_SEL                       BIT(27)
#define BIT_AON_APB_CGM_AON_APB_PUB_FORCE_EN                    BIT(24)
#define BIT_AON_APB_CGM_AON_APB_PUB_AUTO_GATE_SEL               BIT(23)
#define BIT_AON_APB_CGM_AON_APB_AUDCP_FORCE_EN                  BIT(22)
#define BIT_AON_APB_CGM_AON_APB_AUDCP_AUTO_GATE_SEL             BIT(21)
#define BIT_AON_APB_CGM_AON_APB_PSCP_FORCE_EN                   BIT(20)
#define BIT_AON_APB_CGM_AON_APB_PSCP_AUTO_GATE_SEL              BIT(19)
#define BIT_AON_APB_CGM_AON_APB_V3_FORCE_EN                     BIT(18)
#define BIT_AON_APB_CGM_AON_APB_V3_AUTO_GATE_SEL                BIT(17)
#define BIT_AON_APB_CGM_AON_APB_NR_FORCE_EN                     BIT(16)
#define BIT_AON_APB_CGM_AON_APB_NR_AUTO_GATE_SEL                BIT(15)
#define BIT_AON_APB_CGM_AON_APB_AP_FORCE_EN                     BIT(14)
#define BIT_AON_APB_CGM_AON_APB_AP_AUTO_GATE_SEL                BIT(13)
#define BIT_AON_APB_CGM_AP_AXI_FORCE_EN                         BIT(12)
#define BIT_AON_APB_CGM_AP_AXI_AUTO_GATE_SEL                    BIT(11)
#define BIT_AON_APB_CGM_CP1_AXI_AP_FORCE_EN                     BIT(10)
#define BIT_AON_APB_CGM_CP1_AXI_AP_AUTO_GATE_SEL                BIT(9)
#define BIT_AON_APB_CGM_CP0_AXI_AP_FORCE_EN                     BIT(8)
#define BIT_AON_APB_CGM_CP0_AXI_AP_AUTO_GATE_SEL                BIT(7)
#define BIT_AON_APB_CGM_APCPU_PMU_AUTO_GATE_SEL                 BIT(2)
#define BIT_AON_APB_CGM_APCPU_PMU_FORCE_EN                      BIT(1)
#define BIT_AON_APB_MBOX_AUTO_GATE_SEL                          BIT(0)

/* REG_AON_APB_AUTO_GATE_CTRL1 */

#define BIT_AON_APB_CGM_PUB_CLK_ANLG_IO_APB_EN                  BIT(5)
#define BIT_AON_APB_CGM_DMC_REF_AUTO_GATE_SEL                   BIT(4)
#define BIT_AON_APB_CGM_TOP_DVFS_ROOT_AUTO_GATE_SEL             BIT(3)
#define BIT_AON_APB_CGM_TOP_DVFS_ROOT_FORCE_EN                  BIT(2)

/* REG_AON_APB_AUTO_GATE_CTRL3 */

#define BIT_AON_APB_CGM_PERIPH_AUTO_GATE_EN                     BIT(13)
#define BIT_AON_APB_CGM_GIC_AUTO_GATE_EN                        BIT(12)
#define BIT_AON_APB_CGM_ACP_AUTO_GATE_EN                        BIT(11)
#define BIT_AON_APB_CGM_AXI_PERIPH_AUTO_GATE_EN                 BIT(10)
#define BIT_AON_APB_CGM_ACE_AUTO_GATE_EN                        BIT(9)
#define BIT_AON_APB_CGM_SCU_AUTO_GATE_EN                        BIT(8)
#define BIT_AON_APB_CGM_CORE1_AUTO_GATE_EN                      BIT(1)
#define BIT_AON_APB_CGM_CORE0_AUTO_GATE_EN                      BIT(0)

/* REG_AON_APB_V3_LPC_CTRL */

#define BIT_AON_APB_V3_FRC_STOP_ACK                             BIT(8)
#define BIT_AON_APB_V3_FRC_STOP_REQ                             BIT(0)

/* REG_AON_APB_PSCP_LPC_CTRL */

#define BIT_AON_APB_PSCP_FRC_STOP_ACK                           BIT(8)
#define BIT_AON_APB_PSCP_FRC_STOP_REQ                           BIT(0)

/* REG_AON_APB_AP_LPC_CTRL */

#define BIT_AON_APB_APCPU_FRC_STOP_ACK                          BIT(9)
#define BIT_AON_APB_AP_FRC_STOP_ACK                             BIT(8)
#define BIT_AON_APB_APCPU_FRC_STOP_REQ                          BIT(1)
#define BIT_AON_APB_AP_FRC_STOP_REQ                             BIT(0)

/* REG_AON_APB_AUDCP_LPC_CTRL */

#define BIT_AON_APB_AUDCP_FRC_STOP_ACK                          BIT(8)
#define BIT_AON_APB_AUDCP_FRC_STOP_REQ                          BIT(0)

/* REG_AON_APB_NRCP_LPC_CTRL */

#define BIT_AON_APB_NRCP_FRC_STOP_ACK                           BIT(8)
#define BIT_AON_APB_NRCP_FRC_STOP_REQ                           BIT(0)

/* REG_AON_APB_APCPU_AXI_CTRL */

#define BIT_AON_APB_CGM_APCPU_AXI_AUTO_FREQ_DOWN_CTRL_SEL       BIT(3)
#define BIT_AON_APB_CGM_APCPU_AXI_AUTO_FREQ_DOWN_EN             BIT(2)
#define BIT_AON_APB_CGM_APCPU_AXI_SEL_IDLE(x)                   (((x) & 0x3))

/* REG_AON_APB_APCPU_CLK_CTRL0 */

#define BIT_AON_APB_APCPU_CORE_WAKEUP_ACE_CLK_EN                BIT(1)
#define BIT_AON_APB_APCPU_CORE_WAKEUP_SCU_CLK_EN                BIT(0)

/* REG_AON_APB_PUB_CLK_GATING_CTRL */

#define BIT_AON_APB_PUB_APB_FW_EB                               BIT(17)
#define BIT_AON_APB_PUB_REG_EB                                  BIT(16)
#define BIT_AON_APB_DMC_EB                                      BIT(15)

/* REG_AON_APB_DDRPHY_VREP */

#define BIT_AON_APB_PHY_VREF_ADJ(x)                             (((x) & 0xFF) << 2)
#define BIT_AON_APB_PHY_VREF_PD                                 BIT(1)
#define BIT_AON_APB_PHY_VREF_HI_C                               BIT(0)

/* REG_AON_APB_CGM_RESCUE */

#define BIT_AON_APB_CGM_RESCUE(x)                               (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AON_APB_FREQ_CTRL */

#define BIT_AON_APB_AON_APB_MASTER_BUSY(x)                      (((x) & 0x1FFF) << 2)
#define BIT_AON_APB_AON_APB_FREQ_CTRL_EN                        BIT(1)
#define BIT_AON_APB_AON_APB_IDLE_EN                             BIT(0)

/* REG_AON_APB_APCPU_MONITOR_STATUS */

#define BIT_AON_APB_MONITOR_GATE_AUTO_EN_STATUS(x)              (((x) & 0xF) << 4)
#define BIT_AON_APB_MONITOR_WAIT_EN_STATUS(x)                   (((x) & 0xF))

/* REG_AON_APB_APCPU_DEBUG_PWR_LP_CTRL */

#define BIT_AON_APB_APCPU_LP_NUM_DEBUG_PWR(x)                   (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_APCPU_LP_EB_DEBUG_PWR                       BIT(0)

/* REG_AON_APB_APCPU_GIC_COL_LP_CTRL */

#define BIT_AON_APB_APCPU_LP_NUM_GIC_COL(x)                     (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_APCPU_LP_EB_GIC_COL                         BIT(0)

/* REG_AON_APB_APCPU_CLUSTER_ATB_LPC_CTRL */

#define BIT_AON_APB_APCPU_CLUSTER_ATB_LP_NUM(x)                 (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_APCPU_CLUSTER_ATB_LP_EB                     BIT(0)

/* REG_AON_APB_APCPU_CLUSTER_APB_LPC_CTRL */

#define BIT_AON_APB_APCPU_CLUSTER_APB_LP_NUM(x)                 (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_APCPU_CLUSTER_APB_LP_EB                     BIT(0)

/* REG_AON_APB_APCPU_CLUSTER_GIC_LPC_CTRL */

#define BIT_AON_APB_APCPU_CLUSTER_GIC_LP_NUM(x)                 (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_APCPU_CLUSTER_GIC_LP_EB                     BIT(0)

/* REG_AON_APB_APCPU_GIC600_GIC_LPC_CTRL */

#define BIT_AON_APB_APCPU_GIC600_GIC_LP_NUM(x)                  (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_APCPU_GIC600_GIC_LP_EB                      BIT(0)

/* REG_AON_APB_APCPU_DBG_BLK_LPC_CTRL */

#define BIT_AON_APB_APCPU_DBG_BLK_LP_NUM(x)                     (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_APCPU_DBG_BLK_LP_EB                         BIT(0)

/* REG_AON_APB_APCPU_TOP_MTX_M0_LPC_CTRL */

#define BIT_AON_APB_APCPU_TOP_MTX_LP_NUM(x)                     (((x) & 0xFFFF) << 9)
#define BIT_AON_APB_APCPU_TOP_MTX_MIAN_LP_EB                    BIT(8)
#define BIT_AON_APB_APCPU_TOP_MTX_S3_LP_EB                      BIT(7)
#define BIT_AON_APB_APCPU_TOP_MTX_S2_LP_EB                      BIT(6)
#define BIT_AON_APB_APCPU_TOP_MTX_S1_LP_EB                      BIT(5)
#define BIT_AON_APB_APCPU_TOP_MTX_S0_LP_EB                      BIT(4)
#define BIT_AON_APB_APCPU_TOP_MTX_M3_LP_EB                      BIT(3)
#define BIT_AON_APB_APCPU_TOP_MTX_M2_LP_EB                      BIT(2)
#define BIT_AON_APB_APCPU_TOP_MTX_M1_LP_EB                      BIT(1)
#define BIT_AON_APB_APCPU_TOP_MTX_M0_LP_EB                      BIT(0)

/* REG_AON_APB_APCPU_CLUSTER_SCU_LPC_CTRL */

#define BIT_AON_APB_APCPU_CLUSTER_SCU_LP_NUM(x)                 (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_APCPU_CLUSTER_SCU_LP_EB                     BIT(0)

/* REG_AON_APB_APCPU_DDR_AB_LPC_CTRL */

#define BIT_AON_APB_APCPU_DDR_AB_LP_NUM(x)                      (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_APCPU_DDR_AB_LP_EB                          BIT(0)

/* REG_AON_APB_APCPU_QOS_CTRL */

#define BIT_AON_APB_QOS_DAP_APCPU(x)                            (((x) & 0xF) << 20)
#define BIT_AON_APB_QOS_ETR_APCPU(x)                            (((x) & 0xF) << 16)
#define BIT_AON_APB_ARQOS_THRESHOLD_APCPU(x)                    (((x) & 0xF) << 12)
#define BIT_AON_APB_AWQOS_THRESHOLD_APCPU(x)                    (((x) & 0xF) << 8)
#define BIT_AON_APB_ARQOS_APCPU(x)                              (((x) & 0xF) << 4)
#define BIT_AON_APB_AWQOS_APCPU(x)                              (((x) & 0xF))

/* REG_AON_APB_APCPU_URGENCY_CTRL */

#define BIT_AON_APB_ARURGENCY_APCPU(x)                          (((x) & 0x3) << 14)
#define BIT_AON_APB_AWURGENCY_APCPU(x)                          (((x) & 0x3) << 12)
#define BIT_AON_APB_ARURGENCY_APCPU_M3(x)                       (((x) & 0x3) << 10)
#define BIT_AON_APB_AWURGENCY_APCPU_M3(x)                       (((x) & 0x3) << 8)
#define BIT_AON_APB_ARURGENCY_APCPU_M2(x)                       (((x) & 0x3) << 6)
#define BIT_AON_APB_AWURGENCY_APCPU_M2(x)                       (((x) & 0x3) << 4)
#define BIT_AON_APB_ARURGENCY_APCPU_M0(x)                       (((x) & 0x3) << 2)
#define BIT_AON_APB_AWURGENCY_APCPU_M0(x)                       (((x) & 0x3))

/* REG_AON_APB_AON_MTX_PROT_CFG */

#define BIT_AON_APB_HPROT_DMAW(x)                               (((x) & 0xF) << 4)
#define BIT_AON_APB_HPROT_DMAR(x)                               (((x) & 0xF))

/* REG_AON_APB_APCU_LPC_CTRL */

#define BIT_AON_APB_APCPU2AP_LP_ACK                             BIT(3)
#define BIT_AON_APB_APCPU2AP_LP_FORCE                           BIT(2)
#define BIT_AON_APB_DAP2APCPU_LP_ACK                            BIT(1)
#define BIT_AON_APB_DAP2APCPU_LP_FORCE                          BIT(0)

/* REG_AON_APB_CM42AON_LPC_CTRL */

#define BIT_AON_APB_CM4_TO_AON_AXI_PU_NUM(x)                    (((x) & 0xFF) << 17)
#define BIT_AON_APB_CM4_TO_AON_AXI_LP_NUM(x)                    (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_CM4_TO_AON_AXI_LP_EB                        BIT(0)

/* REG_AON_APB_AON_MTX_MAIN_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_MAIN_PU_NUM(x)                      (((x) & 0xFF) << 17)
#define BIT_AON_APB_AON_MTX_MAIN_LP_NUM(x)                      (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_MAIN_LP_EB                          BIT(0)

/* REG_AON_APB_AON_MTX_M0_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_M0_PU_NUM(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_AON_MTX_M0_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_M0_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_M1_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_M1_PU_NUM(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_AON_MTX_M1_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_M1_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_M2_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_M2_PU_NUM(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_AON_MTX_M2_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_M2_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_M3_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_M3_PU_NUM(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_AON_MTX_M3_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_M3_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_M4_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_M4_PU_NUM(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_AON_MTX_M4_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_M4_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_M5_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_M5_PU_NUM(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_AON_MTX_M5_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_M5_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_M6_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_M6_PU_NUM(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_AON_MTX_M6_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_M6_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_S0_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_S0_PU_NUM(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_AON_MTX_S0_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_S0_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_S1_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_S1_PU_NUM(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_AON_MTX_S1_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_S1_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_S2_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_S2_PU_NUM(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_AON_MTX_S2_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_S2_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_S3_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_S3_PU_NUM(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_AON_MTX_S3_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_S3_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_S4_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_S4_PU_NUM(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_AON_MTX_S4_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_S4_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_S5_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_S5_PU_NUM(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_AON_MTX_S5_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_S5_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_S6_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_S6_PU_NUM(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_AON_MTX_S6_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_S6_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_S7_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_S7_PU_NUM(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_AON_MTX_S7_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_S7_LP_EB                            BIT(0)

/* REG_AON_APB_EAXI_MTX_M0_LPC_CTRL */

#define BIT_AON_APB_EAXI_MTX_M0_PU_NUM(x)                       (((x) & 0xFF) << 17)
#define BIT_AON_APB_EAXI_MTX_M0_LP_NUM(x)                       (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_EAXI_MTX_M0_LP_EB                           BIT(0)

/* REG_AON_APB_EAXI_MTX_M1_LPC_CTRL */

#define BIT_AON_APB_EAXI_MTX_M1_PU_NUM(x)                       (((x) & 0xFF) << 17)
#define BIT_AON_APB_EAXI_MTX_M1_LP_NUM(x)                       (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_EAXI_MTX_M1_LP_EB                           BIT(0)

/* REG_AON_APB_EAXI_MTX_M2_LPC_CTRL */

#define BIT_AON_APB_EAXI_MTX_M2_PU_NUM(x)                       (((x) & 0xFF) << 17)
#define BIT_AON_APB_EAXI_MTX_M2_LP_NUM(x)                       (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_EAXI_MTX_M2_LP_EB                           BIT(0)

/* REG_AON_APB_EAXI_MTX_S0_LPC_CTRL */

#define BIT_AON_APB_EAXI_MTX_S0_PU_NUM(x)                       (((x) & 0xFF) << 17)
#define BIT_AON_APB_EAXI_MTX_S0_LP_NUM(x)                       (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_EAXI_MTX_S0_LP_EB                           BIT(0)

/* REG_AON_APB_EAXI_MTX_S1_LPC_CTRL */

#define BIT_AON_APB_EAXI_MTX_S1_PU_NUM(x)                       (((x) & 0xFF) << 17)
#define BIT_AON_APB_EAXI_MTX_S1_LP_NUM(x)                       (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_EAXI_MTX_S1_LP_EB                           BIT(0)

/* REG_AON_APB_EAXI_MTX_MAIN_LPC_CTRL */

#define BIT_AON_APB_EAXI_MTX_MAIN_PU_NUM(x)                     (((x) & 0xFF) << 17)
#define BIT_AON_APB_EAXI_MTX_MAIN_LP_NUM(x)                     (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_EAXI_MTX_MAIN_LP_EB                         BIT(0)

/* REG_AON_APB_AON_SOC_USB_CTRL */

#define BIT_AON_APB_U2U3_REF_CLK_SEL(x)                         (((x) & 0x3) << 3)
#define BIT_AON_APB_USB_BUSCLK_SEL_SOC                          BIT(2)
#define BIT_AON_APB_USB_DIVN_MUX_SEL                            BIT(1)

/* REG_AON_APB_PCIE_SLV_ADDR_OFFSET */

#define BIT_AON_APB_PCIE_MOD_SEL                                BIT(16)
#define BIT_AON_APB_PCIE_SLV_ADDR_OFFSET(x)                     (((x) & 0x3FF))

/* REG_AON_APB_AP_EMMC_PHY_CTRL */

#define BIT_AON_APB_AP_EMMC_IO_POWER_OFF_DELAY                  BIT(25)
#define BIT_AON_APB_AP_EMMC_IO_POWER_OFF                        BIT(24)
#define BIT_AON_APB_AP_EMMC_CARDDET_DBNC_THD_32K(x)             (((x) & 0xFF) << 16)
#define BIT_AON_APB_AP_EMMC_BATTERY_DBNC_THD_32K(x)             (((x) & 0xFF) << 8)
#define BIT_AON_APB_AP_EMMC_CARDDET_DBNC_EN_32K                 BIT(7)
#define BIT_AON_APB_AP_EMMC_BATTERY_DBNC_EN_32K                 BIT(6)
#define BIT_AON_APB_AP_EMMC_BATTERY_DEB_EN_32K                  BIT(5)
#define BIT_AON_APB_AP_EMMC_BATTERY_PRESENT_32K                 BIT(4)
#define BIT_AON_APB_AP_EMMC_CARD_PROTECT_32K                    BIT(3)
#define BIT_AON_APB_AP_EMMC_CARD_PRESENT_32K                    BIT(2)
#define BIT_AON_APB_AP_EMMC_BATTERY_DET                         BIT(1)
#define BIT_AON_APB_AP_EMMC_CARD_DET                            BIT(0)

/* REG_AON_APB_AP_SDIO1_PHY_CTRL */

#define BIT_AON_APB_AP_SDIO1_IO_POWER_OFF_DELAY                 BIT(25)
#define BIT_AON_APB_AP_SDIO1_IO_POWER_OFF                       BIT(24)
#define BIT_AON_APB_AP_SDIO1_CARDDET_DBNC_THD_32K(x)            (((x) & 0xFF) << 16)
#define BIT_AON_APB_AP_SDIO1_BATTERY_DBNC_THD_32K(x)            (((x) & 0xFF) << 8)
#define BIT_AON_APB_AP_SDIO1_CARDDET_DBNC_EN_32K                BIT(7)
#define BIT_AON_APB_AP_SDIO1_BATTERY_DBNC_EN_32K                BIT(6)
#define BIT_AON_APB_AP_SDIO1_BATTERY_DEB_EN_32K                 BIT(5)
#define BIT_AON_APB_AP_SDIO1_BATTERY_PRESENT_32K                BIT(4)
#define BIT_AON_APB_AP_SDIO1_CARD_PROTECT_32K                   BIT(3)
#define BIT_AON_APB_AP_SDIO1_CARD_PRESENT_32K                   BIT(2)
#define BIT_AON_APB_AP_SDIO1_BATTERY_DET                        BIT(1)
#define BIT_AON_APB_AP_SDIO1_CARD_DET                           BIT(0)

/* REG_AON_APB_PS_SDIO2_PHY_CTRL */

#define BIT_AON_APB_PS_SDIO2_IO_POWER_OFF_DELAY                 BIT(25)
#define BIT_AON_APB_PS_SDIO2_IO_POWER_OFF                       BIT(24)
#define BIT_AON_APB_PS_SDIO2_CARDDET_DBNC_THD_32K(x)            (((x) & 0xFF) << 16)
#define BIT_AON_APB_PS_SDIO2_BATTERY_DBNC_THD_32K(x)            (((x) & 0xFF) << 8)
#define BIT_AON_APB_PS_SDIO2_CARDDET_DBNC_EN_32K                BIT(7)
#define BIT_AON_APB_PS_SDIO2_BATTERY_DBNC_EN_32K                BIT(6)
#define BIT_AON_APB_PS_SDIO2_BATTERY_DEB_EN_32K                 BIT(5)
#define BIT_AON_APB_PS_SDIO2_BATTERY_PRESENT_32K                BIT(4)
#define BIT_AON_APB_PS_SDIO2_CARD_PROTECT_32K                   BIT(3)
#define BIT_AON_APB_PS_SDIO2_CARD_PRESENT_32K                   BIT(2)
#define BIT_AON_APB_PS_SDIO2_BATTERY_DET                        BIT(1)
#define BIT_AON_APB_PS_SDIO2_CARD_DET                           BIT(0)

/* REG_AON_APB_V3PS_SDIO2_PHY_CTRL */

#define BIT_AON_APB_V3PS_SDIO2_IO_POWER_OFF_DELAY               BIT(25)
#define BIT_AON_APB_V3PS_SDIO2_IO_POWER_OFF                     BIT(24)
#define BIT_AON_APB_V3PS_SDIO2_CARDDET_DBNC_THD_32K(x)          (((x) & 0xFF) << 16)
#define BIT_AON_APB_V3PS_SDIO2_BATTERY_DBNC_THD_32K(x)          (((x) & 0xFF) << 8)
#define BIT_AON_APB_V3PS_SDIO2_CARDDET_DBNC_EN_32K              BIT(7)
#define BIT_AON_APB_V3PS_SDIO2_BATTERY_DBNC_EN_32K              BIT(6)
#define BIT_AON_APB_V3PS_SDIO2_BATTERY_DEB_EN_32K               BIT(5)
#define BIT_AON_APB_V3PS_SDIO2_BATTERY_PRESENT_32K              BIT(4)
#define BIT_AON_APB_V3PS_SDIO2_CARD_PROTECT_32K                 BIT(3)
#define BIT_AON_APB_V3PS_SDIO2_CARD_PRESENT_32K                 BIT(2)
#define BIT_AON_APB_V3PS_SDIO2_BATTERY_DET                      BIT(1)
#define BIT_AON_APB_V3PS_SDIO2_CARD_DET                         BIT(0)

/* REG_AON_APB_RVBARADDR0 */

#define BIT_AON_APB_RVBARADDR0(x)                               (((x) & 0xFFFFFFFF))

/* REG_AON_APB_RVBARADDR1 */

#define BIT_AON_APB_RVBARADDR1(x)                               (((x) & 0xFFFFFFFF))

/* REG_AON_APB_APCPU_PU_NUM */

#define BIT_AON_APB_APCPU_ACE_PU_NUM(x)                         (((x) & 0xFF) << 8)
#define BIT_AON_APB_APCPU_MTX_PU_NUM(x)                         (((x) & 0xFF))

/* REG_AON_APB_APCPU_L3CACHE_RAM_PD_BYPASS */

#define BIT_AON_APB_APCPU_L3CACHE_RAM_PD_BYPASS                 BIT(0)

/* REG_AON_APB_AON_TO_AUDCP_RS_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_AON_TO_AUDCP(x)                      (((x) & 0xFF) << 17)
#define BIT_AON_APB_LP_NUM_AON_TO_AUDCP(x)                      (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AON_TO_AUDCP                          BIT(0)

/* REG_AON_APB_AP_TO_NR_RS_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_AP_TO_NR(x)                          (((x) & 0xFF) << 17)
#define BIT_AON_APB_LP_NUM_AP_TO_NR(x)                          (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AP_TO_NR                              BIT(0)

/* REG_AON_APB_AP_TO_PSCP_RS_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_AP_TO_PSCP(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_LP_NUM_AP_TO_PSCP(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AP_TO_PSCP                            BIT(0)

/* REG_AON_APB_APCPU_TO_AP_RS_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_APCPU_TO_AP(x)                       (((x) & 0xFF) << 17)
#define BIT_AON_APB_LP_NUM_APCPU_TO_AP(x)                       (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_APCPU_TO_AP                           BIT(0)

/* REG_AON_APB_NR_TO_AP_RS_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_NR_TO_AP(x)                          (((x) & 0xFF) << 17)
#define BIT_AON_APB_LP_NUM_NR_TO_AP(x)                          (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_NR_TO_AP                              BIT(0)

/* REG_AON_APB_NR_TO_PSCP_RS_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_NR_TO_PSCP(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_LP_NUM_NR_TO_PSCP(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_NR_TO_PSCP                            BIT(0)

/* REG_AON_APB_PSCP_TO_AP_RS_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_PSCP_TO_AP(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_LP_NUM_PSCP_TO_AP(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_PSCP_TO_AP                            BIT(0)

/* REG_AON_APB_PSCP_TO_NR_RS_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_PSCP_TO_NR(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_LP_NUM_PSCP_TO_NR(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_PSCP_TO_NR                            BIT(0)

/* REG_AON_APB_PSCP_TO_V3_RS_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_PSCP_TO_V3(x)                        (((x) & 0xFF) << 17)
#define BIT_AON_APB_LP_NUM_PSCP_TO_V3(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_PSCP_TO_V3                            BIT(0)

/* REG_AON_APB_AUDCP_TO_PUB_RS_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_AUDCP_TO_PUB(x)                      (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AUDCP_TO_PUB                          BIT(0)

/* REG_AON_APB_AON_TO_PUB_RS_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_AON_TO_PUB(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AON_TO_PUB                            BIT(0)

/* REG_AON_APB_CSSYS_TO_PUB_RS_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_CSSYS_TO_PUB(x)                      (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_CSSYS_TO_PUB                          BIT(0)

/* REG_AON_APB_APCPU_TO_PUB_RS_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_APCPU_TO_PUB(x)                      (((x) & 0xFF) << 17)
#define BIT_AON_APB_LP_NUM_APCPU_TO_PUB(x)                      (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_APCPU_TO_PUB                          BIT(0)

/* REG_AON_APB_AP_TO_PUB_RS_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_AP_TO_PUB(x)                         (((x) & 0xFF) << 17)
#define BIT_AON_APB_LP_NUM_AP_TO_PUB(x)                         (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AP_TO_PUB                             BIT(0)

/* REG_AON_APB_NRACC_TO_PUB_RS_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_NRACC_TO_PUB(x)                      (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_NRACC_TO_PUB                          BIT(0)

/* REG_AON_APB_NRCPU_TO_PUB_RS_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_NRCPU_TO_PUB(x)                      (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_NRCPU_TO_PUB                          BIT(0)

/* REG_AON_APB_V3CPU_TO_PUB_RS_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_V3CPU_TO_PUB(x)                      (((x) & 0xFF) << 17)
#define BIT_AON_APB_LP_NUM_V3CPU_TO_PUB(x)                      (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_V3CPU_TO_PUB                          BIT(0)

/* REG_AON_APB_V3ACC_TO_PUB_RS_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_V3ACC_TO_PUB(x)                      (((x) & 0xFF) << 17)
#define BIT_AON_APB_LP_NUM_V3ACC_TO_PUB(x)                      (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_V3ACC_TO_PUB                          BIT(0)

/* REG_AON_APB_PSCP_TO_PUB_RS_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_PSCP_TO_PUB(x)                       (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_PSCP_TO_PUB                           BIT(0)

/* REG_AON_APB_AB_W_AGCP2EMC_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_AB_W_AGCP2EMC(x)                     (((x) & 0xFF) << 19)
#define BIT_AON_APB_LP_FORCE_ACK_AB_W_AGCP2EMC                  BIT(18)
#define BIT_AON_APB_LP_FORCE_AB_W_AGCP2EMC                      BIT(17)
#define BIT_AON_APB_LP_NUM_AB_W_AGCP2EMC(x)                     (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AB_W_AGCP2EMC                         BIT(0)

/* REG_AON_APB_AB_W_AONSYS2EMC_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_AB_W_AONSYS2EMC(x)                   (((x) & 0xFF) << 19)
#define BIT_AON_APB_LP_FORCE_ACK_AB_W_AONSYS2EMC                BIT(18)
#define BIT_AON_APB_LP_FORCE_AB_W_AONSYS2EMC                    BIT(17)
#define BIT_AON_APB_LP_NUM_AB_W_AONSYS2EMC(x)                   (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AB_W_AONSYS2EMC                       BIT(0)

/* REG_AON_APB_AB_W_APCPU2EMC_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_AB_W_APCPU2EMC(x)                    (((x) & 0xFF) << 19)
#define BIT_AON_APB_LP_FORCE_ACK_AB_W_APCPU2EMC                 BIT(18)
#define BIT_AON_APB_LP_FORCE_AB_W_APCPU2EMC                     BIT(17)
#define BIT_AON_APB_LP_NUM_AB_W_APCPU2EMC(x)                    (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AB_W_APCPU2EMC                        BIT(0)

/* REG_AON_APB_AB_W_CSSYS2EMC_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_AB_W_CSSYS2EMC(x)                    (((x) & 0xFF) << 19)
#define BIT_AON_APB_LP_FORCE_ACK_AB_W_CSSYS2EMC                 BIT(18)
#define BIT_AON_APB_LP_FORCE_AB_W_CSSYS2EMC                     BIT(17)
#define BIT_AON_APB_LP_NUM_AB_W_CSSYS2EMC(x)                    (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AB_W_CSSYS2EMC                        BIT(0)

/* REG_AON_APB_AB_W_MINIAP2EMC_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_AB_W_MINIAP2EMC(x)                   (((x) & 0xFF) << 19)
#define BIT_AON_APB_LP_FORCE_ACK_AB_W_MINIAP2EMC                BIT(18)
#define BIT_AON_APB_LP_FORCE_AB_W_MINIAP2EMC                    BIT(17)
#define BIT_AON_APB_LP_NUM_AB_W_MINIAP2EMC(x)                   (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AB_W_MINIAP2EMC                       BIT(0)

/* REG_AON_APB_AB_W_NRACC2EMC_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_AB_W_NRACC2EMC(x)                    (((x) & 0xFF) << 19)
#define BIT_AON_APB_LP_FORCE_ACK_AB_W_NRACC2EMC                 BIT(18)
#define BIT_AON_APB_LP_FORCE_AB_W_NRACC2EMC                     BIT(17)
#define BIT_AON_APB_LP_NUM_AB_W_NRACC2EMC(x)                    (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AB_W_NRACC2EMC                        BIT(0)

/* REG_AON_APB_AB_W_NRCPU2EMC_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_AB_W_NRCPU2EMC(x)                    (((x) & 0xFF) << 19)
#define BIT_AON_APB_LP_FORCE_ACK_AB_W_NRCPU2EMC                 BIT(18)
#define BIT_AON_APB_LP_FORCE_AB_W_NRCPU2EMC                     BIT(17)
#define BIT_AON_APB_LP_NUM_AB_W_NRCPU2EMC(x)                    (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AB_W_NRCPU2EMC                        BIT(0)

/* REG_AON_APB_AB_W_V3ACC2EMC_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_AB_W_V3ACC2EMC(x)                    (((x) & 0xFF) << 19)
#define BIT_AON_APB_LP_FORCE_ACK_AB_W_V3ACC2EMC                 BIT(18)
#define BIT_AON_APB_LP_FORCE_AB_W_V3ACC2EMC                     BIT(17)
#define BIT_AON_APB_LP_NUM_AB_W_V3ACC2EMC(x)                    (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AB_W_V3ACC2EMC                        BIT(0)

/* REG_AON_APB_AB_W_V3CPU2EMC_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_AB_W_V3CPU2EMC(x)                    (((x) & 0xFF) << 19)
#define BIT_AON_APB_LP_FORCE_ACK_AB_W_V3CPU2EMC                 BIT(18)
#define BIT_AON_APB_LP_FORCE_AB_W_V3CPU2EMC                     BIT(17)
#define BIT_AON_APB_LP_NUM_AB_W_V3CPU2EMC(x)                    (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AB_W_V3CPU2EMC                        BIT(0)

/* REG_AON_APB_AB_W_PSCP2EMC_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_AB_W_PSCP2EMC(x)                     (((x) & 0xFF) << 19)
#define BIT_AON_APB_LP_FORCE_ACK_AB_W_PSCP2EMC                  BIT(18)
#define BIT_AON_APB_LP_FORCE_AB_W_PSCP2EMC                      BIT(17)
#define BIT_AON_APB_LP_NUM_AB_W_PSCP2EMC(x)                     (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AB_W_PSCP2EMC                         BIT(0)

/* REG_AON_APB_AHB2AHB_ASYNC_CTRL */

#define BIT_AON_APB_NOBUF_EARLY_RESP_EN                         BIT(2)
#define BIT_AON_APB_SCLK_AUTO_GATE_EN                           BIT(1)
#define BIT_AON_APB_MCLK_AUTO_GATE_EN                           BIT(0)

/* REG_AON_APB_APCPU_ATB_CLK_DFS_CTRL */

#define BIT_AON_APB_APCPU_ATB_CLK_DFS_CTRL_DIV                  BIT(1)
#define BIT_AON_APB_APCPU_ATB_CLK_DFS_CTRL_SEL                  BIT(0)

/* REG_AON_APB_AON_APB_DFS_CTRL */

#define BIT_AON_APB_AON_APB_DFS_SUB_SYS_MASK                    BIT(1)
#define BIT_AON_APB_AON_APB_DFS_REG_SLICE_MASK                  BIT(0)

/* REG_AON_APB_AON_TO_PUB_RF_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_AON_TO_PUB_RF(x)                     (((x) & 0xFF) << 19)
#define BIT_AON_APB_LP_FORCE_ACK_AON_TO_PUB_RF                  BIT(18)
#define BIT_AON_APB_LP_FORCE_AON_TO_PUB_RF                      BIT(17)
#define BIT_AON_APB_LP_NUM_AON_TO_PUB_RF(x)                     (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AON_TO_PUB_RF                         BIT(0)

/* REG_AON_APB_EAXI_TO_APCPU_LPC_CTRL */

#define BIT_AON_APB_PU_NUM_EAXI_TO_APCPU(x)                     (((x) & 0xFF) << 19)
#define BIT_AON_APB_LP_FORCE_ACK_EAXI_TO_APCPU                  BIT(18)
#define BIT_AON_APB_LP_FORCE_EAXI_TO_APCPU                      BIT(17)
#define BIT_AON_APB_LP_NUM_EAXI_TO_APCPU(x)                     (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_EAXI_TO_APCPU                         BIT(0)

/* REG_AON_APB_EWARLY_WAKEUP_EN */

#define BIT_AON_APB_EARLY_WAKEUP_EN                             BIT(0)

/* REG_AON_APB_PWR_CTRL */

#define BIT_AON_APB_EFUSE_PWON_RD_END_FLAG                      BIT(2)

/* REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG4 */

#define BIT_AON_APB_REG_DBG_MOD_SEL_AON(x)                      (((x) & 0xFF) << 24)
#define BIT_AON_APB_REG_DBG_MOD_SEL_PUB(x)                      (((x) & 0xFF) << 16)
#define BIT_AON_APB_REG_DBG_MOD_SEL_AUDCP(x)                    (((x) & 0xFF) << 8)
#define BIT_AON_APB_REG_DBG_MOD_SEL_AP(x)                       (((x) & 0xFF))

/* REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG0 */

#define BIT_AON_APB_REG_DBG_MOD_SEL_NR(x)                       (((x) & 0xFF) << 24)
#define BIT_AON_APB_REG_DBG_MOD_SEL_V3(x)                       (((x) & 0xFF) << 16)
#define BIT_AON_APB_REG_DBG_MOD_SEL_PSCP(x)                     (((x) & 0xFF) << 8)
#define BIT_AON_APB_REG_DBG_BUS_SEL_APCPU(x)                    (((x) & 0xFF))

/* REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG1 */

#define BIT_AON_APB_REG_DBG_BUS_SEL_AP(x)                       (((x) & 0xFF) << 24)
#define BIT_AON_APB_REG_DBG_BUS_SEL_PSCP(x)                     (((x) & 0xFF) << 16)
#define BIT_AON_APB_REG_DBG_BUS_SEL_V3(x)                       (((x) & 0xFF) << 8)
#define BIT_AON_APB_REG_DBG_BUS_SEL_AUDCP(x)                    (((x) & 0xFF))

/* REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG2 */

#define BIT_AON_APB_REG_DBG_BUS_SEL_PUB(x)                      (((x) & 0xFF) << 24)
#define BIT_AON_APB_REG_DBG_BUS_SEL_NR(x)                       (((x) & 0xFF) << 16)
#define BIT_AON_APB_REG_DBG_BUS_SEL_AON(x)                      (((x) & 0xFF) << 8)

/* REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG3 */

#define BIT_AON_APB_REG_DBG_MOD_SEL_APCPU(x)                    (((x) & 0xFF) << 16)
#define BIT_AON_APB_REG_DBG_SYS_SEL_B(x)                        (((x) & 0xFF) << 8)
#define BIT_AON_APB_REG_DBG_SYS_SEL(x)                          (((x) & 0xFF))

/* REG_AON_APB_PAD_DBG_BUS_SEL_CFG1 */

#define BIT_AON_APB_DBG_BUS4_SEL(x)                             (((x) & 0x3F) << 24)
#define BIT_AON_APB_DBG_BUS3_SEL(x)                             (((x) & 0x3F) << 18)
#define BIT_AON_APB_DBG_BUS2_SEL(x)                             (((x) & 0x3F) << 12)
#define BIT_AON_APB_DBG_BUS1_SEL(x)                             (((x) & 0x3F) << 6)
#define BIT_AON_APB_DBG_BUS0_SEL(x)                             (((x) & 0x3F))

/* REG_AON_APB_PAD_DBG_BUS_SEL_CFG2 */

#define BIT_AON_APB_DBG_BUS9_SEL(x)                             (((x) & 0x3F) << 24)
#define BIT_AON_APB_DBG_BUS8_SEL(x)                             (((x) & 0x3F) << 18)
#define BIT_AON_APB_DBG_BUS7_SEL(x)                             (((x) & 0x3F) << 12)
#define BIT_AON_APB_DBG_BUS6_SEL(x)                             (((x) & 0x3F) << 6)
#define BIT_AON_APB_DBG_BUS5_SEL(x)                             (((x) & 0x3F))

/* REG_AON_APB_PAD_DBG_BUS_SEL_CFG3 */

#define BIT_AON_APB_DBG_BUS14_SEL(x)                            (((x) & 0x3F) << 24)
#define BIT_AON_APB_DBG_BUS13_SEL(x)                            (((x) & 0x3F) << 18)
#define BIT_AON_APB_DBG_BUS12_SEL(x)                            (((x) & 0x3F) << 12)
#define BIT_AON_APB_DBG_BUS11_SEL(x)                            (((x) & 0x3F) << 6)
#define BIT_AON_APB_DBG_BUS10_SEL(x)                            (((x) & 0x3F))

/* REG_AON_APB_PAD_DBG_BUS_SEL_CFG4 */

#define BIT_AON_APB_DBG_BUS19_SEL(x)                            (((x) & 0x3F) << 24)
#define BIT_AON_APB_DBG_BUS18_SEL(x)                            (((x) & 0x3F) << 18)
#define BIT_AON_APB_DBG_BUS17_SEL(x)                            (((x) & 0x3F) << 12)
#define BIT_AON_APB_DBG_BUS16_SEL(x)                            (((x) & 0x3F) << 6)
#define BIT_AON_APB_DBG_BUS15_SEL(x)                            (((x) & 0x3F))

/* REG_AON_APB_PAD_DBG_BUS_SEL_CFG5 */

#define BIT_AON_APB_DBG_BUS24_SEL(x)                            (((x) & 0x3F) << 24)
#define BIT_AON_APB_DBG_BUS23_SEL(x)                            (((x) & 0x3F) << 18)
#define BIT_AON_APB_DBG_BUS22_SEL(x)                            (((x) & 0x3F) << 12)
#define BIT_AON_APB_DBG_BUS21_SEL(x)                            (((x) & 0x3F) << 6)
#define BIT_AON_APB_DBG_BUS20_SEL(x)                            (((x) & 0x3F))

/* REG_AON_APB_PAD_DBG_BUS_SEL_CFG6 */

#define BIT_AON_APB_DBG_BUS29_SEL(x)                            (((x) & 0x3F) << 24)
#define BIT_AON_APB_DBG_BUS28_SEL(x)                            (((x) & 0x3F) << 18)
#define BIT_AON_APB_DBG_BUS27_SEL(x)                            (((x) & 0x3F) << 12)
#define BIT_AON_APB_DBG_BUS26_SEL(x)                            (((x) & 0x3F) << 6)
#define BIT_AON_APB_DBG_BUS25_SEL(x)                            (((x) & 0x3F))

/* REG_AON_APB_PAD_DBG_BUS_SEL_CFG7 */

#define BIT_AON_APB_DBG_BUS31_SEL(x)                            (((x) & 0x3F) << 6)
#define BIT_AON_APB_DBG_BUS30_SEL(x)                            (((x) & 0x3F))

/* REG_AON_APB_PAD_DBG_BUS_DATA_A */

#define BIT_AON_APB_PAD_DBG_BUS_DATA_A(x)                       (((x) & 0xFFFFFFFF))

/* REG_AON_APB_PAD_DBG_BUS_DATA_B */

#define BIT_AON_APB_PAD_DBG_BUS_DATA_B(x)                       (((x) & 0xFFFFFFFF))

/* REG_AON_APB_PAD_DBG_BUS_DATA_OUT */

#define BIT_AON_APB_PAD_DBG_BUS_DATA_OUT(x)                     (((x) & 0xFFFFFFFF))

/* REG_AON_APB_DBG_BUS_DATA_V3 */

#define BIT_AON_APB_DBG_BUS_DATA_V3(x)                          (((x) & 0xFFFFFFFF))

/* REG_AON_APB_DBG_BUS_DATA_PSCP */

#define BIT_AON_APB_DBG_BUS_DATA_PSCP(x)                        (((x) & 0xFFFFFFFF))

/* REG_AON_APB_DBG_BUS_DATA_AUDCP */

#define BIT_AON_APB_DBG_BUS_DATA_AUDCP(x)                       (((x) & 0xFFFFFFFF))

/* REG_AON_APB_SCC_DBG_BUS */

#define BIT_AON_APB_SCC_DBG_BUS(x)                              (((x) & 0xFFFFFFFF))

/* REG_AON_APB_DEBUG_FILTER_0 */

#define BIT_AON_APB_MATCH_SEL                                   BIT(19)
#define BIT_AON_APB_WAIT_OVER(x)                                (((x) & 0xFFFF) << 3)
#define BIT_AON_APB_ENABLE_COUNTER                              BIT(2)
#define BIT_AON_APB_ENABLE_FILTER                               BIT(1)
#define BIT_AON_APB_DEBUG_MODE                                  BIT(0)

/* REG_AON_APB_DEBUG_FILTER_1 */

#define BIT_AON_APB_ADDR_FLT(x)                                 (((x) & 0xFFFFFFFF))

/* REG_AON_APB_DEBUG_FILTER_2 */

#define BIT_AON_APB_ADDR_OVER(x)                                (((x) & 0xFFFFFFFF))

/* REG_AON_APB_DEBUG_FILTER_3 */

#define BIT_AON_APB_ADDR_DIFF(x)                                (((x) & 0xFFFFFFFF))

/* REG_AON_APB_DEBUG_FILTER_4 */

#define BIT_AON_APB_LATEST_ADDR(x)                              (((x) & 0xFFFFFFFF))

/* REG_AON_APB_DEBUG_FILTER_5 */

#define BIT_AON_APB_ADDR_MASK(x)                                (((x) & 0xFFFFFFFF))

/* REG_AON_APB_TPIU_DATA_TO_SERDES_SEL */

#define BIT_AON_APB_TPIU_TO_SERDES_SEL                          BIT(0)

/* REG_AON_APB_MTX_BUSMON_EB */

#define BIT_AON_APB_BUSMON_EB_DBD_MTX                           BIT(2)
#define BIT_AON_APB_BUSMON_EB_EAXI_MTX                          BIT(1)
#define BIT_AON_APB_BUSMON_EB_AON_MAIN_MTX                      BIT(0)

/* REG_AON_APB_AON_CHIP_ID0 */

#define BIT_AON_APB_AON_CHIP_ID0(x)                             (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AON_CHIP_ID1 */

#define BIT_AON_APB_AON_CHIP_ID1(x)                             (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AON_PLAT_ID0 */

#define BIT_AON_APB_AON_PLAT_ID0(x)                             (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AON_PLAT_ID1 */

#define BIT_AON_APB_AON_PLAT_ID1(x)                             (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AON_IMPL_ID */

#define BIT_AON_APB_AON_IMPL_ID(x)                              (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AON_MFT_ID */

#define BIT_AON_APB_AON_MFT_ID(x)                               (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AON_VER_ID */

#define BIT_AON_APB_AON_VER_ID(x)                               (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AON_CHIP_ID */

#define BIT_AON_APB_AON_CHIP_ID(x)                              (((x) & 0xFFFFFFFF))

/* REG_AON_APB_USER_RSV_FLAG1 */

#define BIT_AON_APB_USER_RSV_FLAG1_B1                           BIT(1)
#define BIT_AON_APB_USER_RSV_FLAG1_B0                           BIT(0)

/* REG_AON_APB_BOND_OPT0 */

#define BIT_AON_APB_BOND_OPTION0(x)                             (((x) & 0xFFFFFFFF))

/* REG_AON_APB_DEVICE_LIFE_CYCLE */

#define BIT_AON_APB_BOND_OPTION1(x)                             (((x) & 0xFFFFFFFF))

/* REG_AON_APB_RES_REG0 */

#define BIT_AON_APB_RES_REG0(x)                                 (((x) & 0xFFFFFFFF))

/* REG_AON_APB_RES_REG1 */

#define BIT_AON_APB_RES_REG1(x)                                 (((x) & 0xFFFFFFFF))

/* REG_AON_APB_CP_RFFE_RES_REG0 */

#define BIT_AON_APB_CP_RFFE_RES_REG0(x)                         (((x) & 0xFFFFFFFF))

/* REG_AON_APB_CP_RFFE_RES_REG1 */

#define BIT_AON_APB_CP_RFFE_RES_REG1(x)                         (((x) & 0xFFFFFFFF))

/* REG_AON_APB_CP_RFFE_RES_REG2 */

#define BIT_AON_APB_CP_RFFE_RES_REG2(x)                         (((x) & 0xFFFFFFFF))

/* REG_AON_APB_CP_RFFE_RES_REG3 */

#define BIT_AON_APB_CP_RFFE_RES_REG3(x)                         (((x) & 0xFFFFFFFF))

/* REG_AON_APB_CP_RFFE_RES_REG4 */

#define BIT_AON_APB_CP_RFFE_RES_REG4(x)                         (((x) & 0xFFFFFFFF))

/* REG_AON_APB_CP_RFFE_RES_REG5 */

#define BIT_AON_APB_CP_RFFE_RES_REG5(x)                         (((x) & 0xFFFFFFFF))


#endif /* AON_APB_H */


