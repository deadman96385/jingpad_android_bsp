#include <asm/types.h>
#include <common.h>
#include "asm/arch/clk_para_config.h"
#include "dmc_sprd_misc.h"
#include "dmc_sprd_r1p0.h"
#include "dmc_pin_cfg.h"
#include "dmc_sprd_r1p0_bist.h"

#define MAX_SCAN_STEP 0xff
#define TEST_MAGIC_NUMBER1 0x55555555
#define TEST_MAGIC_NUMBER2 0xaaaaaaaa

#define EADGE_SEARCH_ERROR -2147483648

#define AC_EADGE_SEARCH_OK			0
#define AC_EADGE_SEARCH_ADDR_ERR	-1
#define AC_EADGE_SEARCH_CMD_ERR		-2
#define AC_EADGE_SEARCH_SETTING_ERR	-3
#define AC_EADGE_SEARCH_NOFOUND_ERR	-4

#define SCAN_LEN 64
#define CLK_DMEM_SCAN_OFFSET 7

//#define USE_DQ_BIT_DESKEW
//#define USE_CA_BIT_DESKEW
//#define USE_CA_TRAINING
#define MIN_WINDOW 15


static int sipi_bist_simple_test(int cs)
{
	u32 chip_size;
	BIST_SIPI_PARA para;
	
	u32 bist_pattern_data[8] = {
		0xeeef7bde, 0x4210db6e, 0x92488888, 0xc7878787,
		0x33331c71, 0x00000055, 0x00000000, 0x00000000};
	
	para.len = BIST_RESERVE_SIZE/4;
	para.op_mode = BIST_OP_MODE_RW;


	sdram_chip_whole_size(&chip_size);

	if (chip_size>0x80000000-0x200000)
	{
		chip_size = 0x80000000-0x200000;
	}

	para.saddr = DDR_START_ADDR_PHY+chip_size-BIST_RESERVE_SIZE;

	memcpy(&para.pattern_data[0], &bist_pattern_data[0], 32);

	if (BIST_OK != dmc_bist_addr(BIST_TYPE_SIPI, &para))
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

#if 0
int find_dqsin_neg_right_eadge(int byte_index, int *eadge)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 dq_dll_reg_default;
	volatile u32 *pdqs_in_neg_dll;
	int step;
	u32 regval, tmp;
	int i;
	int last_status = 0;

	switch(byte_index)
	{
		case 0:
			pdqs_in_neg_dll = &pdmc->dmc_dqsin_neg_dll_ds0;
			break;
		case 1:
			pdqs_in_neg_dll = &pdmc->dmc_dqsin_neg_dll_ds1;
			break;
		case 2:
			pdqs_in_neg_dll = &pdmc->dmc_dqsin_neg_dll_ds2;
			break;
		case 3:
			pdqs_in_neg_dll = &pdmc->dmc_dqsin_neg_dll_ds3;
			break;
		default:
			return EADGE_SEARCH_ERROR;
	}

	dq_dll_reg_default = REG32(pdqs_in_neg_dll);

	for(i=0; i<SCAN_LEN; i++)
	{
		
		REG32(pdqs_in_neg_dll) = i;
		reset_dmc_fifo();
		dmc_sprd_delay(1);

		if (0 != sipi_bist_simple_test(0))
		{
			REG32(pdqs_in_neg_dll) = dq_dll_reg_default;
			reset_dmc_fifo();
			if (last_status == 1)
			{
				*eadge = i-1;
				return AC_EADGE_SEARCH_OK;
			}
			else
			{
				last_status = 0;
			}			
		}
		else
		{
			last_status = 1;
		}
		
	}
	return EADGE_SEARCH_ERROR;
}
#endif

#if 0
int find_dqsin_pst_right_eadge(int byte_index, int *eadge)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 dq_dll_reg_default;
	volatile u32 *pdqs_in_pst_dll;
	int step;
	int i;
	int last_status = 0;

	switch(byte_index)
	{
		case 0:
			pdqs_in_pst_dll = &pdmc->dmc_dqsin_pos_dll_ds0;
			break;
		case 1:
			pdqs_in_pst_dll = &pdmc->dmc_dqsin_pos_dll_ds1;
			break;
		case 2:
			pdqs_in_pst_dll = &pdmc->dmc_dqsin_pos_dll_ds2;
			break;
		case 3:
			pdqs_in_pst_dll = &pdmc->dmc_dqsin_pos_dll_ds3;
			break;
		default:
			return EADGE_SEARCH_ERROR;
	}

	dq_dll_reg_default = REG32(pdqs_in_pst_dll);

	for(i=0; i<SCAN_LEN; i++)
	{
		
		REG32(pdqs_in_pst_dll) = i;
		reset_dmc_fifo();
		dmc_sprd_delay(1);

		if (0 != sipi_bist_simple_test(0))
		{
			REG32(pdqs_in_pst_dll) = dq_dll_reg_default;
			reset_dmc_fifo();
			if (last_status == 1)
			{
				*eadge = i-1;
				return AC_EADGE_SEARCH_OK;
			}
			else
			{
				last_status = 0;
			}			
		}
		else
		{
			last_status = 1;
		}
		
	}
	return EADGE_SEARCH_ERROR;
}
#endif

