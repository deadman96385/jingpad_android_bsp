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
#include <sprd_mm.h>
#include <linux/sprd_iommu.h>
#include <linux/sprd_ion.h>

#include "isp_reg.h"
#include "isp_core.h"
#include "isp_cfg.h"

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "ISP_CFG: %d: %d %s:" \
	fmt, current->pid, __LINE__, __func__

unsigned long cfg_cmd_addr_reg[ISP_CONTEXT_HW_NUM] = {
	ISP_CFG_PRE0_CMD_ADDR,
	ISP_CFG_CAP0_CMD_ADDR,
	ISP_CFG_PRE1_CMD_ADDR,
	ISP_CFG_CAP1_CMD_ADDR
};

unsigned long isp_cfg_ctx_addr[ISP_CONTEXT_SW_NUM] = { 0 };

static DEFINE_MUTEX(buf_mutex);

struct isp_cfg_map_sector {
	uint32_t offset;
	uint32_t size;
};

/* s_map_sec_cnt/s_map_sectors only configure once
 * due to ISP_CFG_MAP[] is static and fixed
 */
static uint32_t s_map_sec_cnt;
static struct isp_cfg_map_sector s_map_sectors[ISP_CFG_MAP_MAX];

struct isp_dev_cfg_info {
	uint32_t bypass;
	uint32_t tm_bypass;
	uint32_t sdw_mode;
	uint32_t num_of_mod;
	uint32_t *isp_cfg_map;

	uint32_t cfg_main_sel;
	uint32_t bp_pre0_pixel_rdy;
	uint32_t bp_pre1_pixel_rdy;
	uint32_t bp_cap0_pixel_rdy;
	uint32_t bp_cap1_pixel_rdy;

	/* 0: cfg trigger start. 1: fmcu trigger start */
	uint32_t pre0_cmd_ready_mode;
	uint32_t pre1_cmd_ready_mode;
	uint32_t cap0_cmd_ready_mode;
	uint32_t cap1_cmd_ready_mode;

	uint32_t tm_set_number;
	uint32_t cap0_th;
	uint32_t cap1_th;
} s_cfg_settings = {
	0, 1, 1, 0, NULL,
	0, 1, 1, 1, 1,
	0, 0, 0, 0,
	0, 0, 0
};

int debug_show_ctx_reg_buf(void *param)
{
	struct seq_file *s = (struct seq_file *)param;
	uint32_t ctx_id = *(uint32_t *)s->private;
	uint32_t i, item, start, count;
	uint32_t addr;
	unsigned long datap;
	uint32_t cfg_map_size = 0;
	uint32_t *cfg_map = NULL;

	mutex_lock(&buf_mutex);
	datap =  isp_cfg_ctx_addr[ctx_id];
	cfg_map_size = s_cfg_settings.num_of_mod;
	cfg_map = s_cfg_settings.isp_cfg_map;
	if (datap == 0UL) {
		mutex_unlock(&buf_mutex);
		seq_printf(s,
			"----ctx %d cfg buf freed.---\n", ctx_id);
		return 0;
	}

	seq_printf(s,
		"dump regsigters buf of ISP context %d - kaddr: 0x%lx\n",
		ctx_id, datap);

	for (i = 0; i < cfg_map_size; i++) {
		seq_puts(s, "---------------\n");
		item = cfg_map[i];
		start = item & 0xffff;
		count = (item >> 16) & 0xffff;
		for (addr = start; addr < (start + count); addr += 4)
			seq_printf(s, "%04x:  %08x\n",
				addr,  *(uint32_t *)(datap + addr));
	}
	mutex_unlock(&buf_mutex);
	seq_puts(s, "------------------------\n");
	return 0;
}


