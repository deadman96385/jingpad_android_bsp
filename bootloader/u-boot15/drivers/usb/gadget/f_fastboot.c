/*
 * ether.c -- Ethernet gadget driver, with CDC and non-CDC options
 *
 * Copyright (C) 2003-2005,2008 David Brownell
 * Copyright (C) 2003-2004 Robert Schwebel, Benedikt Spranger
 * Copyright (C) 2008 Nokia Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
//#define DEBUG

#include <common.h>
#include <asm/errno.h>
#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>
#include <linux/usb/composite.h>
#include <linux/usb/usb_uboot.h>
#include <linux/ctype.h>
#include "gadget_chips.h"

#define atomic_read


unsigned packet_received, packet_sent;
static volatile int txn_done;
int txn_status;

#define DEV_CONFIG_CDC	1
#define GFP_ATOMIC ((gfp_t) 0)
#define GFP_KERNEL ((gfp_t) 0)

#define DRIVER_DESC		"fastboot Gadget"
/* Based on linux 2.6.27 version */
#define DRIVER_VERSION		"May Day 2005"

static const char shortname[] = "fastboot";
static const char driver_desc[] = DRIVER_DESC;

#define RX_EXTRA	20	/* guard against rx overflows */

/* CDC support the same host-chosen outgoing packet filters. */
#define	DEFAULT_FILTER	(USB_CDC_PACKET_TYPE_BROADCAST \
			|USB_CDC_PACKET_TYPE_ALL_MULTICAST \
			|USB_CDC_PACKET_TYPE_PROMISCUOUS \
			|USB_CDC_PACKET_TYPE_DIRECTED)

#define USB_CONNECT_TIMEOUT (3 * CONFIG_SYS_HZ)

/*-------------------------------------------------------------------------*/
struct fastboot_dev {
	struct usb_gadget *gadget;
	struct usb_request *req;	/* for control responses */
	struct usb_request *stat_req;	/* for cdc status */

	u8 config;
	struct usb_ep *in_ep, *out_ep;
	const struct usb_endpoint_descriptor
	*in, *out;

	struct usb_request *tx_req, *rx_req;

	unsigned suspended:1;
	unsigned network_started:1;
};

static struct fastboot_dev l_fbdev;
static struct usb_gadget_driver fastboot_driver;

/*-------------------------------------------------------------------------*/

#define DEFAULT_QLEN	2	/* double buffering by default */

/* peak bulk transfer bits-per-second */
#define	HS_BPS		(13 * 512 * 8 * 1000 * 8)
#define	FS_BPS		(19 *  64 * 1 * 1000 * 8)

#ifdef CONFIG_USB_GADGET_DUALSPEED
#define	DEVSPEED	USB_SPEED_HIGH

/* for dual-speed hardware, use deeper queues at highspeed */
#define qlen(gadget) \
	(DEFAULT_QLEN*((gadget->speed == USB_SPEED_HIGH) ? qmult : 1))

static inline int BITRATE(struct usb_gadget *g)
{
	return (g->speed == USB_SPEED_HIGH) ? HS_BPS : FS_BPS;
}

#else /* full speed (low speed doesn't do bulk) */

#define qmult		1

#define	DEVSPEED	USB_SPEED_FULL

#define qlen(gadget) DEFAULT_QLEN

static inline int BITRATE(struct usb_gadget *g)
{
	return FS_BPS;
}
#endif

/*
 * Thanks to NetChip Technologies for donating this product ID.
 * It's for devices with only CDC Ethernet configurations.
 */
#define FASTBOOT_VENDOR_NUM		0x18D1	/* Goolge VID */
#define FASTBOOT_PRODUCT_NUM		0x4ee0	/* Fastboot Product ID */
//#define FASTBOOT_PRODUCT_NUM          0x0C02  /* Linux-USB Ethernet Gadget */

/*
 * Some systems will want different product identifers published in the
 * device descriptor, either numbers or strings or both.  These string
 * parameters are in UTF-8 (superset of ASCII's 7 bit characters).
 */

