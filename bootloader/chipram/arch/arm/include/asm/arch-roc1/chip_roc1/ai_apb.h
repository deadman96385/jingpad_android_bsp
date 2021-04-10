/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-18 10:52:53
 *
 */


#ifndef AI_APB_H
#define AI_APB_H

#define CTL_BASE_AI_APB 0x6FD00000


#define REG_AI_APB_APB_EB                           ( CTL_BASE_AI_APB + 0x0000 )
#define REG_AI_APB_APB_RST                          ( CTL_BASE_AI_APB + 0x0004 )
#define REG_AI_APB_GEN_CLK_CFG                      ( CTL_BASE_AI_APB + 0x0008 )
#define REG_AI_APB_CAMBRICON_INT_STATUS             ( CTL_BASE_AI_APB + 0x000C )
#define REG_AI_APB_POWERVR_INT_STATUS               ( CTL_BASE_AI_APB + 0x0010 )
#define REG_AI_APB_CAMBRICON_STATUS                 ( CTL_BASE_AI_APB + 0x0014 )
#define REG_AI_APB_LPC_AB_TO_DDR                    ( CTL_BASE_AI_APB + 0x0018 )
#define REG_AI_APB_LPC_CFG_MTX_M0                   ( CTL_BASE_AI_APB + 0x001C )
#define REG_AI_APB_LPC_CFG_MTX_S0                   ( CTL_BASE_AI_APB + 0x0020 )
#define REG_AI_APB_LPC_CFG_MTX_S1                   ( CTL_BASE_AI_APB + 0x0024 )
#define REG_AI_APB_LPC_CFG_MTX_S2                   ( CTL_BASE_AI_APB + 0x0028 )
#define REG_AI_APB_LPC_MAIN_MTX_M0                  ( CTL_BASE_AI_APB + 0x002C )
#define REG_AI_APB_LPC_MAIN_MTX_M1                  ( CTL_BASE_AI_APB + 0x0030 )
#define REG_AI_APB_LPC_MAIN_MTX_S0                  ( CTL_BASE_AI_APB + 0x0034 )
#define REG_AI_APB_LPC_MAIN_MTX_S1                  ( CTL_BASE_AI_APB + 0x0038 )
#define REG_AI_APB_LPC_MAIN_MTX_MAIN                ( CTL_BASE_AI_APB + 0x003C )
#define REG_AI_APB_LPC_AB_SLV_CAMBRICON             ( CTL_BASE_AI_APB + 0x0040 )
#define REG_AI_APB_LPC_AB_DDR_CAMBRICON             ( CTL_BASE_AI_APB + 0x0044 )
#define REG_AI_APB_LPC_AB_SLV_POWERVR               ( CTL_BASE_AI_APB + 0x004C )
#define REG_AI_APB_LPC_AB_DDR_POWERVR               ( CTL_BASE_AI_APB + 0x0050 )
#define REG_AI_APB_ASYNC_BRIDGE_TO_DDR              ( CTL_BASE_AI_APB + 0x0054 )
#define REG_AI_APB_AI_QOS_CTRL                      ( CTL_BASE_AI_APB + 0x0058 )
#define REG_AI_APB_AI_APB2APB_MMU_CTRL              ( CTL_BASE_AI_APB + 0x005C )
#define REG_AI_APB_AI_APB2APB_DVFS_CTRL             ( CTL_BASE_AI_APB + 0x0060 )
#define REG_AI_APB_AI_CAMBRICON_LP_HANDSK_CTRL      ( CTL_BASE_AI_APB + 0x0064 )
#define REG_AI_APB_AI_CAMBRICON_SOFT_RST            ( CTL_BASE_AI_APB + 0x0068 )
#define REG_AI_APB_LPC_RS_CAMB_TO_MMU               ( CTL_BASE_AI_APB + 0x006C )

/* REG_AI_APB_APB_EB */

#define BIT_AI_APB_POWERVR_EB                         BIT(4)
#define BIT_AI_APB_CAMBRICON_EB                       BIT(3)
#define BIT_AI_APB_MMU_APB_EB                         BIT(2)
#define BIT_AI_APB_DVFS_APB_EB                        BIT(1)
#define BIT_AI_APB_CLK_TOP_APB_EB                     BIT(0)

