
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

#define DDR_READY_BIT	BIT(7)
#define MINIAP_DONE_BIT	BIT(9)

#define MPLL_REFIN 26
#define DPLL_REFIN 26
#define NRDSPPLL_REFIN 26
#define REFIN 26
#define LPLL_REFIN 260
#define MPLL_N(FREQ,REFIN)	(FREQ/REFIN)


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
	.clk_vol_unit_count = 16,
	.clk_list_unit_count = 6,

#if !defined(CONFIG_FPGA)
	.core0_freq.name = "C*CORE0",//clk_core0
	.core0_freq.value = CLK_CORE0,

	.core1_freq.name = "C*CORE1",//clk_core1
	.core1_freq.value = CLK_CORE1,

	.clk_scu.name = "C*SCU",
	.clk_scu.value = CLK_SCU,
#endif

	.ddr_freq.name = "C*DDR",//clk_ddr
	.ddr_freq.value = CLK_DDR_FREQ,

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

	.dcdc_gen0.name = "D*GEN0",
#ifdef DCDC_GEN0
	.dcdc_gen0.value = DCDC_GEN0,
#endif

	.dcdc_gen1.name = "D*GEN1",
#ifdef DCDC_GEN1
	.dcdc_gen1.value = DCDC_GEN1,
#endif

	.dcdc_gpu.name = "D*GPU",
#ifdef DCDC_GPU
	.dcdc_gpu.value = DCDC_GPU,
#endif

	.dcdc_memq.name = "D*MEMQ",
#ifdef DCDC_MEMQ
	.dcdc_memq.value = DCDC_MEMQ,
#endif

	.dcdc_sram.name = "D*SRAM",
#ifdef DCDC_SRAM
	.dcdc_sram.value = DCDC_SRAM,
#endif

	.debug_flags[0].name = "d_flag0",
	.debug_flags[1].name = "d_flag1",
	.debug_flags[2].name = "d_flag2",
	.debug_flags[3].name = "d_flag3",

#if !defined(CONFIG_FPGA)
	.algio_freq.name = "C#ALGIO",
	.algio_freq.lvl_count = CLK_ANALOG_IO_APB_LEVEL,
	.algio_freq.lvl = CLK_ANALOG_IO_APB_LEVEL_ID,
	.algio_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.algio_freq.clk_list = {26000000, 48000000},

	.clk_periph.name = "C*PERIPH",
	.clk_periph.lvl_count = CLK_PERIPH_LEVEL,
	.clk_periph.lvl = CLK_PERIPH_LEVEL_ID,
	.clk_periph.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.clk_periph.clk_list = {26000000, 153600000, 384000000, 512000000},

	.axi_freq.name = "C#AXI",//clk_axi
	.axi_freq.lvl_count = CLK_AXI_LEVEL,
	.axi_freq.lvl = CLK_AXI_LEVEL_ID,
	.axi_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,//all c# clk,the max level_count,now max=6
	.axi_freq.clk_list = {26000000, 64000000, 96000000, 128000000, 256000000, 390000000},

	.peri_apb_freq.name = "C#PERI_APB",
	.peri_apb_freq.lvl_count = CLK_PERI_APB_LEVEL,
	.peri_apb_freq.lvl = CLK_PERI_APB_LEVEL_ID,
	.peri_apb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.peri_apb_freq.clk_list = {26000000, 64000000, 96000000, 128000000},

	.apcpu_axi_freq.name = "C#APCPUAXI",
	.apcpu_axi_freq.lvl_count = CLK_APCPU_AXI_LEVEL ,
	.apcpu_axi_freq.lvl = CLK_APCPU_AXI_LEVEL_ID,
	.apcpu_axi_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.apcpu_axi_freq.clk_list = {26000000, 76800000, 128000000, 256000000},

	.aon_apb_freq.name = "C#AONAPB",//clk_aon_apb
	.aon_apb_freq.lvl_count = CLK_AON_APB_LEVEL,
	.aon_apb_freq.lvl = CLK_AON_APB_LEVEL_ID,
	.aon_apb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.aon_apb_freq.clk_list = {4000000, 4000000, 13000000, 25000000, 26000000, 96000000, 100000000, 128000000},
#endif

	.magic_end = MAGIC_END
};
#endif

static void delay()
{
    volatile uint32 i;
    for (i=0; i<0x100; i++);
}

static void soc_voltage_init()
{

#ifdef CONFIG_ADIE_SC2730
#ifdef DCDC_ARM
    regulator_set_voltage("vddcpu",mcu_clk_para.dcdc_arm.value);
#endif

#ifdef DCDC_CORE
    regulator_set_voltage("vddcore",mcu_clk_para.dcdc_core.value);
#endif

#ifdef DCDC_MEM
    regulator_set_voltage("vddmem",mcu_clk_para.dcdc_mem.value);
#endif

#ifdef DCDC_MEMQ
    regulator_set_voltage("vddmemq",mcu_clk_para.dcdc_memq.value);
#endif

#ifdef DCDC_GEN0
    regulator_set_voltage("vddgen0",mcu_clk_para.dcdc_gen0.value);
#endif

#ifdef DCDC_GEN1
    regulator_set_voltage("vddgen1",mcu_clk_para.dcdc_gen1.value);
#endif

#ifdef DCDC_GPU
    regulator_set_voltage("vddgpu",mcu_clk_para.dcdc_gpu.value);
#endif

#ifdef DCDC_SRAM
    regulator_set_voltage("vddsram",mcu_clk_para.dcdc_sram.value);
#endif
#endif
    delay();
}

#if !defined(CONFIG_FPGA)

#if defined(CONFIG_CLK_PARA)
#define SPRD_PLL_MAX_RATE               (0xFFFFFFFFULL)

struct sprd_icp_table {
	unsigned long long rate;
	u8 icp;
};

static struct sprd_icp_table mpll_icp_table[] = {
	{
		.rate = 1400000000ULL,
		.icp = 1,
	},
	{
		.rate = 1600000000ULL,
		.icp = 2,
	},
	{
		.rate = 1800000000ULL,
		.icp = 3,
	},
	{
		.rate = 2000000000ULL,
		.icp = 4,
	},
	{
		.rate = 2200000000ULL,
		.icp = 5,
	},
	{
		.rate = 2500000000ULL,
		.icp = 6,
	},
	{
		.rate = SPRD_PLL_MAX_RATE,
		.icp = 0x6,
	},
};

static uint32 set_mpll(unsigned long long clk, uint32 index)
{
	uint32 reg1, reg3, clk_cfg1;
	struct sprd_icp_table *itable;

	itable = mpll_icp_table;
	uint32 refin = MPLL_REFIN;

	switch (index) {
	case 0:
		reg1 = REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_CTRL0;
		reg3 = REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_CTRL2;
		break;

	case 1:
		reg1 = REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_CTRL0;
		reg3 = REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_CTRL2;
		break;

	default:
		return -1;
	};

	if (index <=1) {
		if (clk <= 1200000000 ) {
			REG32(reg3) |= BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_POSTDIV ;
			clk = clk * 2;
		}
		else
			REG32(reg3) &= ~BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_POSTDIV ;
	}

	clk = clk/1000000;

	clk_cfg1 = REG32(reg1);

	clk_cfg1 &= ~BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_N(~0);
	clk_cfg1 |= BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_N(MPLL_N(clk, refin));

	clk_cfg1 &= ~BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_ICP(3);
	for (; itable->rate <= SPRD_PLL_MAX_RATE; itable++) {
		if (clk * 1000000 <= itable->rate) {
			clk_cfg1 |= BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_ICP(itable->icp);
			break;
		}
	}

	REG32(reg1) = clk_cfg1;

	udelay(240);

	return 0;
}

static uint32 set_nrdsppll(unsigned long long clk)
{
	uint32 reg1, reg3, clk_cfg1;
	uint32 refin = NRDSPPLL_REFIN;

	reg1 = REG_ANLG_PHY_G3_ANALOG_PLL_TOP_NR_DSPPLL_CTRL0;
	reg3 = REG_ANLG_PHY_G3_ANALOG_PLL_TOP_NR_DSPPLL_CTRL2;
	REG32(reg3) |= BIT_ANLG_PHY_G3_ANALOG_PLL_TOP_NR_DSPPLL_POSTDIV;
	clk = clk * 2;
	clk = clk/1000000;

	clk_cfg1 = REG32(reg1);
	clk_cfg1 &= ~BIT_ANLG_PHY_G3_ANALOG_PLL_TOP_NR_DSPPLL_N(~0);
	clk_cfg1 |= BIT_ANLG_PHY_G3_ANALOG_PLL_TOP_NR_DSPPLL_N(clk/refin);

	clk_cfg1 &= ~BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_ICP(~0);
	clk_cfg1 |= BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_ICP(2);

	REG32(reg1) = clk_cfg1;

	udelay(240);

	return 0;
};

static uint32 apb_clk_config(void)
{
	REG32(REG_AON_CLK_CORE_CGM_AON_APB_CFG) |= mcu_clk_para.aon_apb_freq.lvl;

	REG32(REG_AP_CLK_CORE_CGM_PERI_APB_CFG) |= mcu_clk_para.peri_apb_freq.lvl;

	return 0;
}

static uint32 axi_clk_config(void)
{
	REG32(REG_AP_CLK_CORE_CGM_AXI_CFG) |= mcu_clk_para.axi_freq.lvl;

	return 0;
}

static uint32 clk_periph_config(void)
{
	/* vddcore should be at least 0.8v */;
	REG32(REG_APCPU_CLK_CORE_CGM_PERIPH_CFG) |=
		BIT_APCPU_CLK_CORE_CGM_PERIPH_CFG_CGM_PERIPH_SEL(mcu_clk_para.clk_periph.lvl);

	return 0;
}

static uint32 alg_io_clk_config(void)
{
	REG32(REG_AON_CLK_CORE_CGM_ANALOG_IO_APB_CFG) |= mcu_clk_para.algio_freq.lvl;

	return 0;
}

static uint32 apcpu_axi_clk_config(void)
{
	REG32(REG_AON_CLK_CORE_CGM_APCPU_AXI_CFG) |= mcu_clk_para.apcpu_axi_freq.lvl;

	return 0;
}


static uint32 mcu_clk_config(void)
{
	/* config core0,1 */
	//set_mpll(mcu_clk_para.core0_freq.value, 0);
	REG32(REG_APCPU_CLK_CORE_CGM_CORE0_CFG) |= BIT_APCPU_CLK_CORE_CGM_CORE0_CFG_CGM_CORE0_SEL(2);

	REG32(REG_APCPU_CLK_CORE_CGM_CORE1_CFG) |= BIT_APCPU_CLK_CORE_CGM_CORE1_CFG_CGM_CORE1_SEL(2);

	/* ACE should configure before SCU */
	REG32(REG_APCPU_CLK_CORE_CGM_ACE_CFG) |= BIT_APCPU_CLK_CORE_CGM_ACE_CFG_CGM_ACE_DIV((CLK_SCU + CLK_ACE - 1)/CLK_ACE - 1);

	/* set mpll1 rate */
	//set_mpll(mcu_clk_para.clk_scu.value, 1);
	REG32(REG_APCPU_CLK_CORE_CGM_SCU_CFG) |= BIT_APCPU_CLK_CORE_CGM_SCU_CFG_CGM_SCU_SEL(2);

	return 0;
}

static void misc_clk_config(void)
{
	/* AON usb suspend clock select: 1M  */
	REG32(REG_AON_CLK_CORE_CGM_USB3B_SUSPEND_CFG) = BIT_AON_CLK_CORE_CGM_USB3B_SUSPEND_CFG_CGM_USB3B_SUSPEND_SEL;

	/* IPA usb clock select: 24M */
	REG32(REG_AP_CLK_CORE_CGM_USB1_REF_CFG) = BIT_AP_CLK_CORE_CGM_USB1_REF_CFG_CGM_USB1_REF_SEL;
}

static uint32 clk_config(void)
{
    axi_clk_config();
    clk_periph_config();
    apb_clk_config();
    alg_io_clk_config();
    apcpu_axi_clk_config();
    mcu_clk_config();
    misc_clk_config();
    set_nrdsppll(780000000);
    return 0;
}

