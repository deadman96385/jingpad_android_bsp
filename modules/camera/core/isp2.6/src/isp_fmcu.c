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

#include <linux/types.h>
#include <linux/delay.h>
#include <linux/sprd_iommu.h>
#include <linux/sprd_ion.h>
#include <sprd_mm.h>

#include "cam_types.h"

#include "isp_reg.h"
#include "isp_fmcu.h"
#include "cam_hw.h"
#include "defines.h"

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "ISP_FMCU %d: %d %s:" \
	fmt, current->pid, __LINE__, __func__


static int isp_fmcu_push_cmd(struct isp_fmcu_ctx_desc *fmcu_ctx,
				uint32_t addr, uint32_t cmd)
{
	int ret = 0;
	uint32_t *ptr;

	if (!fmcu_ctx) {
		pr_err("fail to get fmcu_ctx pointer\n");
		return -EFAULT;
	}
	if (fmcu_ctx->cmdq_pos[fmcu_ctx->cur_buf_id]
		> (fmcu_ctx->cmdq_size / sizeof(uint32_t))) {
		pr_err("fail to get fmcu%d cmdq, overflow.\n", fmcu_ctx->fid);
		return -EFAULT;
	}

	ptr = fmcu_ctx->cmd_buf[fmcu_ctx->cur_buf_id]
				+ fmcu_ctx->cmdq_pos[fmcu_ctx->cur_buf_id];
	*ptr++ = cmd;
	*ptr++ = addr;
	fmcu_ctx->cmdq_pos[fmcu_ctx->cur_buf_id] += 2;

	return ret;
}

static int isp_fmcu_cmd_ready(struct isp_fmcu_ctx_desc *fmcu_ctx)
{
	int ret = 0;
	int cmd_num;
	unsigned long base;

	if (!fmcu_ctx) {
		pr_err("fail to get fmcu_ctx pointer\n");
		return -EFAULT;
	}
	pr_debug("set fmcu cmd ready%d\n", fmcu_ctx->fid);

	if (fmcu_ctx->fid == 0)
		base =  ISP_FMCU0_BASE;
	else
		base =  ISP_FMCU1_BASE;

	if (fmcu_ctx->cmdq_pos[fmcu_ctx->cur_buf_id]
	> (fmcu_ctx->cmdq_size / sizeof(uint32_t))) {
		pr_err("fail to get fmcu%d cmdq, overflow.\n", fmcu_ctx->fid);
		return -EFAULT;
	}
	cmd_num = (int) fmcu_ctx->cmdq_pos[fmcu_ctx->cur_buf_id] / 2;

#if 0
	{
		unsigned int i = 0;
		unsigned long addr =
			(unsigned long)fmcu_ctx->cmd_buf[fmcu_ctx->cur_buf_id];
		pr_info("fmcu %d  cmd num %d\n",
				(int)fmcu_ctx->fid,  cmd_num);

		for (i = 0; i <= cmd_num; i += 2) {
			pr_info("a:0x%08x c: 0x%08x | a:0x%08x c: 0x%08x\n",
				*(uint32_t *)(addr + 4),
				*(uint32_t *)(addr),
				*(uint32_t *)(addr + 12),
				*(uint32_t *)(addr + 8));
			addr += 16;
		}
	}
#endif
	ISP_HREG_WR(base + ISP_FMCU_DDR_ADDR,
				fmcu_ctx->hw_addr[fmcu_ctx->cur_buf_id]);
	ISP_HREG_MWR(base + ISP_FMCU_CTRL, 0xFFFF0000, cmd_num << 16);
	ISP_HREG_WR(base + ISP_FMCU_CMD_READY, 1);

	pr_debug("fmcu%d start done, cmdq len %d\n",
		fmcu_ctx->fid,
		(uint32_t)fmcu_ctx->cmdq_pos[fmcu_ctx->cur_buf_id] * 4);

	fmcu_ctx->cur_buf_id = !(fmcu_ctx->cur_buf_id);
	return ret;
}

