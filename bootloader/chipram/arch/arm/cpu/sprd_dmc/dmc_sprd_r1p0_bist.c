#include <asm/types.h>
#include "asm/arch/clk_para_config.h"
#include "dmc_sprd_r1p0.h"
#include "dmc_sprd_misc.h"
#include "dmc_sprd_r1p0_bist.h"

void dmc_bist_clear_status(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 regval;

	regval = pdmc->dmc_bist[0];
	regval = u32_bits_set(regval, 13, 1, 1);
	pdmc->dmc_bist[0] = regval;
	dmc_sprd_delay(1);
	regval = pdmc->dmc_bist[0];
	regval = u32_bits_set(regval, 13, 1, 0);
	pdmc->dmc_bist[0] = regval;
}

static int bist_set_opmode_bits(u32 *regval, BIST_OP_MODE op_mode)
{
	u32 val = *regval;
	switch(op_mode)
	{
		case BIST_OP_MODE_RW:
			u32_bits_set(val, 4, 2, 0);
			break;
		case BIST_OP_MODE_WRONLY:
			u32_bits_set(val, 4, 2, 1);
			break;
		case BIST_OP_MODE_RDONLY:
			u32_bits_set(val, 4, 2, 2);
			break;
		default:
			return -1;
	}
	*regval = val;
	return 0;
}


void dmc_bist_dump_fail_info(void)
{
}

void dmc_bist_set_saddr(DRAM_JEDEC_ADDR *saddr)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 val;

	val = (saddr->column) | (saddr->bank<<12) | (saddr->cs<<15) | (saddr->row<<16);
	pdmc->dmc_bist[2] = val;	
}

