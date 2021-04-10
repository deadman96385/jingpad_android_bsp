/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-18 10:53:58
 *
 */


#ifndef AON_APB_H
#define AON_APB_H

#define CTL_BASE_AON_APB 0x32090000


#define REG_AON_APB_APB_EB0                            ( CTL_BASE_AON_APB + 0x0000 )
#define REG_AON_APB_APB_EB1                            ( CTL_BASE_AON_APB + 0x0004 )
#define REG_AON_APB_APB_EB2                            ( CTL_BASE_AON_APB + 0x0008 )
#define REG_AON_APB_APB_RST0                           ( CTL_BASE_AON_APB + 0x000C )
#define REG_AON_APB_APB_RST1                           ( CTL_BASE_AON_APB + 0x0010 )
#define REG_AON_APB_APB_RST2                           ( CTL_BASE_AON_APB + 0x0014 )
#define REG_AON_APB_APB_RTC_EB0                        ( CTL_BASE_AON_APB + 0x0018 )
#define REG_AON_APB_PWR_CTRL                           ( CTL_BASE_AON_APB + 0x0024 )
#define REG_AON_APB_TS_CFG                             ( CTL_BASE_AON_APB + 0x0028 )
#define REG_AON_APB_BOOT_MODE                          ( CTL_BASE_AON_APB + 0x002C )
#define REG_AON_APB_BB_BG_CTRL                         ( CTL_BASE_AON_APB + 0x0030 )
#define REG_AON_APB_CP_ARM_JTAG_CTRL                   ( CTL_BASE_AON_APB + 0x0034 )
#define REG_AON_APB_DCXO_LC_REG0                       ( CTL_BASE_AON_APB + 0x003C )
#define REG_AON_APB_DCXO_LC_REG1                       ( CTL_BASE_AON_APB + 0x0040 )
#define REG_AON_APB_AUDCP_BOOT_PROT                    ( CTL_BASE_AON_APB + 0x0078 )
#define REG_AON_APB_AON_REG_PROT                       ( CTL_BASE_AON_APB + 0x007C )
#define REG_AON_APB_AON_APB_CLK_SEL                    ( CTL_BASE_AON_APB + 0x0080 )
#define REG_AON_APB_DAP_DJTAG_SEL                      ( CTL_BASE_AON_APB + 0x0084 )
#define REG_AON_APB_USER_RSV_FLAG1                     ( CTL_BASE_AON_APB + 0x0088 )
#define REG_AON_APB_CM4_SYS_SOFT_RST                   ( CTL_BASE_AON_APB + 0x008C )
#define REG_AON_APB_MDAR_SYS_HSDL_CFG                  ( CTL_BASE_AON_APB + 0x00C0 )
#define REG_AON_APB_AUTO_GATE_CTRL0                    ( CTL_BASE_AON_APB + 0x00D0 )
#define REG_AON_APB_AUTO_GATE_CTRL1                    ( CTL_BASE_AON_APB + 0x00D4 )
#define REG_AON_APB_AP_AXI_CTRL                        ( CTL_BASE_AON_APB + 0x00D8 )
#define REG_AON_APB_AON_CHIP_ID0                       ( CTL_BASE_AON_APB + 0x00E0 )
#define REG_AON_APB_AON_CHIP_ID1                       ( CTL_BASE_AON_APB + 0x00E4 )
#define REG_AON_APB_AON_PLAT_ID0                       ( CTL_BASE_AON_APB + 0x00E8 )
#define REG_AON_APB_AON_PLAT_ID1                       ( CTL_BASE_AON_APB + 0x00EC )
#define REG_AON_APB_AON_IMPL_ID                        ( CTL_BASE_AON_APB + 0x00F0 )
#define REG_AON_APB_AON_MFT_ID                         ( CTL_BASE_AON_APB + 0x00F4 )
#define REG_AON_APB_AON_VER_ID                         ( CTL_BASE_AON_APB + 0x00F8 )
#define REG_AON_APB_AON_CHIP_ID                        ( CTL_BASE_AON_APB + 0x00FC )
#define REG_AON_APB_CCIR_RCVR_CFG                      ( CTL_BASE_AON_APB + 0x0100 )
#define REG_AON_APB_PLL_BG_CFG                         ( CTL_BASE_AON_APB + 0x0108 )
#define REG_AON_APB_LVDSDIS_SEL                        ( CTL_BASE_AON_APB + 0x010C )
#define REG_AON_APB_AUTO_GATE_CTRL2                    ( CTL_BASE_AON_APB + 0x0114 )
#define REG_AON_APB_AUTO_GATE_CTRL3                    ( CTL_BASE_AON_APB + 0x0118 )
#define REG_AON_APB_APCPU_CLK_CTRL0                    ( CTL_BASE_AON_APB + 0x011C )
#define REG_AON_APB_CGM_ESE                            ( CTL_BASE_AON_APB + 0x0120 )
#define REG_AON_APB_SP_CFG_BUS                         ( CTL_BASE_AON_APB + 0x0124 )
#define REG_AON_APB_APB_RST3                           ( CTL_BASE_AON_APB + 0x0130 )
#define REG_AON_APB_RC100M_CFG                         ( CTL_BASE_AON_APB + 0x0134 )
#define REG_AON_APB_CGM_REG1                           ( CTL_BASE_AON_APB + 0x0138 )
#define REG_AON_APB_CGM_CLK_TOP_REG1                   ( CTL_BASE_AON_APB + 0x013C )
#define REG_AON_APB_AUDCP_DSP_CTRL0                    ( CTL_BASE_AON_APB + 0x0140 )
#define REG_AON_APB_AUDCP_DSP_CTRL1                    ( CTL_BASE_AON_APB + 0x0144 )
#define REG_AON_APB_AUDCP_CTRL                         ( CTL_BASE_AON_APB + 0x014C )
#define REG_AON_APB_WTLCP_LDSP_CTRL0                   ( CTL_BASE_AON_APB + 0x0150 )
#define REG_AON_APB_WTLCP_LDSP_CTRL1                   ( CTL_BASE_AON_APB + 0x0154 )
#define REG_AON_APB_WTLCP_TDSP_CTRL0                   ( CTL_BASE_AON_APB + 0x0158 )
#define REG_AON_APB_WTLCP_TDSP_CTRL1                   ( CTL_BASE_AON_APB + 0x015C )
#define REG_AON_APB_WTLCP_CTRL                         ( CTL_BASE_AON_APB + 0x0164 )
#define REG_AON_APB_WTL_WCDMA_EB                       ( CTL_BASE_AON_APB + 0x0168 )
#define REG_AON_APB_PCP_AON_EB                         ( CTL_BASE_AON_APB + 0x0170 )
#define REG_AON_APB_PCP_SOFT_RST                       ( CTL_BASE_AON_APB + 0x0174 )
#define REG_AON_APB_PUBCP_CTRL                         ( CTL_BASE_AON_APB + 0x0178 )
#define REG_AON_APB_VECTOR_VDSP                        ( CTL_BASE_AON_APB + 0x017C )
#define REG_AON_APB_WTLCP_LPC_CTRL                     ( CTL_BASE_AON_APB + 0x0180 )
#define REG_AON_APB_PUBCP_LPC_CTRL                     ( CTL_BASE_AON_APB + 0x0184 )
#define REG_AON_APB_AON_SOC_USB_CTRL                   ( CTL_BASE_AON_APB + 0x0190 )
#define REG_AON_APB_ESE_INT_MASK                       ( CTL_BASE_AON_APB + 0x0194 )
#define REG_AON_APB_SOFT_RST_AON_ADD1                  ( CTL_BASE_AON_APB + 0x01A0 )
#define REG_AON_APB_VDSP_INT_CTRL                      ( CTL_BASE_AON_APB + 0x01A4 )
#define REG_AON_APB_EB_AON_ADD1                        ( CTL_BASE_AON_APB + 0x01B0 )
#define REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG4             ( CTL_BASE_AON_APB + 0x01BC )
#define REG_AON_APB_DBG_DJTAG_CTRL                     ( CTL_BASE_AON_APB + 0x01C0 )
#define REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG0             ( CTL_BASE_AON_APB + 0x01C4 )
#define REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG1             ( CTL_BASE_AON_APB + 0x01C8 )
#define REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG2             ( CTL_BASE_AON_APB + 0x01CC )
#define REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG3             ( CTL_BASE_AON_APB + 0x01D0 )
#define REG_AON_APB_PAD_DBG_BUS_SEL_CFG1               ( CTL_BASE_AON_APB + 0x01D4 )
#define REG_AON_APB_PAD_DBG_BUS_SEL_CFG2               ( CTL_BASE_AON_APB + 0x01D8 )
#define REG_AON_APB_PAD_DBG_BUS_SEL_CFG3               ( CTL_BASE_AON_APB + 0x01DC )
#define REG_AON_APB_PAD_DBG_BUS_SEL_CFG4               ( CTL_BASE_AON_APB + 0x01E0 )
#define REG_AON_APB_PAD_DBG_BUS_SEL_CFG5               ( CTL_BASE_AON_APB + 0x01E4 )
#define REG_AON_APB_PAD_DBG_BUS_SEL_CFG6               ( CTL_BASE_AON_APB + 0x01E8 )
#define REG_AON_APB_PAD_DBG_BUS_SEL_CFG7               ( CTL_BASE_AON_APB + 0x01EC )
#define REG_AON_APB_PAD_DBG_BUS_DATA_A                 ( CTL_BASE_AON_APB + 0x01F0 )
#define REG_AON_APB_PAD_DBG_BUS_DATA_B                 ( CTL_BASE_AON_APB + 0x01F4 )
#define REG_AON_APB_PAD_DBG_BUS_DATA_OUT               ( CTL_BASE_AON_APB + 0x01F8 )
#define REG_AON_APB_MBIST_EFUSE_CTRL                   ( CTL_BASE_AON_APB + 0x01FC )
#define REG_AON_APB_OTG_PHY_TUNE                       ( CTL_BASE_AON_APB + 0x0200 )
#define REG_AON_APB_OTG_PHY_TEST                       ( CTL_BASE_AON_APB + 0x0204 )
#define REG_AON_APB_OTG_PHY_CTRL                       ( CTL_BASE_AON_APB + 0x0208 )
#define REG_AON_APB_OTG_CTRL0                          ( CTL_BASE_AON_APB + 0x020C )
#define REG_AON_APB_OTG_CTRL1                          ( CTL_BASE_AON_APB + 0x0210 )
#define REG_AON_APB_USB_CLK_REF_SEL                    ( CTL_BASE_AON_APB + 0x0214 )
#define REG_AON_APB_LVDSRF_CTRL                        ( CTL_BASE_AON_APB + 0x0218 )
#define REG_AON_APB_THM0_CTRL                          ( CTL_BASE_AON_APB + 0x021C )
#define REG_AON_APB_THM1_CTRL                          ( CTL_BASE_AON_APB + 0x0220 )
#define REG_AON_APB_THM2_CTRL                          ( CTL_BASE_AON_APB + 0x0224 )
#define REG_AON_APB_THM3_CTRL                          ( CTL_BASE_AON_APB + 0x0228 )
#define REG_AON_APB_OVERHEAT_CTRL                      ( CTL_BASE_AON_APB + 0x022C )
#define REG_AON_APB_PUBCP_SIM1_TOP_CTRL                ( CTL_BASE_AON_APB + 0x0230 )
#define REG_AON_APB_PUBCP_SIM2_TOP_CTRL                ( CTL_BASE_AON_APB + 0x0234 )
#define REG_AON_APB_PUBCP_SIM3_TOP_CTRL                ( CTL_BASE_AON_APB + 0x0238 )
#define REG_AON_APB_AP_SIM_TOP_CTRL                    ( CTL_BASE_AON_APB + 0x023C )
#define REG_AON_APB_APCPU_MONITOR_STATUS               ( CTL_BASE_AON_APB + 0x0280 )
#define REG_AON_APB_APCPU_DEBUG_PWR_LP_CTRL            ( CTL_BASE_AON_APB + 0x0284 )
#define REG_AON_APB_APCPU_GIC_COL_LP_CTRL              ( CTL_BASE_AON_APB + 0x0288 )
#define REG_AON_APB_APCPU_CLUSTER_ATB_LPC_CTRL         ( CTL_BASE_AON_APB + 0x028C )
#define REG_AON_APB_APCPU_CLUSTER_APB_LPC_CTRL         ( CTL_BASE_AON_APB + 0x0290 )
#define REG_AON_APB_APCPU_CLUSTER_GIC_LPC_CTRL         ( CTL_BASE_AON_APB + 0x0294 )
#define REG_AON_APB_APCPU_GIC600_GIC_LPC_CTRL          ( CTL_BASE_AON_APB + 0x0298 )
#define REG_AON_APB_APCPU_DBG_BLK_LPC_CTRL             ( CTL_BASE_AON_APB + 0x029C )
#define REG_AON_APB_APCPU_TOP_MTX_M0_LPC_CTRL          ( CTL_BASE_AON_APB + 0x0300 )
#define REG_AON_APB_APCPU_TOP_MTX_LPC_PU_NUM_CTRL      ( CTL_BASE_AON_APB + 0x0304 )
#define REG_AON_APB_APCPU_CLUSTER_SCU_LPC_CTRL         ( CTL_BASE_AON_APB + 0x0320 )
#define REG_AON_APB_APCPU_DDR_AB_LPC_CTRL              ( CTL_BASE_AON_APB + 0x0324 )
#define REG_AON_APB_APCPU_QOS_CTRL                     ( CTL_BASE_AON_APB + 0x0328 )
#define REG_AON_APB_MPLL0_CTRL                         ( CTL_BASE_AON_APB + 0x032C )
#define REG_AON_APB_MPLL1_CTRL                         ( CTL_BASE_AON_APB + 0x0330 )
#define REG_AON_APB_MPLL2_CTRL                         ( CTL_BASE_AON_APB + 0x0334 )
#define REG_AON_APB_MPLL3_CTRL                         ( CTL_BASE_AON_APB + 0x0338 )
#define REG_AON_APB_DPLL_CTRL                          ( CTL_BASE_AON_APB + 0x0340 )
#define REG_AON_APB_PUB_CLK_GATING_CTRL                ( CTL_BASE_AON_APB + 0x0344 )
#define REG_AON_APB_DDRPHY_VREP                        ( CTL_BASE_AON_APB + 0x0348 )
#define REG_AON_APB_CM42AON_LPC_CTRL                   ( CTL_BASE_AON_APB + 0x0380 )
#define REG_AON_APB_AON_MTX_MAIN_LPC_CTRL              ( CTL_BASE_AON_APB + 0x0384 )
#define REG_AON_APB_AON_MTX_M0_LPC_CTRL                ( CTL_BASE_AON_APB + 0x0388 )
#define REG_AON_APB_AON_MTX_M1_LPC_CTRL                ( CTL_BASE_AON_APB + 0x038C )
#define REG_AON_APB_AON_MTX_M2_LPC_CTRL                ( CTL_BASE_AON_APB + 0x0390 )
#define REG_AON_APB_AON_MTX_M3_LPC_CTRL                ( CTL_BASE_AON_APB + 0x0394 )
#define REG_AON_APB_AON_MTX_M4_LPC_CTRL                ( CTL_BASE_AON_APB + 0x0398 )
#define REG_AON_APB_AON_MTX_M5_LPC_CTRL                ( CTL_BASE_AON_APB + 0x039C )
#define REG_AON_APB_AON_MTX_M6_LPC_CTRL                ( CTL_BASE_AON_APB + 0x03A0 )
#define REG_AON_APB_AON_MTX_S0_LPC_CTRL                ( CTL_BASE_AON_APB + 0x03A4 )
#define REG_AON_APB_AON_MTX_S1_LPC_CTRL                ( CTL_BASE_AON_APB + 0x03A8 )
#define REG_AON_APB_AON_MTX_S2_LPC_CTRL                ( CTL_BASE_AON_APB + 0x03AC )
#define REG_AON_APB_AON_MTX_S3_LPC_CTRL                ( CTL_BASE_AON_APB + 0x03B0 )
#define REG_AON_APB_AON_MTX_S4_LPC_CTRL                ( CTL_BASE_AON_APB + 0x03B4 )
#define REG_AON_APB_AON_MTX_S5_LPC_CTRL                ( CTL_BASE_AON_APB + 0x03B8 )
#define REG_AON_APB_AON_MTX_S6_LPC_CTRL                ( CTL_BASE_AON_APB + 0x03BC )
#define REG_AON_APB_AON_MTX_S7_LPC_CTRL                ( CTL_BASE_AON_APB + 0x03C0 )
#define REG_AON_APB_AON_MTX_S8_LPC_CTRL                ( CTL_BASE_AON_APB + 0x03C4 )
#define REG_AON_APB_AON_MTX_S9_LPC_CTRL                ( CTL_BASE_AON_APB + 0x03C8 )
#define REG_AON_APB_AP2GPU_SLI_LPC_CTRL                ( CTL_BASE_AON_APB + 0x03CC )
#define REG_AON_APB_AP2MM_SLI_LPC_CTRL                 ( CTL_BASE_AON_APB + 0x03D0 )
#define REG_AON_APB_WTLCP2DDR_SLI_LPC_CTRL             ( CTL_BASE_AON_APB + 0x03D4 )
#define REG_AON_APB_APCPU2AP_SLI_LPC_CTRL              ( CTL_BASE_AON_APB + 0x03D8 )
#define REG_AON_APB_AUDCP2DDR_SLI_LPC_CTRL             ( CTL_BASE_AON_APB + 0x03DC )
#define REG_AON_APB_APCPU2DDR_SLI_LPC_CTRL             ( CTL_BASE_AON_APB + 0x03E0 )
#define REG_AON_APB_AON2DDR_BRG_LPC_CTRL               ( CTL_BASE_AON_APB + 0x03E4 )
#define REG_AON_APB_PUBCP2WTLCP_SLI_LPC_CTRL           ( CTL_BASE_AON_APB + 0x03E8 )
#define REG_AON_APB_AON_APB_FREQ_CTRL                  ( CTL_BASE_AON_APB + 0x0400 )
#define REG_AON_APB_MIPI_CSI_POWER_CTRL                ( CTL_BASE_AON_APB + 0x0408 )
#define REG_AON_APB_APCPU_MERGE_MTX_M0_LPC_CTRL        ( CTL_BASE_AON_APB + 0x0410 )
#define REG_AON_APB_APCPU_MERGE_MTX_M1_LPC_CTRL        ( CTL_BASE_AON_APB + 0x0414 )
#define REG_AON_APB_APCPU_MERGE_MTX_S0_LPC_CTRL        ( CTL_BASE_AON_APB + 0x0418 )
#define REG_AON_APB_GPU_MERGE_MTX_M0_LPC_CTRL          ( CTL_BASE_AON_APB + 0x041C )
#define REG_AON_APB_GPU_MERGE_MTX_M1_LPC_CTRL          ( CTL_BASE_AON_APB + 0x0420 )
#define REG_AON_APB_GPU_MERGE_MTX_S0_LPC_CTRL          ( CTL_BASE_AON_APB + 0x0424 )
#define REG_AON_APB_GPU2DDR_SLI_LPC_CTRL               ( CTL_BASE_AON_APB + 0x0428 )
#define REG_AON_APB_MM_DCAM2DDR_SLI_LPC_CTRL           ( CTL_BASE_AON_APB + 0x042C )
#define REG_AON_APB_MM_MTX2DDR_SLI_LPC_CTRL            ( CTL_BASE_AON_APB + 0x0430 )
#define REG_AON_APB_IPA12DDR_SLI_LPC_CTRL              ( CTL_BASE_AON_APB + 0x0434 )
#define REG_AON_APB_IPA22DDR_SLI_LPC_CTRL              ( CTL_BASE_AON_APB + 0x0438 )
#define REG_AON_APB_AI2DDR_SLI_LPC_CTRL                ( CTL_BASE_AON_APB + 0x043C )
#define REG_AON_APB_ESE2DDR_SLI_LPC_CTRL               ( CTL_BASE_AON_APB + 0x0440 )
#define REG_AON_APB_ESE2DDR_ASYNC_BRG_LPC_CTRL         ( CTL_BASE_AON_APB + 0x0444 )
#define REG_AON_APB_AP2IPA_SLI_LPC_CTRL                ( CTL_BASE_AON_APB + 0x0448 )
#define REG_AON_APB_AP2AI_SLI_LPC_CTRL                 ( CTL_BASE_AON_APB + 0x044C )
#define REG_AON_APB_AP2IPA_ASYNC_BRG_LPC_CTRL          ( CTL_BASE_AON_APB + 0x0450 )
#define REG_AON_APB_C_CHANNEL_SYNC_SEL_CFG             ( CTL_BASE_AON_APB + 0x0480 )
#define REG_AON_APB_APCPU_INT_ENABLE_CTRL0             ( CTL_BASE_AON_APB + 0x0500 )
#define REG_AON_APB_APCPU_INT_ENABLE_CTRL1             ( CTL_BASE_AON_APB + 0x0504 )
#define REG_AON_APB_APCPU_INT_ENABLE_CTRL2             ( CTL_BASE_AON_APB + 0x0508 )
#define REG_AON_APB_APCPU_INT_ENABLE_CTRL3             ( CTL_BASE_AON_APB + 0x050C )
#define REG_AON_APB_APCPU_INT_ENABLE_CTRL4             ( CTL_BASE_AON_APB + 0x0510 )
#define REG_AON_APB_APCPU_INT_ENABLE_CTRL5             ( CTL_BASE_AON_APB + 0x0514 )
#define REG_AON_APB_SDIO0_CTRL_REG                     ( CTL_BASE_AON_APB + 0x0520 )
#define REG_AON_APB_SDIO1_CTRL_REG                     ( CTL_BASE_AON_APB + 0x0524 )
#define REG_AON_APB_SDIO2_CTRL_REG                     ( CTL_BASE_AON_APB + 0x0528 )
#define REG_AON_APB_EMMC_CTRL_REG                      ( CTL_BASE_AON_APB + 0x052C )
#define REG_AON_APB_WDG_RST_FLAG                       ( CTL_BASE_AON_APB + 0x0A24 )
#define REG_AON_APB_BOND_OPT0                          ( CTL_BASE_AON_APB + 0x0A3C )
#define REG_AON_APB_DEVICE_LIFE_CYCLE                  ( CTL_BASE_AON_APB + 0x0A40 )
#define REG_AON_APB_RES_REG0                           ( CTL_BASE_AON_APB + 0x0A44 )
#define REG_AON_APB_RES_REG1                           ( CTL_BASE_AON_APB + 0x0A48 )
#define REG_AON_APB_AON_MTX_PROT_CFG                   ( CTL_BASE_AON_APB + 0x0A58 )
#define REG_AON_APB_PLL_LOCK_OUT_SEL                   ( CTL_BASE_AON_APB + 0x0A64 )
#define REG_AON_APB_CPU2DDR_BRIDGE_DEBUG_SIGNAL_R      ( CTL_BASE_AON_APB + 0x0A70 )
#define REG_AON_APB_AON2DDR_BRIDGE_DEBUG_SIGNAL_W      ( CTL_BASE_AON_APB + 0x0A74 )
#define REG_AON_APB_AON2DDR_BRIDGE_DEBUG_SIGNAL_LIST   ( CTL_BASE_AON_APB + 0x0A78 )
#define REG_AON_APB_AUD2DDR_BRIDGE_DEBUG_SIGNAL_R      ( CTL_BASE_AON_APB + 0x0A7C )
#define REG_AON_APB_WTL2DDR_BRIDGE_DEBUG_SIGNAL_R      ( CTL_BASE_AON_APB + 0x0A80 )
#define REG_AON_APB_DEBUG_FILTER_0                     ( CTL_BASE_AON_APB + 0x0A90 )
#define REG_AON_APB_DEBUG_FILTER_1                     ( CTL_BASE_AON_APB + 0x0A94 )
#define REG_AON_APB_DEBUG_FILTER_2                     ( CTL_BASE_AON_APB + 0x0A98 )
#define REG_AON_APB_DEBUG_FILTER_3                     ( CTL_BASE_AON_APB + 0x0A9C )
#define REG_AON_APB_DEBUG_FILTER_4                     ( CTL_BASE_AON_APB + 0x0AA0 )
#define REG_AON_APB_DEBUG_FILTER_5                     ( CTL_BASE_AON_APB + 0x0AA4 )
#define REG_AON_APB_LEAKAGE_MAGIC_WORD                 ( CTL_BASE_AON_APB + 0x0B00 )
#define REG_AON_APB_LEAKAGE_SWITCH                     ( CTL_BASE_AON_APB + 0x0B04 )
#define REG_AON_APB_FUNC_TEST_BOOT_ADDR                ( CTL_BASE_AON_APB + 0x0B10 )
#define REG_AON_APB_CGM_RESCUE                         ( CTL_BASE_AON_APB + 0x0B14 )
#define REG_AON_APB_AON_SDIO                           ( CTL_BASE_AON_APB + 0x0B2C )
#define REG_AON_APB_SP_WAKEUP_MASK_EN0                 ( CTL_BASE_AON_APB + 0x0B84 )
#define REG_AON_APB_SP_WAKEUP_MASK_EN1                 ( CTL_BASE_AON_APB + 0x0B88 )
#define REG_AON_APB_SP_WAKEUP_MASK_EN2                 ( CTL_BASE_AON_APB + 0x0B8C )
#define REG_AON_APB_DBG_BUS_DATA_WTLCP                 ( CTL_BASE_AON_APB + 0x0B90 )
#define REG_AON_APB_DBG_BUS_DATA_PUBCP                 ( CTL_BASE_AON_APB + 0x0B94 )
#define REG_AON_APB_DBG_BUS_DATA_AUDCP                 ( CTL_BASE_AON_APB + 0x0B98 )
#define REG_AON_APB_SDIO_EMMC_POWER_STATUS             ( CTL_BASE_AON_APB + 0x0B9C )
#define REG_AON_APB_SCC_DBG_BUS                        ( CTL_BASE_AON_APB + 0x0C00 )
#define REG_AON_APB_AON_FUNC_CTRL_0                    ( CTL_BASE_AON_APB + 0x0C04 )
#define REG_AON_APB_AON_FUNC_CTRL_1                    ( CTL_BASE_AON_APB + 0x0C08 )

