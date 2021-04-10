#include "sci_types.h"
#include "ddrc_r1p0.h"
#include "ddrc_r1p0_common.h"
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

u32 u32_bits_set(u32 orgval,u32 start_bitpos, u32 bit_num, u32 value)
{
	u32 bit_mask = (1 << bit_num) - 1;
	u32 reg_data = orgval;

	reg_data &= ~(bit_mask << start_bitpos);
	reg_data |= ((value & bit_mask) << start_bitpos);
	return reg_data;
}

void reg_bits_set(u32 addr, u32 start_bitpos, u32 bit_num, u32 value)
{
	u32 bit_mask = (1 << bit_num) - 1;
	u32 reg_data = __raw_readl(addr);

	reg_data &= ~(bit_mask << start_bitpos);
	reg_data |= ((value & bit_mask) << start_bitpos);
	__raw_writel(addr, reg_data);
}

uint32 reg_bits_get(u32 addr, u32 start_bit, u32 bits_num)
{
	u32 reg_data = __raw_readl(addr);
	u32 bit_mask = ((1<< bits_num) -1);

	reg_data &= (bit_mask << start_bit);
	reg_data = reg_data >> start_bit;
	return reg_data;
}

void dmc_sprd_delay(int x)
{
	volatile int i;
	volatile unsigned int val;
        x *= 2;
	for(i=0; i<x; i++)
	{
		val = *(volatile unsigned int *)0x402b00c4;  // readonly reg.
	}
	return val;
}
void dmc_dosoft_cmd_setting(uint32 cmd)
{
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;

	pdmc->dmc_dcfg1= cmd;
	while(((pdmc->dmc_dcfg1 >> 19) & 0x1ff) != 0);//bit[27:19]
}

void inline ddrc_force_rd_fifo_reset(void)
{
	//bit[23]
	//0:normal operating
	//1:sw force rd fifo prt reset
	REG32(DMC_GUCPHY0_BASE + 0x284) |= (1<<23);
	REG32(DMC_GUCPHY1_BASE + 0x284) |= (1<<23);
	REG32(DMC_GUCPHY0_BASE + 0x284) &= ~(1<<23);
	REG32(DMC_GUCPHY1_BASE + 0x284) &= ~(1<<23);
}

int dmc_mrr(DMC_CMD_CS_INDEX cs, int mr_addr, u32* result, int tout)
{
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 mrr_valid[4];
	u32 val;
	int mrr_tout = tout;
	u32 temp=0;

	if ((CMD_CS_0 != cs) && (CMD_CS_1 != cs))
	{
		return -1;
	}

	/*set mr register addr*/
	val= pdmc->dmc_dcfg1;
	val = u32_bits_set(val, 0, 16, mr_addr);
	/*1 cs mode*/
	val &= ~(1<<31);
	/*set cs index*/
	if (CMD_CS_0 == cs)
	{
		val &=~(1<<28);
	}
	else if (CMD_CS_1 == cs)
	{
		val |= (1<<28);
	}
	/*start mrr command*/
	val |= (1 << 25);
	pdmc->dmc_dcfg1 = val;

	/* wait until [27:19]==0 */
	while(((pdmc->dmc_dcfg1 >> 19) & 0x1ff) != 0);

	while(mrr_tout-- > 0)
	{
		mrr_valid[0] = (pdmc->dmc_sts0 >> 12 )& 1;
		mrr_valid[1] = (pdmc->dmc_sts1 >> 12 )& 1;
		mrr_valid[2] = (pdmc->dmc_sts2 >> 12 )& 1;
		mrr_valid[3] = (pdmc->dmc_sts3 >> 12 )& 1;
		/*0xA0 bit[12] ch0_rfdmem_mrr_valid*/
		if(mrr_valid[0] == 1 ||
		   mrr_valid[1] == 1 ||
		   mrr_valid[2] == 1 ||
		   mrr_valid[3] == 1)
		{
			/*0xD0 [7:0] ch0_rfdmem_mrr_readout value*/
			if (mrr_valid[0] == 1)
				temp = pdmc->dmc_sts4 & 0xff;
			if (mrr_valid[1] == 1)
				temp |= (((pdmc->dmc_sts4 >> 16) & 0xff) << 8);
			if (mrr_valid[2] == 1)
				temp |= ((pdmc->dmc_sts5 & 0xff) << 16);
			if (mrr_valid[3] == 1)
				temp |= (((pdmc->dmc_sts5 >> 16) & 0xff) << 24);
			*result = temp;
			ddrc_force_rd_fifo_reset();
			return 0;
		}
	}
	return -1;

}

#define UART1_TX_BUF_ADDR 0X70100000
//#define UART1_TX_BUF_ADDR 0X70000000
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

char *itoa_simple(int num, char *str, int radix)
{
    /* \u7d22\u5f15\u8868 */
//    char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *index = 0;
    index = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
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

