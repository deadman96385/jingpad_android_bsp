/*
 * qos configure for ROC1.
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

#include <linux/err.h>
#include <linux/of.h>
#include <linux/mfd/syscon.h>
#include <linux/regmap.h>
#include <linux/device.h>
#include <dt-bindings/soc/sprd,roc1-regs.h>
#include <dt-bindings/soc/sprd,roc1-mask.h>

#include "vha_chipdep.h"

#define QOS_BITS_MASK   (0xf)

struct ai_qos {
	unsigned int arqos_threshold;
	unsigned int awqos_threshold;
	unsigned int arqos_powervr;
	unsigned int awqos_powervr;
};
static struct ai_qos vha_ai_qos;

static inline unsigned int vha_get_mask_shift(unsigned int mask)
{
	unsigned int count = 0;

	while (!(mask & 1)) {
		mask = mask >> 1;
		count++;
	}

	return count;
}

int vha_set_qos(struct device *dev)
{
	unsigned int val, mask;
	struct regmap *ai_apb_regs;
	unsigned int arqos_threshold_shift =
		vha_get_mask_shift(MASK_AI_APB_ARQOS_THRESHOLD_AI_MAIN_MTX);
	unsigned int awqos_threshold_shift =
		vha_get_mask_shift(MASK_AI_APB_AWQOS_THRESHOLD_AI_MAIN_MTX);
	unsigned int arqos_powervr_shift =
		vha_get_mask_shift(MASK_AI_APB_ARQOS_POWERVR_SW_AI_MAIN_MTX);
	unsigned int awqos_powervr_shift =
		vha_get_mask_shift(MASK_AI_APB_AWQOS_POWERVR_SW_AI_MAIN_MTX);

	ai_apb_regs = vha_get_ai_apb_regs(dev);
	if (IS_ERR(ai_apb_regs)) {
		pr_warn("failed to get ai_apb_regs\n");
		return -EINVAL;
	}

	val = (vha_ai_qos.arqos_threshold << arqos_threshold_shift)
		| (vha_ai_qos.awqos_threshold << awqos_threshold_shift)
		| (vha_ai_qos.arqos_powervr << arqos_powervr_shift)
		| (vha_ai_qos.awqos_powervr << awqos_powervr_shift)
		| MASK_AI_APB_QOS_POWERVR_SEL_SW_AI_MAIN_MTX;

	mask = (MASK_AI_APB_ARQOS_THRESHOLD_AI_MAIN_MTX
                | MASK_AI_APB_AWQOS_THRESHOLD_AI_MAIN_MTX
                | MASK_AI_APB_ARQOS_POWERVR_SW_AI_MAIN_MTX
                | MASK_AI_APB_AWQOS_POWERVR_SW_AI_MAIN_MTX
		| MASK_AI_APB_QOS_POWERVR_SEL_SW_AI_MAIN_MTX);

	regmap_update_bits(ai_apb_regs, REG_AI_APB_AI_QOS_CTRL, mask, val);

	return 0;
}

int vha_restore_qos(struct device *dev)
{
	vha_set_qos(dev);

	return 0;
}

int vha_ai_parse_qos_dt(struct device *dev)
{
	struct device_node *qos_node = NULL;
	struct device_node *vha_node = dev->of_node;
	unsigned char val;

	qos_node = of_parse_phandle(vha_node, "sprd,qos", 0);
	if (qos_node) {
		if (of_property_read_u8(qos_node, "arqos-threshold-ai", &val)) {
			pr_warn("arqos-threshold-ai reading fail.\n");
			val = 0xf;
		}

		vha_ai_qos.arqos_threshold = ((unsigned int)val) & QOS_BITS_MASK;

		if (of_property_read_u8(qos_node, "awqos-threshold-ai", &val)) {
			pr_warn("awqos-threshold-ai reading fail.\n");
			val = 0xf;
		}

		vha_ai_qos.awqos_threshold = ((unsigned int)val) & QOS_BITS_MASK;

		if (of_property_read_u8(qos_node, "arqos-powervr", &val)) {
			pr_warn("arqos-powervr reading fail.\n");
			val = 0x6;
		}

		vha_ai_qos.arqos_powervr = ((unsigned int)val) & QOS_BITS_MASK;

		if (of_property_read_u8(qos_node, "awqos-powervr", &val)) {
			pr_warn("awqos-powervr reading fail.\n");
			val = 0x6;
		}

		vha_ai_qos.awqos_powervr = ((unsigned int)val) & QOS_BITS_MASK;

	} else {
		pr_warn("%s fail to get ai_qos node\n", __func__);
		vha_ai_qos.arqos_threshold = 0xf;
		vha_ai_qos.awqos_threshold = 0xf;
		vha_ai_qos.arqos_powervr = 0x6;
		vha_ai_qos.awqos_powervr = 0x6;
	}


	return 0;
}

