
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

#define MPLL_REFIN 26
#define DPLL_REFIN 26
#define REFIN 26
#define LPLL_REFIN 260
#define MPLL_N(FREQ,REFIN)	(FREQ/REFIN)

#define string_log(x) ddrc_print_debug(x)

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
	.clk_vol_unit_count = 22,
	.clk_list_unit_count = 11,

#if !defined(CONFIG_FPGA)
	.core0_freq.name = "C*CORE0",//clk_core0
	.core0_freq.value = CLK_CORE0,

	.core1_freq.name = "C*CORE1",//clk_core1
	.core1_freq.value = CLK_CORE1,

	.core2_freq.name = "C*CORE2",//clk_core2
	.core2_freq.value = CLK_CORE2,

	.core3_freq.name = "C*CORE3",//clk_core3
	.core3_freq.value = CLK_CORE3,

	.core4_freq.name = "C*CORE4",//clk_core4
	.core4_freq.value = CLK_CORE4,

	.core5_freq.name = "C*CORE5",//clk_core5
	.core5_freq.value = CLK_CORE5,

	.core6_freq.name = "C*CORE6",//clk_core6
	.core6_freq.value = CLK_CORE6,

	.core7_freq.name = "C*CORE7",//clk_core7
	.core7_freq.value = CLK_CORE7,

	.clk_scu.name = "C*SCU",
	.clk_scu.value = CLK_SCU,
#endif

	.ddr_freq.name = "C*DDR",//clk_ddr
	.ddr_freq.value = CLK_DDR_FREQ,

#ifdef DDR_MODE
	.ddr_mode.name = "DDR_MODE",//ddr_mode
	.ddr_mode.value = DDR_MODE,
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

	.vsp_freq.name = "C#VSP",
	.vsp_freq.lvl_count = CLK_VSP_LEVEL,
	.vsp_freq.lvl = CLK_VSP_LEVEL_ID,
	.vsp_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.vsp_freq.clk_list = {256000000, 307200000, 384000000, 512000000},

	.clk_periph.name = "C*PERIPH",
	.clk_periph.lvl_count = CLK_PERIPH_LEVEL,
	.clk_periph.lvl = CLK_PERIPH_LEVEL_ID,
	.clk_periph.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.clk_periph.clk_list = {26000000, 153600000, 512000000, 768000000},

	.ap_axi_freq.name = "C#AXI",//clk_axi
	.ap_axi_freq.lvl_count = CLK_AP_AXI_LEVEL,
	.ap_axi_freq.lvl = CLK_AP_AXI_LEVEL_ID,
	.ap_axi_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,//all c# clk,the max level_count,now max=6
	.ap_axi_freq.clk_list = {26000000, 76800000, 128000000, 256000000},

	.ap_apb_freq.name = "C#AP_APB",//clk_apb
	.ap_apb_freq.lvl_count = CLK_AP_APB_LEVEL,
	.ap_apb_freq.lvl = CLK_AP_APB_LEVEL_ID,
	.ap_apb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.ap_apb_freq.clk_list = {26000000, 64000000, 96000000, 128000000},

	.aon_apb_freq.name = "C#AONAPB",//clk_aon_apb
	.aon_apb_freq.lvl_count = CLK_AON_APB_LEVEL,
	.aon_apb_freq.lvl = CLK_AON_APB_LEVEL_ID,
	.aon_apb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.aon_apb_freq.clk_list = {4000000, 4000000, 13000000, 25000000, 26000000, 96000000, 100000000, 128000000},

	.ap_mm_freq.name = "C#MM",
	.ap_mm_freq.lvl_count = CLK_AP_MM_LEVEL,
	.ap_mm_freq.lvl = CLK_AP_MM_LEVEL_ID,
	.ap_mm_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.ap_mm_freq.clk_list = {26000000, 96000000, 128000000, 153600000},

	.ap_gpu_freq.name = "C#GPU",
	.ap_gpu_freq.lvl_count = CLK_AP_GPU_LEVEL,
	.ap_gpu_freq.lvl = CLK_AP_GPU_LEVEL_ID,
	.ap_gpu_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.ap_gpu_freq.clk_list = {26000000, 96000000, 128000000, 153600000},

	.ap_ai_freq.name = "C#AI",
	.ap_ai_freq.lvl_count = CLK_AP_AI_LEVEL,
	.ap_ai_freq.lvl = CLK_AP_AI_LEVEL_ID,
	.ap_ai_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.ap_ai_freq.clk_list = {26000000, 96000000, 128000000, 153600000},

	.vdsp_freq.name = "C#VDSP",
	.vdsp_freq.lvl_count = CLK_VDSP_LEVEL,
	.vdsp_freq.lvl = CLK_VDSP_LEVEL_ID,
	.vdsp_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.vdsp_freq.clk_list = {192000000, 307200000, 468000000, 614400000, 702000000, 768000000},

	.ipa_core_freq.name = "C#IPACORE",
	.ipa_core_freq.lvl_count = CLK_IPA_CORE_LEVEL,
	.ipa_core_freq.lvl = CLK_IPA_CORE_LEVEL_ID,
	.ipa_core_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.ipa_core_freq.clk_list = {26000000, 192000000, 384000000, 409600000},
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

