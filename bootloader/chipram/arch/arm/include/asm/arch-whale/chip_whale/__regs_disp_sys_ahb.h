/* the head file modifier:     g   2014-12-04 14:10:54*/

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
#ifndef __H_REGS_DISP_AHB_HEADFILE_H__
#define __H_REGS_DISP_AHB_HEADFILE_H__ __FILE__

#define  REGS_DISP_AHB

/* registers definitions for DISP_AHB */
#define REG_DISP_AHB_AHB_EB				SCI_ADDR(REGS_DISP_AHB_BASE, 0x0000)/*AHB clock enable*/
#define REG_DISP_AHB_AHB_RST				SCI_ADDR(REGS_DISP_AHB_BASE, 0x0004)/*AHB soft reset*/
#define REG_DISP_AHB_DPHY_CKG_CFG			SCI_ADDR(REGS_DISP_AHB_BASE, 0x0008)/*clock enable*/
#define REG_DISP_AHB_DISPC_QOS_CFG0			SCI_ADDR(REGS_DISP_AHB_BASE, 0x0018)/*DISPC Matrix QOS config0*/
#define REG_DISP_AHB_DISPC_QOS_CFG1			SCI_ADDR(REGS_DISP_AHB_BASE, 0x001C)/*DISPC Matrix QOS config1*/
#define REG_DISP_AHB_MISC_CTRL				SCI_ADDR(REGS_DISP_AHB_BASE, 0x0020)/*MISC control*/



/* bits definitions for register REG_DISP_AHB_AHB_EB */
#define BIT_DISP_AHB_DISPC_MTX_EB				(BIT(16))
#define BIT_DISP_AHB_TMC_MTX_EB					(BIT(15))
#define BIT_DISP_AHB_GSP_MTX_EB					(BIT(14))
#define BIT_DISP_AHB_GPU_MTX_EB					(BIT(13))
#define BIT_DISP_AHB_VPP_EB					(BIT(12))
#define BIT_DISP_AHB_VPP_MMU_EB					(BIT(11))
#define BIT_DISP_AHB_GPU_EB					(BIT(10))
#define BIT_DISP_AHB_CKG_EB					(BIT(9))
#define BIT_DISP_AHB_DSI1_EB					(BIT(8))
#define BIT_DISP_AHB_DSI0_EB					(BIT(7))
#define BIT_DISP_AHB_GSP1_MMU_EB				(BIT(6))
#define BIT_DISP_AHB_GSP0_MMU_EB				(BIT(5))
#define BIT_DISP_AHB_GSP1_EB					(BIT(4))
#define BIT_DISP_AHB_GSP0_EB					(BIT(3))
#define BIT_DISP_AHB_DISPC_MMU_EB				(BIT(2))
#define BIT_DISP_AHB_DISPC1_EB					(BIT(1))
#define BIT_DISP_AHB_DISPC0_EB					(BIT(0))

/* bits definitions for register REG_DISP_AHB_AHB_RST */
#define BIT_DISP_AHB_GSP_MTX_SOFT_RST				(BIT(15))
#define BIT_DISP_AHB_VPP_SOFT_RST				(BIT(14))
#define BIT_DISP_AHB_VPP_MMU_SOFT_RST				(BIT(13))
#define BIT_DISP_AHB_DISPC0_ENC_SOFT_RST			(BIT(12))
#define BIT_DISP_AHB_DISPC_MTX_SOFT_RST				(BIT(11))
#define BIT_DISP_AHB_CKG_SOFT_RST				(BIT(10))
#define BIT_DISP_AHB_DISPC0_LVDS_SOFT_RST			(BIT(9))
#define BIT_DISP_AHB_DSI1_SOFT_RST				(BIT(8))
#define BIT_DISP_AHB_DSI0_SOFT_RST				(BIT(7))
#define BIT_DISP_AHB_GSP1_MMU_SOFT_RST				(BIT(6))
#define BIT_DISP_AHB_GSP0_MMU_SOFT_RST				(BIT(5))
#define BIT_DISP_AHB_GSP1_SOFT_RST				(BIT(4))
#define BIT_DISP_AHB_GSP0_SOFT_RST				(BIT(3))
#define BIT_DISP_AHB_DISPC_MMU_SOFT_RST				(BIT(2))
#define BIT_DISP_AHB_DISPC1_SOFT_RST				(BIT(1))
#define BIT_DISP_AHB_DISPC0_SOFT_RST				(BIT(0))

