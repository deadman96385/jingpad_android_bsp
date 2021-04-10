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
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/wait.h>

#include <linux/syscore_ops.h>

#include "vdsp_sipc.h"
#include "vdsp_sipc_priv.h"

#define USING_SHARE_MEM

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "[VDSP]VDSP_SMSG: %d %d %s : "\
	fmt, current->pid, __LINE__, __func__

#define SMSG_TXBUF_ADDR		(0)
#define SMSG_TXBUF_SIZE		(SZ_1K)
#define SMSG_RXBUF_ADDR		(SMSG_TXBUF_SIZE)
#define SMSG_RXBUF_SIZE		(SZ_1K)

#define SMSG_RINGHDR		(SMSG_TXBUF_SIZE + SMSG_RXBUF_SIZE)
#define SMSG_TXBUF_RDPTR	(SMSG_RINGHDR + 0)
#define SMSG_TXBUF_WRPTR	(SMSG_RINGHDR + 4)
#define SMSG_RXBUF_RDPTR	(SMSG_RINGHDR + 8)
#define SMSG_RXBUF_WRPTR	(SMSG_RINGHDR + 12)

#define SIPC_READL(addr)      readl((__force void __iomem *)(addr))
#define SIPC_WRITEL(b, addr)  writel(b, (__force void __iomem *)(addr))

#define HIGH_OFFSET_FLAG (0xFEFE)

static u8 g_wakeup_flag;

struct smsg_ipc *vdsp_smsg_ipcs[VDSP_SIPC_ID_NR];
EXPORT_SYMBOL_GPL(vdsp_smsg_ipcs);

static ushort debug_enable;

module_param_named(debug_enable, debug_enable, ushort, 0644);
static u8 channel2index[VDSP_SMSG_CH_NR + 1];

static int vdsp_smsg_ipc_smem_init(struct smsg_ipc *ipc);

void vdsp_smsg_init_channel2index(void)
{
	u16 i, j;

	for (i = 0; i < ARRAY_SIZE(channel2index); i++) {
		for (j = 0; j < SMSG_VALID_CH_NR; j++) {
			/* find the index of channel i */
			if (sipc_cfg[j].channel == i)
				break;
		}

		/* if not find, init with INVALID_CHANEL_INDEX,
		 * else init whith j
		 */
		if (j == SMSG_VALID_CH_NR)
			channel2index[i] = INVALID_CHANEL_INDEX;
		else
			channel2index[i] = j;
	}
}

static void vdsp_get_channel_status(u8 dst, char *status, int size)
{
	int i, len;
	struct smsg_channel *ch;

	len = strlen(status);
	for (i = 0;  i < SMSG_VALID_CH_NR && len < size; i++) {
		ch = vdsp_smsg_ipcs[dst]->channels[i];
		if (!ch)
			continue;
		if (SIPC_READL(ch->rdptr) < SIPC_READL(ch->wrptr))
			snprintf(
				status + len,
				size - len,
				"dst-%d-ch-%d: rd = %u, wr = %u.\n",
				dst,
				i,
				SIPC_READL(ch->rdptr),
				SIPC_READL(ch->wrptr)
				);
	}
}

static void vdsp_smsg_wakeup_print(struct smsg_ipc *ipc, struct smsg *msg)
{
	/* if the first msg come after the irq wake up by sipc,
	 * use prin_fo to output log
	 */
	if (g_wakeup_flag) {
		g_wakeup_flag = 0;
		pr_info("irq read smsg: dst=%d, channel=%d,type=%d, flag=0x%04x, value=0x%08x\n",
			ipc->dst,
			msg->channel,
			msg->type,
			msg->flag,
			msg->value);
	} else {
		pr_debug("irq read smsg: dst=%d, channel=%d,type=%d, flag=0x%04x, value=0x%08x\n",
			 ipc->dst,
			 msg->channel,
			 msg->type,
			 msg->flag,
			 msg->value);
	}
}

static void vdsp_smsg_die_process(struct smsg_ipc *ipc, struct smsg *msg)
{
	if (msg->type == VDSP_SMSG_TYPE_DIE) {
		if (debug_enable) {
			char sipc_status[100] = {0};

			vdsp_get_channel_status(ipc->dst,
					   sipc_status,
					   sizeof(sipc_status));
			sbuf_get_status(ipc->dst,
					sipc_status,
					sizeof(sipc_status));
			panic("cpcrash: %s", sipc_status);
			while (1)
				;
		}
	}
}

