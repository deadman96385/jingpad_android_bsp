#include <asm/types.h>
#include <common.h>
#include "asm/arch/clk_para_config.h"
#include "lpddr3_cfg.h"
#include "dmc_sprd_r1p0.h"
#include "dmc_sprd_misc.h"

static DMC_JEDEC_TIMING_CFG dmc_jedec_timing[4] = {
	/*400MHz*/
	{
		/*dtmg0*/
		0x4,		/*tRRD*/
		0x4,		/*tCCD*/
		0x8,		/*tRCD*/
		0x9,		/*tRP*/
		/*dtmg1*/	
		0x2,		/*tRTR*/
		0x8,		/*tWTR*/
		0x8,		/*tRTW*/
		0x2,		/*tRTP*/
		/*dtmg2*/	
		0x34,		/*tRFC*/
		0x0b,		/*tWR*/
		0x38,		/*tXSR*/
		/*dtmg3*/	
		0x3,		/*tCKE*/
		0x5,		/*tXP*/
		0x2,		/*tMRD*/
		0x14,		/*tFAW*/
		0x11,		/*tRAS*/
	},
	/*384MHz*/
	{
		/*dtmg0*/
		0x4,		/*tRRD*/
		0x4,		/*tCCD*/
		0x7,		/*tRCD*/
		0x9,		/*tRP*/
		/*dtmg1*/	
		0x2,		/*tRTR*/
		0x8,		/*tWTR*/
		0x8,		/*tRTW*/
		0x2,		/*tRTP*/
		/*dtmg2*/	
		0x32,		/*tRFC*/
		0x0b,		/*tWR*/
		0x36,		/*tXSR*/
		/*dtmg3*/	
		0x3,		/*tCKE*/
		0x5,		/*tXP*/
		0x2,		/*tMRD*/
		0x14,		/*tFAW*/
		0x11,		/*tRAS*/
	},
	/*333MHz*/
	{
		/*dtmg0*/
		0x4,		/*tRRD*/
		0x4,		/*tCCD*/
		0x6,		/*tRCD*/
		0x7,		/*tRP*/
		/*dtmg1*/	
		0x2,		/*tRTR*/
		0x8,		/*tWTR*/
		0x7,		/*tRTW*/
		0x2,		/*tRTP*/
		/*dtmg2*/	
		0x2c,		/*tRFC*/
		0x0a,		/*tWR*/
		0x2f,		/*tXSR*/
		/*dtmg3*/	
		0x3,		/*tCKE*/
		0x5,		/*tXP*/
		0x2,		/*tMRD*/
		0x11,		/*tFAW*/
		0x0e,		/*tRAS*/
	},
	/*200MHz*/
	{
		/*dtmg0*/
		0x2,		/*tRRD*/
		0x4,		/*tCCD*/
		0x4,		/*tRCD*/
		0x5,		/*tRP*/
		/*dtmg1*/	
		0x2,		/*tRTR*/
		0x7,		/*tWTR*/
		0x7,		/*tRTW*/
		0x1,		/*tRTP*/
		/*dtmg2*/	
		0x1a,		/*tRFC*/
		0x08,		/*tWR*/
		0x1c,		/*tXSR*/
		/*dtmg3*/	
		0x3,		/*tCKE*/
		0x4,		/*tXP*/
		0x2,		/*tMRD*/
		0xa,		/*tFAW*/
		0x9,		/*tRAS*/
	}
};

static DMC_LOCAL_TIMING_CFG dmc_local_timing[4] = {
	/*400MHz*/
	{
		0x01c044ec,	/*dtmg4*/
		0x01e001e0,	/*dtmg5*/
		0x0007f000,	/*dtmg6*/
		0x0007f000,	/*dtmg7*/
		0x0001c000,	/*dtmg8*/
		0x00070000,	/*dtmg9*/
		0x00000004	/*dtmg10*/
	},
	/*384MHz*/
	{
		0x01c044ec,	/*dtmg4*/
		0x01e001e0,	/*dtmg5*/
		0x0007f000,	/*dtmg6*/
		0x0007f000,	/*dtmg7*/
		0x0001c000,	/*dtmg8*/
		0x00070000,	/*dtmg9*/
		0x00000004	/*dtmg10*/
	},
	/*333MHz*/
	{
		0x01c044eb,	/*dtmg4*/
		0x01e001e0,	/*dtmg5*/
		0x0007f000,	/*dtmg6*/
		0x0007f000,	/*dtmg7*/
		0x0001c000,	/*dtmg8*/
		0x00070000,	/*dtmg9*/
		0x00000004	/*dtmg10*/
	},
	/*200MHz*/
	{
		0x01c044eb,	/*dtmg4*/
		0x01e001e0,	/*dtmg5*/
		0x0007f000,	/*dtmg6*/
		0x0007f000,	/*dtmg7*/
		0x0001c000,	/*dtmg8*/
		0x00070000,	/*dtmg9*/
		0x00010004	/*dtmg10*/
	}
};

