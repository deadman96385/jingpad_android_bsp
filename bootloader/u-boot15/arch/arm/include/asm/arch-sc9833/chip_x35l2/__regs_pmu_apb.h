/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _PMU_APB_REG_H
#define _PMU_APB_REG_H

#define CTL_BASE_PMU_APB SPRD_PMU_PHYS


#define REG_PMU_APB_PD_CA7_TOP_CFG                         ( CTL_BASE_PMU_APB + 0x0000 )
#define REG_PMU_APB_PD_CA7_C0_CFG                          ( CTL_BASE_PMU_APB + 0x0004 )
#define REG_PMU_APB_PD_CA7_C1_CFG                          ( CTL_BASE_PMU_APB + 0x0008 )
#define REG_PMU_APB_PD_CA7_C2_CFG                          ( CTL_BASE_PMU_APB + 0x000C )
#define REG_PMU_APB_PD_CA7_C3_CFG                          ( CTL_BASE_PMU_APB + 0x0010 )
#define REG_PMU_APB_PD_CA7_TOP_CFG2                        ( CTL_BASE_PMU_APB + 0x0014 )
#define REG_PMU_APB_PD_AP_SYS_CFG                          ( CTL_BASE_PMU_APB + 0x0018 )
#define REG_PMU_APB_PD_MM_TOP_CFG                          ( CTL_BASE_PMU_APB + 0x001C )
#define REG_PMU_APB_PD_GPU_TOP_CFG                         ( CTL_BASE_PMU_APB + 0x0020 )
#define REG_PMU_APB_PD_WTLCP_TD_CFG                        ( CTL_BASE_PMU_APB + 0x0024 )
#define REG_PMU_APB_PD_WTLCP_LTE_P1_CFG                    ( CTL_BASE_PMU_APB + 0x0028 )
#define REG_PMU_APB_PD_WTLCP_LTE_P2_CFG                    ( CTL_BASE_PMU_APB + 0x002C )
#define REG_PMU_APB_PD_WTLCP_LDSP_CFG                      ( CTL_BASE_PMU_APB + 0x0034 )
#define REG_PMU_APB_PD_WTLCP_TGDSP_CFG                     ( CTL_BASE_PMU_APB + 0x0038 )
#define REG_PMU_APB_PD_WTLCP_HU3GE_A_CFG                   ( CTL_BASE_PMU_APB + 0x003C )
#define REG_PMU_APB_PD_WTLCP_HU3GE_B_CFG                   ( CTL_BASE_PMU_APB + 0x0040 )
#define REG_PMU_APB_PD_WTLCP_SYS_CFG                       ( CTL_BASE_PMU_APB + 0x0044 )
#define REG_PMU_APB_PD_PUBCP_SYS_CFG                       ( CTL_BASE_PMU_APB + 0x0048 )
#define REG_PMU_APB_PD_WTLCP_LTE_P3_CFG                    ( CTL_BASE_PMU_APB + 0x004C )
#define REG_PMU_APB_PD_WTLCP_LTE_P4_CFG                    ( CTL_BASE_PMU_APB + 0x0050 )
#define REG_PMU_APB_PUBCP_FRC_STOP_REQ_FOR_WTL             ( CTL_BASE_PMU_APB + 0x0054 )
#define REG_PMU_APB_PD_PUB_SYS_CFG                         ( CTL_BASE_PMU_APB + 0x005C )
#define REG_PMU_APB_AP_WAKEUP_POR_CFG                      ( CTL_BASE_PMU_APB + 0x0060 )
#define REG_PMU_APB_XTL_WAIT_CNT                           ( CTL_BASE_PMU_APB + 0x0070 )
#define REG_PMU_APB_XTLBUF_WAIT_CNT                        ( CTL_BASE_PMU_APB + 0x0074 )
#define REG_PMU_APB_PLL_WAIT_CNT1                          ( CTL_BASE_PMU_APB + 0x0078 )
#define REG_PMU_APB_PLL_WAIT_CNT2                          ( CTL_BASE_PMU_APB + 0x007C )
#define REG_PMU_APB_XTL0_REL_CFG                           ( CTL_BASE_PMU_APB + 0x0080 )
#define REG_PMU_APB_XTL1_REL_CFG                           ( CTL_BASE_PMU_APB + 0x0084 )
#define REG_PMU_APB_CPPLL_REL_CFG                          ( CTL_BASE_PMU_APB + 0x0088 )
#define REG_PMU_APB_XTLBUF0_REL_CFG                        ( CTL_BASE_PMU_APB + 0x008C )
#define REG_PMU_APB_XTLBUF1_REL_CFG                        ( CTL_BASE_PMU_APB + 0x0090 )
#define REG_PMU_APB_MPLL_REL_CFG                           ( CTL_BASE_PMU_APB + 0x0094 )
#define REG_PMU_APB_DPLL_REL_CFG                           ( CTL_BASE_PMU_APB + 0x0098 )
#define REG_PMU_APB_LTEPLL_REL_CFG                         ( CTL_BASE_PMU_APB + 0x009C )
#define REG_PMU_APB_TWPLL_REL_CFG                          ( CTL_BASE_PMU_APB + 0x00A0 )
#define REG_PMU_APB_LVDSDIS_PLL_REL_CFG                    ( CTL_BASE_PMU_APB + 0x00A4 )
#define REG_PMU_APB_GPLL_REL_CFG                           ( CTL_BASE_PMU_APB + 0x00A8 )
#define REG_PMU_APB_RPLL_REL_CFG                           ( CTL_BASE_PMU_APB + 0x00AC )
#define REG_PMU_APB_CP_SOFT_RST                            ( CTL_BASE_PMU_APB + 0x00B0 )
#define REG_PMU_APB_CP_SLP_STATUS_DBG0                     ( CTL_BASE_PMU_APB + 0x00B4 )
#define REG_PMU_APB_PWR_STATUS0_DBG                        ( CTL_BASE_PMU_APB + 0x00BC )
#define REG_PMU_APB_PWR_STATUS1_DBG                        ( CTL_BASE_PMU_APB + 0x00C0 )
#define REG_PMU_APB_PWR_STATUS2_DBG                        ( CTL_BASE_PMU_APB + 0x00C4 )
#define REG_PMU_APB_SLEEP_CTRL                             ( CTL_BASE_PMU_APB + 0x00CC )
#define REG_PMU_APB_DDR_SLEEP_CTRL                         ( CTL_BASE_PMU_APB + 0x00D0 )
#define REG_PMU_APB_SLEEP_STATUS                           ( CTL_BASE_PMU_APB + 0x00D4 )
#define REG_PMU_APB_CA7_TOP_CFG                            ( CTL_BASE_PMU_APB + 0x00E4 )
#define REG_PMU_APB_CA7_C0_CFG                             ( CTL_BASE_PMU_APB + 0x00E8 )
#define REG_PMU_APB_CA7_C1_CFG                             ( CTL_BASE_PMU_APB + 0x00EC )
#define REG_PMU_APB_CA7_C2_CFG                             ( CTL_BASE_PMU_APB + 0x00F0 )
#define REG_PMU_APB_CA7_C3_CFG                             ( CTL_BASE_PMU_APB + 0x00F4 )
#define REG_PMU_APB_DDR_CHN_SLEEP_CTRL0                    ( CTL_BASE_PMU_APB + 0x00F8 )
#define REG_PMU_APB_DDR_CHN_SLEEP_CTRL1                    ( CTL_BASE_PMU_APB + 0x00FC )
#define REG_PMU_APB_DDR_OP_MODE_CFG                        ( CTL_BASE_PMU_APB + 0x012C )
#define REG_PMU_APB_DDR_PHY_RET_CFG                        ( CTL_BASE_PMU_APB + 0x0130 )
#define REG_PMU_APB_CLK26M_SEL_CFG                         ( CTL_BASE_PMU_APB + 0x0134 )
#define REG_PMU_APB_BISR_DONE_STATUS                       ( CTL_BASE_PMU_APB + 0x0138 )
#define REG_PMU_APB_BISR_BUSY_STATUS                       ( CTL_BASE_PMU_APB + 0x013C )
#define REG_PMU_APB_BISR_BYP_CFG                           ( CTL_BASE_PMU_APB + 0x0140 )
#define REG_PMU_APB_BISR_EN_CFG                            ( CTL_BASE_PMU_APB + 0x0144 )
#define REG_PMU_APB_CGM_AUTO_GATE_SEL_CFG0                 ( CTL_BASE_PMU_APB + 0x0148 )
#define REG_PMU_APB_CGM_AUTO_GATE_SEL_CFG1                 ( CTL_BASE_PMU_APB + 0x014C )
#define REG_PMU_APB_CGM_AUTO_GATE_SEL_CFG2                 ( CTL_BASE_PMU_APB + 0x0150 )
#define REG_PMU_APB_CGM_AUTO_GATE_SEL_CFG3                 ( CTL_BASE_PMU_APB + 0x0154 )
#define REG_PMU_APB_CGM_FORCE_EN_CFG0                      ( CTL_BASE_PMU_APB + 0x0158 )
#define REG_PMU_APB_CGM_FORCE_EN_CFG1                      ( CTL_BASE_PMU_APB + 0x015C )
#define REG_PMU_APB_CGM_FORCE_EN_CFG2                      ( CTL_BASE_PMU_APB + 0x0160 )
#define REG_PMU_APB_CGM_FORCE_EN_CFG3                      ( CTL_BASE_PMU_APB + 0x0164 )
#define REG_PMU_APB_SLEEP_XTLON_CTRL                       ( CTL_BASE_PMU_APB + 0x0168 )
#define REG_PMU_APB_MEM_SLP_CFG                            ( CTL_BASE_PMU_APB + 0x016C )
#define REG_PMU_APB_MEM_SD_CFG                             ( CTL_BASE_PMU_APB + 0x0170 )
#define REG_PMU_APB_CA7_CORE_PU_LOCK                       ( CTL_BASE_PMU_APB + 0x0174 )
#define REG_PMU_APB_ARM7_HOLD_CGM_EN                       ( CTL_BASE_PMU_APB + 0x0178 )
#define REG_PMU_APB_PWR_CNT_WAIT_CFG0                      ( CTL_BASE_PMU_APB + 0x017C )
#define REG_PMU_APB_PWR_CNT_WAIT_CFG1                      ( CTL_BASE_PMU_APB + 0x0180 )
#define REG_PMU_APB_RC0_REL_CFG                            ( CTL_BASE_PMU_APB + 0x0184 )
#define REG_PMU_APB_RC1_REL_CFG                            ( CTL_BASE_PMU_APB + 0x0188 )
#define REG_PMU_APB_RC_CNT_WAIT_CFG                        ( CTL_BASE_PMU_APB + 0x018C )
#define REG_PMU_APB_MEM_AUTO_SLP_CFG                       ( CTL_BASE_PMU_APB + 0x0190 )
#define REG_PMU_APB_MEM_AUTO_SD_CFG                        ( CTL_BASE_PMU_APB + 0x0194 )
#define REG_PMU_APB_WAKEUP_LOCK_EN                         ( CTL_BASE_PMU_APB + 0x01A0 )
#define REG_PMU_APB_WTLCP_TGDSP_CORE_INT_DISABLE           ( CTL_BASE_PMU_APB + 0x01B0 )
#define REG_PMU_APB_WTLCP_LDSP_CORE_INT_DISABLE            ( CTL_BASE_PMU_APB + 0x01B4 )
#define REG_PMU_APB_PUBCP_CORE_INT_DISABLE                 ( CTL_BASE_PMU_APB + 0x01B8 )
#define REG_PMU_APB_CA7_C0_CORE_INT_DISABLE                ( CTL_BASE_PMU_APB + 0x01BC )
#define REG_PMU_APB_CA7_C1_CORE_INT_DISABLE                ( CTL_BASE_PMU_APB + 0x01C0 )
#define REG_PMU_APB_CA7_C2_CORE_INT_DISABLE                ( CTL_BASE_PMU_APB + 0x01C4 )
#define REG_PMU_APB_CA7_C3_CORE_INT_DISABLE                ( CTL_BASE_PMU_APB + 0x01C8 )
#define REG_PMU_APB_WTLCP_TGDSP_DSLP_ENA                   ( CTL_BASE_PMU_APB + 0x0200 )
#define REG_PMU_APB_WTLCP_LDSP_DSLP_ENA                    ( CTL_BASE_PMU_APB + 0x0204 )
#define REG_PMU_APB_AP_DSLP_ENA                            ( CTL_BASE_PMU_APB + 0x0208 )
#define REG_PMU_APB_PUBCP_DSLP_ENA                         ( CTL_BASE_PMU_APB + 0x020C )
#define REG_PMU_APB_WTLCP_DSLP_ENA                         ( CTL_BASE_PMU_APB + 0x0210 )
#define REG_PMU_APB_CA7_TOP_DSLP_ENA                       ( CTL_BASE_PMU_APB + 0x0214 )
#define REG_PMU_APB_SYS_PUB_DSLP_ENA                       ( CTL_BASE_PMU_APB + 0x0220 )
#define REG_PMU_APB_AP_AUTO_LSLP_ENA                       ( CTL_BASE_PMU_APB + 0x0224 )
#define REG_PMU_APB_PUBCP_AUTO_LSLP_ENA                    ( CTL_BASE_PMU_APB + 0x0228 )
#define REG_PMU_APB_WTLCP_AUTO_LSLP_ENA                    ( CTL_BASE_PMU_APB + 0x022C )
#define REG_PMU_APB_LIGHT_SLEEP_ENABLE                     ( CTL_BASE_PMU_APB + 0x0230 )
#define REG_PMU_APB_ARM7_LIGHT_SLEEP                       ( CTL_BASE_PMU_APB + 0x0234 )
#define REG_PMU_APB_SYS_DOZE_DSLP_ENA                      ( CTL_BASE_PMU_APB + 0x0240 )
#define REG_PMU_APB_PUB_ACC_RDY                            ( CTL_BASE_PMU_APB + 0x0250 )
#define REG_PMU_APB_PUB_CLK_RDY                            ( CTL_BASE_PMU_APB + 0x0254 )
#define REG_PMU_APB_EIC_SEL                                ( CTL_BASE_PMU_APB + 0x0258 )
#define REG_PMU_APB_AXI_LP_CTRL_DISABLE                    ( CTL_BASE_PMU_APB + 0x0260 )
#define REG_PMU_APB_PMU_DEBUG                              ( CTL_BASE_PMU_APB + 0x0270 )
#define REG_PMU_APB_SLEEP_CNT_CLR                          ( CTL_BASE_PMU_APB + 0x0274 )
#define REG_PMU_APB_LVDSRFPLL_REL_CFG                      ( CTL_BASE_PMU_APB + 0x0280 )
#define REG_PMU_APB_PAD_OUT_ADIE_CTRL0                     ( CTL_BASE_PMU_APB + 0x0290 )
#define REG_PMU_APB_PAD_OUT_ADIE_CTRL1                     ( CTL_BASE_PMU_APB + 0x0294 )
#define REG_PMU_APB_BISR_FORCE_SEL                         ( CTL_BASE_PMU_APB + 0x0300 )
#define REG_PMU_APB_AON_MEM_CTRL                           ( CTL_BASE_PMU_APB + 0x0330 )
#define REG_PMU_APB_PWR_DOMAIN_INT_CLR                     ( CTL_BASE_PMU_APB + 0x0334 )
#define REG_PMU_APB_PD_CA7_C0_SHUTDOWN_MARK_STATUS         ( CTL_BASE_PMU_APB + 0x3000 )
#define REG_PMU_APB_PD_CA7_C1_SHUTDOWN_MARK_STATUS         ( CTL_BASE_PMU_APB + 0x3004 )
#define REG_PMU_APB_PD_CA7_C2_SHUTDOWN_MARK_STATUS         ( CTL_BASE_PMU_APB + 0x3008 )
#define REG_PMU_APB_PD_CA7_C3_SHUTDOWN_MARK_STATUS         ( CTL_BASE_PMU_APB + 0x300C )
#define REG_PMU_APB_PD_CA7_TOP_SHUTDOWN_MARK_STATUS        ( CTL_BASE_PMU_APB + 0x3010 )
#define REG_PMU_APB_PD_AP_SYS_SHUTDOWN_MARK_STATUS         ( CTL_BASE_PMU_APB + 0x3014 )
#define REG_PMU_APB_PD_GPU_TOP_SHUTDOWN_MARK_STATUS        ( CTL_BASE_PMU_APB + 0x3018 )
#define REG_PMU_APB_PD_MM_TOP_SHUTDOWN_MARK_STATUS         ( CTL_BASE_PMU_APB + 0x301C )
#define REG_PMU_APB_PD_WTLCP_TD_SHUTDOWN_MARK_STATUS       ( CTL_BASE_PMU_APB + 0x3020 )
#define REG_PMU_APB_PD_WTLCP_LTE_P1_SHUTDOWN_MARK_STATUS   ( CTL_BASE_PMU_APB + 0x3024 )
#define REG_PMU_APB_PD_WTLCP_LTE_P2_SHUTDOWN_MARK_STATUS   ( CTL_BASE_PMU_APB + 0x3028 )
#define REG_PMU_APB_PD_WTLCP_LDSP_SHUTDOWN_MARK_STATUS     ( CTL_BASE_PMU_APB + 0x3030 )
#define REG_PMU_APB_PD_WTLCP_TGDSP_SHUTDOWN_MARK_STATUS    ( CTL_BASE_PMU_APB + 0x3034 )
#define REG_PMU_APB_PD_WTLCP_HU3GE_A_SHUTDOWN_MARK_STATUS  ( CTL_BASE_PMU_APB + 0x3038 )
#define REG_PMU_APB_PD_WTLCP_HU3GE_B_SHUTDOWN_MARK_STATUS  ( CTL_BASE_PMU_APB + 0x303C )
#define REG_PMU_APB_PD_WTLCP_SYS_SHUTDOWN_MARK_STATUS      ( CTL_BASE_PMU_APB + 0x3040 )
#define REG_PMU_APB_PD_PUBCP_SYS_SHUTDOWN_MARK_STATUS      ( CTL_BASE_PMU_APB + 0x3044 )
#define REG_PMU_APB_PD_WTLCP_LTE_P3_SHUTDOWN_MARK_STATUS   ( CTL_BASE_PMU_APB + 0x3048 )
#define REG_PMU_APB_PD_WTLCP_LTE_P4_SHUTDOWN_MARK_STATUS   ( CTL_BASE_PMU_APB + 0x304C )
#define REG_PMU_APB_PD_PUB_SYS_SHUTDOWN_MARK_STATUS        ( CTL_BASE_PMU_APB + 0x3054 )

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_CA7_TOP_CFG
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_CA7_TOP_DBG_SHUTDOWN_EN                              BIT(28)
#define BIT_PMU_APB_PD_CA7_TOP_PD_SEL                                       BIT(27)
#define BIT_PMU_APB_PD_CA7_TOP_FORCE_SHUTDOWN                               BIT(25)
#define BIT_PMU_APB_PD_CA7_TOP_AUTO_SHUTDOWN_EN                             BIT(24)
#define BIT_PMU_APB_PD_CA7_TOP_PWR_ON_DLY(x)                                (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_CA7_TOP_PWR_ON_SEQ_DLY(x)                            (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_CA7_TOP_ISO_ON_DLY(x)                                (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_CA7_C0_CFG
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_CA7_C0_WFI_SHUTDOWN_EN                               BIT(29)
#define BIT_PMU_APB_PD_CA7_C0_DBG_SHUTDOWN_EN                               BIT(28)
#define BIT_PMU_APB_PD_CA7_C0_PD_SEL                                        BIT(27)
#define BIT_PMU_APB_PD_CA7_C0_FORCE_SHUTDOWN                                BIT(25)
#define BIT_PMU_APB_PD_CA7_C0_AUTO_SHUTDOWN_EN                              BIT(24)
#define BIT_PMU_APB_PD_CA7_C0_PWR_ON_DLY(x)                                 (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_CA7_C0_PWR_ON_SEQ_DLY(x)                             (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_CA7_C0_ISO_ON_DLY(x)                                 (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_CA7_C1_CFG
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_CA7_C1_WFI_SHUTDOWN_EN                               BIT(29)
#define BIT_PMU_APB_PD_CA7_C1_DBG_SHUTDOWN_EN                               BIT(28)
#define BIT_PMU_APB_PD_CA7_C1_PD_SEL                                        BIT(27)
#define BIT_PMU_APB_PD_CA7_C1_FORCE_SHUTDOWN                                BIT(25)
#define BIT_PMU_APB_PD_CA7_C1_AUTO_SHUTDOWN_EN                              BIT(24)
#define BIT_PMU_APB_PD_CA7_C1_PWR_ON_DLY(x)                                 (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_CA7_C1_PWR_ON_SEQ_DLY(x)                             (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_CA7_C1_ISO_ON_DLY(x)                                 (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_CA7_C2_CFG
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_CA7_C2_WFI_SHUTDOWN_EN                               BIT(29)
#define BIT_PMU_APB_PD_CA7_C2_DBG_SHUTDOWN_EN                               BIT(28)
#define BIT_PMU_APB_PD_CA7_C2_PD_SEL                                        BIT(27)
#define BIT_PMU_APB_PD_CA7_C2_FORCE_SHUTDOWN                                BIT(25)
#define BIT_PMU_APB_PD_CA7_C2_AUTO_SHUTDOWN_EN                              BIT(24)
#define BIT_PMU_APB_PD_CA7_C2_PWR_ON_DLY(x)                                 (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_CA7_C2_PWR_ON_SEQ_DLY(x)                             (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_CA7_C2_ISO_ON_DLY(x)                                 (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_CA7_C3_CFG
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_CA7_C3_WFI_SHUTDOWN_EN                               BIT(29)
#define BIT_PMU_APB_PD_CA7_C3_DBG_SHUTDOWN_EN                               BIT(28)
#define BIT_PMU_APB_PD_CA7_C3_PD_SEL                                        BIT(27)
#define BIT_PMU_APB_PD_CA7_C3_FORCE_SHUTDOWN                                BIT(25)
#define BIT_PMU_APB_PD_CA7_C3_AUTO_SHUTDOWN_EN                              BIT(24)
#define BIT_PMU_APB_PD_CA7_C3_PWR_ON_DLY(x)                                 (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_CA7_C3_PWR_ON_SEQ_DLY(x)                             (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_CA7_C3_ISO_ON_DLY(x)                                 (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_CA7_TOP_CFG2
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_CA7_TOP_DCDC_PWR_ON_DLY(x)                           (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_CA7_TOP_DCDC_PWR_OFF_DLY(x)                          (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_AP_SYS_CFG
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_AP_SYS_FORCE_SHUTDOWN                                BIT(25)
#define BIT_PMU_APB_PD_AP_SYS_AUTO_SHUTDOWN_EN                              BIT(24)
#define BIT_PMU_APB_PD_AP_SYS_PWR_ON_DLY(x)                                 (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_AP_SYS_PWR_ON_SEQ_DLY(x)                             (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_AP_SYS_ISO_ON_DLY(x)                                 (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_MM_TOP_CFG
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_MM_TOP_FORCE_SHUTDOWN                                BIT(25)
#define BIT_PD_MM_TOP_FORCE_SHUTDOWN						BIT_PMU_APB_PD_MM_TOP_FORCE_SHUTDOWN
#define BIT_PMU_APB_PD_MM_TOP_AUTO_SHUTDOWN_EN                              BIT(24)
#define BIT_PMU_APB_PD_MM_TOP_PWR_ON_DLY(x)                                 (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_MM_TOP_PWR_ON_SEQ_DLY(x)                             (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_MM_TOP_ISO_ON_DLY(x)                                 (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_GPU_TOP_CFG
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_GPU_TOP_FORCE_SHUTDOWN                               BIT(25)
#define BIT_PD_GPU_TOP_FORCE_SHUTDOWN						BIT_PMU_APB_PD_GPU_TOP_FORCE_SHUTDOWN
#define BIT_PMU_APB_PD_GPU_TOP_AUTO_SHUTDOWN_EN                             BIT(24)
#define BIT_PMU_APB_PD_GPU_TOP_PWR_ON_DLY(x)                                (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_GPU_TOP_PWR_ON_SEQ_DLY(x)                            (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_GPU_TOP_ISO_ON_DLY(x)                                (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_TD_CFG
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_TD_FORCE_SHUTDOWN                              BIT(25)
#define BIT_PMU_APB_PD_WTLCP_TD_AUTO_SHUTDOWN_EN                            BIT(24)
#define BIT_PMU_APB_PD_WTLCP_TD_PWR_ON_DLY(x)                               (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_TD_PWR_ON_SEQ_DLY(x)                           (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_TD_ISO_ON_DLY(x)                               (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LTE_P1_CFG
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P1_FORCE_SHUTDOWN                          BIT(25)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_AUTO_SHUTDOWN_EN                        BIT(24)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_PWR_ON_DLY(x)                           (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_PWR_ON_SEQ_DLY(x)                       (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_ISO_ON_DLY(x)                           (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LTE_P2_CFG
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P2_FORCE_SHUTDOWN                          BIT(25)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_AUTO_SHUTDOWN_EN                        BIT(24)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_PWR_ON_DLY(x)                           (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_PWR_ON_SEQ_DLY(x)                       (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_ISO_ON_DLY(x)                           (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LDSP_CFG
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LDSP_PD_SEL                                    BIT(27)
#define BIT_PMU_APB_PD_WTLCP_LDSP_FORCE_SHUTDOWN                            BIT(25)
#define BIT_PMU_APB_PD_WTLCP_LDSP_AUTO_SHUTDOWN_EN                          BIT(24)
#define BIT_PMU_APB_PD_WTLCP_LDSP_PWR_ON_DLY(x)                             (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_LDSP_PWR_ON_SEQ_DLY(x)                         (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_LDSP_ISO_ON_DLY(x)                             (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_TGDSP_CFG
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_TGDSP_PD_SEL                                   BIT(27)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_FORCE_SHUTDOWN                           BIT(25)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_AUTO_SHUTDOWN_EN                         BIT(24)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_PWR_ON_DLY(x)                            (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_PWR_ON_SEQ_DLY(x)                        (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_ISO_ON_DLY(x)                            (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_HU3GE_A_CFG
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_FORCE_SHUTDOWN                         BIT(25)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_AUTO_SHUTDOWN_EN                       BIT(24)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_PWR_ON_DLY(x)                          (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_PWR_ON_SEQ_DLY(x)                      (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_ISO_ON_DLY(x)                          (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_HU3GE_B_CFG
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_FORCE_SHUTDOWN                         BIT(25)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_AUTO_SHUTDOWN_EN                       BIT(24)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_PWR_ON_DLY(x)                          (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_PWR_ON_SEQ_DLY(x)                      (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_ISO_ON_DLY(x)                          (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_SYS_CFG
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_SYS_FORCE_SHUTDOWN                             BIT(25)
#define BIT_PMU_APB_PD_WTLCP_SYS_AUTO_SHUTDOWN_EN                           BIT(24)
#define BIT_PMU_APB_PD_WTLCP_SYS_PWR_ON_DLY(x)                              (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_SYS_PWR_ON_SEQ_DLY(x)                          (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_SYS_ISO_ON_DLY(x)                              (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_PUBCP_SYS_CFG
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_PUBCP_DBG_SHUTDOWN_EN                                BIT(26)
#define BIT_PMU_APB_PD_PUBCP_SYS_FORCE_SHUTDOWN                             BIT(25)
#define BIT_PMU_APB_PD_PUBCP_SYS_AUTO_SHUTDOWN_EN                           BIT(24)
#define BIT_PMU_APB_PD_PUBCP_SYS_PWR_ON_DLY(x)                              (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_PUBCP_SYS_PWR_ON_SEQ_DLY(x)                          (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_PUBCP_SYS_ISO_ON_DLY(x)                              (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LTE_P3_CFG
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P3_FORCE_SHUTDOWN                          BIT(25)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_AUTO_SHUTDOWN_EN                        BIT(24)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_PWR_ON_DLY(x)                           (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_PWR_ON_SEQ_DLY(x)                       (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_ISO_ON_DLY(x)                           (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LTE_P4_CFG
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P4_FORCE_SHUTDOWN                          BIT(25)
#define BIT_PMU_APB_PD_WTLCP_LTE_P4_AUTO_SHUTDOWN_EN                        BIT(24)
#define BIT_PMU_APB_PD_WTLCP_LTE_P4_PWR_ON_DLY(x)                           (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_LTE_P4_PWR_ON_SEQ_DLY(x)                       (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_LTE_P4_ISO_ON_DLY(x)                           (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PUBCP_FRC_STOP_REQ_FOR_WTL
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUBCP_FRC_STOP_REQ_FOR_WTL                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_PUB_SYS_CFG
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_PUB_SYS_FORCE_SHUTDOWN                               BIT(25)
#define BIT_PMU_APB_PD_PUB_SYS_AUTO_SHUTDOWN_EN                             BIT(24)
#define BIT_PMU_APB_PD_PUB_SYS_PWR_ON_DLY(x)                                (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_PUB_SYS_PWR_ON_SEQ_DLY(x)                            (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_PUB_SYS_ISO_ON_DLY(x)                                (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_AP_WAKEUP_POR_CFG
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_AP_WAKEUP_POR_N                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_XTL_WAIT_CNT
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_XTL1_WAIT_CNT(x)                                        (((x) & 0xFF) << 8)
#define BIT_PMU_APB_XTL0_WAIT_CNT(x)                                        (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_XTLBUF_WAIT_CNT
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_XTLBUF1_WAIT_CNT(x)                                     (((x) & 0xFF) << 8)
#define BIT_PMU_APB_XTLBUF0_WAIT_CNT(x)                                     (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PLL_WAIT_CNT1
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_LTEPLL_WAIT_CNT(x)                                      (((x) & 0xFF) << 24)
#define BIT_PMU_APB_TWPLL_WAIT_CNT(x)                                       (((x) & 0xFF) << 16)
#define BIT_PMU_APB_DPLL_WAIT_CNT(x)                                        (((x) & 0xFF) << 8)
#define BIT_PMU_APB_MPLL_WAIT_CNT(x)                                        (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PLL_WAIT_CNT2
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CPPLL_WAIT_CNT(x)                                       (((x) & 0xFF) << 24)
#define BIT_PMU_APB_RPLL_WAIT_CNT(x)                                        (((x) & 0xFF) << 16)
#define BIT_PMU_APB_GPLL_WAIT_CNT(x)                                        (((x) & 0xFF) << 8)
#define BIT_PMU_APB_LVDSDIS_PLL_WAIT_CNT(x)                                 (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_XTL0_REL_CFG
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_XTL0_ARM7_SEL                                           BIT(5)
#define BIT_XTL0_ARM7_SEL							BIT_PMU_APB_XTL0_ARM7_SEL
#define BIT_PMU_APB_XTL0_PUBCP_SEL                                          BIT(2)
#define BIT_PMU_APB_XTL0_WTLCP_SEL                                          BIT(1)
#define BIT_PMU_APB_XTL0_AP_SEL                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_XTL1_REL_CFG
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_XTL1_ARM7_SEL                                           BIT(5)
#define BIT_PMU_APB_XTL1_PUBCP_SEL                                          BIT(2)
#define BIT_PMU_APB_XTL1_WTLCP_SEL                                          BIT(1)
#define BIT_PMU_APB_XTL1_AP_SEL                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CPPLL_REL_CFG
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CPPLL_REF_SEL                                           BIT(8)
#define BIT_PMU_APB_CPPLL_ARM7_SEL                                          BIT(5)
#define BIT_PMU_APB_CPPLL_PUBCP_SEL                                         BIT(2)
#define BIT_PMU_APB_CPPLL_WTLCP_SEL                                         BIT(1)
#define BIT_PMU_APB_CPPLL_AP_SEL                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_XTLBUF0_REL_CFG
// Register Offset : 0x008C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_XTLBUF0_ARM7_SEL                                        BIT(5)
#define BIT_PMU_APB_XTLBUF0_PUBCP_SEL                                       BIT(2)
#define BIT_PMU_APB_XTLBUF0_WTLCP_SEL                                       BIT(1)
#define BIT_PMU_APB_XTLBUF0_AP_SEL                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_XTLBUF1_REL_CFG
// Register Offset : 0x0090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_XTLBUF1_ARM7_SEL                                        BIT(5)
#define BIT_PMU_APB_XTLBUF1_PUBCP_SEL                                       BIT(2)
#define BIT_PMU_APB_XTLBUF1_WTLCP_SEL                                       BIT(1)
#define BIT_PMU_APB_XTLBUF1_AP_SEL                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_MPLL_REL_CFG
// Register Offset : 0x0094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_MPLL_REF_SEL                                            BIT(8)
#define BIT_PMU_APB_MPLL_ARM7_SEL                                           BIT(5)
#define BIT_PMU_APB_MPLL_PUBCP_SEL                                          BIT(2)
#define BIT_PMU_APB_MPLL_WTLCP_SEL                                          BIT(1)
#define BIT_PMU_APB_MPLL_AP_SEL                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_DPLL_REL_CFG
// Register Offset : 0x0098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_DPLL_REF_SEL                                            BIT(8)
#define BIT_PMU_APB_DPLL_ARM7_SEL                                           BIT(5)
#define BIT_PMU_APB_DPLL_PUBCP_SEL                                          BIT(2)
#define BIT_PMU_APB_DPLL_WTLCP_SEL                                          BIT(1)
#define BIT_PMU_APB_DPLL_AP_SEL                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_LTEPLL_REL_CFG
// Register Offset : 0x009C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_LTEPLL_REF_SEL(x)                                       (((x) & 0x3) << 8)
#define BIT_PMU_APB_LTEPLL_ARM7_SEL                                         BIT(5)
#define BIT_PMU_APB_LTEPLL_PUBCP_SEL                                        BIT(2)
#define BIT_PMU_APB_LTEPLL_WTLCP_SEL                                        BIT(1)
#define BIT_PMU_APB_LTEPLL_AP_SEL                                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_TWPLL_REL_CFG
// Register Offset : 0x00A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_TWPLL_REF_SEL(x)                                        (((x) & 0x3) << 8)
#define BIT_PMU_APB_TWPLL_ARM7_SEL                                          BIT(5)
#define BIT_PMU_APB_TWPLL_PUBCP_SEL                                         BIT(2)
#define BIT_PMU_APB_TWPLL_WTLCP_SEL                                         BIT(1)
#define BIT_PMU_APB_TWPLL_AP_SEL                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_LVDSDIS_PLL_REL_CFG
// Register Offset : 0x00A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_LVDSDIS_PLL_REF_SEL                                     BIT(8)
#define BIT_PMU_APB_LVDSDIS_PLL_ARM7_SEL                                    BIT(5)
#define BIT_PMU_APB_LVDSDIS_PLL_PUBCP_SEL                                   BIT(2)
#define BIT_PMU_APB_LVDSDIS_PLL_WTLCP_SEL                                   BIT(1)
#define BIT_PMU_APB_LVDSDIS_PLL_AP_SEL                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_GPLL_REL_CFG
// Register Offset : 0x00A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_GPLL_REF_SEL                                            BIT(8)
#define BIT_PMU_APB_GPLL_ARM7_SEL                                           BIT(5)
#define BIT_PMU_APB_GPLL_PUBCP_SEL                                          BIT(2)
#define BIT_PMU_APB_GPLL_WTLCP_SEL                                          BIT(1)
#define BIT_PMU_APB_GPLL_AP_SEL                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_RPLL_REL_CFG
// Register Offset : 0x00AC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_RPLL_REF_SEL(x)                                         (((x) & 0x3) << 8)
#define BIT_PMU_APB_RPLL_ARM7_SEL                                           BIT(5)
#define BIT_PMU_APB_RPLL_PUBCP_SEL                                          BIT(2)
#define BIT_PMU_APB_RPLL_WTLCP_SEL                                          BIT(1)
#define BIT_PMU_APB_RPLL_AP_SEL                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CP_SOFT_RST
// Register Offset : 0x00B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_ARM7_SOFT_RST                                           BIT(8)
#define BIT_PMU_APB_PUB_SOFT_RST                                            BIT(6)
#define BIT_PMU_APB_AP_SOFT_RST                                             BIT(5)
#define BIT_PMU_APB_GPU_SOFT_RST                                            BIT(4)
#define BIT_PMU_APB_MM_SOFT_RST                                             BIT(3)
#define BIT_PMU_APB_WTLCP_DSP_SYS_SRST                                      BIT(2)
#define BIT_PMU_APB_PUBCP_SOFT_RST                                          BIT(1)
#define BIT_PMU_APB_WTLCP_SOFT_RST                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CP_SLP_STATUS_DBG0
// Register Offset : 0x00B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUBCP_DEEP_SLP_DBG(x)                                   (((x) & 0xFFFF) << 16)
#define BIT_PMU_APB_WTLCP_DEEP_SLP_DBG(x)                                   (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PWR_STATUS0_DBG
// Register Offset : 0x00BC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_MM_TOP_STATE(x)                                      (((x) & 0xF) << 28)
#define BIT_PMU_APB_PD_GPU_TOP_STATE(x)                                     (((x) & 0xF) << 24)
#define BIT_PMU_APB_PD_AP_SYS_STATE(x)                                      (((x) & 0xF) << 20)
#define BIT_PMU_APB_PD_CA7_C3_STATE(x)                                      (((x) & 0xF) << 16)
#define BIT_PMU_APB_PD_CA7_C2_STATE(x)                                      (((x) & 0xF) << 12)
#define BIT_PMU_APB_PD_CA7_C1_STATE(x)                                      (((x) & 0xF) << 8)
#define BIT_PMU_APB_PD_CA7_C0_STATE(x)                                      (((x) & 0xF) << 4)
#define BIT_PMU_APB_PD_CA7_TOP_STATE(x)                                     (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PWR_STATUS1_DBG
// Register Offset : 0x00C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_TD_STATE(x)                                    (((x) & 0xF) << 28)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_STATE(x)                                (((x) & 0xF) << 24)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_STATE(x)                                (((x) & 0xF) << 20)
#define BIT_PMU_APB_PD_WTLCP_LDSP_STATE(x)                                  (((x) & 0xF) << 12)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_STATE(x)                                 (((x) & 0xF) << 8)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_STATE(x)                               (((x) & 0xF) << 4)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_STATE(x)                               (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PWR_STATUS2_DBG
// Register Offset : 0x00C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_PUB_SYS_STATE(x)                                     (((x) & 0xF) << 24)
#define BIT_PMU_APB_PD_WTLCP_LTE_P4_STATE(x)                                (((x) & 0xF) << 16)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_STATE(x)                                (((x) & 0xF) << 12)
#define BIT_PMU_APB_PD_PUBCP_SYS_STATE(x)                                   (((x) & 0xF) << 8)
#define BIT_PMU_APB_PD_WTLCP_SYS_STATE(x)                                   (((x) & 0xF) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_SLEEP_CTRL
// Register Offset : 0x00CC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_AON_DMA_FORCE_LIGHT_SLEEP                               BIT(27)
#define BIT_PMU_APB_PUBCP_FORCE_LIGHT_SLEEP                                 BIT(26)
#define BIT_PMU_APB_WTLCP_FORCE_LIGHT_SLEEP                                 BIT(25)
#define BIT_PMU_APB_AP_FORCE_LIGHT_SLEEP                                    BIT(24)
#define BIT_PMU_APB_ARM7_FORCE_DEEP_SLEEP                                   BIT(21)
#define BIT_PMU_APB_PUBCP_FORCE_DEEP_SLEEP                                  BIT(18)
#define BIT_PMU_APB_WTLCP_FORCE_DEEP_SLEEP                                  BIT(17)
#define BIT_PMU_APB_AP_FORCE_DEEP_SLEEP                                     BIT(16)
#define BIT_PMU_APB_PUBCP_LIGHT_SLEEP                                       BIT(10)
#define BIT_PMU_APB_WTLCP_LIGHT_SLEEP                                       BIT(9)
#define BIT_PMU_APB_AP_LIGHT_SLEEP                                          BIT(8)
#define BIT_PMU_APB_PUBCP_DEEP_SLEEP                                        BIT(2)
#define BIT_PMU_APB_WTLCP_DEEP_SLEEP                                        BIT(1)
#define BIT_PMU_APB_AP_DEEP_SLEEP                                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_DDR_SLEEP_CTRL
// Register Offset : 0x00D0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_BUSY_TRANSFER_HWDATA_SEL                                BIT(16)
#define BIT_PMU_APB_DDR_PUBL_APB_SOFT_RST                                   BIT(12)
#define BIT_PMU_APB_DDR_UMCTL_APB_SOFT_RST                                  BIT(11)
#define BIT_PMU_APB_DDR_PUBL_SOFT_RST                                       BIT(10)
#define BIT_PMU_APB_DDR_PHY_SOFT_RST                                        BIT(8)
#define BIT_PMU_APB_DDR_PHY_AUTO_GATE_EN                                    BIT(6)
#define BIT_PMU_APB_DDR_PUBL_AUTO_GATE_EN                                   BIT(5)
#define BIT_PMU_APB_DDR_UMCTL_AUTO_GATE_EN                                  BIT(4)
#define BIT_PMU_APB_DDR_PHY_EB                                              BIT(2)
#define BIT_PMU_APB_DDR_UMCTL_EB                                            BIT(1)
#define BIT_PMU_APB_DDR_PUBL_EB                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_SLEEP_STATUS
// Register Offset : 0x00D4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_ARM7_SLP_STATUS(x)                                      (((x) & 0xF) << 20)
#define BIT_PMU_APB_PUBCP_SLP_STATUS(x)                                     (((x) & 0xF) << 8)
#define BIT_PMU_APB_WTLCP_SLP_STATUS(x)                                     (((x) & 0xF) << 4)
#define BIT_PMU_APB_AP_SLP_STATUS(x)                                        (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CA7_TOP_CFG
// Register Offset : 0x00E4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CA7_L2RSTDISABLE                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CA7_C0_CFG
// Register Offset : 0x00E8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CA7_VINITHI_C0                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CA7_C1_CFG
// Register Offset : 0x00EC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CA7_VINITHI_C1                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CA7_C2_CFG
// Register Offset : 0x00F0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CA7_VINITHI_C2                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CA7_C3_CFG
// Register Offset : 0x00F4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CA7_VINITHI_C3                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_DDR_CHN_SLEEP_CTRL0
// Register Offset : 0x00F8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_DDR_CTRL_AXI_LP_EN                                      BIT(31)
#define BIT_PMU_APB_DDR_CTRL_CGM_SEL                                        BIT(30)
#define BIT_PMU_APB_DDR_CHN9_AXI_LP_EN                                      BIT(25)
#define BIT_PMU_APB_DDR_CHN8_AXI_LP_EN                                      BIT(24)
#define BIT_PMU_APB_DDR_CHN7_AXI_LP_EN                                      BIT(23)
#define BIT_PMU_APB_DDR_CHN6_AXI_LP_EN                                      BIT(22)
#define BIT_PMU_APB_DDR_CHN5_AXI_LP_EN                                      BIT(21)
#define BIT_PMU_APB_DDR_CHN4_AXI_LP_EN                                      BIT(20)
#define BIT_PMU_APB_DDR_CHN3_AXI_LP_EN                                      BIT(19)
#define BIT_PMU_APB_DDR_CHN2_AXI_LP_EN                                      BIT(18)
#define BIT_PMU_APB_DDR_CHN1_AXI_LP_EN                                      BIT(17)
#define BIT_PMU_APB_DDR_CHN0_AXI_LP_EN                                      BIT(16)
#define BIT_PMU_APB_DDR_CHN9_CGM_SEL                                        BIT(9)
#define BIT_PMU_APB_DDR_CHN8_CGM_SEL                                        BIT(8)
#define BIT_PMU_APB_DDR_CHN7_CGM_SEL                                        BIT(7)
#define BIT_PMU_APB_DDR_CHN6_CGM_SEL                                        BIT(6)
#define BIT_PMU_APB_DDR_CHN5_CGM_SEL                                        BIT(5)
#define BIT_PMU_APB_DDR_CHN4_CGM_SEL                                        BIT(4)
#define BIT_PMU_APB_DDR_CHN3_CGM_SEL                                        BIT(3)
#define BIT_PMU_APB_DDR_CHN2_CGM_SEL                                        BIT(2)
#define BIT_PMU_APB_DDR_CHN1_CGM_SEL                                        BIT(1)
#define BIT_PMU_APB_DDR_CHN0_CGM_SEL                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_DDR_CHN_SLEEP_CTRL1
// Register Offset : 0x00FC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_DDR_CHN9_AXI_STOP_SEL                                   BIT(9)
#define BIT_PMU_APB_DDR_CHN8_AXI_STOP_SEL                                   BIT(8)
#define BIT_PMU_APB_DDR_CHN7_AXI_STOP_SEL                                   BIT(7)
#define BIT_PMU_APB_DDR_CHN6_AXI_STOP_SEL                                   BIT(6)
#define BIT_PMU_APB_DDR_CHN5_AXI_STOP_SEL                                   BIT(5)
#define BIT_PMU_APB_DDR_CHN4_AXI_STOP_SEL                                   BIT(4)
#define BIT_PMU_APB_DDR_CHN3_AXI_STOP_SEL                                   BIT(3)
#define BIT_PMU_APB_DDR_CHN2_AXI_STOP_SEL                                   BIT(2)
#define BIT_PMU_APB_DDR_CHN1_AXI_STOP_SEL                                   BIT(1)
#define BIT_PMU_APB_DDR_CHN0_AXI_STOP_SEL                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_DDR_OP_MODE_CFG
// Register Offset : 0x012C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_DDR_OPERATE_MODE_BUSY                                   BIT(28)
#define BIT_PMU_APB_DDR_PUBL_RET_EN                                         BIT(27)
#define BIT_PMU_APB_DDR_PHY_ISO_RST_EN                                      BIT(26)
#define BIT_PMU_APB_DDR_UMCTL_RET_EN                                        BIT(25)
#define BIT_PMU_APB_DDR_PHY_AUTO_RET_EN                                     BIT(24)
#define BIT_PMU_APB_DDR_OPERATE_MODE_CNT_LMT(x)                             (((x) & 0xFF) << 16)
#define BIT_PMU_APB_DDR_OPERATE_MODE(x)                                     (((x) & 0x7) << 8)
#define BIT_PMU_APB_DDR_OPERATE_MODE_IDLE(x)                                (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_DDR_PHY_RET_CFG
// Register Offset : 0x0130
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_DDR_UMCTL_SOFT_RST                                      BIT(16)
#define BIT_PMU_APB_DDR_PHY_CKE_RET_EN                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CLK26M_SEL_CFG
// Register Offset : 0x0134
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_AON_RC_4M_SEL                                           BIT(8)
#define BIT_PMU_APB_GGE_26M_SEL                                             BIT(6)
#define BIT_PMU_APB_PUB_26M_SEL                                             BIT(5)
#define BIT_PMU_APB_AON_26M_SEL                                             BIT(4)
#define BIT_PMU_APB_PUBCP_26M_SEL                                           BIT(2)
#define BIT_PMU_APB_WTLCP_26M_SEL                                           BIT(1)
#define BIT_PMU_APB_AP_26M_SEL                                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_BISR_DONE_STATUS
// Register Offset : 0x0138
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P4_BISR_DONE                               BIT(20)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_BISR_DONE                               BIT(19)
#define BIT_PMU_APB_PD_AON_MEM_BISR_DONE                                    BIT(18)
#define BIT_PMU_APB_PD_PUBCP_SYS_BISR_DONE                                  BIT(17)
#define BIT_PMU_APB_PD_WTLCP_SYS_BISR_DONE                                  BIT(16)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_BISR_DONE                              BIT(15)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_BISR_DONE                              BIT(14)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_BISR_DONE                                BIT(13)
#define BIT_PMU_APB_PD_WTLCP_LDSP_BISR_DONE                                 BIT(12)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_BISR_DONE                               BIT(10)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_BISR_DONE                               BIT(9)
#define BIT_PMU_APB_PD_WTLCP_TD_BISR_DONE                                   BIT(8)
#define BIT_PMU_APB_PD_MM_TOP_BISR_DONE                                     BIT(7)
#define BIT_PMU_APB_PD_GPU_TOP_BISR_DONE                                    BIT(6)
#define BIT_PMU_APB_PD_AP_SYS_BISR_DONE                                     BIT(5)
#define BIT_PMU_APB_PD_CA7_TOP_BISR_DONE                                    BIT(4)
#define BIT_PMU_APB_PD_CA7_C3_BISR_DONE                                     BIT(3)
#define BIT_PMU_APB_PD_CA7_C2_BISR_DONE                                     BIT(2)
#define BIT_PMU_APB_PD_CA7_C1_BISR_DONE                                     BIT(1)
#define BIT_PMU_APB_PD_CA7_C0_BISR_DONE                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_BISR_BUSY_STATUS
// Register Offset : 0x013C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P4_BISR_BUSY                               BIT(20)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_BISR_BUSY                               BIT(19)
#define BIT_PMU_APB_PD_AON_MEM_BISR_BUSY                                    BIT(18)
#define BIT_PMU_APB_PD_PUBCP_SYS_BISR_BUSY                                  BIT(17)
#define BIT_PMU_APB_PD_WTLCP_SYS_BISR_BUSY                                  BIT(16)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_BISR_BUSY                              BIT(15)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_BISR_BUSY                              BIT(14)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_BISR_BUSY                                BIT(13)
#define BIT_PMU_APB_PD_WTLCP_LDSP_BISR_BUSY                                 BIT(12)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_BISR_BUSY                               BIT(10)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_BISR_BUSY                               BIT(9)
#define BIT_PMU_APB_PD_WTLCP_TD_BISR_BUSY                                   BIT(8)
#define BIT_PMU_APB_PD_MM_TOP_BISR_BUSY                                     BIT(7)
#define BIT_PMU_APB_PD_GPU_TOP_BISR_BUSY                                    BIT(6)
#define BIT_PMU_APB_PD_AP_SYS_BISR_BUSY                                     BIT(5)
#define BIT_PMU_APB_PD_CA7_TOP_BISR_BUSY                                    BIT(4)
#define BIT_PMU_APB_PD_CA7_C3_BISR_BUSY                                     BIT(3)
#define BIT_PMU_APB_PD_CA7_C2_BISR_BUSY                                     BIT(2)
#define BIT_PMU_APB_PD_CA7_C1_BISR_BUSY                                     BIT(1)
#define BIT_PMU_APB_PD_CA7_C0_BISR_BUSY                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_BISR_BYP_CFG
// Register Offset : 0x0140
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P4_BISR_FORCE_BYP                          BIT(20)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_BISR_FORCE_BYP                          BIT(19)
#define BIT_PMU_APB_PD_AON_MEM_BISR_FORCE_BYP                               BIT(18)
#define BIT_PMU_APB_PD_PUBCP_SYS_BISR_FORCE_BYP                             BIT(17)
#define BIT_PMU_APB_PD_WTLCP_SYS_BISR_FORCE_BYP                             BIT(16)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_BISR_FORCE_BYP                         BIT(15)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_BISR_FORCE_BYP                         BIT(14)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_BISR_FORCE_BYP                           BIT(13)
#define BIT_PMU_APB_PD_WTLCP_LDSP_BISR_FORCE_BYP                            BIT(12)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_BISR_FORCE_BYP                          BIT(10)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_BISR_FORCE_BYP                          BIT(9)
#define BIT_PMU_APB_PD_WTLCP_TD_BISR_FORCE_BYP                              BIT(8)
#define BIT_PMU_APB_PD_MM_TOP_BISR_FORCE_BYP                                BIT(7)
#define BIT_PMU_APB_PD_GPU_TOP_BISR_FORCE_BYP                               BIT(6)
#define BIT_PMU_APB_PD_AP_SYS_BISR_FORCE_BYP                                BIT(5)
#define BIT_PMU_APB_PD_CA7_TOP_BISR_FORCE_BYP                               BIT(4)
#define BIT_PMU_APB_PD_CA7_C3_BISR_FORCE_BYP                                BIT(3)
#define BIT_PMU_APB_PD_CA7_C2_BISR_FORCE_BYP                                BIT(2)
#define BIT_PMU_APB_PD_CA7_C1_BISR_FORCE_BYP                                BIT(1)
#define BIT_PMU_APB_PD_CA7_C0_BISR_FORCE_BYP                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_BISR_EN_CFG
// Register Offset : 0x0144
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P4_BISR_FORCE_EN                           BIT(20)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_BISR_FORCE_EN                           BIT(19)
#define BIT_PMU_APB_PD_AON_MEM_BISR_FORCE_EN                                BIT(18)
#define BIT_PMU_APB_PD_PUBCP_SYS_BISR_FORCE_EN                              BIT(17)
#define BIT_PMU_APB_PD_WTLCP_SYS_BISR_FORCE_EN                              BIT(16)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_BISR_FORCE_EN                          BIT(15)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_BISR_FORCE_EN                          BIT(14)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_BISR_FORCE_EN                            BIT(13)
#define BIT_PMU_APB_PD_WTLCP_LDSP_BISR_FORCE_EN                             BIT(12)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_BISR_FORCE_EN                           BIT(10)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_BISR_FORCE_EN                           BIT(9)
#define BIT_PMU_APB_PD_WTLCP_TD_BISR_FORCE_EN                               BIT(8)
#define BIT_PMU_APB_PD_MM_TOP_BISR_FORCE_EN                                 BIT(7)
#define BIT_PMU_APB_PD_GPU_TOP_BISR_FORCE_EN                                BIT(6)
#define BIT_PMU_APB_PD_AP_SYS_BISR_FORCE_EN                                 BIT(5)
#define BIT_PMU_APB_PD_CA7_TOP_BISR_FORCE_EN                                BIT(4)
#define BIT_PMU_APB_PD_CA7_C3_BISR_FORCE_EN                                 BIT(3)
#define BIT_PMU_APB_PD_CA7_C2_BISR_FORCE_EN                                 BIT(2)
#define BIT_PMU_APB_PD_CA7_C1_BISR_FORCE_EN                                 BIT(1)
#define BIT_PMU_APB_PD_CA7_C0_BISR_FORCE_EN                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CGM_AUTO_GATE_SEL_CFG0
// Register Offset : 0x0148
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CGM_AUTO_GATE_SEL_CFG0(x)                               (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CGM_AUTO_GATE_SEL_CFG1
// Register Offset : 0x014C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CGM_AUTO_GATE_SEL_CFG1(x)                               (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CGM_AUTO_GATE_SEL_CFG2
// Register Offset : 0x0150
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CGM_AUTO_GATE_SEL_CFG2(x)                               (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CGM_AUTO_GATE_SEL_CFG3
// Register Offset : 0x0154
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CGM_AUTO_GATE_SEL_CFG3(x)                               (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CGM_FORCE_EN_CFG0
// Register Offset : 0x0158
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CGM_FORCE_EN_CFG0(x)                                    (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CGM_FORCE_EN_CFG1
// Register Offset : 0x015C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CGM_FORCE_EN_CFG1(x)                                    (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CGM_FORCE_EN_CFG2
// Register Offset : 0x0160
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CGM_FORCE_EN_CFG2(x)                                    (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CGM_FORCE_EN_CFG3
// Register Offset : 0x0164
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CGM_FORCE_EN_CFG3(x)                                    (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_SLEEP_XTLON_CTRL
// Register Offset : 0x0168
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_ARM7_SLEEP_XTL_ON                                       BIT(5)
#define BIT_PMU_APB_PUBCP_SLEEP_XTL_ON                                      BIT(2)
#define BIT_PMU_APB_WTLCP_SLEEP_XTL_ON                                      BIT(1)
#define BIT_PMU_APB_AP_SLEEP_XTL_ON                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_MEM_SLP_CFG
// Register Offset : 0x016C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_MEM_SLP_CFG(x)                                          (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_MEM_SD_CFG
// Register Offset : 0x0170
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_MEM_SD_CFG(x)                                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CA7_CORE_PU_LOCK
// Register Offset : 0x0174
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CA7_C3_GIC_WAKEUP_EN                                    BIT(11)
#define BIT_PMU_APB_CA7_C2_GIC_WAKEUP_EN                                    BIT(10)
#define BIT_PMU_APB_CA7_C1_GIC_WAKEUP_EN                                    BIT(9)
#define BIT_PMU_APB_CA7_C0_GIC_WAKEUP_EN                                    BIT(8)
#define BIT_PMU_APB_CA7_C3_PU_LOCK                                          BIT(3)
#define BIT_PMU_APB_CA7_C2_PU_LOCK                                          BIT(2)
#define BIT_PMU_APB_CA7_C1_PU_LOCK                                          BIT(1)
#define BIT_PMU_APB_CA7_C0_PU_LOCK                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_ARM7_HOLD_CGM_EN
// Register Offset : 0x0178
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_CA7_TOP_CMG_HOLD_EN                                  BIT(4)
#define BIT_PMU_APB_PD_CA7_C3_CMG_HOLD_EN                                   BIT(3)
#define BIT_PMU_APB_PD_CA7_C2_CMG_HOLD_EN                                   BIT(2)
#define BIT_PMU_APB_PD_CA7_C1_CMG_HOLD_EN                                   BIT(1)
#define BIT_PMU_APB_PD_CA7_C0_CMG_HOLD_EN                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PWR_CNT_WAIT_CFG0
// Register Offset : 0x017C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUBCP_PWR_WAIT_CNT(x)                                   (((x) & 0xFF) << 16)
#define BIT_PMU_APB_WTLCP_PWR_WAIT_CNT(x)                                   (((x) & 0xFF) << 8)
#define BIT_PMU_APB_AP_PWR_WAIT_CNT(x)                                      (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PWR_CNT_WAIT_CFG1
// Register Offset : 0x0180
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_ARM7_PWR_WAIT_CNT(x)                                    (((x) & 0xFF) << 8)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_RC0_REL_CFG
// Register Offset : 0x0184
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_RC0_ARM7_SEL                                            BIT(5)
#define BIT_PMU_APB_RC0_PUBCP_SEL                                           BIT(2)
#define BIT_PMU_APB_RC0_WTLCP_SEL                                           BIT(1)
#define BIT_PMU_APB_RC0_AP_SEL                                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_RC1_REL_CFG
// Register Offset : 0x0188
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_RC1_ARM7_SEL                                            BIT(5)
#define BIT_PMU_APB_RC1_PUBCP_SEL                                           BIT(2)
#define BIT_PMU_APB_RC1_WTLCP_SEL                                           BIT(1)
#define BIT_PMU_APB_RC1_AP_SEL                                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_RC_CNT_WAIT_CFG
// Register Offset : 0x018C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_RC1_WAIT_CNT(x)                                         (((x) & 0xFF) << 8)
#define BIT_PMU_APB_RC0_WAIT_CNT(x)                                         (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_MEM_AUTO_SLP_CFG
// Register Offset : 0x0190
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_MEM_AUTO_SLP_EN(x)                                      (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_MEM_AUTO_SD_CFG
// Register Offset : 0x0194
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_MEM_AUTO_SD_EN(x)                                       (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_WAKEUP_LOCK_EN
// Register Offset : 0x01A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUBCP_SYS_WAKEUP_LOCK_EN                                BIT(24)
#define BIT_PMU_APB_WTLCP_SYS_WAKEUP_LOCK_EN                                BIT(23)
#define BIT_PMU_APB_AP_SYS_WAKEUP_LOCK_EN                                   BIT(22)
#define BIT_PMU_APB_PD_PUB_SYS_WAKEUP_LOCK_EN                               BIT(21)
#define BIT_PMU_APB_PD_WTLCP_LTE_P4_WAKEUP_LOCK_EN                          BIT(19)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_WAKEUP_LOCK_EN                          BIT(18)
#define BIT_PMU_APB_PD_PUBCP_SYS_WAKEUP_LOCK_EN                             BIT(17)
#define BIT_PMU_APB_PD_WTLCP_SYS_WAKEUP_LOCK_EN                             BIT(16)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_WAKEUP_LOCK_EN                         BIT(15)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_WAKEUP_LOCK_EN                         BIT(14)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_WAKEUP_LOCK_EN                           BIT(13)
#define BIT_PMU_APB_PD_WTLCP_LDSP_WAKEUP_LOCK_EN                            BIT(12)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_WAKEUP_LOCK_EN                          BIT(10)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_WAKEUP_LOCK_EN                          BIT(9)
#define BIT_PMU_APB_PD_WTLCP_TD_WAKEUP_LOCK_EN                              BIT(8)
#define BIT_PMU_APB_PD_MM_TOP_WAKEUP_LOCK_EN                                BIT(7)
#define BIT_PMU_APB_PD_GPU_TOP_WAKEUP_LOCK_EN                               BIT(6)
#define BIT_PMU_APB_PD_AP_SYS_WAKEUP_LOCK_EN                                BIT(5)
#define BIT_PMU_APB_PD_CA7_TOP_WAKEUP_LOCK_EN                               BIT(4)
#define BIT_PMU_APB_PD_CA7_C3_WAKEUP_LOCK_EN                                BIT(3)
#define BIT_PMU_APB_PD_CA7_C2_WAKEUP_LOCK_EN                                BIT(2)
#define BIT_PMU_APB_PD_CA7_C1_WAKEUP_LOCK_EN                                BIT(1)
#define BIT_PMU_APB_PD_CA7_C0_WAKEUP_LOCK_EN                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_WTLCP_TGDSP_CORE_INT_DISABLE
// Register Offset : 0x01B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_WTLCP_TGDSP_CORE_INT_DISABLE                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_WTLCP_LDSP_CORE_INT_DISABLE
// Register Offset : 0x01B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_WTLCP_LDSP_CORE_INT_DISABLE                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PUBCP_CORE_INT_DISABLE
// Register Offset : 0x01B8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUBCP_CORE_INT_DISABLE                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CA7_C0_CORE_INT_DISABLE
// Register Offset : 0x01BC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CA7_C0_CORE_INT_DISABLE                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CA7_C1_CORE_INT_DISABLE
// Register Offset : 0x01C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CA7_C1_CORE_INT_DISABLE                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CA7_C2_CORE_INT_DISABLE
// Register Offset : 0x01C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CA7_C2_CORE_INT_DISABLE                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CA7_C3_CORE_INT_DISABLE
// Register Offset : 0x01C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CA7_C3_CORE_INT_DISABLE                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_WTLCP_TGDSP_DSLP_ENA
// Register Offset : 0x0200
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_WTLCP_TGDSP_DSLP_ENA                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_WTLCP_LDSP_DSLP_ENA
// Register Offset : 0x0204
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_WTLCP_LDSP_DSLP_ENA                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_AP_DSLP_ENA
// Register Offset : 0x0208
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_AP_DSLP_ENA                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PUBCP_DSLP_ENA
// Register Offset : 0x020C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUBCP_DSLP_ENA                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_WTLCP_DSLP_ENA
// Register Offset : 0x0210
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_WTLCP_DSLP_ENA                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CA7_TOP_DSLP_ENA
// Register Offset : 0x0214
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CA7_TOP_DSLP_ENA                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_SYS_PUB_DSLP_ENA
// Register Offset : 0x0220
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_WTLCP_PUB_DSLP_ENA                                      BIT(2)
#define BIT_PMU_APB_PUBCP_PUB_DSLP_ENA                                      BIT(1)
#define BIT_PMU_APB_AP_PUB_DSLP_ENA                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_AP_AUTO_LSLP_ENA
// Register Offset : 0x0224
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_AP_AUTO_LSLP_ENA                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PUBCP_AUTO_LSLP_ENA
// Register Offset : 0x0228
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUBCP_AUTO_LSLP_ENA                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_WTLCP_AUTO_LSLP_ENA
// Register Offset : 0x022C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_WTLCP_AUTO_LSLP_ENA                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_LIGHT_SLEEP_ENABLE
// Register Offset : 0x0230
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_DMA_CHN3_LSLP_ENA                                       BIT(18)
#define BIT_PMU_APB_DMA_CHN1_LSLP_ENA                                       BIT(17)
#define BIT_PMU_APB_DMA_CHNALL_LSLP_ENA                                     BIT(16)
#define BIT_PMU_APB_WTLCP_LSLP_SEL                                          BIT(10)
#define BIT_PMU_APB_PUBCP_LSLP_SEL                                          BIT(9)
#define BIT_PMU_APB_AP_LSLP_SEL                                             BIT(8)
#define BIT_PMU_APB_AON_DMA_LSLP_ENA                                        BIT(3)
#define BIT_PMU_APB_WTLCP_LSLP_ENA                                          BIT(2)
#define BIT_PMU_APB_PUBCP_LSLP_ENA                                          BIT(1)
#define BIT_PMU_APB_AP_LSLP_ENA                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_ARM7_LIGHT_SLEEP
// Register Offset : 0x0234
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_ARM7_LIGHT_SLEEP                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_SYS_DOZE_DSLP_ENA
// Register Offset : 0x0240
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_WTLCP_DOZE_DSLP_ENA                                     BIT(2)
#define BIT_PMU_APB_PUBCP_DOZE_DSLP_ENA                                     BIT(1)
#define BIT_PMU_APB_AP_DOZE_DSLP_ENA                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PUB_ACC_RDY
// Register Offset : 0x0250
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUB_ACC_RDY                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PUB_CLK_RDY
// Register Offset : 0x0254
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUB_CLK_RDY                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_EIC_SEL
// Register Offset : 0x0258
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_EIC_LIGHT_SLEEP_SEL                                     BIT(1)
#define BIT_PMU_APB_EIC_DEEP_SLEEP_SEL                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_AXI_LP_CTRL_DISABLE
// Register Offset : 0x0260
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_AXI_LP_CTRL_DISABLE                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PMU_DEBUG
// Register Offset : 0x0270
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PMU_DEBUG(x)                                            (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_SLEEP_CNT_CLR
// Register Offset : 0x0274
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUBCP_PUB_DEEP_SLEEP_CNT_CLR                            BIT(14)
#define BIT_PMU_APB_WTLCP_PUB_DEEP_SLEEP_CNT_CLR                            BIT(13)
#define BIT_PMU_APB_AP_PUB_DEEP_SLEEP_CNT_CLR                               BIT(12)
#define BIT_PMU_APB_PUBCP_DOZE_SLEEP_CNT_CLR                                BIT(11)
#define BIT_PMU_APB_WTLCP_DOZE_SLEEP_CNT_CLR                                BIT(10)
#define BIT_PMU_APB_AP_DOZE_SLEEP_CNT_CLR                                   BIT(9)
#define BIT_PMU_APB_ARM7_DEEP_SLEEP_CNT_CLR                                 BIT(8)
#define BIT_PMU_APB_PUB_DEEP_SLEEP_CNT_CLR                                  BIT(7)
#define BIT_PMU_APB_PUBCP_DEEP_SLEEP_CNT_CLR                                BIT(6)
#define BIT_PMU_APB_WTLCP_DEEP_SLEEP_CNT_CLR                                BIT(5)
#define BIT_PMU_APB_AP_DEEP_SLEEP_CNT_CLR                                   BIT(4)
#define BIT_PMU_APB_PUB_LIGHT_SLEEP_CNT_CLR                                 BIT(3)
#define BIT_PMU_APB_PUBCP_LIGHT_SLEEP_CNT_CLR                               BIT(2)
#define BIT_PMU_APB_WTLCP_LIGHT_SLEEP_CNT_CLR                               BIT(1)
#define BIT_PMU_APB_AP_LIGHT_SLEEP_CNT_CLR                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_LVDSRFPLL_REL_CFG
// Register Offset : 0x0280
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_LVDSRFPLL_REF_SEL(x)                                    (((x) & 0x3) << 8)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PAD_OUT_ADIE_CTRL0
// Register Offset : 0x0290
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_POL_SEL                              BIT(26)
#define BIT_PMU_APB_PAD_OUT_XTL_EN_POL_SEL                                  BIT(25)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_POL_SEL                              BIT(24)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_EXT_XTL_PD_MASK                      BIT(21)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_ARM7_DEEP_SLEEP_MASK                 BIT(20)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_CA7_TOP_PD_MASK                      BIT(19)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_WTLCP_DEEP_SLEEP_MASK                BIT(18)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_PUBCP_DEEP_SLEEP_MASK                BIT(17)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_AP_DEEP_SLEEP_MASK                   BIT(16)
#define BIT_PMU_APB_PAD_OUT_XTL_EN_EXT_XTL_PD_MASK                          BIT(15)
#define BIT_PMU_APB_PAD_OUT_XTL_EN_ARM7_DEEP_SLEEP_MASK                     BIT(14)
#define BIT_PMU_APB_PAD_OUT_XTL_EN_CA7_TOP_PD_MASK                          BIT(13)
#define BIT_PMU_APB_PAD_OUT_XTL_EN_WTLCP_DEEP_SLEEP_MASK                    BIT(12)
#define BIT_PMU_APB_PAD_OUT_XTL_EN_PUBCP_DEEP_SLEEP_MASK                    BIT(11)
#define BIT_PMU_APB_PAD_OUT_XTL_EN_AP_DEEP_SLEEP_MASK                       BIT(10)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_EXT_XTL_PD_MASK                      BIT(9)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_ARM7_DEEP_SLEEP_MASK                 BIT(8)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_CA7_TOP_PD_MASK                      BIT(7)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_WTLCP_DEEP_SLEEP_MASK                BIT(6)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_PUBCP_DEEP_SLEEP_MASK                BIT(5)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_AP_DEEP_SLEEP_MASK                   BIT(4)
#define BIT_PMU_APB_EXT_XTL3_COMB_EN                                        BIT(3)
#define BIT_PMU_APB_EXT_XTL2_COMB_EN                                        BIT(2)
#define BIT_PMU_APB_EXT_XTL1_COMB_EN                                        BIT(1)
#define BIT_PMU_APB_EXT_XTL0_COMB_EN                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PAD_OUT_ADIE_CTRL1
// Register Offset : 0x0294
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PAD_OUT_XTL_EN_PLL_PD_MASK                              BIT(23)
#define BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_PLL_PD_MASK                          BIT(22)
#define BIT_PMU_APB_PAD_OUT_XTL_BUF_EN1_PLL_PD_MASK                         BIT(21)
#define BIT_PMU_APB_PAD_OUT_XTL_BUF_EN0_PLL_PD_MASK                         BIT(20)
#define BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_PLL_PD_MASK                          BIT(19)
#define BIT_PMU_APB_PAD_OUT_XTL_BUF_EN1_POL_SEL                             BIT(18)
#define BIT_PMU_APB_PAD_OUT_XTL_BUF_EN0_POL_SEL                             BIT(17)
#define BIT_PMU_APB_PAD_OUT_XTL_BUF_EN1_EXT_XTL_PD_MASK                     BIT(14)
#define BIT_PMU_APB_PAD_OUT_XTL_BUF_EN1_ARM7_DEEP_SLEEP_MASK                BIT(13)
#define BIT_PMU_APB_PAD_OUT_XTL_BUF_EN1_CA7_TOP_PD_MASK                     BIT(12)
#define BIT_PMU_APB_PAD_OUT_XTL_BUF_EN1_WTLCP_DEEP_SLEEP_MASK               BIT(11)
#define BIT_PMU_APB_PAD_OUT_XTL_BUF_EN1_PUBCP_DEEP_SLEEP_MASK               BIT(10)
#define BIT_PMU_APB_PAD_OUT_XTL_BUF_EN1_AP_DEEP_SLEEP_MASK                  BIT(9)
#define BIT_PMU_APB_PAD_OUT_XTL_BUF_EN0_EXT_XTL_PD_MASK                     BIT(6)
#define BIT_PMU_APB_PAD_OUT_XTL_BUF_EN0_ARM7_DEEP_SLEEP_MASK                BIT(5)
#define BIT_PMU_APB_PAD_OUT_XTL_BUF_EN0_CA7_TOP_PD_MASK                     BIT(4)
#define BIT_PMU_APB_PAD_OUT_XTL_BUF_EN0_WTLCP_DEEP_SLEEP_MASK               BIT(3)
#define BIT_PMU_APB_PAD_OUT_XTL_BUF_EN0_PUBCP_DEEP_SLEEP_MASK               BIT(2)
#define BIT_PMU_APB_PAD_OUT_XTL_BUF_EN0_AP_DEEP_SLEEP_MASK                  BIT(1)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_BISR_FORCE_SEL
// Register Offset : 0x0300
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P4_BISR_FORCE_SEL                          BIT(20)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_BISR_FORCE_SEL                          BIT(19)
#define BIT_PMU_APB_PD_AON_MEM_BISR_FORCE_SEL                               BIT(18)
#define BIT_PMU_APB_PD_PUBCP_SYS_BISR_FORCE_SEL                             BIT(17)
#define BIT_PMU_APB_PD_WTLCP_SYS_BISR_FORCE_SEL                             BIT(16)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_BISR_FORCE_SEL                         BIT(15)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_BISR_FORCE_SEL                         BIT(14)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_BISR_FORCE_SEL                           BIT(13)
#define BIT_PMU_APB_PD_WTLCP_LDSP_BISR_FORCE_SEL                            BIT(12)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_BISR_FORCE_SEL                          BIT(10)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_BISR_FORCE_SEL                          BIT(9)
#define BIT_PMU_APB_PD_WTLCP_TD_BISR_FORCE_SEL                              BIT(8)
#define BIT_PMU_APB_PD_MM_TOP_BISR_FORCE_SEL                                BIT(7)
#define BIT_PMU_APB_PD_GPU_TOP_BISR_FORCE_SEL                               BIT(6)
#define BIT_PMU_APB_PD_AP_SYS_BISR_FORCE_SEL                                BIT(5)
#define BIT_PMU_APB_PD_CA7_TOP_BISR_FORCE_SEL                               BIT(4)
#define BIT_PMU_APB_PD_CA7_C3_BISR_FORCE_SEL                                BIT(3)
#define BIT_PMU_APB_PD_CA7_C2_BISR_FORCE_SEL                                BIT(2)
#define BIT_PMU_APB_PD_CA7_C1_BISR_FORCE_SEL                                BIT(1)
#define BIT_PMU_APB_PD_CA7_C0_BISR_FORCE_SEL                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_AON_MEM_CTRL
// Register Offset : 0x0330
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_ARM7_MEM_ALL_SEL                                        BIT(1)
#define BIT_PMU_APB_AON_MEM_ARM7_SEL                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PWR_DOMAIN_INT_CLR
// Register Offset : 0x0334
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_INT_REQ_PWR_DOWN_CLR(x)                                 (((x) & 0x3F) << 16)
#define BIT_PMU_APB_INT_REQ_PWR_UP_CLR(x)                                   (((x) & 0x3F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_CA7_C0_SHUTDOWN_MARK_STATUS
// Register Offset : 0x3000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_CA7_C0_SHUTDOWN_MARK(x)                              (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_CA7_C1_SHUTDOWN_MARK_STATUS
// Register Offset : 0x3004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_CA7_C1_SHUTDOWN_MARK(x)                              (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_CA7_C2_SHUTDOWN_MARK_STATUS
// Register Offset : 0x3008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_CA7_C2_SHUTDOWN_MARK(x)                              (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_CA7_C3_SHUTDOWN_MARK_STATUS
// Register Offset : 0x300C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_CA7_C3_SHUTDOWN_MARK(x)                              (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_CA7_TOP_SHUTDOWN_MARK_STATUS
// Register Offset : 0x3010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_CA7_TOP_SHUTDOWN_MARK(x)                             (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_AP_SYS_SHUTDOWN_MARK_STATUS
// Register Offset : 0x3014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_AP_SYS_SHUTDOWN_MARK(x)                              (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_GPU_TOP_SHUTDOWN_MARK_STATUS
// Register Offset : 0x3018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_GPU_TOP_SHUTDOWN_MARK(x)                             (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_MM_TOP_SHUTDOWN_MARK_STATUS
// Register Offset : 0x301C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_MM_TOP_SHUTDOWN_MARK(x)                              (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_TD_SHUTDOWN_MARK_STATUS
// Register Offset : 0x3020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_TD_SHUTDOWN_MARK(x)                            (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LTE_P1_SHUTDOWN_MARK_STATUS
// Register Offset : 0x3024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P1_SHUTDOWN_MARK(x)                        (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LTE_P2_SHUTDOWN_MARK_STATUS
// Register Offset : 0x3028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P2_SHUTDOWN_MARK(x)                        (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LDSP_SHUTDOWN_MARK_STATUS
// Register Offset : 0x3030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LDSP_SHUTDOWN_MARK(x)                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_TGDSP_SHUTDOWN_MARK_STATUS
// Register Offset : 0x3034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_TGDSP_SHUTDOWN_MARK(x)                         (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_HU3GE_A_SHUTDOWN_MARK_STATUS
// Register Offset : 0x3038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_SHUTDOWN_MARK(x)                       (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_HU3GE_B_SHUTDOWN_MARK_STATUS
// Register Offset : 0x303C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_SHUTDOWN_MARK(x)                       (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_SYS_SHUTDOWN_MARK_STATUS
// Register Offset : 0x3040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_SYS_SHUTDOWN_MARK(x)                           (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_PUBCP_SYS_SHUTDOWN_MARK_STATUS
// Register Offset : 0x3044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_PUBCP_SYS_SHUTDOWN_MARK(x)                           (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LTE_P3_SHUTDOWN_MARK_STATUS
// Register Offset : 0x3048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P3_SHUTDOWN_MARK(x)                        (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LTE_P4_SHUTDOWN_MARK_STATUS
// Register Offset : 0x304C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P4_SHUTDOWN_MARK(x)                        (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_PUB_SYS_SHUTDOWN_MARK_STATUS
// Register Offset : 0x3054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_PUB_SYS_SHUTDOWN_MARK(x)                             (((x) & 0xF))


#endif // _PMU_APB_REG_H
