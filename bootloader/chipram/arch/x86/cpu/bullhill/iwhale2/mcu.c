
/******************************************************************************
    David.Jia   2007.10.29      share_version_union

******************************************************************************/

#include <common.h>
#include <sci_types.h>
#include <timer.h>
/* delete  chip_drv_common_io_h */
#include <adi.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_chipram_env.h>
#include "chip_id.h"
#include <asm/io.h>

#define MPLL_REFIN 26
#define DPLL_REFIN 26
#define REFIN 26
#define LPLL_REFIN 260
#define NINT(freq,refin)	(freq/refin)
#define KINT(freq,refin)	((freq- (freq/refin) * refin) * (0x7FFFFF + 1) / refin)

#if defined(CONFIG_CLK_PARA)
#include <asm/arch/clk_para_config.h>
const MCU_CLK_PARA_T mcu_clk_para=
{
	.magic_header = MAGIC_HEADER,
	.version = CONFIG_PARA_VERSION,
	.clk_vol_unit_count = 8,
	.clk_list_unit_count = 4,

	.ddr_freq.name = "C*DDR",//clk_ddr
	.ddr_freq.value = CLK_DDR_FREQ,

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

struct iwhale_ibias_table iwhale2_adjustable_pll1_table[] = {//GPLL/LPLL/DPLL/RPLL/TWPLL
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

struct iwhale_ibias_table iwhale2_adjustable_pll2_table[] = {//CPPLL
	{
		.rate = 702000000,
		.ibias = 0x0,
	},
	{
		.rate = 884000000,
		.ibias = 0x1,
	},
	{
		.rate = 1118000000,
		.ibias = 0x2,
	},
	{
		.rate = IWHALE_PLL_MAX_RATE,
		.ibias = 0x2,
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

static void udelay(u32 us)
{
	volatile uint32 i,j;
	for(i = 0; i < us; i++)
		for(j = 0; j < 624; j++);
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

	REG32(REG_AON_APB_RC100M_CFG) |= BIT_AON_APB_RC100M_AUTO_GATE_EN;//start auto

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

static uint32 AxiClkConfig(void)
{
#if defined(CONFIG_CLK_PARA)
	uint32 clk_cfg;
	clk_cfg = REG32(REG_AP_CLK_CGM_AP_AXI_CFG);
	clk_cfg &= ~BIT_AP_CLK_CGM_AP_AXI_SEL(3);
	clk_cfg |= BIT_AP_CLK_CGM_AP_AXI_SEL(mcu_clk_para.axi_freq.lvl);//iwhale2 3:256M
	REG32(REG_AP_CLK_CGM_AP_AXI_CFG) = clk_cfg;
#endif
	delay();
	return 0;
}

static uint32 NocClkConfig(void)
{
     uint32 clk_cfg;
     clk_cfg = REG32(REG_AON_CLK_CGM_AP_NOC_CFG);
     clk_cfg &= ~BIT_AON_CLK_CGM_AP_NOC_SEL(3);
     clk_cfg |= BIT_AON_CLK_CGM_AP_NOC_SEL(3);//iwhale2 3:256M
     REG32(REG_AON_CLK_CGM_AP_NOC_CFG) = clk_cfg;
     delay();
     return 0;
}

static uint32 CP_MdarClkConfig(void)
{
     uint32 clk_cfg;
     clk_cfg = REG32(REG_AON_CLK_CGM_AON_MDAR_APB_CFG);
     clk_cfg &= ~BIT_AON_CLK_CGM_AON_MDAR_APB_SEL(7);
     clk_cfg |= BIT_AON_CLK_CGM_AON_MDAR_APB_SEL(5);//iwhale2 3:153.6M
     REG32(REG_AON_CLK_CGM_AON_MDAR_APB_CFG) = clk_cfg;
     delay();
     return 0;
}

static uint32 CP_AonClkConfig(void)
{
     uint32 clk_cfg;
     clk_cfg = REG32(REG_AON_CLK_CGM_AON_CP_APB_CFG);
     clk_cfg &= ~BIT_AON_CLK_CGM_AON_CP_APB_SEL(7);
     clk_cfg |= BIT_AON_CLK_CGM_AON_CP_APB_SEL(5);//iwhale2 3:153.6M
     REG32(REG_AON_CLK_CGM_AON_CP_APB_CFG) = clk_cfg;
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
	apb_cfg |= BIT_AP_CLK_CGM_AP_APB_SEL(mcu_clk_para.ap_apb_freq.lvl);  //iwhale2:  0:26M 1:64M 2:96M 3:128M
	REG32(REG_AP_CLK_CGM_AP_APB_CFG) = apb_cfg;

	apb_cfg = REG32(REG_AON_CLK_CGM_AON_APB_CFG);
	apb_cfg &= ~BIT_AON_CLK_CGM_AON_APB_SEL(7);
	apb_cfg |= BIT_AON_CLK_CGM_AON_APB_SEL(mcu_clk_para.aon_apb_freq.lvl);//iwhale2:  0:26M  4:128M 5:153.6m
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
	apb_cfg |= BIT_AON_CLK_CGM_DAP_SEL(mcu_clk_para.dap_freq.lvl);  //iwhale2:  5:153.6M
	REG32(REG_AON_CLK_CGM_DAP_CFG) = apb_cfg;
#endif
	delay();
	return 0;
}

static uint32 ClkConfig(uint32 arm_clk,uint32 arm_big_clk)
{
	AxiClkConfig();
	DapClkConfig();
	ApbClkConfig();
	NocClkConfig();
	Analog_IO_ClkConfig();
	CP_MdarClkConfig();
	CP_AonClkConfig();
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

	ANA_REG_OR(ANA_REG_GLB_LDO_SD_PD_REG,BIT_LDO_SDCORE_PD);
	ANA_REG_OR(ANA_REG_GLB_LDO_SDIO_PD_REG,BIT_LDO_SDIO_PD);

	/*
	 * fix DCDC GPU to DCM_PWM mode
	 * */
	ANA_REG_OR(ANA_REG_GLB_DCDC_GPU_REG0, BIT_DCDC_GPU_PFM);
	ANA_REG_BIC(ANA_REG_GLB_DCDC_GPU_REG0, BIT_DCDC_GPU_DCM);
#endif
	return 0;
}

static uint32 MCU_Init()
{
	power_config();
	/*enable and calibrate rco100m */
	Rco100_config();
#if defined(CONFIG_CLK_PARA)
	if (ClkConfig(NULL,NULL))
#else
		if (ClkConfig(CLK_800M,CLK_1500M))
#endif
			/* clkconfig failed*/
			while(1);
	return 0;
}

static uint32 Chip_Sleep_Ctrl()
{
#if defined(CONFIG_DDR_DOUBLE_PUB)
#else
	CHIP_REG_OR(REG_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_CTRL,
		BIT_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_PUB1_DEEP_SLEEP_MASK |
		BIT_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_CM4_DEEP_SLEEP_MASK |
		BIT_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_PLL_PD_MASK |
		0);

	CHIP_REG_OR(REG_COM_PMU_APB_PAD_OUT_XTL_EB_CTRL,
		BIT_COM_PMU_APB_PAD_OUT_XTL_EB_PUB1_DEEP_SLEEP_MASK |
		BIT_COM_PMU_APB_PAD_OUT_XTL_EB_PLL_PD_MASK |
		0);

	CHIP_REG_OR(REG_COM_PMU_APB_PAD_OUT_XTL_EB1_CTRL,
		BIT_COM_PMU_APB_PAD_OUT_XTL_EB1_PUB1_DEEP_SLEEP_MASK |
		BIT_COM_PMU_APB_PAD_OUT_XTL_EB1_PLL_PD_MASK |
		0);

	CHIP_REG_OR(REG_COM_PMU_APB_PAD_OUT_XTL_EB2_CTRL,
		BIT_COM_PMU_APB_PAD_OUT_XTL_EB2_PUB1_DEEP_SLEEP_MASK |
		BIT_COM_PMU_APB_PAD_OUT_XTL_EB2_PLL_PD_MASK |
		0);

	CHIP_REG_OR(REG_COM_PMU_APB_DCXO_LC_DEEP_SLEEP_CTRL,
		BIT_COM_PMU_APB_DCXO_LC_DEEP_SLEEP_PUB1_DEEP_SLEEP_MASK |
		BIT_COM_PMU_APB_DCXO_LC_DEEP_SLEEP_PLL_PD_MASK |
		0);
#endif
	CHIP_REG_AND(REG_COM_PMU_APB_DCXO_LC_DEEP_SLEEP_CTRL,
		~(BIT_COM_PMU_APB_DCXO_LC_DEEP_SLEEP_CAM_EB_MASK |
		0));
	return 0;
}

static void Reset_lpll0_config(uint32 clk)
{
	uint32 clk_cfg1_reg, clk_cfg2_reg, clk_cfg1, clk_cfg2;
	uint32 nint, kint;
	struct iwhale_ibias_table *itable;

	clk_cfg1_reg = REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_3;
	clk_cfg2_reg = REG_ANLG_PHY_G2_ANALOG_BB_TOP_MODU_CTRL_3;
	clk = clk /100000;

	clk_cfg1 = REG32(clk_cfg1_reg);
	clk_cfg2 = REG32(clk_cfg2_reg);
	itable = iwhale2_adjustable_pll1_table;

	nint = BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_NINT(NINT(clk,LPLL_REFIN));
	kint = BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_KINT(KINT(clk,LPLL_REFIN));
	clk_cfg2 &= ~(BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_NINT(~0x0) | BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_KINT(~0x0));
	clk_cfg2 |= nint | kint;
	/* set ibias */
	clk_cfg1 &= ~BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_IBIAS(3);
	for (; itable->rate <= IWHALE_PLL_MAX_RATE; itable++) {
		if (clk*1000000 <= itable->rate) {
			clk_cfg1 |= BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_IBIAS(itable->ibias);
			break;
		}
	}
	REG32(clk_cfg1_reg) = clk_cfg1;
	REG32(clk_cfg2_reg) = clk_cfg2;
	delay();
	delay();
	delay();
	delay();
	delay();
	while(!(REG32(clk_cfg1_reg) & BIT_ANLG_PHY_G2_ANALOG_BB_TOP_LPLL0_LOCK_DONE));
}

void Reset_cppll_config(uint32 clk)
{
	uint32 clk_cfg1_reg, clk_cfg2_reg, clk_cfg1, clk_cfg2;
	uint32 nint, kint;
	struct iwhale_ibias_table *itable;

	clk_cfg1_reg = REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_6;
	clk_cfg2_reg = REG_ANLG_PHY_G2_ANALOG_BB_TOP_MODU_CTRL_6;
	clk = clk / 1000000;
	itable = iwhale2_adjustable_pll2_table;
	clk_cfg1 = REG32(clk_cfg1_reg);
	clk_cfg2 = REG32(clk_cfg2_reg);

	nint = BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_NINT(NINT(clk,REFIN));
	kint = BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_KINT(0x1faa4c);//configure cppll 786.432M
	clk_cfg2 &= ~(BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_NINT(~0x0) | BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_KINT(~0x0));
	clk_cfg2 |= nint | kint;
	/* set ibias */
	clk_cfg1 &= ~BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_IBIAS(3);
	for (; itable->rate <= IWHALE_PLL_MAX_RATE; itable++) {
		if (clk*1000000 <= itable->rate) {
			clk_cfg1 |= BIT_ANLG_PHY_G2_ANALOG_BB_TOP_CPPLL_IBIAS(itable->ibias);
			break;
		}
	}
	REG32(clk_cfg1_reg) = clk_cfg1;
	REG32(clk_cfg2_reg) = clk_cfg2;
	delay();
	delay();
	delay();
	delay();
	delay();
}

void SwitchPll(void)
{
	uint32 clk_cfg;
	/*modify ap_apb_bus:26M ap_axi:26m*/
	REG32(REG_AP_CLK_CGM_AP_APB_CFG) &= ~BIT_AP_CLK_CGM_AP_APB_SEL(~0x0);
	REG32(REG_AP_CLK_CGM_AP_AXI_CFG) &= ~BIT_AP_CLK_CGM_AP_AXI_SEL(~0x0);
	if(0 == get_chip_version()) {

		/* Rpll0_reserved, register control*/
		REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_REG_SEL_CFG_0) |= BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_RESERVED | BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_REF_SEL;
		/* Rpll0 sel tune 26m*/
		REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_0) &= ~BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_REF_SEL(~0X0);
		REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_0) |= BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_REF_SEL(1);
		udelay(200);
		/* Rpll0 bypass */
		REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK26M_CTL_0) |= BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_26M_SEL;
	}else {
		/* Rpll0 not bypass */
		REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK26M_CTL_0) &= ~BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_26M_SEL;
		REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_REG_SEL_CFG_0) |= BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_DIV1_EN;
		REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_DIV_CTRL_0) |= BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_DIV1_EN;
		REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_0) |= BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_IBIAS(~0x0);
	}

	delay();
	delay();

	/* TWPLL switch */
	clk_cfg = REG32(REG_PMU_APB_TWPLL_REL_CFG);
	clk_cfg &= ~BIT_PMU_APB_TWPLL_REF_SEL(7);
	clk_cfg |= BIT_PMU_APB_TWPLL_REF_SEL(2);//sel rpll0
	REG32(REG_PMU_APB_TWPLL_REL_CFG) = clk_cfg;

	/* LPLL0 switch */
	clk_cfg = REG32(REG_PMU_APB_LPLL0_REL_CFG);
	clk_cfg &= ~BIT_PMU_APB_LPLL0_REF_SEL(7);
	clk_cfg |= BIT_PMU_APB_LPLL0_REF_SEL(2);//sel rpll0
	REG32(REG_PMU_APB_LPLL0_REL_CFG) = clk_cfg;

	/* LPLL1 switch */
	clk_cfg = REG32(REG_PMU_APB_LPLL1_REL_CFG);
	clk_cfg &= ~BIT_PMU_APB_LPLL1_REF_SEL(7);
	clk_cfg |= BIT_PMU_APB_LPLL1_REF_SEL(2);//sel rpll0
	REG32(REG_PMU_APB_LPLL1_REL_CFG) = clk_cfg;

	if(0 == get_chip_version()) {
		/* m_lvds switch */
		clk_cfg = REG32(REG_COM_PMU_APB_LVDS_RF_PLL_REF_SEL);
		clk_cfg &= ~(BIT_COM_PMU_APB_LVDS_RF_PLL0_REF_SEL(~0x0) | BIT_COM_PMU_APB_LVDS_RF_PLL1_REF_SEL(~0x0));
		clk_cfg |= BIT_COM_PMU_APB_LVDS_RF_PLL0_REF_SEL(2) | BIT_COM_PMU_APB_LVDS_RF_PLL1_REF_SEL(2);//sel rpll0
		REG32(REG_COM_PMU_APB_LVDS_RF_PLL_REF_SEL) = clk_cfg;
	}
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

	if(0 == get_chip_version())
	/* lpll0 div from lpll1 div means ltepcc & ltescc source from lpll1*/
	REG32(REG_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG) |= BIT_PRE_DIV_CLK_GEN_CGM_LPLL0_307M2_WTLCP_SEL |
															BIT_PRE_DIV_CLK_GEN_CGM_LPLL0_245M76_WTLCP_SEL |
															BIT_PRE_DIV_CLK_GEN_CGM_LPLL0_204M8_WTLCP_SEL |
															BIT_PRE_DIV_CLK_GEN_CGM_LPLL0_153M6_WTLCP_SEL |
															BIT_PRE_DIV_CLK_GEN_CGM_LPLL0_122M88_WTLCP_SEL |
															BIT_PRE_DIV_CLK_GEN_CGM_LPLL0_102M4_WTLCP_SEL |
															BIT_PRE_DIV_CLK_GEN_CGM_LPLL0_61M44_WTLCP_SEL;
	else {
		REG32(REG_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL0_CFG) &= ~BIT_PRE_DIV_CLK_GEN_CGM_LPLL1_307M2_WTLCP_SEL;
		REG32(REG_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL1_CFG) &= ~(BIT_PRE_DIV_CLK_GEN_CGM_LPLL1_245M76_WTLCP_SEL |
															BIT_PRE_DIV_CLK_GEN_CGM_LPLL1_204M8_WTLCP_SEL |
															BIT_PRE_DIV_CLK_GEN_CGM_LPLL1_153M6_WTLCP_SEL |
															BIT_PRE_DIV_CLK_GEN_CGM_LPLL1_122M88_WTLCP_SEL |
															BIT_PRE_DIV_CLK_GEN_CGM_LPLL1_102M4_WTLCP_SEL |
															BIT_PRE_DIV_CLK_GEN_CGM_LPLL1_61M44_WTLCP_SEL);
		/* emmc sel cppll */
		REG32(REG_AON_APB_RES_REG0) |= (1 << 31);
	}
	/* change agcp sel 25M from clk_xbuf,not from rpll1 26m*/
	REG32(REG_PRE_DIV_CLK_GEN_OUTPUT_CLOCK_MUX_SEL1_CFG) &= ~BIT_PRE_DIV_CLK_GEN_CGM_XTL_26M_GGE_AGCP_SEL(~0x0);

	/*
	 * xltbuf1,xtlbuf2 not use,xtl0 and xtlbuf0 related all subsys now,
	 * Noted, after rco100 done,will not related cm4.
	 */
	CHIP_REG_OR(REG_PMU_APB_XTL0_REL_CFG,
			BIT_PMU_APB_XTL0_AP_SYS_SEL |
			BIT_PMU_APB_XTL0_WTLCP_SYS_SEL |
			BIT_PMU_APB_XTL0_PUBCP_SYS_SEL |
			BIT_PMU_APB_XTL0_AGCP_SYS_SEL |
			BIT_PMU_APB_XTL0_PUB0_SYS_SEL |
			BIT_PMU_APB_XTL0_PUB1_SYS_SEL |
			BIT_PMU_APB_XTL0_CAM_PD_SEL |
			0
			);
	CHIP_REG_AND(REG_PMU_APB_XTL0_REL_CFG,
			~BIT_PMU_APB_XTL0_CM4_SYS_SEL);

	CHIP_REG_OR(REG_PMU_APB_XTLBUF0_REL_CFG,
			BIT_PMU_APB_XTLBUF0_AP_SYS_SEL |
			BIT_PMU_APB_XTLBUF0_WTLCP_SYS_SEL |
			BIT_PMU_APB_XTLBUF0_PUBCP_SYS_SEL |
			BIT_PMU_APB_XTLBUF0_AGCP_SYS_SEL |
			BIT_PMU_APB_XTLBUF0_PUB0_SYS_SEL |
			BIT_PMU_APB_XTLBUF0_PUB1_SYS_SEL |
			BIT_PMU_APB_XTLBUF0_CAM_PD_SEL |
			0
			);

	CHIP_REG_AND(REG_PMU_APB_XTLBUF0_REL_CFG,
			~BIT_PMU_APB_XTLBUF0_CM4_SYS_SEL);
