/*
 * Copyright (C) 2019 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2019-02-11 15:07:05
 *
 */


#ifndef APCPU_CLK_CORE_H
#define APCPU_CLK_CORE_H

#define CTL_BASE_APCPU_CLK_CORE 0x63970000


#define REG_APCPU_CLK_CORE_CGM_CORE0_CFG      ( CTL_BASE_APCPU_CLK_CORE + 0x0020 )
#define REG_APCPU_CLK_CORE_CGM_CORE1_CFG      ( CTL_BASE_APCPU_CLK_CORE + 0x0024 )
#define REG_APCPU_CLK_CORE_CGM_SCU_CFG        ( CTL_BASE_APCPU_CLK_CORE + 0x0028 )
#define REG_APCPU_CLK_CORE_CGM_ACE_CFG        ( CTL_BASE_APCPU_CLK_CORE + 0x002C )
#define REG_APCPU_CLK_CORE_CGM_ATB_CFG        ( CTL_BASE_APCPU_CLK_CORE + 0x0030 )
#define REG_APCPU_CLK_CORE_CGM_DEBUG_APB_CFG  ( CTL_BASE_APCPU_CLK_CORE + 0x0034 )
#define REG_APCPU_CLK_CORE_CGM_GIC_CFG        ( CTL_BASE_APCPU_CLK_CORE + 0x0038 )
#define REG_APCPU_CLK_CORE_CGM_PERIPH_CFG     ( CTL_BASE_APCPU_CLK_CORE + 0x003C )

/* REG_APCPU_CLK_CORE_CGM_CORE0_CFG */

#define BIT_APCPU_CLK_CORE_CGM_CORE0_CFG_CGM_CORE0_DIV(x)          (((x) & 0x7) << 8)
#define BIT_APCPU_CLK_CORE_CGM_CORE0_CFG_CGM_CORE0_SEL(x)          (((x) & 0x3))

/* REG_APCPU_CLK_CORE_CGM_CORE1_CFG */

#define BIT_APCPU_CLK_CORE_CGM_CORE1_CFG_CGM_CORE1_DIV(x)          (((x) & 0x7) << 8)
#define BIT_APCPU_CLK_CORE_CGM_CORE1_CFG_CGM_CORE1_SEL(x)          (((x) & 0x3))

/* REG_APCPU_CLK_CORE_CGM_SCU_CFG */

#define BIT_APCPU_CLK_CORE_CGM_SCU_CFG_CGM_SCU_DIV(x)              (((x) & 0x7) << 8)
#define BIT_APCPU_CLK_CORE_CGM_SCU_CFG_CGM_SCU_SEL(x)              (((x) & 0x3))

/* REG_APCPU_CLK_CORE_CGM_ACE_CFG */

#define BIT_APCPU_CLK_CORE_CGM_ACE_CFG_CGM_ACE_DIV(x)              (((x) & 0x7) << 8)

/* REG_APCPU_CLK_CORE_CGM_ATB_CFG */

#define BIT_APCPU_CLK_CORE_CGM_ATB_CFG_CGM_ATB_DIV(x)              (((x) & 0x7) << 8)
#define BIT_APCPU_CLK_CORE_CGM_ATB_CFG_CGM_ATB_SEL(x)              (((x) & 0x3))

/* REG_APCPU_CLK_CORE_CGM_DEBUG_APB_CFG */

#define BIT_APCPU_CLK_CORE_CGM_DEBUG_APB_CFG_CGM_DEBUG_APB_DIV(x)  (((x) & 0x3) << 8)

/* REG_APCPU_CLK_CORE_CGM_GIC_CFG */

#define BIT_APCPU_CLK_CORE_CGM_GIC_CFG_CGM_GIC_DIV(x)              (((x) & 0x7) << 8)
#define BIT_APCPU_CLK_CORE_CGM_GIC_CFG_CGM_GIC_SEL(x)              (((x) & 0x3))

/* REG_APCPU_CLK_CORE_CGM_PERIPH_CFG */

#define BIT_APCPU_CLK_CORE_CGM_PERIPH_CFG_CGM_PERIPH_DIV(x)        (((x) & 0x7) << 8)
#define BIT_APCPU_CLK_CORE_CGM_PERIPH_CFG_CGM_PERIPH_SEL(x)        (((x) & 0x3))


#endif /* APCPU_CLK_CORE_H */


