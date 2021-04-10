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

#include <linux/debugfs.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <asm/pgtable.h>
#include <uapi/linux/sched/types.h>

#include <linux/sprd_iommu.h>
#include <linux/sprd_ion.h>
#include "ion.h"
#include <linux/string.h>
#include "vdsp_sipc.h"
#include "vdsp_sipc_priv.h"
#include "vdsp_sbuf.h"

#define USING_SHARE_MEM

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "VDSP_SBUF: %d %d %s : "\
	fmt, current->pid, __LINE__, __func__

#define VOLA_SBUF_SMEM volatile struct sbuf_smem_header
#define VOLA_SBUF_RING volatile struct sbuf_ring_header
#define VDSP_MAX_DATA_LEN 0x1000
struct name_node {
	struct	list_head list;
	char	comm[TASK_COMM_LEN];
	pid_t	pid;
	u8	latest;
};

union sbuf_buf {
	void *buf;
	void __user *ubuf;
};

enum task_type {
	TASK_RXWAIT = 0,
	TASK_TXWAIT,
	TASK_SELECT
};

static struct sbuf_mgr *sbufs[VDSP_SIPC_ID_NR][SMSG_VALID_CH_NR];
static char *___strtok = NULL;
extern void sprd_log_sem_down(void);

char *strtok(char *s, char const *ct)
{
	char *sbegin, *send;

	sbegin  = s ? s : ___strtok;
	if (!sbegin) {
		return NULL;
	}
	sbegin += strspn(sbegin,ct);
	if (*sbegin == '\0') {
		___strtok = NULL;
		return( NULL );
	}
	send = strpbrk( sbegin, ct);
	if (send && *send != '\0')
		*send++ = '\0';
	___strtok = send;
	return (sbegin);
}

static void vdsp_notifier_handler (int event, void *data)
{
	struct sbuf_mgr *sbuf = data;
	int cnt = 0;
	char *buf;
	char *delim = "\n";
	char *p;

	buf = kzalloc(VDSP_MAX_DATA_LEN, GFP_KERNEL);
	if (!buf) {
		pr_err("vdsp_notifier_handler kzalloc memory falied\n");
		return;
	}

	pr_info("sbuf notifier handler event=%d\n", event);

	switch (event) {
	case SBUF_NOTIFY_WRITE:
		break;
	case SBUF_NOTIFY_READ:
		do {
			memset(buf, 0, VDSP_MAX_DATA_LEN);
			cnt = vdsp_sbuf_read(sbuf->dst,
				sbuf->channel,
				0,
				(void *)buf,
				VDSP_MAX_DATA_LEN,
				0);
			pr_info("%s read data len =%d\n",__func__, cnt);

			if (cnt < 0) {
				pr_err("sbuf read cnt[%d] failed\n", cnt);
				kfree(buf);
				return;
			}

			p = strtok(buf, delim);
			if (p){
				printk("[VDSP LOG]%s ", p);
				printk("\n");
			}
			while((p = strtok(NULL, delim))) {
				printk("[VDSP LOG]%s ", p);
				printk("\n");
			}
		} while(cnt == VDSP_MAX_DATA_LEN);
		break;
	default:
		pr_info("Received event is invalid(event=%d)\n", event);
	}

	kfree(buf);
}

static bool sbuf_is_task_pointer(const void *ptr)
{
	struct task_struct *task;
	struct thread_info *thread_info;

	task = (struct task_struct *)ptr;
	if (IS_ERR_OR_NULL(task) || !virt_addr_valid(task))
		return false;

#ifndef CONFIG_THREAD_INFO_IN_TASK
	/* in this case thread_info is in the same addres with stack thread_union*/
	if (IS_ERR_OR_NULL(task->stack) || !virt_addr_valid(task->stack))
		return false;
#endif

	thread_info = task_thread_info(task);
	if (IS_ERR_OR_NULL(thread_info) || !virt_addr_valid(thread_info))
		return false;

	return (thread_info->addr_limit == KERNEL_DS ||
		thread_info->addr_limit == USER_DS);
}

static struct task_struct *vdsp_sbuf_wait_get_task(wait_queue_entry_t *pos,
					      u32 *b_select)
{
	struct task_struct *task;
	struct poll_wqueues *table;

	if (!pos->private)
		return NULL;

	/* if the private is put into wait list by sbuf_read, the struct of
	 * pos->private is struct task_struct
	 * if the private is put into list by sbuf_poll, the struct of
	 * pos->private is struct poll_wqueues
	 */

	/* firstly, try struct poll_wqueues */
	table = (struct poll_wqueues *)pos->private;
	task = table->polling_task;
	if (sbuf_is_task_pointer(task)) {
		*b_select = 1;
		return task;
	}

	/* firstly, try convert it with the struct task_struct */
	task = (struct task_struct *)pos->private;

	if (sbuf_is_task_pointer(task)) {
		*b_select = 0;
		return task;
	}

	return NULL;
}

static void vdsp_sbuf_skip_old_data(struct sbuf_mgr *sbuf)
{
	struct sbuf_ring *ring = NULL;
	struct sbuf_ring_header_op *hd_op = NULL;
	u32 i;

	for (i = 0; i < sbuf->ringnr; i++) {
		ring = &sbuf->rings[i];
		hd_op = &ring->header_op;

		/* clean sbuf tx ring , sbuf tx ring no need to clear */
		/* *(hd_op->tx_wt_p) = *(hd_op->tx_rd_p); */
		/* clean sbuf rx ring */
		*(hd_op->rx_rd_p) = *(hd_op->rx_wt_p);
	}
}

static void vdsp_sbuf_comm_init(struct sbuf_mgr *sbuf)
{
	u32 bufnum = sbuf->ringnr;
	int i;
	struct sbuf_ring *ring;

	for (i = 0; i < bufnum; i++) {
		ring = &sbuf->rings[i];
		init_waitqueue_head(&ring->txwait);
		init_waitqueue_head(&ring->rxwait);
		mutex_init(&ring->txlock);
		mutex_init(&ring->rxlock);
		ring->need_wake_lock = 1;
		ring->tx_wakelock_state = 0;
		ring->rx_wakelock_state = 0;

		sprintf(ring->tx_wakelock_name,
			"sbuf-%d-%d-%d-tx",
			sbuf->dst, sbuf->channel, i);
		wakeup_source_init(&ring->tx_wake_lock,
				   ring->tx_wakelock_name);
		sprintf(ring->rx_wakelock_name,
			"sbuf-%d-%d-%d-rx",
			sbuf->dst, sbuf->channel, i);
		wakeup_source_init(&ring->rx_wake_lock,
				   ring->rx_wakelock_name);
	}
}

