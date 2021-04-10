#include "ddrc_common.h"
#include "ddrc_r2p2_scan_offline.h"
#include "ddrc_init.h"
#include "dram_test.h"
#include <fdl_channel.h>
#include <asm/arch/sprd_reg.h>

#ifdef SCAN_USB_LOG_ENABLE
#define dmc_print_str(x) dmc_print_usb(x)
#define print_Hex(x) print_Hex_Usb(x)
#define print_Dec(x) print_Dec_Usb(x)
struct FDL_ChannelHandler *fdl_channel;
#endif

#define QUAR_DELAY_FREQ DDR_CLK_622M

#define SCAN_LEN   MAX_DQ_DELAY
#define SCAN_MIN_PASS_WINIDOW 10
#define INTERLEAVE_MODE 1
#define NON_INTERLEAVE_MODE 0
#define DLL_CNT_NUM 6
#define SCAN_RATE 1
static u64 ddr_size;

extern DRAM_INFO_T dram_info;
extern u32 user_mode_pattern[];

static u32 first_pass,last_pass;
static u32 freq_fn = 0;
u32 pass_win_max_scan[DDR_CHANNEL_NUM+1] = {0,0};
/*ca call sdram initmay change this value*/
u32 pass_win_max_scan_tmp[DDR_CHANNEL_NUM+1] = {0,0};
//static u32 seed = 0x2345abcd;

static u32 scan_mid = 0;
static u32 scan_pas_wind = 0;
static u32 scan_pas_wind_tmp = 0;
static u32 scan_vref = 0;
static u32 interleave_en = NON_INTERLEAVE_MODE;
/*for perbit san*/
u32 bit_mask_num = 0xFFFF;
u32 scan_ui;
u32 delay_min;
u32 delay_max;

u32 delay_min_wr;
u32 delay_max_wr;
extern DDRC_FREQ_INFO_T ddrc_freq_info_lp3[];
extern DDRC_FREQ_INFO_T ddrc_freq_info_lp4[];

u32 pass_rate = 0;
//lp3 setup
int eye_mask_vol_high;
int eye_mask_vol_low;
int eye_mask_vol_high_hold;
int eye_mask_vol_low_hold;

u32 eye_mask_pass_rate_high = 0;
u32 eye_mask_pass_rate_low = 0;
u32 eye_mask_pass_rate_high_hold = 0;
u32 eye_mask_pass_rate_low_hold = 0;

u32 scan_final_result[2] = {0,0};
u32 curr_delay_cell;
char str_dl[DLL_CNT_NUM][8] = {"AC0: ","AC1: ","DS0: ","DS1: ","DS2: ","DS3: "};
u32 delay_cell[DLL_CNT_NUM];
char string_item[3][4] = {"RD","WR","CA"};
extern int first_init;

uint32 scan_bist1;
uint32 scan_bist2;
uint32 scan_debug;
uint32 write_flag;
/*
u32 rand_u32(){
	u32 d;
	d=((seed >> 3)^seed)&0x1ffffffe;
	seed=(seed>>29)|d<<2;
	d=((seed>>3)^seed)&0xf;
	seed>>=3;
	seed|=d<<28;
	return seed;
}
*/
#ifdef SCAN_USB_LOG_ENABLE
void dmc_print_usb(const char *string)
{
	char *s1 = NULL;
	u32 num = 0;

	s1 = (char *)string;

	while (*s1 != '\0')
	{
		s1++;
		num++;
	}
	s1 = string;
	fdl_channel->Write (fdl_channel, s1, num);
}


static char  log_string[33];
static char *  toStrDec(u32 val)
{
	int i, j, num;
	u32 temp = val;	num = 0;
	do{
		num++;
		temp /= 10;
	}while(temp > 0);
	for(i = num-1; i >= 0; i--)
	{
		temp = (val%10) + 0x30;
		val /= 10;
		log_string[i] = temp & 0xff;
	}
	log_string[num] = ' ';
	log_string[num + 1] = 0;
	return log_string;
}

static char *  toStrHex(u32 val)
{
	int i, j, num;
	u32 temp = val;
	log_string[0] = '0';
	log_string[1] = 'x';
	for(i = 0; i < 8; i++)
	{
		temp = (val >> ((7 - i) * 4)) & 0xf;
		if (temp < 0xa)
			log_string[2 + i] = temp + 0x30;
		else
			log_string[2 + i] = 'A' + temp - 0xa;
	}
	log_string[10] = ' ';
	log_string[11] = 0;
	return log_string;
}

static int  print_Dec_Usb(u32 val)
{
	if(val <0)
	{
		dmc_print_usb("-");
		val = 0 - val;
	}
	dmc_print_usb(toStrDec(val));
	return 0;
}

static int  print_Hex_Usb(u32 val)
{
	dmc_print_usb(toStrHex(val));
	return 0;
}
#endif
static void bist_init_scan(u32 bist_chn_num,u32 bist_start_addr,u32 bist_data_mode,u32 write_or_read,u32 bist_size)
{
	u32 val=0,i;
	volatile u32 offset = bist_chn_num*0x4000;
	//bist clear
	bist_clear(bist_chn_num);
	/*clear to 0*/
	__raw_writel(BIST_BASE_ADDR+0x00+offset,0);
	reg_bit_set(BIST_BASE_ADDR+0x00+offset, 0, 1, 0x1);

	switch(bist_data_mode)
	{
	case LFSR_DATA_PATTERN:
		reg_bit_set(BIST_BASE_ADDR+0x00+offset, 5, 2, LFSR_DATA_PATTERN);
		reg_bit_set(BIST_BASE_ADDR+0x00+offset, 7, 4,0xf);
		reg_bit_set(BIST_BASE_ADDR+0x00+offset,11, 3, FOUR_WORDS);

		/*patten*/
		__raw_writel(BIST_BASE_ADDR+0xcc+offset,0x00d500ca);
		__raw_writel(BIST_BASE_ADDR+0xd0+offset,0x00d700cb);
		__raw_writel(BIST_BASE_ADDR+0xd4+offset,0x00ca00c5);
		__raw_writel(BIST_BASE_ADDR+0xd8+offset,0x00e800d4);

		break;
	case SIPI_DATA_PATTERN://m9+m12
		reg_bit_set(BIST_BASE_ADDR+0x00+offset, 5, 2, SIPI_DATA_PATTERN);
		reg_bit_set(BIST_BASE_ADDR+0x00+offset, 7, 4,7);
		reg_bit_set(BIST_BASE_ADDR+0x00+offset,11, 3, FOUR_WORDS);
		reg_bit_set(BIST_BASE_ADDR+0x00+offset,27, 1, 0x1);//sipi auto

		/*patten*/
		__raw_writel(BIST_BASE_ADDR+0x10+offset,0x8542a150);
		__raw_writel(BIST_BASE_ADDR+0x14+offset,0x542a150a);
		__raw_writel(BIST_BASE_ADDR+0x18+offset,0x540150a8);
		__raw_writel(BIST_BASE_ADDR+0x1c+offset,0x40540540);
		__raw_writel(BIST_BASE_ADDR+0x20+offset,0x05405405);
		__raw_writel(BIST_BASE_ADDR+0x24+offset,0x54054054);
		if(dram_info.dram_type > DRAM_LP3)
		{
			__raw_writel(BIST_BASE_ADDR+0x28+offset,0x00550055);
			__raw_writel(BIST_BASE_ADDR+0x2c+offset,0x00550055);
		}
		else
		{
			__raw_writel(BIST_BASE_ADDR+0x28+offset,0x00010001);
			__raw_writel(BIST_BASE_ADDR+0x2c+offset,0x00010001);
		}
		__raw_writel(BIST_BASE_ADDR+0x30+offset,0x028140a0);
		__raw_writel(BIST_BASE_ADDR+0x34+offset,0x28140a05);
		__raw_writel(BIST_BASE_ADDR+0x38+offset,0xa800a050);
		__raw_writel(BIST_BASE_ADDR+0x3c+offset,0x80a80a80);
		__raw_writel(BIST_BASE_ADDR+0x40+offset,0x0a80a80a);
		__raw_writel(BIST_BASE_ADDR+0x44+offset,0xa80a80a8);
		break;
	case USER_DATA_PATTERN:
		//bist enable
		reg_bit_set(BIST_BASE_ADDR+0x00+offset, 5, 2, USER_DATA_PATTERN);
		reg_bit_set(BIST_BASE_ADDR+0x00+offset, 7, 4,0xf);
		reg_bit_set(BIST_BASE_ADDR+0x00+offset,11, 3, FOUR_WORDS);
		/*patten*/
		for(i = 0; i < 32; i++)
		{
			__raw_writel(BIST_BASE_ADDR+0x30+i*4+offset,user_mode_pattern[i]);
		}
		break;
	default:while(1);
	}

	reg_bit_set(BIST_BASE_ADDR+0x00+offset, 3, 2, write_or_read);
	if(interleave_en == NON_INTERLEAVE_MODE)
	reg_bit_set(BIST_BASE_ADDR+0x00+offset, 24, 2, 3);
	reg_bit_set(BIST_BASE_ADDR+0x00+offset,28,1,(dram_info.dram_type==DRAM_LP3)?0x1:0x0);

	__raw_writel(BIST_BASE_ADDR+0x04+offset,bist_size);
	__raw_writel(BIST_BASE_ADDR+0x08+offset,bist_start_addr);
#ifdef PERBIT_SCAN
			/*phy 0 ,1 bit 0 config at the same time*/
	if(dram_info.dram_type > DRAM_LP3)
	{
		val = ~(bit_mask_num |(bit_mask_num <<16));
	}
	else
	{
		if(bit_mask_num != 0xFFFF)
			val = ~bit_mask_num;
		else
			val = 0;
	}
	__raw_writel(BIST_BASE_ADDR+0x0C+offset,val);
#endif

}

