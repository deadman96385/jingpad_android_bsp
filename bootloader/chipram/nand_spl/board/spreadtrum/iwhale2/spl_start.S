//
#include <config.h>
#include <common.h>
//

#define SVC_STACK_TEMP CONFIG_SVC_STACK_TEMP
#define SPL_STACK      CONFIG_SPL_STACK
#define TEMP_STACK_DDR CONFIG_TEMP_STACK_DDR

#define IA32_MTRR_DEF_TYPE 0x2FF
#define IA32_MTRR_PHYSBASE0 0x200
#define IA32_MTRR_PHYSMASK0 0x201

#define SRAM_START 0xE6000000

.global	_start

.code32

_start:
	jmp	reset

/*************************************************************************
 *
 * 32 byte jump
 * 2048-32 byte
 *
 * 0xFFFB0800
 *
 *************************************************************************/
#ifdef CONFIG_VOL_PARA
_vol_para:
	.long	vol_para
#endif

_hang:
	.long	do_hang

do_hang:
	jmp	do_hang

clear_bss:
	movl	$__bss_start, %edi
	movl	$__bss_end, %ecx
	subl	%edi, %ecx
	xorl	%eax, %eax
	cld
	rep	stosb
	ret

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
 * These are defined in the board-specific linker script.
 */

.align	4

.global	_bss_start_ofs
_bss_start_ofs:
	.long	__bss_start

.global	_bss_end_ofs
_bss_end_ofs:
	.long	__bss_end

/*
 * the actual reset code
 */

reset:
/* set up temp stack */
	movl	$SVC_STACK_TEMP, %esp

	call	cpu_init_crit

	call 	clear_bss
	movl	$TEMP_STACK_DDR , %esp
	call    Chip_Init
	movl	$SPL_STACK, %esp
	jmp	nand_boot

/*************************************************************************
 * void relocate_code (addr_sp, gd, addr_moni)
 *
 * This "function" does not return, instead it continues in RAM
 * after relocating the monitor code.
 *
 *************************************************************************/
.global	relocate_code

relocate_code:
	ret

/*************************************************************************
 *
 * CPU_init_critical registers
 *
 * setup important registers
 * setup memory timing
 *
 *************************************************************************/
cpu_init_crit:

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

/* Variable Range MTRR #1: xxxx0000-xxx3FFFF, WP (SRAM) */
	movl	$0, %edx
	movl	$(SRAM_START | 0x0005), %eax
	wrmsr
	incl	%ecx
	movl	%ebx, %edx
	movl	$0xFFFC0800, %eax
	wrmsr
	incl	%ecx

/* disable the rest of Variable Range MTRR */
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

	/*
	 * Jump to board specific initialization...
	 * The Mask ROM will have already initialized
	 * basic memory. Go here to bump up clock rate and handle
	 * wake up conditions.
	 */
	ret
