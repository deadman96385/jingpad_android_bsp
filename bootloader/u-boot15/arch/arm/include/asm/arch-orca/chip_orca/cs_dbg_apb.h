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


#ifndef CS_DBG_APB_H
#define CS_DBG_APB_H

#define CTL_BASE_CS_DBG_APB 0x7800A000


#define REG_CS_DBG_APB_BUS_BUSY_TIMER         ( CTL_BASE_CS_DBG_APB + 0x0000 )
#define REG_CS_DBG_APB_MISC_STATUS            ( CTL_BASE_CS_DBG_APB + 0x0004 )
#define REG_CS_DBG_APB_PWR_UP_EN              ( CTL_BASE_CS_DBG_APB + 0x0008 )
#define REG_CS_DBG_APB_DBG_CTRL               ( CTL_BASE_CS_DBG_APB + 0x000C )
#define REG_CS_DBG_APB_STM_SOFT_RST           ( CTL_BASE_CS_DBG_APB + 0x0010 )
#define REG_CS_DBG_APB_RCO_CLK_CTRL           ( CTL_BASE_CS_DBG_APB + 0x0014 )
#define REG_CS_DBG_APB_DBG_SYS_LP_CTRL_1      ( CTL_BASE_CS_DBG_APB + 0x0018 )
#define REG_CS_DBG_APB_DBG_SYS_LP_CTRL_2      ( CTL_BASE_CS_DBG_APB + 0x001C )
#define REG_CS_DBG_APB_APCPU_CS_LP_CTRL       ( CTL_BASE_CS_DBG_APB + 0x0020 )
#define REG_CS_DBG_APB_DBG_MTX_M0_LPC_CTRL    ( CTL_BASE_CS_DBG_APB + 0x0024 )
#define REG_CS_DBG_APB_DBG_MTX_S0_LPC_CTRL    ( CTL_BASE_CS_DBG_APB + 0x0028 )
#define REG_CS_DBG_APB_DBG_MTX_S1_LPC_CTRL    ( CTL_BASE_CS_DBG_APB + 0x002C )
#define REG_CS_DBG_APB_SUB_SYS_DBG_CLK_CTRL   ( CTL_BASE_CS_DBG_APB + 0x00F0 )
#define REG_CS_DBG_APB_DEBUG_SUBSYS_SEL_A     ( CTL_BASE_CS_DBG_APB + 0x0100 )
#define REG_CS_DBG_APB_DEBUG_SUBSYS_SEL_B     ( CTL_BASE_CS_DBG_APB + 0x0104 )
#define REG_CS_DBG_APB_AON_DBG_MOD_SEL        ( CTL_BASE_CS_DBG_APB + 0x010C )
#define REG_CS_DBG_APB_AON_DBG_SIG_SEL        ( CTL_BASE_CS_DBG_APB + 0x0110 )
#define REG_CS_DBG_APB_APCPU_DBG_MOD_SEL      ( CTL_BASE_CS_DBG_APB + 0x0114 )
#define REG_CS_DBG_APB_APCPU_DBG_SIG_SEL      ( CTL_BASE_CS_DBG_APB + 0x0118 )
#define REG_CS_DBG_APB_AUDCP_DBG_MOD_SEL      ( CTL_BASE_CS_DBG_APB + 0x011C )
#define REG_CS_DBG_APB_AUDCP_DBG_SIG_SEL      ( CTL_BASE_CS_DBG_APB + 0x0120 )
#define REG_CS_DBG_APB_PSCP_DBG_MOD_SEL       ( CTL_BASE_CS_DBG_APB + 0x0124 )
#define REG_CS_DBG_APB_PSCP_DBG_SIG_SEL       ( CTL_BASE_CS_DBG_APB + 0x0128 )
#define REG_CS_DBG_APB_PUB_DBG_MOD_SEL        ( CTL_BASE_CS_DBG_APB + 0x012C )
#define REG_CS_DBG_APB_PUB_DBG_SIG_SEL        ( CTL_BASE_CS_DBG_APB + 0x0130 )
#define REG_CS_DBG_APB_V3_DBG_MOD_SEL         ( CTL_BASE_CS_DBG_APB + 0x0134 )
#define REG_CS_DBG_APB_V3_DBG_SIG_SEL         ( CTL_BASE_CS_DBG_APB + 0x0138 )
#define REG_CS_DBG_APB_NR_DBG_MOD_SEL         ( CTL_BASE_CS_DBG_APB + 0x013C )
#define REG_CS_DBG_APB_NR_DBG_SIG_SEL         ( CTL_BASE_CS_DBG_APB + 0x0140 )
#define REG_CS_DBG_APB_AP_DBG_MOD_SEL         ( CTL_BASE_CS_DBG_APB + 0x014C )
#define REG_CS_DBG_APB_AP_DBG_SIG_SEL         ( CTL_BASE_CS_DBG_APB + 0x0150 )
#define REG_CS_DBG_APB_MDAR_DBG_MOD_SEL       ( CTL_BASE_CS_DBG_APB + 0x0154 )
#define REG_CS_DBG_APB_MDAR_DBG_SIG_SEL       ( CTL_BASE_CS_DBG_APB + 0x0158 )
#define REG_CS_DBG_APB_AON_DBG_MOD_SEL_2      ( CTL_BASE_CS_DBG_APB + 0x0160 )
#define REG_CS_DBG_APB_AON_DBG_SIG_SEL_2      ( CTL_BASE_CS_DBG_APB + 0x0164 )
#define REG_CS_DBG_APB_DBG_BUS0_SEL           ( CTL_BASE_CS_DBG_APB + 0x0200 )
#define REG_CS_DBG_APB_DBG_BUS1_SEL           ( CTL_BASE_CS_DBG_APB + 0x0204 )
#define REG_CS_DBG_APB_DBG_BUS2_SEL           ( CTL_BASE_CS_DBG_APB + 0x0208 )
#define REG_CS_DBG_APB_DBG_BUS3_SEL           ( CTL_BASE_CS_DBG_APB + 0x020C )
#define REG_CS_DBG_APB_DBG_BUS4_SEL           ( CTL_BASE_CS_DBG_APB + 0x0210 )
#define REG_CS_DBG_APB_DBG_BUS5_SEL           ( CTL_BASE_CS_DBG_APB + 0x0214 )
#define REG_CS_DBG_APB_DBG_BUS6_SEL           ( CTL_BASE_CS_DBG_APB + 0x0218 )
#define REG_CS_DBG_APB_DBG_BUS7_SEL           ( CTL_BASE_CS_DBG_APB + 0x021C )
#define REG_CS_DBG_APB_DBG_BUS8_SEL           ( CTL_BASE_CS_DBG_APB + 0x0220 )
#define REG_CS_DBG_APB_DBG_BUS9_SEL           ( CTL_BASE_CS_DBG_APB + 0x0224 )
#define REG_CS_DBG_APB_DBG_BUS10_SEL          ( CTL_BASE_CS_DBG_APB + 0x0228 )
#define REG_CS_DBG_APB_DBG_BUS11_SEL          ( CTL_BASE_CS_DBG_APB + 0x022C )
#define REG_CS_DBG_APB_DBG_BUS12_SEL          ( CTL_BASE_CS_DBG_APB + 0x0230 )
#define REG_CS_DBG_APB_DBG_BUS13_SEL          ( CTL_BASE_CS_DBG_APB + 0x0234 )
#define REG_CS_DBG_APB_DBG_BUS14_SEL          ( CTL_BASE_CS_DBG_APB + 0x0238 )
#define REG_CS_DBG_APB_DBG_BUS15_SEL          ( CTL_BASE_CS_DBG_APB + 0x023C )
#define REG_CS_DBG_APB_DBG_BUS16_SEL          ( CTL_BASE_CS_DBG_APB + 0x0240 )
#define REG_CS_DBG_APB_DBG_BUS17_SEL          ( CTL_BASE_CS_DBG_APB + 0x0244 )
#define REG_CS_DBG_APB_DBG_BUS18_SEL          ( CTL_BASE_CS_DBG_APB + 0x0248 )
#define REG_CS_DBG_APB_DBG_BUS19_SEL          ( CTL_BASE_CS_DBG_APB + 0x024C )
#define REG_CS_DBG_APB_DBG_BUS20_SEL          ( CTL_BASE_CS_DBG_APB + 0x0250 )
#define REG_CS_DBG_APB_DBG_BUS21_SEL          ( CTL_BASE_CS_DBG_APB + 0x0254 )
#define REG_CS_DBG_APB_DBG_BUS22_SEL          ( CTL_BASE_CS_DBG_APB + 0x0258 )
#define REG_CS_DBG_APB_DBG_BUS23_SEL          ( CTL_BASE_CS_DBG_APB + 0x025C )
#define REG_CS_DBG_APB_DBG_BUS24_SEL          ( CTL_BASE_CS_DBG_APB + 0x0260 )
#define REG_CS_DBG_APB_DBG_BUS25_SEL          ( CTL_BASE_CS_DBG_APB + 0x0264 )
#define REG_CS_DBG_APB_DBG_BUS26_SEL          ( CTL_BASE_CS_DBG_APB + 0x0268 )
#define REG_CS_DBG_APB_DBG_BUS27_SEL          ( CTL_BASE_CS_DBG_APB + 0x026C )
#define REG_CS_DBG_APB_DBG_BUS28_SEL          ( CTL_BASE_CS_DBG_APB + 0x0270 )
#define REG_CS_DBG_APB_DBG_BUS29_SEL          ( CTL_BASE_CS_DBG_APB + 0x0274 )
#define REG_CS_DBG_APB_DBG_BUS30_SEL          ( CTL_BASE_CS_DBG_APB + 0x0278 )
#define REG_CS_DBG_APB_DBG_BUS31_SEL          ( CTL_BASE_CS_DBG_APB + 0x027C )
#define REG_CS_DBG_APB_DBG_BUS_DATA_A         ( CTL_BASE_CS_DBG_APB + 0x0300 )
#define REG_CS_DBG_APB_DBG_BUS_DATA_B         ( CTL_BASE_CS_DBG_APB + 0x0304 )
#define REG_CS_DBG_APB_DBG_BUS_DATA           ( CTL_BASE_CS_DBG_APB + 0x0308 )
#define REG_CS_DBG_APB_ETR_AXI_MON_INT_EN     ( CTL_BASE_CS_DBG_APB + 0x0400 )
#define REG_CS_DBG_APB_ETR_AXI_MON_INT_CLR    ( CTL_BASE_CS_DBG_APB + 0x0404 )
#define REG_CS_DBG_APB_ETR_AXI_MON_INT_RAW    ( CTL_BASE_CS_DBG_APB + 0x0408 )
#define REG_CS_DBG_APB_ETR_AXI_MON_INT_STAT   ( CTL_BASE_CS_DBG_APB + 0x040C )
#define REG_CS_DBG_APB_ETR_AXI_MON_AWADDR0    ( CTL_BASE_CS_DBG_APB + 0x0410 )
#define REG_CS_DBG_APB_ETR_AXI_MON_AWADDR1    ( CTL_BASE_CS_DBG_APB + 0x0414 )
#define REG_CS_DBG_APB_ETR_AXI_MON_AWADDR2    ( CTL_BASE_CS_DBG_APB + 0x0418 )
#define REG_CS_DBG_APB_ETR_AXI_MON_AWADDR3    ( CTL_BASE_CS_DBG_APB + 0x041C )

