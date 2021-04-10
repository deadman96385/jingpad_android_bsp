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

#include "chip_isharkl2/__hardware-isharkl2.h"

#endif /* __ASM_ARCH_SCI_HARDWARE_H */
