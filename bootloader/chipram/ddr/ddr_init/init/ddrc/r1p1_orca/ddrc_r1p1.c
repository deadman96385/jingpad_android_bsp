#include <sci_types.h>
#include <asm/arch-orca/clk_para_config.h>
#include <asm/arch-orca/sprd_reg.h>
#include <asm/arch-orca/sprd_chipram_env.h>
//#include <asm/arch-orca/chip_orca/pinmap.h>
#include <gpio_drvapi.h>
#include <adi.h>
#include "ddrc_r1p1.h"
#include "ddrc_r1p1_phy.h"
#include "ddrc_r1p1_common.h"

u16 dram_init_powerup_times = 0;

DRAM_JEDEC_INFO jedec_info_cs[DDR_RANK_NUM_MAX] = {
	{0,			/*cs index*/
	CFG_CS0_BANK_NUM,	/*bank number*/
	CFG_CS0_ROW_NUM,	/*row number*/
	CFG_CS0_COLUMN_NUM,	/*column number*/
	CFG_CS0_DQ_DW,		/*data width*/
	CFG_CS0_SIZE		/*cs0 size*/
	},
	{1,			/*cs index*/
	 CFG_CS1_BANK_NUM,	/*bank number*/
	 CFG_CS1_ROW_NUM,	/*row number*/
	 CFG_CS1_COLUMN_NUM,	/*column number*/
	 CFG_CS1_DQ_DW,		/*data width*/
	 CFG_CS1_SIZE		/*cs1 size*/
	 }
};

DRAM_CHIP_INFO ddr_chip_cur = {
	CFG_DRAM_TYPE,
	1,
	&(jedec_info_cs[0]),	//jedec_info_ca[0]
	&(jedec_info_cs[1]),	//jedec_info_ca[1]
	0,
	CFG_PINMUX_CASE
};

dfs_freq_table dfs_table[FREQ_POINT_NUM_MAX]={{0,256},{1,384},{2,667},{3,768},{4,1024},{5,1333},{6,1536},{7,1866}};

