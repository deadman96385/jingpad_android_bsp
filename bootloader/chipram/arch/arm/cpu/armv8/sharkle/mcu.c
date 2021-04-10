
/******************************************************************************
    David.Jia   2007.10.29      share_version_union

******************************************************************************/

#include <common.h>
#include <sci_types.h>
/* delete  chip_drv_common_io_h */
#include <adi.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_chipram_env.h>
#include <fdl_channel.h>
#include <timer.h>
#include <asm/arch/sprd_ptm.h>

#define string_log(x) dmc_print_str(x)

#define MPLL_REFIN 26
#define DPLL_REFIN 26
#define REFIN 26
#define LPLL_REFIN 260
#define NINT(FREQ,REFIN)	(FREQ/REFIN)
#define KINT(FREQ,REFIN)	((FREQ-(FREQ/REFIN)*REFIN)*(BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL_KINT(~0x0)+1)/REFIN)


#if defined(CONFIG_DUAL_DDR)
extern void noc_init(void);
#endif

#if defined(CONFIG_CLK_PARA)
#include <asm/arch/clk_para_config.h>
const MCU_CLK_PARA_T mcu_clk_para=
{
	.magic_header = MAGIC_HEADER,
	.version = CONFIG_PARA_VERSION,
	.clk_vol_unit_count = 14,
	.clk_list_unit_count = 3,

	.core0_freq.name = "C*CORE0",//clk_core0,1
	.core0_freq.value = CLK_CA53_CORE0,

	.ca53_axi_freq.name = "C*CAXI0",
	.ca53_axi_freq.value = CLK_CA53_AXI,

	.dbg0_freq.name = "C*DGB0",//clk_debug0,1
	.dbg0_freq.value = CLK_DGB0_FREQ,

	.ace0_freq.name = "C*ACE0",//ap nic400 matrix clock
	.ace0_freq.value = CLK_ACE0_FREQ,

	.atb0_freq.name = "C*ATB0",//clk_atb0
	.atb0_freq.value = CLK_ATB0_FREQ,

	.ddr_freq.name = "C*DDR",//clk_ddr
	.ddr_freq.value = CLK_DDR_FREQ,

	.ddr_debug_mode.name = "DDR_MODE",//ddr_mode
#ifdef DDR_MODE
	.ddr_debug_mode.value = DDR_MODE,
#endif

	.dcdc_arm.name = "D*ARM",//dcdc_arm0,1,core
#ifdef DCDC_ARM
	.dcdc_arm.value = DCDC_ARM,
#endif

    .dcdc_core.name = "D*CORE",
#ifdef DCDC_CORE
    .dcdc_core.value = DCDC_CORE,
#endif

	.dcdc_mem.name = "D*MEM",
#ifdef DCDC_MEM
	.dcdc_mem.value = DCDC_MEM,
#endif

	.dcdc_gen.name = "D*GEN",
#ifdef DCDC_GEN
	.dcdc_gen.value = DCDC_GEN,
#endif

	.debug_flags[0].name = "d_flag0",
	.debug_flags[1].name = "d_flag1",
	.debug_flags[2].name = "d_flag2",
	.debug_flags[3].name = "d_flag3",
#if defined(CONFIG_ADIE_SC2723) || defined(CONFIG_ADIE_SC2723S)
	.debug_flags[0].value = 0x3FFFFFF1, //0x3FFFFFFF
#endif

	.axi_freq.name = "C#AXI",//clk_axi
	.axi_freq.lvl_count = CLK_AXI_LEVEL,
	.axi_freq.lvl = CLK_AXI_LEVEL_ID,
	.axi_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,//all c# clk,the max level_count,now max=6
	.axi_freq.clk_list = {26000000,76800000,128000000,256000000},

	.ap_apb_freq.name = "C#AP_APB",//clk_apb
	.ap_apb_freq.lvl_count = CLK_APB_LEVEL,
	.ap_apb_freq.lvl = CLK_APB_LEVEL_ID,
	.ap_apb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.ap_apb_freq.clk_list = {26000000,64000000,96000000,128000000},

	.aon_apb_freq.name = "C#AONAPB",//clk_aon_apb
	.aon_apb_freq.lvl_count = CLK_AON_APB_LEVEL,
	.aon_apb_freq.lvl = CLK_AON_APB_LEVEL_ID,
	.aon_apb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.aon_apb_freq.clk_list = {26000000,76800000,96000000,128000000},

	.magic_end = MAGIC_END
};
#endif
static void delay()
{
    volatile uint32 i;
    for (i=0; i<0x100; i++);
}

