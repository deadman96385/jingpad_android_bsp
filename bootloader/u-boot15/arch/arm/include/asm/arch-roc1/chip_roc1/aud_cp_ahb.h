/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-18 10:54:21
 *
 */


#ifndef AUD_CP_AHB_H
#define AUD_CP_AHB_H

#define CTL_BASE_AUD_CP_AHB 0x015E0000


#define REG_AUD_CP_AHB_MODULE_EB0_STS         ( CTL_BASE_AUD_CP_AHB + 0x0000 )
#define REG_AUD_CP_AHB_MODULE_EB1_STS         ( CTL_BASE_AUD_CP_AHB + 0x0004 )
#define REG_AUD_CP_AHB_MODULE_RST0_STS        ( CTL_BASE_AUD_CP_AHB + 0x0008 )
#define REG_AUD_CP_AHB_BUS_CTRL               ( CTL_BASE_AUD_CP_AHB + 0x000C )
#define REG_AUD_CP_AHB_ACC_AUTO               ( CTL_BASE_AUD_CP_AHB + 0x0010 )
#define REG_AUD_CP_AHB_M_S_PUB_FRC_LSLP       ( CTL_BASE_AUD_CP_AHB + 0x0014 )
#define REG_AUD_CP_AHB_AHB_ARCH_EB            ( CTL_BASE_AUD_CP_AHB + 0x0018 )
#define REG_AUD_CP_AHB_CORE_SLEEP             ( CTL_BASE_AUD_CP_AHB + 0x001C )
#define REG_AUD_CP_AHB_SYS_SLP_EN             ( CTL_BASE_AUD_CP_AHB + 0x0020 )
#define REG_AUD_CP_AHB_MCACHE_CTRL            ( CTL_BASE_AUD_CP_AHB + 0x0024 )
#define REG_AUD_CP_AHB_MCU_STATUS             ( CTL_BASE_AUD_CP_AHB + 0x0028 )
#define REG_AUD_CP_AHB_ID2QOS_AR_0            ( CTL_BASE_AUD_CP_AHB + 0x002C )
#define REG_AUD_CP_AHB_ID2QOS_AR_1            ( CTL_BASE_AUD_CP_AHB + 0x0030 )
#define REG_AUD_CP_AHB_ID2QOS_AW_0            ( CTL_BASE_AUD_CP_AHB + 0x0034 )
#define REG_AUD_CP_AHB_ID2QOS_AW_1            ( CTL_BASE_AUD_CP_AHB + 0x0038 )
#define REG_AUD_CP_AHB_EXT_ACC_AUD_SEL        ( CTL_BASE_AUD_CP_AHB + 0x003C )
#define REG_AUD_CP_AHB_AUD_RESERVED           ( CTL_BASE_AUD_CP_AHB + 0x0040 )
#define REG_AUD_CP_AHB_LP_EB_AUDCP            ( CTL_BASE_AUD_CP_AHB + 0x0044 )
#define REG_AUD_CP_AHB_ACTIVE_SYNC_SEL_AUDCP  ( CTL_BASE_AUD_CP_AHB + 0x0048 )
#define REG_AUD_CP_AHB_AXILP_NUM              ( CTL_BASE_AUD_CP_AHB + 0x004C )
#define REG_AUD_CP_AHB_AWQOS                  ( CTL_BASE_AUD_CP_AHB + 0x0050 )
#define REG_AUD_CP_AHB_ARQOS                  ( CTL_BASE_AUD_CP_AHB + 0x0054 )
#define REG_AUD_CP_AHB_M_S_PUB_CTL_PERI       ( CTL_BASE_AUD_CP_AHB + 0x0058 )
#define REG_AUD_CP_AHB_M_S_FRC_DOZE           ( CTL_BASE_AUD_CP_AHB + 0x005C )
#define REG_AUD_CP_AHB_M_S_PUB_FRC_DSLP       ( CTL_BASE_AUD_CP_AHB + 0x0060 )
#define REG_AUD_CP_AHB_AUD_BRIDGE_DEBUG_SIG   ( CTL_BASE_AUD_CP_AHB + 0x0064 )
#define REG_AUD_CP_AHB_AUD_PROT_SEL           ( CTL_BASE_AUD_CP_AHB + 0x0068 )
#define REG_AUD_CP_AHB_AUD_BRIDGE_STATE       ( CTL_BASE_AUD_CP_AHB + 0x006C )
#define REG_AUD_CP_AHB_AUD_BRIDGE_CTL         ( CTL_BASE_AUD_CP_AHB + 0x0070 )
#define REG_AUD_CP_AHB_M_AXCACHE_CTL          ( CTL_BASE_AUD_CP_AHB + 0x0074 )
#define REG_AUD_CP_AHB_DSP_DMA_INT_CLEAR      ( CTL_BASE_AUD_CP_AHB + 0x0078 )
#define REG_AUD_CP_AHB_DSP_PSU_STA            ( CTL_BASE_AUD_CP_AHB + 0x007C )
#define REG_AUD_CP_AHB_FORCE_DMA_BUSY         ( CTL_BASE_AUD_CP_AHB + 0x0080 )
#define REG_AUD_CP_AHB_WAKEUP_EN_INT_H        ( CTL_BASE_AUD_CP_AHB + 0x0084 )
#define REG_AUD_CP_AHB_WAKEUP_EN_INT_L        ( CTL_BASE_AUD_CP_AHB + 0x0088 )
#define REG_AUD_CP_AHB_DSP_L2CC_CTRL          ( CTL_BASE_AUD_CP_AHB + 0x008C )
#define REG_AUD_CP_AHB_MTX_QOS_THD            ( CTL_BASE_AUD_CP_AHB + 0x0090 )
#define REG_AUD_CP_AHB_FREQ_FRC_ON_CTRL       ( CTL_BASE_AUD_CP_AHB + 0x0094 )
#define REG_AUD_CP_AHB_FREQ_FRC_OFF_CTRL      ( CTL_BASE_AUD_CP_AHB + 0x0098 )
#define REG_AUD_CP_AHB_DBG_DUMMG_REG          ( CTL_BASE_AUD_CP_AHB + 0x009C )
#define REG_AUD_CP_AHB_DVFS_CTRL              ( CTL_BASE_AUD_CP_AHB + 0x00A0 )
#define REG_AUD_CP_AHB_CGM_AUTO_EN            ( CTL_BASE_AUD_CP_AHB + 0x00A4 )
#define REG_AUD_CP_AHB_BUS_CLK_CTRL           ( CTL_BASE_AUD_CP_AHB + 0x00A8 )
#define REG_AUD_CP_AHB_LPC_SYNC_SEL           ( CTL_BASE_AUD_CP_AHB + 0x00AC )
#define REG_AUD_CP_AHB_BUS_MON_CTRL           ( CTL_BASE_AUD_CP_AHB + 0x00B0 )
#define REG_AUD_CP_AHB_SYS_DBG_BUS            ( CTL_BASE_AUD_CP_AHB + 0x00B4 )
#define REG_AUD_CP_AHB_LPC_PU_NUM0            ( CTL_BASE_AUD_CP_AHB + 0x00B8 )
#define REG_AUD_CP_AHB_LPC_PU_NUM1            ( CTL_BASE_AUD_CP_AHB + 0x00BC )
#define REG_AUD_CP_AHB_LPC_PU_NUM2            ( CTL_BASE_AUD_CP_AHB + 0x00C0 )
#define REG_AUD_CP_AHB_LPC_PU_NUM3            ( CTL_BASE_AUD_CP_AHB + 0x00C4 )

