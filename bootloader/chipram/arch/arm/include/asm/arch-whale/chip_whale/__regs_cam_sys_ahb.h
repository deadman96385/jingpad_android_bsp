/* the head file modifier:     g   2014-12-04 14:15:18*/

/*  
* Copyright (C) 2013 Spreadtrum Communications Inc.  
*
* This program is free software; you can redistribute it and/or  
* modify it under the terms of the GNU General Public License 
* as published by the Free Software Foundation; either version 2 
* of the License, or (at your option) any later version.  
* 
* This program is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty of 
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  
* GNU General Public License for more details.  
* 
*************************************************  
* Automatically generated C header: do not edit *  
*************************************************  
*/  
#ifndef __H_REGS_CAM_AHB_HEADFILE_H__
#define __H_REGS_CAM_AHB_HEADFILE_H__ 

#define  REGS_CAM_AHB

/* registers definitions for CAM_AHB */
#define REG_CAM_AHB_AHB_EB				SCI_ADDR(REGS_CAM_AHB_BASE, 0x0000)/*AHB clock enable*/
#define REG_CAM_AHB_AHB_RST				SCI_ADDR(REGS_CAM_AHB_BASE, 0x0004)/*AHB soft reset*/
#define REG_CAM_AHB_GEN_CKG_CFG				SCI_ADDR(REGS_CAM_AHB_BASE, 0x0008)/*clock enable*/
#define REG_CAM_AHB_MIPI_CSI_CTRL			SCI_ADDR(REGS_CAM_AHB_BASE, 0x000C)/*MIPI CSI PHY control*/
#define REG_CAM_AHB_MM_QOS_CFG0				SCI_ADDR(REGS_CAM_AHB_BASE, 0x0010)/*Matrix QOS config0*/
#define REG_CAM_AHB_MM_QOS_CFG1				SCI_ADDR(REGS_CAM_AHB_BASE, 0x0014)/*Matrix QOS config0*/



/* bits definitions for register REG_CAM_AHB_AHB_EB */
#define BIT_CAM_AHB_MMU_EB					(BIT(8))
#define BIT_CAM_AHB_CKG_EB					(BIT(7))
#define BIT_CAM_AHB_JPG1_EB					(BIT(6))
#define BIT_CAM_AHB_JPG0_EB					(BIT(5))
#define BIT_CAM_AHB_CSI1_EB					(BIT(4))
#define BIT_CAM_AHB_CSI0_EB					(BIT(3))
#define BIT_CAM_AHB_ISP_EB					(BIT(2))
#define BIT_CAM_AHB_DCAM1_EB					(BIT(1))
#define BIT_CAM_AHB_DCAM0_EB					(BIT(0))

/* bits definitions for register REG_CAM_AHB_AHB_RST */
#define BIT_CAM_AHB_CCIR_SOFT_RST				(BIT(18))
#define BIT_CAM_AHB_MMU_SOFT_RST				(BIT(17))
#define BIT_CAM_AHB_CKG_SOFT_RST				(BIT(16))
#define BIT_CAM_AHB_DCAM1_ROT_SOFT_RST				(BIT(15))
#define BIT_CAM_AHB_DCAM1_CAM2_SOFT_RST				(BIT(14))
#define BIT_CAM_AHB_DCAM1_CAM1_SOFT_RST				(BIT(13))
#define BIT_CAM_AHB_DCAM1_CAM0_SOFT_RST				(BIT(12))
#define BIT_CAM_AHB_DCAM0_ROT_SOFT_RST				(BIT(11))
#define BIT_CAM_AHB_DCAM0_CAM2_SOFT_RST				(BIT(10))
#define BIT_CAM_AHB_DCAM0_CAM1_SOFT_RST				(BIT(9))
#define BIT_CAM_AHB_DCAM0_CAM0_SOFT_RST				(BIT(8))
#define BIT_CAM_AHB_JPG1_SOFT_RST				(BIT(7))
#define BIT_CAM_AHB_JPG0_SOFT_RST				(BIT(6))
#define BIT_CAM_AHB_CSI1_SOFT_RST				(BIT(5))
#define BIT_CAM_AHB_CSI0_SOFT_RST				(BIT(4))
#define BIT_CAM_AHB_ISP_CFG_SOFT_RST				(BIT(3))
#define BIT_CAM_AHB_ISP_LOG_SOFT_RST				(BIT(2))
#define BIT_CAM_AHB_DCAM1_SOFT_RST				(BIT(1))
#define BIT_CAM_AHB_DCAM0_SOFT_RST				(BIT(0))

