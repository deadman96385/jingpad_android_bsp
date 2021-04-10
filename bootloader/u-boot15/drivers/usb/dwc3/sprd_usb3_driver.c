/******************************************************************************

  Copyright (C), 2001-2015, Spreatrum Communications Inc.

 ******************************************************************************
  File Name     : sprd_usb3_driver.c
  Version       : 1.0 Beta
  Author        : Miao.Zhu
  Created       : 2014/12/25
  Last Modified :
  Description   : This file provides APIs to event handle, data transfer and etc.
  Function List : NA
  History       :
  1.Date        : 2014/12/25
    Author      : Miao.Zhu
    Modification: Created file
  2.Data        : 2015/03/12
    Author      : Miao.Zhu
    Modification: Add caching and buffering for transfer.
  3.Data        : 2015/10/01
    Author      : Miao.Zhu
    Modification: Add support for Auto Downloader function.
******************************************************************************/
#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
#include <packet.h>
#include <dl_crc.h>
#include "sprd_usb3_def.h"
#include <usb/sprd_usb_drv.h>

/* dwc3 rcv buf size n >= ((dl_size + 0x8)/mps + 1)*mps
 * or else dwc3 controller can't receive short packet.
 * */
#define MAX_RECV_LENGTH 0x10000

static int hdlc_disabled;
/** Driver context struct */
static usb3_device_t g_usb3_dev;

/** Endpoint context structs */
static usb3_pcd_ep_t g_ep0, g_epn_out, g_epn_in;

/** EP0 SETUP packet buffer */
static char g_ep0_setup_pkt[8];

/** DMA descriptor (TRB) for EP0 SETUP packets */
static usb3_dma_desc_t	g_ep0_setup_desc __attribute__((aligned (128)));

/** DMA descriptor (TRB) for EP0 Data/Status Out phases */
//static usb3_dma_desc_t	g_ep0_out_desc __attribute__((aligned (128)));

/** DMA descriptor (TRB) for EP0 Data/Status In phases */
static usb3_dma_desc_t	g_ep0_in_desc __attribute__((aligned (128)));

/** DMA descriptor (TRB) for EPn Out transfer */
static usb3_dma_desc_t	g_epn_out_desc __attribute__((aligned (128)));

/** DMA descriptor (TRB) for EPn In transfer */
static usb3_dma_desc_t	g_epn_in_desc[2] __attribute__((aligned (128)));

/** Receiver buffer for EP0 Data Out phases */
//static uint8_t g_ep0_out_buffer[8];

/** Receive buffer for EPn out transfer */
static uint8_t g_out_buffer[MAX_RECV_LENGTH] __attribute__((aligned (128)));

/** Received data len for EPn out transfer */
static int g_out_len;

/**Send data done flag for EPn in transfer*/
static int g_usb_send_done;

/** Send buffer for EPn in transfer */
//static char g_in_buffer[MAX_RECV_LENGTH];

extern void invalidate_dcache_range(phys_addr_t, phys_addr_t);
extern void flush_dcache_range(phys_addr_t, phys_addr_t);
extern uint32_t	dwc3_get_evt_lpos();

static void usb_receive(usb3_pcd_t *pcd);

PUBLIC __attribute__((aligned (64)))  unsigned char usb_out_endpoint_buf[1];
/**
 * Spin on register bit until handshake completes or times out.
 *
 * @param dev   Programming view of usb3 controller.
 * @param ptr   Address of register to read.
 * @param mask  Bit to look at in result of read.
 * @param done  Value of the bit when handshake succeeds.
 * @return      1 when the mask bit has the specified value (handshake done),
 *              0 when timeout has passed (handshake failed).
 */
static int inline _handshake(usb3_device_t *dev,
				volatile uint32_t __iomem *ptr,
				uint32_t mask, uint32_t done)
{
	uint32_t usec = 1000;
	uint32_t result;


	do {
		result = reg_rd32(ptr);
		if ((result & mask) == done) {
			return 1;
		}
		usec -= 1;
	} while (usec > 0);

	return 0;
}

static void inline usb3_flush_cache(phys_addr_t addr,
				uint32_t size, uint32_t dir)
{
	if (dir)
		flush_dcache_range(addr, addr + size);
	else
		invalidate_dcache_range(addr, addr + size);
}

