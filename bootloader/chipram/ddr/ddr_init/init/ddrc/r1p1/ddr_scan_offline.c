#include "sci_types.h"
#include "ddrc_r1p1.h"
#include "ddrc_r1p1_phy.h"
#include "ddrc_r1p1_common.h"
#include "ddr_scan_offline.h"
#include "debug.h"
#include <fdl_channel.h>
#include <asm/arch/sprd_reg.h>

#define REG32(x)	(*((volatile unsigned int*)(x)))
u32 bit_mask_num = 0xFFFF;
extern int uart_log_disable;

typedef struct __BIST_INFO{
	u32 bist_num;
	u32 bist_addr[4];
	u32 bist_len;
	u32 bist_mode;
	u32 bist_bwtest_mode;
	u32 bist_pattern;
} BIST_INFO;

#define PASS ddrc_print_scan("\t0x0")
#define FAIL ddrc_print_scan("\t0xf")
#define PASS_SYMBOL ddrc_print_scan("*")
#define FAIL_SYMBOL ddrc_print_scan(".")
#define FAIL_VREF_TRAINING_STRAT_SYMBOL ddrc_print_scan("S")
#define FAIL_VREF_TRAINING_END_SYMBOL ddrc_print_scan("E")
#define PASS_VREF_TRAINING_SYMBOL ddrc_print_scan("o")
#define PASS_VREF_DELAY_TRAINING_SYMBOL ddrc_print_scan("M")
#define PASS_VREF_TRAINING_STRAT_SYMBOL ddrc_print_scan("S")
#define PASS_VREF_TRAINING_END_SYMBOL ddrc_print_scan("E")
#define THROUGH_EYE_SCOPE ddrc_print_scan("|")
extern DRAM_CHIP_INFO ddr_chip_cur;
extern uint32 bist_fail_num[];

extern BIST_INFO bist_info_ch0;
extern BIST_INFO bist_info_ch1;
extern BIST_INFO bist_info_ch2;
extern void ddrc_phy_rpull_set(uint32 phy_base, uint32 freq_sel, uint32 value);

extern  _start();

//rom_value store_flag
rom_value *store_reboot_value=((rom_value *)ROM_START_ADDRESS);

/*
u16 first_pass=0;//store firt get pass position
u16 last_pass=0;//store last get pass position
u16 center_pass=0;
*/
#define first_pass  (store_reboot_value->first_pass)
#define last_pass   (store_reboot_value->last_pass)
#define center_pass (store_reboot_value->center_pass)
#define pass_flag   (store_reboot_value->pass_flag)
#define fail_flag   (store_reboot_value->fail_flag)

u8 ddr_scan_transfer_flag=1;//avoid repeat call ddr_offline_scan_seq function ,use for ddrc_r1p0.c
u32 freq_sel;//read FREQ
u32 vref_address_0=0; //store scan read vreaf address
u32 vref_address_1=0;
uint32 LP4_write_training_vref=0;/*write training value to read MR14 for LPDDR4X*/
u32 LP4X_ca_training_vref=0;/*CA training value to read MR12 for LPDDR4X*/
best_delay_para best_delay;//store best delay for read and write
/*Store scan best parameter*/
best_para read_dac_para;
best_para read_op_para;
best_para write_dac_para;
/*Bist start address*/
u64 bist_start_address=0;/*use for dual rank set bist start address*/
//rom_value *store_reboot_value=&store_flag;
struct phy_train_res train_res[2][2];//train_res[rank][phy]


/*HW Training Result*/
/*static struct ca_result	    ca_phy0_result;
static struct ca_result	    ca_phy1_result;*/
static struct read_result	read_phy0_result;
static struct read_result	read_phy1_result;
static struct write_result  write_phy0_result;
static struct write_result  write_phy1_result;

#define ca_phy0_result (store_reboot_value->ca_phy0_result)
#define ca_phy1_result (store_reboot_value->ca_phy1_result)
#define VREFE_SCAN_AC_MAX 0x72
static void ddr_print_scan_dead_line_4x(int num);
static struct scan_odt_vref_high scan_wr_odt_vref_high[3]= {
{
	.odt = 3, //80ohm
	.vref = 0x62
},
{
	.odt = 4, //60ohm
	.vref = 0x62
},
{
	.odt = 5, //48ohm
	.vref = 0x52
}

};
static struct scan_odt_vref_high scan_rd_odt_vref_high[3]= {
{
	.odt = 3, //80ohm
	.vref = 0x56
},
{
	.odt = 4, //60ohm
	.vref = 0x50
},
{
	.odt = 5, //48ohm
	.vref = 0x48
}

};

extern LPDDR4_ODT_CFG lpddr4_odt_cfg[];
extern LPDDR4_ODT_CFG lpddr4x_odt_cfg[];


/******************************
*Name:uint8tochar
* Function:uint Transform char
*******************************/
char p_data[5] = {0};
char *uint8tochar(uint8 val)
{
	uint8 high_byte = 0;
	uint8 low_byte = 0;
	uint8 temp;
	temp = val&0xf;
	if(temp > 9)
	{
		low_byte=temp-10+0x61;
	}else
	{
		low_byte=temp+0x30;
	}
	temp = (val&0xf0) >> 4;
	if(temp > 9)
	{
		high_byte=temp-10+0x61;
	}else
	{
		high_byte=temp+0x30;
	}
	p_data[0]= high_byte;
	p_data[1]= low_byte;
	p_data[2]= 0;

	return p_data;
}

static uint32 dmc_ddr_test(u32 bist_num,u64 addr)
{
	volatile uint32 i=0;
	uint32 test_num=0;

	bist_info_ch0.bist_num = 0;
	bist_info_ch0.bist_len = BIST_RESERVE_SIZE;
	bist_info_ch0.bist_addr[0] = addr;//0;//chip_size - BIST_RESERVE_SIZE;
	bist_info_ch0.bist_addr[1] = addr + 0x1000000;
	bist_info_ch0.bist_addr[2] = addr + 0x2000000;
	bist_info_ch0.bist_mode = BIST_ALLWRC;
	bist_info_ch0.bist_pattern = SIPI_PATT;
	bist_info_ch0.bist_bwtest_mode = NORMAL_MODE;

	bist_info_ch1.bist_num = 1;
	bist_info_ch1.bist_len = BIST_RESERVE_SIZE;
	bist_info_ch1.bist_addr[0] = addr;//0;//chip_size - BIST_RESERVE_SIZE;
	bist_info_ch1.bist_addr[1] = addr + 0x1000000;
	bist_info_ch1.bist_addr[2] = addr + 0x2000000;
	bist_info_ch1.bist_mode = BIST_ALLWRC;
	bist_info_ch1.bist_pattern = LFSR_PATT;
	bist_info_ch1.bist_bwtest_mode = NORMAL_MODE;

	bist_info_ch2.bist_num = 2;
	bist_info_ch2.bist_len = BIST_RESERVE_SIZE;
	bist_info_ch2.bist_addr[0] = addr;//0;//chip_size - BIST_RESERVE_SIZE;
	bist_info_ch2.bist_addr[1] = addr + 0x1000000;
	bist_info_ch2.bist_addr[2] = addr + 0x2000000;
	bist_info_ch2.bist_mode = BIST_ALLWRC;
	bist_info_ch2.bist_pattern = USER_PATT;
	bist_info_ch2.bist_bwtest_mode = NORMAL_MODE;
	//for(i=0;i<10;i++)
	{
		bist_fail_num[bist_num]=0;
		bist_fail_num[bist_num]+=bist_test();
		test_num++;
	}
	if(bist_fail_num[bist_num] >0)
		return 1;
	else
		return 0;
}

static u64 get_bist_address_lp4(u32 channel_num,u32 rank_num)
{
	u64 bist_addr;
	u64 ddr_size;

	sdram_chip_whole_size(&ddr_size);
	if((rank_num == 1) && (ddr_size > 0x140000000))
	{
		bist_addr = ddr_size/2;
		return bist_addr;
	}
	if(channel_num == 0)
	{
		if(rank_num == 0)
			bist_addr = 0;
		else
			bist_addr = ddr_size/4;
	}
	else
	{
		if(rank_num == 0)
			bist_addr = ddr_size/2;
		else
			bist_addr = (ddr_size/2 + ddr_size/4);
	}

	//rand32 = rand_u32()%0x40000;
	//bist_addr += rand32;
	return bist_addr;
}

void store_train_result(u32 rank)
{
	u32 data_tmp=0;
	u32 phy_base;
	int i;

	for(i = 0;i < 2;i++ )
	{
		if(i == 0)
			phy_base = DMC_GUCPHY0_BASE;
		else
			phy_base = DMC_GUCPHY1_BASE;
		/*CA*/
		data_tmp = __raw_readl(phy_base + 0xe6*4);
		train_res[rank][i].phy_ca_e6 = data_tmp;
		/*Read*/
		data_tmp = __raw_readl(phy_base + 0xea*4);
		train_res[rank][i].phy_read_ea = data_tmp;
		data_tmp = __raw_readl(phy_base + 0xeb*4);
		train_res[rank][i].phy_read_eb = data_tmp;
		data_tmp = __raw_readl(phy_base + 0xed*4);
		train_res[rank][i].phy_read_ed=data_tmp;
		/*Write*/
		data_tmp = __raw_readl(phy_base + 0xe9*4);
		train_res[rank][i].phy_write_e9=data_tmp;
		data_tmp = __raw_readl(phy_base + 0xec*4);
		train_res[rank][i].phy_write_ec=data_tmp;
		data_tmp = __raw_readl(phy_base + 0xee*4);
		train_res[rank][i].phy_write_ee=data_tmp;
	}
}


