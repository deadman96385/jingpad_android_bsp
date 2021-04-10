#include <asm/types.h>
#include <asm/arch/clk_para_config.h>
#include <common.h>
#include "dmc_sprd_r2p0.h"
#include "dmc_sprd_r2p0_bist.h"

extern DRAM_CHIP_INFO ddr_chip_cur;

int dmc_bist_test(BIST_TYPE bist_type, void *para)
{
	u32 regval;
	int tout;
	u32 burstlen;
	u32 dcfg0_bkup;
	u32 lfsr_seed = 0;
	u32 * pattern_dptr = NULL;
	u32 len = ((BIST_LFSR_PARA *)para)->len;
	u32 saddr = ((BIST_LFSR_PARA *)para)->saddr;
	BIST_OP_MODE op_mode = ((BIST_LFSR_PARA *)para)->op_mode;
	DRAM_JEDEC_ADDR jedec_addr;
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	DRAM_JEDEC_INFO *cs_info;

	switch(bist_type)
	{
		case BIST_TYPE_LFSR:
			lfsr_seed = ((BIST_LFSR_PARA *)para)->seed_val;
			break;
		case BIST_TYPE_SIPI:
			pattern_dptr = &(((BIST_SIPI_PARA *)para)->pattern_data[0]);
			break;
		case BIST_TYPE_USRDEF:
			pattern_dptr = &(((BIST_USRDEF_PARA *)para)->pattern_data[0]);
			break;
		case BIST_TYPE_USRDEF_INC:
			pattern_dptr = &(((BIST_USRDEF_INC_PARA *)para)->pattern_data[0]);
			break;
		default:
			return BIST_PARA_ERR;
	}
	regval = ((pdmc->dmc_cfg0)>>4)&0x7;
	if (regval <= 4)
	{
		burstlen = (1<<regval);
	}
	else
	{
		return BIST_PARA_ERR;
	}

	if (op_mode >= BIST_OP_MODE_RESERVED)
	{
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

	/* Step2:set bist pattern use default bist pattern*/
	pdmc->dmc_bist[6] = lfsr_seed;
#ifdef USRDEF_BIST_PATTERN
	if (pattern_dptr != NULL)
	{
		memcpy(&(pdmc->dmc_bist[7]), pattern_dptr, 32);
	}
#endif
	/* Step3: set colum an row*/
	if (ddr_chip_cur.unsymmetry)
	{
		dcfg0_bkup = regval = pdmc->dmc_dcfg0;
		regval = u32_bits_set(regval, 4, 3, (ddr_chip_cur.cs1_jedec_info->column - 8));
		pdmc->dmc_dcfg0 = regval;
	}
	/* Step6: set test length, and start/end address.... */
	pdmc->dmc_bist[1] = len>>2;    // bist_len register value unit in "Word"(=4Bytes)
	regval = ((jedec_addr.row & 0xffff) << 16) |
			 ((jedec_addr.cs & 0x1) << 15) |
			 ((jedec_addr.bank & 0x7) << 12) |
			 (jedec_addr.column & 0xfff);
	/*set addr_row[31:16],addr_cs[15],addr_bank[14:12],addr_col[11:0]*/
	pdmc->dmc_bist[2] = regval;

	/* Step7: Clear bist status  */
	regval = pdmc->dmc_bist[0];
	regval = u32_bits_set(regval, 13, 1, 1);    // clear last bist status.
	regval = u32_bits_set(regval, 0, 1, 1);     // enable bist
	regval = u32_bits_set(regval, 16, 10, burstlen);     // enable bist
	pdmc->dmc_bist[0] = regval;

	regval = u32_bits_set(regval, 13, 1, 0);
	regval = u32_bits_set(regval, 8, 2, bist_type);
	pdmc->dmc_bist[0] = regval;

	/* Step8: set pattern mode, trigger bist start  */
	regval = pdmc->dmc_bist[0];
	regval = u32_bits_set(regval, 12, 2, 0);    // [13]=0, [12]=0, disable maximum address BIST excuting
	regval = u32_bits_set(regval, 4, 2, op_mode);
	regval = u32_bits_set(regval, 0, 2, 3);     // [0]=1: enable bist; [1]=1: start bist
	pdmc->dmc_bist[0] = regval;

	/* Polling end status. */
	tout = (pdmc->dmc_bist[1]-1)*2;
	while(tout > 0)
	{
		regval = pdmc->dmc_bist[0];
		if (regval & 0x4)
			break;
		tout--;
	}

	/* disable bist */
	regval = pdmc->dmc_bist[0];
	regval = u32_bits_set(regval, 0, 1, 0);
	pdmc->dmc_bist[0] = regval;
	if(ddr_chip_cur.unsymmetry)
		pdmc->dmc_dcfg0 = dcfg0_bkup;
	/* Final: check bist result */
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
