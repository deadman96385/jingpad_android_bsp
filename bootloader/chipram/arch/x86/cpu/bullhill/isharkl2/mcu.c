
/******************************************************************************
    David.Jia   2007.10.29      share_version_union

******************************************************************************/

#include <common.h>
#include <sci_types.h>
/* delete  chip_drv_common_io_h */
#include <adi.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_chipram_env.h>
#include <timer.h>
#include <asm/io.h>

#define MPLL_REFIN 26
#define DPLL_REFIN 26
#define REFIN 26
#define LPLL_REFIN 260
#define NINT(freq,refin)	(freq/refin)
#define KINT(freq,refin)	((freq- (freq/refin) * refin) * (0x7FFFFF + 1) / refin)
#define PIN_SDIO_SL 0XE42A101C

#if defined(CONFIG_CLK_PARA)
#include <asm/arch/clk_para_config.h>
const MCU_CLK_PARA_T mcu_clk_para=
{
	.magic_header = MAGIC_HEADER,
	.version = CONFIG_PARA_VERSION,
	.clk_vol_unit_count = 8,
	.clk_list_unit_count = 4,

	.ddr_freq.name = "C*DDR",//clk_ddr
	.ddr_freq.value = DDR_FREQ,

	.ddr_debug_mode.name = "DDR_MODE",//clk_ddr
	.ddr_debug_mode.value = DDR_MODE,
#ifdef DCDC_ARM0
	.dcdc_arm0.name = "D*ARM0",//dcdc_arm0,1,core
	.dcdc_arm0.value = DCDC_ARM0,
#endif

#ifdef DCDC_CORE
	.dcdc_core.name = "D*CORE",
	.dcdc_core.value = DCDC_CORE,
#endif

#ifdef DCDC_ARM1
	.dcdc_arm1.name = "D*ARM1",
	.dcdc_arm1.value = DCDC_ARM1,
#endif

#ifdef DCDC_MEM
	.dcdc_mem.name = "D*MEM",
	.dcdc_mem.value = DCDC_MEM,
#endif

#ifdef DCDC_GEN
	.dcdc_gen.name = "D*GEN",
	.dcdc_gen.value = DCDC_GEN,
#endif

	.ssc_enable.name = "ssc_eb",//new add for ssc
	.ssc_enable.value = 0,
	.ssc_width.name = "ssc_wid",
	.ssc_width.value = 0,

	.axi_freq.name = "C#AXI",//clk_axi
	.axi_freq.lvl_count = CLK_AXI_LEVEL,
	.axi_freq.lvl = CLK_AXI_LEVEL_ID,
	.axi_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,//all c# clk,the max level_count,now max=6
	.axi_freq.clk_list = {26000000,96000000,128000000,256000000},

	.dap_freq.name = "C#DAP",//clk_dap
	.dap_freq.lvl_count = CLK_DAP_LEVEL,
	.dap_freq.lvl = CLK_DAP_LEVEL_ID,
	.dap_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.dap_freq.clk_list = {4000000,26000000,100000000,76800000,128000000,153600000},

	.ap_apb_freq.name = "C#AP_APB",//clk_apb
	.ap_apb_freq.lvl_count = CLK_APB_LEVEL,
	.ap_apb_freq.lvl = CLK_APB_LEVEL_ID,
	.ap_apb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.ap_apb_freq.clk_list = {26000000,64000000,96000000,128000000},

	.aon_apb_freq.name = "C#AONAPB",//clk_aon_apb
	.aon_apb_freq.lvl_count = CLK_AON_APB_LEVEL,
	.aon_apb_freq.lvl = CLK_AON_APB_LEVEL_ID,
	.aon_apb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.aon_apb_freq.clk_list = {4000000,26000000,100000000,96000000,128000000,153600000},

	.magic_end = MAGIC_END
};
#endif

struct iwhale_ibias_table {
	unsigned long rate;
	u8 ibias;
};

#define IWHALE_PLL_MAX_RATE		(0xFFFFFFFF)

struct iwhale_ibias_table isharkl2_adjustable_pll1_table[] = {//GPLL/LPLL/DPLL/RPLL
	{
		.rate = 1014000000,
		.ibias = 0x0,
	},
	{
		.rate = 1300000000,
		.ibias = 0x1,
	},
	{
		.rate = 1612000000,
		.ibias = 0x2,
	},
	{
		.rate = IWHALE_PLL_MAX_RATE,
		.ibias = 0x2,
	},
};

