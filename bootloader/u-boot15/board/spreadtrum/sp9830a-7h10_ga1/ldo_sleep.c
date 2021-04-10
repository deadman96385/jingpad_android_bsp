#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
#include <adi_hal_internal.h>

/***************************************************************************************************************************/
/*     VDD18 VDD28 VDD25 RF0 RF1 RF2 EMMCIO EMMCCORE DCDCARM DCDCWRF DCDCWPA DCDCGEN DCDCOTP AVDD18 SD SIM0 SIM1 SIM2 CAMA */
/* AP    x     x    v     v   v   v     v      v        v       v       v       x       v      v    v    v   v     v    v  */
/* CP0   x     x    v     v   v   x     x      x        x       v       x       x       x      x    x    x   x     x    x  */
/* CP1   x     x    v     x   x   x     x      x        x       x       x       x       x      x    x    x   x     x    x  */
/* CP2   x     x    v     v   x   v     x      x        x       v       x       x       x      x    x    x   x     x    x  */
/* EX0   x     x    x     v   x   x     x      x        x       x       x       x       x      x    x    x   x     x    x  */
/* EX1   x     x    x     x   v   x     x      x        x       x       x       x       x      x    x    x   x     x    x  */
/* EX2   x     x    x     v   x   x     x      x        x       x       x       x       x      x    x    x   x     x    x  */
/***************************************************************************************************************************/

/***************************************************************************************************************************/
/*     CAMD CMAIO CAMMOT USB CLSG LPREF LPRF0 LPRF1 LPRF2 LPEMMCIO LPEMMCCORE LPWPA  LPGEN   LPARM LPMEM LPCORE LPBG  BG   */
/* AP    v     v    v     v   v   v     v      v     v       v       v          x       v      v     v     v     v     v   */
/* CP0   x     x    x     x   x   x     x      x     x       x       x          x       x      x     x     x     x     x   */
/* CP1   x     x    x     x   x   x     x      x     x       x       x          x       x      x     x     x     x     x   */
/* CP2   x     x    x     x   x   x     v      v     x       x       x          x       x      x     x     x     x     x   */
/* EX0   x     x    x     x   x   x     x      x     v       x       x          x       x      x     x     x     x     x   */
/* EX1   x     x    x     x   x   x     x      x     x       x       x          x       x      x     x     x     x     x   */
/* EX2   x     x    x     x   x   x     x      x     x       x       x          x       x      x     x     x     x     x   */
/***************************************************************************************************************************/

