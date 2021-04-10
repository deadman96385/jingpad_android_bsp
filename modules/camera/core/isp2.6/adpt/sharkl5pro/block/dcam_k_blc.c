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
#include "dcam_interface.h"
#include "cam_block.h"

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "BLC: %d %d %s : "\
	fmt, current->pid, __LINE__, __func__

enum {
	_UPDATE_INFO = BIT(0),
};
int dcam_k_blc_block(struct dcam_dev_param *param)
{
	int ret = 0;
	uint32_t idx = param->idx;
	unsigned int val = 0;
	struct dcam_dev_blc_info *p;

	if (param == NULL)
		return -EPERM;
	/* update ? */
	if (!(param->blc.update & _UPDATE_INFO))
		return 0;
	param->blc.update &= (~(_UPDATE_INFO));
	p = &(param->blc.blc_info);
	DCAM_REG_MWR(idx, DCAM_BLC_PARA_R_B, BIT_31,
		(p->bypass) << 31);
	if (p->bypass)
		return 0;

	val = ((p->b & 0x3FFF) << 16) | (p->r & 0x3FFF);
	DCAM_REG_WR(idx, DCAM_BLC_PARA_R_B, val);

	val = ((p->gb & 0x3FFF) << 16) | (p->gr & 0x3FFF);
	DCAM_REG_WR(idx, DCAM_BLC_PARA_G, val);

	return ret;
}

int dcam_k_cfg_blc(struct isp_io_param *param, struct dcam_dev_param *p)
{
	int ret = 0;

	if (NULL == param->property_param || NULL == p) {
		pr_err("fail to get valid param %p %p\n",
			param->property_param, p);
		return -1;
	}
	/* debugfs bypass blc */
	if (g_dcam_bypass[p->idx] & (1 << _E_BLC))
		return 0;

	switch (param->property) {
	case DCAM_PRO_BLC_BLOCK:
		/* online mode not need mutex, response faster
		 * Offline need mutex to protect param
		 */
		if (DCAM_ONLINE_MODE) {
			ret = copy_from_user((void *)&(p->blc.blc_info),
				param->property_param,
				sizeof(p->blc.blc_info));
			if (ret) {
				pr_err("fail to copy from user ret=0x%x\n",
					(unsigned int)ret);
				return -EPERM;
			}
			p->blc.update |= _UPDATE_INFO;
			ret = dcam_k_blc_block(p);
		} else {
			mutex_lock(&p->param_lock);
			ret = copy_from_user((void *)&(p->blc.blc_info),
				param->property_param,
				sizeof(p->blc.blc_info));
			if (ret) {
				mutex_unlock(&p->param_lock);
				pr_err("fail to copy from user ret=0x%x\n",
					(unsigned int)ret);
				return -EPERM;
			}
			p->blc.update |= _UPDATE_INFO;
			mutex_unlock(&p->param_lock);
		}
		break;
	default:
		pr_err("fail to support cmd id:%d\n",
			param->property);
		break;
	}

	return ret;
}
