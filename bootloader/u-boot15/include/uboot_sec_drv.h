/*
 * Copyright (c) 2013-2014, ARM Limited and Contributors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _UBOOT_SEC_DRV_H_
#define _UBOOT_SEC_DRV_H_

#include <common.h>
#include "secureboot/sec_common.h"

#define TEESMC_32                       0
#define TEESMC_64                       0x40000000
#define TEESMC_FAST_CALL                0x80000000
#define TEESMC_STD_CALL                 0

#define TEESMC_OWNER_MASK               0x3F
#define TEESMC_OWNER_SHIFT              24

#define TEESMC_FUNC_MASK                0xFFFF

#define TEESMC_IS_FAST_CALL(smc_val)    ((smc_val) & TEESMC_FAST_CALL)
#define TEESMC_IS_64(smc_val)           ((smc_val) & TEESMC_64)
#define TEESMC_FUNC_NUM(smc_val)        ((smc_val) & TEESMC_FUNC_MASK)
#define TEESMC_OWNER_NUM(smc_val)       (((smc_val) >> TEESMC_OWNER_SHIFT) & \
                                         TEESMC_OWNER_MASK)

#define TEESMC_CALL_VAL(type, calling_convention, owner, func_num) \
((type) | (calling_convention) | \
(((owner) & TEESMC_OWNER_MASK) << TEESMC_OWNER_SHIFT) |\
((func_num) & TEESMC_FUNC_MASK))

#define TEESMC_OWNER_ARCH 0
#define TEESMC_OWNER_CPU 1
#define TEESMC_OWNER_SIP 2
#define TEESMC_OWNER_OEM 3
#define TEESMC_OWNER_STANDARD 4
#define TEESMC_OWNER_TRUSTED_APP 48
#define TEESMC_OWNER_TRUSTED_OS 50
#define TEESMC_OWNER_SPRDSEC 52

#define TEESMC_OWNER_TRUSTED_OS_API 63


#ifdef CONFIG_TEECFG_CUSTOM
#define TEESMC_OWNER_SECURE_MONITOR 60
#define TEESMC_FUNCID_GET_TEESIZE 19
#define TEESMC_FC_GET_TEESIZE \
	TEESMC_CALL_VAL(TEESMC_32, TEESMC_FAST_CALL, TEESMC_OWNER_SECURE_MONITOR, \
	TEESMC_FUNCID_GET_TEESIZE)
#endif

#define TEESMC_FUNCID_SIPCALL_WITH_ARG 0x20

#define TEESMC_SIPCALL_WITH_ARG \
TEESMC_CALL_VAL(TEESMC_32, TEESMC_FAST_CALL, TEESMC_OWNER_SPRDSEC, \
TEESMC_FUNCID_SIPCALL_WITH_ARG)

#ifdef CONFIG_X86
#define SEC_FIREWALL_CMD 	0x02
#define SEC_VERIFY_CMD 0x1
#define SEC_GETHBK_CMD 0x8
/*add fastboot cmd for iwhale2*/
#define FUNCTYPE_GET_SOCID 0x03
#define FUNCTYPE_GET_LCS 0x0A
#define FUNCTYPE_SET_RMA 0x0B
/*add for vboot*/
#define FUNCTYPE_VBOOT_VERIFY_IMG	0x20
#define FUNCTYPE_VBOOT_SET_VERSION 0x21
#define FUNCTYPE_SET_BINDING_DATA   0x30
#define FUNCTYPE_CRYPTO_DATA 0x31
#define FUNCTYPE_CHECK_PWD 0x32
#define FUNCTYPE_CHECK_LOCK_STATUS 0x33
#define FUNCTYPE_VERIFY_PRODUCT_SN_SIGNATURE 0x34
#define FUNCTYPE_CONFIG_OS_VERSION 0x35

#else
#define FUNCTYPE_VERIFY_IMG               0x01
#define FUNCTYPE_PROGRAM_EFUSE            0x02
#define FUNCTYPE_GET_SOCID                0x03
#define FUNCTYPE_UPDATE_VERSION           0x04
#define FUNCTYPE_GET_SANSA_LCS            0x05
#define FUNCTYPE_SET_SANSA_RMA            0x06
#define FUNCTYPE_KCE_PROGRAM              0x07
#define FUNCTYPE_GET_HBK                  0x08
#define FUNCTYPE_SET_SECURE_RANGE_PARAM   0x09
/*add fastboot cmd for sharkl2*/
#define FUNCTYPE_GET_LCS 0x0A
#define FUNCTYPE_SET_RMA 0x0B

#define FUNCTYPE_VBOOT_VERIFY_IMG	0x20
#define FUNCTYPE_VBOOT_SET_VERSION 0x21
#define FUNCTYPE_SET_RPMB_SIZE     0x22
#define FUNCTYPE_IS_WR_RPMB_KEY    0x23
#define FUNCTYPE_CHECK_RPMB_KEY    0x24

/*add for vboot*/
#define FUNCTYPE_SET_BINDING_DATA   0x30
#define FUNCTYPE_CRYPTO_DATA 0x31
#define FUNCTYPE_CHECK_PWD 0x32
#define FUNCTYPE_CHECK_LOCK_STATUS 0x33
#define FUNCTYPE_VERIFY_PRODUCT_SN_SIGNATURE 0x34
#define FUNCTYPE_CONFIG_OS_VERSION 0x35
#define FUNCTYPE_SET_ROOT_OF_TRUST 0x36

// add for SOTER-start
#if defined (CONFIG_CHIP_UID)
#define FUNCTYPE_SET_CHIP_UID          0x40
#endif
// add for SOTER-end

#define BLOCK_NUM_3                      (0x03)
#define DISABLE_DX_DEBUG_CONTROL         (0x20000000)
#endif

#define NO_ERROR 0

typedef struct smc_param {
        uint32_t a0;
        uint32_t a1;
        uint32_t a2;
        uint32_t a3;
        uint32_t a4;
        uint32_t a5;
        uint32_t a6;
        uint32_t a7;
}smc_param;

int uboot_check_rpmb_key();
int uboot_is_wr_rpmb_key();
int uboot_set_rpmb_size();
int uboot_verify_img(unsigned long start_addr, uint32_t lenth);
int uboot_get_socid(uint64_t start_addr, uint64_t lenth);
int uboot_program_efuse(uint64_t start_addr, uint64_t lenth);
int uboot_update_swVersion(uint64_t start_addr, uint64_t lenth);

int uboot_sansa_get_lcs(uint32_t *p_lcs);

int uboot_sansa_set_rma(uint32_t *p_rmaret);

int uboot_kce_program(uint64_t start_addr, uint64_t lenth);

smc_param *tee_common_call(uint32_t funcid, uint32_t start_addr, uint32_t lenth);

#ifdef CONFIG_TEECFG_CUSTOM
int tee_smc_get_tee_size(void);
#endif

void tee_smc_call   (struct smc_param *param);

void tee_call_request(unsigned int **mem_ptr);
void tos_status_check();
void tos_start_notify();
void tos_end_notify();
#endif
