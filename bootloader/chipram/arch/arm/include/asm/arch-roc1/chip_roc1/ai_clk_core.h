/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-18 10:54:28
 *
 */


#ifndef AI_CLK_CORE_H
#define AI_CLK_CORE_H

#define CTL_BASE_AI_CLK_CORE 0x6FD04000


#define REG_AI_CLK_CORE_CGM_CAMBRICON_CFG      ( CTL_BASE_AI_CLK_CORE + 0x0020 )
#define REG_AI_CLK_CORE_CGM_POWERVR_CFG        ( CTL_BASE_AI_CLK_CORE + 0x0024 )
#define REG_AI_CLK_CORE_CGM_AI_MTX_CFG         ( CTL_BASE_AI_CLK_CORE + 0x0028 )
#define REG_AI_CLK_CORE_CGM_AI_MMU_CFG         ( CTL_BASE_AI_CLK_CORE + 0x002C )
#define REG_AI_CLK_CORE_CGM_CAMBRICON_CFG_CFG  ( CTL_BASE_AI_CLK_CORE + 0x0030 )
#define REG_AI_CLK_CORE_CGM_POWERVR_CFG_CFG    ( CTL_BASE_AI_CLK_CORE + 0x0034 )
#define REG_AI_CLK_CORE_CGM_DVFS_AI_CFG        ( CTL_BASE_AI_CLK_CORE + 0x0038 )

/* REG_AI_CLK_CORE_CGM_CAMBRICON_CFG */

#define BIT_AI_CLK_CORE_CGM_CAMBRICON_CFG_CGM_CAMBRICON_FDIV_DENOM(x)  (((x) & 0xF) << 20)
#define BIT_AI_CLK_CORE_CGM_CAMBRICON_CFG_CGM_CAMBRICON_FDIV_NUM(x)    (((x) & 0xF) << 16)
#define BIT_AI_CLK_CORE_CGM_CAMBRICON_CFG_CGM_CAMBRICON_DIV(x)         (((x) & 0x7) << 8)
#define BIT_AI_CLK_CORE_CGM_CAMBRICON_CFG_CGM_CAMBRICON_SEL(x)         (((x) & 0x3))

/* REG_AI_CLK_CORE_CGM_POWERVR_CFG */

#define BIT_AI_CLK_CORE_CGM_POWERVR_CFG_CGM_POWERVR_FDIV_DENOM(x)      (((x) & 0xF) << 20)
#define BIT_AI_CLK_CORE_CGM_POWERVR_CFG_CGM_POWERVR_FDIV_NUM(x)        (((x) & 0xF) << 16)
#define BIT_AI_CLK_CORE_CGM_POWERVR_CFG_CGM_POWERVR_DIV(x)             (((x) & 0x7) << 8)
#define BIT_AI_CLK_CORE_CGM_POWERVR_CFG_CGM_POWERVR_SEL                BIT(0)

/* REG_AI_CLK_CORE_CGM_AI_MTX_CFG */

#define BIT_AI_CLK_CORE_CGM_AI_MTX_CFG_CGM_AI_MTX_DIV(x)               (((x) & 0x7) << 8)
#define BIT_AI_CLK_CORE_CGM_AI_MTX_CFG_CGM_AI_MTX_SEL(x)               (((x) & 0x3))

/* REG_AI_CLK_CORE_CGM_AI_MMU_CFG */


/* REG_AI_CLK_CORE_CGM_CAMBRICON_CFG_CFG */

#define BIT_AI_CLK_CORE_CGM_CAMBRICON_CFG_CFG_CGM_CAMBRICON_CFG_SEL    BIT(0)

/* REG_AI_CLK_CORE_CGM_POWERVR_CFG_CFG */

#define BIT_AI_CLK_CORE_CGM_POWERVR_CFG_CFG_CGM_POWERVR_CFG_SEL        BIT(0)

/* REG_AI_CLK_CORE_CGM_DVFS_AI_CFG */

#define BIT_AI_CLK_CORE_CGM_DVFS_AI_CFG_CGM_DVFS_AI_SEL                BIT(0)


#endif /* AI_CLK_CORE_H */


