#include "sci_types.h"
#include "ddrc_r1p1.h"
#include "ddrc_r1p1_phy.h"
#include "ddrc_r1p1_common.h"

extern TRAIN_CONDITIONS_TABLE phy_train;

uint32 __raw_readl(uint32 addr)
{
	volatile uint32 val;
	val = REG32(addr);
	return val;
}

void __raw_writel(uint32 addr, uint32 val)
{
	REG32(addr) = val;
}

uint32 u32_bits_set(uint32 orgval,uint32 start_bitpos, uint32 bit_num, uint32 value)
{
	uint32 bit_mask = (1 << bit_num) - 1;
	uint32 reg_data = orgval;

	reg_data &= ~(bit_mask << start_bitpos);
	reg_data |= ((value & bit_mask) << start_bitpos);
	return reg_data;
}

void reg_bits_set(uint32 addr, uint32 start_bitpos, uint32 bit_num, uint32 value)
{
	uint32 bit_mask = (1 << bit_num) - 1;
	uint32 reg_data = __raw_readl(addr);

	reg_data &= ~(bit_mask << start_bitpos);
	reg_data |= ((value & bit_mask) << start_bitpos);
	__raw_writel(addr, reg_data);
}

uint32 reg_bits_get(uint32 addr, uint32 start_bit, uint32 bits_num)
{
	uint32 reg_data = __raw_readl(addr);
	uint32 bit_mask = ((1<< bits_num) -1);

	reg_data &= (bit_mask << start_bit);
	reg_data = reg_data >> start_bit;
	return reg_data;
}

void dmc_sprd_delay(uint32 x)
{
	volatile uint32 i;
	volatile unsigned int val;
	x *= 2;
	for(i=0; i<x; i++)
	{
		val = *(volatile unsigned int *)(PMU_APB_BASE_ADDR);  // readonly reg.
	}
}

