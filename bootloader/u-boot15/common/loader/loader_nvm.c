#include <common.h>
#include <android_bootimg.h>
#include "loader_common.h"
#include <malloc.h>
#include <ext_common.h>
#include <ext4fs.h>
#include <linux/sizes.h>
#include "dl_operate.h"
#include "sci_img.h"
#include "sprd_common_rw.h"
#include <chipram_env.h>
#ifdef  CONFIG_SPRD_HW_I2C
#include <sprd_i2c_hwchn.h>
#endif

#include <secureboot/sprdsec_header.h>
#include <secureboot/sec_common.h>
#include <uboot_sec_drv.h>
#include <avb/uboot_avb_ops.h>
#include <otp_helper.h>
#include <stdio_dev.h>
#ifdef CONFIG_SECBOOT
#include <lcd_console.h>
#endif
#ifdef CONFIG_ARM7_RAM_ACTIVE
extern void pmic_arm7_RAM_active(void);
#endif
#ifdef CONFIG_SOC_IWHALE2
extern void aon_lpc_config();
#endif

#ifdef CONFIG_MINI_TRUSTZONE
#include "trustzone_def.h"
#endif

#ifdef CONFIG_SECURE_BOOT
#include "secure_boot.h"
#include "secure_verify.h"
#include <linux/types.h>
#endif

#ifdef CONFIG_OF_LIBFDT
#include <libfdt.h>
#include "dev_tree.h"
#endif

#if (defined CONFIG_SECBOOT) && (defined CONFIG_VBOOT_V2)
unsigned os_version __attribute__((aligned(4096))); /*must be PAGE ALIGNED*/
unsigned char root_of_trust_str[ROOT_OF_TRUST_MAXSIZE] __attribute__((aligned(4096)));
#endif
#ifdef CONFIG_SPRD_SOC_SP9853I
#include <asm/arch/sprd_reg.h>
#endif
DECLARE_GLOBAL_DATA_PTR;

extern int lcd_line_length;
extern enVerifiedState g_verifiedbootstate;

extern int fdt_fixup_memory_region(void *fdt, int *auto_mem_num_p);
extern int get_dt_end_addr(void *fdt, uchar **addr);
extern int lcd_get_size(int *line_length);
extern unsigned char _chkNVEcc(uint8_t *buf, uint64_t size, uint32_t checksum);
extern void wakeup_source_enable();
extern void ap_clk_doze_enable();
#ifdef CONFIG_SOC_IWHALE2
extern void ag_tg_ldsp_hold();
#endif

#define MODEM_MAGIC		"SCI1"
#define MODEM_HDR_SIZE		(12 * 512) //size of a block
#define SCI_TYPE_MODEM_BIN	1
#define SCI_TYPE_PARSING_LIB	2
#define SCI_LAST_HDR		0x100
#define MODEM_SHA1_HDR		0x400
#define MODEM_SHA1_SIZE		20

#define FREE_RAM_SPACE_ADDR		0x9d000000 /* 0x9d000000 ~9f000000  30M Bytes Free*/
/*secure lcs*/
#define SECURE_LCS               0x5

#define DT_TABLE_MAGIC 0xd7b7ab1e

struct dt_table_header {
	uint32_t magic;
	uint32_t total_size;
	uint32_t header_size;
	uint32_t dt_entry_size;
	uint32_t dt_entry_count;
	uint32_t dt_entries_offset;
	uint32_t page_size;
	uint32_t reserved[1];
};
struct dt_table_entry {
	uint32_t dt_size;
	uint32_t dt_offset;
	uint32_t id;
	uint32_t rev;
	uint32_t custom[4];
};

typedef struct {
	uint32_t type_flags;
	uint32_t offset;
	uint32_t length;
} data_block_header_t;

typedef struct _BOOT_IMG_OFFSET {
	uint64_t hdr_offset;
	uint64_t kernel_offset;
	uint64_t ramdisk_offset;
	uint64_t dt_offset;
	uint64_t recovery_dtbo_offset;	/* recovery dtbo/acpio */
}BOOT_IMG_OFFSET;
static BOOT_IMG_OFFSET boot_img_offset;
unsigned int g_DeviceStatus = VBOOT_STATUS_LOCK;


#ifdef CONFIG_SUPPORT_TDLTE
static boot_image_required_t const s_boot_image_tl_table[] = {
#if !defined( CONFIG_KERNEL_BOOT_CP )
	{"tl_fixnv1", "tl_fixnv2", LTE_FIXNV_SIZE, LTE_FIXNV_ADDR},
	{"tl_runtimenv1", "tl_runtimenv2", LTE_RUNNV_SIZE, LTE_RUNNV_ADDR},
	{"tl_modem", NULL, LTE_MODEM_SIZE, LTE_MODEM_ADDR},
	{"tl_ldsp", NULL, LTE_LDSP_SIZE, LTE_LDSP_ADDR},	//ltedsp
	{"tl_tgdsp", NULL, LTE_GDSP_SIZE, LTE_GDSP_ADDR},
#endif
	{NULL, NULL, 0, 0}
};
#endif

#ifdef CONFIG_SUPPORT_WLTE
static boot_image_required_t const s_boot_image_wl_table[] = {
#if !defined( CONFIG_KERNEL_BOOT_CP )
	{"wl_fixnv1", "wl_fixnv2", LTE_FIXNV_SIZE, LTE_FIXNV_ADDR},
	{"wl_runtimenv1", "wl_runtimenv2", LTE_RUNNV_SIZE, LTE_RUNNV_ADDR},
	{"wl_modem", NULL, LTE_MODEM_SIZE, LTE_MODEM_ADDR},
	{"wl_ldsp", NULL, LTE_LDSP_SIZE, LTE_LDSP_ADDR},
	{"wl_gdsp", NULL, LTE_GDSP_SIZE, LTE_GDSP_ADDR},
	{"wl_warm", NULL, WL_WARM_SIZE, WL_WARM_ADDR},
#endif
	{NULL, NULL, 0, 0}
};
#endif

#ifdef CONFIG_SUPPORT_GSM
static boot_image_required_t const s_boot_image_gsm_table[] = {
#if !defined( CONFIG_KERNEL_BOOT_CP )
	{"g_fixnv1", "g_fixnv2", GSM_FIXNV_SIZE, GSM_FIXNV_ADDR},
	{"g_runtimenv1", "g_runtimenv2", GSM_RUNNV_SIZE, GSM_RUNNV_ADDR},
	{"g_modem", NULL, GSM_MODEM_SIZE, GSM_MODEM_ADDR},
	{"g_dsp", NULL, GSM_DSP_SIZE, GSM_DSP_ADDR},
#endif
	{NULL, NULL, 0, 0}
};
#endif

#ifdef CONFIG_SUPPORT_LTE
static boot_image_required_t const s_boot_image_lte_table[] = {
#if (!defined( CONFIG_KERNEL_BOOT_CP )) && (!defined(CONFIG_MEM_LAYOUT_DECOUPLING))
#ifdef CONFIG_ADVANCED_LTE
	{"l_fixnv1","l_fixnv2",LTE_FIXNV_SIZE,LTE_FIXNV_ADDR},
	{"l_runtimenv1","l_runtimenv2",LTE_RUNNV_SIZE,LTE_RUNNV_ADDR},
	{"l_modem",NULL,LTE_MODEM_SIZE,LTE_MODEM_ADDR},
	{"l_tgdsp",NULL,LTE_TGDSP_SIZE ,LTE_TGDSP_ADDR}, //tddsp
	{"l_ldsp",NULL,LTE_LDSP_SIZE ,LTE_LDSP_ADDR},
#else
	{"l_fixnv1", "l_fixnv2", LTE_FIXNV_SIZE, LTE_FIXNV_ADDR},
	{"l_runtimenv1", "l_runtimenv2", LTE_RUNNV_SIZE, LTE_RUNNV_ADDR},
	{"l_modem", NULL, LTE_MODEM_SIZE, LTE_MODEM_ADDR},
	{"l_ldsp", NULL, LTE_LDSP_SIZE, LTE_LDSP_ADDR},
	{"l_gdsp", NULL, LTE_GDSP_SIZE, LTE_GDSP_ADDR},
	{"l_warm", NULL, WL_WARM_SIZE, WL_WARM_ADDR},
#endif
#endif
#ifdef  CONFIG_ADVANCED_LTE
#ifdef CONFIG_SUPPORT_AGDSP
	{"l_agdsp",NULL,LTE_AGDSP_SIZE ,LTE_AGDSP_ADDR}, //agdsp now is boot by uboot
#endif// end CONFIG_SUPPORT_AGDSP
#endif
	{NULL, NULL, 0, 0}
};
#endif