#if 0
int find_dqsout_right_eadge(int byte_index, int *eadge)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 dq_dll_reg_default;
	volatile u32 *pdqs_out_dll;
	int i;
	int last_status = 0;

	switch(byte_index)
	{
		case 0:
			pdqs_out_dll = &pdmc->dmc_clkwr_dll_ds0;
			break;
		case 1:
			pdqs_out_dll = &pdmc->dmc_clkwr_dll_ds1;
			break;
		case 2:
			pdqs_out_dll = &pdmc->dmc_clkwr_dll_ds2;
			break;
		case 3:
			pdqs_out_dll = &pdmc->dmc_clkwr_dll_ds3;
			break;
		default:
			return EADGE_SEARCH_ERROR;
	}

	dq_dll_reg_default = REG32(pdqs_out_dll);

	for(i=0; i<SCAN_LEN; i++)
	{
		
		REG32(pdqs_out_dll) = i;
		reset_dmc_fifo();
		dmc_sprd_delay(1);

		if (0 != sipi_bist_simple_test(0))
		{
			REG32(pdqs_out_dll) = dq_dll_reg_default;
			reset_dmc_fifo();
			if (last_status == 1)
			{
				*eadge = i-1;
				return AC_EADGE_SEARCH_OK;
			}
			else
			{
				last_status = 0;
			}			
		}
		else
		{
			last_status = 1;
		}
		
	}
	return EADGE_SEARCH_ERROR;
}
#endif

#ifdef USE_CA_BIT_DESKEW
static int find_ac_right_eadge(int *eadge)
{
	
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 regval;
	u32 ac_dll_default = pdmc->dmc_clkwr_dll_ac;
	int last_status = 0;
	int i;	


	for (i=0; i<SCAN_LEN; i++)
	{
		pdmc->dmc_clkwr_dll_ac = i;
		reset_dmc_fifo();
		if (0 != sipi_bist_simple_test(0))
		{
			pdmc->dmc_clkwr_dll_ac = ac_dll_default;
			sdram_ac_train_reset();
			reset_dmc_fifo();
			if (1 == last_status)
			{
				*eadge = i-1;
				return AC_EADGE_SEARCH_OK;
			}
			else
			{
				last_status = 0;
			}
		}
		else
		{
			last_status = 1;
		}
		
	}
	return AC_EADGE_SEARCH_NOFOUND_ERR;
	
}
#endif


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

static void set_dqout_dll_byte_with_offset(int index, int val)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 *pdqout_dll_reg;
	u32 regval;
	u32 cycle_time;

	switch(index)
	{
		case 0:
			cycle_time = pdmc->dmc_sts_dll_ds0&0x7f;
			pdqout_dll_reg = &pdmc->dmc_clkwr_dll_ds0;
			break;
		case 1:
			cycle_time = pdmc->dmc_sts_dll_ds1&0x7f;
			pdqout_dll_reg = &pdmc->dmc_clkwr_dll_ds1;
			break;
		case 2:
			cycle_time = pdmc->dmc_sts_dll_ds2&0x7f;
			pdqout_dll_reg = &pdmc->dmc_clkwr_dll_ds2;
			break;
		case 3:
			cycle_time = pdmc->dmc_sts_dll_ds3&0x7f;
			pdqout_dll_reg = &pdmc->dmc_clkwr_dll_ds3;
			break;
		default:
			break;
	}

	regval = REG32(pdqout_dll_reg);

	if (((val/4)-cycle_time)>=0)
	{
		regval = u32_bits_set(regval, 16, 8, (val*4-cycle_time)/4);
		regval = u32_bits_set(regval, 0, 8, 0x20);
		regval = u32_bits_set(regval, 30, 2, 2);
	}
	else
	{
		regval = u32_bits_set(regval, 16, 8, (cycle_time - val*4)/4);
		regval = u32_bits_set(regval, 0, 8, 0x20);
		regval = u32_bits_set(regval, 30, 2, 3);
	}

	REG32(pdqout_dll_reg) = regval;
	switch(index)
	{
		case 0:
			pdmc->dmc_cfg_dll_ds0 |= 1<<11;
			dmc_sprd_delay(1);
			pdmc->dmc_cfg_dll_ds0 &= ~(1<<11);
			break;
		case 1:
			pdmc->dmc_cfg_dll_ds1 |= 1<<11;
			dmc_sprd_delay(1);
			pdmc->dmc_cfg_dll_ds1 &= ~(1<<11);
			break;
		case 2:
			pdmc->dmc_cfg_dll_ds2 |= 1<<11;
			dmc_sprd_delay(1);
			pdmc->dmc_cfg_dll_ds2 &= ~(1<<11);
			break;
		case 3:
			pdmc->dmc_cfg_dll_ds3 |= 1<<11;
			dmc_sprd_delay(1);
			pdmc->dmc_cfg_dll_ds3 &= ~(1<<11);
			break;
		default:
			break;
	}
	reset_dmc_fifo();
}

