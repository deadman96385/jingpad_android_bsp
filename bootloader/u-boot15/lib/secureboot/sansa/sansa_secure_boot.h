#ifndef _SANSA_SECURE_BOOT_H
#define _SANSA_SECURE_BOOT_H

#include <linux/string.h>
#include <secureboot/sec_common.h>
#include <secureboot/sansa/dx_header.h>
#include <secureboot/sansa/secureboot_defs.h>
#include <secureboot/sansa/bootimagesverifier_def.h>
#include <secureboot/sansa/bootimagesverifier_api.h>
#include <secureboot/sansa/dx_crypto_boot_defs.h>
#include <common.h>

#define RSA_HW_PKI_PKA_BARRETT_MOD_TAG_SIZE_IN_BITS    132
#define RSA_HW_PKI_PKA_BARRETT_MOD_TAG_SIZE_IN_BYTES   ((RSA_HW_PKI_PKA_BARRETT_MOD_TAG_SIZE_IN_BITS+7)/8)
#define N_REVNP_SIZE_IN_BYTES	SB_RSA_MOD_SIZE_IN_WORDS*sizeof(uint32_t)

DxSbCertInfo_t certPkgInfo = {0};
#endif
