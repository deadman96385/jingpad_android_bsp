/* drivers/video/sc8825/lcd_ili9881p_mipi.c
 *
 * Support for ili9881p mipi LCD device
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
{LCM_SEND(6),{4,0,0xFF,0x98,0x81,0x01}},
{LCM_SEND(2),{0x44,0x31}},

{LCM_SEND(6),{4,0,0xFF,0x98,0x81,0x05}},
{LCM_SEND(2),{0xB2,0x70}},
{LCM_SEND(2),{0x04,0x28}},
{LCM_SEND(2),{0x30,0xF7}},
{LCM_SEND(2),{0x29,0x00}},
{LCM_SEND(2),{0x2A,0x14}},
{LCM_SEND(2),{0x38,0xA8}},
{LCM_SEND(2),{0x1A,0x50}},
{LCM_SEND(2),{0x52,0x5F}},
{LCM_SEND(2),{0x54,0x28}},
{LCM_SEND(2),{0x55,0x25}},
{LCM_SEND(2),{0x26,0x02}},
{LCM_SEND(2),{0x3D,0xA1}},
{LCM_SEND(2),{0x1B,0x01}},

{LCM_SEND(6),{4,0,0xFF,0x98,0x81,0x02}},
{LCM_SEND(2),{0x42,0x2F}},
{LCM_SEND(2),{0x01,0x50}},
{LCM_SEND(2),{0x15,0x10}},

{LCM_SEND(2),{0x57,0x00}},
{LCM_SEND(2),{0x58,0x16}},
{LCM_SEND(2),{0x59,0x25}},
{LCM_SEND(2),{0x5A,0x13}},
{LCM_SEND(2),{0x5B,0x16}},
{LCM_SEND(2),{0x5C,0x29}},
{LCM_SEND(2),{0x5D,0x1D}},
{LCM_SEND(2),{0x5E,0x1F}},
{LCM_SEND(2),{0x5F,0x85}},
{LCM_SEND(2),{0x60,0x1E}},
{LCM_SEND(2),{0x61,0x2A}},
{LCM_SEND(2),{0x62,0x72}},
{LCM_SEND(2),{0x63,0x19}},
{LCM_SEND(2),{0x64,0x16}},
{LCM_SEND(2),{0x65,0x4A}},
{LCM_SEND(2),{0x66,0x21}},
{LCM_SEND(2),{0x67,0x28}},
{LCM_SEND(2),{0x68,0x4F}},
{LCM_SEND(2),{0x69,0x5D}},
{LCM_SEND(2),{0x6A,0x25}},
{LCM_SEND(2),{0x6B,0x00}},
{LCM_SEND(2),{0x6C,0x16}},
{LCM_SEND(2),{0x6D,0x25}},
{LCM_SEND(2),{0x6E,0x13}},
{LCM_SEND(2),{0x6F,0x16}},
{LCM_SEND(2),{0x70,0x29}},
{LCM_SEND(2),{0x71,0x1D}},
{LCM_SEND(2),{0x72,0x1F}},
{LCM_SEND(2),{0x73,0x85}},
{LCM_SEND(2),{0x74,0x1E}},
{LCM_SEND(2),{0x75,0x2A}},
{LCM_SEND(2),{0x76,0x72}},
{LCM_SEND(2),{0x77,0x19}},
{LCM_SEND(2),{0x78,0x16}},
{LCM_SEND(2),{0x79,0x4A}},
{LCM_SEND(2),{0x7A,0x21}},
{LCM_SEND(2),{0x7B,0x28}},
{LCM_SEND(2),{0x7C,0x4F}},
{LCM_SEND(2),{0x7D,0x5D}},
{LCM_SEND(2),{0x7E,0x25}},

{LCM_SEND(6),{4,0,0xFF,0x98,0x81,0x06}},
{LCM_SEND(2),{0x01,0x03}},
{LCM_SEND(2),{0x2B,0x0A}},

{LCM_SEND(6),{4,0,0xFF,0x98,0x81,0x00}},
{LCM_SEND(2),{0x35,0x00}},
{LCM_SEND(2),{0x11,0x00}},
{LCM_SLEEP(120)},
{LCM_SEND(2),{0x29,0x00}},
{LCM_SLEEP(20)},

};

static LCM_Force_Cmd_Code rd_prep_code[]={
	{0x39, {LCM_SEND(6), {0x4, 0, 0xFF, 0x98, 0x81,0x00}}},
	{0x37, {LCM_SEND(2), {0x3, 0}}},
};

static LCM_Init_Code disp_on =  {LCM_SEND(1), {0x29}};

static LCM_Init_Code sleep_in =  {LCM_SEND(1), {0x10}};

static LCM_Init_Code sleep_out =  {LCM_SEND(1), {0x11}};

static int32_t ili9881p_mipi_init(struct panel_spec *self)
{
	int32_t i;
	LCM_Init_Code *init = init_data;
	unsigned int tag;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;

	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;
	LCD_PRINT("lcd_ili9881p_init\n");

	mipi_set_cmd_mode();

	mipi_eotp_set(1,0);
	for(i = 0; i < ARRAY_SIZE(init_data); i++){
		tag = (init->tag >>24);
		if(tag & LCM_TAG_SEND){
			mipi_gen_write(init->data, (init->tag & LCM_TAG_MASK));
		}else if(tag & LCM_TAG_SLEEP){
			mdelay((init->tag & LCM_TAG_MASK));
		}
		init++;
	}

	mipi_eotp_set(1,1);
	return 0;
}

//extern uint32_t load_lcd_adc_to_kernel();
static uint32_t ili9881p_readid(struct panel_spec *self)
{
#if 1
	/*Jessica TODO: need read id*/
	int32_t i = 0;
	uint32_t j =0;
	uint32_t lcd_adc =0;
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

	//return  0x988101;
	printk("lcd_ili9881p_mipi read id!\n");
	//mipi_set_lp_mode();

	mipi_set_cmd_mode();
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
		mdelay(50);
		read_rtn = mipi_force_read(0x04, 3,(uint8_t *)read_data);
