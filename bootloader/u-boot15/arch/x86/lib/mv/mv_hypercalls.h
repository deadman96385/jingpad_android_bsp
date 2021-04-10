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
 * 2) Use only C99 fixed width types for definition as this header needs to be
 * both 32bit/64bit portable.
 * Avoid the use of pointers/enum in structure as that make the structure
 * variable size based on 32/64bit toolchain used.
*/

/* For inclusion by Guest VMs only! */

#ifndef _MV_HYPERCALLS_H
#define _MV_HYPERCALLS_H

#include "mv_ipc.h"

#define VMM_HIRQ_VECTOR 33

#define VMM_HIRQ_START      512
#define VMM_HIRQ_END        1024

/* NOTE: must be consistent with mvconfig.h */
#define CONFIG_MAX_VCPUS_PER_VM 8

#define mv_id_t uint32_t

/*NOTE: this hirq_info stuff must be consistent with guest_vm.h */
struct hirq_info_t {
	uint32_t host_pending_flag;
	uint32_t lvl1;
	uint32_t lvl2[16];
};

struct vcpu_stolen_cpu_time_stats {
	/*
	 * accumulated counter for cpu time taken away from vcpu
	 * while it was active (preempted)
	 */
	volatile uint64_t active_stolen_cpu_count;

	/*
	 * accumulated counter for cpu time taken away from vcpu
	 * while it was idle
	 */
	volatile uint64_t idle_stolen_cpu_count;

	/* period for stolen cpu time counters in nsec */
	uint32_t stolen_cpu_counter_period_nsec;

} __attribute__((packed));

/**
 * @brief Shared data between the MobileVisor and the guest
 *
 * This data structure defines the shared data between
 * the MobileVisor and the guest.
 */
struct mv_shared_data {
	/** @brief Guest OS ID
	 *
	 * Each guest has a unique ID. This is used for various
	 * IPC APIs such as xirq posting.
	 * For SMP guests, each VCPU will have the same OS ID.
	 */
	const uint32_t os_id;

	/** @brief Shared memory start address
	 *
	 * This field contains the physical start address for
	 * the shared memory region.
	 * The guest is expected to map in the shared memory
	 * region into its virtual address space.
	 */
	const uint64_t ivmc_shmem_paddr;

	/** @brief Shared memory size
	 *
	 * This field contains the size of the shared memory region.
	 * The guest is expected to map in the shared memory region
	 * into its virtual address space.
	 */
	const uint64_t ivmc_shmem_size;

	/** @brief Secured shared memory start address
	 *
	 * This field contains the physical start address for
	 * the secured shared memory region.
	 * The guest is expected to map in the secured shared memory
	 * region into its virtual address space.
	 */
	const uint64_t ivmc_sec_shmem_paddr;

	/** @brief Secured shared memory size
	 *
	 * This field contains the size of the secured shared memory
	 * region.
	 * The guest is expected to map in the secured shared memory
	 * region into its virtual address space.
	 */
	const uint64_t ivmc_sec_shmem_size;


	/** @brief OS command line for the guest
	 *
	 * Each guest will have a command line. Apart from the usual
	 * parameters (e.g. in the case of Linux), it also contains
	  * the virtual device information
	 */
	const int8_t vm_cmdline[512];

	/** @brief hirq info exchanged between guest and host
	 *
	 **/
	struct hirq_info_t hirq_info;

	/** @brief PM control shared data
	 *
	 */
	/*pm_control_shared_data_t pm_control_shared_data; */

	/** @brief System idle flag
	 *
	 * Only used by VCPU who is the power manager owner for a physical CPU
	 * If set, indicates that system is idle,
	 * i.e. no pending tasks or interrupts
	 */
	volatile uint32_t system_idle;

	/** @brief Platform reboot initiation status
	 *
	 * Indicates if a platform reboot has been initiated.
	 * If >0, platform reboot has been initiated,
	 * guests should perform reboot housecleaning accordingly.
	 * and finally invoke VMCALL_STOP_VCPU for each vcpu.
	 */
	const volatile uint32_t is_platform_reboot_initiated;

	/** @brief VCPU stolen cpu time stats
	 *
	 * This gives stats of cpu time stolen from vcpu
	 * while it was active/idle.
	 */
	struct vcpu_stolen_cpu_time_stats stolen_cpu_time_stats;

