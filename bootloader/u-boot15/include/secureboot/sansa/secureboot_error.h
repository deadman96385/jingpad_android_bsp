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


#ifndef _SECUREBOOT_ERROR_H
#define _SECUREBOOT_ERROR_H

/*
 * All the includes that are needed for code using this module to
 * compile correctly should be #included here.
 */

#ifdef __cplusplus
extern "C"
{
#endif


/* error definitions */


#define DX_SECUREBOOT_BASE_ERROR                 0xF0000000

#define DX_SECUREBOOT_LAYER_BASE_ERROR           0x01000000

#define DX_SB_VERIFIER_LAYER_PREFIX      	1
#define DX_SB_DRV_LAYER_PREFIX    		2
#define DX_SB_SW_REVOCATION_LAYER_PREFIX 	3
#define DX_SB_NVM_LAYER_PREFIX                  4
#define DX_SB_SEP_LAYER_PREFIX                  5
#define DX_SB_HAL_LAYER_PREFIX                  6
#define DX_SB_RSA_LAYER_PREFIX			7
#define DX_SB_VERIFIER_CERT_LAYER_PREFIX	8
#define DX_SB_X509_CERT_LAYER_PREFIX		9

/* Boot Images Manager Base error = 0xF1000000 */
#define DX_BOOT_IMG_VERIFIER_BASE_ERROR          DX_SECUREBOOT_BASE_ERROR + \
                                                 DX_SB_VERIFIER_LAYER_PREFIX*DX_SECUREBOOT_LAYER_BASE_ERROR 
/* NVM Base error = 0xF4000000 */
#define DX_NVM_BASE_ERROR                        DX_SECUREBOOT_BASE_ERROR + \
                                                 DX_SB_NVM_LAYER_PREFIX*DX_SECUREBOOT_LAYER_BASE_ERROR                                                 
/* SEP Base error = 0xF5000000 */
#define DX_SB_SEP_BASE_ERROR                     DX_SECUREBOOT_BASE_ERROR + \
                                                 DX_SB_SEP_LAYER_PREFIX*DX_SECUREBOOT_LAYER_BASE_ERROR                                                 
/* HAL Base error = 0xF6000000 */
#define DX_SB_HAL_BASE_ERROR                     DX_SECUREBOOT_BASE_ERROR + \
                                                 DX_SB_HAL_LAYER_PREFIX*DX_SECUREBOOT_LAYER_BASE_ERROR                                                 
/* RSA Base error = 0xF7000000 */
#define DX_SB_RSA_BASE_ERROR                     DX_SECUREBOOT_BASE_ERROR + \
                                                 DX_SB_RSA_LAYER_PREFIX*DX_SECUREBOOT_LAYER_BASE_ERROR
/* Boot Images verifier cert Base error = 0xF8000000 */
#define DX_BOOT_IMG_VERIFIER_CERT_BASE_ERROR     DX_SECUREBOOT_BASE_ERROR + \
                                                 DX_SB_VERIFIER_CERT_LAYER_PREFIX*DX_SECUREBOOT_LAYER_BASE_ERROR                                                /* x509 Base error = 0xF9000000 */
#define DX_SB_X509_CERT_BASE_ERROR     		 DX_SECUREBOOT_BASE_ERROR + \
                                                 DX_SB_X509_CERT_LAYER_PREFIX*DX_SECUREBOOT_LAYER_BASE_ERROR                                               

/* crypto driver error base = 0xF2000000 */
#define DX_SB_DRV_BASE_ERROR     		 DX_SECUREBOOT_BASE_ERROR + \
                                                 DX_SB_DRV_LAYER_PREFIX*DX_SECUREBOOT_LAYER_BASE_ERROR                                               



/* the discretix error definition */
#define DX_SB_SEP_FATAL_ERROR_ERR       	 DX_SB_SEP_BASE_ERROR + 0x00000001
#define DX_SB_SEP_WRONG_STATE_ERR		 DX_SB_SEP_BASE_ERROR + 0x00000002
#define DX_SB_HAL_FATAL_ERROR_ERR       	 DX_SB_HAL_BASE_ERROR + 0x00000001
#define	DX_SB_DRV_ILLEGAL_INPUT_ERR		 DX_SB_DRV_BASE_ERROR + 0x00000001


/************************ Enums ********************************/


/************************ Typedefs  ****************************/


/************************ Structs  ******************************/


/************************ Public Variables **********************/


/************************ Public Functions **********************/


#ifdef __cplusplus
}
#endif

#endif

