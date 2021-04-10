
#include <config.h>
#include <common.h>
#include <asm/macro.h>
#include <asm/arch-whale/mmu.h>
#include <linux/linkage.h>
//

#if defined(CONFIG_SOC_SHARKLE) || defined(CONFIG_SOC_SHARKL3) || defined(CONFIG_SOC_WHALEK)
#define FDL1_STACK 0x3000 /*for sharkle*/
#define DDR_STACK 0x808f0000
#elif defined(CONFIG_SOC_SHARKLJ1)
#define FDL1_STACK 0x5000D000 /*for sharklj1*/
#define DDR_STACK 0x808f0000
#else
#define FDL1_STACK 0x00006000 /*for whale,whale2*/
#define DDR_STACK 0x808f0000
#endif
/*
 *************************************************************************
 *
 * Jump vector table as in table 3.1 in [1]
 *
 *************************************************************************
 */

#define COUNTER_FREQUENCY             (0x1800000)     /* 24MHz */
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

#if defined(CONFIG_SCX35L64) ||defined(CONFIG_WHALE)|| defined (CONFIG_WHALE2)|| defined (CONFIG_SOC_SHARKLJ1) || defined(CONFIG_SOC_SHARKLE) || defined(CONFIG_SOC_SHARKL3) || defined(CONFIG_SOC_WHALEK)
.local _bss1_start
_bss1_start:
	.word __bss1_start
.local _bss1_end
_bss1_end:
	.word __bss1_end
.local _bss0_start
_bss0_start:
	.word __bss0_start
.local _bss0_end
_bss0_end:
	.word __bss0_end
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
/*add refer to chipram start*/

	/*
	 * Could be EL3/EL2/EL1, Initial State:
	 * Little Endian, MMU Disabled, i/dCache Disabled
	 */


	switch_el x1, 3f, 2f, 1f

3:      msr     vbar_el3, x0
	msr	cptr_el3, xzr			/* Enable FP/SIMD */
	ldr	x0, =COUNTER_FREQUENCY
	msr	cntfrq_el0, x0			/* Initialize CNTFRQ */
	b	0f
2:	msr	vbar_el2, x0
	mov	x0, #0x33ff
	msr	cptr_el2, x0			/* Enable FP/SIMD */
	b	0f
1:	msr	vbar_el1, x0
	mov	x0, #3 << 20
	msr	cpacr_el1, x0			/* Enable FP/SIMD */
0:
	/* Cache/BPB/TLB Invalidate */

	bl	__asm_flush_dcache_all		/* dCache clean&invalidate */
	bl	__asm_invalidate_icache_all	/* iCache invalidate */
	bl	__asm_invalidate_tlb_all	/* invalidate TLBs */

        /*set STACK*/
        ldr x0, =FDL1_STACK
        mov sp, x0

        bl clear_bss0
        bl clear_bss
        bl  Chip_Init
        /*clear bss*/
        ldr x0, =DDR_STACK
        mov sp, x0

        b main

/*
 * Clear BSS section
 */
ENTRY(clear_bss)
    mov     x29, lr                 /* Save LR */
    ldr     x0, =__bss1_start                /* this is auto-relocated! */
    ldr     x1, =__bss1_end                  /* this is auto-relocated! */
            mov     x2, #0
clear_loop:  str     x2, [x0]
             add     x0, x0, #8
             cmp     x0, x1
             b.lo    clear_loop
    mov     lr, x29                 /* Restore LR */
             ret
ENDPROC(clear_bss)

ENTRY(clear_bss0)
    mov     x29, lr                 /* Save LR */
    ldr     x0, =__bss0_start                /* this is auto-relocated! */
    ldr     x1, =__bss0_end                  /* this is auto-relocated! */
            mov     x2, #0
clear_loop0:  str     x2, [x0]
             add     x0, x0, #8
             cmp     x0, x1
             b.lo    clear_loop0
    mov     lr, x29                 /* Restore LR */
             ret
ENDPROC(clear_bss0)