static void cctx_init_page_buf_addr(
				struct isp_cfg_ctx_desc *cfg_ctx,
				void *sw_addr,
				unsigned long hw_addr)
{
	unsigned long offset;
	struct isp_cfg_buf *cfg_buf;
	int  c_id, bid;

	for (c_id = 0; c_id < ISP_CONTEXT_HW_NUM; c_id++) {
		offset = c_id * ISP_CFG_BUF_SIZE;
		cfg_buf = &cfg_ctx->cfg_buf[c_id];
		bid = CFG_BUF_HW;
		cfg_buf->reg_buf[bid].sw_addr = sw_addr + offset;
		cfg_buf->reg_buf[bid].hw_addr = hw_addr + offset;
		pr_debug("isp ctx %d  buf %d: sw=%p, hw:0x%lx\n",
			c_id, bid, cfg_buf->reg_buf[bid].sw_addr,
			cfg_buf->reg_buf[bid].hw_addr);
	}
}

static void cctx_init_sw_page_buf_addr(
				struct isp_cfg_ctx_desc *cfg_ctx,
				void *sw_addr)
{
	unsigned long offset;
	struct isp_cfg_buf *cfg_buf;
	int  c_id, bid;

	for (c_id = 0; c_id < ISP_CONTEXT_SW_NUM; c_id++) {
		offset = c_id * ISP_CFG_BUF_SIZE;
		cfg_buf = &cfg_ctx->cfg_buf[c_id];
		bid = CFG_BUF_SW;
		cfg_buf->reg_buf[bid].sw_addr = sw_addr + offset;
		cfg_buf->reg_buf[bid].hw_addr = 0UL;
		pr_debug("isp ctx %d  buf %d: sw=%p, hw:0x%lx\n",
			c_id, bid, cfg_buf->reg_buf[bid].sw_addr,
			cfg_buf->reg_buf[bid].hw_addr);
	}
}

static void cctx_deinit_page_buf_addr(struct isp_cfg_ctx_desc *cfg_ctx)
{
	struct isp_cfg_buf *cfg_buf;
	int c_id, bid;

	for (c_id = 0; c_id < ISP_CONTEXT_SW_NUM; c_id++) {
		cfg_buf = &cfg_ctx->cfg_buf[c_id];
		for (bid = 0; bid < CFG_BUF_NUM; bid++) {
			cfg_buf->reg_buf[bid].sw_addr = NULL;
			cfg_buf->reg_buf[bid].hw_addr = 0UL;
		}
	}
}

static void cctx_init_regbuf_addr(struct isp_cfg_ctx_desc *cfg_ctx)
{
	struct isp_cfg_buf *cfg_buf;
	struct regfile_buf_info *cur_regbuf_p;
	enum cfg_buf_id cur_regbuf_id;
	int c_id;

	/*
	 * Init context reg buf for each isp context.
	 * Each context has two buf, shadow and work.
	 * Using shadow buf as initial buf.
	 * @isp_cfg_ctx_addr will be used when using ISP_BASE_ADDR.
	 */
	for (c_id = 0; c_id < ISP_CONTEXT_SW_NUM; c_id++) {
		cfg_buf = &cfg_ctx->cfg_buf[c_id];
		cfg_buf->cur_buf_id = cur_regbuf_id = CFG_BUF_SW;
		cur_regbuf_p = &cfg_buf->reg_buf[cur_regbuf_id];
		isp_cfg_ctx_addr[c_id] =
				(unsigned long)cur_regbuf_p->sw_addr;
		pr_debug("init cctx_buf[%d] sw=%p, hw=0x%lx\n",
					c_id, cur_regbuf_p->sw_addr,
					cur_regbuf_p->hw_addr);
	}

}

static void cctx_deinit_regbuf_addr(struct isp_cfg_ctx_desc *cfg_ctx)
{
	int c_id;

	mutex_lock(&buf_mutex);
	for (c_id = 0; c_id < ISP_CONTEXT_SW_NUM; c_id++)
		isp_cfg_ctx_addr[c_id] = 0UL;
	mutex_unlock(&buf_mutex);
}

