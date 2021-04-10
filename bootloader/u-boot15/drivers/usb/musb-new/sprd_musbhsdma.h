/*
 * Copyright (C) 2016 Spreadtrum Communications Inc.
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

#define MUSB_DMA_PAUSE	0x1000
#define MUSB_DMA_FRAG_WAIT	0x1004
#define MUSB_DMA_INTR_RAW_STATUS	0x1008
#define MUSB_DMA_INTR_MASK_STATUS	0x100C
#define MUSB_DMA_REQ_STATUS	0x1010
#define MUSB_DMA_EN_STATUS	0x1014
#define MUSB_DMA_DEBUG_STATUS	0x1018

#define MUSB_DMA_CHN_PAUSE(n)		(0x1C00 + (n - 1) * 0x20)
#define MUSB_DMA_CHN_CFG(n)		(0x1C04 + (n - 1) * 0x20)
#define MUSB_DMA_CHN_INTR(n)		(0x1C08 + (n - 1) * 0x20)
#define MUSB_DMA_CHN_ADDR(n)		(0x1C0C + (n - 1) * 0x20)
#define MUSB_DMA_CHN_LEN(n)		(0x1C10 + (n - 1) * 0x20)
#define MUSB_DMA_CHN_LLIST_PTR(n)	(0x1C14 + (n - 1) * 0x20)
#define MUSB_DMA_CHN_BYTE_CNT(n)	(0x1C18 + (n - 1) * 0x20)
#define MUSB_DMA_CHN_REQ(n)		(0x1C1C + (n - 1) * 0x20)

#define musb_read_dma_addr(mbase, bchannel)	\
	musb_readl(mbase,	\
		   MUSB_DMA_CHN_ADDR(bchannel))

#define musb_write_dma_addr(mbase, bchannel, addr) \
	musb_writel(mbase, \
		    MUSB_DMA_CHN_ADDR(bchannel), \
		    addr)

#define BIT_0					0x01
#define BIT_1					0x02
#define BIT_2					0x04
#define BIT_3					0x08
#define BIT_4					0x10
#define BIT_5					0x20
#define BIT_6					0x40
#define BIT_7					0x80
#define BIT_8					0x0100
#define BIT_9					0x0200
#define BIT_10					0x0400
#define BIT_11					0x0800
#define BIT_12					0x1000
#define BIT_13					0x2000
#define BIT_14					0x4000
#define BIT_15					0x8000
#define BIT_16					0x010000
#define BIT_17					0x020000
#define BIT_18					0x040000
#define BIT_19					0x080000
#define BIT_20					0x100000
#define BIT_21					0x200000
#define BIT_22					0x400000
#define BIT_23					0x800000
#define BIT_24					0x01000000
#define BIT_25					0x02000000
#define BIT_26					0x04000000
#define BIT_27					0x08000000
#define BIT_28					0x10000000
#define BIT_29					0x20000000
#define BIT_30					0x40000000
#define BIT_31					0x80000000

#define CHN_EN	BIT_0
#define CHN_LLIST_INT_EN	BIT_2
#define CHN_START_INT_EN	BIT_3
#define CHN_USBRX_INT_EN	BIT_4

#define CHN_LLIST_INT_MASK_STATUS	BIT_18
#define CHN_START_INT_MASK_STATUS	BIT_19
#define CHN_USBRX_INT_MASK_STATUS	BIT_20

#define CHN_LLIST_INT_CLR	BIT_26
#define CHN_START_INT_CLR	BIT_27
#define CHN_USBRX_LAST_INT_CLR	BIT_28

#define MUSB_DMA_CHANNELS	30

struct sprd_musb_dma_controller;
#if 0
struct linklist_node_s {
	unsigned int	addr;
	unsigned short	frag_len;
	unsigned short	blk_len;
	u8	ioc;
	u8	sp;
	u8	list_end;
	u8	epn;
};
#endif
struct sprd_musb_dma_channel {
	struct dma_channel	channel;
	struct sprd_musb_dma_controller	*controller;
	u16	max_packet_sz;
	u8	idx;
	u8	transmit;
	unsigned int	addr;
	unsigned short	blk_len;
	unsigned short	frag_len;
	u8		ep_num;
	u8		ioc;
	u8		sp;
	u8		list_end;
};

struct sprd_musb_dma_controller {
	struct dma_controller	controller;
	struct sprd_musb_dma_channel	channel[MUSB_DMA_CHANNELS];
	void	*private_data;
	void __iomem	*base;
	u32	used_channels;
};

irqreturn_t sprd_dma_interrupt(struct musb *musb, u32 int_hsdma);
struct dma_controller *dma_controller_create(struct musb *musb,
							void __iomem *base);
void dma_controller_destroy(struct dma_controller *c);
