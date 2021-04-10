
//
#include <config.h>
#include <common.h>
//

#define SVC_STACK_TEMP 0x5000CFF0 //for shark
#define SPL_STACK      0x808f0000

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
.globl reset
#else
.globl _start
_start: b	reset
	ldr	pc, =0xFFFF0004
	ldr	pc, =0xFFFF0008
	ldr	pc, =0xFFFF000C
	ldr	pc, =0xFFFF0010
	ldr	pc, =0xFFFF0014
	ldr	pc, =0xFFFF0018
	/*ldr	pc, =0xFFFF001C*/
	.word	get_sec_callback

/* 0x20 */
	.rept   120
	.long   0xABCD1234
	.endr

/* 0xC0 */
/*	.rept   208
	.long   0xAABBCCDD
	.endr
*/
/* 0x200 */
#	.rept   256
	.rept    128
	.long   0x11223344
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
	bl	SecClkConfig

	ldr	r0, =0x50005C00 /* spl start */
	ldr	r1, =0x5200     /* spl check length */
	ldr	r2, =0x5000AE00 /* spl vlr info */
	ldr	r3, =0x50005A00 /* spl key info */
   	#bl	secure_check

	ldr	pc, =0x50003C00
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
	mov	r0, #0			@ set up for MCR
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
	mov	pc, lr			@ back to my caller

