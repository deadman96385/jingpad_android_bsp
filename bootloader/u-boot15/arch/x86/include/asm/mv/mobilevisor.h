/*
 * Copyright (C) 2015 Intel Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __MOBILEVISOR__
#define __MOBILEVISOR__

#ifdef CONFIG_MOBILEVISOR
int is_x86_mobilevisor(void);
#else
static inline int is_x86_mobilevisor(void)
{
	return 0;
}
#endif

#endif /* __MOBILEVISOR__ */