#ifdef CONFIG_SUPPORT_TD
static boot_image_required_t const s_boot_image_TD_table[] = {
#if !defined( CONFIG_KERNEL_BOOT_CP )
	{"tdfixnv1", "tdfixnv2", FIXNV_SIZE, TDFIXNV_ADR},
	{"tdruntimenv1", "tdruntimenv2", RUNTIMENV_SIZE, TDRUNTIMENV_ADR},
	{"tdmodem", NULL, TDMODEM_SIZE, TDMODEM_ADR},
	{"tddsp", NULL, TDDSP_SIZE, TDDSP_ADR},
#endif
	{NULL, NULL, 0, 0}
};
#endif

#ifdef CONFIG_SUPPORT_W
static boot_image_required_t const s_boot_image_W_table[] = {
#if (!defined( CONFIG_KERNEL_BOOT_CP )) && (!defined(CONFIG_MEM_LAYOUT_DECOUPLING))
	{"wfixnv1", "wfixnv2", FIXNV_SIZE, WFIXNV_ADR},
	{"wruntimenv1", "wruntimenv2", RUNTIMENV_SIZE, WRUNTIMENV_ADR},
	{"wmodem", NULL, WMODEM_SIZE, WMODEM_ADR},
	{"wdsp", NULL, WDSP_SIZE, WDSP_ADR},
#endif
	{NULL, NULL, 0, 0}
};
#endif

#ifdef CONFIG_SUPPORT_WIFI
static boot_image_required_t const s_boot_image_WIFI_table[] = {
	{"wcnfixnv1", "wcnfixnv2", FIXNV_SIZE, WCNFIXNV_ADR},
	{"wcnruntimenv1", "wcnruntimenv2", RUNTIMENV_SIZE, WCNRUNTIMENV_ADR},
	{"wcnmodem", NULL, WCNMODEM_SIZE, WCNMODEM_ADR},
	{NULL, NULL, 0, 0}
};
#endif

static boot_image_required_t const s_boot_image_COMMON_table[] = {
#ifdef CONFIG_SIMLOCK_ENABLE
	{"simlock", NULL, SIMLOCK_SIZE, SIMLOCK_ADR},
#endif
#ifdef CONFIG_DFS_ENABLE
#if !defined( CONFIG_KERNEL_BOOT_CP )
	{"pm_sys", NULL, DFS_SIZE, DFS_ADDR},
#endif
#endif
	{NULL, NULL, 0, 0}

};

#ifdef CONFIG_MINI_TRUSTZONE
static boot_image_required_t const s_boot_image_TZ_table[] = {
	{"sml", NULL, TRUSTRAM_SIZE, TRUSTRAM_ADR},
	{NULL, NULL, 0, 0}

};
#endif

static boot_image_required_t *const s_boot_image_table[] = {
#ifdef CONFIG_SUPPORT_TDLTE
	s_boot_image_tl_table,
#endif

#ifdef CONFIG_SUPPORT_WLTE
	s_boot_image_wl_table,
#endif

#ifdef CONFIG_SUPPORT_LTE
	s_boot_image_lte_table,
#endif

#ifdef CONFIG_SUPPORT_GSM
	s_boot_image_gsm_table,
#endif

#ifdef CONFIG_SUPPORT_TD
	s_boot_image_TD_table,
#endif

#ifdef CONFIG_SUPPORT_W
	s_boot_image_W_table,
#endif

#ifdef CONFIG_SUPPORT_WIFI
	s_boot_image_WIFI_table,
#endif
#ifdef CONFIG_MINI_TRUSTZONE
	s_boot_image_TZ_table,
#endif
	s_boot_image_COMMON_table,

	0
};

#ifdef CONFIG_SECURE_BOOT
uint8_t header_buf[SEC_HEADER_MAX_SIZE];
#endif

/* Note: return NULL if kernel offset was not found */
struct boot_img_hdr *get_boot_img_hdr(void)
{
	return !boot_img_offset.kernel_offset ? NULL : (boot_img_hdr *)raw_header;
}

struct boot_img_hdr_v1 *get_boot_img_hdr_v1(struct boot_img_hdr *hdr)
{
	return (struct boot_img_hdr_v1 *)(hdr + 1);
}

struct boot_img_hdr_v2 *get_boot_img_hdr_v2(struct boot_img_hdr *hdr)
{
	struct boot_img_hdr_v1 *hdr_v1 = get_boot_img_hdr_v1(hdr);

	return (struct boot_img_hdr_v2 *)(hdr_v1 + 1);
}

#ifdef CONFIG_SECURE_BOOT

int get_spl_hash(void *hash_data)
{
	NBLHeader *header;
	unsigned int len;
	uint8_t *spl_data;
	int ret = 0;
	int size = CONFIG_SPL_HASH_LEN;
	spl_data = malloc(size);
	if (!spl_data) {
		return ret;
	}

	if (0 != common_raw_read("splloader", (uint64_t)size, (uint64_t)0, (char *) spl_data)) {
		errorf("PARTITION_BOOT1 read error \n");
		return ret;
	}

	header = (NBLHeader *) ((uint8_t *) spl_data + BOOTLOADER_HEADER_OFFSET);
	len = header->mHashLen;
	/*clear header */
	memset(header, 0, sizeof(NBLHeader));
	header->mHashLen = len;
	debugf("cal spl hash len=%d\n", header->mHashLen * 4);
	ret = cal_sha1(spl_data, (header->mHashLen) << 2, hash_data);

	if (spl_data)
		free(spl_data);

	return ret;
}
#endif
void _boot_secure_check(void)
{
#ifdef SECURE_BOOT_ENABLE
	secure_check(DSP_ADR, 0, DSP_ADR + DSP_SIZE - VLR_INFO_OFF, CONFIG_SYS_NAND_U_BOOT_DST + CONFIG_SYS_NAND_U_BOOT_SIZE - KEY_INFO_SIZ - VLR_INFO_OFF);
	secure_check(MODEM_ADR, 0, MODEM_ADR + MODEM_SIZE - VLR_INFO_OFF,
		     CONFIG_SYS_NAND_U_BOOT_DST + CONFIG_SYS_NAND_U_BOOT_SIZE - KEY_INFO_SIZ - VLR_INFO_OFF);
#ifdef CONFIG_SIMLOCK
	secure_check(SIMLOCK_ADR, 0, SIMLOCK_ADR + SIMLOCK_SIZE - VLR_INFO_OFF,
		     CONFIG_SYS_NAND_U_BOOT_DST + CONFIG_SYS_NAND_U_BOOT_SIZE - KEY_INFO_SIZ - VLR_INFO_OFF);
#endif
#endif
	return;
}

int splash_screen_prepare(uchar *logo_part_name, u8 *addr)
{
	size_t size ;
	u32 bmp_header_size = 8192;

	size = lcd_get_size(&lcd_line_length);
	size += bmp_header_size;
#ifndef CONFIG_ZEBU
	if (0 != common_raw_read(logo_part_name, (uint64_t)size, (uint64_t)0, addr)) {
		errorf("failed to read logo partition:%s\n", logo_part_name);
		return -1;
	}
#else
	memcpy(addr, 0xb0000000, (size_t)size);
#endif

	return 0;
}

