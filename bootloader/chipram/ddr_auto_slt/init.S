
#include <config.h>
#include <common.h>
//


#if   defined CONFIG_SC8825
#define DDR_SCAN_STACK 0x00028000
#elif defined CONFIG_SC8830 || defined(CONFIG_SC9630) || defined(CONFIG_SCX35L64)
#define DDR_SCAN_STACK 0x5000CFF0
#elif defined CONFIG_SC7710G2
#define DDR_SCAN_STACK 0x40008000
#else
#define DDR_SCAN_STACK 0x31000000
#endif

/*
 *************************************************************************
 *
 * Jump vector table as in table 3.1 in [1]
 *
 *************************************************************************
 */


.globl _start
_start:
	b	reset
/* 0x20 */
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
	.word __bss0_start
.local _bss0_end
_bss0_end:
	.word __bss0_end
.local _bss1_start
_bss1_start:
	.word __bss1_start
.local _bss1_end
_bss1_end:
	.word __bss1_end

.local _armboot_start
_armboot_start:
	.word _start
    .align 5
#ifdef CONFIG_VOL_PARA
_vol_para:
    .word   vol_para
#endif

/*
 * the actual reset code
 */
reset:
	/*
	 * set the cpu to SVC32 mode
	 */
	mrs	r0,cpsr
	bic	r0,r0,#0x1f
	orr	r0,r0,#0xd3
	msr	cpsr,r0

	MRC p15,0,r0,c1,c0,0

	BIC r0,r0,#0x80
	BIC r0,r0,#1	/*disable MMU*/
	LDR r1,=0x1004
	BIC r0,r0,r1	/*disable cache*/

	MCR p15,0,r0,c1,c0,0

	/*set stack limit to 0*/
	MOV R10, #0
	ldr sp, =DDR_SCAN_STACK

	ldr r0, _bss0_start
	ldr r1, _bss0_end
	bl  clear_bss

	/* bl  sdram_init */
	bl  Chip_Init

	ldr r0, _bss1_start
	ldr r1, _bss1_end
	bl  clear_bss

	b   main

clear_bss:
	mov	r2, #0x00000000		/* clear                            */
clbss_l:str	r2, [r0]		/* clear loop...                    */
	add	r0, r0, #4
	cmp	r0, r1
	ble	clbss_l
	bx	r14

