/*
 * Chip depended functions.
 *
 * Copyright (C) 2018 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef _VHA_CHIPDEP_H
#define _VHA_CHIPDEP_H

#include <linux/device.h>
#include <linux/regmap.h>
#include <img_mem_man.h>

int vha_powerdomain_init(struct device *dev);
int vha_powerdomain_setup(void);
int vha_powerdomain_unsetup(void);
int vha_clockdomain_init(struct device *dev);
int vha_clock_init(struct device *dev);
int vha_clockdomain_select(struct device *dev);
int vha_clockdomain_setup(void);
int vha_clockdomain_unsetup(void);
int vha_apll_rate_set(struct device *dev);
u64 vha_get_chip_dmamask(void);
struct regmap *vha_get_ai_apb_regs(struct device *dev);

/* qos for powervr */
int vha_restore_qos(struct device *dev);
int vha_ai_parse_qos_dt(struct device *dev);
int vha_set_qos(struct device *dev);

#endif /* _VHA_CHIPDEP_H */
