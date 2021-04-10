#include <ddr_common.h>


#ifdef DDR_SCAN_SUPPORT
uint32 user_mode_pattern[] = {0xFFFFFFFF,
				0x00000000,
				0xFFFFFFFF,
				0x00000000,
				0x00000000,
				0xFFFFFFFF,
				0x00000000,
				0xFFFFFFFF,
				0x00000000,
				0x00000000,
				0xFFFFFFFF,
				0xFFFFFFFF,
				0xFFFFFFFF,
				0xFFFFFFFF,
				0x00000000,
				0x00000000,
				0xFFFFFFFF,
				0xFFFFFFFF,
				0xFFFFFFFF,
				0xFFFFFFFF,
				0x00000000,
				0x00000000,
				0x00000000,
				0x00000000,
				0x00000000,
				0x00000000,
				0x00000000,
				0x00000000,
				0xFFFFFFFF,
				0xFFFFFFFF,
				0xFFFFFFFF,
				0xFFFFFFFF};

uint32 sipi_mode_pattern[] = {0x38ccccaa,
                              0xe1e1e38e,
                              0x111249e1,
                              0xdb084211,
                              0xdef77776,
                              0x0000007b,
                              0x01234567,
                              0x89abcdef};

uint32 lfsr_mode_pattern[] = {0x12345678,
	                      0x89abcdef,
	                      0x8abce529,
	                      0xfbed20ec};

#endif

uint32 __raw_readl(uint32 addr)
{
     volatile uint32 val;
	 
     //asm volatile("ldr %w0, [%1]" : "=r" (val) : "r" (addr));
     val = REG32(addr);	 
     return val;
}
 
void __raw_writel(uint32 addr,uint32 val)
{
     //asm volatile("str %w0, [%1]" : : "r" (val), "r" (addr));
     REG32(addr) = val;
}

void reg_bit_set(uint32 addr,uint32 start_bit,uint32 bits_num,uint32 val)
{
	uint32 tmp_val,bit_msk = ((1 << bits_num) - 1);
	tmp_val = __raw_readl(addr);
	tmp_val &= ~(bit_msk << start_bit);
	tmp_val |= ( (val & bit_msk) << start_bit );
	__raw_writel(addr,tmp_val);
}
uint32 reg_bit_get(uint32 addr,uint32 start_bit,uint32 bits_num)
{
	uint32 tmp_val,bit_msk = ((1 << bits_num) - 1);
	tmp_val = __raw_readl(addr);
	tmp_val &= (bit_msk << start_bit);
	tmp_val = tmp_val >> start_bit;
        return tmp_val;
}
void wait_us(uint32 us)
{
	volatile uint32 i = 0;
	volatile uint32 j = 0;
	volatile uint32 reg = 0;

	for(i = 0; i < us; i++)
	{
		for(j = 0; j < 153; j++)
		{
			reg = __raw_readl(DDR_DUMMY_REG);
			reg = reg;
		}
	}
}

void wait_10us(uint32 us_10)
{
	volatile uint32 i = 0;

	for(i = 0; i < us_10; i++)
	{
	    wait_us(10);
	}
}

void __ddr_print(char * log)
{
#if defined (CONFIG_SOC_IWHALE2) || defined(CONFIG_SOC_ISHARKL2)
#ifdef CONFIG_NAND_SPL
	char *s1 = NULL;
	s1 = log;
	while((*s1) != NULL)
	{
		while(UART0_TX_BUF_CNT != 0);
		REG32(UART0_TX_BUF_ADDR) = *s1;
		s1++;
	}
#endif
#else
	char *s1 = NULL;
	s1 = log;
	while((*s1) != NULL)
	{
		while(UART0_TX_BUF_CNT != 0);
		REG32(UART0_TX_BUF_ADDR) = *s1;
		s1++;
	}
#endif
}

void ddr_output_char(char ch)
{
#if defined (CONFIG_SOC_IWHALE2) || defined(CONFIG_SOC_ISHARKL2)
#ifdef CONFIG_NAND_SPL
	//wait until uart1 tx fifo empty
	while(UART0_TX_BUF_CNT != 0);
	//put out char by uart1 tx fifo
	REG32(UART0_TX_BUF_ADDR) = ch;
	return;
#endif
#else
	//wait until uart1 tx fifo empty
	while(UART0_TX_BUF_CNT != 0);
	//put out char by uart1 tx fifo
	REG32(UART0_TX_BUF_ADDR) = ch;
	return;
#endif
}