static PORT_PARA port_para[8] = {
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
	for(i=0; i<FREQ_POINT_NUM_MAX; i++)
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
	for(i=0; i<FREQ_POINT_NUM_MAX; i++)
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

uint32 sdram_chip_data_width(void)
{
	return jedec_info_cs[0].dw;
}

uint32 sdram_chip_cs_num(void)
{
	return ddr_chip_cur.cs_num;
}

uint32 sdram_chip_whole_size(uint64 *size)
{
	uint32 ret = TRUE;
	if (ddr_chip_cur.cs_num == 1)
	{
		*size = jedec_info_cs[0].cs_size;
	}
	else if (ddr_chip_cur.cs_num == 2)
	{
		*size = jedec_info_cs[0].cs_size + jedec_info_cs[1].cs_size;
	}
	else
	{
		ret = FALSE;
	}
	return ret;
}

uint32 sdram_cs_whole_size(int cs, uint64*size)
{
	uint32 ret = TRUE;
	if (0 == cs)
	{
		*size = jedec_info_cs[0].cs_size;
	}
	else if (1 == cs)
	{
		*size = jedec_info_cs[1].cs_size;
	}
	else
	{
		ret = FALSE;
	}
	return ret;
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
	p_env->cs0_size = jedec_info_cs[0].cs_size;
	p_env->cs1_size = jedec_info_cs[1].cs_size;
	uint32 val;
	if (ddr_chip_cur.cs_num == 1)
	{
		p_env->cs1_size = jedec_info_cs[1].cs_size = 0;
		p_env->dram_size = p_env->cs0_size;
	}
	else if (ddr_chip_cur.cs_num == 2)
	{
		p_env->dram_size = (u64)p_env->cs0_size + (u64)p_env->cs1_size;
	}

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
	REG32(AON_RAM_FOR_DDR + 0x0) = p_env->dram_size & 0xFFFFFFFF;
	REG32(AON_RAM_FOR_DDR + 0x4) = p_env->dram_size >> 32;
}

typedef struct
{
	uint32 magic;	//0x5a5a3c3c
	uint64 dram_size;
	u8 pub_smart_light_sleep_dis;
	u8 pub_light_sleep_dis;
	u8 pub_deep_sleep_dis;
	u8 ddr_dfs_dis;
}param_for_sp;


static void aon_ram_for_ddr_clear(void)
{
	memset(AON_RAM_FOR_DDR, 0, AON_RAM_FOR_DDR_SIZE);
}

static void dmc_update_param_for_sp(void)
{
	param_for_sp * p_param_for_sp = AON_RAM_FOR_DDR + 0x20;
	p_param_for_sp->magic = 0x5A5A3C3C;
	p_param_for_sp->dram_size = jedec_info_cs[0].cs_size + jedec_info_cs[1].cs_size;
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
	param_for_sp * p_param_for_sp = AON_RAM_FOR_DDR;
	if ((ddr_mode & 0x1))
	{
		/*  debug info dfs disable    */
		p_param_for_sp->ddr_dfs_dis = 1;
	}

	if ((ddr_mode & 0x2))
	{
		/*	debug info reinit disable	*/
		p_param_for_sp->pub_deep_sleep_dis = 1;
	}

	if ((ddr_mode & 0x4))
	{
		/*  debug info pub smart light disable    */
		p_param_for_sp->pub_smart_light_sleep_dis = 1;
	}

	if ((ddr_mode & 0x8))
	{
		/*  debug info pub light disable    */
		p_param_for_sp->pub_light_sleep_dis = 1;
	}

}

void dmc_ddr_mode_register_store(void)
{
	u32 i;
	u32 type;
	u32 cs0[4]={0};
	u32 cs1[4]={0};
	//save mr5/mr6/mr7/mr8
	dmc_exit_self_refresh(8);
	for (i=5; i<=8; i++)
	{
		dmc_mrr(0, i, &cs0[i-5], 10000);
		dmc_mrr(1, i, &cs1[i-5], 10000);
	}
	//bit[31:24]mr8 | bit[23:16]mr7 | bit[15:8]mr6 | bit[7:0]mr5
	REG32(AON_RAM_FOR_DDR + 0xc)=(((cs0[3]&0xff)<<24)|((cs0[2]&0xff)<<16)|\
				      ((cs0[1]&0xff)<<8)|(cs0[0]&0xff));
	REG32(AON_RAM_FOR_DDR + 0x10)=(((cs1[3]&0xff)<<24)|((cs1[2]&0xff)<<16)|\
				      ((cs1[1]&0xff)<<8)|(cs1[0]&0xff));
	//bit[7:4] save ddr cs number, bit[3:0] save ddr type
	if (ddr_chip_cur.chip_type == DRAM_LPDDR3)
		type = 0x3;
	else if (ddr_chip_cur.chip_type == DRAM_LPDDR4)
		type = 0x4;
	else if (ddr_chip_cur.chip_type == DRAM_LPDDR4X)
		type = 0x5;
	else
	{
		type = 0x3;
	}
	REG32(AON_RAM_FOR_DDR + 0x8) = ((ddr_chip_cur.cs_num << 4) | type);
}

static void pub_soft_reset(void)
{
	REG32(REG_PMU_APB_CP_SOFT_RST) |= 1<<6;
	dmc_sprd_delay(100);
	REG32(REG_PMU_APB_CP_SOFT_RST) &= ~(1<<6);
}
static void ddr_ctrl_soft_reset(void)
{
	REG32(REG_PMU_APB_DDR_PHY_RET_CFG) |= 1<<16;
}
static void ddr_ctrl_soft_reset_clear(void)
{
	REG32(REG_PMU_APB_DDR_PHY_RET_CFG) &= ~(1<<16);
}

static void ddrc_axi_lowpower_setting(void)
{
	/*bit[8] 1'b1 ddr_chn0_axi_lp_en*/
	/*bit[9] 1'b1 ddr_chn1_axi_lp_en*/
	/*bit[10] 1'b1 ddr_chn2_axi_lp_en*/
	/*bit[11] 1'b0 ddr_chn3_axi_lp_en*/
	/*bit[12] 1'b1 ddr_chn4_axi_lp_en*/
	/*bit[13] 1'b1 ddr_chn5_axi_lp_en*/
	/*bit[14] 1'b1 ddr_chn6_axi_lp_en*/
	/*bit[15] 1'b1 ddr_chn7_axi_lp_en*/
	//reg_bits_set(REG_PUB_APB_REG_PUB_DDR_CHN_LP_CTRL, 8, 7, 0x7f);//ddr channelx axi lower power en

	/*pub_top_pub_top_AHB_RF_DDR_CHN_SLEEP_CTRL*/
	/*bit[0] 1'b0 ddr_chn0_axi_stop_sel*/
	/*bit[1] 1'b0 ddr_chn1_axi_stop_sel*/
	/*bit[2] 1'b0 ddr_chn2_axi_stop_sel*/
	/*bit[3] 1'b0 ddr_chn3_axi_stop_sel*/
	/*bit[4] 1'b0 ddr_chn4_axi_stop_sel*/
	/*bit[5] 1'b0 ddr_chn5_axi_stop_sel*/
	/*bit[6] 1'b0 ddr_chn6_axi_stop_sel*/
	/*bit[7] 1'b0 ddr_chn7_axi_stop_sel*/
	//reg_bits_set(REG_PUB_APB_REG_PUB_DDR_CHN_LP_CTRL, 0, 7, 0x0);//ddr channelx axi top sel

	/*PUB_TOP_AHB_WRAP_RF_FENCING_CTRL 0x61053358*/
	/*bit[30] rf_ddr_fencing_en*/
	/*bit[29:0] rf_fencing_chnl_idle_cnt*/
	reg_bits_set(REG_PUB_APB_REG_FENCING_CTRL, 30, 1, 0x1);//ddr fencing enable
	reg_bits_set(REG_PUB_APB_REG_FENCING_CTRL, 0, 30, 0x600);//ddr fencing channel idle cnt(1us)
}
static void ddrc_apb_lowpower_setting(void)
{
	/*AON_CLK_LP_RF_CLK_SW_MODE_SEL*/
//	reg_bits_set(REG_AON_CLK_LP_CLK_SW_MODE_SEL, 4, 1, 0x0);//clk emc ref mode sel
//	reg_bits_set(REG_AON_CLK_LP_BUSCLK_MODE_SEL, 4, 1, 0x1);//clk_aonmatrix2pub_mode_sel
	/*bit[6] 1'b1 pub_cfg_auto_en*/
	/*bit[7] 1'b0 pub_cfg_slow_en*/
//	reg_bits_set(REG_AON_CLK_LP_CLK_AUTO_GATE_EN_CTRL3, 6, 2, 0x1);
//	reg_bits_set(REG_PMU_APB_PMU_DUMMY_REG1, 14, 2, 0x1);//debug
}
static void ddrc_pub_lowpoer_setting(void)
{
	/*enable pubsys clock auto gating fuctions*/
	/*PUB_TOP_PUB_APB_RF_DMC_DDR_CLK_CTRL 0x61054000*/
	/*bit[31] 1'b1 pub_clk_dfs_sleep_auto_gate_en*/
	/*bit[30] 1'b1 clk_aon_apb_auto_gate_en*/
	/*bit[29] 1'b1 clk_dmc_ref_auto_gate_en*/
	/*bit[28] 1'b1 pub_clk_dfs_auto_gate_en*/
	/*bit[27] 1'b1 dmc_dfi_mon_auto_gate_en*/
	/*bit[26] 1'b1 dmc_sref_auto_gate_en*/
	/*bit[25] 1'b1 ddr_phy_auto_gate_en*/
	/*bit[24] 1'b1 ddr_umctrl_auto_gate_en*/
	/*bit[23] 1'b1 pub_clk_dmc_bist_eb*/
	/*bit[22] 1'b0 pub_clk_dmc_ref_en*/
	/*bit[20] 1'b0 pub_clk_aon_apb_en*/
	/*bit[15] 1'b1 pub_clk_dfs_eb*/
	/*bit[11] 1'b1 pub_clk_dmc_x1_eb*/
	reg_bits_set(REG_PUB_APB_REG_DMC_DDR_CLK_CTRL, 24, 8, 0xFF);
	reg_bits_set(REG_PUB_APB_REG_DMC_DDR_CLK_CTRL, 20, 1, 0x0);
	reg_bits_set(REG_PUB_APB_REG_DMC_DDR_CLK_CTRL, 22, 1, 0x0);
	reg_bits_set(REG_PUB_APB_REG_DMC_DDR_CLK_CTRL, 11, 1, 0x0);
	/*bit[23] bit[15] set 1 for debug,128M clock always on*/
	reg_bits_set(REG_PUB_APB_REG_DMC_DDR_CLK_CTRL, 23, 1, 0x0);
	reg_bits_set(REG_PUB_APB_REG_DMC_DDR_CLK_CTRL, 15, 1, 0x0);

	/* REG_PUB_APB_REG_DMC_DESKEW_WAIT_CNT0[31:16] deskewpll reset,uint: 7.8125ns */
	reg_bits_set(REG_PUB_APB_REG_DMC_DESKEW_WAIT_CNT0, 16, 16, 0x80);

	/*enable qos controller clock auto gating functions 0x61020008*/
	/*bit[0] 1'b1 qosc_port_clkc_auto_gate_en*/
	/*but[1] 1'b1 qosc_bw_limit_auto_gate_en*/
	/*bit[8] 1'b0 qosc_cfg_clk_en*/
	/*bit[9] 1'b1 qosc_cfg_clk_auto_gate_en*/
	//reg_bits_set(REG_PUB_QOSC_AHB_REG_QOSC_CLK_CTRL, 0, 2, 0x3);
	//reg_bits_set(REG_PUB_QOSC_AHB_REG_QOSC_CLK_CTRL, 8, 2, 0x1);

	/*REG_PUB_APB_REG_DMC_CLK_INIT_CFG 0x6105400C*/
	/*bit[8] dmc sleep_force_finish_mode*/
	reg_bits_set(REG_PUB_APB_REG_DMC_CLK_INIT_CFG, 8, 1, 0x1);

	/*REG_PUB_APB_REG_PUB_BUS_CK_EB 0x610531CC*/
	/*bit[7] pub_apb_ptm_reg_eb*/
	/*bit[6] pub_clk_dmc_ptm_eb*/
	//reg_bits_set(REG_PUB_APB_REG_PUB_BUS_CK_EB, 6, 2, 0x0);

	/*for pll pd default*/
	/*0x6105400C*/
	/*bit[4] deskew_pll_pd_default_sel*/
	/*bit[5] deskew_pll_pd_default_sw*/
	reg_bits_set(REG_PUB_APB_REG_DMC_CLK_INIT_CFG, 4, 2, 0x3);

	/* PUB_SYS_SLEEP_BYPASS_CFG 0X640100D8 */
	/*bit[2] pub_sys_self_refresh_flag_bypass, default 0*/
	/*bit[1] pub_sys_pwr_pd_ack_bypass, default 0*/
	/*bit[0] pub_sys_deep_sleep_lock_ack_bypass, default 0*/
	reg_bits_set(REG_PMU_APB_PUB_SYS_SLEEP_BYPASS_CFG, 0, 3, 0x0);

	/* PD_PUB_SYS_CFG 0X6401006C */
	/*bit[25] pd_pub_sys_force_shutdown, default 0*/
	/*bit[24] pd_pub_sys_auto_shutdown, default 1*/
	/*bit[23:16] pd_pub_sys_pwr_on_dly, default 0x20*/
	/*bit[15:8] pd_pub_sys_pwr_on_seq_dly, default 0x80*/
	/*bit[7:0] pd_pub_sys_iso_on_dly, default 0x6*/
	reg_bits_set(REG_PMU_APB_PD_PUB_SYS_CFG, 25, 1, 0x0);
	reg_bits_set(REG_PMU_APB_PD_PUB_SYS_CFG, 24, 1, 0x1);
	reg_bits_set(REG_PMU_APB_PD_PUB_SYS_CFG, 16, 8, 0x01);
	reg_bits_set(REG_PMU_APB_PD_PUB_SYS_CFG, 8, 8, 0x01);
	reg_bits_set(REG_PMU_APB_PD_PUB_SYS_CFG, 0, 8, 0x01);

	/* DDR_SLP_WAIT_CNT 0X64010338 */
	/*bit[31:16] pub_sys_deep_sleep_wait_cnt, default 0*/
	/*bit[15:0] pub_sys_sleep_wait_cnt, default 0, uint:26M cycle*/
	reg_bits_set(REG_PMU_APB_DDR_SLP_WAIT_CNT, 16, 16, 0x0);
	reg_bits_set(REG_PMU_APB_DDR_SLP_WAIT_CNT, 0, 16, 0x80);

}
static void ddrc_smart_light_setting(void)
{
	/*Step 1) enable smart light sleep*/
	REG32(REG_PMU_APB_LIGHT_SLEEP_ENABLE) |= (BIT_PMU_APB_PUB_SYS_SMART_LSLP_ENA);
	/*Step 2) clear force sleep signal*/
	/*REG_PMU_APB_FORCE_DEEP_SLEEP_CFG bit[7] PUB_SYS_FORCE_DEEP_SLEEP*/
	/*REG_PMU_APB_FORCE_LIGHT_SLEEP_CFG bit[7] PUB_SYS_FORCE_LIGHT_SLEEP*/
	reg_bits_set(REG_PMU_APB_FORCE_DEEP_SLEEP_CFG, 7, 1, 0x0);
	reg_bits_set(REG_PMU_APB_FORCE_LIGHT_SLEEP_CFG, 7, 1, 0x0);

	/*Step 3) suto sleep enable*/
	reg_bits_set(REG_PMU_APB_PUB_SYS_AUTO_LIGHT_SLEEP_ENABLE, 0, 16, 0x0000);
}
void ddrc_lowpower_setting(void)
{
#ifndef	DDR_SCAN_ENABLE
	ddrc_axi_lowpower_setting();
	ddrc_apb_lowpower_setting();
	ddrc_pub_lowpoer_setting();
	ddrc_smart_light_setting();
#endif
}
void wdt_rst_keep_sre(void)
{
	if((0x5E486947 == REG32(CHIP_RESET_CONTROL_KEY))&&(REG32(CHIP_RESET_CONTROL_STATUS)&0x3))
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

void ddr_phy_io_latch_clear(void)
{
	reg_bits_set(REG_PMU_APB_DDR_PHY_RET_CFG, 0, 1, 0);	//ddr_phy_ret_en
	reg_bits_set(REG_PMU_APB_DDR_OP_MODE_CFG, 24, 1, 0);	//ddr_phy_auto_ret_en
	reg_bits_set(REG_PMU_APB_DDR_PHY_RET_CFG, 0, 1, 1);	//ddr_phy_ret_en
}

void dmc_port_qos_cfg0(volatile uint32 *addr,uint32 timeout_pri_wr_ch, uint32 timeout_thr_wr_ch, uint32 timeout_thr_rd_ch)
{
	uint32 regval;
	regval = *addr;
	regval = u32_bits_set(regval, 0, 4, timeout_pri_wr_ch);
	regval = u32_bits_set(regval, 16, 8, timeout_thr_wr_ch);
	regval = u32_bits_set(regval, 24, 8, timeout_thr_rd_ch);
	*addr = regval;
}

void dmc_port_qos_cfg1(volatile uint32 *addr,uint32 bandwidth_pri_rd_ch, uint32 bandwidth_thr_ch, uint32 bandwidth_holdoff_en_ch)
{
	uint32 regval;
	regval = *addr;
	regval = u32_bits_set(regval, 0, 4, bandwidth_pri_rd_ch);
	regval = u32_bits_set(regval, 16, 10, bandwidth_thr_ch);
	regval = u32_bits_set(regval, 31, 1, bandwidth_holdoff_en_ch);
	*addr = regval;
}

void dmc_ctrl_qos_init(void)
{
	int i;
	/*port 0 CPU*/
	/*port 1 GPU*/
	/*port 2 DPU/DCAM(ISP_RAW)*/
	/*port 3 ISP/VDSP*/
	/*port 4 AP/VSP/AON/eSE/IPA-1*/
	/*port 5 WTLCP*/
	/*port 6 PUBCP/AUDCP/IPA-2*/
	/*port 7 AI*/
	for(i = 0; i < 8; i++)
	{
		dmc_port_qos_cfg0((volatile uint32 *)(DMC_REG_ADDR_BASE_PHY + 0x20 + i*8),
				port_para[i].timeout_pri_wr_chx,
				port_para[i].timeout_thr_wr_chx,
				port_para[i].timeout_thr_rd_chx);
		dmc_port_qos_cfg1((volatile uint32 *)(DMC_REG_ADDR_BASE_PHY + 0x24 + i*8),
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
	REG32(DMC_MAP) = 0xC0C03030;
}
void ddrc_qos_setting(void)
{
	uint32 i = 0;
	/*Step1 ctrl qos setting*/
//	dmc_ctrl_qos_init();
	/*nic400 pub merge mtx setting*/
	//m0 setting
	REG32(PUB_NIC400_MERGE_MTX_ADDR + 0x0)   = 0x1;
	REG32(PUB_NIC400_MERGE_MTX_ADDR + 0x4)   = 0x06040201;
	REG32(PUB_NIC400_MERGE_MTX_ADDR + 0x8)   = 0x120D0803;
	REG32(PUB_NIC400_MERGE_MTX_ADDR + 0xc)   = 0x22172008;
	REG32(PUB_NIC400_MERGE_MTX_ADDR + 0x060) = 0x3;
	REG32(PUB_NIC400_MERGE_MTX_ADDR + 0x064) = 0x08400840;
	REG32(PUB_NIC400_MERGE_MTX_ADDR + 0x068) = 0x1;
	//m1 settting
	REG32(PUB_NIC400_MERGE_MTX_ADDR + 0x80 + 0x0)   = 0x1;
	REG32(PUB_NIC400_MERGE_MTX_ADDR + 0x80 + 0x4)   = 0x03030303;
	REG32(PUB_NIC400_MERGE_MTX_ADDR + 0x80 + 0x8)   = 0x0C0C0C0C;
	REG32(PUB_NIC400_MERGE_MTX_ADDR + 0x80 + 0xc)   = 0x200C2003;
	REG32(PUB_NIC400_MERGE_MTX_ADDR + 0x80 + 0x060) = 0x3;
	REG32(PUB_NIC400_MERGE_MTX_ADDR + 0x80 + 0x064) = 0x08400840;
	REG32(PUB_NIC400_MERGE_MTX_ADDR + 0x80 + 0x068) = 0x1;

	/*nic400 pub cross mtx setting*/
	//m0 port setting
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x0)   = 0x1;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x4)   = 0x01010101;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x8)   = 0x09090909;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0xc)   = 0x20092001;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x060) = 0x0;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x064) = 0x08400840;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x068) = 0x1;
	//m1 port setting
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x80 + 0x0) = 0x1;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x80 + 0x4) = 0x03030303;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x80 + 0x8) = 0x0C0C0C0C;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x80 + 0xc) = 0x200C2003;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x80 + 0x060) = 0x0;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x80 + 0x064) = 0x08400840;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x80 + 0x068) = 0x1;
	//m2 port setting
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x100 + 0x0) = 0x1;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x100 + 0x4) = 0x08080808;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x100 + 0x8) = 0x14141414;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x100 + 0xc) = 0x20142008;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x100 + 0x060) = 0x0;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x100 + 0x064) = 0x08400840;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x100 + 0x068) = 0x1;
	//m3 port setting
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x180 + 0x0) = 0x1;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x180 + 0x4) = 0x03030303;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x180 + 0x8) = 0x0C0C0C0C;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x180 + 0xc) = 0x200C2003;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x180 + 0x060) = 0x0;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x180 + 0x064) = 0x08400840;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x180 + 0x068) = 0x1;
	//m4 port setting
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x200 + 0x0) = 0x1;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x200 + 0x4) = 0x01010101;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x200 + 0x8) = 0x06060606;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x200 + 0xc) = 0x20062001;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x200 + 0x060) = 0x0;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x200 + 0x064) = 0x08400840;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x200 + 0x068) = 0x1;
	//m5 port setting
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x280 + 0x0) = 0x1;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x280 + 0x4) = 0x01010101;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x280 + 0x8) = 0x0A0A0A0A;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x280 + 0xc) = 0x20082001;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x280 + 0x060) = 0x0;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x280 + 0x064) = 0x08400840;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x280 + 0x068) = 0x1;
	//m6 port setting
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x300 + 0x0) = 0x1;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x300 + 0x4) = 0x02020202;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x300 + 0x8) = 0x07070707;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x300 + 0xc) = 0x20072002;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x300 + 0x060) = 0x0;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x300 + 0x064) = 0x08400840;
	REG32(PUB_NIC400_CROSS_MTX_ADDR + 0x300 + 0x068) = 0x1;

	//enable dmc high urgent
	reg_bits_set(RF_HI_URGENT_EN, 8, 2, 3);
	//switch dmc channel qos to fixed value
	reg_bits_set(REG_PUB_APB_REG_QOS_FIXED_CTRL0, 0, 7, 0x7F);
	REG32(REG_PUB_APB_REG_QOS_FIXED_CTRL1) = 0x0;
	reg_bits_set(REG_PUB_APB_REG_QOS_FIXED_CTRL2, 0, 24, 0x0);

	/*QOS_SWITCH Setting*/
	/*[1]   urgent_chn_sel*/
	/*[0]   qos_urgent_sel*/
	reg_bits_set(REG_PUB_APB_REG_QOS_SWITCH, 0, 2, 0x0);

	/*qos Mapping*/
	REG32(DMC_MAP) = 0x10100404;

	//qosc setting
	//enable qosc
	reg_bits_set(REG_PUB_QOSC_AHB_REG_QOSC_PORT_ENABLE, 0, 7, 0x3F);
	//enable qosc urgent
	reg_bits_set(REG_PUB_QOSC_AHB_REG_QOSC_AXURGENT_EN, 0, 7, 0x3F);
	reg_bits_set(REG_PUB_QOSC_AHB_REG_QOSC_AXURGENT_EN, 16, 7, 0x3F);
	//set high qos
	for (i=0; i < 7; i++)
		reg_bits_set(REG_PUB_QOSC_AHB_REG_QOSC_QOS_VALUE_CH0 + i*4, 16, 16, 0x8844);
}