static ushort bcdDevice;

static char *iManufacturer = "Spreadtrum";

static char *iProduct;
static char *iSerialNumber = "20080823";
extern char *get_product_sn();


/*-------------------------------------------------------------------------*/

/*
 * USB DRIVER HOOKUP (to the hardware driver, below us), mostly
 * ep0 implementation:  descriptors, config management, setup().
 * also optional class-specific notification interrupt transfer.
 */

/*
 * DESCRIPTORS ... most are static, but strings and (full) configuration
 * descriptors are built on demand.  For now we do either full CDC, or
 * our simple subset.
 */

#define STRING_MANUFACTURER		1
#define STRING_PRODUCT			2
#define STRING_ETHADDR			3
#define STRING_DATA			4
#define STRING_CONTROL			5
#define STRING_CDC			7
#define STRING_SUBSET			8
#define STRING_SERIALNUMBER		10

/* holds our biggest descriptor */
#define USB_BUFSIZ	256
#define USB_MAX_TRANSFER_SIZE (32 * 1024)
/*
 * This device advertises one configuration, eth_config,
 * on hardware supporting at least two configs.
 *
 * FIXME define some higher-powered configurations to make it easier
 * to recharge batteries ...
 */

#define DEV_CONFIG_VALUE	1	/* cdc or subset */

static struct usb_device_descriptor device_desc = {
	.bLength = sizeof device_desc,
	.bDescriptorType = USB_DT_DEVICE,

	.bcdUSB = __constant_cpu_to_le16(0x0200),

	.bDeviceClass = 0,
	.bDeviceSubClass = 0,
	.bDeviceProtocol = 0,

	.idVendor = __constant_cpu_to_le16(FASTBOOT_VENDOR_NUM),
	.idProduct = __constant_cpu_to_le16(FASTBOOT_PRODUCT_NUM),
	.iManufacturer = STRING_MANUFACTURER,
	.iProduct = STRING_PRODUCT,
	.bNumConfigurations = 1,
};

static struct usb_config_descriptor fastboot_config = {
	.bLength = sizeof fastboot_config,
	.bDescriptorType = USB_DT_CONFIG,

	/* compute wTotalLength on the fly */
	.bNumInterfaces = 1,
	.bConfigurationValue = DEV_CONFIG_VALUE,
	.iConfiguration = STRING_CDC,
	.bmAttributes = USB_CONFIG_ATT_ONE,	// | USB_CONFIG_ATT_SELFPOWER,
	.bMaxPower = 0xfa,
};

/* ... but the "real" data interface has two bulk endpoints */

static const struct usb_interface_descriptor data_intf = {
	.bLength = sizeof data_intf,
	.bDescriptorType = USB_DT_INTERFACE,

	.bInterfaceNumber = 0,
	.bAlternateSetting = 0,
	.bNumEndpoints = 2,
	.bInterfaceClass = USB_CLASS_VENDOR_SPEC,
	.bInterfaceSubClass = 0x42,
	.bInterfaceProtocol = 3,
	.iInterface = STRING_DATA,
};

static struct usb_endpoint_descriptor fs_source_desc = {
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,

	.bEndpointAddress = USB_DIR_IN,
	.bmAttributes = USB_ENDPOINT_XFER_BULK,
};

static struct usb_endpoint_descriptor fs_sink_desc = {
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,

	.bEndpointAddress = USB_DIR_OUT,
	.bmAttributes = USB_ENDPOINT_XFER_BULK,
};

static const struct usb_descriptor_header *fs_fastboot_function[] = {
//      (struct usb_descriptor_header *) &otg_descriptor,
#ifdef DEV_CONFIG_CDC
	/* "cdc" mode descriptors */
//      (struct usb_descriptor_header *) &control_intf,
//      (struct usb_descriptor_header *) &header_desc,
//      (struct usb_descriptor_header *) &union_desc,
//      (struct usb_descriptor_header *) &ether_desc,
	/* NOTE: status endpoint may need to be removed */
//      (struct usb_descriptor_header *) &fs_status_desc,
	/* data interface, with altsetting */
	(struct usb_descriptor_header *)&data_intf,
	(struct usb_descriptor_header *)&fs_source_desc,
	(struct usb_descriptor_header *)&fs_sink_desc,
	NULL,
#endif /* DEV_CONFIG_CDC */
};