/* REG_AUD_CP_AHB_MODULE_EB0_STS */

#define BIT_AUD_CP_AHB_DVFS_ASHB_EB                      BIT(23)
#define BIT_AUD_CP_AHB_TMR_26M_EB                        BIT(22)
#define BIT_AUD_CP_AHB_VBC_24M_EB                        BIT(21)
#define BIT_AUD_CP_AHB_AUDIF_CKG_AUTO_EN                 BIT(20)
#define BIT_AUD_CP_AHB_AUD_EB                            BIT(19)
#define BIT_AUD_CP_AHB_DMA_CP_ASHB_EB                    BIT(18)
#define BIT_AUD_CP_AHB_DMA_AP_ASHB_EB                    BIT(17)
#define BIT_AUD_CP_AHB_ICU_EB                            BIT(16)
#define BIT_AUD_CP_AHB_SPINLOCK_EB                       BIT(15)
#define BIT_AUD_CP_AHB_VBC_EB                            BIT(14)
#define BIT_AUD_CP_AHB_VBCIFD_EB                         BIT(13)
#define BIT_AUD_CP_AHB_MCDT_EB                           BIT(12)
#define BIT_AUD_CP_AHB_SRC48K_EB                         BIT(10)
#define BIT_AUD_CP_AHB_DMA_AP_EB                         BIT(6)
#define BIT_AUD_CP_AHB_DMA_CP_EB                         BIT(5)
#define BIT_AUD_CP_AHB_UART_EB                           BIT(4)
#define BIT_AUD_CP_AHB_IIS3_EB                           BIT(3)
#define BIT_AUD_CP_AHB_IIS2_EB                           BIT(2)
#define BIT_AUD_CP_AHB_IIS1_EB                           BIT(1)
#define BIT_AUD_CP_AHB_IIS0_EB                           BIT(0)

