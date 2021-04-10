/* the head file modifier:     g   2014-12-04 14:12:53*/

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
#ifndef __H_REGS_VSP_AHB_HEADFILE_H__
#define __H_REGS_VSP_AHB_HEADFILE_H__ __FILE__

#define  REGS_VSP_AHB

/* registers definitions for VSP_AHB */
#define REG_VSP_AHB_AHB_EB				SCI_ADDR(REGS_VSP_AHB_BASE, 0x0000)/*AHB_EB*/
#define REG_VSP_AHB_AHB_RST				SCI_ADDR(REGS_VSP_AHB_BASE, 0x0004)/*AHB_RST*/
#define REG_VSP_AHB_GEN_CKG_CFG				SCI_ADDR(REGS_VSP_AHB_BASE, 0x0008)/*GEN_CKG_CFG*/



/* bits definitions for register REG_VSP_AHB_AHB_EB */
#define BIT_VSP_AHB_MMU_EB					(BIT(2))
#define BIT_VSP_AHB_CKG_EB					(BIT(1))
#define BIT_VSP_AHB_VSP_EB					(BIT(0))

/* bits definitions for register REG_VSP_AHB_AHB_RST */
#define BIT_VSP_AHB_MMU_SOFT_RST				(BIT(3))
#define BIT_VSP_AHB_CKG_SOFT_RST				(BIT(2))
#define BIT_VSP_AHB_OR1200_SOFT_RST				(BIT(1))
#define BIT_VSP_AHB_VSP_SOFT_RST				(BIT(0))

/* bits definitions for register REG_VSP_AHB_GEN_CKG_CFG */
#define BIT_VSP_AHB_VSP_AXI_CKG_EN				(BIT(0))

#endif
