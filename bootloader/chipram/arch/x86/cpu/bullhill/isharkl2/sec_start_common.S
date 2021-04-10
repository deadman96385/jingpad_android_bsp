
//
#include <config.h>
#include <common.h>
//

.globl _start

.code32

_start:
	jmp	reset

	.align	8
	.long	get_sec_callback
	.long	0

/* 0x10 */
	.rept   124
	.long   0xABCD1234
	.endr

/* 0x200 */
	.rept    128
	.long   0x11223344
	.endr
