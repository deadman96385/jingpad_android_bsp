
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

#define MPLL_REFIN 26
#define DPLL_REFIN 26
#define REFIN 26
#define LPLL_REFIN 260
#define NINT(FREQ,REFIN)	(FREQ/REFIN)
#define KINT(FREQ,REFIN)	((FREQ-(FREQ/REFIN)*REFIN)*(BIT_ANA_APB_MPLL0_KINT(~0x0)+1)/REFIN)


#if defined(CONFIG_DUAL_DDR)
extern void noc_init(void);
#endif

#if defined(CONFIG_CLK_PARA)
#include <asm/arch/clk_para_config.h>
const MCU_CLK_PARA_T mcu_clk_para=
{
    .magic_header = MAGIC_HEADER,
    .version = CONFIG_PARA_VERSION,
	.clk_vol_unit_count = 18,
	.clk_list_unit_count = 4,

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

    .dcdc_arm0.name = "D*ARM0",//dcdc_arm0,1,core
	.dcdc_arm0.value = DCDC_ARM0,

    .dcdc_arm1.name = "D*ARM1",
    .dcdc_core.name = "D*CORE",
    .dcdc_core.value = DCDC_CORE,
	.dcdc_mem.name = "D*MEM",
	.dcdc_gen.name = "D*GEN",
#ifdef DCDC_ARM1
	.dcdc_arm1.value = DCDC_ARM1,
#endif

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
#if defined(CONFIG_ADIE_SC2723) || defined(CONFIG_ADIE_SC2723S)
	.debug_flags[0].value = 0x3FFFFFF1, //0x3FFFFFFF
#endif

	.axi_freq.name = "C#AXI",//clk_axi
    .axi_freq.lvl_count = CLK_AXI_LEVEL,
    .axi_freq.lvl = CLK_AXI_LEVEL_ID,
	.axi_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,//all c# clk,the max level_count,now max=6
	.axi_freq.clk_list = {26000000,76800000,128000000,256000000},

	.cci_freq.name = "C#CCI",//clk_cci
	.cci_freq.lvl_count = CLK_CCI_LEVEL,
	.cci_freq.lvl = CLK_CCI_LEVEL_ID,
	.cci_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.cci_freq.clk_list = {26000000,384000000,614400000,768000000},

    .ap_apb_freq.name = "C#AP_APB",//clk_apb
    .ap_apb_freq.lvl_count = CLK_APB_LEVEL,
    .ap_apb_freq.lvl = CLK_APB_LEVEL_ID,
	.ap_apb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.ap_apb_freq.clk_list = {26000000,64000000,96000000,128000000},

    .aon_apb_freq.name = "C#AONAPB",//clk_aon_apb
    .aon_apb_freq.lvl_count = CLK_AON_APB_LEVEL,
    .aon_apb_freq.lvl = CLK_AON_APB_LEVEL_ID,
	.aon_apb_freq.lvl_count_max = CLK_LEVEL_COUNT_MAX,
	.aon_apb_freq.clk_list = {25000000,26000000,100000000,96000000,128000000,153600000},

	.magic_end = MAGIC_END
};
#endif
#if defined(CONFIG_AUTODETECT_SS)
#define UART1_TX_BUF_ADDR 0X70100000
#define UART1_TX_BUF_CNT ((REG32(0x70100000 + 0xc)>>8)&0xff)

#ifndef NULL
#define NULL ((void *)0)
#endif


void serial_print(const char *string)
{
    char *s1 = NULL;

    s1 = string;

    while (*s1 != NULL)
    {
		//wait until uart1 tx fifo empty
		while(UART1_TX_BUF_CNT != 0);

		//put out char by uart1 tx fifo
		REG32(UART1_TX_BUF_ADDR) = *s1;
		s1++;
	}
}

void uitoa(int i, char *string)
{
        int power=0,j=0;

        j=i;
        for( power=1;j>10;j/=10)
                power*=10;

        for(;power>0;power/=10)
        {
                *string++='0'+i/power;
                i%=power;
        }
        *string='\0';
}

int mcu_strcmp(char* str1, char* str2){
    while(*str1 && *str2 && *str1==*str2){
        ++str1;
        ++str2;
    }
    return *str1-*str2;
}

char ss_uid[9][10] = {"P6U79711",
		"P6U79712",
		"P4TK1116",
		"P4TK1117",
		"P8B77012",
		"P8B77013",
		"P4TK4722",
		"P4TK4723",
		"END"};
#endif
static void delay()
{
    volatile uint32 i;
    for (i=0; i<0x100; i++);
}

struct whale_ibias_table {
	unsigned long rate;
	u8 ibias;
};
#ifdef CONFIG_WHALE
#define WHALE_PLL_MAX_RATE		(0xFFFFFFFF)

struct whale_ibias_table whale_adjustable_pll_table[] = {
	{
		.rate = 936000000,
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
		.rate = WHALE_PLL_MAX_RATE,
		.ibias = 0x2,
	},
};

struct whale_ibias_table whale_mpll1_table[] = {
	{
		.rate = 1404000000,
		.ibias = 0x0,
	},
	{
		.rate = 1872000000,
		.ibias = 0x1,
	},
	{
		.rate = 2548000000,
		.ibias = 0x2,
	},
	{
		.rate = WHALE_PLL_MAX_RATE,
		.ibias = 0x2,
	},
};
#elif defined(CONFIG_WHALE2)
#define WHALE_PLL_MAX_RATE		(0xFFFFFFFF)
struct whale_ibias_table whale2_adjustable_pll1_table[] = {//gpll/lpll/dpll/rpll/cpll
	{
		.rate = 780000000,
		.ibias = 0x0,
	},
	{
		.rate = 988000000,
		.ibias = 0x1,
	},
	{
		.rate = 1196000000,
		.ibias = 0x2,
	},
	{
		.rate = WHALE_PLL_MAX_RATE,
		.ibias = 0x2,
	},
};

struct whale_ibias_table whale2_adjustable_pll2_table[] = {//twpll/mpll0/mpll1
	{
		.rate = 1638000000,
		.ibias = 0x0,
	},
	{
		.rate = 2080000000,
		.ibias = 0x1,
	},
	{
		.rate = 2600000000,
		.ibias = 0x2,
	},
	{
		.rate = WHALE_PLL_MAX_RATE,
		.ibias = 0x2,
	},
};

struct whale_ibias_table whale2_adjustable_upll_table[] = {
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
		.rate = WHALE_PLL_MAX_RATE,
		.ibias = 0x2,
	},
};

#endif