/* REG_CS_DBG_APB_BUS_BUSY_TIMER */

#define BIT_CS_DBG_APB_BUS_BUSY_TIMER_EN              BIT(8)
#define BIT_CS_DBG_APB_BUS_BUSY_TIMER_DIVIDER(x)      (((x) & 0xFF))

/* REG_CS_DBG_APB_MISC_STATUS */

#define BIT_CS_DBG_APB_TPIU_DATA_OVF                  BIT(4)
#define BIT_CS_DBG_APB_APCPU_CSSYS_EN                 BIT(3)
#define BIT_CS_DBG_APB_APCPU_APB_TRANS_CSYSREQ        BIT(2)
#define BIT_CS_DBG_APB_CPWRUPREQ_CDBGPWRUP            BIT(1)
#define BIT_CS_DBG_APB_DBGCONNECTED                   BIT(0)

/* REG_CS_DBG_APB_PWR_UP_EN */

#define BIT_CS_DBG_APB_CSYSPWRUPREQ_NRCP_EN           BIT(6)
#define BIT_CS_DBG_APB_CSYSPWRUPREQ_V3PS_EN           BIT(5)
#define BIT_CS_DBG_APB_CSYSPWRUPREQ_V3PHY_EN          BIT(4)
#define BIT_CS_DBG_APB_CSYSPWRUPREQ_RCO_EN            BIT(3)
#define BIT_CS_DBG_APB_CSYSPWRUPREQ_PSCP_EN           BIT(2)
#define BIT_CS_DBG_APB_CSYSPWRUPREQ_AON_CM4_EN        BIT(1)
#define BIT_CS_DBG_APB_CSYSPWRUPREQ_APCPU_EN          BIT(0)

