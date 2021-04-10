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

#define MAX_DATA   80//48
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

#if 1 //L505 1709
{LCM_SEND(2),{0x00,0x00}},//EXTC=1
{LCM_SEND(6),{4,0,0xff,0x12,0x89,0x01}},
{LCM_SEND(2),{0x00,0x80}},//CMD2 enable
{LCM_SEND(5),{3,0,0xff,0x12,0x89}},
{LCM_SEND(2),{0x00,0x90}},         //MIPI 4:0xb0, 3:0xa0, 2:0x90
{LCM_SEND(2),{0xff,0xb0}},
//-------------------- panel setting --------------------------------//
{LCM_SEND(2),{0x00,0x80}},             //TCON Setting
{LCM_SEND(11),{9,0,0xc0,0x4a,0x00,0x10,0x10,0x96,0x01,0x68,0x40}},
{LCM_SEND(2),{0x00,0x90}},             //Panel Timing Setting
{LCM_SEND(6),{4,0,0xc0,0x3b,0x01,0x09}},
{LCM_SEND(2),{0x00,0x8c}},             //column inversion
{LCM_SEND(2),{0xc0,0x00}},
{LCM_SEND(2),{0x00,0x80}},             //frame rate:60Hz
{LCM_SEND(2),{0xc1,0x33}},
//-------------------- power setting --------------------------------//
{LCM_SEND(2),{0x00,0x85}},             //VGH=7x, VGL=-5x, VGH=16V, VGL=-12V
{LCM_SEND(6),{4,0,0xc5,0x0a,0x0a,0x49}},
{LCM_SEND(2),{0x00,0x00}},             //GVDD=4.80V, NGVDD=-4.80V
{LCM_SEND(5),{3,0,0xd8,0x27,0x27}},     
//LCM_SEND(2),{0x00,0x00}},             //VCOM=-1.6V
//LCM_SEND(2),{0xd9,0x00,0x6a}},             
{LCM_SEND(2),{0x00,0x84}},             //chopper
{LCM_SEND(2),{0xC4,0x02}},
{LCM_SEND(2),{0x00,0x93}},             //pump option
{LCM_SEND(2),{0xC4,0x04}},
{LCM_SEND(2),{0x00,0x96}},             //VCL regulator
{LCM_SEND(2),{0xF5,0xE7}},
{LCM_SEND(2),{0x00,0xA0}},             //pump3 off
{LCM_SEND(2),{0xF5,0x4A}},
{LCM_SEND(2),{0x00,0x8a}},             //blank frame
{LCM_SEND(2),{0xc0,0x11}},
{LCM_SEND(2),{0x00,0x8b}}, //scan mode
{LCM_SEND(2),{0xc0,0x04}}, //01 05 04default
{LCM_SEND(2),{0x00,0x83}},             //vcom active
{LCM_SEND(2),{0xF5,0x81}},
//-------------------- for Power IC ----------------------------------//
{LCM_SEND(2),{0x00,0x90}},             //2xVPNL, x1.5=01, x2=05, x3=09
{LCM_SEND(5),{3,0,0xc4,0x96,0x05}},
//-------------------- panel timing state control --------------------//
{LCM_SEND(2),{0x00,0x80}},             //panel timing state control
{LCM_SEND(18),{16,0,0xcb,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x00,0x14,0x14,0x00,0x00,0x14}},
{LCM_SEND(2),{0x00,0x90}},             //panel timing state control
{LCM_SEND(10),{8,0,0xcb,0x14,0x00,0x00,0x00,0x00,0x00,0x00}},
//-------------------- panel pad mapping control ---------------------//
{LCM_SEND(2),{0x00,0x80}},             //panel timing state control
{LCM_SEND(17),{15,0,0xcc,0x06,0x1d,0x1e,0x1d,0x1d,0x10,0x0c,0x0e,0x0a,0x00,0x02,0x00,0x00,0x00}},
{LCM_SEND(2),{0x00,0x90}},             //panel timing state control
{LCM_SEND(18),{16,0,0xcc,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x1d,0x1e,0x1d,0x1d,0x0f,0x0b,0x0d}},
{LCM_SEND(2),{0x00,0xa0}},             //panel timing state control
{LCM_SEND(16),{14,0,0xcc,0x09,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00}},	
{LCM_SEND(2),{0x00,0xb0}},             //panel timing state control
{LCM_SEND(17),{15,0,0xcc,0x01,0x1e,0x1d,0x1d,0x1d,0x09,0x0d,0x0b,0x0f,0x00,0x05,0x00,0x00,0x00}},
{LCM_SEND(2),{0x00,0xc0}},             //panel timing state control
{LCM_SEND(18),{16,0,0xcc,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x1e,0x1d,0x1d,0x1d,0x0a,0x0e,0x0c}},
{LCM_SEND(2),{0x00,0xd0}},             //panel timing state control
{LCM_SEND(16),{14,0,0xcc,0x10,0x00,0x06,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00}},
//-------------------- panel timing setting --------------------------//
{LCM_SEND(2),{0x00,0x80}},             //panel VST setting
{LCM_SEND(9),{7,0,0xce,0x87,0x05,0x10,0x86,0x00,0x00}},
{LCM_SEND(2),{0x00,0x90}},             //panel VEND setting
{LCM_SEND(12),{10,0,0xce,0x34,0xff,0x10,0x05,0x00,0x00,0x00,0x00,0x00}},
{LCM_SEND(2),{0x00,0xa0}},             //panel CLKA setting
{LCM_SEND(18),{16,0,0xce,0x30,0x83,0x86,0x87,0x16,0x00,0x82,0x85,0x87,0x81,0x84,0x87,0x80,0x83,0x87}},
{LCM_SEND(2),{0x00,0xb0}},             //panel CLKB setting
{LCM_SEND(18),{16,0,0xce,0x30,0x00,0x82,0x87,0x16,0x00,0x01,0x81,0x87,0x02,0x80,0x87,0x03,0x00,0x87}},
{LCM_SEND(2),{0x00,0xF0}},                             
{LCM_SEND(9),{7,0,0xCE,0x01,0x20,0xC1,0x81,0x00,0x00}},
{LCM_SEND(2),{0x00,0x00}},
{LCM_SEND(19),{17,0,0xE1,0x1a,0x39,0x4a,0x59,0x66,0x7f,0x7a,0x8e,0x69,0x56,0x5f,0x47,0x2f,0x14,0x09,0x00}},
{LCM_SEND(2),{0x00,0x00}},
{LCM_SEND(19),{17,0,0xE2,0x1a,0x39,0x4a,0x59,0x66,0x7f,0x7a,0x8e,0x69,0x56,0x5f,0x47,0x2f,0x14,0x09,0x00}},
{LCM_SEND(2),{0x00,0x00}},             //CMD2 disable
{LCM_SEND(6),{4,0,0xff,0xff,0xff,0xff}},