/*******************************
*Function:Print Set register
*Name    :ddr_print_set_register for test
********************************/
void ddr_print_set_register(void)
{
	u32 phy_data_0=0,phy_data_1=0,phy_data_2=0,phy_data_3=0,phy_data_4=0,phy_data_5=0;
	phy_data_0=REG32(DMC_GUCPHY0_BASE+freq_sel*20*4+0x12*4);
	phy_data_1=REG32(DMC_GUCPHY1_BASE+freq_sel*20*4+0x12*4);
	phy_data_2=REG32(DMC_GUCPHY0_BASE+freq_sel*20*4+0x11*4);
	phy_data_3=REG32(DMC_GUCPHY1_BASE+freq_sel*20*4+0x11*4);
	phy_data_4=REG32(DMC_GUCPHY0_BASE+freq_sel*20*4+0xc*4);
	phy_data_5=REG32(DMC_GUCPHY1_BASE+freq_sel*20*4+0xc*4);
	ddrc_print_scan("\r\n Write register:");
	ddr_print_u32_data(phy_data_0);
	ddr_print_u32_data(phy_data_1);
	ddrc_print_scan("\r\n Read register:");
	ddr_print_u32_data(phy_data_2);
	ddr_print_u32_data(phy_data_3);
	ddrc_print_scan("\r\n CA register:");
	ddr_print_u32_data(phy_data_4);
	 //ddr_print_u32_data(phy_data_5);
}

/**********************************************
*Function:Print x axis ruler
*
**********************************************/
static void ddr_print_scan_dead_line(void)
{
	u32 i=0;
	u32 data_temp=0;
	ddrc_print_scan("              ");

	for(i=0;i<=0xff;i++)
	{
		switch (i)
		{
			case 0x0:ddrc_print_scan("0");break;
			case 0x10:ddrc_print_scan("1");break;
			case 0x20:ddrc_print_scan("2");break;
			case 0x30:ddrc_print_scan("3");break;
			case 0x40:ddrc_print_scan("4");break;
			case 0x50:ddrc_print_scan("5");break;
			case 0x60:ddrc_print_scan("6");break;
			case 0x70:ddrc_print_scan("7");break;
			case 0x80:ddrc_print_scan("8");break;
			case 0x90:ddrc_print_scan("9");break;
			case 0xa0:ddrc_print_scan("A");break;
			case 0xb0:ddrc_print_scan("B");break;
			case 0xc0:ddrc_print_scan("C");break;
			case 0xd0:ddrc_print_scan("D");break;
			case 0xe0:ddrc_print_scan("E");break;
			case 0xf0:ddrc_print_scan("F");break;
			default:ddrc_print_scan("-");break;
		}
	}
	ddrc_print_scan("\r\n");
}

/**********************************************
*Function:Print x axis ruler
*LPDDR4-write
**********************************************/
static void ddr_print_scan_dead_line_4x(int num)
{
	u32 i=0;
	u32 data_temp=0;

	ddrc_print_scan("              ");

	for(i=0;i<=num;i++)
	{
		switch (i&0xff)
		{
			case 0x0:ddrc_print_scan("0");break;
			case 0x10:ddrc_print_scan("1");break;
			case 0x20:ddrc_print_scan("2");break;
			case 0x30:ddrc_print_scan("3");break;
			case 0x40:ddrc_print_scan("4");break;
			case 0x50:ddrc_print_scan("5");break;
			case 0x60:ddrc_print_scan("6");break;
			case 0x70:ddrc_print_scan("7");break;
			case 0x80:ddrc_print_scan("8");break;
			case 0x90:ddrc_print_scan("9");break;
			case 0xa0:ddrc_print_scan("A");break;
			case 0xb0:ddrc_print_scan("B");break;
			case 0xc0:ddrc_print_scan("C");break;
			case 0xd0:ddrc_print_scan("D");break;
			case 0xe0:ddrc_print_scan("E");break;
			case 0xf0:ddrc_print_scan("F");break;
			default:ddrc_print_scan("-");break;
		}

	}
	ddrc_print_scan("\r\n");
}

void ca_result_get(u32 phy, u32 rank, struct ca_result *phy_ca_result)
{
	u32 data_tmp;
	data_tmp = train_res[rank][phy].phy_ca_e6;//0x0398 CA training coarse and fine delay trainining result and ca vref result

	phy_ca_result->vref_dram_ca_result = (data_tmp >> 24) & 0x3f;
	phy_ca_result->ca_pass_window = (data_tmp >> 16) & 0xFF;
	phy_ca_result->ca_result_cfg_fine = (data_tmp >> 8) & 0xFF;
	phy_ca_result->ca_result_cfg_coarse = data_tmp & 0xff;

	phy_ca_result->ca_result_cfg_fine += 0x100*phy_ca_result->ca_result_cfg_coarse;
	//Update Eye Window Start & End
	phy_ca_result->ca_eye_window_start=TRAINGING_EYE_START_VALUE(phy_ca_result->ca_result_cfg_fine,phy_ca_result->ca_pass_window);
	phy_ca_result->ca_eye_window_end = TRAINGING_EYE_END_VALUE(phy_ca_result->ca_result_cfg_fine,phy_ca_result->ca_pass_window);
}

void read_result_get(u32 phy, u32 rank, struct read_result *phy_read_result)
{
	u32 data_tmp;
	data_tmp = train_res[rank][phy].phy_read_ea;//0x03a8 // read vref training result

	phy_read_result->deye_vref_db0_result = data_tmp & 0xff;
//	phy_read_result->deye_vref_db1_result = (data_tmp >> 8) & 0xff;

	data_tmp = train_res[rank][phy].phy_read_eb;

	phy_read_result->rd_db1_dqsn = (data_tmp >> 24) & 0xff;
	phy_read_result->rd_db0_dqsn = (data_tmp >> 16) & 0xff;
	phy_read_result->rd_db1_dqs = (data_tmp >> 8) & 0xff;
	phy_read_result->rd_db0_dqs = data_tmp & 0xff;

	data_tmp = train_res[rank][phy].phy_read_ed;//0x03b4 read eye pass window

	phy_read_result->db1_rdq_pass_window = (data_tmp >> 8) & 0xFF; //mlb_train_db0_deye_pass_window_cfg_db1
	phy_read_result->db0_rdq_pass_window = data_tmp & 0xFF;///mlb_train_db0_deye_pass_window_cfg_db0

	//Calcullation read training eye window start and end
	phy_read_result->rd_db0_eye_window_start=TRAINGING_EYE_START_VALUE(phy_read_result->rd_db0_dqs,phy_read_result->db0_rdq_pass_window);
	phy_read_result->rd_db0_eye_window_end  = TRAINGING_EYE_END_VALUE(phy_read_result->rd_db0_dqs,phy_read_result->db0_rdq_pass_window);
	phy_read_result->rd_db1_eye_window_start=TRAINGING_EYE_START_VALUE(phy_read_result->rd_db1_dqs,phy_read_result->db1_rdq_pass_window);
	phy_read_result->rd_db1_eye_window_end  = TRAINGING_EYE_END_VALUE(phy_read_result->rd_db1_dqs,phy_read_result->db1_rdq_pass_window);
}

void write_result_get(u32 phy, u32 rank, struct write_result *phy_write_result)
{
	u32 data_tmp;
	data_tmp = train_res[rank][phy].phy_write_e9;//0x03a4 rddv_sel value and dram vref training result

	phy_write_result->vref_dram_adj_result = (data_tmp >> 24) & 0x3F;//

	data_tmp = train_res[rank][phy].phy_write_ec;//0x03b0 write DQS to DQ coarse and fine phase training result
	phy_write_result->db1_wdq_bt_result = (data_tmp >> 20) & 0xF;//**_cfg_db1_wdq
	phy_write_result->db0_wdq_bt_result = (data_tmp >> 16) & 0xF;//**_cfg_db0_wdq
	phy_write_result->db1_wdq_result = (data_tmp >> 8) & 0xFF;//**_cfg_db1_wrdeye
	phy_write_result->db0_wdq_result = data_tmp & 0xFF;//**_cfg_db0_wrdeye

	data_tmp = train_res[rank][phy].phy_write_ee;//0x03b8 read eye pass window

	phy_write_result->db1_wdq_pass_window = (data_tmp >> 8) & 0xFF; //mlb_train_db0_deye_pass_window_cfg_db1
	phy_write_result->db0_wdq_pass_window = data_tmp & 0xFF;///mlb_train_db0_deye_pass_window_cfg_db0
	//Calcullation write training eye window start and end
	phy_write_result->wr_db0_eye_window_start = TRAINGING_EYE_START_VALUE(phy_write_result->db0_wdq_result, phy_write_result->db0_wdq_pass_window);
	phy_write_result->wr_db0_eye_window_end  = TRAINGING_EYE_END_VALUE(phy_write_result->db0_wdq_result, phy_write_result->db0_wdq_pass_window);
	phy_write_result->wr_db1_eye_window_start = TRAINGING_EYE_START_VALUE(phy_write_result->db1_wdq_result, phy_write_result->db1_wdq_pass_window);
	phy_write_result->wr_db1_eye_window_end  = TRAINGING_EYE_END_VALUE(phy_write_result->db1_wdq_result, phy_write_result->db1_wdq_pass_window);
	phy_write_result->db0_wdq_result += 0x100*(phy_write_result->db0_wdq_bt_result);
	phy_write_result->db1_wdq_result += 0x100*(phy_write_result->db1_wdq_bt_result);
}

void phy_delay_line_set_ca(u32 phy_base, u32 value, u32 freq_sel)
{
	u32 tmp_addr = phy_base + (freq_sel *20*4);

	//set delay line manual value
	reg_bits_set(tmp_addr + 0xc*4, 0, 1, ((value >> 8) & 0x1));//reg_f0_mlb_vref_ca_rang_manu_cfg_delay_bt
	reg_bits_set(tmp_addr + 0xc*4, 8, 8, (value & 0xFF));//reg_f0_mlb_vref_ca_rang_manu_cfg_delay

	//update manual value
	reg_bits_set(phy_base + 0xb2*4, 0, 1, 0);//reg_cal_update_rule_cfg_ca_manual_mode
	reg_bits_set(phy_base + 0xb2*4, 0, 1, 1);//reg_cal_update_rule_cfg_ca_manual_mode
	//dmc_sprd_delay(2);//2us
}

