/*
 * Copyright (C) 2018 Spreadtrum Communications Inc.
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
#include "dpu_r4p0_corner_param.h"
#include "dpu_enhance_param.h"

#define DISPC_INT_FBC_PLD_ERR_MASK	BIT(8)
#define DISPC_INT_FBC_HDR_ERR_MASK	BIT(9)

#define XFBC8888_HEADER_SIZE(w, h) (ALIGN(w * h / (8 * 8) / 2, 32))
#define XFBC8888_PAYLOAD_SIZE(w, h) (w * h * 4)
#define XFBC8888_BUFFER_SIZE(w, h) (XFBC8888_HEADER_SIZE(w, h) \
				+ XFBC8888_PAYLOAD_SIZE(w, h))

#define XFBC565_HEADER_SIZE(w, h) (ALIGN(w * h / (16 * 8) / 2, 16))
#define XFBC565_PAYLOAD_SIZE(w, h) (w * h * 2)
#define XFBC565_BUFFER_SIZE(w, h) (XFBC565_HEADER_SIZE(w, h) \
				+ XFBC565_PAYLOAD_SIZE(w, h))

struct layer_reg {
	u32 addr[4];
	u32 ctrl;
	u32 size;
	u32 pitch;
	u32 pos;
	u32 alpha;
	u32 ck;
	u32 pallete;
	u32 crop_start;
};

struct wb_region_reg {
	u32 pos;
	u32 size;
};

struct dpu_reg {
	u32 dpu_version;
	u32 dpu_ctrl;
	u32 dpu_cfg0;
	u32 dpu_cfg1;
	u32 dpu_cfg2;
	u32 dpu_secure;
	u32 reserved_0x0018_0x001C[2];
	u32 panel_size;
	u32 blend_size;
	u32 reserved_0x0028;
	u32 bg_color;
	struct layer_reg layers[8];
	u32 wb_base_addr;
	u32 wb_ctrl;
	u32 wb_cfg;
	u32 wb_pitch;
	u32 reserved_0x01C0_0x01DC[8];
	u32 dpu_int_en;
	u32 dpu_int_clr;
	u32 dpu_int_sts;
	u32 dpu_int_raw;
	u32 dpi_ctrl;
	u32 dpi_h_timing;
	u32 dpi_v_timing;
	u32 reserved_0x01FC;
	u32 dpu_enhance_cfg;
	u32 reserved_0x0204_0x020C[3];
	u32 epf_epsilon;
	u32 epf_gain0_3;
	u32 epf_gain4_7;
	u32 epf_diff;
	u32 reserved_0x0220_0x023C[8];
	u32 hsv_lut_addr;
	u32 hsv_lut_wdata;
	u32 hsv_lut_rdata;
	u32 reserved_0x024C_0x027C[13];
	u32 cm_coef01_00;
	u32 cm_coef03_02;
	u32 cm_coef11_10;
	u32 cm_coef13_12;
	u32 cm_coef21_20;
	u32 cm_coef23_22;
	u32 reserved_0x0298_0x02BC[10];
	u32 slp_cfg0;
	u32 slp_cfg1;
	u32 slp_cfg2;
	u32 slp_cfg3;
	u32 slp_lut_addr;
	u32 slp_lut_wdata;
	u32 slp_lut_rdata;
	u32 threed_lut_addr;
	u32 threed_lut_wdata;
	u32 threed_lut_rdata;
	u32 reserved_0x02E8_0x02FC[6];
	u32 gamma_lut_addr;
	u32 gamma_lut_wdata;
	u32 gamma_lut_rdata;
	u32 reserved_0x030C_0x033C[13];
	u32 checksum_en;
	u32 checksum0_start_pos;
	u32 checksum0_end_pos;
	u32 checksum1_start_pos;
	u32 checksum1_end_pos;
	u32 checksum0_result;
	u32 checksum1_result;
	u32 reserved_0x035C;
	u32 dpu_sts[18];
	u32 reserved_0x03A8_0x03AC[2];
	u32 dpu_fbc_cfg0;
	u32 dpu_fbc_cfg1;
	u32 dpu_fbc_cfg2;
	u32 reserved_0x03BC;
	u32 slp_cfg4;
	u32 slp_cfg5;
	u32 slp_cfg6;
	u32 slp_cfg7;
	u32 slp_cfg8;
	u32 slp_cfg9;
	u32 slp_cfg10;
	u32 reserved_0x3DC_0x3EC[5];
	u32 rf_ram_addr;
	u32 rf_ram_rdata_low;
	u32 rf_ram_rdata_high;
	u32 reserved_0x03FC;
	u32 cabc_hist0;
	u32 cabc_hist1;
	u32 cabc_hist2;
	u32 cabc_hist3;
	u32 cabc_hist4;
	u32 cabc_hist5;
	u32 cabc_hist6;
	u32 cabc_hist7;
	u32 cabc_hist8;
	u32 cabc_hist9;
	u32 cabc_hist10;
	u32 cabc_hist11;
	u32 cabc_hist12;
	u32 cabc_hist13;
	u32 cabc_hist14;
	u32 cabc_hist15;
	u32 cabc_hist16;
	u32 cabc_hist17;
	u32 cabc_hist18;
	u32 cabc_hist19;
	u32 cabc_hist20;
	u32 cabc_hist21;
	u32 cabc_hist22;
	u32 cabc_hist23;
	u32 cabc_hist24;
	u32 cabc_hist25;
	u32 cabc_hist26;
	u32 cabc_hist27;
	u32 cabc_hist28;
	u32 cabc_hist29;
	u32 cabc_hist30;
	u32 cabc_hist31;
	u32 reserved_0x047C_0x04FC[32];
	u32 corner_config;
	u32 top_corner_lut_addr;
	u32 top_corner_lut_wdata;
	u32 top_corner_lut_rdata;
	u32 bot_corner_lut_addr;
	u32 bot_corner_lut_wdata;
	u32 bot_corner_lut_rdata;
};

struct wb_region {
	u32 index;
	u16 pos_x;
	u16 pos_y;
	u16 size_w;
	u16 size_h;
};

enum {
	ENHANCE_CFG_ID_MODULE_EN,
	ENHANCE_CFG_ID_SCL,
	ENHANCE_CFG_ID_EPF,
	ENHANCE_CFG_ID_HSV,
	ENHANCE_CFG_ID_CM,
	ENHANCE_CFG_ID_SLP,
	ENHANCE_CFG_ID_GAMMA,
	ENHANCE_CFG_ID_MAX
};

struct enhance_module {
	u32 scl_en: 1;
	u32 epf_en: 1;
	u32 hsv_en: 1;
	u32 cm_en: 1;
	u32 slp_en: 1;
	u32 gamma_en: 1;
	u32 blp_en: 1;
};

struct scale_cfg {
	u32 in_w;
	u32 in_h;
	u32 out_w;
	u32 out_h;
};

struct epf_cfg {
	int epsilon0;
	int epsilon1;
	int gain0;
	int gain1;
	int gain2;
	int gain3;
	int gain4;
	int gain5;
	int gain6;
	int gain7;
	int max_diff;
	int min_diff;
};

struct hsv_entry {
	u16 hue;
	u16 sat;
};

struct hsv_lut {
	struct hsv_entry table[360];
};

struct gamma_entry {
	u16 r;
	u16 g;
	u16 b;
};

struct gamma_lut {
	u16 r[256];
	u16 g[256];
	u16 b[256];
};

struct cm_cfg {
	short coef00;
	short coef01;
	short coef02;
	short coef03;
	short coef10;
	short coef11;
	short coef12;
	short coef13;
	short coef20;
	short coef21;
	short coef22;
	short coef23;
};

struct slp_cfg {
	u8 brightness;
	u16 brightness_step;
	u8 fst_max_bright_th;
	u8 fst_max_bright_th_step[5];
	u8 hist_exb_no;
	u8 hist_exb_percent;
	u16 mask_height;
	u8 fst_pth_index[4];
	u8 hist9_index[9];
	u8 glb_x[3];
	u16 glb_s[3];
	u16 limit_hclip;
	u16 limit_lclip;
	u16 limit_clip_step;
	u8 fast_ambient_th;
	u8 scene_change_percent_th;
	u8 local_weight;
	u8 fst_pth;
	u8 cabc_endv;
	u8 cabc_startv;
};

struct enhance_cfg {
	u32 id;
	void *param;
};

static bool evt_update;
static bool evt_stop;
static int wb_en;
static int max_vsync_count;
static int vsync_count;
static struct sprd_adf_hwlayer wb_layer;
static struct wb_region region[3];
static int wb_xfbc_en;

#ifdef CONFIG_CORNER_RADIUS
static int corner_radius = CONFIG_CORNER_RADIUS;
#else
static int corner_radius;
#endif

static void dpu_clean(struct dispc_context *ctx);
static void dpu_layer(struct dispc_context *ctx,
		    struct sprd_adf_hwlayer *hwlayer);
static void dpu_write_back(struct dispc_context *ctx,
		struct wb_region region[], u8 count);
static void dpu_corner_init(struct dispc_context *ctx);


static u32 dpu_get_version(struct dispc_context *ctx)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;

	return reg->dpu_version;
}

static u32 dpu_isr(struct dispc_context *ctx)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;
	u32 reg_val;

	if (!reg) {
		pr_err("invalid reg\n");
		return 0;
	}

	reg_val = reg->dpu_int_sts;
	reg->dpu_int_clr = reg_val;

	/*disable err interrupt */
	if (reg_val & DISPC_INT_ERR_MASK)
		reg->dpu_int_en &= ~DISPC_INT_ERR_MASK;

	/*dpu update done isr */
	if (reg_val & DISPC_INT_UPDATE_DONE_MASK) {
		evt_update = true;
		wake_up_interruptible_all(&ctx->wait_queue);
	}

	/*dpu vsync isr */
	if (reg_val & DISPC_INT_DPI_VSYNC_MASK) {
		/*write back feature*/
		if (vsync_count == max_vsync_count && wb_en)
			dpu_write_back(ctx, region, 1);
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
		/*
		 * The write back is a time-consuming operation. If there is a
		 * flip occurs before write back done, the write back buffer is
		 * no need to display. Or the new frame will be covered by the
		 * write back buffer, which is not we wanted.
		 */
		if (vsync_count > max_vsync_count) {
			dpu_clean(ctx);
			dpu_layer(ctx, &wb_layer);
			/*reg_val |= DISPC_INT_FENCE_SIGNAL_REQUEST;*/
		}
		pr_debug("wb done\n");
	}

	/* dpu write back error isr */
	if (reg_val & DISPC_INT_WB_FAIL_MASK) {
		pr_err("dpu write back fail\n");
		/*give a new chance to write back*/
		wb_en = true;
		vsync_count = 0;
	}

	/* dpu ifbc payload error isr */
	if (reg_val & DISPC_INT_FBC_PLD_ERR_MASK)
		pr_err("dpu ifbc payload error\n");

	/* dpu ifbc header error isr */
	if (reg_val & DISPC_INT_FBC_HDR_ERR_MASK)
		pr_err("dpu ifbc header error\n");

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
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;

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
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;

	if (!reg)
		return;

	if (ctx->if_type == SPRD_DISPC_IF_DPI)
		reg->dpu_ctrl |= BIT(1);

	dpu_wait_stop_done(ctx);
	pr_info("dpu stop\n");
}

