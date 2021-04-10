#include <asm/types.h>
#include <common.h>
#include <asm/arch/clk_para_config.h>
#include "dmc_sprd_r2p0.h"
#include "dmc_sprd_r2p0_bist.h"

 /* Note: CA_PATTERN_RISE_PHASE1_MAP (val1) should be mapped to CA_PATTERN_RISE (val)
  *  CA_PATTERN_RISE_PHASE1_MAP: bits{14:0} =  pack{val[8], 0,val[7], 0,val[6], 0,val[5], 0,val[3], 0,val[2], 0,val[1], 0,val[0]}
  *  CA_PATTERN_RISE_PHASE2_MAP: bits{8:0}   =  pack{val[9], 0,0,0,0,0,0,0,val[4]}
  */
#define CA_PATTERN_RISE  0x3FF
#define CA_PATTERN_RISE_PHASE1_MAP \
	((CA_PATTERN_RISE & 1) | \
	 ((CA_PATTERN_RISE>>1 & 1) << 2) | \
	 ((CA_PATTERN_RISE>>2 & 1) << 4) | \
	 ((CA_PATTERN_RISE>>3 & 1) << 6) | \
	 ((CA_PATTERN_RISE>>5 & 1) << 8) | \
	 ((CA_PATTERN_RISE>>6 & 1) << 10) | \
	 ((CA_PATTERN_RISE>>7 & 1) << 12) | \
	 ((CA_PATTERN_RISE>>8 & 1) << 14))
#define CA_PATTERN_RISE_PHASE2_MAP \
	 (((CA_PATTERN_RISE>>4) & 1)  | \
	 ((CA_PATTERN_RISE>>9 & 1) << 8))

#define CA_PATTERN_MASK  0x3FF   // 10 bits in total
#define CA_PHASE1_MAP_MASK  0x5555   // for bit[8:5] & bits[3:0]
#define CA_PHASE2_MAP_MASK  0x0101   // for bit[9] & bit[5]

#define MAX_CA_MAIN_DELAY (1<<7)
#define MAX_CA_BIT_DELAY (1<<5)
#define MAX_CA_CLK_DL  ((1<<3)-1)

#define MAX_DQ_DELAY  (1<<7)
#define MAX_DQ_BITS_DELAY (1<<5)
#define MAX_DM_DELAY  (1<<5)

#define INIT_DQ_IN_DL    (7*4)
#define MIN_WINDOW  10

#ifdef CONFIG_SOC_SHARKLJ1
#define MIN_DQ_DELAY 0
#else
#define MIN_DQ_DELAY 0
#endif

//#define USE_CA_BITSKEW
#define USE_CA_TRAINING
#define USE_RDE_TRAINING
#define USE_WRE_TRAINING
//#define USE_WR_LEVELING

#define TRAINING_BIST_SIZE  0x80000  // 512KBytes. It should not be larger than BIST_RESERVE_SIZE

//#define  DDR_TRAINGING_LOG
extern DRAM_CHIP_INFO ddr_chip_cur;
extern u32 ddr_clk_array[];
static u32 bist_mask[4] = {0xffffff00, 0xffff00ff, 0xff00ffff, 0x00ffffff};

#ifdef DDR_TRAINGING_LOG
char  log_string[32];
char *  toStrDec(u32 val)
{
	int i, j, num;
	u32 temp = val;

	num = 0;
	do
	{
		num++;
		temp /= 10;
	}while(temp >0);

	for (i = num-1; i >=0; i--)
	{
		temp = (val%10) + 0x30; val /= 10;
		log_string[i] = temp&0xff;
	}
	log_string[num] = ' ';
	log_string[num+1] = 0;
	return log_string;
}

