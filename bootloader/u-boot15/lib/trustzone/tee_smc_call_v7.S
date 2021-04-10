
.macro FUNC name colon
.global \name
.type \name , %function
\name \colon
.endm

.macro END_FUNC name
.size \name , .-\name
.endm

    .globl tee_smc_call

FUNC tee_smc_call, :
        push    {r4-r8, lr}
        mov     r8, r0
        ldm     r8, {r0-r7}
.arch_extension sec
        smc     #0
        stm     r8, {r0-r7}
        pop     {r4-r8, pc}
END_FUNC tee_smc_call


