
/******************************************************************************
    David.Jia   2007.10.29      share_version_union

******************************************************************************/

#include <common.h>
#include <sci_types.h>
/* delete  chip_drv_common_io_h */
#include <adi.h>
#include <asm/arch/pinmap.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_chipram_env.h>
#include <fdl_channel.h>
#include <timer.h>

#define string_log(x) dmc_print_str(x)

#define MPLL_REFIN 26
#define DPLL_REFIN 26
#define REFIN 26
#define LPLL_REFIN 260
#define NINT(FREQ,REFIN)	(FREQ/REFIN)
#define KINT(FREQ,REFIN)	((FREQ-(FREQ/REFIN)*REFIN)*(BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL0_KINT(~0x0)+1)/REFIN)

#define local_enable_scr_el3_ea() \
	asm("mrs x1, scr_el3" : : : "memory");\
	asm("orr x1, x1, #(0x1 << 3)" : : : "memory");\
	asm("msr scr_el3, x1" : : : "memory")
#define local_async_enable()    asm("msr    daifclr, #4" : : : "memory")

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
	.clk_list_unit_count = 5,

	.core0_freq.name = "C*CORE0",
	.core0_freq.value = CLK_CA55_CORE0,

	.core4_freq.name = "C*CORE4",
	.core4_freq.value = CLK_CA55_CORE4,

	.clk_scu_freq.name = "C*SCU",
	.clk_scu_freq.value = CLK_SCU,

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

	.ldo_mem.name = "LDO_MEM",
#ifdef LDO_MEM
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

	.ap_atb_freq.name = "C#ATB",//clk_atb
	.ap_atb_freq.lvl_count = (CLK_ATB_LEVEL - 1),
	.ap_atb_freq.lvl = CLK_ATB_LEVEL_ID,
	.ap_atb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.ap_atb_freq.clk_list = {26000000, 384000000, 512000000}, // max is 512M, so delete mpll2 source

	.ap_periph_freq.name = "C#APPERI",//clk_periph
	.ap_periph_freq.lvl_count = CLK_PERIPH_LEVEL,
	.ap_periph_freq.lvl = CLK_PERIPH_LEVEL_ID,
	.ap_periph_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.ap_periph_freq.clk_list = {26000000,153600000,384000000,512000000},

	.ap_axi_freq.name = "C#APAXI",//clk_apb
	.ap_axi_freq.lvl_count = CLK_AP_AXI_LEVEL,
	.ap_axi_freq.lvl = CLK_AP_AXI_LEVEL_ID,
	.ap_axi_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.ap_axi_freq.clk_list = {26000000,76800000,128000000,256000000},

	.ap_apb_freq.name = "C#APAPB",//clk_apb
	.ap_apb_freq.lvl_count = CLK_AP_APB_LEVEL,
	.ap_apb_freq.lvl = CLK_AP_APB_LEVEL_ID,
	.ap_apb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.ap_apb_freq.clk_list = {26000000,64000000,96000000,128000000},

	.aon_apb_freq.name = "C#AONAPB",//clk_aon_apb
	.aon_apb_freq.lvl_count = CLK_AON_APB_LEVEL,
	.aon_apb_freq.lvl = CLK_AON_APB_LEVEL_ID,
	.aon_apb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.aon_apb_freq.clk_list = {4000000,25000000,26000000,96000000,100000000,128000000},

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

static struct sprd_ibias_table mpll_ibias_table[] = {
	{
		.rate = 1000000000UL,
		.ibias = 0x0,
	},
	{
		.rate = 1200000000UL,
		.ibias = 0x1,
	},
	{
		.rate = 1400000000UL,
		.ibias = 0x2,
	},
	{
		.rate = 1600000000,
		.ibias = 0x3,
	},
	{
		.rate = 1800000000,
		.ibias = 0x4,
	},
	{
		.rate = SPRD_PLL_MAX_RATE,
		.ibias = 0x5,
	},
};

