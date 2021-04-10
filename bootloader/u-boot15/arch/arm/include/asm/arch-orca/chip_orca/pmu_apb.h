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


#ifndef PMU_APB_H
#define PMU_APB_H

#define CTL_BASE_PMU_APB 0x64010000


#define REG_PMU_APB_PD_APCPU_TOP_CFG                              ( CTL_BASE_PMU_APB + 0x0000 )
#define REG_PMU_APB_PD_APCPU_C0_CFG                               ( CTL_BASE_PMU_APB + 0x0004 )
#define REG_PMU_APB_PD_APCPU_C1_CFG                               ( CTL_BASE_PMU_APB + 0x0008 )
#define REG_PMU_APB_PD_APCPU_C2_CFG                               ( CTL_BASE_PMU_APB + 0x000C )
#define REG_PMU_APB_PD_APCPU_C3_CFG                               ( CTL_BASE_PMU_APB + 0x0010 )
#define REG_PMU_APB_PD_APCPU_TOP_CFG2                             ( CTL_BASE_PMU_APB + 0x0014 )
#define REG_PMU_APB_PD_NRCP_SYS_CFG                               ( CTL_BASE_PMU_APB + 0x0018 )
#define REG_PMU_APB_PD_AP_SYS_CFG                                 ( CTL_BASE_PMU_APB + 0x001C )
#define REG_PMU_APB_PD_NRCP_DL_CFG                                ( CTL_BASE_PMU_APB + 0x0020 )
#define REG_PMU_APB_PD_NRCP_UL_CFG                                ( CTL_BASE_PMU_APB + 0x0024 )
#define REG_PMU_APB_PD_NRCP_SYNC_CFG                              ( CTL_BASE_PMU_APB + 0x0028 )
#define REG_PMU_APB_PD_GPU_RGX_DUST_A_CFG1                        ( CTL_BASE_PMU_APB + 0x002C )
#define REG_PMU_APB_PD_V3_PS_CFG                                  ( CTL_BASE_PMU_APB + 0x0030 )
#define REG_PMU_APB_PD_V3_LCE_CFG                                 ( CTL_BASE_PMU_APB + 0x0034 )
#define REG_PMU_APB_PD_V3_DPFEC_CFG                               ( CTL_BASE_PMU_APB + 0x0038 )
#define REG_PMU_APB_PD_NRCP_DSP_0_CFG                             ( CTL_BASE_PMU_APB + 0x003C )
#define REG_PMU_APB_PD_NRCP_DSP_1_CFG                             ( CTL_BASE_PMU_APB + 0x0040 )
#define REG_PMU_APB_PD_V3_WCE_CFG                                 ( CTL_BASE_PMU_APB + 0x0044 )
#define REG_PMU_APB_PD_V3_PHY_CFG                                 ( CTL_BASE_PMU_APB + 0x0048 )
#define REG_PMU_APB_PD_V3_LWPROC_CFG                              ( CTL_BASE_PMU_APB + 0x004C )
#define REG_PMU_APB_PD_V3_TD_CFG                                  ( CTL_BASE_PMU_APB + 0x0050 )
#define REG_PMU_APB_PD_V3_MODEM_SYS_CFG                           ( CTL_BASE_PMU_APB + 0x0054 )
#define REG_PMU_APB_PD_PSCP_SYS_CFG                               ( CTL_BASE_PMU_APB + 0x0058 )
#define REG_PMU_APB_PD_AUDCP_AUDDSP_CFG                           ( CTL_BASE_PMU_APB + 0x005C )
#define REG_PMU_APB_PD_AUDCP_SYS_CFG                              ( CTL_BASE_PMU_APB + 0x0060 )
#define REG_PMU_APB_PUBCP_FRC_STOP_REQ_FOR_WTL                    ( CTL_BASE_PMU_APB + 0x0064 )
#define REG_PMU_APB_PD_PUB_SYS_CFG                                ( CTL_BASE_PMU_APB + 0x006C )
#define REG_PMU_APB_AP_WAKEUP_POR_CFG                             ( CTL_BASE_PMU_APB + 0x0070 )
#define REG_PMU_APB_XTL_WAIT_CNT                                  ( CTL_BASE_PMU_APB + 0x0074 )
#define REG_PMU_APB_PLL_WAIT_CNT0                                 ( CTL_BASE_PMU_APB + 0x0078 )
#define REG_PMU_APB_PLL_WAIT_CNT1                                 ( CTL_BASE_PMU_APB + 0x007C )
#define REG_PMU_APB_PLL_WAIT_CNT2                                 ( CTL_BASE_PMU_APB + 0x0080 )
#define REG_PMU_APB_XTL0_REL_CFG                                  ( CTL_BASE_PMU_APB + 0x0084 )
#define REG_PMU_APB_XTL1_REL_CFG                                  ( CTL_BASE_PMU_APB + 0x0088 )
#define REG_PMU_APB_NR_RPLL_REL_CFG                               ( CTL_BASE_PMU_APB + 0x008C )
#define REG_PMU_APB_XTLBUF0_REL_CFG                               ( CTL_BASE_PMU_APB + 0x0090 )
#define REG_PMU_APB_XTLBUF1_REL_CFG                               ( CTL_BASE_PMU_APB + 0x0094 )
#define REG_PMU_APB_DPLL0_REL_CFG                                 ( CTL_BASE_PMU_APB + 0x0098 )
#define REG_PMU_APB_DPLL1_REL_CFG                                 ( CTL_BASE_PMU_APB + 0x009C )
#define REG_PMU_APB_V3PLL_REL_CFG                                 ( CTL_BASE_PMU_APB + 0x00A0 )
#define REG_PMU_APB_NRPLL_REL_CFG                                 ( CTL_BASE_PMU_APB + 0x00A4 )
#define REG_PMU_APB_V3_RPLL_REL_CFG                               ( CTL_BASE_PMU_APB + 0x00A8 )
#define REG_PMU_APB_R8PLL_REL_CFG                                 ( CTL_BASE_PMU_APB + 0x00AC )
#define REG_PMU_APB_CP_SOFT_RST                                   ( CTL_BASE_PMU_APB + 0x00B0 )
#define REG_PMU_APB_CP_SLP_STATUS_DBG0                            ( CTL_BASE_PMU_APB + 0x00B4 )
#define REG_PMU_APB_XTLBUF_LDO_WAIT_CNT                           ( CTL_BASE_PMU_APB + 0x00C4 )
#define REG_PMU_APB_PUB_SYS_AUTO_LIGHT_SLEEP_ENABLE               ( CTL_BASE_PMU_APB + 0x00C8 )
#define REG_PMU_APB_SLEEP_CTRL                                    ( CTL_BASE_PMU_APB + 0x00CC )
#define REG_PMU_APB_DDR_SLEEP_CTRL                                ( CTL_BASE_PMU_APB + 0x00D0 )
#define REG_PMU_APB_SLEEP_STATUS                                  ( CTL_BASE_PMU_APB + 0x00D4 )
#define REG_PMU_APB_PUB_SYS_SLEEP_BYPASS_CFG                      ( CTL_BASE_PMU_APB + 0x00D8 )
#define REG_PMU_APB_PUB_SYS_DEEP_SLEEP_POLL0                      ( CTL_BASE_PMU_APB + 0x00DC )
#define REG_PMU_APB_PUB_SYS_DEEP_SLEEP_POLL1                      ( CTL_BASE_PMU_APB + 0x00E0 )
#define REG_PMU_APB_DDR_CHN_SLEEP_CTRL0                           ( CTL_BASE_PMU_APB + 0x00F8 )
#define REG_PMU_APB_DDR_CHN_SLEEP_CTRL1                           ( CTL_BASE_PMU_APB + 0x00FC )
#define REG_PMU_APB_DDR_OP_MODE_CFG                               ( CTL_BASE_PMU_APB + 0x012C )
#define REG_PMU_APB_DDR_PHY_RET_CFG                               ( CTL_BASE_PMU_APB + 0x0130 )
#define REG_PMU_APB_CLK26M_SEL_CFG                                ( CTL_BASE_PMU_APB + 0x0134 )
#define REG_PMU_APB_BISR_DONE_STATUS                              ( CTL_BASE_PMU_APB + 0x0138 )
#define REG_PMU_APB_BISR_BUSY_STATUS                              ( CTL_BASE_PMU_APB + 0x013C )
#define REG_PMU_APB_BISR_BYP_CFG                                  ( CTL_BASE_PMU_APB + 0x0140 )
#define REG_PMU_APB_BISR_EN_CFG                                   ( CTL_BASE_PMU_APB + 0x0144 )
#define REG_PMU_APB_SLEEP_XTLON_CTRL                              ( CTL_BASE_PMU_APB + 0x0168 )
#define REG_PMU_APB_MEM_SLP_CFG                                   ( CTL_BASE_PMU_APB + 0x016C )
#define REG_PMU_APB_MEM_SD_CFG                                    ( CTL_BASE_PMU_APB + 0x0170 )
#define REG_PMU_APB_APCPU_CORE_WAKEUP_EN                          ( CTL_BASE_PMU_APB + 0x0174 )
#define REG_PMU_APB_SP_SYS_HOLD_CGM_EN                            ( CTL_BASE_PMU_APB + 0x0178 )
#define REG_PMU_APB_PWR_CNT_WAIT_CFG0                             ( CTL_BASE_PMU_APB + 0x017C )
#define REG_PMU_APB_PWR_CNT_WAIT_CFG1                             ( CTL_BASE_PMU_APB + 0x0180 )
#define REG_PMU_APB_RCO_REL_CFG                                   ( CTL_BASE_PMU_APB + 0x0184 )
#define REG_PMU_APB_RCO_CNT_WAIT_CFG                              ( CTL_BASE_PMU_APB + 0x018C )
#define REG_PMU_APB_MPLL0_REL_CFG                                 ( CTL_BASE_PMU_APB + 0x0190 )
#define REG_PMU_APB_MPLL1_REL_CFG                                 ( CTL_BASE_PMU_APB + 0x0194 )
#define REG_PMU_APB_NR_CPUPLL_REL_CFG                             ( CTL_BASE_PMU_APB + 0x0198 )
#define REG_PMU_APB_MEM_AUTO_SLP_CFG                              ( CTL_BASE_PMU_APB + 0x019C )
#define REG_PMU_APB_MEM_AUTO_SD_CFG                               ( CTL_BASE_PMU_APB + 0x01A0 )
#define REG_PMU_APB_WAKEUP_LOCK_EN                                ( CTL_BASE_PMU_APB + 0x01A4 )
#define REG_PMU_APB_AUDCP_SYS_CORE_INT_DISABLE                    ( CTL_BASE_PMU_APB + 0x01A8 )
#define REG_PMU_APB_V3_PS_CORE_INT_DISABLE                        ( CTL_BASE_PMU_APB + 0x01AC )
#define REG_PMU_APB_NRCP_DSP_1_CORE_INT_DISABLE                   ( CTL_BASE_PMU_APB + 0x01B0 )
#define REG_PMU_APB_NRCP_DSP_0_CORE_INT_DISABLE                   ( CTL_BASE_PMU_APB + 0x01B4 )
#define REG_PMU_APB_PSCP_CORE_INT_DISABLE                         ( CTL_BASE_PMU_APB + 0x01B8 )
#define REG_PMU_APB_APCPU_C0_CORE_INT_DISABLE                     ( CTL_BASE_PMU_APB + 0x01BC )
#define REG_PMU_APB_APCPU_C1_CORE_INT_DISABLE                     ( CTL_BASE_PMU_APB + 0x01C0 )
#define REG_PMU_APB_APCPU_C2_CORE_INT_DISABLE                     ( CTL_BASE_PMU_APB + 0x01C4 )
#define REG_PMU_APB_APCPU_C3_CORE_INT_DISABLE                     ( CTL_BASE_PMU_APB + 0x01C8 )
#define REG_PMU_APB_APCPU_C4_CORE_INT_DISABLE                     ( CTL_BASE_PMU_APB + 0x01CC )
#define REG_PMU_APB_APCPU_C5_CORE_INT_DISABLE                     ( CTL_BASE_PMU_APB + 0x01D0 )
#define REG_PMU_APB_NRCP_CORE_INT_DISABLE                         ( CTL_BASE_PMU_APB + 0x01D4 )
#define REG_PMU_APB_V3_PHY_CORE_INT_DISABLE                       ( CTL_BASE_PMU_APB + 0x01D8 )
#define REG_PMU_APB_APCPU_C4_DSLP_ENA                             ( CTL_BASE_PMU_APB + 0x01DC )
#define REG_PMU_APB_APCPU_C5_DSLP_ENA                             ( CTL_BASE_PMU_APB + 0x01E0 )
#define REG_PMU_APB_APCPU_C6_DSLP_ENA                             ( CTL_BASE_PMU_APB + 0x01E4 )
#define REG_PMU_APB_APCPU_C7_DSLP_ENA                             ( CTL_BASE_PMU_APB + 0x01E8 )
#define REG_PMU_APB_NR_DSPPLL_REL_CFG                             ( CTL_BASE_PMU_APB + 0x01EC )
#define REG_PMU_APB_NRCP_DSP_0_DSLP_ENA                           ( CTL_BASE_PMU_APB + 0x0200 )
#define REG_PMU_APB_NRCP_DSP_1_DSLP_ENA                           ( CTL_BASE_PMU_APB + 0x0204 )
#define REG_PMU_APB_AP_DSLP_ENA                                   ( CTL_BASE_PMU_APB + 0x0208 )
#define REG_PMU_APB_PSCP_DSLP_ENA                                 ( CTL_BASE_PMU_APB + 0x020C )
#define REG_PMU_APB_V3_MODEM_DSLP_ENA                             ( CTL_BASE_PMU_APB + 0x0210 )
#define REG_PMU_APB_APCPU_TOP_DSLP_ENA                            ( CTL_BASE_PMU_APB + 0x0214 )
#define REG_PMU_APB_SP_SYS_DSLP_ENA                               ( CTL_BASE_PMU_APB + 0x0218 )
#define REG_PMU_APB_PUB_DEEP_SLEEP_ENA                            ( CTL_BASE_PMU_APB + 0x021C )
#define REG_PMU_APB_PUB_DEEP_SLEEP_WAKEUP_EN                      ( CTL_BASE_PMU_APB + 0x0220 )
#define REG_PMU_APB_LIGHT_SLEEP_WAKEUP_EN                         ( CTL_BASE_PMU_APB + 0x0224 )
#define REG_PMU_APB_V3_PS_DSLP_ENA                                ( CTL_BASE_PMU_APB + 0x0228 )
#define REG_PMU_APB_V3_PHY_DSLP_ENA                               ( CTL_BASE_PMU_APB + 0x022C )
#define REG_PMU_APB_LIGHT_SLEEP_ENABLE                            ( CTL_BASE_PMU_APB + 0x0230 )
#define REG_PMU_APB_LIGHT_SLEEP_MON                               ( CTL_BASE_PMU_APB + 0x0234 )
#define REG_PMU_APB_AUDCP_SYS_DSLP_ENA                            ( CTL_BASE_PMU_APB + 0x0244 )
#define REG_PMU_APB_AUDCP_AUDDSP_DSLP_ENA                         ( CTL_BASE_PMU_APB + 0x0248 )
#define REG_PMU_APB_NRCP_DSLP_ENA                                 ( CTL_BASE_PMU_APB + 0x024C )
#define REG_PMU_APB_PUB_ACC_RDY                                   ( CTL_BASE_PMU_APB + 0x0250 )
#define REG_PMU_APB_PUB_CLK_RDY                                   ( CTL_BASE_PMU_APB + 0x0254 )
#define REG_PMU_APB_EIC_SEL                                       ( CTL_BASE_PMU_APB + 0x0258 )
#define REG_PMU_APB_MIXED_CFG                                     ( CTL_BASE_PMU_APB + 0x025C )
#define REG_PMU_APB_PMU_DEBUG                                     ( CTL_BASE_PMU_APB + 0x0270 )
#define REG_PMU_APB_SLEEP_CNT_CLR                                 ( CTL_BASE_PMU_APB + 0x0274 )
#define REG_PMU_APB_PAD_OUT_DCDC_AI_EN_CFG                        ( CTL_BASE_PMU_APB + 0x027C )
#define REG_PMU_APB_LVDSRFPLL_REL_CFG                             ( CTL_BASE_PMU_APB + 0x0280 )
#define REG_PMU_APB_EXT_XTL_EN_CTRL                               ( CTL_BASE_PMU_APB + 0x0284 )
#define REG_PMU_APB_PAD_OUT_CHIP_SLEEP_CFG                        ( CTL_BASE_PMU_APB + 0x0288 )
#define REG_PMU_APB_PAD_OUT_XTL_EN0_CFG                           ( CTL_BASE_PMU_APB + 0x028C )
#define REG_PMU_APB_PAD_OUT_XTL_EN1_CFG                           ( CTL_BASE_PMU_APB + 0x0290 )
#define REG_PMU_APB_PAD_OUT_DCDC_ARM0_EN_CFG                      ( CTL_BASE_PMU_APB + 0x0294 )
#define REG_PMU_APB_PAD_OUT_XTL_EN2_CFG                           ( CTL_BASE_PMU_APB + 0x0298 )
#define REG_PMU_APB_DCXO_LP_DEEP_SLEEP_CFG                        ( CTL_BASE_PMU_APB + 0x029C )
#define REG_PMU_APB_BISR_FORCE_SEL                                ( CTL_BASE_PMU_APB + 0x0300 )
#define REG_PMU_APB_AON_MEM_CTRL                                  ( CTL_BASE_PMU_APB + 0x0330 )
#define REG_PMU_APB_PWR_DOMAIN_INT_CLR                            ( CTL_BASE_PMU_APB + 0x0334 )
#define REG_PMU_APB_DDR_SLP_WAIT_CNT                              ( CTL_BASE_PMU_APB + 0x0338 )
#define REG_PMU_APB_PMU_CLK_DIV_CFG                               ( CTL_BASE_PMU_APB + 0x033C )
#define REG_PMU_APB_CGM_PMU_SEL                                   ( CTL_BASE_PMU_APB + 0x0340 )
#define REG_PMU_APB_PWR_DGB_PARAMETER                             ( CTL_BASE_PMU_APB + 0x0344 )
#define REG_PMU_APB_APCPU_C0_DSLP_ENA                             ( CTL_BASE_PMU_APB + 0x0348 )
#define REG_PMU_APB_APCPU_C1_DSLP_ENA                             ( CTL_BASE_PMU_APB + 0x034C )
#define REG_PMU_APB_APCPU_C2_DSLP_ENA                             ( CTL_BASE_PMU_APB + 0x0350 )
#define REG_PMU_APB_APCPU_C3_DSLP_ENA                             ( CTL_BASE_PMU_APB + 0x0354 )
#define REG_PMU_APB_APCPU_GIC_RST_EN                              ( CTL_BASE_PMU_APB + 0x0358 )
#define REG_PMU_APB_ANALOG_PHY_PD_CFG                             ( CTL_BASE_PMU_APB + 0x035C )
#define REG_PMU_APB_PUB_SYS_DEEP_SLEEP_SEL                        ( CTL_BASE_PMU_APB + 0x0360 )
#define REG_PMU_APB_PD_APCPU_C4_CFG                               ( CTL_BASE_PMU_APB + 0x0364 )
#define REG_PMU_APB_PD_APCPU_C5_CFG                               ( CTL_BASE_PMU_APB + 0x0368 )
#define REG_PMU_APB_PD_APCPU_C6_CFG                               ( CTL_BASE_PMU_APB + 0x036C )
#define REG_PMU_APB_PD_APCPU_C7_CFG                               ( CTL_BASE_PMU_APB + 0x0370 )
#define REG_PMU_APB_PD_APCPU_TOP_CFG3                             ( CTL_BASE_PMU_APB + 0x0374 )
#define REG_PMU_APB_DCDC_AI_CTRL                                  ( CTL_BASE_PMU_APB + 0x0378 )
#define REG_PMU_APB_APCPU_TOP_CFG                                 ( CTL_BASE_PMU_APB + 0x0380 )
#define REG_PMU_APB_PUB_VOL_DOWN_CFG                              ( CTL_BASE_PMU_APB + 0x0384 )
#define REG_PMU_APB_PLL_WAIT_CNT3                                 ( CTL_BASE_PMU_APB + 0x0388 )
#define REG_PMU_APB_R5PLL_REL_CFG                                 ( CTL_BASE_PMU_APB + 0x038C )
#define REG_PMU_APB_APCPU_DSLP_ENA_SRST_MASK_CFG                  ( CTL_BASE_PMU_APB + 0x0390 )
#define REG_PMU_APB_PCIEPLL_H_REL_CFG                             ( CTL_BASE_PMU_APB + 0x0394 )
#define REG_PMU_APB_R5PLL_RST_CTRL_CFG                            ( CTL_BASE_PMU_APB + 0x0398 )
#define REG_PMU_APB_PCIEPLL_H_RST_CTRL_CFG                        ( CTL_BASE_PMU_APB + 0x039C )
#define REG_PMU_APB_PCIE_SLP_CFG                                  ( CTL_BASE_PMU_APB + 0x03A0 )
#define REG_PMU_APB_GIC_CFG                                       ( CTL_BASE_PMU_APB + 0x03A8 )
#define REG_PMU_APB_FIREWALL_WAKEUP_PUB                           ( CTL_BASE_PMU_APB + 0x03AC )
#define REG_PMU_APB_PD_ESE_SYS_CFG                                ( CTL_BASE_PMU_APB + 0x03B0 )
#define REG_PMU_APB_APCPU_MODE_ST_CFG                             ( CTL_BASE_PMU_APB + 0x03B4 )
#define REG_PMU_APB_APCPU_C0_SIMD_RET_MODE                        ( CTL_BASE_PMU_APB + 0x03B8 )
#define REG_PMU_APB_APCPU_C1_SIMD_RET_MODE                        ( CTL_BASE_PMU_APB + 0x03BC )
#define REG_PMU_APB_APCPU_C2_SIMD_RET_MODE                        ( CTL_BASE_PMU_APB + 0x03C0 )
#define REG_PMU_APB_APCPU_C3_SIMD_RET_MODE                        ( CTL_BASE_PMU_APB + 0x03C4 )
#define REG_PMU_APB_APCPU_CORE_FORCE_STOP                         ( CTL_BASE_PMU_APB + 0x03D4 )
#define REG_PMU_APB_PD_GPU_TOP_CFG1                               ( CTL_BASE_PMU_APB + 0x03E0 )
#define REG_PMU_APB_MPLL_WAIT_CLK_DIV_CFG                         ( CTL_BASE_PMU_APB + 0x03E4 )
#define REG_PMU_APB_MPLL0_RST_CTRL_CFG                            ( CTL_BASE_PMU_APB + 0x03E8 )
#define REG_PMU_APB_MPLL1_RST_CTRL_CFG                            ( CTL_BASE_PMU_APB + 0x03EC )
#define REG_PMU_APB_R8PLL_RST_CTRL_CFG                            ( CTL_BASE_PMU_APB + 0x03F0 )
#define REG_PMU_APB_NR_CPUPLL_RST_CTRL_CFG                        ( CTL_BASE_PMU_APB + 0x03F4 )
#define REG_PMU_APB_DPLL0_RST_CTRL_CFG                            ( CTL_BASE_PMU_APB + 0x03F8 )
#define REG_PMU_APB_DPLL1_RST_CTRL_CFG                            ( CTL_BASE_PMU_APB + 0x03FC )
#define REG_PMU_APB_V3PLL_RST_CTRL_CFG                            ( CTL_BASE_PMU_APB + 0x0400 )
#define REG_PMU_APB_NRPLL_RST_CTRL_CFG                            ( CTL_BASE_PMU_APB + 0x0404 )
#define REG_PMU_APB_NR_DSPPLL_RST_CTRL_CFG                        ( CTL_BASE_PMU_APB + 0x0408 )
#define REG_PMU_APB_V3_RPLL_RST_CTRL_CFG                          ( CTL_BASE_PMU_APB + 0x040C )
#define REG_PMU_APB_NR_RPLL_RST_CTRL_CFG                          ( CTL_BASE_PMU_APB + 0x0410 )
#define REG_PMU_APB_PLL_RST_CTRL_STATE0                           ( CTL_BASE_PMU_APB + 0x0414 )
#define REG_PMU_APB_PLL_RST_CTRL_STATE1                           ( CTL_BASE_PMU_APB + 0x0418 )
#define REG_PMU_APB_ESE_FAST_WAKEUP_CTRL                          ( CTL_BASE_PMU_APB + 0x041C )
#define REG_PMU_APB_NRCP_DSP_TCM_RAM_POWER_CTRL                   ( CTL_BASE_PMU_APB + 0x0420 )
#define REG_PMU_APB_WTLCP_HU3GE_NEST_DOMAIN_CTRL                  ( CTL_BASE_PMU_APB + 0x0424 )
#define REG_PMU_APB_DEBUG_RECOV_TYPE_CFG                          ( CTL_BASE_PMU_APB + 0x0428 )
#define REG_PMU_APB_APCPU_MODE_ST_CFG1                            ( CTL_BASE_PMU_APB + 0x042C )
#define REG_PMU_APB_APCPU_MODE_ST_CFG2                            ( CTL_BASE_PMU_APB + 0x0430 )
#define REG_PMU_APB_APCPU_MODE_ST_CFG3                            ( CTL_BASE_PMU_APB + 0x0434 )
#define REG_PMU_APB_DEBUG_STATE_MARK                              ( CTL_BASE_PMU_APB + 0x0438 )
#define REG_PMU_APB_ANANKELITE_MEM_POWER_CFG                      ( CTL_BASE_PMU_APB + 0x043C )
#define REG_PMU_APB_APCPU_MODE_ST_FRC_ON_CFG                      ( CTL_BASE_PMU_APB + 0x0440 )
#define REG_PMU_APB_APCPU_SOFT_RST_TYPE_CFG                       ( CTL_BASE_PMU_APB + 0x0444 )
#define REG_PMU_APB_APCPU_CORINTH_SCU_CLK_GATE_CFG                ( CTL_BASE_PMU_APB + 0x0448 )
#define REG_PMU_APB_APCPU_PCHANNEL_STATE0                         ( CTL_BASE_PMU_APB + 0x044C )
#define REG_PMU_APB_APCPU_PCHANNEL_STATE1                         ( CTL_BASE_PMU_APB + 0x0450 )
#define REG_PMU_APB_APCPU_SOFT_INT_GEN                            ( CTL_BASE_PMU_APB + 0x0454 )
#define REG_PMU_APB_DUAL_RAIL_RAM_FORCE_PD_CFG                    ( CTL_BASE_PMU_APB + 0x0458 )
#define REG_PMU_APB_DUAL_RAIL_RAM_FORCE_SLP_CFG                   ( CTL_BASE_PMU_APB + 0x045C )
#define REG_PMU_APB_PUB_DFS_FRQ_SEL                               ( CTL_BASE_PMU_APB + 0x0460 )
#define REG_PMU_APB_APCPU_CORE0_SW_PACTIVE                        ( CTL_BASE_PMU_APB + 0x0464 )
#define REG_PMU_APB_APCPU_CORE1_SW_PACTIVE                        ( CTL_BASE_PMU_APB + 0x0468 )
#define REG_PMU_APB_APCPU_CORE2_SW_PACTIVE                        ( CTL_BASE_PMU_APB + 0x046C )
#define REG_PMU_APB_APCPU_CORE3_SW_PACTIVE                        ( CTL_BASE_PMU_APB + 0x0470 )
#define REG_PMU_APB_APCPU_CORE4_SW_PACTIVE                        ( CTL_BASE_PMU_APB + 0x0474 )
#define REG_PMU_APB_APCPU_CORE5_SW_PACTIVE                        ( CTL_BASE_PMU_APB + 0x0478 )
#define REG_PMU_APB_APCPU_CORE6_SW_PACTIVE                        ( CTL_BASE_PMU_APB + 0x047C )
#define REG_PMU_APB_APCPU_CORE7_SW_PACTIVE                        ( CTL_BASE_PMU_APB + 0x0480 )
#define REG_PMU_APB_APCPU_CLUSTER_SW_PACTIVE                      ( CTL_BASE_PMU_APB + 0x0484 )
#define REG_PMU_APB_SOFTWARE_APCPU_PACTIVE_ENABLE                 ( CTL_BASE_PMU_APB + 0x0488 )
#define REG_PMU_APB_SOFTWARE_APCPU_PCHANNEL_HANDSHAKE_ENABLE      ( CTL_BASE_PMU_APB + 0x048C )
#define REG_PMU_APB_APCPU_CORE0_SW_PCHANNEL_HANDSHAKE             ( CTL_BASE_PMU_APB + 0x0490 )
#define REG_PMU_APB_APCPU_CORE1_SW_PCHANNEL_HANDSHAKE             ( CTL_BASE_PMU_APB + 0x0494 )
#define REG_PMU_APB_APCPU_CORE2_SW_PCHANNEL_HANDSHAKE             ( CTL_BASE_PMU_APB + 0x0498 )
#define REG_PMU_APB_APCPU_CORE3_SW_PCHANNEL_HANDSHAKE             ( CTL_BASE_PMU_APB + 0x049C )
#define REG_PMU_APB_APCPU_CORE4_SW_PCHANNEL_HANDSHAKE             ( CTL_BASE_PMU_APB + 0x04A0 )
#define REG_PMU_APB_APCPU_CORE5_SW_PCHANNEL_HANDSHAKE             ( CTL_BASE_PMU_APB + 0x04A4 )
#define REG_PMU_APB_APCPU_CORE6_SW_PCHANNEL_HANDSHAKE             ( CTL_BASE_PMU_APB + 0x04A8 )
#define REG_PMU_APB_APCPU_CORE7_SW_PCHANNEL_HANDSHAKE             ( CTL_BASE_PMU_APB + 0x04AC )
#define REG_PMU_APB_APCPU_CLUSTER_SW_PCHANNEL_HANDSHAKE           ( CTL_BASE_PMU_APB + 0x04B0 )
#define REG_PMU_APB_WTLCP_DPFEC_NEST_DOMAIN_CTRL                  ( CTL_BASE_PMU_APB + 0x04B4 )
#define REG_PMU_APB_GPIO_FORCE_GATING_PLL_CFG                     ( CTL_BASE_PMU_APB + 0x04B8 )
#define REG_PMU_APB_ANALOG_PHY_PWRON_CFG                          ( CTL_BASE_PMU_APB + 0x04BC )
#define REG_PMU_APB_APCPU_MODE_ST_CGM_EN_CFG                      ( CTL_BASE_PMU_APB + 0x04C0 )
#define REG_PMU_APB_APCPU_DENY_TIME_THRESHOLD_CFG                 ( CTL_BASE_PMU_APB + 0x04C4 )
#define REG_PMU_APB_INT_REQ_APCPU_MODE_ST_ENABLE                  ( CTL_BASE_PMU_APB + 0x04C8 )
#define REG_PMU_APB_INT_REQ_APCPU_MODE_ST_CLR                     ( CTL_BASE_PMU_APB + 0x04CC )
#define REG_PMU_APB_INT_REQ_MODE_ST_RECORD                        ( CTL_BASE_PMU_APB + 0x04D0 )
#define REG_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE0_INF               ( CTL_BASE_PMU_APB + 0x04D4 )
#define REG_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE1_INF               ( CTL_BASE_PMU_APB + 0x04D8 )
#define REG_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE2_INF               ( CTL_BASE_PMU_APB + 0x04DC )
#define REG_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE3_INF               ( CTL_BASE_PMU_APB + 0x04E0 )
#define REG_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE4_INF               ( CTL_BASE_PMU_APB + 0x04E4 )
#define REG_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE5_INF               ( CTL_BASE_PMU_APB + 0x04E8 )
#define REG_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE6_INF               ( CTL_BASE_PMU_APB + 0x04EC )
#define REG_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE7_INF               ( CTL_BASE_PMU_APB + 0x04F0 )
#define REG_PMU_APB_INT_REQ_MODE_ST_APCPU_CLUSTER_INF             ( CTL_BASE_PMU_APB + 0x04F4 )
#define REG_PMU_APB_APCPU_CSYSPWRUP_WAKEUP_EN_CFG                 ( CTL_BASE_PMU_APB + 0x04F8 )
#define REG_PMU_APB_DVFS_BLOCK_SHUTDOWN_CFG                       ( CTL_BASE_PMU_APB + 0x04FC )
#define REG_PMU_APB_OFF_EMU_CLR_IN_DISABLE_CFG                    ( CTL_BASE_PMU_APB + 0x0500 )
#define REG_PMU_APB_APCPU_DUAL_RAIL_RAM_FORCE_ON_CFG              ( CTL_BASE_PMU_APB + 0x0504 )
#define REG_PMU_APB_OFF_EMU_TO_OFF_CFG                            ( CTL_BASE_PMU_APB + 0x0508 )
#define REG_PMU_APB_ALL_PLL_PD_RCO_BYP                            ( CTL_BASE_PMU_APB + 0x050C )
#define REG_PMU_APB_SP_CLK_GATE_BYP_CFG                           ( CTL_BASE_PMU_APB + 0x0510 )
#define REG_PMU_APB_DPLL1_CNT_DONE_BYP                            ( CTL_BASE_PMU_APB + 0x0514 )
#define REG_PMU_APB_SRAM_DLY_CTRL_CFG                             ( CTL_BASE_PMU_APB + 0x0518 )
#define REG_PMU_APB_WDG_TRIG_DBG_RECOV_CFG                        ( CTL_BASE_PMU_APB + 0x051C )
#define REG_PMU_APB_APCPU_TOP_RAM_POWER_CTRL                      ( CTL_BASE_PMU_APB + 0x0520 )
#define REG_PMU_APB_PD_GPU_RGX_DUST_B_CFG0                        ( CTL_BASE_PMU_APB + 0x0524 )
#define REG_PMU_APB_PD_GPU_RGX_DUST_B_CFG1                        ( CTL_BASE_PMU_APB + 0x0528 )
#define REG_PMU_APB_PD_IPA_SYS_CFG                                ( CTL_BASE_PMU_APB + 0x0538 )
#define REG_PMU_APB_APCPU_MODE_ST_SOFT_RST                        ( CTL_BASE_PMU_APB + 0x053C )
#define REG_PMU_APB_FORCE_PUB_DEEP_SLEEP_CFG                      ( CTL_BASE_PMU_APB + 0x0540 )
#define REG_PMU_APB_FORCE_DEEP_SLEEP_CFG                          ( CTL_BASE_PMU_APB + 0x0544 )
#define REG_PMU_APB_FORCE_LIGHT_SLEEP_CFG                         ( CTL_BASE_PMU_APB + 0x0548 )
#define REG_PMU_APB_FORCE_SYSTEM_SLEEP_CFG                        ( CTL_BASE_PMU_APB + 0x054C )
#define REG_PMU_APB_ESE_ACCESS_DDR_CFG                            ( CTL_BASE_PMU_APB + 0x0550 )
#define REG_PMU_APB_PWR_STATUS1_DBG                               ( CTL_BASE_PMU_APB + 0x0584 )
#define REG_PMU_APB_PWR_STATUS2_DBG                               ( CTL_BASE_PMU_APB + 0x0588 )
#define REG_PMU_APB_PWR_STATUS3_DBG                               ( CTL_BASE_PMU_APB + 0x058C )
#define REG_PMU_APB_PWR_STATUS4_DBG                               ( CTL_BASE_PMU_APB + 0x0590 )
#define REG_PMU_APB_PWR_STATUS5_DBG                               ( CTL_BASE_PMU_APB + 0x0594 )
#define REG_PMU_APB_PWR_STATUS6_DBG                               ( CTL_BASE_PMU_APB + 0x059C )
#define REG_PMU_APB_PWR_STATUS7_DBG                               ( CTL_BASE_PMU_APB + 0x05A0 )
#define REG_PMU_APB_PWR_STATUS8_DBG                               ( CTL_BASE_PMU_APB + 0x05A4 )
#define REG_PMU_APB_APCU_MODE_STATE0                              ( CTL_BASE_PMU_APB + 0x05B0 )
#define REG_PMU_APB_APCU_MODE_STATE1                              ( CTL_BASE_PMU_APB + 0x05B4 )
#define REG_PMU_APB_APCU_MODE_STATE2                              ( CTL_BASE_PMU_APB + 0x05B8 )
#define REG_PMU_APB_APCPU_WFI_MARK                                ( CTL_BASE_PMU_APB + 0x05C0 )
#define REG_PMU_APB_AXI_LP_CTRL_DISABLE                           ( CTL_BASE_PMU_APB + 0x05D0 )
#define REG_PMU_APB_PD_APCPU_C0_SHUTDOWN_MARK_STATUS              ( CTL_BASE_PMU_APB + 0x0600 )
#define REG_PMU_APB_PD_APCPU_C1_SHUTDOWN_MARK_STATUS              ( CTL_BASE_PMU_APB + 0x0604 )
#define REG_PMU_APB_PD_APCPU_C2_SHUTDOWN_MARK_STATUS              ( CTL_BASE_PMU_APB + 0x0608 )
#define REG_PMU_APB_PD_APCPU_C3_SHUTDOWN_MARK_STATUS              ( CTL_BASE_PMU_APB + 0x060C )
#define REG_PMU_APB_PD_APCPU_TOP_SHUTDOWN_MARK_STATUS             ( CTL_BASE_PMU_APB + 0x0610 )
#define REG_PMU_APB_PD_AP_SYS_SHUTDOWN_MARK_STATUS                ( CTL_BASE_PMU_APB + 0x0614 )
#define REG_PMU_APB_PD_NRCP_SYS_SHUTDOWN_MARK_STATUS              ( CTL_BASE_PMU_APB + 0x0618 )
#define REG_PMU_APB_PD_NRCP_SYNC_SHUTDOWN_MARK_STATUS             ( CTL_BASE_PMU_APB + 0x061C )
#define REG_PMU_APB_PD_V3_WCE_SHUTDOWN_MARK_STATUS                ( CTL_BASE_PMU_APB + 0x0620 )
#define REG_PMU_APB_PD_V3_LCE_SHUTDOWN_MARK_STATUS                ( CTL_BASE_PMU_APB + 0x0624 )
#define REG_PMU_APB_PD_V3_DPFEC_SHUTDOWN_MARK_STATUS              ( CTL_BASE_PMU_APB + 0x0628 )
#define REG_PMU_APB_PD_V3_LWPROC_SHUTDOWN_MARK_STATUS             ( CTL_BASE_PMU_APB + 0x062C )
#define REG_PMU_APB_PD_V3_PHY_SHUTDOWN_MARK_STATUS                ( CTL_BASE_PMU_APB + 0x0630 )
#define REG_PMU_APB_PD_V3_PS_SHUTDOWN_MARK_STATUS                 ( CTL_BASE_PMU_APB + 0x0634 )
#define REG_PMU_APB_PD_NRCP_DSP_0_SHUTDOWN_MARK_STATUS            ( CTL_BASE_PMU_APB + 0x0638 )
#define REG_PMU_APB_PD_NRCP_DSP_1_SHUTDOWN_MARK_STATUS            ( CTL_BASE_PMU_APB + 0x063C )
#define REG_PMU_APB_PD_V3_MODEM_SYS_SHUTDOWN_MARK_STATUS          ( CTL_BASE_PMU_APB + 0x0640 )
#define REG_PMU_APB_PD_PSCP_SYS_SHUTDOWN_MARK_STATUS              ( CTL_BASE_PMU_APB + 0x0644 )
#define REG_PMU_APB_PD_NRCP_DL_SHUTDOWN_MARK_STATUS               ( CTL_BASE_PMU_APB + 0x0648 )
#define REG_PMU_APB_PD_V3_TD_SHUTDOWN_MARK_STATUS                 ( CTL_BASE_PMU_APB + 0x064C )
#define REG_PMU_APB_PD_AUDCP_SYS_SHUTDOWN_MARK_STATUS             ( CTL_BASE_PMU_APB + 0x0650 )
#define REG_PMU_APB_PD_PUB_SYS_SHUTDOWN_MARK_STATUS               ( CTL_BASE_PMU_APB + 0x0654 )
#define REG_PMU_APB_PD_AUDCP_AUDDSP_SHUTDOWN_MARK_STATUS          ( CTL_BASE_PMU_APB + 0x0658 )
#define REG_PMU_APB_PD_NRCP_UL_SHUTDOWN_MARK_STATUS               ( CTL_BASE_PMU_APB + 0x065C )
#define REG_PMU_APB_PD_GPU_RGX_DUST_B_SHUTDOWN_MARK_STATUS        ( CTL_BASE_PMU_APB + 0x0660 )
#define REG_PMU_APB_APCPU_TOP_SLEEP_CNT                           ( CTL_BASE_PMU_APB + 0x0664 )
#define REG_PMU_APB_AP_SYS_SLEEP_CNT                              ( CTL_BASE_PMU_APB + 0x0668 )
#define REG_PMU_APB_V3_MODEM_SYS_SLEEP_CNT                        ( CTL_BASE_PMU_APB + 0x066C )
#define REG_PMU_APB_PSCP_SYS_SLEEP_CNT                            ( CTL_BASE_PMU_APB + 0x0670 )
#define REG_PMU_APB_AUDCP_SYS_SLEEP_CNT                           ( CTL_BASE_PMU_APB + 0x0674 )
#define REG_PMU_APB_PUB_SYS_LIGHT_SLEEP_CNT                       ( CTL_BASE_PMU_APB + 0x0678 )
#define REG_PMU_APB_AP_DEEP_SLEEP_CNT                             ( CTL_BASE_PMU_APB + 0x067C )
#define REG_PMU_APB_SP_SYS_DEEP_SLEEP_CNT                         ( CTL_BASE_PMU_APB + 0x0680 )
#define REG_PMU_APB_V3_MODEM_DEEP_SLEEP_CNT                       ( CTL_BASE_PMU_APB + 0x0684 )
#define REG_PMU_APB_PSCP_DEEP_SLEEP_CNT                           ( CTL_BASE_PMU_APB + 0x0688 )
#define REG_PMU_APB_AUDCP_SYS_DEEP_SLEEP_CNT                      ( CTL_BASE_PMU_APB + 0x068C )
#define REG_PMU_APB_PUB_SYS_DEEP_SLEEP_CNT                        ( CTL_BASE_PMU_APB + 0x0690 )
#define REG_PMU_APB_AP_LIGHT_SLEEP_CNT                            ( CTL_BASE_PMU_APB + 0x0694 )
#define REG_PMU_APB_V3_MODEM_LIGHT_SLEEP_CNT                      ( CTL_BASE_PMU_APB + 0x0698 )
#define REG_PMU_APB_PSCP_LIGHT_SLEEP_CNT                          ( CTL_BASE_PMU_APB + 0x069C )
#define REG_PMU_APB_AUDCP_SYS_LIGHT_SLEEP_CNT                     ( CTL_BASE_PMU_APB + 0x06A0 )
#define REG_PMU_APB_AON_SYS_LIGHT_SLEEP_CNT                       ( CTL_BASE_PMU_APB + 0x06A4 )
#define REG_PMU_APB_SYS_SOFT_RST_BUSY                             ( CTL_BASE_PMU_APB + 0x06A8 )
#define REG_PMU_APB_REG_SYS_SRST_FRC_LP_ACK                       ( CTL_BASE_PMU_APB + 0x06AC )
#define REG_PMU_APB_SOFT_RST_SEL                                  ( CTL_BASE_PMU_APB + 0x06B0 )
#define REG_PMU_APB_REG_SYS_DDR_PWR_HS_ACK                        ( CTL_BASE_PMU_APB + 0x06B4 )
#define REG_PMU_APB_CSI_DSI_PWR_CNT_DONE                          ( CTL_BASE_PMU_APB + 0x06B8 )
#define REG_PMU_APB_PD_AP_SYS_DBG_SHUTDOWN__EN                    ( CTL_BASE_PMU_APB + 0x06BC )
#define REG_PMU_APB_EIC_SYS_SEL                                   ( CTL_BASE_PMU_APB + 0x06C0 )
#define REG_PMU_APB_DDR_SLP_CTRL_STATE                            ( CTL_BASE_PMU_APB + 0x06C4 )
#define REG_PMU_APB_PD_APCPU_C4_SHUTDOWN_MARK_STATUS              ( CTL_BASE_PMU_APB + 0x06C8 )
#define REG_PMU_APB_PD_APCPU_C5_SHUTDOWN_MARK_STATUS              ( CTL_BASE_PMU_APB + 0x06CC )
#define REG_PMU_APB_PD_APCPU_C6_SHUTDOWN_MARK_STATUS              ( CTL_BASE_PMU_APB + 0x06D0 )
#define REG_PMU_APB_PD_APCPU_C7_SHUTDOWN_MARK_STATUS              ( CTL_BASE_PMU_APB + 0x06D4 )
#define REG_PMU_APB_APCPU_TOP_DEEP_SLEEP_CNT                      ( CTL_BASE_PMU_APB + 0x06D8 )
#define REG_PMU_APB_APCPU_TOP_LIGHT_SLEEP_CNT                     ( CTL_BASE_PMU_APB + 0x06DC )
#define REG_PMU_APB_PD_ESE_SYS_SHUTDOWN_MARK_STATUS               ( CTL_BASE_PMU_APB + 0x06E0 )
#define REG_PMU_APB_NRCP_DEEP_SLEEP_CNT                           ( CTL_BASE_PMU_APB + 0x06E4 )
#define REG_PMU_APB_NRCP_SYS_SLEEP_CNT                            ( CTL_BASE_PMU_APB + 0x06E8 )
#define REG_PMU_APB_PD_IPA_SHUTDOWN_MARK_STATUS                   ( CTL_BASE_PMU_APB + 0x06EC )
#define REG_PMU_APB_NRCP_LIGHT_SLEEP_CNT                          ( CTL_BASE_PMU_APB + 0x0720 )
#define REG_PMU_APB_IPA_DEEP_SLEEP_CNT                            ( CTL_BASE_PMU_APB + 0x0724 )
#define REG_PMU_APB_IPA_SYS_SLEEP_CNT                             ( CTL_BASE_PMU_APB + 0x0728 )
#define REG_PMU_APB_IPA_LIGHT_SLEEP_CNT                           ( CTL_BASE_PMU_APB + 0x072C )