struct iwhale_ibias_table isharkl2_adjustable_pll2_table[] = {//twPPLL
	{
		.rate = 1014000000,
		.ibias = 0x0,
	},
	{
		.rate = 1300000000,
		.ibias = 0x1,
	},
	{
		.rate = 1612000000,
		.ibias = 0x3,
	},
	{
		.rate = IWHALE_PLL_MAX_RATE,
		.ibias = 0x3,
	},
};


void chipram_env_set(u32 mode)
{
	chipram_env_t *p_env;
	p_env = (struct chipram_env *)CHIPRAM_ENV_ADDR;
	p_env->magic = CHIPRAM_ENV_MAGIC;
	p_env->mode = mode;
	p_env->dram_size = 0;
	/*
	   p_env->vol_para_addr = (u64)vol_para;
	 */
}

static void delay()
{
	volatile uint32 i;
	for (i=0; i<0x100; i++);
}

static void Rco100_config()
{
	REG32(REG_AON_APB_APB_EB1) |= BIT_AON_APB_RC100M_CAL_EB;//cal_eb
	REG32(REG_AON_APB_APB_RST1) |= BIT_AON_APB_RC100M_CAL_SOFT_RST;//rst_eb
	delay();
	REG32(REG_AON_APB_APB_RST1) &= ~BIT_AON_APB_RC100M_CAL_SOFT_RST;//rst_eb
	REG32(REG_AON_APB_RC100M_CFG) |= BIT_AON_APB_RC100M_FORCE_EN;//force_en
	REG32(REG_AON_APB_RC100M_CFG) |= BIT_AON_APB_RC100M_CAL_START;//start cal
	while(!(REG32(REG_AON_APB_RC100M_CFG) & BIT_AON_APB_RC100M_CAL_DONE));//when cal_done set 1,ok
	REG32(REG_AON_APB_RC100M_CFG) &= ~BIT_AON_APB_RC100M_CAL_START;

	REG32(REG_AON_APB_RC100M_CFG) |= BIT_AON_APB_RC100M_AUTO_GATE_EN;
}

static uint32 AxiClkConfig(void)
{
#if defined(CONFIG_CLK_PARA)
	uint32 clk_cfg;
	clk_cfg = REG32(REG_AP_CLK_CGM_AP_AXI_CFG);
	clk_cfg &= ~BIT_AP_CLK_CGM_AP_AXI_SEL(3);
	clk_cfg |= BIT_AP_CLK_CGM_AP_AXI_SEL(mcu_clk_para.axi_freq.lvl);//isharkl2 3:256M
	REG32(REG_AP_CLK_CGM_AP_AXI_CFG) = clk_cfg;
#endif
	delay();
	return 0;
}

static uint32 Analog_IO_ClkConfig(void)
{
	uint32 clk_cfg;
	REG32(REG_AON_APB_APB_EB1) &= ~(BIT_AON_APB_ANALOG_APB_EB | BIT_AON_APB_IO_APB_EB);
	clk_cfg = REG32(REG_AON_CLK_CGM_ANALOG_APB_CFG);
	clk_cfg &= ~BIT_AON_CLK_CGM_ANALOG_APB_SEL(~0x0);
	clk_cfg |= BIT_AON_CLK_CGM_ANALOG_APB_SEL(2);
	REG32(REG_AON_CLK_CGM_ANALOG_APB_CFG) = clk_cfg;//clk_analog_apb:48M

	clk_cfg = REG32(REG_AON_CLK_CGM_IO_APB_CFG);
	clk_cfg &= ~BIT_AON_CLK_CGM_IO_APB_SEL(~0x0);
	clk_cfg |= BIT_AON_CLK_CGM_IO_APB_SEL(2);
	REG32(REG_AON_CLK_CGM_IO_APB_CFG) = clk_cfg;//clk_io:48M
	REG32(REG_AON_APB_APB_EB1) |= (BIT_AON_APB_ANALOG_APB_EB | BIT_AON_APB_IO_APB_EB);
	delay();
	return 0;
}

static uint32 ApbClkConfig(void)
{
#if defined(CONFIG_CLK_PARA)
	uint32 apb_cfg;
	apb_cfg  = REG32(REG_AP_CLK_CGM_AP_APB_CFG);
	apb_cfg &= ~BIT_AP_CLK_CGM_AP_APB_SEL(3);
	apb_cfg |= BIT_AP_CLK_CGM_AP_APB_SEL(mcu_clk_para.ap_apb_freq.lvl);  //isharkl2:  0:26M 1:64M 2:96M 3:128M
	REG32(REG_AP_CLK_CGM_AP_APB_CFG) = apb_cfg;

	apb_cfg = REG32(REG_AON_CLK_CGM_AON_APB_CFG);
	apb_cfg &= ~BIT_AON_CLK_CGM_AON_APB_SEL(7);
	apb_cfg |= BIT_AON_CLK_CGM_AON_APB_SEL(mcu_clk_para.aon_apb_freq.lvl);//isharkl2:  0:26M  4:128M 5:153.6m
	REG32(REG_AON_CLK_CGM_AON_APB_CFG) = apb_cfg;
#endif
	delay();
	return 0;
}

static uint32 DapClkConfig(void)
{
#if defined(CONFIG_CLK_PARA)
	uint32 apb_cfg;
	apb_cfg  = REG32(REG_AON_CLK_CGM_DAP_CFG);
	apb_cfg &= ~BIT_AON_CLK_CGM_DAP_SEL(7);
	apb_cfg |= BIT_AON_CLK_CGM_DAP_SEL(mcu_clk_para.dap_freq.lvl);  //isharkl2:  5:153.6M
	REG32(REG_AON_CLK_CGM_DAP_CFG) = apb_cfg;
#endif
	delay();
	return 0;
}

static uint32 ClkConfig(void)
{
	AxiClkConfig();
	DapClkConfig();
	ApbClkConfig();
	Analog_IO_ClkConfig();
	return 0;
}

static int power_config()
{
#if defined(CONFIG_ADIE_SC2731)

#ifdef DCDC_ARM0
	regulator_set_voltage("vddarm0",mcu_clk_para.dcdc_arm0.value);
#endif

#ifdef DCDC_ARM1
	regulator_set_voltage("vddarm1",mcu_clk_para.dcdc_arm1.value);
#endif

#ifdef DCDC_CORE
	regulator_set_voltage("vddcore",mcu_clk_para.dcdc_core.value);
#endif

#ifdef DCDC_MEM
	regulator_set_voltage("vddmem",mcu_clk_para.dcdc_mem.value);
#endif

#ifdef DCDC_GEN
	regulator_set_voltage("vddgen",mcu_clk_para.dcdc_gen.value);
#endif

	/* for sp9853i, there is 1.2v leakage voltage when power off vddsdio,
	* need to set pinctrl sl bit to avoid leak voltage. */
	CHIP_REG_OR(PIN_SDIO_SL, BIT_3);
#ifdef CONFIG_NAND_SPL
	ANA_REG_OR(ANA_REG_GLB_LDO_USB33_REG0, BIT_LDO_USB33_PD);
#endif

	/*
	 * fix DCDC GPU to DCM_PWM mode
	 * */
	ANA_REG_OR(ANA_REG_GLB_DCDC_GPU_REG0, BIT_DCDC_GPU_PFM);
	ANA_REG_BIC(ANA_REG_GLB_DCDC_GPU_REG0, BIT_DCDC_GPU_DCM);
#endif
	return 0;
}

uint32 MCU_Init()
{
	power_config();
	/*enable and calibrate rco100m */
	Rco100_config();
	if (ClkConfig())
		/* clkconfig failed*/
		while(1);
	return 0;
}

static void Sel_rco100_for_lp()
{
	/* Switch clk_debounce to RCO25m */
	REG32(REG_AON_CLK_CGM_DEBOUNCE_CFG) &= BIT_AON_CLK_CGM_DEBOUNCE_SEL(0);
	REG32(REG_AON_CLK_CGM_DEBOUNCE_CFG) |= BIT_AON_CLK_CGM_DEBOUNCE_SEL(2);

	/* Switch clk_dap_cfg to RCO100m */
	REG32(REG_AON_CLK_CGM_DAP_CFG) &= BIT_AON_CLK_CGM_DAP_SEL(0);
	REG32(REG_AON_CLK_CGM_DAP_CFG) |= BIT_AON_CLK_CGM_DAP_SEL(2);

	/* Switch clk_adi_cfg to RCO25m */
	REG32(REG_AON_CLK_CGM_ADI_CFG) &= BIT_AON_CLK_CGM_ADI_SEL(0);
	REG32(REG_AON_CLK_CGM_ADI_CFG) |= BIT_AON_CLK_CGM_ADI_SEL(1);
}

uint32 Chip_Sleep_Ctrl()
{
	CHIP_REG_OR(REG_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_CTRL,
		BIT_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_CM4_DEEP_SLEEP_MASK |
		BIT_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_PLL_PD_MASK |
		0);

	return 0;
}

void SwitchPll(void)
{
	uint32 clk_cfg;

	/* TWPLL switch */
	clk_cfg = REG32(REG_PMU_APB_TWPLL_REL_CFG);
	clk_cfg &= ~BIT_PMU_APB_TWPLL_REF_SEL(7);
	clk_cfg |= BIT_PMU_APB_TWPLL_REF_SEL(1);//sel rpll0
	REG32(REG_PMU_APB_TWPLL_REL_CFG) = clk_cfg;

	/* LPLL0 switch */
	clk_cfg = REG32(REG_PMU_APB_LPLL0_REL_CFG);
	clk_cfg &= ~BIT_PMU_APB_LPLL0_REF_SEL(7);
	clk_cfg |= BIT_PMU_APB_LPLL0_REF_SEL(1);//sel rpll0
	REG32(REG_PMU_APB_LPLL0_REL_CFG) = clk_cfg;



	/* m_lvds switch */
	/* keep default configuration, select 26M receive buffer*/

	delay();
	delay();
	delay();
	delay();
	delay();
	delay();
	delay();


}

void pll_sel_config(uint32_t gen_para)
{
	/*
	 * xltbuf1,xtlbuf2 not use,xtl0 and xtlbuf0 related all subsys now,
	 * Noted, after rco100 done,will not related cm4.
	 */
	CHIP_REG_OR(REG_PMU_APB_XTL0_REL_CFG,
			BIT_PMU_APB_XTL0_AP_SYS_SEL |
			BIT_PMU_APB_XTL0_WTLCP_SYS_SEL |
			BIT_PMU_APB_XTL0_PUBCP_SYS_SEL |
			BIT_PMU_APB_XTL0_AUD_SYS_SEL |
			BIT_PMU_APB_XTL0_PUB0_SYS_SEL |
			BIT_PMU_APB_XTL0_CAM_PD_SEL |
			0
			);

	CHIP_REG_AND(REG_PMU_APB_XTL0_REL_CFG,
			~(BIT_PMU_APB_XTL0_CM4_SYS_SEL |
			BIT_PMU_APB_XTL0_PUB1_SYS_SEL));

	CHIP_REG_OR(REG_PMU_APB_XTLBUF0_REL_CFG,
			BIT_PMU_APB_XTLBUF0_AP_SYS_SEL |
			BIT_PMU_APB_XTLBUF0_WTLCP_SYS_SEL |
			BIT_PMU_APB_XTLBUF0_PUBCP_SYS_SEL |
			BIT_PMU_APB_XTLBUF0_AUD_SYS_SEL |
			BIT_PMU_APB_XTLBUF0_PUB0_SYS_SEL |
			BIT_PMU_APB_XTLBUF0_CAM_PD_SEL |
			0
			);

	CHIP_REG_AND(REG_PMU_APB_XTLBUF0_REL_CFG,
			~(BIT_PMU_APB_XTLBUF0_CM4_SYS_SEL |
			BIT_PMU_APB_XTLBUF0_PUB1_SYS_SEL));
	/*
	 * MPLL0,MPLL1,MPLL2 asic default related to ap,
	 * need to configure to related to ext_pd, suggestion from mings.li
	 */
	CHIP_REG_OR(REG_PMU_APB_MPLL0_REL_CFG, BIT_PMU_APB_MPLL0_EXT_PD_SEL);
	CHIP_REG_AND(REG_PMU_APB_MPLL0_REL_CFG, ~BIT_PMU_APB_MPLL0_AP_SYS_SEL);

	CHIP_REG_OR(REG_PMU_APB_MPLL1_REL_CFG, BIT_PMU_APB_MPLL1_EXT_PD_SEL);
	CHIP_REG_AND(REG_PMU_APB_MPLL1_REL_CFG, ~BIT_PMU_APB_MPLL1_AP_SYS_SEL);
	/*
	 * Noted, after rc0100 done,rpll0 will not related to cm4.
	 * rpll1 not use.
	 */
	CHIP_REG_OR(REG_PMU_APB_RPLL0_REL_CFG,
			BIT_PMU_APB_RPLL0_AP_SYS_SEL |
			BIT_PMU_APB_RPLL0_WTLCP_SYS_SEL |
			BIT_PMU_APB_RPLL0_PUBCP_SYS_SEL |
			BIT_PMU_APB_RPLL0_AUD_SYS_SEL |
			BIT_PMU_APB_RPLL0_PUB0_SYS_SEL |
			BIT_PMU_APB_RPLL0_CAM_PD_SEL |
			0
			);

	CHIP_REG_AND(REG_PMU_APB_RPLL0_REL_CFG,
			~(BIT_PMU_APB_RPLL0_CM4_SYS_SEL |
			BIT_PMU_APB_RPLL0_PUB1_SYS_SEL));

	CHIP_REG_OR(REG_PMU_APB_TWPLL_REL_CFG,
			BIT_PMU_APB_TWPLL_AP_SYS_SEL |
			BIT_PMU_APB_TWPLL_WTLCP_SYS_SEL |
			BIT_PMU_APB_TWPLL_PUBCP_SYS_SEL |
			BIT_PMU_APB_TWPLL_AUD_SYS_SEL |
			BIT_PMU_APB_TWPLL_PUB0_SYS_SEL |
			BIT_PMU_APB_TWPLL_CAM_PD_SEL |
			0
			);

	CHIP_REG_AND(REG_PMU_APB_TWPLL_REL_CFG,
			~(BIT_PMU_APB_TWPLL_CM4_SYS_SEL |
			BIT_PMU_APB_TWPLL_PUB1_SYS_SEL));
	/*
	 * Noted,dpll1 related will change after DDR introducing MACRO.
	 */
	CHIP_REG_OR(REG_PMU_APB_DPLL0_REL_CFG,
			BIT_PMU_APB_DPLL0_PUB0_SYS_SEL |
			0
			);

	CHIP_REG_AND(REG_PMU_APB_DPLL0_REL_CFG,
			~(BIT_PMU_APB_DPLL0_AP_SYS_SEL |
				BIT_PMU_APB_DPLL0_WTLCP_SYS_SEL |
				BIT_PMU_APB_DPLL0_PUBCP_SYS_SEL |
				BIT_PMU_APB_DPLL0_AUD_SYS_SEL |
				BIT_PMU_APB_DPLL0_CM4_SYS_SEL |
				BIT_PMU_APB_DPLL0_CAM_PD_SEL |
				0)
			);

	/*
	 * lpll0 only related to ap.
	 */
	CHIP_REG_OR(REG_PMU_APB_LPLL0_REL_CFG,
			BIT_PMU_APB_LPLL0_WTLCP_SYS_SEL |
			0
			);

	CHIP_REG_AND(REG_PMU_APB_LPLL0_REL_CFG,
			~(BIT_PMU_APB_LPLL0_AP_SYS_SEL |
				BIT_PMU_APB_LPLL0_PUBCP_SYS_SEL |
				BIT_PMU_APB_LPLL0_AUD_SYS_SEL |
				BIT_PMU_APB_LPLL0_CM4_SYS_SEL |
				BIT_PMU_APB_LPLL0_PUB0_SYS_SEL |
				BIT_PMU_APB_LPLL0_CAM_PD_SEL |
				0)
			);
	/*
	 * gpll dspll default select no subsys
	 * isp should configure select nothing
	 */
	CHIP_REG_AND(REG_PMU_APB_ISPPLL_REL_CFG, ~0x1FF);

	/*
	 * RC ralated to all subsys now.
	 * related configuration may be change after rco10 done.
	 */
	CHIP_REG_OR(REG_PMU_APB_RC_REL_CFG,
			BIT_PMU_APB_RC_AP_SYS_SEL |
			BIT_PMU_APB_RC_WTLCP_SYS_SEL |
			BIT_PMU_APB_RC_PUBCP_SYS_SEL |
			BIT_PMU_APB_RC_AUD_SYS_SEL |
			BIT_PMU_APB_RC_CM4_SYS_SEL |
			BIT_PMU_APB_RC_PUB0_SYS_SEL |
			BIT_PMU_APB_RC_CAM_PD_SEL |
			0
			);
	/*gpll force on, otherwise clk register gpu dt failed*/
	CHIP_REG_OR(REG_PMU_APB_GPLL_REL_CFG, BIT_PMU_APB_GPLL_AP_SYS_SEL);

	CHIP_REG_AND(REG_PMU_APB_XTLBUF2_REL_CFG,
			~BIT_PMU_APB_XTLBUF2_CM4_SYS_SEL);

	CHIP_REG_AND(REG_PMU_APB_DPLL1_REL_CFG,
			~(BIT_PMU_APB_DPLL1_CM4_SYS_SEL |
			BIT_PMU_APB_DPLL1_PUB1_SYS_SEL));
}