/* REG_CS_DBG_APB_DBG_CTRL */

#define BIT_CS_DBG_APB_DBG_SYS_CLK_GATING_SEL         BIT(18)
#define BIT_CS_DBG_APB_ANTI_HANG_EN                   BIT(17)
#define BIT_CS_DBG_APB_U_SYS_AON_CSSYS_EN_REG         BIT(16)
#define BIT_CS_DBG_APB_APCPU_DAP_EN_REG               BIT(15)
#define BIT_CS_DBG_APB_CROSS_TRIGGER_EN               BIT(14)
#define BIT_CS_DBG_APB_APCPU_MTX_SOFT_RST             BIT(13)
#define BIT_CS_DBG_APB_APCPU_AXI_TRANS_BLKR_BYPASS    BIT(12)
#define BIT_CS_DBG_APB_APCPU_APB_TRANS_BLKR_BYPASS    BIT(11)
#define BIT_CS_DBG_APB_APCPU_CORINTH_DEBUG_EN_FOR_LP  BIT(10)
#define BIT_CS_DBG_APB_AUTO_REG_SAVE_SEL              BIT(9)
#define BIT_CS_DBG_APB_AUTO_REG_SAVE_SOFT_TRIG        BIT(8)
#define BIT_CS_DBG_APB_AUTO_REG_SAVE_EN               BIT(7)
#define BIT_CS_DBG_APB_CSSYS_SOFT_RST_EN              BIT(6)
#define BIT_CS_DBG_APB_AON_MTX_SOFT_RST_EN            BIT(5)
#define BIT_CS_DBG_APB_DAP_SOFT_RST_EN                BIT(4)
#define BIT_CS_DBG_APB_APCPU_CSSYS_EN_REG             BIT(3)
#define BIT_CS_DBG_APB_APCPU_DBG_CONNECTED_SW         BIT(2)
#define BIT_CS_DBG_APB_APCPU_DBG_CONNECTED_CTRL(x)    (((x) & 0x3))

