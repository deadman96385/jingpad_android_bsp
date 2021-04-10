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


#ifndef AON_CLK_LP_H
#define AON_CLK_LP_H

#define CTL_BASE_AON_CLK_LP 0x402D0C00


#define REG_AON_CLK_LP_CLK_LP_SEC              ( CTL_BASE_AON_CLK_LP + 0x0004 )
#define REG_AON_CLK_LP_CLK_SW_MODE_SEL         ( CTL_BASE_AON_CLK_LP + 0x0020 )
#define REG_AON_CLK_LP_BUSCLK_SW_FORCE_EN      ( CTL_BASE_AON_CLK_LP + 0x0024 )
#define REG_AON_CLK_LP_BUSCLK_MODE_SEL         ( CTL_BASE_AON_CLK_LP + 0x0028 )
#define REG_AON_CLK_LP_CSSYS_DCS_CTRL          ( CTL_BASE_AON_CLK_LP + 0x002C )
#define REG_AON_CLK_LP_AON_MATRIX_DCS_CTRL     ( CTL_BASE_AON_CLK_LP + 0x0030 )
#define REG_AON_CLK_LP_MM_EMC_DCS_CTRL         ( CTL_BASE_AON_CLK_LP + 0x0034 )
#define REG_AON_CLK_LP_VSP_EMC_DCS_CTRL        ( CTL_BASE_AON_CLK_LP + 0x0038 )
#define REG_AON_CLK_LP_GPU_CORE_DCS_CTRL       ( CTL_BASE_AON_CLK_LP + 0x003C )
#define REG_AON_CLK_LP_GPU_SOC_DCS_CTRL        ( CTL_BASE_AON_CLK_LP + 0x0040 )
#define REG_AON_CLK_LP_APCPU_CLKEN_CFG         ( CTL_BASE_AON_CLK_LP + 0x0044 )
#define REG_AON_CLK_LP_APCPU_CLKSEL_MODE       ( CTL_BASE_AON_CLK_LP + 0x004C )
#define REG_AON_CLK_LP_APCPU_IDLE_CLKSEL0      ( CTL_BASE_AON_CLK_LP + 0x0050 )
#define REG_AON_CLK_LP_APCPU_IDLE_CLKSEL1      ( CTL_BASE_AON_CLK_LP + 0x0054 )
#define REG_AON_CLK_LP_APCPU_CLKDIV_MODE       ( CTL_BASE_AON_CLK_LP + 0x0058 )
#define REG_AON_CLK_LP_APCPU_IDLE_CLKDIV0      ( CTL_BASE_AON_CLK_LP + 0x005C )
#define REG_AON_CLK_LP_APCPU_IDLE_CLKDIV1      ( CTL_BASE_AON_CLK_LP + 0x0060 )
#define REG_AON_CLK_LP_AP_AXI_CLK_MODE         ( CTL_BASE_AON_CLK_LP + 0x0064 )
#define REG_AON_CLK_LP_DISP_SYS_CLK_MODE       ( CTL_BASE_AON_CLK_LP + 0x0068 )
#define REG_AON_CLK_LP_MM_SYS_CLK_MODE         ( CTL_BASE_AON_CLK_LP + 0x006C )
#define REG_AON_CLK_LP_VSP_SYS_CLK_MODE        ( CTL_BASE_AON_CLK_LP + 0x0070 )
#define REG_AON_CLK_LP_PRE_DIV_SLP_EN          ( CTL_BASE_AON_CLK_LP + 0x0074 )
#define REG_AON_CLK_LP_APCPU_WFX_SEL_IDLE_EN   ( CTL_BASE_AON_CLK_LP + 0x0078 )
#define REG_AON_CLK_LP_APCPU_WFX_DIV_IDLE_EN   ( CTL_BASE_AON_CLK_LP + 0x007C )
#define REG_AON_CLK_LP_CLK_AUTO_GATE_DIV_CTRL  ( CTL_BASE_AON_CLK_LP + 0x0080 )
#define REG_AON_CLK_LP_CLK_AUTO_GATE_EN_CTRL0  ( CTL_BASE_AON_CLK_LP + 0x0084 )
#define REG_AON_CLK_LP_CLK_AUTO_GATE_EN_CTRL1  ( CTL_BASE_AON_CLK_LP + 0x0088 )
#define REG_AON_CLK_LP_CLK_AUTO_GATE_EN_CTRL2  ( CTL_BASE_AON_CLK_LP + 0x008C )
#define REG_AON_CLK_LP_CLK_AUTO_GATE_EN_CTRL3  ( CTL_BASE_AON_CLK_LP + 0x0090 )
#define REG_AON_CLK_LP_AON_M0_LPC              ( CTL_BASE_AON_CLK_LP + 0x0094 )
#define REG_AON_CLK_LP_AON_M1_LPC              ( CTL_BASE_AON_CLK_LP + 0x0098 )
#define REG_AON_CLK_LP_AON_M2_LPC              ( CTL_BASE_AON_CLK_LP + 0x009C )
#define REG_AON_CLK_LP_AON_M3_LPC              ( CTL_BASE_AON_CLK_LP + 0x00A0 )
#define REG_AON_CLK_LP_AON_M4_LPC              ( CTL_BASE_AON_CLK_LP + 0x00A4 )
#define REG_AON_CLK_LP_AON_M5_LPC              ( CTL_BASE_AON_CLK_LP + 0x00A8 )
#define REG_AON_CLK_LP_AON_M6_LPC              ( CTL_BASE_AON_CLK_LP + 0x00AC )
#define REG_AON_CLK_LP_AON_MAIN_LPC            ( CTL_BASE_AON_CLK_LP + 0x00B0 )
#define REG_AON_CLK_LP_AON_S0_LPC              ( CTL_BASE_AON_CLK_LP + 0x00B4 )
#define REG_AON_CLK_LP_AON_S1_LPC              ( CTL_BASE_AON_CLK_LP + 0x00B8 )
#define REG_AON_CLK_LP_AON_S2_LPC              ( CTL_BASE_AON_CLK_LP + 0x00BC )
#define REG_AON_CLK_LP_AON_S3_LPC              ( CTL_BASE_AON_CLK_LP + 0x00C0 )
#define REG_AON_CLK_LP_AON_S4_LPC              ( CTL_BASE_AON_CLK_LP + 0x00C4 )
#define REG_AON_CLK_LP_AON_S5_LPC              ( CTL_BASE_AON_CLK_LP + 0x00C8 )
#define REG_AON_CLK_LP_AON_S6_LPC              ( CTL_BASE_AON_CLK_LP + 0x00CC )
#define REG_AON_CLK_LP_AON_S8_LPC              ( CTL_BASE_AON_CLK_LP + 0x00D0 )
#define REG_AON_CLK_LP_AON_S9_LPC              ( CTL_BASE_AON_CLK_LP + 0x00D4 )
#define REG_AON_CLK_LP_EAXI_M0_LPC             ( CTL_BASE_AON_CLK_LP + 0x00D8 )
#define REG_AON_CLK_LP_EAXI_MAIN_LPC           ( CTL_BASE_AON_CLK_LP + 0x00DC )
#define REG_AON_CLK_LP_EAXI_S0_LPC             ( CTL_BASE_AON_CLK_LP + 0x00E0 )
#define REG_AON_CLK_LP_EAXI_S1_LPC             ( CTL_BASE_AON_CLK_LP + 0x00E4 )
#define REG_AON_CLK_LP_AON_DAP2CPU_LPC         ( CTL_BASE_AON_CLK_LP + 0x00EC )
#define REG_AON_CLK_LP_AON_WCN2EMC_LPC         ( CTL_BASE_AON_CLK_LP + 0x00F0 )
#define REG_AON_CLK_LP_AON_DISP2EMC_LPC        ( CTL_BASE_AON_CLK_LP + 0x00F4 )
#define REG_AON_CLK_LP_AON_WTL2PUB_LPC         ( CTL_BASE_AON_CLK_LP + 0x00F8 )
#define REG_AON_CLK_LP_AON_WCN2PUB_LPC         ( CTL_BASE_AON_CLK_LP + 0x00FC )
#define REG_AON_CLK_LP_CPU_CLUSTER_LPC_EB0     ( CTL_BASE_AON_CLK_LP + 0x0100 )
#define REG_AON_CLK_LP_CPU_CLUSTER_LPC_NUM0    ( CTL_BASE_AON_CLK_LP + 0x0104 )
#define REG_AON_CLK_LP_CPU_CLUSTER_LPC_EB1     ( CTL_BASE_AON_CLK_LP + 0x0108 )
#define REG_AON_CLK_LP_CPU_CLUSTER_LPC_NUM1    ( CTL_BASE_AON_CLK_LP + 0x010C )
#define REG_AON_CLK_LP_CPU_CLUSTER_LPC_NUM2    ( CTL_BASE_AON_CLK_LP + 0x0110 )
#define REG_AON_CLK_LP_CPU_CLUSTER_LPC_NUM3    ( CTL_BASE_AON_CLK_LP + 0x0114 )
#define REG_AON_CLK_LP_SLICE_DONWTREAM_EN      ( CTL_BASE_AON_CLK_LP + 0x0120 )
#define REG_AON_CLK_LP_IMG_GPU_CORE_DFS0       ( CTL_BASE_AON_CLK_LP + 0x0130 )
#define REG_AON_CLK_LP_IMG_GPU_CORE_DFS1       ( CTL_BASE_AON_CLK_LP + 0x0134 )
#define REG_AON_CLK_LP_IMG_GPU_SOC_DFS0        ( CTL_BASE_AON_CLK_LP + 0x0138 )
#define REG_AON_CLK_LP_IMG_GPU_SOC_DFS1        ( CTL_BASE_AON_CLK_LP + 0x013C )