static void vdsp_smsg_msg_process(struct smsg_ipc *ipc, struct smsg *msg)
{
	struct smsg_channel *ch = NULL;
	u32 wr;
	u8 ch_index;

	vdsp_smsg_wakeup_print(ipc, msg);
	vdsp_smsg_die_process(ipc, msg);

	ch_index = channel2index[msg->channel];
	atomic_inc(&ipc->busy[ch_index]);

	pr_info("smsg:get IPC dst=%d msg channel=%d, type=%d, flag=0x%04x, value=0x%08x\n",
		 ipc->dst, msg->channel,
		 msg->type, msg->flag,
		 msg->value);

	if (msg->type >= VDSP_SMSG_TYPE_NR) {
		/* invalid msg */
		pr_info("invalid smsg: channel=%d, type=%d, flag=0x%04x, value=0x%08x\n",
			msg->channel, msg->type, msg->flag, msg->value);
		goto exit_msg_proc;
	}

	if (msg->type == VDSP_SMSG_TYPE_HIGH_OFFSET &&
		msg->flag == HIGH_OFFSET_FLAG) {
		/* high offset msg */
		ipc->high_offset = msg->value;
		pr_info("smsg:  high_offset = 0x%x\n",
			msg->value);
		goto exit_msg_proc;
	}

	ch = ipc->channels[ch_index];
	if (!ch) {
		if (ipc->states[ch_index] == CH_STAT_UNUSED &&
			msg->type == VDSP_SMSG_TYPE_OPEN &&
			msg->flag == VDSP_SMSG_OPEN_MAGIC) {
			ipc->states[ch_index] = CH_STAT_REMOTE_OPENED;
			pr_info("server CH_STAT_REMOTE_OPENED\n");
		}
		else
			/* drop this bad msg since channel
			 * is not opened
			 */
			pr_info("smsg channel %d not opened! drop smsg: type=%d, flag=0x%04x, value=0x%08x\n",
				msg->channel, msg->type,
				msg->flag, msg->value);

		goto exit_msg_proc;
	}

	if ((int)(SIPC_READL(ch->wrptr) - SIPC_READL(ch->rdptr)) >=
		SMSG_CACHE_NR) {
		/* msg cache is full, drop this msg */
		pr_info("smsg channel %d recv cache is full! drop smsg: type=%d, flag=0x%04x, value=0x%08x\n",
			msg->channel, msg->type, msg->flag, msg->value);
	} else {
		/* write smsg to cache */
		wr = SIPC_READL(ch->wrptr) & (SMSG_CACHE_NR - 1);
		memcpy(&ch->caches[wr], msg, sizeof(struct smsg));
		SIPC_WRITEL(SIPC_READL(ch->wrptr) + 1, ch->wrptr);
		pr_info("write smsg to cache ch wrptr:%d, rdptr:%d\n",
			SIPC_READL(ch->wrptr),
			SIPC_READL(ch->rdptr));
	}

	wake_up_interruptible_all(&ch->rxwait);
	__pm_wakeup_event(&ch->sipc_wake_lock, jiffies_to_msecs(HZ / 2));

exit_msg_proc:
	atomic_dec(&ipc->busy[ch_index]);
}


irqreturn_t vdsp_smsg_irq_handler(int irq, void *private)
{
	struct smsg_ipc *ipc = (struct smsg_ipc *)private;
	struct smsg *msg;
	uintptr_t rxpos;

	pr_info("%s, irq = %d\n",ipc->name, irq);

	if (ipc->rxirq_status(ipc->dst))
		ipc->rxirq_clear(ipc->dst);

	if (!ipc->smem_inited) {
		pr_info("%s: %s smem have not been inited!",
			__func__, ipc->name);
		return IRQ_HANDLED;
	}
	pr_info("*****************************************************\n");
	pr_info("IPC rxbuf_size[%d], rxbuf_rdptr[0x%lx][%d], rxbuf_wrptr[0x%lx][%d], txbuf_size[%d], txbuf_rdptr[0x%lx][%d], txbuf_wrptr[0x%lx][%d]\n",
		ipc->rxbuf_size, ipc->rxbuf_rdptr, SIPC_READL(ipc->rxbuf_rdptr),
		ipc->rxbuf_wrptr, SIPC_READL(ipc->rxbuf_wrptr),
		ipc->txbuf_size, ipc->txbuf_rdptr, SIPC_READL(ipc->txbuf_rdptr),
		ipc->txbuf_wrptr,  SIPC_READL(ipc->txbuf_wrptr));
	pr_info("*****************************************************\n");
	while (SIPC_READL(ipc->rxbuf_wrptr) != SIPC_READL(ipc->rxbuf_rdptr)) {
		rxpos = (SIPC_READL(ipc->rxbuf_rdptr) & (ipc->rxbuf_size - 1)) *
			sizeof(struct smsg) + ipc->rxbuf_addr;
		msg = (struct smsg *)rxpos;
		pr_info("irq get smsg: IPC wrptr=%u, rdptr=%u, rxpos=0x%lx\n",
			 SIPC_READL(ipc->rxbuf_wrptr),
			 SIPC_READL(ipc->rxbuf_rdptr),
			 rxpos);

		vdsp_smsg_msg_process(ipc, msg);
		/* update smsg rdptr */
		SIPC_WRITEL(SIPC_READL(ipc->rxbuf_rdptr) + 1, ipc->rxbuf_rdptr);
	}

	return IRQ_HANDLED;
}
EXPORT_SYMBOL_GPL(vdsp_smsg_irq_handler);

