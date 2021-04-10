/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
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

#include "sprd_dispc.h"

#define DISPC_BRIGHTNESS           (0x00 << 16)
#define DISPC_CONTRAST             (0x100 << 0)
#define DISPC_OFFSET_U             (0x80 << 16)
#define DISPC_SATURATION_U         (0x100 << 0)
#define DISPC_OFFSET_V             (0x80 << 16)
#define DISPC_SATURATION_V         (0x100 << 0)

typedef struct {
	uint32_t addr[4];
	uint32_t ctrl;
	uint32_t size;
	uint32_t pitch;
	uint32_t pos;
	uint32_t alpha;
	uint32_t ck;
	uint32_t pallete;
	uint32_t crop_start;
} reg_layer_t;

typedef struct {
	uint32_t dpu_version;
	uint32_t dpu_ctrl;
	uint32_t dpu_size;
	uint32_t dpu_rstn;
	uint32_t dpu_secure;
	uint32_t dpu_qos;
	uint32_t reserved_0x0018;
	uint32_t bg_color;
	reg_layer_t layers[6];
	uint32_t wb_base_addr;
	uint32_t wb_ctrl;
	uint32_t wb_pitch;
	uint32_t reserved_0x014c;
	uint32_t y2r_ctrl;
	uint32_t y2r_y_param;
	uint32_t y2r_u_param;
	uint32_t y2r_v_param;
	uint32_t dpu_int_en;
	uint32_t dpu_int_clr;
	uint32_t dpu_int_sts;
	uint32_t dpu_int_raw;
	uint32_t dpi_ctrl;
	uint32_t dpi_h_timing;
	uint32_t dpi_v_timing;
	uint32_t dpi_sts0;
	uint32_t dpi_sts1;
	uint32_t dpu_sts0;
	uint32_t dpu_sts1;
	uint32_t dpu_sts2;
	uint32_t dpu_sts3;
	uint32_t dpu_sts4;
	uint32_t dpu_sts5;
	uint32_t dpu_checksum_en;
	uint32_t dpu_checksum0_start_pos;
	uint32_t dpu_checksum0_end_pos;
	uint32_t dpu_checksum1_start_pos;
	uint32_t dpu_checksum1_end_pos;
	uint32_t dpu_checksum0_result;
	uint32_t dpu_checksum1_result;
} dpu_reg_t;


enum {
	DPU_LAYER_FORMAT_YUV422,
	DPU_LAYER_FORMAT_YUV420,
	DPU_LAYER_FORMAT_ARGB888,
	DPU_LAYER_FORMAT_RGB565,
	DPU_LAYER_FORMAT_AFBC,
	DPU_LAYER_FORMAT_MAX_TYPES,
};

static bool evt_update;
static bool evt_stop;
static int wb_en;
static int max_vsync_count;
static int vsync_count;
static struct sprd_adf_hwlayer *wb_layer;

static void dpu_clean(struct dispc_context *ctx);
static void dpu_write_back(struct dispc_context *ctx, int enable);
static void dpu_layer(struct dispc_context *ctx,
		    struct sprd_adf_hwlayer *hwlayer);

static int32_t dpu_wait_update_done(struct dispc_context *ctx);

static u32 dpu_get_version(struct dispc_context *ctx)
{
	return 0x0100;
}

#if 0
static void writeback_update_handler(struct work_struct *data)
{
	int ret;
	struct dispc_context *ctx =
		container_of(data, struct dispc_context, wb_work);
	dpu_reg_t *reg = (dpu_reg_t *)ctx->base;

	ret = down_trylock(&ctx->refresh_lock);
	if (ret != 1) {
		reg->dpu_ctrl |= BIT(5);
		dpu_wait_update_done(ctx);
		up(&ctx->refresh_lock);
	} else
		pr_debug("cannot acquire lock for wb_lock\n");
}
#endif