#define SPRD_PLL_MAX_RATE               (0xFFFFFFFFUL)

struct sprd_ibias_table {
	unsigned long rate;
	u8 ibias;
};

static struct sprd_ibias_table pll_ibias_table[] = {
	{
		.rate = 936000000UL,
		.ibias = 0x0,
	},
	{
		.rate = 1248000000UL,
		.ibias = 0x1,
	},
	{
		.rate = 1600000000UL,
		.ibias = 0x2,
	},
	{
		.rate = SPRD_PLL_MAX_RATE,
		.ibias = 0x2,
	},
};

static uint32 ArmCoreConfig(uint32 arm_clk)
{

#ifdef CONFIG_ADIE_SC2721
#ifdef DCDC_ARM
    regulator_set_voltage("vddcpu",mcu_clk_para.dcdc_arm.value);
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
#endif

    delay();
    return 0;
}

static uint32 SetISPllClk(uint32 clk)
{
	uint32 clk_cfg1_reg, clk_cfg2_reg, clk_cfg1, clk_cfg2;
	uint32 nint, kint;
	uint32 refin = REFIN;

	clk = clk/1000000;

	clk_cfg1_reg = REG_ANLG_PHY_G1_ANALOG_PLL_TOP_IPPLL_CTRL0;
	clk_cfg2_reg = REG_ANLG_PHY_G1_ANALOG_PLL_TOP_IPPLL_CTRL1;

	/* calc kint/nint */
	clk_cfg1 = REG32(clk_cfg1_reg);
	clk_cfg1 |= (BIT_ANLG_PHY_G1_ANALOG_PLL_TOP_IPLL_SDM_EN |
		BIT_ANLG_PHY_G1_ANALOG_PLL_TOP_IPLL_DIV_S);

	nint = BIT_ANLG_PHY_G1_ANALOG_PLL_TOP_IPLL_NINT(NINT(clk, refin));
	kint = BIT_ANLG_PHY_G1_ANALOG_PLL_TOP_IPLL_KINT(KINT(clk, refin));
	clk_cfg2 = REG32(clk_cfg2_reg);
	clk_cfg2 &= ~(BIT_ANLG_PHY_G1_ANALOG_PLL_TOP_IPLL_NINT(~0) |
		BIT_ANLG_PHY_G1_ANALOG_PLL_TOP_IPLL_KINT(~0));
	clk_cfg2 |= (nint | kint);

	REG32(clk_cfg1_reg) = clk_cfg1;
	REG32(clk_cfg2_reg) = clk_cfg2;

	udelay(200);

	return 0;
}

static uint32 SetMPllClk(uint32 clk)
{
	uint32 clk_cfg1_reg, clk_cfg2_reg, clk_cfg1, clk_cfg2;
	uint32 nint, kint;
	struct sprd_ibias_table *itable = pll_ibias_table;
	uint32 refin = REFIN;

	clk = clk/1000000;

	clk_cfg1_reg = REG_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL_CTRL0;
	clk_cfg2_reg = REG_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL_CTRL1;

	/* calc kint/nint */
	clk_cfg1 = REG32(clk_cfg1_reg);
	clk_cfg1 |= (BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL_SDM_EN |
		BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL_DIV_S);

	nint = BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL_NINT(NINT(clk, refin));
	kint = BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL_KINT(KINT(clk, refin));
	clk_cfg2 = REG32(clk_cfg2_reg);
	clk_cfg2 &= ~(BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL_NINT(~0) |
		BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL_KINT(~0));
	clk_cfg2 |= (nint | kint);

	/* set ibias */
	clk_cfg1 &= ~BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL_IBIAS(3);
	for (; itable->rate <= SPRD_PLL_MAX_RATE; itable++) {
		if (clk*1000000 <= itable->rate) {
			clk_cfg1 |= BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL_IBIAS(itable->ibias);
			break;
		}
	}
	REG32(clk_cfg1_reg) = clk_cfg1;
	REG32(clk_cfg2_reg) = clk_cfg2;

	udelay(200);

	return 0;
}