/*
 * usb 2.0 devices need to expose both high speed and full speed
 * descriptors, unless they only run at full speed.
 */

static struct usb_endpoint_descriptor hs_source_desc = {
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,

	.bmAttributes = USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize = __constant_cpu_to_le16(512),
};

static struct usb_endpoint_descriptor hs_sink_desc = {
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,

	.bmAttributes = USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize = __constant_cpu_to_le16(512),
};

static struct usb_qualifier_descriptor dev_qualifier = {
	.bLength = sizeof dev_qualifier,
	.bDescriptorType = USB_DT_DEVICE_QUALIFIER,

	.bcdUSB = __constant_cpu_to_le16(0x0200),
	.bDeviceClass = USB_CLASS_VENDOR_SPEC,

	.bNumConfigurations = 1,
};

static const struct usb_descriptor_header *hs_fastboot_function[] = {
//      (struct usb_descriptor_header *) &otg_descriptor,
#ifdef DEV_CONFIG_CDC
	/* "cdc" mode descriptors */
//      (struct usb_descriptor_header *) &control_intf,
//      (struct usb_descriptor_header *) &header_desc,
//      (struct usb_descriptor_header *) &union_desc,
//      (struct usb_descriptor_header *) &ether_desc,
	/* NOTE: status endpoint may need to be removed */
//      (struct usb_descriptor_header *) &hs_status_desc,
	/* data interface, with altsetting */
//      (struct usb_descriptor_header *) &data_nop_intf,
	(struct usb_descriptor_header *)&data_intf,
	(struct usb_descriptor_header *)&hs_source_desc,
	(struct usb_descriptor_header *)&hs_sink_desc,
	NULL,
#endif /* DEV_CONFIG_CDC */
};


/*-------------------------------------------------------------------------*/

/* descriptors that are built on-demand */

static char manufacturer[50];
static char product_desc[40] = DRIVER_DESC;
static char serial_number[128];

/* static strings, in UTF-8 */
static struct usb_string strings[] = {
	{STRING_MANUFACTURER, manufacturer,},
	{STRING_PRODUCT, product_desc,},
	{STRING_SERIALNUMBER, serial_number,},
	{STRING_DATA, "fastboot Data",},
#ifdef	DEV_CONFIG_CDC
	{STRING_CDC, "fastboot Ethernet",},
	{STRING_CONTROL, "fastboot Communications Control",},
#endif
	{}			/* end of list */
};

static struct usb_gadget_strings stringtab = {
	.language = 0x0409,	/* en-us */
	.strings = strings,
};

/*============================================================================*/
static u8 control_req[USB_BUFSIZ] __attribute__ ((aligned(4)));

/**
 * strlcpy - Copy a %NUL terminated string into a sized buffer
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 * @size: size of destination buffer
 *
 * Compatible with *BSD: the result is always a valid
 * NUL-terminated string that fits in the buffer (unless,
 * of course, the buffer size is zero). It does not pad
 * out the result like strncpy() does.
 */
/*
size_t strlcpy(char *dest, const char *src, size_t size)
{
	size_t ret = strlen(src);

	if (size) {
		size_t len = (ret >= size) ? size - 1 : ret;
		memcpy(dest, src, len);
		dest[len] = '\0';
	}
	return ret;
}*/

/*============================================================================*/

/*
 * one config, two interfaces:  control, data.
 * complications: class descriptors, and an altsetting.
 */
