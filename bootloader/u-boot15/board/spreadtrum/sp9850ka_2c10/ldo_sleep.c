#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
#include <adi_hal_internal.h>

#define IS_32K 0
#define IS_32KLESS 1
#define W_EFFUSE_2721 0x0
#define R_EFFUSE_2721 0x8000
#define CPU_PD_BLOCK 4
#define CPU_PD_BIT 15

extern int sprd_get_32k(void);
extern u32 sprd_pmic_efuse_read(int blk_index);

void DCDC_ldo_power_on()
{
	//regulator_enable("vddcpu");
	//regulator_enable("vddcore");
	//regulator_enable("vddmem");
	//regulator_enable("vddgen");
	//regulator_enable("vddwpa");
	//regulator_enable("vddcama");
	//regulator_enable("vddcammot");
	//regulator_enable("vddsim0");
	//regulator_enable("vddsim1");
	regulator_enable("vddsim2");
	//regulator_enable("vddemmccore");
	regulator_disable("vddsdcore");
	regulator_disable("vddsdio");
	//regulator_enable("vdd28");
	//regulator_enable("vddwifipa");
	//regulator_enable("vdddcxo");
	//regulator_disable("vddusb33");
	//regulator_enable("vddcamd");
	regulator_enable("vddcon");
	//regulator_enable("vddcamio");
	//regulator_enable("vdd18");
	regulator_enable("vddrf18");
	regulator_enable("vddrf15");
	//regulator_enable("vddldomem");
}