static int isp_fmcu_start(struct isp_fmcu_ctx_desc *fmcu_ctx)
{
	int ret = 0;
	int cmd_num;
	unsigned long base;

	if (!fmcu_ctx) {
		pr_err("fail to get fmcu_ctx pointer\n");
		return -EFAULT;
	}
	pr_debug("start fmcu%d\n", fmcu_ctx->fid);

	if (fmcu_ctx->fid == 0)
		base =  ISP_FMCU0_BASE;
	else
		base =  ISP_FMCU1_BASE;

	if (fmcu_ctx->cmdq_pos[fmcu_ctx->cur_buf_id]
	> (fmcu_ctx->cmdq_size / sizeof(uint32_t))) {
		pr_err("fail to get fmcu%d cmdq, overflow.\n", fmcu_ctx->fid);
		return -EFAULT;
	}
	cmd_num = (int) fmcu_ctx->cmdq_pos[fmcu_ctx->cur_buf_id] / 2;

#if 0
	{
		unsigned int i = 0;
		unsigned long addr =
			(unsigned long)fmcu_ctx->cmd_buf[fmcu_ctx->cur_buf_id];
		pr_info("fmcu %d  cmd num %d\n",
				(int)fmcu_ctx->fid,  cmd_num);

		for (i = 0; i <= cmd_num; i += 2) {
			pr_info("a:0x%08x c: 0x%08x | a:0x%08x c: 0x%08x\n",
				*(uint32_t *)(addr + 4),
				*(uint32_t *)(addr),
				*(uint32_t *)(addr + 12),
				*(uint32_t *)(addr + 8));
			addr += 16;
		}
	}
#endif

/*
 * FLUSH_DCACHE(fmcu_ctx->cmd_buf[fmcu_ctx->cur_buf_id],
 * fmcu_ctx->cmdq_pos[fmcu_ctx->cur_buf_id] * sizeof(uint32_t));
 * sprd_ion_flush_dcache_area_wrapper(fmcu_ctx->cmd_buf[fmcu_ctx->cur_buf_id],
 * fmcu_ctx->cmdq_pos[fmcu_ctx->cur_buf_id] * sizeof(uint32_t));
 */

	ISP_HREG_WR(base + ISP_FMCU_DDR_ADDR,
			fmcu_ctx->hw_addr[fmcu_ctx->cur_buf_id]);
	ISP_HREG_MWR(base + ISP_FMCU_CTRL, 0xFFFF0000, cmd_num << 16);
	ISP_HREG_WR(base + ISP_FMCU_ISP_REG_REGION, ISP_OFFSET_RANGE);
	ISP_HREG_WR(base + ISP_FMCU_START, 1);

	pr_debug("fmcu%d start done, cmdq len %d\n",
		fmcu_ctx->fid,
		(uint32_t)fmcu_ctx->cmdq_pos[fmcu_ctx->cur_buf_id] * 4);

	fmcu_ctx->cur_buf_id = !(fmcu_ctx->cur_buf_id);
	return ret;
}


static int isp_fmcu_ctx_reset(struct isp_fmcu_ctx_desc *fmcu_ctx)
{
	int ret = 0;

	if (!fmcu_ctx) {
		pr_err("fail to get fmcu_ctx pointer\n");
		return -EFAULT;
	}

	pr_debug("Enter\n");

	fmcu_ctx->cmdq_pos[fmcu_ctx->cur_buf_id] = 0;
	memset(fmcu_ctx->cmd_buf[fmcu_ctx->cur_buf_id], 0, fmcu_ctx->cmdq_size);

	pr_debug("Done\n");
	return ret;
}

