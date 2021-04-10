#ifdef DDR_SCAN_ENABLE
#include "sci_types.h"
#include "ddrc_r1p0.h"
#include "ddrc_r1p0_phy.h"
#include "ddrc_r1p0_common.h"
#include "ddr_scan_r1p0.h"
#include "debug.h"


#define REG32(x)						(*((volatile unsigned int*)(x)))

#define PASS dmc_print_str("\t0x0")
#define FAIL dmc_print_str("\t0xf")

#define PARAM_SCAN_END  dmc_print_str("\r\n0x343434")
#define SCAN_LOG_START  dmc_print_str("\r\n0x71747172")
#define SCAN_LOG_END    dmc_print_str("\r\n0x656E6464")

#define scan_vref_write_up_offset   5
#define scan_vref_write_down_offset 5
#define scan_vref_read_up_offset    5
#define scan_vref_read_down_offset  5
#define scan_vref_ca_up_offset      5
#define scan_vref_ca_down_offset    5

extern  _start();
extern DRAM_CHIP_INFO ddr_chip_cur;
//rom_value store_flag
static rom_value *store_reboot_value = ((rom_value *)ROM_START_ADDRESS);


#define first_pass  (store_reboot_value->first_pass)
#define last_pass   (store_reboot_value->last_pass)
#define center_pass (store_reboot_value->center_pass)
#define pass_flag   (store_reboot_value->pass_flag)
#define fail_flag   (store_reboot_value->fail_flag)

static u8 ddr_scan_transfer_flag = 1; //avoid repeat call ddr_offline_scan_seq function ,use for ddrc_r1p0.c
static u32 freq_sel; //read FREQ
static u32 vref_address_0 = 0; //store scan read vreaf address
static u32 vref_address_1 = 0;
static u8 scan_bist_pattern = 2; //bist pattern  2-LFSR
static uint32 LP4_write_training_vref = 0; /*write training value to read MR14 for LPDDR4X*/
static uint32 LP4X_ca_training_vref=0;/*CA training value to read MR12 for LPDDR4X*/

static best_para read_dac_para;
static best_para read_op_para;
static best_para write_dac_para;
//rom_value *store_reboot_value=&store_flag;


/*HW Training Result*/
static struct read_result	read_phy0_result;
static struct read_result	read_phy1_result;
static struct write_result  write_phy0_result;
static struct write_result  write_phy1_result;

#define ca_phy0_result (store_reboot_value->ca_phy0_result)
#define ca_phy1_result (store_reboot_value->ca_phy1_result)



static void ddr_print_u32_data(u32 print_data);
/******************************
*Name:uint8tochar
* Function:uint Transform char
*******************************/
static char p_data[5] = { 0 };
static char* uint8tochar(uint8 val)
{
	uint8 high_byte = 0;
	uint8 low_byte = 0;
	uint8 temp;
	temp = val & 0xf;
	if (temp > 9)
	{
		low_byte = temp - 10 + 0x61;
	} else
	{
		low_byte = temp + 0x30;
	}

	temp = (val & 0xf0) >> 4;
	if (temp > 9)
	{
		high_byte = temp - 10 + 0x61;
	} else
	{
		high_byte = temp + 0x30;
	}

	p_data[0] = high_byte;
	p_data[1] = low_byte;
	p_data[2] = 0;

	return p_data;
}

static void ca_result_get(u32 phy_base, struct ca_result *phy_ca_result)
{
	u32 data_tmp;
	data_tmp = __raw_readl(phy_base + 0xe6 * 4); //0x0398 CA training coarse and fine delay trainining result and ca vref result

	phy_ca_result->vref_dram_ca_result = (data_tmp >> 24) & 0x3f;
	phy_ca_result->ca_pass_window = (data_tmp >> 16) & 0xFF;
	phy_ca_result->ca_result_cfg_fine = (data_tmp >> 8) & 0xFF;
	phy_ca_result->ca_result_cfg_coarse = data_tmp & 0xff;
	//Update Eye Window Start & End
	phy_ca_result->ca_eye_window_start = TRAINGING_EYE_START_VALUE(phy_ca_result->ca_result_cfg_fine, phy_ca_result->ca_pass_window);
	phy_ca_result->ca_eye_window_end = TRAINGING_EYE_END_VALUE(phy_ca_result->ca_result_cfg_fine, phy_ca_result->ca_pass_window);
}

static void read_result_get(u32 phy_base, struct read_result *phy_read_result)
{
	u32 data_tmp;
	data_tmp = __raw_readl(phy_base + 0xea * 4); //0x03a8 // read vref training result

	phy_read_result->deye_vref_db0_result = data_tmp & 0xff;
//	phy_read_result->deye_vref_db1_result = (data_tmp >> 8) & 0xff;

	data_tmp = __raw_readl(phy_base + 0xeb * 4);

	phy_read_result->rd_db1_dqsn = (data_tmp >> 24) & 0xff;
	phy_read_result->rd_db0_dqsn = (data_tmp >> 16) & 0xff;
	phy_read_result->rd_db1_dqs = (data_tmp >> 8) & 0xff;
	phy_read_result->rd_db0_dqs = data_tmp & 0xff;

	data_tmp = __raw_readl(phy_base + 0xed * 4); //0x03b4 read eye pass window

	phy_read_result->db1_rdq_pass_window = (data_tmp >> 8) & 0xFF; //mlb_train_db0_deye_pass_window_cfg_db1
	phy_read_result->db0_rdq_pass_window = data_tmp & 0xFF; ///mlb_train_db0_deye_pass_window_cfg_db0

	//Calcullation read training eye window start and end
	phy_read_result->rd_db0_eye_window_start = TRAINGING_EYE_START_VALUE(phy_read_result->rd_db0_dqs, phy_read_result->db0_rdq_pass_window);
	phy_read_result->rd_db0_eye_window_end  = TRAINGING_EYE_END_VALUE(phy_read_result->rd_db0_dqs, phy_read_result->db0_rdq_pass_window);
	phy_read_result->rd_db1_eye_window_start = TRAINGING_EYE_START_VALUE(phy_read_result->rd_db1_dqs, phy_read_result->db1_rdq_pass_window);
	phy_read_result->rd_db1_eye_window_end  = TRAINGING_EYE_END_VALUE(phy_read_result->rd_db1_dqs, phy_read_result->db1_rdq_pass_window);
}