/* REG_PMU_APB_PD_APCPU_TOP_CFG */

#define BIT_PMU_APB_PD_APCPU_TOP_DBG_SHUTDOWN_EN                   BIT(28)
#define BIT_PMU_APB_PD_APCPU_TOP_PD_SEL                            BIT(27)
#define BIT_PMU_APB_PD_APCPU_TOP_FORCE_SHUTDOWN                    BIT(25)
#define BIT_PMU_APB_PD_APCPU_TOP_AUTO_SHUTDOWN_EN                  BIT(24)
#define BIT_PMU_APB_PD_APCPU_TOP_PWR_ON_SEQ_DLY(x)                 (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_APCPU_TOP_ISO_ON_DLY(x)                     (((x) & 0xFF))

/* REG_PMU_APB_PD_APCPU_C0_CFG */

#define BIT_PMU_APB_PD_APCPU_C0_WFI_SHUTDOWN_EN                    BIT(29)
#define BIT_PMU_APB_PD_APCPU_C0_DBG_SHUTDOWN_EN                    BIT(28)
#define BIT_PMU_APB_PD_APCPU_C0_PD_SEL                             BIT(27)
#define BIT_PMU_APB_PD_APCPU_C0_FORCE_SHUTDOWN                     BIT(25)
#define BIT_PMU_APB_PD_APCPU_C0_AUTO_SHUTDOWN_EN                   BIT(24)
#define BIT_PMU_APB_PD_APCPU_C0_PWR_ON_DLY(x)                      (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_APCPU_C0_PWR_ON_SEQ_DLY(x)                  (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_APCPU_C0_ISO_ON_DLY(x)                      (((x) & 0xFF))

/* REG_PMU_APB_PD_APCPU_C1_CFG */

#define BIT_PMU_APB_PD_APCPU_C1_WFI_SHUTDOWN_EN                    BIT(29)
#define BIT_PMU_APB_PD_APCPU_C1_DBG_SHUTDOWN_EN                    BIT(28)
#define BIT_PMU_APB_PD_APCPU_C1_PD_SEL                             BIT(27)
#define BIT_PMU_APB_PD_APCPU_C1_FORCE_SHUTDOWN                     BIT(25)
#define BIT_PMU_APB_PD_APCPU_C1_AUTO_SHUTDOWN_EN                   BIT(24)
#define BIT_PMU_APB_PD_APCPU_C1_PWR_ON_DLY(x)                      (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_APCPU_C1_PWR_ON_SEQ_DLY(x)                  (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_APCPU_C1_ISO_ON_DLY(x)                      (((x) & 0xFF))

/* REG_PMU_APB_PD_APCPU_C2_CFG */

#define BIT_PMU_APB_PD_APCPU_C2_WFI_SHUTDOWN_EN                    BIT(29)
#define BIT_PMU_APB_PD_APCPU_C2_DBG_SHUTDOWN_EN                    BIT(28)
#define BIT_PMU_APB_PD_APCPU_C2_PD_SEL                             BIT(27)
#define BIT_PMU_APB_PD_APCPU_C2_FORCE_SHUTDOWN                     BIT(25)
#define BIT_PMU_APB_PD_APCPU_C2_AUTO_SHUTDOWN_EN                   BIT(24)
#define BIT_PMU_APB_PD_APCPU_C2_PWR_ON_DLY(x)                      (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_APCPU_C2_PWR_ON_SEQ_DLY(x)                  (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_APCPU_C2_ISO_ON_DLY(x)                      (((x) & 0xFF))

/* REG_PMU_APB_PD_APCPU_C3_CFG */

#define BIT_PMU_APB_PD_APCPU_C3_WFI_SHUTDOWN_EN                    BIT(29)
#define BIT_PMU_APB_PD_APCPU_C3_DBG_SHUTDOWN_EN                    BIT(28)
#define BIT_PMU_APB_PD_APCPU_C3_PD_SEL                             BIT(27)
#define BIT_PMU_APB_PD_APCPU_C3_FORCE_SHUTDOWN                     BIT(25)
#define BIT_PMU_APB_PD_APCPU_C3_AUTO_SHUTDOWN_EN                   BIT(24)
#define BIT_PMU_APB_PD_APCPU_C3_PWR_ON_DLY(x)                      (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_APCPU_C3_PWR_ON_SEQ_DLY(x)                  (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_APCPU_C3_ISO_ON_DLY(x)                      (((x) & 0xFF))

/* REG_PMU_APB_PD_APCPU_TOP_CFG2 */

#define BIT_PMU_APB_PD_APCPU_TOP_DCDC_PWR_ON_DLY(x)                (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_APCPU_TOP_DCDC_PWR_OFF_DLY(x)               (((x) & 0xFF))

/* REG_PMU_APB_PD_NRCP_SYS_CFG */

#define BIT_PMU_APB_PD_NRCP_SYS_DBG_SHUTDOWN_EN                    BIT(27)
#define BIT_PMU_APB_PD_NRCP_SYS_FORCE_SHUTDOWN                     BIT(25)
#define BIT_PMU_APB_PD_NRCP_SYS_AUTO_SHUTDOWN_EN                   BIT(24)
#define BIT_PMU_APB_PD_NRCP_SYS_PWR_ON_DLY(x)                      (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_NRCP_SYS_PWR_ON_SEQ_DLY(x)                  (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_NRCP_SYS_ISO_ON_DLY(x)                      (((x) & 0xFF))

/* REG_PMU_APB_PD_AP_SYS_CFG */

#define BIT_PMU_APB_PD_AP_SYS_FORCE_SHUTDOWN                       BIT(25)
#define BIT_PMU_APB_PD_AP_SYS_AUTO_SHUTDOWN_EN                     BIT(24)
#define BIT_PMU_APB_PD_AP_SYS_PWR_ON_DLY(x)                        (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_AP_SYS_PWR_ON_SEQ_DLY(x)                    (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_AP_SYS_ISO_ON_DLY(x)                        (((x) & 0xFF))

/* REG_PMU_APB_PD_NRCP_DL_CFG */

#define BIT_PMU_APB_PD_NRCP_DL_FORCE_SHUTDOWN                      BIT(25)
#define BIT_PMU_APB_PD_NRCP_DL_AUTO_SHUTDOWN_EN                    BIT(24)
#define BIT_PMU_APB_PD_NRCP_DL_PWR_ON_DLY(x)                       (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_NRCP_DL_PWR_ON_SEQ_DLY(x)                   (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_NRCP_DL_ISO_ON_DLY(x)                       (((x) & 0xFF))

/* REG_PMU_APB_PD_NRCP_UL_CFG */

#define BIT_PMU_APB_PD_NRCP_UL_FORCE_SHUTDOWN                      BIT(25)
#define BIT_PMU_APB_PD_NRCP_UL_AUTO_SHUTDOWN_EN                    BIT(24)
#define BIT_PMU_APB_PD_NRCP_UL_PWR_ON_DLY(x)                       (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_NRCP_UL_PWR_ON_SEQ_DLY(x)                   (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_NRCP_UL_ISO_ON_DLY(x)                       (((x) & 0xFF))

/* REG_PMU_APB_PD_NRCP_SYNC_CFG */

#define BIT_PMU_APB_PD_NRCP_SYNC_FORCE_SHUTDOWN                    BIT(25)
#define BIT_PMU_APB_PD_NRCP_SYNC_AUTO_SHUTDOWN_EN                  BIT(24)
#define BIT_PMU_APB_PD_NRCP_SYNC_PWR_ON_DLY(x)                     (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_NRCP_SYNC_PWR_ON_SEQ_DLY(x)                 (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_NRCP_SYNC_ISO_ON_DLY(x)                     (((x) & 0xFF))

/* REG_PMU_APB_PD_GPU_RGX_DUST_A_CFG1 */

#define BIT_PMU_APB_PD_GPU_RGX_DUST_A_SHUTDOWN_DLY(x)              (((x) & 0xFF) << 24)
#define BIT_PMU_APB_PD_GPU_RGX_DUST_A_RST_DEASSERT_DLY(x)          (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_GPU_RGX_DUST_A_RST_ASSERT_DLY(x)            (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_GPU_RGX_DUST_A_ISO_OFF_DLY(x)               (((x) & 0xFF))

/* REG_PMU_APB_PD_V3_PS_CFG */

#define BIT_PMU_APB_PD_V3_PS_PD_SEL                                BIT(27)
#define BIT_PMU_APB_PD_V3_PS_DBG_SHUTDOWN_EN                       BIT(26)
#define BIT_PMU_APB_PD_V3_PS_FORCE_SHUTDOWN                        BIT(25)
#define BIT_PMU_APB_PD_V3_PS_AUTO_SHUTDOWN_EN                      BIT(24)
#define BIT_PMU_APB_PD_V3_PS_PWR_ON_DLY(x)                         (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_V3_PS_PWR_ON_SEQ_DLY(x)                     (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_V3_PS_ISO_ON_DLY(x)                         (((x) & 0xFF))

/* REG_PMU_APB_PD_V3_LCE_CFG */

#define BIT_PMU_APB_PD_V3_LCE_FORCE_SHUTDOWN                       BIT(25)
#define BIT_PMU_APB_PD_V3_LCE_AUTO_SHUTDOWN_EN                     BIT(24)
#define BIT_PMU_APB_PD_V3_LCE_PWR_ON_DLY(x)                        (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_V3_LCE_PWR_ON_SEQ_DLY(x)                    (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_V3_LCE_ISO_ON_DLY(x)                        (((x) & 0xFF))

/* REG_PMU_APB_PD_V3_DPFEC_CFG */

#define BIT_PMU_APB_PD_V3_DPFEC_FORCE_SHUTDOWN                     BIT(25)
#define BIT_PMU_APB_PD_V3_DPFEC_AUTO_SHUTDOWN_EN                   BIT(24)
#define BIT_PMU_APB_PD_V3_DPFEC_PWR_ON_DLY(x)                      (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_V3_DPFEC_PWR_ON_SEQ_DLY(x)                  (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_V3_DPFEC_ISO_ON_DLY(x)                      (((x) & 0xFF))

/* REG_PMU_APB_PD_NRCP_DSP_0_CFG */

#define BIT_PMU_APB_PD_NRCP_DSP_0_PD_SEL                           BIT(27)
#define BIT_PMU_APB_PD_NRCP_DSP_0_FORCE_SHUTDOWN                   BIT(25)
#define BIT_PMU_APB_PD_NRCP_DSP_0_AUTO_SHUTDOWN_EN                 BIT(24)
#define BIT_PMU_APB_PD_NRCP_DSP_0_PWR_ON_DLY(x)                    (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_NRCP_DSP_0_PWR_ON_SEQ_DLY(x)                (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_NRCP_DSP_0_ISO_ON_DLY(x)                    (((x) & 0xFF))

/* REG_PMU_APB_PD_NRCP_DSP_1_CFG */

#define BIT_PMU_APB_PD_NRCP_DSP_1_PD_SEL                           BIT(27)
#define BIT_PMU_APB_PD_NRCP_DSP_1_FORCE_SHUTDOWN                   BIT(25)
#define BIT_PMU_APB_PD_NRCP_DSP_1_AUTO_SHUTDOWN_EN                 BIT(24)
#define BIT_PMU_APB_PD_NRCP_DSP_1_PWR_ON_DLY(x)                    (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_NRCP_DSP_1_PWR_ON_SEQ_DLY(x)                (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_NRCP_DSP_1_ISO_ON_DLY(x)                    (((x) & 0xFF))

/* REG_PMU_APB_PD_V3_WCE_CFG */

#define BIT_PMU_APB_PD_V3_WCE_FORCE_SHUTDOWN                       BIT(25)
#define BIT_PMU_APB_PD_V3_WCE_AUTO_SHUTDOWN_EN                     BIT(24)
#define BIT_PMU_APB_PD_V3_WCE_PWR_ON_DLY(x)                        (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_V3_WCE_PWR_ON_SEQ_DLY(x)                    (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_V3_WCE_ISO_ON_DLY(x)                        (((x) & 0xFF))

/* REG_PMU_APB_PD_V3_PHY_CFG */

#define BIT_PMU_APB_PD_V3_PHY_PD_SEL                               BIT(27)
#define BIT_PMU_APB_PD_V3_PHY_DBG_SHUTDOWN_EN                      BIT(26)
#define BIT_PMU_APB_PD_V3_PHY_FORCE_SHUTDOWN                       BIT(25)
#define BIT_PMU_APB_PD_V3_PHY_AUTO_SHUTDOWN_EN                     BIT(24)
#define BIT_PMU_APB_PD_V3_PHY_PWR_ON_DLY(x)                        (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_V3_PHY_PWR_ON_SEQ_DLY(x)                    (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_V3_PHY_ISO_ON_DLY(x)                        (((x) & 0xFF))