/* REG_CS_DBG_APB_STM_SOFT_RST */

#define BIT_CS_DBG_APB_STM_SOFT_RST                   BIT(0)

/* REG_CS_DBG_APB_RCO_CLK_CTRL */

#define BIT_CS_DBG_APB_AON_APB_CLK_RCO_SEL(x)         (((x) & 0x7) << 9)
#define BIT_CS_DBG_APB_CSSYS_CLK_RCO_SEL(x)           (((x) & 0x7) << 6)
#define BIT_CS_DBG_APB_DAP_CLK_RCO_SEL(x)             (((x) & 0x7) << 3)
#define BIT_CS_DBG_APB_AON_APB_CLK_RCO_CTRL_EN_REG    BIT(2)
#define BIT_CS_DBG_APB_CSSYS_CLK_RCO_CTRL_EN_REG      BIT(1)
#define BIT_CS_DBG_APB_DAP_CLK_RCO_CTRL_EN_REG        BIT(0)

/* REG_CS_DBG_APB_DBG_SYS_LP_CTRL_1 */

#define BIT_CS_DBG_APB_DBG_SYS_IDLE_THR(x)            (((x) & 0xFFFF) << 16)
#define BIT_CS_DBG_APB_DBG_SYS_CLK_SWITCH_INTVL(x)    (((x) & 0xFF) << 8)
#define BIT_CS_DBG_APB_DBG_SYS_CLK_IDLE_SEL(x)        (((x) & 0x7) << 4)
#define BIT_CS_DBG_APB_DBG_SYS_CW_EN                  BIT(2)
#define BIT_CS_DBG_APB_DBG_SYS_CG_EN                  BIT(1)
#define BIT_CS_DBG_APB_DBG_SYS_CLK_CTRL_EN            BIT(0)

