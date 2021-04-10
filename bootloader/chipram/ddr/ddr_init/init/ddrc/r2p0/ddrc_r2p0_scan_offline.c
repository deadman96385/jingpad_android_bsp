#include "ddrc_common.h"
#include "ddrc_r2p0_scan_offline.h"
#include "ddrc_init.h"
#include "dram_test.h"
#include <fdl_channel.h>
#include <asm/arch/sprd_reg.h>

#define DDR_CHANNEL_NUM 2
#define DMC_LP4_MR3 0x33

//static u64 ddr_size;
//static u32 mem_drv_stren_lp3[] = {DRV_34_OHM, DRV_40_OHM, DRV_48_OHM};
//????
//static u32 dmc_drv_stren_lp3[] = {DRV_34_OHM, DRV_40_OHM, DRV_48_OHM};
//static u32 dmc_drv_stren_lp4[] = {DRV_40_OHM, DRV_48_OHM, DRV_60_OHM};

u32 pass_win_max_scan[DDR_CHANNEL_NUM+1] = {0,0};

extern DRAM_INFO_T dram_info;
extern u32 user_mode_pattern[];

static u32 freq_fn;
#ifdef SCAN_USB_LOG_ENABLE
#define dmc_print_str(x) dmc_print_usb(x)
#define print_Hex(x) print_Hex_Usb(x)
#define print_Dec(x) print_Dec_Usb(x)
struct FDL_ChannelHandler *fdl_channel;

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
	}while(temp >0);
	for(i = num-1; i >=0; i--)
	{
		temp = (val % 10) + 0x30;
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
	u32 val=0 ,i;
	volatile u32 offset = bist_chn_num*0x4000;
	//bist clear
	bist_clear(bist_chn_num);
	/*clear to 0*/
	__raw_writel(BIST_BASE_ADDR+0x00+offset,0);
	reg_bit_set(BIST_BASE_ADDR+0x00+offset, 0, 1, 0x1);

	switch(bist_data_mode)
	{
	case LFSR_DATA_PATTERN:
		__raw_writel(BIST_BASE_ADDR+0x00+offset, 5, 2, LFSR_DATA_PATTERN);
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
		__raw_writel(BIST_BASE_ADDR+0x28+offset,0x00550055);
		__raw_writel(BIST_BASE_ADDR+0x2c+offset,0x00550055);
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
	reg_bit_set(BIST_BASE_ADDR+0x00+offset, 24, 2, 3);
	reg_bit_set(BIST_BASE_ADDR+0x00+offset,28,1,(dram_info.dram_type==DRAM_LP3)?0x1:0x0);

	__raw_writel(BIST_BASE_ADDR+0x04+offset,bist_size);
	__raw_writel(BIST_BASE_ADDR+0x08+offset,bist_start_addr);

}

static u32 scan_bist_patten_test(u32 bist_addr)
{
	u32 i,ret= 0;
	for(i = 0;i <= LFSR_DATA_PATTERN;i++)
	{
		bist_init_scan(0,bist_addr,i,BIST_ALLWRC,SCAN_BIST_SIZE);
		bist_test_entry_chn(0,&ret);
		if(ret!=0)
		{
			return ret;
		}
	}
	return ret;
}

static void print_items(u32* item,u32 num)
{
	int i;

	dmc_print_str("\r\n0x0");
	for(i = 0 ;i < num; i++)
	{
		dmc_print_str("\t");
		print_Hex(item[i]);
	}
	dmc_print_str("\t");
}
static void scan_pre_set(void)
{
	u32 regval;
	u64 size;

	//ddr_size = dram_info.cs0_size + dram_info.cs1_size;

	/*enable reg write*/
	__raw_writel(DMC_CTL0_(0x009c),0xdeadbeef);

	/*disable period cpst and wbuf merge*/
	reg_bit_set(DMC_CTL0_(0x0144), 16,2,0x0);
	reg_bit_set(DMC_CTL0_(0x0114), 24,1,0x0);//disable mr4
	reg_bit_set(DMC_CTL0_(0x0118), 24,1,0x0);//disable auto zqc
	reg_bit_set(DMC_CTL0_(0x0124), 2,1,0x0);//drf_auto_self_ref_en
	reg_bit_set(DMC_CTL0_(0x010c), 12,1,0x0);//drf_auto_self_ref_en

	if(dram_info.dram_type > DRAM_LP3)
	{
		reg_bit_set(DMC_CTL0_(0x0148), 0,14,0);//ch0 linear base
		reg_bit_set(DMC_CTL0_(0x0148), 16,14,0);//ch1 linear base
		reg_bit_set(DMC_CTL0_(0x0150), 0,14,0);//interleave base
		reg_bit_set(DMC_CTL0_(0x0150), 16,14,0);//interleave offset
		dmc_print_str("\r\n***0x44444444***");
	}
	else
		dmc_print_str("\r\n***0x33333333***");
}

static void scan_ca_pre_set(u32 i,u32 vref)
{
	u32 regval;
	__raw_writel(DMC_CTL0_(0x009c),0xdeadbeef);

	reg_bit_set(DMC_CTL0_(0x0144), 16,2,0x0);
	reg_bit_set(DMC_CTL0_(0x0114), 24,1,0x0);//disable mr4
	reg_bit_set(DMC_CTL0_(0x0118), 24,1,0x0);//disable auto zqc
	reg_bit_set(DMC_CTL0_(0x0124), 2,1,0x0);//drf_auto_self_ref_en
	reg_bit_set(DMC_CTL0_(0x010c), 12,1,0x0);//drf_auto_self_ref_en

	if(dram_info.dram_type > DRAM_LP3)
	{
		reg_bit_set(DMC_CTL0_(0x0148), 0,14,0);//ch0 linear base
		reg_bit_set(DMC_CTL0_(0x0148), 16,14,0);//ch1 linear base
		reg_bit_set(DMC_CTL0_(0x0150), 0,14,0);//interleave base
		reg_bit_set(DMC_CTL0_(0x0150), 16,14,0);//interleave offset
		/*set CA vref*/
		reg_bit_set(DMC_CTL0_(0x0100),20,4,(1<<i));
		dmc_mrw(DRAM_MR_12, DRAM_CS_ALL, vref);
		/*delay at least 500ns for vref update*/
		wait_us(5);
		reg_bit_set(DMC_CTL0_(0x0100),20,4,3);
	}
	else
	{
		reg_bit_set((REG_AON_APB_RF_BASE+0x348), 2, 8, vref);
		wait_us(2);
	}

}
static void get_vref_max_min(int* v_max,int* v_min,u32 vref)
{
	int vref_max, vref_min;

	/*vref 0~0x1D;0x40~0x72*/
	if(vref > 0x3F)
	{
		vref_max = vref + CUST_VREF_SHIFT;
		if(vref_max > 0x72)
			vref_max = 0x72;
		vref_min = vref - CUST_VREF_SHIFT;
		if(vref_min < 0x40)
			vref_min = 0x1D + 1 - (0x40 - vref_min);
	}
	else
	{
		vref_max = vref + CUST_VREF_SHIFT;
		if(vref_max > 0x1D)
			vref_max = 0x40 + (vref_max - 0x1D);
		vref_min = vref - CUST_VREF_SHIFT;
		if(vref_min < 0)
			vref_min = 0;
	}
	*v_max = vref_max;
	*v_min = vref_min;
}
static int scan_write(int rank_num)
{
	u32 regval, bist_addr, default_cfg_dl_ds;
	int i, j, delay, vref_min, vref ;
	u32 reg ,item[5] ,default_vref ,vref_max ,drv;

	dmc_print_str("\r\n0x434f4e54");

	default_vref = 0;
	bist_addr = 0;

	if(dram_info.dram_type > DRAM_LP3)
	{
		dmc_mrr(DRAM_MR_14, rank_num, &default_vref);
		if(rank_num == 1)
			bist_addr = dram_info.cs0_size;
		/*use channel 0 vref*/
		get_vref_max_min(&vref_max,&vref_min,(default_vref>>(0*8))&0x7F);
	}
	else
	{
		regval = REG32(REG_AON_APB_RF_BASE+0x348);
		default_vref = (regval>>2)&0xFF;

		vref_max = default_vref + CUST_VREF_SHIFT;
		if(vref_max > VREF_PHY_START)
			vref_max = VREF_PHY_START;
		vref_min = default_vref - CUST_VREF_SHIFT;
		if(vref_min < VREF_PHY_END)
			vref_min = VREF_PHY_END;
	}
	if(rank_num == 0)
	{
		dmc_print_str("\r\n###0x77aa77aa");
		print_Hex(vref_min);
		print_Hex(vref_max);
		dmc_print_str("###");
	}
	for (drv=DS_34; drv>DS_60; drv--)
	{
		ddrc_dq_ds_set(drv);

		for(i = 0;i < DDR_CHANNEL_NUM; i++)
		{
			/*two bytes for each channel*/
			for(j = 0;j < DDR_BYTE_NUM; j++)
			{
				reg = DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0x6c + 0x20*(i*2 +j);
				default_cfg_dl_ds = REG32(reg);

				for (vref = vref_max; vref >= vref_min; vref--)
				{
					/*vref 0~0x32;0x40~0x72,0x1E~0x3F is duplicated*/
					if(dram_info.dram_type > DRAM_LP3)
					{
						if((vref == 0x3F))
							vref = 0x1D;
						reg_bit_set(DMC_CTL0_(0x0100),20,4,(1<<i));
						/*set DQ vref*/
						dmc_mrw(DRAM_MR_14, DRAM_CS_ALL, vref);
						reg_bit_set(DMC_CTL0_(0x0100),20,4,3);
					}
					else
					{
						/*set DQ vref*/
						reg_bit_set((REG_AON_APB_RF_BASE+0x348), 2, 8, vref);
					}
					/*delay at least 500ns for vref update*/
					wait_us(2);

					for(delay = 0; delay < MAX_DQ_DELAY; delay++)
					{
						/*byte*/
						item[0] = SCAN_ROW1_SYMBOL | (SCAN_ITEM_BYTE<<SCAN_ITEM_OFFSET) | j;
						/*drv*/
						item[1] = SCAN_ROW2_SYMBOL | (SCAN_ITEM_DRV<<SCAN_ITEM_OFFSET) | (240/drv);
						/*cs*/
						item[2] = SCAN_ROW3_SYMBOL | (SCAN_ITEM_PHY<<SCAN_ITEM_OFFSET) | i;
						/*vref*/
						item[3] = SCAN_ROW4_SYMBOL | (SCAN_ITEM_VREF_WR << SCAN_ITEM_OFFSET)|(vref);
						/*wr dl*/
						item[4] = SCAN_COLUMN1_SYMBOL | (SCAN_ITEM_WR_DL<<SCAN_ITEM_OFFSET) | delay;
						print_items(item,5);
						/*result*/
						/*set delay*/
						if(freq_fn <=1) //freq < 384 bit 7 need add 1
							reg_bit_set(reg, 7, 1, 1);
						else
							reg_bit_set(reg, 7, 1, 0);
						reg_bit_set(reg, 15, 1, 0);
						reg_bit_set(reg, 31, 1, 0);
						reg_bit_set(reg, 0, 7, delay);
						dmc_phy_soft_update();

						if(scan_bist_patten_test(bist_addr))
						{
							dmc_print_str("0xf");
						}
						else
							dmc_print_str("0x0");
					}
				}
				/*after one channel vref and delay scan end restore vref and delay reg*/
				REG32(reg) = default_cfg_dl_ds;
				dmc_phy_soft_update();
				if(dram_info.dram_type > DRAM_LP3)
				{
					reg_bit_set(DMC_CTL0_(0x0100),20,4,(1<<i));
					dmc_mrw(DRAM_MR_14, DRAM_CS_ALL, (default_vref>>(i*8))&0x7F);
					/*delay at least 500ns for vref update*/
					reg_bit_set(DMC_CTL0_(0x0100),20,4,3);
				}
				else
					reg_bit_set((REG_AON_APB_RF_BASE+0x348), 2, 8, default_vref);
			}
		}
	}
	/*default drv 40 lp3 lp4*/
	ddrc_dq_ds_set(DS_40);
	return 0;
}

static int  scan_read(int rank_num)
{
	u32 regval, default_vref, bist_addr, default_cfg_rd_dl_ds;
	int i, j, drv, delay, drv_tmp, vref;
	u32 reg, reg_pos, item[5], vref_max, vref_min, default_cfg_rd_dl_ds_pos;

	dmc_print_str("\r\n0x434f4e54");
	bist_addr = 0;

	regval = REG32(DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT +0xF4);

	default_vref = (regval >> 24)&0xFF;

	vref_max = default_vref + CUST_VREF_SHIFT;
	if(vref_max > VREF_PHY_START)
		vref_max = VREF_PHY_START;
	vref_min = default_vref - CUST_VREF_SHIFT;
	if(vref_min < VREF_PHY_END)
		vref_min = VREF_PHY_END;

	dmc_print_str("\r\n###0x77aa77bb");
	print_Hex(vref_min);
	print_Hex(vref_max);
	dmc_print_str("###");

	/*drv strength 4 60ohm,5 48 ohm,6 40 ohm,lp4 no 34*/
	for (drv=DS_34; drv>DS_60; drv--)
	{
		if(dram_info.dram_type < DRAM_LP4)
			dmc_mrw(DRAM_MR_3,DRAM_CS_ALL,(8-drv));

		for(i = 0;i < DDR_CHANNEL_NUM; i++)
		{
			if(dram_info.dram_type > DRAM_LP3)
			{
				if(drv==DS_34)
					drv_tmp = DS_40;
				else
					drv_tmp = drv;
				reg_bit_set(DMC_CTL0_(0x0100),20,4,(1<<i));
				regval = (DMC_LP4_MR3&(~(7<<3)))|(drv_tmp<<3);
				dmc_mrw(DRAM_MR_3,DRAM_CS_ALL,regval);
				reg_bit_set(DMC_CTL0_(0x0100),20,4,3);
			}
			/*two bytes for each channel*/
			for(j = 0;j < DDR_BYTE_NUM; j++)
			{
				reg_pos = DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0x70 + 0x20*(i*2+j);
				reg = reg_pos + 4;
				default_cfg_rd_dl_ds = REG32(reg);
				default_cfg_rd_dl_ds_pos = REG32(reg_pos);

				for (vref = vref_max; vref >= vref_min; vref--)
				{
					/*set read vref*/
					reg_bit_set((DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT+0xF4), 24, 8, vref);

					/*delay at least 500ns*/
					wait_us(2);
					for(delay = 0; delay < MAX_DQ_DELAY; delay++)
					{
						/*byte*/
						item[0] = SCAN_ROW1_SYMBOL | (SCAN_ITEM_BYTE<<SCAN_ITEM_OFFSET) | j;
						/*drv*/
						item[1] = SCAN_ROW2_SYMBOL | (SCAN_ITEM_DRV<<SCAN_ITEM_OFFSET) | (240/drv);
						/*PHY*/
						item[2] = SCAN_ROW3_SYMBOL | (SCAN_ITEM_PHY<<SCAN_ITEM_OFFSET) | i;
						/*vref*/
						item[3] = SCAN_ROW4_SYMBOL | (SCAN_ITEM_VREF_RD << SCAN_ITEM_OFFSET)|(vref);
						/*rd positive dl*/
						item[4] = SCAN_COLUMN1_SYMBOL | (SCAN_ITEM_RD_DL<<SCAN_ITEM_OFFSET) | delay;
						print_items(item,5);

						/*set delay*/
						reg_bit_set(reg, 31, 1, 0);
						reg_bit_set(reg, 0, 7, delay);

						reg_bit_set(reg_pos, 31, 1, 0);
						reg_bit_set(reg_pos, 0, 7, delay);
						dmc_phy_soft_update();

						if(scan_bist_patten_test(bist_addr))
						{
							dmc_print_str("0xf");
						}
						else
							dmc_print_str("0x0");
					}
				}
				REG32(reg) = default_cfg_rd_dl_ds;
				REG32(reg_pos) = default_cfg_rd_dl_ds_pos;
				dmc_phy_soft_update();
				if(dram_info.dram_type > DRAM_LP3)
				{
					reg_bit_set(DMC_CTL0_(0x0100),20,4,(1<<i));
					dmc_mrw(DRAM_MR_3,DRAM_CS_ALL,DMC_LP4_MR3);
					reg_bit_set(DMC_CTL0_(0x0100),20,4,3);
					wait_us(2);
				}
			}
		}
		reg_bit_set((DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0xF4), 24, 8, default_vref);
		wait_us(2);
	}
	if(dram_info.dram_type < DRAM_LP4)
		dmc_mrw(DRAM_MR_3,DRAM_CS_ALL,2);
	wait_us(2);
	return 0;
}

static int  scan_ca(int rank_num)
{
	u32 regval, bist_addr, default_cfg_dl_ac0, default_cfg_dl_ac1;
	int i, delay, vref_min, vref_max, vref;
	u32 reg0, reg1, item[4], default_vref, drv, channel_num;

	dmc_print_str("\r\n0x434f4e54");

	default_vref = 0;
	bist_addr = 0;
	if(dram_info.dram_type > DRAM_LP3)
	{
		channel_num = DDR_CHANNEL_NUM;
		dmc_mrr(DRAM_MR_12, DRAM_CS_ALL, &default_vref);
		/*use channel0 vref*/
		get_vref_max_min(&vref_max,&vref_min,(default_vref>>(0*8))&0x7F);
	}
	else
	{
		channel_num = 1;

		reg0 = DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0x64;
		reg1 = DMC_PHY_REG_BASE_ADDR + DDR_FREQ_SHIFT + 0x68;
		default_cfg_dl_ac0 = REG32(reg0);
		default_cfg_dl_ac1 = REG32(reg1);

		regval = REG32(REG_AON_APB_RF_BASE+0x348);
		default_vref = (regval>>2)&0xFF;

		vref_max = default_vref + CUST_VREF_SHIFT;
		if(vref_max > VREF_PHY_START)
			vref_max = VREF_PHY_START;
		vref_min = default_vref - CUST_VREF_SHIFT;
		if(vref_min < VREF_PHY_END)
			vref_min = VREF_PHY_END;
	}

	dmc_print_str("\r\n###0x77aa77cc");
	print_Hex(vref_min);
	print_Hex(vref_max);
	dmc_print_str("###");

	for (drv = DS_34; drv > DS_60; drv--)
	{
		ddrc_ca_ds_set(drv);

		for(i = 0;i < channel_num; i++)
		{
			if(dram_info.dram_type > DRAM_LP3)
			{
				reg0 = DMC_PHY_REG_BASE_ADDR  + DDR_FREQ_SHIFT + 0x64 + (i*4);
				default_cfg_dl_ac0 = REG32(reg0);
			}

			for (vref = vref_max; vref >= vref_min; vref--)
			{
				if(dram_info.dram_type > DRAM_LP3)
				{
					REG32(reg0) = default_cfg_dl_ac0;
					dmc_phy_soft_update();

					/*vref 0~0x32;0x40~0x72,0x1D~0x32 is duplicated*/
					if((vref == 0x3F))
						vref = 0x1D;
					/*set CA vref*/
					reg_bit_set(DMC_CTL0_(0x0100),20,4,(1<<i));
					dmc_mrw(DRAM_MR_12, DRAM_CS_ALL, vref);
					/*delay at least 500ns for vref update*/
					wait_us(2);
					reg_bit_set(DMC_CTL0_(0x0100),20,4,3);
				}
				else
					reg_bit_set((REG_AON_APB_RF_BASE+0x348), 2, 8, vref);

				for(delay = 0; delay < MAX_DQ_DELAY; delay++)
				{
					/*phy*/
					item[0] = SCAN_ROW1_SYMBOL | (SCAN_ITEM_PHY<<SCAN_ITEM_OFFSET) | i;
					/*drv*/
					item[1] = SCAN_ROW2_SYMBOL | (SCAN_ITEM_DRV<<SCAN_ITEM_OFFSET) | (240/drv);
					/*vref*/
					item[2] = SCAN_ROW3_SYMBOL | (SCAN_ITEM_VREF_CA << SCAN_ITEM_OFFSET)|(vref);
					/*ac dl*/
					item[3] = SCAN_COLUMN1_SYMBOL | (SCAN_ITEM_AC_DL<<SCAN_ITEM_OFFSET) | delay;
					print_items(item,4);

					/*set delay*/
					reg_bit_set(reg0, 7, 1, 0);
					reg_bit_set(reg0, 15, 1, 0);
					reg_bit_set(reg0, 31, 1, 0);
					reg_bit_set(reg0, 0, 7, delay);
					if(dram_info.dram_type <= DRAM_LP3)
					{
						reg_bit_set(reg1, 7, 1, 0);
						reg_bit_set(reg1, 15, 1, 0);
						reg_bit_set(reg1, 31, 1, 0);
						reg_bit_set(reg1, 0, 7, delay);
					}
					dmc_phy_soft_update();

					if(scan_bist_patten_test(bist_addr))
					{
						dmc_print_str("0xf");
						if(dram_info.dram_type < DRAM_LP4)
						{
							regulator_set_voltage("vddmem",0);
							wait_us(20);
						}
						sdram_init();
						scan_ca_pre_set(i,vref);
					}
					else
					dmc_print_str("0x0");
				}
			}
			REG32(reg0) = default_cfg_dl_ac0;
			if(dram_info.dram_type <= DRAM_LP3)
				REG32(reg1) = default_cfg_dl_ac1;
			dmc_phy_soft_update();
			if(dram_info.dram_type > DRAM_LP3)
			{
				reg_bit_set(DMC_CTL0_(0x0100),20,4,(1<<i));
				dmc_mrw(DRAM_MR_12, DRAM_CS_ALL, (default_vref>>(i*8))&0x7F);
				wait_us(2);
				reg_bit_set(DMC_CTL0_(0x0100),20,4,3);
			}
			else
				reg_bit_set((REG_AON_APB_RF_BASE+0x348), 2, 8, default_vref);
		}
	}
	/*ca default 34*/
	ddrc_ca_ds_set(DS_34);
	return 0;
}

void  ddr_scan_offline_r2p0(u32 ddr_clk)
{
	int i, j, cs_num;
	u32 regval, ddr_type, tmp, half_mode, clk_mode;

	cs_num = dram_info.cs_num;
	dmc_freq_sel_search(ddr_clk, &freq_fn);
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

	regval = (REG32(DMC_PHY_REG_BASE_ADDR + 0x644)) & 0x7F;

	tmp = (((1000000 / ddr_clk) / (regval & 0x7F) / (1 + half_mode)) * 2) >> clk_mode;

	dmc_print_str("\r\n***0x60600000***");
	scan_pre_set();
	dmc_print_str("\r\n***");
	print_Hex(ddr_clk);
	dmc_print_str("***");
	dmc_print_str("\r\n***0x55aa55aa");
	print_Hex(tmp);
	dmc_print_str("***");
	dmc_print_str("\r\n0x73747172");

	if(dram_info.dram_type < DRAM_LP4)
		cs_num = 1;

	for(i = 0; i < cs_num; i++)
	{
		scan_write(i);
	}
	scan_read(0);
	scan_ca(0);

	dmc_print_str("\r\n0x434f4e54");
	dmc_print_str("\r\n0x656E6464");
	while(1)
	{
		wait_us(1280*5000);
		//dmc_print_str("DDR scan offline end....  \r\n");
	}
}
