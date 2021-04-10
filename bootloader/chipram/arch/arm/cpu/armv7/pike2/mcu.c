
/******************************************************************************
    David.Jia   2007.10.29      share_version_union

******************************************************************************/

#include <common.h>
#include <adi.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_chipram_env.h>
#include <timer.h>
#include <asm/arch/avoid_disturb_info.h>

#define string_log(x) dmc_print_str(x)

#define MPLL_REFIN 26
#define DPLL_REFIN 26
#define NINT(FREQ,REFIN)	(FREQ/REFIN)
#define KINT(FREQ,REFIN)	((FREQ-(FREQ/REFIN)*REFIN)*(BIT_AON_APB_MPLL_KINT(~0x0)+1)/REFIN)

#if defined(CONFIG_CLK_PARA)
#include <asm/arch/clk_para_config.h>
const MCU_CLK_PARA_T mcu_clk_para=
{
    .magic_header = MAGIC_HEADER,
    .version = CONFIG_PARA_VERSION,
	.clk_vol_unit_count = 11,
	.clk_list_unit_count = 4,

    .cpu_freq.name = "C*CORE", //clk_core
    .cpu_freq.value = CLK_CA7_CORE,

    .cpu_axi_freq.name = "C*CAXI",
    .cpu_axi_freq.value = CLK_CA7_AXI,

    .cpu_dbg_freq.name = "C*CDBG",
    .cpu_dbg_freq.value = CLK_CA7_DGB,

    .ddr_freq.name = "C*DDR",//clk_ddr
    .ddr_freq.value = CLK_DDR_FREQ,

    .ddr_debug_mode.name = "DDR_MODE",//ddr_mode
#ifdef DDR_MODE
    .ddr_debug_mode.value = DDR_MODE,
#endif

    .dcdc_core.name = "D*CORE",
#ifdef DCDC_CORE
    .dcdc_core.value = DCDC_CORE,
#endif

	.ldo_mem.name = "L*MEM",
#ifdef DCDC_MEM
	.ldo_mem.value = LDO_MEM,
#endif

	.dcdc_gen.name = "D*GEN",
#ifdef DCDC_GEN
	.dcdc_gen.value = DCDC_GEN,
#endif

	.debug_flags[0].name = "d_flag0",
	.debug_flags[1].name = "d_flag1",
	.debug_flags[2].name = "d_flag2",
	.debug_flags[3].name = "d_flag3",

    .ap_axi_freq.name = "C#AP_AXI",
    .ap_axi_freq.lvl_count = CLK_AP_AXI_LEVEL,
    .ap_axi_freq.lvl = (CLK_AP_AXI_LEVEL_ID - 1),
    .ap_axi_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
    .ap_axi_freq.clk_list = {26000000, 76800000, 128000000, 256000000, 266700000},

    .ap_ahb_freq.name = "C#AP_AHB",
    .ap_ahb_freq.lvl_count = CLK_AP_AHB_LEVEL,
    .ap_ahb_freq.lvl = (CLK_AP_AHB_LEVEL_ID - 1),
    .ap_ahb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
    .ap_ahb_freq.clk_list = {26000000, 76800000, 128000000, 192000000, 200000000},

    .ap_apb_freq.name = "C#AP_APB",
    .ap_apb_freq.lvl_count = CLK_AP_APB_LEVEL,
    .ap_apb_freq.lvl = CLK_AP_APB_LEVEL_ID,
    .ap_apb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
    .ap_apb_freq.clk_list = {26000000, 64000000, 96000000, 100000000, 128000000},

    .aon_apb_freq.name = "C#AON_APB",
    .aon_apb_freq.lvl_count = CLK_AON_APB_LEVEL,
    .aon_apb_freq.lvl = CLK_AON_APB_LEVEL_ID,
    .aon_apb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
    .aon_apb_freq.clk_list = {26000000, 100000000, 128000000},

    .magic_end = MAGIC_END
};

#endif

#define SPRD_PLL_MAX_RATE               (0xFFFFFFFFUL)