int32_t _boot_read_partition_with_backup(boot_image_required_t info)
{
	uchar header_buf[NV_HEADER_SIZE];
	uchar backup_header_buf[NV_HEADER_SIZE];
	nv_header_t *header_p = header_buf;
	nv_header_t *backup_header_p = backup_header_buf;
	uchar * backup_nv_buf = NULL;
	int status = ORIGIN_BACKUP_NV_OK;
	int ret = 0;

	backup_nv_buf = malloc(info.size);
	if (NULL == backup_nv_buf) {
		errorf("no enough space for backup nv buffer\n");
		return 0;
	}

	do {
		/*read origin image header */
		if (0 != common_raw_read(info.partition, NV_HEADER_SIZE, (uint64_t)0, header_buf)) {
			errorf("read origin <<<%s>>> image header failed\n", info.partition);
			status |= ORIGIN_NV_DAMAGED;
			break;
		}

		if (NV_HEAD_MAGIC != header_p->magic) {
			errorf("<<<%s>>> header magic error, wrong magic=0x%x\n", info.partition, header_p->magic);
			status |= ORIGIN_NV_DAMAGED;
			break;
		}

		/*read origin image */
		if (0 != common_raw_read(info.partition, (uint64_t)(info.size), NV_HEADER_SIZE, info.mem_addr)) {
			errorf("read origin <<<%s>>> image data failed\n", info.partition);
			status |= ORIGIN_NV_DAMAGED;
			break;
		}

		/*check crc */
		if (_chkNVEcc(info.mem_addr, info.size, header_p->checksum)) {
			debugf("read origin <<<%s>>> image success and crc correct\n", info.partition);
		} else {
			errorf("check origin <<<%s>>> image crc wrong\n", info.partition);
			status |= ORIGIN_NV_DAMAGED;
		}
	} while(0);

	do {
		/*read backup header */
		if (0 != common_raw_read(info.bak_partition, NV_HEADER_SIZE, (uint64_t)0, backup_header_buf)) {
			errorf("read backup <<<%s>>> image header failed\n", info.bak_partition);
			status |= BACKUP_NV_DAMAGED;
			break;
		}

		if (NV_HEAD_MAGIC != backup_header_p->magic) {
			errorf("backup <<<%s>>> header magic error, wrong magic=0x%x\n", info.bak_partition, backup_header_p->magic);
			status |= BACKUP_NV_DAMAGED;
			break;
		}

		/*read bakup image */
		if (0 != common_raw_read(info.bak_partition, (uint64_t)(info.size), NV_HEADER_SIZE, backup_nv_buf)) {
			errorf("read backup <<<%s>>> image failed\n", info.bak_partition);
			status |= BACKUP_NV_DAMAGED;
			break;
		}

		/*check crc */
		if (_chkNVEcc(backup_nv_buf, info.size, backup_header_p->checksum)) {
			debugf("read backup <<<%s>>> image success and crc correct\n", info.bak_partition);
		} else {
			errorf("check backup <<<%s>>> image crc wrong\n", info.bak_partition);
			status |= BACKUP_NV_DAMAGED;
		}
	} while(0);

	switch (status) {
	case ORIGIN_BACKUP_NV_OK :
		debugf("both org and bak nv partition are ok\n");
		ret = 1;
		break;
	case ORIGIN_NV_DAMAGED :
		memcpy(info.mem_addr, backup_nv_buf, info.size);
		if (0 != common_raw_write(info.partition, NV_HEADER_SIZE, (uint64_t)0, (uint64_t)0, backup_header_buf)) {
			errorf("reapire origin <<<%s>>> image header fail\n", info.partition);
			ret = 0;
			break;
		}

		if (0 != common_raw_write(info.partition, (uint64_t)(info.size), (uint64_t)0, NV_HEADER_SIZE, backup_nv_buf)) {
			errorf("reapire origin <<<%s>>> image data fail\n", info.partition);
			ret = 0;
			break;
		}

		ret = 1;
		break;
	case BACKUP_NV_DAMAGED :
		if (0 != common_raw_write(info.bak_partition, NV_HEADER_SIZE, (uint64_t)0, (uint64_t)0, header_buf)) {
			errorf("reapire backup <<<%s>>> image header fail\n", info.bak_partition);
			ret = 0;
			break;
		}

		if (0 != common_raw_write(info.bak_partition, (uint64_t)(info.size), (uint64_t)0, NV_HEADER_SIZE, info.mem_addr)) {
			errorf("reapire backup <<<%s>>> image data fail\n", info.bak_partition);
			ret = 0;
			break;
		}
		debugf("repair backup <<<%s>>> image OK\n", info.bak_partition);
		ret = 1;
		break;
	case ORIGIN_NV_DAMAGED | BACKUP_NV_DAMAGED :
		errorf("both org <<<%s>>> and bak <<<%s>>> partition are damaged!\n", info.partition, info.bak_partition);
		ret = 0;
		break;
	}

	free(backup_nv_buf);
	return ret;
}

unsigned get_modem_img_info(const boot_image_required_t* img_info,
			    unsigned secure_offset,
			    int* is_sci,
			    size_t* total_len,
			    size_t* modem_exe_size) {
	unsigned offset = 0;

	if(!strstr((const char*)img_info->partition, "modem")) {
		*is_sci = 0;
		*total_len = img_info->size;
		*modem_exe_size = img_info->size;
		return 0;
	}

	/* Only support 10 effective headers at most for now. */
	data_block_header_t hdr_buf[11] __attribute__ ((__packed__));
	size_t read_len = sizeof(hdr_buf);

	if (common_raw_read(img_info->partition,
			    read_len,
			    secure_offset,
			    (char*)hdr_buf)) {
		debugf("Read MODEM image header failed!\n");
		return 0;
	}

	/* Check whether it's SCI image. */
	if (memcmp(hdr_buf, MODEM_MAGIC, strlen(MODEM_MAGIC))) {
		/* Not SCI format. */
		*is_sci = 0;
		*total_len = img_info->size;
		*modem_exe_size = img_info->size;

		debugf("Not SCI image.\n");

		return 0;
	}

	/* SCI image. Parse the headers */
	*is_sci = 1;

	unsigned i;
	data_block_header_t* hdr_ptr;
	int modem_offset = -1;
	int image_len = -1;

	for (i = 1, hdr_ptr = hdr_buf + 1;
	     i < sizeof hdr_buf / sizeof hdr_buf[0];
	     ++i, ++hdr_ptr) {
		unsigned type = (hdr_ptr->type_flags & 0xff);
		if (SCI_TYPE_MODEM_BIN == type) {
			modem_offset = (int)hdr_ptr->offset;
			*modem_exe_size = hdr_ptr->length;
			if(hdr_ptr->type_flags & MODEM_SHA1_HDR) {
				modem_offset += MODEM_SHA1_SIZE;
				*modem_exe_size -= MODEM_SHA1_SIZE;
			}
		}
		if (hdr_ptr->type_flags & SCI_LAST_HDR) {
			image_len = (int)(hdr_ptr->offset + hdr_ptr->length);
			break;
		}
	}

	if (-1 == modem_offset) {
		debugf("No MODEM image found in SCI image!\n");
	} else if (-1 == image_len) {
		debugf("SCI header too long!\n");
	} else {
		*total_len = image_len;
		offset = modem_offset;
	}

	debugf("Modem SCI offset: 0x%x!\n", (unsigned)offset);

	return offset;
}

/**
	Function for reading image which is needed when power on.
*/
int _boot_load_required_image(boot_image_required_t img_info)
{
	uint32_t secure_boot_offset = 0;
	int is_sci;
	size_t total_len;
	size_t exe_size;
	unsigned exe_offset;

	debugf("load %s to addr 0x%08x\n", img_info.partition, img_info.mem_addr);

	if (NULL != img_info.bak_partition) {
		debugf("load %s with backup img %s\n", img_info.partition, img_info.bak_partition);
		_boot_read_partition_with_backup(img_info);
	} else {
#if defined (CONFIG_SECURE_BOOT)
		if (common_raw_read(img_info.partition,
				    SEC_HEADER_MAX_SIZE,
				    0,
				    (char*)header_buf)) {
			debugf("%s:%s read error!\n", img_info.partition);
			return 0;
		}
		secure_boot_offset = get_code_offset(header_buf);
		exe_offset = get_modem_img_info(&img_info,
						secure_boot_offset * EMMC_SECTOR_SIZE,
						&is_sci,
						&total_len,
						&exe_size);

		common_raw_read(img_info.partition,
				exe_size,
				secure_boot_offset * EMMC_SECTOR_SIZE + exe_offset,
				(char*)FREE_RAM_SPACE_ADDR);

		secure_verify("uboot", header_buf, (u8 *)FREE_RAM_SPACE_ADDR);
		memcpy((void *)img_info.mem_addr,
		       (void*)FREE_RAM_SPACE_ADDR,
		       exe_size);
#elif defined (CONFIG_SECBOOT)
		if (0 == memcmp("pm_sys", img_info.partition, strlen("pm_sys")))
		{
		#ifndef PROJECT_SEC_CM4
			/***secboot 2nd step***/
			vboot_secure_process_flow(img_info.partition);
		#endif
		}
		else
		{
			/***secboot 2nd step***/
			vboot_secure_process_flow(img_info.partition);
		}

	#if defined (CONFIG_VBOOT_V2)
		memcpy(img_info.mem_addr,gd->verify_base,img_info.size);
	#else
		memcpy(img_info.mem_addr,(gd->verify_base + SYS_HEADER_SIZE),img_info.size);
	#endif
#else  // Secure boot is not turned on
		exe_offset = get_modem_img_info(&img_info, 0,
						&is_sci, &total_len,
						&exe_size);
		if (common_raw_read(img_info.partition,
				    exe_size,
				    exe_offset,
				    img_info.mem_addr)) {
			errorf("read %s partition fail\n", img_info.partition);
		}

#endif
	}

	return 1;
}