static void isync(void)
{
	dmc_sprd_delay(5);
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

void dmc_dosoft_cmd_setting(uint32 cmd)
{
	DDRC_R1P1_REG_INFO_PTR pdmc = (DDRC_R1P1_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;

	pdmc->dmc_dcfg1= cmd;
	while(((pdmc->dmc_dcfg1 >> 19) & 0x1ff) != 0);//bit[27:19]
}

uint32 dmc_mrr(DMC_CMD_CS_INDEX cs, uint32 mr_addr, uint32* result, uint32 tout)
{
	DDRC_R1P1_REG_INFO_PTR pdmc = (DDRC_R1P1_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	uint32 mrr_valid[4];
	uint32 val;
	uint32 mrr_tout = tout;
	uint32 temp = 0;
	uint32 rpull_state = 0;
	uint32 ret = FALSE;

	ddrc_force_rd_fifo_reset();
	#ifdef PXP_DEBUG
	mrr_tout = 1;
	#endif
	if ((CMD_CS_0 != cs) && (CMD_CS_1 != cs))
	{
		return FALSE;
	}
#if 0
	rpull_state = ddrc_phy_rpull_get(DMC_GUCPHY0_BASE, phy_train.freq_sel);
	if(0 == rpull_state)
	{
		ddrc_phy_rpull_set(DMC_GUCPHY0_BASE, phy_train.freq_sel, 1);
		ddrc_phy_rpull_set(DMC_GUCPHY1_BASE, phy_train.freq_sel, 1);
	}
#endif
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
			ret = TRUE;
		}
	}

#if 0
	if(0 == rpull_state)
	{
		ddrc_phy_rpull_set(DMC_GUCPHY0_BASE, phy_train.freq_sel, 0);
		ddrc_phy_rpull_set(DMC_GUCPHY1_BASE, phy_train.freq_sel, 0);
	}
#endif
	return ret;

}
#ifdef DDR_SCAN_ENABLE
#define UART0_TX_BUF_ADDR 0X24100000
#else
#define UART0_TX_BUF_ADDR 0X70000000
#endif
#define UART_TX_BUF_ADDR UART0_TX_BUF_ADDR
#define UART_TX_BUF_CNT ((REG32(UART_TX_BUF_ADDR + 0xc)>>8)&0xff)


void ddrc_print_str(const char *string)
{
	char *s1 = NULL;

	s1 = (char *)string;

	while (*s1 != '\0')
	{
		//wait until uart1 tx fifo empty
		while(UART_TX_BUF_CNT != 0);

		//put out char by uart1 tx fifo
		REG32(UART_TX_BUF_ADDR) = *s1;
		s1++;
	}
}

char *itoa_simple(int num, char *str, int radix)
{
	/* \u7d22\u5f15\u8868 */
//	  char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
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
#define TOLOWER(x) ((x) | 0x20)
#define isxdigit(c)    (('0' <= (c) && (c) <= '9') \
             || ('a' <= (c) && (c) <= 'f') \
             || ('A' <= (c) && (c) <= 'F'))

#define isdigit(c)    ('0' <= (c) && (c) <= '9')

unsigned long strtoul(const char *cp,char **endp,unsigned int base)
{
    unsigned long result = 0,value;

    if (!base) {
        base = 10;
        if (*cp == '0') {
            base = 8;
            cp++;
            if ((TOLOWER(*cp) == 'x') && isxdigit(cp[1])) {
                cp++;
                base = 16;
            }
        }
    } else if (base == 16) {
        if (cp[0] == '0' && TOLOWER(cp[1]) == 'x')
            cp += 2;
    }
    while (isxdigit(*cp) &&
           (value = isdigit(*cp) ? *cp-'0' : TOLOWER(*cp)-'a'+10) < base) {
        result = result*base + value;
        cp++;
    }
    if (endp)
        *endp = (char *)cp;
    return result;
}
long strtol(const char *cp,char **endp,unsigned int base)
{
    if(*cp=='-')
        return -strtoul(cp+1,endp,base);
    return strtoul(cp,endp,base);
}
int  atoi(const char *nptr)//
{
    return  strtol(nptr, (char  **)NULL, 10);
}
char itoc_tmp[20] = {0};
char *itoa_dec(int num)
{
	itoa_simple(num, itoc_tmp, 10);
}

void ddrc_print_debug(const char *string)
{
	#ifdef DDR_LOG_LVL_DEBUG
	ddrc_print_str(string);
	#endif
}
void ddrc_print_info(const char *string)
{
	#ifdef DDR_LOG_LVL_INFO
	ddrc_print_str(string);
	#endif
}
void ddrc_print_err(const char *string)
{
	#ifdef DDR_LOG_LVL_ERR
	ddrc_print_str("ERROR: ");
	ddrc_print_str(string);
	#endif
}
void ddrc_print_scan(const char *string)
{
	#ifdef DDR_LOG_LVL_SCAN
	ddrc_print_str(string);
	#endif
}

#if 0
/***ddrc_print_debug_location example***/
	ddrc_print_debug("Current file:");
	ddrc_print_debug(__FILE__);
	ddrc_print_debug(" Current function:");
	ddrc_print_debug(__FUNCTION__);
	ddrc_print_debug(" Current line num:");
	ddrc_print_debug(itoa_dec(__LINE__));
	ddrc_print_debug(" \r\n");
#endif

void dmc_exit_self_refresh(uint32 repeat)
{
	DDRC_R1P1_REG_INFO_PTR pdmc = (DDRC_R1P1_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	uint32 regval, i;
	/*step 6) exit selfrefresh and initial DRAM if not send current frequency MRWs*/
	/*ch0_rfdmem_cmd_chip_sleep*/
	regval = (pdmc->dmc_dcfg9 >> 24) & 0x3;
	if (regval == 0x3)
	{
		pdmc->dmc_dcfg1 = 0x80800000;//dsoft_resume
		while(((pdmc->dmc_dcfg1 >> 19) & 0x1ff) != 0);
	}

	pdmc->dmc_dcfg1 = 0x80100000;//dsoft_pre-all
	while(((pdmc->dmc_dcfg1 >> 19) & 0x1ff) != 0);

	for (i = 0; i < repeat; i++)
	{
		pdmc->dmc_dcfg1 = 0x80200000;//dsoft_auto_ref
		while(((pdmc->dmc_dcfg1 >> 19) & 0x1ff) != 0);
	}
}

void dmc_entry_self_refresh(uint32 repeat)
{
	DDRC_R1P1_REG_INFO_PTR pdmc = (DDRC_R1P1_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	uint32 regval, i;
	/*step 6) exit selfrefresh and initial DRAM if not send current frequency MRWs*/
	/*ch0_rfdmem_cmd_chip_sleep*/
	pdmc->dmc_dcfg1 = 0x80400000;//dsoft_resume
	while(((pdmc->dmc_dcfg1 >> 19) & 0x1ff) != 0);
}

void phy_vref_manual_dbn(uint32 phy_base, uint32 freq_sel, uint32 dbn, uint32 value)
{
	uint32 tmp_addr = phy_base + (freq_sel*20*4);
	reg_bits_set((phy_base + 0x10*4), (dbn?8:0), 8, value);
}

void phy_vref_manual(uint32 freq_sel, uint32 value)
{
	phy_vref_manual_dbn(DMC_GUCPHY0_BASE, freq_sel, 0, value);
	phy_vref_manual_dbn(DMC_GUCPHY0_BASE, freq_sel, 1, value);
	phy_vref_manual_dbn(DMC_GUCPHY1_BASE, freq_sel, 0, value);
	phy_vref_manual_dbn(DMC_GUCPHY1_BASE, freq_sel, 1, value);
}

/*phy_data_drvn(DMC_GUCPHY0_BASE, freq_sel, PHY_DS_40);*/
/*phy_data_drvp(DMC_GUCPHY0_BASE, freq_sel, PHY_DS_40);*/
/*phy_ca_drvn(DMC_GUCPHY0_BASE, freq_sel, PHY_DS_40);*/
/*phy_ca_drvp(DMC_GUCPHY0_BASE, freq_sel, PHY_DS_40);*/
void phy_data_drvn(uint32 phy_base, uint32 freq_sel, uint32 value)
{
	uint32 tmp_addr = phy_base + (freq_sel*20*4);
	reg_bits_set((phy_base + 0x9*4), 8, 3, value);
}

void phy_data_drvp(uint32 phy_base, uint32 freq_sel, uint32 value)
{
	uint32 tmp_addr = phy_base + (freq_sel*20*4);
	reg_bits_set((phy_base + 0x9*4),12, 3, value);
}

void phy_ca_drvn(uint32 phy_base, uint32 freq_sel, uint32 value)
{
	uint32 tmp_addr = phy_base + (freq_sel*20*4);
	reg_bits_set((phy_base + 0x9*4), 16, 3, value);
}

void phy_ca_drvp(uint32 phy_base, uint32 freq_sel, uint32 value)
{
	uint32 tmp_addr = phy_base + (freq_sel*20*4);
	reg_bits_set((phy_base + 0x9*4), 20, 3, value);
}