static void write_result_get(u32 phy_base, struct write_result *phy_write_result)
{
	u32 data_tmp;
	data_tmp = __raw_readl(phy_base + 0xe9 * 4); //0x03a4 rddv_sel value and dram vref training result

	phy_write_result->vref_dram_adj_result = (data_tmp >> 24) & 0x3F; //

	data_tmp = __raw_readl(phy_base + 0xec * 4); //0x03b0 write DQS to DQ coarse and fine phase training result
	phy_write_result->db1_wdq_bt_result = (data_tmp >> 20) & 0xF; //**_cfg_db1_wdq
	phy_write_result->db0_wdq_bt_result = (data_tmp >> 16) & 0xF; //**_cfg_db0_wdq
	phy_write_result->db1_wdq_result = (data_tmp >> 8) & 0xFF; //**_cfg_db1_wrdeye
	phy_write_result->db0_wdq_result = data_tmp & 0xFF; //**_cfg_db0_wrdeye

	data_tmp = __raw_readl(phy_base + 0xee * 4); //0x03b8 read eye pass window

	phy_write_result->db1_wdq_pass_window = (data_tmp >> 8) & 0xFF; //mlb_train_db0_deye_pass_window_cfg_db1
	phy_write_result->db0_wdq_pass_window = data_tmp & 0xFF; ///mlb_train_db0_deye_pass_window_cfg_db0
	//Calcullation write training eye window start and end
	phy_write_result->wr_db0_eye_window_start = TRAINGING_EYE_START_VALUE(phy_write_result->db0_wdq_result, phy_write_result->db0_wdq_pass_window);
	phy_write_result->wr_db0_eye_window_end  = TRAINGING_EYE_END_VALUE(phy_write_result->db0_wdq_result, phy_write_result->db0_wdq_pass_window);
	phy_write_result->wr_db1_eye_window_start = TRAINGING_EYE_START_VALUE(phy_write_result->db1_wdq_result, phy_write_result->db1_wdq_pass_window);
	phy_write_result->wr_db1_eye_window_end  = TRAINGING_EYE_END_VALUE(phy_write_result->db1_wdq_result, phy_write_result->db1_wdq_pass_window);

}

static void phy_delay_line_set_ca(u32 phy_base, u32 value, u32 freq_sel)
{
	u32 tmp_addr = phy_base + (freq_sel * 20 * 4);

	//set delay line manual value
	reg_bits_set(tmp_addr + 0xc * 4, 0, 1, ((value >> 8) & 0x1)); //reg_f0_mlb_vref_ca_rang_manu_cfg_delay_bt
	reg_bits_set(tmp_addr + 0xc * 4, 8, 8, (value & 0xFF)); //reg_f0_mlb_vref_ca_rang_manu_cfg_delay

	//update manual value
	reg_bits_set(phy_base + 0xb2 * 4, 0, 1, 0); //reg_cal_update_rule_cfg_ca_manual_mode
	reg_bits_set(phy_base + 0xb2 * 4, 0, 1, 1); //reg_cal_update_rule_cfg_ca_manual_mode
	//dmc_sprd_delay(2);//2us
}

static void phy_delay_line_set_wr(u32 phy_base, u32 value, u32 freq_sel, u32 byte_sel)
{
	u32 tmp_addr = phy_base + (freq_sel * 20 * 4);

	if (byte_sel)
	{
		reg_bits_set(tmp_addr + 0x12 * 4, 20, 4, ((value >> 8) & 0xF));
		reg_bits_set(tmp_addr + 0x12 * 4, 8, 8, (value & 0xFF));
	} else
	{
		reg_bits_set(tmp_addr + 0x12 * 4, 16, 4, ((value >> 8) & 0xF));
		reg_bits_set(tmp_addr + 0x12 * 4, 0, 8, (value & 0xFF));
	}

	//update manual value
	reg_bits_set(phy_base + 0xb2 * 4, 3, 1, 0);  //reg_cal_update_rule_cfg_ca_manual_mode
	reg_bits_set(phy_base + 0xb2 * 4, 3, 1, 1); //reg_cal_update_rule_cfg_ca_manual_mode

}

static void phy_delay_line_set_rd(u32 phy_base, u32 value, u32 freq_sel, u32 byte_sel)
{
	u32 tmp_addr = phy_base + (freq_sel * 20 * 4);

	if (byte_sel)
	{
		//reg_bits_set(tmp_addr + 0x11*4, 24, 8, (value & 0xFF));//[31:24] = value[7:0]
		reg_bits_set(tmp_addr + 0x11 * 4, 8, 8, (value & 0xFF)); //[15:8] = value[7:0]
	} else
	{
		//reg_bits_set(tmp_addr + 0x11*4, 16, 8, (value & 0xFF));
		reg_bits_set(tmp_addr + 0x11 * 4, 0, 8, (value & 0xFF));
	}
	//update manual value
	//reg_bits_set(phy_base + 0xb2 * 4, 2, 1, 0); //reg_cal_update_rule_cfg_ca_manual_mode
	//reg_bits_set(phy_base + 0xb2 * 4, 2, 1, 1); //reg_cal_update_rule_cfg_ca_manual_mode

}


static void ddr_print_scan_head(void)
{
		uint32 vref_min;
		uint32 vref_max;
		//u32 regval=(REG32(0x30400000) >> 24) & 0xff;
		//regval=(1000000/ddr_sck[freq_sel])/regval/4;
		u32 UI=((1000000/ddr_sck[freq_sel])/2);
		u32 regval=UI/255;
		u32 result_perstap=0;
/*Print Start log*/
		dmc_print_str("\r\n********************");
		dmc_print_str("\r\n***0x40400000***");
		switch (ddr_chip_cur.chip_type)
		{
			case DRAM_LPDDR2:
				dmc_print_str("\r\n***0x22222222***");
				break;
			case DRAM_LPDDR3:
				dmc_print_str("\r\n***0x33333333***");
				break;
			case DRAM_LPDDR4:
				dmc_print_str("\r\n***0x44444444***");
				break;
			default:
				dmc_print_str("\r\n***Type Error***");
		}

		dmc_print_str("\r\n***");
		ddr_print_u32_data(ddr_sck[freq_sel]);
		dmc_print_str("***");
		dmc_print_str("\r\n***0x55aa55aa");
		result_perstap=((regval >> 0) & 0xff)*X_INCREASE_STEP;
		//ddr_print_u32_data(result_perstap);
		dmc_print_str(uint8tochar(result_perstap));
		dmc_print_str("***");
		dmc_print_str("\r\n0x73747172\r\n");
		dmc_print_str("0x434f4e54\r\n");

		/*****write*****/
		#ifdef DDR_SCAN_LPDDR4
		store_reboot_value->scan_write_vref_max=LP4_write_training_vref+scan_vref_write_up_offset;
		store_reboot_value->scan_write_vref_min=LP4_write_training_vref-scan_vref_write_down_offset;
		#else
		store_reboot_value->scan_write_vref_max=0xd0+scan_vref_write_up_offset;
		store_reboot_value->scan_write_vref_min=0xd0-scan_vref_write_down_offset;
		#endif
		dmc_print_str("###0x77aa77aa");
		ddr_print_u32_data(store_reboot_value->scan_write_vref_min);//Min
		ddr_print_u32_data(store_reboot_value->scan_write_vref_max);//Max
		dmc_print_str("###\r\n");

		/*****read*****/
		store_reboot_value->scan_read_vref_max=read_phy0_result.deye_vref_db0_result+scan_vref_read_up_offset;
		store_reboot_value->scan_read_vref_min=read_phy0_result.deye_vref_db0_result-scan_vref_read_down_offset;
		dmc_print_str("###0x77aa77bb");
		ddr_print_u32_data(store_reboot_value->scan_read_vref_min);//Min
		ddr_print_u32_data(store_reboot_value->scan_read_vref_max);//Max
		dmc_print_str("###\r\n");

		/*****ca*****/
		#ifdef DDR_SCAN_LPDDR4
		store_reboot_value->scan_ca_vref_max=LP4X_ca_training_vref+scan_vref_ca_up_offset;
		store_reboot_value->scan_ca_vref_min=LP4X_ca_training_vref-scan_vref_ca_down_offset;
		#else
		store_reboot_value->scan_ca_vref_max=(0x50|0x80)+scan_vref_ca_up_offset;
		store_reboot_value->scan_ca_vref_min=(0x50|0x80)-scan_vref_ca_down_offset;
		#endif
		dmc_print_str("###0x77aa77cc");
		ddr_print_u32_data(store_reboot_value->scan_ca_vref_min);//Min
		ddr_print_u32_data(store_reboot_value->scan_ca_vref_max);//Max
		dmc_print_str("###\r\n");
}
static void ddr_print_scan_end(void)
{
	dmc_print_str("0x656e6464\r\n");
}
static void ddr_print_scan_center(void)
{
	dmc_print_str("0x434f4e54\r\n");
}