/**
 * Send DEPCSTALL command to EP
 */
static int usb3_dep_cstall(usb3_pcd_t *pcd,
                           usb3_dev_ep_regs_t __iomem *ep_reg, int clr_pend)
{
	u32 depcmd;

	/* Fill clear stall command */
	depcmd = EPCMD_CLR_STALL | EPCMD_ACT_BIT;
	if (clr_pend)
		depcmd |= EPCMD_HP_FRM_BIT;

	/* Start the command */
	reg_wr32(&ep_reg->depcmd, depcmd);

	/* Wait for command completion */
	_handshake(pcd->usb3_dev, &ep_reg->depcmd, EPCMD_ACT_BIT, 0);

	return 0;
}

/**
 * Send DEPSTRTXFER command to EP
 */
static int usb3_dep_startxfer(usb3_pcd_t *pcd,
                              usb3_dev_ep_regs_t __iomem *ep_reg,
                              phys_addr_t dma_addr)
{
	uint32_t retval;

	/* Set param 1 */
	reg_wr32(&ep_reg->depcmdpar1, lower_32_bits(dma_addr));

	/* Set param 0 */
	reg_wr32(&ep_reg->depcmdpar0, upper_32_bits(dma_addr));

	/* Start the command */
	reg_wr32(&ep_reg->depcmd, EPCMD_START_XFER | EPCMD_ACT_BIT);

	/* Wait for command completion */
	_handshake(pcd->usb3_dev, &ep_reg->depcmd, EPCMD_ACT_BIT, 0);

	retval = reg_rd32(&ep_reg->depcmd);

	return retval >> EPCMD_XFER_RSRC_IDX_SHIFT &
	       EPCMD_XFER_RSRC_IDX_BITS >> EPCMD_XFER_RSRC_IDX_SHIFT;
}

/**
 * Send DEPUPDTXFER command to EP
 */
static int usb3_dep_updatexfer(usb3_pcd_t *pcd,
                               usb3_dev_ep_regs_t __iomem *ep_reg,
                               u32 tri)
{

	/* Start the command */
	reg_wr32(&ep_reg->depcmd,
	         tri << EPCMD_XFER_RSRC_IDX_SHIFT |
	         EPCMD_UPDATE_XFER | EPCMD_ACT_BIT);

	/* Wait for command completion */
	_handshake(pcd->usb3_dev, &ep_reg->depcmd, EPCMD_ACT_BIT, 0);

	return 0;
}

/**
 * Fill in the four dwords of a DMA descriptor (aka a TRB).
 */
static void usb3_fill_desc(usb3_dma_desc_t *desc, phys_addr_t dma_addr,
                           uint32_t dma_len, uint32_t type,
                           uint32_t ctrlbits, int own)
{
	desc->bptl = (uint32_t)lower_32_bits(dma_addr);
	desc->bpth = (uint32_t)upper_32_bits(dma_addr);
	desc->status = dma_len << DSCSTS_XFRCNT_SHIFT;
	desc->control = type << DSCCTL_TRBCTL_SHIFT | ctrlbits;

	/* Must do this last! */
	if (own) {
		desc->control |= DSCCTL_HWO_BIT;
	}
}


/**
 * This routine sets up a SETUP stage transfer for EP0 and starts the transfer.
 *
 * @param pcd   Programming view of the PCD.
 */
static void usb3_pcd_ep0_out_start(usb3_pcd_t *pcd)
{
	usb3_dma_desc_t *desc;
	uint8_t tri;

	/* Get the SETUP packet DMA Descriptor (TRB) */
	desc = usb3_ep0_setup_desc(pcd);

	/* DMA Descriptor setup */
	usb3_fill_desc(desc,(phys_addr_t)usb3_ep0_setup_pkt(pcd),
	               8, DSCCTL_TRBCTL_SETUP, DSCCTL_LST_BIT, 1);

	usb3_flush_cache((phys_addr_t)desc, sizeof(*desc), 1);

	/* Issue "DEPSTRTXFER" command to EP0-OUT */
	tri = usb3_dep_startxfer(pcd, pcd->ep0->ep.out_ep_reg, (phys_addr_t)desc);
	pcd->ep0->ep.tri_out = tri + 1;
}

/**
 * This routine handles all USB requests.
 */
