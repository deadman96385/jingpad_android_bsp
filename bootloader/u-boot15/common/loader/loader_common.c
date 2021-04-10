#include "loader_common.h"
#include <mmc.h>
#include <fat.h>
#if defined(CONFIG_OF_LIBFDT)
#include <libfdt.h>
#include <fdt_support.h>
#endif
#include <sprd_common_rw.h>
#include <linux/usb/usb_uboot.h>

#ifdef CONFIG_MINI_TRUSTZONE
#include "trustzone_def.h"
#endif

#ifdef CONFIG_MEM_LAYOUT_DECOUPLING
#include "cp_mem_decoupling.h"
#endif
#include "sprd_cpcmdline.h"
#include <asm/arch/sprd_reg.h>
#include <hwfeature.h>

#define DECOUPLING_INFO_PARTITION "modem"
#ifdef CONFIG_SUPPORT_NR
#define DECOUPLING_INFO_PARTITION_NRPHY "nrphy"
#define DECOUPLING_INFO_PARTITION_V3PHY "v3phy"
#endif


unsigned char raw_header[8192];
unsigned int g_charger_mode = 0;
char serial_number_to_transfer[SP15_MAX_SN_LEN];

extern int charger_connected(void);
extern void modem_entry(void);

unsigned short calc_checksum(unsigned char *dat, unsigned long len)
{
	unsigned short num = 0;
	unsigned long chkSum = 0;
	while (len > 1) {
		num = (unsigned short)(*dat);
		dat++;
		num |= (((unsigned short)(*dat)) << 8);
		dat++;
		chkSum += (unsigned long)num;
		len -= 2;
	}
	if (len) {
		chkSum += *dat;
	}
	chkSum = (chkSum >> 16) + (chkSum & 0xffff);
	chkSum += (chkSum >> 16);
	return (~chkSum);
}

unsigned char _chkNVEcc(uint8_t *buf, uint64_t size, uint32_t checksum)
{
	uint16_t crc;

	crc = calc_checksum(buf, (unsigned long)size);
	debugf("_chkNVEcc calcout 0x%x, org 0x%x\n", crc, (uint16_t)checksum);
	return (crc == (uint16_t) checksum);
}

/*modif to support the sp15 64 bit sn NO */
char *get_product_sn(void)
{
	SP09_PHASE_CHECK_T phase_check_sp09;
	SP15_PHASE_CHECK_T phase_check_sp15;
	uint32_t magic;

	memset(serial_number_to_transfer, 0x0, SP15_MAX_SN_LEN);

	strcpy(serial_number_to_transfer, "0123456789ABCDEF");
	if (0 != common_raw_read(PRODUCTINFO_FILE_PATITION, sizeof(magic), (uint64_t)0, (char *)&magic)) {
		errorf("read miscdata error.\n");
		return serial_number_to_transfer;
	}
	if(magic == SP09_SPPH_MAGIC_NUMBER){
		if(common_raw_read(PRODUCTINFO_FILE_PATITION,sizeof(phase_check_sp09), (uint64_t)0, (char *)&phase_check_sp09)){
			debugf("sp09 read miscdata error.\n");
			return serial_number_to_transfer;
		}
		if(strlen(phase_check_sp09.SN1)){
			memcpy(serial_number_to_transfer, phase_check_sp09.SN1, SP09_MAX_SN_LEN);
		}
	}else if(magic == SP15_SPPH_MAGIC_NUMBER){
		if(common_raw_read(PRODUCTINFO_FILE_PATITION, sizeof(phase_check_sp15), (uint64_t)0 ,(char *)&phase_check_sp15)){
			debugf("sp15 read miscdata error.\n");
			return serial_number_to_transfer;
		}
		if(strlen(phase_check_sp15.SN1)){
			memcpy(serial_number_to_transfer, phase_check_sp15.SN1, SP15_MAX_SN_LEN);
		}
	}
	return serial_number_to_transfer;
}