/* REG_AON_APB_APB_EB0 */

#define BIT_AON_APB_SERDES_DPHY_REF_EB                          BIT(20)
#define BIT_AON_APB_SERDES_DPHY_CFG_EB                          BIT(19)
#define BIT_AON_APB_LVDIS_PLL_DIV_EN                            BIT(18)
#define BIT_AON_APB_CSSYS_PUB_EB                                BIT(17)
#define BIT_AON_APB_CSSYS_APB_EB                                BIT(16)
#define BIT_AON_APB_CSSYS_EB                                    BIT(15)
#define BIT_AON_APB_APCPU_DAP_EB                                BIT(14)
#define BIT_AON_APB_AI_EB                                       BIT(13)
#define BIT_AON_APB_MSPI_EB                                     BIT(12)
#define BIT_AON_APB_GPU_EB                                      BIT(11)
#define BIT_AON_APB_SP_AHB_CLK_SOFT_EB                          BIT(10)
#define BIT_AON_APB_MM_EB                                       BIT(9)
#define BIT_AON_APB_IPA_EB                                      BIT(8)
#define BIT_AON_APB_PROBE_EB                                    BIT(7)
#define BIT_AON_APB_AUX2_EB                                     BIT(6)
#define BIT_AON_APB_AUX1_EB                                     BIT(5)
#define BIT_AON_APB_AUX0_EB                                     BIT(4)
#define BIT_AON_APB_DJTAG_EB                                    BIT(3)
#define BIT_AON_APB_DJTAG_TCK_EB                                BIT(2)
#define BIT_AON_APB_RFTI_EB                                     BIT(1)
#define BIT_AON_APB_RC100M_CAL_EB                               BIT(0)