void ddr_power_cfg(void)
{
	if(LPDDR4 == ddr_chip_cur.chip_type)
	{
		//regulator_set_voltage("vddcore", 800);	//mv
		regulator_set_voltage("vddmem", 1100);
		regulator_set_voltage("vddmemq", 1100);
	}
	else if(LPDDR4X == ddr_chip_cur.chip_type)
	{
		//regulator_set_voltage("vddcore", 800);
		regulator_set_voltage("vddmem", 1100);
		regulator_set_voltage("vddmemq", 600);
	}
}
void ddr_init(void)
{
	#if defined(CONFIG_CLK_PARA)
	uint32 ddr_clk = (mcu_clk_para.ddr_freq.value)/1000000;
	#else
	uint32 ddr_clk = DDR_CLK;
	#endif
	unsigned int regval;
	unsigned int rst_mode = ANA_REG_GET(ANA_REG_GLB_POR_RST_MONITOR);
	unsigned int all_bist_flag = 1;
	rst_mode &= 0xff;
	dram_init_powerup_times = 0;
	ddrc_print_debug("ddr init start\r\n");
	#if defined(ADC_DETECT_DRAM_TYPE)
	ddr_type_detect();
	#endif
	ddr_power_cfg();
	wdt_rst_keep_sre();
	if (find_freq_num(ddr_clk) > 7)
	{
		ddrc_print_err("invalid ddr clock\r\n");
		while(1);
	}

	/*step 1). pub soft rst*/
	pub_soft_reset();

	/*step 2). ddr phy io latch clear */
	ddr_phy_io_latch_clear();

	/*step 3). release dmc ctrl rst*/
	ddr_ctrl_soft_reset();

	/*step 4). ddrc ctrl init pre setting*/
	ctrl_pre_set_seq(dfs_table);

	/*step 5). ddrc phy init pre setting*/
	ddrc_phy_pre_set_seq();
	//reg_modify_before_initial();
	/*step 6). dmc ctrl rst clear*/
	ddr_ctrl_soft_reset_clear();

	/*step 7). initial frequency point*/
	ddrc_phy_init_seq(ddr_clk);

	/*step 8). ddrc phy setting after phy initial*/
	ddrc_phy_post_set_seq();
//	ddrc_phy_init_post_seq();

	/*step 9). exit selfrefresh and initial DRAM if not send current frequency MRWs*/
	/*ch0_rfdmem_cmd_chip_sleep*/
	dmc_exit_self_refresh(8);

	/*step 10). ddrc powerup init setting*/
	/*this setting for one freq boot*/

	ctrl_post_set_seq();

	/*step 12). dmc initial setting post*/

	/*bist test*/
	//reg_modify_before_bist();
	if((rst_mode==0x70)||(rst_mode==0x80)||(rst_mode==0xf0)||(rst_mode==0xf1))
		all_bist_flag = 0;
	dmc_ddr_test_ch(0, all_bist_flag);
	dmc_ddr_test_ch(0,0);      //infomation for cm4
	/* aon ram clear */
	aon_ram_for_ddr_clear();

	/*transmit ddr info for sp*/
	dmc_update_param_for_sp();	//call when first use aon ram

	/*save ddr info*/
	dmc_ddr_mode_register_store();

	/*pub axi low power setting*/
	ddrc_lowpower_setting();

	/*step 11). phy or ctrl setting after dram inital*/
	REG32(REG_PMU_APB_PUB_ACC_RDY) = 0x1;

	/*transmit ddr size for uboot*/
	dmc_update_param_for_uboot();

	/*pub qos setting*/
	ddrc_qos_setting();
	/*locked dmc ctrl registers*/
	dmc_ctrl_reg_lock();
	/*ddr debug setting*/
	//dmc_ddr_debug_mode();

	ddrc_print_debug("ddr init pass\r\n");
}
void test_entry(void)
{
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
	ddr_scan_vdd_seq();
	#endif
}
int sdram_init(void)
{
	ddr_init();
	test_entry();
	return 0;
}


