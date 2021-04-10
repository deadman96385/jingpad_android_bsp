/*
 * Copyright (C) 2015, Intel Corporation
 *
 * SPDX-License-Identifier:     GPL-2.0+
 *
 */

#ifndef _X86_BASEIA_CPU_H_
#define _X86_BASEIA_CPU_H_

int cpu_x86_baseia_bind(struct udevice *dev);
int cpu_x86_baseia_probe(struct udevice *dev);
int baseia_get_info(struct udevice *dev, struct cpu_info *info);

#endif /* _X86_BASEIA_CPU_H_ */