static int vdsp_sbuf_host_init(struct smsg_ipc *sipc, struct sbuf_mgr *sbuf,
	u32 bufnum, u32 txbufsize, u32 rxbufsize)
{
	VOLA_SBUF_SMEM *smem;
	VOLA_SBUF_RING *ringhd;
	struct sbuf_ring_header_op *hd_op;
	int hsize, i;
	phys_addr_t offset = 0;
	struct sbuf_ring *ring;

	sbuf->ringnr = bufnum;

	/* allocate smem */
	hsize = sizeof(struct sbuf_smem_header) +
		sizeof(struct sbuf_ring_header) * bufnum;
	sbuf->smem_size = hsize + (txbufsize + rxbufsize) * bufnum;
#ifdef USING_SHARE_MEM
	sbuf->smem_addr = vdsp_share_mem_alloc(sipc->vdsp_mem_desc,
					      &sbuf->smem_ion,
					      ION_HEAP_ID_MASK_SYSTEM,
					      sbuf->smem_size);
	sbuf->smem_addr = 1;
#endif
	if (!sbuf->smem_addr) {
		pr_err("%s: channel %d-%d, Failed to allocate smem for sbuf\n",
			__func__, sbuf->dst, sbuf->channel);
		return -ENOMEM;
	}
	sbuf->dst_smem_addr = sbuf->smem_addr - sipc->smem_base + sipc->dst_smem_base;

	pr_info("channel %d-%d, smem_addr=0x%x, smem_size=0x%x, dst_smem_addr=0x%x\n",
		 sbuf->dst,
		 sbuf->channel,
		 sbuf->smem_addr,
		 sbuf->smem_size,
		 sbuf->dst_smem_addr);

#ifdef CONFIG_PHYS_ADDR_T_64BIT
	offset = sipc->high_offset;
	offset = offset << 32;
#endif

	pr_info("%s: channel %d-%d, offset = 0x%llx!\n",
		__func__, sbuf->dst, sbuf->channel, offset);
#ifdef USING_SHARE_MEM
	vdsp_share_mem_kmap(sipc->vdsp_mem_desc, &sbuf->smem_ion);
	sbuf->smem_virt = (void *)sbuf->smem_ion.addr_k[0];
	pr_info("channel %d-%d, smem_virt=0x%p\n",
		 sbuf->dst,
		 sbuf->channel,
		 sbuf->smem_virt);
#endif
	if (!sbuf->smem_virt) {
		pr_err("%s: channel %d-%d, Failed to map smem for sbuf\n",
			__func__, sbuf->dst, sbuf->channel);
#ifdef USING_SHARE_MEM
		vdsp_share_mem_free(sipc->vdsp_mem_desc, &sbuf->smem_ion);
#endif
		return -EFAULT;
	}

	/* allocate rings description */
	sbuf->rings = kcalloc(bufnum, sizeof(struct sbuf_ring), GFP_KERNEL);
	if (!sbuf->rings) {
#ifdef USING_SHARE_MEM
		vdsp_share_mem_unkmap(sipc->vdsp_mem_desc, &sbuf->smem_ion);
		vdsp_share_mem_free(sipc->vdsp_mem_desc, &sbuf->smem_ion);
#endif
		return -ENOMEM;
	}

	/* initialize all ring bufs */
	smem = (VOLA_SBUF_SMEM *)sbuf->smem_virt;
	smem->ringnr = bufnum;
	for (i = 0; i < bufnum; i++) {
		ringhd = (VOLA_SBUF_RING *)&smem->headers[i];
		ringhd->txbuf_addr = sbuf->dst_smem_addr + hsize +
			(txbufsize + rxbufsize) * i;
		ringhd->txbuf_size = txbufsize;
		ringhd->txbuf_rdptr = 0;
		ringhd->txbuf_wrptr = 0;
		ringhd->rxbuf_addr = smem->headers[i].txbuf_addr + txbufsize;
		ringhd->rxbuf_size = rxbufsize;
		ringhd->rxbuf_rdptr = 0;
		ringhd->rxbuf_wrptr = 0;

		ring = &sbuf->rings[i];
		ring->header = ringhd;
		ring->txbuf_virt = sbuf->smem_virt + hsize +
			(txbufsize + rxbufsize) * i;
		ring->rxbuf_virt = ring->txbuf_virt + txbufsize;
		/* init header op */
		hd_op = &ring->header_op;
		hd_op->rx_rd_p = &ringhd->rxbuf_rdptr;
		hd_op->rx_wt_p = &ringhd->rxbuf_wrptr;
		hd_op->rx_size = ringhd->rxbuf_size;
		hd_op->tx_rd_p = &ringhd->txbuf_rdptr;
		hd_op->tx_wt_p = &ringhd->txbuf_wrptr;
		hd_op->tx_size = ringhd->txbuf_size;
		pr_info("channel %d-%d [%d], ring txbuf_addr=0x%x, txbuf_virt=0x%p, rxbuf_addr=0x%x, rxbuf_virt=0x%p\n",
			sbuf->dst,
			sbuf->channel,
			i,
			ringhd->txbuf_addr,
			ring->txbuf_virt,
			ringhd->rxbuf_addr,
			ring->rxbuf_virt);
	}

	vdsp_sbuf_comm_init(sbuf);

	return 0;
}

