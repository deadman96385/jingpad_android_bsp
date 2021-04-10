
#include <asm/arch-orca/sprd_reg.h>
#include <asm/arch-orca/clk_para_config.h>
#include "sci_types.h"
#include "ddrc_r1p1.h"
#include "ddrc_r1p1_phy.h"
#include "ddrc_r1p1_phy_cfg_lp4.h"
#include "ddrc_r1p1_common.h"

extern DRAM_CHIP_INFO ddr_chip_cur;
extern unsigned int phy_cfg_data_lp4[160];
extern unsigned int phy_cfg_common_data_lp4[54];
extern LPDDR4_MR_INFO lpddr4_mr_info;


uint32 min_freq, max_freq;
uint32 freq_sel_mask = FREQ_SEL_MASK;
TRAIN_CONDITIONS_TABLE phy_train;

DDR_CLK_ASSO_CFG ddr_clk_asso_cfg_table[FREQ_POINT_NUM_MAX] = {
	{
		.freq_index = 0,
		.clk_freq = PUB_CLK_256M,
		.dq_odt_en = 0,
		.ca_odt_en = 0
	},
	{
		.freq_index = 1,
		.clk_freq = PUB_CLK_384M,
		.dq_odt_en = 0,
		.ca_odt_en = 0
	},
	{
		.freq_index = 2,
		.clk_freq = PUB_CLK_667M,
		.dq_odt_en = 0,
		.ca_odt_en = 0
	},
	{
		.freq_index = 3,
		.clk_freq = PUB_CLK_768M,
		.dq_odt_en = 0,
		.ca_odt_en = 0
	},
	{
		.freq_index = 4,
		.clk_freq = PUB_CLK_1024M,
		.dq_odt_en = 0,
		.ca_odt_en = 0
	},
	{
		.freq_index = 5,
		.clk_freq = PUB_CLK_1333M,
		.dq_odt_en = 0,
		.ca_odt_en = 0
	},
	{
		.freq_index = 6,
		.clk_freq = PUB_CLK_1536M,
		.dq_odt_en = 0,
		.ca_odt_en = 0
	},
	{
		.freq_index = 7,
		.clk_freq = PUB_CLK_1866M,
		.dq_odt_en = 0,
		.ca_odt_en = 0
	}
};


#ifdef PXP_DEBUG
TRAIN_CFG_TABLE ddrc_training_config_table[DDR_RANK_NUM_MAX][FREQ_POINT_NUM_MAX] = {
0};
#else
TRAIN_CFG_TABLE ddrc_training_config_table[DDR_RANK_NUM_MAX][FREQ_POINT_NUM_MAX] = {
	//rank0 config
	{
		//F0 training enable config
		{
			.cabt_enable = 0,
			.gate_enable = 1,
			.reye_enable = 0,
			.rdvref_train_enable = 0,
			.weye_enable = 0,
			.wrvref_train_enable = 0,
			.perbitwr_enable = 0,
			.perbitrd_enable = 0,
			.ca_perbit_enable = 0
		},
		//F1 training enable config
		{
			.cabt_enable = 0,
			.gate_enable = 1,
			.reye_enable = 0,
			.rdvref_train_enable = 0,
			.weye_enable = 0,
			.wrvref_train_enable = 0,
			.perbitwr_enable = 0,
			.perbitrd_enable = 0,
			.ca_perbit_enable = 0
		},
		//F2 training enable config
		{
			.cabt_enable = 1,
			.gate_enable = 1,
			.reye_enable = 1,
			.rdvref_train_enable = 1,
			.weye_enable = 1,
			.wrvref_train_enable = 1,
			.perbitwr_enable = 0,
			.perbitrd_enable = 0,
			.ca_perbit_enable = 0
		},
		//F3 training enable config
		{
			.cabt_enable = 1,
			.gate_enable = 1,
			.reye_enable = 1,
			.rdvref_train_enable = 1,
			.weye_enable = 1,
			.wrvref_train_enable = 1,
			.perbitwr_enable = 0,
			.perbitrd_enable = 0,
			.ca_perbit_enable = 0
		},
		//F4 training enable config
		{
			.cabt_enable = 1,
			.gate_enable = 1,
			.reye_enable = 1,
			.rdvref_train_enable = 1,
			.weye_enable = 1,
			.wrvref_train_enable = 1,
			.perbitwr_enable = 0,
			.perbitrd_enable = 0,
			.ca_perbit_enable = 0
		},
		//F5 training enable config
		{
			.cabt_enable = 1,
			.gate_enable = 1,
			.reye_enable = 1,
			.rdvref_train_enable = 1,
			.weye_enable = 1,
			.wrvref_train_enable = 1,
			.perbitwr_enable = 1,
			.perbitrd_enable = 1,
			.ca_perbit_enable = 0
		},
		//F6 training enable config
		{
			.cabt_enable = 1,
			.gate_enable = 1,
			.reye_enable = 1,
			.rdvref_train_enable = 1,
			.weye_enable = 1,
			.wrvref_train_enable = 1,
			.perbitwr_enable = 0,
			.perbitrd_enable = 0,
			.ca_perbit_enable = 0
		},
		//F7 training enable config
		{
			.cabt_enable = 1,
			.gate_enable = 1,
			.reye_enable = 1,
			.rdvref_train_enable = 1,
			.weye_enable = 1,
			.wrvref_train_enable = 1,
			.perbitwr_enable = 0,
			.perbitrd_enable = 0,
			.ca_perbit_enable = 0
		}
	},
	//rank1 config
	{
		//F0 training enable config
		{
			.cabt_enable = 0,
			.gate_enable = 0,
			.reye_enable = 0,
			.rdvref_train_enable = 0,
			.weye_enable = 0,
			.wrvref_train_enable = 0,
			.perbitwr_enable = 0,
			.perbitrd_enable = 0,
			.ca_perbit_enable = 0
		},
		//F1 training enable config
		{
			.cabt_enable = 0,
			.gate_enable = 0,
			.reye_enable = 0,
			.rdvref_train_enable = 0,
			.weye_enable = 0,
			.wrvref_train_enable = 0,
			.perbitwr_enable = 0,
			.perbitrd_enable = 0,
			.ca_perbit_enable = 0
		},
		//F2 training enable config
		{
			.cabt_enable = 1,
			.gate_enable = 1,
			.reye_enable = 1,
			.rdvref_train_enable = 0,
			.weye_enable = 1,
			.wrvref_train_enable = 0,
			.perbitwr_enable = 0,
			.perbitrd_enable = 0,
			.ca_perbit_enable = 0
		},
		//F3 training enable config
		{
			.cabt_enable = 0,
			.gate_enable = 0,
			.reye_enable = 0,
			.rdvref_train_enable = 0,
			.weye_enable = 0,
			.wrvref_train_enable = 0,
			.perbitwr_enable = 0,
			.perbitrd_enable = 0,
			.ca_perbit_enable = 0
		},
		//F4 training enable config
		{
			.cabt_enable = 0,
			.gate_enable = 0,
			.reye_enable = 0,
			.rdvref_train_enable = 0,
			.weye_enable = 0,
			.wrvref_train_enable = 0,
			.perbitwr_enable = 0,
			.perbitrd_enable = 0,
			.ca_perbit_enable = 0
		},
		//F5 training enable config
		{
			.cabt_enable = 0,
			.gate_enable = 0,
			.reye_enable = 0,
			.rdvref_train_enable = 0,
			.weye_enable = 0,
			.wrvref_train_enable = 0,
			.perbitwr_enable = 0,
			.perbitrd_enable = 0,
			.ca_perbit_enable = 0
		},
		//F6 training enable config
		{
			.cabt_enable = 0,
			.gate_enable = 0,
			.reye_enable = 0,
			.rdvref_train_enable = 0,
			.weye_enable = 0,
			.wrvref_train_enable = 0,
			.perbitwr_enable = 0,
			.perbitrd_enable = 0,
			.ca_perbit_enable = 0
		},
		//F7 training enable config
		{
			.cabt_enable = 0,
			.gate_enable = 0,
			.reye_enable = 0,
			.rdvref_train_enable = 0,
			.weye_enable = 0,
			.wrvref_train_enable = 0,
			.perbitwr_enable = 0,
			.perbitrd_enable = 0,
			.ca_perbit_enable = 0
		}
	}
};
#endif
TRAIN_STATUS_TABLE ddrc_training_status_table = {0};

void while_loop(void)
{
	while(1);
}
#if 0
void ddrc_phy_vref_setting(void)
{
	/*bit[22] PHY_VREF_HI_C vref power down,1:pd 0:no-pd
	 * for lpddr3 suggest set to 1'b0
	 * for lpddr4/4x suggest set to 1'b1
	 * */
	/*bit[23] PHY_VREF_FP hi-current mode 1:enable 0:disable*/
	if (ddr_chip_cur.chip_type == DRAM_LPDDR3)
	{
		reg_bits_set(REG_PMU_APB_DDR_SLEEP_CTRL, 23, 1, 0x0);
	}
	else
	{
		reg_bits_set(REG_PMU_APB_DDR_SLEEP_CTRL, 23, 1, 0x1);
	}
	/*bit[31:24] PHY_VREF_AGJ */
	reg_bits_set(REG_PMU_APB_DDR_SLEEP_CTRL, 24, 8, 0x50);
	dmc_sprd_delay(10);

}
#endif

void ddrc_phy_iopvt_pre_seq(void)
{
	uint32 tmp_addr0 = DMC_GUCPHY0_BASE + (phy_train.freq_sel*20*4);
	uint32 tmp_addr1 = DMC_GUCPHY1_BASE + (phy_train.freq_sel*20*4);
	ddrc_phy_io_get(DMC_GUCPHY0_BASE, phy_train.freq_sel);
	ddrc_phy_io_get(DMC_GUCPHY1_BASE, phy_train.freq_sel);
	/*0x02cc*/
	/*bit[01] mlb_train_wdqs_stop_step_cfg_disable*/
	/*bit[02] mlb_train_wdqs_stop_step_cfg_cal_manual_mode_*/
	reg_bits_set((DMC_GUCPHY0_BASE + 0xB3*4), 1, 2, 0);
	reg_bits_set((DMC_GUCPHY1_BASE + 0xB3*4), 1, 2, 0);
	/*0x032c*/
	/*bit[11] mlb_cal_eb_cfg_cal_eb*/
	reg_bits_set((DMC_GUCPHY0_BASE + 0xCB*4), 11, 1, 1);
	reg_bits_set((DMC_GUCPHY1_BASE + 0xCB*4), 11, 1, 1);

	reg_bits_set((tmp_addr0 + (0x6 * 4)), 11, 1, 0);//bitp[1]cal_disable,bit[2] cal_manual_mode
	reg_bits_set((tmp_addr1 + (0x6 * 4)), 11, 1, 0);//bitp[1]cal_disable,bit[2] cal_manual_mode
}

void ddrc_phy_iopvt_cal_seq(void)
{
	uint32 read_data;
	uint32 data_tmp;
	/*step 1) check result */
	data_tmp = __raw_readl((DMC_GUCPHY0_BASE + 0xd6*4));
	if((data_tmp >> 3) & 0x1)
	{
		ddrc_print_err("polling io pvt failed\r\n");
		while_loop();
	}
	/*step 2) reset the pu/pd base on the iopvt zq resut*/
	/*0xe5*4 PU/PD code of IO PVT calibration result*/
	/*bit[23:16] pdio_cfg_pd_code*/
	/*bit[7:0] pdio_cfg_pu_code*/
	read_data = __raw_readl((DMC_GUCPHY0_BASE + 0xe5*4));
	/*0xb4*4 IO PVT manual mode*/
	/*bit[31:24] cal_default_pd_cfg_default_pd*/
	/*bit[23:16] cal_default_pd_cfg_default_pu*/
	/*bit[11:8]  cal_default_pd_cfg_offset_pd*/
	/*bit[3:0]	 cal_default_pd_cfg_offset_pu*/
	reg_bits_set((DMC_GUCPHY0_BASE + 0xb4*4), 16, 8, (read_data & 0xff));//cfg_pu_code data_tmp[23:16] = read_data[7:0]
	reg_bits_set((DMC_GUCPHY0_BASE + 0xb4*4), 24, 8, ((read_data >> 16) & 0xff));//cfg_pd_code;data_tmp[31:24] = read_data[23:16]

	/*step 3) enable cal_manual_mode and disable iopvt zq cali*/
	reg_bits_set((DMC_GUCPHY0_BASE + 0xB3*4), 1, 2, 3);//bitp[1]cal_disable,bit[2] cal_manual_mode
	reg_bits_set((DMC_GUCPHY1_BASE + 0xB3*4), 1, 2, 3);//bitp[1]cal_disable,bit[2] cal_manual_mode

	/*step 4) disable cal_eb 0xcb*4 MLB gated clock ctrl register*/
	//reg_bits_set((DMC_GUCPHY0_BASE + 0xCB*4), 11, 1, 0);//reg_mlb_cal_eb_cfg_cal_eb
	//reg_bits_set((DMC_GUCPHY1_BASE + 0xCB*4), 11, 1, 0);//reg_mlb_cal_eb_cfg_cal_eb
	ddrc_phy_io_set(DMC_GUCPHY0_BASE, phy_train.freq_sel);
	ddrc_phy_io_set(DMC_GUCPHY1_BASE, phy_train.freq_sel);
	ddrc_training_status_table.iopvt_zq_cal_done = 1;
}


void ddrc_phy_post_setting(uint32 phy_base)
{
	reg_bits_set(phy_base + 0xcb*4, 8, 4, 0); //eb
	reg_bits_set(phy_base + 0xcb*4, 0, 4, 0);//ag_en
	reg_bits_set(phy_base + 0xd1*4, 16, 1, 0); //reg_pwrup_cke_rstn_en
	reg_bits_set(phy_base + 0xCB*4, 11, 1, 0); //reg_mlb_cal_eb_cfg_cal_eb
}

uint32 ddrc_phy_rpull_get(uint32 phy_base, uint32 freq_sel)
{
	uint32 tmp_addr = phy_base + (freq_sel*20*4);

	return(reg_bits_get(tmp_addr + 0x9*4, 31, 1));//cfg_rpull
}

void ddrc_phy_rpull_set(uint32 phy_base, uint32 freq_sel, uint32 value)
{
	uint32 tmp_addr = phy_base + (freq_sel*20*4);

	reg_bits_set(tmp_addr + 0x9*4, 31, 1, value);//cfg_rpull
}

typedef struct{
	uint8 ib;
	uint8 csn;
	uint8 edge_mode;
	uint8 rpull_value;
	uint8 pu_value;
	uint8 pd_value;
	uint8 odtn;
	uint32 rdvref;
}PHY_TRAINING_IO_CFG;

PHY_TRAINING_IO_CFG phy_training_io_cfg = {0};

void ddrc_phy_io_get(uint32 phy_base, uint32 freq_sel)
{
	uint32 tmp_addr = phy_base + (freq_sel*20*4);
	phy_training_io_cfg.ib = reg_bits_get(tmp_addr + 0x6*4, 10, 2); //ibc ib4
	phy_training_io_cfg.csn = reg_bits_get(tmp_addr + 0x6*4, 8, 1); //cs nen
	phy_training_io_cfg.edge_mode = reg_bits_get(tmp_addr + 0x8*4, 28, 1);//edge mode
	phy_training_io_cfg.rpull_value = reg_bits_get(tmp_addr + 0x9*4, 31, 1);//cfg_rpull
	phy_training_io_cfg.pu_value = reg_bits_get(tmp_addr + 0x9*4, 24, 1);//cfg_pu
	phy_training_io_cfg.pd_value = reg_bits_get(tmp_addr + 0x9*4, 28, 1);//cfg_pd
	phy_training_io_cfg.odtn = reg_bits_get(tmp_addr + 0x9*4, 0, 3);//odtn
	phy_training_io_cfg.rdvref = reg_bits_get(tmp_addr + 0x10*4, 0, 16);//rdvref
}

void ddrc_phy_io_set(uint32 phy_base, uint32 freq_sel)
{
	uint32 tmp_addr = phy_base + (freq_sel*20*4);
	reg_bits_set(tmp_addr + 0x6*4, 10, 2, phy_training_io_cfg.ib); //ibc ib4
	reg_bits_set(tmp_addr + 0x6*4, 8, 1, phy_training_io_cfg.csn); //cs nen
	reg_bits_set(tmp_addr + 0x8*4, 28, 1, phy_training_io_cfg.edge_mode);//edge mode
	reg_bits_set(tmp_addr + 0x9*4, 31, 1, phy_training_io_cfg.rpull_value);//cfg_rpull
	reg_bits_set(tmp_addr + 0x9*4, 24, 1, phy_training_io_cfg.pu_value);//cfg_rup
	reg_bits_set(tmp_addr + 0x9*4, 28, 1, phy_training_io_cfg.pd_value);//cfg_rdn
	reg_bits_set(tmp_addr + 0x9*4, 0, 3, phy_training_io_cfg.odtn);//odtn
	reg_bits_set(tmp_addr + 0x10*4, 0, 16, phy_training_io_cfg.rdvref);//rdvref
	reg_bits_set(tmp_addr + 0xA*4, 15, 1, 1);//rd odt always on en.
}

