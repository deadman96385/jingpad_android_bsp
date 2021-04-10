#include "asm/arch/sprd_reg.h"
#include <asm/io.h>
#include <linux/types.h>

int sprd_timer_init(void)
{
	writel(readl(REG_AON_APB_APB_EB0) | BIT_AON_APB_AP_SYST_EB, REG_AON_APB_APB_EB0);
	writel(readl(REG_AON_APB_APB_RTC_EB) | BIT_AON_APB_AP_SYST_RTC_EB, REG_AON_APB_APB_RTC_EB);
	writel(readl(REG_AON_APB_APB_EB0) | BIT_AON_APB_AON_TMR_EB, REG_AON_APB_APB_EB0);
	writel(readl(REG_AON_APB_APB_RTC_EB) | BIT_AON_APB_AON_TMR_RTC_EB, REG_AON_APB_APB_RTC_EB);
	writel(readl(REG_AON_APB_APB_EB0) | BIT_AON_APB_AON_SYST_EB, REG_AON_APB_APB_EB0);
	writel(readl(REG_AON_APB_APB_RTC_EB) | BIT_AON_APB_AON_SYST_RTC_EB, REG_AON_APB_APB_RTC_EB);
	/* enable aon timer2 26M clk source */
	writel(readl(REG_AON_APB_CGM_REG1) | BIT_AON_APB_CGM_SP_TMR_EN, REG_AON_APB_CGM_REG1);

	return 0;
}

/*
 * new add for calibration_detect.c
 */
ulong get_timer_masked(void)
{
	return get_timer(0);
}