//		lcd_adc = load_lcd_adc_to_kernel();
		printk("lcd_ili9881p_mipi read id 0x02 value is 0x%x  lcd_adc %d!\n", read_data[0], lcd_adc);

		if((0x00 == read_data[0]) && (0x80 == read_data[1])  && (0x00 == read_data[2]) ){ // && (lcd_adc > 300) && (lcd_adc < 700) //504
			printk("lcd_ili9881p_mipi read id success!\n");
			return 0x988103;
		}
	}

	mdelay(5);
	//mipi_set_hs_mode();
#endif
	return 0x00;
}

static int32_t ili9881p_reset(struct panel_spec *self)
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

static struct panel_operations lcd_ili9881p_mipi_operations = {
	.panel_init = ili9881p_mipi_init,
	.panel_readid = ili9881p_readid,
	.panel_reset = ili9881p_reset,
};

static struct timing_rgb lcd_ili9881p_mipi_timing = {
#if 0
	.hfp = 84,  /* unit: pixel */// 100
	.hbp = 40,//80
	.hsync = 10,//6
	.vfp = 25, /*unit: line*/
	.vbp = 20,
	.vsync =8, //6,
#endif
#if   1
	.hfp = 60,//80,  /* unit: pixel */// 100
	.hbp = 40,//120,//80
	.hsync = 10, //20,//6
	.vfp = 18,//20, /*unit: line*/
	.vbp = 16,//18,
	.vsync = 6,//8, //6,
#endif
};

static struct info_mipi lcd_ili9881p_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 24, /*18,16*/
	.lan_number = 4,
	.phy_feq = 464*1000,    //488
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_ili9881p_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_ili9881p_mipi_spec = {
	//.cap = PANEL_CAP_NOT_TEAR_SYNC,
	.width = 720,
	.height = 1280,
	.fps = 60,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.is_need_reset = 1,	/*need reset after the former panel init*/
	.info = {
		.mipi = &lcd_ili9881p_mipi_info
	},
	.ops = &lcd_ili9881p_mipi_operations,
};