void phy_delay_line_set_wr(u32 phy_base, u32 value, u32 freq_sel, u32 byte_sel)
{
	u32 tmp_addr = phy_base + (freq_sel *20*4);

	if (byte_sel)
	{
		reg_bits_set(tmp_addr + 0x12*4, 20, 4, ((value >> 8) & 0xF));
		reg_bits_set(tmp_addr + 0x12*4, 8, 8, (value & 0xFF));
	}
	else
	{
		reg_bits_set(tmp_addr + 0x12*4, 16, 4, ((value >> 8) & 0xF));
		reg_bits_set(tmp_addr + 0x12*4, 0, 8, (value & 0xFF));
	}
	//update manual value
	reg_bits_set(phy_base + 0xb2*4, 3, 1, 0);  //reg_cal_update_rule_cfg_ca_manual_mode
	reg_bits_set(phy_base + 0xb2*4, 3, 1, 1);//reg_cal_update_rule_cfg_ca_manual_mode

}

void phy_set_dram_odt_vref(u32 vref, u32 odt)
{
	if (odt)
	{
		lpddr_dmc_mrw(CMD_CS_BOTH, 0xb, odt);//mr11
	}

	//mr12
	//lpddr_dmc_mrw(CMD_CS_BOTH, 0xc, vref);
	//mr14 DQ vref
	lpddr_dmc_mrw(CMD_CS_BOTH, 0xe, vref);
}
void phy_delay_line_set_rd(u32 phy_base, u32 value, u32 freq_sel, u32 byte_sel)
{
	u32 tmp_addr = phy_base + (freq_sel *20*4);

	if (byte_sel)
	{
		//reg_bits_set(tmp_addr + 0x11*4, 24, 8, (value & 0xFF));//[31:24] = value[7:0]
		reg_bits_set(tmp_addr + 0x11*4, 8, 8, (value & 0xFF));//[15:8] = value[7:0]
	}
	else
	{
		//reg_bits_set(tmp_addr + 0x11*4, 16, 8, (value & 0xFF));
		reg_bits_set(tmp_addr + 0x11*4, 0, 8, (value & 0xFF));
	}
	//update manual value
	reg_bits_set(phy_base + 0xb2*4, 2, 1, 0);//reg_cal_update_rule_cfg_ca_manual_mode
	reg_bits_set(phy_base + 0xb2*4, 2, 1, 1);//reg_cal_update_rule_cfg_ca_manual_mode

}

void ctrl_soft_command(void)
{
	u32 data_tmp;
	data_tmp = reg_bits_get(0x31000124, 24, 2);
	if ( data_tmp != 0x3)
	{
		dmc_dosoft_cmd_setting(0x80100000);//dsoft_pre_all
		dmc_dosoft_cmd_setting(0x80200000);//dsoft_auto_ref
		dmc_dosoft_cmd_setting(0x80400000);//dsoft_self_ref
	}

}

void ddr_dump_read_reg(u32 phy0_base,u32 phy1_base)
{
	int i, iLoop=0;
	u32 uaddress=0;
	ddrc_print_scan("\r\nPHY0 Register:");
	ddrc_print_scan("\t\t\t\t\t\t");
	ddrc_print_scan("PHY1 Register:\r\n");
	for(iLoop=0;iLoop<=((RD_ONLY_OFFSET_END-RD_ONLY_OFFSET_START)/4);)
	{
		   //phy_base
		for(i = 0 ; i < 2; i++)
		{
			uaddress=phy0_base+RD_ONLY_OFFSET_START+4*iLoop;
			ddr_print_u32_data(uaddress);
			ddrc_print_scan("= ");
			ddr_print_u32_data(REG32(uaddress));
			iLoop++;
		}
		iLoop -= i;
		ddrc_print_scan("\t");
		for(i = 0 ; i < 2; i++)
		{
			uaddress=phy1_base+RD_ONLY_OFFSET_START+4*iLoop;
			ddr_print_u32_data(uaddress);
			ddrc_print_scan("= ");
			ddr_print_u32_data(REG32(uaddress));
			iLoop++;
		}
		ddrc_print_scan("\r\n");
	}

}
void param_to_pass_boundary_print(void)
{
	uint32 first_pass_percent=0;
	uint32 last_pass_percent =0;
	uint32 state=0;
	uint32 pass_delta=0;

	/*Print first pass*/
	first_pass_percent=((first_pass*1000)/512)-((first_pass/512)*1000);
	ddrc_print_scan("\t:first_pass:0x");
	ddrc_print_scan(uint8tochar(first_pass>>8));
	ddrc_print_scan(uint8tochar(first_pass));

	/*Print last pass*/
	last_pass_percent=((last_pass*1000)/512)-((last_pass/512)*1000);
	ddrc_print_scan("\tlast_pass:0x");
	ddrc_print_scan(uint8tochar(last_pass>>8));
	ddrc_print_scan(uint8tochar(last_pass));

	/*Print pass delta*/
	pass_delta=last_pass-first_pass;
	ddrc_print_scan("\tpass_delta:0x");
	ddrc_print_scan(uint8tochar(pass_delta>>8));
	ddrc_print_scan(uint8tochar(pass_delta));

	/*Print center pass*/
	center_pass=(first_pass+last_pass)/2;
	ddrc_print_scan("\tcenter:0x");
	ddrc_print_scan(uint8tochar(center_pass>>8));
	ddrc_print_scan(uint8tochar(center_pass));
}
/*******************************
*Name:ddr_scan_get_training_printresult
*Function:Get training after SDRAM Initial
*         and print result
*Parameter In :NULL
*Parameter Out:NULL
********************************/
void ddr_scan_get_training_printresult(u32 rank)
{
	uint32 i=0;
	u32 * pResult;

	ddrc_print_scan("\r\n************Training Delay Line**************\r\n");
	/*Get gucphy0 CA Result and Print result*/
	ca_result_get(0, rank, &ca_phy0_result);
	ddrc_print_scan("\r\ndmc_gucphy0_ca_result\r\n");
	pResult=&(ca_phy0_result.vref_dram_ca_result);
	for(i=0;i<(sizeof(ca_phy0_result)/sizeof(u32));i++)
	{
		switch (i)
		{
			case 0:ddrc_print_scan("vref_dram_ca_result :");break;
			case 1:ddrc_print_scan("ca_pass_window      :");break;
			case 2:ddrc_print_scan("ca_result_cfg_fine  :");break;
			case 3:ddrc_print_scan("ca_result_cfg_coarse:");break;
			case 4:ddrc_print_scan("ca_eye_window_start :");break;
			case 5:ddrc_print_scan("ca_eye_window_end   :");break;
		}
		ddr_print_u32_data(pResult[i]);
	}

	/*Get gucphy1 CA Result and Print result*/
	ca_result_get(1, rank, &ca_phy1_result);
	ddrc_print_scan("\r\n\r\ndmc_gucphy1_ca_result\r\n");
	pResult=&(ca_phy1_result.vref_dram_ca_result);
	for(i=0;i<(sizeof(ca_phy1_result)/sizeof(u32));i++)
	{
		switch (i)
		{
			case 0:ddrc_print_scan("vref_dram_ca_result :");break;
			case 1:ddrc_print_scan("ca_pass_window      :");break;
			case 2:ddrc_print_scan("ca_result_cfg_fine  :");break;
			case 3:ddrc_print_scan("ca_result_cfg_coarse:");break;
			case 4:ddrc_print_scan("ca_eye_window_start :");break;
			case 5:ddrc_print_scan("ca_eye_window_end   :");break;
		}
		ddr_print_u32_data(pResult[i]);
	}

    /*Get read GUCPHY0 result*/
	read_result_get(0, rank, &read_phy0_result);
	ddrc_print_scan("\r\n\r\nread_phy0_result\r\n");
	pResult=&(read_phy0_result.deye_vref_db0_result);
	for(i=0;i<sizeof(read_phy0_result)/sizeof(u32);i++)
	{
		switch (i)
		{
			case 0:ddrc_print_scan("deye_vref_db_result :");break;
//			case 1:ddrc_print_scan("deye_vref_db1_result:");break;
			case 1:ddrc_print_scan("rd_db0_dqsn         :");break;
			case 2:ddrc_print_scan("rd_db1_dqsn         :");break;
			case 3:ddrc_print_scan("rd_db0_dqs          :");break;
			case 4:ddrc_print_scan("rd_db1_dqs          :");break;
			case 5:ddrc_print_scan("db0_rdq_pass_window :");break;
			case 6:ddrc_print_scan("db1_rdq_pass_window :");break;
			case 7:ddrc_print_scan("rd_db0_window_start :");break;
			case 8:ddrc_print_scan("rd_db0_window_end   :");break;
			case 9:ddrc_print_scan("rd_db1_window_start :");break;
			case 10:ddrc_print_scan("rd_db1_window_end   :");break;
		}
		ddr_print_u32_data(pResult[i]);
	}

	/*Get read GUCPHY1 result*/
	read_result_get(1, rank, &read_phy1_result);
	ddrc_print_scan("\r\n\r\nread_phy1_result\r\n");
	pResult=&(read_phy1_result.deye_vref_db0_result);
	for(i=0;i<(sizeof(read_phy1_result)/sizeof(u32));i++)
	{
		switch (i)
		{
			case 0:ddrc_print_scan("deye_vref_dbresult  :");break;
//			case 1:ddrc_print_scan("deye_vref_db1_result:");break;
			case 1:ddrc_print_scan("rd_db0_dqsn         :");break;
			case 2:ddrc_print_scan("rd_db1_dqsn         :");break;
			case 3:ddrc_print_scan("rd_db0_dqs          :");break;
			case 4:ddrc_print_scan("rd_db1_dqs          :");break;
			case 5:ddrc_print_scan("db0_rdq_pass_window :");break;
			case 6:ddrc_print_scan("db1_rdq_pass_window :");break;
			case 7:ddrc_print_scan("rd_db0_window_start :");break;
			case 8:ddrc_print_scan("rd_db0_window_end   :");break;
			case 9:ddrc_print_scan("rd_db1_window_start :");break;
			case 10:ddrc_print_scan("rd_db1_window_end   :");break;
		}
		ddr_print_u32_data(pResult[i]);
	}

   /*Get write phy0 result*/
	write_result_get(0, rank, &write_phy0_result);
	ddrc_print_scan("\r\n\r\nwrite_phy0_result\r\n");
	pResult=&(write_phy0_result.vref_dram_adj_result);
	for(i=0;i<(sizeof(write_phy0_result)/sizeof(u32));i++)
	{
		switch (i)
		{
			case 0:ddrc_print_scan("vref_dram_adj_result:");break;
			case 1:ddrc_print_scan("db0_wdq_bt_result   :");break;
			case 2:ddrc_print_scan("db1_wdq_bt_result   :");break;
			case 3:ddrc_print_scan("db0_wdq_result      :");break;
			case 4:ddrc_print_scan("db1_wdq_result      :");break;
			case 5:ddrc_print_scan("db0_wdq_pass_window :");break;
			case 6:ddrc_print_scan("db1_wdq_pass_window :");break;
			case 7:ddrc_print_scan("wr_db0_window_start :");break;
			case 8:ddrc_print_scan("wr_db0_window_end   :");break;
			case 9:ddrc_print_scan("wr_db1_window_start :");break;
			case 10:ddrc_print_scan("wr_db1_window_end   :");break;
		}
		ddr_print_u32_data(pResult[i]);
	}

   /*Get write phy1 result*/
	write_result_get(1, rank, &write_phy1_result);
	ddrc_print_scan("\r\n\r\nwrite_phy1_result\r\n");
	pResult=&(write_phy1_result.vref_dram_adj_result);
	for(i=0;i<(sizeof(write_phy1_result)/sizeof(u32));i++)
	{
		switch (i)
		{
			case 0:ddrc_print_scan("vref_dram_adj_result:");break;
			case 1:ddrc_print_scan("db0_wdq_bt_result   :");break;
			case 2:ddrc_print_scan("db1_wdq_bt_result   :");break;
			case 3:ddrc_print_scan("db0_wdq_result      :");break;
			case 4:ddrc_print_scan("db1_wdq_result      :");break;
			case 5:ddrc_print_scan("db0_wdq_pass_window :");break;
			case 6:ddrc_print_scan("db1_wdq_pass_window :");break;
			case 7:ddrc_print_scan("wr_db0_window_start :");break;
			case 8:ddrc_print_scan("wr_db0_window_end   :");break;
			case 9:ddrc_print_scan("wr_db1_window_start :");break;
			case 10:ddrc_print_scan("wr_db1_window_end   :");break;
		}
		ddr_print_u32_data(pResult[i]);
	}
	ddrc_print_scan("\r\n");

	/*Print PU/PD PVT Calibration Result*/
	ddrc_print_scan("\r\nPHY0 PU/PD Calibration Result:\r\n");
	ddrc_print_scan("\r\nPU Calibration Result:");
	ddr_print_u32_data(reg_bits_get(PUPD_PHY0_IOPVT_CALIBRATION_RESULT,0,8));
	ddrc_print_scan("PD Calibration Result:");
	ddr_print_u32_data(reg_bits_get(PUPD_PHY0_IOPVT_CALIBRATION_RESULT,16,8));
	ddrc_print_scan("\r\n\r\nPHY1 PU/PD Calibration Result:\r\n");
	ddrc_print_scan("\r\nPU Calibration Result:");
	ddr_print_u32_data(reg_bits_get(PUPD_PHY1_IOPVT_CALIBRATION_RESULT,0,8));
	ddrc_print_scan("PD Calibration Result:");
	ddr_print_u32_data(reg_bits_get(PUPD_PHY1_IOPVT_CALIBRATION_RESULT,16,8));
	ddrc_print_scan("\r\n");
}

