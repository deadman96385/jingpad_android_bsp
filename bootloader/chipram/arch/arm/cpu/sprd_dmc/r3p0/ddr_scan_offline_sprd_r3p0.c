#include <asm/types.h>
#include <common.h>
#include <asm/arch/clk_para_config.h>
#include "dmc_sprd_r3p0.h"
#include "ddr_scan_offline_sprd_r3p0.h"
#include "dmc_sprd_r3p0_bist.h"
#ifdef CONFIG_DDR_SCAN
#define MAGIC_NUMBER_LOG_START	"\r\n0x73747172"
#define MAGIC_NUMBER_ITEM_START	"\r\n0x434f4e54"
#define MAGIC_NUMBER_LOG_END	"\r\n0x656e6464"

#define SCAN_LEN  128  // should be 128 for 7bits field
#define CLK_DMEM_SCAN_OFFSET  0x1f

#define MAX_CA_CLK_DL  ((1<<3)-1)
#define MAX_CA_MAIN_DELAY (1<<7)

typedef enum
{
	BIST_RES_INVALID = -1,
	BIST_RES_OK    = 0,
	BIST_RES_FAIL = 1
}BIST_RESULT_E;


static DDR_DRV_STRENGTH drv_supported[] = {DRV_34_OHM,DRV_40_OHM,DRV_48_OHM};


static u32 bist_mask[4] = {0xffffff00, 0xffff00ff, 0xff00ffff, 0x00ffffff};

static PROJECT_INFO sprd_projects[] = {
		{PROJECT_SHARK,		"SHARK"},
		{PROJECT_TSHARK,	"TSHARK"},
		{PROJECT_PIKE,		"PIKE"},
		{PROJECT_PIKEL,		"PIKEL"},
		{PROJECT_WHALE,		"WHALE"},
		{PROJECT_SHARKL2,	"SHARKL2"},
		{PROJECT_SHARKLJ1,	"SHARKLJ1"},
		{PROJECT_UNKNOWN,	"UNKNOWN"},
};

static u32 bist_pattern_data[8] = {
	0x00000000, 0x11111111, 0x22222222, 0x33333333,
	0x44444444, 0x55555555, 0x66666666, 0x77777777};

static u32 sipi_pattern_data[8] = {
		0xeeef7bde, 0x4210db6e, 0x92488888, 0xc7878787,
		0x33331c71, 0x00000055, 0x00000000, 0x00000000};

static u32 lfsr_seed = 0x12345678;
static PROJECT_ID project_id_cur = PROJECT_SHARKL2;
static SCAN_DDR_TYPE_ID scan_ddr_id;

static u32  bist_len = 0x80000;
extern DRAM_CHIP_INFO ddr_chip_cur;
extern u32 ca_ui_qrt_dly;