/* REG_PMU_APB_PD_V3_LWPROC_CFG */

#define BIT_PMU_APB_PD_V3_LWPROC_FORCE_SHUTDOWN                    BIT(25)
#define BIT_PMU_APB_PD_V3_LWPROC_AUTO_SHUTDOWN_EN                  BIT(24)
#define BIT_PMU_APB_PD_V3_LWPROC_PWR_ON_DLY(x)                     (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_V3_LWPROC_PWR_ON_SEQ_DLY(x)                 (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_V3_LWPROC_ISO_ON_DLY(x)                     (((x) & 0xFF))

/* REG_PMU_APB_PD_V3_TD_CFG */

#define BIT_PMU_APB_PD_V3_TD_FORCE_SHUTDOWN                        BIT(25)
#define BIT_PMU_APB_PD_V3_TD_AUTO_SHUTDOWN_EN                      BIT(24)
#define BIT_PMU_APB_PD_V3_TD_PWR_ON_DLY(x)                         (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_V3_TD_PWR_ON_SEQ_DLY(x)                     (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_V3_TD_ISO_ON_DLY(x)                         (((x) & 0xFF))

/* REG_PMU_APB_PD_V3_MODEM_SYS_CFG */

#define BIT_PMU_APB_PD_V3_MODEM_SYS_FORCE_SHUTDOWN                 BIT(25)
#define BIT_PMU_APB_PD_V3_MODEM_SYS_AUTO_SHUTDOWN_EN               BIT(24)
#define BIT_PMU_APB_PD_V3_MODEM_SYS_PWR_ON_DLY(x)                  (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_V3_MODEM_SYS_PWR_ON_SEQ_DLY(x)              (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_V3_MODEM_SYS_ISO_ON_DLY(x)                  (((x) & 0xFF))

/* REG_PMU_APB_PD_PSCP_SYS_CFG */

#define BIT_PMU_APB_PD_PSCP_SYS_DBG_SHUTDOWN_EN                    BIT(26)
#define BIT_PMU_APB_PD_PSCP_SYS_FORCE_SHUTDOWN                     BIT(25)
#define BIT_PMU_APB_PD_PSCP_SYS_AUTO_SHUTDOWN_EN                   BIT(24)
#define BIT_PMU_APB_PD_PSCP_SYS_PWR_ON_DLY(x)                      (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_PSCP_SYS_PWR_ON_SEQ_DLY(x)                  (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_PSCP_SYS_ISO_ON_DLY(x)                      (((x) & 0xFF))

/* REG_PMU_APB_PD_AUDCP_AUDDSP_CFG */

#define BIT_PMU_APB_PD_AUDCP_AUDDSP_PD_SEL                         BIT(27)
#define BIT_PMU_APB_PD_AUDCP_AUDDSP_FORCE_SHUTDOWN                 BIT(25)
#define BIT_PMU_APB_PD_AUDCP_AUDDSP_AUTO_SHUTDOWN_EN               BIT(24)
#define BIT_PMU_APB_PD_AUDCP_AUDDSP_PWR_ON_DLY(x)                  (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_AUDCP_AUDDSP_PWR_ON_SEQ_DLY(x)              (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_AUDCP_AUDDSP_ISO_ON_DLY(x)                  (((x) & 0xFF))

/* REG_PMU_APB_PD_AUDCP_SYS_CFG */

#define BIT_PMU_APB_PD_AUDCP_SYS_FORCE_SHUTDOWN                    BIT(25)
#define BIT_PMU_APB_PD_AUDCP_SYS_AUTO_SHUTDOWN_EN                  BIT(24)
#define BIT_PMU_APB_PD_AUDCP_SYS_PWR_ON_DLY(x)                     (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_AUDCP_SYS_PWR_ON_SEQ_DLY(x)                 (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_AUDCP_SYS_ISO_ON_DLY(x)                     (((x) & 0xFF))

/* REG_PMU_APB_PUBCP_FRC_STOP_REQ_FOR_WTL */

#define BIT_PMU_APB_PUBCP_FRC_STOP_REQ_FOR_WTL                     BIT(0)

/* REG_PMU_APB_PD_PUB_SYS_CFG */

#define BIT_PMU_APB_PD_PUB_SYS_FORCE_SHUTDOWN                      BIT(25)
#define BIT_PMU_APB_PD_PUB_SYS_AUTO_SHUTDOWN_EN                    BIT(24)
#define BIT_PMU_APB_PD_PUB_SYS_PWR_ON_DLY(x)                       (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_PUB_SYS_PWR_ON_SEQ_DLY(x)                   (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_PUB_SYS_ISO_ON_DLY(x)                       (((x) & 0xFF))

/* REG_PMU_APB_AP_WAKEUP_POR_CFG */

#define BIT_PMU_APB_AP_WAKEUP_POR_N                                BIT(0)

/* REG_PMU_APB_XTL_WAIT_CNT */

#define BIT_PMU_APB_XTLBUF1_WAIT_CNT(x)                            (((x) & 0xFF) << 24)
#define BIT_PMU_APB_XTLBUF0_WAIT_CNT(x)                            (((x) & 0xFF) << 16)
#define BIT_PMU_APB_XTL1_WAIT_CNT(x)                               (((x) & 0xFF) << 8)
#define BIT_PMU_APB_XTL0_WAIT_CNT(x)                               (((x) & 0xFF))

/* REG_PMU_APB_PLL_WAIT_CNT0 */

#define BIT_PMU_APB_PCIEPLL_H_WAIT_CNT(x)                          (((x) & 0xFF) << 24)
#define BIT_PMU_APB_R8PLL_WAIT_CNT(x)                              (((x) & 0xFF) << 16)
#define BIT_PMU_APB_MPLL1_WAIT_CNT(x)                              (((x) & 0xFF) << 8)
#define BIT_PMU_APB_MPLL0_WAIT_CNT(x)                              (((x) & 0xFF))

/* REG_PMU_APB_PLL_WAIT_CNT1 */

#define BIT_PMU_APB_V3PLL_WAIT_CNT(x)                              (((x) & 0xFF) << 24)
#define BIT_PMU_APB_NRPLL_WAIT_CNT(x)                              (((x) & 0xFF) << 16)
#define BIT_PMU_APB_DPLL1_WAIT_CNT(x)                              (((x) & 0xFF) << 8)
#define BIT_PMU_APB_DPLL0_WAIT_CNT(x)                              (((x) & 0xFF))

/* REG_PMU_APB_PLL_WAIT_CNT2 */

#define BIT_PMU_APB_NR_RPLL_WAIT_CNT(x)                            (((x) & 0xFF) << 24)
#define BIT_PMU_APB_V3_RPLL_WAIT_CNT(x)                            (((x) & 0xFF) << 16)
#define BIT_PMU_APB_NR_CPUPLL_WAIT_CNT(x)                          (((x) & 0xFF) << 8)
#define BIT_PMU_APB_NR_DSPPLL_WAIT_CNT(x)                          (((x) & 0xFF))

/* REG_PMU_APB_XTL0_REL_CFG */

#define BIT_PMU_APB_XTL0_IPA_SEL                                   BIT(10)
#define BIT_PMU_APB_XTL0_FRC_OFF                                   BIT(9)
#define BIT_PMU_APB_XTL0_FRC_ON                                    BIT(8)
#define BIT_PMU_APB_XTL0_TOP_DVFS_SEL                              BIT(7)
#define BIT_PMU_APB_XTL0_NRCP_SEL                                  BIT(6)
#define BIT_PMU_APB_XTL0_SP_SYS_SEL                                BIT(5)
#define BIT_PMU_APB_XTL0_PUB_SYS_SEL                               BIT(4)
#define BIT_PMU_APB_XTL0_AUDCP_SEL                                 BIT(3)
#define BIT_PMU_APB_XTL0_PSCP_SEL                                  BIT(2)
#define BIT_PMU_APB_XTL0_V3_MODEM_SEL                              BIT(1)
#define BIT_PMU_APB_XTL0_AP_SEL                                    BIT(0)

/* REG_PMU_APB_XTL1_REL_CFG */

#define BIT_PMU_APB_XTL1_IPA_SEL                                   BIT(10)
#define BIT_PMU_APB_XTL1_FRC_OFF                                   BIT(9)
#define BIT_PMU_APB_XTL1_FRC_ON                                    BIT(8)
#define BIT_PMU_APB_XTL1_TOP_DVFS_SEL                              BIT(7)
#define BIT_PMU_APB_XTL1_NRCP_SEL                                  BIT(6)
#define BIT_PMU_APB_XTL1_SP_SYS_SEL                                BIT(5)
#define BIT_PMU_APB_XTL1_PUB_SYS_SEL                               BIT(4)
#define BIT_PMU_APB_XTL1_AUDCP_SEL                                 BIT(3)
#define BIT_PMU_APB_XTL1_PSCP_SEL                                  BIT(2)
#define BIT_PMU_APB_XTL1_V3_MODEM_SEL                              BIT(1)
#define BIT_PMU_APB_XTL1_AP_SEL                                    BIT(0)

/* REG_PMU_APB_NR_RPLL_REL_CFG */

#define BIT_PMU_APB_NR_RPLL_IPA_SEL                                BIT(11)
#define BIT_PMU_APB_NR_RPLL_REF_SEL                                BIT(10)
#define BIT_PMU_APB_NR_RPLL_FRC_OFF                                BIT(9)
#define BIT_PMU_APB_NR_RPLL_FRC_ON                                 BIT(8)
#define BIT_PMU_APB_NR_RPLL_TOP_DVFS_SEL                           BIT(7)
#define BIT_PMU_APB_NR_RPLL_NRCP_SEL                               BIT(6)
#define BIT_PMU_APB_NR_RPLL_SP_SYS_SEL                             BIT(5)
#define BIT_PMU_APB_NR_RPLL_PUB_SYS_SEL                            BIT(4)
#define BIT_PMU_APB_NR_RPLL_AUDCP_SEL                              BIT(3)
#define BIT_PMU_APB_NR_RPLL_PSCP_SEL                               BIT(2)
#define BIT_PMU_APB_NR_RPLL_V3_MODEM_SEL                           BIT(1)
#define BIT_PMU_APB_NR_RPLL_AP_SEL                                 BIT(0)

/* REG_PMU_APB_XTLBUF0_REL_CFG */

#define BIT_PMU_APB_XTLBUF0_IPA_SEL                                BIT(10)
#define BIT_PMU_APB_XTLBUF0_FRC_OFF                                BIT(9)
#define BIT_PMU_APB_XTLBUF0_FRC_ON                                 BIT(8)
#define BIT_PMU_APB_XTLBUF0_TOP_DVFS_SEL                           BIT(7)
#define BIT_PMU_APB_XTLBUF0_NRCP_SEL                               BIT(6)
#define BIT_PMU_APB_XTLBUF0_SP_SYS_SEL                             BIT(5)
#define BIT_PMU_APB_XTLBUF0_PUB_SYS_SEL                            BIT(4)
#define BIT_PMU_APB_XTLBUF0_AUDCP_SEL                              BIT(3)
#define BIT_PMU_APB_XTLBUF0_PSCP_SEL                               BIT(2)
#define BIT_PMU_APB_XTLBUF0_V3_MODEM_SEL                           BIT(1)
#define BIT_PMU_APB_XTLBUF0_AP_SEL                                 BIT(0)

/* REG_PMU_APB_XTLBUF1_REL_CFG */

#define BIT_PMU_APB_XTLBUF1_IPA_SEL                                BIT(10)
#define BIT_PMU_APB_XTLBUF1_FRC_OFF                                BIT(9)
#define BIT_PMU_APB_XTLBUF1_FRC_ON                                 BIT(8)
#define BIT_PMU_APB_XTLBUF1_TOP_DVFS_SEL                           BIT(7)
#define BIT_PMU_APB_XTLBUF1_NRCP_SEL                               BIT(6)
#define BIT_PMU_APB_XTLBUF1_SP_SYS_SEL                             BIT(5)
#define BIT_PMU_APB_XTLBUF1_PUB_SYS_SEL                            BIT(4)
#define BIT_PMU_APB_XTLBUF1_AUDCP_SEL                              BIT(3)
#define BIT_PMU_APB_XTLBUF1_PSCP_SEL                               BIT(2)
#define BIT_PMU_APB_XTLBUF1_V3_MODEM_SEL                           BIT(1)
#define BIT_PMU_APB_XTLBUF1_AP_SEL                                 BIT(0)

/* REG_PMU_APB_DPLL0_REL_CFG */

#define BIT_PMU_APB_DPLL0_IPA_SEL                                  BIT(11)
#define BIT_PMU_APB_DPLL0_REF_SEL                                  BIT(10)
#define BIT_PMU_APB_DPLL0_FRC_OFF                                  BIT(9)
#define BIT_PMU_APB_DPLL0_FRC_ON                                   BIT(8)
#define BIT_PMU_APB_DPLL0_TOP_DVFS_SEL                             BIT(7)
#define BIT_PMU_APB_DPLL0_NRCP_SEL                                 BIT(6)
#define BIT_PMU_APB_DPLL0_SP_SYS_SEL                               BIT(5)
#define BIT_PMU_APB_DPLL0_PUB_SYS_SEL                              BIT(4)
#define BIT_PMU_APB_DPLL0_AUDCP_SEL                                BIT(3)
#define BIT_PMU_APB_DPLL0_PSCP_SEL                                 BIT(2)
#define BIT_PMU_APB_DPLL0_V3_MODEM_SEL                             BIT(1)
#define BIT_PMU_APB_DPLL0_AP_SEL                                   BIT(0)

/* REG_PMU_APB_DPLL1_REL_CFG */

#define BIT_PMU_APB_DPLL1_IPA_SEL                                  BIT(11)
#define BIT_PMU_APB_DPLL1_REF_SEL                                  BIT(10)
#define BIT_PMU_APB_DPLL1_FRC_OFF                                  BIT(9)
#define BIT_PMU_APB_DPLL1_FRC_ON                                   BIT(8)
#define BIT_PMU_APB_DPLL1_TOP_DVFS_SEL                             BIT(7)
#define BIT_PMU_APB_DPLL1_NRCP_SEL                                 BIT(6)
#define BIT_PMU_APB_DPLL1_SP_SYS_SEL                               BIT(5)
#define BIT_PMU_APB_DPLL1_PUB_SYS_SEL                              BIT(4)
#define BIT_PMU_APB_DPLL1_AUDCP_SEL                                BIT(3)
#define BIT_PMU_APB_DPLL1_PSCP_SEL                                 BIT(2)
#define BIT_PMU_APB_DPLL1_V3_MODEM_SEL                             BIT(1)
#define BIT_PMU_APB_DPLL1_AP_SEL                                   BIT(0)

/* REG_PMU_APB_V3PLL_REL_CFG */

#define BIT_PMU_APB_V3PLL_IPA_SEL                                  BIT(12)
#define BIT_PMU_APB_V3PLL_REF_SEL(x)                               (((x) & 0x3) << 10)
#define BIT_PMU_APB_V3PLL_FRC_OFF                                  BIT(9)
#define BIT_PMU_APB_V3PLL_FRC_ON                                   BIT(8)
#define BIT_PMU_APB_V3PLL_TOP_DVFS_SEL                             BIT(7)
#define BIT_PMU_APB_V3PLL_NRCP_SEL                                 BIT(6)
#define BIT_PMU_APB_V3PLL_SP_SYS_SEL                               BIT(5)
#define BIT_PMU_APB_V3PLL_PUB_SYS_SEL                              BIT(4)
#define BIT_PMU_APB_V3PLL_AUDCP_SEL                                BIT(3)
#define BIT_PMU_APB_V3PLL_PSCP_SEL                                 BIT(2)
#define BIT_PMU_APB_V3PLL_V3_MODEM_SEL                             BIT(1)
#define BIT_PMU_APB_V3PLL_AP_SEL                                   BIT(0)

/* REG_PMU_APB_NRPLL_REL_CFG */

#define BIT_PMU_APB_NRPLL_IPA_SEL                                  BIT(12)
#define BIT_PMU_APB_NRPLL_REF_SEL(x)                               (((x) & 0x3) << 10)
#define BIT_PMU_APB_NRPLL_FRC_OFF                                  BIT(9)
#define BIT_PMU_APB_NRPLL_FRC_ON                                   BIT(8)
#define BIT_PMU_APB_NRPLL_TOP_DVFS_SEL                             BIT(7)
#define BIT_PMU_APB_NRPLL_NRCP_SEL                                 BIT(6)
#define BIT_PMU_APB_NRPLL_SP_SYS_SEL                               BIT(5)
#define BIT_PMU_APB_NRPLL_PUB_SYS_SEL                              BIT(4)
#define BIT_PMU_APB_NRPLL_AUDCP_SEL                                BIT(3)
#define BIT_PMU_APB_NRPLL_PSCP_SEL                                 BIT(2)
#define BIT_PMU_APB_NRPLL_V3_MODEM_SEL                             BIT(1)
#define BIT_PMU_APB_NRPLL_AP_SEL                                   BIT(0)

/* REG_PMU_APB_V3_RPLL_REL_CFG */

#define BIT_PMU_APB_V3_RPLL_IPA_SEL                                BIT(11)
#define BIT_PMU_APB_V3_RPLL_REF_SEL                                BIT(10)
#define BIT_PMU_APB_V3_RPLL_FRC_OFF                                BIT(9)
#define BIT_PMU_APB_V3_RPLL_FRC_ON                                 BIT(8)
#define BIT_PMU_APB_V3_RPLL_TOP_DVFS_SEL                           BIT(7)
#define BIT_PMU_APB_V3_RPLL_NRCP_SEL                               BIT(6)
#define BIT_PMU_APB_V3_RPLL_SP_SYS_SEL                             BIT(5)
#define BIT_PMU_APB_V3_RPLL_PUB_SYS_SEL                            BIT(4)
#define BIT_PMU_APB_V3_RPLL_AUDCP_SEL                              BIT(3)
#define BIT_PMU_APB_V3_RPLL_PSCP_SEL                               BIT(2)
#define BIT_PMU_APB_V3_RPLL_V3_MODEM_SEL                           BIT(1)
#define BIT_PMU_APB_V3_RPLL_AP_SEL                                 BIT(0)

/* REG_PMU_APB_R8PLL_REL_CFG */

#define BIT_PMU_APB_R8PLL_IPA_SEL                                  BIT(12)
#define BIT_PMU_APB_R8PLL_REF_SEL                                  BIT(10)
#define BIT_PMU_APB_R8PLL_FRC_OFF                                  BIT(9)
#define BIT_PMU_APB_R8PLL_FRC_ON                                   BIT(8)
#define BIT_PMU_APB_R8PLL_TOP_DVFS_SEL                             BIT(7)
#define BIT_PMU_APB_R8PLL_NRCP_SEL                                 BIT(6)
#define BIT_PMU_APB_R8PLL_SP_SYS_SEL                               BIT(5)
#define BIT_PMU_APB_R8PLL_PUB_SYS_SEL                              BIT(4)
#define BIT_PMU_APB_R8PLL_AUDCP_SEL                                BIT(3)
#define BIT_PMU_APB_R8PLL_PSCP_SEL                                 BIT(2)
#define BIT_PMU_APB_R8PLL_V3_MODEM_SEL                             BIT(1)
#define BIT_PMU_APB_R8PLL_AP_SEL                                   BIT(0)

/* REG_PMU_APB_CP_SOFT_RST */

#define BIT_PMU_APB_NRCP_SYS_SOFT_RST                              BIT(17)
#define BIT_PMU_APB_AP_VSP_SOFT_RST                                BIT(16)
#define BIT_PMU_APB_NRCP_DSP_1_SOFT_RST                            BIT(15)
#define BIT_PMU_APB_NRCP_DSP_0_SOFT_RST                            BIT(14)
#define BIT_PMU_APB_NRCP_AON_SOFT_RST                              BIT(13)
#define BIT_PMU_APB_V3_MODEM_AON_SOFT_RST                          BIT(12)
#define BIT_PMU_APB_AP_VDSP_SOFT_RST                               BIT(11)
#define BIT_PMU_APB_AUDCP_AUDDSP_SOFT_RST                          BIT(10)
#define BIT_PMU_APB_AUDCP_SYS_SOFT_RST                             BIT(9)
#define BIT_PMU_APB_SP_SYS_SOFT_RST                                BIT(8)
#define BIT_PMU_APB_APCPU_SOFT_RST                                 BIT(7)
#define BIT_PMU_APB_PUB_SOFT_RST                                   BIT(6)
#define BIT_PMU_APB_AP_SOFT_RST                                    BIT(5)
#define BIT_PMU_APB_GPU_SOFT_RST                                   BIT(4)
#define BIT_PMU_APB_V3_MODEM_PHY_SOFT_RST                          BIT(3)
#define BIT_PMU_APB_V3_MODEM_PS_SOFT_RST                           BIT(2)
#define BIT_PMU_APB_PSCP_SOFT_RST                                  BIT(1)
#define BIT_PMU_APB_V3_MODEM_SOFT_RST                              BIT(0)

/* REG_PMU_APB_CP_SLP_STATUS_DBG0 */

#define BIT_PMU_APB_PSCP_DEEP_SLP_DBG(x)                           (((x) & 0xFFFF) << 16)
#define BIT_PMU_APB_V3_MODEM_DEEP_SLP_DBG(x)                       (((x) & 0xFFFF))

/* REG_PMU_APB_XTLBUF_LDO_WAIT_CNT */

#define BIT_PMU_APB_XTLBUF1_LDO_WAIT_CNT(x)                        (((x) & 0xFF) << 8)
#define BIT_PMU_APB_XTLBUF0_LDO_WAIT_CNT(x)                        (((x) & 0xFF))

/* REG_PMU_APB_PUB_SYS_AUTO_LIGHT_SLEEP_ENABLE */

#define BIT_PMU_APB_PUB_SYS_AUTO_LIGHT_SLEEP_ENABLE(x)             (((x) & 0xFFFFFFFF))

/* REG_PMU_APB_SLEEP_CTRL */

#define BIT_PMU_APB_IPA_DEEP_SLEEP                                 BIT(7)
#define BIT_PMU_APB_SP_SYS_DEEP_SLEEP                              BIT(6)
#define BIT_PMU_APB_AUDCP_DEEP_SLEEP                               BIT(5)
#define BIT_PMU_APB_PUB_SYS_DEEP_SLEEP                             BIT(4)
#define BIT_PMU_APB_NRCP_DEEP_SLEEP                                BIT(3)
#define BIT_PMU_APB_PSCP_DEEP_SLEEP                                BIT(2)
#define BIT_PMU_APB_V3_MODEM_DEEP_SLEEP                            BIT(1)
#define BIT_PMU_APB_AP_DEEP_SLEEP                                  BIT(0)

/* REG_PMU_APB_DDR_SLEEP_CTRL */

#define BIT_PMU_APB_PUB_SYS_AUTO_DEEP_SLEEP_ENABLE                 BIT(20)
#define BIT_PMU_APB_DDR_SLEEP_DISABLE_ACK                          BIT(19)
#define BIT_PMU_APB_DDR_SLEEP_DISABLE_ACK_BYP                      BIT(18)
#define BIT_PMU_APB_DDR_SLEEP_DISABLE                              BIT(17)
#define BIT_PMU_APB_BUSY_TRANSFER_HWDATA_SEL                       BIT(16)
#define BIT_PMU_APB_DDR_PUBL_APB_SOFT_RST                          BIT(12)
#define BIT_PMU_APB_DDR_UMCTL_APB_SOFT_RST                         BIT(11)
#define BIT_PMU_APB_DDR_PUBL_SOFT_RST                              BIT(10)
#define BIT_PMU_APB_DDR_PHY_SOFT_RST                               BIT(8)
#define BIT_PMU_APB_DDR_PHY_AUTO_GATE_EN                           BIT(6)
#define BIT_PMU_APB_DDR_PUBL_AUTO_GATE_EN                          BIT(5)
#define BIT_PMU_APB_DDR_UMCTL_AUTO_GATE_EN                         BIT(4)
#define BIT_PMU_APB_DDR_PHY_EB                                     BIT(2)
#define BIT_PMU_APB_DDR_UMCTL_EB                                   BIT(1)
#define BIT_PMU_APB_DDR_PUBL_EB                                    BIT(0)

/* REG_PMU_APB_SLEEP_STATUS */

#define BIT_PMU_APB_IPA_SLP_STATUS(x)                              (((x) & 0xF) << 24)
#define BIT_PMU_APB_SP_SYS_SLP_STATUS(x)                           (((x) & 0xF) << 20)
#define BIT_PMU_APB_NRCP_SLP_STATUS(x)                             (((x) & 0xF) << 16)
#define BIT_PMU_APB_AUDCP_SLP_STATUS(x)                            (((x) & 0xF) << 12)
#define BIT_PMU_APB_PSCP_SLP_STATUS(x)                             (((x) & 0xF) << 8)
#define BIT_PMU_APB_V3_MODEM_SLP_STATUS(x)                         (((x) & 0xF) << 4)
#define BIT_PMU_APB_AP_SLP_STATUS(x)                               (((x) & 0xF))

/* REG_PMU_APB_PUB_SYS_SLEEP_BYPASS_CFG */

#define BIT_PMU_APB_PUB_PD_VOL_DOWN_ENA                            BIT(4)
#define BIT_PMU_APB_PUB_SYS_VOL_ADJ_ENA                            BIT(3)
#define BIT_PMU_APB_PUB_SYS_SELF_REFRESH_FLAG_BYPASS               BIT(2)
#define BIT_PMU_APB_PUB_SYS_PWR_PD_ACK_BYPASS                      BIT(1)
#define BIT_PMU_APB_PUB_SYS_DEEP_SLEEP_LOCK_ACK_BYPASS             BIT(0)

/* REG_PMU_APB_PUB_SYS_DEEP_SLEEP_POLL0 */

#define BIT_PMU_APB_IPA_PUB_SYS_DEEP_SLEEP_POLL(x)                 (((x) & 0xFF) << 16)
#define BIT_PMU_APB_NRCP_PUB_SYS_DEEP_SLEEP_POLL(x)                (((x) & 0xFF) << 8)
#define BIT_PMU_APB_AUDCP_PUB_SYS_DEEP_SLEEP_POLL(x)               (((x) & 0xFF))

/* REG_PMU_APB_PUB_SYS_DEEP_SLEEP_POLL1 */

#define BIT_PMU_APB_AON_PUB_SYS_DEEP_SLEEP_POLL(x)                 (((x) & 0xFF) << 24)
#define BIT_PMU_APB_PSCP_PUB_SYS_DEEP_SLEEP_POLL(x)                (((x) & 0xFF) << 16)
#define BIT_PMU_APB_AP_PUB_SYS_DEEP_SLEEP_POLL(x)                  (((x) & 0xFF) << 8)
#define BIT_PMU_APB_V3_MODEM_PUB_SYS_DEEP_SLEEP_POLL(x)            (((x) & 0xFF))

/* REG_PMU_APB_DDR_CHN_SLEEP_CTRL0 */

#define BIT_PMU_APB_DDR_CTRL_AXI_LP_EN                             BIT(31)
#define BIT_PMU_APB_DDR_CTRL_CGM_SEL                               BIT(30)
#define BIT_PMU_APB_DDR_CHN9_AXI_LP_EN                             BIT(25)
#define BIT_PMU_APB_DDR_CHN8_AXI_LP_EN                             BIT(24)
#define BIT_PMU_APB_DDR_CHN7_AXI_LP_EN                             BIT(23)
#define BIT_PMU_APB_DDR_CHN6_AXI_LP_EN                             BIT(22)
#define BIT_PMU_APB_DDR_CHN5_AXI_LP_EN                             BIT(21)
#define BIT_PMU_APB_DDR_CHN4_AXI_LP_EN                             BIT(20)
#define BIT_PMU_APB_DDR_CHN3_AXI_LP_EN                             BIT(19)
#define BIT_PMU_APB_DDR_CHN2_AXI_LP_EN                             BIT(18)
#define BIT_PMU_APB_DDR_CHN1_AXI_LP_EN                             BIT(17)
#define BIT_PMU_APB_DDR_CHN0_AXI_LP_EN                             BIT(16)
#define BIT_PMU_APB_DDR_CHN9_CGM_SEL                               BIT(9)
#define BIT_PMU_APB_DDR_CHN8_CGM_SEL                               BIT(8)
#define BIT_PMU_APB_DDR_CHN7_CGM_SEL                               BIT(7)
#define BIT_PMU_APB_DDR_CHN6_CGM_SEL                               BIT(6)
#define BIT_PMU_APB_DDR_CHN5_CGM_SEL                               BIT(5)
#define BIT_PMU_APB_DDR_CHN4_CGM_SEL                               BIT(4)
#define BIT_PMU_APB_DDR_CHN3_CGM_SEL                               BIT(3)
#define BIT_PMU_APB_DDR_CHN2_CGM_SEL                               BIT(2)
#define BIT_PMU_APB_DDR_CHN1_CGM_SEL                               BIT(1)
#define BIT_PMU_APB_DDR_CHN0_CGM_SEL                               BIT(0)

/* REG_PMU_APB_DDR_CHN_SLEEP_CTRL1 */