extern int enter_sysdump_flag;

static uint64_t boot_img_offset_v01(boot_img_hdr *hdr, uint64_t offset)
{
	uint64_t size;

	/*kernel image */
	boot_img_offset.kernel_offset = offset + KERNL_PAGE_SIZE;
	size = PAD_SIZE(hdr->kernel_size, KERNL_PAGE_SIZE);
	if (0 == size) {
		errorf("kernel image should not be zero!\n");
		return 0;
	}

	debugf("boot_img_offset.kernel_offset is 0x%llx\n", boot_img_offset.kernel_offset );

	if( hdr->ramdisk_size) {
		/* ramdisk image */
		boot_img_offset.ramdisk_offset = boot_img_offset.kernel_offset + size;
		size = PAD_SIZE(hdr->ramdisk_size, KERNL_PAGE_SIZE);
		if (0 == size) {
			errorf("ramdisk image size should not be zero\n");
			return 0;
		}

		debugf("boot_img_offset.ramdisk_offset is 0x%llx\n", boot_img_offset.ramdisk_offset );

		/* dt image */
		boot_img_offset.dt_offset = boot_img_offset.ramdisk_offset + size;

		debugf("boot_img_offset.dt_offset is 0x%llx\n", boot_img_offset.dt_offset );
	}

	return 1;
}

static uint64_t boot_img_offset_v2(boot_img_hdr *hdr, uint64_t offset)
{
	struct boot_img_hdr_v1 *hdr_v1 = get_boot_img_hdr_v1(hdr);
	struct boot_img_hdr_v2 *hdr_v2 = get_boot_img_hdr_v2(hdr);
	uint64_t size;

	/* kernel image */
	boot_img_offset.kernel_offset = offset + KERNL_PAGE_SIZE;
	size = PAD_SIZE(hdr->kernel_size, KERNL_PAGE_SIZE);
	if (0 == size) {
		errorf("kernel image should not be zero!\n");
		return 0;
	}

	debugf("boot_img_offset.kernel_offset is 0x%llx\n", boot_img_offset.kernel_offset );

	if( hdr->ramdisk_size) {
		/* ramdisk image */
		boot_img_offset.ramdisk_offset = boot_img_offset.kernel_offset + size;
		size = PAD_SIZE(hdr->ramdisk_size, KERNL_PAGE_SIZE);
		if (0 == size) {
			errorf("ramdisk image size should not be zero\n");
			return 0;
		}

		debugf("boot_img_offset.ramdisk_offset is 0x%llx\n", boot_img_offset.ramdisk_offset );
	}

	/* Fixme second stage */

	if (hdr_v1->recovery_dtbo_size) {
		/* recovery_dtbo_offset */
		boot_img_offset.recovery_dtbo_offset = boot_img_offset.ramdisk_offset + size;
		size = PAD_SIZE(hdr_v1->recovery_dtbo_size, KERNL_PAGE_SIZE);
		if (0 == size) {
			errorf("recover dtbo image size should not be zero\n");
			return 0;
		}

		debugf("boot_img_offset.recovery_dtbo_offset is 0x%llx\n", boot_img_offset.recovery_dtbo_offset);
	}

	/* dt image */
	if (hdr_v1->recovery_dtbo_size)
		boot_img_offset.dt_offset = boot_img_offset.recovery_dtbo_offset + size;
	else if (hdr->ramdisk_size)
		boot_img_offset.dt_offset = boot_img_offset.ramdisk_offset + size;

	debugf("boot_img_offset.dt_offset is 0x%llx\n", boot_img_offset.dt_offset );
	if (hdr_v2->dtb_addr != boot_img_offset.dt_offset)
		debugf("Warning: dtb addr 0x%llx on boot img hdr\n", hdr_v2->dtb_addr);
	return 1;
}

typedef uint64_t (*boot_img_offset_hdl)(boot_img_hdr *, uint64_t);
static boot_img_offset_hdl boot_img_offset_hdl_tbl[] = {
	boot_img_offset_v01,
	boot_img_offset_v01,
	boot_img_offset_v2,
};

uint64_t _get_kernel_ramdisk_dt_offset( boot_img_hdr * hdr, uchar *partition)
{
	uint64_t size;
	uint64_t offset = 0;
	uint32_t secure_boot_offset = 0;

#ifdef CONFIG_SECURE_BOOT
	if (0 != common_raw_read(partition, (uint64_t)512, (uint64_t)0,  (u8 *) hdr)) {
		errorf("%s read error!\n", partition);
		return 0;
	}
	secure_boot_offset = get_code_offset(hdr);
	offset += secure_boot_offset;
#endif
#if (defined CONFIG_SECBOOT) && (!(defined CONFIG_VBOOT_V2))
	offset = 512;/**header of image size is 512B**/
#endif
	boot_img_offset.hdr_offset = offset;
	if (0 != common_raw_read(partition, KERNL_PAGE_SIZE, (uint64_t)offset, (char *)hdr)) {
		errorf("read %s header error!\n", partition);
		return 0;
	}

	/*image header check */
	if (0 != memcmp(hdr->magic, BOOT_MAGIC, BOOT_MAGIC_SIZE)) {
		errorf("bad boot image header, give up boot!!!!\n");
		return 0;
	}

	debug("boot_img_hdr header_version: %d\n", hdr->header_version);
	if (hdr->header_version >= ARRAY_SIZE(boot_img_offset_hdl_tbl))
		hdr->header_version = BOOT_HEADER_VERSION_ONE;
	if (!boot_img_offset_hdl_tbl[hdr->header_version](hdr, offset)) {
		return 0;
	}

#if (defined CONFIG_SPRD_SYSDUMP)
	if(enter_sysdump_flag){
		debug("Now doing sysdump ,go back here .\n");
		return 1;
	}
#endif
#if (defined CONFIG_SECBOOT) && (defined CONFIG_VBOOT_V2)
	if (0 == hdr->os_version) {
		errorf("os version should not be zero!\n");
		return 0;
	}

	os_version = hdr->os_version;

	if(config_os_version((unsigned long)&os_version, sizeof(os_version))) {
		errorf("config_os_version failed\n");
		return 0;
	}
#endif

	return 1;
}