void ssc_setting(uint32_t ssc_eb, uint32_t ssc_width)
{
	if(1 ==  ssc_eb)
	{
		/*something to be done*/
	}
}

/*
 * rpll default configuration can not meet SW demand,
 * so we need reconfiguration it.
 * 1. 780M (high freq to meet emmc demand)
 * 2. keep rpll has stable output
 */
void Rpll_reconfig()
{
	uint32 value;
	/* 1:dbg sel*/
	REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_REG_SEL_CFG_0) |= (BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_DIV1_EN |
															BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_RESERVED |
															BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_BIST_EN |
															BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_26M_DIV |
															BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_IBIAS);
	/* pmu control 2:rpll_nint = 0x1e,26m_div=0x1e*/
	REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_WRAP_GLUE_CTRL) = 0x0;

	value = REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_MODU_CTRL_0);
	value &= ~BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_NINT(~0x0);
	value |= BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_NINT(0x1E);
	REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_MODU_CTRL_0) = value;

	value = REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_DIV_CTRL_0);
	value &= ~(BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_26M_DIV(~0x0) | BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_RESERVED(~0x0));
	value |= BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_26M_DIV(0x1E);
	REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_DIV_CTRL_0) = value;
	/* 3:enable rpll_26m*/
	REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_DIV_CTRL_0) |= BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_DIV1_EN;
	/* 4:Rpll0 not bypass */
	REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK26M_CTL_0) |= BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_26M_SEL;
	/*5.Rpll0 ibias setting 3*/
	REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_0) |= BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_IBIAS(~0x0);
	REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_2) |= BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_IBIAS(~0x0);
	REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_WRAP_GLUE_CTRL) = 0x13;//mdar control
	udelay(200);
}

void Disable_Unused_Module()
{
	REG32(REG_AON_APB_APB_RTC_EB) &= ~BIT_AON_APB_GPU_TS_EB;
	REG32(REG_AON_APB_APB_EB1) &= ~BIT_AON_APB_RC100M_CAL_EB;
	REG32(REG_AON_APB_CGM_CLK_TOP_REG1) &=
				~(BIT_AON_APB_CGM_SDIO2_1X_EN |
				BIT_AON_APB_CGM_SDIO2_2X_EN);
}

static void uncore_register_set_bits(u8 portID, u8 offset, u32 mask, u32 val)
{
	u32 orig, tmp;
	u32 index = (portID << 16) |(offset << 8) | 0xF0;

	outl(0x800000D0, 0xCF8);
	outl(0x06000000 | index, 0xCFC);
	outl(0x800000D4, 0xCF8);
	orig = inl(0xCFC);

	tmp = orig & ~mask;
	tmp |= val & mask;

	outl(0x800000D4,0xCF8);
	outl(tmp,0xCFC);
	outl(0x800000D0,0xCF8);
	outl(0x07000000 | index,0xCFC);
}