/* REG_AUD_CP_AHB_MODULE_EB1_STS */


/* REG_AUD_CP_AHB_MODULE_RST0_STS */

#define BIT_AUD_CP_AHB_DVFS_SOFT_RST                     BIT(26)
#define BIT_AUD_CP_AHB_AUD_SOFT_RST                      BIT(25)
#define BIT_AUD_CP_AHB_UART_SOFT_RST                     BIT(16)
#define BIT_AUD_CP_AHB_IIS3_SOFT_RST                     BIT(15)
#define BIT_AUD_CP_AHB_IIS2_SOFT_RST                     BIT(14)
#define BIT_AUD_CP_AHB_IIS1_SOFT_RST                     BIT(13)
#define BIT_AUD_CP_AHB_IIS0_SOFT_RST                     BIT(12)
#define BIT_AUD_CP_AHB_DMA_CP_SOFT_RST                   BIT(11)
#define BIT_AUD_CP_AHB_SPINLOCK_SOFT_RST                 BIT(10)
#define BIT_AUD_CP_AHB_VBC_SOFT_RST                      BIT(9)
#define BIT_AUD_CP_AHB_VBCIFD_SOFT_RST                   BIT(8)
#define BIT_AUD_CP_AHB_MCDT_SOFT_RST                     BIT(7)
#define BIT_AUD_CP_AHB_SRC48K_SOFT_RST                   BIT(5)
#define BIT_AUD_CP_AHB_DMA_AP_SOFT_RST                   BIT(1)
#define BIT_AUD_CP_AHB_VBC_24M_SOFT_RST                  BIT(0)

/* REG_AUD_CP_AHB_BUS_CTRL */


/* REG_AUD_CP_AHB_ACC_AUTO */


/* REG_AUD_CP_AHB_M_S_PUB_FRC_LSLP */
//                   light sleep control force
//                   DMA_CLK_EN-> M_S_PUB_FRC_LSLP

#define BIT_AUD_CP_AHB_SLAVE0_PUB0_FRC_LSLP              BIT(16)
#define BIT_AUD_CP_AHB_MASTER4_PUB0_FRC_LSLP             BIT(14)
#define BIT_AUD_CP_AHB_MASTER3_PUB0_FRC_LSLP             BIT(13)
#define BIT_AUD_CP_AHB_MASTER2_PUB0_FRC_LSLP             BIT(12)
#define BIT_AUD_CP_AHB_MASTER1_PUB0_FRC_LSLP             BIT(11)
#define BIT_AUD_CP_AHB_MASTER0_PUB0_FRC_LSLP             BIT(10)
#define BIT_AUD_CP_AHB_DMA_CHN2_GRP2_LSLP_EN             BIT(9)
#define BIT_AUD_CP_AHB_DMA_CHN2_GRP1_LSLP_EN             BIT(8)
#define BIT_AUD_CP_AHB_AUD_DSP_CORE_FRC_SLEEP            BIT(7)
#define BIT_AUD_CP_AHB_PMU_CPDMA_FRC_SLP                 BIT(3)
#define BIT_AUD_CP_AHB_PMU_APDMA_FRC_SLP                 BIT(2)

/* REG_AUD_CP_AHB_AHB_ARCH_EB */

#define BIT_AUD_CP_AHB_AHB_ARCH_EB                       BIT(0)

/* REG_AUD_CP_AHB_CORE_SLEEP */

#define BIT_AUD_CP_AHB_DSP_CORE_SLEEP                    BIT(0)