static void do_setup(usb3_pcd_t *pcd)
{
	usb_device_request_t *ctrl = &pcd->ep0_setup_pkt->req;
	usb3_pcd_ep_t *ep0 = pcd->ep0;
	uint16_t wlength;

	wlength = UGETW(ctrl->wLength);

	ep0->ep.stopped = 0;
	ep0->ep.three_stage = 1;

	if (ctrl->bmRequestType & 0x80) {
		ep0->ep.is_in = 1;
		pcd->ep0state = EP0_IN_DATA_PHASE;
	} else {
		ep0->ep.is_in = 0;
		pcd->ep0state = EP0_OUT_DATA_PHASE;
	}

	if (wlength == 0) {
		ep0->ep.is_in = 1;
		pcd->ep0state = EP0_IN_WAIT_NRDY;
		ep0->ep.three_stage = 0;
	} else {
		/* We do not handle any three-stage setup requests */
		usb3_dep_cstall(pcd, &pcd->out_ep_regs[0], 0);
	}
}

/**
 * This routine starts the Zero-Length Packet for the IN status phase of a
 * control write transfer.
 */
static void setup_in_status_phase(usb3_pcd_t *pcd, void *buf)
{
	usb3_pcd_ep_t *ep0 = pcd->ep0;
	usb3_dma_desc_t *desc;
	uint32_t desc_type;
	uint8_t tri;

	ep0->ep.is_in = 1;
	pcd->ep0state = EP0_IN_STATUS_PHASE;

	desc = usb3_ep0_in_desc(pcd);
	desc_type = DSCCTL_TRBCTL_STATUS_2;

	/* DMA Descriptor setup */
	usb3_fill_desc(desc, (phys_addr_t)buf,
	               0, desc_type, DSCCTL_LST_BIT, 1);

	usb3_flush_cache((phys_addr_t)desc, sizeof(*desc), 1);

	/* Issue "DEPSTRTXFER" command to EP0-IN */
	tri = usb3_dep_startxfer(pcd, ep0->ep.in_ep_reg, (phys_addr_t)desc);
	ep0->ep.tri_in = tri + 1;
}

/**
 * This routine handles EP0 Control transfers.
 *
 * The state of the control tranfers are tracked in <code>ep0state</code>.
 */
static void usb3_handle_ep0(usb3_pcd_t *pcd, uint32_t event)
{
	usb3_pcd_ep_t *ep0 = pcd->ep0;

	switch (pcd->ep0state) {
	case EP0_IN_WAIT_NRDY:
		if (ep0->ep.is_in)
			setup_in_status_phase(pcd, usb3_ep0_setup_pkt(pcd));
		break;

	case EP0_IN_STATUS_PHASE:
	case EP0_OUT_STATUS_PHASE:
		pcd->ep0state = EP0_IDLE;
		ep0->ep.stopped = 1;
		ep0->ep.is_in = 0;	/* OUT for next SETUP */

		/* Prepare for more SETUP Packets */
		usb3_pcd_ep0_out_start(pcd);
		break;

	case EP0_IN_DATA_PHASE:
	case EP0_OUT_DATA_PHASE:
	case EP0_OUT_WAIT_NRDY:
	case EP0_STALL:
	case EP0_IDLE:
		break;
	}
	return;
}

/**
 * This routine handles EP0 transfers.
 *
 * This routine gets the request corresponding to the current EP0 transfer. If
 * EP0 is in IDLE state, it calls usb3_do_setup() to begin processing
 * the next Setup request, otherwise it calls usb3_handle_ep0() to handle
 * the next stage of the current transfer.
 */
static void usb3_handle_ep0_xfer(usb3_pcd_t *pcd, uint32_t event)
{
	if (pcd->ep0state == EP0_IDLE) {
		usb3_flush_cache((phys_addr_t)usb3_ep0_setup_pkt(pcd), 8, 0);
		do_setup(pcd);
	} else {
		usb3_handle_ep0(pcd, event);
	}
}

/**
 * This routine handles EPn interrupts except EP0.
 */
