
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
#define NINT(FREQ,REFIN)	(FREQ/REFIN)
#define KINT(FREQ,REFIN)	((FREQ-(FREQ/REFIN)*REFIN)*(BIT_AON_APB_MPLL_KINT(~0x0)+1)/REFIN)

#if defined(CONFIG_CLK_PARA)
#include <asm/arch/clk_para_config.h>
const MCU_CLK_PARA_T mcu_clk_para=
{
    .magic_header = MAGIC_HEADER,
    .version = CONFIG_PARA_VERSION,
    .core_freq = CLK_CA7_CORE,
    .ddr_freq = DDR_FREQ,
    .axi_freq = CLK_CA7_AXI,
    .dgb_freq = CLK_CA7_DGB,
    .ahb_freq = CLK_CA7_AHB,
    .apb_freq = CLK_CA7_APB,
    .pub_ahb_freq = CLK_PUB_AHB,
    .aon_apb_freq = CLK_AON_APB,
#ifdef CONFIG_ARCH_SCX35L2
	.ap_axi_freq = CLK_AP_AXI,
#endif
    .dcdc_arm = DCDC_ARM,
    .dcdc_core = DCDC_CORE,
#ifdef DCDC_MEM
	.dcdc_mem = DCDC_MEM,
#endif
#ifdef DCDC_GEN
	.dcdc_gen = DCDC_GEN,
#endif
#if defined(CONFIG_ADIE_SC2723) || defined(CONFIG_ADIE_SC2723S)
	.debug_flags[0] = 0x3FFFFFF1, //0x3FFFFFFF
#elif defined(CONFIG_ADIE_SC2713S)
	.debug_flags[0] = 0xFFFF0FE2, //0xFFFF0FFE
#else /* defined(CONFIG_ADIE_SC2711) || defined(CONFIG_SPX15) */
	.debug_flags[0] = 0x1FFF07F1, //0x1FFF07FF
#endif
    .magic_end = MAGIC_END
};
#endif

static void delay()
{
    volatile uint32 i;
    for (i=0; i<0x100; i++);
}

#ifdef CONFIG_SCX35LT8

#define REG_AON_CLK_CCI_CFG                              SCI_ADDR(SPRD_AONCKG_PHYS, 0x0074)
static void SetMiscConfig(void)
{
    REG32(REG_AON_CLK_CCI_CFG) &= ~0x3;
    REG32(REG_AON_CLK_CCI_CFG) |= 0x2;
}

static uint32 SetMPllClk_T8 (uint32 clk, uint32 litflag)
{
    uint32 mpll_cfg;
    uint32 mpll_reg_cfg1, mpll_reg_cfg2, bit_done;

#define REG_AON_APB_MPLL0_CFG1                          SCI_ADDR(REGS_AON_APB_BASE, 0x00140)
#define REG_AON_APB_MPLL0_CFG2                          SCI_ADDR(REGS_AON_APB_BASE, 0x00144)
#define MPLL0_SOFT_CNT_DONE (BIT(0))

#define MPLL_SOFT_CNT_DONE (BIT(5))

    if(litflag){
        mpll_reg_cfg1 = REG_AON_APB_MPLL0_CFG1;
        mpll_reg_cfg2 = REG_AON_APB_MPLL0_CFG2;
        bit_done = MPLL0_SOFT_CNT_DONE;
    }else{
        mpll_reg_cfg1 = REG_AON_APB_MPLL_CFG1;
        mpll_reg_cfg2 = REG_AON_APB_MPLL_CFG2;
        bit_done = MPLL_SOFT_CNT_DONE;
    }

    REG32(REG_AON_APB_PLL_SOFT_CNT_DONE) &= ~bit_done;

    clk=clk/1000000;

    mpll_cfg  = REG32(mpll_reg_cfg1);

    mpll_cfg |= (1<<26); 	//fractional divider
    mpll_cfg |= (1<<24);//mpll sdm en
    mpll_cfg |= (3<<18);	// MPLL_REFIN 0-2M 1-4M 2-13M 3-26M
    REG32(mpll_reg_cfg1) = mpll_cfg;

    mpll_cfg = (KINT(clk,MPLL_REFIN)&0xfffff);
    mpll_cfg |= (NINT(clk,MPLL_REFIN)&0x3f)<<24;
    REG32(mpll_reg_cfg2) = mpll_cfg;

    delay();
    delay();
    delay();
    delay();
    delay();

    REG32(REG_AON_APB_PLL_SOFT_CNT_DONE) |=  bit_done;

    return 0;
}
#endif

