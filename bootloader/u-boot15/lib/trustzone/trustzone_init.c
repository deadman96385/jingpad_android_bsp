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
//#include <stdint.h>
#include "trustzone_def.h"
#include "secure_efuse.h"

#define SPSR_64(el, sp, daif)				\
	(MODE_RW_64 << MODE_RW_SHIFT |			\
	((el) & MODE_EL_MASK) << MODE_EL_SHIFT |	\
	((sp) & MODE_SP_MASK) << MODE_SP_SHIFT |	\
	((daif) & SPSR_DAIF_MASK) << SPSR_DAIF_SHIFT)

void io_or_32(unsigned long addr, unsigned int val){

 unsigned int reg = *(volatile unsigned int*)addr;
 *(volatile unsigned int*)addr = reg | val;

}

void io_clr_32(unsigned long addr, unsigned int val){
   unsigned int reg = *(volatile unsigned int*)addr;
  *(volatile unsigned int*)addr = reg & ~val;

}

void mmio_write_32(uintptr_t addr, uint32_t value)
{
	*(volatile uint32_t*)addr = value;
}


extern unsigned int masterkey[8];

inline void tzRam_init(void)
{

        //io_or_32(0x402b00b0, 0x00000100);
        //io_or_32(0x402e0114, 0x00000010);

        //io_clr_32(0x402b00b0, 0x00000100);
        //io_clr_32(0x402e0114, 0x00000010);

	io_clr_32(0x402e0124,0x1);

        io_or_32(ARM7_SPACE_EN, 0x01);
//        io_or_32(SECURE_EN,     0x01);

//      mmio_write_32(0x50800000, 0xabababab);

}


int trustzone_entry(unsigned long bl31Addr){
	uint32_t spsr_bl31 = SPSR_64(MODE_EL3, MODE_SP_ELX, DISABLE_ALL_EXCEPTIONS);
	tzRam_init();

	memcpy(TRUSTZONE_ADR+0x200,TRUSTRAM_ADR,TRUSTZONE_SIZE-0x200);
	#if 0 //build error tmp not used
        memset(masterkey,    0x0, 32);
	read_master_key();

        memcpy(TRUSTZONE_ADR+0x1c0, masterkey, 32);
        debugf("before Jump to BL31 \n");
	#endif
	debugf("tzRam_init done SPSR_EL3[%x]\n", spsr_bl31);

	jmp_to_bl31(bl31Addr,spsr_bl31);
	//debugf("return to Uboot 64!\n");
}