/* REG_CS_DBG_APB_DBG_SYS_LP_CTRL_2 */

#define BIT_CS_DBG_APB_DBG_SYS_SW_EVENT(x)            (((x) & 0xFFFF) << 16)
#define BIT_CS_DBG_APB_AXI_ED_EN                      BIT(12)
#define BIT_CS_DBG_APB_ETR_ED_EN                      BIT(11)
#define BIT_CS_DBG_APB_TPIU_ED_EN                     BIT(10)
#define BIT_CS_DBG_APB_DAP_CPWRUP_ED_EN               BIT(9)
#define BIT_CS_DBG_APB_DAP_APB_ED_EN                  BIT(8)
#define BIT_CS_DBG_APB_CTM_ED_EN                      BIT(7)
#define BIT_CS_DBG_APB_CTI_ED_EN                      BIT(6)
#define BIT_CS_DBG_APB_RTM_ED_EN                      BIT(5)
#define BIT_CS_DBG_APB_PTM_ED_EN                      BIT(4)
#define BIT_CS_DBG_APB_NRCP_ED_EN                     BIT(3)
#define BIT_CS_DBG_APB_V3_ED_EN                       BIT(2)
#define BIT_CS_DBG_APB_PSCP_ED_EN                     BIT(1)
#define BIT_CS_DBG_APB_APCPU_ED_EN                    BIT(0)

/* REG_CS_DBG_APB_APCPU_CS_LP_CTRL */

#define BIT_CS_DBG_APB_APCPU_CS_IDLE_THR(x)           (((x) & 0xFFFF) << 16)
#define BIT_CS_DBG_APB_APCPU_CS_CLK_SWITCH_INTVL(x)   (((x) & 0xFF) << 8)
#define BIT_CS_DBG_APB_APCPU_CS_CLK_IDLE_DIV_EN       BIT(7)
#define BIT_CS_DBG_APB_APCPU_CS_CLK_IDLE_DIV(x)       (((x) & 0x7) << 4)
#define BIT_CS_DBG_APB_APCPU_CS_CLK_IDLE_SEL_EN       BIT(3)
#define BIT_CS_DBG_APB_APCPU_CS_CLK_IDLE_SEL(x)       (((x) & 0x3) << 1)
#define BIT_CS_DBG_APB_APCPU_CS_CLK_CTRL_EN           BIT(0)

/* REG_CS_DBG_APB_DBG_MTX_M0_LPC_CTRL */

#define BIT_CS_DBG_APB_DBG_MTX_M0_LP_NUM(x)           (((x) & 0xFFFF) << 16)
#define BIT_CS_DBG_APB_DBG_MTX_M0_PU_NUM(x)           (((x) & 0xFF) << 8)
#define BIT_CS_DBG_APB_DBG_MTX_M0_CSYSACK_SYNC_SEL    BIT(2)
#define BIT_CS_DBG_APB_DBG_MTX_M0_CACTIVE_SYNC_SEL    BIT(1)
#define BIT_CS_DBG_APB_DBG_MTX_M0_LPC_EB              BIT(0)

/* REG_CS_DBG_APB_DBG_MTX_S0_LPC_CTRL */