static uint32 ApbClkConfig(void)
{
	uint32 clk_cfg;

	/* ap_apb to twpll_128m */
	clk_cfg = REG32(REG_AP_CLK_CORE_CGM_AP_APB_CFG);
	clk_cfg &= ~BIT_AP_CLK_CORE_CGM_AP_APB_SEL(~0);
	clk_cfg |= mcu_clk_para.ap_apb_freq.lvl;
	REG32(REG_AP_CLK_CORE_CGM_AP_APB_CFG) = clk_cfg;

	/* aon_apb to twpll_28m */
	clk_cfg = REG32(REG_AON_CLK_CORE_CGM_AON_APB_CFG);
	clk_cfg &= ~BIT_AON_CLK_CORE_CGM_AON_APB_SEL(~0);
	clk_cfg |= mcu_clk_para.aon_apb_freq.lvl;
	REG32(REG_AON_CLK_CORE_CGM_AON_APB_CFG) = clk_cfg;

	/* analog_io_apb to 48m */
	clk_cfg = REG32(REG_AON_CLK_CORE_CGM_ANALOG_IO_APB_CFG);
	clk_cfg |= BIT_AON_CLK_CORE_CGM_ANALOG_IO_APB_SEL;
	REG32(REG_AON_CLK_CORE_CGM_ANALOG_IO_APB_CFG) = clk_cfg;

	return 0;
}

static uint32 AxiClkConfig(void)
{
	uint32 clk_cfg;

	clk_cfg = REG32(REG_AON_CLK_CORE_CGM_AP_AXI_CFG);
	clk_cfg &= ~BIT_AON_CLK_CORE_CGM_AP_AXI_SEL(~0);
	clk_cfg |= mcu_clk_para.axi_freq.lvl;
	REG32(REG_AON_CLK_CORE_CGM_AP_AXI_CFG) = clk_cfg;

	delay();

	return 0;
}

static uint32 DbgClkConfig(uint32 arm_clk)
{
	uint32 clk_cfg,freq1,freq2,freq3;

	clk_cfg = REG32(REG_AP_AHB_CA53_CKG_DIV_CFG);
	clk_cfg &= ~(BIT_AP_AHB_CA53_ATB_DIV(~0) |
		BIT_AP_AHB_CA53_AXI_CKG_DIV(~0) |
		BIT_AP_AHB_CA53_DBG_CKG_DIV(~0));
	freq1 = mcu_clk_para.ca53_axi_freq.value; /* for cpu main mtx */
	freq2 = mcu_clk_para.dbg0_freq.value;
	freq3 = mcu_clk_para.atb0_freq.value;

	clk_cfg |= (arm_clk/freq1-1+ ((arm_clk%freq1)? 1:0)) << 8;
        clk_cfg |= (arm_clk/freq2-1+ ((arm_clk%freq2)? 1:0)) << 16;
        clk_cfg |= (arm_clk/freq3-1+ ((arm_clk%freq3)? 1:0));

	REG32(REG_AP_AHB_CA53_CKG_DIV_CFG) = clk_cfg;

	/* clk_dap to 153.6m */
	clk_cfg = REG32(REG_AON_CLK_CORE_CGM_CA53_DAP_CFG);
	clk_cfg &= ~(BIT_AON_CLK_CORE_CGM_CA53_DAP_SEL(~0));
	clk_cfg |= 3;
	REG32(REG_AON_CLK_CORE_CGM_CA53_DAP_CFG) = clk_cfg;

	return 0;
}

static uint32 McuClkConfig(uint32 arm_clk)
{
	SetMPllClk(arm_clk);

	/* cpu clk switch to mpll */
	REG32(REG_AP_AHB_CA53_CKG_SEL_CFG) = 3;
	delay();

	return 0;
}