static void usb3_handle_epn_xfer(usb3_pcd_t *pcd,
                                 usb3_pcd_ep_t *ep, uint32_t event)
{
	if (ep == pcd->out_ep) {
		usb3_dma_desc_t *desc = ep->ep.dma_desc;

		usb3_flush_cache((phys_addr_t)desc, sizeof(*desc), 0);

		g_out_len = MAX_RECV_LENGTH -
		            (desc->status >> DSCSTS_XFRCNT_SHIFT
		             & DSCSTS_XFRCNT_BITS >> DSCSTS_XFRCNT_SHIFT);

		/* Sync transmit buffer */
		usb3_flush_cache((phys_addr_t)g_out_buffer, MAX_RECV_LENGTH, 1);

		if ((event & DEPEVT_INTTYPE_BITS) ==
		    DEPEVT_XFER_CMPL << DEPEVT_INTTYPE_SHIFT)
			ep->ep.tri_out = 0;
		ep->ep.xfer_started = 0;
	} else if(ep == pcd->in_ep) {
		g_usb_send_done = 1;
	}

}


/**
 * This interrupt indicates that an EP has a pending interrupt.
 */
static void usb3_handle_ep_intr(usb3_pcd_t *pcd,
                                int physep, uint32_t event)
{
	usb3_pcd_ep_t *ep;
	int epnum, is_in;

	/* Physical Out EPs are even, physical In EPs are odd */
	is_in = physep & 1;
	epnum = physep >> 1 & 0xf;

	/* Get EP pointer */
	if(epnum == 0) {
		if ((pcd->ep0state == EP0_IDLE) && is_in)
			return;
		ep = pcd->ep0;
	} else
		ep = is_in ? pcd->in_ep : pcd->out_ep;

	switch (event & DEPEVT_INTTYPE_BITS) {
	case DEPEVT_XFER_CMPL << DEPEVT_INTTYPE_SHIFT:

		ep->ep.xfer_started = 0;

	case DEPEVT_XFER_IN_PROG << DEPEVT_INTTYPE_SHIFT:
		/* Complete the transfer */
		if (epnum == 0)
			usb3_handle_ep0_xfer(pcd, event);
		else
			usb3_handle_epn_xfer(pcd, ep, event);
		break;

	case DEPEVT_XFER_NRDY << DEPEVT_INTTYPE_SHIFT:
		if (epnum == 0) {
			switch (pcd->ep0state) {
			case EP0_IN_WAIT_NRDY:
			case EP0_OUT_WAIT_NRDY:
				usb3_handle_ep0_xfer(pcd, event);
				break;
			default:
				break;
			}
		}
		/*
		else if (!is_in && !ep->ep.xfer_started)
		{
		    // Get ready to receive data from host
		    usb_receive(pcd);
		}
		*/
		break;

	case DEPEVT_FIFOXRUN << DEPEVT_INTTYPE_SHIFT:
	case DEPEVT_EPCMD_CMPL << DEPEVT_INTTYPE_SHIFT:
	default:
		break;
	}
}


/**
 * This routine fetches the next event from the Event Buffer.
 */
static uint32_t get_eventbuf_event(usb3_device_t *dev, int size)
{
	uint32_t event;

	event = *dev->event_ptr++;
	if (dev->event_ptr >= dev->event_buf + size)
		dev->event_ptr -= size;

	return event;
}

/**
 * This routine handles all interrupt events.
 */
static void usb3_handle_event(usb3_device_t *dev)
{
	usb3_pcd_t *pcd = &dev->pcd;
	uint32_t event;
	int count, physep, i;

	count = reg_rd32(&dev->core_global_regs->geventbuf[0].geventcnt);
	count &= EVENTCNT_CNT_BITS;

	if(!count)
		return;

	for (i = 0; i < count; i += 4) {
		event = get_eventbuf_event(dev, dev->event_size);
		reg_wr32(&dev->core_global_regs->geventbuf[0].geventcnt, 4);
		if (event == 0) {
			/* Ignore null events */
			continue;
		}

		if (event & EVENT_NON_EP_BIT) {
			/* do nothing */
			/* Note: There SHOULD NOT be device events in this stage */
		} else {
			physep = event >> DEPEVT_EPNUM_SHIFT &
			         DEPEVT_EPNUM_BITS >> DEPEVT_EPNUM_SHIFT;
			usb3_handle_ep_intr(pcd, physep, event);
		}
	}
}

/**
 * This routine ingnores any present events
 */