/* REG_AUD_CP_AHB_SYS_SLP_EN */

#define BIT_AUD_CP_AHB_DSP_SYS_SLEEP_EN                  BIT(0)

/* REG_AUD_CP_AHB_MCACHE_CTRL */

#define BIT_AUD_CP_AHB_MCACHE_STRAP_POST_NUM(x)          (((x) & 0xF) << 4)
#define BIT_AUD_CP_AHB_MCACHE_STRAP_PRE_NUM(x)           (((x) & 0xF))

/* REG_AUD_CP_AHB_MCU_STATUS */

#define BIT_AUD_CP_AHB_MCU_STATUS(x)                     (((x) & 0xFFF))

/* REG_AUD_CP_AHB_ID2QOS_AR_0 */


/* REG_AUD_CP_AHB_ID2QOS_AR_1 */


/* REG_AUD_CP_AHB_ID2QOS_AW_0 */


/* REG_AUD_CP_AHB_ID2QOS_AW_1 */


/* REG_AUD_CP_AHB_EXT_ACC_AUD_SEL */

#define BIT_AUD_CP_AHB_AUD_IIS2_EXT_SEL                  BIT(2)
#define BIT_AUD_CP_AHB_AUD_IIS1_EXT_SEL                  BIT(1)
#define BIT_AUD_CP_AHB_AUD_IIS0_EXT_SEL                  BIT(0)

/* REG_AUD_CP_AHB_AUD_RESERVED */

#define BIT_AUD_CP_AHB_HIGH_RESERVED(x)                  (((x) & 0xFFFF) << 16)
#define BIT_AUD_CP_AHB_LOW_RESERVED(x)                   (((x) & 0xFFFF))

/* REG_AUD_CP_AHB_LP_EB_AUDCP */

#define BIT_AUD_CP_AHB_LP_AUD_CP_MTX_EB_S7               BIT(15)
#define BIT_AUD_CP_AHB_LP_AUD_CP_MTX_EB_ASYNC_BRIDGE     BIT(14)
#define BIT_AUD_CP_AHB_LP_AUD_CP_MTX_EB_S6               BIT(13)
#define BIT_AUD_CP_AHB_LP_AUD_CP_MTX_EB_S5               BIT(12)
#define BIT_AUD_CP_AHB_LP_AUD_CP_MTX_EB_S4               BIT(11)
#define BIT_AUD_CP_AHB_LP_AUD_CP_MTX_EB_S3               BIT(10)
#define BIT_AUD_CP_AHB_LP_AUD_CP_MTX_EB_S2               BIT(9)
#define BIT_AUD_CP_AHB_LP_AUD_CP_MTX_EB_S1               BIT(8)
#define BIT_AUD_CP_AHB_LP_AUD_CP_MTX_EB_S0               BIT(7)
#define BIT_AUD_CP_AHB_LP_AUD_CP_MTX_EB_MAIN             BIT(6)
#define BIT_AUD_CP_AHB_LP_AUD_CP_MTX_EB_M4               BIT(4)
#define BIT_AUD_CP_AHB_LP_AUD_CP_MTX_EB_M3               BIT(3)
#define BIT_AUD_CP_AHB_LP_AUD_CP_MTX_EB_M2               BIT(2)
#define BIT_AUD_CP_AHB_LP_AUD_CP_MTX_EB_M1               BIT(1)
#define BIT_AUD_CP_AHB_LP_AUD_CP_MTX_EB_M0               BIT(0)

/* REG_AUD_CP_AHB_ACTIVE_SYNC_SEL_AUDCP */


/* REG_AUD_CP_AHB_AXILP_NUM */

#define BIT_AUD_CP_AHB_LP_AUD_CP_MTX_NUM(x)              (((x) & 0xFFFF))

/* REG_AUD_CP_AHB_AWQOS */
//                   awqos_m1
//                   awqos_m2
//                   awqos_m3
//                   awqos_m4
//                   
//                   awqos_s0
//                   awqos_s1

#define BIT_AUD_CP_AHB_AWQOS_M0(x)                       (((x) & 0xF) << 20)
#define BIT_AUD_CP_AHB_AWQOS_M1(x)                       (((x) & 0xF) << 16)
#define BIT_AUD_CP_AHB_AWQOS_M2(x)                       (((x) & 0xF) << 12)
#define BIT_AUD_CP_AHB_AWQOS_M4(x)                       (((x) & 0xF) << 4)