static void cctx_page_buf_aligned(struct isp_cfg_ctx_desc *cfg_ctx,
					void **sw_addr, unsigned long *hw_addr)
{
	void *kaddr;
	unsigned long ofst_align = 0;
	unsigned long iova, aligned_iova;
	struct camera_buf *ion_buf = &cfg_ctx->ion_pool;

	kaddr = (void *)ion_buf->addr_k[0];
	iova = ion_buf->iova[0];

	if (!IS_ERR_OR_NULL(kaddr) && iova) {
		if (IS_ALIGNED(iova, ALIGN_PADDING_SIZE)) {
			*hw_addr = iova;
			*sw_addr = kaddr;
		} else {
			aligned_iova = ALIGN(iova, ALIGN_PADDING_SIZE);
			ofst_align = aligned_iova - iova;
			*sw_addr = kaddr + ofst_align;
			*hw_addr = aligned_iova;
		}
		pr_debug("aligned sw: %p, hw: 0x%lx, ofs: 0x%lx",
					*sw_addr, *hw_addr, ofst_align);
	}
}


static int cctx_buf_init(struct isp_cfg_ctx_desc *cfg_ctx)
{
	int ret = 0;
	int iommu_enable = 0;
	size_t size;
	void *sw_addr = NULL;
	unsigned long hw_addr = 0;
	struct camera_buf *ion_buf = NULL;
	struct camera_buf *ion_buf_cached = NULL;

	/*alloc cfg context buffer*/
	ion_buf = &cfg_ctx->ion_pool;
	memset(ion_buf, 0, sizeof(cfg_ctx->ion_pool));
	sprintf(ion_buf->name, "isp_cfg_ctx");

	if (get_iommu_status(CAM_IOMMUDEV_ISP) == 0) {
		pr_debug("isp iommu enable\n");
		iommu_enable = 1;
	} else {
		pr_debug("isp iommu disable\n");
		iommu_enable = 0;
	}
	size = ISP_CFG_BUF_SIZE_HW_PADDING;
	ret = cambuf_alloc(ion_buf, size, 0, iommu_enable);
	if (ret) {
		pr_err("fail to get cfg buffer\n");
		ret = -EFAULT;
		goto err_alloc_cfg;
	}

	ret = cambuf_kmap(ion_buf);
	if (ret) {
		pr_err("fail to kmap cfg buffer\n");
		ret = -EFAULT;
		goto err_kmap_cfg;
	}

	ret = cambuf_iommu_map(ion_buf, CAM_IOMMUDEV_ISP);
	if (ret) {
		pr_err("fail to map cfg buffer\n");
		ret = -EFAULT;
		goto err_hwmap_cfg;
	}

	/*alloc cfg sw context buffer*/
	ion_buf_cached = &cfg_ctx->ion_pool_cached;
	memset(ion_buf_cached, 0, sizeof(cfg_ctx->ion_pool_cached));
	sprintf(ion_buf_cached->name, "isp_cfg_swctx");

	size = ISP_CFG_BUF_SIZE_SW_ALL;
	ret = cambuf_alloc(ion_buf_cached, size, 0, iommu_enable | CAM_BUF_CAHCED);
	if (ret) {
		pr_err("fail to get cfg buffer\n");
		ret = -EFAULT;
		goto err_alloc_cfg1;
	}

	ret = cambuf_kmap(ion_buf_cached);
	if (ret) {
		pr_err("fail to kmap cfg buffer\n");
		ret = -EFAULT;
		goto err_kmap_cfg1;
	}


	cctx_page_buf_aligned(cfg_ctx, &sw_addr, &hw_addr);
	cctx_init_page_buf_addr(cfg_ctx, sw_addr, hw_addr);
	cctx_init_sw_page_buf_addr(cfg_ctx, (void *)ion_buf_cached->addr_k[0]);
	cctx_init_regbuf_addr(cfg_ctx);

	pr_debug("cmd sw: %p, hw: 0x%lx, size:0x%x\n",
			sw_addr, hw_addr, (int)ion_buf->size[0]);
	pr_debug("cmd1 sw: 0x%lx, size:0x%x\n",
			ion_buf_cached->addr_k[0], (int)ion_buf_cached->size[0]);

	return 0;

err_kmap_cfg1:
	cambuf_free(ion_buf_cached);
err_alloc_cfg1:
	cambuf_iommu_unmap(ion_buf);
err_hwmap_cfg:
	cambuf_kunmap(ion_buf);
err_kmap_cfg:
	cambuf_free(ion_buf);
err_alloc_cfg:
	return ret;
}


