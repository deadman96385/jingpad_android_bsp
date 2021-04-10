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
#ifndef __TRUSTZONE_DEF_H__
#define __TRUSTZONE_DEF_H__

#define ARM7_SPACE_EN 0x402e3084
#define SECURE_EN     0x402e3080

#define DAIF_FIQ_BIT		(1 << 0)
#define DAIF_IRQ_BIT		(1 << 1)
#define DAIF_ABT_BIT		(1 << 2)
#define DAIF_DBG_BIT		(1 << 3)

#define DISABLE_ALL_EXCEPTIONS \
		(DAIF_FIQ_BIT | DAIF_IRQ_BIT | DAIF_ABT_BIT | DAIF_DBG_BIT)

#define MODE_SP_SHIFT		0x0
#define MODE_SP_MASK		0x1
#define MODE_SP_EL0		0x0
#define MODE_SP_ELX		0x1

#define MODE_RW_SHIFT		0x4
#define MODE_RW_MASK		0x1
#define MODE_RW_64			0x0
#define MODE_RW_32			0x1

#define MODE_EL_SHIFT		0x2
#define MODE_EL_MASK		0x3
#define MODE_EL3		0x3
#define MODE_EL2		0x2
#define MODE_EL1		0x1
#define MODE_EL0		0x0

#define SPSR_DAIF_SHIFT		6
#define SPSR_DAIF_MASK		0xf


void          smc            (unsigned long, unsigned long);
unsigned long read_scr       (void);
void          write_scr      (unsigned long);
int           jmp_to_bl31    (unsigned long, unsigned long);
int           trustzone_entry(unsigned long);

#endif /* __TRUSTZONE_DEF_H__ */


