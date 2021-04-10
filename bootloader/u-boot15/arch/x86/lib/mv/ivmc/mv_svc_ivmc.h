/* ----------------------------------------------------------------------------
   Copyright (C) 2013 Intel Mobile Communications GmbH

	Sec Class: Intel Confidential (IC)

   All rights reserved.
   ----------------------------------------------------------------------------
   This document contains proprietary information belonging to IMC.
   Passing on and copying of this document, use
   and communication of its contents is not permitted without prior written
   authorisation.
  ---------------------------------------------------------------------------*/
#ifndef _MV_SVC_IVMC_H
#define _MV_SVC_IVMC_H

/**
 @brief Mobilevisor platform inter-vm message request
 @param vm id
 @return 0 on success, error code other wise.
**/
uint32_t mv_svc_ivmc_request(uint32_t vm_id);

/**
 @brief Mobilevisor platform inter-vm message response 
 @param result
 @return 0 on success, error code other wise.
**/
uint32_t mv_svc_ivmc_response(uint32_t result);

#endif /* _MV_SVC_IVMC_H */