static uint32 SetMPllClk (uint32 clk)
{
    uint32 mpll_cfg1, mpll_cfg2;

    REG32(REG_AON_APB_PLL_SOFT_CNT_DONE) &= ~BIT_AON_APB_MPLL_SOFT_CNT_DONE;

    clk=clk/1000000;

    mpll_cfg1 = REG32(REG_AON_APB_MPLL_CFG1);
    mpll_cfg1 |= BIT_AON_APB_MPLL_DIV_S;//fractional divider
    mpll_cfg1 |= BIT_AON_APB_MPLL_SDM_EN;//mpll sdm en
    mpll_cfg1 |= BIT_AON_APB_MPLL_RES(3);	// MPLL_REFIN 0-2M 1-4M 2-13M 3-26M
    REG32(REG_AON_APB_MPLL_CFG1) = mpll_cfg1;

    mpll_cfg2 = REG32(REG_AON_APB_MPLL_CFG2);
	mpll_cfg2 &= ~(BIT_AON_APB_MPLL_NINT(~0x0) | BIT_AON_APB_MPLL_KINT(~0x0));
	mpll_cfg2 |= BIT_AON_APB_MPLL_NINT(NINT(clk,MPLL_REFIN)) | BIT_AON_APB_MPLL_KINT(KINT(clk,MPLL_REFIN));
    REG32(REG_AON_APB_MPLL_CFG2) = mpll_cfg2;

    delay();
    delay();
    delay();
    delay();
    delay();

    REG32(REG_AON_APB_PLL_SOFT_CNT_DONE) |= BIT_AON_APB_MPLL_SOFT_CNT_DONE;

    return 0;
}

static uint32 AhbClkConfig()
{
#if defined(CONFIG_CLK_PARA)
    uint32 ahb_cfg;
    ahb_cfg  = REG32(REG_AP_CLK_AP_AHB_CFG);
    ahb_cfg &= ~BIT_AP_CLK_AP_APB_CFG_AP_APB_SEL(~0x0);
    ahb_cfg |= mcu_clk_para.ahb_freq;  //ahb select 192M           0:26M 1:76M 2:128M 3:192M
    REG32(REG_AP_CLK_AP_AHB_CFG) = ahb_cfg;

    ahb_cfg  = REG32(REG_AON_CLK_PUB_AHB_CFG);
    ahb_cfg &= ~BIT_AON_CLK_PUB_AHB_CFG_PUB_AHB_SEL(~0x0);
    ahb_cfg |= mcu_clk_para.pub_ahb_freq;  //pub ahb select 128M      0:26M 1:4M 2:96M 3:128M
    REG32(REG_AON_CLK_PUB_AHB_CFG) = ahb_cfg;
#else
    uint32 ahb_cfg;
    ahb_cfg  = REG32(REG_AP_CLK_AP_AHB_CFG);
    ahb_cfg &=~3;
    ahb_cfg |= 3;  //ahb select 192M           0:26M 1:76M 2:128M 3:192M
    REG32(REG_AP_CLK_AP_AHB_CFG) = ahb_cfg;

    ahb_cfg  = REG32(REG_AON_CLK_PUB_AHB_CFG);
    ahb_cfg &=~3;
    ahb_cfg |= 3;  //pub ahb select 128M      0:26M 1:4M 2:96M 3:128M
    REG32(REG_AON_CLK_PUB_AHB_CFG) = ahb_cfg;
#endif
    delay();
    return 0;
}