/* REG_AON_APB_APB_EB1 */

#define BIT_AON_APB_SCC_EB                                      BIT(20)
#define BIT_AON_APB_AON_IIS_EB                                  BIT(19)
#define BIT_AON_APB_DEBUG_FILTER_EB                             BIT(18)
#define BIT_AON_APB_APCPU_TS0_EB                                BIT(17)
#define BIT_AON_APB_THM3_EB                                     BIT(16)
#define BIT_AON_APB_UFS_AO_EB                                   BIT(15)
#define BIT_AON_APB_I2C1_EB                                     BIT(14)
#define BIT_AON_APB_CKG_EB                                      BIT(13)
#define BIT_AON_APB_ANA_EB                                      BIT(12)
#define BIT_AON_APB_PIN_EB                                      BIT(11)
#define BIT_AON_APB_SPLK_EB                                     BIT(10)
#define BIT_AON_APB_OTG_PHY_EB                                  BIT(9)
#define BIT_AON_APB_OTG_UTMI_EB                                 BIT(8)
#define BIT_AON_APB_DVFS_TOP_EB                                 BIT(7)
#define BIT_AON_APB_AON_TMR_EB                                  BIT(6)
#define BIT_AON_APB_AP_SYST_EB                                  BIT(5)
#define BIT_AON_APB_AON_SYST_EB                                 BIT(4)
#define BIT_AON_APB_KPD_EB                                      BIT(3)
#define BIT_AON_APB_MBOX_EB                                     BIT(2)
#define BIT_AON_APB_GPIO_EB                                     BIT(1)
#define BIT_AON_APB_EFUSE_EB                                    BIT(0)

/* REG_AON_APB_APB_EB2 */

#define BIT_AON_APB_SERDES_EB                                   BIT(31)
#define BIT_AON_APB_APCPU_WDG_EB                                BIT(30)
#define BIT_AON_APB_AP_WDG_EB                                   BIT(29)
#define BIT_AON_APB_PWM3_EB                                     BIT(28)
#define BIT_AON_APB_PWM2_EB                                     BIT(27)
#define BIT_AON_APB_PWM1_EB                                     BIT(26)
#define BIT_AON_APB_PWM0_EB                                     BIT(25)
#define BIT_AON_APB_AP_TMR2_EB                                  BIT(24)
#define BIT_AON_APB_AP_TMR1_EB                                  BIT(23)
#define BIT_AON_APB_AP_TMR0_EB                                  BIT(22)
#define BIT_AON_APB_WTLCP_INTC_EB                               BIT(21)
#define BIT_AON_APB_WTLCP_LDSP_INTC_EB                          BIT(20)
#define BIT_AON_APB_WTLCP_TGDSP_INTC_EB                         BIT(19)
#define BIT_AON_APB_PUBCP_INTC_EB                               BIT(18)
#define BIT_AON_APB_AUDCP_INTC_EB                               BIT(17)
#define BIT_AON_APB_AP_INTC5_EB                                 BIT(16)
#define BIT_AON_APB_AP_INTC4_EB                                 BIT(15)
#define BIT_AON_APB_AP_INTC3_EB                                 BIT(14)
#define BIT_AON_APB_AP_INTC2_EB                                 BIT(13)
#define BIT_AON_APB_AP_INTC1_EB                                 BIT(12)
#define BIT_AON_APB_AP_INTC0_EB                                 BIT(11)
#define BIT_AON_APB_EIC_EB                                      BIT(10)
#define BIT_AON_APB_ADI_EB                                      BIT(9)
#define BIT_AON_APB_PMU_EB                                      BIT(8)
#define BIT_AON_APB_I2C0_EB                                     BIT(7)
#define BIT_AON_APB_PUBCP_SIM2_AON_TOP_EB                       BIT(6)
#define BIT_AON_APB_PUBCP_SIM1_AON_TOP_EB                       BIT(5)
#define BIT_AON_APB_PUBCP_SIM0_AON_TOP_EB                       BIT(4)
#define BIT_AON_APB_AP_SIM_AON_TOP_EB                           BIT(3)
#define BIT_AON_APB_THM2_EB                                     BIT(2)
#define BIT_AON_APB_THM1_EB                                     BIT(1)
#define BIT_AON_APB_THM0_EB                                     BIT(0)

/* REG_AON_APB_APB_RST0 */

#define BIT_AON_APB_SERDES_DPHY_APB_SOFT_RST                    BIT(9)
#define BIT_AON_APB_SERDES_DPHY_SOFT_RST                        BIT(8)
#define BIT_AON_APB_LVDSDIS_SOFT_RST                            BIT(7)
#define BIT_AON_APB_DAP_MTX_SOFT_RST                            BIT(6)
#define BIT_AON_APB_MSPI1_SOFT_RST                              BIT(5)
#define BIT_AON_APB_MSPI0_SOFT_RST                              BIT(4)
#define BIT_AON_APB_BB_CAL_SOFT_RST                             BIT(3)
#define BIT_AON_APB_DCXO_LC_SOFT_RST                            BIT(2)
#define BIT_AON_APB_RFTI_SOFT_RST                               BIT(1)
#define BIT_AON_APB_RC100M_CAL_SOFT_RST                         BIT(0)

/* REG_AON_APB_APB_RST1 */

#define BIT_AON_APB_SCC_SOFT_RST                                BIT(20)
#define BIT_AON_APB_AON_IIS_SOFT_RST                            BIT(19)
#define BIT_AON_APB_DEBUG_FILTER_SOFT_RST                       BIT(18)
#define BIT_AON_APB_APCPU_TS0_SOFT_RST                          BIT(17)
#define BIT_AON_APB_THM3_SOFT_RST                               BIT(16)
#define BIT_AON_APB_UFS_AO_SOFT_RST                             BIT(15)
#define BIT_AON_APB_I2C1_SOFT_RST                               BIT(14)
#define BIT_AON_APB_CKG_SOFT_RST                                BIT(13)
#define BIT_AON_APB_ANA_SOFT_RST                                BIT(12)
#define BIT_AON_APB_PIN_SOFT_RST                                BIT(11)
#define BIT_AON_APB_SPLK_SOFT_RST                               BIT(10)
#define BIT_AON_APB_OTG_PHY_SOFT_RST                            BIT(9)
#define BIT_AON_APB_OTG_UTMI_SOFT_RST                           BIT(8)
#define BIT_AON_APB_DVFS_TOP_SOFT_RST                           BIT(7)
#define BIT_AON_APB_AON_TMR_SOFT_RST                            BIT(6)
#define BIT_AON_APB_AP_SYST_SOFT_RST                            BIT(5)
#define BIT_AON_APB_AON_SYST_SOFT_RST                           BIT(4)
#define BIT_AON_APB_KPD_SOFT_RST                                BIT(3)
#define BIT_AON_APB_MBOX_SOFT_RST                               BIT(2)
#define BIT_AON_APB_GPIO_SOFT_RST                               BIT(1)
#define BIT_AON_APB_EFUSE_SOFT_RST                              BIT(0)

/* REG_AON_APB_APB_RST2 */

#define BIT_AON_APB_SERDES_SOFT_RST                             BIT(31)
#define BIT_AON_APB_APCPU_WDG_SOFT_RST                          BIT(30)
#define BIT_AON_APB_AP_WDG_SOFT_RST                             BIT(29)
#define BIT_AON_APB_PWM3_SOFT_RST                               BIT(28)
#define BIT_AON_APB_PWM2_SOFT_RST                               BIT(27)
#define BIT_AON_APB_PWM1_SOFT_RST                               BIT(26)
#define BIT_AON_APB_PWM0_SOFT_RST                               BIT(25)
#define BIT_AON_APB_AP_TMR2_SOFT_RST                            BIT(24)
#define BIT_AON_APB_AP_TMR1_SOFT_RST                            BIT(23)
#define BIT_AON_APB_AP_TMR0_SOFT_RST                            BIT(22)
#define BIT_AON_APB_WTLCP_INTC_SOFT_RST                         BIT(21)
#define BIT_AON_APB_WTLCP_LDSP_INTC_SOFT_RST                    BIT(20)
#define BIT_AON_APB_WTLCP_TGDSP_INTC_SOFT_RST                   BIT(19)
#define BIT_AON_APB_PUBCP_INTC_SOFT_RST                         BIT(18)
#define BIT_AON_APB_AUDCP_INTC_SOFT_RST                         BIT(17)
#define BIT_AON_APB_AP_INTC5_SOFT_RST                           BIT(16)
#define BIT_AON_APB_AP_INTC4_SOFT_RST                           BIT(15)
#define BIT_AON_APB_AP_INTC3_SOFT_RST                           BIT(14)
#define BIT_AON_APB_AP_INTC2_SOFT_RST                           BIT(13)
#define BIT_AON_APB_AP_INTC1_SOFT_RST                           BIT(12)
#define BIT_AON_APB_AP_INTC0_SOFT_RST                           BIT(11)
#define BIT_AON_APB_EIC_SOFT_RST                                BIT(10)
#define BIT_AON_APB_ADI_SOFT_RST                                BIT(9)
#define BIT_AON_APB_PMU_SOFT_RST                                BIT(8)
#define BIT_AON_APB_I2C0_SOFT_RST                               BIT(7)
#define BIT_AON_APB_PUBCP_SIM2_AON_TOP_SOFT_RST                 BIT(6)
#define BIT_AON_APB_PUBCP_SIM1_AON_TOP_SOFT_RST                 BIT(5)
#define BIT_AON_APB_PUBCP_SIM0_AON_TOP_SOFT_RST                 BIT(4)
#define BIT_AON_APB_AP_SIM_AON_TOP_SOFT_RST                     BIT(3)
#define BIT_AON_APB_THM2_SOFT_RST                               BIT(2)
#define BIT_AON_APB_THM1_SOFT_RST                               BIT(1)
#define BIT_AON_APB_THM0_SOFT_RST                               BIT(0)

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

/* REG_AON_APB_PWR_CTRL */

#define BIT_AON_APB_EFUSE_PWON_RD_END_FLAG                      BIT(2)

/* REG_AON_APB_TS_CFG */

#define BIT_AON_APB_DBG_TRACE_CTRL_EN                           BIT(16)
#define BIT_AON_APB_EVENTACK_RESTARTREQ_TS01                    BIT(4)
#define BIT_AON_APB_EVENT_RESTARTREQ_TS01                       BIT(1)
#define BIT_AON_APB_EVENT_HALTREQ_TS01                          BIT(0)

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

/* REG_AON_APB_BB_BG_CTRL */

#define BIT_AON_APB_BB_BG_AUTO_PD_EN                            BIT(3)
#define BIT_AON_APB_BB_BG_SLP_PD_EN                             BIT(2)
#define BIT_AON_APB_BB_BG_FORCE_ON                              BIT(1)
#define BIT_AON_APB_BB_BG_FORCE_PD                              BIT(0)

