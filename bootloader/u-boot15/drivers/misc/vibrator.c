#include <config.h>
#include <asm/io.h>
#include <linux/types.h>
#include "adi_hal_internal.h"
#include <asm/arch/sprd_reg.h>

#define ANA_VIBRATOR_CTRL0_U      (ANA_REG_GLB_VIBR_CTRL0)

#define CUR_DRV_CAL_SEL_U	(0x0 << 12)
#ifdef CONFIG_ADIE_SC2730
	#define SLP_LDOVIBR_PD_EN_U		BIT_SLP_LDO_VDDVIB_PD_EN
	#define LDO_VIBR_PD_U			BIT_LDO_VDDVIB_PD
#else
	#define SLP_LDOVIBR_PD_EN_U	(0x1 << 9)
	#define LDO_VIBR_PD_U		(0x1 << 8)
#endif
#define LDO_VIBR_V_U		(0xB4)

#ifdef CONFIG_NONE_VIBRATOR

void set_vibrator(int on) {}
void vibrator_hw_init(void) {}

#else

void set_vibrator(int on)
{
	if (on){
		ANA_REG_AND(ANA_VIBRATOR_CTRL0_U, ~LDO_VIBR_PD_U);
		ANA_REG_AND(ANA_VIBRATOR_CTRL0_U, ~SLP_LDOVIBR_PD_EN_U);
		}
	else{
			ANA_REG_MSK_OR(ANA_VIBRATOR_CTRL0_U, LDO_VIBR_PD_U, LDO_VIBR_PD_U);
			ANA_REG_MSK_OR(ANA_VIBRATOR_CTRL0_U, SLP_LDOVIBR_PD_EN_U, SLP_LDOVIBR_PD_EN_U);
		}
}

void vibrator_hw_init(void)
{
#if defined(CONFIG_ADIE_SC2721) || defined(CONFIG_ADIE_SC2720) || defined(CONFIG_ADIE_SC2730)
	//SC2721 TODO
#else
	ANA_REG_OR(ANA_REG_GLB_RTC_CLK_EN, BIT_RTC_VIBR_EN);
#endif

#if defined(CONFIG_ADIE_SC2730)
	ANA_REG_MSK_OR(ANA_VIBRATOR_CTRL0_U,LDO_VIBR_V_U,LDO_VIBR_V_U);
#else
	ANA_REG_MSK_OR(ANA_VIBRATOR_CTRL0_U,CUR_DRV_CAL_SEL_U,CUR_DRV_CAL_SEL_U);
	ANA_REG_MSK_OR(ANA_VIBRATOR_CTRL0_U,LDO_VIBR_V_U,LDO_VIBR_V_U);
#endif
}

#endif