static uint32 ApbClkConfig()
{
#if defined(CONFIG_CLK_PARA)
    uint32 apb_cfg;
    apb_cfg  = REG32(REG_AP_CLK_AP_APB_CFG);
    apb_cfg &= ~BIT_AP_CLK_AP_APB_CFG_AP_APB_SEL(~0x0);
    apb_cfg |= mcu_clk_para.apb_freq;  //apb select 128M            0:26M 1:64M 2:96M 3:128M
    REG32(REG_AP_CLK_AP_APB_CFG) = apb_cfg;

    apb_cfg = REG32(REG_AON_CLK_AON_APB_CFG);
    apb_cfg &= ~BIT_AON_CLK_AON_APB_CFG_AON_APB_SEL(~0x0);
    apb_cfg |= mcu_clk_para.aon_apb_freq;  //aon apb select 128M        0:26M 1:76M 2:96M 3:128M
    REG32(REG_AON_CLK_AON_APB_CFG) = apb_cfg;
#ifdef CONFIG_SCX35LT8
    SetMiscConfig();
#endif

#else
    uint32 apb_cfg;
    apb_cfg  = REG32(REG_AP_CLK_AP_APB_CFG);
    apb_cfg &=~3;
    apb_cfg |= 1;  //apb select 64M            0:26M 1:64M 2:96M 3:128M
    REG32(REG_AP_CLK_AP_APB_CFG) = apb_cfg;

    apb_cfg = REG32(REG_AON_CLK_AON_APB_CFG);
    apb_cfg &=~3;
    apb_cfg |= 3;  //aon apb select 96M        0:4M 1:26M 2:76.8M 3:96M
    REG32(REG_AON_CLK_AON_APB_CFG) = apb_cfg;
#endif
    delay();
    return 0;
}

#ifdef CONFIG_ARCH_SCX35L2
static uint32 AP_AxiClkConfig()
{
#if defined(CONFIG_CLK_PARA)
    uint32 ap_axi_cfg;
    ap_axi_cfg = REG32(REG_AP_CLK_AP_AXI_CFG);
    ap_axi_cfg &= ~BIT_AP_CLK_AP_AXI_CFG_AP_AXI_SEL(~0x0);
    ap_axi_cfg |= mcu_clk_para.ap_axi_freq;  //axi select 256M            0:26M 1:76.8M 2:128M 3:256M
    REG32(REG_AP_CLK_AP_AXI_CFG) = ap_axi_cfg;
#endif
	delay();
	return 0;
}

static uint32 Analog_IO_ClkConfig()
{
	uint32 clk_cfg;
	clk_cfg = REG32(REG_AON_CLK_ANALOG_APB_CFG);
	clk_cfg &= ~BIT_AON_CLK_ANALOG_APB_CFG_ANALOG_APB_SEL(~0x0);
	clk_cfg |= BIT_AON_CLK_ANALOG_APB_CFG_ANALOG_APB_SEL(2);//48M
	REG32(REG_AON_CLK_ANALOG_APB_CFG) = clk_cfg;

	clk_cfg = REG32(REG_AON_CLK_IO_APB_CFG);
	clk_cfg &= ~BIT_AON_CLK_IO_APB_CFG_IO_APB_SEL(~0x0);
	clk_cfg |= BIT_AON_CLK_IO_APB_CFG_IO_APB_SEL(2);//48M
	REG32(REG_AON_CLK_IO_APB_CFG) = clk_cfg;
	delay();
	return 0;
}

static uint32 Rfti_SBI_ClkConfig()
{
	uint32 clk_cfg;
	clk_cfg = REG32(REG_AON_CLK_RFTI_SBI_CFG);
	clk_cfg &= ~BIT_AON_CLK_RFTI_SBI_CFG_RFTI_SBI_SEL(~0x0);
	clk_cfg |= BIT_AON_CLK_RFTI_SBI_CFG_RFTI_SBI_SEL(4);//96M
	REG32(REG_AON_CLK_RFTI_SBI_CFG) = clk_cfg;
	delay();
	return 0;
}
#endif