void fdt_fixup_all(u8 *fdt_blob)
{
	uint32_t fdt_size;
	boot_img_hdr *hdr = raw_header;
	int err;
	char  *boot_mode_type_str;

	if (fdt_check_header(fdt_blob) != 0) {
		errorf("image is not a fdt\n");
	}

#ifdef CONFIG_SPLASH_SCREEN
	fdt_fixup_lcdid(fdt_blob);
	fdt_fixup_lcdname(fdt_blob);
	fdt_fixup_lcdbase(fdt_blob);
	fdt_fixup_lcdsize(fdt_blob);
	fdt_fixup_pixelclock(fdt_blob);
	fdt_fixup_lcdbpix(fdt_blob);
#endif

#ifndef CONFIG_ZEBU
	fdt_fixup_adc_calibration_data(fdt_blob);
#endif
	//fdt_fixup_dram_training(fdt_blob);
	fdt_fixup_ddr_size(fdt_blob);
	fdt_fixup_ro_boot_ramsize(fdt_blob);
	fdt_fixup_ddrsize_range(fdt_blob);
	fdt_fixup_hwfeature(fdt_blob);
	fdt_fixup_sysdump_uboot(fdt_blob);
	fdt_fixup_sysdump_magic(fdt_blob);
#ifdef CONFIG_SECURE_BOOT
	fdt_fixup_secureboot_param(fdt_blob);
#endif
#ifdef CONFIG_NAND_BOOT
	fdt_fixup_mtd(fdt_blob);
#ifdef CONFIG_UBI_ATTACH_MTD
	fdt_fixup_ubi_ai(fdt_blob);
#endif
#endif

#ifdef CONFIG_MEM_LAYOUT_DECOUPLING
	fdt_fixup_cp_coupling_info(fdt_blob, DECOUPLING_INFO_PARTITION);
#ifdef CONFIG_SUPPORT_NR
	fdt_fixup_cp_coupling_info(fdt_blob, DECOUPLING_INFO_PARTITION_NRPHY);
	fdt_fixup_cp_coupling_info(fdt_blob, DECOUPLING_INFO_PARTITION_V3PHY);
#endif
#endif

#if defined (CONFIG_SP_DDR_BOOT) && defined (CONFIG_MEM_LAYOUT_DECOUPLING)
	/* sp ddr boot info */
	fdt_fixup_sp_info(fdt_blob);
#endif

	/*max let cp_cmdline_fixup befor fdt_fixup_cp_boot*/
	cp_cmdline_fixup();
	fdt_fixup_cp_boot(fdt_blob);

	boot_mode_type_str = getenv("bootmode");
	if (NULL != boot_mode_type_str)
	{
		if(!strncmp(boot_mode_type_str, "sprdisk", 7)) {
			fdt_fixup_memleakon(fdt_blob);
		}
	}

	/*for verified boot*/
	fdt_fixup_verified_boot(fdt_blob);
	fdt_fixup_flash_lock_state(fdt_blob);
#ifndef CONFIG_ZEBU
	fdt_fixup_serialno(fdt_blob);
#endif
	fdt_fixup_chosen_bootargs_board_private(fdt_blob);

#ifdef CONFIG_SANSA_SECBOOT
	//fdt_fixup_socid(fdt_blob);
#endif

	/* for non iq mode, remove reserved iq memory from dtb */
	fdt_fixup_iq_reserved_mem(fdt_blob);

#ifdef CONFIG_BOARD_KERNEL_CMDLINE
	/* board kernel cmdline in header of boot.img */
	fdt_fixup_board_kernel_cmdline(fdt_blob);
#endif

	/* if enabled, set loglevel = 7*/
	fdt_fixup_loglevel(fdt_blob);
	fdt_fixup_system_mount_part_num(fdt_blob);

#ifdef CONFIG_GET_CPU_SERIAL_NUMBER
	fdt_fixup_cpu_serial_number(fdt_blob);
#endif

#ifdef CONFIG_VBOOT_V2
    fdt_fixup_vboot(fdt_blob);
#endif

	fdt_fixup_first_mode(fdt_blob);

#ifdef CONFIG_TEECFG_CUSTOM
	if(reboot_mode_check() != CMD_TOS_PANIC_MODE)
		fdt_fixup_tee_reserved_mem(fdt_blob);
#endif
	return;
}

void fdt_fixup_all_x86(u8 *fdt_blob)
{
	uint32_t fdt_size;
	boot_img_hdr *hdr = raw_header;
	int err;
	char  *boot_mode_type_str;

	if (fdt_check_header(fdt_blob) != 0) {
		errorf("image is not a fdt\n");
	}

#ifdef CONFIG_SPLASH_SCREEN
	fdt_fixup_lcdid(fdt_blob);
	fdt_fixup_lcdname(fdt_blob);
	fdt_fixup_lcdbase(fdt_blob);
	fdt_fixup_lcdsize(fdt_blob);
	fdt_fixup_pixelclock(fdt_blob);
	fdt_fixup_lcdbpix(fdt_blob);
#endif

	fdt_fixup_adc_calibration_data(fdt_blob);

	fdt_fixup_serialno(fdt_blob);

#ifdef CONFIG_MEM_LAYOUT_DECOUPLING
	fdt_fixup_cp_coupling_info(fdt_blob, DECOUPLING_INFO_PARTITION);
#ifdef CONFIG_SUPPORT_NR
	fdt_fixup_cp_coupling_info(fdt_blob, DECOUPLING_INFO_PARTITION_NRPHY);
	fdt_fixup_cp_coupling_info(fdt_blob, DECOUPLING_INFO_PARTITION_V3PHY);
#endif
#endif

	/*max let cp_cmdline_fixup befor fdt_fixup_cp_boot*/
	cp_cmdline_fixup();

	fdt_fixup_cp_boot(fdt_blob);

	/*for verified boot*/
	fdt_fixup_verified_boot(fdt_blob);
	fdt_fixup_flash_lock_state(fdt_blob);

	/* for non iq mode, remove reserved iq memory from dtb */
	fdt_fixup_iq_reserved_mem(fdt_blob);

	fdt_fixup_pmic_wa(fdt_blob);

#ifdef CONFIG_BOARD_KERNEL_CMDLINE
	/* board kernel cmdline in header of boot.img */
	fdt_fixup_board_kernel_cmdline(fdt_blob);
#endif

	/* if enabled, set loglevel = 7*/
	fdt_fixup_loglevel(fdt_blob);
	fdt_fixup_system_mount_part_num(fdt_blob);

#ifdef CONFIG_VBOOT_V2
    fdt_fixup_vboot(fdt_blob);
#endif
}

