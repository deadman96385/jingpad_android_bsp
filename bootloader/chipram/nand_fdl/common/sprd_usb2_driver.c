/******************************************************************************
 ** File Name:      sprd_usb2_driver.c                                        *
 ** Author:         JiaYong.Yang                                              *
 ** DATE:           09/01/2010                                                *
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
#include "sprd_usb2_def.h"


PUBLIC void Dcache_InvalRegion(unsigned int addr, unsigned int length);
PUBLIC void Dcache_CleanRegion(unsigned int addr, unsigned int length);

static __inline void usb_handler (void);
/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#define MAX_RECV_LENGTH     (64*64)//640*64 0xa000
#define USB_TIMEOUT             (1000)

/**---------------------------------------------------------------------------*
 **                         Data Structures                                   *
 **---------------------------------------------------------------------------*/

static int currentDmaBufferIndex;
static uint32    enum_speed;
static uint32    recv_length;
static uint32 nIndex, readIndex;
static __align(64)  unsigned char usb_out_endpoint_buf[2][MAX_RECV_LENGTH];
static __align(64) uint32    s_setup_packet[8];

/*****************************************************************************/
//  Description:   configure out endpoint0 to receive setup message.
//  Global resource dependence:
//  Author:        jiayong.yang
//  Note:
/*****************************************************************************/
LOCAL void EPO0_config (BOOLEAN is_dma, uint32 *buffer)
{
    // Programs DOEPTSIZ0 register with Packet Count and Transfer Size
    * (volatile uint32 *) USB_DOEP0TSIZ |= BIT_19 |BIT_30
			| BIT_29 | BIT_3 | BIT_4;
    if (is_dma)
    {
        * (volatile uint32 *) USB_DOEPDMA (0) = (uint32) buffer;
    }

    * (volatile uint32 *) USB_DOEP0CTL |= (unsigned int) BIT_31;
    * (volatile uint32 *) USB_DOEP0CTL |= (unsigned int) BIT_26;
}
/*****************************************************************************/
//  Description:   configure in endpoint0 to send message.
//  Global resource dependence:
//  Author:        jiayong.yang
//  Note:
/*****************************************************************************/
void EPI0_config (uint32 transfer_size, uint32 packet_count, BOOLEAN is_dma, uint32 *buffer)
{
    volatile USB_DIEP0TSIZ_U *diep0tsiz_ptr = (USB_DIEP0TSIZ_U *) USB_DIEP0TSIZ;

    diep0tsiz_ptr->mBits.transfer_size = transfer_size;
    diep0tsiz_ptr->mBits.packet_count = packet_count;

    if (is_dma)
    {
#if defined CONFIG_SC8810 || defined CONFIG_SC8825 || defined CONFIG_SC8830  || defined CONFIG_SC9630
	Dcache_CleanRegion((unsigned int)(buffer), transfer_size);
#endif
	* (volatile uint32 *) USB_DIEPDMA (0) = (uint32) buffer;//lint !e718
    }

    * (volatile uint32 *) USB_DIEP0CTL |= (unsigned int) BIT_31;
    * (volatile uint32 *) USB_DIEP0CTL |= (unsigned int) BIT_26;
}

/*****************************************************************************/
//  Description:   configure specified endpoint to send/receive message.
//  Global resource dependence:
//  Author:        jiayong.yang
//  Note:
/*****************************************************************************/
LOCAL void EPn_Enable(USB_EP_NUM_E ep_num, USB_EP_TYPE_E ep_type, BOOLEAN dir, uint32 mps)
{
    // out endpoint
    if (dir)
    {
        volatile USB_DOEPCTL_U *doepctl_ptr = (USB_DOEPCTL_U *) USB_DOEPCTL (ep_num);

        doepctl_ptr->mBits.ep_type = ep_type;
        doepctl_ptr->mBits.mps = mps;
        doepctl_ptr->mBits.set_nak = 0x1;
        doepctl_ptr->mBits.active_ep = 1;
        doepctl_ptr->mBits.set_data0_pid = 1;
    }
    else
    {
        volatile USB_DIEPCTL_U *diepctl_ptr = (USB_DIEPCTL_U *) USB_DIEPCTL (ep_num);

        diepctl_ptr->mBits.ep_type = ep_type;
        diepctl_ptr->mBits.mps = mps;
        diepctl_ptr->mBits.set_nak = 1;
        diepctl_ptr->mBits.active_ep = 1;
        diepctl_ptr->mBits.tx_fifo_number = ep_num;
        diepctl_ptr->mBits.set_data0_pid = 1;
    }
}