static void dpu_run(struct dispc_context *ctx)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;

	if (!reg)
		return;

	evt_update = false;

	if (ctx->if_type == SPRD_DISPC_IF_DPI) {
		if (ctx->is_stopped) {
			/* dpu run */
			reg->dpu_ctrl |= BIT(0);

			ctx->is_stopped = false;
			pr_info("dpu run\n");
		} else {
			/*dpu register update trigger*/
			reg->dpu_ctrl |= BIT(2);

			/*make sure all the regs are updated to the shadow*/
			dpu_wait_update_done(ctx);
		}

		/* if the underflow err was disabled in isr, re-enable it */
		reg->dpu_int_en |= DISPC_INT_ERR_MASK;

	} else if (ctx->if_type == SPRD_DISPC_IF_EDPI) {
		/* dpu run */
		reg->dpu_ctrl |= BIT(0);

		ctx->is_stopped = false;
	}
}

static int dpu_init(struct dispc_context *ctx)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;
	struct panel_info *panel = ctx->panel;
	u32 size;
	int i;

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

	/* set dpu output size */
	size = (panel->width & 0xffff) | ((panel->height) << 16);
	reg->panel_size = size;
	reg->blend_size = size;

	reg->dpu_cfg0 = 0;
	reg->dpu_cfg1 = 0x44aadc;
	reg->dpu_cfg2 = 0;
	dpu_clean(ctx);
	reg->dpu_enhance_cfg = 0;

	if (corner_radius)
		dpu_corner_init(ctx);

	/*dpu_write_back_config(ctx);*/

	/* config dpu enhance slp lut */
	for (i = 0; i < 256; i++) {
		reg->slp_lut_addr = i;
		udelay(1);
		reg->slp_lut_wdata = slp_lut[i];
	}

	return 0;
}