/*******************************
*Name:ddr_scan_get_training_printresult
*Function:Get training after SDRAM Initial
*         and print result
*Parameter In :NULL
*Parameter Out:NULL
********************************/
static void ddr_scan_get_training_printresult(void)
{
	uint32 i = 0;
	u32 *pResult;
	dmc_print_str("\r\n************Training Delay Line**************\r\n");

	/*Get gucphy0 CA Result and Print result*/
	ca_result_get(DMC_GUCPHY0_BASE, &ca_phy0_result);
	dmc_print_str("\r\ndmc_gucphy0_ca_result\r\n");
	pResult = &(ca_phy0_result.vref_dram_ca_result);
	for (i = 0; i < 4; i++)
	{
		switch (i)
		{
			case 0:
				dmc_print_str("vref_dram_ca_re     :"); break;
			case 1:
				dmc_print_str("ca_pass_window      :"); break;
			case 2:
				dmc_print_str("ca_result_cfg_fine  :"); break;
			case 3:
				dmc_print_str("ca_result_cfg_coarse:"); break;
			case 4:
				dmc_print_str("ca_eye_window_start :"); break;
			case 5:
				dmc_print_str("ca_eye_window_end   :"); break;
		}
		dmc_print_str("0x");
		dmc_print_str(uint8tochar(pResult[i]));
		dmc_print_str("\t");
	}
	/*Get gucphy1 CA Result and Print result*/
	ca_result_get(DMC_GUCPHY1_BASE, &ca_phy1_result);
	dmc_print_str("\r\ndmc_gucphy1_ca_result\r\n");
	pResult = &(ca_phy1_result.vref_dram_ca_result);
	for (i = 0; i < (sizeof(ca_phy1_result) / sizeof(u32)); i++)
	{
		switch (i)
		{
			case 0:
				dmc_print_str("vref_dram_ca_result :"); break;
			case 1:
				dmc_print_str("ca_pass_window      :"); break;
			case 2:
				dmc_print_str("ca_result_cfg_fine  :"); break;
			case 3:
				dmc_print_str("ca_result_cfg_coarse:"); break;
			case 4:
				dmc_print_str("ca_eye_window_start :"); break;
			case 5:
				dmc_print_str("ca_eye_window_end   :"); break;
		}
		dmc_print_str("0x");
		dmc_print_str(uint8tochar(pResult[i]));
		dmc_print_str("\t");
	}

	/*Get read GUCPHY0 result*/

	read_result_get(DMC_GUCPHY0_BASE, &read_phy0_result);
	dmc_print_str("\r\nread_phy0_result\r\n");
	pResult = &(read_phy0_result.deye_vref_db0_result);
	for (i = 0; i < sizeof(read_phy0_result) / sizeof(u32); i++)
	{
		switch (i)
		{
			case 0:
				dmc_print_str("deye_vref_db_result  :"); break;
//				case 1:dmc_print_str("deye_vref_db1_result:");break;
			case 1:
				dmc_print_str("rd_db0_dqsn          :"); break;
			case 2:
				dmc_print_str("rd_db1_dqsn          :"); break;
			case 3:
				dmc_print_str("rd_db0_dqs           :"); break;
			case 4:
				dmc_print_str("rd_db1_dqs           :"); break;
			case 5:
				dmc_print_str("db0_rdq_pass_window  :"); break;
			case 6:
				dmc_print_str("db1_rdq_pass_window  :"); break;
			case 7:
				dmc_print_str("rd_db0_window_start  :"); break;
			case 8:
				dmc_print_str("rd_db0_window_end    :"); break;
			case 9:
				dmc_print_str("rd_db1_window_start  :"); break;
			case 10:
				dmc_print_str("rd_db1_window_end    :"); break;

		}
		dmc_print_str("0x");
		dmc_print_str(uint8tochar(pResult[i]));
		dmc_print_str("\t");
	}

	/*Get read GUCPHY1 result*/
	read_result_get(DMC_GUCPHY1_BASE, &read_phy1_result);
	dmc_print_str("\r\nread_phy1_result\r\n");
	pResult = &(read_phy1_result.deye_vref_db0_result);
	for (i = 0; i < (sizeof(read_phy1_result) / sizeof(u32)); i++)
	{
		switch (i)
		{
			case 0:
				dmc_print_str("deye_vref_dbresult  :"); break;
//				case 1:dmc_print_str("deye_vref_db1_result:");break;
			case 1:
				dmc_print_str("rd_db0_dqsn         :"); break;
			case 2:
				dmc_print_str("rd_db1_dqsn         :"); break;
			case 3:
				dmc_print_str("rd_db0_dqs          :"); break;
			case 4:
				dmc_print_str("rd_db1_dqs          :"); break;
			case 5:
				dmc_print_str("db0_rdq_pass_window :"); break;
			case 6:
				dmc_print_str("db1_rdq_pass_window :"); break;
			case 7:
				dmc_print_str("rd_db0_window_start :"); break;
			case 8:
				dmc_print_str("rd_db0_window_end   :"); break;
			case 9:
				dmc_print_str("rd_db1_window_start :"); break;
			case 10:
				dmc_print_str("rd_db1_window_end   :"); break;
		}
		dmc_print_str("0x");
		dmc_print_str(uint8tochar(pResult[i]));
		dmc_print_str("\t");
	}

	/*Get write phy0 result*/
	write_result_get(DMC_GUCPHY0_BASE, &write_phy0_result);
	dmc_print_str("\r\nwrite_phy0_result\r\n");
	pResult = &(write_phy0_result.vref_dram_adj_result);
	for (i = 1; i < (sizeof(write_phy0_result) / sizeof(u32)); i++)
	{
		switch (i)
		{
			case 0:
				dmc_print_str("vref_dram_adj_result:"); break;
			case 1:
				dmc_print_str("db0_wdq_bt_result   :"); break;
			case 2:
				dmc_print_str("db1_wdq_bt_result   :"); break;
			case 3:
				dmc_print_str("db0_wdq_result      :"); break;
			case 4:
				dmc_print_str("db1_wdq_result      :"); break;
			case 5:
				dmc_print_str("db0_wdq_pass_window :"); break;
			case 6:
				dmc_print_str("db1_wdq_pass_window :"); break;
			case 7:
				dmc_print_str("wr_db0_window_start :"); break;
			case 8:
				dmc_print_str("wr_db0_window_end   :"); break;
			case 9:
				dmc_print_str("wr_db1_window_start :"); break;
			case 10:
				dmc_print_str("wr_db1_window_end   :"); break;
		}
		dmc_print_str("0x");
		dmc_print_str(uint8tochar(pResult[i]));
		dmc_print_str("\t");
	}

	/*Get write phy1 result*/
	write_result_get(DMC_GUCPHY1_BASE, &write_phy1_result);
	dmc_print_str("\r\nwrite_phy1_result\r\n");
	pResult = &(write_phy1_result.vref_dram_adj_result);
	for (i = 1; i < (sizeof(write_phy1_result) / sizeof(u32)); i++)
	{
		switch (i)
		{
			case 0:
				dmc_print_str("vref_dram_adj_result:"); break;
			case 1:
				dmc_print_str("db0_wdq_bt_result   :"); break;
			case 2:
				dmc_print_str("db1_wdq_bt_result   :"); break;
			case 3:
				dmc_print_str("db0_wdq_result      :"); break;
			case 4:
				dmc_print_str("db1_wdq_result      :"); break;
			case 5:
				dmc_print_str("db0_wdq_pass_window :"); break;
			case 6:
				dmc_print_str("db1_wdq_pass_window :"); break;
			case 7:
				dmc_print_str("wr_db0_window_start :"); break;
			case 8:
				dmc_print_str("wr_db0_window_end   :"); break;
			case 9:
				dmc_print_str("wr_db1_window_start :"); break;
			case 10:
				dmc_print_str("wr_db1_window_end   :"); break;
		}
		dmc_print_str("0x");
		dmc_print_str(uint8tochar(pResult[i]));
		dmc_print_str("\t");
	}
	dmc_print_str("\r\n");

	/*Print PU/PD PVT Calibration Result*/
	dmc_print_str("PHY0 PU/PD Calibration Result:\r\n");
	dmc_print_str("PU Calibration Result:");
	ddr_print_u32_data(reg_bits_get(PUPD_PHY0_IOPVT_CALIBRATION_RESULT, 0, 8));
	dmc_print_str("PD Calibration Result:");
	ddr_print_u32_data(reg_bits_get(PUPD_PHY0_IOPVT_CALIBRATION_RESULT, 16, 8));
	dmc_print_str("\r\n");
	dmc_print_str("PHY1 PU/PD Calibration Result:\r\n");
	dmc_print_str("PU Calibration Result:");
	ddr_print_u32_data(reg_bits_get(PUPD_PHY1_IOPVT_CALIBRATION_RESULT, 0, 8));
	dmc_print_str("PD Calibration Result:");
	ddr_print_u32_data(reg_bits_get(PUPD_PHY1_IOPVT_CALIBRATION_RESULT, 16, 8));
	dmc_print_str("\r\n");
}