static int vdsp_sbuf_client_init(struct smsg_ipc *sipc, struct sbuf_mgr *sbuf)
{
#if 0
	VOLA_SBUF_SMEM *smem;
	VOLA_SBUF_RING *ringhd;
	struct sbuf_ring_header_op *hd_op;
	struct sbuf_ring *ring;
	int hsize, i;
	u32 txbufsize, rxbufsize;
	phys_addr_t offset = 0;
	u32 bufnum;
//	u8 dst = sbuf->dst;

#ifdef CONFIG_PHYS_ADDR_T_64BIT
	offset = sipc->high_offset;
	offset = offset << 32;
	pr_info("%s: channel %d-%d, offset = 0x%llx!\n",
		__func__, sbuf->dst, sbuf->channel, offset);
#endif

	/* get bufnum and bufsize */
	hsize = sizeof(struct sbuf_smem_header) +
		sizeof(struct sbuf_ring_header) * 1;
#ifdef USING_SHARE_MEM
	sbuf->smem_virt = shmem_ram_vmap_nocache(dst,
						 sbuf->smem_addr + offset,
						 hsize);
#endif
	if (!sbuf->smem_virt) {
		pr_err("%s: channel %d-%d, Failed to map smem for sbuf head\n",
		       __func__, sbuf->dst, sbuf->channel);
		return -EFAULT;
	}
	smem = (VOLA_SBUF_SMEM *)sbuf->smem_virt;
	sbuf->ringnr = smem->ringnr;
	bufnum = sbuf->ringnr;
	ringhd = (VOLA_SBUF_RING *)&smem->headers[0];
	txbufsize = ringhd->rxbuf_size;
	rxbufsize = ringhd->txbuf_size;
	hsize = sizeof(struct sbuf_smem_header) +
	sizeof(struct sbuf_ring_header) * bufnum;
	sbuf->smem_size = hsize + (txbufsize + rxbufsize) * bufnum;
	pr_debug("%s: channel %d-%d, txbufsize = 0x%x, rxbufsize = 0x%x!\n",
		 __func__, sbuf->dst, sbuf->channel, txbufsize, rxbufsize);
	pr_debug("%s: channel %d-%d, smem_size = 0x%x, ringnr = %d!\n",
		 __func__, sbuf->dst, sbuf->channel, sbuf->smem_size, bufnum);
#ifdef USING_SHARE_MEM
	shmem_ram_unmap(dst, sbuf->smem_virt);
#endif

	/* get smem virtual address */
#ifdef USING_SHARE_MEM
	sbuf->smem_virt = shmem_ram_vmap_nocache(dst,
						sbuf->smem_addr + offset,
						sbuf->smem_size);
#endif
	if (!sbuf->smem_virt) {
		pr_err("%s: channel %d-%d,Failed to map smem for sbuf\n",
			__func__, sbuf->dst, sbuf->channel);
		//smem_free(dst, sbuf->smem_addr_debug, sbuf->smem_size);
		return -EFAULT;
	}

	/* allocate rings description */
	sbuf->rings = kcalloc(bufnum, sizeof(struct sbuf_ring), GFP_KERNEL);
	if (!sbuf->rings) {
#ifdef USING_SHARE_MEM
		smem_free(dst, sbuf->smem_addr_debug, sbuf->smem_size);
		shmem_ram_unmap(dst, sbuf->smem_virt);
#endif
		return -ENOMEM;
	}
	pr_info("%s: channel %d-%d, ringns = 0x%p!\n",
		 __func__, sbuf->dst, sbuf->channel, sbuf->rings);

	/* initialize all ring bufs */
	smem = (VOLA_SBUF_SMEM *)sbuf->smem_virt;
	for (i = 0; i < bufnum; i++) {
		ringhd = (VOLA_SBUF_RING *)&smem->headers[i];
		ring = &sbuf->rings[i];
		ring->header = ringhd;
		/* host txbuf_addr */
		ring->rxbuf_virt = sbuf->smem_virt + hsize +
			(txbufsize + rxbufsize) * i;
		/* host rxbuf_addr */
		ring->txbuf_virt = ring->rxbuf_virt + rxbufsize;
		/* init header op , client mode, rx <==> tx */
		hd_op = &ring->header_op;
		hd_op->rx_rd_p = &ringhd->txbuf_rdptr;
		hd_op->rx_wt_p = &ringhd->txbuf_wrptr;
		hd_op->rx_size = ringhd->txbuf_size;
		hd_op->tx_rd_p = &ringhd->rxbuf_rdptr;
		hd_op->tx_wt_p = &ringhd->rxbuf_wrptr;
		hd_op->tx_size = ringhd->rxbuf_size;
	}

	vdsp_sbuf_comm_init(sbuf);
#endif
	return 0;
}

#ifdef PR_READ
	unsigned char vdsplogbuff[4096];