/*****************************************************************************/
//  Description:   start endpoint transfer.
//  Global resource dependence:
//  Author:        jiayong.yang
//  Note:
/*****************************************************************************/
LOCAL void usb_start_transfer (USB_EP_NUM_E ep_num, BOOLEAN dir, uint32 transfer_size, BOOLEAN is_dma, uint32 *buffer)
{
    uint16 packet_count = 0;

    if (dir)
    {
        volatile USB_DOEPTSIZ_U *doeptsiz_ptr = (USB_DOEPTSIZ_U *) USB_DOEPTSIZ (ep_num);
        volatile USB_DOEPCTL_U   *doepctl_ptr = (USB_DOEPCTL_U *) USB_DOEPCTL (ep_num);

        if (is_dma)
        {
	//	Dcache_InvalRegion((unsigned int)buffer,  MAX_RECV_LENGTH);
		* (volatile uint32 *) USB_DOEPDMA (ep_num) = (uint32) buffer;
        }

        doeptsiz_ptr->mBits.transfer_size = MAX_RECV_LENGTH;    // transfer size
        doeptsiz_ptr->mBits.packet_count = (MAX_RECV_LENGTH+doepctl_ptr->mBits.mps-1)/doepctl_ptr->mBits.mps;
        * (volatile uint32 *) USB_DOEPCTL (ep_num) |= (unsigned int) BIT_26; // clear nak
        * (volatile uint32 *) USB_DOEPCTL (ep_num) |= (unsigned int) BIT_31; // endpoint enable
    }
    else
    {
        volatile USB_DIEPTSIZ_U *dieptsiz_ptr = (USB_DIEPTSIZ_U *) USB_DIEPTSIZ (ep_num);
        volatile USB_DIEPCTL_U   *diepctl_ptr = (USB_DIEPCTL_U *) USB_DIEPCTL (ep_num);


        if (is_dma)
        {
#if defined CONFIG_SC8810 || defined CONFIG_SC8825 || defined CONFIG_SC8830 || defined CONFIG_SC9630
		Dcache_CleanRegion((unsigned int)buffer,  transfer_size);
#endif
		* (volatile uint32 *) USB_DIEPDMA (ep_num) = (uint32) buffer;
        }

        dieptsiz_ptr->mBits.transfer_size = transfer_size;                  // transfer size
        packet_count = (transfer_size+diepctl_ptr->mBits.mps-1) /diepctl_ptr->mBits.mps;
        dieptsiz_ptr->mBits.packet_count = packet_count;                    // packet count

        * (volatile uint32 *) USB_DIEPCTL (ep_num) |= (unsigned int) BIT_26;            // clear nak
        * (volatile uint32 *) USB_DIEPCTL (ep_num) |= (unsigned int) BIT_31;            // endpoint enable
    }

}
static __align(4) uint8 dev_desc[] =
{
	0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x40,
	0x82, 0x17, 0x00, 0x4d, 0xff, 0xff, 0x00, 0x00,
	0x00, 0x01,
};
static __align(4) uint8 config_desc[] =
{
	0x09, 0x02, 0x20, 0x00, 0x01, 0x01, 0x00, 0xc0,0x32,
	0x09, 0x04, 0x00, 0x00, 0x02, 0xff, 0x00, 0x00, 0x00,
	0x07, 0x05, 0x85, 0x02, 0x00, 0x02, 0x00,
	0x07, 0x05, 0x06, 0x02, 0x00, 0x02, 0x00
};
/*****************************************************************************/
//  Description:   process desecriptor request.
//  Global resource dependence:
//  Author:        jiayong.yang
//  Note:
/*****************************************************************************/
LOCAL void usb_get_descriptor (USB_REQUEST_1_U *request1, USB_REQUEST_2_U *request2)
{
	uint32 len, length = 0;
	uint8   *send_data = NULL;


	length = (uint32) request2->mBits.length_l;

	switch (request1->mBits.value_m)
	{
	case USB_DEVICE_DESCRIPTOR_TYPE:
		send_data = dev_desc;
		len = length < sizeof(dev_desc) ?
			length : sizeof(dev_desc);
		EPI0_config (len, 0x1, TRUE, (uint32 *)send_data);
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
		EPI0_config (len, 0x1, TRUE, (uint32 *) send_data);
		break;

	default:
		* (volatile uint32 *) USB_DIEP0CTL |= BIT_21;
		break;
	}
}
/*****************************************************************************/
//  Description:   process setup transaction.
//  Global resource dependence:
//  Author:        jiayong.yang
//  Note:
/*****************************************************************************/
LOCAL void usb_setup_handle (void)
{
	uint32  mps, vendor_ack = 0;
	USB_REQUEST_1_U   *request1;
	USB_REQUEST_2_U   *request2;

	request1 = (USB_REQUEST_1_U *) (unsigned int) (&s_setup_packet[0]);
	request2 = (USB_REQUEST_2_U *) (unsigned int) (&s_setup_packet[1]);

	switch (request1->mBits.type)
	{

	case USB_REQ_STANDARD://standard

		switch (request1->mBits.brequest)
		{
		case USB_REQUEST_SET_ADDRESS:
		{
			volatile USB_DCFG_U *dcfg_ptr = (USB_DCFG_U *) USB_DCFG;

			dcfg_ptr->mBits.devaddr = request1->mBits.value_l;
			EPI0_config (0, 1, FALSE, NULL);
		}
			break;

		case USB_REQUEST_GET_DESCRIPTOR:
			usb_get_descriptor (request1, request2);
			break;

		case USB_REQUEST_SET_CONFIGURATION:
			EPI0_config (0, 1, FALSE, NULL);
			mps = enum_speed ? 0x40 : 0x200;
			EPn_Enable(USB_EP5, USB_EP_TYPE_BULK, USB_EP_DIR_IN, mps);
			EPn_Enable(USB_EP6, USB_EP_TYPE_BULK, USB_EP_DIR_OUT, mps);
			break;

		case USB_REQUEST_GET_STATUS:
			EPI0_config (2, 1, TRUE, &vendor_ack);
			break;
		}
	break;

	case USB_REQ_CLASS://class
		EPI0_config (0, 1, FALSE, NULL);
		break;
	}
}
/*****************************************************************************/
//  Description:   usb reset interrupt handler.
//  Global resource dependence:
//  Author:        jiayong.yang
//  Note:
/*****************************************************************************/

