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

#ifndef _MV_IPC_H
#define _MV_IPC_H

#ifdef __KERNEL__
#include "linux/types.h"
#else
#include "stdint.h"
#endif

#define mv_paddr_t uint32_t

/** @typedef mv_vlink_state
 *  @brief indicate the current status of a vlink
 */
enum mv_vlink_state {
	VLINK_INIT,
	VLINK_OFF,
	VLINK_ON
};

/** @brief Vlink structure
 *
 *  Used to store information of a vlink between
 *  server(destination) and client(caller, source) OS
 */
struct mv_vlink {
	/** unique name identifier */
	mv_paddr_t name;
	/** logical vlink id */
	uint32_t link;
	/** os id of guest who is server */
	uint32_t s_id;
	/** additional info for server setup */
	mv_paddr_t s_info;
	/** server end state */
	uint32_t s_state;
	/** os id of guest who is client */
	uint32_t c_id;
	/** additional info for client setup */
	mv_paddr_t c_info;
	/** client end state */
	uint32_t c_state;
	/** physical address of the next vlink */
	mv_paddr_t next;
};

#define MAX_MBOX_NAME_SIZE    16
#define MAX_MBOX_INSTANCE_NAME_SIZE    16
#define MAX_MBOX_CMDLINE_SIZE 32

/** @brief mailbox instance look-up entry
 *
 *  Store the instance name and id mapping
 */
struct mbox_instance_dir_entry {
	/** instance name */
	char name[MAX_MBOX_NAME_SIZE];

	/** instance id */
	uint32_t id;
};

/** @brief mailbox instance look-up directory
 *
 *  Store the list of mailbox instance look-up entries
 */
struct mbox_instance_directory {
	/** number of mailbox instances available for this mbox */
	uint32_t num_of_instances;

	/** list of mailbox look-up entries */
	struct mbox_instance_dir_entry entry[0];
};

/** @brief mailbox look-up entry
 *
 *  Store the mailbox name and id mapping
 */
struct mbox_dir_entry {
	/** mailbox name */
	char name[MAX_MBOX_NAME_SIZE];

	/** mailbox id */
	uint32_t id;

	/** address of shared memory for all instances belonging to this mbox */
	mv_paddr_t addr_of_shmem_for_all_instances;

	/** size of shared memory for all instances belonging to this mbox */
	uint32_t size_of_shmem_for_all_instances;

	/** point to mbox instance dir */
	mv_paddr_t p_instance_dir;
};

/** @brief mailbox look-up directory
 *
 *  Store the list of mailbox look-up entries
 */
struct mbox_directory {
	/** number of mailbox look-up entries available */
	uint32_t num_of_entries;

	/** number of mailbox instances available */
	uint32_t num_of_instances;

	/** list of mailbox look-up entries */
	struct mbox_dir_entry entry[0];
};

/** @brief main data structure for a mailbox instance
 *
 *  stores all the details for the mailbox
 */
struct mbox_db_guest_entry {

	/** mailbox name */
	char name[MAX_MBOX_NAME_SIZE];

	/** instance name */
	char instance_name[MAX_MBOX_INSTANCE_NAME_SIZE];

	/** command line data */
	char cmd_line[MAX_MBOX_CMDLINE_SIZE];

	/** unique mailbox instance token */
	uint32_t token;

	/** mailbox id */
	uint32_t id;

	/** instance number */
	uint32_t instance;

	/** hirq for on_connect event */
	uint32_t on_connect_hirq;

	/** hirq for on_disconnect event */
	uint32_t on_disconnect_hirq;

	/** number of user-defined events */
	uint32_t num_of_events;

	/** first hirq of user-defined events */
	uint32_t first_event_hirq;

	/** shared memory size in bytes */
	uint32_t size_of_shared_memory;

	/** shared memory physical start address */
	char shared_mem[0];
};

/*
 * mailbox structures and APIs
 */

#define MBOX_INIT_ERR   0xFFFFFFFF
#define MBOX_SUCCESS    0
#define MBOX_ERROR      1

/**
 * @brief mailbox callback functions
 *
 * This data structure defines the various mailbox
 * callbacks that the mailbox driver should implement
 */
struct mbox_ops {
	/** @brief mailbox on-connect handler
	 *
	 * invoked by the system when both end points have
	 * been initialized
	 */
	void (*on_connect)(uint32_t token, void *cookie);

	/** @brief mailbox on-disconnect handler
	 *
	 * invoked by the system when the other end point
	 * has been shutdown
	 */
	void (*on_disconnect)(uint32_t token, void *cookie);

	/** @brief mailbox event handler
	 *
	 * invoked by the system when the other end point
	 * has posted an event to us
	 */
	void (*on_event)(uint32_t token, uint32_t event_id, void *cookie);
};

/** @brief initializes the ipc stack
 *
 *  @return 0 on success, 1 on error
 */
uint32_t mv_ipc_init(void);

/** @brief get all instance shared memory by mbox name
 *
 *  @param name mailbox name
 *  @param vaddr return virtual address of start shared memory
 *  @param size return size of shared memory
 *  This shared memory is commonly used by all instances
 */
void mbox_get_shmem_for_all_instances(char *name,
		uint32_t *vaddr, uint32_t *size);

/** @brief initialize mailbox entry
 *
 *  Initialize the specified mailbox instance
 *
 *  @param name mailbox name
 *  @param name instance name
 *  @param ops mailbox event callbacks
 *  @param info mailbox entry structure
 *  @param cookie cookie passed in by caller
 *  @return the mailbox token upon success, otherwise MBOX_INIT_ERR
 */
uint32_t mv_ipc_mbox_get_info(char *name,
			      char *instance_name,
			      struct mbox_ops *ops,
			      unsigned char **shared_mem_start,
			      uint32_t *shared_mem_size,
			      char **cmdline, void *cookie);

/** @brief close mailbox entry
 *
 *  Close the specified mailbox instance
 *
 *  @param token the mailbox instance to close
 */
void mv_ipc_mbox_close(uint32_t token);

/** @brief iterate all mailbox instances
 *
 *  Iterate all mailbox instances and invoke the callback
 *
 *  @param name mailbox name
 *  @param on_instance callback function
 *  @return 0 on success, 1 on error
 */
uint32_t mv_ipc_mbox_for_all_instances(char *name,
				       void (*on_instance)(char *instance_name,
						       uint32_t
						       instance_index,
						       uint32_t
						       instance_count));

/** @brief post a mailbox event
 *
 *  Post an event to the specified mailbox instance
 *
 *  @param token the mailbox instance to post event to
 *  @param event_id the 0-based event id to post
 *  @return 0 on success, 1 on error
 */
uint32_t mv_ipc_mbox_post(uint32_t token, uint32_t event_id);

/** @brief set a mailbox status to online
 *
 *
 *  @param token
 *  @return 0 on success, 1 on error
 */
uint32_t mv_ipc_mbox_set_online(uint32_t token);

/** @brief set a mailbox status to offline
 *
 *
 *  @param token
 *  @return 0 on success, 1 on error
 */
uint32_t mv_ipc_mbox_set_offline(uint32_t token);

/** @brief convert event_id to hirq
 *
 *
 *  @param token
 *  @param event_id
 *  @return hirq
 */
uint32_t mv_ipc_mbox_event_to_hirq(uint32_t token, uint32_t event_id);

extern struct irq_domain *hirq_domain;

#endif				/* _MV_IPC_H */
