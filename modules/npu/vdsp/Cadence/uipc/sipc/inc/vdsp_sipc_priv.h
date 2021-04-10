/*
 * Copyright (C) 2019 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __SIPC_PRIV_H
#define __SIPC_PRIV_H
#include <linux/ktime.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <vdsp_ipi_drv.h>


#define CH_STAT_UNUSED               0
#define CH_STAT_OPENED               1
#define CH_STAT_CLOSED               2
#define CH_STAT_REMOTE_OPENED        3
#define CH_STAT_NATIVE_OPENED        4

enum {
	SIPC_BASE_IPI = 0,
	SIPC_BASE_NR
};

enum {
	SMEM_LOCAL = 0,
	SMEM_NR
};

extern struct smsg_ipc *vdsp_smsg_ipcs[];

#define SMSG_CACHE_NR		256

struct smsg_channel {
	/* wait queue for recv-buffer */
	wait_queue_head_t	rxwait;
	struct mutex		rxlock;
	struct wakeup_source	sipc_wake_lock;
	char			wake_lock_name[16];

	/* cached msgs for recv */
	uintptr_t		wrptr[1];
	uintptr_t		rdptr[1];
	struct smsg		caches[SMSG_CACHE_NR];
};

/* smsg ring-buffer between AP/CP ipc */
struct smsg_ipc {
	const char	*name;
	u8	dst;
	u8	client;	/* sipc is  client mode */
	/* target core_id over mailbox */
	u8	core_id;
	u8	core_sensor_id;
	u32	type; /* sipc type, mbox, ipi, pcie */
	u32	smem_inited;

	u32	suspend;
	wait_queue_head_t	suspend_wait;
	/* lock for suspend-list */
	spinlock_t		suspend_pinlock;

	/* send-buffer info */
	uintptr_t	txbuf_addr;
	u32		txbuf_size;	/* must be 2^n */
	uintptr_t	txbuf_rdptr;
	uintptr_t	txbuf_wrptr;

	/* recv-buffer info */
	uintptr_t	rxbuf_addr;
	u32		rxbuf_size;	/* must be 2^n */
	uintptr_t	rxbuf_rdptr;
	uintptr_t	rxbuf_wrptr;

	/* sipc irq related */
	int	irq;
	u32	(*rxirq_status)(u8 id);
	void	(*rxirq_clear)(u8 id);
	void	(*txirq_trigger)(u8 id, u64 msg);

	void __iomem *ring_base;
	u32	ring_size;
	struct ion_buf ring_ion;
	void	*smem_vbase;
	u32	smem_base;
	u32	smem_size;
	u32	smem_type;
	u32	dst_smem_base;
	u32	high_offset;
	u32	dst_high_offset;

	struct task_struct	*thread;

	/* lock for send-buffer */
	spinlock_t		txpinlock;
	/* all fixed channels receivers */
	struct smsg_channel	*channels[SMSG_VALID_CH_NR];
	/* record the runtime status of smsg channel */
	atomic_t		busy[SMSG_VALID_CH_NR];
	/* all channel states: 0 unused, 1 be opened by other core, 2 opend */
	u8			states[SMSG_VALID_CH_NR];

	struct vdsp_ipi_ctx_desc *vdsp_ipi_desc;
	struct vdsp_mem_desc *vdsp_mem_desc;
};

void vdsp_smsg_init_channel2index(void);
void vdsp_smsg_ipc_create(struct smsg_ipc *ipc);
void vdsp_smsg_ipc_destroy(struct smsg_ipc *ipc);

/*smem alloc size align*/
#define SMEM_ALIGN_POOLSZ 0x40000	/*256KB*/

#ifdef CONFIG_64BIT
#define SMEM_ALIGN_BYTES	8
#define SMEM_MIN_ORDER		3
#else
#define SMEM_ALIGN_BYTES	4
#define SMEM_MIN_ORDER		2
#endif

/* initialize smem pool for AP/CP */
int smem_init(u32 addr, u32 size, u32 dst, u32 mem_type);
void sbuf_get_status(u8 dst, char *status_info, int size);

#if defined(CONFIG_DEBUG_FS)
void vdsp_sipc_debug_putline(struct seq_file *m, char c, int n);
#endif

#endif