static void set_dqout_dll_byte_without_offset(int index, int val)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;

	switch(index)
	{
		case 0:
			pdmc->dmc_clkwr_dll_ds0 = val&0xff;
			break;
		case 1:
			pdmc->dmc_clkwr_dll_ds1 = val&0xff;
			break;
		case 2:
			pdmc->dmc_clkwr_dll_ds2 = val&0xff;
			break;
		case 3:
			pdmc->dmc_clkwr_dll_ds3 = val&0xff;
			break;
		default:
			break;
	}
	reset_dmc_fifo();
}

static void set_dqin_neg_dll_byte_with_offset(int index, int val)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 *pdqin_dll_reg;
	u32 regval;
	u32 cycle_time;
	char strbuf[64];

	switch(index)
	{
		case 0:
			cycle_time = pdmc->dmc_sts_dll_ds0&0x7f;
			pdqin_dll_reg = &pdmc->dmc_dqsin_neg_dll_ds0;
			break;
		case 1:
			cycle_time = pdmc->dmc_sts_dll_ds1&0x7f;
			pdqin_dll_reg = &pdmc->dmc_dqsin_neg_dll_ds1;
			break;
		case 2:
			cycle_time = pdmc->dmc_sts_dll_ds2&0x7f;
			pdqin_dll_reg = &pdmc->dmc_dqsin_neg_dll_ds2;
			break;
		case 3:
			cycle_time = pdmc->dmc_sts_dll_ds3&0x7f;
			pdqin_dll_reg = &pdmc->dmc_dqsin_neg_dll_ds3;
			break;
		default:
			break;
	}
	
#if 0
	dmc_print_str("cycle:");	
	dmc_print_str(itoa_simple(cycle_time, strbuf, 16));
	dmc_print_str("\r\n");

	dmc_print_str("val:");	
	dmc_print_str(itoa_simple(val, strbuf, 16));
	dmc_print_str("\r\n");
#endif

	regval = REG32(pdqin_dll_reg);

	if ((val*4)>=cycle_time)
	{
		regval = u32_bits_set(regval, 16, 8, (val*4-cycle_time)/4);
		regval = u32_bits_set(regval, 0, 8, 0x20);
		regval = u32_bits_set(regval, 30, 2, 2);
	}
	else
	{
		regval = u32_bits_set(regval, 16, 8, (cycle_time - val*4)/4);
		regval = u32_bits_set(regval, 0, 8, 0x20);
		regval = u32_bits_set(regval, 30, 2, 3);
	}

	REG32(pdqin_dll_reg) = regval;

	switch(index)
	{
		case 0:
			pdmc->dmc_cfg_dll_ds0 |= 1<<11;
			dmc_sprd_delay(1);
			pdmc->dmc_cfg_dll_ds0 &= ~(1<<11);
			break;
		case 1:
			pdmc->dmc_cfg_dll_ds1 |= 1<<11;
			dmc_sprd_delay(1);
			pdmc->dmc_cfg_dll_ds1 &= ~(1<<11);
			break;
		case 2:
			pdmc->dmc_cfg_dll_ds2 |= 1<<11;
			dmc_sprd_delay(1);
			pdmc->dmc_cfg_dll_ds2 &= ~(1<<11);
			break;
		case 3:
			pdmc->dmc_cfg_dll_ds3 |= 1<<11;
			dmc_sprd_delay(1);
			pdmc->dmc_cfg_dll_ds3 &= ~(1<<11);
			break;
		default:
			break;
	}
	
	reset_dmc_fifo();
}

