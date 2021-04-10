/*
 * (C) Copyright 2014
 * David Feng <fenghua@phytium.com.cn>
 * Sharma Bhupesh <bhupesh.sharma@freescale.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <asm/arch/sprd_reg.h>
#include <common.h>
#include <malloc.h>
#include <boot_mode.h>
#include <adi_hal_internal.h>
#include <chipram_env.h>
#include <sprd_adc.h>
#include <sprd_led.h>
#include <sprd_battery.h>
#include "otp_helper.h"

#define ADC_CHANNEL_FOR_NV    1

DECLARE_GLOBAL_DATA_PTR;
phys_size_t real_ram_size = 0x40000000;

phys_size_t get_real_ram_size(void)
{
        return real_ram_size;
}

void enable_global_clocks(void)
{
	//TODO
}

static void thm_overheate_en(void)
{
	sci_glb_set(REG_AON_APB_OVERHEAT_CTRL,
				BIT_AON_APB_THM0_OVERHEAT_ALARM_ADIE_EN |
				BIT_AON_APB_THM1_OVERHEAT_ALARM_ADIE_EN |
				BIT_AON_APB_THM2_OVERHEAT_ALARM_ADIE_EN );
}

extern void setup_chipram_env(void);
int board_init(void)
{
	setup_chipram_env();
#ifndef CONFIG_FPGA
	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;
	ADI_init();
	/*FPGA forbiden*/
	misc_init();
	pmic_adc_Init();
	/*FPGA forbiden*/
	pin_init();
	sprd_eic_init();
	sprd_gpio_init();
	sprd_led_init();
	/*FPGA forbiden*/
	regulator_init();
	sprd_pmu_lowpower_init();
	TDPllRefConfig(1);
	enable_global_clocks();
	thm_overheate_en();
#endif
	return 0;
}
int dram_init(void)
{
	/*
	 * Clear spin table so that secondary processors
	 * observe the correct value after waken up from wfe.
	 */
	*(unsigned long *)CPU_RELEASE_ADDR = 0;
	gd->ram_size = PHYS_SDRAM_1_SIZE;
	return 0;
}

#ifdef CONFIG_DUAL_DDR
void dram_init_banksize(void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
	gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
	gd->bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;
}
#endif


int misc_init_r(void)
{
	/*reserver for future use*/
	return 0;
}

int board_late_init(void)
{

 boot_mode_t boot_role;
        extern chipram_env_t* get_chipram_env(void);
        chipram_env_t* cr_env = get_chipram_env();
        boot_role = cr_env->mode;

	boot_pwr_check();
	sprdfgu_init();

#if !defined(CONFIG_FPGA)
#ifdef CONFIG_NAND_BOOT
	//extern int nand_ubi_dev_init(void);
	nand_ubi_dev_init();
	debugf("nand ubi init OK!\n");
#endif
	debugf("CHG init OK!\n");
#endif
	board_keypad_init();
	return 0;
}

static boot_mode_enum_type  get_mode_from_plug_in_charger_to_normal_boot(void)
{
	if (charger_connected()) {
		debugf("get mode from charger\n");
		return CMD_NORMAL_MODE;
	} else {
		return CMD_UNDEFINED_MODE;
		}
}


CBOOT_FUNC s_boot_func_array[CHECK_BOOTMODE_FUN_NUM] = {
	get_mode_from_bat_low,
	write_sysdump_before_boot_extend,
	/* 1 get mode from file*/
	get_mode_from_file_extend,
	/* 2 get mode from watch dog*/
	get_mode_from_watchdog,
	/*3 get mode from alarm register*/
	get_mode_from_alarm_register,
	/*0 get mode from calibration detect*/
	get_mode_from_pctool,
	/*4 get mode from charger*/
	get_mode_from_plug_in_charger_to_normal_boot,
	/*5 get mode from keypad*/
	get_mode_from_keypad,
	/*6 get mode from gpio*/
	get_mode_from_gpio_extend,

	/*shutdown device*/
	//get_mode_from_shutdown,
	0
};



void board_boot_mode_regist(CBOOT_MODE_ENTRY *array)
{
	MODE_REGIST(CMD_NORMAL_MODE, normal_mode);
	MODE_REGIST(CMD_RECOVERY_MODE, recovery_mode);
	MODE_REGIST(CMD_FASTBOOT_MODE, fastboot_mode);
	MODE_REGIST(CMD_WATCHDOG_REBOOT, watchdog_mode);
	MODE_REGIST(CMD_AP_WATCHDOG_REBOOT, ap_watchdog_mode);
	MODE_REGIST(CMD_UNKNOW_REBOOT_MODE, unknow_reboot_mode);
	MODE_REGIST(CMD_PANIC_REBOOT, panic_reboot_mode);
	MODE_REGIST(CMD_AUTODLOADER_REBOOT, autodloader_mode);
	MODE_REGIST(CMD_SPECIAL_MODE, special_mode);
	MODE_REGIST(CMD_CHARGE_MODE, normal_mode);
	MODE_REGIST(CMD_ENGTEST_MODE,engtest_mode);
	MODE_REGIST(CMD_FACTORYTEST_MODE, factorytest_mode);
	MODE_REGIST(CMD_CALIBRATION_MODE, normal_mode);
	MODE_REGIST(CMD_EXT_RSTN_REBOOT_MODE, normal_mode);
	MODE_REGIST(CMD_IQ_REBOOT_MODE, iq_mode);
	MODE_REGIST(CMD_ALARM_MODE, alarm_mode);
	MODE_REGIST(CMD_SPRDISK_MODE, sprdisk_mode);
	MODE_REGIST(CMD_AUTOTEST_MODE, autotest_mode);
	return ;
}

uint32_t sprd_get_chip_version(void)
{
	return 1;
}

static const int adc2deltanv_table[] = {
	-1, /* reserved */
	-1, /* reserved */
	-1, /* reserved */
	-1, /* reserved */
	-1, /* reserved */
	-1, /* reserved */
	-1, /* reserved */
	0 /* hw_ver00.nv */
};

static int get_adc_value_board(int channel)
{
	int adc_value = 0,vol= 0 ,level= 0;

	adc_value = pmic_adc_get_value_by_isen(channel,0,15,2000);
	vol = sprd_chan_small_adc_to_vol(channel, 0 , 0 ,adc_value);
	debugf("The voltage is = %d\n",vol);

	if (vol <= 0 || vol >= 1200) {
		errorf("vol is out of ranger [0~1200]\n");
		return -1;
	}


	if (vol >= 9 && vol <= 31)
		level = 0;
	if (vol >= 180 && vol <= 220)
		level = 1;
	if (vol >= 275 && vol <= 325)
		level = 2;
	if (vol >= 446 && vol <= 514)
		level = 3;
	if (vol >= 560 && vol <= 640)
		level = 4;
	if (vol >= 731 && vol <= 829)
		level = 5;
	if (vol >= 883 && vol <= 997)
		level = 6;
	if (vol >= 1054 && vol <= 1186)
		level = 7;

	debugf("level = %d\n",level);

	if(level < 0 || level > 7) {
		errorf("Adc value of rf band if is wrong, the rfboard.id will be set to -1\n");
		return -1;
	}

	return adc2deltanv_table[level];
}

/* Return rf band info */
int sprd_get_bandinfo(void)
{
	unsigned int adc_val = 0;

	adc_val = get_adc_value_board(ADC_CHANNEL_FOR_NV);
	debugf("rfboard.id = %d\n", adc_val);

	return adc_val;
}
