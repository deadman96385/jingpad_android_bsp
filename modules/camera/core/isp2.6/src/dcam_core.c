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

#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/regmap.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>
#include <linux/sprd_ion.h>

#include <sprd_isp_hw.h>
#include "sprd_img.h"
#include <video/sprd_mmsys_pw_domain.h>
#include <sprd_mm.h>

#include "cam_debugger.h"
#include "dcam_reg.h"
#include "dcam_int.h"
#include "dcam_path.h"

#include <linux/sprd_iommu.h>
#include <linux/sprd_ion.h>

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "DCAM_CORE: %d %d %s : "\
	fmt, current->pid, __LINE__, __func__

/* VCH2 maybe used for raw picture output
 * If yes, PDAF should not output data though VCH2
 * todo: avoid conflict between raw/pdaf type3
 */
struct statis_path_buf_info s_statis_path_info_all[] = {
	{DCAM_PATH_PDAF,    0,  0, STATIS_PDAF},
	{DCAM_PATH_VCH2,    0,   0, STATIS_EBD},
	{DCAM_PATH_AEM,     0,   0, STATIS_AEM},
	{DCAM_PATH_AFM,     0,   0, STATIS_AFM},
	{DCAM_PATH_AFL,     0,   0, STATIS_AFL},
	{DCAM_PATH_HIST,    0,  0, STATIS_HIST},
	{DCAM_PATH_3DNR,    0,  0, STATIS_3DNR},
	{DCAM_PATH_LSCM,    0,  0, STATIS_LSCM},
};

atomic_t s_dcam_working;
atomic_t s_dcam_axi_opened;
atomic_t s_dcam_opened[DCAM_ID_MAX];

/*
 * set MIPI capture related register
 * range: 0x0100 ~ 0x010c
 *
 * TODO: support DCAM2, some registers only exist in DCAM0/1
 */

static int dcam_cfg_dcamsec(struct dcam_pipe_dev *dev, void *param)
{
	//bool *sec_eb = (bool *)param;

	dev->dcamsec_eb =  0;//*sec_eb;

	pr_info("camca : dcamsec_mode=%d\n", dev->dcamsec_eb);
	return 0;
}

static int dcam_cfg_rps(struct dcam_pipe_dev *dev, void *param)
{
	uint32_t *data = (uint32_t *)param;

	dev->rps =  *data;

	pr_info("hwsim : rps[%d]\n", dev->rps);
	return 0;
}


void dcam_ret_src_frame(void *param)
{
	struct camera_frame *frame;
	struct dcam_pipe_dev *dev;

	if (!param) {
		pr_err("fail to get valid param.\n");
		return;
	}

	frame = (struct camera_frame *)param;
	dev = (struct dcam_pipe_dev *)frame->priv_data;
	pr_debug("frame %p, ch_id %d, buf_fd %d\n",
		frame, frame->channel_id, frame->buf.mfd[0]);

	cambuf_iommu_unmap(&frame->buf);
	dev->dcam_cb_func(
		DCAM_CB_RET_SRC_BUF,
		frame, dev->cb_priv_data);
}

void dcam_ret_out_frame(void *param)
{
	struct camera_frame *frame;
	struct dcam_pipe_dev *dev;
	struct dcam_path_desc *path;

	if (!param) {
		pr_err("fail to get valid param.\n");
		return;
	}

	frame = (struct camera_frame *)param;

	if (frame->is_reserved) {
		path =  (struct dcam_path_desc *)frame->priv_data;
		camera_enqueue(&path->reserved_buf_queue, frame);
	} else {
		cambuf_iommu_unmap(&frame->buf);
		dev = (struct dcam_pipe_dev *)frame->priv_data;
		dev->dcam_cb_func(DCAM_CB_DATA_DONE, frame, dev->cb_priv_data);
	}
}


void dcam_destroy_reserved_buf(void *param)
{
	struct camera_frame *frame;

	if (!param) {
		pr_err("fail to get valid param.\n");
		return;
	}

	frame = (struct camera_frame *)param;

	if (unlikely(frame->is_reserved == 0)) {
		pr_err("fail to check frame type if reserved.\n");
		return;
	}
	/* is_reserved:
	 *  1:  basic mapping reserved buffer;
	 *  2:  copy of reserved buffer.
	 */
	if (frame->is_reserved == 1) {
		cambuf_iommu_unmap(&frame->buf);
		cambuf_put_ionbuf(&frame->buf);
	}
	put_empty_frame(frame);
}

void dcam_destroy_statis_buf(void *param)
{
	struct camera_frame *frame;

	if (!param) {
		pr_err("fail to get valid param.\n");
		return;
	}

	frame = (struct camera_frame *)param;
	put_empty_frame(frame);
}


static struct camera_buf *get_reserved_buffer(struct dcam_pipe_dev *dev)
{
	int ret = 0;
	int iommu_enable = 0; /* todo: get from dev dts config value */
	size_t size;
	struct camera_buf *ion_buf = NULL;

	ion_buf = kzalloc(sizeof(*ion_buf), GFP_KERNEL);
	if (!ion_buf) {
		pr_err("fail to alloc buffer.\n");
		goto nomem;
	}

	if (get_iommu_status(CAM_IOMMUDEV_DCAM) == 0)
		iommu_enable = 1;

	size = DCAM_INTERNAL_RES_BUF_SIZE;
	ret = cambuf_alloc(ion_buf, size, 0, iommu_enable);
	if (ret) {
		pr_err("fail to get dcam reserverd buffer\n");
		goto ion_fail;
	}

	ret = cambuf_iommu_map(ion_buf, CAM_IOMMUDEV_DCAM);
	if (ret) {
		pr_err("fail to map dcam reserved buffer to iommu\n");
		goto hwmap_fail;
	}
	pr_info("dcam%d done. ion %p\n", dev->idx, ion_buf);
	return ion_buf;

hwmap_fail:
	cambuf_free(ion_buf);
ion_fail:
	kfree(ion_buf);
nomem:
	return NULL;
}

static int put_reserved_buffer(struct dcam_pipe_dev *dev)
{
	struct camera_buf *ion_buf = NULL;

	ion_buf = (struct camera_buf *)dev->internal_reserved_buf;
	if (!ion_buf) {
		pr_info("no reserved buffer.\n");
		return 0;
	}
	pr_info("ionbuf %p\n", ion_buf);

	cambuf_iommu_unmap(ion_buf);
	if (ion_buf->type == CAM_BUF_USER)
		cambuf_put_ionbuf(ion_buf);
	else
		cambuf_free(ion_buf);
	kfree(ion_buf);
	dev->internal_reserved_buf = NULL;

	return 0;
}

static int statis_type_to_path_id(enum isp_statis_buf_type type)
{
	switch (type) {
	case STATIS_AEM:
		return DCAM_PATH_AEM;
	case STATIS_AFM:
		return DCAM_PATH_AFM;
	case STATIS_AFL:
		return DCAM_PATH_AFL;
	case STATIS_HIST:
		return DCAM_PATH_HIST;
	case STATIS_PDAF:
		return DCAM_PATH_PDAF;
	case STATIS_EBD:
		return DCAM_PATH_VCH2;
	case STATIS_3DNR:
		return DCAM_PATH_3DNR;
	case STATIS_LSCM:
		return DCAM_PATH_LSCM;
	default:
		return -1;
	}
}

static void init_reserved_statis_bufferq(struct dcam_pipe_dev *dev)
{
	int i, j;
	enum isp_statis_buf_type stats_type;
	struct camera_frame *newfrm;
	enum dcam_path_id path_id;
	struct camera_buf *ion_buf = NULL;
	struct dcam_path_desc *path;

	pr_debug("enter\n");

	if (dev->internal_reserved_buf == NULL) {
		ion_buf =  get_reserved_buffer(dev);
		if (IS_ERR_OR_NULL(ion_buf))
			return;

		dev->internal_reserved_buf = ion_buf;
	}
	ion_buf = (struct camera_buf *)dev->internal_reserved_buf;

	for (i = 0; i < (int)ARRAY_SIZE(s_statis_path_info_all); i++) {
		path_id = s_statis_path_info_all[i].path_id;
		stats_type = s_statis_path_info_all[i].buf_type;
		if (!stats_type)
			continue;

		path = &dev->path[path_id];
		j  = 0;
		while (j < DCAM_RESERVE_BUF_Q_LEN) {
			newfrm = get_empty_frame();
			if (newfrm) {
				newfrm->is_reserved = 1;
				memcpy(&newfrm->buf, ion_buf, sizeof(struct camera_buf));
				camera_enqueue(&path->reserved_buf_queue, newfrm);
				j++;
			}
			pr_debug("path%d reserved buffer %d\n", path->path_id, j);
		}
	}

	pr_info("init statis reserver bufq done: %p\n", ion_buf);
}

static int init_statis_bufferq(struct dcam_pipe_dev *dev)
{
	int ret = 0;
	int i, j;
	enum dcam_path_id path_id;
	enum isp_statis_buf_type stats_type;
	struct camera_buf *ion_buf;
	struct camera_frame *pframe;
	struct dcam_path_desc *path;

	pr_debug("enter\n");

	for (i = 0; i < ARRAY_SIZE(s_statis_path_info_all); i++) {
		path_id = s_statis_path_info_all[i].path_id;
		stats_type = s_statis_path_info_all[i].buf_type;
		if (!stats_type)
			continue;

		path = &dev->path[path_id];
		camera_queue_init(&path->out_buf_queue,
				DCAM_OUT_BUF_Q_LEN, 0, dcam_destroy_statis_buf);
		camera_queue_init(&path->result_queue,
				DCAM_RESULT_Q_LEN, 0, dcam_destroy_statis_buf);
		camera_queue_init(&path->reserved_buf_queue,
				DCAM_RESERVE_BUF_Q_LEN, 0,
					dcam_destroy_statis_buf);
	}

	init_reserved_statis_bufferq(dev);

	for (i = 0; i < ARRAY_SIZE(s_statis_path_info_all); i++) {

		path_id = s_statis_path_info_all[i].path_id;
		stats_type = s_statis_path_info_all[i].buf_type;
		if (!stats_type)
			continue;

		path = &dev->path[path_id];
		for (j = 0; j < STATIS_BUF_NUM_MAX; j++) {
			ion_buf = &dev->statis_buf_array[stats_type][j];
			if (ion_buf->mfd[0] <= 0)
				continue;

			pframe = get_empty_frame();
			pframe->channel_id = path_id;
			pframe->irq_property = stats_type;
			pframe->buf = *ion_buf;

			ret = camera_enqueue(&path->out_buf_queue, pframe);
			if (ret) {
				pr_info("dcam%d statis %d overflow\n", dev->idx, stats_type);
				put_empty_frame(pframe);
			}
			pr_debug("dcam%d statis %d buf %d kaddr 0x%lx iova 0x%08x\n",
				dev->idx, stats_type, ion_buf->mfd[0],
				ion_buf->addr_k[0], (uint32_t)ion_buf->iova[0]);
		}
	}

	pr_info("done.\n");
	return ret;
}

static int deinit_statis_bufferq(struct dcam_pipe_dev *dev)
{
	int ret = 0;
	int i;
	enum dcam_path_id path_id;
	struct dcam_path_desc *path;

	pr_debug("enter\n");

	for (i = 0; i < ARRAY_SIZE(s_statis_path_info_all); i++) {
		path_id = s_statis_path_info_all[i].path_id;
		path = &dev->path[path_id];

		pr_debug("path_id[%d] i[%d]\n", path_id, i);

		if (path_id == DCAM_PATH_MAX)
			continue;

		atomic_set(&path->user_cnt, 0);
		camera_queue_clear(&path->out_buf_queue);
		camera_queue_clear(&path->result_queue);
		camera_queue_clear(&path->reserved_buf_queue);
	}
	pr_info("done.\n");
	return ret;
}


