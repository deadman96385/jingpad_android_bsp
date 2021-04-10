/*
 * Copyright (C) 2015, Intel Corporation
 *
 * SPDX-License _ Identifier: 	GPL-2.0+
 */

#include <common.h>
#include <asm/ibmpc.h>
#include <asm/pnp_def.h>
#include <netdev.h>
#include <smsc_lpc47m.h>
#include <malloc.h>
#include <boot_mode.h>
#include <adi_hal_internal.h>
#include <sprd_adc.h>

#define SERIAL_DEV PNP_DEV(0x2e, 4)

DECLARE_GLOBAL_DATA_PTR;
phys_size_t real_ram_size = 0x80000000;

int board_early_init_f(void)
{
//	lpc47m_enable_serial(SERIAL_DEV, UART0_BASE);

	return 0;
}

int board_early_init_r(void)
{
	printf("Board_early_init_r :\n");
	return 0;
}

void setup_pch_gpios(u16 gpiobase, const struct pch_gpio_map *gpio)
{
	return;
}

int board_eth_init(bd_t *bis)
{
//	return pci_eth_init(bis);
}

int board_init(void)
{
	printf("Board_init:\n");
#ifdef CONFIG_SPRD_PLATFORM
	/*get env transfer from chipram*/
	setup_chipram_env();

	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;
	ADI_init();
	/*FPGA forbiden*/
	//misc_init();
	//LDO_Init();
	pmic_adc_Init();
	/*FPGA forbiden*/
//	pin_init();
	sprd_eic_init();
	sprd_gpio_init();
	/*FPGA forbiden*/
	init_ldo_sleep_gr();
	boot_pwr_check();
	return 0;
#else
	return 0;
#endif
}

int misc_init_r(void)
{
#ifdef CONFIG_SPRD_PLATFORM
	dvfs_init();
	init_vid_table();
	boot_pwr_check();
	return 0;
#else
	return 0;
#endif
}

int board_late_init(void)
{
#ifdef CONFIG_SPRD_PLATFORM
	boot_pwr_check();

#if !defined(CONFIG_FPGA)
#ifdef CONFIG_NAND_BOOT
        //extern int nand_ubi_dev_init(void);
        nand_ubi_dev_init();
        debugf("nand ubi init OK!\n");
#endif

	CHG_Init();
	debugf("CHG init OK!\n");
#endif
	board_keypad_init();
	return 0;
#else
	return 0;
#endif
}

phys_size_t get_real_ram_size(void)
{
        return real_ram_size;
}

CBOOT_FUNC s_boot_func_array[CHECK_BOOTMODE_FUN_NUM] = {
#ifdef CONFIG_SPRD_PLATFORM
        //get_mode_from_bat_low,
        write_sysdump_before_boot_extend,
	/* 1 get mode from file*/
	get_mode_from_file_extend,
	/* 2 get mode from watch dog */
	get_mode_from_watchdog,
	/* 3 get mode from alarm register */
	get_mode_from_alarm_register,
	/* 0 get mode from calibration detect */
	get_mode_from_calibration,
	/*4 get mode from charger */
	get_mode_from_charger,
	/*5 get mode from keypad*/
	get_mode_from_keypad,
	0
#else
	0
#endif
};

void board_boot_mode_regist(CBOOT_MODE_ENTRY *array)
{
#ifdef CONFIG_SPRD_PLATFORM
        MODE_REGIST(CMD_NORMAL_MODE, normal_mode);
        MODE_REGIST(CMD_RECOVERY_MODE, recovery_mode);
        MODE_REGIST(CMD_FASTBOOT_MODE, fastboot_mode);
        MODE_REGIST(CMD_WATCHDOG_REBOOT, watchdog_mode);
        MODE_REGIST(CMD_AP_WATCHDOG_REBOOT, ap_watchdog_mode);
        MODE_REGIST(CMD_UNKNOW_REBOOT_MODE, unknow_reboot_mode);
        MODE_REGIST(CMD_PANIC_REBOOT, panic_reboot_mode);
        MODE_REGIST(CMD_AUTODLOADER_REBOOT, autodloader_mode);
        MODE_REGIST(CMD_SPECIAL_MODE, special_mode);
        MODE_REGIST(CMD_CHARGE_MODE, charge_mode);
        MODE_REGIST(CMD_ENGTEST_MODE,engtest_mode);
        MODE_REGIST(CMD_CALIBRATION_MODE, calibration_mode);
        MODE_REGIST(CMD_EXT_RSTN_REBOOT_MODE, normal_mode);
        MODE_REGIST(CMD_IQ_REBOOT_MODE, iq_mode);
        MODE_REGIST(CMD_ALARM_MODE, alarm_mode);

	return;
#else
	return;
#endif
}
