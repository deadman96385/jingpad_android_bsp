/**
 * sprd-musbhsdmac - Spreadtrum MUSB Specific Glue layer
 *
 * Copyright (c) 2016 Spreadtrum Co., Ltd.
 * http://www.spreadtrum.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2  of
 * the License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "musb_core.h"
#include "sprd_musbhsdma.h"

void invalidate_dcache_range(unsigned long start, unsigned long stop);
void flush_dcache_range(unsigned long start, unsigned long stop);

 unsigned char linklist_tx[12] __attribute__((aligned (64)));
 unsigned char linklist_rx[12] __attribute__((aligned (64)));

static void sprd_dma_channel_release(struct dma_channel *channel);

static void sprd_dma_controller_stop(struct sprd_musb_dma_controller
				*controller)
{
	struct musb *musb = controller->private_data;
	struct dma_channel *channel;
	u32 bit;

	if (controller->used_channels != 0) {
		dev_err(musb->controller,
			"Stopping DMA controller while channel active\n");

		for (bit = 0; bit < MUSB_DMA_CHANNELS; bit++) {
			if (controller->used_channels & (1 << bit)) {
				channel = &controller->channel[bit].channel;
				sprd_dma_channel_release(channel);

				if (!controller->used_channels)
					break;
			}
		}
	}
}

/*alloc dma channel number*/
static struct dma_channel *sprd_dma_channel_allocate(struct dma_controller *c,
				struct musb_hw_ep *hw_ep, u8 transmit)
{
	struct sprd_musb_dma_controller *controller = container_of(c,
			struct sprd_musb_dma_controller, controller);
	struct sprd_musb_dma_channel *musb_channel = NULL;
	struct dma_channel *channel = NULL;
	u8 bit;
	u16 csr;
	struct musb *musb = controller->private_data;

	bit = hw_ep->epnum;

	if (transmit) {
		musb_channel = &(controller->channel[bit]);
		controller->used_channels |= (1 << bit);
		musb_channel->idx = bit;
		/* CONFIG DMA MODE */
		csr = musb_readw(hw_ep->regs, MUSB_TXCSR);
		csr |= MUSB_TXCSR_DMAMODE | MUSB_TXCSR_DMAENAB |
			MUSB_TXCSR_AUTOSET;
		musb_writew(hw_ep->regs, MUSB_TXCSR, csr);
	} else {
		musb_channel = &(controller->channel[bit + 15]);
		controller->used_channels |= (1 << (bit + 15));
		musb_channel->idx = bit + 15;
		/* CONFIG DMA MODE */
		csr = musb_readw(hw_ep->regs, MUSB_RXCSR);
		csr |= MUSB_RXCSR_DMAMODE | MUSB_RXCSR_DMAENAB |
			MUSB_RXCSR_AUTOCLEAR;
		musb_writew(hw_ep->regs, MUSB_RXCSR, csr);
	}

	musb_channel->controller = controller;
	musb_channel->ep_num = bit;
	musb_channel->transmit = transmit;
	channel = &(musb_channel->channel);
	channel->private_data = musb_channel;
	channel->status = MUSB_DMA_STATUS_FREE;
	channel->max_len = 0xffff;
	/* Tx => mode 1; Rx => mode 0 */
	channel->desired_mode = transmit;
	channel->actual_len = 0;

	dev_vdbg(musb->controller, "sprd_dma_channel_allocate %d,0x%p\n",
			transmit, musb_channel);

	return channel;
}

static void sprd_dma_channel_release(struct dma_channel *channel)
{
	struct sprd_musb_dma_channel *musb_channel = channel->private_data;

	channel->actual_len = 0;

	musb_channel->controller->used_channels &=
		~(1 << musb_channel->idx);

	channel->status = MUSB_DMA_STATUS_UNKNOWN;
}

static void sprd_configure_channel(struct dma_channel *channel,
				u16 packet_sz, u8 transmit,
				dma_addr_t dma_addr, u32 len)
{
	struct sprd_musb_dma_channel *musb_channel = channel->private_data;
	struct sprd_musb_dma_controller *controller = musb_channel->controller;
	void __iomem *mbase = controller->base;
	u8 bchannel = musb_channel->idx;
	u32 csr = 0;

	if (transmit) {
		/* enable linklist end interrupt */
		csr = musb_readl(mbase, MUSB_DMA_CHN_INTR(bchannel));
		csr |= CHN_LLIST_INT_EN;
		musb_writel(mbase, MUSB_DMA_CHN_INTR(bchannel), csr);

		/* set linklist pointer */
		musb_writel(mbase, MUSB_DMA_CHN_LLIST_PTR(bchannel),
					(u32)linklist_tx);

		/* enable channel and trigger rx dma transfer */
		csr = musb_readl(mbase, MUSB_DMA_CHN_CFG(bchannel));
		csr |= CHN_EN;
		musb_writel(mbase, MUSB_DMA_CHN_CFG(bchannel), csr);
	} else {
		/* enable linklist end and rx last interrupt */
		csr = musb_readl(mbase, MUSB_DMA_CHN_INTR(bchannel));
		csr |= CHN_USBRX_INT_EN | CHN_LLIST_INT_EN;
		musb_writel(mbase, MUSB_DMA_CHN_INTR(bchannel), csr);

		/* set linklist pointer */
		musb_writel(mbase, MUSB_DMA_CHN_LLIST_PTR(bchannel),
					(u32)linklist_rx);
		/* enable channel and trigger rx dma transfer */
		csr = musb_readl(mbase, MUSB_DMA_CHN_CFG(bchannel));
		csr |= CHN_EN;
		musb_writel(mbase, MUSB_DMA_CHN_CFG(bchannel), csr);
	}
}