static char ascii[]="0123456789abcdef";
void ddr_print_u32_hex(uint32 data)
{
	uint32 index,i;

	ddr_output_char('0');
	ddr_output_char('x');
	for(i=4;i<=32;i=i+4)
	{
		index= (data>>(32-i))&0xf;
		ddr_output_char(ascii[index]);
	}
	ddr_output_char(' ');
	return;
}

#if defined (CONFIG_SOC_IWHALE2) || defined(CONFIG_SOC_ISHARKL2)
void __ddr_wdg_reset(void)
{
	uint32 cnt=3*WDG_CLK;
	/*enable interface clk*/
	ANA_REG_OR(ANA_AGEN, AGEN_WDG_EN);

	/*enable interface clk*/
	ANA_REG_OR(ANA_RTC_CLK_EN,AGEN_RTC_WDG_EN);
	ANA_REG_SET(WDG_LOCK, WDG_UNLOCK_KEY);
	ANA_REG_OR(WDG_CTRL, WDG_NEW_VER_EN);

	/*load time value*/
	ANA_REG_SET(WDG_LOAD_HIGH, (uint16_t) (((cnt) >> 16) & 0xffff));
	ANA_REG_SET(WDG_LOAD_LOW, (uint16_t) ((cnt) & 0xffff));

	ANA_REG_OR(WDG_CTRL, (WDG_CNT_EN_BIT | WDG_RST_EN_BIT));
	ANA_REG_SET(WDG_LOCK, (uint16_t) (~WDG_UNLOCK_KEY));
	//reg_bit_set(0xe42b012c, 3, 1, 1);
	while(1);
}
#else
void __ddr_wdg_reset(void)
{ 
	uint32 i = 0;

	uint32 reg_val_pd;
	volatile uint32 reg_val = 0;

	ANA_REG_MSK_OR(ANA_REG_GLB_PWR_WR_PROT_VALUE, BITS_PWR_WR_PROT_VALUE(0x6e7f),0x7FFF);

	reg_val_pd = ANA_REG_GET(ANA_REG_GLB_POWER_PD_SW);
	reg_val_pd |= (1 << 7);
	ANA_REG_SET(ANA_REG_GLB_POWER_PD_SW,reg_val_pd);

	wait_us(2000);

	reg_val_pd =  ANA_REG_GET(ANA_REG_GLB_POWER_PD_SW);
	reg_val_pd &= (~(1 << 7));
	ANA_REG_SET(ANA_REG_GLB_POWER_PD_SW,reg_val_pd);

	ANA_REG_MSK_OR(ANA_REG_GLB_PWR_WR_PROT_VALUE, 0, 0x7FFF);


	ANA_REG_OR (ANA_REG_GLB_ARM_MODULE_EN, BIT_ANA_WDG_EN); //WDG enable

	ANA_REG_OR (ANA_REG_GLB_RTC_CLK_EN,    BIT_RTC_WDG_EN); //WDG Rtc enable

	/*unlock arch enable*/
	ANA_REG_SET(ANA_REG_GLB_MCU_WR_PROT_VALUE,0x3c4d);

	/*first enable ana watch module*/
	reg_val = ANA_REG_GET(ANA_REG_GLB_ARM_MODULE_EN);
	reg_val |= (1 << 2);
	ANA_REG_SET(ANA_REG_GLB_ARM_MODULE_EN,reg_val);

	reg_val = ANA_REG_GET(ANA_REG_GLB_RTC_CLK_EN);
	reg_val |= (1 << 2); /* enable the  PCLK of watchdog */
	ANA_REG_SET(ANA_REG_GLB_RTC_CLK_EN,reg_val);

	/*second unlock watch module*/
	ANA_REG_SET(WDG_LOCK,WDG_UNLOCK_KEY);

	/*third load watch count*/
	ANA_REG_SET(WDG_LOAD_HIGH,0x0);
	ANA_REG_SET(WDG_LOAD_LOW,0x10);

	/*forth watchdog run and reset enable*/
	ANA_REG_SET(WDG_CTRL,0xe);

	/*lock watchdog for safe*/
	ANA_REG_SET(WDG_LOCK,0x0000);

	while(1);

	return;
}
#endif



