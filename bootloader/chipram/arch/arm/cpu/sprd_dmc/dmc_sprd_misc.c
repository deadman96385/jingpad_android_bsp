#include <sci_types.h>
#include "asm/arch/clk_para_config.h"
#include "dmc_sprd_r1p0.h"
#include "dmc_sprd_misc.h"

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
		val=*(volatile unsigned int *)0x30000218;
	}
}

static void isync(void)
{
	asm volatile ("dsb");
}

void dmc_set_cmd_cs_index(DMC_CMD_CS_INDEX index)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 val = pdmc->dmc_dcfg1;
	switch(index)
	{
		case CMD_CS_0:
			val = u32_bits_set(val, 31, 1, 0);
			val = u32_bits_set(val, 28, 1, 0);
			break;
		case CMD_CS_1:
			val = u32_bits_set(val, 31, 1, 0);
			val = u32_bits_set(val, 28, 1, 1);
			break;
		case CMD_CS_BOTH:
			val = u32_bits_set(val, 31, 1, 1);
			break;
		default:
			break;
	}
	pdmc->dmc_dcfg1 = val;	
}

DMC_CMD_CS_INDEX dmc_get_cmd_cs_index(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 val = pdmc->dmc_dcfg1;

	if (0x80000000&val)
	{
		return CMD_CS_BOTH;
	}
	else if(0 == (val&(1<<28)))
	{
		return CMD_CS_0;
	}
	else
	{
		return CMD_CS_1;
	}
}

int dmc_mrr(DMC_CMD_CS_INDEX cs, int mr_addr, u8* result, int tout)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 val; 
	int mrr_tout = tout;
	
	if ((CMD_CS_0 != cs) && (CMD_CS_1 != cs))
	{
		return -1;
	}

	/*set byte switch*/
	val = pdmc->dmc_dcfg2;
	val = u32_bits_set(val, 20, 2, MRR_BYTE_SWITCH_INDEX);
	pdmc->dmc_dcfg2 = val;
	
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
	dmc_sprd_delay(100);	
	while(mrr_tout-->0)
	{
		val = pdmc->dmc_dcfg2; 
		if (val & (1<<16))
		{
			* result = (val>>8)&0xff;
			reset_dmc_fifo();
			return 0;
		}
	}
	reset_dmc_fifo();
	return -1;	
}

void dmc_mrw(DMC_CMD_CS_INDEX cs, int mr_addr, unsigned char val)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 tmp;

	/*set reg val*/
	tmp = pdmc->dmc_dcfg2;
	tmp = u32_bits_set(tmp, 0, 8, val);
	pdmc->dmc_dcfg2 = tmp;
	isync();
	tmp = pdmc->dmc_dcfg1;
	/*set mr register addr*/
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
	isync();
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

#define UART1_TX_BUF_ADDR 0X70100000
#define UART1_TX_BUF_CNT ((REG32(0x70100000 + 0xc)>>8)&0xff)

#ifndef NULL
#define NULL ((void *)0)
#endif


void dmc_print_str(const char *string)
{
    char *s1 = NULL;

    s1 = string;

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
	unsigned long *dl = (unsigned long *)dest, *sl = (unsigned long *)src;
	char *d8, *s8;

	/* while all data is aligned (common case), copy a word at a time */
	if ( (((ulong)dest | (ulong)src) & (sizeof(*dl) - 1)) == 0) {
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