static int unmap_statis_buffer(struct dcam_pipe_dev *dev)
{
	int i, j;
	int32_t mfd;
	enum dcam_path_id path_id;
	enum isp_statis_buf_type stats_type;
	struct camera_buf *ion_buf = NULL;

	for (i = 0; i < ARRAY_SIZE(s_statis_path_info_all); i++) {
		path_id = s_statis_path_info_all[i].path_id;
		stats_type = s_statis_path_info_all[i].buf_type;
		if (!stats_type)
			continue;

		for (j = 0; j < STATIS_BUF_NUM_MAX; j++) {
			ion_buf = &dev->statis_buf_array[stats_type][j];
			mfd = ion_buf->mfd[0];
			if (mfd <= 0)
				continue;

			pr_debug("stats %d,  j %d,  mfd %d, offset %d\n",
					stats_type, j, mfd, ion_buf->offset[0]);

			if (ion_buf->mapping_state & CAM_BUF_MAPPING_KERNEL)
				cambuf_kunmap(ion_buf);
			cambuf_iommu_unmap(ion_buf);
			cambuf_put_ionbuf(ion_buf);
			memset(ion_buf, 0, sizeof(struct camera_buf));
		}
	}

	pr_info("done\n");
	return 0;
}

static int dcam_cfg_statis_buffer(
		struct dcam_pipe_dev *dev,
		struct isp_statis_buf_input *input)
{
	int ret = 0;
	int i, j;
	int32_t mfd;
	uint32_t offset;
	enum dcam_path_id path_id;
	enum isp_statis_buf_type stats_type;
	struct camera_buf *ion_buf = NULL;
	struct camera_frame *pframe = NULL;
	struct dcam_path_desc *path = NULL;

	if (input->type == STATIS_INIT) {
		memset(&dev->statis_buf_array[0][0], 0, sizeof(dev->statis_buf_array));
		for (i = 0; i < ARRAY_SIZE(s_statis_path_info_all); i++) {
			path_id = s_statis_path_info_all[i].path_id;
			stats_type = s_statis_path_info_all[i].buf_type;
			if (!stats_type)
				continue;

			for (j = 0; j < STATIS_BUF_NUM_MAX; j++) {
				mfd = input->mfd_array[stats_type][j];

				pr_debug("i %d, type %d, mfd %d, offset %d\n",
					i, stats_type, mfd, input->offset_array[stats_type][j]);

				if (mfd <= 0)
					continue;

				ion_buf = &dev->statis_buf_array[stats_type][j];
				ion_buf->mfd[0] = mfd;
				ion_buf->offset[0] =  input->offset_array[stats_type][j];
				ion_buf->type = CAM_BUF_USER;
				ret = cambuf_get_ionbuf(ion_buf);
				if (ret) {
					memset(ion_buf, 0, sizeof(struct camera_buf));
					continue;
				}

				ret = cambuf_iommu_map(ion_buf, CAM_IOMMUDEV_DCAM);
				if (ret) {
					cambuf_put_ionbuf(ion_buf);
					memset(ion_buf, 0, sizeof(struct camera_buf));
					continue;
				}

				if (stats_type != STATIS_PDAF) {
					ret = cambuf_kmap(ion_buf);
					if (ret) {
						pr_err("fail to kmap statis buf %d\n", mfd);
						ion_buf->addr_k[0] = 0L;
					}
				}

				pr_debug("stats %d,mfd %d, off %d, kaddr 0x%lx, iova 0x%08x\n",
					stats_type, mfd, ion_buf->offset[0],
					ion_buf->addr_k[0], (uint32_t)ion_buf->iova[0]);
			}
		}
		pr_info("done\n");

	} else if (atomic_read(&dev->state) == STATE_RUNNING) {

		path_id = statis_type_to_path_id(input->type);
		if (path_id < 0) {
			pr_err("fail to get a valid statis type: %d\n", input->type);
			ret = -EINVAL;
			goto exit;
		}

		for (j = 0; j < STATIS_BUF_NUM_MAX; j++) {
			mfd = dev->statis_buf_array[input->type][j].mfd[0];
			offset = dev->statis_buf_array[input->type][j].offset[0];
			if ((mfd > 0) && (mfd == input->mfd)
				&&(offset == input->offset)) {
				ion_buf = &dev->statis_buf_array[input->type][j];
				break;
			}
		}

		if (ion_buf == NULL) {
			pr_err("fail to get statis buf %d, type %d\n",
					input->type, input->mfd);
			ret = -EINVAL;
			goto exit;
		}

		pframe = get_empty_frame();
		pframe->irq_property = input->type;
		pframe->buf = *ion_buf;
		path = &dev->path[path_id];
		ret = camera_enqueue(&path->out_buf_queue, pframe);
		pr_debug("statis %d, mfd %d, off %d, iova 0x%08x,  kaddr 0x%lx\n",
			input->type, mfd, offset,
			(uint32_t)pframe->buf.iova[0], pframe->buf.addr_k[0]);

		if (ret)
			put_empty_frame(pframe);
	}
exit:
	return ret;
}

/* use reserved buffer from user for statis as well */
static int cfg_reserved_stat_buffer(
		struct dcam_pipe_dev *dev, void *param)
{
	int ret = 0;
	int32_t mfd;
	struct camera_buf *ion_buf = NULL;

	ion_buf = (struct camera_buf *)dev->internal_reserved_buf;
	if (ion_buf) {
		pr_debug("there is reserved buffer for stats\n");
		return 0;
	}

	ion_buf = kzalloc(sizeof(*ion_buf), GFP_KERNEL);
	if (!ion_buf) {
		pr_err("fail to alloc buffer.\n");
		goto nomem;
	}

	mfd = *(int32_t *)param;
	ion_buf->mfd[0] = mfd;
	ion_buf->type = CAM_BUF_USER;

	ret = cambuf_get_ionbuf(ion_buf);
	if (ret) {
		pr_err("fail to get buf for %d\n", mfd);
		goto buf_fail;
	}

	ret = cambuf_iommu_map(ion_buf, CAM_IOMMUDEV_DCAM);
	if (ret) {
		pr_err("fail to map dcam reserved buffer to iommu\n");
		goto map_fail;
	}
	pr_info("dcam%d, ion %p, mfd %d\n", dev->idx, ion_buf, mfd);

	dev->internal_reserved_buf = (void *)ion_buf;
	return 0;

map_fail:
	cambuf_put_ionbuf(ion_buf);
buf_fail:
	kfree(ion_buf);
nomem:
	return -EINVAL;
}

static int dcam_cfg_statis_buffer_skip(struct dcam_pipe_dev *dev, struct camera_frame *pframe)
{
	int ret = 0;
	int path_id;

	path_id = statis_type_to_path_id(pframe->irq_property);
	if (path_id < 0) {
		pr_err("invalid statis type: %d\n", pframe->irq_property);
		ret = -EINVAL;
		goto exit;
	}

	ret = camera_enqueue(&dev->path[path_id].out_buf_queue, pframe);
exit:
	return ret;
}

#if 0
/* dcam_offline_cfg_param
 * after param prepare
 * Input: param
 * unused
 */
int dcam_offline_cfg_param(struct dcam_dev_param *pm)
{
	FUNC_DCAM_PARAM func = NULL;
	const FUNC_DCAM_PARAM all_sub[] = {
		dcam_k_blc_block, dcam_k_rgb_gain_block,
		dcam_k_rgb_dither_random_block,
		dcam_k_lsc_block, dcam_k_bayerhist_block, dcam_k_aem_bypass,
		dcam_k_aem_mode, dcam_k_aem_win, dcam_k_aem_skip_num,
		dcam_k_aem_rgb_thr, dcam_k_afl_block, dcam_k_afl_bypass,
		dcam_k_awbc_block, dcam_k_awbc_gain, dcam_k_awbc_block,
		dcam_k_bpc_block,
		dcam_k_bpc_ppe_param, dcam_k_3dnr_me, dcam_k_afm_block,
		dcam_k_afm_bypass, dcam_k_afm_win, dcam_k_afm_win_num,
		dcam_k_afm_mode, dcam_k_afm_skipnum, dcam_k_afm_crop_eb,
		dcam_k_afm_crop_size, dcam_k_afm_done_tilenum,
	};
	int i;
	int ret = 0, t = 0;

	if (pm == NULL) {
		pr_err("dcam param error(pm == NULL)\n");
		return -EINVAL;
	}

	for (i = 0; i < ARRAY_SIZE(all_sub); i++) {
		func = all_sub[i];
		if (func)
			t = func(pm);
		if (t)
			pr_warn("set param fail, sub block %d\n", i);

		ret |= t;
	}

	return ret;
}
#endif