static struct sprd_icp_table mpll2_icp_table[] = {
	{
		.rate = 1200000000ULL,
		.icp = 0,
	},
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
		.rate = SPRD_PLL_MAX_RATE,
		.icp = 0x4,
	},
};

static uint32 set_mpll(unsigned long long clk, uint32 index)
{
	uint32 reg1, reg3, clk_cfg1;
	struct sprd_icp_table *itable;

	if (index < 2)
		itable = mpll_icp_table;
	else
		itable = mpll2_icp_table;
	uint32 refin = MPLL_REFIN;

	switch (index) {
	case 0:
		reg1 = REG_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CTRL0;
		reg3 = REG_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_CTRL4;
		break;

	case 1:
		reg1 = REG_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CTRL0;
		reg3 = REG_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_CTRL4;
		break;

	case 2:
		reg1 = REG_ANLG_PHY_G9_ANALOG_MPLL2_MPLL2_CTRL0;
		reg3 = REG_ANLG_PHY_G9_ANALOG_MPLL2_MPLL2_CTRL4;
		break;

	default:
		return -1;
	};

	if (index < 2) {
		if (clk <= 1200000000 ) {
			REG32(reg3) |= BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_POSTDIV;
			clk = clk * 2;
		}
		else
			REG32(reg3) &= ~BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_POSTDIV;
	} else {
		if (clk <= 1000000000 ) {
			REG32(reg3) |= BIT_ANLG_PHY_G9_ANALOG_MPLL2_MPLL2_POSTDIV;
			clk = clk * 2;
		}
		else
			REG32(reg3) &= ~BIT_ANLG_PHY_G9_ANALOG_MPLL2_MPLL2_POSTDIV;
	}

	clk = clk/1000000;

	clk_cfg1 = REG32(reg1);
	clk_cfg1 &= ~(BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_DIV_S | BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_SDM_EN);

	clk_cfg1 &= ~BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_N(~0);
	clk_cfg1 |= BIT_ANLG_PHY_G17_ANALOG_MPLL0_MPLL0_N(MPLL_N(clk, refin));

	clk_cfg1 &= ~BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_ICP(3);
	for (; itable->rate <= SPRD_PLL_MAX_RATE; itable++) {
		if (clk * 1000000 <= itable->rate) {
			clk_cfg1 |= BIT_ANLG_PHY_G4_ANALOG_MPLL1_MPLL1_ICP(itable->icp);
			break;
		}
	}

	REG32(reg1) = clk_cfg1;

	udelay(240);

	return 0;
}

static uint32 apb_clk_config(void)
{
	/* aon apb is special, it's default clk is 26m */
	REG32(REG_AON_CLK_CORE_CGM_AON_APB_CFG) =
					BIT_AON_CLK_CORE_CGM_AON_APB_CFG_CGM_AON_APB_SEL(4);
	REG32(REG_AON_CLK_CORE_CGM_AON_APB_CFG) |= mcu_clk_para.aon_apb_freq.lvl;

	REG32(REG_AP_CLK_CORE_CGM_AP_APB_CFG) &= ~(BIT_AP_CLK_CORE_CGM_AP_APB_CFG_CGM_AP_APB_SEL(~0));
	REG32(REG_AP_CLK_CORE_CGM_AP_APB_CFG) |= mcu_clk_para.ap_apb_freq.lvl;

	return 0;
}

