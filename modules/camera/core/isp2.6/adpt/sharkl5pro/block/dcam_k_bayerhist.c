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

#include "dcam_reg.h"
#include "dcam_core.h"

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "BAYER_HIST: %d %d %s : "\
	fmt, current->pid, __LINE__, __func__

enum {
	_UPDATE_INFO = BIT(0),
};

int dcam_k_bayerhist_block(struct dcam_dev_param *param)
{
	struct dcam_pipe_dev *dev;
	int ret = 0;
	uint32_t idx = param->idx;
	struct dcam_dev_hist_info *p;


	if (param == NULL)
		return -1;
	/* update ? */
	if (!(param->hist.update & _UPDATE_INFO))
		return 0;
	param->hist.update &= (~(_UPDATE_INFO));
	p = &(param->hist.bayerHist_info);
	DCAM_REG_MWR(idx, DCAM_HIST_FRM_CTRL0, BIT_0, p->hist_bypass);
	if (p->hist_bypass)
		return 0;

	/*
	 * use hardware slow motion feature
	 * TODO: handle skip_num not equal to slowmotion_count - 1
	 */
	dev = param->dev;
	if (p->hist_skip_num > 0 && dev->slowmotion_count) {
		pr_debug("DCAM%u HIST ignore skip_num %u, slowmotion_count %u\n",
			dev->idx, p->hist_skip_num, dev->slowmotion_count);
		p->hist_skip_num = 0;
	}

	DCAM_REG_MWR(idx, DCAM_HIST_FRM_CTRL0, 0xfc,
			((p->hist_skip_num & 0xf) << 4) |
			(p->hist_mul_enable << 3) |
			(p->hist_mode_sel << 2));

	DCAM_REG_MWR(idx, DCAM_BAYER_HIST_START, 0xffffffff,
			((p->bayer_hist_sty & 0x1fff) << 16) |
			(p->bayer_hist_stx & 0x1fff));

	DCAM_REG_MWR(idx, DCAM_BAYER_HIST_END, 0xffffffff,
			((p->bayer_hist_endy & 0x1fff) << 16) |
			(p->bayer_hist_endx & 0x1fff));

	DCAM_REG_MWR(idx, DCAM_HIST_FRM_CTRL1, 0x7,
			(p->hist_initial_clear << 2) |
			(p->hist_skip_num_clr << 1) |
			(p->hist_sgl_start << 0));
	return ret;
}

int dcam_k_bayerhist_bypass(struct dcam_dev_param *p)
{
	int ret = 0;
	uint32_t idx = p->idx;
	uint32_t bypass = 0;

	bypass = p->hist.bayerHist_info.hist_bypass;
	DCAM_REG_MWR(idx, DCAM_HIST_FRM_CTRL0, BIT_0, bypass);

	return ret;
}

int dcam_k_cfg_bayerhist(struct isp_io_param *param,
			struct dcam_dev_param *p)
{
	int ret = 0;

	switch (param->property) {
	case DCAM_PRO_BAYERHIST_BYPASS:
		ret = copy_from_user((void *)&(p->hist.bayerHist_info.hist_bypass),
				param->property_param,
				sizeof(p->hist.bayerHist_info.hist_bypass));
		if (ret) {
			pr_err("fail to copy from user, ret=0x%x\n",
				(unsigned int)ret);
			return -EPERM;
		}
		dcam_k_bayerhist_bypass(p);
		break;
	case DCAM_PRO_BAYERHIST_BLOCK:
		if (DCAM_ONLINE_MODE) {
			ret = copy_from_user((void *)&(p->hist.bayerHist_info),
				param->property_param,
				sizeof(p->hist.bayerHist_info));
			if (ret) {
				pr_err("fail to copy from user, ret=0x%x\n",
					(unsigned int)ret);
				return -EPERM;
			}
			p->hist.update |= _UPDATE_INFO;
			ret = dcam_k_bayerhist_block(p);
		} else {
			mutex_lock(&p->param_lock);
			ret = copy_from_user((void *)&(p->hist.bayerHist_info),
				param->property_param,
				sizeof(p->hist.bayerHist_info));
			if (ret) {
				mutex_unlock(&p->param_lock);
				pr_err("fail to copy from user, ret=0x%x\n",
					(unsigned int)ret);
				return -EPERM;
			}
			p->hist.update |= _UPDATE_INFO;
			mutex_unlock(&p->param_lock);
		}
		break;
	default:
		pr_err("fail to support property %d\n",
			param->property);
		ret = -EINVAL;
		break;
	}

	return ret;
}