static int isp_fmcu_ctx_init(struct isp_fmcu_ctx_desc *fmcu_ctx)
{
	int ret = 0;
	int i;
	int iommu_enable = 0;
	struct camera_buf *ion_buf = NULL;

	if (!fmcu_ctx) {
		pr_err("fail to get fmcu_ctx pointer\n");
		return -EFAULT;
	}
	pr_debug("Enter\n");


	fmcu_ctx->cmdq_size = ISP_FMCU_CMDQ_SIZE;
	fmcu_ctx->lock = __SPIN_LOCK_UNLOCKED(&fmcu_ctx->lock);

	/*alloc cmd queue buffer*/
	for (i = 0; i < MAX_BUF; i++) {
		ion_buf = &fmcu_ctx->ion_pool[i];
		memset(ion_buf, 0, sizeof(fmcu_ctx->ion_pool[i]));
		sprintf(ion_buf->name, "isp_fmcu_ctx%d", i);

		if (get_iommu_status(CAM_IOMMUDEV_ISP) == 0) {
			pr_debug("isp iommu enable\n");
			iommu_enable = 1;
		} else {
			pr_debug("isp iommu disable\n");
			iommu_enable = 0;
		}
		ret = cambuf_alloc(ion_buf,
				fmcu_ctx->cmdq_size, 0, iommu_enable);
		if (ret) {
			pr_err("fail to get fmcu buffer\n");
			ret = -EFAULT;
			goto err_alloc_fmcu;
		}

		ret = cambuf_kmap(ion_buf);
		if (ret) {
			pr_err("fail to kmap fmcu buffer\n");
			ret = -EFAULT;
			goto err_kmap_fmcu;
		}
		ret = cambuf_iommu_map(ion_buf, CAM_IOMMUDEV_ISP);
		if (ret) {
			pr_err("fail to map fmcu buffer\n");
			ret = -EFAULT;
			goto err_hwmap_fmcu;
		}
		fmcu_ctx->cmd_buf[i] = (uint32_t *)ion_buf->addr_k[0];
		fmcu_ctx->hw_addr[i] = ion_buf->iova[0];
		fmcu_ctx->cmdq_pos[i] = 0;
		pr_info("fmcu%d cmd buf hw_addr:0x%lx, sw_addr:%p, size:%zd\n",
			i, fmcu_ctx->hw_addr[i], fmcu_ctx->cmd_buf[i],
			ion_buf->size[0]);
	}

	return 0;

err_hwmap_fmcu:
	for (i = 0; i < MAX_BUF; i++) {
		ion_buf = &fmcu_ctx->ion_pool[i];
		if (ion_buf)
			cambuf_iommu_unmap(ion_buf);
	}
err_kmap_fmcu:
	for (i = 0; i < MAX_BUF; i++) {
		ion_buf = &fmcu_ctx->ion_pool[i];
		if (ion_buf)
			cambuf_kunmap(ion_buf);
	}
err_alloc_fmcu:
	for (i = 0; i < MAX_BUF; i++) {
		ion_buf = &fmcu_ctx->ion_pool[i];
		if (ion_buf)
			cambuf_free(ion_buf);
	}
	pr_err("fail to init fmcu%d.\n", fmcu_ctx->fid);
	return ret;
}

static int isp_fmcu_ctx_deinit(struct isp_fmcu_ctx_desc *fmcu_ctx)
{
	int ret = 0;
	int i;
	struct camera_buf *ion_buf = NULL;

	if (!fmcu_ctx) {
		pr_err("fail to get fmcu_ctx pointer\n");
		return -EFAULT;
	}

	pr_debug("Enter\n");
	for (i = 0; i < MAX_BUF; i++) {
		ion_buf = &fmcu_ctx->ion_pool[i];
		cambuf_iommu_unmap(ion_buf);
		cambuf_kunmap(ion_buf);
		cambuf_free(ion_buf);
	}

	pr_debug("Done\n");
	return ret;
}


struct isp_fmcu_ops fmcu_ops = {
	.ctx_init = isp_fmcu_ctx_init,
	.ctx_deinit = isp_fmcu_ctx_deinit,
	.ctx_reset = isp_fmcu_ctx_reset,
	.push_cmdq = isp_fmcu_push_cmd,
	.hw_start = isp_fmcu_start,
	.cmd_ready = isp_fmcu_cmd_ready,
};

static struct isp_fmcu_ctx_desc s_fmcu_desc[ISP_FMCU_NUM] = {
	{
		.fid = ISP_FMCU_0,
		.ops = &fmcu_ops,
		.cur_buf_id = PING,
	},
	{
		.fid = ISP_FMCU_1,
		.ops = &fmcu_ops,
		.cur_buf_id = PING,
	},
};

struct isp_fmcu_ctx_desc *get_isp_fmcu_ctx_desc(void *arg)
{
	int i;
	struct isp_fmcu_ctx_desc *fmcu = NULL;
	struct cam_hw_info *hw = NULL;

	if (!arg) {
		pr_err("fail to get valid arg\n");
		return NULL;
	}

	hw = (struct cam_hw_info *)arg;
	for (i = 0; i < ISP_FMCU_NUM; i++) {
		if (atomic_inc_return(&s_fmcu_desc[i].user_cnt) == 1) {
			if (hw->hw_ops.core_ops.fmcu_valid_get(s_fmcu_desc[i].fid)) {
				fmcu = &s_fmcu_desc[i];
				pr_info("fmcu %d , %p\n", fmcu->fid, fmcu);
				break;
			}
		}
		atomic_dec(&s_fmcu_desc[i].user_cnt);
	}

	return fmcu;
}

int put_isp_fmcu_ctx_desc(struct isp_fmcu_ctx_desc *fmcu)
{
	int i;

	pr_info("fmcu %d. %p\n", fmcu->fid, fmcu);
	for (i = 0; i < ISP_FMCU_NUM; i++) {
		if (fmcu == &s_fmcu_desc[i]) {
			fmcu = NULL;
			atomic_dec(&s_fmcu_desc[i].user_cnt);
			break;
		}
	}

	if (fmcu != NULL)
		pr_err("fail to match original ptr %p\n", fmcu);

	return 0;
}
