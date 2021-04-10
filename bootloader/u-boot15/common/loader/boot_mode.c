#include <common.h>
#include "loader_common.h"
#include <libfdt.h>
#include "dev_tree.h"
#include "secureboot/sec_common.h"

extern unsigned int g_charger_mode;
extern int do_fastboot(void);
extern void lcd_printf(const char *fmt, ...);
void lcd_enable(void);
extern void fastboot_lcd_printf(void);

void __attribute__((weak)) fastboot_lcd_printf(void)
{
	lcd_printf("   fastboot mode");
	return;
}

#ifdef CONFIG_AUTOLOAD_MODE

void autoload_mode(void)
{
	struct boot_img_hdr *boot_hdr;
	ulong kernel_size = 0;
	uchar * ramdisk_addr = 0;
	ulong ramdisk_size = 0;
	uchar * dt_addr = 0;
	ulong dt_size = 0;
	struct dt_table *table = NULL;
	uint64_t size = 0;
	struct dt_entry *dt_entry_ptr = NULL;
	uint64_t offset = 0;
	debugf("autoload_mode\n");
	boot_hdr = malloc(512*4);
	memcpy((void *)boot_hdr,(const void *)BOOTIMG_ADR,512*4);
	if (!memcmp(boot_hdr->magic, BOOT_MAGIC, BOOT_MAGIC_SIZE)) {
		kernel_size = (boot_hdr->kernel_size + (KERNL_PAGE_SIZE-1)) & (~(KERNL_PAGE_SIZE -1));
		ramdisk_addr =  (void *)BOOTIMG_ADR+512*4+kernel_size;
		ramdisk_size = (boot_hdr->ramdisk_size + (KERNL_PAGE_SIZE-1)) & (~(KERNL_PAGE_SIZE -1));
		dt_addr = (void *)BOOTIMG_ADR+512*4+kernel_size+ramdisk_size;
		dt_size = (boot_hdr->dt_size + (KERNL_PAGE_SIZE-1)) & (~(KERNL_PAGE_SIZE -1));
		memcpy((void *)KERNEL_ADR, (const void *)BOOTIMG_ADR+512*4, kernel_size);
		memcpy((void *)RAMDISK_ADR, ramdisk_addr, ramdisk_size);

		table = (struct dt_table*)dt_addr;
		/* Validate the device tree table header */
		if((table->magic != DEV_TREE_MAGIC) || (table->version != DEV_TREE_VERSION)) {
			errorf("Cannot validate Device Tree Table \n");
		}

		/* Calculate the offset of device tree within device tree table */
		dt_entry_ptr = dev_tree_get_entry_ptr(table);
		if(NULL == dt_entry_ptr) {
			errorf("Getting device tree address failed\n");
		}

		memcpy((void *)DT_ADR, dt_addr+dt_entry_ptr->offset, dt_entry_ptr->size);

		debugf("\nthe kernel is loading in the address:0x%x,size is 0x%lx\n", KERNEL_ADR, kernel_size);
		debugf("\nthe ramdisk is loading in the address:0x%x,size is 0x%lx\n", RAMDISK_ADR, ramdisk_size);
		debugf("\nthe dtb is loading in the address:0x%x,size is 0x%lx\n", DT_ADR, dt_entry_ptr->size);
	}
	fdt_initrd_norsvmem(DT_ADR, RAMDISK_ADR, RAMDISK_ADR + boot_hdr->ramdisk_size, 1);
	free(boot_hdr);

	vlx_entry(DT_ADR);

}

#endif

void normal_mode(void)
{
#ifndef CONFIG_ZEBU
	vibrator_hw_init();

	set_vibrator(1);
	vlx_nand_boot(BOOT_PART, BACKLIGHT_ON, LCD_ON);
#else
	vlx_nand_boot_zebu(BOOT_PART, BACKLIGHT_ON, LCD_ON);
#endif
	return;
}

void calibration_mode(void)
{
	debugf("calibration_mode\n");

	setenv("bootmode", "cali");
#ifdef CONFIG_CALIMODE_USE_BOOTIMG
	vlx_nand_boot(BOOT_PART, BACKLIGHT_OFF, LCD_OFF);
#else
	vlx_nand_boot(RECOVERY_PART, BACKLIGHT_OFF, LCD_OFF);
#endif
	return;
}

void autotest_mode(void)
{
	debugf("autotest_mode\n");

	setenv("bootmode", "autotest");
	vlx_nand_boot(BOOT_PART, BACKLIGHT_OFF, LCD_ON);
	return;
}

void recovery_mode(void)
{
    debugf("recovery_mode\n");
    setenv("bootmode", "recovery");
    vlx_nand_boot(RECOVERY_PART, BACKLIGHT_ON, LCD_ON);
    return;

}


void special_mode(void)
{
	debugf("special_mode\n");

	setenv("bootmode", "special");
	vlx_nand_boot(BOOT_PART, BACKLIGHT_OFF, LCD_ON);
	return;
}

void iq_mode(void)
{
	debugf("iq_mode\n");
	setenv("bootmode", "iq");
	vlx_nand_boot(BOOT_PART, BACKLIGHT_OFF, LCD_ON);
	return;

}

void watchdog_mode(void)
{
	debugf("watchdog_mode\n");
	setenv("bootmode", "wdgreboot");
	vlx_nand_boot(BOOT_PART, BACKLIGHT_OFF, LCD_ON);
	return;

}

