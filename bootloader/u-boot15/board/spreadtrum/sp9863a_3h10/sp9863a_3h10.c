/*
 * (C) Copyright 2014
 * David Feng <fenghua@phytium.com.cn>
 * Sharma Bhupesh <bhupesh.sharma@freescale.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include <common.h>
#include <malloc.h>
#include <boot_mode.h>
#include <adi_hal_internal.h>
#include <chipram_env.h>
#include <sprd_adc.h>
#include <sprd_led.h>
#include <sprd_battery.h>

DECLARE_GLOBAL_DATA_PTR;
phys_size_t real_ram_size = 0x40000000;

phys_size_t get_real_ram_size(void)
{
        return real_ram_size;
}

void enable_global_clocks(void)
{
	__raw_writel(BIT_AON_APB_MM_EB, REG_AON_APB_APB_EB0 + 0x1000);
	__raw_writel(BIT_AON_APB_MM_VSP_EB, REG_AON_APB_APB_EB1 + 0x1000);
	__raw_writel(BIT_AON_APB_CLK_GPU_EB | BIT_AON_APB_CLK_DISP_EB,
			REG_AON_APB_AON_CLK_TOP_CFG + 0x1000);
	while (__raw_readl(REG_PMU_APB_PWR_STATUS0_DBG) & BIT_PMU_APB_PD_MM_TOP_STATE(~0));
}

extern void setup_chipram_env(void);
int board_init(void)
{
	setup_chipram_env();
#ifndef CONFIG_FPGA
	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;
	ADI_init();
	/*FPGA forbiden*/
	pmic_adc_Init();
	/*FPGA forbiden*/
	pin_init();
	regulator_init();
	sprd_gpio_init();
	misc_init();
	sprd_eic_init();
	sprd_led_init();
	/*FPGA forbiden*/
	sprd_pmu_lowpower_init();
	enable_global_clocks();
#endif
	return 0;
}
int dram_init(void)
{
#ifdef CONFIG_DDR_AUTO_DETECT
  ulong sdram_base = CONFIG_SYS_SDRAM_BASE;
  ulong sdram_size = 0;
  chipram_env_t * env = CHIPRAM_ENV_LOCATION;
  if (CHIPRAM_ENV_MAGIC != env->magic) {
    printf("Chipram magic wrong , ddr data may be broken\n");
    return 0;
  }

  real_ram_size = 0;

  if (env->cs_number == 1) {
    real_ram_size += env->cs0_size;
    debugf("dram cs0 size %x\n",env->cs0_size);
  } else if(env->cs_number == 2){
    real_ram_size += env->cs0_size;
    real_ram_size += env->cs1_size;
    debugf("dram cs0 size %x\ndram cs1 size %x\n",env->cs0_size, env->cs1_size);
  }

  //real_ram_size = get_ram_size((volatile void *)sdram_base, real_ram_size);
#else
  real_ram_size = REAL_SDRAM_SIZE;
#endif

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

static void battery_init(void)
{
	sprdchg_common_cfg();
	sprdchg_2703_init();
	sprdbat_init();
}

int board_late_init(void)
{

 boot_mode_t boot_role;
        extern chipram_env_t* get_chipram_env(void);
        chipram_env_t* cr_env = get_chipram_env();
        boot_role = cr_env->mode;

	boot_pwr_check();

#if !defined(CONFIG_FPGA)
#ifdef CONFIG_NAND_BOOT
	//extern int nand_ubi_dev_init(void);
	nand_ubi_dev_init();
	debugf("nand ubi init OK!\n");
#endif
	battery_init();
	debugf("CHG init OK!\n");
#endif
	board_keypad_init();
	return 0;
}


CBOOT_FUNC s_boot_func_array[CHECK_BOOTMODE_FUN_NUM] = {
	get_mode_from_bat_low,
	write_sysdump_before_boot_extend,
	get_mode_from_miscdata_boot_flag,
	/* 1 get mode from file*/
	get_mode_from_file_extend,
	/* 2 get mode from watch dog*/
	get_mode_from_watchdog,
	/*3 get mode from alarm register*/
	get_mode_from_alarm_register,
	/*0 get mode from calibration detect*/
	get_mode_from_pctool,
	/*4 get mode from charger*/
	get_mode_from_charger,
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
	MODE_REGIST(CMD_CHARGE_MODE, charge_mode);
	MODE_REGIST(CMD_ENGTEST_MODE,engtest_mode);
	MODE_REGIST(CMD_FACTORYTEST_MODE, factorytest_mode);
	MODE_REGIST(CMD_CALIBRATION_MODE, calibration_mode);
	MODE_REGIST(CMD_EXT_RSTN_REBOOT_MODE, normal_mode);
	MODE_REGIST(CMD_IQ_REBOOT_MODE, iq_mode);
	MODE_REGIST(CMD_ALARM_MODE, alarm_mode);
	MODE_REGIST(CMD_SPRDISK_MODE, sprdisk_mode);
	MODE_REGIST(CMD_AUTOTEST_MODE, autotest_mode);
	MODE_REGIST(CMD_APKMMI_MODE, apkmmi_mode);
	MODE_REGIST(CMD_UPT_MODE, upt_mode);
	return ;
}