#define BIT_CS_DBG_APB_DBG_MTX_S0_LP_NUM(x)           (((x) & 0xFFFF) << 16)
#define BIT_CS_DBG_APB_DBG_MTX_S0_PU_NUM(x)           (((x) & 0xFF) << 8)
#define BIT_CS_DBG_APB_DBG_MTX_S0_CSYSACK_SYNC_SEL    BIT(2)
#define BIT_CS_DBG_APB_DBG_MTX_S0_CACTIVE_SYNC_SEL    BIT(1)
#define BIT_CS_DBG_APB_DBG_MTX_S0_LPC_EB              BIT(0)

/* REG_CS_DBG_APB_DBG_MTX_S1_LPC_CTRL */

#define BIT_CS_DBG_APB_DBG_MTX_S1_LP_NUM(x)           (((x) & 0xFFFF) << 16)
#define BIT_CS_DBG_APB_DBG_MTX_S1_PU_NUM(x)           (((x) & 0xFF) << 8)
#define BIT_CS_DBG_APB_DBG_MTX_S1_CSYSACK_SYNC_SEL    BIT(2)
#define BIT_CS_DBG_APB_DBG_MTX_S1_CACTIVE_SYNC_SEL    BIT(1)
#define BIT_CS_DBG_APB_DBG_MTX_S1_LPC_EB              BIT(0)

/* REG_CS_DBG_APB_SUB_SYS_DBG_CLK_CTRL */

#define BIT_CS_DBG_APB_TPIU2SERDES_CGM_EN             BIT(0)

/* REG_CS_DBG_APB_DEBUG_SUBSYS_SEL_A */

#define BIT_CS_DBG_APB_DBG_SUBSYS_SEL_A(x)            (((x) & 0xFF))

/* REG_CS_DBG_APB_DEBUG_SUBSYS_SEL_B */

#define BIT_CS_DBG_APB_DBG_SUBSYS_SEL_B(x)            (((x) & 0xFF))

/* REG_CS_DBG_APB_AON_DBG_MOD_SEL */

#define BIT_CS_DBG_APB_AON_DBG_MOD_SEL(x)             (((x) & 0xFF))

/* REG_CS_DBG_APB_AON_DBG_SIG_SEL */

#define BIT_CS_DBG_APB_AON_DBG_SIG_SEL(x)             (((x) & 0xFF))

/* REG_CS_DBG_APB_APCPU_DBG_MOD_SEL */

#define BIT_CS_DBG_APB_APCPU_DBG_MOD_SEL(x)           (((x) & 0xFF))

/* REG_CS_DBG_APB_APCPU_DBG_SIG_SEL */

#define BIT_CS_DBG_APB_APCPU_DBG_SIG_SEL(x)           (((x) & 0xFF))

/* REG_CS_DBG_APB_AUDCP_DBG_MOD_SEL */

#define BIT_CS_DBG_APB_AUDCP_DBG_MOD_SEL(x)           (((x) & 0xFF))

/* REG_CS_DBG_APB_AUDCP_DBG_SIG_SEL */

#define BIT_CS_DBG_APB_AUDCP_DBG_SIG_SEL(x)           (((x) & 0xFF))

/* REG_CS_DBG_APB_PSCP_DBG_MOD_SEL */

#define BIT_CS_DBG_APB_PSCP_DBG_MOD_SEL(x)            (((x) & 0xFF))

/* REG_CS_DBG_APB_PSCP_DBG_SIG_SEL */

#define BIT_CS_DBG_APB_PSCP_DBG_SIG_SEL(x)            (((x) & 0xFF))

/* REG_CS_DBG_APB_PUB_DBG_MOD_SEL */

#define BIT_CS_DBG_APB_PUB_DBG_MOD_SEL(x)             (((x) & 0xFF))

/* REG_CS_DBG_APB_PUB_DBG_SIG_SEL */

#define BIT_CS_DBG_APB_PUB_DBG_SIG_SEL(x)             (((x) & 0xFF))

/* REG_CS_DBG_APB_V3_DBG_MOD_SEL */

#define BIT_CS_DBG_APB_V3_DBG_MOD_SEL(x)              (((x) & 0xFF))

/* REG_CS_DBG_APB_V3_DBG_SIG_SEL */

#define BIT_CS_DBG_APB_V3_DBG_SIG_SEL(x)              (((x) & 0xFF))