static uint32 axi_clk_config(void)
{
	REG32(REG_AON_CLK_CORE_CGM_AP_AXI_CFG) &= ~BIT_AON_CLK_CORE_CGM_AP_AXI_CFG_CGM_AP_AXI_SEL(~0);
	REG32(REG_AON_CLK_CORE_CGM_AP_AXI_CFG) |= mcu_clk_para.ap_axi_freq.lvl;

	return 0;
}

static uint32 clk_periph_config(void)
{
	/* vddcore should be at least 0.8v */
	REG32(REG_AON_SEC_APB_APCPU_TOP_MISC_CLK_CFG) &=
					~(BIT_AON_SEC_APB_CGM_PERIPH_DIV(~0) |
					BIT_AON_SEC_APB_CGM_PERIPH_SEL(~0));

	REG32(REG_AON_SEC_APB_APCPU_TOP_MISC_CLK_CFG) |=
		BIT_AON_SEC_APB_CGM_PERIPH_SEL(mcu_clk_para.clk_periph.lvl);

	return 0;
}

static uint32 alg_io_clk_config(void)
{
	REG32(REG_AON_CLK_CORE_CGM_ANALOG_IO_APB_CFG) &= ~BIT_AON_CLK_CORE_CGM_ANALOG_IO_APB_CFG_CGM_ANALOG_IO_APB_SEL;
	REG32(REG_AON_CLK_CORE_CGM_ANALOG_IO_APB_CFG) |= mcu_clk_para.algio_freq.lvl;

	return 0;
}

static uint32 vsp_clk_config(void)
{
	REG32(REG_AP_CLK_CORE_CGM_VSP_CFG) &= ~BIT_AP_CLK_CORE_CGM_VSP_CFG_CGM_VSP_SEL(~0);
	REG32(REG_AP_CLK_CORE_CGM_VSP_CFG) |= mcu_clk_para.vsp_freq.lvl;

	return 0;
}

static uint32 mm_clk_config(void)
{
	REG32(REG_AON_CLK_CORE_CGM_AP_MM_CFG) &= ~BIT_AON_CLK_CORE_CGM_AP_MM_CFG_CGM_AP_MM_SEL(~0);
	REG32(REG_AON_CLK_CORE_CGM_AP_MM_CFG) |= mcu_clk_para.ap_mm_freq.lvl;

	return 0;
}

static uint32 gpu_clk_config(void)
{
	REG32(REG_AON_CLK_CORE_CGM_AP_GPU_CFG) &= ~BIT_AON_CLK_CORE_CGM_AP_GPU_CFG_CGM_AP_GPU_SEL(~0);
	REG32(REG_AON_CLK_CORE_CGM_AP_GPU_CFG) |= mcu_clk_para.ap_gpu_freq.lvl;

	return 0;
}

static uint32 ai_clk_config(void)
{
	REG32(REG_AON_CLK_CORE_CGM_AP_AI_CFG) &= ~BIT_AON_CLK_CORE_CGM_AP_AI_CFG_CGM_AP_AI_SEL(~0);
	REG32(REG_AON_CLK_CORE_CGM_AP_AI_CFG) |= mcu_clk_para.ap_ai_freq.lvl;

	return 0;
}

static uint32 vdsp_clk_config(void)
{
	REG32(REG_AP_CLK_CORE_CGM_VDSP_CFG) &= ~BIT_AP_CLK_CORE_CGM_VDSP_CFG_CGM_VDSP_SEL(~0);
	REG32(REG_AP_CLK_CORE_CGM_VDSP_CFG) |= mcu_clk_para.vdsp_freq.lvl;

	return 0;
}