LPDDR3_MR_INFO lpddr3_mr_info = {
													/*burst length*/
#ifdef CFG_BL
								CFG_BL,
#else
								DEFAULT_LPDDR3_BL,					
#endif
	
								 0,					/*burst type*/
								 0,					/*wrap*/
								 3,					/*nwr*/
								 6,					/*read latency*/
								 3,					/*write latency*/
								 DDR_DRV_CFG		/*driver strength*/
	};

static DMC_DELAY_LINE_CFG dl_cfg = {
	/*dll ac*/
	CFG_DLL_CLKWR_AC,		/*dmc_clkwr_dll_ac*/
	/*dll ds*/
	CFG_DLL_CLKWR_DS0,		/*dmc_clkwr_dll_ds0*/
	CFG_DLL_CLKWR_DS1,		/*dmc_clkwr_dll_ds1*/
	CFG_DLL_CLKWR_DS2,		/*dmc_clkwr_dll_ds2*/
	CFG_DLL_CLKWR_DS3,		/*dmc_clkwr_dll_ds3*/
	/*dll dqsin pos*/
	CFG_DLL_DQSIN_POS_DS0,	/*dmc_dqsin_pos_dll_ds0*/
	CFG_DLL_DQSIN_POS_DS1,	/*dmc_dqsin_pos_dll_ds1*/
	CFG_DLL_DQSIN_POS_DS2,	/*dmc_dqsin_pos_dll_ds2*/
	CFG_DLL_DQSIN_POS_DS3,	/*dmc_dqsin_pos_dll_ds3*/
	/*dll dqsin neg*/	
	CFG_DLL_DQSIN_NEG_DS0,	/*dmc_dqsin_neg_dll_ds0*/
	CFG_DLL_DQSIN_NEG_DS1,	/*dmc_dqsin_neg_dll_ds1*/
	CFG_DLL_DQSIN_NEG_DS2,	/*dmc_dqsin_neg_dll_ds2*/
	CFG_DLL_DQSIN_NEG_DS3,	/*dmc_dqsin_neg_dll_ds3*/	
	/*dll dqsgate pre*/
	0x00000000,		/*dmc_dqsgate_pre_dll_ds0*/
	0x00000000,		/*dmc_dqsgate_pre_dll_ds1*/
	0x00000000,		/*dmc_dqsgate_pre_dll_ds2*/
	0x00000000,		/*dmc_dqsgate_pre_dll_ds3*/		
	/*dll dqsgate pst*/
	0x00000000,		/*dmc_dqsgate_pst_dll_ds0*/
	0x00000000,		/*dmc_dqsgate_pst_dll_ds1*/
	0x00000000,		/*dmc_dqsgate_pst_dll_ds2*/
	0x00000000,		/*dmc_dqsgate_pst_dll_ds3*/		
	/*dll date out strobe*/
	0x00000000,		/*dmc_date_out_dll_ds0*/
	0x00000000,		/*dmc_date_out_dll_ds1*/
	0x10000000,		/*dmc_date_out_dll_ds2*/
	0x00000000,		/*dmc_date_out_dll_ds3*/	
	/*dmc_dmdqs_inout_dll_ds*/
	0x00000000,		/*dmc_dmdqs_inout_dll_ds0*/
	0x00000000,		/*dmc_dmdqs_inout_dll_ds1*/
	0x00000000,		/*dmc_dmdqs_inout_dll_ds2*/
	0x00000000,		/*dmc_dmdqs_inout_dll_ds3*/
	/*dmc_data_in_dll_ds*/
	0x00000000,		/*dmc_data_in_dll_ds0*/
	0x00000000,		/*dmc_data_in_dll_ds1*/
	0x01000000,		/*dmc_data_in_dll_ds2*/
	0x00000000,		/*dmc_data_in_dll_ds3*/	

	/*dmc_cfg_dll_ac*/
	0x07028404,		/*dmc_cfg_dll_ac*/
	/*dmc_cfg_dll_ds*/
	0x07028404,		/*dmc_cfg_dll_ds0*/
	0x07028404,		/*dmc_cfg_dll_ds1*/
	0x07028404,		/*dmc_cfg_dll_ds2*/
	0x07028404,		/*dmc_cfg_dll_ds3*/
	/*dmc_addr_out_dll_ac;*/
	0x01122222,		/*dmc_addr_out0_dll_ac*/
	0x00000000,		/*dmc_addr_out1_dll_ac*/
};

