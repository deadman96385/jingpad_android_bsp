/*
 * Copyright (C) 2017-2018 Spreadtrum Communications Inc.
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
#include <sprd_mm.h>
#include "sprd_isp_hw.h"

#include "isp_reg.h"
#include "cam_types.h"
#include "cam_block.h"

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "YGAMMA: %d %d %s : "\
	fmt, current->pid, __LINE__, __func__


static int isp_k_ygamma_block(struct isp_io_param *param,
	struct isp_k_block *isp_k_param, uint32_t idx)
{
	int ret = 0;
	uint32_t i, val;
	uint32_t buf_sel, ybuf_addr;
	struct isp_dev_ygamma_info ygamma_info;

	ret = copy_from_user((void *)&ygamma_info,
			param->property_param,
			sizeof(ygamma_info));
	if (ret != 0) {
		pr_err("fail to copy from user, ret = %d\n", ret);
		return ret;
	}
	if (g_isp_bypass[idx] & (1 << _EISP_GAMY))
		ygamma_info.bypass = 1;
	isp_k_param->ygamma_bypass = ygamma_info.bypass;
	if (ygamma_info.bypass)
		return 0;

	buf_sel = 0;
	ybuf_addr = ISP_YGAMMA_BUF0;
	ISP_REG_MWR(idx, ISP_YGAMMA_PARAM, BIT_1, buf_sel << 1);

	for (i = 0; i < ISP_YUV_GAMMA_NUM - 1; i++) {
		val = (ygamma_info.gain[i] & 0xFF);
		ISP_REG_WR(idx, ybuf_addr + i * 4, val);
	}

	return ret;
}

int isp_k_cfg_ygamma(struct isp_io_param *param,
	struct isp_k_block *isp_k_param, uint32_t idx)
{
	int ret = 0;

	switch (param->property) {
	case ISP_PRO_YGAMMA_BLOCK:
		ret = isp_k_ygamma_block(param, isp_k_param, idx);
		break;
	default:
		pr_err("fail to support cmd id = %d\n",
			param->property);
		break;
	}

	return ret;
}
