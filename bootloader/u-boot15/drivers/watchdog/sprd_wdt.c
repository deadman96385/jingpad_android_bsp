#include <common.h>
#include <asm/io.h>
#include "sprd_wdt.h"
#include <asm/arch/common.h>
/*****************************************************************************/
//  Description:    This function config the watch dog module.
//  Dependency:     No
//  Author:         Jie.Dai
//  Note:
/*****************************************************************************/
int wdt_config (wdt_config_t *cfg)
{
    ///WDG_TRACE("Watch Dog Trace: Watch Dog Value 0x%8.8x", CHIP_REG_GET(WDG_VALUE));
    ANA_REG_SET (WDG_LOCK, WDG_UNLOCK_KEY);

    switch (cfg->mode) {
        case WDG_TIMEOUT_MODE_RESET:
            ANA_REG_AND (WDG_CTRL, (~WDG_INT_EN_BIT));
            break;

        case WDG_TIMEOUT_MODE_INT:
            ANA_REG_OR (WDG_CTRL, WDG_INT_EN_BIT);
            break;

        default:
            break;  //No need to change
    }

    if (WDG_TIMER_STATE_STOP != cfg->state) {
        wdt_load_value (cfg->val);
    }

    switch (cfg->state) {
        case WDG_TIMER_STATE_STOP:
            ANA_REG_AND (WDG_CTRL, (~WDG_CNT_EN_BIT));
            break;

        case WDG_TIMER_STATE_START:
            ANA_REG_OR (WDG_CTRL, WDG_CNT_EN_BIT | WDG_RST_EN_BIT);
            break;

        default:
            break;  //No need to change
    }

    sprd_dbg ("Watch Dog Trace: Watch Dog Control 0x%8.8x", ANA_REG_GET (WDG_CTRL));

    ANA_REG_SET (WDG_LOCK, (~WDG_UNLOCK_KEY));
    return 0;
}


void start_watchdog(uint32_t init_time_ms)
{
    wdt_config_t config;
    //clk on
	ANA_REG_OR (ANA_REG_GLB_ARM_MODULE_EN, BIT_ANA_WDG_EN); //WDG enable
	ANA_REG_OR (ANA_REG_GLB_RTC_CLK_EN,    BIT_RTC_WDG_EN); //WDG Rtc enable

    sprd_dbg ("Watch Dog Trace: WDG_ResetMCU");
    config.state    = WDG_TIMER_STATE_START ;
    config.mode     = WDG_TIMEOUT_MODE_RESET;
    config.val      = 0x50;

    wdt_config (&config);
}

void stop_watchdog(void)
{
    wdt_config_t config;

    sprd_dbg ("Watch Dog Trace: WDG_TimerStop");
    wdt_int_clr();

    config.state    = WDG_TIMER_STATE_STOP  ;
    config.mode     = WDG_TIMEOUT_MODE_RESET;
    config.val      = WDG_MAX_COUNT;

    wdt_config (&config);
}

void init_watchdog(void)
{
    wdt_config_t config;

    sprd_dbg ("Watch Dog Trace: WDG_TimerInit");

    config.state    = WDG_TIMER_STATE_START ;
    config.mode     = WDG_TIMEOUT_MODE_RESET;
    config.val      = WDG_INIT_COUNT;

    wdt_config (&config);
}

void wdt_reset_MCU(void)
{
    wdt_config_t config;

    sprd_dbg ("Watch Dog Trace: wdt_reset_MCU");

    config.state    = WDG_TIMER_STATE_START ;
    config.mode     = WDG_TIMEOUT_MODE_RESET;
    config.val      = 0x50;

    wdt_config (&config);
}

void feed_watchdog(void)
{
}

void load_watchdog(uint32_t time_ms)
{
    wdt_config_t config;

    sprd_dbg ("Watch Dog Trace: WDG_TimerLoad %d", time_ms);

    config.state    = WDG_TIMER_STATE_KEEP  ;
    config.mode     = WDG_TIMEOUT_MODE_KEEP ;
    config.val      = (time_ms * 1000) / 30;

    wdt_config (&config);
}

void hw_watchdog_reset(void)
{

}

int hw_watchdog_rst_pending(void)
{
	u32 ret = 0;
	u32 val = 0;
    //clk on
	ANA_REG_OR (ANA_REG_GLB_ARM_MODULE_EN, BIT_ANA_WDG_EN); //WDG enable
	ANA_REG_OR (ANA_REG_GLB_RTC_CLK_EN,    BIT_RTC_WDG_EN); //WDG Rtc enable

	val = wdt_rst_raw_int();
	printf("hw watchdog int raw status 0x%x\n", val);
	ret = val & WDG_INT_RST_BIT;
	wdt_int_clr();
	return ret;	
}

int fatal_dump_enabled(void)
{
	return readl(0x1ffc);
}

