#include <sci_types.h>
#include <asm/arch/clk_para_config.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_chipram_env.h>
#include <asm/arch/pinmap.h>
#include <gpio_drvapi.h>

#include "ddrc_r1p0.h"
#include "ddrc_r1p0_phy.h"
#include "ddrc_r1p0_common.h"
#include "ddr_test.h"
extern u32 FREQ_TRAINING_ENABLE[8];
#ifdef DDR_SCAN_ENABLE
extern u32 ddr_scan_repeat_call_flag;
#endif
static DRAM_JEDEC_INFO jedec_info_cs0 = {0,			/*cs index*/
					CFG_CS0_BANK_NUM,	/*bank number*/
					CFG_CS0_ROW_NUM,	/*row number*/
					CFG_CS0_COLUMN_NUM,	/*column number*/
					CFG_CS0_DQ_DW,		/*data width*/
					CFG_CS0_SIZE		/*cs0 size*/
};

static DRAM_JEDEC_INFO jedec_info_cs1 = {1,			/*cs index*/
					 CFG_CS1_BANK_NUM,	/*bank number*/
					 CFG_CS1_ROW_NUM,	/*row number*/
					 CFG_CS1_COLUMN_NUM,	/*column number*/
					 CFG_CS1_DQ_DW,		/*data width*/
					 CFG_CS1_SIZE		/*cs1 size*/
};

DRAM_CHIP_INFO ddr_chip_cur = {
	CFG_DRAM_TYPE,
	0,//manufacturer id
	2,
	&jedec_info_cs0,
	&jedec_info_cs1,
	0,
	CFG_IO_MODE,
        CFG_PINMUX_CASE
};

dfs_freq_table dfs_table[8]={{0,160},{1,233},{2,311},{3,400},{4,533},{5,622},{6,800},{7,933}};

static PORT_PARA port_para[18] = {
	/*timeout_pri_wr_chx timeout_thr_wr_chx timeout_thr_rd_chx timeout_pri_rd_chx bw_thr_chx bw_holdoff_en_chx*/
	/*port0*/
	{0x0E, 0x80, 0x80, 0x0E, 0x00, 0x00},
	/*port1*/
	{0x0A, 0x00, 0x00, 0x0A, 0x00, 0x00},
	/*port2*/
	{0x0C, 0x00, 0x41, 0x0E, 0x00, 0x00},
	/*port3*/
	{0x0A, 0x80, 0x80, 0x0A, 0x00, 0x00},
	/*port4*/
	{0x0e, 0x80, 0x80, 0x0E, 0x00, 0x00},
	/*port5*/
	{0x0e, 0x00, 0x00, 0x0E, 0x00, 0x00},
	/*port6*/
	{0x0E, 0x40, 0x40, 0x0E, 0x00, 0x00},
	/*port7*/
	{0x0A, 0x80, 0x80, 0x0A, 0x00, 0x00}
};

uint32 find_freq_num(uint32 clk_freq)
{
	uint32 i=0;
	for(i=0; i<8; i++)
	{
		if(clk_freq == dfs_table[i].freq)
		{
			return dfs_table[i].point_num;
		}
	}
	return 8;
}