/****************************************
*FUNCTION:DDR scan bist for one bit
*OUTPUT:NULL
*IN    :vref_val: Current set vref value
*       deye_vref_result:Training Vref Value
*       db_dqs:Training delay time
*****************************************/

int ddr_print_bist_result(u8 *pass_flag_bist,u8 *fail_flag_bist,uint32 i,u16 vref_val,const u32 deye_vref_result,const u32 db_dqs,u32 training_eye_start,u32 training_eye_end,scan_type scan_type)
{
	u32 ret=0;
	u8 pattern_i=0;
	u32 vref_mask=0;

	//step. bist operation and record the pass and fail
	if(dmc_ddr_test(0,bist_start_address)==0)//1:faild 0:success
		ret=0;
	else
		ret=1;

	if(ret)//fail
	{
		/*4X scan  write and ca no set bit8 to 1*/
		if((scan_type==scan_write) || (scan_type==scan_ca))
			vref_mask=0x00;
		else
			 vref_mask=0x80;

		/*Distinguish Cmos and diffential mode */
		if((vref_val == (deye_vref_result)) && (deye_vref_result != 0)) //Only cmos mode Set biet 8 to 1
		{
			//ddrc_print_scan("123\n");
#ifdef DDR_SCAN_PRINT_THROUGH_LINE
			if ((i == (db_dqs + 0x30)) || (i == (db_dqs - 0x30))) //through  width
				{THROUGH_EYE_SCOPE;}
			else
#endif
			if (i == training_eye_start) /*Symbol training Start & End Value*/
				FAIL_VREF_TRAINING_STRAT_SYMBOL;
			else if (i == training_eye_end)
				FAIL_VREF_TRAINING_END_SYMBOL;
			else FAIL_SYMBOL;
		}
		else
		{
#ifdef DDR_SCAN_PRINT_THROUGH_LINE
			if ((i == (db_dqs + 0x30)) || (i == (db_dqs - 0x30))) //through  width
			{
				THROUGH_EYE_SCOPE;
			}
			else
#endif
				FAIL_SYMBOL;
		}
		 /*Update data*/
		if((*pass_flag_bist==0)&&(*fail_flag_bist==1))//Update last_pass
		{
			last_pass=i-1;
			*fail_flag_bist=0;
		}
		if((last_pass-first_pass)<5)//if pass number < 5 Recount first_pass
		{
			*pass_flag_bist=1;
		}
	}
	else//success
	{
		if((scan_type==scan_write)|| (scan_type==scan_ca)) {
		vref_mask=0x00;//Only write
		}else
		{
		  vref_mask=0x80;//4x: read & ca
		}
		if((vref_val==deye_vref_result)&&(deye_vref_result!=0))//Diffential Mode ScanVREF==Training ,Vref write  need compare fixed Training value was 0xd0
		{
#ifdef DDR_SCAN_PRINT_THROUGH_LINE
			if ((i == (db_dqs + 0x30)) || (i == (db_dqs - 0x30))) //through  width
			{
				THROUGH_EYE_SCOPE;
			} else
#endif
			if (i==training_eye_start)/*Symbol training Start & End Value*/
				PASS_VREF_TRAINING_STRAT_SYMBOL;
			else if (i == training_eye_end)
				PASS_VREF_TRAINING_END_SYMBOL;
			else if (i == db_dqs)  /*Symbol training Center dqs*/
				PASS_VREF_DELAY_TRAINING_SYMBOL;
			else
				PASS_VREF_TRAINING_SYMBOL;
		}else
		{
#ifdef DDR_SCAN_PRINT_THROUGH_LINE
		if ((i == (db_dqs + 0x30)) || (i == (db_dqs - 0x30))) //print through  width
		{
			THROUGH_EYE_SCOPE;
		} else
#endif
			PASS_SYMBOL;
		}
		/*Update calculation first pass and last pass*/
		if(*pass_flag_bist==1)
		{
			first_pass=i;
			*pass_flag_bist=0;
		}
		if((last_pass<=first_pass)||((last_pass-first_pass)<5))//last_pass not suitable condition,reset collet fail_flag
		{
			 *fail_flag_bist=1;
		}
	}

return ret;
}
/****************************************
*FUNCTION:DDR scan Read write and ca and print result
*CORRESPONDING Module :PHY0 and PHY1
*INPUT :struct scan_type_parameter
*       dmc_phy_base:PHY0 or PHY1 dmc base address
*       scan_num    :Loop scan set parameter MAX value
        data_module :Only scan  wr and rd  have this parameter(data module 0 and data module 1)
        type        :Scan type write ¡¢read or ca
        vref_val    :Current set vref
*OUTPUT:NULL
*****************************************/
void ddr_offline_scan_parameter(scan_type_parameter type_para,u16 vref_val)
{
	uint32 i=0;
	uint32 read_data=0;
	pass_flag=1;
	fail_flag=1;
	first_pass=0;
	last_pass=0;
	scan_type_parameter temp_parameter=type_para;//Temporarily store
	/***If scan Write or Read should store some parameter ****/
	if(temp_parameter.type==scan_write)
	{
		read_data=REG32(temp_parameter.dmc_phy_base+freq_sel*20*4+0x12*4);
	}
	else if(temp_parameter.type==scan_read)
	{
		read_data=REG32(temp_parameter.dmc_phy_base+freq_sel*20*4+0x11*4);
	}
    /****Loop set parameter and bist test****/
	if(temp_parameter.type == scan_write)
	{
		i = freq_sel*50;
		temp_parameter.scan_num +=freq_sel*30;
	}
	for (; i<=temp_parameter.scan_num; i=i+X_INCREASE_STEP)
	{
		switch((int)(temp_parameter.type))//Chose scan type
	    {
			case 0: phy_delay_line_set_wr(temp_parameter.dmc_phy_base,i,freq_sel,temp_parameter.data_module);break;
			case 1: phy_delay_line_set_rd(temp_parameter.dmc_phy_base,i,freq_sel,temp_parameter.data_module);break;
			default:ddrc_print_scan("\r\n************temp_parameter.type is error**********\r\n");
		}

	   //step. bist operation and record the pass and fail
		if(temp_parameter.type==scan_read)
		{
			if((temp_parameter.dmc_phy_base==DMC_GUCPHY0_BASE)&&(temp_parameter.data_module==data_module_0))
				ddr_print_bist_result(&pass_flag, &fail_flag, i, vref_val, read_phy0_result.deye_vref_db0_result, read_phy0_result.rd_db0_dqs,\
		                                      TRAINGING_EYE_START_VALUE(read_phy0_result.rd_db0_dqs, read_phy0_result.db0_rdq_pass_window),\
		                                      TRAINGING_EYE_END_VALUE(read_phy0_result.rd_db0_dqs, read_phy0_result.db0_rdq_pass_window),temp_parameter.type);
		        else if((temp_parameter.dmc_phy_base==DMC_GUCPHY0_BASE)&&(temp_parameter.data_module==data_module_1))
				ddr_print_bist_result(&pass_flag,&fail_flag,i,vref_val,read_phy0_result.deye_vref_db0_result,read_phy0_result.rd_db1_dqs,\
		                                      TRAINGING_EYE_START_VALUE(read_phy0_result.rd_db1_dqs, read_phy0_result.db1_rdq_pass_window), \
		                                      TRAINGING_EYE_END_VALUE(read_phy0_result.rd_db1_dqs, read_phy0_result.db1_rdq_pass_window),temp_parameter.type);
			else if((temp_parameter.dmc_phy_base==DMC_GUCPHY1_BASE)&&(temp_parameter.data_module==data_module_0))
				ddr_print_bist_result(&pass_flag,&fail_flag,i,vref_val,read_phy1_result.deye_vref_db0_result,read_phy0_result.rd_db0_dqs,\
		                                      TRAINGING_EYE_START_VALUE(read_phy1_result.rd_db0_dqs, read_phy1_result.db0_rdq_pass_window), \
		                                      TRAINGING_EYE_END_VALUE(read_phy1_result.rd_db0_dqs, read_phy1_result.db0_rdq_pass_window),temp_parameter.type);
			else if((temp_parameter.dmc_phy_base==DMC_GUCPHY1_BASE)&&(temp_parameter.data_module==data_module_1))
				ddr_print_bist_result(&pass_flag,&fail_flag,i,vref_val,read_phy1_result.deye_vref_db0_result,read_phy0_result.rd_db1_dqs,\
		                                      TRAINGING_EYE_START_VALUE(read_phy1_result.rd_db1_dqs, read_phy1_result.db1_rdq_pass_window),\
		                                      TRAINGING_EYE_END_VALUE(read_phy1_result.rd_db1_dqs, read_phy1_result.db1_rdq_pass_window),temp_parameter.type);
		   }
		else if(temp_parameter.type==scan_write)
		{
			if((temp_parameter.dmc_phy_base==DMC_GUCPHY0_BASE)&&(temp_parameter.data_module==data_module_0))
				ddr_print_bist_result(&pass_flag, &fail_flag, i, vref_val, LP4_write_training_vref, write_phy0_result.db0_wdq_result,\
		                                      TRAINGING_EYE_START_VALUE(write_phy0_result.db0_wdq_result, write_phy0_result.db0_wdq_pass_window),\
		                                      TRAINGING_EYE_END_VALUE(write_phy0_result.db0_wdq_result, write_phy0_result.db0_wdq_pass_window),temp_parameter.type);
			else if((temp_parameter.dmc_phy_base==DMC_GUCPHY0_BASE)&&(temp_parameter.data_module==data_module_1))
				ddr_print_bist_result(&pass_flag, &fail_flag, i, vref_val, LP4_write_training_vref, write_phy0_result.db1_wdq_result,\
		                                      TRAINGING_EYE_START_VALUE(write_phy0_result.db1_wdq_result, write_phy0_result.db1_wdq_pass_window),\
		                                      TRAINGING_EYE_END_VALUE(write_phy0_result.db1_wdq_result+0x100, write_phy0_result.db1_wdq_pass_window),temp_parameter.type);
			else if((temp_parameter.dmc_phy_base==DMC_GUCPHY1_BASE)&&(temp_parameter.data_module==data_module_0))
				ddr_print_bist_result(&pass_flag, &fail_flag, i, vref_val, LP4_write_training_vref, write_phy1_result.db0_wdq_result,\
		                                      TRAINGING_EYE_START_VALUE(write_phy1_result.db0_wdq_result, write_phy1_result.db0_wdq_pass_window),\
		                                      TRAINGING_EYE_END_VALUE(write_phy1_result.db0_wdq_result, write_phy1_result.db0_wdq_pass_window),temp_parameter.type);    //0x50 bit7-->1 =0xd0
			else if((temp_parameter.dmc_phy_base==DMC_GUCPHY1_BASE)&&(temp_parameter.data_module==data_module_1))
				ddr_print_bist_result(&pass_flag, &fail_flag, i, vref_val, LP4_write_training_vref, write_phy1_result.db1_wdq_result,\
		                                      TRAINGING_EYE_START_VALUE(write_phy1_result.db1_wdq_result, write_phy1_result.db1_wdq_pass_window),\
		                                      TRAINGING_EYE_END_VALUE(write_phy1_result.db1_wdq_result, write_phy1_result.db1_wdq_pass_window),temp_parameter.type);
	   }
	}
  /*Data Restore*/
	if(temp_parameter.type==scan_write)//Restore
	{
		REG32(temp_parameter.dmc_phy_base+freq_sel*20*4+0x12*4)=read_data;
		//update
		reg_bits_set(temp_parameter.dmc_phy_base + 0xb2*4, 3, 1, 0);
		reg_bits_set(temp_parameter.dmc_phy_base + 0xb2*4, 3, 1, 1);
	}else if(temp_parameter.type==scan_read)
	{
		REG32(temp_parameter.dmc_phy_base+freq_sel*20*4+0x11*4)=read_data;
		//update
		reg_bits_set(temp_parameter.dmc_phy_base + 0xb2*4, 2, 1, 0);
		reg_bits_set(temp_parameter.dmc_phy_base + 0xb2*4, 2, 1, 1);
	}
}
/******************************
*Function:scan ca
*
*******************************/
void pub_power_up(void)
{
	reg_bits_set(PD_PUB_SYS_CFG,25, 1,0x1);//pub Off
	while(((REG32(PWR_STATUS2_DBG)>>20)&0x1f) != 0x7);//pd_pub_sys_state
	reg_bits_set(PD_PUB_SYS_CFG,25, 1,0x0);//pub ON
	while(((REG32(PWR_STATUS2_DBG)>>20)&0x1f) != 0x0);//pd_pub_sys_state //PUB poweroff
}
void dram_pub_power_restart(void)
{
	store_reboot_value->window_fail_flag=0;
	regulator_disable("vddmem");//DRAM poweroff
	dmc_sprd_delay(20000);
	//pub_power_up();
	regulator_enable("vddmem");  //DRAM ON
	udelay(30);
}
void ddr_offline_scan_parameter_ca(scan_type_parameter type_para,u16 vref_val)
{
	uint32 i=0;
	u8 ret=0;
	uint32 read_data_a=0;
	uint32 read_data_b=0;
	scan_type_parameter temp_parameter=type_para;//Temporarily store
	//back updata
	read_data_a=REG32(DMC_GUCPHY0_BASE+freq_sel*20*4+0x0c*4);
	read_data_b=REG32(DMC_GUCPHY1_BASE+freq_sel*20*4+0x0c*4);
	/****Loop set parameter and bist test****/
	i=store_reboot_value->scan_x;
	for (; i<=temp_parameter.scan_num;)
	{
        /*Set Delay*/
		phy_delay_line_set_ca(temp_parameter.dmc_phy_base,i,freq_sel);
		ret=ddr_print_bist_result(&pass_flag, &fail_flag, i, vref_val, LP4X_ca_training_vref, ca_phy0_result.ca_result_cfg_fine,\
	                              TRAINGING_EYE_START_VALUE(ca_phy0_result.ca_result_cfg_fine, ca_phy0_result.ca_pass_window),\
	                              TRAINGING_EYE_END_VALUE(ca_phy0_result.ca_result_cfg_fine, ca_phy0_result.ca_pass_window), temp_parameter.type);
		i=i+1;
		store_reboot_value->scan_x=i;
		if(ret)
		{
			if(store_reboot_value->window_fail_flag==0)//Judge all file in line
			{
#if 1
				uart_log_disable = 1;
				//_start();
				ddr_init();
				REG32(0x31000124)=0;
				reg_bits_set(0x3100010c,12,1,0);
				udelay(5);
				ddr_scan_set_ca_vref_lpddr4(vref_val);

				udelay(20);
				uart_log_disable = 0;
#else
				dram_powerup_seq(find_ddr_freq(freq_sel));
				phy_delay_line_set_ca(temp_parameter.dmc_phy_base,ca_phy0_result.ca_result_cfg_fine,freq_sel);
				ddr_scan_set_ca_vref_lpddr4(LP4X_ca_training_vref);
#endif
			}
			else
			{
				uart_log_disable = 1;
				store_reboot_value->window_fail_flag=0;
				dram_pub_power_restart();
				//_start();
				ddr_init();
				REG32(0x31000124)=0;
				reg_bits_set(0x3100010c,12,1,0);
				udelay(5);

				ddr_scan_set_ca_vref_lpddr4(vref_val);
				udelay(20);
				uart_log_disable = 0;
			}
		}
	}
	pass_flag=1;
	fail_flag=1;
}
/*******************************
*Function:Print 32 bit data
*Name    :ddr_print_set_register
*In      :u32 int data
*out     :NULL
********************************/
void ddr_print_u32_data(u32 print_data)
{
	ddrc_print_scan("0x");
	//if(print_data>0xffffff)
	ddrc_print_scan(uint8tochar((print_data>>24)&0xff));
	//if(print_data>0xffff)
	ddrc_print_scan(uint8tochar((print_data>>16)&0xff));
	//if(print_data>0xff)
	ddrc_print_scan(uint8tochar((print_data>>8)&0xff));
	ddrc_print_scan(uint8tochar((print_data>>0)&0xff));
	ddrc_print_scan(" ");
}
/**********************************************************
** Function:u32tostr
** u32 convert string
***********************************************************/
void u32tostr(unsigned long dat,char *str)
{
	char temp[20];
	unsigned char i=0,j=0;
	i=0;
	while(dat)
	{
		temp[i]=dat%10+0x30;
		i++;
		dat/=10;
	}
	j=i;
	for(i=0;i<j;i++)
	{
		str[i]=temp[j-i-1];
	}
	if(!i)
		str[i++]='0';
	str[i]=0;
}
char pr_str[12];
void ddr_print_u32_dec_data(u32 print_data)
{
	u32tostr(print_data,pr_str);
	ddrc_print_scan(pr_str);
}