static void dpu_uninit(struct dispc_context *ctx)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;

	if (!reg)
		return;

	reg->dpu_int_en = 0;
	reg->dpu_int_clr = 0xff;
}

enum {
	DPU_LAYER_FORMAT_YUV422_2PLANE,
	DPU_LAYER_FORMAT_YUV420_2PLANE,
	DPU_LAYER_FORMAT_YUV420_3PLANE,
	DPU_LAYER_FORMAT_ARGB8888,
	DPU_LAYER_FORMAT_RGB565,
	DPU_LAYER_FORMAT_XFBC_ARGB8888 = 8,
	DPU_LAYER_FORMAT_XFBC_RGB565,
	DPU_LAYER_FORMAT_MAX_TYPES,
};

/*
 * Because in OpenGL/PNG, the RGBA color stored in memory such that R
 * is at lowest address, G after it, B after that, and A last(the highest
 * address). Which is equivalent to ABGR in DRM format. That means the
 * color order in OpenGL(Android) is inverse in DRM(kernel).
 *
 * When the function implementBufferFormatConfig() was corrected in
 * vendor/sprd/modules/hwcomposer/SprdADFWrapper.cpp, the hal_to_drm_format()
 * could be removed.
 */
static u32 hal_to_drm_format(u32 hal_format)
{
	switch (hal_format) {
	case DRM_FORMAT_RGBA8888:
		return DRM_FORMAT_ABGR8888;
	case DRM_FORMAT_RGBX8888:
		return DRM_FORMAT_XBGR8888;
	case DRM_FORMAT_BGRA8888:
		return DRM_FORMAT_ARGB8888;
	case DRM_FORMAT_RGB888:
		return DRM_FORMAT_BGR888;
/*
	case DRM_FORMAT_RGB565:
		return DRM_FORMAT_BGR565;
*/
	default:
		return hal_format;
	}
}

