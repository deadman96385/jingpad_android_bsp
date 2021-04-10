    .text

    .global arm_spsr_read
    .global arm_scr_el3_read
    .global arm_scr_el3_write
    .global arm_current_el_read
    .global arm_exception_to_el1
    .global arm_exception_to_el2
    .global arm_exception_to_el3
    .global arm_secure_state_switch
    .global arm_spsr_set
    .global arm_elr_set
    .global arm_eret
    .global arm_set_sp
    .global arm_get_sp

#define HVBARADDR	0x1000

arm_spsr_read:
    mrs   x0, SPSR_EL3
    ret

arm_scr_el3_read:
    mrs   x0, SCR_EL3
    ret

arm_scr_el3_write:
    msr   SCR_EL3, x0
    ret

arm_current_el_read:
    mrs   x0, CurrentEL
    lsr   x0, x0, #2
    ret

arm_exception_to_el1:
    dsb sy
    isb
    svc #0
    ret

arm_exception_to_el2:
    dsb sy
    isb
    hvc #0
    ret

arm_exception_to_el3:
    dsb sy
    isb
    smc #0
    ret

arm_secure_state_switch:
    mrs x1, scr_el3
    mov x2, #1
    bic x1, x1, x2
    orr x1, x1, x0
    msr scr_el3, x1
    isb
    ret

arm_spsr_set:
    mov x1, x0
    mrs x0, CurrentEl
    lsr x0, x0, #2
    cmp x0, #0
    b.eq spsr_returned
    cmp x0, #3
    b.eq write_spsr_el3
    cmp x0, #2
    b.eq write_spsr_el2
    msr spsr_el1, x1
    b spsr_returned
write_spsr_el2:
    msr spsr_el2, x1
    b spsr_returned
write_spsr_el3:
    msr spsr_el3, x1
spsr_returned:
    isb
    ret

arm_elr_set:
    mov x1, x0
    mrs x0, CurrentEl
    lsr x0, x0, #2
    cmp x0, #0
    b.eq elr_returned
    cmp x0, #3
    b.eq write_elr_el3
    cmp x0, #2
    b.eq write_elr_el2
    msr elr_el1, x1
    b elr_returned
write_elr_el2:
    msr elr_el2, x1
    b elr_returned
write_elr_el3:
    msr elr_el3, x1
elr_returned:
    isb
    ret

arm_eret:
    mov x0,x30
    bl arm_elr_set
    dsb sy
    eret
    isb
    ret

.global arm_eret_1
arm_eret_1:
    ldr x0, =0x80000000
    msr vbar_el1, x0
    msr vbar_el2, x0
    msr vbar_el3, x0
    dsb sy
    eret
    isb
    ret

arm_set_sp:
    mov sp, x0
    ret

arm_get_sp:
	mov x0, sp
    ret

/* .global el1_sync_32
    .global el1_sync_64
    .global el2_sync_64
    .global el3_sync_64
    .extern return_addr

el1_sync_32:
 ldr x30,=return_addr
     ret
el1_sync_64:
 ldr x30,=return_addr
     ret
el2_sync_64:
 ldr x30,=return_addr
     ret
el3_sync_64:
     ldr x30,=return_addr
     ret
 */
