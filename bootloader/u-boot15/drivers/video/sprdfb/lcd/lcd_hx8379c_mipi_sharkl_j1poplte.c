/* drivers/video/sprdfb/lcd_hx8379c_mipi.c
 *
 * Support for hx8379c mipi LCD device
 *
 * Copyright (C) 2010 Spreadtrum
 */

//#include <asm/arch/sprd_lcd.h>
#include "../sprdfb_chip_common.h"                                                                                                                                             LCM_SLEEP
#include "../sprdfb_panel.h"                                                                                                                                                   LCM_TAG_MASK
   
#include "../sprdfb.h"
#define printk printf

#define  LCD_DEBUG
#ifdef LCD_DEBUG
#define LCD_PRINT printk
#else
#define LCD_PRINT(...)
#endif

#define MAX_DATA   150

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

#define LCD_NEW_PANEL


static LCM_Init_Code init_data[] = {

// Set EXTC
{LCM_SEND(6), {4, 0, 0xb9,0xff,0x83,0x79}},

//Set Power
{LCM_SEND(19), {17, 0, 0xB1,0x44,0x15,0x15,0x31,0x31,0x50,0xD0,0xEE,0x54,0x80,0x38,0x38,0xF8,0x33,0x32,0x22}},

// Set Display 
{LCM_SEND(12), {10, 0, 0xb2,0x82,0x3C,0x0C,0x03,0x20,0x50,0x11,0x42,0x1D}},

{LCM_SEND(13), {11, 0, 0xb4,0x08,0x6E,0x08,0x6E,0x08,0x6E,0x22,0x86,0x23,0x86}},
{LCM_SEND(7), {5, 0, 0xc7,0x00,0x00,0x00,0xC0}},
{LCM_SEND(2), {0xcc,0x02}},
{LCM_SEND(2), {0xd2,0x00}},
{LCM_SEND(32), {30, 0, 0xd3,0x00,0x07,0x00,0x3C,0x14,0x08,0x08,0x32,0x10,0x01,0x00,0x01,0x03,0x72,0x03,0x72,0x00,0x08,0x00,0x08,0x33,0x33,0x05,0x05,0x37,0x05,0x05,0x37,0x0A}},
{LCM_SEND(37), {35, 0, 0xd5,0x19,0x19,0x18,0x18,0x1A,0x1A,0x1B,0x1B,0x02,0x03,0x00,0x01,0x06,0x07,0x04,0x05,0x20,0x21,0x22,0x23,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00}},
{LCM_SEND(35), {33, 0, 0xd6,0x18,0x18,0x19,0x19,0x1A,0x1A,0x1B,0x1B,0x05,0x04,0x07,0x06,0x01,0x00,0x03,0x02,0x23,0x22,0x21,0x20,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18}},
{LCM_SEND(45), {43, 0, 0xe0,0x00,0x00,0x00,0x24,0x2C,0x3F,0x09,0x2F,0x05,0x09,0x0B,0x17,0x0E,0x11,0x13,0x11,0x13,0x07,0x12,0x13,0x19,0x00,0x00,0x00,0x26,0x2C,0x3F,0x0A,0x2E,0x06,0x08,0x0A,0x16,0x0D,0x10,0x13,0x11,0x13,0x06,0x12,0x13,0x17}},
{LCM_SEND(5), {3, 0, 0xb6,0x8f,0x8f}},


{LCM_SEND(1), {0x11}},//0x11
{LCM_SLEEP(120)},
{LCM_SEND(1), {0x29}},//0x29
{LCM_SLEEP(100)},


};

static LCM_Init_Code disp_on =  {LCM_SEND(1), {0x29}};

static LCM_Init_Code sleep_in[] =  {
	{LCM_SEND(1), {0x28}},
	{LCM_SLEEP(150)}, 	//>150ms
	{LCM_SEND(1), {0x10}},
	{LCM_SLEEP(150)},	//>150ms
};

static LCM_Init_Code sleep_out[] =  {
	{LCM_SEND(1), {0x11}},
	{LCM_SLEEP(120)},//>120ms
	{LCM_SEND(1), {0x29}},
	{LCM_SLEEP(20)}, //>20ms
};

