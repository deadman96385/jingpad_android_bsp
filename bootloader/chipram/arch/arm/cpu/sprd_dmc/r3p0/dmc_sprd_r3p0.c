#include <asm/types.h>
#include <common.h>
#include <sci_types.h>
#include <asm/arch/clk_para_config.h>
/* delete  chip_drv_common_io_h */
#include <adi.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_chipram_env.h>
#include "dmc_sprd_r3p0.h"
#include "dmc_sprd_r3p0_bist.h"

extern LPDDR_MR_INFO lpddr2_mr_info;
extern LPDDR_MR_INFO lpddr3_mr_info;


static DRAM_JEDEC_INFO jedec_info_cs0 = {0,			/*cs index*/
					CFG_CS0_BANK_NUM,	/*bank number*/
					CFG_CS0_ROW_NUM,	/*row number*/
					CFG_CS0_COLUMN_NUM,	/*column number*/
					CFG_CS0_DQ_DW,		/*data width*/
					CFG_CS0_AP_PIN_POS,	/*auto precharge pin position*/
					CFG_CS0_SIZE		/*cs0 size*/
};

static DRAM_JEDEC_INFO jedec_info_cs1 = {1,			/*cs index*/
					 CFG_CS1_BANK_NUM,	/*bank number*/
					 CFG_CS1_ROW_NUM,	/*row number*/
					 CFG_CS1_COLUMN_NUM,	/*column number*/
					 CFG_CS1_DQ_DW,		/*data width*/
					 CFG_CS1_AP_PIN_POS,	/*auto precharge pin position*/
					 CFG_CS1_SIZE		/*cs1 size*/
};



DRAM_CHIP_INFO ddr_chip_cur = {CFG_DRAM_TYPE,		/*dram type*/
				DRAM_SAMSUNG,		/*vendor*/
				CFG_CS_NUM,		/*cs number*/
				INVALID_T,		/*pcb type*/
				&jedec_info_cs0,	/*phycial character*/
				&jedec_info_cs1,	/*phycial character*/
				CFG_IS_UNSYMMETRY_DRAM	/*if is unsymmetry dram*/
};

DDR_UNSYMMETRY_MODE unsymmetry_mode_cur = CFG_UNSYMMETRY_DRAM_MODE;	/*unsymmetry type*/

/* Define four clk freq points here, and you can modify it before init pre-setting.
 * Make sure that the initial clk freq is included in this array.
 */
u32 ddr_clk_array[] = {
	DDR_CLK0,
	DDR_CLK1,
	DDR_CLK2,
	DDR_CLK3
};

static SDRAM_CS_PIN_TABLE pin_table[] = {
	{26,0x8000000},  //bit26 128M
	{27,0x10000000}, //bit27 256M
	{28,0x20000000}, //bit28 512M
	{29,0x30000000}, //bit29 768M
	{29,0x40000000}, //bit29 1024M
	{30,0x60000000}, //bit30 1536M
	{30,0x80000000}, //bit30 2048M
	{31,0xc0000000}, //bit31 3072M
	{31,0x100000000} //bit31 4096M
};

#ifdef CONFIG_SOC_PIKE2
static PORT_PARA port_para[18] = {
	/*port0*/
	{
		0xf,
		0x0,
		0x0,
	},
	{
		0xf,
		0x0,
		0x0,
	},
	/*port1*/
	{
		0x0,
		0x0,
		0x0,
	},
	{
		0x0,
		0x0,
		0x0,
	},
	/*port2*/
	{
		0xe,
		0x0,
		0x0,
	},
	{
		0xe,
		0x0,
		0x0,
	},
	/*port3*/
	{
		0xe,
		0x72,
		0x40,
	},
	{
		0xd,
		0x0,
		0x0,
	},
	/*port4*/
	{
		0xf,
		0x0,
		0x0,
	},
	{
		0xf,
		0x0,
		0x0,
	},
	/*port5*/
	{
		0x0,
		0x0,
		0x0,
	},
	{
		0x0,
		0x0,
		0x0,
	},
	/*port6*/
	{
		0x0,
		0x0,
		0x0,
	},
	{
		0x0,
		0x0,
		0x0,
	},
	/*port7*/
	{
		0x0,
		0x0,
		0x0,
	},
	{
		0x0,
		0x0,
		0x0,
	},
};
#else
static PORT_PARA port_para[18] = {
	/*port0*/
	{
		0xe,
		0x0,
		0x0,
	},
	{
		0xe,
		0x0,
		0x0,
	},
	/*port1*/
	{
		0x7,
		0x80,
		0x80,
	},
	{
		0x7,
		0x0,
		0x0,
	},
	/*port2*/
	{
		0xa,
		0x0,
		0x41,
	},
	{
		0xe,
		0x0,
		0x0,
	},
	/*port3*/
	{
		0x6,
		0x80,
		0x80,
	},
	{
		0x6,
		0x0,
		0x0,
	},
	/*port4*/
	{
		0x7,
		0x0,
		0x0,
	},
	{
		0x7,
		0x0,
		0x0,
	},
	/*port5*/
	{
		0xd,
		0x0,
		0x0,
	},
	{
		0xd,
		0x0,
		0x0,
	},
	/*port6*/
	{
		0xc,
		0x0,
		0x0,
	},
	{
		0x9,
		0x0,
		0x0,
	},
	/*port7*/
	{
		0xA,
		0xFF,
		0xFF,
	},
	{
		0xA,
		0x0,
		0x0,
	},
};
#endif