void ap_watchdog_mode(void)
{
	debugf("ap_watchdog_mode\n");
	setenv("bootmode", "apwdgreboot");
	vlx_nand_boot(BOOT_PART, BACKLIGHT_OFF, LCD_ON);
	return;

}

void unknow_reboot_mode(void)
{
	debugf("unknow_reboot_mode\n");
	setenv("bootmode", "unknowreboot");
	vlx_nand_boot(BOOT_PART, BACKLIGHT_OFF, LCD_ON);
	return;

}

void panic_reboot_mode(void)
{
	debugf("enter\n");
	setenv("bootmode", "panic");
	vlx_nand_boot(BOOT_PART, BACKLIGHT_OFF, LCD_ON);
	return;

}

void fastboot_mode(void)
{
	debugf("enter\n");
#ifdef CONFIG_SPLASH_SCREEN
extern int drv_lcd_init (void);
	debug("[LCD] Drawing the logo...\n");
	drv_lcd_init();
	lcd_splash(LOGO_PART);
	lcd_enable();

	vibrator_hw_init();
	set_vibrator(1);

	extern void set_backlight(uint32_t value);
	fastboot_lcd_printf();
	set_backlight(BACKLIGHT_ON);
	mdelay(400);
	set_vibrator(0);
#endif
	//MMU_DisableIDCM();
#if (defined CONFIG_X86) && (defined CONFIG_MOBILEVISOR) && (defined CONFIG_SPRD_SOC_SP9853I)
	tos_start_notify();
#endif
#ifdef CONFIG_SECBOOT
	if (get_lock_status() == VBOOT_STATUS_UNLOCK){
		debugf("INFO: LOCK FLAG IS : UNLOCK!!!\n");
		lcd_printf("\n   INFO: LOCK FLAG IS : UNLOCK!!!\n");
	}
	get_secboot_base_from_dt();
#endif

	do_fastboot();

	return;
}

#ifdef CONFIG_ERASE_SPL_AUTO_DOWNLOAD
/**
 * If the SPL is erased, the romcode will enter the download process.
 * Notice: SPL must download.
 */
int erase_spl_enter_download_mode(void)
{
	if (0 != common_raw_erase("splloader", (uint64_t)0, (uint64_t)0)) {
		debugf("erase partition splloader fail!\n");
		return -1;
	} else {
		if (0 != common_raw_erase("splloader_bak", (uint64_t)0, (uint64_t)0)) {
			debugf("erase partition splloader_bak fail!\n");
			return -2;
		} else {
			debugf("erase partition splloader and splloader_bak ok\n");
			reset_to_normal(CMD_NORMAL_MODE);
			while(1);
		}
	}

	return 0;
}
#endif

void autodloader_mode(void)
{
	debugf("Enter autodloader mode\n");

#ifdef CONFIG_ERASE_SPL_AUTO_DOWNLOAD
	if (0 != erase_spl_enter_download_mode()) {
		debugf("erase partition splloader and splloader_bak fail!\n");
		debugf("enter old autodloader_mode!\n");
	}
#endif

#if (defined CONFIG_X86) && (defined CONFIG_MOBILEVISOR) && (defined CONFIG_SPRD_SOC_SP9853I)
	tos_start_notify();
#endif

#ifdef CONFIG_SECBOOT
	get_secboot_base_from_dt();
#endif
	/* remap iram */
	//autodlader_remap();
	/* main handler receive and jump */
	autodloader_mainhandler();

	/*reach here means error happened*/
	return;
}

void charge_mode(void)
{
	debugf("enter\n");

	g_charger_mode = 1;
	setenv("bootmode", "charger");
	vlx_nand_boot(BOOT_PART, BACKLIGHT_ON, LCD_ON);

}

void engtest_mode(void)
{
	printf("enter\n");
	setenv("bootmode", "engtest");
	vlx_nand_boot(BOOT_PART, BACKLIGHT_OFF, LCD_ON);

}


void alarm_mode(void)
{
	debugf("enter\n");
	setenv("bootmode", "alarm");
	vlx_nand_boot(BOOT_PART, BACKLIGHT_OFF, LCD_ON);

}

void factorytest_mode(void)
{
    debugf("factorytest enter\n");
    setenv("bootmode", "factorytest");
#ifdef CONFIG_CALIMODE_USE_BOOTIMG
	vlx_nand_boot(BOOT_PART, BACKLIGHT_ON, LCD_ON);
#else
	vlx_nand_boot(RECOVERY_PART, BACKLIGHT_ON, LCD_ON);
#endif
    return;
}

void sprdisk_mode(void)
{
	debugf("enter\n");
	setenv("bootmode", "sprdisk");
	vlx_nand_boot(BOOT_PART, BACKLIGHT_OFF, LCD_ON);

}

void apkmmi_mode(void)
{
	debugf("enter\n");
	setenv("bootmode", "apkmmi_mode");
	vlx_nand_boot(BOOT_PART, BACKLIGHT_ON, LCD_ON);
}

void upt_mode(void)
{
	debugf("enter\n");
	setenv("bootmode", "upt_mode");
	vlx_nand_boot(BOOT_PART, BACKLIGHT_ON, LCD_ON);
}
