#ifndef _LOADER_COMMON_H_
#define _LOADER_COMMON_H_

#include <common.h>
#include <linux/types.h>
//#include <asm/arch/bits.h>
#include <linux/string.h>
#include <android_bootimg.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/ubi.h>
//#include <linux/crc32b.h>
#include <linux/mtd/nand.h>
#include <nand.h>
#include <environment.h>
#include <jffs2/jffs2.h>
#include <boot_mode.h>
#include <malloc.h>
#include <ubi_uboot.h>
#ifdef CONFIG_MTD_PARTITIONS
#include <linux/mtd/partitions.h>
#endif
#include <fdtdec.h>

#define COMMAND_LINE_OFFSET	0x9000 /*for x86 linux startup*/
extern unsigned char raw_header[8192];

#define TRUE   1		/* Boolean true value. */
#define FALSE  0		/* Boolean false value. */

#define SPL_PART "spl"
#define LOGO_PART "logo"
#define CHARGER_LOGO_PART "chargelogo"
#define BOOT_PART "boot"
#define RECOVERY_PART "recovery"
#define FACTORY_PART "prodnv"
#define PRODUCTINFO_FILE_PATITION  "miscdata"
#define DT_PART "dt"

/*FDT_ADD_SIZE used to describe the size of the new bootargs items*/

/*include lcd id, lcd base, etc*/
#define FDT_ADD_SIZE (0x20000)

#define TRUSTRAM_SIZE 0x32000

#define SIMLOCK_SIZE   1024

#define NV_HEAD_MAGIC	(0x00004e56)
#define NV_VERSION		(101)
#define NV_HEAD_LEN	(512)

#define MAX_SN_LEN 			(24)
#define SP09_MAX_SN_LEN			MAX_SN_LEN
#define SP09_MAX_STATION_NUM		(15)
#define SP09_MAX_STATION_NAME_LEN	(10)
#define SP09_SPPH_MAGIC_NUMBER          (0X53503039)	// "SP09"
#define SP09_MAX_LAST_DESCRIPTION_LEN   (32)

/*for verified boot*/
typedef enum verified_state{
	v_state_green = 0,
	v_state_yellow = 1,
	v_state_orange = 2,
	v_state_red = 3
}enVerifiedState;

typedef enum verified_ret{
	v_state_ok = 0,
	v_state_failed = 1,
	v_state_initial = 10
}enVerifiedRet;

typedef struct _tagSP09_PHASE_CHECK {
	uint32_t Magic;	// "SP09"
	char SN1[SP09_MAX_SN_LEN];	// SN , SN_LEN=24
	char SN2[SP09_MAX_SN_LEN];	// add for Mobile
	int StationNum;		// the test station number of the testing
	char StationName[SP09_MAX_STATION_NUM][SP09_MAX_STATION_NAME_LEN];
	unsigned char Reserved[13];	//
	unsigned char SignFlag;
	char szLastFailDescription[SP09_MAX_LAST_DESCRIPTION_LEN];
	unsigned short iTestSign;	// Bit0~Bit14 ---> station0~station 14
	//if tested. 0: tested, 1: not tested
	unsigned short iItem;	// part1: Bit0~ Bit_14 indicate test Station,1 : Pass,

} SP09_PHASE_CHECK_T, *LPSP09_PHASE_CHECK_T;

/*add the struct add define to support the sp15*/
#define SP15_MAX_SN_LEN 	        (64)
#define SP15_MAX_STATION_NUM		(20)
#define SP15_MAX_STATION_NAME_LEN	(15)
#define SP15_SPPH_MAGIC_NUMBER          (0X53503135)	// "SP15"
#define SP15_MAX_LAST_DESCRIPTION_LEN   (32)

typedef struct _tagSP15_PHASE_CHECK {
    uint32_t Magic;	// "SP15"
    char SN1[SP15_MAX_SN_LEN];	// SN , SN_LEN=64
    char SN2[SP15_MAX_SN_LEN];	// add for Mobile
    int StationNum;		// the test station number of the testing
    char StationName[SP15_MAX_STATION_NUM][SP15_MAX_STATION_NAME_LEN];
    unsigned char Reserved[13];	//
    unsigned char SignFlag;
    char szLastFailDescription[SP15_MAX_LAST_DESCRIPTION_LEN];
    unsigned long iTestSign;	// Bit0~Bit14 ---> station0~station 14
    //if tested. 0: tested, 1: not tested
    unsigned long iItem;	// part1: Bit0~ Bit_14 indicate test Station,1 : Pass,

} SP15_PHASE_CHECK_T, *LPSP15_PHASE_CHECK_T;

typedef struct boot_image_required {
	uchar *partition;	//partition name record on disk
	uchar *bak_partition;	//if no backup partition, set NULL
	uint64_t size;	//partition size to be read
	char *mem_addr;	//target memory addr
} boot_image_required_t;

typedef struct _NV_HEADER {
	uint32_t magic;
	uint32_t len;
	uint32_t checksum;
	uint32_t version;
} nv_header_t;

#ifdef CONFIG_SP_DDR_BOOT
typedef struct sp_ddr_boot {
	uint32_t *bootcode;
	uint32_t bootcode_word_num;
	fdt_addr_t sp_iram_addr;
	fdt_addr_t sp_ddr_addr;
	fdt_size_t sp_ddr_img_size;
} sp_ddr_boot_t;
#endif

void set_vibrator(int on);
void vibrator_hw_init(void);
void vlx_entry(uchar *dt_adr);
#ifdef CONFIG_SPLASH_SCREEN
void set_backlight(uint32_t value);
#else
#define set_backlight
#endif

int autodloader_mainhandler(void);

extern char* get_calibration_parameter(void);
extern bool is_calibration_by_uart(void);
#if defined (CONFIG_SECBOOT)
extern int set_lock_status(unsigned int flag);
extern unsigned int get_lock_status(void);
extern int uboot_encrypt_data(uint64_t start_addr, uint64_t lenth);
#endif

#ifdef CONFIG_SP_DDR_BOOT
void *get_sp_ddr_boot_info(void);
#endif

#endif /* _LOADER_COMMON_H_ */
