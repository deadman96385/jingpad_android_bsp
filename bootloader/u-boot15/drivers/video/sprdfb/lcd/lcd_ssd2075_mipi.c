/* drivers/video/sprdfb/lcd_ssd2075_mipi.c
 *
 * Support for ssd2075 mipi LCD device
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

//#include <asm/arch/sprd_lcd.h>
//#include "../sprdfb.h"

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

#define MAX_DATA   48

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
 {LCM_SEND(2),{0xE1,0x93}},
 {LCM_SEND(2),{0xB3,0x00}},
 //5inchGIP
 {LCM_SEND(7),{5,0,0xB6,0x16,0x0F,0x00,0x77}}, //0x00
 {LCM_SEND(11),{9,0,0xB8,0x00,0x06,0x08,0x00,0x07,0x09,0x23,0x04}},
 {LCM_SEND(9),{7,0,0xB9,0x04,0x08,0x22,0xFF,0xFF,0x0F}},
 {LCM_SEND(11),{9,0,0xBA,0x0E,0x0E,0x10,0x10,0x0A,0x0A,0x0C,0x0C}},
 {LCM_SEND(11),{9,0,0xBB,0xA1,0xA1,0xA1,0xA1,0xA1,0xA1,0xA1,0xA1}},
 {LCM_SEND(11),{9,0,0xBC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
 {LCM_SEND(11),{9,0,0xBD,0x0F,0x0F,0x11,0x11,0x0B,0x0B,0x0D,0x0D}},
 {LCM_SEND(11),{9,0,0xBE,0xA1,0xA1,0xA1,0xA1,0xA1,0xA1,0xA1,0xA1}},
 {LCM_SEND(11),{9,0,0xBF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
 {LCM_SEND(6),{4,0,0xB1,0x06,0x44,0x10}},
 {LCM_SEND(8),{6,0,0xE0,0x11,0x02,0x04,0x00,0x01}},

 //Gamma2.2
 #if 1
 {LCM_SEND(9),{7,0,0xD0,0x00,0x00,0x0E,0x0F,0x14,0x20}},
 {LCM_SEND(8),{6,0,0xD1,0x1A,0x37,0x29,0x1B,0x08}},
 {LCM_SEND(9),{7,0,0xD2,0x00,0x00,0x0E,0x0F,0x14,0x20}},
 {LCM_SEND(8),{6,0,0xD3,0x1A,0x37,0x29,0x1B,0x08}},
 {LCM_SEND(9),{7,0,0xD4,0x00,0x00,0x0E,0x0F,0x14,0x20}},
 {LCM_SEND(8),{6,0,0xD5,0x1A,0x37,0x29,0x1B,0x08}},
 {LCM_SEND(9),{7,0,0xD6,0x00,0x00,0x0E,0x0F,0x14,0x20}},
 {LCM_SEND(8),{6,0,0xD7,0x1A,0x37,0x29,0x1B,0x08}},
 {LCM_SEND(9),{7,0,0xD8,0x00,0x00,0x0E,0x0F,0x14,0x20}},
 {LCM_SEND(8),{6,0,0xD9,0x1A,0x37,0x29,0x1B,0x08}},
 {LCM_SEND(9),{7,0,0xDA,0x00,0x00,0x0E,0x0F,0x14,0x20}},
 {LCM_SEND(8),{6,0,0xDB,0x1A,0x37,0x29,0x1B,0x08}},
 #else
 {LCM_SEND(9),{7,0,0xD0,0x00,0x00,0x1E,0x27,0x2D,0x35}},
 {LCM_SEND(8),{6,0,0xD1,0x2D,0x27,0x1A,0x1B,0x0A}},
 {LCM_SEND(9),{7,0,0xD2,0x00,0x00,0x1E,0x27,0x2D,0x35}},
 {LCM_SEND(8),{6,0,0xD3,0x2D,0x27,0x1A,0x1B,0x0A}},
 {LCM_SEND(9),{7,0,0xD4,0x00,0x00,0x1E,0x27,0x2D,0x35}},
 {LCM_SEND(8),{6,0,0xD5,0x26,0x2B,0x23,0x1B,0x0A}},
 {LCM_SEND(9),{7,0,0xD6,0x00,0x00,0x1E,0x27,0x2D,0x35}},
 {LCM_SEND(8),{6,0,0xD7,0x2D,0x27,0x1A,0x1B,0x0A}},
 {LCM_SEND(9),{7,0,0xD8,0x00,0x00,0x1E,0x27,0x2D,0x35}},
 {LCM_SEND(8),{6,0,0xD9,0x2D,0x27,0x1A,0x1B,0x0A}},
 {LCM_SEND(9),{7,0,0xDA,0x00,0x00,0x1E,0x27,0x2D,0x35}},
 {LCM_SEND(8),{6,0,0xDB,0x2D,0x27,0x1A,0x1B,0x0A}},
 #endif

 {LCM_SEND(7),{5,0,0x70,0xD8,0x00,0xFF,0x80}},
 {LCM_SEND(2),{0xFF,0x01}},

 {LCM_SEND(5),{3,0,0xC6,0xCC,0x33}},//77->CC
 {LCM_SEND(5),{3,0,0xDE,0x9D,0x30}},
 {LCM_SEND(2),{0x14,0x00}},

 {LCM_SEND(2),{0xE9,0x07}},
 {LCM_SEND(5),{3,0,0xED,0x60,0x10}},
 {LCM_SEND(2),{0xEC,0x12}},
 {LCM_SEND(7),{5,0,0xCD,0x77,0x7B,0x34,0x08}},
 {LCM_SEND(10),{8,0,0xC3,0x03,0x0D,0x34,0x05,0x01,0x44,0x54}},
 {LCM_SEND(8),{6,0,0xC4,0x02,0x03,0x3D,0x3D,0x5A}}, // Vcom
 {LCM_SEND(6),{4,0,0xCB,0xDF,0x80,0x00}},
 {LCM_SEND(6),{4,0,0xEA,0x15,0x28,0x00}},
 {LCM_SEND(7),{5,0,0xF0,0x38,0x00,0x00,0x00}},
 {LCM_SEND(6),{4,0,0xC9,0x60,0x00,0x82}},
 {LCM_SEND(11),{9,0,0xB5,0x00,0x05,0x05,0x1E,0x04,0x40,0x20,0xFC}},
 {LCM_SEND(2),{0x36,0x0B}},//08->0B rotate 180
 {LCM_SEND(2),{0x3A,0x70}},
 {LCM_SEND(1),{0x11}},
 {LCM_SLEEP(120)},
 {LCM_SEND(1),{0x29}},
 };


static LCM_Init_Code disp_on =  {LCM_SEND(1), {0x29}};

static LCM_Init_Code sleep_in =  {LCM_SEND(1), {0x10}};

static LCM_Init_Code sleep_out =  {LCM_SEND(1), {0x11}};

static int32_t ssd2075_mipi_init(struct panel_spec *self)
{
	int32_t i;
	LCM_Init_Code *init = init_data;
	unsigned int tag;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	LCD_PRINT("lcd_ssd2075_init\n");

	mipi_set_cmd_mode();
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
	mipi_eotp_set(1,1);

	return 0;
}

static uint32_t ssd2075_readid(struct panel_spec *self)
{
	int32_t i = 0;
	uint32 j =0;
	uint8_t read_data[10] = {0};
	int32_t read_rtn = 0;
	uint8_t param[2] = {0};
	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_force_write_t mipi_force_write = self->info.mipi->ops->mipi_force_write;
	mipi_force_read_t mipi_force_read = self->info.mipi->ops->mipi_force_read;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	LCD_PRINT("lcd_ssd2075_mipi read id!\n");
	mipi_set_cmd_mode();
	mipi_eotp_set(1,0);

	for(j = 0; j < 4; j++){
		param[0] = 0x0a;
		param[1] = 0x00;
		mipi_force_write(0x37, param, 2);
		read_rtn = mipi_force_read(0xA1,10,(uint8_t *)read_data);
		LCD_PRINT("lcd_ssd2075_mipi read id 0xA1 value is 0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x!\n", read_data[0], read_data[1], \
		read_data[2], read_data[3],read_data[4], read_data[5],read_data[6], read_data[7],read_data[8], read_data[9]);

		if((0x20 == read_data[0])&&(0x75 == read_data[1])){
			LCD_PRINT("lcd_ssd2075_mipi read id success!\n");
			mipi_eotp_set(1,1);
			return 0x2075;
		}
	}
	mipi_eotp_set(1,1);

	return 0;
}

static struct panel_operations lcd_ssd2075_mipi_operations = {
	.panel_init = ssd2075_mipi_init,
	.panel_readid = ssd2075_readid,
};

static struct timing_rgb lcd_ssd2075_mipi_timing = {
	.hfp =50,
	.hbp = 36,
	.hsync =16,
	.vfp = 12,
	.vbp = 14,
	.vsync = 2,
};


static struct info_mipi lcd_ssd2075_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 24, /*18,16*/
	.lan_number = 	4,
	.phy_feq =500*1000,
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_ssd2075_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_ssd2075_mipi_spec = {
	.width = 720,
	.height = 1280,
	.fps = 60,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.is_need_reset = 1,	/*need reset after the former panel init*/
	.info = {
		.mipi = &lcd_ssd2075_mipi_info
	},
	.ops = &lcd_ssd2075_mipi_operations,
};