	/** @brief Shared data for pal
	 *
	 * This is used internally for PAL shared data
	 */
	uint32_t pal_shared_mem_data[256];
} __attribute__((packed));

enum vmmlog_buf_status {
	VMMLOG_BUFFER_INVALID = 0,
	VMMLOG_BUFFER_VALID,
	VMMLOG_BUFFER_CONSUMED,
};

struct vmmlog_buffer {
	uint64_t buf_ptr;      /* pointer to buffer. VM write, VMM read */
	uint32_t buf_size;     /* total size of buffer. VM write, VMM read */
	uint32_t buf_data_len; /* data length of buffer. VMM write, VM read */
	uint32_t buf_status;   /* status of buffer. both VMM and VM read&write*/
};

#define VMMLOG_BUF_NO_MAX 4
#define VMMLOG_BUF_NO_MIN 2
struct vmmlog_buf_info {
	uint32_t buffer_num;  /* number of allocated buffer */
	uint32_t buf_to_read;  /* buffer to be read */
	uint32_t buf_to_write; /* buffer to be written */
	struct vmmlog_buffer buffers[VMMLOG_BUF_NO_MAX];/* buffer array */
};

enum vmmlog_level {
	VMM_CRIT = 0,	/* VMM critical log level */
	VMM_ERR,		/* VMM Error log level */
	VMM_WARNING,	/* VMM warning log level */
	VMM_INFO,		/* VMM informative log level */
	VMM_DEBUG		/* VMM debug log level */
};

/** @brief Informs MobileVisor that the guest is now idle
 *
 * Upon the idle call, MobileVisor will no longer schedule the guest until
 * an interrupt for this guest arrives.
 */
void mv_idle(void);

/** @brief Retrieves the caller's VCPU ID
 *
 * The guest's VCPU ID is a zero-based number in the range between 0 to n-1
 * where n is the number of VCPUs the guest VM supports
 */
uint32_t mv_vcpu_id(void);

/** @brief Indicate that the vcpu is ready to accept hirqs
 *
 *  @param none
 */
void mv_hirq_ready(void);

/** @brief Connect the virtual interrupt to the guest
 *
 * The specified virq must have a properly configured entry in mvconfig
 * and the calling guest must be the owner of this vector
 *
 * Upon the call, mv will program the IOAPIC for the corresponding
 * interrupt line with the specified vector number. The interrupt will
 * remain masked
 *
 *  @param virq irq vector number.
 *  @param vaffinity specify which vcpu will process this irq.
 */
void mv_virq_request(uint32_t virq, uint32_t vaffinity);

/** @brief EOI a virtual interrupt
 *
 * After virtual interrupt servicing, EOI must be performed in order
 * for the mv to deliver the next interrupt
 *
 *  @param virq irq vector number.
 */
void mv_virq_eoi(uint32_t virq);

/** @brief Mask a virtual interrupt
 *
 * Mask the specifid virtual interrupt. Upon the call, mv will mask the
 * corresponding interrupt line in the IOAPIC
 *
 *  @param virq irq vector number.
 */
void mv_virq_mask(uint32_t virq);

/** @brief Unmask a virtual interrupt
 *
 * Unmasking the specified virtual interrupt. Upon the call, mv will
 * unmask the corresponding interrupt line in the IOAPIC
 *
 *  @param virq irq vector number.
 */
void mv_virq_unmask(uint32_t virq);

/** @brief Set of the affinity of the virtual interrupt
 *
 * Set the VCPU affinity of the virtual interrupt.
 *
 *  @param virq irq vector number.
 *  @param vaffinity specify which vcpu will process this irq.
 */
void mv_virq_set_affinity(uint32_t virq, uint32_t vaffinity);

/**
 *  @brief Report unexpected (spurious) vector to Mobilevisor.
 *
 *  @param vector - spurious vector number
 *
 *  @return None
 */
void mv_virq_spurious(uint32_t vector);

/** @brief Trigger an IPI to the specified vcpus bitmap
 *
 *  @param virq The virq vector number.
 *  @param vcpus Specify which CPUs want to receive this virq.
 */
void mv_ipi_post(uint32_t virq, uint32_t vcpus);

/** @brief Start a secondary VCPU
 *
 *  @param vcpu_id Specify which vcpu is started.
 *  @param entry_addr Specify the vcpu start address.
 */