/* REG_AON_CLK_LP_CLK_LP_SEC */


/* REG_AON_CLK_LP_CLK_SW_MODE_SEL */

#define BIT_AON_CLK_LP_CLK_CSSYS_DBG_MODE_SEL            BIT(10)
#define BIT_AON_CLK_LP_CLK_RFTI2_XO_MODE_SEL             BIT(9)
#define BIT_AON_CLK_LP_CLK_RFTI1_XO_MODE_SEL             BIT(8)
#define BIT_AON_CLK_LP_CLK_RFTI_LTH_MODE_SEL             BIT(7)
#define BIT_AON_CLK_LP_CLK_RFTI_SBI_MODE_SEL             BIT(6)
#define BIT_AON_CLK_LP_CLK_AP_AXI_MTX_PD                 BIT(5)
#define BIT_AON_CLK_LP_CLK_EMC_REF_MODE_SEL              BIT(4)
#define BIT_AON_CLK_LP_CLK_DISP_MODE_SEL                 BIT(3)
#define BIT_AON_CLK_LP_CLK_GPU_MODE_SEL                  BIT(2)
#define BIT_AON_CLK_LP_CLK_WCN_MODE_SEL                  BIT(1)
#define BIT_AON_CLK_LP_CLK_WCDMA_MODE_SEL                BIT(0)

/* REG_AON_CLK_LP_BUSCLK_SW_FORCE_EN */

#define BIT_AON_CLK_LP_CLK_WCDMA2WTLCP_SW_FORCE_ON       BIT(6)
#define BIT_AON_CLK_LP_CLK_WCDMA2PUBCP_SW_FORCE_ON       BIT(5)
#define BIT_AON_CLK_LP_CLK_AONMATRIX2PUB_SW_FORCE_ON     BIT(4)
#define BIT_AON_CLK_LP_CLK_AONMATRIX2WCNCP_SW_FORCE_ON   BIT(3)
#define BIT_AON_CLK_LP_CLK_AONMATRIX2PUBCP_SW_FORCE_ON   BIT(2)
#define BIT_AON_CLK_LP_CLK_AONMATRIX2WTLCP_SW_FORCE_ON   BIT(1)
#define BIT_AON_CLK_LP_CLK_AONMATRIX2AP_SW_FORCE_ON      BIT(0)

/* REG_AON_CLK_LP_BUSCLK_MODE_SEL */

#define BIT_AON_CLK_LP_CLK_AON_MATRIX2DBG_MODE_SEL       BIT(7)
#define BIT_AON_CLK_LP_CLK_WCDMA2WTLCP_MODE_SEL          BIT(6)
#define BIT_AON_CLK_LP_CLK_WCDMA2PUBCP_MODE_SEL          BIT(5)
#define BIT_AON_CLK_LP_CLK_AONMATRIX2PUB_MODE_SEL        BIT(4)
#define BIT_AON_CLK_LP_CLK_AONMATRIX2WCNCP_MODE_SEL      BIT(3)
#define BIT_AON_CLK_LP_CLK_AONMATRIX2PUBCP_MODE_SEL      BIT(2)
#define BIT_AON_CLK_LP_CLK_AONMATRIX2WTLCP_MODE_SEL      BIT(1)
#define BIT_AON_CLK_LP_CLK_AONMATRIX2AP_MODE_SEL         BIT(0)

/* REG_AON_CLK_LP_CSSYS_DCS_CTRL */

#define BIT_AON_CLK_LP_CSSYS_DCS_IDLE_NUM(x)             (((x) & 0xFF) << 24)
#define BIT_AON_CLK_LP_CSSYS_DCS_DIV(x)                  (((x) & 0xFF) << 16)
#define BIT_AON_CLK_LP_CSSYS_DCS_FORCE_DIV(x)            (((x) & 0xFF) << 8)
#define BIT_AON_CLK_LP_CSSYS_IDLE_CLK_OFF                BIT(2)
#define BIT_AON_CLK_LP_CSSYS_DCS_FORCE                   BIT(1)
#define BIT_AON_CLK_LP_CSSYS_DCS_EB                      BIT(0)

/* REG_AON_CLK_LP_AON_MATRIX_DCS_CTRL */

#define BIT_AON_CLK_LP_AON_MATRIX_DCS_IDLE_NUM(x)        (((x) & 0xFF) << 24)
#define BIT_AON_CLK_LP_AON_MATRIX_DCS_DIV(x)             (((x) & 0xFF) << 16)
#define BIT_AON_CLK_LP_AON_MATRIX_DCS_FORCE_DIV(x)       (((x) & 0xFF) << 8)
#define BIT_AON_CLK_LP_AON_MATRIX_IDLE_CLK_OFF           BIT(2)
#define BIT_AON_CLK_LP_AON_MATRIX_DCS_FORCE              BIT(1)
#define BIT_AON_CLK_LP_AON_MATRIX_DCS_EB                 BIT(0)

/* REG_AON_CLK_LP_MM_EMC_DCS_CTRL */

#define BIT_AON_CLK_LP_MM_EMC_DCS_IDLE_NUM(x)            (((x) & 0xFF) << 24)
#define BIT_AON_CLK_LP_MM_EMC_DCS_DIV(x)                 (((x) & 0xFF) << 16)
#define BIT_AON_CLK_LP_MM_EMC_DCS_FORCE_DIV(x)           (((x) & 0xFF) << 8)
#define BIT_AON_CLK_LP_MM_EMC_IDLE_CLK_OFF               BIT(2)
#define BIT_AON_CLK_LP_MM_EMC_DCS_FORCE                  BIT(1)
#define BIT_AON_CLK_LP_MM_EMC_DCS_EB                     BIT(0)

