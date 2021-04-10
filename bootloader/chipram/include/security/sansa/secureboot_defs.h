/***************************************************************
*  Copyright 2014 (c) Discretix Technologies Ltd.              *
*  This software is protected by copyright, international      *
*  treaties and various patents. Any copy, reproduction or     *
*  otherwise use of this software must be authorized in a      *
*  license agreement and include this Copyright Notice and any *
*  other notices specified in the license agreement.           *
*  Any redistribution in binary form must be authorized in the *
*  license agreement and include this Copyright Notice and     *
*  any other notices specified in the license agreement and/or *
*  in materials provided with the binary distribution.         *
****************************************************************/



#ifndef _SECURE_BOOT_DEFS_H
#define _SECURE_BOOT_DEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "dx_crypto_boot_defs.h"
/* General definitions */
/***********************/

#define DX_SB_MAX_NUM_OF_HASH_KEYS_IN_OTP	3
#define DX_SB_MAX_SIZE_NONCE_WORDS		2
#define DX_SB_MAX_SIZE_NONCE_BYTES		2*sizeof(uint32_t)

/*RSA defenitions*/
#define SB_RSA_MOD_SIZE_IN_WORDS 64
#define SB_RSA_HW_PKI_PKA_BARRETT_MOD_TAG_SIZE_IN_WORDS 5

#ifdef DX_HASH_SHA1_MODE
/* the hashblock size in words */
#define HASH_BLOCK_SIZE_IN_WORDS             16
/* the HASH - SHA1 results in words */
#define HASH_RESULT_SIZE_IN_WORDS            5
#define HASH_RESULT_SIZE_IN_BYTES            20
#else
/* the hashblock size in words */
#define HASH_BLOCK_SIZE_IN_WORDS             16
/* the HASH - SHA2 results in words */
#define HASH_RESULT_SIZE_IN_WORDS            8
#define HASH_RESULT_SIZE_IN_BYTES            32
#endif

typedef uint32_t HASH_Result_t[HASH_RESULT_SIZE_IN_WORDS];
typedef uint32_t DxSbCertPubKeyHash_t[HASH_RESULT_SIZE_IN_WORDS];
typedef uint32_t DxSbCertSocId_t[HASH_RESULT_SIZE_IN_WORDS];

/* input/output to the verification API */
typedef struct{

	/* internal field - keeps the version id for the certificates chain  */
	DxSbSwVersionId_t activeMinSwVersionId;

	/* in/out the public key hash (hash(N||Np) */
	HASH_Result_t pubKeyHash;

	/* internal flag */
	uint32_t initDataFlag;

}DxSbCertInfo_t;


/* Public key data structure */
typedef struct {
	/* N public key, big endian representation */
	uint32_t N[SB_RSA_MOD_SIZE_IN_WORDS];

#ifndef DX_NP_NOT_USED_IN_SB
	/* Np (Barrett n' value) */
	uint32_t Np[SB_RSA_HW_PKI_PKA_BARRETT_MOD_TAG_SIZE_IN_WORDS];  
#else  
	/* H value */
	uint32_t H[SB_RSA_MOD_SIZE_IN_WORDS + 1];  
#endif 

}DxSbNParams_t;

/* sw version */
typedef struct {
	DxSbSwVersionId_t  id;
	uint32_t swVersion;
}DxSbSwVersion_t;


/* Record HASH structure */
typedef struct {
	/* HASH calculated on the record */
	uint32_t SwHashResult[HASH_RESULT_SIZE_IN_WORDS];  

	/* Memory load address */
	uint64_t    memLoadAddr;

}DxSbHashRecordInfo_t; 

#define SIZE_OF_SW_DATA_COMP_PAIR_BYTES		40

/* Signature structure */
typedef struct {
	/* RSA PSS signature */
	uint32_t sig[SB_RSA_MOD_SIZE_IN_WORDS];

}DxSbSignature_t;  
 
/* SW component additional parameters */
typedef struct {
	/* Storage address */
	uint64_t    StoreAddr;	

	/* Size of the sw component in words */
	uint32_t    Len;

}DxSbSwImgAddData_t;

#define SIZE_OF_ADD_DATA_PAIR_BYTES		12

/* Table nonce used in composing iv for sw components decryption */
typedef uint8_t DxSbNonce_t[DX_SB_MAX_SIZE_NONCE_BYTES];

/********* Supported algorithms definitions ***********/

/* HASH supported algorithms */
typedef enum {
	/* HASH SHA 256 output */
	HASH_SHA256_Alg_Output = 0x01,

	/* HASH SHA 256 output truncated to 128 bits */
	HASH_SHA256_Alg_128_Output = 0x02,

	/* Last */
	HASH_Last              = 0x7FFFFFFF 

}DxSbHashAlg_t;


/* RSA supported algorithms */
typedef enum {
	/* RSA PSS 2048 after HASH SHA 256 */
	RSA_PSS_2048           = 0x01,
	RSA_PKCS15_2048	       = 0x02,

	/* Last */
	RSA_Last               = 0x7FFFFFFF

}DxSbRsaAlg_t;


/********* End of Supported algorithms definitions ***********/


/********* Function pointer definitions ***********/

/* Flash Read function pointer defintion, this function is used inside the secure boot APIs 
   To read data from the Flash */

typedef uint32_t (*DxSbFlashReadFunc) (uint64_t flashAddress,	/* Flash address to read from */
				       uint8_t *memDst,	/* memory destination to read the data to */
				       uint32_t sizeToRead,	/* size to read from Flash (in bytes) */
				       void* context);		/* context for user's needs */


/* Flash Write functions pointer definition, this function is used inside the secure boot APIs 
   to write data to the Flash */
typedef uint32_t (*DX_SB_FlashWrite) (uint64_t flashAddress, /* Flash address to write to */
					uint8_t *memSrc,	 /* memory source to write the data from */
					uint32_t sizeToWrite,	 /* size to write to Flash (in bytes) */ 
					void* context);		 /* context for user's needs */

/* Get OTP HASH function pointer definition, this function is used to retrieve the OEM key HASH
   from OTP */
typedef uint32_t (*Dx_SB_GetOTPHASH) (unsigned long hwBaseAddress,    /* CC base address */
					uint32_t keyIndex, 	     /* The OTP index */ 
					uint32_t *hashBuffer,      /* The HASH output */
					uint32_t hashSizeInWords); /* size of Hash key */

/********* End of Function pointer definitions ***********/

/* Indication to load or not the component to memory */
#define DX_SW_COMP_NO_MEM_LOAD_INDICATION       0xFFFFFFFFFFFFFFFFUL


#ifdef __cplusplus
}
#endif

#endif


