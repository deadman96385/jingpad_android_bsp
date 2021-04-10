
//#include <sci_types.h>
//#include <asm/arch/clk_para_config.h>
//#include <asm/arch/sprd_reg.h>
//#include <asm/arch/sprd_chipram_env.h>

#include "ddrc_r1p1.h"
#include "ddrc_r1p1_phy.h"
#include "ddrc_r1p1_common.h"
#include "ddrc_r1p1_auto_detect.h"

extern DRAM_CHIP_INFO ddr_chip_cur;
extern DRAM_JEDEC_INFO jedec_info_cs[2];
extern DDR_UNSYMMETRY_MODE unsymmetry_mode_cur;
#ifdef DDR_AUTO_DETECT

struct ddr_detect_info detect_info_cs[2];
#ifdef DDR_FREQ_AUTO_SEL
MR_AUTO_FREQ_SEL mr_freq_detect[] = {
	{
		DDR_REG_VAL_MR5_INDEX0,
		DDR_REG_VAL_MR6_INDEX0,
		DDR_REG_VAL_MR7_INDEX0,
		DDR_REG_VAL_MR8_INDEX0,
		DDR_CS_NUM_VAL_INDEX0,
		MR_DDR_CLK_SEL_INDEX0
	},
	{
		DDR_REG_VAL_MR5_INDEX1,
		DDR_REG_VAL_MR6_INDEX1,
		DDR_REG_VAL_MR7_INDEX1,
		DDR_REG_VAL_MR8_INDEX0,
		DDR_CS_NUM_VAL_INDEX0,
		MR_DDR_CLK_SEL_INDEX1
	}
};
#endif
LPDDR_JEDEC_ORIGINIZE org_standard_lp4[16] = {
	/*2Gb*/
	{0x10000000,	16,	8,	14,	10},
	/*3Gb*/
	{0x18000000,	16,	8,	15,	10},
	/*4Gb*/
	{0x20000000,	 8,	8,	16,	10},
	{0x20000000,	16,	8,	15,	10},
	/*6Gb*/
	{0x30000000,	16,	8,	16,	10},
	/*8Gb*/
	{0x40000000,	16,	8,	16,	10},
};

struct MR8_size_info LPDDR4_mr8_size[] = {
	{LP4_MR8_SIZE_2Gb ,0x10000000},
	{LP4_MR8_SIZE_3Gb ,0x18000000},
	{LP4_MR8_SIZE_4Gb ,0x20000000},
	{LP4_MR8_SIZE_6Gb ,0x30000000},
	{LP4_MR8_SIZE_8Gb ,0x40000000},
	{LP4_MR8_SIZE_12Gb,0x60000000},
	{LP4_MR8_SIZE_16Gb,0x80000000},
};

