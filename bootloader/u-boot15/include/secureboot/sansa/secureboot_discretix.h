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

 
#ifndef _SECUREBOOT_DISCRETIX_H
#define _SECUREBOOT_DISCRETIX_H

/*
 * All the includes that are needed for code using this module to
 * compile correctly should be #included here.
 */
#include "secureboot_basetypes.h"
#include "secureboot_error.h"
#ifdef DX_SB_CERT_SUPPORTED
#include "bootimagesverifierx509_def.h"
#include "bootimagesverifierx509_api.h"
#else
#include "bootimagesverifier_def.h"
#include "bootimagesverifier_api.h"
#endif



#endif


