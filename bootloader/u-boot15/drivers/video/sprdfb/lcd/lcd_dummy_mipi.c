/* drivers/video/sprdfb/lcd_dummy_mipi.c
 *
 * Support for dummy mipi LCD device
 *
 * Copyright (C) 2015 Spreadtrum
 */

#include "../sprdfb_chip_common.h"
#include "../sprdfb.h"
#include "../sprdfb_panel.h"

#define printk printf

#define  LCD_DEBUG
#ifdef LCD_DEBUG
#define LCD_PRINT printk
#else
#define LCD_PRINT(...)
#endif

static int32_t dummy_mipi_init(struct panel_spec *self)
{
	LCD_PRINT("dummy panel init!\n");
	return 0;
}


static uint32_t dummy_readid(struct panel_spec *self)
{
	LCD_PRINT("lcd_dummy_mipi read id!\n");
	return 0xFFFF;
}

static struct panel_operations lcd_dummy_mipi_operations = {
	.panel_init = dummy_mipi_init,
	.panel_readid = dummy_readid,
};

static struct timing_rgb lcd_dummy_mipi_timing = {
	.hfp = 80,  /* unit: pixel */
	.hbp = 4,
	.hsync = 4,//4,
	.vfp = 17, /*unit: line*/
	.vbp = 18,
	.vsync = 5,
};


static struct info_mipi lcd_dummy_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 24, /*18,16*/
#ifdef CONFIG_ZEBU
	.lan_number = 3,
#else
	.lan_number = 4,
#endif
	.phy_feq = 550*1000,
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_dummy_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_dummy_mipi_spec = {
	.width = 720,
	.height = 1280,
	.fps = 60,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.info = {
		.mipi = &lcd_dummy_mipi_info
	},
	.ops = &lcd_dummy_mipi_operations,
};