static int config_buf(struct usb_gadget *g, u8 * buf, u8 type, unsigned index, int is_otg)
{
	int len;
	const struct usb_config_descriptor *config;
	const struct usb_descriptor_header **function;
	int hs = 0;

	if (gadget_is_dualspeed(g)) {
		hs = (g->speed == USB_SPEED_HIGH);
		if (type == USB_DT_OTHER_SPEED_CONFIG)
			hs = !hs;
	}
#define which_fn(t)	(hs ? hs_ ## t ## _function : fs_ ## t ## _function)

	debug("%s , type :%d, index %d\n", __func__, type, index);
	if (index >= device_desc.bNumConfigurations)
		return -EINVAL;

	config = &fastboot_config;
	function = which_fn(fastboot);

	/* for now, don't advertise srp-only devices */
/*
	if (!is_otg)
		function++;
*/
	len = usb_gadget_config_buf(config, buf, USB_BUFSIZ, function);
	if (len < 0)
		return len;
	((struct usb_config_descriptor *)buf)->bDescriptorType = type;
	return len;
}

/*-------------------------------------------------------------------------*/

static int alloc_requests(struct fastboot_dev *dev, unsigned n, gfp_t gfp_flags);

static int set_fastboot_config(struct fastboot_dev *dev, gfp_t gfp_flags)
{
	int result = 0;
	struct usb_gadget *gadget = dev->gadget;

	dev->in = ep_choose(gadget, &hs_source_desc, &fs_source_desc);
	dev->in_ep->driver_data = dev;

	dev->out = ep_choose(gadget, &hs_sink_desc, &fs_sink_desc);
	dev->out_ep->driver_data = dev;

	result = usb_ep_enable(dev->in_ep, dev->in);
	if (result != 0) {
		debug("enable %s --> %d\n", dev->in_ep->name, result);
		goto done;
	}

	result = usb_ep_enable(dev->out_ep, dev->out);
	if (result != 0) {
		debug("enable %s --> %d\n", dev->out_ep->name, result);
		goto done;
	}

done:
	if (result == 0)
		result = alloc_requests(dev, 1, gfp_flags);

	/* on error, disable any endpoints  */
	if (result < 0) {
		(void)usb_ep_disable(dev->in_ep);
		(void)usb_ep_disable(dev->out_ep);
		dev->in = NULL;
		dev->out = NULL;
	}

	/* caller is responsible for cleanup on error */
	return result;
}

static void fastboot_reset_config(struct fastboot_dev *dev)
{
	if (dev->config == 0)
		return;

	debug("%s\n", __func__);

	/*
	 * disable endpoints, forcing (synchronous) completion of
	 * pending i/o.  then free the requests.
	 */

	if (dev->in) {
		usb_ep_disable(dev->in_ep);
		if (dev->tx_req) {
			usb_ep_free_request(dev->in_ep, dev->tx_req);
			dev->tx_req = NULL;
		}
	}
	if (dev->out) {
		usb_ep_disable(dev->out_ep);
		if (dev->rx_req) {
			usb_ep_free_request(dev->out_ep, dev->rx_req);
			dev->rx_req = NULL;
		}
	}
	dev->config = 0;
}

/*
 * change our operational config.  must agree with the code
 * that returns config descriptors, and altsetting code.
 */
static int fastboot_set_config(struct fastboot_dev *dev, unsigned number, gfp_t gfp_flags)
{
	int result = 0;
	struct usb_gadget *gadget = dev->gadget;

	fastboot_reset_config(dev);

	switch (number) {
	case DEV_CONFIG_VALUE:
		result = set_fastboot_config(dev, gfp_flags);
		break;
	default:
		result = -EINVAL;
		/* FALL THROUGH */
	case 0:
		break;
	}

	if (result) {
		if (number)
			fastboot_reset_config(dev);
		usb_gadget_vbus_draw(dev->gadget, gadget_is_otg(dev->gadget) ? 8 : 100);
	} else {
		char *speed;
		unsigned power;

		power = 2 * fastboot_config.bMaxPower;
		usb_gadget_vbus_draw(dev->gadget, power);

		switch (gadget->speed) {
		case USB_SPEED_FULL:
			speed = "full";
			break;
#ifdef CONFIG_USB_GADGET_DUALSPEED
		case USB_SPEED_HIGH:
			speed = "high";
			break;
#endif
		default:
			speed = "?";
			break;
		}

		dev->config = number;
		debug("%s speed config #%d: %d mA, %s\n", speed, number, power, driver_desc);
	}
	return result;
}

