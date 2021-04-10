#ifndef _IWHALE2_EFUSE_DRIVE_H
#define _IWHALE2_EFUSE_DRIVE_H

typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned long long  uint64;
typedef signed char         int8;
typedef signed short        int16;
typedef signed int          int32;
typedef signed long long    int64;

/* secure efuse block id definitions */
#define HUK_BLOCK_START      (0)
#define HUK_BLOCK_END        (7)
#define KCE_BLOCK_START      (8)
#define KCE_BLOCK_END        (15)
#define ROTPK0_BLOCK_START   (16)
#define ROTPK0_BLOCK_END     (23)
#define SEC_VERSION_BLOCK    (24)
#define NSEC_VER_BLOCK_START (25)
#define NSEC_VER_BLOCK_END   (31)
#define ROTPK1_BLOCK_START   (32)
#define ROTPK1_BLOCK_END     (39)
#define ENDORKEY_BLOCK_START (40)
#define ENDORKEY_BLOCK_END   (47)
#define RESERVED_BLOCK_START (48)
#define RESERVED_BLOCK_END   (61)
#define CYCLE_STATE_BLOCK    (62)
#define LOCK_BIT_BLOCK       (63)

#define PUBLIC_EFUSE_BLOCK2  (2)

/*  life cycle rma bit */
#define RMA_MODE_BIT         (0)

typedef enum {
	EFUSE_RESULT_SUCCESS = 0,
	EFUSE_RD_ERROR,
	EFUSE_WR_ERROR,
	EFUSE_ID_ERROR,
	EFUSE_PARAM_ERROR
} Efuse_Result_Ret;

Efuse_Result_Ret sprd_ce_efuse_read(unsigned int block_id, unsigned int *pReadData);

Efuse_Result_Ret sprd_ce_efuse_program(unsigned int blocked_id, unsigned int pWriteData);

Efuse_Result_Ret sprd_ce_efuse_huk_program(void);

Efuse_Result_Ret sprd_get_lock_bits(unsigned int start_id, unsigned int end_id, unsigned int *bits_data, unsigned int *bits_data1);

unsigned int sprd_get_secure_boot_enable(void);

#endif
