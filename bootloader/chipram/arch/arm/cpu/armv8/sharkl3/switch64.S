/*@AREA armv8_switch_to64, CODE, READONLY
@    CODE32
*/
.globl switch_to_arch_64


/*
@============================================================================
@ switch to arch 64 for armv8
@
@ PROTOTYPE
@ void switch_to_arch_64(void)
@
@============================================================================
switch_to_arch_64:
	mov r0, #3
	dsb sy
	mrc p15, 0, r1, c12, c0, 2
	mcr p15, 0, r0, c12, c0, 2
	isb sy
loop:
	wfi
        
        b loop  */