/*if the DDR chip size is bigger than 4Gbit, fRFCab should be 210ns, else 130ns(default) is enough*/
static void adjust_tfcab(void)
{
	int chipsize = 0;

	sdram_chip_whole_size(&chipsize);
	if (chipsize > 0x10000000)
	{
		dmc_jedec_timing[0].tRFC = 0x54;	/*400MHz*/
		dmc_jedec_timing[1].tRFC = 0x51;	/*384MHz*/
		dmc_jedec_timing[2].tRFC = 0x46;	/*333MHz*/
		dmc_jedec_timing[3].tRFC = 0x2a;	/*200MHz*/
	}
}


void lpddr3_jedec_timing_init(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	unsigned int dtmg0, dtmg1, dtmg2, dtmg3;
	int i;

	adjust_tfcab();

	for(i=0; i<4; i++)
	{
		dtmg0 = ((dmc_jedec_timing[i].tRRD&0xf)<<24) | ((dmc_jedec_timing[i].tCCD&0xf)<<16) | ((dmc_jedec_timing[i].tRCD&0xf)<<8) | (dmc_jedec_timing[i].tRP&0xf);
		dtmg1 = ((dmc_jedec_timing[i].tRTR&0xf)<<24) | ((dmc_jedec_timing[i].tWTR&0xf)<<16) | ((dmc_jedec_timing[i].tRTW&0xf)<<8) | (dmc_jedec_timing[i].tRTP&0xf);
		dtmg2 = ((dmc_jedec_timing[i].tRFC&0xff)<<24) | ((dmc_jedec_timing[i].tWR&0x3f)<<16) | (dmc_jedec_timing[i].tXSR&0x3ff);
		dtmg3 = ((dmc_jedec_timing[i].tCKE&0xf)<<28) | ((dmc_jedec_timing[i].tXP&0xf)<<24) | ((dmc_jedec_timing[i].tMRD&0xf)<<16) | ((dmc_jedec_timing[i].tFAW&0xff)<<8) | (dmc_jedec_timing[i].tRAS&0x3f);
		if (0 == i)
		{
			pdmc->dmc_dtmg_f0[0]=dtmg0;
			pdmc->dmc_dtmg_f0[1]=dtmg1;
			pdmc->dmc_dtmg_f0[2]=dtmg2;
			pdmc->dmc_dtmg_f0[3]=dtmg3;
		}
		else if(1 == i)
		{
			pdmc->dmc_dtmg_f1[0]=dtmg0;
			pdmc->dmc_dtmg_f1[1]=dtmg1;
			pdmc->dmc_dtmg_f1[2]=dtmg2;
			pdmc->dmc_dtmg_f1[3]=dtmg3;
		}
		else if(2 == i)
		{
			pdmc->dmc_dtmg_f2[0]=dtmg0;
			pdmc->dmc_dtmg_f2[1]=dtmg1;
			pdmc->dmc_dtmg_f2[2]=dtmg2;
			pdmc->dmc_dtmg_f2[3]=dtmg3;
		}
		else if(3 == i)
		{
			pdmc->dmc_dtmg_f3[0]=dtmg0;
			pdmc->dmc_dtmg_f3[1]=dtmg1;
			pdmc->dmc_dtmg_f3[2]=dtmg2;
			pdmc->dmc_dtmg_f3[3]=dtmg3;
		}
	}	
}


