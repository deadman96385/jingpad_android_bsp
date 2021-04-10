/**
 * usb_uboot.c - USB Module header file
 *
 * Copyright (C) 2015 Spreadtrum  - http://www.spreadtrum.com
 *
 * Authors: Miao.Zhu <miao.zhu@spreadtrum.com>,
 *
 * SPDX-License-Identifier:     GPL-2.0
 */

#ifndef __USB_UBOOT_H__
#define __USB_UBOOT_H__

extern int
usb_driver_init(unsigned int max_speed);
extern void
usb_driver_exit(void);
extern int
usb_gadget_handle_interrupts(void);

#endif

