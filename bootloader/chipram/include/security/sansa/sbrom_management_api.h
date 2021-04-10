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



#ifndef _SBROM_MNG_API_H
#define _SBROM_MNG_API_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "dx_pal_types.h"
#include "sbrom_management_defs.h"
#include "secureboot_defs.h"


/* Life cycle state definitions */
#define DX_MNG_CHIP_MANUFACTURE_LCS		0x0
#define DX_MNG_DEVICE_MANUFACTURE_LCS		0x1
#define DX_MNG_SECURITY_DISABLED_LCS		0x3
#define DX_MNG_SECURE_LCS			0x5
#define DX_MNG_RMA_LCS				0x7

/* AES definitions */
#define DX_MNG_AES_BLOCK_SIZE_IN_WORDS	4
#define DX_MNG_AES_BLOCK_SIZE_IN_BYTES	(DX_MNG_AES_BLOCK_SIZE_IN_WORDS*sizeof(uint32_t))

	/* definition for NONCE array */
#define DX_MNG_MAX_NONCE_ARRAY_SIZE_WORDS	4
#define DX_MNG_MAX_KDR_SIZE_WORDS		8

typedef uint8_t DxMngAesCmacResult_t[DX_MNG_AES_BLOCK_SIZE_IN_BYTES];
typedef uint32_t DxMngAesKey_t[DX_MNG_AES_BLOCK_SIZE_IN_WORDS];

/* Max size of ram buffer for RND usage */
#define DX_RND_MAX_SIZE_OF_RAM_BUFFER_WORDS 1024
#define DX_RND_MAX_SIZE_OF_RAM_BUFFER_BYTES (DX_RND_MAX_SIZE_OF_RAM_BUFFER_WORDS * sizeof(uint32_t))

/*----------------------------
      PUBLIC FUNCTIONS
-----------------------------------*/

/*! 
 * @brief Secure-Boot ROM Managemant entry point. 
 * 	Verify HW version product number.
 *
 * @param[in] hwBaseAddress 	- cryptocell base address
 *
 * @return DxError_t 		- On success: the value DX_OK is returned, 
 *         			  On failure: a value from sbrom_management_error.h
 */
DxError_t DX_MNG_InitSbrom(unsigned long hwBaseAddress);


/*! 
 * @brief This function retrieves the security lifecycle from the HW register (when it is valid). 
 *        If the lifecycle is "secure" the function also needs to verify that the security disable flag
 *        (word 0x18 in OTP) is set to 4'b0011.
 *
 * @param[in] hwBaseAddress 	- cryptocell base address
 * @param[in/out] pLcs		- pointer to copy of current lifecycle state
 *
 * @return DxError_t 		- On success: the value DX_OK is returned, 
 *         			  On failure: a value from sbrom_management_error.h
 */
DxError_t DX_MNG_GetLcs(unsigned long hwBaseAddress,
			uint32_t *pLcs);

/*! 
 * @brief This function retrieves the security lifecycle from the HW register (when it is valid). 
 *        If the lifecycle is "secure" the function also needs to verify that the security disable flag
 *        (word 0x18 in OTP) is set to 4'b0011.
 *        In case the LCS is RMA the function will initialize the KDR to random value.
 *
 * @param[in] hwBaseAddress 	- cryptocell base address
 * @param[in/out] pLcs		- pointer to copy of current lifecycle state
 * @param[in] pWspace 		- workspace buffer, can be null for all states except for RMA
 * @param[in] wspaceSize 	- workspace buffer size, for RMA mode must be at least DX_RND_MAX_SIZE_OF_RAM_BUFFER_BYTES.
 * 
 *
 * @return DxError_t 		- On success: the value DX_OK is returned, 
 *         			  On failure: a value from sbrom_management_error.h
 */
DxError_t DX_MNG_GetAndInitLcs(unsigned long hwBaseAddress,
			       uint32_t *pLcs, 
			       uint32_t *pWspace,
			       uint32_t wspaceSize);

