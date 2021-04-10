#include <asm/types.h>
#include <common.h>
#include "asm/arch/clk_para_config.h"
#include "dmc_sprd_r1p0.h"
#include "dmc_sprd_misc.h"

#define PD_SELECT_AC 	3
#define PD_SELECT_DS0 	3
#define PD_SELECT_DS1 	3
#define PD_SELECT_DS2 	3
#define PD_SELECT_DS3 	3

//#define DFS_SUPPORT

static DRAM_JEDEC_INFO jedec_info_cs0 = {0, 	/*cs index*/
										 CFG_CS0_BANK_NUM, 	/*bank number*/
										 CFG_CS0_ROW_NUM, 	/*row number*/
										 CFG_CS0_COLUMN_NUM, 	/*column number*/
										 CFG_CS0_DQ_DW, 	/*data width*/
										 CFG_CS0_AP_PIN_POS,	/*auto precharge pin position*/
										 CFG_CS0_SIZE	/*cs0 size*/
										};	

static DRAM_JEDEC_INFO jedec_info_cs1 = {1, 	/*cs index*/
										 CFG_CS1_BANK_NUM, 	/*bank number*/
										 CFG_CS1_ROW_NUM, 	/*row number*/
										 CFG_CS1_COLUMN_NUM, 	/*column number*/
										 CFG_CS1_DQ_DW, 	/*data width*/
										 CFG_CS1_AP_PIN_POS,	/*auto precharge pin position*/
										 CFG_CS1_SIZE	/*cs1 size*/
										};	



static DRAM_CHIP_INFO ddr_chip_cur = {CFG_DRAM_TYPE,		/*dram type*/ 
									  DRAM_SAMSUNG,			/*vendor*/
									  2,					/*cs number*/
									  &jedec_info_cs0,		/*phycial character*/
									  &jedec_info_cs1,		/*phycial character*/
									  CFG_IS_UNSYMMETRY_DRAM/*if is unsymmetry dram*/
};

DDR_UNSYMMETRY_MODE unsymmetry_mode_cur = CFG_UNSYMMETRY_DRAM_MODE;	/*unsymmetry type*/


static DMC_CHARACTER dmc_character_cur = {1, 	/*auto gate*/
										  1,	/*auto sleep*/	
										  0,	/*enlarge cs merge to cs x*/
										  1,	/*command queue mode*/
										  1,	/*row hit detected function*/
										  1};	/*if clock is always on*/	

typedef struct __sdram_cs_pin_table {
	int pin_index;
	u32 cs_size;
}SDRAM_CS_PIN_TABLE;

static SDRAM_CS_PIN_TABLE pin_table[] = {
	{23,0x800000},{24,0x1000000},{25,0x2000000},{26,0x4000000},
	{27,0x8000000},{28,0x10000000},{29,0x20000000},{30,0x30000000},
	{30,0x40000000},{30,0x60000000},{30,0x80000000}
};

extern LPDDR2_MR_INFO lpddr2_mr_info;
extern LPDDR3_MR_INFO lpddr3_mr_info;

extern int dmc_pin_init(void); 

#ifdef DDR_AUTO_DETECT
extern int lpddr2_update_bank_row_column_dw(u8 val, DRAM_JEDEC_INFO *info);
extern int lpddr2_update_cs1_size(u8 mr8, DRAM_JEDEC_INFO *info);
extern int lpddr3_update_bank_row_column_dw(u8 val, DRAM_JEDEC_INFO *info);
extern int lpddr3_update_cs1_size(u8 mr8, DRAM_JEDEC_INFO *info);
extern int lpddr2_update_jedec_info(u8 val, DRAM_JEDEC_INFO *info);
extern int lpddr3_update_jedec_info(u8 val, DRAM_JEDEC_INFO *info);
#endif

