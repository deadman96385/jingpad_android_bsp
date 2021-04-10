#include <config.h>
#include <common.h>
//


/*#define FDL1_STACK 0xFFFBCFF0*/
#define FDL1_STACK 0xE6022600
/*#define FDL1_STACK 0xE50F0000*/

/*
 *************************************************************************
 *
 * Jump vector table as in table 3.1 in [1]
 *
 *************************************************************************
 */


.globl _start

.code32

_start:
	jmp	reset
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

.align 4
.local _bss0_start
_bss0_start:
	.long __bss0_start
.local _bss0_end
_bss0_end:
	.long __bss0_end
.local _bss1_start
_bss1_start:
	.long __bss1_start
.local _bss1_end
_bss1_end:
	.long __bss1_end

.local _x86boot_start
_x86boot_start:
	.long _start
#if defined (CONFIG_AUTODLOADER)
.extern fdl1_check_autodloader
#endif

    .align 32
#ifdef CONFIG_VOL_PARA
_vol_para:
    .long   vol_para
#endif

/*
 * the actual reset code
 */

reset:
	/*
	 * disable caches
	 */
	movl	%cr0, %eax
	orl	$0x40000000, %eax
	movl	%eax, %cr0
	wbinvd

	movl	$FDL1_STACK, %esp

	movl	$__bss0_start, %edi
	movl	$__bss0_end, %ecx
	subl	%edi, %ecx
	xorl	%eax, %eax
	cld
	rep	stosb

	movl	$__bss1_start, %edi
	movl	$__bss1_end, %ecx
	subl	%edi, %ecx
	xorl	%eax, %eax
	cld
	rep	stosb
/*	call	Chip_Init */

	call    Chip_Init
	call	main