/*!
 * @brief This function reads the public key from OTP memory by key index
 *        (index can be select Hbk, Hbk0, or Hbk1). Returns an error if the
 *        requested hash field does not match its zero count.
 *
 * @param[in] hwBaseAddress 	- cryptocell base address
 * @param[in] keyIndex 		- the index of the key HASH in the OTP (should be DxSbPubKeyIndexType_t) 
 * @param[out] hashedPubKey	- the HASH of the public key
 * @param[in] hashResultSizeWord- the HASH buffer size in words
 *
 * @return DxError_t 		- On success: the value DX_OK is returned, 
 *         			  On failure: a value from sbrom_management_error.h
 */    
DxError_t DX_MNG_GetPubKeyHash(	unsigned long hwBaseAddress, 
				DxSbPubKeyIndexType_t keyIndex,
				uint32_t *hashedPubKey,
				uint32_t hashResultSizeWords);

/*!
 * @brief This function is used to generate and lock the provisioning key. 
 * 	  Atfer it computes AES-CMAC with KCP key, it load 0 to the AES engine key. 
 *
 * @param[in] hwBaseAddress 	- cryptocell base address
 * @param[out] macResult 	- AES CMAC output buffer 
 *
 * @return DxError_t 		- On success: the value DX_OK is returned, 
 *         			  On failure: a value from sbrom_management_error.h
 */      
DxError_t DX_MNG_GetProvisionKey(unsigned long hwBaseAddress,
				 DxMngAesCmacResult_t macResult);


/*!
 * @brief This function sets the "disable security" flag in the OTP manager,
 * 	  and writes a zero session key to lock the setting in place.
 *
 * @param[in] hwBaseAddress 	- cryptocell base address
 *
 * @return DxError_t 		- On success: the value DX_OK is returned, 
 *         			  On failure: a value from sbrom_management_error.h
 */   
DxError_t DX_MNG_DisableSecurity(unsigned long hwBaseAddress);


/*!
 * @brief This function gets the TRNG characterization information from the OTP (Manufacturer-Programmed Flags).
 *
 * @param[in] hwBaseAddress 	- cryptocell base address
 * @param[out] trngParams 	- bits [12:0] - TRNG characterization information.
 *
 * @return DxError_t 		- On success: the value DX_OK is returned, 
 *         			  On failure: a value from sbrom_management_error.h
 */ 
DxError_t DX_MNG_GetTrngInfo (unsigned long hwBaseAddress,
			      uint32_t *trngParams);

/*!
 * @brief This function retrieves the minimum SW version from the OTP memory.
 *        It receives a counter index (indicating whether to read the counter for trusted firmware upgrades or
 *        non-trusted firmware upgrades), and returns the requested version (number of bits set within the
 *        specified field).
 *
 * @param[in] hwBaseAddress 	- cryptocell base address 
 * @param[in] counterId 	- sw revocation counter ID 
 * @param[out] swVersion	- the sw version value (number of bits set in the OTP )
 *
 * @return DxError_t 		- On success: the value DX_OK is returned, 
 *         			  On failure: a value from sbrom_management_error.h
 */    
DxError_t DX_MNG_GetSwVersion(unsigned long hwBaseAddress, DxSbSwVersionId_t counterNum, uint32_t *swVersion);

/*!
 * @brief This function writes the minimum SW version to the OTP memory.
 *        It receives a counter index (indicating whether to read the counter for trusted firmware upgrades or
 *        non-trusted firmware upgrades), and encodes the given counter value to base-1 representation
 *        (This is monotonic anti-rollback counter).
 *
 * @param[in] hwBaseAddress 	- cryptocell base address 
 * @param[in] counterId 	- sw revocation counter ID 
 * @param[in] swVersion		- the new sw version
 * 				  (note: it is the number of bits that should be set in the OTP memory)
 *
 * @return DxError_t 		- On success: the value DX_OK is returned, 
 *         			  On failure: a value from sbrom_management_error.h
 */    
