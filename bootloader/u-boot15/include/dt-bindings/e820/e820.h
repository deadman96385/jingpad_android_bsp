/*
 * Copyright (C) 2015 Intel, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 *
 */

#ifndef _DT_BINDINGS_E820_H
#define _DT_BINDINGS_E820_H

#define E820_RAM	1
#define E820_RESERVED	2
#define E820_ACPI	3
#define E820_NVS	4
#define E820_UNUSABLE	5

/* E820 entry up to the end of DRAM */
#define E820_SIZE_END_RAM	(0)

#endif

