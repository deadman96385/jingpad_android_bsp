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
#include "mv_gal.h"
#include "mv_hypercalls.h"
#include "mv_svc_hypercalls.h"


void (*vmm_service_init_handlers[VMM_LAST_SERVICE+1])(void) = {
	mv_svc_pinctrl_init,
	mv_svc_pm_init,
	mv_svc_sys_exception_init,
	mv_svc_coredump_init,
	mv_svc_socwatch_init,
	mv_svc_sep_init,
	mv_svc_watchdog_init,
	mv_svc_sysprof_init,
	mv_svc_reg_access_init,
	mv_svc_pmic_reg_access_init,
	mv_svc_vtimer_init,
	mv_svc_rtc_init,
	mv_svc_spcu_thermal_init,
	mv_svc_pwm_init,
	mv_svc_security_init,
	mv_svc_silent_lake_init,
	mv_svc_log_init,
};

void __attribute__((weak)) mv_svc_pinctrl_init(void) {}
void __attribute__((weak)) mv_svc_pm_init(void) {}
void __attribute__((weak)) mv_svc_sys_exception_init(void) {}
void __attribute__((weak)) mv_svc_coredump_init(void) {}
void __attribute__((weak)) mv_svc_socwatch_init(void) {}
void __attribute__((weak)) mv_svc_sep_init(void) {}
void __attribute__((weak)) mv_svc_watchdog_init(void) {}
void __attribute__((weak)) mv_svc_sysprof_init(void) {}
void __attribute__((weak)) mv_svc_reg_access_init(void) {}
void __attribute__((weak)) mv_svc_pmic_reg_access_init(void) {}
void __attribute__((weak)) mv_svc_vtimer_init(void) {}
void __attribute__((weak)) mv_svc_rtc_init(void) {}
void __attribute__((weak)) mv_svc_spcu_thermal_init(void) {}
void __attribute__((weak)) mv_svc_pwm_init(void) {}
void __attribute__((weak)) mv_svc_security_init(void) {}
void __attribute__((weak)) mv_svc_silent_lake_init(void) {}
void __attribute__((weak)) mv_svc_log_init(void) {}

uint32_t mv_svc_get_service_info(enum mv_service_id service_id,
		uint32_t *current_version,
		uint32_t *min_compatible_version,
		uint32_t *shared_mem_offset,
		uint32_t *shared_mem_size)
{
	return mv_platform_service(OPCODE_SERVICE_INFO, service_id, 0,
		0, 0, 0, current_version, min_compatible_version,
		shared_mem_offset, shared_mem_size);
}


