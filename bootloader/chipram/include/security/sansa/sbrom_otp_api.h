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



#ifndef _SBROM_OTP_API_H
#define _SBROM_OTP_API_H

#ifdef __cplusplus
extern "C"
{
#endif


/*!
 * @brief This function retrives a 32bit word from the OTP memory. 	  
 *
 * @param[in] hwBaseAddress 	- cryptocell base address 
 * @param[in] otpAddress	- Address in OTP [in Words]
 * @param[out] otpWord		- the returned OTP word
 *
 * @return DxError_t 		- On success: the value DX_OK is returned, 
 *         			  On failure: a value from sbrom_management_error.h
 */    
DxError_t DX_MNG_ReadOTPWord(unsigned long hwBaseAddress, uint32_t otpAddress, uint32_t *otpWord);


/*!
 * @brief This function receives a 32-bit word, and burn it to the OTP memory.
 *      Note:
 *      The customer should develop the required implementation for programming the OTP bit-by-bit (no more than once).  
 *
 * @param[in] hwBaseAddress 	- cryptocell base address 
 * @param[in] otpAddress	- Address in OTP [in Words]
 * @param[in] otpWord		- OTP 32bit word 
 *
 * @return DxError_t 		- On success: the value DX_OK is returned, 
 *         			  On failure: a value from sbrom_management_error.h
 */    
DxError_t DX_MNG_WriteOTPWord(unsigned long hwBaseAddress, uint32_t otpAddress, uint32_t otpWord);


#ifdef __cplusplus
}
#endif

#endif



