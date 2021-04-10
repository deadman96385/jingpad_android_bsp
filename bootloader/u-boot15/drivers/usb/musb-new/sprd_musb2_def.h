/******************************************************************************
 ** File Name:    sprd_musb2_def.h                                            *
 ** Author:       chunhou.wang                                                *
 ** DATE:         07/13/2016                                                  *
 ** Copyright:    2016 Spreatrum, Incoporated. All Rights Reserved.           *
 ** Description:                                                              *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                                         *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                                 *
 ** 07/13/2016    chunhou.wang    Create.                                     *
 ******************************************************************************/
#ifndef _USB20_V3_REG_H_
#define _USB20_V3_REG_H_
/*----------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **------------------------------------------------------------------------- */

/**---------------------------------------------------------------------------*
 **                             Compiler Flag                                 *
 **--------------------------------------------------------------------------*/
#ifdef   __cplusplus
extern   "C"
{
#endif
/**---------------------------------------------------------------------------*
**                               Micro Define                                **
**---------------------------------------------------------------------------*/

#if 1
#include <asm/arch/sprd_reg.h>


//**************** Core Global CSR ***************************
#define USB_REG_BASE	SPRD_USB_BASE

#define Mentor_USB_FADDR                     (USB_REG_BASE + 0x00)
#define Mentor_USB_POWER                     (USB_REG_BASE + 0x01)
#define Mentor_USB_INTRTX                    (USB_REG_BASE + 0x02)
#define Mentor_USB_INTRRX                    (USB_REG_BASE + 0x04)
#define Mentor_USB_INTRTXE                   (USB_REG_BASE + 0x06)
#define Mentor_USB_INTRRXE                   (USB_REG_BASE + 0x08)
#define Mentor_USB_INTRUSB                   (USB_REG_BASE + 0x0A)
#define Mentor_USB_INTRUSBE                  (USB_REG_BASE + 0x0B)
#define Mentor_USB_FMNO                      (USB_REG_BASE + 0x0C)
#define Mentor_USB_INDEX                     (USB_REG_BASE + 0x0E)
#define Mentor_USB_TXMAXP(n)                 (USB_REG_BASE + 0x100+n*0x10)
#define Mentor_USB_TXCSRL(n)                 (USB_REG_BASE + 0x102+n*0x10)
#define Mentor_USB_TXCSRH(n)                 (USB_REG_BASE + 0x103+n*0x10)
#define Mentor_USB_RXMAXP(n)                 (USB_REG_BASE + 0x104+n*0x10)
#define Mentor_USB_RXCSRL(n)                 (USB_REG_BASE + 0x106+n*0x10)
#define Mentor_USB_RXCSRH(n)                 (USB_REG_BASE + 0x107+n*0x10)
#define Mentor_USB_RXCOUNT(n)                (USB_REG_BASE + 0x108+n*0x10)
#define Mentor_USB_CSR0L                     (USB_REG_BASE + 0x12)
#define Mentor_USB_CSR0H                     (USB_REG_BASE + 0x13)
#define Mentor_USB_COUNT0                    (USB_REG_BASE + 0x18)
#define Mentor_USB_EP0_FIFO                  (USB_REG_BASE + 0x20)
#define Mentor_USB_EP1_FIFO                  (USB_REG_BASE + 0x24)
#define Mentor_USB_EP2_FIFO                  (USB_REG_BASE + 0x28)
#define Mentor_USB_EP3_FIFO                  (USB_REG_BASE + 0x2C)
#define Mentor_USB_EP4_FIFO                  (USB_REG_BASE + 0x30)
#define Mentor_USB_EP5_FIFO                  (USB_REG_BASE + 0x34)
#define Mentor_USB_EP6_FIFO                  (USB_REG_BASE + 0x38)

//**************** FIFO SIZE AND ADDRESS ****************
#define Mentor_USB_TX_FIFOS                       (USB_REG_BASE + 0x62)
#define Mentor_USB_RX_FIFOS                       (USB_REG_BASE + 0x63)
#define Mentor_USB_TX_FIFOA                       (USB_REG_BASE + 0x64)
#define Mentor_USB_RX_FIFOA                       (USB_REG_BASE + 0x66)

//**************** DMA REGISTER *********************************
#define MUSB_DMA_BASE                        USB_REG_BASE

#define MUSB_DMA_PAUSE                        (MUSB_DMA_BASE + 0x1000)
#define MUSB_DMA_FRAG_WAIT                       (MUSB_DMA_BASE + 0x1004)
#define MUSB_DMA_INTR_RAW_STATUS                     (MUSB_DMA_BASE + 0x1008)
#define MUSB_DMA_INTR_MASK_STATUS                     (MUSB_DMA_BASE + 0x100C)
#define MUSB_DMA_REQ_STATUS                       (MUSB_DMA_BASE + 0x1010)
#define MUSB_DMA_EN_STATUS                    (MUSB_DMA_BASE + 0x1014)
#define MUSB_DMA_DEBUG_STATUS                    (MUSB_DMA_BASE + 0x1018)

#define MUSB_DMA_CHN_PAUSE(n)                  (MUSB_DMA_BASE + 0x1C00+(n-1)*0x20)  // n(0-15)
#define MUSB_DMA_CHN_CFG(n)                    (MUSB_DMA_BASE + 0x1C04+(n-1)*0x20)  // n(0-15)
#define MUSB_DMA_CHN_INTR(n)                   (MUSB_DMA_BASE + 0x1C08+(n-1)*0x20)  // n(0-15)
#define MUSB_DMA_CHN_ADDR(n)                   (MUSB_DMA_BASE + 0x1C0C+(n-1)*0x20)  // n(1-15)
#define MUSB_DMA_CHN_LEN(n)                    (MUSB_DMA_BASE + 0x1C10+(n-1)*0x20)  // n(0-15)
#define MUSB_DMA_CHN_LLIST_PTR(n)              (MUSB_DMA_BASE + 0x1C14+(n-1)*0x20)  // n(1-15)
#define MUSB_DMA_CHN_BYTE_CNT(n)               (MUSB_DMA_BASE + 0x1C18+(n-1)*0x20)  // n(0-15)
#define MUSB_DMA_CHN_REQ(n)                    (MUSB_DMA_BASE + 0x1C1C+(n-1)*0x20)  // n(0-15)



//#define USB_FIFO_MAX_WORD               128
//#define USB_FIFO_MAX_BYTE               512

#define USB_CTRL_END                    0x203FFFFF
#define USB_CLK_12M                     12000000
#define USB_CLK_48M                     48000000
#endif


#define USB_DEVICE                      0
#define USB_INTERFACE                   1
#define USB_ENDPOINT                    2
#define USB_RECIPIENT_OTHER             3

#define  ENPOINT_HALT                   0

#define  USB_CONNECTTED                  0
#define  USB_POWERED                     1
#define  USB_DEFAULT                     2
#define  USB_ADDRESSED                   3
#define  USB_CONFIGED                    4


#define USB_EP_DIR_OUT                  1
#define USB_EP_DIR_IN                   0


#define USB_PACKET_16           0x10
#define USB_PACKET_32           0x20
#define USB_PACKET_64           0x40
#define USB_PACKET_128          0x80
#define USB_PACKET_256          0x100
#define USB_PACKET_512          0x200
#define USB_PACKET_1024         0x400



// USB endpoind type
typedef enum
{
    USB_EP_TYPE_CONTROL   = 0,
    USB_EP_TYPE_ISO          ,
    USB_EP_TYPE_BULK         ,
    USB_EP_TYPE_INTERRUPT    ,
    USB_EP_TYPE_MAX
}
USB_EP_TYPE_E;


#undef USB_EP1
#undef USB_EP2
#undef USB_EP3
#undef USB_EP4
#undef USB_EP5
#undef USB_EP6
// USB EPx ID
typedef enum
{
    USB_EP0            =  0,
    USB_EP1                ,
    USB_EP2                ,
    USB_EP3                ,
    USB_EP4                ,
    USB_EP5                ,
    USB_EP6                ,
    USB_EP_NUMBER
} USB_EP_NUM_E;




#define USB_INT_SOF                     (BIT_0)
#define USB_INT_SPEND                   (BIT_1)
#define USB_INT_RESUM                   (BIT_2)
#define USB_INT_RST                     (BIT_3)
#define USB_INT_UNPID                   (BIT_4)
#define USB_INT_EPID                    (BIT_5)
#define USB_INT_CHANGE                  (BIT_6)
#define USB_INT_DEVICE                  (BIT_7)
#define USB_INT_EP0                     (BIT_8)
#define USB_INT_EP1                     (BIT_9)
#define USB_INT_EP2                     (BIT_10)
#define USB_INT_EP3                     (BIT_11)
#define USB_INT_EP4                     (BIT_12)


/**----------------------------------------------------------------------------*
**                             Data Prototype                                 **
**----------------------------------------------------------------------------*/

//************************** Core Global Register Prototype *******************/

typedef struct linklist_node_s
{

	unsigned int 	addr;
	unsigned short  frag_len;
	unsigned short  blk_len;
	unsigned int	list_end :1;
	unsigned int	sp :1;
	unsigned int	ioc :1;
	unsigned int	reserved:5;
	unsigned int	data_addr :4;
	unsigned int	pad :20;
#ifndef CONFIG_USB_SPRD_DMA_V0
	unsigned int reserved2;
#endif
} linklist_node_t;


/********************  USB2.0 Protocol Prototype  ****************/

typedef union usb_request_1_tag
{
    struct usb_request_1_map
    {
#if (!defined(_LITTLE_ENDIAN) && !defined(CHIP_ENDIAN_LITTLE))
        volatile unsigned int       direction     :1;
        volatile unsigned int       type          :2;
        volatile unsigned int       recipient     :5;
        volatile unsigned int       brequest      :8;
        volatile unsigned int       value_l       :8;
        volatile unsigned int       value_m       :8;
#else
        volatile unsigned int       recipient     :5;
        volatile unsigned int       type          :2;
        volatile unsigned int 		direction     :1;
        volatile unsigned int       brequest      :8;
        volatile unsigned int       value_l       :8;
        volatile unsigned int       value_m       :8;
#endif
    } mBits ;
    volatile unsigned int dwValue ;
} USB_REQUEST_1_U;

typedef union usb_request_2_tag
{
    struct usb_request_2_map
    {

        volatile unsigned int       index_l       :8;
        volatile unsigned int       index_m       :8;
        volatile unsigned int       length_l      :8;
        volatile unsigned int       length_m      :8;
    } mBits ;
    volatile unsigned int dwValue ;
} USB_REQUEST_2_U;
/*
typedef struct _usb_endp_cfg{
    uint8 ep_address;
    uint8 ep_type;
    uint16 mps;
    uint32 res2;
}USB_EPCfg_T;
*/
#define USB_EPx_NUMBER                  6
/**----------------------------------------------------------------------------*
**                         Local Function Prototype                           **
**----------------------------------------------------------------------------*/

/**----------------------------------------------------------------------------*
**                           Function Prototype                               **
**----------------------------------------------------------------------------*/


/**----------------------------------------------------------------------------*
**                         Compiler Flag                                      **
**----------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif
/**---------------------------------------------------------------------------*/
#endif
// End

