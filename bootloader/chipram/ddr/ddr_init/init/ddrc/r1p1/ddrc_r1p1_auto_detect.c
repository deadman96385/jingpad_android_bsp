
//#include <sci_types.h>
//#include <asm/arch/clk_para_config.h>
//#include <asm/arch/sprd_reg.h>
//#include <asm/arch/sprd_chipram_env.h>

#include "ddrc_r1p1.h"
#include "ddrc_r1p1_phy.h"
#include "ddrc_r1p1_common.h"
#include "ddrc_r1p1_auto_detect.h"
#include <asm/arch-roc1/sprd_reg.h>

extern DRAM_CHIP_INFO ddr_chip_cur;
extern DRAM_JEDEC_INFO jedec_info_cs[2];
extern DDR_UNSYMMETRY_MODE unsymmetry_mode_cur;
uint32 hynix_misc_mode = 0;
#define VENDOR_HYNIX	6
#ifdef DDR_AUTO_DETECT

struct ddr_detect_info detect_info_cs[2];
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
	{0x40000000,	 8,	8,	17,	10},
	/*12Gb*/
	{0x60000000,	 8,	8,	18,	10},
	{0x60000000,	16,	8,	17,	10},
	/*16Gb*/
	{0x80000000,	 8,	8,	18,	10},
	{0x80000000,	16,	8,	17,	10},
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
		dmc_mrr(cs, 5, &mr5, 10000);
		dmc_mrr(cs, 6, &mr6, 10000);
		dmc_mrr(cs, 7, &mr7, 10000);
		if (((mr5) == (mr6)) && ((mr5)==(mr7)))
		{
			ddrc_print_err("mrr same\r\n");
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
			ddr_chip_cur.chip_type = DRAM_LPDDR4X;
		}
		else if(mr8_type == S16_SDRAM_LP4X || mr8_type == S8_SDRAM_LP4X)
		{
			ddr_chip_cur.chip_type = DRAM_LPDDR4X;
		}
		else if(mr8_type == S16_SDRAM_LP4Y)
		{
			ddr_chip_cur.chip_type = DRAM_LPDDR4Y;
		}
		else
		{
			ddrc_print_err("mr8_type\r\n");
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
			ddrc_print_err("mr8_width\r\n");
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
			ddrc_print_err("mr8_density\r\n");
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

extern u32 g_mr5_8[DDR_RANK_NUM_MAX];
uint32 lpddr_size_auto_detect(void)
{
	uint32 cs_mr8[DDR_RANK_NUM_MAX];
	uint32 cs_mr5[DDR_RANK_NUM_MAX];
	uint32 cs_num = 0;
	uint32 i;
	uint32 ret = TRUE;
	char char_8[9] = {0};
	uint32  org_standard_num=0;
	u32 val;
	DRAM_JEDEC_INFO *cs0_info, *cs1_info;
	org_standard_num = sizeof(org_standard_lp4)/sizeof(org_standard_lp4[0]);
	if(((DRAM_LPDDR4 == ddr_chip_cur.chip_type) || (DRAM_LPDDR4X == ddr_chip_cur.chip_type) || (DRAM_LPDDR4Y == ddr_chip_cur.chip_type)))
	{
		LPDDR_JEDEC_ORIGINIZE *org_standard_array=org_standard_lp4;
		for(i = 0; i < DDR_RANK_NUM_MAX; i++)
		{
			ret = TRUE;
			ddrc_print_info("CS");
			ddrc_print_info(itoa_simple(i, char_8, 10));
			ddrc_print_info(" mr8 read.\r\n");
			ret = dmc_mrr(i, 8, &(cs_mr8[i]), 10000);
			ddrc_print_info("mr8: 0x");
			ddrc_print_info(itoa_simple(cs_mr8[i], char_8, 16));
			ddrc_print_info("\r\n");
			g_mr5_8[i] = (cs_mr8[i] & 0xff) << 24;

			ret = dmc_mrr(i, 5, &(cs_mr5[i]), 10000);
			ddrc_print_info("mr5: 0x");
			ddrc_print_info(itoa_simple(cs_mr5[i], char_8, 16));
			ddrc_print_info("\r\n");
			g_mr5_8[i] |= cs_mr5[i] & 0xff;
			ret = dmc_mrr(i, 6, &val, 10000);
			g_mr5_8[i] |= (val & 0xff) << 8;

			ret = dmc_mrr(i, 7, &val, 10000);
			g_mr5_8[i] |= (val & 0xff) << 16;

			if (FALSE == ret)
			{
				ddrc_print_err("mr8 fail\r\n");
				while(1);
			}

			ret = mr8_to_detect_info(i, cs_mr8[i], &(detect_info_cs[i]));
			if(FALSE == ret)
			{
				jedec_info_cs[i].cs_size = 0;
				ddrc_print_err("auto detect fail\r\n");
			}

			jedec_info_cs[i].cs_size = detect_info_cs[i].mem_size;
			jedec_info_cs[i].dw = detect_info_cs[i].mem_width;

			if(FALSE == update_row_column(&jedec_info_cs[i], org_standard_array, org_standard_num))
			{
				ddrc_print_err("row_column fail\r\n");
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
		if ((cs_mr5[0] & 0xff) == VENDOR_HYNIX) {
			hynix_misc_mode = 1;
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
#ifdef DDR_USE_DEFAULT_TYPE

        ddr_chip_cur.pinmux_case = ddr_type_case[0].ddr_pinmux_c;
        ddr_chip_cur.chip_type = ddr_type_case[0].ddr_type;
#else
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
#endif
}

#ifdef GPIO_DETECT_DRAM_TYPE
inline void ddr_type_detect_gpio(void)
{
	uint32 gpio_n0_val;

	reg_bits_set(REG_AON_APB_APB_EB1, 1, 1, 1);
	sprd_gpio_request(DRAM_TYPE_DETECT_GPIO_N0);
	sprd_gpio_direction_input(DRAM_TYPE_DETECT_GPIO_N0);
	gpio_n0_val = sprd_gpio_get(DRAM_TYPE_DETECT_GPIO_N0);
	if(gpio_n0_val == 1) // 1 : emcp ,0 :discrete
		ddr_chip_cur.pinmux_case = LP4_PINMUX_CASE0;
	else
		ddr_chip_cur.pinmux_case = LP4_PINMUX_CASE1;

}
#endif
#endif


/*different devices may support different highest frequency*/
#ifdef DDR_FREQ_AUTO_SEL
MR_AUTO_FREQ_SEL mr_freq_detect[] = {
	/*samsung KMDH6001DA-B422*/
	{
		{
			{0x1, 0x6, 0x10, 0x12},
			{0, 0, 0, 0}
		},
		2,
		1866
	},
	/*spectek SUVJ9K9ZZAD9DQKSM*/
	{
		{
			{0xFF, 0x4, 0x10, 0x10},
			{0, 0, 0, 0}
		},
		2,
		1536
	},
	/*hynix H9HQ16AECMMDAR-KMM*/
	{
		{
			{0x6, 0x4, 0, 0x11},
			{0, 0, 0, 0}
		},
		2,
		1866
	}
};
u32 max_ddr_clk_sel = 1866;

uint32 mr_freq_select(u32 *ddr_clk)
{
	u32 mr5_val = 0,mr6_val = 0,mr7_val = 0,mr8_val=0;	//roc1 str need word align
	u8 hex_value[16] = {0};
	int size = sizeof(mr_freq_detect)/sizeof(mr_freq_detect[0]);
	int i = 0;

	*ddr_clk = max_ddr_clk_sel;

	dmc_mrr(0, 5, &mr5_val, 10000);
	dmc_mrr(0, 6, &mr6_val, 10000);
	dmc_mrr(0, 7, &mr7_val, 10000);
	dmc_mrr(0, 8, &mr8_val, 10000);
	mr5_val &= 0xFF;
	mr6_val &= 0xFF;
	mr7_val &= 0xFF;
	mr8_val &= 0xFF;
#if 0
	ddrc_print_info("mr5: 0x");
	ddrc_print_info(itoa_simple(mr5_val, hex_value, 16));
	ddrc_print_info("\n");
	ddrc_print_info("mr6: 0x");
	ddrc_print_info(itoa_simple(mr6_val, hex_value, 16));
	ddrc_print_info("\n");
	ddrc_print_info("mr7: 0x");
	ddrc_print_info(itoa_simple(mr7_val, hex_value, 16));
	ddrc_print_info("\n");
	ddrc_print_info("mr8: 0x");
	ddrc_print_info(itoa_simple(mr8_val, hex_value, 16));
	ddrc_print_info("\n");
#endif
	for(i = 0; i < size; i++)
	{
		if((mr_freq_detect[i].mr_devices_info[0].reg_val_mr5 == mr5_val) &&
		(mr_freq_detect[i].mr_devices_info[0].reg_val_mr6 == mr6_val) &&
		(mr_freq_detect[i].mr_devices_info[0].reg_val_mr7 == mr7_val) &&
		(mr_freq_detect[i].mr_devices_info[0].reg_val_mr8 == mr8_val))
		{
			*ddr_clk = mr_freq_detect[i].ddr_clk_sel;
			max_ddr_clk_sel = mr_freq_detect[i].ddr_clk_sel;
			return TRUE;
		}
	}
	return FALSE;
}
#endif
