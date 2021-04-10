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

#ifndef _SBROM_DMA_PAL_H
#define _SBROM_DMA_PAL_H

#include "dx_pal_types.h"
#include "dx_pal_dma_sb.h"
#include "dx_pal_dma_defs.h"


#ifdef __cplusplus
extern "C"
{
#endif


/*!  
 * This function should perfom flush operation for cache memory for passed data. 
 * the function can also handle cases of cache line alignment and virtual to physical addresses translation. 
 * 
 * @param[in] origDataAddr 	- original data address (may be virtual address) 
 * @param[out] mappedDataAddr 	- data address after mapping (must be physical address)
 * @param[in] dataSize	- size of data in bytes
 * @param[in] dmaDirection	- dma direction of data 
 * @param[in] dmaHandle	- handle for additional data if needed, may be NULL 
 *  
 */
void DX_PAL_DmaMap (uint64_t origDataAddr, uint64_t *mappedDataAddr, uint32_t dataSize, DX_PAL_DmaBufferDirection_t dmaDirection, 
		    DX_PAL_DmaBufferHandle dmaHandle);

/*!  
 * This function should perfom invalidate operation for cache memory for passed data.
 * 
 * @param[in] origDataAddr 	- original data address (may be virtual address) 
 * @param[out] mappedDataAddr 	- data address that need to be unmapped (must be physical address)
 * @param[in] dataSize	- size of data in bytes
 * @param[in] dmaDirection	- dma direction of data 
 * @param[in] dmaHandle	- handle for additional data if needed, may be NULL 
 *  
 */
void DX_PAL_DmaUnmap(uint64_t origDataAddr, uint64_t *mappedDataAddr, uint32_t dataSize, DX_PAL_DmaBufferDirection_t dmaDirection, 
		     DX_PAL_DmaBufferHandle dmaHandle);



#ifdef __cplusplus
}
#endif

#endif
