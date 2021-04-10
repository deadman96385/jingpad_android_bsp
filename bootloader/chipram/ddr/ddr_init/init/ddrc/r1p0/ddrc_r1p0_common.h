#ifndef __DDRC_SPRD_COMMON_H__
#define __DDRC_SPRD_COMMON_H__

#include "ddrc_r1p0.h"
u32 __raw_readl(u32 addr);
void __raw_writel(u32 addr, u32 val);
void dmc_sprd_delay(int x);

u32 u32_bits_set(u32 orgval,u32 start_bitpos, u32 bit_num, u32 value);

void reg_bits_set(u32 addr, u32 start_bitpos, u32 bit_num, u32 value);

uint32 reg_bits_get(u32 addr, u32 start_bit, u32 bits_num);

int dmc_mrr(DMC_CMD_CS_INDEX cs, int mr_addr, u32* result, int tout);

void dmc_mrw(DMC_CMD_CS_INDEX cs, int mr_addr, unsigned char val);

int lpddr3_mr_set_rlwl(int rl, int wl);

int mr_set_drv(int drv);

void dmc_print_str(const char *string);

char *itoa_simple(int num, char *str, int radix);


#endif
