/* drivers/video/sprdfb/lcd_otm8019a_mipi.c
 *
 * Support for otm8019a mipi LCD device
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

#define printk printf

#define  LCD_DEBUG
//#define THREE_LANE_SUPPORT

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


static LCM_Force_Cmd_Code rd_prep_code[]={
	{0x37, {LCM_SEND(2), {0x5, 0}}},
};

static LCM_Init_Code init_data[] = {
		{LCM_SEND(2),{0x00,0x00}},
		{LCM_SEND(6),{4,0,0xFF,0x80,0x19,0x01}},
	
		{LCM_SEND(2),{0x00,0x80}},
		{LCM_SEND(5),{3,0,0xFF,0x80,0x19}},
	
		{LCM_SEND(2),{0x00,0x03}},
		{LCM_SEND(2),{0xFF,0x01}},
	
		{LCM_SEND(2),{0x00,0x00}},
		{LCM_SEND(5),{3,0,0xD8,0x6F,0x6F}},//7F
	
		{LCM_SEND(2),{0x00,0x82}},
		{LCM_SEND(2),{0xC5,0xB0}},
	
		{LCM_SEND(2),{0x00,0xA1}},
		{LCM_SEND(2),{0xC1,0x08}},
	
		{LCM_SEND(2),{0x00,0xA3}},
		{LCM_SEND(2),{0xC0,0x1B}},
	
		{LCM_SEND(2),{0x00,0xB4}},
		{LCM_SEND(2),{0xC0,0x77}},
	
		{LCM_SEND(2),{0x00,0x81}},
		{LCM_SEND(2),{0xC4,0x83}},
	
		{LCM_SEND(2),{0x00,0x90}},
		{LCM_SEND(6),{4,0,0xC5,0x4E,0xA7,0x01}},
	
		{LCM_SEND(2),{0x00,0xB1}},
		{LCM_SEND(2),{0xC5,0xA9}},
	
		{LCM_SEND(2),{0x00,0x00}},
		{LCM_SEND(2),{0xD9,0x17}},
	
	//***************Gamma 2.2********************
		{LCM_SEND(2),{0x00,0x00}},
		{LCM_SEND(23),{21,0,0xE1,0x00,0x10,0x22,0x38,0x50,0x62,0x67,0x92,0x7f,0x94,0x75,0x65,0x7e,0x6c,0x72,0x6c,0x65,0x5d,0x53,0x02}},
	
		{LCM_SEND(2),{0x00,0x00}},
		{LCM_SEND(23),{21,0,0xE2,0x00,0x10,0x22,0x38,0x50,0x62,0x67,0x92,0x7f,0x94,0x75,0x65,0x7e,0x6c,0x72,0x6c,0x65,0x5d,0x53,0x02}},
	//******************************************** 
	//***************Gamma 2.5********************
		{LCM_SEND(2),{0x00,0x00}},
		{LCM_SEND(23),{21,0,0xE1,0x00,0x02,0x07,0x12,0x22,0x37,0x41,0x78,0x6b,0x85,0x7f,0x6b,0x82,0x6b,0x71,0x69,0x61,0x58,0x4c,0x00}},
	
		{LCM_SEND(2),{0x00,0x00}},
		{LCM_SEND(23),{21,0,0xE2,0x00,0x02,0x07,0x12,0x22,0x37,0x41,0x78,0x6b,0x85,0x7f,0x6b,0x82,0x6b,0x71,0x69,0x61,0x58,0x4c,0x00}},
	//******************************************** 
	
		{LCM_SEND(2),{0x00,0xA7}},
		{LCM_SEND(2),{0xB3,0x00}},
	
		{LCM_SEND(2),{0x00,0x92}},
		{LCM_SEND(2),{0xB3,0x45}},
	
		{LCM_SEND(2),{0x00,0x90}},
		{LCM_SEND(2),{0xB3,0x02}},
	
		{LCM_SEND(2),{0x00,0x00}},
		{LCM_SEND(2),{0x36,0x00}},
	
		{LCM_SEND(2),{0x00,0x90}},
		{LCM_SEND(9),{7,0,0xC0,0x00,0x15,0x00,0x00,0x00,0x03}},
	
		{LCM_SEND(2),{0x00,0xA0}},
		{LCM_SEND(2),{0xC1,0xE8}},
	
		{LCM_SEND(2),{0x00,0xA6}},
		{LCM_SEND(6),{4,0,0xC1,0x01,0x00,0x00}},
	
		{LCM_SEND(2),{0x00,0x80}},
	//	{LCM_SEND(9),{7,0,0xCE,0x87,0x03,0x00,0x86,0x03,0x00}},
		{LCM_SEND(9),{7,0,0xCE,0x87,0x05,0x14,0x86,0x05,0x14}},
		{LCM_SLEEP(2),},
	
		{LCM_SEND(2),{0x00,0x90}},
		{LCM_SEND(9),{7,0,0xCE,0x33,0x54,0x14,0x33,0x55,0x14}},
		{LCM_SLEEP(2),},
	
		{LCM_SEND(2),{0x00,0xA0}},
		{LCM_SEND(17),{15,0,0xCE,0x38,0x03,0x03,0x58,0x00,0x14,0x00,0x38,0x02,0x03,0x59,0x00,0x14,0x00}},
		{LCM_SLEEP(2),},
	
		{LCM_SEND(2),{0x00,0xB0}},
		{LCM_SEND(17),{15,0,0xCE,0x38,0x01,0x03,0x5A,0x00,0x14,0x00,0x38,0x00,0x03,0x5B,0x00,0x14,0x00}},
		{LCM_SLEEP(2),},
	
		{LCM_SEND(2),{0x00,0xC0}},
		{LCM_SEND(17),{15,0,0xCE,0x30,0x00,0x03,0x5C,0x00,0x14,0x00,0x30,0x01,0x03,0x5D,0x00,0x14,0x00}},
		{LCM_SLEEP(2),},
	
		{LCM_SEND(2),{0x00,0xD0}},
		{LCM_SEND(17),{15,0,0xCE,0x38,0x05,0x03,0x5E,0x00,0x14,0x00,0x38,0x04,0x03,0x5F,0x00,0x14,0x00}},
		{LCM_SLEEP(2),},
	
		{LCM_SEND(2),{0x00,0xC0}},
	//	{LCM_SEND(13),{11,0,0xCF,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x80,0x00,0x09}},
		{LCM_SEND(13),{11,0,0xCF,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00}},
	
		{LCM_SEND(2),{0x00,0xC0}},
		{LCM_SEND(18),{16,0,0xCB,0x00,0x01,0x01,0x01,0x01,0x00,0x00,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00}},
	
		{LCM_SEND(2),{0x00,0xD0}},
		{LCM_SEND(18),{16,0,0xCB,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x00}},
	
		{LCM_SEND(2),{0x00,0xE0}},
		{LCM_SEND(13),{11,0,0xCB,0x00,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00}},
	
		{LCM_SEND(2),{0x00,0x80}},
		{LCM_SEND(13),{11,0,0xCC,0x00,0x26,0x25,0x02,0x06,0x00,0x00,0x0A,0x0E,0x0C}},
	
		{LCM_SEND(2),{0x00,0x90}},
		{LCM_SEND(18),{16,0,0xCC,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	
		{LCM_SEND(2),{0x00,0xA0}},
		{LCM_SEND(18),{16,0,0xCC,0x0f,0x0b,0x0d,0x09,0x00,0x00,0x05,0x01,0x25,0x26,0x00,0x00,0x00,0x00,0x00}},
	
		{LCM_SEND(2),{0x00,0xB0}},
		{LCM_SEND(13),{11,0,0xCC,0x00,0x25,0x26,0x05,0x01,0x00,0x00,0x0D,0x09,0x0B}},
	
		{LCM_SEND(2),{0x00,0xC0}},
		{LCM_SEND(18),{16,0,0xCC,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	
		{LCM_SEND(2),{0x00,0xD0}},
		{LCM_SEND(18),{16,0,0xCC,0x10,0x0c,0x0a,0x0e,0x00,0x00,0x02,0x06,0x26,0x25,0x00,0x00,0x00,0x00,0x00}},
	
	//-----------------AUTO SHIFT-------------------
		{LCM_SEND(2),{0x00,0x98}},
		{LCM_SEND(2),{0xC0,0x00}},
		{LCM_SEND(2),{0x00,0xA9}},
		{LCM_SEND(2),{0xC0,0x06}},
		{LCM_SEND(2),{0x00,0xB0}},
		{LCM_SEND(6),{4,0,0xC1,0x20,0x00,0x00}},
		{LCM_SEND(2),{0x00,0xE1}},
		{LCM_SEND(5),{3,0,0xC0,0x40,0x18}},
	//----------------------------------------------
		{LCM_SEND(2),{0x00,0x80}},
		{LCM_SEND(2),{0xC4,0x30}}, //source blanking area=GND
	
		{LCM_SEND(2),{0x00,0x80}},
		{LCM_SEND(5),{3,0,0xC1,0x03,0x33}},
	
		{LCM_SEND(2),{0x00,0x90}},
		{LCM_SEND(2),{0xB6,0xB4}},//command fial
		{LCM_SLEEP(10),},
	
		{LCM_SEND(2),{0x00,0x94}},
		{LCM_SEND(2),{0xC5,0x66}},
	
		{LCM_SEND(2),{0x00,0x00}},
		{LCM_SEND(2),{4,0,0xFF,0xFF,0xFF,0xFF}},
	
		{LCM_SEND(2), {0x11,0x00}}, // sleep out
		{LCM_SLEEP(120)},
		{LCM_SEND(2), {0x29,0x00}}, // display on
		{LCM_SLEEP(5),}, //30,100
};


static LCM_Init_Code disp_on =  {LCM_SEND(1), {0x29}};
static LCM_Init_Code sleep_in =  {LCM_SEND(1), {0x10}};
static LCM_Init_Code sleep_out =  {LCM_SEND(1), {0x11}};

static int32_t otm8019a_mipi_init(struct panel_spec *self)
{
	int32_t i;
	LCM_Init_Code *init = init_data;
	unsigned int tag;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	LCD_PRINT("otm8019a_mipi_init\n");

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

static uint32_t otm8019a_readid(struct panel_spec *self)
{
	/*Jessica TODO: need read id*/
	int32_t i = 0;
	uint32_t j =0;
	LCM_Force_Cmd_Code * rd_prepare = rd_prep_code;
	uint8_t read_data[5] = {0};
	int32_t read_rtn = 0;
	unsigned int tag = 0;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_force_write_t mipi_force_write = self->info.mipi->ops->mipi_force_write;
	mipi_force_read_t mipi_force_read = self->info.mipi->ops->mipi_force_read;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	LCD_PRINT("lcd_otm8019a_mipi read id!\n");
	//return 0x8019;

	mipi_set_cmd_mode();
	mipi_eotp_set(1,0);

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

		read_rtn = mipi_force_read(0xa1, 5,(uint8_t *)read_data);
		LCD_PRINT("lcd_otm8019a_mipi read id 0xa1 value is 0x%x, 0x%x, 0x%x, 0x%x, 0x%x!\n",
			read_data[0], read_data[1], read_data[2], read_data[3], read_data[4]);

                mipi_eotp_set(1,1);

		if((0x01 == read_data[0])&&(0x8b == read_data[1])&&(0x80 == read_data[2])&&(0x19 == read_data[3])&&(0xff == read_data[4])){
			LCD_PRINT("lcd_otm8019a_mipi read id success!\n");
			return 0x8019;
		}
	}

	printk("lcd_otm8019a_mipi identify fail!\n");
	return 0x0;
}

static struct panel_operations lcd_otm8019a_mipi_operations = {
	.panel_init = otm8019a_mipi_init,
	.panel_readid = otm8019a_readid,
};

static struct timing_rgb lcd_otm8019a_mipi_timing = {
	.hfp =48,
	.hbp = 48,
	.hsync =8,
	.vfp = 16,
	.vbp = 16,
	.vsync = 8,
};

static struct info_mipi lcd_otm8019a_mipi_info = {
	.work_mode				= SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width		= 24, /*18,16*/
	.lan_number				= 2,
	.phy_feq				= 500*1000,
	.h_sync_pol				= SPRDFB_POLARITY_POS,
	.v_sync_pol				= SPRDFB_POLARITY_POS,
	.de_pol					= SPRDFB_POLARITY_POS,
	.te_pol					= SPRDFB_POLARITY_POS,
	.color_mode_pol			= SPRDFB_POLARITY_NEG,
	.shut_down_pol			= SPRDFB_POLARITY_NEG,
	.timing					= &lcd_otm8019a_mipi_timing,
	.ops					= NULL,
};

struct panel_spec lcd_otm8019a_mipi_spec = {
	.width					= 480,
	.height					= 854,
	.fps					= 60,
	.type					= LCD_MODE_DSI,
	.direction				= LCD_DIRECT_NORMAL,
	.info = {
		.mipi				= &lcd_otm8019a_mipi_info
	},
	.ops					= &lcd_otm8019a_mipi_operations,
};