{LCM_SEND(1), {0x11}},
{LCM_SLEEP(120)},
{LCM_SEND(1), {0x29}},
{LCM_SLEEP(20),},
#endif

};


static LCM_Init_Code disp_on =  {LCM_SEND(1), {0x29}};
static LCM_Init_Code sleep_in =  {LCM_SEND(1), {0x10}};
static LCM_Init_Code sleep_out =  {LCM_SEND(1), {0x11}};

static int32_t otm1289a_mipi_init(struct panel_spec *self)
{
	int32_t i;
	LCM_Init_Code *init = init_data;
	unsigned int tag;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	LCD_PRINT("otm1289a_mipi_init\n");

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

static uint32_t otm1289a_readid(struct panel_spec *self)
{
//	return 0x1283;
#if 1
	/*Jessica TODO: need read id*/
	int32_t i = 0;
	int32_t j =0;
	LCM_Force_Cmd_Code * rd_prepare = rd_prep_code;
	uint8_t read_data[5] = {0};
	int32_t read_rtn = 0;
	unsigned int tag = 0;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_force_write_t mipi_force_write = self->info.mipi->ops->mipi_force_write;
	mipi_force_read_t mipi_force_read = self->info.mipi->ops->mipi_force_read;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	LCD_PRINT("lcd_otm1289a_mipi read id!\n");

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
		LCD_PRINT("lcd_otm1289a_mipi read id 0xa1 value is 0x%x, 0x%x, 0x%x, 0x%x, 0x%x!\n",
			read_data[0], read_data[1], read_data[2], read_data[3], read_data[4]);

        mipi_eotp_set(1,1);

		if((0x01 == read_data[0])&&(0x8b == read_data[1])&&(0x12 == read_data[2])&&(0x89 == read_data[3])&&(0xff == read_data[4])){
			LCD_PRINT("lcd_otm1289a_mipi read id success!\n");
			return 0x128902;
		}
	}

	printk("lcd_otm1289a_mipi identify fail!\n");
	return 0x0;
#endif
}

static int32_t otm1289a_reset(struct panel_spec *self)
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

static struct panel_operations lcd_otm1289a_mipi_operations = {
	.panel_init = otm1289a_mipi_init,
	.panel_readid = otm1289a_readid,
	.panel_reset = otm1289a_reset,
};

static struct timing_rgb lcd_otm1289a_mipi_timing = {
	.hfp =32,
	.hbp = 4,
	.hsync =8,
	.vfp = 17,
	.vbp = 18,
	.vsync = 7,
};

static struct info_mipi lcd_otm1289a_mipi_info = {
	.work_mode				= SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width		= 24, /*18,16*/
#if 0 //def THREE_LANE_SUPPORT
	.lan_number				= 3,
	.phy_feq				= 550*1000,
#else
	.lan_number				= 4,
	.phy_feq				= 500*1000,
#endif
	.h_sync_pol				= SPRDFB_POLARITY_POS,
	.v_sync_pol				= SPRDFB_POLARITY_POS,
	.de_pol					= SPRDFB_POLARITY_POS,
	.te_pol					= SPRDFB_POLARITY_POS,
	.color_mode_pol			= SPRDFB_POLARITY_NEG,
	.shut_down_pol			= SPRDFB_POLARITY_NEG,
	.timing					= &lcd_otm1289a_mipi_timing,
	.ops					= NULL,
};

struct panel_spec lcd_otm1289a_kd_mipi_spec = {
	.width					= 720,
	.height					= 1280,
	.fps					= 60,
	.type					= LCD_MODE_DSI,
	.direction				= LCD_DIRECT_NORMAL,
	.is_need_reset = 1,	/*need reset after the former panel init*/
	.info = {
		.mipi				= &lcd_otm1289a_mipi_info
	},
	.ops					= &lcd_otm1289a_mipi_operations,
};