static int cctx_buf_deinit(struct isp_cfg_ctx_desc *cfg_ctx)
{
	struct camera_buf *ion_buf = NULL;

	ion_buf = &cfg_ctx->ion_pool;

	cctx_deinit_regbuf_addr(cfg_ctx);
	cctx_deinit_page_buf_addr(cfg_ctx);

	cambuf_iommu_unmap(ion_buf);
	cambuf_kunmap(ion_buf);
	cambuf_free(ion_buf);

	ion_buf = &cfg_ctx->ion_pool_cached;
	cambuf_kunmap(ion_buf);
	cambuf_free(ion_buf);

	return 0;
}

static int isp_cfg_reset_ctxbuf(
		struct isp_cfg_ctx_desc *cfg_ctx,
		enum isp_context_id ctx_id)
{
	void *shadow_buf_vaddr = NULL;

	if (!cfg_ctx) {
		pr_err("fail to get cfg_ctx pointer\n");
		return -EFAULT;
	}
	pr_debug("Enter\n");

	shadow_buf_vaddr = (void *)isp_cfg_ctx_addr[ctx_id];
	if (!IS_ERR_OR_NULL(shadow_buf_vaddr)) {
		memset(shadow_buf_vaddr, 0x0, ISP_REG_SIZE);
		pr_debug("ctx %d reset shadow page buf\n", ctx_id);
	}

	pr_debug("Done\n");

	return 0;
}


/*  Interface */
static int isp_cfg_map_init(struct isp_cfg_ctx_desc *cfg_ctx)
{
	uint32_t i = 0;
	uint32_t cfg_map_size = 0;
	uint32_t *cfg_map = NULL;
	uint32_t val;

	pr_debug("enter.");
	cfg_map_size = s_cfg_settings.num_of_mod;
	cfg_map = s_cfg_settings.isp_cfg_map;
	if (atomic_inc_return(&cfg_ctx->map_cnt) == 1) {
		pr_info("cfg map init start\n");
		for (i = 0; i < cfg_map_size; i++) {
			ISP_HREG_WR(ISP_CFG0_BUF + i * 4,
				cfg_map[i]);
			ISP_HREG_WR(ISP_CFG1_BUF + i * 4,
				cfg_map[i]);
		}
	}

	/* only config once after system running */
	if (s_map_sec_cnt == 0) {
		uint32_t item;
		uint32_t addr, count;
		struct isp_cfg_map_sector *cur = &s_map_sectors[0];

		count = cfg_map_size;
		if (count > ISP_CFG_MAP_MAX) {
			pr_warn("cfg map array is too large %d\n", count);
			s_map_sec_cnt = 0;
			goto setting;
		}

		pr_debug("map sections %d\n", count);
		s_map_sec_cnt = count;
		for (i = 0; i < s_map_sec_cnt; i++) {
			item = cfg_map[i];
			addr = item & 0x3ffff;
			count = (item >> 18) & 0x3fff;
			cur->offset = addr;
			cur->size = count * 4;
			pr_debug("No.%d. (0x%08x, %d)\n", i, addr, count);
			cur++;
		}
	}

setting:
	val = (s_cfg_settings.pre1_cmd_ready_mode << 27)|
		(s_cfg_settings.pre0_cmd_ready_mode << 26)|
		(s_cfg_settings.cap1_cmd_ready_mode << 25)|
		(s_cfg_settings.cap0_cmd_ready_mode << 24)|
		(s_cfg_settings.bp_cap1_pixel_rdy << 23) |
		(s_cfg_settings.bp_cap0_pixel_rdy << 22) |
		(s_cfg_settings.bp_pre1_pixel_rdy << 21) |
		(s_cfg_settings.bp_pre0_pixel_rdy << 20) |
		(s_cfg_settings.cfg_main_sel << 16) |
		(s_cfg_settings.num_of_mod << 8) |
		(s_cfg_settings.sdw_mode << 5) |
		(s_cfg_settings.tm_bypass << 4) |
		(s_cfg_settings.bypass);

	ISP_HREG_WR(ISP_CFG_PAMATER, val);

	if (!s_cfg_settings.tm_bypass) {
		ISP_HREG_WR(ISP_CFG_TM_NUM,
				s_cfg_settings.tm_set_number);
		ISP_HREG_WR(ISP_CFG_CAP0_TH,
				s_cfg_settings.cap0_th);
		ISP_HREG_WR(ISP_CFG_CAP1_TH,
				s_cfg_settings.cap1_th);
	}

	ISP_HREG_MWR(ISP_ARBITER_ENDIAN_COMM, BIT_0, 0x1);
	return 0;
}

