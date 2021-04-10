

#ifndef __SEC_COMMON_H
#define __SEC_COMMON_H

#include<secureboot/sprdsec_header.h>
#include<crypto/sprdrsa.h>
#include<secure_efuse.h>
#include<asm/arch/chip_releted_def.h>
#include<sprd_imgversion.h>

#define VBOOT_STATUS_LOCK (0)
#define VBOOT_STATUS_UNLOCK (1)

#define PDT_INFO_LOCK_FLAG_OFFSET (8*1024)
#define PDT_INFO_LOCK_FLAG_SECTION_SIZE (512)
#define PDT_INFO_LOCK_FLAG_MAX_SIZE (64)
#define PDT_INFO_UNLOCK_PWD_MAX_SIZE (64)

#define VBOOT_UNLOCK_PWD_CHECK_FAIL (1)
#define VBOOT_UNLOCK_PWD_CHECK_SUCC (0)

#define PRODUCT_SN_TOKEN_MAX_SIZE	(64)
#define PRODUCT_SN_SIGNATURE_SIZE	(512)

typedef struct{
	uint64_t img_addr;		//the base address of image to verify
	uint64_t img_len;		//length of image
	uint64_t pubkeyhash;	//pubkey hash for verifying image
	uint64_t hash_len;		//length of pubkeyhash
	uint64_t flag;		//sprd or sansa plan
}imgToVerifyInfo;

/*add for vboot v2*/
typedef struct{
	uint32_t vboot_verify_ret;
	uint32_t reserved0;
	uint32_t reserved1;
	uint32_t reserved2;
}VBootResultInfo;

typedef struct{
	uint64_t img_name;
	uint64_t img_name_len;
	uint64_t img_addr; //the base address of image to verify
	uint64_t img_len; //length of image
	uint64_t vbmeta_img_addr;
	uint64_t vbmeta_img_len;
	uint64_t vbmeta_pubkey_addr;
	uint64_t vbmeta_pubkey_len;
	uint64_t vb_cmdline_addr;
	uint64_t vb_cmdline_len;
	VBootResultInfo * verify_return_data;
	uint64_t verify_return_data_len;
	uint64_t vboot_unlock_status;
}VbootVerifyInfo;

/* Add for fastboot flashing lock_bootloader/unlock bootloader command */
typedef struct {
	uint64_t vbmeta_img_addr;				//vbmeta image addr
	uint64_t vbmeta_img_len;			//vbmeta image size
	uint64_t vbmeta_pubkey_addr;			//address to save vbmeta image hash
	uint64_t vbmeta_pubkey_len;			//hash length
	uint64_t product_sn_addr;				//product serial number addr
	uint64_t product_sn_len;			//product serial number length
	uint64_t product_sn_signature_addr;		//product serial number addr
	uint64_t product_sn_signature_len;		//product serial number length
	VBootResultInfo * verify_return_data;
	uint64_t verify_return_data_len;
}VbootUnlockVerifyInfo;

#if 0
typedef enum enAntiRBImageType{
	IMAGE_VBMETA = 0, /**/
	IMAGE_BOOT,
	IMAGE_RECOVERY,
	IMAGE_SYSTEM,
	IMAGE_L_MODEM,
	IMAGE_L_LDSP,
	IMAGE_L_LGDSP,
	IMAGE_PM_SYS,
	IMAGE_END
}antirb_image_type;
#endif
typedef struct{
    uint32_t img_ver[IMAGE_TYPE_END];
    uint32_t update_flag;
}VbootVerInfo;

#define SPRD_FLAG 1
#define SANSA_FLAG 2
#define SEC_MAX_PARTITION_NAME_LEN   (36)

extern imgToVerifyInfo img_verify_info;
#ifdef TOS_TRUSTY
extern imgToVerifyInfo *img_verify_info_tos;
#define  PAGE_ALIGN 4096
//#define  ARG_START_ADRESS 0x98100000//0x94000000+64M
#endif
extern VbootVerifyInfo *vboot_verify_info;
extern unsigned int g_DeviceStatus;

/*this two marco is diffent among products, pls check it!*/
#define SIMG_BUF     0x2E00000
#define CERT_SIZE    0x1000
#define SYS_HEADER_SIZE 0x200
#define RESERVE_SIZE 0x3000000
#if defined (CONFIG_SOC_IWHALE2)||defined (CONFIG_SPRD_SOC_SP9853I)
#define IRAM_BEGIN   0xe6000000
#elif defined (CONFIG_SOC_SHARKLE)||defined (CONFIG_SOC_SHARKL3)
#define IRAM_BEGIN   0x5000
#elif defined (CONFIG_SOC_SHARKL5)||defined (CONFIG_SOC_ROC1)||defined (CONFIG_SOC_SHARKL5PRO)
#define IRAM_BEGIN   0x5500
#elif defined (CONFIG_SOC_PIKE2)
#define IRAM_BEGIN 0x50002e00
#else
#define IRAM_BEGIN   (SPL_BASE_ADDR - SYS_HEADER_SIZE)
#endif
#define UBOOT_START  (CONFIG_SYS_TEXT_BASE - SYS_HEADER_SIZE)