static int sprd_dma_channel_program(struct dma_channel *channel,
				u16 packet_sz, u8 mode,
				dma_addr_t dma_addr, u32 len)
{
	struct sprd_musb_dma_channel *musb_channel = channel->private_data;
	struct sprd_musb_dma_controller *controller = musb_channel->controller;
	struct musb *musb = controller->private_data;
	unsigned char *q;
	unsigned long cache_start = 0;
	unsigned long cache_end = 0;
	u32 length;

	dev_vdbg(musb->controller, "ep%d-%s pkt_sz %d, dma_addr 0x%x length %d, mode %d\n",
		musb_channel->ep_num,
		musb_channel->transmit ? "Tx" : "Rx",
		packet_sz, dma_addr, len, mode);

	if (channel->status == MUSB_DMA_STATUS_UNKNOWN ||
		channel->status == MUSB_DMA_STATUS_BUSY)
		return -EINVAL;

	/* Let targets check/tweak the arguments */
	if (musb->ops->adjust_channel_params) {
		int ret = musb->ops->adjust_channel_params(channel,
			packet_sz, &mode, &dma_addr, &len);
		if (ret)
			return ret;
	}

	/*
	 * The DMA engine in RTL1.8 and above cannot handle
	 * DMA addresses that are not aligned to a 4 byte boundary.
	 * It ends up masking the last two bits of the address
	 * programmed in DMA_ADDR.
	 *
	 * Fail such DMA transfers, so that the backup PIO mode
	 * can carry out the transfer
	 */
	if ((musb->hwvers >= MUSB_HWVERS_1800) && (dma_addr % 4))
		return -EINVAL;

    if(musb_channel->transmit) {
		cache_start = (u64)dma_addr;
		if (len % 64)
			length = len - (len % 64) + 64;
		else
			length = len;
		cache_end = cache_start + length;
		flush_dcache_range(cache_start, cache_end);
    } else {
    		if (len % 64)
			length = len - (len % 64) + 64;
		else
			length = len;

		cache_start = (unsigned long)dma_addr;
		cache_end = cache_start + length;
		invalidate_dcache_range(cache_start, cache_end);
    }

	channel->actual_len = 0;
	musb_channel->addr = (unsigned int)dma_addr;
	musb_channel->frag_len = 32;
	musb_channel->blk_len = len;
	musb_channel->max_packet_sz = packet_sz;
	musb_channel->ioc = 1;
	musb_channel->sp = 0;
	musb_channel->list_end = 1;
	channel->status = MUSB_DMA_STATUS_BUSY;

	if (musb_channel->transmit)
		q = &linklist_tx[0];
	else
		q = &linklist_rx[0];

	memset(q, 0, sizeof(*q));

	memcpy(q, &musb_channel->addr, 4);
	q += 4;

	memcpy(q, &musb_channel->frag_len, 2);
	q += 2;

	memcpy(q, &musb_channel->blk_len, 2);
	q += 2;

	*q = (musb_channel->ioc << 2) | (musb_channel->sp << 1) |
		musb_channel->list_end;
	q += 4;

	if(musb_channel->transmit) {
		cache_start = (unsigned long)(&musb_channel);
		cache_end = cache_start + 64;
		flush_dcache_range(cache_start, cache_end);

		cache_start = (unsigned long)(&linklist_tx);
		cache_end = cache_start + 64;
		flush_dcache_range(cache_start, cache_end);
	} else {
		cache_start = (unsigned long)(&musb_channel) & 0xffffff40;
		cache_end = cache_start + 64;
		invalidate_dcache_range(cache_start, cache_end);
//		dev_dbg(musb->controller,"%p\n",&musb_channel);

		cache_start = (unsigned long)(&linklist_rx);
		cache_end = cache_start + 64;
		invalidate_dcache_range(cache_start, cache_end);
	}

	sprd_configure_channel(channel, packet_sz, mode, dma_addr, len);

	return 0;
}

