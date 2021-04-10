#include <common.h>
#include <command.h>
#include <linux/types.h>
//#include <linux/keypad.h>
//#include <linux/key_code.h>
#include <linux/input.h>
#include <boot_mode.h>
//#include <android_bootimg.h>
//#include <asm/arch/gpio.h>
#include <asm/arch/check_reboot.h>
#include <sprd_battery.h>

extern CBOOT_FUNC s_boot_func_array[CHECK_BOOTMODE_FUN_NUM] ;

extern unsigned int check_key_boot(unsigned char key);
extern void write_sysdump_before_boot(int rst_mode);
extern unsigned char board_key_scan(void);
extern void board_boot_mode_regist(CBOOT_MODE_ENTRY *array);

int boot_pwr_check(void)
{
	static int total_cnt = 0;

	if (!power_button_pressed())
		total_cnt ++;
	return total_cnt;
}


boot_mode_enum_type get_mode_from_arg(char* mode_name)
{

	debugf("cboot:get mode from argument:%s\n",mode_name);
	if(!strcmp(mode_name,"normal"))
		return CMD_NORMAL_MODE;

	if(!strcmp(mode_name,"recovery"))
		return CMD_RECOVERY_MODE;

	if(!strcmp(mode_name,"fastboot"))
		return CMD_FASTBOOT_MODE;

	if(!strcmp(mode_name,"charge"))
		return CMD_CHARGE_MODE;

	if(!strcmp(mode_name,"sprdisk"))
		return CMD_SPRDISK_MODE;

	/*just for debug*/
#ifdef CONFIG_SPRD_SYSDUMP
	if(!strcmp(mode_name,"sysdump"))
		write_sysdump_before_boot(CMD_UNKNOW_REBOOT_MODE);
#endif
	return CMD_UNDEFINED_MODE;

}


unsigned reboot_mode_check(void)
{
	  static unsigned rst_mode = 0;
	   static unsigned check_times = 0;
	   if(!check_times)
	  {
		  rst_mode = check_reboot_mode();
		  check_times++;
	  }
	  debugf("reboot_mode_check rst_mode=0x%x\n",rst_mode);
	  return rst_mode;
  }


  // 0 get mode from pc tool
boot_mode_enum_type get_mode_from_pctool(void)
{
	int ret = pctool_mode_detect();
	if (ret < 0)
		return CMD_UNDEFINED_MODE;
	else
		return ret;
}