static uint32 ipa_core_clk_config(void)
{
	unsigned long long clk_ipa_core;
	unsigned long long clk_ipa_mtx;
	unsigned long long clk_ipa_apb;

	clk_ipa_core=mcu_clk_para.ipa_core_freq.clk_list[mcu_clk_para.ipa_core_freq.lvl];
	clk_ipa_mtx=clk_ipa_core;
	REG32(REG_IPA_CLK_CORE_CGM_IPA_MTX_CFG ) &= ~BIT_IPA_CLK_CORE_CGM_IPA_MTX_CFG_CGM_IPA_MTX_DIV(~0);
	REG32(REG_IPA_CLK_CORE_CGM_IPA_MTX_CFG ) |= BIT_IPA_CLK_CORE_CGM_IPA_MTX_CFG_CGM_IPA_MTX_DIV((clk_ipa_core + clk_ipa_mtx - 1)/clk_ipa_mtx - 1);

	clk_ipa_apb=clk_ipa_core/2;
	REG32(REG_IPA_CLK_CORE_CGM_IPA_APB_CFG ) &= ~BIT_IPA_CLK_CORE_CGM_IPA_APB_CFG_CGM_IPA_APB_DIV(~0);
	REG32(REG_IPA_CLK_CORE_CGM_IPA_APB_CFG ) |= BIT_IPA_CLK_CORE_CGM_IPA_APB_CFG_CGM_IPA_APB_DIV((clk_ipa_core + clk_ipa_apb - 1)/clk_ipa_apb - 1);

	REG32(REG_IPA_CLK_CORE_CGM_IPA_CORE_CFG) &= ~BIT_IPA_CLK_CORE_CGM_IPA_CORE_CFG_CGM_IPA_CORE_SEL(~0);
	REG32(REG_IPA_CLK_CORE_CGM_IPA_CORE_CFG) |= mcu_clk_para.ipa_core_freq.lvl;

	return 0;
}

static uint32 mcu_clk_config(void)
{
	/* config core0,1,2,3 */
	//set_mpll(mcu_clk_para.core0_freq.value, 0);
	REG32(REG_AON_SEC_APB_APCPU_ANANKE_CLK_CFG) &=
						~(BIT_AON_SEC_APB_CGM_CORE0_SEL(~0) |
						BIT_AON_SEC_APB_CGM_CORE0_DIV(~0));
	REG32(REG_AON_SEC_APB_APCPU_ANANKE_CLK_CFG) |= BIT_AON_SEC_APB_CGM_CORE0_SEL(1) |
						BIT_AON_SEC_APB_CGM_CORE1_SEL(1) |
						BIT_AON_SEC_APB_CGM_CORE2_SEL(1) |
						BIT_AON_SEC_APB_CGM_CORE3_SEL(1);

	/* config core4,5,6,7 */
	//set_mpll(mcu_clk_para.core4_freq.value, 1);
	REG32(REG_AON_SEC_APB_APCPU_PROMETHEUS_CLK_CFG) |= BIT_AON_SEC_APB_CGM_CORE4_SEL(2) |
						BIT_AON_SEC_APB_CGM_CORE5_SEL(2) |
						BIT_AON_SEC_APB_CGM_CORE6_SEL(2) |
						BIT_AON_SEC_APB_CGM_CORE7_SEL(2);

	/* ACE should configure before SCU */
	REG32(REG_AON_SEC_APB_APCPU_BUS_CLK_CFG) &= ~BIT_AON_SEC_APB_CGM_ACE_DIV(~0);
	REG32(REG_AON_SEC_APB_APCPU_BUS_CLK_CFG) |= BIT_AON_SEC_APB_CGM_ACE_DIV((CLK_SCU + CLK_ACE - 1)/CLK_ACE - 1);

	/* set mpll2 rate */
	//set_mpll(mcu_clk_para.clk_scu.value, 2);
	REG32(REG_AON_SEC_APB_APCPU_BUS_CLK_CFG) &= ~(BIT_AON_SEC_APB_CGM_SCU_SEL(~0) |
						BIT_AON_SEC_APB_CGM_SCU_DIV(~0));
	REG32(REG_AON_SEC_APB_APCPU_BUS_CLK_CFG) |= BIT_AON_SEC_APB_CGM_SCU_SEL(1);

	return 0;
}