void mv_vcpu_start(uint32_t vcpu_id, uint32_t entry_addr);

/** @brief Stop a secondary VCPU
 *
 *  @param vcpu_id Specify which vcpu needs to be stopped.
 */
void mv_vcpu_stop(uint32_t vcpu_id);

/** @brief Returns a physical address to the VMM-vcpu shared data
 *    for the calling vcpu
 *
 */
phys_addr_t mv_vcpu_get_data(void);

/** @brief Check if the calling vcpu has any pending interrupts.
 *
 *  @return Return 1 if has.
 */
int32_t mv_vcpu_has_irq_pending(void);

/** @brief Returns mask of currently running guests.
 *
 *  @return The ID of the currenly running guest.
 */
uint32_t mv_get_running_guests(void);

/**
 *  @brief Initate a platform reboot based on desired reboot action.
 *
 *  @param reboot_action If it is set to 0 , then nothing is to be done.
 *  Actual reboot action definition depends on pal implmenetation
 *  This reboot action value is passed to pal_reboot().
 *
 *  @return Return -1 if unsucessful (eg. reboot action is already pending)
 */
int32_t mv_initiate_reboot(uint32_t reboot_action);

/**
 *  @brief Initialize the specified mailbox instance
 *
 *  @param id mailbox id
 *  @param instance mailbox instance number
 *  @param p_mbox_info the physical address of mailbox entry structure
 *
 *  @return returns the mailbox instance token
 */
uint32_t mv_mbox_get_info(uint32_t id,
			  uint32_t instance, uint32_t *p_mbox_db_guest_entry);

/**
 *  @brief Retrieves the mailbox look-up directory
 *
 *  @return returns the physical address of the directory
 */
uint32_t mv_mbox_get_directory(void);

/**
 *  @brief Informs mobilevisor about the driver state
 *
 *  mailbox instance becomes active after both end point
 *  has invoked the mv_mbox_set_ready call
 *
 *  @param token mailbox instance token
 */
void mv_mbox_set_online(uint32_t token);

/**
 *  @brief Informs mobilevisor to disconnect this ipc
 *
 *  mailbox instance becomes deactive after both end point
 *
 *  @param token mailbox instance token
 */
void mv_mbox_set_offline(uint32_t token);

/**
 *  @brief Post an event to the counter part
 *
 *  @param token mailbox instance token
 *  @param hirq mailbox event hirq to post
 */
void mv_mbox_post(uint32_t token, uint32_t hirq);

/** @brief Used for platform service request. This should not be used directly.
 *     Instead, guest should use functions from mv_platform_service.h.
 */

/** @brief Start vm
 *
 *  @param vcpu_id Specify which vcpu is started.
 *  @param entry_addr Specify the vcpu start address.
 */
void mv_vm_start(uint32_t vm_id);

/** @brief Stop vm
 *
 *  @param vcpu_id Specify which vcpu needs to be stopped.
 */
void mv_vm_stop(uint32_t vm_id);

/** @brief Get cpu mapping
 * @param vcpu_map (out)
 * @param shared_cpu_map (out)
 * @param apic_map (out)
 * @param num_of_cpus (out)
 */
void mv_get_cpu_map(uint32_t *vcpu_map, uint32_t *shared_cpu_map,
		    uint32_t *apic_map, uint32_t *num_of_cpus);

/** @brief Get vm load info
 *  @param vm_id Specify which vm loading info will be reported
 *  @param vm_loadaddr(out)
 *  @param vm_loadszie(out)
 */
uint32_t mv_get_vm_loadinfo(uint32_t vm_id, uint32_t *vm_loadaddr,
			uint32_t *vm_loadsize);

/** @brief config VMM log
 *  @param enable true to enable, false to disable log
 *  @param buffer_info Buffer settings to transfer log
 *  @param log_level Specify the lowest message level to be logged
 */
void mv_vmm_log(uint32_t enable, uint32_t buffer_info, uint32_t log_level);

uint32_t mv_platform_service(uint32_t service_type, uint32_t arg1,
			uint32_t arg2, uint32_t arg3, uint32_t arg4,
			uint32_t *ret0, uint32_t *ret1, uint32_t *ret2,
			uint32_t *ret3, uint32_t *ret4);
#endif				/* _MV_HYPERCALLS_H */