void lpddr3_local_timing_init(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	/*timing array 0*/
	pdmc->dmc_dtmg_f0[4]=dmc_local_timing[0].dtmg4;
	pdmc->dmc_dtmg_f0[5]=dmc_local_timing[0].dtmg5;
	pdmc->dmc_dtmg_f0[6]=dmc_local_timing[0].dtmg6;
	pdmc->dmc_dtmg_f0[7]=dmc_local_timing[0].dtmg7;
	pdmc->dmc_dtmg_f0[8]=dmc_local_timing[0].dtmg8;
	pdmc->dmc_dtmg_f0[9]=dmc_local_timing[0].dtmg9;
	pdmc->dmc_dtmg_f0[10]=dmc_local_timing[0].dtmg10;
	/*timing array 1*/
	pdmc->dmc_dtmg_f1[4]=dmc_local_timing[1].dtmg4;
	pdmc->dmc_dtmg_f1[5]=dmc_local_timing[1].dtmg5;
	pdmc->dmc_dtmg_f1[6]=dmc_local_timing[1].dtmg6;
	pdmc->dmc_dtmg_f1[7]=dmc_local_timing[1].dtmg7;
	pdmc->dmc_dtmg_f1[8]=dmc_local_timing[1].dtmg8;
	pdmc->dmc_dtmg_f1[9]=dmc_local_timing[1].dtmg9;
	pdmc->dmc_dtmg_f1[10]=dmc_local_timing[1].dtmg10;
	/*timing array 2*/
	pdmc->dmc_dtmg_f2[4]=dmc_local_timing[2].dtmg4;
	pdmc->dmc_dtmg_f2[5]=dmc_local_timing[2].dtmg5;
	pdmc->dmc_dtmg_f2[6]=dmc_local_timing[2].dtmg6;
	pdmc->dmc_dtmg_f2[7]=dmc_local_timing[2].dtmg7;
	pdmc->dmc_dtmg_f2[8]=dmc_local_timing[2].dtmg8;
	pdmc->dmc_dtmg_f2[9]=dmc_local_timing[2].dtmg9;
	pdmc->dmc_dtmg_f2[10]=dmc_local_timing[2].dtmg10;
	/*timing array 3*/
	pdmc->dmc_dtmg_f3[4]=dmc_local_timing[3].dtmg4;
	pdmc->dmc_dtmg_f3[5]=dmc_local_timing[3].dtmg5;
	pdmc->dmc_dtmg_f3[6]=dmc_local_timing[3].dtmg6;
	pdmc->dmc_dtmg_f3[7]=dmc_local_timing[3].dtmg7;
	pdmc->dmc_dtmg_f3[8]=dmc_local_timing[3].dtmg8;
	pdmc->dmc_dtmg_f3[9]=dmc_local_timing[3].dtmg9;
	pdmc->dmc_dtmg_f3[10]=dmc_local_timing[3].dtmg10;
}

static int lpddr3_dmc_delay_line_init(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;

	pdmc->dmc_clkwr_dll_ac = dl_cfg.dmc_clkwr_dll_ac;

	pdmc->dmc_clkwr_dll_ds0 = dl_cfg.dmc_clkwr_dll_ds0;
	pdmc->dmc_dqsin_pos_dll_ds0 = dl_cfg.dmc_dqsin_pos_dll_ds0;
	pdmc->dmc_dqsin_neg_dll_ds0 = dl_cfg.dmc_dqsin_neg_dll_ds0;

	pdmc->dmc_clkwr_dll_ds1 = dl_cfg.dmc_clkwr_dll_ds1;
	pdmc->dmc_dqsin_pos_dll_ds1 = dl_cfg.dmc_dqsin_pos_dll_ds1;
	pdmc->dmc_dqsin_neg_dll_ds1 = dl_cfg.dmc_dqsin_neg_dll_ds1;

	pdmc->dmc_clkwr_dll_ds2 = dl_cfg.dmc_clkwr_dll_ds2;
	pdmc->dmc_dqsin_pos_dll_ds2 = dl_cfg.dmc_dqsin_pos_dll_ds2;
	pdmc->dmc_dqsin_neg_dll_ds2 = dl_cfg.dmc_dqsin_neg_dll_ds2;

	pdmc->dmc_clkwr_dll_ds3 = dl_cfg.dmc_clkwr_dll_ds3;
	pdmc->dmc_dqsin_pos_dll_ds3 = dl_cfg.dmc_dqsin_pos_dll_ds3;
	pdmc->dmc_dqsin_neg_dll_ds3 = dl_cfg.dmc_dqsin_neg_dll_ds3;
		

	pdmc->dmc_addr_out0_dll_ac = dl_cfg.dmc_addr_out0_dll_ac;
	pdmc->dmc_addr_out1_dll_ac = dl_cfg.dmc_addr_out1_dll_ac;
	return 0;
}



