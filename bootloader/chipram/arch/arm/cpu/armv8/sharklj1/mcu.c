
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

#define REFIN 26
#define NINT(FREQ,REFIN)	(FREQ/REFIN)
#define KINT(FREQ,REFIN)		((FREQ-(FREQ/REFIN)*REFIN)*(0x7FFFFF +1)/REFIN)

#if defined(CONFIG_DUAL_DDR)
extern void noc_init(void);
#endif

#if defined(CONFIG_CLK_PARA)
#include <asm/arch/clk_para_config.h>
const MCU_CLK_PARA_T mcu_clk_para=
{
    .magic_header = MAGIC_HEADER,
    .version = CONFIG_PARA_VERSION,
	.clk_vol_unit_count = 17,
	.clk_list_unit_count = 5,

    .core0_freq.name = "C*CORE0",//clk_core0,1
	.core0_freq.value = CLK_CA53_CORE0,
	.core1_freq.name = "C*CORE1",
	.core1_freq.value = CLK_CA53_CORE1,

	.dgb0_freq.name = "C*DGB0",//clk_debug0,1
	.dgb0_freq.value = CLK_DGB0_FREQ,
	.dgb1_freq.name = "C*DGB1",
	.dgb1_freq.value = CLK_DGB1_FREQ,

	.ace0_freq.name = "C*ACE0",//clk_ace0,1
	.ace0_freq.value = CLK_ACE0_FREQ,
	.ace1_freq.name = "C*ACE1",
	.ace1_freq.value = CLK_ACE1_FREQ,

	.atb0_freq.name = "C*ATB0",//clk_atb0,1
	.atb0_freq.value = CLK_ATB0_FREQ,
	.atb1_freq.name = "C*ATB1",
	.atb1_freq.value = CLK_ATB1_FREQ,

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
	.dcdc_gen.name = "D*GEN",

#ifdef DCDC_MEM
	.dcdc_mem.value = DCDC_MEM,
#endif

#ifdef DCDC_GEN
	.dcdc_gen.value = DCDC_GEN,
#endif

	.debug_flags[0].name = "d_flag0",
	.debug_flags[1].name = "d_flag1",
	.debug_flags[2].name = "d_flag2",
	.debug_flags[3].name = "d_flag3",

	.axi_freq.name = "C#AXI",//clk_ap_axi
	.axi_freq.lvl_count = CLK_AXI_LEVEL,
	.axi_freq.lvl = CLK_AXI_LEVEL_ID,
	.axi_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,//all c# clk,the max level_count,now max=6
	.axi_freq.clk_list = {26000000,76800000,128000000,256000000},

	.cci_freq.name = "C#CCI",//clk_cci
	.cci_freq.lvl_count = CLK_CCI_LEVEL,
	.cci_freq.lvl = CLK_CCI_LEVEL_ID,
	.cci_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.cci_freq.clk_list = {26000000,153600000,384000000,512000000,614400000,667000000},

	.ap_apb_freq.name = "C#AP_APB",//clk_ap_apb
	.ap_apb_freq.lvl_count = CLK_APB_LEVEL,
	.ap_apb_freq.lvl = CLK_APB_LEVEL_ID,
	.ap_apb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.ap_apb_freq.clk_list = {26000000,64000000,96000000,128000000},

	.aon_apb_freq.name = "C#AONAPB",//clk_aon_apb
	.aon_apb_freq.lvl_count = CLK_AON_APB_LEVEL,
	.aon_apb_freq.lvl = CLK_AON_APB_LEVEL_ID,
	.aon_apb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.aon_apb_freq.clk_list = {4000000,26000000,96000000,128000000},

	.pub_ahb_freq.name = "C#PUBAHB",//clk_pub_ahb
	.pub_ahb_freq.lvl_count = CLK_PUB_AHB_LEVEL,
	.pub_ahb_freq.lvl = CLK_PUB_AHB_LEVEL_ID,
	.pub_ahb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.pub_ahb_freq.clk_list = {26000000,4000000,96000000,128000000},

	.magic_end = MAGIC_END
};
#endif
#define SPRD_PLL_MAX_RATE		(0xFFFFFFFF)
struct sprd_ibias_table {
	unsigned long rate;
	u8 ibias;
};

