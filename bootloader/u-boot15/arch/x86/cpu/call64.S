/*
 * (C) Copyright 2014 Google, Inc
 * Copyright (C) 1991, 1992, 1993  Linus Torvalds
 *
 * Parts of this copied from Linux arch/x86/boot/compressed/head_64.S
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm/global_data.h>
#include <asm/msr-index.h>
#include <asm/processor-flags.h>

	.globl cpu_call64

	.code32
cpu_call64:
	/*
	 * cpu_call64(ulong target, ulong setup_base)
	 *
	 * edx:eax - target
	 * ecx - setup_base
	 */
	push	%ebp
	movl	%esp, %ebp
	andl	$0xfffffff8, %esp

	/* Push target address */
	push	%edx
	push	%eax

	/* Copy setup_base */
	movl	%ecx, %esi

	/* Load new GDT with the 64bit segments using 32bit descriptor */
	lgdt	gdtr_data


	/* After gdt is loaded */
	xorl	%eax, %eax
	lldt	%ax

	/*
	 * Setup for the jump to 64bit mode
	 *
	 * When the jump is performed we will be in long mode but
	 * in 32bit compatibility mode with EFER.LME = 1, CS.L = 0, CS.D = 1
	 * (and in turn EFER.LMA = 1). To jump into 64bit mode we use
	 * the new gdt/idt that has __KERNEL_CS with CS.L = 1.
	 * We place all of the values on our mini stack so lret can
	 * used to perform that far jump. See the gdt below.
	 */

	cli

	/* Jump from 32bit compatibility mode into 64bit mode. */
	ljmp	$0x10, $lret_target

	.code64

lret_target:

	movq	$0xffffffff, %rax
	andq	%rax, %rsp
	andq	%rax, %rbp
	pop	%rax			/* target */
	jmp	*%rax			/* Jump to the 64-bit target */

	.data
	.align	16
	.word	0
gdtr_data:
	.word	gdt_end - gdt_start - 1
	.long	gdt_start
gdt_start:
	.quad	0x0000000000000000	/* NULL descriptor */
	.quad	0x0000000000000000	/* Zero descriptor */
	.quad	0x00af9a000000ffff	/* __KERNEL_CS */
	.quad	0x00cf92000000ffff	/* __KERNEL_DS */
	.quad	0x0080890000000000	/* TS descriptor */
	.quad   0x0000000000000000	/* TS continued */
gdt_end:
