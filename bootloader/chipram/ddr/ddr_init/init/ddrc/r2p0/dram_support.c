/**************
**DRAM Auto Detect Function
**IO Driver Strength
**CA/DQ vref
**Pinmux
**send to uboot ddr size
**
************/
#include <asm/arch/clk_para_config.h>
#include <sci_types.h>
#include <asm/arch/sprd_chipram_env.h>
#include "dram_support.h"

extern DRAM_INFO_T dram_info;
extern DDRC_DMC_DTMG_T *dmc_dtmg;
extern DDRC_PHY_TMG_T *phy_tmg;
extern u32 lp3_size_timing[2][6];
extern u32 lp4_size_timing[4][8];

#ifdef DDR_SCAN_ENABLE
#define dmc_print_str(x) NULL
#define print_Hex(x) NULL
#define print_Dec(x) NULL
#endif

struct MR8_SIZE_INFO LPDDR3_mr8_size[] = {
		{LPDDR3_MR8_SIZE_1Gb,0x0800},
		{LPDDR3_MR8_SIZE_2Gb,0x1000},
		{LPDDR3_MR8_SIZE_4Gb,0x2000},
		{LPDDR3_MR8_SIZE_6Gb,0x3000},
		{LPDDR3_MR8_SIZE_8Gb,0x4000},
		{LPDDR3_MR8_SIZE_12Gb,0x6000},
		{LPDDR3_MR8_SIZE_16Gb,0x8000},
		{LPDDR3_MR8_SIZE_32Gb,0x10000},
};

struct MR8_SIZE_INFO LPDDR4_mr8_size[] = {
		{LPDDR4_MR8_SIZE_2Gb,0x1000},
		{LPDDR4_MR8_SIZE_3Gb,0x1800},
		{LPDDR4_MR8_SIZE_4Gb,0x2000},
		{LPDDR4_MR8_SIZE_6Gb,0x3000},
		{LPDDR4_MR8_SIZE_8Gb,0x4000},
		{LPDDR4_MR8_SIZE_12Gb,0x6000},
		{LPDDR4_MR8_SIZE_16Gb,0x8000},
};

#if defined(DRAM_FREQ_AUTO_DETECT)
struct DRAM_TOP_FREQ_SEL LPDDR4_top_freq[] = {
		{DDR_CLK_1200M,0x00000601},
		{DDR_CLK_933M, 0x00000501},
};

struct DRAM_TOP_FREQ_SEL LPDDR3_top_freq[] = {
		{DDR_CLK_933M, 0x00000501},
};

#endif

//update MR5/MR6/MR7 info
int dram_revision_info_update(u32 cs_num)
{
	u32 mr5_val=0,mr6_val=0,mr7_val=0;
	u32 ret;
	//reset fifo
	ddrc_phy_fifo_reset();
	dmc_mrr(DRAM_MR_5,cs_num,&mr5_val);
	if(DRAM_CS_0 == cs_num)
	{
		dram_info.mr_reg_cs0 &= ~(0xff<<0);
		dram_info.mr_reg_cs0 |= (mr5_val<<0);
	}else
	{
		dram_info.mr_reg_cs1 &= ~(0xff<<0);
		dram_info.mr_reg_cs1 |= (mr5_val<<0);
	}
	//reset fifo
	ddrc_phy_fifo_reset();
	dmc_mrr(DRAM_MR_6,cs_num,&mr6_val);
	if(DRAM_CS_0 == cs_num)
	{
		dram_info.mr_reg_cs0 &= ~(0xff<<8);
		dram_info.mr_reg_cs0 |= (mr6_val<<8);
	}else
	{
		dram_info.mr_reg_cs1 &= ~(0xff<<8);
		dram_info.mr_reg_cs1 |= (mr6_val<<8);
	}
	//reset fifo
	ddrc_phy_fifo_reset();
	dmc_mrr(DRAM_MR_7,cs_num,&mr7_val);
	if(DRAM_CS_0 == cs_num)
	{
		dram_info.mr_reg_cs0 &= ~(0xff<<16);
		dram_info.mr_reg_cs0 |= (mr7_val<<16);
	}else
	{
		dram_info.mr_reg_cs1 &= ~(0xff<<16);
		dram_info.mr_reg_cs1 |= (mr7_val<<16);
	}

	if((mr5_val==mr6_val)&&(mr6_val==mr7_val))
	{
		return FALSE;
	}
	return TRUE;
}