static struct sprd_ibias_table pll_ibias_table[] = {
	{
		.rate = 988000000UL,
		.ibias = 0x0,
	},
	{
		.rate = 1274000000UL,
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

static void delay(void)
{
    volatile uint32 i;
    for (i=0; i<0x100; i++);
}

#if defined(CONFIG_VOL_PARA)

static uint32 ArmCoreConfig(uint32 arm_clk)
{
#if defined(CONFIG_VOL_PARA)

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

#endif

static uint32 SetBigLitMPllClk(uint32 clk, uint32 litflag)
{
	uint32 clk_cfg1_reg, clk_cfg2_reg, clk_cfg1, clk_cfg2;
	uint32 nint, kint;
	struct sprd_ibias_table *itable = pll_ibias_table;
	uint32 refin = REFIN;

	/* 1:lit core  0:big core */
	clk = clk/1000000;
	if (litflag) {
		clk_cfg1_reg = REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_CTRL0;
		clk_cfg2_reg = REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_CTRL1;
	} else {
		clk_cfg1_reg = REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_CTRL0;
		clk_cfg2_reg = REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_CTRL1;
	}

	/* mpll0/mpll1 has the same bit definition */
	clk_cfg1 = REG32(clk_cfg1_reg);
	clk_cfg1 |= (BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_SDM_EN
		|  BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_DIV_S);

	nint = BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_NINT(NINT(clk,refin));
	kint = BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_KINT(KINT(clk,refin));
	clk_cfg2 = REG32(clk_cfg2_reg);
	clk_cfg2 &= ~(BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_NINT(~0x0)
			| BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_KINT(~0x0));
	clk_cfg2 |= (nint | kint);
	/* set ibias */
	clk_cfg1 &= (~BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_IBIAS(3));
	for (; itable->rate <= SPRD_PLL_MAX_RATE; itable++) {
		if (clk*1000000 <= itable->rate) {
			clk_cfg1 |= BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_IBIAS(itable->ibias);
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

static uint32 SetMPllClk(uint32 clk,uint32 big_clk)
{
	SetBigLitMPllClk(clk, 1);
	SetBigLitMPllClk(big_clk, 0);
	return 0;
}

static uint32 AhbClkConfig(void)
{
	uint32 ahb_cfg;

	/* pub_ahb set to twpll_128m*/
	ahb_cfg  = REG32(REG_AON_CLK_CORE_CGM_PUB_AHB_CFG);
	ahb_cfg &= ~BIT_AON_CLK_CORE_CGM_PUB_AHB_CFG_CGM_PUB_AHB_SEL(~0x0);
	ahb_cfg |= mcu_clk_para.pub_ahb_freq.lvl;
	REG32(REG_AON_CLK_CORE_CGM_PUB_AHB_CFG) = ahb_cfg;

	delay();
	return 0;
}

static uint32 ApbClkConfig(void)
{
	uint32 clk_cfg;

	/* ap_apb set to twpll_128m*/
	clk_cfg = REG32(REG_AP_CLK_CORE_CGM_AP_APB_CFG);
	clk_cfg &= ~BIT_AP_CLK_CORE_CGM_AP_APB_CFG_CGM_AP_APB_SEL(~0);
	clk_cfg |= mcu_clk_para.ap_apb_freq.lvl;
	REG32(REG_AP_CLK_CORE_CGM_AP_APB_CFG) = clk_cfg;

	/* aon_apb set to twpll_128m*/
	clk_cfg = REG32(REG_AON_CLK_CORE_CGM_AON_APB_CFG);
	clk_cfg &= ~BIT_AON_CLK_CORE_CGM_AON_APB_CFG_CGM_AON_APB_SEL(~0);
	clk_cfg |= mcu_clk_para.aon_apb_freq.lvl;
	REG32(REG_AON_CLK_CORE_CGM_AON_APB_CFG) = clk_cfg;

	delay();
	return 0;
}

static void CciClkConfig(void)
{
	/* cci set to twpll_512m*/
	uint32 clk_cfg;
	clk_cfg = REG32(REG_AON_CLK_CORE_CGM_CCI_CFG);
	clk_cfg &= ~BIT_AON_CLK_CORE_CGM_CCI_CFG_CGM_CCI_SEL(~0);
	clk_cfg |= mcu_clk_para.cci_freq.lvl;
	REG32(REG_AON_CLK_CORE_CGM_CCI_CFG) = clk_cfg;

}
static uint32 AxiClkConfig(uint32 arm_clk)
{
	uint32 clk_cfg;

	/* ap_axi set to twpll_256m*/
	clk_cfg = REG32(REG_AON_CLK_CORE_CGM_AP_AXI_CFG);
	clk_cfg &= ~BIT_AON_CLK_CORE_CGM_AP_AXI_CFG_CGM_AP_AXI_SEL(~0);
	clk_cfg |= mcu_clk_para.axi_freq.lvl;
	REG32(REG_AON_CLK_CORE_CGM_AP_AXI_CFG) = clk_cfg;

	delay();
	return 0;
}

static uint32 DbgClkConfig(uint32 arm_clk,uint32 arm_big_clk)
{
	uint32 clk_cfg,freq1,freq2,freq3;

	clk_cfg = REG32(REG_AON_APB_CA53_LIT_CLK_CFG);//lit ACE/DBG/ATB
	clk_cfg &= ~(7 << 8 | 7 << 12 | 7 << 16);
	freq1 = mcu_clk_para.ace0_freq.value;
	freq2 = mcu_clk_para.dgb0_freq.value;
	freq3 = mcu_clk_para.atb0_freq.value;

	clk_cfg |= (arm_clk/freq1-1+ ((arm_clk%freq1)? 1:0))<<8;
	clk_cfg |= (arm_clk/freq2-1+ ((arm_clk%freq2)? 1:0))<<12;
	clk_cfg |= (arm_clk/freq3-1+ ((arm_clk%freq3)? 1:0))<<16;
	REG32(REG_AON_APB_CA53_LIT_CLK_CFG) = clk_cfg;

	clk_cfg = REG32(REG_AON_APB_CA53_BIG_CLK_CFG);//big ACE/DBG/ATB
	clk_cfg &= ~(7 << 8 | 7 << 12 | 7 << 16);
	freq1 = mcu_clk_para.ace1_freq.value;
	freq2 = mcu_clk_para.dgb1_freq.value;
	freq3 = mcu_clk_para.atb1_freq.value;

	clk_cfg |= (arm_big_clk/freq1-1+ ((arm_big_clk%freq1)? 1:0))<<8;
	clk_cfg |= (arm_big_clk/freq2-1+ ((arm_big_clk%freq2)? 1:0))<<12;
	clk_cfg |= (arm_big_clk/freq3-1+ ((arm_big_clk%freq3)? 1:0))<<16;
	REG32(REG_AON_APB_CA53_BIG_CLK_CFG) = clk_cfg;

	return 0;
}

static uint32 McuClkConfig(uint32 arm_clk,uint32 arm_big_clk)
{
	uint32 clk_cfg;

	SetMPllClk(arm_clk,arm_big_clk);
	delay();

	/* little cpu switch to mpll0 */
	clk_cfg = REG32(REG_AON_APB_CA53_LIT_CLK_CFG);
	clk_cfg |= 8;
	REG32(REG_AON_APB_CA53_LIT_CLK_CFG) = clk_cfg;
	delay();

	clk_cfg = REG32(REG_AON_APB_CA53_BIG_CLK_CFG);
	clk_cfg |= 8;
	REG32(REG_AON_APB_CA53_BIG_CLK_CFG) = clk_cfg;
	delay();

	return 0;
}

static uint32 Analog_IO_ClkConfig()
{
	uint32 clk_cfg;
	clk_cfg = REG32(REG_AON_CLK_CORE_CGM_ANALOG_APB_CFG);
	clk_cfg &= ~BIT_AON_CLK_CORE_CGM_ANALOG_APB_CFG_CGM_ANALOG_APB_SEL(~0x0);
	clk_cfg |= BIT_AON_CLK_CORE_CGM_ANALOG_APB_CFG_CGM_ANALOG_APB_SEL(2);//48M
	REG32(REG_AON_CLK_CORE_CGM_ANALOG_APB_CFG) = clk_cfg;

	clk_cfg = REG32(REG_AON_CLK_CORE_CGM_IO_APB_CFG);
	clk_cfg &= ~BIT_AON_CLK_CORE_CGM_IO_APB_CFG_CGM_IO_APB_SEL(~0x0);
	clk_cfg |= BIT_AON_CLK_CORE_CGM_IO_APB_CFG_CGM_IO_APB_SEL(2);//48M
	REG32(REG_AON_CLK_CORE_CGM_IO_APB_CFG) = clk_cfg;
	delay();
	return 0;
}

static uint32 Rfti_SBI_ClkConfig()
{
	uint32 clk_cfg;
	clk_cfg = REG32(REG_AON_CLK_CORE_CGM_RFTI_SBI_CFG);
	clk_cfg &= ~BIT_AON_CLK_CORE_CGM_RFTI_SBI_CFG_CGM_RFTI_SBI_SEL(~0x0);
	clk_cfg |= BIT_AON_CLK_CORE_CGM_RFTI_SBI_CFG_CGM_RFTI_SBI_SEL(4);//96M
	REG32(REG_AON_CLK_CORE_CGM_RFTI_SBI_CFG) = clk_cfg;
	delay();
	return 0;
}

static uint32 ClkConfig(uint32 arm_clk,uint32 arm_big_clk)
{
	ArmCoreConfig(arm_clk);
	AxiClkConfig(arm_clk);
	DbgClkConfig(arm_clk,arm_big_clk);
	McuClkConfig(arm_clk,arm_big_clk);
	AhbClkConfig();
	ApbClkConfig();
	CciClkConfig();
	Analog_IO_ClkConfig();
	Rfti_SBI_ClkConfig();
	return 0;
}

uint32 MCU_Init(void)
{
#if defined(CONFIG_CLK_PARA)
    if (ClkConfig(mcu_clk_para.core0_freq.value,mcu_clk_para.core1_freq.value))
#else
    if (ClkConfig(CLK_800M,CLK_1500M))
#endif
        while(1);
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

void SwitchPll(void)
{
	uint32 clk_cfg;

	/*
	 * lvdspll twpll witch to rpll,lvdspll switch to untune26M
	 */
	clk_cfg = REG32(REG_PMU_APB_TWPLL_REL_CFG);
	clk_cfg &= ~BIT_PMU_APB_TWPLL_REF_SEL(~0x0);
	clk_cfg |= BIT_PMU_APB_TWPLL_REF_SEL(1);
	REG32(REG_PMU_APB_TWPLL_REL_CFG) = clk_cfg;

	clk_cfg = REG32(REG_PMU_APB_LTEPLL_REL_CFG);
	clk_cfg &= ~BIT_PMU_APB_LTEPLL_REF_SEL(~0x0);
	clk_cfg |= BIT_PMU_APB_LTEPLL_REF_SEL(1);
	REG32(REG_PMU_APB_LTEPLL_REL_CFG) = clk_cfg;

	clk_cfg = REG32(REG_PMU_APB_LVDSRFPLL_REL_CFG);
	clk_cfg &= ~BIT_PMU_APB_LVDSRFPLL_REF_SEL(~0x0);
	clk_cfg |= BIT_PMU_APB_LVDSRFPLL_REF_SEL(2);
	REG32(REG_PMU_APB_LVDSRFPLL_REL_CFG) = clk_cfg;
}

void pll_sel_config(uint32_t gen_para)
{
	/*
	 * step1:xtl related subsys configuration
	 */
	CHIP_REG_OR(REG_PMU_APB_XTL0_REL_CFG, (BIT_PMU_APB_XTL0_ARM7_SEL |
											BIT_PMU_APB_XTL0_PUBCP_SEL |
											BIT_PMU_APB_XTL0_WTLCP_SEL |
											BIT_PMU_APB_XTL0_AP_SEL));

	CHIP_REG_AND(REG_PMU_APB_XTL1_REL_CFG, ~(BIT_PMU_APB_XTL1_ARM7_SEL |
											BIT_PMU_APB_XTL1_PUBCP_SEL |
											BIT_PMU_APB_XTL1_WTLCP_SEL |
											BIT_PMU_APB_XTL1_AP_SEL));

	CHIP_REG_OR(REG_PMU_APB_XTLBUF0_REL_CFG, (BIT_PMU_APB_XTLBUF0_ARM7_SEL |
											BIT_PMU_APB_XTLBUF0_PUBCP_SEL |
											BIT_PMU_APB_XTLBUF0_WTLCP_SEL |
											BIT_PMU_APB_XTLBUF0_AP_SEL));

	/*audio will use xtlbuf1 output 26m*/
	CHIP_REG_OR(REG_PMU_APB_XTLBUF1_REL_CFG, BIT_PMU_APB_XTLBUF1_AP_SEL);

	CHIP_REG_AND(REG_PMU_APB_XTLBUF1_REL_CFG, ~(BIT_PMU_APB_XTLBUF1_ARM7_SEL |
											BIT_PMU_APB_XTLBUF1_PUBCP_SEL |
											BIT_PMU_APB_XTLBUF1_WTLCP_SEL));
	/*
	 * pub related to rpll/twpll/ltepll/dpll/xtl0/xtlbuf0/chip_sleep
	 */
	CHIP_REG_OR(REG_PMU_APB_XTL_PLL_PD_PUB_SYS_SEL, (BIT_PMU_APB_XTL0_PUB_SEL |
											BIT_PMU_APB_XTLBUF0_PUB_SEL |
											BIT_PMU_APB_DPLL_PUB_SEL |
											BIT_PMU_APB_TWPLL_PUB_SEL |
											BIT_PMU_APB_LTEPLL_PUB_SEL |
											BIT_PMU_APB_RPLL_PUB_SEL));

	/*
	 * step2: pll related subsys configuration
	 * cppll, gpll related nothing
	 */
	CHIP_REG_OR(REG_PMU_APB_TWPLL_REL_CFG, (BIT_PMU_APB_TWPLL_ARM7_SEL |
											BIT_PMU_APB_TWPLL_PUBCP_SEL |
											BIT_PMU_APB_TWPLL_WTLCP_SEL |
											BIT_PMU_APB_TWPLL_AP_SEL));

	CHIP_REG_OR(REG_PMU_APB_MPLL_REL_CFG, BIT_PMU_APB_MPLL_AP_SEL);
	CHIP_REG_AND(REG_PMU_APB_MPLL_REL_CFG, ~(BIT_PMU_APB_MPLL_ARM7_SEL |
											BIT_PMU_APB_MPLL_PUBCP_SEL |
											BIT_PMU_APB_MPLL_WTLCP_SEL));

	CHIP_REG_OR(REG_PMU_APB_BMPLL_REL_CFG, BIT_PMU_APB_BMPLL_AP_SEL);
	CHIP_REG_AND(REG_PMU_APB_BMPLL_REL_CFG, ~(BIT_PMU_APB_BMPLL_ARM7_SEL |
											BIT_PMU_APB_BMPLL_PUBCP_SEL |
											BIT_PMU_APB_BMPLL_WTLCP_SEL));

	CHIP_REG_OR(REG_PMU_APB_RPLL_REL_CFG, (BIT_PMU_APB_RPLL_ARM7_SEL |
											BIT_PMU_APB_RPLL_PUBCP_SEL |
											BIT_PMU_APB_RPLL_WTLCP_SEL |
											BIT_PMU_APB_RPLL_AP_SEL));

	CHIP_REG_OR(REG_PMU_APB_DPLL_REL_CFG, (BIT_PMU_APB_DPLL_AP_SEL |
											BIT_PMU_APB_DPLL_PUBCP_SEL |
											BIT_PMU_APB_DPLL_WTLCP_SEL));
	CHIP_REG_AND(REG_PMU_APB_DPLL_REL_CFG, ~(BIT_PMU_APB_DPLL_ARM7_SEL));

	CHIP_REG_OR(REG_PMU_APB_LTEPLL_REL_CFG, BIT_PMU_APB_LTEPLL_WTLCP_SEL);
	CHIP_REG_AND(REG_PMU_APB_LTEPLL_REL_CFG, ~(BIT_PMU_APB_LTEPLL_ARM7_SEL |
												BIT_PMU_APB_LTEPLL_PUBCP_SEL |
												BIT_PMU_APB_LTEPLL_AP_SEL));
}

static void memory_repair_once()
{
	CHIP_REG_OR(REG_PMU_APB_BISR_FORCE_SEL,BIT_PMU_APB_PD_AON_MEM_BISR_FORCE_SEL);
}

void Chip_Init (void) /*lint !e765 "Chip_Init" is used by init.s entry.s*/
{
	memory_repair_once();
	timer_init();
	sci_adi_init();
	regulator_init();
#if !defined(CONFIG_FPGA)
	pll_sel_config(0x0);
	SwitchPll();
	MCU_Init();
	sdram_init();
#endif

/*
 * mdelay init for mmc_v40.c use
*/
	CHIP_REG_OR(REG_AON_APB_APB_EB0, BIT_AON_APB_AP_SYST_EB);
	CHIP_REG_OR(REG_AON_APB_APB_RTC_EB, BIT_AON_APB_AP_SYST_RTC_EB);
}

