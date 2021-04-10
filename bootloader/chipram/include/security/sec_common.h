

#ifndef __SEC_COMMON_H
#define __SEC_COMMON_H

#include<security/sprdsec_header.h>
#include<security/sprd_rsa.h>

typedef struct{
	uint64_t img_addr; //the base address of image to verify
	uint64_t img_len; //length of image
	uint64_t pubkeyhash;//pubkey hash for verifying image
	uint64_t hash_len; //length of pubkeyhash
}imgToVerifyInfo;

/*this two marco is diffent among products, pls check it!*/
#if defined (CONFIG_ARCH_SCX35L2) ||defined (CONFIG_SOC_PIKE2)
#define IRAM_BEGIN 0x50002e00
#elif defined (CONFIG_SOC_IWHALE2)||defined (CONFIG_SOC_ISHARKL2)
#define IRAM_BEGIN 0xe6000000
#elif defined (CONFIG_SOC_SHARKLJ1)
#define IRAM_BEGIN 0x50010000
#elif defined (CONFIG_SOC_SHARKLE)||defined (CONFIG_SOC_SHARKL3)
#define IRAM_BEGIN 0x00005000
#elif defined (CONFIG_SOC_SHARKL5)||defined (CONFIG_SOC_ROC1)||defined (CONFIG_SOC_SHARKL5PRO)
#define IRAM_BEGIN 0x00005500
#else
#define IRAM_BEGIN 0x0000ce00
#endif


typedef struct{
	uint32_t mMagicNum; //0x42544844
	uint32_t mVersion; // 1
	uint8_t mPayloadHash[32]; //sha256 hash val
	uint64_t mImgAddr;  // image loader address
	uint32_t mImgSize;  //image size
	uint8_t reserved[460]; // 460 + 13*4 = 512
}sys_img_header;


typedef enum
{
	SECURE_BOOT = 1,
	SECURE_DOWNLOAD = 2
}SECURE_TYPE;

typedef enum
{
	SECBOOT_VERIFY_SUCCESS = 0,
	SECBOOT_VERIFY_FAIL = 1,
	SECBOOT_SET_SWVERSION_FAIL
}SecBoot_Result_Ret;

SecBoot_Result_Ret secboot_verify(void *ptr,void *m,void *n,uint32_t data_len,SECURE_TYPE type);

void dl_secure_verify(void *partition_name,void *header,void *code);

int secboot_enable_check(void);

void secboot_param_set(uint64_t load_buf,imgToVerifyInfo *imginfo);

void secboot_get_pubkhash(uint64_t img_buf,imgToVerifyInfo *imginfo);

void update_swVersion(void);

void secboot_init(void);

extern void sansa_enable_efuse_EB(void);

#endif
