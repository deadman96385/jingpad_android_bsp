#ifndef __DMC_SPRD_MISC_H__
#define __DMC_SPRD_MISC_H__

#if CONFIG_SPRD_DMC_R1P0
#include "dmc_sprd_r1p0.h"
#endif

#if 0
#define dmc_sprd_delay(x)	\
	do { \
		volatile int i; \	
		volatile unsigned int val; \
		for (i=0; i<x; i++)\
		{ \
			val = *(volatile unsigned int *)0x30000218; \
		} \
	} while(0);
#endif

void dmc_sprd_delay(int x);

#define REG32(x)   (*((volatile u32 *)(x)))

#if CONFIG_SPRD_DMC_R1P0
u32 u32_bits_set(u32 orgval,u32 start_bitpos, u32 bit_num, u32 value);

int dmc_mrr(DMC_CMD_CS_INDEX cs, int mr_addr, u8* result, int tout);

void dmc_mrw(DMC_CMD_CS_INDEX cs, int mr_addr, unsigned char val);

int mr_set_rlwl(int rl, int wl);

int mr_set_drv(int drv);

void dmc_print_str(const char *string);

char *itoa_simple(int num, char *str, int radix);
#endif

#endif