#endif
static int vdsp_sbuf_thread(void *data)
{
	struct sbuf_mgr *sbuf = data;
	struct sbuf_ring *ring;
	struct smsg mcmd, mrecv;
	int rval, bufid;
	struct smsg_ipc *sipc;

	sipc = vdsp_smsg_ipcs[sbuf->dst];

	sprd_log_sem_down();
	pr_info("1");
	/* since the channel open may hang, we call it in the sbuf thread */
	rval = vdsp_smsg_ch_open(sbuf->dst, sbuf->channel, -1);
	if (rval != 0) {
		pr_err("Failed to open channel %d\n", sbuf->channel);
		/* assign NULL to thread poniter as failed to open channel */
		sbuf->thread = NULL;
		return rval;
	}

	/* if client, send SMSG_CMD_SBUF_INIT, wait sbuf SMSG_DONE_SBUF_INIT */
	if (sipc->client) {
		pr_info("12");
		vdsp_smsg_set(&mcmd, sbuf->channel, VDSP_SMSG_TYPE_CMD,
			 SMSG_CMD_SBUF_INIT, 0);
		vdsp_smsg_send(sbuf->dst, &mcmd, -1);
		do {
			vdsp_smsg_set(&mrecv, sbuf->channel, 0, 0, 0);
			rval = vdsp_smsg_recv(sbuf->dst, &mrecv, -1);
			if (rval != 0) {
				sbuf->thread = NULL;
				return rval;
			}
		} while (mrecv.type != VDSP_SMSG_TYPE_DONE ||
			mrecv.flag != SMSG_DONE_SBUF_INIT);
		sbuf->smem_addr = mrecv.value;
		pr_info("%s: channel %d-%d, done_sbuf_init, address = 0x%x!\n",
			__func__, sbuf->dst, sbuf->channel, sbuf->smem_addr);
		if (vdsp_sbuf_client_init(sipc, sbuf)) {
			sbuf->thread = NULL;
			return 0;
		}
		sbuf->state = SBUF_STATE_READY;
	} else
	pr_info("changdou 131313131313131313113\n");
	/* sbuf init done, handle the ring rx events */
	while (!kthread_should_stop()) {
		/* monitor sbuf rdptr/wrptr update smsg */
		vdsp_smsg_set(&mrecv, sbuf->channel, 0, 0, 0);
		rval = vdsp_smsg_recv(sbuf->dst, &mrecv, -1);
		if (rval == -EIO) {
			/* channel state is free */
			msleep(20);
			continue;
		}

		pr_info("sbuf thread recv msg: dst=%d, channel=%d, type=%d, flag=0x%04x, value=0x%08x\n",
			 sbuf->dst,
			 sbuf->channel,
			 mrecv.type,
			 mrecv.flag,
			 mrecv.value);

		switch (mrecv.type) {
		case VDSP_SMSG_TYPE_OPEN:
			pr_info("%s: channel %d-%d, state=%d, recv open msg!\n",
				__func__, sbuf->dst,
				sbuf->channel, sbuf->state);
			if (sipc->client)
				break;

			/* if channel state is already reay, reopen it
			 * (such as modem reset), we must skip the old
			 * buf data , than give open ack and reset state
			 * to idle
			 */
			if (sbuf->state == SBUF_STATE_READY) {
				vdsp_sbuf_skip_old_data(sbuf);
				sbuf->state = SBUF_STATE_IDLE;
			}
			/* handle channel open */
			vdsp_smsg_open_ack(sbuf->dst, sbuf->channel);
			break;
		case VDSP_SMSG_TYPE_CLOSE:
			/* handle channel close */
			vdsp_sbuf_skip_old_data(sbuf);
			vdsp_smsg_close_ack(sbuf->dst, sbuf->channel);
			sbuf->state = SBUF_STATE_IDLE;
			break;
		case VDSP_SMSG_TYPE_CMD:
			pr_info("%s: channel %d-%d state = %d, recv cmd msg, flag = %d!\n",
				__func__, sbuf->dst, sbuf->channel,
				sbuf->state, mrecv.flag);
			if (sipc->client)
				break;

			vdsp_share_mem_iommu_map(sipc->vdsp_mem_desc,
						&sbuf->smem_ion,
						IOMMU_ALL);

			sbuf->vdsp_addr = sbuf->smem_ion.iova[0];

			/* respond cmd done for sbuf init only state is idle */
			if (sbuf->state == SBUF_STATE_IDLE &&
			    mrecv.flag == SMSG_CMD_SBUF_INIT) {
				vdsp_smsg_set(&mcmd,
					 sbuf->channel,
					 VDSP_SMSG_TYPE_DONE,
					 SMSG_DONE_SBUF_INIT,
					 (u32)((u64)sbuf->vdsp_addr & 0xFFFFFFFF));
				pr_info("send value = 0x%x", mcmd.value);
				vdsp_smsg_send(sbuf->dst, &mcmd, -1);
			#ifdef CONFIG_PHYS_ADDR_T_64BIT
				vdsp_smsg_set(&mcmd,
					 sbuf->channel,
					 VDSP_SMSG_TYPE_DONE,
					 SMSG_DONE_SBUF_INIT,
					 (u32)(((u64)sbuf->vdsp_addr & 0xFFFFFFFF00000000) >> 32));
				pr_info("send value 111 = 0x%x", mcmd.value);
				vdsp_smsg_send(sbuf->dst, &mcmd, -1);
			#endif
				sbuf->state = SBUF_STATE_READY;
				for (bufid = 0; bufid < sbuf->ringnr; bufid++) {
					ring = &sbuf->rings[bufid];
					if (ring->handler)
						ring->handler(SBUF_NOTIFY_READY,
								ring->data);
				}
			}
			break;
		case VDSP_SMSG_TYPE_EVENT:
			bufid = mrecv.value;
			WARN_ON(bufid >= sbuf->ringnr);
			ring = &sbuf->rings[bufid];
			switch (mrecv.flag) {
			case SMSG_EVENT_SBUF_RDPTR:
				wake_up_interruptible_all(&ring->txwait);
				if (ring->handler)
					ring->handler(SBUF_NOTIFY_WRITE,
						      ring->data);
				__pm_wakeup_event(&ring->tx_wake_lock,
					jiffies_to_msecs(HZ / 2));
				ring->tx_wakelock_state = 1;
				pr_debug("sbuf %s : wake_lock hz/2!",
					  ring->tx_wakelock_name);
				break;
			case SMSG_EVENT_SBUF_WRPTR:
				wake_up_interruptible_all(&ring->rxwait);
				if (ring->handler)
					ring->handler(SBUF_NOTIFY_READ,
						      ring->data);
#ifdef PR_READ
				vdsp_sbuf_read(1, 3, 0, vdsplogbuff, 4096, -1);
#endif
				__pm_wakeup_event(&ring->rx_wake_lock,
					jiffies_to_msecs(HZ / 2));
				ring->rx_wakelock_state = 1;
#ifdef PR_READ
				printk("[GGG VDSP]: %s", vdsplogbuff);
#endif
				break;
			default:
				rval = 1;
				break;
			}
			break;
		default:
			rval = 1;
			break;
		};

		if (rval) {
			pr_info("non-handled sbuf msg: %d-%d, %d, %d, %d\n",
				sbuf->dst,
				sbuf->channel,
				mrecv.type,
				mrecv.flag,
				mrecv.value);
			rval = 0;
		}
		/* unlock sipc channel wake lock */
		vdsp_smsg_ch_wake_unlock(sbuf->dst, sbuf->channel);
	}

	return 0;
}


