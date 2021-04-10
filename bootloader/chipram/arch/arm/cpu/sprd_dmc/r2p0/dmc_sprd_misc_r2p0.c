#include <sci_types.h>
#include "dmc_sprd_r2p0.h"

extern DRAM_CHIP_INFO ddr_chip_cur;

u32 u32_bits_set(u32 orgval,u32 start_bitpos, u32 bit_num, u32 value)
{
	u32 bit_mask = (1<<bit_num) - 1;
	u32 reg_data = orgval;

	reg_data &= ~(bit_mask<<start_bitpos);
	reg_data |= ((value&bit_mask)<<start_bitpos);
	return reg_data;
}

void dmc_sprd_delay(int x)
{
	volatile int i;
	volatile unsigned int val;
	for(i=0;i<x;i++)
	{
		val=*(volatile unsigned int *)0x402b00c4;  // readonly reg.
	}
}

int dmc_mrr(DMC_CMD_CS_INDEX cs, int mr_addr, u8* result, int tout)
{
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 val;
	int mrr_tout = tout;
	u8 temp=0;

	if ((CMD_CS_0 != cs) && (CMD_CS_1 != cs))
	{
		return -1;
	}

	/*set byte switch*/
	val = pdmc->dmc_dcfg4;
	val = u32_bits_set(val, 24, 2, MRR_BYTE_SWITCH_INDEX);
	pdmc->dmc_dcfg4 = val;

	/*set mr register addr*/
	val= pdmc->dmc_dcfg1;
	val = u32_bits_set(val, 0, 16, mr_addr);
	/*1 cs mode*/
	val = u32_bits_set(val, 31, 1, 0);
	/*set cs index*/
	if (CMD_CS_0 == cs)
	{
		val = u32_bits_set(val, 28, 1, 0);
	}
	else if (CMD_CS_1 == cs)
	{
		val = u32_bits_set(val, 28, 1, 1);
	}
	/*start mrr command*/
	val = u32_bits_set(val, 25, 1, 1);
	pdmc->dmc_dcfg1 = val;

	/* wait until [26:20]==0 */
	while(((pdmc->dmc_dcfg1 >> 20) & 0x7f) != 0);

	while(mrr_tout-->0)
	{
		val = pdmc->dmc_dcfg2;
		if (val & (1<<16))
		{
			temp = (val>>8)&0xff;
#ifdef EVB_PIKE
			*result = (temp&0x24)|((temp&0x01)<<3)|((temp&0x02)<<6)|((temp&0x08)<<3)|((temp&0x10)>>3)|((temp&0x40)>>2)|((temp&0x80)>>7);
#else
			if(ddr_chip_cur.chip_type == DRAM_LPDDR2)
			{
				*result = ((temp&0x6f) | ((temp&0x10)<<3)|((temp&0x80)>>3));
			}
			else
			{
				* result = temp;
			}
#endif
			reset_dmc_fifo();
			return 0;
		}
	}
	reset_dmc_fifo();
	return -1;
}

void dmc_mrw(DMC_CMD_CS_INDEX cs, int mr_addr, unsigned char val)
{
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 tmp;
	u8 mr_val;

#ifdef EVB_PIKE
	mr_val = (val&0x24)|((val&0x01)<<3)|((val&0x02)<<6)|((val&0x08)<<3)|((val&0x10)>>3)|((val&0x40)>>4)|((val&0x80)>>7);
#else
	if(ddr_chip_cur.chip_type == DRAM_LPDDR2)
	{
		mr_val = (val&0x6f) | ((val&0x10)<<3) | ((val&0x80)>>3);
	}
	else
	{
		mr_val = val;
	}
#endif

	/*set reg val*/
	tmp = pdmc->dmc_dcfg2;
	tmp = u32_bits_set(tmp, 0, 8, mr_val);
	pdmc->dmc_dcfg2 = tmp;

	/*set mr register addr*/
	tmp = pdmc->dmc_dcfg1;
	tmp = u32_bits_set(tmp, 0, 16, mr_addr);
	/*set cs index*/
	if (CMD_CS_0 == cs)
	{
		/*1 cs mode*/
		tmp = u32_bits_set(tmp, 31, 1, 0);
		/*cs index*/
		tmp = u32_bits_set(tmp, 28, 1, 0);
	}
	else if (CMD_CS_1 == cs)
	{
		/*1 cs mode*/
		tmp = u32_bits_set(tmp, 31, 1, 0);
		/*cs index*/
		tmp = u32_bits_set(tmp, 28, 1, 1);
	}
	/*2 cs mode*/
	else
	{
		tmp = u32_bits_set(tmp, 31, 1, 1);
	}
	/*triger MRW*/
	tmp = u32_bits_set(tmp, 24, 1, 1);
	pdmc->dmc_dcfg1 = tmp;

	/* wait until [26:20]==0 */
	while(((pdmc->dmc_dcfg1 >> 20) & 0x7f) != 0);
}

