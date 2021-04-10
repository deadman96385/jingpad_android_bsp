/* ----------------------------------------------------------------------------
 *  Copyright (C) 2015 Intel Corporation

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
#ifndef _VMCALLS_H
#define _VMCALLS_H

enum vmcall_opcode {
	VMCALL_FIRST = 0x10000000,
	VMCALL_IDLE = VMCALL_FIRST,
	VMCALL_VCPU_ID,
	VMCALL_VIRQ_READY,
	VMCALL_VIRQ_REQUEST,
	VMCALL_VIRQ_EOI,
	VMCALL_VIRQ_MASK,
	VMCALL_VIRQ_UNMASK,
	VMCALL_VIRQ_SET_AFFINITY,
	VMCALL_VIRQ_SPURIOUS,
	VMCALL_IPI_POST,
	VMCALL_VCPU_START,
	VMCALL_VCPU_STOP,
	VMCALL_VCPU_GET_DATA,
	VMCALL_VCPU_HAS_IRQ_PENDING,
	VMCALL_GET_RUNNING_GUESTS,
	VMCALL_INITIATE_REBOOT,
	VMCALL_VM_START,
	VMCALL_VM_STOP,
	VMCALL_MBOX_GET_DIRECTORY,
	VMCALL_MBOX_GET_INFO,
	VMCALL_MBOX_SET_ONLINE,
	VMCALL_MBOX_SET_OFFLINE,
	VMCALL_MBOX_POST,
	VMCALL_GET_CPU_MAP,
	VMCALL_GET_VM_LOADINFO,
	VMCALL_VMM_LOG,
	VMCALL_VMM_TRACE,
	VMCALL_LAST = VMCALL_VMM_TRACE,
};

#endif				/* _VMCALLS_H */
