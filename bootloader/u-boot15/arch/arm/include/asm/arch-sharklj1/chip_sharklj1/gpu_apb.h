/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2017-05-30 15:03:07
 *
 */


#ifndef GPU_APB_H
#define GPU_APB_H

#define CTL_BASE_GPU_APB 0x60100000


#define REG_GPU_APB_APB_RST                 ( CTL_BASE_GPU_APB + 0x0000 )
#define REG_GPU_APB_APB_CLK_CTRL            ( CTL_BASE_GPU_APB + 0x0004 )
#define REG_GPU_APB_APB_BARRIER_CTRL        ( CTL_BASE_GPU_APB + 0x0008 )
#define REG_GPU_APB_GPU_PATH                ( CTL_BASE_GPU_APB + 0x000C )
#define REG_GPU_APB_GPUD_ACTIVE             ( CTL_BASE_GPU_APB + 0x0010 )
#define REG_GPU_APB_GPU_MTX_SYNC_STAGE      ( CTL_BASE_GPU_APB + 0x0020 )
#define REG_GPU_APB_CGM_GPU_FDIV            ( CTL_BASE_GPU_APB + 0x0080 )
#define REG_GPU_APB_GPU_PATH_SEL            ( CTL_BASE_GPU_APB + 0x0084 )

/* REG_GPU_APB_APB_RST */

#define BIT_GPU_APB_GPU_SOFT_RST            BIT(0)

/* REG_GPU_APB_APB_CLK_CTRL */

#define BIT_GPU_APB_CLK_GPU_DIV(x)          (((x) & 0x3) << 4)
#define BIT_GPU_APB_CLK_GPU_SEL(x)          (((x) & 0x7))

/* REG_GPU_APB_APB_BARRIER_CTRL */

#define BIT_GPU_APB_GPU_BARRIER_DISABLE_EN  BIT(0)

/* REG_GPU_APB_GPU_PATH */

#define BIT_GPU_APB_GPU_PATH                BIT(0)

/* REG_GPU_APB_GPUD_ACTIVE */

#define BIT_GPU_APB_GDC_ACTIVE              BIT(2)
#define BIT_GPU_APB_GDG_ACTIVE              BIT(1)
#define BIT_GPU_APB_GDL_ACTIVE              BIT(0)

/* REG_GPU_APB_GPU_MTX_SYNC_STAGE */


/* REG_GPU_APB_CGM_GPU_FDIV */

#define BIT_GPU_APB_CGM_GPU_FDIV_NUM(x)     (((x) & 0xF) << 16)
#define BIT_GPU_APB_CGM_GPU_FDIV_DENOM(x)   (((x) & 0xF))

/* REG_GPU_APB_GPU_PATH_SEL */

#define BIT_GPU_APB_GPU_PATH_SEL            BIT(0)


#endif /* GPU_APB_H */

