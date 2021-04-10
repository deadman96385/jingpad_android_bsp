/* drivers/video/sprdfb/lcd_hx8399c_mipi.c
 *
 * Support for hx8399c mipi LCD device
 *
 * Copyright (C) 2010 Spreadtrum
 */

//#include <asm/arch/sprd_lcd.h>
#include "../sprdfb_chip_common.h"
#include "../sprdfb_panel.h"
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


static LCM_Init_Code init_data[] = {
{LCM_SEND(6),{ 4, 0, 0xB9, 0xFF, 0x83, 0x99}},
{LCM_SEND(7),{ 5, 0, 0xBA, 0x63, 0x03, 0x68, 0x73}},
{LCM_SEND(18),{ 16, 0, 0xB1, 0x02, 0x04, 0x6D, 0x8D, 0x01, 0x32, 0x33, 0x11, 0x11, 0x5E, 0x64, 0x56, 0x73, 0x02, 0x02}},
{LCM_SEND(18),{ 16, 0, 0xB2, 0x07, 0x00, 0x80, 0xAE, 0x05, 0x07, 0x5A, 0x31, 0x10, 0x30, 0x00, 0x1E, 0x70, 0x03, 0xD4}},
{LCM_SEND(47),{ 45, 0, 0xB4, 0x00, 0xFF, 0x10, 0x18, 0x04, 0x9A, 0x00, 0x00, 0x06, 0x00, 0x02, 0x04, 0x00, 0x24, 0x02, 0x04, 0x0A, 0x21, 0x03, 0x00, 0x00, 0x02, 0x9F, 0x88, 0x10, 0x18, 0x04, 0x9A, 0x00, 0x00, 0x08, 0x00, 0x02, 0x04, 0x00, 0x24, 0x02, 0x04, 0x0A, 0x00, 0x00, 0x02, 0x9F, 0x12}},
{LCM_SEND(36),{ 34, 0, 0xD3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x07, 0x88, 0x07, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x05, 0x40}},
{LCM_SEND(35),{ 33, 0, 0xD5, 0x20, 0x20, 0x1E, 0x1E, 0x1F, 0x1F, 0x01, 0x01, 0x00, 0x00, 0x25, 0x25, 0x18, 0x18, 0x18, 0x18, 0x24, 0x24, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x2F, 0x2F, 0x30, 0x30, 0x31, 0x31}},
{LCM_SEND(35),{ 33, 0, 0xD6, 0x24, 0x24, 0x1E, 0x1E, 0x1F, 0x1F, 0x00, 0x00, 0x01, 0x01, 0x25, 0x25, 0x18, 0x18, 0x18, 0x18, 0x20, 0x20, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x2F, 0x2F, 0x30, 0x30, 0x31, 0x31}},
{LCM_SEND(2),{0xBD, 0x00}},
{LCM_SEND(19),{ 17, 0, 0xD8, 0xAA, 0x8A, 0xAA, 0xAA, 0xAA, 0x8A, 0xAA, 0xAA, 0xAA, 0x8A, 0xAA, 0xAA, 0xAA, 0x8A, 0xAA, 0xAA}},
{LCM_SEND(2),{0xBD, 0x01}},
{LCM_SEND(19),{ 17, 0, 0xD8, 0xFF, 0xCF, 0xEA, 0xBF, 0xFF, 0xCF, 0xEA, 0xBF, 0xFF, 0xCF, 0xEA, 0xBF, 0xFF, 0xCF, 0xEA, 0xBF}},
{LCM_SEND(2),{ 0xBD, 0x02}},
{LCM_SEND(11),{ 9, 0, 0xD8, 0xFF, 0xCF, 0xEA, 0xBF, 0xFF, 0xCF, 0xEA, 0xBF}},
{LCM_SEND(2),{0xBD, 0x00}},
{LCM_SEND(8),{ 6, 0, 0xC9, 0x03, 0x00, 0x12, 0x20, 0x31}},
{LCM_SEND(57),{ 55, 0, 0xE0, 0x02, 0x1D, 0x2B, 0x25, 0x54, 0x5F, 0x6C, 0x69, 0x72, 0x7B, 0x82, 0x8A, 0x90, 0x98, 0x9F, 0xA4, 0xA5, 0xAC, 0xAD, 0xB3, 0xA4, 0xAF, 0xB1, 0x5B, 0x59, 0x65, 0x7C, 0x02, 0x1D, 0x2B, 0x25, 0x54, 0x5F, 0x6C, 0x6A, 0x73, 0x7A, 0x84, 0x8B, 0x90, 0x96, 0x9C, 0x9F, 0xA0, 0xA9, 0xAC, 0xB2, 0xA4, 0xAF, 0xB1, 0x5A, 0x51, 0x59, 0x7C}},
{LCM_SEND(5),{ 3, 0, 0xB6, 0x8A, 0x8A}},
{LCM_SEND(2),{0xCC, 0x08}},
{LCM_SEND(8),{ 6, 0, 0xC7, 0x00, 0x08, 0x00, 0x01, 0x08}},
{LCM_SEND(5),{ 3, 0, 0xC0, 0x25, 0x5A}},
{LCM_SLEEP(5)},
//{LCM_SEND(5),{ 3, 0, 0x51, 0x00, 0x00}},
{LCM_SEND(10),{ 8, 0, 0xBF, 0x40, 0x41, 0x50, 0x09, 0x1A, 0xC0, 0xCD}},
{LCM_SEND(2),{0xE4, 0x01}},
{LCM_SLEEP(10)},
{LCM_SEND(2),{0x11, 0x00}},
{LCM_SLEEP(150)},
{LCM_SEND(2),{0x29, 0x00}},
{LCM_SLEEP(20)},
{LCM_SEND(5),{ 3, 0, 0xE4, 0x01, 0x02}},
{LCM_SLEEP(8)},
{LCM_SEND(12),{ 10, 0, 0xE5, 0x00, 0x04, 0x0B, 0x08, 0x06, 0x00, 0x20, 0x20, 0x00}},
{LCM_SLEEP(1)},
{LCM_SEND(15),{ 13, 0, 0xE6, 0x00, 0x00, 0x00, 0x05, 0x05, 0x10, 0x0A, 0x10, 0x20, 0x20, 0x00, 0x00}},
{LCM_SLEEP(1)},
{LCM_SEND(5),{3,0,0x51, 0x00,0x00}},
{LCM_SLEEP(5)},
{LCM_SEND(2),{0x55, 0x01}},
{LCM_SLEEP(5)},
{LCM_SEND(12),{ 10, 0, 0xCA, 0x24, 0x24, 0x24, 0x23, 0x23, 0x20, 0x20, 0x20, 0x20}},
{LCM_SLEEP(5)},
{LCM_SEND(2),{0x53, 0x2C}},
{LCM_SLEEP(5)},
};