#ifdef CONFIG_SOC_IWHALE2
#define VERIFY_ADDR  (0x29000000)
#else
//#define VERIFY_ADDR  (CONFIG_SYS_TEXT_BASE - RESERVE_SIZE)
#endif

#ifdef CONFIG_VBOOT_V2
//#define VBMETA_IMG_MAX_SIZE 0x800000
//#define VBOOT_BUFFER_ADDR  (VERIFY_ADDR - RESERVE_SIZE+ VBMETA_IMG_MAX_SIZE) /*0x99800000 ~ 0x9c000000 40MB*/
//#define VBMETA_IMG_ADDR  (VERIFY_ADDR - RESERVE_SIZE) /*0x99000000 ~ 0x99800000 8MB*/
#define VBMETA_PARTITION_MAX_SIZE (1024*1024)

typedef enum GetKeyFrom {
	GET_FROM_RAM = 0,
	GET_FROM_EMMC = 1
} get_key_from;
#endif

#define SEC_TRUE    0
#define SEC_FALSE   1

/***108K***/
#define SPL_IMAGE_SIZE (108*1024)
#define SECTION_SIZE   (512)
/**
SPL_EMMC_SECTOR_NUM=SPL_IMAGE_SIZE / SECTOR_SIZE
**/
#define SPL_EMMC_SECTOR_NUM  (SPL_IMAGE_SIZE/SECTION_SIZE)
//#define SAVE_SPL_IMAGE  VERIFY_ADDR

#define MAX_PACKED_IMAGE_SIZE  0x1400000  // 20MB
#define IMG_BAK_HEADER 0x42544844
typedef struct{
    uint32_t  mMagicNum;        // "BTHD"=="0x42544844"=="boothead"
    uint32_t  mVersion;         // 1
    uint8_t   mPayloadHash[32]; // sha256 hash value
    uint64_t  mImgAddr;         // image loaded address
    uint32_t  mImgSize;         // image size
    uint32_t  is_packed;        // packed image flag 0:false 1:true
    uint32_t  mFirmwareSize;    // runtime firmware size
    uint32_t  mFirmwareOff;     // runtime firmware offset
    uint8_t   reserved[448];    // 448 + 16*4 = 512
}sys_img_header;

typedef enum VERIFY_RESULT {
	VERIFY_NO_NEED = 1,
	VERIFY_OK,
	VERIFY_FAIL,
	VERIFY_STOP_WRITE,
	VERIFY_SPECIAL
} VERIFY_RESULT;


typedef enum VERIFY_PROCESS_FLAG {
	VERIFY_PROCESS_DOWNLOAD = 1,
	VERIFY_PROCESS_BOOT
}VERIFY_PROCESS_FLAG;

int get_secboot_base_from_dt(void);

VERIFY_RESULT dl_secure_process_flow(ulong * strip, unsigned char * part_name, 
				uint32_t rcv_size, uint32_t total_size, unsigned char * buf);

VERIFY_RESULT fb_secure_process_flow(ulong * strip, unsigned char * part_name,
			    uint32_t rcv_size, uint32_t total_size, unsigned char * buf);

void secboot_param_set(uint64_t load_buf,imgToVerifyInfo *imginfo);

int secure_efuse_program();

void secboot_init(char *partition_name);

void secboot_terminal(void);

void secboot_secure_process_flow(char *partition_name, uint64_t size, uint64_t offset, char *ram_addr);

#ifdef CONFIG_VBOOT_V2
void vboot_secure_process_init(char *partition_name, char *img_ram_addr, char * vbmeta_ram_addr, sys_img_header *header, VERIFY_PROCESS_FLAG flag);
void vboot_secure_process_flow(char *partition_name);
void vboot_secure_process_flow_cm4(char *partition_name);
void vboot_secure_process_prepare(void);
#endif

#ifdef CONFIG_SECBOOT
extern char * strtok(char * s,const char * ct);
extern int verify_product_sn_signature(void);
extern int config_os_version(unsigned long *os_version, uint32_t os_version_len);

#define ROOT_OF_TRUST_MAXSIZE 1024
extern int set_root_of_trust(unsigned char *root_of_trust_str, uint32_t root_of_trust_len);
extern unsigned char root_of_trust_str[ROOT_OF_TRUST_MAXSIZE];
#endif
void secboot_update_swVersion(void);

#endif