static void misc_clk_config(void)
{
	/* AON usb clock select: 96M  */
	REG32(REG_AON_CLK_CORE_CGM_USB_CFG) = BIT_AON_CLK_CORE_CGM_USB_CFG_CGM_USB_SEL(3);

	/* AON usb suspend clock select: 1M  */
	REG32(REG_AON_CLK_CORE_CGM_USB_SUSPEND_CFG) = BIT_AON_CLK_CORE_CGM_USB_SUSPEND_CFG_CGM_USB_SUSPEND_SEL;

	/* IPA usb clock select: 24M */
	REG32(REG_IPA_CLK_CORE_CGM_USB_REF_CFG) = BIT_IPA_CLK_CORE_CGM_USB_REF_CFG_CGM_USB_REF_SEL;

	vsp_clk_config();
	mm_clk_config();
	gpu_clk_config();
	ai_clk_config();
	vdsp_clk_config();
	ipa_core_clk_config();
}

static uint32 clk_config(void)
{
    axi_clk_config();
    clk_periph_config();
    apb_clk_config();
    alg_io_clk_config();
    mcu_clk_config();
    misc_clk_config();
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
	REG32(REG_IPA_CLK_CORE_CGM_IPA_CORE_CFG) &= ~BIT_IPA_CLK_CORE_CGM_IPA_CORE_CFG_CGM_IPA_CORE_SEL(~0);
	REG32(REG_AP_CLK_CORE_CGM_VSP_CFG) &= ~BIT_AP_CLK_CORE_CGM_VSP_CFG_CGM_VSP_SEL(~0);
	REG32(REG_AON_CLK_CORE_CGM_AP_MM_CFG) &= ~BIT_AON_CLK_CORE_CGM_AP_MM_CFG_CGM_AP_MM_SEL(~0);
	REG32(REG_AON_CLK_CORE_CGM_AP_GPU_CFG) &= ~BIT_AON_CLK_CORE_CGM_AP_GPU_CFG_CGM_AP_GPU_SEL(~0);
	REG32(REG_AON_CLK_CORE_CGM_AP_AI_CFG) &= ~BIT_AON_CLK_CORE_CGM_AP_AI_CFG_CGM_AP_AI_SEL(~0);
	REG32(REG_AP_CLK_CORE_CGM_VDSP_CFG) &= ~BIT_AP_CLK_CORE_CGM_VDSP_CFG_CGM_VDSP_SEL(~0);
	REG32(REG_AON_CLK_CORE_CGM_AP_AXI_CFG) &= ~BIT_AON_CLK_CORE_CGM_AP_AXI_CFG_CGM_AP_AXI_SEL(~0);
	REG32(REG_AON_SEC_APB_APCPU_TOP_MISC_CLK_CFG) &=
		~(BIT_AON_SEC_APB_CGM_PERIPH_DIV(~0) |
				BIT_AON_SEC_APB_CGM_PERIPH_SEL(~0));
	REG32(REG_AON_CLK_CORE_CGM_AON_APB_CFG) =
		BIT_AON_CLK_CORE_CGM_AON_APB_CFG_CGM_AON_APB_SEL(4);
	REG32(REG_AP_CLK_CORE_CGM_AP_APB_CFG) &= ~(BIT_AP_CLK_CORE_CGM_AP_APB_CFG_CGM_AP_APB_SEL(~0));
	REG32(REG_AON_SEC_APB_APCPU_ANANKE_CLK_CFG) &=
		~(BIT_AON_SEC_APB_CGM_CORE0_SEL(~0) |
				BIT_AON_SEC_APB_CGM_CORE0_DIV(~0));
	REG32(REG_AON_SEC_APB_APCPU_BUS_CLK_CFG) &= ~(BIT_AON_SEC_APB_CGM_SCU_SEL(~0) |
			BIT_AON_SEC_APB_CGM_SCU_DIV(~0));
	REG32(REG_AON_SEC_APB_APCPU_BUS_CLK_CFG) &= ~BIT_AON_SEC_APB_CGM_ACE_DIV(~0);

	REG32(REG_PMU_APB_TWPLL_REL_CFG) &= ~BIT_PMU_APB_TWPLL_AP_SEL;

	/* rpll output 26m to twpll cannot use auto mode, the auto mode cannnot work, so use force mode */
	REG32(REG_ANLG_PHY_G5_ANALOG_BB_TOP_REG_SEL_CFG_0) |= BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_DIV_EN;
	REG32(REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_PERFOR) |= BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_ICP(7);
	REG32(REG_PMU_APB_LTEPLL_REL_CFG) |= BIT_PMU_APB_LTEPLL_REF_SEL(1);
	REG32(REG_PMU_APB_TWPLL_REL_CFG) |= BIT_PMU_APB_TWPLL_REF_SEL(1);
	REG32(REG_PMU_APB_TWPLL_REL_CFG) |= BIT_PMU_APB_TWPLL_AP_SEL;

	/* modify top dvfs clock source from TWPLL(default) to RCO */
	REG32(REG_AON_CLK_CORE_CGM_TOP_DVFS_CFG) &= ~BIT_AON_CLK_CORE_CGM_TOP_DVFS_CFG_CGM_TOP_DVFS_SEL(~0);
	REG32(REG_AON_CLK_CORE_CGM_TOP_DVFS_CFG) |= BIT_AON_CLK_CORE_CGM_TOP_DVFS_CFG_CGM_TOP_DVFS_SEL(2);

	/*all_pll_pd only rco bypass*/
	REG32(REG_PMU_APB_ALL_PLL_PD_RCO_BYP) |= BIT_PMU_APB_ALL_PLL_PD_RCO_BYP;
	/*RCO always on */
	REG32(REG_PMU_APB_RCO_REL_CFG) |= BIT_PMU_APB_RCO_FRC_ON;
}