static int isp_cfg_start_isp(
			struct isp_cfg_ctx_desc *cfg_ctx,
			enum isp_context_hw_id ctx_id)
{
	unsigned long reg_addr[] = {
		ISP_CFG_PRE0_START,
		ISP_CFG_CAP0_START,
		ISP_CFG_PRE1_START,
		ISP_CFG_CAP1_START,
	};

	pr_debug("isp cfg start:  context_id %d, P0_addr 0x%x\n", ctx_id,
		ISP_HREG_RD(ISP_CFG_PRE0_CMD_ADDR));

	ISP_HREG_WR(reg_addr[ctx_id], 1);
	return 0;
}


static int isp_cfg_config_block(
			struct isp_cfg_ctx_desc *cfg_ctx,
			enum isp_context_id sw_ctx_id,
			enum isp_context_hw_id hw_ctx_id,
			uint32_t  fmcu_enable)
{
	int ret = 0;
	uint32_t val = 0;
	unsigned long flag;
	void *shadow_buf_vaddr = NULL;
	void *work_buf_vaddr = NULL;
	unsigned long hw_addr = 0;
	enum cfg_buf_id buf_id;
	struct isp_cfg_buf *cfg_buf_p;
	uint32_t ready_mode[ISP_CONTEXT_HW_NUM] = {
		BIT_26, /* pre0_cmd_ready_mode */
		BIT_24, /* cap0_cmd_ready_mode */
		BIT_27, /* pre1_cmd_ready_mode */
		BIT_25 /* cap1_cmd_ready_mode */
	};

	if (!cfg_ctx) {
		pr_err("fail to get cfg_ctx pointer\n");
		return -EFAULT;
	}
	pr_debug("cfg isp sw ctx %d hw ctx %d\n", sw_ctx_id, hw_ctx_id);

	shadow_buf_vaddr = (void *)isp_cfg_ctx_addr[sw_ctx_id];

	if (hw_ctx_id < ISP_CONTEXT_HW_NUM) {
		cfg_buf_p = &cfg_ctx->cfg_buf[hw_ctx_id];
		buf_id = CFG_BUF_HW;
		hw_addr = (unsigned long)cfg_buf_p->reg_buf[buf_id].hw_addr;
		work_buf_vaddr = cfg_buf_p->reg_buf[buf_id].sw_addr;

		pr_debug("ctx %d cmd buf %p, %p\n",
				hw_ctx_id, work_buf_vaddr, shadow_buf_vaddr);

		if (s_map_sec_cnt > 0)
			goto copy_sec;

		pr_debug("copy whole cfg buffer\n");
		memcpy(work_buf_vaddr, shadow_buf_vaddr, ISP_REG_SIZE);
	} else {
		pr_err("fail to get valid isp hw ctx_id %d\n", hw_ctx_id);
		return -EINVAL;
	}

copy_sec:
	if (s_map_sec_cnt > 0) {
		uint32_t i;
		unsigned long src = (unsigned long)shadow_buf_vaddr;
		unsigned long dst = (unsigned long)work_buf_vaddr;
		struct isp_cfg_map_sector *cur = &s_map_sectors[0];

		pr_debug("copy %d sections for cfg buffer\n", s_map_sec_cnt);
		for (i = 0; i < s_map_sec_cnt; i++) {
			memcpy((void *)(dst + cur->offset), (void *)(src + cur->offset), cur->size);
			cur++;
		}
	}

	/* FLUSH_DCACHE(work_buf_vaddr, ISP_REG_SIZE); */
	/* sprd_ion_flush_dcache_area_wrapper(work_buf_vaddr, ISP_REG_SIZE); */

	pr_debug("shadow: 0x%p, work: 0x%p, hw_addr: 0x%lx\n",
			shadow_buf_vaddr, work_buf_vaddr, hw_addr);

	if (fmcu_enable)
		val = ready_mode[hw_ctx_id];
	else
		val = 0;

	spin_lock_irqsave(&cfg_ctx->lock, flag);
	ISP_HREG_MWR(ISP_CFG_PAMATER, ready_mode[hw_ctx_id], val);
	spin_unlock_irqrestore(&cfg_ctx->lock, flag);

	ISP_HREG_WR(cfg_cmd_addr_reg[hw_ctx_id], hw_addr);

	pr_debug("ctx %d,  reg %08x  %08x, hw_addr %lx, val %08x\n",
		hw_ctx_id,
		(uint32_t)cfg_cmd_addr_reg[hw_ctx_id],
		(uint32_t)ISP_GET_REG(cfg_cmd_addr_reg[hw_ctx_id]),
		hw_addr,
		ISP_HREG_RD(cfg_cmd_addr_reg[hw_ctx_id]));

	pr_debug("Done\n");
	return ret;
}