/*****************************************
*Name    :ddr_get_best_write_delay
*Function:get best delay data
*IN      :scan write loop num and vref
*OUT     :Global Variable:wr_best_delay
******************************************/
void ddr_get_best_delay_para(u8 loop_num,u32 vref_value,best_para *para)
{
	u32 center_pass_value=0;
	u32 pass_width=0;
	center_pass_value=(last_pass+first_pass)/2;
	pass_width=last_pass-first_pass;
	switch (loop_num)
	{
		case 0:   /*PHY0 Data_byte0*/
		if((para->Phy0_databyte0.best_width) < pass_width)
		{
			para->Phy0_databyte0.best_width=pass_width;
			para->Phy0_databyte0.best_delay=center_pass_value;
			para->Phy0_databyte0.best_vref=vref_value;
			para->Phy0_databyte0.eye_width=eye_open_value(pass_width);
		}
		break;
		case 1:  /*PHY0 Data_byte1*/
		if((para->Phy0_databyte1.best_width) < pass_width)
		{
			para->Phy0_databyte1.best_width =pass_width;
			para->Phy0_databyte1.best_delay =center_pass_value;
			para->Phy0_databyte1.best_vref  =vref_value;
			para->Phy0_databyte1.eye_width=eye_open_value(pass_width);
		}
		break;
		case 2:  /*PHY1 Data_byte0*/
		if((para->Phy1_databyte0.best_width) < pass_width)
		{
			para->Phy1_databyte0.best_width=pass_width;
			para->Phy1_databyte0.best_delay=center_pass_value;
			para->Phy1_databyte0.best_vref=vref_value;
			para->Phy1_databyte0.eye_width=eye_open_value(pass_width);
		}
		break;
		case 3:  /*PHY1 Data_byte1*/
		if((para->Phy1_databyte1.best_width) < pass_width)
		{
			para->Phy1_databyte1.best_width=pass_width;
			para->Phy1_databyte1.best_delay=center_pass_value;
			para->Phy1_databyte1.best_vref=vref_value;
			para->Phy1_databyte1.eye_width=eye_open_value(pass_width);
		}
		break;
	}
}
/*****************************************
*Name    :ddr_print_best_para
*Function:print read and write parameter
*IN      :NULL
*OUT     :NULL
******************************************/
 void ddr_print_best_parameter(best_para *para)
{
   u8 ibest=0;
   u8 ivalue=0;
   u32 *pbest_para=&(para->Phy0_databyte0.best_delay);
   for(ibest=0;ibest<(sizeof(best_para)/sizeof(best_value));ibest++)//loop best_delay member
	{
		switch (ibest)
		{
		case 0:ddrc_print_scan("\r\nPhy0DataByte0:");break;
		case 1:ddrc_print_scan("\r\nPhy0DataByte1:");break;
		case 2:ddrc_print_scan("\r\nPhy1DataByte0:");break;
		case 3:ddrc_print_scan("\r\nPhy1DataByte1:");break;
		}
		for(ivalue=0;ivalue<(sizeof(best_value)/sizeof(u32));ivalue++)//loop best_value member
		{
		switch (ivalue)
		{
		case 0:ddrc_print_scan("BestDelay:");break;
		case 1:ddrc_print_scan("Best Vref:");break;
		case 2:ddrc_print_scan("MaxWidth :");break;
		case 3:ddrc_print_scan("EYE Width:");break;
		}
		ddr_print_u32_data(pbest_para[ibest*4+ivalue]);
		ddrc_print_scan("\t");
		}
	}

}
static void ddr_print_all_best_para(void)
{
	u8 ibest=0;
	u8 ivalue=0;
	ddrc_print_scan("\r\n\r\nRead best  dac Parameter:");
	ddr_print_best_parameter(&read_dac_para);
	#ifndef DDR_SCAN_CMOS_MODE
	ddrc_print_scan("\r\n\r\nRead best op Parameter:");
	ddr_print_best_parameter(&read_op_para);
	#endif
	ddrc_print_scan("\r\n\r\nWrite best dac Parameter:");
	ddr_print_best_parameter(&write_dac_para);
}
/****************************
 *print ca best parameter
*****************************/
static void ddr_print_ca_best_para(best_para *para)
{
	u8 ibest=0;
	u8 ivalue=0;
	ddrc_print_scan("\r\n\r\nCA best Parameter:");
	u32 *pbest_para=&(para->Phy0_databyte0.best_delay);
	for(ivalue=0;ivalue<(sizeof(best_value)/sizeof(u32));ivalue++)//loop best_value member
	   {
		switch (ivalue)
		{
			case 0:ddrc_print_scan("BestDelay:");break;
			case 1:ddrc_print_scan("Best Vref:");break;
			case 2:ddrc_print_scan("MaxWidth :");break;
			case 3:ddrc_print_scan("EYE Width:");break;
		}
		ddr_print_u32_data(pbest_para[ivalue]);
		ddrc_print_scan("\t");
	  }

}