DxError_t DX_MNG_SetSwVersion(unsigned long hwBaseAddress, DxSbSwVersionId_t counterId, uint32_t swVersion);

/*!
 * @brief This function retrieves the code encryption key (Kce) from the OTP memory,
 *        returning either the key or an error indication if the number of zero bits in Kce does not
 *        match the zero-count field in the OEM flags word in OTP memory.
 * 
 * @param[in] hwBaseAddress 	- cryptocell base address
 * @param[out] codeEncryptionKey- a pointer to store the Kce buffer
 *
 * @return DxError_t 		- On success: the value DX_OK is returned, 
 *         			  On failure: a value from sbrom_management_error.h
 */    
DxError_t DX_MNG_GetCodeEncryptionKey(unsigned long hwBaseAddress, DxMngAesKey_t codeEncryptionKey);


/*!
 * @brief This function computes and outputs the device's SOC_ID as AES-CMAC with secret key based on KDR,
 * 	  and input data that compose of boot-public-key-hash.
 *
 * @param[in] hwBaseAddress 	- cryptocell base address
 * @param[out] hashResult 	- SHA256 output buffer 
 *
 * @return DxError_t 		- On success: the value DX_OK is returned, 
 *         			  On failure: a value from sbrom_management_error.h
 */      
DxError_t DX_MNG_ComputeSOC_ID(unsigned long hwBaseAddress, HASH_Result_t hashResult);

/*!
 * @brief This function sets RMA bit in the manufacture flags word in the OTP.
 *
 * @param[in] hwBaseAddress 	- cryptocell base address
 *
 * @return DxError_t 		- On success: the value DX_OK is returned, 
 *         			  On failure: a value from sbrom_management_error.h
 */
DxError_t DX_MNG_SetRmaMode(unsigned long hwBaseAddress);



/*! 
 * @brief sets 31 low bits of DCU register in case LCS=CM or RMA; and lock DCU
 *
 * @param[in] hwBaseAddress 	- cryptocell base address
 * @param[in] dcuVal 	   	- [0:30] DCU new value
 * 				  [31] ignored
 * @return DxError_t 		- On success: the value DX_OK is returned, 
 *         			  On failure: a value from sbrom_management_error.h
 */
DxError_t DX_MNG_SetDCU(unsigned long   hwBaseAddress,
			uint32_t   dcuVal);

/*!
 * This function backup/restore on-chip secure RAM to/from external DRAM: 
 * It encrypts/decrypts the provided block (using the always-on state counter and destination address to construct the AES-CTR nonce);
 * Also, computes AES-CMAC signature, and appends/verifiys the signature.
 *  
 * @param[in] hwBaseAddress 	- cryptocell base address 
 * @param[in] srcAddr		- input Host memory address (aligned to 32bit).
 * @param[in] dstAddr		- output Host mamory address (aligned to 32bit).  
 * @param[in] blockSize 	- number of bytes to process (must be aligned to word boundaries).
 * @param[in] isSramBackup 	- if TRUE, SRAM backup; else, SRAM restore
 *  
 * 
 * @return DxError_t 		- On success: the value DX_OK is returned, 
 *         			  On failure: a value from sbrom_management_error.h
 * 
 */
DxError_t DX_MNG_ExtRamBackupAndRestore(unsigned long hwBaseAddress,	
					uint64_t srcAddr,
					uint64_t dstAddr,
					uint32_t blockSize,
					DxBool_t isSramBackup);


#define DX_MNG_ExtRamBackup(hwBaseAddress, srcAddr, dstAddr, blockSize)	\
	DX_MNG_ExtRamBackupAndRestore(hwBaseAddress, srcAddr, dstAddr, blockSize, DX_TRUE)


#define DX_MNG_ExtRamRestore(hwBaseAddress, srcAddr, dstAddr, blockSize)	\
	DX_MNG_ExtRamBackupAndRestore(hwBaseAddress, srcAddr, dstAddr, blockSize, DX_FALSE)



#ifdef __cplusplus
}
#endif

#endif