static int sprd_dma_channel_abort(struct dma_channel *channel)
{
	struct sprd_musb_dma_channel *musb_channel = channel->private_data;
	struct sprd_musb_dma_controller *controller = musb_channel->controller;
	void __iomem *mbase = controller->base;
	struct musb *musb = controller->private_data;
	u8 bchannel = musb_channel->idx;
	int offset;
	u16 csr;

	if (channel->status == MUSB_DMA_STATUS_BUSY) {
		if (musb_channel->transmit) {
			offset = 0x100 + musb_channel->ep_num * 0x10 + MUSB_TXCSR;

			/*
			 * The programming guide says that we must clear
			 * the DMAENAB bit before the DMAMODE bit...
			 */
			csr = musb_readl(mbase, offset);
			csr &= ~(MUSB_TXCSR_AUTOSET | MUSB_TXCSR_DMAENAB);
			musb_writel(mbase, offset, csr);
			csr &= ~MUSB_TXCSR_DMAMODE;
			musb_writel(mbase, offset, csr);
		} else {
			offset = 0x100 + musb_channel->ep_num * 0x10 + MUSB_RXCSR;

			csr = musb_readl(mbase, offset);
			csr &= ~(MUSB_RXCSR_AUTOCLEAR |
				 MUSB_RXCSR_DMAENAB |
				 MUSB_RXCSR_DMAMODE);
			musb_writel(mbase, offset, csr);
		}

		musb_writel(mbase, MUSB_DMA_CHN_LLIST_PTR(bchannel), 0);
		musb_write_dma_addr(mbase, bchannel, 0);
		channel->status = MUSB_DMA_STATUS_FREE;
	}

	return 0;
}

static void sprd_musb_dma_completion(struct musb *musb, u8 epnum, u8 transmit)
{
	struct musb_ep *musb_ep;
	struct musb_request *musb_req;
	struct usb_request *request;
	struct list_head *queue;
	u32 blk_len, len;

	if (transmit)
		musb_ep = &musb->endpoints[epnum].ep_in;
	else
		musb_ep = &musb->endpoints[epnum].ep_out;

	queue = &musb_ep->req_list;

	if (list_empty(queue))
		return;
	musb_req = container_of(queue->next, struct musb_request, list);
	request = &musb_req->request;

	if (!transmit) {
		blk_len = musb_readl(musb->mregs, MUSB_DMA_CHN_LEN(epnum + 15));
		blk_len = (blk_len & 0xffff0000) >> 16;
		request->actual = request->length - blk_len;
	} else
		request->actual = request->length;

	musb_ep->dma->status = MUSB_DMA_STATUS_FREE;
	musb_g_giveback(musb_ep, request, 0);
}

irqreturn_t sprd_dma_interrupt(struct musb *musb, u32 int_hsdma)
{
	void __iomem *mbase = musb->mregs;
	u8 bchannel = 0;
	u32 intr, int_dma;
	int i;

	int_dma = musb_readl(musb->mregs, MUSB_DMA_INTR_MASK_STATUS);
	for (i = 0; i < MUSB_DMA_CHANNELS; i++) {
		bchannel++;
		if ((int_hsdma & BIT_0) != BIT_0) {
			int_hsdma = int_hsdma >> 1;
			continue;
		}
		int_hsdma = int_hsdma >> 1;

		intr = musb_readl(mbase, MUSB_DMA_CHN_INTR(bchannel));
		dev_vdbg(musb->controller, "sprd_dma_interrupt is 0x%x, %d , %d\n",
				intr, bchannel, int_dma);

		if (intr & CHN_START_INT_MASK_STATUS) {
			dev_dbg(musb->controller, "DMA request is NULL\n");

			/* clear interrupt */
			intr |= CHN_START_INT_CLR;
			musb_writel(mbase, MUSB_DMA_CHN_INTR(bchannel), intr);
		}
		if (bchannel > 15) {
			if (intr & CHN_LLIST_INT_MASK_STATUS) {
				/* clear interrupt */
				intr |= CHN_LLIST_INT_CLR |
					CHN_USBRX_LAST_INT_CLR;
				musb_writel(mbase, MUSB_DMA_CHN_INTR(bchannel),
					intr);
				/* callback to give complete */
				sprd_musb_dma_completion(musb,
					(bchannel - 15), 0);
			}
		} else {
			if ((musb->int_tx | musb->int_listend) & (1 << bchannel)) {
				/* clear interrupt */
				intr |= CHN_LLIST_INT_CLR;
				musb_writel(mbase, MUSB_DMA_CHN_INTR(bchannel),
					intr);
				/* callback to give complete */
				sprd_musb_dma_completion(musb, bchannel, 1);
			}
		}
	}

	return IRQ_HANDLED;
}

void dma_controller_destroy(struct dma_controller *c)
{
	struct sprd_musb_dma_controller *controller = container_of(c,
			struct sprd_musb_dma_controller, controller);

	sprd_dma_controller_stop(controller);

	kfree(controller);
}
EXPORT_SYMBOL_GPL(dma_controller_destroy);

struct dma_controller *dma_controller_create(struct musb *musb,
						    void __iomem *base)
{
	struct sprd_musb_dma_controller *controller;

	controller = kzalloc(sizeof(*controller), GFP_KERNEL);
	if (!controller)
		return NULL;

	controller->private_data = musb;
	controller->base = base;

	controller->controller.channel_alloc = sprd_dma_channel_allocate;
	controller->controller.channel_release = sprd_dma_channel_release;
	controller->controller.channel_program = sprd_dma_channel_program;
	controller->controller.channel_abort = sprd_dma_channel_abort;

	return &controller->controller;
}
EXPORT_SYMBOL_GPL(dma_controller_create);
