#include <asm/types.h>
#include "asm/arch/clk_para_config.h"
#include "dmc_sprd_misc.h"
#include "dmc_sprd_r1p0.h"
#include "dmc_pin_cfg.h"
#include "ddr_scan_offline_sprd_r1p0.h"
#include "dmc_sprd_r1p0_bist.h"

#define MAGIC_NUMBER_LOG_START 	"\r\n0x73747172"
#define MAGIC_NUMBER_ITEM_START	"\r\n0x434f4e54"
#define MAGIC_NUMBER_LOG_END 	"\r\n0x656e6464"

#define SCAN_LEN 128

#define TPRD 0x0f
#define CLK_DMEM_SCAN_OFFSET 7

#if 0
static DMC_DRV_STRENGTH drv_supported[] = {DRV_34_OHM, DRV_40_OHM, DRV_48_OHM, DRV_60_OHM};
#else
static DMC_DRV_STRENGTH drv_supported[] = {DRV_34_OHM, DRV_40_OHM, DRV_48_OHM};
#endif


static PROJECT_INFO sprd_projects[] = {
		{PROJECT_SHARK, 	"SHARK"},
		{PROJECT_TSHARK, 	"TSHARK"},
		{PROJECT_PIKE,		"PIKE"},
		{PROJECT_PIKEL,		"PIKEL"},
		{PROJECT_WHALE,		"WHALE"},
		{PROJECT_UNKNOWN,	"UNKNOWN"},
};

static u32 bist_pattern_data[8] = {
	0x00000000, 0x11111111, 0x22222222, 0x33333333,
	0x44444444, 0x55555555, 0x66666666, 0x77777777};

static u32 sipi_pattern_data[8] = {
		0xeeef7bde, 0x4210db6e, 0x92488888, 0xc7878787,
		0x33331c71, 0x00000055, 0x00000000, 0x00000000};

static u32 lfsr_seed = 0x12345678;


static PROJECT_ID project_id_cur = PROJECT_TSHARK;

static SCAN_DDR_TYPE_ID scan_ddr_id;