/*-------------------------------------------------------------------------*/

static void
fastboot_setup_complete(struct usb_ep *ep, struct usb_request *req)
{
	if (req->status || req->actual != req->length)
		debug("setup complete --> %d, %d/%d\n",
			req->status, req->actual, req->length);
}

/*
 * The setup() callback implements all the ep0 functionality that's not
 * handled lower down.  CDC has a number of less-common features:
 *
 *  - two interfaces:  control, and ethernet data
 *  - Ethernet data interface has two altsettings:  default, and active
 *  - class-specific descriptors for the control interface
 *  - class-specific control requests
 */
static int
fastboot_setup(struct usb_gadget *gadget, const struct usb_ctrlrequest *ctrl)
{
	struct fastboot_dev *dev = get_gadget_data(gadget);
	struct usb_request *req = dev->req;
	int value = -EOPNOTSUPP;
	u16 wIndex = le16_to_cpu(ctrl->wIndex);
	u16 wValue = le16_to_cpu(ctrl->wValue);
	u16 wLength = le16_to_cpu(ctrl->wLength);

	/*
	 * descriptors just go into the pre-allocated ep0 buffer,
	 * while config change events may enable network traffic.
	 */
	switch (ctrl->bRequest) {

	case USB_REQ_GET_DESCRIPTOR:
		if (ctrl->bRequestType != USB_DIR_IN)
			break;
		switch (wValue >> 8) {

		case USB_DT_DEVICE:
			device_desc.bMaxPacketSize0 = gadget->ep0->maxpacket;
			value = min(wLength, (u16) sizeof device_desc);
			memcpy(req->buf, &device_desc, value);
			break;
		case USB_DT_DEVICE_QUALIFIER:
			if (!gadget_is_dualspeed(gadget))
				break;
			/* assumes ep0 uses the same value for both speeds ... */
			dev_qualifier.bMaxPacketSize0 = device_desc.bMaxPacketSize0;
			value = min(wLength, (u16) sizeof dev_qualifier);
			memcpy(req->buf, &dev_qualifier, value);
			break;

		case USB_DT_OTHER_SPEED_CONFIG:
			if (!gadget_is_dualspeed(gadget))
				break;
			/* FALLTHROUGH */
		case USB_DT_CONFIG:
			value = config_buf(gadget, req->buf,
				wValue >> 8, wValue & 0xff, gadget_is_otg(gadget));
			if (value >= 0)
				value = min(wLength, (u16) value);
			break;

		case USB_DT_STRING:
			value = usb_gadget_get_string(&stringtab, wValue & 0xff, req->buf);

			if (value >= 0)
				value = min(wLength, (u16) value);

			break;
		}
		break;

	case USB_REQ_SET_CONFIGURATION:
		if (ctrl->bRequestType != 0)
			break;
		value = fastboot_set_config(dev, wValue, GFP_ATOMIC);
		l_fbdev.network_started = 1;
		break;
	case USB_REQ_GET_CONFIGURATION:
		if (ctrl->bRequestType != USB_DIR_IN)
			break;
		*(u8 *) req->buf = dev->config;
		value = min(wLength, (u16) 1);
		break;

	case USB_REQ_SET_INTERFACE:
		if (ctrl->bRequestType != USB_RECIP_INTERFACE
			|| !dev->config || wIndex > 1)
			break;
		/*
		 * FIXME this is wrong, as is the assumption that
		 * all non-PXA hardware talks real CDC ...
		 */
		debug("set_interface ignored!\n");

done_set_intf:
		break;
	case USB_REQ_GET_INTERFACE:
		if (ctrl->bRequestType != (USB_DIR_IN | USB_RECIP_INTERFACE)
		    || !dev->config || wIndex > 1)
			break;

		/* for CDC, iff carrier is on, data interface is active. */
		if (wIndex != 1)
			*(u8 *) req->buf = 0;
		else {
			/* *(u8 *)req->buf = netif_carrier_ok (dev->net) ? 1 : 0; */
			/* carrier always ok ... */
			*(u8 *) req->buf = 1;
		}
		value = min(wLength, (u16) 1);
		break;
	default:
		debug("unknown control req%02x.%02x v%04x i%04x l%d\n",
			ctrl->bRequestType, ctrl->bRequest, wValue, wIndex, wLength);
	}

	/* respond with data transfer before status phase? */
	if (value >= 0) {
		req->length = value;
		req->zero = value < wLength;
		value = usb_ep_queue(gadget->ep0, req, GFP_ATOMIC);
		if (value < 0) {
			debug("ep_queue --> %d\n", value);
			req->status = 0;
			fastboot_setup_complete(gadget->ep0, req);
		}
	}

	/* host either stalls (value < 0) or reports success */
	return value;
}