/* REG_AUD_CP_AHB_ARQOS */
//                   arqos_m1
//                   arqos_m2
//                   arqos_m3
//                   arqos_m4
//                   
//                   arqos_s0
//                   arqos_s1

#define BIT_AUD_CP_AHB_ARQOS_M0(x)                       (((x) & 0xF) << 20)
#define BIT_AUD_CP_AHB_ARQOS_M1(x)                       (((x) & 0xF) << 16)
#define BIT_AUD_CP_AHB_ARQOS_M2(x)                       (((x) & 0xF) << 12)
#define BIT_AUD_CP_AHB_ARQOS_M4(x)                       (((x) & 0xF) << 4)

/* REG_AUD_CP_AHB_M_S_PUB_CTL_PERI */

#define BIT_AUD_CP_AHB_PERI_FRC_OFF                      BIT(2)
#define BIT_AUD_CP_AHB_PERI_FRC_ON                       BIT(1)

/* REG_AUD_CP_AHB_M_S_FRC_DOZE */


/* REG_AUD_CP_AHB_M_S_PUB_FRC_DSLP */

#define BIT_AUD_CP_AHB_SLAVE0_PUB0_FRC_DSLP              BIT(9)
#define BIT_AUD_CP_AHB_DMA_CHN2_GRP2_FRC_DSLP            BIT(8)
#define BIT_AUD_CP_AHB_DMA_CHN2_GRP1_FRC_DSLP            BIT(7)
#define BIT_AUD_CP_AHB_MASTER4_PUB0_FRC_DSLP             BIT(4)
#define BIT_AUD_CP_AHB_MASTER3_PUB0_FRC_DSLP             BIT(3)
#define BIT_AUD_CP_AHB_MASTER2_PUB0_FRC_DSLP             BIT(2)
#define BIT_AUD_CP_AHB_MASTER1_PUB0_FRC_DSLP             BIT(1)
#define BIT_AUD_CP_AHB_MASTER0_PUB0_FRC_DSLP             BIT(0)

/* REG_AUD_CP_AHB_AUD_BRIDGE_DEBUG_SIG */

#define BIT_AUD_CP_AHB_AUD_BRIDGE_DEBUG_SIGNAL_W(x)      (((x) & 0xFFFFFFFF))

/* REG_AUD_CP_AHB_AUD_PROT_SEL */

#define BIT_AUD_CP_AHB_DMA_CP_PROT(x)                    (((x) & 0xF) << 4)
#define BIT_AUD_CP_AHB_DMA_AP_PROT(x)                    (((x) & 0xF))

/* REG_AUD_CP_AHB_AUD_BRIDGE_STATE */

#define BIT_AUD_CP_AHB_AUD_BRIDGE_AXI_DETECTOR_OVERFLOW  BIT(1)
#define BIT_AUD_CP_AHB_AUD_BRIDGE_TRANS_IDLE             BIT(0)

/* REG_AUD_CP_AHB_AUD_BRIDGE_CTL */

#define BIT_AUD_CP_AHB_AUD_BRIDGE_FIFO_AF_LVL_AW_CH(x)   (((x) & 0x7) << 27)
#define BIT_AUD_CP_AHB_AUD_BRIDGE_FIFO_AF_LVL_W_CH(x)    (((x) & 0x7) << 24)
#define BIT_AUD_CP_AHB_AUD_BRIDGE_FIFO_AF_LVL_B_CH(x)    (((x) & 0x7) << 21)
#define BIT_AUD_CP_AHB_AUD_BRIDGE_FIFO_AF_LVL_AR_CH(x)   (((x) & 0x7) << 18)
#define BIT_AUD_CP_AHB_AUD_BRIDGE_FIFO_AF_LVL_R_CH(x)    (((x) & 0x7) << 15)
#define BIT_AUD_CP_AHB_AUD_BRIDGE_FIFO_AE_LVL_AW_CH(x)   (((x) & 0x7) << 12)
#define BIT_AUD_CP_AHB_AUD_BRIDGE_FIFO_AE_LVL_W_CH(x)    (((x) & 0x7) << 9)
#define BIT_AUD_CP_AHB_AUD_BRIDGE_FIFO_AE_LVL_B_CH(x)    (((x) & 0x7) << 6)
#define BIT_AUD_CP_AHB_AUD_BRIDGE_FIFO_AE_LVL_AR_CH(x)   (((x) & 0x7) << 3)
#define BIT_AUD_CP_AHB_AUD_BRIDGE_FIFO_AE_LVL_R_CH(x)    (((x) & 0x7))