static void MiscClkConfig(void)
{
        /* cgm_gsp_cfg 0x2150009c [1:0] : cgm_gsp_sel: clk_gsp_source:*/
        /*0:153.6m; 1:192m; 2:256m; 3:384m; default:2h'0*/
        REG32(REG_AP_CLK_CORE_CGM_GSP_CFG) &= ~BIT_AP_CLK_CORE_CGM_GSP_SEL(~0);
        REG32(REG_AP_CLK_CORE_CGM_GSP_CFG) |= BIT_AP_CLK_CORE_CGM_GSP_SEL(0x3);
}

static uint32 ClkConfig(uint32 arm_clk)
{
    ArmCoreConfig(arm_clk);
    AxiClkConfig();
    DbgClkConfig(arm_clk);
    McuClkConfig(arm_clk);
    ApbClkConfig();
    MiscClkConfig();
    return 0;
}

uint32 MCU_Init()
{
#if defined(CONFIG_CLK_PARA)
    if (ClkConfig(mcu_clk_para.core0_freq.value))
        while(1);
#endif

    return 0;
}

void chipram_env_set(u32 mode)
{
	chipram_env_t *p_env;
	p_env = (struct chipram_env *)CHIPRAM_ENV_ADDR;
	p_env->magic = CHIPRAM_ENV_MAGIC;
	p_env->mode = mode;
	p_env->dram_size = 0;
	if(BOOTLOADER_MODE_DOWNLOAD == mode)
		p_env->channel_sel = FDL_GetBootMode();
	else
		p_env->channel_sel = NULL;
}

void pll_ref_sel(void)
{
	/* not bypass RPLL */
	REG32(REG_ANLG_PHY_G6_ANALOG_BB_TOP_RPLL_CTRL0) |= BIT_ANLG_PHY_G6_ANALOG_BB_TOP_RPLL_26M_SEL;

	/* LTEPLL sel RPLL */
	REG32(REG_PMU_APB_LTEPLL_REL_CFG) &= ~BIT_PMU_APB_LTEPLL_REF_SEL(~0);
	REG32(REG_PMU_APB_LTEPLL_REL_CFG) |= BIT_PMU_APB_LTEPLL_REF_SEL(1);

	/* TWPLL sel RPLL */
	REG32(REG_PMU_APB_TWPLL_REL_CFG) &= ~BIT_PMU_APB_TWPLL_REF_SEL(~0);
	REG32(REG_PMU_APB_TWPLL_REL_CFG) |= BIT_PMU_APB_LTEPLL_REF_SEL(1);
}