#if defined(CONFIG_DDR_DOUBLE_PUB)
	CHIP_REG_OR(REG_PMU_APB_XTL0_REL_CFG,
			BIT_PMU_APB_XTL0_PUB1_SYS_SEL |
			0);

	CHIP_REG_OR(REG_PMU_APB_XTLBUF0_REL_CFG,
			BIT_PMU_APB_XTLBUF0_PUB1_SYS_SEL |
			0);
#else
	CHIP_REG_AND(REG_PMU_APB_XTL0_REL_CFG,
			~(BIT_PMU_APB_XTL0_PUB1_SYS_SEL |
			0));

	CHIP_REG_AND(REG_PMU_APB_XTLBUF0_REL_CFG,
			~(BIT_PMU_APB_XTLBUF0_PUB1_SYS_SEL |
			0));
#endif

	if(0 == get_chip_version()) {
		CHIP_REG_OR(REG_PMU_APB_XTLBUF1_REL_CFG,
				(BIT_PMU_APB_XTLBUF1_AP_SYS_SEL |
				BIT_PMU_APB_XTLBUF1_WTLCP_SYS_SEL |
				BIT_PMU_APB_XTLBUF1_PUBCP_SYS_SEL |
				BIT_PMU_APB_XTLBUF1_AGCP_SYS_SEL |
				BIT_PMU_APB_XTLBUF1_PUB0_SYS_SEL |
				BIT_PMU_APB_XTLBUF1_CAM_PD_SEL |
				0)
			);

		CHIP_REG_AND(REG_PMU_APB_XTLBUF1_REL_CFG,
				~(BIT_PMU_APB_XTLBUF1_PUB1_SYS_SEL |
				BIT_PMU_APB_XTLBUF1_CM4_SYS_SEL |
				0)
			);
	}else
		CHIP_REG_AND(REG_PMU_APB_XTLBUF1_REL_CFG,
			~(BIT_PMU_APB_XTLBUF1_AP_SYS_SEL |
				BIT_PMU_APB_XTLBUF1_WTLCP_SYS_SEL |
				BIT_PMU_APB_XTLBUF1_PUBCP_SYS_SEL |
				BIT_PMU_APB_XTLBUF1_AGCP_SYS_SEL |
				BIT_PMU_APB_XTLBUF1_CM4_SYS_SEL |
				BIT_PMU_APB_XTLBUF1_PUB0_SYS_SEL |
				BIT_PMU_APB_XTLBUF1_PUB1_SYS_SEL |
				BIT_PMU_APB_XTLBUF1_CAM_PD_SEL |
				0)
			);

	CHIP_REG_AND(REG_PMU_APB_XTLBUF2_REL_CFG,
			~(BIT_PMU_APB_XTLBUF2_AP_SYS_SEL |
				BIT_PMU_APB_XTLBUF2_WTLCP_SYS_SEL |
				BIT_PMU_APB_XTLBUF2_PUBCP_SYS_SEL |
				BIT_PMU_APB_XTLBUF2_AGCP_SYS_SEL |
				BIT_PMU_APB_XTLBUF2_CM4_SYS_SEL |
				BIT_PMU_APB_XTLBUF2_PUB0_SYS_SEL |
				BIT_PMU_APB_XTLBUF2_PUB1_SYS_SEL |
				BIT_PMU_APB_XTLBUF2_CAM_PD_SEL |
				0)
			);

	/*
	 * MPLL0,MPLL1,MPLL2 asic default related to ap,
	 * no need to configure.
	 * Noted, after rc0100 done,rpll0 will not related to cm4.
	 * rpll1 not use.
	 */
	CHIP_REG_OR(REG_PMU_APB_RPLL0_REL_CFG,
			BIT_PMU_APB_RPLL0_AP_SYS_SEL |
			BIT_PMU_APB_RPLL0_WTLCP_SYS_SEL |
			BIT_PMU_APB_RPLL0_PUBCP_SYS_SEL |
			BIT_PMU_APB_RPLL0_AGCP_SYS_SEL |
			BIT_PMU_APB_RPLL0_PUB0_SYS_SEL |
			BIT_PMU_APB_RPLL0_CAM_PD_SEL |
			0
			);

	if(1 == get_chip_version()) {
		CHIP_REG_OR(REG_ANLG_PHY_G2_ANALOG_BB_TOP_REG_SEL_CFG_0,
				BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_DIV1_EN |
				BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_26M_DIV |
				BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_RESERVED |
				BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_BB_TOP_RPLL0_IBIAS);
		udelay(200);
		udelay(200);
	}

	CHIP_REG_AND(REG_ANLG_PHY_G2_ANALOG_BB_TOP_PWR_CTRL_0,
			~BIT_ANLG_PHY_G2_ANALOG_BB_TOP_RPLL0_PD);

	CHIP_REG_AND(REG_PMU_APB_RPLL0_REL_CFG,
			~(BIT_PMU_APB_RPLL0_PUB1_SYS_SEL |
				BIT_PMU_APB_RPLL0_CM4_SYS_SEL |
				0)
			);

	CHIP_REG_AND(REG_PMU_APB_RPLL1_REL_CFG,
			~(BIT_PMU_APB_RPLL1_AP_SYS_SEL |
				BIT_PMU_APB_RPLL1_WTLCP_SYS_SEL |
				BIT_PMU_APB_RPLL1_PUBCP_SYS_SEL |
				BIT_PMU_APB_RPLL1_AGCP_SYS_SEL |
				BIT_PMU_APB_RPLL1_CM4_SYS_SEL |
				BIT_PMU_APB_RPLL1_PUB0_SYS_SEL |
				BIT_PMU_APB_RPLL1_PUB1_SYS_SEL |
				BIT_PMU_APB_RPLL1_CAM_PD_SEL |
				0)
			);

	CHIP_REG_OR(REG_PMU_APB_TWPLL_REL_CFG,
			BIT_PMU_APB_TWPLL_AP_SYS_SEL |
			BIT_PMU_APB_TWPLL_WTLCP_SYS_SEL |
			BIT_PMU_APB_TWPLL_PUBCP_SYS_SEL |
			BIT_PMU_APB_TWPLL_AGCP_SYS_SEL |
			BIT_PMU_APB_TWPLL_PUB0_SYS_SEL |
			BIT_PMU_APB_TWPLL_CAM_PD_SEL |
			0
			);

	CHIP_REG_AND(REG_PMU_APB_TWPLL_REL_CFG,
			~(BIT_PMU_APB_TWPLL_PUB1_SYS_SEL |
				BIT_PMU_APB_TWPLL_CM4_SYS_SEL |
				0)
			);
	/*
	 * Noted,dpll1 related will change after DDR introducing MACRO.
	 */
	CHIP_REG_OR(REG_PMU_APB_DPLL0_REL_CFG,
			BIT_PMU_APB_DPLL0_AP_SYS_SEL |
			BIT_PMU_APB_DPLL0_WTLCP_SYS_SEL |
			BIT_PMU_APB_DPLL0_PUBCP_SYS_SEL |
			BIT_PMU_APB_DPLL0_AGCP_SYS_SEL |
			BIT_PMU_APB_DPLL0_PUB0_SYS_SEL |
			BIT_PMU_APB_DPLL0_CAM_PD_SEL |
			0
			);

	CHIP_REG_AND(REG_PMU_APB_DPLL0_REL_CFG,
			~(BIT_PMU_APB_DPLL0_CM4_SYS_SEL |
				BIT_PMU_APB_DPLL0_PUB1_SYS_SEL |
				0)
			);