static phys_addr_t vdsp_smsg_send_smem_addr(void *args)
{
	phys_addr_t addr = 0;
	struct smsg_ipc *ipc = (struct smsg_ipc *)args;

	vdsp_share_mem_iommu_map(ipc->vdsp_mem_desc,
				&ipc->ring_ion,
				IOMMU_ALL);

	addr = ipc->ring_ion.iova[0];

	pr_info("addr:0x%lx", (unsigned long)ipc->ring_ion.iova[0]);

	return addr;
}


static void vdsp_smsg_ipc_init_irq_callback(struct smsg_ipc *ipc)
{
#if 1
	int ret1 = 0, ret2 = 0;

	switch (ipc->type) {
	case SIPC_BASE_IPI:
		/* explicitly call irq handler in case of missing irq on boot */
		vdsp_smsg_irq_handler(ipc->irq, ipc);

		pr_info("register ipi handler vdsp_smsg_irq_handler\n");
		/* register IPI irq */
#if 0
		ret2 = ret1 = request_irq(ipc->irq,
				   vdsp_smsg_irq_handler,
				   IRQF_NO_SUSPEND,
				   ipc->name,
				   ipc);
#else
		ipc->vdsp_ipi_desc->ops->irq_register(3,
						     vdsp_smsg_irq_handler,
						     ipc);
#endif
		break;
	default:
		break;
	}
	pr_info("%s:%s ret1=%d, ret2=%d\n", __func__, ipc->name, ret1, ret2);
#else
	if (ipc->dst == 9) {
		ipc->vdsp_ipi_desc->ops->irq_register(3, vdsp_smsg_irq_handler, ipc);
		vdsp_ipi_set_msg_ion(3, &ipc->ring_ion);
	}
#endif
}