int vdsp_sbuf_create(u8 dst, u8 channel, u32 bufnum, u32 txbufsize, u32 rxbufsize)
{
	struct sbuf_mgr *sbuf;
	u8 ch_index;
	int i, ret;
	struct smsg_ipc *sipc = NULL;
	struct sched_param param = {.sched_priority = 10};

	sipc = vdsp_smsg_ipcs[dst];
	ch_index = vdsp_sipc_channel2index(channel);
	if (ch_index == INVALID_CHANEL_INDEX) {
		pr_err("%s:channel %d invalid!\n", __func__, channel);
		return -EINVAL;
	}

	pr_info("%s dst=%d, chanel=%d, bufnum=%d, txbufsize=0x%x, rxbufsize=0x%x\n",
		 __func__,
		 dst,
		 channel,
		 bufnum,
		 txbufsize,
		 rxbufsize);

	if (dst >= VDSP_SIPC_ID_NR  || !sipc) {
		pr_err("%s: dst = %d is invalid\n", __func__, dst);
		return -EINVAL;
	}

	sbuf = kzalloc(sizeof(*sbuf), GFP_KERNEL);
	if (!sbuf)
		return -ENOMEM;

	sbuf->state = SBUF_STATE_IDLE;
	sbuf->dst = dst;
	sbuf->channel = channel;
	if (!sipc->client) {
		ret = vdsp_sbuf_host_init(sipc, sbuf, bufnum, txbufsize, rxbufsize);
		if (ret) {
			kfree(sbuf);
			return ret;
		}
	}

	sbuf->thread = kthread_create(vdsp_sbuf_thread, sbuf,
			"sbuf-%d-%d", dst, channel);
	if (IS_ERR(sbuf->thread)) {
		pr_err("Failed to create kthread: sbuf-%d-%d\n", dst, channel);
		if (!sipc->client) {
			if (sbuf->rings) {
				for (i = 0; i < sbuf->ringnr; i++) {
					wakeup_source_trash(&sbuf->rings[i].tx_wake_lock);
					wakeup_source_trash(&sbuf->rings[i].rx_wake_lock);
				}
				kfree(sbuf->rings);
			}

#ifdef USING_SHARE_MEM
			vdsp_share_mem_unkmap(sipc->vdsp_mem_desc, &sbuf->smem_ion);
			vdsp_share_mem_free(sipc->vdsp_mem_desc, &sbuf->smem_ion);
#endif
		}
		ret = PTR_ERR(sbuf->thread);
		kfree(sbuf);
		return ret;
	}

	sbufs[dst][ch_index] = sbuf;

	vdsp_sbuf_register_notifier(sbuf->dst,
		sbuf->channel,
		0,
		vdsp_notifier_handler,
		sbuf);

	/*set the thread as a real time thread, and its priority is 10*/
	sched_setscheduler(sbuf->thread, SCHED_FIFO, &param);
	wake_up_process(sbuf->thread);

	return 0;
}
EXPORT_SYMBOL_GPL(vdsp_sbuf_create);

void vdsp_sbuf_set_no_need_wake_lock(u8 dst, u8 channel, u32 bufnum)
{
	u8 ch_index;
	struct sbuf_mgr *sbuf;
	struct sbuf_ring *ring = NULL;

	ch_index = vdsp_sipc_channel2index(channel);
	if (ch_index == INVALID_CHANEL_INDEX) {
		pr_err("%s:channel %d invalid!\n", __func__, channel);
		return;
	}

	sbuf = sbufs[dst][ch_index];
	if (!sbuf || sbuf->ringnr <= bufnum)
		return;

	ring = &sbuf->rings[bufnum];
	ring->need_wake_lock = 0;
}
EXPORT_SYMBOL_GPL(vdsp_sbuf_set_no_need_wake_lock);

void vdsp_sbuf_destroy(u8 dst, u8 channel)
{
	struct sbuf_mgr *sbuf;
	int i;
	u8 ch_index;
	struct smsg_ipc *sipc;

	ch_index = vdsp_sipc_channel2index(channel);
	if (ch_index == INVALID_CHANEL_INDEX) {
		pr_err("%s:channel %d invalid!\n", __func__, channel);
		return;
	}

	sbuf = sbufs[dst][ch_index];
	if (!sbuf)
		return;

	sipc = vdsp_smsg_ipcs[dst];

	sbuf->state = SBUF_STATE_IDLE;
	vdsp_smsg_ch_close(dst, channel, -1);

	/* stop sbuf thread if it's created successfully and still alive */
	if (!IS_ERR_OR_NULL(sbuf->thread))
		kthread_stop(sbuf->thread);

	if (sbuf->rings) {
		for (i = 0; i < sbuf->ringnr; i++) {
			wake_up_interruptible_all(&sbuf->rings[i].txwait);
			wake_up_interruptible_all(&sbuf->rings[i].rxwait);
			wakeup_source_trash(&sbuf->rings[i].tx_wake_lock);
			wakeup_source_trash(&sbuf->rings[i].rx_wake_lock);
		}
		kfree(sbuf->rings);
	}

	if (sbuf->smem_virt)
#ifdef USING_SHARE_MEM
			vdsp_share_mem_unkmap(sipc->vdsp_mem_desc, &sbuf->smem_ion);
#endif

#ifdef USING_SHARE_MEM
	if (!sipc->client)
		vdsp_share_mem_free(sipc->vdsp_mem_desc, &sbuf->smem_ion);
#endif

	kfree(sbuf);

	sbufs[dst][ch_index] = NULL;
}
EXPORT_SYMBOL_GPL(vdsp_sbuf_destroy);