static struct sprd_ibias_table isppll_ibias_table[] = {
	{
		.rate = 1000000000UL,
		.ibias = 0x0,
	},
	{
		.rate = 1200000000UL,
		.ibias = 0x1,
	},
	{
		.rate = 1400000000UL,
		.ibias = 0x2,
	},
	{
		.rate = 1600000000,
		.ibias = 0x3,
	},
	{
		.rate = SPRD_PLL_MAX_RATE,
		.ibias = 0x3,
	},
};

static pinmap_t pinmap[]={
	{REG_PIN_GPIO87,		BITS_PIN_AF(3)},
};
static void  ddr_pin_init(void)
{
	int i;

	for (i = 0; i < sizeof(pinmap)/sizeof(pinmap[0]); i++)
		REG32(SPRD_PIN_PHYS + pinmap[i].reg) = pinmap[i].val;
}

#if defined(CONFIG_VOL_PARA)

/* DCDC MEM output select:
 * [BONDOPT2 BONDOPT1]
 * 00: DDR2 application (1.2v)
 * 01: DDR3L application (1.35v)
 * 10: DDR3 application (1.5v)
 * 11: DDR1 application (1.8v)
 * DCDC MEM converter control bits with two bonding options as [bpt2 bpt1 xxx], list below:
 * 000: 1.2v
 * 001: 1.25v
 * 010: 1.35v
 * 011: 1.30v
 * 100: 1.50v
 * 101: 1.40v
 * 110: 1.80v
 * 111: 1.90v
 * DCDC MEM calibration control bits with small adjust step is 200/32mv.
 */
static int div_2(unsigned int dividend, unsigned int divisor, int *prem)
{
	if (divisor == 0)
		return 0;

	if (dividend < divisor)
		return 0;
	else if (dividend == divisor)
		return 1;

	unsigned int k, c, res = 0, rem = 0;

	while (dividend > divisor) {
		for (k = 0, c = divisor; dividend >= c; c <<= 1, k++) {
			if (dividend - c < divisor) {
				res += 1 << k;
				rem = dividend - c;
				break;
			}
		}
		if (dividend - c < divisor)
			break;

		res += 1 << (k - 1);
		dividend -= c >> 1;
	}

	if (prem)
		*prem = rem;

	return res;
}

static uint32 ArmCoreConfig()
{
#if defined(CONFIG_VOL_PARA)

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

#ifdef LDO_MEM
    regulator_set_voltage("ldomem",mcu_clk_para.ldo_mem.value);
#endif
#endif

#endif
    delay();
    return 0;
}

#endif

static int set_clk_mpll(uint32 clk, uint32 index)
{
	uint32 reg1, reg2, reg3, reg4, clk_cfg1, clk_cfg2;
	uint32 nint, kint;
	struct sprd_ibias_table *itable = mpll_ibias_table;
	uint32 refin = MPLL_REFIN;

	switch (index) {
	case 0:
		reg1 = REG_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL0_CTRL0;
		reg2 = REG_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL0_CTRL1;
		reg3 = REG_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL0_CTRL2;
		reg4 = REG_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL0_CTRL3;
		break;

	case 1:
		reg1 = REG_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL1_CTRL0;
		reg2 = REG_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL1_CTRL1;
		reg3 = REG_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL1_CTRL2;
		reg4 = REG_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL1_CTRL3;
		break;

	case 2:
		reg1 = REG_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL2_CTRL0;
		reg2 = REG_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL2_CTRL1;
		reg3 = REG_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL2_CTRL2;
		reg4 = REG_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL2_CTRL3;
		break;

	default:
		return -1;
	}

	if (clk < 800000000) {
		REG32(reg3) |= BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL2_POSTDIV;
		clk = clk * 2;
	}

	clk = clk/1000000;

	clk_cfg1 = REG32(reg1);
	clk_cfg1 |= BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL0_DIV_S | BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL0_SDM_EN;

	/* calc kint/nint */
	nint = BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL0_NINT(NINT(clk, refin));
	kint = BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL0_KINT(KINT(clk, refin));
	clk_cfg2 = REG32(reg2);
	clk_cfg2 = ~(BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL0_NINT(~0) |
		BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL0_KINT(~0));
	clk_cfg2 |= (nint | kint);

	clk_cfg1 &= ~BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL0_IBIAS(3);
	REG32(reg4) &= ~BIT(22);
	if ((clk > 1600) && (clk < 1800))
		REG32(reg4) |= BIT(22);
	else if ( clk >= 1800) {
		REG32(reg4) |= BIT(22);
		clk_cfg1 |= BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL0_IBIAS(1);
	} else
		for (; itable->rate <= SPRD_PLL_MAX_RATE; itable++) {
			if (clk*1000000 <= itable->rate) {
				clk_cfg1 |= BIT_ANLG_PHY_G2_ANALOG_PLL_TOP_IPLL_IBIAS(itable->ibias);
				break;
			}
		}

	REG32(reg1) = clk_cfg1;
	REG32(reg2) = clk_cfg2;

	udelay(200);

	return 0;
}

