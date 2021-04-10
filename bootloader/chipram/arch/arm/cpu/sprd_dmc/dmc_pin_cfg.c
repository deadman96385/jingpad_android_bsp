#include <asm/types.h>
#include "asm/arch/clk_para_config.h"
#include "dmc_sprd_r1p0.h"
#include "dmc_sprd_misc.h"
#include "dmc_pin_cfg.h"

#define PIN_EB0_REG_ADDR 0x402e0000

static DMC_PIN_DRV_INFO pin_drv_info[] = {
	{DMC_PIN_DQ_BYTE0,	REG_DRV_PIN_DQ_BYTE0, 	DRV_PIN_POS_DQ_BYTE0, 	DRV_PIN_NEG_DQ_BYTE0},
	{DMC_PIN_DQS0_T, 	REG_DRV_PIN_DQS0_T, 	DRV_PIN_POS_DQS0_T, 	DRV_PIN_NEG_DQS0_T},
	{DMC_PIN_CA, 		REG_DRV_PIN_CA, 		DRV_PIN_POS_CA, 		DRV_PIN_NEG_CA},
	{DMC_PIN_CK_T, 		REG_DRV_PIN_CK_T, 		DRV_PIN_POS_CK_T, 		DRV_PIN_NEG_CK_T},
	{DMC_PIN_CS0, 		REG_DRV_PIN_CS0,		DRV_PIN_POS_CS0, 		DRV_PIN_NEG_CS0},
};

static DMC_PIN_DRV_INFO pin_drv_relevent[] = {
	{DMC_PIN_DQ_BYTE1,	REG_DRV_PIN_DQ_BYTE1, 	DRV_PIN_POS_DQ_BYTE1, 	DRV_PIN_NEG_DQ_BYTE1},
	{DMC_PIN_DQ_BYTE2,	REG_DRV_PIN_DQ_BYTE2, 	DRV_PIN_POS_DQ_BYTE2, 	DRV_PIN_NEG_DQ_BYTE2},
	{DMC_PIN_DQ_BYTE3,	REG_DRV_PIN_DQ_BYTE3, 	DRV_PIN_POS_DQ_BYTE3, 	DRV_PIN_NEG_DQ_BYTE3},

	{DMC_PIN_DQS0_C, 	REG_DRV_PIN_DQS0_C, 	DRV_PIN_POS_DQS0_C, 	DRV_PIN_NEG_DQS0_C},
	{DMC_PIN_DQS1_T, 	REG_DRV_PIN_DQS1_T, 	DRV_PIN_POS_DQS1_T, 	DRV_PIN_NEG_DQS1_T},
	{DMC_PIN_DQS1_C, 	REG_DRV_PIN_DQS1_C, 	DRV_PIN_POS_DQS1_C, 	DRV_PIN_NEG_DQS1_C},
	{DMC_PIN_DQS2_T, 	REG_DRV_PIN_DQS2_T, 	DRV_PIN_POS_DQS2_T, 	DRV_PIN_NEG_DQS2_T},
	{DMC_PIN_DQS2_C, 	REG_DRV_PIN_DQS2_C, 	DRV_PIN_POS_DQS2_C, 	DRV_PIN_NEG_DQS2_C},
	{DMC_PIN_DQS3_T, 	REG_DRV_PIN_DQS3_T, 	DRV_PIN_POS_DQS3_T, 	DRV_PIN_NEG_DQS3_T},
	{DMC_PIN_DQS3_C, 	REG_DRV_PIN_DQS3_C, 	DRV_PIN_POS_DQS3_C, 	DRV_PIN_NEG_DQS3_C},

	{DMC_PIN_CK_C, 		REG_DRV_PIN_CK_C, 		DRV_PIN_POS_CK_C, 		DRV_PIN_NEG_CK_C},

	{DMC_PIN_CS1, 		REG_DRV_PIN_CS1,		DRV_PIN_POS_CS1, 		DRV_PIN_NEG_CS1},
	{DMC_PIN_CKE0, 		REG_DRV_PIN_CKE0,		DRV_PIN_POS_CKE0, 		DRV_PIN_NEG_CKE0},
};

