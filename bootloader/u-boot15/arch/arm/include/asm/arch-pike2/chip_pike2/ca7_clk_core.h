/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _CA7_CLK_CORE_REG_H
#define _CA7_CLK_CORE_REG_H

#define CTL_BASE_CA7_CLK_CORE 0x20E00000


#define REG_CA7_CLK_CORE_CGM_CA7_MCU_CFG   ( CTL_BASE_CA7_CLK_CORE + 0x0020 )
#define REG_CA7_CLK_CORE_CGM_CA7_CORE_CFG  ( CTL_BASE_CA7_CLK_CORE + 0x0024 )
#define REG_CA7_CLK_CORE_CGM_CA7_AXI_CFG   ( CTL_BASE_CA7_CLK_CORE + 0x0028 )
#define REG_CA7_CLK_CORE_CGM_CA7_DBG_CFG   ( CTL_BASE_CA7_CLK_CORE + 0x002C )
#define REG_CA7_CLK_CORE_CGM_AXI_EMC_CFG   ( CTL_BASE_CA7_CLK_CORE + 0x0030 )

/*---------------------------------------------------------------------------
// Register Name   : REG_CA7_CLK_CORE_CGM_CA7_MCU_CFG
// Register Offset : 0x0020
// Description     :
---------------------------------------------------------------------------*/

#define BIT_CA7_CLK_CORE_CGM_CA7_MCU_CFG_CGM_CA7_MCU_SEL(x)                   (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_CA7_CLK_CORE_CGM_CA7_CORE_CFG
// Register Offset : 0x0024
// Description     :
---------------------------------------------------------------------------*/

#define BIT_CA7_CLK_CORE_CGM_CA7_CORE_CFG_CGM_CA7_CORE_SEL                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CA7_CLK_CORE_CGM_CA7_AXI_CFG
// Register Offset : 0x0028
// Description     :
---------------------------------------------------------------------------*/

#define BIT_CA7_CLK_CORE_CGM_CA7_AXI_CFG_CGM_CA7_AXI_SEL                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CA7_CLK_CORE_CGM_CA7_DBG_CFG
// Register Offset : 0x002C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_CA7_CLK_CORE_CGM_CA7_DBG_CFG_CGM_CA7_DBG_SEL                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_CA7_CLK_CORE_CGM_AXI_EMC_CFG
// Register Offset : 0x0030
// Description     :
---------------------------------------------------------------------------*/



#endif // _CA7_CLK_CORE_REG_H
