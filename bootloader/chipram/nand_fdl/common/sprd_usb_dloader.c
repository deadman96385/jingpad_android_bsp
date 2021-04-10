/******************************************************************************

  Copyright (C), 2001-2014, Spreatrum Communications Inc.

 ******************************************************************************
  File Name     : sprd_usb_dloader.c
  Version       : 1.0 Beta
  Author        : Miao.Zhu
  Created       : 2014/12/24
  Last Modified :
  Description   : This file provides USB read/write interfaces
                    some code is borrowed from usb_boot.c
  Function List : NA
  History       :
  1.Date        : 2014/12/24
    Author      : Miao.Zhu
    Modification: Created file
******************************************************************************/
#include <common.h>
#include <fdl_crc.h>
#include <fdl_channel.h>
#include "sprd_usb_drv.h"


static int FDL_UsbOpen (struct FDL_ChannelHandler  *channel,
                        unsigned int baudrate)
{
	return 0;
}

static int FDL_UsbRead (struct FDL_ChannelHandler  *channel,
                        const unsigned char *buf, unsigned int len)
{
	return usb_get_packet((unsigned char *)buf, len);
}

static char FDL_UsbGetChar (struct FDL_ChannelHandler  *channel)
{
	return usb_get_entry();
}

static int FDL_UsbGetSingleChar (struct FDL_ChannelHandler  *channel)
{
	return 0;
}

static int FDL_UsbWrite (struct FDL_ChannelHandler  *channel,
                         const unsigned char *buf, unsigned int len)
{
	usb_send((unsigned char *)buf, len);
	return 0;
}

static int FDL_UsbPutChar (struct FDL_ChannelHandler  *channel,
                           const unsigned char ch)
{
	usb_send((char *)&ch, 1);
	return 0;
}

static int FDL_UsbSetBaudrate (struct FDL_ChannelHandler  *channel,
                               unsigned int baudrate)
{
	return 0;
}

static int FDL_UsbClose (struct FDL_ChannelHandler  *channel)
{
	return 0;
}

struct FDL_ChannelHandler gUSBChannel = {
	FDL_UsbOpen,
	FDL_UsbRead,
	FDL_UsbGetChar,
	FDL_UsbGetSingleChar,
	FDL_UsbWrite,
	FDL_UsbPutChar,
	FDL_UsbSetBaudrate,
	FDL_UsbClose,
	0
};

