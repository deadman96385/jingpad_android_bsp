/* the head file modifier:     g   2014-12-04 14:26:12*/

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
#ifndef __H_REGS_AON_SEC_HEADFILE_H__
#define __H_REGS_AON_SEC_HEADFILE_H__ __FILE__



#define REGS_AON_SEC_APB_BASE 0x40880000
/* registers definitions for AON_SEC_APB */
#define REG_AON_SEC_APB_CHIP_KPRTL_0			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0000)/*CHIP_KPRTL_0*/
#define REG_AON_SEC_APB_CHIP_KPRTL_1			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0004)/*CHIP_KPRTL_1*/
#define REG_AON_SEC_APB_CHIP_KPRTL_2			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0008)/*CHIP_KPRTL_2*/
#define REG_AON_SEC_APB_CHIP_KPRTL_3			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x000c)/*CHIP_KPRTL_3*/
#define REG_AON_SEC_APB_SEC_EB				SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0010)/*SEC_EB*/
#define REG_AON_SEC_APB_SEC_SOFT_RST			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0014)/*SEC_SOFT_RST*/
#define REG_AON_SEC_APB_CA53_CFG_CTRL			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0018)/*CA53 configuration control*/
#define REG_AON_SEC_APB_CA53_SOFT_RST			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x001C)/*CA53 software reset control register*/
#define REG_AON_SEC_APB_CA53_LIT_CLK_CFG		SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0020)/*CA53 LIT Clock control register*/
#define REG_AON_SEC_APB_CA53_BIG_CLK_CFG		SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0024)/*CA53 BIG Clock control register*/
#define REG_AON_SEC_APB_CA53_TOP_CLK_CFG		SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0028)/*CA53 TOP Clock control register*/
#define REG_AON_SEC_APB_CCI_CFG0			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x002C)/*CCI configuration0*/
#define REG_AON_SEC_APB_CCI_CFG1			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0030)/*CCI configuration1*/
#define REG_AON_SEC_APB_RVBARADDR0_LIT			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0034)/*RVBARADDR0_LIT*/
#define REG_AON_SEC_APB_RVBARADDR1_LIT			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0038)/*RVBARADDR1_LIT*/
#define REG_AON_SEC_APB_RVBARADDR2_LIT			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x003C)/*RVBARADDR2_LIT*/
#define REG_AON_SEC_APB_RVBARADDR3_LIT			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0040)/*RVBARADDR3_LIT*/
#define REG_AON_SEC_APB_RVBARADDR0_BIG			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0044)/*RVBARADDR0_BIG*/
#define REG_AON_SEC_APB_RVBARADDR1_BIG			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0048)/*RVBARADDR1_BIG*/
#define REG_AON_SEC_APB_RVBARADDR2_BIG			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x004C)/*RVBARADDR2_BIG*/
#define REG_AON_SEC_APB_RVBARADDR3_BIG			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0050)/*RVBARADDR3_BIG*/
#define REG_AON_SEC_APB_CA53_NOC_CTRL			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0054)/*CA53_NOC_CTRL*/
#define REG_AON_SEC_APB_AP_NOC_CTRL			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0058)/*AP_NOC_CTRL*/



/* bits definitions for register REG_AON_SEC_APB_CHIP_KPRTL_0 */
#define BITS_AON_SEC_APB_KPRTL_0(_X_)				(_X_)

/* bits definitions for register REG_AON_SEC_APB_CHIP_KPRTL_1 */
#define BITS_AON_SEC_APB_KPRTL_1(_X_)				(_X_)

/* bits definitions for register REG_AON_SEC_APB_CHIP_KPRTL_2 */
#define BITS_AON_SEC_APB_KPRTL_2(_X_)				(_X_)

/* bits definitions for register REG_AON_SEC_APB_CHIP_KPRTL_3 */
#define BITS_AON_SEC_APB_KPRTL_3(_X_)				(_X_)

/* bits definitions for register REG_AON_SEC_APB_SEC_EB */
#define BIT_AON_SEC_APB_SEC_RTC_CLK_GATE_EB			(BIT(7))
#define BIT_AON_SEC_APB_SEC_GPIO_EB				(BIT(6))
#define BIT_AON_SEC_APB_SEC_WDG_EB				(BIT(5))
#define BIT_AON_SEC_APB_SEC_WDG_RTC_EB				(BIT(4))
#define BIT_AON_SEC_APB_SEC_RTC_EB				(BIT(3))
#define BIT_AON_SEC_APB_SEC_TMR0_EB				(BIT(2))
#define BIT_AON_SEC_APB_SEC_TMR0_RTC_EB				(BIT(1))
#define BIT_AON_SEC_APB_SEC_TZPC_EB				(BIT(0))