static int isp_cfg_ctx_init(struct isp_cfg_ctx_desc *cfg_ctx)
{
	int ret = 0;
	int i;

	if (!cfg_ctx) {
		pr_err("fail to get cfg_ctx pointer\n");
		return -EFAULT;
	}
	pr_debug("Enter\n");

	if (atomic_inc_return(&cfg_ctx->user_cnt) > 1) {
		pr_info("already done.\n");
		goto exit;
	}

	cfg_ctx->lock = __SPIN_LOCK_UNLOCKED(&cfg_ctx->lock);
	atomic_set(&cfg_ctx->map_cnt, 0);

	ret = cctx_buf_init(cfg_ctx);
	if (ret) {
		pr_err("fail to init isp cfg ctx buffer.\n");
		return -EFAULT;
	}

	for (i = 0; i < ISP_CONTEXT_SW_NUM; i++)
		isp_cfg_poll_addr[i] = &isp_cfg_ctx_addr[i];

	s_cfg_settings.isp_cfg_map =
		cfg_ctx->hw_ops->core_ops.cfg_map_info_get(
		&s_cfg_settings.num_of_mod);

exit:
	pr_info("cfg ctx init done\n");

	return ret;
}

static int isp_cfg_ctx_deinit(struct isp_cfg_ctx_desc *cfg_ctx)
{
	int ret = 0;

	if (!cfg_ctx) {
		pr_err("fail to get cfg_ctx pointer\n");
		return -EFAULT;
	}

	pr_debug("Enter\n");
	if (atomic_dec_return(&cfg_ctx->user_cnt) > 0) {
		pr_info("isp cfg still have user.\n");
		goto exit;
	}

	atomic_set(&cfg_ctx->map_cnt, 0);
	ret = cctx_buf_deinit(cfg_ctx);
	if (ret)
		pr_err("fail to deinit isp cfg ctx buffer.\n");
exit:
	pr_info("Done\n");

	return ret;
}


struct isp_cfg_ops cfg_ops = {
	.ctx_init = isp_cfg_ctx_init,
	.ctx_deinit = isp_cfg_ctx_deinit,
	.ctx_reset = isp_cfg_reset_ctxbuf,
	.hw_init = isp_cfg_map_init,
	.hw_cfg = isp_cfg_config_block,
	.hw_start = isp_cfg_start_isp,
};

struct isp_cfg_ctx_desc s_ctx_desc = {
		.ops = &cfg_ops,
};

struct isp_cfg_ctx_desc *get_isp_cfg_ctx_desc()
{
	return &s_ctx_desc;
}

int put_isp_cfg_ctx_desc(struct isp_cfg_ctx_desc *param)
{
	if (&s_ctx_desc == param)
		return 0;
	pr_err("fail to match param %p, %p\n",
			param, &s_ctx_desc);
	return -EINVAL;
}
