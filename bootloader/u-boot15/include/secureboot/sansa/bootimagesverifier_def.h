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



#ifndef _BOOT_IMAGES_VERIFIER_DEF_H
#define _BOOT_IMAGES_VERIFIER_DEF_H

#ifdef __cplusplus
extern "C"
{
#endif

//#include <stdint.h>
#include "secureboot_defs.h"

/* General definitions */
/***********************/

/* Certificate Magic number */
#define DX_CERT_MAGIC_NUMBER_DEFAULT_VALUE 0xE291F358

/********* Certificate structure definitions ***********/

/* Certificate Size offset */
#define SB_CERT_SIZE_OFFSET_IN_WORDS 2

/* Certificate Flag offset */
#define SB_CERT_FLAG_OFFSET_IN_WORDS 3

/* 1 . Certificate header structure */
typedef struct {
	/* Magic number to validate certificate */
	uint32_t magicNumber;  

	/* Certificate version to validate certificate */
	uint32_t certVersion;  

	/* Bits [0:15] holds direct offset in words to the Certificate signature, 
	   Bits [16:31] holds the number of sw components , if exist*/   
	uint32_t certSize;

	/* Bits [0:7] holds HBK 
	   Bits [8:15] holds pub key algorithm identifier
	   Bits [16] code encryption
	   Bits [17:18] cert type
	   Bits [19:31] reserved */
	uint32_t certFlags;

}DxSbCertHeader_t;

typedef enum {
	DX_SB_KEY_CERT = 1,
	DX_SB_CONTENT_CERT,
	DX_SB_CERT_TYPE_LAST = 0x7FFFFFFF

}DxSbCertTypes_t;


/********* End of certificate structure definitions ***********/

/* Define workspace minimum size */
#define DX_SB_MAX_CERT_PKG_SIZE_IN_BYTES	2048
#define DX_SB_MIN_WORKSPACE_SIZE_IN_BYTES 	DX_DOUBLE_BUFFER_MAX_SIZE_IN_BYTES + DX_SB_MAX_CERT_PKG_SIZE_IN_BYTES


#ifdef __cplusplus
}
#endif

#endif