/* REG_AUD_CP_AHB_M_AXCACHE_CTL */

#define BIT_AUD_CP_AHB_ARCACHE_SRC_CFG(x)                (((x) & 0xF) << 20)
#define BIT_AUD_CP_AHB_AWCACHE_SRC_CFG(x)                (((x) & 0xF) << 16)
#define BIT_AUD_CP_AHB_ARCACHE_DMA_CP_CFG(x)             (((x) & 0xF) << 12)
#define BIT_AUD_CP_AHB_AWCACHE_DMA_CP_CFG(x)             (((x) & 0xF) << 8)
#define BIT_AUD_CP_AHB_ARCACHE_DMA_CFG(x)                (((x) & 0xF) << 4)
#define BIT_AUD_CP_AHB_AWCACHE_DMA_CFG(x)                (((x) & 0xF))

/* REG_AUD_CP_AHB_DSP_DMA_INT_CLEAR */

#define BIT_AUD_CP_AHB_CEVA_PDMA_IACKN                   BIT(1)
#define BIT_AUD_CP_AHB_CEVA_DDMA_IACK                    BIT(0)

/* REG_AUD_CP_AHB_DSP_PSU_STA */

#define BIT_AUD_CP_AHB_TL42X_PSU_SYS_PSHTDWN_R(x)        (((x) & 0x1FF) << 14)
#define BIT_AUD_CP_AHB_TL42X_PSU_PSHTDWN_R(x)            (((x) & 0x7FF) << 3)
#define BIT_AUD_CP_AHB_TL42X_PSU_CORE_IDLE_R             BIT(2)
#define BIT_AUD_CP_AHB_TL42X_PSU_DSP_IDLE_R              BIT(1)
#define BIT_AUD_CP_AHB_TL42X_PSU_CORE_WAIT_R             BIT(0)

/* REG_AUD_CP_AHB_FORCE_DMA_BUSY */

#define BIT_AUD_CP_AHB_FORCE_DMA_CP_BUSY                 BIT(1)
#define BIT_AUD_CP_AHB_FORCE_DMA_AP_BUSY                 BIT(0)

/* REG_AUD_CP_AHB_WAKEUP_EN_INT_H */

#define BIT_AUD_CP_AHB_WAKEUP_EN_INT_H(x)                (((x) & 0xFFFF))

/* REG_AUD_CP_AHB_WAKEUP_EN_INT_L */

#define BIT_AUD_CP_AHB_WAKEUP_EN_INT_L(x)                (((x) & 0xFFFFFFFF))

/* REG_AUD_CP_AHB_DSP_L2CC_CTRL */

#define BIT_AUD_CP_AHB_DSP_L2CC_ENDIAN                   BIT(1)
#define BIT_AUD_CP_AHB_DSP_L2CC_DBG_LIMIT                BIT(0)

/* REG_AUD_CP_AHB_MTX_QOS_THD */

#define BIT_AUD_CP_AHB_ARQOS_THRESHOLD(x)                (((x) & 0xF) << 4)
#define BIT_AUD_CP_AHB_AWQOS_THRESHOLD(x)                (((x) & 0xF))

/* REG_AUD_CP_AHB_FREQ_FRC_ON_CTRL */

#define BIT_AUD_CP_AHB_AUDCP_AUTO_FREQ_DE                BIT(11)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_ON_FUNC_M4       BIT(10)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_ON_FUNC_M2       BIT(9)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_ON_FUNC_M0_1     BIT(8)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_ON_FUNC_M0_0     BIT(7)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_ON_MTX_MAIN      BIT(6)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_ON_MTX_M4        BIT(5)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_ON_MTX_M3        BIT(4)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_ON_MTX_M2        BIT(3)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_ON_MTX_M1        BIT(2)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_ON_MTX_M0        BIT(1)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_EB                   BIT(0)

/* REG_AUD_CP_AHB_FREQ_FRC_OFF_CTRL */