static int dcam_offline_start_slices_hw(void *param)
{
	int ret = 0;
	int i, loop = 0;
	uint32_t force_ids = DCAM_CTRL_ALL;
	uint32_t fetch_pitch = 0;
	uint32_t reg_val = 0;
	uint32_t loose_val = 0;
	uint32_t val_4in1 = 0;
	struct dcam_pipe_dev *dev = NULL;
	struct camera_frame *pframe = NULL;
	struct dcam_path_desc *path = NULL;
	struct dcam_fetch_info *fetch = NULL;
	struct cam_hw_info *hw = NULL;

	dev = (struct dcam_pipe_dev *)param;
	fetch = &dev->fetch;
	hw = dev->hw;

	pframe = camera_dequeue(&dev->in_queue);
	if (pframe == NULL) {
		pr_warn("no frame from in_q. dcam%d\n", dev->idx);
		return 0;
	}

	pr_info("frame %p, dcam%d  ch_id %d.  buf_fd %d\n", pframe,
		dev->idx, pframe->channel_id, pframe->buf.mfd[0]);
	pr_info("size %d %d,  endian %d, pattern %d\n",
		pframe->width, pframe->height, pframe->endian, pframe->pattern);

	ret = cambuf_iommu_map(&pframe->buf, CAM_IOMMUDEV_DCAM);
	if (ret) {
		pr_err("fail to map buf to dcam%d iommu.\n", dev->idx);
		goto map_err;
	}

	ret = wait_for_completion_interruptible_timeout(
					&dev->slice_done,
					DCAM_OFFLINE_TIMEOUT);
	if (ret == ERESTARTSYS) {
		pr_err("fail to wait as interrupted.\n");
		ret = -EFAULT;
		goto wait_err;
	} else if (ret == 0) {
		pr_err("fail to wait as dcam%d offline timeout.\n", dev->idx);
		ret = -EFAULT;
		goto wait_err;
	}
	ret = 0;

	do {
		ret = camera_enqueue(&dev->proc_queue, pframe);
		if (ret == 0)
			break;
		pr_info("wait for proc queue. loop %d\n", loop);
		mdelay(1);
	} while (loop++ < 500);
	if (ret) {
		pr_err("fail to enqueue frame as timeout.\n");
		ret = 0;
		goto inq_overflow;
	}

	/* prepare frame info for tx done
	 * ASSERT: this dev has no cap_sof
	 */
	dev->index_to_set = pframe->fid;
	if (pframe->sensor_time.tv_sec || pframe->sensor_time.tv_usec) {
		dev->frame_ts[tsid(pframe->fid)].tv_sec =
			pframe->sensor_time.tv_sec;
		dev->frame_ts[tsid(pframe->fid)].tv_nsec =
			pframe->sensor_time.tv_usec * NSEC_PER_USEC;
		dev->frame_ts_boot[tsid(pframe->fid)] = pframe->boot_sensor_time;
		pr_info("frame[%d]\n", pframe->fid);
	}
	/* cfg path output and path */
	for (i  = 0; i < DCAM_PATH_MAX; i++) {
		path = &dev->path[i];
		if (atomic_read(&path->user_cnt) < 1 || atomic_read(&path->is_shutoff) > 0)
			continue;
		ret = dcam_path_set_store_frm(dev, path, NULL); /* TODO: */
		if (ret == 0) {
			/* interrupt need > 1 */
			loose_val = ((dev->is_loose) | (path->is_loose));
			val_4in1 = ((dev->is_4in1) | (path->is_4in1));
			path->is_loose = loose_val;
			atomic_set(&path->set_frm_cnt, 1);
			atomic_inc(&path->set_frm_cnt);
			hw->hw_ops.core_ops.path_start(dev, i);
		} else {
			pr_err("fail to set dcam%d path%d store frm\n",
				dev->idx, path->path_id);
			ret = 0;
			goto dequeue;
		}
	}

	/* cfg fetch */
	if(val_4in1 == 1)
		fetch->is_loose = 0;
	else
		fetch->is_loose = loose_val;
	fetch->endian = pframe->endian;
	fetch->pattern = pframe->pattern;
	fetch->size.w = pframe->width;
	fetch->size.h = pframe->height;
	fetch->trim.start_x = 0;
	fetch->trim.start_y = 0;
	fetch->trim.size_x = pframe->width;
	fetch->trim.size_y = pframe->height;
	fetch->addr.addr_ch0 = (uint32_t)pframe->buf.iova[0];
	if (fetch->is_loose != 0) {
		fetch_pitch = (fetch->size.w * 16 + 127) / 128;
	} else {
		fetch_pitch = (fetch->size.w * 10 + 127) / 128;
	}

	if (hw->ip_dcam[dev->idx]->offline_slice_support
		&& hw->hw_ops.core_ops.dcam_slice_fetch_set)
		hw->hw_ops.core_ops.dcam_slice_fetch_set(dev);

	/* cfg mipicap */
	DCAM_REG_MWR(dev->idx,
		DCAM_MIPI_CAP_CFG, BIT_30, 0x1 << 30);
	DCAM_REG_MWR(dev->idx,
		DCAM_MIPI_CAP_CFG, BIT_29, 0x1 << 29);
	DCAM_REG_MWR(dev->idx,
		DCAM_MIPI_CAP_CFG, BIT_28, 0x1 << 28);
	DCAM_REG_MWR(dev->idx,
		DCAM_MIPI_CAP_CFG, BIT_12, 0x1 << 12);
	DCAM_REG_MWR(dev->idx,
		DCAM_MIPI_CAP_CFG, BIT_3, 0x0 << 3);
	DCAM_REG_MWR(dev->idx,
		DCAM_MIPI_CAP_CFG, BIT_1, 0x1 << 1);
	reg_val = (pframe->height - 1) << 16;
	reg_val |= (pframe->width/2 - 1);
	DCAM_REG_WR(dev->idx, DCAM_MIPI_CAP_END, reg_val);

	/* cfg bin path */
	DCAM_REG_MWR(dev->idx, DCAM_CAM_BIN_CFG, 0x3FF << 20, fetch_pitch << 20);

	DCAM_AXIM_WR(IMG_FETCH_X,
		(fetch_pitch << 16) | (fetch->trim.start_x & 0xffff));

	dev->slice_count = 2;

	mutex_lock(&dev->blk_dcam_pm->lsc.lsc_lock);
	dcam_init_lsc(dev, 0);
	mutex_unlock(&dev->blk_dcam_pm->lsc.lsc_lock);

	/* DCAM_CTRL_COEF will always set in dcam_init_lsc() */
	//force_ids &= ~DCAM_CTRL_COEF;
	hw->hw_ops.core_ops.force_copy(force_ids, dev);
	udelay(500);
	dev->iommu_status = (uint32_t)(-1);
	atomic_set(&dev->state, STATE_RUNNING);
	pr_info("slice0 fetch start\n");

	/* start fetch */
	DCAM_AXIM_WR(IMG_FETCH_START, 1);

	while(1) {
		ret = wait_for_completion_interruptible_timeout(
						&dev->slice_done,
						DCAM_OFFLINE_TIMEOUT);
		if (ret == ERESTARTSYS) {
			pr_err("fail to wait as interrupted\n");
			ret = -EFAULT;
			goto dequeue;
		} else if (ret == 0) {
			pr_err("fail to wait as dcam%d offline timeout.\n", dev->idx);
			ret = -EFAULT;
			goto dequeue;
		}
		ret = 0;

		reg_val = DCAM_REG_RD(dev->idx, DCAM_BIN_BASE_WADDR0);
		DCAM_REG_WR(dev->idx, DCAM_BIN_BASE_WADDR0, reg_val + fetch_pitch*128/8/2);
		DCAM_AXIM_WR(IMG_FETCH_X,
			(fetch_pitch << 16) | ((fetch->trim.start_x + fetch->trim.size_x/2) & 0x1fff));
		DCAM_REG_MWR(dev->idx,
			DCAM_MIPI_CAP_CFG, BIT_30, 0x0 << 30);

		dcam_init_lsc_slice(dev, 0);
		hw->hw_ops.core_ops.force_copy(force_ids, dev);
		udelay(500);
		dev->iommu_status = (uint32_t)(-1);
		atomic_set(&dev->state, STATE_RUNNING);
		pr_info("slice1 fetch start\n");

		DCAM_AXIM_WR(IMG_FETCH_START, 1);
		break;
	}

	return 0;

dequeue:
	pframe = camera_dequeue_tail(&dev->proc_queue);
inq_overflow:
wait_err:
	cambuf_iommu_unmap(&pframe->buf);
	complete(&dev->slice_done);
	complete(&dev->frm_done);
map_err:
	/* return buffer to cam channel shared buffer queue. */
	dev->dcam_cb_func(DCAM_CB_RET_SRC_BUF, pframe, dev->cb_priv_data);
	dev->slice_num = 0;
	dev->slice_count = 0;
	return 0;
}

int get_slice_trim(uint32_t width, uint32_t heigth, uint32_t slice_num,
	uint32_t slice_no, struct img_trim *slice_trim)
{
	int ret = 0;
	uint32_t slice_w = 0, slice_h = 0;
	uint32_t slice_x_num = 0, slice_y_num = 0;
	uint32_t start_x = 0, size_x = 0;
	uint32_t start_y = 0, size_y = 0;

	if (!width || !slice_num || !slice_trim) {
		pr_err("fail to get valid param %d, %d, %p.\n", width, slice_num, slice_trim);
		return -EFAULT;
	}

	if (heigth > ISP_SLCIE_HEIGHT_MAX) {
		slice_x_num = slice_num / 2;
		slice_y_num = 2;
	} else {
		slice_x_num = slice_num;
		slice_y_num = 1;
	}
	slice_w = width / slice_x_num;
	slice_w = ALIGN(slice_w, 2);
	slice_h = heigth / slice_y_num;
	slice_h = ALIGN(slice_h, 2);

	start_x = slice_w * (slice_no % slice_x_num);
	size_x = slice_w;
	if (size_x & 0x03) {
		if (slice_no != 0) {
			start_x -=  ALIGN(size_x, 4) - size_x;
			size_x = ALIGN(size_x, 4);
		} else {
			start_x -=  ALIGN(size_x, 4);
			size_x = ALIGN(size_x, 4);
		}
	}

	start_y = (slice_no / slice_x_num) * slice_h;
	size_y = slice_h;

	slice_trim->start_x = start_x;
	slice_trim->size_x = size_x;
	slice_trim->start_y = start_y;
	slice_trim->size_y = size_y;
	pr_debug("slice %d [%d, %d, %d, %d].\n", slice_no, start_x, size_x, start_y, size_y);
	return ret;
}

static int dcam_offline_start_slices_sw(void *param)
{
	int ret = 0;
	int i, loop;
	uint32_t force_ids = DCAM_CTRL_ALL;
	struct dcam_pipe_dev *dev = NULL;
	struct camera_frame *pframe = NULL;
	struct dcam_path_desc *path;
	struct dcam_fetch_info *fetch;
	struct cam_hw_info *hw = NULL;
	uint32_t slice_no;

	dev = (struct dcam_pipe_dev *)param;
	dev->offline = 1;
	fetch = &dev->fetch;
	hw = dev->hw;

	if (dev->slice_count) {
		pframe = camera_dequeue(&dev->proc_queue);
		if (!pframe) {
			pr_err("fail to map buf to dcam%d iommu.\n", dev->idx);
			goto map_err;
		}
	} else {
		pframe = camera_dequeue(&dev->in_queue);
		if (pframe == NULL) {
			pr_warn("no frame from in_q. dcam%d\n", dev->idx);
			return 0;
		}

		pr_debug("frame %p, dcam%d  ch_id %d.  buf_fd %d\n", pframe,
			dev->idx, pframe->channel_id, pframe->buf.mfd[0]);
		pr_debug("size %d %d,  endian %d, pattern %d\n",
			pframe->width, pframe->height, pframe->endian, pframe->pattern);

		ret = cambuf_iommu_map(&pframe->buf, CAM_IOMMUDEV_DCAM);
		if (ret) {
			pr_err("fail to map buf to dcam%d iommu.\n", dev->idx);
			goto map_err;
		}

		dev->slice_count = dev->slice_num;
	}
	slice_no = dev->slice_num - dev->slice_count;

	ret = wait_for_completion_interruptible_timeout(
					&dev->slice_done,
					DCAM_OFFLINE_TIMEOUT);
	if (ret == ERESTARTSYS) {
		pr_err("interrupt when dcam wait\n");
		ret = -EFAULT;
		goto wait_err;
	} else if (ret == 0) {
		pr_err("error: dcam%d offline timeout.\n", dev->idx);
		ret = -EFAULT;
		goto wait_err;
	}
	ret = 0;

	loop = 0;
	do {
		ret = camera_enqueue(&dev->proc_queue, pframe);
		if (ret == 0)
			break;
		pr_info("wait for proc queue. loop %d\n", loop);

		/* wait for previous frame proccessed done. */
		mdelay(1);
	} while (loop++ < 500);
	if (ret) {
		pr_err("error: input frame queue tmeout.\n");
		ret = 0;
		goto inq_overflow;
	}

	/* prepare frame info for tx done
	 * ASSERT: this dev has no cap_sof
	 */
	dev->index_to_set = pframe->fid;
	if (pframe->sensor_time.tv_sec || pframe->sensor_time.tv_usec) {
		dev->frame_ts[tsid(pframe->fid)].tv_sec =
			pframe->sensor_time.tv_sec;
		dev->frame_ts[tsid(pframe->fid)].tv_nsec =
			pframe->sensor_time.tv_usec * NSEC_PER_USEC;
		dev->frame_ts_boot[tsid(pframe->fid)] = pframe->boot_sensor_time;
		pr_info("frame[%d]\n", pframe->fid);
	}
	/* cfg path output and path */
	for (i  = 0; i < DCAM_PATH_MAX; i++) {
		path = &dev->path[i];
		if (atomic_read(&path->user_cnt) < 1 || atomic_read(&path->is_shutoff) > 0)
			continue;
		ret = dcam_path_set_store_frm(dev, path, NULL); /* TODO: */
		if (ret == 0) {
			/* interrupt need > 1 */
			atomic_set(&path->set_frm_cnt, 1);
			atomic_inc(&path->set_frm_cnt);
			hw->hw_ops.core_ops.path_start(dev, i);
		} else {
			pr_err("fail to set dcam%d path%d store frm\n",
				dev->idx, path->path_id);
			ret = 0;
			goto dequeue;
		}
	}

	get_slice_trim(pframe->width, pframe->height, dev->slice_num,
		slice_no, &dev->slice_trim);

	/* cfg fetch */
	fetch->is_loose = 0;
	fetch->endian = pframe->endian;
	fetch->pattern = pframe->pattern;
	fetch->size.w = pframe->width;
	fetch->size.h = pframe->height;
	fetch->trim.start_x = 0;
	fetch->trim.start_y = 0;
	fetch->trim.size_x = pframe->width;
	fetch->trim.size_y = pframe->height;
	fetch->addr.addr_ch0 = (uint32_t)pframe->buf.iova[0];
	hw->hw_ops.core_ops.dcam_slice_fetch_set(dev);

	dcam_init_lsc_slice(dev, 0);
	hw->hw_ops.core_ops.force_copy(force_ids, dev);
	udelay(500);
	dev->iommu_status = (uint32_t)(-1);
	atomic_set(&dev->state, STATE_RUNNING);
	dev->err_count = 1;
	hw->hw_ops.core_ops.fetch_start(hw);
	pr_debug("done slice %d.\n", slice_no);

	return 0;

dequeue:
	pframe = camera_dequeue_tail(&dev->proc_queue);
inq_overflow:
wait_err:
	cambuf_iommu_unmap(&pframe->buf);
	complete(&dev->slice_done);
	complete(&dev->frm_done);
map_err:
	dev->slice_num = 0;
	dev->slice_count = 0;
	dev->dcam_cb_func(DCAM_CB_RET_SRC_BUF, pframe, dev->cb_priv_data);
	return ret;
}