static int vdsp_smsg_ipc_smem_init(struct smsg_ipc *ipc)
{
	void __iomem *p;
	int ret = 1;

	if (ipc->smem_inited)
		return 0;

	ipc->smem_inited = 1;
	pr_debug("%s: %s!\n", __func__, ipc->name);
#ifdef USING_SHARE_MEM
	if (ipc->type == SIPC_BASE_IPI) {
		ipc->ring_base = NULL;
		ipc->ring_size = SZ_4K;
		ret = vdsp_share_mem_alloc(ipc->vdsp_mem_desc,
						     &ipc->ring_ion,
						     ION_HEAP_ID_MASK_SYSTEM,
						     SZ_4K);

		if (ret) {
			pr_err("IPC ipc->ring_base = NULL, ring_size = 0x%x\n",
				ipc->ring_size);
			return -ENOMEM;
		}
	}
#endif /* USING_SHARE_MEM */

	if (!ret) {
#ifdef USING_SHARE_MEM
		vdsp_share_mem_kmap(ipc->vdsp_mem_desc, &ipc->ring_ion);
		ipc->ring_base = (void __iomem *)ipc->ring_ion.addr_k[0];
#endif /* USING_SHARE_MEM */

		if (!ipc->ring_base) {
			vdsp_share_mem_free(ipc->vdsp_mem_desc, &ipc->ring_ion);
			pr_err("ioremap failed!\n");
			return -ENOMEM;
		}

		/* assume client is boot later than host */
		if (!ipc->client) {
			for (p = ipc->ring_base; p < ipc->ring_base + ipc->ring_size;) {
#ifdef CONFIG_64BIT
				*(uint64_t *)p = 0x0;
				p += sizeof(uint64_t);
#else
				*(u32 *)p = 0x0;
				p += sizeof(u32);
#endif
			}
		}

		if (ipc->client) {
			/* clent mode, tx is host rx , rx is host tx*/
			ipc->smem_vbase = (void *)ipc->ring_base;
			ipc->txbuf_size = SMSG_RXBUF_SIZE /
				sizeof(struct smsg);
			ipc->txbuf_addr = (uintptr_t)ipc->ring_base +
				SMSG_RXBUF_ADDR;
			ipc->txbuf_rdptr = (uintptr_t)ipc->ring_base +
				SMSG_RXBUF_RDPTR;
			ipc->txbuf_wrptr = (uintptr_t)ipc->ring_base +
				SMSG_RXBUF_WRPTR;
			ipc->rxbuf_size = SMSG_TXBUF_SIZE /
				sizeof(struct smsg);
			ipc->rxbuf_addr = (uintptr_t)ipc->ring_base +
				SMSG_TXBUF_ADDR;
			ipc->rxbuf_rdptr = (uintptr_t)ipc->ring_base +
				SMSG_TXBUF_RDPTR;
			ipc->rxbuf_wrptr = (uintptr_t)ipc->ring_base +
				SMSG_TXBUF_WRPTR;
		} else {
			ipc->smem_vbase = (void *)ipc->ring_base;
			ipc->txbuf_size = SMSG_TXBUF_SIZE /
				sizeof(struct smsg);
			ipc->txbuf_addr = (uintptr_t)ipc->ring_base +
				SMSG_TXBUF_ADDR;
			ipc->txbuf_rdptr = (uintptr_t)ipc->ring_base +
				SMSG_TXBUF_RDPTR;
			ipc->txbuf_wrptr = (uintptr_t)ipc->ring_base +
				SMSG_TXBUF_WRPTR;
			ipc->rxbuf_size = SMSG_RXBUF_SIZE /
				sizeof(struct smsg);
			ipc->rxbuf_addr = (uintptr_t)ipc->ring_base +
				SMSG_RXBUF_ADDR;
			ipc->rxbuf_rdptr = (uintptr_t)ipc->ring_base +
				SMSG_RXBUF_RDPTR;
			ipc->rxbuf_wrptr = (uintptr_t)ipc->ring_base +
				SMSG_RXBUF_WRPTR;
		}
	}

	pr_info("IPC rxbuf_size[%d], rxbuf_rdptr[0x%lx], rxbuf_wrptr[0x%lx], txbuf_size[%d], txbuf_rdptr[0x%lx], txbuf_wrptr[0x%lx]\n",
		ipc->rxbuf_size, ipc->rxbuf_rdptr, ipc->rxbuf_wrptr,
		ipc->txbuf_size, ipc->txbuf_rdptr, ipc->txbuf_wrptr);


	/*
	 * Call XRP interface to send share memory to VDSP
	 * XRP Send Message
	 *
	 * if Using MAILBOX, Can Send Message Via mailbox,
	 * But MUST Create thread to do.
	 */
	if (ipc && ipc->vdsp_mem_desc && ipc->vdsp_mem_desc->ops &&
	    ipc->vdsp_mem_desc->ops->mem_register_callback) {
		pr_info("register vdsp_smsg_send_smem_addr\n");
		ipc->vdsp_mem_desc->ops->mem_register_callback(
					ipc->vdsp_mem_desc,
					CB_MSG,
					vdsp_smsg_send_smem_addr,
					ipc);
	} else {
		pr_info("error, not register\n");
	}

	return 0;
}

void vdsp_smsg_ipc_create(struct smsg_ipc *ipc)
{
	pr_info("%s: %s\n", __func__, ipc->name);

	vdsp_smsg_ipc_init_irq_callback(ipc);
	vdsp_smsg_ipcs[ipc->dst] = ipc;
	pr_info("ipc->dst = %d\n", ipc->dst);

	vdsp_smsg_ipc_smem_init(ipc);
}

void vdsp_smsg_ipc_destroy(struct smsg_ipc *ipc)
{
#ifdef USING_SHARE_MEM
	vdsp_share_mem_unkmap(ipc->vdsp_mem_desc, &ipc->ring_ion);
	vdsp_share_mem_free(ipc->vdsp_mem_desc, &ipc->ring_ion);
#endif	/* USING_SHARE_MEM */

	if (ipc->type == SIPC_BASE_IPI) {
		free_irq(ipc->irq, ipc);
	}

	if (!IS_ERR_OR_NULL(ipc->thread))
		kthread_stop(ipc->thread);

	vdsp_smsg_ipcs[ipc->dst] = NULL;
}

int vdsp_sipc_get_wakeup_flag(void)
{
	return (int)g_wakeup_flag;
}
EXPORT_SYMBOL_GPL(vdsp_sipc_get_wakeup_flag);

