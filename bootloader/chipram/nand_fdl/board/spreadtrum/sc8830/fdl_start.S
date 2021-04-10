
#include <config.h>
#include <common.h>
//


#if defined(CONFIG_ARCH_SCX35L2)
#define FDL1_STACK 0x5000CFF0
#elif defined CONFIG_SOC_PIKE2
#define FDL1_STACK 0x5000EFF0
#endif

#define SPL_DDR_STACK      0x808f0000
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

#if defined (CONFIG_SC8825) || defined (CONFIG_SC7710G2) || defined (CONFIG_SC8830) || defined(CONFIG_SC9630)  || defined(CONFIG_SCX35L64)
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
#else
.local _bss_start
_bss_start:
	.word __bss_start
.local _bss_end
_bss_end:
	.word _end
#endif
.local _armboot_start
_armboot_start:
	.word _start
#if defined (CONFIG_AUTODLOADER)
.extern fdl1_check_autodloader
#endif

    .align 5

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
	ldr sp, =FDL1_STACK
#if defined (CONFIG_SC8825) || defined (CONFIG_SC7710G2) || defined (CONFIG_SC8830) || defined(CONFIG_SC9630)  || defined(CONFIG_SCX35L64)
	ldr r0, _bss0_start
	ldr r1, _bss0_end
	bl  clear_bss
#endif


	bl  Chip_Init

	ldr sp, =SPL_DDR_STACK
#if defined(CONFIG_SC9630) || defined(CONFIG_SCX35L64)
	ldr r0, _bss1_start
	ldr r1, _bss1_end
	bl  clear_bss
#else
	ldr r0, _bss_start
	ldr r1, _bss_end
	bl  clear_bss
#endif

	b   main

clear_bss:
	mov	r2, #0x00000000		/* clear                            */
clbss_l:str	r2, [r0]		/* clear loop...                    */
	add	r0, r0, #4
	cmp	r0, r1
	ble	clbss_l
	bx	r14