static uint32 AxiClkConfig(uint32 arm_clk)
{
#if defined(CONFIG_CLK_PARA)
	uint32 ca7_ckg_cfg;
	ca7_ckg_cfg = REG32(REG_AP_AHB_CA7_CKG_DIV_CFG);
	ca7_ckg_cfg &= ~BIT_AP_AHB_CA7_AXI_CKG_DIV(~0x0);
#ifdef CONFIG_SCX35LT8
	/*mcu_big_axi freq is the same as mcu freq*/
#else
	ca7_ckg_cfg |= BIT_AP_AHB_CA7_AXI_CKG_DIV(arm_clk/mcu_clk_para.axi_freq -1 + (arm_clk%mcu_clk_para.axi_freq? 1:0));
#endif

	REG32(REG_AP_AHB_CA7_CKG_DIV_CFG) = ca7_ckg_cfg;
#else
	uint32 ca7_ckg_cfg;
	ca7_ckg_cfg  = REG32(REG_AP_AHB_CA7_CKG_DIV_CFG);
	ca7_ckg_cfg &= ~(7<<8);
	ca7_ckg_cfg |= ((arm_clk/(CLK_500M+1))&0x7)<<8;
	REG32(REG_AP_AHB_CA7_CKG_DIV_CFG) = ca7_ckg_cfg;
#endif
	delay();
	return 0;
}

static uint32 DbgClkConfig(uint32 arm_clk)
{
#if defined(CONFIG_CLK_PARA)
    uint32 ca7_ckg_cfg;
    ca7_ckg_cfg  =  REG32(REG_AP_AHB_CA7_CKG_DIV_CFG);
    ca7_ckg_cfg &= ~BIT_AP_AHB_CA7_DBG_CKG_DIV(~0x0);
    ca7_ckg_cfg |= BIT_AP_AHB_CA7_DBG_CKG_DIV(arm_clk/mcu_clk_para.dgb_freq -1 + (arm_clk%mcu_clk_para.dgb_freq? 1:0));
    ca7_ckg_cfg |=  ((arm_clk/(mcu_clk_para.dgb_freq+1))&0x7)<<16;
    REG32(REG_AP_AHB_CA7_CKG_DIV_CFG) = ca7_ckg_cfg;
#else
    uint32 ca7_ckg_cfg;
    ca7_ckg_cfg  =  REG32(REG_AP_AHB_CA7_CKG_DIV_CFG);
    ca7_ckg_cfg &= ~(7<<16);
    ca7_ckg_cfg |=  ((arm_clk/(CLK_200M+1))&0x7)<<16;
    REG32(REG_AP_AHB_CA7_CKG_DIV_CFG) = ca7_ckg_cfg;
#endif
    delay();
    return 0;
}

static uint32 McuClkConfig(uint32 arm_clk)
{
    uint32 ca7_ckg_cfg;

    /* Both big and LITTLE clock set here*/
#ifdef CONFIG_SCX35LT8
    ca7_ckg_cfg  =  REG32(REG_AP_AHB_CA7_CKG_DIV_CFG);
    ca7_ckg_cfg &= ~(0x7e);  //ap clk div = 0;
    REG32(REG_AP_AHB_CA7_CKG_DIV_CFG) = ca7_ckg_cfg;

    delay();

    SetMPllClk_T8(CLK_1000M, 1);
    SetMPllClk_T8(CLK_800M, 0);

    ca7_ckg_cfg  =  REG32(REG_AP_AHB_CA7_CKG_SEL_CFG);
    ca7_ckg_cfg &= ~(0x3f); //a7 core select 26M
    ca7_ckg_cfg |=  0x36; //LITTLE select mpll0, big select mpll
    REG32(REG_AP_AHB_CA7_CKG_SEL_CFG) = ca7_ckg_cfg;

    delay();
#else
    ca7_ckg_cfg  =  REG32(REG_AP_AHB_CA7_CKG_SEL_CFG);
    ca7_ckg_cfg &= ~BIT_AP_AHB_CA7_MCU_CKG_SEL(~0x0); //a7 core select 26M
    REG32(REG_AP_AHB_CA7_CKG_SEL_CFG) = ca7_ckg_cfg;
    delay();

    SetMPllClk(arm_clk);

    ca7_ckg_cfg  =  REG32(REG_AP_AHB_CA7_CKG_DIV_CFG);
    ca7_ckg_cfg &= ~BIT_AP_AHB_CA7_MCU_CKG_DIV(~0x0);  //ap clk div = 0;
    REG32(REG_AP_AHB_CA7_CKG_DIV_CFG) = ca7_ckg_cfg;

    ca7_ckg_cfg  =  REG32(REG_AP_AHB_CA7_CKG_SEL_CFG);
    ca7_ckg_cfg |=  BIT_AP_AHB_CA7_MCU_CKG_SEL(6); //a7 core select mcu MPLL       0:26M 1:(TWPLL)512M 2:(TWPLL)768M 3:(DPLL)1334M 4:(LTEPLL)1288M 5:(TWPLL)1536M 6:(MPLL)1500M
    REG32(REG_AP_AHB_CA7_CKG_SEL_CFG) = ca7_ckg_cfg;

    delay();
#endif
    return 0;
}

