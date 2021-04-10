/******************************************************************************
 ** File Name:      sprd_musb2_driver.c                                        *
 ** Author:         chunhou.wang                                              *
 ** DATE:           07/11/2016                                                *
 ** Copyright:      2010 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:                                                              *
 ******************************************************************************/
/**---------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **---------------------------------------------------------------------------*/

#include <common.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include <sprd_regulator.h>
#include <usb/usb200_fdl.h>
#include <packet.h>
#include <dl_crc.h>
#include "sprd_musb2_def.h"
#include <linux/usb/ch9.h>
#include <asm/arch/common.h>
#include <linux/usb/musb.h>
#include "musb_core.h"

extern void usb_phy_init(void);
static __inline void usb_handler (void);
void invalidate_dcache_range(unsigned long start, unsigned long stop);
void flush_dcache_range(unsigned long start, unsigned long stop);

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#define MAX_RECV_LENGTH         0xffc0//(64k-64)
#define USB_TIMEOUT             (1000)
#define REG32(x)     (*((volatile uint32_t *)(x)))

/**---------------------------------------------------------------------------*
 **                         Data Structures                                   *
 **---------------------------------------------------------------------------*/
static int hdlc_disabled;
static int currentDmaBufferIndex;
static uint32_t    enum_speed;
static uint32_t    recv_length;
static uint32_t nIndex, readIndex;
static uint32_t g_recv_packet_len = MAX_RECV_LENGTH;
PUBLIC __attribute__((aligned (64)))  unsigned char usb_out_endpoint_buf[RECV_PKT_SIZE + MAX_RECV_LENGTH];
static unsigned char * const usb_out_endpoint_cmd = usb_out_endpoint_buf + RECV_PKT_SIZE;
volatile unsigned char    s_setup_packet[8] __attribute__((aligned (64)));
struct linklist_node_s dma_linklist_tx[64] __attribute__((aligned (64)));
struct linklist_node_s dma_linklist_rx[64] __attribute__((aligned (64)));
unsigned char *out_endpoint = NULL;
__attribute__((aligned (64))) unsigned char linklist_ram_tx[sizeof(dma_linklist_tx)];
__attribute__((aligned (64))) unsigned char linklist_ram_rx[sizeof(dma_linklist_rx)];
__attribute__((aligned (4))) unsigned char DeviceStatus[] =
{
	0x00,0x00
};
static __attribute__((aligned (4))) uint8_t dev_desc[] =
{
	0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x40,
	0x82, 0x17, 0x00, 0x4d, 0xff, 0xff, 0x00, 0x00,
	0x00, 0x01
};
static __attribute__((aligned (4))) uint8_t config_desc[] =
{
	0x09, 0x02, 0x20, 0x00, 0x01, 0x01, 0x00, 0xc0,0x32,
	0x09, 0x04, 0x00, 0x00, 0x02, 0xff, 0x00, 0x00, 0x00,
	0x07, 0x05, 0x85, 0x02, 0x00, 0x02, 0x00,
	0x07, 0x05, 0x06, 0x02, 0x00, 0x02, 0x00
};