void dram_byte_latency_mode()
{
	u32 mr0_val=0;
	u32 cs_num=0;
	u32 fn;//config 256~1333
	for(cs_num=0;cs_num<2;cs_num++)
	{
		ddrc_phy_fifo_reset();
		dmc_mrr(DRAM_MR_0,cs_num,&mr0_val);
#if TEST_DEBUG_LOG_LEVEL > 1
		dmc_print_str("\r\nMR0 value:");
		print_Hex(mr0_val);
#endif
		if((mr0_val>>1)&0x1)
		{
			for(fn=3; fn<dram_info.fn_max; fn++)
			{
			    (dmc_dtmg+fn)->dmc_dtmg6 &= ~(0x1f<<0);
			    (dmc_dtmg+fn)->dmc_dtmg6 |= ((((dmc_dtmg+fn)->dmc_dtmg6>>8)&0x1f)<<0);
			    __raw_writel(DMC_CTL0_(0x0198+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg6);
			}
            return;
		}
	}
}

u32 mr8_to_detect_info(u32 mr8_value,u32 cs_num)
{
	u32 mr8_type,mr8_size,mr8_width;
	u32 i;
	u32 mem_size=0;
	u32 dram_detect_size=0;

	//detect cs valid
	if((0 == dram_revision_info_update(cs_num))||(mr8_value == 0xFF))
	{
		return FALSE;
	}
	mr8_type = (mr8_value & 0x3)>>0;
	mr8_size = (mr8_value & 0x3c)>>2;
	mr8_width = (mr8_value & 0xc0)>>6;
	if(dram_info.dram_type==DRAM_LP3)
	{
		for(i=0; i< sizeof(LPDDR3_mr8_size)/sizeof(LPDDR3_mr8_size[0]);i++)
		{
			if(mr8_size == LPDDR3_mr8_size[i].mr8_size)
			{
				mem_size=LPDDR3_mr8_size[i].mem_size;
			}
		}
		if(mr8_width == WIDTH_X16)
		{
			mem_size *=2;
		}
	}else
	{
		mr8_width += WIDTH_X16;
		for(i=0; i< sizeof(LPDDR4_mr8_size)/sizeof(LPDDR4_mr8_size[0]);i++)
		{
			if(mr8_size == LPDDR4_mr8_size[i].mr8_size)
			{
				mem_size=(LPDDR4_mr8_size[i].mem_size*2);
			}
		}
		if(mr8_width == WIDTH_X8)
		{
			mem_size *= 2;
		}
	}
	switch(mem_size)
	{
	case MEM_SIZE_4Gb:dram_detect_size=0x4;break;
	case MEM_SIZE_6Gb:dram_detect_size=0x6;break;
	case MEM_SIZE_8Gb:dram_detect_size=0x8;break;
	case MEM_SIZE_12Gb:dram_detect_size=0xc;break;
	case MEM_SIZE_16Gb:dram_detect_size=0x10;break;
	case MEM_SIZE_24Gb:dram_detect_size=0x18;break;
	case MEM_SIZE_32Gb:dram_detect_size=0x20;break;
	case MEM_SIZE_48Gb:dram_detect_size=0x30;break;
	case MEM_SIZE_64Gb:dram_detect_size=0x40;break;
	}
	dram_info.dram_detect_type &= ~(0xFF<<(4+cs_num*12));
	dram_info.dram_detect_type |= (dram_detect_size<<(4+cs_num*12));
	dram_info.dram_detect_type &= ~(0xF<<(cs_num*12));
	dram_info.dram_detect_type |= (mr8_width<<(cs_num*12));
	if(cs_num==DRAM_CS_0)
	{
		dram_info.cs0_size=(((u64)mem_size)<<16);
	}else
	{
		dram_info.cs1_size=(((u64)mem_size)<<16);
		dram_info.cs_num++;
	}
	return TRUE;
}


void dram_type_pinmux_auto_detect()
{
	/*
	*ADC Interface is used to detect DDR Type which is supported by freeman.liu
	*gerritID:http://review.source.spreadtrum.com/gerrit/#/c/527750/
	*
	*/
	u32 volt_val=0;
	u32 dram_status=0;//0:emcp 1:discrete
#if defined(DRAM_TYPE_AUTO_DETECT)
	sc27xx_adc_current_mode_vol(6,0,2000,&volt_val);
#ifdef CONFIG_DEBUG
	dmc_print_str("\r\n ADC Volt Value");
	print_Hex(volt_val);
#endif
	if((volt_val>=446) && (volt_val<=514))
	{
		dram_info.dram_type=DRAM_LP4X;
		dram_status=DRAM_EMCP;
	}else if((volt_val>=560) && (volt_val<=640))
	{
		dram_info.dram_type=DRAM_LP4X;
		dram_status=DRAM_DISCRETE;
	}else if((volt_val>=731) && (volt_val<=829))
	{
		dram_info.dram_type=DRAM_LP4;
		dram_status=DRAM_DISCRETE;
	}else if((volt_val>=883) && (volt_val<=977))
	{
		dram_info.dram_type=DRAM_LP4X;
		dram_status=DRAM_EMCP;
	}else if((volt_val>=1054) && (volt_val<=1186))
	{
		dram_info.dram_type=DRAM_LP3;
		dram_status=DRAM_DISCRETE;
	}else
	{
		dmc_print_str("\r\nADC Detect Volt error!!!");
	}
#else
	dram_info.dram_type=DRAM_TYPE_FIXED;
	dram_status=DRAM_EMCP;
#endif
	dram_info.dram_detect_type &= ~(0xFF<<24);
	switch(dram_info.dram_type)
	{
	case DRAM_LP3:
		dram_info.pinmux_type=DRAM_PINMUX_LP3;
		dram_info.dram_detect_type |= (DRAM_LP3<<24);
		dram_info.fn_max=LP3_FN_MAX;
		//regulator_set_voltage("vddcore",750);
		regulator_set_voltage("vddmem",DCDC_MEM_LP3);
		reg_bit_set(DDRPHY_VREF, 1, 1,0x0);//phy_vref_pd
		reg_bit_set(DDRPHY_VREF, 2, 8,0x50);//phy_vref_adj
		break;
	case DRAM_LP4:
		dram_info.pinmux_type=DRAM_PINMUX_DISCRETE_LP4;
		dram_info.dram_detect_type |= (DRAM_LP4<<24);
		dram_info.fn_max=LP4_FN_MAX;
		//regulator_set_voltage("vddcore",900);
		regulator_set_voltage("vddmem",DCDC_MEM);
		regulator_set_voltage("vddmemq",DCDC_MEM);
		reg_bit_set(DDRPHY_VREF, 1, 1,0x1);//phy_vref_pd
		break;
	case DRAM_LP4X:
		dram_info.dram_detect_type |= (DRAM_LP4<<24);
		dram_info.pinmux_type=DRAM_PINMUX_EMCP_LP4X;
		if(dram_status==DRAM_DISCRETE)
		{
			dram_info.pinmux_type=DRAM_PINMUX_DISCRETE_LP4X;
		}
		dram_info.fn_max=LP4_FN_MAX;
		//regulator_set_voltage("vddcore",mcu_clk_para.dcdc_core.value);
		regulator_set_voltage("vddmem",DCDC_MEM);
		reg_bit_set(DDRPHY_VREF, 1, 1,0x1);//phy_vref_pd
		break;
	}
	wait_us(50);
}

void dram_size_dmc_timing_adapter()
{
	u32 fn;
	u32 *tmg_arr=NULL;
	u32 cs_n=0;
	u32 cs_density[2]={0};
	u32 density=0;
	u32 density_num=0;
	for(cs_n=0;cs_n<dram_info.cs_num;cs_n++)
	{
		(cs_n==0)?(density=((dram_info.mr_reg_cs0>>26)&0xf)):(density=((dram_info.mr_reg_cs1>>26)&0xf));
		if(dram_info.dram_type==DRAM_LP3)
		{
			switch(density)
			{
			case LPDDR3_MR8_SIZE_1Gb:
			case LPDDR3_MR8_SIZE_2Gb:
			case LPDDR3_MR8_SIZE_4Gb:
				 cs_density[cs_n]=0;
				 break;
			case LPDDR3_MR8_SIZE_6Gb:
			case LPDDR3_MR8_SIZE_8Gb:
			case LPDDR3_MR8_SIZE_12Gb:
			case LPDDR3_MR8_SIZE_16Gb:
				 cs_density[cs_n]=1;
				 break;
			}
			if((cs_n>0)&&(cs_density[1]>cs_density[0]))
			{
				density_num=cs_density[1];
			}else
			{
				density_num=cs_density[0];
			}
			tmg_arr=&lp3_size_timing[density_num][0];
		}else
		{
			switch(density)
			{
			case LPDDR4_MR8_SIZE_2Gb:
				 cs_density[cs_n]=0;
				 break;
			case LPDDR4_MR8_SIZE_3Gb:
			case LPDDR4_MR8_SIZE_4Gb:
				 cs_density[cs_n]=1;
				 break;
			case LPDDR4_MR8_SIZE_6Gb:
		    case LPDDR4_MR8_SIZE_8Gb:
				 cs_density[cs_n]=2;
				 break;
			case LPDDR4_MR8_SIZE_12Gb:
			case LPDDR4_MR8_SIZE_16Gb:
				 cs_density[cs_n]=3;
				 break;
			}
			if((cs_n>0)&&(cs_density[1]>cs_density[0]))
			{
				density_num=cs_density[1];
			}else
			{
				density_num=cs_density[0];
			}
			tmg_arr=&lp4_size_timing[density_num][0];
		}
	}
#if TEST_DEBUG_LOG_LEVEL > 1
	dmc_print_str("\r\ndram density:");
	print_Dec(density_num);
#endif
	for(fn=0;fn<dram_info.fn_max;fn++)
	{
		(dmc_dtmg+fn)->dmc_dtmg2 &= ~(0x3ff<<0);
		(dmc_dtmg+fn)->dmc_dtmg2 &= ~(0xffff<<16);
		(dmc_dtmg+fn)->dmc_dtmg2 |= tmg_arr[fn];
		__raw_writel(DMC_CTL0_(0x0188+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg2);
	}
}

void dram_size_ctrl_set()
{
	u32 col_mode=0;
	u32 cs_position=0;
	u32 cs_mode=0;
	u32 remap_en=0;
	u32 remap_addr_0=0;
	u32 remap_addr_1=0;
#if defined(DRAM_SIZE_AUTO_DETECT)||defined(DRAM_SIZE_FIXED)
	if(dram_info.dram_type==DRAM_LP3)
	{
		switch(dram_info.dram_detect_type)
		{
		case LPDDR3_32G_2CS_16GX32_16GX32:
		case LPDDR3_32G_2CS_16GX16_16GX16:
		case LPDDR3_32G_2CS_16GX16_16GX32:
		case LPDDR3_24G_2CS_16GX16_8GX16:
			col_mode=0x3;cs_position=0x7;cs_mode=0x0;break;
		case LPDDR3_32G_1CS_32GX16:
		case LPDDR3_24G_1CS_24GX32:
			col_mode=0x4;cs_position=0x7;cs_mode=0x1;break;
		case LPDDR3_24G_2CS_16GX32_8GX32:
		case LPDDR3_24G_2CS_16GX16_8GX32:
		case LPDDR3_24G_2CS_8GX32_16GX16:
		case LPDDR3_24G_2CS_8GX32_16GX32:
		case LPDDR3_24G_2CS_8GX16_16GX32:
			col_mode=0x7;cs_position=0x7;cs_mode=0x0;break;
		case LPDDR3_24G_2CS_12GX32_12GX32:
		case LPDDR3_24G_2CS_12GX16_12GX16:
		case LPDDR3_24G_2CS_12GX16_12GX32:
			col_mode=0x3;cs_position=0x7;cs_mode=0x0;
			remap_en=0x1;remap_addr_0=0x98543210;remap_addr_1=0x3210dcba;
			break;
		case LPDDR3_16G_1CS_16GX32:
		case LPDDR3_16G_1CS_16GX16:
		case LPDDR3_12G_1CS_12GX32:
		case LPDDR3_12G_1CS_12GX16:
			col_mode=0x3;cs_position=0x6;cs_mode=0x1;break;
		case LPDDR3_16G_2CS_8GX32_8GX32:
		case LPDDR3_12G_2CS_8GX32_4GX32:
			col_mode=0x2;cs_position=0x6;cs_mode=0x0;break;
		case LPDDR3_16G_2CS_8GX16_8GX16:
			col_mode=0x3;cs_position=0x6;cs_mode=0x0;break;
		case LPDDR3_12G_2CS_6GX32_6GX32:
			col_mode=0x2;cs_position=0x6;cs_mode=0x0;
			remap_en=0x1;remap_addr_0=0x10654210;remap_addr_1=0x42106542;
			break;
		case LPDDR3_12G_2CS_8GX16_4GX32:
			col_mode=0x6;cs_position=0x6;cs_mode=0x0;break;
		case LPDDR3_8G_1CS_8GX32:
			col_mode=0x2;cs_position=0x5;cs_mode=0x1;break;
		case LPDDR3_8G_1CS_8GX16:
			col_mode=0x3;cs_position=0x5;cs_mode=0x1;break;
		case LPDDR3_8G_2CS_4GX32_4GX32:
			col_mode=0x2;cs_position=0x5;cs_mode=0x0;break;
		case LPDDR3_6G_1CS_6GX32:
			col_mode=0x2;cs_position=0x5;cs_mode=0x1;break;
		case LPDDR3_6G_2CS_4GX32_2GX32:
			col_mode=0x5;cs_position=0x5;cs_mode=0x0;break;
		case LPDDR3_4G_1CS_4GX32:
		case LPDDR3_4G_1CS_4GX16:
			col_mode=0x2;cs_position=0x4;cs_mode=0x1;break;
		case LPDDR3_4G_2CS_2GX32_2GX32:
			col_mode=0x1;cs_position=0x4;cs_mode=0x0;break;
		default:
			col_mode=0x2;cs_position=0x6;cs_mode=0x0;break;
		}
	}else
	{
		switch(dram_info.dram_detect_type)
		{
		case LPDDR4_64G_2CS_32GX8_32GX8:
		case LPDDR4_48G_2CS_16GX8_32GX8:
		case LPDDR4_48G_2CS_16GX16_32GX8:
			col_mode=0x2;cs_position=0x7;cs_mode=0x0;break;
		case LPDDR4_48G_2CS_32GX8_16GX8:
		case LPDDR4_48G_2CS_32GX8_16GX16:
			col_mode=0x2;cs_position=0x7;cs_mode=0x0;
			remap_en=0x1;remap_addr_0=0xba983210;remap_addr_1=0x3210fedc;
			break;
		case LPDDR4_48G_2CS_24GX8_24GX8:
			col_mode=0x2;cs_position=0x7;cs_mode=0x0;
			remap_en=0x1;remap_addr_0=0x98543210;remap_addr_1=0x3210dcba;
			break;
		case LPDDR4_32G_1CS_32GX32:
			col_mode=0x2;cs_position=0x6;cs_mode=0x1;break;
		case LPDDR4_32G_2CS_16GX16_16GX16:
		case LPDDR4_32G_2CS_16GX8_16GX16:
		case LPDDR4_24G_2CS_16GX16_8GX16:
		case LPDDR4_24G_2CS_16GX8_8GX16:
			col_mode=0x2;cs_position=0x6;cs_mode=0x0;break;
		case LPDDR4_24G_2CS_12GX16_12GX16:
			col_mode=0x2;cs_position=0x6;cs_mode=0x0;
			remap_en=0x1;remap_addr_0=0x10654210;remap_addr_1=0x42106542;
			break;
		case LPDDR4_16G_1CS_16GX16:
		case LPDDR4_12G_1CS_12GX16:
			col_mode=0x2;cs_position=0x5;cs_mode=0x1;break;
		case LPDDR4_16G_2CS_8GX16_8GX16:
		case LPDDR4_12G_2CS_8GX16_4GX16:
			col_mode=0x2;cs_position=0x5;cs_mode=0x0;break;
		case LPDDR4_8G_1CS_8GX16:
			col_mode=0x2;cs_position=0x4;cs_mode=0x1;break;
		case LPDDR4_8G_2CS_4GX16_4GX16:
			col_mode=0x2;cs_position=0x4;cs_mode=0x0;break;
		case LPDDR4_4G_1CS_4GX16:
			col_mode=0x2;cs_position=0x3;cs_mode=0x1;break;
		default:
			col_mode=0x2;cs_position=0x6;cs_mode=0x0;break;
		}
	}
#else
	cs_mode=DRAM_CS_MODE_DEF;
	cs_position=DRAM_CS_POSITION_DEF;
	col_mode=DRAM_COL_MODE_DEF;
	remap_en=DRAM_REMAP_EN;
	remap_addr_0=DRAM_REMAP_ADDR_0;
	remap_addr_1=DRAM_REMAP_ADDR_1;
#endif
	reg_bit_set(DMC_CTL0_(0x0000),14, 2,cs_mode);//rf_cs_mode
	reg_bit_set(DMC_CTL0_(0x0000), 0, 3,cs_position);//rf_cs_position
	reg_bit_set(DMC_CTL0_(0x0100), 4, 3,col_mode);//drf_column_mode
	reg_bit_set(DMC_CTL0_(0x0014), 3, 1,remap_en);//rf_remap_en
	__raw_writel(DMC_CTL0_(0x0018),remap_addr_0);//rf_dmc_remap_addr_0
	__raw_writel(DMC_CTL0_(0x001c),remap_addr_1);//rf_dmc_remap_addr_0

	//update timing parameter relate to DDR SIZE
	dram_size_dmc_timing_adapter();
}



void dram_size_auto_detect()
{
	u32 cs_mr8_val=0;
	u32 ret;
	u64 total_size=0;
	dram_info.cs_num=1;
	dram_info.cs0_size=0x0;
	dram_info.cs1_size=0x0;
	//reset fifo
	ddrc_phy_fifo_reset();
	ret=dmc_mrr(DRAM_MR_8,DRAM_CS_0,&cs_mr8_val);
	if(0 != ret)
	{
		dmc_print_str("\r\nCS0 mr8 read fail!");
		while(1);
	}
	dram_info.mr_reg_cs0 &= ~(0xff<<24);
	dram_info.mr_reg_cs0 |= (cs_mr8_val<<24);
	ret=mr8_to_detect_info(cs_mr8_val,DRAM_CS_0);
	if(!ret)
	{
		dmc_print_str("\r\nddr cs0 fail!");
		while(1);
	}
	cs_mr8_val=0;
	//reset fifo
	ddrc_phy_fifo_reset();
	dmc_mrr(DRAM_MR_8,DRAM_CS_1,&cs_mr8_val);
	dram_info.mr_reg_cs1 &= ~(0xff<<24);
	dram_info.mr_reg_cs1 |= (cs_mr8_val<<24);
	ret=mr8_to_detect_info(cs_mr8_val,DRAM_CS_1);
	if(!ret)
	{
		dmc_print_str("\r\nddr cs1 unvalid!");
	}
	if(dram_info.dram_type == DRAM_LP4X)
	{
		dram_byte_latency_mode();
	}
	reg_bit_set(DMC_CTL0_(0x0104),28,1,0x0);//dsoft_cs
	dram_size_ctrl_set();
	total_size=dram_info.cs0_size+dram_info.cs1_size;
	(total_size>0x100000000)?(dram_info.dram_32gb_flag=1):(dram_info.dram_32gb_flag=0);
#ifdef CONFIG_DEBUG
	dmc_print_str("\r\nCS0 MR8/7/6/5:");
	print_Hex(dram_info.mr_reg_cs0);
	if(dram_info.cs_num>1)
	{
		dmc_print_str("\r\nCS1 MR8/7/6/5:");
		print_Hex(dram_info.mr_reg_cs1);
	}
	dmc_print_str("\r\nDRAM Type: ");
	print_Hex(dram_info.dram_detect_type);
#endif
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
	p_env->cs_number = dram_info.cs_num;
	p_env->cs0_size = dram_info.cs0_size;
	p_env->cs1_size = dram_info.cs1_size;
    u32 val;
	if (dram_info.cs_num == 1)
	{
		p_env->cs1_size = 0;
		p_env->dram_size = p_env->cs0_size;
	}
	else if (dram_info.cs_num == 2)
		p_env->dram_size = (u64)p_env->cs0_size + (u64)p_env->cs1_size;

	if (dram_info.cs_num == 2)
	{
#if defined(CONFIG_CHIPRAM_DDR_CUSTOMIZE)
		dmc_ddr_size_limit(p_env, CONFIG_CHIPRAM_DDR_CUSTOMIZE);
#else
		p_env->cs1_size -= BIST_RESERVE_SIZE;
#endif
	}
	else if (dram_info.cs_num == 1)
	{
#if defined(CONFIG_CHIPRAM_DDR_CUSTOMIZE)
		dmc_ddr_size_limit(p_env, CONFIG_CHIPRAM_DDR_CUSTOMIZE);
#else
		p_env->cs0_size -= BIST_RESERVE_SIZE;
#endif
	}
	/*Save physical ddr size int dmc reg for kernel driver*/
	REG32(DDR_INIT_DEBUG_ADDR+0x0) = p_env->dram_size & 0xFFFFFFFF;
	REG32(DDR_INIT_DEBUG_ADDR+0x4) = p_env->dram_size >> 32;
}


void dram_freq_auto_detect(u32* target_fn)
{
#ifdef DRAM_FREQ_AUTO_DETECT
	u32 fn=0;
	u32 fixed_mr_val=dram_info.mr_reg_cs0 & (~(0xff<<24));
	*target_fn=DRAM_TOP_FREQ;
	struct DRAM_TOP_FREQ_SEL *top_freq_arr = (dram_info.dram_type == DRAM_LP3)?LPDDR3_top_freq
				:LPDDR4_top_freq;
	u32 fn_max=(dram_info.dram_type == DRAM_LP3)?(sizeof(LPDDR3_top_freq)/sizeof(LPDDR3_top_freq[0]))
				:(sizeof(LPDDR4_top_freq)/sizeof(LPDDR4_top_freq[0]));
	for(fn=0;fn<fn_max;fn++)
	{
		if(fixed_mr_val==(top_freq_arr+fn)->fixed_mr_val)
		{
			*target_fn=(top_freq_arr+fn)->top_ddr_clk;
		}
	}
#else
	*target_fn=DRAM_TOP_FREQ;
	if(dram_info.dram_type == DRAM_LP3)
	{
		if(*target_fn>DDR_CLK_933M)
		{
			*target_fn=DDR_CLK_933M;
		}
	}
#endif

}
u32 val_pinmux[][16] = {
{
CA_BIT_PATTERN_AC0_31_0,BYTE_PATTERN_AC0,CA_BIT_PATTERN_AC1_31_0,BYTE_PATTERN_AC1,DQ_BIT_IN_PATTERN_DS0_31_0,
DQ_BIT_OUT_PATTERN_DS0_31_0,DQ_BIT_IN_OUT_PATTERN_DS0_35_32,DQ_BIT_IN_PATTERN_DS1_31_0,DQ_BIT_OUT_PATTERN_DS1_31_0,DQ_BIT_IN_OUT_PATTERN_DS1_35_32,
DQ_BIT_IN_PATTERN_DS2_31_0,DQ_BIT_OUT_PATTERN_DS2_31_0,DQ_BIT_IN_OUT_PATTERN_DS2_35_32,DQ_BIT_IN_PATTERN_DS3_31_0,DQ_BIT_OUT_PATTERN_DS3_31_0,DQ_BIT_IN_OUT_PATTERN_DS3_35_32
},
{
0x00042032,0x00c68898,0x00908765,0x00468898,0x56432108,0x86764321,
0x00000007,0x51047623,0x32740165,0x00000088,0x80164235,0x84031256,
0x00000077,0x75643810,0x75643810,0x00000022
},
{
0x00040123,0x00c68898,0x00908765,0x00468898,0x46325081,0x86375402,
0x00000017,0x01254637,0x02431567,0x00000088,0x10863254,0x84103276,
0x00000057,0x76534810,0x76534810,0x00000022
},
{
0x00203514,0x00468898,0x00205431,0x00468898,0x84307512,0x38265014,
0x00000076,0x43785102,0x58376021,0x00000046,0x84207631,0x32861504,
0x00000075,0x35784102,0x58637021,0x00000046
},
{
0x00432051,0x00468898,0x00021345,0x00468898,0x84057613,0x32460815,
0x00000072,0x53408217,0x08756214,0x00000036,0x27035614,0x62304715,
0x00000088,0x54182037,0x08761352,0x00000046
}
};
/*
	CA0 pinmux  0x0678 0x067c
	CA1 pinmux  0x06b8 0x06bc
	byte0 pinmux 0x06f4 0x06f8 0x06fc
	byte1 pinmux 0x0734 0x0738 0x073c
	byte2 pinmux 0x0774 0x0778 0x077c
	byte3 pinmux 0x07b4 0x07b8 0x07bc
*/
u16 reg_pinmux[]={0x0678,0x067c,0x06b8,0x06bc,0x06f4,0x06f8,0x06fc,0x0734,0x0738,0x073c,0x0774,0x0778,0x077c,0x07b4,0x07b8,0x07bc};

void ddrc_phy_pinmux_set()
{
	u32 *ptr=NULL;
	int i = 0;
	switch(dram_info.pinmux_type)
	{
	case DEFINE_PINMUX_CASE:
		ptr = &(val_pinmux[0][0]);
		break;
	case LPDDR3_PINMUX_CASE0:
		ptr = &(val_pinmux[1][0]);
		break;
	case LPDDR3_PINMUX_CASE1:
		ptr = &(val_pinmux[2][0]);
		break;
	case LPDDR4_PINMUX_CASE0:
		ptr = &(val_pinmux[3][0]);
		break;
	case LPDDR4_PINMUX_CASE1:
		ptr = &(val_pinmux[4][0]);
		break;
	default:while(1);
	}
	for(i=0; i<16; i++)
		__raw_writel(DMC_PHY0_(reg_pinmux[i]),ptr[i]);

}


void ddrc_ca_ds_set(u32 ds_val)
{
	reg_bit_set(DMC_PHY0_(0x0004),0,3,ds_val);
	reg_bit_set(DMC_PHY0_(0x0004),4,3,ds_val);
}
void ddrc_dq_ds_set(u32 ds_val)
{
	u32 fn=0;
	for(fn=0;fn<8;fn++)
	{
		(phy_tmg+fn)->cfg_io_ds_cfg &= ~(0x7<<0);
		(phy_tmg+fn)->cfg_io_ds_cfg |= (ds_val<<0);//rf_phy_io_ds_dq_drvn
		(phy_tmg+fn)->cfg_io_ds_cfg &= ~(0x7<<4);
		(phy_tmg+fn)->cfg_io_ds_cfg |= (ds_val<<4);//rf_phy_io_ds_dq_drvp
		__raw_writel(DMC_PHY0_(0x00f4+fn*0xc0),(phy_tmg+fn)->cfg_io_ds_cfg);
	}
}

void ddrc_dq_odt_set(u32 fn,u32 odt_val)
{
	(phy_tmg+fn)->cfg_io_ds_cfg &= ~(0x7<<8);//rf_phy_io_ds_dq_odtp
	(phy_tmg+fn)->cfg_io_ds_cfg &= ~(0x7<<12);
	(phy_tmg+fn)->cfg_io_ds_cfg |= (odt_val<<12);//rf_phy_io_ds_dq_odtn
	__raw_writel(DMC_PHY0_(0x00f4+fn*0xc0),(phy_tmg+fn)->cfg_io_ds_cfg);
}

void dram_dq_odt_set(u32 fn,u32 odt_val)
{
#if defined(VRCG_ON_EN)
	(dmc_dtmg+fn)->dmc_dtmg14 &= ~(0x7<<0);
	(dmc_dtmg+fn)->dmc_dtmg14 |= (odt_val<<0);
	__raw_writel(DMC_CTL0_(0x01b8+fn*0x60),(dmc_dtmg+fn)->dmc_dtmg14);
#else
	(dmc_dtmg+fn)->dmc_dtmg11 &= ~(0x7<<16);
	(dmc_dtmg+fn)->dmc_dtmg11 |= (odt_val<<16);
	__raw_writel(DMC_CTL0_(0x01ac+fn*0x60),(dmc_dtmg+fn)->dmc_dtmg11);
#endif
}