void ddrc_phy_rpull_set_for_gate_train_pre(uint32 phy_base, uint32 freq_sel)
{
	uint32 tmp_addr = phy_base + (freq_sel*20*4);
	ddrc_phy_io_get(phy_base, freq_sel);
	//gate manual mode
	reg_bits_set(phy_base + 0xb2*4, 1, 1, 0);

	reg_bits_set(tmp_addr + 0x9*4, 31, 1, 0);//cfg_rpull
	reg_bits_set(tmp_addr + 0x9*4, 24, 1, 0);//cfg_rup
	reg_bits_set(tmp_addr + 0x9*4, 28, 1, 0);//cfg_rdn
//	reg_bits_set(tmp_addr + 0x9*4, 4, 3, 0x0);//odtp off
	reg_bits_set(tmp_addr + 0x9*4, 0, 3, 0x2);//odtn 80ohm
	reg_bits_set(tmp_addr + 0x10*4, 0, 16, 0x3030);//read vref rest
//	if(phy_train.freq_sel == 6)
//		reg_bits_set(phy_base + 0xa8 * 4, 8, 8, 0x1E);
	/* 0: off	  */
	/* 1: 240 ohm */
	/* 2: 120 ohm */
	/* 3: 80 ohm */
	/* 4: 60 ohm */
	/* 5: 48 ohm */
	/* 6: 40 ohm */
	/* 7: 34 ohm */
	/*
	if (DRAM_LPDDR4 == ddr_chip_cur.chip_type)
	{
		reg_bits_set(tmp_addr + 0x6*4, 8, 4, 0xC);
		reg_bits_set(tmp_addr + 0x9*4, 0, 3, 0x2);//odtn 120ohm
		reg_bits_set(phy_base + 0xa0*4, 4, 1, 0);
	}
	*/
	reg_bits_set(tmp_addr + 0x6*4, 10, 2, 1); //ibc ib4
	reg_bits_set(tmp_addr + 0x6*4, 8, 1, 1); //csn en
//	reg_bits_set(tmp_addr + 0x6*4, 9, 1, 0); //csp en
	/* rodt_alwayson */
//	reg_bits_set(tmp_addr + 0xa*4, 15, 1, 1);//edge mode

//	reg_bits_set(phy_base + 0xa2*4, 0, 1, 0);//rddv_sel_auto for gate train

//	reg_bits_set(phy_base + 0xc6*4, 16, 8, 0xf); //gate stop intg

//	reg_bits_set(phy_base + 0xa0*4, 4, 1, 1);
//	reg_bits_set(phy_base + 0xa0*4, 11, 2, 3);

	reg_bits_set(tmp_addr + 0x8*4, 28, 1, 1);//edge mode

}
void ddrc_phy_rpull_set_for_gate_train_post(uint32 phy_base, uint32 freq_sel)
{
	uint32 tmp_addr = phy_base + (freq_sel*20*4);
	//gate manual mode
	reg_bits_set(phy_base + 0xb2*4, 1, 1, 1);

//	reg_bits_set(tmp_addr + 0x6*4, 8, 4, 0x6);
//	reg_bits_set(phy_base + 0xa0*4, 11, 2, 0);
//	reg_bits_set(tmp_addr + 0x6*4, 8, 1, 0); //cs nen
//	reg_bits_set(tmp_addr + 0x8*4, 28, 1, 0);//edge mode
//	reg_bits_set(tmp_addr + 0x9*4, 31, 1, 1); //cfg_rpull
//	reg_bits_set(tmp_addr + 0x9*4, 24, 1, 0);//cfg_rup
//	reg_bits_set(tmp_addr + 0x9*4, 28, 1, 0);//cfg_rdn
//	reg_bits_set(tmp_addr + 0x9*4, 0, 3, 0x3);//odtn 80ohm
	ddrc_phy_io_set(phy_base, freq_sel);
}

void phy_reload_rank0_gate(uint32 wr_bit, uint32 phy_base, uint32 freq_sel, uint32 rank)
{
	uint32 tmp_addr = phy_base + (freq_sel*20*4);
	uint32 read_data;
	uint32 regval;
	uint32 data_tmp;
	uint32 window_width_max;
	char s_tmp[11] = {0};
	/*0x03A0 gate pass window*/
	/*bit[31:24] mlb_db1_gate_pass_window_cfg_coarse_db1*/
	/*bit[20:16] mlb_db1_gate_pass_window_cfg_fine_db1*/
	/*bit[15:8] mlb_db0_gate_pass_window_cfg_coarse_db0*/
	/*bit[7:0] mlb_db0_gate_pass_window_cfg_fine_db0*/
	data_tmp = __raw_readl(phy_base + 0xe8*4);
	ddrc_print_debug("gate training window coarse_db1 ");
	ddrc_print_debug(itoa_simple(((data_tmp >> 24) & 0xff), s_tmp, 10));
	ddrc_print_debug("\r\n");
	ddrc_print_debug("gate training window fine_db1 ");
	ddrc_print_debug(itoa_simple(((data_tmp >> 16) & 0xff), s_tmp, 10));
	ddrc_print_debug("\r\n");
	ddrc_print_debug("gate training window coarse_db0 ");
	ddrc_print_debug(itoa_simple(((data_tmp >> 8) & 0xff), s_tmp, 10));
	ddrc_print_debug("\r\n");
	ddrc_print_debug("gate training window fine_db0 ");
	ddrc_print_debug(itoa_simple(((data_tmp >> 0) & 0xff), s_tmp, 10));
	ddrc_print_debug("\r\n");
	if ((((data_tmp >> 16) & 0xffff) < 10) || ((data_tmp & 0xffff) < 10))
	{
		ddrc_print_err("gate training window too small\r\n");
		while_loop();
	}
	window_width_max = ((data_tmp >> 24) > (data_tmp >> 8)) ? (data_tmp >> 24) : (data_tmp >> 8);
#if 0
	if ((wr_bit >> 8) & 0x1)//GATE
	{
		/*0x039C The gate training coarse and fine delay training result*/
		data_tmp = __raw_readl(phy_base + 0xe7*4);
		/*F0-7 The gate training manual mode coarse and fine delay setting*/
		__raw_writel(tmp_addr + 0xd*4, data_tmp);//db1_dl_gate_fine_cfg_db1_fine

		/*0x03A4 The rddv_sel valude and DRAM vref training reslut*/
		/*bit[29:24] vref_dram_value_manu_cfg*/
		/*bit[3:0]	 vref_dram_value_manu_cfg_rddv_sel*/
		read_data = REG32(phy_base + 0xe9*4);
		/*F0-7 rddv sel and offset manual mode setting for set and DRAM
		 * vref manual mode seting*/
		/*bit[30]	 mlb_vref_dram_rang_manu_cfg_range*/
		/*bit[29:24] mlb_vref_dram_rang_manu_cfg_value*/
		/*bit[10:8]  mlb_vref_dram_rang_manu_cfg_offset*/
		/*bit[3:0]	 mlb_vref_dram_rang_manu_cfg_sel*/
		reg_bits_set(tmp_addr + 0xf*4, 0, 4, (read_data & 0xf));
	}
#endif
	if ((wr_bit >> 8) & 0x1)
	{
		read_data = __raw_readl(phy_base + 0xe7*4);
		//In order to cover different rank gate position,
		//adjust the gate training offset for stability
		//if (freq_sel == 4)
		//	read_data += 0x0101;
		//else if (freq_sel > 4)
		//	read_data += 0x0202;

		__raw_writel(tmp_addr + 0xd*4, read_data);
		/*
		 * --PHY latency (Kevin/Yuelin) (test stability)
		 *	F7: 50600404, coarse tune offset + 2 = 6 (4.375*2-2 = 6) ---à rddv_sel =
		 *	roundup (((gate_bt-2)*2+8)/4): 4
		 *	F6: B8B80303, coarse tune offset + 2 = 5 (3.7*2-2 = 5.4) ---à rddv_sel =
		 *	roundup (((gate_bt-2)*2+8)/4):4
		 *	F5: E8F00202, coarse tune offset +2 =4 (3*2-2 =4) ---à rddv_sel = roundup
		 *	(((gate_bt-2)*2+8)/4):3
		 *	F4: 80800202, coarse tune offset +1 = 3 (2.5*2-2=3) --à rddv_sel = roundup
		 *	(((gate_bt-1)*2+8)/4):3
		 *	F3:4
		 *	F2:3
		 *	F1:3
		 *	F1~f3: roundup ((gate_bt*2+8)/4):
		 *	We could check the value after the formula implemented, the difference is
		 *	the reduced number of clk_d2 (controller clock)
		 *	If originally is 5, after tuning is 3, then we will save 2 clk_d2 read
		 *	latency.
		 *	But, of course, it have to stable, the formula is based on the read ddr_dqs
		 *	come back time + 2 ddr_clk (data received) then start to push out the read
		 *	data to controller.
		 * */
		regval = __raw_readl(phy_base + 0xe7*4);
		read_data = (((regval & 0xff) * 2 + window_width_max) / 2 ) + 0xA;	// (start+end)/2=middle. (end-start)=window_width_max.  8 is offset.
		if (read_data % 4)
		{
			regval = read_data/4 + 1;
		}
		else
		{
			regval = read_data/4;
		}
		reg_bits_set(tmp_addr + 0xf*4, 0, 4, (regval & 0xf));
	}

}
int ca_reload_rank_reg(uint32 phy_base, uint32 freq_sel, uint32 rank)
{
	uint32 data_tmp;
	uint32 read_data;
	uint32 data_rank0;
	uint32 data_rank1;
	uint32 data_rank0_bk;
	uint32 data_rank1_bk;
	uint32 ac_mst_delay;
	uint32 tmp_addr = phy_base + (freq_sel*20*4);

	ac_mst_delay = reg_bits_get((phy_base + 0xe1*4), 0, 9);

	read_data = __raw_readl(phy_base + 0xe6*4);
	if (((read_data >> 16) & 0xFF) < 10)
	{
		if (rank)
			ddrc_print_err("RANK 1 CA Training fine window size smaller than 10!\r\n");
		else
			ddrc_print_err("RANK 0 CA Training fine window size smaller than 10!\r\n");
//		return -1;
	}

	data_tmp = __raw_readl(phy_base + 0xe6*4);
	if ((((data_tmp >> 8) & 0xff) == 0xff) && ((data_tmp & 0x1) == 0x1))
	{
		ddrc_print_err("rank CA training failed because have not right boundary!\r\n");
		return -1;
	}
	(lpddr4_mr_info.p_odt_cfg + phy_train.freq_sel)->mr12 = u32_bits_set((lpddr4_mr_info.p_odt_cfg + phy_train.freq_sel)->mr12, 0, 6, ((data_tmp >> 24) & 0x3f));
	if(phy_train.freq_sel < MAX_FREQ_SEL)
	{
//		(lpddr4_mr_info.p_odt_cfg + phy_train.freq_sel)->mr12 = u32_bits_set((lpddr4_mr_info.p_odt_cfg + phy_train.freq_sel + 1)->mr12, 0, 6, ((data_tmp >> 24) & 0x3f));
	}

	if (rank == 0)
	{
		/*bit[0] ca delay bt enable
		*bit[15:8] ca training fine dealy
		*bit[29:24] ca training vref manual mode value
		*/
		reg_bits_set((tmp_addr + 0xc*4), 0, 1, (data_tmp&0x1));
		reg_bits_set((tmp_addr + 0xc*4), 8, 8, ((data_tmp>>8)&0xff));
		reg_bits_set((tmp_addr + 0xc*4), 24, 6, ((data_tmp>>24)&0x3f));
	}
	else
	{
		data_rank1 = data_tmp;

		data_rank0 = __raw_readl(tmp_addr + 0xc*4);

		//{data_rank1[0], data_rank1[15:8]}
		data_rank1_bk = (((data_rank1 & 0x1) << 9) | (data_rank1 >> 8 & 0xff));
		data_rank0_bk = (((data_rank0 & 0x1) << 9) | (data_rank0 >> 8 & 0xff));

		if (data_rank1_bk  > data_rank0_bk)
		{
			__raw_writel(tmp_addr + 0xc*4, data_rank0);
			//reg_phy_longer_ca_dl_sel <= #'RD reg_wdata[19:16]
			reg_bits_set((phy_base + 0xd2*4), 16, 4, 0x2);
			//reg_phy_fdl_ca_mul_wr <= #'RD reg_wdata[21:16]ca delay difference
			reg_bits_set((phy_base + 0xd3*4), 16, 8, ((data_rank1_bk - data_rank0_bk)*ac_mst_delay/256/2));
		}
		else //rank0 longer
		{
			__raw_writel(tmp_addr + 0xC*4, data_rank1);
			//reg_phy_longer_ca_dl_sel <= #'RD reg_wdata[19:16]
			reg_bits_set((phy_base + 0xd2*4), 16, 4, 0x1);
			//reg_phy_fdl_ca_mul_wr <= #'RD reg_wdata[21:16]ca delay difference
			reg_bits_set((phy_base + 0xd3*4), 16, 8, (data_rank0_bk - data_rank1_bk)*ac_mst_delay/256/2);

			ddrc_training_status_table.ca_shorter_rank = 1;
		}
	}
	return 1;
}

void phy_reload_weye_result(uint32 phy_base, uint32 freq_sel)
{
	uint32 read_data;
	uint32 data_tmp;
	uint32 tmp_addr = phy_base + freq_sel*20*4;
	uint32 tmp_fdl_mul_wr_pre;
	uint32 tmp_fdl_mul_wr;
	uint32 db0_mst_delay;
	uint32 db1_mst_delay;

	if (ddrc_training_status_table.wr_shorter_rank != ddrc_training_status_table.ca_shorter_rank) //different with ca
	{
		db0_mst_delay = __raw_readl(phy_base + 0xdf*4) & 0x1f;
		db1_mst_delay = __raw_readl(phy_base + 0xe0*4) & 0x1f;

		tmp_fdl_mul_wr_pre = __raw_readl(phy_base + 0xd3*4);
		tmp_fdl_mul_wr_pre = (tmp_fdl_mul_wr_pre & 0x3f) *2 * 256;

		read_data = __raw_readl(tmp_addr + 0x12*4);

		tmp_fdl_mul_wr = tmp_fdl_mul_wr_pre / db0_mst_delay;
		//{read_data[19:16], read_data[7:0]} = {read_data[19:16], read_data[7:0]} - tmp_fdl_mul_wr;
		data_tmp = (((read_data >> 16) & 0xf) << 8) | (read_data & 0xff);
		data_tmp -= tmp_fdl_mul_wr;
		read_data = u32_bits_set(read_data, 0, 8, (data_tmp & 0xff));
		read_data = u32_bits_set(read_data, 16, 4, ((data_tmp >> 8) & 0xff));

		tmp_fdl_mul_wr = tmp_fdl_mul_wr_pre / db1_mst_delay;
		//{read_data[19:16], read_data[7:0]} = {read_data[19:16], read_data[7:0]} - tmp_fdl_mul_wr;
		data_tmp = (((read_data >> 16) & 0xf) << 8) | (read_data & 0xff);
		data_tmp -= tmp_fdl_mul_wr;
		read_data = u32_bits_set(read_data, 0, 8, (data_tmp & 0xff));
		read_data = u32_bits_set(read_data, 16, 4, ((data_tmp >> 8) & 0xff));

		__raw_writel(tmp_addr + 0x12*4, read_data);

	}
}