static u32 dpu_img_ctrl(u32 format, u32 blending, u32 compression)
{
	int reg_val = 0;

	/* layer enable */
	reg_val |= BIT(0);

	/* need to convert the HAL_PIXEL_FORMAT* to DRM_FORMAT* first */
	format = hal_to_drm_format(format);

	switch (format) {
	case DRM_FORMAT_BGRA8888:
		/* BGRA8888 -> ARGB8888 */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B3B2B1B0 << 8;
		if (compression)
			/* XFBC-ARGB8888 */
			reg_val |= (DPU_LAYER_FORMAT_XFBC_ARGB8888 << 4);
		else
			reg_val |= (DPU_LAYER_FORMAT_ARGB8888 << 4);
		break;
	case DRM_FORMAT_RGBX8888:
	case DRM_FORMAT_RGBA8888:
		/* RGBA8888 -> ABGR8888 */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B3B2B1B0 << 8;
	case DRM_FORMAT_ABGR8888:
		/* rb switch */
		reg_val |= BIT(10);
	case DRM_FORMAT_ARGB8888:
		if (compression)
			/* XFBC-ARGB8888 */
			reg_val |= (DPU_LAYER_FORMAT_XFBC_ARGB8888 << 4);
		else
			reg_val |= (DPU_LAYER_FORMAT_ARGB8888 << 4);
		break;
	case DRM_FORMAT_XBGR8888:
		/* rb switch */
		reg_val |= BIT(10);
	case DRM_FORMAT_XRGB8888:
		if (compression)
			/* XFBC-ARGB8888 */
			reg_val |= (DPU_LAYER_FORMAT_XFBC_ARGB8888 << 4);
		else
			reg_val |= (DPU_LAYER_FORMAT_ARGB8888 << 4);
		break;
	case DRM_FORMAT_BGR565:
		/* rb switch */
		reg_val |= BIT(10);
	case DRM_FORMAT_RGB565:
		if (compression)
			/* XFBC-RGB565 */
			reg_val |= (DPU_LAYER_FORMAT_XFBC_RGB565 << 4);
		else
			reg_val |= (DPU_LAYER_FORMAT_RGB565 << 4);
		break;
	case DRM_FORMAT_NV12:
		/*2-Lane: Yuv420 */
		reg_val |= DPU_LAYER_FORMAT_YUV420_2PLANE << 4;
		/*Y endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B3B2B1B0 << 8;
		/*UV endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B3B2B1B0 << 10;
		break;
	case DRM_FORMAT_NV21:
		/*2-Lane: Yuv420 */
		reg_val |= DPU_LAYER_FORMAT_YUV420_2PLANE << 4;
		/*Y endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B0B1B2B3 << 8;
		/*UV endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B0B1B2B3 << 10;
		break;
	case DRM_FORMAT_NV16:
		/*2-Lane: Yuv422 */
		reg_val |= DPU_LAYER_FORMAT_YUV422_2PLANE << 4;
		/*Y endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B3B2B1B0 << 8;
		/*UV endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B3B2B1B0 << 10;
		break;
	case DRM_FORMAT_NV61:
		/*2-Lane: Yuv422 */
		reg_val |= DPU_LAYER_FORMAT_YUV422_2PLANE << 4;
		/*Y endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B0B1B2B3 << 8;
		/*UV endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B0B1B2B3 << 10;
		break;
	case DRM_FORMAT_YUV420:
		reg_val |= DPU_LAYER_FORMAT_YUV420_3PLANE << 4;
		/*Y endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B0B1B2B3 << 8;
		/*UV endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B0B1B2B3 << 10;
		break;
	default:
		pr_err("error: invalid format %c%c%c%c\n", format,
						format >> 8,
						format >> 16,
						format >> 24);
		break;
	}

	switch (blending) {
	case HWC_BLENDING_NONE:
		/* don't do blending, maybe RGBX */
		/* alpha mode select - layer alpha */
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
		/* alpha mode select - layer alpha */
		reg_val |= BIT(2);
		break;
	}

	return reg_val;
}