/* REG_AON_CLK_LP_VSP_EMC_DCS_CTRL */

#define BIT_AON_CLK_LP_VSP_EMC_DCS_IDLE_NUM(x)           (((x) & 0xFF) << 24)
#define BIT_AON_CLK_LP_VSP_EMC_DCS_DIV(x)                (((x) & 0xFF) << 16)
#define BIT_AON_CLK_LP_VSP_EMC_DCS_FORCE_DIV(x)          (((x) & 0xFF) << 8)
#define BIT_AON_CLK_LP_VSP_EMC_IDLE_CLK_OFF              BIT(2)
#define BIT_AON_CLK_LP_VSP_EMC_DCS_FORCE                 BIT(1)
#define BIT_AON_CLK_LP_VSP_EMC_DCS_EB                    BIT(0)

/* REG_AON_CLK_LP_GPU_CORE_DCS_CTRL */

#define BIT_AON_CLK_LP_GPU_CORE_DCS_IDLE_NUM(x)          (((x) & 0xFF) << 24)
#define BIT_AON_CLK_LP_GPU_CORE_DCS_DIV(x)               (((x) & 0xFF) << 16)
#define BIT_AON_CLK_LP_GPU_CORE_DCS_FORCE_DIV(x)         (((x) & 0xFF) << 8)
#define BIT_AON_CLK_LP_GPU_CORE_IDLE_CLK_OFF             BIT(2)
#define BIT_AON_CLK_LP_GPU_CORE_DCS_FORCE                BIT(1)
#define BIT_AON_CLK_LP_GPU_CORE_DCS_EB                   BIT(0)

/* REG_AON_CLK_LP_GPU_SOC_DCS_CTRL */

#define BIT_AON_CLK_LP_GPU_SOC_DCS_IDLE_NUM(x)           (((x) & 0xFF) << 24)
#define BIT_AON_CLK_LP_GPU_SOC_DCS_DIV(x)                (((x) & 0xFF) << 16)
#define BIT_AON_CLK_LP_GPU_SOC_DCS_FORCE_DIV(x)          (((x) & 0xFF) << 8)
#define BIT_AON_CLK_LP_GPU_SOC_IDLE_CLK_OFF              BIT(2)
#define BIT_AON_CLK_LP_GPU_SOC_DCS_FORCE                 BIT(1)
#define BIT_AON_CLK_LP_GPU_SOC_DCS_EB                    BIT(0)

/* REG_AON_CLK_LP_APCPU_CLKEN_CFG */

#define BIT_AON_CLK_LP_CLK_PERIPH_AUTO_GATE              BIT(31)
#define BIT_AON_CLK_LP_CLK_PERIPH_SW_EN                  BIT(30)
#define BIT_AON_CLK_LP_CLK_GIC_AUTO_GATE                 BIT(29)
#define BIT_AON_CLK_LP_CLK_GIC_SW_EN                     BIT(28)
#define BIT_AON_CLK_LP_CLK_DEBUG_APB_AUTO_GATE           BIT(27)
#define BIT_AON_CLK_LP_CLK_DEBUG_APB_SW_EN               BIT(26)
#define BIT_AON_CLK_LP_CLK_ATB_AUTO_GATE                 BIT(25)
#define BIT_AON_CLK_LP_CLK_ATB_SW_EN                     BIT(24)
#define BIT_AON_CLK_LP_CLK_AXI_ACP_AUTO_GATE             BIT(23)
#define BIT_AON_CLK_LP_CLK_AXI_ACP_SW_EN                 BIT(22)
#define BIT_AON_CLK_LP_CLK_AXI_PERIPH_AUTO_GATE          BIT(21)
#define BIT_AON_CLK_LP_CLK_AXI_PERIPH_SW_EN              BIT(20)
#define BIT_AON_CLK_LP_CLK_ACE_AUTO_GATE                 BIT(19)
#define BIT_AON_CLK_LP_CLK_ACE_SW_EN                     BIT(18)
#define BIT_AON_CLK_LP_CLK_SCU_AUTO_GATE                 BIT(17)
#define BIT_AON_CLK_LP_CLK_SCU_SW_EN                     BIT(16)
#define BIT_AON_CLK_LP_CLK_CORE7_AUTO_GATE               BIT(15)
#define BIT_AON_CLK_LP_CLK_CORE7_SW_EN                   BIT(14)
#define BIT_AON_CLK_LP_CLK_CORE6_AUTO_GATE               BIT(13)
#define BIT_AON_CLK_LP_CLK_CORE6_SW_EN                   BIT(12)
#define BIT_AON_CLK_LP_CLK_CORE5_AUTO_GATE               BIT(11)
#define BIT_AON_CLK_LP_CLK_CORE5_SW_EN                   BIT(10)
#define BIT_AON_CLK_LP_CLK_CORE4_AUTO_GATE               BIT(9)
#define BIT_AON_CLK_LP_CLK_CORE4_SW_EN                   BIT(8)
#define BIT_AON_CLK_LP_CLK_CORE3_AUTO_GATE               BIT(7)
#define BIT_AON_CLK_LP_CLK_CORE3_SW_EN                   BIT(6)
#define BIT_AON_CLK_LP_CLK_CORE2_AUTO_GATE               BIT(5)
#define BIT_AON_CLK_LP_CLK_CORE2_SW_EN                   BIT(4)
#define BIT_AON_CLK_LP_CLK_CORE1_AUTO_GATE               BIT(3)
#define BIT_AON_CLK_LP_CLK_CORE1_SW_EN                   BIT(2)
#define BIT_AON_CLK_LP_CLK_CORE0_AUTO_GATE               BIT(1)
#define BIT_AON_CLK_LP_CLK_CORE0_SW_EN                   BIT(0)

/* REG_AON_CLK_LP_APCPU_CLKSEL_MODE */

#define BIT_AON_CLK_LP_CLK_PERIPH_SEL_IDLE_EN            BIT(11)
#define BIT_AON_CLK_LP_CLK_GIC_SEL_IDLE_EN               BIT(10)
#define BIT_AON_CLK_LP_CLK_ATB_SEL_IDLE_EN               BIT(9)
#define BIT_AON_CLK_LP_CLK_SCU_SEL_IDLE_EN               BIT(8)
#define BIT_AON_CLK_LP_CLK_CORE7_SEL_IDLE_EN             BIT(7)
#define BIT_AON_CLK_LP_CLK_CORE6_SEL_IDLE_EN             BIT(6)
#define BIT_AON_CLK_LP_CLK_CORE5_SEL_IDLE_EN             BIT(5)
#define BIT_AON_CLK_LP_CLK_CORE4_SEL_IDLE_EN             BIT(4)
#define BIT_AON_CLK_LP_CLK_CORE3_SEL_IDLE_EN             BIT(3)
#define BIT_AON_CLK_LP_CLK_CORE2_SEL_IDLE_EN             BIT(2)
#define BIT_AON_CLK_LP_CLK_CORE1_SEL_IDLE_EN             BIT(1)
#define BIT_AON_CLK_LP_CLK_CORE0_SEL_IDLE_EN             BIT(0)

/* REG_AON_CLK_LP_APCPU_IDLE_CLKSEL0 */

#define BIT_AON_CLK_LP_CLK_CORE7_SEL_IDLE(x)             (((x) & 0x7) << 28)
#define BIT_AON_CLK_LP_CLK_CORE6_SEL_IDLE(x)             (((x) & 0x7) << 24)
#define BIT_AON_CLK_LP_CLK_CORE5_SEL_IDLE(x)             (((x) & 0x7) << 20)
#define BIT_AON_CLK_LP_CLK_CORE4_SEL_IDLE(x)             (((x) & 0x7) << 16)
#define BIT_AON_CLK_LP_CLK_CORE3_SEL_IDLE(x)             (((x) & 0x7) << 12)
#define BIT_AON_CLK_LP_CLK_CORE2_SEL_IDLE(x)             (((x) & 0x7) << 8)
#define BIT_AON_CLK_LP_CLK_CORE1_SEL_IDLE(x)             (((x) & 0x7) << 4)
#define BIT_AON_CLK_LP_CLK_CORE0_SEL_IDLE(x)             (((x) & 0x7))