int vdsp_sbuf_write(u8 dst, u8 channel, u32 bufid,
	       void *buf, u32 len, int timeout)
{
	struct sbuf_mgr *sbuf;
	struct sbuf_ring *ring = NULL;
	struct sbuf_ring_header_op *hd_op;
	struct smsg mevt;
	void *txpos;
	int rval, left, tail, txsize;
	u8 ch_index;
	union sbuf_buf u_buf;

	u_buf.buf = buf;
	ch_index = vdsp_sipc_channel2index(channel);
	if (ch_index == INVALID_CHANEL_INDEX) {
		pr_err("%s:channel %d invalid!\n", __func__, channel);
		return -EINVAL;
	}

	sbuf = sbufs[dst][ch_index];
	if (!sbuf)
		return -ENODEV;
	ring = &sbuf->rings[bufid];
	hd_op = &ring->header_op;
	if (sbuf->state != SBUF_STATE_READY) {
		pr_info("sbuf-%d-%d not ready to write!\n",
			dst, channel);
		return -ENODEV;
	}

	pr_info("dst=%d, channel=%d, bufid=%d, len=%d, timeout=%d\n",
		 dst,
		 channel,
		 bufid,
		 len,
		 timeout);
	pr_info("sbuf channel=%d, wrptr=%d, rdptr=%d\n",
		 channel,
		 *(hd_op->tx_wt_p),
		 *(hd_op->tx_rd_p));

	rval = 0;
	left = len;

	if (timeout) {
		mutex_lock(&ring->txlock);
	} else {
		if (!mutex_trylock(&ring->txlock)) {
			pr_debug("sbuf_read busy, dst=%d, channel=%d, bufid=%d\n",
				 dst, channel, bufid);
			return -EBUSY;
		}
	}

	if (timeout == 0) {
		/* no wait */
		if ((int)(*(hd_op->tx_wt_p) - *(hd_op->tx_rd_p)) >=
				hd_op->tx_size) {
			pr_info("%s: %d-%d ring %d txbuf is full!\n",
				__func__, dst, channel, bufid);
			rval = -EBUSY;
		}
	} else if (timeout < 0) {
		/* wait forever */
		rval = wait_event_interruptible(
			ring->txwait,
			(int)(*(hd_op->tx_wt_p) - *(hd_op->tx_rd_p)) <
			hd_op->tx_size ||
			sbuf->state == SBUF_STATE_IDLE);
		if (rval < 0)
			pr_debug("%s: wait interrupted!\n", __func__);

		if (sbuf->state == SBUF_STATE_IDLE) {
			pr_err("%s: sbuf state is idle!\n", __func__);
			rval = -EIO;
		}
	} else {
		/* wait timeout */
		rval = wait_event_interruptible_timeout(
			ring->txwait,
			(int)(*(hd_op->tx_wt_p) - *(hd_op->tx_rd_p)) <
			hd_op->tx_size ||
			sbuf->state == SBUF_STATE_IDLE,
			timeout);
		if (rval < 0) {
			pr_debug("%s: wait interrupted!\n", __func__);
		} else if (rval == 0) {
			pr_info("%s: wait timeout!\n", __func__);
			rval = -ETIME;
		}

		if (sbuf->state == SBUF_STATE_IDLE) {
			pr_err("%s: sbuf state is idle!\n", __func__);
			rval = -EIO;
		}
	}

	while (left && (int)(*(hd_op->tx_wt_p) - *(hd_op->tx_rd_p)) <
	       hd_op->tx_size && sbuf->state == SBUF_STATE_READY) {
		/* calc txpos & txsize */
		txpos = ring->txbuf_virt +
			*(hd_op->tx_wt_p) % hd_op->tx_size;
		txsize = hd_op->tx_size -
			(int)(*(hd_op->tx_wt_p) - *(hd_op->tx_rd_p));
		txsize = min(txsize, left);

		tail = txpos + txsize - (ring->txbuf_virt + hd_op->tx_size);
		if (tail > 0) {
			/* ring buffer is rounded */
			if ((uintptr_t)u_buf.buf > TASK_SIZE) {
				unalign_memcpy(txpos, u_buf.buf, txsize - tail);
				unalign_memcpy(ring->txbuf_virt,
					       u_buf.buf + txsize - tail, tail);
			} else {
				if (unalign_copy_from_user(
					txpos,
					u_buf.ubuf,
					txsize - tail) ||
				   unalign_copy_from_user(
					ring->txbuf_virt,
					u_buf.ubuf + txsize - tail,
					tail)) {
					pr_err("%s:failed to copy from user!\n",
					       __func__);
					rval = -EFAULT;
					break;
				}
			}
		} else {
			if ((uintptr_t)u_buf.buf > TASK_SIZE) {
				unalign_memcpy(txpos, u_buf.buf, txsize);
			} else {
				/* handle the user space address */
				if (unalign_copy_from_user(
						txpos,
						u_buf.ubuf,
						txsize)) {
					pr_err("%s:failed to copy from user!\n",
					       __func__);
					rval = -EFAULT;
					break;
				}
			}
		}

		pr_info("sbuf channel=%d, txpos=%p, txsize=%d\n",
			 channel, txpos, txsize);

		/* update tx wrptr */
		*(hd_op->tx_wt_p) = *(hd_op->tx_wt_p) + txsize;
		/* tx ringbuf is empty, so need to notify peer side */
		if (*(hd_op->tx_wt_p) - *(hd_op->tx_rd_p) == txsize) {
			vdsp_smsg_set(&mevt, channel,
				 VDSP_SMSG_TYPE_EVENT,
				 SMSG_EVENT_SBUF_WRPTR,
				 bufid);
			vdsp_smsg_send(dst, &mevt, -1);
		}

		left -= txsize;
		u_buf.buf += txsize;
	}

	/* must tx_wakelock_state is 1(means have got a long wake lock) ,
	 * we can do below actions, ortherwise system can't enter to sleep
	 */
	if (ring->tx_wakelock_state) {
		ring->tx_wakelock_state = 0;

		/* if need wake lock , update wake lock time to 20ms,
		 * else unlock it immediately
		 */
		if (ring->need_wake_lock) {
			pr_debug("sbuf %s : wake_lock hz/50!",
				 ring->tx_wakelock_name);
			__pm_wakeup_event(&ring->tx_wake_lock,
				jiffies_to_msecs(HZ / 50));
		} else {
			pr_debug("sbuf %s : wake_unlock!",
				 ring->tx_wakelock_name);
			__pm_relax(&ring->tx_wake_lock);
		}
	}
	mutex_unlock(&ring->txlock);

	pr_info("done, channel=%d, len=%d\n",
		 channel, len - left);

	if (len == left)
		return rval;
	else
		return (len - left);
}
EXPORT_SYMBOL_GPL(vdsp_sbuf_write);