void phy_reload_rank_0_reg(uint32 wr_bit,uint32 phy_base, uint32 freq_sel, uint32 rank)
{
	uint32 read_data;
	uint32 data_tmp;
	uint32 regval;
	uint32 window_width_max;
	char s_tmp[11];
	uint32 tmp_addr = phy_base + freq_sel*20*4;

//	ddrc_print_debug("rank0 training result: \r\n");
	if ((wr_bit >> 8) & 0x1)
	{
		/*0x03A0 gate pass window*/
		/*bit[31:24] mlb_db1_gate_pass_window_cfg_coarse_db1*/
		/*bit[20:16] mlb_db1_gate_pass_window_cfg_fine_db1*/
		/*bit[15:8] mlb_db0_gate_pass_window_cfg_coarse_db0*/
		/*bit[7:0] mlb_db0_gate_pass_window_cfg_fine_db0*/
		data_tmp = __raw_readl(phy_base + 0xe8*4);
		ddrc_print_debug("gate training window coarse_db1 ");
		ddrc_print_debug(itoa_simple(((data_tmp >> 24) & 0xff), s_tmp, 10));
		ddrc_print_debug("\r\n");
		ddrc_print_debug("gate training window fine_db1 ");
		ddrc_print_debug(itoa_simple(((data_tmp >> 16) & 0xff), s_tmp, 10));
		ddrc_print_debug("\r\n");
		ddrc_print_debug("gate training window coarse_db0 ");
		ddrc_print_debug(itoa_simple(((data_tmp >> 8) & 0xff), s_tmp, 10));
		ddrc_print_debug("\r\n");
		ddrc_print_debug("gate training window fine_db0 ");
		ddrc_print_debug(itoa_simple(((data_tmp >> 0) & 0xff), s_tmp, 10));
		ddrc_print_debug("\r\n");
		if ((((data_tmp >> 16) & 0xffff) < 10) || ((data_tmp & 0xffff) < 10))
		{
			ddrc_print_err("gate training window too small\r\n");
			while_loop();
		}
		window_width_max = ((data_tmp >> 24) > (data_tmp >> 8)) ? (data_tmp >> 24) : (data_tmp >> 8);
		read_data = __raw_readl(phy_base + 0xe7*4);
		//In order to cover different rank gate position,
		//adjust the gate training offset for stability
		//if (freq_sel == 4)
		//	read_data += 0x0101;
		//else if (freq_sel > 4)
		//	read_data += 0x0202;

		__raw_writel(tmp_addr + 0xd*4, read_data);
		/*
		 * --PHY latency (Kevin/Yuelin) (test stability)
		 *	F7: 50600404, coarse tune offset + 2 = 6 (4.375*2-2 = 6) ---à rddv_sel =
		 *	roundup (((gate_bt-2)*2+8)/4): 4
		 *	F6: B8B80303, coarse tune offset + 2 = 5 (3.7*2-2 = 5.4) ---à rddv_sel =
		 *	roundup (((gate_bt-2)*2+8)/4):4
		 *	F5: E8F00202, coarse tune offset +2 =4 (3*2-2 =4) ---à rddv_sel = roundup
		 *	(((gate_bt-2)*2+8)/4):3
		 *	F4: 80800202, coarse tune offset +1 = 3 (2.5*2-2=3) --à rddv_sel = roundup
		 *	(((gate_bt-1)*2+8)/4):3
		 *	F3:4
		 *	F2:3
		 *	F1:3
		 *	F1~f3: roundup ((gate_bt*2+8)/4):
		 *	We could check the value after the formula implemented, the difference is
		 *	the reduced number of clk_d2 (controller clock)
		 *	If originally is 5, after tuning is 3, then we will save 2 clk_d2 read
		 *	latency.
		 *	But, of course, it have to stable, the formula is based on the read ddr_dqs
		 *	come back time + 2 ddr_clk (data received) then start to push out the read
		 *	data to controller.
		 * */
		regval = __raw_readl(phy_base + 0xe7*4);
		//if (((regval >> 16) & 0xff) >= 0x80)
		//	read_data = ((regval & 0xff) + 1 ) * 2 + 8;
		//else
			read_data = (regval & 0xff) * 2 + window_width_max + 8;	// (start+end)/2=middle. (end-start)=window_width_max.  8 is offset.
		if (read_data % 4)
		{
			regval = read_data/4 + 1;
		}
		else
		{
			regval = read_data/4;
		}
		reg_bits_set(tmp_addr + 0xf*4, 0, 4, (regval & 0xf));

	}

	if ((wr_bit >> 10) & 0x1)//RDEYE
	{
		/*0x03AC Read dqs rising and flling edge phase shift training*/

		read_data = __raw_readl(phy_base + 0x3B4);
		if ((((read_data & 0xff) <= 10)) ||
			(((read_data >> 8) & 0xFF) <= 10))
		{
			ddrc_print_err("rank 0 Read EYE window size too small!\r\n");
			while_loop();
		}
		data_tmp = __raw_readl(phy_base + 0xeb*4);
		/*0x44 + F0-7 Rank read dqs rising and falling edge phase shift
		 * manual mode setting*/
		/*bit[31:24] db1_dll_rddeye_dqsn_cfg_db0_dqs_mul*/
		/*bit[23:16] db1_dll_rddeye_dqsn_cfg_db1_dqs_mul*/
		/*bit[15:8]  db1_dll_rddeye_dqsn_cfg_db1_dqs*/
		/*bit[7:0]	 db1_dll_rddeye_dqsn_cfg_db0_dqs*/
		__raw_writel(tmp_addr + 0x11*4, data_tmp);

		if ((((data_tmp >> 24) & 0xff) == 0xff) ||
			(((data_tmp >> 16) & 0xff) == 0xf)||
			(((data_tmp >> 8) & 0xff) == 0xff)||
			((data_tmp & 0xff) == 0xff))
		{
			ddrc_print_err("rank 0 Read EYE training failed because have not right boundary!\r\n");
			while_loop();
		}
	}

	if ((wr_bit >> 11) & 0x1)//RVREF
	{
		/*0x03A8 Read vref training result*/
		/*bit[15:8] vref_phy_agj_result_db1_cfg_db1_result*/
		/*bit[7:0]	vref_phy_agj_result_db1_cfg_db0_result*/
		read_data = __raw_readl(phy_base + 0xea*4);
		/*0x40 + F0-7 Read vref manual mode setting and multiple rank MLB
		 * function disable control*/
		/*bit[15:8] mlb_vref_phy_value_manu_db1_cfg_db1*/
		/*bit[7:0]	mlb_vref_phy_value_manu_db1_cfg_db0*/
		reg_bits_set(tmp_addr + 0x10*4, 0, 16, read_data & 0xffff);
	}

	if ((wr_bit >> 13) & 0x1)//WEYE
	{
		read_data = __raw_readl(phy_base + 0x3B8);
		if ((((read_data & 0xff) <= 10)) ||
			 (((read_data >> 8) & 0xFF) <= 10))
		{
			if (rank)
				ddrc_print_err("RANK 1 Write EYE window size too small!\r\n");
			else
				ddrc_print_err("RANK 0 Write EYE window size too small!\r\n");

			while_loop();
		}

		data_tmp = __raw_readl(phy_base + 0xec*4);
		__raw_writel(tmp_addr + 0x12*4, data_tmp);///db1_bt_wdq_cfg_db1_bt/db0_bt/db1_wrdeye/db0_wrdeye

		if (((((data_tmp >> 8) & 0xff) == 0xff) && (((data_tmp >> 20) & 0xf) == 0xf)) ||
			((((data_tmp >>16) & 0xf) == 0xf) && ((data_tmp & 0xff) == 0xff)))
		{
			ddrc_print_err("rank 0 Write EYE training failed because have not right boundary!\r\n");
			while_loop();
		}
		phy_reload_weye_result(phy_base, freq_sel);
	}

	if ((wr_bit >> 14) & 0x1)//WVREF
	{
		/*0x03A4 The rddv_sel valude and DRAM vref training reslut*/
		/*bit[29:24] vref_dram_value_manu_cfg*/
		/*bit[3:0]	 vref_dram_value_manu_cfg_rddv_sel*/
		read_data = __raw_readl(phy_base + 0xe9*4);
		/*rddv sel and offset manual mode setting for set
		 * and DRAM vref manual mode settting for F0-7*/
		/*bit[29:24] mlb_vref_dram_range_manu_cfg_value*/
		reg_bits_set(tmp_addr + 0xf*4, 24, 6, ((read_data >>24) & 0x3f));
		(lpddr4_mr_info.p_odt_cfg + phy_train.freq_sel)->mr14 = u32_bits_set((lpddr4_mr_info.p_odt_cfg + phy_train.freq_sel)->mr14, 0, 6, ((read_data >>24) & 0x3f));
		if(DMC_GUCPHY0_BASE  == phy_base)
		{
			lpddr_dmc_mrw_chn_sel(CMD_CHN_0);
		}
		else
		{
			lpddr_dmc_mrw_chn_sel(CMD_CHN_1);
		}
		if(0 == phy_train.rank)
		{
			lpddr_dmc_mrw(CMD_CS_BOTH, 14, (lpddr4_mr_info.p_odt_cfg + phy_train.freq_sel)->mr14);
		}
		else
		{
			lpddr_dmc_mrw(CMD_CS_1, 14, (lpddr4_mr_info.p_odt_cfg + phy_train.freq_sel)->mr14);
		}
		lpddr_dmc_mrw_chn_sel(CMD_CHN_BOTH);
	}

	if ((wr_bit >> 9) & 0x1)//RPERB dm use dq0
	{
		data_tmp = __raw_readl(phy_base + 0xf6*4);
		__raw_writel(phy_base + 0xbc*4, data_tmp);

		read_data = __raw_readl(phy_base + 0xf5*4);
		__raw_writel(phy_base + 0xbb*4, read_data);

		data_tmp = __raw_readl(phy_base + 0xf4*4);
		data_tmp= u32_bits_set(data_tmp, 24, 8, (read_data & 0xff));//f5[7:0] is reg_ro_rd_db1_dq3_fdl_cfg_db1_dq0
		__raw_writel(phy_base + 0xba*4, data_tmp);//bit[31:24]fdl_db1_dm_rd_cfg_db1_dm_rd
							//bit[23:16]fdl_db1_dm_rd_cfg_db1_dqs_rd
							//bit[15:8]fdl_db1_dm_rd_cfg_db0_dq7_rd
							//bit[7:0]fdl_db1_dm_rd_cfg_db0_dq6_rd

		data_tmp = __raw_readl(phy_base + 0xf3*4);
		__raw_writel(phy_base + 0xb9*4, data_tmp);//bit[31:24]fdl_db0_dq5_rd_cfg_db0_dq5_rd
							//bit[23:16]fdl_db0_dq5_rd_cfg_db0_dq4_rd
							//bit[15:8]fdl_db0_dq5_rd_cfg_db0_dq3_rd
							//bit[7:0]fdl_db0_dq5_rd_cfg_db0_dq2_rd

		data_tmp = __raw_readl(phy_base + 0xf2*4);//data_tmp[15:8]= data_tmp[23:16]if reg ro rd db0 dq1  fdl cfg db0 dq0
		data_tmp= u32_bits_set(data_tmp, 8, 8, ((data_tmp >> 16) & 0xff));
		__raw_writel(phy_base + 0xb8*4, data_tmp);

		data_tmp = __raw_readl(phy_base + 0xe2*4);
		if ((data_tmp & 0xf) != 0xf)
		{
			ddrc_print_err("perbit rd training failed\r\n");
			while_loop();//perbit rd training fail
		}
	}

	if ((wr_bit >> 12) & 0x1)//WPERB dm us dq0
	{
		/*0x03EC PHY write path per bit deskew training result*/
		data_tmp = __raw_readl(phy_base + 0xfb*4);
		/*0x0304 PHY write path per bit deskew manual mode setting*/
		__raw_writel(phy_base + 0xc1*4, data_tmp);

		read_data = __raw_readl(phy_base + 0xfa*4);
		/*0x0300 PHY write path per bit deskew manual mode setting*/
		__raw_writel(phy_base + 0xc0*4, read_data);

		/*0x03E4 PHY write path per bit deskew training result*/
		/*0x3E8 bit[7:0] wr_db1_dq3_fdl_cfg_db1_dq0*/
		/*0x3E4 bit[31:24] wr_db1_dm_fdl_cfg_db1_dm*/
		/* dq0 to dm
		 * data_tmp[31:24] == read_data[7:0]*/
		data_tmp = __raw_readl(phy_base + 0xf9*4);
		data_tmp= u32_bits_set(data_tmp, 24, 8, (read_data & 0xff));
		/*0x0300 PHY write path per bit deskew manual mode setting*/
		__raw_writel(phy_base + 0xbf*4, data_tmp);

		data_tmp = __raw_readl(phy_base + 0xf8*4);
		/*0x0300 PHY write path per bit deskew manual mode setting*/
		__raw_writel(phy_base + 0xbe*4, data_tmp);

		data_tmp = __raw_readl(phy_base + 0xf7*4);//data_tmp[15:8]= data_tmp[23:16]
		data_tmp= u32_bits_set(data_tmp, 8, 8, ((data_tmp >> 16) & 0xff));
		/*0x0300 PHY write path per bit deskew manual mode setting*/
		__raw_writel(phy_base + 0xbd*4, data_tmp);

		data_tmp = __raw_readl(phy_base + 0xe2*4);
		if (((data_tmp >> 4) & 0xf) != 0xf)
		{
			ddrc_print_err("perbit wr training failed!\r\n");
			while_loop();
		}
	}
}

void phy_reload_rank_1_reg(uint32 wr_bit, uint32 phy_base, uint32 freq_sel, uint32 rank)
{
	uint32 data_tmp;
	uint32 tmp_addr = phy_base + (freq_sel * 20 * 4);
	uint32 data_rank0;
	uint32 data_rank0_bk;
	uint32 data_rank1;
	uint32 data_rank1_bk;
	uint32 db0_mst_delay;
	uint32 db1_mst_delay;
	uint32 ac_mst_delay;
	u64 fdl_db0_mul_wr_pre;
	u64 fdl_db1_mul_wr_pre;

	data_tmp = __raw_readl(phy_base + 0xdf*4);
	db0_mst_delay = data_tmp & 0x1ff;

	data_tmp = __raw_readl(phy_base + 0xe0*4);
	db1_mst_delay = data_tmp & 0x1ff;

	data_tmp = __raw_readl(phy_base + 0xe1*4);
	ac_mst_delay = data_tmp & 0x1ff;

	if ((wr_bit >> 10) & 0x1)//rdeye
	{
		data_rank1 = __raw_readl(phy_base + 0xeb*4);

		if (((data_rank1 >> 24 & 0xff) == 0xff) || ((data_rank1 >> 16 & 0xff) == 0xff) ||
			((data_rank1 >> 8 & 0xff) == 0xff) || ((data_rank1 & 0xff) == 0xff))
		{
			ddrc_print_err("Rank RDEYE CA training failed because have not right boundary!\r\n");
			while_loop();

		}

		data_rank0 = __raw_readl(tmp_addr + 0x11*4);

		if ((data_rank1 & 0xff) > (data_rank0 & 0xff)) //db0 rank 1 longer
		{
			reg_bits_set(phy_base + 0xd2*4, 0, 4, 2); //reg phy longer rd dl sel db0 <= #'RD reg_wdata[3:0]

			data_rank0 = u32_bits_set(data_rank0, 0, 8, (data_rank0 & 0xff));//not used
			data_rank0 = u32_bits_set(data_rank0, 16, 8, (data_rank1 & 0xff));
			__raw_writel(tmp_addr + 0x11*4, data_rank0);
		}
		else
		{
			reg_bits_set(phy_base + 0xd2*4, 0, 4, 1); //reg phy longer rd dl sel db0 <= #'RD reg_wdata[3:0]

			data_rank0 = u32_bits_set(data_rank0, 0, 8, (data_rank1 & 0xff));
			data_rank0 = u32_bits_set(data_rank0, 16, 8, (data_rank0 & 0xff));
			__raw_writel(tmp_addr + 0x11*4, data_rank0);
		}

		if (((data_rank1 >> 8) & 0xff) > ((data_rank0 >> 8) & 0xff))//db1 rank 1 longer
		{
			reg_bits_set(phy_base + 0xd2*4, 4, 4, 2); //reg phy longer rd dl sel db0 <= #'RD reg_wdata[3:0]
			//data_rank0[15:8] = data_rank0[15:8]
			//data_rank0[31:24] = data_rank1[15:8]
			data_rank0 = u32_bits_set(data_rank0, 8, 8, ((data_rank0 >> 8) & 0xff));
			data_rank0 = u32_bits_set(data_rank0, 24, 8, ((data_rank1 >> 8) & 0xff));
			__raw_writel(tmp_addr + 0x11*4, data_rank0);
		}
		else
		{
			reg_bits_set(phy_base + 0xd2*4, 4, 4, 1); //reg phy longer rd dl sel db0 <= #'RD reg_wdata[3:0]
			//data_rank0[15:8] = data_rank1[15:8]
			//data_rank0[31:24] = data_rank0[15:8]
			data_rank0 = u32_bits_set(data_rank0, 8, 8, ((data_rank1 >> 8) & 0xff));
			data_rank0 = u32_bits_set(data_rank0, 24, 8, ((data_rank0 >> 8) & 0xff));
			__raw_writel(tmp_addr + 0x11*4, data_rank0);
		}
	}

	if ((wr_bit >> 13) & 0x1)//weye
	{
		data_rank1 = __raw_readl(phy_base + 0xec*4);

		if ((((data_rank1 >> 8 & 0xff) == 0xff) && ((data_rank1 >> 20 & 0xf) == 0xf)) ||
			(((data_rank1 >> 16 & 0xf) == 0xf) && ((data_rank1 & 0xff) == 0xff)))
		{
			ddrc_print_err("Rank WEYE CA training failed because have not right boundary!\r\n");
			while_loop();

		}

		data_rank0 = __raw_readl(tmp_addr + 0x12*4);

		//{data_rank1[19:16], data_rank1[7:0]} = {data_rank0[19:16], data_rank0[7:0]}
		data_rank1_bk = (((data_rank1 >> 16) & 0xf) << 8) | (data_rank1 & 0xff);
		data_rank0_bk = (((data_rank0 >> 16) & 0xf) << 8) | (data_rank0 & 0xff);

		//pre calcute the difference of to rank
		if (data_rank1_bk > data_rank0_bk) //rank 1  db0 longer
		{
			fdl_db0_mul_wr_pre = data_rank1_bk - data_rank0_bk;
			ddrc_training_status_table.wr_shorter_rank_db0 = 0;
		}
		else
		{
			fdl_db0_mul_wr_pre = data_rank0_bk - data_rank1_bk;
			ddrc_training_status_table.wr_shorter_rank_db0 = 1;
			ddrc_training_status_table.wr_shorter_rank = 1;
		}

		//{data_rank1[23:20], data_rank1[15:8]} = {data_rank0[23:20], data_rank0[15:8]}
		data_rank1_bk = (((data_rank1 >> 20) & 0xf) << 8) | ((data_rank1 >> 8) & 0xff);
		data_rank0_bk = (((data_rank0 >> 20) & 0xf) << 8) | ((data_rank0 >> 8) & 0xff);

		if (data_rank1_bk > data_rank0_bk)
		{
			fdl_db1_mul_wr_pre = data_rank1_bk - data_rank0_bk;
			ddrc_training_status_table.wr_shorter_rank_db1 = 0;
		}
		else
		{
			fdl_db1_mul_wr_pre = data_rank0_bk - data_rank1_bk;
			ddrc_training_status_table.wr_shorter_rank_db1 = 1;
		}

		if (ddrc_training_status_table.wr_shorter_rank_db0	!= ddrc_training_status_table.wr_shorter_rank_db1)
			ddrc_print_debug("wr_shorter_rank_dbx different\r\n");

		if (ddrc_training_status_table.wr_shorter_rank_db0 == 0)
		{
			reg_bits_set(phy_base + 0xd2*4, 8, 4, 2); //reg phy longer wr dl sel db0 <= #'RD reg_wdata[11:8]

			data_tmp = __raw_readl(phy_base + 0xd3*4);
			data_tmp= u32_bits_set(data_tmp, 0, 8, (fdl_db0_mul_wr_pre*db0_mst_delay)/256/2);
			__raw_writel(phy_base + 0xd3*4, data_tmp);

			//{data_rank0[19:16], data_rank0[7:0]} = {data_rank0[19:16], data_rank0[7:0]};
			data_rank0 = u32_bits_set(data_rank0, 0, 8, (data_rank0 & 0xff));
			data_rank0 = u32_bits_set(data_rank0, 16, 4, ((data_rank0 >> 16) & 0xf));
			__raw_writel(tmp_addr + 0x12*4, data_rank0);
		}
		else
		{
			reg_bits_set(phy_base + 0xd2*4, 8, 4, 1); //reg phy longer rd dl sel db0 <= #'RD reg_wdata[3:0]

			data_tmp = __raw_readl(phy_base + 0xd3*4);
			data_tmp= u32_bits_set(data_tmp, 0, 8, fdl_db0_mul_wr_pre*db0_mst_delay/256/2);
			__raw_writel(phy_base + 0xd3*4, data_tmp);

			//{data_rank0[19:16], data_rank0[7:0]} = {data_rank1[19:16], data_rank1[7:0]};
			data_rank0 = u32_bits_set(data_rank0, 0, 8, (data_rank1 & 0xff));
			data_rank0 = u32_bits_set(data_rank0, 16, 4, ((data_rank1 >> 16)& 0xf));
			__raw_writel(tmp_addr + 0x12*4, data_rank0);
		}

		if (ddrc_training_status_table.wr_shorter_rank_db1 == 0)
		{
			reg_bits_set(phy_base+ 0xd2*4, 12, 4, 2); //reg phy longer rd dl sel db0 <= #'RD reg_wdata[3:0]

			data_tmp = __raw_readl(phy_base + 0xd3*4);
			data_tmp= u32_bits_set(data_tmp, 8, 8, fdl_db1_mul_wr_pre*db1_mst_delay/256/2);
			__raw_writel(phy_base + 0xd3*4, data_tmp);

			//{data_rank0[23:20], data_rank0[15:8]} = {data_rank0[23:20], data_rank0[15:8]};
			data_rank0 = u32_bits_set(data_rank0, 8, 8, ((data_rank0 >> 8)& 0xff));
			data_rank0 = u32_bits_set(data_rank0, 16, 4, ((data_rank0 >> 20)& 0xf));
			__raw_writel(tmp_addr + 0x12*4, data_rank0);
		}
		else
		{
			//data_tmp = __raw_readl(phy_base + 0xd2*4);
			reg_bits_set(phy_base + 0xd2*4, 12, 4, 1); //reg phy longer rd dl sel db0 <= #'RD reg_wdata[3:0]

			data_tmp = __raw_readl(phy_base + 0xd3*4);
			data_tmp= u32_bits_set(data_tmp, 8, 8, fdl_db1_mul_wr_pre*db1_mst_delay/256/2);
			__raw_writel(phy_base + 0xd3*4, data_tmp);

			//{data_rank0[23:20], data_rank0[15:8]} = {data_rank1[23:20], data_rank1[15:8]};
			data_rank0 = u32_bits_set(data_rank0, 8, 8, ((data_rank1 >> 8)& 0xff));
			data_rank0 = u32_bits_set(data_rank0, 16, 4, ((data_rank1 >> 20)& 0xf));
			__raw_writel(tmp_addr + 0x12*4, data_rank0);
		}

	}
}
void phy_load_ca_perbit_reg(uint32 phy_base, uint32 freq, uint32 rank)
{
	uint32 data_tmp;
	uint32 max_fdl;
	uint32 read_data;
	uint32 data_tmp1, data_tmp2, data_tmp3;
	uint32 data_tmp1_0_7, data_tmp1_8_15, data_tmp1_16_23, data_tmp1_24_31;
	uint32 data_tmp2_0_7, data_tmp2_8_15, data_tmp2_16_23, data_tmp2_24_31;
	uint32 data_tmp3_0_7, data_tmp3_8_15;//data_tmp3_16_23, data_tmp3_24_31;

	read_data = __raw_readl(phy_base + 0xe6*4);
	if (((read_data >> 16) & 0xFF) < 10)
	{
		ddrc_print_err("RANK 0 CA Perbit Training CA window size too small!\r\n");
		while_loop();
	}

	//CA per bit deskew training result
	data_tmp1 = __raw_readl(phy_base + 0xef*4);//train_addr3_fdl_cfg_addr[3/2/1/0]_wr
	data_tmp2 = __raw_readl(phy_base + 0xf0*4);//train_addr7_fdl_cfg_addr[7/6/5/4]_wr
	data_tmp3 = __raw_readl(phy_base + 0xf1*4);//train_addr9_fdl_cfg_addr[9/8]_wr

	max_fdl = 0;

	data_tmp1_0_7 = data_tmp1 & 0xff;//addr0_wr
	data_tmp1_8_15 = (data_tmp1 >> 8) & 0xff;//addr1_wr
	data_tmp1_16_23 = (data_tmp1 >>16) & 0xff;//addr2_wr
	data_tmp1_24_31 = (data_tmp1 >> 24) & 0xff;//addr3_wr

	data_tmp2_0_7 = data_tmp2 & 0xff;//addr4_wr
	data_tmp2_8_15 = (data_tmp2 >> 8) & 0xff;//addr5
	data_tmp2_16_23 = (data_tmp2 >>16) & 0xff;//addr6
	data_tmp2_24_31 = (data_tmp2 >> 24) & 0xff;//addr7

	data_tmp3_0_7 = data_tmp3 & 0xff;//addr8
	data_tmp3_8_15 = (data_tmp3 >> 8) & 0xff;//addr9

	if (data_tmp1_0_7 > max_fdl)	max_fdl = data_tmp1_0_7;
	if (data_tmp1_8_15 > max_fdl)	max_fdl = data_tmp1_8_15;
	if (data_tmp1_16_23 > max_fdl)	max_fdl = data_tmp1_16_23;
	if (data_tmp1_24_31 > max_fdl)	max_fdl = data_tmp1_24_31;
	if (data_tmp2_0_7 > max_fdl)	max_fdl = data_tmp2_0_7;
	if (data_tmp2_8_15 > max_fdl)	max_fdl = data_tmp2_8_15;

	//check fdl result
//	if ((data_tmp1_0_7 == 0x3f) || (data_tmp1_8_15 == 0x3f)||
//		(data_tmp1_16_23 == 0x3f) || (data_tmp1_24_31 == 0x3f) ||
//		(data_tmp2_0_7 == 0x3f) || (data_tmp2_8_15 == 0x3f))
//	{
//		ddrc_print_err("Rank Ca perbit training fail because have not right boundary\r\n");
//		while_loop();
//	}


	max_fdl = 0x3f - max_fdl;
	data_tmp1 = u32_bits_set(data_tmp1, 0, 8, data_tmp1_0_7 + max_fdl);
	data_tmp1 = u32_bits_set(data_tmp1, 8, 8, data_tmp1_8_15 + max_fdl);
	data_tmp1 = u32_bits_set(data_tmp1, 16, 8, data_tmp1_16_23 + max_fdl);
	data_tmp1 = u32_bits_set(data_tmp1, 24, 8, data_tmp1_24_31 + max_fdl);

	data_tmp2 = u32_bits_set(data_tmp2, 0, 8, data_tmp2_0_7 + max_fdl);
	data_tmp2 = u32_bits_set(data_tmp2, 8, 8, data_tmp2_8_15 + max_fdl);

	data_tmp1 = u32_bits_set(data_tmp1, 0, 1, 1);//to create upd pulse, force bit[0] to 0
	__raw_writel((phy_base + 0xb5*4), data_tmp1);//fdl_addr3_wr_cfg_addr[3/2/1/0]
	__raw_writel((phy_base + 0xb6*4), data_tmp2);//fdl_addr7_wr_cfg_addr[7/6/5/4]

}

