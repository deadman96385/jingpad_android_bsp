#ifndef __SPRD_WDT_H__
#define __SPRD_WDT_H__
void start_watchdog(uint32_t init_time_ms);
void stop_watchdog(void);
void system_reboot(int cmd);
#endif	/*__SPRD_WDT_H__*/

