/* ----------------------------------------------------------------------------
   Copyright (C) 2014 Intel Mobile Communications GmbH

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License Version 2
 *  as published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  You should have received a copy of the GNU General Public License Version 2
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.

  ---------------------------------------------------------------------------*/
/*
 * NOTES:
 * 1) This source file is included in guests including Linux and purposely
 * kept in line with Linux kernel coding guidelines for ease of portability and
 * maintainability. See linux/Documentation/CodingStyle for coding guidelines.
 * Please check all further changes are compliant with Linux coding standard
 * and clear all commands reported by Linux checkpatch.pl
 * Use command: linux/scripts/checkpatch.pl -f <filename>
 * Clear ALL warnings and errors reported.
 *
 * 2) Use only C99 fixed width types for definition as this header needs to be
 * both 32bit/64bit portable.
 * Avoid the use of pointers/enum in structure as that make the structure
 * variable size based on 32/64bit toolchain used.
*/
#ifndef _MV_SVC_SECURITY_H
#define _MV_SVC_SECURITY_H

#define SECURITY_API_VER		1
#define SECURITY_API_MIN_VER		1

/**
 @brief Mobilevisor platform security verify vm complete service
 @param vm verify result and vm id
**/
int32_t mv_svc_security_verify_vm_completed(uint32_t verify_result,
						uint32_t vm_id);
/**
 @brief Mobilevisor platform security getvm loadinfo service
 @param vm id
 @return value vm load address and size
**/
int32_t mv_svc_security_getvm_loadinfo(uint32_t vm_id, uint32_t *vm_loadaddr,
					uint32_t *vm_loadsize);

#endif /* _MV_SVC_SECURITY_H */
