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

#ifndef _SPRD_H_
#define _SPRD_H_

#include "sprd_panel.h"
#include "lib/adf_format.h"
#include "lib/drm_fourcc.h"

//==================================================================
#define down(x)
#define up(x)

#define wake_up_interruptible_all(queue)
#define wait_event_interruptible_timeout(queue, flag, timeout) \
({\
	u32 count;\
	if (!(flag)) {\
		for (count = 0; !(flag) && (count < timeout); count++) {\
			msleep(1);\
		}\
	}\
	(flag);\
})

#define msecs_to_jiffies(x)	(x)

#define ADF_MAX_PLANES	4
/**
 * sprd_adf_hwlayer - layer config that will set to hw
 *
 * @adf_buffer: get dma_buf for iommu map
 * @hwlayer_id: unique hwlayer id
 * @iova_plane: buffer plane io address
 * @alpha: layer's alpha value
 * @dst_x: layer's dest x
 * @dst_y: layer's dest y
 * @dst_w: layer's dest w
 * @dst_h: layer's dest h
 * @format: DRM-style fourcc, see drm_fourcc.h for standard formats
 * @blending: layer's blending mode
 * @rotation: layer's rotation value
 * @scale: layer's scale value
 * @compression: layer buffer's Compression mode
 */
struct sprd_adf_hwlayer {
//	struct adf_buffer base;
//	struct sprd_iommu_unmap_data iova_space[ADF_MAX_PLANES];
	__u32 hwlayer_id;
	__u32 interface_id;
	__u32 iova_plane[ADF_MAX_PLANES];
	__u32 pitch[ADF_MAX_PLANES];
	__u8 n_planes;
	__u32 alpha;
	__s16 start_x;
	__s16 start_y;
	__s16 start_w;
	__s16 start_h;
	__s16 dst_x;
	__s16 dst_y;
	__u16 dst_w;
	__u16 dst_h;
	__u32 format;
	__u32 blending;
	__u32 rotation;
	__u32 scale;
	__u32 compression;
	__u32 source;
};

/**
 * sprd_restruct_config - restruct config depend on display mode
 *
 * @number_hwlayer: the number of hw layer in this config
 * @hwlayers: hw layer config info that will set to hw plane
 * entries will follow this structure in memory
 */
struct sprd_restruct_config {
	__u32 number_hwlayer;
	struct sprd_adf_hwlayer hwlayers[0];
};

enum {
	/* no blending */
	HWC_BLENDING_NONE     = 0x0100,

	/* ONE / ONE_MINUS_SRC_ALPHA */
	HWC_BLENDING_PREMULT  = 0x0105,

	/* SRC_ALPHA / ONE_MINUS_SRC_ALPHA */
	HWC_BLENDING_COVERAGE = 0x0405
};

//================================================================================

#define DISPC_INT_DONE_MASK		BIT(0)
#define DISPC_INT_TE_MASK		BIT(1)
#define DISPC_INT_ERR_MASK		BIT(2)
#define DISPC_INT_EDPI_TE_MASK		BIT(3)
#define DISPC_INT_UPDATE_DONE_MASK	BIT(4)
#define DISPC_INT_DPI_VSYNC_MASK	BIT(5)
#define DISPC_INT_WB_DONE_MASK		BIT(6)
#define DISPC_INT_WB_FAIL_MASK		BIT(7)

/* NOTE: this mask is not a realy dispc interrupt mask */
#define DISPC_INT_FENCE_SIGNAL_REQUEST	BIT(31)

//#define ROUND(a, b) (((a) + (b) / 2) / (b))

enum {
	NORMAL_MODE = 0,
	FULL_MODE,
	MIXED_MODE
};

enum {
	SIZE_64 = 0,
	SIZE_128
};

enum {
	SPRD_DISPC_IF_DBI = 0,
	SPRD_DISPC_IF_DPI,
	SPRD_DISPC_IF_EDPI,
	SPRD_DISPC_IF_LIMIT
};

enum {
	SPRD_UNKNOWN = 0,
	SPRD_DYNAMIC_PCLK = 0x1,
	SPRD_DYNAMIC_FPS,
	SPRD_DYNAMIC_MIPI_CLK,
	SPRD_FORCE_FPS,
	SPRD_FORCE_PCLK,
	SPRD_MIPI_SSC,
};