void phy_load_rw_perbit_reg(uint32 wr_bit, uint32 phy_base, uint32 freq, uint32 rank)
{
	uint32 data_tmp;
	uint32 max_fdl;
	uint32 data_tmp1, data_tmp2, data_tmp3, data_tmp4, data_tmp5;
	uint32 data_tmp1_0_7, data_tmp1_8_15, data_tmp1_16_23, data_tmp1_24_31;
	uint32 data_tmp2_0_7, data_tmp2_8_15, data_tmp2_16_23, data_tmp2_24_31;
	uint32 data_tmp3_0_7, data_tmp3_8_15;//, data_tmp3_16_23, data_tmp3_24_31;
	uint32 data_tmp4_0_7, data_tmp4_8_15, data_tmp4_16_23, data_tmp4_24_31;
	uint32 data_tmp5_0_7, data_tmp5_8_15, data_tmp5_16_23, data_tmp5_24_31;

	max_fdl = 0;
	if (((wr_bit >>9) & 0x1)) //RPERB dm use dq0
	{
		data_tmp1 = __raw_readl(phy_base + 0xf6*4);
		data_tmp2 = __raw_readl(phy_base + 0xf5*4);
		data_tmp3 = __raw_readl(phy_base + 0xf4*4);
		data_tmp4 = __raw_readl(phy_base + 0xf3*4);
		data_tmp5 = __raw_readl(phy_base + 0xf2*4);

		data_tmp1_0_7 = data_tmp1 & 0xff;
		data_tmp1_8_15 = (data_tmp1 >> 8) & 0xff;
		data_tmp1_16_23 = (data_tmp1 >>16) & 0xff;
		data_tmp1_24_31 = (data_tmp1 >> 24) & 0xff;

		data_tmp2_0_7 = data_tmp2 & 0xff;
		data_tmp2_8_15 = (data_tmp2 >> 8) & 0xff;
		data_tmp2_16_23 = (data_tmp2 >>16) & 0xff;
		data_tmp2_24_31 = (data_tmp2 >> 24) & 0xff;

		//check fdl result
//		if ((data_tmp1_24_31 == 0) || (data_tmp1_16_23 ==0) ||
//		(data_tmp1_8_15 == 0) || (data_tmp1_0_7 == 0) ||
//		(data_tmp2_24_31 == 0) || (data_tmp2_16_23 == 0) ||
//		(data_tmp2_8_15 == 0) || (data_tmp2_0_7 == 0))
//		{
//			ddrc_print_err("Read perbit traininig  rank failed because have not right boundary\r\n");
//			while_loop();
//		}

		//set dm to dq0
		//data_tmp3[31:24] = data_tmp2[7:0]
		data_tmp3 = u32_bits_set(data_tmp3, 24, 8, (data_tmp2 & 0xff));//f5[7:0] is reg ro rd db1 dq3 fdl cfg db1 dq0

		data_tmp3_0_7 = data_tmp3 & 0xff;
		data_tmp3_8_15 = (data_tmp3 >> 8) & 0xff;

		data_tmp4_0_7 = data_tmp4 & 0xff;
		data_tmp4_8_15 = (data_tmp4 >> 8) & 0xff;
		data_tmp4_16_23 = (data_tmp4 >>16) & 0xff;
		data_tmp4_24_31 = (data_tmp4 >> 24) & 0xff;

		data_tmp5_16_23 = (data_tmp5 >>16) & 0xff;
		data_tmp5_24_31 = (data_tmp5 >> 24) & 0xff;

//		if ((data_tmp3_8_15 == 0) || (data_tmp3_0_7 == 0) ||
//		(data_tmp4_24_31 == 0) || (data_tmp4_16_23 == 0) ||
//		(data_tmp4_8_15 == 0) || (data_tmp4_0_7 == 0) ||
//		(data_tmp5_24_31 == 0) || (data_tmp5_16_23 == 0))
//		{
//			ddrc_print_err("Read perbit traininig rank failed because have not right boundary\r\n");
//			while_loop();
//		}

		//set dm to dq0
		//data_tmp5[15:8] = data_tmp5[23:16]
		data_tmp5 = u32_bits_set(data_tmp5, 8, 8,((data_tmp5 >> 16) & 0xff));//[23:16] is reg ro rd db0 dq1 fdl cfg db0 dq0
		//PHY read path per bit deskew manual mode setting
		/*0x02F0; 0x02EC; 0x02E8; 0x02E4; 0x02E0*/
		__raw_writel(phy_base + 0xbc*4, data_tmp1);
		__raw_writel(phy_base + 0xbb*4, data_tmp2);
		__raw_writel(phy_base + 0xba*4, data_tmp3);
		__raw_writel(phy_base + 0xb9*4, data_tmp4);
		__raw_writel(phy_base + 0xb8*4, data_tmp5);

		/*0x0388 MLB training search read out register*/
		/*
		bit[3:0] wdqs_search_result_cfg_rdqs_sucess
		*/
		data_tmp = __raw_readl(phy_base + 0xe2*4);
		if ((data_tmp & 0xf) != 0xf)
		{
			ddrc_print_err("perbit read rank training failed\r\n");
			while_loop();
		}
	}

	if ((wr_bit >> 12) & 0x1) //WPERB dm use dq0
	{
		//load WPERB
		data_tmp1 = __raw_readl(phy_base + 0xf7*4);
		data_tmp2 = __raw_readl(phy_base + 0xf8*4);
		data_tmp3 = __raw_readl(phy_base + 0xf9*4);
		data_tmp4 = __raw_readl(phy_base + 0xfa*4);
		data_tmp5 = __raw_readl(phy_base + 0xfb*4);

		//db1
		max_fdl = 0;
		data_tmp1_0_7 = data_tmp1 & 0xff;
		data_tmp1_8_15 = (data_tmp1 >> 8) & 0xff;
		data_tmp1_16_23 = (data_tmp1 >>16) & 0xff;
		data_tmp1_24_31 = (data_tmp1 >> 24) & 0xff;

		data_tmp2_0_7 = data_tmp2 & 0xff;
		data_tmp2_8_15 = (data_tmp2 >> 8) & 0xff;
		data_tmp2_16_23 = (data_tmp2 >>16) & 0xff;
		data_tmp2_24_31 = (data_tmp2 >> 24) & 0xff;

		data_tmp3_0_7 = data_tmp3 & 0xff;
		data_tmp3_8_15 = (data_tmp3 >> 8) & 0xff;
		//data_tmp3_16_23 = (data_tmp3 >>16) & 0xff;
		//data_tmp3_24_31 = (data_tmp3 >> 24) & 0xff;

		if (data_tmp1_24_31 > max_fdl) max_fdl = data_tmp1_24_31;
		if (data_tmp1_16_23 > max_fdl) max_fdl = data_tmp1_16_23;
		if (data_tmp2_24_31 > max_fdl) max_fdl = data_tmp2_24_31;
		if (data_tmp2_16_23 > max_fdl) max_fdl = data_tmp2_16_23;
		if (data_tmp2_8_15 > max_fdl) max_fdl = data_tmp2_8_15;
		if (data_tmp2_0_7 > max_fdl) max_fdl = data_tmp2_0_7;
		if (data_tmp3_8_15 > max_fdl) max_fdl = data_tmp3_8_15;
		if (data_tmp3_0_7 > max_fdl) max_fdl = data_tmp3_0_7;

		//check fdl result
//		if ((data_tmp1_24_31 == 0x3f) || (data_tmp1_16_23 == 0x3f) ||
//		(data_tmp2_24_31 == 0x3f) || (data_tmp2_16_23 == 0x3f) ||
//		(data_tmp2_8_15 == 0x3f) || (data_tmp2_0_7 == 0x3f)||
//		(data_tmp3_8_15 == 0x3f) || (data_tmp3_0_7 == 0x3f))
//		{
//			ddrc_print_err("Write perbit rank traininig failed because 3dc,3e0,3e4 have not right boundary;\r\n");
//			while_loop();
//		}

		max_fdl = 0x3f - max_fdl;
		data_tmp1 = u32_bits_set(data_tmp1, 24, 8, data_tmp1_24_31 + max_fdl);
		data_tmp1 = u32_bits_set(data_tmp1, 16, 8, data_tmp1_16_23 + max_fdl);

		data_tmp2 = u32_bits_set(data_tmp2, 24, 8, data_tmp2_24_31 + max_fdl);
		data_tmp2 = u32_bits_set(data_tmp2, 16, 8, data_tmp2_16_23 + max_fdl);
		data_tmp2 = u32_bits_set(data_tmp2, 8, 8, data_tmp2_8_15 + max_fdl);
		data_tmp2 = u32_bits_set(data_tmp2, 0, 8, data_tmp2_0_7 + max_fdl);
		data_tmp3 = u32_bits_set(data_tmp3, 8, 8, data_tmp3_8_15 + max_fdl);
		data_tmp3 = u32_bits_set(data_tmp3, 0, 8, data_tmp3_0_7 + max_fdl);

		//set dm and dqs
		/*
		[23:16] wr_db0_dq1_fdl_cfg_db0_dq0
		[15:08] wr_db0_dq1_fdl+cfg_db0_dm
		*/
		//data_tmp1[15:8] = data_tmp1[23:16]
		data_tmp1 = u32_bits_set(data_tmp1, 8, 8, ((data_tmp1 >> 16) & 0xff ) );

		//db0
		max_fdl = 0;
		data_tmp4_0_7 = data_tmp4 & 0xff;
		data_tmp4_8_15 = (data_tmp4 >> 8) & 0xff;
		data_tmp4_16_23 = (data_tmp4 >>16) & 0xff;
		data_tmp4_24_31 = (data_tmp4 >> 24) & 0xff;

		data_tmp5_0_7 = data_tmp5 & 0xff;
		data_tmp5_8_15 = (data_tmp5 >> 8) & 0xff;
		data_tmp5_16_23 = (data_tmp5 >>16) & 0xff;
		data_tmp5_24_31 = (data_tmp5 >> 24) & 0xff;

		if (data_tmp4_24_31 > max_fdl) max_fdl = data_tmp4_24_31;
		if (data_tmp4_16_23 > max_fdl) max_fdl = data_tmp4_16_23;
		if (data_tmp4_8_15 > max_fdl) max_fdl = data_tmp4_8_15;
		if (data_tmp4_0_7 > max_fdl) max_fdl = data_tmp4_0_7;

		if (data_tmp5_24_31 > max_fdl) max_fdl = data_tmp5_24_31;
		if (data_tmp5_16_23 > max_fdl) max_fdl = data_tmp5_16_23;
		if (data_tmp5_8_15 > max_fdl) max_fdl = data_tmp5_8_15;
		if (data_tmp5_0_7 > max_fdl) max_fdl = data_tmp5_0_7;

		//check fdl result
//		if ((data_tmp4_24_31 == 0x3f) || (data_tmp4_16_23 ==0x3f) ||
//		(data_tmp4_8_15   == 0x3f) || (data_tmp4_0_7	== 0x3f) ||
//		(data_tmp5_24_31 == 0x3f) || (data_tmp5_16_23 == 0x3f)||
//		(data_tmp5_8_15   == 0x3f) || (data_tmp5_0_7	== 0x3f))
//		{
//			ddrc_print_err("Write perbit rank traininig failed because 3E8,3EC,have not right boundary;\r\n");
//			while_loop();
//		}
		max_fdl = 0x3f -max_fdl;
		data_tmp4 = u32_bits_set(data_tmp4, 24, 8, data_tmp4_24_31 + max_fdl);
		data_tmp4 = u32_bits_set(data_tmp4, 16, 8, data_tmp4_16_23 + max_fdl);
		data_tmp4 = u32_bits_set(data_tmp4, 8, 8, data_tmp4_8_15 + max_fdl);
		data_tmp4 = u32_bits_set(data_tmp4, 0, 8, data_tmp4_0_7 + max_fdl);

		data_tmp5 = u32_bits_set(data_tmp5, 8, 8, data_tmp5_24_31 + max_fdl);
		data_tmp5 = u32_bits_set(data_tmp5, 0, 8, data_tmp5_16_23 + max_fdl);
		data_tmp5 = u32_bits_set(data_tmp5, 8, 8, data_tmp5_8_15 + max_fdl);
		data_tmp5 = u32_bits_set(data_tmp5, 0, 8, data_tmp5_0_7 + max_fdl);

		//set dm and dqs
		/*0x03E4 [31:24]= 0x03E8 [7:0] */
		/*
		0x03E4
		bit[31:24] wr_db1_dm_fdl_cfg_db1_dm
		*/
		/*
		0x03E8
		bit[7:0] wr_db1_dq3_fdl_cfg_db1_dq0
		*/
		//data_tmp3[31:24] = data_tmp4[7:0]
		data_tmp3 = u32_bits_set(data_tmp3, 24, 8, (data_tmp4 & 0xff ) );
		data_tmp1 = u32_bits_set(data_tmp1, 16, 1, 0x1);

		/*PHY write path per bit deskew manual mode setting*/
		/*0x02F4; 0x02F8; 0x02FC; 0x0300; 0x0304*/
		__raw_writel(phy_base + 0xbd*4, data_tmp1);
		__raw_writel(phy_base + 0xbe*4, data_tmp2);
		__raw_writel(phy_base + 0xbf*4, data_tmp3);
		__raw_writel(phy_base + 0xc0*4, data_tmp4);
		__raw_writel(phy_base + 0xc1*4, data_tmp5);

		/*
			0x0388 MLB training search read out register
			bit[7:4] wdqs_search_result_cfg_wrdq_sucess
		*/
		data_tmp = __raw_readl(phy_base + 0xe2*4);
		if (((data_tmp >> 4) & 0xf) != 0xf)
		{
			ddrc_print_err("Perbit write rank training failed\r\n");
			while_loop();
		}
	}
}

void odt_set_for_ca_train(uint32 phy_base, uint32 freq_sel, uint32	odt_on)
{
	uint32 data_tmp;
	uint32 tmp_addr = phy_base + freq_sel *20*4;

	if (odt_on)
	{
		/*F0-7 phy otd and ocd setting*/
		/*bit[22:20] rpull_cfg_ca_drvp*/
		/*bit[18:16] rpull_cfg_ca_drvp*/
		/*bit[14:12] rpull_cfg_data_drvp*/
		/*bit[10:8] rpull_cfg_data_drvn*/
		/*bit[6:4] rpull_cfg_odtp*/
		/*bit[2:0] rpull_cfg_odtn*/
		/*but*/
		data_tmp = __raw_readl(tmp_addr + 0x9*4);
		data_tmp= u32_bits_set(data_tmp, 0, 3, 0x2);	//120Ohm
		data_tmp= u32_bits_set(data_tmp, 4, 3, 0x0);
		__raw_writel(tmp_addr + 0x9*4, data_tmp);
	}
	else
	{
		data_tmp = __raw_readl(tmp_addr + 0x9*4);//0x0024
		data_tmp= u32_bits_set(data_tmp, 0, 3, 0x0);//rpull_cfg_odtn
		data_tmp= u32_bits_set(data_tmp, 4, 3, 0x0);//rpull_cfg_odtp
		__raw_writel(tmp_addr + 0x9*4, data_tmp);

	}
	/*F0-7 PHY read odt and write odt control*/
	/*bit[31] mlb_wrodt_alwayson_cfg_wrodt_alwaysoff*/
	/*bit[26:24] mlb_wrodt_alwayson_cfg_wrodt_en_dly*/
	/*bit[21:16] mlb_wrodt_alwayson_cfg_wrodt_cnt_intg*/
	/*bit[15] mlb_wrodt_alwayson_cfg_rdodt_alwayson*/
	/*bit[10:8] mlb_wrodt_alwayson_cfg_rdodt_en_dly*/
	/*bit[5:0] mlb_wrodt_alwayson_cfg_rdodt_cnt_intg*/
	reg_bits_set((tmp_addr + 0xa*4), 15, 1, odt_on);

}