char *  toStrHex(u32 val)
{
	int i, j, num;
	u32 temp = val;

	log_string[0] = '0';
	log_string[1] = 'x';
	for (i = 0; i < 8; i++)
	{
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

static int  print_Dec(s32 val)
{
	if(val <0)
	{
		dmc_print_str("-");
		val = 0 - val;
	}
	dmc_print_str(toStrDec(val));
	return 0;
}

static int  print_Hex(u32 val)
{
	dmc_print_str(toStrHex(val));
	return 0;
}

static int print_String(const char *string)
{
	dmc_print_str(string);
	return 0;
}
#else
static int  print_Dec(s32 val) {return 0;}
static int  print_Hex(u32 val) {return 0;}
static int print_String(const char *string) {return 0;}
#endif

int get_half_mode()
{
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 regval, idx;

	idx = (pdmc->dmc_dcfg11>> 4) & 0x3; /* drf_dfs_reg_sel */
	regval = pdmc->dmc_dtmg_f[idx][11];

	return (regval>>8)&1;
}

/* Fast bist : keep register as previous value set .... just trigger bist to save time ..*/
static int fast_sipi_bist_test()
{
	u32 regval;
	u32 len;
	int tout;
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	static u32 first_flag = 1;
	u32 dcfg0_bkup;

	if (first_flag)
	{
		print_Hex(pdmc->dmc_bist[1]);
		print_String(" bist_len\r\n");
		first_flag = 0;
		len = TRAINING_BIST_SIZE;
		if (len > BIST_RESERVE_SIZE)
			len = BIST_RESERVE_SIZE;

		pdmc->dmc_bist[1] = len>>2;  // bist_len register value unit in "Word"(=4Bytes)
		print_Hex(pdmc->dmc_bist[1]);
		print_String(" bist_len\r\n");
	}

	/* Step3: set colum an row*/
	if (ddr_chip_cur.unsymmetry)
	{
		dcfg0_bkup = regval = pdmc->dmc_dcfg0;
		regval = u32_bits_set(regval, 4, 3, (ddr_chip_cur.cs1_jedec_info->column - 8));
		pdmc->dmc_dcfg0 = regval;
	}
	/* Step7: Clear bist status  */
	regval = pdmc->dmc_bist[0];
	regval = u32_bits_set(regval, 13, 1, 1);    // clear last bist status.
	regval = u32_bits_set(regval, 0, 1, 1);     // enable bist
	pdmc->dmc_bist[0] = regval;

	//regval = u32_bits_set(regval, 13, 1, 0);
	//pdmc->dmc_bist[0] = regval;

	/* Step8: set pattern mode, trigger bist start  */
	//regval = pdmc->dmc_bist[0];
	regval = u32_bits_set(regval, 12, 2, 0);    // [13]=0, [12]=0, disable maximum address BIST excuting
	regval = u32_bits_set(regval, 0, 2, 3);     // [0]=1: enable bist; [1]=1: start bist
	pdmc->dmc_bist[0] = regval;

	/* Polling end status. */
	tout = BIST_RESERVE_SIZE * 2;
	while(tout > 0)
	{
		regval = pdmc->dmc_bist[0];
		if (regval & 0x4)
			break;
		tout--;
	}

	/* disable bist */
	//regval = pdmc->dmc_bist[0];
	regval = u32_bits_set(regval, 0, 1, 0);
	pdmc->dmc_bist[0] = regval;
	if(ddr_chip_cur.unsymmetry)
		pdmc->dmc_dcfg0 = dcfg0_bkup;

	/* Final: check bist result */
	if (tout<1)
	{
		return BIST_TOUT;
	}

	/*Bug bist ok maybe not be set when done bit has beed set. So read it again to walk around the bug*/
	regval = pdmc->dmc_bist[0];
	if (regval & 0x8)
	{
		return BIST_OK;
	}
	else
	{
		return BIST_FAIL;
	}
}


static int sipi_bist_simple_test()
{
	u64 chip_size;
	BIST_SIPI_PARA para;

	u32 bist_pattern_data[8] = {
		0xeeef7bde, 0x4210db6e, 0x92488888, 0xc7878787,
		0x33331c71, 0x00000055, 0x00000000, 0x00000000};

	para.len = BIST_RESERVE_SIZE;
	para.op_mode = BIST_OP_MODE_RW;
	sdram_chip_whole_size(&chip_size);
	/* Address space 0xFFE0_0000~0xFFFF_FFFF is reserverd for internal memory on some 32bits platform, such as SharkL2.
	    CPU can only access DDR_START_ADDR_PHY(0x8000_0000) ~ 0xFFE0_0000 for external memory.
	    */
#ifndef CONFIG_SOC_SHARKLJ1
	if (chip_size > (0x80000000 - 0x200000))
	{
		chip_size = 0x80000000 - 0x200000;
	}
#endif
	// para.len = BIST_RESERVE_SIZE will be set to register bist[1], unit in WORD(4Bytes)
	if (para.len > chip_size)
	{
		para.len = chip_size;
	}
	para.saddr = chip_size - para.len;

	memcpy(&para.pattern_data[0], &bist_pattern_data[0], sizeof(bist_pattern_data));

	if (BIST_OK != dmc_bist_test(BIST_TYPE_SIPI, &para))
	{
		return -1;
	}
	else
	{
		return 0;
	}
}


static void dqin_bit_offset_adjust(u32 init_dl)
{
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 regval;
	init_dl &= 0x1f;
	regval = (init_dl << 24) | (init_dl << 16) | (init_dl << 8) | init_dl;
	pdmc->dmc_dq_in0_dl_ds0 = regval;
	pdmc->dmc_dq_in0_dl_ds1 = regval;
	pdmc->dmc_dq_in0_dl_ds2 = regval;
	pdmc->dmc_dq_in0_dl_ds3 = regval;
	pdmc->dmc_dq_in1_dl_ds0 = regval;
	pdmc->dmc_dq_in1_dl_ds1 = regval;
	pdmc->dmc_dq_in1_dl_ds2 = regval;
	pdmc->dmc_dq_in1_dl_ds3 = regval;
}

void set_dqs_out_offset(u32 dl_dsx[4])
{
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 regval;
	regval = pdmc->dmc_dmdqs_inout_dl_ds0;
	regval = u32_bits_set(regval, 0, 5, dl_dsx[0]);
	pdmc->dmc_dmdqs_inout_dl_ds0 = regval;

	regval = pdmc->dmc_dmdqs_inout_dl_ds1;
	regval = u32_bits_set(regval, 0, 5, dl_dsx[1]);
	pdmc->dmc_dmdqs_inout_dl_ds1 = regval;

	regval = pdmc->dmc_dmdqs_inout_dl_ds2;
	regval = u32_bits_set(regval, 0, 5, dl_dsx[2]);
	pdmc->dmc_dmdqs_inout_dl_ds2 = regval;

	regval = pdmc->dmc_dmdqs_inout_dl_ds3;
	regval = u32_bits_set(regval, 0, 5, dl_dsx[3]);
	pdmc->dmc_dmdqs_inout_dl_ds3 = regval;
}

static int set_dq_iomux(u32 sel, u32 out, u32 oe, u32 ie)
{
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;

	pdmc->dmc_iomux_sel_ds0 = sel;
	pdmc->dmc_iomux_out_ds0 = out;
	pdmc->dmc_iomux_oe_ds0  = oe;
	pdmc->dmc_iomux_ie_ds0   = ie;

	pdmc->dmc_iomux_sel_ds1 = sel;
	pdmc->dmc_iomux_out_ds1 = out;
	pdmc->dmc_iomux_oe_ds1  = oe;
	pdmc->dmc_iomux_ie_ds1   = ie;

	pdmc->dmc_iomux_sel_ds2 = sel;
	pdmc->dmc_iomux_out_ds2 = out;
	pdmc->dmc_iomux_oe_ds2  = oe;
	pdmc->dmc_iomux_ie_ds2   = ie;

	pdmc->dmc_iomux_sel_ds3 = sel;
	pdmc->dmc_iomux_out_ds3 = out;
	pdmc->dmc_iomux_oe_ds3  = oe;
	pdmc->dmc_iomux_ie_ds3   = ie;
	return 0;
}

/*
 bound_ok[0][0]: phase1 start ok.
 bound_ok[0][1]: phase1 end ok.
 bound_ok[1][0]: phase2 start ok.
 bound_ok[1][1]: phase2 end ok.
 */
int set_ca_dll_with_offset(s32 bound_ok[2][2], u32 default_clkwr_dll_ac)
{
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 regval;
	s32 start_ok, end_ok, middle;
	s32 rfdll_cnt;
	u32 offset;
	u32  window;

	/* Select overlap PASS range of phase1 & phase2 as final window. */
	start_ok = (bound_ok[0][0] > bound_ok[1][0]) ? bound_ok[0][0] : bound_ok[1][0];
	end_ok = (bound_ok[0][1] > bound_ok[1][1]) ? bound_ok[1][1] : bound_ok[0][1];

#ifdef USE_CA_BITSKEW
	if (bound_ok[0][1] < bound_ok[1][1])
	{
		offset = bound_ok[1][1] - bound_ok[0][1];
		offset *= 4;
		bits_delay[4] += offset;
		bits_delay[9] += offset;
	}
	else if (bound_ok[0][1] > bound_ok[1][1])
	{
		offset = bound_ok[0][1] - bound_ok[1][1];
		offset *= 4;
		bits_delay[0] += offset;
		bits_delay[1] += offset;
		bits_delay[2] += offset;
		bits_delay[3] += offset;
		bits_delay[5] += offset;
		bits_delay[6] += offset;
		bits_delay[7] += offset;
		bits_delay[8] += offset;
	}
	regval = (bits_delay[3]<<24) | (bits_delay[2]<<16) | (bits_delay[1]<<8) | bits_delay[0];
	pdmc->dmc_addr_out0_dll_ac = regval;
	regval = (bits_delay[7]<<24) | (bits_delay[6]<<16) | (bits_delay[5]<<8) | bits_delay[4];
	pdmc->dmc_addr_out1_dll_ac = regval;
	regval = (bits_delay[9]<<8) | bits_delay[8];
	pdmc->dmc_addr_out2_dll_ac = regval;

	print_String("Offset bitskew:  \r\n");
	print_Dec(bits_delay[0]);
	print_Dec(bits_delay[1]);
	print_Dec(bits_delay[2]);
	print_Dec(bits_delay[3]);
	print_Dec(bits_delay[4]);
	print_Dec(bits_delay[5]);
	print_Dec(bits_delay[6]);
	print_Dec(bits_delay[7]);
	print_Dec(bits_delay[8]);
	print_Dec(bits_delay[9]);
	print_String("\r\n");
#endif

	window = end_ok - start_ok;
	if (window < MIN_WINDOW)
	{
		print_String("Error: too small window:  ");
		print_Dec(window);
		print_String("\r\n");
		return -1;
	}

	middle = (end_ok + start_ok) * 4 /2;
	rfdll_cnt = (pdmc->dmc_sts_dll_ac & 0x7f) * 4;
	if (get_half_mode() == 0)
	{
		rfdll_cnt  /= 2;
	}

	regval = default_clkwr_dll_ac;
	if (middle < rfdll_cnt)
	{
		offset =  rfdll_cnt - middle;
		regval = u32_bits_set(regval, 30, 2, 3);  // Minus offset compensation
	}
	else
	{
		offset =  middle - rfdll_cnt;
		regval = u32_bits_set(regval, 30, 2, 2);  // Plus offset compensation
	}

	regval = u32_bits_set(regval, 16, 7, offset>>2);
	regval = u32_bits_set(regval, 28, 2, offset);
	pdmc->dmc_clkwr_dll_ac = regval;

	print_String("Final start and end ok: ");
	print_Dec(start_ok);
	print_Dec(end_ok);
	print_String("\r\n");
	print_String("middle, rfdll, offset,   reg_0x304, reg_0x308:  ");
	print_Dec(middle);
	print_Dec(rfdll_cnt);
	print_Dec(offset);
	print_Hex(pdmc->dmc_sts_dll_ac);
	print_Hex(regval);
	print_Hex(pdmc->dmc_clkwr_dll_ac);
	print_String("\r\n");

	/* Trigger compensation. */
	pdmc->dmc_cfg_dll_ac |=  (1<<11);
	dmc_sprd_delay(1);
	pdmc->dmc_cfg_dll_ac &= (~(1<<11));

	return 0;
}


int  set_dqs_dll_with_offset(volatile u32 *p_dst_reg[4], u32 default_reg_val[4], s32 middle[4], u32 init_dll)
{
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 regval;
	u32 rfdll_cnt[4];
	s32 delay_cnt;
	u32 offset;
	volatile u32  *pcfg_dl_dsx[4];
	int i;

	rfdll_cnt[0] = (pdmc->dmc_sts_dll_ds0 & 0x7f) * 4;
	rfdll_cnt[1] = (pdmc->dmc_sts_dll_ds1 & 0x7f) * 4;
	rfdll_cnt[2] = (pdmc->dmc_sts_dll_ds2 & 0x7f) * 4;
	rfdll_cnt[3] = (pdmc->dmc_sts_dll_ds3 & 0x7f) * 4;
	pcfg_dl_dsx[0] = &pdmc->dmc_cfg_dll_ds0;
	pcfg_dl_dsx[1] = &pdmc->dmc_cfg_dll_ds1;
	pcfg_dl_dsx[2] = &pdmc->dmc_cfg_dll_ds2;
	pcfg_dl_dsx[3] = &pdmc->dmc_cfg_dll_ds3;

	print_String("REG dmc_sts_dll_dsx:   ");
	print_Hex(pdmc->dmc_sts_dll_ds0);
	print_Hex(pdmc->dmc_sts_dll_ds1);
	print_Hex(pdmc->dmc_sts_dll_ds2);
	print_Hex(pdmc->dmc_sts_dll_ds3);
	print_String("\r\n");

	if (get_half_mode() == 0)
	{
		rfdll_cnt[0] >>= 1;
		rfdll_cnt[1] >>= 1;
		rfdll_cnt[2] >>= 1;
		rfdll_cnt[3] >>= 1;
	}

	for(i = 0; i < 4; i++)
	{
		delay_cnt = middle[i] - init_dll;
		regval = default_reg_val[i];
		if (delay_cnt < rfdll_cnt[i])
		{
			offset = rfdll_cnt[i] - delay_cnt;
			regval = u32_bits_set(regval, 30, 2, 3);  // minus offset.
		}
		else
		{
			offset = delay_cnt - rfdll_cnt[i];
			regval = u32_bits_set(regval, 30, 2, 2); // plus offset.
		}
		regval = u32_bits_set(regval, 16, 7, offset>>2);
		regval = u32_bits_set(regval, 28, 2, offset);
		REG32(p_dst_reg[i]) = regval;

		print_String("middle, delay, rfdll, offset, final reg ");
		print_Dec(middle[i]);
		print_Dec(delay_cnt);
		print_Dec(rfdll_cnt[i]);
		print_Dec(offset);
		print_Hex(p_dst_reg[i]);
		print_String(": ");
		print_Hex(regval);

		/* Trigger dl compensation. */
		REG32(pcfg_dl_dsx[i]) = REG32(pcfg_dl_dsx[i]) | (1<<11);
		dmc_sprd_delay(10);
		REG32(pcfg_dl_dsx[i]) = REG32(pcfg_dl_dsx[i]) & (~(1<<11));
		reset_dmc_fifo();

		print_Hex(REG32(p_dst_reg[i]));
		print_String("\r\n");
	}

	return 0;
}


#ifdef USE_CA_TRAINING
#ifdef USE_CA_BITSKEW
int ca_training_bitskew(int phase2, u32 bits_delay[10])
{
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 regval;
	u32 pattern_rise, pattern_rise_map;
	u32 pattern_fall,  pattern_fall_map;
	u32 phy_rcv_data;
	u32 rcv_data_rise, rcv_data_fall;
	u32 compare_rise_fail, compare_fall_fail;
	u32 compare_fail, compare_pass;
	u32 phase_mask;
	u32 drf_mode_reg_a, drf_mod_reg_op;
	u32 dcfg2_val, dcfg1_val;
	int pass_flag, loop, first_flag;

	/* Define ca training pattern rise an pattern fall (10bits) */
	pattern_rise = CA_PATTERN_RISE & CA_PATTERN_MASK;
	pattern_fall  = (~pattern_rise) & CA_PATTERN_MASK;

	drf_mode_reg_a = ((pattern_fall & 0x3) << 10) | pattern_rise;
	drf_mod_reg_op = (pattern_fall >> 2) & 0xff;
	dcfg2_val = drf_mod_reg_op;
	dcfg1_val = (1<<29) | (1<<24) | drf_mode_reg_a;  //[29]=1;[28]=cs_sel(default:0);[24]=1;[15:0]=drf_mode_reg_a;

	/* phase 1 for CA bit[8:5] & bits[3:0] */
	phase_mask = phase2 ? CA_PHASE2_MAP_MASK : CA_PHASE1_MAP_MASK;
	pattern_rise_map = phase2 ? CA_PATTERN_RISE_PHASE2_MAP : CA_PATTERN_RISE_PHASE1_MAP;
	pattern_fall_map = (~pattern_rise_map) & phase_mask;

	/*Step6. CA bits deskew */
	loop = 0;
	compare_pass = phase_mask;
	while(compare_pass && (loop++ < MAX_CA_BIT_DELAY))
	{
		/* Adjust bit delay if it is passed.*/
		if (phase2)
		{
			bits_delay[4] += ((compare_pass>>0) & 1);
			bits_delay[9] += ((compare_pass>>8) & 1);
		}
		else
		{
			bits_delay[0] += ((compare_pass>>0) & 1);
			bits_delay[1] += ((compare_pass>>2) & 1);
			bits_delay[2] += ((compare_pass>>4) & 1);
			bits_delay[3] += ((compare_pass>>6) & 1);
			bits_delay[5] += ((compare_pass>>8) & 1);
			bits_delay[6] += ((compare_pass>>10) & 1);
			bits_delay[7] += ((compare_pass>>12) & 1);
			bits_delay[8] += ((compare_pass>>14) & 1);

			regval = (bits_delay[3]<<24) | (bits_delay[2]<<16) | (bits_delay[1]<<8) | bits_delay[0];
			pdmc->dmc_addr_out0_dll_ac = regval;
		}

		regval = (bits_delay[7]<<24) | (bits_delay[6]<<16) | (bits_delay[5]<<8) | bits_delay[4];
		pdmc->dmc_addr_out1_dll_ac = regval;
		regval = (bits_delay[9]<<8) | bits_delay[8];
		pdmc->dmc_addr_out2_dll_ac = regval;

		/*Step6.1) Re-send CA training pattern to start bits aligned */
		pdmc->dmc_dcfg2 = dcfg2_val;
		pdmc->dmc_dcfg1 = dcfg1_val;
		/* wait until [26:20]==0 after mr operation */
		while(((pdmc->dmc_dcfg1 >> 20) & 0x7f) != 0);

		/*Step6.2) rcv dram return data*/
		phy_rcv_data = pdmc->dmc_rcv_data;

		/*Step6.3)  remap recv data*/
		rcv_data_rise = phy_rcv_data;
		rcv_data_fall  = (phy_rcv_data>>1);

		/*Step6.4) compare pattern and received data*/
		compare_rise_fail = rcv_data_rise ^ pattern_rise_map;
		compare_fall_fail  = rcv_data_fall  ^ pattern_fall_map;
		compare_fail = (compare_rise_fail | compare_fall_fail) & phase_mask;
		compare_pass = (~compare_fail) & phase_mask;
	}

	print_String("loop:  ");
	print_Dec(loop);
	print_String("\r\n");

	/*  Adjust bit delay to last pass value.*/
	if (phase2)
	{
		bits_delay[0]--;
		bits_delay[1]--;
		bits_delay[2]--;
		bits_delay[3]--;
		bits_delay[4]--;
		bits_delay[5]--;
		bits_delay[6]--;
		bits_delay[7]--;
		bits_delay[8]--;
		bits_delay[9]--;

		print_String("Bitskew:  \r\n");
		for (regval=0; regval < 10; regval++)
		{
			u32 delay_bit = bits_delay[regval];
			print_Dec(bits_delay[regval]);
			print_String("\r\n");
		}
	}


	return 0;
}
#endif

int ca_training_main_delay(int phase2, s32 delay[2])
{
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 regval;
	u32 pattern_rise, pattern_rise_map;
	u32 pattern_fall,  pattern_fall_map;
	u32 phy_rcv_data;
	u32 rcv_data_rise, rcv_data_fall;
	u32 compare_rise_fail, compare_fall_fail;
	u32 compare_fail, compare_pass;
	u32 phase_mask;
	u32 drf_mode_reg_a, drf_mod_reg_op;
	u32 dcfg2_val, dcfg1_val;
	s32 main_delay;
	u32 init_clk_dl;
	int pass_flag;
	int startok = -1;
	int endok = -1;
	u32 rfdll_cnt;
	rfdll_cnt = pdmc->dmc_sts_dll_ac & 0x7f;
	/* Define ca training pattern rise and pattern fall (10bits) */
	pattern_rise = CA_PATTERN_RISE & CA_PATTERN_MASK;
	pattern_fall  = (~pattern_rise) & CA_PATTERN_MASK;

	drf_mode_reg_a = ((pattern_fall & 0x3) << 10) | pattern_rise;
	drf_mod_reg_op = (pattern_fall >> 2) & 0xff;
	dcfg2_val = drf_mod_reg_op;
	dcfg1_val = (1<<29) | (1<<24) | drf_mode_reg_a;  //[29]=1;[28]=cs_sel(default:0);[24]=1;[15:0]=drf_mode_reg_a;

	/* phase 1 for CA bit[8:5] & bits[3:0] */
	phase_mask = phase2 ? CA_PHASE2_MAP_MASK : CA_PHASE1_MAP_MASK;
	pattern_rise_map = phase2 ? CA_PATTERN_RISE_PHASE2_MAP : CA_PATTERN_RISE_PHASE1_MAP;
	pattern_fall_map = (~pattern_rise_map) & phase_mask;

	if (phase2)
		print_String("Phase2 Start............\r\n");
	else
		print_String("Phase1 Start............\r\n");

	print_String("pattern:  ");
	print_Hex(pattern_rise);
	print_Hex(pattern_fall);
	print_Hex(phase_mask);
	print_Hex(pattern_rise_map);
	print_Hex(pattern_fall_map);
	print_String("\r\n");

	/*Step4. send CA training pattern till (all bits passed => at least one bit failed) */
	main_delay = 0;  // Search from 0 for both phase 1 and phase 2.
	pass_flag = 0;
	init_clk_dl = 0;
	do {
		dmc_sprd_delay(2);
		/* send CA training pattern*/
		pdmc->dmc_dcfg2 = dcfg2_val;
		pdmc->dmc_dcfg1 = dcfg1_val;
		/* wait until [26:20]==0 after mr operation */
		while(((pdmc->dmc_dcfg1 >> 20) & 0x7f) != 0);

		dmc_sprd_delay(2);

		/*Step4.1) rcv dram return data*/
		phy_rcv_data = pdmc->dmc_rcv_data;

		print_Dec(main_delay);
		print_String(" phy_rcv_data:  ");
		print_Hex(phy_rcv_data&0xffff);
		print_String("\r\n");

		/*Step4.2  remap recv data*/
		rcv_data_rise = phy_rcv_data;
		rcv_data_fall  = (phy_rcv_data>>1);

		/*Step4.4) compare pattern and received data*/
		compare_rise_fail = rcv_data_rise ^ pattern_rise_map;
		compare_fall_fail  = rcv_data_fall  ^ pattern_fall_map;
		compare_fail = (compare_rise_fail | compare_fall_fail) & phase_mask;
		compare_pass = (~compare_fail)&phase_mask;

		print_String("Compare result pass:  ");
		print_Hex(compare_pass);
		print_String("    failed:  ");
		print_Hex(compare_fail);
		print_String("\r\n");
#if 0
		if (main_delay==0 && compare_fail==0 && init_clk_dl <(MAX_CA_CLK_DL*4))
		{
			/*Step1. Tune cmd out dll ac */
			init_clk_dl += 4;
			regval = pdmc->dmc_cmd_out_dll_ac;
			regval = u32_bits_set(regval, 24, 5, init_clk_dl);
			pdmc->dmc_cmd_out_dll_ac = regval;
			regval = (pdmc->dmc_cmd_out_dll_ac >> 24 & 0x1f);
			print_String("PASSED............tune dmc_cmd_out_dll_ac  to ");
			print_Dec(init_clk_dl/4);
			print_String("\r\n");
			print_String("dmc_cmd_out_dll_ac:");
			print_Dec(regval);
			print_String("\r\n");
			continue;
		}

		if (init_clk_dl > 0)
		{
			/* minus 4 to last PASS value (startok) */
			init_clk_dl -= (compare_fail) ? 4 : 0;
			compare_fail = 0;

			regval = pdmc->dmc_cmd_out_dll_ac;
			regval = u32_bits_set(regval, 24, 5, 0);
			pdmc->dmc_cmd_out_dll_ac = regval;
		}
#endif
		if (compare_fail==0 && pass_flag==0)
		{
			pass_flag = 1; // all passed flag (first)
			delay[0] = main_delay; // start ok
			startok = main_delay;  //start ok


			print_String("                                      Start ok:  ");
			print_Dec(delay[0]);
			print_String("\r\n");
		}

		if (pass_flag && compare_fail)
		{
			endok = main_delay -1;
			if ((startok != -1) && (endok != -1) &&
				((endok - startok) <= MIN_WINDOW))
			{
				startok = -1;
				endok = -1;
				pass_flag = 0;
			}
			else if ((startok != -1) && (endok != -1) &&
				((endok - startok) > MIN_WINDOW))
			{
				break;
			}
		}

		/*Step4.5) adjust delay */
		main_delay++;
		regval = pdmc->dmc_clkwr_dll_ac;
		regval = u32_bits_set(regval, 0,  7, main_delay);
		pdmc->dmc_clkwr_dll_ac = regval;
	}while(main_delay < rfdll_cnt);

	if (pass_flag == 0)
	{
		// Should not be here: no pass status is found. restore REG and return.
		print_String("Error: no pass.\r\n");
		return -1;
	}

	/*Step5. Adjust main delay to last all pass value. */
	delay[1] = main_delay - 1;  // end ok

	print_String("                                               End ok:  ");
	print_Dec(delay[1]);
	print_String("\r\n");

	return 0;
}


/* Note: only cs(0) CA training is implemented */
int dmc_lpddr3_ca_training()
{
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 regval;
	u32 default_clkwr_dll_ac;
	s32 main_delay[2];
	s32 bound_ok[2][2];
	int phase2;

	/*Step1. Initialize delay line to 0, set clk delay offset. => Save default value.  */
	default_clkwr_dll_ac = pdmc->dmc_clkwr_dll_ac;

	/*Step2. Set LPDDR3 dq iomux, open IE */
	set_dq_iomux(0xffffffff, 0, 0, 0xffffffff);

	phase2 = 0;

phase2_redo:
	/*Step3.  Start CA training phase 1(mr41)/phase2(mr48) */
	pdmc->dmc_dcfg2 = phase2 ? 0xc0 : 0xa4;

	regval = (0<<28) | (1<<24) | (phase2 ?  0x30 : 0x29);  // bit28:cs=0
	pdmc->dmc_dcfg1 = regval;
	/* wait until [26:20]==0 */
	while(((pdmc->dmc_dcfg1 >> 20) & 0x7f) != 0);

	/*Step3.3)  set cke low and disable rf_auto_cpst_en*/
	regval = pdmc->dmc_dcfg0;
	regval = u32_bits_set(regval, 14, 1, 0);
	pdmc->dmc_dcfg0 = regval;

	regval = pdmc->dmc_clkwr_dll_ac;
	regval = u32_bits_set(regval, 31, 1, 0);
	regval = u32_bits_set(regval, 0,  7, 0);
	regval = u32_bits_set(regval, 24, 2, 0);   // Initialize main delay to 0 */
	pdmc->dmc_clkwr_dll_ac = regval;

	/*Step4/5. CA training for main delay */
	if (ca_training_main_delay(phase2, main_delay) < 0)
	{
		pdmc->dmc_clkwr_dll_ac = default_clkwr_dll_ac;

		print_String("CA training failed. Restore default reg: ");
		print_Hex(default_clkwr_dll_ac);
		print_String("\r\n");

		return -1;
	}

	bound_ok[phase2][0] = main_delay[0];
	bound_ok[phase2][1] = main_delay[1];

#ifdef  USE_CA_BITSKEW
	/*Step6/7.  CA training for bits deskew */
	ca_training_bitskew(phase2, bits_delay);
#endif

	/*Step8. setting cke high, enable rf_auto_cpst_en */
	regval = pdmc->dmc_dcfg0;
	regval = u32_bits_set(regval, 14, 1, 1);
	pdmc->dmc_dcfg0 = regval;

	regval = pdmc->dmc_clkwr_dll_ac;
	regval = u32_bits_set(regval, 31, 1, 1);
	pdmc->dmc_clkwr_dll_ac = regval;

	/* set MR42 mode disable CA training*/
	pdmc->dmc_dcfg2 = 0xa8;
	pdmc->dmc_dcfg1 = (0<<29) | (0<<28) | (1<<24) | 0x2a;   // bit28: cs=0
	/* wait until [26:20]==0 */
	while(((pdmc->dmc_dcfg1 >> 20) & 0x7f) != 0);

	if (!phase2)
	{
		phase2 = 1;
		goto phase2_redo;
	}

	/*Step9. Set LPDDR3 dq iomux, close OE/IE (reverse strep2) */
	set_dq_iomux(0, 0, 0, 0);

	print_String("Phase1 startok and endok:   ");
	print_Dec(bound_ok[0][0]);
	print_Dec(bound_ok[0][1]);
	print_String("\r\n");
	print_String("Phase2 startok and endok:   ");
	print_Dec(bound_ok[1][0]);
	print_Dec(bound_ok[1][1]);
	print_String("\r\n");

	/*Step10/11. Complete compensation according to phase1/phase2 result */
	if (set_ca_dll_with_offset(bound_ok, default_clkwr_dll_ac) != 0)
	{
		pdmc->dmc_clkwr_dll_ac = default_clkwr_dll_ac;
	}
	reset_dmc_fifo();

	return 0;
}
#else
int dmc_lpddr3_ca_training() {}
#endif


#ifdef USE_RDE_TRAINING
#ifdef USE_RDE_BITSKEW
int lpddr3_rde_bitskew(int  i)
{
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	volatile u32 *p_dq_dl_in0, *p_dq_dl_in1, *p_dq_dl_cur;
	u32 regval;
	u32 delay;
	int  j, loc;

	switch(i)
	{
		case 0:
			p_dq_dl_in0 = &pdmc->dmc_dq_in0_dl_ds0;
			p_dq_dl_in1 = &pdmc->dmc_dq_in1_dl_ds0;
			break;
		case 1:
			p_dq_dl_in0 = &pdmc->dmc_dq_in0_dl_ds1;
			p_dq_dl_in1 = &pdmc->dmc_dq_in1_dl_ds1;
			break;
		case 2:
			p_dq_dl_in0 = &pdmc->dmc_dq_in0_dl_ds2;
			p_dq_dl_in1 = &pdmc->dmc_dq_in1_dl_ds2;
			break;
		case 3:
			p_dq_dl_in0 = &pdmc->dmc_dq_in0_dl_ds3;
			p_dq_dl_in1 = &pdmc->dmc_dq_in1_dl_ds3;
			break;
		default:
			return -1;
	}

	/* Adjust each bit delay to align all bits of the byte. */
	for (j = 0; j < 8; j++)
	{
		p_dq_dl_cur = (j < 4) ? p_dq_dl_in0 : p_dq_dl_in1;
		pdmc->dmc_bist[5] = ~((1<<j) << (i*8));
		loc = (j & 0x3) * 8;
		regval = REG32(p_dq_dl_cur);
		for (delay = 1; delay < MAX_DQ_BITS_DELAY; delay++)
		{
			regval = u32_bits_set(regval, loc, 5, delay);
			REG32(p_dq_dl_cur) = regval;
			reset_dmc_fifo();

			if (0 != fast_sipi_bist_test())
			{
				break;
			}
		}
		regval = u32_bits_set(regval, loc, 5, delay - 1);
		REG32(p_dq_dl_cur) = regval;

		print_String("lpddr3_rde_bitskew bits:   ");
		print_Dec(j);
		print_Dec(delay-1);
		print_String("\r\n");
	}

	pdmc->dmc_bist[5]  = bist_mask[i];

	if (0 != fast_sipi_bist_test())
	{
		print_String("Bist test for byte failed.\r\n");
	}
	else
	{
		print_String("Bist test for byte PASSED.\r\n");
	}

	return 0;
}
#endif

int dmc_lpddr3_rde_training(int  neg)
{
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 regval,res;
	u32 default_bist_mask;
	u32 default_dqsin_dll[4];
	volatile u32 *pdqs_in_dll[4];
	u32 init_dq_in_dl;
	s32 middle[4];
	s32 i, j;
	s32 lastval, startok, endok;
	int err_flag = 0;

	/* Step1. pre-setting and store default REG val. */
	default_bist_mask = pdmc->dmc_bist[5];
	pdqs_in_dll[0] = &pdmc->dmc_dqsin_pos_dll_ds0 + neg;
	pdqs_in_dll[1] = &pdmc->dmc_dqsin_pos_dll_ds1 + neg;
	pdqs_in_dll[2] = &pdmc->dmc_dqsin_pos_dll_ds2 + neg;
	pdqs_in_dll[3] = &pdmc->dmc_dqsin_pos_dll_ds3 + neg;
	default_dqsin_dll[0] = REG32(pdqs_in_dll[0]);
	default_dqsin_dll[1] = REG32(pdqs_in_dll[1]);
	default_dqsin_dll[2] = REG32(pdqs_in_dll[2]);
	default_dqsin_dll[3] = REG32(pdqs_in_dll[3]);

	init_dq_in_dl = INIT_DQ_IN_DL;
	dqin_bit_offset_adjust(init_dq_in_dl);

	/* Training for each byte independently.  */
	for(i = 0; i < 4; i++)
	{
		lastval = -1;
		startok = -1;
		endok = -1;
		pdmc->dmc_bist[5] = bist_mask[i];

		print_String("dmc_lpddr3_rde_training Byte:   ");
		print_Dec(i);
		print_String("\r\n");

		/* Step 2.  Search the pass window */
		for(j = MIN_DQ_DELAY; j < MAX_DQ_DELAY;  j++)
		{
			REG32(pdqs_in_dll[i]) = j;
			//reset_dmc_fifo();
			res = fast_sipi_bist_test();
			print_Dec(j);
			if (0 != res)
			{
				print_String(" Failed. \r\n");
				endok = j - 1;
				if ((startok != -1) && (endok != -1) && ((endok - startok) <= MIN_WINDOW))
				{
					startok = -1;
					endok = -1;
				}
				else if ((startok != -1) && (endok != -1) && ((endok - startok) > MIN_WINDOW))
				{
					lastval = 1;
					break;
				}
			}
			else
			{
				print_String(" OK. \r\n");
				if (startok == -1)
					startok = j;
				if (j == (MAX_DQ_DELAY - 1))
					lastval = 1;
			}
		}

		/* Check pass window is normal, or else stop training and restore default REG value. */
		if (startok < 0)
		{
			print_String("error:  startok -1 \r\n");
			err_flag = -1;
			REG32(pdqs_in_dll[i]) = default_dqsin_dll[i];
			break;
		}
		if (endok < 0 || endok < startok)
		{
			if (lastval == 1)
			{
				print_String(" end ok till end. \r\n");
				endok = MAX_DQ_DELAY - 1;
			}
		}

		print_String("          Start and end ok:  ");
		print_Dec(startok);
		print_Dec(endok);
		print_String("\r\n");

		if ((endok - startok) < MIN_WINDOW)
		{
			print_String("error:  window small\r\n");
			err_flag = -1;
			REG32(pdqs_in_dll[i]) = default_dqsin_dll[i];
			break;
		}

		/* Reset dqs_in_pst_dll to default value. */
		REG32(pdqs_in_dll[i]) = default_dqsin_dll[i];
		reset_dmc_fifo();

		/* Step 2.3) DQ bits skew */
		//if (!neg)  lpddr3_rde_bitskew(i);

		/* Step3. Find the window midpoint.  */
		middle[i] = (startok + endok) * 4 /2;
	}

	pdmc->dmc_bist[5] = default_bist_mask;

	/* Restore dq in dl. */
	dqin_bit_offset_adjust(0);

	/* Make compensation */
	if (!err_flag)
	{
		set_dqs_dll_with_offset(pdqs_in_dll, default_dqsin_dll, middle, init_dq_in_dl);
	}

	reset_dmc_fifo();
	return 0;
}
#else
int dmc_lpddr3_rde_training(int neg) {}
#endif


#ifdef USE_WRE_TRAINING
#ifdef USE_WRE_BITSKEW
int lpddr3_wde_bitskew(int  i)
{
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	volatile u32 *p_dq_dl_out0, *p_dq_dl_out1, *p_dq_dl_cur, *p_dm_dl;
	u32 regval;
	u32  delay;
	int  j, loc;

	switch(i)
	{
		case 0:
			p_dq_dl_out0 = &pdmc->dmc_dq_out0_dl_ds0;
			p_dq_dl_out1 = &pdmc->dmc_dq_out1_dl_ds0;
			p_dm_dl = &pdmc->dmc_dmdqs_inout_dl_ds0;
			break;
		case 1:
			p_dq_dl_out0 = &pdmc->dmc_dq_out0_dl_ds1;
			p_dq_dl_out1 = &pdmc->dmc_dq_out1_dl_ds1;
			p_dm_dl = &pdmc->dmc_dmdqs_inout_dl_ds1;
			break;
		case 2:
			p_dq_dl_out0 = &pdmc->dmc_dq_out0_dl_ds2;
			p_dq_dl_out1 = &pdmc->dmc_dq_out1_dl_ds2;
			p_dm_dl = &pdmc->dmc_dmdqs_inout_dl_ds2;
			break;
		case 3:
			p_dq_dl_out0 = &pdmc->dmc_dq_out0_dl_ds3;
			p_dq_dl_out1 = &pdmc->dmc_dq_out1_dl_ds3;
			p_dm_dl = &pdmc->dmc_dmdqs_inout_dl_ds3;
			break;
		default:
			return -1;
	}

	/* Adjust each bit delay to align all bits of the byte. */
	for (j = 0; j < 8; j++)
	{
		p_dq_dl_cur = (j < 4) ? p_dq_dl_out0 : p_dq_dl_out1;
		pdmc->dmc_bist[5] = ~((1<<j) << (i*8));
		loc = (j & 0x3) * 8;
		regval = REG32(p_dq_dl_cur);
		for (delay = 1; delay < MAX_DQ_BITS_DELAY; delay++)
		{
			regval = u32_bits_set(regval, loc, 5, delay);
			REG32(p_dq_dl_cur) = regval;
			reset_dmc_fifo();

			if (0 != fast_sipi_bist_test())
			{
				break;
			}
		}
		regval = u32_bits_set(regval, loc, 5, delay - 1);
		REG32(p_dq_dl_cur) = regval;

		print_String("wde_bitskew bits:   ");
		print_Dec(j);
		print_Dec(delay-1);
		print_String("\r\n");
	}

	pdmc->dmc_bist[5]  = bist_mask[i];

	if (0 != fast_sipi_bist_test())
	{
		print_String("Bist test for byte failed.\r\n");
	}
	else
	{
		print_String("Bist test for byte PASSED.\r\n");
	}

	return 0;

	/* Adjust dm delay to align to DQ byte. */
	/* Default delay is 0 and pass status, so we search from 1 here. */
	regval = REG32(p_dm_dl);
	for (delay = 1; delay < MAX_DM_DELAY; delay++)
	{
		regval = u32_bits_set(regval, 8, 5, delay);
		REG32(p_dm_dl) = regval;
		reset_dmc_fifo();

		if (0 != fast_sipi_bist_test())
		{
			break;
		}
	}
	regval = u32_bits_set(regval, 8, 5, delay - 1);
	REG32(p_dm_dl) = regval;

	print_String("wde_bitskew DM:   ");
	print_Dec(delay-1);
	print_String("\r\n");

	return 0;
}
#endif

/* Write data eye training and skew
  * Note: only cs(0)  is implemented
  */
int dmc_lpddr3_wde_training()
{
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 regval;
	u32 default_bist_mask;
	u32 default_clkwr_dl_ds[4];
	volatile u32 *pclkwr_dll_dsx[4];
	volatile u32 *pdmdqs_inout_dl_dsx[4];
	u32 middle[4];
	s32 i, j, k;
	s32 lastval, startok, endok;
	int res, err_flag = 0;
	u32 rfdll_cnt[4];
	/* Step1. pre-setting and store default REG val. */
	default_bist_mask = pdmc->dmc_bist[5];
	pdmdqs_inout_dl_dsx[0] = (volatile u32 *)&pdmc->dmc_dmdqs_inout_dl_ds0;
	pdmdqs_inout_dl_dsx[1] = (volatile u32 *)&pdmc->dmc_dmdqs_inout_dl_ds1;
	pdmdqs_inout_dl_dsx[2] = (volatile u32 *)&pdmc->dmc_dmdqs_inout_dl_ds2;
	pdmdqs_inout_dl_dsx[3] = (volatile u32 *)&pdmc->dmc_dmdqs_inout_dl_ds3;
	pclkwr_dll_dsx[0] = (volatile u32 *)&pdmc->dmc_clkwr_dll_ds0;
	pclkwr_dll_dsx[1] = (volatile u32 *)&pdmc->dmc_clkwr_dll_ds1;
	pclkwr_dll_dsx[2] = (volatile u32 *)&pdmc->dmc_clkwr_dll_ds2;
	pclkwr_dll_dsx[3] = (volatile u32 *)&pdmc->dmc_clkwr_dll_ds3;
	default_clkwr_dl_ds[0] = pdmc->dmc_clkwr_dll_ds0;
	default_clkwr_dl_ds[1] = pdmc->dmc_clkwr_dll_ds1;
	default_clkwr_dl_ds[2] = pdmc->dmc_clkwr_dll_ds2;
	default_clkwr_dl_ds[3] = pdmc->dmc_clkwr_dll_ds3;
	rfdll_cnt[0] = (pdmc->dmc_sts_dll_ds0 & 0x7f);
	rfdll_cnt[1] = (pdmc->dmc_sts_dll_ds1 & 0x7f);
	rfdll_cnt[2] = (pdmc->dmc_sts_dll_ds2 & 0x7f);
	rfdll_cnt[3] = (pdmc->dmc_sts_dll_ds3 & 0x7f);
	/* Training for each byte independently.  */
	for(i = 0; i < 4; i++)
	{
		lastval = -1;
		startok = -1;
		endok = -1;
		k = 1;
		pdmc->dmc_bist[5] = bist_mask[i];

		print_String("dmc_lpddr3_wde_training Byte:   ");
		print_Dec(i);
		print_String("\r\n");

		/* Step 2.  Search the pass window of  clkwr_dll_dsx*/
		for(j = MIN_DQ_DELAY; j < rfdll_cnt[i];  j++)
		{
			REG32(pclkwr_dll_dsx[i]) = j;
			//reset_dmc_fifo();

			res = fast_sipi_bist_test();

			print_Dec(j);
			if (0 != res)
			{
				print_String(" Failed. \r\n");
				endok = j - 1;
				if ((startok != -1) && (endok != -1) && ((endok - startok) <= MIN_WINDOW))
				{
					startok = -1;
					endok = -1;
				}
				else if ((startok != -1) && (endok != -1) && ((endok - startok) > MIN_WINDOW))
				{
					lastval = 1;
					break;
				}
			}
			else
			{
				print_String(" OK. \r\n");
				if (startok == -1)
				{
					startok = j;
				}
				if (j == (rfdll_cnt[i] - 1))
					lastval = 1;
			}
		}

		/* Check pass window is normal, or else stop training and restore default REG value. */
		if (startok < 0)
		{
			print_String("error:  startok -1 \r\n");
			err_flag = -1;
			REG32(pclkwr_dll_dsx[i]) = default_clkwr_dl_ds[i];
			break;
		}
		if (endok < 0 || endok < startok)
		{
			if (lastval == 1)
			{
				print_String(" end ok till end. \r\n");
				endok = rfdll_cnt[i] - 1;
			}
		}
		startok -= (k-1);

		print_String("       Start and end ok:  ");
		print_Dec(startok);
		print_Dec(endok);
		print_String("\r\n");

		/* Reset clkwr_dll_dsx to default value. */
		REG32(pclkwr_dll_dsx[i]) = default_clkwr_dl_ds[i];
		reset_dmc_fifo();

		/* Step 2.3) DQ bits and DM skew */
		//lpddr3_wde_bitskew(i);

		/* Step3. Find the window midpoint (unit in quarter delay cell).  */
		middle[i] = (startok + endok) * 4 /2;
	}

	pdmc->dmc_bist[5] = default_bist_mask;

	/* Make compensation */
	if (!err_flag)
	{
		set_dqs_dll_with_offset(pclkwr_dll_dsx, default_clkwr_dl_ds, middle, 0);
	}

	reset_dmc_fifo();
	return 0;
}
#else
int dmc_lpddr3_wde_training() {}
#endif


#ifdef USE_WR_LEVELING
int dmc_lpddr3_write_leveling()
{
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 regval;
	u32 default_cmd_out_dll_ac;
	u32 init_clk_dl;
	u32 dl_ds[4];
	u32 phy_rcv_data;
	u32 byte0, byte1, byte2, byte3;
	s32 j;
	int cs_sel = 0;

	/*Step1. setting mr2[7]=1, go into wr leveling mode*/
	pdmc->dmc_dcfg2 = 0x80;
	pdmc->dmc_dcfg1 = cs_sel ? 0x11000002 : 0x01000002;
	/* wait until [26:20]==0 */
	while(((pdmc->dmc_dcfg1 >> 20) & 0x7f) != 0);

	/*Step2. setting clk default value*/
	init_clk_dl = 0;
	regval = default_cmd_out_dll_ac = pdmc->dmc_cmd_out_dll_ac;
	regval = u32_bits_set(regval, 24, 5, init_clk_dl);
	pdmc->dmc_cmd_out_dll_ac = regval;

	print_String("Set reg_0x318:  ");
	print_Hex(pdmc->dmc_cmd_out_dll_ac);
	print_String("\r\n");

	/* setting dqs default value (search from 0)*/
	dl_ds[0] = dl_ds[1] = dl_ds[2] = dl_ds[3] = 0;
	set_dqs_out_offset(dl_ds);

	/*Step3. setting lpddr3 dq/dqs iomux, open IE/OE */
	set_dq_iomux(0x3ff, 0, 0x300, 0xff);

	phy_rcv_data = 0;
	phy_rcv_data = pdmc->dmc_rcv_data;
	print_String("Initial phy_rcv_data:  ");
	print_Hex(phy_rcv_data);
	print_String("\r\n");

	j = 0;
	do
	{
		if (j++ >= 31)
			break;

		byte0 = phy_rcv_data & 0xff;
		byte1 = (phy_rcv_data >> 8 )  & 0xff;
		byte2 = (phy_rcv_data >> 16) & 0xff;
		byte3 = (phy_rcv_data >> 24) & 0xff;

		/*Step4.  Adjust dqs out delay */
		if(byte0 == 0)
		{
			dl_ds[0]++;
			regval = pdmc->dmc_dmdqs_inout_dl_ds0;
			regval = u32_bits_set(regval, 0, 5, dl_ds[0]);
			pdmc->dmc_dmdqs_inout_dl_ds0 = regval;
		}
		if(byte1 == 0)
		{
			dl_ds[1]++;
			regval = pdmc->dmc_dmdqs_inout_dl_ds1;
			regval = u32_bits_set(regval, 0, 5, dl_ds[1]);
			pdmc->dmc_dmdqs_inout_dl_ds1= regval;
		}
		if(byte2 == 0)
		{
			dl_ds[2]++;
			regval = pdmc->dmc_dmdqs_inout_dl_ds2;
			regval = u32_bits_set(regval, 0, 5, dl_ds[2]);
			pdmc->dmc_dmdqs_inout_dl_ds2 = regval;
		}
		if(byte3 == 0)
		{
			dl_ds[3]++;
			regval = pdmc->dmc_dmdqs_inout_dl_ds3;
			regval = u32_bits_set(regval, 0, 5, dl_ds[3]);
			pdmc->dmc_dmdqs_inout_dl_ds3= regval;
		}
		dmc_sprd_delay(1);  // need delay 50ns here.

		print_String("phy_rcv_data:  ");
		print_Hex(phy_rcv_data);
		print_String("\r\n");

		print_String("dl_dsx[0],[1],[2],[3]:   ");
		print_Dec(dl_ds[0]);
		print_Dec(dl_ds[1]);
		print_Dec(dl_ds[2]);
		print_Dec(dl_ds[3]);
		print_String("\r\n");

		/*Step5. receive dram return data*/
		phy_rcv_data = pdmc->dmc_rcv_data;

		/*Step6. redo step5 & step6 if not all byte==0xff */
	}while (phy_rcv_data != 0xffffffff);

	/*Step7. Offset dqs delay based on initial_clk_delay */
	pdmc->dmc_cmd_out_dll_ac = default_cmd_out_dll_ac;

	dl_ds[0] = (dl_ds[0] > init_clk_dl) ?  (dl_ds[0] - init_clk_dl) : 0;
	dl_ds[1] = (dl_ds[1] > init_clk_dl) ?  (dl_ds[1] - init_clk_dl) : 0;
	dl_ds[2] = (dl_ds[2] > init_clk_dl) ?  (dl_ds[2] - init_clk_dl) : 0;
	dl_ds[3] = (dl_ds[3] > init_clk_dl) ?  (dl_ds[3] - init_clk_dl) : 0;

	set_dqs_out_offset(dl_ds);

	print_String("Reg_0x318, 0x428,...0x728:   ");
	print_Hex(pdmc->dmc_cmd_out_dll_ac);
	print_Hex(pdmc->dmc_dmdqs_inout_dl_ds0);
	print_Hex(pdmc->dmc_dmdqs_inout_dl_ds1);
	print_Hex(pdmc->dmc_dmdqs_inout_dl_ds2);
	print_Hex(pdmc->dmc_dmdqs_inout_dl_ds3);
	print_String("\r\n");

	/*Step8. setting lpddr3 dq/dqs iomux, close IE/OE */
	set_dq_iomux(0, 0, 0, 0);

	/*Step9. setting mr2[7]=0, exit WR leveling mode*/
	pdmc->dmc_dcfg2 = 0x0;
	pdmc->dmc_dcfg1 = cs_sel ? 0x11000002 : 0x01000002;
	/* wait until [26:20]==0 */
	while(((pdmc->dmc_dcfg1 >> 20) & 0x7f) != 0);

	reset_dmc_fifo();
	return 0;
}
#else
int dmc_lpddr3_write_leveling() {return 0;}
#endif


int ddr_scan_online_sprd_r2p0(u32 ddr_clk)
{
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;

	if (0 != sipi_bist_simple_test())
	{
		dmc_print_str("sipi_bist_simple_test  first faile do not care\r\n");
	}
	if (ddr_clk == ddr_clk_array[0])
	{
		if (0 != dmc_lpddr3_wde_training())
		{
			dmc_print_str("dmc_lpddr3_wde_training  Failed\r\n");
			return -1;
		}

		if (0 != dmc_lpddr3_rde_training(0))
		{
			dmc_print_str("dmc_lpddr3_rde_training_pos failed\r\n");
			return -1;
		}

		if (0 != dmc_lpddr3_rde_training(1))
		{
			dmc_print_str("dmc_lpddr3_rde_training_neg failed\r\n");
			return -1;
		}
		//double check dq training result
		if (0 != sipi_bist_simple_test())
		{
			dmc_print_str("sipi_bist_simple_test  lasted Failed\r\n");
			return -1;
		}
	}
	print_Hex(pdmc->dmc_bist[1]);
	print_String(" bist_len\r\n");

	return 0;
}