static uint32 clk_lit_mcu_config(uint32 arm_clk)
{
	set_clk_mpll(arm_clk, 0);

	if ( REG32(REG_AON_APB_AON_VER_ID) > 0 ) {
		REG32(REG_APCPU_TOP_CLK_CORE_CGM_CORE0_CFG) |= BIT_APCPU_TOP_CLK_CORE_CGM_CORE0_CFG_CGM_CORE0_SEL(2);
		REG32(REG_APCPU_TOP_CLK_CORE_CGM_CORE1_CFG) |= BIT_APCPU_TOP_CLK_CORE_CGM_CORE1_CFG_CGM_CORE1_SEL(2);
		REG32(REG_APCPU_TOP_CLK_CORE_CGM_CORE2_CFG) |= BIT_APCPU_TOP_CLK_CORE_CGM_CORE2_CFG_CGM_CORE2_SEL(2);
		REG32(REG_APCPU_TOP_CLK_CORE_CGM_CORE3_CFG) |= BIT_APCPU_TOP_CLK_CORE_CGM_CORE3_CFG_CGM_CORE3_SEL(2);
	} else {
		REG32(REG_APCPU_TOP_CLK_CORE_CGM_CORE0_CFG) |= BIT_APCPU_TOP_CLK_CORE_CGM_CORE0_CFG_CGM_CORE0_SEL(2);
		REG32(REG_APCPU_TOP_CLK_CORE_CGM_CORE1_CFG) |= BIT_APCPU_TOP_CLK_CORE_CGM_CORE1_CFG_CGM_CORE1_SEL(2);
		REG32(REG_APCPU_TOP_CLK_CORE_CGM_CORE2_CFG) |= BIT_APCPU_TOP_CLK_CORE_CGM_CORE2_CFG_CGM_CORE2_SEL(2);
		REG32(REG_APCPU_TOP_CLK_CORE_CGM_CORE3_CFG) |= BIT_APCPU_TOP_CLK_CORE_CGM_CORE3_CFG_CGM_CORE3_SEL(2);
	}

	return 0;
}

static uint32 clk_big_mcu_config(uint32 arm_clk)
{
	set_clk_mpll(arm_clk, 1);
	REG32(REG_APCPU_TOP_CLK_CORE_CGM_CORE4_CFG) |= BIT_APCPU_TOP_CLK_CORE_CGM_CORE4_CFG_CGM_CORE4_SEL(7);
	REG32(REG_APCPU_TOP_CLK_CORE_CGM_CORE5_CFG) |= BIT_APCPU_TOP_CLK_CORE_CGM_CORE5_CFG_CGM_CORE5_SEL(7);
	REG32(REG_APCPU_TOP_CLK_CORE_CGM_CORE6_CFG) |= BIT_APCPU_TOP_CLK_CORE_CGM_CORE6_CFG_CGM_CORE6_SEL(7);
	REG32(REG_APCPU_TOP_CLK_CORE_CGM_CORE7_CFG) |= BIT_APCPU_TOP_CLK_CORE_CGM_CORE7_CFG_CGM_CORE7_SEL(7);

	return 0;
}