static void set_dqin_neg_dll_byte_without_offset(int index, int val)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;

	switch(index)
	{
		case 0:
			pdmc->dmc_dqsin_neg_dll_ds0 = val&0xff;
			break;
		case 1:
			pdmc->dmc_dqsin_neg_dll_ds1 = val&0xff;
			break;
		case 2:
			pdmc->dmc_dqsin_neg_dll_ds2 = val&0xff;
			break;
		case 3:
			pdmc->dmc_dqsin_neg_dll_ds3 = val&0xff;
			break;
		default:
			break;
	}
	reset_dmc_fifo();
}

static void set_dqin_pst_dll_byte_with_offset(int index, int val)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 *pdqin_dll_reg;
	u32 regval;
	u32 cycle_time;

	switch(index)
	{
		case 0:
			cycle_time = pdmc->dmc_sts_dll_ds0&0x7f;
			pdqin_dll_reg = &pdmc->dmc_dqsin_pos_dll_ds0;
			break;
		case 1:
			cycle_time = pdmc->dmc_sts_dll_ds1&0x7f;
			pdqin_dll_reg = &pdmc->dmc_dqsin_pos_dll_ds1;
			break;
		case 2:
			cycle_time = pdmc->dmc_sts_dll_ds2&0x7f;
			pdqin_dll_reg = &pdmc->dmc_dqsin_pos_dll_ds2;
			break;
		case 3:
			cycle_time = pdmc->dmc_sts_dll_ds3&0x7f;
			pdqin_dll_reg = &pdmc->dmc_dqsin_pos_dll_ds3;
			break;
		default:
			break;
	}

	regval = REG32(pdqin_dll_reg);

	if ((val*4)>=cycle_time)
	{
		regval = u32_bits_set(regval, 16, 8, (val*4-cycle_time)/4);
		regval = u32_bits_set(regval, 0, 8, 0x20);
		regval = u32_bits_set(regval, 30, 2, 2);
	}
	else
	{
		regval = u32_bits_set(regval, 16, 8, (cycle_time - val*4)/4);
		regval = u32_bits_set(regval, 0, 8, 0x20);
		regval = u32_bits_set(regval, 30, 2, 3);
	}

	REG32(pdqin_dll_reg) = regval;

	switch(index)
	{
		case 0:
			pdmc->dmc_cfg_dll_ds0 |= 1<<11;
			dmc_sprd_delay(1);
			pdmc->dmc_cfg_dll_ds0 &= ~(1<<11);
			break;
		case 1:
			pdmc->dmc_cfg_dll_ds1 |= 1<<11;
			dmc_sprd_delay(1);
			pdmc->dmc_cfg_dll_ds1 &= ~(1<<11);
			break;
		case 2:
			pdmc->dmc_cfg_dll_ds2 |= 1<<11;
			dmc_sprd_delay(1);
			pdmc->dmc_cfg_dll_ds2 &= ~(1<<11);
			break;
		case 3:
			pdmc->dmc_cfg_dll_ds3 |= 1<<11;
			dmc_sprd_delay(1);
			pdmc->dmc_cfg_dll_ds3 &= ~(1<<11);
			break;
		default:
			break;
	}
	
	reset_dmc_fifo();
}

static void set_dqin_pst_dll_byte_without_offset(int index, int val)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;

	switch(index)
	{
		case 0:
			pdmc->dmc_dqsin_pos_dll_ds0 = val&0xff;
			break;
		case 1:
			pdmc->dmc_dqsin_pos_dll_ds1 = val&0xff;
			break;
		case 2:
			pdmc->dmc_dqsin_pos_dll_ds2 = val&0xff;
			break;
		case 3:
			pdmc->dmc_dqsin_pos_dll_ds3 = val&0xff;
			break;
		default:
			break;
	}
	reset_dmc_fifo();
}