static uint32 ArmCoreConfig(uint32 arm_clk)
{
    uint32 dcdc_arm;
    uint32 mbist_block_val;

#if defined(CONFIG_VOL_PARA)
#ifdef CONFIG_ARCH_SCX35L2
    if(ddie_efuse_read(MBIST_LV_BLOCK)& MBIST_JUDGE_BIT)
	regulator_set_voltage("vddcore",mcu_clk_para.dcdc_core + 50);
    else
	regulator_set_voltage("vddcore",mcu_clk_para.dcdc_core);
#else
	regulator_set_voltage("vddcore",mcu_clk_para.dcdc_core);
#endif

#ifdef DCDC_ARM
	regulator_set_voltage("vddcpu",mcu_clk_para.dcdc_arm);
#endif

#ifdef DCDC_MEM
	regulator_set_voltage("vddmem",mcu_clk_para.dcdc_mem);
#endif

#ifdef DCDC_GEN
	regulator_set_voltage("vddgen",mcu_clk_para.dcdc_gen);
#endif
#endif
    delay();
    return 0;
}

#ifdef CONFIG_NAND_SPL
void PLL_Ref_Sel(void)
{
#if defined (CP_SELECT_SWITCH)
	/* step1:choose XTL1_BUF to associate with CP,keep default */

	/* step2:choose CP0/CP1 subsystem to sin1 */
	REG32(REG_PMU_APB_26M_SEL_CFG) |= BIT_CP0_26M_SEL | BIT_CP1_26M_SEL;

	/* step3:choose CP's LTEPLL/TWPLL to sin1 */
	/* LTEPLL select SIN1 */
	REG32(REG_PMU_APB_LTEPLL_REL_CFG) |= BIT_LTEPLL_REF_SEL;
	/* TWPLL select SIN1 */
	REG32(REG_PMU_APB_TWPLL_REL_CFG) |= BIT_TWPLL_REF_SEL;

	delay();
#elif defined(CONFIG_ARCH_SCX35L2)
	/*
	 * step1:xtl related subsys configuration
	 */
	uint32 clk_cfg;
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
	 * pub related to dpll/xtl0/xtlbuf0/chip_sleep
	 */
	CHIP_REG_AND(REG_PMU_APB_CGM_AUTO_GATE_SEL_CFG0, ~((1 << 0) | (1 << 2) | (1 << 5)));

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

	CHIP_REG_OR(REG_PMU_APB_RPLL_REL_CFG, (BIT_PMU_APB_RPLL_ARM7_SEL |
											BIT_PMU_APB_RPLL_PUBCP_SEL |
											BIT_PMU_APB_RPLL_WTLCP_SEL |
											BIT_PMU_APB_RPLL_AP_SEL));

	CHIP_REG_OR(REG_PMU_APB_DPLL_REL_CFG, (BIT_PMU_APB_MPLL_AP_SEL |
											BIT_PMU_APB_MPLL_PUBCP_SEL |
											BIT_PMU_APB_MPLL_WTLCP_SEL));
	CHIP_REG_AND(REG_PMU_APB_DPLL_REL_CFG, ~(BIT_PMU_APB_MPLL_ARM7_SEL));

	CHIP_REG_OR(REG_PMU_APB_LTEPLL_REL_CFG, BIT_PMU_APB_LTEPLL_WTLCP_SEL);
	CHIP_REG_AND(REG_PMU_APB_LTEPLL_REL_CFG, ~(BIT_PMU_APB_LTEPLL_ARM7_SEL |
												BIT_PMU_APB_LTEPLL_PUBCP_SEL |
												BIT_PMU_APB_LTEPLL_AP_SEL));
	/*
	 * step3: lvdspll twpll witch to rpll,lvdspll switch to untune26M
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

	delay();
	delay();
	delay();
	delay();
	delay();
	delay();
	delay();
#endif
}
#else
void PLL_Ref_Sel(void) {}
#endif

static uint32 ClkConfig(uint32 arm_clk)
{
    ArmCoreConfig(arm_clk);
    //AvsEb();
    AxiClkConfig(arm_clk);
    DbgClkConfig(arm_clk);
    McuClkConfig(arm_clk);
    AhbClkConfig();
    ApbClkConfig();
#ifdef CONFIG_ARCH_SCX35L2
	AP_AxiClkConfig();
	Analog_IO_ClkConfig();
	Rfti_SBI_ClkConfig();//rfti spi master clk,96M
#endif
    return 0;
}

#ifdef CONFIG_SCX35LT8
static uint32 ADIConfig(void)
{
    REG32(REG_AON_APB_APB_EB0) |= 0x1<<16;	/*ADI_EB*/
#if 0
	REG32(REG_AON_APB_APB_RST0) |= 0x1<<17;	/*ADI_SOFT_RST*/
	{
		 uint32 wait = 50;
		 while(wait --) {}
	}
	REG32(REG_AON_APB_APB_RST0) &= ~(0x1<<17);	/*ADI_SOFT_RST*/
#endif
	REG32(0x40030020) = 0x74d0835d;//data 16 bit cmd 13bit both 29 bit
	REG32(0x40030024) |= (1 << 31);// 2 -wire mode enable
}
#endif

