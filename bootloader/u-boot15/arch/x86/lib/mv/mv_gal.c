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

#include <common.h>
#include <android_bootimg.h>
#include <asm/io.h>
#include <asm/ptrace.h>
#include <asm/zimage.h>
#include <asm/byteorder.h>
#include <asm/bootm.h>
#include <asm/bootparam.h>
#include <linux/compiler.h>

#include <asm/control_regs.h>
#include <asm/processor-flags.h>

#include "mv_hypercalls.h"
#include "mv_service_list.h"
#include "mv_gal.h"

static struct mv_shared_data *mv_shared_data[CONFIG_MAX_VCPUS_PER_VM];
static unsigned int myid;

struct mv_shared_data *mv_gal_get_shared_data(void)
{
	return mv_shared_data[mv_vcpu_id()];
}

void mv_gal_panic(char *panic_msg)
{
	if (panic_msg)
		mv_gal_printk("PANIC: %s\n", panic_msg);
	else
		mv_gal_printk("PANIC\n");

	while (1);
}

void mv_gal_services_init(void)
{
	int i;

	for (i = VMM_FIRST_SERVICE; i <= VMM_LAST_SERVICE; i++)
		vmm_service_init_handlers[i]();
}


void mv_gal_init(struct mv_shared_data *data)
{
	myid = data->os_id;

	mv_gal_services_init();
}

inline unsigned int mv_gal_os_id(void)
{
	return myid;
}

static int mv_map_vcpu_shmem(void)
{
	mv_shared_data[mv_vcpu_id()] = mv_vcpu_get_data();

	printf("mv_shared_data=0x%p\n", mv_gal_get_shared_data());

	return 0;
}

int mv_init_secondary(void)
{
	printf("In %s\n", __func__);
	mv_map_vcpu_shmem();

	return 0;
}

int mv_init(void)
{
	struct mv_shared_data *shmem;

	printf("In %s\n", __func__);

	if (mv_map_vcpu_shmem())
		printf("Unable to map vcpu shared mem\n");

	shmem = mv_gal_get_shared_data();

	printf("ivmc_shmem_paddr=0x%llx ivmc_shmem_size=0x%llx\n",
		shmem->ivmc_shmem_paddr,
		shmem->ivmc_shmem_size);

	printf("Calling mobile gal init. os_id=%d\n",
		shmem->os_id);

	mv_gal_init(shmem);

	return 0;
}

int is_x86_mobilevisor(void)
{
	unsigned long cr4 = read_cr4();
	return (cr4 & X86_CR4_VMXE)?1:0;
}