/*-------------------------------------------------------------------------*/
#if 0
static void rx_complete(struct usb_ep *ep, struct usb_request *req);

static int rx_submit(struct fastboot_dev *dev, struct usb_request *req, gfp_t gfp_flags)
{
	int retval = -ENOMEM;
	size_t size;

	/*
	 * Padding up to RX_EXTRA handles minor disagreements with host.
	 * Normally we use the USB "terminate on short read" convention;
	 * so allow up to (N*maxpacket), since that memory is normally
	 * already allocated.  Some hardware doesn't deal well with short
	 * reads (e.g. DMA must be N*maxpacket), so for now don't trim a
	 * byte off the end (to force hardware errors on overflow).
	 */

	debug("%s\n", __func__);

	size = (ETHER_HDR_SIZE + dev->mtu + RX_EXTRA);
	size += dev->out_ep->maxpacket - 1;
	size -= size % dev->out_ep->maxpacket;

	/*
	 * Some platforms perform better when IP packets are aligned,
	 * but on at least one, checksumming fails otherwise.
	 */

	req->buf = (u8 *) NetRxPackets[0];
	req->length = size;
	req->complete = rx_complete;

	retval = usb_ep_queue(dev->out_ep, req, gfp_flags);

	if (retval)
		error("rx submit --> %d", retval);

	return retval;
}

static void rx_complete(struct usb_ep *ep, struct usb_request *req)
{
	struct fastboot_dev *dev = ep->driver_data;

	debug("%s: status %d\n", __func__, req->status);

	packet_received = 1;
}

#endif
static int alloc_requests(struct fastboot_dev *dev, unsigned n, gfp_t gfp_flags)
{

#if 0
	dev->tx_req = usb_ep_alloc_request(dev->in_ep, 0);

	if (!dev->tx_req)
		goto fail1;

	dev->rx_req = usb_ep_alloc_request(dev->out_ep, 0);

	if (!dev->rx_req)
		goto fail2;

	return 0;

fail2:
	usb_ep_free_request(dev->in_ep, dev->tx_req);
fail1:
	error("can't alloc requests");
	return -1;
#endif
	return 0;
}

static void tx_complete(struct usb_ep *ep, struct usb_request *req)
{
	debug("%s: status %s\n", __func__, (req->status) ? "failed" : "ok");
	packet_sent = 1;
}

static void req_complete(struct usb_ep *ep, struct usb_request *req)
{
	if (req->status || req->actual != req->length)
		debug("req complete --> %d, %d/%d\n",
			req->status, req->actual, req->length);

	txn_status = req->status;
	txn_done = 1;
}