void reset_dmc_fifo(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	pdmc->dmc_dcfg0 |= 1<<16;
	dmc_sprd_delay(1);
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

int sdram_chip_whole_size(unsigned int *size)
{

	if (ddr_chip_cur.cs_num == 1)
	{
		*size = jedec_info_cs0.cs_size;
	}
	else if (ddr_chip_cur.cs_num == 2)
	{
		*size = jedec_info_cs0.cs_size + jedec_info_cs1.cs_size;
	}
	else
	{
		return -1;
	}
	return 0;
	
}


int sdram_cs_whole_size(int cs, unsigned int *size)
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
	u32 offset = addr - DDR_START_ADDR_PHY;
	u32 chip_size;
	u32 cs_size;
	u32 bank_size = sdram_bank_whole_size();
	u32 row_size = sdram_row_whole_size();
	u32 column_size = sdram_column_whole_size();

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

#define PIKE_REG_AON_APB_DPLL_CFG0 0x402e3004
#define PIKE_REG_AON_APB_DPLL_CFG1 0x402e3074



static u32 dpll_clk_get(void)
{
	u32 clk = 0;
	u32 nint, kint, refin, pnt = 0 ;
	u32 reg1, reg2, div_s, sdm_en, n;

	reg1 = REG32(PIKE_REG_AON_APB_DPLL_CFG0);
	reg2 = REG32(PIKE_REG_AON_APB_DPLL_CFG1);
	kint = reg2 >> 12;
	nint = reg2 & 0x3F;
	div_s = (reg2 >> 10) & 0x01;
	sdm_en = (reg2 >> 6) & 0x01;
	n = reg1 & 0x7ff;

	switch((reg1>>24)&0x3)
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
		if (((kint * refin ) & 0xFFFFF) >= 0x80000) {
			pnt = 1;
		}
		else {
			pnt = 0;
		}
		kint = ((kint * refin) >> 20) + pnt;
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

static void dpll_clk_set(u32 clk)
{
    volatile u32 reg1 = 0, reg2=0;
    u32 refin = 0;

    if(dpll_clk_get() == clk) {
        return;
    }   

    reg1 = REG32(PIKE_REG_AON_APB_DPLL_CFG0);
    reg2 = REG32(PIKE_REG_AON_APB_DPLL_CFG1);

    /* get refin value */
    refin = 26; 
    reg1 = u32_bits_set(reg1, 18, 2, 3); 

    if (0 == clk%refin)
    {   
        reg1 = u32_bits_set(reg1, 26, 1, 0); 
        reg1 = u32_bits_set(reg1, 0, 10, clk/refin);
		/*set div_s=0*/
		reg2 = u32_bits_set(reg1, 10, 1, 0); 
        REG32(PIKE_REG_AON_APB_DPLL_CFG0) = reg1;
		REG32(PIKE_REG_AON_APB_DPLL_CFG1) = reg2;
    }   
    else
    {   
    	/*set div_s=1*/
		reg2 = u32_bits_set(reg2, 10, 1, 1);
		/*set sdm_en=1*/
		reg2 = u32_bits_set(reg2, 6, 1, 1);
		/*set NINT*/
		reg2 = u32_bits_set(reg2, 0, 6, clk/refin);
		/*set KINT*/
		reg2 = u32_bits_set(reg2, 12, 20, (clk%refin)*1048576/refin);	
        
        REG32(PIKE_REG_AON_APB_DPLL_CFG1) = reg2;
    }   
    
    dmc_sprd_delay(100);
}

#define REG_AON_APB_EMC_CFG 0X402E0080
#define REG_AON_APB_RST1	0x402e000c


void sdram_clk_src_set(u32 clk)
{
	u32 regval;

	regval = REG32(REG_AON_APB_EMC_CFG);
	switch(clk)
	{
		case 200:
			dpll_clk_set(800);
			/*div = 4*/
            regval = u32_bits_set(regval,8,3,1);
            /*src index=3 dpll*/
            regval = u32_bits_set(regval,0,2,3);
			break;
		case 333:
			dpll_clk_set(666);
			/*div = 2*/
            regval = u32_bits_set(regval,8,3,0);
            /*src index=3 dpll*/
            regval = u32_bits_set(regval,0,2,3);
			break;
		case 384:
			/*div = 2*/
            regval = u32_bits_set(regval,8,3,0);
            /*src index=2 tdpll*/
            regval = u32_bits_set(regval,0,2,2);
			break;
		case 400:
			dpll_clk_set(800);
			/*div = 2*/
            regval = u32_bits_set(regval,8,3,0);
            /*src index=3 dpll*/
            regval = u32_bits_set(regval,0,2,3);
			break;
		default:
			break;
	}
	REG32(REG_AON_APB_EMC_CFG) = regval;
}

static void pub_phy_soft_reset(void)
{
	REG32(REG_AON_APB_RST1) |= 1<<4;
	dmc_sprd_delay(100);
	REG32(REG_AON_APB_RST1) &= ~(1<<4);
}

static void enable_pub_clk_autogate(void)
{
	REG32(0x402b00d0) |= 0x70;
	dmc_sprd_delay(10);
	REG32(0x402b00d0) &= 0xfffffff0;	
}


static void sdram_clk_init(void)
{
#if defined(CONFIG_CLK_PARA)
	u32 ddr_clk = (mcu_clk_para.ddr_freq)/1000000;
#else
	u32 ddr_clk = DDR_CLK ;
#endif
 	sdram_clk_src_set(ddr_clk);
	pub_phy_soft_reset();
	enable_pub_clk_autogate();
}

static int init_cfg1(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 val;
#if 0
	val = pdmc->dmc_cfg1;
	/*force to lpddr2/3*/
	val = u32_bits_set(val, 1, 2, 1);
	pdmc->dmc_cfg1 = val;
#endif
	return 0;
}


/*ddr type, column mode, data width, precharge pin are configed here*/
static int init_dcfg0(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 val;

	val = pdmc->dmc_dcfg0;

	
	/*column mode*/
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
	/*data width*/
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

	pdmc->dmc_dcfg0 = val;
	pdmc->dmc_dcfg0 |= (0x1 << 17);
	return 0;
}

/*cs pin are configed here*/
static int init_cfg0(void)
{
	int i;
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 val = pdmc->dmc_cfg0;
	u32 cs_size;
	int burstl;

	sdram_cs_whole_size(0, &cs_size);

	if (ddr_chip_cur.chip_type == DRAM_LPDDR2)
	{
		burstl = lpddr2_mr_info.bl;
	}
	else
	{
		burstl = lpddr3_mr_info.bl;
	}
	
	/*cs pin*/
	for(i=0; i<(sizeof(pin_table)/sizeof(SDRAM_CS_PIN_TABLE)); i++)
	{
		if (pin_table[i].cs_size == cs_size)
		{
			val = u32_bits_set(val, 0, 3, (pin_table[i].pin_index-23));			
			break;
		}		
	}
	if (i == (sizeof(pin_table)/sizeof(SDRAM_CS_PIN_TABLE)))
	{
		return -1;
	}

	/*burst length*/
	switch(burstl)
	{
		case 1:
			val = u32_bits_set(val, 5, 3, 0);
			break;
		case 2:
			val = u32_bits_set(val, 5, 3, 1);
			break;
		case 4:
			val = u32_bits_set(val, 5, 3, 2);
			break;
		case 8:
			val = u32_bits_set(val, 5, 3, 3);
			break;
		case 16:
			val = u32_bits_set(val, 5, 3, 4);
			break;
		default:
			return -1;
	}
	
	pdmc->dmc_cfg0 = val;
	return 0;	
}

int sdram_basic_init(void)
{
	if (0 != init_dcfg0())
	{
		return -1;
	}

	if (0 != init_cfg0())
	{
		return -1;
	}	

	if (0 != init_cfg1())
	{
		return -1;
	}

	return 0;
	
}

void sdram_timing_init(void)
{
	if (ddr_chip_cur.chip_type == DRAM_LPDDR2)
	{
		lpddr2_timing_init();
	}
	else if (ddr_chip_cur.chip_type == DRAM_LPDDR3)
	{
		lpddr3_timing_init();
	}
}

#define DLL_LOCK_TIME_COUNT 0x1000000

#define MAX_RETRY_TIMES	5

int dmc_dll_init(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 val;
	u32 val1, val2, val3, val4, val5;
	u32 tout;
	int retry_time = 0;

lockretry:
	retry_time++;
	tout = DLL_LOCK_TIME_COUNT;
	/*step 1 reset dsx DLL*/
	/*0x0300 - 32'h0702_8504*/
	pdmc->dmc_cfg_dll_ac |= 1<<8;
	pdmc->dmc_cfg_dll_ds0 |= 1<<8;
	pdmc->dmc_cfg_dll_ds1 |= 1<<8;
	pdmc->dmc_cfg_dll_ds2 |= 1<<8;
	pdmc->dmc_cfg_dll_ds3 |= 1<<8;

	pdmc->dmc_cfg_dll_ac = 0x07028404;
	pdmc->dmc_cfg_dll_ds0 = 0x07028404;
	pdmc->dmc_cfg_dll_ds1 = 0x07028404;
	pdmc->dmc_cfg_dll_ds2 = 0x07028404;
	pdmc->dmc_cfg_dll_ds3 = 0x07028404;
	
	do {
		val1 = pdmc->dmc_cfg_dll_ac;
		if (val1 & (1<<21))
		{
			/*clear error bit*/
			pdmc->dmc_cfg_dll_ac = val1 | (1<<20);
			if (retry_time < MAX_RETRY_TIMES)
			{
				goto lockretry;				
			}
			else
			{
				return -1;
			}
		}
		
		val2 = pdmc->dmc_cfg_dll_ds0;
		if (val2 & (1<<21))
		{
			/*clear error bit*/
			pdmc->dmc_cfg_dll_ds0 = val2 | (1<<20);
			if (retry_time < MAX_RETRY_TIMES)
			{
				goto lockretry;				
			}
			else
			{
				return -1;
			}
		}
		
		val3 = pdmc->dmc_cfg_dll_ds1;
		if (val3 & (1<<21))
		{
			/*clear error bit*/
			pdmc->dmc_cfg_dll_ds1 = val3 | (1<<20);
			if (retry_time < MAX_RETRY_TIMES)
			{
				goto lockretry;				
			}
			else
			{
				return -1;
			}
		}
		
		val4 = pdmc->dmc_cfg_dll_ds2;
		if (val4 & (1<<21))
		{
			/*clear error bit*/
			pdmc->dmc_cfg_dll_ds2 = val4 | (1<<20);
			if (retry_time < MAX_RETRY_TIMES)
			{
				goto lockretry;				
			}
			else
			{
				return -1;
			}
		}
		
		val5 = pdmc->dmc_cfg_dll_ds3;
		if (val5 & (1<<21))
		{
			/*clear error bit*/
			pdmc->dmc_cfg_dll_ds3 = val5 | (1<<20);
			if (retry_time < MAX_RETRY_TIMES)
			{
				goto lockretry;				
			}
			else
			{
				return -1;
			}
		}		

		if ((0 != (val1 & (1<<22))) && (0 != (val2 & (1<<22))) && (0 != (val3 & (1<<22))) && (0 != (val4 & (1<<22))) && (0 != (val5 & (1<<22))))
		{
			break;
		}
		tout--;
		
	}while(tout>0);

	if (0 == tout)
	{
		/*time out*/
		if (retry_time < MAX_RETRY_TIMES)
		{
			goto lockretry;				
		}
		else
		{
			return -1;
		}
	}

	
	/*step 4 decrease pd cont to 2*/
	/*0x0300	-	32'h0202_8404*/
	val = pdmc->dmc_cfg_dll_ac;
	val = u32_bits_set(val, 24, 8, PD_SELECT_AC);
	pdmc->dmc_cfg_dll_ac = val;

	val = pdmc->dmc_cfg_dll_ds0;
	val = u32_bits_set(val, 24, 8, PD_SELECT_DS0);
	pdmc->dmc_cfg_dll_ds0 = val;

	val = pdmc->dmc_cfg_dll_ds1;
	val = u32_bits_set(val, 24, 8, PD_SELECT_DS1);
	pdmc->dmc_cfg_dll_ds1 = val;

	val = pdmc->dmc_cfg_dll_ds2;
	val = u32_bits_set(val, 24, 8, PD_SELECT_DS2);
	pdmc->dmc_cfg_dll_ds2 = val;

	val = pdmc->dmc_cfg_dll_ds3;
	val = u32_bits_set(val, 24, 8, PD_SELECT_DS3);
	pdmc->dmc_cfg_dll_ds3 = val;

	tout = DLL_LOCK_TIME_COUNT;
	
	do {
		val1 = pdmc->dmc_cfg_dll_ac;
		if (val1 & (1<<21))
		{
			/*clear error bit*/
			pdmc->dmc_cfg_dll_ac = val1 | (1<<20);
			if (retry_time < MAX_RETRY_TIMES)
			{
				goto lockretry;				
			}
			else
			{
				return -1;
			}
		}
		
		val2 = pdmc->dmc_cfg_dll_ds0;
		if (val2 & (1<<21))
		{
			/*clear error bit*/
			pdmc->dmc_cfg_dll_ds0 = val2 | (1<<20);
			if (retry_time < MAX_RETRY_TIMES)
			{
				goto lockretry;				
			}
			else
			{
				return -1;
			}
		}
		
		val3 = pdmc->dmc_cfg_dll_ds1;
		if (val3 & (1<<21))
		{
			/*clear error bit*/
			pdmc->dmc_cfg_dll_ds1 = val3 | (1<<20);
			if (retry_time < MAX_RETRY_TIMES)
			{
				goto lockretry;				
			}
			else
			{
				return -1;
			}
		}
		
		val4 = pdmc->dmc_cfg_dll_ds2;
		if (val4 & (1<<21))
		{
			/*clear error bit*/
			pdmc->dmc_cfg_dll_ds2 = val4 | (1<<20);
			if (retry_time < MAX_RETRY_TIMES)
			{
				goto lockretry;				
			}
			else
			{
				return -1;
			}
		}
		
		val5 = pdmc->dmc_cfg_dll_ds3;
		if (val5 & (1<<21))
		{
			/*clear error bit*/
			pdmc->dmc_cfg_dll_ds3 = val5 | (1<<20);
			if (retry_time < MAX_RETRY_TIMES)
			{
				goto lockretry;				
			}
			else
			{
				return -1;
			}
		}		

		if ((0 != (val1 & (1<<22))) && (0 != (val2 & (1<<22))) && (0 != (val3 & (1<<22))) && (0 != (val4 & (1<<22))) && (0 != (val5 & (1<<22))))
		{
			break;
		}
		tout--;		
	}while(tout>0);

	if (0 == tout)
	{
		/*time out*/
		if (retry_time < MAX_RETRY_TIMES)
		{
			goto lockretry;				
		}
		else
		{
			return -1;
		}
	}	
	
	return 0;	
}

static void dmc_channel_auto_sleep_cfg(int flag)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	volatile unsigned int *preg = &(pdmc->ahbaxireg[0]);
	int i;

	for(i=0; i<MAX_CHANNEL_NUM-1; i++)
	{
		if(flag)
		{
			*(preg+2*i) |= 1<<7;
		}
		else
		{
			*(preg+2*i) &= ~(1<<7);
		}
	}
	*(preg+2*9) &= ~(1<<17);
	return ;
}

static void dmc_pub_pin_remap(void)
{
	u32 chipsize;

	if (-1 == sdram_chip_whole_size(&chipsize))
	{
		chipsize = 0x20000000;
	}

	/*enable DSP port remap*/
    REG32(0x300e3000) = 1<<9;
	switch(chipsize)
	{
		/*4G bit*/
		case 0x20000000:
			REG32(0x300e302c) = 0x98989898;
			break;
		/*6G bit*/
		case 0x30000000:
			REG32(0x300e302c) = 0x8a988a98;
			break;
		/*8G bit*/
		case 0x40000000:
			REG32(0x300e302c) = 0xba98ba98;
			break;
		/*12G bit*/
		case 0x60000000:
			REG32(0x300e302c) = 0x8edc8a98;
			break;
		/*16G bit*/
		case 0x80000000:
		default:
			REG32(0x300e302c) = 0x00000000;
			break;
	}    
}

static PORT_PARA port_para[18] = {
	/*port0*/	
	{
		0xa,
		0x40,
		0x40,
	},
	{
		0xa,
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
		0xc,
		0x20,
		0x20,
	},
	{
		0xc,
		0x0,
		0x0,
	},
	/*port3*/
	{
		0xa,
		0x80,
		0x80,
	},
	{
		0xa,
		0x0,
		0x0,
	},
	/*port4*/
	{
		0xe,
		0x8,
		0x8,
	},
	{
		0xe,
		0x0,
		0x0,
	},
	/*port5*/
	{
		0xe,
		0x10,
		0x10,
	},
	{
		0xe,
		0x0,
		0x0,
	},
	/*port6*/
	{
		0xe,
		0x80,
		0x80,
	},
	{
		0xe,
		0x0,
		0x0,
	},
	/*port7*/
	{
		0xe,
		0x8,
		0x8,
	},
	{
		0xe,
		0x0,
		0x0,
	},
	/*port8*/
	{
		0xe,
		0x10,
		0x10,
	},
	{
		0xe,
		0x0,
		0x0,
	},
};


void dmc_port_qos_init(u32 *addr,u32 timeout_pri_wr_ch, u32 timeout_thr_wr_ch, u32 timeout_thr_rd_ch)
{
	u32 regval;
	regval = *addr;
	regval = u32_bits_set(regval, 0, 4, timeout_pri_wr_ch);
	regval = u32_bits_set(regval, 16, 8, timeout_thr_wr_ch);
	regval = u32_bits_set(regval, 24, 8, timeout_thr_rd_ch);
    *addr = regval;
}

static void dmc_pub_qos_init(void)
{
	int i;
    PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
    u32 regval;
	/*port 0 mm/dcam/vsp*/
	/*port 1 GPU/gsp*/
	/*port 2 display*/
	/*port 3 CA7*/
	/*port 4 CPOW*/
	/*port 5 CP0 ARM*/
	/*port 6 AP matrix*/
	/*port 7 zip*/
	/*port 8 CP2*/
	for(i = 0;i < 9*2; i++)
	{
		dmc_port_qos_init(&pdmc->ahbaxireg[i],port_para[i].timeout_pri_wr_ch, port_para[i].timeout_thr_wr_ch, port_para[i].timeout_thr_rd_ch);
	} 

    /*port 9 DSP*/
   regval = pdmc->ahbaxireg[18];
	regval = u32_bits_set(regval, 0, 4, 0xf);
    pdmc->ahbaxireg[18] = regval;
	regval = pdmc->ahbaxireg[19];
	regval = u32_bits_set(regval, 0, 10, 0x0);
	regval = u32_bits_set(regval, 15, 1, 0x0);
	regval = u32_bits_set(regval, 16, 8, 0x0);
    pdmc->ahbaxireg[19] = regval;

	/*band width schedule*/
    regval = pdmc->dmc_cfg0;
    regval = u32_bits_set(regval, 16, 11, 0x190);
    regval = u32_bits_set(regval, 27, 1, 0);
    pdmc->dmc_cfg0 = regval;

	regval = REG32(0x300e3100);
	regval = u32_bits_set(regval, 0, 9, 0);
	regval = u32_bits_set(regval, 16, 9, 0x3);
    REG32(0x300e3100) = regval;

	regval = REG32(0x300e3120);
	regval = u32_bits_set(regval, 0, 20, 0x88888);
    REG32(0x300e3120) = regval;

	regval = REG32(0x300e3150);
	regval = u32_bits_set(regval, 0, 20, 0x88888);
    REG32(0x300e3150) = regval;	

	regval = REG32(0x300e3124);
    regval = u32_bits_set(regval, 0, 4, 0x2);
    regval = u32_bits_set(regval, 16, 4, 0);
    REG32(0x300e3124) = regval;	

	regval = REG32(0x300e3154);
    regval = u32_bits_set(regval, 0, 4, 0x2);
    regval = u32_bits_set(regval, 16, 4, 0);
    REG32(0x300e3154) = regval;	
    

    REG32(0x300e3110) = 0xd6be4a00;
    REG32(0x300e3114) = 0x0000000c;
    REG32(0x300e3118) = 0xd6be4a00;
    REG32(0x300e311c) = 0x0000000c; 
}



int dmc_lowpower_cfg(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 val = pdmc->dmc_cfg0;

	
	/*auto gate*/
	if (dmc_character_cur.auto_gate == 0)
	{
		val = u32_bits_set(val, 9, 1, 0);
	}
	else
	{
		val = u32_bits_set(val, 9, 1, 1);
	}

	/*auto sleep*/
	if (dmc_character_cur.auto_sleep== 0)
	{
		val = u32_bits_set(val, 8, 1, 0);
		dmc_channel_auto_sleep_cfg(0);
	}
	else
	{
		val = u32_bits_set(val, 8, 1, 1);
		dmc_channel_auto_sleep_cfg(1);
	}
	pdmc->dmc_cfg0 = val;
	
	val = pdmc->dmc_lpcfg1;
	/*auto power down, auto clock stop*/
	val = u32_bits_set(val, 0, 2, 3);
	pdmc->dmc_lpcfg1 = val;

#ifdef DFS_SUPPORT
	/*auto dfs enable*/
	val = pdmc->dmc_lpcfg3;
	val = u32_bits_set(val, 0, 3, 3);
	pdmc->dmc_lpcfg3 = val;
#endif
	 
	return 0;
}

static void dmc_cmd_queue_init(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	if (dmc_character_cur.cmd_queue_m)
	{
		pdmc->dmc_cfg0 |= 1<<4;
	}
	else
	{
		pdmc->dmc_cfg0 &= ~(1<<4);
	}
}

int sdram_final_init(void)
{
	if (ddr_chip_cur.chip_type == DRAM_LPDDR2)
	{
		lpddr2_final_init();
	}
	else 
	{
		lpddr3_final_init();
	}
	return 0;
}

int sdram_ac_train_reset(void)
{
	if (ddr_chip_cur.chip_type == DRAM_LPDDR2)
	{
		return lpddr2_ac_train_reset();
	}
	else
	{
		return lpddr3_ac_train_reset();
	}
}

#ifdef DDR_AUTO_DETECT
void sdram_init_blindly(void)
{
	sdram_basic_init();
	sdram_timing_init();
	dmc_dll_init();
	sdram_final_init();
}

int update_cs_num(void)
{
	int cs_num = 0;
	int i;
	u8 val;

	for(i=0; i<2; i++)
	{
		dmc_mrr(i, 0, &val, 10000);
		if ((0 != val) && (0xff != val))
		{
			cs_num++;
		}
	}
	if(cs_num<1)
	{
		return -1;
	}
	ddr_chip_cur.cs_num = cs_num;
	return 0;
}

int update_chip_type(u8 mr8)
{
	if ((mr8&0x3) == 0x3)
	{
		ddr_chip_cur.chip_type = DRAM_LPDDR3;
	}
	else if ((mr8&0x3)==0 || (mr8&0x3) == 1)
	{
		ddr_chip_cur.chip_type = DRAM_LPDDR2;
	}
	else
	{
		return -1;
	}
	return 0;
}

int update_jedec_info(u8 mr8, int cs_index)
{	
	DRAM_JEDEC_INFO *info;

	if (0 == cs_index)
	{
		info = &jedec_info_cs0;
	}
	else if (1 == cs_index)
	{
		info = &jedec_info_cs1;
	}
	else
	{
		return -1;
	}
		
	if (ddr_chip_cur.chip_type == DRAM_LPDDR2)
	{
		
		if (0 != lpddr2_update_jedec_info(mr8, info))
		{
			return -2;
		}
		
	}
	else if (ddr_chip_cur.chip_type == DRAM_LPDDR3)
	{
		if (0 != lpddr3_update_jedec_info(mr8, info))
		{
			return -3;
		}
	}
	else
	{
		return -4;
	}
	return 0;
}


/*According to constraintion all ddr chip's cs width must be 32 bits.
  So if the information we read fraom MR register is 16 bits width it
  must be two die in one cs*/
int correct_parameter_by_product_constraintion(int cs)
{
	DRAM_JEDEC_INFO *info;

	if (0 == cs)
	{
		info = &jedec_info_cs0;
	}
	else if (1 == cs)
	{
		info = &jedec_info_cs1;
	}
	else
	{
		return -1;
	}
	
	if (info->dw == 16)
	{
		info->dw = 32;
		info->cs_size *= 2;
	}
	return 0;
}

int sdram_auto_detect(void)
{
	u8 mr8;
	
	sdram_init_blindly();
	update_cs_num();
	if (0 != dmc_mrr(0, 8, &mr8, 10000))
	{
		return -1;
	}		
	update_chip_type(mr8);
	update_jedec_info(mr8, 0);
	correct_parameter_by_product_constraintion(0);
	if (2 == ddr_chip_cur.cs_num)
	{
		if (0 != dmc_mrr(1, 8, &mr8, 10000))
		{
			return -1;
		}
		update_jedec_info(mr8, 1);
		correct_parameter_by_product_constraintion(0);
		if (jedec_info_cs0.cs_size == jedec_info_cs1.cs_size)
		{
			ddr_chip_cur.unsymmetry = 0;
		}
		else
		{
			if ((jedec_info_cs0.cs_size == 0x20000000) && (jedec_info_cs1.cs_size == 0x10000000))
			{				
				if (jedec_info_cs0.dw == 32)
				{
					unsymmetry_mode_cur = DDR_6Gb_10_COL_MODE;
				}
				else if (jedec_info_cs0.dw == 16)
				{
					unsymmetry_mode_cur = DDR_6Gb_11_COL_MODE;
				}
				else 
				{
					return -1;
				}
				ddr_chip_cur.unsymmetry = 1;
			}
			else if ((jedec_info_cs0.cs_size == 0x40000000) && (jedec_info_cs1.cs_size == 0x20000000))
			{
				unsymmetry_mode_cur = DDR_12Gb_MODE;
				ddr_chip_cur.unsymmetry = 1;
			}
			else
			{
				return -1;
			}
		}
	}
	else
	{
		ddr_chip_cur.unsymmetry = 0;
	}
	return 0;
}

#endif

#define SW_WAKEUP
#define DDR_PHY_RET_CFG	0x402b0130
#define DDR_OP_MODE_CFG	0x402b012c
#define DDR_CHN_SLEEP_CTRL0	0x402b00f8
#define DDR_PUB_LP_CFG	0x402b006c
#define DDR_PHY_LP_CFG	0x402b0144


typedef struct
{
	volatile unsigned int magic_head;
	volatile unsigned int ap_access_pub_address;
	volatile unsigned int cp0_arm_access_pub_address;
	volatile unsigned int cp0_dsp_access_pub_address;
	volatile unsigned int cp2_access_pub_address;
	volatile unsigned int pub_access_able;
	volatile unsigned int sw_reinit_enable;
}ddr_pub_dp_reg_ctrl,*ddr_pub_dp_reg_ctrl_p;

ddr_pub_dp_reg_ctrl lp_cfg=
{
	0x445d4362,		//magic data head
	0x3000021c,		//ap access pub address
	0x0100021c,		//cp0 arm access pub address
	0x2100021c,		//cp0 dsp access pub address
	0x0100021c,		//pub access able
	0x5a5a5a5a,		//pub access flag
	#ifdef SW_WAKEUP
	0x00000001,		//sw reinit flag
	#else
	0x00000000,		//hw reinit flag
	#endif
};

static void save_ddr_ctl_reg_into_iram()
{
	ddr_pub_dp_reg_ctrl_p pub_dp_reg_ctrl_p = (ddr_pub_dp_reg_ctrl_p)0x50002400;
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	*pub_dp_reg_ctrl_p = lp_cfg;
	pdmc->dmc_bist[7] = 0x5a5a5a5a;
}

extern int sipi_bist_simple_test(int cs);

void dmc_deep_sleep_prepare(void)
{
	u32 val;	
	u32 pub_val,phy_val;
	/*clear hardware retention setting*/
	REG32(DDR_PHY_RET_CFG) &= ~1;

	/*set hardware auto asert CKE enable*/
	val = REG32(DDR_OP_MODE_CFG);
	pub_val = REG32(DDR_PUB_LP_CFG);
	phy_val = REG32(DDR_PHY_LP_CFG);
#ifdef SW_WAKEUP
	val = u32_bits_set(val, 24, 3, 5);
	pub_val = u32_bits_set(pub_val, 24, 2, 1);
#else
	val = u32_bits_set(val, 24, 3, 2);
	//pub_val = u32_bits_set(pub_val, 24, 2, 1);
	pub_val = u32_bits_set(pub_val, 24, 2, 0);
#endif
	phy_val = u32_bits_set(phy_val, 24, 2, 1);

	REG32(DDR_OP_MODE_CFG) = val;
	REG32(DDR_PUB_LP_CFG) = pub_val;
	REG32(DDR_PHY_LP_CFG) = phy_val;

	/*set DMC IO and channel low power enable*/
	val = REG32(DDR_CHN_SLEEP_CTRL0);
	val = u32_bits_set(val, 30, 1, 1);
	val = u32_bits_set(val, 16, 10, 0x3ff);
	REG32(DDR_CHN_SLEEP_CTRL0) = val;
	return ;
}

#if 0
void mem_rw_test(void)
{
	int i;
	volatile u32 *pmem = 0x80000000;

	while(1)
	{
		pmem = 0x80000000;
		dmc_print_str("mem rw test:\r\n");
		for(i=0; i<0x4000000; i++)
		{
			*(pmem) = i;
			if (*pmem != i)
			{
				dmc_print_str("read write error\r\n");
			}
			pmem++;
		}
	}
}
#endif

void save_param_for_uboot(void)
{
	u32 total_size;
	mem_cs_info_t *pMem = (mem_cs_info_t *)DDR_DFS_VAL_BASE;
	pMem->cs_number = ddr_chip_cur.cs_num;
	pMem->cs0_size = jedec_info_cs0.cs_size;
	pMem->cs1_size = jedec_info_cs1.cs_size;

	/*reserve 1M room*/
	total_size = pMem->cs0_size + pMem->cs1_size;
	if (0x80000000 == total_size)
	{
		pMem->cs1_size -= SYS_MAP_RESERVE_SIZE + BIST_RESERVE_SIZE;
	}
	else
	{
		pMem->cs1_size -= BIST_RESERVE_SIZE;
	}
#ifdef DDR_SIZE_FIXED_ON
	pMem->cs_number = ddr_chip_cur.cs_num;
	total_size = pMem->cs0_size + pMem->cs1_size;
	pMem->cs0_size = DDR_FIXED_SIZE;
	pMem->cs1_size = 0;

	if (total_size < DDR_FIXED_SIZE)
	{
		pMem->cs0_size = total_size;
	}
#endif
}

int sdram_init(void)
{
	u32 regval;
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	char strbuf[64];

	//dmc_print_str("DDR init begin...\r\n");
	
	dmc_pub_pin_remap();
	if (0 != dmc_pin_init())
	{
		dmc_print_str("error:-1\r\n");
		return -1;
	}
	sdram_clk_init();
#ifdef DDR_AUTO_DETECT
	if (0 != sdram_auto_detect())
	{
		dmc_print_str("error:-2\r\n");
		return -2;
	}
	reset_dmc_fifo();
#endif
	if (0 != sdram_basic_init())
	{
		dmc_print_str("error:-3\r\n");
		return -3;
	}
	sdram_timing_init();
	if (0 != dmc_dll_init())
	{
		dmc_print_str("error:-4\r\n");
		return -4;
	}
	if (0 != sdram_final_init())
	{
		dmc_print_str("error:-5\r\n");
		return -5;
	}	
#if 1
	if(0 != ddr_scan_online_sprd_r1p0())
	{
		dmc_print_str("error:-6\r\n");
		return -6;
	}
	dmc_bist_disable();
#else
	ddr_scan_sprd_r1p0();
	while(1);	
#endif

	dmc_lowpower_cfg();
	dmc_pub_qos_init();

	dmc_cmd_queue_init();
	dmc_deep_sleep_prepare();

	//mem_rw_test();
#if 0
	while(1);
#endif

	save_param_for_uboot();

	//dmc_print_str("DDR init OK\r\n");
	save_ddr_ctl_reg_into_iram();
	//while(1);
	return 0;
}

