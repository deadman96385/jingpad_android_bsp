/* ----------------------------------------------------------------------------
   Copyright (C) 2015 Intel Corporation

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

/* For inclusion by Guest VMs only! */

#ifndef _MV_SVC_HYPERCALLS_H
#define _MV_SVC_HYPERCALLS_H

#include "mv_service_list.h"

extern struct mv_shared_data *mv_shared_data[];

extern void mv_svc_pinctrl_init(void);
extern void mv_svc_pm_init(void);
extern void mv_svc_sys_exception_init(void);
extern void mv_svc_coredump_init(void);
extern void mv_svc_socwatch_init(void);
extern void mv_svc_sep_init(void);
extern void mv_svc_watchdog_init(void);
extern void mv_svc_sysprof_init(void);
extern void mv_svc_reg_access_init(void);
extern void mv_svc_pmic_reg_access_init(void);
extern void mv_svc_vtimer_init(void);
extern void mv_svc_rtc_init(void);
extern void mv_svc_spcu_thermal_init(void);
extern void mv_svc_pwm_init(void);
extern void mv_svc_security_init(void);
extern void mv_svc_silent_lake_init(void);
extern void mv_svc_log_init(void);

/**
 * @brief Query the Mobilevisor on the platform service with the given
 * unique ID.
 * Mobilevisor will return the availability of the service, the version
 * info as well as the shared memory information if applicable.
 *
 * Before the guest VM can invoke any platform service, it is mandatory
 * for the VM to make this hypercall. In addition to the availability
 * check, it should also perform the versioning check to ensure that the
 * platform service is compatible with the currently compiled guest.
 *
 * @param service_id The unique platform service ID (input)
 * @param current_version Current version of the service (output)
 * @param min_compatible_version Minimum compatible version of the
 * service (output)
 * @param shared_mem_offset Offset address in VCPU/VMM shared memory for
 * start address of the shared memory. If the service does not use shared
 * memory, NULL will be returned.(output)
 * @param shared_mem_size Size of the shared memory. 0 if the service does
 * not use shared memory (output)
 * @return return 1 if service is available, 0 otherwise
**/
uint32_t mv_svc_get_service_info(enum mv_service_id service_id,
	uint32_t *current_version,
	uint32_t *min_compatible_version,
	uint32_t *shared_mem_offset,
	uint32_t *shared_mem_size);

/**
 @return struct pal_shared_data * physical address to per VCPU-Mobilevisor
				  platform shared data structure
**/
struct pal_shared_data *mv_svc_get_shared_data(void);

#endif /* _MV_SVC_HYPERCALLS_H */