/* REG_AON_APB_CP_ARM_JTAG_CTRL */

#define BIT_AON_APB_AGCP_DSP_JTAG_MODE                          BIT(3)
#define BIT_AON_APB_CP_ARM_JTAG_PIN_SEL(x)                      (((x) & 0x7))

/* REG_AON_APB_DCXO_LC_REG0 */

#define BIT_AON_APB_DCXO_LC_FLAG                                BIT(8)
#define BIT_AON_APB_DCXO_LC_FLAG_CLR                            BIT(1)
#define BIT_AON_APB_DCXO_LC_CNT_CLR                             BIT(0)

/* REG_AON_APB_DCXO_LC_REG1 */

#define BIT_AON_APB_DCXO_LC_CNT(x)                              (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AUDCP_BOOT_PROT */

#define BIT_AON_APB_AUDCP_BOOTCTRL_PROT                         BIT(31)
#define BIT_AON_APB_AUDCP_REG_PROT_VAL(x)                       (((x) & 0xFFFF))

/* REG_AON_APB_AON_REG_PROT */

#define BIT_AON_APB_LDSP_CTRL_PROT                              BIT(31)
#define BIT_AON_APB_REG_PROT_VAL(x)                             (((x) & 0xFFFF))

/* REG_AON_APB_AON_APB_CLK_SEL */

#define BIT_AON_APB_CGM_AON_APB_LP_SEL(x)                       (((x) & 0x7))

/* REG_AON_APB_DAP_DJTAG_SEL */

#define BIT_AON_APB_DAP_DBGPWRUP_SOFT_EN                        BIT(2)
#define BIT_AON_APB_DAP_SYSPWRUP_SOFT_EN                        BIT(1)
#define BIT_AON_APB_DAP_DJTAG_EN                                BIT(0)

/* REG_AON_APB_USER_RSV_FLAG1 */

#define BIT_AON_APB_USER_RSV_FLAG1_B1                           BIT(1)
#define BIT_AON_APB_USER_RSV_FLAG1_B0                           BIT(0)

/* REG_AON_APB_CM4_SYS_SOFT_RST */

#define BIT_AON_APB_CM4_SYS_SOFT_RST                            BIT(4)
#define BIT_AON_APB_CM4_CORE_SOFT_RST                           BIT(0)

/* REG_AON_APB_MDAR_SYS_HSDL_CFG */

#define BIT_AON_APB_MDAR_SYS_HSDL_CFG(x)                        (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AUTO_GATE_CTRL0 */

#define BIT_AON_APB_CGM_AP_MM_FORCE_EN                          BIT(30)
#define BIT_AON_APB_CGM_AP_MM_AUTO_GATE_SEL                     BIT(29)
#define BIT_AON_APB_CGM_EMC_FORCE_EN                            BIT(28)
#define BIT_AON_APB_CGM_EMC_AUTO_GATE_SEL                       BIT(27)
#define BIT_AON_APB_CGM_MM_ISP_RAW_FORCE_EN                     BIT(26)
#define BIT_AON_APB_CGM_MM_ISP_RAW_AUTO_GATE_SEL                BIT(25)
#define BIT_AON_APB_CGM_MM_ISP_YUV_FORCE_EN                     BIT(24)
#define BIT_AON_APB_CGM_MM_ISP_YUV_AUTO_GATE_SEL                BIT(23)
#define BIT_AON_APB_CGM_AON_APB_PUB_FORCE_EN                    BIT(22)
#define BIT_AON_APB_CGM_AON_APB_PUB_AUTO_GATE_SEL               BIT(21)
#define BIT_AON_APB_CGM_AON_APB_AUDCP_FORCE_EN                  BIT(20)
#define BIT_AON_APB_CGM_AON_APB_AUDCP_AUTO_GATE_SEL             BIT(19)
#define BIT_AON_APB_CGM_AON_APB_PUBCP_FORCE_EN                  BIT(18)
#define BIT_AON_APB_CGM_AON_APB_PUBCP_AUTO_GATE_SEL             BIT(17)
#define BIT_AON_APB_CGM_AON_APB_WTLCP_FORCE_EN                  BIT(16)
#define BIT_AON_APB_CGM_AON_APB_WTLCP_AUTO_GATE_SEL             BIT(15)
#define BIT_AON_APB_CGM_AON_APB_AP_FORCE_EN                     BIT(14)
#define BIT_AON_APB_CGM_AON_APB_AP_AUTO_GATE_SEL                BIT(13)
#define BIT_AON_APB_CGM_AP_AXI_FORCE_EN                         BIT(12)
#define BIT_AON_APB_CGM_AP_AXI_AUTO_GATE_SEL                    BIT(11)
#define BIT_AON_APB_CGM_ESE_SYS_FORCE_EN                        BIT(10)
#define BIT_AON_APB_CGM_ESE_SYS_AUTO_GATE_SEL                   BIT(9)
#define BIT_AON_APB_CGM_AP_GPU_FORCE_EN                         BIT(8)
#define BIT_AON_APB_CGM_AP_GPU_AUTO_GATE_SEL                    BIT(7)
#define BIT_AON_APB_CGM_AP_AI_FORCE_EN                          BIT(6)
#define BIT_AON_APB_CGM_AP_AI_AUTO_GATE_SEL                     BIT(5)
#define BIT_AON_APB_CGM_GPU_MEM_FORCE_EN                        BIT(4)
#define BIT_AON_APB_CGM_GPU_MEM_AUTO_GATE_SEL                   BIT(3)
#define BIT_AON_APB_CGM_APCPU_PMU_AUTO_GATE_SEL                 BIT(2)
#define BIT_AON_APB_CGM_APCPU_PMU_FORCE_EN                      BIT(1)
#define BIT_AON_APB_MBOX_AUTO_GATE_SEL                          BIT(0)

/* REG_AON_APB_AUTO_GATE_CTRL1 */

#define BIT_AON_APB_CGM_DMC_REF_AUTO_GATE_SEL                   BIT(4)
#define BIT_AON_APB_CGM_TOP_DVFS_ROOT_AUTO_GATE_SEL             BIT(3)
#define BIT_AON_APB_CGM_TOP_DVFS_ROOT_FORCE_EN                  BIT(2)
#define BIT_AON_APB_CGM_AON_APB_ESE_AUTO_GATE_SEL               BIT(1)
#define BIT_AON_APB_CGM_AON_APB_ESE_FORCE_EN                    BIT(0)

/* REG_AON_APB_AP_AXI_CTRL */

#define BIT_AON_APB_CGM_AP_AXI_AUTO_FREQ_DOWN_CTRL_SEL          BIT(3)
#define BIT_AON_APB_CGM_AP_AXI_AUTO_FREQ_DOWN_EN                BIT(2)
#define BIT_AON_APB_CGM_AP_AXI_SEL_IDLE(x)                      (((x) & 0x3))

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

/* REG_AON_APB_CCIR_RCVR_CFG */

#define BIT_AON_APB_ANALOG_PLL_RSV(x)                           (((x) & 0xFFFF) << 16)
#define BIT_AON_APB_ANALOG_TESTMUX(x)                           (((x) & 0xFFFF))

/* REG_AON_APB_PLL_BG_CFG */

#define BIT_AON_APB_PLL_BG_RSV(x)                               (((x) & 0x3F))

/* REG_AON_APB_LVDSDIS_SEL */

#define BIT_AON_APB_LVDSDIS_LOG_SEL(x)                          (((x) & 0x3) << 1)
#define BIT_AON_APB_LVDSDIS_DBG_SEL                             BIT(0)

/* REG_AON_APB_AUTO_GATE_CTRL2 */

#define BIT_AON_APB_CGM_WCDMA_ROOT_FORCE_EN                     BIT(5)
#define BIT_AON_APB_CGM_WCDMA_ROOT_AUTO_GATE_SEL                BIT(4)
#define BIT_AON_APB_CGM_WCDMA_PUBCP_FORCE_EN                    BIT(3)
#define BIT_AON_APB_CGM_WCDMA_PUBCP_AUTO_GATE_SEL               BIT(2)
#define BIT_AON_APB_CGM_WCDMA_WTLCP_FORCE_EN                    BIT(1)
#define BIT_AON_APB_CGM_WCDMA_WTLCP_AUTO_GATE_SEL               BIT(0)

/* REG_AON_APB_AUTO_GATE_CTRL3 */

#define BIT_AON_APB_CGM_PERIPH_AUTO_GATE_EN                     BIT(13)
#define BIT_AON_APB_CGM_GIC_AUTO_GATE_EN                        BIT(12)
#define BIT_AON_APB_CGM_ACP_AUTO_GATE_EN                        BIT(11)
#define BIT_AON_APB_CGM_AXI_PERIPH_AUTO_GATE_EN                 BIT(10)
#define BIT_AON_APB_CGM_ACE_AUTO_GATE_EN                        BIT(9)
#define BIT_AON_APB_CGM_SCU_AUTO_GATE_EN                        BIT(8)
#define BIT_AON_APB_CGM_CORE7_AUTO_GATE_EN                      BIT(7)
#define BIT_AON_APB_CGM_CORE6_AUTO_GATE_EN                      BIT(6)
#define BIT_AON_APB_CGM_CORE5_AUTO_GATE_EN                      BIT(5)
#define BIT_AON_APB_CGM_CORE4_AUTO_GATE_EN                      BIT(4)
#define BIT_AON_APB_CGM_CORE3_AUTO_GATE_EN                      BIT(3)
#define BIT_AON_APB_CGM_CORE2_AUTO_GATE_EN                      BIT(2)
#define BIT_AON_APB_CGM_CORE1_AUTO_GATE_EN                      BIT(1)
#define BIT_AON_APB_CGM_CORE0_AUTO_GATE_EN                      BIT(0)

/* REG_AON_APB_APCPU_CLK_CTRL0 */

#define BIT_AON_APB_APCPU_CORE_WAKEUP_ACE_CLK_EN                BIT(1)
#define BIT_AON_APB_APCPU_CORE_WAKEUP_SCU_CLK_EN                BIT(0)

/* REG_AON_APB_CGM_ESE */

#define BIT_AON_APB_REG_ESE_AUTO_SWITCH_RCO_BYPASS              BIT(2)
#define BIT_AON_APB_CGM_ESE_SOURCE_SEL(x)                       (((x) & 0x3))

/* REG_AON_APB_SP_CFG_BUS */

#define BIT_AON_APB_SP_AHB_CLK_SOFT_EN                          BIT(7)
#define BIT_AON_APB_CM4_SLEEPING_STAT                           BIT(6)
#define BIT_AON_APB_CM4_LOCKUP_STAT                             BIT(5)
#define BIT_AON_APB_CM4_SOFT_MPUDIS                             BIT(4)
#define BIT_AON_APB_MMTX_SLEEP_CM4_PUB_WR                       BIT(3)
#define BIT_AON_APB_MMTX_SLEEP_CM4_PUB_RD                       BIT(2)
#define BIT_AON_APB_INT_REQ_CM4_SOFT                            BIT(1)
#define BIT_AON_APB_SP_CFG_BUS_SLEEP                            BIT(0)

/* REG_AON_APB_APB_RST3 */

#define BIT_AON_APB_DJTAG_AI_SOFT_RST                           BIT(12)
#define BIT_AON_APB_DJTAG_IPA_SOFT_RST                          BIT(11)
#define BIT_AON_APB_DJTAG_SOFT_RST                              BIT(10)
#define BIT_AON_APB_DJTAG_PUB0_SOFT_RST                         BIT(9)
#define BIT_AON_APB_DJTAG_AON_SOFT_RST                          BIT(8)
#define BIT_AON_APB_DJTAG_AUDCP_SOFT_RST                        BIT(7)
#define BIT_AON_APB_DJTAG_WTLCP_SOFT_RST                        BIT(6)
#define BIT_AON_APB_DJTAG_PUBCP_SOFT_RST                        BIT(5)
#define BIT_AON_APB_DJTAG_MM_SOFT_RST                           BIT(4)
#define BIT_AON_APB_DJTAG_ESE_SOFT_RST                          BIT(3)
#define BIT_AON_APB_DJTAG_GPU_SOFT_RST                          BIT(2)
#define BIT_AON_APB_DJTAG_APCPU_SOFT_RST                        BIT(1)
#define BIT_AON_APB_DJTAG_AP_SOFT_RST                           BIT(0)

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

/* REG_AON_APB_CGM_REG1 */