u32 lfsr_bist_sample(u32 bist_addr)
{
	u32 ret;
	ret = 0;
	bist_init_scan(0,bist_addr,LFSR_DATA_PATTERN,BIST_ALLWRC,SCAN_BIST_SIZE);
	bist_test_entry_chn(0,&ret);
	return ret;
}

static int sipi_bist_sample(u32 bist_addr)
{
	u32 ret;
	ret = 0;
	bist_init_scan(0,bist_addr,SIPI_DATA_PATTERN,BIST_ALLWRC,SCAN_BIST_SIZE);
	bist_test_entry_chn(0,&ret);
	return ret;

}

static int usrdef_bist_sample(u32 bist_addr)
{
	u32 ret;
	ret = 0;
	bist_init_scan(0,bist_addr,USER_DATA_PATTERN,BIST_ALLWRC,SCAN_BIST_SIZE);
	bist_test_entry_chn(0,&ret);
	return ret;

}
#if 0
static u32 get_training_middle(u32 default_cfg_dl_ds,u32 byte,u32 clk,u32 pass_win,u32 *ps_start,u32 *ps_end,u32 ca)
{
	u32 middle_temp,regval,tmp;

	middle_temp = default_cfg_dl_ds & 0xff;
	if((clk <= 384) && (ca == 0))
		middle_temp += 0;//default_cfg_dl_ds&(1<<7)?0x40:0;write bit 7 set 1 by write
	else if((clk <= 384) && (ca == 1))
		middle_temp += default_cfg_dl_ds&(1<<15)?0x80:0;
	else
		middle_temp += default_cfg_dl_ds&(1<<15)?0x40:0;

	middle_temp += default_cfg_dl_ds&(1<<23)?0x20:0;
	if(ca)
	{
		regval = REG32(DMC_PHY_REG_BASE_ADDR + 0x644 + 0x40*(byte));//bypte/2=channel
		curr_delay_cell = delay_cell[(1 - ca)];
	}
	else
	{
		regval = REG32(DMC_PHY_REG_BASE_ADDR + 0x6C4 + 0x40*byte);
		curr_delay_cell = delay_cell[(2 + byte)];
	}
	regval &= 0x7F;

	/*933, 1200  absolute dll = relative dll * dll_cnt  / 0x40 */
	/*below 933  absolute dll = relative dll * dll_cnt  / 0x20*/
	if(clk >= DDR_CLK_1024M)
	{
		middle_temp = (middle_temp << 2);
		middle_temp += ((default_cfg_dl_ds >> 24) & 0x3);
		middle_temp = (middle_temp*regval)/0x40;
		tmp = ((pass_win&0xFF)*regval)/(0x40*2);
		tmp *= 4;
		dmc_print_str("training--> pass window: ");
		print_Hex((tmp*2));
		dmc_print_str("raw win&dll cnt:");
		print_Hex((pass_win&0xFF));
		print_Hex(regval);
		if(middle_temp < tmp)
			*ps_start = 0;
		else
			*ps_start = middle_temp - tmp;
		*ps_end = middle_temp + tmp;
	}
	else
	{
		if(clk > QUAR_DELAY_FREQ)
		{
			middle_temp = (middle_temp << 2);
			middle_temp += ((default_cfg_dl_ds >> 24) & 0x3);
		}
		middle_temp = (middle_temp*regval)/0x20;
		tmp = ((pass_win&0xFF)*regval)/(0x20*2);
		if(clk > QUAR_DELAY_FREQ)
		{
			tmp *= 4;
		}
		dmc_print_str("training--> pass window: ");
		print_Hex((tmp*2));
		if(middle_temp < tmp)
			*ps_start = 0;
		else
			*ps_start = middle_temp - tmp;
		*ps_end = middle_temp + tmp;
	}
	return middle_temp;


}
#endif
u32 write_flag_scan;
static u32 get_training_middle(u32 default_cfg_dl_ds,u32 byte,u32 clk,u32 pass_win,u32 *ps_start,u32 *ps_end,u32 ca)
{
	u32 middle_temp,regval,tmp;

	middle_temp = default_cfg_dl_ds & 0xff;
	/*if((clk <= 384) && (ca == 0))
		middle_temp += 0;//default_cfg_dl_ds&(1<<7)?0x40:0;write bit 7 set 1 by write
	else if((clk <= 384) && (ca == 1))
		middle_temp += default_cfg_dl_ds&(1<<15)?0x80:0;
	else
		middle_temp += default_cfg_dl_ds&(1<<15)?0x40:0;
	middle_temp += default_cfg_dl_ds&(1<<23)?0x80:0;
	*/

	if( ca || write_flag_scan)
	{
		if((clk <= 384) )
			middle_temp += default_cfg_dl_ds&(1<<15)?0x80:0;
		else
			middle_temp += default_cfg_dl_ds&(1<<15)?0x40:0;

		middle_temp += default_cfg_dl_ds&(1<<23)?0x80:0;
	}
	if(ca)
	{
		regval = REG32(DMC_PHY_REG_BASE_ADDR + 0x644 + 0x40*(byte));//bypte/2=channel
		curr_delay_cell = delay_cell[(1 - ca)];
	}
	else
	{
		regval = REG32(DMC_PHY_REG_BASE_ADDR + 0x6C4 + 0x40*byte);
		curr_delay_cell = delay_cell[(2 + byte)];
	}
	regval &= 0x7F;

	/*over 933  absolute dll = relative dll * dll_cnt  / 0x80 */
	/*below 933  absolute dll = relative dll * dll_cnt  / 0x40*/
	if(clk >= DDR_CLK_933M)//256,384 not training scan
	{
		middle_temp = (middle_temp << 3);
		middle_temp += ((default_cfg_dl_ds >> 24) & 0x7);
		if(write_flag_scan)
			middle_temp = (middle_temp*regval)/0x80/2;
		else
			middle_temp = (middle_temp*regval)/0x80;
		tmp = ((pass_win&0xFF)*regval)/(0x80*2);
		tmp *= 8;
		dmc_print_str("training--> pass window: ");
		print_Hex((tmp));
		dmc_print_str("raw win&dll cnt:");
		print_Hex((pass_win&0xFF));
		print_Hex(regval);
		if(middle_temp < tmp)
			*ps_start = 0;
		else
			*ps_start = middle_temp - tmp;
		*ps_end = middle_temp + tmp;
	}
	else
	{
		if(clk > QUAR_DELAY_FREQ)
		{
			middle_temp = (middle_temp << 3);
			middle_temp += ((default_cfg_dl_ds >> 24) & 0x7);
		}
		if(write_flag_scan)
			middle_temp = (middle_temp*regval)/0x40/2;
		else
			middle_temp = (middle_temp*regval)/0x40;
		tmp = ((pass_win&0xFF)*regval)/(0x40*2);
		if(clk > QUAR_DELAY_FREQ)
		{
			tmp *= 8;
		}
		dmc_print_str("training--> pass window: ");
		print_Hex((tmp));
		if(middle_temp < tmp)
			*ps_start = 0;
		else
			*ps_start = middle_temp - tmp;
		*ps_end = middle_temp + tmp;
	}
	return middle_temp;


}
void lp4_interleave_en(u32 inter_en)
{
	if(dram_info.dram_type > DRAM_LP3)
	{
		if(inter_en==1)
		{
			reg_bit_set(DMC_CTL0_(0x0148), 0,14,0);//ch0 linear base
			reg_bit_set(DMC_CTL0_(0x0148), 16,14,0);//ch1 linear base
			reg_bit_set(DMC_CTL0_(0x0150), 0,14,0);//interleave base
			reg_bit_set(DMC_CTL0_(0x0150), 16,14,0);//interleave offset
			interleave_en = INTERLEAVE_MODE;
		}
		else
		{
			reg_bit_set(DMC_CTL0_(0x0148), 0,14,0);//ch0 linear base
			reg_bit_set(DMC_CTL0_(0x0148), 16,14,((ddr_size/2)>>20));//ch1 linear base
			reg_bit_set(DMC_CTL0_(0x0150), 0,14,0x3FFF);//interleave base
			reg_bit_set(DMC_CTL0_(0x0150), 16,14,0);//interleave offset
			interleave_en = NON_INTERLEAVE_MODE;
		}
	}
}

void dmc_reg_dump(void)
{
	u32 regval, i, j, reg_len[2] = {0x80C,0x624},base_add[2] = {DMC_PHY_REG_BASE_ADDR,DMC_CTL_REG_BASE_ADDR};

	for(j = 0;j < 2;j++)
	{
		if(j==0)
			dmc_print_str("phy reg:\r\n");
		else
			dmc_print_str("dmc reg:\r\n");
		for(i=0; i<=reg_len[j];)
		{
			print_Hex(i);
			dmc_print_str(":");
			regval = REG32(base_add[j] + i);
			print_Hex(regval);
			regval = REG32(base_add[j] + 4 +i);
			print_Hex(regval);
			regval = REG32(base_add[j] + 8 + i);
			print_Hex(regval);
			regval = REG32(base_add[j] + 12 + i);
			print_Hex(regval);
			dmc_print_str("\r\n");
			i+=0x10;
		}
	}

}