/**
	Function for load dtbo and merge into dtb
*/
void load_and_merge_dtbo(uchar *partition, uchar *dt_start_addr)
{
	int ret = 0;
	int offset = 0;
	int count,i;
	struct dt_table_header table_header;
	struct dt_table_entry *entry=NULL;
	struct fdt_header *dtbo_header = NULL;
	u8 *dtbo_start_addr = NULL;
	u8 *dtbo_addr = NULL;
	struct boot_img_hdr_v1 hdr;
	uint64_t hdr_offset = boot_img_offset.hdr_offset + sizeof(boot_img_hdr);

	debugf("load dtbo from %s\n", partition);
	if (0 != common_raw_read(partition, sizeof(struct boot_img_hdr_v1), hdr_offset, (char *)&hdr)) {
		errorf("read %s header error!\n", partition);
		return 0;
	}

	debug("recovery_dtbo_size: 0x%x\n", hdr.recovery_dtbo_size);
	debug("recovery_dtbo_offset: 0x%x\n", hdr.recovery_dtbo_offset);
	debug("header_size: 0x%x\n", hdr.header_size);

	/* read dtbo table header */
	if (0 != common_raw_read(partition, (uint64_t)sizeof(struct dt_table_header), hdr.recovery_dtbo_offset, &table_header)) {
		errorf("read dtbo fail\n");
		goto error;
	}

	/* dtbo image header check */
	if (be32_to_cpu(table_header.magic) != DT_TABLE_MAGIC) {
		errorf("invalid dtbo partition\n");
		goto error;
	}

	if (be32_to_cpu(table_header.total_size) == 0)
		goto error;

	/* dtbo alloc memory*/
	dtbo_start_addr = malloc(be32_to_cpu(table_header.total_size));
	if (NULL == dtbo_start_addr) {
		errorf("malloc size=%dfor dt entrys fail\n", be32_to_cpu(table_header.total_size));
		goto error;
	}

	/* load dtbo image */
	if (0 != common_raw_read(partition, (uint64_t)be32_to_cpu(table_header.total_size), hdr.recovery_dtbo_offset, dtbo_start_addr)) {
		errorf("read dtbo fail\n");
		goto error;
	}

	if (be32_to_cpu(table_header.dt_entry_count) == 0) {
		errorf("not found dtbo !\n");
		goto error;
	}

	count = be32_to_cpu(table_header.dt_entry_count);
	entry = (struct dt_table_entry *)(dtbo_start_addr +
				be32_to_cpu(table_header.dt_entries_offset));
	if (NULL == entry) {
		goto error;
	}

	for (i = 0; i < count; i++) {
		offset = be32_to_cpu(entry->dt_offset);
		debugf("%s : offset = 0x%x size=0x%x\n"
			,__func__, offset, be32_to_cpu(entry->dt_size));

		dtbo_addr = dtbo_start_addr + offset;
		dtbo_header = (struct fdt_header *)dtbo_addr;
		if (fdt_check_header(dtbo_header) != 0) {
			errorf("image is not a fdt\n");
			goto error;
		}

		ret = fdt_overlay_apply(dt_start_addr, dtbo_addr);
		if (ret) {
			errorf("fdt_overlay_apply(): %s\n", fdt_strerror(ret));
			goto error;
		}
		dtbo_addr = NULL;
		entry++;
	}

error:
	if (NULL != dtbo_start_addr) {
		free(dtbo_start_addr);
		dtbo_start_addr = NULL;
	}
}

/**
	Function for do memory defragment and load dtb
*/
void merge_dtbo(uchar *dt_start_addr)
{
#ifdef CONFIG_OF_LIBFDT_OVERLAY
	struct dt_table_header *table_header;
	struct dt_table_entry *entry=NULL;
	struct dt_table_entry *cur_entry=NULL;
	struct fdt_header dtbo_header;
	uint8_t data[64];
	u8 *dtbo_addr = NULL;
	int offset = 0;
	int ret = 0;
	int count,size,i;

	if (0 != common_raw_read("dtbo", sizeof(*table_header), 0, &data[0])) {
		errorf("read dtbo fail\n");
		goto error;
	}
	table_header = (struct dt_table_header *)data;
	if (be32_to_cpu(table_header->magic) != DT_TABLE_MAGIC) {
		errorf("invalid dtbo partition\n");
		goto error;
	}
	if (be32_to_cpu(table_header->dt_entry_count)==0)
		goto error;
	size =be32_to_cpu(table_header->dt_entry_size) *
		 be32_to_cpu(table_header->dt_entry_count);
	entry = malloc(size);
	if (NULL == entry) {
		errorf("malloc size=%dfor dt entrys fail\n",size);
		goto error;
	}
	offset = be32_to_cpu(table_header->dt_entries_offset);
	count = be32_to_cpu(table_header->dt_entry_count);

	if (0 != common_raw_read("dtbo", size, offset, entry)) {
		errorf("read dt entries fail\n");
		goto error;
	}

	cur_entry = entry;
	for (i=0; i < count; i++) {
		printf("%s : offset = 0x%x size=0x%x\n"
			,__func__, offset, be32_to_cpu(cur_entry->dt_size));

		offset = be32_to_cpu(cur_entry->dt_offset);
		size = sizeof(struct fdt_header);
		if (0 != common_raw_read("dtbo", size, offset, &dtbo_header)) {
			errorf("read dtbo fail\n");
			goto error;
		}

		if (fdt_check_header(&dtbo_header) != 0) {
			errorf("image is not a fdt\n");
			goto error;
		}
		size = fdt_totalsize(&dtbo_header);
		dtbo_addr = malloc(size);
		if (NULL == dtbo_addr) {
			errorf("malloc size %d for dtbo fail\n", size);
			goto error;
		}
		if (0 != common_raw_read("dtbo", size, offset, dtbo_addr)) {
			errorf("read dtbo fail\n");
			goto error;
		}
		ret = fdt_overlay_apply(dt_start_addr, dtbo_addr);
		if (ret) {
			errorf("fdt_overlay_apply(): %s\n", fdt_strerror(ret));
			goto error;
		}
		free(dtbo_addr);
		dtbo_addr = NULL;
		cur_entry++;
	}
error:
	if (NULL != entry)
		free(entry);
	if (NULL != dtbo_addr)
		free(dtbo_addr);
#endif
}
int load_fixup_dt_img(uchar *partition, uchar **dt_start_addr) {
	u8 *fdt_blob = NULL;
	struct dt_table table;
	char * header = NULL;
	struct dt_entry *dt_entry_ptr;
	uint64_t size = 0;
	uint64_t fdt_size = 0;
	uint64_t fdt_offset = 0;
	int ret = -1;
	uchar *dt_end_addr;
	uchar *ramdisk_adr;
	uint32_t auto_mem_num = 0;
	struct boot_img_hdr *hdr;
	struct boot_img_hdr_v2 *hdr_v2 = NULL;

	hdr = get_boot_img_hdr();
	if (hdr) {
		hdr_v2 = get_boot_img_hdr_v2(hdr);
	}

	/* if Android V2, read fdt directly */
	if (!hdr_v2 || !((BOOT_HEADER_VERSION_TWO == hdr->header_version)
			&& (hdr_v2->dtb_addr && hdr_v2->dtb_size))) {
		size = sizeof(struct dt_table);
		if (0 != common_raw_read(partition, size, (uint64_t)(boot_img_offset.dt_offset), &table)) {
			errorf("read dt image table header fail\n");
			goto error;
		}

		/* Validate the device tree table header */
		if((table.magic != DEV_TREE_MAGIC) || (table.version != DEV_TREE_VERSION)) {
			errorf("Cannot validate Device Tree Table(magic%x,version%d) on %s\n",
				table.magic, table.version, partition);
			goto error;
		}

		size = sizeof(struct dt_table) + sizeof(struct dt_entry) * table.num_entries;
		header = (char *)malloc(size);
		if (NULL == header) {
			errorf("malloc size %d for dt header fail\n", size);
			goto error;
		}
		if (0 != common_raw_read(partition, size,  (uint64_t)(boot_img_offset.dt_offset), header)) {
			errorf("read dt image table and entries header fail\n");
			goto error;
		}

		/* Calculate the offset of device tree within device tree table */
		dt_entry_ptr = dev_tree_get_entry_ptr((struct dt_table *)header);
		if(NULL == dt_entry_ptr) {
			errorf("Getting device tree address failed\n");
			goto error;
		}

		size = dt_entry_ptr->size;
		fdt_offset = boot_img_offset.dt_offset + dt_entry_ptr->offset;
	} else {
		fdt_offset = boot_img_offset.dt_offset;
		size = hdr_v2->dtb_size;
		if (fdt_offset != hdr_v2->dtb_addr)
			debugf("Warning: dtb addr 0x%llx on boot img hdr\n", hdr_v2->dtb_addr);
		debugf("v2 header fdt_offset:0x%llx size:0x%llx\n", fdt_offset, size);
	}
	/* malloc reserve FDT_ADD_SIZE for fdt fixup */
	fdt_blob = malloc(size + FDT_ADD_SIZE);
	debugf("malloc size for fdt: 0x%lx\n", size + FDT_ADD_SIZE);
	if (0 != common_raw_read(partition, (uint64_t)size, (uint64_t)fdt_offset, (char *)fdt_blob)) {
		errorf("dt entry size read error!\n");
		goto error;
	}

	if (fdt_check_header(fdt_blob) != 0) {
		errorf("image is not a fdt\n");
		goto error;
	}
	fdt_size = fdt_totalsize(fdt_blob);
	ret = fdt_open_into(fdt_blob, fdt_blob, fdt_size + FDT_ADD_SIZE);
	if (0 != ret) {
		errorf("libfdt fdt_open_into(): %s\n", fdt_strerror(ret));
		goto error;
	}
#ifdef CONFIG_X86
	fdt_fixup_all_x86(fdt_blob);
#else
	fdt_fixup_all(fdt_blob);
#endif
	ret = fdt_fixup_memory_region(fdt_blob, &auto_mem_num);
	if(ret < 0)
		goto error;
	fdt_size = fdt_totalsize(fdt_blob);
	size = PAD_SIZE(fdt_size, KERNL_PAGE_SIZE);
	if (0 == ret && 0 != auto_mem_num) {
		if(0 != get_dt_end_addr(fdt_blob , &dt_end_addr))
			goto end;
		*dt_start_addr = dt_end_addr - size;
	}
end:
	memcpy(*dt_start_addr, fdt_blob, size);
	ret = 0;
error:
	if (NULL != header)
		free(header);
	if (NULL != fdt_blob)
		free(fdt_blob);
	return ret;
}