#define BIT_PMU_APB_DDR_CHN9_AXI_STOP_SEL                          BIT(9)
#define BIT_PMU_APB_DDR_CHN8_AXI_STOP_SEL                          BIT(8)
#define BIT_PMU_APB_DDR_CHN7_AXI_STOP_SEL                          BIT(7)
#define BIT_PMU_APB_DDR_CHN6_AXI_STOP_SEL                          BIT(6)
#define BIT_PMU_APB_DDR_CHN5_AXI_STOP_SEL                          BIT(5)
#define BIT_PMU_APB_DDR_CHN4_AXI_STOP_SEL                          BIT(4)
#define BIT_PMU_APB_DDR_CHN3_AXI_STOP_SEL                          BIT(3)
#define BIT_PMU_APB_DDR_CHN2_AXI_STOP_SEL                          BIT(2)
#define BIT_PMU_APB_DDR_CHN1_AXI_STOP_SEL                          BIT(1)
#define BIT_PMU_APB_DDR_CHN0_AXI_STOP_SEL                          BIT(0)

/* REG_PMU_APB_DDR_OP_MODE_CFG */

#define BIT_PMU_APB_DDR_PUB_RET_EN                                 BIT(27)
#define BIT_PMU_APB_DDR_PHY_ISO_RST_EN                             BIT(26)
#define BIT_PMU_APB_DDR_UMCTL_RET_EN                               BIT(25)
#define BIT_PMU_APB_DDR_PHY_CHB_AUTO_RET_EN                        BIT(24)
#define BIT_PMU_APB_DDR_PHY_CHA_AUTO_RET_EN                        BIT(23)

/* REG_PMU_APB_DDR_PHY_RET_CFG */

#define BIT_PMU_APB_DDR_UMCTL_SOFT_RST                             BIT(16)
#define BIT_PMU_APB_DDR_PHY_CHB_CKE_RET_EN                         BIT(1)
#define BIT_PMU_APB_DDR_PHY_CHA_CKE_RET_EN                         BIT(0)

/* REG_PMU_APB_CLK26M_SEL_CFG */

#define BIT_PMU_APB_AON_RC_4M_SEL                                  BIT(8)
#define BIT_PMU_APB_NRCP_26M_SEL                                   BIT(6)
#define BIT_PMU_APB_PUB_26M_SEL                                    BIT(5)
#define BIT_PMU_APB_AON_26M_SEL                                    BIT(4)
#define BIT_PMU_APB_AUDCP_26M_SEL                                  BIT(3)
#define BIT_PMU_APB_PSCP_26M_SEL                                   BIT(2)
#define BIT_PMU_APB_V3_MODEM_26M_SEL                               BIT(1)
#define BIT_PMU_APB_AP_26M_SEL                                     BIT(0)

/* REG_PMU_APB_BISR_DONE_STATUS */

#define BIT_PMU_APB_PD_IPA_SYS_BISR_DONE                           BIT(30)
#define BIT_PMU_APB_PD_ESE_SYS_BISR_DONE                           BIT(29)
#define BIT_PMU_APB_PD_APCPU_C7_BISR_DONE                          BIT(28)
#define BIT_PMU_APB_PD_APCPU_C6_BISR_DONE                          BIT(27)
#define BIT_PMU_APB_PD_APCPU_C5_BISR_DONE                          BIT(26)
#define BIT_PMU_APB_PD_APCPU_C4_BISR_DONE                          BIT(25)
#define BIT_PMU_APB_PD_NRCP_DSP_1_BISR_DONE                        BIT(23)
#define BIT_PMU_APB_PD_NRCP_DSP_0_BISR_DONE                        BIT(22)
#define BIT_PMU_APB_PD_NRCP_UL_BISR_DONE                           BIT(21)
#define BIT_PMU_APB_PD_NRCP_DL_BISR_DONE                           BIT(20)
#define BIT_PMU_APB_PD_V3_TD_BISR_DONE                             BIT(19)
#define BIT_PMU_APB_PD_AON_MEM_BISR_DONE                           BIT(18)
#define BIT_PMU_APB_PD_PSCP_SYS_BISR_DONE                          BIT(17)
#define BIT_PMU_APB_PD_V3_MODEM_SYS_BISR_DONE                      BIT(16)
#define BIT_PMU_APB_PD_V3_PS_BISR_DONE                             BIT(15)
#define BIT_PMU_APB_PD_V3_PHY_BISR_DONE                            BIT(14)
#define BIT_PMU_APB_PD_V3_LWPROC_BISR_DONE                         BIT(13)
#define BIT_PMU_APB_PD_V3_WCE_BISR_DONE                            BIT(12)
#define BIT_PMU_APB_PD_V3_DPFEC_BISR_DONE                          BIT(11)
#define BIT_PMU_APB_PD_V3_LCE_BISR_DONE                            BIT(10)
#define BIT_PMU_APB_PD_AUDCP_AUDDSP_BISR_DONE                      BIT(9)
#define BIT_PMU_APB_PD_AUDCP_SYS_BISR_DONE                         BIT(8)
#define BIT_PMU_APB_PD_NRCP_SYNC_BISR_DONE                         BIT(7)
#define BIT_PMU_APB_PD_NRCP_SYS_BISR_DONE                          BIT(6)
#define BIT_PMU_APB_PD_AP_SYS_BISR_DONE                            BIT(5)
#define BIT_PMU_APB_PD_APCPU_TOP_BISR_DONE                         BIT(4)
#define BIT_PMU_APB_PD_APCPU_C3_BISR_DONE                          BIT(3)
#define BIT_PMU_APB_PD_APCPU_C2_BISR_DONE                          BIT(2)
#define BIT_PMU_APB_PD_APCPU_C1_BISR_DONE                          BIT(1)
#define BIT_PMU_APB_PD_APCPU_C0_BISR_DONE                          BIT(0)

/* REG_PMU_APB_BISR_BUSY_STATUS */

#define BIT_PMU_APB_PD_IPA_SYS_BISR_BUSY                           BIT(30)
#define BIT_PMU_APB_PD_ESE_SYS_BISR_BUSY                           BIT(29)
#define BIT_PMU_APB_PD_APCPU_C7_BISR_BUSY                          BIT(28)
#define BIT_PMU_APB_PD_APCPU_C6_BISR_BUSY                          BIT(27)
#define BIT_PMU_APB_PD_APCPU_C5_BISR_BUSY                          BIT(26)
#define BIT_PMU_APB_PD_APCPU_C4_BISR_BUSY                          BIT(25)
#define BIT_PMU_APB_PD_NRCP_DSP_1_BISR_BUSY                        BIT(23)
#define BIT_PMU_APB_PD_NRCP_DSP_0_BISR_BUSY                        BIT(22)
#define BIT_PMU_APB_PD_NRCP_UL_BISR_BUSY                           BIT(21)
#define BIT_PMU_APB_PD_NRCP_DL_BISR_BUSY                           BIT(20)
#define BIT_PMU_APB_PD_V3_TD_BISR_BUSY                             BIT(19)
#define BIT_PMU_APB_PD_AON_MEM_BISR_BUSY                           BIT(18)
#define BIT_PMU_APB_PD_PSCP_SYS_BISR_BUSY                          BIT(17)
#define BIT_PMU_APB_PD_V3_MODEM_SYS_BISR_BUSY                      BIT(16)
#define BIT_PMU_APB_PD_V3_PS_BISR_BUSY                             BIT(15)
#define BIT_PMU_APB_PD_V3_PHY_BISR_BUSY                            BIT(14)
#define BIT_PMU_APB_PD_V3_LWPROC_BISR_BUSY                         BIT(13)
#define BIT_PMU_APB_PD_V3_WCE_BISR_BUSY                            BIT(12)
#define BIT_PMU_APB_PD_V3_DPFEC_BISR_BUSY                          BIT(11)
#define BIT_PMU_APB_PD_V3_LCE_BISR_BUSY                            BIT(10)
#define BIT_PMU_APB_PD_AUDCP_AUDDSP_BISR_BUSY                      BIT(9)
#define BIT_PMU_APB_PD_AUDCP_SYS_BISR_BUSY                         BIT(8)
#define BIT_PMU_APB_PD_NRCP_SYNC_BISR_BUSY                         BIT(7)
#define BIT_PMU_APB_PD_NRCP_SYS_BISR_BUSY                          BIT(6)
#define BIT_PMU_APB_PD_AP_SYS_BISR_BUSY                            BIT(5)
#define BIT_PMU_APB_PD_APCPU_TOP_BISR_BUSY                         BIT(4)
#define BIT_PMU_APB_PD_APCPU_C3_BISR_BUSY                          BIT(3)
#define BIT_PMU_APB_PD_APCPU_C2_BISR_BUSY                          BIT(2)
#define BIT_PMU_APB_PD_APCPU_C1_BISR_BUSY                          BIT(1)
#define BIT_PMU_APB_PD_APCPU_C0_BISR_BUSY                          BIT(0)

/* REG_PMU_APB_BISR_BYP_CFG */

#define BIT_PMU_APB_PD_IPA_SYS_BISR_FORCE_BYP                      BIT(30)
#define BIT_PMU_APB_PD_ESE_SYS_BISR_FORCE_BYP                      BIT(29)
#define BIT_PMU_APB_PD_APCPU_C7_BISR_FORCE_BYP                     BIT(28)
#define BIT_PMU_APB_PD_APCPU_C6_BISR_FORCE_BYP                     BIT(27)
#define BIT_PMU_APB_PD_APCPU_C5_BISR_FORCE_BYP                     BIT(26)
#define BIT_PMU_APB_PD_APCPU_C4_BISR_FORCE_BYP                     BIT(25)
#define BIT_PMU_APB_PD_NRCP_DSP_1_BISR_FORCE_BYP                   BIT(23)
#define BIT_PMU_APB_PD_NRCP_DSP_0_BISR_FORCE_BYP                   BIT(22)
#define BIT_PMU_APB_PD_NRCP_UL_BISR_FORCE_BYP                      BIT(21)
#define BIT_PMU_APB_PD_NRCP_DL_BISR_FORCE_BYP                      BIT(20)
#define BIT_PMU_APB_PD_V3_TD_BISR_FORCE_BYP                        BIT(19)
#define BIT_PMU_APB_PD_AON_MEM_BISR_FORCE_BYP                      BIT(18)
#define BIT_PMU_APB_PD_PSCP_SYS_BISR_FORCE_BYP                     BIT(17)
#define BIT_PMU_APB_PD_V3_MODEM_SYS_BISR_FORCE_BYP                 BIT(16)
#define BIT_PMU_APB_PD_V3_PS_BISR_FORCE_BYP                        BIT(15)
#define BIT_PMU_APB_PD_V3_PHY_BISR_FORCE_BYP                       BIT(14)
#define BIT_PMU_APB_PD_V3_LWPROC_BISR_FORCE_BYP                    BIT(13)
#define BIT_PMU_APB_PD_V3_WCE_BISR_FORCE_BYP                       BIT(12)
#define BIT_PMU_APB_PD_V3_DPFEC_BISR_FORCE_BYP                     BIT(11)
#define BIT_PMU_APB_PD_V3_LCE_BISR_FORCE_BYP                       BIT(10)
#define BIT_PMU_APB_PD_AUDCP_AUDDSP_BISR_FORCE_BYP                 BIT(9)
#define BIT_PMU_APB_PD_AUDCP_SYS_BISR_FORCE_BYP                    BIT(8)
#define BIT_PMU_APB_PD_NRCP_SYNC_BISR_FORCE_BYP                    BIT(7)
#define BIT_PMU_APB_PD_NRCP_SYS_BISR_FORCE_BYP                     BIT(6)
#define BIT_PMU_APB_PD_AP_SYS_BISR_FORCE_BYP                       BIT(5)
#define BIT_PMU_APB_PD_APCPU_TOP_BISR_FORCE_BYP                    BIT(4)
#define BIT_PMU_APB_PD_APCPU_C3_BISR_FORCE_BYP                     BIT(3)
#define BIT_PMU_APB_PD_APCPU_C2_BISR_FORCE_BYP                     BIT(2)
#define BIT_PMU_APB_PD_APCPU_C1_BISR_FORCE_BYP                     BIT(1)
#define BIT_PMU_APB_PD_APCPU_C0_BISR_FORCE_BYP                     BIT(0)

/* REG_PMU_APB_BISR_EN_CFG */

#define BIT_PMU_APB_PD_IPA_SYS_BISR_FORCE_EN                       BIT(30)
#define BIT_PMU_APB_PD_ESE_SYS_BISR_FORCE_EN                       BIT(29)
#define BIT_PMU_APB_PD_APCPU_C7_BISR_FORCE_EN                      BIT(28)
#define BIT_PMU_APB_PD_APCPU_C6_BISR_FORCE_EN                      BIT(27)
#define BIT_PMU_APB_PD_APCPU_C5_BISR_FORCE_EN                      BIT(26)
#define BIT_PMU_APB_PD_APCPU_C4_BISR_FORCE_EN                      BIT(25)
#define BIT_PMU_APB_PD_NRCP_DSP_1_BISR_FORCE_EN                    BIT(23)
#define BIT_PMU_APB_PD_NRCP_DSP_0_BISR_FORCE_EN                    BIT(22)
#define BIT_PMU_APB_PD_NRCP_UL_BISR_FORCE_EN                       BIT(21)
#define BIT_PMU_APB_PD_NRCP_DL_BISR_FORCE_EN                       BIT(20)
#define BIT_PMU_APB_PD_V3_TD_BISR_FORCE_EN                         BIT(19)
#define BIT_PMU_APB_PD_AON_MEM_BISR_FORCE_EN                       BIT(18)
#define BIT_PMU_APB_PD_PSCP_SYS_BISR_FORCE_EN                      BIT(17)
#define BIT_PMU_APB_PD_V3_MODEM_SYS_BISR_FORCE_EN                  BIT(16)
#define BIT_PMU_APB_PD_V3_PS_BISR_FORCE_EN                         BIT(15)
#define BIT_PMU_APB_PD_V3_PHY_BISR_FORCE_EN                        BIT(14)
#define BIT_PMU_APB_PD_V3_LWPROC_BISR_FORCE_EN                     BIT(13)
#define BIT_PMU_APB_PD_V3_WCE_BISR_FORCE_EN                        BIT(12)
#define BIT_PMU_APB_PD_V3_DPFEC_BISR_FORCE_EN                      BIT(11)
#define BIT_PMU_APB_PD_V3_LCE_BISR_FORCE_EN                        BIT(10)
#define BIT_PMU_APB_PD_AUDCP_AUDDSP_BISR_FORCE_EN                  BIT(9)
#define BIT_PMU_APB_PD_AUDCP_SYS_BISR_FORCE_EN                     BIT(8)
#define BIT_PMU_APB_PD_NRCP_SYNC_BISR_FORCE_EN                     BIT(7)
#define BIT_PMU_APB_PD_NRCP_SYS_BISR_FORCE_EN                      BIT(6)
#define BIT_PMU_APB_PD_AP_SYS_BISR_FORCE_EN                        BIT(5)
#define BIT_PMU_APB_PD_APCPU_TOP_BISR_FORCE_EN                     BIT(4)
#define BIT_PMU_APB_PD_APCPU_C3_BISR_FORCE_EN                      BIT(3)
#define BIT_PMU_APB_PD_APCPU_C2_BISR_FORCE_EN                      BIT(2)
#define BIT_PMU_APB_PD_APCPU_C1_BISR_FORCE_EN                      BIT(1)
#define BIT_PMU_APB_PD_APCPU_C0_BISR_FORCE_EN                      BIT(0)

/* REG_PMU_APB_SLEEP_XTLON_CTRL */

#define BIT_PMU_APB_IPA_SLEEP_XTL_ON                               BIT(6)
#define BIT_PMU_APB_SP_SYS_SLEEP_XTL_ON                            BIT(5)
#define BIT_PMU_APB_NRCP_SLEEP_XTL_ON                              BIT(4)
#define BIT_PMU_APB_AUDCP_SYS_SLEEP_XTL_ON                         BIT(3)
#define BIT_PMU_APB_PSCP_SLEEP_XTL_ON                              BIT(2)
#define BIT_PMU_APB_V3_MODEM_SLEEP_XTL_ON                          BIT(1)
#define BIT_PMU_APB_AP_SLEEP_XTL_ON                                BIT(0)

/* REG_PMU_APB_MEM_SLP_CFG */

#define BIT_PMU_APB_MEM_SLP_CFG(x)                                 (((x) & 0xFFFFFFFF))

/* REG_PMU_APB_MEM_SD_CFG */

#define BIT_PMU_APB_MEM_SD_CFG(x)                                  (((x) & 0xFFFFFFFF))

/* REG_PMU_APB_APCPU_CORE_WAKEUP_EN */

#define BIT_PMU_APB_APCPU_C7_WAKEUP_EN                             BIT(7)
#define BIT_PMU_APB_APCPU_C6_WAKEUP_EN                             BIT(6)
#define BIT_PMU_APB_APCPU_C5_WAKEUP_EN                             BIT(5)
#define BIT_PMU_APB_APCPU_C4_WAKEUP_EN                             BIT(4)
#define BIT_PMU_APB_APCPU_C3_WAKEUP_EN                             BIT(3)
#define BIT_PMU_APB_APCPU_C2_WAKEUP_EN                             BIT(2)
#define BIT_PMU_APB_APCPU_C1_WAKEUP_EN                             BIT(1)
#define BIT_PMU_APB_APCPU_C0_WAKEUP_EN                             BIT(0)

/* REG_PMU_APB_SP_SYS_HOLD_CGM_EN */

#define BIT_PMU_APB_PD_APCPU_TOP_CMG_HOLD_EN                       BIT(8)
#define BIT_PMU_APB_PD_APCPU_C7_CMG_HOLD_EN                        BIT(7)
#define BIT_PMU_APB_PD_APCPU_C6_CMG_HOLD_EN                        BIT(6)
#define BIT_PMU_APB_PD_APCPU_C5_CMG_HOLD_EN                        BIT(5)
#define BIT_PMU_APB_PD_APCPU_C4_CMG_HOLD_EN                        BIT(4)
#define BIT_PMU_APB_PD_APCPU_C3_CMG_HOLD_EN                        BIT(3)
#define BIT_PMU_APB_PD_APCPU_C2_CMG_HOLD_EN                        BIT(2)
#define BIT_PMU_APB_PD_APCPU_C1_CMG_HOLD_EN                        BIT(1)
#define BIT_PMU_APB_PD_APCPU_C0_CMG_HOLD_EN                        BIT(0)

/* REG_PMU_APB_PWR_CNT_WAIT_CFG0 */

#define BIT_PMU_APB_AUDCP_PWR_WAIT_CNT(x)                          (((x) & 0xFF) << 24)
#define BIT_PMU_APB_PSCP_PWR_WAIT_CNT(x)                           (((x) & 0xFF) << 16)
#define BIT_PMU_APB_V3_MODEM_PWR_WAIT_CNT(x)                       (((x) & 0xFF) << 8)
#define BIT_PMU_APB_AP_PWR_WAIT_CNT(x)                             (((x) & 0xFF))

/* REG_PMU_APB_PWR_CNT_WAIT_CFG1 */

#define BIT_PMU_APB_IPA_PWR_WAIT_CNT(x)                            (((x) & 0xFF) << 16)
#define BIT_PMU_APB_SP_SYS_PWR_WAIT_CNT(x)                         (((x) & 0xFF) << 8)
#define BIT_PMU_APB_NRCP_PWR_WAIT_CNT(x)                           (((x) & 0xFF))

/* REG_PMU_APB_RCO_REL_CFG */

#define BIT_PMU_APB_RCO_IPA_SEL                                    BIT(11)
#define BIT_PMU_APB_RCO_CSYSPWRUPREQ_SEL                           BIT(10)
#define BIT_PMU_APB_RCO_FRC_OFF                                    BIT(9)
#define BIT_PMU_APB_RCO_FRC_ON                                     BIT(8)
#define BIT_PMU_APB_RCO_TOP_DVFS_SEL                               BIT(7)
#define BIT_PMU_APB_RCO_PUB_SYS_SEL                                BIT(6)
#define BIT_PMU_APB_RCO_SP_SYS_SEL                                 BIT(5)
#define BIT_PMU_APB_RCO_NRCP_SEL                                   BIT(4)
#define BIT_PMU_APB_RCO_AUDCP_SEL                                  BIT(3)
#define BIT_PMU_APB_RCO_PSCP_SEL                                   BIT(2)
#define BIT_PMU_APB_RCO_V3_MODEM_SEL                               BIT(1)
#define BIT_PMU_APB_RCO_AP_SEL                                     BIT(0)

/* REG_PMU_APB_RCO_CNT_WAIT_CFG */

#define BIT_PMU_APB_RCO_WAIT_CNT(x)                                (((x) & 0xFF))

/* REG_PMU_APB_MPLL0_REL_CFG */

#define BIT_PMU_APB_MPLL0_IPA_SEL                                  BIT(11)
#define BIT_PMU_APB_MPLL0_TOP_DVFS_SEL                             BIT(10)
#define BIT_PMU_APB_MPLL0_REF_SEL                                  BIT(9)
#define BIT_PMU_APB_MPLL0_FRC_OFF                                  BIT(8)
#define BIT_PMU_APB_MPLL0_FRC_ON                                   BIT(7)
#define BIT_PMU_APB_MPLL0_NRCP_SEL                                 BIT(6)
#define BIT_PMU_APB_MPLL0_SP_SYS_SEL                               BIT(5)
#define BIT_PMU_APB_MPLL0_PUB_SYS_SEL                              BIT(4)
#define BIT_PMU_APB_MPLL0_AUDCP_SEL                                BIT(3)
#define BIT_PMU_APB_MPLL0_PSCP_SEL                                 BIT(2)
#define BIT_PMU_APB_MPLL0_V3_MODEM_SEL                             BIT(1)
#define BIT_PMU_APB_MPLL0_AP_SEL                                   BIT(0)

/* REG_PMU_APB_MPLL1_REL_CFG */

#define BIT_PMU_APB_MPLL1_IPA_SEL                                  BIT(11)
#define BIT_PMU_APB_MPLL1_TOP_DVFS_SEL                             BIT(10)
#define BIT_PMU_APB_MPLL1_REF_SEL                                  BIT(9)
#define BIT_PMU_APB_MPLL1_FRC_OFF                                  BIT(8)
#define BIT_PMU_APB_MPLL1_FRC_ON                                   BIT(7)
#define BIT_PMU_APB_MPLL1_NRCP_SEL                                 BIT(6)
#define BIT_PMU_APB_MPLL1_SP_SYS_SEL                               BIT(5)
#define BIT_PMU_APB_MPLL1_PUB_SYS_SEL                              BIT(4)
#define BIT_PMU_APB_MPLL1_AUDCP_SEL                                BIT(3)
#define BIT_PMU_APB_MPLL1_PSCP_SEL                                 BIT(2)
#define BIT_PMU_APB_MPLL1_V3_MODEM_SEL                             BIT(1)
#define BIT_PMU_APB_MPLL1_AP_SEL                                   BIT(0)

/* REG_PMU_APB_NR_CPUPLL_REL_CFG */

#define BIT_PMU_APB_NR_CPUPLL_IPA_SEL                              BIT(11)
#define BIT_PMU_APB_NR_CPUPLL_TOP_DVFS_SEL                         BIT(10)
#define BIT_PMU_APB_NR_CPUPLL_REF_SEL                              BIT(9)
#define BIT_PMU_APB_NR_CPUPLL_FRC_OFF                              BIT(8)
#define BIT_PMU_APB_NR_CPUPLL_FRC_ON                               BIT(7)
#define BIT_PMU_APB_NR_CPUPLL_NRCP_SEL                             BIT(6)
#define BIT_PMU_APB_NR_CPUPLL_SP_SYS_SEL                           BIT(5)
#define BIT_PMU_APB_NR_CPUPLL_PUB_SYS_SEL                          BIT(4)
#define BIT_PMU_APB_NR_CPUPLL_AUDCP_SEL                            BIT(3)
#define BIT_PMU_APB_NR_CPUPLL_PSCP_SEL                             BIT(2)
#define BIT_PMU_APB_NR_CPUPLL_V3_MODEM_SEL                         BIT(1)
#define BIT_PMU_APB_NR_CPUPLL_AP_SEL                               BIT(0)

/* REG_PMU_APB_MEM_AUTO_SLP_CFG */

#define BIT_PMU_APB_MEM_AUTO_SLP_EN(x)                             (((x) & 0xFFFFFFFF))

/* REG_PMU_APB_MEM_AUTO_SD_CFG */

#define BIT_PMU_APB_MEM_AUTO_SD_EN(x)                              (((x) & 0xFFFFFFFF))

/* REG_PMU_APB_WAKEUP_LOCK_EN */

#define BIT_PMU_APB_PD_APCPU_C7_WAKEUP_LOCK_EN                     BIT(31)
#define BIT_PMU_APB_PD_APCPU_C6_WAKEUP_LOCK_EN                     BIT(30)
#define BIT_PMU_APB_PD_APCPU_C5_WAKEUP_LOCK_EN                     BIT(29)
#define BIT_PMU_APB_PD_APCPU_C4_WAKEUP_LOCK_EN                     BIT(28)
#define BIT_PMU_APB_PD_GPU_RGX_DUST_B_WAKEUP_LOCK_EN               BIT(27)
#define BIT_PMU_APB_PD_V3_TD_WAKEUP_LOCK_EN                        BIT(26)
#define BIT_PMU_APB_NRCP_SYS_WAKEUP_LOCK_EN                        BIT(25)
#define BIT_PMU_APB_PSCP_SYS_WAKEUP_LOCK_EN                        BIT(24)
#define BIT_PMU_APB_V3_MODEM_SYS_WAKEUP_LOCK_EN                    BIT(23)
#define BIT_PMU_APB_AP_SYS_WAKEUP_LOCK_EN                          BIT(22)
#define BIT_PMU_APB_PD_PUB_SYS_WAKEUP_LOCK_EN                      BIT(21)
#define BIT_PMU_APB_PD_NRCP_UL_WAKEUP_LOCK_EN                      BIT(19)
#define BIT_PMU_APB_PD_NRCP_DL_WAKEUP_LOCK_EN                      BIT(18)
#define BIT_PMU_APB_PD_PSCP_SYS_WAKEUP_LOCK_EN                     BIT(17)
#define BIT_PMU_APB_PD_V3_MODEM_SYS_WAKEUP_LOCK_EN                 BIT(16)
#define BIT_PMU_APB_PD_V3_PS_WAKEUP_LOCK_EN                        BIT(15)
#define BIT_PMU_APB_PD_V3_PHY_WAKEUP_LOCK_EN                       BIT(14)
#define BIT_PMU_APB_PD_V3_LWPROC_WAKEUP_LOCK_EN                    BIT(13)
#define BIT_PMU_APB_PD_V3_WCE_WAKEUP_LOCK_EN                       BIT(12)
#define BIT_PMU_APB_PD_V3_DPFEC_WAKEUP_LOCK_EN                     BIT(11)
#define BIT_PMU_APB_PD_V3_LCE_WAKEUP_LOCK_EN                       BIT(10)
#define BIT_PMU_APB_PD_AUDCP_AUDDSP_WAKEUP_LOCK_EN                 BIT(9)
#define BIT_PMU_APB_PD_AUDCP_SYS_WAKEUP_LOCK_EN                    BIT(8)
#define BIT_PMU_APB_PD_NRCP_SYNC_WAKEUP_LOCK_EN                    BIT(7)
#define BIT_PMU_APB_PD_NRCP_SYS_WAKEUP_LOCK_EN                     BIT(6)
#define BIT_PMU_APB_PD_AP_SYS_WAKEUP_LOCK_EN                       BIT(5)
#define BIT_PMU_APB_PD_APCPU_TOP_WAKEUP_LOCK_EN                    BIT(4)
#define BIT_PMU_APB_PD_APCPU_C3_WAKEUP_LOCK_EN                     BIT(3)
#define BIT_PMU_APB_PD_APCPU_C2_WAKEUP_LOCK_EN                     BIT(2)
#define BIT_PMU_APB_PD_APCPU_C1_WAKEUP_LOCK_EN                     BIT(1)
#define BIT_PMU_APB_PD_APCPU_C0_WAKEUP_LOCK_EN                     BIT(0)

/* REG_PMU_APB_AUDCP_SYS_CORE_INT_DISABLE */

#define BIT_PMU_APB_AUDCP_SYS_CORE_INT_DISABLE                     BIT(0)

/* REG_PMU_APB_V3_PS_CORE_INT_DISABLE */

#define BIT_PMU_APB_V3_PS_CORE_INT_DISABLE                         BIT(0)

/* REG_PMU_APB_NRCP_DSP_1_CORE_INT_DISABLE */

#define BIT_PMU_APB_NRCP_DSP_1_CORE_INT_DISABLE                    BIT(0)

/* REG_PMU_APB_NRCP_DSP_0_CORE_INT_DISABLE */

#define BIT_PMU_APB_NRCP_DSP_0_CORE_INT_DISABLE                    BIT(0)

/* REG_PMU_APB_PSCP_CORE_INT_DISABLE */

#define BIT_PMU_APB_PSCP_CORE_INT_DISABLE                          BIT(0)

/* REG_PMU_APB_APCPU_C0_CORE_INT_DISABLE */

#define BIT_PMU_APB_APCPU_C0_CORE_INT_DISABLE                      BIT(0)

/* REG_PMU_APB_APCPU_C1_CORE_INT_DISABLE */

#define BIT_PMU_APB_APCPU_C1_CORE_INT_DISABLE                      BIT(0)

/* REG_PMU_APB_APCPU_C2_CORE_INT_DISABLE */