static void scan_pre_set(u32 clk)
{
	u32 regval,i;
	u64 size;
	u32 half_mode;
	u32 clk_mode;
	u32 tmp = 1;
	dmc_print_str("\r\nscan ddr type: ");

	if(dram_info.dram_type == DRAM_LP4)
		dmc_print_str("lpddr4\r\n");
	else if(dram_info.dram_type == DRAM_LP4X)
		dmc_print_str("lpddr4x\r\n");
	else if(dram_info.dram_type == DRAM_LP3)
		dmc_print_str("lpddr3\r\n");

	ddr_size = dram_info.cs0_size + dram_info.cs1_size;
	if(ddr_size > 0x140000000)
	{
		ddr_size = 0x100000000;
		dram_info.cs0_size = 0x80000000;
		reg_bit_set(DMC_CTL0_(0x0000), 0, 3,6);
	}

	/*enable reg write*/
	__raw_writel(DMC_CTL0_(0x009c),0xdeadbeef);

	regval = REG32(DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0x60);
	half_mode = (regval >> 2)&0x01;
	if(regval&(1<<3))
	{
		if(regval&(1<<24))
			clk_mode = 0;//1x
		else
			clk_mode = 2;//4x
	}
	else
		clk_mode = 1;//2x

	dmc_print_str("\r\nrf SCAN RATE is: ");
	print_Dec(SCAN_RATE);

	dmc_print_str("\r\nrf dll cnt&delay cell(fs): ");
	for(i = 0; i < DLL_CNT_NUM; i++)
	{
		//l5pro
		dmc_print_str(str_dl[i]);
		regval = REG32(DMC_PHY_REG_BASE_ADDR + 0x644 + i*0x40);
		print_Dec(regval&0x7F);
		if(clk < DDR_CLK_512M)
		{
			tmp = 250000000/clk/(regval&0x7F);
			//<512,4x half,4x = 2*regval 
			scan_ui = (regval&0x7F)*2*8/2;
		}
		else if((clk < DDR_CLK_933M) && (clk >= DDR_CLK_512M))
		{
			tmp = 500000000/clk/(regval&0x7F);
			//512~1024,xx half,4x = regval 
			scan_ui = (regval&0x7F)*1*8/2;
		}
		else if((clk <= DDR_CLK_1866M) && (clk >= DDR_CLK_933M))
		{
			tmp = 1000000000/clk/(regval&0x7F);
			//>=1024,1x half,4x = regval /2
			scan_ui = (regval&0x7F)/2*8/2;
		}
		print_Dec(tmp);
		delay_cell[i] = tmp;
	/*	//l5
		dmc_print_str(str_dl[i]);
		regval = REG32(DMC_PHY_REG_BASE_ADDR + 0x644 + i*0x40);
		print_Dec(regval&0x7F);
		tmp = (((1000000000/clk)/(regval&0x7F)/(1+half_mode))*2)>> clk_mode;
		print_Dec(tmp);
		delay_cell[i] = tmp;
	*/
	}

#if 0 	//l5
	/*quarter delay ui*/
	scan_ui = (1000000000/clk)*2/tmp;
	/*1/5 scan_ui*/
	tmp = scan_ui/4;
	scan_ui -= tmp;
#endif

	if(clk <= QUAR_DELAY_FREQ)
		scan_ui /= 4;
	
	dmc_print_str("\r\nscan_ui: ");
	print_Hex(scan_ui);

	/*disable period cpst and wbuf merge*/
	reg_bit_set(DMC_CTL0_(0x0144), 16,2,0x0);
	reg_bit_set(DMC_CTL0_(0x0114), 24,1,0x0);//disable mr4
	reg_bit_set(DMC_CTL0_(0x0118), 24,1,0x0);//disable auto zqc
	reg_bit_set(DMC_CTL0_(0x0124), 2,1,0x0);//drf_auto_self_ref_en
	reg_bit_set(DMC_CTL0_(0x010c), 12,1,0x0);//drf_auto_self_ref_en

	lp4_interleave_en(NON_INTERLEAVE_MODE);
	if(dram_info.dram_type > DRAM_LP3)
	{
		dmc_mrw(DRAM_MR_13, DRAM_CS_ALL, (1 << 3));
		dmc_print_str("\r\nVRCG mode\r\n");
	}
	//dram_dq_odt_set(1);
}

static void scan_ca_pre_set(int i,u32 vref)
{
	u32 regval;
	u64 size;

	ddr_size = dram_info.cs0_size + dram_info.cs1_size;
	__raw_writel(DMC_CTL0_(0x009c),0xdeadbeef);

	reg_bit_set(DMC_CTL0_(0x0144), 16,2,0x0);
	reg_bit_set(DMC_CTL0_(0x0114), 24,1,0x0);//disable mr4
	reg_bit_set(DMC_CTL0_(0x0118), 24,1,0x0);//disable auto zqc
	reg_bit_set(DMC_CTL0_(0x0124), 2,1,0x0);//drf_auto_self_ref_en
	reg_bit_set(DMC_CTL0_(0x010c), 12,1,0x0);//drf_auto_self_ref_en

	lp4_interleave_en(NON_INTERLEAVE_MODE);
	if(dram_info.dram_type > DRAM_LP3)
	{
		dmc_mrw(DRAM_MR_13, DRAM_CS_ALL, (1 << 3));
		wait_us(5);
		
		/*set CA vref*/
		reg_bit_set(DMC_CTL0_(0x0100),20,4,(1<<i));
		dmc_mrw(DRAM_MR_12, DRAM_CS_ALL, vref);
		/*delay at least 500ns for vref update*/
		wait_us(5);
		reg_bit_set(DMC_CTL0_(0x0100),20,4,3);

		//dram_dq_odt_set(1);
	}
	else
	{
		reg_bit_set((REG_AON_APB_RF_BASE+0x348), 2, 8, vref);
		wait_us(2);
	}
}

static u32 get_bist_address_lp4(u32 channel_num,u32 rank_num)
{
	u32 bist_addr,rand32;
	/*dram_info.cs0_size ->two phy*/
	if(channel_num == 0)
	{
		if(rank_num == 0)
			bist_addr = 0;
		else
			bist_addr = dram_info.cs0_size/2;
	}
	else
	{
		if(rank_num == 0)
			bist_addr = ddr_size/2;
		else
			bist_addr = (ddr_size/2 + dram_info.cs0_size/2);
	}

	//rand32 = rand_u32()%0x40000;
	//bist_addr += rand32;
	return bist_addr;
}

void print_scan_result(u32 rank,u32 byte,u32 shift)
{
	dmc_print_str("\r\n\r\nscan result--> pass window:");
	print_Hex(scan_pas_wind);

	dmc_print_str("mid:");
	print_Hex(scan_mid);

	dmc_print_str("vref:");
	print_Hex(scan_vref);

	dmc_print_str("\r\ncs");
	print_Dec(rank);

	if(shift == SCAN_CA_ITEM_SHIFT)
		dmc_print_str(" phy");
	else
		dmc_print_str(" byte");
	print_Dec(byte);

	dmc_print_str(" traing vref scan pass rate:");
	print_Dec(pass_rate);
	print_Dec(eye_mask_pass_rate_high);
	print_Dec(eye_mask_pass_rate_low);
	if(dram_info.dram_type == DRAM_LP3)
	{
		print_Dec(eye_mask_pass_rate_high_hold);
		print_Dec(eye_mask_pass_rate_low_hold);
	}

	dmc_print_str("\r\n");
	if((pass_rate < LP4_LP3_MIN_PASS_RATE) || (eye_mask_pass_rate_high < LP4_LP3_MIN_EYE_MASK_PASS_RATE)
		|| (eye_mask_pass_rate_low < LP4_LP3_MIN_EYE_MASK_PASS_RATE))
	{
		scan_final_result[rank] |= (1 << (byte + shift));
	}
	if(dram_info.dram_type == DRAM_LP3)
	{
		if((eye_mask_pass_rate_high_hold < LP4_LP3_MIN_EYE_MASK_PASS_RATE)||
			(eye_mask_pass_rate_low_hold < LP4_LP3_MIN_EYE_MASK_PASS_RATE))
		{
			scan_final_result[rank] |= (1 << (byte + shift));
		}
	}
}

uint32 aa=0;
uint32 bb = 0;;
uint32 cc = 0;
static void check_scan_result(u32 bist_addr,u32 *flag,u32 delay,int *channel,u32 vref,u32 max_delay)
{
	u32 chk_flag;
	u32 channel_num,pass_winodw;
	//channel_num = *channel;
	//bist_addr = get_bist_address_lp4(channel_num, 0);

	chk_flag = *flag;
	if(delay==0)
		print_Dec(0);
	/*cs n ,channel n ,byte n bist*/
	if((0 != lfsr_bist_sample(bist_addr))|| (0 != sipi_bist_sample(bist_addr)) || (0 != usrdef_bist_sample(bist_addr)))
	//if(0 != dram_bist_specific_space(0x0,0x1000))
	{
		dmc_print_str(" ");
aa++;
		if(((chk_flag & SCAN_FST_PAS_FLAG) != 0) && (((chk_flag & SCAN_LAST_PAS_FLAG)) == 0))
		{
			last_pass = delay - SCAN_RATE;
			if((last_pass - first_pass) < SCAN_MIN_PASS_WINIDOW)
			{
				chk_flag &= ~SCAN_LAST_PAS_FLAG;
				chk_flag &= ~SCAN_FST_PAS_FLAG;
			}
			else
			{
				chk_flag |= SCAN_LAST_PAS_FLAG;
			}
		}
		if(channel !=NULL)
		{
			if(dram_info.dram_type < DRAM_LP4)
			{
				regulator_set_voltage("vddmem",0);
				wait_us(1000);
			}
			sdram_init();
			scan_ca_pre_set((*channel),vref);
		}
	}
	else
	{
		if (chk_flag & SCAN_VREF_FLAG)
		{
bb++;
			dmc_print_str("S");
			if((chk_flag & SCAN_FST_PAS_FLAG) == 0)
			{
				first_pass = delay;
				chk_flag |= SCAN_FST_PAS_FLAG;
			}
		}
		else
		{
cc++;
			dmc_print_str("*");
if(scan_debug == 1){
//	while(1);
}
			if((chk_flag & SCAN_FST_PAS_FLAG) == 0)
			{
				first_pass = delay;
				chk_flag |= SCAN_FST_PAS_FLAG;
			}
		}
	}
	if(delay ==(max_delay-SCAN_RATE))
	{
		pass_winodw = last_pass - first_pass + SCAN_RATE;
		scan_pas_wind_tmp = pass_winodw;
		if((channel !=NULL) && (dram_info.dram_type > DRAM_LP3))
			scan_pas_wind_tmp /= 2;
		if(pass_winodw > scan_pas_wind)
		{
			scan_pas_wind = pass_winodw;
			scan_mid = (last_pass + first_pass)/2;
			scan_vref = vref;
		}
		chk_flag &= ~SCAN_LAST_PAS_FLAG;
		chk_flag &= ~SCAN_FST_PAS_FLAG;
	}
	*flag = chk_flag;
	if(((delay+1)%10) == 0)
	{
		//dmc_print_str(" ");
		print_Dec(((delay+1)/10));
	}

}

