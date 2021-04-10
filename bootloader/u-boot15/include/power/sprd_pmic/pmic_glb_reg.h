/*
 * Copyright (C) 2014-2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */

#ifndef _PMIC_GLB_REG_H_
#define _PMIC_GLB_REG_H_

#if defined(CONFIG_ADIE_SC2723)
#include "sc2723_reg_base.h"
#include "__regs_ana_sc2723_glb.h"
#elif defined(CONFIG_ADIE_SC2731)
#include "sc2731_reg_base.h"
#include "__regs_ana_sc2731_glb.h"
#elif defined(CONFIG_ADIE_SC2721)
#include "sc2721_reg_base.h"
#include "__regs_ana_sc2721_glb.h"
#elif defined(CONFIG_ADIE_SC2720)
#include "sc2720_reg_base.h"
#include "__regs_ana_sc2720_glb.h"
#elif defined(CONFIG_ADIE_SC2730)
#include "sc2730_reg_base.h"
#include "__regs_ana_sc2730_glb.h"
#else
#error "PMIC address is not defined!"
#endif

#endif