uint32 trigger_training_done(uint32 wr_bit, uint32 rd_bit)
{
	uint32 src_rank = 0;
	uint32 data_tmp;
	uint32 read_data;
	uint32 ret = 0;
	uint32 count = 3;
	/*step 0) add for modify rank*/
	if (ddrc_training_status_table.rank1_training_done)
	{
		if((wr_bit >> 6) & 0x1) //ca training
		{
			data_tmp = __raw_readl(DMC_GUCPHY0_BASE + 0xac*4);
			src_rank = (data_tmp >> 12) & 0x3;//dat_tmp[13:12] mlb_multi_rank_cfg_multi_rank

			reg_bits_set((DMC_GUCPHY0_BASE + 0xac*4), 12, 2, ddrc_training_status_table.ca_shorter_rank);//cfg_multi_rank
			reg_bits_set((DMC_GUCPHY1_BASE + 0xac*4), 12, 2, ddrc_training_status_table.ca_shorter_rank);//cfg_multi_rank
		}
		if((wr_bit >> 13) & 0x1)	//wr training
		{
			data_tmp = __raw_readl(DMC_GUCPHY0_BASE + 0xac*4);
			src_rank = (data_tmp >> 12) & 0x3;//dat_tmp[13:12] mlb_multi_rank_cfg_multi_rank

			reg_bits_set((DMC_GUCPHY0_BASE + 0xac*4), 12, 2, ddrc_training_status_table.wr_shorter_rank);//cfg_multi_rank
			reg_bits_set((DMC_GUCPHY1_BASE + 0xac*4), 12, 2, ddrc_training_status_table.wr_shorter_rank);//cfg_multi_rank
		}
	}

	/*step 1) training start traininig*/
	/*0x02cc training enable control
	[31:24] mlb_train_wdqs_stop_step_cfg_wdqs_stop_step
	[22:20] mlb_train_wdqs_stop_step_cfg_wdqs_top_intg
	[18:16] mlb_train_wdqs_stop_step_cfg_data_training_mode
	[15:15] mlb_train_wdqs_stop_step_cfg_gate_fast_mode
	[14:14] mlb_train_wdqs_stop_step_cfg_wrvref_disable
	[13:13] mlb_train_wdqs_stop_step_cfg_wreye_enable
	[12:12] mlb_train_wdqs_stop_step_cfg_wr_perbit_disable
	[11:11] mlb_train_wdqs_stop_step_cfg_rdvref_disable
	[10:10] mlb_train_wdqs_stop_step_cfg_rdeye_enable
	[9] mlb_train_wdqs_stop_step_cfg_rd_perbit_disable
	[8] mlb_train_wdqs_stop_step_cfg_train_gate_enable
	[6] mlb_train_wdqs_stop_step_cfg_train_ca_enable
	[5] mlb_train_wdqs_stop_step_cfg_ca_perbit_disable
	[4] mlb_train_wdqs_stop_step_cfg_cal_ncomp_first
	[3] mlb_train_wdqs_stop_step_cfg_cal_manual_pwrdn
	[2] mlb_train_wdqs_stop_step_cfg_cal_manual_mode
	[1] mlb_train_wdqs_stop_step_cfg_disable
	[0] mlb_train_wdqs_stop_step_cfg_train_start
	*/
	data_tmp = __raw_readl(DMC_GUCPHY0_BASE + 0xB3*4);//mlb_train_wdqs_stop_step_cfg_XX
	__raw_writel(DMC_GUCPHY0_BASE + 0xB3*4, data_tmp^wr_bit);

	data_tmp = __raw_readl(DMC_GUCPHY1_BASE + 0xB3*4);//mlb_train_wdqs_stop_step_cfg_XX
	__raw_writel(DMC_GUCPHY1_BASE + 0xB3*4, data_tmp^wr_bit);

	/*step 2) polling training done*/
	/*0x00358 DDR PHY status read out register*/
	/*
	[27] ro_phy_stat_cfg_train_done
	[26] ro_phy_stat_cfg_train_start
	[25] ro_phy_stat_cfg_vref_done
	[24] ro_phy_stat_cfg_vref_start
	[23] ro_phy_stat_cfg_wteye_done
	[22] ro_phy_stat_cfg_wteye_start
	[21] ro_phy_stat_cfg_wt_perbit_done
	[20] ro_phy_stat_cfg_wt_perbit_start
	[19] ro_phy_stat_cfg_rdeye_done
	[18] ro_phy_stat_cfg_rdeye_start
	[17] ro_phy_stat_cfg_rd_perbit_done
	[16] ro_phy_stat_cfg_rd_perbit_start
	[15] ro_phy_stat_cfg_gate_done
	[14] ro_phy_stat_cfg_gate_start
	[13] ro_phy_stat_cfg_wlvl_done
	[12] ro_phy_stat_cfg_wlvl_start
	[11] ro_phy_stat_cfg_ca_done
	[10] ro_phy_stat_cfg_ca_start
	[9]  ro_phy_stat_cfg_ca_perbit_done
	[8]  ro_phy_stat_cfg_ca_perbit_start
	[7]  ro_phy_stat_cfg_automrs_done
	[6]  ro_phy_stat_cfg_automrs_start
	[5]  ro_phy_stat_cfg_runtime_fail
	[4]  ro_phy_stat_cfg_runtime_done
	[3]  ro_phy_stat_cfg_cal_fail
	[2]  ro_phy_stat_cfg_iopvt_done
	[1]  ro_phy_stat_cfg_dfi_done
	[0]  ro_phy_stat_cfg_pll_lock
	*/
	count = 300;
	do{
		dmc_sprd_delay(100);
		count--;
		read_data = __raw_readl(DMC_GUCPHY0_BASE + 0xd6*4);
		data_tmp = read_data & rd_bit;
		if (data_tmp == rd_bit)
		{
			ret = TRUE;
			break;
		}
		else
		{
			ret = FALSE;
		}
	}while(count);
	count = 300;
	do{
		dmc_sprd_delay(100);
		count--;
		read_data = __raw_readl(DMC_GUCPHY1_BASE + 0xd6*4);
		data_tmp = read_data & rd_bit;
		if (data_tmp == rd_bit)
		{
			ret = TRUE;
			break;
		}
		else
		{
			ret = FALSE;
		}
	}while(count);

	/*step 3) add for modify rank*/
	if (ddrc_training_status_table.rank1_training_done)
	{
		reg_bits_set(DMC_GUCPHY0_BASE + 0xac*4, 12, 2, src_rank);//cfg_multi_rank
		reg_bits_set(DMC_GUCPHY1_BASE + 0xac*4, 12, 2, src_rank);//cfg_multi_rank
	}
	return ret;
}
void disable_this_training(uint32 wr_bit)
{
	uint32 data_tmp;
	dmc_dosoft_cmd_setting(0x80200000);//dsoft_auto_ref

	data_tmp = __raw_readl(DMC_GUCPHY0_BASE + 0xB3*4);
	__raw_writel(DMC_GUCPHY0_BASE + 0xB3*4, data_tmp^wr_bit);

	data_tmp = __raw_readl(DMC_GUCPHY1_BASE + 0xB3*4);
	__raw_writel(DMC_GUCPHY1_BASE + 0xB3*4, data_tmp^wr_bit);
}
void ddrc_phy_disable_all_training(void)
{
	uint32 data_tmp;
	data_tmp = __raw_readl(DMC_GUCPHY0_BASE + 0xB3*4);
	data_tmp &= (~0xFFFF);
	__raw_writel(DMC_GUCPHY0_BASE + 0xB3*4, (data_tmp | 0xDA22));
	data_tmp = __raw_readl(DMC_GUCPHY1_BASE + 0xB3*4);
	data_tmp &= (~0xFFFF);
	__raw_writel(DMC_GUCPHY1_BASE + 0xB3*4, (data_tmp | 0xDA22));
};

void ddrc_ctrl_mode_setting(uint32 wr_bit)
{
#if 0
	//DDRC_R1P1_REG_INFO_PTR pdmc = (DDRC_R1P1_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	uint32 data_tmp;
	if (((wr_bit >> 14) & 1) == 1)
	{
		data_tmp = reg_bits_get((DMC_GUCPHY0_BASE + 0xe9*4), 24, 6);
		/*
		pdmc->dmc_dcfg2 = data_tmp;
		pdmc->dmc_dcfg1 = 0x810000E;//mr14 write vref(dq)
		while(((pdmc->dmc_dcfg1 >> 19) & 0x1ff) != 0);
		*/
//		data_tmp |= (1<<6);//enable range1
		(lpddr4_mr_info.p_odt_cfg + phy_train.freq_sel)->mr14 = u32_bits_set((lpddr4_mr_info.p_odt_cfg + phy_train.freq_sel)->mr14, 0, 6, data_tmp);
		lpddr_dmc_mrw(CMD_CS_BOTH, 14, (lpddr4_mr_info.p_odt_cfg + phy_train.freq_sel)->mr14);
		dmc_sprd_delay(200);//vrcg
	}
#endif
}
void rw_eye_training_flow(uint32 wr_bit, uint32 rd_bit, uint32 freq_sel, uint32 rank)
{
	trigger_training_done(wr_bit, rd_bit);

	//step 1) read training result and write to manual mode register
	if (rank == 0)
	{
		phy_reload_rank_0_reg(wr_bit, DMC_GUCPHY0_BASE, freq_sel, rank);
		phy_reload_rank_0_reg(wr_bit, DMC_GUCPHY1_BASE, freq_sel, rank);
	}
	else
	{
		phy_reload_rank_1_reg(wr_bit, DMC_GUCPHY0_BASE, freq_sel, rank);
		phy_reload_rank_1_reg(wr_bit, DMC_GUCPHY1_BASE, freq_sel, rank);
	}
	if((ddrc_training_config_table[rank][freq_sel].perbitrd_enable)\
	|| (ddrc_training_config_table[rank][freq_sel].perbitwr_enable))
	{
		/*step 3) read traininig result and write to manual mode register*/
		phy_load_rw_perbit_reg(wr_bit, DMC_GUCPHY0_BASE, freq_sel, phy_train.rank);
		phy_load_rw_perbit_reg(wr_bit, DMC_GUCPHY1_BASE, freq_sel, phy_train.rank);
		//db0
		reg_bits_set(DMC_GUCPHY0_BASE + 0xbd*4, 16, 1, 0);//to create upd pulse toggle[0]
		reg_bits_set(DMC_GUCPHY1_BASE + 0xbd*4, 16, 1, 0);//to create upd pulse toggle[0]
		reg_bits_set(DMC_GUCPHY0_BASE + 0xbd*4, 16, 1, 1);//to create upd pulse toggle[0]
		reg_bits_set(DMC_GUCPHY1_BASE + 0xbd*4, 16, 1, 1);//to create upd pulse toggle[0]
		reg_bits_set(DMC_GUCPHY0_BASE + 0xbd*4, 16, 1, 0);//to create upd pulse toggle[0]
		reg_bits_set(DMC_GUCPHY1_BASE + 0xbd*4, 16, 1, 0);//to create upd pulse toggle[0]
		//db1
		reg_bits_set(DMC_GUCPHY0_BASE + 0xc0*4, 0, 1, 0);//to create upd pulse toggle[0]
		reg_bits_set(DMC_GUCPHY1_BASE + 0xc0*4, 0, 1, 0);//to create upd pulse toggle[0]
		reg_bits_set(DMC_GUCPHY0_BASE + 0xc0*4, 0, 1, 1);//to create upd pulse toggle[0]
		reg_bits_set(DMC_GUCPHY1_BASE + 0xc0*4, 0, 1, 1);//to create upd pulse toggle[0]
		reg_bits_set(DMC_GUCPHY0_BASE + 0xc0*4, 0, 1, 0);//to create upd pulse toggle[0]
		reg_bits_set(DMC_GUCPHY1_BASE + 0xc0*4, 0, 1, 0);//to create upd pulse toggle[0]
		dmc_sprd_delay(200);
	}

	//step 2) soft send precharge all and auto refres
	dmc_dosoft_cmd_setting(0x80100000);//dsoft_pre_all

	ddrc_ctrl_mode_setting(wr_bit);
	//step 5) disable this training
	disable_this_training(wr_bit);
}
void phy_gate_seq(uint32 freq_sel)
{
	uint32 wr_bit = BIT08_GATE;
	uint32 rd_bit = BIT15_GATE_DONE;
	ddrc_print_debug("gate training start.\r\n");

	ddrc_phy_rpull_set_for_gate_train_pre(DMC_GUCPHY0_BASE, freq_sel);
	ddrc_phy_rpull_set_for_gate_train_pre(DMC_GUCPHY1_BASE, freq_sel);
	while(FALSE == trigger_training_done(wr_bit, rd_bit))
	{
		ddrc_print_debug("gate training not done.\r\n");
		start_watchdog(1);
		while (1) ;
	}

	phy_reload_rank0_gate(wr_bit, DMC_GUCPHY0_BASE, freq_sel, 0);
	phy_reload_rank0_gate(wr_bit, DMC_GUCPHY1_BASE, freq_sel, 0);

	/*soft send precharge all and auto refresh*/
	dmc_dosoft_cmd_setting(0x80100000);//dsoft_pre_all

	/*disable this training*/
	disable_this_training(wr_bit);
	ddrc_phy_rpull_set_for_gate_train_post(DMC_GUCPHY0_BASE, freq_sel);
	ddrc_phy_rpull_set_for_gate_train_post(DMC_GUCPHY1_BASE, freq_sel);

}
void phy_rwvref_seq(uint32 freq_sel, uint32 rw_sel, uint32 rank)
{
	uint32 wr_bit = BIT14_WVREF;
	uint32 rd_bit = BIT23_WREYE_DONE;
	if (rw_sel == 0)
	{
		wr_bit = BIT11_RVREF;
		rd_bit = BIT19_RDEYE_DONE;
		//read_manual_mode
		reg_bits_set(DMC_GUCPHY0_BASE + 0xb2*4, 2, 1, 0);
		reg_bits_set(DMC_GUCPHY1_BASE + 0xb2*4, 2, 1, 0);
	}
	else
	{
		//write manual_mode
		reg_bits_set(DMC_GUCPHY0_BASE + 0xb2*4, 3, 1, 0);
		reg_bits_set(DMC_GUCPHY1_BASE + 0xb2*4, 3, 1, 0);
	}

	rw_eye_training_flow(wr_bit, rd_bit, freq_sel, rank);
}

void read_cmos_vref_set(uint32 freq_sel, uint32 rw_sel)
{
	uint32 regval;

	regval = __raw_readl(DMC_GUCPHY0_BASE + (freq_sel*20*4) + 0x6*4);
	if ((rw_sel == 0) && (regval & (1 << 11)))
	{
		/*read cmos mode*/
		reg_bits_set(DMC_GUCPHY0_BASE + 0xc8*4, 8, 8, 0x48);
		reg_bits_set(DMC_GUCPHY1_BASE + 0xc8*4, 8, 8, 0x48);
	}
	else
	{
		reg_bits_set(DMC_GUCPHY0_BASE + 0xc8*4, 8, 8, 0);
		reg_bits_set(DMC_GUCPHY1_BASE + 0xc8*4, 8, 8, 0);
	}
}

void phy_rweye_seq(uint32 freq_sel, uint32 rw_sel, uint32 rank)
{
	uint32 wr_bit = BIT13_WREYE;
	uint32 rd_bit = BIT23_WREYE_DONE;

	read_cmos_vref_set(freq_sel, rw_sel);

	if (rw_sel == 0)
	{
		wr_bit = BIT10_RDEYE;
		rd_bit = BIT19_RDEYE_DONE;
		if (ddrc_training_config_table[rank][freq_sel].rdvref_train_enable)
		{
			wr_bit |= BIT11_RVREF;
		}
		if (ddrc_training_config_table[rank][freq_sel].perbitrd_enable)
		{
			ddrc_training_status_table.rdperbit_done =1 ;
			wr_bit |= BIT09_RPERB;
			rd_bit |= BIT17_RPERB_DONE;
		}
		//read_manual_mode
		reg_bits_set(DMC_GUCPHY0_BASE + 0xb2*4, 2, 1, 0);
		reg_bits_set(DMC_GUCPHY1_BASE + 0xb2*4, 2, 1, 0);
	}
	else
	{	//write manual_mode
		reg_bits_set(DMC_GUCPHY0_BASE + 0xb2*4, 3, 1, 0);
		reg_bits_set(DMC_GUCPHY1_BASE + 0xb2*4, 3, 1, 0);
		if (ddrc_training_config_table[rank][freq_sel].wrvref_train_enable)
		{
			wr_bit |= BIT14_WVREF;
		}
		if (ddrc_training_config_table[rank][freq_sel].perbitwr_enable)
		{
			ddrc_training_status_table.wrperbit_done = 1;
			wr_bit |= BIT12_WPERB;
			rd_bit |= BIT21_WPERB_DONE;
		}
	}

	rw_eye_training_flow(wr_bit, rd_bit, freq_sel, rank);
}