static u32 get_pass_rate(u32 pass_wind)
{
	u32 tmp, ui, ddr_clk, rate;

	/*pass winodw fs*/
	if(dram_info.dram_type > DRAM_LP3)
		ddr_clk = ddrc_freq_info_lp4[freq_fn].ddr_clk;
	else
		ddr_clk = ddrc_freq_info_lp3[freq_fn].ddr_clk;
	tmp = curr_delay_cell*pass_wind;
	if(ddr_clk > QUAR_DELAY_FREQ)
		tmp /= 8;
	dmc_print_str("pass window(fs):");
	print_Dec(tmp);
	//tmp = tmp * SCAN_RATE;
	/*ui ps*/
	ui = (1000000 / ddr_clk) / 2;
	rate = (tmp / ui) / 10;
	return rate;
}

static void check_scan_result_second(u32 ps_start,u32 ps_end,u32 chk_flag,u32 middle_temp,u32 vref,u32 max_delay)
{
	u32 delay,tmp;

	dmc_print_str(":fst_pas:");
	print_Dec(first_pass);
	dmc_print_str("last_pas:");
	print_Dec(last_pass);
	dmc_print_str("delta:");
	print_Dec(last_pass - first_pass + 1);
	dmc_print_str("mid:");
	print_Dec((first_pass + last_pass)/2);
	if(chk_flag & SCAN_VREF_FLAG)
	{
		/*scan pass winodw*/
		pass_rate = get_pass_rate(scan_pas_wind_tmp);

		dmc_print_str("\r\nVref: ");
		print_Hex(vref);
		for(delay = delay_min; delay < delay_max; delay = delay + SCAN_RATE)
		{
			if(delay==0)
				print_Dec(0);
			if(middle_temp == delay)
				dmc_print_str("M");
			else if((delay >= ps_start) && (delay <= ps_end))
				dmc_print_str("T");
			else
				dmc_print_str(" ");
			if(((delay+1)%10) == 0)
			{
				//dmc_print_str(" ");
				print_Dec(((delay+1)/10));
			}
		}
		dmc_print_str(":fst_pas:");
		print_Dec(ps_start);
		dmc_print_str("last_pas:");
		print_Dec(ps_end);
		dmc_print_str("delta:");
		print_Dec(ps_end - ps_start + 1);
		dmc_print_str("mid:");
		print_Dec((ps_start + ps_end)/2);
		/*training pass winodw*/
		scan_pas_wind_tmp = ps_end - ps_start + 1;
	}
	tmp = get_pass_rate(scan_pas_wind_tmp);
	if(chk_flag & SCAN_EYE_MASK_LP3_SETUP_LP4_HIGH_FLAG)
	{
		eye_mask_pass_rate_high = tmp;
	}
	else if(chk_flag & SCAN_EYE_MASK_LP3_SETUP_LP4_LOW_FLAG)
	{
		eye_mask_pass_rate_low = tmp;
	}
	else if(chk_flag & SCAN_EYE_MASK_LP3_HOLD_HIGH_FLAG)
	{
		eye_mask_pass_rate_high_hold = tmp;
	}
	else if(chk_flag & SCAN_EYE_MASK_LP3_HOLD_LOW_FLAG)
	{
		eye_mask_pass_rate_low_hold = tmp;
	}

}

static void eye_mask_vol_lp3(u32 default_vref)
{
	eye_mask_vol_high = default_vref + LP3_EYE_MASK_VOL_SETUP_STEP;
	eye_mask_vol_low = default_vref - LP3_EYE_MASK_VOL_SETUP_STEP;
	eye_mask_vol_high_hold = default_vref + LP3_EYE_MASK_VOL_HOLD_STEP;
	eye_mask_vol_low_hold = default_vref - LP3_EYE_MASK_VOL_HOLD_STEP;
	if(eye_mask_vol_high > VREF_DDR_START)
		eye_mask_vol_high = VREF_DDR_START;
	if(eye_mask_vol_high_hold > VREF_DDR_START)
		eye_mask_vol_high_hold = VREF_DDR_START;
	if(eye_mask_vol_low < VREF_DDR_END_LP3)
		eye_mask_vol_low = VREF_DDR_END_LP3;
	if(eye_mask_vol_low_hold < VREF_DDR_END_LP3)
		eye_mask_vol_low_hold = VREF_DDR_END_LP3;
}

static void eye_mask_vol_flag(u32 vol,u32* flag)
{
	if(vol == eye_mask_vol_high)
		*flag |= SCAN_EYE_MASK_LP3_SETUP_LP4_HIGH_FLAG;
	else
		*flag &= ~SCAN_EYE_MASK_LP3_SETUP_LP4_HIGH_FLAG;
	if(vol == eye_mask_vol_low)
		*flag |= SCAN_EYE_MASK_LP3_SETUP_LP4_LOW_FLAG;
	else
		*flag &= ~SCAN_EYE_MASK_LP3_SETUP_LP4_LOW_FLAG;
	if(dram_info.dram_type < DRAM_LP4)
	{
		if(vol == eye_mask_vol_high_hold)
			*flag |= SCAN_EYE_MASK_LP3_HOLD_HIGH_FLAG;
		else
			*flag &= ~SCAN_EYE_MASK_LP3_HOLD_HIGH_FLAG;
		if(vol == eye_mask_vol_low_hold)
			*flag |= SCAN_EYE_MASK_LP3_HOLD_LOW_FLAG;
		else
			*flag &= ~SCAN_EYE_MASK_LP3_HOLD_LOW_FLAG;
	}
}

static void get_middle_vref_flag(int vref, int default_vref, int middle_temp, int delay, u32 *chk_flag)
{
	if((vref == default_vref) && (middle_temp == delay))
		*chk_flag |= SCAN_MIDDLE_FLAG;
	else
		*chk_flag &= ~SCAN_MIDDLE_FLAG;
	if(vref == default_vref)
		*chk_flag |= SCAN_VREF_FLAG;
	else
		*chk_flag &= ~SCAN_VREF_FLAG;

}

static void set_read_cmos_diff_mode(u32 cmos)
{
	u32 val = 0;

	if(dram_info.dram_type > DRAM_LP3)
		val |= (1 << 1);
	if(cmos == 0)
	{
		dmc_print_str("diff(ib4) mode\r\n");
		/*1 ibc vref no change ,ib4 must config for LP4*/
		reg_bit_set((DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT+0xF4), 21, 3, val);
	}
	else if(cmos == 1)
	{
		dmc_print_str("coms(ibc) mode\r\n");
		/*1 ibc vref no change ,ib4 must config for LP4*/
		reg_bit_set((DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT+0xF4), 21, 3, (val | 1));
	}
}

static void perbit_channel_byte_change(int *channel,int *byte)
{
#ifdef PERBIT_SCAN
	int k;
	if(bit_mask_num !=0xFFFF)
	{
		for(k = 0; k <4; k++)
		{
			if(((bit_mask_num >> k*8)&0xFF) != 0)
			{
				*channel = k/2;
				break;
			}
		}
		if((bit_mask_num >= (1 << 16)) && (dram_info.dram_type > DRAM_LP3))
			bit_mask_num = bit_mask_num >> 16;
		*byte = k;
	}
#endif
}

static void get_delay_min_max(int rank,int byte,u32 mid,u32 max_delay)
{
	u32 tmp;

	//every time need start at same delay_min
	if((rank == 0) && (byte == 0))
	{
		//l5pro max delay - min delay less than 0x40,so use middle - 0x20 = min,middle+0x20 = max
		//scan_ui = 0x20;
		if(write_flag == 0xff)
			scan_ui = scan_ui + 20;//give more for if delay_min not enough
		if(mid < scan_ui)
			delay_min = 0;
		else
		{
			delay_min = mid - scan_ui;
			tmp = delay_min%10;
			delay_min -= tmp;
		}
		if(write_flag == 0xff)
			scan_ui = scan_ui - 20;//restore to normal
		
		delay_max = mid + scan_ui;
		if(delay_max > max_delay)
			delay_max = max_delay;

		/*l5
		if(mid < scan_ui)
			delay_min = 0;
		else
		{
			delay_min = mid - scan_ui;
			tmp = delay_min%10;
			delay_min -= tmp;
		}
		delay_max = mid + scan_ui;
		if(delay_max > max_delay)
			delay_max = max_delay;
		*/
	}
}