/*****************************************************************************/
//  Description:   configure out and in endpoint to receive/send setup message.
//  Global resource dependence:
//  Author:       chunhou.wang
//  Note:
/*****************************************************************************/
void configure_ep(void)
{
	(*(volatile unsigned char*)Mentor_USB_INDEX) = USB_EP5;
	(*(volatile unsigned short*)Mentor_USB_INTRTXE)=0x21;
	(*(volatile unsigned short*)Mentor_USB_INTRRXE)=0x40;
	(*(volatile unsigned char*)Mentor_USB_TX_FIFOS)=0x17;
	(*(volatile unsigned short*)Mentor_USB_TX_FIFOA)=0x108;

	if(enum_speed)
	{
	(*(volatile unsigned short*)Mentor_USB_TXMAXP(USB_EP5)) =0x40;
	}else{
	(*(volatile unsigned short*)Mentor_USB_TXMAXP(USB_EP5)) =0x200;
	}
	(*(volatile unsigned char*)Mentor_USB_TXCSRL(USB_EP5)) =0x48;
	(*(volatile unsigned char*)Mentor_USB_TXCSRH(USB_EP5)) =0x20;
	(*(volatile unsigned char*)Mentor_USB_TXCSRH(USB_EP5))|=(BIT_2|BIT_4|BIT_7);

	(*(volatile unsigned char*)Mentor_USB_INDEX) = USB_EP6;

	(*(volatile unsigned char*)Mentor_USB_RX_FIFOS)=0x17;
	(*(volatile unsigned short*)Mentor_USB_RX_FIFOA)=0x08;

	if(enum_speed)
	{
	(*(volatile unsigned short*)Mentor_USB_RXMAXP(USB_EP6)) =0x40;
	}else{
	(*(volatile unsigned short*)Mentor_USB_RXMAXP(USB_EP6)) =0x200;
	}
	(*(volatile unsigned char*)Mentor_USB_RXCSRL(USB_EP6)) =0x90;
	(*(volatile unsigned char*)Mentor_USB_RXCSRH(USB_EP6))|=(BIT_3|BIT_5|BIT_7);
}
/*****************************************************************************/
//  Description:   configure dma linklist node.
//  Global resource dependence:
//  Author:        chunhou.wang
//  Note:
/*****************************************************************************/
void prepare_linklist_node (uint32_t dir,int ep, unsigned int transfer_size, unsigned int *buffer, unsigned char list_end, unsigned int index)
{
	int rx_ch;
	unsigned long cache_start = 0;
	unsigned long cache_end = 0;
	unsigned int cache_len;
	u32 len;

	if (index > 63) {
		printf("linklist size overflow\r\n");
		return;
	}
	if (dir) {
		dma_linklist_rx[index].addr = (unsigned int)buffer;
		dma_linklist_rx[index].blk_len = transfer_size;
		dma_linklist_rx[index].frag_len = 32;
		dma_linklist_rx[index].ioc = list_end;
		dma_linklist_rx[index].sp = 0;
		dma_linklist_rx[index].list_end = list_end;

		if (list_end) {
			memcpy(linklist_ram_rx, (unsigned char *)dma_linklist_rx,
					(index + 1)*sizeof(dma_linklist_rx[0]));
			if (!index)
				len = 64;
			else
				len = sizeof(dma_linklist_rx);

			cache_start = (unsigned long)(&dma_linklist_rx);
			cache_end = cache_start + (unsigned long)len;
			invalidate_dcache_range(cache_start, cache_end);

			cache_start = (unsigned long)(&linklist_ram_rx);
			cache_end = cache_start + (unsigned long)len;
			invalidate_dcache_range(cache_start, cache_end);

			//out ep for receive data
			rx_ch = ep + 15;
			//enable linklist end rx last interrupt
			REG32(MUSB_DMA_CHN_INTR(rx_ch)) |= 0x14;
			//set linklist pointer
			REG32(MUSB_DMA_CHN_LLIST_PTR(rx_ch)) = (uint32_t)linklist_ram_rx;
			//enable channel and trigger rx dma transfer
			REG32(MUSB_DMA_CHN_CFG(rx_ch)) |= 0x1;
		}
	} else {
		cache_start = (u64)buffer;
		if (transfer_size % 64)
			len = transfer_size - (transfer_size % 64) + 64;
		else
			len = transfer_size;
		cache_end = cache_start + len;
		flush_dcache_range(cache_start, cache_end);

		if (transfer_size%512 != 0) {
			dma_linklist_tx[index].addr = buffer;
			dma_linklist_tx[index].blk_len = transfer_size;
			dma_linklist_tx[index].frag_len = 32;
			dma_linklist_tx[index].ioc = list_end;
			dma_linklist_tx[index].sp = 0;
			dma_linklist_tx[index].list_end = list_end;
		} else {
			if ((index + 1) > 63) {
				printf("tx linklist size overflow\r\n");
				return;
			}
			dma_linklist_tx[index].addr = buffer;
			dma_linklist_tx[index].blk_len = transfer_size;
			dma_linklist_tx[index].frag_len = 32;
			dma_linklist_tx[index].ioc = --list_end;
			dma_linklist_tx[index].sp = 0;
			dma_linklist_tx[index].list_end = list_end;
			/* EOF: short packet */
			index++;
			dma_linklist_tx[index].addr = buffer;
			dma_linklist_tx[index].blk_len = 0x0;
			dma_linklist_tx[index].frag_len = 32;
			dma_linklist_tx[index].ioc = ++list_end;
			dma_linklist_tx[index].sp = 1;
			dma_linklist_tx[index].list_end = list_end;
		}
		memcpy(&linklist_ram_tx, (unsigned char *)&dma_linklist_tx,
				(index + 1)*sizeof(dma_linklist_tx[0]));

		len = (index + 1)*64;
		cache_start = (unsigned long)(&dma_linklist_tx);
		cache_end = cache_start + (unsigned long)len;
		flush_dcache_range(cache_start, cache_end);

		cache_start = (unsigned long)(&linklist_ram_tx);
		cache_end = cache_start + (unsigned long)len;
		flush_dcache_range(cache_start, cache_end);
	}
}

