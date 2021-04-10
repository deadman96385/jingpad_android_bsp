/*
	tentry.S
*/

.macro FUNC name colon
.global \name
.type \name , %function
\name \colon
.endm

.macro DATA name colon
.global \name
.type \name , %object
\name \colon
.endm

.macro END_DATA name
.size \name , .-\name
.endm

.macro END_FUNC name
.size \name , .-\name
.endm

	.globl tos_entry

.align 2

FUNC tos_entry, :
	mov lr, r1
	mov r12, r0

	mov r0, #0
	mov r1, #0
	mov r2, #0
	mov r3, #0

	bx  r12
END_FUNC tos_entry

