/* drivers/video/sprdfb/lcd_st7703_mipi.c
 *
 * Support for st7703 mipi LCD device
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
#ifdef LCD_DEBUG
#define LCD_PRINT printk
#else
#define LCD_PRINT(...)
#endif

#define MAX_DATA   70

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
	{LCM_SEND(6),{4,0,0xB9,0xF1,0x12,0x83}},

	{LCM_SEND(30),{28,0,0xBA,0x33,0x81,0x05,0xF9,0x0E,0x0E,0x20,0x00,0x00,                     
	                    0x00,0x00,0x00,0x00,0x00,0x44,0x25,0x00,0x91,0x0A,                                          
	                    0x00,0x00,0x02,0x4F,0x11,0x03,0x02,0x37}},
	                  
	{LCM_SEND(2),{0xB8,0x76}},

	{LCM_SEND(13),{11,0,0xB3,0x0C,0x10,0x05,0x05,0x03,0xFF,0x00,0x00,0x00,0x00}},

	{LCM_SEND(12),{10,0,0xC0,0x73,0x73,0x50,0x50,0xC0,0x00,0x08,0x50,0x00}},                                                             
	                                                  
	{LCM_SEND(2),{0xBC,0x4F}}, 
	 
	{LCM_SEND(2),{0xCC,0x0B}},
	                     
	{LCM_SEND(2),{0xB4,0x80}}, 
	                      
	{LCM_SEND(6),{4,0,0xB2,0xF0,0x12,0xA0}},

	{LCM_SEND(17),{15,0,0xE3,0x07,0x07,0x0B,0x0B,0x03,0x0B,0x00,0x00,0x00,0x00,0x6F,0x00,0xC0,0x10}},                                                                                                      
	{LCM_SEND(15),{13,0,0xC1,0x53,0xC0,0x26,0x26,0x77,0xF1,0xFF,0xFF,0xEE,0xEE,0xEE,0xEE}},                                          
	                                   
	{LCM_SEND(8),{6,0,0xC6,0x02,0x40,0xCF,0x7F,0x00}},
	                           
	{LCM_SEND(5),{3,0,0xB5,0x14,0x14}},
	                   
	//{LCM_SEND(5),{3,0,0xB6,0x4D,0x4D}},
	                                      
	{LCM_SEND(6),{4,0,0xBF,0x02,0x11,0x00}},

	{LCM_SEND(66),{64,0,0xE9,0x82,0x10,0x09,0x00,0x00,0xC1,0x89,0x12,0x31,                      
	                    0x23,0x47,0x87,0xC1,0x89,0x47,0x2A,0x00,0x00,0x0C,                                             
	                    0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x88,                       
	                    0x20,0x46,0x02,0x88,0x88,0x88,0x88,0x88,0x88,0xFF,                                             
	                    0x88,0x31,0x57,0x13,0x88,0x88,0x88,0x88,0x88,0x88,                       
	                    0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	                    0x00,0x00,0x00,0x00}},  
	                                           
	{LCM_SEND(64),{62,0,0xEA,0x00,0x1A,0x00,0x00,0x00,0x00,0x02,0x00,0x00,                     
	                    0x00,0x00,0x00,0x8F,0x13,0x31,0x75,0x88,0x88,0x88,                                          
	                    0x88,0x88,0x88,0xF8,0x8F,0x02,0x20,0x64,0x88,0x88,                     
	                    0x88,0x88,0x88,0x88,0xF8,0x23,0x00,0x00,0x00,0x00,                                          
	                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,                     
	                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,                                          
	                    0x00,0x00}}, 
	                             
	{LCM_SEND(37),{35,0,0xE0,0x00,0x03,0x07,0x28,0x2F,0x38,0x36,0x36,0x05,0x0B,0x0D,0x10,0x12,0x10,0x12,0x12,0x18,
	                         0x00,0x03,0x07,0x28,0x2F,0x38,0x36,0x36,0x05,0x0B,0x0D,0x10,0x12,0x10,0x12,0x12,0x18}},
	{LCM_SEND(2),{0xC7,0xB0}},
	{LCM_SEND(6),{4,0,0xC8,0x10,0x01,0x02}},                          
	{LCM_SEND(2),{0x51,0x00}}, 
	{LCM_SEND(2),{0x53,0x24}}, 
	{LCM_SEND(2),{0x55,0x02}}, 
	{LCM_SEND(2),{0x5E,0x04}}, 

	{LCM_SEND(1),{0x11}},
	{LCM_SLEEP(120)},                        
	{LCM_SEND(1),{0x29}},                    
	{LCM_SLEEP(20)},
 };

static LCM_Force_Cmd_Code rd_prep_code[]={
	//{0x39, {LCM_SEND(6), {4,0,0xBF,0x91,0x61,0xF2}}},
	{0x37, {LCM_SEND(2), {0x3, 0}}},
};

static LCM_Init_Code disp_on =  {LCM_SEND(1), {0x29}};

static LCM_Init_Code sleep_in =  {LCM_SEND(1), {0x10}};

static LCM_Init_Code sleep_out =  {LCM_SEND(1), {0x11}};

static int32_t st7703_mipi_init(struct panel_spec *self)
{
	int32_t i;
	LCM_Init_Code *init = init_data;
	unsigned int tag;
	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;
	mipi_set_lp_mode_t mipi_set_lp_mode = self->info.mipi->ops->mipi_set_lp_mode;
	mipi_set_hs_mode_t mipi_set_hs_mode = self->info.mipi->ops->mipi_set_hs_mode;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;
	mipi_dcs_write_t mipi_dcs_write = self->info.mipi->ops->mipi_dcs_write;

	LCD_PRINT("uboot lcd_st7703_init\n");
	mipi_set_cmd_mode();
	//mipi_eotp_set(0,0);
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

static uint32_t st7703_readid(struct panel_spec *self)
{
        /*Jessica TODO: need read id*/
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

	LCD_PRINT("uboot lcd_st7703_mipi read id!\n");
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
		read_rtn = mipi_force_read(0x04, 3,(uint8_t *)read_data);
		LCD_PRINT("lcd_st7703_mipi read id 0x04 value is 0x%x-0x%x-%x!\n", read_data[0],read_data[1],read_data[2]);
		//A1 21 1f
		if((0xA1 == read_data[0])){
			mipi_eotp_set(1,1);
			#if 1
			i2c_set_bus_num(4);
			i2c_init(100000, 0x3E);
			i2c_reg_write(0x3E, 0x00, 0x0F);
			mdelay(1);
			i2c_reg_write(0x3E, 0x01, 0x0F);
			mdelay(1);
			#endif
			LCD_PRINT("lcd_st7703_mipi read id success!\n");
			return 0x7703;
		}
	}
	mipi_set_hs_mode();
	return 0x0;
}