/* REG_AON_CLK_LP_APCPU_IDLE_CLKSEL1 */

#define BIT_AON_CLK_LP_CLK_PERIPH_SEL_IDLE(x)            (((x) & 0x3) << 12)
#define BIT_AON_CLK_LP_CLK_GIC_SEL_IDLE(x)               (((x) & 0x3) << 8)
#define BIT_AON_CLK_LP_CLK_ATB_SEL_IDLE(x)               (((x) & 0x3) << 4)
#define BIT_AON_CLK_LP_CLK_SCU_SEL_IDLE(x)               (((x) & 0x7))

/* REG_AON_CLK_LP_APCPU_CLKDIV_MODE */

#define BIT_AON_CLK_LP_CLK_PERIPH_DIV_IDLE_EN            BIT(15)
#define BIT_AON_CLK_LP_CLK_GIC_DIV_IDLE_EN               BIT(14)
#define BIT_AON_CLK_LP_CLK_DEBUG_APB_DIV_IDLE_EN         BIT(13)
#define BIT_AON_CLK_LP_CLK_ATB_DIV_IDLE_EN               BIT(12)
#define BIT_AON_CLK_LP_CLK_AXI_ACP_DIV_IDLE_EN           BIT(11)
#define BIT_AON_CLK_LP_CLK_AXI_PERIPH_DIV_IDLE_EN        BIT(10)
#define BIT_AON_CLK_LP_CLK_ACE_DIV_IDLE_EN               BIT(9)
#define BIT_AON_CLK_LP_CLK_SCU_DIV_IDLE_EN               BIT(8)
#define BIT_AON_CLK_LP_CLK_CORE7_DIV_IDLE_EN             BIT(7)
#define BIT_AON_CLK_LP_CLK_CORE6_DIV_IDLE_EN             BIT(6)
#define BIT_AON_CLK_LP_CLK_CORE5_DIV_IDLE_EN             BIT(5)
#define BIT_AON_CLK_LP_CLK_CORE4_DIV_IDLE_EN             BIT(4)
#define BIT_AON_CLK_LP_CLK_CORE3_DIV_IDLE_EN             BIT(3)
#define BIT_AON_CLK_LP_CLK_CORE2_DIV_IDLE_EN             BIT(2)
#define BIT_AON_CLK_LP_CLK_CORE1_DIV_IDLE_EN             BIT(1)
#define BIT_AON_CLK_LP_CLK_CORE0_DIV_IDLE_EN             BIT(0)

/* REG_AON_CLK_LP_APCPU_IDLE_CLKDIV0 */

#define BIT_AON_CLK_LP_CLK_CORE7_DIV_IDLE(x)             (((x) & 0x7) << 28)
#define BIT_AON_CLK_LP_CLK_CORE6_DIV_IDLE(x)             (((x) & 0x7) << 24)
#define BIT_AON_CLK_LP_CLK_CORE5_DIV_IDLE(x)             (((x) & 0x7) << 20)
#define BIT_AON_CLK_LP_CLK_CORE4_DIV_IDLE(x)             (((x) & 0x7) << 16)
#define BIT_AON_CLK_LP_CLK_CORE3_DIV_IDLE(x)             (((x) & 0x7) << 12)
#define BIT_AON_CLK_LP_CLK_CORE2_DIV_IDLE(x)             (((x) & 0x7) << 8)
#define BIT_AON_CLK_LP_CLK_CORE1_DIV_IDLE(x)             (((x) & 0x7) << 4)
#define BIT_AON_CLK_LP_CLK_CORE0_DIV_IDLE(x)             (((x) & 0x7))

/* REG_AON_CLK_LP_APCPU_IDLE_CLKDIV1 */

#define BIT_AON_CLK_LP_CLK_PERIPH_DIV_IDLE(x)            (((x) & 0x7) << 28)
#define BIT_AON_CLK_LP_CLK_GIC_DIV_IDLE(x)               (((x) & 0x7) << 24)
#define BIT_AON_CLK_LP_CLK_DEBUG_APB_DIV_IDLE(x)         (((x) & 0x7) << 20)
#define BIT_AON_CLK_LP_CLK_ATB_DIV_IDLE(x)               (((x) & 0x7) << 16)
#define BIT_AON_CLK_LP_CLK_AXI_ACP_DIV_IDLE(x)           (((x) & 0x7) << 12)
#define BIT_AON_CLK_LP_CLK_AXI_PERIPH_DIV_IDLE(x)        (((x) & 0x7) << 8)
#define BIT_AON_CLK_LP_CLK_ACE_DIV_IDLE(x)               (((x) & 0x7) << 4)
#define BIT_AON_CLK_LP_CLK_SCU_DIV_IDLE(x)               (((x) & 0x7))

/* REG_AON_CLK_LP_AP_AXI_CLK_MODE */

#define BIT_AON_CLK_LP_AP_AXI_CFG_SW_FORCE_ON            BIT(18)
#define BIT_AON_CLK_LP_AP_AXI_MATRIX_SW_FORCE_ON         BIT(17)
#define BIT_AON_CLK_LP_AP_AXI_MATRIX_MODE_SEL            BIT(16)
#define BIT_AON_CLK_LP_AP_AXI_IDLE_CLK_SEL(x)            (((x) & 0x3) << 10)
#define BIT_AON_CLK_LP_AP_AXI_IDLE_MODE_SEL              BIT(9)
#define BIT_AON_CLK_LP_AP_AXI_IDLE_EN                    BIT(8)
#define BIT_AON_CLK_LP_AP_AXI_LIGHT_AUTO_GATE            BIT(2)
#define BIT_AON_CLK_LP_AP_AXI_DOZE_AUTO_GATE             BIT(1)
#define BIT_AON_CLK_LP_AP_AXI_DEEP_AUTO_GATE             BIT(0)

/* REG_AON_CLK_LP_DISP_SYS_CLK_MODE */

#define BIT_AON_CLK_LP_DPU_IDLE_CLK_SEL(x)               (((x) & 0x3) << 8)
#define BIT_AON_CLK_LP_DPU_IDLE_EN                       BIT(0)

/* REG_AON_CLK_LP_MM_SYS_CLK_MODE */

#define BIT_AON_CLK_LP_DCAM_IF_IDLE_CLK_SEL(x)           (((x) & 0x3) << 16)
#define BIT_AON_CLK_LP_BPC_IDLE_CLK_SEL(x)               (((x) & 0x7) << 12)
#define BIT_AON_CLK_LP_ISP_IDLE_CLK_SEL(x)               (((x) & 0x7) << 8)
#define BIT_AON_CLK_LP_DCAM_IF_IDLE_EN                   BIT(2)
#define BIT_AON_CLK_LP_BPC_IDLE_EN                       BIT(1)
#define BIT_AON_CLK_LP_ISP_IDLE_EN                       BIT(0)

/* REG_AON_CLK_LP_VSP_SYS_CLK_MODE */

#define BIT_AON_CLK_LP_VSP_IDLE_CLK_SEL(x)               (((x) & 0x7) << 16)
#define BIT_AON_CLK_LP_JPG_IDLE_CLK_SEL(x)               (((x) & 0x3) << 12)
#define BIT_AON_CLK_LP_CPP_IDLE_CLK_SEL(x)               (((x) & 0x3) << 8)
#define BIT_AON_CLK_LP_VSP_IDLE_EN                       BIT(2)
#define BIT_AON_CLK_LP_JPG_IDLE_EN                       BIT(1)
#define BIT_AON_CLK_LP_CPP_IDLE_EN                       BIT(0)