/* TODO: need to be refined */
static int dcam_offline_start_frame(void *param)
{
	int ret = 0;
	int i, loop;
	uint32_t force_ids = DCAM_CTRL_ALL;
	uint32_t loose_val = 0;
	uint32_t val_4in1 = 0;
	struct dcam_pipe_dev *dev = NULL;
	struct camera_frame *pframe = NULL;
	struct dcam_path_desc *path = NULL;
	struct dcam_fetch_info *fetch = NULL;
	struct cam_hw_info *hw = NULL;

	dev = (struct dcam_pipe_dev *)param;

	hw = dev->hw;
	dev->offline = 1;
	pr_debug("enter.dev->idx = %d\n", dev->idx);

	ret = wait_for_completion_interruptible_timeout(
					&dev->frm_done,
					DCAM_OFFLINE_TIMEOUT);
	if (ret == ERESTARTSYS) {
		pr_err("fail to wait as interrupted.\n");
		ret = -EFAULT;
		pframe = camera_dequeue(&dev->in_queue);
		if (pframe == NULL) {
			pr_warn("no frame from in_q. dcam%d\n", dev->idx);
			return 0;
		}
		goto wait_err;
	} else if (ret == 0) {
		pr_err("fail to wait as dcam%d offline timeout.\n", dev->idx);
		ret = -EFAULT;
		pframe = camera_dequeue(&dev->in_queue);
		if (pframe == NULL) {
			pr_warn("no frame from in_q. dcam%d\n", dev->idx);
			return 0;
		}
		goto wait_err;
	}

	if (dev->dcam_slice_mode == CAM_OFFLINE_SLICE_HW) {
		ret = dcam_offline_start_slices_hw(param);
		return ret;
	} else if (dev->dcam_slice_mode == CAM_OFFLINE_SLICE_SW) {
		ret = dcam_offline_start_slices_sw(param);
		return ret;
	}

	fetch = &dev->fetch;

	pframe = camera_dequeue(&dev->in_queue);
	if (pframe == NULL) {
		pr_warn("no frame from in_q. dcam%d\n", dev->idx);
		return 0;
	}

	if (DCAM_FETCH_TWICE(dev)) {
		dev->raw_fetch_count++;
		ret = hw->hw_ops.core_ops.dcam_fetch_block_set(dev);
		if (!DCAM_FIRST_FETCH(dev)) {
			struct camera_frame *frame = NULL;

			frame = camera_dequeue(&dev->proc_queue);
			if (frame) {
				path = &dev->path[DCAM_PATH_BIN];
				ret = camera_enqueue(&path->out_buf_queue, frame);
			}
			pframe->endian = frame->endian;
			pframe->pattern = frame->pattern;
			pframe->width = frame->width;
			pframe->height = frame->height;
		}
	}

	pr_info("frame %p, dcam%d  ch_id %d.  buf_fd %d\n", pframe,
		dev->idx, pframe->channel_id, pframe->buf.mfd[0]);
	pr_info("size %d %d,  endian %d, pattern %d\n",
		pframe->width, pframe->height, pframe->endian, pframe->pattern);

	ret = cambuf_iommu_map(&pframe->buf, CAM_IOMMUDEV_DCAM);
	if (ret) {
		pr_err("fail to map buf to dcam%d iommu.\n", dev->idx);
		goto map_err;
	}

	loop = 0;
	do {
		ret = camera_enqueue(&dev->proc_queue, pframe);
		if (ret == 0)
			break;
		pr_info("wait for proc queue. loop %d\n", loop);

		/* wait for previous frame proccessed done. */
		mdelay(1);
	} while (loop++ < 500);

	if (ret) {
		pr_err("fail to enqueue frame as timeout.\n");
		ret = 0;
		goto inq_overflow;
	}

	/* todo: enable statis path from user config */
	pr_debug("hwsim:rps[%d]\n",dev->rps);

	if (dev->rps == 1) {
		pr_debug("hwsim:offline enable aem\n");
		atomic_set(&dev->path[DCAM_PATH_AEM].user_cnt, 1); /* hwsim first loop need aem statis */
	} else {
		atomic_set(&dev->path[DCAM_PATH_AEM].user_cnt, 0);
	}
	if (dev->is_pdaf) {
		pr_info("offline pdaf\n");
		atomic_set(&dev->path[DCAM_PATH_PDAF].user_cnt, 1);
	}
	atomic_set(&dev->path[DCAM_PATH_AFM].user_cnt, 0);
	atomic_set(&dev->path[DCAM_PATH_AFL].user_cnt, 0);
	atomic_set(&dev->path[DCAM_PATH_HIST].user_cnt, 0);
	atomic_set(&dev->path[DCAM_PATH_LSCM].user_cnt, 0);

	/* prepare frame info for tx done
	 * ASSERT: this dev has no cap_sof
	 */
	dev->index_to_set = pframe->fid;
	if (pframe->sensor_time.tv_sec || pframe->sensor_time.tv_usec) {
		dev->frame_ts[tsid(pframe->fid)].tv_sec =
			pframe->sensor_time.tv_sec;
		dev->frame_ts[tsid(pframe->fid)].tv_nsec =
			pframe->sensor_time.tv_usec * NSEC_PER_USEC;
		dev->frame_ts_boot[tsid(pframe->fid)] = pframe->boot_sensor_time;
		pr_info("frame[%d]\n", pframe->fid);
	}

	for (i = 0; i < DCAM_PATH_MAX; i++) {
		path = &dev->path[i];
		if (atomic_read(&path->user_cnt) < 1 || atomic_read(&path->is_shutoff) > 0)
			continue;
		ret = dcam_path_set_store_frm(dev, path, NULL); /* TODO: */
		if (ret == 0) {
			/* interrupt need > 1 */
			if (i == DCAM_PATH_FULL || i == DCAM_PATH_BIN) {
			        if(dev->rps == 1)
			            loose_val = (loose_val | (dev->is_loose) | (path->is_loose));
			        else
	                            loose_val = ((dev->is_loose) | (path->is_loose));
			}
			path->is_loose = loose_val;
			val_4in1 = ((dev->is_4in1) | (path->is_4in1));
			atomic_set(&path->set_frm_cnt, 1);
			atomic_inc(&path->set_frm_cnt);
			hw->hw_ops.core_ops.path_start(dev, i);
		} else {
			pr_err("fail to set dcam%d path%d store frm\n",
				dev->idx, path->path_id);
			ret = 0;
			goto dequeue;
		}
	}

	/* todo - need to cfg fetch param from input or frame. */
	if(val_4in1 == 1) {
	    if(dev->rps == 1)
	      fetch->is_loose = loose_val;
	  else
	      fetch->is_loose = 0;
	} else
              fetch->is_loose = loose_val;
	pr_info("is_loose =%d",fetch->is_loose);
	fetch->endian = pframe->endian;
	fetch->pattern = pframe->pattern;
	fetch->size.w = pframe->width;
	fetch->size.h = pframe->height;
	fetch->trim.start_x = 0;
	fetch->trim.start_y = 0;
	fetch->trim.size_x = pframe->width;
	fetch->trim.size_y = pframe->height;
	fetch->addr.addr_ch0 = (uint32_t)pframe->buf.iova[0];

	ret = hw->hw_ops.core_ops.dcam_fetch_set(dev);

	mutex_lock(&dev->blk_dcam_pm->lsc.lsc_lock);
	dcam_init_lsc(dev, 0);
	mutex_unlock(&dev->blk_dcam_pm->lsc.lsc_lock);

	/* DCAM_CTRL_COEF will always set in dcam_init_lsc() */
	//force_ids &= ~DCAM_CTRL_COEF;
	hw->hw_ops.core_ops.force_copy(force_ids, dev);
	udelay(500);

	dev->iommu_status = (uint32_t)(-1);
	atomic_set(&dev->state, STATE_RUNNING);
	dev->err_count = 1;
	hw->hw_ops.core_ops.reg_trace(dev->idx, NORMAL_REG_TRACE);

	if (dev->dcamsec_eb)
		pr_warn("camca : dcamsec_eb= %d, fetch disable\n", dev->dcamsec_eb);
	else
		hw->hw_ops.core_ops.fetch_start(hw);

	return 0;

dequeue:
	pframe = camera_dequeue_tail(&dev->proc_queue);
inq_overflow:
	cambuf_iommu_unmap(&pframe->buf);
map_err:
	complete(&dev->frm_done);
wait_err:
	/* return buffer to cam channel shared buffer queue. */
	dev->dcam_cb_func(DCAM_CB_RET_SRC_BUF, pframe, dev->cb_priv_data);
	return 0;
}

static int dcam_offline_thread_loop(void *arg)
{
	struct dcam_pipe_dev *dev = NULL;
	struct cam_thread_info *thrd;
	uint32_t idx = 0;

	if (!arg) {
		pr_err("fail to get valid input ptr\n");
		return -1;
	}

	thrd = (struct cam_thread_info *)arg;
	dev = (struct dcam_pipe_dev *)thrd->ctx_handle;
	idx = dev->idx;

	init_completion(&dev->frm_done);
	complete(&dev->frm_done);
	pr_info("dcam%d\n", dev->idx);
	init_completion(&dev->slice_done);
	complete(&dev->slice_done);
	while (1) {
		if (wait_for_completion_interruptible(
			&thrd->thread_com) == 0) {
			if (atomic_cmpxchg(
					&thrd->thread_stop, 1, 0) == 1) {
				pr_info("dcam%d offline thread stop.\n", idx);
				break;
			}
			pr_debug("thread com done.\n");

			if (thrd->proc_func(dev)) {
				pr_err("fail to start dcam pipe to proc. exit thread\n");
				dev->dcam_cb_func(
					DCAM_CB_DEV_ERR, dev,
					dev->cb_priv_data);
				break;
			}
		} else {
			pr_debug("offline thread exit!");
			break;
		}
	}

	return 0;
}

static int dcam_stop_offline_thread(void *param)
{
	int ret = 0;
	int cnt = 0;
	struct cam_thread_info *thrd;
	struct dcam_pipe_dev *dev;

	thrd = (struct cam_thread_info *)param;
	dev = (struct dcam_pipe_dev *)thrd->ctx_handle;

	if (thrd->thread_task) {
		atomic_set(&thrd->thread_stop, 1);
		complete(&thrd->thread_com);
		while (cnt < 1000) {
			cnt++;
			if (atomic_read(&thrd->thread_stop) == 0)
				break;
			udelay(1000);
		}
		thrd->thread_task = NULL;
		pr_info("offline thread stopped. wait %d ms\n", cnt);
	} else {
		pr_info("dcam%d no offline thread\n", dev->idx);
		return 0;
	}

	/* wait for last frame done */
	ret = wait_for_completion_interruptible_timeout(
					&dev->frm_done,
					DCAM_OFFLINE_TIMEOUT);
	if (ret == -ERESTARTSYS)
		pr_err("interrupt when isp wait\n");
	else if (ret == 0)
		pr_err("dcam%d timeout.\n", dev->idx);
	else
		pr_info("wait time %d\n", ret);

	return 0;
}