int _boot_load_kernel_ramdisk_image(char *bootmode, boot_img_hdr * hdr, uchar **dt_addr )
{
	uchar *partition = NULL;
	uchar *dtb_partname = NULL;
	uint64_t size;
	uchar *dt_img_adr;
	char  *boot_mode_type_str;
	uchar *ramdisk_addr = 0;
	uint64_t fdt_size = 0;
	int ret;

	if (0 == memcmp(bootmode, RECOVERY_PART, strlen(RECOVERY_PART))) {
		partition = "recovery";
		debugf("enter recovery mode!\n");
	} else {
		partition = "boot";
		debugf("enter boot mode!\n");
	}

	if(0 == _get_kernel_ramdisk_dt_offset(hdr, partition))
		return 0;
	debugf("!!! load kernel partition %s: \n!!! kernel (0x%x:0x%x)\n!!! ramdisk(0x%x:0x%x) dt=%d\n",
		partition,hdr->kernel_addr,hdr->kernel_size,hdr->ramdisk_addr,
		hdr->ramdisk_size, hdr->dt_size);
	/* get kernel image size */
	size = PAD_SIZE(hdr->kernel_size, KERNL_PAGE_SIZE);
	if (0 == size) {
		errorf("kernel image should not be zero!\n");
		return 0;
	}

	/* read kernel image */
	if (0 != common_raw_read(partition, size, (uint64_t)(boot_img_offset.kernel_offset) , (char *)KERNEL_ADR)) {
		errorf("%s kernel read error!\n", partition);
		return 0;
	}
	debugf("%s kernel read OK,size=0x%llx, locate to 0x%lx \n", partition, size, (ulong)KERNEL_ADR);

	if (hdr->ramdisk_size) {	//androidp recovery mode need load ramdisk
		ramdisk_addr = RAMDISK_ADR;
		/* get ramdisk image size */
		size = PAD_SIZE(hdr->ramdisk_size, KERNL_PAGE_SIZE);
		if (0 == size) {
			errorf("ramdisk image size should not be zero\n");
			return 0;
		}

	}
/*read dt image*/
#if defined(CONFIG_SEPARATE_DT)
	if (!_boot_load_separate_dt())
		return 0;
	fdt_size = fdt_totalsize(DT_ADR);
	ret = fdt_open_into(DT_ADR, DT_ADR, fdt_size + FDT_ADD_SIZE);
	if (0 != ret)
		errorf("libfdt fdt_open_into(): %s\n", fdt_strerror(ret));
	fdt_fixup_all((uchar *)DT_ADR);
#else
	if (BOOT_HEADER_VERSION_ONE == hdr->header_version) {
		/* fixbug1007672 */
		struct boot_img_hdr_v2 *hdr_v2 = get_boot_img_hdr_v2(hdr);
		if (hdr_v2->dtb_size && hdr_v2->dtb_addr) {
			dtb_partname = partition;
			boot_img_offset.dt_offset = hdr_v2->dtb_addr;
		} else if (0 == common_raw_read("dtb", 10, 0, (char *)DT_ADR)) {
			dtb_partname = "dtb";
			boot_img_offset.dt_offset = 0;
		} else {
			dtb_partname = partition;
		}
	} else {
		dtb_partname = partition;
	}

	/* for memory defragment, dr_addr and ramdisk_adr is allocated dynamically*/
	if (0 == load_fixup_dt_img(dtb_partname, dt_addr)) {
		if (DT_ADR != *dt_addr) {
			debugf("allocate dt_addr:%lx \n", *dt_addr);
			/*allocate  ramdisk addr */
			ramdisk_addr = *dt_addr - size;
		} else {
			debugf(" use default value : DT_ADDR & RAMDISK_ADR\n");
		}
	} else {
		errorf("load dt error!\n");
		return 0;
	}
#ifdef CONFIG_OF_LIBFDT_OVERLAY
	if (BOOT_HEADER_VERSION_ONE == hdr->header_version) {
		if (0 == memcmp(bootmode, RECOVERY_PART, strlen(RECOVERY_PART))) {
			load_and_merge_dtbo(partition, *dt_addr);
		} else {
			merge_dtbo(*dt_addr);
		}
	} else if (BOOT_HEADER_VERSION_TWO == hdr->header_version) {
		if (boot_img_offset.recovery_dtbo_offset)
			load_and_merge_dtbo(partition, *dt_addr);
		else
			merge_dtbo(*dt_addr);
	}
#endif
#endif

	if( hdr->ramdisk_size ) {
		fdt_initrd_norsvmem(*dt_addr, ramdisk_addr, ramdisk_addr + hdr->ramdisk_size, 1);
		if (0 == size) {
			errorf("ramdisk image size should not be zero\n");
			return 0;
		}
		/*read ramdisk image */
		if (0 != common_raw_read(partition, size, (uint64_t)(boot_img_offset.ramdisk_offset), ramdisk_addr)) {
			errorf("%s ramdisk read error!\n", partition);
			return 0;
		}
		debugf("%s ramdisk read OK,size=0x%llx, locate to 0x%lx \n", partition, size, ramdisk_addr);

		boot_mode_type_str = getenv("bootmode");
		if (NULL != boot_mode_type_str)
		{
			if(!strncmp(boot_mode_type_str, "sprdisk", 7)) {
				int ramdisk_size;
				ramdisk_size = boot_sprdisk(0, ramdisk_addr);
				if (ramdisk_size > 0) {
					hdr->ramdisk_size = ramdisk_size;
					if (RAMDISK_ADR != ramdisk_addr) {
						/* get ramdisk size , calculate addr, so we can have enough room for sprdisk ramdisk */
						size = PAD_SIZE(hdr->ramdisk_size, KERNL_PAGE_SIZE);
						ramdisk_addr = *dt_addr - size;
						hdr->ramdisk_addr = ramdisk_addr;
					}
					fdt_initrd_norsvmem(*dt_addr, ramdisk_addr, ramdisk_addr+hdr->ramdisk_size , 1);
					boot_sprdisk(ramdisk_size, ramdisk_addr);
				} else {
					errorf("%s, sprdisk mode failure!\n", __FUNCTION__);
				}
				return 1;
			}
		}


#ifdef CONFIG_SDRAMDISK
		{
			int sd_ramdisk_size = 0;
#ifdef WDSP_ADR
			size = WDSP_ADR - RAMDISK_ADR;
#else
			size = TDDSP_ADR - RAMDISK_ADR;
#endif
			if (size > 0)
				_sd_fat_mount();
				sd_ramdisk_size = load_sd_ramdisk((void *) RAMDISK_ADR, size);
			if (sd_ramdisk_size > 0)
				hdr->ramdisk_size = sd_ramdisk_size;
		}
#endif
	}
	return 1;
}