/* bits definitions for register REG_CAM_AHB_GEN_CKG_CFG */
#define BIT_CAM_AHB_ISP_AXI_CKG_EN				(BIT(10))
#define BIT_CAM_AHB_JPG1_AXI_CKG_EN				(BIT(9))
#define BIT_CAM_AHB_JPG0_AXI_CKG_EN				(BIT(8))
#define BIT_CAM_AHB_SENSOR1_CKG_EN				(BIT(7))
#define BIT_CAM_AHB_SENSOR0_CKG_EN				(BIT(6))
#define BIT_CAM_AHB_DCAM1_AXI_CKG_EN				(BIT(5))
#define BIT_CAM_AHB_DCAM0_AXI_CKG_EN				(BIT(4))
#define BIT_CAM_AHB_MIPI_CSI1_CKG_EN				(BIT(3))
#define BIT_CAM_AHB_CPHY1_CFG_CKG_EN				(BIT(2))
#define BIT_CAM_AHB_MIPI_CSI0_CKG_EN				(BIT(1))
#define BIT_CAM_AHB_CPHY0_CFG_CKG_EN				(BIT(0))

/* bits definitions for register REG_CAM_AHB_MIPI_CSI_CTRL */
#define BITS_CAM_AHB_MIPI_CPHY1_SAMPLE_SEL(_X_)			((_X_) << 11 & (BIT(11)|BIT(12)))
#define BIT_CAM_AHB_MIPI_CPHY1_SYNC_MODE			(BIT(10))
#define BIT_CAM_AHB_MIPI_CPHY1_TEST_CTL				(BIT(9))
#define BIT_CAM_AHB_MIPI_CPHY1_SEL				(BIT(8))
#define BITS_CAM_AHB_MIPI_CPHY0_SAMPLE_SEL(_X_)			((_X_) << 3 & (BIT(3)|BIT(4)))
#define BIT_CAM_AHB_MIPI_CPHY0_SYNC_MODE			(BIT(2))
#define BIT_CAM_AHB_MIPI_CPHY0_TEST_CTL				(BIT(1))
#define BIT_CAM_AHB_MIPI_CPHY0_SEL				(BIT(0))

/* bits definitions for register REG_CAM_AHB_MM_QOS_CFG0 */
#define BITS_CAM_AHB_QOS_R_DCAM1(_X_)				((_X_) << 28 & (BIT(28)|BIT(29)|BIT(30)|BIT(31)))
#define BITS_CAM_AHB_QOS_W_DCAM1(_X_)				((_X_) << 24 & (BIT(24)|BIT(25)|BIT(26)|BIT(27)))
#define BITS_CAM_AHB_QOS_R_DCAM0(_X_)				((_X_) << 20 & (BIT(20)|BIT(21)|BIT(22)|BIT(23)))
#define BITS_CAM_AHB_QOS_W_DCAM0(_X_)				((_X_) << 16 & (BIT(16)|BIT(17)|BIT(18)|BIT(19)))
#define BITS_CAM_AHB_QOS_R_JPG1(_X_)				((_X_) << 12 & (BIT(12)|BIT(13)|BIT(14)|BIT(15)))
#define BITS_CAM_AHB_QOS_W_JPG1(_X_)				((_X_) << 8 & (BIT(8)|BIT(9)|BIT(10)|BIT(11)))
#define BITS_CAM_AHB_QOS_R_JPG0(_X_)				((_X_) << 4 & (BIT(4)|BIT(5)|BIT(6)|BIT(7)))
#define BITS_CAM_AHB_QOS_W_JPG0(_X_)				((_X_) & (BIT(0)|BIT(1)|BIT(2)|BIT(3)))

/* bits definitions for register REG_CAM_AHB_MM_QOS_CFG1 */
#define BIT_CAM_AHB_CAM_DDR_ADDR_BIT32				(BIT(16))
#define BITS_CAM_AHB_CAM_NIU_AR_QOS(_X_)			((_X_) << 12 & (BIT(12)|BIT(13)|BIT(14)|BIT(15)))
#define BITS_CAM_AHB_CAM_NIU_AW_QOS(_X_)			((_X_) << 8 & (BIT(8)|BIT(9)|BIT(10)|BIT(11)))
#define BITS_CAM_AHB_QOS_R_ISP(_X_)				((_X_) << 4 & (BIT(4)|BIT(5)|BIT(6)|BIT(7)))
#define BITS_CAM_AHB_QOS_W_ISP(_X_)				((_X_) & (BIT(0)|BIT(1)|BIT(2)|BIT(3)))

#endif