static int  scan_write_lp3(int rank_num,u32 clk)
{
	u32 default_vref,chk_flag,vref_flag;
	u32 regval, bist_addr, default_cfg_dl_ds;;
	int i, j, vref, delay;
	u32 reg,middle_temp,pass_flag,max_delay,ps_start, ps_end,tmp;
	u32 scan_cycle,scan_2cycle;
	bist_addr = 0;
	if(rank_num == 1)
		bist_addr = dram_info.cs0_size;
	if(clk > QUAR_DELAY_FREQ)
		max_delay = MAX_DQ_DELAY*8;
	else
		max_delay = MAX_DQ_DELAY;
	write_flag_scan = 1;
	regval = REG32(REG_AON_APB_RF_BASE+0x348);
	default_vref = (regval>>2)&0xFF;
	dmc_print_str("\r\nScan write start\r\n");

	for(i = 0;i < 4; i++)
	{
		perbit_channel_byte_change(&tmp,&i);
		dmc_print_str("\r\nwrite byte: ");
		print_Dec(i);
		dmc_print_str("\r\n");

		reg = DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0x6c + 0x20*i;
		default_cfg_dl_ds = REG32(reg);
		scan_cycle = reg_bit_get(reg, 15, 1);
		scan_2cycle = reg_bit_get(reg, 23, 1);
		middle_temp = get_training_middle(default_cfg_dl_ds,i,clk,(pass_win_max_scan[1]>>(i*8)),&ps_start,&ps_end,0);

		get_delay_min_max(rank_num,i,middle_temp,max_delay);

		dmc_print_str("mid:");
		print_Hex(middle_temp);
		dmc_print_str("vref:");
		print_Hex(default_vref);
		eye_mask_vol_lp3(default_vref);
		scan_pas_wind = 0;

		for (vref = VREF_DDR_START; vref >= VREF_DDR_END_LP3; vref--)
		{
			dmc_print_str("\r\nVref: ");
			print_Hex(vref);

			/*set DQ vref*/
			reg_bit_set((REG_AON_APB_RF_BASE+0x348), 2, 8, vref);

			/*delay at least 500us????*/
			wait_us(5);
			pass_flag = 0;
			first_pass = 0;
			last_pass = 0;
			chk_flag = 0;
			eye_mask_vol_flag(vref,&chk_flag);
			//for(delay = 0; delay < delay_max; delay++)
			for(delay = delay_min; delay < delay_max; delay++)
			{
				/*2cycle cycle set 0*/
				/*
				if(clk <=384)
					reg_bit_set(reg, 7, 1, 1);
				else
					reg_bit_set(reg, 7, 1, 0);

				reg_bit_set(reg, 15, 1, 0);
				*/
				if((default_cfg_dl_ds & 0xff) < 0x20){
					if(scan_cycle == 1 && scan_2cycle == 1)
					{
						reg_bit_set(reg, 15, 1, 0);
						reg_bit_set(reg, 23, 1, 1);
					}
					else if(scan_cycle == 0 && scan_2cycle == 1)
					{
						reg_bit_set(reg, 15, 1, 1);
						reg_bit_set(reg, 23, 1, 0);
					}
					else if(scan_cycle == 1 && scan_2cycle == 0)
					{
						reg_bit_set(reg, 15, 1, 0);
						reg_bit_set(reg, 23, 1, 0);
					}
				}
				reg_bit_set(reg, 31, 1, 0);
				if(clk > QUAR_DELAY_FREQ)
				{
					reg_bit_set(reg, 0, 8, (delay >> 3));
					reg_bit_set(reg, 24, 3, (delay&0x7));
				}
				else
					reg_bit_set(reg, 0, 8, delay);

				dmc_phy_soft_update();

				get_middle_vref_flag(vref,default_vref,middle_temp,delay,&chk_flag);

				check_scan_result(bist_addr,&chk_flag,delay,NULL,vref,delay_max);
			}
			check_scan_result_second(ps_start,ps_end,chk_flag,middle_temp,vref,delay_max);

			REG32(reg) = default_cfg_dl_ds;
			dmc_phy_soft_update();
		}
		print_scan_result(rank_num,i,SCAN_WR_ITEM_SHIFT);
		if(bit_mask_num !=0xFFFF)
		break;
	}
	reg_bit_set((REG_AON_APB_RF_BASE+0x348), 2, 8, default_vref);
	write_flag_scan = 0;
	dmc_print_str("\r\nScan write end\r\n");
	return 0;
}

static int  scan_read_lp3(int rank_num,u32 clk,u32 cmos)
{
	u32 default_vref,chk_flag,vref_flag,pass_flag,ps_start, ps_end;
	u32 regval, bist_addr, default_cfg_rd_dl_ds,default_cfg_rd_dl_ds_pos;
	int i, j, vref, delay;
	u32 tmp,reg,reg_pos,middle_temp,max_delay;
	bist_addr = 0;
	if(rank_num == 1)
		bist_addr = dram_info.cs0_size;
	if(clk > QUAR_DELAY_FREQ)
		max_delay = MAX_DQ_DELAY*8;
	else
		max_delay = MAX_DQ_DELAY;

	default_vref = REG32(DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0xF4);

	dmc_print_str("\r\nScan read start\r\n");

	set_read_cmos_diff_mode(cmos);

	for(i = 0;i < 4; i++)
	{
		perbit_channel_byte_change(&tmp,&i);
		dmc_print_str("\r\nread byte: ");
		print_Dec(i);
		dmc_print_str("\r\n");
		/*reg pos reg neg*/
		reg_pos = DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0x70 + 0x20*i;
		reg = reg_pos + 4;

		default_cfg_rd_dl_ds = REG32(reg);
		default_cfg_rd_dl_ds_pos = REG32(reg_pos);

		middle_temp = get_training_middle(default_cfg_rd_dl_ds,i,clk,(pass_win_max_scan[0]>>(i*8)),&ps_start,&ps_end,0);

		get_delay_min_max(rank_num,i,middle_temp,max_delay);
		dmc_print_str("delay_min: ");
		print_Hex(delay_min);
		dmc_print_str("delay_max: ");
		print_Hex(delay_max);

		dmc_print_str("mid:");
		print_Dec(middle_temp);
		dmc_print_str("vref:");
		print_Hex((default_vref>>24)&0x7F);
		eye_mask_vol_lp3((default_vref>>24)&0x7F);
		scan_pas_wind = 0;

		for (vref = VREF_DDR_START; vref >= VREF_DDR_END; vref--)
		{
			dmc_print_str("\r\nVref: ");
			print_Hex(vref);

			/*set read vref*/
			reg_bit_set((DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0xF4), 24, 8, vref);

			/*delay at least 500ns*/
			wait_us(5);
			pass_flag = 0;
			first_pass = 0;
			last_pass = 0;
			chk_flag = 0;
			eye_mask_vol_flag(vref,&chk_flag);

			for(delay = delay_min; delay < delay_max; delay++)
			{

				reg_bit_set(reg, 31, 1, 0);
				reg_bit_set(reg_pos, 31, 1, 0);
				if(clk > QUAR_DELAY_FREQ)
				{
					reg_bit_set(reg, 0, 8, delay>>3);
					reg_bit_set(reg_pos, 0, 8, delay>>3);
					reg_bit_set(reg, 24, 3, delay&0x07);
					reg_bit_set(reg_pos, 24, 3, delay&0x07);
				}
				else
				{
					reg_bit_set(reg, 0, 8, delay);
					reg_bit_set(reg_pos, 0, 8, delay);
				}
				dmc_phy_soft_update();

				get_middle_vref_flag(vref,((default_vref>>24)&0x7F),middle_temp,delay,&chk_flag);

				check_scan_result(bist_addr,&chk_flag,delay,NULL,vref,delay_max);

			}
			check_scan_result_second(ps_start,ps_end,chk_flag,middle_temp,vref,delay_max);
		}
		print_scan_result(rank_num,i,SCAN_RD_ITEM_SHIFT);
		REG32(reg) = default_cfg_rd_dl_ds;
		REG32(reg_pos) = default_cfg_rd_dl_ds_pos;
		dmc_phy_soft_update();
		if(bit_mask_num !=0xFFFF)
		break;
	}

	REG32(DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0xF4) = default_vref;
	dmc_print_str("\r\nScan read end\r\n");

	return 0;
}

static int  scan_ca_lp3(int rank_num,u32 clk)
{
	u32 default_vref,chk_flag,vref_flag,pass_flag,max_delay,ps_start, ps_end;
	u32 regval, bist_addr, default_cfg_dl_ac0, default_cfg_dl_ac1 ,reg0 ,reg1,middle_temp;
	int i, j, vref, delay;
	u32 middle_temp_before_mod,middle_temp_mod;

	bist_addr = 0;
	if(rank_num == 1)
		bist_addr = dram_info.cs0_size;
	if(clk > QUAR_DELAY_FREQ)
		max_delay = MAX_DQ_DELAY*8;
	else
		max_delay = MAX_DQ_DELAY;

	regval = REG32(REG_AON_APB_RF_BASE+0x348);
	default_vref = (regval>>2)&0xFF;

	reg0 = DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0x64;
	reg1 = DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0x68;
	default_cfg_dl_ac0 = REG32(reg0);
	default_cfg_dl_ac1 = REG32(reg1);
	dmc_print_str("\r\nScan CA start\r\n");

	middle_temp = get_training_middle(default_cfg_dl_ac0,0,clk,pass_win_max_scan_tmp[2],&ps_start,&ps_end,1);
	middle_temp_mod = middle_temp % SCAN_RATE;
	middle_temp_before_mod = middle_temp;
	if(middle_temp_mod != 0){
		middle_temp = middle_temp - middle_temp_mod;
	}
	get_delay_min_max(rank_num,0,middle_temp,max_delay);

	dmc_print_str("mid: ");
	print_Hex(middle_temp);
	dmc_print_str("vref:");
	print_Hex(default_vref);
	eye_mask_vol_lp3(default_vref);
	scan_pas_wind = 0;

	for (vref = VREF_DDR_START; vref >= VREF_DDR_END_LP3; vref--)
	{
		dmc_print_str("\r\nVref: ");
		print_Hex(vref);

		/*set CA vref*/
		reg_bit_set((REG_AON_APB_RF_BASE+0x348), 2, 8, vref);

		/*delay at least 500ns?????*/
		wait_us(5);
		chk_flag = 0;
		first_pass = 0;
		last_pass = 0;
		eye_mask_vol_flag(vref,&chk_flag);

		for(delay = delay_min; delay < delay_max; delay++)
		{
			/*need reset sdram*/
			//sdram_init();

			reg_bit_set(reg0, 15, 1, 0);
			reg_bit_set(reg1, 15, 1, 0);
			reg_bit_set(reg0, 23, 1, 0);
			reg_bit_set(reg1, 23, 1, 0);
			reg_bit_set(reg0, 31, 1, 0);
			reg_bit_set(reg1, 31, 1, 0);

			if(clk > QUAR_DELAY_FREQ)
			{
				reg_bit_set(reg0, 0, 8, delay>>3);
				reg_bit_set(reg1, 0, 8, delay>>3);
				reg_bit_set(reg0, 24, 3, (delay&0x7));
				reg_bit_set(reg1, 24, 3, (delay&0x7));
			}
			else
			{
				reg_bit_set(reg0, 0, 7, delay);
				reg_bit_set(reg1, 0, 7, delay);
			}
			dmc_phy_soft_update();

			get_middle_vref_flag(vref,default_vref,middle_temp,delay,&chk_flag);

			check_scan_result(bist_addr,&chk_flag,delay,&i,vref,delay_max);
		}
		check_scan_result_second(ps_start,ps_end,chk_flag,middle_temp,vref,delay_max);
	}
	print_scan_result(rank_num,0,SCAN_CA_ITEM_SHIFT);
	REG32(reg0) = default_cfg_dl_ac0;
	REG32(reg1) = default_cfg_dl_ac1;
	dmc_phy_soft_update();
	reg_bit_set((REG_AON_APB_RF_BASE+0x348), 2, 8, default_vref);
	dmc_print_str("\r\nScan CA end\r\n");

	return 0;
}