static void dpu_clean(struct dispc_context *ctx)
{
	int i;
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;

	for (i = 0; i < 8; i++)
		reg->layers[i].ctrl = 0;
}

static void dpu_bgcolor(struct dispc_context *ctx, u32 color)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;

	if (!reg)
		return;

	reg->bg_color = color;
	dpu_clean(ctx);
}

static void dpu_layer(struct dispc_context *ctx,
		    struct sprd_adf_hwlayer *hwlayer)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;
	struct layer_reg *layer;
	int size;
	int offset;
	int wd;
	int i;

	if (!reg)
		return;

	layer = &reg->layers[hwlayer->hwlayer_id];
	offset = (hwlayer->dst_x & 0xffff) | ((hwlayer->dst_y) << 16);

	if (hwlayer->start_w && hwlayer->start_h)
		size = (hwlayer->start_w & 0xffff) | ((hwlayer->start_h) << 16);
	else
		size = (hwlayer->dst_w & 0xffff) | ((hwlayer->dst_h) << 16);

	if (adf_format_is_rgb(hwlayer->format))
		wd = adf_format_bpp(hwlayer->format) / 8;
	else
		wd = adf_format_plane_cpp(hwlayer->format, 0);

	for (i = 0; i < hwlayer->n_planes; i++) {
		if (hwlayer->iova_plane[i] % 16)
			pr_err("layer addr[%d] is not 16 bytes align, it's 0x%08x\n",
					i, hwlayer->iova_plane[i]);
		layer->addr[i] = hwlayer->iova_plane[i];
	}

	layer->pos = offset;
	layer->size = size;
	layer->crop_start = (hwlayer->start_y << 16) | hwlayer->start_x;
	layer->alpha = hwlayer->alpha;

	if (adf_format_num_planes(hwlayer->format) == 3)
		/* UV pitch is 1/2 of Y pitch*/
		layer->pitch = (hwlayer->pitch[0] / wd) |
				(hwlayer->pitch[0] / wd << 15);
	else
		layer->pitch = hwlayer->pitch[0] / wd;

	layer->ctrl = dpu_img_ctrl(hwlayer->format, hwlayer->blending,
		hwlayer->compression);

	pr_debug("dst_x = %d, dst_y = %d, dst_w = %d, dst_h = %d\n",
				hwlayer->dst_x, hwlayer->dst_y,
				hwlayer->dst_w, hwlayer->dst_h);
	pr_debug("start_x = %d, start_y = %d, start_w = %d, start_h = %d\n",
				hwlayer->start_x, hwlayer->start_y,
				hwlayer->start_w, hwlayer->start_h);
}

