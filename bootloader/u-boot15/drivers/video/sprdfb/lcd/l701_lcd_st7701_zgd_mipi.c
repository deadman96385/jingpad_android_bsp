/* drivers/video/sprdfb/lcd_st7701_mipi.c
 *
 * Support for st7701 mipi LCD device
 *
 * Copyright (C) 2010 Spreadtrum
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

//#define LCD_Delay(ms)  uDelay(ms*1000)
///#define printk printf

#define  LCD_DEBUG
#ifdef LCD_DEBUG
#define LCD_PRINT printk
#else
#define LCD_PRINT(...)
#endif

#define MAX_DATA   56

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
//#define ARRAY_SIZE(array) ( sizeof(array) / sizeof(array[0]))

#define LCM_TAG_SEND  (1<< 0)
#define LCM_TAG_SLEEP (1 << 1)

static LCM_Init_Code init_data[] = {
	{LCM_SEND(8), {6, 0, 0xFF, 0x77, 0x01, 0x00, 0x00, 0x10}},
	{LCM_SEND(5), {3, 0, 0xC0, 0x63, 0x00}},
	{LCM_SEND(5), {3, 0, 0xC1, 0x0C, 0x07}},
	{LCM_SEND(5), {3, 0, 0xC2, 0x31, 0x08}},
	{LCM_SEND(2), {0xCC, 0x10}},
	{LCM_SEND(19), {17, 0, 0xB0, 0x40, 0x02, 0x87, 0x0E, 0x15, 0x0A, 0x03, 0x0A, 0x0A, 0x18, 0x08, 0x16, 0x13, 0x07, 0x09, 0x19}},
	{LCM_SEND(19), {17, 0, 0xB1, 0x40, 0x01, 0x86, 0x0D, 0x13, 0x09, 0x03, 0x0A, 0x09, 0x1C, 0x09, 0x15, 0x13, 0x91, 0x16, 0x19}},
	{LCM_SEND(8), {6, 0, 0xFF, 0x77, 0x01, 0x00, 0x00, 0x11}},
	{LCM_SEND(2), {0xB0, 0x4D}},
	{LCM_SEND(2), {0xB1, 0x64}},
	{LCM_SEND(2), {0xB2, 0x07}},
	{LCM_SEND(2), {0xB3, 0x80}},
	{LCM_SEND(2), {0xB5, 0x47}},
	{LCM_SEND(2), {0xB7, 0x85}},
	{LCM_SEND(2), {0xB8, 0x21}},
	{LCM_SEND(2), {0xB9, 0x10}},
	{LCM_SEND(2), {0xC1, 0x78}},
	{LCM_SEND(2), {0xC2, 0x78}},
	{LCM_SEND(2), {0xD0, 0x88}},
	{LCM_SEND(6), {4, 0, 0xE0, 0x00, 0xB4, 0x02}},
	{LCM_SEND(14), {12, 0, 0xE1, 0x06, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20}},
	{LCM_SEND(16), {14, 0, 0xE2, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{LCM_SEND(7), {5, 0, 0xE3, 0x00, 0x00, 0x33, 0x33}},
	{LCM_SEND(5), {3, 0, 0xE4, 0x44, 0x44}},
	{LCM_SEND(19), {17, 0, 0xE5, 0x09, 0x31, 0xBE, 0xA0, 0x0B, 0x31, 0xBE, 0xA0, 0x05, 0x31, 0xBE, 0xA0, 0x07, 0x31, 0xBE, 0xA0}},
	{LCM_SEND(7), {5, 0, 0xE6, 0x00, 0x00, 0x33, 0x33}},
	{LCM_SEND(5), {3, 0, 0xE7, 0x44, 0x44}},
	{LCM_SEND(19), {17, 0, 0xE8, 0x08, 0x31, 0xBE, 0xA0, 0x0A, 0x31, 0xBE, 0xA0, 0x04, 0x31, 0xBE, 0xA0, 0x06, 0x31, 0xBE, 0xA0}},
	{LCM_SEND(19), {17, 0, 0xEA, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00}},
	{LCM_SEND(10), {8, 0, 0xEB, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{LCM_SEND(5), {3, 0, 0xEC, 0x02, 0x00}},
	{LCM_SEND(19), {17, 0, 0xED, 0xF5, 0x47, 0x6F, 0x0B, 0x8F, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF9, 0xF8, 0xB0, 0xF6, 0x74, 0x5F}},
	{LCM_SEND(15), {13, 0, 0xEF, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}},
	{LCM_SEND(8), {6, 0, 0xFF, 0x77, 0x01, 0x00, 0x00, 0x00}},

	{LCM_SEND(2), {0x11, 0x00}},
	{LCM_SLEEP(120)},
	{LCM_SEND(2), {0x29, 0x00}},
	{LCM_SLEEP(20)},
	{LCM_SEND(2), {0x2C, 0x00}},
};

static LCM_Force_Cmd_Code rd_prep_code[]={
	{0x39, {LCM_SEND(8),{6,0, 0x01, 0x77, 0x01, 0x00, 0x00, 0x10}}},
	{0x37, {LCM_SEND(2), {0x3, 0}}},
};

static LCM_Init_Code disp_on =  {LCM_SEND(1), {0x29}};

static LCM_Init_Code sleep_in =  {LCM_SEND(1), {0x10}};

static LCM_Init_Code sleep_out =  {LCM_SEND(1), {0x11}};

static int32_t st7701_mipi_init(struct panel_spec *self)
{
	int32_t i;
	LCM_Init_Code *init = init_data;
	unsigned int tag;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;
	LCD_PRINT("uboot lcd_st7701_init\n");

	mipi_set_cmd_mode();

	mdelay(5);
	mipi_eotp_set(1,0);
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

	mdelay(5);
	mipi_eotp_set(1,1);
	return 0;
}

static uint32_t st7701_readid(struct panel_spec *self)
{
	/* TODO: need read id*/
	int32_t i = 0;
	int32_t j =0;
	LCM_Force_Cmd_Code * rd_prepare = rd_prep_code;
	uint8_t read_data[3] = {0};
	int32_t read_rtn = 0;
	unsigned int tag = 0;
	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_force_write_t mipi_force_write = self->info.mipi->ops->mipi_force_write;
	mipi_force_read_t mipi_force_read = self->info.mipi->ops->mipi_force_read;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	LCD_PRINT("uboot lcd_st7701_mipi read id!\n");

	mipi_set_cmd_mode();
	for(j = 0; j < 4; j++){
		rd_prepare = rd_prep_code;
		for(i = 0; i < ARRAY_SIZE(rd_prep_code); i++){
			tag = (rd_prepare->real_cmd_code.tag >> 24);
			if(tag & LCM_TAG_SEND){
				mipi_force_write(rd_prepare->datatype, rd_prepare->real_cmd_code.data, (rd_prepare->real_cmd_code.tag & LCM_TAG_MASK));
				udelay(20);
			}else if(tag & LCM_TAG_SLEEP){
				mdelay((rd_prepare->real_cmd_code.tag & LCM_TAG_MASK));
			}
			rd_prepare++;
		}
		mdelay(120);
		read_rtn = mipi_force_read(0xa1, 2,(uint8_t *)read_data);
		LCD_PRINT("lcd_st7701_mipi read id 0x04 value is 0x%x, 0x%x, 0x%x!\n", read_data[0], read_data[1], read_data[2]);

		if((0x88 == read_data[0])&&(0x02 == read_data[1])){
			LCD_PRINT("lcd_st7701_mipi read id success!\n");
			return 0x77012;
		}
	}

	mdelay(5);

	return 0x0;
}

int32_t st7701_reset(struct panel_spec *self)
{
	sprd_gpio_request(NULL, LCM_GPIO_RSTN);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 1);
	mdelay(5);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 0);
	mdelay(5);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 1);
	mdelay(20);

	return 0;
}

static struct panel_operations lcd_st7701_mipi_operations = {
	.panel_init = st7701_mipi_init,
	.panel_readid = st7701_readid,
	.panel_reset = st7701_reset,
};

static struct timing_rgb lcd_st7701_mipi_timing = {
	.hfp = 80,  /* unit: pixel */// 100
	.hbp = 80,//80
	.hsync = 10,//6
	.vfp = 18, /*unit: line*/
	.vbp = 18,
	.vsync =4, //6,
};

static struct info_mipi lcd_st7701_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 24, /*18,16*/
	.lan_number = 2,
	.phy_feq = 480*1000,
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_st7701_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_st7701_zgd_mipi_spec = {
	.width = 480,
	.height = 800,
	.fps = 60,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.is_need_reset = 1,
	.info = {
		.mipi = &lcd_st7701_mipi_info
	},
	.ops = &lcd_st7701_mipi_operations,
};


