/* drivers/video/sprdfb/lcd_hx8379a_mipi.c
 *
 * Support for hx8379a mipi LCD device
 *
 * Copyright (C) 2010 Spreadtrum
 */

#include <asm/arch/sprd_lcd.h>
#include "../sprdfb.h"
#define printk printf

#define  LCD_DEBUG
#ifdef LCD_DEBUG
#define LCD_PRINT printk
#else
#define LCD_PRINT(...)
#endif

#define MAX_DATA   100

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
// Set EXTC
{LCM_SEND(6), {4, 0, 0xb9,0xff,0x83,0x79}},

// Set MIPI 
{LCM_SEND(5), {3, 0, 0xba,0x51,0x93}},
//Set Power
{LCM_SEND(34), {32, 0, 0xB1,0x00,0x50,0x24,0xF5,0x98,0x08,0x11,0x17,0x77,0x29,0x31,0x9A,
                0x1A,0x12,0x0B,0x76,0xF1,0x00,0xE6,0xE6,0xE6,0xE6,0xE6,0x00,0x04,0x05,
                0x0A,0x0B,0x04,0x05,0x6F}},
// Set Display 
{LCM_SEND(16), {14, 0, 0xB2,0x00,0x00,0xFE,0x0E,0x0A,0x19,0xE2,0x00,0xFF,0x0E,0x0A,0x19,0x20}},
// Set CYC
{LCM_SEND(34), {32, 0, 0xB4,0x80,0x12,0x00,0x32,0x10,0x03,0x54,0x13,0x67,0x32,0x13,0x6B,
                0x39,0x00,0x42,0x05,0x37,0x00,0x41,0x08,0x3C,0x3C,0x08,0x00,0x40,0x08,
                0x28,0x08,0x30,0x30,0x04}},
// Set GIP
{LCM_SEND(50), {48, 0, 0xD5,0x00,0x00,0x0A,0x00,0x01,0x00,0x00,0x06,0x01,0x01,0x01,
                0x23,0x45,0x67,0xAA,0xBB,0x88,0x88,0x67,0x45,0x88,0x88,0x88,0x88,0x88,
                0x54,0x10,0x76,0x54,0x32,0xAA,0xBB,0x88,0x88,0x76,0x10,0x88,0x88,0x88,
                0x88,0x88,0x39,0x01,0x00,0x00,0x00,0x00}},
// Set Gamma 
{LCM_SEND(38), {36, 0, 0xE0,0x79,0x00,0x01,0x0F,0x25,0x26,0x3F,0x33,0x47,0x0A,0x11,0x11,
                0x15,0x17,0x14,0x16,0x11,0x17,0x00,0x01,0x0F,0x25,0x26,0x3F,0x33,0x47,
                0x0A,0x11,0x11,0x15,0x17,0x14,0x16,0x11,0x17}},
// Set Panel 
//{LCM_SEND(2), {0xcc,0x02}}, //no rotation
{LCM_SEND(2), {0xcc,0x0E}},//rotation 180
// Set VCOM
{LCM_SEND(7), {5, 0, 0xB6,0x00,0xAC,0x00,0xAC}},
//set TE
{LCM_SEND(2), {0x35,0x00}},

{LCM_SEND(1), {0x11}},//0x11
{LCM_SLEEP(200)},
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

static int32_t hx8379a_mipi_init(struct panel_spec *self)
{
	int32_t i;
	LCM_Init_Code *init = init_data;
	unsigned int tag;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_dcs_write_t mipi_dcs_write = self->info.mipi->ops->mipi_dcs_write;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	LCD_PRINT("lcd_hx8379a_init\n");

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

static uint32_t hx8379a_readid(struct panel_spec *self)
{
	uint32 j =0;
	uint8_t read_data[4] = {0};
	int32_t read_rtn = 0;
	uint8_t param[2] = {0};
	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_force_write_t mipi_force_write = self->info.mipi->ops->mipi_force_write;
	mipi_force_read_t mipi_force_read = self->info.mipi->ops->mipi_force_read;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	LCD_PRINT("lcd_hx8379a_mipi read id!\n");

	mipi_set_cmd_mode();
	mipi_eotp_set(0,0);

	for(j = 0; j < 4; j++){
		param[0] = 0x01;
		param[1] = 0x00;
		mipi_force_write(0x37, param, 2);
		read_rtn = mipi_force_read(0xda,1,&read_data[0]);
		LCD_PRINT("lcd_hx8379a_mipi read id 0xda value is 0x%x!\n",read_data[0]);

		read_rtn = mipi_force_read(0xdb,1,&read_data[1]);
		LCD_PRINT("lcd_hx8379a_mipi read id 0xdb value is 0x%x!\n",read_data[1]);

		read_rtn = mipi_force_read(0xdc,1,&read_data[2]);
		LCD_PRINT("lcd_hx8379a_mipi read id 0xdc value is 0x%x!\n",read_data[2]);

		if((0x83 == read_data[0])&&(0x79 == read_data[1])&&(0x0a == read_data[2])){
				LCD_PRINT("lcd_hx8379a_mipi read id success!\n");
				return 0x8379;
			}
	}

	mipi_eotp_set(0,0);

	return 0;
}

static struct panel_operations lcd_hx8379a_mipi_operations = {
	.panel_init = hx8379a_mipi_init,
	.panel_readid = hx8379a_readid,
};

static struct timing_rgb lcd_hx8379a_mipi_timing = {
	.hfp = 25,  /* unit: pixel */
	.hbp = 25,
	.hsync = 11,
	.vfp = 22, /*unit: line*/
	.vbp = 12,
	.vsync = 3,
};


static struct info_mipi lcd_hx8379a_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 24, /*18,16*/
	.lan_number = 	2,
	.phy_feq =500*1000,
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_hx8379a_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_hx8379a_mipi_spec = {
	.width = 480,
	.height = 854,
	.fps = 62,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.info = {
		.mipi = &lcd_hx8379a_mipi_info
	},
	.ops = &lcd_hx8379a_mipi_operations,
};