extern void (*lcd_panel_cabc_pwm_bl)(int brightness);
//extern void backlight_control(int brigtness);
static int32_t hx8379c_mipi_init(struct panel_spec *self)
{
	int32_t i = 0;
	LCM_Init_Code *init = init_data;
	unsigned int tag;

//	lcd_panel_cabc_pwm_bl = backlight_control;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_dcs_write_t mipi_dcs_write = self->info.mipi->ops->mipi_dcs_write;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	LCD_PRINT("zhouhehe   ---lcd_hx8379c_init\n");

	mipi_set_cmd_mode();
	mipi_eotp_set(0,0);

	for(i = 0; i < ARRAY_SIZE(init_data); i++){
		tag = (init->tag >>24);
		if(tag & LCM_TAG_SEND){
			mipi_dcs_write(init->data, (init->tag & LCM_TAG_MASK));
			udelay(20);
		}else if(tag & LCM_TAG_SLEEP){
			mdelay(init->tag & LCM_TAG_MASK);//udelay((init->tag & LCM_TAG_MASK) * 1000);
		}
		init++;
	}
	mipi_eotp_set(0,0);

	return 0;
}

static uint32_t hx8379c_readid(struct panel_spec *self)
{


	uint32 j =0;
	uint8_t read_data[4] = {0};
	int32_t read_rtn = 0;
	uint8_t param[2] = {0};
	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_force_write_t mipi_force_write = self->info.mipi->ops->mipi_force_write;
	mipi_force_read_t mipi_force_read = self->info.mipi->ops->mipi_force_read;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	LCD_PRINT("lcd_hx8379c_mipi read id!\n");

	mipi_set_cmd_mode();
	mipi_eotp_set(0,0);

	for(j = 0; j < 4; j++){
		param[0] = 0x01;
		param[1] = 0x00;
		mipi_force_write(0x37, param, 2);
		read_rtn = mipi_force_read(0xda,1,&read_data[0]);
		LCD_PRINT("lcd_hx8379c_mipi read id 0xda value is 0x%x!\n",read_data[0]);

		read_rtn = mipi_force_read(0xdb,1,&read_data[1]);
		LCD_PRINT("lcd_hx8379c_mipi read id 0xdb value is 0x%x!\n",read_data[1]);

		read_rtn = mipi_force_read(0xdc,1,&read_data[2]);
		LCD_PRINT("lcd_hx8379c_mipi read id 0xdc value is 0x%x!\n",read_data[2]);

		if((0x6 == read_data[1])&&(0x80 == read_data[2])){
				LCD_PRINT("lcd_hx8379c_mipi read id success!\n");
				return 0x8379;
		}

	}

	mipi_eotp_set(0,0);

	LCD_PRINT("lcd_s6d77a1_mipi read id failed!\n");
	
	return 0;

//	return 0x8379;
}

static struct panel_operations lcd_hx8379c_mipi_operations = {
	.panel_init = hx8379c_mipi_init,
	.panel_readid = hx8379c_readid,
};

static struct timing_rgb lcd_hx8379c_mipi_timing = {
#ifndef LCD_NEW_PANEL
	.hfp = 115,  /* unit: pixel */
	.hbp = 55,
	.hsync = 4,
	.vfp = 6, /*unit: line*/
	.vbp = 19,
	.vsync = 4,
#else
	.hfp = 74,  /* unit: pixel */
	.hbp = 88,
	.hsync = 26,
	.vfp = 16, /* unit: line */
	.vbp = 12,
	.vsync = 4,
#endif
};


static struct info_mipi lcd_hx8379c_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 24, /*18,16*/
	.lan_number = 	2,
	.phy_feq =481*1000,
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_hx8379c_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_hx8379c_mipi_spec = {
	.width = 480,
	.height = 800,
	.fps = 60,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.info = {
		.mipi = &lcd_hx8379c_mipi_info
	},
	.ops = &lcd_hx8379c_mipi_operations,
};