#ifdef DDR_AUTO_DETECT
LPDDR_JEDEC_ORIGINIZE org_standard[14] = {
	 /*1Gb*/
	{0x8000000,	16,	8,	13,	10},
	{0x8000000,	32,	8,	13,	9},
	/*2Gb*/
	{0x10000000,	16,	8,	14,	10},
	{0x10000000,	32,	8,	14,	9},
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
#endif

void reset_dmc_fifo(void) {
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	pdmc->dmc_dcfg0 |= 1<<16;
	pdmc->dmc_dcfg0 &= ~(1<<16);
}

DRAM_TYPE dmc_get_ddr_type(void)
{
	return ddr_chip_cur.chip_type;
}

int sdram_chip_data_width(void)
{
	return jedec_info_cs0.dw;
}

int sdram_chip_cs_num(void)
{
	return ddr_chip_cur.cs_num;
}

int sdram_chip_whole_size(u64 *size)
{

	if (ddr_chip_cur.cs_num == 1)
	{
		*size = jedec_info_cs0.cs_size;
	}
	else if (ddr_chip_cur.cs_num == 2)
	{
		*size = (u64)(jedec_info_cs0.cs_size) + (u64)(jedec_info_cs1.cs_size);
	}
	else
	{
		return -1;
	}
	return 0;
}


int sdram_cs_whole_size(int cs, u32 *size)
{
	if (0 == cs)
	{
		*size = jedec_info_cs0.cs_size;
	}
	else if (1 == cs)
	{
		*size = jedec_info_cs1.cs_size;
	}
	else
	{
		return -1;
	}
	return 0;
}


#ifdef ADDR_CS_ROW_BANK_COLUMN
unsigned int sdram_bank_whole_size(void)
{
	int val;
	val = ddr_chip_cur.cs0_jedec_info->column;
	return (1<<val)*(ddr_chip_cur.cs0_jedec_info->dw/8);
}

unsigned int sdram_row_whole_size(void)
{
	int val;
	val = ddr_chip_cur.cs0_jedec_info->column;
	return (1<<val)*(ddr_chip_cur.cs0_jedec_info->bank)*(ddr_chip_cur.cs0_jedec_info->dw/8);
}
unsigned int sdram_cs1_row_size(void)

{
	int val;
	val = ddr_chip_cur.cs1_jedec_info->column;
	return (1<<val)*(ddr_chip_cur.cs1_jedec_info->bank)*(ddr_chip_cur.cs1_jedec_info->dw/8);
}
#else
unsigned int sdram_bank_whole_size(void)
{
	int val;
	val = ddr_chip_cur.cs0_jedec_info->column+ddr_chip_cur.cs0_jedec_info->row;
	return (1<<val)*(ddr_chip_cur.cs0_jedec_info->dw/8);
}

unsigned int sdram_row_whole_size(void)
{
	int val;
	val = ddr_chip_cur.cs0_jedec_info->column;
	return (1<<val)*(ddr_chip_cur.cs0_jedec_info->dw/8);
}
#endif

unsigned int sdram_column_whole_size(void)
{
	return (ddr_chip_cur.cs0_jedec_info->dw/8);
}

int trans_addr_to_jedec_addr(u32 addr, DRAM_JEDEC_ADDR *jedec_addr)
{
	u32 offset = addr;
	u64 chip_size;
	u32 cs_size;
	u32 bank_size = sdram_bank_whole_size();
	u32 row_size = sdram_row_whole_size();
	u32 column_size = sdram_column_whole_size();

	if (offset > jedec_info_cs0.cs_size)
	{
		row_size = sdram_cs1_row_size();
	}

	if (0 != sdram_chip_whole_size(&chip_size))
	{
		return -1;
	}

	if (0 != sdram_cs_whole_size(0, &cs_size))
	{
		return -2;
	}

	if (0 != offset%(jedec_info_cs0.dw/8))
	{
		return -3;
	}

	if (offset > chip_size)
	{
		return -4;
	}

	jedec_addr->cs = offset/cs_size;
	offset %= cs_size;

#ifdef ADDR_CS_ROW_BANK_COLUMN
	jedec_addr->row = offset/row_size;
	offset %= row_size;
	jedec_addr->bank = offset/bank_size;
	offset %= bank_size;
#else
	jedec_addr->bank = offset/bank_size;
	offset %= bank_size;
	jedec_addr->row = offset/row_size;
	offset %= row_size;
#endif
	jedec_addr->column = offset/column_size;
	return 0;
}

int sdram_ac_train_reset(void)
{
	if (ddr_chip_cur.chip_type == DRAM_LPDDR2)
	{
		return 0;//lpddr2_ac_train_reset();
	}
	else
	{
		return lpddr3_ac_train_reset();
	}
	return 0;
}

static u32 dpll_clk_get(void)
{
	u32 clk = 0;
	u32 nint, kint, refin, pnt = 0 ;
	u32 reg1, reg2, div_s, sdm_en, n;

	reg1 = REG32(DDR_DPLL_CFG1);
	reg2 = REG32(DDR_DPLL_CFG2);
	nint = (reg2 >> 23)&0x7f;
	kint = reg2 & 0x7FFFFF;
	div_s = (reg1 >> 20) & 0x1;
	sdm_en = (reg1 >> 18) & 0x1;
	n = reg1 & 0x7ff;

	switch((reg1>>22)&0x3)
	{
		case 0:
			refin = 2;
			break;
		case 1:
			refin = 4;
			break;
		case 2:
			refin = 13;
			break;
		case 3:
			refin = 26;
			break;
	}

	if ((div_s != 0) && (sdm_en != 0)) {
		if (((kint * refin ) & 0x7FFFFF) >= 0x3fffff) {
			pnt = 1;
		}
		else {
			pnt = 0;
		}
		kint = ((kint * refin) >> 23) + pnt;
		clk = nint * refin + kint;
	}
	else if ((div_s != 0) && (sdm_en == 0)) {
		clk = nint * refin;
	}
	else/* if (div_s == 0) */ {
		clk = refin * n;
	}

	return clk;
}
#ifdef CONFIG_SOC_PIKE2
static void dpll_clk_set(u32 clk)
{
	volatile u32 reg1 = 0, reg2=0;
	u32 refin = 0;

	if(dpll_clk_get() == clk) {
		return;
	}

	reg1 = REG32(DDR_DPLL_CFG1);
	reg2 = REG32(DDR_DPLL_CFG2);

	/* get refin value */
	refin = 26;
	reg1 = u32_bits_set(reg1, 22, 8, 3);

	if((1345 < clk)&&(clk <= 1600))
		reg1 = u32_bits_set(reg1, 11, 2, 0x3);
	else if(1131 < clk)
		reg1 = u32_bits_set(reg1, 11, 2, 0x2);
	else if(951 < clk)
		reg1 = u32_bits_set(reg1, 11, 2, 0x1);
	else
		reg1 = u32_bits_set(reg1, 11, 2, 0x0);

	if (0 == clk%refin)
	{
		reg1 = u32_bits_set(reg1, 0, 11, clk/refin);
		/*set div_s=0*/
		reg1 = u32_bits_set(reg1, 20, 1, 0);
		REG32(DDR_DPLL_CFG1) = reg1;
		REG32(DDR_DPLL_CFG2) = reg2;
	}
	else
	{
		/*set div_s=1*/
		reg1 = u32_bits_set(reg1, 20, 1, 1);
		/*set sdm_en=1*/
		reg1 = u32_bits_set(reg1, 18, 1, 1);
		/*set NINT*/
		reg2 = u32_bits_set(reg2, 23, 7, clk/refin);
		/*set KINT*/
		reg2 = u32_bits_set(reg2, 0, 23, (clk%refin)*8388608/refin);
		REG32(DDR_DPLL_CFG1) = reg1;
		REG32(DDR_DPLL_CFG2) = reg2;
	}

	dmc_sprd_delay(200);
}
#else
static void dpll_clk_set(u32 clk)
{
	volatile u32 reg1 = 0, reg2=0;
	u32 refin = 0;

	if(dpll_clk_get() == clk) {
		return;
	}

	reg1 = REG32(DDR_DPLL_CFG1);
	reg2 = REG32(DDR_DPLL_CFG2);

	/* get refin value */
	refin = 26;
	//reg1 = u32_bits_set(reg1, 22, 8, 3);
	if((1240 < clk) && (clk <= 1600))
		reg1 = u32_bits_set(reg1, 15, 2, 2);
	else if(936 < clk)
		reg1 = u32_bits_set(reg1, 15, 2, 1);
	else
		reg1 = u32_bits_set(reg1, 15, 2, 0);
	if (0 == clk%refin)
	{
		reg1 = u32_bits_set(reg1, 17, 11, clk/refin);
		/*set div_s=0*/
		reg1 = u32_bits_set(reg1, 9, 1, 0);
		REG32(DDR_DPLL_CFG1) = reg1;
		REG32(DDR_DPLL_CFG2) = reg2;
	}
	else
	{
		/*set div_s=1*/
		reg1 = u32_bits_set(reg1, 9, 1, 1);
		/*set sdm_en=1*/
		reg1 = u32_bits_set(reg1, 11, 1, 1);
		/*set NINT*/
		reg2 = u32_bits_set(reg2, 23, 7, clk/refin);
		/*set KINT*/
		reg2 = u32_bits_set(reg2, 0, 23, (clk%refin)*8388608/refin);
		REG32(DDR_DPLL_CFG1) = reg1;
		REG32(DDR_DPLL_CFG2) = reg2;
	}

	dmc_sprd_delay(200);
}
#endif

#ifdef CONFIG_SOC_PIKE2
void sdram_clk_src_set(u32 clk)
{
	u32 regval;

	regval = REG32(REG_SP_AHB_CM4_CLK_EMC_CTRL);
	switch(clk)
	{
		case 166:
			dpll_clk_set(996);
			/*src index=5 dpll*/
			regval = u32_bits_set(regval,2,3,5);
			/*div = 2*/
			regval = u32_bits_set(regval,0,2,2);
			break;

		case 192:
			/*src index=1 twpll=384*/
			regval = u32_bits_set(regval,2,3,1);
			/*div = 1*/
			regval = u32_bits_set(regval,0,2,0);
			break;

		case 256:
			/*src index=2 twpll=512*/
			regval = u32_bits_set(regval,2,3,2);
			/*div = 1*/
			regval = u32_bits_set(regval,0,2,0);
			break;

		case 384:
			/*src index=3 twpll=768*/
			regval = u32_bits_set(regval,2,3,3);
			/*div = 0*/
			regval = u32_bits_set(regval,0,2,0);
			break;

		case 400:
			dpll_clk_set(800);
			/*src index=5 dpll*/
			regval = u32_bits_set(regval,2,3,5);
			/*div = 1*/
			regval = u32_bits_set(regval,0,2,0);
			break;

		case 466:
			dpll_clk_set(932);
			/*src index=5 dpll*/
			regval = u32_bits_set(regval,2,3,5);
			/*div = 1*/
			regval = u32_bits_set(regval,0,2,0);
			break;

		case 533:
			dpll_clk_set(1062);
			/*src index=5 dpll*/
			regval = u32_bits_set(regval,2,3,5);
			/*div = 1*/
			regval = u32_bits_set(regval,0,2,0);
			break;

		default:
			dpll_clk_set(1067);
			/*src index=5 dpll*/
			regval = u32_bits_set(regval,2,3,5);
			/*div = 1*/
			regval = u32_bits_set(regval,0,2,0);
			break;
	}
	REG32(REG_SP_AHB_CM4_CLK_EMC_CTRL) = regval;

}
#else
void sdram_clk_src_set(u32 clk)
{
	u32 regval;

	//regval = REG32(CM4_CLK_DMC_CTL);
	//regval = u32_bits_set(regval,0,1,1); //cm4 dmc_dfs_en = 1

	//add aon
	regval = REG32(REG_AON_APB_HARD_DFS_CTRL); //0x402e00ac
	switch(clk)
	{
		case 166:
			dpll_clk_set(1334);
			/*src index=4 dpll=1334*/
			regval = u32_bits_set(regval,6,3,4);
			regval = u32_bits_set(regval,2,4,3);
			break;

		case 256:
			/*src index=1 twpll=512*/
#ifdef PXP_VERSION
			/*pxp twpll512 gate enable*/
			regval = REG32(0x402d0048);
			regval =  u32_bits_set(regval,2,1,0);
			REG32(0x402d0048) = regval;
#endif
			regval = u32_bits_set(regval,6,3,1);
			/*div = 1*/
			regval = u32_bits_set(regval,2,4,0);
			break;

		case 384:
			/*src index=3 twpll=768*/
#ifdef PXP_VERSION
			/*pxp twpll768 gate enable*/
			regval = REG32(0x402d0048);
			regval =  u32_bits_set(regval,3,1,0);
			REG32(0x402d0048) = regval;
#endif
			regval = u32_bits_set(regval,6,3,3);
			/*div = 1*/
			regval = u32_bits_set(regval,2,4,0);
			break;

		case 400:
			dpll_clk_set(800);
			/*src index=4 dpll*/
			regval = u32_bits_set(regval,6,3,4);
			/*div = 1*/
			regval = u32_bits_set(regval,2,4,0);
			break;

		case 466:
			dpll_clk_set(932);
			/*src index=4 dpll*/
			regval = u32_bits_set(regval,6,3,4);
			/*div = 1*/
			regval = u32_bits_set(regval,2,4,0);
			break;

		case 533:
			dpll_clk_set(1067);
			/*src index=4 dpll*/
			regval = u32_bits_set(regval,6,3,4);
			/*div = 1*/
			regval = u32_bits_set(regval,2,4,0);
			break;

		case 667:
			dpll_clk_set(1334);
			/*src index=4 dpll*/
			regval = u32_bits_set(regval,6,3,4);
			/*div = 1*/
			regval = u32_bits_set(regval,2,4,0);
			break;

		default:
			dpll_clk_set(1334);
			/*src index=4 dpll*/
			regval = u32_bits_set(regval,6,3,4);
			/*div = 1*/
			regval = u32_bits_set(regval,2,4,0);
			break;
	}

	REG32(REG_AON_APB_HARD_DFS_CTRL) = regval;
}

#endif
static void pub_phy_soft_reset(void)
{
	REG32(REG_AON_APB_APB_RST1) |= 1<<4;
	REG32(REG_AON_APB_APB_RST1) &= ~(1<<4);
}

static void enable_pub_clk_autogate(void)
{
	REG32(REG_PMU_APB_DDR_SLEEP_CTRL) |= 0x70;
	dmc_sprd_delay(1);
	REG32(REG_PMU_APB_DDR_SLEEP_CTRL) &= 0xfffffff0;
}


static void sdram_clk_init(u32 ddr_clk)
{
	sdram_clk_src_set(ddr_clk);
	pub_phy_soft_reset();
	enable_pub_clk_autogate();
}

static void dmc_zq_cal(int target_drv)
{
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 inc_drvn;
	u32 inc_drvp;
	u32 deinc_drvn;
	u32 deinc_drvp;
	u32 val,val1,val2,drvn,drvp;

	//step1. Setting zprog and enable zq calibration(rf_zq_pd)
	val = pdmc->dmc_cfg2;
	val = u32_bits_set(val,16,1,0);
	val = u32_bits_set(val,10,5,target_drv);
	pdmc->dmc_cfg2 = val;
	dmc_sprd_delay(2);  // delay 1us

	//step2. Calibration nmos  1
	inc_drvn = 0x0;
	val = pdmc->dmc_cfg2;
	val = u32_bits_set(val,15,1,0);
	val = u32_bits_set(val,0,5,inc_drvn);
	pdmc->dmc_cfg2 = val;
	//val = REG32(PUB_DMC_BASE+0x8);
	while((pdmc->dmc_cfg2 & DMC_ZQ_CALOVER) != 0)
	{
		inc_drvn = inc_drvn + 1;
		val = u32_bits_set(val,0,5,inc_drvn);
		pdmc->dmc_cfg2 =  val;
		dmc_sprd_delay(1);
	}

	//step3.  Calibration nmos 0
	deinc_drvn=0x1f;
	val = pdmc->dmc_cfg2;
	val = u32_bits_set(val,15,1,0);
	val = u32_bits_set(val,0,5,deinc_drvn);
	pdmc->dmc_cfg2 = val;
	//val = REG32(PUB_DMC_BASE+0x8);
	while((pdmc->dmc_cfg2 & DMC_ZQ_CALOVER) == 0)
	{
		deinc_drvn = deinc_drvn - 1;
		val = u32_bits_set(val,0,5,deinc_drvn);
		pdmc->dmc_cfg2 = val;
		dmc_sprd_delay(1);
	}

	//step4. Set average drvn
	val = pdmc->dmc_cfg2;
	val1 = (inc_drvn+deinc_drvn)/2;
	val = u32_bits_set(val,0,5,val1);
	pdmc->dmc_cfg2 = val;

	//step5. Calibration pmos 0
	inc_drvp = 0x0;
	val = pdmc->dmc_cfg2;
	val = u32_bits_set(val,15,1,1);
	val = u32_bits_set(val,5,5,inc_drvp);
	pdmc->dmc_cfg2 = val;
	//val = REG32(DMC_ZQ_CAL);
	while((pdmc->dmc_cfg2 &DMC_ZQ_CALOVER) == 0)
	{
		inc_drvp = inc_drvp + 1;
		val = u32_bits_set(val,5,5,inc_drvp);
		pdmc->dmc_cfg2 = val;
		dmc_sprd_delay(1);
	}

	//step6.  Calibration pmos 1
	deinc_drvp = 0x1f;
	val = pdmc->dmc_cfg2;
	val = u32_bits_set(val,15,1,1);
	val = u32_bits_set(val,5,5,deinc_drvp);
	pdmc->dmc_cfg2 = val;
	//val=REG32(DMC_ZQ_CAL);
	while((pdmc->dmc_cfg2 & DMC_ZQ_CALOVER) != 0)
	{
		deinc_drvp = deinc_drvp - 1;
		val = u32_bits_set(val,5,5,deinc_drvp);
		pdmc->dmc_cfg2 = val;
		dmc_sprd_delay(1);
	}

	//step7. Set average drvp
	val = pdmc->dmc_cfg2;
	val2 = (inc_drvp+deinc_drvp)/2;
	val = u32_bits_set(val,5,5,val2);
	pdmc->dmc_cfg2 = val;

	//step8. close zq Calibration
	val = pdmc->dmc_cfg2;
	val = u32_bits_set(val,16,1,1);
	pdmc->dmc_cfg2 = val;

	//step9. dmc_drvnp_setting (based on dmc_zq calibration result)
	drvn = pdmc->dmc_cfg2  & 0x1f; //drvn
	drvp = (pdmc->dmc_cfg2 >> 5) & 0x1f; //drvp

	val = pdmc->dmc_io_addr_ctrl_ac;
	val = u32_bits_set(val,21,1,1);    //Enable IB2 mode of AC slice IOs
	val = u32_bits_set(val,0,5,drvp);
	val = u32_bits_set(val,8,5,drvn);
	val = pdmc->dmc_io_addr_ctrl_ac = val;

	val = pdmc->dmc_io_dq_ctrl_ds;
	val = u32_bits_set(val,21,1,1);    //Enable IB2 mode of data slice x IOs
	val = u32_bits_set(val,0,5,drvp);
	val = u32_bits_set(val,8,5,drvn);
	pdmc->dmc_io_dq_ctrl_ds = val;

}


/*ddr type, column mode, data width, precharge pin are configed here*/
static int init_dcfg0(void)
{
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 val;

	val = pdmc->dmc_dcfg0;

	/*set column mode*/
	if (0 != ddr_chip_cur.unsymmetry)
	{
		switch(unsymmetry_mode_cur)
		{
			case DDR_6Gb_10_COL_MODE:
				val = u32_bits_set(val, 4, 3, 5);
				break;
			case DDR_6Gb_11_COL_MODE:
				val = u32_bits_set(val, 4, 3, 6);
				break;
			case DDR_12Gb_MODE:
				val = u32_bits_set(val, 4, 3, 7);
				break;
			default:
				return -1;
		}
	}
	else
	{
		switch(ddr_chip_cur.cs0_jedec_info->column)
		{
			case 8:
				val = u32_bits_set(val,4,3,0);
				break;
			case 9:
				val = u32_bits_set(val,4,3,1);
				break;
			case 10:
				val = u32_bits_set(val,4,3,2);
				break;
			case 11:
				val = u32_bits_set(val,4,3,3);
				break;
			case 12:
				val = u32_bits_set(val,4,3,4);
				break;
			default:
				return -1;
		}
	}

	/* data width */
	if (ddr_chip_cur.cs0_jedec_info->dw == 16)
	{
		val = u32_bits_set(val, 8, 1, 0);
	}
	else if (ddr_chip_cur.cs0_jedec_info->dw == 32)
	{
		val = u32_bits_set(val, 8, 1, 1);
	}
	else
	{
		return -1;
	}

	/* set drf_8bank_en */
	if (ddr_chip_cur.cs0_jedec_info->bank == 8)
	{
		val = u32_bits_set(val, 7, 1, 1);
	}
	else if (ddr_chip_cur.cs0_jedec_info->bank == 4)
	{
		val = u32_bits_set(val, 7, 1, 0);
	}
	else
	{
		return -1;
	}

	pdmc->dmc_dcfg0 = val;

	return 0;
}

/*cs pin are configed here*/
static int init_cfg0(void)
{
	int i;
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 val = pdmc->dmc_cfg0;
	u64 cs_size;
	int burstl;

	sdram_chip_whole_size(&cs_size);

	if (ddr_chip_cur.chip_type == DRAM_LPDDR2)
	{
		burstl = lpddr2_mr_info.bl;
	}
	else
	{
		burstl = lpddr3_mr_info.bl;
	}

	/*burst length*/
	switch(burstl)
	{
		case 1:
			val = u32_bits_set(val, 4, 3, 0);
			break;
		case 2:
			val = u32_bits_set(val, 4, 3, 1);
			break;
		case 4:
			val = u32_bits_set(val, 4, 3, 2);
			break;
		case 8:
			val = u32_bits_set(val, 4, 3, 3);
			break;
		case 16:
			val = u32_bits_set(val, 4, 3, 4);
			break;
		default:
			return -1;
	}

	/*cs pin*/
	for(i = 0; i < (sizeof(pin_table)/sizeof(pin_table[0])); i++)
	{
		//ram size <= 3GB
		if (cs_size <= pin_table[i].cs_size)
		{
			val = u32_bits_set(val, 0, 3, (pin_table[i].pin_index-24));
			break;
		}
	}
	//ram size > 3GB
	if (i == (sizeof(pin_table)/sizeof(pin_table[0])))
	{
		val = u32_bits_set(val, 0, 3, 7);
	}

	if (ddr_chip_cur.cs_num == 1)
	{
		val = u32_bits_set(val, 0, 3, 7);
		val = u32_bits_set(val, 14, 2, 1);
	}
	val = u32_bits_set(val, 9, 2, 3);//hight urgent qos setting
	val = u32_bits_set(val, 28, 1, 1);//open mpu_en
	pdmc->dmc_cfg0 = val;
	return 0;
}
#ifdef DDR_MR8_READ
int dram_ddr_init_pre_setting(u32 ddr_clk, int number)
{
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 regval;

#ifdef DMC_CA_SWAP
	pdmc->dmc_ca_bit_pattern_0 = 0x68405213;
	pdmc->dmc_ca_bit_pattern_1 = 0x97;
#endif

	/*pin swap conifg for CA and DQ byte0*/
	pin_swap_config();

	/*step 1)  Set timing base define */
	lpddr_timing_pre_init(ddr_chip_cur.chip_type, ddr_clk, number);

	/*step 2)  Disable rf_clk_gate_en*/
	regval = pdmc->dmc_cfg3;
	regval = u32_bits_set(regval, 0, 15, 0);
	pdmc->dmc_cfg3 = regval;

	/*step 3)  Enable drf_sample_auto_rst_en (default:0) */
	regval = pdmc->dmc_dcfg0;
	regval = u32_bits_set(regval, 17, 1, 1);
	pdmc->dmc_dcfg0 = regval;

	/*step 4)  Set initial drf_dfs_reg_sel (default:0) */
	regval = pdmc->dmc_dcfg11;
	regval = u32_bits_set(regval, 0, 4, 0);  // disable DFS and dll lock wait
	regval = u32_bits_set(regval, 4, 2, number);
	pdmc->dmc_dcfg11 = regval;

	return 0;
}
#endif
int dram_init_pre_setting(u32 ddr_clk)
{
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 regval;


#ifdef DMC_CA_SWAP
	pdmc->dmc_ca_bit_pattern_0 = 0x68405213;
	pdmc->dmc_ca_bit_pattern_1 = 0x97;
#endif
	/*pin swap conifg for CA and DQ byte0*/
	pin_swap_config();

	/*step 0) Set vref on*/
	regval = pdmc->dmc_cfg1;
	regval = u32_bits_set(regval, 0, 3, 1);	/*bit[1]=0: vref_int_pd_en,for bringup stability,bit[0]=0,for power*/
	regval = u32_bits_set(regval, 16, 3, 1);	/*bit[17]=0:vref_ext_pd_en,for bringup stability*/
	regval = u32_bits_set(regval, 20, 6, 0);	/*bit[25:20]=0:vref adj level,sel opmode*/
	pdmc->dmc_cfg1 = regval;
  
	/*step 1)  Set timing base define */
	lpddr_timing_init(ddr_chip_cur.chip_type, ddr_clk_array);

	/*step 2)  Disable rf_clk_gate_en*/
	regval = pdmc->dmc_cfg3;
	regval = u32_bits_set(regval, 0, 15, 0);
	pdmc->dmc_cfg3 = regval;

	/*step 3)  Enable drf_sample_auto_rst_en (default:0) */
	regval = pdmc->dmc_dcfg0;
	regval = u32_bits_set(regval, 17, 1, 1);
	pdmc->dmc_dcfg0 = regval;

	/*step 4)  Set initial drf_dfs_reg_sel (default:0) */
	regval = pdmc->dmc_dcfg11;
	regval = u32_bits_set(regval, 0, 4, 0);  // disable DFS and dll lock wait
	if(ddr_clk_array[0] == ddr_clk) //F0 setting timing register
	{
		regval = u32_bits_set(regval, 4, 2, 0);
	}
	else if(ddr_clk_array[1] == ddr_clk) //F1 setting timing register
	{
		regval= u32_bits_set(regval, 4, 2, 1);
	}
	else if (ddr_clk_array[2] == ddr_clk) //F2 setting timing register
	{
		regval= u32_bits_set(regval, 4, 2, 2);
	}
	else //F3 setting timing register
	{
		regval = u32_bits_set(regval, 4, 2, 3);
	}
	pdmc->dmc_dcfg11 = regval;

	return 0;
}


int dmc_dll_init(u32 init_count)
{
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 sts_val[5];
	u32 all_locked;
	u32 val;

	/*step1&2, set and start dll*/
	lpddr_dll_init(ddr_chip_cur.chip_type);

	/*step3, polling dll lock*/
	do {
		sts_val[0] = pdmc->dmc_sts_dll_ac;
		sts_val[1] = pdmc->dmc_sts_dll_ds0;
		sts_val[2] = pdmc->dmc_sts_dll_ds1;
		sts_val[3] = pdmc->dmc_sts_dll_ds2;
		sts_val[4] = pdmc->dmc_sts_dll_ds3;
		all_locked = (sts_val[0] & DLL_LOCK_BITMASK)
					& (sts_val[1] & DLL_LOCK_BITMASK)
					& (sts_val[2] & DLL_LOCK_BITMASK)
					& (sts_val[3] & DLL_LOCK_BITMASK)
					& (sts_val[4] & DLL_LOCK_BITMASK);
	}while (!all_locked);

	/*step4, set dll function*/
	val = pdmc->dmc_cfg_dll_ac; //PUB_DMC_BASE+32'h0300-----set---->[9]=1;[10]=1; [12]= 1; [15]= 1; [27]= 1;[6:0]=8
	val = u32_bits_set(val, 9, 2, 3);
	val = u32_bits_set(val, 12, 1, 1);
	val = u32_bits_set(val, 14, 1, 1);
	val = u32_bits_set(val, 27, 1, 1);
	val = u32_bits_set(val, 0, 7, init_count);
	pdmc->dmc_cfg_dll_ac = val;
	pdmc->dmc_cfg_dll_ds0 = val;
	pdmc->dmc_cfg_dll_ds1 = val;
	pdmc->dmc_cfg_dll_ds2 = val;
	pdmc->dmc_cfg_dll_ds3 = val;

	return 0;
}
static void dmc_portx_remap_addr_x(u32 addr_0, u32 addr_1)
{
#ifdef CONFIG_SOC_SHARKLE
	/*dmc remap en*/
	REG32(REG_PUB_APB_DMC_REMAP_EN) |= 0x3fff;
	REG32(REG_PUB_APB_DMC_PORT0_REMAP_ADDR_0) = addr_0;
	REG32(REG_PUB_APB_DMC_PORT0_REMAP_ADDR_1) = addr_1;
	REG32(REG_PUB_APB_DMC_PORT1_REMAP_ADDR_0) = addr_0;
	REG32(REG_PUB_APB_DMC_PORT1_REMAP_ADDR_1) = addr_1;
	REG32(REG_PUB_APB_DMC_PORT2_REMAP_ADDR_0) = addr_0;
	REG32(REG_PUB_APB_DMC_PORT2_REMAP_ADDR_1) = addr_1;
	REG32(REG_PUB_APB_DMC_PORT3_REMAP_ADDR_0) = addr_0;
	REG32(REG_PUB_APB_DMC_PORT3_REMAP_ADDR_1) = addr_1;
	REG32(REG_PUB_APB_DMC_PORT4_REMAP_ADDR_0) = addr_0;
	REG32(REG_PUB_APB_DMC_PORT4_REMAP_ADDR_1) = addr_1;
	REG32(REG_PUB_APB_DMC_PORT5_REMAP_ADDR_0) = addr_0;
	REG32(REG_PUB_APB_DMC_PORT5_REMAP_ADDR_1) = addr_1;
	REG32(REG_PUB_APB_DMC_PORT6_REMAP_ADDR_0) = addr_0;
	REG32(REG_PUB_APB_DMC_PORT6_REMAP_ADDR_1) = addr_1;
#endif
}
static int dmc_pub_addr_remap(void)
{
	u64 chipsize;
	int i;
	if ((ddr_chip_cur.cs_num == 1) || (ddr_chip_cur.unsymmetry != 0))
		return -1;

	if (-1 == sdram_chip_whole_size(&chipsize))
	{
		return -1;
	}

	/*enable all port remap*/
	switch(chipsize)
	{
		/*12G bit*/
		case 0x60000000:
			dmc_portx_remap_addr_x(0x10654210, 0x42106542);
			break;
		/*24G bit*/
		case 0xC0000000:
			dmc_portx_remap_addr_x(0x98543210, 0x3210dcba);
			break;
		default:
			break;
	}
	return 0;
}

void dmc_port_qos_cfg0(volatile unsigned int *addr,u32 timeout_pri_wr_ch, u32 timeout_thr_wr_ch, u32 timeout_thr_rd_ch)
{
	u32 regval;
	regval = *addr;
	regval = u32_bits_set(regval, 0, 4, timeout_pri_wr_ch);
	regval = u32_bits_set(regval, 16, 8, timeout_thr_wr_ch);
	regval = u32_bits_set(regval, 24, 8, timeout_thr_rd_ch);
	*addr = regval;
}

void dmc_port_qos_cfg1(volatile unsigned int *addr,u32 bandwidth_pri_rd_ch, u32 bandwidth_thr_ch, u32 bandwidth_holdoff_en_ch)
{
	u32 regval;
	regval = *addr;
	regval = u32_bits_set(regval, 0, 4, bandwidth_pri_rd_ch);
	regval = u32_bits_set(regval, 16, 10, bandwidth_thr_ch);
	regval = u32_bits_set(regval, 31, 1, bandwidth_holdoff_en_ch);
	*addr = regval;
}

#ifdef CONFIG_SOC_PIKE2
	#define  SPRD_DISP_NIC400_QOS (SPRD_DISP_MM_QOS_PHYS+0x42000)
	#define  SPRD_MM_NIC400_QOS (SPRD_DISP_MM_QOS_PHYS+0x43000)
	#define  SPRD_WCN_NIC400_QOS (SPRD_AON_WCN_2TO1_BUS_QOS+0x42000)
	#define  SPRD_AON_NIC400_QOS (SPRD_AON_WCN_2TO1_BUS_QOS+0x43000)

	QOS_CONFIG_PARA qos_config[] ={
	/*DISP*/
	{SPRD_DISP_NIC400_QOS, 200, 300, 4, 4, 3,  11, 11, 14, 0, 0},
	/*DCAM*/
	{SPRD_MM_NIC400_QOS,   80,  150, 4, 3, 3,  8,  11, 14, 0, 0},
	/*WCN*/
	{SPRD_WCN_NIC400_QOS,  100, 120, 1, 1, 10, 10, 15, 15, 0, 0},
	/*AON*/
	{SPRD_AON_NIC400_QOS,  100, 120, 1, 1, 10, 10, 15, 15, 0, 0}
	};
#endif

static void dmc_pub_qos_init(void)
{
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 regval;
	int i;
	/*port 0 MM/DCAM/ISP*/
	/*port 1 GPU*/
	/*port 2 DISP*/
	/*port 3 CPU*/
	/*port 4 AP/VSP/GSP*/
	/*port 5 WTL/PUBCP*/
	/*port 6 WCN/AON*/
	for(i = 0; i < 8*2; i += 2)
	{
		dmc_port_qos_cfg0(&pdmc->ahbaxireg[i], port_para[i].timeout_pri_wr_ch, port_para[i].timeout_thr_wr_ch, port_para[i].timeout_thr_rd_ch);
	}

	for(i = 1; i < 8*2; i += 2)
	{
		dmc_port_qos_cfg1(&pdmc->ahbaxireg[i], port_para[i].timeout_pri_wr_ch, 0x0, 0x0);
	}

	/*band width schedule*/
	regval = pdmc->dmc_cfg0;
	regval = u32_bits_set(regval, 16, 11, 0x190);
	regval = u32_bits_set(regval, 27, 1, 0);
	pdmc->dmc_cfg0 = regval;
	/*Set qos urgent map; [31:16] drf_hi_urgent_map,[15:0] drf_lo_urgent_map*/
	pdmc->dmc_dcfg10 = 0xC0003000;
#ifdef CONFIG_SOC_PIKE2
	regval = pdmc->dmc_dcfg7;
	regval = u32_bits_set(regval,8, 5, 0x18);
	pdmc->dmc_dcfg7 = regval;

	/*NIC400 write read channel config*/
	for(i = 0; i < (sizeof(qos_config)/sizeof(QOS_CONFIG_PARA)); i++)
	{
		regval = REG32((qos_config[i].subsys_base_addr + 0x130));
		regval = u32_bits_set(regval, 0, 12, qos_config[i].write_latency);
		regval = u32_bits_set(regval, 16, 12, qos_config[i].read_latency);
		REG32((qos_config[i].subsys_base_addr + 0x130)) = regval;

		regval = REG32((qos_config[i].subsys_base_addr + 0x134));
		regval = u32_bits_set(regval, 0, 3, qos_config[i].write_step);
		regval = u32_bits_set(regval, 8, 3, qos_config[i].read_step);
		REG32((qos_config[i].subsys_base_addr + 0x134)) = regval;

		regval = REG32((qos_config[i].subsys_base_addr + 0x138));
		regval = u32_bits_set(regval, 0, 4, qos_config[i].write_min_qos);
		regval = u32_bits_set(regval, 16, 4, qos_config[i].read_min_qos);
		regval = u32_bits_set(regval, 8, 4, qos_config[i].write_max_qos);
		regval = u32_bits_set(regval, 24, 4, qos_config[i].read_max_qos);
		REG32((qos_config[i].subsys_base_addr + 0x138)) = regval;

		regval = REG32((qos_config[i].subsys_base_addr + 0x10C));
		regval = u32_bits_set(regval, 16, 1, qos_config[i].write_addr_latency);
		regval = u32_bits_set(regval, 20, 1, qos_config[i].read_addr_latency);
		REG32((qos_config[i].subsys_base_addr + 0x10C)) = regval;

		regval = REG32((qos_config[i].subsys_base_addr + 0x10C));
		regval = u32_bits_set(regval, 3, 1, 1);
		regval = u32_bits_set(regval, 4, 1, 1);
		REG32((qos_config[i].subsys_base_addr + 0x10C)) = regval;
	}

	/*DMC urgent config*/
	REG32(SPRD_PUB_PHYS+0x3304) |= 0xecececec;
	REG32(SPRD_PUB_PHYS+0x3308) |= 0xecececec;
	REG32(SPRD_PUB_PHYS+0x330C) |= 0xecececec;
	REG32(SPRD_PUB_PHYS+0x3310) |= 0xecececec;
	REG32(SPRD_PUB_PHYS+0x3300) = 0xFF;

	/*DMC urgent request*/
	REG32(SPRD_PUB_PHYS+0x4300) |= 0x100;
	while(1)
	{
		regval=REG32(SPRD_PUB_PHYS+0x3300);
		if(regval&0x200)
		break;
	}

	/*clear request*/
	REG32(SPRD_PUB_PHYS+0x5300) |= 0x100;
#endif

#ifdef CONFIG_SOC_SHARKLE
	/*Set pub axi port qos*/
	REG32(REG_PUB_APB_PUB_AXI_QOS_REG) = 0xCCBFC955;/*bit[31:28] awqos_threshold_cp*/
							/*bit[27:24] arqos_threshold_cp*/
							/*bit[23:20] awqos_threshold_aon_wcn*/
							/*bit[19:16] arqos_threshold_aon_wcn*/
							/*bit[15:12] AWQOS_WCN*/
							/*bit[11: 8] ARQOS_WCN*/
							/*bit[7:  4] AWQOS_AON*/
							/*bit[3:  0] ARQOS_AON*/
	REG32(REG_AP_AHB_AP_QOS0) = 0x55555566; /*[31:28]	ar_qos_usb	RW	0x5*/
						/*[27:24]	aw_qos_usb	RW	0x5*/
						/*[23:20]	ar_qos_ce	RW	0x5*/
						/*[19:16]	aw_qos_ce	RW	0x5*/
						/*[15:12]	ar_qos_dma	RW	0x5*/
						/*[11:8]	aw_qos_dma	RW	0x5*/
						/*[7:4]		ar_qos_ca53	RW	0x6*/
						/*[3:0]		aw_qos_ca53	RW	0x6*/
	REG32(REG_AP_AHB_AP_QOS1) = 0x55555555; /*[31:28]	ar_qos_sdio0	RW	0x5*/
						/*[27:24]	aw_qos_sdio0	RW	0x5*/
						/*[23:20]	ar_qos_sdio1	RW	0x5*/
						/*[19:16]	aw_qos_sdio1	RW	0x5*/
						/*[15:12]	ar_qos_emmc	RW	0x5*/
						/*[11:8]	aw_qos_emmc	RW	0x5*/
						/*[7:4]		ar_qos_nandc	RW	0x5*/
						/*[3:0]		aw_qos_nandc	RW	0x5*/
	REG32(REG_AP_AHB_AP_QOS2) = 0xff5566df; /*[31:28]	arqos_threshold_cpu	RW	0xf*/
						/*[27:24]	awqos_threshold_cpu	RW	0xf*/
						/*[23:20]	arqos_threshold_main	RW	0x5*/
						/*[19:16]	awqos_threshold_main	RW	0x5*/
						/*[15:12]	arqos_threshold_merge	RW	0x6*/
						/*[11:8]	awqos_threshold_merge	RW	0x6*/
						/*[7:4]		arqos_threshold_disp	RW	0xd*/
						/*[3:0]		awqos_threshold_disp	RW	0xf*/

#endif
}

void dmc_init_post_setting(u32 ddr_clk)
{
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 val;
	u8 mr0;

	/*step 2)  Read mr0 till mr0[0]==0 : DAI complete */
	do {
		dmc_mrr(CMD_CS_0, 0, &mr0, 10000);
	}while((mr0&1));

#ifdef DDR_AUTO_DETECT
	/*step 3) auto_detect */
	if (0 != lpddr_auto_detect())
	{
		dmc_print_str("lpddr auto detect failed\r\n");
		return -1;
	}
#endif
#ifdef CA_TRAINING
	/*step 4) CA Training and Write Leveling */
	if (ddr_chip_cur.chip_type != DRAM_LPDDR2)
	{
		if (ddr_clk == ddr_clk_array[0])
		{
			dmc_lpddr3_ca_training();
			dmc_lpddr3_write_leveling();
		}
	}
#endif
	/*step 5)  Set burst length and rf_cs_postion.*/
	if (0 != init_cfg0())
	{
		dmc_print_str("init cfg0 fail\r\n");
		return -1;
	}

	/*step 6)  Set dram width if x16 or 4 bank*/
	if (0 != init_dcfg0())
	{
		dmc_print_str("init cfg0 fail\r\n");
		return -1;
	}

	/* step 7) set bist mask for 16bit dram */
	if (ddr_chip_cur.cs0_jedec_info->dw == 16)
	{
		pdmc->dmc_bist[5] = 0xffff0000;
	}

	/*step 8) Set axi channel for Asynchronous channel
	 *SharklE all axi channel is syncchronous channel
	 * */
#ifdef DMC_PORTX_SYNC_MODE
	/*PUB_DMC_BASE+32'h24+8*0  ==0x30000024*/
	val = pdmc->ahbaxireg[1];
	val = u32_bits_set(val, 4, 1, 0);
	pdmc->ahbaxireg[1] = val;

	/*PUB_DMC_BASE+32'h24+8*2  ==0x30000034*/
	val = pdmc->ahbaxireg[5];
	val = u32_bits_set(val, 4, 1, 0);
	pdmc->ahbaxireg[5] = val;

	/*PUB_DMC_BASE+32'h24+8*5  ==0x3000004c*/
	val = pdmc->ahbaxireg[11];
	val = u32_bits_set(val, 4, 1, 0);
	pdmc->ahbaxireg[11] = val;

	/*PUB_DMC_BASE+32'h24+8*7 ==0x3000005c*/
	val = pdmc->ahbaxireg[15];
	val = u32_bits_set(val, 4, 1, 0);
	pdmc->ahbaxireg[15] = val;
#endif
	/*step 9) Set idle_cnt. (drf_pwr_down_idle_cnt)[31:16]=0x10, (drf_self_ref_idle_cnt)[15:0]=0x100*/
	//need witch yuxiang sync
//	pdmc->dmc_dcfg10 = 0x00100100;

	/*step 10) enbale lowpower*/
	val = pdmc->dmc_dcfg9;
	val = u32_bits_set(val, 0, 3, 0x5);	/*drf_auto_clk_stop_en_ahb : 1 */
						/*drf_auto_pwr_down_en_ahb : 0 */
						/*drf_auto_self_ref_en_ahb : 1 */
	val = u32_bits_set(val, 4, 8, 0xff);	/*drf_t_cksrx: 0xf */
						/*drf_t_cksre: 0xf*/
	val = u32_bits_set(val, 16, 4, 0xf);	/*drf_ca_shutdow : 1*/
						/*drf_cs_shutdown_en : 1*/
						/*drf_ck_shutdown_en : 1*/
						/*drf_dqspull_shutdown_en : 1*/
#ifndef  CHIP_VERSION
	/* bit 12 must be cleared on PXP/ZEBU/FPGA, to avoid DMC hang for dll lock when exiting self-refresh. */
	val = u32_bits_set(val, 12, 1, 0);
#endif
	pdmc->dmc_dcfg9 = val;

	if (ddr_chip_cur.chip_type != DRAM_LPDDR2)
	{
		/*step 11) setting drf_t_mr4 for not the same with drf_t_zqc*/
		val = pdmc->dmc_dcfg5;
		val = u32_bits_set(val, 0, 24, 0x600000);	/*drf_t_mr4*/
		val = u32_bits_set(val, 24, 2, 1);		/*[24]=1: drf_auto_mr4_en, [25]=0: for rank-0 */
		pdmc->dmc_dcfg5 = val;
	}

#ifdef EDA_TEST
	/*step 12)  drf_auto_zqc_sel (2:8`h56 ZQCS; 1:8`hAB ZQCL)*/
	val = pdmc->dmc_dcfg6;
	val = u32_bits_set(val, 0, 24, 0x630000);
	val = u32_bits_set(val, 24, 1, 1);		/*[24]=1: drf_auto_zqc_en */
	if(ddr_chip_cur.cs_num == 1)			/*[25]=0: drf_auto_zqc_allcs,for rank-0*/
		val = u32_bits_set(val, 25, 1, 0);
	val = u32_bits_set(val, 26, 2, 2);
	pdmc->dmc_dcfg6 = val;
#endif

	/*step 13) enable auto refresh and pre bank refresh*/
	val = pdmc->dmc_dcfg3;
	val = u32_bits_set(val, 12, 1, 1);
	if(ddr_chip_cur.cs_num == 1)			/*[13]=0: drf_auto_ref_allcs,CSs are auto-refresh one by one */
		val = u32_bits_set(val, 13, 1, 0);
	val = u32_bits_set(val, 15, 1, 1);
	pdmc->dmc_dcfg3 = val;

	/*step 14) enable DFS and set pll lock time*/
	val = pdmc->dmc_dcfg11;
	val = u32_bits_set(val, 0, 4, 0x7);			//dfs en
	val = u32_bits_set(val, 17, 1, 1);
	val = u32_bits_set(val, 20, 12, 0);
#ifndef  CHIP_VERSION
	/* bit 1 must be cleared on PXP/ZEBU/FPGA, because no dll */
	val = u32_bits_set(val, 1, 1, 0);
#endif
	pdmc->dmc_dcfg11 = val;

#if 0
	/*step 15) Set vref on*/
	val = pdmc->dmc_cfg1;
	val = u32_bits_set(val, 0, 3, 1);	/*bit[1]=0: vref_int_pd_en,for bringup stability,bit[0]=0,for power*/
	val = u32_bits_set(val, 16, 3, 1);	/*bit[17]=0:vref_ext_pd_en,for bringup stability*/
	val = u32_bits_set(val, 20, 6, 0);	/*bit[25:20]=0:vref adj level,sel opmode*/
	pdmc->dmc_cfg1 = val;
#endif

	/*step 16) rf_clk_gate_en*/
	val = pdmc->dmc_cfg3;
	val = u32_bits_set(val, 0, 15, 0x7fff);
	pdmc->dmc_cfg3 = val;

	/*step 17) Reset phy read fifo (drf_sample_rst) */
	reset_dmc_fifo();
}
static void dmc_ddr_size_limit(chipram_env_t *p_env, u32 limit_size)
{
	if (p_env->cs_number == 2)
	{
		if (p_env->dram_size >= limit_size)
		{
			if (p_env->cs0_size >= limit_size)
			{
				p_env->cs0_size = limit_size - BIST_RESERVE_SIZE;
				p_env->cs1_size = 0;
				p_env->cs_number = 1;
			}
			else
			{
				p_env->cs1_size = limit_size - (p_env->cs0_size + BIST_RESERVE_SIZE);
			}
		}
		else
		{
			p_env->cs1_size -= BIST_RESERVE_SIZE;
		}
	}
	else
	{
		if (p_env->dram_size >= limit_size)
			p_env->cs0_size = limit_size - BIST_RESERVE_SIZE;
		else
			p_env->cs0_size -= BIST_RESERVE_SIZE;
	}
}
void dmc_update_param_for_uboot(void)
{
	chipram_env_t * p_env = CHIPRAM_ENV_ADDR;
	p_env->cs_number = ddr_chip_cur.cs_num;
	p_env->cs0_size = jedec_info_cs0.cs_size;
	p_env->cs1_size = jedec_info_cs1.cs_size;
        u32 val;
	/*reserve 1M room*/
	/*
	 * Address space 0xFFE0_0000~0xFFFF_FFFF is reserverd for internal memory on some 32bits platform, such as SharkL2.
	 * CPU can only access DDR_START_ADDR_PHY(0x8000_0000) ~ 0xFFE0_0000 for external memory.
	 */
	if (ddr_chip_cur.cs_num == 1)
	{
		p_env->cs1_size = jedec_info_cs1.cs_size = 0;
		p_env->dram_size = p_env->cs0_size;
	}
	else if (ddr_chip_cur.cs_num == 2)
		p_env->dram_size = (u64)p_env->cs0_size + (u64)p_env->cs1_size;

	if (ddr_chip_cur.cs_num == 2)
	{
#if defined(CONFIG_CHIPRAM_DDR_1G)
		dmc_ddr_size_limit(p_env, 0x40000000);
#elif defined(CONFIG_CHIPRAM_DDR_512M)
		dmc_ddr_size_limit(p_env, 0x20000000);
#elif defined(CONFIG_CHIPRAM_DDR_CUSTOMIZE)
		dmc_ddr_size_limit(p_env, CONFIG_CHIPRAM_DDR_CUSTOMIZE);
#else
#ifdef CONFIG_ARCH_SCX35L2
		if (0x80000000 <= p_env->dram_size)
		{
			if(p_env->cs0_size >= 0x80000000) {
				p_env->cs0_size = 0x80000000 - (SYS_MAP_RESERVE_SIZE + BIST_RESERVE_SIZE);
				p_env->cs1_size = 0;
			} else
				p_env->cs1_size = 0x80000000 - (p_env->cs0_size + SYS_MAP_RESERVE_SIZE + BIST_RESERVE_SIZE);
		}
		else
#endif
		{
			if (0x100000000 < p_env->dram_size)
				p_env->cs1_size = 0x100000000 - p_env->cs0_size - BIST_RESERVE_SIZE;
			else
				p_env->cs1_size -= BIST_RESERVE_SIZE;
		}
#endif
	}
	else if (ddr_chip_cur.cs_num == 1)
	{
#if defined(CONFIG_CHIPRAM_DDR_1G)
		dmc_ddr_size_limit(p_env, 0x40000000);
#elif defined(CONFIG_CHIPRAM_DDR_512M)
		dmc_ddr_size_limit(p_env, 0x20000000);
#elif defined(CONFIG_CHIPRAM_DDR_CUSTOMIZE)
		dmc_ddr_size_limit(p_env, CONFIG_CHIPRAM_DDR_CUSTOMIZE);
#else
#ifdef CONFIG_ARCH_SCX35L2
		if (0x80000000 <=  p_env->dram_size)
		{
			p_env->cs0_size = 0x80000000 - (SYS_MAP_RESERVE_SIZE + BIST_RESERVE_SIZE);
		}
		else
#endif
		{
			p_env->cs0_size -= BIST_RESERVE_SIZE;
		}
#endif
	}
	/* Save physical ddr size(8bytes) in DMC reg for kernel dirver. */
	((DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE)->dmc_bist[13] = p_env->dram_size & 0xFFFFFFFF;
	((DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE)->dmc_bist[14] = p_env->dram_size >> 32;
	if (ddr_chip_cur.unsymmetry)
	{
		val = REG32(DMC_DUMMY_REG1);
		val = u32_bits_set(val,0,4,ddr_chip_cur.cs1_jedec_info->column);
		REG32(DMC_DUMMY_REG1) = val;
	}
}

static void dmc_smart_light_sleep_prepare(u32 ddr_clk)
{
	u32 regval;
#ifdef CONFIG_SOC_SHARKLE
	/*Step 1) enable smart light sleep*/
	REG32(REG_PMU_APB_LIGHT_SLEEP_ENABLE) |= BIT_PMU_APB_PUB_SYS_SMART_LSLP_ENA;

	/*Step 2) clear force sleep signal*/
	regval = REG32(REG_PMU_APB_SLEEP_CTRL);
	regval = u32_bits_set(regval, 29, 2, 0);
	REG32(REG_PMU_APB_SLEEP_CTRL) = regval;

	/*Step 3) light sleep fence idle cnt setting*/
	regval = REG32(REG_PUB_APB_FENCING_CTRL);
	regval = u32_bits_set(regval, 0, 30, ddr_clk);
	REG32(REG_PUB_APB_FENCING_CTRL) = regval;

#endif
#ifdef CONFIG_SOC_PIKE2
	/*Step 1) subsys HW enable*/
	regval = REG32(REG_AON_APB_DDR_SLEEP_CTRL1);
	regval = u32_bits_set(regval, 16, 9, 0x1FF);
	REG32(REG_AON_APB_DDR_SLEEP_CTRL1) = regval;

	/*Step 2) HW control smart light sleep*/
	regval = REG32(REG_AON_APB_DDR_SLEEP_CTRL0);
	regval = u32_bits_set(regval, 5, 1, 1);
	REG32(REG_AON_APB_DDR_SLEEP_CTRL0) = regval;

	/*Step 3) deep sleep force enable*/
	regval = REG32(REG_AON_APB_DDR_SLEEP_CTRL2);
	regval = u32_bits_set(regval, 16, 1, 1);
	REG32(REG_AON_APB_DDR_SLEEP_CTRL2) = regval;
#endif

}

static void dmc_ddr_debug_mode(void)
{
#if defined(DDR_MODE)
	u32 ddr_mode = mcu_clk_para.ddr_debug_mode.value;
#else
	u32 ddr_mode = 0x0;
#endif
	u32 regval;
	u8 mr_val;
	int i;
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;

	/* ddr_mode
	 * bit[0] 1'b1 dfs disable; 1'b0 dfs_enable
	 * bit[1] 1'b1 retention disable; 1'b0 retention enable
	 *
	*/
	if ((ddr_mode & 0x1))
	{
		regval = REG32(DMC_DUMMY_REG1);
		regval = u32_bits_set(regval, 4, 4,0xf);
		REG32(DMC_DUMMY_REG1) = regval;
	}

	if ((ddr_mode & 0x2))
	{
		regval = REG32(DMC_DUMMY_REG1);
		regval = u32_bits_set(regval, 8, 4,0xf);
		REG32(DMC_DUMMY_REG1) = regval;
	}
#ifdef CONFIG_NAND_SPL
	pdmc->dmc_dtmg_f[3][2] = 0;
	if (ddr_chip_cur.chip_type == DRAM_LPDDR2)
		pdmc->dmc_dtmg_f[3][2] |= 2;
	else if (ddr_chip_cur.chip_type == DRAM_LPDDR3)
		pdmc->dmc_dtmg_f[3][2] |= 3;
	else if (ddr_chip_cur.chip_type == DRAM_LPDDR1)
		pdmc->dmc_dtmg_f[3][2] |= 1;

	pdmc->dmc_dtmg_f[3][2] |= (ddr_chip_cur.cs_num << 4);

	pdmc->dmc_dtmg_f[3][11] = 0;
	for(i = 5; i < 9; i++)
	{
		dmc_mrr(0, i, &mr_val, 10000);
		pdmc->dmc_dtmg_f[3][11] |= (((u32)mr_val) & 0x0FF) << ((i-5)*8);
	}
	if (ddr_chip_cur.cs_num == 2)
	{
		pdmc->dmc_dtmg_f[3][13] = 0;
		for(i = 5; i < 9; i++)
		{
			dmc_mrr(1, i, &mr_val, 10000);
			pdmc->dmc_dtmg_f[3][13] |= (((u32)mr_val) & 0x0FF) << ((i-5)*8);
		}
	}
#endif

}

#ifdef CONFIG_FPGA
#ifndef CONFIG_SOC_SHARKLE
void sdram_init_fpga()
{
	REG32(0x402b00b0) = 0x00000005;
	REG32(0x402b0130) = 0x00000000;
	;REG32(0x50820010) = 0x00000010;
	dmc_sprd_delay(200);
	REG32(0x30000200) = 0x43090707;
	REG32(0x30000204) = 0x02080700;
	REG32(0x30000208) = 0x54242c3c;
	REG32(0x3000020c) = 0x31021310;
	REG32(0x30000210) = 0x000c0303;
	REG32(0x30000214) = 0x001e0002;
	REG32(0x30000218) = 0x001e0002;
	REG32(0x3000021c) = 0x001c0002;
	REG32(0x30000220) = 0x007f0006;
	REG32(0x30000224) = 0x007f0006;
	REG32(0x30000228) = 0x007c0006;
	REG32(0x3000022c) = 0x20241004;
	REG32(0x30000230) = 0x0c300000;
	REG32(0x30000210) = 0x00100404;
	REG32(0x30000214) = 0x03000300;
	REG32(0x30000218) = 0x03000000;
	REG32(0x3000021c) = 0x00800000;
	REG32(0x30000220) = 0xf0000000;
	REG32(0x30000224) = 0xf0000000;
	REG32(0x30000228) = 0xf0000000;
	REG32(0x3000022c) = 0x203c1006;
	REG32(0x30000000) = 0x00000335;
	REG32(0x30000100) = 0x00020da0;
	REG32(0x30000300) = 0x6a228501;
	REG32(0x30000400) = 0x6a228501;
	REG32(0x30000500) = 0x6a228501;
	REG32(0x30000600) = 0x6a228501;
	REG32(0x30000700) = 0x6a228501;
	REG32(0x30000308) = 0x80000008;
	REG32(0x30000300) = 0x6a228401;
	REG32(0x30000408) = 0x80000008;
	REG32(0x3000040c) = 0x80000008;
	REG32(0x30000410) = 0x80000008;
	REG32(0x30000414) = 0x80000004;
	REG32(0x30000400) = 0x6a228401;
	REG32(0x30000508) = 0x80000008;
	REG32(0x3000050c) = 0x80000008;
	REG32(0x30000510) = 0x80000008;
	REG32(0x30000514) = 0x80000004;
	REG32(0x30000500) = 0x6a228401;
	REG32(0x30000608) = 0x80000008;
	REG32(0x3000060c) = 0x80000008;
	REG32(0x30000610) = 0x80000008;
	REG32(0x30000614) = 0x80000004;
	REG32(0x30000600) = 0x6a228401;
	REG32(0x30000708) = 0x80000008;
	REG32(0x3000070c) = 0x80000008;
	REG32(0x30000710) = 0x80000008;
	REG32(0x30000714) = 0x80000004;
	REG32(0x30000700) = 0x6a228401;
	REG32(0x30000300) = 0x6a220401;
	REG32(0x30000400) = 0x6a220401;
	REG32(0x30000500) = 0x6a220401;
	REG32(0x30000600) = 0x6a220401;
	REG32(0x30000700) = 0x6a220401;
	REG32(0x30000414) = 0x0300007f;
	REG32(0x30000514) = 0x0300007f;
	REG32(0x30000614) = 0x0300007f;
	REG32(0x30000714) = 0x0300007f;
	REG32(0x30000428) = 0x001c0000;
	REG32(0x30000528) = 0x001c0000;
	REG32(0x30000628) = 0x001c0000;
	REG32(0x30000728) = 0x001c0000;
	REG32(0x30000100) = 0x00024da0;
	dmc_sprd_delay(100);
	REG32(0x30000104) = 0x9100003f;
	dmc_sprd_delay(100);
	REG32(0x30000108) = 0x000000ff;
	REG32(0x30000104) = 0x0100000a;
	dmc_sprd_delay(100);
	REG32(0x30000104) = 0x1100000a;
	dmc_sprd_delay(100);
	REG32(0x300004a4) = 0x03000000;
	REG32(0x300005a4) = 0x03000000;
	REG32(0x300006a4) = 0x03000000;
	REG32(0x300007a4) = 0x03000000;
	REG32(0x30000108) = 0x00000006;
	REG32(0x30000104) = 0x91000002;
	REG32(0x30000108) = 0x00000003;
	REG32(0x30000104) = 0x91000003;
	dmc_sprd_delay(100);
	REG32(0x30000108) = 0x00000023;
	REG32(0x30000104) = 0x91000001;
	dmc_sprd_delay(100);
	REG32(0x30000124) = 0x00001741;
	REG32(0x3000012c) = 0x00000007;
	REG32(0x30000114) = 0x06001ff0;
	REG32(0x3000010c) = 0x01013019;
	REG32(0x30000118) = 0x00000800;
}
#else
void sdram_init_fpga()
{
	REG32(0x402b0130) = 0x00000000;
	dmc_sprd_delay(100);
	REG32(0x402e0050) = 0x189d89d8;
	dmc_sprd_delay(100);
	REG32(0x30000200) = 0x43090707;
	REG32(0x30000204) = 0x02080700;
	REG32(0x30000208) = 0x54242c3c;
	REG32(0x3000020c) = 0x31021310;
	REG32(0x30000220) = 0x00110606;
	REG32(0x30000214) = 0x001e0005;
	REG32(0x30000218) = 0x001e0005;
	REG32(0x3000021c) = 0x001c0005;
	REG32(0x30000220) = 0x00ff000a;
	REG32(0x30000224) = 0x00ff000a;
	REG32(0x30000228) = 0x00fc000a;
	REG32(0x3000022c) = 0x03e83008;
	REG32(0x30000230) = 0x14520008;
	REG32(0x30000210) = 0x00100404;
	REG32(0x30000214) = 0x03000300;
	REG32(0x30000218) = 0x03000000;
	REG32(0x3000021c) = 0x00800000;
	REG32(0x30000220) = 0xf0000000;
	REG32(0x30000224) = 0xf0000000;
	REG32(0x30000228) = 0xf0000000;
	REG32(0x3000022c) = 0x203c3406;
	dmc_sprd_delay(100);
	REG32(0x30000000) = 0x00000137;
	REG32(0x30000100) = 0x40024db0;
	dmc_sprd_delay(100);
	REG32(0x30000104) = 0x8100003f;
	dmc_sprd_delay(100);
	REG32(0x30000108) = 0x000000ff;
	REG32(0x30000104) = 0x0100000a;
	dmc_sprd_delay(100);
	REG32(0x30000104) = 0x1100000a;
	dmc_sprd_delay(100);
	REG32(0x30000494) = 0x03145294;
	dmc_sprd_delay(100);
	REG32(0x30000108) = 0x00000006;
	REG32(0x30000104) = 0x91000002;
	REG32(0x30000108) = 0x00000003;
	REG32(0x30000104) = 0x91000003;
	REG32(0x30000108) = 0x00000023;
	REG32(0x30000104) = 0x81000001;
	dmc_sprd_delay(100);
	REG32(0x30000124) = 0x00001741;
	REG32(0x30000114) = 0x06001ff0;
	REG32(0x3000010c) = 0x00193019;
	REG32(0x3000012c) = 0x00000000;
	REG32(0x30000118) = 0x0a000800;
}
#endif
#endif

#ifdef MEM_TEST
char  log_string_2[32];
static char *  string_to_hex(u64 val)
{
	int i, j, num;
	u64 temp = val;

	log_string_2[0] = '0';
	log_string_2[1] = 'x';
	for (i = 0; i < 16; i++)
	{
		temp = (val >> ((7-i)*4)) & 0xf;
		if (temp < 0xa)
			log_string_2[2+i] = temp+0x30;
		else
			log_string_2[2+i] = 'A'+temp-0xa;
	}
	log_string_2[18] = ' ';
	log_string_2[19] = 0;
	return log_string_2;
}
void ddr_write_read_test(void)
{
	u64 i, cs_size;
	sdram_chip_whole_size(&cs_size);
	for(i=0;i<cs_size;i+=0x8)
	{
		*(volatile u64*)(DDR_START_ADDR_PHY + i) = DDR_START_ADDR_PHY + i;
	}
	for(i=0;i<cs_size;i+=0x8)
	{
		if(*(volatile u64*)(DDR_START_ADDR_PHY + i) != (DDR_START_ADDR_PHY + i))
		{
			dmc_print_str("address:");
			dmc_print_str(string_to_hex((DDR_START_ADDR_PHY + i)));
			dmc_print_str("data:");
			dmc_print_str(string_to_hex(*(volatile u64*)(DDR_START_ADDR_PHY + i)));
			dmc_print_str("\r\n");
			dmc_print_str("ddr write read test fail\r\n");
			while(1);
		}
	}
	return;
}
#endif

#ifdef CONFIG_FDL1
#define TEST_SIZE 5*1024*1024
#define TEST_PATTERN 0x12345678
//cs0 at least 128M,then can test cs1
#define CS0_TEST_MIN_LENGTH 128*1024*1224

int ddr_selfrefresh_test(u32 timeout)
{
	u64 cs0_size,cs1_size;
	u32 i;
	volatile u32 * cs0_base,* cs1_base;

	cs0_size = jedec_info_cs0.cs_size;
	cs1_size = 0;
	cs0_base = DDR_START_ADDR_PHY;



	if(TEST_SIZE > cs0_size)
	{
		return -1;
	}

	if (ddr_chip_cur.cs_num == 2)
	{
		if(cs0_size > CS0_TEST_MIN_LENGTH)
		{
			cs1_size = (u64)(jedec_info_cs1.cs_size);
			cs1_base = DDR_START_ADDR_PHY + cs0_size;
			if(TEST_SIZE > cs1_size)
			{
				return -1;
			}
		}
	}
	dmc_print_str("sr start\r\n");

	for(i = 0; i < TEST_SIZE/4 ; i++)
	{
		*(cs0_base + i) = TEST_PATTERN;
	}

	if(cs1_size != 0)
	{
		for(i = 0; i < TEST_SIZE/4 ; i++)
		{
			*(cs1_base + i) = TEST_PATTERN;
		}
	}

	//timeout s
	dmc_sprd_delay((1000/2)*(timeout*1000-1000));

	dmc_print_str("wait end, data check\r\n");
	for(i = 0; i < TEST_SIZE/4; i++)
	{
		if(*(cs0_base + i) != TEST_PATTERN)
		{
			dmc_print_str("sr test fail\r\n");
			return -1;
		}
	}

	if(cs1_size != 0)
	{
		for(i = 0; i < TEST_SIZE/4; i++)
		{
			if(*(cs1_base + i) != TEST_PATTERN)
			{
				dmc_print_str("sr test cs1 fail\r\n");
				return -1;
			}
		}
	}
	dmc_print_str("sr test pass\r\n");
	return 0;

}

int ddr_scan_fdl1_test(int start, int end)
{
	int ret;

	if(start <= ddr_chip_cur.cs0_jedec_info->cs_size) {
		ret = ddr_bist_test(0,start);
		if(ret != 0)
			return -1;
	} else {
		ret = ddr_bist_test(0,ddr_chip_cur.cs0_jedec_info->cs_size);
		if(ret != 0)
			return -1;
		ret = ddr_bist_test(ddr_chip_cur.cs0_jedec_info->cs_size, start);
		if(ret != 0)
			return -1;
	}

	if(end >= ddr_chip_cur.cs0_jedec_info->cs_size) {
		if(ddr_chip_cur.cs_num == 2) {
			ret = ddr_bist_test(end, 0);
			if(ret != 0)
				return -1;
		}
	} else {
		ret = ddr_bist_test(end,ddr_chip_cur.cs0_jedec_info->cs_size);
		if(ret != 0)
			return -1;
		if(ddr_chip_cur.cs_num == 2) {
			ret = ddr_bist_test(ddr_chip_cur.cs0_jedec_info->cs_size, 0);
			if(ret != 0)
				return -1;
		}
	}
	return 0;
}
#endif
int sdram_init(void)
{
#ifdef CONFIG_FPGA
	sdram_init_fpga();
#else

#if defined(CONFIG_CLK_PARA)
	u32 ddr_clk = (mcu_clk_para.ddr_freq.value)/1000000;
#else
	u32 ddr_clk = DDR_CLK;
#endif
	u32 regval;
	dmc_print_str("DDR init start\r\n");
	/* Make sure that clk set(4 points) including current initial ddr_clk */
	/*if ((ddr_clk_array[0] != ddr_clk)
		&& (ddr_clk_array[1] != ddr_clk)
		&& (ddr_clk_array[2] != ddr_clk)
		&& (ddr_clk_array[3] != ddr_clk))
	{
		ddr_clk_array[3] = ddr_clk;
	}*/

	/*  Step0. Power up, tb_reset, set_clock; */
#ifdef CONFIG_SOC_PIKE2
	REG32(REG_AON_APB_CM4_SYS_SOFT_RST) = 0;
	dmc_sprd_delay(10);

	REG32(REG_AON_APB_CM4_SYS_SOFT_RST) |=0x1;
	dmc_sprd_delay(10);
	/*cm4 soft reset (bit[8])*/
	regval = REG32(REG_PMU_APB_SOFT_RST);
	regval = u32_bits_set(regval, 8, 1, 0);
	REG32(REG_PMU_APB_SOFT_RST) = regval;
	dmc_sprd_delay(10);
#endif
	REG32(REG_PMU_APB_DDR_PHY_RET_CFG) = 0x0;
//	REG32(PMU_APB_SOFT_RESET) &= ~CM4_SOFT_RESET;

	/*if (ddr_chip_cur.chip_type == DRAM_LPDDR2)
	{
		#ifndef DDR_MIN_CLK
		ddr_clk_array[0] = 533;
		#else
		ddr_clk_array[0] = 466;
		#endif
	}*/

#ifdef DDR_MR8_READ
	sdram_clk_init(ddr_clk_array[3]);

	/* Step1. set pin drvn drvp*/
	dmc_zq_cal(DDR_DRV_CFG);

	/* Step2. pre-setting */
	if (0 != dram_ddr_init_pre_setting(ddr_clk_array[3], 3))
	{
		dmc_print_str("error:-3\r\n");
		while(1);
	}
	/* Step3. dmc_dll_init.  This step should be skipped on PXP/ZEBU/FPGA platform */
	if (0 != dmc_dll_init(DDR_DLL_CFG))
	{
		dmc_print_str("error:-4\r\n");
		while(1);
	}

	if (0 != lpddr_pre_powerup_init())
	{
		dmc_print_str("error:-3\r\n");
		while(1);
	}
#endif

#ifndef CONFIG_SOC_PIKE2
	if (ddr_chip_cur.chip_type == DRAM_LPDDR2)
	{
		#ifndef DDR_MIN_CLK
		ddr_clk_array[0] = 533;
		#else
		ddr_clk_array[0] = DDR_MIN_CLK;
		#endif
	}
#endif

#ifdef DDR_FREQ_AUTO_SEL
	if(ddr_clk == ddr_clk_array[0])
	{
		mr_freq_select(&ddr_clk);
		ddr_clk_array[0] = ddr_clk;
	}
#endif

	if (ddr_clk > ddr_clk_array[0])
		ddr_clk = ddr_clk_array[0];

	sdram_clk_init(ddr_clk);

	/* Step1. set pin drvn drvp*/
	dmc_zq_cal(DDR_DRV_CFG);

	/* Step2. pre-setting */
	if (0 != dram_init_pre_setting(ddr_clk))
	{
		dmc_print_str("error:-3\r\n");
		while(1);
	}
	if(ddr_clk == ddr_clk_array[0])
		ui_qtr_dly_cnt_init();

	/* Step3. dmc_dll_init.  This step should be skipped on PXP/ZEBU/FPGA platform */
	if (0 != dmc_dll_init(DDR_DLL_CFG))
	{
		dmc_print_str("error:-4\r\n");
		while(1);
	}

	/* Step4. lpddr23_powerup_init */
	if (0 != lpddr_powerup_init(ddr_clk))
	{
		dmc_print_str("error:-5\r\n");
		while(1);
	}

	// Step5. Dram_init_post_setting
	dmc_init_post_setting(ddr_clk);

	dmc_pub_addr_remap();

	dmc_pub_qos_init();

	if(0 != ddr_scan_online_sprd_r2p0(ddr_clk))
	{
		dmc_print_str("error:-6\r\n");
		while(1);
	}
#ifdef CONFIG_DDR_SCAN
	ddr_scan_offline_sprd_r3p0();
	while(1);
#endif
	/*ddr init done flag*/
	REG32(REG_PMU_APB_PUB_ACC_RDY) |= 0x1;
	dmc_update_param_for_uboot();
	dmc_smart_light_sleep_prepare(ddr_clk);
	dmc_ddr_debug_mode();
	dmc_print_str("DDR init OK\r\n");
#ifdef MEM_TEST
	dmc_print_str("ddr write read test start\r\n");
	ddr_write_read_test();
	dmc_print_str("ddr write read test end\r\n");
#endif
#endif
	return 0;
}