static int lfsr_bist_sample(int cs)
{
	u32 cs_size;
	BIST_LFSR_PARA para;

	para.len = bist_len;
	para.op_mode = BIST_OP_MODE_RW;
	para.seed_val = lfsr_seed;

	if (0 == cs)
	{
		para.saddr = 0;
	}
	else
	{
		sdram_cs_whole_size(0, &cs_size);
		para.saddr = 0 + cs_size;
	}

	if (BIST_OK != dmc_bist_test(BIST_TYPE_LFSR, &para))
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

static int sipi_bist_sample(int cs)
{
	u32 cs_size;
	BIST_SIPI_PARA para;

	para.len = bist_len;
	para.op_mode = BIST_OP_MODE_RW;

	if (0 == cs)
	{
		para.saddr = 0;
	}
	else
	{
		sdram_cs_whole_size(0, &cs_size);
		para.saddr = 0 + cs_size;
	}

	memcpy(&para.pattern_data[0], &sipi_pattern_data[0], sizeof(para.pattern_data));

	if (BIST_OK != dmc_bist_test(BIST_TYPE_SIPI, &para))
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

static int usrdef_bist_sample(int cs)
{
	u32 cs_size;
	BIST_SIPI_PARA para;
	para.len = bist_len;
	para.op_mode = BIST_OP_MODE_RW;

	if (0 == cs)
	{
		para.saddr = 0;
	}
	else
	{
		sdram_cs_whole_size(0, &cs_size);
		para.saddr = 0 + cs_size;
	}

	memcpy(&para.pattern_data[0], &bist_pattern_data[0], 32);

	if (BIST_OK != dmc_bist_test(BIST_TYPE_USRDEF, &para))
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

static void get_scan_ddr_id(void)
{
	DRAM_TYPE ddr_type = dmc_get_ddr_type();
	switch(ddr_type)
	{
		case DRAM_LPDDR2:
			scan_ddr_id = LPDDR2;
			break;
		case DRAM_LPDDR3:
			scan_ddr_id = LPDDR3;
			break;
		default:
			scan_ddr_id = DDR_UNKNOWN;
			break;
	}
}


//#define LOG_TYPE_OPEN

void scan_log_head(void)
{
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	char strbuf[24];
	int i;
	u32 regval = ((ca_ui_qrt_dly >> 2) << 1);
#if defined(CONFIG_CLK_PARA)
	u32 clk_rate = (mcu_clk_para.ddr_freq.value)/1000000;
#else
	u32 clk_rate = DDR_CLK;
#endif

	regval = (1000000/clk_rate)/regval;

#ifdef LOG_TYPE_OPEN
	dmc_print_str("\r\nVersion: 0.2");
	dmc_print_str("\r\n//----PROJECT = ");
	for(i=0; i<sizeof(sprd_projects)/sizeof(PROJECT_INFO); i++)
	{
		if (project_id_cur == sprd_projects[i].id)
		{
			dmc_print_str(sprd_projects[i].name);
			break;
		}
		if (PROJECT_UNKNOWN == sprd_projects[i].id)
		{
			dmc_print_str(sprd_projects[i].name);
		}
	}
	dmc_print_str("\r\n//----FREQ = ");
	dmc_print_str(itoa_simple(clk_rate, strbuf, 10));
	dmc_print_str("M");
#else
	dmc_print_str("\r\n********************");
	/*project id*/
	dmc_print_str("\r\n***0x");
	dmc_print_str(itoa_simple(project_id_cur, strbuf, 16));
	dmc_print_str("***");
	/*ddr type*/
	dmc_print_str("\r\n***0x");
	dmc_print_str(itoa_simple(scan_ddr_id, strbuf, 16));
	dmc_print_str("***");
	/*clock freqency*/
	dmc_print_str("\r\n***0x");
	dmc_print_str(itoa_simple(clk_rate, strbuf, 16));
	dmc_print_str("***");
	/*tick count*/
	dmc_print_str("\r\n***0x55aa55aa");
	dmc_print_str(itoa_simple(regval, strbuf, 16));
	dmc_print_str("***");
#endif
}

void print_item_log_start(void)
{
#ifdef LOG_TYPE_OPEN
#else
	dmc_print_str(MAGIC_NUMBER_ITEM_START);
#endif
}

void print_log_start(void)
{
#ifdef LOG_TYPE_OPEN
	dmc_print_str("\r\n//-----DDR SCAN START------");
#else
	dmc_print_str(MAGIC_NUMBER_LOG_START);
#endif
}


void scan_log_tail(void)
{
#ifdef LOG_TYPE_OPEN
	dmc_print_str("\r\n//-----DDR SCAN END!------");
#else
	dmc_print_str(MAGIC_NUMBER_LOG_END);
#endif
}

static void dqin_bit_offset_adjust(void)
{
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	pdmc->dmc_dq_in0_dl_ds0 = 0x1c1c1c1c;  // 0x1c= 7*4
	pdmc->dmc_dq_in0_dl_ds1 = 0x1c1c1c1c;
	pdmc->dmc_dq_in0_dl_ds2 = 0x1c1c1c1c;
	pdmc->dmc_dq_in0_dl_ds3 = 0x1c1c1c1c;
	pdmc->dmc_dq_in1_dl_ds0 = 0x1c1c1c1c;
	pdmc->dmc_dq_in1_dl_ds1 = 0x1c1c1c1c;
	pdmc->dmc_dq_in1_dl_ds2 = 0x1c1c1c1c;
	pdmc->dmc_dq_in1_dl_ds3 = 0x1c1c1c1c;
}

static void dqin_bit_offset_restore(void)
{
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	pdmc->dmc_dq_in0_dl_ds0 = 0;
	pdmc->dmc_dq_in0_dl_ds1 = 0;
	pdmc->dmc_dq_in0_dl_ds2 = 0;
	pdmc->dmc_dq_in0_dl_ds3 = 0;
	pdmc->dmc_dq_in1_dl_ds0 = 0;
	pdmc->dmc_dq_in1_dl_ds1 = 0;
	pdmc->dmc_dq_in1_dl_ds2 = 0;
	pdmc->dmc_dq_in1_dl_ds3 = 0;
}


/*scan byte dqs in pre delay*/
void dmc_scan_byte_dqs_in_pst(void)
{
	int i, j, k, m;
	int cs_num = sdram_chip_cs_num();
	int byte_num = sdram_chip_data_width()/8;
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	char strbuf[32];
	u32 item;
	u32 ds0_org = pdmc->dmc_dqsin_pos_dll_ds0;
	u32 ds1_org = pdmc->dmc_dqsin_pos_dll_ds1;
	u32 ds2_org = pdmc->dmc_dqsin_pos_dll_ds2;
	u32 ds3_org = pdmc->dmc_dqsin_pos_dll_ds3;

	print_item_log_start();

	dqin_bit_offset_adjust();
	for(i=0; i<cs_num; i++)
	{
		for (m=0; m<sizeof(drv_supported)/sizeof(DMC_DRV_STRENGTH); m++)
		{
			//dmc_set_drv_target((int)drv_supported[m]);
			//dmc_set_pin_drv();
			//dmc_zq_cal((int)drv_supported[m]);
			for(j=0; j<byte_num; j++)
			{
				pdmc->dmc_bist[5] = bist_mask[j];

				for(k=0; k<SCAN_LEN; k++)
				{
					reset_dmc_fifo();
					switch(j)
					{
						case 0:
							pdmc->dmc_dqsin_pos_dll_ds0 = k;
							break;
						case 1:
							pdmc->dmc_dqsin_pos_dll_ds1 = k;
							break;
						case 2:
							pdmc->dmc_dqsin_pos_dll_ds2 = k;
							break;
						case 3:
							pdmc->dmc_dqsin_pos_dll_ds3 = k;
							break;
						default:
							break;
					}
					dmc_sprd_delay(1);

					/*index*/
					dmc_print_str("\r\n0x0");

					/*byte*/
					dmc_print_str("\t0x");
					item = SCAN_ROW1_SYMBOL | (SCAN_ITEM_BYTE<<SCAN_ITEM_OFFSET) | j;
					dmc_print_str(itoa_simple(item, strbuf, 16));

					/*drv*/
					dmc_print_str("\t0x");
					item = SCAN_ROW2_SYMBOL | (SCAN_ITEM_DRV<<SCAN_ITEM_OFFSET) | drv_supported[m];
					dmc_print_str(itoa_simple(item, strbuf, 16));

					/*cs*/
					dmc_print_str("\t0x");
					item = SCAN_ROW3_SYMBOL | (SCAN_ITEM_CS<<SCAN_ITEM_OFFSET) | i;
					dmc_print_str(itoa_simple(item, strbuf, 16));

					/*rd positive dl*/
					dmc_print_str("\t0x");
					item = SCAN_COLUMN1_SYMBOL | (SCAN_ITEM_RD_PST_DL<<SCAN_ITEM_OFFSET) | k;
					dmc_print_str(itoa_simple(item, strbuf, 16));

					/*result*/
					dmc_print_str("\t0x");

					if((0 != lfsr_bist_sample(i)) || (0 != sipi_bist_sample(i)) || (0 != usrdef_bist_sample(i)))
					{
						dmc_print_str("f");
						continue;
					}
					dmc_print_str("0");
				}

				switch(j)
				{
					case 0:
						pdmc->dmc_dqsin_pos_dll_ds0 = ds0_org;
						break;
					case 1:
						pdmc->dmc_dqsin_pos_dll_ds1 = ds1_org;
						break;
					case 2:
						pdmc->dmc_dqsin_pos_dll_ds2 = ds2_org;
						break;
					case 3:
						pdmc->dmc_dqsin_pos_dll_ds3 = ds3_org;
						break;
					default:
						break;
				}

				reset_dmc_fifo();
			}
			pdmc->dmc_bist[5] = 0;
		}
	}
	dqin_bit_offset_restore();
}


/*scan byte dqs in post delay*/
void dmc_scan_byte_dqs_in_neg(void)
{
	int i, j, k, m;
	int cs_num = sdram_chip_cs_num();
	int byte_num = sdram_chip_data_width()/8;
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	char strbuf[32];
	u32 item;
	u32 ds0_org = pdmc->dmc_dqsin_neg_dll_ds0;
	u32 ds1_org = pdmc->dmc_dqsin_neg_dll_ds1;
	u32 ds2_org = pdmc->dmc_dqsin_neg_dll_ds2;
	u32 ds3_org = pdmc->dmc_dqsin_neg_dll_ds3;

	print_item_log_start();

	dqin_bit_offset_adjust();
	for(i=0; i<cs_num; i++)
	{
		for (m=0; m<sizeof(drv_supported)/sizeof(DMC_DRV_STRENGTH); m++)
		{
			//dmc_set_drv_target((int)drv_supported[m]);
			//dmc_set_pin_drv();
			//dmc_zq_cal((int)drv_supported[m]);
			for(j=0; j<byte_num; j++)
			{
				pdmc->dmc_bist[5] = bist_mask[j];

				for(k=0; k<SCAN_LEN; k++)
				{
					reset_dmc_fifo();
					switch(j)
					{
						case 0:
							pdmc->dmc_dqsin_neg_dll_ds0 = k;
							break;
						case 1:
							pdmc->dmc_dqsin_neg_dll_ds1 = k;
							break;
						case 2:
							pdmc->dmc_dqsin_neg_dll_ds2 = k;
							break;
						case 3:
							pdmc->dmc_dqsin_neg_dll_ds3 = k;
							break;
						default:
							break;
					}
					dmc_sprd_delay(1);

					/*index*/
					dmc_print_str("\r\n0x0");

					/*byte*/
					dmc_print_str("\t0x");
					item = SCAN_ROW1_SYMBOL | (SCAN_ITEM_BYTE<<SCAN_ITEM_OFFSET) | j;
					dmc_print_str(itoa_simple(item, strbuf, 16));

					/*drv*/
					dmc_print_str("\t0x");
					item = SCAN_ROW2_SYMBOL | (SCAN_ITEM_DRV<<SCAN_ITEM_OFFSET) | drv_supported[m];
					dmc_print_str(itoa_simple(item, strbuf, 16));

					/*cs*/
					dmc_print_str("\t0x");
					item = SCAN_ROW3_SYMBOL | (SCAN_ITEM_CS<<SCAN_ITEM_OFFSET) | i;
					dmc_print_str(itoa_simple(item, strbuf, 16));

					/*rd positive dl*/
					dmc_print_str("\t0x");
					item = SCAN_COLUMN1_SYMBOL | (SCAN_ITEM_RD_NEG_DL<<SCAN_ITEM_OFFSET) | k;
					dmc_print_str(itoa_simple(item, strbuf, 16));

					/*result*/
					dmc_print_str("\t0x");

					if((0 != lfsr_bist_sample(i)) || (0 != sipi_bist_sample(i)) || (0 != usrdef_bist_sample(i)))
					{
						dmc_print_str("f");
						continue;
					}
					dmc_print_str("0");
				}
				switch(j)
				{
					case 0:
						pdmc->dmc_dqsin_neg_dll_ds0 = ds0_org;
						break;
					case 1:
						pdmc->dmc_dqsin_neg_dll_ds1 = ds1_org;
						break;
					case 2:
						pdmc->dmc_dqsin_neg_dll_ds2 = ds2_org;
						break;
					case 3:
						pdmc->dmc_dqsin_neg_dll_ds3 = ds3_org;
						break;
					default:
						break;
				}
				reset_dmc_fifo();
			}
			pdmc->dmc_bist[5] = 0;
		}
	}
	dqin_bit_offset_restore();
}


static void dmc_set_dmdqs_out_offset(int val)
{
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;

	pdmc->dmc_dmdqs_inout_dl_ds0 = u32_bits_set(pdmc->dmc_dmdqs_inout_dl_ds0, 0, 5, val&0x1f);
	pdmc->dmc_dmdqs_inout_dl_ds1 = u32_bits_set(pdmc->dmc_dmdqs_inout_dl_ds1, 0, 5, val&0x1f);
	pdmc->dmc_dmdqs_inout_dl_ds2 = u32_bits_set(pdmc->dmc_dmdqs_inout_dl_ds2, 0, 5, val&0x1f);
	pdmc->dmc_dmdqs_inout_dl_ds3 = u32_bits_set(pdmc->dmc_dmdqs_inout_dl_ds3, 0, 5, val&0x1f);
}


/*scan byte dqs out delay*/
void dmc_scan_byte_dqs_out(void)
{
	int i, j, k, m;
	int cs_num = sdram_chip_cs_num();
	int byte_num = sdram_chip_data_width()/8;
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	char strbuf[32];
	u32 item;

	u32 ds0_org = pdmc->dmc_clkwr_dll_ds0;
	u32 ds1_org = pdmc->dmc_clkwr_dll_ds1;
	u32 ds2_org = pdmc->dmc_clkwr_dll_ds2;
	u32 ds3_org = pdmc->dmc_clkwr_dll_ds3;

	print_item_log_start();

	for(i=0; i<cs_num; i++)
	{
		for (m=0; m<sizeof(drv_supported)/sizeof(DMC_DRV_STRENGTH); m++)
		{
			//dmc_set_drv_target((int)drv_supported[m]);
			//dmc_set_pin_drv();
			//dmc_zq_cal((int)drv_supported[m]);
			for(j=0; j<byte_num; j++)
			{
				pdmc->dmc_bist[5] = bist_mask[j];

				for(k=0; k<SCAN_LEN; k++)
				{
					reset_dmc_fifo();
					switch(j)
					{
						case 0:
							pdmc->dmc_clkwr_dll_ds0 = k;
							break;
						case 1:
							pdmc->dmc_clkwr_dll_ds1 = k;
							break;
						case 2:
							pdmc->dmc_clkwr_dll_ds2 = k;
							break;
						case 3:
							pdmc->dmc_clkwr_dll_ds3 = k;
							break;
						default:
							break;
					}
					dmc_sprd_delay(1);

					/*index*/
					dmc_print_str("\r\n0x0");

					/*byte*/
					dmc_print_str("\t0x");
					item = SCAN_ROW1_SYMBOL | (SCAN_ITEM_BYTE<<SCAN_ITEM_OFFSET) | j;
					dmc_print_str(itoa_simple(item, strbuf, 16));

					/*drv*/
					dmc_print_str("\t0x");
					item = SCAN_ROW2_SYMBOL | (SCAN_ITEM_DRV<<SCAN_ITEM_OFFSET) | drv_supported[m];
					dmc_print_str(itoa_simple(item, strbuf, 16));

					/*cs*/
					dmc_print_str("\t0x");
					item = SCAN_ROW3_SYMBOL | (SCAN_ITEM_CS<<SCAN_ITEM_OFFSET) | i;
					dmc_print_str(itoa_simple(item, strbuf, 16));

					/*wr dl*/
					dmc_print_str("\t0x");
					item = SCAN_COLUMN1_SYMBOL | (SCAN_ITEM_WR_DL<<SCAN_ITEM_OFFSET) | k;
					dmc_print_str(itoa_simple(item, strbuf, 16));

					/*result*/
					dmc_print_str("\t0x");

					if((0 != lfsr_bist_sample(i)) || (0 != sipi_bist_sample(i)) || (0 != usrdef_bist_sample(i)))
					{
						dmc_print_str("f");
						continue;
					}

					dmc_print_str("0");
				}

				switch(j)
				{
					case 0:
						pdmc->dmc_clkwr_dll_ds0 = ds0_org;
						break;
					case 1:
						pdmc->dmc_clkwr_dll_ds1 = ds1_org;
						break;
					case 2:
						pdmc->dmc_clkwr_dll_ds2 = ds2_org;
						break;
					case 3:
						pdmc->dmc_clkwr_dll_ds3 = ds3_org;
						break;
					default:
						break;
				}
				reset_dmc_fifo();
			}
			pdmc->dmc_bist[5] = 0;
		}
	}
}


/*scan AC delay line*/
void dmc_scan_ac(void)
{
	int i, j;
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	char strbuf[32];
	u32 item;
	u32 ca_dll_org = pdmc->dmc_clkwr_dll_ac;
	u32 regval;

	print_item_log_start();

	for (i=0; i<sizeof(drv_supported)/sizeof(DMC_DRV_STRENGTH); i++)
	{
		//dmc_set_drv_target((int)drv_supported[i]);
		//dmc_set_pin_drv();
		//dmc_zq_cal((int)drv_supported[i]);

		for (j=0; j<SCAN_LEN; j++)
		{
			pdmc->dmc_clkwr_dll_ac = j;
			reset_dmc_fifo();
			dmc_sprd_delay(1);

			/*index*/
			dmc_print_str("\r\n0x0");
			/*cs*/
			dmc_print_str("\t0x");
			item = SCAN_ROW1_SYMBOL | (SCAN_ITEM_CS<<SCAN_ITEM_OFFSET) | 0;
			dmc_print_str(itoa_simple(item, strbuf, 16));
			/*drv*/
			dmc_print_str("\t0x");
			item = SCAN_ROW2_SYMBOL | (SCAN_ITEM_DRV<<SCAN_ITEM_OFFSET) | drv_supported[i];
			dmc_print_str(itoa_simple(item, strbuf, 16));
			/*ac dl*/
			dmc_print_str("\t0x");
			item = SCAN_COLUMN1_SYMBOL | (SCAN_ITEM_AC_DL<<SCAN_ITEM_OFFSET) | j;
			dmc_print_str(itoa_simple(item, strbuf, 16));
			/*result*/
			dmc_print_str("\t0x");

			if((0 != lfsr_bist_sample(0)) || (0 != sipi_bist_sample(0)) || (0 != usrdef_bist_sample(0)))
			{
				reset_dmc_fifo();
				sdram_ac_train_reset();
				reset_dmc_fifo();
				dmc_print_str("f");
				continue;
			}

			dmc_print_str("0");

		}
	}
}
int  ddr_scan_offline_sprd_r3p0(void)
{
	get_scan_ddr_id();
	scan_log_head();
	print_log_start();
	dmc_scan_byte_dqs_out();
	dmc_scan_byte_dqs_in_pst();
	dmc_scan_byte_dqs_in_neg();
	if(ddr_chip_cur.chip_type != DRAM_LPDDR2)
	{
		dmc_scan_ac();
	}
	scan_log_tail();
	return 0;
}
#endif
