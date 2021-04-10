/*
 * Copyright (c) 2013-2014, ARM Limited and Contributors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <common.h>

//#define U_BOOT_CTX_BASE  (TRUSTZONE_ADR + 0x100)
//fix me
#define U_BOOT_CTX_BASE  (0x50808000 + 0x100)

#define ESR_EC_SHIFT			26
//#define ESR_EC_MASK			0x3f
#define ESR_EC_LENGTH			6
#define EC_AARCH64_SMC                  0x17
/*
 * This macro is used to create a function label and place the
 * code into a separate text section based on the function name
 * to enable elimination of unused code during linking
 */
.macro func _name
.section .text.\_name, "ax"
.type \_name, %function
\_name:
.endm

//------------------------------------------------------------------------------------

	.globl	read_scr
	.globl	write_scr
	.globl  smc

func smc
	smc #0
	ret

func write_scr
	msr	scr_el3, x0
	ret

func read_scr
	mrs	x0, scr_el3
	ret

	.globl	jmp_to_bl31
func jmp_to_bl31
	/*disable EL2 trap*/
        //mov     x2, #0x33ff
        //msr     cptr_el2, x2
	/*spsr*/
	msr	spsr_el3, x1
	/*jump to */
	msr	elr_el3, x0
	/*Save X30lr, SP, general regs(9~29) to spec mem*/
	ldr     x2,  =U_BOOT_CTX_BASE
	mov     x3,  sp
	str     x3,  [x2, #0]
	str     x30, [x2, 0x8]
        stp     x9, x10, [x2, 0x10]
	stp     x11,x12, [x2, 0x20]
	stp     x13,x14, [x2, 0x30]
	stp     x15,x16, [x2, 0x40]
	stp     x17,x18, [x2, 0x50]
        stp     x19,x20, [x2, 0x60]
	stp     x21,x22, [x2, 0x70]
	stp     x23,x24, [x2, 0x80]
	stp     x25,x26, [x2, 0x90]
	stp     x27,x28, [x2, 0xa0]
	str     x29, [x2, 0xa8]
        //b .
	eret