static LCM_Force_Cmd_Code rd_prep_code[]={
//	{0x39, {LCM_SEND(8), {0x6, 0, 0xF0, 0x55, 0xAA, 0x52, 0x08, 0x01}}},
	{0x37, {LCM_SEND(2), {0x3, 0}}},
};
static int32_t lcd_hx8399c_init(struct panel_spec *self)
{
	int32_t i;
	LCM_Init_Code *init = init_data;
	unsigned int tag;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_dcs_write_t mipi_dcs_write = self->info.mipi->ops->mipi_dcs_write;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;
	
	LCD_PRINT("lcd_hx8399c_init \n");
	
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

static uint32_t hx8399c_readid(struct panel_spec *self)
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

	LCD_PRINT("sprdfb:hx8399c_readid!\n");

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
		printk("hx8399c_readid  0xDA value is 0x%x, 0x%x, 0x%x!\n", read_data[0], read_data[1], read_data[2]);

		if(0x83 == read_data[0]){
			printk("lcd_hx8399c_mipi read id success!\n");
			mipi_eotp_set(1,1);
			i2c_set_bus_num(3); //iwhale2 5
			read_rtn = i2c_reg_read(0x3E, 0x00);
			printk("lcd_hx8399c_mipi read i2c read_rtn 0x%x\n", read_rtn);
			
			if (0x0A != read_rtn) {
				i2c_reg_write(0x3E, 0x00, 0x0A);
				i2c_reg_write(0x3E, 0x01, 0x0A);
				i2c_reg_write(0x3E, 0x03, 0x03);
				i2c_reg_write(0x3E, 0xFF, 0x80);
				mdelay(50);
			}
			return 0x8399;
		}
	}
	mipi_eotp_set(1,1);
	return 0x0;
}

static int32_t hx8399c_reset(struct panel_spec *self)
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

static unsigned char set_bl_seq[5] = {
	0x03,0x00,0x51, 0x0F,0xFF
};

static int32_t hx8399c_set_brightness(struct panel_spec *self,uint16_t brightness)
{
	uint16_t temp;
	mipi_dcs_write_t mipi_dcs_write = self->info.mipi->ops->mipi_dcs_write;
	temp = 0x10*(unsigned char)brightness;
	set_bl_seq[3] = temp>>8;
	set_bl_seq[4] = (unsigned char)temp&0xFF;

	mipi_dcs_write(&set_bl_seq[0], 5);

	return 0;
}

static struct panel_operations lcd_hx8399c_mipi_operations = {
	.panel_init = lcd_hx8399c_init,
	.panel_readid = hx8399c_readid,
	.panel_reset = hx8399c_reset,
	.panel_set_brightness = hx8399c_set_brightness,
};

static struct timing_rgb lcd_hx8399c_mipi_timing = {
	.hfp = 156,  /* unit: pixel */
	.hbp = 32,
	.hsync = 32,
	.vfp = 25, /*unit: line*/
	.vbp = 20,
	.vsync = 4,
};


static struct info_mipi lcd_hx8399c_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 24, /*18,16*/
	.lan_number = 4,
	.phy_feq =960*1000,
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_hx8399c_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_hx8399c_mipi_spec = {
	.width = 1080,
	.height = 1920,
	.fps = 60,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.info = {
		.mipi = &lcd_hx8399c_mipi_info
	},
	.is_need_reset = 1,
	.ops = &lcd_hx8399c_mipi_operations,
};