#define BIT_AON_APB_LTE_PCCSCC_RFTI_CLK_SW_CFG(x)               (((x) & 0xFF) << 24)
#define BIT_AON_APB_CGM_UFS_AO_EN                               BIT(23)
#define BIT_AON_APB_CGM_USB_SUSPEND_EN                          BIT(22)
#define BIT_AON_APB_CGM_LPLL1_WTLCP_SEL                         BIT(21)
#define BIT_AON_APB_CGM_LPLL0_WTLCP_SEL                         BIT(20)
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
#define BIT_AON_APB_CGM_DSI_CSI_TEST_EB                         BIT(8)
#define BIT_AON_APB_CGM_MDAR_CHK_EN                             BIT(7)
#define BIT_AON_APB_CGM_26M_LVDSDIS_EN                          BIT(6)
#define BIT_AON_APB_CGM_LVDSRF_CALI_EN                          BIT(5)
#define BIT_AON_APB_CGM_RFTI2_LTH_EN                            BIT(4)
#define BIT_AON_APB_CGM_RFTI2_XO_EN                             BIT(3)
#define BIT_AON_APB_CGM_RFTI1_LTH_EN                            BIT(2)
#define BIT_AON_APB_CGM_RFTI1_XO_EN                             BIT(1)
#define BIT_AON_APB_CGM_RFTI_SBI_EN                             BIT(0)

/* REG_AON_APB_CGM_CLK_TOP_REG1 */

#define BIT_AON_APB_SOFT_DDR0_CKG_1X_EN                         BIT(26)
#define BIT_AON_APB_SOFT_DDR0_DATA_RET                          BIT(23)
#define BIT_AON_APB_LIGHT_SLEEP_DDR0_DATA_RET_EN                BIT(21)
#define BIT_AON_APB_EMC0_CKG_SEL_LOAD                           BIT(19)
#define BIT_AON_APB_CLK_DEBUG_TS_EB                             BIT(18)
#define BIT_AON_APB_ESE_EFUSE_CTRL_EB                           BIT(17)
#define BIT_AON_APB_AAPC_CLK_TEST_EB                            BIT(16)
#define BIT_AON_APB_CGM_CPHY_CFG_EN                             BIT(15)
#define BIT_AON_APB_ALL_PLL_TEST_EB                             BIT(14)
#define BIT_AON_APB_CGM_WCDMA_ICI_EN                            BIT(13)
#define BIT_AON_APB_CGM_RFTI_RX_WD_EN                           BIT(12)
#define BIT_AON_APB_CGM_RFTI_TX_WD_EN                           BIT(11)
#define BIT_AON_APB_CGM_WCDMA_EN                                BIT(10)
#define BIT_AON_APB_CGM_EMMC_2X_EN                              BIT(9)
#define BIT_AON_APB_CGM_EMMC_1X_EN                              BIT(8)
#define BIT_AON_APB_CGM_SDIO2_1X_EN                             BIT(7)
#define BIT_AON_APB_CGM_SDIO2_2X_EN                             BIT(6)
#define BIT_AON_APB_CGM_SDIO1_1X_EN                             BIT(5)
#define BIT_AON_APB_CGM_SDIO1_2X_EN                             BIT(4)
#define BIT_AON_APB_CGM_SDIO0_1X_EN                             BIT(3)
#define BIT_AON_APB_CGM_SDIO0_2X_EN                             BIT(2)
#define BIT_AON_APB_CGM_AP_AXI_EN                               BIT(1)
#define BIT_AON_APB_CGM_CSSYS_EN                                BIT(0)

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

#define BIT_AON_APB_CM4_2_AUD_ACCESS_EN                         BIT(6)
#define BIT_AON_APB_AP_2_AUD_ACCESS_EN                          BIT(5)
#define BIT_AON_APB_CR5_2_AUD_ACCESS_EN                         BIT(4)
#define BIT_AON_APB_LDSP_2_AUD_ACCESS_EN                        BIT(3)
#define BIT_AON_APB_TGDSP_2_AUD_ACCESS_EN                       BIT(2)
#define BIT_AON_APB_AUDCP_FRC_CLK_DSP_EN                        BIT(1)
#define BIT_AON_APB_TOP_2_AUD_ACCESS_EN                         BIT(0)

/* REG_AON_APB_WTLCP_LDSP_CTRL0 */

#define BIT_AON_APB_WTLCP_LDSP_BOOT_VECTOR(x)                   (((x) & 0xFFFFFFFF))

/* REG_AON_APB_WTLCP_LDSP_CTRL1 */

#define BIT_AON_APB_WTLCP_STCK_LDSP                             BIT(13)
#define BIT_AON_APB_WTLCP_STMS_LDSP                             BIT(12)
#define BIT_AON_APB_WTLCP_STDO_LDSP                             BIT(11)
#define BIT_AON_APB_WTLCP_STDI_LDSP                             BIT(10)
#define BIT_AON_APB_WTLCP_STRTCK_LDSP                           BIT(9)
#define BIT_AON_APB_WTLCP_SW_JTAG_ENA_LDSP                      BIT(8)
#define BIT_AON_APB_WTLCP_LDSP_EXTERNAL_WAIT                    BIT(1)
#define BIT_AON_APB_WTLCP_LDSP_BOOT                             BIT(0)

/* REG_AON_APB_WTLCP_TDSP_CTRL0 */

#define BIT_AON_APB_WTLCP_TDSP_BOOT_VECTOR(x)                   (((x) & 0xFFFFFFFF))

/* REG_AON_APB_WTLCP_TDSP_CTRL1 */

#define BIT_AON_APB_WTLCP_STCK_TDSP                             BIT(13)
#define BIT_AON_APB_WTLCP_STMS_TDSP                             BIT(12)
#define BIT_AON_APB_WTLCP_STDO_TDSP                             BIT(11)
#define BIT_AON_APB_WTLCP_STDI_TDSP                             BIT(10)
#define BIT_AON_APB_WTLCP_STRTCK_TDSP                           BIT(9)
#define BIT_AON_APB_WTLCP_SW_JTAG_ENA_TDSP                      BIT(8)
#define BIT_AON_APB_WTLCP_TDSP_EXTERNAL_WAIT                    BIT(1)
#define BIT_AON_APB_WTLCP_TDSP_BOOT                             BIT(0)

/* REG_AON_APB_WTLCP_CTRL */

#define BIT_AON_APB_WTLCP_AON_FRC_WSYS_LT_STOP                  BIT(4)
#define BIT_AON_APB_WTLCP_AON_FRC_WSYS_STOP                     BIT(3)
#define BIT_AON_APB_WTLCP_DSP_DEEP_SLEEP_EN                     BIT(2)

/* REG_AON_APB_WTL_WCDMA_EB */

#define BIT_AON_APB_WTLCP_WCMDA_EB                              BIT(16)
#define BIT_AON_APB_WCDMA_AUTO_GATE_EN                          BIT(8)
#define BIT_AON_APB_WTLCP_WTLSYS_RFTI_TX_EB                     BIT(1)
#define BIT_AON_APB_WTLCP_WTLSYS_RFTI_RX_EB                     BIT(0)

/* REG_AON_APB_PCP_AON_EB */

#define BIT_AON_APB_PUBCP_SYST_RTC_EB                           BIT(11)
#define BIT_AON_APB_PUBCP_TMR_EB                                BIT(10)
#define BIT_AON_APB_PUBCP_TMR_RTC_EB                            BIT(9)
#define BIT_AON_APB_PUBCP_SYST_EB                               BIT(8)
#define BIT_AON_APB_PUBCP_WDG_EB                                BIT(7)
#define BIT_AON_APB_PUBCP_WDG_RTC_EB                            BIT(6)
#define BIT_AON_APB_PUBCP_ARCH_RTC_EB                           BIT(5)
#define BIT_AON_APB_PUBCP_EIC_EB                                BIT(4)
#define BIT_AON_APB_PUBCP_EIC_RTCDV5_EB                         BIT(3)
#define BIT_AON_APB_PUBCP_EIC_RTC_EB                            BIT(2)

/* REG_AON_APB_PCP_SOFT_RST */

#define BIT_AON_APB_PUBCP_CR5_CORE_SOFT_RST                     BIT(10)
#define BIT_AON_APB_PUBCP_CR5_DBG_SOFT_RST                      BIT(9)
#define BIT_AON_APB_PUBCP_CR5_ETM_SOFT_RST                      BIT(8)
#define BIT_AON_APB_PUBCP_CR5_MP_SOFT_RST                       BIT(7)
#define BIT_AON_APB_PUBCP_CR5_CS_DBG_SOFT_RST                   BIT(6)
#define BIT_AON_APB_PUBCP_TMR_SOFT_RST                          BIT(5)
#define BIT_AON_APB_PUBCP_SYST_SOFT_RST                         BIT(4)
#define BIT_AON_APB_PUBCP_WDG_SOFT_RST                          BIT(3)
#define BIT_AON_APB_PUBCP_EIC_SOFT_RST                          BIT(2)

/* REG_AON_APB_PUBCP_CTRL */

#define BIT_AON_APB_AON_ACCESS_PUBCP                            BIT(13)
#define BIT_AON_APB_PUBCP_CR5_STANDBYWFI_N                      BIT(12)
#define BIT_AON_APB_PUBCP_CR5_STANDBYWFE_N                      BIT(11)
#define BIT_AON_APB_PUBCP_CR5_CLKSTOPPED0_N                     BIT(10)
#define BIT_AON_APB_PUBCP_CR5_L2IDLE                            BIT(9)
#define BIT_AON_APB_PUBCP_CR5_VALIRQ0_N                         BIT(8)
#define BIT_AON_APB_PUBCP_CR5_VALFIQ0_N                         BIT(7)
#define BIT_AON_APB_PUBCP_CR5_STOP                              BIT(6)
#define BIT_AON_APB_PUBCP_CR5_CSYSACK_ATB                       BIT(5)
#define BIT_AON_APB_PUBCP_CR5_CACTIVE_ATB                       BIT(4)
#define BIT_AON_APB_PUBCP_CR5_CSSYNC_REQ                        BIT(3)
#define BIT_AON_APB_PUBCP_CR5_CSYSREQ_ATB                       BIT(2)
#define BIT_AON_APB_PUBCP_CR5_NODBGCLK                          BIT(1)
#define BIT_AON_APB_PUBCP_CR5_CFGEE                             BIT(0)

/* REG_AON_APB_VECTOR_VDSP */

#define BIT_AON_APB_VECTOR_VDSP(x)                              (((x) & 0xFFFFFFFF))

/* REG_AON_APB_WTLCP_LPC_CTRL */

#define BIT_AON_APB_WTLCP_FRC_STOP_ACK                          BIT(8)
#define BIT_AON_APB_WTLCP_FRC_STOP_REQ                          BIT(0)

/* REG_AON_APB_PUBCP_LPC_CTRL */

#define BIT_AON_APB_PUBCP_FRC_STOP_ACK                          BIT(8)
#define BIT_AON_APB_PUBCP_FRC_STOP_REQ                          BIT(0)

/* REG_AON_APB_AON_SOC_USB_CTRL */

#define BIT_AON_APB_USB20_CTRL_MUX_REG                          BIT(3)
#define BIT_AON_APB_USB_BUSCLK_SEL_SOC                          BIT(2)
#define BIT_AON_APB_USB_DIVN_MUX_SEL                            BIT(1)
#define BIT_AON_APB_AON_IIS_SEL                                 BIT(0)

/* REG_AON_APB_ESE_INT_MASK */

#define BIT_AON_APB_INT_REQ_ESE_TO_CP_SWITCH                    BIT(4)
#define BIT_AON_APB_INT_REQ_ESE_TO_CP_MASK                      BIT(3)
#define BIT_AON_APB_INT_REQ_ESE_TO_CP_MASK_CM4                  BIT(2)
#define BIT_AON_APB_INT_REQ_ESE_TO_APCPUREE_MASK                BIT(1)
#define BIT_AON_APB_INT_REQ_ESE_TO_APCPUTEE_MASK                BIT(0)

/* REG_AON_APB_SOFT_RST_AON_ADD1 */

#define BIT_AON_APB_BSMTMR_SOFT_RST                             BIT(7)
#define BIT_AON_APB_RFTI2_LTH_SOFT_RST                          BIT(6)
#define BIT_AON_APB_RFTI1_LTH_SOFT_RST                          BIT(5)
#define BIT_AON_APB_CSSYS_SOFT_RST                              BIT(4)
#define BIT_AON_APB_RFTI_SBI_SOFT_RST                           BIT(1)
#define BIT_AON_APB_LVDSRF_CALI_SOFT_RST                        BIT(0)

/* REG_AON_APB_VDSP_INT_CTRL */

#define BIT_AON_APB_INT_REQ_DCAM2_ARM_STAT                      BIT(9)
#define BIT_AON_APB_INT_REQ_DCAM1_ARM_STAT                      BIT(8)
#define BIT_AON_APB_INT_REQ_DCAM0_ARM_STAT                      BIT(7)
#define BIT_AON_APB_INT_REQ_ISP_CH1_STAT                        BIT(6)
#define BIT_AON_APB_INT_REQ_ISP_CH0_STAT                        BIT(5)
#define BIT_AON_APB_INT_REQ_DCAM2_ARM_MASK                      BIT(4)
#define BIT_AON_APB_INT_REQ_DCAM1_ARM_MASK                      BIT(3)
#define BIT_AON_APB_INT_REQ_DCAM0_ARM_MASK                      BIT(2)
#define BIT_AON_APB_INT_REQ_ISP_CH1_MASK                        BIT(1)
#define BIT_AON_APB_INT_REQ_ISP_CH0_MASK                        BIT(0)

