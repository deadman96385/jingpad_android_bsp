/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _ASM_PAGING_H
#define _ASM_PAGING_H

#define PAGE_PRESENT    0x001
#define PAGE_WRITE      0x002
#define PAGE_USER       0x004
#define PAGE_PWT        0x008
#define PAGE_PCD        0x010
#define PAGE_ACCESSED   0x020
#define PAGE_DIRTY      0x040
#define PAGEDIR_PS      0x080
#define PAGE_PAT        0x080  /* PAT bit for 4KB pages in page table */
#define PAGE_GLOBAL     0x100
#define PAGEDIR_PAT    0x1000  /* PAT bit for large pages, in directory */
#define PAGE_XD         (1ull << 63)

#endif