void prepare_linklist_multi_nodes(uint32_t dir,int ep, unsigned int transfer_size, unsigned char *buf)
{

	unsigned int buf_length;
	unsigned int offset;
	unsigned int packet_len = (unsigned int)MAX_RECV_LENGTH;
	unsigned int link_list_index;

	for (buf_length = transfer_size, offset = 0, link_list_index = 0; buf_length > packet_len;
		buf_length -= packet_len, offset += packet_len, link_list_index++) {
		prepare_linklist_node (dir, ep, packet_len, (unsigned int *)(buf + offset), 0x0, link_list_index);
	}
	prepare_linklist_node (dir, ep, packet_len, (unsigned int *)(buf + offset), 0x01, link_list_index);
}

/*****************************************************************************/
//  Description:   process desecriptor request.
//  Global resource dependence:
//  Author:        chunhou.wang
//  Note:
/*****************************************************************************/
LOCAL void usb_get_descriptor (USB_REQUEST_1_U *request1, USB_REQUEST_2_U *request2)
{
	uint32_t len, length = 0;
	uint8_t   *send_data = NULL;
	uint32_t i;

	(*(volatile unsigned char*)Mentor_USB_CSR0L) |= BIT_6;

	length = (uint32_t) request2->mBits.length_l;

	switch (request1->mBits.value_m)
	{
	case USB_DEVICE_DESCRIPTOR_TYPE:
		send_data = dev_desc;
		len = length < sizeof(dev_desc) ?
			length : sizeof(dev_desc);
		for(i=0;i<len;i++)
			*(volatile unsigned char*)Mentor_USB_EP0_FIFO = send_data[i];
		(*(volatile unsigned char*)Mentor_USB_CSR0L) |= (BIT_1 | BIT_3);
		break;

	case USB_CONFIGURATION_DESCRIPTOR_TYPE:
		if (enum_speed)
		{
			config_desc[22] = config_desc[29] = 0x40;
			config_desc[23] = config_desc[30] = 0x00;
		}
		send_data = config_desc;
		len = length < sizeof(config_desc) ?
			length : sizeof(config_desc);
		for(i=0;i<len;i++)
			*(volatile unsigned char*)Mentor_USB_EP0_FIFO = send_data[i];
		(*(volatile unsigned char*)Mentor_USB_CSR0L) |= (BIT_1 | BIT_3);
		break;

	default:

		break;
	}
}
/*****************************************************************************/
//  Description:   process setup transaction.
//  Global resource dependence:
//  Author:        chunhou.wang
//  Note:
/*****************************************************************************/
LOCAL void usb_setup_handle (void)
{
	volatile unsigned short reg;
	volatile unsigned char reg1;
	volatile unsigned int i;
	USB_REQUEST_1_U   *request1;
	USB_REQUEST_2_U   *request2;
	uint32_t length =0;
	unsigned long cache_start = 0;
	unsigned long cache_end = 0;

	reg1 = *(volatile unsigned char*)Mentor_USB_CSR0L ;
	if((reg1 & BIT_0 ) == BIT_0)
	{
		cache_start = (unsigned long)s_setup_packet;
		cache_end = cache_start + 64;
		invalidate_dcache_range(cache_start, cache_end);
		for(i=0;i<8;i++)
			s_setup_packet[i] = *(volatile unsigned char*)Mentor_USB_EP0_FIFO;

	request1 = (USB_REQUEST_1_U *) s_setup_packet;
	request2 = (USB_REQUEST_2_U *) (s_setup_packet+4);

	switch (request1->mBits.type)
	{

	case USB_REQ_STANDARD://standard

		switch (request1->mBits.brequest)
		{
			case USB_REQUEST_SET_ADDRESS:
			{
				(*(volatile unsigned char*)Mentor_USB_CSR0L) |= (BIT_3 | BIT_6);
				reg= *(volatile unsigned short *)Mentor_USB_INTRTX;
				while((reg & BIT_0) != BIT_0)
					reg= *(volatile unsigned short *)Mentor_USB_INTRTX;

				(*(volatile unsigned char*)Mentor_USB_FADDR) = request1->mBits.value_l;
			}
			break;

			case USB_REQUEST_GET_DESCRIPTOR:
				usb_get_descriptor (request1, request2);
			break;

			case USB_REQUEST_SET_CONFIGURATION:
				(*(volatile unsigned char*)Mentor_USB_CSR0L) |= (BIT_3 | BIT_6);
				reg= *(volatile unsigned short *)Mentor_USB_INTRTX;
				while((reg & BIT_0) != BIT_0)
					reg= *(volatile unsigned short *)Mentor_USB_INTRTX;
			break;

			case USB_REQUEST_GET_STATUS:
				(*(volatile unsigned char*)Mentor_USB_CSR0L) |= BIT_6;
				length = (uint32_t)(request2->mBits.length_l | (request2->mBits.length_m<<8));
				for(i=0;i<length;i++)
					*(volatile unsigned char*)Mentor_USB_EP0_FIFO = DeviceStatus[i];
				(*(volatile unsigned char*)Mentor_USB_CSR0L) |= (BIT_1 | BIT_3);
			break;
		}
		break;

	case USB_REQ_CLASS://class
		switch (request1->mBits.recipient)
		{
			case USB_REC_INTERFACE:
			(*(volatile unsigned char*)Mentor_USB_CSR0L) |= (BIT_3 | BIT_6);
			reg= *(volatile unsigned short *)Mentor_USB_INTRTX;
			while((reg & BIT_0) != BIT_0)
				reg= *(volatile unsigned short *)Mentor_USB_INTRTX;
			if(request1->mBits.value_l)
			{
				configure_ep();
				prepare_linklist_node (USB_EP_DIR_OUT, (unsigned int)USB_EP6, (unsigned int)MAX_RECV_LENGTH,
						(unsigned int *)usb_out_endpoint_cmd, 0x01, 0x0);
			}
			break;
			default:
			{
				(*(volatile unsigned char*)Mentor_USB_CSR0L) |= (BIT_3 | BIT_6);
				reg= *(volatile unsigned short *)Mentor_USB_INTRTX;
				while((reg & BIT_0) != BIT_0)
					reg= *(volatile unsigned short *)Mentor_USB_INTRTX;
			}
			break;
		}
		break;
		default:
		{
			(*(volatile unsigned char*)Mentor_USB_CSR0L) |= (BIT_3 | BIT_6);
			reg= *(volatile unsigned short *)Mentor_USB_INTRTX;
			while((reg & BIT_0) != BIT_0)
				reg= *(volatile unsigned short *)Mentor_USB_INTRTX;
		}
		break;
	}
	}
}

