/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */

#ifndef __H_REGS_GPU_APB_HEADFILE_H__
#define __H_REGS_GPU_APB_HEADFILE_H__ 



#define REG_GPU_APB_APB_RST                  SCI_ADDR(REGS_GPU_APB_BASE, 0x0000 )
#define REG_GPU_APB_GPU_PATH_SEL             SCI_ADDR(REGS_GPU_APB_BASE, 0x0004 )
#define REG_GPU_APB_GPU_BARRIER_DISABLE      SCI_ADDR(REGS_GPU_APB_BASE, 0x0008 )
#define REG_GPU_APB_GPU_PATH                 SCI_ADDR(REGS_GPU_APB_BASE, 0x000C )
#define REG_GPU_APB_GPUD_ACTIVE              SCI_ADDR(REGS_GPU_APB_BASE, 0x0010 )
#define REG_GPU_APB_GPU_MTX_SYNC_STAGE       SCI_ADDR(REGS_GPU_APB_BASE, 0x0020 )
#define REG_GPU_APB_CGM_GPU_FDIV             SCI_ADDR(REGS_GPU_APB_BASE, 0x0080 )

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_APB_APB_RST
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_APB_GPU_SOFT_RST                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_APB_GPU_PATH_SEL
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_APB_GPU_PATH_SEL                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_APB_GPU_BARRIER_DISABLE
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_APB_GPU_BARRIER_DISABLE               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_APB_GPU_PATH
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_APB_GPU_PATH                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_APB_GPUD_ACTIVE
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_APB_GDC_ACTIVE                        BIT(2)
#define BIT_GPU_APB_GDG_ACTIVE                        BIT(1)
#define BIT_GPU_APB_GDL_ACTIVE                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_APB_GPU_MTX_SYNC_STAGE
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_APB_GPU_MTX_SYNC_STAGE                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_APB_CGM_GPU_FDIV
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_APB_CGM_GPU_FDIV_NUM(x)               (((x) & 0xF) << 16)
#define BIT_GPU_APB_CGM_GPU_FDIV_DENOM(x)             (((x) & 0xF))


#endif