uint32 mr8_to_detect_info(uint32 cs, uint32 mr8_value,struct ddr_detect_info *detect_info)
{

	uint32 mr8_type;
	uint32 mr8_size;
	uint32 mr8_width;
	uint32 mr5=0,mr6=0,mr7=0;
	uint32 i;
	uint32 ret = TRUE;
	uint32 density_n = sizeof(LPDDR4_mr8_size)/sizeof(LPDDR4_mr8_size[0]);

	//check csx valid
	if(mr8_value == 0)
	{
		dmc_mrr(cs, 8, &mr5, 10000);
		dmc_mrr(cs, 8, &mr6, 10000);
		dmc_mrr(cs, 8, &mr7, 10000);
		if (((mr5) == (mr6)) && ((mr5)==(mr7)))
		{
			ddrc_print_err("mrr return same vaule!\r\n");
			ret = ret && FALSE;
		}
	}
	mr8_type = (mr8_value & 0x3)>>0;
	mr8_size = (mr8_value & 0x3c)>>2;
	mr8_width = (mr8_value & 0xc0)>>6;

	if((DRAM_LPDDR4 == ddr_chip_cur.chip_type) || (DRAM_LPDDR4X == ddr_chip_cur.chip_type) || (DRAM_LPDDR4Y == ddr_chip_cur.chip_type))
	{
		if(mr8_type == S16_SDRAM_LP4)
		{
			ddr_chip_cur.chip_type = DRAM_LPDDR4;
		}
		else if(mr8_type == S16_SDRAM_LP4X)
		{
			ddr_chip_cur.chip_type = DRAM_LPDDR4X;
		}
		else if(mr8_type == S16_SDRAM_LP4Y)
		{
			ddr_chip_cur.chip_type = DRAM_LPDDR4Y;
		}
		else
		{
			ddrc_print_err("mr8_type invalid!\r\n");
			ret = ret && FALSE;
		}
		if(mr8_width == LP4_WIDTH_X16)
		{
			detect_info->mem_width = 16;
		}
		else if(mr8_width == LP4_WIDTH_X8)
		{
			detect_info->mem_width = 8;
		}
		else
		{
			ddrc_print_err("mr8_width invalid!\r\n");
			ret = ret && FALSE;
		}
		for(i=0; i<density_n; i++)
		{
			if(mr8_size == LPDDR4_mr8_size[i].mr8_size)
			{
				detect_info->mem_size = LPDDR4_mr8_size[i].mem_size;
				detect_info->bank = 8;
				break;
			}
		}
		if(i == density_n)
		{
			ddrc_print_err("mr8_density invalid!\r\n");
			ret = ret && FALSE;
		}
	}
	return ret;
}

uint32 update_row_column(DRAM_JEDEC_INFO *info, LPDDR_JEDEC_ORIGINIZE *org_standard_ptr, int org_standard_num)
{
	uint32 i;
	for(i = 0; i < org_standard_num; i++)
	{
		if ((info->cs_size == org_standard_ptr[i].cs_size) &&
			(info->dw == org_standard_ptr[i].dw) &&
			(info->bank == org_standard_ptr[i].bank))
		{
			info->row = org_standard_ptr[i].row;
			info->column= org_standard_ptr[i].column;
			return TRUE;
		}
	}
	return FALSE;
}


uint32 lpddr_size_auto_detect(void)
{
	uint32 cs_mr8[DDR_RANK_NUM_MAX];
	uint32 cs_num = 0;
	uint32 i;
	uint32 ret = TRUE;
	char char_8[9] = {0};
	uint32  org_standard_num=0;
	DRAM_JEDEC_INFO *cs0_info, *cs1_info;
	if(((DRAM_LPDDR4 == ddr_chip_cur.chip_type) || (DRAM_LPDDR4X == ddr_chip_cur.chip_type) || (DRAM_LPDDR4Y == ddr_chip_cur.chip_type)))
	{
		LPDDR_JEDEC_ORIGINIZE *org_standard_array=org_standard_lp4;
		for(i = 0; i < DDR_RANK_NUM_MAX; i++)
		{
			ret = TRUE;
			ddrc_print_info("CS");
			ddrc_print_info(itoa_simple(i, char_8, 10));
			ddrc_print_info(" mr8 read.\r\n");
			ret = dmc_mrr(1, 8, &cs_mr8+i, 10000);
			ddrc_print_info("mr8: 0x");
			ddrc_print_info(itoa_simple(cs_mr8[i], char_8, 16));
			ddrc_print_info("\r\n");
			if (FALSE == ret)
			{
				ddrc_print_err("mr8 read fail\r\n");
				while(1);
			}

			ret = mr8_to_detect_info(1, cs_mr8[i], &detect_info_cs+i);
			if(FALSE == ret)
			{
				jedec_info_cs[i].cs_size = 0;
				ddrc_print_err("ddr auto detect fail!\r\n");
			}

			jedec_info_cs[i].cs_size = detect_info_cs[i].mem_size;
			jedec_info_cs[i].dw = detect_info_cs[i].mem_width;

			if(FALSE == update_row_column(jedec_info_cs + i, org_standard_array, org_standard_num))
			{
				ddrc_print_err("ddr update_row_column failed\r\n");
				while(1);
			}

			if(detect_info_cs[i].mem_width == 8)
			{
				/*update cs1 ddr info*/
				jedec_info_cs[i].cs_size = detect_info_cs[i].mem_size * 4;
			}
			else
			{
				/*update cs1 ddr info*/
				jedec_info_cs[i].cs_size = detect_info_cs[i].mem_size * 2;
			}
			if(ret)
			{
				cs_num++;
			}
		}
	}
	/*update ddr cs number*/
	ddr_chip_cur.cs_num = cs_num;
	return 0;
}