void vdsp_sipc_set_wakeup_flag(void)
{
	g_wakeup_flag = 1;
}
EXPORT_SYMBOL_GPL(vdsp_sipc_set_wakeup_flag);

void vdsp_sipc_clear_wakeup_flag(void)
{
	g_wakeup_flag = 0;
}
EXPORT_SYMBOL_GPL(vdsp_sipc_clear_wakeup_flag);

int vdsp_smsg_ch_wake_unlock(u8 dst, u8 channel)
{
	struct smsg_ipc *ipc = vdsp_smsg_ipcs[dst];
	struct smsg_channel *ch;
	u8 ch_index;

	ch_index = channel2index[channel];
	if (ch_index == INVALID_CHANEL_INDEX) {
		pr_err("%s:channel %d invalid!\n", __func__, channel);
		return -EINVAL;
	}

	if (!ipc)
		return -ENODEV;

	ch = ipc->channels[ch_index];
	if (!ch)
		return -ENODEV;

	__pm_relax(&ch->sipc_wake_lock);
	return 0;
}
EXPORT_SYMBOL_GPL(vdsp_smsg_ch_wake_unlock);

int vdsp_smsg_ch_open(u8 dst, u8 channel, int timeout)
{
	struct smsg_ipc *ipc = vdsp_smsg_ipcs[dst];
	struct smsg_channel *ch;
	struct smsg mopen;
	struct smsg mrecv;
	int rval = 0;
	u8 ch_index;

	ch_index = channel2index[channel];
	if (ch_index == INVALID_CHANEL_INDEX) {
		pr_err("%s:channel %d invalid!\n", __func__, channel);
		return -EINVAL;
	}

	if (!ipc)
		return -ENODEV;

	ch = kzalloc(sizeof(*ch), GFP_KERNEL);
	if (!ch)
		return -ENOMEM;

	sprintf(ch->wake_lock_name, "smsg-%d-%d", dst, channel);
	wakeup_source_init(&ch->sipc_wake_lock,
			   ch->wake_lock_name);

	atomic_set(&ipc->busy[ch_index], 1);
	init_waitqueue_head(&ch->rxwait);
	mutex_init(&ch->rxlock);
	ipc->channels[ch_index] = ch;

	pr_info("channel %d-%d send open msg!\n",
		dst, channel);

	vdsp_smsg_set(&mopen,
		     channel,
		     VDSP_SMSG_TYPE_OPEN,
		     VDSP_SMSG_OPEN_MAGIC,
		     0);
	rval = vdsp_smsg_send(dst, &mopen, timeout);
	if (rval != 0) {
		pr_err("%s: channel %d-%d send open msg error = %d!\n",
		       __func__, dst, channel, rval);
		ipc->states[ch_index] = CH_STAT_UNUSED;
		ipc->channels[ch_index] = NULL;
		atomic_dec(&ipc->busy[ch_index]);
		/* guarantee that channel resource isn't used in irq handler  */
		while (atomic_read(&ipc->busy[ch_index]))
			;
		wakeup_source_trash(&ch->sipc_wake_lock);
		kfree(ch);

		return rval;
	}

	pr_info("channel %d-%d send send msg [%d -- %d]!\n",
		dst, channel, VDSP_SMSG_TYPE_OPEN, VDSP_SMSG_OPEN_MAGIC);

	/* open msg might be got before */
	if (ipc->states[ch_index] == CH_STAT_REMOTE_OPENED)
		goto open_done;

	ipc->states[ch_index] = CH_STAT_NATIVE_OPENED;

	do {
		vdsp_smsg_set(&mrecv, channel, 0, 0, 0);
		rval = vdsp_smsg_recv(dst, &mrecv, timeout);
		if (rval != 0) {
			pr_err("%s: channel %d-%d smsg receive error = %d!\n",
			       __func__, dst, channel, rval);
			ipc->states[ch_index] = CH_STAT_UNUSED;
			ipc->channels[ch_index] = NULL;
			atomic_dec(&ipc->busy[ch_index]);
			/* guarantee that channel resource isn't used
			 * in irq handler
			 */
			while (atomic_read(&ipc->busy[ch_index]))
				;
			wakeup_source_trash(&ch->sipc_wake_lock);
			kfree(ch);
			return rval;
		}
	} while (mrecv.type != VDSP_SMSG_TYPE_OPEN ||
		 mrecv.flag != VDSP_SMSG_OPEN_MAGIC);

	pr_info("%s: channel %d-%d receive open msg!\n",
		__func__, dst, channel);

open_done:
	pr_info("%s: channel %d-%d success\n", __func__, dst, channel);
	ipc->states[ch_index] = CH_STAT_OPENED;
	atomic_dec(&ipc->busy[ch_index]);

	return 0;
}
EXPORT_SYMBOL_GPL(vdsp_smsg_ch_open);