/* REG_AI_APB_APB_RST */

#define BIT_AI_APB_SYS_SOFT_RST_REQ_POWERVR           BIT(9)
#define BIT_AI_APB_CAMB_SLV_AB_SOFT_RST               BIT(8)
#define BIT_AI_APB_CAMB_DDR_AB_SOFT_RST               BIT(7)
#define BIT_AI_APB_POWERVR_SOFT_RST                   BIT(6)
#define BIT_AI_APB_POWERVR_SLV_AB_SOFT_RST            BIT(5)
#define BIT_AI_APB_POWERVR_DDR_AB_SOFT_RST            BIT(4)
#define BIT_AI_APB_MMU_SOFT_RST                       BIT(3)
#define BIT_AI_APB_AI_MAIN_SOFT_RST                   BIT(2)
#define BIT_AI_APB_DVFS_SOFT_RST                      BIT(1)
#define BIT_AI_APB_CKG_SOFT_RST                       BIT(0)

/* REG_AI_APB_GEN_CLK_CFG */

#define BIT_AI_APB_AUTO_CKG_EN_POWERVR_CFG            BIT(11)
#define BIT_AI_APB_AUTO_CKG_EN_CAMBRICON_CFG          BIT(10)
#define BIT_AI_APB_AUTO_CKG_EN_MAIN_MTX               BIT(9)
#define BIT_AI_APB_AUTO_CKG_EN_POWERVR                BIT(8)
#define BIT_AI_APB_AUTO_CKG_EN_CAMBRICON              BIT(7)
#define BIT_AI_APB_AI_MAIN_MTX_CKG_EN_SW              BIT(6)
#define BIT_AI_APB_MMU_CKG_EN                         BIT(5)
#define BIT_AI_APB_DVFS_CKG_EN                        BIT(4)
#define BIT_AI_APB_POWERVR_CFG_CKG_EN_SW              BIT(3)
#define BIT_AI_APB_CAMBRICON_CFG_CKG_EN_SW            BIT(2)
#define BIT_AI_APB_POWERVR_CKG_EN_SW                  BIT(1)
#define BIT_AI_APB_CAMBRICON_CKG_EN_SW                BIT(0)

/* REG_AI_APB_CAMBRICON_INT_STATUS */

#define BIT_AI_APB_IRQ_VALID                          BIT(1)
#define BIT_AI_APB_IRQ                                BIT(0)

/* REG_AI_APB_POWERVR_INT_STATUS */

#define BIT_AI_APB_FINISH_IRQ                         BIT(0)

/* REG_AI_APB_CAMBRICON_STATUS */

#define BIT_AI_APB_MMU_INVALIDATE                     BIT(3)
#define BIT_AI_APB_FU_IDLE                            BIT(2)
#define BIT_AI_APB_IO_IDLE                            BIT(1)
#define BIT_AI_APB_IPU_START                          BIT(0)

/* REG_AI_APB_LPC_AB_TO_DDR */

#define BIT_AI_APB_PU_NUM_LPC_AB_TO_DDR(x)            (((x) & 0xFF) << 21)
#define BIT_AI_APB_AXI_LP_CTRL_DISABLE                BIT(20)
#define BIT_AI_APB_LP_EB_AB_TO_DDR                    BIT(16)
#define BIT_AI_APB_LP_NUM_AB_TO_DDR(x)                (((x) & 0xFFFF))

/* REG_AI_APB_LPC_CFG_MTX_M0 */

#define BIT_AI_APB_PU_NUM_LPC_CFG_MTX_M0(x)           (((x) & 0xFF) << 21)
#define BIT_AI_APB_LP_EB_CFG_MTX_M0                   BIT(16)
#define BIT_AI_APB_LP_NUM_CFG_MTX_M0(x)               (((x) & 0xFFFF))

/* REG_AI_APB_LPC_CFG_MTX_S0 */

