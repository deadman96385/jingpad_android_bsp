/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _GPU_CLK_REG_H
#define _GPU_CLK_REG_H

#define CTL_BASE_GPU_CLK SPRD_GPUCKG_BASE


#define REG_GPU_CLK_CGM_GPU_CORE_CFG  ( CTL_BASE_GPU_CLK + 0x0020 )
#define REG_GPU_CLK_CGM_GPU_MEM_CFG   ( CTL_BASE_GPU_CLK + 0x0024 )
#define REG_GPU_CLK_CGM_GPU_SYS_CFG   ( CTL_BASE_GPU_CLK + 0x0028 )
#define REG_GPU_CLK_CGM_GPU_26M_CFG   ( CTL_BASE_GPU_CLK + 0x002C )

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_CLK_CGM_GPU_CORE_CFG
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_CLK_CGM_GPU_CORE_DIV(x)            (((x) & 0x7) << 8)
#define BIT_GPU_CLK_CGM_GPU_CORE_SEL(x)            (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_CLK_CGM_GPU_MEM_CFG
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_CLK_CGM_GPU_MEM_DIV(x)             (((x) & 0x7) << 8)
#define BIT_GPU_CLK_CGM_GPU_MEM_SEL(x)             (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_CLK_CGM_GPU_SYS_CFG
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_CLK_CGM_GPU_SYS_SEL                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_CLK_CGM_GPU_26M_CFG
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_CLK_CGM_GPU_26M_SEL                BIT(0)


#endif // _GPU_CLK_REG_H
