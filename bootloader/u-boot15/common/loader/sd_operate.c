#include <linux/types.h>
#include <common.h>
#include <part.h>
#include <mmc.h>
#include <fat.h>
#include <android_bootimg.h>

//rootfs.cpio.gz
#define SD_RAMDISK   "ramdisk.img"

#define TEST_VERIFY_FILE ".sprdtest"

#define SD_BACKUP_MISC_NAME  ".bak.misc.img"
#define SD_BACKUP_RECOVERY_NAME   ".bak.recovery.img"


/*Dangerous defination, always avoid use buffer like this!*/
#define BACKUP_RECOVERY_BUF_ADDR    0x9d000000

extern int _boot_load_separate_dt(void);
extern int sprd_host_init(int sdio_type);

int find_sd_backup_misc_flag = 0;
int _sd_fat_mount()
{
	struct mmc *mmc;
	block_dev_desc_t *dev_desc = NULL;
	int ret = 0;

	debugf("tick=%ld\n",get_ticks());
	mmc = board_sd_init();
	dev_desc = &mmc->block_dev;
	if (dev_desc == NULL) {
		debugf("no mmc block device found\n");
		return -1;
	}
	ret = fat_register_device(dev_desc, 1);
	if (ret < 0) {
		debugf("fat regist fail %d\n", ret);
		return -1;
	}
	ret = file_fat_detectfs();
	if (ret) {
		debugf("detect fs failed\n");
		return -1;
	}

	debugf("after mount fat in sd, tick=%ld\n",get_ticks());

	return 0;
}

#ifdef OTA_BACKUP_MISC_RECOVERY

char misc_buf[8192];

int get_recovery_msg_in_sd(void* out,int size)
{

	int ret = 0;

	ret = _sd_fat_mount();
	if (ret < 0) {
		debugf("mount fat fs in sd fail\n");
		return -1;
	}

	ret = file_fat_read(SD_BACKUP_MISC_NAME, (void *)misc_buf, sizeof(misc_buf));
	if (ret <= 0) {
		debugf("No backup MISC partition in sd card, ret=%d\n", ret);
		find_sd_backup_misc_flag = 0;
	} else {
		debugf("read BACKUP_MISC OK,ret=%d\n", ret);
		memcpy(out, misc_buf, size);
		find_sd_backup_misc_flag = 1;
	}
	debugf("fat_read %d,tick=%ld\n", ret,get_ticks());
	return ret;
}



int boot_load_recovery_in_sd(boot_img_hdr * hdr)
{

	int ret = 0;

	unsigned int header_size = 0;
	unsigned int kernel_size = 0;
	unsigned int ramdisk_size = 0;
	unsigned int dt_size = 0;
	unsigned int total_size = 0;
	unsigned int dt_img_adr = 0;

	unsigned int offset = 0;

	if (0 == find_sd_backup_misc_flag) {
		debugf("No backup MISC in sd card, no need of load backup recovery\n");
		return -1;
	}

	header_size = 4 * EMMC_SECTOR_SIZE;
	ret = file_fat_read(SD_BACKUP_RECOVERY_NAME, (void *)hdr, header_size);
	if (ret <= 0) {
		debugf("No backup RECOVERY partition in sd card, ret=%d\n", ret);
		return -1;
	}

	/*image header check*/
	if (0 != memcmp(hdr->magic, BOOT_MAGIC, BOOT_MAGIC_SIZE)) {
		debugf("Bad boot image header, give up boot!!!!\n");
		return -1;
	}

	kernel_size = (hdr->kernel_size + (KERNL_PAGE_SIZE - 1)) & (~(KERNL_PAGE_SIZE - 1));
	ramdisk_size = (hdr->ramdisk_size + (KERNL_PAGE_SIZE - 1)) & (~(KERNL_PAGE_SIZE - 1));
	dt_size = (hdr->dt_size + (KERNL_PAGE_SIZE - 1)) & (~(KERNL_PAGE_SIZE - 1));
	total_size = header_size + kernel_size + ramdisk_size + dt_size;

	ret = file_fat_read(SD_BACKUP_RECOVERY_NAME, (void *)BACKUP_RECOVERY_BUF_ADDR, total_size);
	if (ret <= 0) {
		debugf("Read recovery image file in SD fail, ret=%d\n", ret);
		return -1;
	}

	offset = header_size;
	memcpy((void *)KERNEL_ADR, (void *)(BACKUP_RECOVERY_BUF_ADDR + offset), kernel_size);
	debugf("Load kernel to address 0x%x, size from header(0x%x), size padded(0x%x)\n",
		(ulong)KERNEL_ADR, hdr->kernel_size, kernel_size);

	offset += kernel_size;
	memcpy((void *)RAMDISK_ADR, (void *)(BACKUP_RECOVERY_BUF_ADDR + offset), ramdisk_size);
	debugf("Load ramdisk to address 0x%x, size from header(0x%x), size padded(0x%x)\n",
		(ulong)RAMDISK_ADR, hdr->ramdisk_size, ramdisk_size);

#ifdef CONFIG_SEPARATE_DT
	if (!_boot_load_separate_dt())
		return -1;
#else
	dt_img_adr = RAMDISK_ADR - dt_size - KERNL_PAGE_SIZE;
	offset += ramdisk_size;
	memcpy((void *)dt_img_adr, (void *)(BACKUP_RECOVERY_BUF_ADDR + offset), dt_size);

	if (load_dtb((void*)DT_ADR, (void *)dt_img_adr)) {
		debugf("Load DT of SD backuped recovery error!\n");
		return -1;
	}
	debugf("Load dt to address 0x%x, size from header(0x%x), size padded(0x%x)\n",
		(ulong)DT_ADR, hdr->dt_size, dt_size);
#endif

	return 0;
}

#endif

int load_sd_ramdisk(void* buf,int size)
{
	int ret = 0;
	char bufread[10];

	printf("%s: start, tick=%ld\n",__func__,get_ticks());
	ret = file_fat_read(TEST_VERIFY_FILE, bufread, 10);
	if (ret<=0){
		printf("sd verity file read error %d\n", ret);
		return ret;
	}

	ret = file_fat_read(SD_RAMDISK, buf, size);
	if(ret <= 0){
		printf("sd file read error %d\n", ret);
	}

	printf("fat_read %d,tick=%ld\n", ret,get_ticks());
	return ret;
}
