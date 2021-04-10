/* drivers/video/sprdfb/lcd_jd9161_mipi.c
 *
 * Support for jd9161 mipi LCD device
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

#define LCD_ADC_CHANNEL 2

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
#define LCM_TAG_SEND  (1<< 0)
#define LCM_TAG_SLEEP (1 << 1)

static LCM_Init_Code init_data[] = {
	{LCM_SEND(6),{4,0,0xBF,0x91,0x61,0xF2}},
	{LCM_SEND(5),{3,0,0xB3,0x00,0x34}},
	{LCM_SEND(5),{3,0,0xB4,0x00,0x34}},
	{LCM_SEND(9),{7,0,0xB8,0x00,0xBF,0x01,0x00,0xBF,0x01 }},
	{LCM_SEND(6),{4,0,0xBA,0x3E,0x23,0x00}},
	{LCM_SEND(2),{0xC3,0x04}},
	{LCM_SEND(5),{3,0,0xC4,0x30,0x6A }},
	{LCM_SEND(12),{10,0,0xC7,0x00,0x01,0x31,0x0A,0x6A,0x2C,0x0F,0xA5,0xA5 }},
	{LCM_SEND(41),{39,0,0xC8,0x7F,0x60,0x4B,0x3B,0x33,0x22,0x25,0x0F,0x29,0x29,0x2B,0x4A,0x36,0x3A,0x28,0x21,0x14,0x07,0x00,0x7F,0x60,0x4B,0x3B,0x33,0x22,0x25,0x0F,0x29,0x29,0x2B,0x4A,0x36,0x3A,0x28,0x21,0x14,0x07,0x00}},
	{LCM_SEND(19),{17,0,0xD4,0x1F,0x1F,0x1F,0x03,0x01,0x05,0x07,0x09,0x0B,0x11,0x13,0x1F,0x1F,0x1F,0x1F,0x1F}},
	{LCM_SEND(19),{17,0,0xD5,0x1F,0x1F,0x1F,0x02,0x00,0x04,0x06,0x08,0x0A,0x10,0x12,0x1F,0x1F,0x1F,0x1F,0x1F}},
	{LCM_SEND(19),{17,0,0xD6,0x1F,0x1F,0x1F,0x10,0x12,0x04,0x0A,0x08,0x06,0x02,0x00,0x1F,0x1F,0x1F,0x1F,0x1F}},
	{LCM_SEND(19),{17,0,0xD7,0x1F,0x1F,0x1F,0x11,0x13,0x05,0x0B,0x09,0x07,0x03,0x01,0x1F,0x1F,0x1F,0x1F,0x1F}},
	{LCM_SEND(23),{21,0,0xD8,0x20,0x00,0x00,0x30,0x03,0x30,0x01,0x02,0x30,0x01,0x02,0x06,0x70,0x73,0x5D,0x72,0x06,0x38,0x70,0x08 }},
	{LCM_SEND(22),{20,0,0xD9,0x00,0x0A,0x0A,0x88,0x00,0x00,0x06,0x7B,0x00,0x80,0x00,0x3B,0x33,0x1F,0x00,0x00,0x00,0x06,0x70 }},
	{LCM_SEND(2),{0x35,0x00 }},
	{LCM_SEND(2),{0xBE,0x01}},
	{LCM_SEND(2),{0xC1,0x10}},
	{LCM_SEND(13),{11,0,0xCC,0x34,0x20,0x38,0x60,0x11,0x91,0x00,0x40,0x00,0x00}},
	{LCM_SEND(2),{0xBE,0x00}},
	{LCM_SEND(2),{0x11 ,0x00}},
	{LCM_SLEEP(120)},
	{LCM_SEND(2),{0x29,0x00}},
	{LCM_SLEEP(10)},
 };

static LCM_Force_Cmd_Code rd_prep_code[]={
	{0x39, {LCM_SEND(6), {4,0,0xBF,0x91,0x61,0xF2}}},
	{0x37, {LCM_SEND(2), {0x3, 0}}},
};

static LCM_Init_Code disp_on =  {LCM_SEND(1), {0x29}};

static LCM_Init_Code sleep_in =  {LCM_SEND(1), {0x10}};

static LCM_Init_Code sleep_out =  {LCM_SEND(1), {0x11}};

static int32_t jd9161_mipi_init(struct panel_spec *self)
{
	int32_t i;
	LCM_Init_Code *init = init_data;
	unsigned int tag;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;

	mipi_set_lp_mode_t mipi_set_lp_mode = self->info.mipi->ops->mipi_set_lp_mode;
	mipi_set_hs_mode_t mipi_set_hs_mode = self->info.mipi->ops->mipi_set_hs_mode;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;
	printk("uboot lcd_jd9161_init\n");
	mipi_set_lp_mode();
	//mipi_eotp_set(1,0);
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
	mipi_set_hs_mode();
	return 0;

}

static uint32_t jd9161_readid(struct panel_spec *self)
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
        mipi_set_lp_mode_t mipi_set_lp_mode = self->info.mipi->ops->mipi_set_lp_mode;
        mipi_set_hs_mode_t mipi_set_hs_mode = self->info.mipi->ops->mipi_set_hs_mode;
        mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	printk("uboot lcd_jd9161_mipi read id!\n");
	mipi_set_lp_mode();
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
		mdelay(50);
		read_rtn = mipi_force_read(0x04, 2,(uint8_t *)read_data);
		printk("lcd_jd9161_mipi read id 0x04 value is 0x%x,0x%x!\n", read_data[0],read_data[1]);

		if((read_data[0] ==0x91) || (read_data[1] ==0x6)){
			printk("lcd_jd9161_mipi read id success!\n");
			return 0x9161;
		}
	}
	return 0x0;
}

int32_t jd9161_reset(struct panel_spec *self)
{
	sprd_gpio_request(NULL, LCM_GPIO_RSTN);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 1);
	mdelay(5);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 0);
	mdelay(10);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 1);
	mdelay(120);

	return 0;
}

static struct panel_operations lcd_jd9161_mipi_operations = {
	.panel_init = jd9161_mipi_init,
	.panel_readid = jd9161_readid,
	.panel_reset = jd9161_reset,
};

static struct timing_rgb lcd_jd9161_mipi_timing = {
	.hfp = 10,  /* unit: pixel */// 100
	.hbp = 10,//80
	.hsync = 10,//6
	.vfp = 6, /*unit: line*/
	.vbp = 6,
	.vsync =4, //6,
};

static struct info_mipi lcd_jd9161_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 24, /*18,16*/
	.lan_number = 2,
	.phy_feq = 320*1000, //500->10MHz,400->8M in lp mode
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_jd9161_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_jd9161_mipi_spec = {
	.width = 480,
	.height = 854,
	.fps = 60,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.info = {
		.mipi = &lcd_jd9161_mipi_info
	},
	.ops = &lcd_jd9161_mipi_operations,
};


