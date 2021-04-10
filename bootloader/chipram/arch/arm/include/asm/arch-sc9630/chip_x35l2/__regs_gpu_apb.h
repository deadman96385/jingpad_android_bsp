/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _GPU_APB_REG_H
#define _GPU_APB_REG_H

#define CTL_BASE_GPU_APB SPRD_GPUAPB_PHYS


#define REG_GPU_APB_APB_RST               ( CTL_BASE_GPU_APB + 0x0000 )
#define REG_GPU_APB_APB_CLK_CTRL          ( CTL_BASE_GPU_APB + 0x0004 )
#define REG_GPU_APB_APB_BARRIER_CTRL      ( CTL_BASE_GPU_APB + 0x0008 )

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_APB_APB_RST
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_APB_GPU_SOFT_RST                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_APB_APB_CLK_CTRL
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_APB_CLK_GPU_DIV(x)                       (((x) & 0x3) << 4)
#define BIT_GPU_APB_CLK_GPU_SEL(x)                       (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_APB_APB_BARRIER_CTRL
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_APB_GPU_BARRIER_DISABLE_EN               BIT(0)


#endif // _GPU_APB_REG_H