/* bits definitions for register REG_AON_SEC_APB_SEC_SOFT_RST */
#define BIT_AON_SEC_APB_SEC_GPIO_SOFT_RST			(BIT(4))
#define BIT_AON_SEC_APB_SEC_WDG_SOFT_RST			(BIT(3))
#define BIT_AON_SEC_APB_SEC_RTC_SOFT_RST			(BIT(2))
#define BIT_AON_SEC_APB_SEC_TMR0_SOFT_RST			(BIT(1))
#define BIT_AON_SEC_APB_SEC_TZPC_SOFT_RST			(BIT(0))

/* bits definitions for register REG_AON_SEC_APB_CA53_CFG_CTRL */
#define BIT_AON_SEC_APB_CA53_GIC_CFGSDISABLE			(BIT(8))
#define BITS_AON_SEC_APB_CA53_BIG_CP15SDISABLE(_X_)		((_X_) << 4 & (BIT(4)|BIT(5)|BIT(6)|BIT(7)))
#define BITS_AON_SEC_APB_CA53_LIT_CP15SDISABLE(_X_)		((_X_) & (BIT(0)|BIT(1)|BIT(2)|BIT(3)))

/* bits definitions for register REG_AON_SEC_APB_CA53_SOFT_RST */
#define BIT_AON_SEC_APB_CA53_BIG_DBG_SOFT_RST			(BIT(25))
#define BIT_AON_SEC_APB_CA53_BIG_L2_SOFT_RST			(BIT(24))
#define BITS_AON_SEC_APB_CA53_BIG_ATB_SOFT_RST(_X_)		((_X_) << 20 & (BIT(20)|BIT(21)|BIT(22)|BIT(23)))
#define BITS_AON_SEC_APB_CA53_BIG_CORE_SOFT_RST(_X_)		((_X_) << 16 & (BIT(16)|BIT(17)|BIT(18)|BIT(19)))
#define BIT_AON_SEC_APB_CA53_LIT_DBG_SOFT_RST			(BIT(9))
#define BIT_AON_SEC_APB_CA53_LIT_L2_SOFT_RST			(BIT(8))
#define BITS_AON_SEC_APB_CA53_LIT_ATB_SOFT_RST(_X_)		((_X_) << 4 & (BIT(4)|BIT(5)|BIT(6)|BIT(7)))
#define BITS_AON_SEC_APB_CA53_LIT_CORE_SOFT_RST(_X_)		((_X_) & (BIT(0)|BIT(1)|BIT(2)|BIT(3)))

/* bits definitions for register REG_AON_SEC_APB_CA53_LIT_CLK_CFG */
#define BITS_AON_SEC_APB_CLK_CA53_LIT_ATB_DIV(_X_)		((_X_) << 16 & (BIT(16)|BIT(17)|BIT(18)))
#define BITS_AON_SEC_APB_CLK_CA53_LIT_DBG_DIV(_X_)		((_X_) << 12 & (BIT(12)|BIT(13)|BIT(14)))
#define BITS_AON_SEC_APB_CLK_CA53_LIT_ACE_DIV(_X_)		((_X_) << 8 & (BIT(8)|BIT(9)|BIT(10)))
#define BITS_AON_SEC_APB_CLK_CA53_LIT_MCU_DIV(_X_)		((_X_) << 4 & (BIT(4)|BIT(5)|BIT(6)))
#define BIT_AON_SEC_APB_CLK_CA53_LIT_MPLL0_SEL			(BIT(3))
#define BITS_AON_SEC_APB_CLK_CA53_LIT_MCU_SEL(_X_)		((_X_) & (BIT(0)|BIT(1)|BIT(2)))

/* bits definitions for register REG_AON_SEC_APB_CA53_BIG_CLK_CFG */
#define BITS_AON_SEC_APB_CLK_CA53_BIG_ATB_DIV(_X_)		((_X_) << 16 & (BIT(16)|BIT(17)|BIT(18)))
#define BITS_AON_SEC_APB_CLK_CA53_BIG_DBG_DIV(_X_)		((_X_) << 12 & (BIT(12)|BIT(13)|BIT(14)))
#define BITS_AON_SEC_APB_CLK_CA53_BIG_ACE_DIV(_X_)		((_X_) << 8 & (BIT(8)|BIT(9)|BIT(10)))
#define BITS_AON_SEC_APB_CLK_CA53_BIG_MCU_DIV(_X_)		((_X_) << 4 & (BIT(4)|BIT(5)|BIT(6)))
#define BIT_AON_SEC_APB_CLK_CA53_BIG_MPLL1_SEL			(BIT(3))
#define BITS_AON_SEC_APB_CLK_CA53_BIG_MCU_SEL(_X_)		((_X_) & (BIT(0)|BIT(1)|BIT(2)))