void phy_rwpbit_seq(uint32 freq_sel, uint32 rw_sel)
{
	uint32 wr_bit = BIT12_WPERB;
	uint32 rd_bit = BIT23_WREYE_DONE;

	if (rw_sel == 0)
	{
		wr_bit = BIT09_RPERB;
		rd_bit = BIT19_RDEYE_DONE;
		ddrc_training_status_table.rdperbit_done =1 ;
		//read_manual_mode
		reg_bits_set(DMC_GUCPHY0_BASE + 0xb2*4, 2, 1, 0);
		reg_bits_set(DMC_GUCPHY1_BASE + 0xb2*4, 2, 1, 0);
	}
	else
	{
		ddrc_training_status_table.wrperbit_done = 1;
		//write manual_mode
		reg_bits_set(DMC_GUCPHY0_BASE + 0xb2*4, 3, 1, 0);
		reg_bits_set(DMC_GUCPHY1_BASE + 0xb2*4, 3, 1, 0);
	}

	trigger_training_done(wr_bit, rd_bit);

	/*step 3) read traininig result and write to manual mode register*/
	phy_load_rw_perbit_reg(wr_bit, DMC_GUCPHY0_BASE, freq_sel, phy_train.rank);
	phy_load_rw_perbit_reg(wr_bit, DMC_GUCPHY1_BASE, freq_sel, phy_train.rank);
	//db0
	reg_bits_set(DMC_GUCPHY0_BASE + 0xbd*4, 16, 1, 0);//to create upd pulse toggle[0]
	reg_bits_set(DMC_GUCPHY1_BASE + 0xbd*4, 16, 1, 0);//to create upd pulse toggle[0]
	reg_bits_set(DMC_GUCPHY0_BASE + 0xbd*4, 16, 1, 1);//to create upd pulse toggle[0]
	reg_bits_set(DMC_GUCPHY1_BASE + 0xbd*4, 16, 1, 1);//to create upd pulse toggle[0]
	reg_bits_set(DMC_GUCPHY0_BASE + 0xbd*4, 16, 1, 0);//to create upd pulse toggle[0]
	reg_bits_set(DMC_GUCPHY1_BASE + 0xbd*4, 16, 1, 0);//to create upd pulse toggle[0]
	//db1
	reg_bits_set(DMC_GUCPHY0_BASE + 0xc0*4, 0, 1, 0);//to create upd pulse toggle[0]
	reg_bits_set(DMC_GUCPHY1_BASE + 0xc0*4, 0, 1, 0);//to create upd pulse toggle[0]
	reg_bits_set(DMC_GUCPHY0_BASE + 0xc0*4, 0, 1, 1);//to create upd pulse toggle[0]
	reg_bits_set(DMC_GUCPHY1_BASE + 0xc0*4, 0, 1, 1);//to create upd pulse toggle[0]
	reg_bits_set(DMC_GUCPHY0_BASE + 0xc0*4, 0, 1, 0);//to create upd pulse toggle[0]
	reg_bits_set(DMC_GUCPHY1_BASE + 0xc0*4, 0, 1, 0);//to create upd pulse toggle[0]
	dmc_sprd_delay(200);

	/*step 4) soft send precharge all and auto refresh*/
	dmc_dosoft_cmd_setting(0x80100000);

//	if (ddr_chip_cur.chip_type == DRAM_LPDDR4)
	{
		ddrc_ctrl_mode_setting(wr_bit);
	}

	/*step 5) disable this training*/
	disable_this_training(wr_bit);
}
int phy_caeye_seq(uint32 freq_sel, uint32 rank)
{
	uint32 wr_bit = BIT06_CA;
	uint32 rd_bit  = BIT11_CA_DONE;
	uint32 data_tmp;
	int regval1,regval2;

	if (ddrc_training_config_table[rank][freq_sel].ca_perbit_enable)
	{
		wr_bit |= BIT05_CA_PERB;
		rd_bit |= BIT11_CA_DONE;
		ddrc_training_status_table.caperbit_done = 1;
	}
	//ca manual mode
	reg_bits_set(DMC_GUCPHY0_BASE + 0xb2*4, 0, 1, 0);
	reg_bits_set(DMC_GUCPHY1_BASE + 0xb2*4, 0, 1, 0);

	ddrc_print_debug("CA Training Start !\r\n");

	ddrc_phy_io_get(DMC_GUCPHY0_BASE, phy_train.freq_sel);
	ddrc_phy_io_get(DMC_GUCPHY1_BASE, phy_train.freq_sel);
	/*step 1) special set for CA*/
	odt_set_for_ca_train(DMC_GUCPHY0_BASE, freq_sel, 1);
	odt_set_for_ca_train(DMC_GUCPHY1_BASE, freq_sel, 1);

	/*step 2) selfrefresh for LP4 ca training*/
//	if (ddr_chip_cur.chip_type == DRAM_LPDDR4)
	{
		data_tmp = reg_bits_get((DMC_REG_ADDR_BASE_PHY + 0x0124), 24, 2);
		if (data_tmp != 0x3  )//ch0_rfdmem_cmd_chip_sleep
		{
			dmc_dosoft_cmd_setting(0x80100000);//bit[20] dosoft_precharge_all
			dmc_dosoft_cmd_setting(0x80200000);//bit[21] dosoft_auto_ref
			dmc_dosoft_cmd_setting(0x80400000);//bit[22] dosoft_self_ref
		}
	}


	/*step 4) cfg_vref_ca_disable 0x02b0*/
	reg_bits_set(DMC_GUCPHY0_BASE + 0xac*4, 1, 1, 1);//mlb_multi_rank_cfg_vref_ca_disable
	reg_bits_set(DMC_GUCPHY1_BASE + 0xac*4, 1, 1, 1);//mlb_multi_rank_cfg_vref_ca_disable

	trigger_training_done(wr_bit, rd_bit);

	/*step 6) read training result and write to manual mode register*/
	regval1 = ca_reload_rank_reg(DMC_GUCPHY0_BASE, freq_sel, rank);
	regval2 = ca_reload_rank_reg(DMC_GUCPHY1_BASE, freq_sel, rank);
	if (ddrc_training_config_table[rank][freq_sel].ca_perbit_enable)
	{
		phy_load_ca_perbit_reg(DMC_GUCPHY0_BASE, freq_sel, rank);
		phy_load_ca_perbit_reg(DMC_GUCPHY1_BASE, freq_sel, rank);

		reg_bits_set((DMC_GUCPHY0_BASE + 0xb5*4), 0, 1, 0);//to create upd pulse toggle[0]
		reg_bits_set((DMC_GUCPHY1_BASE + 0xb5*4), 0, 1, 0);//to create upd pulse toggle[0]
		reg_bits_set((DMC_GUCPHY0_BASE + 0xb5*4), 0, 1, 1);//to create upd pulse toggle[0]
		reg_bits_set((DMC_GUCPHY1_BASE + 0xb5*4), 0, 1, 1);//to create upd pulse toggle[0]
		reg_bits_set((DMC_GUCPHY0_BASE + 0xb5*4), 0, 1, 0);//to create upd pulse toggle[0]
		reg_bits_set((DMC_GUCPHY1_BASE + 0xb5*4), 0, 1, 0);//to create upd pulse toggle[0]
		dmc_sprd_delay(200);
	}

	/*step 7) soft send precharge all and auto refresh*/
	data_tmp = reg_bits_get((DMC_REG_ADDR_BASE_PHY + 0x124), 24, 2);
	if (data_tmp == 0x3)
	{
		dmc_dosoft_cmd_setting(0x80800000);//dsoft_resume
	}
	dmc_dosoft_cmd_setting(0x80100000);//dsoft_precharge_all

	/*step 8) disable this training*/
	disable_this_training(wr_bit);

	/*step9) special set for ca traininig*/
	ddrc_phy_io_set(DMC_GUCPHY0_BASE, phy_train.freq_sel);
	ddrc_phy_io_set(DMC_GUCPHY1_BASE, phy_train.freq_sel);
//	odt_set_for_ca_train(DMC_GUCPHY0_BASE, freq_sel, 0);
//	odt_set_for_ca_train(DMC_GUCPHY1_BASE, freq_sel, 0);

	/*step 10) check training result*/
	/*0x0398 CA training coarse and fine delay training*/
	/*
	[31:31] vref_dram_ca_train_cfg_fail
	[29:24] vref_dram_ca_result_cfg_vref_dram
	[23:16] vref_dram_ca_pass_window
	[15:08] vref_dram_ca_result_cfg_fine
	[07:00] vref_dram_ca_result_cfg_coarse
	*/
	if ((regval1 < 0) || (regval2 < 0))
		return -1;

	data_tmp = reg_bits_get((DMC_GUCPHY0_BASE + 0xe6*4), 31, 1);
	if (data_tmp)
	{
		ddrc_print_err("PHY 0  rank CA traininig  failed\r\n");
		return -2;
	}

	data_tmp = reg_bits_get((DMC_GUCPHY1_BASE + 0xe6*4), 31, 1);
	if ((data_tmp >> 31) & 0x1)
	{
		ddrc_print_err("PHY 1 rank CA traininig failed\r\n");
		return -2;
	}
	return 1;

}

void phy_caperbit_seq(uint32 freq_sel, uint32 rank)
{
	uint32 wr_bit = BIT05_CA_PERB;
	uint32 rd_bit  = BIT11_CA_DONE;
	uint32 data_tmp;
	ddrc_training_status_table.caperbit_done = 1;
	//ca manual mode
	reg_bits_set(DMC_GUCPHY0_BASE + 0xb2*4, 0, 1, 0);
	reg_bits_set(DMC_GUCPHY1_BASE + 0xb2*4, 0, 1, 0);

	/*step 1) special set for CA*/
	odt_set_for_ca_train(DMC_GUCPHY0_BASE, freq_sel, 1);
	odt_set_for_ca_train(DMC_GUCPHY1_BASE, freq_sel, 1);

	/*step 2) selfrefresh for LP4 ca training*/
//	if (ddr_chip_cur.chip_type == DRAM_LPDDR4)
	{
		data_tmp = reg_bits_get((DMC_REG_ADDR_BASE_PHY + 0x124), 24, 2);
		if (data_tmp != 0x3)//ch0_rfdmem_cmd_chip_sleep
		{
			dmc_dosoft_cmd_setting(0x80100000);//bit[20] dosoft_pre_all
			dmc_dosoft_cmd_setting(0x80200000);//bit[21] dosoft_auto_ref
			dmc_dosoft_cmd_setting(0x80400000);//bit[22] dosoft_self_ref
		}
	}
//	else //for lpddr3
//	{
//		/*step 0.2) special set for lpddr3 perbit training*/
//		/*0x02B0 MLB training setting*/
//		/*bit[3] mlb_multi_rank_cfg_ca_end_bt*/
//		if ((wr_bit >> 5) & 0x1) //CA PERB
//		{
//			reg_bits_set((DMC_GUCPHY0_BASE + 0xac*4), 3, 1, 1);
//			reg_bits_set((DMC_GUCPHY1_BASE + 0xac*4), 3, 1, 1);
//		}
//	}

	/*step 3) cfg_vref_ca_disable */
	//0x02B0 bit[1] mbl_multi_rank_cfg_vref_ca_disable
	reg_bits_set((DMC_GUCPHY0_BASE + 0xac*4), 1, 1, 1);//mlb_multi_rank_cfg_vref_ca_disable
	reg_bits_set((DMC_GUCPHY1_BASE + 0xac*4), 1, 1, 1);//mlb_multi_rank_cfg_vref_ca_disable

	/*step 4) polling training done*/
	trigger_training_done(wr_bit, rd_bit);


	/*step 5) read training result and write to manual mode register*/
	phy_load_ca_perbit_reg(DMC_GUCPHY0_BASE, freq_sel, rank);
	phy_load_ca_perbit_reg(DMC_GUCPHY1_BASE, freq_sel, rank);

	reg_bits_set((DMC_GUCPHY0_BASE + 0xb5*4), 0, 1, 0);//to create upd pulse toggle[0]
	reg_bits_set((DMC_GUCPHY1_BASE + 0xb5*4), 0, 1, 0);//to create upd pulse toggle[0]
	reg_bits_set((DMC_GUCPHY0_BASE + 0xb5*4), 0, 1, 1);//to create upd pulse toggle[0]
	reg_bits_set((DMC_GUCPHY1_BASE + 0xb5*4), 0, 1, 1);//to create upd pulse toggle[0]
	reg_bits_set((DMC_GUCPHY0_BASE + 0xb5*4), 0, 1, 0);//to create upd pulse toggle[0]
	reg_bits_set((DMC_GUCPHY1_BASE + 0xb5*4), 0, 1, 0);//to create upd pulse toggle[0]
	dmc_sprd_delay(200);

	/*step 6) soft send precharge all and auto refresh*/
	data_tmp = reg_bits_get((DMC_REG_ADDR_BASE_PHY + 0x124), 24, 2);
	if (data_tmp == 0x3  )
	{
		dmc_dosoft_cmd_setting(0x80800000);//dsoft_resume
	}
	dmc_dosoft_cmd_setting(0x80100000);//dsoft_pre_all


	/*step 7) disable this training*/
	disable_this_training(wr_bit);

	/*step 7) special set for ca traininig*/
	odt_set_for_ca_train(DMC_GUCPHY0_BASE, freq_sel, 0);
	odt_set_for_ca_train(DMC_GUCPHY1_BASE, freq_sel, 0);

	/*step 8) check training result*/
	data_tmp = reg_bits_get((DMC_GUCPHY0_BASE + 0xe6*4), 31, 1);//0x0398
	if (data_tmp)
	{
		ddrc_print_err("phy 0 ca perbit traininig failed\r\n");
		while_loop();
	}

	data_tmp = reg_bits_get((DMC_GUCPHY1_BASE + 0xe6*4), 31, 1);
	if (data_tmp)
	{
		ddrc_print_err("phy 1 ca perbit traininig failed\r\n");
		while_loop();
	}
}

void training_process_ctrl_pre(uint32 phy_base, uint32 freq_sel, uint32 rank)
{
	uint32 tmp_addr = phy_base + (freq_sel*20*4);

	//step 1) cfg multi rank
	reg_bits_set(phy_base + 0xac*4, 12, 2, rank);

	//step 2) disable dcc clock gate and setting manual mode
	//bit[8]dcc_ag_en_cfg_dcc_ag_en
	//reg_bits_set(tmp_addr + 0xb*4, 8, 1, 0);

	//step 3) rpull cfg
//	reg_bits_set(tmp_addr + 0x9*4, 31, 1, 1); //cfg_rpull  ??
//	reg_bits_set(tmp_addr + 0x9*4, 24, 1, 0);//cfg_rup
//	reg_bits_set(tmp_addr + 0x9*4, 28, 1, 0);//cfg_rdn

	dmc_sprd_delay(400);
}

void training_process_ctrl_post(uint32 phy_base, uint32 freq_sel)
{
	//uint32 tmp_addr = phy_base + (freq_sel* 20*4);

	//step 1) enable manual mode
	reg_bits_set(phy_base + 0xb2*4, 0, 4, 0xf);

	//step 2) enable dcc_ag_en
	//reg_bits_set(tmp_addr + 0xb*4, 8, 1, 1);

	//step 3) cfg multi rank
	reg_bits_set(phy_base + 0xac*4, 12, 2, 0);
}

void ddrc_phy_training_conditions(uint32 freq_sel, uint32 rank)
{

	reg_bits_set(DMC_GUCPHY0_BASE + 0x2e0, 0,  8, 0x0);
	reg_bits_set(DMC_GUCPHY1_BASE + 0x2e0, 0,  8, 0x0);
	reg_bits_set(DMC_GUCPHY0_BASE + 0x2e8, 16, 8, 0x0);
	reg_bits_set(DMC_GUCPHY1_BASE + 0x2e8, 16, 8, 0x0);
	reg_bits_set(DMC_GUCPHY0_BASE + 0x2F4, 0,  8, 0x0);
	reg_bits_set(DMC_GUCPHY1_BASE + 0x2F4, 0,  8, 0x0);
	reg_bits_set(DMC_GUCPHY0_BASE + 0x2FC, 16, 8, 0x0);
	reg_bits_set(DMC_GUCPHY1_BASE + 0x2FC, 16, 8, 0x0);
	if (0x8 == ddr_chip_cur.cs0_jedec_info->dw)
	{
//		ddrc_training_config_table[rank][freq_sel].cabt_enable = 0;
	}
	reg_bits_set(DMC_GUCPHY0_BASE + 0x2e0, 0,  8, 0x1f);
	reg_bits_set(DMC_GUCPHY1_BASE + 0x2e0, 0,  8, 0x1f);
	reg_bits_set(DMC_GUCPHY0_BASE + 0x2e8, 16, 8, 0x1f);
	reg_bits_set(DMC_GUCPHY1_BASE + 0x2e8, 16, 8, 0x1f);
	reg_bits_set(DMC_GUCPHY0_BASE + 0x2F4, 0,  8, 0x3f);
	reg_bits_set(DMC_GUCPHY1_BASE + 0x2F4, 0,  8, 0x3f);
	reg_bits_set(DMC_GUCPHY0_BASE + 0x2FC, 16, 8, 0x3f);
	reg_bits_set(DMC_GUCPHY1_BASE + 0x2FC, 16, 8, 0x3f);
}


void cabt_preset(uint32 freq)
{
	reg_bits_set((DMC_GUCPHY0_BASE + 0x280), 12, 1, 1);
	reg_bits_set((DMC_GUCPHY1_BASE + 0x280), 12, 1, 1);
	/********** sharkl3 ca hw training, two rank recive cbt cmd ************/
	//if (LP4_PINMUX_CASE0	== ddr_chip_cur.pinmux_case)
	//{
	//	REG32(DMC_GUCPHY0_BASE + 0x338) = 0x1ac6A008;
	//	REG32(DMC_GUCPHY1_BASE + 0x338) = 0x1ac68407;
	//}
	//else if(LP4_PINMUX_CASE1	== ddr_chip_cur.pinmux_case)
	//{
	//	REG32(DMC_GUCPHY0_BASE + 0x338) = 0x1ac6A008;
	//	REG32(DMC_GUCPHY1_BASE + 0x338) = 0x1ac88407;
	//}
	//else if(LP4_PINMUX_CASE2	== ddr_chip_cur.pinmux_case)
	//{
	//	REG32(DMC_GUCPHY0_BASE + 0x338) = 0x1ac6A038;
	//	REG32(DMC_GUCPHY1_BASE + 0x338) = 0x1ac68436;
	//}
	//else if(LP3_PINMUX_CASE0	== ddr_chip_cur.pinmux_case)
	//{
	//	REG32(DMC_GUCPHY0_BASE + 0x338) = 0x1ac69082;
	//	REG32(DMC_GUCPHY1_BASE + 0x338) = 0x1ac69005;
	//}
	//else if(LP3_PINMUX_CASE1	== ddr_chip_cur.pinmux_case)
	//{
	//	REG32(DMC_GUCPHY0_BASE + 0x338) = 0x1ac69082;
	//	REG32(DMC_GUCPHY1_BASE + 0x338) = 0x1ac69016;
	//}
	//else
	//{
	//}
	/***************************************************************/
	/********** sharkl3 ca vref hw training, vref set 0 ************/
	//if (ddr_chip_cur.chip_type == DRAM_LPDDR4)
	//{
	//	reg_bits_set(((DMC_GUCPHY0_BASE + (freq_sel*20*4)) + 0x8*4), 24, 1, 0);
	//	reg_bits_set(((DMC_GUCPHY1_BASE + (freq_sel*20*4)) + 0x8*4), 24, 1, 0);
	//}
	/***************************************************************/
}