LOCAL void usb_reset_handler (void)
{
	int i, timeout = 0;
	volatile USB_DCFG_U *dcfg_ptr = (USB_DCFG_U *) USB_DCFG;

    for (i = 0; i < 16; i++)
        * (volatile uint32 *)USB_DOEPCTL(i) |= BIT_27;
    * (volatile uint32 *) USB_DOEP0CTL |= BIT_27;
    * (volatile uint32 *) USB_GINTMSK &= (~BIT_12);
    * (volatile uint32 *) USB_DAINTMSK = ~0;
    * (volatile uint32 *) USB_DOEPMSK |= BIT_13|BIT_3|BIT_0;
    * (volatile uint32 *) USB_DIEPMSK |= BIT_0 | BIT_3;
	dcfg_ptr->mBits.devaddr = 0;

	/* Flush RxFIFO */
    * (volatile uint32 *) USB_GRSTCTL |= (unsigned int) BIT_5;
    while ( (* (volatile uint32 *) USB_GRSTCTL) & ( (unsigned int) BIT_5))
    {
        timeout++;
        if (timeout >= USB_TIMEOUT)
            break;
    }

    timeout = 0;
	/* Flush all TxFIFOs */
    * (volatile uint32 *) USB_GRSTCTL |= BIT_10;
    * (volatile uint32 *) USB_GRSTCTL |= (unsigned int) BIT_4;
    while ( (* (volatile uint32 *) USB_GRSTCTL) & ( (unsigned int) BIT_4))
    {
        timeout++;
        if (timeout >= USB_TIMEOUT)
            break;
    }
    * (volatile uint32 *) USB_GINTMSK |= BIT_12;
#ifndef CONFIG_SCX35L64
    Dcache_InvalRegion((unsigned int)s_setup_packet, sizeof(s_setup_packet));
#endif
    EPO0_config (TRUE, s_setup_packet);
}

/*****************************************************************************/
//  Description:   usb enumeration done handler.
//  Global resource dependence:
//  Author:        jiayong.yang
//  Note:
/*****************************************************************************/