#define BIT_PMU_APB_APCPU_C2_CORE_INT_DISABLE                      BIT(0)

/* REG_PMU_APB_APCPU_C3_CORE_INT_DISABLE */

#define BIT_PMU_APB_APCPU_C3_CORE_INT_DISABLE                      BIT(0)

/* REG_PMU_APB_APCPU_C4_CORE_INT_DISABLE */

#define BIT_PMU_APB_APCPU_C4_CORE_INT_DISABLE                      BIT(0)

/* REG_PMU_APB_APCPU_C5_CORE_INT_DISABLE */

#define BIT_PMU_APB_APCPU_C5_CORE_INT_DISABLE                      BIT(0)

/* REG_PMU_APB_NRCP_CORE_INT_DISABLE */

#define BIT_PMU_APB_NRCP_CORE_INT_DISABLE                          BIT(0)

/* REG_PMU_APB_V3_PHY_CORE_INT_DISABLE */

#define BIT_PMU_APB_V3_PHY_CORE_INT_DISABLE                        BIT(0)

/* REG_PMU_APB_APCPU_C4_DSLP_ENA */

#define BIT_PMU_APB_APCPU_C4_DSLP_ENA                              BIT(0)

/* REG_PMU_APB_APCPU_C5_DSLP_ENA */

#define BIT_PMU_APB_APCPU_C5_DSLP_ENA                              BIT(0)

/* REG_PMU_APB_APCPU_C6_DSLP_ENA */

#define BIT_PMU_APB_APCPU_C6_DSLP_ENA                              BIT(0)

/* REG_PMU_APB_APCPU_C7_DSLP_ENA */

#define BIT_PMU_APB_APCPU_C7_DSLP_ENA                              BIT(0)

/* REG_PMU_APB_NR_DSPPLL_REL_CFG */

#define BIT_PMU_APB_NR_DSPPLL_IPA_SEL                              BIT(11)
#define BIT_PMU_APB_NR_DSPPLL_TOP_DVFS_SEL                         BIT(10)
#define BIT_PMU_APB_NR_DSPPLL_REF_SEL                              BIT(9)
#define BIT_PMU_APB_NR_DSPPLL_FRC_OFF                              BIT(8)
#define BIT_PMU_APB_NR_DSPPLL_FRC_ON                               BIT(7)
#define BIT_PMU_APB_NR_DSPPLL_NRCP_SEL                             BIT(6)
#define BIT_PMU_APB_NR_DSPPLL_SP_SYS_SEL                           BIT(5)
#define BIT_PMU_APB_NR_DSPPLL_PUB_SYS_SEL                          BIT(4)
#define BIT_PMU_APB_NR_DSPPLL_AUDCP_SEL                            BIT(3)
#define BIT_PMU_APB_NR_DSPPLL_PSCP_SEL                             BIT(2)
#define BIT_PMU_APB_NR_DSPPLL_V3_MODEM_SEL                         BIT(1)
#define BIT_PMU_APB_NR_DSPPLL_AP_SEL                               BIT(0)

/* REG_PMU_APB_NRCP_DSP_0_DSLP_ENA */

#define BIT_PMU_APB_NRCP_DSP_0_DSLP_ENA                            BIT(0)

/* REG_PMU_APB_NRCP_DSP_1_DSLP_ENA */

#define BIT_PMU_APB_NRCP_DSP_1_DSLP_ENA                            BIT(0)

/* REG_PMU_APB_AP_DSLP_ENA */

#define BIT_PMU_APB_AP_DSLP_ENA                                    BIT(0)

/* REG_PMU_APB_PSCP_DSLP_ENA */

#define BIT_PMU_APB_PSCP_DSLP_ENA                                  BIT(0)

/* REG_PMU_APB_V3_MODEM_DSLP_ENA */

#define BIT_PMU_APB_V3_MODEM_DSLP_ENA1                             BIT(1)
#define BIT_PMU_APB_V3_MODEM_DSLP_ENA0                             BIT(0)

/* REG_PMU_APB_APCPU_TOP_DSLP_ENA */

#define BIT_PMU_APB_APCPU_TOP_DSLP_ENA                             BIT(0)

/* REG_PMU_APB_SP_SYS_DSLP_ENA */

#define BIT_PMU_APB_SP_SYS_DSLP_ENA                                BIT(0)

/* REG_PMU_APB_PUB_DEEP_SLEEP_ENA */

#define BIT_PMU_APB_AUDCP_SYS_PUB_DSLP_ENA                         BIT(0)

/* REG_PMU_APB_PUB_DEEP_SLEEP_WAKEUP_EN */

#define BIT_PMU_APB_AUDCP_PUB_DSLP_WAKEUP_EN                       BIT(0)

/* REG_PMU_APB_LIGHT_SLEEP_WAKEUP_EN */

#define BIT_PMU_APB_NRCP_LSLP_WAKEUP_EN                            BIT(4)
#define BIT_PMU_APB_AUDCP_LSLP_WAKEUP_EN                           BIT(3)
#define BIT_PMU_APB_V3_MODEM_LSLP_WAKEUP_EN                        BIT(2)
#define BIT_PMU_APB_PSCP_LSLP_WAKEUP_EN                            BIT(1)
#define BIT_PMU_APB_AP_LSLP_WAKEUP_EN                              BIT(0)

/* REG_PMU_APB_V3_PS_DSLP_ENA */

#define BIT_PMU_APB_V3_PS_DSLP_ENA                                 BIT(0)

/* REG_PMU_APB_V3_PHY_DSLP_ENA */

#define BIT_PMU_APB_V3_PHY_DSLP_ENA                                BIT(0)

/* REG_PMU_APB_LIGHT_SLEEP_ENABLE */

#define BIT_PMU_APB_APCPU_TOP_SMART_LSLP_ENA                       BIT(21)
#define BIT_PMU_APB_NRCP_SMART_LSLP_ENA                            BIT(16)
#define BIT_PMU_APB_AUDCP_SYS_SMART_LSLP_ENA                       BIT(15)
#define BIT_PMU_APB_AON_SMART_LSLP_ENA                             BIT(14)
#define BIT_PMU_APB_V3_MODEM_SMART_LSLP_ENA                        BIT(13)
#define BIT_PMU_APB_PSCP_SMART_LSLP_ENA                            BIT(12)
#define BIT_PMU_APB_AP_SMART_LSLP_ENA                              BIT(11)
#define BIT_PMU_APB_PUB_SYS_SMART_LSLP_ENA                         BIT(10)
#define BIT_PMU_APB_MM_LSLP_ENA                                    BIT(9)
#define BIT_PMU_APB_GPU_LSLP_ENA                                   BIT(8)
#define BIT_PMU_APB_IPA_LSLP_ENA                                   BIT(6)
#define BIT_PMU_APB_NRCP_LSLP_ENA                                  BIT(5)
#define BIT_PMU_APB_AUDCP_SYS_LSLP_ENA                             BIT(4)
#define BIT_PMU_APB_AON_LSLP_ENA                                   BIT(3)
#define BIT_PMU_APB_V3_MODEM_LSLP_ENA                              BIT(2)
#define BIT_PMU_APB_PSCP_LSLP_ENA                                  BIT(1)
#define BIT_PMU_APB_AP_LSLP_ENA                                    BIT(0)

/* REG_PMU_APB_LIGHT_SLEEP_MON */

#define BIT_PMU_APB_IPA_LIGHT_SLEEP                                BIT(7)
#define BIT_PMU_APB_NRCP_LIGHT_SLEEP                               BIT(6)
#define BIT_PMU_APB_PUB_SYS_LIGHT_SLEEP                            BIT(5)
#define BIT_PMU_APB_AP_LIGHT_SLEEP                                 BIT(4)
#define BIT_PMU_APB_V3_MODEM_LIGHT_SLEEP                           BIT(3)
#define BIT_PMU_APB_PSCP_LIGHT_SLEEP                               BIT(2)
#define BIT_PMU_APB_AUDCP_LIGHT_SLEEP                              BIT(1)
#define BIT_PMU_APB_AON_SYS_LIGHT_SLEEP                            BIT(0)

/* REG_PMU_APB_AUDCP_SYS_DSLP_ENA */

#define BIT_PMU_APB_AUDCP_SYS_DSLP_ENA                             BIT(0)

/* REG_PMU_APB_AUDCP_AUDDSP_DSLP_ENA */

#define BIT_PMU_APB_AUDCP_AUDDSP_DSLP_ENA                          BIT(0)

/* REG_PMU_APB_NRCP_DSLP_ENA */

#define BIT_PMU_APB_NRCP_DSLP_ENA                                  BIT(0)

/* REG_PMU_APB_PUB_ACC_RDY */

#define BIT_PMU_APB_PUB_ACC_RDY                                    BIT(0)

/* REG_PMU_APB_PUB_CLK_RDY */

#define BIT_PMU_APB_PUB_CLK_RDY                                    BIT(0)

/* REG_PMU_APB_EIC_SEL */

#define BIT_PMU_APB_EIC_LIGHT_SLEEP_SEL                            BIT(1)
#define BIT_PMU_APB_EIC_DEEP_SLEEP_SEL                             BIT(0)

/* REG_PMU_APB_MIXED_CFG */

#define BIT_PMU_APB_CS_SYS_DDR_WAKEUP_N_MASK                       BIT(1)
#define BIT_PMU_APB_AP_APCPU_COUPLE_EN                             BIT(0)

/* REG_PMU_APB_PMU_DEBUG */

#define BIT_PMU_APB_PMU_DEBUG(x)                                   (((x) & 0xFFFFFFFF))

/* REG_PMU_APB_SLEEP_CNT_CLR */

#define BIT_PMU_APB_IPA_SYS_SLEEP_CNT_CLR                          BIT(22)
#define BIT_PMU_APB_IPA_LIGHT_SLEEP_CNT_CLR                        BIT(21)
#define BIT_PMU_APB_IPA_DEEP_SLEEP_CNT_CLR                         BIT(20)
#define BIT_PMU_APB_NRCP_LIGHT_SLEEP_CNT_CLR                       BIT(19)
#define BIT_PMU_APB_NRCP_SYS_SLEEP_CNT_CLR                         BIT(18)
#define BIT_PMU_APB_APCPU_TOP_SYS_SLEEP_CNT_CLR                    BIT(17)
#define BIT_PMU_APB_PSCP_SYS_SLEEP_CNT_CLR                         BIT(16)
#define BIT_PMU_APB_V3_MODEM_SYS_SLEEP_CNT_CLR                     BIT(15)
#define BIT_PMU_APB_AP_SYS_SLEEP_CNT_CLR                           BIT(14)
#define BIT_PMU_APB_AUDCP_SYS_SLEEP_CNT_CLR                        BIT(13)
#define BIT_PMU_APB_AON_SYS_LIGHT_SLEEP_CNT_CLR                    BIT(12)
#define BIT_PMU_APB_PSCP_LIGHT_SLEEP_CNT_CLR                       BIT(11)
#define BIT_PMU_APB_V3_MODEM_LIGHT_SLEEP_CNT_CLR                   BIT(10)
#define BIT_PMU_APB_AP_LIGHT_SLEEP_CNT_CLR                         BIT(9)
#define BIT_PMU_APB_PUB_SYS_LIGHT_SLEEP_CNT_CLR                    BIT(8)
#define BIT_PMU_APB_AUDCP_SYS_LIGHT_SLEEP_CNT_CLR                  BIT(7)
#define BIT_PMU_APB_NRCP_DEEP_SLEEP_CNT_CLR                        BIT(6)
#define BIT_PMU_APB_SP_SYS_DEEP_SLEEP_CNT_CLR                      BIT(5)
#define BIT_PMU_APB_PSCP_DEEP_SLEEP_CNT_CLR                        BIT(4)
#define BIT_PMU_APB_V3_MODEM_DEEP_SLEEP_CNT_CLR                    BIT(3)
#define BIT_PMU_APB_AP_DEEP_SLEEP_CNT_CLR                          BIT(2)
#define BIT_PMU_APB_PUB_DEEP_SLEEP_CNT_CLR                         BIT(1)
#define BIT_PMU_APB_AUDCP_SYS_DEEP_SLEEP_CNT_CLR                   BIT(0)

/* REG_PMU_APB_PAD_OUT_DCDC_AI_EN_CFG */

#define BIT_PMU_APB_PAD_OUT_DCDC_AI_EN_IPA_DEEP_SLEEP_MASK         BIT(13)
#define BIT_PMU_APB_PAD_OUT_DCDC_AI_EN_POL_SEL                     BIT(12)
#define BIT_PMU_APB_PAD_OUT_DCDC_AI_EN_TOP_DVFS_DEEP_SLEEP_MASK    BIT(11)
#define BIT_PMU_APB_PAD_OUT_DCDC_AI_EN_PLL_PD_MASK                 BIT(10)
#define BIT_PMU_APB_PAD_OUT_DCDC_AI_EN_EXT_XTL_PD_MASK             BIT(9)
#define BIT_PMU_APB_PAD_OUT_DCDC_AI_EN_SP_SYS_DEEP_SLEEP_MASK      BIT(8)
#define BIT_PMU_APB_PAD_OUT_DCDC_AI_EN_AP_DEEP_SLEEP_MASK          BIT(7)
#define BIT_PMU_APB_PAD_OUT_DCDC_AI_EN_ESE_DEEP_SLEEP_MASK         BIT(6)
#define BIT_PMU_APB_PAD_OUT_DCDC_AI_EN_PUB_SYS_DEEP_SLEEP_MASK     BIT(5)
#define BIT_PMU_APB_PAD_OUT_DCDC_AI_EN_AI_SYS_PD_MASK              BIT(4)
#define BIT_PMU_APB_PAD_OUT_DCDC_AI_EN_APCPU_TOP_PD_MASK           BIT(3)
#define BIT_PMU_APB_PAD_OUT_DCDC_AI_EN_WTLCP_DEEP_SLEEP_MASK       BIT(2)
#define BIT_PMU_APB_PAD_OUT_DCDC_AI_EN_PUBCP_DEEP_SLEEP_MASK       BIT(1)
#define BIT_PMU_APB_PAD_OUT_DCDC_AI_EN_AUDCP_DEEP_SLEEP_MASK       BIT(0)

/* REG_PMU_APB_LVDSRFPLL_REL_CFG */

#define BIT_PMU_APB_LVDSRFPLL_REF_SEL(x)                           (((x) & 0x3) << 8)

/* REG_PMU_APB_EXT_XTL_EN_CTRL */

#define BIT_PMU_APB_EXT_XTL3_COMB_EN                               BIT(3)
#define BIT_PMU_APB_EXT_XTL2_COMB_EN                               BIT(2)
#define BIT_PMU_APB_EXT_XTL1_COMB_EN                               BIT(1)
#define BIT_PMU_APB_EXT_XTL0_COMB_EN                               BIT(0)

/* REG_PMU_APB_PAD_OUT_CHIP_SLEEP_CFG */

#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_IPA_DEEP_SLEEP_MASK         BIT(13)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_POL_SEL                     BIT(12)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_TOP_DVFS_DEEP_SLEEP_MASK    BIT(11)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_PLL_PD_MASK                 BIT(10)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_EXT_XTL_PD_MASK             BIT(9)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_SP_SYS_DEEP_SLEEP_MASK      BIT(8)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_AP_DEEP_SLEEP_MASK          BIT(7)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_NRCP_DEEP_SLEEP_MASK        BIT(6)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_PUB_SYS_DEEP_SLEEP_MASK     BIT(5)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_APCPU_C7_PD_MASK            BIT(4)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_APCPU_TOP_PD_MASK           BIT(3)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_V3_MODEM_DEEP_SLEEP_MASK    BIT(2)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_PSCP_DEEP_SLEEP_MASK        BIT(1)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_AUDCP_DEEP_SLEEP_MASK       BIT(0)

/* REG_PMU_APB_PAD_OUT_XTL_EN0_CFG */

#define BIT_PMU_APB_PAD_OUT_XTL_EN0_IPA_DEEP_SLEEP_MASK            BIT(13)
#define BIT_PMU_APB_PAD_OUT_XTL_EN0_POL_SEL                        BIT(12)
#define BIT_PMU_APB_PAD_OUT_XTL_EN0_TOP_DVFS_DEEP_SLEEP_MASK       BIT(11)
#define BIT_PMU_APB_PAD_OUT_XTL_EN0_PLL_PD_MASK                    BIT(10)
#define BIT_PMU_APB_PAD_OUT_XTL_EN0_EXT_XTL_PD_MASK                BIT(9)
#define BIT_PMU_APB_PAD_OUT_XTL_EN0_SP_SYS_DEEP_SLEEP_MASK         BIT(8)
#define BIT_PMU_APB_PAD_OUT_XTL_EN0_AP_DEEP_SLEEP_MASK             BIT(7)
#define BIT_PMU_APB_PAD_OUT_XTL_EN0_NRCP_DEEP_SLEEP_MASK           BIT(6)
#define BIT_PMU_APB_PAD_OUT_XTL_EN0_PUB_SYS_DEEP_SLEEP_MASK        BIT(5)
#define BIT_PMU_APB_PAD_OUT_XTL_EN0_APCPU_C7_PD_MASK               BIT(4)
#define BIT_PMU_APB_PAD_OUT_XTL_EN0_APCPU_TOP_PD_MASK              BIT(3)
#define BIT_PMU_APB_PAD_OUT_XTL_EN0_V3_MODEM_DEEP_SLEEP_MASK       BIT(2)
#define BIT_PMU_APB_PAD_OUT_XTL_EN0_PSCP_DEEP_SLEEP_MASK           BIT(1)
#define BIT_PMU_APB_PAD_OUT_XTL_EN0_AUDCP_DEEP_SLEEP_MASK          BIT(0)

/* REG_PMU_APB_PAD_OUT_XTL_EN1_CFG */

#define BIT_PMU_APB_PAD_OUT_XTL_EN1_IPA_DEEP_SLEEP_MASK            BIT(13)
#define BIT_PMU_APB_PAD_OUT_XTL_EN1_POL_SEL                        BIT(12)
#define BIT_PMU_APB_PAD_OUT_XTL_EN1_TOP_DVFS_DEEP_SLEEP_MASK       BIT(11)
#define BIT_PMU_APB_PAD_OUT_XTL_EN1_PLL_PD_MASK                    BIT(10)
#define BIT_PMU_APB_PAD_OUT_XTL_EN1_EXT_XTL_PD_MASK                BIT(9)
#define BIT_PMU_APB_PAD_OUT_XTL_EN1_SP_SYS_DEEP_SLEEP_MASK         BIT(8)
#define BIT_PMU_APB_PAD_OUT_XTL_EN1_AP_DEEP_SLEEP_MASK             BIT(7)
#define BIT_PMU_APB_PAD_OUT_XTL_EN1_NRCP_DEEP_SLEEP_MASK           BIT(6)
#define BIT_PMU_APB_PAD_OUT_XTL_EN1_PUB_SYS_DEEP_SLEEP_MASK        BIT(5)
#define BIT_PMU_APB_PAD_OUT_XTL_EN1_APCPU_C7_PD_MASK               BIT(4)
#define BIT_PMU_APB_PAD_OUT_XTL_EN1_APCPU_TOP_PD_MASK              BIT(3)
#define BIT_PMU_APB_PAD_OUT_XTL_EN1_V3_MODEM_DEEP_SLEEP_MASK       BIT(2)
#define BIT_PMU_APB_PAD_OUT_XTL_EN1_PSCP_DEEP_SLEEP_MASK           BIT(1)
#define BIT_PMU_APB_PAD_OUT_XTL_EN1_AUDCP_DEEP_SLEEP_MASK          BIT(0)

/* REG_PMU_APB_PAD_OUT_DCDC_ARM0_EN_CFG */

#define BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_IPA_DEEP_SLEEP_MASK       BIT(13)
#define BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_POL_SEL                   BIT(12)
#define BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_TOP_DVFS_DEEP_SLEEP_MASK  BIT(11)
#define BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_PLL_PD_MASK               BIT(10)
#define BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_EXT_XTL_PD_MASK           BIT(9)
#define BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_SP_SYS_DEEP_SLEEP_MASK    BIT(8)
#define BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_AP_DEEP_SLEEP_MASK        BIT(7)
#define BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_NRCP_DEEP_SLEEP_MASK      BIT(6)
#define BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_PUB_SYS_DEEP_SLEEP_MASK   BIT(5)
#define BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_APCPU_C7_PD_MASK          BIT(4)
#define BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_APCPU_TOP_PD_MASK         BIT(3)
#define BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_V3_MODEM_DEEP_SLEEP_MASK  BIT(2)
#define BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_PSCP_DEEP_SLEEP_MASK      BIT(1)
#define BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_AUDCP_DEEP_SLEEP_MASK     BIT(0)

/* REG_PMU_APB_PAD_OUT_XTL_EN2_CFG */

#define BIT_PMU_APB_PAD_OUT_XTL_EN2_IPA_DEEP_SLEEP_MASK            BIT(13)
#define BIT_PMU_APB_PAD_OUT_XTL_EN2_POL_SEL                        BIT(12)
#define BIT_PMU_APB_PAD_OUT_XTL_EN2_TOP_DVFS_DEEP_SLEEP_MASK       BIT(11)
#define BIT_PMU_APB_PAD_OUT_XTL_EN2_PLL_PD_MASK                    BIT(10)
#define BIT_PMU_APB_PAD_OUT_XTL_EN2_EXT_XTL_PD_MASK                BIT(9)
#define BIT_PMU_APB_PAD_OUT_XTL_EN2_SP_SYS_DEEP_SLEEP_MASK         BIT(8)
#define BIT_PMU_APB_PAD_OUT_XTL_EN2_AP_DEEP_SLEEP_MASK             BIT(7)
#define BIT_PMU_APB_PAD_OUT_XTL_EN2_NRCP_DEEP_SLEEP_MASK           BIT(6)
#define BIT_PMU_APB_PAD_OUT_XTL_EN2_PUB_SYS_DEEP_SLEEP_MASK        BIT(5)
#define BIT_PMU_APB_PAD_OUT_XTL_EN2_APCPU_C7_PD_MASK               BIT(4)
#define BIT_PMU_APB_PAD_OUT_XTL_EN2_APCPU_TOP_PD_MASK              BIT(3)
#define BIT_PMU_APB_PAD_OUT_XTL_EN2_V3_MODEM_DEEP_SLEEP_MASK       BIT(2)
#define BIT_PMU_APB_PAD_OUT_XTL_EN2_PSCP_DEEP_SLEEP_MASK           BIT(1)
#define BIT_PMU_APB_PAD_OUT_XTL_EN2_AUDCP_DEEP_SLEEP_MASK          BIT(0)

/* REG_PMU_APB_DCXO_LP_DEEP_SLEEP_CFG */

#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_IPA_DEEP_SLEEP_MASK         BIT(13)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_POL_SEL                     BIT(12)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_TOP_DVFS_DEEP_SLEEP_MASK    BIT(11)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_PLL_PD_MASK                 BIT(10)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_EXT_XTL_PD_MASK             BIT(9)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_SP_SYS_DEEP_SLEEP_MASK      BIT(8)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_AP_DEEP_SLEEP_MASK          BIT(7)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_NRCP_DEEP_SLEEP_MASK        BIT(6)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_PUB_SYS_DEEP_SLEEP_MASK     BIT(5)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_APCPU_C7_PD_MASK            BIT(4)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_APCPU_TOP_PD_MASK           BIT(3)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_V3_MODEM_DEEP_SLEEP_MASK    BIT(2)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_PSCP_DEEP_SLEEP_MASK        BIT(1)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_AUDCP_DEEP_SLEEP_MASK       BIT(0)

/* REG_PMU_APB_BISR_FORCE_SEL */

#define BIT_PMU_APB_PD_IPA_SYS_BISR_FORCE_SEL                      BIT(30)
#define BIT_PMU_APB_PD_ESE_SYS_BISR_FORCE_SEL                      BIT(29)
#define BIT_PMU_APB_PD_APCPU_C7_BISR_FORCE_SEL                     BIT(28)
#define BIT_PMU_APB_PD_APCPU_C6_BISR_FORCE_SEL                     BIT(27)
#define BIT_PMU_APB_PD_APCPU_C5_BISR_FORCE_SEL                     BIT(26)
#define BIT_PMU_APB_PD_APCPU_C4_BISR_FORCE_SEL                     BIT(25)
#define BIT_PMU_APB_PD_NRCP_DSP_1_BISR_FORCE_SEL                   BIT(23)
#define BIT_PMU_APB_PD_NRCP_DSP_0_BISR_FORCE_SEL                   BIT(22)
#define BIT_PMU_APB_PD_NRCP_UL_BISR_FORCE_SEL                      BIT(21)
#define BIT_PMU_APB_PD_NRCP_DL_BISR_FORCE_SEL                      BIT(20)
#define BIT_PMU_APB_PD_V3_TD_BISR_FORCE_SEL                        BIT(19)
#define BIT_PMU_APB_PD_AON_MEM_BISR_FORCE_SEL                      BIT(18)
#define BIT_PMU_APB_PD_PSCP_SYS_BISR_FORCE_SEL                     BIT(17)
#define BIT_PMU_APB_PD_V3_MODEM_SYS_BISR_FORCE_SEL                 BIT(16)
#define BIT_PMU_APB_PD_V3_PS_BISR_FORCE_SEL                        BIT(15)
#define BIT_PMU_APB_PD_V3_PHY_BISR_FORCE_SEL                       BIT(14)
#define BIT_PMU_APB_PD_V3_LWPROC_BISR_FORCE_SEL                    BIT(13)
#define BIT_PMU_APB_PD_V3_WCE_BISR_FORCE_SEL                       BIT(12)
#define BIT_PMU_APB_PD_V3_DPFEC_BISR_FORCE_SEL                     BIT(11)
#define BIT_PMU_APB_PD_V3_LCE_BISR_FORCE_SEL                       BIT(10)
#define BIT_PMU_APB_PD_AUDCP_AUDDSP_BISR_FORCE_SEL                 BIT(9)
#define BIT_PMU_APB_PD_AUDCP_SYS_BISR_FORCE_SEL                    BIT(8)
#define BIT_PMU_APB_PD_NRCP_SYNC_BISR_FORCE_SEL                    BIT(7)
#define BIT_PMU_APB_PD_NRCP_SYS_BISR_FORCE_SEL                     BIT(6)
#define BIT_PMU_APB_PD_AP_SYS_BISR_FORCE_SEL                       BIT(5)
#define BIT_PMU_APB_PD_APCPU_TOP_BISR_FORCE_SEL                    BIT(4)
#define BIT_PMU_APB_PD_APCPU_C3_BISR_FORCE_SEL                     BIT(3)
#define BIT_PMU_APB_PD_APCPU_C2_BISR_FORCE_SEL                     BIT(2)
#define BIT_PMU_APB_PD_APCPU_C1_BISR_FORCE_SEL                     BIT(1)
#define BIT_PMU_APB_PD_APCPU_C0_BISR_FORCE_SEL                     BIT(0)

/* REG_PMU_APB_AON_MEM_CTRL */

#define BIT_PMU_APB_EFUSE_SEL_BUF                                  BIT(2)
#define BIT_PMU_APB_SP_SYS_MEM_ALL_SEL                             BIT(1)
#define BIT_PMU_APB_AON_MEM_SP_SYS_SEL                             BIT(0)

/* REG_PMU_APB_PWR_DOMAIN_INT_CLR */

#define BIT_PMU_APB_INT_REQ_PWR_DOWN_CLR(x)                        (((x) & 0x1FF) << 16)
#define BIT_PMU_APB_INT_REQ_PWR_UP_CLR(x)                          (((x) & 0x1FF))

/* REG_PMU_APB_DDR_SLP_WAIT_CNT */

#define BIT_PMU_APB_PUB_SYS_DEEP_SLEEP_WAIT_CNT(x)                 (((x) & 0xFFFF) << 16)
#define BIT_PMU_APB_PUB_SYS_SLEEP_WAIT_CNT(x)                      (((x) & 0xFFFF))

/* REG_PMU_APB_PMU_CLK_DIV_CFG */

#define BIT_PMU_APB_PWR_ST_CLK_DIV_CFG(x)                          (((x) & 0xFFFF) << 16)
#define BIT_PMU_APB_SLP_CTRL_CLK_DIV_CFG(x)                        (((x) & 0xFFFF))

/* REG_PMU_APB_CGM_PMU_SEL */

#define BIT_PMU_APB_CGM_PMU_SEL_REG(x)                             (((x) & 0x3))

/* REG_PMU_APB_PWR_DGB_PARAMETER */

#define BIT_PMU_APB_RAM_PWR_DLY(x)                                 (((x) & 0xFF) << 24)
#define BIT_PMU_APB_ISO_OFF_DLY(x)                                 (((x) & 0xFF) << 16)
#define BIT_PMU_APB_CGM_ON_DLY(x)                                  (((x) & 0xFF) << 8)
#define BIT_PMU_APB_RST_ASSERT_DLY(x)                              (((x) & 0xFF))

/* REG_PMU_APB_APCPU_C0_DSLP_ENA */

#define BIT_PMU_APB_APCPU_C0_DSLP_ENA                              BIT(0)

/* REG_PMU_APB_APCPU_C1_DSLP_ENA */

#define BIT_PMU_APB_APCPU_C1_DSLP_ENA                              BIT(0)

/* REG_PMU_APB_APCPU_C2_DSLP_ENA */

#define BIT_PMU_APB_APCPU_C2_DSLP_ENA                              BIT(0)

