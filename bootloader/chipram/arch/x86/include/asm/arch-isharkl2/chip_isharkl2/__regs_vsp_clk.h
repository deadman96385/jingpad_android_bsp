/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _VSP_CLK_REG_H
#define _VSP_CLK_REG_H

#define CTL_BASE_VSP_CLK SPRD_VSP_CLK_BASE


#define REG_CLKTOP_CGM_AHB_VSP_CFG  ( CTL_BASE_VSP_CLK + 0x0020 )
#define REG_CLKTOP_CGM_VSP_CFG      ( CTL_BASE_VSP_CLK + 0x0024 )
#define REG_CLKTOP_CGM_GSP0_CFG     ( CTL_BASE_VSP_CLK + 0x0028 )
#define REG_CLKTOP_CGM_SYS_MTX_CFG  ( CTL_BASE_VSP_CLK + 0x002C )

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_CLK_CLKTOP_CGM_AHB_VSP_CFG
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_AHB_VSP_SEL(x)            (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_CLK_CLKTOP_CGM_VSP_CFG
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_VSP_DIV(x)                (((x) & 0x3) << 8)
#define BIT_CGM_VSP_SEL(x)                (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_CLK_CLKTOP_CGM_GSP0_CFG
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_GSP0_SEL(x)               (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_CLK_CLKTOP_CGM_SYS_MTX_CFG
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_CGM_SYS_MTX_SEL(x)            (((x) & 0x3))


#endif // _VSP_CLK_REG_H