/*Set write vref for lpddr4x*/
inline void ddr_scan_set_write_vref_lpddr4(int vref, int i){
	reg_bits_set(0x31000100,20,4,(1<<i));
	lpddr_dmc_mrw(CMD_CS_BOTH,0xe, vref);//mr14
	reg_bits_set(0x31000100,20,4,3);
}

/*Set write vref for lpddr4x*/
inline void ddr_scan_set_ca_vref_lpddr4(int vref){
	lpddr_dmc_mrw(CMD_CS_BOTH,0xc, vref);//mr12
}

/************************************************************************
*Name : Off line scan write:
* Note:	1.maybe need to go into selfrefresh status when update dll value
* 	2.maybe need to reset after scan one time
*************************************************************************/

/*according PHY&DataByte scan*/
void ddr_offline_scan_wr(u16 max ,u16 min,best_para*pPara, u32 rank)
{
	u8 i=0,j;
	int vref_lv=0;

	ddrc_print_scan("\r\noff line scan write\r\n");
	for(i=0;i<(sizeof(phy_scan_para_wr)/sizeof(scan_type_parameter));i++)
	{
		if(bit_mask_num !=0xFFFF)
		{
			for(j = 0; j <4; j++)
			{
				if(((bit_mask_num >> j*8)&0xFF) != 0)
					i = j;
			}
			if(bit_mask_num >= (1 << 16))
				bit_mask_num = bit_mask_num >> 16;

		}
		bist_start_address = get_bist_address_lp4(i/2,rank);

		ddrc_print_scan("\r\nBist start address=");
		if(bist_start_address > 0xFFFFFFFF)
			ddr_print_u32_data((bist_start_address >> 32));
		ddr_print_u32_data(bist_start_address);
		ddrc_print_scan("\r\n          ");
		ddr_print_scan_dead_line_4x(0x1ff);

		if(phy_scan_para_wr[i].dmc_phy_base == DMC_GUCPHY0_BASE)
			ddrc_print_scan("PHY0,");
		else
			ddrc_print_scan("PHY1,");

		if(phy_scan_para_wr[i].data_module == 0)
			ddrc_print_scan("DataByte0,");
		else
			ddrc_print_scan("DataByte1,");

		for(vref_lv = max;vref_lv >= min;vref_lv--)
		{
			if((LP4_write_training_vref > 0x1D) &&(LP4_write_training_vref <0x40))
			{
				if(vref_lv == 0x54)
					vref_lv = 0x32;
			}
			else
			{
				if(vref_lv == 0x3F)
					vref_lv = 0x1D;
			}

			ddr_scan_set_write_vref_lpddr4(vref_lv,i/2);  //set vref value
			dmc_sprd_delay(20);//2ms

			if(vref_lv!=max)
				ddrc_print_scan("               ");

			ddrc_print_scan("VREFE=");
			ddrc_print_scan(uint8tochar(vref_lv&0xff));
			ddrc_print_scan(":");

			// reg_bits_set(PHY_VREFE_ADDRESS,31,1,1);//always keep 1 for bit 31 according email
			//Scan and print
			ddr_offline_scan_parameter(phy_scan_para_wr[i],vref_lv);
			param_to_pass_boundary_print();//print boundary
			 //ddr_get_best_write_delay(i,vref_lv);//store best parameter
			ddr_get_best_delay_para(i,vref_lv,pPara);//store best parameter
			first_pass=0;
			last_pass=0;
			ddrc_print_scan("\r\n");
		}

		ddrc_print_scan("\r\n");
		/*perbit mode*/
		if(bit_mask_num !=0xFFFF)
			break;
		//default vref
		ddr_scan_set_write_vref_lpddr4(write_phy0_result.vref_dram_adj_result,i/2);
	}
}