#if defined(CONFIG_DDR_DOUBLE_PUB)
	CHIP_REG_OR(REG_PMU_APB_DPLL1_REL_CFG,
			BIT_PMU_APB_DPLL1_PUB1_SYS_SEL |
			0
			);

	CHIP_REG_AND(REG_PMU_APB_DPLL1_REL_CFG,
			~(BIT_PMU_APB_DPLL1_WTLCP_SYS_SEL |
				BIT_PMU_APB_DPLL1_AP_SYS_SEL |
				BIT_PMU_APB_DPLL1_PUBCP_SYS_SEL |
				BIT_PMU_APB_DPLL1_AGCP_SYS_SEL |
				BIT_PMU_APB_DPLL1_CM4_SYS_SEL |
				BIT_PMU_APB_DPLL1_PUB0_SYS_SEL |
				BIT_PMU_APB_DPLL1_CAM_PD_SEL |
				0)
			);
#else
	CHIP_REG_AND(REG_PMU_APB_DPLL1_REL_CFG,
			~(BIT_PMU_APB_DPLL1_WTLCP_SYS_SEL |
				BIT_PMU_APB_DPLL1_AP_SYS_SEL |
				BIT_PMU_APB_DPLL1_PUBCP_SYS_SEL |
				BIT_PMU_APB_DPLL1_AGCP_SYS_SEL |
				BIT_PMU_APB_DPLL1_CM4_SYS_SEL |
				BIT_PMU_APB_DPLL1_PUB0_SYS_SEL |
				BIT_PMU_APB_DPLL1_PUB1_SYS_SEL |
				BIT_PMU_APB_DPLL1_CAM_PD_SEL |
				0)
			);