static uint32 clk_scu_config(uint32 clk_rate)
{
	/* Set MPLL2 rate */
	set_clk_mpll(clk_rate, 2);

	/* Set clk_ace clk_axi_periph clk_axi_acp*/
	REG32(REG_APCPU_TOP_CLK_CORE_CGM_ACE_CFG) |= BIT_APCPU_TOP_CLK_CORE_CGM_ACE_CFG_CGM_ACE_DIV(1);
	REG32(REG_APCPU_TOP_CLK_CORE_CGM_AXI_PERIPH_CFG) |= BIT_APCPU_TOP_CLK_CORE_CGM_AXI_PERIPH_CFG_CGM_AXI_PERIPH_DIV(3);
	REG32(REG_APCPU_TOP_CLK_CORE_CGM_AXI_ACP_CFG) |= BIT_APCPU_TOP_CLK_CORE_CGM_AXI_ACP_CFG_CGM_AXI_ACP_DIV(7);

	/* Switch SCU clock source to MPLL2 */
	REG32(REG_APCPU_TOP_CLK_CORE_CGM_SCU_CFG) |= BIT_APCPU_TOP_CLK_CORE_CGM_SCU_CFG_CGM_SCU_SEL(5);

	return 0;
}

static void clk_atb_config(void)
{
	uint32 clk_cfg;

	REG32(REG_APCPU_TOP_CLK_CORE_CGM_DEBUG_APB_CFG) |=
                BIT_APCPU_TOP_CLK_CORE_CGM_DEBUG_APB_CFG_CGM_DEBUG_APB_DIV(2);

	clk_cfg = REG32(REG_APCPU_TOP_CLK_CORE_CGM_ATB_CFG);
	clk_cfg |= mcu_clk_para.ap_atb_freq.lvl;
	REG32(REG_APCPU_TOP_CLK_CORE_CGM_ATB_CFG) = clk_cfg;
}

static void clk_periph_config(void)
{
	REG32(REG_APCPU_TOP_CLK_CORE_CGM_PERIPH_CFG) |= mcu_clk_para.ap_periph_freq.lvl;
}

static void clk_ap_axi_config(void)
{
	REG32(REG_AON_CLK_CORE_CGM_AP_AXI_CFG) |=  mcu_clk_para.ap_axi_freq.lvl;
}

static void clk_ap_apb_config(void)
{
	REG32(REG_AP_CLK_CORE_CGM_AP_APB_CFG) |= mcu_clk_para.ap_apb_freq.lvl;
}

static void clk_aon_apb_config(void)
{
	REG32(REG_AON_CLK_CORE_CGM_AON_APB_CFG) = mcu_clk_para.aon_apb_freq.lvl;
}

static void miscclk_config(void)
{
}

static uint32 clk_config(void)
{
    ArmCoreConfig();
    clk_lit_mcu_config(mcu_clk_para.core0_freq.value);
    clk_big_mcu_config(mcu_clk_para.core4_freq.value);
    clk_scu_config(mcu_clk_para.clk_scu_freq.value);
    clk_atb_config();
    clk_periph_config();
    clk_ap_axi_config();
    clk_ap_apb_config();
    clk_aon_apb_config();
    miscclk_config();
    return 0;
}

