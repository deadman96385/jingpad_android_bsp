#include <sci_types.h>
#include <asm/arch/clk_para_config.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_chipram_env.h>

#include "ddrc_r1p0.h"
#include "ddrc_r1p0_phy.h"
#include "ddrc_r1p0_common.h"
#include "ddrc_r1p0_auto_dected.h"

extern DRAM_CHIP_INFO ddr_chip_cur;
extern DDR_UNSYMMETRY_MODE unsymmetry_mode_cur;
#ifdef DDR_AUTO_DETECT

struct ddr_detect_info detect_info_cs0;
struct ddr_detect_info detect_info_cs1;
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
	{0x40000000,	8,	8,	17,	10},
	/*12Gb*/
	{0x60000000,	16,	8,	16,	10},
	/*16Gb*/
	{0x80000000,	8,	8,	17,	10},
	{0x80000000,	16,	8,	16,	10},
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

LPDDR_JEDEC_ORIGINIZE org_standard_lp3[16] = {
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

struct MR8_size_info LPDDR3_mr8_size[] = {
	{MR8_SIZE_4Gb,0x20000000},
	{MR8_SIZE_6Gb,0x30000000},
	{MR8_SIZE_8Gb,0x40000000},
	{MR8_SIZE_12Gb,0x60000000},
	{MR8_SIZE_16Gb,0x80000000},
	{MR8_SIZE_32Gb,0x100000000},
};

int lpddr3_update_row_column(DRAM_JEDEC_INFO *info, LPDDR_JEDEC_ORIGINIZE *org_standard_ptr, int org_standard_num)
{
	int i;
	for (i = 0; i < org_standard_num; i++)
	{
		if ((info->cs_size == org_standard_ptr[i].cs_size) &&
			(info->dw == org_standard_ptr[i].dw) &&
			(info->bank == org_standard_ptr[i].bank))
		{
			info->row = org_standard_ptr[i].row;
			info->column= org_standard_ptr[i].column;
			return 0;
		}
	}
	return -1;
}

uint32 mr8_to_detect_info(uint32 cs, uint32 mr8_value,struct ddr_detect_info *detect_info)
{

	uint32 mr8_type;
	uint32 mr8_size;
	uint32 mr8_width;
	uint32 mr5=0,mr6=0,mr7=0;
	uint32 i;

	//check csx valid
	if (mr8_value == 0)
	{
		dmc_mrr(cs, 5, &mr5, 10000);
		dmc_mrr(cs, 6, &mr6, 10000);
		dmc_mrr(cs, 7, &mr7, 10000);
		if (((mr5) == (mr6)) && ((mr5)==(mr7)))
		{
			return FALSE;
		}
	}
	mr8_type = (mr8_value & 0x3)>>0;
	mr8_size = (mr8_value & 0x3c)>>2;
	mr8_width = (mr8_value & 0xc0)>>6;
	if(((DRAM_LPDDR4 == ddr_chip_cur.chip_type) && (!((mr8_type == LP4X_S16_SDRAM) || (mr8_type == S16_SDRAM)))) || ((DRAM_LPDDR3 == ddr_chip_cur.chip_type) && (mr8_type != S8_SDRAM)))
	{
		return FALSE;
	}
        if(DRAM_LPDDR4 == ddr_chip_cur.chip_type)
        {
            if(mr8_width == LP4_WIDTH_X16)
            {
            	detect_info->mem_width = 16;
            }else if(mr8_width == LP4_WIDTH_X8)
            {
            	detect_info->mem_width = 8;
            }else{
            	return FALSE;
            }
            for (i=0; i<sizeof(LPDDR4_mr8_size)/sizeof(LPDDR4_mr8_size[0]); i++)
            {
            	if(mr8_size == LPDDR4_mr8_size[i].mr8_size)
            	{
            		detect_info->mem_size = LPDDR4_mr8_size[i].mem_size;
            		detect_info->bank = 8;
            		return TRUE;
            	}
            }
        }
        else if(DRAM_LPDDR3 == ddr_chip_cur.chip_type)
        {
          //detect_info->mem_type = DRAM_LPDDR3;
            if(mr8_width == WIDTH_X32)
            {
            	detect_info->mem_width = 32;
            }else if(mr8_width == WIDTH_X16)
            {
            	detect_info->mem_width = 16;
            }else{
            	return FALSE;
            }

            for (i=0; i<sizeof(LPDDR3_mr8_size)/sizeof(LPDDR3_mr8_size[0]); i++)
             {
             	if(mr8_size == LPDDR3_mr8_size[i].mr8_size)
             	{
             		detect_info->mem_size = LPDDR3_mr8_size[i].mem_size;
             		detect_info->bank = 8;
             		return TRUE;
             	}
             }
       }
        else
        {
            /*for more ddr type*/
        }

	return FALSE;
}

int lpddr_auto_detect(void)
{
	u32 cs0_mr8;
	u32 cs1_mr8;
	u32 cs0_mr5;
	int cs_num = 1;
	u32 ret;
	int  ret_i=0;
        char mr8_hex_value[8] = {0};
	int  org_standard_num=0;
	DRAM_JEDEC_INFO *cs0_info, *cs1_info;
        LPDDR_JEDEC_ORIGINIZE (*org_standard_array)=org_standard_lp3;
        ret_i = dmc_mrr(0, 8, &cs0_mr8, 10000);
#ifdef MR8_LOG_ENABLE
	dmc_print_str("cs0 mr8: 0x");
	dmc_print_str(itoa_simple(cs0_mr8, mr8_hex_value, 16));
	dmc_print_str("\n");
#endif
	if (0 != ret_i)
	{
		dmc_print_str("cs0 CS0 mr8 read failed\n");
		while(1);
	}
	ret = mr8_to_detect_info(0, cs0_mr8, &detect_info_cs0);
	if(ret == FALSE)
	{
#ifndef DDR_SCAN_ENABLE
            dmc_print_str("ddr auto detect CS0 fail\n");
#endif
	;
	}
        ddr_chip_cur.cs0_jedec_info->cs_size = detect_info_cs0.mem_size;
        ddr_chip_cur.cs0_jedec_info->dw = detect_info_cs0.mem_width;
        if(DRAM_LPDDR3 == ddr_chip_cur.chip_type)
        {
            org_standard_num = sizeof(org_standard_lp3)/sizeof(org_standard_lp3[0]);
            org_standard_array = org_standard_lp3;
        }
        else if(DRAM_LPDDR4 == ddr_chip_cur.chip_type)
        {
            org_standard_num = sizeof(org_standard_lp4)/sizeof(org_standard_lp4[0]);
            org_standard_array = org_standard_lp4;
        }
        else
        {
            /*for other type*/
        }

	if (0 != lpddr3_update_row_column(ddr_chip_cur.cs0_jedec_info, org_standard_array, org_standard_num))
	{
		dmc_print_str("ddr update CS0 jedec info failed\n");
		while(1);
	}

        if((DRAM_LPDDR3 == ddr_chip_cur.chip_type) && (detect_info_cs0.mem_width == 16))
        {
        	/*update cs0 ddr info*/
        	ddr_chip_cur.cs0_jedec_info->cs_size = detect_info_cs0.mem_size * 2;
        }
        else if((DRAM_LPDDR4 == ddr_chip_cur.chip_type) )
        {
            if(detect_info_cs0.mem_width == 8)
            {
        	/*update cs0 ddr info*/
        	ddr_chip_cur.cs0_jedec_info->cs_size = detect_info_cs0.mem_size * 4;
            }
            else
            {
        	/*update cs0 ddr info*/
        	ddr_chip_cur.cs0_jedec_info->cs_size = detect_info_cs0.mem_size * 2;
            }
        }
        else
        {
            /*for other type*/
        }
	//add mr5 read
	ret_i = dmc_mrr(0, 5, &cs0_mr5, 10000);
	if (0 != ret_i)
	{
#ifndef DDR_SCAN_ENABLE
		dmc_print_str("cs0 mr5 read failed\n");
#endif
		;
	}
	else
	{
		ddr_chip_cur.manufacture_id = (cs0_mr5 & 0xff);
	}

        ret_i = dmc_mrr(1, 8, &cs1_mr8, 10000);
#ifdef MR8_LOG_ENABLE
	dmc_print_str("cs1 mr8: 0x");
	dmc_print_str(itoa_simple(cs1_mr8, mr8_hex_value, 16));
	dmc_print_str("\n");
#endif
	if (0 != ret_i)
	{
		dmc_print_str("cs1 mr8 read failed\n");
		while(1);
	}

	ret = mr8_to_detect_info(1, cs1_mr8, &detect_info_cs1);
	if(ret == FALSE)
	{
		ddr_chip_cur.cs1_jedec_info->cs_size = 0;
#ifndef DDR_SCAN_ENABLE
		dmc_print_str("\n\r ddr auto detect CS1 fail ");
#endif
	}
	else
	{
            cs_num ++;
            ddr_chip_cur.cs1_jedec_info->cs_size = detect_info_cs1.mem_size;
            ddr_chip_cur.cs1_jedec_info->dw = detect_info_cs1.mem_width;

            if (0 != lpddr3_update_row_column(ddr_chip_cur.cs1_jedec_info, org_standard_array, org_standard_num))
            {
            	dmc_print_str("ddr update CS1 jedec info failed\n");
            	while(1);
            }

            if((DRAM_LPDDR3 == ddr_chip_cur.chip_type) && (detect_info_cs1.mem_width == 16))
            {
            	/*update cs1 ddr info*/
            	ddr_chip_cur.cs1_jedec_info->cs_size = detect_info_cs1.mem_size * 2;
            }
            else if((DRAM_LPDDR4 == ddr_chip_cur.chip_type))
            {
                if(detect_info_cs1.mem_width == 8)
                {
                	/*update cs1 ddr info*/
                	ddr_chip_cur.cs1_jedec_info->cs_size = detect_info_cs1.mem_size * 4;
                }
                else
                {
                	/*update cs1 ddr info*/
                	ddr_chip_cur.cs1_jedec_info->cs_size = detect_info_cs1.mem_size * 2;
                }
            }
            else
            {
                /*for other type*/
            }
        }
	/*update ddr cs number*/
	ddr_chip_cur.cs_num = cs_num;

	/*check whether the cs size if symmetric*/
	if (2 == ddr_chip_cur.cs_num)
	{
		if (ddr_chip_cur.cs0_jedec_info->cs_size == ddr_chip_cur.cs1_jedec_info->cs_size)
		{
			ddr_chip_cur.unsymmetry = 0;
		}
		else
		{
			/* TODO: according to ddr combination configuration documenit record unsymmetry sdram column mode*/
			ddr_chip_cur.unsymmetry = 1;
			/*cs0 512M(1x32) + cs1 256M(1x32)*/
			if ((ddr_chip_cur.cs0_jedec_info->cs_size == 0x20000000) &&
			    (ddr_chip_cur.cs1_jedec_info->cs_size== 0x10000000))
			{
				unsymmetry_mode_cur = DDR_6Gb_10_COL_MODE;
			}
			/*cs0 1GB(2x16) + cs1 512M(1x32)*/
			else if((ddr_chip_cur.cs0_jedec_info->cs_size == 0x40000000) &&
				(ddr_chip_cur.cs1_jedec_info->cs_size == 0x20000000) &&
				(detect_info_cs0.mem_width == 16))
			{
				unsymmetry_mode_cur = DDR_6Gb_11_COL_MODE;
			}
			/*mode 1:cs0 2GB(1x32) + cs1 1GB (1x32); mode 2:cs0 2GB(2x16) + cs1 (1x32)*/
			else if ((ddr_chip_cur.cs0_jedec_info->cs_size == 0x80000000) &&
				 (ddr_chip_cur.cs1_jedec_info->cs_size == 0x40000000) &&
				 (detect_info_cs1.mem_width == 32))
			{
				unsymmetry_mode_cur = DDR_12Gb_MODE;
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
#if defined(GPIO_DETECT_DRAM_TYPE)
struct ddr_type_t ddr_pinmux_case[4]=
{
/***   gpio_N1  gpio_N0  pinmux_case    ***/
       {0,      0,       LP3_PINMUX_CASE0},
       {0,      1,       LP4_PINMUX_CASE2},
       {1,      0,       LP4_PINMUX_CASE0},
       {1,      1,       LP4_PINMUX_CASE1}
};
void ddr_type_detect(void)
{
        uint32 gpio_n1_val,gpio_n0_val;
        char pinmux_case_detect = 0;
        char i = 0;
	sprd_gpio_request(DRAM_TYPE_DETECT_GPIO_N1);
	sprd_gpio_direction_input(DRAM_TYPE_DETECT_GPIO_N1);
	gpio_n1_val = sprd_gpio_get(DRAM_TYPE_DETECT_GPIO_N1);

#if defined(GPIO_DETECT_DRAM_TYPE_ONE_PIN)
	gpio_n0_val = 0;
#else
	sprd_gpio_request(DRAM_TYPE_DETECT_GPIO_N0);
	sprd_gpio_direction_input(DRAM_TYPE_DETECT_GPIO_N0);
	gpio_n0_val = sprd_gpio_get(DRAM_TYPE_DETECT_GPIO_N0);
#endif

//        pinmux_case_detect = ((gpio_n1_val << 1) & (gpio_n0_val ));
//        ddr_chip_cur.pinmux_case = pinmux_case_detect;

        for(i=0; i<4; i++)
        {
            if((gpio_n1_val == ddr_pinmux_case[i].gpio_1_value) && (gpio_n0_val == ddr_pinmux_case[i].gpio_0_value))
            {
                ddr_chip_cur.pinmux_case = ddr_pinmux_case[i].ddr_pinmux_c;
                break;
            }
        }
        if(4 == i)
        {
		dmc_print_str("ddr_type_detect : gpio read failed\n");
                while(1);
        }
        if(LP3_PINMUX_CASE0  == ddr_chip_cur.pinmux_case)
        {
	    ddr_chip_cur.chip_type = DRAM_LPDDR3;
	    ddr_chip_cur.io_mode = IO_LP3;
        }
        else if((LP4_PINMUX_CASE0  == ddr_chip_cur.pinmux_case) || (LP4_PINMUX_CASE1  == ddr_chip_cur.pinmux_case))
        {
	    ddr_chip_cur.chip_type = DRAM_LPDDR4;
	    ddr_chip_cur.io_mode = IO_LP4X;
        }
        else if(LP4_PINMUX_CASE2  == ddr_chip_cur.pinmux_case)
        {
	    ddr_chip_cur.chip_type = DRAM_LPDDR4;
	    ddr_chip_cur.io_mode = IO_LP4;
        }
}
void lp3_identify(void)
{
    u32 cs0_mr8;
    if(LP3_PINMUX_CASE0 == ddr_chip_cur.pinmux_case)
    {
	if (0 != dmc_mrr(0, 8, &cs0_mr8, 10000))
	{
		dmc_print_str("CS0 mr8 read failed\n");
		while(1);
	}
        if (!(cs0_mr8 & (1 << 4)))
        {
            ddr_chip_cur.pinmux_case = LP3_PINMUX_CASE1;
        }
    }
}
#endif

#ifdef DDR_FREQ_AUTO_SEL
int mr_freq_select(u32 *ddr_clk)
{
	u8 mr5_val = 0,mr6_val = 0,mr7_val = 0,mr8_val=0;
	u8 hex_value[4] = {0};
	int size = sizeof(mr_freq_detect)/sizeof(mr_freq_detect[0]);
	int i;
	dmc_mrr(0, 5, &mr5_val, 10000);
	dmc_mrr(0, 6, &mr6_val, 10000);
	dmc_mrr(0, 7, &mr7_val, 10000);
	dmc_mrr(0, 8, &mr8_val, 10000);
#if 0
	dmc_print_str("mr5: 0x");
	dmc_print_str(itoa_simple(mr5_val, hex_value, 16));
	dmc_print_str("\n");
	dmc_print_str("mr6: 0x");
	dmc_print_str(itoa_simple(mr6_val, hex_value, 16));
	dmc_print_str("\n");
	dmc_print_str("mr7: 0x");
	dmc_print_str(itoa_simple(mr7_val, hex_value, 16));
	dmc_print_str("\n");
	dmc_print_str("mr8: 0x");
	dmc_print_str(itoa_simple(mr8_val, hex_value, 16));
	dmc_print_str("\n");
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