static int dcam_create_offline_thread(void *param)
{
	struct dcam_pipe_dev *dev;
	struct cam_thread_info *thrd;
	char thread_name[32] = { 0 };

	dev = (struct dcam_pipe_dev *)param;
	thrd = &dev->thread;
	thrd->ctx_handle = dev;
	thrd->proc_func = dcam_offline_start_frame;
	atomic_set(&thrd->thread_stop, 0);
	init_completion(&thrd->thread_com);

	sprintf(thread_name, "dcam%d_offline", dev->idx);
	thrd->thread_task = kthread_run(dcam_offline_thread_loop,
					thrd, "%s", thread_name);
	if (IS_ERR_OR_NULL(thrd->thread_task)) {
		pr_err("fail to start offline thread for dcam%d\n",
				dev->idx);
		return -EFAULT;
	}

	pr_info("dcam%d offline thread created.\n", dev->idx);
	return 0;
}

/*
 * Helper function to initialize dcam_sync_helper.
 */
static inline void
_init_sync_helper_locked(struct dcam_pipe_dev *dev,
			 struct dcam_sync_helper *helper)
{
	memset(&helper->sync, 0, sizeof(struct dcam_frame_synchronizer));
	helper->enabled = 0;
	helper->dev = dev;
}

/*
 * Initialize frame synchronizer helper.
 */
static inline int dcam_init_sync_helper(struct dcam_pipe_dev *dev)
{
	unsigned long flags = 0;
	int i = 0;

	INIT_LIST_HEAD(&dev->helper_list);

	spin_lock_irqsave(&dev->helper_lock, flags);

	for (i = 0; i < DCAM_SYNC_HELPER_COUNT; i++) {
		_init_sync_helper_locked(dev, &dev->helpers[i]);
		list_add_tail(&dev->helpers[i].list, &dev->helper_list);
	}
	spin_unlock_irqrestore(&dev->helper_lock, flags);

	return 0;
}

/*
 * Enables/Disables frame sync for path_id. Should be called before streaming.
 */
int dcam_if_set_sync_enable(void *handle, int path_id, int enable)
{
	struct dcam_pipe_dev *dev = NULL;
	int ret = 0;

	if (unlikely(!handle)) {
		pr_err("fail to get valid param.\n");
		return -EINVAL;
	}
	dev = (struct dcam_pipe_dev *)handle;

	if (unlikely(!is_path_id(path_id))) {
		pr_err("fail to get valid param path_id: %d\n", path_id);
		return -EINVAL;
	}

	ret = atomic_read(&dev->state);
	if (unlikely(ret != STATE_INIT && ret != STATE_IDLE)) {
		pr_err("fail to get a valid ret, DCAM%u frame sync in %d state\n",
			dev->idx, ret);
		return -EINVAL;
	}

	if (enable)
		dev->helper_enabled |= BIT(path_id);
	else
		dev->helper_enabled &= ~BIT(path_id);

	pr_info("DCAM%u %s %s frame sync\n", dev->idx,
		to_path_name(path_id), enable ? "enable" : "disable");

	return 0;
}

/*
 * Helper function to put dcam_sync_helper.
 */
static inline void
_put_sync_helper_locked(struct dcam_pipe_dev *dev,
			struct dcam_sync_helper *helper)
{
	_init_sync_helper_locked(dev, helper);
	list_add_tail(&helper->list, &dev->helper_list);
}

/*
 * Release frame sync reference for @frame thus dcam_frame_synchronizer data
 * can be recycled for next use.
 */
int dcam_if_release_sync(struct dcam_frame_synchronizer *sync,
			 struct camera_frame *frame)
{
	struct dcam_sync_helper *helper = NULL;
	struct dcam_pipe_dev *dev = NULL;
	unsigned long flags = 0;
	int ret = 0, path_id = 0;
	bool ignore = false;

	if (unlikely(!sync || !frame)) {
		pr_err("fail to get valid param. sync=%p, frame=%p\n", sync, frame);
		return -EINVAL;
	}

	helper = container_of(sync, struct dcam_sync_helper, sync);
	dev = helper->dev;

	for (path_id = 0; path_id < DCAM_PATH_MAX; path_id++) {
		if (frame == sync->frames[path_id])
			break;
	}

	if (unlikely(!is_path_id(path_id))) {
		pr_err("fail to get a valid path_id, DCAM%u can't find path id, fid %u, sync %u\n",
		       dev->idx, frame->fid, sync->index);
		return -EINVAL;
	}

	/* unbind each other */
	frame->sync_data = NULL;
	sync->frames[path_id] = NULL;

	pr_debug("DCAM%u %s release sync, id %u, data 0x%p\n",
		dev->idx, to_path_name(path_id), sync->index, sync);

	spin_lock_irqsave(&dev->helper_lock, flags);
	if (unlikely(!helper->enabled)) {
		ignore = true;
		goto exit;
	}
	helper->enabled &= ~BIT(path_id);
	if (!helper->enabled)
		_put_sync_helper_locked(dev, helper);

exit:
	spin_unlock_irqrestore(&dev->helper_lock, flags);

	if (ignore)
		pr_warn("ignore not enabled sync helper\n");

	return ret;
}

/*
 * Get an empty dcam_sync_helper. Returns NULL if no empty helper remains.
 */
struct dcam_sync_helper *dcam_get_sync_helper(struct dcam_pipe_dev *dev)
{
	struct dcam_sync_helper *helper = NULL;
	unsigned long flags = 0;
	bool running_low = false;

	if (unlikely(!dev)) {
		pr_err("fail to get valid param.\n");
		return NULL;
	}

	spin_lock_irqsave(&dev->helper_lock, flags);
	if (unlikely(list_empty(&dev->helper_list))) {
		running_low = true;
		goto exit;
	}

	helper = list_first_entry(&dev->helper_list,
				  struct dcam_sync_helper, list);
	list_del_init(&helper->list);

exit:
	spin_unlock_irqrestore(&dev->helper_lock, flags);

	if (running_low)
		pr_warn_ratelimited("DCAM%u helper is running low...\n",
				    dev->idx);

	return helper;
}

/*
 * Put an empty dcam_sync_helper.
 *
 * In CAP_SOF, when the requested empty dcam_sync_helper finally not being used,
 * it should be returned to FIFO. This only happens when no buffer is
 * available and all paths are using reserved memory.
 *
 * This is also an code defect in CAP_SOF that should be changed later...
 */
void dcam_put_sync_helper(struct dcam_pipe_dev *dev,
				struct dcam_sync_helper *helper)
{
	unsigned long flags = 0;

	if (unlikely(!dev)) {
		pr_err("fail to get valid param.\n");
		return;
	}

	spin_lock_irqsave(&dev->helper_lock, flags);
	_put_sync_helper_locked(dev, helper);
	spin_unlock_irqrestore(&dev->helper_lock, flags);
}

static int sprd_dcam_get_path(
	void *dcam_handle, int path_id)
{
	struct dcam_pipe_dev *dev;
	struct dcam_path_desc *path = NULL;

	if (!dcam_handle) {
		pr_err("fail to get valid param, dcam_handle=%p\n", dcam_handle);
		return -EFAULT;
	}
	if (path_id < DCAM_PATH_FULL || path_id >= DCAM_PATH_MAX) {
		pr_err("fail to get a valid path_id, path id %d\n", path_id);
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)dcam_handle;
	path = &dev->path[path_id];
	if (atomic_inc_return(&path->user_cnt) > 1) {
		atomic_dec(&path->user_cnt);
		pr_err("fail to get a valid param, dcam%d path %d in use.\n", dev->idx, path_id);
		return -EFAULT;
	}

	camera_queue_init(&path->result_queue, DCAM_RESULT_Q_LEN,
					0, dcam_ret_out_frame);
	camera_queue_init(&path->out_buf_queue, DCAM_OUT_BUF_Q_LEN,
					0, dcam_ret_out_frame);
	camera_queue_init(&path->reserved_buf_queue, DCAM_RESERVE_BUF_Q_LEN,
					0, dcam_destroy_reserved_buf);

	return 0;
}

static int sprd_dcam_put_path(
	void *dcam_handle, int path_id)
{
	int ret = 0;
	struct dcam_pipe_dev *dev;
	struct dcam_path_desc *path = NULL;

	if (!dcam_handle) {
		pr_err("fail to get a valid param,  dcam_handle=%p\n",
				dcam_handle);
		return -EFAULT;
	}
	if (path_id < DCAM_PATH_FULL || path_id >= DCAM_PATH_MAX) {
		pr_err("fail to get a valid param, path id %d\n", path_id);
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)dcam_handle;
	path = &dev->path[path_id];

	if (atomic_read(&path->user_cnt) == 0) {
		pr_debug("fail to get a valid user_cnt, dcam%d path %d is not in use.\n",
					dev->idx, path_id);
		return -EFAULT;
	}

	if (atomic_dec_return(&path->user_cnt) != 0) {
		pr_warn("dcam%d path %d has multi users.\n",
					dev->idx, path_id);
		atomic_set(&path->user_cnt, 0);
	}

	camera_queue_clear(&path->result_queue);
	camera_queue_clear(&path->out_buf_queue);
	camera_queue_clear(&path->reserved_buf_queue);

	pr_info("put dcam%d path %d done\n", dev->idx, path_id);
	return ret;
}

static inline void sprd_dcam_show_frame_info(struct dcam_pipe_dev *dev,
					     struct dcam_path_desc *path,
					     struct camera_frame *frame)
{
	uint32_t size = 0, is_loose = 0;

	is_loose = path->is_loose;
	if (frame->is_compressed)
		size = dcam_if_cal_compressed_size(frame->width,
			frame->height, frame->compress_4bit_bypass);
	else
		size = cal_sprd_raw_pitch(frame->width, is_loose) * frame->height;

	pr_debug("DCAM%u %s frame %u %u size %u %u buf %08lx %08x\n",
		dev->idx, to_path_name(path->path_id),
		frame->is_reserved, frame->is_compressed,
		frame->width, frame->height,
		frame->buf.iova[0], size);
}