static u32 dpu_isr(struct dispc_context *ctx)
{
	dpu_reg_t *reg = (dpu_reg_t *)ctx->base;
	u32 reg_val;

	if (!reg) {
		pr_err("invalid reg\n");
		return 0;
	}

	reg_val = reg->dpu_int_sts;
	reg->dpu_int_clr = reg_val;

	/*disable err interrupt */
	if (reg_val & DISPC_INT_ERR_MASK) {
		reg->dpu_int_en &= ~DISPC_INT_ERR_MASK;
	}

	/*dpu update done isr */
	if (reg_val & DISPC_INT_UPDATE_DONE_MASK) {
		evt_update = true;
		wake_up_interruptible_all(&ctx->wait_queue);
	}

	/*dpu vsync isr */
	if (reg_val & DISPC_INT_DPI_VSYNC_MASK) {
		/*write back feature*/
		if (vsync_count == max_vsync_count && wb_en)
			dpu_write_back(ctx, true);
			vsync_count++;
	}

	/* dpu stop done isr */
	if (reg_val & DISPC_INT_DONE_MASK) {
		ctx->is_stopped = true;
		evt_stop = true;
		wake_up_interruptible_all(&ctx->wait_queue);
	}

	/* dpu write back done isr */
	if (reg_val & DISPC_INT_WB_DONE_MASK) {
		wb_en = false;
		if (vsync_count > max_vsync_count) {
			dpu_clean(ctx);
			dpu_layer(ctx, wb_layer);
			reg_val |= DISPC_INT_FENCE_SIGNAL_REQUEST;
		}
		dpu_write_back(ctx, false);
	}

	/* dpu write back error isr */
	if (reg_val & DISPC_INT_WB_FAIL_MASK) {
		pr_err("dpu write back fail\n");
		/*give a new chance to write back*/
		wb_en = true;
		vsync_count = 0;
	}

	return reg_val;
}

static int32_t dpu_wait_stop_done(struct dispc_context *ctx)
{
	int rc;

	/* if this function was called more than once without */
	/* calling dpu_run() in the middle, return directly */
	if (ctx->is_stopped && (!evt_stop)) {
		pr_info("dpu has already stopped!\n");
		return 0;
	}

	/*wait for stop done interrupt*/
	rc = wait_event_interruptible_timeout(ctx->wait_queue, evt_stop,
					       msecs_to_jiffies(500));
	evt_stop = false;

	if (!rc) {
		/* time out */
		pr_err("dpu wait for stop done time out!\n");
		ctx->is_stopped = true;
		return -1;
	}

	return 0;
}

static int32_t dpu_wait_update_done(struct dispc_context *ctx)
{
	int rc;
	dpu_reg_t *reg = (dpu_reg_t *)ctx->base;

	/*wait for reg update done interrupt*/
	rc = wait_event_interruptible_timeout(ctx->wait_queue,
			reg->dpu_int_sts & DISPC_INT_UPDATE_DONE_MASK,
			msecs_to_jiffies(500));
	reg->dpu_int_clr = DISPC_INT_UPDATE_DONE_MASK;
	evt_update = false;

	if (!rc) {
		/* time out */
		pr_err("dpu wait for reg update done time out!\n");
		return -1;
	}

	return 0;
}

static void dpu_stop(struct dispc_context *ctx)
{
	dpu_reg_t *reg = (dpu_reg_t *)ctx->base;

	if (!reg)
		return;

	if (ctx->if_type == SPRD_DISPC_IF_DPI)
		reg->dpu_ctrl |= BIT(1);

	dpu_wait_stop_done(ctx);
	pr_info("dpu stop\n");
}

static void dpu_run(struct dispc_context *ctx)
{
	dpu_reg_t *reg = (dpu_reg_t *)ctx->base;

	if (!reg)
		return;

	if (ctx->if_type == SPRD_DISPC_IF_DPI) {
		if (ctx->is_stopped) {
			/* set update mode with SW only */
			reg->dpu_ctrl |= BIT(4);

			/* update regs to shadow */
			reg->dpu_ctrl |= BIT(5);

			/* this delay is needed for registers update */
			udelay(10);

			/* start refresh */
			reg->dpu_ctrl |= BIT(0);

			/* set update mode with SW and VSync */
			reg->dpu_ctrl &= ~BIT(4);

			evt_update = false;

			ctx->is_stopped = false;

			pr_info("dpu run\n");
		} else {
			/*dpi register update trigger*/
			reg->dpu_ctrl |= BIT(5);

			/*make sure all the regs are updated to the shadow*/
			dpu_wait_update_done(ctx);
		}

		/* if the underflow err was disabled in isr, re-enable it */
		reg->dpu_int_en |= DISPC_INT_ERR_MASK;

	} else if (ctx->if_type == SPRD_DISPC_IF_EDPI) {
		/* make sure the dpu is in stop status, because shadow regs */
		/* can only be updated in the rising edge of DISPC_RUN bit */
		dpu_wait_stop_done(ctx);

		/* start refresh */
		reg->dpu_ctrl |= BIT(0);

		ctx->is_stopped = false;
	}
}