void pll_sel_cfg(void)
{
	/* XTL sel */
	REG32(REG_PMU_APB_XTL0_REL_CFG) |= BIT_PMU_APB_XTL0_AP_SEL |
					BIT_PMU_APB_XTL0_WTLCP_SEL |
					BIT_PMU_APB_XTL0_PUBCP_SEL |
					BIT_PMU_APB_XTL0_AUDCP_SYS_SEL |
					BIT_PMU_APB_XTL0_PUB_SYS_SEL |
					BIT_PMU_APB_XTL0_SP_SYS_SEL |
					BIT_PMU_APB_XTL0_ESE_SEL |
					//BIT_PMU_APB_XTL0_TOP_DVFS_SEL |
					BIT_PMU_APB_XTL0_IPA_SEL;
	REG32(REG_PMU_APB_XTL0_REL_CFG) &= ~BIT_PMU_APB_XTL0_TOP_DVFS_SEL;

	REG32(REG_PMU_APB_XTL1_REL_CFG) &= ~(BIT_PMU_APB_XTL1_AP_SEL |
					BIT_PMU_APB_XTL1_WTLCP_SEL |
					BIT_PMU_APB_XTL1_PUBCP_SEL |
					BIT_PMU_APB_XTL1_AUDCP_SYS_SEL |
					BIT_PMU_APB_XTL1_PUB_SYS_SEL |
					BIT_PMU_APB_XTL1_SP_SYS_SEL |
					BIT_PMU_APB_XTL1_ESE_SEL |
					BIT_PMU_APB_XTL1_TOP_DVFS_SEL |
					BIT_PMU_APB_XTL1_IPA_SEL);

	REG32(REG_PMU_APB_XTLBUF0_REL_CFG) |= BIT_PMU_APB_XTLBUF0_AP_SEL |
					BIT_PMU_APB_XTLBUF0_WTLCP_SEL |
					BIT_PMU_APB_XTLBUF0_PUBCP_SEL |
					BIT_PMU_APB_XTLBUF0_AUDCP_SYS_SEL |
					BIT_PMU_APB_XTLBUF0_PUB_SYS_SEL |
					BIT_PMU_APB_XTLBUF0_SP_SYS_SEL |
					BIT_PMU_APB_XTLBUF0_ESE_SEL |
					//BIT_PMU_APB_XTLBUF0_TOP_DVFS_SEL |
					BIT_PMU_APB_XTLBUF0_IPA_SEL;
	REG32(REG_PMU_APB_XTLBUF0_REL_CFG) &= ~BIT_PMU_APB_XTLBUF0_TOP_DVFS_SEL;

	REG32(REG_PMU_APB_XTLBUF1_REL_CFG) &= ~(BIT_PMU_APB_XTLBUF1_AP_SEL |
					BIT_PMU_APB_XTLBUF1_WTLCP_SEL |
					BIT_PMU_APB_XTLBUF1_PUBCP_SEL |
					BIT_PMU_APB_XTLBUF1_AUDCP_SYS_SEL |
					BIT_PMU_APB_XTLBUF1_PUB_SYS_SEL |
					BIT_PMU_APB_XTLBUF1_SP_SYS_SEL |
					BIT_PMU_APB_XTLBUF1_ESE_SEL |
					BIT_PMU_APB_XTLBUF1_TOP_DVFS_SEL |
					BIT_PMU_APB_XTLBUF1_IPA_SEL);

	/* MPLL0 1 2 defalut select ap */

	/* DPLL0 default select all ,no sp */
	REG32(REG_PMU_APB_DPLL0_REL_CFG) |= BIT_PMU_APB_DPLL0_AP_SEL |
					BIT_PMU_APB_DPLL0_WTLCP_SEL |
					BIT_PMU_APB_DPLL0_PUBCP_SEL |
					BIT_PMU_APB_DPLL0_PUB_SYS_SEL |
					BIT_PMU_APB_DPLL0_IPA_SEL;

	/* DPLL1 same as DPLL0 */
	REG32(REG_PMU_APB_DPLL1_REL_CFG) |= BIT_PMU_APB_DPLL1_AP_SEL |
					BIT_PMU_APB_DPLL1_WTLCP_SEL |
					BIT_PMU_APB_DPLL1_PUBCP_SEL |
					BIT_PMU_APB_DPLL1_PUB_SYS_SEL |
					BIT_PMU_APB_DPLL1_IPA_SEL;

	/* ISPPLL select no sys at default */
	REG32(REG_PMU_APB_ISPPLL_REL_CFG) |= BIT_PMU_APB_ISPPLL_AP_SEL;
	/* GPLL select no sys at default */

	/* TWPLL select all */
	REG32(REG_PMU_APB_TWPLL_REL_CFG) |= BIT_PMU_APB_TWPLL_AP_SEL |
					BIT_PMU_APB_TWPLL_WTLCP_SEL |
					BIT_PMU_APB_TWPLL_PUBCP_SEL |
					BIT_PMU_APB_TWPLL_AUDCP_SYS_SEL |
					BIT_PMU_APB_TWPLL_PUB_SYS_SEL |
					BIT_PMU_APB_TWPLL_SP_SYS_SEL |
					BIT_PMU_APB_TWPLL_ESE_SEL |
					//BIT_PMU_APB_TWPLL_TOP_DVFS_SEL |
					BIT_PMU_APB_TWPLL_IPA_SEL;
	REG32(REG_PMU_APB_TWPLL_REL_CFG) &= ~BIT_PMU_APB_TWPLL_TOP_DVFS_SEL;

	/* RPLL select all */
	REG32(REG_PMU_APB_RPLL_REL_CFG) |= BIT_PMU_APB_RPLL_AP_SEL |
					BIT_PMU_APB_RPLL_WTLCP_SEL |
					BIT_PMU_APB_RPLL_PUBCP_SEL |
					BIT_PMU_APB_RPLL_AUDCP_SYS_SEL |
					BIT_PMU_APB_RPLL_PUB_SYS_SEL |
					BIT_PMU_APB_RPLL_SP_SYS_SEL |
					BIT_PMU_APB_RPLL_ESE_SEL |
					//BIT_PMU_APB_RPLL_TOP_DVFS_SEL |
					BIT_PMU_APB_RPLL_IPA_SEL;
	REG32(REG_PMU_APB_RPLL_REL_CFG) &= ~BIT_PMU_APB_RPLL_TOP_DVFS_SEL;

	/* LTEPLL select ap/wtlcp/audcp/pub/ipa */
	REG32(REG_PMU_APB_LTEPLL_REL_CFG) |= BIT_PMU_APB_LTEPLL_AP_SEL |
					BIT_PMU_APB_LTEPLL_WTLCP_SEL |
					BIT_PMU_APB_LTEPLL_AUDCP_SYS_SEL |
					BIT_PMU_APB_LTEPLL_PUB_SYS_SEL |
					BIT_PMU_APB_LTEPLL_IPA_SEL;

	/* RCO100M select all */
	REG32(REG_PMU_APB_RCO_REL_CFG ) |= BIT_PMU_APB_RCO_AP_SEL |
					BIT_PMU_APB_RCO_WTLCP_SEL |
					BIT_PMU_APB_RCO_PUBCP_SEL |
					BIT_PMU_APB_RCO_AUDCP_SEL |
					BIT_PMU_APB_RCO_PUB_SYS_SEL |
					BIT_PMU_APB_RCO_SP_SYS_SEL |
					BIT_PMU_APB_RCO_ESE_SEL |
					BIT_PMU_APB_RCO_TOP_DVFS_SEL |
					BIT_PMU_APB_RCO_IPA_SEL;
}