static DMC_PIN_PULL_INFO pin_pull_info[] =	{
	{DMC_PIN_DQS0_T, 	REG_DRV_PIN_DQS0_T, 	PULL_DQS0_T_RESIS_VAL},
	{DMC_PIN_DQS0_C, 	REG_DRV_PIN_DQS0_C, 	PULL_DQS0_C_RESIS_VAL},
	{DMC_PIN_DQS1_T, 	REG_DRV_PIN_DQS1_T, 	PULL_DQS1_T_RESIS_VAL},
	{DMC_PIN_DQS1_C, 	REG_DRV_PIN_DQS1_C, 	PULL_DQS1_C_RESIS_VAL},
	{DMC_PIN_DQS2_T, 	REG_DRV_PIN_DQS2_T, 	PULL_DQS2_T_RESIS_VAL},
	{DMC_PIN_DQS2_C, 	REG_DRV_PIN_DQS2_C, 	PULL_DQS2_C_RESIS_VAL},
	{DMC_PIN_DQS3_T, 	REG_DRV_PIN_DQS3_T, 	PULL_DQS3_T_RESIS_VAL},
	{DMC_PIN_DQS3_C, 	REG_DRV_PIN_DQS3_C, 	PULL_DQS3_C_RESIS_VAL},
};


void dmc_set_drv_target(int drv)
{
	int i;
	for(i=0; i<sizeof(pin_drv_info)/sizeof(DMC_PIN_DRV_INFO); i++)
	{
		pin_drv_info[i].drv_pos_target = drv;
		pin_drv_info[i].drv_neg_target = drv;
	}
}



int dmc_set_pin_drv_reg(DMC_PIN_TEAM_NAME pin, DMC_POLAR_TYPE polar, int factor)
{
	int i;
	u32 regval;
	for (i=0; i<sizeof(pin_drv_info)/sizeof(DMC_PIN_DRV_INFO); i++)
	{
		if (pin == pin_drv_info[i].name)
		{
			regval = REG32(pin_drv_info[i].drv_cfg_reg);
			if (DMC_POLAR_PMOS == polar)
			{
				regval = u32_bits_set(regval, 25, 5, (u32)factor);
			}
			else
			{
				regval = u32_bits_set(regval, 20, 5, (u32)factor);
			}
			REG32(pin_drv_info[i].drv_cfg_reg) = regval;
			return 0;
		}
	}

	for (i=0; i<sizeof(pin_drv_relevent)/sizeof(DMC_PIN_DRV_INFO); i++)
	{
		if (pin == pin_drv_relevent[i].name)
		{
			regval = REG32(pin_drv_relevent[i].drv_cfg_reg);
			if (DMC_POLAR_PMOS == polar)
			{
				regval = u32_bits_set(regval, 25, 5, (u32)factor);
			}
			else
			{
				regval = u32_bits_set(regval, 20, 5, (u32)factor);
			}
			REG32(pin_drv_relevent[i].drv_cfg_reg) = regval;
			return 0;
		}
	}
	return -1;
}