#define BIT_AI_APB_PU_NUM_LPC_CFG_MTX_S0(x)           (((x) & 0xFF) << 21)
#define BIT_AI_APB_LP_EB_CFG_MTX_S0                   BIT(16)
#define BIT_AI_APB_LP_NUM_CFG_MTX_S0(x)               (((x) & 0xFFFF))

/* REG_AI_APB_LPC_CFG_MTX_S1 */

#define BIT_AI_APB_PU_NUM_LPC_CFG_MTX_S1(x)           (((x) & 0xFF) << 21)
#define BIT_AI_APB_LP_EB_CFG_MTX_S1                   BIT(16)
#define BIT_AI_APB_LP_NUM_CFG_MTX_S1(x)               (((x) & 0xFFFF))

/* REG_AI_APB_LPC_CFG_MTX_S2 */

#define BIT_AI_APB_PU_NUM_LPC_CFG_MTX_S2(x)           (((x) & 0xFF) << 21)
#define BIT_AI_APB_LP_EB_CFG_MTX_S2                   BIT(16)
#define BIT_AI_APB_LP_NUM_CFG_MTX_S2(x)               (((x) & 0xFFFF))

/* REG_AI_APB_LPC_MAIN_MTX_M0 */

#define BIT_AI_APB_PU_NUM_LPC_MAIN_MTX_M0(x)          (((x) & 0xFF) << 21)
#define BIT_AI_APB_LP_EB_MAIN_MTX_M0                  BIT(16)
#define BIT_AI_APB_LP_NUM_MAIN_MTX_M0(x)              (((x) & 0xFFFF))

/* REG_AI_APB_LPC_MAIN_MTX_M1 */

#define BIT_AI_APB_PU_NUM_LPC_MAIN_MTX_M1(x)          (((x) & 0xFF) << 21)
#define BIT_AI_APB_LP_EB_MAIN_MTX_M1                  BIT(16)
#define BIT_AI_APB_LP_NUM_MAIN_MTX_M1(x)              (((x) & 0xFFFF))

/* REG_AI_APB_LPC_MAIN_MTX_S0 */

#define BIT_AI_APB_PU_NUM_LPC_MAIN_MTX_S0(x)          (((x) & 0xFF) << 21)
#define BIT_AI_APB_LP_EB_MAIN_MTX_S0                  BIT(16)
#define BIT_AI_APB_LP_NUM_MAIN_MTX_S0(x)              (((x) & 0xFFFF))

/* REG_AI_APB_LPC_MAIN_MTX_S1 */

#define BIT_AI_APB_PU_NUM_LPC_MAIN_MTX_S1(x)          (((x) & 0xFF) << 21)
#define BIT_AI_APB_LP_EB_MAIN_MTX_S1                  BIT(16)
#define BIT_AI_APB_LP_NUM_MAIN_MTX_S1(x)              (((x) & 0xFFFF))

/* REG_AI_APB_LPC_MAIN_MTX_MAIN */

#define BIT_AI_APB_PU_NUM_LPC_MAIN_MTX_MAIN(x)        (((x) & 0xFF) << 21)
#define BIT_AI_APB_LP_EB_MAIN_MTX_MAIN                BIT(16)
#define BIT_AI_APB_LP_NUM_MAIN_MTX_MAIN(x)            (((x) & 0xFFFF))

/* REG_AI_APB_LPC_AB_SLV_CAMBRICON */

#define BIT_AI_APB_LP_EB_AB_SLV_CAMBRICON             BIT(16)
#define BIT_AI_APB_LP_NUM_AB_SLV_CAMBRICON(x)         (((x) & 0xFFFF))

/* REG_AI_APB_LPC_AB_DDR_CAMBRICON */

#define BIT_AI_APB_LP_EB_AB_DDR_CAMBRICON             BIT(16)
#define BIT_AI_APB_LP_NUM_AB_DDR_CAMBRICON(x)         (((x) & 0xFFFF))

/* REG_AI_APB_LPC_AB_SLV_POWERVR */

#define BIT_AI_APB_LP_EB_AB_SLV_POWERVR               BIT(16)
#define BIT_AI_APB_LP_NUM_AB_SLV_POWERVR(x)           (((x) & 0xFFFF))

