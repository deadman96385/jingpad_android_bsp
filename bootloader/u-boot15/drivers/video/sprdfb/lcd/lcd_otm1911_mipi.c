/* drivers/video/sprdfb/lcd_nt35597_mipi.c
 *
 * Support for nt35532 mipi LCD device
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

#define MAX_DATA   10

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

{LCM_SEND(2),{0x00,0x00}},
{LCM_SEND(6),{4,0,0xFF,0x19,0x11,0x01}},
{LCM_SLEEP(10)},
{LCM_SEND(2),{0x00,0x80}},
{LCM_SEND(5),{3,0,0xFF,0x19,0x11}},

{LCM_SEND(2),{0x00,0xB0}},
{LCM_SEND(2),{0xCA,0x00}},
{LCM_SEND(2),{0x00,0xB5}},
{LCM_SEND(2),{0xCA,0x04}},
{LCM_SEND(2),{0x00,0xB2}},
{LCM_SEND(2),{0xCA,0x0A}},

{LCM_SEND(2),{0x00,0x00}},
{LCM_SEND(6),{4,0,0xFF,0x00,0x00,0x00}},
{LCM_SLEEP(10)},

{LCM_SEND(5),{3,0,0x51,0x00,0x00}},
{LCM_SLEEP(5)},
{LCM_SEND(2),{0x53,0x2c}},
{LCM_SLEEP(5)},
{LCM_SEND(2),{0x55,0x01}},
{LCM_SLEEP(5)},

{LCM_SEND(1),{0x11}},
{LCM_SLEEP(150)},

{LCM_SEND(1),{0x29}},
{LCM_SLEEP(200)},
};


static LCM_Force_Cmd_Code rd_prep_code[]={
	{0x37, {LCM_SEND(2), {0x3, 0}}},
};

static int32_t otm1911_mipi_init(struct panel_spec *self)
{
	int32_t i = 0;
	LCM_Init_Code *init = init_data;
	unsigned int tag;
	mipi_set_lp_mode_t mipi_set_lp_mode = self->info.mipi->ops->mipi_set_lp_mode;/* u-boot\arch\arm\include\asm\arch\sprd_lcd.h */
	mipi_set_hs_mode_t mipi_set_hs_mode = self->info.mipi->ops->mipi_set_hs_mode;
	mipi_set_video_mode_t mipi_set_video_mode = self->info.mipi->ops->mipi_set_video_mode;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;
	LCD_PRINT("sprdfb:otm1911_mipi_init\n");

	mipi_set_lp_mode();
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
	mipi_set_hs_mode();
	mipi_set_video_mode();
	return 0;
}

static uint32_t otm1911_readid(struct panel_spec *self)
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

	LCD_PRINT("sprdfb:lcd_otm1911_mipi read id!\n");

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
		read_rtn = mipi_force_read(0xDA, 1,(uint8_t *)read_data);
		printk("lcd_otm1911_mipi read id 0xDA value is 0x%x, 0x%x, 0x%x!\n", read_data[0], read_data[1], read_data[2]);

		if(0x40 == read_data[0]){
			printk("lcd_otm1911_mipi read id success!\n");
			mipi_eotp_set(1,1);
			i2c_set_bus_num(3); //iwhale2 5
			read_rtn = i2c_reg_read(0x3E, 0x00);
			printk("lcd_otm1911_mipi read i2c read_rtn 0x%x\n", read_rtn);
			
			if (0x0A != read_rtn) {
				i2c_reg_write(0x3E, 0x00, 0x0A);
				i2c_reg_write(0x3E, 0x01, 0x0A);
				i2c_reg_write(0x3E, 0x03, 0x03);
				i2c_reg_write(0x3E, 0xFF, 0x80);
				mdelay(50);
			}
			return 0x1911;
		}
	}
	mipi_eotp_set(1,1);
	return 0x0;
}

int32_t otm1911_reset(struct panel_spec *self)
{
	sprd_gpio_request(NULL, 40);
	sprd_gpio_direction_output(NULL, 40, 1);
	mdelay(10);

	sprd_gpio_request(NULL, 41);
	sprd_gpio_direction_output(NULL, 41, 1);
	mdelay(20);

	sprd_gpio_request(NULL, LCM_GPIO_RSTN);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 1);
	mdelay(20);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 0);
	mdelay(50);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 1);
	mdelay(50);

	return 0;
}

static unsigned char set_bl_seq[] = {
	0x51, 0xFF
};

int32_t otm1911_set_brightness(struct panel_spec *self,uint16_t brightness)
{
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;
	set_bl_seq[1] = brightness;
	mipi_gen_write(&set_bl_seq[0], 2);
}

static struct panel_operations lcd_otm1911_mipi_operations = {
	.panel_init = otm1911_mipi_init,
	.panel_readid = otm1911_readid,
	.panel_reset = otm1911_reset,
	.panel_set_brightness = otm1911_set_brightness,
};

static struct timing_rgb lcd_otm1911_mipi_timing = {
	.hfp = 143,  /* unit: pixel */
	.hbp = 37,//80
	.hsync = 20,//4//10
	.vfp = 50, /*unit: line*/
	.vbp = 26,//32
	.vsync = 4,//4//4
};

static struct info_mipi lcd_otm1911_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 24, /*18,16*/
	.lan_number = 4,
	.phy_feq = 9798*100,
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_otm1911_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_otm1911_mipi_spec = {
	.width = 1080,
	.height = 1920,
	.fps = 60,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.is_need_reset = 1,
	//.is_need_dsc = 1,
	.info = {
		.mipi = &lcd_otm1911_mipi_info
	},
	.ops = &lcd_otm1911_mipi_operations,
};
