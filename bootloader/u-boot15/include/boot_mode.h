#ifndef _BOOT_MODE_H_
#define _BOOT_MODE_H_
#include <common.h>

#define BACKLIGHT_ON 25
#define BACKLIGHT_OFF 0
#define LCD_ON 1
#define LCD_OFF 0

typedef enum {
	CMD_UNDEFINED_MODE=0,
	CMD_POWER_DOWN_DEVICE,
	CMD_NORMAL_MODE,
	CMD_RECOVERY_MODE,
	CMD_FASTBOOT_MODE,
	CMD_ALARM_MODE,
	CMD_CHARGE_MODE,
	CMD_ENGTEST_MODE,
	CMD_WATCHDOG_REBOOT,
	CMD_AP_WATCHDOG_REBOOT,
	CMD_SPECIAL_MODE,
	CMD_UNKNOW_REBOOT_MODE,
	CMD_PANIC_REBOOT,
	CMD_VMM_PANIC_MODE,   //0xd
	CMD_TOS_PANIC_MODE,
	CMD_EXT_RSTN_REBOOT_MODE,
	CMD_CALIBRATION_MODE,
	CMD_FACTORYTEST_MODE,
	CMD_AUTODLOADER_REBOOT,
	CMD_AUTOTEST_MODE,
	CMD_IQ_REBOOT_MODE,
	CMD_SLEEP_MODE,
	CMD_SPRDISK_MODE,
	CMD_APKMMI_MODE,
	CMD_UPT_MODE,

	/*this is not a mode name ,beyond CMD_MAX_MODE means overflow*/
	CMD_MAX_MODE
}boot_mode_enum_type;

typedef enum {
	CMD_SET_FIRST_NORMAL_BOOT_MODE = 0,

	CMD_SET_FIRST_GSM_CLA_MODE,
	CMD_SET_FIRST_GSM_FINAL_TEST_MODE,

	CMD_SET_FIRST_WCDMA_CLA_MODE,
	CMD_SET_FIRST_WCDMA_FINAL_TEST_MODE,

	CMD_SET_FIRST_TDSCDMA_CLA_MODE,
	CMD_SET_FIRST_TDSCDMA_FINAL_TEST_MODE,

	CMD_SET_FIRST_LTETDD_CLA_MODE,
	CMD_SET_FIRST_LTETDD_FINAL_TEST_MODE,

	CMD_SET_FIRST_LTEFDD_CLA_MODE,
	CMD_SET_FIRST_LTEFDD_FINAL_TEST_MODE,

	CMD_SET_FIRST_NR5GSUB6G_CLA_MODE,
	CMD_SET_FIRST_NR5GSUB6G_FINAL_TEST_MODE,

	CMD_SET_FIRST_NRMMW_CLA_MODE,
	CMD_SET_FIRST_NRMMW_FINAL_TEST_MODE,

	CMD_SET_FIRST_CDMA2K_CLA_MODE,
	CMD_SET_FIRST_CDMA2K_FINAL_TEST_MODE,

	CMD_SET_FIRST_BBAT_MODE,

	CMD_SET_FIRST_NATIVE_MMI_MODE,/* MMI for feature phone */

	CMD_SET_FIRST_APK_MMI_MODE,/* apply for smartphone */

	CMD_SET_FIRST_NBIOT_CAL_MODE,
	CMD_SET_FIRST_NBIOT_FINAL_TEST_MODE,

	CMD_SET_FIRST_UPT_MODE,

	CMD_SET_FIRST_MAX_MODE
}set_first_mode_enum_type;

typedef struct first_boot_mode {
	u32 set_mode;
	u32 boot_mode;
	u32 cail_parameter;
} first_boot_mode_t;

#define SET_FIRST_MODE_MAGIC 0x53464d00
#define SET_FIRST_MODE_OFFSET (9 * 1024 + 32)
#define SET_FIRST_MDOE_LEN 0x4

#define CHECK_BOOTMODE_FUN_NUM 15
typedef boot_mode_enum_type (*CBOOT_FUNC) (void);
typedef void (*CBOOT_MODE_ENTRY) (void);

#define MODE_REGIST( index, fun) \
    do{\
            array[index]  = fun;\
        }while(0)


int get_mode_from_file(void);
int set_recovery_run_fastbootd(void);
int clear_recovery_not_run_fastbootd(void);
int pctool_mode_detect(void);
int is_bat_low(void);
int alarm_flag_check(void);
int cali_file_check(void);
int read_adc_calibration_data(char *buffer,int size);
int pctool_mode_detect_uart(void);
int sprdisk_mode_detect(void);

#ifdef CONFIG_AUTOLOAD_MODE
void autoload_mode(void);
#endif

void normal_mode(void);
void recovery_mode(void);
void charge_mode(void);
void fastboot_mode(void);
void alarm_mode(void);
void engtest_mode(void);
void calibration_mode(void);
void factorytest_mode(void);
void watchdog_mode(void);
void ap_watchdog_mode(void);
void unknow_reboot_mode(void);
void special_mode(void);
void panic_reboot_mode(void);
void autodloader_mode(void);
void iq_mode(void);
void autotest_mode(void);
void sprdisk_mode(void);
void apkmmi_mode(void);
void upt_mode(void);

boot_mode_enum_type get_mode_from_arg(char* mode_name);
boot_mode_enum_type get_mode_from_pctool(void);
boot_mode_enum_type get_mode_from_bat_low(void);
boot_mode_enum_type write_sysdump_before_boot_extend(void);
boot_mode_enum_type get_mode_from_file_extend(void);
boot_mode_enum_type get_mode_from_watchdog(void);
boot_mode_enum_type get_mode_from_alarm_register(void);
boot_mode_enum_type get_mode_from_charger(void);
boot_mode_enum_type get_mode_from_keypad(void);
boot_mode_enum_type get_mode_from_gpio_extend(void);
boot_mode_enum_type get_mode_from_miscdata_boot_flag(void);

void vlx_nand_boot(char * kernel_pname, int backlight_set, int lcd_enable);
#endif