int dmc_zq_cal(DMC_POLAR_TYPE ploar, int target_drv)
{
	u32 drv_target_reg;
	u32 regval;
	u32 calover;
	int factor = -1;
	int i;
	static u32 nmos_val = 0;

	if (DMC_POLAR_NMOS == ploar)
	{
		nmos_val = 0;
	}
	

	if (target_drv>960 || target_drv<=0)
	{
		return -1;
	}
	
	/*set target driver strength*/
	drv_target_reg = DMC_CAL_RESISTANCE_ORG/target_drv;
	regval = REG32(REG_DDR_ZQ_CAL);
	regval = u32_bits_set(regval, 10, 5, drv_target_reg);
	/*clear zq_drvn zq_drvp*/
	regval = u32_bits_set(regval, 0, 5, nmos_val);
	regval = u32_bits_set(regval, 5, 5, 0);
	REG32(REG_DDR_ZQ_CAL) = regval;
	/*set target polar*/
	regval = REG32(REG_DDR_ZQ_CAL);
	if (DMC_POLAR_PMOS == ploar)
	{
		regval = u32_bits_set(regval, 15, 1, 1);
	}
	else
	{
		regval = u32_bits_set(regval, 15, 1, 0);
	}
	REG32(REG_DDR_ZQ_CAL) = regval;	
	dmc_sprd_delay(1);
	/*pull down to start cal*/
	regval = REG32(REG_DDR_ZQ_CAL);
	regval = u32_bits_set(regval, 16, 1, 0);
	REG32(REG_DDR_ZQ_CAL) = regval;
	dmc_sprd_delay(1);
	
	/*check if the org flag is right*/
	regval = REG32(REG_DDR_ZQ_CAL);
	regval &= 1<<17;
	if (DMC_POLAR_PMOS == ploar)
	{
		if (0 != regval)
		{
			return -1;
		}		
	}
	else
	{
		if (0 == regval)
		{
			return -1;

		}		
	}
	calover = regval;
	

	/*cal*/
	for (i=DMC_CAL_FACTOR_MIN; i<DMC_CAL_FACTOR_MAX; i++)
	{
		regval = REG32(REG_DDR_ZQ_CAL);
		if (DMC_POLAR_NMOS == ploar)
		{
			regval = u32_bits_set(regval, 0, 5, i-1);
		}
		else
		{
			regval = u32_bits_set(regval, 5, 5, i-1);
		}
		
		
		REG32(REG_DDR_ZQ_CAL) = regval;
		dmc_sprd_delay(1);
		regval = REG32(REG_DDR_ZQ_CAL);
		regval &= 1<<17;
		if (regval != calover)
		{
			factor = i-1;
			if (DMC_POLAR_NMOS == ploar)
			{
				nmos_val = factor;
			}
			break;
		}
		dmc_sprd_delay(1);
	}

	/*pull up to end calibration*/
	regval = REG32(REG_DDR_ZQ_CAL);
	regval = u32_bits_set(regval, 16, 1, 1);
	REG32(REG_DDR_ZQ_CAL) = regval;
	return factor;	
}

static void pin_reg_enable(void)
{
	REG32(PIN_EB0_REG_ADDR) |= 1<<20;
}

static void set_revelent_pin_drv(void)
{
	int pin_drv_cal_pos = 0, pin_drv_cal_neg = 0;
	int i;

	for (i=0; i<sizeof(pin_drv_relevent)/sizeof(DMC_PIN_DRV_INFO); i++)
	{
		switch(pin_drv_relevent[i].name)
		{
			case DMC_PIN_DQ_BYTE1:
			case DMC_PIN_DQ_BYTE2:
			case DMC_PIN_DQ_BYTE3:
				dmc_set_pin_drv_reg(pin_drv_relevent[i].name, DMC_POLAR_PMOS, pin_drv_info[0].drv_pos_target);
				dmc_set_pin_drv_reg(pin_drv_relevent[i].name, DMC_POLAR_NMOS, pin_drv_info[0].drv_neg_target);
				break;			
			case DMC_PIN_DQS1_T:			
			case DMC_PIN_DQS2_T:			
			case DMC_PIN_DQS3_T:			
				//dmc_set_pin_drv_reg(pin_drv_relevent[i].name, DMC_POLAR_PMOS, pin_drv_info[1].drv_pos_target+2);
				dmc_set_pin_drv_reg(pin_drv_relevent[i].name, DMC_POLAR_PMOS, pin_drv_info[1].drv_pos_target);
				dmc_set_pin_drv_reg(pin_drv_relevent[i].name, DMC_POLAR_NMOS, pin_drv_info[1].drv_neg_target);
				break;
			case DMC_PIN_DQS0_C:
			case DMC_PIN_DQS1_C:
			case DMC_PIN_DQS2_C:
			case DMC_PIN_DQS3_C:
				dmc_set_pin_drv_reg(pin_drv_relevent[i].name, DMC_POLAR_PMOS, pin_drv_info[1].drv_pos_target);
				dmc_set_pin_drv_reg(pin_drv_relevent[i].name, DMC_POLAR_NMOS, pin_drv_info[1].drv_neg_target);
				break;
			case DMC_PIN_CK_C:
				dmc_set_pin_drv_reg(pin_drv_relevent[i].name, DMC_POLAR_PMOS, pin_drv_info[3].drv_pos_target);
				dmc_set_pin_drv_reg(pin_drv_relevent[i].name, DMC_POLAR_NMOS, pin_drv_info[3].drv_neg_target);
				break;
			case DMC_PIN_CS1:
			case DMC_PIN_CKE0:
				dmc_set_pin_drv_reg(pin_drv_relevent[i].name, DMC_POLAR_PMOS, pin_drv_info[4].drv_pos_target);
				dmc_set_pin_drv_reg(pin_drv_relevent[i].name, DMC_POLAR_NMOS, pin_drv_info[4].drv_neg_target);
				break;
			default:
				break;
		}
		
	}
}