int vdsp_sbuf_read(u8 dst, u8 channel, u32 bufid,
	      void *buf, u32 len, int timeout)
{
	struct sbuf_mgr *sbuf;
	struct sbuf_ring *ring = NULL;
	struct sbuf_ring_header_op *hd_op;
	struct smsg mevt;
	void *rxpos;
	int rval, left, tail, rxsize;
	u8 ch_index;
	union sbuf_buf u_buf;

	u_buf.buf = buf;
	ch_index = vdsp_sipc_channel2index(channel);
	if (ch_index == INVALID_CHANEL_INDEX) {
		pr_err("%s:channel %d invalid!\n", __func__, channel);
		return -EINVAL;
	}
	sbuf = sbufs[dst][ch_index];
	if (!sbuf)
		return -ENODEV;
	ring = &sbuf->rings[bufid];
	hd_op = &ring->header_op;

	if (sbuf->state != SBUF_STATE_READY) {
		pr_debug("sbuf-%d-%d not ready to read!\n", dst, channel);
		return -ENODEV;
	}

	pr_info("%s:dst=%d, channel=%d, bufid=%d, len=%d, timeout=%d\n",
		 __func__, dst, channel, bufid, len, timeout);
	pr_info("%s: channel=%d, rx_wt_p=%d, rx_rd_p=%d\n",
		 __func__,
		 channel,
		 *(hd_op->rx_wt_p),
		 *(hd_op->rx_rd_p));

	rval = 0;
	left = len;

	if (timeout) {
		mutex_lock(&ring->rxlock);
	} else {
		if (!mutex_trylock(&ring->rxlock)) {
			pr_debug("%s: busy!,dst=%d, channel=%d, bufid=%d\n",
				 __func__, dst, channel, bufid);
			return -EBUSY;
		}
	}

	if (*(hd_op->rx_wt_p) == *(hd_op->rx_rd_p)) {
		if (timeout == 0) {
			/* no wait */
			pr_debug("%s: %d-%d ring %d rxbuf is empty!\n",
				 __func__, dst, channel, bufid);
			rval = -ENODATA;
		} else if (timeout < 0) {
			/* wait forever */
			rval = wait_event_interruptible(
				ring->rxwait,
				*(hd_op->rx_wt_p) != *(hd_op->rx_rd_p) ||
				sbuf->state == SBUF_STATE_IDLE);
			if (rval < 0)
				pr_debug("%s: wait interrupted!\n", __func__);

			if (sbuf->state == SBUF_STATE_IDLE) {
				pr_err("%s: sbuf state is idle!\n", __func__);
				rval = -EIO;
			}
		} else {
			/* wait timeout */
			rval = wait_event_interruptible_timeout(
				ring->rxwait,
				*(hd_op->rx_wt_p) != *(hd_op->rx_rd_p) ||
				sbuf->state == SBUF_STATE_IDLE, timeout);
			if (rval < 0) {
				pr_debug("%s: wait interrupted!\n", __func__);
			} else if (rval == 0) {
				pr_info("%s: wait timeout!\n", __func__);
				rval = -ETIME;
			}

			if (sbuf->state == SBUF_STATE_IDLE) {
				pr_err("%s: state is idle!\n", __func__);
				rval = -EIO;
			}
		}
	}

	while (left &&
	       (*(hd_op->rx_wt_p) != *(hd_op->rx_rd_p)) &&
	       sbuf->state == SBUF_STATE_READY) {
		/* calc rxpos & rxsize */
		rxpos = ring->rxbuf_virt +
			*(hd_op->rx_rd_p) % hd_op->rx_size;
		rxsize = (int)(*(hd_op->rx_wt_p) - *(hd_op->rx_rd_p));
		/* check overrun */
		if (rxsize > hd_op->rx_size)
			pr_err("%s: overrun bufid = %d, channel= %d rxsize=0x%x, sbuf rdptr=%d, wrptr=%d",
			       __func__,
			       bufid,
			       channel,
			       rxsize,
			       *(hd_op->rx_wt_p),
			       *(hd_op->rx_rd_p));

		rxsize = min(rxsize, left);

		pr_info("%s: sbuf channel=%d, buf=%p, rxpos=0x%x, rxsize=%d left%d\n",
			 __func__, channel, u_buf.buf, rxpos, rxsize, left);

		tail = rxpos + rxsize - (ring->rxbuf_virt + hd_op->rx_size);

		if (tail > 0) {
			/* ring buffer is rounded */
			pr_info("ring buffer is rounded\n");
			if ((uintptr_t)u_buf.buf > TASK_SIZE) {
				unalign_memcpy(u_buf.buf, rxpos, rxsize - tail);
				unalign_memcpy(u_buf.buf + rxsize - tail,
					       ring->rxbuf_virt, tail);
			} else {
				/* handle the user space address */
				if (unalign_copy_to_user(u_buf.ubuf,
							 rxpos,
							 rxsize - tail) ||
				    unalign_copy_to_user(u_buf.ubuf
							 + rxsize - tail,
							 ring->rxbuf_virt,
							 tail)) {
					pr_err("%s: failed to copy to user!\n",
						__func__);
					rval = -EFAULT;
					break;
				}
			}
		} else {
			if ((uintptr_t)u_buf.buf > TASK_SIZE) {
				unalign_memcpy(u_buf.buf, rxpos, rxsize);
			} else {
				/* handle the user space address */
				pr_info("handle the user space address\n");
				if (unalign_copy_to_user(u_buf.ubuf,
							 rxpos, rxsize)) {
					pr_err("%s: failed to copy to user!\n",
						__func__);
					rval = -EFAULT;
					break;
				}
			}
		}

		/* update rx rdptr */
		*(hd_op->rx_rd_p) = *(hd_op->rx_rd_p) + rxsize;
		pr_info("update rx rdptr sbuf rx_wt_p[%d], rx_rd_p[%d], rx_size[%d], rxsize[%d], [%d]\n",
			*(hd_op->rx_wt_p),
			*(hd_op->rx_rd_p),
			hd_op->rx_size,
			rxsize,
			hd_op->rx_size - rxsize);
		/* rx ringbuf is full ,so need to notify peer side */
		if ((*(hd_op->rx_wt_p) - *(hd_op->rx_rd_p)) ==
		    (hd_op->rx_size - rxsize)) {
			vdsp_smsg_set(&mevt, channel,
				 VDSP_SMSG_TYPE_EVENT,
				 SMSG_EVENT_SBUF_RDPTR,
				 bufid);
			vdsp_smsg_send(dst, &mevt, -1);
			pr_info("vdsp_smsg_send SMSG_EVENT_SBUF_RDPTR\n");
		} else {
			pr_info("no need vdsp_smsg_send SMSG_EVENT_SBUF_RDPTR\n");
		}

		left -= rxsize;
		u_buf.buf += rxsize;
	}

	/* must rx_wakelock_state is 1(means have got a long wake lock) ,
	 * we can do below actions, ortherwise system can't enter to sleep
	 */
	if (ring->rx_wakelock_state) {
		ring->rx_wakelock_state = 0;

		/* if need wake lock , update wake lock time to 20ms,
		 * else unlock it immediately
		 */
		if (ring->need_wake_lock) {
			pr_debug("sbuf %s : wake_lock hz/50!",
				 ring->rx_wakelock_name);
			__pm_wakeup_event(&ring->rx_wake_lock,
				jiffies_to_msecs(HZ / 50));
		} else {
			pr_debug("sbuf %s : wake_unlock!",
				 ring->rx_wakelock_name);
			__pm_relax(&ring->rx_wake_lock);
		}
	}

	mutex_unlock(&ring->rxlock);

	pr_info("%s: done, channel=%d, len=%d", __func__, channel, len - left);

	if (len == left)
		return rval;
	else
		return (len - left);
}
EXPORT_SYMBOL_GPL(vdsp_sbuf_read);