static void usb3_flush_events(usb3_device_t *dev)
{
	int count;

	count = reg_rd32(&dev->core_global_regs->geventbuf[0].geventcnt);
	count &= EVENTCNT_CNT_BITS;

	if (count) {
		dev->event_ptr += count >> 2;
		if (dev->event_ptr >= dev->event_buf + dev->event_size)
			dev->event_ptr -= dev->event_size;
		reg_wr32(&dev->core_global_regs->geventbuf[0].geventcnt, count);
	}
}

/**
 * This routine initializes an Event Buffer.
 */
static void usb3_init_eventbuf(usb3_device_t *dev, uint32_t autodl_mode)
{
	uint32_t offset;
	phys_addr_t event_addr;

	event_addr =
	        (phys_addr_t)reg_rd32(
	                &dev->core_global_regs->geventbuf[0].geventadr_lo);
	event_addr |=
	        ((phys_addr_t)reg_rd32(
	                 &dev->core_global_regs->geventbuf[0].geventadr_hi))
	        << 32U;

	dev->event_buf = (uint32_t *)event_addr;
	/* Event_size in DWORD */
	dev->event_size =
	        reg_rd32(&dev->core_global_regs->geventbuf[0].geventsiz) >> 2;

	/* Get current event ptr from last stage
	 * If it's normal downloading, the last stage is FDL1;
	 * If it's (so-called) automatic downloading, the last stage is uboot.
	 */
	if (autodl_mode) {
		offset = dwc3_get_evt_lpos();
		dev->event_ptr = dev->event_buf + (offset >> 2);
	} else {
		event_addr = *(phys_addr_t *)(dev->event_buf + dev->event_size);
		dev->event_ptr = (uint32_t *)event_addr;
	}
}

/**
 * Initialize the PCD EP structures to their default state.
 *
 * @param pcd   The PCD structure.
 *
 ** Note: All required physical endpoints are configurated in the ROM code stage,
  * what needs to be done is initialize programming views of EPs.
 */
static void pcd_epinit(usb3_pcd_t *pcd)
{
	usb3_pcd_ep_t *ep;
	uint32_t maxpacket;

	/** Initialize the EP0 structure */
	ep = pcd->ep0 = &g_ep0;
	ep->ep.pcd = pcd;
	ep->ep.stopped = 1;
	ep->ep.out_ep_reg = &pcd->out_ep_regs[0];
	ep->ep.in_ep_reg = &pcd->in_ep_regs[0];
	ep->ep.stopped = 1;
	ep->ep.is_in = 0;

	switch(pcd->speed) {
	case USB_SPEED_SUPER:
		pcd->ep0->ep.maxpacket = 512;
		maxpacket = 1024;
		break;
	case USB_SPEED_HIGH:
		pcd->ep0->ep.maxpacket = 64;
		maxpacket = 512;
		break;
	case USB_SPEED_FULL:
		pcd->ep0->ep.maxpacket = 64;
		maxpacket = 64;
		break;
	}

	/**Initialize the EP1-n structures */
	ep = pcd->out_ep = &g_epn_out;
	ep->ep.dma_desc = &g_epn_out_desc;
	ep->ep.pcd = pcd;
	ep->ep.stopped = 1;
	ep->ep.out_ep_reg = &pcd->out_ep_regs[1];
	ep->ep.maxpacket = maxpacket;
	ep->ep.xfer_started = 0;

	ep = pcd->in_ep = &g_epn_in;
	ep->ep.dma_desc = g_epn_in_desc;
	ep->ep.pcd = pcd;
	ep->ep.stopped = 1;
	ep->ep.in_ep_reg = &pcd->in_ep_regs[1];
	ep->ep.maxpacket = maxpacket;
	ep->ep.xfer_started = 0;

	/** Initialize EP0 state */
	pcd->ep0state = EP0_IDLE;
}

/**
 * Initialize the PCD portion of the driver.
 *
 * @param dev   Programming view of usb3 controller.
 */