void cabt_postset(uint32 freq)
{
	reg_bits_set((DMC_GUCPHY0_BASE + 0x280), 12, 1, 0);
	reg_bits_set((DMC_GUCPHY1_BASE + 0x280), 12, 1, 0);
	/********** sharkl3 ca hw training, two rank recive cbt cmd ************/
	//if (LP4_PINMUX_CASE0	== ddr_chip_cur.pinmux_case)
	//{
	//	REG32(DMC_GUCPHY0_BASE + 0x338) = 0x1ac68808;
	//	REG32(DMC_GUCPHY1_BASE + 0x338) = 0x1ac68107;
	//}
	//else if(LP4_PINMUX_CASE1	== ddr_chip_cur.pinmux_case)
	//{
	//	REG32(DMC_GUCPHY0_BASE + 0x338) = 0x1ac68808;
	//	REG32(DMC_GUCPHY1_BASE + 0x338) = 0x1ac88107;
	//}
	//else if(LP4_PINMUX_CASE2	== ddr_chip_cur.pinmux_case)
	//{
	//	REG32(DMC_GUCPHY0_BASE + 0x338) = 0x1ac68838;
	//	REG32(DMC_GUCPHY1_BASE + 0x338) = 0x1ac68136;
	//}
	//else if(LP3_PINMUX_CASE0	== ddr_chip_cur.pinmux_case)
	//{
	//	REG32(DMC_GUCPHY0_BASE + 0x338) = 0x1ac68882;
	//	REG32(DMC_GUCPHY1_BASE + 0x338) = 0x1ac68805;
	//}
	//else if(LP3_PINMUX_CASE1	== ddr_chip_cur.pinmux_case)
	//{
	//	REG32(DMC_GUCPHY0_BASE + 0x338) = 0x1ac68882;
	//	REG32(DMC_GUCPHY1_BASE + 0x338) = 0x1ac68816;
	//}
	//else
	//{
	//}
	/***************************************************************/

	/********** sharkl3 ca vref hw training, vref set 0 ************/
	//if (ddr_chip_cur.chip_type == DRAM_LPDDR4)
	//{
	//	reg_bits_set(((DMC_GUCPHY0_BASE + (freq_sel*20*4)) + 0x8*4), 24, 1, 1);
	//	reg_bits_set(((DMC_GUCPHY1_BASE + (freq_sel*20*4)) + 0x8*4), 24, 1, 1);
	//}
	/***************************************************************/
}

int ddrc_phy_training_seq(uint32 this_freq, uint32 freq_sel, uint32 rank)
{
	uint32 regval;
	uint32 read_data;
	int ca_result = 0;
	//step 0) for special satuation, reconfig the conditions for training
	ddrc_phy_training_conditions(freq_sel, rank);

	//step 1) setting some phy register for training mode this will change global argument
	training_process_ctrl_pre(DMC_GUCPHY0_BASE, freq_sel, phy_train.rank);
	training_process_ctrl_pre(DMC_GUCPHY1_BASE, freq_sel, phy_train.rank);

	//step 2) trigger mlb training
	{
		//ca perbit training, all frequencies  only need do once.
		if (ddrc_training_config_table[rank][freq_sel].ca_perbit_enable)
		{
//			phy_caperbit_seq(freq_sel, rank);
		}

		if (ddrc_training_config_table[rank][freq_sel].cabt_enable)
		{
			cabt_preset(freq_sel);
			regval = 0;
			while(1)
			{
				ca_result = phy_caeye_seq(freq_sel, rank);
				if (ca_result == 1 && regval < 10)
				{
					break;
				}
				regval ++;
				if (regval >= 10)
				{
//					ddrc_ca_debug = regval;
					while_loop();
				}
			}
			cabt_postset(freq_sel);
		}

		if (ddrc_training_config_table[rank][freq_sel].gate_enable == 1)
		{
			phy_gate_seq(freq_sel);
		}

		//read perbit training
		if (ddrc_training_config_table[rank][freq_sel].perbitrd_enable)
		{
//			phy_rwpbit_seq(freq_sel, 0);
		}

		if (ddrc_training_config_table[rank][freq_sel].rdvref_train_enable)
		{
//			phy_rwvref_seq(freq_sel, 0, rank);
		}

		if (ddrc_training_config_table[rank][freq_sel].reye_enable)
		{
			phy_rweye_seq(freq_sel, 0, rank);
		}

		//werit perbit training
		if (ddrc_training_config_table[rank][freq_sel].perbitwr_enable)
		{
//			phy_rwpbit_seq(freq_sel, 1);
		}

		if (ddrc_training_config_table[rank][freq_sel].wrvref_train_enable)
		{
//			phy_rwvref_seq(freq_sel, 1, rank);
		}

		if (ddrc_training_config_table[rank][freq_sel].weye_enable)
		{
			phy_rweye_seq(freq_sel, 1, rank);
		}
	}
	dmc_exit_self_refresh(1);
	lpddr_dmc_mrw(CMD_CS_BOTH, 0xD, 0x08);
	dmc_sprd_delay(2000);//vrcg

	//step 5) this frequency end need go into selfrefresh mode
	dmc_entry_self_refresh(1);

	//step 6) training post setting
	training_process_ctrl_post(DMC_GUCPHY0_BASE, freq_sel);
	training_process_ctrl_post(DMC_GUCPHY1_BASE, freq_sel);
	return 0;
}

void ddrc_phy_reset(uint32 on)
{
	reg_bits_set(REG_DMC_RST_CTL, 0, 1, on);
	dmc_sprd_delay(50);
}


void lpddr4_set_pre(uint32 phy_base, uint32 freq_sel)
{
	uint32 this_freq = find_ddr_freq(freq_sel);
	switch (this_freq)
	{
		case 1866:
			REG32(phy_base + 0x294) = DMC_GUCPHY_LP4_1866_294_DATA;
			REG32(phy_base + 0x298) = DMC_GUCPHY_LP4_1866_298_DATA;
			REG32(phy_base + 0x29C) = DMC_GUCPHY_LP4_1866_29C_DATA;
			REG32(phy_base + 0x2A0) = DMC_GUCPHY_LP4_1866_2A0_DATA;
			REG32(phy_base + 0x2A4) = DMC_GUCPHY_LP4_1866_2A4_DATA;
			REG32(phy_base + 0x2BC) = DMC_GUCPHY_LP4_1866_2BC_DATA;
			break;
		case 1536:
			REG32(phy_base + 0x294) = DMC_GUCPHY_LP4_1536_294_DATA;
			REG32(phy_base + 0x298) = DMC_GUCPHY_LP4_1536_298_DATA;
			REG32(phy_base + 0x29C) = DMC_GUCPHY_LP4_1536_29C_DATA;
			REG32(phy_base + 0x2A0) = DMC_GUCPHY_LP4_1536_2A0_DATA;
			REG32(phy_base + 0x2A4) = DMC_GUCPHY_LP4_1536_2A4_DATA;
			REG32(phy_base + 0x2BC) = DMC_GUCPHY_LP4_1536_2BC_DATA;
			break;
		case 1333:
			REG32(phy_base + 0x294) = DMC_GUCPHY_LP4_1333_294_DATA;
			REG32(phy_base + 0x298) = DMC_GUCPHY_LP4_1333_298_DATA;
			REG32(phy_base + 0x29C) = DMC_GUCPHY_LP4_1333_29C_DATA;
			REG32(phy_base + 0x2A0) = DMC_GUCPHY_LP4_1333_2A0_DATA;
			REG32(phy_base + 0x2A4) = DMC_GUCPHY_LP4_1333_2A4_DATA;
			REG32(phy_base + 0x2BC) = DMC_GUCPHY_LP4_1333_2BC_DATA;
			break;
		case 1024:
			REG32(phy_base + 0x294) = DMC_GUCPHY_LP4_1024_294_DATA;
			REG32(phy_base + 0x298) = DMC_GUCPHY_LP4_1024_298_DATA;
			REG32(phy_base + 0x29C) = DMC_GUCPHY_LP4_1024_29C_DATA;
			REG32(phy_base + 0x2A0) = DMC_GUCPHY_LP4_1024_2A0_DATA;
			REG32(phy_base + 0x2A4) = DMC_GUCPHY_LP4_1024_2A4_DATA;
			REG32(phy_base + 0x2BC) = DMC_GUCPHY_LP4_1024_2BC_DATA;
			break;
		case 768:
			REG32(phy_base + 0x294) = DMC_GUCPHY_LP4_768_294_DATA;
			REG32(phy_base + 0x298) = DMC_GUCPHY_LP4_768_298_DATA;
			REG32(phy_base + 0x29C) = DMC_GUCPHY_LP4_768_29C_DATA;
			REG32(phy_base + 0x2A0) = DMC_GUCPHY_LP4_768_2A0_DATA;
			REG32(phy_base + 0x2A4) = DMC_GUCPHY_LP4_768_2A4_DATA;
			REG32(phy_base + 0x2BC) = DMC_GUCPHY_LP4_768_2BC_DATA;
			break;
		case 667:
			REG32(phy_base + 0x294) = DMC_GUCPHY_LP4_667_294_DATA;
			REG32(phy_base + 0x298) = DMC_GUCPHY_LP4_667_298_DATA;
			REG32(phy_base + 0x29C) = DMC_GUCPHY_LP4_667_29C_DATA;
			REG32(phy_base + 0x2A0) = DMC_GUCPHY_LP4_667_2A0_DATA;
			REG32(phy_base + 0x2A4) = DMC_GUCPHY_LP4_667_2A4_DATA;
			REG32(phy_base + 0x2BC) = DMC_GUCPHY_LP4_667_2BC_DATA;
			break;
		case 384:
			REG32(phy_base + 0x294) = DMC_GUCPHY_LP4_384_294_DATA;
			REG32(phy_base + 0x298) = DMC_GUCPHY_LP4_384_298_DATA;
			REG32(phy_base + 0x29C) = DMC_GUCPHY_LP4_384_29C_DATA;
			REG32(phy_base + 0x2A0) = DMC_GUCPHY_LP4_384_2A0_DATA;
			REG32(phy_base + 0x2A4) = DMC_GUCPHY_LP4_384_2A4_DATA;
			REG32(phy_base + 0x2BC) = DMC_GUCPHY_LP4_384_2BC_DATA;
			break;
		case 256:
			REG32(phy_base + 0x294) = DMC_GUCPHY_LP4_256_294_DATA;
			REG32(phy_base + 0x298) = DMC_GUCPHY_LP4_256_298_DATA;
			REG32(phy_base + 0x29C) = DMC_GUCPHY_LP4_256_29C_DATA;
			REG32(phy_base + 0x2A0) = DMC_GUCPHY_LP4_256_2A0_DATA;
			REG32(phy_base + 0x2A4) = DMC_GUCPHY_LP4_256_2A4_DATA;
			REG32(phy_base + 0x2BC) = DMC_GUCPHY_LP4_256_2BC_DATA;
			break;

		default:
			break;
	}

}




void training_set_pre(uint32 phy_base, uint32 freq_sel)
{
	uint32 this_freq = find_ddr_freq(freq_sel);
	uint32 tmp_addr = phy_base + freq_sel*20*4;
//	  if ((ddrc_training_config_table[phy_train.rank][freq_sel].gate_enable)||(ddrc_training_config_table[phy_train.rank][freq_sel].cabt_enable))
	{
		lpddr4_set_pre(phy_base, freq_sel);
	}
	//set CA manual vref

	if (ddrc_training_config_table[phy_train.rank][freq_sel].cabt_enable)
	{
//		reg_bits_set((tmp_addr + 0xc*4), 0, 1, 1);//ca_rang_manu_delay_bt
//		reg_bits_set((tmp_addr + 0xc*4), 8, 8, 0);//ca_rang_manu_cfg_delay
	}

}



/*setting second dll mode*/
void write_back_deskew_dll(uint32 phy_base, uint32 freq_sel)
{
	uint32 read_data;
	uint32 wrbk_data;
	uint32 data_tmp;
	uint32 tmp_addr;
	uint32 rd_coarse;
	uint32 regval;
	uint32 cur_freq = find_ddr_freq(freq_sel);

	tmp_addr = phy_base + freq_sel*20*4;
	//step 1) read out coarse tuning resluts and write back to WR register
	//0xd8*4 bit[7:6] deskew_dll_status_reg01_cfg_clk_pos
	read_data = reg_bits_get((phy_base + 0xd8*4), 6, 2);
	reg_bits_set((tmp_addr + 0x4*4), 18, 2, read_data); //cfg_dll_clk_pos

	/*step 2) read out coarse tuning result and write back*/
	rd_coarse = __raw_readl(phy_base + 0xd7*4);
	/*0x035c
	 *bit[31] deskew_dll_status_reg00_cfg_dll_lock
	 *bit[30] deskew_dll_status_reg00_cfg_first_pass
	 *bit[29] deskew_dll_status_reg00_cfg_fail_flag
	 *bit[28] deskew_dll_status_reg00_cfg_agj_saturat
	 *bit[27:18] deskew_dll_status_reg00_cfg_fine_dly
	 *bit[17:14] deskew_dll_status_reg00_cfg_cnt_unlock
	 *bit[13:08] deskew_dll_status_reg00_cfg_cnt_lock
	 *bit[07:00] deskew_dll_status_reg00_cfg_cnt_continus
	 * */
	if (cur_freq > 400)
	{
		regval = (rd_coarse >> 18) & 0x1FF;
		regval = (regval >= 10) ? (regval - 10) : 0;
		rd_coarse = u32_bits_set(rd_coarse, 18, 9, regval);
	}
	regval = (rd_coarse >> 18) & 0xFF;
	/*F0-7 Deskew dll reg 1 setting*/
	/*bit[31] dll_1_cfg_dll_mode_en*/
	/*bit[30:26] dll_1_cfg_cyc_rst*/
	/*bit[25:21] dll_1_cfg_cyc_check*/
	/*bit[20:16] dll_1_cfg_cyc_found*/
	/*bit[15:08] dll_1_cfg_adj_ini_lo*/
	/*bit[07:00] dll_1_cfg_adj_coarse_lo*/
	wrbk_data = __raw_readl(tmp_addr + 0x3*4);
	wrbk_data = u32_bits_set(wrbk_data, 0, 8, regval);
	wrbk_data = u32_bits_set(wrbk_data, 8, 8, regval);
	__raw_writel(tmp_addr + 0x3*4,	wrbk_data);
	/*F0-7 Deskew dll reg 2 setting*/
	/*bit[31:29] dll_2_cfg_adjs0_cyc*/
	/*bit[28:26] dll_2_cfg_adjs1_cyc*/
	/*bit[25:23] dll_2_cfg_adjs2_cyc*/
	/*bit[22]	 dll_2_cfg_adj_v_coafse*/
	/*bit[21:20] dll_2_cfg_coarse_tune_mode*/
	/*bit[19;18] dll_2_cfg_dll_clk_pos_i*/
	/*bit[16]	 dll_2_cfg_adj_ini_hi*/
	/*bit[14]	 dll_2_cfg_agj_coarse_hi*/
	/*bit[9]	 dll_2_cfg_det_en1*/
	/*bit[8]	 dll_2_cfg_det_start1*/
	/*bit[7:5]	 dll_2_cfg_det_period1*/
	/*bit[4]	 dll_2_cfg_det_en0*/
	/*bit[3]	 dll_2_cfg_det_start0*/
	/*bit[2:0]	 dll_2_cfg_det_period0*/
	wrbk_data = __raw_readl(tmp_addr + 0x4*4);
	regval = (rd_coarse >> 26) & 0x1;
	wrbk_data = u32_bits_set(wrbk_data, 14, 1, regval);
	wrbk_data = u32_bits_set(wrbk_data, 16, 1, regval);
	wrbk_data = u32_bits_set(wrbk_data, 20, 3, 0x0);//bit[21:20] coarse_tune_mode (3:bypass tuning by appling 1st training coarse tune)
							//bit[22] adj_v_coarse
	__raw_writel(tmp_addr + 0x4*4, wrbk_data);

	/*step 3) set fine tune bypass*/
	/*F0-7 Deskew dll reg 0 setting*/
	/*bit[1] dll_0_cfg_fine_tune_bypass*/
//	read_data = __raw_readl(tmp_addr + 0x2*4);
//	regval = cur_freq < 533 ? 1 : 0;
//	read_data = u32_bits_set(read_data, 1, 1, regval);
//	REG32(tmp_addr + 0x2*4) = read_data;

	/*step 4) write back acc init delay*/
	/*F0--7 DLL max and min value*/
	/*bit[24:16] min_delay_value*/
	/*bit[08:00] max_delay_value*/
	//read_data = __raw_readl(phy_base + 0xdf*4);
	//bit[8:0]phy_db0_dll_cfg_1st
	//regval = (read_data & 0x1ff);

	read_data = REG32(phy_base + (0x104 + freq_sel) * 4);
	regval = ((read_data >> 16) & 0x1ff);

	if ((cur_freq > 256) && (phy_base == DMC_GUCPHY0_BASE))
	{
		if ((regval == 0x1FF) || ((read_data & 0x1FF) == 0x1FF))
		{
			ddrc_print_err("ACC min/max delay value error!\r\n");
			while_loop();
		}
	}
	if (cur_freq > 1066)
	{
		if (regval >= 0)
			regval -= 0;
		else
			regval = 0;
	}
	else if (cur_freq > 384)
	{
		if (regval >= 40)
			regval -= 40;
		else
			regval = 0;
	}
	else
	{
		if (regval >= 10)
			regval -= 10;
		else
			regval = 0;
	}
	if (reg_bits_get((tmp_addr + 0x7*4), 31, 1) == 0)
	{
	read_data = u32_bits_set(read_data, 16, 9, regval);
	data_tmp = __raw_readl(tmp_addr + 0x7*4);
	//acc init delay;data_tmp[21:16] = read_data[24:19]
	/*bit[21:16] master delay line initial deyal, start value setting*/
	data_tmp = u32_bits_set(data_tmp, 16, 6, ((read_data >> 19) & 0x3f));
	__raw_writel(tmp_addr + 0x7*4, data_tmp);
	}
}