int vdsp_sbuf_poll_wait(u8 dst, u8 channel, u32 bufid,
		   struct file *filp, poll_table *wait)
{
	struct sbuf_mgr *sbuf;
	struct sbuf_ring *ring = NULL;
	struct sbuf_ring_header_op *hd_op;
	unsigned int mask = 0;
	u8 ch_index;

	ch_index = vdsp_sipc_channel2index(channel);
	if (ch_index == INVALID_CHANEL_INDEX) {
		pr_err("%s:channel %d invalid!\n", __func__, channel);
		return mask;
	}
	sbuf = sbufs[dst][ch_index];
	if (!sbuf)
		return mask;
	ring = &sbuf->rings[bufid];
	hd_op = &ring->header_op;
	if (sbuf->state != SBUF_STATE_READY) {
		pr_err("sbuf-%d-%d not ready to poll !\n", dst, channel);
		return mask;
	}

	poll_wait(filp, &ring->txwait, wait);
	poll_wait(filp, &ring->rxwait, wait);

	if (*(hd_op->rx_wt_p) != *(hd_op->rx_rd_p))
		mask |= POLLIN | POLLRDNORM;

	if (*(hd_op->tx_wt_p) - *(hd_op->tx_rd_p) < hd_op->tx_size)
		mask |= POLLOUT | POLLWRNORM;

	return mask;
}
EXPORT_SYMBOL_GPL(vdsp_sbuf_poll_wait);

int vdsp_sbuf_status(u8 dst, u8 channel)
{
	struct sbuf_mgr *sbuf;
	u8 ch_index;

	ch_index = vdsp_sipc_channel2index(channel);
	if (ch_index == INVALID_CHANEL_INDEX) {
		pr_err("%s:channel %d invalid!\n", __func__, channel);
		return -EINVAL;
	}
	sbuf = sbufs[dst][ch_index];

	if (!sbuf)
		return -ENODEV;
	if (sbuf->state != SBUF_STATE_READY)
		return -ENODEV;

	return 0;
}
EXPORT_SYMBOL_GPL(vdsp_sbuf_status);

int vdsp_sbuf_register_notifier(u8 dst, u8 channel, u32 bufid,
			   void (*handler)(int event, void *data), void *data)
{
	struct sbuf_mgr *sbuf;
	struct sbuf_ring *ring = NULL;
	u8 ch_index;

	ch_index = vdsp_sipc_channel2index(channel);
	if (ch_index == INVALID_CHANEL_INDEX) {
		pr_err("%s:channel %d invalid!\n", __func__, channel);
		return -EINVAL;
	}
	sbuf = sbufs[dst][ch_index];
	if (!sbuf)
		return -ENODEV;
	ring = &sbuf->rings[bufid];
	ring->handler = handler;
	ring->data = data;

	if (sbuf->state == SBUF_STATE_READY)
		handler(SBUF_NOTIFY_READ, data);

	return 0;
}
EXPORT_SYMBOL_GPL(vdsp_sbuf_register_notifier);

void vdsp_sbuf_get_status(u8 dst, char *status_info, int size)
{
	struct sbuf_mgr *sbuf = NULL;
	struct sbuf_ring *ring = NULL;
	struct sbuf_ring_header_op *hd_op;
	wait_queue_entry_t *pos;
	struct task_struct *task;
	unsigned long flags;
	int i, n, len, cnt;
	u32 b_select;
	char *phead;

	if (!status_info || size < 0 || dst >= VDSP_SIPC_ID_NR)
		return;
	len = strlen(status_info);
	for (i = 0;  i < SMSG_VALID_CH_NR; i++) {
		sbuf = sbufs[dst][i];
		if (!sbuf)
			continue;

		for (n = 0;  n < sbuf->ringnr && len < size; n++) {
			ring = &sbuf->rings[n];
			hd_op = &ring->header_op;

			if ((*(hd_op->rx_wt_p) - *(hd_op->rx_rd_p))
					< hd_op->rx_size)
				continue;

			snprintf(status_info + len,
				 size - len,
				 "ch-%d-ring-%d is full.\n",
				 sbuf->channel,
				 n);
			len = strlen(status_info);

			/*  show all rxwait task */
			spin_lock_irqsave(&ring->rxwait.lock, flags);
			cnt = 0;
			list_for_each_entry(pos,
					    &ring->rxwait.head,
					    entry) {
				task = vdsp_sbuf_wait_get_task(pos, &b_select);
				if (!task)
					continue;

				if (b_select)
					phead = "rxwait task";
				else
					phead = "select task";

				snprintf(
					 status_info + len,
					 size - len,
					 "%s %d: %s, state=0x%lx, pid=%d.\n",
					 phead,
					 cnt, task->comm,
					 task->state, task->pid);
				cnt++;
				len = strlen(status_info);
			}
			spin_unlock_irqrestore(&ring->rxwait.lock, flags);
		}
	}
}
EXPORT_SYMBOL_GPL(vdsp_sbuf_get_status);


MODULE_AUTHOR("Camera System Design");
MODULE_DESCRIPTION("SIPC/SBUF driver");
MODULE_LICENSE("GPL v2");