static void fastboot_unbind(struct usb_gadget *gadget)
{
	struct fastboot_dev *dev = get_gadget_data(gadget);

	debug("%s...\n", __func__);

	/* we've already been disconnected ... no i/o is active */
	if (dev->req) {
		usb_ep_free_request(gadget->ep0, dev->req);
		dev->req = NULL;
	}
#if 0
	if (dev->tx_req) {
		usb_ep_free_request(dev->in_ep, dev->tx_req);
		dev->tx_req = NULL;
	}

	if (dev->rx_req) {
		usb_ep_free_request(dev->out_ep, dev->rx_req);
		dev->rx_req = NULL;
	}
#endif
	set_gadget_data(gadget, NULL);
}

static void fastboot_disconnect(struct usb_gadget *gadget)
{
	fastboot_reset_config(get_gadget_data(gadget));
}

static void fastboot_suspend(struct usb_gadget *gadget)
{
	/* Not used */
}

static void fastboot_resume(struct usb_gadget *gadget)
{
	/* Not used */
}

/*-------------------------------------------------------------------------*/

static int fastboot_bind(struct usb_gadget *gadget)
{
	struct fastboot_dev *dev = &l_fbdev;
	u8 cdc = 1, zlp = 1;
	struct usb_ep *in_ep, *out_ep;
	int gcnum;
	u8 tmp[7];

	debugf("%s controller :%s recognized\n", __func__, gadget->name);
	gcnum = usb_gadget_controller_number(gadget);
	if (gcnum >= 0)
		device_desc.bcdDevice = cpu_to_le16(0x0300 + gcnum);
	else {
		/*
		 * can't assume CDC works.  don't want to default to
		 * anything less functional on CDC-capable hardware,
		 * so we fail in this case.
		 */
		error("controller '%s' not recognized", gadget->name);
		return -ENODEV;
	}

	if (bcdDevice)
		device_desc.bcdDevice = cpu_to_le16(bcdDevice);
	if (iManufacturer)
		strlcpy(manufacturer, iManufacturer, sizeof manufacturer);
	if (iProduct)
		strlcpy(product_desc, iProduct, sizeof product_desc);

	iSerialNumber = get_product_sn();
	device_desc.iSerialNumber = STRING_SERIALNUMBER,
	strlcpy(serial_number, iSerialNumber, sizeof serial_number);

	/* all we really need is bulk IN/OUT */
	usb_ep_autoconfig_reset(gadget);
	in_ep = usb_ep_autoconfig(gadget, &fs_source_desc);
	if (!in_ep) {
autoconf_fail:
		error("can't autoconfigure on %s\n", gadget->name);
		return -ENODEV;
	}
	in_ep->driver_data = in_ep;	/* claim */

	out_ep = usb_ep_autoconfig(gadget, &fs_sink_desc);
	if (!out_ep)
		goto autoconf_fail;
	out_ep->driver_data = out_ep;	/* claim */

	usb_gadget_set_selfpowered(gadget);

	if (gadget_is_dualspeed(gadget)) {

		/* and that all endpoints are dual-speed */
		hs_source_desc.bEndpointAddress = fs_source_desc.bEndpointAddress;
		hs_sink_desc.bEndpointAddress = fs_sink_desc.bEndpointAddress;
	}

	dev->network_started = 0;
	dev->in_ep = in_ep;
	dev->out_ep = out_ep;

	/* preallocate control message data and buffer */
	dev->req = usb_ep_alloc_request(gadget->ep0, GFP_KERNEL);
	if (!dev->req)
		goto fail;
	dev->req->buf = control_req;
	dev->req->complete = fastboot_setup_complete;
	dev->tx_req = usb_ep_alloc_request(dev->in_ep, GFP_KERNEL);
	dev->tx_req->complete = req_complete;
	dev->rx_req = usb_ep_alloc_request(dev->out_ep, GFP_KERNEL);
	dev->rx_req->complete = req_complete;

	/* ... and maybe likewise for status transfer */

	/* finish hookup to lower layer ... */
	dev->gadget = gadget;
	set_gadget_data(gadget, dev);
	gadget->ep0->driver_data = dev;

	debug("bind controller with the driver\n");
	/*
	 * two kinds of host-initiated state changes:
	 *  - iff DATA transfer is active, carrier is "on"
	 *  - tx queueing enabled if open *and* carrier is "on"
	 */
	return 0;

fail:
	error("%s failed", __func__);
	fastboot_unbind(gadget);
	return -ENOMEM;
}