/*****************************************
*step  .Off line Scan read and print
*Note:1 need to go into selfrefresh status when update dll value
*	  2 Need to before scan back up and after scan restore
*****************************************/
/*
     LOOP1: PHY &  DATA MODULE (4 times)
         LOOP2: VREF  (ACCORDING PHY &  DATA MODULE SET ADDRESS)
             LOOP3: scan parameter  FUNCTION:ddr_offline_scan_parameter
*/
//void ddr_offline_scan_rd(vref_mes vref_temp)
/*according PHY&DataByte scan*/
void ddr_offline_scan_rd(u16 max, u16 min, best_para *pPara, u32 rank)
{
	u8 i=0,j;
	int vref_val=0;
	vref_address_0=DMC_GUCPHY0_BASE+vrefi_offset[freq_sel];//confirm vref register
	vref_address_1=DMC_GUCPHY1_BASE+vrefi_offset[freq_sel];

	for(i=0;i<(sizeof(phy_scan_para_rd)/sizeof(scan_type_parameter));i++)  //pay & data module
	{
		if(bit_mask_num !=0xFFFF)
		{
			for(j = 0; j <4; j++)
			{
				if(((bit_mask_num >> j*8)&0xFF) != 0)
					i = j;
			}
			if(bit_mask_num >= (1 << 16))
				bit_mask_num = bit_mask_num >> 16;
		}

		bist_start_address = get_bist_address_lp4(i/2,rank);

		ddrc_print_scan("\r\nBist start address=");
		if(bist_start_address > 0xFFFFFFFF)
			ddr_print_u32_data((bist_start_address >> 32));
		ddr_print_u32_data(bist_start_address);

		ddrc_print_scan("\r\n          ");
		ddr_print_scan_dead_line();

		if(phy_scan_para_wr[i].dmc_phy_base==DMC_GUCPHY0_BASE) //Display message
			ddrc_print_scan("PHY0,");
		else
			ddrc_print_scan("PHY1,");
		if(phy_scan_para_wr[i].data_module==0)
			ddrc_print_scan("DataByte0,");
		else
			{ddrc_print_scan("DataByte1,");}

		for(vref_val=max;vref_val>=min;vref_val--)
		{
						//ddrc_print_scan("1\n");
			reg_bits_set(vref_address_0,0,8,vref_val);
			reg_bits_set(vref_address_1,0,8,vref_val);
			reg_bits_set(vref_address_0,8,8,vref_val);
			reg_bits_set(vref_address_1,8,8,vref_val);
			//ddrc_print_scan("2\n");
			dmc_sprd_delay(5000);//20ms

			if(vref_val!=max)
			ddrc_print_scan("               ");
			ddrc_print_scan("VREFI=");
			ddrc_print_scan(uint8tochar(vref_val&0xff));
			ddrc_print_scan(":");

			//ddrc_print_scan("3\n");
			ddr_offline_scan_parameter(phy_scan_para_rd[i],vref_val);
			param_to_pass_boundary_print();//print boundary
			//ddr_get_best_read_delay(i,vref_val);//store read best parameter
			ddr_get_best_delay_para(i,vref_val,pPara);
			ddrc_print_scan("\r\n");
		}
		/*perbit mode*/
		if(bit_mask_num !=0xFFFF)
			break;
	}
	reg_bits_set(vref_address_0,0,8,read_phy0_result.deye_vref_db0_result);
	reg_bits_set(vref_address_1,0,8,read_phy0_result.deye_vref_db0_result);
	reg_bits_set(vref_address_0,8,8,read_phy0_result.deye_vref_db0_result);
	reg_bits_set(vref_address_1,8,8,read_phy0_result.deye_vref_db0_result);
	ddrc_print_scan("\r\n");
}

void ddr_offline_scan_ca(u16 vref_max ,u16 vref_min)
{
	u8 i=0;
	u16 vref_lv=0;
	u8 test_print=0;
	/*print and set best read DQ delay and write DQ delay*/
	//ddr_print_best_para();//print best parameter for read and write
	//ddr_set_best_delay_para();//set best parameter
	//ddr_print_scan_dead_line();
	/*set vrefe for scan ca*/
	reg_bits_set(0x3100010c,12,1,0);

	vref_lv=(store_reboot_value->vref_lv);
	i=store_reboot_value->phy_num;
	for(;i<(sizeof(phy_scan_para_ca)/sizeof(scan_type_parameter));)  //CA only scan PHY0
	{
		bist_start_address = get_bist_address_lp4(i/2,0);
		ddrc_print_scan("\r\nBist start address=");
		ddr_print_u32_data(bist_start_address);

	    if((store_reboot_value->old_phy_num)!=(store_reboot_value->phy_num))
		{
			store_reboot_value->old_phy_num=store_reboot_value->phy_num;//update old phy value
			ddrc_print_scan("\r\nDDR Scan CA Start\r\n");
			ddr_print_scan_dead_line_4x(phy_scan_para_ca[0].scan_num);
			if(phy_scan_para_ca[i].dmc_phy_base==DMC_GUCPHY0_BASE) //Display message
				ddrc_print_scan("PHY0,");
			else
				ddrc_print_scan("PHY1,");
		}

		for(;vref_lv>vref_min;)//VREF
		{
			if((store_reboot_value->old_vref_lv)!=(store_reboot_value->vref_lv))
			{
				store_reboot_value->old_vref_lv=store_reboot_value->vref_lv;//update old vref value
				if((store_reboot_value->vref_lv)!=VREFE_SCAN_AC_MAX)//Align print log
					ddrc_print_scan("     ");
				ddrc_print_scan("VREFE=");
				ddrc_print_scan(uint8tochar(vref_lv&0xff));
				ddrc_print_scan(":");
			}

			if((LP4X_ca_training_vref > 0x1D) &&(LP4X_ca_training_vref <0x40))
			{
				if(vref_lv == 0x54)
					vref_lv = 0x32;
			}
			else
			{
				if(vref_lv == 0x3F)
					vref_lv = 0x1D;
			}

			ddr_scan_set_ca_vref_lpddr4(vref_lv);/*set vref value for LPDDR4*/

			ddr_offline_scan_parameter_ca(phy_scan_para_ca[i],vref_lv);
			if((first_pass==0)&&(last_pass==0))//Try this test
			{
				store_reboot_value->window_fail_flag=1;/*Restart Dram Power & Power*/
			}
			param_to_pass_boundary_print();//print boundary
			ddr_get_best_delay_para(i,vref_lv,&(store_reboot_value->ca_best_para));//store best parameter
			first_pass=0;//Reset rom first_pass&last_pass Value  -test
			last_pass=0;
			ddrc_print_scan("\r\n");
			store_reboot_value->scan_x=0;
			vref_lv--;
			store_reboot_value->vref_lv=vref_lv;
		}
		/*Restore some variable*/
		store_reboot_value->vref_lv=VREFE_DAC_MAX;
		vref_lv=VREFE_DAC_MAX;
		i=i+1;
		first_pass=0;
		last_pass=0;
		store_reboot_value->phy_num=i;
	}
	reg_bits_set(0x3100010c,12,1,1);
}

