
//
#include <config.h>
#include <common.h>
//

.globl _start
_start: b	reset
	ldr	pc, =0xFFFF0004
	ldr	pc, =0xFFFF0008
	ldr	pc, =0xFFFF000C
	ldr	pc, =0xFFFF0010
	ldr	pc, =0xFFFF0014
	ldr	pc, =0xFFFF0018
	/*ldr	pc, =0xFFFF001C*/
	.word	get_sec_callback

/* 0x20 */
	.rept   120
	.long   0xABCD1234
	.endr

/* 0xC0 */
/*	.rept   208
	.long   0xAABBCCDD
	.endr
*/
/* 0x200 */
	#.rept   256
	.rept    128
	.long   0x11223344
	.endr


