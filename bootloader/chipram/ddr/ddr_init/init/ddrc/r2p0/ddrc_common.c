#include "ddrc_common.h"

u32 __raw_readl(u32 addr)
{
	volatile u32 val;
	val = REG32(addr);
	return val;
}

void __raw_writel(u32 addr, u32 val)
{
	REG32(addr) = val;
}

void reg_bit_set(u32 addr, u32 start_bit, u32 bits_num, u32 val)
{
	u32 tmp_val,bit_msk = ((1<<bits_num)-1);
	tmp_val = __raw_readl(addr);
	tmp_val &= ~(bit_msk << start_bit);
	tmp_val |= ((val & bit_msk)<< start_bit);
	__raw_writel(addr, tmp_val);
}

u32 reg_bit_get(u32 addr, u32 start_bit, u32 bits_num)
{
	u32 tmp_val,bit_msk = ((1 << bits_num) - 1);
	tmp_val = __raw_readl(addr);
	tmp_val &= (bit_msk <<start_bit);
	tmp_val = tmp_val >> start_bit;
	return tmp_val;
}

void wait_us(u32 us)
{
	volatile u32 i = 0;
	volatile u32 j = 0;
	volatile u32 reg = 0;
	for(i=0; i<us; i++)
	{
		for(j=0;j<7;j++)
		{
			reg = __raw_readl(DDR_SLP_CTRL_STATUS);
		}
	}

}

void wait_100ns(u32 ns)
{
	volatile u32 i = 0;
	volatile u32 reg = 0;
	for(i=0; i<ns; i++)
	{
	#if 0
		reg = __raw_readl(DDR_SLP_CTRL_STATUS);
	#endif
	}

}


#define UART1_TX_BUF_CNT ((REG32(UART1_TX_BUF_ADDR + 0xc)>>8)&0xff)

void dmc_print_str(const char *string)
{
	char *s1 = NULL;

    s1 = (char *)string;

    while (*s1 != '\0')
    {
        //wait until uart1 tx fifo empty
        while(UART1_TX_BUF_CNT != 0);

        //put out char by uart1 tx fifo
        REG32(UART1_TX_BUF_ADDR) = *s1;
        s1++;
    }
}

static char  log_string[33];
static char *  toStrDec(u32 val){
	int i, j, num;
	u32 temp = val;	num = 0;
	do{
		num++;
		temp /= 10;
	  }while(temp >0);
	for(i = num-1; i >=0; i--){
		temp = (val%10) + 0x30;
		val /= 10;
		log_string[i] = temp&0xff;
	}
	log_string[num] = ' ';
	log_string[num+1] = 0;
	return log_string;
}

static char *  toStrHex(u32 val){
	int i, j, num;
	u32 temp = val;
	log_string[0] = '0';
	log_string[1] = 'x';
	for(i = 0; i < 8; i++){
		temp = (val >> ((7-i)*4)) & 0xf;
		if (temp < 0xa)
			log_string[2+i] = temp+0x30;
		else
			log_string[2+i] = 'A'+temp-0xa;
	}
	log_string[10] = ' ';
	log_string[11] = 0;
	return log_string;
}

int  print_Dec(u32 val){
	if(val <0){
		dmc_print_str("-");
		val = 0 - val;
	}
	dmc_print_str(toStrDec(val));
	return 0;
}

int  print_Hex(u32 val){
	dmc_print_str(toStrHex(val));
	return 0;
}

int print_String(const char *string){
	dmc_print_str(string);
	return 0;
}


