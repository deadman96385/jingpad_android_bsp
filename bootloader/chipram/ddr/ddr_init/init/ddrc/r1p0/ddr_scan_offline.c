#include "sci_types.h"
#include "ddrc_r1p0.h"
#include "ddrc_r1p0_phy.h"
#include "ddrc_r1p0_common.h"
#include "ddr_scan_offline.h"
#include "debug.h"

#ifdef DDR_SCAN_ENABLE
#define REG32(x)	(*((volatile unsigned int*)(x)))

#define PASS dmc_print_str("\t0x0")
#define FAIL dmc_print_str("\t0xf")
#define PASS_SYMBOL dmc_print_str("*")
#define FAIL_SYMBOL dmc_print_str(".")
#define FAIL_VREF_TRAINING_STRAT_SYMBOL dmc_print_str("S")
#define FAIL_VREF_TRAINING_END_SYMBOL dmc_print_str("E")
#ifndef DDR_SCAN_PRINT_THROUGH_LINE
#define PASS_VREF_TRAINING_SYMBOL dmc_print_str("*")
#else
#define PASS_VREF_TRAINING_SYMBOL dmc_print_str("o")
#endif
#define PASS_VREF_DELAY_TRAINING_SYMBOL dmc_print_str("M")
#define PASS_VREF_TRAINING_STRAT_SYMBOL dmc_print_str("S")
#define PASS_VREF_TRAINING_END_SYMBOL dmc_print_str("E")
#define THROUGH_EYE_SCOPE dmc_print_str("|")
#define PARAM_SCAN_END  dmc_print_str("\r\n0x343434")
#define SCAN_LOG_START  dmc_print_str("\r\n0x71747172")
#define SCAN_LOG_END    dmc_print_str("\r\n0x656E6464")
extern  _start();
extern int sdram_init(void);
extern u16 dram_init_powerup_times;//define for ddrc_r1p0_lpddrx.c  YOu must set this variable to 0 before Repeat call sdram_init()
/*Store Rank0 Training result used for ddr scan*/
extern RANK0_TRAINING_SCAN rank0_training_result;
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

u8 ddr_scan_transfer_flag=1;//avoid repeat call ddr_offline_scan_seq function ,use for ddrc_r1p0.c
u32 freq_sel;//read FREQ
u32 vref_address_0=0; //store scan read vreaf address
u32 vref_address_1=0;
u8 scan_bist_pattern=2;//bist pattern  2-LFSR
uint32 LP4_write_training_vref=0;/*write training value to read MR14 for LPDDR4X*/
u32 LP4X_ca_training_vref=0;/*CA training value to read MR12 for LPDDR4X*/
//best_delay_para best_delay;//store best delay for read and write
/*Store scan best parameter*/
best_para read_dac_para;
best_para read_op_para;
best_para write_dac_para;
/*Bist start address*/
u32 bist_start_address=0;/*use for dual rank set bist start address*/
//rom_value *store_reboot_value=&store_flag;
u32 ddr_scan_repeat_call_flag=0;//0:Allow repeat call 1:Not repeat call

/*HW Training Result*/
/*static struct ca_result	    ca_phy0_result;
static struct ca_result	    ca_phy1_result;*/
static struct read_result	read_phy0_result;
static struct read_result	read_phy1_result;
static struct write_result  write_phy0_result;
static struct write_result  write_phy1_result;

#define ca_phy0_result (store_reboot_value->ca_phy0_result)
#define ca_phy1_result (store_reboot_value->ca_phy1_result)

void ddr_print_set_register(void);
static void ddr_print_scan_dead_line(void);
static void ddr_print_scan_dead_line_4x(int num);


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

void ca_result_get(u32 phy_base, struct ca_result *phy_ca_result)
{
	u32 data_tmp;
	if (store_reboot_value->rank_loop_num==0)
	{
		if (phy_base == DMC_GUCPHY0_BASE)
			data_tmp = rank0_training_result.PHY0_CA_E6;
		else
			data_tmp = rank0_training_result.PHY1_CA_E6;
	}else
	{
		data_tmp = __raw_readl(phy_base + 0xe6 * 4); //0x0398 CA training coarse and fine delay trainining result and ca vref result
	}

	phy_ca_result->vref_dram_ca_result = (data_tmp >> 24) & 0x3f;
	phy_ca_result->ca_pass_window = (data_tmp >> 16) & 0xFF;
	phy_ca_result->ca_result_cfg_fine = (data_tmp >> 8) & 0xFF;
	phy_ca_result->ca_result_cfg_coarse = data_tmp & 0xff;
	//Update Eye Window Start & End
	phy_ca_result->ca_eye_window_start=TRAINGING_EYE_START_VALUE(phy_ca_result->ca_result_cfg_fine,phy_ca_result->ca_pass_window);
	phy_ca_result->ca_eye_window_end = TRAINGING_EYE_END_VALUE(phy_ca_result->ca_result_cfg_fine,phy_ca_result->ca_pass_window);
}

void read_result_get(u32 phy_base, struct read_result *phy_read_result)
{
	u32 data_tmp;
	if (store_reboot_value->rank_loop_num==0)
	{
		if (phy_base == DMC_GUCPHY0_BASE)
			data_tmp = rank0_training_result.PHY0_READ_EA;
		else
			data_tmp = rank0_training_result.PHY1_READ_EA;

	}else
	{
		/*Please uncommon this line if RANK1 Read training open in ddr init */
		//data_tmp = __raw_readl(phy_base + 0xea*4);//0x03a8 // read vref training result
		/*Rank0 Training Result used for Rank1. Because Rank1 Read Training Currently Closed */
		if (phy_base == DMC_GUCPHY0_BASE)
			data_tmp = rank0_training_result.PHY0_READ_EA;
		else
			data_tmp = rank0_training_result.PHY1_READ_EA;
	}

	phy_read_result->deye_vref_db0_result = data_tmp & 0xff;
//	phy_read_result->deye_vref_db1_result = (data_tmp >> 8) & 0xff;
	if (store_reboot_value->rank_loop_num==0)
	{
		if (phy_base == DMC_GUCPHY0_BASE)
			data_tmp = rank0_training_result.PHY0_READ_EB;
		else
			data_tmp = rank0_training_result.PHY1_READ_EB;
	}else
	{
		/*Please uncommon this line if RANK1 Read training open in ddr init */
		//data_tmp = __raw_readl(phy_base + 0xeb*4);
		/*Rank0 Training Result used for Rank1. Because Rank1 Read Training Currently Closed */
		if (phy_base == DMC_GUCPHY0_BASE)
			data_tmp = rank0_training_result.PHY0_READ_EB;
		else
			data_tmp = rank0_training_result.PHY1_READ_EB;
	}

	phy_read_result->rd_db1_dqsn = (data_tmp >> 24) & 0xff;
	phy_read_result->rd_db0_dqsn = (data_tmp >> 16) & 0xff;
	phy_read_result->rd_db1_dqs = (data_tmp >> 8) & 0xff;
	phy_read_result->rd_db0_dqs = data_tmp & 0xff;
	if (store_reboot_value->rank_loop_num==0)
	{
		if (phy_base == DMC_GUCPHY0_BASE)
			data_tmp = rank0_training_result.PHY0_READ_ED;
		else
			data_tmp = rank0_training_result.PHY1_READ_ED;
	}else
	{
		/*Please uncommon this line if RANK1 Read training open in ddr init */
		//data_tmp = __raw_readl(phy_base + 0xed*4);//0x03b4 read eye pass window
		/*Rank0 Training Result used for Rank1. Because Rank1 Read Training Currently Closed */
		if (phy_base == DMC_GUCPHY0_BASE)
			data_tmp = rank0_training_result.PHY0_READ_ED;
		else
			data_tmp = rank0_training_result.PHY1_READ_ED;
	}

	phy_read_result->db1_rdq_pass_window = (data_tmp >> 8) & 0xFF; //mlb_train_db0_deye_pass_window_cfg_db1
	phy_read_result->db0_rdq_pass_window = data_tmp & 0xFF;///mlb_train_db0_deye_pass_window_cfg_db0

	//Calcullation read training eye window start and end
	phy_read_result->rd_db0_eye_window_start=TRAINGING_EYE_START_VALUE(phy_read_result->rd_db0_dqs,phy_read_result->db0_rdq_pass_window);
	phy_read_result->rd_db0_eye_window_end  = TRAINGING_EYE_END_VALUE(phy_read_result->rd_db0_dqs,phy_read_result->db0_rdq_pass_window);
	phy_read_result->rd_db1_eye_window_start=TRAINGING_EYE_START_VALUE(phy_read_result->rd_db1_dqs,phy_read_result->db1_rdq_pass_window);
	phy_read_result->rd_db1_eye_window_end  = TRAINGING_EYE_END_VALUE(phy_read_result->rd_db1_dqs,phy_read_result->db1_rdq_pass_window);
}