static u32 get_wr_ca_vol_shift_lp4(u32 deault_vref,u32 vol_step)
{
	u32 tmp;

	tmp = vol_step;
	if(deault_vref <0x40)
	{
		/*default vref in range 0*/
		if(tmp > 0x32)
			tmp = 0x54 + tmp - 0x32;
	}
	else
	{
		/*default vref in range 1*/
		if(tmp > 0x72)
			tmp = 0x72;
		if(tmp < 0x40)
			tmp = 0x1D -(0x40 - tmp);
	}
	return tmp;
}

static void get_wr_ca_eye_mask_vol_lp4(u32 tmp_default_vref)
{
	u32 vref;

	if(dram_info.dram_type == DRAM_LP4)
		vref = tmp_default_vref + LP4_WR_EYE_MASK_VOL_STEP;
	else
		vref = tmp_default_vref + LP4X_WR_EYE_MASK_VOL_STEP;
	eye_mask_vol_high = get_wr_ca_vol_shift_lp4(tmp_default_vref,vref);

	if(dram_info.dram_type == DRAM_LP4)
		vref = tmp_default_vref - LP4_WR_EYE_MASK_VOL_STEP;
	else
		vref = tmp_default_vref - LP4X_WR_EYE_MASK_VOL_STEP;
	if(vref < 0)
		vref = 0;
	eye_mask_vol_low = get_wr_ca_vol_shift_lp4(tmp_default_vref,vref);

}

static int  scan_write_lp4(int rank_num,u32 clk)
{
	u32  default_vref,chk_flag,tmp_default_vref;
	u32 regval, bist_addr, default_cfg_dl_ds;
	int i, j, k, vref, delay, max_delay;
	u32 middle_temp,reg,reg_diff, ps_start, ps_end, tmp,reg_diff_val;
	u32 middle_temp_mod,middle_temp_before_mod;
	u32 scan_cycle,scan_2cycle;

	default_vref = 0;
	if(clk > QUAR_DELAY_FREQ)
		max_delay = MAX_DQ_DELAY*8;
	else
		max_delay = MAX_DQ_DELAY;
	dmc_mrr(DRAM_MR_14, DRAM_CS_ALL, &default_vref);
	tmp_default_vref = default_vref;

	dmc_print_str("\r\nScan write start\r\n");

	for(i = 0;i < DDR_CHANNEL_NUM; i++)
	{
		perbit_channel_byte_change(&i,&k);

		bist_addr = get_bist_address_lp4(i, rank_num);

		/*two bytes for each channel*/
		for(j = 0;j < DDR_BYTE_NUM; j++)
		{
			if(bit_mask_num !=0xFFFF)
			{
				j = k%2;
			}
			dmc_print_str("\r\nWR PHY");
			print_Dec(i);
			dmc_print_str("BYTE");
			print_Dec(j);
			dmc_print_str("bist addr:");
			print_Hex(bist_addr);
			dmc_print_str("cfg_dll_ds_dl:");

			reg = DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0x6c + 0x20*((i*2) +j);
			scan_cycle = reg_bit_get(reg, 15, 1);
			scan_2cycle = reg_bit_get(reg, 23, 1);
			reg_diff = DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0x7c + 0x20*((i*2) +j);
			default_cfg_dl_ds = REG32(reg);
			reg_diff_val = REG32(reg_diff);
			print_Hex(default_cfg_dl_ds);
#if 1
			middle_temp = default_cfg_dl_ds & 0xff;
			/*1: cs1> cs0 ; 0:cs0>cs1*/
			if(reg_diff_val&0x01)
			{
				/*cs1*/
				if(rank_num == 1)
				{
					middle_temp += ((reg_diff_val >>1)&0x7F);
				}
			}
			else
			{
				/*cs0*/
				if(rank_num == 0)
				{
					middle_temp += ((reg_diff_val >>1)&0x7F);
				}
			}
			middle_temp += default_cfg_dl_ds & (~0xff);
			if((default_cfg_dl_ds & 0xff) < 0x20){
				middle_temp += 0x40;//middle also need fit scan_cycle & scan_2cycle onfig
			}
#endif
			middle_temp = get_training_middle(middle_temp,(i*2+j),clk,
				(pass_win_max_scan_tmp[i]>> (8*rank_num)),&ps_start,&ps_end,0);
		
		middle_temp_mod = middle_temp % SCAN_RATE;
		middle_temp_before_mod = middle_temp;
		if(middle_temp_mod != 0){
			middle_temp = middle_temp - middle_temp_mod;
		}

			write_flag = 0xff;
			get_delay_min_max(rank_num,(2*i + j),middle_temp,max_delay);
			write_flag = 0;
			dmc_print_str("delay_min: ");
			print_Hex(delay_min);
			dmc_print_str("delay_max: ");
			print_Hex(delay_max);

			dmc_print_str("mid:");
			print_Hex(middle_temp);
		dmc_print_str("mid before mod: ");
		print_Hex(middle_temp_before_mod);

			dmc_print_str("vref:");
			tmp_default_vref = (default_vref>>(i*8) & 0x7F);
			print_Hex(tmp_default_vref);

			get_wr_ca_eye_mask_vol_lp4(tmp_default_vref);

			scan_pas_wind = 0;

			for (vref = VREF_DDR_START; vref >= VREF_DDR_END; vref--)
			{
				/*vref 0~0x32;0x40~0x72;0x1E~0x32 and 0x40 ~0x54 duped*/
				if(tmp_default_vref <0x40)
				{
					/*default vref in range 0, use 0x1E~0x32 instead of 0x40 ~0x54*/
					if(vref == 0x54)
						vref = 0x32;
				}
				else
				{
					/*default vref in range 1, use 0x40 ~0x54 instead of 0x1E~0x32 */
					if(vref == 0x3F)
						vref = 0x1D;
				}
				dmc_print_str("\r\nVref: ");
				print_Hex(vref);

				reg_bit_set(DMC_CTL0_(0x0100),20,4,(1<<i));
				/*set DQ vref*/
				dmc_mrw(DRAM_MR_14, DRAM_CS_ALL, vref);
				/*delay at least 500ns for vref update*/
				wait_us(2);
				reg_bit_set(DMC_CTL0_(0x0100),20,4,3);
				//dmc_mrr(DRAM_MR_14, DRAM_CS_ALL, &regval);
				//print_Hex(regval);
				chk_flag = 0;
				first_pass = 0;
				last_pass = 0;

				eye_mask_vol_flag(vref,&chk_flag);
				
//delay_min = 0;
//delay_max = 512;
				for(delay = delay_min; delay < delay_max; delay = delay + SCAN_RATE)
				{
					/*set delay*/
					/*if(clk <=384)
						reg_bit_set(reg, 15, 1, 1);
					else
						reg_bit_set(reg, 15, 1, 0);
					reg_bit_set(reg, 23, 1, 0);*/
				
					if((default_cfg_dl_ds & 0xff) < 0x20){
						if(scan_cycle == 1 && scan_2cycle == 1)
						{
							reg_bit_set(reg, 15, 1, 0);
							reg_bit_set(reg, 23, 1, 1);
						}
						else if(scan_cycle == 0 && scan_2cycle == 1)
						{
							reg_bit_set(reg, 15, 1, 1);
							reg_bit_set(reg, 23, 1, 0);
						}
						else if(scan_cycle == 1 && scan_2cycle == 0)
						{
							reg_bit_set(reg, 15, 1, 0);
							reg_bit_set(reg, 23, 1, 0);
						}
					}
					reg_bit_set(reg, 31, 1, 0);
					reg_bit_set(reg_diff, 1, 7, 0);
				
					if(clk > QUAR_DELAY_FREQ)
					{
						reg_bit_set(reg, 0, 8, (delay >> 3));
						reg_bit_set(reg, 24, 3, (delay&0x7));
					}
					else
						reg_bit_set(reg, 0, 8, delay);
					dmc_phy_soft_update();

					get_middle_vref_flag(vref,tmp_default_vref,middle_temp,delay,&chk_flag);

					check_scan_result(bist_addr,&chk_flag,delay,NULL,vref,delay_max);
				}
				check_scan_result_second(ps_start,ps_end,chk_flag,middle_temp,vref,delay_max);
			}
			print_scan_result(rank_num,(i*2 + j),SCAN_WR_ITEM_SHIFT);
			REG32(reg) = default_cfg_dl_ds;
			REG32(reg_diff) = reg_diff_val;
			dmc_phy_soft_update();
			if(bit_mask_num !=0xFFFF)
				break;
		}

		reg_bit_set(DMC_CTL0_(0x0100),20,4,(1<<i));
		dmc_mrw(DRAM_MR_14, DRAM_CS_ALL, (default_vref>>(i*8))&0x7F);
		/*delay at least 500ns for vref update*/
		wait_us(1);
		reg_bit_set(DMC_CTL0_(0x0100),20,4,3);
		if(bit_mask_num !=0xFFFF)
			break;
	}

	dmc_print_str("\r\nScan write end\r\n");
	/*delay at least 500ns for vref update*/
	wait_us(1);
	return 0;
}

