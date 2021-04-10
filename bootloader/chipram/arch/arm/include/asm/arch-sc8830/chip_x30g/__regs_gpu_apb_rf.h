/*
 * Copyright (C) 2014 Spreadtrum Communications Inc.
 */

//#ifndef __SCI_GLB_REGS_H__
//#error  "Don't include this file directly, Pls include sci_glb_regs.h"
//#endif


#ifndef __H_REGS_GPU_APB_RF_HEADFILE_H__
#define __H_REGS_GPU_APB_RF_HEADFILE_H__ __FILE__

#define	REGS_GPU_APB_RF

/* registers definitions for GPU_APB_RF */
#define REG_GPU_APB_RF_APB_RST                            SCI_ADDR(REGS_GPU_APB_RF_BASE, 0x0000)
#define REG_GPU_APB_RF_APB_CLK_CTRL                       SCI_ADDR(REGS_GPU_APB_RF_BASE, 0x0004)



/* bits definitions for register REG_GPU_APB_RF_APB_RST */
#define BIT_GPU_SOFT_RST                                  ( BIT(0) )

/* bits definitions for register REG_GPU_APB_RF_APB_CLK_CTRL */
#define BITS_CLK_GPU_DIV(_X_)                             ( (_X_) << 4 & (BIT(4)|BIT(5)) )
#define BITS_CLK_GPU_SEL(_X_)                             ( (_X_) & (BIT(0)|BIT(1)|BIT(2)) )

#endif