void write_result_get(u32 phy_base, struct write_result *phy_write_result)
{
	u32 data_tmp;
	if (store_reboot_value->rank_loop_num==0)
	{
		if (phy_base == DMC_GUCPHY0_BASE)
			data_tmp = rank0_training_result.PHY0_WRITE_E9;
		else
			data_tmp = rank0_training_result.PHY1_WRITE_E9;
	}else
	{
		data_tmp = __raw_readl(phy_base + 0xe9*4);//0x03a4 rddv_sel value and dram vref training result
	}

	phy_write_result->vref_dram_adj_result = (data_tmp >> 24) & 0x3F;//
	if (store_reboot_value->rank_loop_num==0)
	{
		if (phy_base == DMC_GUCPHY0_BASE)
			data_tmp = rank0_training_result.PHY0_WRITE_EC;
		else
			data_tmp = rank0_training_result.PHY1_WRITE_EC;
	}else
	{
		data_tmp = __raw_readl(phy_base + 0xec*4);//0x03b0 write DQS to DQ coarse and fine phase training result
	}
	phy_write_result->db1_wdq_bt_result = (data_tmp >> 20) & 0xF;//**_cfg_db1_wdq
	phy_write_result->db0_wdq_bt_result = (data_tmp >> 16) & 0xF;//**_cfg_db0_wdq
	phy_write_result->db1_wdq_result = (data_tmp >> 8) & 0xFF;//**_cfg_db1_wrdeye
	phy_write_result->db0_wdq_result = data_tmp & 0xFF;//**_cfg_db0_wrdeye
	if (store_reboot_value->rank_loop_num==0)
	{
		if (phy_base == DMC_GUCPHY0_BASE)
			data_tmp = rank0_training_result.PHY0_WRITE_EE;
		else
			data_tmp = rank0_training_result.PHY1_WRITE_EE;
	}else
	{
		data_tmp = __raw_readl(phy_base + 0xee*4);//0x03b8 read eye pass window
	}

	phy_write_result->db1_wdq_pass_window = (data_tmp >> 8) & 0xFF; //mlb_train_db0_deye_pass_window_cfg_db1
	phy_write_result->db0_wdq_pass_window = data_tmp & 0xFF;///mlb_train_db0_deye_pass_window_cfg_db0
	#ifdef DDR_SCAN_LPDDR4
	phy_write_result->db0_wdq_result=phy_write_result->db0_wdq_result+0x100;
	phy_write_result->db1_wdq_result=phy_write_result->db1_wdq_result+0x100;
	#endif
	//Calcullation write training eye window start and end
	phy_write_result->wr_db0_eye_window_start = TRAINGING_EYE_START_VALUE(phy_write_result->db0_wdq_result, phy_write_result->db0_wdq_pass_window);
	phy_write_result->wr_db0_eye_window_end  = TRAINGING_EYE_END_VALUE(phy_write_result->db0_wdq_result, phy_write_result->db0_wdq_pass_window);
	phy_write_result->wr_db1_eye_window_start = TRAINGING_EYE_START_VALUE(phy_write_result->db1_wdq_result, phy_write_result->db1_wdq_pass_window);
	phy_write_result->wr_db1_eye_window_end  = TRAINGING_EYE_END_VALUE(phy_write_result->db1_wdq_result, phy_write_result->db1_wdq_pass_window);

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
	//reg_bits_set(phy_base + 0xb2*4, 2, 1, 0);//reg_cal_update_rule_cfg_ca_manual_mode
	//reg_bits_set(phy_base + 0xb2*4, 2, 1, 1);//reg_cal_update_rule_cfg_ca_manual_mode

}

void ctrl_soft_command(void)
{
	u32 data_tmp;
	data_tmp = reg_bits_get(0x30000124, 24, 2);
	if ( data_tmp != 0x3)
	{
		dmc_dosoft_cmd_setting(0x80100000);//dsoft_pre_all
		dmc_dosoft_cmd_setting(0x80200000);//dsoft_auto_ref
		dmc_dosoft_cmd_setting(0x80400000);//dsoft_self_ref
	}

}

