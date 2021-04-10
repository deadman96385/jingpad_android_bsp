/*
 * (C) Copyright 2016 Intel Corporation
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm/global_data.h>
#include <asm/msr-index.h>
#include <asm/processor-flags.h>

	.globl cpu_set_paging
	.globl cpu_paging_disable

	.code32

cpu_set_paging:
	/*
	 * cpu_paging_enable(ulong pgtable)
	 *
	 * eax - pgtable
	 */

	/* Set PML4 */
	movl	%eax, %cr3

	/* Set CR4.PAE */
	movl	%cr4, %eax
	orl	$(X86_CR4_PAE), %eax
	movl	%eax, %cr4

	/* Set IA32_EFER.LME */
	movl	$MSR_EFER, %ecx
	rdmsr
	btsl	$_EFER_LME, %eax
	wrmsr

	/* Set CR0.PG */
	movl	%cr0, %eax
	orl	$X86_CR0_PG, %eax
	movl	%eax, %cr0

	ret

cpu_paging_disable:
	/* Clear CR0.PG */
	movl	%cr0, %eax
	andl	$~X86_CR0_PG, %eax
	movl	%eax, %cr0

	ret
