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


#define REG_CAM_AHB_AHB_EB               ( CTL_BASE_CAM_AHB + 0x0000 )
#define REG_CAM_AHB_AHB_RST              ( CTL_BASE_CAM_AHB + 0x0004 )
#define REG_CAM_AHB_GEN_CKG_CFG          ( CTL_BASE_CAM_AHB + 0x0008 )
#define REG_CAM_AHB_MIPI_CSI_CTRL        ( CTL_BASE_CAM_AHB + 0x000C )
#define REG_CAM_AHB_NIC0_QOS_CFG0        ( CTL_BASE_CAM_AHB + 0x0010 )
#define REG_CAM_AHB_NIC0_QOS_CFG1        ( CTL_BASE_CAM_AHB + 0x0014 )
#define REG_CAM_AHB_NIC1_QOS_CFG2        ( CTL_BASE_CAM_AHB + 0x0018 )
#define REG_CAM_AHB_NIC1_QOS_CFG3        ( CTL_BASE_CAM_AHB + 0x001C )
#define REG_CAM_AHB_CB_SRC_SEL           ( CTL_BASE_CAM_AHB + 0x0020 )
#define REG_CAM_AHB_BUSMON_CK_EN         ( CTL_BASE_CAM_AHB + 0x0024 )
#define REG_CAM_AHB_MODULE_CLK_EN        ( CTL_BASE_CAM_AHB + 0x0028 )
#define REG_CAM_AHB_MODULE_SOFT_RST      ( CTL_BASE_CAM_AHB + 0x002C )
#define REG_CAM_AHB_CAM_AXI_LPC0         ( CTL_BASE_CAM_AHB + 0x0030 )
#define REG_CAM_AHB_CAM_AXI_LPC1         ( CTL_BASE_CAM_AHB + 0x0034 )
#define REG_CAM_AHB_CAM_AXI_LPC2         ( CTL_BASE_CAM_AHB + 0x0038 )
#define REG_CAM_AHB_CAM_AXI_LPC3         ( CTL_BASE_CAM_AHB + 0x003C )
#define REG_CAM_AHB_CAM_AXI_LPC4         ( CTL_BASE_CAM_AHB + 0x0040 )
#define REG_CAM_AHB_CAM_AB0_CTRL0        ( CTL_BASE_CAM_AHB + 0x0044 )
#define REG_CAM_AHB_CAM_AB0_CTRL1        ( CTL_BASE_CAM_AHB + 0x0048 )
#define REG_CAM_AHB_CAM_AB0_CTRL2        ( CTL_BASE_CAM_AHB + 0x004C )
#define REG_CAM_AHB_CAM_AB1_CTRL0        ( CTL_BASE_CAM_AHB + 0x0050 )
#define REG_CAM_AHB_CAM_AB1_CTRL1        ( CTL_BASE_CAM_AHB + 0x0054 )
#define REG_CAM_AHB_CAM_AB1_CTRL2        ( CTL_BASE_CAM_AHB + 0x0058 )
#define REG_CAM_AHB_CAM_AB0_DBG          ( CTL_BASE_CAM_AHB + 0x005C )
#define REG_CAM_AHB_CAM_AB1_DBG          ( CTL_BASE_CAM_AHB + 0x0060 )
#define REG_CAM_AHB_DSI0_CNT_CTRL        ( CTL_BASE_CAM_AHB + 0x0064 )
#define REG_CAM_AHB_DSI1_CNT_CTRL        ( CTL_BASE_CAM_AHB + 0x0068 )

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_AHB_EB
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_SENSOR2_EB                                     BIT(25)
#define BIT_CAM_AHB_CLK26M_IF_EB                                   BIT(24)
#define BIT_CAM_AHB_CAM_MTX_EB                                     BIT(23)
#define BIT_CAM_AHB_SENSOR1_EB                                     BIT(22)
#define BIT_CAM_AHB_SENSOR0_EB                                     BIT(21)
#define BIT_CAM_AHB_DCAM0_IF_EB                                    BIT(20)
#define BIT_CAM_AHB_ISP_ISP2DCAM_EB                                BIT(19)
#define BIT_CAM_AHB_ISP_PCLK_EB                                    BIT(18)
#define BIT_CAM_AHB_ISP_MCLK_EB                                    BIT(17)
#define BIT_CAM_AHB_ISP_ICLK_EB                                    BIT(16)
#define BIT_CAM_AHB_ISP_LCLK_EB                                    BIT(15)
#define BIT_CAM_AHB_ISP2DCAM_IF_EB                                 BIT(14)
#define BIT_CAM_AHB_DCAM2ISP_IF_EB                                 BIT(13)
#define BIT_CAM_AHB_ISP2_EB                                        BIT(12)
#define BIT_CAM_AHB_MMU_PF_EB                                      BIT(11)
#define BIT_CAM_AHB_CPP_EB                                         BIT(10)
#define BIT_CAM_AHB_ISP1_EB                                        BIT(9)
#define BIT_CAM_AHB_MMU_EB                                         BIT(8)
#define BIT_CAM_AHB_CKG_EB                                         BIT(7)
#define BIT_CAM_AHB_JPG1_EB                                        BIT(6)
#define BIT_CAM_AHB_JPG0_EB                                        BIT(5)
#define BIT_CAM_AHB_CSI1_EB                                        BIT(4)
#define BIT_CAM_AHB_CSI0_EB                                        BIT(3)
#define BIT_CAM_AHB_ISP0_EB                                        BIT(2)
#define BIT_CAM_AHB_DCAM1_EB                                       BIT(1)
#define BIT_CAM_AHB_DCAM0_EB                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_AHB_RST
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_ISP2_LOG_SOFT_RST                              BIT(30)
#define BIT_CAM_AHB_ISP2DCAM_IF_SOFT_RST                           BIT(29)
#define BIT_CAM_AHB_DCAM2ISP_IF_SOFT_RST                           BIT(28)
#define BIT_CAM_AHB_ISP_IP_SOFT_RST                                BIT(27)
#define BIT_CAM_AHB_DCAM1_IF_SOFT_RST                              BIT(26)
#define BIT_CAM_AHB_DCAM1_CAM3_SOFT_RST                            BIT(25)
#define BIT_CAM_AHB_DCAM0_IF_SOFT_RST                              BIT(24)
#define BIT_CAM_AHB_DCAM0_CAM3_SOFT_RST                            BIT(23)
#define BIT_CAM_AHB_CPP_SOFT_RST                                   BIT(22)
#define BIT_CAM_AHB_ISP1_CFG_SOFT_RST                              BIT(21)
#define BIT_CAM_AHB_ISP1_LOG_SOFT_RST                              BIT(20)
#define BIT_CAM_AHB_MMU_PF_SOFT_RST                                BIT(19)
#define BIT_CAM_AHB_CCIR_SOFT_RST                                  BIT(18)
#define BIT_CAM_AHB_MMU_SOFT_RST                                   BIT(17)
#define BIT_CAM_AHB_CKG_SOFT_RST                                   BIT(16)
#define BIT_CAM_AHB_DCAM1_ROT_SOFT_RST                             BIT(15)
#define BIT_CAM_AHB_DCAM1_CAM2_SOFT_RST                            BIT(14)
#define BIT_CAM_AHB_DCAM1_CAM1_SOFT_RST                            BIT(13)
#define BIT_CAM_AHB_DCAM1_CAM0_SOFT_RST                            BIT(12)
#define BIT_CAM_AHB_DCAM0_ROT_SOFT_RST                             BIT(11)
#define BIT_CAM_AHB_DCAM0_CAM2_SOFT_RST                            BIT(10)
#define BIT_CAM_AHB_DCAM0_CAM1_SOFT_RST                            BIT(9)
#define BIT_CAM_AHB_DCAM0_CAM0_SOFT_RST                            BIT(8)
#define BIT_CAM_AHB_JPG1_SOFT_RST                                  BIT(7)
#define BIT_CAM_AHB_JPG0_SOFT_RST                                  BIT(6)
#define BIT_CAM_AHB_CSI1_SOFT_RST                                  BIT(5)
#define BIT_CAM_AHB_CSI0_SOFT_RST                                  BIT(4)
#define BIT_CAM_AHB_ISP0_CFG_SOFT_RST                              BIT(3)
#define BIT_CAM_AHB_ISP0_LOG_SOFT_RST                              BIT(2)
#define BIT_CAM_AHB_DCAM1_SOFT_RST                                 BIT(1)
#define BIT_CAM_AHB_DCAM0_SOFT_RST                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_GEN_CKG_CFG
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_SPARE_AXI_CKG_EN                               BIT(17)
#define BIT_CAM_AHB_ISP2DCAM_IF_AXI_CKG_EN                         BIT(16)
#define BIT_CAM_AHB_DCAM2ISP_IF_AXI_CKG_EN                         BIT(15)
#define BIT_CAM_AHB_DCAM0_IF_CKG_EN                                BIT(14)
#define BIT_CAM_AHB_CPP_AXI_CKG_EN                                 BIT(13)
#define BIT_CAM_AHB_ISP2_AXI_CKG_EN                                BIT(12)
#define BIT_CAM_AHB_ISP1_AXI_CKG_EN                                BIT(11)
#define BIT_CAM_AHB_ISP0_AXI_CKG_EN                                BIT(10)
#define BIT_CAM_AHB_JPG1_AXI_CKG_EN                                BIT(9)
#define BIT_CAM_AHB_JPG0_AXI_CKG_EN                                BIT(8)
#define BIT_CAM_AHB_SENSOR1_CKG_EN                                 BIT(7)
#define BIT_CAM_AHB_SENSOR0_CKG_EN                                 BIT(6)
#define BIT_CAM_AHB_DCAM1_AXI_CKG_EN                               BIT(5)
#define BIT_CAM_AHB_DCAM0_AXI_CKG_EN                               BIT(4)
#define BIT_CAM_AHB_MIPI_CSI1_CKG_EN                               BIT(3)
#define BIT_CAM_AHB_CPHY1_CFG_CKG_EN                               BIT(2)
#define BIT_CAM_AHB_MIPI_CSI0_CKG_EN                               BIT(1)
#define BIT_CAM_AHB_CPHY0_CFG_CKG_EN                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_MIPI_CSI_CTRL
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_MIPI_CPHY1_SAMPLE_SEL(x)                       (((x) & 0x3) << 11)
#define BIT_CAM_AHB_MIPI_CPHY1_SYNC_MODE                           BIT(10)
#define BIT_CAM_AHB_MIPI_CPHY1_TEST_CTL                            BIT(9)
#define BIT_CAM_AHB_MIPI_CPHY1_SEL                                 BIT(8)
#define BIT_CAM_AHB_MIPI_CPHY0_SAMPLE_SEL(x)                       (((x) & 0x3) << 3)
#define BIT_CAM_AHB_MIPI_CPHY0_SYNC_MODE                           BIT(2)
#define BIT_CAM_AHB_MIPI_CPHY0_TEST_CTL                            BIT(1)
#define BIT_CAM_AHB_MIPI_CPHY0_SEL                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_NIC0_QOS_CFG0
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_QOS_R_DCAM2ISP(x)                              (((x) & 0xF) << 28)
#define BIT_CAM_AHB_QOS_W_DCAM2ISP(x)                              (((x) & 0xF) << 24)
#define BIT_CAM_AHB_QOS_R_CPP(x)                                   (((x) & 0xF) << 20)
#define BIT_CAM_AHB_QOS_W_CPP(x)                                   (((x) & 0xF) << 16)
#define BIT_CAM_AHB_QOS_R_JPG1(x)                                  (((x) & 0xF) << 12)
#define BIT_CAM_AHB_QOS_W_JPG1(x)                                  (((x) & 0xF) << 8)
#define BIT_CAM_AHB_QOS_R_JPG0(x)                                  (((x) & 0xF) << 4)
#define BIT_CAM_AHB_QOS_W_JPG0(x)                                  (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_NIC0_QOS_CFG1
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_ISPC_SOFT_RST_MASK                             BIT(25)
#define BIT_CAM_AHB_ISPB_SOFT_RST_MASK                             BIT(24)
#define BIT_CAM_AHB_ISPA_SOFT_RST_MASK                             BIT(23)
#define BIT_CAM_AHB_DCAM2ISP_SOFT_RST_MASK                         BIT(22)
#define BIT_CAM_AHB_DCAM1_SOFT_RST_MASK                            BIT(21)
#define BIT_CAM_AHB_DCAM0_SOFT_RST_MASK                            BIT(20)
#define BIT_CAM_AHB_DISPC1_SOFT_RST_MASK                           BIT(19)
#define BIT_CAM_AHB_DISPC0_SOFT_RST_MASK                           BIT(18)
#define BIT_CAM_AHB_CPP_SOFT_RST_MASK                              BIT(17)
#define BIT_CAM_AHB_JPG_SOFT_RST_MASK                              BIT(16)
#define BIT_CAM_AHB_CAM_NIC0_DDR_ADDR_BIT32                        BIT(8)
#define BIT_CAM_AHB_CAM_NIU0_AR_QOS(x)                             (((x) & 0xF) << 4)
#define BIT_CAM_AHB_CAM_NIU0_AW_QOS(x)                             (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_NIC1_QOS_CFG2
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_QOS_R_DCAM1(x)                                 (((x) & 0xF) << 28)
#define BIT_CAM_AHB_QOS_W_DCAM1(x)                                 (((x) & 0xF) << 24)
#define BIT_CAM_AHB_QOS_R_DCAM0(x)                                 (((x) & 0xF) << 20)
#define BIT_CAM_AHB_QOS_W_DCAM0(x)                                 (((x) & 0xF) << 16)
#define BIT_CAM_AHB_QOS_R_ISP1(x)                                  (((x) & 0xF) << 12)
#define BIT_CAM_AHB_QOS_W_ISP1(x)                                  (((x) & 0xF) << 8)
#define BIT_CAM_AHB_QOS_R_ISP0(x)                                  (((x) & 0xF) << 4)
#define BIT_CAM_AHB_QOS_W_ISP0(x)                                  (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_NIC1_QOS_CFG3
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_QOS_R_ISP2(x)                                  (((x) & 0xF) << 20)
#define BIT_CAM_AHB_QOS_W_ISP2(x)                                  (((x) & 0xF) << 16)
#define BIT_CAM_AHB_CAM_NIC1_DDR_ADDR_BIT32                        BIT(8)
#define BIT_CAM_AHB_CAM_NIU1_AR_QOS(x)                             (((x) & 0xF) << 4)
#define BIT_CAM_AHB_CAM_NIU1_AW_QOS(x)                             (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CB_SRC_SEL
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_MIPI_HOST1_CB_CLK_EN                           BIT(1)
#define BIT_CAM_AHB_MIPI_HOST0_CB_CLK_EN                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_BUSMON_CK_EN
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_BUSMON_M2_EB                                   BIT(2)
#define BIT_CAM_AHB_BUSMON_M1_EB                                   BIT(1)
#define BIT_CAM_AHB_BUSMON_M0_EB                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_MODULE_CLK_EN
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_SM_ISPC_IN_ISP_EB                              BIT(9)
#define BIT_CAM_AHB_SM_ISPB_IN_ISP_EB                              BIT(8)
#define BIT_CAM_AHB_SM_ISPA_IN_ISP_EB                              BIT(7)
#define BIT_CAM_AHB_SM_ISPC_IN_DCAM2ISP_EB                         BIT(6)
#define BIT_CAM_AHB_SM_ISPB_IN_DCAM2ISP_EB                         BIT(5)
#define BIT_CAM_AHB_SM_ISPA_IN_DCAM2ISP_EB                         BIT(4)
#define BIT_CAM_AHB_SM_DCAM1_IF_IN_DCAM2ISP_EB                     BIT(3)
#define BIT_CAM_AHB_SM_DCAM0_IF_IN_DCAM2ISP_EB                     BIT(2)
#define BIT_CAM_AHB_SM_DCAM1_IF_IN_DCAM_EB                         BIT(1)
#define BIT_CAM_AHB_SM_DCAM0_IF_IN_DCAM_EB                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_MODULE_SOFT_RST
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_SM_ISPC_IN_ISP_SOFT_RST                        BIT(9)
#define BIT_CAM_AHB_SM_ISPB_IN_ISP_SOFT_RST                        BIT(8)
#define BIT_CAM_AHB_SM_ISPA_IN_ISP_SOFT_RST                        BIT(7)
#define BIT_CAM_AHB_SM_ISPC_IN_DCAM2ISP_SOFT_RST                   BIT(6)
#define BIT_CAM_AHB_SM_ISPB_IN_DCAM2ISP_SOFT_RST                   BIT(5)
#define BIT_CAM_AHB_SM_ISPA_IN_DCAM2ISP_SOFT_RST                   BIT(4)
#define BIT_CAM_AHB_SM_DCAM1_IF_IN_DCAM2ISP_SOFT_RST               BIT(3)
#define BIT_CAM_AHB_SM_DCAM0_IF_IN_DCAM2ISP_SOFT_RST               BIT(2)
#define BIT_CAM_AHB_SM_DCAM1_IF_IN_DCAM_SOFT_RST                   BIT(1)
#define BIT_CAM_AHB_SM_DCAM0_IF_IN_DCAM_SOFT_RST                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AXI_LPC0
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_LP_EB_DCAM0                                    BIT(31)
#define BIT_CAM_AHB_LP_FORCE_DCAM0                                 BIT(30)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_DCAM0                          BIT(29)
#define BIT_CAM_AHB_LP_EB_DCAM1                                    BIT(28)
#define BIT_CAM_AHB_LP_FORCE_DCAM1                                 BIT(27)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_DCAM1                          BIT(26)
#define BIT_CAM_AHB_LP_EB_DCAM2ISP                                 BIT(25)
#define BIT_CAM_AHB_LP_FORCE_DCAM2ISP                              BIT(24)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_DCAM2ISP                       BIT(23)
#define BIT_CAM_AHB_LP_EB_JPG0                                     BIT(22)
#define BIT_CAM_AHB_LP_FORCE_JPG0                                  BIT(21)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_JPG0                           BIT(20)
#define BIT_CAM_AHB_LP_EB_JPG1                                     BIT(19)
#define BIT_CAM_AHB_LP_FORCE_JPG1                                  BIT(18)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_JPG1                           BIT(17)
#define BIT_CAM_AHB_LP_EB_CPP                                      BIT(16)
#define BIT_CAM_AHB_LP_FORCE_CPP                                   BIT(15)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_CPP                            BIT(14)
#define BIT_CAM_AHB_LP_EB_ISPA                                     BIT(13)
#define BIT_CAM_AHB_LP_FORCE_ISPA                                  BIT(12)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_ISPA                           BIT(11)
#define BIT_CAM_AHB_LP_EB_ISPB                                     BIT(10)
#define BIT_CAM_AHB_LP_FORCE_ISPB                                  BIT(9)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_ISPB                           BIT(8)
#define BIT_CAM_AHB_LP_EB_ISPC                                     BIT(7)
#define BIT_CAM_AHB_LP_FORCE_ISPC                                  BIT(6)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_ISPC                           BIT(5)
#define BIT_CAM_AHB_LP_EB_CAM_MMU                                  BIT(4)
#define BIT_CAM_AHB_LP_FORCE_CAM_MMU                               BIT(3)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_CAM_MMU                        BIT(2)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AXI_LPC1
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_LP_EB_CAM_MMU_PF                               BIT(31)
#define BIT_CAM_AHB_LP_FORCE_CAM_MMU_PF                            BIT(30)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_CAM_MMU_PF                     BIT(29)
#define BIT_CAM_AHB_LP_EB_ISP2DCAM_IF0                             BIT(28)
#define BIT_CAM_AHB_LP_FORCE_ISP2DCAM_IF0                          BIT(27)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_ISP2DCAM_IF0                   BIT(26)
#define BIT_CAM_AHB_LP_EB_ISP2DCAM_IF1                             BIT(25)
#define BIT_CAM_AHB_LP_FORCE_ISP2DCAM_IF1                          BIT(24)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_ISP2DCAM_IF1                   BIT(23)
#define BIT_CAM_AHB_LP_EB_CAM_MAIN                                 BIT(22)
#define BIT_CAM_AHB_LP_FORCE_CAM_MAIN                              BIT(21)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_CAM_MAIN                       BIT(20)
#define BIT_CAM_AHB_LP_EB_DISPC0                                   BIT(19)
#define BIT_CAM_AHB_LP_FORCE_DISPC0                                BIT(18)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_DISPC0                         BIT(17)
#define BIT_CAM_AHB_LP_EB_DISPC1                                   BIT(16)
#define BIT_CAM_AHB_LP_FORCE_DISPC1                                BIT(15)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_DISPC1                         BIT(14)
#define BIT_CAM_AHB_LP_EB_DISPC_MTX                                BIT(13)
#define BIT_CAM_AHB_LP_FORCE_DISPC_MTX                             BIT(12)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_DISPC_MTX                      BIT(11)
#define BIT_CAM_AHB_LP_EB_SYS_DISP                                 BIT(10)
#define BIT_CAM_AHB_LP_FORCE_SYS_DISP                              BIT(9)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_SYS_DISP                       BIT(8)
#define BIT_CAM_AHB_LP_EB_SYS_CAM0                                 BIT(7)
#define BIT_CAM_AHB_LP_FORCE_SYS_CAM0                              BIT(6)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_SYS_CAM0                       BIT(5)
#define BIT_CAM_AHB_LP_EB_SYS_CAM1                                 BIT(4)
#define BIT_CAM_AHB_LP_FORCE_SYS_CAM1                              BIT(3)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_SYS_CAM1                       BIT(2)
#define BIT_CAM_AHB_ADDR_CUTOFF_ENABLE_CAM                         BIT(1)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AXI_LPC2
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_LP_EB_SYS_MAIN                                 BIT(31)
#define BIT_CAM_AHB_LP_FORCE_SYS_MAIN                              BIT(30)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_SYS_MAIN                       BIT(29)
#define BIT_CAM_AHB_LP_EB_MTX_NOC                                  BIT(28)
#define BIT_CAM_AHB_LP_FORCE_MTX_NOC                               BIT(27)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_MTX_NOC                        BIT(26)
#define BIT_CAM_AHB_LP_EB_CAM_PUB0                                 BIT(25)
#define BIT_CAM_AHB_LP_FORCE_CAM_PUB0                              BIT(24)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_CAM_PUB0                       BIT(23)
#define BIT_CAM_AHB_LP_EB_CAM_PUB1                                 BIT(22)
#define BIT_CAM_AHB_LP_FORCE_CAM_PUB1                              BIT(21)
#define BIT_CAM_AHB_ACTIVE_SYNC_SEL_CAM_PUB1                       BIT(20)
#define BIT_CAM_AHB_LP_NUM_CAM_TOP(x)                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AXI_LPC3
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_LP_NUM_DISP_TOP(x)                             (((x) & 0xFFFF) << 16)
#define BIT_CAM_AHB_LP_NUM_CAM_SYS(x)                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AXI_LPC4
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_LP_NUM_CAM_NOC(x)                              (((x) & 0xFFFF) << 16)
#define BIT_CAM_AHB_LP_NUM_CAM_AB(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AB0_CTRL0
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_AXI_DETECTOR_OVERFLOW_CH0                      BIT(31)
#define BIT_CAM_AHB_BRIDGE_TRANS_IDLE_CH0                          BIT(30)
#define BIT_CAM_AHB_BRIDGE_FIFO_FULL_CH0                           BIT(29)
#define BIT_CAM_AHB_BRIDGE_WFIFO_FULL_CH0                          BIT(28)
#define BIT_CAM_AHB_BRIDGE_RFIFO_FULL_CH0                          BIT(27)
#define BIT_CAM_AHB_FIFO_AF_LVL_AW_CH0(x)                          (((x) & 0x3F) << 20)
#define BIT_CAM_AHB_FIFO_AE_LVL_AW_CH0(x)                          (((x) & 0x3F) << 14)
#define BIT_CAM_AHB_FIFO_AF_LVL_W_CH0(x)                           (((x) & 0x3F) << 8)
#define BIT_CAM_AHB_FIFO_AE_LVL_W_CH0(x)                           (((x) & 0x3F) << 2)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AB0_CTRL1
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_FIFO_AF_LVL_B_CH0(x)                           (((x) & 0x3F) << 24)
#define BIT_CAM_AHB_FIFO_AE_LVL_B_CH0(x)                           (((x) & 0x3F) << 18)
#define BIT_CAM_AHB_FIFO_AF_LVL_AR_CH0(x)                          (((x) & 0x3F) << 12)
#define BIT_CAM_AHB_FIFO_AE_LVL_AR_CH0(x)                          (((x) & 0x3F) << 6)
#define BIT_CAM_AHB_FIFO_AF_LVL_R_CH0(x)                           (((x) & 0x3F))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AB0_CTRL2
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_FIFO_AE_LVL_R_CH0(x)                           (((x) & 0x3F))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AB1_CTRL0
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_AXI_DETECTOR_OVERFLOW_CH1                      BIT(31)
#define BIT_CAM_AHB_BRIDGE_TRANS_IDLE_CH1                          BIT(30)
#define BIT_CAM_AHB_BRIDGE_FIFO_FULL_CH1                           BIT(29)
#define BIT_CAM_AHB_BRIDGE_WFIFO_FULL_CH1                          BIT(28)
#define BIT_CAM_AHB_BRIDGE_RFIFO_FULL_CH1                          BIT(27)
#define BIT_CAM_AHB_FIFO_AF_LVL_AW_CH1(x)                          (((x) & 0x3F) << 20)
#define BIT_CAM_AHB_FIFO_AE_LVL_AW_CH1(x)                          (((x) & 0x3F) << 14)
#define BIT_CAM_AHB_FIFO_AF_LVL_W_CH1(x)                           (((x) & 0x3F) << 8)
#define BIT_CAM_AHB_FIFO_AE_LVL_W_CH1(x)                           (((x) & 0x3F) << 2)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AB1_CTRL1
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_FIFO_AF_LVL_B_CH1(x)                           (((x) & 0x3F) << 24)
#define BIT_CAM_AHB_FIFO_AE_LVL_B_CH1(x)                           (((x) & 0x3F) << 18)
#define BIT_CAM_AHB_FIFO_AF_LVL_AR_CH1(x)                          (((x) & 0x3F) << 12)
#define BIT_CAM_AHB_FIFO_AE_LVL_AR_CH1(x)                          (((x) & 0x3F) << 6)
#define BIT_CAM_AHB_FIFO_AF_LVL_R_CH1(x)                           (((x) & 0x3F))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AB1_CTRL2
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_FIFO_AE_LVL_R_CH1(x)                           (((x) & 0x3F))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AB0_DBG
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_CAM_AB0_DBG_SIGNAL(x)                          (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_CAM_AB1_DBG
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_CAM_AB1_DBG_SIGNAL(x)                          (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_DSI0_CNT_CTRL
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_DSI0_DLN_TIMER_VALUE(x)                        (((x) & 0x1FF) << 9)
#define BIT_CAM_AHB_DSI0_CLN_TIMER_VALUE(x)                        (((x) & 0x1FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_DSI1_CNT_CTRL
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_DSI1_DLN_TIMER_VALUE(x)                        (((x) & 0x1FF) << 9)
#define BIT_CAM_AHB_DSI1_CLN_TIMER_VALUE(x)                        (((x) & 0x1FF))


#endif // _CAM_AHB_REG_H