/***************************/
/**USE FOR Choose Rank0 &Rank1 **/
/***************************/
void ddr_scan_choose_rank(u32 rank_number)
{
	u32 temp_dmc;
	u64 ddr_size;

	sdram_chip_whole_size(&ddr_size);
	if((rank_number == 1) && ddr_size > 0x140000000)
	{
		rank_configure[rank_number].linear_1 = 0;
		rank_configure[rank_number].interleave_base = 0;
	}
	DDRC_R1P1_REG_INFO_PTR pdmc = (DDRC_R1P1_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	/*1¡¢Change interleave mode*/
	temp_dmc=pdmc->dmc_dcfg17;
	temp_dmc = u32_bits_set(temp_dmc, 24, 3, rank_configure[rank_number].interleave_mode);
	pdmc->dmc_dcfg17=temp_dmc;
	/*2¡¢Change linear 0 & 1*/
	temp_dmc=pdmc->dmc_dcfg18;
	temp_dmc = u32_bits_set(temp_dmc, 0, 14, rank_configure[rank_number].linear_0);
	temp_dmc = u32_bits_set(temp_dmc, 16, 14, rank_configure[rank_number].linear_1);
	pdmc->dmc_dcfg18=temp_dmc;
	/*3¡¢Change interleave base*/
	temp_dmc=pdmc->dmc_dcfg20;
	temp_dmc=u32_bits_set(temp_dmc, 0, 14, rank_configure[rank_number].interleave_base);
	pdmc->dmc_dcfg20=temp_dmc;
	/*4¡¢Change bist start*/
	/*Change Global Variable so bist.c shout update this address*/
	bist_start_address = rank_configure[rank_number].bist_start;
	/*Print*/

	if (store_reboot_value->SwitchRankTrainingFlag==1)/*Control only scan one time*/
	{
		/*Print current choose rank*/
		ddrc_print_scan("\r\n\r\n@@@@@@@@@@@@@@@@@@@@@RANK=0x");
		ddrc_print_scan(uint8tochar(store_reboot_value->rank_loop_num));
		ddrc_print_scan(" DDR SCAN!!@@@@@@@@@@@@@@@@@@@@@\r\n\r\n");
		ddrc_print_scan("\r\nInterleaveMode=");
		ddr_print_u32_data(((pdmc->dmc_dcfg17)>>24)&0x7);
		ddrc_print_scan("\tLinear0=");
		ddr_print_u32_data((pdmc->dmc_dcfg18)&0x3fff);
		ddrc_print_scan("\tLinear1=");
		ddr_print_u32_data(((pdmc->dmc_dcfg18)>>16)&0x3fff);
		ddrc_print_scan("\tInterleaveBase=");
		ddr_print_u32_data((pdmc->dmc_dcfg20)&0x3fff);
		/*Print choose rank register,if you need*/
	}
    /*Training*/
	if (store_reboot_value->SwitchRankTrainingFlag==1)
	{
		store_reboot_value->SwitchRankTrainingFlag=0;/*Avoid repeat _start()*/
		//_start();/*Convert rank Repeat training*/
	}
	/*Print Training Result*/
	if (store_reboot_value->RankTrainingPrintFlag==1)
	{
		store_reboot_value->RankTrainingPrintFlag=0;
		ddr_scan_get_training_printresult(rank_number);
	}
}
/*Use for change vdd repeat dump register*/
static void ddr_scan_clear_minmax(void)
{
  //clear min/max
	reg_bits_set((DMC_GUCPHY0_BASE+0x340),29,1,1);
	reg_bits_set((DMC_GUCPHY0_BASE+0x340),29,1,0);
	reg_bits_set((DMC_GUCPHY1_BASE+0x340),29,1,1);
	reg_bits_set((DMC_GUCPHY1_BASE+0x340),29,1,0);
}
/*Reset store 0x80000 parameter*/
void ddr_scan_reset_rom_parameter()
{
/*Delay line set*/
	store_reboot_value->rom_start_flag=0xaa;
	store_reboot_value->vref_lv=VREFE_SCAN_AC_MAX;//VREFE_DAC_MAX;
	store_reboot_value->scan_x=0;
	store_reboot_value->old_vref_lv=0;
	store_reboot_value->phy_num=0;
	store_reboot_value->old_phy_num=2;//Any value except 0
	store_reboot_value->window_fail_flag=0;
	store_reboot_value->read_write_end_flag=0;
	pass_flag=1;
	fail_flag=1;
	/*VDD SCAN parameter initial*/
	store_reboot_value->new_vddq=VDDQ_MAX;
	store_reboot_value->old_vddq=0;
	store_reboot_value->new_vddcore=VDDCORE_MAX;
	store_reboot_value->old_vddcore=0;
	store_reboot_value->print_vddcore_training_flag=0;
	store_reboot_value->print_vddq_training_flag=0;
	/*Convert Rank */
	store_reboot_value->RankTrainingPrintFlag=1;/*control print training result if change rank*/
	store_reboot_value->SwitchRankTrainingFlag=1;/*Control training if change rank*/
}
/*******************************
*Name:ddr_offline_scan_seq
*Function:Main Sacn sequence   scan rd¡¢wr and ca
*Parameter In :NULL
*Parameter Out:NULL
********************************/
void ddr_offline_scan_seq(int rank)
{
	u32 back_register_0=0;
	u32 back_register_1=0;
	u32 i,size;
	u32 tmp, val;
	LPDDR4_ODT_CFG * p_odt_cfg;
	switch(ddr_chip_cur.chip_type)
	{
		case LPDDR4:
			p_odt_cfg = lpddr4_odt_cfg;
			break;
		case LPDDR4X:
			p_odt_cfg = lpddr4x_odt_cfg;
			break;
		default:
			break;
	}
	reg_bits_set(0x322800b0,8,1,0);//Enable address 0x800000 space
	reg_bits_set(0x32280544,5,1,0);
	memset(&read_dac_para,0,sizeof(read_dac_para));
	memset(&read_op_para,0,sizeof(read_op_para));
	memset(&write_dac_para,0,sizeof(write_dac_para));
	REG32(0x31000124)=0;
	dmc_sprd_delay(2);//2us

	if(store_reboot_value->read_write_end_flag==0)//Avoid scan ca repeat call read & write function
	{
#ifdef DDR_SCAN_READ
		size = sizeof(scan_rd_odt_vref_high)/sizeof(scan_rd_odt_vref_high[0]);
		tmp = VREFI_OP_MAX;
		val = p_odt_cfg[freq_sel].mr11;
		for(i = 0;i < size;i++)
		{
			if(scan_rd_odt_vref_high[i].odt ==  (val & 0x7))
			{
				tmp = scan_rd_odt_vref_high[i].vref;
					break;
			}
		}

		vref_address_0=DMC_GUCPHY0_BASE+vrefi_offset[freq_sel];
		vref_address_1=DMC_GUCPHY1_BASE+vrefi_offset[freq_sel];
		back_register_0=REG32(vref_address_0);
		back_register_1=REG32(vref_address_1);
		ddrc_print_scan("\r\nScan read   OP mode start!\r\n");
		ddr_offline_scan_rd(tmp,VREFI_OP_MIN,&read_op_para,rank);
		ddrc_print_scan("\r\nScan read   OP mode end!\r\n");
#ifdef PERBIT_SCAN
		ddrc_print_scan("\r\nread   OP mode PERBIT start!\r\n");
		for(i = 0; i < 32; i++)
		{
			ddrc_print_scan("\r\nbit:");
			ddr_print_u32_data(i);
			ddrc_print_scan("\r\n");
			bit_mask_num = (1<<i);
			ddr_offline_scan_rd(tmp,VREFI_OP_MIN,&read_op_para,rank);
		}
		bit_mask_num = 0xFFFF;
		ddrc_print_scan("\r\nread   OP mode PERBIT end!\r\n");
#endif
		REG32(vref_address_0)=back_register_0;
		REG32(vref_address_1)=back_register_1;
		dmc_sprd_delay(20);//20us
#endif

#ifdef DDR_SCAN_WRITE
		size = sizeof(scan_wr_odt_vref_high)/sizeof(scan_wr_odt_vref_high[0]);
		tmp = DMC_GUCPHY0_BASE + freq_sel *20*4;
		val = __raw_readl(tmp + 0x9*4);
		tmp = VREFE_DAC_MAX;
		for(i = 0;i < size;i++)
		{
			if(scan_wr_odt_vref_high[i].odt ==  (val & 0x7))
			{
				tmp = scan_wr_odt_vref_high[i].vref;
					break;
			}
		}

		ddrc_print_scan("\r\nScan write   DAC mode start!\r\n");
		ddr_offline_scan_wr(tmp,VREFE_DAC_MIN,&write_dac_para,rank);
		ddrc_print_scan("\r\nScan write   DAC mode end!\r\n");
#ifdef PERBIT_SCAN
		ddrc_print_scan("\r\nwrite	DAC mode PERBIT start!\r\n");
		for(i = 0; i < 32; i++)
		{
			ddrc_print_scan("\r\nbit:");
			ddr_print_u32_data(i);
			ddrc_print_scan("\r\n");
			bit_mask_num = (1<<i);
			ddr_offline_scan_wr(tmp,VREFE_DAC_MIN,&write_dac_para,rank);
		}
		bit_mask_num = 0xFFFF;
		ddrc_print_scan("\r\nwrite	DAC mode PERBIT end!\r\n");
#endif
		dmc_sprd_delay(20);//20us
		ddr_print_all_best_para();
#endif
		store_reboot_value->read_write_end_flag=1;
	}

#ifdef DDR_SCAN_CA
	ddr_offline_scan_ca(CA_SCAN_MAX,CA_SCAN_MIN);//Debug for 0xf0 Normal Set:(VREFE_DAC_MAX,VREFE_DAC_MIN);
	ddr_print_ca_best_para(&(store_reboot_value->ca_best_para));
#endif
}
/**************************************************
 *Function:Loop Adjust vddq&vddcore
 *          to ddr read&write&ca scan
 **************************************************/
int scan_init_times = 0;

/*No vdd scan*/
void ddr_scan_vdd_seq(void)
{
	u32 freq;
	u64 ddr_size;
	u32 cs_num;


	if(scan_init_times == 0)
		scan_init_times = 1;
	else
		return;
	dmc_ctrl_reg_unlock();

	cs_num = sdram_chip_cs_num();
	sdram_chip_whole_size(&ddr_size);

	rank_configure[0].linear_1 = (ddr_size/2) >> 20;
	rank_configure[1].linear_1 = (ddr_size/2) >> 20;

	//regulator_set_voltage("vddcore",950);
	//u32 vddq,vddcore;
	reg_bits_set(0x322800b0,8,1,0);//Enable address 0x800000 space
	reg_bits_set(0x32280544,5,1,0);

	REG32(0x31000124)=0;
	reg_bits_set(0x3100010c,12,1,1);
	freq_sel = (REG32(0x3100012c) >> 8) & 0x7;//get freq for register
	freq = find_ddr_freq(freq_sel);

	dmc_mrr(CMD_CS_0, 14, &LP4_write_training_vref, 10000);
	LP4_write_training_vref=LP4_write_training_vref&0x7f;
	dmc_mrr(CMD_CS_0, 12, &LP4X_ca_training_vref, 10000);
	LP4X_ca_training_vref=LP4X_ca_training_vref&0x7f;

	if(store_reboot_value->rom_start_flag != 0xaa)
	{
		memset(store_reboot_value,0,sizeof(rom_value));//Initial rom arear
		ddr_scan_reset_rom_parameter(); /*Reset Store 0x800000 parameter*/
		store_reboot_value->rank_loop_num = 0; /*Rank loop,this reset only this valided*/
		/*RANK SCAN parameter initial*/
		ddrc_print_scan("Current SCK=");
		ddr_print_u32_dec_data(freq);
		ddrc_print_scan("\r\n");
		ddrc_print_scan("ddr type=");
		if(ddr_chip_cur.chip_type == LPDDR4)
			ddrc_print_scan("LPDDR4");
		else if(ddr_chip_cur.chip_type == LPDDR4X)
			ddrc_print_scan("LPDDR4X");
		else
			ddrc_print_scan("LPDDR4Y");
		/*step 1. Start SDRAM Init*/
		/*step 2. read out Initial training result and print*/
		ddr_scan_get_training_printresult(store_reboot_value->rank_loop_num);
		ddrc_print_scan("\r\nLp4 Write vref training Value=");
		ddr_print_u32_data(LP4_write_training_vref);
		ddrc_print_scan("\tCA VREF Training Value=");
		ddr_print_u32_data(LP4X_ca_training_vref);
		ddrc_print_scan("\r\n");
		ddr_dump_read_reg(DMC_GUCPHY0_BASE, DMC_GUCPHY1_BASE);
	}

	for(;store_reboot_value->rank_loop_num < cs_num;store_reboot_value->rank_loop_num++)/*LP4X*/
	{
		ddr_scan_choose_rank(store_reboot_value->rank_loop_num);/*Choose rank*/
		ddr_offline_scan_seq(store_reboot_value->rank_loop_num);
		ddr_scan_reset_rom_parameter();//reset store 0x800000 parameter
		if (ddr_chip_cur.cs_num == 1)
			break;
	}
	/*Judge  dump register*/
	ddr_dump_read_reg(DMC_GUCPHY0_BASE, DMC_GUCPHY1_BASE);

	ddrc_print_scan("scan end\r\n");
	while(1);
}