#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_OFF_FUNC_M4      BIT(9)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_OFF_FUNC_M2      BIT(8)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_OFF_FUNC_M0_1    BIT(7)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_OFF_FUNC_M0_0    BIT(6)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_OFF_MTX_MAIN     BIT(5)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_OFF_MTX_M4       BIT(4)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_OFF_MTX_M3       BIT(3)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_OFF_MTX_M2       BIT(2)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_OFF_MTX_M1       BIT(1)
#define BIT_AUD_CP_AHB_AUTO_FREQ_DE_FRC_OFF_MTX_M0       BIT(0)

/* REG_AUD_CP_AHB_DBG_DUMMG_REG */

#define BIT_AUD_CP_AHB_DBG_DUMMG_REG(x)                  (((x) & 0xFFFFFFFF))

/* REG_AUD_CP_AHB_DVFS_CTRL */

#define BIT_AUD_CP_AHB_CGM_DVFS_ROOT_AUTO_GATE_EN        BIT(0)

/* REG_AUD_CP_AHB_CGM_AUTO_EN */

#define BIT_AUD_CP_AHB_DISABLE_CGM_MASTER_2_SLAVE7       BIT(24)
#define BIT_AUD_CP_AHB_DISABLE_CGM_MASTER_2_SLAVE6       BIT(23)
#define BIT_AUD_CP_AHB_DISABLE_CGM_MASTER_2_SLAVE5       BIT(22)
#define BIT_AUD_CP_AHB_DISABLE_CGM_MASTER_2_SLAVE4       BIT(21)
#define BIT_AUD_CP_AHB_DISABLE_CGM_MASTER_2_SLAVE3       BIT(20)
#define BIT_AUD_CP_AHB_DISABLE_CGM_MASTER_2_SLAVE2       BIT(19)
#define BIT_AUD_CP_AHB_DISABLE_CGM_MASTER_2_SLAVE1       BIT(18)
#define BIT_AUD_CP_AHB_DISABLE_CGM_MASTER_2_SLAVE0       BIT(17)
#define BIT_AUD_CP_AHB_ASYNC_BRIDGE_AUTO_GATE_EN         BIT(16)
#define BIT_AUD_CP_AHB_CGM_MTX_S7_AUTO_GATE_EN           BIT(13)
#define BIT_AUD_CP_AHB_CGM_MTX_S6_AUTO_GATE_EN           BIT(12)
#define BIT_AUD_CP_AHB_CGM_MTX_S5_AUTO_GATE_EN           BIT(11)
#define BIT_AUD_CP_AHB_CGM_MTX_S4_AUTO_GATE_EN           BIT(10)
#define BIT_AUD_CP_AHB_CGM_MTX_S3_AUTO_GATE_EN           BIT(9)
#define BIT_AUD_CP_AHB_CGM_MTX_S2_AUTO_GATE_EN           BIT(8)
#define BIT_AUD_CP_AHB_CGM_MTX_S1_AUTO_GATE_EN           BIT(7)
#define BIT_AUD_CP_AHB_CGM_MTX_S0_AUTO_GATE_EN           BIT(6)
#define BIT_AUD_CP_AHB_CGM_MTX_MAIN_AUTO_GATE_EN         BIT(5)
#define BIT_AUD_CP_AHB_CGM_MTX_M4_AUTO_GATE_EN           BIT(4)
#define BIT_AUD_CP_AHB_CGM_MTX_M3_AUTO_GATE_EN           BIT(3)
#define BIT_AUD_CP_AHB_CGM_MTX_M2_AUTO_GATE_EN           BIT(2)
#define BIT_AUD_CP_AHB_CGM_MTX_M1_AUTO_GATE_EN           BIT(1)
#define BIT_AUD_CP_AHB_CGM_MTX_M0_AUTO_GATE_EN           BIT(0)

/* REG_AUD_CP_AHB_BUS_CLK_CTRL */

