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

#ifndef _DX_CRYPTO_BOOT_DEFS_H
#define _DX_CRYPTO_BOOT_DEFS_H

/* version counters value */
typedef enum {

	/* trusted version */
	DX_SW_VERSION_COUNTER1 = 1,
	/* non trusted version */
	DX_SW_VERSION_COUNTER2,

	DX_SW_VERSION_MAX      = 0x7FFFFFFF

}DxSbSwVersionId_t;


/* SW version definition */
#define DX_SB_VERSION_COUNTER1_WIDTH	1
#define DX_SB_VERSION_COUNTER2_WIDTH	7
#define BITS_WITHIN_WORD  32


typedef enum {
	DX_SB_HASH_BOOT_KEY_0_128B 	= 0,		/* 128-bit truncated SHA256 digest of public key 0 */
	DX_SB_HASH_BOOT_KEY_1_128B	= 1, 		/* 128-bit truncated SHA256 digest of public key 1 */
	DX_SB_HASH_BOOT_KEY_256B	= 2, 		/* 256-bit SHA256 digest of public key */
	DX_SB_HASH_BOOT_NOT_USED	= 0xFF,
	DX_SB_HASH_EXTERNAL_BOOT_KEY 	= 0xFFFFFFFF,	/* use external 128-bit truncated SHA256 digest */
}DxSbPubKeyIndexType_t;


#endif
