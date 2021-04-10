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

#define CTL_BASE_VSP_CLK SPRD_VSPCKG_BASE


#define REG_VSP_CLK_CGM_AHB_VSP_CFG    ( CTL_BASE_VSP_CLK + 0x0020 )
#define REG_VSP_CLK_CGM_VSP_CFG        ( CTL_BASE_VSP_CLK + 0x0024 )
#define REG_VSP_CLK_CGM_VSP_ENC_CFG    ( CTL_BASE_VSP_CLK + 0x0028 )
#define REG_VSP_CLK_CGM_VPP_CFG        ( CTL_BASE_VSP_CLK + 0x002C )
#define REG_VSP_CLK_CGM_GSP0_CFG       ( CTL_BASE_VSP_CLK + 0x0030 )
#define REG_VSP_CLK_CGM_GSP1_CFG       ( CTL_BASE_VSP_CLK + 0x0034 )
#define REG_VSP_CLK_CGM_GSP_MTX_CFG    ( CTL_BASE_VSP_CLK + 0x0038 )
#define REG_VSP_CLK_CGM_SYS_MTX_CFG    ( CTL_BASE_VSP_CLK + 0x003C )
#define REG_VSP_CLK_CGM_BIST_256M_CFG  ( CTL_BASE_VSP_CLK + 0x0040 )
#define REG_VSP_CLK_CGM_BIST_384M_CFG  ( CTL_BASE_VSP_CLK + 0x0044 )

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_CLK_CGM_AHB_VSP_CFG
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_CLK_CGM_AHB_VSP_SEL(x)              (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_CLK_CGM_VSP_CFG
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_CLK_CGM_VSP_DIV(x)                  (((x) & 0x3) << 8)
#define BIT_VSP_CLK_CGM_VSP_SEL(x)                  (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_CLK_CGM_VSP_ENC_CFG
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_CLK_CGM_VSP_ENC_DIV(x)              (((x) & 0x3) << 8)
#define BIT_VSP_CLK_CGM_VSP_ENC_SEL(x)              (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_CLK_CGM_VPP_CFG
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_CLK_CGM_VPP_SEL(x)                  (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_CLK_CGM_GSP0_CFG
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_CLK_CGM_GSP0_SEL(x)                 (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_CLK_CGM_GSP1_CFG
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_CLK_CGM_GSP1_SEL(x)                 (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_CLK_CGM_GSP_MTX_CFG
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_CLK_CGM_GSP_MTX_SEL(x)              (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_CLK_CGM_SYS_MTX_CFG
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_CLK_CGM_SYS_MTX_SEL(x)              (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_CLK_CGM_BIST_256M_CFG
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_CLK_CGM_BIST_256M_SEL               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_CLK_CGM_BIST_384M_CFG
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_CLK_CGM_BIST_384M_SEL               BIT(0)


#endif // _VSP_CLK_REG_H