/*****************************************************************************/
//  Description:   out endpoint0 handler.
//  Global resource dependence:
//  Author:        chunhou.wang
//  Note:
/*****************************************************************************/

LOCAL void USB_EPxSendData (char ep_id,unsigned char* pBuf,int len)
{
	int tx_ch;
	volatile uint32_t reg32;
	volatile uint32_t i;

	tx_ch = ep_id;

	prepare_linklist_node (USB_EP_DIR_IN, (unsigned int)ep_id, len, pBuf, 0x01, 0x0);

	//enable linklist end interrupt
	REG32(MUSB_DMA_CHN_INTR(tx_ch)) |= 0x04;
	//set linklist pointer
	REG32(MUSB_DMA_CHN_LLIST_PTR(tx_ch)) = (uint32_t)linklist_ram_tx;
	//enable channel and trigger rx dma transfer
	REG32(MUSB_DMA_CHN_CFG(tx_ch)) |= 0x1;

	//polling linklist end int
	reg32=REG32(MUSB_DMA_CHN_INTR(tx_ch));
	while((reg32 & BIT_18) != BIT_18)
		reg32=REG32(MUSB_DMA_CHN_INTR(tx_ch));

	//clear tx linklist end int
	REG32(MUSB_DMA_CHN_INTR(tx_ch)) |= BIT_26;

}
/*****************************************************************************/
//  Description:   out endpoint handler.
//  Global resource dependence:
//  Author:        chunhou.wang
//  Note:
/*****************************************************************************/
LOCAL void usb_EP_out_handle (void)
{

	volatile unsigned int reg32;
	int rx_ch;
	volatile unsigned int reg32_blk_len;
	unsigned long cache_start = 0;
	unsigned long cache_end = 0;
	uint32_t cache_len;
	//out ep for receive data
	rx_ch = USB_EP6 + 15;

	//clear linklist end interrupt
	REG32(MUSB_DMA_CHN_INTR(rx_ch)) |= 0x14000000;

	//get dma receive data len
	reg32_blk_len = REG32(MUSB_DMA_CHN_LEN(rx_ch));
	reg32_blk_len = (reg32_blk_len&0xffff0000)>>16;
	recv_length = MAX_RECV_LENGTH - reg32_blk_len;
	cache_start = (unsigned long)out_endpoint;

	if (g_recv_packet_len%64)
		cache_len = g_recv_packet_len - g_recv_packet_len%64 + 64;
	else
		cache_len = g_recv_packet_len;
	cache_end = cache_start + cache_len;
	invalidate_dcache_range(cache_start, cache_end);
}
/*****************************************************************************/
//  Description:   usb interrupt handler.
//  Global resource dependence:
//  Author:        chunhou.wang
//  Note:
/*****************************************************************************/
static __inline void usb_handler (void)
{
	volatile unsigned char reg_usb;
	volatile unsigned char reg_power;
	volatile unsigned short reg_tx;
	volatile unsigned int reg32;
	volatile unsigned char reg_rx;

	reg_usb = *(volatile unsigned char *)Mentor_USB_INTRUSB;
	if((reg_usb & BIT_2) == BIT_2)
	{
		reg_power=*(volatile unsigned char *)Mentor_USB_POWER;
		if((reg_power & BIT_4) == BIT_4)
			enum_speed =0;
		else
			enum_speed =1;
	}

	reg_tx = *(volatile unsigned short *)Mentor_USB_INTRTX;
	reg32 = REG32(MUSB_DMA_CHN_INTR(USB_EP6+15));

	if((reg_tx & BIT_0) == BIT_0)
	{
		(*(volatile unsigned char*)Mentor_USB_INDEX) = 0x0;
		usb_setup_handle();
	}
	if((reg32 &BIT_18)==BIT_18)
	{
		usb_EP_out_handle();
	}
}