#if 0
static int dpu_write_back_config(struct dispc_context *ctx)
{
	int ret;
	static int need_config = 1;
	struct panel_info *panel = ctx->panel;
	u32 wb_addr_v;
	struct sprd_dispc *dispc =
		(struct sprd_dispc *)container_of(ctx, struct sprd_dispc, ctx);
	size_t logo_size = ALIGN(panel->width, 16) * panel->height * 4;

	if (!need_config) {
		pr_debug("write back info has configed\n");
		return 0;
	}

	wb_en = 0;
	max_vsync_count = 0;
	vsync_count = 0;
	ret = sprd_dispc_wb_buf_alloc(dispc, ION_HEAP_ID_MASK_FB,
					&logo_size, &wb_addr_v);
	if (!ret) {
		wb_layer = devm_kmalloc(&dispc->dev,
					     sizeof(*wb_layer),
					     GFP_KERNEL);
		if (!wb_layer) {
			/* write back fail*/
			max_vsync_count = 0;
			pr_err("cannot use write back\n");
			return -1;
		}

		memset(wb_layer, 0, sizeof(struct sprd_adf_hwlayer));
		wb_layer->hwlayer_id = 1;
		wb_layer->interface_id = 0;
		wb_layer->n_planes = 1;
		wb_layer->iova_plane[0] = wb_addr_v;
		wb_layer->pitch[0] = ALIGN(panel->width, 16) * 4;
		wb_layer->alpha = 0xff;
		wb_layer->format = DRM_FORMAT_RGBA8888;
		wb_layer->compression = 0;
		wb_layer->dst_w = panel->width;
		wb_layer->dst_h = panel->height;

		/*disable write back feature*/
		max_vsync_count = 3;
	}

	need_config = 0;
	return 0;
}
#endif

static int dpu_init(struct dispc_context *ctx)
{
	dpu_reg_t *reg = (dpu_reg_t *)ctx->base;
	struct panel_info *panel = ctx->panel;
	uint32_t size;

	if (reg == NULL) {
		pr_err("dpu base address is null!");
		return -1;
	}

	if (panel == NULL) {
		pr_err("ctx->panel is null!");
		return -1;
	}

	/* set bg color */
	reg->bg_color = 0;

	/* enable dithering */
	reg->dpu_ctrl |= BIT(6);

	/* enable DISPC Power Control */
	reg->dpu_ctrl |= BIT(7);

	/* clear update down register*/
	reg->dpu_int_clr |= BIT(4);

	/* set dpu output size */
	size = (panel->width & 0xffff) | ((panel->height) << 16);
	reg->dpu_size = size;
	reg->dpu_qos = (14 << 12)|(6 << 8)|(14 << 4)|(11 << 0);
	reg->y2r_ctrl = 1;
	reg->y2r_y_param = DISPC_BRIGHTNESS | DISPC_CONTRAST;
	reg->y2r_u_param = DISPC_OFFSET_U | DISPC_SATURATION_U;
	reg->y2r_v_param = DISPC_OFFSET_V | DISPC_SATURATION_V;
//	dpu_write_back_config(ctx);
//	INIT_WORK(&ctx->wb_work, writeback_update_handler);

	return 0;
}

static void dpu_uninit(struct dispc_context *ctx)
{
	dpu_reg_t *reg = (dpu_reg_t *)ctx->base;

	if (!reg)
		return;

	reg->dpu_int_en = 0;
	reg->dpu_int_clr = 0xff;
}

