
//
#include <config.h>
#include <common.h>
//

#define IA32_MTRR_DEF_TYPE 0x2FF

#define SVC_STACK_TEMP 0xFFFBCFF0 //for iShark
#define SPL_STACK      0x808F0000

/*************************************************************************
 *
 * Startup Code (reset vector)
 *
 * do important init only if we don't start from memory!
 * setup Memory and board specific bits prior to relocation.
 * relocate armboot to ram
 * setup stack
 *
 *************************************************************************/

/*
 * the actual reset code
 */

#ifdef CONFIG_SECURE_BOOT
.global	reset
#else
.global	_start

.code32

_start:
	jmp	reset

	.align	8
	.long	get_sec_callback
	.long	0

/* 0x10 */
	.rept	124
	.long	0xABCD1234
	.endr

/* 0x200 */
	.rept	128
	.long	0x11223344
	.endr
#endif
/*************************************************************************
 *
 * Startup Code (reset vector)
 *
 * do important init only if we don't start from memory!
 * setup Memory and board specific bits prior to relocation.
 * relocate armboot to ram
 * setup stack
 *
 *************************************************************************/

/*
 * the actual reset code
 */

reset:
	/*set up temp stack*/
	movl	$SVC_STACK_TEMP, %esp

	call	cpu_init_crit
	call	SecClkConfig

	movl	$0xFFFB2C00, %esi /* spl start */
	movl	$0x5200, %ecx     /* spl check length */
	movl	$0xFFFB7E00, %edx /* spl vlr info */
	movl	$0xFFFB2A00, %ebx /* spl key info */

	movl	$0xFFFB0C00, %eax
	jmpl	%eax

/*************************************************************************
 *
 * CPU_init_critical registers
 *
 * setup important registers
 * setup memory timing
 *
 *************************************************************************/
cpu_init_crit:
	/*
	 * disable caches
	 */
	movl	%cr0, %eax
	orl	$0x40000000, %eax
	movl	%eax, %cr0
	wbinvd
	movl	$0, %eax
	movl	$0, %edx
	movl	$IA32_MTRR_DEF_TYPE, %ecx
	wrmsr


	/*
	 * Jump to board specific initialization...
	 * The Mask ROM will have already initialized
	 * basic memory. Go here to bump up clock rate and handle
	 * wake up conditions.
	 */
	ret
