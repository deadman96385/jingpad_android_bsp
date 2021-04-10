#ifndef _SPRD_SECURE_EFUSE_MNG_API_H
#define _SPRD_SECURE_EFUSE_MNG_API_H

#ifdef __cplusplus
extern "C"
{
#endif

#define SEC_EFUSE_OK                               0x0
/* error definition - per bit */
#define SEC_EFUSE_BASE_ERROR                       0xFFFF0000
#define SEC_EFUSE_ILLEGAL_INPUT_PARAM_ERR          SEC_EFUSE_BASE_ERROR + 0x00000001
#define SEC_EFUSE_WRITE_FAIL_ERR                   SEC_EFUSE_BASE_ERROR + 0x00000002
#define SEC_EFUSE_READ_FAIL_ERR                    SEC_EFUSE_BASE_ERROR + 0x00000003
#define SEC_EFUSE_WRITE_CHECK_ERR                  SEC_EFUSE_BASE_ERROR + 0x00000004
#define SEC_EFUSE_LOCK_BIT_ERR                     SEC_EFUSE_BASE_ERROR + 0x00000005
#define SEC_EFUSE_POINTER_ERR                      SEC_EFUSE_BASE_ERROR + 0x00000006
#define SECURE_BOOT_DISABLE_ERR                    SEC_EFUSE_BASE_ERROR + 0x00000010

/*---------------------------
        PUBLIC FUNCTIONS
----------------------------------*/

/* version counter of value */
typedef enum {
    /* trusted version */
    SW_VERSION_COUNTER1 = 0,
    /* non trusted version */
    SW_VERSION_COUNTER2
} sw_version_id_t;

/*
 * write Hardware Unique Key (HUK).
 */
void sprd_huk_program(void);

/*
 * write KCE efuse blocks.
 */
unsigned int sprd_kce_program(unsigned int* pKceData);

/* write Root of Trust Public Key Hash(ROTPK0) blocks.
 *
 */
unsigned int sprd_rotpk0_program(unsigned int* pRotpkData);

/*
 * get secure or non secure firmware minimum version.
 */
unsigned int sprd_get_version(sw_version_id_t counterId, unsigned int* swVersion);

/*
 * set secure or non secure firmware minimum version.
 */
unsigned int sprd_set_version(sw_version_id_t counterId, unsigned int swVersion);

/*
 * write Root of Trust Public Key Hash(ROTPK1) blocks
 */
unsigned int sprd_rotpk1_program(unsigned int* pArotpkData);

/*
 * write endorsement key.
 */
unsigned int sprd_endorkey_program(unsigned int* pEndorkeyData);

/*
 * get device life cycle state.
 */
unsigned int sprd_get_lcs(unsigned int *pLcs);

/*
 * write reserved blocks.
 */
unsigned int sprd_reserved_efuse_program(unsigned int start_id, unsigned int end_id, unsigned int* pReservedData);

/*
 * read efuse blocks.
 */
unsigned int sprd_sec_efuse_blocks_read(unsigned int start_id, unsigned int end_id, unsigned int *readData);

/*
 * read rotpk0 blocks
 */
unsigned int sprd_sec_efuse_rotpk0_read(unsigned int *readData);

/*
 * read rotpk1 blocks
 */
unsigned int sprd_sec_efuse_rotpk1_read(unsigned int *readData);

/*
 * read endorkey blocks
 */
unsigned int sprd_sec_efuse_endorkey_read(unsigned int *readData);

/*
 * read reserverd blocks
 */
unsigned int sprd_sec_efuse_reserverd_read(unsigned int startOffset, unsigned int *readData, unsigned int len);

/*
 * read eotpk select blocks
 */
unsigned int sprd_sec_efuse_rotpk_select(unsigned int *rpkFlag);


#ifdef __cplusplus
}
#endif

#endif
