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



#ifndef _SBROM_MNG_ERROR_H
#define _SBROM_MNG_ERROR_H

#ifdef __cplusplus
extern "C"
{
#endif

/* error definition - per bit */
#define DX_MNG_BASE_ERROR                    		0x0B000000
#define DX_MNG_ILLEGAL_INPUT_PARAM_ERR           	DX_MNG_BASE_ERROR + 0x00000001
#define DX_MNG_ILLEGAL_RKEK_VALUE_ERR     		DX_MNG_BASE_ERROR + 0x00000002   
#define DX_MNG_ILLEGAL_SCP_VALUE_ERR     		DX_MNG_BASE_ERROR + 0x00000004   
#define DX_MNG_ILLEGAL_OEM_HASH_VALUE_ERR     		DX_MNG_BASE_ERROR + 0x00000008   
#define DX_MNG_ILLEGAL_LCS_FOR_OPERATION_ERR   		DX_MNG_BASE_ERROR + 0x00000010   
#define DX_MNG_ILLEGAL_SESSION_KEY_ERR           	DX_MNG_BASE_ERROR + 0x00000020
#define DX_MNG_EXT_RAM_RESTORE_FAIL_ERR           	DX_MNG_BASE_ERROR + 0x00000040
#define DX_MNG_ILLEGAL_OEM_KCE_VALUE_ERR     		DX_MNG_BASE_ERROR + 0x00000080
#define DX_MNG_HASH_NOT_PROGRAMMED_ERR			DX_MNG_BASE_ERROR + 0x00000100
#define DX_MNG_OTP_WRITE_FAIL_ERR			DX_MNG_BASE_ERROR + 0x00000200
#define DX_MNG_ILLEGAL_HW_VERSION_ERR			DX_MNG_BASE_ERROR + 0x00000400
#define DX_MNG_ILLEGAL_SIGNATURE_ERR			DX_MNG_BASE_ERROR + 0x00000800
#define DX_MNG_CERTIFICATE_VERIFY_FAIL_ERR		DX_MNG_BASE_ERROR + 0x00001000
#define DX_MNG_ILLEGAL_CERTIFICATE_TYPE_ERR		DX_MNG_BASE_ERROR + 0x00001001
#define DX_MNG_TRNG_OP_ERR				DX_MNG_BASE_ERROR + 0x00002000
#define DX_MNG_ILLEGAL_SIZE_FOR_PRNG_ERR         	DX_MNG_BASE_ERROR + 0x00002001
#define DX_MNG_ENTROPY_OVERFLOW_ERR           		DX_MNG_BASE_ERROR + 0x00002002
#define DX_MNG_LOW_ENTROPY_ERR           		DX_MNG_BASE_ERROR + 0x00002003




/* error definition - mixed */
#define DX_MNG_ILLEGAL_OTP_KEY_ERR     			DX_MNG_BASE_ERROR + 0x00000006   

#ifdef __cplusplus
}
#endif

#endif