uint32 find_ddr_freq(uint32 num)
{
	uint32 i=0;
	for(i=0; i<8; i++)
	{
		if(num == dfs_table[i].point_num)
		{
			return dfs_table[i].freq;
		}
	}
	return 8;
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

int sdram_chip_whole_size(uint64 *size)
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

int sdram_cs_whole_size(int cs, uint64*size)
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
void dmc_ddr_mode_register_store(void)
{
#if 0
	u32 i;
	u32 type;
	u32 cs0[4]={0};
	u32 cs1[4]={0};
	//save mr5/mr6/mr7/mr8
	for (i=5; i<=8; i++)
	{
		dmc_mrr(0, i, &cs0[i-5], 10000);
		dmc_mrr(1, i, &cs1[i-5], 10000);
	}
	//bit[31:24]mr8 | bit[23:16]mr7 | bit[15:8]mr6 | bit[7:0]mr5
	REG32(DMC_DTMG12_F0)=(((cs0[3]&0xff)<<24)|((cs0[2]&0xff)<<16)|((cs0[1]&0xff)<<8)|(cs0[0]&0xff));
	REG32(DMC_DTMG13_F0)=(((cs1[3]&0xff)<<24)|((cs1[2]&0xff)<<16)|((cs1[1]&0xff)<<8)|(cs1[0]&0xff));
	//bit[7:4] save ddr cs number, bit[3:0] save ddr type
	if (ddr_chip_cur.chip_type == DRAM_LPDDR3)
		type = 0x3;
	else if ((ddr_chip_cur.chip_type == DRAM_LPDDR4) && (ddr_chip_cur.io_mode == IO_LP4))
		type = 0x4;
	else if ((ddr_chip_cur.chip_type == DRAM_LPDDR4) && (ddr_chip_cur.io_mode == IO_LP4X))
		type = 0x5;
	else
	{
		type = 0x3;
	}
	REG32(DMC_DTMG14_F0) = ((ddr_chip_cur.cs_num << 4) | type);
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

static void dmc_update_param_for_uboot(void)
{
	chipram_env_t * p_env = CHIPRAM_ENV_ADDR;
	p_env->cs_number = ddr_chip_cur.cs_num;
	p_env->cs0_size = jedec_info_cs0.cs_size;
	p_env->cs1_size = jedec_info_cs1.cs_size;
        u32 val;
	if (ddr_chip_cur.cs_num == 1)
	{
		p_env->cs1_size = jedec_info_cs1.cs_size = 0;
		p_env->dram_size = p_env->cs0_size;
	}
	else if (ddr_chip_cur.cs_num == 2)
		p_env->dram_size = (u64)p_env->cs0_size + (u64)p_env->cs1_size;

	if (ddr_chip_cur.cs_num == 2)
	{
#if defined(CONFIG_CHIPRAM_DDR_CUSTOMIZE)
		dmc_ddr_size_limit(p_env, CONFIG_CHIPRAM_DDR_CUSTOMIZE);
#else
		p_env->cs1_size -= BIST_RESERVE_SIZE;
#endif
	}
	else if (ddr_chip_cur.cs_num == 1)
	{
#if defined(CONFIG_CHIPRAM_DDR_CUSTOMIZE)
		dmc_ddr_size_limit(p_env, CONFIG_CHIPRAM_DDR_CUSTOMIZE);
#else
		p_env->cs0_size -= BIST_RESERVE_SIZE;
#endif
	}
	/*Save physical ddr size int dmc reg for kernel driver*/
	REG32(DMC_DTMG17_F0) = p_env->dram_size & 0xFFFFFFFF;
	REG32(DMC_DTMG18_F0) = p_env->dram_size >> 32;
}

static void dmc_ddr_debug_mode(void)
{
#if defined(DDR_MODE)
	u32 ddr_mode = mcu_clk_para.ddr_debug_mode.value;
#else
	u32 ddr_mode = 0x0;
#endif
	u32 regval;
	/* ddr_mode
	 * bit[0] 1'b1 dfs disable; 1'b0 dfs_enable
	 * bit[1] 1'b1 retention disable; 1'b0 retention enable
	 *
	*/
	if ((ddr_mode & 0x1))
	{
		regval = REG32(DMC_DTMG16_F0);
		regval = u32_bits_set(regval, 0, 8,0x5A);
		REG32(DMC_DTMG16_F0) = regval;
	}

	if ((ddr_mode & 0x2))
	{
		regval = REG32(DMC_DTMG16_F0);
		regval = u32_bits_set(regval, 8, 8,0x5A);
		REG32(DMC_DTMG16_F0) = regval;
	}
}
#if defined(CONFIG_SOC_SHARKL3)
void dmc_exit_self_refresh(u32 repeat)
{
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 regval, i;
	/*step 6) exit selfrefresh and initial DRAM if not send current frequency MRWs*/
	/*ch0_rfdmem_cmd_chip_sleep*/
	regval = (pdmc->dmc_dcfg9 >> 24) & 0x3;
	if (regval == 0x3)
	{
		pdmc->dmc_dcfg1 = 0x80800000;//dsoft_resume
		while(((pdmc->dmc_dcfg1 >> 19) & 0x1ff) != 0);
	}

	pdmc->dmc_dcfg1 = 0x80100000;//dsoft_pre-all
	while(((pdmc->dmc_dcfg1 >> 19) & 0x1ff) != 0);

	for (i = 0; i < repeat; i++)
	{
		pdmc->dmc_dcfg1 = 0x80200000;//dsoft_auto_ref
		while(((pdmc->dmc_dcfg1 >> 19) & 0x1ff) != 0);
	}
}

void dmc_entry_self_refresh(u32 repeat)
{
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 regval, i;
	/*step 6) exit selfrefresh and initial DRAM if not send current frequency MRWs*/
	/*ch0_rfdmem_cmd_chip_sleep*/
	pdmc->dmc_dcfg1 = 0x80400000;//dsoft_resume
	while(((pdmc->dmc_dcfg1 >> 19) & 0x1ff) != 0);
}

static void pub_soft_reset(void)
{
	REG32(REG_PMU_APB_CP_SOFT_RST) |= 1<<6;
	dmc_sprd_delay(100);
	REG32(REG_PMU_APB_CP_SOFT_RST) &= ~(1<<6);
}
static void ddr_umctrl_soft_reset(void)
{
	REG32(REG_PMU_APB_DDR_PHY_RET_CFG) |= 1<<16;
	dmc_sprd_delay(100);
	REG32(REG_PMU_APB_DDR_PHY_RET_CFG) &= ~(1<<16);
}

static void ddrc_axi_lowpower_setting(void)
{
	/*bit[16] 1'b1 ddr_chn0_axi_lp_en*/
	/*bit[17] 1'b1 ddr_chn1_axi_lp_en*/
	/*bit[18] 1'b1 ddr_chn2_axi_lp_en*/
	/*bit[19] 1'b0 ddr_chn3_axi_lp_en*/
	/*bit[20] 1'b1 ddr_chn4_axi_lp_en*/
	/*bit[21] 1'b1 ddr_chn5_axi_lp_en*/
	/*bit[22] 1'b1 ddr_chn6_axi_lp_en*/
	/*bit[23] 1'b1 ddr_chn7_axi_lp_en*/
	reg_bits_set(REG_PUB_TOP_AHB_DDR_CHN_SLEEP_CTRL0, 16, 8, 0xF7);//ddr channelx axi lower power en

	/*pub_top_pub_top_AHB_RF_DDR_CHN_SLEEP_CTRL*/
	/*bit[0] 1'b0 ddr_chn0_axi_top_sel*/
	/*bit[1] 1'b0 ddr_chn1_axi_top_sel*/
	/*bit[2] 1'b0 ddr_chn2_axi_top_sel*/
	/*bit[3] 1'b0 ddr_chn3_axi_top_sel*/
	/*bit[4] 1'b0 ddr_chn4_axi_top_sel*/
	/*bit[5] 1'b0 ddr_chn5_axi_top_sel*/
	/*bit[6] 1'b0 ddr_chn6_axi_top_sel*/
	/*bit[7] 1'b0 ddr_chn7_axi_top_sel*/
	reg_bits_set(REG_PUB_TOP_AHB_DDR_CHN_SLEEP_CTRL1, 0, 8, 0x0);//ddr channelx axi top sel

	/*PUB_TOP_AHB_WRAP_RF_FENCING_CTRL*/
	reg_bits_set(REG_PUB_AHB_WRAP_FENCING_CTRL, 30, 1, 0x1);//ddr fencing enable
	reg_bits_set(REG_PUB_AHB_WRAP_FENCING_CTRL, 0, 30, 0x26E);//ddr fencing channel idle cnt(1us)
	/*bit[13] enable to reset sleep counter when ddr channel back to active*/
	reg_bits_set(REG_PMU_APB_DDR_SLP_CTRL_CFG0, 13, 1, 0x1);
}
static void ddrc_apb_lowpower_setting(void)
{
	/*AON_CLK_LP_RF_CLK_SW_MODE_SEL*/
	reg_bits_set(REG_AON_CLK_LP_CLK_SW_MODE_SEL, 4, 1, 0x0);//clk emc ref mode sel
	reg_bits_set(REG_AON_CLK_LP_BUSCLK_MODE_SEL, 4, 1, 0x1);//clk_aonmatrix2pub_mode_sel
	/*bit[6] 1'b1 pub_cfg_auto_en*/
	/*bit[7] 1'b0 pub_cfg_slow_en*/
	reg_bits_set(REG_AON_CLK_LP_CLK_AUTO_GATE_EN_CTRL3, 6, 2, 0x1);
	reg_bits_set(REG_PMU_APB_PMU_DUMMY_REG1, 14, 2, 0x1);//debug
}
static void ddrc_pub_lowpoer_setting(void)
{
	/*enable pubsys clock auto gating fuctions*/
	/*PUB_TOP_PUB_TOP_AHB_RG_DMC_DDR_CTRL_CLK_CTRLi 0x30200000*/
	/*bit[31] 1'b1 pub_clk_dfs_sleep_auto_gate_en*/
	/*bit[30] 1'b1 clk_apb_auto_gate_en*/
	/*bit[29] 1'b1 clk_emc_ref_auto_gate_en*/
	/*bit[28] 1'b1 pub_clk_dfs_auto_gate_en*/
	/*bit[27] 1'b1 dmc_dfi_mon_auto_gate_en*/
	/*bit[26] 1'b1 dmc_sref_auto_gate_en*/
	/*bit[25] 1'b1 ddr_phy_auto_gate_en*/
	/*bit[24] 1'b1 ddr_umctrl_auto_gate_en*/
	/*bit[22] 1'b0 pub_clk_emc_ref_en*/
	/*bit[20] 1'b0 pub_clk_apb_en*/
	/*bit[11] 1'b0 pub_clk_dmc_x1_eb*/
	/*bit[23] 1'b1 pub_top_mon_en*/
	/*bit[15] 1'b1 pub_clk_dfs_en*/
	reg_bits_set(REG_PUB_TOP_AHB_DMC_DDR_CLK_CTRL, 24, 8, 0xFF);
	reg_bits_set(REG_PUB_TOP_AHB_DMC_DDR_CLK_CTRL, 20, 1, 0x0);
	reg_bits_set(REG_PUB_TOP_AHB_DMC_DDR_CLK_CTRL, 22, 1, 0x0);
	reg_bits_set(REG_PUB_TOP_AHB_DMC_DDR_CLK_CTRL, 11, 1, 0x0);
	/*bit[23] bit[15] set 1 for debug,128M clock always on*/
	reg_bits_set(REG_PUB_TOP_AHB_DMC_DDR_CLK_CTRL, 23, 1, 0x0);
	reg_bits_set(REG_PUB_TOP_AHB_DMC_DDR_CLK_CTRL, 15, 1, 0x0);

	/*enable qos controller clock auto gating functions 0x30210008*/
	/*bit[0] 1'b1 qosc_port_clkc_auto_gate_en*/
	/*but[1] 1'b1 qosc_bw_limit_auto_gate_en*/
	/*bit[8] 1'b0 qosc_cfg_clk_en*/
	/*bit[9] 1'b1 qosc_cfg_clk_auto_gate_en*/
	reg_bits_set(REG_PUB_QOSC_AHB_QOSC_CLK_CTRL, 0, 2, 0x3);
	reg_bits_set(REG_PUB_QOSC_AHB_QOSC_CLK_CTRL, 8, 2, 0x2);

	/*PUB_TOP_PUB_QOSC_AHB_RF_QOSC_M1_CLK_CTRL 0x30210408*/
	/*bit[0] 1'b1 qosc_port_clk_auto_gate_en (M1)*/
	/*bit[1] 1'b1 qosc_bw_limit_auto_gate_en (M1)*/
	/*bit[8] 1'b0 qosc_cfg_clk_en(M1)*/
	reg_bits_set(REG_PUB_QOSC_AHB_M1_QOSC_CLK_CTRL, 0, 2, 0x3);
	reg_bits_set(REG_PUB_QOSC_AHB_M1_QOSC_CLK_CTRL, 8, 1, 0x0);

	/*PUB_TOP_PUB_QOSC_AHB_RF_QOSC_M2_CLK_CTRL 0x30210608*/
	/*bit[0] 1'b1 qosc_port_clk_auto_gate_en (M2)*/
	/*bit[1] 1'b1 qosc_bw_limit_auto_gate_en (M2)*/
	/*bit[8] 1'b0 qosc_cfg_clk_en(M2)*/
	reg_bits_set(REG_PUB_QOSC_AHB_M2_QOSC_CLK_CTRL, 0, 2, 0x3);
	reg_bits_set(REG_PUB_QOSC_AHB_M2_QOSC_CLK_CTRL, 8, 1, 0x0);

	/*REG_PUB_TOP_AHB_DMC_CLK_INIT_CFG 0x30200108*/
	/*bit[8] dmc sleep_force_finish_mode*/
	reg_bits_set(REG_PUB_TOP_AHB_DMC_CLK_INIT_CFG, 8, 1, 0x1);

	/*REG_PUB_TOP_AHB_HSEL_IDLE_CNT 0x30200088*/
	/*bit[7:0] hsel_idle_cnt*/
	reg_bits_set(REG_PUB_TOP_AHB_HSEL_IDLE_CNT, 0, 8, 0x10);

	/*disable bus ot detect clk*/
	/*REG_PUB_AHB_WRAP_PUB_PERI_CLK_EN*/
	/*bit[1] ot_clk_en OT mode clock enable*/
	reg_bits_set(REG_PUB_AHB_WRAP_PUB_PERI_CLK_EN, 1, 1, 0x0);

	/*for pll pd default*/
	/*0x30200108*/
	/*bit[4] deskew_pll_pd_default_sel*/
	/*bit[5] deskew_pll_pd_default_sw*/
	reg_bits_set(REG_PUB_TOP_AHB_DMC_CLK_INIT_CFG, 4, 2, 0x3);
	//reg_bits_set(0x30400284, 24, 1 ,0x0);
	//reg_bits_set(0x30410284, 24, 1 ,0x0);
}
static void ddrc_smart_light_setting(void)
{
	/*Step 1) enable smart light sleep*/
	REG32(REG_PMU_APB_DDR_SLP_CTRL_CFG0) |= BIT_PMU_APB_PUB_SYS_SMART_LSLP_ENA;
	/*Step 2) clear force sleep signal*/
	/*bit[21] PUB_SYS_FORCE_DEEP_SLEEP*/
	/*bit[29] PUB_SYS_FORCE_LIGHT_SLEEP*/
	reg_bits_set(REG_PMU_APB_SLEEP_CTRL, 21, 1, 0x0);
	reg_bits_set(REG_PMU_APB_SLEEP_CTRL, 29, 1, 0x0);

	/*Step 3) suto sleep enable*/
	reg_bits_set(REG_PMU_APB_PUB_SYS_AUTO_LIGHT_SLEEP_ENABLE, 0, 16, 0xFFFF);
}
void ddrc_lowpower_setting(void)
{
	ddrc_axi_lowpower_setting();
	ddrc_apb_lowpower_setting();
	ddrc_pub_lowpoer_setting();
	//ddrc_smart_light_setting();
}
#endif
void wdt_rst_keep_sre(void)
{
   if((0x5E486947 == REG32(CHIP_RESET_CONTROL_STATUS))&&(REG32(CHIP_RESET_CONTROL_STATUS)&0x3))
   {
       REG32(CHIP_RESET_CONTROL_STATUS) = (0x1979<<16)|0x0;
   }
   else
   {
       REG32(CHIP_RESET_CONTROL_STATUS) = (0x1979<<16)|0x0;
       REG32(CHIP_RESET_CONTROL_KEY) = (0x5E486947);
       REG32(CHIP_RESET_CONTROL_ENABLE) = (0x6A39<<16)|(0x3<<12)|0x3;
   }
}
static void sdram_init_fpga(void)
{
}

void dmc_port_qos_cfg0(volatile u32 *addr,u32 timeout_pri_wr_ch, u32 timeout_thr_wr_ch, u32 timeout_thr_rd_ch)
{
	u32 regval;
	regval = *addr;
	regval = u32_bits_set(regval, 0, 4, timeout_pri_wr_ch);
	regval = u32_bits_set(regval, 16, 8, timeout_thr_wr_ch);
	regval = u32_bits_set(regval, 24, 8, timeout_thr_rd_ch);
	*addr = regval;
}

void dmc_port_qos_cfg1(volatile u32 *addr,u32 bandwidth_pri_rd_ch, u32 bandwidth_thr_ch, u32 bandwidth_holdoff_en_ch)
{
	u32 regval;
	regval = *addr;
	regval = u32_bits_set(regval, 0, 4, bandwidth_pri_rd_ch);
	regval = u32_bits_set(regval, 16, 10, bandwidth_thr_ch);
	regval = u32_bits_set(regval, 31, 1, bandwidth_holdoff_en_ch);
	*addr = regval;
}

void dmc_ctrl_qos_init(void)
{
	int i;
	/*port 0 DCAM/ISP*/
	/*port 1 GPU/GSP*/
	/*port 2 DISPLAY*/
	/*port 3 CA7*/
	/*port 4 PUBCP*/
	/*port 5 vSP/JPG/CPP*/
	/*port 6 WLTE/DSP*/
	/*port 7 AP/AON*/
	for(i = 0; i < 8; i++)
	{
		dmc_port_qos_cfg0((volatile u32 *)(DMC_REG_ADDR_BASE_PHY + 0x20 + i*8),
				  port_para[i].timeout_pri_wr_chx,
				  port_para[i].timeout_thr_wr_chx,
				  port_para[i].timeout_thr_rd_chx);
		dmc_port_qos_cfg1((volatile u32 *)(DMC_REG_ADDR_BASE_PHY + 0x24 + i*8),
				  port_para[i].timeout_pri_rd_chx,
				  port_para[i].bw_thr_chx,
				  port_para[i].bw_holdoff_en_chx);
	}
	/*dram band width scheduling counter*/
	reg_bits_set(DMC_REG_ADDR_BASE_PHY, 27, 1, 0);
	reg_bits_set(DMC_REG_ADDR_BASE_PHY, 16, 11, 0x190);

	//enable dmc prefetch function for M0~M9:[3]=CPU,[5]=WTLCP
	reg_bits_set(RF_PORT_PREFETCH_EN, 0, 8, 0x28);
	//bit[8] rf_hi_urgent_en bit[9] rf_urgent_qos_en
	reg_bits_set(RF_HI_URGENT_EN,8,2,3);

	/*qos Mapping*/
	REG32(DMC_MAP)=0xC0C03030;
}
void ddrc_qos_setting(void)
{
	/*Step1 ctrl qos setting*/
	dmc_ctrl_qos_init();

	/*Step2 PUBSYS QOS setting*/
        //PUB AHB WRAP QOS Setting
	//bit[21:20] wifi fifo urgency ctrl en ; set WCN port urgent when wifi
	//issue urgent signal,2'b01= high urgent ,2'b10=ultra high urgent
	//bit[23:22] wifi dfs urgency dtrl en; set WCN prot urgent when wifi
	//wifi_dfs_req==1; 2'b01=high urgent , 2'b10=ultra high urget
	reg_bits_set(REG_PUB_AHB_WRAP_WIFI_DFS_CTRL, 20, 4, 0x1);

	//PUB AHB qosc Setting
	/*Qos ctrl Basic Setting*/
	REG32(REG_PUB_QOSC_AHB_QOSC_CLK_CTRL)   =0x00000213;//QOSC_CLK_CTRL
	REG32(REG_PUB_QOSC_AHB_M1_QOSC_CLK_CTRL)=0x00000033;//M1_QOSC_CLK_CTRL
	REG32(REG_PUB_QOSC_AHB_M2_QOSC_CLK_CTRL)=0x00000073;//M2_QOSC_CLK_CTRL
	REG32(REG_PUB_QOSC_AHB_QOSC_CFG)        =0x17330075;//QOSC_CFG
	REG32(REG_PUB_QOSC_AHB_M1_QOSC_CFG)     =0x10330000;//M1_QOSC_CFG
	REG32(REG_PUB_QOSC_AHB_M2_QOSC_CFG)     =0x10330000;//M2_QOSC_CFG

	/*Qos ctrl Function enable*/
	REG32(REG_PUB_QOSC_AHB_QOSC_PORT_ENABLE)   =0x000000ff;//QOSC_PORT_ENABLE
	REG32(REG_PUB_QOSC_AHB_QOSC_SV_COUNTER_EN) =0x00000000;//QOSC_SV_COUNTER_EN
	REG32(REG_PUB_QOSC_AHB_QOSC_AXURGENT_EN)   =0x00640061;//QOSC_AXURGENT_EN
	REG32(REG_PUB_QOSC_AHB_QOSC_LATMON_AXURGENT_EN) = 0x00000000;//QOSC_LATMON_AXURGENT_EN

	REG32(REG_PUB_QOSC_AHB_M1_QOSC_PORT_ENABLE)=0x00000003;//M1_QOSC_PORT_ENABLE
	REG32(REG_PUB_QOSC_AHB_M1_QOSC_SV_COUNTER_EN) =0x00000000;//M1_QOSC_SV_COUNTER_EN
	REG32(REG_PUB_QOSC_AHB_M1_QOSC_AXURGENT_EN)=0x00000000;//M1_QOSC_AXURGENT_EN
	REG32(REG_PUB_QOSC_AHB_M1_QOSC_LATMON_AXURGENT_EN)=0x00000000;//M1_QOSC_LATMON_AXURGENT_EN

	REG32(REG_PUB_QOSC_AHB_M2_QOSC_PORT_ENABLE)=0x00000007;//M2_QOSC_PORT_ENABLE
	REG32(REG_PUB_QOSC_AHB_M2_QOSC_SV_COUNTER_EN)=0x00000000;//M2_QOSC_SV_COUNTER_EN
	REG32(REG_PUB_QOSC_AHB_M2_QOSC_AXURGENT_EN)=0x00020002;//M2_QOSC_AXURGENT_EN
	REG32(REG_PUB_QOSC_AHB_M2_QOSC_LATMON_AXURGENT_EN)=0x00000000;//M2_QOSC_LATMON_AXURGENT_EN

	/*Qos Value setting*/
	REG32(REG_PUB_QOSC_AHB_QOSC_QOS_VALUE_CH0)=0x6E6C6600;//QOSC_QOS_VALUE_CH0
	REG32(REG_PUB_QOSC_AHB_QOSC_QOS_VALUE_CH1)=0x66666600;//QOSC_QOS_VALUE_CH1
	REG32(REG_PUB_QOSC_AHB_QOSC_QOS_VALUE_CH2)=0xE6C6A600;//QOSC_QOS_VALUE_CH2
	REG32(REG_PUB_QOSC_AHB_QOSC_QOS_VALUE_CH3)=0x66666600;//QOSC_QOS_VALUE_CH3
	REG32(REG_PUB_QOSC_AHB_QOSC_QOS_VALUE_CH4)=0x44444400;//QOSC_QOS_VALUE_CH4
	REG32(REG_PUB_QOSC_AHB_QOSC_QOS_VALUE_CH5)=0xEEEEAA00;//QOSC_QOS_VALUE_CH5
	REG32(REG_PUB_QOSC_AHB_QOSC_QOS_VALUE_CH6)=0xCCCCC400;//QOSC_QOS_VALUE_CH6
	REG32(REG_PUB_QOSC_AHB_QOSC_QOS_VALUE_CH7)=0x44444400;//QOSC_QOS_VALUE_CH7

	REG32(REG_PUB_QOSC_AHB_M1_QOSC_QOS_VALUE_CH0)=0x44444400;//M1_QOSC_QOS_VALUE_CH0
	REG32(REG_PUB_QOSC_AHB_M1_QOSC_QOS_VALUE_CH1)=0x99999900;//M1_QOSC_QOS_VALUE_CH1
	REG32(REG_PUB_QOSC_AHB_M2_QOSC_QOS_VALUE_CH0)=0x44444400;//M2_QOSC_QOS_VALUE_CH0
	REG32(REG_PUB_QOSC_AHB_M2_QOSC_QOS_VALUE_CH1)=0xcccc9900;//M2_QOSC_QOS_VALUE_CH1
	REG32(REG_PUB_QOSC_AHB_M2_QOSC_QOS_VALUE_CH2)=0x44444400;//M2_QOSC_QOS_VALUE_CH2

	/*Step3 Enable QoS setting*/
	REG32(REG_PUB_QOSC_AHB_QOS_CTRL_EB)=0x00000001;//QOS_CTR_EB
	REG32(REG_PUB_QOSC_AHB_M1_QOS_CTRL_EB)=0x00000001;//M1_QOS_CTRL_EB
	REG32(REG_PUB_QOSC_AHB_M2_QOS_CTRL_EB)=0x00000001;//M2_QOS_CTRL_EB
}
static pinmap_t vddq_en_pinmap[]={
	{REG_PIN_GPIO141,		BITS_PIN_AF(3)},
};
static void  vddq_en_pin_init(void)
{
	int i;

	for (i = 0; i < sizeof(vddq_en_pinmap)/sizeof(vddq_en_pinmap[0]); i++)
		REG32(SPRD_PIN_PHYS + vddq_en_pinmap[i].reg) = vddq_en_pinmap[i].val;
}

void lpddr4x_vddq_en(void)
{
	vddq_en_pin_init();
	sprd_gpio_request(LP4X_VDDQ_CTRL_GPIO_N);
	sprd_gpio_direction_output(LP4X_VDDQ_CTRL_GPIO_N, V_HIGH);
}
void ddr_power_cfg(void)
{
    if(DRAM_LPDDR3 == ddr_chip_cur.chip_type)
    {
        regulator_set_voltage("ldomem",1200);
    }
    else
    {
        regulator_set_voltage("ldomem",1100);
        lpddr4x_vddq_en();
    }
}
int sdram_init(void)
{
#if defined(CONFIG_CLK_PARA)
	u32 ddr_clk = (mcu_clk_para.ddr_freq.value)/1000000;
#else
	u32 ddr_clk = DDR_CLK;
#endif
	unsigned int regval;
#if defined(CONFIG_FPGA) || defined(CONFIG_SOC_WHALEK)
	sdram_init_fpga();
#else
#ifndef DDR_SCAN_ENABLE
	dmc_print_str("ddr init start\n");
#endif
#if defined(GPIO_DETECT_DRAM_TYPE)
        ddr_type_detect();
#endif
        ddr_power_cfg();
        wdt_rst_keep_sre();
	if (find_freq_num(ddr_clk) > 7)
	{
		dmc_print_str("error: invalid ddr clock\n");
		while(1);
	}
	ddrc_phy_vref_setting();
	/*enable vref hc mode*/
	reg_bits_set(REG_PMU_APB_DDR_SLEEP_CTRL, 22, 1, 0x1);

	/*step 1). pub soft rst*/
	pub_soft_reset();

	/*step 1). ddr phy ret en clear sw*/
	reg_bits_set(REG_PMU_APB_DDR_OP_MODE_CFG, 30, 1, 1);

	/*step 1). release dmc ctrl rst*/
	ddr_umctrl_soft_reset();

	/*step 2). ddrc ctrl init pre setting*/
	ctrl_pre_set_seq(dfs_table);

	/*step 3). ddrc phy init pre setting*/
	ddrc_phy_pre_set_seq();

	/*step 4). initial frequency point*/
	ddrc_phy_init_seq();

	/*step 5). ddrc phy setting after phy initial*/
	ddrc_phy_post_set_seq();

	/*step 6). exit selfrefresh and initial DRAM if not send current frequency MRWs*/
	/*ch0_rfdmem_cmd_chip_sleep*/
	dmc_exit_self_refresh(8);

	/*step 7). ddrc powerup init setting*/
//#ifndef DDR_SCAN_ENABLE
//	/*this setting for one freq boot*/
//#if !defined(GUCPHY_TRAINING_MODE) || !defined(CONFIG_NAND_SPL)
//	dram_powerup_seq(ddr_clk);
//#ifdef DDR_AUTO_DETECT
//	lpddr_auto_detect();
//	ctrl_dram_setting();
//	phy_dram_setting();
//#endif
//#endif
//#endif

	/*step 8). phy or ctrl setting after dram inital*/
	ctrl_post_set_seq();

	/*step 9). dmc initial setting post*/
	ddrc_phy_init_post_seq();

	/*bist test*/
	dmc_ddr_test(0);

	/*disable vref hc mode*/
	reg_bits_set(REG_PMU_APB_DDR_SLEEP_CTRL, 22, 1, 0x0);
	dmc_ddr_mode_register_store();

	/*pub axi low power setting*/
	ddrc_lowpower_setting();

	REG32(REG_PMU_APB_PUB_ACC_RDY) = 0x1;

	/*transmit ddr size for uboot*/
	dmc_update_param_for_uboot();

	/*ddr debug setting*/
	dmc_ddr_debug_mode();

	/*pub qos setting*/
	ddrc_qos_setting();
#ifndef DDR_SCAN_ENABLE
	/*locked dmc ctrl registers*/
	REG32(0x3000009c) = 0xdeadbeef;
#endif
#endif
#ifndef DDR_SCAN_ENABLE
	dmc_print_str("ddr init pass\n");
#endif
#ifdef DFS_SUPPORT
        dfs_init();
#endif
#ifdef DDR_REINIT_TEST
	DMC_ReInit();
#endif
#ifdef POWER_TEST
        power_consumption_measure_entry();
#endif
#ifdef	DDR_SCAN_ENABLE
	if(ddr_scan_repeat_call_flag==0)
		ddr_scan_vdd_seq();
#endif

#ifdef CONFIG_FDL1
#ifdef MEM_TEST
	ddr_write_read_test();
#endif
#endif
	return 0;
}


