#ifndef _SANSA_SECURE_BOOT_H
#define _SANSA_SECURE_BOOT_H

#include <security/sec_common.h>
#include <security/sansa/dx_header.h>
#include <security/sansa/secureboot_defs.h>
#include <security/sansa/bootimagesverifier_def.h>
#include <security/sansa/bootimagesverifier_api.h>
#include <security/sansa/dx_crypto_boot_defs.h>

#define RSA_HW_PKI_PKA_BARRETT_MOD_TAG_SIZE_IN_BITS    132
#define RSA_HW_PKI_PKA_BARRETT_MOD_TAG_SIZE_IN_BYTES   ((RSA_HW_PKI_PKA_BARRETT_MOD_TAG_SIZE_IN_BITS+7)/8)

DxSbCertInfo_t certPkgInfo = {0};

#define CERT_NUM_MAX 10
static DxSbSwVersionId_t defSwVersionId = DX_SW_VERSION_COUNTER1;//1:trusted version  2:non trusted version
static uint32_t iNodeCounter = 0;

typedef struct{
	DxSbSwVersion_t swVersionInfo[CERT_NUM_MAX];
	uint32_t num;
}SwVersionRecordInfo_t;

static SwVersionRecordInfo_t swVersionRecordInfo = {0};

static unsigned int SB_MemoryRead(uint64_t storageAddress,uint8_t *memDst,uint32_t sizeToRead,void *context);
#endif