void enable_auto_gate_for_lp(void)
{
}

static void rco100m_config()
{
	/* rco default controlled by aon reg */
	REG32(REG_AON_APB_APB_EB0) |= BIT_AON_APB_RC100M_CAL_EB;
	REG32(REG_AON_APB_APB_RST0) |= BIT_AON_APB_RC100M_CAL_SOFT_RST;
	udelay(30);
	REG32(REG_AON_APB_APB_RST0) &= ~BIT_AON_APB_RC100M_CAL_SOFT_RST;
	REG32(REG_AON_APB_RC100M_CFG) |= BIT_AON_APB_RC100M_AUTO_GATE_EN;
	//REG32(REG_AON_APB_RTC4M_0_CFG) |= BIT_AON_APB_RTC4M0_FORCE_EN;
	REG32(REG_AON_APB_RC100M_CFG) |= BIT_AON_APB_RC100M_CAL_START;
	while(!(REG32(REG_AON_APB_RC100M_CFG) & BIT_AON_APB_RC100M_CAL_DONE));
}
#endif

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

void reset_mm_subsystem(void)
{
	REG32(REG_AON_APB_APB_EB1) |= BIT_AON_APB_ANA_EB;
	REG32(REG_PMU_APB_PD_MM_TOP_CFG) &= ~(BIT_PMU_APB_PD_MM_TOP_FORCE_SHUTDOWN | BIT_PMU_APB_PD_MM_TOP_AUTO_SHUTDOWN_EN);
	REG32(REG_AON_APB_APB_EB0) |= BIT_AON_APB_MM_EB;
	udelay(10000);
	REG32(REG_MM_AHB_MM_QOS) = BIT_MM_AHB_AR_QOS_THRESHOLD_MM(0xA) | BIT_MM_AHB_AW_QOS_THRESHOLD_MM(0xA);
	REG32(REG_AON_APB_APB_RST1) |= BIT_AON_APB_ANA_SOFT_RST;
	udelay(100);
	REG32(REG_AON_APB_APB_RST1) &= ~BIT_AON_APB_ANA_SOFT_RST;
}

extern void sdram_init(void);
extern int sc27xx_adc_init(void);

void Chip_Init (void) /*lint !e765 "Chip_Init" is used by init.s entry.s*/
{
	local_enable_scr_el3_ea();
	local_async_enable();
	timer_init();
#if !defined(CONFIG_FPGA)
#ifdef CONFIG_NAND_SPL
	reset_mm_subsystem();
#endif
	REG32(REG_AON_APB_APB_EB1) |= BIT_AON_APB_ANA_EB;
	rco100m_config();
	sci_adi_init();
	pll_sel_cfg();
	pll_ref_sel();
	regulator_init();
	soc_voltage_init();
	mcu_init();
	sc27xx_adc_init();
	enable_auto_gate_for_lp();
	sdram_init();
	sprd_ptm_init();
	sprd_log();
#endif
}

