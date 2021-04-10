#include <asm/arch/sprd_reg.h>

#if defined(CONFIG_SOC_IWHALE2)
#define AP_AHB_CE_EFS_EB_BIT                                   BIT(26)
#define AP_AHB_CE1_EB_BIT                                      BIT(25)
#define AP_AHB_CE0_EB_BIT                                      BIT(24)
#endif

void disable_ahb_ce_eb(void)
{
#if defined(CONFIG_SOC_IWHALE2)
	(*(volatile unsigned int *)REG_AP_AHB_AHB_EB) &= (unsigned int)(~AP_AHB_CE1_EB_BIT);
#endif

#if defined(CONFIG_ARCH_SCX35L2)
	(*(volatile unsigned int *)REG_AP_AHB_AHB_EB) &= (unsigned int)(~BIT_AP_AHB_CE_SEC_EB);
#endif

#if defined(CONFIG_SOC_PIKE2) || defined(CONFIG_SOC_SHARKLE) || defined(CONFIG_SOC_SHARKL3) || defined(CONFIG_SOC_SHARKL5) || defined(CONFIG_SOC_ROC1)||defined(CONFIG_SOC_SHARKL5PRO)
	sprd_ce_init();
	sprd_ce_close();
#endif
}

void disable_ahb_ce_efs_eb(void)
{
#if defined(CONFIG_SOC_IWHALE2)
	(*(volatile unsigned int *)REG_AP_AHB_AHB_EB) &= (unsigned int)(~AP_AHB_CE_EFS_EB_BIT);
#endif

#if defined(CONFIG_ARCH_SCX35L2)
	(*(volatile unsigned int *)REG_AP_AHB_AHB_EB) &= (unsigned int)(~BIT_AP_AHB_CE_EFUSE_EB);
#endif
}