void pll_sel_cfg(void)
{
	/* xtl sel */
	REG32(REG_PMU_APB_XTL0_REL_CFG) |= BIT_PMU_APB_XTL0_AP_SEL |
					BIT_PMU_APB_XTL0_WTLCP_SEL |
					BIT_PMU_APB_XTL0_PUBCP_SEL |
					BIT_PMU_APB_XTL0_WCN_SYS_SEL |
					BIT_PMU_APB_XTL0_PUB_SYS_SEL |
					BIT_PMU_APB_XTL0_SP_SYS_SEL;

	REG32(REG_PMU_APB_XTL1_REL_CFG) &= ~(BIT_PMU_APB_XTL1_AP_SEL |
					BIT_PMU_APB_XTL1_WTLCP_SEL |
					BIT_PMU_APB_XTL1_PUBCP_SEL |
					BIT_PMU_APB_XTL1_WCN_SYS_SEL |
					BIT_PMU_APB_XTL1_PUB_SYS_SEL |
					BIT_PMU_APB_XTL1_SP_SYS_SEL);

	REG32(REG_PMU_APB_XTLBUF0_REL_CFG) |= BIT_PMU_APB_XTLBUF0_AP_SEL |
					BIT_PMU_APB_XTLBUF0_WTLCP_SEL |
					BIT_PMU_APB_XTLBUF0_PUBCP_SEL |
					BIT_PMU_APB_XTLBUF0_WCN_SYS_SEL |
					BIT_PMU_APB_XTLBUF0_PUB_SYS_SEL |
					BIT_PMU_APB_XTLBUF0_SP_SYS_SEL;

	REG32(REG_PMU_APB_XTLBUF1_REL_CFG) &= ~(BIT_PMU_APB_XTLBUF1_AP_SEL |
					BIT_PMU_APB_XTLBUF1_WTLCP_SEL |
					BIT_PMU_APB_XTLBUF1_PUBCP_SEL |
					BIT_PMU_APB_XTLBUF1_WCN_SYS_SEL |
					BIT_PMU_APB_XTLBUF1_PUB_SYS_SEL |
					BIT_PMU_APB_XTLBUF1_SP_SYS_SEL);

	/* ISPPLL & GPLL & MPLL no need associate with AP */
	REG32(REG_PMU_APB_ISPPLL_REL_CFG) &= ~BIT_PMU_APB_ISPPLL_AP_SEL;
	REG32(REG_PMU_APB_GPLL_REL_CFG) &= ~BIT_PMU_APB_GPLL_AP_SEL;

	/* DPLL sel PUB is enough, keep as default value */

	/* LTEPLL sel */
	REG32(REG_PMU_APB_LTEPLL_REL_CFG) |= BIT_PMU_APB_LTEPLL_WTLCP_SEL;

	REG32(REG_PMU_APB_LTEPLL_REL_CFG) &= ~(BIT_PMU_APB_LTEPLL_AP_SEL |
					BIT_PMU_APB_LTEPLL_PUBCP_SEL |
					BIT_PMU_APB_LTEPLL_WCN_SYS_SEL |
					BIT_PMU_APB_LTEPLL_PUB_SYS_SEL |
					BIT_PMU_APB_LTEPLL_SP_SYS_SEL);

	/* TWPLL sel, because wcn may be use aon, so twpll musy be sel wcn sys */
	REG32(REG_PMU_APB_TWPLL_REL_CFG) |= BIT_PMU_APB_TWPLL_AP_SEL |
					BIT_PMU_APB_TWPLL_WTLCP_SEL |
					BIT_PMU_APB_TWPLL_WCN_SYS_SEL |
					BIT_PMU_APB_TWPLL_PUBCP_SEL |
					BIT_PMU_APB_TWPLL_PUB_SYS_SEL |
					BIT_PMU_APB_TWPLL_SP_SYS_SEL;

	REG32(REG_PMU_APB_RPLL_REL_CFG) |= BIT_PMU_APB_RPLL_AP_SEL |
					BIT_PMU_APB_RPLL_WTLCP_SEL |
					BIT_PMU_APB_RPLL_WCN_SYS_SEL |
					BIT_PMU_APB_RPLL_PUBCP_SEL |
					BIT_PMU_APB_RPLL_PUB_SYS_SEL |
					BIT_PMU_APB_RPLL_SP_SYS_SEL;

	delay();
}

void enable_auto_gate_for_lp(void)
{
	/* aon auto gate */
	REG32(REG_AON_APB_EMC_AUTO_GATE_EN) |= BIT_AON_APB_CA53_EMC_AUTO_GATE_EN |
					BIT_AON_APB_AP_EMC_AUTO_GATE_EN |
					BIT_AON_APB_WTLCP_EMC_AUTO_GATE_EN |
					BIT_AON_APB_PUBCP_EMC_AUTO_GATE_EN |
					BIT_AON_APB_AON_APB_PUB_AUTO_GATE_EN |
					BIT_AON_APB_AP_PUB_AUTO_GATE_EN |
					BIT_AON_APB_WTLCP_PUB_AUTO_GATE_EN |
					BIT_AON_APB_PUBCP_PUB_AUTO_GATE_EN;
	//REG32(REG_AON_APB_AUTO_GATE_CTRL0) |= BIT_AON_APB_CGM_AP_AXI_AUTO_GATE_SEL;

	/* ap ahb auto gate */
	REG32(REG_AP_AHB_AP_SYS_FORCE_SLEEP_CFG) |= BIT_AP_AHB_CGM_CLK_AP_AXI_AUTO_GATE_EN;
	REG32(REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG) |= BIT_AP_AHB_CA53_CORE_AUTO_GATE_EN |
					BIT_AP_AHB_CA53_DBG_AUTO_GATE_EN |
					BIT_AP_AHB_CA53_EMC_AUTO_GATE_EN |
					BIT_AP_AHB_AP_EMC_AUTO_GATE_EN |
					BIT_AP_AHB_AP_AHB_AUTO_GATE_EN |
					BIT_AP_AHB_GSP_AUTO_GATE_EN |
					BIT_AP_AHB_CA53_AXI_AUTO_GATE_EN |
					BIT_AP_AHB_CA53_ATB_AUTO_GATE_EN;
	REG32(REG_AP_AHB_S5_LPC) |= BIT_AP_AHB_CGM_MTX_S5_AUTO_GATE_EN;
	REG32(REG_AP_AHB_MAIN_LPC) |= BIT_AP_AHB_CGM_MATRIX_AUTO_GATE_EN;
	//REG32(REG_AP_AHB_S0_LPC) |= BIT_AP_AHB_CGM_MTX_S0_AUTO_GATE_EN;
	REG32(REG_AP_AHB_S1_LPC) |= BIT_AP_AHB_CGM_MTX_S1_AUTO_GATE_EN;
	REG32(REG_AP_AHB_S2_LPC) |= BIT_AP_AHB_CGM_MTX_S2_AUTO_GATE_EN;
	REG32(REG_AP_AHB_S3_LPC) |= BIT_AP_AHB_CGM_MTX_S3_AUTO_GATE_EN;
	REG32(REG_AP_AHB_S4_LPC) |= BIT_AP_AHB_CGM_MTX_S4_AUTO_GATE_EN;
	REG32(REG_AP_AHB_MERGE_S0_LPC) |= BIT_AP_AHB_CGM_MERGE_S0_AUTO_GATE_EN;
}