static void dram_configure_bridge_perf(void)
{
	/*
	 * Sync FIFO to have same CLK
	 * 0 - Not same
	 * 1 - same
	 * Bit[4], Bit[2]
	 */
	uncore_register_set_bits(0x1B, 0x0, BIT(4) | BIT(2), BIT(4) | BIT(2));

	/*
	 * Request MAX_NUM of pending reads
	 * Bit[7:0]
	 * Update cache paramaters
	 * Bit[19:16]
	 */
	uncore_register_set_bits(0x1B, 0x1, BIT(16), BIT(16));

	/*
	 * Enable Non-posted writes
	 * Bit[0]
	 * Enable last bit
	 */
	uncore_register_set_bits(0x14, 0x10, BIT(0), BIT(0));

	/* ackgate bit 0-22 */
	uncore_register_set_bits(0x00, 0x18, 0x007FFFFF, 0x007FFFFF);

	/* aisochctl */
	uncore_register_set_bits(0x00, 0x20, 0x1FF, 0x1);

	/* avcctl bit 31 8 */
	uncore_register_set_bits(0x00, 0x21, BIT(31) | BIT(8), BIT(31) | BIT(8));

	/* aarbctl0 */
	uncore_register_set_bits(0x00, 0xC0, 0xF, 0x4);

	/* bwflush */
	uncore_register_set_bits(0x03, 0x07, 0x0000FFFF, 0x0);

	/* bbankmask 25 */
	uncore_register_set_bits(0x03, 0x08, 0x01FFFFFF, 0x0);

	/* browmask 25 */
	uncore_register_set_bits(0x03, 0x09, 0x01FFFFFF, 0x003FFFFC);

	/* brankmask 10 */
	uncore_register_set_bits(0x03, 0x0A, 0x000002FF, 0x80);

	/* balimit0 */
	uncore_register_set_bits(0x03, 0x0B, 0x3F3F3F3F, 0x1F1F1F1F);
	/* balimit1 */
	uncore_register_set_bits(0x03, 0x0C, 0x3F3F3F3F, 0x1F1F1F1F);
	/* balimit2 */
	uncore_register_set_bits(0x03, 0x0D, 0x3F3F3F3F, 0x1F1F1F1F);
	/* balimit3 */
	uncore_register_set_bits(0x03, 0x0E, 0x3F3F3F3F, 0x1F1F1F1F);

	/* bmisc, mask as RO */
	/* uncore_register_set_bits(0x03, 0x28, 0x7<<6, 0x7<<6); */

	/* bctrl 0,1,2,3 11,12 */
	uncore_register_set_bits(0x03, 0x3D, 0xF|BIT(11)|BIT(12), 0xF|BIT(11)|BIT(12));

	/* cunit_ssa_regional_trunkgate_ctl */
	uncore_register_set_bits(0x08, 0x43, 0xFF|BIT(16)|BIT(18), 0x08|BIT(16)|BIT(18));

	/* t_ctl, mask now, break s3 in some devices */
	/* uncore_register_set_bits(0x02, 0x03, BIT(10)|BIT(16), BIT(10)); */

	/* t_misc_ctl */
	uncore_register_set_bits(0x02, 0x04, 0xF<<1, 0x6<<1);

	/* t_clkgate_ctl 0-28 */
	uncore_register_set_bits(0x02, 0x05, 0x1FFFFFFF, 0x1FFFFFFF);

	/* memaxi AW cobuf enable */
	REG32(REG_PUB_APB_PUB0_AXI_AW_COBUF_EN) |= 0x2;
}

void Chip_Init (void)
{
#ifndef CONFIG_FPGA
	timer_init();
	/* BaseIA perf config */
	dram_configure_bridge_perf();
	//disable retrigger memory repair when switch pll
	REG32(REG_PMU_APB_PD_AON_SYS_PWR_CFG) &= ~BIT_PMU_APB_AON_WAKEUP_POR;
	REG32(REG_AP_CLK_CGM_AP_APB_CFG) = 0;
	REG32(REG_AP_CLK_CGM_AP_AXI_CFG) = 0;
	sci_adi_init();
	regulator_init();
	pll_sel_config(0x0);
	Rpll_reconfig();//suggest from demi tian
	SwitchPll();
	MCU_Init();
	Disable_Unused_Module();
	Chip_Sleep_Ctrl();
	Sel_rco100_for_lp();
	/* new add interface for ssc enable and ssc width setting */
	ssc_setting(mcu_clk_para.ssc_enable.value,mcu_clk_para.ssc_width.value);
	sprd_gpio_init();
	#ifdef CONFIG_CLK_PARA
	sdram_init(mcu_clk_para.ddr_freq.value,mcu_clk_para.ddr_debug_mode.value);
	#else
	sdram_init(DDR_FREQ,DDR_MODE);
	#endif
#else
	sdram_init();
#endif
}

