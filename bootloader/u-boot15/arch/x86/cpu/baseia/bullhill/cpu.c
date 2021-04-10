/*
 * Copyright (C) 2015 Intel, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 *
 */

#include <common.h>
#include <cpu.h>
#include <dm.h>
#include <asm/cpu.h>
#include "../cpu.h"

static const struct cpu_ops cpu_x86_baseia_bullhill_ops = {
	.get_desc       = x86_cpu_get_desc,
	.get_info       = baseia_get_info,
};

static const struct udevice_id cpu_x86_baseia_ids[] = {
	{ .compatible = "intel,bullhill" },
	{ }
};

U_BOOT_DRIVER(cpu_x86_baseia_drv) = {
	.name           = "cpu_x86_bullhill",
	.id             = UCLASS_CPU,
	.of_match       = cpu_x86_baseia_ids,
	.bind           = cpu_x86_baseia_bind,
	.probe          = cpu_x86_baseia_probe,
	.ops            = &cpu_x86_baseia_bullhill_ops,
};