static int sprd_dcam_cfg_path(
	void *dcam_handle,
	enum dcam_path_cfg_cmd cfg_cmd,
	int path_id, void *param)
{
	int ret = 0;
	struct dcam_pipe_dev *dev = NULL;
	struct dcam_path_desc *path = NULL;
	struct cam_hw_info *hw = NULL;
	struct camera_frame *pframe = NULL;
	uint32_t lowlux_4in1 = 0;
	uint32_t shutoff = 0;
	unsigned long flag = 0;
	enum dcam_path_state state = DCAM_PATH_IDLE;

	static const char *tb_src[] = {"(4c)raw", "bin-sum"}; /* for log */

	if (!dcam_handle || !param) {
		pr_err("fail to get a valid param, input param: %p, %p\n",
				dcam_handle, param);
		return -EFAULT;
	}
	if (path_id < DCAM_PATH_FULL || path_id >= DCAM_PATH_MAX) {
		pr_err("fail to get a valid param, dcam path id %d\n", path_id);
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)dcam_handle;
	hw = dev->hw;
	path = &dev->path[path_id];

	if (atomic_read(&path->user_cnt) == 0) {
		pr_err("fail to get a valid user_cnt, dcam%d, path %d is not in use.\n",
			dev->idx, path_id);
		return -EFAULT;
	}

	switch (cfg_cmd) {
	case DCAM_PATH_CFG_OUTPUT_RESERVED_BUF:
	case DCAM_PATH_CFG_OUTPUT_BUF:
		pframe = (struct camera_frame *)param;
		ret = cambuf_iommu_map(&pframe->buf, CAM_IOMMUDEV_DCAM);
		if (ret)
			goto exit;

		if (atomic_read(&dev->state) != STATE_RUNNING)
			sprd_dcam_show_frame_info(dev, path, pframe);

		/* is_reserved:
		 *  1:  basic mapping reserved buffer;
		 *  2:  copy of reserved buffer.
		 */
		if (unlikely(cfg_cmd == DCAM_PATH_CFG_OUTPUT_RESERVED_BUF)) {
			int i = 1;
			struct camera_frame *newfrm;

			pframe->is_reserved = 1;
			pframe->priv_data = path;
			ret = camera_enqueue(&path->reserved_buf_queue, pframe);
			if (ret) {
				pr_err("fail to enqueue frame of dcam path %d reserve buffer.\n",
					path_id);
				cambuf_iommu_unmap(&pframe->buf);
				goto exit;
			}

			pr_info("config dcam output reserverd buffer.\n");

			while (i < DCAM_RESERVE_BUF_Q_LEN) {
				newfrm = get_empty_frame();
				if (newfrm) {
					newfrm->is_reserved = 2;
					newfrm->priv_data = path;
					memcpy(&newfrm->buf, &pframe->buf,
						sizeof(pframe->buf));
					ret = camera_enqueue(
						&path->reserved_buf_queue,
						newfrm);
					i++;
				}
			}
		} else {
			pframe->is_reserved = 0;
			pframe->priv_data = dev;
			ret = camera_enqueue(&path->out_buf_queue, pframe);
			if (ret) {
				pr_err("fail to enqueue frame of dcam path %d\n",
					path_id);
				cambuf_iommu_unmap(&pframe->buf);
				goto exit;
			}
			pr_debug("config dcam output buffer.\n");
		}
		break;
	case DCAM_PATH_CFG_SIZE:
		ret = dcam_cfg_path_size(dev, path, param);
		break;
	case DCAM_PATH_CFG_BASE:
		ret = dcam_cfg_path_base(dev, path, param);
		break;
	case DCAM_PATH_CFG_FULL_SOURCE:
		lowlux_4in1 = *(uint32_t *)param;

		if (lowlux_4in1) {
			dev->lowlux_4in1 = 1;
			ret = hw->hw_ops.core_ops.path_src_sel(dev,
				PROCESS_RAW_SRC_SEL);
			dev->skip_4in1 = 1; /* auto copy, so need skip 1 frame */
		} else {
			dev->lowlux_4in1 = 0;
			ret = hw->hw_ops.core_ops.path_src_sel(dev,
				ORI_RAW_SRC_SEL);
			dev->skip_4in1 = 1;
		}
		pr_info("dev%d lowlux %d, skip_4in1 %d, full src: %s\n", dev->idx,
			dev->lowlux_4in1, dev->skip_4in1, tb_src[lowlux_4in1]);
		break;
	case DCAM_PATH_CFG_SHUTOFF:
		shutoff = *(uint32_t *)param;
		atomic_set(&path->is_shutoff, shutoff);
		pr_debug("set path %d shutoff %d\n", path_id, shutoff);
		break;
	case DCAM_PATH_CFG_STATE:
		state = *(uint32_t *)param;
		spin_lock_irqsave(&path->state_lock, flag);
		path->state = state;
		spin_unlock_irqrestore(&path->state_lock, flag);
		break;
	default:
		pr_warn("unsupported command: %d\n", cfg_cmd);
		break;
	}
exit:
	return ret;
}

/* get path rect from register
 */
static int dcam_get_path_rect(struct dcam_pipe_dev *dev, void *param)
{
	struct sprd_img_path_rect *p = (struct sprd_img_path_rect *)param;
	struct dcam_path_desc *path;
	struct dcam_dev_aem_win *aem_win;
	struct isp_img_rect *afm_crop;


	if ((!dev) || (!param)) {
		pr_err("fail to get valid param, dev=%p, param=%p\n", dev, param);
		return -EINVAL;
	}
	path = &dev->path[DCAM_PATH_BIN];
	p->trim_valid_rect.x = path->in_trim.start_x;
	p->trim_valid_rect.y = path->in_trim.start_y;
	p->trim_valid_rect.w = path->in_trim.size_x;
	p->trim_valid_rect.h = path->in_trim.size_y;
	if (!dev->blk_dcam_pm) {
		pr_err("fail to get a valid param\n");
		return -EINVAL;
	}
	aem_win = &(dev->blk_dcam_pm->aem.win_info);
	afm_crop = &(dev->blk_dcam_pm->afm.crop_size);
	p->ae_valid_rect.x = aem_win->offset_x;
	p->ae_valid_rect.y = aem_win->offset_y;
	p->ae_valid_rect.w = aem_win->blk_width * aem_win->blk_num_x;
	p->ae_valid_rect.h = aem_win->blk_height * aem_win->blk_num_y;

	p->af_valid_rect.x = afm_crop->x;
	p->af_valid_rect.y = afm_crop->y;
	p->af_valid_rect.w = afm_crop->w;
	p->af_valid_rect.h = afm_crop->h;
#if	0
	/* trim rect */
	val = DCAM_REG_RD(dev->id, DCAM_BIN_CROP_START);
	if (val & (1 << 31)) {
		param->trim_valid_rect.x = val & 0x1FFF; /* b12:b0 */
		param->trim_valid_rect.y = (val >> 16) & 0x1FFF; /* b28:b16 */
		val = DCAM_REG_RD(dev->id, ISP_AFM_CROP_SIZE);
		param->trim_valid_rect.w = val & 0x1FFF;
		param->trim_valid_rect.h = (val >> 16) & 0x1FFF;
	} else {

	}

	/* aem */
	val = DCAM_REG_RD(dev->idx, DCAM_AEM_OFFSET);
	param->ae_valid_rect.x = val & 0x1FFF;
	param->ae_valid_rect.y = (val >> 16) & 0x1FFF;
	val = DCAM_REG_RD(dev->idx, DCAM_AEM_BLK_NUM);
	blk_num_w = val & 0xFF;
	blk_num_h = (val >> 8) 0xFF;
	val = DCAM_REG_RD(dev->idx, DCAM_AEM_BLK_SIZE);
	param->ae_valid_rect.w = (val & 0xFF) * blk_num_w;
	param->ae_valid_rect.h = ((val >> 8) & 0xFF) * blk_num_h;

	/* afm */
	val = DCAM_REG_RD(dev->idx, ISP_RAW_AFM_CROP_START);
	param->af_valid_rect.x = val & 0x1FFF;
	param->af_valid_rect.y = (val >> 16) & 0x1FFF;
	val = DCAM_REG_RD(dev->idx, ISP_RAW_AFM_CROP_SIZE);
	param->af_valid_rect.w = val & 0x1FFF;
	param->af_valid_rect.h = (val >> 16) & 0x1FFF;
#endif
	return 0;
}

/* offline process frame */
static int sprd_dcam_proc_frame(
		void *dcam_handle,  void *param)
{
	int ret = 0;
	struct dcam_pipe_dev *dev = NULL;
	struct camera_frame *pframe;

	if (!dcam_handle || !param) {
		pr_err("fail to get a valid param, dcam_handle=%p, param=%p\n", dcam_handle, param);
		return -EFAULT;
	}
	dev = (struct dcam_pipe_dev *)dcam_handle;

	pr_debug("dcam%d offline proc frame!\n", dev->idx);
	/* if enable, 4in1 capture once more then dcam1 can't run
	 * if (atomic_read(&dev->state) == STATE_RUNNING) {
	 *	pr_err("DCAM%u started for online\n", dev->idx);
	 *	return -EFAULT;
	 * }
	 */
	pframe = (struct camera_frame *)param;
	pframe->priv_data = dev;

	if(dev->slice_count != 0) {
		if (dev->dcam_slice_mode == CAM_OFFLINE_SLICE_HW)
			return -EFAULT;
		else {
			complete(&dev->thread.thread_com);
			return ret;
		}
	}

	ret = camera_enqueue(&dev->in_queue, pframe);
	if (ret == 0)
		complete(&dev->thread.thread_com);
	else
		pr_err("fail to enqueue frame to dev->in_queue, ret = %d\n", ret);

	return ret;
}

static int sprd_dcam_ioctrl(void *dcam_handle,
	enum dcam_ioctrl_cmd cmd, void *param)
{
	int ret = 0;
	struct dcam_pipe_dev *dev = NULL;
	struct dcam_mipi_info *cap = NULL;
	struct dcam_path_desc *path = NULL;
	struct camera_frame *frame = NULL;
	int *fbc_mode = NULL;

	if (!dcam_handle) {
		pr_err("fail to get valid input ptr\n");
		return -EFAULT;
	}
	dev = (struct dcam_pipe_dev *)dcam_handle;

	if (unlikely(atomic_read(&dev->state) == STATE_INIT)) {
		pr_err("fail to get valid dev state of DCAM%d\n", dev->idx);
		return -EINVAL;
	}

	switch (cmd) {
	case DCAM_IOCTL_CFG_CAP:
		cap = &dev->cap_info;
		memcpy(cap, param, sizeof(struct dcam_mipi_info));
		dev->is_4in1 = cap->is_4in1;
		dev->dcam_slice_mode = cap->dcam_slice_mode;
		dev->slice_count = 0;
		break;
	case DCAM_IOCTL_CFG_STATIS_BUF:
		ret = dcam_cfg_statis_buffer(dev, param);
		break;
	case DCAM_IOCTL_CFG_RESERV_STATSBUF:
		ret = cfg_reserved_stat_buffer(dev, param);
		break;
	case DCAM_IOCTL_CFG_START:
		/* sign of isp mw starting to config block param. */
		ret = cambuf_iommu_map(
				&dev->blk_dcam_pm->lsc.buf,
				CAM_IOMMUDEV_DCAM);
		if (ret)
			dev->blk_dcam_pm->lsc.buf.iova[0] = 0L;
		break;
	case DCAM_IOCTL_CFG_STOP:
		cambuf_iommu_unmap(&dev->blk_dcam_pm->lsc.buf);
		break;
	case DCAM_IOCTL_INIT_STATIS_Q:
		ret = init_statis_bufferq(dev);
		break;
	case DCAM_IOCTL_DEINIT_STATIS_Q:
		ret = deinit_statis_bufferq(dev);
		put_reserved_buffer(dev);
		unmap_statis_buffer(dev);
		break;
	case DCAM_IOCTL_CFG_EBD:
		dev->is_ebd = 1;
		ret = dev->hw->hw_ops.core_ops.ebd_set(dev->idx, param);
		break;
	case DCAM_IOCTL_CFG_SEC:
		ret = dcam_cfg_dcamsec(dev, param);
		break;
	case DCAM_IOCTL_CFG_FBC:
		fbc_mode = (int *)param;
		/* update compressed flag for reserved buffer */
		if (*fbc_mode == DCAM_FBC_FULL_14_BIT ||
			*fbc_mode == DCAM_FBC_FULL_10_BIT)
			path = &dev->path[DCAM_PATH_FULL];
		else if (*fbc_mode == DCAM_FBC_BIN_14_BIT ||
			*fbc_mode == DCAM_FBC_BIN_10_BIT)
			path = &dev->path[DCAM_PATH_BIN];
		if (!path) {
			pr_info("Unsupport fbc mode %d\n", *fbc_mode);
			return 0;
		}
		if (dev->hw->hw_ops.core_ops.dcam_fbc_ctrl)
			dev->hw->hw_ops.core_ops.dcam_fbc_ctrl(
				dev->idx, *fbc_mode);

		list_for_each_entry(frame, &path->reserved_buf_queue.head, list) {
			if (!frame)
				break;
			else {
				frame->is_compressed = 1;
				if (*fbc_mode == DCAM_FBC_FULL_14_BIT ||
					*fbc_mode == DCAM_FBC_BIN_14_BIT)
						frame->compress_4bit_bypass = 0;
			}
		}
		break;
	case DCAM_IOCTL_CFG_RPS:
		ret = dcam_cfg_rps(dev, param);
		break;
	case DCAM_IOCTL_CFG_REPLACER:
		dev->replacer = (struct dcam_image_replacer *)param;
		break;
	case DCAM_IOCTL_GET_PATH_RECT:
		ret = dcam_get_path_rect(dev, param);
		break;
	case DCAM_IOCTL_CFG_STATIS_BUF_SKIP:
		ret = dcam_cfg_statis_buffer_skip(dev, param);
		break;
	default:
		pr_err("fail to get a known cmd: %d\n", cmd);
		ret = -EFAULT;
		break;
	}

	return ret;
}

