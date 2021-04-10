/*
 *Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 *This software is licensed under the terms of the GNU General Public
 *License version 2, as published by the Free Software Foundation, and
 *may be copied, distributed, and modified under those terms.
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 */

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

//==================================================================
#include <common.h>
#include <asm/io.h>
#include <asm/errno.h>
#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
#include <linux/compat.h>
#include <linux/types.h>
#include <lcd.h>


#ifndef bool
typedef int bool;
#endif
#ifndef false
#define false 0
#endif
#ifndef true
#define true 1
#endif


#define pr_err(fmt, args...) do { printf("[sprdfb][%s] ", __func__); printf(fmt, ##args); } while (0)
#define pr_info(fmt, args...) do { printf("[sprdfb][%s] ", __func__); printf(fmt, ##args); } while (0)
#define pr_emerg(fmt, args...) do { printf("[sprdfb][%s]", __func__); printf(fmt, ##args); } while (0)
#define pr_debug(fmt, args...) do { } while (0)

#define msleep(a)	udelay(a * 1000)
#define CMD_END		0
//==================================================================
enum {
	SPRD_MAINLCD_ID = 0,
	SPRD_SUBLCD_ID,
	SPRD_MAX_LCD_ID,
};

/* LCD supported FPS */
#define LCD_MAX_FPS 70
#define LCD_MIN_FPS 0

enum {
	SPRD_PANEL_TYPE_MCU = 0,
	SPRD_PANEL_TYPE_RGB,
	SPRD_PANEL_TYPE_MIPI,
	SPRD_PANEL_TYPE_LVDS,
	SPRD_PANEL_TYPE_LIMIT
};

enum {
	SPRD_POLARITY_POS = 0,
	SPRD_POLARITY_NEG,
	SPRD_POLARITY_LIMIT
};

enum {
	SPRD_RGB_BUS_TYPE_I2C = 0,
	SPRD_RGB_BUS_TYPE_SPI,
	SPRD_RGB_BUS_TYPE_LVDS,
	SPRD_RGB_BUG_TYPE_LIMIT
};

enum {
	SPRD_MIPI_MODE_CMD = 0,
	SPRD_MIPI_MODE_VIDEO,
	SPRD_MIPI_MODE_LIMIT
};

enum {
	PANEL_VIDEO_NON_BURST_SYNC_PULSES = 0,
	PANEL_VIDEO_NON_BURST_SYNC_EVENTS,
	PANEL_VIDEO_BURST_MODE
};

struct rgb_timing {
	uint16_t hfp;		/*unit: pixel */
	uint16_t hbp;
	uint16_t hsync;
	uint16_t vfp;		/*unit: line */
	uint16_t vbp;
	uint16_t vsync;
};

struct dsi_cmd_header {
	uint8_t data_type;
	uint8_t wait;
	uint8_t wc_l;
	uint8_t wc_h;
} __packed;

struct dsi_cmd_desc {
	uint8_t data_type;
	uint8_t wait;
	uint8_t wc_h;
	uint8_t wc_l;
	uint8_t payload[];
};

/* LCD abstraction */
struct panel_info {
	/* common parameters */
	const char *lcd_name;
	uint8_t type;
	uint8_t bpp;
//	uint8_t fps;
	uint16_t width;
	uint16_t height;

	/* DPI specific parameters */
	uint32_t pixel_clk;
	uint16_t h_sync_pol;
	uint16_t v_sync_pol;
	uint16_t de_pol;
	uint16_t te_pol;
	struct rgb_timing rgb_timing;

	/* MIPI DSI specific parameters */
	uint32_t phy_freq;
	uint8_t lane_num;
	uint8_t work_mode;	/*command_mode, video_mode */
	uint8_t burst_mode;	/*burst, non-burst */
	bool nc_clk_en;

	/* platform specific parameters */
	bool dsc_en;
	bool bv3_en;
	bool is_oled;
};

struct panel_ops {
	int (*init)(void);
	int (*read_id)(void);
	int (*power)(int on);
	int (*set_brightness)(int level);
};

struct panel_cfg {
	uint32_t lcd_id;
	struct panel_driver *drv;
};

struct panel_driver {
	struct panel_info *info;
	struct panel_ops *ops;
};

struct panel_info *panel_info_attach(void);
int sprd_panel_probe(void);

#endif
