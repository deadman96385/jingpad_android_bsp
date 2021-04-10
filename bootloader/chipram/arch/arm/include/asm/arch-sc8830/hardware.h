/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 */

#ifndef __ASM_ARCH_SCI_HARDWARE_H
#define __ASM_ARCH_SCI_HARDWARE_H

#define SCI_IOMAP(x)	(SCI_IOMAP_BASE + (x))

#ifndef SCI_ADDR
#define SCI_ADDR(_b_, _o_)                              ( (u32)(_b_) + (_o_) )
#endif

#include <asm/sizes.h>

#if defined(CONFIG_SPX15)
#include "chip_x15/__hardware-sc8830.h"
#elif defined(CONFIG_SPX30G)
	#if defined(CONFIG_SPX20)
		#include "chip_x20/__hardware-sc7720.h"
	#else
		#include "chip_x30g/__hardware-sc8830.h"
	#endif
#else
#include "chip_x35/__hardware-sc8830.h"
#endif

#endif