uint32 MCU_Init()
{

#if defined(CONFIG_CLK_PARA)

#ifdef CONFIG_SCX35LT8
	ADIConfig();
#endif

    if (ClkConfig(mcu_clk_para.core_freq))
#else
#if (defined(CONFIG_SPX15) || defined(CONFIG_SC8830))
    if (ClkConfig(CLK_1000M))
#else
    if (ClkConfig(CLK_800M))
#endif
#endif
        while(1);
    return 0;
}

#ifdef CONFIG_SCX35LT8
#define REG_AON_CLK_EMC_CFG   (0x50820010)
#endif

#if defined(CONFIG_CLK_PARA)
void set_ddr_clk(uint32 ddr_clk)
{
    volatile uint32 reg_val;

	if(ddr_clk > 1559)	// fractiional divider max NINT is 60*26
	{
		reg_val = 0;
		reg_val &= ~(1<<26);	//interger divider
		reg_val |= (0x2<<20);		//DPLL_LPF
		reg_val |= (2<<18); 	// DPLL_REFIN 0-2M 1-4M 2-13M 3-26M
		reg_val &= ~(0x3<<16);		//DPLL_IBIAS
		reg_val |= ((NINT(ddr_clk,13)&0x7ff)<<0);		//DPLL_N
		REG32(REG_AON_APB_DPLL_CFG1) = reg_val;

	}
	else
	{
    reg_val = REG32(REG_AON_APB_DPLL_CFG1);
    reg_val |= (1<<26); 	//fractional divider
    reg_val |= (3<<18);		// DPLL_REFIN 0-2M 1-4M 2-13M 3-26M
    REG32(REG_AON_APB_DPLL_CFG1) = reg_val;

    reg_val = (KINT(ddr_clk,DPLL_REFIN)&0xfffff);
    reg_val |= (NINT(ddr_clk,DPLL_REFIN)&0x3f)<<24;
    REG32(REG_AON_APB_DPLL_CFG2) = reg_val;
	}
#ifdef CONFIG_SCX35LT8
    reg_val = REG32(0x402e0114);
    reg_val &= ~(1<<4);
    REG32(0x402e0114) = reg_val;

    reg_val = REG32(0x402b00b0);
    reg_val &= ~(1<<8);
    REG32(0x402b00b0) = reg_val;
#endif
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

void chipram_env_set(u32 mode)
{
#if defined(CONFIG_SCX35L64) || defined(CONFIG_CHIP_ENV_SET)
	chipram_env_t *p_env;
	p_env = (struct chipram_env *)CHIPRAM_ENV_ADDR;
	p_env->magic = CHIPRAM_ENV_MAGIC;
	p_env->mode = mode;
	p_env->dram_size = 0;
#endif
}
/*switch to arch64 mode and set pc to addr*/
extern void switch_to_arch_64(void);
void switch64_and_set_pc(u32 addr)
{
#ifdef CONFIG_SCX35L64
	/*release ARM7 space, then AP can access*/
	REG32(REG_AON_APB_ARM7_SYS_SOFT_RST) &= ~(1 << 4);
	REG32(REG_PMU_APB_CP_SOFT_RST) &= ~(1 << 8);
	/*set core0 reset vector*/
	REG32(0x50820020) = addr;

#ifdef CONFIG_SCX35LT8
	REG32(0x50820034) |= 0x1;
#else
	REG32(0x50820034) |= 0xf;

	REG32(0x50820024) = addr;
	REG32(0x50820028) = addr;
	REG32(0x5082002c) = addr;
	REG32(0x402b1008) = BIT(24);
	REG32(0x402b100c) = BIT(24);
	REG32(0x402b1010) = BIT(24);
#endif

	switch_to_arch_64();
#endif
}

#if defined(CONFIG_ARCH_SCX35L2) && defined(CONFIG_ADIE_SC2721)
void sc2721_refout_conf(void)
{
	uint32 value;

	value = ANA_REG_GET(ANA_REG_GLB_CLK32KLESS_CTRL0);
	value &= (BIT_TSX_MODE | BIT_RTC_MODE);
	if (value == (BIT_TSX_MODE | BIT_RTC_MODE)) {
		value = ANA_REG_GET(ANA_REG_GLB_TSX_CTRL0);
		value &= ~(BIT_DCXO_26M_REF_OUT3_EN_SW |
			BIT_DCXO_26M_REF_OUT2_EN_SW |
			BIT_DCXO_26M_REF_OUT1_EN_SW);
		ANA_REG_SET(ANA_REG_GLB_TSX_CTRL0, value);

		value = ANA_REG_GET(ANA_REG_GLB_TSX_CTRL1);
		value |= (BIT_DCXO_26M_REF_OUT3_EXT_XTL3_EN |
			BIT_DCXO_26M_REF_OUT2_EXT_XTL2_EN |
			BIT_DCXO_26M_REF_OUT1_EXT_XTL1_EN);
		ANA_REG_SET(ANA_REG_GLB_TSX_CTRL1, value);

		REG32(REG_PMU_APB_PAD_OUT_ADIE_CTRL1) &=
			~(BIT_PMU_APB_PAD_OUT_XTL_BUF_EN1_WTLCP_DEEP_SLEEP_MASK |
			BIT_PMU_APB_PAD_OUT_XTL_BUF_EN1_PUBCP_DEEP_SLEEP_MASK);

		REG32(REG_PMU_APB_PAD_OUT_ADIE_CTRL1) |=
			BIT_PMU_APB_PAD_OUT_XTL_BUF_EN1_AP_DEEP_SLEEP_MASK;
	}
}
#else
void sc2721_refout_conf(void) {}
#endif

extern void sdram_init(void);
void Chip_Init (void) /*lint !e765 "Chip_Init" is used by init.s entry.s*/
{
    uint32 value;

    timer_init();
    sci_adi_init();
    regulator_init();

    sc2721_refout_conf();
    /* MUST stand first statement */
/*solve rpll output 26M*/
#ifdef CONFIG_SCX35L2_MDAR
    Mdar_rpll_init();
    delay();
#endif
    PLL_Ref_Sel();
#if defined(CONFIG_SPX15)
	if(0x2711A000 == ANA_GET_CHIP_ID()) {
	    value = ANA_REG_GET(0x4003883c);
	    value &= ~0x7f00;
	    value |= 0x38 << 8;
	    ANA_REG_SET(0x4003883c,value);

	    value = ANA_REG_GET(0x40038820);
	    value &= ~0xff;
	    value |= 0x38 << 0;
	    ANA_REG_SET(0x40038820,value);
	}
#endif

    MCU_Init();
#ifndef CONFIG_SPX35L64_FPGA
    sdram_init();
#endif
}