int vdsp_smsg_ch_close(u8 dst, u8 channel,  int timeout)
{
	struct smsg_ipc *ipc = vdsp_smsg_ipcs[dst];
	struct smsg_channel *ch;
	struct smsg mclose;
	u8 ch_index;

	ch_index = channel2index[channel];
	if (ch_index == INVALID_CHANEL_INDEX) {
		pr_err("%s:channel %d invalid!\n", __func__, channel);
		return -EINVAL;
	}

	ch = ipc->channels[ch_index];
	if (!ch)
		return 0;

	vdsp_smsg_set(&mclose,
		     channel,
		     VDSP_SMSG_TYPE_CLOSE,
		     VDSP_SMSG_CLOSE_MAGIC,
		     0);
	vdsp_smsg_send(dst, &mclose, timeout);

	ipc->states[ch_index] = CH_STAT_CLOSED;
	wake_up_interruptible_all(&ch->rxwait);

	/* wait for the channel being unused */
	while (atomic_read(&ipc->busy[ch_index]))
		;

	/* maybe channel has been free for smsg_ch_open failed */
	if (ipc->channels[ch_index]) {
		ipc->channels[ch_index] = NULL;
		/* guarantee that channel resource isn't used in irq handler */
		while (atomic_read(&ipc->busy[ch_index]))
			;
		wakeup_source_trash(&ch->sipc_wake_lock);
		kfree(ch);
	}

	/* finally, update the channel state*/
	ipc->states[ch_index] = CH_STAT_UNUSED;

	return 0;
}
EXPORT_SYMBOL_GPL(vdsp_smsg_ch_close);

int vdsp_smsg_senddie(u8 dst)
{
	struct smsg msg;
	struct smsg_ipc *ipc = vdsp_smsg_ipcs[dst];
	uintptr_t txpos;
	int rval = 0;

	if (!ipc)
		return -ENODEV;

	msg.channel = VDSP_SMSG_CH_CTRL;
	msg.type = VDSP_SMSG_TYPE_DIE;
	msg.flag = 0;
	msg.value = 0;

	if (!ipc->ring_base) {
		if ((int)(SIPC_READL(ipc->txbuf_wrptr) -
			SIPC_READL(ipc->txbuf_rdptr)) >= ipc->txbuf_size) {
			pr_info("smsg_send: smsg txbuf is full!\n");
			rval = -EBUSY;
			goto send_failed;
		}

		/* calc txpos and write smsg */
		txpos = (SIPC_READL(ipc->txbuf_wrptr) & (ipc->txbuf_size - 1)) *
			sizeof(struct smsg) + ipc->txbuf_addr;
		memcpy((void *)txpos, &msg, sizeof(struct smsg));

		pr_debug("write smsg: wrptr=%u, rdptr=%u, txpos=0x%lx\n",
			 SIPC_READL(ipc->txbuf_wrptr),
			 SIPC_READL(ipc->txbuf_rdptr),
			 txpos);

		/* update wrptr */
		SIPC_WRITEL(SIPC_READL(ipc->txbuf_wrptr) + 1, ipc->txbuf_wrptr);
	}

	ipc->txirq_trigger(ipc->dst, *((u64 *)&msg));
send_failed:

	return rval;
}
EXPORT_SYMBOL_GPL(vdsp_smsg_senddie);

