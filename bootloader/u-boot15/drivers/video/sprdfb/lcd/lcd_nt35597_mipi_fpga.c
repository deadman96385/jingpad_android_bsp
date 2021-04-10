/* drivers/video/sprdfb/lcd_nt35597_mipi.c
 *
 * Support for nt35597 mipi LCD device
 *
 * Copyright (C) 2015 Spreadtrum
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

#define MAX_DATA   24

typedef struct LCM_Init_Code_tag {
	unsigned int tag;
	unsigned char data[MAX_DATA];
}LCM_Init_Code;

typedef struct LCM_force_cmd_code_tag{
	unsigned int datatype;
	LCM_Init_Code real_cmd_code;
}LCM_Force_Cmd_Code;

#define LCM_TAG_SHIFT 24
#define LCM_TAG_MASK  ((1 << 24) -1)
#define LCM_SEND(len) ((1 << LCM_TAG_SHIFT)| len)
#define LCM_SLEEP(ms) ((2 << LCM_TAG_SHIFT)| ms)

#define LCM_TAG_SEND  (1<< 0)
#define LCM_TAG_SLEEP (1 << 1)

static LCM_Init_Code init_data[] = {

#if 1
{LCM_SEND(2), {0xFF, 0x10}},
{LCM_SEND(2), {0xBB, 0x13}},


{LCM_SEND(2), {0xE5, 0x00}},


{LCM_SEND(2), {0xC0, 0x00}},
{LCM_SEND(2), {0xFB, 0x01}},

{LCM_SEND(1), {0x11}},
{LCM_SLEEP(120)},
{LCM_SEND(1), {0x29}},
#endif

};


static LCM_Force_Cmd_Code rd_prep_code[]={
//	{0x39, {LCM_SEND(8), {0x6, 0, 0xF0, 0x55, 0xAA, 0x52, 0x08, 0x01}}},
	{0x37, {LCM_SEND(2), {0x3, 0}}},
};

static int32_t nt35597_mipi_init(struct panel_spec *self)
{
	int32_t i = 0;
	LCM_Init_Code *init = init_data;
	unsigned int tag;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;

	LCD_PRINT("sprdfb:nt35597_mipi_init\n");

	mipi_set_cmd_mode();

	for(i = 0; i < ARRAY_SIZE(init_data); i++){
		tag = (init->tag >>24);
		if(tag & LCM_TAG_SEND){
			mipi_gen_write(init->data, (init->tag & LCM_TAG_MASK));
			udelay(20);
		}else if(tag & LCM_TAG_SLEEP){
			mdelay((init->tag & LCM_TAG_MASK));
		}
		init++;
	}
	return 0;
}

static uint32_t nt35597_readid(struct panel_spec *self)
{
	int32_t i = 0;
	uint32_t j =0;
	LCM_Force_Cmd_Code * rd_prepare = rd_prep_code;
	uint8_t read_data[3] = {0};
	int32_t read_rtn = 0;
	unsigned int tag = 0;
	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_force_write_t mipi_force_write = self->info.mipi->ops->mipi_force_write;
	mipi_force_read_t mipi_force_read = self->info.mipi->ops->mipi_force_read;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	LCD_PRINT("sprdfb:lcd_nt35597_mipi read id!\n");

	return 0x97;
	mipi_set_cmd_mode();
	mipi_eotp_set(0,1);

	for(j = 0; j < 4; j++){
		rd_prepare = rd_prep_code;
		for(i = 0; i < ARRAY_SIZE(rd_prep_code); i++){
			tag = (rd_prepare->real_cmd_code.tag >> 24);
			if(tag & LCM_TAG_SEND){
				mipi_force_write(rd_prepare->datatype, rd_prepare->real_cmd_code.data, (rd_prepare->real_cmd_code.tag & LCM_TAG_MASK));
			}else if(tag & LCM_TAG_SLEEP){
				mdelay((rd_prepare->real_cmd_code.tag & LCM_TAG_MASK));
			}
			rd_prepare++;
		}
		read_rtn = mipi_force_read(0xF4, 1,(uint8_t *)read_data);
		printk("lcd_nt35597_mipi read id 0xF4 value is 0x%x, 0x%x, 0x%x!\n", read_data[0], read_data[1], read_data[2]);

		if(0x97 == read_data[0]){
			printk("lcd_nt35597_mipi read id success!\n");
			mipi_eotp_set(1,1);
			return 0x97;
		}
	}
	mipi_eotp_set(1,1);
	return 0x97;
}

int32_t nt35597_reset(struct panel_spec *self)
{
#if 0
	sprd_gpio_request(NULL, LCM_GPIO_AVDDEN);
	sprd_gpio_direction_output(NULL, LCM_GPIO_AVDDEN, 1);
	sprd_gpio_set(NULL, LCM_GPIO_AVDDEN, 1);
	mdelay(10);
	sprd_gpio_request(NULL, LCM_GPIO_AVEEEN);
	sprd_gpio_direction_output(NULL, LCM_GPIO_AVEEEN, 1);
	sprd_gpio_set(NULL, LCM_GPIO_AVEEEN, 1);
	mdelay(20);
#endif
	dispc_write(1, DISPC_RSTN);
	mdelay(20);
	dispc_write(0, DISPC_RSTN);
	mdelay(20);
	dispc_write(1, DISPC_RSTN);
	mdelay(120);

	return 0;
}

static struct panel_operations lcd_nt35597_mipi_operations = {
	.panel_init = nt35597_mipi_init,
	.panel_readid = nt35597_readid,
	.panel_reset = nt35597_reset,
};

static struct timing_rgb lcd_nt35597_mipi_timing = {
	.hfp = 0x40,  /* unit: pixel */
	.hbp = 0x40,
	.hsync = 2,//4,
	.vfp = 15, /*unit: line*/
	.vbp = 5,
	.vsync = 2,
};

static struct info_mipi lcd_nt35597_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 24, /*18,16*/
	.lan_number = 4,
	.phy_feq = 300*1000,
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_nt35597_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_nt35597_mipi_fpga_spec = {
	.width = 720,
	.height = 1280,
	.fps = 6,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.is_need_reset = 1,
	.is_need_dsc = 0,
	.info = {
		.mipi = &lcd_nt35597_mipi_info
	},
	.ops = &lcd_nt35597_mipi_operations,
};