void usb_enumeration_done (void)
{
    volatile USB_DSTS_U *dsts_ptr = (USB_DSTS_U *) USB_DSTS;

    enum_speed = dsts_ptr->mBits.enumspd; //read enumration speed

    * (volatile uint32 *) USB_DCTL |= (unsigned int) BIT_8;
}
/*****************************************************************************/
//  Description:    out endpoint6 handler.
//  Global resource dependence:
//  Author:        jiayong.yang
//  Note:
/*****************************************************************************/
LOCAL void usb_EP6_handle (void)
{
    volatile USB_DOEPINT_U *doepint_ptr = (USB_DOEPINT_U *) USB_DOEPINT (USB_EP6);
    volatile USB_DOEPINT_U  doepint;
    volatile USB_DOEPTSIZ_U *doeptsiz_ptr = (USB_DOEPTSIZ_U *) USB_DOEPTSIZ (USB_EP6);
    volatile uint32  mask;

    mask = * (volatile uint32 *) USB_DOEPMSK;
    doepint.dwValue = doepint_ptr->dwValue;

    doepint.dwValue &= (unsigned int) mask;

    if (doepint.mBits.transfer_com)
    {
        doepint_ptr->mBits.transfer_com = 1;
        recv_length = MAX_RECV_LENGTH - doeptsiz_ptr->mBits.transfer_size;
#ifndef CONFIG_SCX35L64
        Dcache_InvalRegion((unsigned int)(&usb_out_endpoint_buf[currentDmaBufferIndex][0]),  MAX_RECV_LENGTH);
#endif
        * (volatile uint32 *) USB_DOEPMSK |= (unsigned int) BIT_13;
        * (volatile uint32 *) USB_DOEPMSK |= (unsigned int) BIT_4;
        * (volatile uint32 *) USB_DOEPMSK &= (unsigned int) (~BIT_0);
    }
    else if (doepint.mBits.nak)
    {
        doepint_ptr->mBits.nak = 0x1;
        usb_start_transfer (USB_EP6, USB_EP_DIR_OUT, 1,
			TRUE, (uint32 *) usb_out_endpoint_buf[currentDmaBufferIndex]);
        * (volatile uint32 *) USB_DOEPMSK &= (unsigned int) (~BIT_13);
        * (volatile uint32 *) USB_DOEPMSK |= (unsigned int) BIT_0;
    }
    else if (doepint.mBits.bbleerr)
    {
        doepint_ptr->mBits.bbleerr = 0x01;
    }
}
/*****************************************************************************/
//  Description:   out endpoint0 handler.
//  Global resource dependence:
//  Author:        jiayong.yang
//  Note:
/*****************************************************************************/

LOCAL void usb_EP0_out_handle (void)
{
    volatile USB_DOEPINT_U *doepint_ptr = (USB_DOEPINT_U *) USB_DOEPINT (0);

    if (doepint_ptr->mBits.timeout_condi)
    {
        doepint_ptr->mBits.timeout_condi = 1;
        usb_setup_handle();
    }

    if (doepint_ptr->mBits.transfer_com)
    {
        doepint_ptr->mBits.transfer_com = 0x1;
        * (volatile uint32 *) USB_DOEP0CTL |= (unsigned int) BIT_27;
    }

    if (doepint_ptr->mBits.outtokenfifoemp)
    {
        doepint_ptr->mBits.outtokenfifoemp = 0x1;
    }

    doepint_ptr->dwValue = 0xffffffff;// clear all interrupt
#ifndef CONFIG_SCX35L64
    Dcache_InvalRegion((unsigned int)s_setup_packet, sizeof(s_setup_packet));
#endif
    EPO0_config (TRUE, s_setup_packet); //renable ep0 nd set packet count
}

/*****************************************************************************/
//  Description:   out endpoint handler.
//  Global resource dependence:
//  Author:        jiayong.yang
//  Note:
/*****************************************************************************/
LOCAL void usb_EP_out_handle (void)
{
    volatile USB_DAINT_U *daint_ptr = (USB_DAINT_U *) USB_DAINT;
    USB_DAINT_U daint;

    daint.dwValue = daint_ptr->dwValue;         // disable EP out interrupt
    * (volatile uint32 *) USB_GINTMSK &= (unsigned int) (~BIT_19);

    if (daint.mBits.outepint_0)
    {
        usb_EP0_out_handle();
    }

    if (daint.mBits.outepint_6)
    {
        usb_EP6_handle();
    }

    * (volatile uint32 *) USB_GINTMSK |= (unsigned int) BIT_19; // enable reset interrupt
}
/*****************************************************************************/
//  Description:   in endpoint handler.
//  Global resource dependence:
//  Author:        jiayong.yang
//  Note:
/*****************************************************************************/
LOCAL void usb_EP_in_handle (void)
{
    volatile USB_DAINT_U *daint_ptr = (USB_DAINT_U *) USB_DAINT;
    USB_DAINT_U daint;


    * (volatile uint32 *) USB_GINTMSK &= (unsigned int) (~BIT_18); // disable EP in interrupt
    daint.dwValue = daint_ptr->dwValue;

    if (daint.mBits.inepint_0)
    {
        volatile USB_DIEPINT_U *diepint_ptr = (USB_DIEPINT_U *) USB_DIEPINT (0);

        diepint_ptr->dwValue = 0xFFFFFFFF;
    }

    if (daint.mBits.inepint_5)
    {
        volatile USB_DIEPINT_U *diepint_ptr = (USB_DIEPINT_U *) USB_DIEPINT (5);

        diepint_ptr->dwValue = 0xFFFFFFFF;
    }

    * (volatile uint32 *) USB_GINTMSK |= (unsigned int) BIT_18; // enable EP in interrupt
}