/* REG_CS_DBG_APB_NR_DBG_MOD_SEL */

#define BIT_CS_DBG_APB_NR_DBG_MOD_SEL(x)              (((x) & 0xFF))

/* REG_CS_DBG_APB_NR_DBG_SIG_SEL */

#define BIT_CS_DBG_APB_NR_DBG_SIG_SEL(x)              (((x) & 0xFF))

/* REG_CS_DBG_APB_AP_DBG_MOD_SEL */

#define BIT_CS_DBG_APB_AP_DBG_MOD_SEL(x)              (((x) & 0xFF))

/* REG_CS_DBG_APB_AP_DBG_SIG_SEL */

#define BIT_CS_DBG_APB_AP_DBG_SIG_SEL(x)              (((x) & 0xFF))

/* REG_CS_DBG_APB_MDAR_DBG_MOD_SEL */

#define BIT_CS_DBG_APB_MDAR_DBG_MOD_SEL(x)            (((x) & 0xFF))

/* REG_CS_DBG_APB_MDAR_DBG_SIG_SEL */

#define BIT_CS_DBG_APB_MDAR_DBG_SIG_SEL(x)            (((x) & 0xFF))

/* REG_CS_DBG_APB_AON_DBG_MOD_SEL_2 */

#define BIT_CS_DBG_APB_AON_DBG_MOD_SEL_2(x)           (((x) & 0xFF))

/* REG_CS_DBG_APB_AON_DBG_SIG_SEL_2 */

#define BIT_CS_DBG_APB_AON_DBG_SIG_SEL_2(x)           (((x) & 0xFF))

/* REG_CS_DBG_APB_DBG_BUS0_SEL */

#define BIT_CS_DBG_APB_DBG_BUS0_SEL(x)                (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS1_SEL */

#define BIT_CS_DBG_APB_DBG_BUS1_SEL(x)                (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS2_SEL */

#define BIT_CS_DBG_APB_DBG_BUS2_SEL(x)                (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS3_SEL */

#define BIT_CS_DBG_APB_DBG_BUS3_SEL(x)                (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS4_SEL */

#define BIT_CS_DBG_APB_DBG_BUS4_SEL(x)                (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS5_SEL */

#define BIT_CS_DBG_APB_DBG_BUS5_SEL(x)                (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS6_SEL */

#define BIT_CS_DBG_APB_DBG_BUS6_SEL(x)                (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS7_SEL */

#define BIT_CS_DBG_APB_DBG_BUS7_SEL(x)                (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS8_SEL */

#define BIT_CS_DBG_APB_DBG_BUS8_SEL(x)                (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS9_SEL */

#define BIT_CS_DBG_APB_DBG_BUS9_SEL(x)                (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS10_SEL */

#define BIT_CS_DBG_APB_DBG_BUS10_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS11_SEL */

#define BIT_CS_DBG_APB_DBG_BUS11_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS12_SEL */

#define BIT_CS_DBG_APB_DBG_BUS12_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS13_SEL */

#define BIT_CS_DBG_APB_DBG_BUS13_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS14_SEL */

#define BIT_CS_DBG_APB_DBG_BUS14_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS15_SEL */

#define BIT_CS_DBG_APB_DBG_BUS15_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS16_SEL */

#define BIT_CS_DBG_APB_DBG_BUS16_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS17_SEL */

#define BIT_CS_DBG_APB_DBG_BUS17_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS18_SEL */

#define BIT_CS_DBG_APB_DBG_BUS18_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS19_SEL */

#define BIT_CS_DBG_APB_DBG_BUS19_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS20_SEL */

#define BIT_CS_DBG_APB_DBG_BUS20_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS21_SEL */

#define BIT_CS_DBG_APB_DBG_BUS21_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS22_SEL */

#define BIT_CS_DBG_APB_DBG_BUS22_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS23_SEL */

#define BIT_CS_DBG_APB_DBG_BUS23_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS24_SEL */

#define BIT_CS_DBG_APB_DBG_BUS24_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS25_SEL */

#define BIT_CS_DBG_APB_DBG_BUS25_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS26_SEL */