uint32 mcu_init()
{
    if (clk_config())
        while(1);

    return 0;
}

#else
uint32 mcu_init()
{
    return 0;
}
#endif


void pll_ref_sel(void)
{
	REG32(REG_AON_CLK_CORE_CGM_ANALOG_IO_APB_CFG) &= ~BIT_AON_CLK_CORE_CGM_ANALOG_IO_APB_CFG_CGM_ANALOG_IO_APB_SEL;
	REG32(REG_AON_CLK_CORE_CGM_APCPU_AXI_CFG) &= ~BIT_AON_CLK_CORE_CGM_APCPU_AXI_CFG_CGM_APCPU_AXI_SEL(~0);
	REG32(REG_AP_CLK_CORE_CGM_AXI_CFG) &= ~BIT_AP_CLK_CORE_CGM_AXI_CFG_CGM_AXI_SEL(~0);
	REG32(REG_APCPU_CLK_CORE_CGM_PERIPH_CFG) &=
					~(BIT_APCPU_CLK_CORE_CGM_PERIPH_CFG_CGM_PERIPH_DIV(~0) |
					BIT_APCPU_CLK_CORE_CGM_PERIPH_CFG_CGM_PERIPH_SEL(~0));
	/* aon apb is special, it's default clk is 26m */
	REG32(REG_AON_CLK_CORE_CGM_AON_APB_CFG) =
		BIT_AON_CLK_CORE_CGM_AON_APB_CFG_CGM_AON_APB_SEL(4);
	REG32(REG_AP_CLK_CORE_CGM_PERI_APB_CFG) &= ~(BIT_AP_CLK_CORE_CGM_PERI_APB_CFG_CGM_PERI_APB_SEL(~0));
	REG32(REG_APCPU_CLK_CORE_CGM_CORE0_CFG) &=
						~(BIT_APCPU_CLK_CORE_CGM_CORE0_CFG_CGM_CORE0_SEL(~0) |
						BIT_APCPU_CLK_CORE_CGM_CORE0_CFG_CGM_CORE0_DIV(~0));
	REG32(REG_APCPU_CLK_CORE_CGM_CORE1_CFG) &=
						~(BIT_APCPU_CLK_CORE_CGM_CORE1_CFG_CGM_CORE1_SEL(~0) |
						BIT_APCPU_CLK_CORE_CGM_CORE1_CFG_CGM_CORE1_DIV(~0));
	REG32(REG_APCPU_CLK_CORE_CGM_ACE_CFG) &= ~BIT_APCPU_CLK_CORE_CGM_ACE_CFG_CGM_ACE_DIV(~0);
	REG32(REG_APCPU_CLK_CORE_CGM_SCU_CFG) &= ~(BIT_APCPU_CLK_CORE_CGM_SCU_CFG_CGM_SCU_SEL(~0) |
						BIT_APCPU_CLK_CORE_CGM_SCU_CFG_CGM_SCU_DIV(~0));


	/* v3_rpll should enable cp,v3_rpll output 26m to v3pll cannot use auto mode, the auto mode cannnot work, so use force mode */
	REG32(REG_AON_APB_V3_RPLL_CTRL_REG0) |= BIT_AON_APB_V3_RPLL_CP_EN_REG;
	REG32(REG_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG) &= ~(BIT_PRE_DIV_CLK_GEN_GATE_EN_SEL1_CFG_CGM_XTL_26M_V3_AUTO_GATE_SEL);
	REG32(REG_PMU_APB_V3PLL_REL_CFG) |= BIT_PMU_APB_V3PLL_REF_SEL(1);

	/*nr_rpll should enable cp, nr_rpll output 26m to nrpll cannot use auto mode, the auto mode cannnot work, so use force mode*/
	REG32(REG_AON_APB_NR_RPLL_CTRL_REG0) |= BIT_AON_APB_NR_RPLL_CP_EN_REG;
	REG32(REG_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG) &= ~(BIT_PRE_DIV_CLK_GEN_PLL_WAIT_SEL0_CFG_NR_RPLL_26M_WAIT_AUTO_GATE_SEL);
	REG32(REG_PMU_APB_NRPLL_REL_CFG) |= BIT_PMU_APB_NRPLL_REF_SEL(1);
}