void ddr_print_scan_head(void)
{
	//print parameters--- ddr scan script head
	#ifdef DRAM_LPDDR3
	dmc_print_str("\r\n@@@@-1");
	#else
	dmc_print_str("\r\n@@@@-2");
	#endif
	dmc_print_str("\r\n**************************");
	dmc_print_str("\r\n*********0x28400000*******");
	#ifdef DDR_SCAN_LPDDR3
	dmc_print_str("\r\n*******0x33333333*********");
	#endif
	#ifdef DDR_SCAN_LPDDR4
	dmc_print_str("\r\n*******0x44444444*********");
	#endif
}
void ddr_dump_read_reg(u32 phy0_base,u32 phy1_base)
{
	int iLoop=0;
	u32 uaddress=0;
	dmc_print_str("\r\nPHY0 Rd Only Register:");
	dmc_print_str("\t\t");
	dmc_print_str("PHY1 Rd Only Register:\r\n");
	for(iLoop=0;iLoop<=((RD_ONLY_OFFSET_END-RD_ONLY_OFFSET_START)/4);iLoop++)
	{
		   //phy_base
		uaddress=phy0_base+RD_ONLY_OFFSET_START+4*iLoop;
		ddr_print_u32_data(uaddress);
		dmc_print_str("=");
		ddr_print_u32_data(REG32(uaddress));
		dmc_print_str("\t");
		uaddress=phy1_base+RD_ONLY_OFFSET_START+4*iLoop;
		ddr_print_u32_data(uaddress);
		dmc_print_str("=");
		ddr_print_u32_data(REG32(uaddress));
		dmc_print_str("\r\n");
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
   dmc_print_str("\t:first_pass:0x");
   dmc_print_str(uint8tochar(first_pass>>8));
   dmc_print_str(uint8tochar(first_pass));

   /*Print last pass*/
   last_pass_percent=((last_pass*1000)/512)-((last_pass/512)*1000);
   dmc_print_str("\tlast_pass:0x");
   dmc_print_str(uint8tochar(last_pass>>8));
   dmc_print_str(uint8tochar(last_pass));

   /*Print pass delta*/
   pass_delta=last_pass-first_pass;
   dmc_print_str("\tpass_delta:0x");
   dmc_print_str(uint8tochar(pass_delta>>8));
   dmc_print_str(uint8tochar(pass_delta));

    /*Print center pass*/
   center_pass=(first_pass+last_pass)/2;
   dmc_print_str("\tcenter:0x");
   dmc_print_str(uint8tochar(center_pass>>8));
   dmc_print_str(uint8tochar(center_pass));

}
/*******************************
*Name:ddr_scan_get_training_printresult
*Function:Get training after SDRAM Initial
*         and print result
*Parameter In :NULL
*Parameter Out:NULL
********************************/
void ddr_scan_get_training_printresult(void)
{
	uint32 i=0;
	u32 * pResult;
	dmc_print_str("\r\n************Training Delay Line**************\r\n");
	/*Get gucphy0 CA Result and Print result*/
	ca_result_get( DMC_GUCPHY0_BASE , &ca_phy0_result);
	dmc_print_str("\r\ndmc_gucphy0_ca_result\r\n");
	pResult=&(ca_phy0_result.vref_dram_ca_result);
	for(i=0;i<4;i++)
	{
		switch (i)
		{
			case 0:dmc_print_str("vref_dram_ca_re     :");break;
			case 1:dmc_print_str("ca_pass_window      :");break;
			case 2:dmc_print_str("ca_result_cfg_fine  :");break;
			case 3:dmc_print_str("ca_result_cfg_coarse:");break;
			case 4:dmc_print_str("ca_eye_window_start :");break;
			case 5:dmc_print_str("ca_eye_window_end   :");break;
		}
		ddr_print_u32_data(pResult[i]);
	}
	/*Get gucphy1 CA Result and Print result*/
	ca_result_get( DMC_GUCPHY1_BASE , &ca_phy1_result);
	dmc_print_str("\r\ndmc_gucphy1_ca_result\r\n");
	pResult=&(ca_phy1_result.vref_dram_ca_result);
	for(i=0;i<(sizeof(ca_phy1_result)/sizeof(u32));i++)
	{
		switch (i)
		{
			case 0:dmc_print_str("vref_dram_ca_result :");break;
			case 1:dmc_print_str("ca_pass_window      :");break;
			case 2:dmc_print_str("ca_result_cfg_fine  :");break;
			case 3:dmc_print_str("ca_result_cfg_coarse:");break;
			case 4:dmc_print_str("ca_eye_window_start :");break;
			case 5:dmc_print_str("ca_eye_window_end   :");break;
		}
		ddr_print_u32_data(pResult[i]);
	}
    /*Get read GUCPHY0 result*/
	read_result_get(DMC_GUCPHY0_BASE, &read_phy0_result);
	dmc_print_str("\r\nread_phy0_result\r\n");
	pResult=&(read_phy0_result.deye_vref_db0_result);
	for(i=0;i<sizeof(read_phy0_result)/sizeof(u32);i++)
	{
		switch (i)
		{
			case 0:dmc_print_str("deye_vref_db_result  :");break;
//			case 1:dmc_print_str("deye_vref_db1_result:");break;
			case 1:dmc_print_str("rd_db0_dqsn          :");break;
			case 2:dmc_print_str("rd_db1_dqsn          :");break;
			case 3:dmc_print_str("rd_db0_dqs           :");break;
			case 4:dmc_print_str("rd_db1_dqs           :");break;
			case 5:dmc_print_str("db0_rdq_pass_window  :");break;
			case 6:dmc_print_str("db1_rdq_pass_window  :");break;
			case 7:dmc_print_str("rd_db0_window_start  :");break;
			case 8:dmc_print_str("rd_db0_window_end    :");break;
			case 9:dmc_print_str("rd_db1_window_start  :");break;
			case 10:dmc_print_str("rd_db1_window_end    :");break;
		}
		ddr_print_u32_data(pResult[i]);
	}
	/*Get read GUCPHY1 result*/
	read_result_get(DMC_GUCPHY1_BASE, &read_phy1_result);
	dmc_print_str("\r\nread_phy1_result\r\n");
	pResult=&(read_phy1_result.deye_vref_db0_result);
	for(i=0;i<(sizeof(read_phy1_result)/sizeof(u32));i++)
	{
		switch (i)
		{
			case 0:dmc_print_str("deye_vref_dbresult  :");break;
//			case 1:dmc_print_str("deye_vref_db1_result:");break;
			case 1:dmc_print_str("rd_db0_dqsn         :");break;
			case 2:dmc_print_str("rd_db1_dqsn         :");break;
			case 3:dmc_print_str("rd_db0_dqs          :");break;
			case 4:dmc_print_str("rd_db1_dqs          :");break;
			case 5:dmc_print_str("db0_rdq_pass_window :");break;
			case 6:dmc_print_str("db1_rdq_pass_window :");break;
			case 7:dmc_print_str("rd_db0_window_start :");break;
			case 8:dmc_print_str("rd_db0_window_end   :");break;
			case 9:dmc_print_str("rd_db1_window_start :");break;
			case 10:dmc_print_str("rd_db1_window_end   :");break;
		}
		ddr_print_u32_data(pResult[i]);
	}
   /*Get write phy0 result*/
	write_result_get(DMC_GUCPHY0_BASE, &write_phy0_result);
	dmc_print_str("\r\nwrite_phy0_result\r\n");
	pResult=&(write_phy0_result.vref_dram_adj_result);
	for(i=1;i<(sizeof(write_phy0_result)/sizeof(u32));i++)
	{
		switch (i)
		{
			case 0:dmc_print_str("vref_dram_adj_result:");break;
			case 1:dmc_print_str("db0_wdq_bt_result   :");break;
			case 2:dmc_print_str("db1_wdq_bt_result   :");break;
			case 3:dmc_print_str("db0_wdq_result      :");break;
			case 4:dmc_print_str("db1_wdq_result      :");break;
			case 5:dmc_print_str("db0_wdq_pass_window :");break;
			case 6:dmc_print_str("db1_wdq_pass_window :");break;
			case 7:dmc_print_str("wr_db0_window_start :");break;
			case 8:dmc_print_str("wr_db0_window_end   :");break;
			case 9:dmc_print_str("wr_db1_window_start :");break;
			case 10:dmc_print_str("wr_db1_window_end   :");break;
		}
		ddr_print_u32_data(pResult[i]);
        }

   /*Get write phy1 result*/
	write_result_get(DMC_GUCPHY1_BASE, &write_phy1_result);
	dmc_print_str("\r\nwrite_phy1_result\r\n");
	pResult=&(write_phy1_result.vref_dram_adj_result);
	for(i=1;i<(sizeof(write_phy1_result)/sizeof(u32));i++)
	{
		switch (i)
		{
			case 0:dmc_print_str("vref_dram_adj_result:");break;
			case 1:dmc_print_str("db0_wdq_bt_result   :");break;
			case 2:dmc_print_str("db1_wdq_bt_result   :");break;
			case 3:dmc_print_str("db0_wdq_result      :");break;
			case 4:dmc_print_str("db1_wdq_result      :");break;
			case 5:dmc_print_str("db0_wdq_pass_window :");break;
			case 6:dmc_print_str("db1_wdq_pass_window :");break;
			case 7:dmc_print_str("wr_db0_window_start :");break;
			case 8:dmc_print_str("wr_db0_window_end   :");break;
			case 9:dmc_print_str("wr_db1_window_start :");break;
			case 10:dmc_print_str("wr_db1_window_end   :");break;
		}
		ddr_print_u32_data(pResult[i]);
	}
	dmc_print_str("\r\n");

	/*Print PU/PD PVT Calibration Result*/
	dmc_print_str("PHY0 PU/PD Calibration Result:\r\n");
	dmc_print_str("PU Calibration Result:");
	ddr_print_u32_data(reg_bits_get(PUPD_PHY0_IOPVT_CALIBRATION_RESULT,0,8));
	dmc_print_str("PD Calibration Result:");
	ddr_print_u32_data(reg_bits_get(PUPD_PHY0_IOPVT_CALIBRATION_RESULT,16,8));
	dmc_print_str("\r\n");
	dmc_print_str("PHY1 PU/PD Calibration Result:\r\n");
	dmc_print_str("PU Calibration Result:");
	ddr_print_u32_data(reg_bits_get(PUPD_PHY1_IOPVT_CALIBRATION_RESULT,0,8));
	dmc_print_str("PD Calibration Result:");
	ddr_print_u32_data(reg_bits_get(PUPD_PHY1_IOPVT_CALIBRATION_RESULT,16,8));
	dmc_print_str("\r\n");
}

/****************************************
*FUNCTION:DDR scan bist for one bit
*OUTPUT:NULL
*IN    :vref_val: Current set vref value
*       deye_vref_result:Training Vref Value
*       db_dqs:Training delay time
*****************************************/

int ddr_print_bist_result(uint32 i,PRINT_BIST_PARA * pPara)
{
    u32 ret=0;
	u8 pattern_i=0;
	u32 ret_sum=0;
	u32 vref_mask=0;
	//step. bist operation and record the pass and fail
#ifdef DDR_SCAN_LOOP_ALL_BIST_PATTERN                       /*Scan three pattern*/
	for(pattern_i=0;pattern_i<3;pattern_i++)//all pattern pass
	{
		scan_bist_pattern=pattern_i;
		if(dmc_ddr_test(0, pattern_i, bist_start_address)==0)//1:faild 0:success
		{
			ret_sum++;
		}
	}
	 if(ret_sum==3)//success
		{  ret=0;}
	 else
		{  ret=1;}
	 ret_sum=0;
#else	/*Only use for one pattern for bist*/
	 if(dmc_ddr_test(0)==0)//1:faild 0:success
		{ ret=0;}
	 else
		{ ret=1;}
#endif
	if(ret)//fail
	{
	#ifdef ENCRPTY_LOG
	FAIL;
	#else
	/*4X scan  write and ca no set bit8 to 1*/
	#ifdef DDR_SCAN_LPDDR4
	if((pPara->type==scan_write) || (pPara->type==scan_ca))
		{vref_mask=0x0;}
	else
		{ vref_mask=0x80;}
	#else
		vref_mask=0x80;//LPDDR3
	#endif
      	/*Distinguish Cmos and diffential mode */
	#ifndef DDR_SCAN_CMOS_MODE
	if ((pPara->scan_vref == pPara->train_vref) && (pPara->train_vref != 0)) //Diffential Mode ScanVREF==Training ,Vref write  need compare fixed Training value was 0xd0
	#else
	if((pPara->scan_vref == (pPara->train_vref | vref_mask)) && (pPara->train_vref != 0)) //Only cmos mode Set biet 8 to 1
	#endif
	{
		#ifdef DDR_SCAN_PRINT_THROUGH_LINE
		if ((i == (pPara->train_dqs + 0x30)) || (i == (pPara->train_dqs - 0x30))) //through  width
			{THROUGH_EYE_SCOPE;}
		else
		if (i == pPara->eye_start) /*Symbol training Start & End Value*/
			FAIL_VREF_TRAINING_STRAT_SYMBOL;
		else if (i == pPara->eye_end)
			FAIL_VREF_TRAINING_END_SYMBOL;
		else
		#endif
		FAIL_SYMBOL;
	}
	else
        {
		#ifdef DDR_SCAN_PRINT_THROUGH_LINE
		if ((i == (pPara->train_dqs + 0x30)) || (i == (pPara->train_dqs - 0x30))) //through  width
		{
			THROUGH_EYE_SCOPE;
		}
		else
		#endif
			FAIL_SYMBOL;
	}
	 /*Update data*/
	if((pPara->pass_flag==0)&&(pPara->fail_flag==1))//Update last_pass
	{
		last_pass=i-1;
		pPara->fail_flag=0;
	}
	if((last_pass-first_pass)<5)//if pass number < 5 Recount first_pass
	{
		pPara->pass_flag=1;
	}
	#endif
	}
	else//success
	{
	#ifdef ENCRPTY_LOG
		PASS;
	#else
	#ifdef DDR_SCAN_LPDDR4
	if((pPara->type==scan_write)|| (pPara->type==scan_ca)) {
		vref_mask=0x0;//Only write
	}else
	{
          vref_mask=0x80;//4x: read & ca
	}
	#else
		vref_mask=0x80;//LPDDR3
	#endif
	#ifndef DDR_SCAN_CMOS_MODE
		if((pPara->scan_vref==pPara->train_vref)&&(pPara->train_vref!=0))//Diffential Mode ScanVREF==Training ,Vref write  need compare fixed Training value was 0xd0
	#else
		if((pPara->scan_vref==(pPara->train_vref|vref_mask))&&(pPara->train_vref!=0))//Only cmos mode Set biet 8 to 1
	#endif
		{
		#ifdef DDR_SCAN_PRINT_THROUGH_LINE
		if ((i == (pPara->train_dqs + 0x30)) || (i == (pPara->train_dqs - 0x30))) //through  width
		{
			THROUGH_EYE_SCOPE;
		} else
		if (i==pPara->eye_start)/*Symbol training Start & End Value*/
			PASS_VREF_TRAINING_STRAT_SYMBOL;
		else if (i == pPara->eye_end)
			PASS_VREF_TRAINING_END_SYMBOL;
		else if (i == pPara->train_dqs)  /*Symbol training Center dqs*/
			PASS_VREF_DELAY_TRAINING_SYMBOL;
		else
		#endif
			PASS_VREF_TRAINING_SYMBOL;
		}else
		{
		#ifdef DDR_SCAN_PRINT_THROUGH_LINE
		if ((i == (pPara->train_dqs + 0x30)) || (i == (pPara->train_dqs - 0x30))) //print through  width
		{
			THROUGH_EYE_SCOPE;
		} else
		#endif
			PASS_SYMBOL;
		}
		/*Update calculation first pass and last pass*/
		if(pPara->pass_flag==1)
		{
			first_pass=i;
			pPara->pass_flag=0;
		}
		if((last_pass<=first_pass)||((last_pass-first_pass)<5))//last_pass not suitable condition,reset collet fail_flag
		{
			 pPara->fail_flag=1;
		}
	#endif
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

	first_pass=0;
	last_pass=0;
	scan_type_parameter temp_parameter=type_para;//Temporarily store
	store_reboot_value->print_bist_para.pass_flag=1;
	store_reboot_value->print_bist_para.fail_flag=1;
	store_reboot_value->print_bist_para.scan_vref=vref_val;
	store_reboot_value->print_bist_para.type = temp_parameter.type;

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
	for (i=0; i<=temp_parameter.scan_num; i=i+X_INCREASE_STEP)
	{
		switch((int)(temp_parameter.type))//Chose scan type
	        {
				case 0: phy_delay_line_set_wr(temp_parameter.dmc_phy_base,i,freq_sel,temp_parameter.data_module);break;
				case 1: phy_delay_line_set_rd(temp_parameter.dmc_phy_base,i,freq_sel,temp_parameter.data_module);break;
				default:dmc_print_str("\r\n************temp_parameter.type is error**********\r\n");
			}
	   //step. bist operation and record the pass and fail
		if(temp_parameter.type==scan_read)
		{
			if((temp_parameter.dmc_phy_base==DMC_GUCPHY0_BASE)&&(temp_parameter.data_module==data_module_0))
			{
				store_reboot_value->print_bist_para.eye_start	=TRAINGING_EYE_START_VALUE(read_phy0_result.rd_db0_dqs, read_phy0_result.db0_rdq_pass_window);
				store_reboot_value->print_bist_para.eye_end 	=TRAINGING_EYE_END_VALUE(read_phy0_result.rd_db0_dqs, read_phy0_result.db0_rdq_pass_window);
				store_reboot_value->print_bist_para.train_dqs	=read_phy0_result.rd_db0_dqs;
				store_reboot_value->print_bist_para.train_vref	=read_phy0_result.deye_vref_db0_result;
			}
			else if((temp_parameter.dmc_phy_base==DMC_GUCPHY0_BASE)&&(temp_parameter.data_module==data_module_1))
			{
				store_reboot_value->print_bist_para.eye_start	=TRAINGING_EYE_START_VALUE(read_phy0_result.rd_db1_dqs, read_phy0_result.db1_rdq_pass_window);
				store_reboot_value->print_bist_para.eye_end 	=TRAINGING_EYE_END_VALUE(read_phy0_result.rd_db1_dqs, read_phy0_result.db1_rdq_pass_window);
				store_reboot_value->print_bist_para.train_dqs	=read_phy0_result.rd_db1_dqs;
				store_reboot_value->print_bist_para.train_vref	=read_phy0_result.deye_vref_db0_result;
			}
			else if((temp_parameter.dmc_phy_base==DMC_GUCPHY1_BASE)&&(temp_parameter.data_module==data_module_0))
			{
				store_reboot_value->print_bist_para.eye_start	=TRAINGING_EYE_START_VALUE(read_phy1_result.rd_db0_dqs, read_phy1_result.db0_rdq_pass_window);
				store_reboot_value->print_bist_para.eye_end 	=TRAINGING_EYE_END_VALUE(read_phy1_result.rd_db0_dqs, read_phy1_result.db0_rdq_pass_window);
				store_reboot_value->print_bist_para.train_dqs	=read_phy1_result.rd_db0_dqs;
				store_reboot_value->print_bist_para.train_vref	=read_phy1_result.deye_vref_db0_result;
			}
			else if((temp_parameter.dmc_phy_base==DMC_GUCPHY1_BASE)&&(temp_parameter.data_module==data_module_1))
			{
				store_reboot_value->print_bist_para.eye_start	=TRAINGING_EYE_START_VALUE(read_phy1_result.rd_db1_dqs, read_phy1_result.db1_rdq_pass_window);
				store_reboot_value->print_bist_para.eye_end 	=TRAINGING_EYE_END_VALUE(read_phy1_result.rd_db1_dqs, read_phy1_result.db1_rdq_pass_window);
				store_reboot_value->print_bist_para.train_dqs	=read_phy1_result.rd_db1_dqs;
				store_reboot_value->print_bist_para.train_vref	=read_phy1_result.deye_vref_db0_result;
			}else
			{
				dmc_print_str("DDR Scan Choose parameter Error!!");
				while (1);
			}
		}
		else if(temp_parameter.type==scan_write)
		{
	#ifdef DDR_SCAN_LPDDR4
			if((temp_parameter.dmc_phy_base==DMC_GUCPHY0_BASE)&&(temp_parameter.data_module==data_module_0))
			{
				store_reboot_value->print_bist_para.eye_start   =TRAINGING_EYE_START_VALUE(write_phy0_result.db0_wdq_result, write_phy0_result.db0_wdq_pass_window);
				store_reboot_value->print_bist_para.eye_end     =TRAINGING_EYE_END_VALUE(write_phy0_result.db0_wdq_result, write_phy0_result.db0_wdq_pass_window);
				store_reboot_value->print_bist_para.train_dqs   =write_phy0_result.db0_wdq_result;
				store_reboot_value->print_bist_para.train_vref  =LP4_write_training_vref;
			}
			else if((temp_parameter.dmc_phy_base==DMC_GUCPHY0_BASE)&&(temp_parameter.data_module==data_module_1))
			{
				store_reboot_value->print_bist_para.eye_start   =TRAINGING_EYE_START_VALUE(write_phy0_result.db1_wdq_result, write_phy0_result.db1_wdq_pass_window);
				store_reboot_value->print_bist_para.eye_end     =TRAINGING_EYE_END_VALUE(write_phy0_result.db1_wdq_result, write_phy0_result.db1_wdq_pass_window);
				store_reboot_value->print_bist_para.train_dqs   =write_phy0_result.db1_wdq_result;
				store_reboot_value->print_bist_para.train_vref  =LP4_write_training_vref;
			}
			else if((temp_parameter.dmc_phy_base==DMC_GUCPHY1_BASE)&&(temp_parameter.data_module==data_module_0))
			{
				store_reboot_value->print_bist_para.eye_start   =TRAINGING_EYE_START_VALUE(write_phy1_result.db0_wdq_result, write_phy1_result.db0_wdq_pass_window);
				store_reboot_value->print_bist_para.eye_end     =TRAINGING_EYE_END_VALUE(write_phy1_result.db0_wdq_result, write_phy1_result.db0_wdq_pass_window);
				store_reboot_value->print_bist_para.train_dqs   =write_phy1_result.db0_wdq_result;
				store_reboot_value->print_bist_para.train_vref  = LP4_write_training_vref;
			}
			else if((temp_parameter.dmc_phy_base==DMC_GUCPHY1_BASE)&&(temp_parameter.data_module==data_module_1))
			{
				store_reboot_value->print_bist_para.eye_start   =TRAINGING_EYE_START_VALUE(write_phy1_result.db1_wdq_result, write_phy1_result.db1_wdq_pass_window);
				store_reboot_value->print_bist_para.eye_end     =TRAINGING_EYE_END_VALUE(write_phy1_result.db1_wdq_result, write_phy1_result.db1_wdq_pass_window);
				store_reboot_value->print_bist_para.train_dqs   =write_phy1_result.db1_wdq_result;
				store_reboot_value->print_bist_para.train_vref  =LP4_write_training_vref;
			}
	#else
			//ddr_print_bist_result(&pass_flag,&fail_flag,i,vref_val,0xd0,0);	 //0x50 bit7-->1 =0xd0
			if((temp_parameter.dmc_phy_base==DMC_GUCPHY0_BASE)&&(temp_parameter.data_module==data_module_0))
			{
				store_reboot_value->print_bist_para.eye_start   =TRAINGING_EYE_START_VALUE(write_phy0_result.db0_wdq_result, write_phy0_result.db0_wdq_pass_window);
				store_reboot_value->print_bist_para.eye_end     =TRAINGING_EYE_END_VALUE(write_phy0_result.db0_wdq_result, write_phy0_result.db0_wdq_pass_window);
				store_reboot_value->print_bist_para.train_dqs   =write_phy0_result.db0_wdq_result;
				store_reboot_value->print_bist_para.train_vref  =0xd0;
			}
			else if((temp_parameter.dmc_phy_base==DMC_GUCPHY0_BASE)&&(temp_parameter.data_module==data_module_1))
			{
				store_reboot_value->print_bist_para.eye_start   =TRAINGING_EYE_START_VALUE(write_phy0_result.db1_wdq_result, write_phy0_result.db1_wdq_pass_window);
				store_reboot_value->print_bist_para.eye_end     =TRAINGING_EYE_END_VALUE(write_phy0_result.db1_wdq_result, write_phy0_result.db1_wdq_pass_window);
				store_reboot_value->print_bist_para.train_dqs   =write_phy0_result.db1_wdq_result;
				store_reboot_value->print_bist_para.train_vref  =0xd0;
			}
			else if((temp_parameter.dmc_phy_base==DMC_GUCPHY1_BASE)&&(temp_parameter.data_module==data_module_0))
			{
				store_reboot_value->print_bist_para.eye_start   =TRAINGING_EYE_START_VALUE(write_phy1_result.db0_wdq_result, write_phy1_result.db0_wdq_pass_window);
				store_reboot_value->print_bist_para.eye_end     =TRAINGING_EYE_END_VALUE(write_phy1_result.db0_wdq_result, write_phy1_result.db0_wdq_pass_window);
				store_reboot_value->print_bist_para.train_dqs   = write_phy1_result.db0_wdq_result;
				store_reboot_value->print_bist_para.train_vref  =0xd0;
			}
			else if((temp_parameter.dmc_phy_base==DMC_GUCPHY1_BASE)&&(temp_parameter.data_module==data_module_1))
			{
				store_reboot_value->print_bist_para.eye_start   =TRAINGING_EYE_START_VALUE(write_phy1_result.db1_wdq_result, write_phy1_result.db1_wdq_pass_window);
				store_reboot_value->print_bist_para.eye_end     =TRAINGING_EYE_END_VALUE(write_phy1_result.db1_wdq_result, write_phy1_result.db1_wdq_pass_window);
				store_reboot_value->print_bist_para.train_dqs   =write_phy1_result.db1_wdq_result;
				store_reboot_value->print_bist_para.train_vref  =0xd0;
			}
	#endif
		}
	ddr_print_bist_result(i,&(store_reboot_value->print_bist_para));
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
		//reg_bits_set(temp_parameter.dmc_phy_base + 0xb2*4, 2, 1, 0);
		//reg_bits_set(temp_parameter.dmc_phy_base + 0xb2*4, 2, 1, 1);
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
	pub_power_up();
	regulator_enable("vddmem");  //DRAM ON
	dmc_sprd_delay(20000);
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
	store_reboot_value->print_bist_para.scan_vref=vref_val;
	store_reboot_value->print_bist_para.type = temp_parameter.type;
	store_reboot_value->print_bist_para.eye_start   =TRAINGING_EYE_START_VALUE(ca_phy0_result.ca_result_cfg_fine, ca_phy0_result.ca_pass_window);
	store_reboot_value->print_bist_para.eye_end     =TRAINGING_EYE_END_VALUE(ca_phy0_result.ca_result_cfg_fine, ca_phy0_result.ca_pass_window);
	store_reboot_value->print_bist_para.train_dqs   =ca_phy0_result.ca_result_cfg_fine;

	i=store_reboot_value->scan_x;
	for (; i<=temp_parameter.scan_num;)
	{
	/*Set Delay*/
	phy_delay_line_set_ca(temp_parameter.dmc_phy_base,i,freq_sel);
	#ifdef DDR_SCAN_LPDDR4
	store_reboot_value->print_bist_para.train_vref  =LP4X_ca_training_vref;
	#else
	store_reboot_value->print_bist_para.train_vref  =(0x50|0x80);
	#endif
	ret = ddr_print_bist_result(i,&(store_reboot_value->print_bist_para));
  	i=i+1;
	store_reboot_value->scan_x=i;
	if(ret)
		{
			if(store_reboot_value->window_fail_flag==0)//Judge all file in line
				_start();
			else
			{
				dmc_print_str("\r\nPower Restart for DDR and PUB!\r\n");
				store_reboot_value->window_fail_flag=0;
				dram_pub_power_restart();
				_start();
			}
		}
	}
	store_reboot_value->print_bist_para.pass_flag=1;
	store_reboot_value->print_bist_para.fail_flag=1;
}
/*******************************
*Function:Print 32 bit data
*Name    :ddr_print_set_register
*In      :u32 int data
*out     :NULL
********************************/
void ddr_print_u32_data(u32 print_data)
{
	dmc_print_str("0x");
	//if(print_data>0xffffff)
	dmc_print_str(uint8tochar((print_data>>24)&0xff));
	//if(print_data>0xffff)
	dmc_print_str(uint8tochar((print_data>>16)&0xff));
	//if(print_data>0xff)
	dmc_print_str(uint8tochar((print_data>>8)&0xff));
	dmc_print_str(uint8tochar((print_data>>0)&0xff));
	dmc_print_str("\t");
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
	if(!i) {str[i++]='0';}
	str[i]=0;
}
char pr_str[12];
void ddr_print_u32_dec_data(u32 print_data)
{
	u32tostr(print_data,pr_str);
	dmc_print_str(pr_str);
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
	dmc_print_str("\r\n Write register:");
	ddr_print_u32_data(phy_data_0);
	ddr_print_u32_data(phy_data_1);
	dmc_print_str("\r\n Read register:");
	ddr_print_u32_data(phy_data_2);
	ddr_print_u32_data(phy_data_3);
	dmc_print_str("\r\n CA register:");
	ddr_print_u32_data(phy_data_4);
	 //ddr_print_u32_data(phy_data_5);
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
		case 0:dmc_print_str("\r\nPhy0DataByte0:");break;
		case 1:dmc_print_str("\r\nPhy0DataByte1:");break;
		case 2:dmc_print_str("\r\nPhy1DataByte0:");break;
		case 3:dmc_print_str("\r\nPhy1DataByte1:");break;
		}
		for(ivalue=0;ivalue<(sizeof(best_value)/sizeof(u32));ivalue++)//loop best_value member
		{
		switch (ivalue)
		{
		case 0:dmc_print_str("BestDelay:");break;
		case 1:dmc_print_str("Best Vref:");break;
		case 2:dmc_print_str("MaxWidth :");break;
		case 3:dmc_print_str("EYE Width:");break;
		}
		ddr_print_u32_data(pbest_para[ibest*4+ivalue]);
		dmc_print_str("\t");
		}
	}

}
static void ddr_print_all_best_para(void)
{
	u8 ibest=0;
	u8 ivalue=0;
	dmc_print_str("\r\n\r\nRead best  dac Parameter:");
	ddr_print_best_parameter(&read_dac_para);
	#ifndef DDR_SCAN_CMOS_MODE
	dmc_print_str("\r\n\r\nRead best op Parameter:");
	ddr_print_best_parameter(&read_op_para);
	#endif
	dmc_print_str("\r\n\r\nWrite best dac Parameter:");
	ddr_print_best_parameter(&write_dac_para);
}
/****************************
 *print ca best parameter
*****************************/
static void ddr_print_ca_best_para(best_para *para)
{
	u8 ibest=0;
	u8 ivalue=0;
	dmc_print_str("\r\n\r\nCA best Parameter:");
	u32 *pbest_para=&(para->Phy0_databyte0.best_delay);
	for(ivalue=0;ivalue<(sizeof(best_value)/sizeof(u32));ivalue++)//loop best_value member
	   {
		switch (ivalue)
		{
			case 0:dmc_print_str("BestDelay:");break;
			case 1:dmc_print_str("Best Vref:");break;
			case 2:dmc_print_str("MaxWidth :");break;
			case 3:dmc_print_str("EYE Width:");break;
		}
		ddr_print_u32_data(pbest_para[ivalue]);
		dmc_print_str("\t");
	  }

}

/*Set write vref for lpddr4x*/
void ddr_scan_set_write_vref_lpddr4(int vref){
#ifdef DDR_SCAN_LPDDR4
	lpddr_dmc_mrw(CMD_CS_BOTH,0xe, vref);//mr14
#else
	dmc_print_str("\r\nOperate ddr_scan_set_write_vref_lpddr4x is error\r\n");
#endif
}
/*Set write vref for lpddr4x*/
void ddr_scan_set_ca_vref_lpddr4(int vref){
#ifdef DDR_SCAN_LPDDR4
	lpddr_dmc_mrw(CMD_CS_BOTH,0xc, vref);//mr12
#else
	dmc_print_str("\r\nOperate ddr_scan_set_ca_vref_lpddr4x is error\r\n");
#endif
}
/************************************************************************
*Name : Off line scan write:
* Note:	1.maybe need to go into selfrefresh status when update dll value
* 	2.maybe need to reset after scan one time
*************************************************************************/
/*according PHY&DataByte scan*/
void ddr_offline_scan_wr(u16 max ,u16 min,best_para*pPara)
{
   u8 i=0;
   int vref_lv=0;
   reg_bits_set(PHY_VREFE_ADDRESS,22,1,0); //phy_vref_hi_c
   reg_bits_set(PHY_VREFE_ADDRESS,23,1,0); //phy_vref_pd
   //dmc_print_str("\r\noff line scan write\r\n");
   for(i=0;i<(sizeof(phy_scan_para_wr)/sizeof(scan_type_parameter));i++)
	{
#ifdef DDR_SCAN_LPDDR3
	    dram_pub_power_restart();
	    dram_init_powerup_times=0;
	    ddr_scan_repeat_call_flag=1;/*Do not allow repeat ddr_scan_vdd_seq for sdram_init*/
	    sdram_init();
	    ddr_scan_repeat_call_flag=0;/* Allow repeat ddr_scan_vdd_seq for sdram_init use for ca scan*/
#endif
	//print scale logo
	dmc_print_str("          ");
#ifdef DDR_SCAN_LPDDR3
	ddr_print_scan_dead_line();
#else
	ddr_print_scan_dead_line_4x(0x1ff);
#endif
	//Display message
	if(phy_scan_para_wr[i].dmc_phy_base==DMC_GUCPHY0_BASE)
		dmc_print_str("PHY0,");
	else dmc_print_str("PHY1,");
	if(phy_scan_para_wr[i].data_module==0)
		dmc_print_str("DataByte0,");
	else dmc_print_str("DataByte1,");
	for(vref_lv=max;vref_lv>=min;vref_lv--)
	{
#ifndef DDR_SCAN_LPDDR4
		reg_bits_set(PHY_VREFE_ADDRESS, 24, 8, vref_lv); //set vref value
		dmc_sprd_delay(20000);//20ms
#else
		if(vref_lv==0x39) {
			vref_lv=0x33;
		}
		ddr_scan_set_write_vref_lpddr4(vref_lv);  //set vref value
		dmc_sprd_delay(2000);//2ms
#endif
		if(vref_lv!=max)
			dmc_print_str("               ");
		dmc_print_str("VREFE=");
		dmc_print_str(uint8tochar(vref_lv&0xff));
		dmc_print_str(":");
		// reg_bits_set(PHY_VREFE_ADDRESS,31,1,1);//always keep 1 for bit 31 according email
		//Scan and print
		ddr_offline_scan_parameter(phy_scan_para_wr[i],vref_lv);
		param_to_pass_boundary_print();//print boundary
		 //ddr_get_best_write_delay(i,vref_lv);//store best parameter
		ddr_get_best_delay_para(i,vref_lv,pPara);//store best parameter
		first_pass=0;
		last_pass=0;
		dmc_print_str("\r\n");
	}
	dmc_print_str("\r\n");
	}
#ifndef DDR_SCAN_LPDDR4
	reg_bits_set(PHY_VREFE_ADDRESS, 24, 8, 0xd7); //set best vref value
	dmc_sprd_delay(20000); //20ms
#endif
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
void ddr_offline_scan_rd(u16 max ,u16 min,best_para *pPara)
{
	u8 i=0;
	int vref_val=0;
	vref_address_0=DMC_GUCPHY0_BASE+vrefi_offset[freq_sel];//confirm vref register
	vref_address_1=DMC_GUCPHY1_BASE+vrefi_offset[freq_sel];
	//dmc_print_str("\r\nOff line Scan read.......\r\n");
	for(i=0;i<(sizeof(phy_scan_para_rd)/sizeof(scan_type_parameter));i++)  //pay & data module
	{
		dmc_print_str("          ");
		ddr_print_scan_dead_line();
		if(phy_scan_para_wr[i].dmc_phy_base==DMC_GUCPHY0_BASE) //Display message
			  dmc_print_str("PHY0,");
		 else dmc_print_str("PHY1,");
		 if(phy_scan_para_wr[i].data_module==0)
			  dmc_print_str("DataByte0,");
		 else {dmc_print_str("DataByte1,");}
          for(vref_val=max;vref_val>=min;vref_val--)
          	{
		if(vref_val!=max)
			dmc_print_str("               ");
		dmc_print_str("VREFI=");
		dmc_print_str(uint8tochar(vref_val&0xff));
		dmc_print_str(":");
		reg_bits_set(vref_address_0,0,8,vref_val);
		reg_bits_set(vref_address_1,0,8,vref_val);
		reg_bits_set(vref_address_0,8,8,vref_val);
		reg_bits_set(vref_address_1,8,8,vref_val);
		dmc_sprd_delay(20000);//20ms
		ddr_offline_scan_parameter(phy_scan_para_rd[i],vref_val);
		param_to_pass_boundary_print();//print boundary
		//ddr_get_best_read_delay(i,vref_val);//store read best parameter
		ddr_get_best_delay_para(i,vref_val,pPara);
		dmc_print_str("\r\n");
		}
	}
	dmc_print_str("\r\n");
}

void ddr_offline_scan_ca(u16 vref_max ,u16 vref_min)
{
	u8 i=0;
	u16 vref_lv=0;
	u8 test_print=0;
	/*print and set best read DQ delay and write DQ delay*/
	//close auto refresh in ca scan
	reg_bits_set(0x3000010c,12,1,0);
	//close DMC auto sleep
	reg_bits_set(0x30000000,8,2,0);
	//ddr_print_scan_dead_line();
	/*set vrefe for scan ca*/
	reg_bits_set(PHY_VREFE_ADDRESS,22,1,0); //phy_vref_hi_c
	reg_bits_set(PHY_VREFE_ADDRESS,23,1,0); //phy_vref_pd
	vref_lv=(store_reboot_value->vref_lv);
	i=store_reboot_value->phy_num;
	for(;i<(sizeof(phy_scan_para_ca)/sizeof(scan_type_parameter));)  //CA only scan PHY0
	 {
	    if((store_reboot_value->old_phy_num)!=(store_reboot_value->phy_num))
	    	{
			store_reboot_value->old_phy_num=store_reboot_value->phy_num;//update old phy value
			dmc_print_str("\r\nDDR Scan CA Start\r\n");
			#ifdef DDR_SCAN_LPDDR4
				ddr_print_scan_dead_line_4x(phy_scan_para_ca[0].scan_num);
			#else
				ddr_print_scan_dead_line();
			#endif
			if(phy_scan_para_ca[i].dmc_phy_base==DMC_GUCPHY0_BASE) //Display message
				dmc_print_str("PHY0,");
			else
				dmc_print_str("PHY1,");
	    	}
		for(;vref_lv>vref_min;)//VREF
		{
			if((store_reboot_value->old_vref_lv)!=(store_reboot_value->vref_lv))
			{
				store_reboot_value->old_vref_lv=store_reboot_value->vref_lv;//update old vref value
				#ifdef DDR_SCAN_LPDDR3
				if((store_reboot_value->vref_lv)!=VREFE_DAC_MAX)//Align print log
					dmc_print_str("     ");
				#endif
				dmc_print_str("VREFE=");
				dmc_print_str(uint8tochar(vref_lv&0xff));
				dmc_print_str(":");
			}
#ifdef DDR_SCAN_LPDDR4
			ddr_scan_set_ca_vref_lpddr4(vref_lv);/*set vref value for LPDDR4*/
			if(vref_lv==0x40) {
				vref_lv=0x33;
			}
#else
			reg_bits_set(PHY_VREFE_ADDRESS,24,8,vref_lv);//set vref value for LPDDR3
			//reg_bits_set(PHY_VREFE_ADDRESS,31,1,1);//always keep 1 for bit 31 according email
			dmc_sprd_delay(20000);//20ms
#endif
			ddr_offline_scan_parameter_ca(phy_scan_para_ca[i],vref_lv);
			if((first_pass==0)&&(last_pass==0))//Try this test
			{
				store_reboot_value->window_fail_flag=1;/*Restart Dram Power & Power*/
			}
			param_to_pass_boundary_print();//print boundary
			ddr_get_best_delay_para(i,vref_lv,&(store_reboot_value->ca_best_para));//store best parameter
			first_pass=0;//Reset rom first_pass&last_pass Value  -test
			last_pass=0;
			dmc_print_str("\r\n");
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
}
/**********************************************
*Function:Print x axis ruler
*
**********************************************/
static void ddr_print_scan_dead_line(void)
{
 u32 i=0;
 u32 data_temp=0;
 //#ifdef DDR_SCAN_CA
   dmc_print_str("              ");

  for(i=0;i<=0xff;i++)
  {
	switch (i)
	  {
		case 0x0:dmc_print_str("0");break;
		case 0x10:dmc_print_str("1");break;
		case 0x20:dmc_print_str("2");break;
		case 0x30:dmc_print_str("3");break;
		case 0x40:dmc_print_str("4");break;
		case 0x50:dmc_print_str("5");break;
		case 0x60:dmc_print_str("6");break;
		case 0x70:dmc_print_str("7");break;
		case 0x80:dmc_print_str("8");break;
		case 0x90:dmc_print_str("9");break;
		case 0xa0:dmc_print_str("A");break;
		case 0xb0:dmc_print_str("B");break;
		case 0xc0:dmc_print_str("C");break;
		case 0xd0:dmc_print_str("D");break;
		case 0xe0:dmc_print_str("E");break;
		case 0xf0:dmc_print_str("F");break;
		default:dmc_print_str("-");break;
	 }
    }
  dmc_print_str("\r\n");
}
/**********************************************
*Function:Print x axis ruler
*LPDDR4-write
**********************************************/
static void ddr_print_scan_dead_line_4x(int num)
{
 u32 i=0;
 u32 data_temp=0;
 //#ifdef DDR_SCAN_CA
#if 1
	dmc_print_str("              ");
#else
	dmc_print_str("                        ");
#endif
	for(i=0;i<=num;i++)
	{
	switch (i&0xff)
	{
	  	case 0x0:dmc_print_str("0");break;
	  	case 0x10:dmc_print_str("1");break;
	  	case 0x20:dmc_print_str("2");break;
	  	case 0x30:dmc_print_str("3");break;
	  	case 0x40:dmc_print_str("4");break;
	  	case 0x50:dmc_print_str("5");break;
	  	case 0x60:dmc_print_str("6");break;
	  	case 0x70:dmc_print_str("7");break;
	  	case 0x80:dmc_print_str("8");break;
	  	case 0x90:dmc_print_str("9");break;
	  	case 0xa0:dmc_print_str("A");break;
	  	case 0xb0:dmc_print_str("B");break;
	  	case 0xc0:dmc_print_str("C");break;
	  	case 0xd0:dmc_print_str("D");break;
	  	case 0xe0:dmc_print_str("E");break;
	  	case 0xf0:dmc_print_str("F");break;
	  	default:dmc_print_str("-");break;
	 }

	}
	dmc_print_str("\r\n");
}
/***************************/
/**USE FOR Choose Rank0 &Rank1 **/
/***************************/
void ddr_scan_choose_rank(u32 rank_number)
{
	u32 temp_dmc;
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
#ifdef DDR_SCAN_LPDDR4
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
	sdram_cs_whole_size(0,&rank_configure[1].bist_start);
	bist_start_address = rank_configure[rank_number].bist_start;
	/*Print*/

#else
	sdram_cs_whole_size(0,&rank_bist_addr[1]);
	bist_start_address=rank_bist_addr[rank_number];
#endif

if (store_reboot_value->SwitchRankTrainingFlag==1)/*Control only scan one time*/
	{
	/*Print current choose rank*/
	dmc_print_str("\r\n\r\n@@@@@@@@@@@@@@@@@@@@@RANK=0x");
	dmc_print_str(uint8tochar(store_reboot_value->rank_loop_num));
	dmc_print_str(" DDR SCAN!!@@@@@@@@@@@@@@@@@@@@@\r\n\r\n");
	dmc_print_str("\r\nInterleaveMode=");
	ddr_print_u32_data(((pdmc->dmc_dcfg17)>>24)&0x7);
	dmc_print_str("\tLinear0=");
	ddr_print_u32_data((pdmc->dmc_dcfg18)&0x3fff);
	dmc_print_str("\tLinear1=");
	ddr_print_u32_data(((pdmc->dmc_dcfg18)>>16)&0x3ff);
	dmc_print_str("\tInterleaveBase=");
	ddr_print_u32_data((pdmc->dmc_dcfg20)&0x3ff);
	/*Print choose rank register,if you need*/
	dmc_print_str("\r\nBist start address=");
	ddr_print_u32_data(bist_start_address);
	dmc_print_str("\r\n");
#ifdef DDR_SCAN_LPDDR4
	dmc_print_str("\r\nLp4 Write vref training Value=");
	ddr_print_u32_data(LP4_write_training_vref);
	dmc_print_str("\tCA VREF Training Value=");
	ddr_print_u32_data(LP4X_ca_training_vref);
	dmc_print_str("\r\n");
#endif
	}
    /*Training*/
	if (store_reboot_value->SwitchRankTrainingFlag==1)
	 {
		store_reboot_value->SwitchRankTrainingFlag=0;/*Avoid repeat _start()*/
		_start();/*Convert rank Repeat training*/
	 }
	/*Print Training Result*/
	if (store_reboot_value->RankTrainingPrintFlag==1)
	{
		store_reboot_value->RankTrainingPrintFlag=0;
		ddr_scan_get_training_printresult();
		/*print dump rd register value*/
		ddr_dump_read_reg(DMC_GUCPHY0_BASE, DMC_GUCPHY1_BASE);
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
	store_reboot_value->vref_lv=CA_SCAN_MAX;//VREFE_DAC_MAX;
	store_reboot_value->scan_x=0;
	store_reboot_value->old_vref_lv=0;
	store_reboot_value->phy_num=0;
	store_reboot_value->old_phy_num=2;//Any value except 0
	store_reboot_value->window_fail_flag=0;
	store_reboot_value->read_write_end_flag=0;
	store_reboot_value->print_bist_para.pass_flag=1;
	store_reboot_value->print_bist_para.fail_flag=1;
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
void ddr_offline_scan_seq(void)
{
	u32 back_register_0=0;
	u32 back_register_1=0;
	reg_bits_set(0x402b00b0,8,1,0);//Enable address 0x800000 space
	reg_bits_set(0x402b00cc,20,1,0);
	memset(&read_dac_para,0,sizeof(read_dac_para));
	memset(&read_op_para,0,sizeof(read_op_para));
	memset(&write_dac_para,0,sizeof(write_dac_para));
	REG32(0x30000124)=0;
	dmc_sprd_delay(2);//2us
	if(store_reboot_value->read_write_end_flag==0)//Avoid scan ca repeat call read & write function
	{
		#ifdef DDR_SCAN_READ
		/*Scan Vrefi Read*/
		vref_address_0=DMC_GUCPHY0_BASE+vrefi_offset[freq_sel];
		vref_address_1=DMC_GUCPHY1_BASE+vrefi_offset[freq_sel];
		back_register_0=REG32(vref_address_0);
		back_register_1=REG32(vref_address_1);
		dmc_print_str("\r\nOff line Scan read  DAC Mode start !\r\n");
		ddr_offline_scan_rd(VREFI_DAC_MAX,VREFI_DAC_MIN,&read_dac_para);
		dmc_print_str("\r\nOff line Scan read DAC Mode end!\r\n");
		//#ifndef DDR_SCAN_CMOS_MODE
		//dmc_print_str("\r\nOff line Scan read   OP mode start!\r\n");
		//ddr_offline_scan_rd(VREFI_OP_MAX,VREFI_OP_MIN,&read_op_para);
		//dmc_print_str("\r\nOff line Scan read   OP mode end!\r\n");
		//#endif
		REG32(vref_address_0)=back_register_0;
		REG32(vref_address_1)=back_register_1;
		dmc_sprd_delay(20000);//20ms
		#endif
		#ifdef DDR_SCAN_WRITE
		//Scan VREFE WRITE
		back_register_0=REG32(PHY_VREFE_ADDRESS);
		dmc_print_str("\r\nOff line Scan write   DAC mode start!\r\n");
		ddr_offline_scan_wr(VREFE_DAC_MAX,VREFE_DAC_MIN,&write_dac_para);
		dmc_print_str("\r\nOff line Scan write   DAC mode end!\r\n");
		REG32(PHY_VREFE_ADDRESS)=back_register_0;
		dmc_sprd_delay(20000);//20ms
		ddr_print_all_best_para();
		#endif
		store_reboot_value->read_write_end_flag=1;
	}
	#ifdef DDR_SCAN_CA
	//dmc_print_str("\r\nOff line Scan CA start!\r\n");
	ddr_offline_scan_ca(CA_SCAN_MAX,CA_SCAN_MIN);//Debug for 0xf0 Normal Set:(VREFE_DAC_MAX,VREFE_DAC_MIN);
	ddr_print_ca_best_para(&(store_reboot_value->ca_best_para));
	// dmc_print_str("\r\nOff line Scan CA end!\r\n");
	#endif
  //  while(1);//wait for test

}
/**************************************************
 *Function:Loop Adjust vddq&vddcore
 *          to ddr read&write&ca scan
 **************************************************/
#ifdef RD_DDR_SCAN
#ifdef DDR_SCAN_CONTAIN_VDD_LOOP
 /*Contain vdd scan*/
void ddr_scan_vdd_seq(void)
{
   //u32 vddq,vddcore;
	reg_bits_set(0x402b00b0,8,1,0);//Enable address 0x800000 space
	reg_bits_set(0x402b00cc,20,1,0);
	freq_sel = (REG32(0x3000012c) >> 8) & 0x7;//get freq for register
#ifdef DDR_SCAN_LPDDR4
	//LP4_write_training_vref =reg_bits_get(0x402b00d0,24,8); //LP4 write training must read set register
	dmc_mrr(CMD_CS_0, 14, &LP4_write_training_vref, 10000);
	LP4_write_training_vref=LP4_write_training_vref&0x7f;//Only the lower 7 bits are valid
	dmc_mrr(CMD_CS_0, 12, &LP4X_ca_training_vref, 10000);/*read MR12*/
	LP4X_ca_training_vref=LP4X_ca_training_vref&0x7f;/*Only the lower 7 bits are valid*/
#endif
	 if(store_reboot_value->rom_start_flag != 0xaa)
	 {
		memset(store_reboot_value,0,sizeof(rom_value));//Initial rom arear
		ddr_scan_reset_rom_parameter();/*rest parameter for store 0x800000*/
		store_reboot_value->rank_loop_num = 0; /*Rank loop,this reset only this valided*/
		store_reboot_value->SwitchRankTrainingFlag=1;/*Control Training in change rank function */
		dmc_print_str("Current SCK=");
		ddr_print_u32_data(freq_sel);
		dmc_print_str("\r\n");

		/*step 1. Start SDRAM Init*/
		/*step 2. read out Initial training result and print*/
		ddr_print_scan_head();//print scan head
		ddr_scan_get_training_printresult();
		#ifdef DDR_SCAN_LPDDR4
		dmc_print_str("\r\nLp4 Write vref training value=");
		ddr_print_u32_data(LP4_write_training_vref);
		dmc_print_str("\tCA VREF Training Value=");
		ddr_print_u32_data(LP4X_ca_training_vref);
		dmc_print_str("\r\n");
		#endif
	  }
#ifdef DDR_SCAN_DUAL_RANK
    /*Loop rank*/
   for(;store_reboot_value->rank_loop_num<2;store_reboot_value->rank_loop_num++) /*scan rank */
    {
	ddr_scan_choose_rank(store_reboot_value->rank_loop_num);/*Choose rank*/
#endif
	/*Loop set vddq & vddcore*/
#ifndef DDR_SCAN_LPDDR4/*LP4X no loop scan vddq*/
	for(;(store_reboot_value->new_vddq) >= VDDQ_MIN;)        /*scan vddq*/
	{
#endif
		for(;(store_reboot_value->new_vddcore)>=VDDCORE_MIN;) /*scan vddcore*/
		{
#ifndef DDR_SCAN_LPDDR4/*LP4X no loop scan vddq*/
		/*VDDQ*/
		regulator_set_voltage("ldomem",store_reboot_value->new_vddq);
#endif
		if(store_reboot_value->new_vddq!=store_reboot_value->old_vddq)
		{
			dmc_print_str("\r\n#####################VDDQ=");
			ddr_print_u32_dec_data(regulator_get_voltage("ldomem"));
			dmc_print_str("#####################\r\n");
			store_reboot_value->print_vddq_training_flag=1;
			store_reboot_value->old_vddq=store_reboot_value->new_vddq;//update old value
			ddr_scan_clear_minmax();
			_start();//Use for do HW training if only call  ddrc_phy_init_seq function not through
		}else if(store_reboot_value->print_vddq_training_flag==1)
		{
			ddr_scan_get_training_printresult();//print training result
			store_reboot_value->print_vddq_training_flag=0;
		}
		regulator_set_voltage("vddcore",store_reboot_value->new_vddcore);/*Set vddcore voltage*/
		/*VDDCORE*/
		if(store_reboot_value->new_vddcore!=store_reboot_value->old_vddcore)
		{
			dmc_print_str("\r\n&&&&&&&&&&&&&&&&&&&VDDCORE=");
			ddr_print_u32_dec_data(regulator_get_voltage("vddcore"));
			dmc_print_str("&&&&&&&&&&&&&&&&&&&\r\n");
			//ddrc_phy_init_seq();//training or call _start()--NeedTest
			store_reboot_value->print_vddcore_training_flag=1;
			store_reboot_value->old_vddcore=store_reboot_value->new_vddcore;//update old value
			//clear min/max
			ddr_scan_clear_minmax();
			_start();
		}else if(store_reboot_value->print_vddcore_training_flag==1)
		{
			ddr_scan_get_training_printresult();//print training result
			#ifdef DDR_SCAN_DUMP_RD_REG_ENABLE  //print dump rd register value
			ddr_dump_read_reg(DMC_GUCPHY0_BASE,DMC_GUCPHY1_BASE);
			#endif
			//clear min/max
			ddr_scan_clear_minmax();
			store_reboot_value->print_vddcore_training_flag=0;
		}
		ddr_offline_scan_seq();
		#ifdef DDR_SCAN_DUMP_RD_REG_ENABLE  //print dump rd register value
		ddr_dump_read_reg(DMC_GUCPHY0_BASE,DMC_GUCPHY1_BASE);
		ddr_scan_clear_minmax();
		#endif
		/*Clear store rom scan variable prepare for repeat call ddr scan seq*/
		{
			store_reboot_value->vref_lv=VREFE_DAC_MAX;
			store_reboot_value->scan_x=0;
			store_reboot_value->old_vref_lv=0;
			store_reboot_value->phy_num=0;
			store_reboot_value->old_phy_num=2;//Any value except 0
			store_reboot_value->window_fail_flag=0;
			store_reboot_value->read_write_end_flag=0;
			store_reboot_value->print_bist_para.pass_flag=1;
			store_reboot_value->print_bist_para.fail_flag=1;
		}
		store_reboot_value->new_vddcore=store_reboot_value->new_vddcore-VDDCORE_PER_STEP;//change loop variable
		}
#ifndef DDR_SCAN_LPDDR4/*LP4X no loop scan vddq*/
			store_reboot_value->new_vddq = store_reboot_value->new_vddq - VDDQ_PER_STEP; //change loop variable
			store_reboot_value->new_vddcore = VDDCORE_MAX; //initial loop variable
		}
#endif
#ifdef DDR_SCAN_DUAL_RANK
	 ddr_scan_reset_rom_parameter();/*Clear some parameter and continue loop*/
   }
#endif
	 while(1);
}
#else
/*No vdd scan*/
void ddr_scan_vdd_seq(void)
{
	//u32 vddq,vddcore;
	reg_bits_set(0x402b00b0,8,1,0);//Enable address 0x800000 space
	reg_bits_set(0x402b00cc,20,1,0);
	freq_sel = (REG32(0x3000012c) >> 8) & 0x7;//get freq for register

	 if(store_reboot_value->rom_start_flag != 0xaa)
	 {
		memset(store_reboot_value,0,sizeof(rom_value));//Initial rom arear
		ddr_scan_reset_rom_parameter(); /*Reset Store 0x800000 parameter*/
		store_reboot_value->rank_loop_num = 0; /*Rank loop,this reset only this valided*/
		/*RANK SCAN parameter initial*/
		dmc_print_str("Current SCK=");
		ddr_print_u32_data(freq_sel);
		dmc_print_str("\r\n");
		/*step 1. Start SDRAM Init*/
		/*step 2. read out Initial training result and print*/
		ddr_print_scan_head();//print scan head
		ddr_scan_get_training_printresult();

		ddr_dump_read_reg(DMC_GUCPHY0_BASE, DMC_GUCPHY1_BASE);
	  }

#ifdef DDR_SCAN_DUAL_RANK
	#ifdef DDR_SCAN_LPDDR4
	for(;store_reboot_value->rank_loop_num<(sizeof(rank_configure)/sizeof(RankConfigure));store_reboot_value->rank_loop_num++)/*LP4X*/
	#else
	for (;store_reboot_value->rank_loop_num<(sizeof(rank_bist_addr)/sizeof(uint64));store_reboot_value->rank_loop_num++)/*LP3*/
	#endif
	{
#ifdef DDR_SCAN_LPDDR4
		if (store_reboot_value->rank_loop_num==0)
		{
			dmc_mrr(CMD_CS_0, 14, &LP4_write_training_vref, 10000); //Get Write Training Vref for LPDDR4X
			LP4_write_training_vref=LP4_write_training_vref&0x7f;//Only the lower 7 bits are valid
			dmc_mrr(CMD_CS_0, 12, &LP4X_ca_training_vref, 10000);/*read MR12*/
			LP4X_ca_training_vref=LP4X_ca_training_vref&0x7f;/*Only the lower 7 bits are valid*/
		}else if(store_reboot_value->rank_loop_num==1)
		{
			dmc_mrr(CMD_CS_1, 14, &LP4_write_training_vref, 10000); //Ger Write Training Vref for LPDDR4X
			LP4_write_training_vref=LP4_write_training_vref&0x7f;//Only the lower 7 bits are valid
			dmc_mrr(CMD_CS_1, 12, &LP4X_ca_training_vref, 10000);/*read MR12*/
			LP4X_ca_training_vref=LP4X_ca_training_vref&0x7f;/*Only the lower 7 bits are valid*/
		}
#endif
		ddr_scan_choose_rank(store_reboot_value->rank_loop_num);/*Choose rank*/
		ddr_offline_scan_seq();
		ddr_scan_reset_rom_parameter();//reset store 0x800000 parameter
		if(1 == sdram_chip_cs_num())
		{
			store_reboot_value->rank_loop_num=2;
		}
	}
#else
		ddr_offline_scan_seq();
#endif
/*Judge  dump register*/
#ifdef DDR_SCAN_DUMP_RD_REG_ENABLE  //print dump rd register value
	ddr_dump_read_reg(DMC_GUCPHY0_BASE, DMC_GUCPHY1_BASE);
#endif
	 while(1);
}
#endif
#endif
#endif