static int lfsr_bist_sample(int cs)
{
	u32 cs_size;
	BIST_LFSR_PARA para;
	
	para.len = 0x100000;
	para.op_mode = BIST_OP_MODE_RW;
	para.seed_val = lfsr_seed;

	if (0 == cs)
	{
		para.saddr = DDR_START_ADDR_PHY;
	}
	else
	{
		sdram_cs_whole_size(0, &cs_size);
		para.saddr = DDR_START_ADDR_PHY + cs_size;
	}

	if (BIST_OK != dmc_bist_addr(BIST_TYPE_LFSR, &para))
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
	
	para.len = 0x100000;
	para.op_mode = BIST_OP_MODE_RW;

	if (0 == cs)
	{
		para.saddr = DDR_START_ADDR_PHY;
	}
	else
	{
		sdram_cs_whole_size(0, &cs_size);
		para.saddr = DDR_START_ADDR_PHY + cs_size;
	}

	memcpy(&para.pattern_data[0], &sipi_pattern_data[0], 32);

	if (BIST_OK != dmc_bist_addr(BIST_TYPE_SIPI, &para))
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
	para.len = 0x100000;
	para.op_mode = BIST_OP_MODE_RW;

	if (0 == cs)
	{
		para.saddr = DDR_START_ADDR_PHY;
	}
	else
	{
		sdram_cs_whole_size(0, &cs_size);
		para.saddr = DDR_START_ADDR_PHY + cs_size;
	}

	memcpy(&para.pattern_data[0], &bist_pattern_data[0], 32);

	if (BIST_OK != dmc_bist_addr(BIST_TYPE_USRDEF, &para))
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
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	char strbuf[24];
	int i;
	u32 regval = pdmc->dmc_sts_dll_ac&0x7f;

#if defined(CONFIG_CLK_PARA)
		u32 clk_rate = (mcu_clk_para.ddr_freq)/1000000;
#else
		u32 clk_rate = DDR_CLK ;
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

/*scan byte dqs in pre delay*/
void dmc_scan_byte_dqs_in_pst(void)
{
	int i, j, k, m;
	int cs_num = sdram_chip_cs_num();
	int byte_num = sdram_chip_data_width()/8;
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	char strbuf[32];
	u32 item;
	u32 ds0_org = pdmc->dmc_dqsin_pos_dll_ds0;
	u32 ds1_org = pdmc->dmc_dqsin_pos_dll_ds1;
	u32 ds2_org = pdmc->dmc_dqsin_pos_dll_ds2;
	u32 ds3_org = pdmc->dmc_dqsin_pos_dll_ds3;
	

	print_item_log_start();

	for (m=0; m<sizeof(drv_supported)/sizeof(DMC_DRV_STRENGTH); m++)
	{
		dmc_set_drv_target((int)drv_supported[m]);
		dmc_set_pin_drv();

		for(i=0; i<cs_num; i++)
		{
			for(j=0; j<byte_num; j++)
			{
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
					/*drv*/
					dmc_print_str("\t0x");
					item = SCAN_ROW1_SYMBOL | (SCAN_ITEM_DRV<<SCAN_ITEM_OFFSET) | drv_supported[m];
					dmc_print_str(itoa_simple(item, strbuf, 16));
					/*cs*/
					dmc_print_str("\t0x");
					item = SCAN_ROW2_SYMBOL | (SCAN_ITEM_CS<<SCAN_ITEM_OFFSET) | i;
					dmc_print_str(itoa_simple(item, strbuf, 16));
					/*byte*/
					dmc_print_str("\t0x");
					item = SCAN_ROW3_SYMBOL | (SCAN_ITEM_BYTE<<SCAN_ITEM_OFFSET) | j;
					dmc_print_str(itoa_simple(item, strbuf, 16));
					/*rd positive dl*/
					dmc_print_str("\t0x");
					item = SCAN_COLUMN1_SYMBOL | (SCAN_ITEM_RD_PST_DL<<SCAN_ITEM_OFFSET) | k;
					dmc_print_str(itoa_simple(item, strbuf, 16));
					/*result*/
					dmc_print_str("\t0x");
					if (0 != lfsr_bist_sample(i))
					{
						dmc_print_str("f");
						continue;
					}
					if (0 != sipi_bist_sample(i))
					{
						dmc_print_str("f");
						continue;
					}
					if (0 != usrdef_bist_sample(i))
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
		}
	}
}


/*scan byte dqs in post delay*/
void dmc_scan_byte_dqs_in_neg(void)
{
	int i, j, k, m;
	int cs_num = sdram_chip_cs_num();
	int byte_num = sdram_chip_data_width()/8;
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	char strbuf[32];
	u32 item;
	u32 ds0_org = pdmc->dmc_dqsin_neg_dll_ds0;
	u32 ds1_org = pdmc->dmc_dqsin_neg_dll_ds1;
	u32 ds2_org = pdmc->dmc_dqsin_neg_dll_ds2;
	u32 ds3_org = pdmc->dmc_dqsin_neg_dll_ds3;

	print_item_log_start();

	for (m=0; m<sizeof(drv_supported)/sizeof(DMC_DRV_STRENGTH); m++)
	{
		dmc_set_drv_target((int)drv_supported[m]);
		dmc_set_pin_drv();
		for(i=0; i<cs_num; i++)
		{
			for(j=0; j<byte_num; j++)
			{
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
					/*drv*/
					dmc_print_str("\t0x");
					item = SCAN_ROW1_SYMBOL | (SCAN_ITEM_DRV<<SCAN_ITEM_OFFSET) | drv_supported[m];
					dmc_print_str(itoa_simple(item, strbuf, 16));
					/*cs*/
					dmc_print_str("\t0x");
					item = SCAN_ROW2_SYMBOL | (SCAN_ITEM_CS<<SCAN_ITEM_OFFSET) | i;
					dmc_print_str(itoa_simple(item, strbuf, 16));
					/*byte*/
					dmc_print_str("\t0x");
					item = SCAN_ROW3_SYMBOL | (SCAN_ITEM_BYTE<<SCAN_ITEM_OFFSET) | j;
					dmc_print_str(itoa_simple(item, strbuf, 16));
					/*rd neg dl*/
					dmc_print_str("\t0x");
					item = SCAN_COLUMN1_SYMBOL | (SCAN_ITEM_RD_NEG_DL<<SCAN_ITEM_OFFSET) | k;
					dmc_print_str(itoa_simple(item, strbuf, 16));
					/*result*/
					dmc_print_str("\t0x");
					if (0 != lfsr_bist_sample(i))
					{
						dmc_print_str("f");
						continue;
					}
					if (0 != sipi_bist_sample(i))
					{
						dmc_print_str("f");
						continue;
					}
					if (0 != usrdef_bist_sample(i))
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
			}
		}
	}
}

static void dmc_set_dmdqs_out_offset(int val)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 regval;

	regval = pdmc->dmc_dmdqs_inout_dll_ds0;
	regval = u32_bits_set(regval, 0, 3, val&0x7);
	pdmc->dmc_dmdqs_inout_dll_ds0 = regval;

	regval = pdmc->dmc_dmdqs_inout_dll_ds1;
	regval = u32_bits_set(regval, 0, 3, val&0x7);
	pdmc->dmc_dmdqs_inout_dll_ds1 = regval;

	regval = pdmc->dmc_dmdqs_inout_dll_ds2;
	regval = u32_bits_set(regval, 0, 3, val&0x7);
	pdmc->dmc_dmdqs_inout_dll_ds2 = regval;

	regval = pdmc->dmc_dmdqs_inout_dll_ds3;
	regval = u32_bits_set(regval, 0, 3, val&0x7);
	pdmc->dmc_dmdqs_inout_dll_ds3 = regval;
}


/*scan byte dqs out delay*/
void dmc_scan_byte_dqs_out(void)
{
	int i, j, k, m;
	int cs_num = sdram_chip_cs_num();
	int byte_num = sdram_chip_data_width()/8;
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	char strbuf[32];
	u32 item;

	u32 ds0_org = pdmc->dmc_clkwr_dll_ds0;
	u32 ds1_org = pdmc->dmc_clkwr_dll_ds1;
	u32 ds2_org = pdmc->dmc_clkwr_dll_ds2;
	u32 ds3_org = pdmc->dmc_clkwr_dll_ds3;

	dmc_set_dmdqs_out_offset(7);

	print_item_log_start();

	for (m=0; m<sizeof(drv_supported)/sizeof(DMC_DRV_STRENGTH); m++)
	{
		dmc_set_drv_target((int)drv_supported[m]);
		dmc_set_pin_drv();
		for(i=0; i<cs_num; i++)
		{
			for(j=0; j<byte_num; j++)
			{
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
					/*drv*/
					dmc_print_str("\t0x");
					item = SCAN_ROW1_SYMBOL | (SCAN_ITEM_DRV<<SCAN_ITEM_OFFSET) | drv_supported[m];
					dmc_print_str(itoa_simple(item, strbuf, 16));
					/*cs*/
					dmc_print_str("\t0x");
					item = SCAN_ROW2_SYMBOL | (SCAN_ITEM_CS<<SCAN_ITEM_OFFSET) | i;
					dmc_print_str(itoa_simple(item, strbuf, 16));
					/*byte*/
					dmc_print_str("\t0x");
					item = SCAN_ROW3_SYMBOL | (SCAN_ITEM_BYTE<<SCAN_ITEM_OFFSET) | j;
					dmc_print_str(itoa_simple(item, strbuf, 16));
					/*wr dl*/
					dmc_print_str("\t0x");
					item = SCAN_COLUMN1_SYMBOL | (SCAN_ITEM_WR_DL<<SCAN_ITEM_OFFSET) | k;
					dmc_print_str(itoa_simple(item, strbuf, 16));
					/*result*/
					dmc_print_str("\t0x");
					if (0 != lfsr_bist_sample(i))
					{
						dmc_print_str("f");
						continue;
					}
					if (0 != sipi_bist_sample(i))
					{
						dmc_print_str("f");
						continue;
					}
					if (0 != usrdef_bist_sample(i))
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
		}
	}
}

/*scan AC delay line*/
void dmc_scan_ac(void)
{
	int i, j;
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	char strbuf[32];
	u32 item;
	u32 ca_dll_org = pdmc->dmc_clkwr_dll_ac;
	u32 regval;

	print_item_log_start();

	regval = pdmc->dmc_cmd_out0_dll_ac;
	regval = u32_bits_set(regval,  24, 3, CLK_DMEM_SCAN_OFFSET);
	regval = u32_bits_set(regval,  28, 3, CLK_DMEM_SCAN_OFFSET);
	pdmc->dmc_cmd_out0_dll_ac = regval;
	
	
	for (i=0; i<sizeof(drv_supported)/sizeof(DMC_DRV_STRENGTH); i++)
	{
		dmc_set_drv_target((int)drv_supported[i]);
		dmc_set_pin_drv();
		for (j=0; j<SCAN_LEN; j++)
		{			
			pdmc->dmc_clkwr_dll_ac = j;
			reset_dmc_fifo();
			dmc_sprd_delay(1);
			/*index*/
			dmc_print_str("\r\n0x0");
			/*drv*/
			dmc_print_str("\t0x");
			item = SCAN_ROW1_SYMBOL | (SCAN_ITEM_DRV<<SCAN_ITEM_OFFSET) | drv_supported[i];
			dmc_print_str(itoa_simple(item, strbuf, 16));
			/*cs*/
			dmc_print_str("\t0x");
			item = SCAN_ROW2_SYMBOL | (SCAN_ITEM_CS<<SCAN_ITEM_OFFSET) | 0;
			dmc_print_str(itoa_simple(item, strbuf, 16));			
			/*ac dl*/
			dmc_print_str("\t0x");
			item = SCAN_COLUMN1_SYMBOL | (SCAN_ITEM_AC_DL<<SCAN_ITEM_OFFSET) | j;
			dmc_print_str(itoa_simple(item, strbuf, 16));
			/*result*/
			dmc_print_str("\t0x");
			if (0 != lfsr_bist_sample(0))
			{
				sdram_ac_train_reset();
				dmc_print_str("f");
				continue;
			}
			if (0 != sipi_bist_sample(0))
			{
				sdram_ac_train_reset();
				dmc_print_str("f");
				continue;
			}
			if (0 != usrdef_bist_sample(0))
			{
				sdram_ac_train_reset();
				dmc_print_str("f");
				continue;
			}
			dmc_print_str("0");	
		}				
	}
	pdmc->dmc_clkwr_dll_ac = ca_dll_org;
}

static void dq_bit_offset_adjust(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	pdmc->dmc_data_in_dll_ds0 = 0x77777777;
	pdmc->dmc_data_in_dll_ds1 = 0x77777777;
	pdmc->dmc_data_in_dll_ds2 = 0x77777777;
	pdmc->dmc_data_in_dll_ds3 = 0x77777777;
}

void ddr_scan_sprd_r1p0(void)
{
	get_scan_ddr_id();
	scan_log_head();
	print_log_start();
	dmc_scan_ac();
	dmc_scan_byte_dqs_out();
	dq_bit_offset_adjust();
	dmc_scan_byte_dqs_in_pst();
	dmc_scan_byte_dqs_in_neg();
	scan_log_tail();    
}