static int  scan_read_lp4(int rank_num,u32 clk,u32 cmos)
{
	u32 default_vref,chk_flag;
	u32 regval, bist_addr, default_cfg_rd_dl_ds,default_cfg_rd_dl_ds_pos;
	int i, j, k, vref, delay;
	u32 middle_temp,reg,reg_pos,ps_start,ps_end,tmp,max_delay;
	u32 middle_temp_before_mod,middle_temp_mod;

//	if((clk >= 1200) && (cmos == 1))
//		return 0;

	if(clk > QUAR_DELAY_FREQ)
		max_delay = MAX_DQ_DELAY*8;
	else
		max_delay = MAX_DQ_DELAY;

	default_vref = REG32(DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0xF4);
	

	dmc_print_str("\r\nScan read start\r\n");
	if(interleave_en == INTERLEAVE_MODE)
		dmc_print_str("interleave mode\r\n");
	else
		dmc_print_str("non interleave mode\r\n");

	set_read_cmos_diff_mode(cmos);

	for(i = 0;i < DDR_CHANNEL_NUM; i++)
	{
		perbit_channel_byte_change(&i,&k);

		bist_addr = get_bist_address_lp4(i, rank_num);

		/*two bytes for each channel*/
		for(j = 0;j < DDR_BYTE_NUM; j++)
		{
			if(bit_mask_num !=0xFFFF)
			{
				j = k%2;
			}
			dmc_print_str("\r\nread PHY");
			print_Dec(i);
			dmc_print_str("  byte");
			print_Dec(j);
			dmc_print_str("bist addr:");
			print_Hex(bist_addr);
			dmc_print_str("cfg_dll_ds_dl:");

			reg = DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0x70 + 4 + 0x20*(i*2+j);
			reg_pos = DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0x70 + 0x20*(i*2+j);

			default_cfg_rd_dl_ds = REG32(reg);
			default_cfg_rd_dl_ds_pos = REG32(reg_pos);

			print_Hex(default_cfg_rd_dl_ds_pos);
			print_Hex(default_cfg_rd_dl_ds);

			middle_temp = get_training_middle(default_cfg_rd_dl_ds,(i*2+j),clk,
				(pass_win_max_scan_tmp[i]>>16),&ps_start,&ps_end,0);
		
		middle_temp_mod = middle_temp % SCAN_RATE;
		middle_temp_before_mod = middle_temp;
		if(middle_temp_mod != 0){
			middle_temp = middle_temp - middle_temp_mod;
		}

			get_delay_min_max(rank_num,(2*i + j),middle_temp,max_delay);
			dmc_print_str("delay_min: ");
			print_Hex(delay_min);
			dmc_print_str("delay_max: ");
			print_Hex(delay_max);

			dmc_print_str("mid:");
			print_Hex(middle_temp);
			dmc_print_str("mid before mod: ");
			print_Hex(middle_temp_before_mod);

			dmc_print_str("vref:");
			tmp = (default_vref >> 24) & 0x7F;
			print_Hex(tmp);

			if(dram_info.dram_type == DRAM_LP4)
			{
				eye_mask_vol_high= tmp + LP4_RD_EYE_MASK_VOL_STEP;
				eye_mask_vol_low= tmp - LP4_RD_EYE_MASK_VOL_STEP;
			}
			else
			{
				eye_mask_vol_high = tmp + LP4X_RD_EYE_MASK_VOL_STEP;
				eye_mask_vol_low = tmp - LP4X_RD_EYE_MASK_VOL_STEP;
			}
			if(eye_mask_vol_high > VREF_PHY_START)
				eye_mask_vol_high = VREF_PHY_START;
			if(eye_mask_vol_low < VREF_PHY_END)
				eye_mask_vol_low = VREF_PHY_END;

			scan_pas_wind = 0;

			for (vref = VREF_PHY_START; vref >= VREF_PHY_END; vref--)
			{
				dmc_print_str("\r\nVref: ");
				print_Hex(vref);

				/*set read vref*/
				reg_bit_set((DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT+0xF4), 24, 7, vref);

				/*delay at least 500ns*/
				wait_us(2);

				chk_flag = 0;
				first_pass = 0;
				last_pass = 0;

				eye_mask_vol_flag(vref,&chk_flag);

//delay_min = 0;
//delay_max =1024;
scan_debug = i;
				for(delay = delay_min; delay < delay_max; delay = delay + SCAN_RATE)
				{
					/*set delay*/
					reg_bit_set(reg, 31, 1, 0);
					reg_bit_set(reg_pos, 31, 1, 0);
					if(clk > QUAR_DELAY_FREQ)
					{
						reg_bit_set(reg, 0, 8, (delay >> 3));
						reg_bit_set(reg, 24, 3, (delay&0x7));
						reg_bit_set(reg_pos, 0, 8, (delay >> 3));
						reg_bit_set(reg_pos, 24, 3, (delay&0x7));
					}
					else
					{
						reg_bit_set(reg, 0, 8, delay);
						reg_bit_set(reg_pos, 0, 8, delay);
					}
					dmc_phy_soft_update();

					get_middle_vref_flag(vref,((default_vref>>24) & 0x7F),middle_temp,delay,&chk_flag);

					check_scan_result(bist_addr,&chk_flag,delay,NULL,vref,delay_max);
				}
				check_scan_result_second(ps_start,ps_end,chk_flag,middle_temp,vref,delay_max);
			}
			print_scan_result(rank_num,(i*2 + j),SCAN_RD_ITEM_SHIFT);
			REG32(reg) = default_cfg_rd_dl_ds;
			REG32(reg_pos) = default_cfg_rd_dl_ds_pos;
			dmc_phy_soft_update();
			if(bit_mask_num !=0xFFFF)
				break;
		}
		if(bit_mask_num !=0xFFFF)
			break;
	}
	REG32(DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0xF4) = default_vref;

	dmc_print_str("\r\nScan read end\r\n");
	return 0;
}

static int  scan_ca_lp4(int rank_num,u32 clk)
{
	u32 default_vref,chk_flag;
	u32 regval, bist_addr, default_cfg_dl_ac;
	int i, j,vref, delay;
	u32 middle_temp,reg,ps_start,ps_end,tmp,max_delay;
	u32 middle_temp_before_mod,middle_temp_mod;

	default_vref = 0;
	if(clk > QUAR_DELAY_FREQ)
		max_delay = MAX_DQ_DELAY*8;
	else
		max_delay = MAX_DQ_DELAY;

	dmc_mrr(DRAM_MR_12, DRAM_CS_ALL, &default_vref);

	dmc_print_str("\r\nScan CA start\r\n");

	
/*reg_bit_set(DMC_CTL0_(0x010c),12,1,0);
wait_us(2);
dmc_mrw(DRAM_MR_13, DRAM_CS_ALL, 0x8);
wait_us(2);
reg_bit_set(DMC_CTL0_(0x010c),12,1,1);
*/



	for(i = 0;i < DDR_CHANNEL_NUM; i++)
	{
		bist_addr = get_bist_address_lp4(i, rank_num);

		/*two bytes for each channel*/
		reg = DMC_PHY_REG_BASE_ADDR  + DDR_FREQ_SHIFT + 0x64 + (i*4);
		default_cfg_dl_ac = REG32(reg);

		dmc_print_str("\r\nCA PHY");
		print_Dec(i);
		dmc_print_str("bist addr:");
		print_Hex(bist_addr);
		dmc_print_str("cfg_dll_ds_dl:");
		print_Hex(default_cfg_dl_ac);

		middle_temp = get_training_middle(default_cfg_dl_ac,i,clk,
			(pass_win_max_scan_tmp[i]>>24),&ps_start,&ps_end,1);
		middle_temp_mod = middle_temp % SCAN_RATE;
		middle_temp_before_mod = middle_temp;
		if(middle_temp_mod != 0){
			middle_temp = middle_temp - middle_temp_mod;
		}

		if((rank_num == 0) && (i == 0))
		{
//			scan_ui = 0x20;//l5pro less than 0x40,so scan ui = 0x20
			delay_min = 0;
			delay_max = middle_temp + scan_ui*2;
			if(delay_max > max_delay)
				delay_max = max_delay;
		}
			dmc_print_str("delay_min: ");
			print_Hex(delay_min);
			dmc_print_str("delay_max: ");
			print_Hex(delay_max);

		dmc_print_str("mid: ");
		print_Hex(middle_temp);
		dmc_print_str("mid before mod: ");
		print_Hex(middle_temp_before_mod);

		dmc_print_str("vref:");
		print_Hex(((default_vref>>(i*8)) & 0x7F));
		get_wr_ca_eye_mask_vol_lp4(((default_vref>>(i*8)) & 0x7F));
		scan_pas_wind = 0;

		for (vref = VREF_DDR_START; vref >= VREF_DDR_END; vref--)
		{
			REG32(reg) = default_cfg_dl_ac;
			dmc_phy_soft_update();

			/*vref 0~0x32;0x40~0x72,0x1D~0x32 is duplicated*/
			if(vref == 0x3F)
				vref = 0x1D;

			dmc_print_str("\r\nVref: ");
			print_Hex(vref);

			/*set CA vref*/
			reg_bit_set(DMC_CTL0_(0x0100),20,4,(1<<i));
			dmc_mrw(DRAM_MR_12, DRAM_CS_ALL, vref);
			/*delay at least 500ns for vref update*/
			wait_us(2);
			reg_bit_set(DMC_CTL0_(0x0100),20,4,3);

			//dmc_mrr(DRAM_MR_12, DRAM_CS_ALL, &regval);
			//print_Hex(regval);

			chk_flag = 0;
			first_pass = 0;
			last_pass = 0;
			eye_mask_vol_flag(vref,&chk_flag);

//delay_min = 0;
//delay_max = 512;
			for(delay = delay_min; delay < delay_max; delay = delay + SCAN_RATE)
			{
				/*set delay*/
				reg_bit_set(reg, 15, 1, 0);
				reg_bit_set(reg, 23, 1, 0);
				reg_bit_set(reg, 31, 1, 0);
				if(clk > QUAR_DELAY_FREQ)
				{
					reg_bit_set(reg, 0, 8, (delay >> 3));
					reg_bit_set(reg, 24, 3, (delay&0x7));
				}
				else
					reg_bit_set(reg, 0, 8, delay);
				dmc_phy_soft_update();

				get_middle_vref_flag(vref,((default_vref>>(i*8)) & 0x7F),middle_temp,delay,&chk_flag);

				check_scan_result(bist_addr,&chk_flag,delay,&i,vref,delay_max);
			}
			check_scan_result_second(ps_start,ps_end,chk_flag,middle_temp,vref,delay_max);
		}
		print_scan_result(rank_num,i,SCAN_CA_ITEM_SHIFT);
		REG32(reg) = default_cfg_dl_ac;
		dmc_phy_soft_update();

		reg_bit_set(DMC_CTL0_(0x0100),20,4,(1<<i));
		dmc_mrw(DRAM_MR_12, DRAM_CS_ALL, (default_vref>>(i*8))&0x7F);
		wait_us(1);
		reg_bit_set(DMC_CTL0_(0x0100),20,4,3);
	}
	dmc_print_str("\r\nScan CA end\r\n");
	return 0;
}

