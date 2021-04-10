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



#ifndef _SBROM_SEC_DEBUG_API_H
#define _SBROM_SEC_DEBUG_API_H

#ifdef __cplusplus
extern "C"
{
#endif


#include "dx_pal_types_plat.h"


#define DX_MNG_SEC_DEBUG_SOC_ID_SIZE    0x20
#define DX_MNG_SEC_DEBUG_DEBUG_MASK_SIZE_IN_BITS    0x1F

/*----------------------------
      PUBLIC FUNCTIONS
-----------------------------------*/

/*! 
 * @brief enable secure debug on the device
 *
 * @param[in] hwBaseAddress 	- cryptocell base address
 * @param[in] pDebugCertPkg 	    - full secure debug certificate
 * @param[in] certPkgSize          - certificate size in bytes
 * @param[out] pEnableRmaMode   - RMA mode:non-zero indicates RMA enabled 
 *
 * @return DxError_t 		- On success: the value DX_OK is returned, 
 *         			  On failure: a value from sbrom_management_error.h
 */
DxError_t DX_MNG_EnableSecureDebug(unsigned long   hwBaseAddress,
				   uint32_t   *pDebugCertPkg,
				   uint32_t   certPkgSize,
				   uint32_t   *pEnableRmaMode);



#ifdef __cplusplus
}
#endif

#endif