void pmic_lowpower_config(uint32_t gen_para)
{
	unsigned int cpu_pd_mode;
	unsigned int feature_32k_less = 0;

	feature_32k_less = sprd_get_32k();

	cpu_pd_mode = sprd_pmic_efuse_read(CPU_PD_BLOCK) & BIT(CPU_PD_BIT);

#if defined(CONFIG_ADIE_SC2721)
	ANA_REG_SET(ANA_REG_GLB_PWR_WR_PROT_VALUE,0x6e7f);
	while( (ANA_REG_GET(ANA_REG_GLB_PWR_WR_PROT_VALUE) & 0x8000) != 0x8000 );

	ANA_REG_SET(ANA_REG_GLB_POWER_PD_SW,
		//BIT_LDO_DCXO_PD |
		//BIT_LDO_EMM_PD |
		BIT_DCDC_TOPCLK6M_PD |
		//BIT_DCDC_GEN_PD |
		//BIT_DCDC_MEM_PD |
		//BIT_DCDC_CORE_PD |
		//BIT_DCDC_CPU_PD |
		//BIT_LDO_MEM_PD |
		//BIT_LDO_AVDD18_PD |
		//BIT_LDO_VDD28_PD |
		//BIT_BG_PD |
		0
	);
	ANA_REG_SET(ANA_REG_GLB_PWR_WR_PROT_VALUE,0x0000);

	ANA_REG_SET(ANA_REG_GLB_SLP_CTRL,
		BIT_LDO_XTL_EN |
		BIT_SLP_IO_EN |
		BIT_SLP_LDO_PD_EN |
		0
	);

	if (cpu_pd_mode == W_EFFUSE_2721) {
		ANA_REG_SET(ANA_REG_GLB_SLP_DCDC_PD_CTRL,
			BIT_SLP_DCDCCORE_DROP_EN |
			//BIT_SLP_DCDCWPA_PD_EN |
			//BIT_SLP_DCDCCPU_PD_EN |
			//BIT_SLP_DCDCMEM_PD_EN |
			0
		);
	} else {
		ANA_REG_SET(ANA_REG_GLB_SLP_DCDC_PD_CTRL,
			BIT_SLP_DCDCCORE_DROP_EN |
			//BIT_SLP_DCDCWPA_PD_EN |
			BIT_SLP_DCDCCPU_PD_EN |
			//BIT_SLP_DCDCMEM_PD_EN |
			0
		);
	}

	if (feature_32k_less == IS_32K) {
		ANA_REG_SET(ANA_REG_GLB_SLP_LDO_PD_CTRL0,
			BIT_SLP_LDORF15_PD_EN |        /*SR3596G*/
			BIT_SLP_LDORF18_PD_EN |        /*SR3596G*/
			//BIT_SLP_LDOEMMCCORE_PD_EN |    /*used by emmc core*/
			BIT_SLP_LDODCXO_PD_EN |        /*used by SR3596G, TCXO and GE2*/
			//BIT_SLP_LDOWIFIPA_PD_EN |    /*used by marlin2*/
			//BIT_SLP_LDOVDD28_PD_EN |     /*used by sensor, lcd/ctp, audio, rf*/
			//BIT_SLP_LDOSDCORE_PD_EN |    /*used by sd*/
			//BIT_SLP_LDOSDIO_PD_EN |      /*used by sd io*/
			//BIT_SLP_LDOUSB33_PD_EN |     /*used by usb*/
			//BIT_SLP_LDOCAMMOT_PD_EN |    /*used by camera*/
			//BIT_SLP_LDOCAMIO_PD_EN |     /*used by camera*/
			//BIT_SLP_LDOCAMD_PD_EN |      /*used by camera*/
			//BIT_SLP_LDOCAMA_PD_EN |      /*used by camera*/
			BIT_SLP_LDOSIM2_PD_EN |      /*used by gps lna and rf switch*/
			//BIT_SLP_LDOSIM1_PD_EN |      /*used by sim1*/
			0
		);
	} else {
		ANA_REG_SET(ANA_REG_GLB_SLP_LDO_PD_CTRL0,
			BIT_SLP_LDORF15_PD_EN |        /*SR3596G*/
			BIT_SLP_LDORF18_PD_EN |        /*SR3596G*/
			//BIT_SLP_LDOEMMCCORE_PD_EN |    /*used by emmc core*/
			//BIT_SLP_LDODCXO_PD_EN |        /*used by SR3596G, TCXO and GE2*/
			//BIT_SLP_LDOWIFIPA_PD_EN |    /*used by marlin2*/
			//BIT_SLP_LDOVDD28_PD_EN |     /*used by sensor, lcd/ctp, audio, rf*/
			//BIT_SLP_LDOSDCORE_PD_EN |    /*used by sd*/
			//BIT_SLP_LDOSDIO_PD_EN |      /*used by sd io*/
			//BIT_SLP_LDOUSB33_PD_EN |     /*used by usb*/
			//BIT_SLP_LDOCAMMOT_PD_EN |    /*used by camera*/
			//BIT_SLP_LDOCAMIO_PD_EN |     /*used by camera*/
			//BIT_SLP_LDOCAMD_PD_EN |      /*used by camera*/
			//BIT_SLP_LDOCAMA_PD_EN |      /*used by camera*/
			BIT_SLP_LDOSIM2_PD_EN |      /*used by gps lna and rf switch*/
			//BIT_SLP_LDOSIM1_PD_EN |      /*used by sim1*/
			0
		);
		ANA_REG_OR(ANA_REG_GLB_CLK32KLESS_CTRL0,
			BIT_SLP_XO_LOW_CUR_EN
		);
	}

	ANA_REG_SET(ANA_REG_GLB_SLP_LDO_PD_CTRL1,
		//BIT_SLP_LDOCON_PD_EN |     /*used by marlin2+ge2*/
		//BIT_SLP_LDOSIM0_PD_EN |    /*used by sim0*/
		BIT_SLP_LDOAVDD18_PD_EN |    /*used by plls, usb20, lvdsrf, csi and so on*/
		//BIT_SLP_LDOMEM_PD_EN |     /*compare with DCDCMEM*/
		0
	);

	ANA_REG_SET(ANA_REG_GLB_SLP_DCDC_LP_CTRL,
		BIT_SLP_DCDCCORE_LP_EN |
		BIT_SLP_DCDCMEM_LP_EN |
		BIT_SLP_DCDCCPU_LP_EN |
		BIT_SLP_DCDCGEN_LP_EN |
		BIT_SLP_DCDCWPA_LP_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_SLP_LDO_LP_CTRL0,
		//BIT_SLP_LDORF15_LP_EN |
		//BIT_SLP_LDORF18_LP_EN |
		//BIT_SLP_LDOEMMCCORE_LP_EN |
		//BIT_SLP_LDODCXO_LP_EN |
		//BIT_SLP_LDOWIFIPA_LP_EN |
		BIT_SLP_LDOVDD28_LP_EN |
		//BIT_SLP_LDOSDCORE_LP_EN |
		//BIT_SLP_LDOSDIO_LP_EN |
		//BIT_SLP_LDOUSB33_LP_EN |
		//BIT_SLP_LDOCAMMOT_LP_EN |
		//BIT_SLP_LDOCAMIO_LP_EN |
		//BIT_SLP_LDOCAMD_LP_EN |
		//BIT_SLP_LDOCAMA_LP_EN |
		//BIT_SLP_LDOSIM2_LP_EN |
		//BIT_SLP_LDOSIM1_LP_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_SLP_LDO_LP_CTRL1,
		BIT_SLP_LDOCON_LP_EN |
		//BIT_SLP_LDOSIM0_LP_EN |
		//BIT_SLP_LDOAVDD18_LP_EN |
		BIT_SLP_LDOMEM_LP_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_DCDC_XTL_EN0,
		BIT_DCDC_CORE_EXT_XTL0_EN |
		//BIT_DCDC_CORE_EXT_XTL1_EN |
		//BIT_DCDC_CORE_EXT_XTL2_EN |
		//BIT_DCDC_CORE_EXT_XTL3_EN |
		//BIT_DCDC_WPA_EXT_XTL0_EN |
		//BIT_DCDC_WPA_EXT_XTL1_EN |
		//BIT_DCDC_WPA_EXT_XTL2_EN |
		//BIT_DCDC_WPA_EXT_XTL3_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_DCDC_XTL_EN1,
		//BIT_DCDC_CPU_EXT_XTL0_EN |
		//BIT_DCDC_CPU_EXT_XTL1_EN |
		//BIT_DCDC_CPU_EXT_XTL2_EN |
		//BIT_DCDC_CPU_EXT_XTL3_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_DCDC_XTL_EN2,
		BIT_DCDC_MEM_EXT_XTL0_EN |
		//BIT_DCDC_MEM_EXT_XTL1_EN |
		//BIT_DCDC_MEM_EXT_XTL2_EN |
		//BIT_DCDC_MEM_EXT_XTL3_EN |
		BIT_DCDC_GEN_EXT_XTL0_EN |
		//BIT_DCDC_GEN_EXT_XTL1_EN |
		//BIT_DCDC_GEN_EXT_XTL2_EN |
		//BIT_DCDC_GEN_EXT_XTL3_EN |
		0
	);
	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN0,
		BIT_LDO_DCXO_EXT_XTL0_EN |
		//BIT_LDO_DCXO_EXT_XTL1_EN |
		//BIT_LDO_DCXO_EXT_XTL2_EN |
		//BIT_LDO_DCXO_EXT_XTL3_EN |
		BIT_LDO_VDD28_EXT_XTL0_EN |
		//BIT_LDO_VDD28_EXT_XTL1_EN |
		//BIT_LDO_VDD28_EXT_XTL2_EN |
		//BIT_LDO_VDD28_EXT_XTL3_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN1,
		//BIT_LDO_RF15_EXT_XTL0_EN |
		//BIT_LDO_RF15_EXT_XTL1_EN |
		//BIT_LDO_RF15_EXT_XTL2_EN |
		//BIT_LDO_RF15_EXT_XTL3_EN |
		BIT_LDO_RF18_EXT_XTL0_EN |
		//BIT_LDO_RF18_EXT_XTL1_EN |
		//BIT_LDO_RF18_EXT_XTL2_EN |
		//BIT_LDO_RF18_EXT_XTL3_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN2,
		//BIT_LDO_SIM0_EXT_XTL0_EN |
		//BIT_LDO_SIM0_EXT_XTL1_EN |
		//BIT_LDO_SIM0_EXT_XTL2_EN |
		//BIT_LDO_SIM0_EXT_XTL3_EN |
		//BIT_LDO_SIM1_EXT_XTL0_EN |
		//BIT_LDO_SIM1_EXT_XTL1_EN |
		//BIT_LDO_SIM1_EXT_XTL2_EN |
		//BIT_LDO_SIM1_EXT_XTL3_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN3,
		//BIT_LDO_SIM2_EXT_XTL0_EN |
		//BIT_LDO_SIM2_EXT_XTL1_EN |
		BIT_LDO_SIM2_EXT_XTL2_EN |
		//BIT_LDO_SIM2_EXT_XTL3_EN |
		BIT_LDO_MEM_EXT_XTL0_EN |
		//BIT_LDO_MEM_EXT_XTL1_EN |
		//BIT_LDO_MEM_EXT_XTL2_EN |
		//BIT_LDO_MEM_EXT_XTL3_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN4,
		//BIT_LDO_CAMMOT_EXT_XTL0_EN |
		//BIT_LDO_CAMMOT_EXT_XTL1_EN |
		//BIT_LDO_CAMMOT_EXT_XTL2_EN |
		//BIT_LDO_CAMMOT_EXT_XTL3_EN |
		//BIT_LDO_CAMIO_EXT_XTL0_EN |
		//BIT_LDO_CAMIO_EXT_XTL1_EN |
		//BIT_LDO_CAMIO_EXT_XTL2_EN |
		//BIT_LDO_CAMIO_EXT_XTL3_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN5,
		//BIT_LDO_CAMA_EXT_XTL0_EN |
		//BIT_LDO_CAMA_EXT_XTL1_EN |
		//BIT_LDO_CAMA_EXT_XTL2_EN |
		//BIT_LDO_CAMA_EXT_XTL3_EN |
		//BIT_LDO_CAMD_EXT_XTL0_EN |
		//BIT_LDO_CAMD_EXT_XTL1_EN |
		//BIT_LDO_CAMD_EXT_XTL2_EN |
		//BIT_LDO_CAMD_EXT_XTL3_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN6,
		//BIT_LDO_SDIO_EXT_XTL0_EN |
		//BIT_LDO_SDIO_EXT_XTL1_EN |
		//BIT_LDO_SDIO_EXT_XTL2_EN |
		//BIT_LDO_SDIO_EXT_XTL3_EN |
		//BIT_LDO_SDCORE_EXT_XTL0_EN |
		//BIT_LDO_SDCORE_EXT_XTL1_EN |
		//BIT_LDO_SDCORE_EXT_XTL2_EN |
		//BIT_LDO_SDCORE_EXT_XTL3_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN7,
		//BIT_LDO_EMMCCORE_EXT_XTL0_EN |
		//BIT_LDO_EMMCCORE_EXT_XTL1_EN |
		//BIT_LDO_EMMCCORE_EXT_XTL2_EN |
		//BIT_LDO_EMMCCORE_EXT_XTL3_EN |
		//BIT_LDO_USB33_EXT_XTL0_EN |
		//BIT_LDO_USB33_EXT_XTL1_EN |
		//BIT_LDO_USB33_EXT_XTL2_EN |
		//BIT_LDO_USB33_EXT_XTL3_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN8,
		//BIT_LDO_KPLED_EXT_XTL0_EN |
		//BIT_LDO_KPLED_EXT_XTL1_EN |
		//BIT_LDO_KPLED_EXT_XTL2_EN |
		//BIT_LDO_KPLED_EXT_XTL3_EN |
		//BIT_LDO_VIBR_EXT_XTL0_EN |
		//BIT_LDO_VIBR_EXT_XTL1_EN |
		//BIT_LDO_VIBR_EXT_XTL2_EN |
		//BIT_LDO_VIBR_EXT_XTL3_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN9,
		BIT_LDO_CON_EXT_XTL0_EN |
		//BIT_LDO_CON_EXT_XTL1_EN |
		//BIT_LDO_CON_EXT_XTL2_EN |
		//BIT_LDO_CON_EXT_XTL3_EN |
		//BIT_LDO_AVDD18_EXT_XTL0_EN |
		//BIT_LDO_AVDD18_EXT_XTL1_EN |
		//BIT_LDO_AVDD18_EXT_XTL2_EN |
		//BIT_LDO_AVDD18_EXT_XTL3_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN10,
		BIT_LDO_WIFIPA_EXT_XTL0_EN |
		//BIT_LDO_WIFIPA_EXT_XTL1_EN |
		//BIT_LDO_WIFIPA_EXT_XTL2_EN |
		//BIT_LDO_WIFIPA_EXT_XTL3_EN |
		0
	);
	ANA_REG_SET(ANA_REG_GLB_XTL_WAIT_CTRL,
		//BIT_RSV |
		BIT_CUR_SEL |
		//BIT_EXT_XTL3_FOR_26M_EN |
		//BIT_EXT_XTL2_FOR_26M_EN |
		//BIT_EXT_XTL1_FOR_26M_EN |
		BIT_EXT_XTL0_FOR_26M_EN |
		BIT_SLP_XTLBUF_PD_EN |
		BIT_XTL_EN |
		BITS_XTL_WAIT(0x32) |
		0
	);

	/*when bring up we power on all dcdc & ldo*/
	DCDC_ldo_power_on();

#endif
}

void sprd_pmu_lowpower_init(void)
{
#ifdef CONFIG_FPGA
	return;
#endif
	pmic_lowpower_config(0x00000000);
	CSP_Init(0x50001800);
}
