/*
 * Copyright (C) 2016 Spreadtrum Communications Inc.
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

#include <linux/uaccess.h>

#include "sprd_mm.h"
#include "sprd_isp_hw.h"
#include "isp_drv.h"

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "PGG: %d %d %s : "\
	fmt, current->pid, __LINE__, __func__

static int isp_k_pgg_block(struct isp_io_param *param, enum isp_id idx)
{
	int ret = 0;
	struct isp_dev_pre_glb_gain_info pgg_info;

	memset(&pgg_info, 0x00, sizeof(pgg_info));

	ret = copy_from_user((void *)&pgg_info,
		param->property_param, sizeof(pgg_info));
	if (ret != 0) {
		pr_err("fail to copy param from user, ret = %d\n", ret);
		return -EPERM;
	}
	ISP_REG_MWR(idx, ISP_PGG_PARAM, BIT_0, pgg_info.bypass);
	if (pgg_info.bypass) {
		isp_dbg_s_ori_byp(SBLK_BYPASS, raw_pgg, idx);
		return 0;
	}

	ISP_REG_MWR(idx, ISP_PGG_PARAM, 0xFFFF00, (pgg_info.gain << 8));

	return ret;
}

int isp_k_cfg_pgg(struct isp_io_param *param,
		struct isp_k_block *isp_k_param, enum isp_id idx)
{
	int ret = 0;

	if (!param) {
		pr_err("fail to get param is null.\n");
		return -EPERM;
	}

	if (!param->property_param) {
		pr_err("fail to get property_param is null.\n");
		return -EPERM;
	}

	switch (param->property) {
	case ISP_PRO_PRE_GLB_GAIN_BLOCK:
		ret = isp_k_pgg_block(param, idx);
		break;
	default:
		pr_err("fail to support cmd id = %d\n", param->property);
		break;
	}

	return ret;
}