#if defined(CONFIG_WHALE2)
void Reset_twpll_config(uint32 clk)
{
	uint32 clk_cfg1_reg, clk_cfg2_reg, clk_cfg1, clk_cfg2;
	uint32 nint, kint;
	struct whale_ibias_table *itable;

	clk_cfg1_reg = REG_ANA_APB_TWPLL_CFG1;
	clk_cfg2_reg = REG_ANA_APB_TWPLL_CFG2;
	clk = clk /1000000;
	itable = whale2_adjustable_pll2_table;
	clk_cfg1 = REG32(clk_cfg1_reg);
	clk_cfg1 |= ( BIT_ANA_APB_TWPLL_SDM_EN) | (BIT_ANA_APB_TWPLL_DIV_S );

	nint = BIT_ANA_APB_TWPLL_NINT(NINT(clk,REFIN));
	kint = BIT_ANA_APB_TWPLL_KINT(KINT(clk,REFIN));
	clk_cfg2 = REG32(clk_cfg2_reg);
	clk_cfg2 &= ~(BIT_ANA_APB_TWPLL_NINT(~0x0) | BIT_ANA_APB_TWPLL_KINT(~0x0));
	clk_cfg2 |= nint | kint;
	/* set ibias */
	clk_cfg1 &=~BIT_ANA_APB_TWPLL_IBIAS(3);
	for (; itable->rate <= WHALE_PLL_MAX_RATE; itable++) {
		if (clk*1000000 <= itable->rate) {
			clk_cfg1 |= BIT_ANA_APB_TWPLL_IBIAS(itable->ibias);
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
	while(!(REG32(clk_cfg1_reg) & BIT_ANA_APB_TWPLL_LOCK_DONE));
}

void Reset_lpll0_config(uint32 clk)
{
	uint32 clk_cfg1_reg, clk_cfg2_reg, clk_cfg1, clk_cfg2;
	uint32 nint, kint;
	struct whale_ibias_table *itable;

	clk_cfg1_reg = REG_ANA_APB_LTEPLL_CFG1;
	clk_cfg2_reg = REG_ANA_APB_LTEPLL_CFG2;
	clk = clk /100000;

	itable = whale2_adjustable_pll1_table;
	clk_cfg1 = REG32(clk_cfg1_reg);
	clk_cfg1 |= ( BIT_ANA_APB_LPLL0_SDM_EN) | (BIT_ANA_APB_LPLL0_DIV_S );

	nint = BIT_ANA_APB_LPLL0_NINT(NINT(clk,LPLL_REFIN));
	kint = BIT_ANA_APB_LPLL0_KINT(KINT(clk,LPLL_REFIN));
	clk_cfg2 = REG32(clk_cfg2_reg);
	clk_cfg2 &= ~(BIT_ANA_APB_LPLL0_NINT(~0x0) | BIT_ANA_APB_LPLL0_KINT(~0x0));
	clk_cfg2 |= nint | kint;
	/* set ibias */
	clk_cfg1 &=~BIT_ANA_APB_LPLL0_IBIAS(3);
	for (; itable->rate <= WHALE_PLL_MAX_RATE; itable++) {
		if (clk*1000000 <= itable->rate) {
			clk_cfg1 |= BIT_ANA_APB_LPLL0_IBIAS(itable->ibias);
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
	while(!(REG32(clk_cfg1_reg) & BIT_ANA_APB_LPLL0_LOCK_DONE));
}


void Reset_lpll1_config(uint32 clk)
{
	uint32 clk_cfg1_reg, clk_cfg2_reg, clk_cfg1, clk_cfg2;
	uint32 nint, kint;
	struct whale_ibias_table *itable;

	clk_cfg1_reg = REG_ANA_APB_LTECAPLL_CFG1;
	clk_cfg2_reg = REG_ANA_APB_LTECAPLL_CFG2;
	clk = clk /100000;

	itable = whale2_adjustable_pll1_table;
	clk_cfg1 = REG32(clk_cfg1_reg);
	clk_cfg1 |= ( BIT_ANA_APB_LPLL1_SDM_EN) | (BIT_ANA_APB_LPLL1_DIV_S );

	nint = BIT_ANA_APB_LPLL1_NINT(NINT(clk,LPLL_REFIN));
	kint = BIT_ANA_APB_LPLL1_KINT(KINT(clk,LPLL_REFIN));
	clk_cfg2 = REG32(clk_cfg2_reg);
	clk_cfg2 &= ~(BIT_ANA_APB_LPLL1_NINT(~0x0) | BIT_ANA_APB_LPLL1_KINT(~0x0));
	clk_cfg2 |= nint | kint;
	/* set ibias */
	clk_cfg1 &=~BIT_ANA_APB_LPLL1_IBIAS(3);
	for (; itable->rate <= WHALE_PLL_MAX_RATE; itable++) {
		if (clk*1000000 <= itable->rate) {
			clk_cfg1 |= BIT_ANA_APB_LPLL1_IBIAS(itable->ibias);
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

void Reset_cppll_config(uint32 clk)
{
	uint32 clk_cfg1_reg, clk_cfg2_reg, clk_cfg1, clk_cfg2;
	uint32 nint, kint;
	struct whale_ibias_table *itable;

	clk_cfg1_reg = REG_ANA_APB_CPPLL_CFG1;
	clk_cfg2_reg = REG_ANA_APB_CPPLL_CFG2;
	clk = clk /1000000;
	itable = whale2_adjustable_pll1_table;
	clk_cfg1 = REG32(clk_cfg1_reg);
	clk_cfg1 |= ( BIT_ANA_APB_CPPLL_SDM_EN) | (BIT_ANA_APB_CPPLL_DIV_S );

	nint = BIT_ANA_APB_CPPLL_NINT(NINT(clk,REFIN));
	kint = BIT_ANA_APB_CPPLL_KINT(0x39F96);
	clk_cfg2 = REG32(clk_cfg2_reg);
	clk_cfg2 &= ~(BIT_ANA_APB_CPPLL_NINT(~0x0) | BIT_ANA_APB_CPPLL_KINT(~0x0));
	clk_cfg2 |= nint | kint;
	/* set ibias */
	clk_cfg1 &=~BIT_ANA_APB_CPPLL_IBIAS(3);
	for (; itable->rate <= WHALE_PLL_MAX_RATE; itable++) {
		if (clk*1000000 <= itable->rate) {
			clk_cfg1 |= BIT_ANA_APB_CPPLL_IBIAS(itable->ibias);
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
#endif

static uint32 SetBigLitMPllClk(uint32 clk, uint32 litflag)//1:lit core  0:big core
{
	uint32 clk_cfg1_reg, refin, clk_cfg2_reg, clk_cfg1, clk_cfg2;
	uint32 nint, kint, fvco;
	struct whale_ibias_table *itable;

	clk = clk/1000000;

	if (litflag) {
		clk_cfg1_reg = REG_ANA_APB_MPLL0_CFG0;
		clk_cfg2_reg = REG_ANA_APB_MPLL0_CFG1;
	#if defined(CONFIG_WHALE2)
		if((CLK_1200M/1000000) > clk){
			REG32(REG_ANA_APB_MPLL0_CFG1)|= BIT_ANA_APB_MPLL0_POSTDIV;//set postdiv
			refin = MPLL_REFIN / 2;
			fvco = clk * 2000000;
		}
		else{
			REG32(REG_ANA_APB_MPLL0_CFG1)&= ~BIT_ANA_APB_MPLL0_POSTDIV;//clr postdiv
			refin = MPLL_REFIN;
			fvco = clk * 1000000;
		}
		itable = whale2_adjustable_pll2_table;
	#else
		refin = MPLL_REFIN;
		itable = whale_adjustable_pll_table;
		fvco = clk * 1000000;
	#endif
	delay();

	clk_cfg1 = REG32(clk_cfg1_reg);
	clk_cfg1 |= ( BIT_ANA_APB_MPLL0_SDM_EN) | ( BIT_ANA_APB_MPLL0_DIV_S);

	nint = BIT_ANA_APB_MPLL0_NINT(NINT(clk,refin));
	kint = BIT_ANA_APB_MPLL0_KINT(KINT(clk,refin));
	clk_cfg2 = REG32(clk_cfg2_reg);
	clk_cfg2 &= ~(BIT_ANA_APB_MPLL0_NINT(~0x0) | BIT_ANA_APB_MPLL0_KINT(~0x0));
	clk_cfg2 |= nint | kint;
	/* set ibias */
	clk_cfg1 &=~BIT_ANA_APB_MPLL0_IBIAS(3);
	for (; itable->rate <= WHALE_PLL_MAX_RATE; itable++) {
		/* ibias caculation according to fvco which is recaculated by
		 * postdiv */
		if (fvco <= itable->rate) {
			clk_cfg1 |= BIT_ANA_APB_MPLL0_IBIAS(itable->ibias);
			break;
		}
	}
	} else {
		clk_cfg1_reg = REG_ANA_APB_MPLL1_CFG0;
		clk_cfg2_reg = REG_ANA_APB_MPLL1_CFG1;
		refin = MPLL_REFIN;
	#if defined(CONFIG_WHALE2)
		itable = whale2_adjustable_pll2_table;
	#else
		itable = whale_mpll1_table;
	#endif
	delay();

	clk_cfg1 = REG32(clk_cfg1_reg);
	clk_cfg1 |= ( BIT_ANA_APB_MPLL1_SDM_EN) | ( BIT_ANA_APB_MPLL1_DIV_S);

	nint = BIT_ANA_APB_MPLL1_NINT(NINT(clk,refin));
	kint = BIT_ANA_APB_MPLL1_KINT(KINT(clk,refin));
	clk_cfg2 = REG32(clk_cfg2_reg);
	clk_cfg2 &= ~(BIT_ANA_APB_MPLL1_NINT(~0x0)
			| BIT_ANA_APB_MPLL1_KINT(~0x0)
			| BIT_ANA_APB_MPLL1_PREDIV);
	clk_cfg2 |= nint | kint;
	/* set ibias */
	clk_cfg1 &=~BIT_ANA_APB_MPLL1_IBIAS(3);
	for (; itable->rate <= WHALE_PLL_MAX_RATE; itable++) {
		if (clk*1000000 <= itable->rate) {
			clk_cfg1 |= BIT_ANA_APB_MPLL1_IBIAS(itable->ibias);
			break;
		}
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
	SetBigLitMPllClk(clk, 1);//1:lit core
	SetBigLitMPllClk(big_clk, 0);//0:big core
	return 0;
}

static uint32 SetDpllClk(uint32 clk, uint32 dnum)
{
	uint32 clk_cfg1_reg, clk_cfg2_reg, clk_cfg1, clk_cfg2;
	uint32 nint, kint;
	struct whale_ibias_table *itable;

	clk = clk/1000000;

	if (dnum == 0) {
		clk_cfg1_reg = 0x40400034;
		clk_cfg2_reg = 0x40400038;
	} else {
		clk_cfg1_reg = 0x4040003c;
		clk_cfg2_reg = 0x40400040;
	}
#if defined(CONFIG_WHALE2)
	itable = whale2_adjustable_pll1_table;
#else
	itable = whale_adjustable_pll_table;
#endif
	/*clk_cfg1 = REG32(clk_cfg1_reg);
	clk_cfg1 |= (1 << 13);
	REG32(clk_cfg1_reg) = clk_cfg1;*/
	delay();

	clk_cfg1 = REG32(clk_cfg1_reg);
	if (dnum == 0)
		clk_cfg1 |= (1 << 25) | (1 << 27);
	else
		clk_cfg1 |= (1 << 24) | (1 << 26);

	nint = (NINT(clk,26)&0x3f)<<24;
	kint = KINT(clk, 26) & 0xfffff;
	clk_cfg2 = REG32(clk_cfg2_reg);
	clk_cfg2 &= ~(0x3f << 24);
	clk_cfg2 &= ~(0xfffff);
	clk_cfg2 |= nint | kint;
	/* set ibias */
	if (dnum == 0)
		clk_cfg1 &= ~(3 << 16);
	else
		clk_cfg1 &= ~(3 << 17);
	for (; itable->rate == WHALE_PLL_MAX_RATE; itable++) {
		if (clk*1000000 < itable->rate) {
			clk_cfg1 |= (itable->ibias << 16);
		}
	}

	REG32(clk_cfg1_reg) = clk_cfg1;
	REG32(clk_cfg2_reg) = clk_cfg2;

	delay();
	delay();
	delay();
	delay();
	delay();

	REG32(clk_cfg1_reg) &= ~(1 << 13);

	return 0;
}

static uint32 DpllClkConfig(uint32 clk)
{
	/*SetDpllClk(clk, 0);
	SetDpllClk(clk, 1);*/
}

#if defined(CONFIG_VOL_PARA)

#if defined(CONFIG_DUALPHASE) && defined(CONFIG_ADIE_SC2731R)
/*
*DCDCARM0/DCDCAR1 DCDCCORE/DCDCGPU dualphase initialize
*/
static void dcdc_dualphase_init(void)
{
	uint32_t reg_val;
#ifdef AUTO_SEL_DUALPHASE
/*
*dcdc dcdc_arm0/dcdc_arm1 dualphase initialize
*/
	ANA_REG_BIC(ANA_REG_GLB_DCDC_ARM0_REG1,BIT_DCDC_ARM0_DUALSEL);
	ANA_REG_OR(ANA_REG_GLB_DCDC_ARM1_REG1,BIT_DCDC_ARM1_DUALSEL);
	ANA_REG_OR(ANA_REG_GLB_DCDC_ARM1_REG2,BIT_DCDC_ARM1_APSEN);
	ANA_REG_BIC(ANA_REG_GLB_DCDC_ARM1_REG2,BIT_DCDC_ARM1_DPSC);

	ANA_REG_MSK_OR(ANA_REG_GLB_DCDC_ARM1_REG2,BITS_DCDC_ARM1_APSDELAY(0x1),BITS_DCDC_ARM1_APSDELAY(~0U));

	ANA_REG_MSK_OR(ANA_REG_GLB_DCDC_DUALPHASE_REG,BITS_DCDC_APS_ARM(0x24),BITS_DCDC_APS_ARM(~0U));

	delay();
/*
*dcdc dcdc_core/dcdc_gpu dualphase initialize
*/
	ANA_REG_BIC(ANA_REG_GLB_DCDC_CORE_REG1,BIT_DCDC_CORE_DUALSEL);
	ANA_REG_OR(ANA_REG_GLB_DCDC_GPU_REG1,BIT_DCDC_GPU_DUALSEL);
	ANA_REG_OR(ANA_REG_GLB_DCDC_CORE_REG2,BIT_DCDC_CORE_APSEN);
	ANA_REG_BIC(ANA_REG_GLB_DCDC_CORE_REG2,BIT_DCDC_CORE_DPSC);

	ANA_REG_MSK_OR(ANA_REG_GLB_DCDC_CORE_REG2,BITS_DCDC_CORE_APSDELAY(0x1),BITS_DCDC_CORE_APSDELAY(~0U));
	ANA_REG_MSK_OR(ANA_REG_GLB_DCDC_DUALPHASE_REG,BITS_DCDC_APS_CORE(0x24),BITS_DCDC_APS_CORE(~0U));
#else
/*
 *force dualphase
 */

/*
*dcdc dcdc_arm0/dcdc_arm1 force dualphase initialize
*/
	ANA_REG_OR(ANA_REG_GLB_DCDC_ARM1_REG1,BIT_DCDC_ARM1_DUALSEL);
	ANA_REG_BIC(ANA_REG_GLB_DCDC_ARM1_REG2,BIT_DCDC_ARM1_APSEN);
	ANA_REG_BIC(ANA_REG_GLB_DCDC_ARM1_REG2,BIT_DCDC_ARM1_DPSC);

/*
*dcdc dcdc_core/dcdc_gpu force dualphase initialize
*/
	ANA_REG_OR(ANA_REG_GLB_DCDC_GPU_REG1,BIT_DCDC_GPU_DUALSEL);
	ANA_REG_BIC(ANA_REG_GLB_DCDC_CORE_REG2,BIT_DCDC_CORE_APSEN);
	ANA_REG_BIC(ANA_REG_GLB_DCDC_CORE_REG2,BIT_DCDC_CORE_DPSC);

#endif

/*
 *PFMAD & PDRSLOW initialize
 * */
	ANA_REG_OR(ANA_REG_GLB_DCDC_ARM0_REG1,BITS_DCDC_ARM0_PFMAD(2));
	ANA_REG_OR(ANA_REG_GLB_DCDC_ARM0_REG0,BITS_DCDC_ARM0_PDRSLOW(1));
	ANA_REG_OR(ANA_REG_GLB_DCDC_ARM1_REG1,BITS_DCDC_ARM1_PFMAD(2));
	ANA_REG_OR(ANA_REG_GLB_DCDC_ARM1_REG0,BITS_DCDC_ARM1_PDRSLOW(1));
	ANA_REG_OR(ANA_REG_GLB_DCDC_CORE_REG1,BITS_DCDC_CORE_PFMAD(2));
	ANA_REG_OR(ANA_REG_GLB_DCDC_CORE_REG0,BITS_DCDC_CORE_PDRSLOW(1));
	ANA_REG_OR(ANA_REG_GLB_DCDC_GPU_REG1,BITS_DCDC_GPU_PFMAD(2));
	ANA_REG_OR(ANA_REG_GLB_DCDC_GPU_REG0,BITS_DCDC_GPU_PDRSLOW(1));
}
#endif

#if defined(CONFIG_AUTODETECT_SS)
static u32 judge_corner_ss()
{
	u32 block0, block1;
	u32 x, y, wafer_id;
	u32 LOTID_0, LOTID_1, LOTID_2, LOTID_3, LOTID_4, LOTID_5;
	char buf[20];
	char *p = buf;
	u32 count = 0,ss =0;
	block0 = ddie_efuse_read(0);
	block1 = ddie_efuse_read(1);

	y = block1 & 0x7F;
	x = (block1 >> 7) & 0x7F;
	wafer_id = (block1 >> 14) & 0x1F;
	LOTID_0 = (block1 >> 19) & 0x3F;
	LOTID_1 = (block1 >> 25) & 0x3F;
	LOTID_2 = block0 & 0x3F;
	LOTID_3 = (block0 >> 6) & 0x3F;
	LOTID_4 = (block0 >> 12) & 0x3F;
	LOTID_5 = (block0 >> 18) & 0x3F;
	*(p++) = LOTID_5 + 48;
	*(p++) = LOTID_4 + 48;
	*(p++) = LOTID_3 + 48;
	*(p++) = LOTID_2 + 48;
	*(p++) = LOTID_1 + 48;
	*(p++) = LOTID_0 + 48;

	uitoa(wafer_id,p);

	do
	{
	serial_print(ss_uid[count]);
	if( 0 == mcu_strcmp(ss_uid[count],buf)){
		serial_print(buf);
		serial_print(" ss corner boost 100mv\n");
		ss = 1;
		break;
		}
	}while(0 != mcu_strcmp(ss_uid[count++],"END"));

	return ss;
}
#endif

static uint32 ArmCoreConfig(uint32 arm_clk)
{
    uint32 dcdc_arm;
#if defined(CONFIG_DUALPHASE) && defined(CONFIG_ADIE_SC2731R)
	dcdc_dualphase_init();
#endif
#if defined(CONFIG_VOL_PARA)
    regulator_set_voltage("vddarm0",mcu_clk_para.dcdc_arm0.value);
    regulator_set_voltage("vddarm1",mcu_clk_para.dcdc_arm1.value);
#if defined(CONFIG_AUTODETECT_SS)
if (judge_corner_ss())
    regulator_set_voltage("vddcore",mcu_clk_para.dcdc_core.value + 100);
else
#endif
    regulator_set_voltage("vddcore",mcu_clk_para.dcdc_core.value);
    regulator_set_voltage("vddmem",mcu_clk_para.dcdc_mem.value);
    regulator_set_voltage("vddgen",mcu_clk_para.dcdc_gen.value);

    REG32(REG_AP_APB_APB_EB) |= BIT_AP_APB_CKG_EB;
#endif
    delay();
    return 0;
}

#endif

static uint32 ApbClkConfig()
{
#if defined(CONFIG_CLK_PARA)
	uint32 apb_cfg;
	apb_cfg  = REG32(0x20000020);
	apb_cfg &=~3;
	apb_cfg |= mcu_clk_para.ap_apb_freq.lvl;  //whale2:  0:26M 1:64M 2:96M 3:128M
	REG32(0x20000020) = apb_cfg;

	apb_cfg = REG32(0x402d0230);
	apb_cfg &=~7;
	apb_cfg |= mcu_clk_para.aon_apb_freq.lvl;  //whale2:  0:26M  4:128M 5:153.6m
	REG32(0x402d0230) = apb_cfg;
#else
	uint32 apb_cfg, i; 
	apb_cfg = REG32(0x20000020); 
	apb_cfg &= ~3; 
	/* ap apb select 128m */
	apb_cfg |= 3;
	REG32(0x20000020) = apb_cfg; 

	apb_cfg = REG32(0x402d0230); 
	apb_cfg &= ~7; 
	/* aon apb select 153.6m */
	apb_cfg |= 5;
	REG32(0x402d0230) = apb_cfg; 

	for (i = 0; i < 0x100; i++) { 
	}
#endif
	delay();
	return 0;
}

static uint32 AxiClkConfig(uint32 arm_clk)
{
#if defined(CONFIG_CLK_PARA)
	uint32 clk_cfg;

	clk_cfg = REG32(0x402d0324);
	clk_cfg &= ~3;
	clk_cfg |= mcu_clk_para.axi_freq.lvl;//whale2 3:256M,whale 3:256M
	REG32(0x402d0324) = clk_cfg;
#else
	uint32 clk_cfg;

	clk_cfg = REG32(0x402d0324);
	clk_cfg &= ~3;
	clk_cfg |= 3;
	REG32(0x402d0324) = clk_cfg;
#endif
	delay();
	return 0;
}

static uint32 DbgClkConfig(uint32 arm_clk,uint32 arm_big_clk)
{
#if defined(CONFIG_CLK_PARA)
	uint32 clk_cfg,freq1,freq2,freq3;

	clk_cfg = REG32(REG_AON_SEC_APB_CA53_LIT_CLK_CFG);//lit ACE/DBG/ATB
	clk_cfg &= ~(7 << 8 | 7 << 12 | 7 << 16);
	freq1 = mcu_clk_para.ace0_freq.value;
	freq2 = mcu_clk_para.dgb0_freq.value;
	freq3 = mcu_clk_para.atb0_freq.value;

	clk_cfg |= (arm_clk/freq1-1+ ((arm_clk%freq1)? 1:0))<<8;
	clk_cfg |= (arm_clk/freq2-1+ ((arm_clk%freq2)? 1:0))<<12;
	clk_cfg |= (arm_clk/freq3-1+ ((arm_clk%freq3)? 1:0))<<16;
	REG32(REG_AON_SEC_APB_CA53_LIT_CLK_CFG) = clk_cfg;

	clk_cfg = REG32(REG_AON_SEC_APB_CA53_BIG_CLK_CFG);//big ACE/DBG/ATB
	clk_cfg &= ~(7 << 8 | 7 << 12 | 7 << 16);
	freq1 = mcu_clk_para.ace1_freq.value;
	freq2 = mcu_clk_para.dgb1_freq.value;
	freq3 = mcu_clk_para.atb1_freq.value;

	clk_cfg |= (arm_big_clk/freq1-1+ ((arm_big_clk%freq1)? 1:0))<<8;
	clk_cfg |= (arm_big_clk/freq2-1+ ((arm_big_clk%freq2)? 1:0))<<12;
	clk_cfg |= (arm_big_clk/freq3-1+ ((arm_big_clk%freq3)? 1:0))<<16;
	REG32(REG_AON_SEC_APB_CA53_BIG_CLK_CFG) = clk_cfg;
#else
	uint32 clk_cfg;

	clk_cfg = REG32(REG_AON_SEC_APB_CA53_LIT_CLK_CFG);
	clk_cfg &= ~(7 << 8 | 7 << 12 | 7 << 16);
	clk_cfg |= (1 << 8) | (3 << 12) | (3 << 16);
	REG32(REG_AON_SEC_APB_CA53_LIT_CLK_CFG) = clk_cfg;

	clk_cfg = REG32(REG_AON_SEC_APB_CA53_BIG_CLK_CFG);
	clk_cfg &= ~(7 << 8 | 7 << 12 | 7 << 16);
	clk_cfg |= (1 << 8) | (3 << 12) | (3 << 16);
	REG32(REG_AON_SEC_APB_CA53_BIG_CLK_CFG) = clk_cfg;
#endif
    delay();
    return 0;
}

static uint32 McuClkConfig(uint32 arm_clk,uint32 arm_big_clk)
{
	uint32 clk_cfg;

	SetMPllClk(arm_clk,arm_big_clk);
	delay();

	/* little cpu switch to mpll0 */
	clk_cfg = REG32(REG_AON_SEC_APB_CA53_LIT_CLK_CFG);
	clk_cfg |= 8;
	REG32(REG_AON_SEC_APB_CA53_LIT_CLK_CFG) = clk_cfg;
	delay();

	clk_cfg = REG32(REG_AON_SEC_APB_CA53_BIG_CLK_CFG);
	clk_cfg |= 8;
	REG32(REG_AON_SEC_APB_CA53_BIG_CLK_CFG) = clk_cfg;
	delay();

	return 0;
}

static void MiscClkConfig(void)
{
	/* set cci clock to  614.4m(whale) 768m(whale2) */
#if defined(CONFIG_CLK_PARA)
	uint32 clk_cfg;
	clk_cfg = REG32(0x402d0300);
	clk_cfg &= ~3;
	clk_cfg |= mcu_clk_para.cci_freq.lvl;//whale2 3:256M,whale 3:256M
	REG32(0x402d0300) = clk_cfg;
#else
	uint32 clk_cfg;

	clk_cfg = REG32(0x402d0300);
	clk_cfg &= ~3;
	clk_cfg |= 3;
	REG32(0x402d0300) = clk_cfg;
#endif
}

static uint32 ClkConfig(uint32 arm_clk,uint32 arm_big_clk)
{
    ArmCoreConfig(arm_clk);
    AxiClkConfig(arm_clk);
    DbgClkConfig(arm_clk,arm_big_clk);
    McuClkConfig(arm_clk,arm_big_clk);
    //AhbClkConfig();
    ApbClkConfig();
    MiscClkConfig();
    DpllClkConfig(CLK_800M);
    return 0;
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

	/* cm4 choose rco100m chang points:
	1 rco100m associate with all subsys (0x402d0178)
	2 pmu clock change xtl4m to rco4m (0x402b0328)
	3 clk_sp_ahb choose rco100m  (0x402d02d0)
	4 clk_aon_apb init to 153.6 which is reconfigured
	to rco100m in deep mode (0x402d0230)
	5 clk_debounce choose rco25m (0x402d02e8)
	6 clk_ca53_dap choose rco100m (0x402d0288)
	7 clk_adi choose rco25m (0x402d0234)*/
	REG32(0x402d02e8) = 2;
	REG32(0x402d0288) = 2;
	REG32(0x402d0234) = 2;
}
uint32 MCU_Init()
{
#if defined(CONFIG_WHALE2)//enable and calibrate rc100m
	Rco100_config();
#endif
#if defined(CONFIG_CLK_PARA)
    if (ClkConfig(mcu_clk_para.core0_freq.value,mcu_clk_para.core1_freq.value))
#else
    if (ClkConfig(CLK_800M,CLK_1500M))
#endif
        while(1);
    return 0;
}
#if 0
#if defined(CONFIG_CLK_PARA)
void set_ddr_clk(uint32 ddr_clk)
{
    volatile uint32 reg_val;

    reg_val = REG32(REG_AON_APB_DPLL_CFG1);
    reg_val |= (1<<26); 	//fractional divider
    reg_val |= (3<<18);		// DPLL_REFIN 0-2M 1-4M 2-13M 3-26M
    REG32(REG_AON_APB_DPLL_CFG1) = reg_val;

    reg_val = (KINT(ddr_clk,DPLL_REFIN)&0xfffff);
    reg_val |= (NINT(ddr_clk,DPLL_REFIN)&0x3f)<<24;
    REG32(REG_AON_APB_DPLL_CFG2) = reg_val;

    //select DPLL 533MHZ source clock
    reg_val = REG32(REG_AON_CLK_EMC_CFG);
    reg_val &= ~0x7;
    //    reg_val |= 0; //default:XTL_26M
    //    reg_val |= 1; //TDPLL_256M
    //    reg_val |= 2; //TDPLL_384M
    reg_val |= 7; //DPLL_533M
    REG32(REG_AON_CLK_EMC_CFG)= reg_val;

    delay();
}
#endif

#endif
void chipram_env_set(u32 mode)
{
#if defined (CONFIG_WHALE)|| defined (CONFIG_WHALE2)
	chipram_env_t *p_env;
	p_env = (struct chipram_env *)CHIPRAM_ENV_ADDR;
	p_env->magic = CHIPRAM_ENV_MAGIC;
	p_env->mode = mode;
	p_env->dram_size = 0;
	if(BOOTLOADER_MODE_DOWNLOAD == mode)
		p_env->channel_sel = FDL_GetBootMode();
	else
		p_env->channel_sel = NULL;
#endif
}
/*switch to arch64 mode and set pc to addr*/
extern void switch_to_arch_64(void);
void switch64_and_set_pc(u32 addr)
{
#if defined (CONFIG_WHALE)|| defined (CONFIG_WHALE2)
	/*release ARM7 space, then AP can access*/
	//REG32(REG_AON_APB_ARM7_SYS_SOFT_RST) &= ~(1 << 4);
	REG32(REG_PMU_APB_SYS_SOFT_RST) &= ~(1 << 21);
	/*set core0 reset vector*/
	REG32(0x50820020) = addr;

//	switch_to_arch_64();
#endif
}

void SwitchPll(void)
{
	uint32 clk_cfg;

	/* set rpll0/rpll1 path */
	REG32(REG_AON_APB_CCIR_RCVR_CFG) |= ((1<<30) | (1<<31));

	delay();
	delay();

	/* LPLL0 switch */
	clk_cfg = REG32(REG_PMU_APB_LTEPLL_REL_CFG);
	clk_cfg &= ~BIT_PMU_APB_LTEPLL_REF_SEL(7);
	clk_cfg |= BIT_PMU_APB_LTEPLL_REF_SEL(2);//sel rpll0
	REG32(REG_PMU_APB_LTEPLL_REL_CFG) = clk_cfg;

	/* TWPLL switch */
	clk_cfg = REG32(REG_PMU_APB_TWPLL_REL_CFG);
	clk_cfg &= ~BIT_PMU_APB_TWPLL_REF_SEL(7);
	clk_cfg |= BIT_PMU_APB_TWPLL_REF_SEL(2);//sel rpll0
	REG32(REG_PMU_APB_TWPLL_REL_CFG) = clk_cfg;

	/* LPLL1 switch */
	clk_cfg = REG32(REG_PMU_APB_LTEPLL1_REL_CFG);
	clk_cfg &= ~BIT_PMU_APB_LTEPLL1_REF_SEL(7);
	clk_cfg |= BIT_PMU_APB_LTEPLL1_REF_SEL(2);//sel rpll0
	REG32(REG_PMU_APB_LTEPLL1_REL_CFG) = clk_cfg;

	/* lvdsrfpll switch */
	clk_cfg = REG32(REG_PMU_APB_LVDS_RF_PLL_REF_SEL);
	clk_cfg &= ~(BIT_PMU_APB_LVDS_RF_PLL1_REF_SEL(7) | BIT_PMU_APB_LVDS_RF_PLL0_REF_SEL(7));
	clk_cfg |= BIT_PMU_APB_LVDS_RF_PLL1_REF_SEL(5) | BIT_PMU_APB_LVDS_RF_PLL0_REF_SEL(2);

	//lvds0 sel rpll0,lvds1 sel rpll1
	REG32(0x402E1138) = 0x400000;//ltepll0 sel lpll1 output
	REG32(REG_AON_APB_CGM_REG1) |= BIT_AON_APB_LTE_PCCSCC_RFTI_CLK_SW_CFG(0x0A);//from james
	REG32(REG_PMU_APB_LVDS_RF_PLL_REF_SEL) = clk_cfg;

	delay();
	delay();
	delay();
	delay();
	delay();
	delay();
	delay();
}


#if defined(CONFIG_WHALE2)
void upll_power_off(void)
{
	CHIP_REG_AND(REG_ANA_APB_UPLL_CFG4, ~0x3f);
	CHIP_REG_OR(REG_ANA_APB_UPLL_CFG3,
			BIT_ANA_APB_REC_26MHZ_1_BUF_PD);
	CHIP_REG_OR(REG_ANA_APB_UPLL_CFG2,
			BIT_ANA_APB_UPLL_PD_SEL |
			BIT_ANA_APB_UPLL_RST);

}

void agdsp_timer0_sel_config(void)
{
	uint32 cfg;

	/* whale2 timer0 default choose rpll1. however,we don't use rpll1 for
	 * saving power. so change agdsp timer0 to choose 26m. notice:agdsp
	 timer1/systmr use 32K by default  */
	cfg = REG32(0x402d0068);
	cfg &= (~(0x3<<3));
	cfg |= (0x0<<3);
	REG32(0x402d0068) = cfg;
}

/*xtl0,xtlbuf0,xtlbuf1,xtlbuf2: all sel(defult)
rc1: ap sel ,sp sel (default)*/
void pll_sel_config(uint32_t gen_para)
{
	CHIP_REG_OR(REG_PMU_APB_XTLBUF0_REL_CFG,
		BIT_PMU_APB_XTLBUF0_AP_SEL |
		BIT_PMU_APB_XTLBUF0_PUBCP_SEL |
		BIT_PMU_APB_XTLBUF0_WTLCP_SEL |
		BIT_PMU_APB_XTLBUF0_AGCP_SEL |
		0
	);

	CHIP_REG_AND(REG_PMU_APB_XTLBUF0_REL_CFG,
		~BIT_PMU_APB_XTLBUF0_CM3_SEL
	);

	CHIP_REG_AND(REG_PMU_APB_XTLBUF1_REL_CFG,
		~(BIT_PMU_APB_XTLBUF1_CM3_SEL |
		BIT_PMU_APB_XTLBUF1_AGCP_SEL |
		BIT_PMU_APB_XTLBUF1_WTLCP_SEL |
		BIT_PMU_APB_XTLBUF1_PUBCP_SEL |
		BIT_PMU_APB_XTLBUF1_AP_SEL)
	);

	CHIP_REG_AND(REG_PMU_APB_XTLBUF2_REL_CFG,
		~(BIT_PMU_APB_XTLBUF2_CM3_SEL |
		BIT_PMU_APB_XTLBUF2_AGCP_SEL |
		BIT_PMU_APB_XTLBUF2_WTLCP_SEL |
		BIT_PMU_APB_XTLBUF2_PUBCP_SEL |
		BIT_PMU_APB_XTLBUF2_AP_SEL)
	);

	CHIP_REG_OR(REG_PMU_APB_XTL0_REL_CFG,
		BIT_PMU_APB_XTL0_AP_SEL |
		BIT_PMU_APB_XTL0_PUBCP_SEL |
		BIT_PMU_APB_XTL0_WTLCP_SEL |
		BIT_PMU_APB_XTL0_AGCP_SEL
	);

	CHIP_REG_AND(REG_PMU_APB_XTL0_REL_CFG,
		~BIT_PMU_APB_XTLBUF0_CM3_SEL
	);

	CHIP_REG_OR(REG_PMU_APB_MPLL_REL_CFG,
		BIT_PMU_APB_MPLL1_AP_SEL |
		BIT_PMU_APB_MPLL0_AP_SEL |
		0
	);

	CHIP_REG_AND(REG_PMU_APB_MPLL_REL_CFG,
		~(BIT_PMU_APB_MPLL1_CM3_SEL |
		BIT_PMU_APB_MPLL1_AGCP_SEL |
		BIT_PMU_APB_MPLL1_WTLCP_SEL |
		BIT_PMU_APB_MPLL1_PUBCP_SEL |
		BIT_PMU_APB_MPLL0_CM3_SEL |
		BIT_PMU_APB_MPLL0_AGCP_SEL |
		BIT_PMU_APB_MPLL0_WTLCP_SEL |
		BIT_PMU_APB_MPLL0_PUBCP_SEL )
	);

	CHIP_REG_OR(REG_PMU_APB_RPLL_REL_CFG,
		BIT_PMU_APB_RPLL0_AGCP_SEL |
		BIT_PMU_APB_RPLL0_WTLCP_SEL |
		BIT_PMU_APB_RPLL0_PUBCP_SEL |
		BIT_PMU_APB_RPLL0_AP_SEL
	);

	CHIP_REG_AND(REG_PMU_APB_RPLL_REL_CFG,
		~(BIT_PMU_APB_RPLL1_CM3_SEL |
		BIT_PMU_APB_RPLL1_AGCP_SEL |
		BIT_PMU_APB_RPLL1_WTLCP_SEL |
		BIT_PMU_APB_RPLL1_PUBCP_SEL |
		BIT_PMU_APB_RPLL1_AP_SEL |
		BIT_PMU_APB_RPLL0_CM3_SEL)
	);
#ifdef DRAM_LPDDR4
	CHIP_REG_OR(REG_PMU_APB_DPLL_REL_CFG,
		BIT_PMU_APB_DPLL1_AP_SEL |
		BIT_PMU_APB_DPLL0_AGCP_SEL |
		BIT_PMU_APB_DPLL0_WTLCP_SEL |
		BIT_PMU_APB_DPLL0_PUBCP_SEL |
		BIT_PMU_APB_DPLL0_AP_SEL |
		0
	);

	CHIP_REG_AND(REG_PMU_APB_DPLL_REL_CFG,
		~(BIT_PMU_APB_DPLL1_CM3_SEL |
		BIT_PMU_APB_DPLL1_AGCP_SEL |
		BIT_PMU_APB_DPLL1_WTLCP_SEL |
		BIT_PMU_APB_DPLL1_PUBCP_SEL |
		BIT_PMU_APB_DPLL0_CM3_SEL )
	);
#else
	CHIP_REG_OR(REG_PMU_APB_DPLL_REL_CFG,
		BIT_PMU_APB_DPLL0_AGCP_SEL |
		BIT_PMU_APB_DPLL0_WTLCP_SEL |
		BIT_PMU_APB_DPLL0_PUBCP_SEL |
		BIT_PMU_APB_DPLL0_AP_SEL |
		0
	);

	CHIP_REG_AND(REG_PMU_APB_DPLL_REL_CFG,
		~(BIT_PMU_APB_DPLL1_CM3_SEL |
		BIT_PMU_APB_DPLL1_AGCP_SEL |
		BIT_PMU_APB_DPLL1_WTLCP_SEL |
		BIT_PMU_APB_DPLL1_PUBCP_SEL |
		BIT_PMU_APB_DPLL1_AP_SEL |
		BIT_PMU_APB_DPLL0_CM3_SEL )
	);

#endif
	CHIP_REG_OR(REG_PMU_APB_LTEPLL_REL_CFG,
		BIT_PMU_APB_LTEPLL_WTLCP_SEL |
		BIT_PMU_APB_LTEPLL_AP_SEL |
		0
	);

	CHIP_REG_AND(REG_PMU_APB_LTEPLL_REL_CFG,
		~(BIT_PMU_APB_LTEPLL_CM3_SEL |
		BIT_PMU_APB_LTEPLL_AGCP_SEL |
		BIT_PMU_APB_LTEPLL_PUBCP_SEL )
	);

	CHIP_REG_OR(REG_PMU_APB_LTEPLL1_REL_CFG,
		BIT_PMU_APB_LTEPLL1_WTLCP_SEL |
		0
	);

	CHIP_REG_AND(REG_PMU_APB_LTEPLL1_REL_CFG,
		~(BIT_PMU_APB_LTEPLL1_CM3_SEL |
		BIT_PMU_APB_LTEPLL1_AGCP_SEL |
		BIT_PMU_APB_LTEPLL1_PUBCP_SEL |
		BIT_PMU_APB_LTEPLL1_AP_SEL)
	);

	CHIP_REG_OR(REG_PMU_APB_TWPLL_REL_CFG,
		BIT_PMU_APB_TWPLL_AGCP_SEL |
		BIT_PMU_APB_TWPLL_WTLCP_SEL |
		BIT_PMU_APB_TWPLL_PUBCP_SEL |
		BIT_PMU_APB_TWPLL_AP_SEL |
		0
	);

	CHIP_REG_AND(REG_PMU_APB_TWPLL_REL_CFG,
		~BIT_PMU_APB_TWPLL_CM3_SEL
	);

	CHIP_REG_OR(REG_PMU_APB_CPPLL_REL_CFG,
		BIT_PMU_APB_CPPLL_AGCP_SEL |
		BIT_PMU_APB_CPPLL_PUBCP_SEL | //should clarify???
		0
	);

	CHIP_REG_AND(REG_PMU_APB_CPPLL_REL_CFG,
		~(BIT_PMU_APB_CPPLL_CM3_SEL |
		BIT_PMU_APB_CPPLL_WTLCP_SEL |
		BIT_PMU_APB_CPPLL_AP_SEL)
	);

	CHIP_REG_OR(REG_PMU_APB_RC_REL_CFG,
		BIT_PMU_APB_RC1_CM3_SEL |
		BIT_PMU_APB_RC1_AGCP_SEL |
		BIT_PMU_APB_RC1_WTLCP_SEL |
		BIT_PMU_APB_RC1_PUBCP_SEL |
		BIT_PMU_APB_RC1_AP_SEL |
		0
	);
	upll_power_off();
	agdsp_timer0_sel_config();

	/* for power saving */
	CHIP_REG_OR(REG_PMU_APB_CP_PUB_PD_CFG,
		BIT_PMU_APB_PUBCP_FORCE_BYP_PUB1 |
		BIT_PMU_APB_WTLCP_FORCE_BYP_PUB1 |
		BIT_PMU_APB_AGCP_FORCE_BYP_PUB1);
}

void noc_slp_cfg(void)
{
	CHIP_REG_AND(REG_PMU_APB_NOC_SLEEP_STOP_BYP,
		~(BIT_PMU_APB_AP_SYS_NOC_LIGHT_SLEEP_STOP_BYP |
		BIT_PMU_APB_PUBCP_SYS_NOC_LIGHT_SLEEP_STOP_BYP |
		BIT_PMU_APB_WTLCP_SYS_NOC_LIGHT_SLEEP_STOP_BYP |
		BIT_PMU_APB_AGCP_SYS_NOC_LIGHT_SLEEP_STOP_BYP |
		BIT_PMU_APB_CA53_TOP_NOC_LIGHT_SLEEP_STOP_BYP)
	);

	CHIP_REG_OR(REG_PMU_APB_NOC_SLP_CFG,
		BIT_PMU_APB_PUB1_DEEP_SLEEP_CLK_SEL_EN |
		BIT_PMU_APB_PUB1_AUTO_GATE_WITH_PUB0_EN |
		BIT_PMU_APB_PUB1_DEEP_SLEEP_CLK_SEL(0x2) |
		0
	);
}
#endif

void Chip_Init (void) /*lint !e765 "Chip_Init" is used by init.s entry.s*/
{
    uint32 value;

    timer_init();
    sci_adi_init();
    regulator_init();
#if !defined(CONFIG_WHALE2_FPGA)
#if defined(CONFIG_WHALE2)
	Reset_twpll_config(1536000000);
	Reset_lpll0_config(1170000000);//sovle emmc problem, div6 195M
	Reset_lpll1_config(1228800000);
	Reset_cppll_config(884736000);
  pll_sel_config(0x0);
#endif
    SwitchPll();
    MCU_Init();
#if defined(CONFIG_CLK_PARA)
    sdram_init(mcu_clk_para.ddr_freq.value);
#else
    sdram_init(DDR_FREQ);
#endif

#if defined(CONFIG_DUAL_DDR)
    noc_init();
#endif
#if defined(CONFIG_WHALE2)
	noc_slp_cfg();
#endif
#endif

/*
 * mdelay init for mmc_v40.c use
*/
#if defined(CONFIG_WHALE2)
	CHIP_REG_OR(REG_AON_APB_APB_EB0, BIT_AON_APB_AP_SYST_EB);
	CHIP_REG_OR(REG_AON_APB_APB_RTC_EB, BIT_AON_APB_AP_SYST_RTC_EB);
#endif
}