/* REG_AON_CLK_LP_PRE_DIV_SLP_EN */

#define BIT_AON_CLK_LP_WTLCP_DOZE_GATE_EN                BIT(11)
#define BIT_AON_CLK_LP_PUBCP_DOZE_GATE_EN                BIT(10)
#define BIT_AON_CLK_LP_AP_DOZE_GATE_EN                   BIT(8)
#define BIT_AON_CLK_LP_WTLCP_DEEP_GATE_EN                BIT(3)
#define BIT_AON_CLK_LP_PUBCP_DEEP_GATE_EN                BIT(2)
#define BIT_AON_CLK_LP_APCPU_DEEP_GATE_EN                BIT(1)
#define BIT_AON_CLK_LP_AP_DEEP_GATE_EN                   BIT(0)

/* REG_AON_CLK_LP_APCPU_WFX_SEL_IDLE_EN */

#define BIT_AON_CLK_LP_CLK_PERIPH_SEL_WFX_IDLE_EN        BIT(11)
#define BIT_AON_CLK_LP_CLK_GIC_SEL_WFX_IDLE_EN           BIT(10)
#define BIT_AON_CLK_LP_CLK_ATB_SEL_WFX_IDLE_EN           BIT(9)
#define BIT_AON_CLK_LP_CLK_SCU_SEL_WFX_IDLE_EN           BIT(8)
#define BIT_AON_CLK_LP_CLK_CORE7_SEL_WFX_IDLE_EN         BIT(7)
#define BIT_AON_CLK_LP_CLK_CORE6_SEL_WFX_IDLE_EN         BIT(6)
#define BIT_AON_CLK_LP_CLK_CORE5_SEL_WFX_IDLE_EN         BIT(5)
#define BIT_AON_CLK_LP_CLK_CORE4_SEL_WFX_IDLE_EN         BIT(4)
#define BIT_AON_CLK_LP_CLK_CORE3_SEL_WFX_IDLE_EN         BIT(3)
#define BIT_AON_CLK_LP_CLK_CORE2_SEL_WFX_IDLE_EN         BIT(2)
#define BIT_AON_CLK_LP_CLK_CORE1_SEL_WFX_IDLE_EN         BIT(1)
#define BIT_AON_CLK_LP_CLK_CORE0_SEL_WFX_IDLE_EN         BIT(0)

/* REG_AON_CLK_LP_APCPU_WFX_DIV_IDLE_EN */

#define BIT_AON_CLK_LP_CLK_DEBUG_APB_DIV_WFX_IDLE_EN     BIT(15)
#define BIT_AON_CLK_LP_CLK_AXI_ACP_DIV_WFX_IDLE_EN       BIT(14)
#define BIT_AON_CLK_LP_CLK_AXI_PERIPH_DIV_WFX_IDLE_EN    BIT(13)
#define BIT_AON_CLK_LP_CLK_ACE_DIV_WFX_IDLE_EN           BIT(12)
#define BIT_AON_CLK_LP_CLK_PERIPH_DIV_WFX_IDLE_EN        BIT(11)
#define BIT_AON_CLK_LP_CLK_GIC_DIV_WFX_IDLE_EN           BIT(10)
#define BIT_AON_CLK_LP_CLK_ATB_DIV_WFX_IDLE_EN           BIT(9)
#define BIT_AON_CLK_LP_CLK_SCU_DIV_WFX_IDLE_EN           BIT(8)
#define BIT_AON_CLK_LP_CLK_CORE7_DIV_WFX_IDLE_EN         BIT(7)
#define BIT_AON_CLK_LP_CLK_CORE6_DIV_WFX_IDLE_EN         BIT(6)
#define BIT_AON_CLK_LP_CLK_CORE5_DIV_WFX_IDLE_EN         BIT(5)
#define BIT_AON_CLK_LP_CLK_CORE4_DIV_WFX_IDLE_EN         BIT(4)
#define BIT_AON_CLK_LP_CLK_CORE3_DIV_WFX_IDLE_EN         BIT(3)
#define BIT_AON_CLK_LP_CLK_CORE2_DIV_WFX_IDLE_EN         BIT(2)
#define BIT_AON_CLK_LP_CLK_CORE1_DIV_WFX_IDLE_EN         BIT(1)
#define BIT_AON_CLK_LP_CLK_CORE0_DIV_WFX_IDLE_EN         BIT(0)

/* REG_AON_CLK_LP_CLK_AUTO_GATE_DIV_CTRL */

#define BIT_AON_CLK_LP_ANLG_IF_SLOW_SEL(x)               (((x) & 0x7) << 8)
#define BIT_AON_CLK_LP_PUB_CFG_SLOW_SEL(x)               (((x) & 0x7) << 4)
#define BIT_AON_CLK_LP_PCLK_EN_SLOW_SEL(x)               (((x) & 0x7))

/* REG_AON_CLK_LP_CLK_AUTO_GATE_EN_CTRL0 */

#define BIT_AON_CLK_LP_IP_SLOW_EN_CROSS_TRIG             BIT(31)
#define BIT_AON_CLK_LP_IP_AUTO_EN_CROSS_TRIG             BIT(30)
#define BIT_AON_CLK_LP_IP_SLOW_EN_AUD                    BIT(29)
#define BIT_AON_CLK_LP_IP_AUTO_EN_AUD                    BIT(28)
#define BIT_AON_CLK_LP_IP_SLOW_EN_APCPU_WDG              BIT(27)
#define BIT_AON_CLK_LP_IP_AUTO_EN_APCPU_WDG              BIT(26)
#define BIT_AON_CLK_LP_IP_SLOW_EN_AP_WDG                 BIT(25)
#define BIT_AON_CLK_LP_IP_AUTO_EN_AP_WDG                 BIT(24)
#define BIT_AON_CLK_LP_IP_SLOW_EN_AP_SYST                BIT(23)
#define BIT_AON_CLK_LP_IP_AUTO_EN_AP_SYST                BIT(22)
#define BIT_AON_CLK_LP_IP_SLOW_EN_AP_INTC5               BIT(21)
#define BIT_AON_CLK_LP_IP_AUTO_EN_AP_INTC5               BIT(20)
#define BIT_AON_CLK_LP_IP_SLOW_EN_AP_INTC4               BIT(19)
#define BIT_AON_CLK_LP_IP_AUTO_EN_AP_INTC4               BIT(18)
#define BIT_AON_CLK_LP_IP_SLOW_EN_AP_INTC3               BIT(17)
#define BIT_AON_CLK_LP_IP_AUTO_EN_AP_INTC3               BIT(16)
#define BIT_AON_CLK_LP_IP_SLOW_EN_AP_INTC2               BIT(15)
#define BIT_AON_CLK_LP_IP_AUTO_EN_AP_INTC2               BIT(14)
#define BIT_AON_CLK_LP_IP_SLOW_EN_AP_INTC1               BIT(13)
#define BIT_AON_CLK_LP_IP_AUTO_EN_AP_INTC1               BIT(12)
#define BIT_AON_CLK_LP_IP_SLOW_EN_AP_INTC0               BIT(11)
#define BIT_AON_CLK_LP_IP_AUTO_EN_AP_INTC0               BIT(10)
#define BIT_AON_CLK_LP_IP_SLOW_EN_AON_TMR                BIT(9)
#define BIT_AON_CLK_LP_IP_AUTO_EN_AON_TMR                BIT(8)
#define BIT_AON_CLK_LP_IP_SLOW_EN_AON_SYST               BIT(7)
#define BIT_AON_CLK_LP_IP_AUTO_EN_AON_SYST               BIT(6)
#define BIT_AON_CLK_LP_IP_SLOW_EN_AON_BSMTMR             BIT(5)
#define BIT_AON_CLK_LP_IP_AUTO_EN_AON_BSMTMR             BIT(4)
#define BIT_AON_CLK_LP_IP_SLOW_EN_ANLG                   BIT(3)
#define BIT_AON_CLK_LP_IP_AUTO_EN_ANLG                   BIT(2)
#define BIT_AON_CLK_LP_IP_SLOW_EN_ADI                    BIT(1)
#define BIT_AON_CLK_LP_IP_AUTO_EN_ADI                    BIT(0)

