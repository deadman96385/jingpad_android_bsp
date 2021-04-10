/******************************************************************************

  Copyright (C), 2001-2014, Spreatrum Communications Inc.

 ******************************************************************************
  File Name     : usb30_drv.h
  Version       : 1.0 Beta
  Author        : Miao.Zhu
  Created       : 2014/12/25
  Last Modified :
  Description   : This file provides public macroes and declaration of functions.
  Function List : NA
  History       :
  1.Date        : 2014/12/25
    Author      : Miao.Zhu
    Modification: Created file
******************************************************************************/
#ifndef __USB30_DRV_H__
#define __USB30_DRV_H__


#define MAX_RECV_LENGTH 1024 * 4

extern void usb_send(unsigned char *buf, int len);
extern unsigned char usb_get_entry(void);
extern int usb_get_packet(unsigned char* buf, int len);
extern void usb_init(unsigned long usb_reg_base);


#endif