#ifdef DDR_SCAN_SUPPORT
void bist_en(uint32 chn_num)
{
	if(chn_num==0)
	{
	//enable pub0 CA53 port bist module
	REG32(0X30018028)	= 0x2A;
	}
	else
	{
	//enable pub0 CA53 port bist module
	REG32(0X30818028)	= 0x2A;
	}
}

void bist_dis(uint32 chn_num)
{
	if(chn_num == 0)
	{
	//enable pub0 CA53 port bist module
	REG32(0X30018028)	= 0;
	}
	else
	{
	//enable pub0 CA53 port bist module
	REG32(0X30818028)	= 0;
	}
}

void bist_clear(uint32 chn_num,uint32 bist_num)
{
	volatile uint32 i = 0;
	volatile uint32 offset = bist_num * 0x4000 + chn_num*0x00800000;
	
	//set bist clear/set bist start
	i  = REG32(0X300D0000+ offset);
	i |= 0x4;
	i &= (~0x2);
	REG32(0X300D0000+ offset) = i;	
}

void bist_trigger(uint32 chn_num,uint32 bist_num)
{
	volatile uint32 i = 0;
	volatile uint32 offset = bist_num * 0x4000 + chn_num*0x00800000;
	
	//trigger bist
	i  = REG32(0X300D0000+ offset);
	i |= 0x2;
	REG32(0X300D0000+ offset) = i;	
}

void bist_wait_done(uint32 chn_num,uint32 bist_num)
{
	volatile uint32 offset = bist_num * 0x4000 + chn_num*0x00800000;

	//wait bist done
	while((REG32(0x300D00B0+ offset)&0X2) != 0X2);
}

uint32 get_bist_result(uint32 chn_num,uint32 bist_num)
{
	volatile uint32 i = 0;
	volatile uint32 offset = bist_num * 0x4000 + chn_num*0x00800000;

	//wait bist done
	while((REG32(0x300D00B0+ offset)&0X2) != 0X2);
	
	if( ((REG32(0x300D00B0+ offset)&0X1) == 0) || 
		 (REG32(0X300D00B4+ offset) == REG32(0X300D0008+offset)+ (((REG32(0X300D0008+offset)+1)<<5)-16) )
	  ) 
	{
		//SCI_TraceLow("\r\nddr bist %d pass :)",bist_num);
		//REG32(0X80000000+bist_num*4) = 0x88888888;
		return 0;
	}
	else
	{
		//SCI_TraceLow("\r\nddr bist $d fail !!!",bist_num);
		//REG32(0X80000000+bist_num*4) = 0xffffffff;
		return 1;
	}
}

void bist_set(uint32 chn_num,uint32 bist_num,uint32 write_or_read,
	         uint32 bist_patt, uint32 bist_src,uint32 bist_len)
{
	volatile uint32 i = 0;
	volatile uint32 offset = bist_num * 0x4000 + chn_num*0x00800000;

	REG32(0X300D0000+ offset) = 4;
	for(i = 0; i < 3000; i++);
	REG32(0X300D0000+ offset) = 0;	
	
	//bist enable
	i = 0;
  	i |=1;
	//set bist mode
  	i |= (write_or_read<<3); //0:write  1:read  2:all write, then read compare  3:one write, then read compare
  	//set bist pattern mode
	i |= (bist_patt<<5); //0:user mode  1:sipi mode  2:lfsr
  	//set burst length
  	i |= (15<<7); //1:(n+1)*2  3:(n+1)*4  7:(n+1)*8  15:(n+1)*16  others:n+1
  	//set data size
  	i |= (0<<11); //0:dword  1:byte  2:halfword  3:word
  	
  	REG32(0X300D0000 + offset) = i;

  	//set trans num
  	REG32(0X300D0004+ offset) = (bist_len>>8) -1;

  	//set start address
  	REG32(0X300D0008+ offset) = bist_src;
	if(bist_patt==USER_MODE)
	{
		//set bist data pattern
		for(i = 0; i < 32; i++)
		{
			REG32(0X300D0030 + i*4 + offset) = user_mode_pattern[i];
		}
	}
	if(bist_patt==SIPI_MODE)
	{
		//set sipi data pattern
		REG32(0x300D0010+offset) = sipi_mode_pattern[0];
		REG32(0x300D0014+offset) = sipi_mode_pattern[1];
		REG32(0x300D0018+offset) = sipi_mode_pattern[2];
		REG32(0x300D001C+offset) = sipi_mode_pattern[3];
		REG32(0x300D0020+offset) = sipi_mode_pattern[4];
		REG32(0x300D0024+offset) = sipi_mode_pattern[5];
		REG32(0x300D0028+offset) = sipi_mode_pattern[6];
		REG32(0x300D0030+offset) = sipi_mode_pattern[7];
	}
}