/* REG_AON_CLK_LP_CLK_AUTO_GATE_EN_CTRL1 */

#define BIT_AON_CLK_LP_IP_SLOW_EN_PCP_WDG                BIT(31)
#define BIT_AON_CLK_LP_IP_AUTO_EN_PCP_WDG                BIT(30)
#define BIT_AON_CLK_LP_IP_SLOW_EN_PCP_TMR                BIT(29)
#define BIT_AON_CLK_LP_IP_AUTO_EN_PCP_TMR                BIT(28)
#define BIT_AON_CLK_LP_IP_SLOW_EN_PCP_SYST               BIT(27)
#define BIT_AON_CLK_LP_IP_AUTO_EN_PCP_SYST               BIT(26)
#define BIT_AON_CLK_LP_IP_SLOW_EN_PCP_EIC                BIT(25)
#define BIT_AON_CLK_LP_IP_AUTO_EN_PCP_EIC                BIT(24)
#define BIT_AON_CLK_LP_IP_SLOW_EN_MDAR                   BIT(23)
#define BIT_AON_CLK_LP_IP_AUTO_EN_MDAR                   BIT(22)
#define BIT_AON_CLK_LP_IP_SLOW_EN_MBOX                   BIT(21)
#define BIT_AON_CLK_LP_IP_AUTO_EN_MBOX                   BIT(20)
#define BIT_AON_CLK_LP_IP_SLOW_EN_KPD                    BIT(19)
#define BIT_AON_CLK_LP_IP_AUTO_EN_KPD                    BIT(18)
#define BIT_AON_CLK_LP_IP_SLOW_EN_INTC                   BIT(17)
#define BIT_AON_CLK_LP_IP_AUTO_EN_INTC                   BIT(16)
#define BIT_AON_CLK_LP_IP_SLOW_EN_I2C                    BIT(15)
#define BIT_AON_CLK_LP_IP_AUTO_EN_I2C                    BIT(14)
#define BIT_AON_CLK_LP_IP_SLOW_EN_GPLUS                  BIT(13)
#define BIT_AON_CLK_LP_IP_AUTO_EN_GPLUS                  BIT(12)
#define BIT_AON_CLK_LP_IP_SLOW_EN_GPIO                   BIT(11)
#define BIT_AON_CLK_LP_IP_AUTO_EN_GPIO                   BIT(10)
#define BIT_AON_CLK_LP_IP_SLOW_EN_GLBREG                 BIT(9)
#define BIT_AON_CLK_LP_IP_AUTO_EN_GLBREG                 BIT(8)
#define BIT_AON_CLK_LP_IP_SLOW_EN_EIC                    BIT(7)
#define BIT_AON_CLK_LP_IP_AUTO_EN_EIC                    BIT(6)
#define BIT_AON_CLK_LP_IP_SLOW_EN_EFUSE                  BIT(5)
#define BIT_AON_CLK_LP_IP_AUTO_EN_EFUSE                  BIT(4)
#define BIT_AON_CLK_LP_IP_SLOW_EN_DJTAG                  BIT(3)
#define BIT_AON_CLK_LP_IP_AUTO_EN_DJTAG                  BIT(2)
#define BIT_AON_CLK_LP_IP_SLOW_EN_DEF                    BIT(1)
#define BIT_AON_CLK_LP_IP_AUTO_EN_DEF                    BIT(0)

/* REG_AON_CLK_LP_CLK_AUTO_GATE_EN_CTRL2 */

#define BIT_AON_CLK_LP_IP_SLOW_EN_THM                    BIT(31)
#define BIT_AON_CLK_LP_IP_AUTO_EN_THM                    BIT(30)
#define BIT_AON_CLK_LP_IP_SLOW_EN_SPLK                   BIT(29)
#define BIT_AON_CLK_LP_IP_AUTO_EN_SPLK                   BIT(28)
#define BIT_AON_CLK_LP_IP_SLOW_EN_SLVFW                  BIT(27)
#define BIT_AON_CLK_LP_IP_AUTO_EN_SLVFW                  BIT(26)
#define BIT_AON_CLK_LP_IP_SLOW_EN_SEC_WDG                BIT(25)
#define BIT_AON_CLK_LP_IP_AUTO_EN_SEC_WDG                BIT(24)
#define BIT_AON_CLK_LP_IP_SLOW_EN_SEC_TZPC               BIT(23)
#define BIT_AON_CLK_LP_IP_AUTO_EN_SEC_TZPC               BIT(22)
#define BIT_AON_CLK_LP_IP_SLOW_EN_SEC_TMR0               BIT(21)
#define BIT_AON_CLK_LP_IP_AUTO_EN_SEC_TMR0               BIT(20)
#define BIT_AON_CLK_LP_IP_SLOW_EN_SEC_RTC                BIT(19)
#define BIT_AON_CLK_LP_IP_AUTO_EN_SEC_RTC                BIT(18)
#define BIT_AON_CLK_LP_IP_SLOW_EN_SEC_GPIO               BIT(17)
#define BIT_AON_CLK_LP_IP_AUTO_EN_SEC_GPIO               BIT(16)
#define BIT_AON_CLK_LP_IP_SLOW_EN_SEC_EIC                BIT(15)
#define BIT_AON_CLK_LP_IP_AUTO_EN_SEC_EIC                BIT(14)
#define BIT_AON_CLK_LP_IP_SLOW_EN_SCC                    BIT(13)
#define BIT_AON_CLK_LP_IP_AUTO_EN_SCC                    BIT(12)
#define BIT_AON_CLK_LP_IP_SLOW_EN_RSTCTL                 BIT(11)
#define BIT_AON_CLK_LP_IP_AUTO_EN_RSTCTL                 BIT(10)
#define BIT_AON_CLK_LP_IP_SLOW_EN_PWM2                   BIT(9)
#define BIT_AON_CLK_LP_IP_AUTO_EN_PWM2                   BIT(8)
#define BIT_AON_CLK_LP_IP_SLOW_EN_PWM1                   BIT(7)
#define BIT_AON_CLK_LP_IP_AUTO_EN_PWM1                   BIT(6)
#define BIT_AON_CLK_LP_IP_SLOW_EN_PWM0                   BIT(5)
#define BIT_AON_CLK_LP_IP_AUTO_EN_PWM0                   BIT(4)
#define BIT_AON_CLK_LP_IP_SLOW_EN_PMU                    BIT(3)
#define BIT_AON_CLK_LP_IP_AUTO_EN_PMU                    BIT(2)
#define BIT_AON_CLK_LP_IP_SLOW_EN_PIN                    BIT(1)
#define BIT_AON_CLK_LP_IP_AUTO_EN_PIN                    BIT(0)

/* REG_AON_CLK_LP_CLK_AUTO_GATE_EN_CTRL3 */