/* REG_PMU_APB_APCPU_C3_DSLP_ENA */

#define BIT_PMU_APB_APCPU_C3_DSLP_ENA                              BIT(0)

/* REG_PMU_APB_APCPU_GIC_RST_EN */

#define BIT_PMU_APB_APCPU_C7_GIC_RST_EN                            BIT(8)
#define BIT_PMU_APB_APCPU_C6_GIC_RST_EN                            BIT(7)
#define BIT_PMU_APB_APCPU_C5_GIC_RST_EN                            BIT(6)
#define BIT_PMU_APB_APCPU_C4_GIC_RST_EN                            BIT(5)
#define BIT_PMU_APB_APCPU_C3_GIC_RST_EN                            BIT(4)
#define BIT_PMU_APB_APCPU_C2_GIC_RST_EN                            BIT(3)
#define BIT_PMU_APB_APCPU_C1_GIC_RST_EN                            BIT(2)
#define BIT_PMU_APB_APCPU_C0_GIC_RST_EN                            BIT(1)
#define BIT_PMU_APB_APCPU_TOP_GIC_RST_EN                           BIT(0)

/* REG_PMU_APB_ANALOG_PHY_PD_CFG */

#define BIT_PMU_APB_CSI_2P2LANE_PD_REG                             BIT(12)
#define BIT_PMU_APB_PHY_PWR_DLY(x)                                 (((x) & 0xFF) << 4)
#define BIT_PMU_APB_DSI_PD_REG                                     BIT(3)
#define BIT_PMU_APB_PCIE2_PD_REG                                   BIT(2)
#define BIT_PMU_APB_CSI_4LANE1_PD_REG                              BIT(1)
#define BIT_PMU_APB_CSI_4LANE0_PD_REG                              BIT(0)

/* REG_PMU_APB_PUB_SYS_DEEP_SLEEP_SEL */

#define BIT_PMU_APB_PUB_SYS_DEEP_SLEEP_SEL                         BIT(0)

/* REG_PMU_APB_PD_APCPU_C4_CFG */

#define BIT_PMU_APB_PD_APCPU_C4_QUAD_CORE_FORCE_SHUTDOWN           BIT(31)
#define BIT_PMU_APB_PD_APCPU_C4_QUAD_CORE_AUTO_SHUTDOWN_EN         BIT(30)
#define BIT_PMU_APB_PD_APCPU_C4_WFI_SHUTDOWN_EN                    BIT(29)
#define BIT_PMU_APB_PD_APCPU_C4_DBG_SHUTDOWN_EN                    BIT(28)
#define BIT_PMU_APB_PD_APCPU_C4_PD_SEL                             BIT(27)
#define BIT_PMU_APB_PD_APCPU_C4_FORCE_SHUTDOWN                     BIT(25)
#define BIT_PMU_APB_PD_APCPU_C4_AUTO_SHUTDOWN_EN                   BIT(24)
#define BIT_PMU_APB_PD_APCPU_C4_PWR_ON_DLY(x)                      (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_APCPU_C4_PWR_ON_SEQ_DLY(x)                  (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_APCPU_C4_ISO_ON_DLY(x)                      (((x) & 0xFF))

/* REG_PMU_APB_PD_APCPU_C5_CFG */

#define BIT_PMU_APB_PD_APCPU_C5_WFI_SHUTDOWN_EN                    BIT(29)
#define BIT_PMU_APB_PD_APCPU_C5_DBG_SHUTDOWN_EN                    BIT(28)
#define BIT_PMU_APB_PD_APCPU_C5_PD_SEL                             BIT(27)
#define BIT_PMU_APB_PD_APCPU_C5_FORCE_SHUTDOWN                     BIT(25)
#define BIT_PMU_APB_PD_APCPU_C5_AUTO_SHUTDOWN_EN                   BIT(24)
#define BIT_PMU_APB_PD_APCPU_C5_PWR_ON_DLY(x)                      (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_APCPU_C5_PWR_ON_SEQ_DLY(x)                  (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_APCPU_C5_ISO_ON_DLY(x)                      (((x) & 0xFF))

/* REG_PMU_APB_PD_APCPU_C6_CFG */

#define BIT_PMU_APB_PD_APCPU_C6_WFI_SHUTDOWN_EN                    BIT(29)
#define BIT_PMU_APB_PD_APCPU_C6_DBG_SHUTDOWN_EN                    BIT(28)
#define BIT_PMU_APB_PD_APCPU_C6_PD_SEL                             BIT(27)
#define BIT_PMU_APB_PD_APCPU_C6_FORCE_SHUTDOWN                     BIT(25)
#define BIT_PMU_APB_PD_APCPU_C6_AUTO_SHUTDOWN_EN                   BIT(24)
#define BIT_PMU_APB_PD_APCPU_C6_PWR_ON_DLY(x)                      (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_APCPU_C6_PWR_ON_SEQ_DLY(x)                  (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_APCPU_C6_ISO_ON_DLY(x)                      (((x) & 0xFF))

/* REG_PMU_APB_PD_APCPU_C7_CFG */

#define BIT_PMU_APB_PD_APCPU_C7_WFI_SHUTDOWN_EN                    BIT(29)
#define BIT_PMU_APB_PD_APCPU_C7_DBG_SHUTDOWN_EN                    BIT(28)
#define BIT_PMU_APB_PD_APCPU_C7_PD_SEL                             BIT(27)
#define BIT_PMU_APB_PD_APCPU_C7_FORCE_SHUTDOWN                     BIT(25)
#define BIT_PMU_APB_PD_APCPU_C7_AUTO_SHUTDOWN_EN                   BIT(24)
#define BIT_PMU_APB_PD_APCPU_C7_PWR_ON_DLY(x)                      (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_APCPU_C7_PWR_ON_SEQ_DLY(x)                  (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_APCPU_C7_ISO_ON_DLY(x)                      (((x) & 0xFF))

/* REG_PMU_APB_PD_APCPU_TOP_CFG3 */

#define BIT_PMU_APB_PD_DCDC_CPU1_SHUTDOWN_WINDOW(x)                (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_DCDC_CPU1_PWR_ON_DLY(x)                     (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_DCDC_CPU1_PWR_OFF_DLY(x)                    (((x) & 0xFF))

/* REG_PMU_APB_DCDC_AI_CTRL */

#define BIT_PMU_APB_PAD_OUT_DCDC_AI_EN                             BIT(0)

/* REG_PMU_APB_APCPU_TOP_CFG */

#define BIT_PMU_APB_APCPU_L2RSTDISABLE                             BIT(0)

/* REG_PMU_APB_PUB_VOL_DOWN_CFG */

#define BIT_PMU_APB_PUB_VOL_UP_CNT(x)                              (((x) & 0xFFFF) << 16)
#define BIT_PMU_APB_PUB_VOL_DOWN_CNT(x)                            (((x) & 0xFFFF))

/* REG_PMU_APB_PLL_WAIT_CNT3 */

#define BIT_PMU_APB_R5PLL_WAIT_CNT(x)                              (((x) & 0xFF))

/* REG_PMU_APB_R5PLL_REL_CFG */

#define BIT_PMU_APB_R5PLL_IPA_SEL                                  BIT(11)
#define BIT_PMU_APB_R5PLL_REF_SEL                                  BIT(10)
#define BIT_PMU_APB_R5PLL_FRC_OFF                                  BIT(9)
#define BIT_PMU_APB_R5PLL_FRC_ON                                   BIT(8)
#define BIT_PMU_APB_R5PLL_TOP_DVFS_SEL                             BIT(7)
#define BIT_PMU_APB_R5PLL_NRCP_SEL                                 BIT(6)
#define BIT_PMU_APB_R5PLL_SP_SYS_SEL                               BIT(5)
#define BIT_PMU_APB_R5PLL_PUB_SYS_SEL                              BIT(4)
#define BIT_PMU_APB_R5PLL_AUDCP_SEL                                BIT(3)
#define BIT_PMU_APB_R5PLL_PSCP_SEL                                 BIT(2)
#define BIT_PMU_APB_R5PLL_V3_MODEM_SEL                             BIT(1)
#define BIT_PMU_APB_R5PLL_AP_SEL                                   BIT(0)

/* REG_PMU_APB_APCPU_DSLP_ENA_SRST_MASK_CFG */

#define BIT_PMU_APB_APCPU_CORE_DSLP_ENA_SOFT_RST_MASK(x)           (((x) & 0x3) << 1)
#define BIT_PMU_APB_APCPU_TOP_DSLP_ENA_SOFT_RST_MASK               BIT(0)

/* REG_PMU_APB_PCIEPLL_H_REL_CFG */

#define BIT_PMU_APB_PCIEPLL_H_PCIE_CLKREQ_SEL                      BIT(14)
#define BIT_PMU_APB_PCIEPLL_H_PCIE_L2_SEL                          BIT(13)
#define BIT_PMU_APB_PCIEPLL_H_REF_SEL(x)                           (((x) & 0x7) << 10)
#define BIT_PMU_APB_PCIEPLL_H_FRC_OFF                              BIT(9)
#define BIT_PMU_APB_PCIEPLL_H_FRC_ON                               BIT(8)
#define BIT_PMU_APB_PCIEPLL_H_TOP_DVFS_SEL                         BIT(7)
#define BIT_PMU_APB_PCIEPLL_H_NRCP_SEL                             BIT(6)
#define BIT_PMU_APB_PCIEPLL_H_SP_SYS_SEL                           BIT(5)
#define BIT_PMU_APB_PCIEPLL_H_PUB_SYS_SEL                          BIT(4)
#define BIT_PMU_APB_PCIEPLL_H_AUDCP_SEL                            BIT(3)
#define BIT_PMU_APB_PCIEPLL_H_PSCP_SEL                             BIT(2)
#define BIT_PMU_APB_PCIEPLL_H_V3_MODEM_SEL                         BIT(1)
#define BIT_PMU_APB_PCIEPLL_H_AP_SEL                               BIT(0)

/* REG_PMU_APB_R5PLL_RST_CTRL_CFG */

#define BIT_PMU_APB_R5PLL_RST_CTRL_BYPASS                          BIT(24)
#define BIT_PMU_APB_R5PLL_DELAY_PWR_ON(x)                          (((x) & 0xFF) << 16)
#define BIT_PMU_APB_R5PLL_DELAY_EN_OFF(x)                          (((x) & 0xFF) << 8)
#define BIT_PMU_APB_R5PLL_DELAY_RST_ASSERT(x)                      (((x) & 0xFF))

/* REG_PMU_APB_PCIEPLL_H_RST_CTRL_CFG */

#define BIT_PMU_APB_PCIEPLL_H_RST_CTRL_BYPASS                      BIT(24)
#define BIT_PMU_APB_PCIEPLL_H_DELAY_PWR_ON(x)                      (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PCIEPLL_H_DELAY_EN_OFF(x)                      (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PCIEPLL_H_DELAY_RST_ASSERT(x)                  (((x) & 0xFF))

/* REG_PMU_APB_PCIE_SLP_CFG */

#define BIT_PMU_APB_AP_CP_HANDSHK(x)                               (((x) & 0x1F) << 7)
#define BIT_PMU_APB_PCIE_CLKREQ_PLL_GATE_MASK                      BIT(6)
#define BIT_PMU_APB_PERST_AP_WAKEUP_EN                             BIT(5)
#define BIT_PMU_APB_REG_PERST_N_ASSERT                             BIT(4)
#define BIT_PMU_APB_PERST_N_AUTO_EN                                BIT(3)
#define BIT_PMU_APB_PCIE_LOAD_DONE                                 BIT(2)
#define BIT_PMU_APB_RCO_PCIE_L2_SEL                                BIT(1)
#define BIT_PMU_APB_PCIE_L2_DSLP_MASK                              BIT(0)

/* REG_PMU_APB_GIC_CFG */

#define BIT_PMU_APB_GICDISABLE                                     BIT(0)

/* REG_PMU_APB_FIREWALL_WAKEUP_PUB */

#define BIT_PMU_APB_FW_WAKEUP_DDR_EN                               BIT(0)

/* REG_PMU_APB_PD_ESE_SYS_CFG */

#define BIT_PMU_APB_PD_ESE_SYS_FORCE_SHUTDOWN                      BIT(25)
#define BIT_PMU_APB_PD_ESE_SYS_AUTO_SHUTDOWN_EN                    BIT(24)
#define BIT_PMU_APB_PD_ESE_SYS_PWR_ON_DLY(x)                       (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_ESE_SYS_PWR_ON_SEQ_DLY(x)                   (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_ESE_SYS_ISO_ON_DLY(x)                       (((x) & 0xFF))

/* REG_PMU_APB_APCPU_MODE_ST_CFG */

#define BIT_PMU_APB_APCPU_CORINTH_RAM_PWR_DLY(x)                   (((x) & 0xFF) << 24)
#define BIT_PMU_APB_APCPU_CORE_RAM_PWR_DLY(x)                      (((x) & 0xFF) << 16)
#define BIT_PMU_APB_APCPU_CORE_INITIAL_DLY(x)                      (((x) & 0xFF) << 8)
#define BIT_PMU_APB_APCPU_CORINTH_INITIAL_DLY(x)                   (((x) & 0xFF))

/* REG_PMU_APB_APCPU_C0_SIMD_RET_MODE */

#define BIT_PMU_APB_APCPU_CORE0_SIMD_RET_MODE(x)                   (((x) & 0x7))

/* REG_PMU_APB_APCPU_C1_SIMD_RET_MODE */

#define BIT_PMU_APB_APCPU_CORE1_SIMD_RET_MODE(x)                   (((x) & 0x7))

/* REG_PMU_APB_APCPU_C2_SIMD_RET_MODE */

#define BIT_PMU_APB_APCPU_CORE2_SIMD_RET_MODE(x)                   (((x) & 0x7))

/* REG_PMU_APB_APCPU_C3_SIMD_RET_MODE */

#define BIT_PMU_APB_APCPU_CORE3_SIMD_RET_MODE(x)                   (((x) & 0x7))

/* REG_PMU_APB_APCPU_CORE_FORCE_STOP */

#define BIT_PMU_APB_APCPU_TOP_FORCE_DEEP_STOP                      BIT(8)
#define BIT_PMU_APB_APCPU_CORE_FORCE_STOP(x)                       (((x) & 0xFF))

/* REG_PMU_APB_PD_GPU_TOP_CFG1 */

#define BIT_PMU_APB_PD_GPU_TOP_SHUTDOWN_DLY(x)                     (((x) & 0xFF) << 24)
#define BIT_PMU_APB_PD_GPU_TOP_RST_DEASSERT_DLY(x)                 (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_GPU_TOP_RST_ASSERT_DLY(x)                   (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_GPU_TOP_ISO_OFF_DLY(x)                      (((x) & 0xFF))

/* REG_PMU_APB_MPLL_WAIT_CLK_DIV_CFG */

#define BIT_PMU_APB_MPLL_WAIT_CLK_DIV_CFG(x)                       (((x) & 0xFFFF))

/* REG_PMU_APB_MPLL0_RST_CTRL_CFG */

#define BIT_PMU_APB_MPLL0_RST_CTRL_BYPASS                          BIT(24)
#define BIT_PMU_APB_MPLL0_DELAY_PWR_ON(x)                          (((x) & 0xFF) << 16)
#define BIT_PMU_APB_MPLL0_DELAY_EN_OFF(x)                          (((x) & 0xFF) << 8)
#define BIT_PMU_APB_MPLL0_DELAY_RST_ASSERT(x)                      (((x) & 0xFF))

/* REG_PMU_APB_MPLL1_RST_CTRL_CFG */

#define BIT_PMU_APB_MPLL1_RST_CTRL_BYPASS                          BIT(24)
#define BIT_PMU_APB_MPLL1_DELAY_PWR_ON(x)                          (((x) & 0xFF) << 16)
#define BIT_PMU_APB_MPLL1_DELAY_EN_OFF(x)                          (((x) & 0xFF) << 8)
#define BIT_PMU_APB_MPLL1_DELAY_RST_ASSERT(x)                      (((x) & 0xFF))

/* REG_PMU_APB_R8PLL_RST_CTRL_CFG */

#define BIT_PMU_APB_R8PLL_RST_CTRL_BYPASS                          BIT(24)
#define BIT_PMU_APB_R8PLL_DELAY_PWR_ON(x)                          (((x) & 0xFF) << 16)
#define BIT_PMU_APB_R8PLL_DELAY_EN_OFF(x)                          (((x) & 0xFF) << 8)
#define BIT_PMU_APB_R8PLL_DELAY_RST_ASSERT(x)                      (((x) & 0xFF))

/* REG_PMU_APB_NR_CPUPLL_RST_CTRL_CFG */

#define BIT_PMU_APB_NR_CPUPLL_RST_CTRL_BYPASS                      BIT(24)
#define BIT_PMU_APB_NR_CPUPLL_DELAY_PWR_ON(x)                      (((x) & 0xFF) << 16)
#define BIT_PMU_APB_NR_CPUPLL_DELAY_EN_OFF(x)                      (((x) & 0xFF) << 8)
#define BIT_PMU_APB_NR_CPUPLL_DELAY_RST_ASSERT(x)                  (((x) & 0xFF))

/* REG_PMU_APB_DPLL0_RST_CTRL_CFG */

#define BIT_PMU_APB_DPLL0_RST_CTRL_BYPASS                          BIT(24)
#define BIT_PMU_APB_DPLL0_DELAY_PWR_ON(x)                          (((x) & 0xFF) << 16)
#define BIT_PMU_APB_DPLL0_DELAY_EN_OFF(x)                          (((x) & 0xFF) << 8)
#define BIT_PMU_APB_DPLL0_DELAY_RST_ASSERT(x)                      (((x) & 0xFF))

/* REG_PMU_APB_DPLL1_RST_CTRL_CFG */

#define BIT_PMU_APB_DPLL1_RST_CTRL_BYPASS                          BIT(24)
#define BIT_PMU_APB_DPLL1_DELAY_PWR_ON(x)                          (((x) & 0xFF) << 16)
#define BIT_PMU_APB_DPLL1_DELAY_EN_OFF(x)                          (((x) & 0xFF) << 8)
#define BIT_PMU_APB_DPLL1_DELAY_RST_ASSERT(x)                      (((x) & 0xFF))

/* REG_PMU_APB_V3PLL_RST_CTRL_CFG */

#define BIT_PMU_APB_V3PLL_RST_CTRL_BYPASS                          BIT(24)
#define BIT_PMU_APB_V3PLL_DELAY_PWR_ON(x)                          (((x) & 0xFF) << 16)
#define BIT_PMU_APB_V3PLL_DELAY_EN_OFF(x)                          (((x) & 0xFF) << 8)
#define BIT_PMU_APB_V3PLL_DELAY_RST_ASSERT(x)                      (((x) & 0xFF))

/* REG_PMU_APB_NRPLL_RST_CTRL_CFG */

#define BIT_PMU_APB_NRPLL_RST_CTRL_BYPASS                          BIT(24)
#define BIT_PMU_APB_NRPLL_DELAY_PWR_ON(x)                          (((x) & 0xFF) << 16)
#define BIT_PMU_APB_NRPLL_DELAY_EN_OFF(x)                          (((x) & 0xFF) << 8)
#define BIT_PMU_APB_NRPLL_DELAY_RST_ASSERT(x)                      (((x) & 0xFF))

/* REG_PMU_APB_NR_DSPPLL_RST_CTRL_CFG */

#define BIT_PMU_APB_NR_DSPPLL_RST_CTRL_BYPASS                      BIT(24)
#define BIT_PMU_APB_NR_DSPPLL_DELAY_PWR_ON(x)                      (((x) & 0xFF) << 16)
#define BIT_PMU_APB_NR_DSPPLL_DELAY_EN_OFF(x)                      (((x) & 0xFF) << 8)
#define BIT_PMU_APB_NR_DSPPLL_DELAY_RST_ASSERT(x)                  (((x) & 0xFF))

/* REG_PMU_APB_V3_RPLL_RST_CTRL_CFG */

#define BIT_PMU_APB_V3_RPLL_RST_CTRL_BYPASS                        BIT(24)
#define BIT_PMU_APB_V3_RPLL_DELAY_PWR_ON(x)                        (((x) & 0xFF) << 16)
#define BIT_PMU_APB_V3_RPLL_DELAY_EN_OFF(x)                        (((x) & 0xFF) << 8)
#define BIT_PMU_APB_V3_RPLL_DELAY_RST_ASSERT(x)                    (((x) & 0xFF))

/* REG_PMU_APB_NR_RPLL_RST_CTRL_CFG */

#define BIT_PMU_APB_NR_RPLL_RST_CTRL_BYPASS                        BIT(24)
#define BIT_PMU_APB_NR_RPLL_DELAY_PWR_ON(x)                        (((x) & 0xFF) << 16)
#define BIT_PMU_APB_NR_RPLL_DELAY_EN_OFF(x)                        (((x) & 0xFF) << 8)
#define BIT_PMU_APB_NR_RPLL_DELAY_RST_ASSERT(x)                    (((x) & 0xFF))

/* REG_PMU_APB_PLL_RST_CTRL_STATE0 */

#define BIT_PMU_APB_ST_NRPLL_STATE(x)                              (((x) & 0xF) << 28)
#define BIT_PMU_APB_ST_V3PLL_STATE(x)                              (((x) & 0xF) << 24)
#define BIT_PMU_APB_ST_DPLL1_STATE(x)                              (((x) & 0xF) << 20)
#define BIT_PMU_APB_ST_DPLL0_STATE(x)                              (((x) & 0xF) << 16)
#define BIT_PMU_APB_ST_NR_CPUPLL_STATE(x)                          (((x) & 0xF) << 12)
#define BIT_PMU_APB_ST_R8PLL_STATE(x)                              (((x) & 0xF) << 8)
#define BIT_PMU_APB_ST_MPLL1_STATE(x)                              (((x) & 0xF) << 4)
#define BIT_PMU_APB_ST_MPLL0_STATE(x)                              (((x) & 0xF))

/* REG_PMU_APB_PLL_RST_CTRL_STATE1 */

#define BIT_PMU_APB_ST_R5PLL_STATE(x)                              (((x) & 0xF) << 16)
#define BIT_PMU_APB_ST_PCIEPLL_H_STATE(x)                          (((x) & 0xF) << 12)
#define BIT_PMU_APB_ST_NR_RPLL_STATE(x)                            (((x) & 0xF) << 8)
#define BIT_PMU_APB_ST_V3_RPLL_STATE(x)                            (((x) & 0xF) << 4)
#define BIT_PMU_APB_ST_NR_DSPPLL_STATE(x)                          (((x) & 0xF))

/* REG_PMU_APB_ESE_FAST_WAKEUP_CTRL */

#define BIT_PMU_APB_PMU_AUTO_SEL_RCO_EN                            BIT(3)
#define BIT_PMU_APB_ESE_SYS_FAST_WAKEUP_AFTER_RCO                  BIT(2)
#define BIT_PMU_APB_ESE_SYS_DEEP_STOP_TYPE_SEL                     BIT(1)
#define BIT_PMU_APB_ESE_SYS_FAST_WAKEUP_EN                         BIT(0)

/* REG_PMU_APB_NRCP_DSP_TCM_RAM_POWER_CTRL */

#define BIT_PMU_APB_NRCP_DSP_1_TCM_RAM_SHUTDOWN_EN                 BIT(1)
#define BIT_PMU_APB_NRCP_DSP_0_TCM_RAM_SHUTDOWN_EN                 BIT(0)

/* REG_PMU_APB_WTLCP_HU3GE_NEST_DOMAIN_CTRL */

#define BIT_PMU_APB_WTLCP_HU3GE_NEST_DOMAIN_EN                     BIT(0)

/* REG_PMU_APB_DEBUG_RECOV_TYPE_CFG */

#define BIT_PMU_APB_DBG_RECOV_WAIT_BUS_IDLE_EN                     BIT(7)
#define BIT_PMU_APB_DBGRSTREQ_TRIG_DBG_RECOV_EN                    BIT(6)
#define BIT_PMU_APB_APCPU_TOP_SOFT_RST_TRIG_DBG_RECOV_EN           BIT(5)
#define BIT_PMU_APB_APCPU_CLUSTER_SOFT_RST_TRIG_DBG_RECOV_EN       BIT(4)
#define BIT_PMU_APB_DEBUG_RECOV_FORCE_TRIG                         BIT(2)
#define BIT_PMU_APB_DEBUG_RECOV_AUTO_TRIG_EN                       BIT(1)
#define BIT_PMU_APB_DBG_RECOV_RST_TYPE_SEL                         BIT(0)

/* REG_PMU_APB_APCPU_MODE_ST_CFG1 */

#define BIT_PMU_APB_APCPU_CORE_RST_DEASSERT_DLY(x)                 (((x) & 0xFF) << 24)
#define BIT_PMU_APB_APCPU_CORE_RST_ASSERT_DLY(x)                   (((x) & 0xFF) << 16)
#define BIT_PMU_APB_APCPU_CORINTH_RST_DEASSERT_DLY(x)              (((x) & 0xFF) << 8)
#define BIT_PMU_APB_APCPU_CORINTH_RST_ASSERT_DLY(x)                (((x) & 0xFF))

/* REG_PMU_APB_APCPU_MODE_ST_CFG2 */

#define BIT_PMU_APB_APCPU_CORE_CGM_OFF_DLY(x)                      (((x) & 0xFF) << 8)
#define BIT_PMU_APB_APCPU_CORE_CGM_ON_DLY(x)                       (((x) & 0xFF))

/* REG_PMU_APB_APCPU_MODE_ST_CFG3 */

#define BIT_PMU_APB_APCPU_CLUSTER_INITIAL_STATE                    BIT(0)

/* REG_PMU_APB_DEBUG_STATE_MARK */

#define BIT_PMU_APB_APCPU_CORE_DEBUG_RECOV_STATE_CLR(x)            (((x) & 0xFF) << 8)
#define BIT_PMU_APB_APCPU_CORE7_WAKEUP_FROM_DEBUG_RECOV            BIT(7)
#define BIT_PMU_APB_APCPU_CORE6_WAKEUP_FROM_DEBUG_RECOV            BIT(6)
#define BIT_PMU_APB_APCPU_CORE5_WAKEUP_FROM_DEBUG_RECOV            BIT(5)
#define BIT_PMU_APB_APCPU_CORE4_WAKEUP_FROM_DEBUG_RECOV            BIT(4)
#define BIT_PMU_APB_APCPU_CORE3_WAKEUP_FROM_DEBUG_RECOV            BIT(3)
#define BIT_PMU_APB_APCPU_CORE2_WAKEUP_FROM_DEBUG_RECOV            BIT(2)
#define BIT_PMU_APB_APCPU_CORE1_WAKEUP_FROM_DEBUG_RECOV            BIT(1)
#define BIT_PMU_APB_APCPU_CORE0_WAKEUP_FROM_DEBUG_RECOV            BIT(0)

/* REG_PMU_APB_ANANKELITE_MEM_POWER_CFG */

#define BIT_PMU_APB_APCPU_SNOOP_FILTER_RAM_DSLP_EN                 BIT(8)
#define BIT_PMU_APB_APCPU_L3CACHE_TAG_P3_RAM_DSLP_EN               BIT(7)
#define BIT_PMU_APB_APCPU_L3CACHE_TAG_P2_RAM_DSLP_EN               BIT(6)
#define BIT_PMU_APB_APCPU_L3CACHE_TAG_P1_RAM_DSLP_EN               BIT(5)
#define BIT_PMU_APB_APCPU_L3CACHE_TAG_P0_RAM_DSLP_EN               BIT(4)
#define BIT_PMU_APB_APCPU_CORE3_RAM_DSLP_EN                        BIT(3)
#define BIT_PMU_APB_APCPU_CORE2_RAM_DSLP_EN                        BIT(2)
#define BIT_PMU_APB_APCPU_CORE1_RAM_DSLP_EN                        BIT(1)
#define BIT_PMU_APB_APCPU_CORE0_RAM_DSLP_EN                        BIT(0)

/* REG_PMU_APB_APCPU_MODE_ST_FRC_ON_CFG */

#define BIT_PMU_APB_PD_APCPU_C7_FRC_ON_EN                          BIT(7)
#define BIT_PMU_APB_PD_APCPU_C6_FRC_ON_EN                          BIT(6)
#define BIT_PMU_APB_PD_APCPU_C5_FRC_ON_EN                          BIT(5)
#define BIT_PMU_APB_PD_APCPU_C4_FRC_ON_EN                          BIT(4)
#define BIT_PMU_APB_PD_APCPU_C3_FRC_ON_EN                          BIT(3)
#define BIT_PMU_APB_PD_APCPU_C2_FRC_ON_EN                          BIT(2)
#define BIT_PMU_APB_PD_APCPU_C1_FRC_ON_EN                          BIT(1)
#define BIT_PMU_APB_PD_APCPU_C0_FRC_ON_EN                          BIT(0)

/* REG_PMU_APB_APCPU_SOFT_RST_TYPE_CFG */

#define BIT_PMU_APB_APCPU_CORE_SOFT_RST_BYPASS                     BIT(5)
#define BIT_PMU_APB_APCPU_CLUSTER_SOFT_RST_BYPASS                  BIT(4)
#define BIT_PMU_APB_APCPU_SRST_RST_BYPASS                          BIT(3)
#define BIT_PMU_APB_CLUSTER_DBGRSTREQ_EN                           BIT(2)
#define BIT_PMU_APB_APCPU_SOFT_RST_TYPE_SEL                        BIT(1)
#define BIT_PMU_APB_DBGRSTREQ_RST_TYPE_SEL                         BIT(0)