int32_t st7703_reset(struct panel_spec *self)
{

	//writel(0x30, 0x40280000);
	#if 0
	sprd_gpio_request(NULL, LCM_GPIO_AVDDEN);
	sprd_gpio_direction_output(NULL, LCM_GPIO_AVDDEN, 1);
	mdelay(10);
	sprd_gpio_request(NULL, LCM_GPIO_AVEEEN);
	sprd_gpio_direction_output(NULL, LCM_GPIO_AVEEEN, 1);
	sprd_gpio_request(NULL, LCM_GPIO_IOVDDEN);
	sprd_gpio_direction_output(NULL, LCM_GPIO_IOVDDEN, 1);
	mdelay(10);
	sprd_gpio_request(NULL, LCM_GPIO_VDDEN);
	sprd_gpio_direction_output(NULL, LCM_GPIO_VDDEN, 1);
	mdelay(10);
	#endif
	sprd_gpio_request(NULL, LCM_GPIO_RSTN);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 1);
	mdelay(10);
	writel(0x30, 0x40280004);
	writel(0x30, 0x40280008);
	mdelay(1);
	writel(0x10, 0x40280000);
	mdelay(1);
	writel(0x30, 0x40280000);
	mdelay(10);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 1);
	mdelay(10);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 0);
	mdelay(10);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 1);
	mdelay(120);
	return 0;
}

static unsigned char set_bl_seq[] = {
	0x51, 0xFF
};

static int32_t st7703_set_brightness(struct panel_spec *self,uint16_t brightness)
{
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;
	set_bl_seq[1] = brightness;
	mipi_gen_write(&set_bl_seq[0], 2);
}

static struct panel_operations lcd_st7703_mipi_operations = {
	.panel_init = st7703_mipi_init,
	.panel_readid = st7703_readid,
	.panel_reset = st7703_reset,
	.panel_set_brightness = st7703_set_brightness,
};

static struct timing_rgb lcd_st7703_mipi_timing = {
	#if 0
	.hfp = 90,  /* unit: pixel */// 100
	.hbp = 90,//80
	.hsync = 40,//6
	.vfp = 50, /*unit: line*/
	.vbp = 26,
	.vsync =4, //6,
	#else
	.hfp = 50,  /* unit: pixel */
	.hbp = 70,
	.hsync = 20,
	.vfp = 20, /*unit: line*/
	.vbp = 20,
	.vsync = 4,
	#endif
};

static struct info_mipi lcd_st7703_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 24, /*18,16*/
	.lan_number = 4,
	.phy_feq = 568*1000,
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_st7703_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_st7703_mipi_spec = {
	//.cap = PANEL_CAP_NOT_TEAR_SYNC,
	.width = 720,
	.height = 1440,
	.fps = 60,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.info = {
		.mipi = &lcd_st7703_mipi_info
	},
	.ops = &lcd_st7703_mipi_operations,
};


