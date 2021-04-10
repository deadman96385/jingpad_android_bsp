/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _CAM_AHB_REG_H
#define _CAM_AHB_REG_H

#define CTL_BASE_CAM_AHB SPRD_CAMAHB_BASE


#define REG_CAM_AHB_AHB_EB                       ( CTL_BASE_CAM_AHB + 0x0000 )
#define REG_CAM_AHB_AHB_RST                      ( CTL_BASE_CAM_AHB + 0x0004 )
#define REG_CAM_AHB_GEN_CKG_CFG                  ( CTL_BASE_CAM_AHB + 0x0008 )
#define REG_CAM_AHB_MIPI_CSI_CTRL                ( CTL_BASE_CAM_AHB + 0x000C )
#define REG_CAM_AHB_NIC0_QOS_CFG0                ( CTL_BASE_CAM_AHB + 0x0010 )
#define REG_CAM_AHB_NIC0_QOS_CFG1                ( CTL_BASE_CAM_AHB + 0x0014 )
#define REG_CAM_AHB_NIC1_QOS_CFG2                ( CTL_BASE_CAM_AHB + 0x0018 )
#define REG_CAM_AHB_CAM_CACHE_CFG1               ( CTL_BASE_CAM_AHB + 0x001C )
#define REG_CAM_AHB_CAM_CACHE_CFG2               ( CTL_BASE_CAM_AHB + 0x0020 )
#define REG_CAM_AHB_CB_SRC_SEL                   ( CTL_BASE_CAM_AHB + 0x0024 )
#define REG_CAM_AHB_JPG_CO_WORK_SRC_SEL          ( CTL_BASE_CAM_AHB + 0x0028 )
#define REG_CAM_AHB_MODULE_CLK_EN                ( CTL_BASE_CAM_AHB + 0x002C )
#define REG_CAM_AHB_MODULE_SOFT_RST              ( CTL_BASE_CAM_AHB + 0x0030 )
#define REG_CAM_AHB_CAM_AXI_LPC0                 ( CTL_BASE_CAM_AHB + 0x0034 )
#define REG_CAM_AHB_CAM_AXI_LPC1                 ( CTL_BASE_CAM_AHB + 0x0038 )
#define REG_CAM_AHB_CAM_AXI_LPC2                 ( CTL_BASE_CAM_AHB + 0x003C )
#define REG_CAM_AHB_CAM_AXI_LPC3                 ( CTL_BASE_CAM_AHB + 0x0040 )
#define REG_CAM_AHB_CAM_AXI_LPC4                 ( CTL_BASE_CAM_AHB + 0x0044 )
#define REG_CAM_AHB_CAM_AXI_LPC5                 ( CTL_BASE_CAM_AHB + 0x0048 )
#define REG_CAM_AHB_CAM_AB0_CTRL0                ( CTL_BASE_CAM_AHB + 0x004C )
#define REG_CAM_AHB_CAM_AB0_CTRL1                ( CTL_BASE_CAM_AHB + 0x0050 )
#define REG_CAM_AHB_CAM_AB0_CTRL2                ( CTL_BASE_CAM_AHB + 0x0054 )
#define REG_CAM_AHB_CAM_AB0_DBG                  ( CTL_BASE_CAM_AHB + 0x0058 )
#define REG_CAM_AHB_CSI_HOST_IDI_CTRL            ( CTL_BASE_CAM_AHB + 0x005C )
#define REG_CAM_AHB_CAM_SUB_IP_EFF_MASK          ( CTL_BASE_CAM_AHB + 0x0060 )
#define REG_CAM_AHB_CAM_DPU_AXI_OT_CTRL_CFG      ( CTL_BASE_CAM_AHB + 0x0064 )
#define REG_CAM_AHB_CAM_ISP_AXI_OT_CTRL_CFG      ( CTL_BASE_CAM_AHB + 0x0068 )
#define REG_CAM_AHB_CAM_JPG_CPP_AXI_OT_CTRL_CFG  ( CTL_BASE_CAM_AHB + 0x006C )
#define REG_CAM_AHB_CAM_JPG_AXI_OT_CTRL_CFG      ( CTL_BASE_CAM_AHB + 0x0070 )
#define REG_CAM_AHB_CAM_CPP_AXI_OT_CTRL_CFG      ( CTL_BASE_CAM_AHB + 0x0074 )

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_AHB_EB
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_JPG_CPP_MTX_EB                                  BIT(25)
#define BIT_CAM_AHB_CLK26M_IF_EB                                    BIT(24)
#define BIT_CAM_AHB_CAM_MTX_EB                                      BIT(23)
#define BIT_CAM_AHB_SENSOR1_EB                                      BIT(22)
#define BIT_CAM_AHB_SENSOR0_EB                                      BIT(21)
#define BIT_CAM_AHB_ISP_MTX_EB                                      BIT(19)
#define BIT_CAM_AHB_ISP_MCLK_EB                                     BIT(17)
#define BIT_CAM_AHB_ISP_ICLK_EB                                     BIT(16)
#define BIT_CAM_AHB_CPP_EB                                          BIT(10)
#define BIT_CAM_AHB_CKG_EB                                          BIT(7)
#define BIT_CAM_AHB_JPG0_EB                                         BIT(5)
#define BIT_CAM_AHB_CSI1_EB                                         BIT(4)
#define BIT_CAM_AHB_CSI0_EB                                         BIT(3)
#define BIT_CAM_AHB_ISP0_EB                                         BIT(2)
#define BIT_CAM_AHB_DCAM1_IF_EB                                     BIT(1)
#define BIT_CAM_AHB_DCAM0_IF_EB                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_AHB_RST
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_ISP_PERFMON_SOFT_RST                            BIT(29)
#define BIT_CAM_AHB_ISP_BLK_CFG_SOFT_RST                            BIT(27)
#define BIT_CAM_AHB_DCAM1_IF_SOFT_RST                               BIT(26)
#define BIT_CAM_AHB_DCAM0_IF_SOFT_RST                               BIT(24)
#define BIT_CAM_AHB_CPP_SOFT_RST                                    BIT(22)
#define BIT_CAM_AHB_ISP_MAIN_CFG_SOFT_RST                           BIT(21)
#define BIT_CAM_AHB_ISP_LITE_CFG_SOFT_RST                           BIT(20)
#define BIT_CAM_AHB_CCIR_SOFT_RST                                   BIT(18)
#define BIT_CAM_AHB_CKG_SOFT_RST                                    BIT(16)
#define BIT_CAM_AHB_ISP_MAIN_IP_SOFT_RST                            BIT(14)
#define BIT_CAM_AHB_ISP_LITE_IP_SOFT_RST                            BIT(13)
#define BIT_CAM_AHB_DCAM1_CAM0_SOFT_RST                             BIT(12)
#define BIT_CAM_AHB_ISP1_CFG_SOFT_RST                               BIT(11)
#define BIT_CAM_AHB_ISP1_LOG_SOFT_RST                               BIT(10)
#define BIT_CAM_AHB_ISP_LITE_FMCU_SOFT_RST                          BIT(9)
#define BIT_CAM_AHB_DCAM0_CAM0_SOFT_RST                             BIT(8)
#define BIT_CAM_AHB_ISP_MAIN_FMCU_SOFT_RST                          BIT(7)
#define BIT_CAM_AHB_JPG0_SOFT_RST                                   BIT(6)
#define BIT_CAM_AHB_CSI1_SOFT_RST                                   BIT(5)
#define BIT_CAM_AHB_CSI0_SOFT_RST                                   BIT(4)
#define BIT_CAM_AHB_ISP0_CFG_SOFT_RST                               BIT(3)
#define BIT_CAM_AHB_ISP0_LOG_SOFT_RST                               BIT(2)
#define BIT_CAM_AHB_DCAM1_SOFT_RST                                  BIT(1)
#define BIT_CAM_AHB_DCAM0_SOFT_RST                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_GEN_CKG_CFG
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_CPP_AXI_CKG_EN                                  BIT(13)
#define BIT_CAM_AHB_ISP1_AXI_CKG_EN                                 BIT(11)
#define BIT_CAM_AHB_ISP0_AXI_CKG_EN                                 BIT(10)
#define BIT_CAM_AHB_JPG0_AXI_CKG_EN                                 BIT(8)
#define BIT_CAM_AHB_SENSOR1_CKG_EN                                  BIT(7)
#define BIT_CAM_AHB_SENSOR0_CKG_EN                                  BIT(6)
#define BIT_CAM_AHB_MIPI_CSI1_CKG_EN                                BIT(3)
#define BIT_CAM_AHB_CPHY1_CFG_CKG_EN                                BIT(2)
#define BIT_CAM_AHB_MIPI_CSI0_CKG_EN                                BIT(1)
#define BIT_CAM_AHB_CPHY0_CFG_CKG_EN                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_MIPI_CSI_CTRL
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_MIPI_CPHY1_SAMPLE_SEL(x)                        (((x) & 0x3) << 11)
#define BIT_CAM_AHB_MIPI_CPHY1_SYNC_MODE                            BIT(10)
#define BIT_CAM_AHB_MIPI_CPHY1_TEST_CTL                             BIT(9)
#define BIT_CAM_AHB_MIPI_CPHY1_SEL                                  BIT(8)
#define BIT_CAM_AHB_MIPI_CPHY0_SAMPLE_SEL(x)                        (((x) & 0x3) << 3)
#define BIT_CAM_AHB_MIPI_CPHY0_SYNC_MODE                            BIT(2)
#define BIT_CAM_AHB_MIPI_CPHY0_TEST_CTL                             BIT(1)
#define BIT_CAM_AHB_MIPI_CPHY0_SEL                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_NIC0_QOS_CFG0
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_QOS_R_CPP(x)                                    (((x) & 0xF) << 20)
#define BIT_CAM_AHB_QOS_W_CPP(x)                                    (((x) & 0xF) << 16)
#define BIT_CAM_AHB_QOS_R_JPG0(x)                                   (((x) & 0xF) << 12)
#define BIT_CAM_AHB_QOS_W_JPG0(x)                                   (((x) & 0xF) << 8)
#define BIT_CAM_AHB_QOS_R_DCAM1(x)                                  (((x) & 0xF) << 4)
#define BIT_CAM_AHB_QOS_W_DCAM1(x)                                  (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_NIC0_QOS_CFG1
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_ISPB_SOFT_RST_MASK                              BIT(24)
#define BIT_CAM_AHB_ISPA_SOFT_RST_MASK                              BIT(23)
#define BIT_CAM_AHB_DCAM1_SOFT_RST_MASK                             BIT(21)
#define BIT_CAM_AHB_DCAM0_SOFT_RST_MASK                             BIT(20)
#define BIT_CAM_AHB_CPP_SOFT_RST_MASK                               BIT(17)
#define BIT_CAM_AHB_JPG_SOFT_RST_MASK                               BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_NIC1_QOS_CFG2
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_QOS_R_DCAM0(x)                                  (((x) & 0xF) << 28)
#define BIT_CAM_AHB_QOS_W_DCAM0(x)                                  (((x) & 0xF) << 24)
#define BIT_CAM_AHB_QOS_R_ISP1(x)                                   (((x) & 0xF) << 20)
#define BIT_CAM_AHB_QOS_W_ISP1(x)                                   (((x) & 0xF) << 16)
#define BIT_CAM_AHB_QOS_R_ISP0(x)                                   (((x) & 0xF) << 12)
#define BIT_CAM_AHB_QOS_W_ISP0(x)                                   (((x) & 0xF) << 8)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_CACHE_CFG1
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_ARCACHE_JPG(x)                                  (((x) & 0xF) << 28)
#define BIT_CAM_AHB_AWCACHE_JPG(x)                                  (((x) & 0xF) << 24)
#define BIT_CAM_AHB_ARCACHE_ISP(x)                                  (((x) & 0xF) << 20)
#define BIT_CAM_AHB_AWCACHE_ISP(x)                                  (((x) & 0xF) << 16)
#define BIT_CAM_AHB_ARCACHE_DCAM1(x)                                (((x) & 0xF) << 12)
#define BIT_CAM_AHB_AWCACHE_DCAM1(x)                                (((x) & 0xF) << 8)
#define BIT_CAM_AHB_ARCACHE_DCAM0(x)                                (((x) & 0xF) << 4)
#define BIT_CAM_AHB_AWCACHE_DCAM0(x)                                (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_CACHE_CFG2
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_ARCACHE_CPP(x)                                  (((x) & 0xF) << 28)
#define BIT_CAM_AHB_AWCACHE_CPP(x)                                  (((x) & 0xF) << 24)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CB_SRC_SEL
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_MIPI_HOST1_CB_CLK_EN                            BIT(1)
#define BIT_CAM_AHB_MIPI_HOST0_CB_CLK_EN                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_JPG_CO_WORK_SRC_SEL
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_ISP_COWORK_SRC_SEL                              BIT(1)
#define BIT_CAM_AHB_JPG_CO_WORK_SRC_SEL                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_MODULE_CLK_EN
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_SM_ISPB_IN_ISP_EB                               BIT(8)
#define BIT_CAM_AHB_SM_ISPA_IN_ISP_EB                               BIT(7)
#define BIT_CAM_AHB_SM_DCAM1_IF_IN_DCAM2ISP_EB                      BIT(3)
#define BIT_CAM_AHB_SM_DCAM0_IF_IN_DCAM2ISP_EB                      BIT(2)
#define BIT_CAM_AHB_SM_DCAM1_IF_IN_DCAM_EB                          BIT(1)
#define BIT_CAM_AHB_SM_DCAM0_IF_IN_DCAM_EB                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_MODULE_SOFT_RST
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_SM_DCAM1_IF_IN_DCAM2ISP_SOFT_RST                BIT(3)
#define BIT_CAM_AHB_SM_DCAM0_IF_IN_DCAM2ISP_SOFT_RST                BIT(2)
#define BIT_CAM_AHB_SM_DCAM1_IF_IN_DCAM_SOFT_RST                    BIT(1)
#define BIT_CAM_AHB_SM_DCAM0_IF_IN_DCAM_SOFT_RST                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AXI_LPC0
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_LP_EB_DCAM0                                     BIT(31)
#define BIT_CAM_AHB_LP_FORCE_DCAM0                                  BIT(30)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_DCAM0                           BIT(29)
#define BIT_CAM_AHB_LP_EB_DCAM1                                     BIT(28)
#define BIT_CAM_AHB_LP_FORCE_DCAM1                                  BIT(27)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_DCAM1                           BIT(26)
#define BIT_CAM_AHB_LP_EB_AP_DISP                                   BIT(25)
#define BIT_CAM_AHB_LP_FORCE_AP_DISP                                BIT(24)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_AP_DISP                         BIT(23)
#define BIT_CAM_AHB_LP_EB_ISPA                                      BIT(22)
#define BIT_CAM_AHB_LP_FORCE_ISPA                                   BIT(21)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_ISPA                            BIT(20)
#define BIT_CAM_AHB_LP_EB_ISPB                                      BIT(19)
#define BIT_CAM_AHB_LP_FORCE_ISPB                                   BIT(18)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_ISPB                            BIT(17)
#define BIT_CAM_AHB_LP_EB_CAM_ISP_MAIN                              BIT(13)
#define BIT_CAM_AHB_LP_FORCE_CAM_ISP_MAIN                           BIT(12)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_CAM_ISP_MAIN                    BIT(11)
#define BIT_CAM_AHB_LP_EB_JPG0                                      BIT(10)
#define BIT_CAM_AHB_LP_FORCE_JPG0                                   BIT(9)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_JPG0                            BIT(8)
#define BIT_CAM_AHB_LP_EB_CPP                                       BIT(7)
#define BIT_CAM_AHB_LP_FORCE_CPP                                    BIT(6)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_CPP                             BIT(5)
#define BIT_CAM_AHB_LP_EB_CAM_CPP_JPG_MAIN                          BIT(4)
#define BIT_CAM_AHB_LP_FORCE_CAM_CPP_JPG_MAIN                       BIT(3)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_CAM_CPP_JPG_MAIN                BIT(2)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AXI_LPC1
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_LP_EB_CAM_MMU_PF                                BIT(31)
#define BIT_CAM_AHB_LP_FORCE_CAM_MMU_PF                             BIT(30)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_CAM_MMU_PF                      BIT(29)
#define BIT_CAM_AHB_LP_EB_CAM_DCAM_ISP_MAIN                         BIT(28)
#define BIT_CAM_AHB_LP_FORCE_CAM_DCAM_ISP_MAIN                      BIT(27)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_CAM_DCAM_ISP_MAIN               BIT(26)
#define BIT_CAM_AHB_LP_EB_DCAM_ISP_AB                               BIT(25)
#define BIT_CAM_AHB_LP_FORCE_DCAM_ISP_AB                            BIT(24)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_DCAM_ISP_AB                     BIT(23)
#define BIT_CAM_AHB_LP_EB_DISPC_AB                                  BIT(22)
#define BIT_CAM_AHB_LP_FORCE_DISPC_AB                               BIT(21)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_DISPC_AB                        BIT(20)
#define BIT_CAM_AHB_LP_EB_SYS_DISP                                  BIT(19)
#define BIT_CAM_AHB_LP_FORCE_SYS_DISP                               BIT(18)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_SYS_DISP                        BIT(17)
#define BIT_CAM_AHB_LP_EB_SYS_CAM0                                  BIT(16)
#define BIT_CAM_AHB_LP_FORCE_SYS_CAM0                               BIT(15)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_SYS_CAM0                        BIT(14)
#define BIT_CAM_AHB_LP_EB_SYS_CAM1                                  BIT(13)
#define BIT_CAM_AHB_LP_FORCE_SYS_CAM1                               BIT(12)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_SYS_CAM1                        BIT(11)
#define BIT_CAM_AHB_LP_EB_SYS_MAIN                                  BIT(10)
#define BIT_CAM_AHB_LP_FORCE_SYS_MAIN                               BIT(9)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_SYS_MAIN                        BIT(8)
#define BIT_CAM_AHB_LP_EB_CAM_PUB0                                  BIT(7)
#define BIT_CAM_AHB_LP_FORCE_CAM_PUB0                               BIT(6)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_CAM_PUB0                        BIT(5)
#define BIT_CAM_AHB_LP_EB_JPG_CPP_AB                                BIT(4)
#define BIT_CAM_AHB_LP_FORCE_JPG_CPP_AB                             BIT(3)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_JPG_CPP_AB                      BIT(2)
#define BIT_CAM_AHB_ADDR_CUTOFF_ENABLE_CAM                          BIT(1)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AXI_LPC2
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_LP_NUM_ISP_TOP(x)                               (((x) & 0xFFFF) << 16)
#define BIT_CAM_AHB_LP_NUM_CAM_TOP(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AXI_LPC3
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_LP_NUM_DISP_AB(x)                               (((x) & 0xFFFF) << 16)
#define BIT_CAM_AHB_LP_NUM_CAM_SYS(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AXI_LPC4
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_LP_NUM_CAM_PUB(x)                               (((x) & 0xFFFF) << 16)
#define BIT_CAM_AHB_LP_NUM_CAM_AB(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AXI_LPC5
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_LP_NUM_CPP_JPG(x)                               (((x) & 0xFFFF) << 16)
#define BIT_CAM_AHB_LP_NUM_CPP_JPG_AB(x)                            (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AB0_CTRL0
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_AXI_DETECTOR_OVERFLOW_CH0                       BIT(31)
#define BIT_CAM_AHB_BRIDGE_TRANS_IDLE_CH0                           BIT(30)
#define BIT_CAM_AHB_BRIDGE_FIFO_FULL_CH0                            BIT(29)
#define BIT_CAM_AHB_BRIDGE_WFIFO_FULL_CH0                           BIT(28)
#define BIT_CAM_AHB_BRIDGE_RFIFO_FULL_CH0                           BIT(27)
#define BIT_CAM_AHB_FIFO_AF_LVL_AW_CH0(x)                           (((x) & 0x3F) << 20)
#define BIT_CAM_AHB_FIFO_AE_LVL_AW_CH0(x)                           (((x) & 0x3F) << 14)
#define BIT_CAM_AHB_FIFO_AF_LVL_W_CH0(x)                            (((x) & 0x3F) << 8)
#define BIT_CAM_AHB_FIFO_AE_LVL_W_CH0(x)                            (((x) & 0x3F) << 2)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AB0_CTRL1
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_FIFO_AF_LVL_B_CH0(x)                            (((x) & 0x3F) << 24)
#define BIT_CAM_AHB_FIFO_AE_LVL_B_CH0(x)                            (((x) & 0x3F) << 18)
#define BIT_CAM_AHB_FIFO_AF_LVL_AR_CH0(x)                           (((x) & 0x3F) << 12)
#define BIT_CAM_AHB_FIFO_AE_LVL_AR_CH0(x)                           (((x) & 0x3F) << 6)
#define BIT_CAM_AHB_FIFO_AF_LVL_R_CH0(x)                            (((x) & 0x3F))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AB0_CTRL2
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_FIFO_AE_LVL_R_CH0(x)                            (((x) & 0x3F))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AB0_DBG
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_CAM_AB0_DBG_SIGNAL(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CSI_HOST_IDI_CTRL
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_IDI_STATE(x)                                    (((x) & 0x7) << 6)
#define BIT_CAM_AHB_IDI_SMOOTH_SW                                   BIT(5)
#define BIT_CAM_AHB_IDI_FORCE_CSI1                                  BIT(4)
#define BIT_CAM_AHB_IDI_INTC_EN                                     BIT(3)
#define BIT_CAM_AHB_IDI_INTC_CLR                                    BIT(2)
#define BIT_CAM_AHB_IDI_DONE_STS                                    BIT(1)
#define BIT_CAM_AHB_IDI_DONE_RAW                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_SUB_IP_EFF_MASK
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_DPU_EFF_MASK                                    BIT(5)
#define BIT_CAM_AHB_ISP_EFF_MASK                                    BIT(4)
#define BIT_CAM_AHB_DCAM1_IF_EFF_MASK                               BIT(3)
#define BIT_CAM_AHB_DCAM0_IF_EFF_MASK                               BIT(2)
#define BIT_CAM_AHB_JPG_EFF_MASK                                    BIT(1)
#define BIT_CAM_AHB_CPP_EFF_MASK                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_DPU_AXI_OT_CTRL_CFG
// Register Offset : 0x0064
// Description     : axi outstanding control config register
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_DPU_AXI_OT_BYPASS_MODE                          BIT(31)
#define BIT_CAM_AHB_DPU_AR_MAX_OT(x)                                (((x) & 0x7F) << 8)
#define BIT_CAM_AHB_DPU_AW_MAX_OT(x)                                (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_ISP_AXI_OT_CTRL_CFG
// Register Offset : 0x0068
// Description     : axi outstanding control config register
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_ISP_AXI_OT_BYPASS_MODE                          BIT(31)
#define BIT_CAM_AHB_ISP_AR_MAX_OT(x)                                (((x) & 0x7F) << 8)
#define BIT_CAM_AHB_ISP_AW_MAX_OT(x)                                (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_JPG_CPP_AXI_OT_CTRL_CFG
// Register Offset : 0x006C
// Description     : axi outstanding control config register
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_JPG_CPP_AXI_OT_BYPASS_MODE                      BIT(31)
#define BIT_CAM_AHB_JPG_CPP_AR_MAX_OT(x)                            (((x) & 0x7F) << 8)
#define BIT_CAM_AHB_JPG_CPP_AW_MAX_OT(x)                            (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_JPG_AXI_OT_CTRL_CFG
// Register Offset : 0x0070
// Description     : axi outstanding control config register
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_JPG_AXI_OT_BYPASS_MODE                          BIT(31)
#define BIT_CAM_AHB_JPG_AR_MAX_OT(x)                                (((x) & 0x7F) << 8)
#define BIT_CAM_AHB_JPG_AW_MAX_OT(x)                                (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_CPP_AXI_OT_CTRL_CFG
// Register Offset : 0x0074
// Description     : axi outstanding control config register
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_CPP_AXI_OT_BYPASS_MODE                          BIT(31)
#define BIT_CAM_AHB_CPP_AR_MAX_OT(x)                                (((x) & 0x7F) << 8)
#define BIT_CAM_AHB_CPP_AW_MAX_OT(x)                                (((x) & 0x7F))


#endif // _CAM_AHB_REG_H
