/*     
	 * IC       :s6e3fa3
	 * module   :AMS549KU01
	 * source   :copy from AMS549KU01 datesheet
	 * Copyright:20160304  bring up whale2 board
	 ------------------
	 * filename :lcd_s6e3fa3_mipi_fhd.dtsi
	 * FHD / OLED 
	 * Read-id :  DA-0X40
	              DB-0X00
	              DC-0X01 
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

// copy form whale test2
static LCM_Init_Code init_data[] = {
{LCM_SEND(1), {0x11}}, //Sleep Out
{LCM_SLEEP(120)},

{LCM_SEND(5), {3, 0, 0xf0, 0x5a, 0x5a} },
{LCM_SEND(5), {3, 0, 0xfC, 0x5a, 0x5a} },

{LCM_SEND(2), {0x35, 0x00} },
{LCM_SEND(2), {0xb0, 0x1e}},
{LCM_SEND(2), {0xfd, 0xb2}},
{LCM_SEND(2), {0xcc, 0x4c} },
{LCM_SEND(2), {0xed, 0x44} },


//------------
{LCM_SEND(38), {36,0,0xca, 0x01 , 0x00 , 0x01 , 0x00 , 0x01 , 0x00 , 0x80 ,
					0x80 , 0x80 , 0x80 , 0x80 , 0x80 , 0x80 , 0x80 , 0x80 ,
					0x80 , 0x80 , 0x80 , 0x80 , 0x80 , 0x80 , 0x80 , 0x80 ,
					0x80 , 0x80 , 0x80 , 0x80 , 0x80 , 0x80 , 0x80 ,
					0x00 , 0x00 , 0x00 , 0x00 , 0x00}},
{LCM_SEND(5), {3,0,0xb2, 0x40,0xe4}},
{LCM_SEND(5), {3,0,0xb6, 0xbc,0x04}},
{LCM_SEND(2), {0xF7, 0x03}},

//------------
{LCM_SEND(5), {3,0,0xb6, 0xbc,0x04}},
{LCM_SEND(2), {0xF7, 0x03}},
//------------
{LCM_SEND(5), {3,0,0xb6, 0xbc,0x04}},
{LCM_SEND(2), {0xb5, 0x50}},
{LCM_SEND(2), {0x53, 0x00}},
	
//------------
{LCM_SEND(5), {3,0,0xb6, 0xbc,0x04}},
{LCM_SEND(2), {0xb5, 0x50}},
{LCM_SEND(2), {0x55, 0x02}},

{LCM_SEND(5), {3, 0, 0xfC, 0xa5, 0xa5} },
{LCM_SEND(5), {3, 0, 0xf0, 0xa5, 0xa5} },

{LCM_SLEEP(120)},
{LCM_SEND(1), {0x29}}, //Display On
{LCM_SLEEP(120)},
};


static LCM_Force_Cmd_Code rd_prep_code[]={
//	{0x39, {LCM_SEND(8), {0x6, 0, 0xF0, 0x55, 0xAA, 0x52, 0x08, 0x01}}},
	{0x37, {LCM_SEND(2), {0x5, 0}}},
};

static int32_t s6e3fa3_mipi_init(struct panel_spec *self)
{
	int32_t i = 0;
	LCM_Init_Code *init = init_data;
	unsigned int tag;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;

	mipi_set_hs_mode_t mipi_set_hs_mode = self->info.mipi->ops->mipi_set_hs_mode;

	LCD_PRINT("sprdfb:s6e3fa3_mipi_init\n");

	//mipi_set_hs_mode();
	mipi_set_cmd_mode();

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
	LCD_PRINT("sprdfb:s6e3fa3_mipi_init-----end\n");
	return 0;
}

static uint32_t s6e3fa3_readid(struct panel_spec *self)
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

	LCD_PRINT("sprdfb:lcd_s6e3fa3_mipi read id!\n");

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
		read_rtn = mipi_force_read(0xda, 1,(uint8_t *)read_data);
		printk("lcd_s6e3fa3_mipi read id 0xda value is 0x%x!\n", read_data[0]);

		if(0x42 == read_data[0]){
			printk("lcd_s6e3fa3_mipi read id success!\n");
			mipi_eotp_set(1,1);
			return 0x400001;
		}
	}
	mipi_eotp_set(1,1); 

printk("lcd_s6e3fa3_mipi read id failed!\n");

return 0;

}

int32_t s6e3fa3_reset(struct panel_spec *self)
{
	sprd_gpio_request(NULL, LCM_GPIO_2V8);
	sprd_gpio_direction_output(NULL, LCM_GPIO_2V8, 1);
	
	sprd_gpio_request(NULL, LCM_GPIO_1V8);
	sprd_gpio_direction_output(NULL, LCM_GPIO_1V8, 1);

	sprd_gpio_request(NULL, LCM_GPIO_RSTN);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 1);
	mdelay(5);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 0);
	mdelay(5);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 1);
	mdelay(20);

	return 0;
}

static struct panel_operations lcd_s6e3fa3_mipi_operations = {
	.panel_init = s6e3fa3_mipi_init,
	.panel_readid = s6e3fa3_readid,
	.panel_reset = s6e3fa3_reset,
};

static struct timing_rgb lcd_s6e3fa3_mipi_timing = {
	.hfp = 32,
	.hbp = 4,
	.hsync =8,
	.vfp = 7,
	.vbp = 9,
	.vsync = 7,
};

static struct info_mipi lcd_s6e3fa3_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_CMD,
	.video_bus_width = 24, /*18,16*/
	.lan_number = 4,
	.phy_feq = 1000*1000,
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_s6e3fa3_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_s6e3fa3_mipi_spec = {
	.width = 1080,
	.height = 1920,
	.fps = 60,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.is_need_reset = 1,
	.non_continue_clk_en = 1,
	.info = {
		.mipi = &lcd_s6e3fa3_mipi_info
	},
	.ops = &lcd_s6e3fa3_mipi_operations,
};