void master_dll_lock_seq()
{
	unsigned int regval;
	uint32 freq_sel = phy_train.freq_sel;
	DDRC_R1P1_REG_INFO_PTR pdmc = (DDRC_R1P1_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;

	/*step 1. setting rf phy init start ahb to high*/
	pdmc->dmc_cfg3 = 0xf;

	/*step 2. polling rf phy dfi init complete*/
	do {
		regval = pdmc->dmc_cfg3;
		regval &= 0xf0000;
	}while (regval != 0xf0000);

	/*step 3. disable dfi init start*/
	pdmc->dmc_cfg3 = 0;
	/*step 4. write back deskew dll setting*/
	#ifndef PXP_DEBUG
	write_back_deskew_dll(DMC_GUCPHY0_BASE, freq_sel);
	write_back_deskew_dll(DMC_GUCPHY1_BASE, freq_sel);
	#endif
	/*save dll result for dfs hold time*/
	//REG32(DMC_GUCPHY0_BASE + (freq_select*4)) = REG32(DMC_GUCPHY0_BASE + 0x037C);
}

void ddrc_phy_init_flow(uint32 this_freq, uint32 freq_sel, uint32 rank)
{
	/*step 7) training really process*/
	ddrc_phy_training_seq(this_freq, freq_sel, rank);
}


void ddrc_phy_reg_set(unsigned int *phy_base_addr)
{
	int i;
	unsigned int *pPhyBase = phy_base_addr;

	for(i=0; i<sizeof(phy_cfg_data_lp4)/sizeof(phy_cfg_data_lp4[0]); i++)
	{
		*(pPhyBase++) = phy_cfg_data_lp4[i];
	}

	pPhyBase = phy_base_addr+0xa0*4/4;
	for(i=0; i<sizeof(phy_cfg_common_data_lp4)/sizeof(phy_cfg_common_data_lp4[0]); i++)
	{
		*(pPhyBase++) = phy_cfg_common_data_lp4[i];
	}
}

void ddrc_phy_io_mode_setting(void)
{
	if (ddr_chip_cur.chip_type == DRAM_LPDDR4)
	{
		reg_bits_set(DMC_GUCPHY0_BASE + (0xa2 * 4), 13, 1, 0x0);
		reg_bits_set(DMC_GUCPHY1_BASE + (0xa2 * 4), 13, 1, 0x0);
	}
	else if ((ddr_chip_cur.chip_type == DRAM_LPDDR4X) || (ddr_chip_cur.chip_type == DRAM_LPDDR4Y))
	{
		reg_bits_set(DMC_GUCPHY0_BASE + (0xa2 * 4), 13, 1, 0x1);
		reg_bits_set(DMC_GUCPHY1_BASE + (0xa2 * 4), 13, 1, 0x1);
	}
}

void ddrc_phy_nmos_setting()
{
	if((ddr_chip_cur.chip_type == DRAM_LPDDR4) || (ddr_chip_cur.chip_type == DRAM_LPDDR4X))
	{
		reg_bits_set(DMC_GUCPHY0_BASE + (0xa0*4), 14, 2, 0x0);	// [14]:dqs, [15]:clk
		reg_bits_set(DMC_GUCPHY1_BASE + (0xa0*4), 14, 2, 0x0);	// [14]:dqs, [15]:clk
	}
	else if(ddr_chip_cur.chip_type == DRAM_LPDDR4Y)
	{
		reg_bits_set(DMC_GUCPHY0_BASE + (0xa0*4), 14, 2, 0x3);	// [14]:dqs, [15]:clk
		reg_bits_set(DMC_GUCPHY1_BASE + (0xa0*4), 14, 2, 0x3);	// [14]:dqs, [15]:clk
	}
}

void ddrc_phy_mode_setting()
{
	if((ddr_chip_cur.chip_type == DRAM_LPDDR4) || (ddr_chip_cur.chip_type == DRAM_LPDDR4X) || (ddr_chip_cur.chip_type == DRAM_LPDDR4Y))
	{
		reg_bits_set(DMC_GUCPHY0_BASE + (0xa1*4), 3, 1, 0x0);	// 0:non-lp3, 1:lp3
		reg_bits_set(DMC_GUCPHY1_BASE + (0xa1*4), 3, 1, 0x0);	// 0:non-lp3, 1:lp3
		reg_bits_set(DMC_GUCPHY0_BASE + (0xa1*4), 4, 1, 0x1);	// 0:non-lp4, 1:lp4
		reg_bits_set(DMC_GUCPHY1_BASE + (0xa1*4), 4, 1, 0x1);	// 0:non-lp4, 1:lp4
	}
	else if(ddr_chip_cur.chip_type == DRAM_LPDDR3)
	{
		reg_bits_set(DMC_GUCPHY0_BASE + (0xa1*4), 3, 1, 0x1);	// 0:non-lp3, 1:lp3
		reg_bits_set(DMC_GUCPHY1_BASE + (0xa1*4), 3, 1, 0x1);	// 0:non-lp3, 1:lp3
		reg_bits_set(DMC_GUCPHY0_BASE + (0xa1*4), 4, 1, 0x0);	// 0:non-lp4, 1:lp4
		reg_bits_set(DMC_GUCPHY1_BASE + (0xa1*4), 4, 1, 0x0);	// 0:non-lp4, 1:lp4
	}
}

void ddrc_phy_pin_mux_setting(void)
{
	if (ddr_chip_cur.pinmux_case == LP4_PINMUX_CASE0)
	{
		__raw_writel(DMC_GUCPHY0_BASE + 0x32C, 0x37010707);
		__raw_writel(DMC_GUCPHY0_BASE + 0x330, 0x76548230);
		__raw_writel(DMC_GUCPHY0_BASE + 0x334, 0x65482301);
		__raw_writel(DMC_GUCPHY0_BASE + 0x338, 0x00068817);
		__raw_writel(DMC_GUCPHY0_BASE + 0x33C, 0x76102345);
		__raw_writel(DMC_GUCPHY0_BASE + 0x340, 0x10000098);
		__raw_writel(DMC_GUCPHY0_BASE + 0x350, 0x76541280);
		__raw_writel(DMC_GUCPHY0_BASE + 0x354, 0x65412803);

		__raw_writel(DMC_GUCPHY1_BASE + 0x32C, 0x37010707);
		__raw_writel(DMC_GUCPHY1_BASE + 0x330, 0x76548230);
		__raw_writel(DMC_GUCPHY1_BASE + 0x334, 0x65482301);
		__raw_writel(DMC_GUCPHY1_BASE + 0x338, 0x00068817);
		__raw_writel(DMC_GUCPHY1_BASE + 0x33C, 0x76102345);
		__raw_writel(DMC_GUCPHY1_BASE + 0x340, 0x10000098);
		__raw_writel(DMC_GUCPHY1_BASE + 0x350, 0x76541280);
		__raw_writel(DMC_GUCPHY1_BASE + 0x354, 0x65412803);
	}
	else if (ddr_chip_cur.pinmux_case == LP4_PINMUX_CASE1)
	{
		reg_bits_set(DMC_GUCPHY0_BASE + 0xcb*4, 24, 8, 0x41);
		__raw_writel(DMC_GUCPHY0_BASE + 0xcc*4, 0x86107324);
		__raw_writel(DMC_GUCPHY0_BASE + 0xcd*4, 0x50832715);
		__raw_writel(DMC_GUCPHY0_BASE + 0xce*4, 0x1AC68846);
		__raw_writel(DMC_GUCPHY0_BASE + 0xcf*4, 0x76235041);
		reg_bits_set(DMC_GUCPHY0_BASE + 0xd1*4, 12, 4, 0x1);
		__raw_writel(DMC_GUCPHY0_BASE + 0xd4*4, 0x36802154);
		__raw_writel(DMC_GUCPHY0_BASE + 0xd5*4, 0x76832057);

		reg_bits_set(DMC_GUCPHY1_BASE + 0xcb*4, 24, 8, 0x47);
		__raw_writel(DMC_GUCPHY1_BASE + 0xcc*4, 0x86017243);
		__raw_writel(DMC_GUCPHY1_BASE + 0xcd*4, 0x40863525);
		__raw_writel(DMC_GUCPHY1_BASE + 0xce*4, 0x1AC68817);
		__raw_writel(DMC_GUCPHY1_BASE + 0xcf*4, 0x76250314);
		reg_bits_set(DMC_GUCPHY1_BASE + 0xd0*4, 0, 9, 0x98);
		reg_bits_set(DMC_GUCPHY1_BASE + 0xd1*4, 12, 4, 0x1);
		__raw_writel(DMC_GUCPHY1_BASE + 0xd4*4, 0x36810245);
		__raw_writel(DMC_GUCPHY1_BASE + 0xd5*4, 0x31620857);
	}
	else
	{
		reg_bits_set(DMC_GUCPHY0_BASE + 0xcb*4, 24, 8, 0x46);
		__raw_writel(DMC_GUCPHY0_BASE + 0xcc*4, 0x84210376);
		__raw_writel(DMC_GUCPHY0_BASE + 0xcd*4, 0x75862105);
		__raw_writel(DMC_GUCPHY0_BASE + 0xce*4, 0x1AC68843);
		__raw_writel(DMC_GUCPHY0_BASE + 0xcf*4, 0x76520431);
		reg_bits_set(DMC_GUCPHY0_BASE + 0xd1*4, 12, 4, 0x1);
		__raw_writel(DMC_GUCPHY0_BASE + 0xd4*4, 0x10862543);
		__raw_writel(DMC_GUCPHY0_BASE + 0xd5*4, 0x35872107);

		reg_bits_set(DMC_GUCPHY1_BASE + 0xcb*4, 24, 8, 0x41);
		__raw_writel(DMC_GUCPHY1_BASE + 0xcc*4, 0x84120763);
		__raw_writel(DMC_GUCPHY1_BASE + 0xcd*4, 0x65832705);
		__raw_writel(DMC_GUCPHY1_BASE + 0xce*4, 0x1AC68841);
		__raw_writel(DMC_GUCPHY1_BASE + 0xcf*4, 0x76504213);
		reg_bits_set(DMC_GUCPHY1_BASE + 0xd0*4, 0, 9, 0x98);
		reg_bits_set(DMC_GUCPHY1_BASE + 0xd1*4, 12, 4, 0x1);
		__raw_writel(DMC_GUCPHY1_BASE + 0xd4*4, 0x21860453);
		__raw_writel(DMC_GUCPHY1_BASE + 0xd5*4, 0x65832707);

	}
}

void ddrc_phy_perbit_set_seq(void)
{
//	if (ddr_chip_cur.chip_type == DRAM_LPDDR3)
//	{
//		REG32(DMC_GUCPHY0_BASE + 0x02E0) = 0X05010100;
//		REG32(DMC_GUCPHY0_BASE + 0x02E4) = 0X05080204;
//		REG32(DMC_GUCPHY0_BASE + 0x02E8) = 0X05000507;
//		REG32(DMC_GUCPHY0_BASE + 0x02EC) = 0X05080606;
//		REG32(DMC_GUCPHY0_BASE + 0x02F0) = 0X09060508;
//		REG32(DMC_GUCPHY1_BASE + 0x02E0) = 0X01040300;
//		REG32(DMC_GUCPHY1_BASE + 0x02E4) = 0X08070506;
//		REG32(DMC_GUCPHY1_BASE + 0x02E8) = 0X04000404;
//		REG32(DMC_GUCPHY1_BASE + 0x02EC) = 0X06010205;
//		REG32(DMC_GUCPHY1_BASE + 0x02F0) = 0X02030304;
//	}
}
void ddrc_phy_pre_set_seq(void)
{
	/*Step1. SW setting the PHY register according to the lpx_register_table_x16_v001 for PHY0 */
	ddrc_phy_reg_set((unsigned int *)DMC_GUCPHY0_BASE);

	/*Step2. SW setting the PHY register according to the lpx_register_table_x16_v001 for PHY1*/
	ddrc_phy_reg_set((unsigned int *)DMC_GUCPHY1_BASE);

	/*step 3. setting pin mux*/
	ddrc_phy_pin_mux_setting();

	ddrc_phy_disable_all_training();

	ddrc_phy_io_mode_setting();
	/*update read perbit window*/
	ddrc_phy_perbit_set_seq();
}

void ddrc_phy_post_set_seq(void)
{
	ddrc_phy_post_setting(DMC_GUCPHY0_BASE);
	ddrc_phy_post_setting(DMC_GUCPHY1_BASE);
}

void ddrc_phy_post_setting_rpull(uint32 phy_base)
{
	uint32 tmp_addr;
	uint32 data_tmp;
	int i;
	/*PHY odt and oct setting for set fx*/
	//set rpull base on gate edge mode
	for (i = MIN_FREQ_SEL; i <= MAX_FREQ_SEL; i++)
	{
		tmp_addr = phy_base + (i *20 *4);
		data_tmp = REG32(tmp_addr + (0x9 * 4));
		data_tmp= u32_bits_set(data_tmp, 31, 1, 1);//phy_pad_rpull
		data_tmp= u32_bits_set(data_tmp, 24, 1, 0);//phy_pad_rpu edge mode without odt lp3
		data_tmp= u32_bits_set(data_tmp, 28, 1, 0);//phy_pad_rpd edge mode without odt lp4
		REG32(tmp_addr + (0x9 * 4)) = data_tmp;
	}
}
static uint32 dqs_to_dq_get(uint32 addr)
{
	uint32 dqs_to_dq;
	uint32 db0_dqs;
	uint32 db1_dqs;
	/*
	*db0_dll_wrdeye_dq
	*[7:0] write DQS to DQ fine phase manual mode setting of data module 0,
	*the phase shift for write data strobe is defined as following, 0x: 01
	*1/256*T of ddr_ck, 0x: 02 2/256*T of ddr_ck, ……0x:80, 128/256*T of ddr_ck, (90shift) ……..0x:FF, 255/256*T of ddr_ck
	*db1_dll_wrdeye_dq
	*[15:8] write DQS to DQ  fine phase manual mode setting of data module 1,
	*the phase shift for write data strobe is defined as following, 0x: 01
	*1/256*T of ddr_ck, 0x: 02 2/256*T of ddr_ck, ……0x:80, 128/256*T of ddr_ck, (90shift) ……..0x:FF, 255/256*T of ddr_ck

	*db0_bt_wdq
	*[19:16]: write DQS to DQ coarse phase delay manual mode setting of data module 0.
	*0x: 1, shift 1/2*T ddr_ck, 0x: 2, shift 1*T ddr_ck, 0x:3 shift 3/2*T ddr_ck…..,
	*this coarse delay is to cover the write leveling dqs delay, and dqs2dq spec in lp4
	*db1_bt_wdq
	*[23:20]: write DQS to DQ coarse phase delay manual mode setting of data module 1.
	*0x: 1, shift 1/2*T ddr_ck, 0x: 2, shift 1*T ddr_ck, 0x:3 shift 3/2*T ddr_ck…..,
	*this coarse delay is to cover the write leveling dqs delay, and dqs2dq spec in lp4
	*/
	dqs_to_dq = reg_bits_get(addr, 0, 24);
	db0_dqs = (((((dqs_to_dq>>16)&0xf)<<8)|(dqs_to_dq & 0xff)) - 0x80);
	db1_dqs = (((((dqs_to_dq>>20)&0xf)<<8)|((dqs_to_dq>>8) & 0xff)) - 0x80);
	db0_dqs = (db0_dqs > 0xff)?0xff:db0_dqs;
	db1_dqs = (db1_dqs > 0xff)?0xff:db1_dqs;
	return ((db1_dqs << 8)|db0_dqs);
}
void ddrc_phy_tdqs2dq_setting(uint32 phy_base)
{
//	if (ddr_chip_cur.chip_type == DRAM_LPDDR4)
	{
		uint32 dqs_to_dq;
		//233 DQS to DQ delay setting depend on 933 write dq value
		dqs_to_dq = dqs_to_dq_get(phy_base + 0x278);
		reg_bits_set(phy_base + 0x98, 0, 8,(dqs_to_dq & 0xff)>>1);
		reg_bits_set(phy_base + 0x98, 8, 8,(((dqs_to_dq>>8) & 0xff))>>1);

		//311 DQS to DQ delay setting depend on 622 write dq value
		dqs_to_dq = dqs_to_dq_get(phy_base + 0x1d8);
		reg_bits_set(phy_base + 0xe8, 0, 8,((dqs_to_dq & 0xff)));
		reg_bits_set(phy_base + 0xe8, 8, 8,((dqs_to_dq >> 8) & 0xff));

		//400 DQS to DQ delay setting depend on 800 write dq value
		dqs_to_dq = dqs_to_dq_get(phy_base + 0x228);
		reg_bits_set(phy_base + 0x138, 0, 8,((dqs_to_dq & 0xff)));
		reg_bits_set(phy_base + 0x138, 8, 8,((dqs_to_dq >> 8) & 0xff));
	}

}

void ddrc_phy_init_post_seq(void)
{
	/*step 1) set rpull for normal mode*/
//	if ((ddr_chip_cur.chip_type == DRAM_LPDDR4) || (REG32(REG_AON_APB_AON_VER_ID) > 0))
	{
		ddrc_phy_post_setting_rpull(DMC_GUCPHY0_BASE);
		ddrc_phy_post_setting_rpull(DMC_GUCPHY1_BASE);
	}
}

void one_freq_point_init_flow(void)
{
	char s_tmp[11] = {0};
	uint32 freq_sel = phy_train.freq_sel;
	uint32 this_freq = find_ddr_freq(freq_sel);
//	ddrc_print_debug(__FILE__  );
//	ddrc_print_debug(__FUNCTION__  );
//	ddrc_print_debug(itoa_dec(__LINE__));
//	ddrc_print_debug(" \r\n");
	ddrc_print_debug("initial F");
	ddrc_print_debug(itoa_simple(freq_sel, s_tmp, 10));
	ddrc_print_debug(" ddr clock ");
	ddrc_print_debug(itoa_simple(this_freq, s_tmp, 10));
	ddrc_print_debug("Mhz\r\n");
	if(PUB_CLK_1866M == this_freq)
	{
		regulator_set_voltage("vddcore", 900);	//mv
		dmc_sprd_delay(7);
	}
	/*pre-setting gucphy*/
	/*perbit training only execulte one times*/
	/*step 1) phy soft_rst*/
	ddrc_phy_reset(1);

	/*step 2) setting dmc clock(gating clock and toggle adj_valid and phy_soft_rst_n=0)*/
	change_clk_freq_seq(freq_sel);
//	change_clk_freq_seq(freq_sel);
	if(min_freq == freq_sel)
	{
		/*step 4) set iopv before initial start*/
		ddrc_phy_iopvt_pre_seq();
	}

	/*step 3) soc rst phy*/
	ddrc_phy_reset(0);

	/*step 5) dll lock(dfi_init_start and dcc_rstn)*/
	master_dll_lock_seq();

	if(min_freq == freq_sel)
	{
		/*step 6) iopvt zq calibration just need one time*/
		ddrc_phy_iopvt_cal_seq();
	}

	//step 1) exit selfrefresh status
	dmc_exit_self_refresh(1);

	//step 2) dram init and send mrws command
	dram_powerup_seq(find_ddr_freq(freq_sel));

	training_set_pre(DMC_GUCPHY0_BASE, freq_sel);
	training_set_pre(DMC_GUCPHY1_BASE, freq_sel);

	phy_train.rank = 0;
	ddrc_phy_init_flow(this_freq, freq_sel, phy_train.rank);//rank 0
//	phy_train.rank = 1;
//	ddrc_phy_init_flow(this_freq, freq_sel, phy_train.rank);//rank 0

	dfs_mrw_update(freq_sel);
	ddrc_print_debug("\r\n");
}



void ddrc_phy_init_seq(uint32 ddr_clk)
{
	uint32 i;
	max_freq = find_freq_num(ddr_clk);
	#ifdef SINGLE_FREQ_INIT
	i = max_freq;
	min_freq = max_freq;
	#else
	i = MIN_FREQ_SEL;
	min_freq = MIN_FREQ_SEL;
	#endif
	if(!(freq_sel_mask & (0x1 << min_freq)))
	{
		ddrc_print_err("min_freq masked\r\n");
		while_loop();
	}

	for (; i <= max_freq; i++)
	{
		if(freq_sel_mask & (0x1 << i))
		{
			phy_train.freq_sel = i;
			one_freq_point_init_flow();
			if(phy_train.freq_sel == min_freq)		//auto detect mr8 at max freq
			{
				//auto detect need run at a frequency,which donot need training.
				#ifdef DDR_AUTO_DETECT
				dmc_exit_self_refresh(8);
				lpddr_size_auto_detect();
				ctrl_dram_setting();
				dmc_entry_self_refresh(8);
				#endif
			}
		}
	}
//	if (ddr_clk >= PUB_CLK_933M)
//	{
//		ddrc_phy_tdqs2dq_setting(DMC_GUCPHY0_BASE);
//		ddrc_phy_tdqs2dq_setting(DMC_GUCPHY1_BASE);
//	}
}




