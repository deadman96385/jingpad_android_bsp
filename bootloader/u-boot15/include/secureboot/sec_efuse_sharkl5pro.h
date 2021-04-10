#ifndef _SEC_EFUSE_SHARKL5PRO_H_
#define _SEC_EFUSE_SHARKL5PRO_H_

#include "sec_efuse_sharkl5pro_drv.h"

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
#define NONE					(255)
#define HUK_BLOCK_START			(0)
#define HUK_BLOCK_END			(7)
#define KCE_BLOCK_START			(8)
#define KCE_BLOCK_END			(15)
#define ROTPK0_BLOCK_START		(16)
#define ROTPK0_BLOCK_END		(23)
#define SEC_VERSION_BLOCK		(24)
#define ROTPK1_BLOCK_START		(25)
#define ROTPK1_BLOCK_END		(32)
#define CYCLE_STATE_BLOCK		(33)
#define LOCK_BIT_BLOCK			(34)
#define NSEC_VER_BLOCK_START	(36)
#define NSEC_VER_BLOCK_END		(42)
#define RESERVED_BLOCK_START	(NONE)
#define RESERVED_BLOCK_END		(NONE)
#define ENDORKEY_BLOCK_START	(NONE)
#define ENDORKEY_BLOCK_END		(NONE)

/********************** Public Part **********************/
#define PUBLIC_EFUSE_BLOCK2		(46)
#define RMA_MODE_BIT			(0)

/* Secure Public Efuse Fuction */
extern Efuse_Result_Ret sprd_ce_efuse_huk_program(void);
extern Efuse_Result_Ret sprd_get_lock_bits(unsigned int start_id, unsigned int end_id, unsigned int *bits_data, unsigned int *bits_data1);
extern Efuse_Result_Ret sprd_ce_efuse_read(unsigned int block_id, unsigned int *read_ptr);
extern Efuse_Result_Ret sprd_ce_efuse_program(unsigned int block_id, unsigned int WriteData);
extern unsigned int sprd_get_secure_boot_enable(void);

/* Public Efuse Fuction */
extern  uint32 sprd_ap_efuse_read(int blk_index);
#endif
