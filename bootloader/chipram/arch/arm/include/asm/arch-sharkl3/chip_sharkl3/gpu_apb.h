/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2017-12-27 15:24:15
 *
 */


#ifndef GPU_APB_H
#define GPU_APB_H

#define CTL_BASE_GPU_APB 0x60100000


#define REG_GPU_APB_APB_RST      ( CTL_BASE_GPU_APB + 0x0000 )

/* REG_GPU_APB_APB_RST */

#define BIT_GPU_APB_GPU_SOFT_RST  BIT(0)


#endif /* GPU_APB_H */

