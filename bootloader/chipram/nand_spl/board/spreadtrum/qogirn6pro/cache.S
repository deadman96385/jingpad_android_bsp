/*
 * (C) Copyright 2013
 * David Feng <fenghua@phytium.com.cn>
 *
 * This file is based on sample code from ARMv8 ARM.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */


#include <config.h>

#include <asm/macro.h>
#include <linux/linkage.h>

/*
 * void __asm_invalidate_icache_all(void)
 *
 * invalidate all tlb entries.
 */
ENTRY(__asm_invalidate_icache_all)
	ic	ialluis
	isb	sy
	ret
ENDPROC(__asm_invalidate_icache_all)