/* REG_PMU_APB_APCPU_CORINTH_SCU_CLK_GATE_CFG */

#define BIT_PMU_APB_APCPU_CORINTH_FUNC_RET_GATE_CLK_EN             BIT(0)

/* REG_PMU_APB_APCPU_PCHANNEL_STATE0 */

#define BIT_PMU_APB_APCPU_CORE7_PCHANNEL_STATE(x)                  (((x) & 0xF) << 28)
#define BIT_PMU_APB_APCPU_CORE6_PCHANNEL_STATE(x)                  (((x) & 0xF) << 24)
#define BIT_PMU_APB_APCPU_CORE5_PCHANNEL_STATE(x)                  (((x) & 0xF) << 20)
#define BIT_PMU_APB_APCPU_CORE4_PCHANNEL_STATE(x)                  (((x) & 0xF) << 16)
#define BIT_PMU_APB_APCPU_CORE3_PCHANNEL_STATE(x)                  (((x) & 0xF) << 12)
#define BIT_PMU_APB_APCPU_CORE2_PCHANNEL_STATE(x)                  (((x) & 0xF) << 8)
#define BIT_PMU_APB_APCPU_CORE1_PCHANNEL_STATE(x)                  (((x) & 0xF) << 4)
#define BIT_PMU_APB_APCPU_CORE0_PCHANNEL_STATE(x)                  (((x) & 0xF))

/* REG_PMU_APB_APCPU_PCHANNEL_STATE1 */

#define BIT_PMU_APB_APCPU_CORINTH_PCHANNEL_STATE(x)                (((x) & 0xF))

/* REG_PMU_APB_APCPU_SOFT_INT_GEN */

#define BIT_PMU_APB_APCPU_CORE7_SOFT_INT                           BIT(7)
#define BIT_PMU_APB_APCPU_CORE6_SOFT_INT                           BIT(6)
#define BIT_PMU_APB_APCPU_CORE5_SOFT_INT                           BIT(5)
#define BIT_PMU_APB_APCPU_CORE4_SOFT_INT                           BIT(4)
#define BIT_PMU_APB_APCPU_CORE3_SOFT_INT                           BIT(3)
#define BIT_PMU_APB_APCPU_CORE2_SOFT_INT                           BIT(2)
#define BIT_PMU_APB_APCPU_CORE1_SOFT_INT                           BIT(1)
#define BIT_PMU_APB_APCPU_CORE0_SOFT_INT                           BIT(0)

/* REG_PMU_APB_DUAL_RAIL_RAM_FORCE_PD_CFG */

#define BIT_PMU_APB_RAM_PD_GPU_RGX_DUST_B_FRC                      BIT(30)
#define BIT_PMU_APB_RAM_PD_APCPU_TOP_FRC                           BIT(29)
#define BIT_PMU_APB_RAM_PD_APCPU_SNOOP_FILTER_FRC                  BIT(28)
#define BIT_PMU_APB_RAM_PD_APCPU_L3CACHE_TAG_P3_FRC                BIT(27)
#define BIT_PMU_APB_RAM_PD_APCPU_L3CACHE_TAG_P2_FRC                BIT(26)
#define BIT_PMU_APB_RAM_PD_APCPU_L3CACHE_TAG_P1_FRC                BIT(25)
#define BIT_PMU_APB_RAM_PD_APCPU_L3CACHE_TAG_P0_FRC                BIT(24)
#define BIT_PMU_APB_RAM_PD_APCPU_CORE3_FRC                         BIT(23)
#define BIT_PMU_APB_RAM_PD_APCPU_CORE2_FRC                         BIT(22)
#define BIT_PMU_APB_RAM_PD_APCPU_CORE1_FRC                         BIT(21)
#define BIT_PMU_APB_RAM_PD_APCPU_CORE0_FRC                         BIT(20)
#define BIT_PMU_APB_RAM_PD_PUBCP_SYS_FRC                           BIT(19)
#define BIT_PMU_APB_RAM_PD_AUDCP_SYS_FRC                           BIT(18)
#define BIT_PMU_APB_RAM_PD_AUDCP_AUDDSP_FRC                        BIT(17)
#define BIT_PMU_APB_RAM_PD_WTLCP_SYS_FRC                           BIT(16)
#define BIT_PMU_APB_RAM_PD_WTLCP_LTE_DPFEC_FRC                     BIT(15)
#define BIT_PMU_APB_RAM_PD_WTLCP_LTE_CE_FRC                        BIT(14)
#define BIT_PMU_APB_RAM_PD_WTLCP_LTE_PROC_FRC                      BIT(13)
#define BIT_PMU_APB_RAM_PD_WTLCP_TD_PROC_FRC                       BIT(12)
#define BIT_PMU_APB_RAM_PD_WTLCP_HU3GE_B_FRC                       BIT(11)
#define BIT_PMU_APB_RAM_PD_WTLCP_HU3GE_A_FRC                       BIT(10)
#define BIT_PMU_APB_RAM_PD_WTLCP_TGDSP_CACHE_FRC                   BIT(9)
#define BIT_PMU_APB_RAM_PD_WTLCP_TGDSP_TCM_FRC                     BIT(8)
#define BIT_PMU_APB_RAM_PD_WTLCP_LDSP_CACHE_FRC                    BIT(7)
#define BIT_PMU_APB_RAM_PD_WTLCP_LDSP_TCM_FRC                      BIT(6)
#define BIT_PMU_APB_RAM_PD_AP_SYS_FRC                              BIT(5)
#define BIT_PMU_APB_RAM_PD_AP_VSP_FRC                              BIT(4)
#define BIT_PMU_APB_RAM_PD_AP_VDSP_FRC                             BIT(3)
#define BIT_PMU_APB_RAM_PD_MM_TOP_FRC                              BIT(2)
#define BIT_PMU_APB_RAM_PD_GPU_TOP_FRC                             BIT(1)
#define BIT_PMU_APB_RAM_PD_GPU_RGX_DUST_A_FRC                      BIT(0)

/* REG_PMU_APB_DUAL_RAIL_RAM_FORCE_SLP_CFG */

#define BIT_PMU_APB_RAM_RET_APCPU_TOP_FRC                          BIT(11)
#define BIT_PMU_APB_RAM_RET_APCPU_SNOOP_FILTER_FRC                 BIT(10)
#define BIT_PMU_APB_RAM_RET_APCPU_L3CACHE_TAG_P3_FRC               BIT(9)
#define BIT_PMU_APB_RAM_RET_APCPU_L3CACHE_TAG_P2_FRC               BIT(8)
#define BIT_PMU_APB_RAM_RET_APCPU_L3CACHE_TAG_P1_FRC               BIT(7)
#define BIT_PMU_APB_RAM_RET_APCPU_L3CACHE_TAG_P0_FRC               BIT(6)
#define BIT_PMU_APB_RAM_RET_APCPU_CORE3_FRC                        BIT(5)
#define BIT_PMU_APB_RAM_RET_APCPU_CORE2_FRC                        BIT(4)
#define BIT_PMU_APB_RAM_RET_APCPU_CORE1_FRC                        BIT(3)
#define BIT_PMU_APB_RAM_RET_APCPU_CORE0_FRC                        BIT(2)
#define BIT_PMU_APB_RAM_SLP_WTLCP_TGDSP_TCM_FRC                    BIT(1)
#define BIT_PMU_APB_RAM_SLP_WTLCP_LDSP_TCM_FRC                     BIT(0)

/* REG_PMU_APB_PUB_DFS_FRQ_SEL */

#define BIT_PMU_APB_PUB_DFS_FREQ_SEL(x)                            (((x) & 0x7))

/* REG_PMU_APB_APCPU_CORE0_SW_PACTIVE */

#define BIT_PMU_APB_PACTIVE_CORE0_SW(x)                            (((x) & 0xF))

/* REG_PMU_APB_APCPU_CORE1_SW_PACTIVE */

#define BIT_PMU_APB_PACTIVE_CORE1_SW(x)                            (((x) & 0xF))

/* REG_PMU_APB_APCPU_CORE2_SW_PACTIVE */

#define BIT_PMU_APB_PACTIVE_CORE2_SW(x)                            (((x) & 0xF))

/* REG_PMU_APB_APCPU_CORE3_SW_PACTIVE */

#define BIT_PMU_APB_PACTIVE_CORE3_SW(x)                            (((x) & 0xF))

/* REG_PMU_APB_APCPU_CORE4_SW_PACTIVE */

#define BIT_PMU_APB_PACTIVE_CORE4_SW(x)                            (((x) & 0xF))

/* REG_PMU_APB_APCPU_CORE5_SW_PACTIVE */

#define BIT_PMU_APB_PACTIVE_CORE5_SW(x)                            (((x) & 0xF))

/* REG_PMU_APB_APCPU_CORE6_SW_PACTIVE */

#define BIT_PMU_APB_PACTIVE_CORE6_SW(x)                            (((x) & 0xF))

/* REG_PMU_APB_APCPU_CORE7_SW_PACTIVE */

#define BIT_PMU_APB_PACTIVE_CORE7_SW(x)                            (((x) & 0xF))

/* REG_PMU_APB_APCPU_CLUSTER_SW_PACTIVE */

#define BIT_PMU_APB_PACTIVE_CLUSTER_SW(x)                          (((x) & 0x7F))

/* REG_PMU_APB_SOFTWARE_APCPU_PACTIVE_ENABLE */

#define BIT_PMU_APB_APCPU_CLUSTER_SW_PACTIVE_EN                    BIT(8)
#define BIT_PMU_APB_APCPU_CORE7_SW_PACTIVE_EN                      BIT(7)
#define BIT_PMU_APB_APCPU_CORE6_SW_PACTIVE_EN                      BIT(6)
#define BIT_PMU_APB_APCPU_CORE5_SW_PACTIVE_EN                      BIT(5)
#define BIT_PMU_APB_APCPU_CORE4_SW_PACTIVE_EN                      BIT(4)
#define BIT_PMU_APB_APCPU_CORE3_SW_PACTIVE_EN                      BIT(3)
#define BIT_PMU_APB_APCPU_CORE2_SW_PACTIVE_EN                      BIT(2)
#define BIT_PMU_APB_APCPU_CORE1_SW_PACTIVE_EN                      BIT(1)
#define BIT_PMU_APB_APCPU_CORE0_SW_PACTIVE_EN                      BIT(0)

/* REG_PMU_APB_SOFTWARE_APCPU_PCHANNEL_HANDSHAKE_ENABLE */

#define BIT_PMU_APB_APCPU_CLUSTER_SW_PCHANNEL_EN                   BIT(8)
#define BIT_PMU_APB_APCPU_CORE7_SW_PCHANNEL_EN                     BIT(7)
#define BIT_PMU_APB_APCPU_CORE6_SW_PCHANNEL_EN                     BIT(6)
#define BIT_PMU_APB_APCPU_CORE5_SW_PCHANNEL_EN                     BIT(5)
#define BIT_PMU_APB_APCPU_CORE4_SW_PCHANNEL_EN                     BIT(4)
#define BIT_PMU_APB_APCPU_CORE3_SW_PCHANNEL_EN                     BIT(3)
#define BIT_PMU_APB_APCPU_CORE2_SW_PCHANNEL_EN                     BIT(2)
#define BIT_PMU_APB_APCPU_CORE1_SW_PCHANNEL_EN                     BIT(1)
#define BIT_PMU_APB_APCPU_CORE0_SW_PCHANNEL_EN                     BIT(0)

/* REG_PMU_APB_APCPU_CORE0_SW_PCHANNEL_HANDSHAKE */

#define BIT_PMU_APB_APCPU_CORE0_PACTIVE(x)                         (((x) & 0xF) << 12)
#define BIT_PMU_APB_APCPU_CORE0_PDENY                              BIT(11)
#define BIT_PMU_APB_APCPU_CORE0_PACCEPT                            BIT(10)
#define BIT_PMU_APB_MODE_ST_CORE0_CGM_EN_SW                        BIT(9)
#define BIT_PMU_APB_RAM_RET_APCPU_CORE0_SW                         BIT(8)
#define BIT_PMU_APB_RAM_PD_APCPU_CORE0_SW                          BIT(7)
#define BIT_PMU_APB_RST_APCPU_CORE0_WARM_SW_N                      BIT(6)
#define BIT_PMU_APB_RST_APCPU_CORE0_COLD_SW_N                      BIT(5)
#define BIT_PMU_APB_APCPU_CORE0_PSTATE_SW(x)                       (((x) & 0xF) << 1)
#define BIT_PMU_APB_APCPU_CORE0_PREQ_SW                            BIT(0)

/* REG_PMU_APB_APCPU_CORE1_SW_PCHANNEL_HANDSHAKE */

#define BIT_PMU_APB_APCPU_CORE1_PACTIVE(x)                         (((x) & 0xF) << 12)
#define BIT_PMU_APB_APCPU_CORE1_PDENY                              BIT(11)
#define BIT_PMU_APB_APCPU_CORE1_PACCEPT                            BIT(10)
#define BIT_PMU_APB_MODE_ST_CORE1_CGM_EN_SW                        BIT(9)
#define BIT_PMU_APB_RAM_RET_APCPU_CORE1_SW                         BIT(8)
#define BIT_PMU_APB_RAM_PD_APCPU_CORE1_SW                          BIT(7)
#define BIT_PMU_APB_RST_APCPU_CORE1_WARM_SW_N                      BIT(6)
#define BIT_PMU_APB_RST_APCPU_CORE1_COLD_SW_N                      BIT(5)
#define BIT_PMU_APB_APCPU_CORE1_PSTATE_SW(x)                       (((x) & 0xF) << 1)
#define BIT_PMU_APB_APCPU_CORE1_PREQ_SW                            BIT(0)

/* REG_PMU_APB_APCPU_CORE2_SW_PCHANNEL_HANDSHAKE */

#define BIT_PMU_APB_APCPU_CORE2_PACTIVE(x)                         (((x) & 0xF) << 12)
#define BIT_PMU_APB_APCPU_CORE2_PDENY                              BIT(11)
#define BIT_PMU_APB_APCPU_CORE2_PACCEPT                            BIT(10)
#define BIT_PMU_APB_MODE_ST_CORE2_CGM_EN_SW                        BIT(9)
#define BIT_PMU_APB_RAM_RET_APCPU_CORE2_SW                         BIT(8)
#define BIT_PMU_APB_RAM_PD_APCPU_CORE2_SW                          BIT(7)
#define BIT_PMU_APB_RST_APCPU_CORE2_WARM_SW_N                      BIT(6)
#define BIT_PMU_APB_RST_APCPU_CORE2_COLD_SW_N                      BIT(5)
#define BIT_PMU_APB_APCPU_CORE2_PSTATE_SW(x)                       (((x) & 0xF) << 1)
#define BIT_PMU_APB_APCPU_CORE2_PREQ_SW                            BIT(0)

/* REG_PMU_APB_APCPU_CORE3_SW_PCHANNEL_HANDSHAKE */

#define BIT_PMU_APB_APCPU_CORE3_PACTIVE(x)                         (((x) & 0xF) << 12)
#define BIT_PMU_APB_APCPU_CORE3_PDENY                              BIT(11)
#define BIT_PMU_APB_APCPU_CORE3_PACCEPT                            BIT(10)
#define BIT_PMU_APB_MODE_ST_CORE3_CGM_EN_SW                        BIT(9)
#define BIT_PMU_APB_RAM_RET_APCPU_CORE3_SW                         BIT(8)
#define BIT_PMU_APB_RAM_PD_APCPU_CORE3_SW                          BIT(7)
#define BIT_PMU_APB_RST_APCPU_CORE3_WARM_SW_N                      BIT(6)
#define BIT_PMU_APB_RST_APCPU_CORE3_COLD_SW_N                      BIT(5)
#define BIT_PMU_APB_APCPU_CORE3_PSTATE_SW(x)                       (((x) & 0xF) << 1)
#define BIT_PMU_APB_APCPU_CORE3_PREQ_SW                            BIT(0)

/* REG_PMU_APB_APCPU_CORE4_SW_PCHANNEL_HANDSHAKE */

#define BIT_PMU_APB_APCPU_CORE4_PACTIVE(x)                         (((x) & 0xF) << 10)
#define BIT_PMU_APB_APCPU_CORE4_PDENY                              BIT(9)
#define BIT_PMU_APB_APCPU_CORE4_PACCEPT                            BIT(8)
#define BIT_PMU_APB_RST_APCPU_CORE4_WARM_SW_N                      BIT(6)
#define BIT_PMU_APB_RST_APCPU_CORE4_COLD_SW_N                      BIT(5)
#define BIT_PMU_APB_APCPU_CORE4_PSTATE_SW(x)                       (((x) & 0xF) << 1)
#define BIT_PMU_APB_APCPU_CORE4_PREQ_SW                            BIT(0)

/* REG_PMU_APB_APCPU_CORE5_SW_PCHANNEL_HANDSHAKE */

#define BIT_PMU_APB_APCPU_CORE5_PACTIVE(x)                         (((x) & 0xF) << 10)
#define BIT_PMU_APB_APCPU_CORE5_PDENY                              BIT(9)
#define BIT_PMU_APB_APCPU_CORE5_PACCEPT                            BIT(8)
#define BIT_PMU_APB_RST_APCPU_CORE5_WARM_SW_N                      BIT(6)
#define BIT_PMU_APB_RST_APCPU_CORE5_COLD_SW_N                      BIT(5)
#define BIT_PMU_APB_APCPU_CORE5_PSTATE_SW(x)                       (((x) & 0xF) << 1)
#define BIT_PMU_APB_APCPU_CORE5_PREQ_SW                            BIT(0)

/* REG_PMU_APB_APCPU_CORE6_SW_PCHANNEL_HANDSHAKE */

#define BIT_PMU_APB_APCPU_CORE6_PACTIVE(x)                         (((x) & 0xF) << 10)
#define BIT_PMU_APB_APCPU_CORE6_PDENY                              BIT(9)
#define BIT_PMU_APB_APCPU_CORE6_PACCEPT                            BIT(8)
#define BIT_PMU_APB_RST_APCPU_CORE6_WARM_SW_N                      BIT(6)
#define BIT_PMU_APB_RST_APCPU_CORE6_COLD_SW_N                      BIT(5)
#define BIT_PMU_APB_APCPU_CORE6_PSTATE_SW(x)                       (((x) & 0xF) << 1)
#define BIT_PMU_APB_APCPU_CORE6_PREQ_SW                            BIT(0)

/* REG_PMU_APB_APCPU_CORE7_SW_PCHANNEL_HANDSHAKE */

#define BIT_PMU_APB_APCPU_CORE7_PACTIVE(x)                         (((x) & 0xF) << 10)
#define BIT_PMU_APB_APCPU_CORE7_PDENY                              BIT(9)
#define BIT_PMU_APB_APCPU_CORE7_PACCEPT                            BIT(8)
#define BIT_PMU_APB_RST_APCPU_CORE7_WARM_SW_N                      BIT(6)
#define BIT_PMU_APB_RST_APCPU_CORE7_COLD_SW_N                      BIT(5)
#define BIT_PMU_APB_APCPU_CORE7_PSTATE_SW(x)                       (((x) & 0xF) << 1)
#define BIT_PMU_APB_APCPU_CORE7_PREQ_SW                            BIT(0)

/* REG_PMU_APB_APCPU_CLUSTER_SW_PCHANNEL_HANDSHAKE */

#define BIT_PMU_APB_RAM_RET_APCPU_SNOOP_FILTER_SW                  BIT(28)
#define BIT_PMU_APB_RAM_PD_APCPU_SNOOP_FILTER_SW                   BIT(27)
#define BIT_PMU_APB_RAM_RET_APCPU_L3CACHE_TAG_P3_SW                BIT(26)
#define BIT_PMU_APB_RAM_PD_APCPU_L3CACHE_TAG_P3_SW                 BIT(25)
#define BIT_PMU_APB_RAM_RET_APCPU_L3CACHE_TAG_P2_SW                BIT(24)
#define BIT_PMU_APB_RAM_PD_APCPU_L3CACHE_TAG_P2_SW                 BIT(23)
#define BIT_PMU_APB_RAM_RET_APCPU_L3CACHE_TAG_P1_SW                BIT(22)
#define BIT_PMU_APB_RAM_PD_APCPU_L3CACHE_TAG_P1_SW                 BIT(21)
#define BIT_PMU_APB_RAM_RET_APCPU_L3CACHE_TAG_P0_SW                BIT(20)
#define BIT_PMU_APB_RAM_PD_APCPU_L3CACHE_TAG_P0_SW                 BIT(19)
#define BIT_PMU_APB_APCPU_CLUSTER_PACTIVE(x)                       (((x) & 0x7F) << 12)
#define BIT_PMU_APB_APCPU_CLUSTER_PDENY                            BIT(11)
#define BIT_PMU_APB_APCPU_CLUSTER_PACCEPT                          BIT(10)
#define BIT_PMU_APB_RST_APCPU_CLUSTER_WARM_SW_N                    BIT(9)
#define BIT_PMU_APB_RST_APCPU_CLUSTER_COLD_SW_N                    BIT(8)
#define BIT_PMU_APB_APCPU_CLUSTER_PSTATE_SW(x)                     (((x) & 0x7F) << 1)
#define BIT_PMU_APB_APCPU_CLUSTER_PREQ_SW                          BIT(0)

/* REG_PMU_APB_WTLCP_DPFEC_NEST_DOMAIN_CTRL */

#define BIT_PMU_APB_WTLCP_DPFEC_NEST_DOMAIN_EN                     BIT(0)

/* REG_PMU_APB_GPIO_FORCE_GATING_PLL_CFG */

#define BIT_PMU_APB_GPLL_GPIO_FORCE_GATING_DISABLE                 BIT(4)
#define BIT_PMU_APB_MPLL2_GPIO_FORCE_GATING_DISABLE                BIT(2)
#define BIT_PMU_APB_MPLL1_GPIO_FORCE_GATING_DISABLE                BIT(1)
#define BIT_PMU_APB_MPLL0_GPIO_FORCE_GATING_DISABLE                BIT(0)

/* REG_PMU_APB_ANALOG_PHY_PWRON_CFG */

#define BIT_PMU_APB_CSI_2P2LANE_PWRON_REG                          BIT(4)
#define BIT_PMU_APB_DSI_PWRON_REG                                  BIT(3)
#define BIT_PMU_APB_PCIE2_PWRON_REG                                BIT(2)
#define BIT_PMU_APB_CSI_4LANE1_PWRON_REG                           BIT(1)
#define BIT_PMU_APB_CSI_4LANE0_PWRON_REG                           BIT(0)

/* REG_PMU_APB_APCPU_MODE_ST_CGM_EN_CFG */

#define BIT_PMU_APB_APCPU_CORE3_MODE_ST_CGM_EN_DISABLE             BIT(3)
#define BIT_PMU_APB_APCPU_CORE2_MODE_ST_CGM_EN_DISABLE             BIT(2)
#define BIT_PMU_APB_APCPU_CORE1_MODE_ST_CGM_EN_DISABLE             BIT(1)
#define BIT_PMU_APB_APCPU_CORE0_MODE_ST_CGM_EN_DISABLE             BIT(0)

/* REG_PMU_APB_APCPU_DENY_TIME_THRESHOLD_CFG */

#define BIT_PMU_APB_APCPU_CLUSTER_DENY_TIME_THRESHOLD(x)           (((x) & 0x3F) << 6)
#define BIT_PMU_APB_APCPU_CORE_DENY_TIME_THRESHOLD(x)              (((x) & 0x3F))

/* REG_PMU_APB_INT_REQ_APCPU_MODE_ST_ENABLE */

#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CLUSTER_EN               BIT(8)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE7_EN                 BIT(7)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE6_EN                 BIT(6)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE5_EN                 BIT(5)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE4_EN                 BIT(4)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE3_EN                 BIT(3)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE2_EN                 BIT(2)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE1_EN                 BIT(1)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE0_EN                 BIT(0)

/* REG_PMU_APB_INT_REQ_APCPU_MODE_ST_CLR */

#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CLUSTER_CLR              BIT(8)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE7_CLR                BIT(7)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE6_CLR                BIT(6)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE5_CLR                BIT(5)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE4_CLR                BIT(4)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE3_CLR                BIT(3)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE2_CLR                BIT(2)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE1_CLR                BIT(1)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE0_CLR                BIT(0)

/* REG_PMU_APB_INT_REQ_MODE_ST_RECORD */

#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CLUSTER                  BIT(8)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE7                    BIT(7)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE6                    BIT(6)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE5                    BIT(5)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE4                    BIT(4)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE3                    BIT(3)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE2                    BIT(2)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE1                    BIT(1)
#define BIT_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE0                    BIT(0)

/* REG_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE0_INF */

#define BIT_PMU_APB_APCPU_CORE0_DENY_TAR_STATE(x)                  (((x) & 0x1F) << 5)
#define BIT_PMU_APB_APCPU_CORE0_DENY_PRE_STATE(x)                  (((x) & 0x1F))

/* REG_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE1_INF */

#define BIT_PMU_APB_APCPU_CORE1_DENY_TAR_STATE(x)                  (((x) & 0x1F) << 5)
#define BIT_PMU_APB_APCPU_CORE1_DENY_PRE_STATE(x)                  (((x) & 0x1F))

/* REG_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE2_INF */

#define BIT_PMU_APB_APCPU_CORE2_DENY_TAR_STATE(x)                  (((x) & 0x1F) << 5)
#define BIT_PMU_APB_APCPU_CORE2_DENY_PRE_STATE(x)                  (((x) & 0x1F))

/* REG_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE3_INF */

#define BIT_PMU_APB_APCPU_CORE3_DENY_TAR_STATE(x)                  (((x) & 0x1F) << 5)
#define BIT_PMU_APB_APCPU_CORE3_DENY_PRE_STATE(x)                  (((x) & 0x1F))

/* REG_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE4_INF */

#define BIT_PMU_APB_APCPU_CORE4_DENY_TAR_STATE(x)                  (((x) & 0x1F) << 5)
#define BIT_PMU_APB_APCPU_CORE4_DENY_PRE_STATE(x)                  (((x) & 0x1F))

/* REG_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE5_INF */

#define BIT_PMU_APB_APCPU_CORE5_DENY_TAR_STATE(x)                  (((x) & 0x1F) << 5)
#define BIT_PMU_APB_APCPU_CORE5_DENY_PRE_STATE(x)                  (((x) & 0x1F))

/* REG_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE6_INF */

#define BIT_PMU_APB_APCPU_CORE6_DENY_TAR_STATE(x)                  (((x) & 0x1F) << 5)
#define BIT_PMU_APB_APCPU_CORE6_DENY_PRE_STATE(x)                  (((x) & 0x1F))

/* REG_PMU_APB_INT_REQ_MODE_ST_APCPU_CORE7_INF */

#define BIT_PMU_APB_APCPU_CORE7_DENY_TAR_STATE(x)                  (((x) & 0x1F) << 5)
#define BIT_PMU_APB_APCPU_CORE7_DENY_PRE_STATE(x)                  (((x) & 0x1F))

/* REG_PMU_APB_INT_REQ_MODE_ST_APCPU_CLUSTER_INF */

#define BIT_PMU_APB_APCPU_CLUSTER_DENY_TAR_STATE(x)                (((x) & 0x3F) << 6)
#define BIT_PMU_APB_APCPU_CLUSTER_DENY_PRE_STATE(x)                (((x) & 0x3F))

/* REG_PMU_APB_APCPU_CSYSPWRUP_WAKEUP_EN_CFG */

#define BIT_PMU_APB_APCPU_CSYSPWRUP_WAKEUP_EN(x)                   (((x) & 0xFF))

/* REG_PMU_APB_DVFS_BLOCK_SHUTDOWN_CFG */

#define BIT_PMU_APB_DCDC_AI_DVFS_BLOCK_SHUTDOWN_EN                 BIT(2)
#define BIT_PMU_APB_DCDC_CPU1_DVFS_BLOCK_SHUTDOWN_EN               BIT(1)
#define BIT_PMU_APB_DCDC_CPU0_DVFS_BLOCK_SHUTDOWN_EN               BIT(0)

/* REG_PMU_APB_OFF_EMU_CLR_IN_DISABLE_CFG */

#define BIT_PMU_APB_APCPU_CORE7_OFF_EMU_CLR_INT_DISABLE_EN         BIT(7)
#define BIT_PMU_APB_APCPU_CORE6_OFF_EMU_CLR_INT_DISABLE_EN         BIT(6)
#define BIT_PMU_APB_APCPU_CORE5_OFF_EMU_CLR_INT_DISABLE_EN         BIT(5)
#define BIT_PMU_APB_APCPU_CORE4_OFF_EMU_CLR_INT_DISABLE_EN         BIT(4)
#define BIT_PMU_APB_APCPU_CORE3_OFF_EMU_CLR_INT_DISABLE_EN         BIT(3)
#define BIT_PMU_APB_APCPU_CORE2_OFF_EMU_CLR_INT_DISABLE_EN         BIT(2)
#define BIT_PMU_APB_APCPU_CORE1_OFF_EMU_CLR_INT_DISABLE_EN         BIT(1)
#define BIT_PMU_APB_APCPU_CORE0_OFF_EMU_CLR_INT_DISABLE_EN         BIT(0)

/* REG_PMU_APB_APCPU_DUAL_RAIL_RAM_FORCE_ON_CFG */