/*****************************************************************************/
//  Description:   initialize the usb core.
//  Global resource dependence:
//  Author:        chunhou.wang
//  Note:
/*****************************************************************************/


#define udelay(x) \
	do { \
		volatile int i; \
		int cnt = 200 * (x); \
		for (i=0; i<cnt; i++);\
	} while(0);

#define mdelay(_ms) udelay((_ms)*1000)

static void usb_core_init (unsigned int autodl_mode)
{
	unsigned long cache_start = 0;
	unsigned long cache_end = 0;
	int rx_ch;

	readIndex = recv_length = 0;
	currentDmaBufferIndex = 0;

#ifdef CONFIG_SOC_SHARKL5
	void* musb_base = SPRD_USB_BASE;
	u8 c_size;

	musb_writeb(musb_base, MUSB_INDEX, 5);
	c_size = musb_read_rxfifosz(musb_base);
	c_size &= ~MUSB_FIFOSZ_DPB;
	musb_write_rxfifosz(musb_base, c_size);

	musb_writeb(musb_base, MUSB_INDEX, 6);
	c_size = musb_read_rxfifosz(musb_base);
	c_size &= ~MUSB_FIFOSZ_DPB;
	musb_write_rxfifosz(musb_base, c_size);
#endif
	cache_start = (unsigned long)(&usb_out_endpoint_cmd[0]);
	cache_end = cache_start + MAX_RECV_LENGTH;
	invalidate_dcache_range(cache_start, cache_end);

	prepare_linklist_node (USB_EP_DIR_OUT, (unsigned int)USB_EP6, (unsigned int)MAX_RECV_LENGTH,
			(unsigned int *)usb_out_endpoint_cmd, 0x01, 0x0);
	//out ep for receive data
	rx_ch = USB_EP6+15;
	//clear linklist end interrupt
	REG32(MUSB_DMA_CHN_INTR(rx_ch)) |=0x14000000;
	return;
}