/* bits definitions for register REG_AON_SEC_APB_CA53_TOP_CLK_CFG */
#define BITS_AON_SEC_APB_CLK_GIC_DIV(_X_)			((_X_) << 18 & (BIT(18)|BIT(19)))
#define BITS_AON_SEC_APB_CLK_GIC_SEL(_X_)			((_X_) << 16 & (BIT(16)|BIT(17)))
#define BITS_AON_SEC_APB_CLK_CSSYS_DIV(_X_)			((_X_) << 10 & (BIT(10)|BIT(11)))
#define BITS_AON_SEC_APB_CLK_CSSYS_SEL(_X_)			((_X_) << 8 & (BIT(8)|BIT(9)))

/* bits definitions for register REG_AON_SEC_APB_CCI_CFG0 */
#define BITS_AON_SEC_APB_CCI_PERIPHBASE_H25(_X_)		((_X_) & (BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15)|BIT(16)|BIT(17)|BIT(18)|BIT(19)|BIT(20)|BIT(21)|BIT(22)|BIT(23)|BIT(24)))

/* bits definitions for register REG_AON_SEC_APB_CCI_CFG1 */
#define BITS_AON_SEC_APB_CCI_AWQOS_BIG(_X_)			((_X_) << 28 & (BIT(28)|BIT(29)|BIT(30)|BIT(31)))
#define BITS_AON_SEC_APB_CCI_ARQOS_BIG(_X_)			((_X_) << 24 & (BIT(24)|BIT(25)|BIT(26)|BIT(27)))
#define BITS_AON_SEC_APB_CCI_AWQOS_LIT(_X_)			((_X_) << 20 & (BIT(20)|BIT(21)|BIT(22)|BIT(23)))
#define BITS_AON_SEC_APB_CCI_ARQOS_LIT(_X_)			((_X_) << 16 & (BIT(16)|BIT(17)|BIT(18)|BIT(19)))
#define BITS_AON_SEC_APB_CCI_QOSOVERRIDE(_X_)			((_X_) << 3 & (BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)))
#define BITS_AON_SEC_APB_CCI_BUFFERABLEOVERRIDE(_X_)		((_X_) & (BIT(0)|BIT(1)|BIT(2)))

/* bits definitions for register REG_AON_SEC_APB_RVBARADDR0_LIT */
#define BITS_AON_SEC_APB_RVBARADDR0_LIT(_X_)			(_X_)

/* bits definitions for register REG_AON_SEC_APB_RVBARADDR1_LIT */
#define BITS_AON_SEC_APB_RVBARADDR1_LIT(_X_)			(_X_)

/* bits definitions for register REG_AON_SEC_APB_RVBARADDR2_LIT */
#define BITS_AON_SEC_APB_RVBARADDR2_LIT(_X_)			(_X_)

/* bits definitions for register REG_AON_SEC_APB_RVBARADDR3_LIT */
#define BITS_AON_SEC_APB_RVBARADDR3_LIT(_X_)			(_X_)

/* bits definitions for register REG_AON_SEC_APB_RVBARADDR0_BIG */
#define BITS_AON_SEC_APB_RVBARADDR0_BIG(_X_)			(_X_)

/* bits definitions for register REG_AON_SEC_APB_RVBARADDR1_BIG */
#define BITS_AON_SEC_APB_RVBARADDR1_BIG(_X_)			(_X_)

/* bits definitions for register REG_AON_SEC_APB_RVBARADDR2_BIG */
#define BITS_AON_SEC_APB_RVBARADDR2_BIG(_X_)			(_X_)

/* bits definitions for register REG_AON_SEC_APB_RVBARADDR3_BIG */
#define BITS_AON_SEC_APB_RVBARADDR3_BIG(_X_)			(_X_)

/* bits definitions for register REG_AON_SEC_APB_CA53_NOC_CTRL */
#define BITS_AON_SEC_APB_CHIP_DDR_CAPACITY_I(_X_)		((_X_) << 9 & (BIT(9)|BIT(10)|BIT(11)))
#define BIT_AON_SEC_APB_CA53_M0_IDLE				(BIT(8))
#define BIT_AON_SEC_APB_CA53_SERVICE_ACCESS_EN			(BIT(3))
#define BITS_AON_SEC_APB_CA53_INTERLEAVE_MODE(_X_)		((_X_) << 1 & (BIT(1)|BIT(2)))
#define BIT_AON_SEC_APB_CA53_INTERLEAVE_SEL			(BIT(0))

/* bits definitions for register REG_AON_SEC_APB_AP_NOC_CTRL */
#define BIT_AON_SEC_APB_AP_M0_IDLE				(BIT(8))
#define BIT_AON_SEC_APB_AP_SERVICE_ACCESS_EN			(BIT(3))
#define BITS_AON_SEC_APB_AP_INTERLEAVE_MODE(_X_)		((_X_) << 1 & (BIT(1)|BIT(2)))
#define BIT_AON_SEC_APB_AP_INTERLEAVE_SEL			(BIT(0))

#endif
