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

#include "mv_hypercalls.h"
#include "vmcalls.h"

#define VMCALL_OPCODE   ".byte 0x0f,0x01,0xc1\n"

#define UNUSED_ARG  0
#define UNUSED_PTR_ARG  NULL

#ifndef __KERNEL__
/*
 * These are the place holders for functions to trace VMCALL entry / exit, and
 * needed as this file is built into lib_guest.a which the guest is linked.
 * The guest should implement its own functions to replace them if needed.
 */
void __attribute__ ((weak)) mv_guest_trace_vmcall_entry(uint32_t nr,
						uint32_t svc, uint32_t op);
void __attribute__ ((weak)) mv_guest_trace_vmcall_exit(void);
void __attribute__ ((weak)) mv_guest_trace_xirq_post(uint32_t xirq);
void __attribute__ ((weak)) mv_guest_trace_ipi_post(uint32_t virq);
void __attribute__ ((weak)) mv_guest_trace_virq_mask(uint32_t virq);
void __attribute__ ((weak)) mv_guest_trace_virq_unmask(uint32_t virq);

void mv_guest_trace_vmcall_entry(uint32_t nr, uint32_t svc, uint32_t op)
{
	(void)nr;
	(void)svc;
	(void)op;
}

void mv_guest_trace_vmcall_exit(void)
{
}

void mv_guest_trace_xirq_post(uint32_t xirq)
{
	(void)xirq;
}

void mv_guest_trace_ipi_post(uint32_t virq)
{
	(void)virq;
}

void mv_guest_trace_virq_mask(uint32_t virq)
{
	(void)virq;
}

void mv_guest_trace_virq_unmask(uint32_t virq)
{
	(void)virq;
}
#endif

static inline int32_t mv_call(uint32_t nr, uint32_t arg0,
			      uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
	uint32_t ret = 0;

#ifndef __KERNEL__
	mv_guest_trace_vmcall_entry(nr, arg0, arg1);
#endif
	asm volatile (VMCALL_OPCODE:"=a"(ret)
		      : "a"(nr), "b"(arg0), "c"(arg1), "d"(arg2), "S"(arg3)
		      : "memory");
#ifndef __KERNEL__
	mv_guest_trace_vmcall_exit();
#endif

	return ret;
}

static inline int mv_call_5(uint32_t nr, uint32_t arg0,
			    uint32_t arg1, uint32_t arg2,
			    uint32_t arg3, uint32_t *ret0,
			    uint32_t *ret1, uint32_t *ret2,
			    uint32_t *ret3, uint32_t *ret4)
{
	uint32_t results[5];

#ifndef __KERNEL__
	mv_guest_trace_vmcall_entry(nr, arg0, arg1);
#endif
	asm volatile (VMCALL_OPCODE:"=a"(results[0]), "=b"(results[1]),
		      "=c"(results[2]), "=d"(results[3]), "=S"(results[4])
		      : "a"(nr), "b"(arg0), "c"(arg1), "d"(arg2), "S"(arg3)
		      : "memory");
#ifndef __KERNEL__
	mv_guest_trace_vmcall_exit();
#endif

	if (ret0)
		*ret0 = results[0];
	if (ret1)
		*ret1 = results[1];
	if (ret2)
		*ret2 = results[2];
	if (ret3)
		*ret3 = results[3];
	if (ret4)
		*ret4 = results[4];

	return results[0];
}

void mv_idle(void)
{
	mv_call(VMCALL_IDLE, UNUSED_ARG, UNUSED_ARG, UNUSED_ARG, UNUSED_ARG);
}

uint32_t mv_vcpu_id(void)
{
	return mv_call(VMCALL_VCPU_ID, UNUSED_ARG, UNUSED_ARG, UNUSED_ARG,
		       UNUSED_ARG);
}

void mv_hirq_ready(void)
{
	mv_call(VMCALL_VIRQ_READY, UNUSED_ARG, UNUSED_ARG, UNUSED_ARG,
		UNUSED_ARG);
}

void mv_virq_request(uint32_t virq, uint32_t vaffinity)
{
	mv_call(VMCALL_VIRQ_REQUEST, virq, vaffinity, UNUSED_ARG, UNUSED_ARG);
}

void mv_virq_eoi(uint32_t virq)
{
	mv_call(VMCALL_VIRQ_EOI, virq, UNUSED_ARG, UNUSED_ARG, UNUSED_ARG);
}

void mv_virq_mask(uint32_t virq)
{
#ifndef __KERNEL__
	mv_guest_trace_virq_mask(virq);
#endif
	mv_call(VMCALL_VIRQ_MASK, virq, UNUSED_ARG, UNUSED_ARG, UNUSED_ARG);
}

void mv_virq_unmask(uint32_t virq)
{
#ifndef __KERNEL__
	mv_guest_trace_virq_unmask(virq);
#endif
	mv_call(VMCALL_VIRQ_UNMASK, virq, UNUSED_ARG, UNUSED_ARG, UNUSED_ARG);
}

