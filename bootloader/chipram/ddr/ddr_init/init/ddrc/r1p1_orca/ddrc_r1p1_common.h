#ifndef __DDRC_SPRD_COMMON_H__
#define __DDRC_SPRD_COMMON_H__
#ifdef TRUE
#undef TRUE
#endif
#ifdef FALSE
#undef FALSE
#endif
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

uint32 __raw_readl(uint32 addr);
void __raw_writel(uint32 addr, uint32 val);
void dmc_sprd_delay(uint32 x);

uint32 u32_bits_set(uint32 orgval,uint32 start_bitpos, uint32 bit_num, uint32 value);

void reg_bits_set(uint32 addr, uint32 start_bitpos, uint32 bit_num, uint32 value);

uint32 reg_bits_get(uint32 addr, uint32 start_bit, uint32 bits_num);

uint32 dmc_mrr(DMC_CMD_CS_INDEX cs, uint32 mr_addr, uint32* result, uint32 tout);

void dmc_mrw(DMC_CMD_CS_INDEX cs, uint32 mr_addr, unsigned char val);

void mr_set_drv(int drv);

void ddrc_print_debug(const char *string);

void ddrc_print_info(const char *string);

void ddrc_print_err(const char *string);

void ddrc_print_scan(const char *string);

char *itoa_simple(int num, char *str, int radix);


#endif