#define BIT_AON_CLK_LP_ANLG_IF_SLOW_EN                   BIT(9)
#define BIT_AON_CLK_LP_ANLG_IF_AUTO_EN                   BIT(8)
#define BIT_AON_CLK_LP_PUB_CFG_SLOW_EN                   BIT(7)
#define BIT_AON_CLK_LP_PUB_CFG_AUTO_EN                   BIT(6)
#define BIT_AON_CLK_LP_IP_SLOW_EN_DVFS                   BIT(5)
#define BIT_AON_CLK_LP_IP_AUTO_EN_DVFS                   BIT(4)
#define BIT_AON_CLK_LP_IP_SLOW_EN_VBC                    BIT(3)
#define BIT_AON_CLK_LP_IP_AUTO_EN_VBC                    BIT(2)
#define BIT_AON_CLK_LP_IP_SLOW_EN_TS                     BIT(1)
#define BIT_AON_CLK_LP_IP_AUTO_EN_TS                     BIT(0)

/* REG_AON_CLK_LP_AON_M0_LPC */

#define BIT_AON_CLK_LP_AON_M0_LP_FORCE                   BIT(17)
#define BIT_AON_CLK_LP_AON_M0_LP_EB                      BIT(16)
#define BIT_AON_CLK_LP_AON_M0_LP_NUM(x)                  (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_M1_LPC */

#define BIT_AON_CLK_LP_AON_M1_LP_FORCE                   BIT(17)
#define BIT_AON_CLK_LP_AON_M1_LP_EB                      BIT(16)
#define BIT_AON_CLK_LP_AON_M1_LP_NUM(x)                  (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_M2_LPC */

#define BIT_AON_CLK_LP_AON_M2_LP_FORCE                   BIT(17)
#define BIT_AON_CLK_LP_AON_M2_LP_EB                      BIT(16)
#define BIT_AON_CLK_LP_AON_M2_LP_NUM(x)                  (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_M3_LPC */

#define BIT_AON_CLK_LP_AON_M3_LP_FORCE                   BIT(17)
#define BIT_AON_CLK_LP_AON_M3_LP_EB                      BIT(16)
#define BIT_AON_CLK_LP_AON_M3_LP_NUM(x)                  (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_M4_LPC */

#define BIT_AON_CLK_LP_AON_M4_LP_FORCE                   BIT(17)
#define BIT_AON_CLK_LP_AON_M4_LP_EB                      BIT(16)
#define BIT_AON_CLK_LP_AON_M4_LP_NUM(x)                  (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_M5_LPC */

#define BIT_AON_CLK_LP_AON_M5_LP_FORCE                   BIT(17)
#define BIT_AON_CLK_LP_AON_M5_LP_EB                      BIT(16)
#define BIT_AON_CLK_LP_AON_M5_LP_NUM(x)                  (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_M6_LPC */

#define BIT_AON_CLK_LP_AON_M6_LP_FORCE                   BIT(17)
#define BIT_AON_CLK_LP_AON_M6_LP_EB                      BIT(16)
#define BIT_AON_CLK_LP_AON_M6_LP_NUM(x)                  (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_MAIN_LPC */

#define BIT_AON_CLK_LP_AON_MAIN_LP_FORCE                 BIT(17)
#define BIT_AON_CLK_LP_AON_MAIN_LP_EB                    BIT(16)
#define BIT_AON_CLK_LP_AON_MAIN_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_S0_LPC */

#define BIT_AON_CLK_LP_AON_S0_LP_FORCE                   BIT(17)
#define BIT_AON_CLK_LP_AON_S0_LP_EB                      BIT(16)
#define BIT_AON_CLK_LP_AON_S0_LP_NUM(x)                  (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_S1_LPC */

#define BIT_AON_CLK_LP_AON_S1_LP_FORCE                   BIT(17)
#define BIT_AON_CLK_LP_AON_S1_LP_EB                      BIT(16)
#define BIT_AON_CLK_LP_AON_S1_LP_NUM(x)                  (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_S2_LPC */

#define BIT_AON_CLK_LP_AON_S2_LP_FORCE                   BIT(17)
#define BIT_AON_CLK_LP_AON_S2_LP_EB                      BIT(16)
#define BIT_AON_CLK_LP_AON_S2_LP_NUM(x)                  (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_S3_LPC */

#define BIT_AON_CLK_LP_AON_S3_LP_FORCE                   BIT(17)
#define BIT_AON_CLK_LP_AON_S3_LP_EB                      BIT(16)
#define BIT_AON_CLK_LP_AON_S3_LP_NUM(x)                  (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_S4_LPC */

#define BIT_AON_CLK_LP_AON_S4_LP_FORCE                   BIT(17)
#define BIT_AON_CLK_LP_AON_S4_LP_EB                      BIT(16)
#define BIT_AON_CLK_LP_AON_S4_LP_NUM(x)                  (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_S5_LPC */

#define BIT_AON_CLK_LP_AON_S5_LP_FORCE                   BIT(17)
#define BIT_AON_CLK_LP_AON_S5_LP_EB                      BIT(16)
#define BIT_AON_CLK_LP_AON_S5_LP_NUM(x)                  (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_S6_LPC */

#define BIT_AON_CLK_LP_AON_S6_LP_FORCE                   BIT(17)
#define BIT_AON_CLK_LP_AON_S6_LP_EB                      BIT(16)
#define BIT_AON_CLK_LP_AON_S6_LP_NUM(x)                  (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_S8_LPC */

#define BIT_AON_CLK_LP_AON_S8_LP_FORCE                   BIT(17)
#define BIT_AON_CLK_LP_AON_S8_LP_EB                      BIT(16)
#define BIT_AON_CLK_LP_AON_S8_LP_NUM(x)                  (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_S9_LPC */

#define BIT_AON_CLK_LP_AON_S9_LP_FORCE                   BIT(17)
#define BIT_AON_CLK_LP_AON_S9_LP_EB                      BIT(16)
#define BIT_AON_CLK_LP_AON_S9_LP_NUM(x)                  (((x) & 0xFFFF))

/* REG_AON_CLK_LP_EAXI_M0_LPC */

#define BIT_AON_CLK_LP_EAXI_M0_LP_FORCE                  BIT(17)
#define BIT_AON_CLK_LP_EAXI_M0_LP_EB                     BIT(16)
#define BIT_AON_CLK_LP_EAXI_M0_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AON_CLK_LP_EAXI_MAIN_LPC */

#define BIT_AON_CLK_LP_EAXI_MAIN_LP_FORCE                BIT(17)
#define BIT_AON_CLK_LP_EAXI_MAIN_LP_EB                   BIT(16)
#define BIT_AON_CLK_LP_EAXI_MAIN_LP_NUM(x)               (((x) & 0xFFFF))

/* REG_AON_CLK_LP_EAXI_S0_LPC */

#define BIT_AON_CLK_LP_EAXI_S0_LP_FORCE                  BIT(17)
#define BIT_AON_CLK_LP_EAXI_S0_LP_EB                     BIT(16)
#define BIT_AON_CLK_LP_EAXI_S0_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AON_CLK_LP_EAXI_S1_LPC */

#define BIT_AON_CLK_LP_EAXI_S1_LP_FORCE                  BIT(17)
#define BIT_AON_CLK_LP_EAXI_S1_LP_EB                     BIT(16)
#define BIT_AON_CLK_LP_EAXI_S1_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_DAP2CPU_LPC */

#define BIT_AON_CLK_LP_DAP2APCPU_LP_EB                   BIT(16)
#define BIT_AON_CLK_LP_DAP2APCPU_LP_NUM(x)               (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_WCN2EMC_LPC */

#define BIT_AON_CLK_LP_WCN2EMC_LP_EB                     BIT(16)
#define BIT_AON_CLK_LP_WCN2EMC_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_DISP2EMC_LPC */

#define BIT_AON_CLK_LP_DISP2EMC_LP_EB                    BIT(16)
#define BIT_AON_CLK_LP_DISP2EMC_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_WTL2PUB_LPC */