/* REG_AI_APB_LPC_AB_DDR_POWERVR */

#define BIT_AI_APB_LP_EB_AB_DDR_POWERVR               BIT(16)
#define BIT_AI_APB_LP_NUM_AB_DDR_POWERVR(x)           (((x) & 0xFFFF))

/* REG_AI_APB_ASYNC_BRIDGE_TO_DDR */

#define BIT_AI_APB_RST_SUBSYS_AB_TO_DDR               BIT(2)
#define BIT_AI_APB_BRIDGE_TRANS_IDLE_AB_TO_DDR        BIT(1)
#define BIT_AI_APB_AXI_DETECTOR_OVERFLOW_AB_TO_DDR    BIT(0)

/* REG_AI_APB_AI_QOS_CTRL */

#define BIT_AI_APB_AWQOS_CAMBRICON_SW_AI_MAIN_MTX(x)  (((x) & 0xF) << 21)
#define BIT_AI_APB_ARQOS_CAMBRICON_SW_AI_MAIN_MTX(x)  (((x) & 0xF) << 17)
#define BIT_AI_APB_QOS_POWERVR_SEL_SW_AI_MAIN_MTX     BIT(16)
#define BIT_AI_APB_AWQOS_POWERVR_SW_AI_MAIN_MTX(x)    (((x) & 0xF) << 12)
#define BIT_AI_APB_ARQOS_POWERVR_SW_AI_MAIN_MTX(x)    (((x) & 0xF) << 8)
#define BIT_AI_APB_AWQOS_THRESHOLD_AI_MAIN_MTX(x)     (((x) & 0xF) << 4)
#define BIT_AI_APB_ARQOS_THRESHOLD_AI_MAIN_MTX(x)     (((x) & 0xF))

/* REG_AI_APB_AI_APB2APB_MMU_CTRL */

#define BIT_AI_APB_MCLK_AUTOGATE_EN_APB2APB_MMU       BIT(1)
#define BIT_AI_APB_SCLK_AUTOGATE_EN_APB2APB_MMU       BIT(0)

/* REG_AI_APB_AI_APB2APB_DVFS_CTRL */

#define BIT_AI_APB_MCLK_AUTOGATE_EN_APB2APB_DVFS      BIT(1)
#define BIT_AI_APB_SCLK_AUTOGATE_EN_APB2APB_DVFS      BIT(0)

/* REG_AI_APB_AI_CAMBRICON_LP_HANDSK_CTRL */

#define BIT_AI_APB_CAMB_IP_LP_REQ                     BIT(20)
#define BIT_AI_APB_CAMB_IP_LP_ACK                     BIT(19)
#define BIT_AI_APB_SW_CAMB_IP_LP_REQ                  BIT(18)
#define BIT_AI_APB_SW_CAMB_IP_SOFT_RST                BIT(17)
#define BIT_AI_APB_SW_CAMB_IP_CGM_EN                  BIT(16)
#define BIT_AI_APB_SW_CAMB_IP_LP_HANDSK_ENABLE        BIT(15)
#define BIT_AI_APB_CAMB_IP_CGM_EN                     BIT(14)
#define BIT_AI_APB_CAMB_LP_NEXT_STATE(x)              (((x) & 0x7) << 11)
#define BIT_AI_APB_CAMB_LP_CURRENT_STATE(x)           (((x) & 0x7) << 8)
#define BIT_AI_APB_CAMB_LP_HANDSHK_CNT(x)             (((x) & 0xFF))

/* REG_AI_APB_AI_CAMBRICON_SOFT_RST */

#define BIT_AI_APB_CAMB_SOFT_RST                      BIT(0)

/* REG_AI_APB_LPC_RS_CAMB_TO_MMU */

#define BIT_AI_APB_PU_NUM_LPC_RS_CAMB_TO_MMU(x)       (((x) & 0xFF) << 21)
#define BIT_AI_APB_LP_EB_RS_CAMB_TO_MMU               BIT(16)
#define BIT_AI_APB_LP_NUM_RS_CAMB_TO_MMU(x)           (((x) & 0xFFFF))


#endif /* AI_APB_H */