void lpddr3_timing_init(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 regval;
#if defined(CONFIG_CLK_PARA)
		u32 ddr_clk = (mcu_clk_para.ddr_freq)/1000000;
#else
		u32 ddr_clk = DDR_CLK ;
#endif
	
	lpddr3_jedec_timing_init();
	lpddr3_local_timing_init();	
	lpddr3_dmc_delay_line_init();

	regval = pdmc->dmc_lpcfg3;
	if(400 == ddr_clk)
	{
		regval = u32_bits_set(regval, 4, 2, 0);
	}
	else if (384 == ddr_clk)
	{
		regval = u32_bits_set(regval, 4, 2, 1);
	}
	
	else if (333 == ddr_clk)
	{
		regval = u32_bits_set(regval, 4, 2, 2);
	}
	else if (200 == ddr_clk)
	{
		regval = u32_bits_set(regval, 4, 2, 3);
	}
	pdmc->dmc_lpcfg3 = regval;
}

static int mr_set_zq(void)
{
	dmc_mrw(CMD_CS_0, 10, 0xff);
	dmc_sprd_delay(10);
	dmc_mrw(CMD_CS_1, 10, 0xff);
	return 0;
}

int lpddr3_final_init(void)
{
	unsigned char val = 0;
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
#if defined(CONFIG_CLK_PARA)
		u32 ddr_clk = (mcu_clk_para.ddr_freq)/1000000;
#else
		u32 ddr_clk = DDR_CLK ;
#endif

#if 0
	if ((400 == ddr_clk) || (384 == ddr_clk) || (333 == ddr_clk) )
	{
		lpddr3_mr_info.rl = 6;
		lpddr3_mr_info.wl = 3;		
	}	
	else if (200 == ddr_clk)
	{
		lpddr3_mr_info.rl = 3;
		lpddr3_mr_info.wl = 1;
	}
	else
	{
		return -1;
	}
#endif
		

	/*cke up*/
	pdmc->dmc_dcfg0 |= 1<<14;

	/*tINIT3 > 200us 100:99us*/
	dmc_sprd_delay(300);
	
	/*reset ddr*/
	dmc_mrw(CMD_CS_BOTH, 0x3f, 0);
	/*burst length:4*/
	switch(lpddr3_mr_info.bl)
	{
		case 4:
			val = 2;
			break;
		case 8:
			val = 3;
			break;
		case 16:
			val = 4;
			break;
		default:
			return -1;
	}
	/*burst type:sequential*/
	if (lpddr3_mr_info.bt == 1)
	{
		val |= 1<<3;
	}
	/*WC:wrap*/	
	if (lpddr3_mr_info.wc == 1)
	{
		val |= 1<<4;
	}
	/*nwr:3*/
	if (lpddr3_mr_info.nwr<3 || lpddr3_mr_info.nwr>7)
	{
		return -1;
	}
	val |= (lpddr3_mr_info.nwr-2)<<5;
	dmc_sprd_delay(10);
	dmc_mrw(CMD_CS_BOTH, 0x1, val);
	
	/*read latency:6*/
	/*write latency:3*/
	dmc_sprd_delay(10);
	if (0 != mr_set_rlwl(lpddr3_mr_info.rl, lpddr3_mr_info.wl))
	{
		return -1;
	}
	/*driver strength*/
	dmc_sprd_delay(10);
	if (0 != mr_set_drv(lpddr3_mr_info.ds))
	{
		return -1;
	}
	dmc_sprd_delay(10);

	/*zq calication*/
	dmc_sprd_delay(10);
	mr_set_zq();
	
	/*hardware auto refresh enable*/
	pdmc->dmc_dcfg3 |= 1<<12;
	return 0;
}