void pll_sel_cfg(void)
{
	/* XTL sel */
	REG32(REG_PMU_APB_XTL0_REL_CFG) |= BIT_PMU_APB_XTL0_AP_SEL |
					BIT_PMU_APB_XTL0_V3_MODEM_SEL |
					BIT_PMU_APB_XTL0_PSCP_SEL |
					BIT_PMU_APB_XTL0_AUDCP_SEL |
					BIT_PMU_APB_XTL0_PUB_SYS_SEL |
					BIT_PMU_APB_XTL0_SP_SYS_SEL |
					BIT_PMU_APB_XTL0_NRCP_SEL |
					BIT_PMU_APB_XTL0_TOP_DVFS_SEL;

	REG32(REG_PMU_APB_XTL1_REL_CFG) &= ~(BIT_PMU_APB_XTL1_AP_SEL |
					BIT_PMU_APB_XTL1_V3_MODEM_SEL |
					BIT_PMU_APB_XTL1_PSCP_SEL |
					BIT_PMU_APB_XTL1_AUDCP_SEL |
					BIT_PMU_APB_XTL1_PUB_SYS_SEL |
					BIT_PMU_APB_XTL1_SP_SYS_SEL |
					BIT_PMU_APB_XTL1_NRCP_SEL |
					BIT_PMU_APB_XTL1_TOP_DVFS_SEL |
					BIT_PMU_APB_XTL1_IPA_SEL);

	REG32(REG_PMU_APB_XTLBUF0_REL_CFG) |= BIT_PMU_APB_XTLBUF0_AP_SEL |
					BIT_PMU_APB_XTLBUF0_V3_MODEM_SEL |
					BIT_PMU_APB_XTLBUF0_PSCP_SEL |
					BIT_PMU_APB_XTLBUF0_AUDCP_SEL |
					BIT_PMU_APB_XTLBUF0_PUB_SYS_SEL |
					BIT_PMU_APB_XTLBUF0_SP_SYS_SEL |
					BIT_PMU_APB_XTLBUF0_NRCP_SEL |
					BIT_PMU_APB_XTLBUF0_TOP_DVFS_SEL;

	REG32(REG_PMU_APB_XTLBUF1_REL_CFG) &= ~(BIT_PMU_APB_XTLBUF1_AP_SEL |
					BIT_PMU_APB_XTLBUF1_V3_MODEM_SEL |
					BIT_PMU_APB_XTLBUF1_PSCP_SEL |
					BIT_PMU_APB_XTLBUF1_AUDCP_SEL |
					BIT_PMU_APB_XTLBUF1_PUB_SYS_SEL |
					BIT_PMU_APB_XTLBUF1_SP_SYS_SEL |
					BIT_PMU_APB_XTLBUF1_NRCP_SEL |
					BIT_PMU_APB_XTLBUF1_TOP_DVFS_SEL |
					BIT_PMU_APB_XTLBUF1_IPA_SEL);

	/* MPLL0 1  defalut select ap */

	/* DPLL0 default select all ,no sp */
	REG32(REG_PMU_APB_DPLL0_REL_CFG) |= BIT_PMU_APB_DPLL0_AP_SEL |
					BIT_PMU_APB_DPLL0_V3_MODEM_SEL |
					BIT_PMU_APB_DPLL0_PSCP_SEL |
					BIT_PMU_APB_DPLL0_AUDCP_SEL |
					BIT_PMU_APB_DPLL0_PUB_SYS_SEL |
					BIT_PMU_APB_DPLL0_NRCP_SEL;

	/* DPLL1 same as DPLL0 */
	REG32(REG_PMU_APB_DPLL1_REL_CFG) |= BIT_PMU_APB_DPLL1_AP_SEL |
					BIT_PMU_APB_DPLL1_V3_MODEM_SEL |
					BIT_PMU_APB_DPLL1_PSCP_SEL |
					BIT_PMU_APB_DPLL1_AUDCP_SEL |
					BIT_PMU_APB_DPLL1_PUB_SYS_SEL |
					BIT_PMU_APB_DPLL1_NRCP_SEL;

	/* R8PLL select PSCP */

	/* R5PLL select V3_MODEM */

	/* NR_CPUPLL select NRCP */

	/* NR_DSPPLL select NRCP */

	/* V3PLL select all */
	REG32(REG_PMU_APB_V3PLL_REL_CFG) |= BIT_PMU_APB_V3PLL_AP_SEL |
					BIT_PMU_APB_V3PLL_V3_MODEM_SEL |
					BIT_PMU_APB_V3PLL_PSCP_SEL |
					BIT_PMU_APB_V3PLL_AUDCP_SEL |
					BIT_PMU_APB_V3PLL_PUB_SYS_SEL |
					BIT_PMU_APB_V3PLL_SP_SYS_SEL |
					BIT_PMU_APB_V3PLL_NRCP_SEL |
					BIT_PMU_APB_V3PLL_TOP_DVFS_SEL;

	/* V3_RPLL select all */
	REG32(REG_PMU_APB_V3_RPLL_REL_CFG) |= BIT_PMU_APB_V3_RPLL_AP_SEL |
					BIT_PMU_APB_V3_RPLL_V3_MODEM_SEL |
					BIT_PMU_APB_V3_RPLL_PSCP_SEL |
					BIT_PMU_APB_V3_RPLL_AUDCP_SEL |
					BIT_PMU_APB_V3_RPLL_PUB_SYS_SEL |
					BIT_PMU_APB_V3_RPLL_SP_SYS_SEL |
					BIT_PMU_APB_V3_RPLL_NRCP_SEL |
					BIT_PMU_APB_V3_RPLL_TOP_DVFS_SEL;

	/* NRPLL select NRCP */

	/* NR_RPLL select NRCP */

	/* RCO100M select all */
	REG32(REG_PMU_APB_RCO_REL_CFG ) &= ~(BIT_PMU_APB_RCO_AP_SEL |
					BIT_PMU_APB_RCO_V3_MODEM_SEL |
					BIT_PMU_APB_RCO_PSCP_SEL |
					BIT_PMU_APB_RCO_AUDCP_SEL |
					BIT_PMU_APB_RCO_PUB_SYS_SEL |
					BIT_PMU_APB_RCO_SP_SYS_SEL |
					BIT_PMU_APB_RCO_NRCP_SEL |
					BIT_PMU_APB_RCO_TOP_DVFS_SEL |
					BIT_PMU_APB_RCO_IPA_SEL);
}