static void dpu_flip(struct dispc_context *ctx,
			struct sprd_restruct_config *config)
{
	int i;
	struct sprd_adf_hwlayer *hwlayer;

	if (ctx->if_type == SPRD_DISPC_IF_EDPI)
		/* make sure the dpu is in stop status, because sharkl3 edpi no shadow regs */
		/* can only be updated in the rising edge of dpu_RUN bit */
		dpu_wait_stop_done(ctx);

	vsync_count = 0;
	if (max_vsync_count && (config->number_hwlayer > 1))
		wb_en = false;
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
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;
	struct panel_info *panel = ctx->panel;
	struct rgb_timing *rgb;
	u32 reg_val = 0;
	u32 int_mask = 0;

	if (!reg || !panel)
		return;

	if (ctx->if_type == SPRD_DISPC_IF_DPI) {
		/*use dpi as interface */
		reg->dpu_cfg0 &= ~(BIT(0));

		/* disalbe halt enable for SPRD DSI */
		/* reg_val |= BIT(16); */

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
		/* enable dpu dpi vsync */
		int_mask |= DISPC_INT_DPI_VSYNC_MASK;
		/* enable underflow err INT */
		int_mask |= DISPC_INT_ERR_MASK;
		/* enable write back done INT */
		int_mask |= DISPC_INT_WB_DONE_MASK;
		/* enable write back fail INT */
		int_mask |= DISPC_INT_WB_FAIL_MASK;
		/* enable ifbc payload error INT */
		int_mask |= DISPC_INT_FBC_PLD_ERR_MASK;
		/* enable ifbc header error INT */
		int_mask |= DISPC_INT_FBC_HDR_ERR_MASK;

		reg->dpu_int_en = int_mask;

	} else if (ctx->if_type == SPRD_DISPC_IF_EDPI) {
		/*use edpi as interface */
		reg->dpu_cfg0 |= BIT(0);

		/*te pol */
		if (panel->te_pol == SPRD_POLARITY_NEG)
			reg_val |= BIT(9);
		/*use external te */
		reg_val |= BIT(10);

		/*enable te */
		reg_val |= BIT(8);
		reg->dpi_ctrl = reg_val;

		/* enable dpu DONE  INT */
		int_mask |= DISPC_INT_DONE_MASK;
		/* enable DISPC TE  INT for edpi*/
		int_mask |= DISPC_INT_TE_MASK;
		/* enable ifbc payload error INT */
		int_mask |= DISPC_INT_FBC_PLD_ERR_MASK;
		/* enable ifbc header error INT */
		int_mask |= DISPC_INT_FBC_HDR_ERR_MASK;

		reg->dpu_int_en = int_mask;
	}
}