#define BIT_PMU_APB_APCPU_SNOOP_FILTER_RAM_FRC_ON                  BIT(8)
#define BIT_PMU_APB_APCPU_L3CACHE_TAG_P3_RAM_FRC_ON                BIT(7)
#define BIT_PMU_APB_APCPU_L3CACHE_TAG_P2_RAM_FRC_ON                BIT(6)
#define BIT_PMU_APB_APCPU_L3CACHE_TAG_P1_RAM_FRC_ON                BIT(5)
#define BIT_PMU_APB_APCPU_L3CACHE_TAG_P0_RAM_FRC_ON                BIT(4)
#define BIT_PMU_APB_APCPU_CORE3_RAM_FRC_ON                         BIT(3)
#define BIT_PMU_APB_APCPU_CORE2_RAM_FRC_ON                         BIT(2)
#define BIT_PMU_APB_APCPU_CORE1_RAM_FRC_ON                         BIT(1)
#define BIT_PMU_APB_APCPU_CORE0_RAM_FRC_ON                         BIT(0)

/* REG_PMU_APB_OFF_EMU_TO_OFF_CFG */

#define BIT_PMU_APB_APCPU_CORE7_OFF_EMU_TO_OFF                     BIT(7)
#define BIT_PMU_APB_APCPU_CORE6_OFF_EMU_TO_OFF                     BIT(6)
#define BIT_PMU_APB_APCPU_CORE5_OFF_EMU_TO_OFF                     BIT(5)
#define BIT_PMU_APB_APCPU_CORE4_OFF_EMU_TO_OFF                     BIT(4)
#define BIT_PMU_APB_APCPU_CORE3_OFF_EMU_TO_OFF                     BIT(3)
#define BIT_PMU_APB_APCPU_CORE2_OFF_EMU_TO_OFF                     BIT(2)
#define BIT_PMU_APB_APCPU_CORE1_OFF_EMU_TO_OFF                     BIT(1)
#define BIT_PMU_APB_APCPU_CORE0_OFF_EMU_TO_OFF                     BIT(0)

/* REG_PMU_APB_ALL_PLL_PD_RCO_BYP */

#define BIT_PMU_APB_ALL_PLL_PD_RCO_BYP                             BIT(0)

/* REG_PMU_APB_SP_CLK_GATE_BYP_CFG */

#define BIT_PMU_APB_SP_PWR_PD_AON_MEM_BYP                          BIT(1)
#define BIT_PMU_APB_SP_PWR_PD_SP_MEM_BYP                           BIT(0)

/* REG_PMU_APB_DPLL1_CNT_DONE_BYP */

#define BIT_PMU_APB_LPDDR3_DPLL1_CNT_DONE_BYP                      BIT(0)

/* REG_PMU_APB_SRAM_DLY_CTRL_CFG */

#define BIT_PMU_APB_SP_SRAM_RCO_SYS_SEL                            BIT(3)
#define BIT_PMU_APB_SP_SRAM_XTLBUF0_SYS_SEL                        BIT(2)
#define BIT_PMU_APB_AON_SRAM_RCO_SYS_SEL                           BIT(1)
#define BIT_PMU_APB_AON_SRAM_XTLBUF0_SYS_SEL                       BIT(0)

/* REG_PMU_APB_WDG_TRIG_DBG_RECOV_CFG */

#define BIT_PMU_APB_WDG_RST_TRIG_DBG_RECOV_EN                      BIT(0)

/* REG_PMU_APB_APCPU_TOP_RAM_POWER_CTRL */

#define BIT_PMU_APB_APCPU_TOP_RAM_SHUTDOWN_EN                      BIT(0)

/* REG_PMU_APB_PD_GPU_RGX_DUST_B_CFG0 */

#define BIT_PMU_APB_PD_GPU_RGX_DUST_B_PWRUP_ABORT                  BIT(28)
#define BIT_PMU_APB_PD_GPU_RGX_DUST_B_PWRDWN_ABORT                 BIT(27)
#define BIT_PMU_APB_PD_GPU_RGX_DUST_B_PD_SEL                       BIT(26)
#define BIT_PMU_APB_PD_GPU_RGX_DUST_B_FORCE_SHUTDOWN               BIT(25)
#define BIT_PMU_APB_PD_GPU_RGX_DUST_B_AUTO_SHUTDOWN_EN             BIT(24)
#define BIT_PMU_APB_PD_GPU_RGX_DUST_B_PWR_ON_DLY(x)                (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_GPU_RGX_DUST_B_PWR_ON_SEQ_DLY(x)            (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_GPU_RGX_DUST_B_ISO_ON_DLY(x)                (((x) & 0xFF))

/* REG_PMU_APB_PD_GPU_RGX_DUST_B_CFG1 */

#define BIT_PMU_APB_PD_GPU_RGX_DUST_B_SHUTDOWN_DLY(x)              (((x) & 0xFF) << 24)
#define BIT_PMU_APB_PD_GPU_RGX_DUST_B_RST_DEASSERT_DLY(x)          (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_GPU_RGX_DUST_B_RST_ASSERT_DLY(x)            (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_GPU_RGX_DUST_B_ISO_OFF_DLY(x)               (((x) & 0xFF))

/* REG_PMU_APB_PD_IPA_SYS_CFG */

#define BIT_PMU_APB_PD_IPA_SYS_FORCE_SHUTDOWN                      BIT(25)
#define BIT_PMU_APB_PD_IPA_SYS_AUTO_SHUTDOWN_EN                    BIT(24)
#define BIT_PMU_APB_PD_IPA_SYS_PWR_ON_DLY(x)                       (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_IPA_SYS_PWR_ON_SEQ_DLY(x)                   (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_IPA_SYS_ISO_ON_DLY(x)                       (((x) & 0xFF))

/* REG_PMU_APB_APCPU_MODE_ST_SOFT_RST */

#define BIT_PMU_APB_APCPU_CLUSTER_MODE_ST_SOFT_RST                 BIT(8)
#define BIT_PMU_APB_APCPU_CORE7_MODE_ST_SOFT_RST                   BIT(7)
#define BIT_PMU_APB_APCPU_CORE6_MODE_ST_SOFT_RST                   BIT(6)
#define BIT_PMU_APB_APCPU_CORE5_MODE_ST_SOFT_RST                   BIT(5)
#define BIT_PMU_APB_APCPU_CORE4_MODE_ST_SOFT_RST                   BIT(4)
#define BIT_PMU_APB_APCPU_CORE3_MODE_ST_SOFT_RST                   BIT(3)
#define BIT_PMU_APB_APCPU_CORE2_MODE_ST_SOFT_RST                   BIT(2)
#define BIT_PMU_APB_APCPU_CORE1_MODE_ST_SOFT_RST                   BIT(1)
#define BIT_PMU_APB_APCPU_CORE0_MODE_ST_SOFT_RST                   BIT(0)

/* REG_PMU_APB_FORCE_PUB_DEEP_SLEEP_CFG */

#define BIT_PMU_APB_AUDCP_FORCE_PUB_DEEP_SLEEP                     BIT(0)

/* REG_PMU_APB_FORCE_DEEP_SLEEP_CFG */

#define BIT_PMU_APB_PUB_SYS_FORCE_DEEP_SLEEP                       BIT(7)
#define BIT_PMU_APB_IPA_FORCE_DEEP_SLEEP                           BIT(6)
#define BIT_PMU_APB_SP_SYS_FORCE_DEEP_SLEEP                        BIT(5)
#define BIT_PMU_APB_AUDCP_FORCE_DEEP_SLEEP                         BIT(4)
#define BIT_PMU_APB_PSCP_FORCE_DEEP_SLEEP                          BIT(3)
#define BIT_PMU_APB_V3_MODEM_FORCE_DEEP_SLEEP                      BIT(2)
#define BIT_PMU_APB_AP_FORCE_DEEP_SLEEP                            BIT(1)
#define BIT_PMU_APB_NRCP_FORCE_DEEP_SLEEP                          BIT(0)

/* REG_PMU_APB_FORCE_LIGHT_SLEEP_CFG */

#define BIT_PMU_APB_PUB_SYS_FORCE_LIGHT_SLEEP                      BIT(7)
#define BIT_PMU_APB_IPA_FORCE_LIGHT_SLEEP                          BIT(6)
#define BIT_PMU_APB_NRCP_FORCE_LIGHT_SLEEP                         BIT(5)
#define BIT_PMU_APB_AON_FORCE_LIGHT_SLEEP                          BIT(4)
#define BIT_PMU_APB_PSCP_FORCE_LIGHT_SLEEP                         BIT(3)
#define BIT_PMU_APB_V3_MODEM_FORCE_LIGHT_SLEEP                     BIT(2)
#define BIT_PMU_APB_AUDCP_FORCE_LIGHT_SLEEP                        BIT(1)
#define BIT_PMU_APB_AP_FORCE_LIGHT_SLEEP                           BIT(0)

/* REG_PMU_APB_FORCE_SYSTEM_SLEEP_CFG */

#define BIT_PMU_APB_PUB_SYS_FORCE_SYSTEM_SLEEP                     BIT(9)
#define BIT_PMU_APB_IPA_FORCE_SYSTEM_SLEEP                         BIT(8)
#define BIT_PMU_APB_AUDCP_FORCE_SYSTEM_SLEEP                       BIT(7)
#define BIT_PMU_APB_GPU_TOP_FORCE_SYSTEM_SLEEP                     BIT(6)
#define BIT_PMU_APB_NRCP_FORCE_SYSTEM_SLEEP                        BIT(5)
#define BIT_PMU_APB_PSCP_FORCE_SYSTEM_SLEEP                        BIT(4)
#define BIT_PMU_APB_V3_MODEM_FORCE_SYSTEM_SLEEP                    BIT(3)
#define BIT_PMU_APB_AP_FORCE_SYSTEM_SLEEP                          BIT(2)
#define BIT_PMU_APB_APCPU_FORCE_SYSTEM_SLEEP                       BIT(1)
#define BIT_PMU_APB_AP_ALL_FORCE_SYSTEM_SLEEP                      BIT(0)

/* REG_PMU_APB_ESE_ACCESS_DDR_CFG */

#define BIT_PMU_APB_ESE_ACCESS_DDR_EN                              BIT(0)

/* REG_PMU_APB_PWR_STATUS1_DBG */

#define BIT_PMU_APB_PD_NRCP_SYS_STATE(x)                           (((x) & 0xFF) << 24)
#define BIT_PMU_APB_PD_AP_VSP_STATE(x)                             (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_AP_VDSP_STATE(x)                            (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_AP_SYS_STATE(x)                             (((x) & 0xFF))

/* REG_PMU_APB_PWR_STATUS2_DBG */

#define BIT_PMU_APB_PD_NRCP_UL_STATE(x)                            (((x) & 0xFF) << 24)
#define BIT_PMU_APB_PD_NRCP_DL_STATE(x)                            (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_NRCP_DSP_1_STATE(x)                         (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_NRCP_DSP_0_STATE(x)                         (((x) & 0xFF))

/* REG_PMU_APB_PWR_STATUS3_DBG */

#define BIT_PMU_APB_PD_PUB_SYS_STATE(x)                            (((x) & 0xFF) << 24)
#define BIT_PMU_APB_PD_PSCP_SYS_STATE(x)                           (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_AUDCP_AUDDSP_STATE(x)                       (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_AUDCP_SYS_STATE(x)                          (((x) & 0xFF))

/* REG_PMU_APB_PWR_STATUS4_DBG */

#define BIT_PMU_APB_PD_V3_LCE_STATE(x)                             (((x) & 0xFF) << 24)
#define BIT_PMU_APB_PD_V3_DPFEC_STATE(x)                           (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_V3_WCE_STATE(x)                             (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_V3_LWPROC_STATE(x)                          (((x) & 0xFF))

/* REG_PMU_APB_PWR_STATUS5_DBG */

#define BIT_PMU_APB_PD_V3_PHY_STATE(x)                             (((x) & 0xFF) << 24)
#define BIT_PMU_APB_PD_V3_PS_STATE(x)                              (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_V3_MODEM_STATE(x)                           (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_NRCP_SYNC_STATE(x)                          (((x) & 0xFF))

/* REG_PMU_APB_PWR_STATUS6_DBG */

#define BIT_PMU_APB_PD_APCPU_C3_STATE(x)                           (((x) & 0xFF) << 24)
#define BIT_PMU_APB_PD_APCPU_C2_STATE(x)                           (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_APCPU_C1_STATE(x)                           (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_APCPU_C0_STATE(x)                           (((x) & 0xFF))

/* REG_PMU_APB_PWR_STATUS7_DBG */

#define BIT_PMU_APB_PD_APCPU_C7_STATE(x)                           (((x) & 0xFF) << 24)
#define BIT_PMU_APB_PD_APCPU_C6_STATE(x)                           (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_APCPU_C5_STATE(x)                           (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_APCPU_C4_STATE(x)                           (((x) & 0xFF))

/* REG_PMU_APB_PWR_STATUS8_DBG */

#define BIT_PMU_APB_PD_V3_TD_STATE(x)                              (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_APCPU_TOP_STATE(x)                          (((x) & 0xFF))

/* REG_PMU_APB_APCU_MODE_STATE0 */

#define BIT_PMU_APB_APCPU_CORE3_POWER_MODE_STATE(x)                (((x) & 0xFF) << 24)
#define BIT_PMU_APB_APCPU_CORE2_POWER_MODE_STATE(x)                (((x) & 0xFF) << 16)
#define BIT_PMU_APB_APCPU_CORE1_POWER_MODE_STATE(x)                (((x) & 0xFF) << 8)
#define BIT_PMU_APB_APCPU_CORE0_POWER_MODE_STATE(x)                (((x) & 0xFF))

/* REG_PMU_APB_APCU_MODE_STATE1 */

#define BIT_PMU_APB_APCPU_CORE7_POWER_MODE_STATE(x)                (((x) & 0xFF) << 24)
#define BIT_PMU_APB_APCPU_CORE6_POWER_MODE_STATE(x)                (((x) & 0xFF) << 16)
#define BIT_PMU_APB_APCPU_CORE5_POWER_MODE_STATE(x)                (((x) & 0xFF) << 8)
#define BIT_PMU_APB_APCPU_CORE4_POWER_MODE_STATE(x)                (((x) & 0xFF))

/* REG_PMU_APB_APCU_MODE_STATE2 */

#define BIT_PMU_APB_APCPU_CORINTH_POWER_MODE_STATE(x)              (((x) & 0xFF))

/* REG_PMU_APB_APCPU_WFI_MARK */

#define BIT_PMU_APB_CORE_WFI_MARK_CLR(x)                           (((x) & 0x3) << 8)
#define BIT_PMU_APB_CORE_WFI_MARK(x)                               (((x) & 0x3))

/* REG_PMU_APB_AXI_LP_CTRL_DISABLE */

#define BIT_PMU_APB_AXI_LP_CTRL_DISABLE                            BIT(0)

/* REG_PMU_APB_PD_APCPU_C0_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_APCPU_C0_SHUTDOWN_MARK(x)                   (((x) & 0xF))

/* REG_PMU_APB_PD_APCPU_C1_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_APCPU_C1_SHUTDOWN_MARK(x)                   (((x) & 0xF))

/* REG_PMU_APB_PD_APCPU_C2_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_APCPU_C2_SHUTDOWN_MARK(x)                   (((x) & 0xF))

/* REG_PMU_APB_PD_APCPU_C3_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_APCPU_C3_SHUTDOWN_MARK(x)                   (((x) & 0xF))

/* REG_PMU_APB_PD_APCPU_TOP_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_APCPU_TOP_SHUTDOWN_MARK(x)                  (((x) & 0xF))

/* REG_PMU_APB_PD_AP_SYS_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_AP_SYS_SHUTDOWN_MARK(x)                     (((x) & 0xF))

/* REG_PMU_APB_PD_NRCP_SYS_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_NRCP_SYS_SHUTDOWN_MARK(x)                   (((x) & 0xF))

/* REG_PMU_APB_PD_NRCP_SYNC_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_NRCP_SYNC_SHUTDOWN_MARK(x)                  (((x) & 0xF))

/* REG_PMU_APB_PD_V3_WCE_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_V3_WCE_SHUTDOWN_MARK(x)                     (((x) & 0xF))

/* REG_PMU_APB_PD_V3_LCE_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_V3_LCE_SHUTDOWN_MARK(x)                     (((x) & 0xF))

/* REG_PMU_APB_PD_V3_DPFEC_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_V3_DPFEC_SHUTDOWN_MARK(x)                   (((x) & 0xF))

/* REG_PMU_APB_PD_V3_LWPROC_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_V3_LWPROC_SHUTDOWN_MARK(x)                  (((x) & 0xF))

/* REG_PMU_APB_PD_V3_PHY_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_V3_PHY_SHUTDOWN_MARK(x)                     (((x) & 0xF))

/* REG_PMU_APB_PD_V3_PS_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_V3_PS_SHUTDOWN_MARK(x)                      (((x) & 0xF))

/* REG_PMU_APB_PD_NRCP_DSP_0_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_NRCP_DSP_0_SHUTDOWN_MARK(x)                 (((x) & 0xF))

/* REG_PMU_APB_PD_NRCP_DSP_1_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_NRCP_DSP_1_SHUTDOWN_MARK(x)                 (((x) & 0xF))

/* REG_PMU_APB_PD_V3_MODEM_SYS_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_V3_MODEM_SYS_SHUTDOWN_MARK(x)               (((x) & 0xF))

/* REG_PMU_APB_PD_PSCP_SYS_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_PSCP_SYS_SHUTDOWN_MARK(x)                   (((x) & 0xF))

/* REG_PMU_APB_PD_NRCP_DL_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_NRCP_DL_SHUTDOWN_MARK(x)                    (((x) & 0xF))

/* REG_PMU_APB_PD_V3_TD_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_V3_TD_SHUTDOWN_MARK(x)                      (((x) & 0xF))

/* REG_PMU_APB_PD_AUDCP_SYS_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_AUDCP_SYS_SHUTDOWN_MARK(x)                  (((x) & 0xF))

/* REG_PMU_APB_PD_PUB_SYS_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_PUB_SYS_SHUTDOWN_MARK(x)                    (((x) & 0xF))

/* REG_PMU_APB_PD_AUDCP_AUDDSP_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_AUDCP_AUDDSP_SHUTDOWN_MARK(x)               (((x) & 0xF))

/* REG_PMU_APB_PD_NRCP_UL_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_NRCP_UL_SHUTDOWN_MARK(x)                    (((x) & 0xF))

/* REG_PMU_APB_PD_GPU_RGX_DUST_B_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_GPU_RGX_DUST_B_SHUTDOWN_MARK(x)             (((x) & 0xF))

/* REG_PMU_APB_APCPU_TOP_SLEEP_CNT */

#define BIT_PMU_APB_APCPU_TOP_SYS_SLEEP_CNT(x)                     (((x) & 0xFF))

/* REG_PMU_APB_AP_SYS_SLEEP_CNT */

#define BIT_PMU_APB_AP_SYS_SLEEP_CNT(x)                            (((x) & 0xFF))

/* REG_PMU_APB_V3_MODEM_SYS_SLEEP_CNT */

#define BIT_PMU_APB_V3_MODEM_SYS_SLEEP_CNT(x)                      (((x) & 0xFF))

/* REG_PMU_APB_PSCP_SYS_SLEEP_CNT */

#define BIT_PMU_APB_PSCP_SYS_SLEEP_CNT(x)                          (((x) & 0xFF))

/* REG_PMU_APB_AUDCP_SYS_SLEEP_CNT */

#define BIT_PMU_APB_AUDCP_SYS_SLEEP_CNT(x)                         (((x) & 0xFF))

/* REG_PMU_APB_PUB_SYS_LIGHT_SLEEP_CNT */

#define BIT_PMU_APB_PUB_SYS_LIGHT_SLEEP_CNT(x)                     (((x) & 0xFF))

/* REG_PMU_APB_AP_DEEP_SLEEP_CNT */

#define BIT_PMU_APB_AP_DEEP_SLEEP_CNT(x)                           (((x) & 0xFF))

/* REG_PMU_APB_SP_SYS_DEEP_SLEEP_CNT */

#define BIT_PMU_APB_SP_SYS_DEEP_SLEEP_CNT(x)                       (((x) & 0xFF))

/* REG_PMU_APB_V3_MODEM_DEEP_SLEEP_CNT */

#define BIT_PMU_APB_V3_MODEM_DEEP_SLEEP_CNT(x)                     (((x) & 0xFF))

/* REG_PMU_APB_PSCP_DEEP_SLEEP_CNT */

#define BIT_PMU_APB_PSCP_DEEP_SLEEP_CNT(x)                         (((x) & 0xFF))

/* REG_PMU_APB_AUDCP_SYS_DEEP_SLEEP_CNT */

#define BIT_PMU_APB_AUDCP_SYS_DEEP_SLEEP_CNT(x)                    (((x) & 0xFF))

/* REG_PMU_APB_PUB_SYS_DEEP_SLEEP_CNT */

#define BIT_PMU_APB_PUB_SYS_DEEP_SLEEP_CNT(x)                      (((x) & 0xFF))

/* REG_PMU_APB_AP_LIGHT_SLEEP_CNT */

#define BIT_PMU_APB_AP_LIGHT_SLEEP_CNT(x)                          (((x) & 0xFF))

/* REG_PMU_APB_V3_MODEM_LIGHT_SLEEP_CNT */

#define BIT_PMU_APB_V3_MODEM_LIGHT_SLEEP_CNT(x)                    (((x) & 0xFF))

/* REG_PMU_APB_PSCP_LIGHT_SLEEP_CNT */

#define BIT_PMU_APB_PSCP_LIGHT_SLEEP_CNT(x)                        (((x) & 0xFF))

/* REG_PMU_APB_AUDCP_SYS_LIGHT_SLEEP_CNT */

#define BIT_PMU_APB_AUDCP_LIGHT_SLEEP_CNT(x)                       (((x) & 0xFF))

/* REG_PMU_APB_AON_SYS_LIGHT_SLEEP_CNT */

#define BIT_PMU_APB_AON_LIGHT_SLEEP_CNT(x)                         (((x) & 0xFF))

/* REG_PMU_APB_SYS_SOFT_RST_BUSY */

#define BIT_PMU_APB_IPA_SYS_SRST_BUSY                              BIT(9)
#define BIT_PMU_APB_AI_SYS_SRST_BUSY                               BIT(8)
#define BIT_PMU_APB_NRCP_SYS_SRST_BUSY                             BIT(7)
#define BIT_PMU_APB_AUDCP_SYS_SRST_BUSY                            BIT(6)
#define BIT_PMU_APB_AP_SYS_SRST_BUSY                               BIT(5)
#define BIT_PMU_APB_APCPU_SYS_SRST_BUSY                            BIT(4)
#define BIT_PMU_APB_GPU_SYS_SRST_BUSY                              BIT(3)
#define BIT_PMU_APB_MM_SYS_SRST_BUSY                               BIT(2)
#define BIT_PMU_APB_V3_MODEM_SYS_SRST_BUSY                         BIT(1)
#define BIT_PMU_APB_PSCP_SYS_SRST_BUSY                             BIT(0)

/* REG_PMU_APB_REG_SYS_SRST_FRC_LP_ACK */

#define BIT_PMU_APB_REG_IPA_SRST_FRC_LP_ACK                        BIT(9)
#define BIT_PMU_APB_REG_AI_SRST_FRC_LP_ACK                         BIT(8)
#define BIT_PMU_APB_REG_NRCP_SRST_FRC_LP_ACK                       BIT(7)
#define BIT_PMU_APB_REG_AUDCP_SRST_FRC_LP_ACK                      BIT(6)
#define BIT_PMU_APB_REG_AP_SRST_FRC_LP_ACK                         BIT(5)
#define BIT_PMU_APB_REG_APCPU_SRST_FRC_LP_ACK                      BIT(4)
#define BIT_PMU_APB_REG_GPU_SRST_FRC_LP_ACK                        BIT(3)
#define BIT_PMU_APB_REG_MM_SRST_FRC_LP_ACK                         BIT(2)
#define BIT_PMU_APB_REG_V3_MODEM_SRST_FRC_LP_ACK                   BIT(1)
#define BIT_PMU_APB_REG_PSCP_SRST_FRC_LP_ACK                       BIT(0)

/* REG_PMU_APB_SOFT_RST_SEL */

#define BIT_PMU_APB_SOFT_RST_SEL(x)                                (((x) & 0x3FF))

/* REG_PMU_APB_REG_SYS_DDR_PWR_HS_ACK */

#define BIT_PMU_APB_REG_CS_SYS_DDR_PWR_HS_ACK                      BIT(11)
#define BIT_PMU_APB_FRC_TOP_ASYNC_BRG_ENA                          BIT(10)
#define BIT_PMU_APB_ASYNC_BRG_EB_IGNORE                            BIT(9)
#define BIT_PMU_APB_REG_NRCP_SYS_DDR_PWR_HS_ACK                    BIT(8)
#define BIT_PMU_APB_REG_AUDCP_SYS_DDR_PWR_HS_ACK                   BIT(7)
#define BIT_PMU_APB_REG_PSCP_SYS_DDR_PWR_HS_ACK                    BIT(6)
#define BIT_PMU_APB_REG_V3_MODEM_SYS_DDR_PWR_HS_ACK                BIT(5)
#define BIT_PMU_APB_REG_APCPU_TOP_DDR_PWR_HS_ACK                   BIT(4)
#define BIT_PMU_APB_REG_AP_SYS_DDR_PWR_HS_ACK                      BIT(3)
#define BIT_PMU_APB_REG_MM_SYS_DDR_PWR_HS_ACK                      BIT(2)
#define BIT_PMU_APB_REG_GPU_SYS_DDR_PWR_HS_ACK                     BIT(1)
#define BIT_PMU_APB_REG_AON_SYS_DDR_PWR_HS_ACK                     BIT(0)

/* REG_PMU_APB_CSI_DSI_PWR_CNT_DONE */

#define BIT_PMU_APB_CSI_2P2LANE_PWR_CNT_DONE                       BIT(3)
#define BIT_PMU_APB_CSI_4LANE1_PWR_CNT_DONE                        BIT(2)
#define BIT_PMU_APB_CSI_4LANE0_PWR_CNT_DONE                        BIT(1)
#define BIT_PMU_APB_DSI_PWR_CNT_DONE                               BIT(0)

/* REG_PMU_APB_PD_AP_SYS_DBG_SHUTDOWN__EN */

#define BIT_PMU_APB_PD_AP_SYS_DBG_SHUTDOWN_EN                      BIT(0)

/* REG_PMU_APB_EIC_SYS_SEL */

#define BIT_PMU_APB_EIC_SYS_SEL(x)                                 (((x) & 0x7))

/* REG_PMU_APB_DDR_SLP_CTRL_STATE */

#define BIT_PMU_APB_DDR_SLP_CTRL_STATE(x)                          (((x) & 0xF))

/* REG_PMU_APB_PD_APCPU_C4_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_APCPU_C4_SHUTDOWN_MARK(x)                   (((x) & 0xF))

/* REG_PMU_APB_PD_APCPU_C5_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_APCPU_C5_SHUTDOWN_MARK(x)                   (((x) & 0xF))

/* REG_PMU_APB_PD_APCPU_C6_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_APCPU_C6_SHUTDOWN_MARK(x)                   (((x) & 0xF))

/* REG_PMU_APB_PD_APCPU_C7_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_APCPU_C7_SHUTDOWN_MARK(x)                   (((x) & 0xF))

/* REG_PMU_APB_APCPU_TOP_DEEP_SLEEP_CNT */

#define BIT_PMU_APB_APCPU_TOP_DEEP_SLEEP_CNT(x)                    (((x) & 0xFF))

/* REG_PMU_APB_APCPU_TOP_LIGHT_SLEEP_CNT */

#define BIT_PMU_APB_APCPU_TOP_LIGHT_SLEEP_CNT(x)                   (((x) & 0xFF))

/* REG_PMU_APB_PD_ESE_SYS_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_ESE_SYS_SHUTDOWN_MARK(x)                    (((x) & 0xF))

/* REG_PMU_APB_NRCP_DEEP_SLEEP_CNT */

#define BIT_PMU_APB_NRCP_DEEP_SLEEP_CNT(x)                         (((x) & 0xFF))

/* REG_PMU_APB_NRCP_SYS_SLEEP_CNT */

#define BIT_PMU_APB_NRCP_SYS_SLEEP_CNT(x)                          (((x) & 0xFF))

/* REG_PMU_APB_PD_IPA_SHUTDOWN_MARK_STATUS */

#define BIT_PMU_APB_PD_IPA_SYS_SHUTDOWN_MARK(x)                    (((x) & 0xF))

/* REG_PMU_APB_NRCP_LIGHT_SLEEP_CNT */

#define BIT_PMU_APB_NRCP_LIGHT_SLEEP_CNT(x)                        (((x) & 0xFF))

/* REG_PMU_APB_IPA_DEEP_SLEEP_CNT */

#define BIT_PMU_APB_IPA_DEEP_SLEEP_CNT(x)                          (((x) & 0xFF))

/* REG_PMU_APB_IPA_SYS_SLEEP_CNT */

#define BIT_PMU_APB_IPA_SYS_SLEEP_CNT(x)                           (((x) & 0xFF))

/* REG_PMU_APB_IPA_LIGHT_SLEEP_CNT */

#define BIT_PMU_APB_IPA_LIGHT_SLEEP_CNT(x)                         (((x) & 0xFF))


#endif /* PMU_APB_H */


