/*
 * (C) Copyright 2013
 * David Feng <fenghua@phytium.com.cn>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */


#include <config.h>
//

#include <asm/macro.h>
#include <linux/linkage.h>

/*
 * Enter Exception.
 * This will save the processor state that is ELR/X0~X30
 * to the stack frame.
 */
/*
 * Exception vectors.
 */