/* REG_AON_APB_EB_AON_ADD1 */

#define BIT_AON_APB_BSM_TMR_EB                                  BIT(1)

/* REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG4 */

#define BIT_AON_APB_REG_DBG_BUS_SEL_AON_EXT(x)                  (((x) & 0xFF) << 16)
#define BIT_AON_APB_REG_DBG_BUS_SEL_AI(x)                       (((x) & 0xFF) << 8)
#define BIT_AON_APB_REG_DBG_BUS_SEL_IPA(x)                      (((x) & 0xFF))

/* REG_AON_APB_DBG_DJTAG_CTRL */

#define BIT_AON_APB_DBGSYS_CSSYS_STM_NSGUAREN                   BIT(16)
#define BIT_AON_APB_DJTAG_SRC_MUX_SEL                           BIT(0)

/* REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG0 */

#define BIT_AON_APB_REG_DBG_BUS_SEL_GPU(x)                      (((x) & 0xFF) << 24)
#define BIT_AON_APB_REG_DBG_MOD_SEL_WTLCP(x)                    (((x) & 0xFF) << 16)
#define BIT_AON_APB_REG_DBG_MOD_SEL_PUBCP(x)                    (((x) & 0xFF) << 8)
#define BIT_AON_APB_REG_DBG_BUS_SEL_APCPU(x)                    (((x) & 0xFF))

/* REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG1 */

#define BIT_AON_APB_REG_DBG_BUS_SEL_AP(x)                       (((x) & 0xFF) << 24)
#define BIT_AON_APB_REG_DBG_BUS_SEL_PUBCP(x)                    (((x) & 0xFF) << 16)
#define BIT_AON_APB_REG_DBG_BUS_SEL_WTLCP(x)                    (((x) & 0xFF) << 8)
#define BIT_AON_APB_REG_DBG_BUS_SEL_AUDCP(x)                    (((x) & 0xFF))

/* REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG2 */

#define BIT_AON_APB_REG_DBG_BUS_SEL_PUB(x)                      (((x) & 0xFF) << 24)
#define BIT_AON_APB_REG_DBG_BUS_SEL_MM(x)                       (((x) & 0xFF) << 16)
#define BIT_AON_APB_REG_DBG_BUS_SEL_AON(x)                      (((x) & 0xFF) << 8)
#define BIT_AON_APB_REG_DBG_BUS_SEL_MDAR(x)                     (((x) & 0xFF))

/* REG_AON_APB_SYS_DEBUG_BUS_SEL_CFG3 */

#define BIT_AON_APB_REG_DBG_MOD_SEL_AON_EXT(x)                  (((x) & 0xFF) << 24)
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

/* REG_AON_APB_MBIST_EFUSE_CTRL */

#define BIT_AON_APB_FUSEBOX_SELECT_BUFFER_SW                    BIT(3)
#define BIT_AON_APB_EFUSE_MUX_SEL_SW_DEFUALT0                   BIT(2)
#define BIT_AON_APB_EFUSE_MUX_SEL_SW_DEFUALT1                   BIT(1)
#define BIT_AON_APB_EFUSE_MUX_SEL_SW                            BIT(0)

/* REG_AON_APB_OTG_PHY_TUNE */

#define BIT_AON_APB_OTG_TXPREEMPPULSETUNE                       BIT(20)
#define BIT_AON_APB_OTG_TXRESTUNE(x)                            (((x) & 0x3) << 18)
#define BIT_AON_APB_OTG_TXHSXVTUNE(x)                           (((x) & 0x3) << 16)
#define BIT_AON_APB_OTG_TXVREFTUNE(x)                           (((x) & 0xF) << 12)
#define BIT_AON_APB_OTG_TXPREEMPAMPTUNE(x)                      (((x) & 0x3) << 10)
#define BIT_AON_APB_OTG_TXRISETUNE(x)                           (((x) & 0x3) << 8)
#define BIT_AON_APB_OTG_TXFSLSTUNE(x)                           (((x) & 0xF) << 4)
#define BIT_AON_APB_OTG_SQRXTUNE(x)                             (((x) & 0x7))

/* REG_AON_APB_OTG_PHY_TEST */

#define BIT_AON_APB_OTG_ATERESET                                BIT(31)
#define BIT_AON_APB_USB30_POWER_PRESENT                         BIT(25)
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

/* REG_AON_APB_LVDSRF_CTRL */

#define BIT_AON_APB_LVDSRF_ISO_EN                               BIT(2)
#define BIT_AON_APB_LVDSRF_PD_PD_L                              BIT(1)
#define BIT_AON_APB_LVDSRF_PS_PD_S                              BIT(0)

/* REG_AON_APB_THM0_CTRL */

#define BIT_AON_APB_THM0_CALI_RSVD(x)                           (((x) & 0xFF))

/* REG_AON_APB_THM1_CTRL */

#define BIT_AON_APB_THM1_CALI_RSVD(x)                           (((x) & 0xFF))

/* REG_AON_APB_THM2_CTRL */

#define BIT_AON_APB_THM2_CALI_RSVD(x)                           (((x) & 0xFF))

/* REG_AON_APB_THM3_CTRL */

#define BIT_AON_APB_THM3_CALI_RSVD(x)                           (((x) & 0xFF))

/* REG_AON_APB_OVERHEAT_CTRL */

#define BIT_AON_APB_THM3_INT_ADIE_EN                            BIT(11)
#define BIT_AON_APB_THM2_INT_ADIE_EN                            BIT(10)
#define BIT_AON_APB_THM1_INT_ADIE_EN                            BIT(9)
#define BIT_AON_APB_THM0_INT_ADIE_EN                            BIT(8)
#define BIT_AON_APB_THM3_OVERHEAT_ALARM_ADIE_EN                 BIT(7)
#define BIT_AON_APB_THM2_OVERHEAT_ALARM_ADIE_EN                 BIT(6)
#define BIT_AON_APB_THM1_OVERHEAT_ALARM_ADIE_EN                 BIT(5)
#define BIT_AON_APB_THM0_OVERHEAT_ALARM_ADIE_EN                 BIT(4)
#define BIT_AON_APB_THM3_OVERHEAT_RST_DDIE_EN                   BIT(3)
#define BIT_AON_APB_THM2_OVERHEAT_RST_DDIE_EN                   BIT(2)
#define BIT_AON_APB_THM1_OVERHEAT_RST_DDIE_EN                   BIT(1)
#define BIT_AON_APB_THM0_OVERHEAT_RST_DDIE_EN                   BIT(0)

/* REG_AON_APB_PUBCP_SIM1_TOP_CTRL */

#define BIT_AON_APB_CP_SIM1_CLK_PL                              BIT(5)
#define BIT_AON_APB_CP_SIM1_DETECT_EN                           BIT(4)
#define BIT_AON_APB_CP_BAT1_DETECT_EN                           BIT(3)
#define BIT_AON_APB_CP_SIM1_DETECT_POL                          BIT(2)
#define BIT_AON_APB_CP_BAT1_DETECT_POL                          BIT(1)
#define BIT_AON_APB_CP_SIM1_OFF_PD_EN                           BIT(0)

/* REG_AON_APB_PUBCP_SIM2_TOP_CTRL */

#define BIT_AON_APB_CP_SIM2_CLK_PL                              BIT(5)
#define BIT_AON_APB_CP_SIM2_DETECT_EN                           BIT(4)
#define BIT_AON_APB_CP_BAT2_DETECT_EN                           BIT(3)
#define BIT_AON_APB_CP_SIM2_DETECT_POL                          BIT(2)
#define BIT_AON_APB_CP_BAT2_DETECT_POL                          BIT(1)
#define BIT_AON_APB_CP_SIM2_OFF_PD_EN                           BIT(0)

/* REG_AON_APB_PUBCP_SIM3_TOP_CTRL */

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

/* REG_AON_APB_APCPU_TOP_MTX_LPC_PU_NUM_CTRL */

#define BIT_AON_APB_APCPU_MTX_PU_NUM(x)                         (((x) & 0xFF) << 8)
#define BIT_AON_APB_APCPU_ACE_PU_NUM(x)                         (((x) & 0xFF))

/* REG_AON_APB_APCPU_CLUSTER_SCU_LPC_CTRL */

#define BIT_AON_APB_APCPU_CLUSTER_SCU_LP_NUM(x)                 (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_APCPU_CLUSTER_SCU_LP_EB                     BIT(0)

/* REG_AON_APB_APCPU_DDR_AB_LPC_CTRL */

#define BIT_AON_APB_APCPU_DDR_AB_LP_NUM(x)                      (((x) & 0xFFFF) << 2)
#define BIT_AON_APB_APCPU_DDR_AB1_LP_EB                         BIT(1)
#define BIT_AON_APB_APCPU_DDR_AB0_LP_EB                         BIT(0)

/* REG_AON_APB_APCPU_QOS_CTRL */

#define BIT_AON_APB_QOS_DAP_APCPU(x)                            (((x) & 0xF) << 20)
#define BIT_AON_APB_QOS_ETR_APCPU(x)                            (((x) & 0xF) << 16)
#define BIT_AON_APB_ARQOS_THRESHOLD_APCPU(x)                    (((x) & 0xF) << 12)
#define BIT_AON_APB_AWQOS_THRESHOLD_APCPU(x)                    (((x) & 0xF) << 8)
#define BIT_AON_APB_ARQOS_APCPU(x)                              (((x) & 0xF) << 4)
#define BIT_AON_APB_AWQOS_APCPU(x)                              (((x) & 0xF))

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

/* REG_AON_APB_MPLL2_CTRL */

#define BIT_AON_APB_CGM_MPLL2_APCPU_FORCE_EN                    BIT(9)
#define BIT_AON_APB_CGM_MPLL2_APCPU_AUTO_GATE_SEL               BIT(8)
#define BIT_AON_APB_MPLL2_WAIT_FORCE_EN                         BIT(2)
#define BIT_AON_APB_MPLL2_WAIT_AUTO_GATE_SEL                    BIT(1)
#define BIT_AON_APB_MPLL2_SOFT_CNT_DONE                         BIT(0)

/* REG_AON_APB_MPLL3_CTRL */

#define BIT_AON_APB_CGM_MPLL3_APCPU_FORCE_EN                    BIT(9)
#define BIT_AON_APB_CGM_MPLL3_APCPU_AUTO_GATE_SEL               BIT(8)
#define BIT_AON_APB_MPLL3_WAIT_FORCE_EN                         BIT(2)
#define BIT_AON_APB_MPLL3_WAIT_AUTO_GATE_SEL                    BIT(1)
#define BIT_AON_APB_MPLL3_SOFT_CNT_DONE                         BIT(0)

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

/* REG_AON_APB_PUB_CLK_GATING_CTRL */

#define BIT_AON_APB_PUB_APB_FW_EB                               BIT(17)
#define BIT_AON_APB_PUB_REG_EB                                  BIT(16)
#define BIT_AON_APB_DMC_EB                                      BIT(15)

/* REG_AON_APB_DDRPHY_VREP */

#define BIT_AON_APB_PHY_VREF_ADJ(x)                             (((x) & 0xFF) << 2)
#define BIT_AON_APB_PHY_VREF_PD                                 BIT(1)
#define BIT_AON_APB_PHY_VREF_HI_C                               BIT(0)

/* REG_AON_APB_CM42AON_LPC_CTRL */

#define BIT_AON_APB_CM4_TO_AON_AXI_LP_NUM(x)                    (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_CM4_TO_AON_AXI_LP_EB                        BIT(0)

/* REG_AON_APB_AON_MTX_MAIN_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_MAIN_LP_NUM(x)                      (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_MAIN_LP_EB                          BIT(0)

/* REG_AON_APB_AON_MTX_M0_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_M0_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_M0_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_M1_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_M1_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_M1_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_M2_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_M2_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_M2_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_M3_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_M3_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_M3_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_M4_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_M4_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_M4_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_M5_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_M5_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_M5_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_M6_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_M6_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_M6_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_S0_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_S0_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_S0_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_S1_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_S1_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_S1_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_S2_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_S2_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_S2_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_S3_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_S3_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_S3_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_S4_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_S4_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_S4_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_S5_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_S5_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_S5_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_S6_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_S6_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_S6_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_S7_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_S7_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_S7_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_S8_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_S8_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_S8_LP_EB                            BIT(0)

/* REG_AON_APB_AON_MTX_S9_LPC_CTRL */

#define BIT_AON_APB_AON_MTX_S9_LP_NUM(x)                        (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON_MTX_S9_LP_EB                            BIT(0)

/* REG_AON_APB_AP2GPU_SLI_LPC_CTRL */

#define BIT_AON_APB_AP2GPU_SLICE_LP_NUM(x)                      (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AP2GPU_SLICE_LP_EB                          BIT(0)

