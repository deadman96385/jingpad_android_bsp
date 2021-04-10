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
/*
 * WARNING:
 * If any files in pal/platforms/<platform>/service are modified,
 * ensure the regenerated lib_mobilevisor_platform_service.a into
 * pal/release/$(PROJECTFOLDER)/lib_guest/ folder for commit
 * Use command: "make release"
*/

/*
 * WARNING:
  * Always use portable C99 fixed width types for 64bit/32bit compatibility.
*/
#include "../mv_gal.h"
#include "../mv_service_list.h"
#include "../mv_hypercalls.h"
#include "../mv_gal.h"
#include "../mv_svc_hypercalls.h"
#include "../security/mv_svc_security.h"

static int initialized;
void mv_svc_security_init(void)
{
	uint32_t current_version, min_compatible_version;
	uint32_t shared_mem_offset, shared_mem_size;

	if (!mv_svc_get_service_info(VMM_SECURITY_SERVICE, &current_version,
		&min_compatible_version, &shared_mem_offset, &shared_mem_size))
		return;

	if (min_compatible_version > SECURITY_API_VER) {
		mv_gal_panic("attempt to invoke a non-available service: security\n");
		return;
	}

	initialized = 1;
}

static void security_service_ensure_init(void)
{
	if (!initialized)
		mv_gal_panic("security service is not initialized\n");
}

int32_t mv_svc_security_verify_vm_completed(uint32_t verify_result,
			uint32_t vm_id)
{
	security_service_ensure_init();
	return mv_platform_service(OPCODE_SECURITY_VERIFY_VM_COMPLETED,
		verify_result, vm_id, 0, 0, 0, 0, 0, 0, 0);
}

#ifdef __KERNEL__
EXPORT_SYMBOL(mv_svc_security_verify_vm_completed);
#endif

int32_t mv_svc_security_mem_cleanup_done(uint32_t vm_id)
{
	security_service_ensure_init();
	return mv_platform_service(OPCODE_SECURITY_MEM_CLEANUP_DONE,
		vm_id, 0, 0, 0, 0, 0, 0, 0, 0);
}

#ifdef __KERNEL__
EXPORT_SYMBOL(mv_svc_security_mem_cleanup_done);
#endif

int32_t mv_svc_security_getvm_loadinfo(uint32_t vm_id, uint32_t *vm_loadaddr,
		uint32_t *vm_loadsize)
{
	security_service_ensure_init();
	return mv_platform_service(OPCODE_SECURITY_GETVM_LOADINFO,
		vm_id, 0, 0, 0, 0, 0, 0, vm_loadaddr, vm_loadsize);
}

#ifdef __KERNEL__
EXPORT_SYMBOL(mv_svc_security_getvm_loadinfo);
#endif

uint32_t mv_svc_security_secure_buffer_request(unsigned int enable,
		uint32_t buf_address, uint32_t buf_size)
{
	security_service_ensure_init();
	return mv_platform_service(OPCODE_SECURITY_SECURE_BUFFER_REQUEST,
		enable, buf_address, buf_size, 0, 0, 0, 0, 0, 0);
}

#ifdef __KERNEL__
EXPORT_SYMBOL(mv_svc_security_secure_buffer_request);
#endif

uint32_t mv_svc_ivmc_request(uint32_t vm_id)
{
    security_service_ensure_init();
    return mv_platform_service(OPCODE_IVMC_REQUEST,
            vm_id, 0, 0, 0, 0, 0, 0, 0, 0);
}

#ifdef __KERNEL__
EXPORT_SYMBOL(mv_svc_ivmc_request);
#endif

uint32_t mv_svc_ivmc_response(uint32_t result)
{
    security_service_ensure_init();
    return mv_platform_service(OPCODE_IVMC_RESPONSE,
            result, 0, 0, 0, 0, 0, 0, 0, 0);
}

#ifdef __KERNEL__
EXPORT_SYMBOL(mv_svc_ivmc_response);
#endif
