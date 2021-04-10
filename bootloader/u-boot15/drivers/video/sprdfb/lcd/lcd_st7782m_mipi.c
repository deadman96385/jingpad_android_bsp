
/* drivers/video/sc8825/lcd_st7782m_mipi.c
 *
 * Support for st7782m mipi LCD device
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

#define LCM_TAG_SEND  (1<< 0)
#define LCM_TAG_SLEEP (1 << 1)

static LCM_Init_Code init_data[] = {
	{LCM_SEND(2), {0xF0, 0xC3}},
	{LCM_SEND(2), {0xF0, 0x96}},
	{LCM_SEND(2), {0xF0, 0xA5}},

	//=== Power Saving Start
	{LCM_SEND(2), {0xE9, 0x20}},                                                //V22P Output
	{LCM_SEND(2), {0xE7, 0x83}},                                                //Bypass Mode
	{LCM_SEND(7), {5, 0, 0xC3, 0x44, 0x02, 0x77, 0x01}},                        //Power Control 3 Column
	{LCM_SEND(7), {5, 0, 0xC4, 0x66, 0x06, 0x66, 0x01}},                        //Power Control 4 Column
	{LCM_SEND(2), {0xED, 0xC3}},                                                //Bybit Mode
	{LCM_SEND(6), {4, 0, 0xE4, 0x40, 0x00, 0x00}},                              //TEST
	{LCM_SEND(17), {15, 0, 0xE5, 0x9A, 0xf5, 0x95, 0x57, 0x22, 0x25, 0x01, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22}},  //Source OK Column
	{LCM_SEND(17), {15, 0, 0xE6, 0x9A, 0xf5, 0x95, 0x85, 0x22, 0x25, 0x21, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33}},  //Source OK Column
	{LCM_SEND(10), {8, 0, 0xEC, 0x00, 0x55, 0x03, 0x00, 0x00, 0x49, 0x22}},     //Source

	//=== Power Saving End
	{LCM_SEND(7), {5, 0, 0xC1, 0x00, 0x0A, 0xAC, 0x11}},                        //Power Control 1  4.5V
	{LCM_SEND(7), {5, 0, 0xC2, 0x00, 0x0A, 0xAC, 0x11}},                        //Power Control 2

	{LCM_SEND(2), {0x36, 0x04}},                                                //04: FW, 10: BW
	{LCM_SEND(2), {0x3A, 0x07}},
	{LCM_SEND(2), {0xC5, 0x41}},                                                //VCOM 0.65V

	{LCM_SEND(17), {15, 0, 0xE0, 0xF0, 0x04, 0x13, 0x0F, 0x12, 0x0A, 0x41, 0x44, 0x50, 0x3A, 0x16, 0x15, 0x20, 0x22}},   //Gamma 0830
	{LCM_SEND(17), {15, 0, 0xE1, 0xF0, 0x04, 0x14, 0x0F, 0x12, 0x0A, 0x41, 0x44, 0x50, 0x3A, 0x16, 0x15, 0x1F, 0x22}},   //Gamma 0830

	{LCM_SEND(5), {3, 0, 0xB1, 0xF5, 0xA9}},                                    //Frame Rate Control 1
	{LCM_SEND(2), {0xB2, 0x10}},                                                //Gate Scan Control 10: FW, 18: BW
	{LCM_SEND(2), {0xB3, 0x02}},                                                //Inversion normal Column
	{LCM_SEND(2), {0xB4, 0x00}},                                                //Inversion idle
	{LCM_SEND(7), {5, 0, 0xB5, 0x00, 0x54, 0x00, 0x54}},                        //Blank Porch Control for Idle mode

	{LCM_SEND(12), {10, 0, 0xA5, 0x20, 0x12, 0xf0, 0x01, 0x00, 0x0a, 0x2A, 0x0A, 0x02}},  //Video Mode Source Timing Control
	{LCM_SEND(12), {10, 0, 0xA6, 0x20, 0x12, 0x40, 0x01, 0x00, 0x11, 0x2A, 0x0A, 0x03}},  //2 Color Mode Source Timing Control
	{LCM_SEND(10), {8, 0, 0xBA, 0x59, 0x02, 0x03, 0x00, 0x22, 0x02, 0x00}},               //GIP Mode
	{LCM_SEND(11), {9, 0, 0xBB, 0x00, 0x35, 0x00, 0x35, 0x88, 0x8B, 0x0B, 0x00}},         //GIP Control 0830
	{LCM_SEND(10), {8, 0, 0xBC, 0x00, 0x79, 0x00, 0x79, 0x88, 0x8B, 0x0B }},              //GIP Control
	{LCM_SEND(14), {12, 0, 0xBD, 0x44, 0xFF, 0xFF, 0xFF, 0x15, 0x51, 0xFF, 0xFF, 0x87, 0xFF, 0x02}},   //GIP Route
	{LCM_SEND(2), {0xD9, 0xE2}},

	{LCM_SEND(1), {0x11}},
	{LCM_SLEEP(120)},
	{LCM_SEND(1), {0x29}},
	{LCM_SLEEP(120)},
};

static LCM_Init_Code disp_on =  {LCM_SEND(1), {0x29}};

static LCM_Init_Code sleep_in =  {LCM_SEND(1), {0x10}};

static LCM_Init_Code sleep_out =  {LCM_SEND(1), {0x11}};

static int32_t st7782m_mipi_init(struct panel_spec *self)
{
	int32_t i;
	LCM_Init_Code *init = init_data;
	unsigned int tag;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;
	LCD_PRINT("st7782m_init\n");

	mipi_set_cmd_mode();

	for(i = 0; i < ARRAY_SIZE(init_data); i++){
		tag = (init->tag >>24);
		if(tag & LCM_TAG_SEND){
			mipi_gen_write(init->data, (init->tag & LCM_TAG_MASK));
		}else if(tag & LCM_TAG_SLEEP){
			mdelay((init->tag & LCM_TAG_MASK));
		}
		init++;
	}
	return 0;
}

static LCM_Force_Cmd_Code rd_prep_code[]={
	{0x37, {LCM_SEND(2), {0x3, 0}}},
};

static uint32_t st7782m_readid(struct panel_spec *self)
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
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;


	LCD_PRINT("lcd_st7782m_mipi read id!\n");

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
		mipi_eotp_set(0,0);
		read_rtn = mipi_force_read(0x04, 3,(uint8_t *)&read_data[0]);
		mipi_eotp_set(1,1);
		LCD_PRINT("lcd_st7782m_mipi read id 0x04 value is 0x%x, 0x%x, 0x%x!\n", read_data[0], read_data[1], read_data[2]);

		if((0x77 == read_data[0])&&(0x82 == read_data[1])){
			LCD_PRINT("lcd_st7782m_mipi read id success!\n");
			return 0x7782;
		}
	}

	return 0;
}

int32_t st7782m_reset(struct panel_spec *self)
{
	sprd_gpio_request(NULL, LCM_GPIO_RSTN);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 1);
	mdelay(10);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 0);
	mdelay(20);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 1);
	mdelay(20);

	return 0;
}

static struct panel_operations lcd_st7782m_mipi_operations = {
	.panel_init = st7782m_mipi_init,
	.panel_readid = st7782m_readid,
	.panel_reset = st7782m_reset,
};

static struct timing_rgb lcd_st7782m_mipi_timing = {
	.hfp = 80,  /* unit: pixel */
	.hbp = 80,
	.hsync = 20,
	.vfp = 4, /*unit: line*/
	.vbp = 4,
	.vsync = 1,
};

static struct info_mipi lcd_st7782m_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 24, /*18,16*/
	.lan_number = 1,
	.phy_feq = 300*1000,
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_st7782m_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_st7782m_mipi_spec = {
	.width = 240,
	.height = 320,
	.fps = 60,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.info = {
		.mipi = &lcd_st7782m_mipi_info
	},
	.ops = &lcd_st7782m_mipi_operations,
};

