/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __ASM_ARCH_SCI_HARDWARE_H
#define __ASM_ARCH_SCI_HARDWARE_H

#define SCI_IOMAP(x)	(SCI_IOMAP_BASE + (x))

#ifndef SCI_ADDR
#define SCI_ADDR(_b_, _o_)                              ( (u32)(_b_) + (_o_) )
#endif

#include <linux/sizes.h>
#include "regs_adi.h"
#include "sprd_eic.h"
#include "rtc_reg_v3.h"
#include "chip_roc1/hardware.h"

#endif