uint32 MCU_Init()
{
#if defined(CONFIG_CLK_PARA)
    if (clk_config())
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

/* To avoid overshot when switch pll source */
void set_clks_to_default(void)
{
	/* set ap axi clock to default */
	REG32(REG_AON_CLK_CORE_CGM_AP_AXI_CFG) &= ~BIT_AON_CLK_CORE_CGM_AP_AXI_CFG_CGM_AP_AXI_SEL(~0);

	/* set ap apb clock to default */
	REG32(REG_AP_CLK_CORE_CGM_AP_APB_CFG) &= ~BIT_AP_CLK_CORE_CGM_AP_APB_CFG_CGM_AP_APB_SEL(~0);
//	REG32(REG_AON_CLK_CORE_CGM_AON_APB_CFG) &= ~(BIT_AON_CLK_CORE_CGM_AON_APB_CFG_CGM_AON_APB_SEL(~0) |
//				BIT_AON_CLK_CORE_CGM_AON_APB_CFG_CGM_AON_APB_DIV(~0));

	/* set core1 clock to 26m */
	REG32(REG_APCPU_TOP_CLK_CORE_CGM_CORE0_CFG) &=
		~(BIT_APCPU_TOP_CLK_CORE_CGM_CORE0_CFG_CGM_CORE0_SEL(~0) |
		BIT_APCPU_TOP_CLK_CORE_CGM_CORE0_CFG_CGM_CORE0_DIV(~0));

	/* set ap top clocks to default */
	REG32(REG_APCPU_TOP_CLK_CORE_CGM_SCU_CFG) &=
		~(BIT_APCPU_TOP_CLK_CORE_CGM_SCU_CFG_CGM_SCU_SEL(~0) |
		BIT_APCPU_TOP_CLK_CORE_CGM_SCU_CFG_CGM_SCU_DIV(~0));

	REG32(REG_APCPU_TOP_CLK_CORE_CGM_ACE_CFG) &=
		~BIT_APCPU_TOP_CLK_CORE_CGM_ACE_CFG_CGM_ACE_DIV(~0);

	REG32(REG_APCPU_TOP_CLK_CORE_CGM_AXI_PERIPH_CFG) &=
		~BIT_APCPU_TOP_CLK_CORE_CGM_AXI_PERIPH_CFG_CGM_AXI_PERIPH_DIV(~0);

	REG32(REG_APCPU_TOP_CLK_CORE_CGM_AXI_ACP_CFG) &=
		~BIT_APCPU_TOP_CLK_CORE_CGM_AXI_ACP_CFG_CGM_AXI_ACP_DIV(~0);

	REG32(REG_APCPU_TOP_CLK_CORE_CGM_ATB_CFG) &=
		~(BIT_APCPU_TOP_CLK_CORE_CGM_ATB_CFG_CGM_ATB_SEL(~0) |
		BIT_APCPU_TOP_CLK_CORE_CGM_ATB_CFG_CGM_ATB_DIV(~0));

	REG32(REG_APCPU_TOP_CLK_CORE_CGM_DEBUG_APB_CFG) &=
		~BIT_APCPU_TOP_CLK_CORE_CGM_DEBUG_APB_CFG_CGM_DEBUG_APB_DIV(~0);

	REG32(REG_APCPU_TOP_CLK_CORE_CGM_PERIPH_CFG) &= ~(BIT_APCPU_TOP_CLK_CORE_CGM_PERIPH_CFG_CGM_PERIPH_SEL(~0) |
		~BIT_APCPU_TOP_CLK_CORE_CGM_PERIPH_CFG_CGM_PERIPH_DIV(0));
}

void pll_ref_sel(void)
{
	/* Don't bypass rpll */
	REG32(REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CTRL2) |= BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_26M_SEL;

	/* Twpll ref switch to RPLL0 */
	REG32(REG_PMU_APB_TWPLL_REL_CFG) &= ~BIT_PMU_APB_TWPLL_REF_SEL(~0);
	REG32(REG_PMU_APB_TWPLL_REL_CFG) |= BIT_PMU_APB_TWPLL_REF_SEL(1);

	/* LPLL ref switch to RPLL0 */
	REG32(REG_PMU_APB_LTEPLL_REL_CFG) &= ~BIT_PMU_APB_LTEPLL_REF_SEL(~0);
	REG32(REG_PMU_APB_LTEPLL_REL_CFG) |= BIT_PMU_APB_LTEPLL_REF_SEL(1);
}

void pll_sel_cfg(void)
{
	/* MPLL0 1 2 defalut select ap */

	/* ISPPLL default select WCN, dynamically seletct AP */
	REG32(REG_PMU_APB_ISPPLL_REL_CFG) |= BIT_PMU_APB_ISPPLL_WCN_SEL;
	REG32(REG_PMU_APB_ISPPLL_REL_CFG) &= ~BIT_PMU_APB_ISPPLL_AP_SEL;

	/* DPLL0 default select WTLCP PUBCP AP WCN PUB */
	REG32(REG_PMU_APB_DPLL0_REL_CFG)  &= ~BIT_PMU_APB_DPLL0_WCN_SEL;

	/* DPLL1 default select no sys */
	REG32(REG_PMU_APB_DPLL1_REL_CFG)  &= ~BIT_PMU_APB_DPLL1_WCN_SEL;

	/* LTEPLL only select WTLCP */
	REG32(REG_PMU_APB_LTEPLL_REL_CFG) &= ~(BIT_PMU_APB_LTEPLL_PUBCP_SEL |
					       BIT_PMU_APB_LTEPLL_AP_SEL);

	/* TWPLL select all, no wcn and cm4 */
	REG32(REG_PMU_APB_TWPLL_REL_CFG) &= ~BIT_PMU_APB_TWPLL_WCN_SEL;
	REG32(REG_PMU_APB_TWPLL_REL_CFG) &= ~BIT_PMU_APB_TWPLL_SP_SEL;

	/* GPLL select no sys at default */
	REG32(REG_PMU_APB_GPLL_REL_CFG) &= ~BIT_PMU_APB_GPLL_AP_SEL;

	/* RPLL select all, no wcn and cm4 */
	REG32(REG_PMU_APB_RPLL_REL_CFG) &= ~BIT_PMU_APB_RPLL_WCN_SEL;
	REG32(REG_PMU_APB_RPLL_REL_CFG) &= ~BIT_PMU_APB_RPLL_SP_SEL;

	/* PLLs select pub, TWPLL & RPLL select PUB to avoid wakeup hole issue */
	REG32(REG_PMU_APB_XTL_PLL_PD_PUB_SYS_SEL) &= ~(BIT_PMU_APB_ISPPLL_PUB_SEL |
						       BIT_PMU_APB_MPLL2_PUB_SEL |
						       BIT_PMU_APB_MPLL1_PUB_SEL |
						       BIT_PMU_APB_MPLL0_PUB_SEL);

	REG32(REG_PMU_APB_XTL_PLL_PD_PUB_SYS_SEL) |= BIT_PMU_APB_RC0_PUB_SEL |
						     BIT_PMU_APB_XTLBUF0_PUB_SEL |
						     BIT_PMU_APB_XTL0_PUB_SEL |
						     BIT_PMU_APB_TWPLL_PUB_SEL |
						     BIT_PMU_APB_RPLL_PUB_SEL;

	REG32(REG_PMU_APB_XTL0_REL_CFG) &= ~BIT_PMU_APB_XTL0_SP_SEL;
	REG32(REG_PMU_APB_XTLBUF0_REL_CFG) &= ~BIT_PMU_APB_XTLBUF0_SP_SEL;
}

void enable_auto_gate_and_dcs_for_lp(void)
{
	REG32(REG_AON_CLK_LP_BUSCLK_MODE_SEL) &= ~(/*BIT_AON_CLK_LP_CLK_AONMATRIX2AP_MODE_SEL |*/
					BIT_AON_CLK_LP_CLK_AONMATRIX2WTLCP_MODE_SEL |
					BIT_AON_CLK_LP_CLK_AONMATRIX2PUBCP_MODE_SEL |
					BIT_AON_CLK_LP_CLK_AONMATRIX2WCNCP_MODE_SEL |
					BIT_AON_CLK_LP_CLK_WCDMA2PUBCP_MODE_SEL |
					BIT_AON_CLK_LP_CLK_WCDMA2WTLCP_MODE_SEL |
					BIT_AON_CLK_LP_CLK_AON_MATRIX2DBG_MODE_SEL);

	REG32(REG_AON_CLK_LP_VSP_EMC_DCS_CTRL) |= BIT_AON_CLK_LP_VSP_EMC_DCS_EB;
	REG32(REG_AON_CLK_LP_GPU_CORE_DCS_CTRL) |= BIT_AON_CLK_LP_GPU_CORE_DCS_EB;
	REG32(REG_AON_CLK_LP_GPU_SOC_DCS_CTRL) |= BIT_AON_CLK_LP_GPU_SOC_DCS_EB;
}

void disable_unused_clk_for_lp(void)
{
	REG32(REG_AON_APB_APB_EB1) &= ~(BIT_AON_APB_AUX2_EB | BIT_AON_APB_RTC4M0_CAL_EB | BIT_AON_APB_PROBE_EB);
	REG32(REG_AON_APB_APB_EB2) &= ~(BIT_AON_APB_ANLG_APB_EB | BIT_AON_APB_SCC_EB);
	REG32(REG_AON_APB_AON_SDIO) &= ~BIT_AON_APB_AP_SDIO_ENABLE;
	REG32(REG_AON_CLK_CORE_CGM_AUX2_CFG) = 0;
}

void config_for_rco100m_solution(void)
{
	/* set clock source to rco100m */
	REG32(REG_AON_CLK_CORE_CGM_CSSYS_CFG) = BIT_AON_CLK_CORE_CGM_CSSYS_CFG_CGM_CSSYS_SEL(0x3);
	REG32(REG_AON_CLK_CORE_CGM_CPU_DAP_CFG) = BIT_AON_CLK_CORE_CGM_CPU_DAP_CFG_CGM_CPU_DAP_SEL(0x4);
	REG32(REG_AON_CLK_CORE_CGM_ADI_CFG) = BIT_AON_CLK_CORE_CGM_ADI_CFG_CGM_ADI_SEL(0x1);

	/* chip_sleep bypass cm4 */
	REG32(REG_PMU_APB_PAD_OUT_ADIE_CTRL0) |= BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_ARM7_DEEP_SLEEP_MASK;

	/* xtl_buf_en1 not used now */
	REG32(REG_PMU_APB_PAD_OUT_ADIE_CTRL1) |= BIT_PMU_APB_PAD_OUT_XTL_BUF_EN1_AP_DEEP_SLEEP_MASK;

	/* xtl_buf_en2 select cm4 */
	REG32(REG_PMU_APB_PAD_OUT_ADIE_CTRL2) |= BIT_PMU_APB_PAD_OUT_XTL_BUF_EN2_EXT_XTL_PD_MASK |
						BIT_PMU_APB_PAD_OUT_XTL_BUF_EN2_PUB_SYS_PD_MASK |
						BIT_PMU_APB_PAD_OUT_XTL_BUF_EN2_CA53_TOP_PD_MASK |
						BIT_PMU_APB_PAD_OUT_XTL_BUF_EN2_PLL_PD_MASK |
						BIT_PMU_APB_PAD_OUT_XTL_BUF_EN2_WCN_DEEP_SLEEP_MASK |
						BIT_PMU_APB_PAD_OUT_XTL_BUF_EN2_ARM7_DEEP_SLEEP_MASK |
						BIT_PMU_APB_PAD_OUT_XTL_BUF_EN2_WTLCP_DEEP_SLEEP_MASK |
						BIT_PMU_APB_PAD_OUT_XTL_BUF_EN2_PUBCP_DEEP_SLEEP_MASK |
						BIT_PMU_APB_PAD_OUT_XTL_BUF_EN2_AP_DEEP_SLEEP_MASK;
	REG32(REG_PMU_APB_PAD_OUT_ADIE_CTRL2) &= ~BIT_PMU_APB_PAD_OUT_XTL_BUF_EN2_ARM7_DEEP_SLEEP_MASK;

	/* pll_pd bypass rco */
	REG32(REG_PMU_APB_PMU_DUMMY_REG) |= BIT(18);

	/* enable dbg auto power on rco */
	REG32(REG_PMU_APB_CPWRUPREQ_CTRL0) |= BIT(4);
	//REG32(REG_PMU_APB_CPWRUPREQ_CTRL0) &= ~BIT(1);	//only for debug purpose

	/* dap related setting */
	REG32(REG_AON_APB_DAP_DJTAG_CTRL) |= BIT_AON_APB_DAP_DBGPWRUP_SOFT_EN;
}

uint32 set_isppll_clk(uint32 clk)
{
	uint32 clk_cfg1_reg, clk_cfg2_reg, clk_cfg1, clk_cfg2;
	uint32 nint, kint;
	struct sprd_ibias_table *itable = isppll_ibias_table;
	uint32 refin = MPLL_REFIN;

	clk = clk/1000000;

	clk_cfg1_reg = REG_ANLG_PHY_G2_ANALOG_PLL_TOP_IPPLL_CTRL0;
	clk_cfg2_reg = REG_ANLG_PHY_G2_ANALOG_PLL_TOP_IPPLL_CTRL1;

	clk_cfg1 = REG32(clk_cfg1_reg);
	clk_cfg1 |= BIT_ANLG_PHY_G2_ANALOG_PLL_TOP_IPLL_DIV_S | BIT_ANLG_PHY_G2_ANALOG_PLL_TOP_IPLL_SDM_EN;

	/* calc kint/nint */
	nint = BIT_ANLG_PHY_G2_ANALOG_PLL_TOP_IPLL_NINT(NINT(clk, refin));
	kint = BIT_ANLG_PHY_G2_ANALOG_PLL_TOP_IPLL_KINT(KINT(clk, refin));
	clk_cfg2 = REG32(clk_cfg2_reg);
	clk_cfg2 = ~(BIT_ANLG_PHY_G2_ANALOG_PLL_TOP_IPLL_NINT(~0) |
		BIT_ANLG_PHY_G2_ANALOG_PLL_TOP_IPLL_KINT(~0));
	clk_cfg2 |= (nint | kint);

	clk_cfg1 &= ~BIT_ANLG_PHY_G2_ANALOG_PLL_TOP_IPLL_IBIAS(3);
	for (; itable->rate <= SPRD_PLL_MAX_RATE; itable++) {
		if (clk*1000000 <= itable->rate) {
			clk_cfg1 |= BIT_ANLG_PHY_G2_ANALOG_PLL_TOP_IPLL_IBIAS(itable->ibias);
			break;
		}
	}

	REG32(clk_cfg1_reg) = clk_cfg1;
	REG32(clk_cfg2_reg) = clk_cfg2;

	udelay(200);

	return 0;
}

static void rco100m_config()
{
	REG32(REG_ANLG_PHY_G4_ANALOG_RCO100M_RTC100M_CTRL) |= (1 << 15);
	REG32(REG_AON_APB_APB_EB1) |= BIT_AON_APB_RTC4M0_CAL_EB;
	REG32(REG_AON_APB_APB_RST1) |= BIT_AON_APB_RTC4M0_CAL_SOFT_RST;
	udelay(30);
	REG32(REG_AON_APB_APB_RST1) &= ~BIT_AON_APB_RTC4M0_CAL_SOFT_RST;
	REG32(REG_AON_APB_RTC4M_0_CFG) |= BIT_AON_APB_RTC4M0_AUTO_GATE_EN;
	//REG32(REG_AON_APB_RTC4M_0_CFG) |= BIT_AON_APB_RTC4M0_FORCE_EN;
	REG32(REG_AON_APB_RTC4M_0_CFG) |= BIT_AON_APB_RTC4M0_CAL_START;
	while(!(REG32(REG_AON_APB_RTC4M_0_CFG) & BIT_AON_APB_RTC4M0_CAL_DONE));
}

void sprd_ptm_init(void)
{
	#define PTM_CTL_BASE		SPRD_PERF_TRACE_PHYS
	#define PUB_WRAP_BASE		SPRD_PUB_WRAP_PHYS
	#define PTM_GRP_SEL		(PTM_CTL_BASE + 0x0020)
	#define PTM_CLK_EN		(PUB_WRAP_BASE + 0x0054)
	#define PTM_GRP_SEL_VAL 	0x7fac688
	#define PTM_CLK_EN_VAL		0x0013

	CHIP_REG_SET(PTM_CLK_EN, PTM_CLK_EN_VAL);
	udelay(10);
	CHIP_REG_SET(PTM_GRP_SEL, PTM_GRP_SEL_VAL);
}

void cp_jtag_sel_init(void)
{
	CHIP_REG_SET(REG_AON_APB_CP_DAP_PAD_CTRL, 0x3);
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
	local_enable_scr_el3_ea();
	local_async_enable();
	timer_init();
	cp_jtag_sel_init();
#if !defined(CONFIG_FPGA)
	rco100m_config();
	set_clks_to_default();
	pll_sel_cfg();
	pll_ref_sel();
	sci_adi_init();
	sprd_gpio_init();
	ddr_pin_init();
	regulator_init();
	MCU_Init();
	/* to avoid disturb */
	set_isppll_clk(930000000);
	disable_unused_clk_for_lp();
	enable_auto_gate_and_dcs_for_lp();
	config_for_rco100m_solution();
	sdram_init();
	sprd_log();
#endif
	sprd_ptm_init();
}

