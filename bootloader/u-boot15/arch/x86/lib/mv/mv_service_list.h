/* ----------------------------------------------------------------------------
 *  Copyright (C) 2014 Intel Mobile Communications GmbH

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
*/

#ifndef _MV_SERVICE_LIST_H
#define _MV_SERVICE_LIST_H

/**
 *  @brief enumeration platform dependent service id
*/
enum mv_service_id {
	VMM_FIRST_SERVICE = 0,
	VMM_PINCTRL_SERVICE = VMM_FIRST_SERVICE,
	VMM_PM_SERVICE,
	VMM_SYS_EXCEPTION_SERVICE,
	VMM_COREDUMP_SERVICE,
	VMM_SOCWATCH_SERVICE,
	VMM_SEP_SERVICE,
	VMM_WATCHDOG_SERVICE,
	VMM_SYSPROF_SERVICE,
	VMM_REG_ACCESS_SERVICE,
	VMM_PMIC_REG_ACCESS_SERVICE,
	VMM_VTIMER_SERVICE,
	VMM_RTC_SERVICE,
	VMM_SPCU_THERMAL_SERVICE,
	VMM_PWM_SERVICE,
	VMM_SECURITY_SERVICE,
	VMM_SILENT_LAKE_SERVICE,
	VMM_LOG_SERVICE,
	VMM_LAST_SERVICE = VMM_LOG_SERVICE
};

extern void (*vmm_service_init_handlers[VMM_LAST_SERVICE+1])(void);

/** @typedef vmm_platform_service_opcode
 *
 *  @brief enumeration platform dependent service opcode
 *  which is used in vmcall handlers
*/
enum mv_service_opcode {
	OPCODE_SERVICE_FIRST = 0x20000000,
	OPCODE_SERVICE_INFO = OPCODE_SERVICE_FIRST,
	OPCODE_PINCTRL,
	OPCODE_PM,
	OPCODE_SYS_EXCEPTION,
	OPCODE_CD,
	OPCODE_SOCWATCH,
	OPCODE_SEP,
	OPCODE_WATCHDOG,
	OPCODE_SYSPROF,
	OPCODE_REG_RD,
	OPCODE_REG_WR,
	OPCODE_REG_WR_ONLY,
	OPCODE_PMIC_REG_ACCESS,
	OPCODE_VTIMER_START,
	OPCODE_VTIMER_STOP,
	OPCODE_VTIMER_GET_FREQ,
	OPCODE_TIMESTAMP_COUNTER_INFO,
	OPCODE_RTC,
	OPCODE_SPCU_THERMAL,
	OPCODE_PWM,
	OPCODE_SECURITY_VERIFY_VM_COMPLETED,
	OPCODE_SECURITY_MEM_CLEANUP_DONE,
	OPCODE_SECURITY_GETVM_LOADINFO,
	OPCODE_SECURITY_SECURE_BUFFER_REQUEST,
	OPCODE_SILENT_LAKE,
	OPCODE_LOG,
	OPCODE_IVMC_REQUEST,
	OPCODE_IVMC_RESPONSE,
	OPCODE_SERVICE_LAST = OPCODE_IVMC_RESPONSE
};
#endif /* _MV_SERVICE_LIST */
