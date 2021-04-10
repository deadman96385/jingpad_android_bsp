
//
#include <config.h>
#include <common.h>
#include <asm/macro.h>
#include <asm/arch-whale/mmu.h>
#include <linux/linkage.h>
//

#define SVC_STACK_TEMP 0x00006000 //for whale,whale2
#define SPL_STACK      0x808f0000
#define COUNTER_FREQUENCY             (0x1800000)     /* 24MHz */
.globl _start
_start: 
        b	reset
        .align 3
#if 0
.lobl	_TEXT_BASE
_TEXT_BASE:
	.quad	CONFIG_SYS_TEXT_BASE
#endif

ENTRY(clear_bss)
    mov     x29, lr                 /* Save LR */
             ldr     x0, =_bss_start_ofs                /* this is auto-relocated! */
             ldr     x1, =_bss_end_ofs                  /* this is auto-relocated! */
             mov     x2, #0
clear_loop:  str     x2, [x0]
             add     x0, x0, #8
             cmp     x0, x1       
             b.lo    clear_loop
            mov     lr, x29                 /* Restore LR */
             ret
ENDPROC(clear_bss)

/*
 * These are defined in the board-specific linker script.
 */
.globl _bss_start_ofs
_bss_start_ofs:
	.word __bss_start

.globl _bss_end_ofs
_bss_end_ofs:
	.word __bss_end

reset:
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

        ldr x0,=SVC_STACK_TEMP
        mov sp,x0
        bl     clear_bss 
	/* Processor specific initialization */
        bl      Chip_Init
master_cpu:
            /*set STACK*/
             ldr x0, =SPL_STACK
             mov sp, x0
	     b   nand_boot	 /*_main*/


	.globl	relocate_code
relocate_code:
