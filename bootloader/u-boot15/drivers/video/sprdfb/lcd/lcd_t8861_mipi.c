/* drivers/video/sprdfb/lcd/lcd_t8861_mipi.c
 *
 * Support for t8861 mipi LCD device
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

#include <asm/arch/sprd_lcd.h>
#include "../sprdfb.h"

#define printk printf

//#define  LCD_DEBUG
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

	{LCM_SEND(8), {6, 0,0xFF,0xFF,0x98,0x06,0x04,0x01}},
	{LCM_SLEEP(5)},

	{LCM_SEND(2), {0x08,0x10}},

	{LCM_SEND(2), {0x21,0x01}},

	{LCM_SEND(2), {0x30,0x02}},
	{LCM_SEND(2), {0x31,0x00}}, //0x02

	{LCM_SEND(2), {0x60,0x07}},
	{LCM_SEND(2), {0x61,0x06}},
	{LCM_SEND(2), {0x62,0x06}},
	{LCM_SEND(2), {0x63,0x04}},

	{LCM_SEND(2), {0x40,0x14}},
	{LCM_SEND(2), {0x41,0x44}},//22
	{LCM_SEND(2), {0x42,0x01}},
	{LCM_SEND(2), {0x43,0x89}},
	{LCM_SEND(2), {0x44,0x89}},
	{LCM_SEND(2), {0x45,0x1b}},
	{LCM_SEND(2), {0x46,0x44}},
	{LCM_SEND(2), {0x47,0x44}},

	{LCM_SEND(2), {0x50,0x85}},
	{LCM_SEND(2), {0x51,0x85}},
	{LCM_SEND(2), {0x52,0x00}},
	{LCM_SEND(2), {0x53,0x64}},//90
	
	//{LCM_SEND(8), {6, 0,0xFF,0xFF,0x98,0x06,0x04,0x01}},

	{LCM_SEND(2), {0xA0,0x00}},
	{LCM_SEND(2), {0xA1,0x00}},//01
	{LCM_SEND(2), {0xA2,0x03}},//08
	{LCM_SEND(2), {0xA3,0x0e}},//0e
	{LCM_SEND(2), {0xA4,0x08}},//08
	{LCM_SEND(2), {0xA5,0x1f}},//19
	{LCM_SEND(2), {0xA6,0x0f}},//0b
	{LCM_SEND(2), {0xA7,0x0b}},//0a
	{LCM_SEND(2), {0xA8,0x03}},//02
	{LCM_SEND(2), {0xA9,0x06}},//08
	{LCM_SEND(2), {0xAA,0x05}},//04
	{LCM_SEND(2), {0xAB,0x02}},//03
	{LCM_SEND(2), {0xAC,0x0e}},//0a
	{LCM_SEND(2), {0xAD,0x25}},//2c
	{LCM_SEND(2), {0xAE,0x1d}},//28
	{LCM_SEND(2), {0xAF,0x00}},

	{LCM_SEND(2), {0xC0,0x00}},//00
	{LCM_SEND(2), {0xC1,0x04}},//02
	{LCM_SEND(2), {0xC2,0x0f}},//09
	{LCM_SEND(2), {0xC3,0x10}},//0e
	{LCM_SEND(2), {0xC4,0x0b}},//09
	{LCM_SEND(2), {0xC5,0x1e}},//19
	{LCM_SEND(2), {0xC6,0x09}},//0a
	{LCM_SEND(2), {0xC7,0x0a}},//0a
	{LCM_SEND(2), {0xC8,0x00}},//02
	{LCM_SEND(2), {0xC9,0x0a}},//07
	{LCM_SEND(2), {0xCA,0x01}},//05
	{LCM_SEND(2), {0xCB,0x06}},//04
	{LCM_SEND(2), {0xCC,0x09}},//0a
	{LCM_SEND(2), {0xCD,0x2a}},//2d
	{LCM_SEND(2), {0xCE,0x28}},//28
	{LCM_SEND(2), {0xCF,0x00}},//00
	
	{LCM_SEND(8), {6, 0,0xFF,0xFF,0x98,0x06,0x04,0x06}},
	{LCM_SEND(2), {0x00,0xa0}},
	{LCM_SEND(2), {0x01,0x05}},
	{LCM_SEND(2), {0x02,0x00}},
	{LCM_SEND(2), {0x03,0x00}},
	{LCM_SEND(2), {0x04,0x01}},
	{LCM_SEND(2), {0x05,0x01}},
	{LCM_SEND(2), {0x06,0x88}},
	{LCM_SEND(2), {0x07,0x04}},
	{LCM_SEND(2), {0x08,0x01}},
	{LCM_SEND(2), {0x09,0x90}},
	{LCM_SEND(2), {0x0A,0x04}},
	{LCM_SEND(2), {0x0B,0x01}},
	{LCM_SEND(2), {0x0C,0x01}},
	{LCM_SEND(2), {0x0D,0x01}},
	{LCM_SEND(2), {0x0E,0x00}},
	{LCM_SEND(2), {0x0F,0x00}},

	{LCM_SEND(2), {0x10,0x55}},
	{LCM_SEND(2), {0x11,0x50}},
	{LCM_SEND(2), {0x12,0x01}},
	{LCM_SEND(2), {0x13,0x85}},
	{LCM_SEND(2), {0x14,0x85}},
	{LCM_SEND(2), {0x15,0xc0}},
	{LCM_SEND(2), {0x16,0x0B}},
	{LCM_SEND(2), {0x17,0x00}},
	{LCM_SEND(2), {0x18,0x00}},
	{LCM_SEND(2), {0x19,0x00}},
	{LCM_SEND(2), {0x1A,0x00}},
	{LCM_SEND(2), {0x1B,0x00}},
	{LCM_SEND(2), {0x1C,0x00}},
	{LCM_SEND(2), {0x1D,0x00}},

	{LCM_SEND(2), {0x20,0x01}},
	{LCM_SEND(2), {0x21,0x23}},
	{LCM_SEND(2), {0x22,0x45}},
	{LCM_SEND(2), {0x23,0x67}},
	{LCM_SEND(2), {0x24,0x01}},
	{LCM_SEND(2), {0x25,0x23}},
	{LCM_SEND(2), {0x26,0x45}},
	{LCM_SEND(2), {0x27,0x67}},

	{LCM_SEND(2), {0x30,0x02}},
	{LCM_SEND(2), {0x31,0x22}},
	{LCM_SEND(2), {0x32,0x11}},
	{LCM_SEND(2), {0x33,0xaa}},
	{LCM_SEND(2), {0x34,0xbb}},
	{LCM_SEND(2), {0x35,0x66}},
	{LCM_SEND(2), {0x36,0x00}},
	{LCM_SEND(2), {0x37,0x22}},
	{LCM_SEND(2), {0x38,0x22}},
	{LCM_SEND(2), {0x39,0x22}},
	{LCM_SEND(2), {0x3A,0x22}},
	{LCM_SEND(2), {0x3B,0x22}},
	{LCM_SEND(2), {0x3C,0x22}},
	{LCM_SEND(2), {0x3D,0x22}},
	{LCM_SEND(2), {0x3E,0x22}},
	{LCM_SEND(2), {0x3F,0x22}},

	{LCM_SEND(2), {0x40,0x22}},
	{LCM_SEND(2), {0x53,0x1a}},
	
	{LCM_SEND(8), {6, 0,0xFF,0xFF,0x98,0x06,0x04,0x07}},
	{LCM_SEND(2), {0x18,0x1d}},
	{LCM_SEND(2), {0x17,0x12}},

	{LCM_SEND(2), {0x02,0x77}},
	
	{LCM_SEND(2), {0xe1,0x79}},
	
	{LCM_SEND(2), {0x06,0x13}},

	{LCM_SEND(8), {6, 0,0xFF,0xFF,0x98,0x06,0x04,0x00}},
	
//	{LCM_SEND(2), {0x35,0x00}},

	{LCM_SEND(1), {0x11}}, 	
	{LCM_SLEEP(120)},

	{LCM_SEND(1), {0x29}},
	{LCM_SLEEP(1)},
	
//	{LCM_SEND(8), {6, 0,0xFF,0xFF,0x98,0x06,0x04,0x08}},
	
};

static LCM_Force_Cmd_Code rd_prep_code[]={
	{0x39, {LCM_SEND(8), {0x6, 0, 0xFF, 0xFF, 0x98, 0x06,0x04,0x01}}},
	{0x37, {LCM_SEND(2), {0x3, 0}}},
};

static LCM_Init_Code disp_on =  {LCM_SEND(1), {0x29}};

static LCM_Init_Code sleep_in =  {LCM_SEND(1), {0x10}};

static LCM_Init_Code sleep_out =  {LCM_SEND(1), {0x11}};

static int32_t t8861_mipi_init(struct panel_spec *self)
{
	int32_t i;
	LCM_Init_Code *init = init_data;
	unsigned int tag;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;

     mipi_set_lp_mode_t mipi_set_lp_mode = self->info.mipi->ops->mipi_set_lp_mode;
     mipi_set_hs_mode_t mipi_set_hs_mode = self->info.mipi->ops->mipi_set_hs_mode;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;
	LCD_PRINT("lcd_t8861_init\n");

	//mipi_set_cmd_mode();
	
	udelay(5000);	
	mipi_set_lp_mode();
	//mipi_eotp_set(1,0);
	for(i = 0; i < ARRAY_SIZE(init_data); i++){
		tag = (init->tag >>24);
		if(tag & LCM_TAG_SEND){
			mipi_gen_write(init->data, (init->tag & LCM_TAG_MASK));
			udelay(20);
		}else if(tag & LCM_TAG_SLEEP){
			udelay((init->tag & LCM_TAG_MASK) * 1000);
		}
		init++;
	}
	
	udelay(5000);	
	mipi_set_hs_mode();
	return 0;
}

static uint32_t t8861_readid(struct panel_spec *self)
{
	/*Jessica TODO: need read id*/
	int32_t i = 0;
	uint32 j =0;
	LCM_Force_Cmd_Code * rd_prepare = rd_prep_code;
	uint8_t read_data[3] = {0};
	int32_t read_rtn = 0;
	unsigned int tag = 0;
	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_force_write_t mipi_force_write = self->info.mipi->ops->mipi_force_write;
	mipi_force_read_t mipi_force_read = self->info.mipi->ops->mipi_force_read;
     mipi_set_lp_mode_t mipi_set_lp_mode = self->info.mipi->ops->mipi_set_lp_mode;
     mipi_set_hs_mode_t mipi_set_hs_mode = self->info.mipi->ops->mipi_set_hs_mode;
     mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;
     
	//return 0x6; //cg liyun 20130329

	printk("lcd_t8861_mipi read id!\n");
	mipi_set_lp_mode();

	//mipi_set_cmd_mode();
	for(j = 0; j < 4; j++){
		rd_prepare = rd_prep_code;
		for(i = 0; i < ARRAY_SIZE(rd_prep_code); i++){
			tag = (rd_prepare->real_cmd_code.tag >> 24);
			if(tag & LCM_TAG_SEND){
				mipi_force_write(rd_prepare->datatype, rd_prepare->real_cmd_code.data, (rd_prepare->real_cmd_code.tag & LCM_TAG_MASK));
			}else if(tag & LCM_TAG_SLEEP){
				udelay((rd_prepare->real_cmd_code.tag & LCM_TAG_MASK) * 1000);
			}
			rd_prepare++;
		}
		udelay(50000);	
		read_rtn = mipi_force_read(0x02, 1,(uint8_t *)read_data);
		printk("lcd_t8861_mipi read id 0x02 value is 0x%x!\n", read_data[0]);

		if((0x04 == read_data[0])){
			printk("lcd_t8861_mipi read id success!\n");
			return 0x04;
		}
	}
	
	udelay(5000);	
	mipi_set_hs_mode();
	return 0;
}

static struct panel_operations lcd_t8861_mipi_operations = {
	.panel_init = t8861_mipi_init,
	.panel_readid = t8861_readid,
};

static struct timing_rgb lcd_t8861_mipi_timing = {
	.hfp = 60,  /* unit: pixel */// 100
	.hbp = 80,//80
	.hsync = 60,//6
	.vfp = 20, /*unit: line*/
	.vbp = 14,
	.vsync =6, //6,
};

static struct info_mipi lcd_t8861_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 24, /*18,16*/
	.lan_number = 2,
	.phy_feq = 500*1000,
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_t8861_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_t8861_mipi_spec = {
	//.cap = PANEL_CAP_NOT_TEAR_SYNC,
	.width = 480,
	.height = 800,
	.fps = 60,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.info = {
		.mipi = &lcd_t8861_mipi_info
	},
	.ops = &lcd_t8861_mipi_operations,
};