static void set_ca_dll_byte_with_offset(int val)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 regval = pdmc->dmc_clkwr_dll_ac;
	u32 cycle_time = pdmc->dmc_sts_dll_ac&0x7f;	

	if ((val*4)>=cycle_time)
	{
		regval = u32_bits_set(regval, 16, 8, (val*4-cycle_time)/4);
		regval = u32_bits_set(regval, 0, 8, 0x20);
		regval = u32_bits_set(regval, 30, 2, 2);
	}
	else
	{
		regval = u32_bits_set(regval, 16, 8, (cycle_time - val*4)/4);
		regval = u32_bits_set(regval, 0, 8, 0x20);
		regval = u32_bits_set(regval, 30, 2, 3);
	}

	pdmc->dmc_clkwr_dll_ac = regval;
	reset_dmc_fifo();
}

static void set_ca_dll_byte_without_offset(int val)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;

	pdmc->dmc_clkwr_dll_ac = val&0xff;
	
	reset_dmc_fifo();
}



#ifdef USE_CA_BIT_DESKEW
static u8 get_min_array_val(u8 array[], int size)
{
	u8 val=255;
	int i;

	for(i=0; i<size; i++)
	{
		if(val > array[i])
		{
			val = array[i];
		}
	}
	return val;
}


static int ac_bit_deskew(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	int right_eadge = 255, tmp_eadge;
	u8 right_margin[10], min_offset;
	u32 ac_out0_default, ac_out1_default;
	u32 tmp;
	int i,j;
	int ret;

	ac_out0_default = pdmc->dmc_addr_out0_dll_ac;
	ac_out1_default = pdmc->dmc_addr_out1_dll_ac;

	for (i=0; i<3; i++)
	{
		ret = find_ac_right_eadge(&tmp_eadge);
		if (0 == ret)
		{			
			if (tmp_eadge<right_eadge)
			{
				right_eadge = tmp_eadge;
			}
		}
	}

	set_ca_dll_byte_without_offset(right_eadge);

	reset_dmc_fifo();

	/*ca0~ca7*/
	for (i=0; i<8; i++)
	{
		right_margin[i] = 0;
		for(j=(ac_out0_default>>(i*4))&0x7+1; j<8; j++)
		{
			tmp = ac_out0_default&(~(0xf<<(i*4)));
			pdmc->dmc_addr_out0_dll_ac = j<<(i*4)|tmp;
			reset_dmc_fifo();
			dmc_sprd_delay(1);

			if (0 != sipi_bist_simple_test(0))
			{
				right_margin[i] = j;
				pdmc->dmc_addr_out0_dll_ac = ac_out0_default;
				sdram_ac_train_reset();
				break;
			}					
			
		}
		if (0 == right_margin[i])
		{
			right_margin[i] = 7;
		}	
		
	}

	pdmc->dmc_addr_out0_dll_ac = ac_out0_default;

	/*ca8~ca9*/
	for (i=8; i<10; i++)
	{
		right_margin[i] = 0;
		for(j=(ac_out1_default>>((i-8)*4))&0x7+1; j<8; j++)
		{
			tmp = ac_out1_default&(~(0xf<<((i-8)*4)));
			pdmc->dmc_addr_out1_dll_ac = j<<((i-8)*4)|tmp;
			reset_dmc_fifo();
			dmc_sprd_delay(1);

			if (0 != sipi_bist_simple_test(0))
			{
				right_margin[i] = j;
				pdmc->dmc_addr_out1_dll_ac = ac_out1_default;
				sdram_ac_train_reset();
				break;
			}				
			
		}
		if (0 == right_margin[i])
		{
			right_margin[i] = 7;
		}
	}

	min_offset = get_min_array_val(&right_margin[0], 10);

	pdmc->dmc_addr_out0_dll_ac = (right_margin[0]-min_offset) |
								((right_margin[1]-min_offset)<<4) |
								((right_margin[2]-min_offset)<<(4*2)) |
								((right_margin[3]-min_offset)<<(4*3)) |
								((right_margin[4]-min_offset)<<(4*4)) |
								((right_margin[5]-min_offset)<<(4*5)) |
								((right_margin[6]-min_offset)<<(4*6)) |
								((right_margin[7]-min_offset)<<(4*7));
	pdmc->dmc_addr_out1_dll_ac = (right_margin[8]-min_offset) | ((right_margin[9]-min_offset)<<4);	
	sdram_ac_train_reset();
	reset_dmc_fifo();
	return 0;
}
#endif


static void dqin_bit_offset_adjust(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	pdmc->dmc_data_in_dll_ds0 = 0x77777777;
	pdmc->dmc_data_in_dll_ds1 = 0x77777777;
	pdmc->dmc_data_in_dll_ds2 = 0x77777777;
	pdmc->dmc_data_in_dll_ds3 = 0x77777777;
}