boot_mode_enum_type get_mode_from_bat_low(void)
{
#ifndef CONFIG_FPGA       //jump loop
	while(is_bat_low()) {
#ifdef CONFIG_TARGET_SP9853I_10C10
	  if(1) {
#else
	  if(charger_connected()) {
#endif
		  debugf("cboot:low battery,charging...\n");
		  sprdbat_show_chglogo();
		  sprdbat_lowbat_chg();
		  mdelay(SPRDBAT_CHG_POLLING_T);
	  }else{
		  debugf("cboot:low battery and shutdown\n");
		  return CMD_POWER_DOWN_DEVICE;
	  }
	}
#endif
	sprdbat_chg_led(0);
	return CMD_UNDEFINED_MODE;
}

#ifndef CONFIG_ZEBU
boot_mode_enum_type write_sysdump_before_boot_extend(void)
{
	unsigned rst_mode = reboot_mode_check();
	debugf("cboot:write_sysdump_before_boot_extend!!!!\n");
#ifdef CONFIG_SPRD_SYSDUMP
	write_sysdump_before_boot(rst_mode);
#endif
	return CMD_UNDEFINED_MODE;
}
#endif

/* get mode from miscdata */
boot_mode_enum_type get_mode_from_miscdata_boot_flag(void)
{
	switch (read_boot_flag()) {
		case CMD_CALIBRATION_MODE:
			debugf("get mode from firstmode field: calibration\n");
			return CMD_CALIBRATION_MODE;
		case CMD_FACTORYTEST_MODE:
			debugf("get mode from firstmode field: factorytest\n");
			return CMD_FACTORYTEST_MODE;
		case CMD_AUTOTEST_MODE:
			debugf("get mode from firstmode field: autotest\n");
			return CMD_AUTOTEST_MODE;
		case CMD_APKMMI_MODE:
			debugf("get mode from firstmode field: apkmmi\n");
			return CMD_APKMMI_MODE;
		case CMD_UPT_MODE:
			debugf("get mode from firstmode field: upt\n");
			return CMD_UPT_MODE;
		default:
			debugf("get mode from firstmode field: no set first mode\n");
			return CMD_UNDEFINED_MODE;
	}

	return CMD_UNDEFINED_MODE;
}

/*1 get mode from file, just for recovery mode now*/
boot_mode_enum_type get_mode_from_file_extend(void)
{
	switch (get_mode_from_file()) {
		case CMD_RECOVERY_MODE:
			debugf("cboot:get mode from file:recovery\n");
			return CMD_RECOVERY_MODE;
		default:
			return CMD_UNDEFINED_MODE;
	}
	return CMD_UNDEFINED_MODE;
}

// 2 get mode from watch dog
boot_mode_enum_type get_mode_from_watchdog(void)
{
	unsigned rst_mode = reboot_mode_check();
	int flag;
	switch (rst_mode) {
		case CMD_RECOVERY_MODE:
		case CMD_FASTBOOT_MODE:
		case CMD_NORMAL_MODE:
		case CMD_WATCHDOG_REBOOT:
		case CMD_AP_WATCHDOG_REBOOT:
		case CMD_UNKNOW_REBOOT_MODE:
		case CMD_PANIC_REBOOT:
		case CMD_AUTODLOADER_REBOOT:
		case CMD_SPECIAL_MODE:
		case CMD_EXT_RSTN_REBOOT_MODE:
		case CMD_IQ_REBOOT_MODE:
		case CMD_SPRDISK_MODE:
		case CMD_FACTORYTEST_MODE:
			return rst_mode;
		case CMD_ALARM_MODE:
			if ((flag = alarm_flag_check())) {
				debugf("get_mode_from_watchdog flag=%d\n", flag);
				if (flag == 1) {
				  return CMD_ALARM_MODE;
				}
				else if (flag == 2) {
				  return CMD_NORMAL_MODE;
				}
			}
		default:
			return CMD_UNDEFINED_MODE;
	}
}

// 3 get mode from alarm register
boot_mode_enum_type  get_mode_from_alarm_register(void)
{
	int flag;

	if (alarm_triggered() && (flag = alarm_flag_check())) {
		debugf("get_mode_from_alarm_register flag=%d\n", flag);
		if (flag == 1) {
			return CMD_ALARM_MODE;
		}
		else if (flag == 2) {
			return CMD_NORMAL_MODE;
		}
	} else {
		return CMD_UNDEFINED_MODE;
	}
}

/* 4 get mode from charger*/
boot_mode_enum_type  get_mode_from_charger(void)
{
	if (charger_connected()) {
		debugf("get mode from charger\n");
		return CMD_CHARGE_MODE;
	} else {
		return CMD_UNDEFINED_MODE;
	}
}

/*5 get mode from keypad*/
boot_mode_enum_type  get_mode_from_keypad(void)
{
	uint32_t key_mode = 0;
	uint32_t key_code = 0;
	volatile int i;
	if (boot_pwr_check() >= PWR_KEY_DETECT_CNT) {
		mdelay(50);
		for (i = 0; i < 10; i++) {
			key_code = board_key_scan();
			if(key_code != KEY_RESERVED)
			  break;
		}
		key_mode = check_key_boot(key_code);
		debugf("cboot:get mode from keypad:0x%x\n",key_code);
		switch(key_mode) {
		  case CMD_FASTBOOT_MODE:
			  return  CMD_FASTBOOT_MODE;
		  case CMD_RECOVERY_MODE:
			  return CMD_RECOVERY_MODE;
		  case CMD_FACTORYTEST_MODE:
			  return CMD_FACTORYTEST_MODE;
		  default:
			  return CMD_NORMAL_MODE;
		}
	}else {
		return CMD_UNDEFINED_MODE;
	}
}

// 6 get mode from gpio
boot_mode_enum_type  get_mode_from_gpio_extend(void)
{
	if (get_mode_from_gpio()) {
		debugf("pbint2 triggered, do normal mode\n");
		return CMD_NORMAL_MODE;
	} else {
		return CMD_UNDEFINED_MODE;
	}
}

int do_cboot(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	volatile int i;
	boot_mode_enum_type bootmode = CMD_UNDEFINED_MODE;
	CBOOT_MODE_ENTRY boot_mode_array[CMD_MAX_MODE] ={0};

	if(argc > 2)
		return CMD_RET_USAGE;
#ifdef CONFIG_AUTOLOAD_MODE
	autoload_mode();
#endif
#if defined CONFIG_AUTOBOOT
	if (reboot_mode_check() == CMD_AUTODLOADER_REBOOT)
	{
		autodloader_mode();
	}
	else    {
	#if defined CONFIG_X86
		write_sysdump_before_boot_extend();//if autoboot kernel is crash and reboot,the uboot go to sysdump in x86;
	#endif
		normal_mode();
	}
#endif

#if defined CONFIG_ZEBU || defined CONFIG_FPGA
	normal_mode();
#endif
	boot_pwr_check();
	if (2 == argc) {
		/*argument has the highest priority to determine the boot mode*/
		bootmode = get_mode_from_arg(argv[1]);
	} else {
		for (i = 0;  i < CHECK_BOOTMODE_FUN_NUM; i++) {
			if (0 == s_boot_func_array[i]) {
				bootmode = CMD_POWER_DOWN_DEVICE;
				break;
			}
			bootmode = s_boot_func_array[i]();
			if (CMD_UNDEFINED_MODE == bootmode) {

				continue;
			} else {
				debugf("get boot mode in boot func array[%d]\n",i);
				break;
			}
		}
	}

	board_boot_mode_regist(boot_mode_array);

	printf("enter boot mode %d\n", bootmode);

	if ((bootmode > CMD_POWER_DOWN_DEVICE) &&(bootmode < CMD_MAX_MODE)&& (0 != boot_mode_array[bootmode])) {
		write_log();

		boot_mode_array[bootmode]();
	} else {
#ifdef CONFIG_FPGA
		/*FPGA has no power button ,if hasn't detect any mode ,use normal mode*/
		debugf("FPGA use normal mode instead of power down.\n");
		normal_mode();
#else
		debugf("power down device\n");
		write_log();
		power_down_devices(0);
#endif
		while(1);
	}

	  return 0;
}


U_BOOT_CMD(
		  cboot, CONFIG_SYS_MAXARGS, 1, do_cboot,
		  "choose boot mode",
		  "mode: \nrecovery, fastboot, dloader, charge, normal, vlx, caliberation.\n"
		  "cboot could enter a mode specified by the mode descriptor.\n"
		  "it also could enter a proper mode automatically depending on "
		  "the environment\n"
		);

