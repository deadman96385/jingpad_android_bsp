
#include <config.h>
#include <common.h>//huyue added 
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
	//Power setting Sequence
	{LCM_SEND(5),{3,0,0xC0,0x0A,0x0A}},
	{LCM_SEND(2),{0xc1,0x45}},
	{LCM_SEND(2),{0xc2, 0x00}},

	//Initializing Sequence
	{LCM_SEND(7),{5,0,0x2A,0x00,0x00,0x01,0x3F}},
	{LCM_SEND(7),{5,0,0x2B,0x00,0x00,0x01,0xDF}},
	{LCM_SEND(2),{0x36,0xc8}},
	{LCM_SEND(2),{0x3A,0x66}},
	{LCM_SEND(2),{0xB0,0x8c}},
	{LCM_SEND(2),{0xB4,0x02}},

	{LCM_SEND(6),{4,0,0xB6,0x32,0x22,0x3B}},
	{LCM_SEND(2),{0xB7,0xC6}},
	{LCM_SEND(5),{3,0,0xF9,0x00,0x08}},
	{LCM_SEND(7),{5,0,0xF7,0xA9,0x91,0x2D,0x8A}},
	{LCM_SEND(6),{4,0,0xF8,0x21,0x07,0x02}},
	{LCM_SEND(11),{9,0,0xF1,0x36,0x04,0x00,0x3C,0x0F,0x0F,0x04,0x02}},
	{LCM_SEND(12),{10,0,0xF2,0x18,0xA3,0x12,0x02,0xB2,0x12,0xFF,0x10,0x00}},
	{LCM_SEND(6),{4,0,0xFC,0x00,0x0C,0x80}},
	//gamma setting
	{LCM_SEND(18),{16,0,0xE0,0x01,0x15,0x17,0x0C,0x0F,0x07,0x44,0x65,0x35,0x07,0x12,0x04,0x09,0x06,0x06}},
	{LCM_SEND(18),{16,0,0xE1,0x0F,0x38,0x34,0x0B,0x0B,0x03,0x43,0x22,0x30,0x03,0x0E,0x03,0x21,0x1B,0x00}},
	// 3Gamma Setting Sequence
	{LCM_SEND(19),{17,0,0xE2,0x00,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x00}},
	{LCM_SEND(67),{65,0,0xE3,0x00,0x00,0x00,0x00,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00}},

	//Display on
	{LCM_SEND(1),{0x11}},
	{LCM_SLEEP(120)},
	{LCM_SEND(1),{0x29}},
	{LCM_SLEEP(100)},
};

static LCM_Init_Code disp_on[] =  {
	{LCM_SEND(1),{0x11}},
	{LCM_SLEEP(120)},
	{LCM_SEND(1),{0x29}},
	{LCM_SLEEP(100)},
};

static LCM_Init_Code sleep_in[] =  {
	{LCM_SEND(1), {0x28}},
	{LCM_SLEEP(50)}, 	//>150ms
	{LCM_SEND(1), {0x10}},
	{LCM_SLEEP(120)},	//>150ms
};

static LCM_Init_Code sleep_out[] =  {
	{LCM_SEND(1), {0x11}},
	{LCM_SLEEP(120)},//>120ms
	{LCM_SEND(1), {0x29}},
	{LCM_SLEEP(20)}, //>20ms
};

static int32_t ili9486s1_mipi_init(struct panel_spec *self)
{

	int32_t i;
	LCM_Init_Code *init = init_data;
	unsigned int tag;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_dcs_write_t mipi_dcs_write = self->info.mipi->ops->mipi_dcs_write;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	LCD_PRINT("ili9486s1_mipi_init\n");

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

static LCM_Force_Cmd_Code rd_prep_code[]={
		{0x37, {LCM_SEND(2), {0x3, 0}}},

};

static uint32_t ili9486s1_readid(struct panel_spec *self)
{
#if 0
	int32_t i = 0;
	uint32 j =0;
	LCM_Force_Cmd_Code * rd_prepare = rd_prep_code;
	uint8_t read_data[3] = {0};

	int32_t read_rtn = 0;
	unsigned int tag = 0;
	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_force_write_t mipi_force_write = self->info.mipi->ops->mipi_force_write;
	mipi_force_read_t mipi_force_read = self->info.mipi->ops->mipi_force_read;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	LCD_PRINT("ili9486s1_readid!\n");

	mipi_set_cmd_mode();
	mipi_eotp_set(0,0);

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

		read_rtn = mipi_force_read(0xd3, 3,(uint8_t *)read_data);
		LCD_PRINT("ili9486s1_readid, 0xd3  is 0x%x,0x%x,0x%x\n",read_data[0],read_data[1],read_data[2]);
	}

	mipi_eotp_set(1,1);
#endif
	return 0x8370;
}

static struct panel_operations lcd_ili9486s1_mipi_operations = {
	.panel_init = ili9486s1_mipi_init,
	.panel_readid = ili9486s1_readid,
};

static struct timing_rgb lcd_ili9486s1_mipi_timing = {
	.hfp = 30,  /* unit: pixel */
	.hbp = 26,
	.hsync = 0,
	.vfp = 12, /*unit: line*/
	.vbp = 8,
	.vsync = 1,
};


static struct info_mipi lcd_ili9486s1_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 18, /*18,16*/
	.lan_number = 1,
	.phy_feq =340*1000,
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_ili9486s1_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_ili9486s1_mipi_spec = {
	.width = 320,
	.height = 480,
	.fps = 60,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.info = {
		.mipi = &lcd_ili9486s1_mipi_info
	},
	.ops = &lcd_ili9486s1_mipi_operations,
};