int dmc_bist_addr(BIST_TYPE bist_type, void *para)
{
	u32 regval;
	int tout;
	int ret;
	u32 burstlen;
	u32 saddr = ((BIST_LFSR_PARA *)para)->saddr;
	DRAM_JEDEC_ADDR jedec_addr;
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;

	dmc_bist_clear_status();

	switch(((pdmc->dmc_cfg0)>>5)&0x7)
	{
		case 0:
			burstlen = 1;
			break;
		case 1:
			burstlen = 2;
			break;
		case 2:
			burstlen = 4;
			break;
		case 3:
			burstlen = 8;
			break;
		case 4:
			burstlen = 16;
			break;
		default:
			return BIST_PARA_ERR;
	}

	if (0 != saddr%(burstlen*sdram_chip_data_width()/8))
	{
		dmc_print_str("Data len must aligned with burstlen*datawidth/8\n");
		return BIST_PARA_ERR;
	}

	if (0 != trans_addr_to_jedec_addr(saddr, &jedec_addr))
	{
		return BIST_PARA_ERR;
	}

	dmc_bist_set_saddr(&jedec_addr);

	/*disable lowpower and dfs*/
	regval = pdmc->dmc_lpcfg1;
	regval = u32_bits_set(regval, 0, 3, 0);
	pdmc->dmc_lpcfg1 = regval;

	regval = pdmc->dmc_lpcfg2;
	regval = u32_bits_set(regval, 0, 1, 0);
	pdmc->dmc_lpcfg2 = regval;

	regval = pdmc->dmc_bist[0];
	/*set burst length*/
	regval = u32_bits_set(regval, 16, 10, burstlen);
	/*disable max addr en*/
	regval = u32_bits_set(regval, 12, 1, 0);

	switch(bist_type)
	{
		case BIST_TYPE_LFSR:
			/*set bist type*/
			regval = u32_bits_set(regval, 8, 2, BIST_TYPE_LFSR);
			/*set op mode*/
			bist_set_opmode_bits(&regval, ((BIST_LFSR_PARA *)para)->op_mode);
			/*enable bist*/
			regval = u32_bits_set(regval, 0, 1, 1);
			pdmc->dmc_bist[0] = regval;
			/*set test length*/
			pdmc->dmc_bist[1] = ((BIST_LFSR_PARA *)para)->len;
			/*start bist*/
			regval = pdmc->dmc_bist[0];
			regval = u32_bits_set(regval, 1, 1, 1);
			pdmc->dmc_bist[0] = regval;
			break;
		case BIST_TYPE_SIPI:
			/*set bist type*/
			regval = u32_bits_set(regval, 8, 2, BIST_TYPE_SIPI);
			/*set op mode*/
			bist_set_opmode_bits(&regval, ((BIST_SIPI_PARA *)para)->op_mode);
			/*enable bist*/
			regval = u32_bits_set(regval, 0, 1, 1);
			pdmc->dmc_bist[0] = regval;
			/*set test length*/
			pdmc->dmc_bist[1] = ((BIST_SIPI_PARA *)para)->len;
			/*set patern data*/
			memcpy(&(pdmc->dmc_bist[7]), &(((BIST_SIPI_PARA *)para)->pattern_data[0]), 32);
			/*start bist*/
			regval = pdmc->dmc_bist[0];
			regval = u32_bits_set(regval, 1, 1, 1);
			pdmc->dmc_bist[0] = regval;
			break;
		case BIST_TYPE_USRDEF:
			/*set bist type*/
			regval = u32_bits_set(regval, 8, 2, BIST_TYPE_USRDEF);
			/*set op mode*/
			bist_set_opmode_bits(&regval, ((BIST_USRDEF_PARA *)para)->op_mode);
			/*enable bist*/
			regval = u32_bits_set(regval, 0, 1, 1);
			pdmc->dmc_bist[0] = regval;
			/*set test length*/
			pdmc->dmc_bist[1] = ((BIST_USRDEF_PARA *)para)->len;
			/*set patern data*/
			memcpy(&(pdmc->dmc_bist[7]), &(((BIST_USRDEF_PARA *)para)->pattern_data[0]), 32);
			/*start bist*/
			regval = pdmc->dmc_bist[0];
			regval = u32_bits_set(regval, 1, 1, 1);
			pdmc->dmc_bist[0] = regval;
			break;
		case BIST_TYPE_USRDEF_INC:
			/*set bist type*/
			regval = u32_bits_set(regval, 8, 2, BIST_TYPE_USRDEF_INC);
			/*set op mode*/
			bist_set_opmode_bits(&regval, ((BIST_USRDEF_INC_PARA *)para)->op_mode);
			/*enable bist*/
			regval = u32_bits_set(regval, 0, 1, 1);
			pdmc->dmc_bist[0] = regval;
			/*set test length*/
			pdmc->dmc_bist[1] = ((BIST_USRDEF_INC_PARA *)para)->len;
			/*set patern data*/
			memcpy(&(pdmc->dmc_bist[7]), &(((BIST_USRDEF_INC_PARA *)para)->pattern_data[0]), 32);
			/*start bist*/
			regval = pdmc->dmc_bist[0];
			regval = u32_bits_set(regval, 1, 1, 1);
			pdmc->dmc_bist[0] = regval;
			break;
		default:
			return BIST_PARA_ERR;
	}
	tout = (pdmc->dmc_bist[1]-1)*2;

	while(tout > 0)
	{
		regval = pdmc->dmc_bist[0];
		if (regval & 0x4)
			break;
		tout--;
	}

	if (tout<1)
	{
		return BIST_TOUT;
	}

	/*Bug bist ok maybe not be set when done bit has beed set. So read it again to walk around the bug*/
	regval = pdmc->dmc_bist[0];
	if (regval & 0x8)
	{
		return BIST_OK;
	}
	else
	{
		return BIST_FAIL;
	}
	
}

void dmc_bist_disable(void)
{
	PIKE_DMC_REG_INFO_PTR pdmc = (PIKE_DMC_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 regval;

	dmc_bist_clear_status();

	regval = pdmc->dmc_bist[0];
	/*disable bist*/
	regval = u32_bits_set(regval, 0, 1, 0);
	pdmc->dmc_bist[0] = regval;
}