enum {
	SPRD_DATA_TYPE_YUV422 = 0x00,
	SPRD_DATA_TYPE_YUV420 = 0x01,
	SPRD_DATA_TYPE_YUV400 = 0x02,
	SPRD_DATA_TYPE_RGB888 = 0x03,
	SPRD_DATA_TYPE_RGB666 = 0x04,
	SPRD_DATA_TYPE_RGB565 = 0x05,
	SPRD_DATA_TYPE_RGB555 = 0x06,
	SPRD_DATA_TYPE_COMPRESSED = 0x07,
	SPRD_DATA_TYPE_YUV422_3P = 0x08,
	SPRD_DATA_TYPE_YUV420_3P = 0x09,
	SPRD_DATA_TYPE_RGB888_PACK = 0x0A,
	SPRD_DATA_TYPE_AFBC_888 = 0x0B,
	SPRD_DATA_TYPE_LIMIT
};

enum {
	SPRD_IMG_DATA_ENDIAN_B0B1B2B3 = 0,
	SPRD_IMG_DATA_ENDIAN_B3B2B1B0,
	SPRD_IMG_DATA_ENDIAN_B2B3B0B1,
	SPRD_IMG_DATA_ENDIAN_B1B0B3B2,
	SPRD_IMG_DATA_ENDIAN_LIMIT
};

enum {
	SPRD_OVERLAY_STATUS_OFF = 0,
	SPRD_OVERLAY_STATUS_ON,
	SPRD_OVERLAY_STATUS_STARTED,
	SPRD_OVERLAY_STATUS_MAX
};

enum {
	SPRD_OVERLAY_DISPLAY_ASYNC = 0,
	SPRD_OVERLAY_DISPLAY_SYNC,
	SPRD_OVERLAY_DISPLAY_MAX
};

enum {
	DISPC_CLK_ID_CORE = 0,
	DISPC_CLK_ID_DBI,
	DISPC_CLK_ID_DPI,
	DISPC_CLK_ID_MAX
};

struct dispc_context {
	unsigned long base;
//	unsigned int  base_offset[2];
	bool is_inited;
	bool is_stopped;
	uint32_t id;	/*main_lcd, sub_lcd */
	uint16_t if_type;
	uint32_t dpi_clk_src;
//	void *logo_vaddr;
//	size_t logo_size;
	struct panel_info *panel;
	/*struct semaphore refresh_lock;*/
//	int  vsync_report_rate;
//	int  vsync_ratio_to_panel;
//	wait_queue_head_t wait_queue;
};

struct dispc_core_ops {
	uint32_t (*version)(struct dispc_context *ctx);
	int (*init)(struct dispc_context *ctx);
	void (*uninit)(struct dispc_context *ctx);
	void (*run)(struct dispc_context *ctx);
	void (*stop)(struct dispc_context *ctx);
	uint32_t (*isr)(struct dispc_context *ctx);
	void (*ifconfig)(struct dispc_context *ctx);
//	void (*write_back)(struct dispc_context *ctx, struct dispc_wb *pwb);
	void (*flip)(struct dispc_context *ctx,
		struct sprd_restruct_config *config);
	void (*bg_color)(struct dispc_context *ctx, uint32_t color);
};

struct dispc_clk_ops {
	int (*parse_dt)(struct dispc_context *ctx);
	int (*init)(struct dispc_context *ctx);
//	int (*uinit)(struct dispc_context *ctx);
//	int (*enable)(struct dispc_context *ctx);
//	int (*disable)(struct dispc_context *ctx);
	int (*update)(struct dispc_context *ctx, int clk_id, int val);
};

struct dispc_glb_ops {
	int (*parse_dt)(struct dispc_context *ctx);
	void (*enable)(struct dispc_context *ctx);
	void (*disable)(struct dispc_context *ctx);
	void (*reset)(struct dispc_context *ctx);
	void (*noc)(struct dispc_context *ctx, uint32_t mode);
	void (*power)(struct dispc_context *ctx, int enable);
};

struct sprd_dispc {
	struct dispc_context ctx;
	struct dispc_core_ops *core;
	struct dispc_clk_ops *clk;
	struct dispc_glb_ops *glb;
};

/*struct bitmap_t {
	uint16_t width;
	uint16_t height;
	uint8_t Bpp;
	uint8_t compression;
	uint32_t format;
	const void *addr[4];
};*/

extern struct sprd_dispc dispc_device;

int sprd_dispc_probe(void);
void sprd_dispc_run(struct sprd_dispc *dispc);
void sprd_dispc_stop(struct sprd_dispc *dispc);
int sprd_dispc_flip(struct sprd_dispc *dispc,
		struct sprd_restruct_config *config);

struct dispc_core_ops *dispc_core_ops_attach(void);
struct dispc_clk_ops *dispc_clk_ops_attach(void);
struct dispc_glb_ops *dispc_glb_ops_attach(void);

#endif