/* bits definitions for register REG_DISP_AHB_GEN_CKG_CFG */
#define BIT_DISP_AHB_GSP_NOC_AUTO_CKG_EN			(BIT(13))
#define BIT_DISP_AHB_GSP_NOC_FORCE_CKG_EN			(BIT(12))
#define BIT_DISP_AHB_GSP_MTX_AUTO_CKG_EN			(BIT(11))
#define BIT_DISP_AHB_GSP_MTX_FORCE_CKG_EN			(BIT(10))
#define BIT_DISP_AHB_DISPC_NOC_AUTO_CKG_EN			(BIT(9))
#define BIT_DISP_AHB_DISPC_NOC_FORCE_CKG_EN			(BIT(8))
#define BIT_DISP_AHB_DISPC_MTX_AUTO_CKG_EN			(BIT(7))
#define BIT_DISP_AHB_DISPC_MTX_FORCE_CKG_EN			(BIT(6))
#define BIT_DISP_AHB_GSP1_FORCE_CKG_EN				(BIT(5))
#define BIT_DISP_AHB_GSP0_FORCE_CKG_EN				(BIT(4))
#define BIT_DISP_AHB_GSP1_AUTO_CKG_EN				(BIT(3))
#define BIT_DISP_AHB_GSP0_AUTO_CKG_EN				(BIT(2))
#define BIT_DISP_AHB_DPHY1_CFG_CKG_EN				(BIT(1))
#define BIT_DISP_AHB_DPHY0_CFG_CKG_EN				(BIT(0))

/* bits definitions for register REG_DISP_AHB_DISPC_QOS_CFG0 */
#define BITS_DISP_AHB_QOS_R_GSP1(_X_)				((_X_) << 28 & (BIT(28)|BIT(29)|BIT(30)|BIT(31)))
#define BITS_DISP_AHB_QOS_W_GSP1(_X_)				((_X_) << 24 & (BIT(24)|BIT(25)|BIT(26)|BIT(27)))
#define BITS_DISP_AHB_QOS_R_GSP0(_X_)				((_X_) << 20 & (BIT(20)|BIT(21)|BIT(22)|BIT(23)))
#define BITS_DISP_AHB_QOS_W_GSP0(_X_)				((_X_) << 16 & (BIT(16)|BIT(17)|BIT(18)|BIT(19)))
#define BITS_DISP_AHB_QOS_R_DISPC1(_X_)				((_X_) << 12 & (BIT(12)|BIT(13)|BIT(14)|BIT(15)))
#define BITS_DISP_AHB_QOS_W_DISPC1(_X_)				((_X_) << 8 & (BIT(8)|BIT(9)|BIT(10)|BIT(11)))
#define BITS_DISP_AHB_QOS_R_DISPC0(_X_)				((_X_) << 4 & (BIT(4)|BIT(5)|BIT(6)|BIT(7)))
#define BITS_DISP_AHB_QOS_W_DISPC0(_X_)				((_X_) & (BIT(0)|BIT(1)|BIT(2)|BIT(3)))

/* bits definitions for register REG_DISP_AHB_DISPC_QOS_CFG1 */
#define BITS_DISP_AHB_QOS_R_GPU(_X_)				((_X_) << 4 & (BIT(4)|BIT(5)|BIT(6)|BIT(7)))
#define BITS_DISP_AHB_QOS_W_GPU(_X_)				((_X_) & (BIT(0)|BIT(1)|BIT(2)|BIT(3)))

/* bits definitions for register REG_DISP_AHB_MISC_CTRL */
#define BITS_DISP_AHB_GSP_NIU_AR_QOS(_X_)			((_X_) << 16 & (BIT(16)|BIT(17)|BIT(18)|BIT(19)))
#define BITS_DISP_AHB_GSP_NIU_AW_QOS(_X_)			((_X_) << 12 & (BIT(12)|BIT(13)|BIT(14)|BIT(15)))
#define BITS_DISP_AHB_DISPC_NIU_AR_QOS(_X_)			((_X_) << 8 & (BIT(8)|BIT(9)|BIT(10)|BIT(11)))
#define BITS_DISP_AHB_DISPC_NIU_AW_QOS(_X_)			((_X_) << 4 & (BIT(4)|BIT(5)|BIT(6)|BIT(7)))
#define BIT_DISP_AHB_GSP_DDR_ADDR_BIT32				(BIT(1))
#define BIT_DISP_AHB_DISPC_DDR_ADDR_BIT32			(BIT(0))

#endif