/* REG_AON_APB_AP2MM_SLI_LPC_CTRL */

#define BIT_AON_APB_AP2MM_SLICE_LP_NUM(x)                       (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AP2MM_SLICE_LP_EB                           BIT(0)

/* REG_AON_APB_WTLCP2DDR_SLI_LPC_CTRL */

#define BIT_AON_APB_WTLCP2DDR_SLICE_LP_NUM(x)                   (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_WTLCP2DDR_SLICE_LP_EB                       BIT(0)

/* REG_AON_APB_APCPU2AP_SLI_LPC_CTRL */

#define BIT_AON_APB_APCPU2AP_SLICE_LP_NUM(x)                    (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_APCPU2AP_SLICE_LP_EB                        BIT(0)

/* REG_AON_APB_AUDCP2DDR_SLI_LPC_CTRL */

#define BIT_AON_APB_AUDCP2DDR_SLICE_LP_NUM(x)                   (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AUDCP2DDR_SLICE_LP_EB                       BIT(0)

/* REG_AON_APB_APCPU2DDR_SLI_LPC_CTRL */

#define BIT_AON_APB_APCPU2DDR_SLICE_LP_NUM(x)                   (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_APCPU2DDR_SLICE_LP_EB                       BIT(0)

/* REG_AON_APB_AON2DDR_BRG_LPC_CTRL */

#define BIT_AON_APB_AON2DDR_ASYNC_BRIDGE_LP_NUM(x)              (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AON2DDR_ASYNC_BRIDGE_LP_EB                  BIT(0)

/* REG_AON_APB_PUBCP2WTLCP_SLI_LPC_CTRL */

#define BIT_AON_APB_PUBCP2WTLCP_SLICE_LP_NUM(x)                 (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_PUBCP2WTLCP_SLICE_LP_EB                     BIT(0)

/* REG_AON_APB_AON_APB_FREQ_CTRL */

#define BIT_AON_APB_AON_APB_MASTER_BUSY(x)                      (((x) & 0x3F) << 2)
#define BIT_AON_APB_AON_APB_FREQ_CTRL_EN                        BIT(1)
#define BIT_AON_APB_AON_APB_IDLE_EN                             BIT(0)

/* REG_AON_APB_MIPI_CSI_POWER_CTRL */

#define BIT_AON_APB_ANALOG_BB_TOP_SINDRV_ENA_AUTO_EN            BIT(6)
#define BIT_AON_APB_R2G_ANALOG_BB_TOP_SINDRV_ENA                BIT(5)
#define BIT_AON_APB_M2G_ANALOG_BB_TOP_SINDRV_ENA                BIT(4)
#define BIT_AON_APB_R2G_ANALOG_BB_TOP_SINDRV_ENA_SQUARE         BIT(3)
#define BIT_AON_APB_C2G_ANALOG_BB_TOP_CLK26MHZ_AUD_EN           BIT(2)
#define BIT_AON_APB_C2G_ANALOG_USB20_USB20_PS_PD_S              BIT(1)
#define BIT_AON_APB_C2G_ANALOG_USB20_USB20_PS_PD_L              BIT(0)

/* REG_AON_APB_APCPU_MERGE_MTX_M0_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_APCPU_MERGE_MTX_M0(x)                (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_APCPU_MERGE_MTX_M0                    BIT(0)

/* REG_AON_APB_APCPU_MERGE_MTX_M1_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_APCPU_MERGE_MTX_M1(x)                (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_APCPU_MERGE_MTX_M1                    BIT(0)

/* REG_AON_APB_APCPU_MERGE_MTX_S0_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_APCPU_MERGE_MTX_S0(x)                (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_APCPU_MERGE_MTX_S0                    BIT(0)

/* REG_AON_APB_GPU_MERGE_MTX_M0_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_GPU_MERGE_MTX_M0(x)                  (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_GPU_MERGE_MTX_M0                      BIT(0)

/* REG_AON_APB_GPU_MERGE_MTX_M1_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_GPU_MERGE_MTX_M1(x)                  (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_GPU_MERGE_MTX_M1                      BIT(0)

/* REG_AON_APB_GPU_MERGE_MTX_S0_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_GPU_MERGE_MTX_S0(x)                  (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_GPU_MERGE_MTX_S0                      BIT(0)

/* REG_AON_APB_GPU2DDR_SLI_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_GPU2DDR_REGSLICE(x)                  (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_GPU2DDR_REGSLICE                      BIT(0)

/* REG_AON_APB_MM_DCAM2DDR_SLI_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_MM_DCAM2DDR_REGSLICE(x)              (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_MM_DCAM2DDR_REGSLICE                  BIT(0)

/* REG_AON_APB_MM_MTX2DDR_SLI_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_MM_MTX2DDR_REGSLICE(x)               (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_MM_MTX2DDR_REGSLICE                   BIT(0)

/* REG_AON_APB_IPA12DDR_SLI_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_IPA12DDR_REGSLICE(x)                 (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_IPA12DDR_REGSLICE                     BIT(0)

/* REG_AON_APB_IPA22DDR_SLI_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_IPA22DDR_REGSLICE(x)                 (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_IPA22DDR_REGSLICE                     BIT(0)

/* REG_AON_APB_AI2DDR_SLI_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_AI2DDR_REGSLICE(x)                   (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AI2DDR_REGSLICE                       BIT(0)

/* REG_AON_APB_ESE2DDR_SLI_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_ESE2DDR_REGSLICE(x)                  (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_ESE2DDR_REGSLICE                      BIT(0)

/* REG_AON_APB_ESE2DDR_ASYNC_BRG_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_ESE2DDR_ASYNC_BRIDGE_W(x)            (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_ESE2DDR_ASYNC_BRIDGE_W                BIT(0)

/* REG_AON_APB_AP2IPA_SLI_LPC_CTRL */

#define BIT_AON_APB_AP2IPA_SLICE_LP_NUM(x)                      (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AP2IPA_SLICE_LP_EB                          BIT(0)

/* REG_AON_APB_AP2AI_SLI_LPC_CTRL */

#define BIT_AON_APB_AP2AI_SLICE_LP_NUM(x)                       (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_AP2AI_SLICE_LP_EB                           BIT(0)

/* REG_AON_APB_AP2IPA_ASYNC_BRG_LPC_CTRL */

#define BIT_AON_APB_LP_NUM_AP2IPA_ASYNC_BRIDGE_W(x)             (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_LP_EB_AP2IPA_ASYNC_BRIDGE_W                 BIT(0)

/* REG_AON_APB_C_CHANNEL_SYNC_SEL_CFG */

#define BIT_AON_APB_ESE2DDR_AB_CCHNL_SYNC_SEL                   BIT(16)
#define BIT_AON_APB_ESE2DDR_SLICE_CCHNL_SYNC_SEL                BIT(15)
#define BIT_AON_APB_AI2DDR_SLICE_CCHNL_SYNC_SEL                 BIT(14)
#define BIT_AON_APB_AUDCP2DDR_SLICE_CCHNL_SYNC_SEL              BIT(13)
#define BIT_AON_APB_WTLCP2DDR_SLICE_CCHNL_SYNC_SEL              BIT(12)
#define BIT_AON_APB_IPA22DDR_SLICE_CCHNL_SYNC_SEL               BIT(11)
#define BIT_AON_APB_IPA12DDR_SLICE_CCHNL_SYNC_SEL               BIT(10)
#define BIT_AON_APB_MM_MTX2DDR_SLICE_CCHNL_SYNC_SEL             BIT(9)
#define BIT_AON_APB_MM_DCAM2DDR_SLICE_CCHNL_SYNC_SEL            BIT(8)
#define BIT_AON_APB_GPU2DDR_SLICE_CCHNL_SYNC_SEL                BIT(7)
#define BIT_AON_APB_GPU_MERGE_MTX_S0_CCHNL_SYNC_SEL             BIT(6)
#define BIT_AON_APB_GPU_MERGE_MTX_M1_CCHNL_SYNC_SEL             BIT(5)
#define BIT_AON_APB_GPU_MERGE_MTX_M0_CCHNL_SYNC_SEL             BIT(4)
#define BIT_AON_APB_APCPU2DDR_SLICE_CCHNL_SYNC_SEL              BIT(3)
#define BIT_AON_APB_APCPU_MERGE_MTX_S0_CCHNL_SYNC_SEL           BIT(2)
#define BIT_AON_APB_APCPU_MERGE_MTX_M1_CCHNL_SYNC_SEL           BIT(1)
#define BIT_AON_APB_APCPU_MERGE_MTX_M0_CCHNL_SYNC_SEL           BIT(0)

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

/* REG_AON_APB_SDIO0_CTRL_REG */

#define BIT_AON_APB_SDIO0_EMMC_CARD_PRESENT_32K                 BIT(21)
#define BIT_AON_APB_SDIO0_EMMC_CARD_PROTECT_32K                 BIT(20)
#define BIT_AON_APB_SDIO0_EMMC_BATTERY_PRESENT_32K              BIT(19)
#define BIT_AON_APB_SDIO0_EMMC_BATTERY_DEB_EN_32K               BIT(18)
#define BIT_AON_APB_SDIO0_EMMC_BATTERY_DBNC_THD_32K(x)          (((x) & 0xFF) << 10)
#define BIT_AON_APB_SDIO0_EMMC_BATTERY_DBNC_EN_32K              BIT(9)
#define BIT_AON_APB_SDIO0_EMMC_CARDDET_DBNC_THD_32K(x)          (((x) & 0xFF) << 1)
#define BIT_AON_APB_SDIO0_EMMC_CARDDET_DBNC_EN_32K              BIT(0)

/* REG_AON_APB_SDIO1_CTRL_REG */

#define BIT_AON_APB_SDIO1_EMMC_CARD_PRESENT_32K                 BIT(21)
#define BIT_AON_APB_SDIO1_EMMC_CARD_PROTECT_32K                 BIT(20)
#define BIT_AON_APB_SDIO1_EMMC_BATTERY_PRESENT_32K              BIT(19)
#define BIT_AON_APB_SDIO1_EMMC_BATTERY_DEB_EN_32K               BIT(18)
#define BIT_AON_APB_SDIO1_EMMC_BATTERY_DBNC_THD_32K(x)          (((x) & 0xFF) << 10)
#define BIT_AON_APB_SDIO1_EMMC_BATTERY_DBNC_EN_32K              BIT(9)
#define BIT_AON_APB_SDIO1_EMMC_CARDDET_DBNC_THD_32K(x)          (((x) & 0xFF) << 1)
#define BIT_AON_APB_SDIO1_EMMC_CARDDET_DBNC_EN_32K              BIT(0)

/* REG_AON_APB_SDIO2_CTRL_REG */

#define BIT_AON_APB_SDIO2_EMMC_CARD_PRESENT_32K                 BIT(21)
#define BIT_AON_APB_SDIO2_EMMC_CARD_PROTECT_32K                 BIT(20)
#define BIT_AON_APB_SDIO2_EMMC_BATTERY_PRESENT_32K              BIT(19)
#define BIT_AON_APB_SDIO2_EMMC_BATTERY_DEB_EN_32K               BIT(18)
#define BIT_AON_APB_SDIO2_EMMC_BATTERY_DBNC_THD_32K(x)          (((x) & 0xFF) << 10)
#define BIT_AON_APB_SDIO2_EMMC_BATTERY_DBNC_EN_32K              BIT(9)
#define BIT_AON_APB_SDIO2_EMMC_CARDDET_DBNC_THD_32K(x)          (((x) & 0xFF) << 1)
#define BIT_AON_APB_SDIO2_EMMC_CARDDET_DBNC_EN_32K              BIT(0)

/* REG_AON_APB_EMMC_CTRL_REG */

#define BIT_AON_APB_EMMC_EMMC_CARD_PRESENT_32K                  BIT(21)
#define BIT_AON_APB_EMMC_EMMC_CARD_PROTECT_32K                  BIT(20)
#define BIT_AON_APB_EMMC_EMMC_BATTERY_PRESENT_32K               BIT(19)
#define BIT_AON_APB_EMMC_EMMC_BATTERY_DEB_EN_32K                BIT(18)
#define BIT_AON_APB_EMMC_EMMC_BATTERY_DBNC_THD_32K(x)           (((x) & 0xFF) << 10)
#define BIT_AON_APB_EMMC_EMMC_BATTERY_DBNC_EN_32K               BIT(9)
#define BIT_AON_APB_EMMC_EMMC_CARDDET_DBNC_THD_32K(x)           (((x) & 0xFF) << 1)
#define BIT_AON_APB_EMMC_EMMC_CARDDET_DBNC_EN_32K               BIT(0)

/* REG_AON_APB_WDG_RST_FLAG */