static int usb_fastboot_start(void)
{
	struct fastboot_dev *dev = &l_fbdev;

	while (!dev->network_started)
		usb_gadget_handle_interrupts();

/*
	if (packet_received) {
		debug("%s: packet received\n", __func__);
		if (dev->rx_req) {
			NetReceive(NetRxPackets[0], dev->rx_req->length);
			packet_received = 0;

			rx_submit(dev, dev->rx_req, 0);
		} else
			error("dev->rx_req invalid");
	}
*/
	return 0;
}

static struct usb_gadget_driver fastboot_driver = {
	.speed = DEVSPEED,

	.bind = fastboot_bind,
	.unbind = fastboot_unbind,

	.setup = fastboot_setup,
	.disconnect = fastboot_disconnect,

	.suspend = fastboot_suspend,
	.resume = fastboot_resume,
};

#define mdelay(n)	udelay((n)*1000)

#define BASE_ADDR	0x00000000
#define DEFAULT_CMDLINE	"mem=128M console=null";

#define TAGS_ADDR	(BASE_ADDR + 0x00000100)
#define KERNEL_ADDR	(BASE_ADDR + 0x00800000)
#define RAMDISK_ADDR	(BASE_ADDR + 0x01000000)
//(BASE_ADDR + 0x02000000)


int fb_usb_read(void *_buf, unsigned len)
{
	int r;
	unsigned xfer;
	unsigned char *buf = _buf;
	int count = 0;
	struct usb_request *req = l_fbdev.rx_req;
	struct usb_ep *ep = l_fbdev.out_ep;

	debugf("usb_read(address = 0x%x,len=0x%x)\n", _buf, len);
	while (len > 0) {
		xfer = (len > USB_MAX_TRANSFER_SIZE) ?
			USB_MAX_TRANSFER_SIZE : ALIGN(len, ep->maxpacket);
		req->buf = buf;
		req->length = xfer;
		//r = udc_request_queue(out, req);
		r = usb_ep_queue(ep, req, GFP_ATOMIC);
		if (r < 0) {
			debugf("usb_read() queue failed\n");
			goto oops;
		}
		//event_wait(&txn_done);
		txn_done = 0;
		while (!txn_done)
			usb_gadget_handle_interrupts();

		if (txn_status < 0) {
			debugf("usb_read() transaction failed\n");
			goto oops;
		}
		if ((count % 0x100000) == 0)
			debugf("remained size = 0x%x\n", len);

		count += req->actual;
		buf += req->actual;
		len -= req->actual;

		/* short transfer? */
		if (req->actual != xfer)
			break;
	}

	return count;

oops:
	return -1;
}

int fb_usb_write(void *buf, unsigned len)
{
	int r;
	struct usb_request *req = l_fbdev.tx_req;
	struct usb_ep *ep = l_fbdev.in_ep;

	req->buf = buf;
	req->length = len;
	txn_done = 0;
	//r = udc_request_queue(in, req);
	r = usb_ep_queue(ep, req, GFP_ATOMIC);
	if (r < 0) {
		debugf("usb_write() queue failed\n");
		goto oops;
	}
	//event_wait(&txn_done);
	while (!txn_done)
		usb_gadget_handle_interrupts();
	if (txn_status < 0) {
		debugf("usb_write() transaction failed\n");
		goto oops;
	}
	return req->actual;

oops:
	return -1;
}


int usb_fastboot_init(void)
{
	int status = 0;

	usb_driver_init(USB_SPEED_HIGH);

	status = usb_gadget_register_driver(&fastboot_driver);
	if (status < 0)
		goto fail;
	debugf("usb gadget register driver ok!\n");
	usb_fastboot_start();
	debugf("usb fastboot start finish!\n");
	return 0;

fail:
	error("%s failed. error = %d", __func__, status);
	return status;
}