#ifdef CONFIG_SEPARATE_DT
int _boot_load_separate_dt(void)
{
	struct dt_table table;
	char * header = NULL;
	struct dt_entry *dt_entry_ptr;
	uint32_t secure_boot_offset = 0;
	uint64_t offset = 0;
	uint64_t size = 0;

#ifdef CONFIG_SECURE_BOOT
	if (0 != common_raw_read("dt", EMMC_SECTOR_SIZE, (uint64_t)0, &table)) {
		errorf("dt read error!\n");
		free(table);
		return 0;
	}
	secure_boot_offset = get_code_offset(table);
	offset += secure_boot_offset;
#endif
#ifdef CONFIG_SECBOOT
	offset = 512;/**header of image size is 512B**/
#endif

	size = sizeof(struct dt_table);
	if (0 != common_raw_read(DT_PART, size, offset, &table)) {
		errorf("read dt image table header fail\n");
		goto fail;
	}

	/* Validate the device tree table header */
	if((table.magic != DEV_TREE_MAGIC) || (table.version != DEV_TREE_VERSION)) {
		errorf("Cannot validate Device Tree Table \n");
		goto fail;
	}

	size = sizeof(struct dt_table) + sizeof(struct dt_entry) * table.num_entries;
	header = (char *)malloc(size);
	if (NULL == header) {
		errorf("malloc size %d for dt header fail\n", size);
		goto fail;
	}
	if (0 != common_raw_read(DT_PART, size, offset, header)) {
		errorf("read dt image table and entries header fail\n");
		goto fail;
	}

	/* Calculate the offset of device tree within device tree table */
	dt_entry_ptr = dev_tree_get_entry_ptr((struct dt_table *)header);
	if(NULL == dt_entry_ptr) {
		errorf("Getting device tree address failed\n");
		goto fail;
	}

	size = dt_entry_ptr->size;
	offset += dt_entry_ptr->offset;
	if (0 != common_raw_read(DT_PART, size, offset, (char *)DT_ADR)) {
		errorf("dt entry size 0x%x offset 0x%x read error!\n", size, offset);
		goto fail;
	}

	debugf("load separate DT OK,size=0x%llx, locate to 0x%lx \n", size, (ulong)DT_ADR);
	free(header);
	return 1;

fail:
	if (NULL != header)
		free(header);
	return 0;
}
#endif

/*TODO*/
#ifdef CONFIG_SECURE_BOOT
int secure_verify_partition(block_dev_desc_t * dev, uchar * partition_name, void *ram_addr)
{
	int ret = 0;
	int size;
	disk_partition_t info;

	if (get_partition_info_by_name(dev, partition_name, &info)) {
		errorf("verify get partition %s info failed!\n", partition_name);
		ret = 1;
	}
	size = info.size * EMMC_SECTOR_SIZE;
	debugf("%s=%x  =%x\n", partition_name, info.size, size);
	_boot_partition_read(dev, partition_name, 0, size, (uint8_t *) ram_addr);
	secure_verify("uboot", (uint8_t *) ram_addr, 0);
	return ret;
}
#endif

#ifdef CONFIG_VBOOT_V2
int secure_get_partition_size(uchar * partition_name, uint64_t * size)
{
	int ret = 0;

	ret = get_img_partition_size(partition_name, size);

	debugf("partition:%s,size:0x%llx\n", partition_name, *size);
	return ret;
}
#endif

#ifdef CONFIG_ZEBU
void vlx_nand_boot_zebu(char *kernel_pname, int backlight_set, int lcd_enable)
{
	uint32_t size = DT_SIZE;
	size = (size+(KERNL_PAGE_SIZE - 1)) & (~(KERNL_PAGE_SIZE - 1));
	uint64_t dt_img_adr = RAMDISK_ADR - size - KERNL_PAGE_SIZE;
	debugf("%s,dt_img_addr:%p\n",__func__,dt_img_adr);

	/* copy kernel/dt/ramdisk/sml from jointRAM to InterlaceRAM */
#ifdef CONFIG_INTERLACE_RAM_COPY
	memcpy(KERNEL_ADR,SRC_KERNEL_ADR,KERNEL_SIZE);
	memcpy(RAMDISK_ADR,SRC_RAMDISK_ADR,RAMDISK_SIZE);
	memcpy(dt_img_adr,SRC_DT_ADR,DT_SIZE);
	debugf("copy kernel to interlace RAM done\n");
#endif

	if (load_dtb((uint64_t)DT_ADR,(void*)dt_img_adr)) {
		debugf("dt load error!\n");
		return;
	}

	fdt_fixup_all((uchar *)DT_ADR);
	uint32_t r_size = RAMDISK_SIZE;
	r_size = (r_size+(KERNL_PAGE_SIZE - 1)) & (~(KERNL_PAGE_SIZE - 1));
	fdt_initrd_norsvmem((uchar *)DT_ADR, RAMDISK_ADR, RAMDISK_ADR+r_size, 1);

	vlx_entry(DT_ADR);
}
#endif

#ifdef CONFIG_SECBOOT
int loader_binding_data_set(void)
{
	/*set device state*/
	get_lock_status();

	if(g_DeviceStatus == VBOOT_STATUS_LOCK){
		debugf("INFO: LOCK FLAG IS : LOCK!!!\n");
	}else if(g_DeviceStatus == VBOOT_STATUS_UNLOCK){
		debugf("INFO: LOCK FLAG IS : UNLOCK!!!\n");
		lcd_printf("INFO: LOCK FLAG IS : UNLOCK!!!\n");
	}

	return 0;
}

int loader_binding_state_get(void)
{
	if(g_DeviceStatus == 0xFFFFFFFF) {
		debugf("Warning: get device state error: state is not initiated!\n");
		return -1;
	}

	return g_DeviceStatus;
}

int sprd_sec_verify_lockstatus(unsigned char *lockstatus, unsigned int status_len)
{
#ifndef CONFIG_VBOOT_V2
	return -1; /*default status : locked*/
#else
	uint8_t data_buffer[128] __attribute__((aligned(4096)));
	uint8_t * v_lock_state_ret = (uint8_t *)data_buffer + PDT_INFO_LOCK_FLAG_MAX_SIZE;

	uint32_t ret;

	if(!lockstatus || !status_len || (status_len > PDT_INFO_LOCK_FLAG_MAX_SIZE))
	{
		debugf("para error. \n");
		return -1;
	}

	memset(data_buffer, 0, sizeof(data_buffer));
	memcpy(data_buffer, lockstatus, status_len);

#ifdef CONFIG_VBOOT_DUMP
	do_hex_dump(data_buffer, status_len);
#endif

	ret = uboot_verify_lockstatus(data_buffer, sizeof(data_buffer));

	if(*v_lock_state_ret == VBOOT_STATUS_LOCK)
	{
		//debugf("verify unlock status failed. \n");
		ret = -1;
	}

	return ret;
#endif
}

void pass_pubkey_to_tos(void)
{
	return;
#if 0
	uint8_t *lockptr;
	int dev_lock;
	uint8_t data_buffer[512] __attribute__((aligned(4096)));

	struct smc_param param;
	int ret;

	data_buffer[0] = 0x12;
	data_buffer[1] = 0x34;
	data_buffer[2] = 0x56;
	data_buffer[3] = 0x78;
	//mem_info mi __attribute__((aligned(4096)));

	dev_lock = loader_binding_state_get();
	if (dev_lock < 0) {
		debug("has not gotten dev state!\n");
		return;
	}

	param.a0 = TEESMC_SIPCALL_WITH_ARG;
	param.a1 = FUNCTYPE_SET_BINDING_DATA;
	param.a2 = data_buffer;
	param.a3 = sizeof(data_buffer);
	tee_smc_call(&param);
	ret = param.a0;
#endif
}
#endif

#if defined (CONFIG_SECBOOT)
int take_action_with_vbootret(void)
{
	int sec_time_count = 60;

	switch(g_verifiedbootstate) {
		case v_state_red:
			debugf("WARNNING: Oem Key & User Key Verify Failed!!!\n");
			while(sec_time_count) {
				mdelay(100);
				sec_time_count --;
			}
			power_down_devices(0);
			break;

		case v_state_yellow:
			debugf("WARNNING: USER KEY VERIFY SUCCESS!!!\n");
			break;

		case v_state_green:
			debugf("WARNNING: OEM KEY VERIFY SUCCESS!!!\n");
			break;

		case v_state_orange:
			debugf("WARNNING: LOCK FLAG IS : UNLOCK, SKIP VERIFY!!!\n");
			lcd_printf("WARNNING: LOCK FLAG IS : UNLOCK, SKIP VERIFY!!!\n");
			break;

		default:
			debugf("WARNNING: VERIFY RESULT UNKNOWN!!!\n");
			break;
	}

	return 0;
}
#endif
// add for SOTER start
#if defined (CONFIG_CHIP_UID)
static u32 blocks[2] __attribute__((aligned(4096)));