void print_final_result()
{
	int i,tmp,j;
	if(scan_final_result[0] || scan_final_result[1])
	{
		dmc_print_str("\r\nScan result:\r\n ERROR:");
		for(i = 0; i < 2; i++)
		{
			if(scan_final_result[i])
			{
				dmc_print_str(" cs");
				print_Dec(i);
				for(j = 0; j < 10; j++)
				{
					tmp = (scan_final_result[i] >> j) & 1;
					if(tmp == 1)
					{
						if(j < SCAN_WR_ITEM_SHIFT)
						{
							dmc_print_str(" read byte ");
							print_Dec(j);
						}
						else if(j < SCAN_CA_ITEM_SHIFT)
						{
							dmc_print_str(" write byte ");
							print_Dec((j -4));
						}
						else
						{
							dmc_print_str(" CA ");
							print_Dec((j -8));
						}
						dmc_print_str("fail ");
					}
				}
			}
		}
	}
	else
	{
		dmc_print_str("\r\nScan result:  SCAN ALL PASS");
	}
}

static void scan_perbit(int ddr_clk,int scan_item)
{
#ifdef PERBIT_SCAN
	int j;

	dmc_print_str("\r\nperbit start\r\n");
	for(j = 0;j < 32;j++)
	{
		dmc_print_str(string_item[scan_item]);
		dmc_print_str(" perbit:");
		print_Dec(j);
		bit_mask_num = (1<<j);
		if(dram_info.dram_type > DRAM_LP3)
		{
			if(scan_item == SCAN_READ)
				scan_read_lp4(0,ddr_clk,2);//diff mode
			else
				scan_write_lp4(0,ddr_clk);

		}
		else
		{
			if(scan_item == SCAN_READ)
				scan_read_lp3(0,ddr_clk,2);
			else
				scan_write_lp3(0,ddr_clk);
		}
	}
	dmc_print_str("\r\nperbit end\r\n");
	bit_mask_num = 0xFFFF;
#endif
}
void lp3_dqs_set()
{
	__raw_writel(0x310016E8,0x18181818);
	__raw_writel(0x310016EC,0x18181818);
	__raw_writel(0x31001728,0x18181818);
	__raw_writel(0x3100172C,0x18181818);
	__raw_writel(0x31001768,0x18181818);
	__raw_writel(0x3100176C,0x18181818);
	__raw_writel(0x310017A8,0x18181818);
	__raw_writel(0x310017AC,0x18181818);
	__raw_writel(0x310017C8,0x18181818);
	__raw_writel(0x310017CC,0x18181818);
	__raw_writel(0x310017DC,0x18181818);
	__raw_writel(0x310017E0,0x18181818);
	__raw_writel(0x310017F0,0x18181818);
	__raw_writel(0x310017F4,0x18181818);
	__raw_writel(0x31001804,0x18181818);
	__raw_writel(0x31001808,0x18181818);
}

void ddr_scan_offline_r2p0(u32 ddr_clk)
{
	int i, j, k, cs_num;
	u32 vddcore_step[VDDCORE_STEP_CNT]={700, };
	u32 vddmem_step[VDDCORE_STEP_CNT]={0 };
	VOL_SET_FLAG vol_flag;

#ifdef SCAN_USB_LOG_ENABLE
	fdl_channel = FDL_ChannelGet();

	if (BOOT_FLAG_USB == FDL_GetBootMode())
		usb_init(USB_REG_BASE);

	for (;;)
	{
		char ch = fdl_channel->GetChar(fdl_channel);
		if (0x7C == ch)
			break;
	}
#endif
	pass_win_max_scan_tmp[0] = pass_win_max_scan[0];
	pass_win_max_scan_tmp[1] = pass_win_max_scan[1];
	pass_win_max_scan_tmp[2] = pass_win_max_scan[2];//lp3 ca
	dmc_print_str("\r\nddr scan start\r\n");

	dmc_reg_dump();

	cs_num = dram_info.cs_num;
	dmc_freq_sel_search(ddr_clk, &freq_fn);
	dmc_print_str("\r\nDDR freq:");
	print_Dec(ddr_clk);

    /*first change vdd core*/
	//get_scan_ddr_id();
	scan_pre_set(ddr_clk);
#ifdef VDD_CORE_MEM_ADJ
	vol_flag = VDD_CORE_SET;
	for(j = 0,k = 1; (j < VDDCORE_STEP_CNT)||(k < VDDMEM_STEP_CNT);)
	{
		/*run vdd_core change case*/
		if(vol_flag == VDD_CORE_SET)
		{
			if(j!=0)
			regulator_set_voltage("vddcore",vddcore_step[j]);
			j++;
		}
		/*run vdd_mem change case*/
		if(vol_flag == VDD_MEM_SET)
		{
			regulator_set_voltage("vddmem",vddmem_step[k]);
			k++;
		}
#endif
		if(dram_info.dram_type == DRAM_LP3)
		{
			lp3_dqs_set();
			for(i = 0; i < cs_num; i++)
			{
				dmc_print_str("\r\nscan cs:");
				print_Dec(i);
				/*use default mode*/
				scan_read_lp3(i,ddr_clk,2);
				//scan_read_lp3(i,ddr_clk,0);
				if(i == 0)
					scan_perbit(ddr_clk,SCAN_READ);
			}
			for(i = 0; i < cs_num; i++)
			{
				dmc_print_str("\r\nscan cs:");
				print_Dec(i);
				scan_write_lp3(i,ddr_clk);
				if(i == 0)
					scan_perbit(ddr_clk,SCAN_WRITE);
			}
			for(i = 0; i < cs_num; i++)
			{
				dmc_print_str("\r\nscan cs:");
				print_Dec(i);
				scan_ca_lp3(i,ddr_clk);
			}
		}
		else
		{
			first_init = 2;
			//scan_ca_lp4(0,ddr_clk);
			for(i = 0; i < cs_num; i++)
			{
				dmc_print_str("\r\nscan cs:");
				print_Dec(i);

				/*3 -> use default mode*/
				scan_read_lp4(i,ddr_clk,2);
				//scan_read_lp4(0,ddr_clk,0);
				//scan_read_lp4(0,ddr_clk,1);
				/*use non interleave mode*/
				/*
				lp4_interleave_en(INTERLEAVE_MODE);
				scan_read_lp4(0,ddr_clk,1);
				scan_read_lp4(0,ddr_clk,0);
				lp4_interleave_en(NON_INTERLEAVE_MODE);
				*/
				if(i == 0)
					scan_perbit(ddr_clk,SCAN_READ);
			}
			for(i = 0; i < cs_num; i++)
			{
				dmc_print_str("\r\nscan cs:");
				print_Dec(i);
				scan_write_lp4(i,ddr_clk);
				if(i == 0)
					scan_perbit(ddr_clk,SCAN_WRITE);
			}
#ifdef SCAN_LP4_CA_EANBLE
			/*only scan rank 0*/
//scan_ca_pre_set(0,0x72);
			scan_ca_lp4(0,ddr_clk);
			//scan_ca_lp4(1,ddr_clk);
#endif
		}
#ifdef VDD_CORE_MEM_ADJ
		/*restore to default vol*/
		if(j == VDDCORE_STEP_CNT)
		{
			regulator_set_voltage("vddcore",vddcore_step[0]);
			vol_flag = VDD_MEM_SET;
		}
		if(k == VDDCORE_STEP_CNT)
		{
			regulator_set_voltage("vddmem",vddmem_step[0]);
		}
	}
#endif
	print_final_result();
	dmc_print_str("\r\nDDR scan end\r\n");

	while(1);
}