void mv_virq_set_affinity(uint32_t virq, uint32_t vaffinity)
{
	mv_call(VMCALL_VIRQ_SET_AFFINITY, virq, vaffinity, UNUSED_ARG,
		UNUSED_ARG);
}

/* Trigger an IPI to the specified vcpus bitmap */
void mv_ipi_post(uint32_t virq, uint32_t vcpus)
{
#ifndef __KERNEL__
	mv_guest_trace_ipi_post(virq);
#endif
	mv_call(VMCALL_IPI_POST, virq, vcpus, UNUSED_ARG, UNUSED_ARG);
}

void mv_vcpu_start(uint32_t vcpu_id, uint32_t entry_addr)
{
	mv_call(VMCALL_VCPU_START, vcpu_id, entry_addr, UNUSED_ARG, UNUSED_ARG);
}

void mv_vcpu_stop(uint32_t vcpu_id)
{
	mv_call(VMCALL_VCPU_STOP, vcpu_id, UNUSED_ARG, UNUSED_ARG, UNUSED_ARG);
}

phys_addr_t mv_vcpu_get_data(void)
{
	return mv_call(VMCALL_VCPU_GET_DATA,
			UNUSED_ARG, UNUSED_ARG,
			UNUSED_ARG, UNUSED_ARG);
}

int mv_vcpu_has_irq_pending(void)
{
	return (int)mv_call(VMCALL_VCPU_HAS_IRQ_PENDING, UNUSED_ARG,
			    UNUSED_ARG, UNUSED_ARG, UNUSED_ARG);
}

uint32_t mv_get_running_guests(void)
{
	return (uint32_t) mv_call(VMCALL_GET_RUNNING_GUESTS, UNUSED_ARG,
				  UNUSED_ARG, UNUSED_ARG, UNUSED_ARG);
}

int mv_initiate_reboot(uint32_t reboot_action)
{
	return (int)mv_call(VMCALL_INITIATE_REBOOT, reboot_action,
			    UNUSED_ARG, UNUSED_ARG, UNUSED_ARG);
}

void mv_virq_spurious(uint32_t virq)
{
	mv_call(VMCALL_VIRQ_SPURIOUS, virq, UNUSED_ARG, UNUSED_ARG, UNUSED_ARG);
}

uint32_t mv_mbox_get_info(uint32_t id, uint32_t instance,
			  uint32_t *p_mbox_db_guest_entry)
{
	return (uint32_t) mv_call_5(VMCALL_MBOX_GET_INFO, id, instance,
				    UNUSED_ARG, UNUSED_ARG, UNUSED_ARG,
				    UNUSED_ARG, p_mbox_db_guest_entry,
				    UNUSED_ARG, UNUSED_ARG);
}

uint32_t mv_mbox_get_directory(void)
{
	return (uint32_t) mv_call(VMCALL_MBOX_GET_DIRECTORY, UNUSED_ARG,
				  UNUSED_ARG, UNUSED_ARG, UNUSED_ARG);
}

void mv_mbox_set_online(uint32_t token)
{
	mv_call(VMCALL_MBOX_SET_ONLINE, token, UNUSED_ARG, UNUSED_ARG,
		UNUSED_ARG);
}

void mv_mbox_set_offline(uint32_t token)
{
	mv_call(VMCALL_MBOX_SET_OFFLINE, token, UNUSED_ARG, UNUSED_ARG,
		UNUSED_ARG);
}

void mv_mbox_post(uint32_t token, uint32_t hirq)
{
	mv_call(VMCALL_MBOX_POST, token, hirq, UNUSED_ARG, UNUSED_ARG);
}

void mv_vm_start(uint32_t vm_id)
{
	mv_call(VMCALL_VM_START, vm_id, UNUSED_ARG, UNUSED_ARG, UNUSED_ARG);
}

void mv_vm_stop(uint32_t vm_id)
{
	mv_call(VMCALL_VM_STOP, vm_id, UNUSED_ARG, UNUSED_ARG, UNUSED_ARG);
}

void mv_get_cpu_map(uint32_t *vcpu_map, uint32_t *shared_cpu_map,
		uint32_t *apic_map, uint32_t *num_of_cpus)
{
	mv_call_5(VMCALL_GET_CPU_MAP, UNUSED_ARG, UNUSED_ARG, UNUSED_ARG,
		  UNUSED_ARG, UNUSED_ARG, vcpu_map, shared_cpu_map, apic_map,
		  num_of_cpus);
}

uint32_t mv_platform_service(uint32_t service_type, uint32_t arg1,
			uint32_t arg2, uint32_t arg3, uint32_t arg4,
			uint32_t *ret0, uint32_t *ret1, uint32_t *ret2,
			uint32_t *ret3, uint32_t *ret4)
{
	return mv_call_5(service_type, arg1, arg2,
			 arg3, arg4, ret0, ret1, ret2, ret3, ret4);
}