int vdsp_smsg_send(u8 dst, struct smsg *msg, int timeout)
{
	struct smsg_ipc *ipc = vdsp_smsg_ipcs[dst];
	uintptr_t txpos;
	int rval = 0;
	unsigned long flags;
	u8 ch_index;

	ch_index = channel2index[msg->channel];
	pr_info("channel[%d], ch_index[%d]\n", msg->channel, ch_index);

	if (ch_index == INVALID_CHANEL_INDEX) {
		pr_err("%s:channel %d invalid!\n", __func__, msg->channel);
		return -EINVAL;
	}

	if (!ipc)
		return -ENODEV;

	if (!ipc->channels[ch_index]) {
		pr_err("%s: channel %d not inited!\n", __func__, msg->channel);
		return -ENODEV;
	}

	if (ipc->states[ch_index] != CH_STAT_OPENED &&
	    msg->type != VDSP_SMSG_TYPE_OPEN &&
	    msg->type != VDSP_SMSG_TYPE_CLOSE) {
		pr_err("%s: channel %d not opened!\n", __func__, msg->channel);
		return -EINVAL;
	}

	pr_info("%s: dst=%d, channel=%d, timeout=%d, suspend=%d\n",
		 __func__, dst, msg->channel, timeout, ipc->suspend);

	if (ipc->suspend) {
		rval = wait_event_interruptible(
				ipc->suspend_wait,
				!ipc->suspend);
		if (rval) {
			pr_info("%s:rval = %d!\n", __func__, rval);
			return -EINVAL;
		}
	}
	pr_info("send smsg: channel=%d, type=%d, flag=0x%04x, value=0x%08x\n",
		 msg->channel, msg->type, msg->flag, msg->value);

	spin_lock_irqsave(&ipc->txpinlock, flags);

	pr_info("IPC rxbuf_size[%d], rxbuf_rdptr[0x%lx][%d]"
			"rxbuf_wrptr[0x%lx][%d], txbuf_size[%d]"
			"txbuf_rdptr[0x%lx][%d], txbuf_wrptr[0x%lx][%d]\n",
		ipc->rxbuf_size, ipc->rxbuf_rdptr, SIPC_READL(ipc->rxbuf_rdptr),
		ipc->rxbuf_wrptr,SIPC_READL(ipc->rxbuf_wrptr),
		ipc->txbuf_size, ipc->txbuf_rdptr, SIPC_READL(ipc->txbuf_rdptr),
		ipc->txbuf_wrptr, SIPC_READL(ipc->txbuf_wrptr));
	if (ipc->ring_base) {
		if (((int)(SIPC_READL(ipc->txbuf_wrptr) -
				SIPC_READL(ipc->txbuf_rdptr)) >=
				ipc->txbuf_size)) {
			pr_info("%s: smsg txbuf is full!\n", __func__);
			rval = -EBUSY;
			goto send_failed;
		}

		/* calc txpos and write smsg */
		txpos = (SIPC_READL(ipc->txbuf_wrptr) & (ipc->txbuf_size - 1)) *
			sizeof(struct smsg) + ipc->txbuf_addr;
		memcpy((void *)txpos, msg, sizeof(struct smsg));

		pr_info("write smsg: ipc tx wrptr=%d, tx rdptr=%d, txpos=0x%lx\n",
			 SIPC_READL(ipc->txbuf_wrptr),
			 SIPC_READL(ipc->txbuf_rdptr),
			 txpos);

		/* update wrptr */
		SIPC_WRITEL(SIPC_READL(ipc->txbuf_wrptr) + 1, ipc->txbuf_wrptr);
		pr_info("update : ipc tx wrptr=%d, tx rdptr=%d\n",
			 SIPC_READL(ipc->txbuf_wrptr),
			 SIPC_READL(ipc->txbuf_rdptr),
			 txpos);
	}

	pr_info("Changdou 77777 txirq_trigger\n");
	ipc->txirq_trigger(ipc->dst, *(u64 *)msg);

send_failed:
	spin_unlock_irqrestore(&ipc->txpinlock, flags);

	return rval;
}
EXPORT_SYMBOL_GPL(vdsp_smsg_send);