void sipi_bit_pat_sel(uint32 chn_num,uint32 bist_num,uint32 pat_num)
{
	volatile uint32 i =0;
	volatile uint32 offset = bist_num*0x400+chn_num*0x00800000;
	switch(pat_num)
	{
		case 0:
			REG32(0x300d0028+offset)=0x00010001;
			REG32(0x300d002c+offset)=0x00010001;
			break;
		case 1:
			REG32(0x300d0028+offset)=0x00040004;
			REG32(0x300d002c+offset)=0x00040004;
			break;
		case 2:
			REG32(0x300d0028+offset)=0x00100010;
			REG32(0x300d002c+offset)=0x00100010;
			break;
		case 3:
			REG32(0x300d0028+offset)=0x00400040;
			REG32(0x300d002c+offset)=0x00400040;
			break;
		case 4:
			REG32(0x300d0028+offset)=0x01000100;
			REG32(0x300d002c+offset)=0x01000100;
			break;
		case 5:
			REG32(0x300d0028+offset)=0x04000400;
			REG32(0x300d002c+offset)=0x04000400;
			break;
		case 6:
			REG32(0x300d0028+offset)=0x10001000;
			REG32(0x300d002c+offset)=0x10001000;
			break;
		case 7:
			REG32(0x300d0028+offset)=0x40004000;
			REG32(0x300d002c+offset)=0x40004000;
			break;
	}
}


uint32 bist_test(uint32 write_or_read,uint32 bist_patt,uint32 bist_len,uint32 pat_num)
{
	volatile uint32 i = 0;
	volatile uint32 bist_result = 0;

	//for(i = 0; i < 2000; i++);		

	bist_en(DDR_CHN0);	
	bist_en(DDR_CHN1);


	bist_clear(DDR_CHN0,BIST_ARM);
	//bist_clear(DDR_CHN0,BIST_GPU);
		
	
	bist_clear(DDR_CHN1,BIST_ARM);
	//bist_clear(DDR_CHN1,BIST_GPU);



	bist_set(DDR_CHN0,BIST_ARM,write_or_read,bist_patt,0x00000000,bist_len);
	//bist_set(DDR_CHN0,BIST_GPU,BIST_ONEWRC,0x10000000,0x1000);

	
	bist_set(DDR_CHN1,BIST_ARM,write_or_read,bist_patt,0x00000000,bist_len);
	//bist_set(DDR_CHN1,BIST_GPU,BIST_ONEWRC,0x10000000,0x10000000);

	if(bist_patt==SIPI_MODE)
	{
		sipi_bit_pat_sel(DDR_CHN0,BIST_ARM,pat_num);
		sipi_bit_pat_sel(DDR_CHN1,BIST_ARM,pat_num);
	}


	bist_trigger(DDR_CHN0,BIST_ARM);
	//bist_trigger(DDR_CHN0,BIST_GPU);	

	
	bist_trigger(DDR_CHN1,BIST_ARM);
	//bist_trigger(DDR_CHN1,BIST_GPU);	

	bist_wait_done(DDR_CHN0,BIST_ARM);
	//bist_wait_done(DDR_CHN0,BIST_GPU);


	bist_wait_done(DDR_CHN1,BIST_ARM);
	//bist_wait_done(DDR_CHN1,BIST_GPU);


	bist_result += get_bist_result(DDR_CHN0, BIST_ARM);
	//bist_result += get_bist_result(DDR_CHN0, BIST_GPU);


	bist_result += get_bist_result(DDR_CHN1, BIST_ARM);
	//bist_result += get_bist_result(DDR_CHN1, BIST_GPU);

	bist_clear(DDR_CHN0,BIST_ARM);
	//bist_clear(DDR_CHN0,BIST_GPU);
	

	bist_clear(DDR_CHN1,BIST_ARM);
	//bist_clear(DDR_CHN1,BIST_GPU);


	bist_dis(DDR_CHN0);	
	bist_dis(DDR_CHN1);
	
	return bist_result;
}
#endif