DDR_TYPE_ADC_DETECT ddr_type_case[4] =
{
/***v_min	v_max	ddr_type	pinmux_type	***/
	{1050,	1200,	LPDDR4X,	LP4_PINMUX_CASE0},
	{880,	1000,	LPDDR4,		LP4_PINMUX_CASE1},
	{730,	830,	LPDDR4X,	LP4_PINMUX_CASE1},
	{560,	640,	LPDDR4,		LP4_PINMUX_CASE0}
};


void ddr_type_detect(void)
{
	int v_value = 0;
	char case_n = sizeof(ddr_type_case) / sizeof(ddr_type_case[0]);
	char pinmux_case_detect = 0;
	char i = 0;
	sc27xx_adc_current_mode_vol(6, 0, 2000, &v_value);
	for(i=0; i<case_n; i++)
	{
		if((ddr_type_case[i].v_min < v_value) && (v_value < ddr_type_case[i].v_max))
		{
			ddr_chip_cur.pinmux_case = ddr_type_case[i].ddr_pinmux_c;
			ddr_chip_cur.chip_type = ddr_type_case[i].ddr_type;
			break;
		}
	}
	if(case_n == i)
	{
		ddrc_print_err("ddr_type_detect failed\r\n");
		while(1);
	}
}

#ifdef DDR_FREQ_AUTO_SEL
int mr_freq_select(uint32 *ddr_clk)
{
	char mr5_val = 0,mr6_val = 0,mr7_val = 0,mr8_val=0;
	char hex_value[9] = {0};
	uint32 size = sizeof(mr_freq_detect)/sizeof(mr_freq_detect[0]);
	uint32 i;
	dmc_mrr(0, 5, &mr5_val, 10000);
	dmc_mrr(0, 6, &mr6_val, 10000);
	dmc_mrr(0, 7, &mr7_val, 10000);
	dmc_mrr(0, 8, &mr8_val, 10000);
#if 1
	ddrc_print_info("mr5: 0x");
	ddrc_print_info(itoa_simple(mr5_val, hex_value, 16));
	ddrc_print_info("\r\n");
	ddrc_print_info("mr6: 0x");
	ddrc_print_info(itoa_simple(mr6_val, hex_value, 16));
	ddrc_print_info("\r\n");
	ddrc_print_info("mr7: 0x");
	ddrc_print_info(itoa_simple(mr7_val, hex_value, 16));
	ddrc_print_info("\r\n");
	ddrc_print_info("mr8: 0x");
	ddrc_print_info(itoa_simple(mr8_val, hex_value, 16));
	ddrc_print_info("\r\n");
#endif
	for(i = 0; i < size; i++)
	{
		 if((mr_freq_detect[i].reg_val_mr5 == mr5_val) &&
		    (mr_freq_detect[i].reg_val_mr6 == mr6_val) &&
		    (mr_freq_detect[i].reg_val_mr7 == mr7_val) &&
		    (mr_freq_detect[i].reg_val_mr8 == mr8_val) &&
		    (ddr_chip_cur.cs_num == mr_freq_detect[i].ddr_cs_num))
		{
			*ddr_clk = mr_freq_detect[i].ddr_clk_sel;
			return 0;
		}
	}
	return -1;
}
#endif

#endif

