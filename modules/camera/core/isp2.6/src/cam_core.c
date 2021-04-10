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

#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/miscdevice.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/platform_device.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/sprd_iommu.h>
#include <linux/sprd_ion.h>

#include <sprd_mm.h>
#include <sprd_isp_hw.h>
#include "sprd_img.h"
#include "cam_trusty.h"

#include "cam_debugger.h"
#include "isp_interface.h"
#include "flash_interface.h"

#include "sprd_sensor_drv.h"
#include "dcam_reg.h"
#include "csi_api.h"
#include "dcam_core.h"

#ifdef CONFIG_COMPAT
#include "compat_cam_drv.h"
#endif

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "CAM_CORE: %d %d %s : "\
	fmt, current->pid, __LINE__, __func__

#define IMG_DEVICE_NAME			"sprd_image"
#define CAMERA_TIMEOUT			5000
#define THREAD_STOP_TIMEOUT		3000


#define  CAM_COUNT  CAM_ID_MAX
/* TODO: extend this for slow motion dev */
#define  CAM_SHARED_BUF_NUM  16
#define  CAM_FRAME_Q_LEN   48
#define  CAM_IRQ_Q_LEN        16
#define  CAM_STATIS_Q_LEN   16
#define  CAM_ZOOM_COEFF_Q_LEN   10

/* TODO: tuning ratio limit for power/image quality */
#define MAX_RDS_RATIO 3
#define RATIO_SHIFT 16

#define ISP_PATHID_BITS 8
#define ISP_PATHID_MASK 0x3
#define ISP_CTXID_OFFSET ISP_PATHID_BITS
#define ISP_SLICE_OVERLAP_W_MAX 64
#define DCAM_4IN1_FRAMES 16
#define ALIGN_UP(a, x)	(((a) + (x) - 1) & (~((x) - 1)))

/* TODO: need to pass the num to driver by hal */
#define CAP_NUM_COMMON 1

/* TODO: set superzoom coeff default val */
#define SUPERZOOM_DEFAULT_COEFF	4
#define SUPERZOOM_COEFF_UP_MAX	4

#define PRE_RDS_OUT 3264

enum camera_module_state {
	CAM_INIT = 0,
	CAM_IDLE,
	CAM_CFG_CH,
	CAM_STREAM_ON,
	CAM_STREAM_OFF,
	CAM_RUNNING,
	CAM_ERROR,
};

/* Static Variables Declaration */
static struct camera_format output_img_fmt[] = {
	{ /*ISP_STORE_UYVY = 0 */
		.name = "4:2:2, packed, UYVY",
		.fourcc = IMG_PIX_FMT_UYVY,
		.depth = 16,
	},
	{ /* ISP_STORE_YUV422_3FRAME,*/
		.name = "YUV 4:2:2, planar, (Y-Cb-Cr)",
		.fourcc = IMG_PIX_FMT_YUV422P,
		.depth = 16,
	},
	{ /*ISP_STORE_YUV420_2FRAME*/
		.name = "YUV 4:2:0 planar (Y-CbCr)",
		.fourcc = IMG_PIX_FMT_NV12,
		.depth = 12,
	},
	{ /* ISP_STORE_YVU420_2FRAME,*/
		.name = "YVU 4:2:0 planar (Y-CrCb)",
		.fourcc = IMG_PIX_FMT_NV21,
		.depth = 12,
	},
	{ /*ISP_STORE_YUV420_3FRAME,*/
		.name = "YUV 4:2:0 planar (Y-Cb-Cr)",
		.fourcc = IMG_PIX_FMT_YUV420,
		.depth = 12,
	},
	{
		.name = "RawRGB",
		.fourcc = IMG_PIX_FMT_GREY,
		.depth = 8,
	},
};

struct camera_group;
int s_dbg_superzoom_coeff = -1;

/* user set information for camera module */
struct camera_uchannel {
	uint32_t sn_fmt;
	uint32_t dst_fmt;

	uint32_t deci_factor;/* for ISP output path */
	uint32_t is_high_fps;/* for DCAM slow motion feature */
	uint32_t high_fps_skip_num;/* for DCAM slow motion feature */
	uint32_t is_compressed;/* for ISP output fbc format */

	struct sprd_img_size src_size;
	struct sprd_img_rect src_crop;
	struct sprd_img_size dst_size;
	uint32_t scene;

	/* for binding small picture */
	uint32_t slave_img_en;
	uint32_t slave_img_fmt;
	struct sprd_img_size slave_img_size;

	struct dcam_regular_desc regular_desc;
};

struct camera_uinfo {
	/* cap info */
	struct sprd_img_sensor_if sensor_if;
	struct sprd_img_size sn_size;
	struct sprd_img_size sn_max_size;
	struct sprd_img_rect sn_rect;
	uint32_t capture_mode;
	uint32_t capture_skip;

	uint32_t is_4in1;
	uint32_t is_3dnr;
	uint32_t is_rgb_ltm;
	uint32_t is_yuv_ltm;
	uint32_t is_dual;
	uint32_t dcam_slice_mode;   /*1: hw,  2:sw*/
	uint32_t slice_num;
	uint32_t slice_count;
	uint32_t is_afbc;
};

struct sprd_img_flash_info {
	uint32_t led0_ctrl;
	uint32_t led1_ctrl;
	uint32_t led0_status;
	uint32_t led1_status;
	uint32_t flash_last_status;
};


struct channel_context {
	enum cam_ch_id ch_id;
	uint32_t enable;
	uint32_t frm_base_id;
	uint32_t frm_cnt;
	uint32_t is_loose;
	atomic_t err_status;

	uint32_t compress_input;
	uint32_t compress_4bit_bypass;
	uint32_t compress_3dnr;
	uint32_t compress_output;

	int32_t dcam_path_id;
	uint32_t second_path_id; /* second path */
	uint32_t second_path_enable;

	/* for which need anoter dcam & path offline processing.*/
	int32_t aux_dcam_path_id;

	/* isp_path_id combined from ctx_id | path_id.*/
	/* isp_path_id = (ctx_id << ISP_PATH_BITS) | path_id */
	int32_t isp_path_id;
	int32_t slave_isp_path_id;
	int32_t reserved_buf_fd;
	enum isp_superzoom_status cap_status;

	struct camera_uchannel ch_uinfo;
	struct img_size swap_size;
	struct img_trim trim_dcam;
	struct img_trim trim_isp;
	struct img_size dst_dcam;
	uint32_t rds_ratio;

	/* to store isp offline param data if frame is discarded. */
	void *isp_updata;

	uint32_t alloc_start;
	struct completion alloc_com;
	struct completion superzoom_frm;
	struct sprd_cam_work alloc_buf_work;

	uint32_t uinfo_3dnr;	/* set by hal, 1:hw 3dnr; */
	uint32_t type_3dnr;	/* CAM_3DNR_HW:enable hw,and alloc buffer */
	uint32_t mode_ltm;
	uint32_t ltm_rgb;
	uint32_t ltm_yuv;
	struct camera_frame *superzoom_buf;
	struct camera_frame *nr3_bufs[ISP_NR3_BUF_NUM];
	struct camera_frame *ltm_bufs[LTM_MAX][ISP_LTM_BUF_NUM];

	/* dcam/isp shared frame buffer for full path */
	struct camera_queue share_buf_queue;
	struct camera_queue zoom_coeff_queue; /* channel specific coef queue */
};

struct camera_module {
	uint32_t idx;
	atomic_t state;
	atomic_t timeout_flag;
	struct mutex lock;
	struct camera_group *grp;

	int attach_sensor_id;
	uint32_t iommu_enable;
	enum camera_cap_status cap_status;
	enum dcam_capture_status dcam_cap_status;

	void *isp_dev_handle;
	void *dcam_dev_handle;
	/* for which need another dcam offline processing raw data*/
	void *aux_dcam_dev;
	void *flash_core_handle;
	uint32_t dcam_idx;
	uint32_t aux_dcam_id;

	uint32_t is_smooth_zoom;
	uint32_t zoom_solution; /* for dynamic zoom type swicth. */
	uint32_t rds_limit; /* raw downsizer limit */
	uint32_t binning_limit; /* binning limit: 1 - 1/2,  2 - 1/4 */
	uint32_t zoom_ratio; /* userspace zoom ratio for aem statis */
	struct camera_uinfo cam_uinfo;

	uint32_t last_channel_id;
	struct channel_context channel[CAM_CH_MAX];

	struct completion frm_com;
	struct camera_queue frm_queue; /* frame message queue for user*/
	struct camera_queue irq_queue; /* IRQ message queue for user*/
	struct camera_queue statis_queue; /* statis data queue or user*/


	struct cam_thread_info cap_thrd;
	struct cam_thread_info zoom_thrd;

	/*  dump raw  for debug*/
	struct cam_thread_info dump_thrd;
	struct camera_queue dump_queue;
	struct completion dump_com;
	struct timespec cur_dump_ts;
	uint32_t dump_count;
	uint32_t in_dump;

	/* for raw capture post process */
	struct completion streamoff_com;

	struct timer_list cam_timer;
	struct workqueue_struct *workqueue;
	struct sprd_cam_work work;

	struct camera_queue zsl_fifo_queue; /* for cmp timestamp */
	struct camera_frame *dual_frame; /* 0: no, to find, -1: no need find */
	atomic_t capture_frames_dcam; /* how many frames to report, -1:always */
	atomic_t cap_skip_frames;
	int64_t capture_times; /* *ns, timestamp get from start_capture */
	uint32_t capture_scene;
	uint32_t lowlux_4in1; /* flag */
	struct camera_queue remosaic_queue; /* 4in1: save camera_frame when remosaic */
	uint32_t auto_3dnr; /* 1: enable hw,and alloc buffer before stream on */
	struct sprd_img_flash_info flash_info;
	uint32_t flash_skip_fid;
	uint32_t path_state;
};

struct camera_group {
	atomic_t camera_opened;
	bool   ca_conn;

	spinlock_t module_lock;
	uint32_t  module_used;
	struct camera_module *module[CAM_COUNT];

	spinlock_t rawproc_lock;
	uint32_t rawproc_in;

	uint32_t dcam_count; /*dts cfg dcam count*/
	uint32_t isp_count; /*dts cfg isp count*/

	struct miscdevice *md;
	struct platform_device *pdev;
	struct camera_queue empty_frm_q;
	struct  sprd_cam_sec_cfg camsec_cfg;
	struct camera_debugger debugger;
	struct cam_hw_info *hw_info;
};

struct cam_ioctl_cmd {
	unsigned int cmd;
	int (*cmd_proc)(struct camera_module *module,
			unsigned long arg);
};

struct camera_queue *g_empty_frm_q;
struct cam_global_ctrl g_camctrl = {
	ZOOM_BINNING2,
	DCAM_SCALE_DOWN_MAX * 10,
	0,
	ISP_MAX_LINE_WIDTH
};

static struct isp_pipe_ops *isp_ops;
static struct dcam_pipe_ops *dcam_ops;
static struct cam_flash_ops *flash_ops;
static int img_ioctl_stream_off(
			struct camera_module *module,
			unsigned long arg);

static void put_k_frame(void *param)
{
	int ret = 0;
	struct camera_frame *frame;

	if (!param) {
		pr_err("fail to get valid param\n");
		return;
	}

	frame = (struct camera_frame *)param;
	if (frame->buf.type == CAM_BUF_USER)
		cambuf_put_ionbuf(&frame->buf);
	else {
		if (frame->buf.mapping_state)
			cambuf_kunmap(&frame->buf);
		cambuf_free(&frame->buf);
	}
	ret = put_empty_frame(frame);
}

static void camera_put_empty_frame(void *param)
{
	int ret = 0;
	struct camera_frame *frame;

	if (!param) {
		pr_err("fail to get valid param\n");
		return;
	}

	frame = (struct camera_frame *)param;
	if (frame->priv_data)
		kfree(frame->priv_data);
	cambuf_put_ionbuf(&frame->buf);
	ret = put_empty_frame(frame);
}

void cam_destroy_statis_buf(void *param)
{
	struct camera_frame *frame;

	if (!param) {
		pr_err("fail to get valid param\n");
		return;
	}
	frame = (struct camera_frame *)param;
	put_empty_frame(frame);
}

/* No need release buffer, only give back camera_frame
 * for remosaic_queue, it save camera_frame info when
 * buf send to hal for remosaic, use again when 4in1_post
 */
static void cam_release_camera_frame(void *param)
{
	struct camera_frame *frame;

	if (!param)
		return;
	frame = (struct camera_frame *)param;
	put_empty_frame(frame);
}

/* compression policy */
static void cal_compression(struct camera_module *module)
{
	struct channel_context *ch_pre, *ch_cap, *ch_vid;
	struct cam_hw_info *dcam_hw;
	struct compression_override *override;

	ch_pre = &module->channel[CAM_CH_PRE];
	ch_cap = &module->channel[CAM_CH_CAP];
	ch_vid = &module->channel[CAM_CH_VID];

	/*
	 * Enable compression for DCAM path by default. Full path is prior to
	 * bin path.
	 */
	ch_cap->compress_input = ch_cap->enable
		&& ch_cap->ch_uinfo.sn_fmt == IMG_PIX_FMT_GREY
		&& !ch_cap->ch_uinfo.is_high_fps
		&& !module->cam_uinfo.is_4in1;
	ch_pre->compress_input = ch_pre->enable
		&& ch_pre->ch_uinfo.sn_fmt == IMG_PIX_FMT_GREY
		&& !ch_pre->ch_uinfo.is_high_fps
		&& !ch_cap->compress_input
		&& !module->cam_uinfo.is_4in1;
	ch_vid->compress_input = ch_pre->compress_input;

	/* Disable compression for 3DNR by default */
	ch_cap->compress_3dnr = 0;
	ch_pre->compress_3dnr = 0;
	ch_vid->compress_3dnr = ch_pre->compress_3dnr;

	/*
	 * Enable compression for ISP store according to HAL setting. Normally
	 * this only happens in slow motion and only for video path.
	 */
	ch_cap->compress_output =
		ch_cap->enable && ch_cap->ch_uinfo.is_compressed;
	ch_pre->compress_output =
		ch_pre->enable && ch_pre->ch_uinfo.is_compressed;
	ch_vid->compress_output =
		ch_vid->enable && ch_vid->ch_uinfo.is_compressed;

	/* disable all compression on SharkL5 */
	dcam_hw = module->grp->hw_info;
	if (dcam_hw->prj_id == SHARKL5) {
		ch_cap->compress_input = ch_cap->compress_output =
			ch_cap->compress_3dnr = 0;
		ch_pre->compress_input = ch_pre->compress_output =
			ch_pre->compress_3dnr = 0;
		ch_vid->compress_input = ch_vid->compress_output =
			ch_vid->compress_3dnr = 0;
	}

	/* TODO disable all fbc/fbd for bug 1040757 */
	ch_cap->compress_input = ch_cap->compress_3dnr
		= ch_cap->compress_output = 0;
	ch_pre->compress_input = ch_pre->compress_3dnr
		= ch_pre->compress_output = 0;
	ch_vid->compress_input = ch_vid->compress_3dnr
		= ch_vid->compress_output = 0;

	/* Bypass compression low_4bit by default */
	ch_cap->compress_4bit_bypass = 1;
	ch_pre->compress_4bit_bypass = 1;
	ch_vid->compress_4bit_bypass = 1;

	/* open compression on SharkL5 pro */
	if (dcam_hw->prj_id == SHARKL5pro) {
		/* dcam support full path or bin path */
		ch_cap->compress_input = 0;
		ch_pre->compress_input = 0;
		ch_vid->compress_input = 0;
		/* isp support preview path and video path*/
		ch_vid->compress_output = module->cam_uinfo.is_afbc;
		/* 3dnr support preview&capture&video path*/
		ch_cap->compress_3dnr = 0;
		ch_pre->compress_3dnr = 0;
		ch_vid->compress_3dnr = ch_pre->compress_3dnr;
	}

	/* manually control compression policy here */
	override = &module->grp->debugger.compression[module->idx];
	if (override->enable) {
		ch_cap->compress_input = override->override[CH_CAP][FBC_DCAM];
		ch_cap->compress_3dnr = override->override[CH_CAP][FBC_3DNR];
		ch_cap->compress_output = override->override[CH_CAP][FBC_ISP];

		ch_pre->compress_input = override->override[CH_PRE][FBC_DCAM];
		ch_pre->compress_3dnr = override->override[CH_PRE][FBC_3DNR];
		ch_pre->compress_output = override->override[CH_PRE][FBC_ISP];

		ch_vid->compress_input = override->override[CH_VID][FBC_DCAM];
		ch_vid->compress_3dnr = override->override[CH_VID][FBC_3DNR];
		ch_vid->compress_output = override->override[CH_VID][FBC_ISP];
	}

	if (module->idx > 1) {
		ch_cap->compress_input = 0;
		ch_pre->compress_input = 0;
	}

	/* dcam not support fbc when dcam need fetch */
	if (module->cam_uinfo.dcam_slice_mode ||
		module->cam_uinfo.is_4in1)
		ch_cap->compress_input = 0;

	/* dcam not support fbc when open slowmotion */
	if (ch_pre->ch_uinfo.is_high_fps)
		ch_pre->compress_input = 0;

	pr_info("cam%d: cap %u %u %u, pre %u %u %u, vid %u %u %u\n",
		module->idx,
		ch_cap->compress_input, ch_cap->compress_3dnr,
		ch_cap->compress_output,
		ch_pre->compress_input, ch_pre->compress_3dnr,
		ch_pre->compress_output,
		ch_vid->compress_input, ch_vid->compress_3dnr,
		ch_vid->compress_output);
}

static void config_compression(struct camera_module *module)
{
	struct channel_context *ch_pre, *ch_cap, *ch_vid;
	struct isp_ctx_compression_desc ctx_compression_desc;
	struct isp_path_compression_desc path_compression_desc;
	struct cam_hw_info *hw = NULL;
	int fbc_mode = DCAM_FBC_DISABLE;

	ch_pre = &module->channel[CAM_CH_PRE];
	ch_cap = &module->channel[CAM_CH_CAP];
	ch_vid = &module->channel[CAM_CH_VID];
	hw = module->grp->hw_info;

	if (ch_cap->compress_input) {
		fbc_mode = hw->ip_dcam[module->dcam_idx]->dcam_full_fbc_mode;
		if (DCAM_FBC_FULL_14_BIT == fbc_mode)
			ch_cap->compress_4bit_bypass = 0;
	}

	if (ch_pre->compress_input) {
		fbc_mode = hw->ip_dcam[module->dcam_idx]->dcam_bin_fbc_mode;
		if (DCAM_FBC_BIN_14_BIT == fbc_mode)
			ch_pre->compress_4bit_bypass = 0;
	}

	ch_vid->compress_input = ch_pre->compress_input;
	ch_vid->compress_4bit_bypass = ch_pre->compress_4bit_bypass;

	dcam_ops->ioctl(module->dcam_dev_handle,
			DCAM_IOCTL_CFG_FBC, &fbc_mode);

	/* capture context */
	if (ch_cap->enable) {
		ctx_compression_desc.fetch_fbd = ch_cap->compress_input;
		ctx_compression_desc.fetch_fbd_4bit_bypass = ch_cap->compress_4bit_bypass;
		ctx_compression_desc.nr3_fbc_fbd = ch_cap->compress_3dnr;
		isp_ops->cfg_path(module->isp_dev_handle,
				  ISP_PATH_CFG_CTX_COMPRESSION,
				  ch_cap->isp_path_id >> ISP_CTXID_OFFSET,
				  0, &ctx_compression_desc);

		path_compression_desc.store_fbc = ch_cap->compress_output;
		isp_ops->cfg_path(module->isp_dev_handle,
				  ISP_PATH_CFG_PATH_COMPRESSION,
				  ch_cap->isp_path_id >> ISP_CTXID_OFFSET,
				  ch_cap->isp_path_id & ISP_PATHID_MASK,
				  &path_compression_desc);
	}

	/* preview context */
	if (ch_pre->enable) {
		ctx_compression_desc.fetch_fbd = ch_pre->compress_input;
		ctx_compression_desc.fetch_fbd_4bit_bypass = ch_pre->compress_4bit_bypass;
		ctx_compression_desc.nr3_fbc_fbd = ch_pre->compress_3dnr;
		isp_ops->cfg_path(module->isp_dev_handle,
				  ISP_PATH_CFG_CTX_COMPRESSION,
				  ch_pre->isp_path_id >> ISP_CTXID_OFFSET,
				  0, &ctx_compression_desc);

		path_compression_desc.store_fbc = ch_pre->compress_output;
		isp_ops->cfg_path(module->isp_dev_handle,
				  ISP_PATH_CFG_PATH_COMPRESSION,
				  ch_pre->isp_path_id >> ISP_CTXID_OFFSET,
				  ch_pre->isp_path_id & ISP_PATHID_MASK,
				  &path_compression_desc);
	}

	/* video context */
	if (ch_vid->enable) {
		ctx_compression_desc.fetch_fbd = ch_vid->compress_input;
		ctx_compression_desc.fetch_fbd_4bit_bypass = ch_vid->compress_4bit_bypass;
		ctx_compression_desc.nr3_fbc_fbd = ch_vid->compress_3dnr;
		isp_ops->cfg_path(module->isp_dev_handle,
				  ISP_PATH_CFG_CTX_COMPRESSION,
				  ch_vid->isp_path_id >> ISP_CTXID_OFFSET,
				  0, &ctx_compression_desc);

		path_compression_desc.store_fbc = ch_vid->compress_output;
		isp_ops->cfg_path(module->isp_dev_handle,
				  ISP_PATH_CFG_PATH_COMPRESSION,
				  ch_vid->isp_path_id >> ISP_CTXID_OFFSET,// TODO
				  ch_vid->isp_path_id & ISP_PATHID_MASK,
				  &path_compression_desc);
	}
}

static void prepare_frame_from_file(struct camera_queue *queue,
				    char *filename,
				    uint32_t width, uint32_t height, uint32_t is_loose)
{
	struct camera_frame *frame, *f;
	struct file *raw;
	uint8_t *buf;
	char fullname[DCAM_IMAGE_REPLACER_FILENAME_MAX + 32] = { 0 };
	const char *folder = "/data/ylog/";
	size_t cur;
	uint32_t total;
	int64_t left;
	const uint32_t per = 4096;
	ktime_t start, stop;
	int result = 0;

	/* prepare 1st buffer */
	frame = camera_dequeue_tail(queue);
	if (!frame)
		return;

	if (frame->is_compressed)
		total = dcam_if_cal_compressed_size(width, height,
			frame->compress_4bit_bypass);
	else
		total = cal_sprd_raw_pitch(width, is_loose) * height;

	strcpy(fullname, folder);
	/* length of filename is less then DCAM_IMAGE_REPLACER_FILENAME_MAX */
	strcpy(fullname + strlen(folder), filename);

	pr_info("reading %u bytes from %s\n", total, fullname);
	start = ktime_get_boottime();
	raw = filp_open(fullname, O_RDONLY, 0);
	if (IS_ERR_OR_NULL(raw)) {
		pr_err("fail to open data file\n");
		goto enqueue_frame;
	}

	buf = (uint8_t *)frame->buf.addr_k[0];
	left = total;
	do {
		cur = min((uint32_t)left, per);
		result = kernel_read(raw, buf, cur, &raw->f_pos);
		buf += result;
		left -= result;
	} while (result > 0 && left > 0);
	filp_close(raw, 0);
	stop = ktime_get_boottime();
	pr_info("read succeed, costs %lldns\n", ktime_sub(stop, start));

	/* prepare other buffers */
	list_for_each_entry(f, &queue->head, list) {
		start = ktime_get_boottime();
		memcpy((uint8_t *)f->buf.addr_k[0],
			(uint8_t *)frame->buf.addr_k[0], total);
		stop = ktime_get_boottime();
		pr_info("copy succeed, costs %lldns\n", ktime_sub(stop, start));
	}
	pr_info("done\n");

enqueue_frame:
	camera_enqueue(queue, frame);
}

static void alloc_buffers(struct work_struct *work)
{
	int ret = 0;
	int i, count, total, iommu_enable;
	uint32_t width, height, size, is_loose;
	struct sprd_cam_work *alloc_work;
	struct camera_module *module;
	struct camera_frame *pframe;
	struct channel_context *channel;
	struct camera_debugger *debugger;
	struct cam_hw_info *hw = NULL;
	int path_id;

	pr_info("enter.\n");

	alloc_work = container_of(work, struct sprd_cam_work, work);
	channel = container_of(alloc_work,
			       struct channel_context, alloc_buf_work);
	atomic_set(&alloc_work->status, CAM_WORK_RUNNING);

	module = (struct camera_module *)alloc_work->priv_data;
	hw = module->grp->hw_info;
	iommu_enable = module->iommu_enable;

	width = channel->swap_size.w;
	height = channel->swap_size.h;
	is_loose = module->cam_uinfo.sensor_if.if_spec.mipi.is_loose;

	if (channel->compress_input) {
		width = ALIGN(width, DCAM_FBC_TILE_WIDTH);
		height = ALIGN(height, DCAM_FBC_TILE_HEIGHT);
		pr_info("ch %d, FBC size (%d %d)\n", channel->ch_id, width, height);
		size = dcam_if_cal_compressed_size(width, height,
				channel->compress_4bit_bypass);
	} else if (channel->ch_uinfo.sn_fmt == IMG_PIX_FMT_GREY) {
		size = cal_sprd_raw_pitch(width, is_loose) * height;
	} else {
		size = width * height * 3;
	}
	size = ALIGN(size, CAM_BUF_ALIGN_SIZE);

	total = 5;
	if (channel->ch_id == CAM_CH_CAP && module->cam_uinfo.is_dual)
		total = 4;

	/* 4in1 non-zsl capture for single frame */
	if ((module->cam_uinfo.is_4in1 || module->cam_uinfo.dcam_slice_mode)
		&& channel->ch_id == CAM_CH_CAP &&
		module->channel[CAM_CH_PRE].enable == 0 &&
		module->channel[CAM_CH_VID].enable == 0)
		total = 1;

	if (module->dump_thrd.thread_task)
		total += 3;

	/* extend buffer queue for slow motion */
	if (channel->ch_uinfo.is_high_fps)
		total = CAM_SHARED_BUF_NUM;

	if (channel->ch_id == CAM_CH_PRE &&
		module->grp->camsec_cfg.camsec_mode != SEC_UNABLE) {
		total = 4;
	}

	pr_info("ch_id %d, camsec=%d, buffer size: %u (%u x %u), num %d\n",
		channel->ch_id, module->grp->camsec_cfg.camsec_mode,
		size, width, height,	total);

	for (i = 0, count = 0; i < total; i++) {
		do {
			pframe = get_empty_frame();
			pframe->channel_id = channel->ch_id;
			pframe->is_compressed = channel->compress_input;
			pframe->compress_4bit_bypass =
				channel->compress_4bit_bypass;
			pframe->width = width;
			pframe->height = height;
			pframe->endian = ENDIAN_LITTLE;
			pframe->pattern = module->cam_uinfo.sensor_if.img_ptn;
			if (channel->ch_id == CAM_CH_PRE &&
				module->grp->camsec_cfg.camsec_mode != SEC_UNABLE) {
				pframe->buf.buf_sec = 1;
			} else {
				pframe->buf.buf_sec = 0;
			}

			pr_info("camca: ch_id =%d, buf_sec=%d\n",
				channel->ch_id,
				pframe->buf.buf_sec);

			ret = cambuf_alloc(
					&pframe->buf, size,
					0, iommu_enable);
			if (ret) {
				pr_err("fail to alloc buf: %d ch %d\n",
						i, channel->ch_id);
				put_empty_frame(pframe);
				atomic_inc(&channel->err_status);
				goto exit;
			}

			ret = camera_enqueue(&channel->share_buf_queue, pframe);
			if (ret) {
				pr_err("fail to enqueue shared buf: %d ch %d\n",
						i, channel->ch_id);
				cambuf_free(&pframe->buf);
				put_empty_frame(pframe);
				/* no break here and will retry */
			} else {
				count++;
				pr_debug("frame %p,idx %d,cnt %d,phy_addr %p\n",
					pframe, i, count,
					(void *)pframe->buf.addr_vir[0]);
				break;
			}
		} while (1);
	}

	debugger = &module->grp->debugger;
	path_id = channel->dcam_path_id;
	if (path_id >= 0 && path_id < DCAM_IMAGE_REPLACER_PATH_MAX) {
		struct dcam_image_replacer *replacer;

		replacer = &debugger->replacer[module->dcam_idx];
		if (replacer->enabled[path_id]) {
			prepare_frame_from_file(&channel->share_buf_queue,
						replacer->filename[path_id],
						width, height, is_loose);
			dcam_ops->ioctl(module->dcam_dev_handle,
					DCAM_IOCTL_CFG_REPLACER, replacer);
		}
	} else {
		dcam_ops->ioctl(module->dcam_dev_handle,
				DCAM_IOCTL_CFG_REPLACER, NULL);
	}

	if (hw->ip_dcam[module->dcam_idx]->superzoom_support
		&& channel->ch_id == CAM_CH_CAP) {
		/*more than 8x zoom capture alloc buf*/

		uint32_t w = module->cam_uinfo.sn_max_size.w;
		uint32_t h = module->cam_uinfo.sn_max_size.h;

		size = ((w + 1) & (~1)) * h * 3 / 2;
		size = ALIGN(size, CAM_BUF_ALIGN_SIZE);
		pframe = get_empty_frame();
		if (!pframe) {
			pr_err("fail to superzoom no empty frame.\n");
			ret = -EINVAL;
			goto exit;
		}

		pframe->channel_id = channel->ch_id;
		if (module->grp->camsec_cfg.camsec_mode != SEC_UNABLE) {
			pframe->buf.buf_sec = 1;
			pr_debug("superzoom camca: ch_id =%d, buf_sec=%d\n",
					channel->ch_id,
					pframe->buf.buf_sec);
		}

		ret = cambuf_alloc(&pframe->buf, size, 0, 1);
		if (ret) {
			pr_err("fail to alloc superzoom buf\n");
			put_empty_frame(pframe);
			atomic_inc(&channel->err_status);
			goto exit;
		}

		channel->superzoom_buf = pframe;
		pr_info("idx %d, superzoom w %d, h %d, buf %p \n",
			module->dcam_idx, w, h, pframe);
	}

	if (channel->type_3dnr == CAM_3DNR_HW) {
		/* YUV420 for 3DNR ref*/
		if (channel->compress_3dnr)
			size = isp_3dnr_cal_compressed_size(width, height);
		else {
			size = ((width + 1) & (~1)) * height * 3 / 2;
			size = ALIGN(size, CAM_BUF_ALIGN_SIZE);
		}

		pr_info("ch %d 3dnr buffer size: %u.\n", channel->ch_id, size);
		for (i = 0; i < ISP_NR3_BUF_NUM; i++) {
			pframe = get_empty_frame();

			if (channel->ch_id == CAM_CH_PRE &&
				module->grp->camsec_cfg.camsec_mode != SEC_UNABLE) {
				pframe->buf.buf_sec = 1;
				pr_info("camca:  ch_id =%d, buf_sec=%d\n",
					channel->ch_id,
					pframe->buf.buf_sec);
			}

			ret = cambuf_alloc(&pframe->buf, size, 0, iommu_enable);
			if (ret) {
				pr_err("fail to alloc 3dnr buf: %d ch %d\n",
					i, channel->ch_id);
				put_empty_frame(pframe);
				atomic_inc(&channel->err_status);
				goto exit;
			}
			channel->nr3_bufs[i] = pframe;
		}
	}

	if (channel->mode_ltm != MODE_LTM_OFF) {
		/* todo: ltm buffer size needs to be refined.*/
		/* size = ((width + 1) & (~1)) * height * 3 / 2; */
		/*
		 * sizeof histo from 1 tile: 128 * 16 bit
		 * MAX tile num: 8 * 8
		 * */
		size = 64 * 128 * 2;

		size = ALIGN(size, CAM_BUF_ALIGN_SIZE);

		pr_info("ch %d ltm buffer size: %u.\n", channel->ch_id, size);
		if (channel->ltm_rgb) {
			for (i = 0; i < ISP_LTM_BUF_NUM; i++) {
				if (channel->ch_id == CAM_CH_PRE) {
					pframe = get_empty_frame();

					if (channel->ch_id == CAM_CH_PRE
						&& module->grp->camsec_cfg.camsec_mode == SEC_TIME_PRIORITY) {
						pframe->buf.buf_sec = 1;
						pr_info("camca: ch_id =%d, buf_sec=%d\n",
							channel->ch_id,
							pframe->buf.buf_sec);
					}
					ret = cambuf_alloc(&pframe->buf, size, 0,
							   iommu_enable);
					if (ret) {
						pr_err("fail to alloc ltm buf: %d ch %d\n",
						       i, channel->ch_id);
						put_empty_frame(pframe);
						atomic_inc(&channel->err_status);
						goto exit;
					}
					cambuf_kmap(&pframe->buf);
					channel->ltm_bufs[LTM_RGB][i] = pframe;
				} else { /* CAM_CH_CAP case */
					/*
					 * LTM capture, USING preview path histo,
					 * So, setting preview buf to capture path
					 * */
					channel->ltm_bufs[LTM_RGB][i] =
						module->channel[CAM_CH_PRE].ltm_bufs[LTM_RGB][i];
				}
			}
		}

		if (channel->ltm_yuv) {
			for (i = 0; i < ISP_LTM_BUF_NUM; i++) {
				if (channel->ch_id == CAM_CH_PRE) {
					pframe = get_empty_frame();

					if (channel->ch_id == CAM_CH_PRE
						&& module->grp->camsec_cfg.camsec_mode == SEC_TIME_PRIORITY) {
						pframe->buf.buf_sec = 1;
						pr_info("camca: ch_id =%d, buf_sec=%d\n",
							channel->ch_id,
							pframe->buf.buf_sec);
					}
					ret = cambuf_alloc(&pframe->buf, size, 0,
							   iommu_enable);
					if (ret) {
						pr_err("fail to alloc ltm buf: %d ch %d\n",
						       i, channel->ch_id);
						put_empty_frame(pframe);
						atomic_inc(&channel->err_status);
						goto exit;
					}
					cambuf_kmap(&pframe->buf);
					channel->ltm_bufs[LTM_YUV][i] = pframe;
				} else { /* CAM_CH_CAP case */
					/*
					 * LTM capture, USING preview path histo,
					 * So, setting preview buf to capture path
					 * */
					channel->ltm_bufs[LTM_YUV][i] =
						module->channel[CAM_CH_PRE].ltm_bufs[LTM_YUV][i];
				}
			}
		}
	}

exit:
	complete(&channel->alloc_com);
	atomic_set(&alloc_work->status, CAM_WORK_DONE);
	pr_info("ch %d done. status %d\n",
		channel->ch_id, atomic_read(&channel->err_status));
}

static int set_cap_info(struct camera_module *module)
{
	int ret = 0;
	struct camera_uinfo *info = &module->cam_uinfo;
	struct sprd_img_sensor_if *sensor_if = &info->sensor_if;
	struct dcam_cap_cfg cap_info = { 0 };

	cap_info.mode = info->capture_mode;
	cap_info.frm_skip = info->capture_skip;
	cap_info.is_4in1 = info->is_4in1;
	cap_info.dcam_slice_mode = info->dcam_slice_mode;
	cap_info.sensor_if = sensor_if->if_type;
	cap_info.format =  sensor_if->img_fmt;
	cap_info.pattern = sensor_if->img_ptn;
	cap_info.frm_deci = sensor_if->frm_deci;
	cap_info.is_cphy = sensor_if->if_spec.mipi.is_cphy;
	if (cap_info.sensor_if == DCAM_CAP_IF_CSI2) {
		cap_info.href = sensor_if->if_spec.mipi.use_href;
		cap_info.data_bits = sensor_if->if_spec.mipi.bits_per_pxl;
	}
	cap_info.cap_size.start_x = info->sn_rect.x;
	cap_info.cap_size.start_y = info->sn_rect.y;
	cap_info.cap_size.size_x = info->sn_rect.w;
	cap_info.cap_size.size_y = info->sn_rect.h;

	ret = dcam_ops->ioctl(module->dcam_dev_handle,
				DCAM_IOCTL_CFG_CAP, &cap_info);
	/* for dcam1 mipicap */
	if (info->dcam_slice_mode && module->aux_dcam_dev)
		ret = dcam_ops->ioctl(module->aux_dcam_dev,
				DCAM_IOCTL_CFG_CAP, &cap_info);
	return ret;
}

/* frame to fifo queue for dual camera
 * return: NULL: only input, no output
 *         frame: fifo, set to path->out_buf_queue
 */
static struct camera_frame *dual_fifo_queue(struct camera_module *module,
		struct camera_frame *pframe,
		struct channel_context *channel)
{
	int ret;

	/* zsl, save frames to fifo buffer */
	ret = camera_enqueue(&module->zsl_fifo_queue, pframe);
	if (ret) /* fail */
		return pframe;

	if (get_outbuf_queue_cnt(module->dcam_dev_handle,
		channel->dcam_path_id) < 1) {
		/* do fifo */
		pframe = camera_dequeue(&module->zsl_fifo_queue);
		if (pframe)
			return pframe;
	}

	return NULL;
}

static int dual_get_same_frame(struct camera_module *module)
{
	struct camera_group *grp;
	struct camera_module *pmd[CAM_COUNT];
	struct camera_queue *q[CAM_COUNT];
	struct camera_frame *pframe[CAM_COUNT];
	int i, j;
	int ret = 0;
	int64_t t;

	grp = module->grp;
	if (!grp)
		return -EFAULT;
	/* get the two module */
	for (i = 0, j = 0; i < CAM_COUNT; i++) {
		pmd[j] = grp->module[i];
		if (!pmd[j])
			continue;
		if (pmd[j]->cam_uinfo.is_dual)
			j++;
	}
	if (j != 2) {
		pr_err("fail to get module, dual camera, but have %d module\n", j);
		return -EFAULT;
	}
	q[0] = &(pmd[0]->zsl_fifo_queue);
	q[1] = &(pmd[1]->zsl_fifo_queue);
	t = pmd[0]->capture_times;
	ret = camera_queue_same_frame(q[0], q[1], &pframe[0], &pframe[1], t);
	if (ret) {
		pr_err("fail to get same frame\n");
		return ret;
	}
	pmd[0]->dual_frame = pframe[0];
	pmd[1]->dual_frame = pframe[1];

	return 0;
}
/*
 * return: 0: pframe to isp
 *         1: no need more deal
 */
static struct camera_frame *deal_dual_frame(struct camera_module *module,
		struct camera_frame *pframe,
		struct channel_context *channel)
{
	int ret;
	struct camera_frame *pftmp;

	channel = &module->channel[pframe->channel_id];
	if (atomic_read(&(module->capture_frames_dcam)) == 0) {
		/* no need report to hal, do fifo */
		pframe = dual_fifo_queue(module, pframe, channel);
		if (pframe) {
			if (pframe->sync_data)
				dcam_if_release_sync(pframe->sync_data,
					pframe);
			ret = dcam_ops->cfg_path(module->dcam_dev_handle,
				DCAM_PATH_CFG_OUTPUT_BUF,
				channel->dcam_path_id, pframe);
			if (ret)
				pr_err("fail to set output buffer\n");
		}
		return NULL;
	}
	pftmp = module->dual_frame;
	if (pftmp) {
		module->dual_frame = NULL;
		/* cur frame to out_buf_queue */
		if (pframe->sync_data)
			dcam_if_release_sync(pframe->sync_data,	pframe);
		ret = dcam_ops->cfg_path(module->dcam_dev_handle,
			DCAM_PATH_CFG_OUTPUT_BUF,
			channel->dcam_path_id, pframe);
		return pftmp;
	}
	/* get the same frame */
	ret = dual_get_same_frame(module);
	if (!ret) {
		pftmp = module->dual_frame;
		if (pftmp) {
			module->dual_frame = NULL;
			/* cur frame to out_buf_queue */
			if (pframe->sync_data)
				dcam_if_release_sync(pframe->sync_data,
					pframe);
			ret = dcam_ops->cfg_path(module->dcam_dev_handle,
				DCAM_PATH_CFG_OUTPUT_BUF,
				channel->dcam_path_id, pframe);
			return pftmp;
		}
	}
	pr_warn("Sync fail, report current frame\n");

	return pframe;
}

static struct camera_frame *deal_bigsize_frame(struct camera_module *module,
		struct camera_frame *pframe,
		struct channel_context *channel)
{
	int ret;

	/* full path release sync */
	if (pframe->sync_data)
		dcam_if_release_sync(pframe->sync_data, pframe);
	/* 1: aux dcam bin tx done, set frame to isp
	 * 2: lowlux capture, dcam0 full path done, set frame to isp
	 */
	if (pframe->irq_type != CAMERA_IRQ_BIGSIZE_DONE) {
		/* offline timestamp, check time
		 * recove this time:190415
		 *
		 * if (pframe->sensor_time.tv_sec == 0 &&
		 *	pframe->sensor_time.tv_usec == 0)
		 */
		{
			struct timespec cur_ts;

			pframe->boot_sensor_time = ktime_get_boottime();
			ktime_get_ts(&cur_ts);
			pframe->sensor_time.tv_sec = cur_ts.tv_sec;
			pframe->sensor_time.tv_usec = cur_ts.tv_nsec / NSEC_PER_USEC;
		}
		pr_info("[(PROCESSED)] frame[%d] fd %d, size[%d %d], 0x%x, channel_id %d\n",
			pframe->fid, pframe->buf.mfd[0], pframe->width,
			pframe->height, (uint32_t)pframe->buf.addr_vir[0], pframe->channel_id);
		return pframe;
	}
	/* dcam0 full tx done, frame send to dcam1 or drop */
	pr_info("raw frame[%d] fd %d, size[%d %d], 0x%x, channel_id %d, catpure_cnt = %d, time %lld\n",
			pframe->fid, pframe->buf.mfd[0], pframe->width,
			pframe->height, (uint32_t)pframe->buf.addr_vir[0], pframe->channel_id,
			atomic_read(&module->capture_frames_dcam), pframe->boot_sensor_time);

	if (pframe->fid >= 0) {
		if (module->dcam_cap_status == DCAM_CAPTURE_START_FROM_NEXT_SOF
			&& (module->capture_times < pframe->boot_sensor_time)
			&& atomic_read(&module->capture_frames_dcam) > 0) {
			ret = dcam_ops->proc_frame(module->aux_dcam_dev, pframe);
			if(ret == 0)
				return NULL;
		} else if (module->dcam_cap_status != DCAM_CAPTURE_START_FROM_NEXT_SOF){
			ret = dcam_ops->proc_frame(module->aux_dcam_dev, pframe);
			if(ret == 0)
				return NULL;
		}
	}
	/* set buffer back to dcam0 full path, to out_buf_queue */
	pr_debug("drop frame[%d]\n", pframe->fid);
	channel = &module->channel[pframe->channel_id];
	ret = dcam_ops->cfg_path(
		module->dcam_dev_handle,
		DCAM_PATH_CFG_OUTPUT_BUF,
		channel->dcam_path_id, pframe);
	if (unlikely(ret))
		pr_err("fail to set output buffer, ret %d\n", ret);

	return NULL;
}

static struct camera_frame *deal_4in1_frame(struct camera_module *module,
		struct camera_frame *pframe,
		struct channel_context *channel)
{
	int ret;
	uint32_t shutoff = 0;
	struct dcam_pipe_dev *dev = NULL;

	/* full path release sync */
	if (pframe->sync_data)
		dcam_if_release_sync(pframe->sync_data,	pframe);
	/* 1: aux dcam bin tx done, set frame to isp
	 * 2: lowlux capture, dcam0 full path done, set frame to isp
	 */
	if (pframe->irq_type != CAMERA_IRQ_4IN1_DONE) {
		/* offline timestamp, check time
		 * recove this time:190415
		 *
		 * if (pframe->sensor_time.tv_sec == 0 &&
		 *	pframe->sensor_time.tv_usec == 0)
		 */
		{
			struct timespec cur_ts;

			pframe->boot_sensor_time = ktime_get_boottime();
			ktime_get_ts(&cur_ts);
			pframe->sensor_time.tv_sec = cur_ts.tv_sec;
			pframe->sensor_time.tv_usec = cur_ts.tv_nsec / NSEC_PER_USEC;
		}

		return pframe;
	}
	/* dcam0 full tx done, frame report to HAL or drop */
	if (atomic_read(&module->capture_frames_dcam) > 0) {
		/* 4in1 send buf to hal for remosaic */
		atomic_dec(&module->capture_frames_dcam);
		pframe->evt = IMG_TX_DONE;
		pframe->channel_id = CAM_CH_RAW;
		ret = camera_enqueue(&module->frm_queue, pframe);
		complete(&module->frm_com);
		pr_info("raw frame[%d] fd %d, size[%d %d], 0x%x\n",
			pframe->fid, pframe->buf.mfd[0], pframe->width,
			pframe->height, (uint32_t)pframe->buf.addr_vir[0]);

		/*stop full path & cap eb*/
		shutoff = 1;
		dev = module->dcam_dev_handle;
		dev->hw->hw_ops.core_ops.path_stop(dev, channel->dcam_path_id);
		dev->hw->hw_ops.core_ops.stop_cap_eb(dev);
		dcam_ops->cfg_path(dev, DCAM_PATH_CFG_SHUTOFF,
			channel->dcam_path_id, &shutoff);
		return NULL;
	}
	/* set buffer back to dcam0 full path, to out_buf_queue */
	channel = &module->channel[pframe->channel_id];
	ret = dcam_ops->cfg_path(
		module->dcam_dev_handle,
		DCAM_PATH_CFG_OUTPUT_BUF,
		channel->dcam_path_id, pframe);
	if (unlikely(ret))
		pr_err("fail to set output buffer, ret %d\n", ret);

	return NULL;
}

/* 4in1_raw_capture
 * full path: sensor raw(4cell), bin path: 4in1 bin sum
 * two image save in one fd(one buffer), full + bin
 */
struct camera_frame *deal_4in1_raw_capture(struct camera_module *module,
			struct camera_frame *pframe)
{
	static uint32_t flag_path; /* b0:bin tx done, b1:full tx done */

	/* full path tx done */
	if (pframe->irq_type == CAMERA_IRQ_4IN1_DONE) {
		flag_path |= BIT(1);
	} else { /* bin path tx done */
		flag_path |= BIT(0);
	}
	/* check bin, full both tx done */
	if ((flag_path & 0x2) == 0x2) {
		pframe->evt = IMG_TX_DONE;
		pframe->irq_type = CAMERA_IRQ_4IN1_DONE;
		flag_path = 0;
		return pframe;
	}
	/* not report */
	cambuf_put_ionbuf(&pframe->buf);
	put_empty_frame(pframe);

	return NULL;
}

static int set_superzoom_complete(void *priv_data)
{
	int ret = 0;
	struct camera_module *module;
	struct channel_context *channel;

	if (!priv_data) {
		pr_err("fail to set superzoom complete\n");
		ret = -1;
		goto exit;
	}

	module = (struct camera_module *)priv_data;
	channel = &module->channel[CAM_CH_CAP];
	complete(&channel->superzoom_frm);
	pr_info("done superzoom complete, module idx %d\n", module->idx);
exit:
	return ret;

}

static int get_superzoom_dst(void *param, void *priv_data)
{
	int ret = 0;
	struct camera_module *module;
	struct channel_context *channel;
	struct img_size *size;

	if (!param || !priv_data) {
		pr_err("fail to get superzoom dst\n");
		ret = -1;
		goto exit;
	}

	module = (struct camera_module *)priv_data;
	channel = &module->channel[CAM_CH_CAP];
	size = (struct img_size *)param;
	size->w = channel->ch_uinfo.dst_size.w;
	size->h = channel->ch_uinfo.dst_size.h;
	pr_info("superzoom dst size w %d, h %d\n", size->w, size->h);
exit:
	return ret;
}

static int is_deal_superzoom(enum isp_cb_type type)
{
	int ret = 0;

	if (type == ISP_CB_SET_SUPERZOOM_COMPLETE
		|| type == ISP_CB_GET_SUPERZOOM_DST) {
		pr_info(" is superzoom type %d\n", type);
		ret = 1;
	}

	return ret;
}

static int deal_with_superzoom(enum isp_cb_type type,
	void *param, void *priv_data)
{
	int ret = 0;
	pr_info(" enter\n");

	switch (type) {
		case ISP_CB_SET_SUPERZOOM_COMPLETE:
			ret = set_superzoom_complete(priv_data);
		break;
		case ISP_CB_GET_SUPERZOOM_DST:
			ret = get_superzoom_dst(param, priv_data);
		break;
		default:
			pr_err("should not go to here  type%d\n", type);
		break;
	}

	return ret;
}

int isp_callback(enum isp_cb_type type, void *param, void *priv_data)
{
	int ret = 0;
	uint32_t ch_id;
	struct camera_frame *pframe;
	struct camera_module *module;
	struct channel_context *channel;

	if (is_deal_superzoom(type)) {
		pr_info("do superzoom type %d\n", type);
		return deal_with_superzoom(type, param, priv_data);
	}

	if (!param || !priv_data) {
		pr_err("fail to get valid param %p %p\n", param, priv_data);
		return -EFAULT;
	}

	module = (struct camera_module *)priv_data;

	if (type == ISP_CB_DEV_ERR) {
		pr_err("fail to get isp state, camera %d\n", module->idx);
		pframe = get_empty_frame();
		if (pframe) {
			pframe->evt = IMG_TX_ERR;
			pframe->irq_type = CAMERA_IRQ_IMG;
			ret = camera_enqueue(&module->frm_queue, pframe);
		}
		complete(&module->frm_com);
		return 0;
	}

	pframe = (struct camera_frame *)param;
	pframe->priv_data = NULL;
	channel = &module->channel[pframe->channel_id];

	if ((pframe->fid & 0x3F) == 0)
		pr_debug("cam %d, module %p, frame %p, ch %d\n",
		module->idx, module, pframe, pframe->channel_id);

	switch (type) {
	case ISP_CB_RET_SRC_BUF:
		if ((atomic_read(&module->state) != CAM_RUNNING) ||
			(channel->dcam_path_id < 0)) {
			/* stream off or test_isp_only */
			pr_info("isp ret src frame %p\n", pframe);
			camera_enqueue(&channel->share_buf_queue, pframe);
		} else if (module->cap_status == CAM_CAPTURE_RAWPROC) {
			if (module->cam_uinfo.dcam_slice_mode == CAM_OFFLINE_SLICE_SW) {
				struct channel_context *ch = NULL;

				pr_debug("slice %d %p\n", module->cam_uinfo.slice_count, pframe);
				module->cam_uinfo.slice_count++;
				ch = &module->channel[CAM_CH_CAP];
				ret = dcam_ops->cfg_path(module->dcam_dev_handle,
						DCAM_PATH_CFG_OUTPUT_BUF,
						ch->dcam_path_id, pframe);
				if (module->cam_uinfo.slice_count >= module->cam_uinfo.slice_num)
					module->cam_uinfo.slice_count = 0;
				else
					ret = dcam_ops->proc_frame(module->dcam_dev_handle, pframe);
				return ret;
			}
			/* for case raw capture post-proccessing
			 * just release it, no need to return
			 */
			if (pframe->buf.type == CAM_BUF_USER)
				cambuf_put_ionbuf(&pframe->buf);
			else
				cambuf_free(&pframe->buf);
			pr_info("raw proc return mid frame %p\n", pframe);
			put_empty_frame(pframe);
		} else {
			/* return offline buffer to dcam available queue. */
			pr_debug("isp reset dcam path out %d\n",
				channel->dcam_path_id);

			if (module->dump_thrd.thread_task && module->in_dump) {
				ret = camera_enqueue(&module->dump_queue, pframe);
				if (ret == 0) {
					complete(&module->dump_com);
					return 0;
				}
			}

			if ((module->cam_uinfo.is_4in1 || module->cam_uinfo.dcam_slice_mode) &&
				channel->aux_dcam_path_id == DCAM_PATH_BIN) {
				if (pframe->buf.type == CAM_BUF_USER) {
					/* 4in1, lowlux capture, use dcam0
					 * full path output buffer, from
					 * SPRD_IMG_IO_SET_4IN1_ADDR, user space
					 */
					ret = dcam_ops->cfg_path(module->dcam_dev_handle,
						DCAM_PATH_CFG_OUTPUT_BUF,
						channel->dcam_path_id,
						pframe);
				} else {
					/* 4in1, dcam1 bin path output buffer
					 * alloced by kernel
					 */
					if(module->cam_uinfo.is_4in1)
						ret = dcam_ops->cfg_path(module->dcam_dev_handle,
							DCAM_PATH_CFG_OUTPUT_BUF,
							channel->aux_dcam_path_id,
							pframe);
					else
						ret = dcam_ops->cfg_path(module->aux_dcam_dev,
							DCAM_PATH_CFG_OUTPUT_BUF,
							channel->aux_dcam_path_id,
							pframe);
				}
			} else {
				ret = dcam_ops->cfg_path(
					module->dcam_dev_handle,
					DCAM_PATH_CFG_OUTPUT_BUF,
					channel->dcam_path_id, pframe);
			}
		}
		break;

	case ISP_CB_RET_DST_BUF:
		if (atomic_read(&module->state) == CAM_RUNNING) {
			if (module->cap_status == CAM_CAPTURE_RAWPROC) {
				pr_info("raw proc return dst frame %p\n", pframe);
				cambuf_put_ionbuf(&pframe->buf);
				module->cap_status = CAM_CAPTURE_RAWPROC_DONE;
				pframe->irq_type = CAMERA_IRQ_DONE;
				pframe->irq_property = IRQ_RAW_PROC_DONE;
			} else {
				pframe->irq_type = CAMERA_IRQ_IMG;
			}
			pframe->evt = IMG_TX_DONE;
			ch_id = pframe->channel_id;

			ret = camera_enqueue(&module->frm_queue, pframe);
			if (ret) {
				cambuf_put_ionbuf(&pframe->buf);
				put_empty_frame(pframe);
			} else {
				complete(&module->frm_com);
				pr_debug("ch %d get out frame: %p, evt %d\n",
						ch_id, pframe, pframe->evt);
			}
		} else {
			cambuf_put_ionbuf(&pframe->buf);
			put_empty_frame(pframe);
		}
		break;

	case ISP_CB_STATIS_DONE:
		pframe->evt = IMG_TX_DONE;
		pframe->irq_type = CAMERA_IRQ_STATIS;
		if (atomic_read(&module->state) == CAM_RUNNING) {
			ret = camera_enqueue(&module->frm_queue, pframe);
			if (ret) {
				put_empty_frame(pframe);
			} else {
				complete(&module->frm_com);
				pr_debug("get statis frame: %p, type %d, %d\n",
					pframe, pframe->irq_type, pframe->irq_property);
			}
		} else {
			put_empty_frame(pframe);
		}
		break;
	default:
		pr_err("fail to get cb cmd: %d\n", type);
		break;
	}

	return ret;
}

int dcam_callback(enum dcam_cb_type type, void *param, void *priv_data)
{
	int ret = 0;
	struct camera_frame *pframe;
	struct camera_module *module;
	struct channel_context *channel;
	struct isp_offline_param *cur;
	struct cam_hw_info *hw = NULL;
	int cap_frame = 0, skip_frame = 0;

	if (!param || !priv_data) {
		pr_err("fail to get valid param %p %p\n", param, priv_data);
		return -EFAULT;
	}

	module = (struct camera_module *)priv_data;
	hw = module->grp->hw_info;

	if (type == DCAM_CB_DEV_ERR) {
		pr_err("fail to check cb type. camera %d\n", module->idx);
		csi_api_reg_trace();
		hw->hw_ops.core_ops.reg_trace(module->dcam_idx,
			ABNORMAL_REG_TRACE);

		dcam_ops->stop(module->dcam_dev_handle);

		pframe = get_empty_frame();
		if (pframe) {
			pframe->evt = IMG_TX_ERR;
			pframe->irq_type = CAMERA_IRQ_IMG;
			ret = camera_enqueue(&module->frm_queue, pframe);
		}
		complete(&module->frm_com);
		return 0;
	}

	pframe = (struct camera_frame *)param;
	pframe->priv_data = NULL;
	channel = &module->channel[pframe->channel_id];

	pr_debug("module %p, cam%d ch %d.  cb cmd %d, frame %p\n",
		module, module->idx, pframe->channel_id, type, pframe);

	switch (type) {
	case DCAM_CB_DATA_DONE:
		if (pframe->buf.addr_k[0]) {
			uint32_t *ptr = (uint32_t *)pframe->buf.addr_k[0];

			pr_debug("dcam path %d. outdata: %08x %08x %08x %08x\n",
				channel->dcam_path_id, ptr[0], ptr[1], ptr[2], ptr[3]);
		}

		if (atomic_read(&module->state) != CAM_RUNNING) {
			pr_info("stream off. put frame %p\n", pframe);
			if (pframe->buf.type == CAM_BUF_KERNEL) {
				camera_enqueue(&channel->share_buf_queue, pframe);
			} else {
				/* 4in1 or raw buffer is allocate from user */
				cambuf_put_ionbuf(&pframe->buf);
				put_empty_frame(pframe);
			}
		} else if (channel->ch_id == CAM_CH_RAW) {
			/* RAW capture or test_dcam only */
			if (module->cam_uinfo.is_4in1 == 0) {
				uint32_t capture = 0;
				if (module->cap_status == CAM_CAPTURE_START) {
					if (module->dcam_cap_status != DCAM_CAPTURE_START_FROM_NEXT_SOF) {
						capture = 1;
					} else if (pframe->boot_sensor_time > module->capture_times) {
						/*  raw capture with flash */
						capture = 1;
					}
				}
				pr_info("capture %d, fid %d, start %d  type %d\n", capture,
					pframe->fid, module->cap_status, module->dcam_cap_status);
				pr_info("cap time %lld, frame time %lld\n",
					module->capture_times, pframe->boot_sensor_time);
				if (pframe->sync_data)
					dcam_if_release_sync(pframe->sync_data, pframe);
				if (channel->ch_uinfo.scene == DCAM_SCENE_MODE_CAPTURE
					&& capture == 0) {
					ret = dcam_ops->cfg_path(module->dcam_dev_handle,
							DCAM_PATH_CFG_OUTPUT_BUF,
							channel->dcam_path_id, pframe);
					return 0;
				}
				pframe->evt = IMG_TX_DONE;
				pframe->irq_type = CAMERA_IRQ_IMG;
				ret = camera_enqueue(&module->frm_queue, pframe);
				complete(&module->frm_com);
				pr_info("get out raw frame: fd:%d\n", pframe->buf.mfd[0]);
				return 0;
			}

			pframe->evt = IMG_TX_DONE;
			if (pframe->irq_type != CAMERA_IRQ_4IN1_DONE)
				pframe->irq_type = CAMERA_IRQ_IMG;
			if (module->cam_uinfo.is_4in1) {
				pframe = deal_4in1_raw_capture(module, pframe);
				if (!pframe)
					return 0;
			}
			/* set width,heigth */
			pframe->width = channel->ch_uinfo.dst_size.w;
			pframe->height = channel->ch_uinfo.dst_size.h;
			ret = camera_enqueue(&module->frm_queue, pframe);
			complete(&module->frm_com);
			pr_info("get out raw frame: fd:%d [%d %d]\n",
				pframe->buf.mfd[0], pframe->width, pframe->height);

		} else if (channel->ch_id == CAM_CH_PRE
			|| channel->ch_id == CAM_CH_VID) {

			pr_debug("proc isp path %d\n", channel->isp_path_id);
			/* ISP in_queue maybe overflow.
			 * If previous frame with size updating is dicarded by ISP,
			 * we should set it in current frame for ISP input
			 * If current frame also has new updating param,
			 * here will set it as previous one in a queue for ISP,
			 * ISP can check and free it.
			 */
			if (channel->isp_updata) {
				pr_info("next %p,  prev %p\n",
					pframe->param_data, channel->isp_updata);
				if (pframe->param_data) {
					cur = (struct isp_offline_param *)pframe->param_data;
					cur->prev = channel->isp_updata;
				} else {
					pframe->param_data = channel->isp_updata;
				}
				channel->isp_updata = NULL;
				pr_info("cur %p\n", pframe->param_data);
			}
			if((module->flash_skip_fid == pframe->fid)&&(module->flash_skip_fid != 0)){
				pr_debug("flash_skip_frame fd = %d\n",pframe->fid);
				ret = dcam_ops->cfg_path(module->dcam_dev_handle,
						DCAM_PATH_CFG_OUTPUT_BUF,
						channel->dcam_path_id, pframe);

				return ret;
			}

			ret = isp_ops->proc_frame(module->isp_dev_handle, pframe,
					channel->isp_path_id >> ISP_CTXID_OFFSET);
			if (ret) {
				pr_warn_ratelimited("warning: isp proc frame failed.\n");
				/* ISP in_queue maybe overflow.
				 * If current frame taking (param_data) for size updating
				 * we should hold it here and set it in next frame for ISP
				 */
				if (pframe->param_data) {
					cur = (struct isp_offline_param *)pframe->param_data;
					cur->prev = channel->isp_updata;
					channel->isp_updata = (void *)cur;
					pframe->param_data = NULL;
					pr_info("store:  cur %p   prev %p\n", cur, cur->prev);
				}
				ret = dcam_ops->cfg_path(module->dcam_dev_handle,
						DCAM_PATH_CFG_OUTPUT_BUF,
						channel->dcam_path_id, pframe);
				/* release sync if ISP don't need it */
				if (pframe->sync_data)
					dcam_if_release_sync(pframe->sync_data,
							     pframe);
			}
		} else if (channel->ch_id == CAM_CH_CAP) {
			if ((module->cap_status != CAM_CAPTURE_START) &&
				(module->cap_status != CAM_CAPTURE_RAWPROC)) {
				/*
				 * Release sync if we don't deliver this @pframe
				 * to ISP.
				 */
				if (pframe->sync_data)
					dcam_if_release_sync(pframe->sync_data,
							     pframe);
				if (module->cam_uinfo.is_dual)
					pframe = dual_fifo_queue(module,
						pframe, channel);

				if (pframe) {
					if (pframe->dcam_idx == DCAM_ID_1)
						ret = dcam_ops->cfg_path(
							 module->aux_dcam_dev,
							 DCAM_PATH_CFG_OUTPUT_BUF,
							 channel->aux_dcam_path_id, pframe);
					else
						ret = dcam_ops->cfg_path(
							 module->dcam_dev_handle,
							 DCAM_PATH_CFG_OUTPUT_BUF,
							 channel->dcam_path_id, pframe);
					}
				return ret;
			}

			/* cap scene special process */
			if (module->dcam_cap_status == DCAM_CAPTURE_START_WITH_TIMESTAMP) {

				pframe = deal_dual_frame(module,
						pframe, channel);

				if (!pframe)
					return 0;

				if (atomic_read(&module->capture_frames_dcam) > 0)
					atomic_dec(&module->capture_frames_dcam);

			} else if (module->cam_uinfo.is_4in1) {
				pframe = deal_4in1_frame(module,
						pframe, channel);
				if (!pframe)
					return 0;

				if (atomic_read(&module->capture_frames_dcam) > 0)
					atomic_dec(&module->capture_frames_dcam);

			} else if (module->cam_uinfo.dcam_slice_mode) {
				pframe = deal_bigsize_frame(module,
						pframe, channel);
				if (!pframe)
					return 0;

				if (atomic_read(&module->capture_frames_dcam) > 0)
					atomic_dec(&module->capture_frames_dcam);

			} else if (module->dcam_cap_status == DCAM_CAPTURE_START_FROM_NEXT_SOF) {

				if (pframe->boot_sensor_time < module->capture_times) {

					pr_info("cam%d cap skip frame type[%d] cap_time[%lld] sof_time[%lld]\n",
						module->idx,
						module->dcam_cap_status,
						module->capture_times,
						pframe->boot_sensor_time
						);
					if (pframe->sync_data)
						dcam_if_release_sync(pframe->sync_data, pframe);
					ret = dcam_ops->cfg_path(
						module->dcam_dev_handle,
						DCAM_PATH_CFG_OUTPUT_BUF,
						channel->dcam_path_id, pframe);

					return ret;
				} else {
					cap_frame = atomic_read(&module->capture_frames_dcam);
					skip_frame = atomic_read(&module->cap_skip_frames);
					if (cap_frame > 0 && skip_frame == 0) {
						pr_info("cam%d cap type[%d] num[%d]\n", module->idx,
							module->dcam_cap_status,
							cap_frame);
						atomic_dec(&module->capture_frames_dcam);
					} else {
						pr_info("cam%d cap type[%d] num[%d]\n", module->idx,
							module->dcam_cap_status, cap_frame);
						atomic_dec(&module->cap_skip_frames);
						if (pframe->sync_data)
							dcam_if_release_sync(pframe->sync_data, pframe);
						ret = dcam_ops->cfg_path(
							module->dcam_dev_handle,
							DCAM_PATH_CFG_OUTPUT_BUF,
							channel->dcam_path_id, pframe);

						return ret;
					}
				}
			}

			/* to isp */
			/* skip first frame for online capture (in case of non-zsl) because lsc abnormal */
			if (!module->cam_uinfo.is_4in1 && !module->cam_uinfo.dcam_slice_mode
				&& (module->cap_status != CAM_CAPTURE_RAWPROC) && (pframe->fid < 1))
				ret = 1;
			else
				ret = camera_enqueue(&channel->share_buf_queue, pframe);
			if (ret) {
				pr_debug("capture queue overflow\n");
				if (pframe->sync_data)
					dcam_if_release_sync(pframe->sync_data,
							     pframe);
				ret = dcam_ops->cfg_path(
						module->dcam_dev_handle,
						DCAM_PATH_CFG_OUTPUT_BUF,
						channel->dcam_path_id, pframe);
			} else {
				complete(&module->cap_thrd.thread_com);
			}
		} else {
			/* should not be here */
			pr_warn("reset dcam path out %d for ch %d\n",
				channel->dcam_path_id, channel->ch_id);
			ret = dcam_ops->cfg_path(module->dcam_dev_handle,
						DCAM_PATH_CFG_OUTPUT_BUF,
						channel->dcam_path_id, pframe);
		}
		break;
	case DCAM_CB_STATIS_DONE:
		pframe->evt = IMG_TX_DONE;
		pframe->irq_type = CAMERA_IRQ_STATIS;
		/* temp: statis/irq share same queue with frame data. */
		/* todo: separate statis/irq and frame queue. */

		if((module->flash_skip_fid == pframe->fid)&&(module->flash_skip_fid != 0)){
			ret = dcam_ops->ioctl(module->dcam_dev_handle,
						DCAM_IOCTL_CFG_STATIS_BUF_SKIP,
						pframe);

			return ret;
		}
		if (atomic_read(&module->state) == CAM_RUNNING) {
			ret = camera_enqueue(&module->frm_queue, pframe);
			if (ret) {
				put_empty_frame(pframe);
			} else {
				complete(&module->frm_com);
				pr_debug("get statis frame: %p, type %d, %d\n",
				pframe, pframe->irq_type, pframe->irq_property);
			}
		} else {
			put_empty_frame(pframe);
		}
		break;

	case DCAM_CB_IRQ_EVENT:
		if (pframe->irq_property == IRQ_DCAM_SN_EOF) {
			put_empty_frame(pframe);
			break;
		}
		if (pframe->irq_property == IRQ_DCAM_SOF) {
			 if((module->flash_info.led0_ctrl && module->flash_info.led0_status < FLASH_STATUS_MAX) ||
				(module->flash_info.led1_ctrl && module->flash_info.led1_status < FLASH_STATUS_MAX)) {
				flash_ops->start_flash(module->flash_core_handle);
				if(module->flash_info.flash_last_status != module->flash_info.led0_status)
					module->flash_skip_fid = pframe->fid;
				else
					pr_info("do not need skip");
				pr_info("skip_fram=%d\n", pframe->fid);
				module->flash_info.flash_last_status = module->flash_info.led0_status;
				module->flash_info.led0_ctrl = 0;
				module->flash_info.led1_ctrl = 0;
				module->flash_info.led0_status = 0;
				module->flash_info.led1_status = 0;
			}

		}
		/* temp: statis/irq share same queue with frame data. */
		/* todo: separate statis/irq and frame queue. */
		if (atomic_read(&module->state) == CAM_RUNNING) {
			ret = camera_enqueue(&module->frm_queue, pframe);
			if (ret) {
				put_empty_frame(pframe);
			} else {
				complete(&module->frm_com);
				pr_debug("get irq frame: %p, type %d, %d\n",
				pframe, pframe->irq_type, pframe->irq_property);
			}
		} else {
			put_empty_frame(pframe);
		}
		break;

	case DCAM_CB_RET_SRC_BUF:
		pr_info("dcam ret src frame %p. module %p, %d\n", pframe, module, module->idx);
		if (module->cam_uinfo.is_4in1) {
			/* 4in1 capture case: dcam offline src buffer
			 * should be re-used for dcam online output (raw)
			 */
			dcam_ops->cfg_path(module->dcam_dev_handle,
				DCAM_PATH_CFG_OUTPUT_BUF,
				channel->dcam_path_id, pframe);
		} else if (module->cam_uinfo.dcam_slice_mode) {
			/* 4in1 capture case: dcam offline src buffer
			 * should be re-used for dcam online output (raw)
			 */
			dcam_ops->cfg_path(module->dcam_dev_handle,
				DCAM_PATH_CFG_OUTPUT_BUF,
				channel->dcam_path_id, pframe);
		} else if ((module->cap_status == CAM_CAPTURE_RAWPROC) ||
			(atomic_read(&module->state) != CAM_RUNNING)) {
			/* for case raw capture post-proccessing
			 * and case 4in1 after stream off
			 * just release it, no need to return
			 */
			cambuf_put_ionbuf(&pframe->buf);
			put_empty_frame(pframe);
			pr_info("cap status %d, state %d\n",
				module->cap_status,
					atomic_read(&module->state));
		} else {
			pr_err("fail to get cap status\n");
			cambuf_put_ionbuf(&pframe->buf);
			put_empty_frame(pframe);
		}
		break;

	default:
		break;
	}

	return ret;
}

static inline uint32_t fix_scale(uint32_t size_in, uint32_t ratio16)
{
	uint64_t size_scaled;

	size_scaled = (uint64_t)size_in;
	size_scaled <<= (2 * RATIO_SHIFT);
	size_scaled = ((div64_u64(size_scaled, ratio16)) >> RATIO_SHIFT);
	return (uint32_t)size_scaled;
}

static void get_diff_trim(struct sprd_img_rect *orig,
	uint32_t ratio16, struct img_trim *trim0, struct img_trim *trim1)
{
	trim1->start_x = fix_scale(orig->x - trim0->start_x, ratio16);
	trim1->start_y = fix_scale(orig->y - trim0->start_y, ratio16);
	trim1->size_x =  fix_scale(orig->w, ratio16);
	trim1->size_x = ALIGN(trim1->size_x, 2);
	trim1->size_y =  fix_scale(orig->h, ratio16);
}

static inline void get_largest_crop(
	struct sprd_img_rect *crop_dst, struct sprd_img_rect *crop1)
{
	uint32_t end_x, end_y;
	uint32_t end_x_new, end_y_new;

	if (crop1) {
		end_x = crop_dst->x + crop_dst->w;
		end_y = crop_dst->y + crop_dst->h;
		end_x_new = crop1->x + crop1->w;
		end_y_new = crop1->y + crop1->h;

		crop_dst->x = MIN(crop1->x, crop_dst->x);
		crop_dst->y = MIN(crop1->y, crop_dst->y);
		end_x_new = MAX(end_x, end_x_new);
		end_y_new = MAX(end_y, end_y_new);
		crop_dst->w = end_x_new - crop_dst->x;
		crop_dst->h = end_y_new - crop_dst->y;
	}
}

static inline uint32_t multiply_ratio16(uint64_t num, uint32_t ratio16)
{
	return (uint32_t)((num * ratio16) >> 16);
}

static inline uint32_t divide_ratio16(uint64_t num, uint32_t ratio16)
{
	return (uint32_t)div64_u64(num << 16, ratio16);
}

static int cal_channel_swapsize(struct camera_module *module)
{
	uint32_t src_binning = 0;
	uint32_t ratio_min, shift;
	uint32_t ratio_p_w, ratio_p_h;
	uint32_t ratio_v_w, ratio_v_h;
	uint32_t ratio_p_w1, ratio_p_h1;
	uint32_t ratio_v_w1, ratio_v_h1;
	uint32_t isp_linebuf_len = g_camctrl.isp_linebuf_len;
	struct channel_context *ch_prev = NULL;
	struct channel_context *ch_vid = NULL;
	struct channel_context *ch_cap = NULL;
	struct img_size max_bypass, max_bin, max_rds, temp;
	struct img_size src_p, dst_p, dst_v, max;

	ch_prev = &module->channel[CAM_CH_PRE];
	ch_cap = &module->channel[CAM_CH_CAP];
	ch_vid = &module->channel[CAM_CH_VID];

	if (module->grp->hw_info->prj_id == SHARKL5pro) {
		if (ch_prev->ch_uinfo.src_size.w <= PRE_RDS_OUT) {
			module->zoom_solution = ZOOM_RDS;
			module->rds_limit= 10;
		}
	}

	if (ch_cap->enable) {
		max.w = ch_cap->ch_uinfo.src_size.w;
		max.h = ch_cap->ch_uinfo.src_size.h;
		ch_cap->swap_size = max;
		pr_info("idx %d , cap swap size %d %d\n", module->idx, max.w, max.h);
	}

	if (ch_prev->enable)
		ch_prev = &module->channel[CAM_CH_PRE];
	else if (!ch_prev->enable && ch_vid->enable)
		ch_prev = &module->channel[CAM_CH_VID];
	else
		return 0;

	if (module->cam_uinfo.is_4in1 || module->cam_uinfo.dcam_slice_mode) {
		ch_prev->ch_uinfo.src_size.w >>= 1;
		ch_prev->ch_uinfo.src_size.h >>= 1;
		ch_vid->ch_uinfo.src_size.w >>= 1;
		ch_vid->ch_uinfo.src_size.h >>= 1;
	}

	src_p.w = ch_prev->ch_uinfo.src_size.w;
	src_p.h = ch_prev->ch_uinfo.src_size.h;
	dst_p.w = ch_prev->ch_uinfo.dst_size.w;
	dst_p.h = ch_prev->ch_uinfo.dst_size.h;
	dst_v.w = dst_v.h = 1;
	if (ch_vid->enable) {
		dst_p.w = ch_vid->ch_uinfo.dst_size.w;
		dst_p.h = ch_vid->ch_uinfo.dst_size.h;
	}

	if ((src_p.w * 2) <= module->cam_uinfo.sn_max_size.w)
		src_binning = 1;

	/* bypass dcam scaler always */
	max_bypass = src_p;

	/* go through binning path */
	max_bin = src_p;
	shift = 0;
	if (src_binning == 1) {
		if ((max_bin.w > isp_linebuf_len) &&
			(dst_p.w <= isp_linebuf_len) &&
			(dst_v.w <= isp_linebuf_len))
			shift = 1;

		module->binning_limit = 0;
		if (module->zoom_solution == ZOOM_BINNING4)
			module->binning_limit = 1;
		else if (shift == 1)
			module->binning_limit = 1;

		pr_info("shift %d for binning, p=%d v=%d  src=%d, %d\n",
			shift, dst_p.w, dst_v.w, max_bin.w, isp_linebuf_len);
	} else {
		if ((max_bin.w >= (dst_p.w * 2)) &&
			(max_bin.w >= (dst_v.w * 2)))
			shift = 1;
		else if ((max_bin.w > isp_linebuf_len) &&
			(dst_p.w <= isp_linebuf_len) &&
			(dst_v.w <= isp_linebuf_len))
			shift = 1;

		module->binning_limit = 1;
		if (module->zoom_solution == ZOOM_BINNING4)
			module->binning_limit = 2;

		pr_info("shift %d for full, p=%d v=%d  src=%d, %d\n",
			shift, dst_p.w, dst_v.w, max_bin.w, isp_linebuf_len);
	}
	max_bin.w >>= shift;
	max_bin.h >>= shift;

	/* go through rds path */
	if ((dst_p.w == 0) || (dst_p.h == 0)) {
		pr_err("fail to get valid w %d h %d\n", dst_p.w, dst_p.h);
		return -EFAULT;
	}
	max = src_p;
	ratio_p_w = (1 << RATIO_SHIFT) * max.w / dst_p.w;
	ratio_p_h = (1 << RATIO_SHIFT) * max.h / dst_p.h;
	ratio_min = MIN(ratio_p_w, ratio_p_h);
	temp.w = ((max.h * dst_p.w) / dst_p.h) & (~3);
	temp.h = ((max.w * dst_p.h) / dst_p.w) & (~3);
	ratio_p_w1 = (1 << RATIO_SHIFT) * temp.w / dst_p.w;
	ratio_p_h1 = (1 << RATIO_SHIFT) * temp.h / dst_p.h;
	ratio_min = MIN(ratio_min, MIN(ratio_p_w1, ratio_p_h1));
	if (ch_vid->enable) {
		ratio_v_w = (1 << RATIO_SHIFT) * max.w / dst_v.w;
		ratio_v_h = (1 << RATIO_SHIFT) * max.h / dst_v.h;
		ratio_min = MIN(ratio_min, MIN(ratio_v_w, ratio_v_h));
		temp.w = ((max.h * dst_v.w) / dst_v.h) & (~3);
		temp.h = ((max.w * dst_v.h) / dst_v.w) & (~3);
		ratio_v_w1 = (1 << RATIO_SHIFT) * temp.w / dst_v.w;
		ratio_v_h1 = (1 << RATIO_SHIFT) * temp.h / dst_v.h;
		ratio_min = MIN(ratio_min, MIN(ratio_v_w1, ratio_v_h1));
	}
	ratio_min = MIN(ratio_min, ((module->rds_limit << RATIO_SHIFT) / 10));
	ratio_min = MAX(ratio_min, (1 << RATIO_SHIFT));
	max.w = fix_scale(max.w, ratio_min);
	max.h = fix_scale(max.h, ratio_min);
	if (max.w > DCAM_RDS_OUT_LIMIT) {
		max.w = DCAM_RDS_OUT_LIMIT;
		max.h= src_p.h * max.w / src_p.w;
	}
	max.w = ALIGN(max.w + ALIGN_OFFSET, ALIGN_OFFSET);
	max.h = ALIGN(max.h + ALIGN_OFFSET, ALIGN_OFFSET);
	max_rds = max;

	/* for adaptive solution, select max of rds/bin */
	switch (module->zoom_solution) {
	case ZOOM_DEFAULT:
		ch_prev->swap_size = max_bypass;
		break;
	case ZOOM_BINNING2:
	case ZOOM_BINNING4:
		ch_prev->swap_size = max_bin;
		break;
	case ZOOM_RDS:
		ch_prev->swap_size = max_rds;
		break;
	case ZOOM_ADAPTIVE:
		ch_prev->swap_size.w = MAX(max_bin.w, max_rds.w);
		ch_prev->swap_size.h = MAX(max_bin.h, max_rds.h);
		break;
	default:
		pr_warn("unknown zoom solution %d\n", module->zoom_solution);
		ch_prev->swap_size = max_bypass;
		break;
	}
	pr_info("prev bypass size (%d %d), bin size (%d %d)\n",
		max_bypass.w, max_bypass.h, max_bin.w, max_bin.h);
	pr_info("prev swap size (%d %d), rds size (%d %d)\n",
		ch_prev->swap_size.w, ch_prev->swap_size.h,
		max_rds.w, max_rds.h);

	return 0;
}

static int cal_channel_size_bininig(
	struct camera_module *module, uint32_t bypass_always)
{
	uint32_t shift = 0, factor;
	uint32_t src_binning = 0;
	struct channel_context *ch_prev;
	struct channel_context *ch_vid;
	struct channel_context *ch_cap;
	struct sprd_img_rect *crop_p, *crop_v, *crop_c;
	struct sprd_img_rect crop_dst;
	struct img_trim trim_pv = {0};
	struct img_trim trim_c = {0};
	struct img_trim *isp_trim;
	struct img_size src_p, dst_p, dst_v, dcam_out;

	ch_prev = &module->channel[CAM_CH_PRE];
	ch_cap = &module->channel[CAM_CH_CAP];
	ch_vid = &module->channel[CAM_CH_VID];
	if (!ch_prev->enable && !ch_cap->enable && !ch_vid->enable)
		return 0;

	dcam_out.w = dcam_out.h = 0;
	dst_p.w = dst_p.h = 1;
	dst_v.w = dst_v.h = 1;
	crop_p = crop_v = crop_c = NULL;
	if (ch_prev->enable || (!ch_prev->enable && ch_vid->enable)) {
		src_p.w = ch_prev->ch_uinfo.src_size.w;
		src_p.h = ch_prev->ch_uinfo.src_size.h;
		crop_p = &ch_prev->ch_uinfo.src_crop;
		dst_p.w = ch_prev->ch_uinfo.dst_size.w;
		dst_p.h = ch_prev->ch_uinfo.dst_size.h;
		if ((src_p.w * 2) <= module->cam_uinfo.sn_max_size.w)
			src_binning = 1;
		pr_info("src crop prev %u %u %u %u\n",
			crop_p->x, crop_p->y, crop_p->w, crop_p->h);
	}
	if (ch_vid->enable) {
		crop_v = &ch_vid->ch_uinfo.src_crop;
		dst_v.w = ch_vid->ch_uinfo.dst_size.w;
		dst_v.h = ch_vid->ch_uinfo.dst_size.h;
		pr_info("src crop vid %u %u %u %u\n",
			crop_v->x, crop_v->y, crop_v->w, crop_v->h);
	}
	if (ch_prev->enable || (!ch_prev->enable && ch_vid->enable)) {
		crop_dst = *crop_p;
		get_largest_crop(&crop_dst, crop_v);
		trim_pv.start_x = crop_dst.x;
		trim_pv.start_y = crop_dst.y;
		trim_pv.size_x = crop_dst.w;
		trim_pv.size_y = crop_dst.h;
	}

	if (ch_cap->enable) {
		trim_c.start_x = ch_cap->ch_uinfo.src_crop.x;
		trim_c.start_y = ch_cap->ch_uinfo.src_crop.y;
		trim_c.size_x = ch_cap->ch_uinfo.src_crop.w;
		trim_c.size_y = ch_cap->ch_uinfo.src_crop.h;
	}
	pr_info("trim_pv: %u %u %u %u\n", trim_pv.start_x,
		trim_pv.start_y, trim_pv.size_x, trim_pv.size_y);
	pr_info("trim_c: %u %u %u %u\n", trim_c.start_x,
		trim_c.start_y, trim_c.size_x, trim_c.size_y);

	if (ch_prev->enable || (!ch_prev->enable && ch_vid->enable)) {
		shift = 0;
		if (bypass_always == 0) {
			factor = (src_binning ? 10 : 9);
			if ((trim_pv.size_x >= (dst_p.w * 4)) &&
				(trim_pv.size_x >= (dst_v.w * 4)) &&
				(trim_pv.size_y >= (dst_p.h * 4)) &&
				(trim_pv.size_y >= (dst_v.h * 4)))
				shift = 2;
			else if ((trim_pv.size_x >= (dst_p.w * 2 * factor / 10)) &&
				(trim_pv.size_x >= (dst_v.w * 2 * factor / 10)) &&
				(trim_pv.size_y >= (dst_p.h * 2 * factor / 10)) &&
				(trim_pv.size_y >= (dst_v.h * 2 * factor / 10)))
					shift = 1;
			if (((trim_pv.size_x >> shift) > ch_prev->swap_size.w) ||
				((trim_pv.size_y >> shift) > ch_prev->swap_size.h))
				shift++;
		}
		if (shift > 2) {
			pr_info("dcam binning should limit to 1/4\n");
			shift = 2;
		}
		if (shift > module->binning_limit) {
			pr_info("bin shift limit to %d\n", module->binning_limit);
			shift = module->binning_limit;
		}

		if (shift == 2) {
			/* make sure output 2 aligned and trim invalid */
			pr_debug("shift 2 trim_pv %d %d %d %d\n",
				trim_pv.start_x, trim_pv.start_y,
				trim_pv.size_x, trim_pv.size_y);
			if ((trim_pv.size_x >> 2) & 1) {
				trim_pv.size_x = (trim_pv.size_x + 4) & ~7;
				if ((trim_pv.start_x + trim_pv.size_x) > src_p.w)
					trim_pv.size_x -= 8;
				trim_pv.start_x = (src_p.w - trim_pv.size_x) >> 1;
			}
			if ((trim_pv.size_y >> 2) & 1) {
				trim_pv.size_y = (trim_pv.size_y + 4) & ~7;
				if ((trim_pv.start_y + trim_pv.size_y) > src_p.h)
					trim_pv.size_y -= 8;
				trim_pv.start_y = (src_p.h - trim_pv.size_y) >> 1;
			}
			pr_debug("shift 2 trim_pv final %d %d %d %d\n",
				trim_pv.start_x, trim_pv.start_y,
				trim_pv.size_x, trim_pv.size_y);
		}

		dcam_out.w = (trim_pv.size_x >> shift);
		dcam_out.w = ALIGN_DOWN(dcam_out.w, 2);
		dcam_out.h = (trim_pv.size_y >> shift);
		dcam_out.h = ALIGN_DOWN(dcam_out.h, 2);

		/* avoid isp fetch fbd timeout when isp src width > 1856 */
		if (dcam_out.w > 1856)
			ch_prev->compress_input = 0;

		if (ch_prev->compress_input) {
			dcam_out.h = ALIGN_DOWN(dcam_out.h, DCAM_FBC_TILE_HEIGHT);
			trim_pv.size_y = (dcam_out.h << shift);
		}

		pr_info("shift %d, dst_p %u %u, dst_v %u %u, dcam_out %u %u\n",
			shift, dst_p.w, dst_p.h, dst_v.w, dst_v.h, dcam_out.w, dcam_out.h);

		/* applied latest rect for aem */
		module->zoom_ratio = src_p.w * ZOOM_RATIO_DEFAULT / crop_p->w;
		ch_prev->trim_dcam = trim_pv;
		ch_prev->rds_ratio = ((1 << shift) << RATIO_SHIFT);
		ch_prev->dst_dcam = dcam_out;

		isp_trim = &ch_prev->trim_isp;
		isp_trim->size_x = ((ch_prev->ch_uinfo.src_crop.w >> shift) + 1) & ~1;
		isp_trim->size_y = ((ch_prev->ch_uinfo.src_crop.h >> shift) + 1) & ~1;
		isp_trim->size_x = min(isp_trim->size_x, dcam_out.w);
		isp_trim->size_y = min(isp_trim->size_y, dcam_out.h);
		isp_trim->start_x = ((dcam_out.w - isp_trim->size_x) >> 1) & ~1;
		isp_trim->start_y = ((dcam_out.h - isp_trim->size_y) >> 1) & ~1;
		pr_info("trim isp, prev %u %u %u %u\n",
			isp_trim->start_x, isp_trim->start_y,
			isp_trim->size_x, isp_trim->size_y);
	}

	if (ch_vid->enable) {
		ch_vid->dst_dcam = dcam_out;
		ch_vid->trim_dcam = trim_pv;
		isp_trim = &ch_vid->trim_isp;
		isp_trim->size_x = ((ch_vid->ch_uinfo.src_crop.w >> shift) + 1) & ~1;
		isp_trim->size_y = ((ch_vid->ch_uinfo.src_crop.h >> shift) + 1) & ~1;
		isp_trim->size_x = min(isp_trim->size_x, dcam_out.w);
		isp_trim->size_y = min(isp_trim->size_y, dcam_out.h);
		isp_trim->start_x = ((dcam_out.w - isp_trim->size_x) >> 1) & ~1;
		isp_trim->start_y = ((dcam_out.h - isp_trim->size_y) >> 1) & ~1;
		pr_info("trim isp, vid %u %u %u %u\n",
			isp_trim->start_x, isp_trim->start_y,
			isp_trim->size_x, isp_trim->size_y);
	}

	if (ch_cap->enable) {
		ch_cap->trim_dcam = trim_c;
		get_diff_trim(&ch_cap->ch_uinfo.src_crop,
			(1 << RATIO_SHIFT), &trim_c, &ch_cap->trim_isp);
		ch_cap->trim_isp.start_x &= ~1;
		ch_cap->trim_isp.start_y &= ~1;
		ch_cap->trim_isp.size_x &= ~1;
		ch_cap->trim_isp.size_y &= ~1;
		if (ch_cap->trim_isp.size_x > trim_c.size_x)
			ch_cap->trim_isp.size_x = trim_c.size_x;
		if (ch_cap->trim_isp.size_y > trim_c.size_y)
			ch_cap->trim_isp.size_y = trim_c.size_y;
		pr_info("trim isp, cap %d %d %d %d\n",
			ch_cap->trim_isp.start_x, ch_cap->trim_isp.start_y,
			ch_cap->trim_isp.size_x, ch_cap->trim_isp.size_y);
	}

	pr_info("done\n");
	return 0;
}

static int cal_channel_size_rds(struct camera_module *module)
{
	uint32_t ratio_min, is_same_fov = 0;
	uint32_t ratio_p_w, ratio_p_h;
	uint32_t ratio_v_w, ratio_v_h;
	uint32_t ratio16_w, ratio16_h;
	uint32_t align_w, align_h;
	struct channel_context *ch_prev;
	struct channel_context *ch_vid;
	struct channel_context *ch_cap;
	struct sprd_img_rect *crop_p, *crop_v, *crop_c;
	struct sprd_img_rect crop_dst;
	struct img_trim trim_pv = {0};
	struct img_trim trim_c = {0};
	struct img_size src_p, dst_p, dst_v, dcam_out;

	ch_prev = &module->channel[CAM_CH_PRE];
	ch_cap = &module->channel[CAM_CH_CAP];
	ch_vid = &module->channel[CAM_CH_VID];
	if (!ch_prev->enable && !ch_cap->enable && !ch_vid->enable)
		return 0;

	dst_p.w = dst_p.h = 1;
	dst_v.w = dst_v.h = 1;
	ratio_v_w = ratio_v_h = 1;
	crop_p = crop_v = crop_c = NULL;
	if (ch_prev->enable) {
		src_p.w = ch_prev->ch_uinfo.src_size.w;
		src_p.h = ch_prev->ch_uinfo.src_size.h;
		crop_p = &ch_prev->ch_uinfo.src_crop;
		dst_p.w = ch_prev->ch_uinfo.dst_size.w;
		dst_p.h = ch_prev->ch_uinfo.dst_size.h;
		pr_info("src crop prev %u %u %u %u\n",
			crop_p->x, crop_p->y, crop_p->w, crop_p->h);
	}

	if (ch_vid->enable) {
		crop_v = &ch_vid->ch_uinfo.src_crop;
		dst_v.w = ch_vid->ch_uinfo.dst_size.w;
		dst_v.h = ch_vid->ch_uinfo.dst_size.h;
		pr_info("src crop vid %u %u %u %u\n",
			crop_v->x, crop_v->y, crop_v->w, crop_v->h);
	}

	if (ch_cap->enable && ch_prev->enable &&
		(ch_cap->mode_ltm == MODE_LTM_PRE)) {
		crop_c = &ch_cap->ch_uinfo.src_crop;
		is_same_fov = 1;
		pr_info("src crop cap %d %d %d %d\n", crop_c->x, crop_c->y,
			crop_c->x + crop_c->w, crop_c->y + crop_c->h);
	}

	if (ch_prev->enable) {
		crop_dst = *crop_p;
		get_largest_crop(&crop_dst, crop_v);
		get_largest_crop(&crop_dst, crop_c);
		trim_pv.start_x = crop_dst.x;
		trim_pv.start_y = crop_dst.y;
		trim_pv.size_x = crop_dst.w;
		trim_pv.size_y = crop_dst.h;
	}

	if (is_same_fov)
		trim_c = trim_pv;
	else if (ch_cap->enable) {
		trim_c.start_x = ch_cap->ch_uinfo.src_crop.x & ~1;
		trim_c.start_y = ch_cap->ch_uinfo.src_crop.y & ~1;
		trim_c.size_x = (ch_cap->ch_uinfo.src_crop.w + 1) & ~1;
		trim_c.size_y = (ch_cap->ch_uinfo.src_crop.h + 1) & ~1;

		if (ch_cap->compress_input) {
			uint32_t aligned_y;

			aligned_y = ALIGN_DOWN(trim_c.start_y, 4);
			trim_c.size_y += trim_c.start_y - aligned_y;
			trim_c.start_y = aligned_y;
		}
	}

	pr_info("trim_pv: %u %u %u %u\n", trim_pv.start_x, trim_pv.start_y,
		trim_pv.size_x, trim_pv.size_y);
	pr_info("trim_c: %u %u %u %u\n", trim_c.start_x, trim_c.start_y,
		trim_c.size_x, trim_c.size_y);

	if (ch_prev->enable) {
		ratio_min = 1 << RATIO_SHIFT;
		if (module->zoom_solution >= ZOOM_RDS) {
			ratio_p_w = (1 << RATIO_SHIFT) * crop_p->w / dst_p.w;
			ratio_p_h = (1 << RATIO_SHIFT) * crop_p->h / dst_p.h;
			ratio_min = MIN(ratio_p_w, ratio_p_h);
			if (ch_vid->enable) {
				ratio_v_w = (1 << RATIO_SHIFT) * crop_v->w / dst_v.w;
				ratio_v_h = (1 << RATIO_SHIFT) * crop_v->h / dst_v.h;
				ratio_min = MIN(ratio_min, MIN(ratio_v_w, ratio_v_h));
			}
			ratio_min = MIN(ratio_min, ((module->rds_limit << RATIO_SHIFT) / 10));
			ratio_min = MAX(ratio_min, (1 << RATIO_SHIFT));
			pr_info("ratio_p %d %d, ratio_v %d %d ratio_min %d\n",
				ratio_p_w, ratio_p_h, ratio_v_w, ratio_v_h, ratio_min);
		}

		/* align bin path output size */
		align_w = align_h = DCAM_RDS_OUT_ALIGN;
		align_w = MAX(align_w, DCAM_OUTPUT_DEBUG_ALIGN);
		dcam_out.w = divide_ratio16(trim_pv.size_x, ratio_min);
		dcam_out.h = divide_ratio16(trim_pv.size_y, ratio_min);

		/* avoid isp fetch fbd timeout when isp src width > 1856 */
		if (dcam_out.w > 1856)
			ch_prev->compress_input = 0;

		if (ch_prev->compress_input)
			align_h = MAX(align_h, DCAM_FBC_TILE_HEIGHT);

		dcam_out.w = ALIGN(dcam_out.w, align_w);
		dcam_out.h = ALIGN(dcam_out.h, align_h);

		/* keep same ratio between width and height */
		ratio16_w = div_u64((uint64_t)trim_pv.size_x << RATIO_SHIFT, dcam_out.w);
		ratio16_h = div_u64((uint64_t)trim_pv.size_y << RATIO_SHIFT, dcam_out.h);
		ratio_min = min(ratio16_w, ratio16_h);

		/* if sensor size is too small */
		if (src_p.w < dcam_out.w || src_p.h < dcam_out.h) {
			dcam_out.w = src_p.w;
			dcam_out.h = src_p.h;
			if (ch_prev->compress_input)
				dcam_out.h = ALIGN_DOWN(dcam_out.h,
							DCAM_FBC_TILE_HEIGHT);
			ratio_min = 1 << RATIO_SHIFT;
		}

		if ((1 << RATIO_SHIFT) >= ratio_min) {
			/* enlarge @trim_pv and crop it in isp */
			uint32_t align = 2; /* TODO set to 4 for zzhdr */

			trim_pv.size_x = max(trim_pv.size_x, dcam_out.w);
			trim_pv.size_y = max(trim_pv.size_y, dcam_out.h);
			trim_pv.size_x = ALIGN(trim_pv.size_x, align >> 1);
			trim_pv.size_y = ALIGN(trim_pv.size_y, align >> 1);
			if (src_p.w >= trim_pv.size_x)
				trim_pv.start_x = (src_p.w - trim_pv.size_x) >> 1;
			else
				trim_pv.start_x = 0;
			if (src_p.h >= trim_pv.size_y)
				trim_pv.start_y = (src_p.h - trim_pv.size_y) >> 1;
			else
				trim_pv.start_y = 0;
			trim_pv.start_x = ALIGN_DOWN(trim_pv.start_x, align);
			trim_pv.start_y = ALIGN_DOWN(trim_pv.start_y, align);

			ratio_min = 1 << RATIO_SHIFT;
			pr_info("trim_pv aligned %u %u %u %u\n",
				trim_pv.start_x, trim_pv.start_y,
				trim_pv.size_x, trim_pv.size_y);
		} else {
			dcam_out.w = divide_ratio16(trim_pv.size_x, ratio_min);
			dcam_out.h = divide_ratio16(trim_pv.size_y, ratio_min);
			dcam_out.w = ALIGN(dcam_out.w, align_w);
			dcam_out.h = ALIGN(dcam_out.h, align_h);
		}

		/* check rds out limit if rds used */
		if (dcam_out.w > DCAM_RDS_OUT_LIMIT) {
			dcam_out.w = DCAM_RDS_OUT_LIMIT;
			dcam_out.h = dcam_out.w * trim_pv.size_y / trim_pv.size_x;
			dcam_out.w = ALIGN(dcam_out.w, align_w);
			dcam_out.h = ALIGN(dcam_out.h, align_h);

			/* keep same ratio between width and height */
			ratio16_w = div_u64((uint64_t)trim_pv.size_x << RATIO_SHIFT, dcam_out.w);
			ratio16_h = div_u64((uint64_t)trim_pv.size_y << RATIO_SHIFT, dcam_out.h);
			ratio_min = min(ratio16_w, ratio16_h);
		}

		pr_info("dst_p %u %u, dst_v %u %u, dcam_out %u %u, ratio %u\n",
			dst_p.w, dst_p.h, dst_v.w, dst_v.h,
			dcam_out.w, dcam_out.h, ratio_min);

		/* applied latest rect for aem */
		module->zoom_ratio = src_p.w * ZOOM_RATIO_DEFAULT / crop_p->w;
		ch_prev->trim_dcam = trim_pv;
		ch_prev->rds_ratio = ratio_min;/* rds_ratio is not used */
		ch_prev->dst_dcam = dcam_out;

		ch_prev->trim_isp.size_x =
			divide_ratio16(ch_prev->ch_uinfo.src_crop.w, ratio_min);
		ch_prev->trim_isp.size_y =
			divide_ratio16(ch_prev->ch_uinfo.src_crop.h, ratio_min);
		ch_prev->trim_isp.size_x = min(ch_prev->trim_isp.size_x, dcam_out.w);
		ch_prev->trim_isp.size_y = min(ch_prev->trim_isp.size_y, dcam_out.h);
		ch_prev->trim_isp.start_x =
				(dcam_out.w - ch_prev->trim_isp.size_x) >> 1;
		ch_prev->trim_isp.start_y =
				(dcam_out.h - ch_prev->trim_isp.size_y) >> 1;

		pr_info("trim isp, prev %u %u %u %u\n",
			ch_prev->trim_isp.start_x, ch_prev->trim_isp.start_y,
			ch_prev->trim_isp.size_x, ch_prev->trim_isp.size_y);

		if (ch_vid->enable) {
			ch_vid->trim_isp.size_x =
				divide_ratio16(ch_vid->ch_uinfo.src_crop.w, ratio_min);
			ch_vid->trim_isp.size_y =
				divide_ratio16(ch_vid->ch_uinfo.src_crop.h, ratio_min);
			ch_vid->trim_isp.size_x = min(ch_vid->trim_isp.size_x, dcam_out.w);
			ch_vid->trim_isp.size_y = min(ch_vid->trim_isp.size_y, dcam_out.h);
			ch_vid->trim_isp.start_x =
					(dcam_out.w - ch_vid->trim_isp.size_x) >> 1;
			ch_vid->trim_isp.start_y =
					(dcam_out.h - ch_vid->trim_isp.size_y) >> 1;

			pr_info("trim isp, vid %d %d %d %d\n",
				ch_vid->trim_isp.start_x, ch_vid->trim_isp.start_y,
				ch_vid->trim_isp.size_x, ch_vid->trim_isp.size_y);
		}
	}

	if (ch_cap->enable) {
		ch_cap->trim_dcam = trim_c;
		get_diff_trim(&ch_cap->ch_uinfo.src_crop,
			(1 << RATIO_SHIFT), &trim_c, &ch_cap->trim_isp);
		ch_cap->trim_isp.start_x &= ~1;
		ch_cap->trim_isp.start_y &= ~1;
		ch_cap->trim_isp.size_x &= ~1;
		ch_cap->trim_isp.size_y &= ~1;
		if (ch_cap->trim_isp.size_x > trim_c.size_x)
			ch_cap->trim_isp.size_x = trim_c.size_x;
		if (ch_cap->trim_isp.size_y > trim_c.size_y)
			ch_cap->trim_isp.size_y = trim_c.size_y;
		pr_info("trim isp, cap %d %d %d %d\n",
				ch_cap->trim_isp.start_x, ch_cap->trim_isp.start_y,
				ch_cap->trim_isp.size_x, ch_cap->trim_isp.size_y);
	}

	pr_info("done.\n");

	return 0;
}

static int config_channel_bigsize(
	struct camera_module *module,
	struct channel_context *channel)
{
	int ret = 0;
	int i, total, iommu_enable;
	uint32_t width, height, is_loose, size = 0;
	struct camera_uchannel *ch_uinfo = NULL;
	struct dcam_path_cfg_param ch_desc;
	struct camera_frame *pframe;

	ch_uinfo = &channel->ch_uinfo;
	iommu_enable = module->iommu_enable;
	width = channel->swap_size.w;
	height = channel->swap_size.h;
	is_loose = module->cam_uinfo.sensor_if.if_spec.mipi.is_loose;

	if (channel->ch_uinfo.sn_fmt == IMG_PIX_FMT_GREY)
		size = cal_sprd_raw_pitch(width, is_loose) * height;
	size = ALIGN(size, CAM_BUF_ALIGN_SIZE);

	/* dcam1 alloc memory */
	total = 5;

	/* non-zsl capture for single frame */
	if (channel->ch_id == CAM_CH_CAP &&
		module->channel[CAM_CH_PRE].enable == 0 &&
		module->channel[CAM_CH_VID].enable == 0)
		total = 1;

	pr_info("ch %d alloc shared buffer size: %u (w %u h %u), num %d\n",
		channel->ch_id, size, width, height, total);

	for (i = 0; i < total; i++) {
		do {
			pframe = get_empty_frame();
			pframe->channel_id = channel->ch_id;
			pframe->is_compressed = channel->compress_input;
			pframe->compress_4bit_bypass =
					channel->compress_4bit_bypass;
			pframe->width = width;
			pframe->height = height;
			pframe->endian = ENDIAN_LITTLE;
			pframe->pattern = module->cam_uinfo.sensor_if.img_ptn;
			pframe->buf.buf_sec = 0;
			ret = cambuf_alloc(
					&pframe->buf, size,
					0, iommu_enable);
			if (ret) {
				pr_err("fail to alloc buf: %d ch %d\n",
						i, channel->ch_id);
				put_empty_frame(pframe);
				atomic_inc(&channel->err_status);
				break;
			}
			/* cfg aux_dcam out_buf */
			ret = dcam_ops->cfg_path(
				module->aux_dcam_dev,
				DCAM_PATH_CFG_OUTPUT_BUF,
				channel->aux_dcam_path_id,
				pframe);
		} while (0);
	}

	/* dcam1 cfg path size */
	memset(&ch_desc, 0, sizeof(ch_desc));
	ch_desc.input_size.w = ch_uinfo->src_size.w;
	ch_desc.input_size.h = ch_uinfo->src_size.h;
	ch_desc.output_size = ch_desc.input_size;
	ch_desc.input_trim.start_x = 0;
	ch_desc.input_trim.start_y = 0;
	ch_desc.input_trim.size_x = ch_desc.input_size.w;
	ch_desc.input_trim.size_y = ch_desc.input_size.h;
	ch_desc.is_loose = module->cam_uinfo.sensor_if.if_spec.mipi.is_loose;
	ch_desc.is_4in1 = module->cam_uinfo.is_4in1;

	pr_info("update dcam path %d size for channel %d is_loose %d 4in1 %d\n",
		channel->dcam_path_id, channel->ch_id, ch_desc.is_loose, ch_desc.is_4in1);

	ret = dcam_ops->cfg_path(module->aux_dcam_dev,
				DCAM_PATH_CFG_SIZE,
				channel->aux_dcam_path_id, &ch_desc);

	pr_info("update channel size done for CAP\n");
	return ret;
}

static int capture_is_superzoom(struct camera_uchannel *ch_uinfo,
	struct channel_context *channel, int coeff)
{
	int ret = 0;

	if (!ch_uinfo || !channel) {
		pr_err("fail to input ptr ctx_size or channel is NULL\n");
		return ret;
	}

	pr_debug("superzoom trim_isp: %d, %d, dst size: %d, %d\n",
		channel->trim_isp.size_x, channel->trim_isp.size_y,
		ch_uinfo->dst_size.w, ch_uinfo->dst_size.h);

	if (ch_uinfo->dst_size.w > coeff * channel->trim_isp.size_x
		|| ch_uinfo->dst_size.h > coeff * channel->trim_isp.size_y)
		ret = 1;

	return ret;
}

static int config_channel_size(
	struct camera_module *module,
	struct channel_context *channel)
{
	int ret = 0;
	int is_zoom, loop_count;
	int superzoom_coeff = SUPERZOOM_DEFAULT_COEFF;
	uint32_t isp_ctx_id, isp_path_id;
	struct isp_offline_param *isp_param;
	struct channel_context *vid;
	struct camera_uchannel *ch_uinfo = NULL;
	struct dcam_path_cfg_param ch_desc;
	struct isp_ctx_size_desc ctx_size;
	struct img_trim path_trim;

	if (atomic_read(&module->state) == CAM_RUNNING) {
		is_zoom = 1;
		loop_count = 5;
	} else {
		is_zoom = 0;
		loop_count = 1;
	}

	ch_uinfo = &channel->ch_uinfo;
	/* DCAM full path not updating for zoom. */
	if (is_zoom && channel->ch_id == CAM_CH_CAP)
		goto cfg_isp;

	if (!is_zoom && (channel->swap_size.w > 0)) {
		camera_queue_init(&channel->share_buf_queue,
			CAM_SHARED_BUF_NUM, 0, put_k_frame);

		/* alloc middle buffer for channel */
		channel->alloc_start = 1;
		channel->alloc_buf_work.priv_data = module;
		atomic_set(&channel->alloc_buf_work.status, CAM_WORK_PENDING);
		INIT_WORK(&channel->alloc_buf_work.work, alloc_buffers);
		pr_info("module %p, channel %d, size %d %d\n", module,
			channel->ch_id, channel->swap_size.w, channel->swap_size.h);
		queue_work(module->workqueue, &channel->alloc_buf_work.work);
	}

	memset(&ch_desc, 0, sizeof(ch_desc));
	ch_desc.input_size.w = ch_uinfo->src_size.w;
	ch_desc.input_size.h = ch_uinfo->src_size.h;
	if (channel->ch_id == CAM_CH_CAP) {
		/* no trim in dcam full path. */
		ch_desc.output_size = ch_desc.input_size;
		ch_desc.input_trim.start_x = 0;
		ch_desc.input_trim.start_y = 0;
		ch_desc.input_trim.size_x = ch_desc.input_size.w;
		ch_desc.input_trim.size_y = ch_desc.input_size.h;
	} else {
		if (channel->rds_ratio & ((1 << RATIO_SHIFT) - 1))
			ch_desc.force_rds = 1;
		else
			ch_desc.force_rds = 0;
		ch_desc.input_trim = channel->trim_dcam;
		ch_desc.output_size = channel->dst_dcam;
	}

	pr_info("update dcam path %d size for channel %d\n",
		channel->dcam_path_id, channel->ch_id);

	if (channel->ch_id == CAM_CH_PRE || channel->ch_id == CAM_CH_VID) {
		isp_param = kzalloc(sizeof(struct isp_offline_param), GFP_KERNEL);
		if (isp_param == NULL) {
			pr_err("fail to alloc memory.\n");
			return -ENOMEM;
		}
		ch_desc.priv_size_data = (void *)isp_param;
		isp_param->valid |= ISP_SRC_SIZE;
		isp_param->src_info.src_size = ch_desc.input_size;
		isp_param->src_info.src_trim = ch_desc.input_trim;
		isp_param->src_info.dst_size = ch_desc.output_size;
		isp_param->valid |= ISP_PATH0_TRIM;
		isp_param->trim_path[0] = channel->trim_isp;
		vid = &module->channel[CAM_CH_VID];
		if (vid->enable) {
			isp_param->valid |= ISP_PATH1_TRIM;
			isp_param->trim_path[1] = vid->trim_isp;
		}
		pr_debug("isp_param %p\n", isp_param);
	}

	do {
		ret = dcam_ops->cfg_path(module->dcam_dev_handle,
				DCAM_PATH_CFG_SIZE,
				channel->dcam_path_id, &ch_desc);
		if (ret) {
			/* todo: if previous updating is not applied yet.
			 * this case will happen.
			 * (zoom ratio changes in short gap)
			 * wait here and retry(how long?)
			 */
			pr_info("wait to update dcam path %d size, zoom %d, lp %d\n",
				channel->dcam_path_id, is_zoom, loop_count);
			msleep(20);
		} else {
			break;
		}
	} while (--loop_count);

	if (ret && ch_desc.priv_size_data)
		kfree(ch_desc.priv_size_data);

	/* isp path for prev/video will update from input frame. */
	if (channel->ch_id == CAM_CH_PRE) {
		pr_info("update channel size done for preview\n");
		return ret;
	}

cfg_isp:
	isp_ctx_id = (channel->isp_path_id >> ISP_CTXID_OFFSET);
	isp_path_id = (channel->isp_path_id & ISP_PATHID_MASK);

	if (channel->ch_id == CAM_CH_CAP) {
		struct img_size size = {0};
		int superzoom_flag = 0;

		ctx_size.src.w = ch_uinfo->src_size.w;
		ctx_size.src.h = ch_uinfo->src_size.h;
		ctx_size.crop = channel->trim_dcam;
		pr_debug("cfg isp sw %d size src w %d, h %d, crop %d %d %d %d\n",
			isp_ctx_id, ctx_size.src.w, ctx_size.src.h,
			ctx_size.crop.start_x, ctx_size.crop.start_y, ctx_size.crop.size_x, ctx_size.crop.size_y);
		ret = isp_ops->cfg_path(module->isp_dev_handle,
				ISP_PATH_CFG_CTX_SIZE,
				isp_ctx_id, 0, &ctx_size);
		if (ret != 0)
			goto exit;

		if (s_dbg_superzoom_coeff > 0 &&
			s_dbg_superzoom_coeff < SUPERZOOM_COEFF_UP_MAX) {
			superzoom_coeff = s_dbg_superzoom_coeff;
			pr_debug("sw %d, user proc sfs val , superzoom coeff %d, \n",
				isp_ctx_id, superzoom_coeff);
		}

		if (capture_is_superzoom(ch_uinfo, channel, superzoom_coeff)) {
			size.w = superzoom_coeff * channel->trim_isp.size_x;
			size.h = superzoom_coeff * channel->trim_isp.size_y;
			if (size.w > ch_uinfo->dst_size.w)
				size.w = ch_uinfo->dst_size.w;
			if (size.h > ch_uinfo->dst_size.h)
				size.h = ch_uinfo->dst_size.h;
			channel->cap_status = TO_DO_CAP_SUPERZOOM;
			superzoom_flag = 1;
			pr_debug("dcam id %d, sw %d, superzoom path dst w %d, h %d, channel: trim w %d, h %d, ch_uinfo dst %d, %d\n",
				module->idx, isp_ctx_id, size.w, size.h, channel->trim_isp.size_x,
				channel->trim_isp.size_y, ch_uinfo->dst_size.w, ch_uinfo->dst_size.h);
		} else {
			size.w = ch_uinfo->dst_size.w;
			size.h = ch_uinfo->dst_size.h;
			channel->cap_status = NONE_CAP_SUPERZOOM;
			superzoom_flag = 0;
			pr_debug("dcam id %d, sw %d, no superzoom path dst w %d, h %d, ch_uinfo src w %d, h %d , dst_size %d, %d\n",
				module->idx, isp_ctx_id, size.w, size.h, ch_uinfo->dst_size.w, ch_uinfo->dst_size.h,
				ch_uinfo->dst_size.w, ch_uinfo->dst_size.h);
		}
		ret = isp_ops->cfg_path(module->isp_dev_handle,
				ISP_PATH_CFG_PATH_DST,
				isp_ctx_id, isp_path_id, &size);
		if (ret != 0)
			goto exit;

		ret = isp_ops->cfg_path(module->isp_dev_handle,
				ISP_PATH_CFG_CTX_SUPERZOOM,
				isp_ctx_id, isp_path_id, &superzoom_flag);
		if (ret != 0)
			goto exit;
	}
	path_trim = channel->trim_isp;

cfg_path:
	pr_info("cfg isp ctx sw %d path %d size, path trim %d %d %d %d\n",
		isp_ctx_id, isp_path_id, path_trim.start_x, path_trim.start_y, path_trim.size_x, path_trim.size_y);
	ret = isp_ops->cfg_path(module->isp_dev_handle,
				ISP_PATH_CFG_PATH_SIZE,
				isp_ctx_id, isp_path_id,  &path_trim);
	if (ret != 0)
			goto exit;
	if (channel->ch_id == CAM_CH_CAP && is_zoom) {
		channel = &module->channel[CAM_CH_CAP_THM];
		if (channel->enable) {
			isp_path_id = (channel->isp_path_id & ISP_PATHID_MASK);
			goto cfg_path;
		}
	}
	pr_info("update channel size done for CAP\n");

exit:
	return ret;
}

/* set capture channel size for isp fetch and crop, scaler
 * lowlux: 1: size / 2, 0: full size
 */
static int config_4in1_channel_size(struct camera_module *module,
				uint32_t lowlux_flag)
{
	struct channel_context *ch;
	struct channel_context ch_tmp;
	struct camera_uchannel *p;

	ch  = &module->channel[CAM_CH_CAP];
	/* backup */
	memcpy(&ch_tmp, ch, sizeof(struct channel_context));
	p = &ch_tmp.ch_uinfo;
	if (lowlux_flag) {
		/* bin-sum image, size should /2 */
		p->src_size.w /= 2;
		p->src_size.h /= 2;
		if ((p->src_size.w & 0x1) || (p->src_size.h & 0x1))
			pr_warn("Some problem with sensor size in lowlux\n");
		p->src_crop.x /= 2;
		p->src_crop.y /= 2;
		p->src_crop.w /= 2;
		p->src_crop.h /= 2;
		/* check zoom, low lux not support zoom now 190306 */
		if (p->src_crop.w != p->src_size.w ||
			p->src_crop.h != p->src_size.h) {
			pr_warn("lowlux capture not support zoom now\n");
			p->src_crop.x = 0;
			p->src_crop.y = 0;
			p->src_crop.w = p->src_size.w;
			p->src_crop.h = p->src_size.h;
		}
		p->src_crop.x = ALIGN(p->src_crop.x, 2);
		p->src_crop.y = ALIGN(p->src_crop.y, 2);
		p->src_crop.w = ALIGN(p->src_crop.w, 2);
		p->src_crop.h = ALIGN(p->src_crop.h, 2);
	}
	pr_info("src[%d %d], crop[%d %d %d %d] dst[%d %d]\n",
		p->src_size.w, p->src_size.h,
		p->src_crop.x, p->src_crop.y, p->src_crop.w, p->src_crop.h,
		p->dst_size.w, p->dst_size.h);
	ch_tmp.trim_dcam.start_x = p->src_crop.x;
	ch_tmp.trim_dcam.start_y = p->src_crop.y;
	ch_tmp.trim_dcam.size_x = p->src_crop.w;
	ch_tmp.trim_dcam.size_y = p->src_crop.h;
	ch_tmp.swap_size.w = p->src_size.w;
	ch_tmp.swap_size.h = p->src_size.h;
	get_diff_trim(&ch_tmp.ch_uinfo.src_crop,
		(1 << RATIO_SHIFT), &ch_tmp.trim_dcam, &ch_tmp.trim_isp);
	pr_info("trim_isp[%d %d %d %d]\n", ch_tmp.trim_isp.start_x,
		ch_tmp.trim_isp.start_y, ch_tmp.trim_isp.size_x,
		ch_tmp.trim_isp.size_y);
	config_channel_size(module, &ch_tmp);

	return 0;
}

static int get_slice_num_info(struct sprd_img_size *src,
				struct sprd_img_size *dst)
{
	uint32_t slice_num, slice_w, slice_w_out;
	uint32_t slice_max_w, max_w;
	uint32_t linebuf_len;
	uint32_t input_w = src->w;
	uint32_t output_w = dst->w;

	/* based input */
	linebuf_len = g_camctrl.isp_linebuf_len;
	max_w = input_w;
	slice_num = 1;
	slice_max_w = linebuf_len - ISP_SLICE_OVERLAP_W_MAX;
	if (max_w <= linebuf_len) {
		slice_w = max_w;
	} else {
		do {
			slice_num++;
			slice_w = (max_w + slice_num - 1) / slice_num;
		} while (slice_w >= slice_max_w);
	}
	pr_debug("input_w %d, slice_num %d, slice_w %d\n",
		max_w, slice_num, slice_w);

	/* based output */
	max_w = output_w;
	slice_num = 1;
	slice_max_w = linebuf_len;
	if (max_w > 0) {
		if (max_w > linebuf_len) {
			do {
				slice_num++;
				slice_w_out = (max_w + slice_num - 1) / slice_num;
			} while (slice_w_out >= slice_max_w);
		}
		/* set to equivalent input size, because slice size based on input. */
		slice_w_out = (input_w + slice_num - 1) / slice_num;
	} else
		slice_w_out = slice_w;
	pr_debug("max output w %d, slice_num %d, out limited slice_w %d\n",
		max_w, slice_num, slice_w_out);

	slice_w = MIN(slice_w, slice_w_out);
	slice_w = ALIGN(slice_w, 2);
	slice_num = (input_w + slice_w - 1) / slice_w;
	if (dst->h > ISP_SLCIE_HEIGHT_MAX)
		slice_num *= 2;
	return slice_num;
}

static int zoom_proc(void *param)
{
	int update_pv = 0, update_c = 0;
	int update_always = 0;
	struct camera_module *module;
	struct channel_context *ch_prev, *ch_vid, *ch_cap;
	struct camera_frame *pre_zoom_coeff = NULL;
	struct camera_frame *vid_zoom_coeff = NULL;
	struct camera_frame *cap_zoom_coeff = NULL;
	struct sprd_img_rect *crop;

	module = (struct camera_module *)param;
	ch_prev = &module->channel[CAM_CH_PRE];
	ch_cap = &module->channel[CAM_CH_CAP];
	ch_vid = &module->channel[CAM_CH_VID];
next:
	pre_zoom_coeff = vid_zoom_coeff = cap_zoom_coeff = NULL;
	update_pv = update_c = update_always = 0;
	/* Get node from the preview/video/cap coef queue if exist */
	if (ch_prev->enable)
		pre_zoom_coeff = camera_dequeue(&ch_prev->zoom_coeff_queue);
	if (pre_zoom_coeff) {
		crop = (struct sprd_img_rect *)pre_zoom_coeff->priv_data;
		ch_prev->ch_uinfo.src_crop = *crop;
		kfree(crop);
		put_empty_frame(pre_zoom_coeff);
		update_pv |= 1;
	}

	if (ch_vid->enable)
		vid_zoom_coeff = camera_dequeue(&ch_vid->zoom_coeff_queue);
	if (vid_zoom_coeff) {
		crop = (struct sprd_img_rect *)vid_zoom_coeff->priv_data;
		ch_vid->ch_uinfo.src_crop = *crop;
		kfree(crop);
		put_empty_frame(vid_zoom_coeff);
		update_pv |= 1;
	}

	if (ch_cap->enable)
		cap_zoom_coeff = camera_dequeue(&ch_cap->zoom_coeff_queue);
	if (cap_zoom_coeff) {
		crop = (struct sprd_img_rect *)cap_zoom_coeff->priv_data;
		ch_cap->ch_uinfo.src_crop = *crop;
		kfree(crop);
		put_empty_frame(cap_zoom_coeff);
		update_c |= 1;
	}

	if (update_pv || update_c) {
		if (ch_cap->enable && (ch_cap->mode_ltm == MODE_LTM_CAP))
			update_always = 1;

		if (module->zoom_solution == ZOOM_DEFAULT)
			cal_channel_size_bininig(module, 1);
		else if (module->zoom_solution == ZOOM_BINNING2 ||
			module->zoom_solution == ZOOM_BINNING4)
			cal_channel_size_bininig(module, 0);
		else
			cal_channel_size_rds(module);

		if (ch_cap->enable && (update_c || update_always))
			config_channel_size(module, ch_cap);
		if (ch_prev->enable && (update_pv || update_always))
			config_channel_size(module, ch_prev);
		goto next;
	}
	return 0;
}

static int capture_proc(void *param)
{
	int ret = 0;
	uint32_t cnt_3dnr= 0;
	struct camera_module *module;
	struct camera_frame *pframe;
	struct channel_context *channel;

	module = (struct camera_module *)param;
	channel = &module->channel[CAM_CH_CAP];
	pframe = camera_dequeue(&channel->share_buf_queue);
	if (!pframe)
		return 0;

	ret = -1;
	if (module->cap_status != CAM_CAPTURE_STOP) {
		pr_info("enter\n");
		if (channel->cap_status == NONE_CAP_SUPERZOOM
			|| module->cap_status == CAM_CAPTURE_RAWPROC) {
			/*Not to do superzoom capture*/
			pr_info("capture frame cam id %d, fid[%d],  frame w %d, h %d\n",
				module->idx, pframe->fid,
				pframe->width, pframe->height);
			ret = isp_ops->proc_frame(module->isp_dev_handle, pframe,
						channel->isp_path_id >> ISP_CTXID_OFFSET);
		} else {
			/*superzoom capture*/
			if (channel->uinfo_3dnr) {
				/*3DNR capture*/
				ret = isp_ops->get_3dnr_cnt(module->isp_dev_handle,
						channel->isp_path_id >> ISP_CTXID_OFFSET, &cnt_3dnr);
				if (ret) {
					pr_err("fail to superzoom get 3dnr cnt\n");
					goto exit;
				}

				if (cnt_3dnr % 5 != 4) {
					/*3dnr 0~3 frame*/
					pr_info("superzoom 3DNR capture frame fid[%d],  frame w %d, h %d, 3dr cnt %d\n",
						pframe->fid, pframe->width, pframe->height, cnt_3dnr);
					ret = isp_ops->proc_frame(module->isp_dev_handle, pframe,
								channel->isp_path_id >> ISP_CTXID_OFFSET);
					goto exit;
				}
			}

			/*NONE 3DNR or 3DNR 4frame capture , need to wait*/
			ret = wait_for_completion_interruptible_timeout(
					&channel->superzoom_frm, msecs_to_jiffies(2000));
			if (ret == ERESTARTSYS) {
				pr_err("fail to wait as interrupted\n");
				ret = -EFAULT;
				goto exit;
			} else if (ret == 0) {
				pr_err("fail to wait timeout.\n");
				ret = -EFAULT;
				goto exit;
			}

			pr_info("superzoom capture frame fid[%d],  frame w %d, h %d, 3dnr %d, cnt %d\n",
				pframe->fid, pframe->width, pframe->height, channel->uinfo_3dnr, cnt_3dnr);
			ret = isp_ops->proc_frame(module->isp_dev_handle, pframe,
				channel->isp_path_id >> ISP_CTXID_OFFSET);
		}
	}
exit:
	if (ret) {
		pr_info("capture stop or isp queue overflow\n");
		if (module->cam_uinfo.dcam_slice_mode && pframe->dcam_idx == DCAM_ID_1) {
			ret = dcam_ops->cfg_path(
				module->aux_dcam_dev,
				DCAM_PATH_CFG_OUTPUT_BUF,
				channel->aux_dcam_path_id, pframe);
		}
		else
			ret = dcam_ops->cfg_path(
				module->dcam_dev_handle,
				DCAM_PATH_CFG_OUTPUT_BUF,
				channel->dcam_path_id, pframe);

		/* Bug 1103913. In Race condition when We have already received stop capture &
		  * stream_off request & then capture thread gets chance to execute. In that case
		  * dcam_ops->cfg_path will fail & return non-Zero value. This will  cause memory leak.
		  * So we need to free pframe buffer explicitely.
		  */
		if (ret)
			put_k_frame((void*)pframe);
	}
	return 0;
}

#define CAMERA_DUMP_PATH "/data/ylog/"
/* will create thread in user to read raw buffer*/
#define BYTE_PER_ONCE 4096
static void write_image_to_file(uint8_t *buffer,
	ssize_t size, const char *file)
{
	ssize_t result = 0, total = 0, writ = 0;
	struct file *wfp;

	wfp = filp_open(file, O_CREAT|O_RDWR, 0666);
	if (IS_ERR_OR_NULL(wfp)) {
		pr_err("fail to open file %s\n", file);
		return;
	}
	pr_debug("write image buf=%p, size=%d\n", buffer, (uint32_t)size);
	do {
		writ = (BYTE_PER_ONCE < size) ? BYTE_PER_ONCE : size;
		result = kernel_write(wfp, buffer, writ, &wfp->f_pos);
		pr_debug("write result: %d, size: %d, pos: %d\n",
		(uint32_t)result,  (uint32_t)size, (uint32_t)wfp->f_pos);

		if (result > 0) {
			size -= result;
			buffer += result;
		}
		total += result;
	} while ((result > 0) && (size > 0));
	filp_close(wfp, NULL);
	pr_debug("write image done, total=%d\n", (uint32_t)total);
}

static int dump_one_frame(struct camera_module *module,
			  struct camera_frame *pframe)
{
	ssize_t size = 0;
	struct channel_context *channel;
	enum cam_ch_id ch_id;
	uint8_t file_name[256] = { '\0' };
	uint8_t tmp_str[20] = { '\0' };
	uint32_t is_loose = 0;
	uint32_t width = 0;

	ch_id = pframe->channel_id;
	channel = &module->channel[ch_id];

	strcat(file_name, CAMERA_DUMP_PATH);
	if (ch_id == CAM_CH_PRE)
		strcat(file_name, "prevraw_");
	else
		strcat(file_name, "capraw_");

	sprintf(tmp_str, "%d.", (uint32_t)module->cur_dump_ts.tv_sec);
	strcat(file_name, tmp_str);
	sprintf(tmp_str, "%06d", (uint32_t)(module->cur_dump_ts.tv_nsec / NSEC_PER_USEC));
	strcat(file_name, tmp_str);

	if (!pframe->sw_slice_num) {
		sprintf(tmp_str, "_w%d", pframe->width);
		strcat(file_name, tmp_str);
		sprintf(tmp_str, "_h%d", pframe->height);
		strcat(file_name, tmp_str);
		width = pframe->width;
	} else {
		sprintf(tmp_str, "_no%d", pframe->sw_slice_no);
		strcat(file_name, tmp_str);
		sprintf(tmp_str, "_w%d", pframe->slice_trim.size_x);
		strcat(file_name, tmp_str);
		sprintf(tmp_str, "_h%d", pframe->slice_trim.size_y);
		strcat(file_name, tmp_str);
		width = pframe->slice_trim.size_x;
	}

	sprintf(tmp_str, "_No%d", pframe->fid);
	strcat(file_name, tmp_str);

	is_loose = module->cam_uinfo.sensor_if.if_spec.mipi.is_loose;
	if (pframe->is_compressed) {
		struct compressed_addr addr;

		dcam_if_cal_compressed_addr(pframe->width, pframe->height,
					    pframe->buf.iova[0], &addr,
					    pframe->compress_4bit_bypass);
		sprintf(tmp_str, "_tile%08lx",
			addr.addr1 - pframe->buf.iova[0]);
		strcat(file_name, tmp_str);
		sprintf(tmp_str, "_low2tile%08lx",
			addr.addr2 - addr.addr1);
		strcat(file_name, tmp_str);
		size = dcam_if_cal_compressed_size(pframe->width,
					pframe->height, pframe->compress_4bit_bypass);
	} else {
		size = cal_sprd_raw_pitch(width, is_loose) * pframe->height;
	}
	if(is_loose == CAM_RAW_HALF14 || is_loose == CAM_RAW_HALF10)
		strcat(file_name, ".raw");
	else
		strcat(file_name, ".mipi_raw");

	if (cambuf_kmap(&pframe->buf)) {
		pr_err("fail to kmap dump buf\n");
		return -EFAULT;
	}
	write_image_to_file((char *)pframe->buf.addr_k[0], size, file_name);
	cambuf_kunmap(&pframe->buf);
	pr_debug("dump for ch %d, size %d, kaddr %p, file %s\n", ch_id,
		(int)size, (void *)pframe->buf.addr_k[0], file_name);

	return 0;
}

static inline int should_dump(int mode, int path)
{
	return (mode == DUMP_PATH_BOTH)
		|| (mode == DUMP_PATH_BIN && path == DCAM_PATH_BIN)
		|| (mode == DUMP_PATH_FULL && path == DCAM_PATH_FULL);
}

static int dumpraw_proc(void *param)
{
	uint32_t idx, cnt = 0;
	struct camera_module *module;
	struct channel_context *channel;
	struct camera_frame *pframe = NULL;
	struct cam_dbg_dump *dbg = &g_dbg_dump;

	pr_info("enter. %p\n", param);
	module = (struct camera_module *)param;
	idx = module->dcam_idx;
	if (idx > DCAM_ID_1 || !module->dcam_dev_handle)
		return 0;

	mutex_lock(&dbg->dump_lock);
	dbg->dump_ongoing |= (1 << idx);
	module->dump_count = dbg->dump_count;
	init_completion(&module->dump_com);
	mutex_unlock(&dbg->dump_lock);

	pr_info("start dump count: %d\n", module->dump_count);
	while (module->dump_count) {
		module->in_dump = 1;
		ktime_get_ts(&module->cur_dump_ts);
		if (wait_for_completion_interruptible(
			&module->dump_com) == 0) {
			if ((atomic_read(&module->state) != CAM_RUNNING) ||
				(module->dump_count == 0)) {
				pr_info("dump raw proc exit, %d %u\n",
					atomic_read(&module->state),
					module->dump_count);
				break;
			}
			pframe = camera_dequeue(&module->dump_queue);
			if (!pframe)
				continue;

			channel = &module->channel[pframe->channel_id];
			if (should_dump(dbg->dump_en, channel->dcam_path_id)) {
				dump_one_frame(module, pframe);
				module->dump_count--;
				cnt++;
			}
			/* return it to dcam output queue */
			if (module->cam_uinfo.is_4in1 &&
				channel->aux_dcam_path_id == DCAM_PATH_BIN &&
				pframe->buf.type == CAM_BUF_KERNEL)
				dcam_ops->cfg_path(module->aux_dcam_dev,
					   DCAM_PATH_CFG_OUTPUT_BUF,
					   channel->aux_dcam_path_id, pframe);
			else
				dcam_ops->cfg_path(module->dcam_dev_handle,
					   DCAM_PATH_CFG_OUTPUT_BUF,
					   channel->dcam_path_id, pframe);

		} else {
			pr_info("dump raw proc exit.");
			break;
		}
	}
	module->dump_count = 0;
	module->in_dump = 0;
	pr_info("end dump, real cnt %d\n", cnt);

	mutex_lock(&dbg->dump_lock);
	dbg->dump_count = 0;
	dbg->dump_ongoing &= ~(1 << idx);
	mutex_unlock(&dbg->dump_lock);
	return 0;
}

static int init_bigsize_aux(struct camera_module *module,
			struct channel_context *channel)
{
	int ret = 0;
	uint32_t dcam_idx = DCAM_ID_1;
	uint32_t dcam_path_id;
	void *dcam = NULL;
	struct camera_group *grp = module->grp;
	struct dcam_path_cfg_param ch_desc;
	struct dcam_pipe_dev *dev = NULL;

	dcam = module->aux_dcam_dev;
	if (dcam == NULL) {
		dcam = dcam_if_get_dev(dcam_idx, grp->hw_info);
		if (IS_ERR_OR_NULL(dcam)) {
			pr_err("fail to get dcam%d\n", dcam_idx);
			return -EFAULT;
		}
		module->aux_dcam_dev = dcam;
		module->aux_dcam_id = dcam_idx;
	}

	dev = (struct dcam_pipe_dev *)module->aux_dcam_dev;
	dev->dcam_slice_mode = module->cam_uinfo.dcam_slice_mode;
	dev->slice_num = module->cam_uinfo.slice_num;
	dev->slice_count = 0;

	ret = dcam_ops->open(module->aux_dcam_dev);
	if (ret < 0) {
		pr_err("fail to open aux dcam dev\n");
		ret = -EFAULT;
		goto exit_dev;
	}
	ret = dcam_ops->set_callback(module->aux_dcam_dev,
				dcam_callback, module);
	if (ret) {
		pr_err("fail to set aux dcam callback\n");
		ret = -EFAULT;
		goto exit_close;
	}
	/* todo: will update after dcam offline ctx done. */
	dcam_path_id = DCAM_PATH_BIN;
	ret = dcam_ops->get_path(module->aux_dcam_dev,
				dcam_path_id);
	if (ret < 0) {
		pr_err("fail to get dcam path %d\n", dcam_path_id);
		ret = -EFAULT;
		goto exit_close;
	} else {
		channel->aux_dcam_path_id = dcam_path_id;
		pr_info("get aux dcam path %d\n", dcam_path_id);
	}

	/* cfg dcam1 bin path */
	memset(&ch_desc, 0, sizeof(ch_desc));
	ch_desc.endian.y_endian = ENDIAN_LITTLE;
	ch_desc.is_loose = module->cam_uinfo.sensor_if.if_spec.mipi.is_loose;
	ch_desc.is_4in1 = module->cam_uinfo.is_4in1;

	ret = dcam_ops->cfg_path(module->aux_dcam_dev,
					DCAM_PATH_CFG_BASE,
					channel->aux_dcam_path_id,
					&ch_desc);

	pr_info("done\n");
	return ret;

exit_close:
	dcam_ops->close(module->aux_dcam_dev);
exit_dev:
	dcam_if_put_dev(module->aux_dcam_dev);
	module->aux_dcam_dev = NULL;
	return ret;
}

static int deinit_bigsize_aux(struct camera_module *module)
{
	int ret = 0;
	void *dev;

	pr_info("E\n");
	dev = module->aux_dcam_dev;
	ret = dcam_ops->ioctl(dev, DCAM_IOCTL_CFG_STOP, NULL);
	ret = dcam_ops->stop(dev);
	ret = dcam_ops->put_path(dev, DCAM_PATH_BIN);
	ret += dcam_ops->close(dev);
	ret += dcam_if_put_dev(dev);
	module->aux_dcam_dev = NULL;
	pr_info("Done, ret = %d\n", ret);

	return ret;
}

static int init_4in1_aux(struct camera_module *module,
			struct channel_context *channel)
{
	int ret = 0;
	uint32_t dcam_path_id;
	struct dcam_path_cfg_param ch_desc;

	/* todo: will update after dcam offline ctx done. */
	dcam_path_id = DCAM_PATH_BIN;
	ret = dcam_ops->get_path(module->dcam_dev_handle,
				dcam_path_id);
	if (ret < 0) {
		pr_err("fail to get dcam path %d\n", dcam_path_id);
		ret = -EFAULT;
		goto exit;
	} else {
		module->aux_dcam_dev = NULL;
		channel->aux_dcam_path_id = dcam_path_id;
		pr_info("get aux dcam path %d\n", dcam_path_id);
	}

	/* cfg dcam1 bin path */
	memset(&ch_desc, 0, sizeof(ch_desc));
	ch_desc.endian.y_endian = ENDIAN_LITTLE;
	ch_desc.input_size.w = channel->ch_uinfo.src_size.w;
	ch_desc.input_size.h = channel->ch_uinfo.src_size.h;
	/* dcam1 not trim, do it by isp */
	ch_desc.input_trim.size_x = channel->ch_uinfo.src_size.w;
	ch_desc.input_trim.size_y = channel->ch_uinfo.src_size.h;
	ch_desc.output_size.w = ch_desc.input_trim.size_x;
	ch_desc.output_size.h = ch_desc.input_trim.size_y;
	ch_desc.is_loose = module->cam_uinfo.sensor_if.if_spec.mipi.is_loose;
	ch_desc.is_4in1 = module->cam_uinfo.is_4in1;
	ret = dcam_ops->cfg_path(module->dcam_dev_handle,
					DCAM_PATH_CFG_BASE,
					channel->aux_dcam_path_id,
					&ch_desc);
	ret = dcam_ops->cfg_path(module->dcam_dev_handle,
					DCAM_PATH_CFG_SIZE,
					channel->aux_dcam_path_id,
					&ch_desc);
	/* 4in1 not choose 1 from 3 frames, TODO
	 * channel->frm_cnt = (uint32_t)(-3);
	 */
	pr_info("done\n");
exit:
	return ret;
}

static int deinit_4in1_aux(struct camera_module *module)
{
	int ret = 0;
	struct dcam_pipe_dev *dev = NULL;

	pr_info("E\n");
	dev = (struct dcam_pipe_dev *)module->dcam_dev_handle;
	ret = dcam_ops->put_path(dev, DCAM_PATH_BIN);
	pr_info("Done, ret = %d\n", ret);

	return ret;
}

/* 4in1_raw_capture
 * init second path for bin sum
 */
static int init_4in1_secondary_path(struct camera_module *module,
			struct channel_context *ch)
{
	int ret = 0;
	uint32_t second_path_id = DCAM_PATH_BIN;
	struct dcam_path_cfg_param ch_desc;

	/* now only raw capture can run to here */
	if (ch->ch_id != CAM_CH_RAW)
		return -EFAULT;

	ch->second_path_enable = 0;
	ret = dcam_ops->get_path(
		module->dcam_dev_handle, second_path_id);
	if (ret < 0) {
		pr_err("fail to get dcam path %d\n", second_path_id);
		return -EFAULT;
	}
	ch->second_path_id = second_path_id;

	/* todo: cfg param to user setting. */
	memset(&ch_desc, 0, sizeof(ch_desc));
	ch_desc.is_loose = module->cam_uinfo.sensor_if.if_spec.mipi.is_loose;
	ch_desc.is_4in1 = module->cam_uinfo.is_4in1;
	/*
	 * Configure slow motion for BIN path. HAL must set @is_high_fps
	 * and @high_fps_skip_num for both preview channel and video
	 * channel so BIN path can enable slow motion feature correctly.
	 */
	ch_desc.slowmotion_count = ch->ch_uinfo.high_fps_skip_num;
	ch_desc.endian.y_endian = ENDIAN_LITTLE;

	ch_desc.input_size.w = module->cam_uinfo.sn_size.w / 2;
	ch_desc.input_size.h = module->cam_uinfo.sn_size.h / 2;
	ch_desc.input_trim.start_x = 0;
	ch_desc.input_trim.start_y = 0;
	ch_desc.input_trim.size_x = ch_desc.input_size.w;
	ch_desc.input_trim.size_y = ch_desc.input_size.h;
	ch_desc.output_size.w = ch_desc.input_size.w;
	ch_desc.output_size.h = ch_desc.input_size.h;

	if (ch->ch_id == CAM_CH_RAW)
		ch_desc.is_raw = 1;
	ret = dcam_ops->cfg_path(module->dcam_dev_handle,
			DCAM_PATH_CFG_BASE,
			ch->second_path_id, &ch_desc);
	ret = dcam_ops->cfg_path(module->dcam_dev_handle,
			DCAM_PATH_CFG_SIZE,
			ch->second_path_id, &ch_desc);
	/* bypass bin path all sub block except 4in1 */

	ch->second_path_enable = 1;
	pr_info("done\n");

	return 0;
}

/* 4in1_raw_capture
 * deinit second path
 */
static void deinit_4in1_secondary_path(struct camera_module *module,
			struct channel_context *ch)
{
	/* now only raw capture can run to here */
	if (ch->ch_id != CAM_CH_RAW || (!ch->second_path_enable))
		return ;
	dcam_ops->put_path(module->dcam_dev_handle, ch->second_path_id);
	ch->second_path_enable = 0;
	pr_info("done\n");
}

static int init_channels_size(struct camera_module *module)
{
	uint32_t format = module->cam_uinfo.sensor_if.img_fmt;
	/* bypass RDS if sensor output binning size for image quality */
	module->zoom_solution = g_camctrl.dcam_zoom_mode;
	module->rds_limit = g_camctrl.dcam_rds_limit;

	/* force binning as smaller as possible for security */
	if (module->grp->camsec_cfg.camsec_mode != SEC_UNABLE)
		module->zoom_solution = ZOOM_BINNING4;

	if (format == DCAM_CAP_MODE_YUV)
		module->zoom_solution = ZOOM_DEFAULT;

	cal_channel_swapsize(module);

	pr_info("zoom_solution %d, limit %d %d\n",
		module->zoom_solution,
		module->rds_limit, module->binning_limit);

	return 0;
}

static int init_cam_channel(
			struct camera_module *module,
			struct channel_context *channel)
{
	int ret = 0;
	int isp_ctx_id = 0, isp_path_id = 0, dcam_path_id = 0;
	int slave_path_id = 0;
	int new_isp_ctx, new_isp_path, new_dcam_path;
	struct channel_context *channel_prev = NULL;
	struct channel_context *channel_cap = NULL;
	struct camera_uchannel *ch_uinfo;
	struct isp_path_base_desc path_desc;
	struct isp_init_param init_param;
	struct cam_hw_info *hw = NULL;
	uint32_t format = 0;

	hw = module->grp->hw_info;
	ch_uinfo = &channel->ch_uinfo;
	ch_uinfo->src_size.w = module->cam_uinfo.sn_rect.w;
	ch_uinfo->src_size.h = module->cam_uinfo.sn_rect.h;
	new_isp_ctx = 0;
	new_isp_path = 0;
	new_dcam_path = 0;
	memset(&init_param, 0, sizeof(struct isp_init_param));
	format = module->cam_uinfo.sensor_if.img_fmt;


	switch (channel->ch_id) {
	case CAM_CH_PRE:
		if (format == DCAM_CAP_MODE_YUV)
			dcam_path_id = DCAM_PATH_FULL;
		else
			dcam_path_id = DCAM_PATH_BIN;
		isp_path_id = ISP_SPATH_CP;
		new_isp_ctx = 1;
		new_isp_path = 1;
		new_dcam_path = 1;
		break;

	case CAM_CH_VID:
		/* only consider video/pre share same
		 * dcam path and isp ctx now.
		 */
		channel_prev = &module->channel[CAM_CH_PRE];
		if (channel_prev->enable) {
			channel->dcam_path_id = channel_prev->dcam_path_id;
			isp_ctx_id = (channel_prev->isp_path_id
				>> ISP_CTXID_OFFSET);
		} else {
			dcam_path_id = DCAM_PATH_BIN;
			new_dcam_path = 1;
			new_isp_ctx = 1;
			pr_info("vid channel enable without preview\n");
		}
		isp_path_id = ISP_SPATH_VID;
		new_isp_path = 1;
		break;

	case CAM_CH_CAP:
		dcam_path_id = DCAM_PATH_FULL;
		isp_path_id = ISP_SPATH_CP;
		new_isp_ctx = 1;
		new_isp_path = 1;
		new_dcam_path = 1;
		break;

	case CAM_CH_PRE_THM:
		channel_prev = &module->channel[CAM_CH_PRE];
		if (channel_prev->enable == 0) {
			pr_err("fail to get preview channel enable status\n");
			return -EINVAL;
		}
		channel->dcam_path_id = channel_prev->dcam_path_id;
		isp_ctx_id = (channel_prev->isp_path_id >> ISP_CTXID_OFFSET);
		isp_path_id = ISP_SPATH_FD;
		new_isp_path = 1;
		break;

	case CAM_CH_CAP_THM:
		channel_cap = &module->channel[CAM_CH_CAP];
		if (channel_cap->enable == 0) {
			pr_err("fail to get capture channel enable status\n");
			return -EINVAL;
		}
		channel->dcam_path_id = channel_cap->dcam_path_id;
		isp_ctx_id = (channel_cap->isp_path_id >> ISP_CTXID_OFFSET);
		isp_path_id = ISP_SPATH_FD;
		new_isp_path = 1;
		break;

	case CAM_CH_RAW:
		dcam_path_id = DCAM_PATH_FULL;
		new_dcam_path = 1;
		break;

	default:
		pr_err("fail to get channel id %d\n", channel->ch_id);
		return -EINVAL;
	}

	pr_info("ch %d, new: (%d %d %d)  path (%d %d %d)\n",
		channel->ch_id, new_isp_ctx, new_isp_path, new_dcam_path,
		isp_ctx_id, isp_path_id, dcam_path_id);

	if (new_dcam_path) {
		struct dcam_path_cfg_param ch_desc;

		ret = dcam_ops->get_path(
				module->dcam_dev_handle, dcam_path_id);
		if (ret < 0) {
			pr_err("fail to get dcam path %d\n", dcam_path_id);
			return -EFAULT;
		}
		channel->dcam_path_id = dcam_path_id;
		pr_debug("get dcam path : %d\n", channel->dcam_path_id);

		/* todo: cfg param to user setting. */
		memset(&ch_desc, 0, sizeof(ch_desc));
		if(dcam_path_id == 0 && module->cam_uinfo.is_4in1 == 1)
			ch_desc.is_loose = 0;
		else
			ch_desc.is_loose = module->cam_uinfo.sensor_if.if_spec.mipi.is_loose;
		ch_desc.is_4in1 = module->cam_uinfo.is_4in1;
		/*
		 * Configure slow motion for BIN path. HAL must set @is_high_fps
		 * and @high_fps_skip_num for both preview channel and video
		 * channel so BIN path can enable slow motion feature correctly.
		 */
		ch_desc.slowmotion_count = ch_uinfo->high_fps_skip_num;

		ch_desc.endian.y_endian = ENDIAN_LITTLE;
		ch_desc.bayer_pattern = module->cam_uinfo.sensor_if.img_ptn;
		ch_desc.input_trim.start_x = module->cam_uinfo.sn_rect.x;
		ch_desc.input_trim.start_y = module->cam_uinfo.sn_rect.y;
		ch_desc.input_trim.size_x = module->cam_uinfo.sn_rect.w;
		ch_desc.input_trim.size_y = module->cam_uinfo.sn_rect.h;
		/* auto_3dnr:hw enable, channel->uinfo_3dnr == 1: hw enable */
		ch_desc.enable_3dnr = (module->auto_3dnr | channel->uinfo_3dnr);
		if (channel->ch_id == CAM_CH_RAW)
			ch_desc.is_raw = 1;
		if ((channel->ch_id == CAM_CH_CAP) && module->cam_uinfo.is_4in1)
			ch_desc.is_raw = 1;
		if ((channel->ch_id == CAM_CH_CAP) && module->cam_uinfo.dcam_slice_mode)
			ch_desc.is_raw = 1;
		ret = dcam_ops->cfg_path(module->dcam_dev_handle,
				DCAM_PATH_CFG_BASE,
				channel->dcam_path_id, &ch_desc);
	}

	if (new_isp_ctx) {
		struct isp_ctx_base_desc ctx_desc;
		uint32_t format = module->cam_uinfo.sensor_if.img_fmt;

		memset(&ctx_desc, 0, sizeof(struct isp_ctx_base_desc));
		init_param.is_high_fps = ch_uinfo->is_high_fps;
		init_param.cam_id = module->idx;
		ret = isp_ops->get_context(module->isp_dev_handle, &init_param);
		if (ret < 0) {
			pr_err("fail to get isp context for cam%d ch %d\n",
					module->idx, channel->ch_id);
			goto exit;
		}
		isp_ctx_id = ret;
		isp_ops->set_callback(module->isp_dev_handle,
				isp_ctx_id, isp_callback, module);

		/* todo: cfg param to user setting. */
		if (format == DCAM_CAP_MODE_YUV)
			ctx_desc.in_fmt = ch_uinfo->dst_fmt;
		else
			ctx_desc.in_fmt = ch_uinfo->sn_fmt;
		ctx_desc.is_loose = module->cam_uinfo.sensor_if.if_spec.mipi.is_loose;
		ctx_desc.bayer_pattern = module->cam_uinfo.sensor_if.img_ptn;
		ctx_desc.mode_ltm = MODE_LTM_OFF;
		ctx_desc.mode_3dnr = MODE_3DNR_OFF;
		ctx_desc.enable_slowmotion = ch_uinfo->is_high_fps;
		ctx_desc.slowmotion_count = ch_uinfo->high_fps_skip_num;
		ctx_desc.slw_state = CAM_SLOWMOTION_OFF;
		ctx_desc.ch_id = channel->ch_id;

		/* 20190614: have some change for auto 3dnr, maybe some code
		 * will be refined laster. below show how to use now
		 * 1: ch->type_3dnr, flag for hw 3dnr(dcam) alloc buffer
		 * 2: module->auto_3dnr: 1: alloc buffer for prev,cap,
		 *    later will enable/disable by ch->uinfo_3dnr
		 * scene1: nightshot:module->auto_3dnr==0,prev_ch->type_3dnr==1
		 *         cap_ch->type_3dnr == 0,prev hw, cap sw
		 * scene2: auto_3dnr:module->auto_3dnr==1,ch->type_3dnr==x
		 *         dynamical enable/disable(before start_capture)
		 * scene3: off: module->auto_3dnr == 0, ch->type_3dnr == 0
		 */
		ctx_desc.mode_3dnr = MODE_3DNR_OFF;
		if (module->auto_3dnr) {
			if (channel->uinfo_3dnr) {
				if (channel->ch_id == CAM_CH_CAP)
					ctx_desc.mode_3dnr = MODE_3DNR_CAP;
				else
					ctx_desc.mode_3dnr = MODE_3DNR_PRE;
			}
			channel->type_3dnr = CAM_3DNR_HW;
		} else {
			channel->type_3dnr = CAM_3DNR_OFF;
			if (channel->uinfo_3dnr) {
				channel->type_3dnr = CAM_3DNR_HW;
				if (channel->ch_id == CAM_CH_CAP)
					ctx_desc.mode_3dnr = MODE_3DNR_CAP;
				else
					ctx_desc.mode_3dnr = MODE_3DNR_PRE;
			}
		}

		if (module->cam_uinfo.is_rgb_ltm) {
			channel->ltm_rgb = 1;
			ctx_desc.ltm_rgb = 1;
			if (channel->ch_id == CAM_CH_CAP) {
				channel->mode_ltm = MODE_LTM_CAP;
				ctx_desc.mode_ltm = MODE_LTM_CAP;
			} else if (channel->ch_id == CAM_CH_PRE) {
				channel->mode_ltm = MODE_LTM_PRE;
				ctx_desc.mode_ltm = MODE_LTM_PRE;
			}
		} else {
			channel->ltm_rgb = 0;
			ctx_desc.ltm_rgb = 0;
		}

		if (module->cam_uinfo.is_yuv_ltm) {
			channel->ltm_yuv = 1;
			ctx_desc.ltm_yuv = 1;
			if (channel->ch_id == CAM_CH_CAP) {
				channel->mode_ltm = MODE_LTM_CAP;
				ctx_desc.mode_ltm = MODE_LTM_CAP;
			} else if (channel->ch_id == CAM_CH_PRE) {
				channel->mode_ltm = MODE_LTM_PRE;
				ctx_desc.mode_ltm = MODE_LTM_PRE;
			}
		} else {
			channel->ltm_yuv = 0;
			ctx_desc.ltm_yuv = 0;
		}

		ret = isp_ops->cfg_path(module->isp_dev_handle,
				ISP_PATH_CFG_CTX_BASE, isp_ctx_id, 0, &ctx_desc);

		if (hw->ip_dcam[module->dcam_idx]->superzoom_support
			&& channel->ch_id == CAM_CH_CAP) {
			init_param.cam_id = module->idx;
			init_param.is_superzoom = 1;
			ret = isp_ops->get_context(module->isp_dev_handle, &init_param);
			if (ret != ISP_CONTEXT_SUPERZOOM) {
				pr_err("fail to get isp superzoom context cam%d ch %d\n",
					module->idx, channel->ch_id);
				goto exit;
			}

			isp_ops->set_callback(module->isp_dev_handle,
					ISP_CONTEXT_SUPERZOOM, isp_callback, module);
			ret = isp_ops->cfg_path(module->isp_dev_handle,
					ISP_PATH_CFG_CTX_BASE, ISP_CONTEXT_SUPERZOOM, 0, &ctx_desc);
		}
	}

	if (new_isp_path) {
		ret = isp_ops->get_path(
				module->isp_dev_handle, isp_ctx_id, isp_path_id);
		if (ret < 0) {
			pr_err("fail to get isp path %d from context %d\n",
				isp_path_id, isp_ctx_id);
			if (new_isp_ctx)
				isp_ops->put_context(module->isp_dev_handle, isp_ctx_id);
			goto exit;
		}
		channel->isp_path_id =
			(int32_t)((isp_ctx_id << ISP_CTXID_OFFSET) | isp_path_id);
		pr_debug("get isp path : 0x%x\n", channel->isp_path_id);

		memset(&path_desc, 0, sizeof(path_desc));
		if (channel->ch_uinfo.slave_img_en) {
			slave_path_id = ISP_SPATH_VID;
			path_desc.slave_type = ISP_PATH_MASTER;
			path_desc.slave_path_id = slave_path_id;
		}
		path_desc.out_fmt = ch_uinfo->dst_fmt;
		path_desc.endian.y_endian = ENDIAN_LITTLE;
		path_desc.endian.uv_endian = ENDIAN_LITTLE;
		path_desc.output_size.w = ch_uinfo->dst_size.w;
		path_desc.output_size.h = ch_uinfo->dst_size.h;
		path_desc.regular_mode = ch_uinfo->regular_desc.regular_mode;

		ret = isp_ops->cfg_path(module->isp_dev_handle,
					ISP_PATH_CFG_PATH_BASE,
					isp_ctx_id, isp_path_id, &path_desc);

		if (hw->ip_dcam[module->dcam_idx]->superzoom_support
			&& channel->ch_id == CAM_CH_CAP) {
			ret = isp_ops->get_path(
					module->isp_dev_handle, ISP_CONTEXT_SUPERZOOM, isp_path_id);
			if (ret < 0) {
				pr_err("fail to get isp path %d from superzoom\n", isp_path_id);
				if (new_isp_ctx)
					isp_ops->put_context(module->isp_dev_handle,
							ISP_CONTEXT_SUPERZOOM);
				goto exit;
			}

			ret = isp_ops->cfg_path(module->isp_dev_handle,
					ISP_PATH_CFG_PATH_BASE,
					ISP_CONTEXT_SUPERZOOM, isp_path_id, &path_desc);
		}
	}

	if (new_isp_path && channel->ch_uinfo.slave_img_en) {
		ret = isp_ops->get_path(module->isp_dev_handle,
				isp_ctx_id, slave_path_id);
		if (ret < 0) {
			pr_err("fail to get isp path %d from context %d\n",
				slave_path_id, isp_ctx_id);
			isp_ops->put_path(
				module->isp_dev_handle, isp_ctx_id, isp_path_id);
			if (new_isp_ctx)
				isp_ops->put_context(module->isp_dev_handle, isp_ctx_id);
			goto exit;
		}
		channel->slave_isp_path_id =
			(int32_t)((isp_ctx_id << ISP_CTXID_OFFSET) | slave_path_id);
		path_desc.slave_type = ISP_PATH_SLAVE;
		path_desc.out_fmt = ch_uinfo->slave_img_fmt;
		path_desc.endian.y_endian = ENDIAN_LITTLE;
		path_desc.endian.uv_endian = ENDIAN_LITTLE;
		path_desc.output_size.w = ch_uinfo->slave_img_size.w;
		path_desc.output_size.h = ch_uinfo->slave_img_size.h;
		ret = isp_ops->cfg_path(module->isp_dev_handle,
					ISP_PATH_CFG_PATH_BASE,
					isp_ctx_id, slave_path_id, &path_desc);
	}

	/* 4in1 setting */
	if (channel->ch_id == CAM_CH_CAP && module->cam_uinfo.is_4in1) {
		ret = init_4in1_aux(module, channel);
		if (ret < 0) {
			pr_err("fail to init dcam for 4in1, ret = %d\n", ret);
			goto exit;
		}
	}
	if (channel->ch_id == CAM_CH_RAW && module->cam_uinfo.is_4in1) {
		ret = init_4in1_secondary_path(module, channel);
		if (ret)
			pr_err("fail to init 4in1 raw capture for bin sum\n");
	}
	/* bigsize setting */
 	if (channel->ch_id == CAM_CH_CAP && module->cam_uinfo.dcam_slice_mode) {
		ret = init_bigsize_aux(module, channel);
		if (ret < 0) {
			pr_err("fail to init dcam for 4in1, ret = %d\n", ret);
			goto exit;
		}
	}

exit:
	pr_info("path_id:dcam = %d, aux dcam = %d, isp = 0x%x\n",
		channel->dcam_path_id, channel->aux_dcam_path_id,
		channel->isp_path_id);
	pr_debug("ch %d done. ret = %d\n", channel->ch_id, ret);
	return ret;
}

static void cam_timer_callback(unsigned long data)
{
	struct camera_module *module = (struct camera_module *)data;
	struct camera_frame *frame;
	int ret = 0;

	if (!module || atomic_read(&module->state) != CAM_RUNNING) {
		pr_err("fail to get valid module %p or error state\n", module);
		return;
	}

	if (atomic_read(&module->timeout_flag) == 1) {
		pr_err("fail to get frame data, CAM%d timeout.\n", module->idx);
		frame = get_empty_frame();
		if (module->cap_status == CAM_CAPTURE_RAWPROC) {
			module->cap_status = CAM_CAPTURE_RAWPROC_DONE;
			frame->evt = IMG_TX_DONE;
			frame->irq_type = CAMERA_IRQ_DONE;
			frame->irq_property = IRQ_RAW_PROC_TIMEOUT;
		} else {
			frame->evt = IMG_TIMEOUT;
			frame->irq_type = CAMERA_IRQ_IMG;
			frame->irq_property = IRQ_MAX_DONE;
		}
		ret = camera_enqueue(&module->frm_queue, frame);
		complete(&module->frm_com);
		if (ret)
			pr_err("fail to enqueue.\n");
	}
}

static void sprd_init_timer(struct timer_list *cam_timer,
			unsigned long data)
{
	setup_timer(cam_timer, cam_timer_callback, data);
}

static int sprd_start_timer(struct timer_list *cam_timer,
			uint32_t time_val)
{
	int ret = 0;

	pr_debug("starting timer %ld\n", jiffies);
	ret = mod_timer(cam_timer, jiffies + msecs_to_jiffies(time_val));
	if (ret)
		pr_err("fail to start in mod_timer %d\n", ret);

	return ret;
}

static int sprd_stop_timer(struct timer_list *cam_timer)
{
	pr_debug("stop timer\n");
	del_timer_sync(cam_timer);
	return 0;
}

static int camera_thread_loop(void *arg)
{
	int idx;
	struct camera_module *module;
	struct cam_thread_info *thrd;

	if (!arg) {
		pr_err("fail to get valid input ptr\n");
		return -1;
	}

	thrd = (struct cam_thread_info *)arg;
	module = (struct camera_module *)thrd->ctx_handle;
	idx = module->idx;
	pr_info("%s loop starts\n", thrd->thread_name);
	while (1) {
		if (wait_for_completion_interruptible(
			&thrd->thread_com) == 0) {
			if (atomic_cmpxchg(&thrd->thread_stop, 1, 0) == 1) {
				pr_info("thread %s should stop.\n", thrd->thread_name);
				break;
			}
			pr_info("thread %s trigger\n", thrd->thread_name);
			thrd->proc_func(module);
		} else {
			pr_debug("thread %s exit!", thrd->thread_name);
			break;
		}
	}
	pr_info("%s thread stop.\n", thrd->thread_name);
	complete(&thrd->thread_stop_com);

	return 0;
}

static int camera_create_thread(struct camera_module *module,
	struct cam_thread_info *thrd, void *func)
{
	thrd->ctx_handle = module;
	thrd->proc_func = func;
	atomic_set(&thrd->thread_stop, 0);
	init_completion(&thrd->thread_com);
	init_completion(&thrd->thread_stop_com);
	thrd->thread_task = kthread_run(camera_thread_loop,
				thrd, "%s", thrd->thread_name);
	if (IS_ERR_OR_NULL(thrd->thread_task)) {
		pr_err("fail to start thread %s\n", thrd->thread_name);
		thrd->thread_task = NULL;
		return -EFAULT;
	}
	return 0;
}

static void camera_stop_thread(struct cam_thread_info *thrd)
{
	unsigned long timeleft = 0;

	if (thrd->thread_task) {
		atomic_set(&thrd->thread_stop, 1);
		complete(&thrd->thread_com);
		timeleft = wait_for_completion_timeout(&thrd->thread_stop_com,
				msecs_to_jiffies(THREAD_STOP_TIMEOUT));
		if (timeleft == 0)
			pr_err("fail to stop %s thread, timeout\n", thrd->thread_name);
		thrd->thread_task = NULL;
	}
}

static int camera_module_init(struct camera_module *module)
{
	int ret = 0;
	int ch;
	struct channel_context *channel;
	struct cam_thread_info *thrd;

	pr_info("sprd_img: camera dev %d init start!\n", module->idx);

	atomic_set(&module->state, CAM_INIT);
	mutex_init(&module->lock);
	init_completion(&module->frm_com);
	init_completion(&module->streamoff_com);

	module->cap_status = CAM_CAPTURE_STOP;
	module->dcam_cap_status = DCAM_CAPTURE_STOP;

	for (ch = 0; ch < CAM_CH_MAX; ch++) {
		channel = &module->channel[ch];
		channel->ch_id = ch;
		channel->dcam_path_id = -1;
		channel->isp_path_id = -1;
		init_completion(&channel->alloc_com);
	}

	/* create capture thread */
	thrd = &module->cap_thrd;
	sprintf(thrd->thread_name, "cam%d_capture", module->idx);
	ret = camera_create_thread(module, thrd, capture_proc);
	if (ret)
		goto exit;

	/* create zoom thread */
	thrd = &module->zoom_thrd;
	sprintf(thrd->thread_name, "cam%d_zoom", module->idx);
	ret = camera_create_thread(module, thrd, zoom_proc);
	if (ret)
		goto exit;

	if (g_dbg_dump.dump_en) {
		/* create dump thread */
		thrd = &module->dump_thrd;
		sprintf(thrd->thread_name, "cam%d_dumpraw", module->idx);
		ret = camera_create_thread(module, thrd, dumpraw_proc);
		if (ret)
			goto exit;
	}

	module->flash_core_handle = get_cam_flash_handle(module->idx);

	sprd_init_timer(&module->cam_timer, (unsigned long)module);
	module->attach_sensor_id = SPRD_SENSOR_ID_MAX + 1;
	module->is_smooth_zoom = 1; /* temp for smooth zoom */

	pr_info("module[%d] init OK %p!\n", module->idx, module);
	return 0;
exit:
	camera_stop_thread(&module->cap_thrd);
	camera_stop_thread(&module->zoom_thrd);
	camera_stop_thread(&module->dump_thrd);
	return ret;
}

static int camera_module_deinit(struct camera_module *module)
{
	put_cam_flash_handle(module->flash_core_handle);
	camera_stop_thread(&module->cap_thrd);
	camera_stop_thread(&module->zoom_thrd);
	camera_stop_thread(&module->dump_thrd);
	mutex_destroy(&module->lock);
	return 0;
}

/*---------------  Misc interface start --------------- */

static int img_ioctl_get_time(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	struct sprd_img_time utime;
	struct timespec ts;

	ktime_get_ts(&ts);
	utime.sec = ts.tv_sec;
	utime.usec = ts.tv_nsec / NSEC_PER_USEC;
	pr_debug("get_time %d.%06d\n", utime.sec, utime.usec);

	ret = copy_to_user((void __user *)arg, &utime,
				sizeof(struct sprd_img_time));
	if (unlikely(ret)) {
		pr_err("fail to put user info, ret %d\n", ret);
		return -EFAULT;
	}

	return 0;
}

static int img_ioctl_set_flash(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	struct sprd_img_set_flash set_param;

	ret = copy_from_user((void *)&set_param,
				(void __user *)arg,
				sizeof(struct sprd_img_set_flash));
	if (ret) {
		pr_err("fail to get user info\n");
		ret = -EFAULT;
		goto exit;
	}

	module->flash_info.led0_ctrl = set_param.led0_ctrl;
	module->flash_info.led1_ctrl = set_param.led1_ctrl;
	module->flash_info.led0_status = set_param.led0_status;
	module->flash_info.led1_status = set_param.led1_status;
	pr_info("led0_ctrl=%d,led1_ctrl=%d\n",set_param.led0_ctrl,set_param.led1_ctrl);

	ret = flash_ops->set_flash(module->flash_core_handle,
		(void *)&set_param);
exit:
	return ret;
}

static int img_ioctl_cfg_flash(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	struct sprd_flash_cfg_param cfg_parm;

	ret = copy_from_user((void *) &cfg_parm,
				(void __user *)arg,
				sizeof(struct sprd_flash_cfg_param));
	if (ret) {
		pr_err("fail to get user info\n");
		ret = -EFAULT;
		goto exit;
	}
	ret = flash_ops->cfg_flash(module->flash_core_handle,
		(void *)&cfg_parm);

exit:
	return ret;
}

static int img_ioctl_get_flash(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	struct sprd_flash_capacity flash_info = {0};

	ret = flash_ops->get_flash(module->flash_core_handle,
		(void *)&flash_info);

	ret = copy_to_user((void __user *)arg, (void *)&flash_info,
					sizeof(struct sprd_flash_capacity));

	return ret;
}

static int img_ioctl_get_iommu_status(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	unsigned int iommu_enable;
	struct device	*dcam_dev;

	dcam_dev = &module->grp->pdev->dev;
	if (get_iommu_status(CAM_IOMMUDEV_DCAM) == 0)
		iommu_enable = 1;
	else
		iommu_enable = 0;
	module->iommu_enable = iommu_enable;

	ret = copy_to_user((void __user *)arg, &iommu_enable,
				sizeof(unsigned char));

	if (unlikely(ret)) {
		pr_err("fail to copy to user, ret %d\n", ret);
		ret = -EFAULT;
		goto exit;
	}
	pr_info("iommu_enable:%d\n", iommu_enable);
exit:
	return ret;
}


static int img_ioctl_set_statis_buf(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	struct channel_context *ch = NULL;
	struct isp_statis_buf_input statis_buf;

	ret = copy_from_user((void *)&statis_buf,
			(void *)arg, sizeof(struct isp_statis_buf_input));
	if (unlikely(ret)) {
		pr_err("fail to copy from user, ret %d\n", ret);
		ret = -EFAULT;
		goto exit;
	}

	if ((statis_buf.type == STATIS_INIT) &&
		(atomic_read(&module->state) != CAM_IDLE) &&
		(atomic_read(&module->state) != CAM_CFG_CH)) {
		pr_err("fail to get init statis buf state: %d\n",
			atomic_read(&module->state));
		ret = -EFAULT;
		goto exit;
	}

	if ((statis_buf.type != STATIS_INIT) &&
		(atomic_read(&module->state) != CAM_RUNNING)) {
		pr_warn("should not configure statis buf for state %d\n",
			atomic_read(&module->state));
		goto exit;
	}

	if (statis_buf.type < STATIS_HIST2) {
		ret = dcam_ops->ioctl(module->dcam_dev_handle,
					DCAM_IOCTL_CFG_STATIS_BUF,
					&statis_buf);
	}

	if ((statis_buf.type == STATIS_INIT) ||
		(statis_buf.type >= STATIS_HIST2)) {
		ch = &module->channel[CAM_CH_PRE];
		if (ch->enable) {
			ret = isp_ops->ioctl(module->isp_dev_handle,
					ch->isp_path_id >> ISP_CTXID_OFFSET,
					ISP_IOCTL_CFG_STATIS_BUF,
					&statis_buf);
		}
	}
exit:
	return ret;
}

static int img_ioctl_cfg_param(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	struct channel_context *channel;
	struct isp_io_param param;
	struct dcam_pipe_dev *dev = NULL;

	ret = copy_from_user((void *)&param,
			(void *)arg, sizeof(struct isp_io_param));
	if (unlikely(ret)) {
		pr_err("fail to copy from user, ret %d\n", ret);
		ret = -EFAULT;
		goto exit;
	}
	if (param.property_param == NULL) {
		pr_err("fail to get user param ptr.\n");
		ret = -EFAULT;
		goto exit;
	}

	dev = (struct dcam_pipe_dev *)module->dcam_dev_handle;
	if (dev && dev->raw_fetch_count > 0) {
		pr_warn("raw fetch in progress!\n");
		return 0;
	}

	if (((param.scene_id == PM_SCENE_CAP) &&
		(module->channel[CAM_CH_CAP].enable == 0))) {
		pr_warn("ch scene_id[%d] ch_cap en[%d] ch_pre en[%d]\n",
				param.scene_id,
				module->channel[CAM_CH_CAP].enable,
				module->channel[CAM_CH_PRE].enable);

		return 0;
	}

	if (atomic_read(&module->state) == CAM_STREAM_OFF)
		return 0;

	if ((param.sub_block & DCAM_ISP_BLOCK_MASK) == DCAM_BLOCK_BASE) {
		if ((param.scene_id == PM_SCENE_CAP) &&
			(module->aux_dcam_dev == NULL)) {
			pr_debug("Config DCAM param for capture. Maybe raw proc\n");
		}
		if ((param.scene_id == PM_SCENE_CAP) &&
			(module->aux_dcam_dev != NULL))
			ret = dcam_ops->cfg_blk_param(
				module->aux_dcam_dev, &param);
		else
			ret = dcam_ops->cfg_blk_param(
				module->dcam_dev_handle, &param);
	} else {
		if (param.scene_id == PM_SCENE_PRE)
			channel = &module->channel[CAM_CH_PRE];
		else
			channel = &module->channel[CAM_CH_CAP];
		if (channel->enable && channel->isp_path_id >= 0) {
			ret = isp_ops->cfg_blk_param(module->isp_dev_handle,
				channel->isp_path_id >> ISP_CTXID_OFFSET,
				&param);
		}
	}

exit:
	return ret;
}

static int img_ioctl_cfg_start(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;

	ret = dcam_ops->ioctl(module->dcam_dev_handle,
			DCAM_IOCTL_CFG_START, NULL);
	if ((module->cam_uinfo.dcam_slice_mode || module->cam_uinfo.is_4in1) && module->aux_dcam_dev)
		ret = dcam_ops->ioctl(module->aux_dcam_dev,
			DCAM_IOCTL_CFG_START, NULL);

	return ret;
}

static int img_ioctl_set_function_mode(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	/*struct sprd_img_sensor_if *dst;*/
	struct sprd_img_function_mode __user *uparam;

	uparam = (struct sprd_img_function_mode __user *)arg;
	ret |= get_user(module->cam_uinfo.is_4in1, &uparam->need_4in1);
	ret |= get_user(module->cam_uinfo.is_3dnr, &uparam->need_3dnr);
	ret |= get_user(module->cam_uinfo.is_dual, &uparam->dual_cam);
	ret |= get_user(module->cam_uinfo.is_afbc, &uparam->need_afbc);
	module->cam_uinfo.is_rgb_ltm = 0;
	module->cam_uinfo.is_yuv_ltm = 0;

	if (module->grp->hw_info->prj_id == SHARKL5pro) {
		module->cam_uinfo.is_rgb_ltm = 1;
		module->cam_uinfo.is_yuv_ltm = 0;
	}

	/* no use */
	module->cam_uinfo.is_3dnr = 0;

	pr_info("4in1:[%d], 3dnr[%d], rgb_ltm[%d], yuv_ltm[%d], dual[%d]\n, afbc[%d]\n",
		module->cam_uinfo.is_4in1,
		module->cam_uinfo.is_3dnr,
		module->cam_uinfo.is_rgb_ltm,
		module->cam_uinfo.is_yuv_ltm,
		module->cam_uinfo.is_dual,
		module->cam_uinfo.is_afbc);

	if (unlikely(ret)) {
		pr_err("fail to copy from user, ret %d\n", ret);
		ret = -EFAULT;
		goto exit;
	}

exit:
	return ret;
}


/*---------------  Misc interface end --------------- */




/*---------------  capture(sensor input) config interface start -------------*/

static int img_ioctl_set_sensor_if(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	struct sprd_img_sensor_if *dst;

	dst = &module->cam_uinfo.sensor_if;

	ret = copy_from_user(dst,
				(void __user *)arg,
				sizeof(struct sprd_img_sensor_if));
	pr_info("sensor_if %d %x %x, %d.....mipi %d %d %d %d\n",
		dst->if_type, dst->img_fmt, dst->img_ptn, dst->frm_deci,
		dst->if_spec.mipi.use_href, dst->if_spec.mipi.bits_per_pxl,
		dst->if_spec.mipi.is_loose, dst->if_spec.mipi.lane_num);

	if (unlikely(ret)) {
		pr_err("fail to copy from user, ret %d\n", ret);
		ret = -EFAULT;
		goto exit;
	}

exit:
	return ret;
}

static int img_ioctl_set_mode(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;

	ret = copy_from_user(&module->cam_uinfo.capture_mode,
				(void __user *)arg,
				sizeof(uint32_t));

	pr_info("mode %d\n", module->cam_uinfo.capture_mode);
	if (unlikely(ret)) {
		pr_err("fail to copy from user, ret %d\n", ret);
		ret = -EFAULT;
		goto exit;
	}

exit:
	return ret;
}

static int img_ioctl_set_cam_security(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	bool sec_ret = 0;
	struct sprd_cam_sec_cfg uparam;

	ret = copy_from_user(&uparam,
				(void __user *)arg,
				sizeof(struct sprd_cam_sec_cfg));

	if (unlikely(ret)) {
		pr_err("fail to copy from user, ret %d\n", ret);
		ret = -EFAULT;
		goto exit;
	}

	pr_info("camca : conn = %d, security mode %d,  u camsec_mode=%d, u work_mode=%d\n",
				module->grp->ca_conn,
				module->grp->camsec_cfg.camsec_mode,
				uparam.camsec_mode, uparam.work_mode);

	if (uparam.camsec_mode != SEC_UNABLE) {
		if (!module->grp->ca_conn)
			module->grp->ca_conn = cam_ca_connect();

		if (!module->grp->ca_conn) {
			pr_err("fail to init cam_ca_connect\n");
			ret = -EFAULT;
			goto exit;
		}

		sec_ret = camca_security_set(&uparam);

		if (!sec_ret) {
			ret = -EFAULT;
			pr_err("fail to init cam security set\n");
			goto exit;
		}

		module->grp->camsec_cfg.work_mode = uparam.work_mode;
		module->grp->camsec_cfg.camsec_mode = uparam.camsec_mode;

		ret = sprd_iommu_set_cam_bypass(true);

	}  else {
		module->grp->camsec_cfg.work_mode = uparam.work_mode;
		module->grp->camsec_cfg.camsec_mode = uparam.camsec_mode;

		ret = sprd_iommu_set_cam_bypass(false);
	}

exit:
	return ret;
}

static int img_ioctl_set_sensor_size(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	struct sprd_img_size *dst;

	dst = &module->cam_uinfo.sn_size;

	ret = copy_from_user(dst,
				(void __user *)arg,
				sizeof(struct sprd_img_size));

	pr_info("sensor_size %d %d\n", dst->w, dst->h);
	module->cam_uinfo.dcam_slice_mode = dst->w > DCAM_24M_WIDTH ? CAM_OFFLINE_SLICE_HW : 0;
	if (unlikely(ret)) {
		pr_err("fail to copy from user, ret %d\n", ret);
		ret = -EFAULT;
		goto exit;
	}

exit:
	return ret;
}

static int img_ioctl_set_sensor_trim(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	struct sprd_img_rect *dst;

	dst = &module->cam_uinfo.sn_rect;

	ret = copy_from_user(dst,
				(void __user *)arg,
				sizeof(struct sprd_img_rect));
	pr_info("sensor_trim %d %d %d %d\n", dst->x, dst->y, dst->w, dst->h);
	/* make sure MIPI CAP size is 4 pixel aligned */
	if (unlikely(ret || (dst->w | dst->h) & (DCAM_MIPI_CAP_ALIGN - 1))) {
		pr_err("fail to copy from user, ret %d\n", ret);
		ret = -EFAULT;
		goto exit;
	}

exit:
	return ret;
}

static int img_ioctl_set_sensor_max_size(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	struct sprd_img_size *dst;

	dst = &module->cam_uinfo.sn_max_size;

	ret = copy_from_user(dst,
				(void __user *)arg,
				sizeof(struct sprd_img_size));
	pr_info("sensor_max_size %d %d\n", dst->w, dst->h);

	if (unlikely(ret)) {
		pr_err("fail to copy from user, ret %d\n", ret);
		ret = -EFAULT;
		goto exit;
	}

exit:
	return ret;
}

static int img_ioctl_set_cap_skip_num(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	uint32_t *dst;

	dst = &module->cam_uinfo.capture_skip;

	ret = copy_from_user(dst,
				(void __user *)arg,
				sizeof(uint32_t));
	if (unlikely(ret)) {
		pr_err("fail to copy from user, ret %d\n", ret);
		return -EFAULT;
	}

	pr_debug("set cap skip frame %d\n", *dst);
	return 0;
}


/*---------------  capture(sensor input) config interface end --------------- */



/*---------------  Channel config interface start --------------- */

static int img_ioctl_set_output_size(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	uint32_t scene_mode;
	uint32_t cap_type;
	uint32_t sn_fmt, dst_fmt;
	struct channel_context *channel = NULL;
	struct camera_uchannel *dst;
	struct sprd_img_parm __user *uparam;

	module->last_channel_id = CAM_CH_MAX;
	uparam = (struct sprd_img_parm __user *)arg;

	ret |= get_user(scene_mode, &uparam->scene_mode);
	ret |= get_user(cap_type, &uparam->need_isp_tool);
	ret |= get_user(sn_fmt, &uparam->sn_fmt);
	ret |= get_user(dst_fmt, &uparam->pixel_fmt);

	pr_info("scene %d  cap_type %d, fmt %x %x\n",
		scene_mode, cap_type, sn_fmt, dst_fmt);
	if (unlikely(ret)) {
		pr_err("fail to copy from user, ret %d\n", ret);
		goto exit;
	}

	if (((cap_type == CAM_CAP_RAW_FULL) || (dst_fmt == sn_fmt)) &&
		(module->channel[CAM_CH_RAW].enable == 0)) {
		channel = &module->channel[CAM_CH_RAW];
		channel->enable = 1;
	} else if ((scene_mode == DCAM_SCENE_MODE_PREVIEW)  &&
			(module->channel[CAM_CH_PRE].enable == 0)) {
		channel = &module->channel[CAM_CH_PRE];
		channel->enable = 1;
	} else if (((scene_mode == DCAM_SCENE_MODE_RECORDING) ||
			(scene_mode == DCAM_SCENE_MODE_CAPTURE_CALLBACK)) &&
			(module->channel[CAM_CH_VID].enable == 0)) {
		channel = &module->channel[CAM_CH_VID];
		channel->enable = 1;
	} else if ((scene_mode == DCAM_SCENE_MODE_CAPTURE)  &&
			(module->channel[CAM_CH_CAP].enable == 0)) {
		channel = &module->channel[CAM_CH_CAP];
		channel->enable = 1;
	} else if (module->channel[CAM_CH_PRE].enable == 0) {
		channel = &module->channel[CAM_CH_PRE];
		channel->enable = 1;
	} else if (module->channel[CAM_CH_CAP].enable == 0) {
		channel = &module->channel[CAM_CH_CAP];
		channel->enable = 1;
	}

	if (channel == NULL) {
		pr_err("fail to get valid channel\n");
		ret = -EINVAL;
		goto exit;
	}

	module->last_channel_id = channel->ch_id;
	channel->dcam_path_id = -1;
	channel->isp_path_id = -1;
	channel->slave_isp_path_id = -1;

	dst = &channel->ch_uinfo;
	dst->sn_fmt = sn_fmt;
	dst->dst_fmt = dst_fmt;
	ret |= get_user(dst->is_high_fps, &uparam->is_high_fps);
	ret |= get_user(dst->high_fps_skip_num, &uparam->high_fps_skip_num);
	if (dst->high_fps_skip_num == 1) {
		pr_err("fail to get valid high fps %u\n", dst->high_fps_skip_num);
		ret = -EINVAL;
	}
	ret |= copy_from_user(&dst->src_crop,
			&uparam->crop_rect, sizeof(struct sprd_img_rect));
	ret |= copy_from_user(&dst->dst_size,
			&uparam->dst_size, sizeof(struct sprd_img_size));
	ret |= get_user(dst->slave_img_en, &uparam->aux_img.enable);
	ret |= get_user(dst->slave_img_fmt, &uparam->aux_img.pixel_fmt);
	ret |= copy_from_user(&dst->slave_img_size,
			&uparam->aux_img.dst_size, sizeof(struct sprd_img_size));

	// TODO get this from HAL
	dst->is_compressed = 0;
	dst->scene = scene_mode;
	if (cap_type == CAM_CAP_RAW_FULL && dst->is_high_fps)
		dst->is_high_fps = 0;

	pr_info("cam_channel: ch_id %d high fps %u %u. aux %d %d %d %d\n",
		channel->ch_id, dst->is_high_fps, dst->high_fps_skip_num,
		dst->slave_img_en, dst->slave_img_fmt,
		dst->slave_img_size.w, dst->slave_img_size.h);
	pr_info("cam_channel: crop %d %d %d %d dst %d %d\n",
		dst->src_crop.x, dst->src_crop.y,
		dst->src_crop.w, dst->src_crop.h,
		dst->dst_size.w, dst->dst_size.h);

exit:
	return ret;
}

static int img_ioctl_get_ch_id(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;

	if ((atomic_read(&module->state) != CAM_IDLE) &&
		(atomic_read(&module->state) != CAM_CFG_CH)) {
		pr_err("fail to get correct state, state %d\n",
			atomic_read(&module->state));
		return -EFAULT;
	}

	if (module->last_channel_id >= CAM_CH_MAX) {
		ret = -EINVAL;
		goto exit;
	}
	pr_info("cam_channel: get ch id: %d\n", module->last_channel_id);

	ret = copy_to_user((void __user *)arg, &module->last_channel_id,
				sizeof(uint32_t));
	if (unlikely(ret))
		pr_err("fail to copy to user. ret %d\n", ret);

exit:
	/* todo: error handling. */
	atomic_set(&module->state, CAM_CFG_CH);
	return ret;
}

static int img_ioctl_dcam_path_size(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	struct sprd_dcam_path_size param;

	ret = copy_from_user(
			&param, (void __user *)arg,
			sizeof(struct sprd_dcam_path_size));
	param.dcam_out_w = param.dcam_in_w;
	param.dcam_out_h = param.dcam_in_h;

	if (atomic_read(&module->timeout_flag) == 1)
		pr_info("in %d  %d. pre %d %d, vid %d, %d\n",
			param.dcam_in_w, param.dcam_in_h,
			param.pre_dst_w, param.pre_dst_h,
			param.vid_dst_w, param.vid_dst_h);

	if (unlikely(ret)) {
		pr_err("fail to copy from user, ret %d\n", ret);
		ret = -EFAULT;
		goto exit;
	}

	ret = copy_to_user((void __user *)arg, &param,
			sizeof(struct sprd_dcam_path_size));

exit:
	return ret;
}



static int img_ioctl_set_shrink(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	uint32_t channel_id;
	struct sprd_img_parm __user *uparam;

	if (atomic_read(&module->state) != CAM_CFG_CH) {
		pr_debug("skip\n");
		return ret;
	}

	uparam = (struct sprd_img_parm __user *)arg;

	ret = get_user(channel_id, &uparam->channel_id);
	if (ret == 0 && channel_id < CAM_CH_MAX) {
		ret = copy_from_user(
			&module->channel[channel_id].ch_uinfo.regular_desc,
			(void __user *)&uparam->regular_desc,
			sizeof(struct dcam_regular_desc));
	}

	if (unlikely(ret)) {
		pr_err("fail to copy from user, ret %d\n", ret);
		ret = -EFAULT;
		goto exit;
	}

exit:
	return ret;
}

 static int img_ioctl_ebd_control(struct camera_module *module,
			 unsigned long arg)
{
	int ret = 0;
	struct sprd_ebd_control ebd_tmp;
	uint32_t channel_id;
	struct sprd_img_parm __user *uparam;

	if (atomic_read(&module->state) != CAM_CFG_CH) {
		pr_debug("skip\n");
		return ret;
	}

	uparam = (struct sprd_img_parm __user *)arg;
	ret = get_user(channel_id, &uparam->channel_id);
	if (ret || (channel_id != CAM_CH_PRE))
		return 0;

	ret = copy_from_user(&ebd_tmp, &uparam->ebd_ctrl,
			sizeof(struct sprd_ebd_control));
	if (unlikely(ret)) {
		pr_err("fail to copy pdaf param from user, ret %d\n", ret);
		return -EFAULT;
	}

	pr_info("MODE: %d, VC:%d, DT:%d\n", ebd_tmp.mode,
		ebd_tmp.image_vc, ebd_tmp.image_dt);

	ret = dcam_ops->ioctl(module->dcam_dev_handle,
				DCAM_IOCTL_CFG_EBD, &ebd_tmp);

	return ret;
}

static int img_ioctl_set_zoom_mode(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;

	ret = copy_from_user(&module->is_smooth_zoom,
			     (void __user *)arg,
			     sizeof(uint32_t));

	pr_info("is_smooth_zoom %d\n", module->is_smooth_zoom);
	if (unlikely(ret)) {
		pr_err("fail to copy from user, ret %d\n", ret);
		ret = -EFAULT;
		goto exit;
	}

exit:
	return ret;
}

static int img_ioctl_set_crop(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0, zoom = 0;
	uint32_t channel_id;
	struct img_size max;
	struct channel_context *ch, *ch_vid;
	struct sprd_img_rect *crop;
	struct camera_frame *first = NULL;
	struct camera_frame *zoom_param = NULL;
	struct sprd_img_parm __user *uparam;

	if ((atomic_read(&module->state) != CAM_CFG_CH) &&
		(atomic_read(&module->state) != CAM_RUNNING)) {
		pr_warn("module state: %d\n", atomic_read(&module->state));
		return 0;
	}

	uparam = (struct sprd_img_parm __user *)arg;

	ret = get_user(channel_id, &uparam->channel_id);
	ch = &module->channel[channel_id];
	ch_vid = &module->channel[CAM_CH_VID];
	if (ret || (channel_id >= CAM_CH_MAX) || !ch->enable) {
		pr_err("fail to set crop, ret %d, ch %d\n", ret, channel_id);
		ret = -EINVAL;
		goto exit;
	}

	/* CAM_RUNNING: for zoom update
	 * only crop rect size can be re-configured during zoom
	 * and it is forbidden during capture.
	 */
	if (atomic_read(&module->state) == CAM_RUNNING) {
		if ((module->cap_status == CAM_CAPTURE_START) &&
			module->channel[CAM_CH_CAP].enable &&
			(module->channel[CAM_CH_CAP].type_3dnr != CAM_3DNR_OFF)) {
			pr_err("fail to zoom during 3DNR capture\n");
			goto exit;
		}
		crop = kzalloc(sizeof(struct sprd_img_rect), GFP_KERNEL);
		if (crop == NULL) {
			ret = -ENOMEM;
			goto exit;
		}
		zoom_param = get_empty_frame();
		zoom_param->priv_data = (void *)crop;
		zoom = 1;
	} else {
		crop = &ch->ch_uinfo.src_crop;
	}

	ret = copy_from_user(crop,
			(void __user *)&uparam->crop_rect,
			sizeof(struct sprd_img_rect));
	if (unlikely(ret)) {
		pr_err("fail to copy from user, ret %d\n", ret);
		goto exit;
	}

	max.w = module->cam_uinfo.sn_rect.w;
	max.h = module->cam_uinfo.sn_rect.h;

	pr_info("4in1[%d],set ch%d crop %d %d %d %d.\n",
		module->cam_uinfo.is_4in1, channel_id,
		crop->x, crop->y, crop->w, crop->h);
	/* 4in1 prev, enable 4in1 binning, size/2 */
	if (module->cam_uinfo.is_4in1 &&
		((channel_id == CAM_CH_PRE) || (channel_id == CAM_CH_VID))) {
		crop->x >>= 1;
		crop->y >>= 1;
		crop->w >>= 1;
		crop->h >>= 1;
		max.w >>= 1;
		max.h >>= 1;
	}
	/* > 24M, size/2 */
	if (module->cam_uinfo.dcam_slice_mode &&
		((channel_id == CAM_CH_PRE) || (channel_id == CAM_CH_VID))) {
		crop->x >>= 1;
		crop->y >>= 1;
		crop->w >>= 1;
		crop->h >>= 1;
		max.w >>= 1;
		max.h >>= 1;
	}
	crop->x &= ~1;
	crop->y &= ~1;

	/* Sharkl5pro crop align need to do research*/
	crop->w = ((crop->w + DCAM_PATH_CROP_ALIGN - 1)
		& ~(DCAM_PATH_CROP_ALIGN - 1));
	crop->h = ((crop->h + DCAM_PATH_CROP_ALIGN - 1)
		& ~(DCAM_PATH_CROP_ALIGN - 1));
	if ((crop->x + crop->w) > max.w)
		crop->w -= DCAM_PATH_CROP_ALIGN;
	if ((crop->y + crop->h) > max.h)
		crop->h -= DCAM_PATH_CROP_ALIGN;
	pr_info("aligned crop %d %d %d %d.  max %d %d\n",
		crop->x, crop->y, crop->w, crop->h, max.w, max.h);

	if (zoom) {
		if (camera_enqueue(&ch->zoom_coeff_queue, zoom_param)) {
			/* if zoom queue overflow, discard first one node in queue*/
			pr_warn("ch %d zoom q overflow\n", channel_id);
			first = camera_dequeue(&ch->zoom_coeff_queue);
			if (first) {
				kfree(first->priv_data);
				put_empty_frame(first);
			}
			camera_enqueue(&ch->zoom_coeff_queue, zoom_param);
		}
		zoom_param = NULL;
		if (ch_vid->enable && channel_id == CAM_CH_PRE)
			goto exit;
		complete(&module->zoom_thrd.thread_com);
	}
exit:
	if (zoom_param) {
		kfree(zoom_param->priv_data);
		put_empty_frame(zoom_param);
	}
	return ret;
}

static int img_ioctl_get_fmt(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	struct sprd_img_get_fmt fmt_desc;
	struct camera_format *fmt = NULL;

	ret = copy_from_user(&fmt_desc, (void __user *)arg,
				sizeof(struct sprd_img_get_fmt));
	if (unlikely(ret)) {
		pr_err("fail to copy from user ret %d\n", ret);
		ret = -EFAULT;
		goto exit;
	}
	if (unlikely(fmt_desc.index >= ARRAY_SIZE(output_img_fmt))) {
		pr_err("fail to get valid index > arrar size\n");
		ret = -EINVAL;
		goto exit;
	}

	fmt = &output_img_fmt[fmt_desc.index];
	fmt_desc.fmt = fmt->fourcc;

	ret = copy_to_user((void __user *)arg,
				&fmt_desc,
				sizeof(struct sprd_img_get_fmt));
	if (unlikely(ret)) {
		pr_err("fail to put user info, GET_FMT, ret %d\n", ret);
		ret = -EFAULT;
		goto exit;
	}
exit:
	return ret;
}

static int img_ioctl_check_fmt(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	uint32_t channel_id;
	struct sprd_img_format img_format;
	struct channel_context *channel;

	if (atomic_read(&module->state) != CAM_CFG_CH) {
		pr_debug("skip\n");
		return ret;
	}

	pr_debug("check fmt\n");
	ret = copy_from_user(&img_format,
				(void __user *)arg,
				sizeof(struct sprd_img_format));
	if (ret) {
		pr_err("fail to get img_format\n");
		return -EFAULT;
	}

	if ((atomic_read(&module->state) != CAM_CFG_CH) &&
		(atomic_read(&module->state) != CAM_RUNNING)) {
		pr_err("fail to get module state: %d\n", atomic_read(&module->state));
		return -EFAULT;
	}

	channel_id = img_format.channel_id;
	channel = &module->channel[channel_id];

	if (atomic_read(&module->state) == CAM_CFG_CH) {
		/* to do: check & set channel format / param before stream on */
		pr_info("chk_fmt ch %d\n", channel_id);

		ret = init_cam_channel(module, channel);
		if (ret) {
			/* todo: error handling. */
			pr_err("fail to init channel %d\n", channel->ch_id);
			goto exit;
		}
	}

	img_format.need_binning = 0;
	ret = copy_to_user((void __user *)arg,
			&img_format,
			sizeof(struct sprd_img_format));
	if (ret) {
		ret = -EFAULT;
		pr_err("fail to copy to user\n");
		goto exit;
	}
exit:
	return ret;
}

/* 4in1_raw_capture
 * get the second buffer from the same fd for (bin) path
 * input: i: get i group buffer
 */
static struct camera_frame *get_secondary_buf(struct sprd_img_parm *p,
			struct channel_context *ch, uint32_t i)
{
	struct camera_frame *pframe;
	int ret;
	uint32_t offset;
	uint32_t is_loose;

	pframe = get_empty_frame();
	pframe->buf.type = CAM_BUF_USER;
	pframe->buf.mfd[0] = p->fd_array[i];
	/* raw capture: 4cell + bin-sum, cal offset */
	if(ch->dcam_path_id == 0)
		is_loose = 0;
	else
		is_loose = ch->is_loose;
	offset = cal_sprd_raw_pitch(ch->ch_uinfo.src_size.w, is_loose);
	offset *= ch->ch_uinfo.src_size.h;
	offset = ALIGN_UP(offset, 4096);
	/* first buf offset: p->frame_addr_array[i].y */
	offset += p->frame_addr_array[i].y;
	pr_debug("start 0x%x 0x%x 0x%x offset 0x%x\n",
		p->frame_addr_array[i].y,
		p->frame_addr_array[i].u,
		p->frame_addr_array[i].v, offset);
	pframe->buf.offset[0] = offset;
	pframe->channel_id = ch->ch_id;

	ret = cambuf_get_ionbuf(&pframe->buf);
	if (ret) {
		put_empty_frame(pframe);
		pr_err("fail to get second buffer fail, ret %d\n", ret);
		return NULL;
	}

	return pframe;
}

static int img_ioctl_set_frame_addr(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	uint32_t i, cmd;
	struct sprd_img_parm param;
	struct channel_context *ch = NULL;
	struct channel_context *ch_prv = NULL;
	struct camera_frame *pframe = NULL;

	if ((atomic_read(&module->state) != CAM_CFG_CH) &&
		(atomic_read(&module->state) != CAM_RUNNING)) {
		pr_warn("warn: only for state CFG_CH or RUNNING\n");
		return 0;
	}

	ret = copy_from_user(&param, (void __user *)arg,
				sizeof(struct sprd_img_parm));
	if (ret) {
		pr_err("fail to copy from user. ret %d\n", ret);
		return -EFAULT;
	}

	if ((param.channel_id >= CAM_CH_MAX) ||
		(param.buffer_count == 0) ||
		(module->channel[param.channel_id].enable == 0)) {
		pr_err("fail to get valid channel id %d. buf cnt %d\n",
			param.channel_id,  param.buffer_count);
		return -EFAULT;
	}

	pr_debug("ch %d, buffer_count %d\n", param.channel_id,
			param.buffer_count);

	if (param.channel_id == CAM_CH_CAP) {
		pr_info("ch %d, buffer_count %d\n", param.channel_id,
				param.buffer_count);
	}

	ch_prv = &module->channel[CAM_CH_PRE];
	ch = &module->channel[param.channel_id];
	for (i = 0; i < param.buffer_count; i++) {
		pframe = get_empty_frame();
		pframe->buf.type = CAM_BUF_USER;
		pframe->buf.mfd[0] = param.fd_array[i];
		pframe->buf.offset[0] = param.frame_addr_array[i].y;
		pframe->buf.offset[1] = param.frame_addr_array[i].u;
		pframe->buf.offset[2] = param.frame_addr_array[i].v;
		pframe->channel_id = ch->ch_id;
		pframe->user_fid = param.user_fid;
		pframe->buf.addr_vir[0] = param.frame_addr_vir_array[i].y;
		pframe->buf.addr_vir[1] = param.frame_addr_vir_array[i].u;
		pframe->buf.addr_vir[2] = param.frame_addr_vir_array[i].v;

		pr_debug("ch %d, mfd %d, off 0x%x 0x%x 0x%x, reserved %d user_fid[%d]\n",
			pframe->channel_id, pframe->buf.mfd[0],
			pframe->buf.offset[0], pframe->buf.offset[1],
			pframe->buf.offset[2], param.is_reserved_buf,
			pframe->user_fid);

		if (param.is_reserved_buf) {
			int32_t mfd = param.fd_array[i];
			dcam_ops->ioctl(module->dcam_dev_handle,
				DCAM_IOCTL_CFG_RESERV_STATSBUF,
				&mfd);
		}

		ret = cambuf_get_ionbuf(&pframe->buf);
		if (ret) {
			put_empty_frame(pframe);
			ret = -EFAULT;
			break;
		}

		if (param.channel_id == CAM_CH_CAP || param.is_reserved_buf) {
			pr_info("ch %d, mfd %d, off 0x%x 0x%x 0x%x, size 0x%x, reserved %d\n",
				pframe->channel_id, pframe->buf.mfd[0],
				pframe->buf.offset[0], pframe->buf.offset[1],
				pframe->buf.offset[2], (uint32_t)pframe->buf.size[0],
				param.is_reserved_buf);
		}

		if (ch->isp_path_id >= 0) {
			struct camera_frame *pframe1;

			if (param.is_reserved_buf &&
				((ch->ch_id == CAM_CH_CAP)
				|| (ch->ch_id == CAM_CH_PRE)
				|| (ch->ch_id == CAM_CH_VID && !ch_prv->enable))) {
				cmd = DCAM_PATH_CFG_OUTPUT_RESERVED_BUF;
				pframe1 = get_empty_frame();
				pframe1->is_reserved = 1;
				pframe1->buf.type = CAM_BUF_USER;
				pframe1->buf.mfd[0] = param.fd_array[i];
				pframe1->buf.offset[0] = param.frame_addr_array[i].y;
				pframe1->buf.offset[1] = param.frame_addr_array[i].u;
				pframe1->buf.offset[2] = param.frame_addr_array[i].v;
				pframe1->channel_id = ch->ch_id;
				cambuf_get_ionbuf(&pframe1->buf);
				ret = dcam_ops->cfg_path(module->dcam_dev_handle,
						cmd, ch->dcam_path_id, pframe1);
				if (ret) {
					cambuf_put_ionbuf(&pframe1->buf);
					put_empty_frame(pframe1);
				}
			}

			cmd = ISP_PATH_CFG_OUTPUT_BUF;
			if (param.is_reserved_buf) {
				ch->reserved_buf_fd = pframe->buf.mfd[0];
				cmd = ISP_PATH_CFG_OUTPUT_RESERVED_BUF;
			}
			ret = isp_ops->cfg_path(module->isp_dev_handle, cmd,
					ch->isp_path_id >> ISP_CTXID_OFFSET,
					ch->isp_path_id & ISP_PATHID_MASK,
					pframe);
		} else {
			cmd = DCAM_PATH_CFG_OUTPUT_BUF;
			if (param.is_reserved_buf) {
				ch->reserved_buf_fd = pframe->buf.mfd[0];
				cmd = DCAM_PATH_CFG_OUTPUT_RESERVED_BUF;
				pframe->is_reserved = 1;
			}
			ret = dcam_ops->cfg_path(module->dcam_dev_handle,
					cmd, ch->dcam_path_id, pframe);
			/* 4in1_raw_capture, maybe need two image once */
			if (ch->second_path_enable) {
				ch->is_loose = module->cam_uinfo.sensor_if.if_spec.mipi.is_loose;
				pframe = get_secondary_buf(&param, ch, i);
				if (!pframe) {
					ret = -EFAULT;
					break;
				}
				ret = dcam_ops->cfg_path(module->dcam_dev_handle,
					cmd, ch->second_path_id, pframe);
			}
		}

		if (ret) {
			pr_err("fail to set output buffer for ch%d.\n",
				ch->ch_id);
			cambuf_put_ionbuf(&pframe->buf);
			put_empty_frame(pframe);
			ret = -EFAULT;
			break;
		}
	}

	return ret;
}

/*
 * SPRD_IMG_IO_PATH_FRM_DECI
 *
 * Set frame deci factor for each channel, which controls the number of dropped
 * frames in ISP output path. It's typically used in slow motion scene. There're
 * two situations in slow motion: preview and recording. HAL will set related
 * parameters according to the table below:
 *
 * ===================================================================================
 * |     scene     |  channel  |  is_high_fps  |  high_fps_skip_num  |  deci_factor  |
 * |---------------|-----------|---------------|---------------------|---------------|
 * |    normal     |  preview  |       0       |          0          |       0       |
 * |    preview    |           |               |                     |               |
 * |---------------|-----------|---------------|---------------------|---------------|
 * |  slow motion  |  preview  |       1       |          4          |       3       |
 * |    preview    |           |               |                     |               |
 * |---------------|-----------|---------------|---------------------|---------------|
 * |               |  preview  |       1       |          4          |       3       |
 * |  slow motion  |           |               |                     |               |
 * |   recording   |-----------|---------------|---------------------|---------------|
 * |               |   video   |       1       |          4          |       0       |
 * |               |           |               |                     |               |
 * ===================================================================================
 *
 * Here, is_high_fps means sensor is running at a high frame rate, thus DCAM
 * slow motion function should be enabled. And deci_factor controls how many
 * frames will be dropped by ISP path before DONE interrupt generated. The
 * high_fps_skip_num is responsible for keeping SOF interrupt running at 30
 * frame rate.
 */
static int img_ioctl_set_frm_deci(struct camera_module *module,
				  unsigned long arg)
{
	struct sprd_img_parm __user *uparam = NULL;
	struct channel_context *ch = NULL;
	uint32_t deci_factor = 0, channel_id = 0;
	int ret = 0;

	if ((atomic_read(&module->state) != CAM_CFG_CH) &&
		(atomic_read(&module->state) != CAM_RUNNING)) {
		pr_warn("warn: only for state CFG_CH or RUNNING\n");
		return 0;
	}

	uparam = (struct sprd_img_parm __user *)arg;
	ret |= get_user(channel_id, &uparam->channel_id);
	ret |= get_user(deci_factor, &uparam->deci);
	if (ret) {
		pr_err("fail to get from user. ret %d\n", ret);
		return -EFAULT;
	}

	if ((channel_id >= CAM_CH_MAX) ||
	    (module->channel[channel_id].enable == 0)) {
		pr_err("fail to get valid channel id %d\n", channel_id);
		return -EPERM;
	}

	ch = &module->channel[channel_id];
	ch->ch_uinfo.deci_factor = deci_factor;

	return ret;
}

static int img_ioctl_set_frame_id_base(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	uint32_t channel_id, frame_id_base;
	struct channel_context *ch;
	struct sprd_img_parm __user *uparam;

	if ((atomic_read(&module->state) != CAM_CFG_CH) &&
		(atomic_read(&module->state) != CAM_RUNNING)) {
		pr_warn("warn: only for state CFG_CH or RUNNING\n");
		return 0;
	}

	uparam = (struct sprd_img_parm __user *)arg;
	ret =  get_user(channel_id, &uparam->channel_id);
	ret |= get_user(frame_id_base, &uparam->frame_base_id);
	if (ret) {
		pr_err("fail to get from user. ret %d\n", ret);
		return -EFAULT;
	}
	if ((channel_id >= CAM_CH_MAX) ||
		(module->channel[channel_id].enable == 0)) {
		pr_err("fail to get valid channel id %d\n", channel_id);
		return -EFAULT;
	}

	ch = &module->channel[channel_id];
	ch->frm_base_id = frame_id_base;

	return ret;
}
/*---------------  Channel config interface end --------------- */




/*--------------- Core controlling interface start --------------- */

static int img_ioctl_get_cam_res(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	int dcam_idx;
	struct sprd_img_res res = {0};
	struct camera_group *grp = module->grp;
	void *dcam = NULL;
	void *isp = NULL;

	ret = copy_from_user(&res, (void __user *)arg,
				sizeof(struct sprd_img_res));
	if (ret) {
		pr_err("fail to copy_from_user\n");
		return -EFAULT;
	}

	if (atomic_read(&module->state) != CAM_INIT) {
		pr_err("fail to get cam%d state: %d\n",
			module->idx, atomic_read(&module->state));
		return -EFAULT;
	}
	pr_info("cam%d get res\n", module->idx);

	dcam_idx = -1;
#ifdef TEST_ON_HAPS
	if (res.sensor_id == 0)
		dcam_idx = 0;
	else
		dcam_idx = 1;
#else
	if (res.sensor_id < SPRD_SENSOR_ID_MAX) {
		/* get a preferred dcam dev */
		dcam_idx = sprd_sensor_find_dcam_id(res.sensor_id);
	}
#endif
	if (!is_dcam_id(module->dcam_idx) || (dcam_idx < 0)) {
		pr_err("fail to get dcam id for sensor: %d\n", res.sensor_id);
		return -EFAULT;
	}

	dcam = module->dcam_dev_handle;
	if (dcam == NULL) {
		dcam = dcam_if_get_dev(dcam_idx, grp->hw_info);
		if (IS_ERR_OR_NULL(dcam)) {
			pr_err("fail to get dcam%d\n", dcam_idx);
			ret = -EINVAL;
			goto no_dcam;
		}
		module->dcam_dev_handle = dcam;
		module->dcam_idx = dcam_idx;
	}

	ret = dcam_ops->open(dcam);
	if (ret) {
		ret = -EINVAL;
		goto dcam_fail;
	}

	pr_info("camca get camera res camsec mode %d.\n",
		module->grp->camsec_cfg.camsec_mode);

	if (module->grp->camsec_cfg.camsec_mode != SEC_UNABLE) {
		bool  sec_eb = true;

		ret = dcam_ops->ioctl(module->dcam_dev_handle,
				DCAM_IOCTL_CFG_SEC, &sec_eb);
	}

	if (ret) {
		pr_err("fail to set cam sec %d.\n", module->grp->camsec_cfg.camsec_mode);
		goto dcam_cb_fail;
	}

	ret = dcam_ops->set_callback(dcam, dcam_callback, module);
	if (ret) {
		pr_err("fail to set cam%d callback for dcam.\n", dcam_idx);
		goto dcam_cb_fail;
	}

	isp = module->isp_dev_handle;
	if (isp == NULL) {
		isp = get_isp_pipe_dev();
		if (IS_ERR_OR_NULL(isp)) {
			pr_err("fail to get isp\n");
			module->isp_dev_handle = NULL;
			ret = -EINVAL;
			goto no_isp;
		}
		module->isp_dev_handle = isp;
	}

	ret = isp_ops->ioctl(module->isp_dev_handle, 0,
		ISP_IOCTL_CFG_SEC, &module->grp->camsec_cfg.camsec_mode);

	if (ret) {
		pr_err("fail to set isp sec %d.\n", module->grp->camsec_cfg.camsec_mode);
		goto wq_fail;
	}

	ret = isp_ops->open(isp, grp->hw_info);
	if (ret) {
		pr_err("fail to enable isp module.\n");
		ret = -EINVAL;
		goto isp_fail;
	}


	module->attach_sensor_id = res.sensor_id;
	module->workqueue = create_workqueue("sprd_camera_module");
	if (!module->workqueue) {
		pr_err("fail to create camera dev wq\n");
		ret = -EINVAL;
		goto wq_fail;
	}
	atomic_set(&module->work.status, CAM_WORK_DONE);


	if (dcam_idx == DCAM_ID_0)
		res.flag = DCAM_RES_DCAM0_CAP | DCAM_RES_DCAM0_PATH;
	else if (dcam_idx == DCAM_ID_1)
		res.flag = DCAM_RES_DCAM1_CAP | DCAM_RES_DCAM1_PATH;
	else
		res.flag = DCAM_RES_DCAM2_CAP | DCAM_RES_DCAM2_PATH;


	pr_debug("sensor %d w %u h %u, cam [%d], dcam %d\n",
		res.sensor_id, res.width, res.height, module->idx, module->dcam_idx);

	pr_info("get camera res for sensor %d res %x done.\n",
					res.sensor_id, res.flag);

	ret = copy_to_user((void __user *)arg, &res,
				sizeof(struct sprd_img_res));
	if (ret) {
		pr_err("fail to copy_to_user\n");
		ret = -EFAULT;
		goto copy_fail;
	}
	atomic_set(&module->state, CAM_IDLE);
	pr_info("cam%d get res done\n", module->idx);
	return 0;

copy_fail:
	destroy_workqueue(module->workqueue);
	module->workqueue  = NULL;

wq_fail:
	isp_ops->close(isp);

isp_fail:
	put_isp_pipe_dev(isp);
	module->isp_dev_handle = NULL;

no_isp:
dcam_cb_fail:
	dcam_ops->close(dcam);

dcam_fail:
	dcam_if_put_dev(dcam);
	module->dcam_dev_handle = NULL;
no_dcam:
	pr_err("fail to get camera res for sensor: %d\n", res.sensor_id);

	return ret;
}


static int img_ioctl_put_cam_res(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	uint32_t idx;
	struct sprd_img_res res = {0};

	ret = copy_from_user(&res, (void __user *)arg,
				sizeof(struct sprd_img_res));
	if (ret) {
		pr_err("fail to copy_from_user\n");
		return -EFAULT;
	}

	pr_info("cam%d put res state: %d\n", module->idx,
		atomic_read(&module->state));

	ret = img_ioctl_stream_off(module, arg);

	if (atomic_read(&module->state) != CAM_IDLE) {
		pr_info("cam%d error state: %d\n", module->idx,
			atomic_read(&module->state));
		return -EFAULT;
	}

	idx = module->idx;

	if (module->attach_sensor_id != res.sensor_id) {
		pr_warn("warn: mismatch sensor id: %d, %d for cam %d\n",
				module->attach_sensor_id, res.sensor_id,
				module->idx);
	}

	destroy_workqueue(module->workqueue);
	module->workqueue  = NULL;
	module->attach_sensor_id = -1;

	if (module->dcam_dev_handle) {
		dcam_ops->close(module->dcam_dev_handle);
		dcam_if_put_dev(module->dcam_dev_handle);
		module->dcam_dev_handle = NULL;
	}
	if (module->isp_dev_handle) {
		isp_ops->close(module->isp_dev_handle);
		put_isp_pipe_dev(module->isp_dev_handle);
		module->isp_dev_handle = NULL;
	}

	atomic_set(&module->state, CAM_INIT);

	pr_debug("sensor %d w %u h %u, cam [%d]\n",
		res.sensor_id, res.width, res.height, module->idx);

	pr_info("put camera res for sensor %d res %x done.",
					res.sensor_id, res.flag);
	ret = copy_to_user((void __user *)arg, &res,
			sizeof(struct sprd_img_res));
	if (ret)
		pr_err("fail to copy_to_user!\n");

	return ret;
}

static int img_ioctl_stream_on(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	uint32_t i, j, line_w, isp_ctx_id, isp_path_id;
	uint32_t uframe_sync, live_ch_count = 0, shutoff = 0;
	struct channel_context *ch = NULL;
	struct channel_context *ch_pre = NULL, *ch_vid = NULL;
	struct cam_hw_info *hw = NULL;
	struct dcam_pipe_dev *dev = NULL;

	if (atomic_read(&module->state) != CAM_CFG_CH) {
		pr_info("cam%d error state: %d\n", module->idx,
				atomic_read(&module->state));
		return -EFAULT;
	}

	module->flash_skip_fid = 0;
	atomic_set(&module->state, CAM_STREAM_ON);
	pr_info("cam%d stream on starts\n", module->idx);

	/* settle down compression policy here */
	cal_compression(module);

	ret = init_channels_size(module);
	if (module->zoom_solution == ZOOM_DEFAULT)
		cal_channel_size_bininig(module, 1);
	else if (module->zoom_solution == ZOOM_BINNING2 ||
		module->zoom_solution == ZOOM_BINNING4)
		cal_channel_size_bininig(module, 0);
	else
		cal_channel_size_rds(module);

	config_compression(module);

	ch_pre = &module->channel[CAM_CH_PRE];
	if (ch_pre->enable)
		config_channel_size(module, ch_pre);

	ch_vid = &module->channel[CAM_CH_VID];
	if (ch_vid->enable && !ch_pre->enable)
		config_channel_size(module, ch_vid);

	ch = &module->channel[CAM_CH_CAP];
	if (ch->enable) {
		config_channel_size(module, ch);
		/* alloc dcam1 memory and cfg out buf */
		if (module->cam_uinfo.dcam_slice_mode)
			config_channel_bigsize(module, ch);
	}

	/* line buffer share mode setting
	 * Precondition: dcam0, dcam1 size not conflict
	 */
	hw = module->grp->hw_info;
	line_w = module->cam_uinfo.sn_rect.w;
	if (module->cam_uinfo.is_4in1)
		line_w /= 2;
	if (hw->ip_dcam[module->dcam_idx]->lbuf_share_support
		&& hw->hw_ops.core_ops.lbuf_share_set)
		ret = hw->hw_ops.core_ops.lbuf_share_set(module->dcam_idx, line_w);
	if (ret) {
		pr_err("fail to set line buf share\n");
		ret = -EFAULT;
		goto exit;
	}

	ret = dcam_ops->ioctl(module->dcam_dev_handle,
				DCAM_IOCTL_INIT_STATIS_Q, NULL);

	for (i = 0;  i < CAM_CH_MAX; i++) {
		ch = &module->channel[i];
		if (!ch->enable || (ch->ch_id == CAM_CH_RAW))
			continue;

		live_ch_count++;

		uframe_sync = ch->ch_id != CAM_CH_CAP;
		ret = isp_ops->cfg_path(module->isp_dev_handle,
					ISP_PATH_CFG_PATH_UFRAME_SYNC,
					ch->isp_path_id >> ISP_CTXID_OFFSET,
					ch->isp_path_id & ISP_PATHID_MASK,
					&uframe_sync);
		ret = isp_ops->cfg_path(module->isp_dev_handle,
					ISP_PATH_CFG_CTX_UFRAME_SYNC,
					ch->isp_path_id >> ISP_CTXID_OFFSET,
					ch->isp_path_id & ISP_PATHID_MASK,
					&uframe_sync);

		camera_queue_init(&ch->zoom_coeff_queue,
			(module->is_smooth_zoom ? CAM_ZOOM_COEFF_Q_LEN : 1),
			0, camera_put_empty_frame);

		if (ch->alloc_start) {
			ret = wait_for_completion_interruptible(&ch->alloc_com);
			if (ret != 0) {
				pr_err("fail to config channel/path param work %d\n",
					ret);
				flush_workqueue(module->workqueue);
				goto exit;
			}
			ch->alloc_start = 0;

			if (atomic_read(&ch->err_status) != 0) {
				pr_err("fail to get ch %d correct status\n", ch->ch_id);
				ret = -EFAULT;
				goto exit;
			}

			/* set shared frame for dcam output */
			while (1) {
				struct camera_frame *pframe = NULL;

				pframe = camera_dequeue(&ch->share_buf_queue);
				if (pframe == NULL)
					break;
				if (module->cam_uinfo.is_4in1 &&
					i == CAM_CH_CAP)
					ret = dcam_ops->cfg_path(
						module->dcam_dev_handle,
						DCAM_PATH_CFG_OUTPUT_BUF,
						ch->aux_dcam_path_id,
						pframe);
				else
					ret = dcam_ops->cfg_path(
						module->dcam_dev_handle,
						DCAM_PATH_CFG_OUTPUT_BUF,
						ch->dcam_path_id,
						pframe);
				if (ret) {
					pr_err("fail to config dcam output buffer\n");
					camera_enqueue(&ch->share_buf_queue,
						pframe);
					ret = -EINVAL;
					goto exit;
				}
			}
			isp_ctx_id = ch->isp_path_id >> ISP_CTXID_OFFSET;
			isp_path_id = ch->isp_path_id & ISP_PATHID_MASK;

			for (j = 0; j < ISP_NR3_BUF_NUM; j++) {
				if (ch->nr3_bufs[j] == NULL)
					continue;
				ret = isp_ops->cfg_path(module->isp_dev_handle,
						ISP_PATH_CFG_3DNR_BUF,
						isp_ctx_id, isp_path_id,
						ch->nr3_bufs[j]);
				if (ret) {
					pr_err("fail to config isp 3DNR buffer\n");
					goto exit;
				}
			}

			if (module->cam_uinfo.is_rgb_ltm) {
				for (j = 0; j < ISP_LTM_BUF_NUM; j++) {
					if (ch->ltm_bufs[LTM_RGB][j] == NULL) {
						pr_debug("ch->ltm_bufs[%d][%d] NULL\n",
							LTM_RGB, j);
						continue;
					}
					ret = isp_ops->cfg_path(module->isp_dev_handle,
							ISP_PATH_CFG_RGB_LTM_BUF,
							isp_ctx_id, isp_path_id,
							ch->ltm_bufs[LTM_RGB][j]);
					if (ret) {
						pr_err("fail to config isp rgb LTM buffer\n");
						goto exit;
					}
				}
			}

			if (module->cam_uinfo.is_yuv_ltm) {
				for (j = 0; j < ISP_LTM_BUF_NUM; j++) {
					if (ch->ltm_bufs[LTM_YUV][j] == NULL) {
						pr_debug("ch->ltm_bufs[%d][%d] NULL\n",
							LTM_YUV, j);
						continue;
					}
					ret = isp_ops->cfg_path(module->isp_dev_handle,
							ISP_PATH_CFG_YUV_LTM_BUF,
							isp_ctx_id, isp_path_id,
							ch->ltm_bufs[LTM_YUV][j]);
					if (ret) {
						pr_err("fail to config isp yuv LTM buffer\n");
						goto exit;
					}
				}
			}

			if (hw->ip_dcam[module->dcam_idx]->superzoom_support
				&& ch->ch_id == CAM_CH_CAP) {
				if (ch->superzoom_buf== NULL)
					continue;
				ret = isp_ops->cfg_path(module->isp_dev_handle,
						ISP_PATH_CFG_SUPERZOOM_BUF,
						isp_ctx_id, isp_path_id,
						ch->superzoom_buf);
				if (ret) {
					pr_err("fail to config isp superzoom buffer sw %d,  path id %d\n",
						isp_ctx_id, isp_path_id);
					goto exit;
				}
			}
		}
	}

	/* TODO: WORKAROUND for BBAT/factory_test/mini_camera, remove later */
	if (live_ch_count == 1) {
		pr_info("disable all uframe_sync feature\n");

		uframe_sync = 0;
		for (i = 0; i < CAM_CH_MAX; i++) {
			ch = &module->channel[i];
			if (!ch->enable)
				continue;

			isp_ctx_id = ch->isp_path_id >> ISP_CTXID_OFFSET;
			isp_path_id = ch->isp_path_id & ISP_PATHID_MASK;

			isp_ops->cfg_path(module->isp_dev_handle,
						ISP_PATH_CFG_PATH_UFRAME_SYNC,
						isp_ctx_id, isp_path_id,
						&uframe_sync);
		}
	}

	pr_info("wait for wq done.\n");
	flush_workqueue(module->workqueue);

	camera_queue_init(&module->frm_queue,
		CAM_FRAME_Q_LEN, 0, camera_put_empty_frame);
	camera_queue_init(&module->irq_queue,
		CAM_IRQ_Q_LEN, 0, camera_put_empty_frame);
	camera_queue_init(&module->statis_queue,
		CAM_STATIS_Q_LEN, 0, camera_put_empty_frame);
	camera_queue_init(&module->zsl_fifo_queue,
			CAM_SHARED_BUF_NUM, 0, put_k_frame);
	/* no need release buffer, only release camera_frame */
	camera_queue_init(&module->remosaic_queue,
			CAM_IRQ_Q_LEN, 0, cam_release_camera_frame);

	set_cap_info(module);

	module->dual_frame = NULL;
	dev = (struct dcam_pipe_dev *)module->dcam_dev_handle;
	if (module->cam_uinfo.is_4in1) {
		shutoff = 1;
		dcam_ops->cfg_path(dev, DCAM_PATH_CFG_SHUTOFF, DCAM_PATH_BIN, &shutoff);
	}
	if (module->channel[CAM_CH_CAP].enable)
		dcam_ops->cfg_path(dev, DCAM_PATH_CFG_STATE,
			DCAM_PATH_FULL, &module->path_state);
	ret = dcam_ops->start(module->dcam_dev_handle, 1);
	if (ret < 0) {
		pr_err("fail to start dcam dev, ret %d\n", ret);
		goto exit;
	}
	if (module->cam_uinfo.dcam_slice_mode && module->aux_dcam_dev) {
		ret = dcam_ops->start(module->aux_dcam_dev, 0);
		if (ret < 0) {
			pr_err("fail to start aux_dcam dev, ret %d\n", ret);
			goto exit;
		}
	}
	atomic_set(&module->state, CAM_RUNNING);
	atomic_set(&module->timeout_flag, 1);
	ret = sprd_start_timer(&module->cam_timer, CAMERA_TIMEOUT);

	if (hw->ip_dcam[module->dcam_idx]->superzoom_support) {
		init_completion(&module->channel[CAM_CH_CAP].superzoom_frm);
		complete(&module->channel[CAM_CH_CAP].superzoom_frm);
		pr_info("superzoom stream on do complete, dcam %d\n",
			module->dcam_idx);
	}

	if (module->dump_thrd.thread_task) {
		camera_queue_init(&module->dump_queue, 10, 0, put_k_frame);
		init_completion(&module->dump_com);
		mutex_lock(&g_dbg_dump.dump_lock);
		i = module->dcam_idx;
		if (i < 2) {
			g_dbg_dump.dump_start[i] = &module->dump_thrd.thread_com;
			g_dbg_dump.dump_count = 0;
		}
		mutex_unlock(&g_dbg_dump.dump_lock);
	}

	pr_info("stream on done.\n");
	return 0;

exit:
	atomic_set(&module->state, CAM_CFG_CH);
	pr_info("stream on failed\n");

	/* call stream_off to clear buffers/path */
	img_ioctl_stream_off(module, 0L);

	return ret;
}


static int img_ioctl_stream_off(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	uint32_t i, j;
	uint32_t raw_cap = 0, running = 0;
	int32_t dcam_path_id;
	struct channel_context *ch = NULL;
	struct channel_context *ch_prv = NULL;
	int isp_ctx_id[CAM_CH_MAX] = { -1 };
	struct cam_hw_info *hw = NULL;

	if ((atomic_read(&module->state) != CAM_RUNNING) &&
		(atomic_read(&module->state) != CAM_CFG_CH)) {
		pr_info("cam%d state: %d\n", module->idx,
				atomic_read(&module->state));
		return -EFAULT;
	}

	if (atomic_read(&module->state) == CAM_RUNNING)
		running = 1;

	pr_info("cam %d stream off. state: %d\n",
		module->idx, atomic_read(&module->state));
	atomic_set(&module->state, CAM_STREAM_OFF);
	module->cap_status = CAM_CAPTURE_STOP;
	module->dcam_cap_status = DCAM_CAPTURE_STOP;

	hw = module->grp->hw_info;
	if (hw->ip_dcam[module->dcam_idx]->superzoom_support) {
		init_completion(&module->channel[CAM_CH_CAP].superzoom_frm);
		pr_info("superzoom stream off init complete.\n");
	}
	/* stop raw dump */
	if (module->dump_thrd.thread_task) {
		if (module->in_dump)
			complete(&module->dump_com);
		mutex_lock(&g_dbg_dump.dump_lock);
		i = module->dcam_idx;
		if (i < 2) {
			g_dbg_dump.dump_start[i] = NULL;
			g_dbg_dump.dump_count = 0;
		}
		mutex_unlock(&g_dbg_dump.dump_lock);
		j = 0;
		while (module->in_dump && (j++ < THREAD_STOP_TIMEOUT)) {
			pr_info("camera%d in dump, wait...%d\n", module->idx, j);
			msleep(10);
		}
	}

	if (running) {
		ret = dcam_ops->stop(module->dcam_dev_handle);
		if (ret != 0)
			pr_err("fail to stop dcam %d\n", ret);
		sprd_stop_timer(&module->cam_timer);
	}
	if (module->cam_uinfo.is_4in1)
		deinit_4in1_aux(module);
	if (module->cam_uinfo.dcam_slice_mode && module->aux_dcam_dev)
		deinit_bigsize_aux(module);

	ret = dcam_ops->ioctl(module->dcam_dev_handle,
		DCAM_IOCTL_CFG_STOP, NULL);

	ch_prv = &module->channel[CAM_CH_PRE];
	for (i = 0; i < CAM_CH_MAX; i++) {
		ch = &module->channel[i];
		isp_ctx_id[i] = -1;
		if (!ch->enable)
			continue;
		if (ch->ch_id == CAM_CH_RAW) {
			raw_cap = 1;
			if (module->cam_uinfo.is_4in1)
				deinit_4in1_secondary_path(module, ch);
		}
		pr_info("clear ch %d, dcam path %d, isp path 0x%x\n",
				ch->ch_id,
				ch->dcam_path_id,
				ch->isp_path_id);
		/* prv & vid use same dcam bin path, no need to put it twice */
		if (ch->ch_id == CAM_CH_VID && ch_prv->enable)
			dcam_path_id = -1;
		else
			dcam_path_id = ch->dcam_path_id;
		if (dcam_path_id >= 0) {
			dcam_ops->put_path(module->dcam_dev_handle,
					ch->dcam_path_id);
		}
		if (ch->isp_path_id >= 0) {
			isp_ctx_id[i] = ch->isp_path_id >> ISP_CTXID_OFFSET;
			isp_ops->put_path(module->isp_dev_handle,
					isp_ctx_id[i],
					ch->isp_path_id & ISP_PATHID_MASK);
			if (hw->ip_dcam[module->dcam_idx]->superzoom_support
				&& ch->ch_id == CAM_CH_CAP) {
				pr_info("put path superzoom\n");
				isp_ops->put_path(module->isp_dev_handle,
					ISP_CONTEXT_SUPERZOOM,
					ch->isp_path_id & ISP_PATHID_MASK);
			}
		}
		if (ch->slave_isp_path_id >= 0) {
			isp_ops->put_path(module->isp_dev_handle,
					isp_ctx_id[i],
					ch->slave_isp_path_id & ISP_PATHID_MASK);
		}
	}

	for (i = 0;  i < CAM_CH_MAX; i++) {
		ch = &module->channel[i];
		if (!ch->enable || (ch->ch_id == CAM_CH_RAW))
			continue;
		camera_queue_clear(&ch->zoom_coeff_queue);

		if ((ch->ch_id == CAM_CH_PRE) || (ch->ch_id == CAM_CH_CAP)) {
			if (isp_ctx_id[i] != -1)
				isp_ops->put_context(module->isp_dev_handle,
					isp_ctx_id[i]);

			if (hw->ip_dcam[module->dcam_idx]->superzoom_support
				&& ch->ch_id == CAM_CH_CAP) {
				pr_info("put context superzoom\n");
				isp_ops->put_context(module->isp_dev_handle,
					ISP_CONTEXT_SUPERZOOM);
			}

			if (ch->alloc_start) {
				ret = wait_for_completion_interruptible(
					&ch->alloc_com);
				if (ret != 0)
					pr_err("fail to config channel/path param work %d\n",
						ret);
				pr_info("alloc buffer done.\n");
				ch->alloc_start = 0;
			}
			if (ch->isp_updata) {
				struct isp_offline_param *cur, *prev;

				cur = (struct isp_offline_param *)ch->isp_updata;
				ch->isp_updata = NULL;
				while (cur) {
					prev = (struct isp_offline_param *)cur->prev;
					pr_info("free %p\n", cur);
					kfree(cur);
					cur = prev;
				}
			}
			camera_queue_clear(&ch->share_buf_queue);

			for (j = 0; j < ISP_NR3_BUF_NUM; j++) {
				if (ch->nr3_bufs[j]) {
					put_k_frame(ch->nr3_bufs[j]);
					ch->nr3_bufs[j] = NULL;
				}
			}

			if (module->cam_uinfo.is_rgb_ltm) {
				for (j = 0; j < ISP_LTM_BUF_NUM; j++) {
					if (ch->ltm_bufs[LTM_RGB][j]) {
						if (ch->ch_id == CAM_CH_PRE)
							put_k_frame(ch->ltm_bufs[LTM_RGB][j]);
						ch->ltm_bufs[LTM_RGB][j] = NULL;
					}
				}
			}

			if (module->cam_uinfo.is_yuv_ltm) {
				for (j = 0; j < ISP_LTM_BUF_NUM; j++) {
					if (ch->ltm_bufs[LTM_YUV][j]) {
						if (ch->ch_id == CAM_CH_PRE)
							put_k_frame(ch->ltm_bufs[LTM_YUV][j]);
						ch->ltm_bufs[LTM_YUV][j] = NULL;
					}
				}
			}

			if (hw->ip_dcam[module->dcam_idx]->superzoom_support
				&& ch->ch_id == CAM_CH_CAP) {
				if (ch->superzoom_buf) {
					put_k_frame(ch->superzoom_buf);
					ch->superzoom_buf = NULL;
					pr_info("superzoom put frame\n");
				}
			}
		}
	}

	if (module->dcam_dev_handle) {
		ret = dcam_ops->ioctl(module->dcam_dev_handle,
				DCAM_IOCTL_DEINIT_STATIS_Q, NULL);
		if (ret != 0)
			pr_err("fail to deinit statis q %d\n", ret);
	}

	for (i = 0; i < CAM_CH_MAX; i++) {
		ch = &module->channel[i];
		memset(ch, 0, sizeof(struct channel_context));
		ch->ch_id = i;
		ch->dcam_path_id = -1;
		ch->isp_path_id = -1;
		init_completion(&ch->alloc_com);
	}

	if (running) {
		/* wait for read thread take all events in frm_queue,
		  * frm_queue max len is CAM_FRAME_Q_LEN
		  * then we loop for this counter.
		  * if read thread has exited unexpectedly,
		  * queue_clear() will clear frm_queue as well
		  */
		j = CAM_FRAME_Q_LEN;
		while (j--) {
			i = camera_queue_cnt(&module->frm_queue);
			if (i == 0)
				break;
			pr_info("camera%d wait for read %d %d\n", module->idx, i, j);
			msleep(20);
		}

		camera_queue_clear(&module->frm_queue);
		camera_queue_clear(&module->irq_queue);
		camera_queue_clear(&module->statis_queue);
		if (module->dual_frame) {
			camera_enqueue(&module->zsl_fifo_queue, module->dual_frame);
			module->dual_frame = NULL;
		}
		camera_queue_clear(&module->zsl_fifo_queue);
		camera_queue_clear(&module->remosaic_queue);
		if (module->dump_thrd.thread_task)
			camera_queue_clear(&module->dump_queue);
		/* default 0, hal set 1 when needed */
		module->auto_3dnr = 0;
	}
	atomic_set(&module->state, CAM_IDLE);
	if (raw_cap)
		complete(&module->streamoff_com);

	ret = mdbg_check();
	pr_info("cam %d stream off done.\n", module->idx);

	return ret;
}

static int set_capture_3dnr(struct camera_module *module,
			struct channel_context *ch)
{
	uint32_t mode_3dnr;

	if ((!module) || (!ch))
		return -EFAULT;
	mode_3dnr = MODE_3DNR_OFF;
	if (ch->uinfo_3dnr) {
		if (ch->ch_id == CAM_CH_CAP)
			mode_3dnr = MODE_3DNR_CAP;
		else
			mode_3dnr = MODE_3DNR_PRE;
	}
	pr_debug("mode %d\n", mode_3dnr);
	isp_ops->cfg_path(module->isp_dev_handle, ISP_PATH_CFG_3DNR_MODE,
		ch->isp_path_id >> ISP_CTXID_OFFSET,
		ch->isp_path_id & ISP_PATHID_MASK, &mode_3dnr);

	return 0;
}

static int img_ioctl_start_capture(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	struct sprd_img_capture_param param;
	struct cam_hw_info *hw = NULL;
	ktime_t start_time = 0;
	uint32_t isp_idx = 0;
	uint32_t cap_skip_num = 0;

	ret = copy_from_user(&param, (void __user *)arg,
			sizeof(struct sprd_img_capture_param));
	if (ret) {
		pr_err("fail to copy user info\n");
		return -EFAULT;
	}

	if (atomic_read(&module->state) != CAM_RUNNING) {
		pr_info("cam%d state: %d\n", module->idx,
				atomic_read(&module->state));
		return ret;
	}
	hw = module->grp->hw_info;
	start_time = ktime_get_boottime();

	module->capture_scene = param.cap_scene;
	isp_idx = module->channel[CAM_CH_CAP].isp_path_id >> ISP_CTXID_OFFSET;
	if (module->capture_scene == CAPTURE_HDR
		|| module->capture_scene == CAPTURE_SW3DNR
		|| module->capture_scene == CAPTURE_HW3DNR) {
		if (hw->hw_ops.core_ops.cam_gtm_ltm_dis)
			hw->hw_ops.core_ops.cam_gtm_ltm_dis(
				module->dcam_idx, isp_idx);
	}
	atomic_set(&module->cap_skip_frames, -1);

	/* recognize the capture scene */
	if (param.type == DCAM_CAPTURE_START_FROM_NEXT_SOF) {
		module->dcam_cap_status = DCAM_CAPTURE_START_FROM_NEXT_SOF;
		if (hw->hw_ops.core_ops.dcam_gtm_status_get)
			cap_skip_num = hw->hw_ops.core_ops.dcam_gtm_status_get(
				module->dcam_idx);
		atomic_set(&module->cap_skip_frames, cap_skip_num);
		atomic_set(&module->capture_frames_dcam, param.cap_cnt);
		module->capture_times = start_time;
	} else if (param.type == DCAM_CAPTURE_START_WITH_TIMESTAMP) {
		module->dcam_cap_status = DCAM_CAPTURE_START_WITH_TIMESTAMP;
		/* dual camera need 1 frame */
		atomic_set(&module->capture_frames_dcam, CAP_NUM_COMMON);
		module->capture_times = param.timestamp;

	} else if (module->cam_uinfo.is_4in1) {
		/* not report when setting */
		atomic_set(&module->capture_frames_dcam, 0);
		if (param.type == DCAM_CAPTURE_START_4IN1_LOWLUX) {
			/* 4in1: low lux mode, report until stop capture
			 * raw capture then not change source of full
			 * maybe need 1 frame
			 */
			if (module->last_channel_id == CAM_CH_RAW) {
				atomic_set(&module->capture_frames_dcam, -1);
				module->lowlux_4in1 = 0;
			} else {
				module->lowlux_4in1 = 1;
				dcam_ops->cfg_path(module->dcam_dev_handle,
					DCAM_PATH_CFG_FULL_SOURCE,
					DCAM_PATH_FULL,
					&module->lowlux_4in1);
			}
		} else {
			/* 4in1: report 1 frame for remosaic */
			module->lowlux_4in1 = 0;
			atomic_set(&module->capture_frames_dcam, CAP_NUM_COMMON);
		}
		config_4in1_channel_size(module, module->lowlux_4in1);
	} else if (param.type == DCAM_CAPTURE_START) {
		module->dcam_cap_status = DCAM_CAPTURE_START;
		atomic_set(&module->capture_frames_dcam, CAP_NUM_COMMON);
	} else {
		atomic_set(&module->capture_frames_dcam, -1);
	}

	if (param.type != DCAM_CAPTURE_STOP)
		module->cap_status = CAM_CAPTURE_START;

	/* alway trigger dump for capture */
	if (module->dump_thrd.thread_task) {
		uint32_t idx = module->dcam_idx;
		struct cam_dbg_dump *dbg = &g_dbg_dump;

		if (idx < 2 && module->dcam_dev_handle) {
			mutex_lock(&dbg->dump_lock);
			if (!(dbg->dump_ongoing & (1 << idx))) {
				complete(&module->dump_thrd.thread_com);
				dbg->dump_count = 99;
				pr_debug("trigger sdump capture raw\n");
			}
			mutex_unlock(&dbg->dump_lock);
		}
	}

	pr_info("cam %d start capture type %d, cnt %d, time %lld\n",
		module->idx, param.type, param.cap_cnt, module->capture_times);
	return ret;
}


static int img_ioctl_stop_capture(
			struct camera_module *module,
			unsigned long arg)
{
	struct channel_context *channel = NULL;
	struct cam_hw_info *hw = NULL;
	uint32_t isp_idx = 0;

	module->cap_status = CAM_CAPTURE_STOP;
	module->dcam_cap_status = DCAM_CAPTURE_STOP;

	pr_info("cam %d stop capture.\n", module->idx);
	hw = module->grp->hw_info;
	isp_idx = module->channel[CAM_CH_CAP].isp_path_id >> ISP_CTXID_OFFSET;
	if (module->capture_scene == CAPTURE_HDR
		|| module->capture_scene == CAPTURE_SW3DNR
		|| module->capture_scene == CAPTURE_HW3DNR) {
		if (hw->hw_ops.core_ops.cam_gtm_ltm_eb)
			hw->hw_ops.core_ops.cam_gtm_ltm_eb(
				module->dcam_idx, isp_idx);
	}

	/* Handling special case in which stop_capture comes before start_capture.
	 * In this case before assigning NULL to  module->dual_frame, we should check if it points
	 * to some valid frame, if yes then add that frame to dcam path queue to avoid Memroy leak.
	 */
	if (module->cam_uinfo.is_dual && module->dual_frame) {
		channel = &module->channel[module->dual_frame->channel_id];
		dcam_ops->cfg_path(module->dcam_dev_handle,
				DCAM_PATH_CFG_OUTPUT_BUF,
				channel->dcam_path_id, module->dual_frame);
		pr_info("stop capture comes before start capture, dcam_path_Id = %d\n", channel->dcam_path_id);
		module->dual_frame = NULL;
	}
	/* stop dump for capture */
	if (module->dump_thrd.thread_task && module->in_dump) {
		module->dump_count = 0;
		complete(&module->dump_com);
	}
	/* 4in1 lowlux deinit */
	if (module->cam_uinfo.is_4in1 && module->lowlux_4in1) {
		module->lowlux_4in1 = 0;
		dcam_ops->cfg_path(module->dcam_dev_handle,
				DCAM_PATH_CFG_FULL_SOURCE,
				DCAM_PATH_FULL,
				&module->lowlux_4in1);
	}

	return 0;
}

static int raw_proc_done(struct camera_module *module)
{
	int ret = 0;
	int isp_ctx_id, isp_path_id;
	unsigned long flag = 0;
	struct camera_group *grp = module->grp;
	struct channel_context *ch;
	struct channel_context *ch_raw;
	struct dcam_pipe_dev *dev = NULL;

	pr_info("cam%d start\n", module->idx);

	module->cap_status = CAM_CAPTURE_STOP;
	module->dcam_cap_status = DCAM_CAPTURE_STOP;
	atomic_set(&module->state, CAM_STREAM_OFF);

	if (atomic_read(&module->timeout_flag) == 1)
		pr_err("fail to raw proc, timeout\n");

	ret = dcam_ops->stop(module->dcam_dev_handle);
	sprd_stop_timer(&module->cam_timer);

	ret = dcam_ops->ioctl(module->dcam_dev_handle,
		DCAM_IOCTL_CFG_STOP, NULL);

	ret = dcam_ops->ioctl(module->dcam_dev_handle,
			DCAM_IOCTL_DEINIT_STATIS_Q, NULL);

	ch_raw = &module->channel[CAM_CH_RAW];
	if(ch_raw->enable!=0) {

		dcam_ops->put_path(module->dcam_dev_handle,
					ch_raw->dcam_path_id);

		isp_ctx_id = ch_raw->isp_path_id >> ISP_CTXID_OFFSET;
		isp_path_id = ch_raw->isp_path_id & ISP_PATHID_MASK;

		isp_ops->put_path(module->isp_dev_handle,
					isp_ctx_id, isp_path_id);
		isp_ops->put_context(module->isp_dev_handle, isp_ctx_id);

		ch_raw->enable = 0;
		ch_raw->dcam_path_id = -1;
		ch_raw->isp_path_id = -1;
		ch_raw->aux_dcam_path_id = -1;
	}

	ch = &module->channel[CAM_CH_CAP];
	dcam_ops->put_path(module->dcam_dev_handle,
					ch->dcam_path_id);

	isp_ctx_id = ch->isp_path_id >> ISP_CTXID_OFFSET;
	isp_path_id = ch->isp_path_id & ISP_PATHID_MASK;
	isp_ops->put_path(module->isp_dev_handle,
					isp_ctx_id, isp_path_id);
	isp_ops->put_context(module->isp_dev_handle, isp_ctx_id);

	ch->enable = 0;
	ch->dcam_path_id = -1;
	ch->isp_path_id = -1;
	ch->aux_dcam_path_id = -1;
	camera_queue_clear(&module->frm_queue);
	camera_queue_clear(&ch->share_buf_queue);
	module->cam_uinfo.dcam_slice_mode = CAM_SLICE_NONE;
	module->cam_uinfo.slice_num = 0;

	dev = (struct dcam_pipe_dev *)module->dcam_dev_handle;
	dev->raw_fetch_num = 0;
	dev->raw_fetch_count = 0;
	atomic_set(&module->state, CAM_IDLE);
	pr_info("camera%d rawproc done.\n", module->idx);

	spin_lock_irqsave(&grp->rawproc_lock, flag);
	if (grp->rawproc_in == 0)
		pr_err("fail to raw proc, cam%d rawproc_in should be 1 here.\n", module->idx);
	grp->rawproc_in = 0;
	spin_unlock_irqrestore(&grp->rawproc_lock, flag);

	return ret;
}

/* build channel/path in pre-processing */
static int raw_proc_pre(
		struct camera_module *module,
		struct isp_raw_proc_info *proc_info)
{
	int ret = 0;
	int ctx_id, dcam_path_id, isp_path_id;
	uint32_t loop = 0;
	unsigned long flag = 0;
	struct camera_group *grp = module->grp;
	struct cam_hw_info *hw = NULL;
	struct channel_context *ch = NULL;
	struct img_trim path_trim;
	struct dcam_path_cfg_param ch_desc;
	struct isp_ctx_base_desc ctx_desc;
	struct isp_ctx_size_desc ctx_size;
	struct isp_path_base_desc isp_path_desc;
	struct isp_init_param init_param;

	pr_info("cam%d in. module:%p,  grp %p, %p\n",
		module->idx, module, grp, &grp->rawproc_in);

	do {
		spin_lock_irqsave(&grp->rawproc_lock, flag);
		if (grp->rawproc_in == 0) {
			grp->rawproc_in = 1;
			spin_unlock_irqrestore(&grp->rawproc_lock, flag);
			pr_info("cam%d get rawproc_in\n", module->idx);
			break;
		} else {
			spin_unlock_irqrestore(&grp->rawproc_lock, flag);
			pr_info("cam%d will wait. loop %d\n", module->idx, loop);
			loop++;
			msleep(10);
		}
	} while (loop < 2000);

	if (loop >= 1000) {
		pr_err("fail to raw proc, wait another camera raw proc\n");
		return -EFAULT;
	}
	/* not care 4in1 */
	ch = &module->channel[CAM_CH_CAP];
	ch->dcam_path_id = -1;
	ch->isp_path_id = -1;
	ch->aux_dcam_path_id = -1;

	if ((module->grp->hw_info->prj_id == SHARKL3)
		&& proc_info->src_size.width > ISP_WIDTH_MAX
		&& proc_info->dst_size.width > ISP_WIDTH_MAX) {
		struct dcam_pipe_dev *dev = NULL;

		ch->ch_uinfo.src_size.w = proc_info->src_size.width;
		ch->ch_uinfo.src_size.h = proc_info->src_size.height;
		ch->ch_uinfo.dst_size.w = proc_info->dst_size.width;
		ch->ch_uinfo.dst_size.h = proc_info->dst_size.height;
		module->cam_uinfo.dcam_slice_mode = CAM_OFFLINE_SLICE_SW;
		module->cam_uinfo.slice_num = get_slice_num_info(&ch->ch_uinfo.src_size,
			&ch->ch_uinfo.dst_size);
		module->cam_uinfo.slice_count = 0;
		module->auto_3dnr = 0;

		dev = (struct dcam_pipe_dev *)module->dcam_dev_handle;
		dev->dcam_slice_mode = module->cam_uinfo.dcam_slice_mode;
		dev->slice_num = module->cam_uinfo.slice_num;
		dev->slice_count = 0;
		pr_debug("slice_num %d\n", module->cam_uinfo.slice_num);
	}

	/* specify dcam path */
	dcam_path_id = DCAM_PATH_BIN;
	ret = dcam_ops->get_path(
		module->dcam_dev_handle, dcam_path_id);
	if (ret < 0) {
		pr_err("fail to get dcam path %d\n", dcam_path_id);
		return -EFAULT;
	}
	ch->dcam_path_id = dcam_path_id;

	/* config dcam path  */
	memset(&ch_desc, 0, sizeof(ch_desc));
	if(ch->dcam_path_id == 0 && module->cam_uinfo.is_4in1 == 1)
		ch_desc.is_loose = 0;
	else
		ch_desc.is_loose = module->cam_uinfo.sensor_if.if_spec.mipi.is_loose;
	ch_desc.is_4in1 = module->cam_uinfo.is_4in1;
	ch_desc.raw_cap = 1;
	ch_desc.endian.y_endian = ENDIAN_LITTLE;
	ret = dcam_ops->cfg_path(module->dcam_dev_handle,
			DCAM_PATH_CFG_BASE,
			ch->dcam_path_id, &ch_desc);

	ch_desc.input_size.w = proc_info->src_size.width;
	ch_desc.input_size.h = proc_info->src_size.height;
	ch_desc.input_trim.start_x = 0;
	ch_desc.input_trim.start_y = 0;
	ch_desc.input_trim.size_x = ch_desc.input_size.w;
	ch_desc.input_trim.size_y = ch_desc.input_size.h;
	ch_desc.output_size = ch_desc.input_size;
	ch_desc.priv_size_data = NULL;
	ret = dcam_ops->cfg_path(module->dcam_dev_handle,
			DCAM_PATH_CFG_SIZE,
			ch->dcam_path_id, &ch_desc);

	hw = grp->hw_info;
	if (hw->ip_dcam[module->dcam_idx]->lbuf_share_support
		&& hw->hw_ops.core_ops.lbuf_share_set)
		hw->hw_ops.core_ops.lbuf_share_set(module->dcam_idx,
			proc_info->src_size.width);

	/* specify isp context & path */
	init_param.is_high_fps = 0;/* raw capture + slow motion ?? */
	init_param.cam_id = module->idx;
	ret = isp_ops->get_context(module->isp_dev_handle, &init_param);
	if (ret < 0) {
		pr_err("fail to get isp context\n");
		goto fail_ispctx;
	}
	ctx_id = ret;
	isp_ops->set_callback(module->isp_dev_handle,
		ctx_id, isp_callback, module);

	/* config isp context base */
	memset(&ctx_desc, 0, sizeof(ctx_desc));
	ctx_desc.is_loose = module->cam_uinfo.sensor_if.if_spec.mipi.is_loose;
	ctx_desc.in_fmt = proc_info->src_format;
	ctx_desc.bayer_pattern = proc_info->src_pattern;
	ctx_desc.mode_ltm = MODE_LTM_OFF;
	ctx_desc.mode_3dnr = MODE_3DNR_OFF;
	ret = isp_ops->cfg_path(module->isp_dev_handle,
			ISP_PATH_CFG_CTX_BASE, ctx_id, 0, &ctx_desc);

	isp_path_id = ISP_SPATH_CP;
	ret = isp_ops->get_path(
		module->isp_dev_handle, ctx_id, isp_path_id);
	if (ret < 0) {
		pr_err("fail to get isp path %d from context %d\n",
			isp_path_id, ctx_id);
		goto fail_isppath;
	}
	ch->isp_path_id =
		(int32_t)((ctx_id << ISP_CTXID_OFFSET) | isp_path_id);
	pr_info("get isp path : 0x%x\n", ch->isp_path_id);

	memset(&isp_path_desc, 0, sizeof(isp_path_desc));
	isp_path_desc.out_fmt = IMG_PIX_FMT_NV21;
	isp_path_desc.endian.y_endian = ENDIAN_LITTLE;
	isp_path_desc.endian.uv_endian = ENDIAN_LITTLE;
	isp_path_desc.output_size.w = proc_info->dst_size.width;
	isp_path_desc.output_size.h = proc_info->dst_size.height;
	ret = isp_ops->cfg_path(module->isp_dev_handle,
			ISP_PATH_CFG_PATH_BASE,
			ctx_id, isp_path_id, &isp_path_desc);

	/* config isp input/path size */
	ctx_size.src.w = proc_info->src_size.width;
	ctx_size.src.h = proc_info->src_size.height;
	ctx_size.crop.start_x = 0;
	ctx_size.crop.start_y = 0;
	ctx_size.crop.size_x = ctx_size.src.w;
	ctx_size.crop.size_y = ctx_size.src.h;
	ret = isp_ops->cfg_path(module->isp_dev_handle,
			ISP_PATH_CFG_CTX_SIZE, ctx_id, 0, &ctx_size);

	path_trim.start_x = 0;
	path_trim.start_y = 0;
	path_trim.size_x = proc_info->src_size.width;
	path_trim.size_y = proc_info->src_size.height;
	ret = isp_ops->cfg_path(module->isp_dev_handle,
			ISP_PATH_CFG_PATH_SIZE,
			ctx_id, isp_path_id, &path_trim);

	ch->enable = 1;
	atomic_set(&module->state, CAM_CFG_CH);
	pr_info("done, dcam path %d, isp_path 0x%x\n",
		dcam_path_id, ch->isp_path_id);
	return 0;

fail_isppath:
	isp_ops->put_context(module->isp_dev_handle, ctx_id);
fail_ispctx:
	dcam_ops->put_path(module->dcam_dev_handle, ch->dcam_path_id);
	ch->dcam_path_id = -1;
	ch->isp_path_id = -1;
	ch->aux_dcam_path_id = -1;

	pr_err("fail to call pre raw proc\n");
	return ret;
}

static int raw_proc_post(
		struct camera_module *module,
		struct isp_raw_proc_info *proc_info)
{
	int ret = 0;
	uint32_t width;
	uint32_t height;
	uint32_t is_loose;
	size_t size;
	struct channel_context *ch;
	struct camera_frame *src_frame;
	struct camera_frame *mid_frame;
	struct camera_frame *dst_frame;
	struct dcam_pipe_dev *dev = NULL;

	pr_info("start\n");

	ch = &module->channel[CAM_CH_CAP];
	if (ch->enable == 0) {
		pr_err("fail to get channel enable state\n");
		return -EFAULT;
	}

	ret = dcam_ops->start(module->dcam_dev_handle, 0);
	if (ret < 0) {
		pr_err("fail to start dcam dev, ret %d\n", ret);
		return -EFAULT;
	}

	ret = dcam_ops->ioctl(module->dcam_dev_handle,
				DCAM_IOCTL_INIT_STATIS_Q, NULL);

	pr_info("src %d 0x%x, mid %d, 0x%x, dst %d, 0x%x\n",
		proc_info->fd_src, proc_info->src_offset,
		proc_info->fd_dst0, proc_info->dst0_offset,
		proc_info->fd_dst1, proc_info->dst1_offset);
	src_frame = get_empty_frame();
	src_frame->buf.type = CAM_BUF_USER;
	src_frame->buf.mfd[0] = proc_info->fd_src;
	src_frame->buf.offset[0] = proc_info->src_offset;
	src_frame->channel_id = ch->ch_id;
	src_frame->width = proc_info->src_size.width;
	src_frame->height = proc_info->src_size.height;
	src_frame->endian = proc_info->src_y_endian;
	src_frame->pattern = proc_info->src_pattern;
	ret = cambuf_get_ionbuf(&src_frame->buf);
	if (ret)
		goto src_fail;

	dst_frame = get_empty_frame();
	dst_frame->buf.type = CAM_BUF_USER;
	dst_frame->buf.mfd[0] = proc_info->fd_dst1;
	dst_frame->buf.offset[0] = proc_info->dst1_offset;
	dst_frame->channel_id = ch->ch_id;
	ret = cambuf_get_ionbuf(&dst_frame->buf);
	if (ret)
		goto dst_fail;

	dev = (struct dcam_pipe_dev *)module->dcam_dev_handle;
	if (module->grp->hw_info->prj_id == SHARKL3
		&& module->dcam_idx == DCAM_ID_1)
		dev->raw_fetch_num = 2;
	else
		dev->raw_fetch_num = 1;
	dev->raw_fetch_count = 0;

	mid_frame = get_empty_frame();
	mid_frame->channel_id = ch->ch_id;
	/* if user set this buffer, we use it for dcam output
	 * or else we will allocate one for it.
	 */
	if(ch->dcam_path_id == 0 && module->cam_uinfo.is_4in1 == 1)
		is_loose = 0;
	else
		is_loose = module->cam_uinfo.sensor_if.if_spec.mipi.is_loose;
	pr_info("day raw_proc_post is_loose %d", is_loose);
	if (proc_info->fd_dst0 > 0) {
		mid_frame->buf.type = CAM_BUF_USER;
		mid_frame->buf.mfd[0] = proc_info->fd_dst0;
		mid_frame->buf.offset[0] = proc_info->dst0_offset;
		ret = cambuf_get_ionbuf(&mid_frame->buf);
		if (ret)
			goto mid_fail;
	} else {
		width = proc_info->src_size.width;
		height = proc_info->src_size.height;
		if (module->cam_uinfo.dcam_slice_mode == CAM_OFFLINE_SLICE_SW) {
			width = width / module->cam_uinfo.slice_num;
			if (proc_info->dst_size.height > ISP_SLCIE_HEIGHT_MAX) {
				width *= 2;
			}
			width = ALIGN(width, 4);
		}

		//if(ch->dcam_path_id == 0 && module->cam_uinfo.is_4in1 == 1)
			//ch_desc.is_loose = 0;
		/* todo: accurate buffer size for formats other than mipi-raw*/
		if (proc_info->src_format == IMG_PIX_FMT_GREY)
			size = cal_sprd_raw_pitch(width, is_loose) * height;
		else
			size = width * height * 3;
		size = ALIGN(size, CAM_BUF_ALIGN_SIZE);
		ret = cambuf_alloc(&mid_frame->buf,
				size, 0, module->iommu_enable);
		if (ret)
			goto mid_fail;
	}

	ret = dcam_ops->cfg_path(module->dcam_dev_handle,
			DCAM_PATH_CFG_OUTPUT_BUF,
			ch->dcam_path_id, mid_frame);
	if (ret) {
		pr_err("fail to cfg dcam out buffer.\n");
		goto dcam_out_fail;
	}

	ret = isp_ops->cfg_path(module->isp_dev_handle,
			ISP_PATH_CFG_OUTPUT_BUF,
			ch->isp_path_id >> ISP_CTXID_OFFSET,
			ch->isp_path_id & ISP_PATHID_MASK, dst_frame);
	if (ret)
		pr_err("fail to cfg isp out buffer.\n");

	pr_info("raw proc, src %p, mid %p, dst %p\n",
		src_frame, mid_frame, dst_frame);
	camera_queue_init(&ch->share_buf_queue,
			CAM_SHARED_BUF_NUM, 0, put_k_frame);
	camera_queue_init(&module->frm_queue,
		CAM_FRAME_Q_LEN, 0, camera_put_empty_frame);
	module->cap_status = CAM_CAPTURE_RAWPROC;
	module->dcam_cap_status = DCAM_CAPTURE_START;
	atomic_set(&module->state, CAM_RUNNING);

	dcam_hwsim_extra(module->dcam_idx);
	isp_hwsim_extra(ch->isp_path_id >> ISP_CTXID_OFFSET);

	ret = dcam_ops->proc_frame(module->dcam_dev_handle, src_frame);
	if (ret)
		pr_err("fail to start dcam/isp for raw proc\n");

	atomic_set(&module->timeout_flag, 1);
	ret = sprd_start_timer(&module->cam_timer, CAMERA_TIMEOUT);

	return ret;

dcam_out_fail:
	if (mid_frame->buf.type == CAM_BUF_USER)
		cambuf_put_ionbuf(&mid_frame->buf);
	else
		cambuf_free(&mid_frame->buf);
mid_fail:
	put_empty_frame(mid_frame);
	cambuf_put_ionbuf(&dst_frame->buf);
dst_fail:
	put_empty_frame(dst_frame);
	cambuf_put_ionbuf(&src_frame->buf);
src_fail:
	put_empty_frame(src_frame);
	ret = dcam_ops->stop(module->dcam_dev_handle);
	pr_err("fail to call post raw proc\n");
	return ret;
}

static int img_ioctl_raw_proc(
			struct camera_module *module,
			unsigned long arg)
{
	int ret = 0;
	int error_state = 0;
	struct isp_raw_proc_info proc_info;
	uint32_t rps_info;

	ret = copy_from_user(&proc_info, (void __user *)arg,
				sizeof(struct isp_raw_proc_info));
	if (ret) {
		pr_err("fail to copy_from_user\n");
		return -EFAULT;
	}

	if (!module->dcam_dev_handle || !module->isp_dev_handle) {
		pr_err("fail to init hw resource.\n");
		return -EFAULT;
	}
	if (proc_info.scene == RAW_PROC_SCENE_HWSIM) {
		rps_info = 1;
		pr_info("hwsim\n");
		ret = dcam_ops->ioctl(module->dcam_dev_handle,
				DCAM_IOCTL_CFG_RPS, &rps_info);
		if (ret != 0) {
			pr_err("fail to config rps %d\n", ret);
			return -EFAULT;
		}
	}

	if ((proc_info.cmd == RAW_PROC_PRE) && (proc_info.scene == RAW_PROC_SCENE_RAWCAP)) {
		mutex_unlock(&module->lock);
		/* raw proc must wait for camera stream off and hw is idle */
		ret = wait_for_completion_interruptible(
				&module->streamoff_com);
		mutex_lock(&module->lock);
		if (ret != 0) {
			pr_err("fail to wait streamoff com %d\n", ret);
			return -EFAULT;
		}
	}

	if (proc_info.scene == RAW_PROC_SCENE_RAWCAP) {

		error_state = ((proc_info.cmd == RAW_PROC_PRE) &&
			(atomic_read(&module->state) != CAM_IDLE));
		error_state |= ((proc_info.cmd == RAW_PROC_POST) &&
			(atomic_read(&module->state) != CAM_CFG_CH));
		if (error_state) {
			pr_info("cam%d rawproc %d error state: %d\n",
					module->idx, proc_info.cmd,
					atomic_read(&module->state));
			return -EFAULT;
		}
	} else {
		pr_info("state[%d]\n", atomic_read(&module->state));
	}

	if (proc_info.cmd == RAW_PROC_PRE) {
		ret = raw_proc_pre(module, &proc_info);
	} else if (proc_info.cmd == RAW_PROC_POST) {
		ret = raw_proc_post(module, &proc_info);
	} else if (proc_info.cmd == RAW_PROC_DONE) {
		ret = raw_proc_done(module);
	} else {
		pr_err("fail to get correct cmd %d\n", proc_info.cmd);
		ret = -EINVAL;
	}
	return ret;
}



/* set addr for 4in1 raw which need remosaic
 */
static int img_ioctl_4in1_set_raw_addr(struct camera_module *module,
					unsigned long arg)
{
	int ret;
	enum dcam_id idx;
	struct sprd_img_parm param;
	struct channel_context *ch;
	struct camera_frame *pframe;
	int i;

	ret = copy_from_user(&param, (void __user *)arg,
				sizeof(struct sprd_img_parm));
	if (ret) {
		pr_err("fail to copy_from_user\n");
		return -EFAULT;
	}
	idx = module->idx;
	pr_debug("idx %d, channel_id %d, enable %d\n", idx,
		param.channel_id, module->channel[param.channel_id].enable);
	if ((param.channel_id >= CAM_CH_MAX) ||
		(param.buffer_count == 0) ||
		(module->channel[param.channel_id].enable == 0)) {
		pr_err("fail to get valid channel id %d. buf cnt %d\n",
				param.channel_id,  param.buffer_count);
		return -EFAULT;
	}
	pr_info("ch %d, buffer_count %d\n", param.channel_id,
		param.buffer_count);

	ch = &module->channel[param.channel_id];
	for (i = 0; i < param.buffer_count; i++) {
		pframe = get_empty_frame();
		pframe->buf.type = CAM_BUF_USER;
		pframe->buf.mfd[0] = param.fd_array[i];
		pframe->buf.addr_vir[0] = param.frame_addr_vir_array[i].y;
		pframe->buf.addr_vir[1] = param.frame_addr_vir_array[i].u;
		pframe->buf.addr_vir[2] = param.frame_addr_vir_array[i].v;
		pframe->channel_id = ch->ch_id;
		pframe->width = ch->ch_uinfo.src_size.w;
		pframe->height = ch->ch_uinfo.src_size.h;
		pr_debug("mfd %d, reserved %d\n", pframe->buf.mfd[0],
			param.is_reserved_buf);
		ret = cambuf_get_ionbuf(&pframe->buf);
		if (ret) {
			pr_err("fail to get ion buffer\n");
			put_empty_frame(pframe);
			ret = -EFAULT;
			break;
		}

		if (param.is_reserved_buf) {
			ch->reserved_buf_fd = pframe->buf.mfd[0];
			pframe->is_reserved = 1;
			ret = dcam_ops->cfg_path(module->dcam_dev_handle,
					DCAM_PATH_CFG_OUTPUT_RESERVED_BUF,
					ch->dcam_path_id, pframe);
		} else {
			ret = dcam_ops->cfg_path(module->dcam_dev_handle,
					DCAM_PATH_CFG_OUTPUT_BUF,
					ch->dcam_path_id, pframe);
		}

		if (ret) {
			pr_err("fail to set output buffer for ch%d.\n",
				ch->ch_id);
			cambuf_put_ionbuf(&pframe->buf);
			put_empty_frame(pframe);
			ret = -EFAULT;
			break;
		}
	}
	pr_info("exit, ret = %d\n", ret);

	return ret;
}

/* buffer set to kernel after remosaic
 */
static int img_ioctl_4in1_post_proc(struct camera_module *module,
					unsigned long arg)
{
	struct sprd_img_parm param;
	int ret = 0;
	int iommu_enable;
	struct channel_context *channel;
	struct camera_frame *pframe;
	int i;
	ktime_t sensor_time;
	struct dcam_pipe_dev *dev = NULL;
	uint32_t shutoff = 0;

	ret = copy_from_user(&param, (void __user *)arg,
				sizeof(struct sprd_img_parm));
	if (ret) {
		pr_err("fail to copy_from_user\n");
		return -EFAULT;
	}

	pr_info("E\n");
	/* about image data address
	 * fetch: from HAL, in param
	 * dcam out: alloc by kernel, share buf
	 */
	channel = &module->channel[CAM_CH_CAP];
	iommu_enable = module->iommu_enable;
	/* timestamp, reserved	([2]<<32)|[1]
	 * Attention: Only send back one time, maybe need some
	 * change when hal use another time
	 */
	sensor_time = param.reserved[2];
	sensor_time <<= 32;
	sensor_time |= param.reserved[1];
	/* get frame: 1:check id;2:check time;3:get first,4:get new */
	i = camera_queue_cnt(&module->remosaic_queue);
	while (i--) {
		pframe = camera_dequeue(&module->remosaic_queue);
		/* check frame id */
		if (pframe == NULL)
			break;
		if (pframe->fid == param.index)
			break;
		if (pframe->boot_sensor_time == sensor_time)
			break;
		camera_enqueue(&module->remosaic_queue, pframe);
		pframe = NULL;
	}
	if (pframe == NULL) {
		pr_info("Can't find frame in the queue, get new one\n");
		pframe = get_empty_frame();
		pframe->boot_sensor_time = sensor_time;
		pframe->sensor_time = ktime_to_timeval(ktime_sub(
			pframe->boot_sensor_time, ktime_sub(
			ktime_get_boottime(), ktime_get())));
		pframe->fid = param.index;
	}
	pframe->endian = ENDIAN_LITTLE;
	pframe->pattern = module->cam_uinfo.sensor_if.img_ptn;
	pframe->width = channel->ch_uinfo.src_size.w;
	pframe->height = channel->ch_uinfo.src_size.h;
	pframe->buf.type = CAM_BUF_USER;
	pframe->buf.mfd[0] = param.fd_array[0];
	pframe->buf.addr_vir[0] = param.frame_addr_vir_array[0].y;
	pframe->buf.addr_vir[1] = param.frame_addr_vir_array[0].u;
	pframe->buf.addr_vir[2] = param.frame_addr_vir_array[0].v;
	pframe->channel_id = channel->ch_id;

	ret = cambuf_get_ionbuf(&pframe->buf);
	if (ret) {
		put_empty_frame(pframe);
		return -EFAULT;
	}
	pr_info("frame[%d] fd %d addr_vir[0]=0x%lx iova[0]=0x%lx\n",
		pframe->fid, pframe->buf.mfd[0], pframe->buf.addr_vir[0],
		pframe->buf.iova[0]);

	dev = (struct dcam_pipe_dev *)module->dcam_dev_handle;
	/*stop full path & start bin path*/
	dev->hw->hw_ops.core_ops.binning_4in1_set(dev, 0);
	shutoff = 0;
	dcam_ops->cfg_path(dev, DCAM_PATH_CFG_SHUTOFF, DCAM_PATH_BIN, &shutoff);
	ret = dcam_ops->start(dev, 0);
	if (ret < 0) {
		pr_err("fail to start dcam dev, ret %d\n", ret);
		goto exit;
	}
	if (dev->hw->ip_dcam[module->dcam_idx]->lbuf_share_support
		&& dev->hw->hw_ops.core_ops.lbuf_share_set)
		dev->hw->hw_ops.core_ops.lbuf_share_set(module->dcam_idx,
			pframe->width);
	ret = dcam_ops->proc_frame(dev, pframe);

exit:
	return ret;
}

static int img_ioctl_get_path_rect(struct camera_module *module,
                        unsigned long arg)
{
	int ret = 0;
	struct sprd_img_path_rect parm;

	if (!module) {
		pr_err("fail to get valid param\n");
		return -EINVAL;
	}

	memset((void *)&parm, 0, sizeof(parm));
	ret = copy_from_user(&parm, (void __user *)arg,
				sizeof(struct sprd_img_path_rect));
	if (ret) {
		pr_err("fail to get user info ret %d\n", ret);
		return -EFAULT;
	}

	ret = dcam_ops->ioctl(module->dcam_dev_handle,
		DCAM_IOCTL_GET_PATH_RECT, &parm);
	pr_debug("TRIM rect info x %d y %d w %d h %d\n",
		parm.trim_valid_rect.x, parm.trim_valid_rect.y,
		parm.trim_valid_rect.w, parm.trim_valid_rect.h);
	pr_debug("AE rect info x %d y %d w %d h %d\n",
		parm.ae_valid_rect.x, parm.ae_valid_rect.y,
		parm.ae_valid_rect.w, parm.ae_valid_rect.h);
	pr_debug("AF rect info x %d y %d w %d h %d\n",
		parm.af_valid_rect.x, parm.af_valid_rect.y,
		parm.af_valid_rect.w, parm.af_valid_rect.h);

	ret = copy_to_user((void __user *)arg, &parm,
			sizeof(struct sprd_img_path_rect));
	if (ret) {
		ret = -EFAULT;
		pr_err("fail to copy to user\n");
		return ret;
	}

	return ret;
}

/* set which channel use hw 3dnr
 * if auto 3dnr, will be set when previewing
 */
static int ioctl_set_3dnr_mode(struct camera_module *module,
                        unsigned long arg)
{
	int ret = 0;
	struct sprd_img_3dnr_mode parm;
	struct channel_context *ch;
	uint32_t ch_id;

	if (!module) {
		pr_err("fail to get valid param\n");
		return -EINVAL;
	}

	memset((void *)&parm, 0, sizeof(parm));
	ret = copy_from_user(&parm, (void __user *)arg,
				sizeof(parm));
	if (ret) {
		pr_err("fail to get user info ret %d\n", ret);
		return -EFAULT;
	}
	ch_id = parm.channel_id;
	if (ch_id >= CAM_CH_MAX) {
		pr_err("fail to get channel id %d\n", ch_id);
		return -EFAULT;
	}
	ch = &module->channel[ch_id];
	pr_info("ch_id %d, need_3dnr %d\n", ch_id, parm.need_3dnr);

	/* dynamic set when auto 3dnr */
	if (module->auto_3dnr) {
		if (ch->uinfo_3dnr == parm.need_3dnr)
			return ret;

		ch->uinfo_3dnr = parm.need_3dnr;
		set_capture_3dnr(module, ch);

	} else {
		ch->uinfo_3dnr = parm.need_3dnr;
	}

	return ret;
}

/* set auto_3dnr enable bit to drv
 * 190614: hal set 1 if need, but not set 0(default 0)
 */
static int ioctl_set_auto_3dnr_mode(struct camera_module *module,
                        unsigned long arg)
{
	int ret = 0;
	struct sprd_img_auto_3dnr_mode parm;

	if (!module) {
		pr_err("fail to get valid param\n");
		return -EINVAL;
	}

	memset((void *)&parm, 0, sizeof(parm));
	ret = copy_from_user(&parm, (void __user *)arg,
				sizeof(parm));
	if (ret) {
		pr_err("fail to get user info ret %d\n", ret);
		return -EFAULT;
	}
	module->auto_3dnr = parm.auto_3dnr_enable;
	pr_info("auto_3dnr %d\n", module->auto_3dnr);

	return ret;
}

static int ioctl_get_capability(struct camera_module *module,
                        unsigned long arg)
{
	int ret = 0;
	struct sprd_img_size size = {0};

	if (!module) {
		pr_err("fail to get valid param\n");
		ret = -EINVAL;
		goto exit;
	}

	size.w = ISP_WIDTH_MAX;
	size.h = ISP_HEIGHT_MAX;
	ret = copy_to_user((void __user *)arg, &size,
				sizeof(struct sprd_img_size));
	if (unlikely(ret)) {
		pr_err("fail to get capability, ret %d\n", ret);
		ret = -EFAULT;
		goto exit;
	}

exit:
	return ret;
}

/*--------------- Core controlling interface end --------------- */



/* for user test isp/dcam/fd directly. */
int test_dcam(struct camera_module *module,
			struct dev_test_info *test_info)
{
	int ret = 0;
	int dcam_idx = 0;
	int iommu_enable;
	int path_id;
	size_t size;
	uint32_t is_loose = 0;
	struct channel_context *channel;
	struct camera_frame *pframe;
	struct camera_frame *user_frame;
	struct dcam_path_cfg_param ch_desc = { 0 };
	void *dcam;

	if (test_info->dev == 1)
		dcam_idx = DCAM_ID_0;
	else
		dcam_idx = DCAM_ID_1;

	pr_info("test dcam %d\n", dcam_idx);

	/* test dcam only */
	dcam = module->dcam_dev_handle;
	if (dcam == NULL) {
		dcam = dcam_if_get_dev(dcam_idx, module->grp->hw_info);
		if (IS_ERR_OR_NULL(dcam)) {
			pr_err("fail to get dcam%d\n", dcam_idx);
			ret = -EINVAL;
			goto exit;
		}
		ret = dcam_ops->open(dcam);
		if (ret) {
			dcam_if_put_dev(dcam);
			goto exit;
		}

		ret = dcam_ops->set_callback(dcam, dcam_callback, module);
		if (ret) {
			pr_err("fail to set cam%d callback for dcam.\n",
				dcam_idx);
			dcam_ops->close(dcam);
			dcam_if_put_dev(dcam);
			goto exit;
		}
		pr_info("dcam module open done: %p\n", dcam);
		module->dcam_dev_handle = dcam;
	}

	channel = &module->channel[0];
	if (dcam_ops->get_path) {
		path_id = DCAM_PATH_BIN;
		ret = dcam_ops->get_path(module->dcam_dev_handle,
					path_id);
		if (ret < 0) {
			pr_err("fail to get dcam full path\n");
			goto exit;
		} else {
			channel->dcam_path_id = path_id;
			pr_info("Get full path for dcam offline test.\n");
		}
	}

	if (channel->dcam_path_id >= 0) {
		/* no trim in DCAM full path for offline test. */
		ch_desc.is_raw = 0;
		ch_desc.is_loose = 0;
		ch_desc.frm_deci = 0;
		ch_desc.frm_skip = 0;
		ch_desc.endian.y_endian = ENDIAN_LITTLE;
		ch_desc.input_size.w = test_info->input_size.width;
		ch_desc.input_size.h = test_info->input_size.height;
		ch_desc.input_trim.size_x = ch_desc.input_size.w;
		ch_desc.input_trim.size_y = ch_desc.input_size.h;
		ch_desc.output_size = ch_desc.input_size;
		ch_desc.force_rds = 0;
		ch_desc.priv_size_data = NULL;
		ret = dcam_ops->cfg_path(module->dcam_dev_handle,
					DCAM_PATH_CFG_BASE,
					channel->dcam_path_id,
					&ch_desc);
		ret = dcam_ops->cfg_path(module->dcam_dev_handle,
					DCAM_PATH_CFG_SIZE,
					channel->dcam_path_id,
					&ch_desc);
	}

	iommu_enable = test_info->iommu_en;
	pframe = get_empty_frame();
	if (pframe) {
		pframe->channel_id = channel->ch_id;
		pframe->is_reserved = 0;
		pframe->fid = 0;
		pframe->width = ch_desc.input_size.w;
		pframe->height = ch_desc.input_size.h;
		is_loose = module->cam_uinfo.sensor_if.if_spec.mipi.is_loose;
		size = cal_sprd_raw_pitch(ch_desc.input_size.w, is_loose);
		size *= ch_desc.input_size.h;
		ret = cambuf_alloc(
				&pframe->buf, size,
				0, iommu_enable);
		if (ret) {
			pr_err("fail to alloc buffer.\n");
			put_empty_frame(pframe);
			goto nobuf;
		}
		ret = cambuf_kmap(&pframe->buf);
		if (ret) {
			pr_err("fail to kmap buffer.\n");
			cambuf_free(&pframe->buf);
			put_empty_frame(pframe);
			goto nobuf;
		}
	} else {
		pr_err("fail to get empty frame.\n");
		goto exit;
	}

	user_frame = get_empty_frame();
	if (user_frame) {
		user_frame->channel_id = channel->ch_id;
		user_frame->buf.type = CAM_BUF_USER;
		user_frame->buf.mfd[0] = test_info->inbuf_fd;
		cambuf_get_ionbuf(&user_frame->buf);
		pr_info("src buf kaddr %p.\n",
				(void *)user_frame->buf.addr_k[0]);
	} else {
		pr_err("fail to get empty frame.\n");
		goto exit;
	}

	pr_info("copy source image.\n");
	/* todo: user should alloc new buffer for output
	 * memcpy((void *)pframe->buf.addr_k[0],
	 * (void *)user_frame->buf.addr_k[0], size);
	 */

	ret = dcam_ops->cfg_path(module->dcam_dev_handle,
				DCAM_PATH_CFG_OUTPUT_BUF,
				channel->dcam_path_id, user_frame);

	camera_queue_init(&channel->share_buf_queue,
			CAM_SHARED_BUF_NUM, 0, put_k_frame);
	camera_queue_init(&module->frm_queue,
			CAM_FRAME_Q_LEN, 0, camera_put_empty_frame);

	atomic_set(&module->state, CAM_RUNNING);

	ret = dcam_ops->proc_frame(module->dcam_dev_handle, pframe);

	pr_info("start wait for DCAM callback.\n");
	ret = wait_for_completion_interruptible(&module->frm_com);
	pr_info("wait done.\n");
	user_frame = camera_dequeue(&module->frm_queue);

	cambuf_put_ionbuf(&user_frame->buf);
	put_empty_frame(user_frame);

	atomic_set(&module->state, CAM_IDLE);

	dcam_ops->put_path(module->dcam_dev_handle, channel->dcam_path_id);
	dcam_ops->close(module->dcam_dev_handle);

	camera_queue_clear(&module->frm_queue);
	camera_queue_clear(&channel->share_buf_queue);

	return ret;

nobuf:
	dcam_ops->put_path(module->dcam_dev_handle, channel->dcam_path_id);
	dcam_ops->close(module->dcam_dev_handle);
exit:
	return ret;
}

int test_isp(struct camera_module *module,
			struct dev_test_info *test_info)
{
	int ret = 0;
	int i;
	int iommu_enable;
	int ctx_id, path_id;
	int prop_0, prop_1;
	int double_ch = 0;
	size_t size = 0;
	uint32_t is_loose = 0;
	struct channel_context *channel = NULL;
	struct channel_context *channel_1 = NULL;
	struct camera_frame *pframe_in = NULL;
	struct camera_frame *pframe_out = NULL;
	struct camera_frame *pframe_out_1 = NULL;
	void *isp = NULL;
	struct isp_init_param init_param;

	isp = module->isp_dev_handle;
	if (isp == NULL) {
		isp = get_isp_pipe_dev();
		if (IS_ERR_OR_NULL(isp)) {
			pr_err("fail to get isp\n");
			module->isp_dev_handle = NULL;
			ret = -EINVAL;
			goto exit;
		}

		ret = isp_ops->open(isp, module->grp->hw_info);
		if (ret) {
			pr_err("faile to enable isp module.\n");
			put_isp_pipe_dev(isp);
			ret = -EINVAL;
			goto exit;
		}
		module->isp_dev_handle = isp;
		pr_info("isp module open done: %p\n", isp);
	}

	channel = &module->channel[0];
	channel_1 = &module->channel[1];

	prop_0 = test_info->prop & 0xf;
	if ((test_info->prop >> 8) != 0) {
		double_ch = 1;
		prop_1 = (test_info->prop >> 4) & 0xf;
		if (prop_0 == prop_1)
			double_ch = 0;
	}

	init_param.is_high_fps = 0;/* raw capture + slow motion ?? */
	init_param.cam_id = module->idx;
	ret = isp_ops->get_context(module->isp_dev_handle, &init_param);
	if (ret < 0) {
		pr_err("fail to get isp context\n");
	} else {
		ctx_id = ret;
		if (prop_0 <= PROP_CAP)
			path_id = ISP_SPATH_CP;
		else if (prop_0 == PROP_FD)
			path_id = ISP_SPATH_FD;
		else if (prop_0 == PROP_VIDEO)
			path_id = ISP_SPATH_VID;
		else
			path_id = ISP_SPATH_CP;

		ret = isp_ops->get_path(module->isp_dev_handle, ctx_id,
			path_id);
		if (ret < 0) {
			pr_err("fail to get isp path %d from context %d\n",
				path_id, ctx_id);
			goto exit;
		}
		channel->isp_path_id = (int32_t)((
			ctx_id << ISP_CTXID_OFFSET) | path_id);
		pr_info("get isp path : %d\n", channel->isp_path_id);
		ret = isp_ops->set_callback(module->isp_dev_handle,
					ctx_id, isp_callback, module);
		if (ret)
			pr_err("fail to set cam%d callback for isp.\n",
				module->idx);

		if (double_ch) {
			if (prop_1 <= PROP_CAP)
				path_id = ISP_SPATH_CP;
			else if (prop_1 == PROP_FD)
				path_id = ISP_SPATH_FD;
			else if (prop_1 == PROP_VIDEO)
				path_id = ISP_SPATH_VID;
			else
				path_id = ISP_SPATH_CP;

			ret = isp_ops->get_path(module->isp_dev_handle,
						ctx_id, path_id);
			if (ret < 0) {
				pr_err("fail to get isp path %d from ctx %d\n",
					path_id, ctx_id);
				goto exit;
			}
			channel_1->isp_path_id = (int32_t)((
				ctx_id << ISP_CTXID_OFFSET) | path_id);
			pr_info("get isp path : %d\n", channel_1->isp_path_id);
		}
	}

	if (channel->isp_path_id >= 0) {
		struct isp_ctx_base_desc ctx_desc;
		struct isp_path_base_desc path_desc;
		struct isp_ctx_size_desc ctx_size;
		struct img_trim path_trim;

		/* todo: cfg param to user setting. */
		ctx_desc.in_fmt = test_info->in_fmt;
		ctx_desc.bayer_pattern = COLOR_ORDER_GB;
		ctx_desc.mode_ltm = MODE_LTM_OFF;
		ctx_desc.mode_3dnr = MODE_3DNR_OFF;
		ret = isp_ops->cfg_path(module->isp_dev_handle,
				ISP_PATH_CFG_CTX_BASE,
				channel->isp_path_id >> ISP_CTXID_OFFSET, 0,
				&ctx_desc);

		ctx_size.src.w = test_info->input_size.width;
		ctx_size.src.h = test_info->input_size.height;
		ctx_size.crop.start_x = 0;
		ctx_size.crop.start_y = 0;
		ctx_size.crop.size_x = ctx_size.src.w;
		ctx_size.crop.size_y = ctx_size.src.h;
		ret = isp_ops->cfg_path(module->isp_dev_handle,
				ISP_PATH_CFG_CTX_SIZE,
				channel->isp_path_id >> ISP_CTXID_OFFSET, 0,
				&ctx_size);

		path_desc.out_fmt = test_info->out_fmt;
		path_desc.endian.y_endian = ENDIAN_LITTLE;
		path_desc.endian.uv_endian = ENDIAN_LITTLE;
		path_desc.output_size.w = test_info->output_size.width;
		path_desc.output_size.h = test_info->output_size.height;
		ret = isp_ops->cfg_path(module->isp_dev_handle,
				ISP_PATH_CFG_PATH_BASE,
				channel->isp_path_id >> ISP_CTXID_OFFSET,
				channel->isp_path_id & ISP_PATHID_MASK,
				&path_desc);

		if (double_ch && channel_1->isp_path_id >= 0)
			ret = isp_ops->cfg_path(module->isp_dev_handle,
				ISP_PATH_CFG_PATH_BASE,
				channel_1->isp_path_id >> ISP_CTXID_OFFSET,
				channel_1->isp_path_id & ISP_PATHID_MASK,
				&path_desc);

		path_trim.start_x = 0;
		path_trim.start_y = 0;
		path_trim.size_x = ctx_size.src.w;
		path_trim.size_y = ctx_size.src.h;
		ret = isp_ops->cfg_path(module->isp_dev_handle,
				ISP_PATH_CFG_PATH_SIZE,
				channel->isp_path_id >> ISP_CTXID_OFFSET,
				channel->isp_path_id & ISP_PATHID_MASK,
					&path_trim);

		if (double_ch && channel_1->isp_path_id >= 0)
			ret = isp_ops->cfg_path(module->isp_dev_handle,
				ISP_PATH_CFG_PATH_SIZE,
				channel_1->isp_path_id >> ISP_CTXID_OFFSET,
				channel_1->isp_path_id & ISP_PATHID_MASK,
					&path_trim);

	}

	iommu_enable = test_info->iommu_en;

	pframe_in = get_empty_frame();
	if (pframe_in) {
		pframe_in->buf.type = CAM_BUF_USER;
		pframe_in->buf.mfd[0] = test_info->inbuf_fd;
		pframe_in->channel_id = channel->ch_id;
		cambuf_get_ionbuf(&pframe_in->buf);
	}

	pframe_out = get_empty_frame();
	if (pframe_out) {
		pframe_out->buf.type = CAM_BUF_USER;
		pframe_out->buf.mfd[0] = test_info->outbuf_fd;
		pframe_out->channel_id = channel->ch_id;
		cambuf_get_ionbuf(&pframe_out->buf);
	} else {
		pr_err("fail to get empty frame\n");
		ret = -EINVAL;
		if (pframe_in->buf.type == CAM_BUF_USER)
			cambuf_put_ionbuf(&pframe_in->buf);
		else
			cambuf_free(&pframe_in->buf);
		put_empty_frame(pframe_in);
		put_empty_frame(pframe_out);
		goto nobuf;
	}

	ret = isp_ops->cfg_path(module->isp_dev_handle,
			ISP_PATH_CFG_OUTPUT_BUF,
			channel->isp_path_id >> ISP_CTXID_OFFSET,
			channel->isp_path_id & ISP_PATHID_MASK,
			pframe_out);

	if (double_ch && channel_1->isp_path_id >= 0) {
		pframe_out_1 = get_empty_frame();
		if (pframe_out_1) {
			pframe_out_1->channel_id = channel_1->ch_id;
			pframe_out_1->is_reserved = 0;
			pframe_out_1->fid = 0;
			is_loose = module->cam_uinfo.sensor_if.if_spec.mipi.is_loose;
			size = cal_sprd_raw_pitch(test_info->input_size.width, is_loose);
			size *= test_info->input_size.height;
			ret = cambuf_alloc(
					&pframe_out_1->buf, size,
					0, iommu_enable);
			if (ret) {
				pr_err("fail to alloc buffer.\n");
				if (pframe_in->buf.type == CAM_BUF_USER)
					cambuf_put_ionbuf(&pframe_in->buf);
				else
					cambuf_free(&pframe_in->buf);
				put_empty_frame(pframe_in);
				if (pframe_out->buf.type == CAM_BUF_USER)
					cambuf_put_ionbuf(&pframe_out->buf);
				else
					cambuf_free(&pframe_out->buf);
				put_empty_frame(pframe_out);
				put_empty_frame(pframe_out_1);
				goto nobuf;
			}
		}
		ret = isp_ops->cfg_path(module->isp_dev_handle,
				ISP_PATH_CFG_OUTPUT_BUF,
				channel_1->isp_path_id >> ISP_CTXID_OFFSET,
				channel_1->isp_path_id & ISP_PATHID_MASK,
				pframe_out_1);
	}

	camera_queue_init(&channel->share_buf_queue,
			CAM_SHARED_BUF_NUM, 0, put_k_frame);
	camera_queue_init(&module->frm_queue,
			CAM_FRAME_Q_LEN, 0, camera_put_empty_frame);

	atomic_set(&module->state, CAM_RUNNING);

	ret = isp_ops->proc_frame(module->isp_dev_handle,
			pframe_in, channel->isp_path_id >> ISP_CTXID_OFFSET);

	for (i = 0; i < (double_ch + 1); i++) {
		pr_info("start wait for ISP callback.\n");
		ret = wait_for_completion_interruptible(&module->frm_com);
		pr_info("wait done.\n");

		pframe_out = camera_dequeue(&module->frm_queue);
		pr_info("get ch %d dst frame %p. mfd %d\n",
			pframe_out->channel_id, pframe_out,
			pframe_out->buf.mfd[0]);
		if (pframe_out->buf.type == CAM_BUF_USER)
			cambuf_put_ionbuf(&pframe_out->buf);
		else
			cambuf_free(&pframe_out->buf);
		put_empty_frame(pframe_out);
	}

	camera_queue_clear(&module->frm_queue);
	pframe_in = camera_dequeue(&channel->share_buf_queue);
	if (pframe_in) {
		cambuf_put_ionbuf(&pframe_in->buf);
		put_empty_frame(pframe_in);
	}

	atomic_set(&module->state, CAM_IDLE);
nobuf:
	isp_ops->put_path(module->isp_dev_handle,
			channel->isp_path_id >> ISP_CTXID_OFFSET,
			channel->isp_path_id & ISP_PATHID_MASK);
	if (double_ch)
		isp_ops->put_path(module->isp_dev_handle,
				channel_1->isp_path_id >> ISP_CTXID_OFFSET,
				channel_1->isp_path_id & ISP_PATHID_MASK);
	isp_ops->put_context(module->isp_dev_handle,
			channel->isp_path_id >>	ISP_CTXID_OFFSET);
exit:
	pr_info("done. ret: %d\n", ret);
	return ret;
}

int ioctl_test_dev(struct camera_module *module, unsigned long arg)
{
	int ret = 0;
	struct sprd_img_parm param;
	struct dev_test_info *test_info = (struct dev_test_info *)&param;

	ret = copy_from_user(&param, (void __user *)arg,
				sizeof(struct sprd_img_parm));
	if (ret) {
		pr_err("fail to copy_from_user\n");
		return -EFAULT;
	}

	if (test_info->dev == 0) {
		ret = test_isp(module, test_info);
		goto exit;
	}
	ret = test_dcam(module, test_info);

exit:
	if (ret >= 0)
		ret = copy_to_user((void __user *)arg, &param,
				sizeof(struct sprd_img_parm));
	pr_info("done. ret: %d\n", ret);
	return ret;
}

static int img_ioctl_path_pause(struct camera_module *module, unsigned long arg)
{
	int ret = 0;
	uint32_t dcam_path_state = DCAM_PATH_PAUSE;
	struct dcam_pipe_dev *dev = NULL;

	pr_debug("pause %d with dcam %d not running\n",
			module->idx, module->dcam_idx);
	dev = (struct dcam_pipe_dev *)module->dcam_dev_handle;
	module->path_state = dcam_path_state;
	if (atomic_read(&module->state) == CAM_RUNNING) {
		mutex_lock(&module->lock);
		if (module->channel[CAM_CH_CAP].enable)
			dcam_ops->cfg_path(dev, DCAM_PATH_CFG_STATE,
				DCAM_PATH_FULL, &dcam_path_state);
		mutex_unlock(&module->lock);
	}

	return ret;
}

static int img_ioctl_path_resume(struct camera_module *module, unsigned long arg)
{
	int ret = 0;
	uint32_t dcam_path_state = DCAM_PATH_RESUME;
	struct dcam_pipe_dev *dev = NULL;

	pr_debug("resume %d with dcam %d not running\n",
			module->idx, module->dcam_idx);
	dev = (struct dcam_pipe_dev *)module->dcam_dev_handle;
	module->path_state = dcam_path_state;
	if (atomic_read(&module->state) == CAM_RUNNING) {
		mutex_lock(&module->lock);
		if (module->channel[CAM_CH_CAP].enable)
			dcam_ops->cfg_path(dev, DCAM_PATH_CFG_STATE,
				DCAM_PATH_FULL, &dcam_path_state);
		mutex_unlock(&module->lock);
	}

	return ret;
}

static struct cam_ioctl_cmd ioctl_cmds_table[] = {
	[_IOC_NR(SPRD_IMG_IO_SET_MODE)]		= {SPRD_IMG_IO_SET_MODE,	img_ioctl_set_mode},
	[_IOC_NR(SPRD_IMG_IO_SET_CAP_SKIP_NUM)]	= {SPRD_IMG_IO_SET_CAP_SKIP_NUM,	img_ioctl_set_cap_skip_num},
	[_IOC_NR(SPRD_IMG_IO_SET_SENSOR_SIZE)]	= {SPRD_IMG_IO_SET_SENSOR_SIZE,	img_ioctl_set_sensor_size},
	[_IOC_NR(SPRD_IMG_IO_SET_SENSOR_TRIM)]	= {SPRD_IMG_IO_SET_SENSOR_TRIM,	img_ioctl_set_sensor_trim},
	[_IOC_NR(SPRD_IMG_IO_SET_FRM_ID_BASE)]	= {SPRD_IMG_IO_SET_FRM_ID_BASE,	img_ioctl_set_frame_id_base},
	[_IOC_NR(SPRD_IMG_IO_SET_CROP)]		= {SPRD_IMG_IO_SET_CROP,	img_ioctl_set_crop},
	[_IOC_NR(SPRD_IMG_IO_SET_FLASH)]	= {SPRD_IMG_IO_SET_FLASH,	img_ioctl_set_flash},
	[_IOC_NR(SPRD_IMG_IO_SET_OUTPUT_SIZE)]	= {SPRD_IMG_IO_SET_OUTPUT_SIZE,	img_ioctl_set_output_size},
	[_IOC_NR(SPRD_IMG_IO_SET_ZOOM_MODE)]	= {SPRD_IMG_IO_SET_ZOOM_MODE,	img_ioctl_set_zoom_mode},
	[_IOC_NR(SPRD_IMG_IO_SET_SENSOR_IF)]	= {SPRD_IMG_IO_SET_SENSOR_IF,	img_ioctl_set_sensor_if},
	[_IOC_NR(SPRD_IMG_IO_SET_FRAME_ADDR)]	= {SPRD_IMG_IO_SET_FRAME_ADDR,	img_ioctl_set_frame_addr},
	[_IOC_NR(SPRD_IMG_IO_PATH_FRM_DECI)]	= {SPRD_IMG_IO_PATH_FRM_DECI,	img_ioctl_set_frm_deci},
	[_IOC_NR(SPRD_IMG_IO_PATH_PAUSE)]	= {SPRD_IMG_IO_PATH_PAUSE,	img_ioctl_path_pause},
	[_IOC_NR(SPRD_IMG_IO_PATH_RESUME)]	= {SPRD_IMG_IO_PATH_RESUME,	img_ioctl_path_resume},
	[_IOC_NR(SPRD_IMG_IO_STREAM_ON)]	= {SPRD_IMG_IO_STREAM_ON,	img_ioctl_stream_on},
	[_IOC_NR(SPRD_IMG_IO_STREAM_OFF)]	= {SPRD_IMG_IO_STREAM_OFF,	img_ioctl_stream_off},
	[_IOC_NR(SPRD_IMG_IO_GET_FMT)]		= {SPRD_IMG_IO_GET_FMT,		img_ioctl_get_fmt},
	[_IOC_NR(SPRD_IMG_IO_GET_CH_ID)]	= {SPRD_IMG_IO_GET_CH_ID,	img_ioctl_get_ch_id},
	[_IOC_NR(SPRD_IMG_IO_GET_TIME)]		= {SPRD_IMG_IO_GET_TIME,	img_ioctl_get_time},
	[_IOC_NR(SPRD_IMG_IO_CHECK_FMT)]	= {SPRD_IMG_IO_CHECK_FMT,	img_ioctl_check_fmt},
	[_IOC_NR(SPRD_IMG_IO_SET_SHRINK)]	= {SPRD_IMG_IO_SET_SHRINK,	img_ioctl_set_shrink},
	[_IOC_NR(SPRD_IMG_IO_SET_FREQ_FLAG)]	= {SPRD_IMG_IO_SET_FREQ_FLAG,	NULL},
	[_IOC_NR(SPRD_IMG_IO_CFG_FLASH)]	= {SPRD_IMG_IO_CFG_FLASH,	img_ioctl_cfg_flash},
	[_IOC_NR(SPRD_IMG_IO_PDAF_CONTROL)]	= {SPRD_IMG_IO_PDAF_CONTROL,	NULL},
	[_IOC_NR(SPRD_IMG_IO_GET_IOMMU_STATUS)]	= {SPRD_IMG_IO_GET_IOMMU_STATUS,	img_ioctl_get_iommu_status},
	[_IOC_NR(SPRD_IMG_IO_DISABLE_MODE)]	= {SPRD_IMG_IO_DISABLE_MODE,	NULL},
	[_IOC_NR(SPRD_IMG_IO_ENABLE_MODE)]	= {SPRD_IMG_IO_ENABLE_MODE,	NULL},
	[_IOC_NR(SPRD_IMG_IO_START_CAPTURE)]	= {SPRD_IMG_IO_START_CAPTURE,	img_ioctl_start_capture},
	[_IOC_NR(SPRD_IMG_IO_STOP_CAPTURE)]	= {SPRD_IMG_IO_STOP_CAPTURE,	img_ioctl_stop_capture},
	[_IOC_NR(SPRD_IMG_IO_SET_PATH_SKIP_NUM)]	= {SPRD_IMG_IO_SET_PATH_SKIP_NUM,	NULL},
	[_IOC_NR(SPRD_IMG_IO_SBS_MODE)]		= {SPRD_IMG_IO_SBS_MODE,	NULL},
	[_IOC_NR(SPRD_IMG_IO_DCAM_PATH_SIZE)]	= {SPRD_IMG_IO_DCAM_PATH_SIZE,	img_ioctl_dcam_path_size},
	[_IOC_NR(SPRD_IMG_IO_SET_SENSOR_MAX_SIZE)]	= {SPRD_IMG_IO_SET_SENSOR_MAX_SIZE,	img_ioctl_set_sensor_max_size},
	[_IOC_NR(SPRD_ISP_IO_IRQ)]		= {SPRD_ISP_IO_IRQ,		NULL},
	[_IOC_NR(SPRD_ISP_IO_READ)]		= {SPRD_ISP_IO_READ,		NULL},
	[_IOC_NR(SPRD_ISP_IO_WRITE)]		= {SPRD_ISP_IO_WRITE,		NULL},
	[_IOC_NR(SPRD_ISP_IO_RST)]		= {SPRD_ISP_IO_RST,		NULL},
	[_IOC_NR(SPRD_ISP_IO_STOP)]		= {SPRD_ISP_IO_STOP,		NULL},
	[_IOC_NR(SPRD_ISP_IO_INT)]		= {SPRD_ISP_IO_INT,		NULL},
	[_IOC_NR(SPRD_ISP_IO_SET_STATIS_BUF)]	= {SPRD_ISP_IO_SET_STATIS_BUF,	img_ioctl_set_statis_buf},
	[_IOC_NR(SPRD_ISP_IO_CFG_PARAM)]	= {SPRD_ISP_IO_CFG_PARAM,	img_ioctl_cfg_param},
	[_IOC_NR(SPRD_ISP_REG_READ)]		= {SPRD_ISP_REG_READ,		NULL},
	[_IOC_NR(SPRD_ISP_IO_POST_3DNR)]	= {SPRD_ISP_IO_POST_3DNR,	NULL},
	[_IOC_NR(SPRD_STATIS_IO_CFG_PARAM)]	= {SPRD_STATIS_IO_CFG_PARAM,	NULL},
	[_IOC_NR(SPRD_ISP_IO_RAW_CAP)]		= {SPRD_ISP_IO_RAW_CAP,		img_ioctl_raw_proc},

	[_IOC_NR(SPRD_IMG_IO_GET_DCAM_RES)]	= {SPRD_IMG_IO_GET_DCAM_RES,	img_ioctl_get_cam_res},
	[_IOC_NR(SPRD_IMG_IO_PUT_DCAM_RES)]	= {SPRD_IMG_IO_PUT_DCAM_RES,	img_ioctl_put_cam_res},

	[_IOC_NR(SPRD_ISP_IO_SET_PULSE_LINE)]	= {SPRD_ISP_IO_SET_PULSE_LINE,	NULL},
	[_IOC_NR(SPRD_ISP_IO_CFG_START)]	= {SPRD_ISP_IO_CFG_START,	img_ioctl_cfg_start},
	[_IOC_NR(SPRD_ISP_IO_POST_YNR)]		= {SPRD_ISP_IO_POST_YNR,	NULL},
	[_IOC_NR(SPRD_ISP_IO_SET_NEXT_VCM_POS)]	= {SPRD_ISP_IO_SET_NEXT_VCM_POS,	NULL},
	[_IOC_NR(SPRD_ISP_IO_SET_VCM_LOG)]	= {SPRD_ISP_IO_SET_VCM_LOG,	NULL},
	[_IOC_NR(SPRD_IMG_IO_SET_3DNR)]		= {SPRD_IMG_IO_SET_3DNR,	NULL},
	[_IOC_NR(SPRD_IMG_IO_SET_FUNCTION_MODE)]	= {SPRD_IMG_IO_SET_FUNCTION_MODE,	img_ioctl_set_function_mode},
	[_IOC_NR(SPRD_IMG_IO_GET_FLASH_INFO)]	= {SPRD_IMG_IO_GET_FLASH_INFO,	img_ioctl_get_flash},
	[_IOC_NR(SPRD_ISP_IO_MASK_3A)]		= {SPRD_ISP_IO_MASK_3A,		NULL},
	[_IOC_NR(SPRD_IMG_IO_EBD_CONTROL)]		= {SPRD_IMG_IO_EBD_CONTROL,	img_ioctl_ebd_control},
	[_IOC_NR(SPRD_IMG_IO_SET_4IN1_ADDR)]	= {SPRD_IMG_IO_SET_4IN1_ADDR,	img_ioctl_4in1_set_raw_addr},
	[_IOC_NR(SPRD_IMG_IO_4IN1_POST_PROC)]	= {SPRD_IMG_IO_4IN1_POST_PROC,	img_ioctl_4in1_post_proc},
	//[_IOC_NR(SPRD_IMG_IO_PATH_PAUSE)]	= {SPRD_IMG_IO_PATH_PAUSE,	ioctl_test_dev},
	[_IOC_NR(SPRD_IMG_IO_SET_CAM_SECURITY)]   = {SPRD_IMG_IO_SET_CAM_SECURITY,  img_ioctl_set_cam_security},
	[_IOC_NR(SPRD_IMG_IO_GET_PATH_RECT)]             = {SPRD_IMG_IO_GET_PATH_RECT,   img_ioctl_get_path_rect},
	[_IOC_NR(SPRD_IMG_IO_SET_3DNR_MODE)]    = {SPRD_IMG_IO_SET_3DNR_MODE,   ioctl_set_3dnr_mode},
	[_IOC_NR(SPRD_IMG_IO_SET_AUTO_3DNR_MODE)] = {SPRD_IMG_IO_SET_AUTO_3DNR_MODE, ioctl_set_auto_3dnr_mode},
	[_IOC_NR(SPRD_IMG_IO_CAPABILITY)] = {SPRD_IMG_IO_CAPABILITY, ioctl_get_capability},
};


static long sprd_img_ioctl(struct file *file, unsigned int cmd,
				unsigned long arg)
{
	int ret = 0;
	int locked = 0;
	struct camera_module *module = NULL;
	struct cam_ioctl_cmd *ioctl_cmd_p = NULL;
	int nr = _IOC_NR(cmd);

	pr_debug("cam ioctl, cmd:0x%x, cmdnum %d\n", cmd, nr);

	module = (struct camera_module *)file->private_data;
	if (!module) {
		pr_err("fail to get valid input ptr\n");
		return -EFAULT;
	}

	if (unlikely(!(nr >= 0 && nr < ARRAY_SIZE(ioctl_cmds_table)))) {
		pr_info("invalid cmd: 0x%xn", cmd);
		return -EINVAL;
	}

	ioctl_cmd_p = &ioctl_cmds_table[nr];
	if (unlikely((ioctl_cmd_p->cmd != cmd) ||
			(ioctl_cmd_p->cmd_proc == NULL))) {
		pr_debug("unsupported cmd_k: 0x%x, cmd_u: 0x%x, nr: %d\n",
			ioctl_cmd_p->cmd, cmd, nr);
		return 0;
	}

	/* There is race condition under several cases during stream/off
	 * Take care of lock use
	 */
	if (atomic_read(&module->state) != CAM_RUNNING) {
		mutex_lock(&module->lock);
		locked = 1;
	}

	ret = ioctl_cmd_p->cmd_proc(module, arg);
	if (ret) {
		pr_err("fail to ioctl cmd:%x, nr:%d, func %ps\n",
			cmd, nr, ioctl_cmd_p->cmd_proc);
		goto exit;
	}

	pr_debug("cam id:%d, %ps, done!\n",
			module->idx, ioctl_cmd_p->cmd_proc);
exit:
	if (locked)
		mutex_unlock(&module->lock);
	return ret;
}

static ssize_t sprd_img_read(struct file *file, char __user *u_data,
				size_t cnt, loff_t *cnt_ret)
{
	int ret = 0;
	int i = 0;
	int superzoom_val = 0;
	struct sprd_img_read_op read_op;
	struct camera_module *module = NULL;
	struct camera_frame *pframe;
	struct channel_context *pchannel;
	struct sprd_img_path_capability *cap;
	struct cam_hw_info *hw = NULL;

	module = (struct camera_module *)file->private_data;
	if (!module) {
		pr_err("fail to get valid input ptr\n");
		return -EFAULT;
	}

	if (cnt != sizeof(struct sprd_img_read_op)) {
		pr_err("fail to img read, cnt %zd read_op %d\n", cnt,
			(int32_t)sizeof(struct sprd_img_read_op));
		return -EIO;
	}

	if (copy_from_user(&read_op, (void __user *)u_data, cnt)) {
		pr_err("fail to get user info\n");
		return -EFAULT;
	}

	pr_debug("cam %d read cmd %d\n", module->idx, read_op.cmd);

	switch (read_op.cmd) {
	case SPRD_IMG_GET_SCALE_CAP:
		hw = module->grp->hw_info;
		for (i = 0; i < DCAM_ID_MAX; i++) {
			if (hw->ip_dcam[i]->superzoom_support) {
				superzoom_val = 1;
				break;
			}
		}

		if (superzoom_val)
			read_op.parm.reserved[1] = 10;
		else
			read_op.parm.reserved[1] = 4;

		read_op.parm.reserved[0] = 4672;
		read_op.parm.reserved[2] = 4672;
		pr_debug("line threshold %d, sc factor %d, scaling %d.\n",
				read_op.parm.reserved[0],
				read_op.parm.reserved[1],
				read_op.parm.reserved[2]);
		break;
	case SPRD_IMG_GET_FRM_BUFFER:
rewait:
		memset(&read_op, 0, sizeof(struct sprd_img_read_op));
		while (1) {
			ret = wait_for_completion_interruptible(
				&module->frm_com);
			if (ret == 0) {
				break;
			} else if (ret == -ERESTARTSYS) {
				read_op.evt = IMG_SYS_BUSY;
				ret = 0;
				goto read_end;
			} else {
				pr_err("read frame buf, fail to down, %d\n",
					ret);
				return -EPERM;
			}
		}

		pchannel = NULL;
		pframe = camera_dequeue(&module->frm_queue);

		if (!pframe) {
			/* any exception happens or user trigger exit. */
			pr_info("No valid frame buffer. tx stop.\n");
			read_op.evt = IMG_TX_STOP;
		} else if (pframe->evt == IMG_TX_DONE) {
			atomic_set(&module->timeout_flag, 0);
			if ((pframe->irq_type == CAMERA_IRQ_4IN1_DONE) ||
				(pframe->irq_type == CAMERA_IRQ_IMG)) {
				cambuf_put_ionbuf(&pframe->buf);
				pchannel = &module->channel[pframe->channel_id];
				if (pframe->buf.mfd[0] ==
					pchannel->reserved_buf_fd) {
					pr_info("get output buffer with reserved frame fd %d\n",
						pchannel->reserved_buf_fd);
					put_empty_frame(pframe);
					goto rewait;
				}
				read_op.parm.frame.channel_id = pframe->channel_id;
				read_op.parm.frame.index = pchannel->frm_base_id;
				read_op.parm.frame.frm_base_id = pchannel->frm_base_id;
				read_op.parm.frame.img_fmt = pchannel->ch_uinfo.dst_fmt;
			}
			read_op.evt = pframe->evt;
			read_op.parm.frame.irq_type = pframe->irq_type;
			read_op.parm.frame.irq_property = pframe->irq_property;
			read_op.parm.frame.length = pframe->width;
			read_op.parm.frame.height = pframe->height;
			read_op.parm.frame.real_index = pframe->fid;
			read_op.parm.frame.frame_id = pframe->fid;
			/*
			 * read_op.parm.frame.sec = pframe->time.tv_sec;
			 * read_op.parm.frame.usec = pframe->time.tv_usec;
			 * read_op.parm.frame.monoboottime = pframe->boot_time;
			 */
			/* use SOF time instead of ISP time for better accuracy */
			read_op.parm.frame.sec = pframe->sensor_time.tv_sec;
			read_op.parm.frame.usec = pframe->sensor_time.tv_usec;
			read_op.parm.frame.monoboottime = pframe->boot_sensor_time;
			read_op.parm.frame.yaddr_vir = (uint32_t)pframe->buf.addr_vir[0];
			read_op.parm.frame.uaddr_vir = (uint32_t)pframe->buf.addr_vir[1];
			read_op.parm.frame.vaddr_vir = (uint32_t)pframe->buf.addr_vir[2];
			read_op.parm.frame.mfd = pframe->buf.mfd[0];
			read_op.parm.frame.yaddr = pframe->buf.offset[0];
			read_op.parm.frame.uaddr = pframe->buf.offset[1];
			read_op.parm.frame.vaddr = pframe->buf.offset[2];

			/* for statis buffer address below. */
			read_op.parm.frame.addr_offset = pframe->buf.offset[0];
			if (pframe->irq_type == CAMERA_IRQ_STATIS)
				read_op.parm.frame.zoom_ratio = pframe->zoom_ratio;
			else
				read_op.parm.frame.zoom_ratio = module->zoom_ratio;
		} else {
			struct cam_hw_info *hw = module->grp->hw_info;

			pr_err("fail to get correct event %d\n", pframe->evt);
			if (hw == NULL) {
				pr_err("fail to get hw ops.\n");
				return -EFAULT;
			}
			csi_api_reg_trace();
			hw->hw_ops.core_ops.reg_trace(module->dcam_idx,
				ABNORMAL_REG_TRACE);
			read_op.evt = pframe->evt;
			read_op.parm.frame.irq_type = pframe->irq_type;
			read_op.parm.frame.irq_property = pframe->irq_property;
		}

		pr_debug("read frame, evt 0x%x irq %d ch 0x%x index 0x%x mfd %d\n",
				read_op.evt,
				read_op.parm.frame.irq_type,
				read_op.parm.frame.channel_id,
				read_op.parm.frame.real_index,
				read_op.parm.frame.mfd);

		if (pframe) {
			if (pframe->irq_type != CAMERA_IRQ_4IN1_DONE) {
				put_empty_frame(pframe);
				break;
			}
			/* 4in1 report frame for remosaic
			 * save frame for 4in1_post IOCTL
			 */
			ret = camera_enqueue(&module->remosaic_queue, pframe);
			if (!ret)
				break;
			/* fail, give back */
			put_empty_frame(pframe);
			ret = 0;
		}

		break;

	case SPRD_IMG_GET_PATH_CAP:
		pr_debug("get path capbility\n");
		cap = &read_op.parm.capability;
		memset(cap, 0, sizeof(struct sprd_img_path_capability));
		cap->support_3dnr_mode = 1;
		cap->support_4in1 = 1;
		cap->count = 4;
		cap->path_info[CAM_CH_RAW].support_yuv = 0;
		cap->path_info[CAM_CH_RAW].support_raw = 1;
		cap->path_info[CAM_CH_RAW].support_jpeg = 0;
		cap->path_info[CAM_CH_RAW].support_scaling = 0;
		cap->path_info[CAM_CH_RAW].support_trim = 1;
		cap->path_info[CAM_CH_RAW].is_scaleing_path = 0;
		cap->path_info[CAM_CH_PRE].line_buf = ISP_WIDTH_MAX;
		cap->path_info[CAM_CH_PRE].support_yuv = 1;
		cap->path_info[CAM_CH_PRE].support_raw = 0;
		cap->path_info[CAM_CH_PRE].support_jpeg = 0;
		cap->path_info[CAM_CH_PRE].support_scaling = 1;
		cap->path_info[CAM_CH_PRE].support_trim = 1;
		cap->path_info[CAM_CH_PRE].is_scaleing_path = 0;
		cap->path_info[CAM_CH_CAP].line_buf = ISP_WIDTH_MAX;
		cap->path_info[CAM_CH_CAP].support_yuv = 1;
		cap->path_info[CAM_CH_CAP].support_raw = 0;
		cap->path_info[CAM_CH_CAP].support_jpeg = 0;
		cap->path_info[CAM_CH_CAP].support_scaling = 1;
		cap->path_info[CAM_CH_CAP].support_trim = 1;
		cap->path_info[CAM_CH_CAP].is_scaleing_path = 0;
		cap->path_info[CAM_CH_VID].line_buf = ISP_WIDTH_MAX;
		cap->path_info[CAM_CH_VID].support_yuv = 1;
		cap->path_info[CAM_CH_VID].support_raw = 0;
		cap->path_info[CAM_CH_VID].support_jpeg = 0;
		cap->path_info[CAM_CH_VID].support_scaling = 1;
		cap->path_info[CAM_CH_VID].support_trim = 1;
		cap->path_info[CAM_CH_VID].is_scaleing_path = 0;
		break;

	default:
		pr_err("fail to get valid cmd\n");
		return -EINVAL;
	}

read_end:
	if (copy_to_user((void __user *)u_data, &read_op, cnt))
		ret = -EFAULT;

	if (ret)
		cnt = ret;

	return cnt;
}

static ssize_t sprd_img_write(struct file *file, const char __user *u_data,
				size_t cnt, loff_t *cnt_ret)
{
	int ret = 0;
	struct sprd_img_write_op write_op;
	struct camera_module *module = NULL;

	module = (struct camera_module *)file->private_data;
	if (!module) {
		pr_err("fail to get valid input ptr\n");
		return -EFAULT;
	}

	if (cnt != sizeof(struct sprd_img_write_op)) {
		pr_err("fail to write, cnt %zd  write_op %d\n", cnt,
				(uint32_t)sizeof(struct sprd_img_write_op));
		return -EIO;
	}

	if (copy_from_user(&write_op, (void __user *)u_data, cnt)) {
		pr_err("fail to get user info\n");
		return -EFAULT;
	}

	switch (write_op.cmd) {
	case SPRD_IMG_STOP_DCAM:
		pr_info("user stop camera %d\n", module->idx);
		complete(&module->frm_com);
		break;

	default:
		pr_err("fail to get write cmd %d\n", write_op.cmd);
		break;
	}

	ret =  copy_to_user((void __user *)u_data, &write_op, cnt);
	if (ret) {
		pr_err("fail to get user info\n");
		cnt = ret;
		return -EFAULT;
	}

	return cnt;
}


static int sprd_img_open(struct inode *node, struct file *file)
{
	int ret = 0;
	unsigned long flag;
	struct camera_module *module = NULL;
	struct camera_group *grp = NULL;
	struct miscdevice *md = file->private_data;
	uint32_t i, idx, count = 0;

	grp = md->this_device->platform_data;
	count = grp->dcam_count;

	if (count == 0 || count > CAM_COUNT) {
		pr_err("fail to get valid dts configured dcam count\n");
		return -ENODEV;
	}

	if (atomic_inc_return(&grp->camera_opened) > count) {
		pr_err("fail to open camera, all %d cameras opened already.", count);
		atomic_dec(&grp->camera_opened);
		return -EMFILE;
	}

	pr_info("sprd_img: the camera opened count %d\n",
			atomic_read(&grp->camera_opened));

	pr_info("camca: camsec_mode = %d\n", grp->camsec_cfg.camsec_mode);

	spin_lock_irqsave(&grp->module_lock, flag);
	for (i = 0, idx = count; i < count; i++) {
		if ((grp->module_used & (1 << i)) == 0) {
			if (grp->module[i] != NULL) {
				pr_err("fail to get null module, un-release camera module:  %p, idx %d\n",
						grp->module[i], i);
				spin_unlock_irqrestore(&grp->module_lock, flag);
				ret = -EMFILE;
				goto exit;
			}
			idx = i;
			grp->module_used |= (1 << i);
			break;
		}
	}
	spin_unlock_irqrestore(&grp->module_lock, flag);

	if (idx == count) {
		pr_err("fail to get available camera module.\n");
		ret = -EMFILE;
		goto exit;
	}

	pr_debug("kzalloc. size of module %x, group %x\n",
		(int)sizeof(struct camera_module),
		(int) sizeof(struct camera_group));

	module = vzalloc(sizeof(struct camera_module));
	if (!module) {
		pr_err("fail to alloc camera module %d\n", idx);
		ret = -ENOMEM;
		goto alloc_fail;
	}

	module->idx = idx;
	ret = camera_module_init(module);
	if (ret) {
		pr_err("fail to init camera module %d\n", idx);
		ret = -ENOMEM;
		goto init_fail;
	}

	if (atomic_read(&grp->camera_opened) == 1) {
		isp_ops = get_isp_ops();
		dcam_ops = dcam_if_get_ops();
		flash_ops = get_flash_ops();
		if (isp_ops == NULL || dcam_ops == NULL) {
			pr_err("fail to get isp ops %p, dcam ops %p\n",
					isp_ops, dcam_ops);
			goto init_fail;
		}
		/* should check all needed interface here. */

		if (grp->hw_info && grp->hw_info->soc_dcam->pdev)
			ret = cambuf_reg_iommudev(
				&grp->hw_info->soc_dcam->pdev->dev,
				CAM_IOMMUDEV_DCAM);
		if (grp->hw_info && grp->hw_info->soc_isp->pdev)
			ret = cambuf_reg_iommudev(
				&grp->hw_info->soc_isp->pdev->dev,
				CAM_IOMMUDEV_ISP);

		g_empty_frm_q = &grp->empty_frm_q;
		camera_queue_init(g_empty_frm_q,
				CAM_EMP_Q_LEN_MAX, 0,
				free_empty_frame);

		pr_info("init %p\n", g_empty_frm_q);
	}

	module->idx = idx;
	module->grp = grp;
	grp->module[idx] = module;
	file->private_data = (void *)module;

	pr_info("sprd_img: open end! %d, %p, %p, grp %p\n",
		idx, module, grp->module[idx], grp);

	return 0;

init_fail:
	vfree(module);

alloc_fail:
	spin_lock_irqsave(&grp->module_lock, flag);
	grp->module_used &= ~(1 << idx);
	grp->module[idx] = NULL;
	spin_unlock_irqrestore(&grp->module_lock, flag);

exit:
	atomic_dec(&grp->camera_opened);

	pr_err("fail to open camera %d\n", ret);
	return ret;
}

/* sprd_img_release may be called for all state.
 * if release is called,
 * all other system calls in this file should be returned before.
 * state may be (RUNNING / IDLE / INIT).
 */
static int sprd_img_release(struct inode *node, struct file *file)
{
	int ret = 0;
	int idx = 0;
	unsigned long flag;
	struct camera_group *group = NULL;
	struct camera_module *module;
	struct dcam_pipe_dev *dcam_dev = NULL;
	struct isp_pipe_dev *isp_dev = NULL;

	pr_info("sprd_img: cam release start.\n");

	module = (struct camera_module *)file->private_data;
	if (!module || !module->grp) {
		pr_err("fail to get valid input ptr\n");
		return -EFAULT;
	}

	group = module->grp;
	idx = module->idx;

	if (module->grp->camsec_cfg.camsec_mode  != SEC_UNABLE) {
		bool ret = 0;

		module->grp->camsec_cfg.camsec_mode = SEC_UNABLE;
		ret = camca_security_set(&module->grp->camsec_cfg);

		pr_info("camca :camsec_mode%d, ret %d\n",
				module->grp->camsec_cfg.camsec_mode, ret);
	}

	pr_info("cam %d, state %d\n", idx,
		atomic_read(&module->state));
	pr_info("used: %d, module %p, %p, grp %p\n",
		group->module_used, module, group->module[idx], group);

	spin_lock_irqsave(&group->module_lock, flag);
	if (((group->module_used & (1 << idx)) == 0) ||
		(group->module[idx] != module)) {
		pr_err("fail to release camera %d. used:%x, module:%p\n",
					idx, group->module_used, module);
		spin_unlock_irqrestore(&group->module_lock, flag);
		return -EFAULT;
	}
	spin_unlock_irqrestore(&group->module_lock, flag);

	ret = img_ioctl_stream_off(module, 0L);

	if (atomic_read(&module->state) == CAM_IDLE) {
		module->attach_sensor_id = -1;

		if (module->workqueue) {
			destroy_workqueue(module->workqueue);
			module->workqueue  = NULL;
		}

		dcam_dev = module->dcam_dev_handle;
		isp_dev = module->isp_dev_handle;

		if (dcam_dev) {
			pr_info("force close dcam %p\n", dcam_dev);
			dcam_ops->close(dcam_dev);
			dcam_if_put_dev(dcam_dev);
			module->dcam_dev_handle = NULL;
		}

		if (isp_dev) {
			pr_info("force close isp %p\n", isp_dev);
			isp_ops->close(isp_dev);
			put_isp_pipe_dev(isp_dev);
			module->isp_dev_handle = NULL;
		}
	}
	camera_module_deinit(module);

	spin_lock_irqsave(&group->module_lock, flag);
	group->module_used &= ~(1 << idx);
	group->module[idx] = NULL;
	spin_unlock_irqrestore(&group->module_lock, flag);

	vfree(module);
	file->private_data = NULL;

	if (atomic_dec_return(&group->camera_opened) == 0) {

		cambuf_unreg_iommudev(CAM_IOMMUDEV_DCAM);
		cambuf_unreg_iommudev(CAM_IOMMUDEV_ISP);

		pr_info("release %p\n", g_empty_frm_q);

		/* g_leak_debug_cnt should be 0 after clr, or else memory leak.
		 */
		ret = camera_queue_clear(g_empty_frm_q);
		g_empty_frm_q = NULL;

		ret = mdbg_check();

		dcam_ops = NULL;
		isp_ops = NULL;
	}

	pr_info("sprd_img: cam %d release end.\n", idx);

	return ret;
}


static const struct file_operations image_fops = {
	.open = sprd_img_open,
	.unlocked_ioctl = sprd_img_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = compat_sprd_img_ioctl,
#endif
	.release = sprd_img_release,
	.read = sprd_img_read,
	.write = sprd_img_write,
};

static struct miscdevice image_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = IMG_DEVICE_NAME,
	.fops = &image_fops,
};

static int sprd_cam_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct camera_group *group = NULL;

	if (!pdev) {
		pr_err("fail to get valid input ptr\n");
		return -EFAULT;
	}

	pr_info("Start camera img probe\n");
	group = kzalloc(sizeof(struct camera_group), GFP_KERNEL);
	if (group == NULL) {
		pr_err("fail to alloc memory\n");
		return -ENOMEM;
	}

	ret = misc_register(&image_dev);
	if (ret) {
		pr_err("fail to register misc devices, ret %d\n", ret);
		kfree(group);
		return -EACCES;
	}

	image_dev.this_device->of_node = pdev->dev.of_node;
	image_dev.this_device->platform_data = (void *)group;
	group->md = &image_dev;
	group->pdev = pdev;
	group->hw_info = (struct cam_hw_info *)
		of_device_get_match_data(&pdev->dev);
	if (!group->hw_info) {
		pr_err("fail to get hw_info\n");
		goto probe_pw_fail;
	}
	atomic_set(&group->camera_opened, 0);
	spin_lock_init(&group->module_lock);
	spin_lock_init(&group->rawproc_lock);

	pr_info("sprd img probe pdev name %s\n", pdev->name);
	pr_info("sprd dcam dev name %s\n", pdev->dev.init_name);
	ret = dcam_if_parse_dt(pdev, group->hw_info, &group->dcam_count);
	if (ret) {
		pr_err("fail to parse dcam dts\n");
		goto probe_pw_fail;
	}

	pr_info("sprd isp dev name %s\n", pdev->dev.init_name);
	ret = sprd_isp_parse_dt(pdev->dev.of_node, group->hw_info,
		&group->isp_count);
	if (ret) {
		pr_err("fail to parse isp dts\n");
		goto probe_pw_fail;
	}

	/* for get ta status
	 * group->ca_conn  = cam_ca_connect();
	 */
	if (group->ca_conn)
		pr_info("cam ca-ta unconnect\n");

	group->debugger.hw = group->hw_info;
	ret = cam_debugfs_init(&group->debugger);
	if (ret)
		pr_err("fail to init cam debugfs\n");

	return 0;

probe_pw_fail:
	misc_deregister(&image_dev);
	kfree(group);

	return ret;
}

static int sprd_cam_remove(struct platform_device *pdev)
{
	struct camera_group *group = NULL;

	if (!pdev) {
		pr_err("fail to get valid input ptr\n");
		return -EFAULT;
	}

	group = image_dev.this_device->platform_data;
	if (group) {
		if (group->ca_conn)
			cam_ca_disconnect();
		kfree(group);
		image_dev.this_device->platform_data = NULL;
	}
	misc_deregister(&image_dev);

	return 0;
}

static const struct of_device_id sprd_cam_of_match[] = {
	#if defined (PROJ_SHARKL3)
	{ .compatible = "sprd,sharkl3-cam", .data = &sharkl3_hw_info},
	#elif defined (PROJ_SHARKL5PRO)
	{ .compatible = "sprd,sharkl5pro-cam", .data = &sharkl5pro_hw_info},
	#endif
	{ },
};

static struct platform_driver sprd_img_driver = {
	.probe = sprd_cam_probe,
	.remove = sprd_cam_remove,
	.driver = {
		.name = IMG_DEVICE_NAME,
		.of_match_table = of_match_ptr(sprd_cam_of_match),
	},
};

module_platform_driver(sprd_img_driver);

MODULE_DESCRIPTION("SPRD CAM Driver");
MODULE_AUTHOR("Multimedia_Camera@SPRD");
MODULE_LICENSE("GPL");
