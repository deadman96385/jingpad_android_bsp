
#include <config.h>
#include <common.h>
//


#define DDR_SCAN_STACK 0xE601A000

#define IA32_MTRR_DEF_TYPE 0x2FF
#define IA32_MTRR_PHYSBASE0 0x200
#define IA32_MTRR_PHYSMASK0 0x201

/*
 *************************************************************************
 *
 * Jump vector table as in table 3.1 in [1]
 *
 *************************************************************************
 */


.globl _start
_start:
	jmp	reset

	.align	4

/* 0x04 */
	.rept   127
	.long   0xABCD1234
	.endr
/*
 *************************************************************************
 *
 * Startup Code (reset vector)
 *
 * do important init only if we don't start from memory!
 * setup Memory and board specific bits prior to relocation.
 * relocate armboot to ram
 * setup stack
 *
 *************************************************************************
 */
/*
 * These are defined in the board-specific linker script.
 */
.local _bss0_start
_bss0_start:
	.long	__bss0_start
.local _bss0_end
_bss0_end:
	.long	__bss0_end
.local _bss1_start
_bss1_start:
	.long	__bss1_start
.local _bss1_end
_bss1_end:
	.long	__bss1_end

.local _boot_start
_boot_start:
	.long	_start

.align 32

#ifdef CONFIG_VOL_PARA
_vol_para:
	.long	vol_para
#endif

/*
 * the actual reset code
 */

reset:
/* Cache Disable */

	movl	%cr0, %eax
	orl	$0x60000000, %eax
	movl	%eax, %cr0
	wbinvd

/* MTRR disable */

	movl	$0, %eax
	movl	$0, %edx
	movl	$IA32_MTRR_DEF_TYPE, %ecx
	wrmsr

/* Bits [63:32] of physical address mask */

	movl	$0, %ebx

	movl	$IA32_MTRR_PHYSBASE0, %ecx

/* Variable Range MTRR #0: FFFF8000-FFFFFFFF, WP */

	movl	$0, %edx
	movl	$0xFFFF8005, %eax
	wrmsr
	incl	%ecx
	movl	%ebx, %edx
	movl	$0xFFFF8800, %eax
	wrmsr
	incl	%ecx

/* Variable Range MTRR #1: FFFB0000-FFFBFFFF, WB */

	movl	$0, %edx
	movl	$0xFFFB0006, %eax
	wrmsr
	incl	%ecx
	movl	%ebx, %edx
	movl	$0xFFFF0800, %eax
	wrmsr
	incl	%ecx

	xorl	%edx, %edx
	xorl	%eax, %eax

/* Variable Range MTRR #2: disable */

	wrmsr
	incl	%ecx
	wrmsr
	incl	%ecx

/* Variable Range MTRR #3: disable */

	wrmsr
	incl	%ecx
	wrmsr
	incl	%ecx

/* Variable Range MTRR #4: disable */

	wrmsr
	incl	%ecx
	wrmsr
	incl	%ecx

/* Variable Range MTRR #5: disable */

	wrmsr
	incl	%ecx
	wrmsr
	incl	%ecx

/* Variable Range MTRR #6: disable */

	wrmsr
	incl	%ecx
	wrmsr
	incl	%ecx

/* Variable Range MTRR #7: disable */

	wrmsr
	incl	%ecx
	wrmsr
	incl	%ecx

/* MTRR enable */

	movl	$IA32_MTRR_DEF_TYPE, %ecx
	rdmsr
	andl	$0xFFFFF300, %eax
	orl	$(1 << 11), %eax
	wrmsr

/* Cache Enable */

	movl	%cr0, %eax
	andl	$0x9FFFFFFF, %eax
	movl	%eax, %cr0

	movl	$DDR_SCAN_STACK, %esp

	movl	$__bss0_start, %edi
	movl	$__bss0_end, %ecx
	subl	%edi, %ecx
	xorl	%eax, %eax
	cld
	rep	stosb

	call	Chip_Init

	movl	$__bss1_start, %edi
	movl	$__bss1_end, %ecx
	subl	%edi, %ecx
	xorl	%eax, %eax
	cld
	rep	stosb

	call	main