#endif
	/*
	 * lpll0 only related to ap.
	 * lpll1 only related to wtlcp.
	 * cppll related nothing.
	 */
	CHIP_REG_OR(REG_PMU_APB_LPLL0_REL_CFG,
			BIT_PMU_APB_LPLL0_AP_SYS_SEL |
			BIT_PMU_APB_LPLL0_WTLCP_SYS_SEL |
			0
			);

	CHIP_REG_AND(REG_PMU_APB_LPLL0_REL_CFG,
			~(BIT_PMU_APB_LPLL0_PUBCP_SYS_SEL |
				BIT_PMU_APB_LPLL0_AGCP_SYS_SEL |
				BIT_PMU_APB_LPLL0_CM4_SYS_SEL |
				BIT_PMU_APB_LPLL0_PUB0_SYS_SEL |
				BIT_PMU_APB_LPLL0_PUB1_SYS_SEL |
				BIT_PMU_APB_LPLL0_CAM_PD_SEL |
				0)
			);

	if(get_chip_version())
		CHIP_REG_AND(REG_PMU_APB_LPLL1_REL_CFG, ~BIT_PMU_APB_LPLL1_WTLCP_SYS_SEL);
	else
		CHIP_REG_OR(REG_PMU_APB_LPLL1_REL_CFG, BIT_PMU_APB_LPLL1_WTLCP_SYS_SEL);

	CHIP_REG_AND(REG_PMU_APB_LPLL1_REL_CFG,
			~(BIT_PMU_APB_LPLL1_AP_SYS_SEL |
				BIT_PMU_APB_LPLL1_PUBCP_SYS_SEL |
				BIT_PMU_APB_LPLL1_AGCP_SYS_SEL |
				BIT_PMU_APB_LPLL1_CM4_SYS_SEL |
				BIT_PMU_APB_LPLL1_PUB0_SYS_SEL |
				BIT_PMU_APB_LPLL1_PUB1_SYS_SEL |
				BIT_PMU_APB_LPLL1_CAM_PD_SEL |
				0)
			);

	CHIP_REG_AND(REG_PMU_APB_CPPLL_REL_CFG,
			~(BIT_PMU_APB_CPPLL_AP_SYS_SEL |
				BIT_PMU_APB_CPPLL_WTLCP_SYS_SEL |
				BIT_PMU_APB_CPPLL_PUBCP_SYS_SEL |
				BIT_PMU_APB_CPPLL_AGCP_SYS_SEL |
				BIT_PMU_APB_CPPLL_CM4_SYS_SEL |
				BIT_PMU_APB_CPPLL_PUB0_SYS_SEL |
				BIT_PMU_APB_CPPLL_PUB1_SYS_SEL |
				BIT_PMU_APB_CPPLL_CAM_PD_SEL |
				0)
			);

	if(get_chip_version())
		CHIP_REG_OR(REG_PMU_APB_CPPLL_REL_CFG, BIT_PMU_APB_CPPLL_AP_SYS_SEL);
	/*
	 * RC ralated to all subsys now.
	 * related configuration may be change after rco10 done.
	 */
	CHIP_REG_OR(REG_PMU_APB_RC_REL_CFG,
			BIT_PMU_APB_RC_AP_SYS_SEL |
			BIT_PMU_APB_RC_WTLCP_SYS_SEL |
			BIT_PMU_APB_RC_PUBCP_SYS_SEL |
			BIT_PMU_APB_RC_AGCP_SYS_SEL |
			BIT_PMU_APB_RC_CM4_SYS_SEL |
			BIT_PMU_APB_RC_PUB0_SYS_SEL |
			BIT_PMU_APB_RC_CAM_PD_SEL |
			0
			);