void init_ldo_sleep_gr(void)
{
	unsigned int reg_val;
	ANA_REG_SET(ANA_REG_GLB_PWR_WR_PROT_VALUE,0x6e7f);
	while( (ANA_REG_GET(ANA_REG_GLB_PWR_WR_PROT_VALUE) & 0x8000) != 0x8000 );

	ANA_REG_SET(ANA_REG_GLB_LDO_DCDC_PD,
		//BIT_LDO_EMM_PD |
		//BIT_DCDC_TOPCLK6M_PD |
		//BIT_DCDC_RF_PD |
		//BIT_DCDC_GEN_PD |
		//BIT_DCDC_MEM_PD |
		//BIT_DCDC_ARM_PD |
		//BIT_DCDC_CORE_PD |
		//BIT_LDO_RF0_PD |
		//BIT_LDO_EMMCCORE_PD |
		//BIT_LDO_GEN1_PD |
		//BIT_LDO_DCXO_PD |
		//BIT_LDO_GEN0_PD |
		//BIT_LDO_VDD25_PD |
		//BIT_LDO_VDD28_PD |
		//BIT_LDO_VDD18_PD |
		//BIT_BG_PD |
		0
	);
	ANA_REG_SET(ANA_REG_GLB_LDO_PD_CTRL,
		BIT_LDO_LPREF_PD_SW |
		BIT_DCDC_WPA_PD |
		BIT_DCDC_CON_PD |
		BIT_LDO_WIFIPA_PD |
		BIT_LDO_SDCORE_PD |
		//BIT_LDO_USB_PD |
		BIT_LDO_CAMMOT_PD |
		BIT_LDO_CAMIO_PD |
		BIT_LDO_CAMD_PD |
		BIT_LDO_CAMA_PD |
		BIT_LDO_SIM2_PD |
		BIT_LDO_SIM1_PD |
		BIT_LDO_SIM0_PD |
		BIT_LDO_SDIO_PD |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_PWR_WR_PROT_VALUE,0x0000);

	ANA_REG_SET(ANA_REG_GLB_SLP_WAIT_DCDCARM,
		BITS_SLP_IN_WAIT_DCDCARM(7) |
		BITS_SLP_OUT_WAIT_DCDCARM(8) |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_PWR_SLP_CTRL0,
		BIT_SLP_IO_EN |
		BIT_SLP_DCDCRF_PD_EN |
		//BIT_SLP_DCDCCON_PD_EN |
		//BIT_SLP_DCDCGEN_PD_EN |
		//BIT_SLP_DCDCWPA_PD_EN |
		BIT_SLP_DCDCARM_PD_EN |
		BIT_SLP_LDOVDD25_PD_EN |
		BIT_SLP_LDORF0_PD_EN |
		BIT_SLP_LDOEMMCCORE_PD_EN |
		BIT_SLP_LDOGEN0_PD_EN |
		BIT_SLP_LDODCXO_PD_EN |
		BIT_SLP_LDOGEN1_PD_EN |
		BIT_SLP_LDOWIFIPA_PD_EN |
		//BIT_SLP_LDOVDD28_PD_EN |
		//BIT_SLP_LDOVDD18_PD_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_PWR_SLP_CTRL1,
		BIT_SLP_LDO_PD_EN |
		BIT_SLP_LDOLPREF_PD_EN |
		BIT_SLP_LDOSDCORE_PD_EN |
		BIT_SLP_LDOUSB_PD_EN |
		BIT_SLP_LDOCAMMOT_PD_EN |
		BIT_SLP_LDOCAMIO_PD_EN |
		BIT_SLP_LDOCAMD_PD_EN |
		BIT_SLP_LDOCAMA_PD_EN |
		BIT_SLP_LDOSIM2_PD_EN |
		//BIT_SLP_LDOSIM1_PD_EN |
		//BIT_SLP_LDOSIM0_PD_EN |
		//BIT_SLP_LDOSDIO_PD_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_PWR_SLP_CTRL2,
		//BIT_SLP_DCDCRF_LP_EN |
		//BIT_SLP_DCDCCON_LP_EN |
		BIT_SLP_DCDCCORE_LP_EN |
		BIT_SLP_DCDCMEM_LP_EN |
		//BIT_SLP_DCDCARM_LP_EN |
		BIT_SLP_DCDCGEN_LP_EN |
		//BIT_SLP_DCDCWPA_LP_EN |
		//BIT_SLP_LDORF0_LP_EN  |
		//BIT_SLP_LDOEMMCCORE_LP_EN |
		//BIT_SLP_LDOGEN0_LP_EN |
		//BIT_SLP_LDODCXO_LP_EN |
		//BIT_SLP_LDOGEN1_LP_EN |
		//BIT_SLP_LDOWIFIPA_LP_EN |
		//BIT_SLP_LDOVDD28_LP_EN |
		//BIT_SLP_LDOVDD18_LP_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_PWR_SLP_CTRL3,
		//BIT_SLP_BG_LP_EN |
		//BIT_LDOVDD25_LP_EN_SW |
		//BIT_LDOSDCORE_LP_EN_SW |
		//BIT_LDOUSB_LP_EN_SW |
		//BIT_SLP_LDOVDD25_LP_EN |
		//BIT_SLP_LDOSDCORE_LP_EN |
		//BIT_SLP_LDOUSB_LP_EN |
		//BIT_SLP_LDOCAMMOT_LP_EN |
		//BIT_SLP_LDOCAMIO_LP_EN |
		//BIT_SLP_LDOCAMD_LP_EN |
		//BIT_SLP_LDOCAMA_LP_EN |
		//BIT_SLP_LDOSIM2_LP_EN |
		//BIT_SLP_LDOSIM1_LP_EN |
		//BIT_SLP_LDOSIM0_LP_EN |
		//BIT_SLP_LDOSDIO_LP_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_PWR_SLP_CTRL4,
		//BIT_LDOCAMIO_LP_EN_SW |
		//BIT_LDOCAMMOT_LP_EN_SW |
		//BIT_LDOCAMD_LP_EN_SW |
		//BIT_LDOCAMA_LP_EN_SW |
		//BIT_LDOSIM2_LP_EN_SW |
		//BIT_LDOSIM1_LP_EN_SW |
		//BIT_LDOSIM0_LP_EN_SW |
		//BIT_LDOSDIO_LP_EN_SW |
		//BIT_LDORF0_LP_EN_SW |
		//BIT_LDOEMMCCORE_LP_EN_SW |
		//BIT_LDOGEN0_LP_EN_SW |
		//BIT_LDODCXO_LP_EN_SW |
		//BIT_LDOGEN1_LP_EN_SW |
		//BIT_LDOWIFIPA_LP_EN_SW |
		//BIT_LDOVDD28_LP_EN_SW |
		//BIT_LDOVDD18_LP_EN_SW |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_PWR_XTL_EN0,
		BIT_LDO_XTL_EN |
		//BIT_LDO_GEN0_EXT_XTL0_EN |
		//BIT_LDO_GEN0_XTL1_EN |
		//BIT_LDO_GEN0_XTL0_EN |
		BIT_LDO_GEN1_EXT_XTL0_EN |
		BIT_LDO_GEN1_XTL1_EN |
		BIT_LDO_GEN1_XTL0_EN |
		BIT_LDO_DCXO_EXT_XTL0_EN |
		BIT_LDO_DCXO_XTL1_EN |
		BIT_LDO_DCXO_XTL0_EN |
		//BIT_LDO_VDD18_EXT_XTL0_EN |
		//BIT_LDO_VDD18_XTL1_EN |
		//BIT_LDO_VDD18_XTL0_EN |
		//BIT_LDO_VDD28_EXT_XTL0_EN |
		//BIT_LDO_VDD28_XTL1_EN |
		//BIT_LDO_VDD28_XTL0_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_PWR_XTL_EN1,
		BIT_LDO_RF0_EXT_XTL0_EN |
		BIT_LDO_RF0_XTL1_EN |
		BIT_LDO_RF0_XTL0_EN |
		BIT_LDO_WIFIPA_EXT_XTL0_EN |
		//BIT_LDO_WIFIPA_XTL1_EN |
		//BIT_LDO_WIFIPA_XTL0_EN |
		//BIT_LDO_SIM2_EXT_XTL0_EN |
		//BIT_LDO_SIM2_XTL1_EN |
		//BIT_LDO_SIM2_XTL0_EN |
		//BIT_LDO_SIM1_EXT_XTL0_EN |
		//BIT_LDO_SIM1_XTL1_EN |
		//BIT_LDO_SIM1_XTL0_EN |
		//BIT_LDO_SIM0_EXT_XTL0_EN |
		//BIT_LDO_SIM0_XTL1_EN |
		//BIT_LDO_SIM0_XTL0_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_PWR_XTL_EN2,
		BIT_LDO_VDD25_EXT_XTL0_EN |
		BIT_LDO_VDD25_XTL1_EN |
		BIT_LDO_VDD25_XTL0_EN |
		BIT_DCDC_RF_EXT_XTL0_EN |
		BIT_DCDC_RF_XTL1_EN |
		BIT_DCDC_RF_XTL0_EN |
		BIT_XO_EXT_XTL0_EN |
		BIT_XO_XTL1_EN |
		BIT_XO_XTL0_EN |
		BIT_BG_EXT_XTL0_EN |
		BIT_BG_XTL1_EN |
		BIT_BG_XTL0_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_PWR_XTL_EN3,
		//BIT_DCDC_CON_EXT_XTL0_EN |
		//BIT_DCDC_CON_XTL1_EN |
		//BIT_DCDC_CON_XTL0_EN |
		//BIT_DCDC_WPA_EXT_XTL0_EN |
		//BIT_DCDC_WPA_XTL1_EN |
		//BIT_DCDC_WPA_XTL0_EN |
		BIT_DCDC_MEM_EXT_XTL0_EN |
		BIT_DCDC_MEM_XTL1_EN |
		BIT_DCDC_MEM_XTL0_EN |
		BIT_DCDC_GEN_EXT_XTL0_EN |
		BIT_DCDC_GEN_XTL1_EN |
		BIT_DCDC_GEN_XTL0_EN |
		BIT_DCDC_CORE_EXT_XTL0_EN |
		BIT_DCDC_CORE_XTL1_EN |
		BIT_DCDC_CORE_XTL0_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_XTL_WAIT_CTRL,
		BIT_SLP_XTLBUF_PD_EN |
		BIT_XTL_EN |
		BITS_XTL_WAIT(0x32) |
		0
	);


	/************************************************
	*   Following is AP/CP LDO D DIE Sleep Control   *
	*************************************************/
	REG32(REG_PMU_APB_26M_SEL_CFG) |= (BIT_CP1_26M_SEL | BIT_CP0_26M_SEL);
	
	CHIP_REG_SET(REG_PMU_APB_XTL0_REL_CFG,
		BIT_XTL0_ARM7_SEL |
		BIT_XTL0_VCP1_SEL |
		BIT_XTL0_VCP0_SEL |
		BIT_XTL0_CP1_SEL |
		BIT_XTL0_CP0_SEL |
		BIT_XTL0_AP_SEL |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_XTL1_REL_CFG,
		BIT_XTL1_ARM7_SEL |
		BIT_XTL1_VCP1_SEL |
		BIT_XTL1_VCP0_SEL |
		BIT_XTL1_CP1_SEL |
		BIT_XTL1_CP0_SEL |
		BIT_XTL1_AP_SEL |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_XTLBUF0_REL_CFG,
		BIT_XTLBUF0_ARM7_SEL |
		BIT_XTLBUF0_VCP1_SEL |
		BIT_XTLBUF0_VCP0_SEL |
		BIT_XTLBUF0_CP1_SEL |
		BIT_XTLBUF0_CP0_SEL |
		BIT_XTLBUF0_AP_SEL |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_XTLBUF1_REL_CFG,
		BIT_XTLBUF1_ARM7_SEL |
		BIT_XTLBUF1_VCP1_SEL |
		BIT_XTLBUF1_VCP0_SEL |
		BIT_XTLBUF1_CP1_SEL |
		BIT_XTLBUF1_CP0_SEL |
		BIT_XTLBUF1_AP_SEL |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_MPLL_REL_CFG,
		//BIT_MPLL_REF_SEL |
		//BIT_MPLL_ARM7_SEL |
		//BIT_MPLL_VCP1_SEL |
		//BIT_MPLL_VCP0_SEL |
		//BIT_MPLL_CP1_SEL |
		//BIT_MPLL_CP0_SEL |
		BIT_MPLL_AP_SEL |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_DPLL_REL_CFG,
		//BIT_DPLL_REF_SEL |
		BIT_DPLL_ARM7_SEL |
		BIT_DPLL_VCP1_SEL |
		//BIT_DPLL_VCP0_SEL |
		//BIT_DPLL_CP1_SEL |
		//BIT_DPLL_CP0_SEL |
		BIT_DPLL_AP_SEL |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_LTEPLL_REL_CFG,
		BIT_LTEPLL_REF_SEL |
		//BIT_LTEPLL_ARM7_SEL |
		BIT_LTEPLL_VCP1_SEL |
		//BIT_LTEPLL_VCP0_SEL |
		//BIT_LTEPLL_CP1_SEL |
		//BIT_LTEPLL_CP0_SEL |
		//BIT_LTEPLL_AP_SEL |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_TWPLL_REL_CFG,
		BIT_TWPLL_REF_SEL |
		BIT_TWPLL_ARM7_SEL |
		BIT_TWPLL_VCP1_SEL |
		//BIT_TWPLL_VCP0_SEL |
		//BIT_TWPLL_CP1_SEL |
		//BIT_TWPLL_CP0_SEL |
		BIT_TWPLL_AP_SEL |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_LVDSDIS_PLL_REL_CFG,
		BIT_LVDSDIS_PLL_REF_SEL |
		//BIT_LVDSDIS_PLL_ARM7_SEL |
		//BIT_LVDSDIS_PLL_VCP1_SEL |
		//BIT_LVDSDIS_PLL_VCP0_SEL |
		//BIT_LVDSDIS_PLL_CP1_SEL |
		//BIT_LVDSDIS_PLL_CP0_SEL |
		//BIT_LVDSDIS_PLL_AP_SEL |
		0
	);
	CSP_Init(0x50001800);
}