#define BIT_AON_CLK_LP_WTL2PUB_LP_EB                     BIT(16)
#define BIT_AON_CLK_LP_WTL2PUB_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AON_CLK_LP_AON_WCN2PUB_LPC */

#define BIT_AON_CLK_LP_WCN2PUB_LP_EB                     BIT(16)
#define BIT_AON_CLK_LP_WCN2PUB_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AON_CLK_LP_CPU_CLUSTER_LPC_EB0 */

#define BIT_AON_CLK_LP_APCPU_ACE_S1_LP_EB                BIT(11)
#define BIT_AON_CLK_LP_APCPU_ACE_S0_LP_EB                BIT(10)
#define BIT_AON_CLK_LP_APCPU_ACE_M0_LP_EB                BIT(9)
#define BIT_AON_CLK_LP_APCPU_ACE_MAIN_LP_EB              BIT(8)
#define BIT_AON_CLK_LP_APCPU_TOP_S2_LP_EB                BIT(5)
#define BIT_AON_CLK_LP_APCPU_TOP_S1_LP_EB                BIT(4)
#define BIT_AON_CLK_LP_APCPU_TOP_S0_LP_EB                BIT(3)
#define BIT_AON_CLK_LP_APCPU_TOP_M1_LP_EB                BIT(2)
#define BIT_AON_CLK_LP_APCPU_TOP_M0_LP_EB                BIT(1)
#define BIT_AON_CLK_LP_APCPU_TOP_MAIN_LP_EB              BIT(0)

/* REG_AON_CLK_LP_CPU_CLUSTER_LPC_NUM0 */

#define BIT_AON_CLK_LP_APCPU_TOP_MTX_LP_NUM(x)           (((x) & 0xFFFF) << 16)
#define BIT_AON_CLK_LP_APCPU_ACE_MTX_LP_NUM(x)           (((x) & 0xFFFF))

/* REG_AON_CLK_LP_CPU_CLUSTER_LPC_EB1 */

#define BIT_AON_CLK_LP_GIC600_GIC_LP_EB                  BIT(5)
#define BIT_AON_CLK_LP_DBG_PDBGCLK_LP_EB                 BIT(4)
#define BIT_AON_CLK_LP_CLUSTER_GICCLK_LP_EB              BIT(3)
#define BIT_AON_CLK_LP_CLUSTER_ATCLK_LP_EB               BIT(2)
#define BIT_AON_CLK_LP_CLUSTER_PCLK_LP_EB                BIT(1)
#define BIT_AON_CLK_LP_CLUSTER_SCLK_LP_EB                BIT(0)

/* REG_AON_CLK_LP_CPU_CLUSTER_LPC_NUM1 */

#define BIT_AON_CLK_LP_CLUSTER_PCLK_LP_NUM(x)            (((x) & 0xFFFF) << 16)
#define BIT_AON_CLK_LP_CLUSTER_SCLK_LP_NUM(x)            (((x) & 0xFFFF))

/* REG_AON_CLK_LP_CPU_CLUSTER_LPC_NUM2 */

#define BIT_AON_CLK_LP_CLUSTER_ATCLK_LP_NUM(x)           (((x) & 0xFFFF) << 16)
#define BIT_AON_CLK_LP_CLUSTER_GICCLK_LP_NUM(x)          (((x) & 0xFFFF))

/* REG_AON_CLK_LP_CPU_CLUSTER_LPC_NUM3 */

#define BIT_AON_CLK_LP_DBG_PDBGCLK_LP_NUM(x)             (((x) & 0xFFFF) << 16)
#define BIT_AON_CLK_LP_GIC600_GIC_LP_NUM(x)              (((x) & 0xFFFF))

/* REG_AON_CLK_LP_SLICE_DONWTREAM_EN */

#define BIT_AON_CLK_LP_AON_EMC_DOWNSTREAM_DISABLE_EN     BIT(12)
#define BIT_AON_CLK_LP_GPU_EMC_DOWNSTREAM_DISABLE_EN     BIT(11)
#define BIT_AON_CLK_LP_DISP_EMC_DOWNSTREAM_DISABLE_EN    BIT(10)
#define BIT_AON_CLK_LP_DAP_CPU_DOWNSTREAM_DISABLE_EN     BIT(9)
#define BIT_AON_CLK_LP_APCPU_VSP_DOWNSTREAM_DISABLE_EN   BIT(8)
#define BIT_AON_CLK_LP_APCPU_MM_DOWNSTREAM_DISABLE_EN    BIT(7)
#define BIT_AON_CLK_LP_APCPU_GPU_DOWNSTREAM_DISABLE_EN   BIT(6)
#define BIT_AON_CLK_LP_APCPU_DISP_DOWNSTREAM_DISABLE_EN  BIT(5)
#define BIT_AON_CLK_LP_APCPU_EMC_DOWNSTREAM_DISABLE_EN   BIT(4)
#define BIT_AON_CLK_LP_AONS1_EMC_DOWNSTREAM_DISABLE_EN   BIT(3)
#define BIT_AON_CLK_LP_AON_DBG_DOWNSTREAM_DISABLE_EN     BIT(2)
#define BIT_AON_CLK_LP_WCN2EMC_DOWNSTREAM_DISABLE_EN     BIT(1)
#define BIT_AON_CLK_LP_WTL2EMC_DOWNSTREAM_DISABLE_EN     BIT(0)

/* REG_AON_CLK_LP_IMG_GPU_CORE_DFS0 */

#define BIT_AON_CLK_LP_GPU_CORE_DFS7(x)                  (((x) & 0xF) << 28)
#define BIT_AON_CLK_LP_GPU_CORE_DFS6(x)                  (((x) & 0xF) << 24)
#define BIT_AON_CLK_LP_GPU_CORE_DFS5(x)                  (((x) & 0xF) << 20)
#define BIT_AON_CLK_LP_GPU_CORE_DFS4(x)                  (((x) & 0xF) << 16)
#define BIT_AON_CLK_LP_GPU_CORE_DFS3(x)                  (((x) & 0xF) << 12)
#define BIT_AON_CLK_LP_GPU_CORE_DFS2(x)                  (((x) & 0xF) << 8)
#define BIT_AON_CLK_LP_GPU_CORE_DFS1(x)                  (((x) & 0xF) << 4)
#define BIT_AON_CLK_LP_GPU_CORE_DFS0(x)                  (((x) & 0xF))

/* REG_AON_CLK_LP_IMG_GPU_CORE_DFS1 */

#define BIT_AON_CLK_LP_GPU_CORE_DFS_EN                   BIT(0)

/* REG_AON_CLK_LP_IMG_GPU_SOC_DFS0 */

#define BIT_AON_CLK_LP_GPU_SOC_DFS7(x)                   (((x) & 0xF) << 28)
#define BIT_AON_CLK_LP_GPU_SOC_DFS6(x)                   (((x) & 0xF) << 24)
#define BIT_AON_CLK_LP_GPU_SOC_DFS5(x)                   (((x) & 0xF) << 20)
#define BIT_AON_CLK_LP_GPU_SOC_DFS4(x)                   (((x) & 0xF) << 16)
#define BIT_AON_CLK_LP_GPU_SOC_DFS3(x)                   (((x) & 0xF) << 12)
#define BIT_AON_CLK_LP_GPU_SOC_DFS2(x)                   (((x) & 0xF) << 8)
#define BIT_AON_CLK_LP_GPU_SOC_DFS1(x)                   (((x) & 0xF) << 4)
#define BIT_AON_CLK_LP_GPU_SOC_DFS0(x)                   (((x) & 0xF))

/* REG_AON_CLK_LP_IMG_GPU_SOC_DFS1 */

#define BIT_AON_CLK_LP_GPU_SOC_DFS_EN                    BIT(0)


#endif /* AON_CLK_LP_H */

