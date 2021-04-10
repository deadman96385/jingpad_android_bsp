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



#ifndef _SBROM_MNG_DEFS_H
#define _SBROM_MNG_DEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Security flag word */
#define DX_MNG_SECURITY_DISABLE_FLAG_ON    	0xC     
#define DX_MNG_SECURITY_DISABLE_FLAG_OFF    	0x3  


/* Definitions for OEM HASH key size */
#define DX_MNG_MAX_HASH_SIZE_IN_WORDS		8	
#define DX_MNG_MAX_HASH_SIZE_IN_BYTES		(DX_MNG_MAX_HASH_SIZE_IN_WORDS*sizeof(uint32_t))	
#define DX_MNG_256B_HASH_SIZE_IN_WORDS		DX_MNG_MAX_HASH_SIZE_IN_WORDS
#define DX_MNG_128B_HASH_SIZE_IN_WORDS		DX_MNG_MAX_HASH_SIZE_IN_WORDS/2

#define DX_MNG_HBK1_NOT_EXIST		0xffUL
#define DX_MNG_KCE_NOT_EXIST		0xffUL

/* RKEK size can be retrieved from host boot register bit '1 (missing in header file) */
#define DX_HOST_BOOT_CONFIG_BIT_SHIFT 	0x1UL
#define DX_HOST_BOOT_CONFIG_BIT_SIZE 	0x1UL

/* session key definition */
#define DX_MNG_SESSION_KEY_IS_SET		1
#define DX_MNG_SESSION_KEY_IS_UNSET		0

/*  minimum version anti-rollback conters */
#define DX_MNG_ALL_ONES_VALUE	0xffffffffUL
#define DX_MNG_ALL_ONES_NUM_BITS 32
#define DX_MNG_SW_REVOCATION_MAX_NUM_OF_BITS_CNTR1 31
#define DX_MNG_SW_REVOCATION_MAX_NUM_OF_BITS_CNTR2 223
#define DX_MNG_MAX_SIZE_OF_SRC_ADDRESS		   8

/* ********************** Macros ******************************* */

/*This function is based on an algorithm that was taken from :
  http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetNaive
**/
/* Count number of zeroes in 32-bit word */
#define DX_MNG_COUNT_ZEROES(regVal, regZero) 					\
	do {									\
		uint32_t v = regVal;                                         	\
		v = v - ((v >> 1) & 0x55555555);                   		\
		v = (v & 0x33333333) + ((v >> 2) & 0x33333333);    		\
		v = ((((v + (v >> 4)) & 0xF0F0F0F) * 0x1010101) >> 24); 	\
		regZero	+= (32 - v);						\
	}while(0)


#ifdef __cplusplus
}
#endif

#endif