#ifdef CONFIG_X86
static int start_linux_x86()
{
	struct boot_params *base_ptr;
	struct boot_img_hdr *boot_hdr = (void *)raw_header;
	uint64_t load_address = 0;
	char *bzImage_addr = KERNEL_ADR;
	ulong bzImage_size = 0;
	ulong initrd_addr = RAMDISK_ADR;
	ulong initrd_size = PAD_SIZE(boot_hdr->ramdisk_size, KERNL_PAGE_SIZE);
	int image_64bit = 0;

	debugf("initrd_size: 0x%lx\n", initrd_size);
	disable_interrupts();
	wbinvd();

#ifndef CONFIG_ZEBU
	/*start modem CP */
	modem_entry();
#endif

	/* Setup board for maximum PC/AT Compatibility */
	setup_pcat_compatibility();
	/* Lets look for */
	base_ptr = load_zimage(bzImage_addr, bzImage_size, &load_address);

	if (!base_ptr) {
		puts("## Kernel loading failed ...\n");
		return -1;
	}
	if (setup_zimage(base_ptr, (char *)base_ptr + COMMAND_LINE_OFFSET,
			0, initrd_addr, initrd_size)) {
		puts("Setting up boot parameters failed ...\n");
		return -1;
	}
	image_64bit = image_check64(base_ptr);
	/* we assume that the kernel is in place */
	return boot_linux_kernel((ulong)base_ptr, load_address, image_64bit);
}
#endif

#ifdef CONFIG_ARM
static int start_linux(uchar *dt_addr)
{
#ifdef CONFIG_OF_LIBFDT
	void (*theKernel) (int zero, int arch, u32 params);
	theKernel = (void (*)(void *, int, int, int))KERNEL_ADR;

	/*disable all caches */
	cleanup_before_linux();

	/*start modem CP */
#ifndef CONFIG_ZEBU
	modem_entry();
#endif

#ifdef CONFIG_MINI_TRUSTZONE
	trustzone_entry(TRUSTZONE_ADR + 0x200);
#endif
	/* jump to kernel with register set */
	theKernel(0, machine_arch_type, (u32)dt_addr);
#else
	void (*theKernel) (int zero, int arch, u32 params);
	u32 machine_type = 0;

	machine_type = machine_arch_type;	/* get machine type */
	theKernel = (void (*)(int, int, u32))KERNEL_ADR;	/* set the kernel address */

	/*start modem CP */
	cp_cmdline_fixup();

	/*disable all caches */
	cleanup_before_linux();

	/*start modem CP */
	modem_entry();

	/* jump to kernel with register set */
	theKernel(0, machine_type, VLX_TAG_ADDR);
#endif /*CONFIG_OF_LIBFDT */
	while (1) ;
	return 0;
}
#endif
static int start_linux_armv8(uchar *dt_addr)
{
	void (*theKernel) (void *dtb_addr, int zero, int arch, int reserved);
	theKernel = (void (*)(void *, int, int, int))KERNEL_ADR;

	/*before switch to el2,flush all cache */
	/*FIXME: cleanup_before_linux() will cause panic here, we need to find the solution*/
	flush_dcache_range(CONFIG_SYS_SDRAM_BASE, CONFIG_SYS_SDRAM_END);
#ifdef CONFIG_DUAL_DDR
	flush_dcache_range(CONFIG_SYS_SDRAM_BASE2, CONFIG_SYS_SDRAM_END2);
#endif

	/*sharkle and sharklj1 need disable mmu and cache before jump into kernel*/
	cleanup_before_linux();

	/*start modem CP */
	modem_entry();

#ifdef CONFIG_MINI_TRUSTZONE
	trustzone_entry(TRUSTZONE_ADR + 0x200);
#endif

	/*kernel must run in el2, so here switch to el2 */
	armv8_switch_to_el2();
	theKernel(dt_addr, 0, 0, 0);

	/*never enter here*/
	while (1) ;
	return 0;
}

extern uint32_t uboot_start_time;
void vlx_entry(uchar *dt_addr)
{
	char *bootmode = getenv("bootmode");
	uint32_t consume_time;

	consume_time = SCI_GetTickCount() - uboot_start_time;
	printf("enter mode %s, consume time: %dms\n",
		!bootmode ? "normal" : bootmode, consume_time);

	/* the last time to write log */
	write_log_last();

#ifdef DFS_ON_ARM7
	cp_dfs_param_for_arm7();
#endif
	/*shutdown usb ldo, can't shutdown it in the ldo_sleep.c because download mode must use usb */
	usb_driver_exit();

#ifdef CONFIG_ARM64
	smp_kick_all_cpus();
	start_linux_armv8(dt_addr);
#endif
#ifdef CONFIG_ARM
	start_linux(dt_addr);
#endif
#ifdef CONFIG_X86
	start_linux_x86();
#endif
}
