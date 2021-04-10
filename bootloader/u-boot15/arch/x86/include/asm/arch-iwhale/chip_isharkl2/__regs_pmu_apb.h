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

#define CTL_BASE_PMU_APB SPRD_PMU_BASE


#define REG_PMU_APB_PD_TOP_PWR_CFG                             ( CTL_BASE_PMU_APB + 0x0018 )
#define REG_PMU_APB_PD_AON_SYS_PWR_CFG                         ( CTL_BASE_PMU_APB + 0x001C )
#define REG_PMU_APB_PD_PUBCP_SYS_PWR_CFG                       ( CTL_BASE_PMU_APB + 0x0020 )
#define REG_PMU_APB_PD_AGCP_SYS_PWR_CFG                        ( CTL_BASE_PMU_APB + 0x0024 )
#define REG_PMU_APB_PD_WTLCP_LTE_P4_PWR_CFG                    ( CTL_BASE_PMU_APB + 0x0028 )
#define REG_PMU_APB_PD_WTLCP_TGDSP_PWR_CFG                     ( CTL_BASE_PMU_APB + 0x002C )
#define REG_PMU_APB_PD_WTLCP_HU3GE_B_PWR_CFG                   ( CTL_BASE_PMU_APB + 0x0030 )
#define REG_PMU_APB_PD_AP_SYS_PWR_CFG                          ( CTL_BASE_PMU_APB + 0x0034 )
#define REG_PMU_APB_PD_GPU_PHANTOM_PWR_CFG1                    ( CTL_BASE_PMU_APB + 0x0038 )
#define REG_PMU_APB_PD_GPU_PHANTOM_PWR_CFG0                    ( CTL_BASE_PMU_APB + 0x003C )
#define REG_PMU_APB_PD_AGCP_DSP_PWR_CFG                        ( CTL_BASE_PMU_APB + 0x0040 )
#define REG_PMU_APB_PD_PUB0_SYS_PWR_CFG                        ( CTL_BASE_PMU_APB + 0x0044 )
#define REG_PMU_APB_PD_WTLCP_LTE_P1_PWR_CFG                    ( CTL_BASE_PMU_APB + 0x0048 )
#define REG_PMU_APB_PD_VSP_SYS_PWR_CFG                         ( CTL_BASE_PMU_APB + 0x004C )
#define REG_PMU_APB_PD_WTLCP_LDSP_PWR_CFG                      ( CTL_BASE_PMU_APB + 0x0050 )
#define REG_PMU_APB_PD_GPU_TOP_PWR_CFG1                        ( CTL_BASE_PMU_APB + 0x0054 )
#define REG_PMU_APB_PD_GPU_TOP_PWR_CFG0                        ( CTL_BASE_PMU_APB + 0x0058 )
#define REG_PMU_APB_PD_PUB1_SYS_PWR_CFG                        ( CTL_BASE_PMU_APB + 0x005C )
#define REG_PMU_APB_PD_WTLCP_TD_PWR_CFG                        ( CTL_BASE_PMU_APB + 0x0060 )
#define REG_PMU_APB_PD_BIA_PWR_CFG0                            ( CTL_BASE_PMU_APB + 0x0064 )
#define REG_PMU_APB_PD_BIA_PWR_CFG1                            ( CTL_BASE_PMU_APB + 0x0068 )
#define REG_PMU_APB_PD_BIA_PWR_CFG2                            ( CTL_BASE_PMU_APB + 0x006C )
#define REG_PMU_APB_PD_BIA_PWR_CFG3                            ( CTL_BASE_PMU_APB + 0x0070 )
#define REG_PMU_APB_PD_BIA_PWR_CFG4                            ( CTL_BASE_PMU_APB + 0x0074 )
#define REG_PMU_APB_PD_BIA_PWR_CFG5                            ( CTL_BASE_PMU_APB + 0x0078 )
#define REG_PMU_APB_PD_BIA_PWR_CFG6                            ( CTL_BASE_PMU_APB + 0x007C )
#define REG_PMU_APB_PD_WTLCP_LTE_P3_PWR_CFG                    ( CTL_BASE_PMU_APB + 0x0080 )
#define REG_PMU_APB_PD_WTLCP_SYS_PWR_CFG                       ( CTL_BASE_PMU_APB + 0x0084 )
#define REG_PMU_APB_PD_ISP_TOP_PWR_CFG                         ( CTL_BASE_PMU_APB + 0x0088 )
#define REG_PMU_APB_PD_WTLCP_LTE_P2_PWR_CFG                    ( CTL_BASE_PMU_APB + 0x008C )
#define REG_PMU_APB_PD_VSP_CORE_PWR_CFG                        ( CTL_BASE_PMU_APB + 0x0090 )
#define REG_PMU_APB_PD_CAM_SYS_PWR_CFG                         ( CTL_BASE_PMU_APB + 0x0094 )
#define REG_PMU_APB_PD_WTLCP_HU3GE_A_PWR_CFG                   ( CTL_BASE_PMU_APB + 0x0098 )
#define REG_PMU_APB_XTL_WAIT_CNT0                              ( CTL_BASE_PMU_APB + 0x00AC )
#define REG_PMU_APB_XTLBUF_WAIT_CNT0                           ( CTL_BASE_PMU_APB + 0x00BC )
#define REG_PMU_APB_PLL_WAIT_CNT1                              ( CTL_BASE_PMU_APB + 0x00C0 )
#define REG_PMU_APB_PLL_WAIT_CNT2                              ( CTL_BASE_PMU_APB + 0x00C4 )
#define REG_PMU_APB_PLL_WAIT_CNT3                              ( CTL_BASE_PMU_APB + 0x00C8 )
#define REG_PMU_APB_GPLL_REL_CFG                               ( CTL_BASE_PMU_APB + 0x00CC )
#define REG_PMU_APB_DPLL1_REL_CFG                              ( CTL_BASE_PMU_APB + 0x00D0 )
#define REG_PMU_APB_XTLBUF2_REL_CFG                            ( CTL_BASE_PMU_APB + 0x00D4 )
#define REG_PMU_APB_DPLL0_REL_CFG                              ( CTL_BASE_PMU_APB + 0x00D8 )
#define REG_PMU_APB_MPLL0_REL_CFG                              ( CTL_BASE_PMU_APB + 0x00DC )
#define REG_PMU_APB_XTLBUF1_REL_CFG                            ( CTL_BASE_PMU_APB + 0x00E0 )
#define REG_PMU_APB_RPLL1_REL_CFG                              ( CTL_BASE_PMU_APB + 0x00E4 )
#define REG_PMU_APB_DSPLL_REL_CFG                              ( CTL_BASE_PMU_APB + 0x00E8 )
#define REG_PMU_APB_XTLBUF0_REL_CFG                            ( CTL_BASE_PMU_APB + 0x00EC )
#define REG_PMU_APB_MPLL1_REL_CFG                              ( CTL_BASE_PMU_APB + 0x00F0 )
#define REG_PMU_APB_MPLL2_REL_CFG                              ( CTL_BASE_PMU_APB + 0x00F4 )
#define REG_PMU_APB_TWPLL_REL_CFG                              ( CTL_BASE_PMU_APB + 0x00F8 )
#define REG_PMU_APB_ISPPLL_REL_CFG                             ( CTL_BASE_PMU_APB + 0x00FC )
#define REG_PMU_APB_RC_REL_CFG                                 ( CTL_BASE_PMU_APB + 0x0100 )
#define REG_PMU_APB_LPLL0_REL_CFG                              ( CTL_BASE_PMU_APB + 0x0104 )
#define REG_PMU_APB_XTL0_REL_CFG                               ( CTL_BASE_PMU_APB + 0x0108 )
#define REG_PMU_APB_RPLL0_REL_CFG                              ( CTL_BASE_PMU_APB + 0x010C )
#define REG_PMU_APB_PWR_STATE_DBG1                             ( CTL_BASE_PMU_APB + 0x011C )
#define REG_PMU_APB_PWR_STATE_DBG2                             ( CTL_BASE_PMU_APB + 0x0120 )
#define REG_PMU_APB_PWR_STATE_DBG3                             ( CTL_BASE_PMU_APB + 0x0124 )
#define REG_PMU_APB_PWR_STATE_DBG4                             ( CTL_BASE_PMU_APB + 0x0128 )
#define REG_PMU_APB_PUB0_SYS_SLEEP_CTRL                        ( CTL_BASE_PMU_APB + 0x012C )
#define REG_PMU_APB_PUB1_SYS_SLEEP_CTRL                        ( CTL_BASE_PMU_APB + 0x0130 )
#define REG_PMU_APB_AP_SYS_SLEEP_CTRL                          ( CTL_BASE_PMU_APB + 0x0134 )
#define REG_PMU_APB_CM4_SYS_SLEEP_CTRL                         ( CTL_BASE_PMU_APB + 0x0138 )
#define REG_PMU_APB_WTLCP_SYS_SLEEP_CTRL                       ( CTL_BASE_PMU_APB + 0x0144 )
#define REG_PMU_APB_AGCP_SYS_SLEEP_CTRL                        ( CTL_BASE_PMU_APB + 0x0148 )
#define REG_PMU_APB_PUBCP_SYS_SLEEP_CTRL                       ( CTL_BASE_PMU_APB + 0x014C )
#define REG_PMU_APB_SYS_SLP_STATUS0                            ( CTL_BASE_PMU_APB + 0x015C )
#define REG_PMU_APB_BISR_DONE_STATUS0                          ( CTL_BASE_PMU_APB + 0x0160 )
#define REG_PMU_APB_BISR_BUSY_STATUS0                          ( CTL_BASE_PMU_APB + 0x0170 )
#define REG_PMU_APB_BISR_BYP_CFG0                              ( CTL_BASE_PMU_APB + 0x0178 )
#define REG_PMU_APB_BISR_FORCE_EN_CFG0                         ( CTL_BASE_PMU_APB + 0x0180 )
#define REG_PMU_APB_SLEEP_XTL_ON_CTRL0                         ( CTL_BASE_PMU_APB + 0x0184 )
#define REG_PMU_APB_PWR_WAIT_CNT_CFG1                          ( CTL_BASE_PMU_APB + 0x018C )
#define REG_PMU_APB_PWR_WAIT_CNT_CFG0                          ( CTL_BASE_PMU_APB + 0x0190 )
#define REG_PMU_APB_PWR_PD_WAIT_CNT_CFG1                       ( CTL_BASE_PMU_APB + 0x0198 )
#define REG_PMU_APB_PWR_PD_WAIT_CNT_CFG0                       ( CTL_BASE_PMU_APB + 0x019C )
#define REG_PMU_APB_PD_PUBCP_SYS_CORE_INT_DISABLE              ( CTL_BASE_PMU_APB + 0x01A4 )
#define REG_PMU_APB_PD_WTLCP_TGDSP_CORE_INT_DISABLE            ( CTL_BASE_PMU_APB + 0x01A8 )
#define REG_PMU_APB_PD_AGCP_DSP_CORE_INT_DISABLE               ( CTL_BASE_PMU_APB + 0x01AC )
#define REG_PMU_APB_PD_WTLCP_LDSP_CORE_INT_DISABLE             ( CTL_BASE_PMU_APB + 0x01B0 )
#define REG_PMU_APB_PD_BIA_CORE_INT_DISABLE                    ( CTL_BASE_PMU_APB + 0x01B4 )
#define REG_PMU_APB_AP_SYS_DSLP_ENA                            ( CTL_BASE_PMU_APB + 0x01C4 )
#define REG_PMU_APB_CM4_SYS_DSLP_ENA                           ( CTL_BASE_PMU_APB + 0x01C8 )
#define REG_PMU_APB_WTLCP_SYS_DSLP_ENA                         ( CTL_BASE_PMU_APB + 0x01CC )
#define REG_PMU_APB_AGCP_SYS_DSLP_ENA                          ( CTL_BASE_PMU_APB + 0x01D0 )
#define REG_PMU_APB_PUBCP_SYS_DSLP_ENA                         ( CTL_BASE_PMU_APB + 0x01D4 )
#define REG_PMU_APB_PD_WTLCP_TGDSP_DSLP_ENA                    ( CTL_BASE_PMU_APB + 0x01E4 )
#define REG_PMU_APB_PD_AGCP_DSP_DSLP_ENA                       ( CTL_BASE_PMU_APB + 0x01E8 )
#define REG_PMU_APB_PD_WTLCP_LDSP_DSLP_ENA                     ( CTL_BASE_PMU_APB + 0x01EC )
#define REG_PMU_APB_PD_BIA_DSLP_ENA                            ( CTL_BASE_PMU_APB + 0x01F0 )
#define REG_PMU_APB_PWR_ST_DBG_DLY0                            ( CTL_BASE_PMU_APB + 0x01F4 )
#define REG_PMU_APB_PWR_ST_DBG_DLY1                            ( CTL_BASE_PMU_APB + 0x01F8 )
#define REG_PMU_APB_PWR_ST_DBG_DLY2                            ( CTL_BASE_PMU_APB + 0x01FC )
#define REG_PMU_APB_LIGHT_SLEEP_ENABLE0                        ( CTL_BASE_PMU_APB + 0x0204 )
#define REG_PMU_APB_PUB_DEEP_SLEEP_ENABLE0                     ( CTL_BASE_PMU_APB + 0x0208 )
#define REG_PMU_APB_DOZE_SLEEP_ENABLE0                         ( CTL_BASE_PMU_APB + 0x0214 )
#define REG_PMU_APB_PLL_CNT_DONE_STATUS0                       ( CTL_BASE_PMU_APB + 0x021C )
#define REG_PMU_APB_POWER_SWITCH_ACK_D_STATUS0                 ( CTL_BASE_PMU_APB + 0x0224 )
#define REG_PMU_APB_POWER_SWITCH_ACK_M_STATUS0                 ( CTL_BASE_PMU_APB + 0x022C )
#define REG_PMU_APB_CGM_PMU_SEL_CFG                            ( CTL_BASE_PMU_APB + 0x0234 )
#define REG_PMU_APB_WTLCP_TGDSP_WAKEUP_SOURCE_EN0              ( CTL_BASE_PMU_APB + 0x0238 )
#define REG_PMU_APB_AGCP_DSP_WAKEUP_SOURCE_EN0                 ( CTL_BASE_PMU_APB + 0x023C )
#define REG_PMU_APB_WTLCP_LDSP_WAKEUP_SOURCE_EN0               ( CTL_BASE_PMU_APB + 0x0240 )
#define REG_PMU_APB_WTLCP_SYS_WAKEUP_SOURCE_EN0                ( CTL_BASE_PMU_APB + 0x0244 )
#define REG_PMU_APB_CM4_SYS_WAKEUP_SOURCE_EN0                  ( CTL_BASE_PMU_APB + 0x0248 )
#define REG_PMU_APB_CM4_SYS_WAKEUP_SOURCE_EN1                  ( CTL_BASE_PMU_APB + 0x024C )
#define REG_PMU_APB_PUBCP_CR5_WAKEUP_SOURCE_EN0                ( CTL_BASE_PMU_APB + 0x0250 )
#define REG_PMU_APB_BASEIA_WAKEUP_SOURCE_EN0                   ( CTL_BASE_PMU_APB + 0x0254 )
#define REG_PMU_APB_BASEIA_WAKEUP_SOURCE_EN1                   ( CTL_BASE_PMU_APB + 0x0258 )
#define REG_PMU_APB_BASEIA_WAKEUP_SOURCE_EN2                   ( CTL_BASE_PMU_APB + 0x025C )
#define REG_PMU_APB_BASEIA_WAKEUP_SOURCE_EN3                   ( CTL_BASE_PMU_APB + 0x0260 )
#define REG_PMU_APB_PD_PUBCP_SYS_SHUTDOWN_MARK_STATUS          ( CTL_BASE_PMU_APB + 0x0268 )
#define REG_PMU_APB_PD_AGCP_SYS_SHUTDOWN_MARK_STATUS           ( CTL_BASE_PMU_APB + 0x026C )
#define REG_PMU_APB_PD_WTLCP_LTE_P4_SHUTDOWN_MARK_STATUS       ( CTL_BASE_PMU_APB + 0x0270 )
#define REG_PMU_APB_PD_WTLCP_TGDSP_SHUTDOWN_MARK_STATUS        ( CTL_BASE_PMU_APB + 0x0274 )
#define REG_PMU_APB_PD_TOP_SHUTDOWN_MARK_STATUS                ( CTL_BASE_PMU_APB + 0x0278 )
#define REG_PMU_APB_PD_WTLCP_HU3GE_B_SHUTDOWN_MARK_STATUS      ( CTL_BASE_PMU_APB + 0x027C )
#define REG_PMU_APB_PD_AP_SYS_SHUTDOWN_MARK_STATUS             ( CTL_BASE_PMU_APB + 0x0280 )
#define REG_PMU_APB_PD_GPU_PHANTOM_SHUTDOWN_MARK_STATUS        ( CTL_BASE_PMU_APB + 0x0284 )
#define REG_PMU_APB_PD_AGCP_DSP_SHUTDOWN_MARK_STATUS           ( CTL_BASE_PMU_APB + 0x0288 )
#define REG_PMU_APB_PD_PUB0_SYS_SHUTDOWN_MARK_STATUS           ( CTL_BASE_PMU_APB + 0x028C )
#define REG_PMU_APB_PD_WTLCP_LTE_P1_SHUTDOWN_MARK_STATUS       ( CTL_BASE_PMU_APB + 0x0290 )
#define REG_PMU_APB_PD_VSP_SYS_SHUTDOWN_MARK_STATUS            ( CTL_BASE_PMU_APB + 0x0294 )
#define REG_PMU_APB_PD_WTLCP_LDSP_SHUTDOWN_MARK_STATUS         ( CTL_BASE_PMU_APB + 0x0298 )
#define REG_PMU_APB_PD_GPU_TOP_SHUTDOWN_MARK_STATUS            ( CTL_BASE_PMU_APB + 0x029C )
#define REG_PMU_APB_PD_PUB1_SYS_SHUTDOWN_MARK_STATUS           ( CTL_BASE_PMU_APB + 0x02A0 )
#define REG_PMU_APB_PD_WTLCP_TD_SHUTDOWN_MARK_STATUS           ( CTL_BASE_PMU_APB + 0x02A4 )
#define REG_PMU_APB_PD_BIA_SHUTDOWN_MARK_STATUS                ( CTL_BASE_PMU_APB + 0x02A8 )
#define REG_PMU_APB_PD_WTLCP_LTE_P3_SHUTDOWN_MARK_STATUS       ( CTL_BASE_PMU_APB + 0x02AC )
#define REG_PMU_APB_PD_WTLCP_SYS_SHUTDOWN_MARK_STATUS          ( CTL_BASE_PMU_APB + 0x02B0 )
#define REG_PMU_APB_PD_ISP_TOP_SHUTDOWN_MARK_STATUS            ( CTL_BASE_PMU_APB + 0x02B4 )
#define REG_PMU_APB_PD_WTLCP_LTE_P2_SHUTDOWN_MARK_STATUS       ( CTL_BASE_PMU_APB + 0x02B8 )
#define REG_PMU_APB_PD_VSP_CORE_SHUTDOWN_MARK_STATUS           ( CTL_BASE_PMU_APB + 0x02BC )
#define REG_PMU_APB_PD_CAM_SYS_SHUTDOWN_MARK_STATUS            ( CTL_BASE_PMU_APB + 0x02C0 )
#define REG_PMU_APB_PD_WTLCP_HU3GE_A_SHUTDOWN_MARK_STATUS      ( CTL_BASE_PMU_APB + 0x02C4 )
#define REG_PMU_APB_DDR0_ACC_RDY                               ( CTL_BASE_PMU_APB + 0x02CC )
#define REG_PMU_APB_DDR0_LIGHT_ACC_RDY                         ( CTL_BASE_PMU_APB + 0x02D0 )
#define REG_PMU_APB_DDR0_SLP_CFG                               ( CTL_BASE_PMU_APB + 0x02D4 )
#define REG_PMU_APB_DDR1_ACC_RDY                               ( CTL_BASE_PMU_APB + 0x02D8 )
#define REG_PMU_APB_DDR1_LIGHT_ACC_RDY                         ( CTL_BASE_PMU_APB + 0x02DC )
#define REG_PMU_APB_DDR1_SLP_CFG                               ( CTL_BASE_PMU_APB + 0x02E0 )
#define REG_PMU_APB_PD_CM4_CORE_INT_DISABLE                    ( CTL_BASE_PMU_APB + 0x02E4 )

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_TOP_PWR_CFG
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_TOP_FORCE_SHUTDOWN                                               BIT(25)
#define BIT_PMU_APB_PD_TOP_AUTO_SHUTDOWN_EN                                             BIT(24)
#define BIT_PMU_APB_PD_TOP_PWR_ON_DLY(x)                                                (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_TOP_PWR_ON_SEQ_DLY(x)                                            (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_TOP_ISO_ON_DLY(x)                                                (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_AON_SYS_PWR_CFG
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_AON_WAKEUP_POR                                                      BIT(26)
#define BIT_PMU_APB_PD_AON_SYS_FORCE_SHUTDOWN                                           BIT(25)
#define BIT_PMU_APB_PD_AON_SYS_AUTO_SHUTDOWN_EN                                         BIT(24)
#define BIT_PMU_APB_PD_AON_SYS_PWR_ON_DLY(x)                                            (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_AON_SYS_PWR_ON_SEQ_DLY(x)                                        (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_AON_SYS_ISO_ON_DLY(x)                                            (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_PUBCP_SYS_PWR_CFG
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_PUBCP_SYS_DBG_SHUTDOWN_EN                                        BIT(28)
#define BIT_PMU_APB_PD_PUBCP_SYS_FORCE_SHUTDOWN                                         BIT(25)
#define BIT_PMU_APB_PD_PUBCP_SYS_AUTO_SHUTDOWN_EN                                       BIT(24)
#define BIT_PMU_APB_PD_PUBCP_SYS_PWR_ON_DLY(x)                                          (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_PUBCP_SYS_PWR_ON_SEQ_DLY(x)                                      (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_PUBCP_SYS_ISO_ON_DLY(x)                                          (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_AGCP_SYS_PWR_CFG
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_AGCP_SYS_DBG_SHUTDOWN_EN                                         BIT(28)
#define BIT_PMU_APB_PD_AGCP_SYS_FORCE_SHUTDOWN                                          BIT(25)
#define BIT_PMU_APB_PD_AGCP_SYS_AUTO_SHUTDOWN_EN                                        BIT(24)
#define BIT_PMU_APB_PD_AGCP_SYS_PWR_ON_DLY(x)                                           (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_AGCP_SYS_PWR_ON_SEQ_DLY(x)                                       (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_AGCP_SYS_ISO_ON_DLY(x)                                           (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LTE_P4_PWR_CFG
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P4_DBG_SHUTDOWN_EN                                     BIT(28)
#define BIT_PMU_APB_PD_WTLCP_LTE_P4_FORCE_SHUTDOWN                                      BIT(25)
#define BIT_PMU_APB_PD_WTLCP_LTE_P4_AUTO_SHUTDOWN_EN                                    BIT(24)
#define BIT_PMU_APB_PD_WTLCP_LTE_P4_PWR_ON_DLY(x)                                       (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_LTE_P4_PWR_ON_SEQ_DLY(x)                                   (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_LTE_P4_ISO_ON_DLY(x)                                       (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_TGDSP_PWR_CFG
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_TGDSP_DBG_SHUTDOWN_EN                                      BIT(28)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_PD_SEL                                               BIT(27)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_FORCE_SHUTDOWN                                       BIT(25)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_AUTO_SHUTDOWN_EN                                     BIT(24)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_PWR_ON_DLY(x)                                        (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_PWR_ON_SEQ_DLY(x)                                    (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_ISO_ON_DLY(x)                                        (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_HU3GE_B_PWR_CFG
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_DBG_SHUTDOWN_EN                                    BIT(28)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_FORCE_SHUTDOWN                                     BIT(25)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_AUTO_SHUTDOWN_EN                                   BIT(24)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_PWR_ON_DLY(x)                                      (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_PWR_ON_SEQ_DLY(x)                                  (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_ISO_ON_DLY(x)                                      (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_AP_SYS_PWR_CFG
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_AP_SYS_DBG_SHUTDOWN_EN                                           BIT(28)
#define BIT_PMU_APB_PD_AP_SYS_FORCE_SHUTDOWN                                            BIT(25)
#define BIT_PMU_APB_PD_AP_SYS_AUTO_SHUTDOWN_EN                                          BIT(24)
#define BIT_PMU_APB_PD_AP_SYS_PWR_ON_DLY(x)                                             (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_AP_SYS_PWR_ON_SEQ_DLY(x)                                         (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_AP_SYS_ISO_ON_DLY(x)                                             (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_GPU_PHANTOM_PWR_CFG1
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_GPU_PHANTOM_PWRUP_ABORT_FLAG                                     BIT(30)
#define BIT_PMU_APB_PD_GPU_PHANTOM_PWRDWN_ABORT_FLAG                                    BIT(29)
#define BIT_PMU_APB_PD_GPU_PHANTOM_DBG_SHUTDOWN_EN                                      BIT(28)
#define BIT_PMU_APB_PD_GPU_PHANTOM_FORCE_SHUTDOWN                                       BIT(25)
#define BIT_PMU_APB_PD_GPU_PHANTOM_AUTO_SHUTDOWN_EN                                     BIT(24)
#define BIT_PMU_APB_PD_GPU_PHANTOM_PWR_ON_DLY(x)                                        (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_GPU_PHANTOM_PWR_ON_SEQ_DLY(x)                                    (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_GPU_PHANTOM_ISO_ON_DLY(x)                                        (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_GPU_PHANTOM_PWR_CFG0
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_GPU_PHANTOM_SHUTDOWN_DLY(x)                                      (((x) & 0xFF) << 24)
#define BIT_PMU_APB_PD_GPU_PHANTOM_RST_ASSERT_DLY(x)                                    (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_GPU_PHANTOM_RST_DEASSERT_DLY(x)                                  (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_GPU_PHANTOM_ISO_OFF_DLY(x)                                       (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_AGCP_DSP_PWR_CFG
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_AGCP_DSP_DBG_SHUTDOWN_EN                                         BIT(28)
#define BIT_PMU_APB_PD_AGCP_DSP_PD_SEL                                                  BIT(27)
#define BIT_PMU_APB_PD_AGCP_DSP_FORCE_SHUTDOWN                                          BIT(25)
#define BIT_PMU_APB_PD_AGCP_DSP_AUTO_SHUTDOWN_EN                                        BIT(24)
#define BIT_PMU_APB_PD_AGCP_DSP_PWR_ON_DLY(x)                                           (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_AGCP_DSP_PWR_ON_SEQ_DLY(x)                                       (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_AGCP_DSP_ISO_ON_DLY(x)                                           (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_PUB0_SYS_PWR_CFG
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_PUB0_SYS_FORCE_SHUTDOWN                                          BIT(25)
#define BIT_PMU_APB_PD_PUB0_SYS_AUTO_SHUTDOWN_EN                                        BIT(24)
#define BIT_PMU_APB_PD_PUB0_SYS_PWR_ON_DLY(x)                                           (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_PUB0_SYS_PWR_ON_SEQ_DLY(x)                                       (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_PUB0_SYS_ISO_ON_DLY(x)                                           (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LTE_P1_PWR_CFG
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P1_DBG_SHUTDOWN_EN                                     BIT(28)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_FORCE_SHUTDOWN                                      BIT(25)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_AUTO_SHUTDOWN_EN                                    BIT(24)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_PWR_ON_DLY(x)                                       (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_PWR_ON_SEQ_DLY(x)                                   (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_ISO_ON_DLY(x)                                       (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_VSP_SYS_PWR_CFG
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_VSP_SYS_DBG_SHUTDOWN_EN                                          BIT(28)
#define BIT_PMU_APB_PD_VSP_SYS_FORCE_SHUTDOWN                                           BIT(25)
#define BIT_PMU_APB_PD_VSP_SYS_AUTO_SHUTDOWN_EN                                         BIT(24)
#define BIT_PMU_APB_PD_VSP_SYS_PWR_ON_DLY(x)                                            (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_VSP_SYS_PWR_ON_SEQ_DLY(x)                                        (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_VSP_SYS_ISO_ON_DLY(x)                                            (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LDSP_PWR_CFG
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LDSP_DBG_SHUTDOWN_EN                                       BIT(28)
#define BIT_PMU_APB_PD_WTLCP_LDSP_PD_SEL                                                BIT(27)
#define BIT_PMU_APB_PD_WTLCP_LDSP_FORCE_SHUTDOWN                                        BIT(25)
#define BIT_PMU_APB_PD_WTLCP_LDSP_AUTO_SHUTDOWN_EN                                      BIT(24)
#define BIT_PMU_APB_PD_WTLCP_LDSP_PWR_ON_DLY(x)                                         (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_LDSP_PWR_ON_SEQ_DLY(x)                                     (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_LDSP_ISO_ON_DLY(x)                                         (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_GPU_TOP_PWR_CFG1
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_GPU_TOP_DBG_SHUTDOWN_EN                                          BIT(28)
#define BIT_PMU_APB_PD_GPU_TOP_FORCE_SHUTDOWN                                           BIT(25)
#define BIT_PMU_APB_PD_GPU_TOP_AUTO_SHUTDOWN_EN                                         BIT(24)
#define BIT_PMU_APB_PD_GPU_TOP_PWR_ON_DLY(x)                                            (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_GPU_TOP_PWR_ON_SEQ_DLY(x)                                        (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_GPU_TOP_ISO_ON_DLY(x)                                            (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_GPU_TOP_PWR_CFG0
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_GPU_TOP_SHUTDOWN_DLY(x)                                          (((x) & 0xFF) << 24)
#define BIT_PMU_APB_PD_GPU_TOP_RST_ASSERT_DLY(x)                                        (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_GPU_TOP_RST_DEASSERT_DLY(x)                                      (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_GPU_TOP_ISO_OFF_DLY(x)                                           (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_PUB1_SYS_PWR_CFG
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_PUB1_SYS_FORCE_SHUTDOWN                                          BIT(25)
#define BIT_PMU_APB_PD_PUB1_SYS_AUTO_SHUTDOWN_EN                                        BIT(24)
#define BIT_PMU_APB_PD_PUB1_SYS_PWR_ON_DLY(x)                                           (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_PUB1_SYS_PWR_ON_SEQ_DLY(x)                                       (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_PUB1_SYS_ISO_ON_DLY(x)                                           (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_TD_PWR_CFG
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_TD_DBG_SHUTDOWN_EN                                         BIT(28)
#define BIT_PMU_APB_PD_WTLCP_TD_FORCE_SHUTDOWN                                          BIT(25)
#define BIT_PMU_APB_PD_WTLCP_TD_AUTO_SHUTDOWN_EN                                        BIT(24)
#define BIT_PMU_APB_PD_WTLCP_TD_PWR_ON_DLY(x)                                           (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_TD_PWR_ON_SEQ_DLY(x)                                       (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_TD_ISO_ON_DLY(x)                                           (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_BIA_PWR_CFG0
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_BIA_EFUSE_SENSE_BYPASS                                           BIT(30)
#define BIT_PMU_APB_PD_BIA_S0IX_SLP_ENA                                                 BIT(29)
#define BIT_PMU_APB_PD_BIA_DBG_SHUTDOWN_EN                                              BIT(28)
#define BIT_PMU_APB_PD_BIA_FORCE_SHUTDOWN                                               BIT(25)
#define BIT_PMU_APB_PD_BIA_AUTO_SHUTDOWN_EN                                             BIT(24)
#define BIT_PMU_APB_PD_BIA_CORE_ON_DLY(x)                                               (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_BIA_PWR_ON_SEQ_DLY(x)                                            (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_BIA_ISO_ON_DLY(x)                                                (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_BIA_PWR_CFG1
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_BIA_CGM_ON_DLY(x)                                                (((x) & 0xFF) << 24)
#define BIT_PMU_APB_PD_BIA_CGM_OFF_DLY(x)                                               (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_BIA_CORE_OFF_DLY(x)                                              (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_BIA_ISO_OFF_DLY(x)                                               (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_BIA_PWR_CFG2
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_BIA_CPU_ON_DLY(x)                                                (((x) & 0xFF) << 24)
#define BIT_PMU_APB_PD_BIA_EFUSE_SENSE_DLY(x)                                           (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_BIA_CPU_POWER_DLY(x)                                             (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_BIA_TAP_POWER_DLY(x)                                             (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_BIA_PWR_CFG3
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_BIA_L2_ON_DLY(x)                                                 (((x) & 0xFF) << 24)
#define BIT_PMU_APB_PD_BIA_L2_OFF_DLY(x)                                                (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_BIA_PLL_ON_DLY(x)                                                (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_BIA_PLL_OFF_DLY(x)                                               (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_BIA_PWR_CFG4
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_BIA_CPU_OFF_DLY(x)                                               (((x) & 0xFF) << 24)
#define BIT_PMU_APB_PD_BIA_S0IX_CGM_ON_DLY(x)                                           (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_BIA_S0IX_CGM_OFF_DLY(x)                                          (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_BIA_S0IX_WKUP_ASSERTON_DLY(x)                                    (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_BIA_PWR_CFG5
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_BIA_S0IX_DVFS_PWU_DLY(x)                                         (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_BIA_S0IX_WKUP_DEASSERTOFF_DLY(x)                                 (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_BIA_S0IX_WKUP_DEASSERTON_DLY(x)                                  (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_BIA_PWR_CFG6
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_BIA_CLK_UNLOCK_DLY(x)                                            (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_BIA_CLK_LOCK_DLY(x)                                              (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_BIA_PWR_ON_HALT_DEBUG_MASK                                       BIT(2)
#define BIT_PMU_APB_PD_BIA_S3_HALT_DEBUG_EN                                             BIT(1)
#define BIT_PMU_APB_PD_BIA_HALT_DEBUG_EXIT                                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LTE_P3_PWR_CFG
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P3_DBG_SHUTDOWN_EN                                     BIT(28)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_FORCE_SHUTDOWN                                      BIT(25)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_AUTO_SHUTDOWN_EN                                    BIT(24)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_PWR_ON_DLY(x)                                       (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_PWR_ON_SEQ_DLY(x)                                   (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_ISO_ON_DLY(x)                                       (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_SYS_PWR_CFG
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_SYS_DBG_SHUTDOWN_EN                                        BIT(28)
#define BIT_PMU_APB_PD_WTLCP_SYS_FORCE_SHUTDOWN                                         BIT(25)
#define BIT_PMU_APB_PD_WTLCP_SYS_AUTO_SHUTDOWN_EN                                       BIT(24)
#define BIT_PMU_APB_PD_WTLCP_SYS_PWR_ON_DLY(x)                                          (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_SYS_PWR_ON_SEQ_DLY(x)                                      (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_SYS_ISO_ON_DLY(x)                                          (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_ISP_TOP_PWR_CFG
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_ISP_TOP_DBG_SHUTDOWN_EN                                          BIT(28)
#define BIT_PMU_APB_PD_ISP_TOP_FORCE_SHUTDOWN                                           BIT(25)
#define BIT_PMU_APB_PD_ISP_TOP_AUTO_SHUTDOWN_EN                                         BIT(24)
#define BIT_PMU_APB_PD_ISP_TOP_PWR_ON_DLY(x)                                            (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_ISP_TOP_PWR_ON_SEQ_DLY(x)                                        (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_ISP_TOP_ISO_ON_DLY(x)                                            (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LTE_P2_PWR_CFG
// Register Offset : 0x008C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P2_DBG_SHUTDOWN_EN                                     BIT(28)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_FORCE_SHUTDOWN                                      BIT(25)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_AUTO_SHUTDOWN_EN                                    BIT(24)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_PWR_ON_DLY(x)                                       (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_PWR_ON_SEQ_DLY(x)                                   (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_ISO_ON_DLY(x)                                       (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_VSP_CORE_PWR_CFG
// Register Offset : 0x0090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_VSP_CORE_DBG_SHUTDOWN_EN                                         BIT(28)
#define BIT_PMU_APB_PD_VSP_CORE_FORCE_SHUTDOWN                                          BIT(25)
#define BIT_PMU_APB_PD_VSP_CORE_AUTO_SHUTDOWN_EN                                        BIT(24)
#define BIT_PMU_APB_PD_VSP_CORE_PWR_ON_DLY(x)                                           (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_TOP_BISR_PWR_ON_SEQ_DLY(x)                                       (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_VSP_CORE_ISO_ON_DLY(x)                                           (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_CAM_SYS_PWR_CFG
// Register Offset : 0x0094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_CAM_SYS_DBG_SHUTDOWN_EN                                          BIT(28)
#define BIT_PMU_APB_PD_CAM_SYS_FORCE_SHUTDOWN                                           BIT(25)
#define BIT_PMU_APB_PD_CAM_SYS_AUTO_SHUTDOWN_EN                                         BIT(24)
#define BIT_PMU_APB_PD_CAM_SYS_PWR_ON_DLY(x)                                            (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_CAM_SYS_PWR_ON_SEQ_DLY(x)                                        (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_CAM_SYS_ISO_ON_DLY(x)                                            (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_HU3GE_A_PWR_CFG
// Register Offset : 0x0098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_DBG_SHUTDOWN_EN                                    BIT(28)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_FORCE_SHUTDOWN                                     BIT(25)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_AUTO_SHUTDOWN_EN                                   BIT(24)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_PWR_ON_DLY(x)                                      (((x) & 0xFF) << 16)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_PWR_ON_SEQ_DLY(x)                                  (((x) & 0xFF) << 8)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_ISO_ON_DLY(x)                                      (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_XTL_WAIT_CNT0
// Register Offset : 0x00AC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_XTL0_WAIT_CNT(x)                                                    (((x) & 0xFF) << 8)
#define BIT_PMU_APB_RC_WAIT_CNT(x)                                                      (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_XTLBUF_WAIT_CNT0
// Register Offset : 0x00BC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_XTLBUF0_WAIT_CNT(x)                                                 (((x) & 0xFF) << 16)
#define BIT_PMU_APB_XTLBUF1_WAIT_CNT(x)                                                 (((x) & 0xFF) << 8)
#define BIT_PMU_APB_XTLBUF2_WAIT_CNT(x)                                                 (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PLL_WAIT_CNT1
// Register Offset : 0x00C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_MPLL0_WAIT_CNT(x)                                                   (((x) & 0xFF) << 24)
#define BIT_PMU_APB_DPLL0_WAIT_CNT(x)                                                   (((x) & 0xFF) << 16)
#define BIT_PMU_APB_DPLL1_WAIT_CNT(x)                                                   (((x) & 0xFF) << 8)
#define BIT_PMU_APB_GPLL_WAIT_CNT(x)                                                    (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PLL_WAIT_CNT2
// Register Offset : 0x00C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_MPLL2_WAIT_CNT(x)                                                   (((x) & 0xFF) << 24)
#define BIT_PMU_APB_MPLL1_WAIT_CNT(x)                                                   (((x) & 0xFF) << 16)
#define BIT_PMU_APB_DSPLL_WAIT_CNT(x)                                                   (((x) & 0xFF) << 8)
#define BIT_PMU_APB_RPLL1_WAIT_CNT(x)                                                   (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PLL_WAIT_CNT3
// Register Offset : 0x00C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_RPLL0_WAIT_CNT(x)                                                   (((x) & 0xFF) << 24)
#define BIT_PMU_APB_LPLL0_WAIT_CNT(x)                                                   (((x) & 0xFF) << 16)
#define BIT_PMU_APB_ISPPLL_WAIT_CNT(x)                                                  (((x) & 0xFF) << 8)
#define BIT_PMU_APB_TWPLL_WAIT_CNT(x)                                                   (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_GPLL_REL_CFG
// Register Offset : 0x00CC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_GPLL_FRC_ON                                                         BIT(15)
#define BIT_PMU_APB_GPLL_FRC_OFF                                                        BIT(14)
#define BIT_PMU_APB_GPLL_RELOCK_EN                                                      BIT(13)
#define BIT_PMU_APB_GPLL_AP_SYS_SEL                                                     BIT(8)
#define BIT_PMU_APB_GPLL_WTLCP_SYS_SEL                                                  BIT(7)
#define BIT_PMU_APB_GPLL_PUBCP_SYS_SEL                                                  BIT(6)
#define BIT_PMU_APB_GPLL_AUD_SYS_SEL                                                    BIT(5)
#define BIT_PMU_APB_GPLL_CM4_SYS_SEL                                                    BIT(4)
#define BIT_PMU_APB_GPLL_PUB0_SYS_SEL                                                   BIT(3)
#define BIT_PMU_APB_GPLL_PUB1_SYS_SEL                                                   BIT(2)
#define BIT_PMU_APB_GPLL_CAM_PD_SEL                                                     BIT(1)
#define BIT_PMU_APB_GPLL_EXT_PD_SEL                                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_DPLL1_REL_CFG
// Register Offset : 0x00D0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_DPLL1_FRC_ON                                                        BIT(15)
#define BIT_PMU_APB_DPLL1_FRC_OFF                                                       BIT(14)
#define BIT_PMU_APB_DPLL1_RELOCK_EN                                                     BIT(13)
#define BIT_PMU_APB_DPLL1_AP_SYS_SEL                                                    BIT(8)
#define BIT_PMU_APB_DPLL1_WTLCP_SYS_SEL                                                 BIT(7)
#define BIT_PMU_APB_DPLL1_PUBCP_SYS_SEL                                                 BIT(6)
#define BIT_PMU_APB_DPLL1_AUD_SYS_SEL                                                   BIT(5)
#define BIT_PMU_APB_DPLL1_CM4_SYS_SEL                                                   BIT(4)
#define BIT_PMU_APB_DPLL1_PUB0_SYS_SEL                                                  BIT(3)
#define BIT_PMU_APB_DPLL1_PUB1_SYS_SEL                                                  BIT(2)
#define BIT_PMU_APB_DPLL1_CAM_PD_SEL                                                    BIT(1)
#define BIT_PMU_APB_DPLL1_EXT_PD_SEL                                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_XTLBUF2_REL_CFG
// Register Offset : 0x00D4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_XTLBUF2_FRC_ON                                                      BIT(15)
#define BIT_PMU_APB_XTLBUF2_FRC_OFF                                                     BIT(14)
#define BIT_PMU_APB_XTLBUF2_RELOCK_EN                                                   BIT(13)
#define BIT_PMU_APB_XTLBUF2_AP_SYS_SEL                                                  BIT(8)
#define BIT_PMU_APB_XTLBUF2_WTLCP_SYS_SEL                                               BIT(7)
#define BIT_PMU_APB_XTLBUF2_PUBCP_SYS_SEL                                               BIT(6)
#define BIT_PMU_APB_XTLBUF2_AUD_SYS_SEL                                                 BIT(5)
#define BIT_PMU_APB_XTLBUF2_CM4_SYS_SEL                                                 BIT(4)
#define BIT_PMU_APB_XTLBUF2_PUB0_SYS_SEL                                                BIT(3)
#define BIT_PMU_APB_XTLBUF2_PUB1_SYS_SEL                                                BIT(2)
#define BIT_PMU_APB_XTLBUF2_CAM_PD_SEL                                                  BIT(1)
#define BIT_PMU_APB_XTLBUF2_EXT_PD_SEL                                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_DPLL0_REL_CFG
// Register Offset : 0x00D8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_DPLL0_FRC_ON                                                        BIT(15)
#define BIT_PMU_APB_DPLL0_FRC_OFF                                                       BIT(14)
#define BIT_PMU_APB_DPLL0_RELOCK_EN                                                     BIT(13)
#define BIT_PMU_APB_DPLL0_AP_SYS_SEL                                                    BIT(8)
#define BIT_PMU_APB_DPLL0_WTLCP_SYS_SEL                                                 BIT(7)
#define BIT_PMU_APB_DPLL0_PUBCP_SYS_SEL                                                 BIT(6)
#define BIT_PMU_APB_DPLL0_AUD_SYS_SEL                                                   BIT(5)
#define BIT_PMU_APB_DPLL0_CM4_SYS_SEL                                                   BIT(4)
#define BIT_PMU_APB_DPLL0_PUB0_SYS_SEL                                                  BIT(3)
#define BIT_PMU_APB_DPLL0_PUB1_SYS_SEL                                                  BIT(2)
#define BIT_PMU_APB_DPLL0_CAM_PD_SEL                                                    BIT(1)
#define BIT_PMU_APB_DPLL0_EXT_PD_SEL                                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_MPLL0_REL_CFG
// Register Offset : 0x00DC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_MPLL0_FRC_ON                                                        BIT(15)
#define BIT_PMU_APB_MPLL0_FRC_OFF                                                       BIT(14)
#define BIT_PMU_APB_MPLL0_RELOCK_EN                                                     BIT(13)
#define BIT_PMU_APB_MPLL0_AP_SYS_SEL                                                    BIT(8)
#define BIT_PMU_APB_MPLL0_WTLCP_SYS_SEL                                                 BIT(7)
#define BIT_PMU_APB_MPLL0_PUBCP_SYS_SEL                                                 BIT(6)
#define BIT_PMU_APB_MPLL0_AUD_SYS_SEL                                                   BIT(5)
#define BIT_PMU_APB_MPLL0_CM4_SYS_SEL                                                   BIT(4)
#define BIT_PMU_APB_MPLL0_PUB0_SYS_SEL                                                  BIT(3)
#define BIT_PMU_APB_MPLL0_PUB1_SYS_SEL                                                  BIT(2)
#define BIT_PMU_APB_MPLL0_CAM_PD_SEL                                                    BIT(1)
#define BIT_PMU_APB_MPLL0_EXT_PD_SEL                                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_XTLBUF1_REL_CFG
// Register Offset : 0x00E0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_XTLBUF1_FRC_ON                                                      BIT(15)
#define BIT_PMU_APB_XTLBUF1_FRC_OFF                                                     BIT(14)
#define BIT_PMU_APB_XTLBUF1_RELOCK_EN                                                   BIT(13)
#define BIT_PMU_APB_XTLBUF1_AP_SYS_SEL                                                  BIT(8)
#define BIT_PMU_APB_XTLBUF1_WTLCP_SYS_SEL                                               BIT(7)
#define BIT_PMU_APB_XTLBUF1_PUBCP_SYS_SEL                                               BIT(6)
#define BIT_PMU_APB_XTLBUF1_AUD_SYS_SEL                                                 BIT(5)
#define BIT_PMU_APB_XTLBUF1_CM4_SYS_SEL                                                 BIT(4)
#define BIT_PMU_APB_XTLBUF1_PUB0_SYS_SEL                                                BIT(3)
#define BIT_PMU_APB_XTLBUF1_PUB1_SYS_SEL                                                BIT(2)
#define BIT_PMU_APB_XTLBUF1_CAM_PD_SEL                                                  BIT(1)
#define BIT_PMU_APB_XTLBUF1_EXT_PD_SEL                                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_RPLL1_REL_CFG
// Register Offset : 0x00E4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_RPLL1_FRC_ON                                                        BIT(15)
#define BIT_PMU_APB_RPLL1_FRC_OFF                                                       BIT(14)
#define BIT_PMU_APB_RPLL1_RELOCK_EN                                                     BIT(13)
#define BIT_PMU_APB_RPLL1_AP_SYS_SEL                                                    BIT(8)
#define BIT_PMU_APB_RPLL1_WTLCP_SYS_SEL                                                 BIT(7)
#define BIT_PMU_APB_RPLL1_PUBCP_SYS_SEL                                                 BIT(6)
#define BIT_PMU_APB_RPLL1_AUD_SYS_SEL                                                   BIT(5)
#define BIT_PMU_APB_RPLL1_CM4_SYS_SEL                                                   BIT(4)
#define BIT_PMU_APB_RPLL1_PUB0_SYS_SEL                                                  BIT(3)
#define BIT_PMU_APB_RPLL1_PUB1_SYS_SEL                                                  BIT(2)
#define BIT_PMU_APB_RPLL1_CAM_PD_SEL                                                    BIT(1)
#define BIT_PMU_APB_RPLL1_EXT_PD_SEL                                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_DSPLL_REL_CFG
// Register Offset : 0x00E8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_DSPLL_FRC_ON                                                        BIT(15)
#define BIT_PMU_APB_DSPLL_FRC_OFF                                                       BIT(14)
#define BIT_PMU_APB_DSPLL_RELOCK_EN                                                     BIT(13)
#define BIT_PMU_APB_DSPLL_REF_SEL(x)                                                    (((x) & 0x7) << 10)
#define BIT_PMU_APB_DSPLL_AP_SYS_SEL                                                    BIT(8)
#define BIT_PMU_APB_DSPLL_WTLCP_SYS_SEL                                                 BIT(7)
#define BIT_PMU_APB_DSPLL_PUBCP_SYS_SEL                                                 BIT(6)
#define BIT_PMU_APB_DSPLL_AUD_SYS_SEL                                                   BIT(5)
#define BIT_PMU_APB_DSPLL_CM4_SYS_SEL                                                   BIT(4)
#define BIT_PMU_APB_DSPLL_PUB0_SYS_SEL                                                  BIT(3)
#define BIT_PMU_APB_DSPLL_PUB1_SYS_SEL                                                  BIT(2)
#define BIT_PMU_APB_DSPLL_CAM_PD_SEL                                                    BIT(1)
#define BIT_PMU_APB_DSPLL_EXT_PD_SEL                                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_XTLBUF0_REL_CFG
// Register Offset : 0x00EC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_XTLBUF0_FRC_ON                                                      BIT(15)
#define BIT_PMU_APB_XTLBUF0_FRC_OFF                                                     BIT(14)
#define BIT_PMU_APB_XTLBUF0_RELOCK_EN                                                   BIT(13)
#define BIT_PMU_APB_XTLBUF0_AP_SYS_SEL                                                  BIT(8)
#define BIT_PMU_APB_XTLBUF0_WTLCP_SYS_SEL                                               BIT(7)
#define BIT_PMU_APB_XTLBUF0_PUBCP_SYS_SEL                                               BIT(6)
#define BIT_PMU_APB_XTLBUF0_AUD_SYS_SEL                                                 BIT(5)
#define BIT_PMU_APB_XTLBUF0_CM4_SYS_SEL                                                 BIT(4)
#define BIT_PMU_APB_XTLBUF0_PUB0_SYS_SEL                                                BIT(3)
#define BIT_PMU_APB_XTLBUF0_PUB1_SYS_SEL                                                BIT(2)
#define BIT_PMU_APB_XTLBUF0_CAM_PD_SEL                                                  BIT(1)
#define BIT_PMU_APB_XTLBUF0_EXT_PD_SEL                                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_MPLL1_REL_CFG
// Register Offset : 0x00F0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_MPLL1_FRC_ON                                                        BIT(15)
#define BIT_PMU_APB_MPLL1_FRC_OFF                                                       BIT(14)
#define BIT_PMU_APB_MPLL1_RELOCK_EN                                                     BIT(13)
#define BIT_PMU_APB_MPLL1_AP_SYS_SEL                                                    BIT(8)
#define BIT_PMU_APB_MPLL1_WTLCP_SYS_SEL                                                 BIT(7)
#define BIT_PMU_APB_MPLL1_PUBCP_SYS_SEL                                                 BIT(6)
#define BIT_PMU_APB_MPLL1_AUD_SYS_SEL                                                   BIT(5)
#define BIT_PMU_APB_MPLL1_CM4_SYS_SEL                                                   BIT(4)
#define BIT_PMU_APB_MPLL1_PUB0_SYS_SEL                                                  BIT(3)
#define BIT_PMU_APB_MPLL1_PUB1_SYS_SEL                                                  BIT(2)
#define BIT_PMU_APB_MPLL1_CAM_PD_SEL                                                    BIT(1)
#define BIT_PMU_APB_MPLL1_EXT_PD_SEL                                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_MPLL2_REL_CFG
// Register Offset : 0x00F4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_MPLL2_FRC_ON                                                        BIT(15)
#define BIT_PMU_APB_MPLL2_FRC_OFF                                                       BIT(14)
#define BIT_PMU_APB_MPLL2_RELOCK_EN                                                     BIT(13)
#define BIT_PMU_APB_MPLL2_AP_SYS_SEL                                                    BIT(8)
#define BIT_PMU_APB_MPLL2_WTLCP_SYS_SEL                                                 BIT(7)
#define BIT_PMU_APB_MPLL2_PUBCP_SYS_SEL                                                 BIT(6)
#define BIT_PMU_APB_MPLL2_AUD_SYS_SEL                                                   BIT(5)
#define BIT_PMU_APB_MPLL2_CM4_SYS_SEL                                                   BIT(4)
#define BIT_PMU_APB_MPLL2_PUB0_SYS_SEL                                                  BIT(3)
#define BIT_PMU_APB_MPLL2_PUB1_SYS_SEL                                                  BIT(2)
#define BIT_PMU_APB_MPLL2_CAM_PD_SEL                                                    BIT(1)
#define BIT_PMU_APB_MPLL2_EXT_PD_SEL                                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_TWPLL_REL_CFG
// Register Offset : 0x00F8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_TWPLL_FRC_ON                                                        BIT(15)
#define BIT_PMU_APB_TWPLL_FRC_OFF                                                       BIT(14)
#define BIT_PMU_APB_TWPLL_RELOCK_EN                                                     BIT(13)
#define BIT_PMU_APB_TWPLL_REF_SEL(x)                                                    (((x) & 0x7) << 10)
#define BIT_PMU_APB_TWPLL_AP_SYS_SEL                                                    BIT(8)
#define BIT_PMU_APB_TWPLL_WTLCP_SYS_SEL                                                 BIT(7)
#define BIT_PMU_APB_TWPLL_PUBCP_SYS_SEL                                                 BIT(6)
#define BIT_PMU_APB_TWPLL_AUD_SYS_SEL                                                   BIT(5)
#define BIT_PMU_APB_TWPLL_CM4_SYS_SEL                                                   BIT(4)
#define BIT_PMU_APB_TWPLL_PUB0_SYS_SEL                                                  BIT(3)
#define BIT_PMU_APB_TWPLL_PUB1_SYS_SEL                                                  BIT(2)
#define BIT_PMU_APB_TWPLL_CAM_PD_SEL                                                    BIT(1)
#define BIT_PMU_APB_TWPLL_EXT_PD_SEL                                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_ISPPLL_REL_CFG
// Register Offset : 0x00FC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_ISPPLL_FRC_ON                                                       BIT(15)
#define BIT_PMU_APB_ISPPLL_FRC_OFF                                                      BIT(14)
#define BIT_PMU_APB_ISPPLL_RELOCK_EN                                                    BIT(13)
#define BIT_PMU_APB_ISPPLL_AP_SYS_SEL                                                   BIT(8)
#define BIT_PMU_APB_ISPPLL_WTLCP_SYS_SEL                                                BIT(7)
#define BIT_PMU_APB_ISPPLL_PUBCP_SYS_SEL                                                BIT(6)
#define BIT_PMU_APB_ISPPLL_AUD_SYS_SEL                                                  BIT(5)
#define BIT_PMU_APB_ISPPLL_CM4_SYS_SEL                                                  BIT(4)
#define BIT_PMU_APB_ISPPLL_PUB0_SYS_SEL                                                 BIT(3)
#define BIT_PMU_APB_ISPPLL_PUB1_SYS_SEL                                                 BIT(2)
#define BIT_PMU_APB_ISPPLL_CAM_PD_SEL                                                   BIT(1)
#define BIT_PMU_APB_ISPPLL_EXT_PD_SEL                                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_RC_REL_CFG
// Register Offset : 0x0100
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_RC_FRC_ON                                                           BIT(15)
#define BIT_PMU_APB_RC_FRC_OFF                                                          BIT(14)
#define BIT_PMU_APB_RC_RELOCK_EN                                                        BIT(13)
#define BIT_PMU_APB_RC_AP_SYS_SEL                                                       BIT(8)
#define BIT_PMU_APB_RC_WTLCP_SYS_SEL                                                    BIT(7)
#define BIT_PMU_APB_RC_PUBCP_SYS_SEL                                                    BIT(6)
#define BIT_PMU_APB_RC_AUD_SYS_SEL                                                      BIT(5)
#define BIT_PMU_APB_RC_CM4_SYS_SEL                                                      BIT(4)
#define BIT_PMU_APB_RC_PUB0_SYS_SEL                                                     BIT(3)
#define BIT_PMU_APB_RC_PUB1_SYS_SEL                                                     BIT(2)
#define BIT_PMU_APB_RC_CAM_PD_SEL                                                       BIT(1)
#define BIT_PMU_APB_RC_EXT_PD_SEL                                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_LPLL0_REL_CFG
// Register Offset : 0x0104
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_LPLL0_FRC_ON                                                        BIT(15)
#define BIT_PMU_APB_LPLL0_FRC_OFF                                                       BIT(14)
#define BIT_PMU_APB_LPLL0_RELOCK_EN                                                     BIT(13)
#define BIT_PMU_APB_LPLL0_REF_SEL(x)                                                    (((x) & 0x7) << 10)
#define BIT_PMU_APB_LPLL0_AP_SYS_SEL                                                    BIT(8)
#define BIT_PMU_APB_LPLL0_WTLCP_SYS_SEL                                                 BIT(7)
#define BIT_PMU_APB_LPLL0_PUBCP_SYS_SEL                                                 BIT(6)
#define BIT_PMU_APB_LPLL0_AUD_SYS_SEL                                                   BIT(5)
#define BIT_PMU_APB_LPLL0_CM4_SYS_SEL                                                   BIT(4)
#define BIT_PMU_APB_LPLL0_PUB0_SYS_SEL                                                  BIT(3)
#define BIT_PMU_APB_LPLL0_PUB1_SYS_SEL                                                  BIT(2)
#define BIT_PMU_APB_LPLL0_CAM_PD_SEL                                                    BIT(1)
#define BIT_PMU_APB_LPLL0_EXT_PD_SEL                                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_XTL0_REL_CFG
// Register Offset : 0x0108
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_XTL0_FRC_ON                                                         BIT(15)
#define BIT_PMU_APB_XTL0_FRC_OFF                                                        BIT(14)
#define BIT_PMU_APB_XTL0_RELOCK_EN                                                      BIT(13)
#define BIT_PMU_APB_XTL0_AP_SYS_SEL                                                     BIT(8)
#define BIT_PMU_APB_XTL0_WTLCP_SYS_SEL                                                  BIT(7)
#define BIT_PMU_APB_XTL0_PUBCP_SYS_SEL                                                  BIT(6)
#define BIT_PMU_APB_XTL0_AUD_SYS_SEL                                                    BIT(5)
#define BIT_PMU_APB_XTL0_CM4_SYS_SEL                                                    BIT(4)
#define BIT_PMU_APB_XTL0_PUB0_SYS_SEL                                                   BIT(3)
#define BIT_PMU_APB_XTL0_PUB1_SYS_SEL                                                   BIT(2)
#define BIT_PMU_APB_XTL0_CAM_PD_SEL                                                     BIT(1)
#define BIT_PMU_APB_XTL0_EXT_PD_SEL                                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_RPLL0_REL_CFG
// Register Offset : 0x010C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_RPLL0_FRC_ON                                                        BIT(15)
#define BIT_PMU_APB_RPLL0_FRC_OFF                                                       BIT(14)
#define BIT_PMU_APB_RPLL0_RELOCK_EN                                                     BIT(13)
#define BIT_PMU_APB_RPLL0_AP_SYS_SEL                                                    BIT(8)
#define BIT_PMU_APB_RPLL0_WTLCP_SYS_SEL                                                 BIT(7)
#define BIT_PMU_APB_RPLL0_PUBCP_SYS_SEL                                                 BIT(6)
#define BIT_PMU_APB_RPLL0_AUD_SYS_SEL                                                   BIT(5)
#define BIT_PMU_APB_RPLL0_CM4_SYS_SEL                                                   BIT(4)
#define BIT_PMU_APB_RPLL0_PUB0_SYS_SEL                                                  BIT(3)
#define BIT_PMU_APB_RPLL0_PUB1_SYS_SEL                                                  BIT(2)
#define BIT_PMU_APB_RPLL0_CAM_PD_SEL                                                    BIT(1)
#define BIT_PMU_APB_RPLL0_EXT_PD_SEL                                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PWR_STATE_DBG1
// Register Offset : 0x011C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_STATE(x)                                           (((x) & 0x1F) << 25)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_STATE(x)                                             (((x) & 0x1F) << 20)
#define BIT_PMU_APB_PD_WTLCP_LTE_P4_STATE(x)                                            (((x) & 0x1F) << 15)
#define BIT_PMU_APB_PD_AGCP_SYS_STATE(x)                                                (((x) & 0x1F) << 10)
#define BIT_PMU_APB_PD_PUBCP_SYS_STATE(x)                                               (((x) & 0x1F) << 5)
#define BIT_PMU_APB_PD_BIA_S0IX_STATE(x)                                                (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PWR_STATE_DBG2
// Register Offset : 0x0120
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_VSP_SYS_STATE(x)                                                 (((x) & 0x1F) << 25)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_STATE(x)                                            (((x) & 0x1F) << 20)
#define BIT_PMU_APB_PD_PUB0_SYS_STATE(x)                                                (((x) & 0x1F) << 15)
#define BIT_PMU_APB_PD_AGCP_DSP_STATE(x)                                                (((x) & 0x1F) << 10)
#define BIT_PMU_APB_PD_GPU_PHANTOM_STATE(x)                                             (((x) & 0x1F) << 5)
#define BIT_PMU_APB_PD_AP_SYS_STATE(x)                                                  (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PWR_STATE_DBG3
// Register Offset : 0x0124
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P3_STATE(x)                                            (((x) & 0x1F) << 25)
#define BIT_PMU_APB_PD_BIA_STATE(x)                                                     (((x) & 0x1F) << 20)
#define BIT_PMU_APB_PD_WTLCP_TD_STATE(x)                                                (((x) & 0x1F) << 15)
#define BIT_PMU_APB_PD_PUB1_SYS_STATE(x)                                                (((x) & 0x1F) << 10)
#define BIT_PMU_APB_PD_GPU_TOP_STATE(x)                                                 (((x) & 0x1F) << 5)
#define BIT_PMU_APB_PD_WTLCP_LDSP_STATE(x)                                              (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PWR_STATE_DBG4
// Register Offset : 0x0128
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_STATE(x)                                           (((x) & 0x1F) << 25)
#define BIT_PMU_APB_PD_CAM_SYS_STATE(x)                                                 (((x) & 0x1F) << 20)
#define BIT_PMU_APB_PD_VSP_CORE_STATE(x)                                                (((x) & 0x1F) << 15)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_STATE(x)                                            (((x) & 0x1F) << 10)
#define BIT_PMU_APB_PD_ISP_TOP_STATE(x)                                                 (((x) & 0x1F) << 5)
#define BIT_PMU_APB_PD_WTLCP_SYS_STATE(x)                                               (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PUB0_SYS_SLEEP_CTRL
// Register Offset : 0x012C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_DDR0_GLB_CGM_EN                                                     BIT(11)
#define BIT_PMU_APB_PUB0_SYS_DDR_PWR_DOWN                                               BIT(10)
#define BIT_PMU_APB_PUB0_SYS_SLEEP                                                      BIT(9)
#define BIT_PMU_APB_DDR0_AUTO_DEEP_SLEEP_ENABLE                                         BIT(8)
#define BIT_PMU_APB_DDR0_SLEEP_DISABLE_ACK                                              BIT(7)
#define BIT_PMU_APB_DDR0_SLEEP_DISABLE                                                  BIT(6)
#define BIT_PMU_APB_DDR0_SLEEP_DISABLE_ACK_BYP                                          BIT(5)
#define BIT_PMU_APB_DDR0_AUTO_SLEEP_ENABLE                                              BIT(4)
#define BIT_PMU_APB_PUB0_SYS_FORCE_LIGHT_SLEEP                                          BIT(3)
#define BIT_PMU_APB_PUB0_SYS_FORCE_DEEP_SLEEP                                           BIT(2)
#define BIT_PMU_APB_PUB0_SYS_DDR_GLB_CGM_EN_BYP                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PUB1_SYS_SLEEP_CTRL
// Register Offset : 0x0130
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_DDR1_GLB_CGM_EN                                                     BIT(11)
#define BIT_PMU_APB_PUB1_SYS_DDR_PWR_DOWN                                               BIT(10)
#define BIT_PMU_APB_PUB1_SYS_SLEEP                                                      BIT(9)
#define BIT_PMU_APB_DDR1_AUTO_DEEP_SLEEP_ENABLE                                         BIT(8)
#define BIT_PMU_APB_DDR1_SLEEP_DISABLE_ACK                                              BIT(7)
#define BIT_PMU_APB_DDR1_SLEEP_DISABLE                                                  BIT(6)
#define BIT_PMU_APB_DDR1_SLEEP_DISABLE_ACK_BYP                                          BIT(5)
#define BIT_PMU_APB_DDR1_AUTO_SLEEP_ENABLE                                              BIT(4)
#define BIT_PMU_APB_PUB1_SYS_FORCE_LIGHT_SLEEP                                          BIT(3)
#define BIT_PMU_APB_PUB1_SYS_FORCE_DEEP_SLEEP                                           BIT(2)
#define BIT_PMU_APB_PUB1_SYS_DDR_GLB_CGM_EN_BYP                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_AP_SYS_SLEEP_CTRL
// Register Offset : 0x0134
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_AP_SYS_DOZE_SLEEP                                                   BIT(27)
#define BIT_PMU_APB_AP_SYS_FORCE_DOZE_SLEEP                                             BIT(26)
#define BIT_PMU_APB_AP_SYS_DEEP_SLEEP                                                   BIT(25)
#define BIT_PMU_APB_AP_SYS_FORCE_DEEP_SLEEP                                             BIT(24)
#define BIT_PMU_APB_AP_SYS_LIGHT_SLEEP1                                                 BIT(17)
#define BIT_PMU_APB_AP_SYS_FORCE_LIGHT_SLEEP1                                           BIT(16)
#define BIT_PMU_APB_AP_SYS_LSLP1_WAKEUP_EN                                              BIT(15)
#define BIT_PMU_APB_AP_SYS_LIGHT_SLEEP0                                                 BIT(14)
#define BIT_PMU_APB_AP_SYS_FORCE_LIGHT_SLEEP0                                           BIT(13)
#define BIT_PMU_APB_AP_SYS_LSLP0_WAKEUP_EN                                              BIT(12)
#define BIT_PMU_APB_AP_SYS_PUB_DEEP_SLEEP1                                              BIT(5)
#define BIT_PMU_APB_AP_SYS_FORCE_PUB_DEEP_SLEEP1                                        BIT(4)
#define BIT_PMU_APB_AP_SYS_PUB_DSLP1_WAKEUP_EN                                          BIT(3)
#define BIT_PMU_APB_AP_SYS_PUB_DEEP_SLEEP0                                              BIT(2)
#define BIT_PMU_APB_AP_SYS_FORCE_PUB_DEEP_SLEEP0                                        BIT(1)
#define BIT_PMU_APB_AP_SYS_PUB_DSLP0_WAKEUP_EN                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CM4_SYS_SLEEP_CTRL
// Register Offset : 0x0138
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CM4_SYS_DOZE_SLEEP                                                  BIT(27)
#define BIT_PMU_APB_CM4_SYS_FORCE_DOZE_SLEEP                                            BIT(26)
#define BIT_PMU_APB_CM4_SYS_DEEP_SLEEP                                                  BIT(25)
#define BIT_PMU_APB_CM4_SYS_FORCE_DEEP_SLEEP                                            BIT(24)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_WTLCP_SYS_SLEEP_CTRL
// Register Offset : 0x0144
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_WTLCP_SYS_DOZE_SLEEP                                                BIT(27)
#define BIT_PMU_APB_WTLCP_SYS_FORCE_DOZE_SLEEP                                          BIT(26)
#define BIT_PMU_APB_WTLCP_SYS_DEEP_SLEEP                                                BIT(25)
#define BIT_PMU_APB_WTLCP_SYS_FORCE_DEEP_SLEEP                                          BIT(24)
#define BIT_PMU_APB_WTLCP_SYS_LIGHT_SLEEP0                                              BIT(14)
#define BIT_PMU_APB_WTLCP_SYS_FORCE_LIGHT_SLEEP0                                        BIT(13)
#define BIT_PMU_APB_WTLCP_SYS_LSLP0_WAKEUP_EN                                           BIT(12)
#define BIT_PMU_APB_WTLCP_SYS_PUB_DEEP_SLEEP0                                           BIT(2)
#define BIT_PMU_APB_WTLCP_SYS_FORCE_PUB_DEEP_SLEEP0                                     BIT(1)
#define BIT_PMU_APB_WTLCP_SYS_PUB_DSLP0_WAKEUP_EN                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_AGCP_SYS_SLEEP_CTRL
// Register Offset : 0x0148
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_AGCP_SYS_DOZE_SLEEP                                                 BIT(27)
#define BIT_PMU_APB_AGCP_SYS_FORCE_DOZE_SLEEP                                           BIT(26)
#define BIT_PMU_APB_AGCP_SYS_DEEP_SLEEP                                                 BIT(25)
#define BIT_PMU_APB_AGCP_SYS_FORCE_DEEP_SLEEP                                           BIT(24)
#define BIT_PMU_APB_AGCP_SYS_LIGHT_SLEEP0                                               BIT(14)
#define BIT_PMU_APB_AGCP_SYS_FORCE_LIGHT_SLEEP0                                         BIT(13)
#define BIT_PMU_APB_AGCP_SYS_LSLP0_WAKEUP_EN                                            BIT(12)
#define BIT_PMU_APB_AGCP_SYS_PUB_DEEP_SLEEP0                                            BIT(2)
#define BIT_PMU_APB_AGCP_SYS_FORCE_PUB_DEEP_SLEEP0                                      BIT(1)
#define BIT_PMU_APB_AGCP_SYS_PUB_DSLP0_WAKEUP_EN                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PUBCP_SYS_SLEEP_CTRL
// Register Offset : 0x014C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUBCP_SYS_DOZE_SLEEP                                                BIT(27)
#define BIT_PMU_APB_PUBCP_SYS_FORCE_DOZE_SLEEP                                          BIT(26)
#define BIT_PMU_APB_PUBCP_SYS_DEEP_SLEEP                                                BIT(25)
#define BIT_PMU_APB_PUBCP_SYS_FORCE_DEEP_SLEEP                                          BIT(24)
#define BIT_PMU_APB_PUBCP_SYS_LIGHT_SLEEP0                                              BIT(14)
#define BIT_PMU_APB_PUBCP_SYS_FORCE_LIGHT_SLEEP0                                        BIT(13)
#define BIT_PMU_APB_PUBCP_SYS_LSLP0_WAKEUP_EN                                           BIT(12)
#define BIT_PMU_APB_PUBCP_SYS_PUB_DEEP_SLEEP0                                           BIT(2)
#define BIT_PMU_APB_PUBCP_SYS_FORCE_PUB_DEEP_SLEEP0                                     BIT(1)
#define BIT_PMU_APB_PUBCP_SYS_PUB_DSLP0_WAKEUP_EN                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_SYS_SLP_STATUS0
// Register Offset : 0x015C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUBCP_SYS_SLP_STATUS(x)                                             (((x) & 0xF) << 24)
#define BIT_PMU_APB_AGCP_SYS_SLP_STATUS(x)                                              (((x) & 0xF) << 20)
#define BIT_PMU_APB_WTLCP_SYS_SLP_STATUS(x)                                             (((x) & 0xF) << 16)
#define BIT_PMU_APB_PUB1_SYS_SLP_STATUS(x)                                              (((x) & 0xF) << 12)
#define BIT_PMU_APB_PUB0_SYS_SLP_STATUS(x)                                              (((x) & 0xF) << 8)
#define BIT_PMU_APB_CM4_SYS_SLP_STATUS(x)                                               (((x) & 0xF) << 4)
#define BIT_PMU_APB_AP_SYS_SLP_STATUS(x)                                                (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_BISR_DONE_STATUS0
// Register Offset : 0x0160
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_GPU_C1_BISR_DONE                                                 BIT(25)
#define BIT_PMU_APB_PD_GPU_C0_BISR_DONE                                                 BIT(24)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_BISR_DONE                                          BIT(23)
#define BIT_PMU_APB_PD_CAM_SYS_BISR_DONE                                                BIT(22)
#define BIT_PMU_APB_PD_VSP_CORE_BISR_DONE                                               BIT(21)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_BISR_DONE                                           BIT(20)
#define BIT_PMU_APB_PD_ISP_TOP_BISR_DONE                                                BIT(19)
#define BIT_PMU_APB_PD_WTLCP_SYS_BISR_DONE                                              BIT(18)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_BISR_DONE                                           BIT(17)
#define BIT_PMU_APB_PD_WTLCP_TD_BISR_DONE                                               BIT(16)
#define BIT_PMU_APB_PD_PUB1_SYS_BISR_DONE                                               BIT(15)
#define BIT_PMU_APB_PD_GPU_TOP_BISR_DONE                                                BIT(14)
#define BIT_PMU_APB_PD_WTLCP_LDSP_BISR_DONE                                             BIT(13)
#define BIT_PMU_APB_PD_VSP_SYS_BISR_DONE                                                BIT(12)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_BISR_DONE                                           BIT(11)
#define BIT_PMU_APB_PD_PUB0_SYS_BISR_DONE                                               BIT(10)
#define BIT_PMU_APB_PD_AGCP_DSP_BISR_DONE                                               BIT(9)
#define BIT_PMU_APB_PD_GPU_PHANTOM_BISR_DONE                                            BIT(8)
#define BIT_PMU_APB_PD_AP_SYS_BISR_DONE                                                 BIT(7)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_BISR_DONE                                          BIT(6)
#define BIT_PMU_APB_PD_TOP_BISR_DONE                                                    BIT(5)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_BISR_DONE                                            BIT(4)
#define BIT_PMU_APB_PD_WTLCP_LTE_P4_BISR_DONE                                           BIT(3)
#define BIT_PMU_APB_PD_AGCP_SYS_BISR_DONE                                               BIT(2)
#define BIT_PMU_APB_PD_PUBCP_SYS_BISR_DONE                                              BIT(1)
#define BIT_PMU_APB_PD_AON_SYS_BISR_DONE                                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_BISR_BUSY_STATUS0
// Register Offset : 0x0170
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_GPU_C1_BISR_BUSY                                                 BIT(25)
#define BIT_PMU_APB_PD_GPU_C0_BISR_BUSY                                                 BIT(24)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_BISR_BUSY                                          BIT(23)
#define BIT_PMU_APB_PD_CAM_SYS_BISR_BUSY                                                BIT(22)
#define BIT_PMU_APB_PD_VSP_CORE_BISR_BUSY                                               BIT(21)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_BISR_BUSY                                           BIT(20)
#define BIT_PMU_APB_PD_ISP_TOP_BISR_BUSY                                                BIT(19)
#define BIT_PMU_APB_PD_WTLCP_SYS_BISR_BUSY                                              BIT(18)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_BISR_BUSY                                           BIT(17)
#define BIT_PMU_APB_PD_WTLCP_TD_BISR_BUSY                                               BIT(16)
#define BIT_PMU_APB_PD_PUB1_SYS_BISR_BUSY                                               BIT(15)
#define BIT_PMU_APB_PD_GPU_TOP_BISR_BUSY                                                BIT(14)
#define BIT_PMU_APB_PD_WTLCP_LDSP_BISR_BUSY                                             BIT(13)
#define BIT_PMU_APB_PD_VSP_SYS_BISR_BUSY                                                BIT(12)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_BISR_BUSY                                           BIT(11)
#define BIT_PMU_APB_PD_PUB0_SYS_BISR_BUSY                                               BIT(10)
#define BIT_PMU_APB_PD_AGCP_DSP_BISR_BUSY                                               BIT(9)
#define BIT_PMU_APB_PD_GPU_PHANTOM_BISR_BUSY                                            BIT(8)
#define BIT_PMU_APB_PD_AP_SYS_BISR_BUSY                                                 BIT(7)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_BISR_BUSY                                          BIT(6)
#define BIT_PMU_APB_PD_TOP_BISR_BUSY                                                    BIT(5)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_BISR_BUSY                                            BIT(4)
#define BIT_PMU_APB_PD_WTLCP_LTE_P4_BISR_BUSY                                           BIT(3)
#define BIT_PMU_APB_PD_AGCP_SYS_BISR_BUSY                                               BIT(2)
#define BIT_PMU_APB_PD_PUBCP_SYS_BISR_BUSY                                              BIT(1)
#define BIT_PMU_APB_PD_AON_SYS_BISR_BUSY                                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_BISR_BYP_CFG0
// Register Offset : 0x0178
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_GPU_C1_BISR_FORCE_BYP                                            BIT(25)
#define BIT_PMU_APB_PD_GPU_C0_BISR_FORCE_BYP                                            BIT(24)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_BISR_FORCE_BYP                                     BIT(23)
#define BIT_PMU_APB_PD_CAM_SYS_BISR_FORCE_BYP                                           BIT(22)
#define BIT_PMU_APB_PD_VSP_CORE_BISR_FORCE_BYP                                          BIT(21)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_BISR_FORCE_BYP                                      BIT(20)
#define BIT_PMU_APB_PD_ISP_TOP_BISR_FORCE_BYP                                           BIT(19)
#define BIT_PMU_APB_PD_WTLCP_SYS_BISR_FORCE_BYP                                         BIT(18)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_BISR_FORCE_BYP                                      BIT(17)
#define BIT_PMU_APB_PD_WTLCP_TD_BISR_FORCE_BYP                                          BIT(16)
#define BIT_PMU_APB_PD_PUB1_SYS_BISR_FORCE_BYP                                          BIT(15)
#define BIT_PMU_APB_PD_GPU_TOP_BISR_FORCE_BYP                                           BIT(14)
#define BIT_PMU_APB_PD_WTLCP_LDSP_BISR_FORCE_BYP                                        BIT(13)
#define BIT_PMU_APB_PD_VSP_SYS_BISR_FORCE_BYP                                           BIT(12)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_BISR_FORCE_BYP                                      BIT(11)
#define BIT_PMU_APB_PD_PUB0_SYS_BISR_FORCE_BYP                                          BIT(10)
#define BIT_PMU_APB_PD_AGCP_DSP_BISR_FORCE_BYP                                          BIT(9)
#define BIT_PMU_APB_PD_GPU_PHANTOM_BISR_FORCE_BYP                                       BIT(8)
#define BIT_PMU_APB_PD_AP_SYS_BISR_FORCE_BYP                                            BIT(7)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_BISR_FORCE_BYP                                     BIT(6)
#define BIT_PMU_APB_PD_TOP_BISR_FORCE_BYP                                               BIT(5)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_BISR_FORCE_BYP                                       BIT(4)
#define BIT_PMU_APB_PD_WTLCP_LTE_P4_BISR_FORCE_BYP                                      BIT(3)
#define BIT_PMU_APB_PD_AGCP_SYS_BISR_FORCE_BYP                                          BIT(2)
#define BIT_PMU_APB_PD_PUBCP_SYS_BISR_FORCE_BYP                                         BIT(1)
#define BIT_PMU_APB_PD_AON_SYS_BISR_FORCE_BYP                                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_BISR_FORCE_EN_CFG0
// Register Offset : 0x0180
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_GPU_C1_BISR_FORCE_EN                                             BIT(25)
#define BIT_PMU_APB_PD_GPU_C0_BISR_FORCE_EN                                             BIT(24)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_BISR_FORCE_EN                                      BIT(23)
#define BIT_PMU_APB_PD_CAM_SYS_BISR_FORCE_EN                                            BIT(22)
#define BIT_PMU_APB_PD_VSP_CORE_BISR_FORCE_EN                                           BIT(21)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_BISR_FORCE_EN                                       BIT(20)
#define BIT_PMU_APB_PD_ISP_TOP_BISR_FORCE_EN                                            BIT(19)
#define BIT_PMU_APB_PD_WTLCP_SYS_BISR_FORCE_EN                                          BIT(18)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_BISR_FORCE_EN                                       BIT(17)
#define BIT_PMU_APB_PD_WTLCP_TD_BISR_FORCE_EN                                           BIT(16)
#define BIT_PMU_APB_PD_PUB1_SYS_BISR_FORCE_EN                                           BIT(15)
#define BIT_PMU_APB_PD_GPU_TOP_BISR_FORCE_EN                                            BIT(14)
#define BIT_PMU_APB_PD_WTLCP_LDSP_BISR_FORCE_EN                                         BIT(13)
#define BIT_PMU_APB_PD_VSP_SYS_BISR_FORCE_EN                                            BIT(12)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_BISR_FORCE_EN                                       BIT(11)
#define BIT_PMU_APB_PD_PUB0_SYS_BISR_FORCE_EN                                           BIT(10)
#define BIT_PMU_APB_PD_AGCP_DSP_BISR_FORCE_EN                                           BIT(9)
#define BIT_PMU_APB_PD_GPU_PHANTOM_BISR_FORCE_EN                                        BIT(8)
#define BIT_PMU_APB_PD_AP_SYS_BISR_FORCE_EN                                             BIT(7)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_BISR_FORCE_EN                                      BIT(6)
#define BIT_PMU_APB_PD_TOP_BISR_FORCE_EN                                                BIT(5)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_BISR_FORCE_EN                                        BIT(4)
#define BIT_PMU_APB_PD_WTLCP_LTE_P4_BISR_FORCE_EN                                       BIT(3)
#define BIT_PMU_APB_PD_AGCP_SYS_BISR_FORCE_EN                                           BIT(2)
#define BIT_PMU_APB_PD_PUBCP_SYS_BISR_FORCE_EN                                          BIT(1)
#define BIT_PMU_APB_PD_AON_SYS_BISR_FORCE_EN                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_SLEEP_XTL_ON_CTRL0
// Register Offset : 0x0184
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUBCP_SYS_SLEEP_XTL_ON                                              BIT(4)
#define BIT_PMU_APB_AGCP_SYS_SLEEP_XTL_ON                                               BIT(3)
#define BIT_PMU_APB_WTLCP_SYS_SLEEP_XTL_ON                                              BIT(2)
#define BIT_PMU_APB_CM4_SYS_SLEEP_XTL_ON                                                BIT(1)
#define BIT_PMU_APB_AP_SYS_SLEEP_XTL_ON                                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PWR_WAIT_CNT_CFG1
// Register Offset : 0x018C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_AGCP_SYS_PWR_WAIT_CNT(x)                                            (((x) & 0xFF) << 24)
#define BIT_PMU_APB_WTLCP_SYS_PWR_WAIT_CNT(x)                                           (((x) & 0xFF) << 16)
#define BIT_PMU_APB_CM4_SYS_PWR_WAIT_CNT(x)                                             (((x) & 0xFF) << 8)
#define BIT_PMU_APB_AP_SYS_PWR_WAIT_CNT(x)                                              (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PWR_WAIT_CNT_CFG0
// Register Offset : 0x0190
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUBCP_SYS_PWR_WAIT_CNT(x)                                           (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PWR_PD_WAIT_CNT_CFG1
// Register Offset : 0x0198
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_AGCP_SYS_PWR_PD_WAIT_CNT(x)                                         (((x) & 0xFF) << 24)
#define BIT_PMU_APB_WTLCP_SYS_PWR_PD_WAIT_CNT(x)                                        (((x) & 0xFF) << 16)
#define BIT_PMU_APB_CM4_SYS_PWR_PD_WAIT_CNT(x)                                          (((x) & 0xFF) << 8)
#define BIT_PMU_APB_AP_SYS_PWR_PD_WAIT_CNT(x)                                           (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PWR_PD_WAIT_CNT_CFG0
// Register Offset : 0x019C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUBCP_SYS_PWR_PD_WAIT_CNT(x)                                        (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_PUBCP_SYS_CORE_INT_DISABLE
// Register Offset : 0x01A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_PUBCP_SYS_CORE_INT_DISABLE                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_TGDSP_CORE_INT_DISABLE
// Register Offset : 0x01A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_TGDSP_CORE_INT_DISABLE                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_AGCP_DSP_CORE_INT_DISABLE
// Register Offset : 0x01AC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_AGCP_DSP_CORE_INT_DISABLE                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LDSP_CORE_INT_DISABLE
// Register Offset : 0x01B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LDSP_CORE_INT_DISABLE                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_BIA_CORE_INT_DISABLE
// Register Offset : 0x01B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_BIA_CORE_INT_DISABLE                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_AP_SYS_DSLP_ENA
// Register Offset : 0x01C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_AP_SYS_DSLP_ENA                                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CM4_SYS_DSLP_ENA
// Register Offset : 0x01C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CM4_SYS_DSLP_ENA                                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_WTLCP_SYS_DSLP_ENA
// Register Offset : 0x01CC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_WTLCP_SYS_DSLP_ENA                                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_AGCP_SYS_DSLP_ENA
// Register Offset : 0x01D0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_AGCP_SYS_DSLP_ENA                                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PUBCP_SYS_DSLP_ENA
// Register Offset : 0x01D4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUBCP_SYS_DSLP_ENA                                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_TGDSP_DSLP_ENA
// Register Offset : 0x01E4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_TGDSP_DSLP_ENA                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_AGCP_DSP_DSLP_ENA
// Register Offset : 0x01E8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_AGCP_DSP_DSLP_ENA                                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LDSP_DSLP_ENA
// Register Offset : 0x01EC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LDSP_DSLP_ENA                                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_BIA_DSLP_ENA
// Register Offset : 0x01F0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_BIA_DSLP_ENA                                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PWR_ST_DBG_DLY0
// Register Offset : 0x01F4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CGM_OFF_DLY(x)                                                      (((x) & 0xFF) << 24)
#define BIT_PMU_APB_CGM_ON_DLY(x)                                                       (((x) & 0xFF) << 16)
#define BIT_PMU_APB_ISO_OFF_DLY(x)                                                      (((x) & 0xFF) << 8)
#define BIT_PMU_APB_RST_DEASSERT_DLY(x)                                                 (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PWR_ST_DBG_DLY1
// Register Offset : 0x01F8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_SHUTDOWN_M_D_DLY(x)                                                 (((x) & 0xFF) << 8)
#define BIT_PMU_APB_RST_ASSERT_DLY(x)                                                   (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PWR_ST_DBG_DLY2
// Register Offset : 0x01FC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PWR_ST_CLK_DIV_CFG(x)                                               (((x) & 0x3FF) << 10)
#define BIT_PMU_APB_SLP_CTRL_CLK_DIV_CFG(x)                                             (((x) & 0x3FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_LIGHT_SLEEP_ENABLE0
// Register Offset : 0x0204
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUBCP_SYS_LSLP0_ENA                                                 BIT(4)
#define BIT_PMU_APB_AGCP_SYS_LSLP0_ENA                                                  BIT(3)
#define BIT_PMU_APB_WTLCP_SYS_LSLP0_ENA                                                 BIT(2)
#define BIT_PMU_APB_AP_SYS_LSLP1_ENA                                                    BIT(1)
#define BIT_PMU_APB_AP_SYS_LSLP0_ENA                                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PUB_DEEP_SLEEP_ENABLE0
// Register Offset : 0x0208
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUBCP_SYS_PUB_DSLP0_ENA                                             BIT(4)
#define BIT_PMU_APB_AGCP_SYS_PUB_DSLP0_ENA                                              BIT(3)
#define BIT_PMU_APB_WTLCP_SYS_PUB_DSLP0_ENA                                             BIT(2)
#define BIT_PMU_APB_AP_SYS_PUB_DSLP1_ENA                                                BIT(1)
#define BIT_PMU_APB_AP_SYS_PUB_DSLP0_ENA                                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_DOZE_SLEEP_ENABLE0
// Register Offset : 0x0214
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUBCP_SYS_DOZE_ENA                                                  BIT(4)
#define BIT_PMU_APB_AGCP_SYS_DOZE_ENA                                                   BIT(3)
#define BIT_PMU_APB_WTLCP_SYS_DOZE_ENA                                                  BIT(2)
#define BIT_PMU_APB_CM4_SYS_DOZE_ENA                                                    BIT(1)
#define BIT_PMU_APB_AP_SYS_DOZE_ENA                                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PLL_CNT_DONE_STATUS0
// Register Offset : 0x021C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_RPLL0_CNT_DONE                                                      BIT(16)
#define BIT_PMU_APB_XTL0_CNT_DONE                                                       BIT(15)
#define BIT_PMU_APB_LPLL0_CNT_DONE                                                      BIT(14)
#define BIT_PMU_APB_RC_CNT_DONE                                                         BIT(13)
#define BIT_PMU_APB_ISPPLL_CNT_DONE                                                     BIT(12)
#define BIT_PMU_APB_TWPLL_CNT_DONE                                                      BIT(11)
#define BIT_PMU_APB_MPLL2_CNT_DONE                                                      BIT(10)
#define BIT_PMU_APB_MPLL1_CNT_DONE                                                      BIT(9)
#define BIT_PMU_APB_XTLBUF0_CNT_DONE                                                    BIT(8)
#define BIT_PMU_APB_DSPLL_CNT_DONE                                                      BIT(7)
#define BIT_PMU_APB_RPLL1_CNT_DONE                                                      BIT(6)
#define BIT_PMU_APB_XTLBUF1_CNT_DONE                                                    BIT(5)
#define BIT_PMU_APB_MPLL0_CNT_DONE                                                      BIT(4)
#define BIT_PMU_APB_DPLL0_CNT_DONE                                                      BIT(3)
#define BIT_PMU_APB_XTLBUF2_CNT_DONE                                                    BIT(2)
#define BIT_PMU_APB_DPLL1_CNT_DONE                                                      BIT(1)
#define BIT_PMU_APB_GPLL_CNT_DONE                                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_POWER_SWITCH_ACK_D_STATUS0
// Register Offset : 0x0224
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_ACK_D                                              BIT(22)
#define BIT_PMU_APB_PD_CAM_SYS_ACK_D                                                    BIT(21)
#define BIT_PMU_APB_PD_VSP_CORE_ACK_D                                                   BIT(20)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_ACK_D                                               BIT(19)
#define BIT_PMU_APB_PD_ISP_TOP_ACK_D                                                    BIT(18)
#define BIT_PMU_APB_PD_WTLCP_SYS_ACK_D                                                  BIT(17)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_ACK_D                                               BIT(16)
#define BIT_PMU_APB_PD_WTLCP_TD_ACK_D                                                   BIT(15)
#define BIT_PMU_APB_PD_PUB1_SYS_ACK_D                                                   BIT(14)
#define BIT_PMU_APB_PD_GPU_TOP_ACK_D                                                    BIT(13)
#define BIT_PMU_APB_PD_WTLCP_LDSP_ACK_D                                                 BIT(12)
#define BIT_PMU_APB_PD_VSP_SYS_ACK_D                                                    BIT(11)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_ACK_D                                               BIT(10)
#define BIT_PMU_APB_PD_PUB0_SYS_ACK_D                                                   BIT(9)
#define BIT_PMU_APB_PD_AGCP_DSP_ACK_D                                                   BIT(8)
#define BIT_PMU_APB_PD_GPU_PHANTOM_ACK_D                                                BIT(7)
#define BIT_PMU_APB_PD_AP_SYS_ACK_D                                                     BIT(6)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_ACK_D                                              BIT(5)
#define BIT_PMU_APB_PD_TOP_ACK_D                                                        BIT(4)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_ACK_D                                                BIT(3)
#define BIT_PMU_APB_PD_WTLCP_LTE_P4_ACK_D                                               BIT(2)
#define BIT_PMU_APB_PD_AGCP_SYS_ACK_D                                                   BIT(1)
#define BIT_PMU_APB_PD_PUBCP_SYS_ACK_D                                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_POWER_SWITCH_ACK_M_STATUS0
// Register Offset : 0x022C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_ACK_M                                              BIT(22)
#define BIT_PMU_APB_PD_CAM_SYS_ACK_M                                                    BIT(21)
#define BIT_PMU_APB_PD_VSP_CORE_ACK_M                                                   BIT(20)
#define BIT_PMU_APB_PD_WTLCP_LTE_P2_ACK_M                                               BIT(19)
#define BIT_PMU_APB_PD_ISP_TOP_ACK_M                                                    BIT(18)
#define BIT_PMU_APB_PD_WTLCP_SYS_ACK_M                                                  BIT(17)
#define BIT_PMU_APB_PD_WTLCP_LTE_P3_ACK_M                                               BIT(16)
#define BIT_PMU_APB_PD_WTLCP_TD_ACK_M                                                   BIT(15)
#define BIT_PMU_APB_PD_PUB1_SYS_ACK_M                                                   BIT(14)
#define BIT_PMU_APB_PD_GPU_TOP_ACK_M                                                    BIT(13)
#define BIT_PMU_APB_PD_WTLCP_LDSP_ACK_M                                                 BIT(12)
#define BIT_PMU_APB_PD_VSP_SYS_ACK_M                                                    BIT(11)
#define BIT_PMU_APB_PD_WTLCP_LTE_P1_ACK_M                                               BIT(10)
#define BIT_PMU_APB_PD_PUB0_SYS_ACK_M                                                   BIT(9)
#define BIT_PMU_APB_PD_AGCP_DSP_ACK_M                                                   BIT(8)
#define BIT_PMU_APB_PD_GPU_PHANTOM_ACK_M                                                BIT(7)
#define BIT_PMU_APB_PD_AP_SYS_ACK_M                                                     BIT(6)
#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_ACK_M                                              BIT(5)
#define BIT_PMU_APB_PD_TOP_ACK_M                                                        BIT(4)
#define BIT_PMU_APB_PD_WTLCP_TGDSP_ACK_M                                                BIT(3)
#define BIT_PMU_APB_PD_WTLCP_LTE_P4_ACK_M                                               BIT(2)
#define BIT_PMU_APB_PD_AGCP_SYS_ACK_M                                                   BIT(1)
#define BIT_PMU_APB_PD_PUBCP_SYS_ACK_M                                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CGM_PMU_SEL_CFG
// Register Offset : 0x0234
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CGM_PMU_SEL_REG(x)                                                  (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_WTLCP_TGDSP_WAKEUP_SOURCE_EN0
// Register Offset : 0x0238
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_WTLCP_TGDSP_WAKEUP_SOURCE_TG_DSP_WAKEUP_INT_EN                      BIT(5)
#define BIT_PMU_APB_WTLCP_TGDSP_WAKEUP_SOURCE_AON_MDAR_INT_EN                           BIT(4)
#define BIT_PMU_APB_WTLCP_TGDSP_WAKEUP_SOURCE_WTL_MAIBOX_TAR_TGDSP_EN                   BIT(3)
#define BIT_PMU_APB_WTLCP_TGDSP_WAKEUP_SOURCE_AON_GPIO_INT_EN                           BIT(2)
#define BIT_PMU_APB_WTLCP_TGDSP_WAKEUP_SOURCE_AON_EIC_INT_EN                            BIT(1)
#define BIT_PMU_APB_WTLCP_TGDSP_WAKEUP_SOURCE_WTL_MCDT_INT_TGDSP_EN                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_AGCP_DSP_WAKEUP_SOURCE_EN0
// Register Offset : 0x023C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_AGCP_DSP_WAKEUP_SOURCE_AON_CPALL_EIC_INT_EN                         BIT(4)
#define BIT_PMU_APB_AGCP_DSP_WAKEUP_SOURCE_AG_GPIO_INT_EN                               BIT(3)
#define BIT_PMU_APB_AGCP_DSP_WAKEUP_SOURCE_AG_MAILBOX_SRC_IRQ_EN                        BIT(2)
#define BIT_PMU_APB_AGCP_DSP_WAKEUP_SOURCE_AG_MAILBOX_TAR_IRQ_EN                        BIT(1)
#define BIT_PMU_APB_AGCP_DSP_WAKEUP_SOURCE_INT_DMA_CHN2_MDAR_EN                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_WTLCP_LDSP_WAKEUP_SOURCE_EN0
// Register Offset : 0x0240
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_WTLCP_LDSP_WAKEUP_SOURCE_LTE_DSP_WAKEUP_INT_EN                      BIT(5)
#define BIT_PMU_APB_WTLCP_LDSP_WAKEUP_SOURCE_AON_MDAR_INT_EN                            BIT(4)
#define BIT_PMU_APB_WTLCP_LDSP_WAKEUP_SOURCE_WTL_MAIBOX_TAR_LDSP_EN                     BIT(3)
#define BIT_PMU_APB_WTLCP_LDSP_WAKEUP_SOURCE_AON_GPIO_INT_EN                            BIT(2)
#define BIT_PMU_APB_WTLCP_LDSP_WAKEUP_SOURCE_AON_CPALL_EIC_INT_EN                       BIT(1)
#define BIT_PMU_APB_WTLCP_LDSP_WAKEUP_SOURCE_WTL_MCDT_INT_LDSP_EN                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_WTLCP_SYS_WAKEUP_SOURCE_EN0
// Register Offset : 0x0244
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_WTLCP_SYS_WAKEUP_SOURCE_PUBCP_WAKEUP_INT_EN                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CM4_SYS_WAKEUP_SOURCE_EN0
// Register Offset : 0x0248
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_BUSMON_WTLCP_EN                       BIT(31)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_DFS_PUB1_COMPLETE_EN                      BIT(30)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_DFS_PUB0_COMPLETE_EN                      BIT(29)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_PUB1_CTRL_EN                          BIT(28)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_PUB0_CTRL_EN                          BIT(27)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_THM_EN                                BIT(26)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_PUB1_AXI_BUSMON_EN                    BIT(25)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_GPIO_EN                               BIT(24)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_PUB0_AXI_BUSMON_EN                    BIT(23)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_PUB0_DFI_BUSMON_EN                    BIT(22)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_ITHM0_OVERHEAT_EN                     BIT(21)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_HARDWARE_PUB0_DFS_EXIT_EN                 BIT(20)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_BUSMON_M4_EN                          BIT(19)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_BUSMON_M3_EN                          BIT(18)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_BUSMON_M2_EN                          BIT(17)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_BUSMON_M1_EN                          BIT(16)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_BUSMON_M0_EN                          BIT(15)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_AON_DEF_SLV_EN                        BIT(14)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_PUB0_BUSMON_DMA_EN                    BIT(13)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_ITHM0_ALERT_EN                        BIT(12)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_PUB0_DFS_ERROR_EN                     BIT(11)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_SP_TMR2_EN                            BIT(10)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_BIA_WDG_RESET_EN                      BIT(9)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_DMA_AUD_EN                            BIT(8)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_GPU_VDROP_OUT_0_EN                            BIT(7)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_FPU_EXCEPTION_EN                          BIT(6)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_BUSMON_SP_EN                          BIT(5)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_SP_SPI_EN                             BIT(4)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_AUD_DMA_CHN1_GRP1_EN                      BIT(3)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_AUD_DMA_CHN1_GRP2_EN                      BIT(2)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_AUD_DMA_CHN2_GRP1_EN                      BIT(1)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_AUD_DMA_CHN2_GRP2_EN                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_CM4_SYS_WAKEUP_SOURCE_EN1
// Register Offset : 0x024C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_SEC_EIC1_EN                           BIT(31)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_PWR_ON_EN                             BIT(30)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_CAM_SYS_BUSMON_EN                     BIT(29)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_PWR_DOWN_EN                           BIT(28)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_BASEIA_DVFS_EN                            BIT(27)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_AON_EIC_EN                            BIT(26)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_EIC_GPIO_LAT_EN                       BIT(25)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_EIC_GPIO_NON_LAT_EN                   BIT(24)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_SP_EIC_EN                             BIT(23)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_CM4_SOFT_EN                           BIT(22)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_SP_TMR1_EN                            BIT(21)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_SP_SYST_EN                            BIT(20)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_SP_UART0_EN                           BIT(19)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_SP_UART1_EN                           BIT(18)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_SP_I2C0_EN                            BIT(17)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_SP_I2C1_EN                            BIT(16)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_SP_WDG_EN                             BIT(15)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_MBOX_TAR_CM4_EN                       BIT(14)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_MBOX_SRC_CM4_EN                       BIT(13)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_CM4_DMA_EN                            BIT(12)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_SP_GPIO_EN                            BIT(11)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_AON_I2C_EN                            BIT(10)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_ANA_EN                                BIT(9)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_ADI_EN                                BIT(8)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_VSP_SYS_BUSMON_EN                     BIT(7)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_EIC_NON_LAT_EN                        BIT(6)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_BIA_TMR_EN                            BIT(5)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_VOLTAGE0_BAD_REQUEST_EN               BIT(4)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_VOLTAGE1_BAD_REQUEST_EN               BIT(3)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_BUSMON_AP_EN                          BIT(2)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_SP_TMR0_EN                            BIT(1)
#define BIT_PMU_APB_CM4_SYS_WAKEUP_SOURCE_INT_REQ_BUSMON_PUBCP_EN                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PUBCP_CR5_WAKEUP_SOURCE_EN0
// Register Offset : 0x0250
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PUBCP_CR5_WAKEUP_SOURCE_INT_RFFE_EN                                 BIT(12)
#define BIT_PMU_APB_PUBCP_CR5_WAKEUP_SOURCE_PUBCP_WAKEUP_INT_EN                         BIT(11)
#define BIT_PMU_APB_PUBCP_CR5_WAKEUP_SOURCE_AON_MAIBOX_TAR_PCP_EN                       BIT(10)
#define BIT_PMU_APB_PUBCP_CR5_WAKEUP_SOURCE_AON_MDAR_IRQ_EN                             BIT(9)
#define BIT_PMU_APB_PUBCP_CR5_WAKEUP_SOURCE_CR5_MCDT_IRQ_EN                             BIT(8)
#define BIT_PMU_APB_PUBCP_CR5_WAKEUP_SOURCE_CR5_WDG_IRQ_EN                              BIT(7)
#define BIT_PMU_APB_PUBCP_CR5_WAKEUP_SOURCE_CR5_GPIO_IRQ_EN                             BIT(6)
#define BIT_PMU_APB_PUBCP_CR5_WAKEUP_SOURCE_CR5_EIC_IRQ_EN                              BIT(5)
#define BIT_PMU_APB_PUBCP_CR5_WAKEUP_SOURCE_CR5_SYST_IRQ_EN                             BIT(4)
#define BIT_PMU_APB_PUBCP_CR5_WAKEUP_SOURCE_CR5_TIMER2_IRQ_EN                           BIT(3)
#define BIT_PMU_APB_PUBCP_CR5_WAKEUP_SOURCE_CR5_TIMER1_IRQ_EN                           BIT(2)
#define BIT_PMU_APB_PUBCP_CR5_WAKEUP_SOURCE_CR5_TIMER0_IRQ_EN                           BIT(1)
#define BIT_PMU_APB_PUBCP_CR5_WAKEUP_SOURCE_CR5_WCDMA_SLP_INT_EN                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_BASEIA_WAKEUP_SOURCE_EN0
// Register Offset : 0x0254
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_VBC_ADC01_EN                           BIT(31)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AUD_EN                                 BIT(30)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_CPP_EN                                 BIT(29)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_PCP_WDG_RST_EN                         BIT(28)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_PCP_WDG_IRQ_EN                         BIT(27)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_VBC_DAC01_EN                           BIT(26)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_WTLCP_TG_WDG_RST_EN                        BIT(25)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_AUD_DMA_CHN1_GRP1_EN                       BIT(24)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_AUD_DMA_CHN2_GRP1_EN                       BIT(23)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_AUD_DMA_CHN1_GRP2_EN                       BIT(22)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_AUD_DMA_CHN2_GRP2_EN                       BIT(21)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_WTLCP_LTE_WDG_RST_EN                       BIT(20)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_VBC_DAC23_EN                           BIT(19)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_MEM_FW_PUB0_EN                         BIT(18)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_VOLTAGE0_BAD_REQUEST_EN                BIT(17)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_VOLTAGE0_CH_BUSY_EN                    BIT(16)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_VOLTAGE0_TRANS_EN                      BIT(15)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_VOLTAGE1_BAD_REQUEST_EN                BIT(14)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_VOLTAGE1_CH_BUSY_EN                    BIT(13)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_VOLTAGE1_TRANS_EN                      BIT(12)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_PUB0_DFS_ERROR_EN                      BIT(11)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_PUB1_DFS_ERROR_EN                      BIT(10)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_BIA_TMR_EN                             BIT(9)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_MEM_FW_AP_PUB0_EN                      BIT(8)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_FW_EN                               BIT(7)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DSI0_PLL_EN                            BIT(6)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_CLK_32K_DET_EN                         BIT(5)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_SEC_WDG_EN                             BIT(4)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_MEM_FW_AON_IRAM_EN                     BIT(3)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_SEC_RTC_EN                             BIT(2)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_SEC_TIMER0_EN                          BIT(1)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_SEC_TIMER1_EN                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_BASEIA_WAKEUP_SOURCE_EN1
// Register Offset : 0x0258
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_MBOX_TAR_AP_NOWAKEUP_EN                BIT(31)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_CAM_MMU_PF_EN                          BIT(30)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_IRQ_AP_WDG_EN                              BIT(29)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DJTAG_EN                               BIT(28)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_THM_EN                                 BIT(27)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_ISP_PERFMON_EN                         BIT(26)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_IRQ1_GPU_EN                                BIT(25)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_IRQ0_GPU_EN                                BIT(24)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_VSP_EN                                 BIT(23)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_VSP_ENC_EN                             BIT(22)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_IRQ_ISP_CH0_EN                             BIT(21)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_IRQ_CSI1_EN                                BIT(20)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_IRQ_CSI0_EN                                BIT(19)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_IRQ_JPG1_EN                                BIT(18)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_IRQ_JPG0_EN                                BIT(17)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DCAM1_EN                               BIT(16)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DCAM0_EN                               BIT(15)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_ITHM0_ALERT_EN                         BIT(14)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_GSP0_EN                                BIT(13)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DSI1_0_EN                              BIT(12)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DSI1_1_EN                              BIT(11)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DSI0_0_EN                              BIT(10)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DSI0_1_EN                              BIT(9)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_ITHM0_OVERHEAT_EN                      BIT(8)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DISPC0_EN                              BIT(7)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_PUB1_CTRL_EN                           BIT(6)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_PUB1_AXI_BUSMON_EN                     BIT(5)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_PUB1_DFI_BUSMON_EN                     BIT(4)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_PUB0_CTRL_EN                           BIT(3)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_PUB0_AXI_BUSMON_EN                     BIT(2)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_PUB0_DFI_BUSMON_EN                     BIT(1)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_VBC_ADC23_EN                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_BASEIA_WAKEUP_SOURCE_EN2
// Register Offset : 0x025C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_ADI_EN                                 BIT(31)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AON_DEF_SLV_EN                         BIT(30)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AON_TMR_EN                             BIT(29)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AON_SYST_EN                            BIT(28)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_MBOX_SRC_A53_EN                        BIT(27)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_MBOX_TAR_A53_EN                        BIT(26)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_I2C_EN                                 BIT(25)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_ANA_EN                                 BIT(24)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_ITHM1_ALERT_EN                         BIT(23)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_USB2_EN                             BIT(22)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DCAM2ISP_IF_EN                         BIT(21)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_SDIO0_EN                            BIT(20)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_SDIO1_EN                            BIT(19)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_SDIO2_EN                            BIT(18)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_EMMC_EN                             BIT(17)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_DMA_EN                              BIT(16)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_BUSMON0_EN                          BIT(15)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_SPI3_EN                                BIT(13)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_CE0_EN                              BIT(12)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_CE1_EN                              BIT(11)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_SEC_REQ_DMA_AUD_EN                         BIT(10)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DMA_AUD_EN                             BIT(9)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_IRQ_GPIO_EN                                BIT(8)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_KPD_EN                                 BIT(7)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_EIC_EN                                 BIT(6)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_TMR0_EN                             BIT(5)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_TMR1_EN                             BIT(4)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_TMR2_EN                             BIT(3)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_TMR3_EN                             BIT(2)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_TMR4_EN                             BIT(1)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_SYST_EN                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_BASEIA_WAKEUP_SOURCE_EN3
// Register Offset : 0x0260
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DSIPLL_LOCK_STATUS_EN                  BIT(31)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DMC_MPU_VIO_EN                         BIT(30)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_MPHY_HOP_OK_EN                             BIT(29)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_WTL_GSM_TX_EN                          BIT(28)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_SEC_EIC_EN                             BIT(27)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_SEC_GPIO_EN                            BIT(26)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_BASEIA_DVFS_EN                             BIT(25)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_CAM_IDI_INT_SW_DONE_EN                         BIT(24)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_ISP_LITE_INT_REQ_CH1_EN                        BIT(23)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_ITHM1_OVERHEAT_EN                      BIT(22)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_UART0_EN                            BIT(21)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_UART1_EN                            BIT(20)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_UART2_EN                            BIT(19)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_UART3_EN                            BIT(18)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_UART4_EN                            BIT(17)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_SPI0_EN                             BIT(16)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_SPI1_EN                             BIT(15)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_SPI2_EN                             BIT(14)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_SIM_EN                              BIT(13)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_I2C0_EN                             BIT(12)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_I2C1_EN                             BIT(11)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_I2C2_EN                             BIT(10)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DSIPLL_UNLOCK_STATUS_EN                BIT(9)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_I2C4_EN                             BIT(8)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_I2C5_EN                             BIT(7)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_IIS0_EN                             BIT(6)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_IIS1_EN                             BIT(5)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_IIS2_EN                             BIT(4)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_IIS3_EN                             BIT(3)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_CAM_SYS_BUSMON_EN                      BIT(2)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_VSP_SYS_BUSMON_EN                      BIT(1)
#define BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DMA_SEC_AP_EN                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_PUBCP_SYS_SHUTDOWN_MARK_STATUS
// Register Offset : 0x0268
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_PUBCP_SYS_SHUTDOWN_MARK(x)                                       (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_AGCP_SYS_SHUTDOWN_MARK_STATUS
// Register Offset : 0x026C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_AGCP_SYS_SHUTDOWN_MARK(x)                                        (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LTE_P4_SHUTDOWN_MARK_STATUS
// Register Offset : 0x0270
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P4_SHUTDOWN_MARK(x)                                    (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_TGDSP_SHUTDOWN_MARK_STATUS
// Register Offset : 0x0274
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_TGDSP_SHUTDOWN_MARK(x)                                     (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_TOP_SHUTDOWN_MARK_STATUS
// Register Offset : 0x0278
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_TOP_SHUTDOWN_MARK(x)                                             (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_HU3GE_B_SHUTDOWN_MARK_STATUS
// Register Offset : 0x027C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_HU3GE_B_SHUTDOWN_MARK(x)                                   (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_AP_SYS_SHUTDOWN_MARK_STATUS
// Register Offset : 0x0280
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_AP_SYS_SHUTDOWN_MARK(x)                                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_GPU_PHANTOM_SHUTDOWN_MARK_STATUS
// Register Offset : 0x0284
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_GPU_PHANTOM_SHUTDOWN_MARK(x)                                     (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_AGCP_DSP_SHUTDOWN_MARK_STATUS
// Register Offset : 0x0288
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_AGCP_DSP_SHUTDOWN_MARK(x)                                        (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_PUB0_SYS_SHUTDOWN_MARK_STATUS
// Register Offset : 0x028C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_PUB0_SYS_SHUTDOWN_MARK(x)                                        (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LTE_P1_SHUTDOWN_MARK_STATUS
// Register Offset : 0x0290
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P1_SHUTDOWN_MARK(x)                                    (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_VSP_SYS_SHUTDOWN_MARK_STATUS
// Register Offset : 0x0294
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_VSP_SYS_SHUTDOWN_MARK(x)                                         (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LDSP_SHUTDOWN_MARK_STATUS
// Register Offset : 0x0298
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LDSP_SHUTDOWN_MARK(x)                                      (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_GPU_TOP_SHUTDOWN_MARK_STATUS
// Register Offset : 0x029C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_GPU_TOP_SHUTDOWN_MARK(x)                                         (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_PUB1_SYS_SHUTDOWN_MARK_STATUS
// Register Offset : 0x02A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_PUB1_SYS_SHUTDOWN_MARK(x)                                        (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_TD_SHUTDOWN_MARK_STATUS
// Register Offset : 0x02A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_TD_SHUTDOWN_MARK(x)                                        (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_BIA_SHUTDOWN_MARK_STATUS
// Register Offset : 0x02A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_BIA_SHUTDOWN_MARK(x)                                             (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LTE_P3_SHUTDOWN_MARK_STATUS
// Register Offset : 0x02AC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P3_SHUTDOWN_MARK(x)                                    (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_SYS_SHUTDOWN_MARK_STATUS
// Register Offset : 0x02B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_SYS_SHUTDOWN_MARK(x)                                       (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_ISP_TOP_SHUTDOWN_MARK_STATUS
// Register Offset : 0x02B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_ISP_TOP_SHUTDOWN_MARK(x)                                         (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_LTE_P2_SHUTDOWN_MARK_STATUS
// Register Offset : 0x02B8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_LTE_P2_SHUTDOWN_MARK(x)                                    (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_VSP_CORE_SHUTDOWN_MARK_STATUS
// Register Offset : 0x02BC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_VSP_CORE_SHUTDOWN_MARK(x)                                        (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_CAM_SYS_SHUTDOWN_MARK_STATUS
// Register Offset : 0x02C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_CAM_SYS_SHUTDOWN_MARK(x)                                         (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_WTLCP_HU3GE_A_SHUTDOWN_MARK_STATUS
// Register Offset : 0x02C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_WTLCP_HU3GE_A_SHUTDOWN_MARK(x)                                   (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_DDR0_ACC_RDY
// Register Offset : 0x02CC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_DDR0_ACC_RDY                                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_DDR0_LIGHT_ACC_RDY
// Register Offset : 0x02D0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_DDR0_LIGHT_ACC_RDY                                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_DDR0_SLP_CFG
// Register Offset : 0x02D4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_DDR0_PWR_DOWN_WAIT_CNT(x)                                           (((x) & 0xFFFF) << 16)
#define BIT_PMU_APB_DDR0_SLEEP_WAIT_CNT(x)                                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_DDR1_ACC_RDY
// Register Offset : 0x02D8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_DDR1_ACC_RDY                                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_DDR1_LIGHT_ACC_RDY
// Register Offset : 0x02DC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_DDR1_LIGHT_ACC_RDY                                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_DDR1_SLP_CFG
// Register Offset : 0x02E0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_DDR1_PWR_DOWN_WAIT_CNT(x)                                           (((x) & 0xFFFF) << 16)
#define BIT_PMU_APB_DDR1_SLEEP_WAIT_CNT(x)                                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PMU_APB_PD_CM4_CORE_INT_DISABLE
// Register Offset : 0x02E4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PMU_APB_PD_CM4_CORE_INT_DISABLE                                             BIT(0)


#endif // _PMU_APB_REG_H