/****************************************
*FUNCTION:DDR scan bist for one bit
*OUTPUT:NULL
*IN    :vref_val: Current set vref value
*       deye_vref_result:Training Vref Value
*       db_dqs:Training delay time
*****************************************/

static void ddr_print_bist_result()
{
	u32 ret = 0;
	u8 pattern_i = 0;
	u32 ret_sum = 0;
	u32 vref_mask = 0;
	//step. bist operation and record the pass and fail
	/*Only use for one pattern for bist*/
	if (dmc_ddr_test(0) == 0) //1:faild 0:success

	{
		ret = 0;
	} else
	{ret = 1;}
	if (ret) //fail
	{
		FAIL;
	} else //success
	{
		PASS;
	}


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
static void ddr_offline_scan_parameter(scan_type_parameter type_para, u16 vref_val)
{
	uint32 i = 0;
	uint32 read_data = 0;
	u32 item;
	pass_flag = 1;
	fail_flag = 1;

	first_pass = 0;
	last_pass = 0;

	scan_type_parameter temp_parameter = type_para; //Temporarily store


	/***If scan Write or Read should store some parameter ****/
	if (temp_parameter.type == scan_write)
	{
		read_data = REG32(temp_parameter.dmc_phy_base + freq_sel * 20 * 4 + 0x12 * 4);
	} else if (temp_parameter.type == scan_read)
	{
		read_data = REG32(temp_parameter.dmc_phy_base + freq_sel * 20 * 4 + 0x11 * 4);
	}
	/****Loop set parameter and bist test****/
	for (i = 0; i <= temp_parameter.scan_num; i = i + X_INCREASE_STEP)
	{
		switch ((int)(temp_parameter.type)) //Chose scan type
		{
			case 0:
				phy_delay_line_set_wr(temp_parameter.dmc_phy_base, i, freq_sel, temp_parameter.data_module); break;
			case 1:
				phy_delay_line_set_rd(temp_parameter.dmc_phy_base, i, freq_sel, temp_parameter.data_module); break;
			default:
				dmc_print_str("\r\n************temp_parameter.type is error**********\r\n");
		}
		//step. bist operation and record the pass and fail
		if (temp_parameter.type == scan_read)
		{
				/*index*/
				dmc_print_str("0x0\t");
				/*BYTE*/
				if (temp_parameter.data_module==data_module_0)
					item = SCAN_ROW1_SYMBOL | (SCAN_ITEM_BYTE << SCAN_ITEM_OFFSET)|data_module_0;
				else
					item = SCAN_ROW1_SYMBOL | (SCAN_ITEM_BYTE<<SCAN_ITEM_OFFSET)|data_module_1;
				ddr_print_u32_data(item);
				dmc_print_str("\t");
#ifdef DRIVER_STRENGTH
				/*driver strength*/
				item = SCAN_ROW2_SYMBOL | (SCAN_ITEM_DS << SCAN_ITEM_OFFSET)|(driver_strength[store_reboot_value->driver_strength-DRIVER_STRENGTH_DIFFERENCE]);
				ddr_print_u32_data(item);
				dmc_print_str("\t");
#endif
				/*PHY*/
				if (temp_parameter.dmc_phy_base == DMC_GUCPHY0_BASE) //Display message
					item=SCAN_ROW3_SYMBOL | (SCAN_ITEM_PHY<<SCAN_ITEM_OFFSET)|0x0;
				else
					item=SCAN_ROW3_SYMBOL | (SCAN_ITEM_PHY<<SCAN_ITEM_OFFSET)|0x1;
				ddr_print_u32_data(item);
				dmc_print_str("\t");

				/*VREF*/
#ifdef DDR_SCAN_VREF_ENABLE
				item = SCAN_ROW4_SYMBOL | (SCAN_ITEM_VREF << SCAN_ITEM_OFFSET)|(vref_val);
				ddr_print_u32_data(item);
				dmc_print_str("\t");
#endif
				/*Read delay*/
				item = SCAN_COLUMN1_SYMBOL | (SCAN_ITEM_RD_DL<<SCAN_ITEM_OFFSET) | (i/X_INCREASE_STEP);//i/2 => 0,2,4...=> 0,1,2...
				ddr_print_u32_data(item);
				/*bist result*/
				ddr_print_bist_result();
				dmc_print_str("\r\n");
		} else if (temp_parameter.type == scan_write)
		{
				/*index*/
				dmc_print_str("0x0\t");
				/*BYTE*/
				if (temp_parameter.data_module==data_module_0)
					item = SCAN_ROW1_SYMBOL | (SCAN_ITEM_BYTE << SCAN_ITEM_OFFSET)|data_module_0;
				else
					item = SCAN_ROW1_SYMBOL | (SCAN_ITEM_BYTE << SCAN_ITEM_OFFSET)|data_module_1;
				ddr_print_u32_data(item);
				dmc_print_str("\t");
#ifdef DRIVER_STRENGTH
				/*driver strength*/
				item = SCAN_ROW2_SYMBOL | (SCAN_ITEM_DS << SCAN_ITEM_OFFSET)|(driver_strength[store_reboot_value->driver_strength-DRIVER_STRENGTH_DIFFERENCE]);
				ddr_print_u32_data(item);
				dmc_print_str("\t");
#endif
				/*PHY*/
				if (temp_parameter.dmc_phy_base == DMC_GUCPHY0_BASE) //Display message
					item=SCAN_ROW3_SYMBOL | (SCAN_ITEM_PHY<<SCAN_ITEM_OFFSET)|0x0;
				else
					item=SCAN_ROW3_SYMBOL | (SCAN_ITEM_PHY<<SCAN_ITEM_OFFSET)|0x1;
				ddr_print_u32_data(item);
				dmc_print_str("\t");


				/*VREF*/
#ifdef DDR_SCAN_VREF_ENABLE
				item = SCAN_ROW4_SYMBOL | (SCAN_ITEM_VREF2 << SCAN_ITEM_OFFSET)|(vref_val);
				ddr_print_u32_data(item);
				dmc_print_str("\t");
#endif

				/*write delay*/
				item = SCAN_COLUMN1_SYMBOL | (SCAN_ITEM_WR_DL<<SCAN_ITEM_OFFSET) | (i/X_INCREASE_STEP);//i/2 => 0,2,4...=> 0,1,2...
				ddr_print_u32_data(item);
				/*bist result*/
				ddr_print_bist_result();
				dmc_print_str("\r\n");
		}

	}
	/*Data Restore*/
	if (temp_parameter.type == scan_write) //Restore
	{
		REG32(temp_parameter.dmc_phy_base + freq_sel * 20 * 4 + 0x12 * 4) = read_data;
		//update
		reg_bits_set(temp_parameter.dmc_phy_base + 0xb2 * 4, 3, 1, 0);
		reg_bits_set(temp_parameter.dmc_phy_base + 0xb2 * 4, 3, 1, 1);
	} else if (temp_parameter.type == scan_read)
	{
		REG32(temp_parameter.dmc_phy_base + freq_sel * 20 * 4 + 0x11 * 4) = read_data;
		//update
		//reg_bits_set(temp_parameter.dmc_phy_base + 0xb2 * 4, 2, 1, 0);
		//reg_bits_set(temp_parameter.dmc_phy_base + 0xb2 * 4, 2, 1, 1);
	}
}
/******************************
*Function:scan ca
*
*******************************/
static void pub_power_up(void)
{
	reg_bits_set(PD_PUB_SYS_CFG, 25, 1, 0x1); //pub Off
	while (((REG32(PWR_STATUS2_DBG) >> 20) & 0x1f) != 0x7); //pd_pub_sys_state


	reg_bits_set(PD_PUB_SYS_CFG, 25, 1, 0x0); //pub ON
	while (((REG32(PWR_STATUS2_DBG) >> 20) & 0x1f) != 0x0); //pd_pub_sys_state //PUB poweroff
}
static void dram_pub_power_restart(void)
{
	store_reboot_value->window_fail_flag = 0;
	regulator_disable("vddmem"); //DRAM poweroff
	dmc_sprd_delay(20000);
	pub_power_up();
	regulator_enable("vddmem");  //DRAM ON
	dmc_sprd_delay(20000);
}
static void ddr_offline_scan_parameter_ca(scan_type_parameter type_para, u16 vref_val)
{
	uint32 i = 0;
	u8 ret = 0;
	u32 item;
	uint32 read_data_a = 0;
	uint32 read_data_b = 0;
	scan_type_parameter temp_parameter = type_para; //Temporarily store
	//back updata
	read_data_a = REG32(DMC_GUCPHY0_BASE + freq_sel * 20 * 4 + 0x0c * 4);
	read_data_b = REG32(DMC_GUCPHY1_BASE + freq_sel * 20 * 4 + 0x0c * 4);
	/****Loop set parameter and bist test****/
	i = store_reboot_value->scan_x;
	for (; i <= temp_parameter.scan_num;)
	{
		/*Set Delay*/
		phy_delay_line_set_ca(temp_parameter.dmc_phy_base, i, freq_sel);
		/*index*/
		dmc_print_str("0x0\t");
		/*CA has only situration for PHY adn BYTE*/
		/*PHY*/
		if (temp_parameter.dmc_phy_base == DMC_GUCPHY0_BASE) //Display message
			item = SCAN_ROW1_SYMBOL | (SCAN_ITEM_PHY << SCAN_ITEM_OFFSET) | 0x0;
		else
			item = SCAN_ROW1_SYMBOL | (SCAN_ITEM_PHY << SCAN_ITEM_OFFSET) | 0x1;
		ddr_print_u32_data(item);
		dmc_print_str("\t");
//		/*BYTE*/
//		item = SCAN_ROW2_SYMBOL | (SCAN_ITEM_BYTE << SCAN_ITEM_OFFSET) | data_module_0;
//		ddr_print_u32_data(item);
//		dmc_print_str("\t");

#ifdef DRIVER_STRENGTH
		/*driver strength*/
		item = SCAN_ROW2_SYMBOL | (SCAN_ITEM_DS << SCAN_ITEM_OFFSET)|(driver_strength[store_reboot_value->driver_strength-DRIVER_STRENGTH_DIFFERENCE]);
		ddr_print_u32_data(item);
		dmc_print_str("\t");
#endif
		/*VREF*/
#ifdef DDR_SCAN_VREF_ENABLE
		item = SCAN_ROW3_SYMBOL | (SCAN_ITEM_VREF1 << SCAN_ITEM_OFFSET)|vref_val;
		ddr_print_u32_data(item);
		dmc_print_str("\t");
#endif
		/*CA delay*/
		item = SCAN_COLUMN1_SYMBOL | (SCAN_ITEM_CA_DL<<SCAN_ITEM_OFFSET) | (i/X_INCREASE_STEP);//i/2 => 0,2,4...=> 0,1,2...
		ddr_print_u32_data(item);
		ddr_print_bist_result();
		dmc_print_str("\r\n");
		i = i + X_INCREASE_STEP;
		store_reboot_value->scan_x = i;
		if (store_reboot_value->window_fail_flag == 0) //Judge all file in line
			_start();
		else
		{
			//dmc_print_str("\r\nDram and pub power restart!!!!\r\n");
			store_reboot_value->window_fail_flag = 0;
			dram_pub_power_restart();
			_start();
		}
	}
	pass_flag = 1;
	fail_flag = 1;
//	sdram_reinit();//Reinitial

}
/*******************************
*Function:Print 32 bit data
*Name    :ddr_print_set_register
*In      :u32 int data
*out     :NULL
********************************/
static void ddr_print_u32_data(u32 print_data)
{
	dmc_print_str("0x");
	dmc_print_str(uint8tochar((print_data >> 24) & 0xff));
	dmc_print_str(uint8tochar((print_data >> 16) & 0xff));
	dmc_print_str(uint8tochar((print_data >> 8) & 0xff));
	dmc_print_str(uint8tochar((print_data >> 0) & 0xff));
}
/**********************************************************
** Function:u32tostr
** u32 convert string
***********************************************************/
static void u32tostr(unsigned long dat, char *str)
{
	char temp[20];
	unsigned char i = 0, j = 0;
	i = 0;
	while (dat)
	{
		temp[i] = dat % 10 + 0x30;
		i++;
		dat /= 10;
	}
	j = i;
	for (i = 0; i < j; i++)
	{
		str[i] = temp[j - i - 1];
	}
	if (!i)
	{str[i++] = '0';}
	str[i] = 0;
}
static char pr_str[12];
static void ddr_print_u32_dec_data(u32 print_data)
{
	u32tostr(print_data, pr_str);
	dmc_print_str(pr_str);
}



/*Set write vref for lpddr4x*/
static void ddr_scan_set_write_vref_lpddr4(int vref)
{
//#ifdef DDR_SCAN_LPDDR4
	if (ddr_chip_cur.chip_type == DRAM_LPDDR4 )
	{
		lpddr_dmc_mrw(CMD_CS_BOTH, 0xe, vref); //mr14
	}
	else
		dmc_print_str("\r\nOperate ddr_scan_set_write_vref_lpddr4x is error\r\n");

}
/*Set CA vref for lpddr4x*/
static void ddr_scan_set_ca_vref_lpddr4(int vref)
{
//#ifdef DDR_SCAN_LPDDR4
	if (ddr_chip_cur.chip_type == DRAM_LPDDR4 )
	{
		lpddr_dmc_mrw(CMD_CS_BOTH, 0xc, vref); //mr12
	}
	else
		dmc_print_str("\r\nOperate ddr_scan_set_ca_vref_lpddr4x is error\r\n");
}
/*****************************************
*Name : Off line scan write:
* Note:1.maybe need to go into selfrefresh status when update dll value
*	   2.maybe need to reset after scan one time
******************************************/

/*according PHY&DataByte scan*/
static void ddr_offline_scan_wr(u16 max, u16 min, best_para *pPara)
{
	u8 i = 0;
	int vref_lv = 0;
	uint32 write_buf_size=0;
	if (ddr_chip_cur.chip_type == DRAM_LPDDR4 )
	{
		write_buf_size=(sizeof(phy_scan_para_wr_lp4) / sizeof(scan_type_parameter));
	}else
	{
		write_buf_size=(sizeof(phy_scan_para_wr_lp3) / sizeof(scan_type_parameter));
	}
	reg_bits_set(PHY_VREFE_ADDRESS, 22, 1, 0); //phy_vref_hi_c
	reg_bits_set(PHY_VREFE_ADDRESS, 23, 1, 0); //phy_vref_pd
	//dmc_print_str("\r\noff line scan write\r\n");

	for (i = 0; i < write_buf_size; i++)
	{
		vref_lv = max;
#ifdef DDR_SCAN_VREF_ENABLE
		for (; vref_lv >=min; vref_lv=vref_lv-WRITE_VREF_STEP)
		{
#endif
		//#ifndef DDR_SCAN_LPDDR4
			if (ddr_chip_cur.chip_type != DRAM_LPDDR4 )
			{
				reg_bits_set(PHY_VREFE_ADDRESS, 24, 8, vref_lv); //set vref value
				dmc_sprd_delay(20000); //20ms
			}
			else{
					ddr_scan_set_write_vref_lpddr4(vref_lv);  //set vref value
					if (vref_lv == 0x40)
					{
						vref_lv = 0x33;
					}
				}
			//Scan and print
			if (ddr_chip_cur.chip_type == DRAM_LPDDR4 )
				ddr_offline_scan_parameter(phy_scan_para_wr_lp4[i], vref_lv);
			else
				ddr_offline_scan_parameter(phy_scan_para_wr_lp3[i], vref_lv);
#ifdef DDR_SCAN_VREF_ENABLE
		}
#endif
		//dmc_print_str("\r\n");
	}
//#ifndef DDR_SCAN_LPDDR4
	if (ddr_chip_cur.chip_type != DRAM_LPDDR4 ){
		reg_bits_set(PHY_VREFE_ADDRESS, 24, 8, 0xd7); //set best vref value
		dmc_sprd_delay(20000); //20ms
		}
}

/*****************************************
*step  .Off line Scan read and print
*Note:1 need to go into selfrefresh status when update dll value
*2 Need to before scan back up and after scan restore
*****************************************/
/*
	 LOOP1: PHY &  DATA MODULE (4 times)
		 LOOP2: VREF  (ACCORDING PHY &  DATA MODULE SET ADDRESS)
			 LOOP3: scan parameter  FUNCTION:ddr_offline_scan_parameter
*/
//void ddr_offline_scan_rd(vref_mes vref_temp)

/*according PHY&DataByte scan*/
static void ddr_offline_scan_rd(u16 max, u16 min, best_para *pPara)
{
	u8 i = 0;
	int vref_val = 0;

	vref_address_0 = DMC_GUCPHY0_BASE + vrefi_offset[freq_sel]; //confirm vref register
	vref_address_1 = DMC_GUCPHY1_BASE + vrefi_offset[freq_sel];

	for (i = 0; i < (sizeof(phy_scan_para_rd) / sizeof(scan_type_parameter)); i++)  //pay & data module
	{
		vref_val = max;
#ifdef DDR_SCAN_VREF_ENABLE
		for (; vref_val >= min; vref_val=vref_val-READ_VREF_STEP)
		{
#endif
			reg_bits_set(vref_address_0, 0, 8, vref_val);
			reg_bits_set(vref_address_1, 0, 8, vref_val);

			reg_bits_set(vref_address_0, 8, 8, vref_val);
			reg_bits_set(vref_address_1, 8, 8, vref_val);

			dmc_sprd_delay(20000); //20ms
			ddr_offline_scan_parameter(phy_scan_para_rd[i], vref_val);
			//dmc_print_str("\r\n");
#ifdef DDR_SCAN_VREF_ENABLE
		}
#endif
	}
	//dmc_print_str("\r\n");
}

static void ddr_offline_scan_ca(u16 vref_max, u16 vref_min)
{
	int i = 0;
	int vref_lv = 0;
	u8 test_print = 0;
	uint32 ca_buf_size=0;
	//close auto refresh
	reg_bits_set(0x300010c,12,1,0);
	//close DMC auto sleep
	reg_bits_set(0x30000000,8,2,0);
	if (ddr_chip_cur.chip_type == DRAM_LPDDR4 )
	{
		ca_buf_size = (sizeof(phy_scan_para_ca_lp4) / sizeof(scan_type_parameter));
	}else
	{
		ca_buf_size = (sizeof(phy_scan_para_ca_lp3) / sizeof(scan_type_parameter));
	}
	/*set vrefe for scan ca*/
	reg_bits_set(PHY_VREFE_ADDRESS, 22, 1, 0); //phy_vref_hi_c
	reg_bits_set(PHY_VREFE_ADDRESS, 23, 1, 0); //phy_vref_pd
	vref_lv = (store_reboot_value->vref_lv);
	i = store_reboot_value->phy_num;
	for (; i < ca_buf_size;)  //CA only scan PHY0
	{
#ifdef DDR_SCAN_VREF_ENABLE
		for (; vref_lv >= vref_min;) //VREF
		{
#endif

//#ifdef DDR_SCAN_LPDDR4
		if (ddr_chip_cur.chip_type == DRAM_LPDDR4 )
		{
			ddr_scan_set_ca_vref_lpddr4(vref_lv); /*set vref value for LPDDR4*/
			if (vref_lv == 0x40)
			{
				vref_lv = 0x33;
			}
			ddr_offline_scan_parameter_ca(phy_scan_para_ca_lp4[i], vref_lv);
		}
		else/*LP3*/
		{
				reg_bits_set(PHY_VREFE_ADDRESS, 24, 8, vref_lv); //set vref value for LPDDR3
				//reg_bits_set(PHY_VREFE_ADDRESS,31,1,1);//always keep 1 for bit 31 according email
				dmc_sprd_delay(20000); //20ms
				ddr_offline_scan_parameter_ca(phy_scan_para_ca_lp3[i], vref_lv);
		}

		if ((first_pass == 0) && (last_pass == 0)) //Try this test
		{
			store_reboot_value->window_fail_flag = 1; /*Restart Dram Power & Power*/
		}
		first_pass = 0; //Reset rom first_pass&last_pass Value  -test
		last_pass = 0;
		store_reboot_value->scan_x = 0;
		vref_lv=vref_lv-CA_VREF_STEP;
		store_reboot_value->vref_lv = vref_lv;
#ifdef DDR_SCAN_VREF_ENABLE
		}
#endif
		/*Restore some variable*/
		store_reboot_value->vref_lv = CA_SCAN_MAX;
		vref_lv = CA_SCAN_MAX;
		i = i + 1;
		store_reboot_value->phy_num = i;
		first_pass = 0;
		last_pass = 0;
	}

}


/*******************************
*Name:ddr_offline_scan_seq
*Function:Main Sacn sequence   scan rd¡¢wr and ca
*Parameter In :NULL
*Parameter Out:NULL
********************************/
static void ddr_offline_scan_seq(void)
{
	u32 back_register_0 = 0;
	u32 back_register_1 = 0;
	reg_bits_set(0x402b00b0, 8, 1, 0); //Enable address 0x800000 space
	reg_bits_set(0x402b00cc, 20, 1, 0);
	memset(&read_dac_para, 0, sizeof(read_dac_para));
	memset(&read_op_para, 0, sizeof(read_op_para));
	memset(&write_dac_para, 0, sizeof(write_dac_para));

	REG32(0x30000124) = 0;
	dmc_sprd_delay(2); //2us


	if (store_reboot_value->read_write_end_flag == 0) //Avoid scan ca repeat call read & write function
	{

#ifdef DDR_SCAN_READ
		/*Scan Vrefi Read*/
		vref_address_0 = DMC_GUCPHY0_BASE + vrefi_offset[freq_sel];
		vref_address_1 = DMC_GUCPHY1_BASE + vrefi_offset[freq_sel];
		back_register_0 = REG32(vref_address_0);
		back_register_1 = REG32(vref_address_1);
		//ddr_offline_scan_rd(VREFI_DAC_MAX, VREFI_DAC_MIN, &read_dac_para);
		ddr_offline_scan_rd(store_reboot_value->scan_read_vref_max,store_reboot_value->scan_read_vref_min,&read_dac_para);
		REG32(vref_address_0) = back_register_0;
		REG32(vref_address_1) = back_register_1;
		dmc_sprd_delay(20000); //20ms
#endif
#ifdef DDR_SCAN_READ
#ifdef DDR_SCAN_WRITE
		ddr_print_scan_center();
#endif
#endif
#ifdef DDR_SCAN_WRITE
		//Scan VREFE WRITE
		back_register_0 = REG32(PHY_VREFE_ADDRESS);
		//ddr_offline_scan_wr(VREFE_DAC_MAX, VREFE_DAC_MIN, &write_dac_para);
		ddr_offline_scan_wr(store_reboot_value->scan_write_vref_max,store_reboot_value->scan_write_vref_min,&write_dac_para);
		REG32(PHY_VREFE_ADDRESS) = back_register_0;
		dmc_sprd_delay(20000); //20ms
#endif
#ifdef DDR_SCAN_CA
		ddr_print_scan_center();
#endif
		store_reboot_value->read_write_end_flag = 1;
	}
#ifdef DDR_SCAN_CA
	//ddr_offline_scan_ca(CA_SCAN_MAX, CA_SCAN_MIN); //Debug for 0xf0 Normal Set:(VREFE_DAC_MAX,VREFE_DAC_MIN);
	ddr_offline_scan_ca(store_reboot_value->scan_ca_vref_max,store_reboot_value->scan_ca_vref_min);
#endif


}
#ifndef RD_DDR_SCAN
#ifdef DRIVER_STRENGTH
void ddr_scan_vdd_seq(void)/* Include driver Strenth*/
{
	unsigned char mr3_register =0x3;
	//u32 vddq,vddcore;
	reg_bits_set(0x402b00b0, 8, 1, 0); //Enable address 0x800000 space
	reg_bits_set(0x402b00cc, 20, 1, 0);
	freq_sel = (REG32(0x3000012c) >> 8) & 0x7; //get freq for register
	if (ddr_chip_cur.chip_type == DRAM_LPDDR4 )
	{
		//LP4_write_training_vref = reg_bits_get(0x402b00d0, 24, 8); //LP4 write training must read set register
		dmc_mrr(CMD_CS_0, 14, &LP4_write_training_vref, 10000);
		LP4_write_training_vref=LP4_write_training_vref&0x7f;
		dmc_mrr(CMD_CS_0, 12, &LP4X_ca_training_vref, 10000);
		LP4X_ca_training_vref=LP4X_ca_training_vref&0x7f;
	}
//#endif
	if (store_reboot_value->rom_start_flag != 0xaa)
	{
		memset(store_reboot_value, 0, sizeof(rom_value)); //Initial rom arear
		store_reboot_value->rom_start_flag = 0xaa;
		store_reboot_value->vref_lv = CA_SCAN_MAX;
		store_reboot_value->scan_x = 0;
		store_reboot_value->old_vref_lv = 0;
		store_reboot_value->phy_num = 0;
		store_reboot_value->old_phy_num = 2; //Any value except 0
		store_reboot_value->window_fail_flag = 0;
		pass_flag = 1;
		fail_flag = 1;
#ifdef DDR_SCAN_LPDDR3
		store_reboot_value->driver_strength = DRIVER_STRENGTH_34;
#else
		store_reboot_value->driver_strength =0x04;/*60 O*/
#endif
		store_reboot_value->old_driver_strength=0;

		store_reboot_value->print_vddcore_training_flag = 0;
		store_reboot_value->print_vddq_training_flag = 0;

		/*step 1. Start SDRAM Init*/
		/*step 2. read out Initial training result and print*/
		ddr_scan_get_training_printresult();
		ddr_print_scan_head(); //print scan head
	}
/*Loop io driver strength write mr3*/
#ifdef DDR_SCAN_LPDDR3
	for (; (store_reboot_value->driver_strength) <= DRIVER_STRENGTH_48; store_reboot_value->driver_strength++)/*34,40,48*/
#else
	for (; (store_reboot_value->driver_strength) <= DRIVER_STRENGTH_40; store_reboot_value->driver_strength++)/*40,48,60*/
#endif
	{
		if (store_reboot_value->driver_strength	!=	store_reboot_value->old_driver_strength)
		{
			#ifdef DDR_SCAN_LPDDR3
			lpddr_dmc_mrw(CMD_CS_BOTH,0x3, store_reboot_value->driver_strength);//only LPDDR3
			#else
			mr3_register=0x3;
			mr3_register |= (((store_reboot_value->driver_strength)&0x7)<<3);/*PDDS*/
			mr3_register |= (0 << 6);/*Close DBI*/
			mr3_register |= (1 << 7);
			lpddr_dmc_mrw(CMD_CS_BOTH,0x3, mr3_register);
			#endif

			store_reboot_value->old_driver_strength=store_reboot_value->driver_strength;
		}
		ddr_offline_scan_seq();
		ddr_print_scan_center();
	 /*Clear store rom scan variable prepare for repeat call ddr scan seq*/
	  {
		 store_reboot_value->vref_lv=CA_SCAN_MAX;
		 store_reboot_value->scan_x=0;
		 store_reboot_value->old_vref_lv=0;
		 store_reboot_value->phy_num=0;
		 store_reboot_value->old_phy_num=2;//Any value except 0
		 store_reboot_value->window_fail_flag=0;
		 store_reboot_value->read_write_end_flag=0;
		 pass_flag=1;
		 fail_flag=1;
	  }
	}
	ddr_print_scan_end();


	while (1);
}
#else
void ddr_scan_vdd_seq(void)/*No driver Strenth*/
{
	dmc_print_str("No driver Strenth\r\n");
	//u32 vddq,vddcore;
	reg_bits_set(0x402b00b0, 8, 1, 0); //Enable address 0x800000 space
	reg_bits_set(0x402b00cc, 20, 1, 0);
	freq_sel = (REG32(0x3000012c) >> 8) & 0x7; //get freq for register
//#ifdef DDR_SCAN_LPDDR4
	if (ddr_chip_cur.chip_type == DRAM_LPDDR4 )
	{
		LP4_write_training_vref = reg_bits_get(0x402b00d0, 24, 8); //LP4 write training must read set register
	}
	if (store_reboot_value->rom_start_flag != 0xaa)
	{
		memset(store_reboot_value, 0, sizeof(rom_value)); //Initial rom arear
		store_reboot_value->rom_start_flag = 0xaa;
		store_reboot_value->vref_lv = CA_SCAN_MAX;
		store_reboot_value->scan_x = 0;
		store_reboot_value->old_vref_lv = 0;
		store_reboot_value->phy_num = 0;
		store_reboot_value->old_phy_num = 2; //Any value except 0
		store_reboot_value->window_fail_flag = 0;
		pass_flag = 1;
		fail_flag = 1;
		store_reboot_value->print_vddcore_training_flag = 0;
		store_reboot_value->print_vddq_training_flag = 0;

		/*step 1. Start SDRAM Init*/
		/*step 2. read out Initial training result and print*/
		ddr_print_scan_head(); //print scan head


	}

	ddr_offline_scan_seq();
	ddr_print_scan_end();

	while (1);
}
#endif
#endif
#endif