/*****************************************************************************/
//  Description:   usb interrupt handler.
//  Global resource dependence:
//  Author:        jiayong.yang
//  Note:
/*****************************************************************************/

static __inline void usb_handler (void)
{
    volatile USB_INTSTS_U *usb_int_ptr = (USB_INTSTS_U *) USB_GINTSTS;
    volatile USB_INTSTS_U  usb_int;

    usb_int.dwValue = usb_int_ptr->dwValue;

    // reset interrupt
    if (usb_int.mBits.usbrst)
    {
        * (volatile uint32 *) USB_GINTSTS = BIT_12;
        usb_reset_handler();
    }

	// enumeration done interrupt
    if (usb_int.mBits.enumdone)
    {
        * (volatile uint32 *) USB_GINTSTS = BIT_13;
        usb_enumeration_done();
    }

    // out endpoint interrupt
    if (usb_int.mBits.oepint)
    {
        * (volatile uint32 *) USB_GINTSTS = BIT_19;
        usb_EP_out_handle();
    }

	// in endpoint interrupt
    if (usb_int.mBits.iepint)
    {
        * (volatile uint32 *) USB_GINTSTS = BIT_18;
        usb_EP_in_handle();
    }
}

/*****************************************************************************/
//  Description:   initialize the usb core.
//  Global resource dependence:
//  Author:        jiayong.yang
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
#ifdef CONFIG_USB_RESET
	uint32 reg_value;

	// Soft Disconnect
	* (volatile uint32 *) USB_DCTL |= BIT_1;
	// Reset Core
	*(volatile uint32 *)(AHB_SOFT_RST) |= BIT_6|BIT_7;
	mdelay(3);
	*(volatile uint32 *)(AHB_SOFT_RST) &= ~(BIT_6|BIT_7);
	mdelay(5);

	* (volatile uint32 *) USB_GRSTCTL |= BIT_0;
	do
	{
		reg_value = * (volatile uint32 *) USB_GRSTCTL;

	}while (reg_value & BIT_0);

	*(volatile uint32 *)USB_GOTGCTL |= BIT_6 | BIT_7;
	*(volatile uint32 *)USB_GAHBCFG |= 0x2F;
	*(volatile uint32 *)USB_GAHBCFG |= BIT_23;
	*(volatile uint32 *)USB_GUSBCFG |= BIT_30;
	*(volatile uint32 *)USB_GUSBCFG &= ~(BIT_4 | BIT_6 | BIT_17);
	*(volatile uint32 *)USB_GUSBCFG |= BIT_3;
	*(volatile uint32 *)USB_GUSBCFG |= BIT_0;
	*(volatile uint32 *)USB_GUSBCFG |= BIT_10 | BIT_12;
	*(volatile uint32 *)USB_GINTSTS |= ~0;
	*(volatile uint32 *)USB_GINTMSK = 0;
	*(volatile uint32 *)USB_DCFG &= ~BIT_2;
	*(volatile uint32 *)USB_DCFG &= ~(BIT_11 | BIT_12);
	*(volatile uint32 *)USB_GINTMSK |= (BIT_4 | BIT_12  |BIT_13);
	*(volatile uint32 *)USB_GINTMSK |= (BIT_18 | BIT_19);
	*(volatile uint32 *)USB_DCFG &= ~3;
	*(volatile uint32 *)USB_DCTL &= ~BIT_1;
#endif
	return;
}

int usb_send(unsigned char *pbuf, int len)
{
	usb_start_transfer(USB_EP5, USB_EP_DIR_IN, (uint32) len , 1, (uint32*) pbuf);
	return 0;
}

unsigned char usb_get_entry(void)
{

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

	return usb_out_endpoint_buf[nIndex][readIndex++];
}

int usb_get_packet(unsigned char* buf, unsigned int len)
{
    unsigned char *src, *dest = buf;
    unsigned escape_flag = 0;
    unsigned pkt_flag = PKT_NONE;

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
    src = usb_out_endpoint_buf[nIndex] + readIndex;

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
	usb_core_init();
}