struct sprd_ibias_table {
	unsigned long rate;
	u8 ibias;
};

static struct sprd_ibias_table pll_ibias_table[] = {
	{
		.rate = 951000000UL,
		.ibias = 0x0,
	},
	{
		.rate = 1131000000UL,
		.ibias = 0x1,
	},
	{
		.rate = 1134000000UL,
		.ibias = 0x2,
	},
	{
		.rate = 1600000000UL,
		.ibias = 0x3,
	},
	{
		.rate = SPRD_PLL_MAX_RATE,
		.ibias = 0x3,
	},
};

static void delay()
{
    volatile uint32 i;
    for (i=0; i<0x100; i++);
}

void pll_sel_cfg(void)
{
    /* XTL0 is selected by all subsys */
    REG32(REG_PMU_APB_XTL0_REL_CFG) |=
		BIT_PMU_APB_XTL0_CM4_SEL |
		BIT_PMU_APB_XTL0_PUBCP_SEL |
		BIT_PMU_APB_XTL0_PUB_SEL |
		BIT_PMU_APB_XTL0_WCN_SEL |
		BIT_PMU_APB_XTL0_WTLCP_SEL |
		BIT_PMU_APB_XTL0_AP_SEL;

    /* XTLBUF0 is selected by all subsys */
    REG32(REG_PMU_APB_XTLBUF0_REL_CFG) |=
		BIT_PMU_APB_XTLBUF0_CM4_SEL |
		BIT_PMU_APB_XTLBUF0_PUBCP_SEL |
		BIT_PMU_APB_XTLBUF0_PUB_SEL |
		BIT_PMU_APB_XTLBUF0_WCN_SEL |
		BIT_PMU_APB_XTLBUF0_WTLCP_SEL |
		BIT_PMU_APB_XTLBUF0_AP_SEL;

    /* CPLL is a backup pll, not selected by any subsys now */
    REG32(REG_PMU_APB_CPLL_REL_CFG) |= BIT_PMU_APB_CPLL_AP_SEL;

    /* MPLL is selected by AP sys only, SW need do nothing */

    /* GPLL is dynamicaly selected with ap, but it also depends on whether GPU top needs  */
    REG32(REG_PMU_APB_GPLL_REL_CFG) |= BIT_PMU_APB_GPLL_AP_SEL;

    /* for wakeup DPLL quickly */
    REG32(REG_PMU_APB_DPLL_REL_CFG) |= BIT_PMU_APB_DPLL_PUB_SEL;
    REG32(REG_PMU_APB_DPLL_REL_CFG) &= ~BIT_PMU_APB_DPLL_AP_SEL;

    /* TWPLL is selected by all subsys */
    REG32(REG_PMU_APB_TWPLL_REL_CFG) |=
		BIT_PMU_APB_TWPLL_CM4_SEL |
		BIT_PMU_APB_TWPLL_PUBCP_SEL |
		BIT_PMU_APB_TWPLL_PUB_SEL |
		BIT_PMU_APB_TWPLL_WCN_SEL |
		BIT_PMU_APB_TWPLL_WTLCP_SEL |
		BIT_PMU_APB_TWPLL_AP_SEL;
}

static uint32 SetTwpllClk (uint32 clk)
{
	uint32 clk_cfg1_reg, clk_cfg2_reg, clk_cfg1, clk_cfg2;
	uint32 nint, kint;
	struct sprd_ibias_table *itable = pll_ibias_table;
	uint32 refin = MPLL_REFIN;

	clk = clk/1000000;

	clk_cfg1_reg = REG_AON_APB_TWPLL_CFG1;
	clk_cfg2_reg = REG_AON_APB_TWPLL_CFG2;

	clk_cfg1 = REG32(clk_cfg1_reg);
	clk_cfg1 |= (BIT_AON_APB_TWPLL_DIV_S | BIT_AON_APB_TWPLL_SDM_EN);

	/* calc kint/nint */
	nint = BIT_AON_APB_TWPLL_NINT(NINT(clk, refin));
	kint = 0x6b9948;
	clk_cfg2 = REG32(clk_cfg2_reg);
	clk_cfg2 &= ~(BIT_AON_APB_TWPLL_NINT(~0) |
		BIT_AON_APB_TWPLL_KINT(~0));
	clk_cfg2 |= (nint | kint);

	clk_cfg1 &= ~BIT_AON_APB_TWPLL_IBIAS(3);
	for (; itable->rate <= SPRD_PLL_MAX_RATE; itable++) {
		if (clk*1000000 <= itable->rate) {
			clk_cfg1 |= BIT_AON_APB_TWPLL_IBIAS(itable->ibias);
			break;
		}
	}

	REG32(clk_cfg1_reg) = clk_cfg1;
	REG32(clk_cfg2_reg) = clk_cfg2;

	udelay(200);

	return 0;
}