static void usb3_pcd_init(usb3_device_t *dev, uint32_t autodl_mode)
{
	uint32_t dsts;
	uint8_t speed;

	dev->pcd.usb3_dev = dev;
	dsts = reg_rd32(&dev->pcd.dev_global_regs->dsts);
	switch(dsts >> DSTS_CONNSPD_SHIFT &
		DSTS_CONNSPD_BITS >> DSTS_CONNSPD_SHIFT) {
	case SPEED_HS_PHY_30MHZ_OR_60MHZ:
		speed = USB_SPEED_HIGH;
		break;
	case SPEED_FS_PHY_30MHZ_OR_60MHZ:
		speed = USB_SPEED_FULL;
		break;
	case SPEED_SS_PHY_125MHZ_OR_250MHZ:
		speed = USB_SPEED_SUPER;
		break;
	}
	dev->pcd.speed = speed;

	usb3_init_eventbuf(dev, autodl_mode);
}

/**
 * The routine handles USB3 events (if any)
 */
static void usb3_handler(void)
{
	usb3_device_t* dev = &g_usb3_dev;

	do {
		usb3_handle_event(dev);

		if (g_out_len > 0)
			break;
	} while (1);
}

/**
 * The routine configures EP Out to receive any OUT transfer
 */
static void usb_receive(usb3_pcd_t *pcd)
{
	usb3_pcd_ep_t *ep = pcd->out_ep;
	uint8_t tri;

	if (ep->ep.xfer_started)
		return;

	/* Fill in Bulk Out TRB */
	usb3_fill_desc(ep->ep.dma_desc, (phys_addr_t)g_out_buffer,
	               sizeof g_out_buffer, DSCCTL_TRBCTL_NORMAL,
	               DSCCTL_LST_BIT, 1);

	usb3_flush_cache((phys_addr_t)ep->ep.dma_desc,
		sizeof(usb3_dma_desc_t), 1);

	/* Issue "DEPSTRTXFER" command to EP */
	tri = usb3_dep_startxfer(pcd, ep->ep.out_ep_reg,
	                         (phys_addr_t)ep->ep.dma_desc);

	ep->ep.tri_out = tri + 1;
	ep->ep.xfer_started = 1;
}


/**
 * wait for usb3 data to send
 */
static void wait_usb3_send_done(void)
{
	usb3_device_t* dev = &g_usb3_dev;

	g_usb_send_done = 0;

	do {
		usb3_handle_event(dev);

		if (g_usb_send_done > 0)
			break;
	} while (1);
}

/**
 * The routine sends a handshake to download tool
 * and prepares to receive data.
 */
void usb_send(unsigned char *buf, unsigned int len)
{
	usb3_pcd_t *pcd = &g_usb3_dev.pcd;
	usb3_pcd_ep_t *ep = pcd->in_ep;
	uint8_t zlp = 0, tri;
	phys_addr_t addr = (phys_addr_t)buf;

	/* Sync transmit buffer */
	usb3_flush_cache(addr, len, 1);

	/* Check Whether Zero-Length Packet is required */
	zlp = (len && !(len % ep->ep.maxpacket)) ? 1 : 0;

	/* Fill in Bulk In TRB */
	usb3_fill_desc(ep->ep.dma_desc, addr,
		len, DSCCTL_TRBCTL_NORMAL,
		zlp ? 0 : DSCCTL_LST_BIT, 1);

	if (zlp)
		usb3_fill_desc(ep->ep.dma_desc + 1, 0,
			0, DSCCTL_TRBCTL_NORMAL,
			DSCCTL_LST_BIT, 1);

	usb3_flush_cache((phys_addr_t)ep->ep.dma_desc,
		sizeof(usb3_dma_desc_t) * (1 + zlp), 1);

	/* Issue "DEPSTRTXFER" command to EP */
	tri = usb3_dep_startxfer(pcd, ep->ep.in_ep_reg,
	                         (phys_addr_t)ep->ep.dma_desc);

	ep->ep.tri_in = tri + 1;
	ep->ep.xfer_started = 1;

	/* Prepare to get next OUT transfer */
	usb_receive(pcd);
	wait_usb3_send_done();
}

/**
 * The routine get Entry of download mode.
 * Based on the download protocol, Download tool addresses
 * UE should enter the download mode by sending a 0x7E (called as Entry)
 */
uint8_t usb_get_entry()
{
	usb3_handler();

	if(g_out_len == 1) {
		g_out_len = 0;
		return g_out_buffer[0];
	}
	return 0;
}

/**
 * The routine escapes a command or image packet
 */