static int sprd_dcam_cfg_param(void *dcam_handle, void *param)
{
	int ret = 0;
	uint32_t i = 0;
	func_dcam_cfg_param cfg_fun_ptr = NULL;
	struct dcam_pipe_dev *dev = NULL;
	struct isp_io_param *io_param;
	struct dcam_dev_param *pm = NULL;
	struct dcam_cfg_entry *cfg_entry = NULL;
	struct cam_hw_core_ops *ops = NULL;

	if (!dcam_handle || !param) {
		pr_err("fail to get valid param, dcam_handle=%p, param=%p\n", dcam_handle, param);
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)dcam_handle;
	ops = &dev->hw->hw_ops.core_ops;
	pm = dev->blk_dcam_pm;
	if (!pm) {
		pr_err("fail to check param\n");
		return -EFAULT;
	}
	pm->idx = dev->idx;
	pm->dev = dev;
	io_param = (struct isp_io_param *)param;

	i = io_param->sub_block - DCAM_BLOCK_BASE;
	cfg_entry = ops->block_func_get(i, DCAM_BLOCK_TYPE);
	if (cfg_entry != NULL &&
		cfg_entry->sub_block == io_param->sub_block) {
		cfg_fun_ptr = cfg_entry->cfg_func;
	} else { /* if not, some error */
		pr_err("fail to check param, sub_block = %d, error\n", io_param->sub_block);
	}
	if (cfg_fun_ptr == NULL) {
		pr_debug("block %d not supported.\n", io_param->sub_block);
		goto exit;
	}

	if (dev->dcam_slice_mode && dev->slice_count > 0 && (io_param->sub_block != DCAM_BLOCK_LSC))
		return 0;

	if(io_param->sub_block == DCAM_BLOCK_LSC)
		mutex_lock(&dev->blk_dcam_pm->lsc.lsc_lock);

	pm->dcam_slice_mode = dev->dcam_slice_mode;
	ret = cfg_fun_ptr(io_param, pm);

	if(io_param->sub_block == DCAM_BLOCK_LSC)
		mutex_unlock(&dev->blk_dcam_pm->lsc.lsc_lock);

	if ((io_param->sub_block == DCAM_BLOCK_LSC) &&
		(dev->offline == 0) &&
		(atomic_read(&dev->state) == STATE_RUNNING)) {
		dcam_update_lsc(dev);
	}

exit:
	return ret;
}


static int sprd_dcam_set_cb(void *dcam_handle,
		dcam_dev_callback cb, void *priv_data)
{
	int ret = 0;
	struct dcam_pipe_dev *dev = NULL;

	if (!dcam_handle || !cb || !priv_data) {
		pr_err("fail to get valid param, dcam_handle=%p, cb=%p, priv_data=%p\n",
			dcam_handle, cb, priv_data);
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)dcam_handle;
	dev->dcam_cb_func = cb;
	dev->cb_priv_data = priv_data;

	return ret;
}

static int sprd_dcam_dev_start(void *dcam_handle, int online)
{
	int ret = 0;
	int i;
	uint32_t force_ids = DCAM_CTRL_ALL;
	struct dcam_pipe_dev *dev = NULL;
	struct dcam_sync_helper *helper = NULL;
	struct dcam_path_desc *path = NULL;
	struct cam_hw_info *hw = NULL;
	unsigned long flag;

	if (!dcam_handle) {
		pr_err("fail to get valid dcam_pipe_dev\n");
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)dcam_handle;
	hw = dev->hw;
	dev->offline = !online;

	if (!online) {
		ret = dcam_create_offline_thread(dev);
		if (ret) {
			pr_err("fail to creat offline thread\n");
			return ret;
		}
		if (dev->idx < DCAM_ID_2)
			atomic_dec(&s_dcam_working);
		atomic_set(&dev->state, STATE_RUNNING);
		return ret;
	}

	ret = atomic_read(&dev->state);
	if (unlikely(ret != STATE_IDLE)) {
		pr_err("fail to get a valid state, starting DCAM%u in state %d\n", dev->idx, ret);
		return -EINVAL;
	}

	pr_info("DCAM%u start: %p, state = %d\n", dev->idx, dev, atomic_read(&dev->state));


	ret = dcam_init_sync_helper(dev);
	if (ret < 0) {
		pr_err("fail to init DCAM%u sync helper, ret: %d\n",
			dev->idx, ret);
		return ret;
	}

	/* enable statistic paths  */
	if (dev->blk_dcam_pm->aem.bypass == 0)
		atomic_set(&dev->path[DCAM_PATH_AEM].user_cnt, 1);
	if (dev->blk_dcam_pm->lscm.bypass == 0)
		atomic_set(&dev->path[DCAM_PATH_LSCM].user_cnt, 1);
	if (dev->blk_dcam_pm->afm.bypass == 0)
		atomic_set(&dev->path[DCAM_PATH_AFM].user_cnt, 1);
	if (dev->blk_dcam_pm->afl.bypass == 0)
		atomic_set(&dev->path[DCAM_PATH_AFL].user_cnt, 1);
	if (dev->blk_dcam_pm->hist.bayerHist_info.hist_bypass == 0)
		atomic_set(&dev->path[DCAM_PATH_HIST].user_cnt, 1);

	if (dev->is_pdaf)
		atomic_set(&dev->path[DCAM_PATH_PDAF].user_cnt, 1);
	if (dev->is_3dnr)
		atomic_set(&dev->path[DCAM_PATH_3DNR].user_cnt, 1);

	if (dev->is_ebd)
		atomic_set(&dev->path[DCAM_PATH_VCH2].user_cnt, 1);

	dev->frame_index = 0;
	dev->index_to_set = 0;
	dev->iommu_status = 0;
	memset(dev->frame_ts, 0,
	       sizeof(dev->frame_ts[0]) * DCAM_FRAME_TIMESTAMP_COUNT);
	memset(dev->frame_ts_boot, 0,
	       sizeof(dev->frame_ts_boot[0]) * DCAM_FRAME_TIMESTAMP_COUNT);

	dev->helper_enabled = 0;
	if (!dev->slowmotion_count) {
		/* enable frame sync for 3DNR in normal mode */
		dcam_if_set_sync_enable(dev, DCAM_PATH_FULL, 1);
		dcam_if_set_sync_enable(dev, DCAM_PATH_BIN, 1);
		dcam_if_set_sync_enable(dev, DCAM_PATH_3DNR, 1);

		helper = dcam_get_sync_helper(dev);
	}

	ret = hw->hw_ops.core_ops.mipi_cap_set(dev);
	if (ret < 0) {
		pr_err("fail to set DCAM%u mipi cap\n", dev->idx);
		return ret;
	}

	for (i = 0; i < DCAM_PATH_MAX; i++) {
		path = &dev->path[i];
		atomic_set(&path->set_frm_cnt, 0);

		if (atomic_read(&path->user_cnt) < 1 || atomic_read(&path->is_shutoff) > 0)
			continue;

		if (path->path_id == DCAM_PATH_FULL) {
			spin_lock_irqsave(&path->state_lock, flag);
			if (path->state == DCAM_PATH_PAUSE) {
				hw->hw_ops.core_ops.path_start(dev, i);
				hw->hw_ops.core_ops.path_pause(dev->idx,
					path->path_id);
				spin_unlock_irqrestore(&path->state_lock, flag);
				continue;
			}
			spin_unlock_irqrestore(&path->state_lock, flag);
		}

		ret = dcam_path_set_store_frm(dev, path, helper);
		if (ret < 0) {
			pr_err("fail to set frame for DCAM%u %s , ret %d\n",
			       dev->idx, to_path_name(path->path_id), ret);
			return ret;
		}

		if (atomic_read(&path->set_frm_cnt) > 0)
			hw->hw_ops.core_ops.path_start(dev, i);
	}

	if (dev->is_4in1 == 0)
		dcam_init_lsc(dev, 1);
	/* DCAM_CTRL_COEF will always set in dcam_init_lsc() */
	//force_ids &= ~DCAM_CTRL_COEF;
	hw->hw_ops.core_ops.force_copy(force_ids, dev);

	if (helper) {
		if (helper->enabled)
			helper->sync.index = dev->index_to_set;
		else
			dcam_put_sync_helper(dev, helper);
	}

	/* TODO: change AFL trigger */
	atomic_set(&dev->path[DCAM_PATH_AFL].user_cnt, 0);

	dcam_reset_int_tracker(dev->idx);
	hw->hw_ops.core_ops.start(dev);

	if (dev->is_4in1 == 0)
		hw->hw_ops.core_ops.sram_ctrl_set(dev, 1);

	if (dev->idx < DCAM_ID_2)
		atomic_inc(&s_dcam_working);
	atomic_set(&dev->state, STATE_RUNNING);
	hw->hw_ops.core_ops.reg_trace(dev->idx, NORMAL_REG_TRACE);
	dev->auto_cpy_id = 0;
	dev->err_count = 1;
	pr_info("dcam%d done state = %d\n", dev->idx, atomic_read(&dev->state));
	return ret;
}

static int sprd_dcam_dev_stop(void *dcam_handle)
{
	int ret = 0, state = 0;
	int i = 0;
	struct dcam_pipe_dev *dev = NULL;
	struct dcam_path_desc *path = NULL;

	if (!dcam_handle) {
		pr_err("fail to get valid input ptr\n");
		return -EFAULT;
	}
	dev = (struct dcam_pipe_dev *)dcam_handle;

	if (dev->offline) {
		ret = dcam_stop_offline_thread(&dev->thread);
		if (ret) {
			pr_err("fail to stop offline thread\n");
		}
	}

	state = atomic_read(&dev->state);
	if (unlikely(state == STATE_INIT) || unlikely(state == STATE_IDLE)) {
		pr_warn("DCAM%d not started yet\n", dev->idx);
		return -EINVAL;
	}

	dev->hw->hw_ops.core_ops.stop(dev);
	dev->hw->hw_ops.dcam_soc_ops.reset(dev->hw, &dev->idx);

	if (0) {
		int i;

		for (i = 0; i < DCAM_FRAME_TIMESTAMP_COUNT; i++)
			pr_info("DCAM%u i=%02d t=%lld\n",
				dev->idx, i, dev->frame_ts_boot[i]);
	}

	dcam_dump_int_tracker(dev->idx);
	dcam_reset_int_tracker(dev->idx);

	if (dev->idx < DCAM_ID_2)
		atomic_dec(&s_dcam_working);
	atomic_set(&dev->state, STATE_IDLE);

	dev->blk_dcam_pm->aem.bypass = 1;
	dev->blk_dcam_pm->afm.bypass = 1;
	dev->blk_dcam_pm->afl.bypass = 1;
	dev->blk_dcam_pm->hist.bayerHist_info.hist_bypass = 1;
	dev->blk_dcam_pm->lscm.bypass = 1;
	dev->is_pdaf = dev->is_3dnr = dev->is_4in1 = 0;
	dev->err_count = 0;
	dev->offline = 0;

	for (i  = 0; i < DCAM_PATH_MAX; i++) {
		path = &dev->path[i];
		atomic_set(&path->is_shutoff, 0);
	}
	pr_info("stop dcam pipe dev[%d] state = %d!\n", dev->idx, atomic_read(&dev->state));
	return ret;
}

/*
 * Open dcam_pipe_dev and hardware dcam_if IP.
 */