int vdsp_smsg_recv(u8 dst, struct smsg *msg, int timeout)
{
	struct smsg_ipc *ipc = vdsp_smsg_ipcs[dst];
	struct smsg_channel *ch;
	u32 rd;
	int rval = 0;
	u8 ch_index;

	ch_index = channel2index[msg->channel];
	if (ch_index == INVALID_CHANEL_INDEX) {
		pr_err("%s:channel %d invalid!\n", __func__, msg->channel);
		return -EINVAL;
	}

	if (!ipc)
		return -ENODEV;

	atomic_inc(&ipc->busy[ch_index]);

	ch = ipc->channels[ch_index];

	if (!ch) {
		pr_err("%s: channel %d not opened!\n", __func__, msg->channel);
		atomic_dec(&ipc->busy[ch_index]);
		return -ENODEV;
	}

	pr_info("%s: dst=%d, channel=%d, timeout=%d"
			"ch_index = %d CH wrptr%d, rdptr%d\n",
		 __func__, dst, msg->channel, timeout, ch_index,
		 SIPC_READL(ch->wrptr), SIPC_READL(ch->rdptr));

	if (timeout == 0) {
		if (!mutex_trylock(&ch->rxlock)) {
			pr_err("dst=%d, channel=%d recv smsg busy!\n",
			       dst, msg->channel);
			atomic_dec(&ipc->busy[ch_index]);

			return -EBUSY;
		}

		/* no wait */
		if (SIPC_READL(ch->wrptr) == SIPC_READL(ch->rdptr)) {
			pr_info("dst=%d, channel=%d smsg rx cache is empty!\n",
				dst, msg->channel);

			rval = -ENODATA;

			goto recv_failed;
		}
	} else if (timeout < 0) {
		mutex_lock(&ch->rxlock);
		/* wait forever */
		pr_info("wait event forever in smsg recv~\n");
		rval = wait_event_interruptible(
				ch->rxwait,
				(SIPC_READL(ch->wrptr) !=
				 SIPC_READL(ch->rdptr)) ||
				(ipc->states[ch_index] == CH_STAT_CLOSED));
		pr_info("out wait event in smsg recv "
				"rval %d ch wrptr%d, rdptr%d\n", rval,
			SIPC_READL(ch->wrptr),
			SIPC_READL(ch->rdptr));
		if (rval < 0) {
			pr_info("%s: dst=%d, channel=%d wait interrupted!\n",
				 __func__, dst, msg->channel);

			goto recv_failed;
		}

		if (ipc->states[ch_index] == CH_STAT_CLOSED) {
			pr_info("%s: dst=%d, channel=%d channel is free!\n",
				__func__, dst, msg->channel);

			rval = -EIO;

			goto recv_failed;
		}
	} else {
		mutex_lock(&ch->rxlock);
		/* wait timeout */
		rval = wait_event_interruptible_timeout(
			ch->rxwait,
			(SIPC_READL(ch->wrptr) != SIPC_READL(ch->rdptr)) ||
			(ipc->states[ch_index] == CH_STAT_CLOSED),
			timeout);
		if (rval < 0) {
			pr_info("%s: dst=%d, channel=%d wait interrupted!\n",
				 __func__, dst, msg->channel);

			goto recv_failed;
		} else if (rval == 0) {
			pr_info("%s: dst=%d, channel=%d wait timeout!\n",
				 __func__, dst, msg->channel);

			rval = -ETIME;

			goto recv_failed;
		}

		if (ipc->states[ch_index] == CH_STAT_CLOSED) {
			pr_info("%s: dst=%d, channel=%d channel is free!\n",
				__func__, dst, msg->channel);

			rval = -EIO;

			goto recv_failed;
		}
	}

	pr_info("IPC rxbuf_size[%d], rxbuf_rdptr[0x%lx][%d]"
			"rxbuf_wrptr[0x%lx][%d], txbuf_size[%d]"
			"txbuf_rdptr[0x%lx][%d], txbuf_wrptr[0x%lx][%d]\n",
		ipc->rxbuf_size, ipc->rxbuf_rdptr, SIPC_READL(ipc->rxbuf_rdptr),
		ipc->rxbuf_wrptr,SIPC_READL(ipc->rxbuf_wrptr),
		ipc->txbuf_size, ipc->txbuf_rdptr, SIPC_READL(ipc->txbuf_rdptr),
		ipc->txbuf_wrptr, SIPC_READL(ipc->txbuf_wrptr));
	/* read smsg from cache */
	rd = SIPC_READL(ch->rdptr) & (SMSG_CACHE_NR - 1);
	memcpy(msg, &ch->caches[rd], sizeof(struct smsg));
	SIPC_WRITEL(SIPC_READL(ch->rdptr) + 1, ch->rdptr);

	if (!ipc->ring_base)
		pr_info("read smsg: dst=%d, channel=%d"
				"CH wrptr=%d, ch rdptr=%d, rd=%d\n",
			 dst,
			 msg->channel,
			 SIPC_READL(ch->wrptr),
			 SIPC_READL(ch->rdptr),
			 rd);

	pr_info("recv smsg: dst=%d, channel=%d"
			"type=%d, flag=0x%04x, value=0x%08x, rval = %d\n",
		 dst, msg->channel, msg->type, msg->flag, msg->value, rval);

recv_failed:
	mutex_unlock(&ch->rxlock);
	atomic_dec(&ipc->busy[ch_index]);
	return rval;
}
EXPORT_SYMBOL_GPL(vdsp_smsg_recv);

u8 vdsp_sipc_channel2index(u8 channel)
{
	return channel2index[channel];
}
EXPORT_SYMBOL_GPL(vdsp_sipc_channel2index);


MODULE_AUTHOR("Camera System Design");
MODULE_DESCRIPTION("SIPC/SMSG driver");
MODULE_LICENSE("GPL v2");