static void dqin_bit_offset_restore(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	pdmc->dmc_data_in_dll_ds0 = 0;
	pdmc->dmc_data_in_dll_ds1 = 0;
	pdmc->dmc_data_in_dll_ds2 = 0;
	pdmc->dmc_data_in_dll_ds3 = 0;
}

/*scan byte dqs in post delay*/
int dmc_scan_byte_dqs_in_neg_online(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	int i,j;
	int record[8];
	int middle, middle_record[4];
	volatile u32 *pdqs_in_neg_dll;
	int ret;
	int lastval, startok, endok;
	char strbuf[64];
	int err_flag = 0;
	u32 neg_dll_ds0_default = pdmc->dmc_dqsin_neg_dll_ds0;
	u32 neg_dll_ds1_default = pdmc->dmc_dqsin_neg_dll_ds1;
	u32 neg_dll_ds2_default = pdmc->dmc_dqsin_neg_dll_ds2;
	u32 neg_dll_ds3_default = pdmc->dmc_dqsin_neg_dll_ds3;

	

	dqin_bit_offset_adjust();

	for(i=0; i<4; i++)
	{
		lastval = 0;
		startok = 0;
		endok = 0;
		switch(i)
		{
			case 0:
				pdqs_in_neg_dll = &pdmc->dmc_dqsin_neg_dll_ds0;
				break;
			case 1:
				pdqs_in_neg_dll = &pdmc->dmc_dqsin_neg_dll_ds1;
				break;
			case 2:
				pdqs_in_neg_dll = &pdmc->dmc_dqsin_neg_dll_ds2;
				break;
			case 3:
				pdqs_in_neg_dll = &pdmc->dmc_dqsin_neg_dll_ds3;
				break;
			default:
				return EADGE_SEARCH_ERROR;
		}
		for(j=0; j<SCAN_LEN; j++)
		{
			REG32(pdqs_in_neg_dll) = j;
			reset_dmc_fifo();
			dmc_sprd_delay(1);

			if (0 != sipi_bist_simple_test(0))
			{
				//dmc_print_str("F");
				if (lastval == 1)
				{
					endok = j-1;
					//dmc_print_str("\r\n");
					break;
				}
				else
				{
					lastval = 0;
				}			
			}
			else
			{
				//dmc_print_str("P");
				if (0 == lastval)
				{
					startok = j;
				}
				lastval = 1;
			}
		}
		//dmc_print_str("\r\n");
		if (j == SCAN_LEN)
		{
			//dmc_print_str("Scan din neg error1\r\n");
			err_flag = 1;
			break;
		}

		if ((endok-startok)>MIN_WINDOW)
		{
			middle = (startok+endok)/2;
			middle_record[i] = middle;
			set_dqin_neg_dll_byte_without_offset(i, middle);
			reset_dmc_fifo();
		}
		else
		{
			//dmc_print_str("Scan din neg error2\r\n");
			err_flag = 2;
			break;
		}
#if 0
		dmc_print_str("\r\nstartok:");	
		dmc_print_str(itoa_simple(startok, strbuf, 16));
		dmc_print_str("\r\nendok:");	
		dmc_print_str(itoa_simple(endok, strbuf, 16));
		dmc_print_str("\r\n");
#endif
	}

	dqin_bit_offset_restore();

	if (0 != err_flag)
	{
		pdmc->dmc_dqsin_neg_dll_ds0 = neg_dll_ds0_default;
		pdmc->dmc_dqsin_neg_dll_ds1 = neg_dll_ds1_default;
		pdmc->dmc_dqsin_neg_dll_ds2 = neg_dll_ds2_default;
		pdmc->dmc_dqsin_neg_dll_ds3 = neg_dll_ds3_default;
		reset_dmc_fifo();
		//dmc_print_str("***************scan dqs in neg fail**********************\r\n");
	}
	else
	{
		set_dqin_neg_dll_byte_with_offset(0, middle_record[0]-7);
		set_dqin_neg_dll_byte_with_offset(1, middle_record[1]-7);
		set_dqin_neg_dll_byte_with_offset(2, middle_record[2]-7);
		set_dqin_neg_dll_byte_with_offset(3, middle_record[3]-7);
		reset_dmc_fifo();
	}
	
	return 0;
}

