/*
 * Copyright (c) 2015, Spreadtrum.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
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

#ifndef SECEFUSE_H
#define SECEFUSE_H

#define KCE_BYTES_LEN    16
#ifndef BIT
#define BIT(x) (1<<x)
#endif

#define SEC_EFUSE_OP_READ (0x00000001)
#define SEC_EFUSE_OP_WRITE (0x00000002)

#define REG_AP_CE_EFUSE_BASE	0x21c00000
#define REG_AP_CE_BASE	0x21400000
#define REG_AP_AHB_BASE	0x20e00000

/*BLOCK0 ~ BLOCK7 RW disable*/
/*BLOCK8 ~ BLOCK15 WR only*/
/*BLOCK16 ~ BLOCK46 RW enable*/
#define SEC_EFUSE_BLOCK_ENRD_START_ID 16
#define SEC_EFUSE_BLOCK_ENWR_START_ID 8
#define SEC_EFUSE_PROT_BLOCK_MAX_ID 45
#define SEC_EFUSE_BLOCK_MAX_ID 47

#define REG_AP_CE_KEY_BASE_OFFSET	(REG_AP_CE_BASE + 0x400)
#define REG_AP_CE_KEY_HUK_OFFSET	(REG_AP_CE_KEY_BASE_OFFSET + 0x00)
#define REG_AP_CE_KEY_KCE_OFFSET	(REG_AP_CE_KEY_BASE_OFFSET + 0x20)
#define REG_AP_CE_KEY_ROTPK_OFFSET	(REG_AP_CE_KEY_BASE_OFFSET + 0x30)
#define REG_AP_CE_KEY_SEC_ANTIROLL_OFFSET	(REG_AP_CE_KEY_BASE_OFFSET + 0x50)
#define REG_AP_CE_KEY_NONSEC_ANTIROLL_OFFSET	(REG_AP_CE_KEY_BASE_OFFSET + 0x54)
#define REG_AP_CE_KEY_ROTPK1_OFFSET	(REG_AP_CE_KEY_BASE_OFFSET + 0x70)
#define REG_AP_CE_KEY_RESERVED_OFFSET	(REG_AP_CE_KEY_BASE_OFFSET + 0x90)
#define REG_AP_CE_KEY_LIFECYCLE_OFFSET	(REG_AP_CE_KEY_BASE_OFFSET + 0xb4)
#define REG_AP_CE_KEY_BITPROTECT_OFFSET0 (REG_AP_CE_KEY_BASE_OFFSET + 0xb8)
#define REG_AP_CE_KEY_BITPROTECT_OFFSET1 (REG_AP_CE_KEY_BASE_OFFSET + 0xbc)

#define SEC_EFUSE_BLOCK_WR_TEST_START_ID	36
#define SEC_EFUSE_BLOCK_WR_TEST_END_ID	36

#define SEC_EFUSE_BLOCK_WR_PROT0	46
#define SEC_EFUSE_BLOCK_WR_PROT1	47

#define REG_AP_AHB_EN	(REG_AP_AHB_BASE + 0x00)
#define REG_AP_AHB_RESET	(REG_AP_AHB_BASE + 0x04)

#define SEC_CE_REG_CLK_EN	(REG_AP_CE_BASE + 0x18)
#define SEC_CE_REG_RNG_EN	(REG_AP_CE_BASE + 0x200)
#define SEC_CE_REG_KEY_USE_WAY	(REG_AP_CE_BASE + 0x340)
#define SEC_CE_REG_KEY_SYNC_ADDR	(REG_AP_CE_BASE + 0x344)

#define SEC_CE_EFUSE_REG_RD_INDEX	(REG_AP_CE_EFUSE_BASE + 0x00)
#define SEC_CE_EFUSE_REG_MODE_CTRL	(REG_AP_CE_EFUSE_BASE + 0x0c)
#define SEC_CE_EFUSE_REG_CFG0	(REG_AP_CE_EFUSE_BASE + 0x10)
#define SEC_CE_EFUSE_REG_STATUS	(REG_AP_CE_EFUSE_BASE + 0x20)
#define SEC_CE_EFUSE_REG_STATUS_ERR	(REG_AP_CE_EFUSE_BASE + 0x24)
#define SEC_CE_EFUSE_REG_STATUS_PROT	(REG_AP_CE_EFUSE_BASE + 0x28)
#define SEC_CE_EFUSE_REG_CLR_ERR	(REG_AP_CE_EFUSE_BASE + 0x30)
#define SEC_CE_EFUSE_REG_CLR_PROT	(REG_AP_CE_EFUSE_BASE + 0x34)

//begin of add for adapt platform api

/* secure efuse block id definitions */
#define HUK_BLOCK_START      (0)
#define HUK_BLOCK_END        (7)
#define KCE_BLOCK_START      (8)
#define KCE_BLOCK_END        (11)
#define ROTPK0_BLOCK_START   (12)
#define ROTPK0_BLOCK_END     (19)
#define SEC_VERSION_BLOCK    (20)
#define NSEC_VER_BLOCK_START (21)
#define NSEC_VER_BLOCK_END   (27)
#define ROTPK1_BLOCK_START   (28)
#define ROTPK1_BLOCK_END     (35)
#define RESERVED_BLOCK_START (36)
#define RESERVED_BLOCK_END   (44)
#define CYCLE_STATE_BLOCK    (45)
#define LOCK_BIT_BLOCK       (46)

//invalid value just for compile
#define ENDORKEY_BLOCK_START (0xFFFFFFFF)
#define ENDORKEY_BLOCK_END (0xFFFFFFFF)

#define PUBLIC_EFUSE_BLOCK2  (2)
//end of add for adapt platform api

#define RMA_MODE_BIT         (0)

typedef enum sec_efuse_test_type{
	WRITE_HUK = 0x1,
	WRITE_KCE = 0x2,
	WRITE_OTHER = 0x4
};

typedef enum {
	EFUSE_RESULT_SUCCESS = 0,
	EFUSE_RD_ERROR,
	EFUSE_WR_ERROR,
	EFUSE_ID_ERROR,
	EFUSE_PARAM_ERROR
} Efuse_Result_Ret;

Efuse_Result_Ret sprd_ce_efuse_read(unsigned int block_id, unsigned int *pReadData);

Efuse_Result_Ret sprd_ce_efuse_program(unsigned int block_id, unsigned int WriteData);

Efuse_Result_Ret sprd_ce_efuse_huk_program(void);

Efuse_Result_Ret sprd_get_lock_bits(unsigned int start_id, unsigned int end_id, unsigned int *bits_data, unsigned int *bits_data1);

unsigned int sprd_get_secure_boot_enable(void);
#endif