void enable_auto_gate_for_lp(void)
{
}

/*static void rco100m_config()
{
}
*/
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

#ifdef CONFIG_DDR_BOOT
void boot_flag(int ddr_ret)
{
	if (!ddr_ret)
		CHIP_REG_OR(REG_PMU_APB_PCIE_SLP_CFG, DDR_READY_BIT);

	while(!(CHIP_REG_GET(REG_PMU_APB_PCIE_SLP_CFG) & MINIAP_DONE_BIT));
}
#endif

static void apcpu_pmu_clk_cfg_sel(void)
{
	/*Set apcpu pmu clk to 128MHZ*/
	REG32(REG_AON_CLK_CORE_CGM_APCPU_PMU_CFG) |= BIT_AON_CLK_CORE_CGM_APCPU_PMU_CFG_CGM_APCPU_PMU_SEL(0x3);
}

extern int sc27xx_adc_init(void);
extern int sdram_init(void);
void Chip_Init (void) /*lint !e765 "Chip_Init" is used by init.s entry.s*/
{
	int ret = 0;
	local_enable_scr_el3_ea();
	local_async_enable();
	timer_init();
#if !defined(CONFIG_FPGA)
	REG32(REG_AON_APB_APB_EB1) |= BIT_AON_APB_ANA_EB;
	pll_ref_sel();
	sci_adi_init();
	pll_sel_cfg();
	regulator_init();
	soc_voltage_init();
	mcu_init();
	sc27xx_adc_init();
	enable_auto_gate_for_lp();
	ret = sdram_init();
	apcpu_pmu_clk_cfg_sel();
#endif

#ifdef CONFIG_DDR_BOOT
	boot_flag(ret);
#endif
}

