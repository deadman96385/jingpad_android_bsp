/*
 * Copyright (C) 2016 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */

#ifndef _SPRD_REGULATOR_H_
#define _SPRD_REGULATOR_H_

#include "adi_hal_internal.h"

 int DCDC_Cal_ArmCore(void);
 int regulator_init(void);
 int regulator_enable(const char con_id[]);
 int regulator_disable(const char con_id[]);
 int regulator_disable_all(void);
 int regulator_enable_all(void);
 int regulator_set_voltage(const char con_id[], int to_vol);
#endif


