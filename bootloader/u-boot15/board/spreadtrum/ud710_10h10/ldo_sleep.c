#include <asm/arch-sc9630/sci_types.h>
#include <adi_hal_internal.h>
#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>

#define WARNING_MESSAGE					\
"***********************************************\n"	\
"*                                             *\n"	\
"*  This version does not support AA chip !!!  *\n"	\
"*                                             *\n"	\
"***********************************************\n"

#define REFOUT0_ON				BIT(0)
#define REFOUT1_ON				BIT(1)
#define REFOUT2_ON				BIT(2)
#define REFOUT3_ON				BIT(3)
#define REFOUT4_ON				BIT(4)

#ifndef ROC1_CHIP_VER_AA
#define ROC1_CHIP_VER_AA             1
#endif
#ifndef ROC1_CHIP_VER_AB
#define ROC1_CHIP_VER_AB             3
#endif

#define CONFIG_DCDCCORE_DEEP_DROP_VOL  600
#define CONFIG_DCDCMODEM_DEEP_DROP_VOL 600
#define CONFIG_DCDCGPU_DEEP_DROP_VOL   600

void dcdc_ldo_power_on()
{
#if defined(CONFIG_ADIE_SC2730)
	/* In SC2730, this DCDC/LDO is power on default */
	//regulator_enable("vddsram");
	//regulator_enable("vddmemq");
	//regulator_enable("vddmodem");
	//regulator_enable("vdddcxo");
	//regulator_enable("vddgen0");
	//regulator_enable("vddgen1");
	//regulator_enable("vddmem");
	//regulator_enable("vddcore");
	//regulator_enable("vddcpu");
	//regulator_enable("vddgpu");
	//regulator_enable("avdd18");
	//regulator_enable("vdd28");
	//regulator_enable("vddemmccore"); //not emm which is used by efuse
	//regulator_enable("vddsdcore");
	//regulator_enable("vddsdio");
	//regulator_enable("vddusb33");
	//regulator_disable("vddrf1v8");  //used by ORCA refered by EXT_XTL_EN4 and ROC1 NTC
	//regulator_enable("avdd12");

	/* In SC2730, this LDO is power off default */
	//regulator_enable("vddrf1v25"); //used by ORCA not default on
	//regulator_enable("vddwcn");    //used by ORCA not default on
	//regulator_enable("vddcamio");  //regulator not support in u-boot
	//regulator_enable("vddcamd1");
	//regulator_enable("vddcamd0");
	//regulator_enable("vddcama0");
	//regulator_enable("vddcama1");
	//regulator_enable("vddcammot");
	//regulator_enable("vddsim0");
	//regulator_enable("vddsim1");
	//regulator_enable("vddsim2");
	//regulator_enable("vddwifipa");
	//regulator_enable("vddldo0");
	regulator_enable("vddldo1");
	regulator_enable("vddldo2");
#endif
}

static void dcdccore_deep_drop_config(u32 sleep_voltage)
{
	uint32_t drop_val;

	drop_val = (sleep_voltage * 1000U) / 3125U;
	ANA_REG_SET(ANA_REG_GLB_DCDC_CORE_SLP_CTRL1, BITS_DCDC_CORE_CTRL_DS_SW(drop_val));
}

