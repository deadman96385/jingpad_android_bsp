#ifndef _CHECK_REBOOT_H_
#define _CHECK_REBOOT_H_


#define   HWRST_STATUS_POWERON_MASK 	(0xf0)
#define   HWRST_STATUS_RECOVERY 		(0x20)
#define   HWRST_STATUS_FASTBOOT 		(0x30)
#define   HWRST_STATUS_NORMAL 			(0x40)
#define   HWRST_STATUS_ALARM 			(0x50)
#define   HWRST_STATUS_SLEEP 			(0x60)
#define   HWRST_STATUS_SPECIAL			(0x70)
#define   HWRST_STATUS_CALIBRATION		(0x90)
#define   HWRST_STATUS_PANIC			(0x80)
#define   HWRST_STATUS_AUTODLOADER 		(0xa0)
#define   HWRST_STATUS_IQMODE           (0xb0)
#define   HWRST_STATUS_SPRDISK			(0xc0)
#define   HWRST_STATUS_FACTORYTEST		(0xe0)
#define   HWRST_STATUS_NORMAL2			(0xf0)
#define   HWRST_STATUS_NORMAL3			(0xf1)

#define   HWRST_STATUS_SECURITY			(0x0002)

#define   HW_PBINT2_STATUS				(0x8)
#define   HW_VCHG_STATUS				(0x20)
#define   HW_7SRST_STATUS				(0x80)
#define   SW_EXT_RSTN_STATUS			(0x800)
#define   SW_7SRST_STATUS				(0x1000)

#define   HWRST_RTCSTATUS_DOWNLOAD_BOOT	(0x55)
#define   HWRST_RTCSTATUS_DEFAULT		(0xA596)

unsigned check_reboot_mode(void);
int get_mode_from_gpio(void);
void reset_to_normal(unsigned reboot_mode);
void reboot_devices(unsigned reboot_mode);
void power_down_devices(unsigned pd_cmd);
int power_button_pressed(void);
int charger_connected(void);
int alarm_triggered(void);


#endif