int lpddr3_ac_train_reset(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	unsigned char val = 0;

	pdmc->dmc_dcfg3 &= ~(1<<12);
	
	/*reset ddr*/
	dmc_mrw(CMD_CS_BOTH, 0x3f, 0);
	/*burst length:4*/
	switch(lpddr3_mr_info.bl)
	{
		case 4:
			val = 2;
			break;
		case 8:
			val = 3;
			break;
		case 16:
			val = 4;
			break;
		default:
			return -1;
	}
	/*burst type:sequential*/
	if (lpddr3_mr_info.bt == 1)
	{
		val |= 1<<3;
	}
	/*WC:wrap*/	
	if (lpddr3_mr_info.wc == 1)
	{
		val |= 1<<4;
	}
	/*nwr:3*/
	if (lpddr3_mr_info.nwr<3 || lpddr3_mr_info.nwr>7)
	{
		return -1;
	}
	val |= (lpddr3_mr_info.nwr-2)<<5;
	dmc_sprd_delay(10);
	dmc_mrw(CMD_CS_BOTH, 0x1, val);
	
	/*read latency:6*/
	/*write latency:3*/
	dmc_sprd_delay(10);
	if (0 != mr_set_rlwl(lpddr3_mr_info.rl, lpddr3_mr_info.wl))
	{
		return -1;
	}
	/*driver strength*/
	dmc_sprd_delay(10);
	if (0 != mr_set_drv(lpddr3_mr_info.ds))
	{
		return -1;
	}
	dmc_sprd_delay(10);

	/*zq calication*/
	dmc_sprd_delay(10);
	mr_set_zq();
	
	/*hardware auto refresh enable*/
	pdmc->dmc_dcfg3 |= 1<<12;
	return 0;
}


#ifdef DDR_AUTO_DETECT
static LPDDR3_JEDEC_ORIGINIZE org_standard[] = {	
	/*4Gb*/
	{0x20000000,	16,	8,	14,	11},
	{0x20000000,	32,	8,	14,	10},
	/*6Gb*/
	{0x30000000,	16,	8,	15,	11},
	{0x30000000,	32,	8,	15,	10},
	/*8Gb*/
	{0x40000000,	16,	8,	15,	11},
	{0x40000000,	32,	8,	15,	10},
	/*12Gb*/
	{0x60000000,	16,	8,	15,	12},
	{0x60000000,	32,	8,	15,	11},
	/*16Gb*/
	{0x80000000,	16,	8,	15,	12},
	{0x80000000,	32,	8,	15,	11},
};

int lpddr3_update_row_column(DRAM_JEDEC_INFO *info)
{
	int i;
	for (i=0; i<sizeof(org_standard)/sizeof(LPDDR3_JEDEC_ORIGINIZE); i++)
	{
		if ((info->cs_size == org_standard[i].cs_size) &&
			(info->dw == org_standard[i].dw) &&
			(info->bank == org_standard[i].bank))
		{
			info->row = org_standard[i].row;
			info->column= org_standard[i].column;
			return 0;
		}
	}
	return -1;
}

int lpddr3_update_jedec_info(u8 val, DRAM_JEDEC_INFO *info)
{
	u8 tmp;

	/*dw*/
	tmp = val>>6;
	if (0 == tmp)
	{
		info->dw = 32;
	}
	else if (1 == tmp)
	{
		info->dw = 16;
	}	
	else
	{
		return -1;
	}
	/*cs size*/
	tmp = (val>>2)&0xf;
	switch(tmp)
	{		
		case 6:
			info->cs_size = 0x20000000;
			info->bank = 8;
			break;
		case 7:
			info->cs_size = 0x40000000;
			info->bank = 8;
			break;
		case 8:
			info->cs_size = 0x80000000;
			info->bank = 8;
			break;		
		case 0xd:
			info->cs_size = 0x60000000;
			info->bank = 8;
			break;
		case 0xe:
			info->cs_size = 0x30000000;
			info->bank = 8;
			break;
		default:
			return -2;
	}

	if (0 != lpddr3_update_row_column(info))
	{
		return -3;
	}
	return 0;	
}

#endif