static uint32 SetMPllClk (uint32 clk)
{
	uint32 clk_cfg1_reg, clk_cfg2_reg, clk_cfg1, clk_cfg2;
	uint32 nint, kint;
	struct sprd_ibias_table *itable = pll_ibias_table;
	uint32 refin = MPLL_REFIN;

	clk = clk/1000000;

	clk_cfg1_reg = REG_AON_APB_MPLL_CFG1;
	clk_cfg2_reg = REG_AON_APB_MPLL_CFG2;

	clk_cfg1 = REG32(clk_cfg1_reg);
	clk_cfg1 |= (BIT_AON_APB_MPLL_DIV_S | BIT_AON_APB_MPLL_SDM_EN);

	/* calc kint/nint */
	nint = BIT_AON_APB_MPLL_NINT(NINT(clk, refin));
	kint = BIT_AON_APB_MPLL_KINT(KINT(clk, refin));
	clk_cfg2 = REG32(clk_cfg2_reg);
	clk_cfg2 &= ~(BIT_AON_APB_MPLL_NINT(~0) |
		BIT_AON_APB_MPLL_KINT(~0));
	clk_cfg2 |= (nint | kint);

	clk_cfg1 &= ~BIT_AON_APB_MPLL_IBIAS(3);
	for (; itable->rate <= SPRD_PLL_MAX_RATE; itable++) {
		if (clk*1000000 <= itable->rate) {
			clk_cfg1 |= BIT_AON_APB_MPLL_IBIAS(itable->ibias);
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

	return 0;
}

static uint32 SetGPllClk (uint32 clk)
{
	uint32 clk_cfg1_reg, clk_cfg2_reg, clk_cfg1, clk_cfg2;
	uint32 nint, kint;
	struct sprd_ibias_table *itable = pll_ibias_table;
	uint32 refin = MPLL_REFIN;

	clk = clk/1000000;

	clk_cfg1_reg = REG_AON_APB_GPLL_CFG1;
	clk_cfg2_reg = REG_AON_APB_GPLL_CFG2;

	clk_cfg1 = REG32(clk_cfg1_reg);
	clk_cfg1 |= (BIT_AON_APB_GPLL_DIV_S | BIT_AON_APB_GPLL_SDM_EN);

	/* calc kint/nint */
	nint = BIT_AON_APB_GPLL_NINT(NINT(clk, refin));
	kint = BIT_AON_APB_GPLL_KINT(KINT(clk, refin));
	clk_cfg2 = REG32(clk_cfg2_reg);
	clk_cfg2 &= ~(BIT_AON_APB_GPLL_NINT(~0) |
		BIT_AON_APB_GPLL_KINT(~0));
	clk_cfg2 |= (nint | kint);

	clk_cfg1 &= ~BIT_AON_APB_GPLL_IBIAS(3);
	for (; itable->rate <= SPRD_PLL_MAX_RATE; itable++) {
		if (clk*1000000 <= itable->rate) {
			clk_cfg1 |= BIT_AON_APB_GPLL_IBIAS(itable->ibias);
			break;
		}
	}

	REG32(clk_cfg1_reg) = clk_cfg1;
	REG32(clk_cfg2_reg) = clk_cfg2;

	udelay(200);

	return 0;
}

static uint32 SetCPllClk (uint32 clk)
{
	uint32 clk_cfg1_reg, clk_cfg2_reg, clk_cfg1, clk_cfg2;
	uint32 nint, kint;
	struct sprd_ibias_table *itable = pll_ibias_table;
	uint32 refin = MPLL_REFIN;

	clk = clk/1000000;

	clk_cfg1_reg = REG_AON_APB_CPLL_CFG1;
	clk_cfg2_reg = REG_AON_APB_CPLL_CFG2;

	clk_cfg1 = REG32(clk_cfg1_reg);
	clk_cfg1 |= (BIT_AON_APB_CPLL_DIV_S | BIT_AON_APB_CPLL_SDM_EN);

	/* calc kint/nint */
	nint = BIT_AON_APB_CPLL_NINT(NINT(clk, refin));
	kint = BIT_AON_APB_CPLL_KINT(KINT(clk, refin));
	clk_cfg2 = REG32(clk_cfg2_reg);
	clk_cfg2 &= ~(BIT_AON_APB_CPLL_NINT(~0) |
		BIT_AON_APB_CPLL_KINT(~0));
	clk_cfg2 |= (nint | kint);

	clk_cfg1 &= ~BIT_AON_APB_CPLL_IBIAS(3);
	for (; itable->rate <= SPRD_PLL_MAX_RATE; itable++) {
		if (clk*1000000 <= itable->rate) {
			clk_cfg1 |= BIT_AON_APB_CPLL_IBIAS(itable->ibias);
			break;
		}
	}

	REG32(clk_cfg1_reg) = clk_cfg1;
	REG32(clk_cfg2_reg) = clk_cfg2;

	udelay(200);

	return 0;
}

static uint32 AhbClkConfig()
{
	uint32 clk_cfg;

	clk_cfg = REG32(REG_AP_CLK_AP_AHB_CFG);
	clk_cfg &= ~BIT_AP_CLK_AP_AHB_CFG_AP_AHB_SEL(~0);
	clk_cfg |= mcu_clk_para.ap_ahb_freq.lvl;
	REG32(REG_AP_CLK_AP_AHB_CFG) = clk_cfg;

	delay();
	return 0;
}

static uint32 ApbClkConfig()
{
	uint32 clk_cfg;

	clk_cfg = REG32(REG_AON_CLK_AON_APB_CFG);
	clk_cfg &= ~BIT_AON_CLK_AON_APB_CFG_AON_APB_SEL(~0);
	clk_cfg |= mcu_clk_para.aon_apb_freq.lvl;
	REG32(REG_AON_CLK_AON_APB_CFG) = clk_cfg;
	delay();

	clk_cfg = REG32(REG_AP_CLK_AP_APB_CFG);
	clk_cfg &= ~BIT_AP_CLK_AP_APB_CFG_AP_APB_SEL(~0);
	clk_cfg |= mcu_clk_para.ap_apb_freq.lvl;
	REG32(REG_AP_CLK_AP_APB_CFG) = clk_cfg;

        delay();
	return 0;
}

static uint32 Analog_APB_ClkConfig()
{
	uint32 clk_cfg;

	clk_cfg = REG32(REG_AON_CLK_ANALOG_APB_CFG);
	clk_cfg &= ~BIT_AON_CLK_ANALOG_APB_CFG_ANALOG_APB_SEL(~0);
	clk_cfg |= 2;
	REG32(REG_AON_CLK_ANALOG_APB_CFG) = clk_cfg;

	delay();
	return 0;
}

static uint32 IO_APB_ClkConfig()
{
	uint32 clk_cfg;

	clk_cfg = REG32(REG_AON_CLK_IO_APB_CFG);
	clk_cfg &= ~BIT_AON_CLK_IO_APB_CFG_IO_APB_SEL(~0);
	clk_cfg |= 2;
	REG32(REG_AON_CLK_IO_APB_CFG) = clk_cfg;

	delay();
	return 0;
}

/* ap axi*/
static uint32 ApAxiClkConfig(uint32 arm_clk)
{
	uint32 clk_cfg;

	clk_cfg = REG32(REG_AP_CLK_AP_AXI_CFG);
	clk_cfg &= ~BIT_AP_CLK_AP_AXI_CFG_AP_AXI_SEL(~0);
	clk_cfg |= mcu_clk_para.ap_axi_freq.lvl;
	REG32(REG_AP_CLK_AP_AXI_CFG) = clk_cfg;

	delay();
	return 0;
}

static uint32 DbgClkConfig(uint32 arm_clk)
{
#if 0
	uint32 clk_cfg;

	clk_cfg = REG32(REG_AON_CLK_CA7_DAP_CFG);
	clk_cfg &= ~BIT_AON_CLK_CA7_DAP_CFG_CA7_DAP_SEL(~0);
	clk_cfg |= 4;
	REG32(REG_AON_CLK_CA7_DAP_CFG) = clk_cfg;

	delay();
#endif
	return 0;
}

static uint32 McuClkConfig(uint32 arm_clk)
{
    uint32 clk_cfg;

    SetMPllClk(arm_clk);

    REG32(REG_AP_AHB_CA7_CKG_SEL_CFG) = 6;
    delay();


    clk_cfg = REG32(REG_AP_AHB_CA7_CKG_DIV_CFG);
    clk_cfg &= ~(BIT_AP_AHB_CA7_AXI_CKG_DIV(~0) |
		 BIT_AP_AHB_CA7_DBG_CKG_DIV(~0));

    if ((mcu_clk_para.cpu_freq.value) % (mcu_clk_para.cpu_axi_freq.value))
        clk_cfg |= BIT_AP_AHB_CA7_AXI_CKG_DIV((mcu_clk_para.cpu_freq.value)/(mcu_clk_para.cpu_axi_freq.value));
    else
        clk_cfg |= BIT_AP_AHB_CA7_AXI_CKG_DIV((mcu_clk_para.cpu_freq.value)/(mcu_clk_para.cpu_axi_freq.value) - 1);

    if ((mcu_clk_para.cpu_freq.value) % (mcu_clk_para.cpu_dbg_freq.value))
        clk_cfg |= BIT_AP_AHB_CA7_DBG_CKG_DIV((mcu_clk_para.cpu_freq.value)/(mcu_clk_para.cpu_dbg_freq.value));
    else
        clk_cfg |= BIT_AP_AHB_CA7_DBG_CKG_DIV((mcu_clk_para.cpu_freq.value)/(mcu_clk_para.cpu_dbg_freq.value) - 1);

    REG32(REG_AP_AHB_CA7_CKG_DIV_CFG) = clk_cfg;

    return 0;
}

static uint32 ArmCoreConfig(uint32 arm_clk)
{

#ifdef DCDC_CORE
    regulator_set_voltage("vddcore",mcu_clk_para.dcdc_core.value);
#endif

#ifdef DCDC_GEN
    regulator_set_voltage("vddgen",mcu_clk_para.dcdc_gen.value);
#endif

#ifdef LDO_MEM
    regulator_set_voltage("ldomem",mcu_clk_para.ldo_mem.value);
#endif

    delay();
    return 0;
}

static uint32 ClkConfig(uint32 arm_clk)
{
    ArmCoreConfig(arm_clk);
    ApAxiClkConfig(arm_clk);
    DbgClkConfig(arm_clk);
    Analog_APB_ClkConfig();
    IO_APB_ClkConfig();
    McuClkConfig(arm_clk);
    AhbClkConfig();
    ApbClkConfig();

    return 0;
}

uint32 MCU_Init()
{
    if (ClkConfig(mcu_clk_para.cpu_freq.value))
        while(1);

    return 0;
}

#ifdef CONFIG_SCX35LT8
#define REG_AON_CLK_EMC_CFG   (0x50820010)
#endif

#if defined(CONFIG_CLK_PARA)
void set_ddr_clk(uint32 ddr_clk)
{
}
#endif

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

void ctrl_for_lp(void)
{
	REG32(REG_PMU_APB_PMU_CLK_CFG) |= BIT_PMU_APB_AON_APB_PROTECT_EN;
	REG32(REG_PMU_APB_CGM_XTL_EN_SEL) &= ~BIT_PMU_APB_XTL_PD_REG;
}

void enable_26m_for_adc(void)
{
	/* refout2's mux is glitch free, it needs open tuned 26m to output untuned 26m */
	REG32(REG_PMU_APB_CGM_XTL_EN_SEL) |= BIT_PMU_APB_BBPLL1_PD_SEL;
	udelay(200);
	REG32(REG_AON_APB_CLK_EB0) |= BIT_AON_APB_CLK_26M_AUDIO_EB;
	REG32(REG_PMU_APB_CGM_XTL_EN_SEL) &= ~BIT_PMU_APB_BBPLL1_PD_SEL;
}

/*
 * This is a workaround solution for asic issue,performance busmonitor should be
 * enabled before ddr init,otherwise latency data will be error.
 */
void sprd_bm_init(void)
{
	#define PUB_BM_CFG		(0x4)
	#define BITS_BM_CFG_EB		(0x7f0000)
	#define BIT_BM_CHN_EN		(BIT(0))
	#define CHN_CFG			(0x0)

	CHIP_REG_SET((SPRD_PUB_PHYS + PUB_BM_CFG), BITS_BM_CFG_EB);
	CHIP_REG_SET((SPRD_AXIBM0_PHYS + CHN_CFG), BIT_BM_CHN_EN);
	CHIP_REG_SET((SPRD_AXIBM1_PHYS + CHN_CFG), BIT_BM_CHN_EN);
	CHIP_REG_SET((SPRD_AXIBM2_PHYS + CHN_CFG), BIT_BM_CHN_EN);
	CHIP_REG_SET((SPRD_AXIBM3_PHYS + CHN_CFG), BIT_BM_CHN_EN);
	CHIP_REG_SET((SPRD_AXIBM4_PHYS + CHN_CFG), BIT_BM_CHN_EN);
	CHIP_REG_SET((SPRD_AXIBM5_PHYS + CHN_CFG), BIT_BM_CHN_EN);
	CHIP_REG_SET((SPRD_AXIBM6_PHYS + CHN_CFG), BIT_BM_CHN_EN);
}

static void memory_repair_once()
{
	CHIP_REG_OR(REG_PMU_APB_BISR_FORCE_SEL,BIT_PMU_APB_PD_AON_MEM_BISR_FORCE_SEL);
}

void sprd_log(void)
{
	char hex_value[9] = {0};
	string_log("\r\nchip id : 0x");
	string_log(itoa_simple(REG32(REG_AON_APB_AON_CHIP_ID0), hex_value, 16));
	string_log(" 0x" );
	string_log(itoa_simple(REG32(REG_AON_APB_AON_CHIP_ID1), hex_value, 16));
	string_log(" 0x" );
	string_log(itoa_simple(REG32(REG_AON_APB_AON_VER_ID), hex_value, 16));

	string_log("\r\npmic id : 0x");
	string_log(itoa_simple(ANA_REG_GET(ANA_REG_GLB_CHIP_ID_LOW), hex_value, 16));
	string_log("  0x");
	string_log(itoa_simple(ANA_REG_GET(ANA_REG_GLB_CHIP_ID_HIGH), hex_value, 16));
}

extern void sdram_init(void);
void Chip_Init (void) /*lint !e765 "Chip_Init" is used by init.s entry.s*/
{
	uint32 value;

	CHIP_REG_OR(REG_AON_APB_APB_EB2, BIT_AON_APB_ANLG_EB | BIT_AON_APB_ANLG_APB_EB);
	memory_repair_once();
	timer_init();
	sprd_bm_init();
	SetTwpllClk(1529856000);
	sci_adi_init();
	regulator_init();
	pll_sel_cfg();
	MCU_Init();
	ctrl_for_lp();
	SetGPllClk(1066000000);
	SetCPllClk(1544000000);
	fill_iram_avoid_info();
	enable_26m_for_adc();
	sdram_init();
	sprd_log();
}