#define BIT_AON_APB_AP_WDG_RST_FLAG                             BIT(6)
#define BIT_AON_APB_PCP_WDG_RST_FLAG                            BIT(5)
#define BIT_AON_APB_WTLCP_LTE_WDG_RST_FLAG                      BIT(4)
#define BIT_AON_APB_WTLCP_TG_WDG_RST_FLAG                       BIT(3)
#define BIT_AON_APB_AUDCP_WDG_RST_FLAG                          BIT(2)
#define BIT_AON_APB_APCPU_WDG_RST_FLAG                          BIT(1)
#define BIT_AON_APB_SEC_WDG_RST_FLAG                            BIT(0)

/* REG_AON_APB_BOND_OPT0 */

#define BIT_AON_APB_BOND_OPTION0(x)                             (((x) & 0xFFFFFFFF))

/* REG_AON_APB_DEVICE_LIFE_CYCLE */

#define BIT_AON_APB_BOND_OPTION1(x)                             (((x) & 0xFFFFFFFF))

/* REG_AON_APB_RES_REG0 */

#define BIT_AON_APB_RES_REG0(x)                                 (((x) & 0xFFFFFFFF))

/* REG_AON_APB_RES_REG1 */

#define BIT_AON_APB_RES_REG1(x)                                 (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AON_MTX_PROT_CFG */

#define BIT_AON_APB_HPROT_DMAW(x)                               (((x) & 0xF) << 4)
#define BIT_AON_APB_HPROT_DMAR(x)                               (((x) & 0xF))

/* REG_AON_APB_PLL_LOCK_OUT_SEL */

#define BIT_AON_APB_REC_26MHZ_0_BUF_PD                          BIT(8)
#define BIT_AON_APB_SLEEP_PLLLOCK_SEL                           BIT(7)
#define BIT_AON_APB_PLL_LOCK_SEL(x)                             (((x) & 0x7) << 4)
#define BIT_AON_APB_SLEEP_DBG_SEL(x)                            (((x) & 0xF))

/* REG_AON_APB_CPU2DDR_BRIDGE_DEBUG_SIGNAL_R */

#define BIT_AON_APB_CPU2DDR_BRIDGE_DEBUG_SIGNAL_R(x)            (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AON2DDR_BRIDGE_DEBUG_SIGNAL_W */

#define BIT_AON_APB_AON2DDR_BRIDGE_DEBUG_SIGNAL_R(x)            (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AON2DDR_BRIDGE_DEBUG_SIGNAL_LIST */

#define BIT_AON_APB_AON2DDR_AXI_DETECTOR_OVERFLOW               BIT(2)
#define BIT_AON_APB_AON2DDR_RST_SUBSYS                          BIT(1)
#define BIT_AON_APB_AON2DDR_BRIDGE_TRANS_IDLE                   BIT(0)

/* REG_AON_APB_AUD2DDR_BRIDGE_DEBUG_SIGNAL_R */

#define BIT_AON_APB_AUD2DDR_BRIDGE_DEBUG_SIGNAL_R(x)            (((x) & 0xFFFFFFFF))

/* REG_AON_APB_WTL2DDR_BRIDGE_DEBUG_SIGNAL_R */

#define BIT_AON_APB_WTL2DDR_BRIDGE_DEBUG_SIGNAL_R(x)            (((x) & 0xFFFFFFFF))

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

/* REG_AON_APB_LEAKAGE_MAGIC_WORD */

#define BIT_AON_APB_LEAKAGE_MAGIC_WORD(x)                       (((x) & 0xFFFFFFFF))

/* REG_AON_APB_LEAKAGE_SWITCH */

#define BIT_AON_APB_LEAKAGE_SWITCH                              BIT(0)

/* REG_AON_APB_FUNC_TEST_BOOT_ADDR */

#define BIT_AON_APB_FUNC_TEST_BOOT_ADDR(x)                      (((x) & 0xFFFFFFFF))

/* REG_AON_APB_CGM_RESCUE */

#define BIT_AON_APB_CGM_RESCUE(x)                               (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AON_SDIO */

#define BIT_AON_APB_SDIO2_SLICE_EN                              BIT(3)
#define BIT_AON_APB_CP_SDIO_ENABLE                              BIT(2)
#define BIT_AON_APB_AP_SDIO_ENABLE                              BIT(1)
#define BIT_AON_APB_SDIO_MODULE_SEL                             BIT(0)

/* REG_AON_APB_SP_WAKEUP_MASK_EN0 */

#define BIT_AON_APB_SP_INT_REQ_BUSMON_PUBCP_WAKEUP_EN           BIT(31)
#define BIT_AON_APB_SP_INT_REQ_BUSMON_AUDCP_WAKEUP_EN           BIT(30)
#define BIT_AON_APB_SP_INT_REQ_ADI_WAKEUP_EN                    BIT(29)
#define BIT_AON_APB_SP_INT_REQ_PCP_WDG_WAKEUP_EN                BIT(28)
#define BIT_AON_APB_SP_INT_REQ_PWR_DOWN_ALL_WAKEUP_EN           BIT(27)
#define BIT_AON_APB_SP_INT_REQ_PWR_UP_ALL_WAKEUP_EN             BIT(26)
#define BIT_AON_APB_SP_INT_REQ_AP_WDG_RST_WAKEUP_EN             BIT(25)
#define BIT_AON_APB_SP_INT_REQ_APCPU_WDG_RST_WAKEUP_EN          BIT(24)
#define BIT_AON_APB_SP_INT_REQ_SEC_EIC_WAKEUP_EN                BIT(23)
#define BIT_AON_APB_SP_INT_REQ_SEC_TMR_WAKEUP_EN                BIT(22)
#define BIT_AON_APB_SP_INT_REQ_SEC_WDG_WAKEUP_EN                BIT(21)
#define BIT_AON_APB_SP_INT_REQ_SEC_RTC_WAKEUP_EN                BIT(20)
#define BIT_AON_APB_SP_INT_REQ_SEC_GPIO_WAKEUP_EN               BIT(19)
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
#define BIT_AON_APB_SP_INT_REQ_CM4_GPIO_WAKEUP_EN               BIT(8)
#define BIT_AON_APB_SP_INT_REQ_CM4_SYST_WAKEUP_EN               BIT(7)
#define BIT_AON_APB_SP_INT_REQ_CM4_I2C0_SLV_WAKEUP_EN           BIT(6)
#define BIT_AON_APB_SP_INT_REQ_CM4_WDG_WAKEUP_EN                BIT(5)
#define BIT_AON_APB_SP_INT_REQ_CM4_SPI_WAKEUP_EN                BIT(4)
#define BIT_AON_APB_SP_INT_REQ_CM4_UART1_WAKEUP_EN              BIT(3)
#define BIT_AON_APB_SP_INT_REQ_CM4_UART0_WAKEUP_EN              BIT(2)
#define BIT_AON_APB_SP_INT_REQ_CM4_I3C1_WAKEUP_EN               BIT(1)
#define BIT_AON_APB_SP_INT_REQ_CM4_I3C0_WAKEUP_EN               BIT(0)

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
#define BIT_AON_APB_SP_INT_REQ_GSP_WAKEUP_EN                    BIT(21)
#define BIT_AON_APB_SP_INT_REQ_SLV_FW_AP_WAKEUP_EN              BIT(20)
#define BIT_AON_APB_SP_INT_REQ_DISPC_WAKEUP_EN                  BIT(19)
#define BIT_AON_APB_SP_INT_REQ_PUB_DFS_DENY_EN                  BIT(18)
#define BIT_AON_APB_SP_INT_REQ_PUB_DMC_MPU_VIO_WAKEUP_EN        BIT(17)
#define BIT_AON_APB_SP_INT_REQ_MEM_FW_PUB_WAKEUP_EN             BIT(16)
#define BIT_AON_APB_SP_INT_REQ_PUB_DFI_BUSMON_WAKEUP_EN         BIT(15)
#define BIT_AON_APB_SP_INT_REQ_PUB_PTM_WAKEUP_EN                BIT(14)
#define BIT_AON_APB_SP_INT_REQ_PUB_HARDWARE_DFS_EXIT_WAKEUP_EN  BIT(13)
#define BIT_AON_APB_SP_INT_REQ_PUB_DFS_COMPLETE_WAKEUP_EN       BIT(12)
#define BIT_AON_APB_SP_INT_REQ_PUB_DFS_ERROR_WAKEUP_EN          BIT(11)
#define BIT_AON_APB_SP_INT_REQ_PUB_DFS_GIVEUP_EN                BIT(10)
#define BIT_AON_APB_SP_INT_REQ_CLK_32K_DET_WAKEUP_EN            BIT(9)
#define BIT_AON_APB_SP_INT_REQ_AON_I2C0_WAKEUP_EN               BIT(8)
#define BIT_AON_APB_SP_INT_REQ_THM0_WAKEUP_EN                   BIT(7)
#define BIT_AON_APB_SP_INT_REQ_PWR_UP_PUB_WAKEUP_EN             BIT(6)
#define BIT_AON_APB_SP_INT_REQ_PWR_UP_AP_WAKEUP_EN              BIT(5)
#define BIT_AON_APB_SP_INT_REQ_SLV_FW_AON_WAKEUP_EN             BIT(4)
#define BIT_AON_APB_SP_INT_REQ_MEM_FW_AON_WAKEUP_EN             BIT(3)
#define BIT_AON_APB_SP_INT_REQ_BUSMON_USB_WAKEUP_EN             BIT(2)
#define BIT_AON_APB_SP_INT_REQ_BUSMON_AP_WAKEUP_EN              BIT(1)
#define BIT_AON_APB_SP_INT_REQ_BUSMON_WTLCP_WAKEUP_EN           BIT(0)

/* REG_AON_APB_SP_WAKEUP_MASK_EN2 */

#define BIT_AON_APB_SP_INT_REQ_AON_I2C1_WAKEUP_EN               BIT(10)
#define BIT_AON_APB_SP_INT_REQ_DFS_VOTE_DONE_WAKEUP_EN          BIT(9)
#define BIT_AON_APB_SP_INT_REQ_THM2_WAKEUP_EN                   BIT(8)
#define BIT_AON_APB_SP_INT_REQ_THM1_WAKEUP_EN                   BIT(7)
#define BIT_AON_APB_SP_INT_REQ_CM4_TMR2_WAKEUP_EN               BIT(6)
#define BIT_AON_APB_SP_INT_REQ_CM4_TMR1_WAKEUP_EN               BIT(5)
#define BIT_AON_APB_SP_INT_REQ_CM4_TMR0_WAKEUP_EN               BIT(4)
#define BIT_AON_APB_SP_INT_REQ_EXT_RSTB_SPCPU_WAKEUP_EN         BIT(3)
#define BIT_AON_APB_SP_INT_REQ_ESE_WAKEUP_EN                    BIT(2)
#define BIT_AON_APB_SP_INT_REQ_AUDCP_WDG_RST_WAKEUP_EN          BIT(1)
#define BIT_AON_APB_SP_INT_REQ_AUDCP_VBC_AUDPLY_WAKEUP_EN       BIT(0)

/* REG_AON_APB_DBG_BUS_DATA_WTLCP */

#define BIT_AON_APB_DBG_BUS_DATA_WTLCP(x)                       (((x) & 0xFFFFFFFF))

/* REG_AON_APB_DBG_BUS_DATA_PUBCP */

#define BIT_AON_APB_DBG_BUS_DATA_PUBCP(x)                       (((x) & 0xFFFFFFFF))

/* REG_AON_APB_DBG_BUS_DATA_AUDCP */

#define BIT_AON_APB_DBG_BUS_DATA_AUDCP(x)                       (((x) & 0xFFFFFFFF))

/* REG_AON_APB_SDIO_EMMC_POWER_STATUS */

#define BIT_AON_APB_AP_EMMC_POWER_OFF_DLY                       BIT(20)
#define BIT_AON_APB_PUCP_SDIO0_POWER_OFF_DLY                    BIT(19)
#define BIT_AON_APB_AP_SDIO2_POWER_OFF_DLY                      BIT(18)
#define BIT_AON_APB_AP_SDIO1_POWER_OFF_DLY                      BIT(17)
#define BIT_AON_APB_AP_SDIO0_POWER_OFF_DLY                      BIT(16)
#define BIT_AON_APB_AP_EMMC_POWER_OFF                           BIT(4)
#define BIT_AON_APB_PUCP_SDIO0_POWER_OFF                        BIT(3)
#define BIT_AON_APB_AP_SDIO2_POWER_OFF                          BIT(2)
#define BIT_AON_APB_AP_SDIO1_POWER_OFF                          BIT(1)
#define BIT_AON_APB_AP_SDIO0_POWER_OFF                          BIT(0)

/* REG_AON_APB_SCC_DBG_BUS */

#define BIT_AON_APB_SCC_DBG_BUS(x)                              (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AON_FUNC_CTRL_0 */

#define BIT_AON_APB_AON_FUNC_CTRL_0(x)                          (((x) & 0xFFFFFFFF))

/* REG_AON_APB_AON_FUNC_CTRL_1 */

#define BIT_AON_APB_AON_FUNC_CTRL_1(x)                          (((x) & 0xFFFFFFFF))


#endif /* AON_APB_H */


