
//
#include <config.h>
#include <common.h>
//

#define SVC_STACK_TEMP 0x5000CFF0 //for shark
#define SPL_STACK      0x808f0000

.globl _start
_start: b	reset
	ldr	pc, =0xFFFF0004 
	ldr	pc, =0xFFFF0008 
	ldr	pc, =0xFFFF000C 
	ldr	pc, =0xFFFF0010 
	ldr	pc, =0xFFFF0014 
	ldr	pc, =0xFFFF0018 
	ldr	pc, =0xFFFF001C 

/*************************************************************************
 *
 * 32 byte jump
 * 2048-32 byte
 *
 * 0x50000800
 *
 *************************************************************************/
#ifdef CONFIG_VOL_PARA
_vol_para:
	.word	vol_para
#endif

_hang:
	.word	do_hang

do_hang:
	b	do_hang

clear_bss:
	mov	r2, #0x00000000		/* clear                            */
clbss_l:str	r2, [r0]		/* clear loop...                    */
	add	r0, r0, #4
	cmp	r0, r1
	ble	clbss_l
	bx	r14

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
.globl _bss_start_ofs
_bss_start_ofs:
	.word __bss_start

.globl _bss_end_ofs
_bss_end_ofs:
	.word __bss_end

/*
 * the actual reset code
 */

reset:
	/*
	 * set the cpu to SVC32 mode
	 */
	mrs	r0, cpsr
	bic	r0, r0, #0x1f
	orr	r0, r0, #0xd3
	msr	cpsr,r0

	/*set up temp stack*/
	LDR 	sp, =SVC_STACK_TEMP

	/* the mask ROM code should have PLL and others stable */
	mrc 	p15, 0, r1, c1, c0, 0
	bic 	r1, #0x5
	mcr 	p15, 0, r1, c1, c0, 0

	bl	cpu_init_crit

	ldr 	r0, _bss_start_ofs
	ldr 	r1, _bss_end_ofs
	bl 	clear_bss

	bl	Chip_Init
	ldr     sp, =SPL_STACK 
	b	nand_boot

/*************************************************************************
 * void relocate_code (addr_sp, gd, addr_moni)
 *
 * This "function" does not return, instead it continues in RAM
 * after relocating the monitor code.
 *
 *************************************************************************/
	.globl	relocate_code
relocate_code:
	mov 	pc, lr

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
	 * Invalidate L1 I/D
	 */
	ldr	r0, =0			@ set up for MCR
	mcr	p15, 0, r0, c8, c7, 0	@ invalidate TLBs
	mcr	p15, 0, r0, c7, c5, 0	@ invalidate icache

	/*
	 * disable MMU stuff and caches
	 */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #0x00002000	@ clear bits 13 (--V-)
	bic	r0, r0, #0x00000007	@ clear bits 2:0 (-CAM)
	orr	r0, r0, #0x00000002	@ set bit 1 (--A-) Align
	orr	r0, r0, #0x00000800	@ set bit 12 (Z---) BTB
	mcr	p15, 0, r0, c1, c0, 0

	/*
	 * Jump to board specific initialization...
	 * The Mask ROM will have already initialized
	 * basic memory. Go here to bump up clock rate and handle
	 * wake up conditions.
	 */
	mov	ip, lr			@ persevere link reg across call
	mov	lr, ip			@ restore link
	bx	lr			@ back to my caller