int usb_send(unsigned char *pbuf, int len)
{
	USB_EPxSendData(USB_EP5,(unsigned int *)pbuf,len);
	return 0;
}

unsigned char usb_get_entry(void)
{

    if (readIndex == recv_length)
    {
        readIndex = 0;
        recv_length = 0;
	g_recv_packet_len = MAX_RECV_LENGTH;
REGET:
        usb_handler();

        if (recv_length > 0)
        {
            nIndex = currentDmaBufferIndex;
            currentDmaBufferIndex ^= 0x1;
        }
        else
        {
            goto REGET;
        }
    }

	return usb_out_endpoint_cmd[readIndex++];
}

int usb_rx_multi_nodes_config(unsigned char* buf, unsigned int len)
{
	if (NULL == buf || len == 0x0) {
		printf("%s buf:%p len :%d\r\n", __func__, buf, len);
		return -1;
	}

	prepare_linklist_multi_nodes(USB_EP_DIR_OUT,(unsigned int)USB_EP6, len, buf);
	out_endpoint = buf;
	recv_length = 0;

	return 0;
}

int usb_rx_data_from_linklist(unsigned int len)
{
	int tmp_len = 0;

	if (len > MAX_RECV_LENGTH)
		g_recv_packet_len = len;
	else
		g_recv_packet_len = (unsigned int)MAX_RECV_LENGTH;

	while (recv_length == 0) {
		usb_handler();
	}

	if (len > MAX_RECV_LENGTH)
		tmp_len = len;
	else
		tmp_len = recv_length;

	return tmp_len;
}

int usb_get_packet(unsigned char* buf, unsigned int len)
{
	unsigned char *src, *dest = buf;
	unsigned escape_flag = 0;
	unsigned pkt_flag = PKT_NONE;

	readIndex = recv_length = 0;
loop:
	prepare_linklist_node(USB_EP_DIR_OUT, (unsigned int)USB_EP6, (unsigned int)MAX_RECV_LENGTH,
			(unsigned int *)usb_out_endpoint_cmd, 0x01, 0x0);
	out_endpoint = usb_out_endpoint_cmd;
	if (readIndex == recv_length) {
		readIndex = 0;
		recv_length = 0;
		g_recv_packet_len = MAX_RECV_LENGTH;
REGET:
		usb_handler();

		if (recv_length > 0) {
			nIndex = currentDmaBufferIndex;
			currentDmaBufferIndex ^= 0x1;
		} else {
			goto REGET;
		}
	}
	src = usb_out_endpoint_cmd + readIndex;

	if (hdlc_disabled) {
		memcpy(buf,src+1,recv_length-2);
		readIndex = recv_length;
		return (recv_length - 2);
	}

	for (; readIndex < recv_length; src++) {
		readIndex++;
		switch (pkt_flag) {
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
					} else {
						*dest++ = *src;
					}
					pkt_flag = PKT_GATHER;
				}
				break;
		}
	}
	goto loop;