static void close_pin_drv_calibration(void)
{
	REG32(REG_DDR_ZQ_CAL) |= 1<<16;
}

int dmc_set_pin_drv(void)
{
	u32 val;
	int factor;
	int pin_drv_cal_pos = 0, pin_drv_cal_neg = 0;
	int i;
	
	for (i=0; i<sizeof(pin_drv_info)/sizeof(DMC_PIN_DRV_INFO); i++)
	{		
		if (-1 == (pin_drv_cal_neg = dmc_zq_cal(DMC_POLAR_NMOS, pin_drv_info[i].drv_neg_target)))
		{
			return -1;
		}
		if (-1 == (pin_drv_cal_pos = dmc_zq_cal(DMC_POLAR_PMOS, pin_drv_info[i].drv_pos_target)))
		{
			return -1;
		}
		pin_drv_info[i].drv_neg_target = pin_drv_cal_neg;
		pin_drv_info[i].drv_pos_target = pin_drv_cal_pos;

		if (pin_drv_info[i].name == DMC_PIN_DQS0_T)
		{
			//dmc_set_pin_drv_reg(pin_drv_info[i].name, DMC_POLAR_PMOS, pin_drv_cal_pos+2);
			dmc_set_pin_drv_reg(pin_drv_info[i].name, DMC_POLAR_PMOS, pin_drv_cal_pos);
			dmc_set_pin_drv_reg(pin_drv_info[i].name, DMC_POLAR_NMOS, pin_drv_cal_neg);
		}
		else
		{
			dmc_set_pin_drv_reg(pin_drv_info[i].name, DMC_POLAR_PMOS, pin_drv_cal_pos);
			dmc_set_pin_drv_reg(pin_drv_info[i].name, DMC_POLAR_NMOS, pin_drv_cal_neg);
		}
	}
	close_pin_drv_calibration();
	set_revelent_pin_drv();
	return 0;	
	
}

static int dqs_internal_pull_cfg(void)
{
	u32 regval;
	int i;

	for (i=0; i<sizeof(pin_pull_info)/sizeof(DMC_PIN_PULL_INFO); i++)
	{
		regval = REG32(pin_pull_info[i].drv_cfg_reg);
		switch(pin_pull_info[i].resis_val)
		{
			case PULL_RESIS_660_OHM:
				regval = u32_bits_set(regval, 6, 2, 1);
				break;
			case PULL_RESIS_1000_OHM:
				regval = u32_bits_set(regval, 6, 2, 2);
				break;
			case PULL_RESIS_3000_OHM:
				regval = u32_bits_set(regval, 6, 2, 3);
				break;
			case PULL_RESIS_INFINITE_OHM:
				regval = u32_bits_set(regval, 6, 2, 0);
				break;
			default:
				return -1;
		}		
		REG32(pin_pull_info[i].drv_cfg_reg) = regval;		
	}
	return 0;
}

static  void deep_sleep_dmc_pin_cfg(void)
{
	u32 *pReg = (u32 *)0x402a0244;
	u32 regval;
	int i;

	for (i=0x244; i<=0x334; i+=4)
	{
		regval = REG32(pReg);
		regval = u32_bits_set(regval, 13, 4, 4);
		REG32(pReg) = regval;
		pReg++;		
	}
}

#if 0
static void dump_dmc_pin_reg_info(void)
{
	int i;

	for (i=0; i<sizeof(pin_drv_info)/sizeof(DMC_PIN_DRV_INFO); i++)
	{
		
	}
}
#endif

static void dmc_deep_sleep_ioe_cfg(void)
{
	u32 val;
	/*set cke slp_oe = 1 slp_ie = 0, other pins are using default value*/
	val = REG32(REG_DRV_PIN_CKE0);
	val = u32_bits_set(val, 0, 2, 1);
	REG32(REG_DRV_PIN_CKE0) = val;
}

int dmc_pin_init(void)
{
	pin_reg_enable();
	if (0 != dqs_internal_pull_cfg())
	{
		return -1;
	}
	dmc_deep_sleep_ioe_cfg();	
#if 1
	if (0 != dmc_set_pin_drv())
	{
		return -1;
	}
#endif
	deep_sleep_dmc_pin_cfg();
	return 0;
}