static uint32_t dpu_img_ctrl(u32 format, u32 blending, u32 compression)
{
	int reg_val = 0;

	/*IMG or OSD layer enable */
	reg_val |= BIT(0);

	switch (format) {
	case DRM_FORMAT_RGBA8888:
	case DRM_FORMAT_RGBX8888:
		/* rb switch */
		reg_val |= BIT(15);
	case DRM_FORMAT_BGRA8888:
		reg_val |= SPRD_IMG_DATA_ENDIAN_B3B2B1B0 << 8;
		if (compression)
			reg_val |= (DPU_LAYER_FORMAT_AFBC << 4);
		else
		/* ABGR */
			reg_val |= (DPU_LAYER_FORMAT_ARGB888 << 4);
		break;
		/* rb switch */
	case DRM_FORMAT_ABGR8888:
		reg_val |= BIT(15);
	case DRM_FORMAT_ARGB8888:
		reg_val |= (DPU_LAYER_FORMAT_ARGB888 << 4);
		break;
	case DRM_FORMAT_BGR888:
		/* rb switch */
		reg_val |= BIT(15);
	case DRM_FORMAT_RGB888:
		pr_err("sharkle not support rgb888 format\n");
		break;
	case DRM_FORMAT_BGR565:
		/* rb switch */
		reg_val |= BIT(15);
	case DRM_FORMAT_RGB565:
		/* rgb565 */
		reg_val |= (DPU_LAYER_FORMAT_RGB565 << 4);
		/* B2B3B0B1 */
		reg_val |= (SPRD_IMG_DATA_ENDIAN_B0B1B2B3 << 8);
		break;
	case DRM_FORMAT_NV12:
		/*2-Lane: Yuv420 */
		reg_val |= DPU_LAYER_FORMAT_YUV420 << 4;
		/*Y endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B0B1B2B3 << 8;
		reg_val &= ~BIT(15);
		/*UV endian */
		break;
	case DRM_FORMAT_NV21:
		/*2-Lane: Yuv420 */
		reg_val |= DPU_LAYER_FORMAT_YUV420 << 4;
		/*Y endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B0B1B2B3 << 8;
		/*UV endian */
		reg_val |= BIT(15);
		break;
	case DRM_FORMAT_NV16:
		/*2-Lane: Yuv422 */
		reg_val |= DPU_LAYER_FORMAT_YUV422 << 4;
		/*Y endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B3B2B1B0 << 8;
		/*UV endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B3B2B1B0 << 10;
		break;
	default:
		pr_err("Invalid format 0x%x\n", format);
		break;
	}

	switch (blending) {
	case HWC_BLENDING_NONE:
		/*don't do blending, maybe rgbx*/
		/* alpha mode select  - block alpha */
		reg_val |= BIT(2);
		break;
	case HWC_BLENDING_COVERAGE:
		/*Normal mode*/
		reg_val &= (~BIT(16));
		break;
	case HWC_BLENDING_PREMULT:
		/*Pre-mult mode*/
		reg_val |= BIT(16);
		break;
	default:
		/* alpha mode select  - block alpha */
		reg_val |= BIT(2);
		break;
	}

	return reg_val;
}

static void dpu_layer(struct dispc_context *ctx,
		    struct sprd_adf_hwlayer *hwlayer)
{
	dpu_reg_t *reg = (dpu_reg_t *)ctx->base;
	reg_layer_t *layer;
	int size;
	int offset;
	int wd;
	int i;

	if (!reg)
		return;
	layer = &reg->layers[hwlayer->hwlayer_id];
	size = (hwlayer->dst_w & 0xffff) | ((hwlayer->dst_h) << 16);
	offset = (hwlayer->dst_x & 0xffff) | ((hwlayer->dst_y) << 16);

	if (adf_format_is_rgb(hwlayer->format))
		wd = adf_format_bpp(hwlayer->format) / 8;
	else
		wd = adf_format_plane_cpp(hwlayer->format, 0);

	for (i = 0; i < hwlayer->n_planes; i++) {
		if (hwlayer->iova_plane[i] % 16)
			pr_err("layer addr[%d] is not 16 bytes align, it's 0x%08x\n",
					i, hwlayer->iova_plane[i]);
		layer->addr[i] = hwlayer->iova_plane[i] - 0x80000000;
	}

	layer->pos = offset;
	layer->size = size;
	layer->crop_start = (hwlayer->start_y << 16) | hwlayer->start_x;
	layer->alpha = hwlayer->alpha;
	layer->pitch = hwlayer->pitch[0] / wd;
	layer->ctrl = dpu_img_ctrl(hwlayer->format, hwlayer->blending,
		hwlayer->compression);
}

static void dpu_clean(struct dispc_context *ctx)
{
	int i;
	dpu_reg_t *reg = (dpu_reg_t *)ctx->base;

	for (i = 0; i < 6; i++)
		reg->layers[i].ctrl = 0;
}

static void dpu_flip(struct dispc_context *ctx,
			struct sprd_restruct_config *config)
{
	int i;
	struct sprd_adf_hwlayer *hwlayer;