static int sprd_dcam_dev_open(void *dcam_handle)
{
	int ret = 0;
	int i, iommu_enable = 0;
	struct dcam_pipe_dev *dev = NULL;
	struct dcam_path_desc *path = NULL;
	struct cam_hw_info *hw = NULL;

	if (!dcam_handle) {
		pr_err("fail to get valid input ptr\n");
		return -EFAULT;
	}
	dev = (struct dcam_pipe_dev *)dcam_handle;

	ret = atomic_read(&dev->state);
	if (unlikely(ret != STATE_INIT)) {
		pr_err("fail to get a valid dev state, DCAM%u, state=%d\n",
			dev->idx, ret);
		return -EINVAL;
	}

	hw = dev->hw;
	memset(&dev->path[0], 0, sizeof(dev->path));
	for (i  = 0; i < DCAM_PATH_MAX; i++) {
		path = &dev->path[i];
		path->path_id = i;
		atomic_set(&path->user_cnt, 0);
		atomic_set(&path->set_frm_cnt, 0);
		atomic_set(&path->is_shutoff, 0);
		spin_lock_init(&path->size_lock);
		spin_lock_init(&path->state_lock);

		if (path->path_id == DCAM_PATH_BIN) {
			path->rds_coeff_size = RDS_COEF_TABLE_SIZE;
			path->rds_coeff_buf = kzalloc(path->rds_coeff_size, GFP_KERNEL);
			if (path->rds_coeff_buf == NULL) {
				path->rds_coeff_size = 0;
				pr_err("fail to alloc rds coeff buffer.\n");
				ret = -ENOMEM;
				goto exit;
			}
		}
	}

	dev->blk_dcam_pm =
		kzalloc(sizeof(struct dcam_dev_param), GFP_KERNEL);
	if (dev->blk_dcam_pm == NULL) {
		pr_err("fail to alloc dcam blk param.\n");
		ret = -ENOMEM;
		goto exit;
	}
	pr_info("alloc buf for all dcam pm success, %p, len %d\n",
			dev->blk_dcam_pm, (int)sizeof(struct dcam_dev_param));
	dev->blk_dcam_pm->aem.bypass = 1;
	dev->blk_dcam_pm->afm.bypass = 1;
	dev->blk_dcam_pm->afl.bypass = 1;
	dev->blk_dcam_pm->lscm.bypass = 1;
	dev->blk_dcam_pm->hist.bayerHist_info.hist_bypass = 1;
	mutex_init(&dev->blk_dcam_pm->lsc.lsc_lock);

	if (get_iommu_status(CAM_IOMMUDEV_DCAM) == 0)
		iommu_enable = 1;
	ret = cambuf_alloc(&dev->blk_dcam_pm->lsc.buf,
			DCAM_LSC_BUF_SIZE, 0, iommu_enable);
	ret |= cambuf_kmap(&dev->blk_dcam_pm->lsc.buf);
	if (ret) {
		ret = -ENOMEM;
		goto exit;
	}

	ret = dcam_hw_init(dev);
	if (ret) {
		pr_err("fail to open DCAM%u, ret: %d\n",
			dev->idx, ret);
		goto exit;
	}

	if (atomic_inc_return(&s_dcam_axi_opened) == 1)
		hw->hw_ops.dcam_soc_ops.axi_init(dev);
	ret = hw->hw_ops.dcam_soc_ops.reset(hw, &dev->idx);
	if (ret)
		goto reset_fail;

	camera_queue_init(&dev->in_queue, DCAM_IN_Q_LEN,
				0, dcam_ret_src_frame);
	camera_queue_init(&dev->proc_queue, DCAM_PROC_Q_LEN,
				0, dcam_ret_src_frame);

	atomic_set(&dev->state, STATE_IDLE);
	spin_lock_init(&dev->glb_reg_lock);

	/* for debugfs */
	atomic_inc(&s_dcam_opened[dev->idx]);

	pr_info("open dcam pipe dev[%d]!\n", dev->idx);

	return 0;

reset_fail:
	atomic_dec(&s_dcam_axi_opened);
	ret = dcam_hw_deinit(dev);
exit:
	if (dev->blk_dcam_pm) {
		mutex_destroy(&dev->blk_dcam_pm->lsc.lsc_lock);
		cambuf_kunmap(&dev->blk_dcam_pm->lsc.buf);
		cambuf_free(&dev->blk_dcam_pm->lsc.buf);
		kfree(dev->blk_dcam_pm);
		dev->blk_dcam_pm = NULL;
	}
	if (dev->path[DCAM_PATH_BIN].rds_coeff_buf) {
		kfree(dev->path[DCAM_PATH_BIN].rds_coeff_buf);
		dev->path[DCAM_PATH_BIN].rds_coeff_buf = NULL;
		dev->path[DCAM_PATH_BIN].rds_coeff_size = 0;
	}
	pr_info("fail to open dcam pipe dev[%d]!\n", dev->idx);

	return ret;
}

/*
 * Close dcam_pipe_dev and hardware dcam_if IP.
 */
int sprd_dcam_dev_close(void *dcam_handle)
{
	int ret = 0;
	struct dcam_pipe_dev *dev = NULL;

	if (!dcam_handle) {
		pr_err("fail to get valid input ptr\n");
		return -EINVAL;
	}

	dev = (struct dcam_pipe_dev *)dcam_handle;

	if (unlikely(atomic_read(&dev->state) == STATE_INIT)) {
		pr_err("fail to get dev state, DCAM%u already closed\n", dev->idx);
		return -EINVAL;
	}

	camera_queue_clear(&dev->in_queue);
	camera_queue_clear(&dev->proc_queue);

	if (dev->blk_dcam_pm) {
		mutex_destroy(&dev->blk_dcam_pm->lsc.lsc_lock);
		cambuf_kunmap(&dev->blk_dcam_pm->lsc.buf);
		cambuf_free(&dev->blk_dcam_pm->lsc.buf);
		if(dev->blk_dcam_pm->lsc.weight_tab){
			kfree(dev->blk_dcam_pm->lsc.weight_tab);
			dev->blk_dcam_pm->lsc.weight_tab = NULL;
		}
		kfree(dev->blk_dcam_pm);
		dev->blk_dcam_pm = NULL;
	}
	if (dev->path[DCAM_PATH_BIN].rds_coeff_buf) {
		kfree(dev->path[DCAM_PATH_BIN].rds_coeff_buf);
		dev->path[DCAM_PATH_BIN].rds_coeff_buf = NULL;
		dev->path[DCAM_PATH_BIN].rds_coeff_size = 0;
	}

	ret = dcam_hw_deinit(dev);

	atomic_set(&dev->state, STATE_INIT);
	/* for debugfs */
	atomic_dec(&s_dcam_opened[dev->idx]);
	atomic_dec(&s_dcam_axi_opened);

	pr_info("close dcam pipe dev[%d]!\n", dev->idx);

	return ret;
}

/*
 * Operations for this dcam_pipe_dev.
 */
static struct dcam_pipe_ops s_dcam_pipe_ops = {
	.open = sprd_dcam_dev_open,
	.close = sprd_dcam_dev_close,
	.start = sprd_dcam_dev_start,
	.stop = sprd_dcam_dev_stop,
	.get_path = sprd_dcam_get_path,
	.put_path = sprd_dcam_put_path,
	.cfg_path = sprd_dcam_cfg_path,
	.ioctl = sprd_dcam_ioctrl,
	.cfg_blk_param = sprd_dcam_cfg_param,
	.proc_frame = sprd_dcam_proc_frame,
	.set_callback = sprd_dcam_set_cb,
};

/*
 * Get supported operations for a dcam_pipe_dev.
 */
struct dcam_pipe_ops *dcam_if_get_ops(void)
{
	return &s_dcam_pipe_ops;
}

uint32_t dcam_if_get_open_count(void)
{
	return atomic_read(&s_dcam_axi_opened);
}

static DEFINE_MUTEX(s_dcam_dev_mutex);
static struct dcam_pipe_dev *s_dcam_dev[DCAM_ID_MAX];

/*
 * Create a dcam_pipe_dev for designated cam_hw_info.
 */
void *dcam_if_get_dev(uint32_t idx, struct cam_hw_info *hw)
{
	struct dcam_pipe_dev *dev = NULL;

	if (idx >= DCAM_ID_MAX) {
		pr_err("fail to get valid DCAM index: %u\n", idx);
		return NULL;
	}

	if (unlikely(!hw)) {
		pr_err("fail to get valid param hw\n");
		return NULL;
	}

	mutex_lock(&s_dcam_dev_mutex);
	if (s_dcam_dev[idx]) {
		pr_err("fail to get valid dcam dev, dcam %d already in use. pipe dev: %p\n",
			idx, s_dcam_dev[idx]);
		goto exit;
	}

	dev = vzalloc(sizeof(struct dcam_pipe_dev));
	if (!dev) {
		pr_err("fail to alloc memory for DCAM%u\n", idx);
		goto exit;
	}

	dev->idx = idx;
	dev->hw = hw;
	dev->is_pdaf = 0;

	/* frame sync helper */
	spin_lock_init(&dev->helper_lock);

	atomic_set(&dev->state, STATE_INIT);

	s_dcam_dev[idx] = dev;

exit:
	mutex_unlock(&s_dcam_dev_mutex);

	if (dev == NULL)
		pr_err("fail to get DCAM%u pipe dev\n", idx);
	else
		pr_info("get DCAM%u pipe dev: %p\n", idx, dev);

	return dev;
}

/*
 * Release a dcam_pipe_dev.
 */
int dcam_if_put_dev(void *dcam_handle)
{
	uint32_t idx = 0;
	int ret = 0;
	struct dcam_pipe_dev *dev = NULL;

	if (!dcam_handle) {
		pr_err("fail to get valid input ptr\n");
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)dcam_handle;
	idx = dev->idx;
	if (idx >= DCAM_ID_MAX) {
		pr_err("fail to get valid dcam idx, index: %u\n", idx);
		return -EINVAL;
	}

	mutex_lock(&s_dcam_dev_mutex);
	if (dev != s_dcam_dev[idx]) {
		pr_err("fail to get matched dev: %p, %p\n",
			dev, s_dcam_dev[idx]);
		mutex_unlock(&s_dcam_dev_mutex);
		return -EFAULT;
	}

	ret = atomic_read(&dev->state);
	if (unlikely(ret != STATE_INIT)) {
		pr_warn("releasing DCAM%u in state %d may cause leak\n",
			dev->idx, ret);
	}
	pr_info("put DCAM%u pipe dev: %p\n", idx, dev);
	vfree(dev);
	s_dcam_dev[idx] = NULL;

	mutex_unlock(&s_dcam_dev_mutex);

	return ret;
}

int dcam_hwsim_extra(enum dcam_id idx)
{
	DCAM_REG_MWR(idx, ISP_BPC_PARAM, ((1 & 0x1) << 7), ((0 & 0x1) << 7));
	pr_info("bpc<0x%x>[0x%x]\n", 0x0200, DCAM_REG_RD(idx, 0x0200));

#if 0

		uint32_t val;

		val = (1 & 0x1) |
		((1 & 0x1) << 1) |
		((1 & 0x1) << 2) |
		((1 & 0x1) << 3);
		DCAM_REG_MWR(idx, ISP_BPC_PARAM, 0xF, val);

		pr_info("blc\n");
		DCAM_REG_MWR(idx, DCAM_BLC_PARA_R_B, BIT_31, 1 << 31);

		pr_info("awb \n");
		DCAM_REG_MWR(idx, ISP_AWBC_GAIN0, BIT_31, 1 << 31);

		pr_info("lsc \n");
		DCAM_REG_MWR(idx, DCAM_LENS_LOAD_ENABLE, BIT_0, 1);

		pr_info("rgbg \n");
		DCAM_REG_MWR(idx, ISP_RGBG_YRANDOM_PARAMETER0, BIT_0, 1);

		pr_info("afl \n");
		DCAM_REG_MWR(idx, ISP_AFL_FRM_CTRL0, BIT_0, 1);
		DCAM_REG_MWR(idx, ISP_AFL_PARAM0, BIT_1, 1 << 1);

		pr_info("rgbg_yrandom\n");
		DCAM_REG_MWR(idx, ISP_RGBG_YRANDOM_PARAMETER0, BIT_1, 1 << 1);
#endif

#if 0
		val = ((0 & 1) << 3) | (1 & 1);

		pr_info("ppi ppi_phase_map_corr_en\n");
		DCAM_REG_MWR(idx, ISP_PPI_PARAM, BIT_3 | BIT_0, val);
#endif

		return 0;
}

/* return the number of how many buf in the out_buf_queue */
uint32_t get_outbuf_queue_cnt(void *dev, int path_id)
{
	struct dcam_path_desc *path;

	path = &(((struct dcam_pipe_dev *)dev)->path[path_id]);

	return camera_queue_cnt(&path->out_buf_queue);
}

