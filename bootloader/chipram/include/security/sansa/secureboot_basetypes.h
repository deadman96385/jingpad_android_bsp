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


#ifndef _SECUREBOOT_BASE_TYPES_H
#define _SECUREBOOT_BASE_TYPES_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "dx_pal_types.h"
#include "dx_pal_types_plat.h"
 
/* error definitions */
#define DX_OK			0
/* virtual address 32-64 bit address defined according to the compiler */
typedef uintptr_t		DxVirtAddr_t;
typedef uint64_t 		DxDmaAddr_t;


/************************ Structs  ******************************/


/************************ Public Variables **********************/


/************************ Public Functions **********************/

#ifdef __cplusplus
}
#endif



#endif