	vsync_count = 0;
	if (max_vsync_count && (config->number_hwlayer > 1))
		wb_en = true;
	else
		wb_en = false;

	dpu_clean(ctx);

	for (i = 0; i < config->number_hwlayer; i++) {
		hwlayer = &config->hwlayers[i];
		dpu_layer(ctx, hwlayer);
	}
}

static void dpu_dpi_init(struct dispc_context *ctx)
{
	dpu_reg_t *reg = (dpu_reg_t *)ctx->base;
	struct panel_info *panel = ctx->panel;
	struct rgb_timing *rgb;
	uint32_t reg_val = 0;
	uint32_t int_mask = 0;
	uint8_t bus_width;

	if (!reg || !panel)
		return;

	/*dpi bits */
	switch (panel->bpp) {
	case 16:
		bus_width = 0;
		break;
	case 18:
		bus_width = 1;
		break;
	case 24:
		bus_width = 2;
		break;
	default:
		bus_width = 2;
		break;
	}

	if (ctx->if_type == SPRD_DISPC_IF_DPI) {
		/*use dpi as interface */
		reg->dpu_ctrl &= ~(BIT(1) | BIT(2));

		/*h sync pol */
		if (panel->h_sync_pol == SPRD_POLARITY_NEG)
			reg_val |= BIT(0);

		/*v sync pol */
		if (panel->v_sync_pol == SPRD_POLARITY_NEG)
			reg_val |= BIT(1);

		/*de sync pol */
		if (panel->de_pol == SPRD_POLARITY_NEG)
			reg_val |= BIT(2);

		/* bus width */
		reg_val |= bus_width << 6;

		reg->dpi_ctrl = reg_val;

		rgb = &panel->rgb_timing;
		/* set dpi timing */
		reg->dpi_h_timing = (rgb->hsync << 0) |
				(rgb->hbp << 8) |
				(rgb->hfp << 20);
		reg->dpi_v_timing = (rgb->vsync << 0) |
				(rgb->vbp << 8) |
				(rgb->vfp << 20);

		/*enable dpu update done INT */
		int_mask |= DISPC_INT_UPDATE_DONE_MASK;
		/* enable dpu DONE  INT */
		int_mask |= DISPC_INT_DONE_MASK;
		/* enable dispc dpi vsync */
		int_mask |= DISPC_INT_DPI_VSYNC_MASK;
		/* enable underflow err INT */
		int_mask |= DISPC_INT_ERR_MASK;

		int_mask |= DISPC_INT_WB_DONE_MASK;

		int_mask |= DISPC_INT_WB_FAIL_MASK;

		reg->dpu_int_en = int_mask;

	} else if (ctx->if_type == SPRD_DISPC_IF_EDPI) {
		/*use edpi as interface */
		reg->dpu_ctrl |= BIT(2);

		/*te pol */
		if (panel->te_pol == SPRD_POLARITY_NEG)
			reg_val |= BIT(9);

		/*use external te */
		reg_val |= BIT(10);

		/*enable te */
		reg_val |= BIT(8);

		/* bus width */
		reg_val |= bus_width << 6;

		reg->dpi_ctrl = reg_val;

		/* enable dpu DONE  INT */
		int_mask |= DISPC_INT_DONE_MASK;
		/* enable dpu TE  INT for edpi*/
		int_mask |= DISPC_INT_TE_MASK;

		reg->dpu_int_en = int_mask;
	}

}

static void dpu_write_back(struct dispc_context *ctx, int enable)
{
	dpu_reg_t *reg = (dpu_reg_t *)ctx->base;
	struct panel_info *panel = ctx->panel;

	reg->wb_base_addr = (u32)wb_layer->iova_plane[0];
	reg->wb_pitch = panel->width;

	if (enable)
		reg->wb_ctrl = 1;
	else
		reg->wb_ctrl = 0;

	 schedule_work(&ctx->wb_work);
}

static struct dispc_core_ops dpu_lite_r1p0_ops = {
	.version = dpu_get_version,
	.init = dpu_init,
	.uninit = dpu_uninit,
	.run = dpu_run,
	.stop = dpu_stop,
	.isr = dpu_isr,
	.flip = dpu_flip,
	.ifconfig = dpu_dpi_init,
//	.write_back = dpu_write_back,
};

struct dispc_core_ops *dispc_core_ops_attach(void)
{
	return &dpu_lite_r1p0_ops;
}
