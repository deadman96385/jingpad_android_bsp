/* ============================================================================
@
@ MMU function for armV7
@ steve.zhan
@ Spreadtrum Communications Inc.
@
@ ============================================================================
*/
/*
@AREA mmu_functions, CODE, READONLY
@    CODE32

#include <config.h>
@   Initialize the MMU
@
*/
.globl g_mmu_page_table
.globl MMU_EnableIDCM
.globl MMU_InvalideDCACHEALL
.globl MMU_InvalideICACHEALL
.globl Dcache_InvalRegion
.globl Dcache_CleanRegion

/*
@============================================================================
@ Dcache_InvalRegion
@
@ PROTOTYPE
@ void Dcache_InvalRegion(void *addr, unsigned int length)
@
@ steve.zhan
@ DESCRIPTION
@ Invalid a memory region in the cache.
@============================================================================
*/
Dcache_InvalRegion:
/*
    stmfd sp!, {r0-r3, lr}
    add r1,r1,r0

    mrc p15, 1, r3, c0, c0, 0
    and r3, r3, #7
    mov r2, #16
    mov r2, r2, lsl r3

    sub r3, r2, #1
    tst r0, r3
    bic r0, r0, r3
    mcrne p15, 0, r0, c7, c14, 1

    tst r1, r3
    bic r1, r1, r3
    mcrne p15, 0, r1, c7, c14, 1

1:
    mcr p15, 0, r0, c7, c6, 1
    add r0, r0, r2
    cmp r0, r1
    blo 1b
    .word 0xf57ff04f

    ldmfd sp!, {r0-r3, lr}
    */
/*
@============================================================================
@ Dcache_CleanRegion
@
@ PROTOTYPE
@ void Dcache_CleanRegion(void *addr, unsigned int length)
@
@ steve.zhan
@ DESCRIPTION
@ clean a memory region in the cache.
@============================================================================
*/
Dcache_CleanRegion:
/*
	stmfd sp!, {r0-r3, lr}

	add r1,r1,r0
	mrc p15, 1, r3, c0, c0, 0
	and r3, r3, #7
	mov r2, #16
	mov r2, r2, lsl r3

	sub r3, r2, #1
	bic r0, r0, r3

1:
	mcr p15, 0, r0, c7, c10, 1 
	add r0, r0, r2
	cmp r0, r1
	blo 1b

	.word 0xf57ff04f
	.word 0xf57ff05f
	ldmfd sp!, {r0-r3,pc}
*/
#if 0 
MMU_InvalideICACHEALL:
    stmfd   sp!, {r0, lr}          /*  @ save lr_USR and non-callee*/

    MOV     r0, #0
    MCR     p15, 0, r0, c7, c5, 0     /*  @Invalidate(flush)the ICache*/
    MCR     p15, 0, r0, c8, c5, 0     /*  @flush ITLB only*/
    NOP
    NOP
    NOP
    NOP
    NOP

    ldmfd   sp!, {r0, PC}

#endif
MMU_EnableIDCM:
#if 0
/*
@ save lr_USR and non-callee*/
    stmfd   sp!, {r0-r3, lr}

/*@   Set the MMU page table address*/
    LDR     r2, =g_mmu_page_table
    LDR     r2, [r2]
    MCR     p15, 0, r2, c2, c0, 0

/*@   Domain Access Control: set all domains to manager*/
    LDR     r0, =0xFFFFFFFF
    MCR     p15, 0, r0, c3, c0, 0
/*
@   Enable the ICache, DCache, write buffer, MMU*/
    MRC     p15, 0, r0, c1, c0, 0
    LDR     r1, =0x107D
    ORR     r0, r0, r1
    MCR     p15, 0, r0, c1, c0, 0
/*
@   Delay for the operations to finish*/
    NOP
    NOP
    NOP
    NOP
    NOP
    ldmfd   sp!, {r0-r3, PC}

v7_flush_dcache_all:
	stmfd	sp!,	{r0-r3,lr}
	mov r1, #0x1f0
	add r1,r1,#0xf

	.word 0xf57ff05f

	mrc p15, 1, r3, c0, c0, 0

	and r3, r1, r3, lsr #13
	mov r0, #0

way_loop2:
	mov r1, #0

set_loop2:
	mov r2, r0, lsr #30
	orr r2, r1, lsr #5
	mcr p15, 0, r2, c7 ,c14, 2
	and r1, r1, #1
	cmp r1, r3
	ble set_loop2

	add r0, r0, #1
	cmp r0, #4
	blt way_loop2

	.word 0xf57ff04f
	.word 0xf57ff06f
	ldmfd sp!, {r0-r3,pc}

#endif
v7_flush_dcache_all1:
	.word 0xf57ff05f
        /*
	mrc	p15, 1, r0, c0, c0, 1		         @ read clidr
	ands	r3, r0, #0x7000000		@ extract loc from clidr
	mov	r3, r3, lsr #23			         @ left align loc bit field
	beq	finished			                  @ if loc is 0, then no need to clean
	mov	r10, #0				        @ start clean at cache level 0
loop1:
	add	r2, r10, r10, lsr #1		@ work out 3x current cache level
	mov	r1, r0, lsr r2			@ extract cache type bits from clidr
	and	r1, r1, #7			@ mask of the bits for current cache only
	cmp	r1, #2				@ see what cache we have at this level
	blt	skip				@ skip if no cache, or just i-cache
	mcr	p15, 2, r10, c0, c0, 0		@ select current cache level in cssr
	.word 0xf57ff06f
	mrc	p15, 1, r1, c0, c0, 0		@ read the new csidr
	and	r2, r1, #7			@ extract the length of the cache lines
	add	r2, r2, #4			@ add 4 (line length offset)
	ldr	r4, =0x3ff
	ands	r4, r4, r1, lsr #3		@ find maximum number on the way size
	clz	r5, r4				@ find bit position of way size increment
	ldr	r7, =0x7fff
	ands	r7, r7, r1, lsr #13		@ extract max number of the index size
loop2:
	mov	r9, r4				@ create working copy of max way size
loop3:
	orr	r11, r10, r9, lsl r5	        @ factor way and cache number into r11
	orr	r11, r11, r7, lsl r2	        @ factor index number into r11
	mcr	p15, 0, r11, c7, c14, 2		@ clean & invalidate by set/way
	subs	r9, r9, #1			@ decrement the way
	bge	loop3
	subs	r7, r7, #1			@ decrement the index
	bge	loop2
skip:
	add	r10, r10, #2			@ increment cache number
	cmp	r3, r10
	bgt	loop1
finished:
	mov	r10, #0				@ swith back to cache level 0
	mcr	p15, 2, r10, c0, c0, 0		@ select current cache level in cssr
	.word 0xf57ff04f
	.word 0xf57ff06f
	mov pc, lr
*/

.globl	MMU_DisableIDCM
MMU_DisableIDCM:
/*
	stmfd   sp!, {r0-r12, lr}
@   Disable the ICache, DCache, write buffer, MMU*/
#if 0
	MRC     p15, 0, r0, c1, c0, 0
	LDR     r1, =0x1005
	BIC     r0, r0, r1
	ORR     r0, r0, #0x8    /* @Bit_7 must be one when write c1@*/
	MCR     p15, 0, r0, c1, c0, 0

	bl v7_flush_dcache_all1

	mov r0, #0
	mcr p15, 0, r0, c7, c5, 0
	mcr p15, 0, r0, c8, c7, 0
	NOP
	NOP
	NOP
	NOP
#endif
        /*
@   Return
	ldmfd   sp!, {r0-r12, PC}            @ restore registers*/