void pass_chip_uid_to_tos()
{
    //u32 blocks[2]/* = {0} */__attribute__((aligned(4096)));
    //u32 *blocks = gd->verify_base;
    smc_param *param;

    printf("pass_chip_uid_to_tos()... sizeof(blocks)=%d\n", sizeof(blocks));
    memset(blocks, 0, sizeof(blocks));
#if defined (CONFIG_SPRD_UID)
    blocks[1] = sprd_efuse_double_read(UID_START, UID_DOUBLE);
    blocks[0] = sprd_efuse_double_read(UID_END, UID_DOUBLE);
    param = tee_common_call(FUNCTYPE_SET_CHIP_UID, (uint32_t)blocks, sizeof(u32)*2);
    printf("blks:0x%08x 0x%08x, result: 0x%x \n", blocks[0], blocks[1], param->a0);
#elif defined (CONFIG_X86)
    // implements if nessary
    printf("mocor CONFIG_X86\n");
#else
    blocks[0]= sprd_ap_efuse_read(0);
    blocks[1]= sprd_ap_efuse_read(1);
    param = tee_common_call(FUNCTYPE_SET_CHIP_UID, (uint32_t)blocks, sizeof(u32)*2);
    printf("blks:0x%08x 0x%08x, result: 0x%x \n", blocks[0], blocks[1], param->a0);
#endif
    return;
}
#endif
// add for SOTER end

uint32_t uboot_start_time;
void vlx_nand_boot(char *kernel_pname, int backlight_set, int lcd_enable)
{
	boot_img_hdr *hdr = (void *)raw_header;
	char *mode_ptr = NULL;
	uchar *partition = NULL;
	int i = 0;
	int j = 0;
	int ret = 0;
	uchar *dt_adr = DT_ADR;
	uint32_t lcd_init_time;
	uint32_t backlight_on_time;
	uint32_t uboot_consume_time;

#ifdef CONFIG_SOC_IWHALE2
	aon_lpc_config();
#endif
	wakeup_source_enable();
	ap_clk_doze_enable();

#ifdef CONFIG_SPLASH_SCREEN
	lcd_init_time = SCI_GetTickCount();
	printf("lcd start init time:%dms\n", lcd_init_time);
	if(lcd_enable) {
		extern void lcd_enable(void);
		debug("[LCD] Drawing the logo...\n");
		drv_lcd_init();
		lcd_splash(LOGO_PART);
		lcd_enable();
	}
#ifdef CONFIG_SPRD_SOC_SP9853I
	else {
		/*if no lcd in cali mode, turn off the cam_eb bit*/
		char  *boot_mode_type_str;

		boot_mode_type_str = getenv("bootmode");
		if(!strncmp(boot_mode_type_str, "cali", 4)) {
			sci_glb_clr(REG_AON_APB_APB_EB1, BIT_AON_APB_AON_CAM_EB);
		}

	}
#endif
	set_backlight(backlight_set);
	backlight_on_time = SCI_GetTickCount();
	lcd_init_time= backlight_on_time - lcd_init_time;
	uboot_consume_time = backlight_on_time - uboot_start_time;
	printf("uboot consume time:%dms, lcd init consume:%dms, backlight on time:%dms \n", \
		uboot_consume_time, lcd_init_time, backlight_on_time);

#endif
	set_vibrator(0);

#if 0
#ifdef CONFIG_SECBOOT
	//init fastboot lock data
	init_fblockflag();
#endif
#endif

#if (defined CONFIG_X86) && (defined CONFIG_MOBILEVISOR) && (defined CONFIG_SOC_IWHALE2) && (defined CONFIG_SECBOOT)
	tos_status_check();
#endif

#if (defined CONFIG_X86) && (defined CONFIG_MOBILEVISOR) && (defined CONFIG_SPRD_SOC_SP9853I)
    tos_start_notify();
#endif

#if defined(CONFIG_SECURE_BOOT)||defined(CONFIG_SECBOOT)
	if (0 == memcmp(kernel_pname, RECOVERY_PART, strlen(RECOVERY_PART))) {
		partition = "recovery";
	} else {
		partition = "boot";
	}
#if defined (CONFIG_SECURE_BOOT)
	secure_verify_partition(dev, partition, KERNEL_ADR);
#endif

#if defined (CONFIG_SECBOOT)
	/***secboot only 3 steps***/
	/***secboot 1st step***/
	secboot_init(partition);

	/***secboot 2nd step***/
	/*set v-boot binding data eg:lock status*/
	loader_binding_data_set();
	pass_pubkey_to_tos();

	vboot_secure_process_flow(partition);
#endif
#endif

		/*load required image which config in table */
		i = 0;
#ifdef CONFIG_ARM7_RAM_ACTIVE
#ifdef CONFIG_SOC_IWHALE2
		/*Just for iwhale2 bringup --from Sheng.Zhu advice*/
		ag_tg_ldsp_hold();
#endif
		pmic_arm7_RAM_active();
#endif

	while (s_boot_image_table[i]) {
		j = 0;
		while (s_boot_image_table[i][j].partition) {
			_boot_load_required_image(s_boot_image_table[i][j]);
			j++;
		}
		i++;
	}

extern unsigned int g_charger_mode;
#if defined(CONFIG_KERNEL_BOOT_CP)
	if(g_charger_mode) {
        	boot_image_required_t pm_image = {"pm_sys", NULL, DFS_SIZE, DFS_ADDR};
		_boot_load_required_image(pm_image);
	}
#endif

#if !defined(CONFIG_KERNEL_BOOT_CP) && defined(CONFIG_MEM_LAYOUT_DECOUPLING)
	extern boot_image_required_t *get_cp_load_table(void);
	do {
		boot_image_required_t *cp_load_table = NULL;
		cp_load_table = get_cp_load_table();
		printf("cp_load_table = 0x%p\n", cp_load_table);
		if (NULL != cp_load_table) {
			for(i = 0; cp_load_table[i].size > 0; i++) {
				_boot_load_required_image(cp_load_table[i]);
			}
		}
	} while(0);
#endif

#if defined (CONFIG_SECBOOT)
		secboot_secure_process_flow(partition,0,0,(char *)gd->verify_base);
		//things to do refer to verify ret
		take_action_with_vbootret();

		if(set_root_of_trust(root_of_trust_str, ROOT_OF_TRUST_MAXSIZE)) {
			printf("set_root_of_trust failed.\n");
		} else {
			printf("set_root_of_trust succeeded.\n");
		}
#endif

#ifdef OTA_BACKUP_MISC_RECOVERY
	ret = memcmp(kernel_pname, RECOVERY_PART, strlen(RECOVERY_PART));
	if ((ret != 0) || (boot_load_recovery_in_sd(hdr) != 0))
		if (!_boot_load_kernel_ramdisk_image(kernel_pname, hdr, &dt_adr))
			ret = -1;
#else
	/*loader kernel and ramdisk*/
	if (!_boot_load_kernel_ramdisk_image(kernel_pname, hdr, &dt_adr))
		ret = -1;
#endif

	if (-1 == ret)
		return;

#ifdef PROJECT_SEC_CM4
	if(g_charger_mode)
	{
        	boot_image_required_t pm_image = {"pm_sys", NULL, DFS_SIZE, DFS_ADDR};

		/* load sp ddr boot */
		load_sp_boot_code();

		/***secboot 2nd step***/
		vboot_secure_process_flow_cm4(pm_image.partition);
        }
#endif

#if defined (CONFIG_SECBOOT)
	/***secboot 3rd step***/
	secboot_terminal();
#endif

	// add for SOTER start
#if defined (CONFIG_CHIP_UID)
	pass_chip_uid_to_tos();
#endif
	 // add for SOTER end

//#if defined(TOS_TRUSTY) && defined(CONFIG_EMMC_BOOT) && defined(CONFIG_SPRD_RPMB)

#if defined(CONFIG_SPRD_RPMB)
	if(gd->boot_device == BOOT_DEVICE_EMMC) {
		uboot_set_rpmb_size();
		uboot_is_wr_rpmb_key();
		uboot_check_rpmb_key();
	}
#endif

#ifdef CONFIG_TEE_FIREWALL
	//fdt_reserved_mem_multimedia_parse(dt_adr);
#endif

#if (defined CONFIG_X86) && (defined CONFIG_MOBILEVISOR) && (defined CONFIG_SPRD_SOC_SP9853I)
    tos_end_notify();
#endif

#ifdef  CONFIG_SPRD_HW_I2C
	i2c_dvfs_hwchn_init();
#endif

	vlx_entry(dt_adr);
}