int usb_get_packet(uint8_t* buf, unsigned int len)
{
	usb3_pcd_t *pcd = &g_usb3_dev.pcd;
	uint8_t *src, *dest = buf;
	uint32_t escape_flag = 0;
	uint32_t pkt_flag = PKT_NONE;

	while(1) {
loop:
		usb3_handler();
		if (g_out_len) {
			if (hdlc_disabled) {
				int count = g_out_len;
				memcpy(dest,g_out_buffer+1,count-2);
				g_out_len = 0;;
				return count-2;
			}
			for (src = g_out_buffer; g_out_len--; src++) {
				switch(pkt_flag) {
				case PKT_NONE:
					if (*src == HDLC_FLAG)
						pkt_flag = PKT_HEAD;
					break;
				case PKT_GATHER:
					if (*src == HDLC_FLAG) {
						pkt_flag = PKT_RECV;
						goto end;
					}
				case PKT_HEAD:
					if (*src != HDLC_FLAG) {
						if (*src == HDLC_ESCAPE)
							escape_flag = 1;
						else if (escape_flag) {
							*dest++ = *src ^ HDLC_ESCAPE_MASK;
							escape_flag = 0;
						} else
							*dest++ = *src;
						pkt_flag = PKT_GATHER;
					}
					break;
				}
			}
			/* It's not a complete command or image packet, receive the remains */
			g_out_len = 0;
			usb_receive(pcd);
			goto loop;
		}
	}
end:
	/* The command or image packet is complete. */
	g_out_len = 0;
	return dest - buf;
}
int usb_rx_multi_nodes_config(unsigned char* buf, unsigned int len)
{
	return 0;
}

int usb_rx_data_from_linklist(unsigned int len)
{
	return 0;
}

void usb_disableHDLC( int disabled)
{
	hdlc_disabled = disabled;
}

int usb_support_raw_data_proc(void)
{
	return 0;
}

/**
 * The routine initialize USB3 driver
 * Note: Since USB is initialized and enumerated in ROM code,
  * only Programming view of usb3 controller is necessary to be done
  * in this stage (FDL2), and some properties would be got from USB registers.
 */
void usb_core_init(unsigned long reg_base_addr, uint32_t autodl_mode)
{
	usb3_device_t *usb3_dev = &g_usb3_dev;
	usb3_pcd_t *pcd;

	if (usb3_dev->inited)
		return;

	usb3_dev->base = (volatile uint8_t __iomem *)(long)reg_base_addr;

	pcd = &usb3_dev->pcd;

	/* "Allocate" the data structures that must be in DMA memory */
	pcd->ep0_setup_desc = &g_ep0_setup_desc;
	//pcd->ep0_out_desc = &g_ep0_out_desc;
	pcd->ep0_in_desc = &g_ep0_in_desc;
	pcd->ep0_setup_pkt = (union setup_pkt *)g_ep0_setup_pkt;

	/* Initialize the usb3 core */
	usb3_dev->core_global_regs = (usb3_core_global_regs_t __iomem *)
	                             (reg_base_addr + CORE_GLOBAL_REG_OFFSET);
	pcd->dev_global_regs = (usb3_dev_global_regs_t __iomem *)
	                       (reg_base_addr + DEV_GLOBAL_REG_OFFSET);
	pcd->in_ep_regs = (usb3_dev_ep_regs_t __iomem *)
	                  (reg_base_addr + DEV_IN_EP_REG_OFFSET);
	pcd->out_ep_regs = (usb3_dev_ep_regs_t __iomem *)
	                   (reg_base_addr + DEV_OUT_EP_REG_OFFSET);

	/* Initialize the PCD */
	usb3_pcd_init(usb3_dev, autodl_mode);

	/* Initialize the Endpoints */
	pcd_epinit(pcd);

	/* Flush any pending events occurred in last stage */
	//usb3_flush_events(usb3_dev);

	/* Prepare to get any pending SETUP packet */
	usb3_pcd_ep0_out_start(pcd);

	pcd->state = PCD_STATE_CONFIGURED;
	usb3_dev->inited = 1;
	g_out_len = 0;

	/* Prepare to get next OUT transfer */
	if (autodl_mode)
		usb_receive(pcd);
}

/* Note:
 */
void usb_init(unsigned int autodl_mode)
{
	hdlc_disabled = 0;
	usb_core_init(SPRD_USB_BASE, autodl_mode);
}