int mr_set_rlwl(int rl, int wl)
{
	if ((rl == 3) && (wl == 1))
	{
		dmc_mrw(CMD_CS_BOTH, 0x2, 1);
	}
	else if ((rl == 4) && (wl == 2))
	{
		dmc_mrw(CMD_CS_BOTH, 0x2, 2);
	}
	else if ((rl == 5) && (wl == 2))
	{
		dmc_mrw(CMD_CS_BOTH, 0x2, 3);
	}
	else if ((rl == 6) && (wl == 3))
	{
		dmc_mrw(CMD_CS_BOTH, 0x2, 4);
	}
	else if ((rl == 7) && (wl == 4))
	{
		dmc_mrw(CMD_CS_BOTH, 0x2, 5);
	}
	else if ((rl == 8) && (wl == 4))
	{
		dmc_mrw(CMD_CS_BOTH, 0x2, 6);
	}
	else if ((rl == 9) && (wl == 5))
	{
		dmc_mrw(CMD_CS_BOTH, 0x2, 7);
	}
	else if ((rl == 10) && (wl == 6))
	{
		dmc_mrw(CMD_CS_BOTH, 0x2, 8);
	}
	else if ((rl == 11) && (wl == 6))
	{
		dmc_mrw(CMD_CS_BOTH, 0x2, 9);
	}
	else if ((rl == 12) && (wl == 6))
	{
		dmc_mrw(CMD_CS_BOTH, 0x2, 0xa);
	}
	else if ((rl == 14) && (wl == 8))
	{
		dmc_mrw(CMD_CS_BOTH, 0x2, 0xc);
	}
	else if ((rl == 16) && (wl == 8))
	{
		dmc_mrw(CMD_CS_BOTH, 0x2, 0xe);
	}
	else
	{
		return -1;
	}
	return 0;
}

int mr_set_drv(int drv)
{
	unsigned char val;

	switch(drv)
	{
		case 34:
			val = 1;
			break;
		case 40:
			val = 2;
			break;
		case 48:
			val = 3;
			break;
		case 60:
			val = 4;
			break;
		case 80:
			val = 6;
			break;
		case 120:
			val = 7;
			break;
		default:
			return -1;
	}
	dmc_mrw(CMD_CS_BOTH, 3, val);
	return 0;
}

#define UART1_TX_BUF_ADDR 0x70100000
#define UART1_TX_BUF_CNT ((REG32(0x70100000 + 0xc)>>8)&0xff)

#ifndef NULL
#define NULL ((void *)0)
#endif


void dmc_print_str(const char *string)
{
    char *s1 = NULL;

    s1 = (char *)string;

    while (*s1 != NULL)
    {
		//wait until uart1 tx fifo empty
		while(UART1_TX_BUF_CNT != 0);

		//put out char by uart1 tx fifo
		REG32(UART1_TX_BUF_ADDR) = *s1;
		s1++;
	}
}

char *itoa_simple(int num, char *str, int radix)
{
    /* \u7d22\u5f15\u8868 */
    char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned unum; /* \u4e2d\u95f4\u53d8\u91cf */
    int i=0,j,k;
	char temp;
    /* \u786e\u5b9aunum\u7684\u503c */
    if(radix==10&&num<0) /* \u5341\u8fdb\u5236\u8d1f\u6570 */
    {
        unum=(unsigned)-num;
        str[i++]='-';
    }
    else unum=(unsigned)num; /* \u5176\u4ed6\u60c5\u51b5 */
    /* \u9006\u5e8f */
    do
    {
        str[i++]=index[unum%(unsigned)radix];
        unum/=radix;
    }while(unum);
    str[i]='\0';
    /* \u8f6c\u6362 */
    if(str[0]=='-') k=1; /* \u5341\u8fdb\u5236\u8d1f\u6570 */
    else k=0;

    for(j=k;j<=(i-k-1)/2;j++)
    {
        temp=str[j];
        str[j]=str[i-j-1];
        str[i-j-1]=temp;
    }
    return str;
}

/**
 * memcpy - Copy one area of memory to another
 * @dest: Where to copy to
 * @src: Where to copy from
 * @count: The size of the area.
 *
 * You should not use this function to access IO space, use memcpy_toio()
 * or memcpy_fromio() instead.
 */
void * memcpy(void *dest, const void *src, size_t count)
{
	u32 *dl = (unsigned long *)dest, *sl = (u32*)src;
	char *d8, *s8;

	/* while all data is aligned (common case), copy a word at a time */
	if ( (((u32)dest | (u32)src) & (sizeof(*dl) - 1)) == 0) {
		while (count >= sizeof(*dl)) {
			*dl++ = *sl++;
			count -= sizeof(*dl);
		}
	}
	/* copy the reset one byte at a time */
	d8 = (char *)dl;
	s8 = (char *)sl;
	while (count--)
		*d8++ = *s8++;

	return dest;
}
