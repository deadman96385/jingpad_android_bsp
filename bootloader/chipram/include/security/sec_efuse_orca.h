#ifndef _SEC_EFUSE_ORCA_H_
#define _SEC_EFUSE_ORCA_H_

#include "security/sec_efuse_orca_drv.h"

/*---------------------------
 *   MACRO DEFINITIONS
 *------------------------------*/
/*  minimum version anti-rollback conters */
#define ALL_ONES_VALUE 		0xffffffffUL
#define ALL_ONES_NUM_BITS 	32
#define SW_REVOCATION_MAX_NUM_OF_BITS_CNTR1 31
#define SW_REVOCATION_MAX_NUM_OF_BITS_CNTR2 223

/* SW version definition */
#define VERSION_COUNTER1_WIDTH    1
#define VERSION_COUNTER2_WIDTH    7
#define BITS_WITHIN_WORD          32

/* MACRO to count one bits */
#define COUNT_ONE_BITS(number, BitCount) \
do	\
{	\
	uint32_t tmp_num = number;	\
	BitCount = 0;				\
	while (tmp_num)				\
	{							\
		tmp_num = tmp_num & (tmp_num - 1);		\
        BitCount = BitCount + 1;				\
    }											\
} while (0)

/*********************EFUSE BLOCK INDEX MAPPING**************/
#define RMA_MODE_BIT			(0)
//***************** Public Part
#define BONDING_BLOCK_START		(0)
#define BONDING_BLOCK_END		(1)
#define ANA_BLOCK_START		        (2)
#define ANA_BLOCK_END		        (13)
#define DIG1_LPDDR_BLOCK		(14)
#define DIG2_PCIE_EP_BLOCK		(15)
#define SECUREBOOT_BLOCK_START		(16)
#define SECUREBOOT_BLOCK_END		(23)
#define CP_SIMLOCK_PUBKEY_START		(24)
#define CP_SIMLOCK_PUBKEY_END		(25)

//***************** Secure Part
#define SEC_VERSION_BLOCK		(26)
#define CYCLE_STATE_BLOCK		(27)
#define ROTPK1_BLOCK_START		(28)
#define ROTPK1_BLOCK_END		(35)
#define LOCK_BIT_BLOCK			(36)

//******** just define for compile,no use
#define NONE				(255)
#define HUK_BLOCK_START			(NONE)
#define HUK_BLOCK_END			(NONE)
#define KCE_BLOCK_START			(NONE)
#define KCE_BLOCK_END			(NONE)
#define ROTPK0_BLOCK_START		(NONE)
#define ROTPK0_BLOCK_END		(NONE)
#define NSEC_VER_BLOCK_START		(NONE)
#define NSEC_VER_BLOCK_END		(NONE)
#define RESERVED_BLOCK_START		(NONE)
#define RESERVED_BLOCK_END		(NONE)
#define ENDORKEY_BLOCK_START		(NONE)
#define ENDORKEY_BLOCK_END		(NONE)

extern Efuse_Result_Ret efuse_read_lock_bits_map(uint32 *pReadData);
/* Secure Public Efuse Fuction */
extern Efuse_Result_Ret sprd_ce_efuse_huk_program(void);
extern Efuse_Result_Ret sprd_get_lock_bits(unsigned int start_id, unsigned int end_id, unsigned int *bits_data, unsigned int *bits_data1);
extern Efuse_Result_Ret sprd_ce_efuse_read(unsigned int block_id, unsigned int *read_ptr);
extern Efuse_Result_Ret sprd_ce_efuse_program(unsigned int block_id, unsigned int WriteData);
extern unsigned int sprd_get_secure_boot_enable(void);

/* Public Efuse Fuction */
extern  uint32 sprd_ap_efuse_read(int blk_index);
#endif
