
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

#define MPLL_REFIN 26
#define DPLL_REFIN 26
#define REFIN 26
#define LPLL_REFIN 260
#define NINT(FREQ,REFIN)	(FREQ/REFIN)
#define KINT(FREQ,REFIN)	((FREQ-(FREQ/REFIN)*REFIN)*(BIT_ANLG_PHY_G4_ANALOG_MPLL_THM_TOP_MPLL_KINT(~0x0)+1)/REFIN)

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

	.debug_flags[0].name = "d_flag0",
	.debug_flags[1].name = "d_flag1",
	.debug_flags[2].name = "d_flag2",
	.debug_flags[3].name = "d_flag3",

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
#endif

    delay();
    return 0;
}

static uint32 SetMPllClk(uint32 clk)
{
	delay();
	delay();
	delay();
	delay();
	delay();

	return 0;
}

static uint32 ApbClkConfig(void)
{
	return 0;
}

static uint32 AxiClkConfig(void)
{
	return 0;
}

static uint32 DbgClkConfig(uint32 arm_clk)
{
	return 0;
}

static uint32 McuClkConfig(uint32 arm_clk)
{
	return 0;
}

static void MiscClkConfig(void)
{
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
}

void pll_sel_cfg(void)
{
}

void enable_auto_gate_for_lp(void)
{
}

extern void sdram_init(void);
void Chip_Init (void) /*lint !e765 "Chip_Init" is used by init.s entry.s*/
{
	local_enable_scr_el3_ea();
	local_async_enable();
	timer_init();
#if !defined(CONFIG_FPGA)
	pll_ref_sel();
	sci_adi_init();
	pll_sel_cfg();
	MCU_Init();
	enable_auto_gate_for_lp();
	regulator_init();
//	sdram_init();
#endif
}