#if defined(CONFIG_DDR_DOUBLE_PUB)
	CHIP_REG_OR(REG_PMU_APB_RC_REL_CFG,
			BIT_PMU_APB_RC_PUB1_SYS_SEL |
			0);
#else
	CHIP_REG_AND(REG_PMU_APB_RC_REL_CFG,
                        ~(BIT_PMU_APB_RC_PUB1_SYS_SEL |
                        0));
#endif
}

void ssc_setting(uint32_t ssc_eb, uint32_t ssc_width)
{
	if(1 ==  ssc_eb)
	{
		/*something to be done*/
	}
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
	timer_init();

#if defined(CONFIG_SOC_IWHALE2)
	/* init noc configuration */
	sprd_noc_init();
#endif
#ifndef CONFIG_FPGA
#if defined(CONFIG_SOC_IWHALE2)
	/* BaseIA perf config */
	dram_configure_bridge_perf();

	sci_adi_init();
	regulator_init();
	if(!get_chip_version())
		Reset_lpll0_config(1170000000);//iwhale2_A0 sovle emmc problem, div6 195M
	Reset_cppll_config(786432000);//suppy 12.288M for audio realtek
	REG32(REG_ANLG_PHY_G2_ANALOG_BB_TOP_CLK_CTRL_2) |= BIT_ANLG_PHY_G2_ANALOG_BB_TOP_TWPLL_IBIAS(3);
	pll_sel_config(0x0);
	SwitchPll();
	MCU_Init();
	Chip_Sleep_Ctrl();
	Sel_rco100_for_lp();
	/* new add interface for ssc enable and ssc width setting */
	ssc_setting(mcu_clk_para.ssc_enable.value,mcu_clk_para.ssc_width.value);

	/* emmc need use timer to delay*/
	CHIP_REG_OR(REG_AON_APB_APB_EB0, BIT_AON_APB_AP_SYST_EB);
	CHIP_REG_OR(REG_AON_APB_APB_RTC_EB, BIT_AON_APB_AP_SYST_RTC_EB);

	/* enable ap busmon*/
	CHIP_REG_OR(REG_AP_AHB_AHB_EB, BIT_AP_AHB_BUSMON0_EB |
				BIT_AP_AHB_BUSMON1_EB |
				BIT_AP_AHB_BUSMON2_EB |
				BIT_AP_AHB_BUSMON3_EB);

	/* switch jtag pin to dap */
	CHIP_REG_SET(REG_AON_APB_CP_ARM_JTAG_CTRL, BIT_AON_APB_CP_ARM_JTAG_PIN_SEL(0xF));

	#ifdef CONFIG_CLK_PARA
	sdram_init(mcu_clk_para.ddr_freq.value);
	#else
	sdram_init(DDR_FREQ);
	#endif
	/* some ddr have hollow memory regions, need to be protected by FW */
	sprd_fw_ddr_hollow_cfg();
#endif
#else
	sdram_init();
#endif
}

