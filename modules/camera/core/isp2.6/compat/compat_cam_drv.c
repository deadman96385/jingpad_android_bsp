/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
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

#include <linux/compat.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#include <sprd_mm.h>
#include <sprd_isp_hw.h>
#include "sprd_img.h"

#include "compat_cam_drv.h"

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "compat_cam_drv: %d %d %s : "\
	fmt, current->pid, __LINE__, __func__

static int compat_get_isp_io_param(
		struct compat_isp_io_param __user *data32,
		struct isp_io_param __user *data)
{
	int err = 0;
	uint32_t tmp;
	unsigned long parm;

	err |= get_user(tmp, &data32->scene_id);
	err |= put_user(tmp, &data->scene_id);

	err |= get_user(tmp, &data32->sub_block);
	err |= put_user(tmp, &data->sub_block);

	err |= get_user(tmp, &data32->property);
	err |= put_user(tmp, &data->property);

	err |= get_user(parm, &data32->property_param);
	err |= put_user(((void *)parm), &data->property_param);

	return err;
}

static int compat_put_isp_io_param(
		struct compat_isp_io_param __user *data32,
		struct isp_io_param __user *data)
{
	int err = 0;
	uint32_t tmp;
	compat_caddr_t parm;

	err |= get_user(tmp, &data->scene_id);
	err |= put_user(tmp, &data32->scene_id);

	err |= get_user(tmp, &data->sub_block);
	err |= put_user(tmp, &data32->sub_block);

	err |= get_user(tmp, &data->property);
	err |= put_user(tmp, &data32->property);

	err |= get_user(parm, (compat_caddr_t *)&data->property_param);
	err |= put_user(parm, &data32->property_param);

	return err;
}

static int compat_get_lsc_block(
		struct compat_dcam_dev_lsc_info __user *data32,
		struct dcam_dev_lsc_info __user *data)
{
	int err = 0;
	uint32_t tmp;
	unsigned long parm;

	err |= get_user(tmp, &data32->bypass);
	err |= put_user(tmp, &data->bypass);

	err |= get_user(tmp, &data32->update_all);
	err |= put_user(tmp, &data->update_all);

	err |= get_user(tmp, &data32->grid_width);
	err |= put_user(tmp, &data->grid_width);

	err |= get_user(tmp, &data32->grid_x_num);
	err |= put_user(tmp, &data->grid_x_num);

	err |= get_user(tmp, &data32->grid_y_num);
	err |= put_user(tmp, &data->grid_y_num);

	err |= get_user(tmp, &data32->grid_num_t);
	err |= put_user(tmp, &data->grid_num_t);

	err |= get_user(tmp, &data32->gridtab_len);
	err |= put_user(tmp, &data->gridtab_len);

	err |= get_user(tmp, &data32->weight_num);
	err |= put_user(tmp, &data->weight_num);

	err |= get_user(parm, &data32->grid_tab);
	err |= put_user(((void *)parm), &data->grid_tab);

	err |= get_user(parm, &data32->weight_tab);
	err |= put_user(((void *)parm), &data->weight_tab);

	return err;
}

static int compat_put_lsc_block(
		struct compat_dcam_dev_lsc_info __user *data32,
		struct dcam_dev_lsc_info __user *data)
{
	int err = 0;
	uint32_t tmp = 0;

	err |= put_user(tmp, &data32->update_all);

	return err;
}

long compat_sprd_img_ioctl(struct file *file,
	unsigned int cmd, unsigned long param)
{
	long ret = 0L;
	void __user *data32 = compat_ptr(param);
	struct compat_dcam_dev_lsc_info __user *lsc32;
	struct dcam_dev_lsc_info __user *lsc;

	if (!file->f_op || !file->f_op->unlocked_ioctl)
		return -ENOTTY;

	pr_debug("cmd [0x%x][%d]\n", cmd, _IOC_NR(cmd));

	switch (cmd) {
	case COMPAT_SPRD_ISP_IO_CFG_PARAM:
	{
		struct compat_isp_io_param __user *data32;
		struct isp_io_param __user *data;
		uint32_t sub_block = 0;
		uint32_t property = 0;

		data32 = compat_ptr(param);
		data = compat_alloc_user_space(sizeof(struct isp_io_param));
		compat_get_isp_io_param(data32, data);

		get_user(sub_block, &data->sub_block);
		get_user(property, &data->property);

		pr_debug("cfg param, block %d\n", sub_block);
		if (sub_block == DCAM_BLOCK_LSC &&
			property == DCAM_PRO_LSC_BLOCK) {
			get_user(lsc32, &data->property_param);
			lsc = compat_alloc_user_space(
					sizeof(struct dcam_dev_lsc_info) +
					sizeof(struct isp_io_param));
			compat_get_lsc_block(lsc32, lsc);
			put_user((void *)lsc, &data->property_param);
		}

		file->f_op->unlocked_ioctl(file,
					SPRD_ISP_IO_CFG_PARAM,
					(unsigned long)data);
		if (sub_block == DCAM_BLOCK_LSC &&
			property == DCAM_PRO_LSC_BLOCK) {
			compat_put_lsc_block(lsc32, lsc);
		}
		compat_put_isp_io_param(data32, data);
		break;
	}
	default:
		ret = file->f_op->unlocked_ioctl(file, cmd, (unsigned long)data32);
		break;
	}

	return ret;
}
