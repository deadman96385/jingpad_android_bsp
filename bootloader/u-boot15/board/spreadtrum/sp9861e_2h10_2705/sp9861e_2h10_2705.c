/*
 * Copyright (C) 2015, Intel Corporation
 *
 * SPDX-License _ Identifier: 	GPL-2.0+
 */

#include <common.h>
#include <asm/arch/sprd_reg.h>
#include <asm/ibmpc.h>
#include <asm/pnp_def.h>
#include <netdev.h>
#include <smsc_lpc47m.h>
#include <malloc.h>
#include <boot_mode.h>
#include <adi_hal_internal.h>
#include <sprd_adc.h>
#include <chipram_env.h>
#include <sprd_battery.h>

#define SERIAL_DEV PNP_DEV(0x2e, 4)

DECLARE_GLOBAL_DATA_PTR;
phys_size_t real_ram_size = 0x80000000;

/*
only for passing compile,fo should fix it. sheng.zhu
*/
int misc_init_r(void)
{
	/*reserver for future use*/
	dvfs_init();
	init_vid_table();
	save_vids();
	change_cpu_freq();
	return 0;
}

void thm_overheate_en(void)
{
	sci_glb_set(REG_AON_APB_THERMAL_OVERHEAT_EN,
					BIT_AON_APB_SP_THM_OVERHEAT0_EN |
					BIT_AON_APB_SP_THM_OVERHEAT1_EN);
}

void misc_init()
{
	sci_glb_set(REG_AON_APB_APB_EB0, BIT_AON_APB_AON_GPU_EB);
	sci_glb_set(REG_AON_APB_APB_EB1, BIT_AON_APB_AON_DISP_EB |
					 BIT_AON_APB_AON_CAM_EB |
					 BIT_AON_APB_AON_VSP_EB);
	pmic_misc_init();
	thm_overheate_en();
}

#ifdef CONFIG_SOC_IWHALE2
#include <asm/arch/chip_id.h>
#endif

void disable_unused_module()
{
#ifndef DEBUG
	sci_glb_clr(REG_AON_APB_APB_EB0, BIT_AON_APB_CA53_DAP_EB);
	sci_glb_clr(REG_AON_APB_CGM_CLK_TOP_REG1, BIT_AON_APB_CGM_CSSYS_EN);
#endif
	sci_glb_clr(REG_AON_APB_CGM_REG1, BIT_AON_APB_CGM_RC100M_FDK_EN |
					BIT_AON_APB_CGM_RC100M_REF_EN |
					BIT_AON_APB_CGM_DPHY1_REF_EN);
	sci_glb_clr(REG_AON_APB_CGM_CLK_TOP_REG1, BIT_AON_APB_CGM_SDIO2_1X_EN |
					BIT_AON_APB_CGM_SDIO2_2X_EN);
}

int board_init(void)
{
	int chip_version = 0;
	chip_version = sprd_get_chip_version();

	setup_chipram_env();
	setup_chipram_ddr_range();
#ifndef CONFIG_FPGA
	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;
	ADI_init();
	/*FPGA forbiden*/
	sprd_timer_init();
	misc_init();
	disable_unused_module();
	pmic_adc_Init();
	/*FPGA forbiden*/
	/*workaround*/
	if (1 == chip_version)
	{
		pin_init();
	}
	else if (0 == chip_version)
	{
		pin_init_a0chip();
	}
	sprd_eic_init();
	sprd_gpio_init();
	regulator_init();
	/*FPGA forbiden*/
	sprd_pmu_lowpower_init();
#endif
	return 0;
}

static void battery_init(void)
{
	sprdchg_common_cfg();
	sprdchg_2705_init();
	sprdbat_init();
}

int board_late_init(void)
{
#if !defined(CONFIG_FPGA)
	boot_mode_t boot_role;
        extern chipram_env_t* get_chipram_env(void);
        chipram_env_t* cr_env = get_chipram_env();
        boot_role = cr_env->mode;

	boot_pwr_check();

#ifdef CONFIG_NAND_BOOT
	//extern int nand_ubi_dev_init(void);
	nand_ubi_dev_init();
	debugf("nand ubi init OK!\n");
#endif
	battery_init();
	debugf("CHG init OK!\n");
	board_keypad_init();
#endif
	return 0;
}

phys_size_t get_real_ram_size(void)
{
        return real_ram_size;
}

CBOOT_FUNC s_boot_func_array[CHECK_BOOTMODE_FUN_NUM] = {
#if !defined(CONFIG_FPGA)
	get_mode_from_bat_low,
	write_sysdump_before_boot_extend,
	/* 2 get mode from file*/
	get_mode_from_file_extend,
	/* 3 get mode from watch dog*/
	get_mode_from_watchdog,
	/* 4 get mode from alarm register*/
	get_mode_from_alarm_register,
	/* 5 get mode from calibration detect*/
	get_mode_from_pctool,
	/* 6 get mode from keypad*/
	get_mode_from_keypad,
	/* 7 get mode from charger*/
	get_mode_from_charger,
	/* 8 get mode from gpio*/
	get_mode_from_gpio_extend,

	/*shutdown device*/
	//get_mode_from_shutdown,
	0
#endif
};

void board_boot_mode_regist(CBOOT_MODE_ENTRY *array)
{
#if !defined(CONFIG_FPGA)
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
	MODE_REGIST(CMD_FACTORYTEST_MODE, factorytest_mode);
	MODE_REGIST(CMD_CALIBRATION_MODE, calibration_mode);
	MODE_REGIST(CMD_EXT_RSTN_REBOOT_MODE, normal_mode);
	MODE_REGIST(CMD_IQ_REBOOT_MODE, iq_mode);
	MODE_REGIST(CMD_ALARM_MODE, alarm_mode);
	MODE_REGIST(CMD_SPRDISK_MODE, sprdisk_mode);
	MODE_REGIST(CMD_AUTOTEST_MODE, autotest_mode);
#endif
	return ;
}