static void dpu_write_back(struct dispc_context *ctx,
		struct wb_region region[], u8 count)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;
	struct panel_info *panel = ctx->panel;
	int index;
	int i;

	if (count == 0)
		return;

	reg->wb_ctrl |= 1;

	reg->wb_pitch = panel->width;
	reg->wb_base_addr = wb_layer.iova_plane[0];
	reg->wb_cfg = wb_xfbc_en ? ((2 << 1) | BIT(0)) : 0;

	/*update trigger*/
	reg->dpu_ctrl |= BIT(2);
}


void __maybe_unused dpu_enhance_cfg(struct dispc_context *ctx,
				struct enhance_cfg cfg[],
				 u32 count)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;
	struct panel_info *panel = ctx->panel;
	struct scale_cfg *scale;
	struct epf_cfg *epf;
	struct cm_cfg *cm;
	struct slp_cfg *slp;
	struct gamma_lut *gamma;
	struct hsv_lut *hsv;
	struct enhance_module *mod;
	int i, j;

	if (!reg || !panel || !count)
		return;

	for (i = 0; i < count; i++) {
		switch (cfg[i].id) {
		case ENHANCE_CFG_ID_MODULE_EN:
			mod = cfg[i].param;
			reg->dpu_enhance_cfg = (mod->blp_en << 6) |
						(mod->gamma_en << 5) |
						(mod->slp_en << 4) |
						(mod->cm_en << 3) |
						(mod->hsv_en << 2) |
						(mod->epf_en << 1) |
						mod->scl_en;
			break;
		case ENHANCE_CFG_ID_SCL:
			scale = cfg[i].param;
			reg->panel_size = (scale->out_h << 16) | scale->out_w;
			reg->blend_size = (scale->in_h << 16) | scale->in_w;
			break;
		case ENHANCE_CFG_ID_EPF:
			epf = cfg[i].param;
			reg->epf_epsilon = (epf->epsilon1 << 16) |
					epf->epsilon0;
			reg->epf_gain0_3 = (epf->gain3 << 24) |
					(epf->gain2 << 16) |
					(epf->gain1 << 8) |
					epf->gain0;
			reg->epf_gain4_7 = (epf->gain7 << 24) |
					(epf->gain6 << 16) |
					(epf->gain5 << 8) |
					epf->gain4;
			reg->epf_diff = (epf->max_diff << 8) | epf->min_diff;
			break;
		case ENHANCE_CFG_ID_HSV:
			hsv = cfg[i].param;
			for (j = 0; j < 360; j++) {
				reg->hsv_lut_addr = j;
				reg->hsv_lut_wdata = (hsv->table[j].sat << 16) |
							hsv->table[j].hue;
			}
			break;
		case ENHANCE_CFG_ID_CM:
			cm = cfg[i].param;
			reg->cm_coef01_00 = (cm->coef01 << 16) | cm->coef00;
			reg->cm_coef03_02 = (cm->coef03 << 16) | cm->coef02;
			reg->cm_coef11_10 = (cm->coef11 << 16) | cm->coef10;
			reg->cm_coef13_12 = (cm->coef13 << 16) | cm->coef12;
			reg->cm_coef21_20 = (cm->coef21 << 16) | cm->coef20;
			reg->cm_coef23_22 = (cm->coef23 << 16) | cm->coef22;
			break;
		case ENHANCE_CFG_ID_SLP:
			slp = cfg[i].param;
			reg->slp_cfg0 = (slp->brightness_step << 0) |
				((slp->brightness & 0x7f) << 16);
			reg->slp_cfg1 = ((slp->fst_max_bright_th & 0x7f) << 21) |
				((slp->fst_max_bright_th_step[0] & 0x7f) << 14) |
				((slp->fst_max_bright_th_step[1] & 0x7f) << 7) |
				((slp->fst_max_bright_th_step[2] & 0x7f) << 0);
			reg->slp_cfg2 = ((slp->fst_max_bright_th_step[3] & 0x7f) << 25) |
				((slp->fst_max_bright_th_step[4] & 0x7f) << 18) |
				((slp->hist_exb_no & 0x3) << 16) |
				((slp->hist_exb_percent & 0x7f) << 9);
			reg->slp_cfg3 = ((slp->mask_height & 0xfff) << 19) |
				((slp->fst_pth_index[0] & 0xf) << 15) |
				((slp->fst_pth_index[1] & 0xf) << 11) |
				((slp->fst_pth_index[2] & 0xf) << 7) |
				((slp->fst_pth_index[3] & 0xf) << 3);
			reg->slp_cfg4 = (slp->hist9_index[0] << 24) |
				(slp->hist9_index[1] << 16) | (slp->hist9_index[2] << 8) |
				(slp->hist9_index[3] << 0);
			reg->slp_cfg5 = (slp->hist9_index[4] << 24) |
				(slp->hist9_index[5] << 16) | (slp->hist9_index[6] << 8) |
				(slp->hist9_index[7] << 0);
			reg->slp_cfg6 = (slp->hist9_index[8] << 24) |
				(slp->glb_x[0] << 16) | (slp->glb_x[1] << 8) |
				(slp->glb_x[2] << 0);
			reg->slp_cfg7 = ((slp->glb_s[0] & 0x1ff) << 23) |
				((slp->glb_s[1] & 0x1ff) << 14) |
				((slp->glb_s[2] & 0x1ff) << 5);
			reg->slp_cfg8 = ((slp->limit_hclip & 0x1ff) << 23) |
				((slp->limit_lclip & 0x1ff) << 14) |
				((slp->limit_clip_step & 0x1fff) << 0);
			reg->slp_cfg9 = ((slp->fast_ambient_th & 0x7f) << 25) |
				(slp->scene_change_percent_th << 17) |
				((slp->local_weight & 0xf) << 13) |
				((slp->fst_pth & 0x7f) << 6);
			reg->slp_cfg10 = (slp->cabc_endv << 8) | (slp->cabc_startv << 0);
			reg->dpu_enhance_cfg |= BIT(4);
			break;
		case ENHANCE_CFG_ID_GAMMA:
			gamma = cfg[i].param;
			for (j = 0; j < 256; j++) {
				reg->gamma_lut_addr = j;
				reg->gamma_lut_wdata = (gamma->r[j] << 20) |
							(gamma->g[j] << 10) |
							gamma->b[j];
			}
			break;
		default:
			break;
		}

		/*update trigger*/
		reg->dpu_ctrl |= BIT(2);
	}
}

static void dpu_corner_init(struct dispc_context *ctx)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;
	int i;

	reg->corner_config = (corner_radius << 24) |
				(corner_radius << 8);

	for (i = 0; i < corner_radius; i++) {
		reg->top_corner_lut_addr = i;
		reg->top_corner_lut_wdata = corner_param[corner_radius][i];
		reg->bot_corner_lut_addr = i;
		reg->bot_corner_lut_wdata =
			corner_param[corner_radius][corner_radius - i - 1];
	}

	reg->corner_config |= (TOP_CORNER_EN | BOT_CORNER_EN);
}

static struct dispc_core_ops dpu_r4p0_ops = {
	.version = dpu_get_version,
	.init = dpu_init,
	.uninit = dpu_uninit,
	.run = dpu_run,
	.stop = dpu_stop,
	.isr = dpu_isr,
	.ifconfig = dpu_dpi_init,
	.flip = dpu_flip,
	.bg_color = dpu_bgcolor,
};

struct dispc_core_ops *dispc_core_ops_attach(void)
{
	return &dpu_r4p0_ops;
}
