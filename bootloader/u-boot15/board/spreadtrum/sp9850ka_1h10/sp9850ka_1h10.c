#include <common.h>
#include <asm/io.h>
#include <sprd_regulator.h>
//#include <asm/arch/sprd_reg_ahb.h>
//#include <asm/arch/regs_ahb.h>
#include <asm/arch/common.h>
#include "adi_hal_internal.h"
#include <asm/u-boot.h>
#include <part.h>
//#include <sdhci.h>
#include <sprd_sdhci.h>
#include <asm/arch/mfp.h>
//#include <linux/gpio.h>
//#include <asm/arch/gpio.h>
#include <asm/arch/pinmap.h>
#include "asm/arch/sprd_module_config.h"

#include <boot_mode.h>
#include <chipram_env.h>
#include <asm/arch/sprd_reg.h>
#include <sprd_adc.h>
#include <sprd_battery.h>

DECLARE_GLOBAL_DATA_PTR;

extern void sprd_gpio_init(void);
extern void ADI_init (void);
extern void sprd_pmu_lowpower_init(void);

phys_size_t real_ram_size = 0x40000000;


//extern struct eic_gpio_resource sprd_gpio_resource[];
static void sprd_pmu_init(void)
{
	__raw_writel(__raw_readl(REG_PMU_APB_PD_MM_TOP_CFG)
		& ~(BIT_PD_MM_TOP_FORCE_SHUTDOWN),
		REG_PMU_APB_PD_MM_TOP_CFG);

	while (__raw_readl(REG_PMU_APB_PWR_STATUS0_DBG) & 0xf0000000) {};

	__raw_writel(__raw_readl(REG_PMU_APB_PD_GPU_TOP_CFG)
		& ~(BIT_PD_GPU_TOP_FORCE_SHUTDOWN),
		REG_PMU_APB_PD_GPU_TOP_CFG);

	while (__raw_readl(REG_PMU_APB_PWR_STATUS0_DBG) & 0x0f000000) {};

	__raw_writel(__raw_readl(REG_AON_APB_APB_EB0) | BIT_MM_EB |
		BIT_GPU_EB, REG_AON_APB_APB_EB0);
	__raw_writel(__raw_readl(REG_MM_AHB_RF_AHB_EB) | BIT_CKG_EB,
		REG_MM_AHB_RF_AHB_EB);
#ifndef CONFIG_ARCH_SCX35L2
	__raw_writel(__raw_readl(REG_MM_AHB_RF_GEN_CKG_CFG)
		| BIT_MM_MTX_AXI_CKG_EN | BIT_MM_AXI_CKG_EN,
		REG_MM_AHB_RF_GEN_CKG_CFG);
	__raw_writel(__raw_readl(REG_MM_CLK_MM_AHB_CFG) | 0x3,
		REG_MM_CLK_MM_AHB_CFG);
#endif
}

int board_init()
{
	//gd->bd->bi_arch_number = MACH_TYPE_OPENPHONE;
	/*get env transfer from chipram*/
	setup_chipram_env();
#ifndef CONFIG_FPGA
	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;
	ADI_init();
	misc_init();
	regulator_init();
	pmic_adc_Init();
	pin_init();
	sprd_eic_init();
	sprd_intc_enable();
	sprd_gpio_init();
	sprd_pmu_lowpower_init();
	sprd_pmu_init();
#endif
	return 0;
}

phys_size_t get_real_ram_size(void)
{
        return real_ram_size;
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
	} else if(env->cs_number == 2){
		real_ram_size += env->cs0_size;
		real_ram_size += env->cs1_size;
	}

	//real_ram_size = get_ram_size((volatile void *)sdram_base, real_ram_size);
#else
	real_ram_size = REAL_SDRAM_SIZE;
#endif

        gd->ram_size = PHYS_SDRAM_1_SIZE;

        return 0;
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
	get_mode_from_charger,
	/*5 get mode from keypad*/
	get_mode_from_keypad,
	/*6 get mode from gpio*/
	get_mode_from_gpio_extend,

	/*shutdown device*/
//	get_mode_from_shutdown,

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
	MODE_REGIST(CMD_FACTORYTEST_MODE,factorytest_mode);
	MODE_REGIST(CMD_CALIBRATION_MODE, calibration_mode);
	MODE_REGIST(CMD_EXT_RSTN_REBOOT_MODE, normal_mode);
	MODE_REGIST(CMD_IQ_REBOOT_MODE, iq_mode);
	MODE_REGIST(CMD_ALARM_MODE, alarm_mode);
	MODE_REGIST(CMD_AUTOTEST_MODE, autotest_mode);
	MODE_REGIST(CMD_SPRDISK_MODE, sprdisk_mode);

	return ;
}

static void battery_init(void)
{
	sprdchg_common_cfg();
	sprdchg_fan54015_init();
	sprdchg_2700_init();
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

#endif
	battery_init();
	debugf("CHG init OK!\n");
	board_keypad_init();
	return 0;
}

