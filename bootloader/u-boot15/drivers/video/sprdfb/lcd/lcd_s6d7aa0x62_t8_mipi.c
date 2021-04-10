/* drivers/video/sprdfb/lcd_s6d7aa0x62_mipi.c
 *
 * Support for s6d7aa0x62 mipi LCD device
 *
 * Copyright (C) 2010 Spreadtrum
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




static LCM_Init_Code init_data[] = {

	//Initializing  Sequence(1)
	{LCM_SEND(5), {3, 0, 0xF0, 0x5A, 0x5A} },
	{LCM_SEND(5), {3, 0, 0xF1, 0x5A, 0x5A} },
	{LCM_SEND(5), {3, 0, 0xFC, 0xA5, 0xA5} },
	{LCM_SEND(5), {3, 0, 0xD0, 0x00, 0x10} },

	//Initializing  Sequence(2)
	{LCM_SEND(2), {0xB1, 0x12} },
	{LCM_SEND(7), {5, 0, 0xB2,0x14, 0x22, 0x2F, 0x18} },
	{LCM_SEND(2), {0xB3, 0x11} },
	{LCM_SEND(12), {10, 0, 0xBA,0x03,0x19,0x19,0x11,0x03,0x05,0x18,0x18,0x77} },
	{LCM_SEND(6), {4, 0, 0xBC,0x00, 0x4E, 0x0B} },
	{LCM_SEND(6), {4, 0, 0xC0,0x80, 0x80, 0x30} },
	{LCM_SEND(2), {0xC1, 0x03} },
	{LCM_SEND(2), {0xC2, 0x00} },
	{LCM_SEND(6), {4, 0, 0xC3, 0x40,0x00, 0x28} },
	{LCM_SEND(8), {6, 0, 0xE1, 0x03,0x10, 0x1C, 0xA0, 0x10} },
	{LCM_SEND(11), {9, 0, 0xEE, 0xA5,0x00,0x98,0x00,0xA5,0x00,0x98,0x00} },
	{LCM_SEND(8), {6, 0, 0xF2, 0x02,0x10, 0x10, 0x44, 0x10} },
	{LCM_SEND(13), {11, 0, 0xF3, 0x01,0x93,0x20,0x22,0x80,0x05,0x25,0x3C,0x26,0x00} },
	{LCM_SEND(48), {46, 0, 0xF4, 0x02,0x02,0x10,0x26,0x10,0x02,0x03,0x03,0x03,0x10,0x16,0x03, \
			0x00,0x0C,0x0C,0x03,0x04,0x05,0x13,0x1E,0x09,0x0A,0x05,0x05,0x01,0x04,0x02, \
			0x61,0x74,0x75,0x72,0x83,0x80,0x80,0x00,0x00,0x01,0x01,0x28,0x04,0x03,0x28, \
			0x01,0xD1,0x32} },
	{LCM_SEND(35), {33, 0, 0xF7,0x01,0x1B,0x08,0x0C,0x09,0x0D,0x01,0x01,0x01,0x04,0x06,0x01,0x01, \
			0x00,0x00,0x1A,0x01,0x1B,0x0A,0x0E,0x0B,0x0F,0x01,0x01,0x01,0x05,0x07,0x01,0x01,
			0x00,0x00,0x1A} },
	{LCM_SEND(9), {7, 0, 0xF6, 0x60,0x25, 0x05, 0x00, 0x00, 0x00} },
	{LCM_SEND(8), {6, 0, 0xFD, 0x16,0x10, 0x11, 0x23, 0x09} },
	{LCM_SEND(9), {7, 0, 0xFE, 0x00,0x02, 0x03, 0x21, 0x80, 0x78} },
	{LCM_SEND(20), {18, 0, 0xEF,0x34,0x12,0x98,0xBA,0x10,0x80,0x24,0x80,0x80,0x80,0x00,0x00,0x00, \
			0x44,0xA0,0x82,0x00} },
	{LCM_SEND(16), {14, 0, 0xCD,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E} },
	{LCM_SEND(16), {14, 0, 0xCE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00} },
	{LCM_SEND(2), {0x51, 0xFF} },
	{LCM_SEND(2), {0x53, 0x2C} },
	{LCM_SEND(2), {0x55, 0x01} },

	// Initializing Sequence(3)
	{LCM_SEND(20), {18, 0, 0xFA,0x08,0x3F,0x0D,0x12,0x07,0x0C,0x11,0x0F,0x11,0x18,0x1D,0x1E,0x21,\
			0x23,0x24,0x27,0x30,} },
	{LCM_SEND(20), {18, 0, 0xF8,0x08,0x3F,0x0C,0x12,0x07,0x0C,0x10,0x0F,0x11,0x18,0x1D,0x1E,0x21,\
			0x23,0x23,0x26,0x2F} },

	// Initializing  Sequence(1-1)
	{LCM_SEND(5), {3, 0, 0xF0, 0xA5, 0xA5} },
	{LCM_SEND(5), {3, 0, 0xF1, 0xA5, 0xA5} },
	{LCM_SEND(5), {3, 0, 0xFC, 0x5A, 0x5A} },

	// power on
	{LCM_SEND(1), {0x11} },
	{LCM_SLEEP(120)},
	{LCM_SEND(1), {0x29} },
	{LCM_SLEEP(20)},

};


static LCM_Init_Code sleep_in[] =  {

	{LCM_SEND(1), {0x11}},
	{LCM_SLEEP(170)},
};

static LCM_Init_Code sleep_out[] =  {
	{LCM_SEND(1), {0x10}},
	{LCM_SLEEP(170)},

};


static int32_t s6d7aa0x62_mipi_init(struct panel_spec *self)
{
	int32_t i;
	LCM_Init_Code *init = init_data;
	unsigned int tag;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_dcs_write_t mipi_dcs_write = self->info.mipi->ops->mipi_dcs_write;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	LCD_PRINT("lcd_s6d7aa0x62_init\n");

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

static uint32_t s6d7aa0x62_readid(struct panel_spec *self)
{
#if 0
	uint32 j =0;
	uint8_t read_data[4] = {0};
	int32_t read_rtn = 0;
	uint8_t param[2] = {0};
	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_force_write_t mipi_force_write = self->info.mipi->ops->mipi_force_write;
	mipi_force_read_t mipi_force_read = self->info.mipi->ops->mipi_force_read;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	LCD_PRINT("lcd_s6d7aa0x62_mipi read id!\n");

	mipi_set_cmd_mode();
	mipi_eotp_set(0,0);

	for(j = 0; j < 4; j++){
		param[0] = 0x01;
		param[1] = 0x00;
		mipi_force_write(0x37, param, 2);
		read_rtn = mipi_force_read(0xda,1,&read_data[0]);
		LCD_PRINT("lcd_s6d7aa0x62_mipi read id 0xda value is 0x%x!\n",read_data[0]);

		read_rtn = mipi_force_read(0xdb,1,&read_data[1]);
		LCD_PRINT("lcd_s6d7aa0x62_mipi read id 0xdb value is 0x%x!\n",read_data[1]);

		read_rtn = mipi_force_read(0xdc,1,&read_data[2]);
		LCD_PRINT("lcd_s6d7aa0x62_mipi read id 0xdc value is 0x%x!\n",read_data[2]);

		if((0x55 == read_data[0])&&(0xbf == read_data[1] || 0xc0 == read_data[1] || 0xbe == read_data[1])&&(0x90 == read_data[2])){
				LCD_PRINT("lcd_s6d7aa0x62_mipi read id success!\n");
				return 0x8369;
		}
	}

	mipi_eotp_set(0,0);

	LCD_PRINT("lcd_s6d77a1_mipi read id failed!\n");
	return 0;
#endif
	LCD_PRINT("lcd_s6d7aa0x62_mipi read id!\n");
	return 0x6262;
}

static struct panel_operations lcd_s6d7aa0x62_mipi_operations = {
	.panel_init = s6d7aa0x62_mipi_init,
	.panel_readid = s6d7aa0x62_readid,
};

static struct timing_rgb lcd_s6d7aa0x62_mipi_timing = {

	.hfp = 104,  /* unit: pixel */
	.hbp = 154,
	.hsync = 1,
	.vfp = 16, /*unit: line*/
	.vbp = 12,
	.vsync = 1,

};


static struct info_mipi lcd_s6d7aa0x62_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 24, /*18,16*/
	.lan_number = 	4,
	.phy_feq =481*1000,
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_s6d7aa0x62_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_s6d7aa0x62_mipi_spec = {
	.width = 720,
	.height =1280 ,
	.fps = 60,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	//.suspend_mode = SEND_SLEEP_CMD,
	.info = {
		.mipi = &lcd_s6d7aa0x62_mipi_info
	},
	.ops = &lcd_s6d7aa0x62_mipi_operations,
};
