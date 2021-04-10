#include <adi.h>
#include <asm/arch/sprd_chipram_env.h>
#include <asm/arch/sprd_reg.h>
#include <common.h>

/**---------------------------------------------------------------------------*
**                               Macro Define                                **
**---------------------------------------------------------------------------*/
/*regs*/
#define WDG_BASE            (ANA_WDG_BASE)
#define WDG_LOAD_LOW        (WDG_BASE + 0x00)
#define WDG_LOAD_HIGH       (WDG_BASE + 0x04)
#define WDG_CTRL            (WDG_BASE + 0x08)
#define WDG_INT_CLR         (WDG_BASE + 0x0C)
#define WDG_INT_RAW         (WDG_BASE + 0x10)
#define WDG_INT_MSK         (WDG_BASE + 0x14)
#define WDG_CNT_LOW         (WDG_BASE + 0x18)
#define WDG_CNT_HIGH        (WDG_BASE + 0x1C)
#define WDG_LOCK            (WDG_BASE + 0x20)
#define WDG_CNT_RD_LOW      (WDG_BASE + 0x24)
#define WDG_CNT_RD_HIGH     (WDG_BASE + 0x28)
#define WDG_CNT_IRQV_LOW    (WDG_BASE + 0x2C)
#define WDG_CNT_IRQV_HIGH   (WDG_BASE + 0x30)

#define WDG_INT_EN_BIT          BIT_0
#define WDG_CNT_EN_BIT          BIT_1
#define WDG_RST_EN_BIT          BIT_3

#define WDG_INT_RST_BIT           BIT_3
#define WDG_INT_CLEAR_BIT       BIT_0

#define WDG_LD_BUSY_BIT         BIT_4

#define WDG_UNLOCK_KEY          0xE551

/*v*/
#define		WDG_RESULT_OK       (u32)(0x00000000)
#define		WDG_RESULT_ERR      (u32)(0xFFFFFFFF)
#define		ANA_WDG_LOAD_TIMEOUT_NUM    (0xfffff)
#define		ANA_WDG_CLR_INT_TIMEOUT_NUM (10000)
#define		WDG_MAX_COUNT           (0xFFFFFFFF)
#define		WDG_INIT_COUNT          (0x0009FFFF) //uint : 1/32768s


typedef enum
{
    WDG_TIMER_STATE_STOP    = 0,    //Stop Watch Dog Timer
    WDG_TIMER_STATE_START,          //Start Watch Dog Timer
    WDG_TIMER_STATE_KEEP            //Don't change Watch Dog Timer State
} wdt_state_t;	//	WDG_TIMER_STATE;

typedef enum
{
    WDG_TIMEOUT_MODE_RESET = 0,     //Set Watch Dog to Reset Mode
    WDG_TIMEOUT_MODE_INT,           //Set Watch Dog to Interrupt Mode
    WDG_TIMEOUT_MODE_KEEP           //Don't change Watch Dog Mode
} wdt_mode_t;		//WDG_TIMEOUT_MODE;

typedef struct
{
    wdt_state_t state;
    wdt_mode_t mode;
    u32  val;                    //Set the Timer start val
} wdt_config_t;	//WDG_CONFIG_T;

/**----------------------------------------------------------------------------*
**                           Function Prototype                               **
**----------------------------------------------------------------------------*/
static inline void wdt_load_value(u32 value)
{
	u32 cnt = 0;
	while((ANA_REG_GET(WDG_INT_RAW) & WDG_LD_BUSY_BIT) && ( cnt < ANA_WDG_LOAD_TIMEOUT_NUM ))
		cnt++;
	ANA_REG_SET( WDG_LOAD_HIGH, (u16)(((value) >> 16 ) & 0xffff));
	ANA_REG_SET( WDG_LOAD_LOW , (u16)((value)  & 0xffff) );
}

static inline void clr_wdt_int(u32 msk)
{
    u32 cnt =  0;
    ANA_REG_SET(WDG_INT_CLR, (msk));
    while((ANA_REG_GET(WDG_INT_RAW) & (msk))&&(cnt < ANA_WDG_CLR_INT_TIMEOUT_NUM))
	cnt++;
}
static inline void wdt_int_clr(void)
{
    ANA_REG_SET (WDG_LOCK, WDG_UNLOCK_KEY);
    clr_wdt_int (WDG_INT_CLEAR_BIT | WDG_INT_RST_BIT);
    ANA_REG_SET (WDG_LOCK, (~WDG_UNLOCK_KEY));
}

static inline u32 wdt_rst_raw_int(void)
{
	return ANA_REG_GET(WDG_INT_RAW);
}

int wdt_config(wdt_config_t *cfg)
{
	ANA_REG_SET (WDG_LOCK, WDG_UNLOCK_KEY);

	switch (cfg->mode) {
	    case WDG_TIMEOUT_MODE_RESET:
	        ANA_REG_AND (WDG_CTRL, (~WDG_INT_EN_BIT));
	        break;

	    case WDG_TIMEOUT_MODE_INT:
	        ANA_REG_OR (WDG_CTRL, WDG_INT_EN_BIT);
	        break;

	/*
	 * No need to change
	 */
	    default:
	        break;
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

	/*
	 * No need to change
	 */
	default:
	        break;
	}

	ANA_REG_SET (WDG_LOCK, (~WDG_UNLOCK_KEY));
	return 0;
}


void start_watchdog(uint32_t init_time_ms)
{
	wdt_config_t config;
	/*
	 *  clk on
	 */
	ANA_REG_OR (ANA_REG_GLB_ARM_MODULE_EN, BIT_ANA_WDG_EN); //WDG enable
	ANA_REG_OR (ANA_REG_GLB_RTC_CLK_EN,    BIT_RTC_WDG_EN); //WDG Rtc enable

	config.state    = WDG_TIMER_STATE_START ;
	config.mode     = WDG_TIMEOUT_MODE_RESET;
	config.val      = 0x50;

	wdt_config(&config);
}

void stop_watchdog(void)
{
	wdt_config_t config;

	wdt_int_clr();

	config.state    = WDG_TIMER_STATE_STOP  ;
	config.mode     = WDG_TIMEOUT_MODE_RESET;
	config.val      = WDG_MAX_COUNT;

	wdt_config(&config);
}

void init_watchdog(void)
{
	wdt_config_t config;

	config.state    = WDG_TIMER_STATE_START ;
	config.mode     = WDG_TIMEOUT_MODE_RESET;
	config.val      = WDG_INIT_COUNT;

	wdt_config(&config);
}

void system_reboot(int cmd)
{
	start_watchdog(5);
	while (1) ;
}

void load_watchdog(uint32_t time_ms)
{
	wdt_config_t config;

	config.state    = WDG_TIMER_STATE_KEEP  ;
	config.mode     = WDG_TIMEOUT_MODE_KEEP ;
	config.val      = (time_ms * 1000) / 30;

	wdt_config(&config);
}

int hw_watchdog_rst_pending(void)
{
	u32 ret = 0;
	u32 val = 0;
	/*
	 *  clk on
	 */
	ANA_REG_OR (ANA_REG_GLB_ARM_MODULE_EN, BIT_ANA_WDG_EN); //WDG enable
	ANA_REG_OR (ANA_REG_GLB_RTC_CLK_EN,    BIT_RTC_WDG_EN); //WDG Rtc enable

	val = wdt_rst_raw_int();
	ret = val & WDG_INT_RST_BIT;
	wdt_int_clr();
	return ret;
}