static void pmic_lowpower_config(void)
{
#if defined(CONFIG_ADIE_SC2730)
	uint32_t adie_id;
	uint32_t drop_val;


	adie_id = ANA_REG_GET(ANA_REG_GLB_CHIP_ID_LOW);

	/* DCDC and LDO power globle control */
	ANA_REG_SET(ANA_REG_GLB_PWR_WR_PROT_VALUE, 0x6E7F);
	while((ANA_REG_GET(ANA_REG_GLB_PWR_WR_PROT_VALUE) & 0x8000) != 0x8000);
	ANA_REG_SET(ANA_REG_GLB_POWER_PD_SW,
		//BIT_DCDC_SRAM_PD |
		//BIT_DCDC_MEMQ_PD |
		//BIT_DCDC_MODEM_PD |
		//BIT_LDO_VDD18_DCXO_PD |
		//BIT_LDO_EMM_PD |
		//BIT_DCDC_GEN0_PD |
		//BIT_DCDC_GEN1_PD |
		//BIT_DCDC_MEM_PD |
		//BIT_DCDC_CORE_PD |
		//BIT_DCDC_CPU_PD |
		//BIT_DCDC_GPU_PD |
		//BIT_LDO_AVDD18_PD |
		//BIT_LDO_VDD28_PD |
		//BIT_BG_PD |
		0
	);
	ANA_REG_SET(ANA_REG_GLB_PWR_WR_PROT_VALUE, 0x0000);

	//ADIE sleep globle control
	ANA_REG_SET(ANA_REG_GLB_SLP_CTRL,
		BIT_LDO_XTL_EN |			//DCDC and LDO can control by EXT_XTL pin
		BIT_SLP_IO_EN |				//ADIE io can into sleep mode when CHIP_SLEEP high
		BIT_SLP_LDO_PD_EN |			//DCDC and LDO can pd in sleep mode
		0
	);

	ANA_REG_SET(ANA_REG_GLB_SLP_DCDC_PD_CTRL,
		//BIT_SLP_DCDCMODEM_PD_EN |     //ASIC design not pd
		//BIT_SLP_DCDCMEMQ_PD_EN |      //for ddr keep on even sleep
		BIT_SLP_DCDCSRAM_PD_EN |        //GPU/MM/AP/Ananke/corinth/cpu top
		//BIT_SLP_DCDCSRAM_DROP_EN |
		BIT_SLP_DCDCMODEM_DROP_EN |
		BIT_SLP_DCDCGPU_DROP_EN |
		BIT_SLP_DCDCCORE_DROP_EN |
		//BIT_SLP_DCDCWPA_PD_EN |       //2h10 board not used
		//BIT_SLP_DCDCGPU_PD_EN |       //ASIC design not pd
		//BIT_SLP_DCDCCPU_PD_EN |       //AI use. should shutdown by user self
		//BIT_SLP_DCDCGEN1_PD_EN |
		0
	);

	drop_val = (CONFIG_DCDCMODEM_DEEP_DROP_VOL * 1000U) / 3125U;
	ANA_REG_SET(ANA_REG_GLB_DCDC_MODEM_SLP_CTRL1, BITS_DCDC_MODEM_CTRL_DS_SW(drop_val));

	drop_val = (CONFIG_DCDCGPU_DEEP_DROP_VOL * 1000U) / 3125U;
	ANA_REG_SET(ANA_REG_GLB_DCDC_GPU_SLP_CTRL1, BITS_DCDC_GPU_CTRL_DS_SW(drop_val));

	/*
	 * CHIP_ID BA:0xB000 AB:A-0001 AA 0xA-0000
	 * only BA CHIP can config DCDCGPU & DCDCCORE SLP_LP
	 * adie_id is the ADIE CHIP_ID low 16 bits
	 */
	if (adie_id < 0xB000) {
		ANA_REG_SET(ANA_REG_GLB_SLP_DCDC_LP_CTRL,
			BIT_SLP_DCDCSRAM_LP_EN |
			BIT_SLP_DCDCMODEM_LP_EN |
			BIT_SLP_DCDCMEMQ_LP_EN |
			BIT_SLP_DCDCMEM_LP_EN |
			//BIT_SLP_DCDCGPU_LP_EN |      //cannot config slp_lp
			//BIT_SLP_DCDCCORE_LP_EN |     //cannot config slp_lp
			BIT_SLP_DCDCCPU_LP_EN |        //AI use
			//BIT_SLP_DCDCGEN1_LP_EN |
			BIT_SLP_DCDCGEN0_LP_EN |
			BIT_SLP_DCDCWPA_LP_EN |
			0
		);
	} else {
		ANA_REG_SET(ANA_REG_GLB_SLP_DCDC_LP_CTRL,
			BIT_SLP_DCDCSRAM_LP_EN |
			BIT_SLP_DCDCMODEM_LP_EN |
			BIT_SLP_DCDCMEMQ_LP_EN |
			BIT_SLP_DCDCMEM_LP_EN |
			BIT_SLP_DCDCGPU_LP_EN |
			BIT_SLP_DCDCCORE_LP_EN |
			BIT_SLP_DCDCCPU_LP_EN |        //AI use
			//BIT_SLP_DCDCGEN1_LP_EN |
			BIT_SLP_DCDCGEN0_LP_EN |
			BIT_SLP_DCDCWPA_LP_EN |
			0
		);
	}

	ANA_REG_SET(ANA_REG_GLB_SLP_LDO_PD_CTRL0,
		BIT_SLP_LDO_VDDRF1V8_PD_EN |  //ORCA refered by EXT_XTL_EN4 and ROC NTC use
		//BIT_SLP_LDO_VDDRF1V25_PD_EN |   //ORCA use, only refered by EXT_XTL_EN4
		//BIT_SLP_LDO_VDDEMMCCORE_PD_EN | //EMMC use.should shutdown by user self
		BIT_SLP_LDO_VDD18_DCXO_PD_EN |  //has 32k dcxo need sleep_pd
		//BIT_SLP_LDO_VDDWIFIPA_PD_EN | //Marlin use.should shutdown by user self
		//BIT_SLP_LDO_VDD28_PD_EN |     //keep on
		//BIT_SLP_LDO_VDDSDCORE_PD_EN | //sd use.should shutdown by user self
		//BIT_SLP_LDO_VDDSDIO_PD_EN |   //sd use.should shutdown by user self
		//BIT_SLP_LDO_VDDUSB33_PD_EN |  //usb use.should shutdown by user self
		//BIT_SLP_LDO_VDDCAMMOT_PD_EN | //camera use.should shutdown by user self
		//BIT_SLP_LDO_VDDCAMIO_PD_EN |  //camera use.should shutdown by user self
		//BIT_SLP_LDO_VDDCAMD0_PD_EN |  //camera use.should shutdown by user self
		//BIT_SLP_LDO_VDDCAMA0_PD_EN |  //camera use.should shutdown by user self
		//BIT_SLP_LDO_VDDSIM2_PD_EN |   //not use
		//BIT_SLP_LDO_VDDSIM1_PD_EN |   //not use
		0
	);

	ANA_REG_SET(ANA_REG_GLB_SLP_LDO_PD_CTRL1,
		//BIT_SLP_LDO_VDDLDO2_PD_EN |  //type c use.should shutdown by user self
		BIT_SLP_LDO_AVDD12_PD_EN |     //csi/dsi/ufs use
		//BIT_SLP_LDO_VDDWCN_PD_EN |   //ORCA use, only referd by EXT_EN4
		BIT_SLP_LDO_VDDLDO0_PD_EN |    //marlin use
		//BIT_SLP_LDO_VDDCAMD1_PD_EN | //camera use.should shutdown by user self
		//BIT_SLP_LDO_VDDCAMA1_PD_EN | //camera use.should shutdown by user self
		//BIT_SLP_LDO_VDDSIM0_PD_EN |  //sim0 use.should shutdown by user self
		BIT_SLP_LDO_AVDD18_PD_EN |     //pcie/ufs/dsi/usb/marlin...marlin config later--temp configure here
		//BIT_SLP_LDO_VDDLDO1_PD_EN |  //marlin use
		0
	);

	//slp_lp need check with HW
	ANA_REG_SET(ANA_REG_GLB_SLP_LDO_LP_CTRL0,
		BIT_SLP_LDO_VDDRF1V8_LP_EN |
		//BIT_SLP_LDO_VDDRF1V25_LP_EN |
		//BIT_SLP_LDO_VDDEMMCCORE_LP_EN |
		//BIT_SLP_LDO_VDD18_DCXO_LP_EN |
		//BIT_SLP_LDO_VDDWIFIPA_LP_EN |
		BIT_SLP_LDO_VDD28_LP_EN |
		//BIT_SLP_LDO_VDDSDCORE_LP_EN |
		//BIT_SLP_LDO_VDDSDIO_LP_EN |
		//BIT_SLP_LDO_VDDUSB33_LP_EN |
		//BIT_SLP_LDO_VDDCAMMOT_LP_EN |
		//BIT_SLP_LDO_VDDCAMD0_LP_EN |
		//BIT_SLP_LDO_VDDCAMA0_LP_EN |
		//BIT_SLP_LDO_VDDSIM2_LP_EN |
		//BIT_SLP_LDO_VDDSIM1_LP_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_SLP_LDO_LP_CTRL1,
		//BIT_SLP_LDO_VDDLDO2_LP_EN |
		//BIT_SLP_LDO_AVDD12_LP_EN |
		BIT_SLP_LDO_VDDWCN_LP_EN |
		//BIT_SLP_LDO_VDDCAMD1_LP_EN |
		//BIT_SLP_LDO_VDDCAMA1_LP_EN |
		//BIT_SLP_LDO_VDDLDO0_LP_EN |
		//BIT_SLP_LDO_VDDSIM0_LP_EN |
		BIT_SLP_LDO_AVDD18_LP_EN |
		//BIT_SLP_LDO_VDDLDO1_LP_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_DCDC_XTL_EN,
		BIT_DCDC_CORE_EXT_XTL0_EN |
		//BIT_DCDC_CORE_EXT_XTL1_EN |
		BIT_DCDC_CORE_EXT_XTL2_EN |
		//BIT_DCDC_CORE_EXT_XTL3_EN |
		//BIT_DCDC_CORE_EXT_XTL4_EN |
		//BIT_DCDC_CORE_EXT_XTL5_EN |
		//BIT_DCDC_WPA_EXT_XTL0_EN |
		//BIT_DCDC_WPA_EXT_XTL1_EN |
		//BIT_DCDC_WPA_EXT_XTL2_EN |
		//BIT_DCDC_WPA_EXT_XTL3_EN |
		//BIT_DCDC_WPA_EXT_XTL4_EN |
		//BIT_DCDC_WPA_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_DCDC_XTL_EN0,
		//BIT_DCDC_GEN0_EXT_XTL0_EN |
		//BIT_DCDC_GEN0_EXT_XTL1_EN |
		//BIT_DCDC_GEN0_EXT_XTL2_EN |
		//BIT_DCDC_GEN0_EXT_XTL3_EN |
		//BIT_DCDC_GEN0_EXT_XTL4_EN |
		//BIT_DCDC_GEN0_EXT_XTL5_EN |
		BIT_DCDC_SRAM_EXT_XTL0_EN |
		//BIT_DCDC_SRAM_EXT_XTL1_EN |
		//BIT_DCDC_SRAM_EXT_XTL2_EN |
		//BIT_DCDC_SRAM_EXT_XTL3_EN |
		//BIT_DCDC_SRAM_EXT_XTL4_EN |
		//BIT_DCDC_SRAM_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_DCDC_XTL_EN1,
		//BIT_DCDC_CPU_EXT_XTL0_EN |
		//BIT_DCDC_CPU_EXT_XTL1_EN |
		//BIT_DCDC_CPU_EXT_XTL2_EN |
		//BIT_DCDC_CPU_EXT_XTL3_EN |
		//BIT_DCDC_CPU_EXT_XTL4_EN |
		//BIT_DCDC_CPU_EXT_XTL5_EN |
		BIT_DCDC_GPU_EXT_XTL0_EN |
		//BIT_DCDC_GPU_EXT_XTL1_EN |
		//BIT_DCDC_GPU_EXT_XTL2_EN |
		//BIT_DCDC_GPU_EXT_XTL3_EN |
		//BIT_DCDC_GPU_EXT_XTL4_EN |
		//BIT_DCDC_GPU_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_DCDC_XTL_EN2,
		//BIT_DCDC_MEM_EXT_XTL0_EN |
		//BIT_DCDC_MEM_EXT_XTL1_EN |
		//BIT_DCDC_MEM_EXT_XTL2_EN |
		//BIT_DCDC_MEM_EXT_XTL3_EN |
		//BIT_DCDC_MEM_EXT_XTL4_EN |
		//BIT_DCDC_MEM_EXT_XTL5_EN |
		//BIT_DCDC_GEN1_EXT_XTL0_EN |
		//BIT_DCDC_GEN1_EXT_XTL1_EN |
		//BIT_DCDC_GEN1_EXT_XTL2_EN |
		//BIT_DCDC_GEN1_EXT_XTL3_EN | //WB_CLK_REQ
		//BIT_DCDC_GEN1_EXT_XTL4_EN | //because vddrf1v25 refered EXT_XTL_EN4
		//BIT_DCDC_GEN1_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_DCDC_XTL_EN3,
		//BIT_DCDC_MEMQ_EXT_XTL0_EN |
		//BIT_DCDC_MEMQ_EXT_XTL1_EN |
		//BIT_DCDC_MEMQ_EXT_XTL2_EN |
		//BIT_DCDC_MEMQ_EXT_XTL3_EN |
		//BIT_DCDC_MEMQ_EXT_XTL4_EN |
		//BIT_DCDC_MEMQ_EXT_XTL5_EN |
		//BIT_DCDC_MODEM_EXT_XTL0_EN |
		//BIT_DCDC_MODEM_EXT_XTL1_EN |
		//BIT_DCDC_MODEM_EXT_XTL2_EN |
		//BIT_DCDC_MODEM_EXT_XTL3_EN |
		//BIT_DCDC_MODEM_EXT_XTL4_EN |
		//BIT_DCDC_MODEM_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN0,
		BIT_LDO_VDD18_DCXO_EXT_XTL0_EN |
		//BIT_LDO_VDD18_DCXO_EXT_XTL1_EN |
		//BIT_LDO_VDD18_DCXO_EXT_XTL2_EN |
		//BIT_LDO_VDD18_DCXO_EXT_XTL3_EN |
		BIT_LDO_VDD18_DCXO_EXT_XTL4_EN |
		BIT_LDO_VDD18_DCXO_EXT_XTL5_EN |
		//BIT_LDO_VDD28_EXT_XTL0_EN |
		//BIT_LDO_VDD28_EXT_XTL1_EN |
		//BIT_LDO_VDD28_EXT_XTL2_EN |
		//BIT_LDO_VDD28_EXT_XTL3_EN |
		//BIT_LDO_VDD28_EXT_XTL4_EN |
		//BIT_LDO_VDD28_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN1,
		//BIT_LDO_VDDRF1V8_EXT_XTL0_EN |
		//BIT_LDO_VDDRF1V8_EXT_XTL1_EN |
		//BIT_LDO_VDDRF1V8_EXT_XTL2_EN |
		//BIT_LDO_VDDRF1V8_EXT_XTL3_EN |
		BIT_LDO_VDDRF1V8_EXT_XTL4_EN |   //ORCA use
		//BIT_LDO_VDDRF1V8_EXT_XTL5_EN |
		//BIT_LDO_VDDRF1V25_EXT_XTL0_EN |
		//BIT_LDO_VDDRF1V25_EXT_XTL1_EN |
		//BIT_LDO_VDDRF1V25_EXT_XTL2_EN |
		//BIT_LDO_VDDRF1V25_EXT_XTL3_EN |
		BIT_LDO_VDDRF1V25_EXT_XTL4_EN |  //ORCA use
		//BIT_LDO_VDDRF1V25_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN2,
		//BIT_LDO_VDDSIM0_EXT_XTL0_EN |
		//BIT_LDO_VDDSIM0_EXT_XTL1_EN |
		//BIT_LDO_VDDSIM0_EXT_XTL2_EN |
		//BIT_LDO_VDDSIM0_EXT_XTL3_EN |
		//BIT_LDO_VDDSIM0_EXT_XTL4_EN |
		//BIT_LDO_VDDSIM0_EXT_XTL5_EN |
		//BIT_LDO_VDDSIM1_EXT_XTL0_EN |
		//BIT_LDO_VDDSIM1_EXT_XTL1_EN |
		//BIT_LDO_VDDSIM1_EXT_XTL2_EN |
		//BIT_LDO_VDDSIM1_EXT_XTL3_EN |
		//BIT_LDO_VDDSIM1_EXT_XTL4_EN |
		//BIT_LDO_VDDSIM1_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN3,
		//BIT_LDO_VDDSIM2_EXT_XTL0_EN |
		//BIT_LDO_VDDSIM2_EXT_XTL1_EN |
		//BIT_LDO_VDDSIM2_EXT_XTL2_EN |
		//BIT_LDO_VDDSIM2_EXT_XTL3_EN |
		//BIT_LDO_VDDSIM2_EXT_XTL4_EN |
		//BIT_LDO_VDDSIM2_EXT_XTL5_EN |
		//BIT_LDO_AVDD12_EXT_XTL0_EN |
		//BIT_LDO_AVDD12_EXT_XTL1_EN |
		//BIT_LDO_AVDD12_EXT_XTL2_EN |
		//BIT_LDO_AVDD12_EXT_XTL3_EN |
		//BIT_LDO_AVDD12_EXT_XTL4_EN |
		//BIT_LDO_AVDD12_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN4,
		//BIT_LDO_VDDCAMMOT_EXT_XTL0_EN |
		//BIT_LDO_VDDCAMMOT_EXT_XTL1_EN |
		//BIT_LDO_VDDCAMMOT_EXT_XTL2_EN |
		//BIT_LDO_VDDCAMMOT_EXT_XTL3_EN |
		//BIT_LDO_VDDCAMMOT_EXT_XTL4_EN |
		//BIT_LDO_VDDCAMMOT_EXT_XTL5_EN |
		//BIT_LDO_VDDCAMIO_EXT_XTL0_EN |
		//BIT_LDO_VDDCAMIO_EXT_XTL1_EN |
		//BIT_LDO_VDDCAMIO_EXT_XTL2_EN |
		//BIT_LDO_VDDCAMIO_EXT_XTL3_EN |
		//BIT_LDO_VDDCAMIO_EXT_XTL4_EN |
		//BIT_LDO_VDDCAMIO_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN5,
		//BIT_LDO_VDDCAMA0_EXT_XTL0_EN |
		//BIT_LDO_VDDCAMA0_EXT_XTL1_EN |
		//BIT_LDO_VDDCAMA0_EXT_XTL2_EN |
		//BIT_LDO_VDDCAMA0_EXT_XTL3_EN |
		//BIT_LDO_VDDCAMA0_EXT_XTL4_EN |
		//BIT_LDO_VDDCAMA0_EXT_XTL5_EN |
		//BIT_LDO_VDDCAMA1_EXT_XTL0_EN |
		//BIT_LDO_VDDCAMA1_EXT_XTL1_EN |
		//BIT_LDO_VDDCAMA1_EXT_XTL2_EN |
		//BIT_LDO_VDDCAMA1_EXT_XTL3_EN |
		//BIT_LDO_VDDCAMA1_EXT_XTL4_EN |
		//BIT_LDO_VDDCAMA1_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN6,
		//BIT_LDO_VDDCAMD0_EXT_XTL0_EN |
		//BIT_LDO_VDDCAMD0_EXT_XTL1_EN |
		//BIT_LDO_VDDCAMD0_EXT_XTL2_EN |
		//BIT_LDO_VDDCAMD0_EXT_XTL3_EN |
		//BIT_LDO_VDDCAMD0_EXT_XTL4_EN |
		//BIT_LDO_VDDCAMD0_EXT_XTL5_EN |
		//BIT_LDO_VDDCAMD1_EXT_XTL0_EN |
		//BIT_LDO_VDDCAMD1_EXT_XTL1_EN |
		//BIT_LDO_VDDCAMD1_EXT_XTL2_EN |
		//BIT_LDO_VDDCAMD1_EXT_XTL3_EN |
		//BIT_LDO_VDDCAMD1_EXT_XTL4_EN |
		//BIT_LDO_VDDCAMD1_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN7,
		//BIT_LDO_VDDSDIO_EXT_XTL0_EN |
		//BIT_LDO_VDDSDIO_EXT_XTL1_EN |
		//BIT_LDO_VDDSDIO_EXT_XTL2_EN |
		//BIT_LDO_VDDSDIO_EXT_XTL3_EN |
		//BIT_LDO_VDDSDIO_EXT_XTL4_EN |
		//BIT_LDO_VDDSDIO_EXT_XTL5_EN |
		//BIT_LDO_VDDSDCORE_EXT_XTL0_EN |
		//BIT_LDO_VDDSDCORE_EXT_XTL1_EN |
		//BIT_LDO_VDDSDCORE_EXT_XTL2_EN |
		//BIT_LDO_VDDSDCORE_EXT_XTL3_EN |
		//BIT_LDO_VDDSDCORE_EXT_XTL4_EN |
		//BIT_LDO_VDDSDCORE_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN8,
		//BIT_LDO_VDDEMMCCORE_EXT_XTL0_EN |
		//BIT_LDO_VDDEMMCCORE_EXT_XTL1_EN |
		//BIT_LDO_VDDEMMCCORE_EXT_XTL2_EN |
		//BIT_LDO_VDDEMMCCORE_EXT_XTL3_EN |
		//BIT_LDO_VDDEMMCCORE_EXT_XTL4_EN |
		//BIT_LDO_VDDEMMCCORE_EXT_XTL5_EN |
		//BIT_LDO_VDDUSB33_EXT_XTL0_EN |
		//BIT_LDO_VDDUSB33_EXT_XTL1_EN |
		//BIT_LDO_VDDUSB33_EXT_XTL2_EN |
		//BIT_LDO_VDDUSB33_EXT_XTL3_EN |
		//BIT_LDO_VDDUSB33_EXT_XTL4_EN |
		//BIT_LDO_VDDUSB33_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN9,
		//BIT_LDO_VDDKPLED_EXT_XTL0_EN |
		//BIT_LDO_VDDKPLED_EXT_XTL1_EN |
		//BIT_LDO_VDDKPLED_EXT_XTL2_EN |
		//BIT_LDO_VDDKPLED_EXT_XTL3_EN |
		//BIT_LDO_VDDKPLED_EXT_XTL4_EN |
		//BIT_LDO_VDDKPLED_EXT_XTL5_EN |
		//BIT_LDO_VDDVIB_EXT_XTL0_EN |
		//BIT_LDO_VDDVIB_EXT_XTL1_EN |
		//BIT_LDO_VDDVIB_EXT_XTL2_EN |
		//BIT_LDO_VDDVIB_EXT_XTL3_EN |
		//BIT_LDO_VDDVIB_EXT_XTL4_EN |
		//BIT_LDO_VDDVIB_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN10,
		//BIT_LDO_VDDWCN_EXT_XTL0_EN |
		//BIT_LDO_VDDWCN_EXT_XTL1_EN |
		//BIT_LDO_VDDWCN_EXT_XTL2_EN |
		//BIT_LDO_VDDWCN_EXT_XTL3_EN |
		BIT_LDO_VDDWCN_EXT_XTL4_EN |  //ORCA use
		//BIT_LDO_VDDWCN_EXT_XTL5_EN |
		//BIT_LDO_AVDD18_EXT_XTL0_EN |
		//BIT_LDO_AVDD18_EXT_XTL1_EN |
		//BIT_LDO_AVDD18_EXT_XTL2_EN |
		//BIT_LDO_AVDD18_EXT_XTL3_EN |
		//BIT_LDO_AVDD18_EXT_XTL4_EN |
		//BIT_LDO_AVDD18_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN11,
		//BIT_LDO_VDDLDO0_EXT_XTL0_EN |
		//BIT_LDO_VDDLDO0_EXT_XTL1_EN |
		//BIT_LDO_VDDLDO0_EXT_XTL2_EN |
		BIT_LDO_VDDLDO0_EXT_XTL3_EN |
		//BIT_LDO_VDDLDO0_EXT_XTL4_EN |
		//BIT_LDO_VDDLDO0_EXT_XTL5_EN |
		//BIT_LDO_VDDWIFIPA_EXT_XTL0_EN |
		//BIT_LDO_VDDWIFIPA_EXT_XTL1_EN |
		//BIT_LDO_VDDWIFIPA_EXT_XTL2_EN |
		//BIT_LDO_VDDWIFIPA_EXT_XTL3_EN |
		//BIT_LDO_VDDWIFIPA_EXT_XTL4_EN |
		//BIT_LDO_VDDWIFIPA_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_LDO_XTL_EN12,
		//BIT_LDO_VDDLDO2_EXT_XTL0_EN |
		//BIT_LDO_VDDLDO2_EXT_XTL1_EN |
		//BIT_LDO_VDDLDO2_EXT_XTL2_EN |
		//BIT_LDO_VDDLDO2_EXT_XTL3_EN |
		//BIT_LDO_VDDLDO2_EXT_XTL4_EN |
		//BIT_LDO_VDDLDO2_EXT_XTL5_EN |
		//BIT_LDO_VDDLDO1_EXT_XTL0_EN |
		//BIT_LDO_VDDLDO1_EXT_XTL1_EN |
		//BIT_LDO_VDDLDO1_EXT_XTL2_EN |
		//BIT_LDO_VDDLDO1_EXT_XTL3_EN |
		//BIT_LDO_VDDLDO1_EXT_XTL4_EN |
		//BIT_LDO_VDDLDO1_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_DCXO_XTL_EN,
		//BIT_TSX_XO_EXT_XTL0_EN |
		//BIT_TSX_XO_EXT_XTL1_EN |
		//BIT_TSX_XO_EXT_XTL2_EN |
		//BIT_TSX_XO_EXT_XTL3_EN |
		//BIT_TSX_XO_EXT_XTL4_EN |
		//BIT_TSX_XO_EXT_XTL5_EN |
		//BIT_XO_EXT_XTL0_EN |
		//BIT_XO_EXT_XTL1_EN |
		//BIT_XO_EXT_XTL2_EN |
		//BIT_XO_EXT_XTL3_EN |
		//BIT_XO_EXT_XTL4_EN |
		//BIT_XO_EXT_XTL5_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_TSX_CTRL1,
		BIT_DCXO_26M_REF_OUT0_EXT_XTL0_EN |
		//BIT_DCXO_26M_REF_OUT1_EXT_XTL0_EN |
		//BIT_DCXO_26M_REF_OUT2_EXT_XTL0_EN |
		//BIT_DCXO_26M_REF_OUT3_EXT_XTL0_EN |
		//BIT_DCXO_26M_REF_OUT4_EXT_XTL0_EN |
		//BIT_DCXO_26M_REF_OUT0_EXT_XTL1_EN |
		//BIT_DCXO_26M_REF_OUT1_EXT_XTL1_EN |
		//BIT_DCXO_26M_REF_OUT2_EXT_XTL1_EN |
		//BIT_DCXO_26M_REF_OUT3_EXT_XTL1_EN |
		//BIT_DCXO_26M_REF_OUT4_EXT_XTL1_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_TSX_CTRL2,
		//BIT_DCXO_26M_REF_OUT0_EXT_XTL2_EN |
		//BIT_DCXO_26M_REF_OUT1_EXT_XTL2_EN |
		//BIT_DCXO_26M_REF_OUT2_EXT_XTL2_EN |
		//BIT_DCXO_26M_REF_OUT3_EXT_XTL2_EN |
		//BIT_DCXO_26M_REF_OUT4_EXT_XTL2_EN |
		//BIT_DCXO_26M_REF_OUT0_EXT_XTL3_EN |
		//BIT_DCXO_26M_REF_OUT1_EXT_XTL3_EN |
		//BIT_DCXO_26M_REF_OUT2_EXT_XTL3_EN |
		//BIT_DCXO_26M_REF_OUT3_EXT_XTL3_EN |
		//BIT_DCXO_26M_REF_OUT4_EXT_XTL3_EN |
		0
	);

	ANA_REG_SET(ANA_REG_GLB_TSX_CTRL3,
		BIT_DCXO_26M_REF_OUT0_EXT_XTL4_EN |
		BIT_DCXO_26M_REF_OUT1_EXT_XTL4_EN |
		//BIT_DCXO_26M_REF_OUT2_EXT_XTL4_EN |
		//BIT_DCXO_26M_REF_OUT3_EXT_XTL4_EN |
		//BIT_DCXO_26M_REF_OUT4_EXT_XTL4_EN |
		//BIT_DCXO_26M_REF_OUT0_EXT_XTL5_EN |
		//BIT_DCXO_26M_REF_OUT1_EXT_XTL5_EN |
		BIT_DCXO_26M_REF_OUT2_EXT_XTL5_EN |
		//BIT_DCXO_26M_REF_OUT3_EXT_XTL5_EN |
		//BIT_DCXO_26M_REF_OUT4_EXT_XTL5_EN |
		//BIT_SLP_DCXO_LP_EN |               //has 32k-crystal
		//BIT_DCXO_CORE_AML_CAL_EN |
		BITS_CLK_DCXO_SEL(0x00) |
		0
	);

	//32K-less lp config but 2h10 has 32k-crystal
	//ANA_REG_OR(ANA_REG_GLB_CLK32KLESS_CTRL0, BIT_SLP_XO_LOW_CUR_EN);

	//Refout config
	ANA_REG_SET(ANA_REG_GLB_TSX_CTRL0,
		//BIT_DCXO_26M_REF_OUT4_PIN_EXT_XTL0_EN |
		//BIT_DCXO_26M_REF_OUT4_PIN_EXT_XTL1_EN |
		//BIT_DCXO_26M_REF_OUT4_PIN_EXT_XTL2_EN |
		//BIT_DCXO_26M_REF_OUT4_PIN_EXT_XTL3_EN |
		//BIT_DCXO_26M_REF_OUT4_PIN_EXT_XTL4_EN |
		//BIT_DCXO_26M_REF_OUT4_PIN_EXT_XTL5_EN |
		BIT_SLP_DCXO_26M_REF_OUT0_EN |
		BIT_SLP_DCXO_26M_REF_OUT1_EN |
		BIT_SLP_DCXO_26M_REF_OUT2_EN |
		BIT_SLP_DCXO_26M_REF_OUT3_EN |
		BIT_SLP_DCXO_26M_REF_OUT4_EN |
		BITS_DCXO_26M_REF_OUT_EN(REFOUT3_ON) |
		0
	);

	//Pin exit slp config
	ANA_REG_SET(ANA_REG_GLB_XTL_WAIT_CTRL0,
		//BIT_EXT_XTL5_FOR_26M_EN |
		//BIT_EXT_XTL4_FOR_26M_EN |
		BIT_EXT_XTL3_FOR_26M_EN |
		BIT_EXT_XTL2_FOR_26M_EN |
		BIT_EXT_XTL1_FOR_26M_EN |
		BIT_EXT_XTL0_FOR_26M_EN |
		BIT_SLP_XTLBUF_PD_EN |
		BIT_XTL_EN |
		BITS_XTL_WAIT(0x32) |
		0
	);

	/*turn on/off anyone of refout, phase noise will be worse.
	 *So decrease drive level.
	 *default is less than 0.36K
	 *0x7: REFOUT0/1/2/3/4 DRV_LEVEL 0.36K
	 *0x6: REFOUT0/1/2/3/4 DRV_LEVEL 0.45K
	 *0x5: REFOUT0/1/2/3/4 DRV_LEVEL 0.6K
	 *0x4: REFOUT0/1/2/3/4 DRV_LEVEL 0.9K
	 *0x3: REFOUT0/1/2/3/4 DRV_LEVEL 0.6K
	 *0x2: REFOUT0/1/2/3/4 DRV_LEVEL 0.9K
	 *0x1: REFOUT0/1/2/3/4 DRV_LEVEL 1.8K
	*/
	//default 0x1f : bypass refout0~refout4, drv lvl is highest
	ANA_REG_MSK_OR(ANA_REG_GLB_TSX_CTRL14, BITS_DCXO_26M_REF_BUF_OUTPUT_BYPASS(0x1f), BITS_DCXO_26M_REF_BUF_OUTPUT_BYPASS(~0));
	ANA_REG_MSK_OR(ANA_REG_GLB_TSX_CTRL14, BITS_DCXO_26M_REF_BUF0_DRV_LEVEL_CTRL(0x6), BITS_DCXO_26M_REF_BUF0_DRV_LEVEL_CTRL(~0));
	ANA_REG_MSK_OR(ANA_REG_GLB_TSX_CTRL14, BITS_DCXO_26M_REF_BUF1_DRV_LEVEL_CTRL(0x6), BITS_DCXO_26M_REF_BUF1_DRV_LEVEL_CTRL(~0));
	ANA_REG_MSK_OR(ANA_REG_GLB_TSX_CTRL4, BITS_DCXO_26M_REF_BUF2_DRV_LEVEL_CTRL(0x6), BITS_DCXO_26M_REF_BUF2_DRV_LEVEL_CTRL(~0));
	ANA_REG_MSK_OR(ANA_REG_GLB_TSX_CTRL4, BITS_DCXO_26M_REF_BUF3_DRV_LEVEL_CTRL(0x6), BITS_DCXO_26M_REF_BUF3_DRV_LEVEL_CTRL(~0));
	ANA_REG_MSK_OR(ANA_REG_GLB_TSX_CTRL4, BITS_DCXO_26M_REF_BUF4_DRV_LEVEL_CTRL(0x6), BITS_DCXO_26M_REF_BUF4_DRV_LEVEL_CTRL(~0));
#endif
}

void sprd_pmu_lowpower_init(void)
{
#ifndef CONFIG_FPGA
	if (ROC1_CHIP_VER_AA == CHIP_REG_GET(REG_AON_APB_AON_VER_ID)) {
		printf("\n\n%s\n", WARNING_MESSAGE);
		while(1);
	}
#if defined(CONFIG_SUPPORT_LOWPOWER)
	//Config the ADIE lowpower
	pmic_lowpower_config();

	//Config pmu paratmers
	CSP_Init(0);

	//DCDCCORE drop config
	dcdccore_deep_drop_config(CONFIG_DCDCCORE_DEEP_DROP_VOL);
#endif

	//Power on other dcdc/ldo
	dcdc_ldo_power_on();
#endif
}