end:
	return dest - buf;
}

void usb_disableHDLC( int disabled)
{
	hdlc_disabled = disabled;
}

int usb_support_raw_data_proc(void)
{
	return 0x01;
}

void usb_init(unsigned int autodl_mode)
{
	usb_core_init(autodl_mode);
}
static void __raw_bits_and(unsigned int v, unsigned int a)
{
	__raw_writel((__raw_readl(a) & v), a);
}

static void __raw_bits_or(unsigned int v, unsigned int a)
{
	__raw_writel((__raw_readl(a) | v), a);
}

#define LDO_LDO_USB "vddusb33"

static inline
void    usb_ldo_switch(int flag)
{
        if(flag){
            regulator_enable(LDO_LDO_USB);
        } else {
            regulator_disable(LDO_LDO_USB);
        }
}

static void usb_enable_module(int en)
{
#ifdef REG_USB_EB
	if (en){
		__raw_bits_or(BIT_USB_EB, REG_USB_EB);
	}else {
		__raw_bits_and(~BIT_USB_EB, REG_USB_EB);
	}
#else
	if (en){
		__raw_bits_or(BIT_USB_EB, REG_AP_AHB_AHB_EB);
	}else {
		__raw_bits_and(~BIT_USB_EB, REG_AP_AHB_AHB_EB);
	}
#endif
}
void Musb_mdelay(uint32_t msecs)
{
	//mdelay(msecs);
#ifdef CONFIG_FPGA
	udelay(msecs * 10);
#else
	udelay(msecs * 1000);
#endif
}

static void usb_startup(void)
{
	usb_enable_module(1);
	Musb_mdelay(10);
	usb_ldo_switch(1);
#ifdef REG_USB_EB
	__raw_bits_or(BIT_USB_EB, REG_USB_EB);
#else
	__raw_bits_or(BIT_USB_EB, REG_AP_AHB_AHB_EB);
#endif
	usb_phy_init();
	Musb_mdelay(5);
}
void udc_power_on(void)
{
	usb_startup();
}
static void udc_disable(void)
{
        usb_enable_module(0);
        usb_ldo_switch(0);
}

void udc_power_off(void)
{
	udc_disable();
}

static void sprd_musb_enable(struct musb *musb)
{
	return;
}

static void sprd_musb_disable(struct musb *musb)
{
	return;
}

static int sprd_musb_init(struct musb *musb)
{
	return 0;
}

const struct musb_platform_ops sprd_musb_ops = {
	.init		= sprd_musb_init,
	.enable		= sprd_musb_enable,
	.disable	= sprd_musb_disable,
};

static struct musb_fifo_cfg sprd_musb_mode_cfg[] = {
	MUSB_EP_FIFO_SINGLE(5, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(6, FIFO_RX, 512),
};

static struct musb_hdrc_config musb_config = {
	.fifo_cfg = sprd_musb_mode_cfg,
	.fifo_cfg_size = ARRAY_SIZE(sprd_musb_mode_cfg),
	.multipoint     = 1,
	.dyn_fifo       = 1,
	.num_eps        = 7,
	.ram_bits       = 11,
};

static struct musb_hdrc_platform_data sprd_musb = {
	.mode		= MUSB_PERIPHERAL,
	.config         = &musb_config,
	.power          = 250,
	.platform_ops	= &sprd_musb_ops,
};

int usb_driver_init(unsigned int max_speed)
{
	int retval = 0;
	int error;

	hdlc_disabled = 0;
	udc_power_on();

	if (max_speed == USB_SPEED_HIGH) {
		(*(volatile unsigned char*)Mentor_USB_POWER)    =0x60;
		(*(volatile unsigned char*)Mentor_USB_INTRUSBE)=0xff;
	} else {
		(*(volatile unsigned char*)Mentor_USB_POWER)    =0x40;
		(*(volatile unsigned char*)Mentor_USB_INTRUSBE)=0xff;
	}

	musb_register(&sprd_musb, NULL, (void *)SPRD_USB_BASE);

	return retval;
}
 void usb_driver_exit(void)
{
	udc_power_off();
}