/*scan byte dqs in pre delay*/
int dmc_scan_byte_dqs_in_pst_online(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	int i,j;
	int record[8];
	int middle, middle_record[4];
	volatile u32 *pdqs_in_pst_dll;
	int ret;
	int lastval, startok, endok;
	int err_flag = 0;

	u32 pst_dll_ds0_default = pdmc->dmc_dqsin_pos_dll_ds0;
	u32 pst_dll_ds1_default = pdmc->dmc_dqsin_pos_dll_ds1;
	u32 pst_dll_ds2_default = pdmc->dmc_dqsin_pos_dll_ds2;
	u32 pst_dll_ds3_default = pdmc->dmc_dqsin_pos_dll_ds3;

	dqin_bit_offset_adjust();

	for(i=0; i<4; i++)
	{
		lastval = 0;
		startok = 0;
		endok = 0;
		switch(i)
		{
			case 0:
				pdqs_in_pst_dll = &pdmc->dmc_dqsin_pos_dll_ds0;
				break;
			case 1:
				pdqs_in_pst_dll = &pdmc->dmc_dqsin_pos_dll_ds1;
				break;
			case 2:
				pdqs_in_pst_dll = &pdmc->dmc_dqsin_pos_dll_ds2;
				break;
			case 3:
				pdqs_in_pst_dll = &pdmc->dmc_dqsin_pos_dll_ds3;
				break;
			default:
				return EADGE_SEARCH_ERROR;
		}
		for(j=0; j<SCAN_LEN; j++)
		{
			REG32(pdqs_in_pst_dll) = j;
			reset_dmc_fifo();
			dmc_sprd_delay(1);

			if (0 != sipi_bist_simple_test(0))
			{
				if (lastval == 1)
				{
					endok = j-1;
					break;
				}
				else
				{
					lastval = 0;
				}			
			}
			else
			{
				if (0 == lastval)
				{
					startok = j;
				}
				lastval = 1;
			}
		}
		if (j == SCAN_LEN)
		{
			//dmc_print_str("Scan error di pst 1\r\n");
			err_flag = 1;
			break;
		}
		if ((endok-startok)>MIN_WINDOW)
		{
			middle = (startok+endok)/2;
			middle_record[i] = middle;
			set_dqin_pst_dll_byte_without_offset(i, middle);
			reset_dmc_fifo();			
		}
		else
		{
			//dmc_print_str("Scan error di pst 2\r\n");
			err_flag = 2;
			break;
		}
	}

	dqin_bit_offset_restore();

	if (0 != err_flag)
	{
		pdmc->dmc_dqsin_pos_dll_ds0 = pst_dll_ds0_default;
		pdmc->dmc_dqsin_pos_dll_ds1 = pst_dll_ds1_default;
		pdmc->dmc_dqsin_pos_dll_ds2 = pst_dll_ds2_default;
		pdmc->dmc_dqsin_pos_dll_ds3 = pst_dll_ds3_default;
		reset_dmc_fifo();
	}
	else
	{
		set_dqin_pst_dll_byte_with_offset(0, middle_record[0]-7);
		set_dqin_pst_dll_byte_with_offset(1, middle_record[1]-7);
		set_dqin_pst_dll_byte_with_offset(2, middle_record[2]-7);
		set_dqin_pst_dll_byte_with_offset(3, middle_record[3]-7);
		reset_dmc_fifo();
	}
	
	return 0;
}