#define BIT_CS_DBG_APB_DBG_BUS26_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS27_SEL */

#define BIT_CS_DBG_APB_DBG_BUS27_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS28_SEL */

#define BIT_CS_DBG_APB_DBG_BUS28_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS29_SEL */

#define BIT_CS_DBG_APB_DBG_BUS29_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS30_SEL */

#define BIT_CS_DBG_APB_DBG_BUS30_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS31_SEL */

#define BIT_CS_DBG_APB_DBG_BUS31_SEL(x)               (((x) & 0x3F))

/* REG_CS_DBG_APB_DBG_BUS_DATA_A */

#define BIT_CS_DBG_APB_DBG_BUS_DATA_A(x)              (((x) & 0xFFFFFFFF))

/* REG_CS_DBG_APB_DBG_BUS_DATA_B */

#define BIT_CS_DBG_APB_DBG_BUS_DATA_B(x)              (((x) & 0xFFFFFFFF))

/* REG_CS_DBG_APB_DBG_BUS_DATA */

#define BIT_CS_DBG_APB_DBG_BUS_DATA(x)                (((x) & 0xFFFFFFFF))

/* REG_CS_DBG_APB_ETR_AXI_MON_INT_EN */

#define BIT_CS_DBG_APB_AWADDR3_MATCH_INT_EN           BIT(3)
#define BIT_CS_DBG_APB_AWADDR2_MATCH_INT_EN           BIT(2)
#define BIT_CS_DBG_APB_AWADDR1_MATCH_INT_EN           BIT(1)
#define BIT_CS_DBG_APB_AWADDR0_MATCH_INT_EN           BIT(0)

/* REG_CS_DBG_APB_ETR_AXI_MON_INT_CLR */

#define BIT_CS_DBG_APB_AWADDR3_MATCH_INT_CLR          BIT(3)
#define BIT_CS_DBG_APB_AWADDR2_MATCH_INT_CLR          BIT(2)
#define BIT_CS_DBG_APB_AWADDR1_MATCH_INT_CLR          BIT(1)
#define BIT_CS_DBG_APB_AWADDR0_MATCH_INT_CLR          BIT(0)

/* REG_CS_DBG_APB_ETR_AXI_MON_INT_RAW */

#define BIT_CS_DBG_APB_AWADDR3_MATCH_INT_RAW          BIT(3)
#define BIT_CS_DBG_APB_AWADDR2_MATCH_INT_RAW          BIT(2)
#define BIT_CS_DBG_APB_AWADDR1_MATCH_INT_RAW          BIT(1)
#define BIT_CS_DBG_APB_AWADDR0_MATCH_INT_RAW          BIT(0)

/* REG_CS_DBG_APB_ETR_AXI_MON_INT_STAT */

#define BIT_CS_DBG_APB_AWADDR3_MATCH_INT_STAT         BIT(3)
#define BIT_CS_DBG_APB_AWADDR2_MATCH_INT_STAT         BIT(2)
#define BIT_CS_DBG_APB_AWADDR1_MATCH_INT_STAT         BIT(1)
#define BIT_CS_DBG_APB_AWADDR0_MATCH_INT_STAT         BIT(0)

/* REG_CS_DBG_APB_ETR_AXI_MON_AWADDR0 */

#define BIT_CS_DBG_APB_ETR_AXI_MON_AWADDR0(x)         (((x) & 0xFFFFFFF))

/* REG_CS_DBG_APB_ETR_AXI_MON_AWADDR1 */

#define BIT_CS_DBG_APB_ETR_AXI_MON_AWADDR1(x)         (((x) & 0xFFFFFFF))

/* REG_CS_DBG_APB_ETR_AXI_MON_AWADDR2 */

#define BIT_CS_DBG_APB_ETR_AXI_MON_AWADDR2(x)         (((x) & 0xFFFFFFF))

/* REG_CS_DBG_APB_ETR_AXI_MON_AWADDR3 */

#define BIT_CS_DBG_APB_ETR_AXI_MON_AWADDR3(x)         (((x) & 0xFFFFFFF))


#endif /* CS_DBG_APB_H */