#define BIT_AUD_CP_AHB_DVFS_2_AHB_BYPASS                 BIT(13)
#define BIT_AUD_CP_AHB_PCLK_S4_EN_AUTO                   BIT(12)
#define BIT_AUD_CP_AHB_DSP_CORE_CLK_EB                   BIT(11)
#define BIT_AUD_CP_AHB_DSP_APB_CLK_EB                    BIT(10)
#define BIT_AUD_CP_AHB_DSP_AHB_CLK_EB                    BIT(9)
#define BIT_AUD_CP_AHB_DSP_AXI_CLK_EB                    BIT(8)
#define BIT_AUD_CP_AHB_FRC_CLK_CORE_EN                   BIT(7)
#define BIT_AUD_CP_AHB_FRC_CLK_APB_EN                    BIT(6)
#define BIT_AUD_CP_AHB_FRC_CLK_AHB_EN                    BIT(5)
#define BIT_AUD_CP_AHB_FRC_CLK_AXI_EN                    BIT(4)
#define BIT_AUD_CP_AHB_CLK_CORE_AUTO_GATE_EN             BIT(3)
#define BIT_AUD_CP_AHB_CLK_APB_AUTO_GATE_EN              BIT(2)
#define BIT_AUD_CP_AHB_CLK_AHB_AUTO_GATE_EN              BIT(1)
#define BIT_AUD_CP_AHB_CLK_AXI_AUTO_GATE_EN              BIT(0)

/* REG_AUD_CP_AHB_LPC_SYNC_SEL */

#define BIT_AUD_CP_AHB_CSYSACK_SYNC_SEL_M1               BIT(3)
#define BIT_AUD_CP_AHB_CACTIVE_SYNC_SEL_M1               BIT(2)
#define BIT_AUD_CP_AHB_CSYSACK_SYNC_SEL_M0               BIT(1)
#define BIT_AUD_CP_AHB_CACTIVE_SYNC_SEL_M0               BIT(0)

/* REG_AUD_CP_AHB_BUS_MON_CTRL */

#define BIT_AUD_CP_AHB_BUSMON_4_EB                       BIT(3)
#define BIT_AUD_CP_AHB_BUSMON_3_EB                       BIT(2)
#define BIT_AUD_CP_AHB_BUSMON_2_EB                       BIT(1)
#define BIT_AUD_CP_AHB_BUSMON_1_EB                       BIT(0)

/* REG_AUD_CP_AHB_SYS_DBG_BUS */

#define BIT_AUD_CP_AHB_SYS_DBG_BUS(x)                    (((x) & 0xFFFFFFFF))

/* REG_AUD_CP_AHB_LPC_PU_NUM0 */

#define BIT_AUD_CP_AHB_PU_NUM_M0(x)                      (((x) & 0xFF) << 24)
#define BIT_AUD_CP_AHB_PU_NUM_M1(x)                      (((x) & 0xFF) << 16)
#define BIT_AUD_CP_AHB_PU_NUM_M2(x)                      (((x) & 0xFF) << 8)
#define BIT_AUD_CP_AHB_PU_NUM_M3(x)                      (((x) & 0xFF))

/* REG_AUD_CP_AHB_LPC_PU_NUM1 */

#define BIT_AUD_CP_AHB_PU_NUM_M4(x)                      (((x) & 0xFF) << 24)
#define BIT_AUD_CP_AHB_PU_NUM_MAIN(x)                    (((x) & 0xFF) << 16)
#define BIT_AUD_CP_AHB_PU_NUM_S0(x)                      (((x) & 0xFF) << 8)
#define BIT_AUD_CP_AHB_PU_NUM_S1(x)                      (((x) & 0xFF))

/* REG_AUD_CP_AHB_LPC_PU_NUM2 */

#define BIT_AUD_CP_AHB_PU_NUM_S2(x)                      (((x) & 0xFF) << 24)
#define BIT_AUD_CP_AHB_PU_NUM_S3(x)                      (((x) & 0xFF) << 16)
#define BIT_AUD_CP_AHB_PU_NUM_S4(x)                      (((x) & 0xFF) << 8)
#define BIT_AUD_CP_AHB_PU_NUM_S5(x)                      (((x) & 0xFF))

/* REG_AUD_CP_AHB_LPC_PU_NUM3 */

#define BIT_AUD_CP_AHB_PU_NUM_S6(x)                      (((x) & 0xFF) << 16)
#define BIT_AUD_CP_AHB_PU_NUM_S7(x)                      (((x) & 0xFF) << 8)
#define BIT_AUD_CP_AHB_PU_NUM_ASYNC_BRIDGE(x)            (((x) & 0xFF))


#endif /* AUD_CP_AHB_H */