/*scan byte dqs out delay*/
int dmc_scan_byte_dqs_out_online(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	int i,j;
	int middle, record[4];
	volatile u32 *pdqs_out_dll;
	int ret;
	int lastval, starti_ok, endi;
	int err_flag = 0;

	u32 out_dll_ds0_default = pdmc->dmc_clkwr_dll_ds0;
	u32 out_dll_ds1_default = pdmc->dmc_clkwr_dll_ds1;
	u32 out_dll_ds2_default = pdmc->dmc_clkwr_dll_ds2;
	u32 out_dll_ds3_default = pdmc->dmc_clkwr_dll_ds3;

	dmc_set_dmdqs_out_offset(7);

	for(i=0; i<4; i++)
	{
		lastval = -1;
		starti_ok = -1;
		endi = -1;
		switch(i)
		{
			case 0:
				pdqs_out_dll = &pdmc->dmc_clkwr_dll_ds0;
				break;
			case 1:
				pdqs_out_dll = &pdmc->dmc_clkwr_dll_ds1;
				break;
			case 2:
				pdqs_out_dll = &pdmc->dmc_clkwr_dll_ds2;
				break;
			case 3:
				pdqs_out_dll = &pdmc->dmc_clkwr_dll_ds3;
				break;
			default:
				return EADGE_SEARCH_ERROR;
		}
		for(j=0; j<SCAN_LEN; j++)
		{
			REG32(pdqs_out_dll) = j;
			reset_dmc_fifo();
			dmc_sprd_delay(1);

			if (0 != sipi_bist_simple_test(0))
			{
				if ((lastval == 1) && (starti_ok > 0))
				{
					endi = j-1;
					break;
				}
				lastval = 0;
			}
			else
			{
				if (0 == lastval)
				{
					starti_ok = j;
				}
				lastval = 1;
			}
		}
		if (j == SCAN_LEN)
		{
			//dmc_print_str("Scan error do 1\r\n");
			err_flag = 1;
			break;
		}

		if ((endi-starti_ok)>MIN_WINDOW)
		{
			record[i] = (starti_ok+endi)/2;
			set_dqout_dll_byte_without_offset(i, record[i]);
			reset_dmc_fifo();	
		}
		else
		{
			//dmc_print_str("Scan error do 2\r\n");
			err_flag = 2;
			break;
		}
	}

	dmc_set_dmdqs_out_offset(0);

	if (0 !=  err_flag)
	{
		pdmc->dmc_clkwr_dll_ds0 = out_dll_ds0_default;
		pdmc->dmc_clkwr_dll_ds1 = out_dll_ds1_default;
		pdmc->dmc_clkwr_dll_ds2 = out_dll_ds2_default;
		pdmc->dmc_clkwr_dll_ds3 = out_dll_ds3_default;
		reset_dmc_fifo();
	}
	else
	{
		set_dqout_dll_byte_with_offset(0, record[0]-7);
		set_dqout_dll_byte_with_offset(1, record[1]-7);
		set_dqout_dll_byte_with_offset(2, record[2]-7);
		set_dqout_dll_byte_with_offset(3, record[3]-7);
		reset_dmc_fifo();
	}
	
	return 0;
}

#ifdef USE_CA_TRAINING
/*scan AC delay line*/
int dmc_scan_ac_online(void)
{
	int i;
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 ca_dll_default = pdmc->dmc_clkwr_dll_ac;
	u32 regval;
	int middle;
	int lastval = -1, starti_ok=-1, endi=-1;
	int ret;

	regval = pdmc->dmc_cmd_out0_dll_ac;
	regval = u32_bits_set(regval, 24, 3, CLK_DMEM_SCAN_OFFSET);
	regval = u32_bits_set(regval, 28, 3, CLK_DMEM_SCAN_OFFSET);
	pdmc->dmc_cmd_out0_dll_ac = regval;

#ifdef USE_CA_BIT_DESKEW
	if (0 != ac_bit_deskew())
	{
		return -1;
	}
#endif	


	for(i=0; i<SCAN_LEN; i++)
	{
		pdmc->dmc_clkwr_dll_ac = i;
		reset_dmc_fifo();
		dmc_sprd_delay(1);

		if (0 != sipi_bist_simple_test(0))
		{
			if ((lastval == 1)&&(starti_ok>0))
			{
				endi =i-1;
				break;
			}
			pdmc->dmc_clkwr_dll_ac = ca_dll_default;
			reset_dmc_fifo();
			sdram_ac_train_reset();
			reset_dmc_fifo();
			lastval = 0;				
		}
		else
		{
			if (0 == lastval)
			{
				starti_ok = i;
			}
			lastval = 1;
		}		
			
	}

	regval = pdmc->dmc_cmd_out0_dll_ac;
	regval = u32_bits_set(regval, 24, 3, 0);
	regval = u32_bits_set(regval, 28, 3, 0);
	pdmc->dmc_cmd_out0_dll_ac = regval;

	set_ca_dll_byte_with_offset((starti_ok+endi)/2-CLK_DMEM_SCAN_OFFSET);	
	reset_dmc_fifo();
	return 0;
}
#endif

int ddr_scan_online_sprd_r1p0(void)
{
	
	if (0 != sipi_bist_simple_test(0))
	{
		//dmc_print_str("before scan DDR is fail\r\n");
		return -1;
	}
#if 1
	if (0 != dmc_scan_byte_dqs_in_pst_online())
	{
		return -1;
	}	
#endif

#if 1
	if (0 != dmc_scan_byte_dqs_in_neg_online())
	{
		return -1;
	}
#endif
#if 1
	if (0 != dmc_scan_byte_dqs_out_online())
	{
		return -1;
	}
#endif
#ifdef USE_CA_TRAINING
	if (0 != dmc_scan_ac_online())
	{
		return -1;
	}	
#endif	
	return 0;	
}

