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
#include <packet.h>
#include <fdl_crc.h>
#include "usb200_fdl.h"
#include "sprd_musb2_def.h"


static __inline void usb_handler (void);
extern void * sprd_memset(void * string,int fill,size_t cnt);
extern void * sprd_memcpy(void *dst, const void *src, size_t cnt);
/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#define MAX_RECV_LENGTH     (64*64)//640*64 0xa000
#define USB_TIMEOUT             (1000)
#define REG32(x)     (*((volatile uint32 *)(x)))
/**---------------------------------------------------------------------------*
 **                         Data Structures                                   *
 **---------------------------------------------------------------------------*/

static int currentDmaBufferIndex;
static uint32    enum_speed;
static uint32    recv_length;
static uint32 nIndex, readIndex;
#if defined(CONFIG_PACKET_USB_FIX_ADDR)
static __align(64)  unsigned char *usb_out_endpoint_buf;
#else
static __align(64)  unsigned char usb_out_endpoint_buf[MAX_RECV_LENGTH];
#endif
volatile unsigned char    s_setup_packet[8];
struct linklist_node_s dma_linklist_tx;
struct linklist_node_s dma_linklist_rx;

__align (8) unsigned char linklist_ram_tx[12];
__align (8) unsigned char linklist_ram_rx[12];
__align (4) unsigned char DeviceStatus[] =
{
	0x00,0x00
};
static __align(4) uint8 dev_desc[] =
{
	0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x40,
	0x82, 0x17, 0x00, 0x4d, 0xff, 0xff, 0x00, 0x00,
	0x00, 0x01
};
static __align(4) uint8 config_desc[] =
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
void prepare_linklist_node (uint32 dir,int ep, unsigned int transfer_size, unsigned int *buffer)
{
	volatile unsigned char *q;
	volatile unsigned char *p;
	int rx_ch;

	if(dir)
	{
		dma_linklist_rx.addr = buffer;
		dma_linklist_rx.blk_len = transfer_size;
		dma_linklist_rx.frag_len=32;
		dma_linklist_rx.ep_num=ep;
		dma_linklist_rx.ioc=1;
		dma_linklist_rx.sp=0;
		dma_linklist_rx.list_end=1;

		q =&linklist_ram_rx[0];

		sprd_memset(linklist_ram_rx,0,sizeof(linklist_ram_rx));

		sprd_memcpy(q,&dma_linklist_rx.addr,4);
		q+=4;
		sprd_memcpy(q,&dma_linklist_rx.frag_len,2);
		q+=2;
		sprd_memcpy(q,&dma_linklist_rx.blk_len,2);
		q+=2;

		*q = (dma_linklist_rx.ioc <<2)|(dma_linklist_rx.sp <<1)|dma_linklist_rx.list_end;
		q+=4;

		//out ep for receive data
		rx_ch = ep+15;
		//enable linklist end interrupt
		REG32(MUSB_DMA_CHN_INTR(rx_ch)) |=0x14;
		//set linklist pointer
		REG32(MUSB_DMA_CHN_LLIST_PTR(rx_ch)) = (uint32)linklist_ram_rx;
		//enable channel and trigger rx dma transfer
		REG32(MUSB_DMA_CHN_CFG(rx_ch)) |=0x1;
	}else{
		dma_linklist_tx.addr = buffer;
		dma_linklist_tx.blk_len = transfer_size;
		dma_linklist_tx.frag_len=32;
		dma_linklist_tx.ep_num=ep;
		dma_linklist_tx.ioc=1;
		dma_linklist_tx.sp=0;
		dma_linklist_tx.list_end=1;

		p =&linklist_ram_tx[0];

		sprd_memset(linklist_ram_tx,0,sizeof(linklist_ram_tx));

		sprd_memcpy(p,&dma_linklist_tx.addr,4);
		p+=4;
		sprd_memcpy(p,&dma_linklist_tx.frag_len,2);
		p+=2;
		sprd_memcpy(p,&dma_linklist_tx.blk_len,2);
		p+=2;

		*p = (dma_linklist_tx.ioc <<2)|(dma_linklist_tx.sp <<1)|dma_linklist_tx.list_end;
		p+=4;
	}
}
/*****************************************************************************/
//  Description:   process desecriptor request.
//  Global resource dependence:
//  Author:        chunhou.wang
//  Note:
/*****************************************************************************/
LOCAL void usb_get_descriptor (USB_REQUEST_1_U *request1, USB_REQUEST_2_U *request2)
{
	uint32 len, length = 0;
	uint8   *send_data = NULL;
	uint32 i;

	(*(volatile unsigned char*)Mentor_USB_CSR0L) |= BIT_6;

	length = (uint32) request2->mBits.length_l;

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
	uint32 length =0;

	reg1 = *(volatile unsigned char*)Mentor_USB_CSR0L ;
	if((reg1 & BIT_0 ) == BIT_0)
	{
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
				length = (uint32)(request2->mBits.length_l | (request2->mBits.length_m<<8));
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
				prepare_linklist_node (USB_EP_DIR_OUT,(unsigned int)USB_EP6,(unsigned int)MAX_RECV_LENGTH,(unsigned int *) usb_out_endpoint_buf);
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

LOCAL void USB_EPxSendData (char ep_id,unsigned int* pBuf,int len)
{
	int tx_ch;
	volatile uint32 reg32;

	tx_ch = ep_id;

	prepare_linklist_node (USB_EP_DIR_IN,(unsigned int)ep_id, len,pBuf);

	//enable linklist end interrupt
	REG32(MUSB_DMA_CHN_INTR(tx_ch)) |=0x04;
	//set linklist pointer
	REG32(MUSB_DMA_CHN_LLIST_PTR(tx_ch)) = (uint32)linklist_ram_tx;
	//enable channel and trigger rx dma transfer
	REG32(MUSB_DMA_CHN_CFG(tx_ch)) |=0x1;

	//polling linklist end int
	reg32=REG32(MUSB_DMA_CHN_INTR(tx_ch));
	while((reg32 & BIT_18) !=BIT_18)
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

	//out ep for receive data
	rx_ch = USB_EP6+15;
	//clear linklist end interrupt
	REG32(MUSB_DMA_CHN_INTR(rx_ch)) |=0x14000000;

	//get dma receive data len
	reg32_blk_len = REG32(MUSB_DMA_CHN_LEN(rx_ch));
	reg32_blk_len = (reg32_blk_len&0xffff0000)>>16;
	recv_length = MAX_RECV_LENGTH - reg32_blk_len ;

	//enable linklist end interrupt
	REG32(MUSB_DMA_CHN_INTR(rx_ch)) |=0x14;
	//set linklist pointer
	REG32(MUSB_DMA_CHN_LLIST_PTR(rx_ch)) = (uint32)linklist_ram_rx;
	//enable channel and trigger rx dma transfer
	REG32(MUSB_DMA_CHN_CFG(rx_ch)) |=0x1;
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

	reg_usb = *(volatile unsigned char *)Mentor_USB_INTRUSB;
	if((reg_usb & BIT_2) == BIT_2)
	{
		reg_power=*(volatile unsigned char *)Mentor_USB_POWER;
		if((reg_power & BIT_4) ==BIT_4)
			enum_speed =0;
		else
			enum_speed =1;
	}

	reg_tx = *(volatile unsigned short *)Mentor_USB_INTRTX;
	reg32 =REG32(MUSB_DMA_CHN_INTR(USB_EP6+15));
	if((reg_tx & BIT_0)==BIT_0)
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

static void usb_core_init (void)
{
	(*(volatile unsigned char*)Mentor_USB_POWER)    =0x60;
	(*(volatile unsigned char*)Mentor_USB_INTRUSBE)=0xff;
	return;
}

int usb_send(unsigned char *pbuf, int len)
{
	USB_EPxSendData(USB_EP5,(unsigned int*) pbuf,len);
	return 0;
}

unsigned char usb_get_entry(void)
{
	prepare_linklist_node (USB_EP_DIR_OUT,(unsigned int)USB_EP6,(unsigned int)MAX_RECV_LENGTH,(unsigned int *) usb_out_endpoint_buf);


    if (readIndex == recv_length)
    {
        readIndex = 0;
        recv_length = 0;
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

	return usb_out_endpoint_buf[readIndex++];
}

int usb_get_packet(unsigned char* buf, unsigned int len)
{
    unsigned char *src, *dest = buf;
    unsigned escape_flag = 0;
    unsigned pkt_flag = PKT_NONE;
	//prepare_linklist_node (USB_EP_DIR_OUT,(unsigned int)USB_EP6,(unsigned int)MAX_RECV_LENGTH,(unsigned int *) usb_out_endpoint_buf);

loop:
    if(readIndex == recv_length){
        readIndex = 0;
        recv_length = 0;
REGET:
        usb_handler();


        if (recv_length > 0){
            nIndex = currentDmaBufferIndex;
            currentDmaBufferIndex ^= 0x1;
        }else
            goto REGET;
    }
    src = usb_out_endpoint_buf+ readIndex;

    for (; readIndex < recv_length; src++) {
        readIndex++;
        switch (pkt_flag) {
        case PKT_NONE:
            if (*src == HDLC_FLAG)
                pkt_flag = PKT_HEAD;
            break;
        case PKT_GATHER:
            if(*src == HDLC_FLAG) {
                pkt_flag = PKT_RECV;
                goto end;
            }
        case PKT_HEAD:
            if(*src != HDLC_FLAG) {
                if(*src == HDLC_ESCAPE)
                    escape_flag = 1;
                else if(escape_flag) {
                    *dest++ = *src ^ HDLC_ESCAPE_MASK;
                    escape_flag = 0;
                } else
                    *dest++ = *src;
                pkt_flag = PKT_GATHER;
            }
            break;
        }

    }
    goto loop;
end:
    return dest - buf;
}

void usb_init(unsigned long usb_reg_base)
{
#if defined(CONFIG_PACKET_USB_FIX_ADDR)
    usb_out_endpoint_buf = (unsigned char*)USB_FIX_ADDR;
#endif
	usb_core_init();
}