void disable_unused_clk_gate(void)
{
	REG32(REG_AON_APB_APB_EB1 + 0x2000) = BIT_AON_APB_AUX2_EB | BIT_AON_APB_PROBE_EB;
}

static void memory_repair_once()
{
	CHIP_REG_OR(REG_PMU_APB_BISR_FORCE_SEL,BIT_PMU_APB_PD_AON_MEM_BISR_FORCE_SEL);
}

void sprd_log(void)
{
	char hex_value[9] = {0};
	string_log("\r\nchip id : 0x");
	string_log(itoa_simple(__raw_readl(REG_AON_APB_AON_CHIP_ID0), hex_value, 16));
	string_log(" 0x" );
	string_log(itoa_simple(__raw_readl(REG_AON_APB_AON_CHIP_ID1), hex_value, 16));
	string_log(" 0x" );
	string_log(itoa_simple(__raw_readl(REG_AON_APB_AON_VER_ID), hex_value, 16));

	string_log("\r\npmic id : 0x");
	string_log(itoa_simple(ANA_REG_GET(ANA_REG_GLB_CHIP_ID_LOW), hex_value, 16));
	string_log("  0x");
	string_log(itoa_simple(ANA_REG_GET(ANA_REG_GLB_CHIP_ID_HIGH), hex_value, 16));
}

extern void sdram_init(void);
void Chip_Init (void) /*lint !e765 "Chip_Init" is used by init.s entry.s*/
{
	memory_repair_once();
	timer_init();
	sprd_ptm_init();
#if !defined(CONFIG_FPGA)
	CHIP_REG_OR(REG_AON_APB_APB_EB2, BIT_AON_APB_ANLG_EB | BIT_AON_APB_ANLG_APB_EB);
	REG32(REG_AP_CLK_CORE_CGM_AP_APB_CFG) &= ~BIT_AP_CLK_CORE_CGM_AP_APB_SEL(~0);
	REG32(REG_AON_CLK_CORE_CGM_AP_AXI_CFG) &= ~BIT_AON_CLK_CORE_CGM_AP_AXI_SEL(~0);
	/* power down 32M buffer for low power*/
	REG32(REG_ANLG_PHY_G6_ANALOG_BB_TOP_ANA_BB_PWR_CTRL + 0x1000) = 0x8;
	pll_ref_sel();
	sci_adi_init();
	regulator_init();
	pll_sel_cfg();
	MCU_Init();
	SetISPllClk(930000000);
	enable_auto_gate_for_lp();
	disable_unused_clk_gate();
	/* GSP & VSP has a common non-glitch matrix, improve it as soon as possible */
	REG32(REG_AP_CLK_CORE_CGM_GSP_CFG) |= BIT_AP_CLK_CORE_CGM_GSP_SEL(3);
	sdram_init();
	sprd_log();
#endif
}

