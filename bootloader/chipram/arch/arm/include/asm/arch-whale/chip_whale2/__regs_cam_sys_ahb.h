/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */

#ifndef __H_REGS_CAM_AHB_HEADFILE_H__
#define __H_REGS_CAM_AHB_HEADFILE_H__ 



#define REG_CAM_AHB_AHB_EB         SCI_ADDR(REGS_CAM_AHB_BASE, 0x0000 )
#define REG_CAM_AHB_AHB_RST        SCI_ADDR(REGS_CAM_AHB_BASE, 0x0004 )
#define REG_CAM_AHB_GEN_CKG_CFG    SCI_ADDR(REGS_CAM_AHB_BASE, 0x0008 )
#define REG_CAM_AHB_MIPI_CSI_CTRL  SCI_ADDR(REGS_CAM_AHB_BASE, 0x000C )
#define REG_CAM_AHB_NIC0_QOS_CFG0        SCI_ADDR(REGS_CAM_AHB_BASE, 0x0010 )
#define REG_CAM_AHB_NIC0_QOS_CFG1        SCI_ADDR(REGS_CAM_AHB_BASE, 0x0014 )
#define REG_CAM_AHB_NIC1_QOS_CFG2        SCI_ADDR(REGS_CAM_AHB_BASE, 0x0018 )
#define REG_CAM_AHB_NIC1_QOS_CFG3        SCI_ADDR(REGS_CAM_AHB_BASE, 0x001C )
#define REG_CAM_AHB_CB_SRC_SEL           SCI_ADDR(REGS_CAM_AHB_BASE, 0x0020 )
#define REG_CAM_AHB_BUSMON_CK_EN         SCI_ADDR(REGS_CAM_AHB_BASE, 0x0024 )
#define REG_CAM_AHB_MODULE_CLK_EN        SCI_ADDR(REGS_CAM_AHB_BASE, 0x0028 )
#define REG_CAM_AHB_MODULE_SOFT_RST      SCI_ADDR(REGS_CAM_AHB_BASE, 0x002C )

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_AHB_EB
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_CLK26M_IF_EB                                   BIT(21)
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
#define BIT_CAM_AHB_MMU_EB                              BIT(8)
#define BIT_CAM_AHB_CKG_EB                              BIT(7)
#define BIT_CAM_AHB_JPG1_EB                             BIT(6)
#define BIT_CAM_AHB_JPG0_EB                             BIT(5)
#define BIT_CAM_AHB_CSI1_EB                             BIT(4)
#define BIT_CAM_AHB_CSI0_EB                             BIT(3)
#define BIT_CAM_AHB_ISP0_EB                                        BIT(2)
#define BIT_CAM_AHB_DCAM1_EB                            BIT(1)
#define BIT_CAM_AHB_DCAM0_EB                            BIT(0)

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
#define BIT_CAM_AHB_CCIR_SOFT_RST                       BIT(18)
#define BIT_CAM_AHB_MMU_SOFT_RST                        BIT(17)
#define BIT_CAM_AHB_CKG_SOFT_RST                        BIT(16)
#define BIT_CAM_AHB_DCAM1_ROT_SOFT_RST                  BIT(15)
#define BIT_CAM_AHB_DCAM1_CAM2_SOFT_RST                 BIT(14)
#define BIT_CAM_AHB_DCAM1_CAM1_SOFT_RST                 BIT(13)
#define BIT_CAM_AHB_DCAM1_CAM0_SOFT_RST                 BIT(12)
#define BIT_CAM_AHB_DCAM0_ROT_SOFT_RST                  BIT(11)
#define BIT_CAM_AHB_DCAM0_CAM2_SOFT_RST                 BIT(10)
#define BIT_CAM_AHB_DCAM0_CAM1_SOFT_RST                 BIT(9)
#define BIT_CAM_AHB_DCAM0_CAM0_SOFT_RST                 BIT(8)
#define BIT_CAM_AHB_JPG1_SOFT_RST                       BIT(7)
#define BIT_CAM_AHB_JPG0_SOFT_RST                       BIT(6)
#define BIT_CAM_AHB_CSI1_SOFT_RST                       BIT(5)
#define BIT_CAM_AHB_CSI0_SOFT_RST                       BIT(4)
#define BIT_CAM_AHB_ISP0_CFG_SOFT_RST                              BIT(3)
#define BIT_CAM_AHB_ISP0_LOG_SOFT_RST                              BIT(2)
#define BIT_CAM_AHB_DCAM1_SOFT_RST                      BIT(1)
#define BIT_CAM_AHB_DCAM0_SOFT_RST                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_GEN_CKG_CFG
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_SENSOR2_CKG_EN                                 BIT(18)
#define BIT_CAM_AHB_SPARE_AXI_CKG_EN                               BIT(17)
#define BIT_CAM_AHB_ISP2DCAM_IF_AXI_CKG_EN                         BIT(16)
#define BIT_CAM_AHB_DCAM2ISP_IF_AXI_CKG_EN                         BIT(15)
#define BIT_CAM_AHB_DCAM0_IF_CKG_EN                                BIT(14)
#define BIT_CAM_AHB_CPP_AXI_CKG_EN                                 BIT(13)
#define BIT_CAM_AHB_ISP2_AXI_CKG_EN                                BIT(12)
#define BIT_CAM_AHB_ISP1_AXI_CKG_EN                                BIT(11)
#define BIT_CAM_AHB_ISP0_AXI_CKG_EN                                BIT(10)
#define BIT_CAM_AHB_JPG1_AXI_CKG_EN                     BIT(9)
#define BIT_CAM_AHB_JPG0_AXI_CKG_EN                     BIT(8)
#define BIT_CAM_AHB_SENSOR1_CKG_EN                      BIT(7)
#define BIT_CAM_AHB_SENSOR0_CKG_EN                      BIT(6)
#define BIT_CAM_AHB_DCAM1_AXI_CKG_EN                    BIT(5)
#define BIT_CAM_AHB_DCAM0_AXI_CKG_EN                    BIT(4)
#define BIT_CAM_AHB_MIPI_CSI1_CKG_EN                    BIT(3)
#define BIT_CAM_AHB_CPHY1_CFG_CKG_EN                    BIT(2)
#define BIT_CAM_AHB_MIPI_CSI0_CKG_EN                    BIT(1)
#define BIT_CAM_AHB_CPHY0_CFG_CKG_EN                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_MIPI_CSI_CTRL
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_MIPI_CPHY1_SAMPLE_SEL(x)            (((x) & 0x3) << 11)
#define BIT_CAM_AHB_MIPI_CPHY1_SYNC_MODE                BIT(10)
#define BIT_CAM_AHB_MIPI_CPHY1_TEST_CTL                 BIT(9)
#define BIT_CAM_AHB_MIPI_CPHY1_SEL                      BIT(8)
#define BIT_CAM_AHB_MIPI_CPHY0_SAMPLE_SEL(x)            (((x) & 0x3) << 3)
#define BIT_CAM_AHB_MIPI_CPHY0_SYNC_MODE                BIT(2)
#define BIT_CAM_AHB_MIPI_CPHY0_TEST_CTL                 BIT(1)
#define BIT_CAM_AHB_MIPI_CPHY0_SEL                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_MM_QOS_CFG0
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CAM_AHB_QOS_R_DCAM2ISP(x)                              (((x) & 0xF) << 28)
#define BIT_CAM_AHB_QOS_W_DCAM2ISP(x)                              (((x) & 0xF) << 24)
#define BIT_CAM_AHB_QOS_R_CPP(x)                                   (((x) & 0xF) << 20)
#define BIT_CAM_AHB_QOS_W_CPP(x)                                   (((x) & 0xF) << 16)
#define BIT_CAM_AHB_QOS_R_JPG1(x)                       (((x) & 0xF) << 12)
#define BIT_CAM_AHB_QOS_W_JPG1(x)                       (((x) & 0xF) << 8)
#define BIT_CAM_AHB_QOS_R_JPG0(x)                       (((x) & 0xF) << 4)
#define BIT_CAM_AHB_QOS_W_JPG0(x)                       (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_CAM_AHB_MM_QOS_CFG1
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

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

#define BIT_CAM_AHB_BUSMON_M8_EB                                   BIT(8)
#define BIT_CAM_AHB_BUSMON_M7_EB                                   BIT(7)
#define BIT_CAM_AHB_BUSMON_M6_EB                                   BIT(6)
#define BIT_CAM_AHB_BUSMON_M5_EB                                   BIT(5)
#define BIT_CAM_AHB_BUSMON_M4_EB                                   BIT(4)
#define BIT_CAM_AHB_BUSMON_M3_EB                                   BIT(3)
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

#endif
