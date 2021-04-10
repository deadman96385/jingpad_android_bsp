/* drivers/video/sc8810/lcd_hx8363_rgb_spi.c
 *
 *
 *
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

#include <asm/arch/sprd_lcd.h>
#define printk printf

#define  LCD_DEBUG
#ifdef LCD_DEBUG
#define LCD_PRINT printk
#else
#define LCD_PRINT(...)
#endif

#define HX8363_SpiWriteCmd(cmd) \
{ \
	spi_send_cmd((cmd & 0xFF));\
}

#define  HX8363_SpiWriteData(data)\
{ \
	spi_send_data((data & 0xFF));\
}


static int32_t hx8363_init(struct panel_spec *self)
{
	uint32_t test_data[8] = {0};
	uint32_t left = 0;
	uint32_t top = 0;	
	uint32_t right = 480;
	uint32_t bottom = 800;		
	uint32_t data = 0;
	spi_send_cmd_t spi_send_cmd = self->info.rgb->bus_info.spi->ops->spi_send_cmd; 
	spi_send_data_t spi_send_data = self->info.rgb->bus_info.spi->ops->spi_send_data; 
	spi_read_t spi_read = self->info.rgb->bus_info.spi->ops->spi_read; 


	LCD_PRINT("VIVA_init\n");

	HX8363_SpiWriteCmd(0xB9); // SET password
	HX8363_SpiWriteData(0xFF); // 
	HX8363_SpiWriteData(0x83); // 
	HX8363_SpiWriteData(0x69); // 

	HX8363_SpiWriteCmd(0xB1);
	HX8363_SpiWriteData(0x0B);
	HX8363_SpiWriteData(0x83);
	HX8363_SpiWriteData(0xA7);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x11);
	HX8363_SpiWriteData(0x11); //
	HX8363_SpiWriteData(0x08); //
	HX8363_SpiWriteData(0x08); //the lower ,Saturation is better
	HX8363_SpiWriteData(0x0C); //the lower ,Saturation is better
	HX8363_SpiWriteData(0x22);


	HX8363_SpiWriteCmd(0xC6); // SET DISP
	HX8363_SpiWriteData(0x41); // 
	HX8363_SpiWriteData(0xFF); // 
	HX8363_SpiWriteData(0x7A); // 
	HX8363_SpiWriteData(0xFF); // 

	HX8363_SpiWriteCmd(0xE3);
	HX8363_SpiWriteData(0x00);//Column inversion
	HX8363_SpiWriteData(0x00); 
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x00);


	HX8363_SpiWriteCmd(0xC0); //Set_VCOM 
	HX8363_SpiWriteData(0x73);
	HX8363_SpiWriteData(0x50); //0x10
	HX8363_SpiWriteData(0x00); //0x10
	HX8363_SpiWriteData(0x34); //0x10
	HX8363_SpiWriteData(0xC4); //0x10
	HX8363_SpiWriteData(0x00); //0x10

// STEP 2


	HX8363_SpiWriteCmd(0x3A); // SET Panel
	HX8363_SpiWriteData(0x70); //

	HX8363_SpiWriteCmd(0xB3); // SET Panel
	HX8363_SpiWriteData(0x83); //
	HX8363_SpiWriteData(0x00); //
	HX8363_SpiWriteData(0x31); //
	HX8363_SpiWriteData(0x03); //
	HX8363_SpiWriteData(0x01); //
	HX8363_SpiWriteData(0x13); //
	HX8363_SpiWriteData(0x06); //

	HX8363_SpiWriteCmd(0xB4); // SET Panel
	HX8363_SpiWriteData(0x00); //

	HX8363_SpiWriteCmd(0xCC); // SET Panel
	HX8363_SpiWriteData(0x0C); //

	HX8363_SpiWriteCmd(0xEA); // SET Panel
	HX8363_SpiWriteData(0x72); //

	HX8363_SpiWriteCmd(0xB2); // SET Panel
	HX8363_SpiWriteData(0x03); //



	HX8363_SpiWriteCmd(0xD5);  // SET Gamma
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x0D);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x12);
	HX8363_SpiWriteData(0x40);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x01);
	HX8363_SpiWriteData(0x60);
	HX8363_SpiWriteData(0x37);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x0F);
	HX8363_SpiWriteData(0x01);
	HX8363_SpiWriteData(0x05);
	HX8363_SpiWriteData(0x47);
	HX8363_SpiWriteData(0x03);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x03);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x03);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x00); // 
	HX8363_SpiWriteData(0x18);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x89);
	HX8363_SpiWriteData(0x00);
	HX8363_SpiWriteData(0x11 );
	HX8363_SpiWriteData(0x33 );
	HX8363_SpiWriteData(0x55 );
	HX8363_SpiWriteData(0x77 );
	HX8363_SpiWriteData(0x31 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x98 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x66 );
	HX8363_SpiWriteData(0x44 );
	HX8363_SpiWriteData(0x22 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x02 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x89 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x22 );
	HX8363_SpiWriteData(0x44 );
	HX8363_SpiWriteData(0x66 );
	HX8363_SpiWriteData(0x20 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x98 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x77 );
	HX8363_SpiWriteData(0x55 );
	HX8363_SpiWriteData(0x33 );
	HX8363_SpiWriteData(0x11 );
	HX8363_SpiWriteData(0x13 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x01 );
	HX8363_SpiWriteData(0x00 );
	//G
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x03 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0xCF );
	HX8363_SpiWriteData(0xFF );
	HX8363_SpiWriteData(0xFF );
	HX8363_SpiWriteData(0x03 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0xCF );
	HX8363_SpiWriteData(0xFF );
	HX8363_SpiWriteData(0xFF );
	HX8363_SpiWriteData(0x20 );
	HX8363_SpiWriteData(0x8C );
	HX8363_SpiWriteData(0x5A );




	HX8363_SpiWriteCmd(0xE0); //COLMOD 
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x02 );
	HX8363_SpiWriteData(0x0D );
	HX8363_SpiWriteData(0x0C );
	HX8363_SpiWriteData(0x3F );
	HX8363_SpiWriteData(0x19 );
	HX8363_SpiWriteData(0x2D );
	HX8363_SpiWriteData(0x04 );
	HX8363_SpiWriteData(0x0F );
	HX8363_SpiWriteData(0x0E );
	HX8363_SpiWriteData(0x14 );
	HX8363_SpiWriteData(0x17 );
	HX8363_SpiWriteData(0x15 );
	HX8363_SpiWriteData(0x16 );
	HX8363_SpiWriteData(0x10 );
	HX8363_SpiWriteData(0x11 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x00 );
	HX8363_SpiWriteData(0x02 );
	HX8363_SpiWriteData(0x0c );
	HX8363_SpiWriteData(0x12 );
	HX8363_SpiWriteData(0x3F );
	HX8363_SpiWriteData(0x19 );
	HX8363_SpiWriteData(0x2C );
	HX8363_SpiWriteData(0x05 );
	HX8363_SpiWriteData(0x08 );
	HX8363_SpiWriteData(0x0E );
	HX8363_SpiWriteData(0x12 );
	HX8363_SpiWriteData(0x16 );
	HX8363_SpiWriteData(0x14 );
	HX8363_SpiWriteData(0x15 );
	HX8363_SpiWriteData(0x10 );
	HX8363_SpiWriteData(0x12 );
	HX8363_SpiWriteData(0x01 );


	HX8363_SpiWriteCmd(0x11); //COLMOD 
	udelay(120000); 
	HX8363_SpiWriteCmd(0x29); //COLMOD 





}

static int32_t hx8363_enter_sleep(struct panel_spec *self, uint8_t is_sleep)
{
	spi_send_cmd_t spi_send_cmd = self->info.rgb->bus_info.spi->ops->spi_send_cmd; 
	spi_send_data_t spi_send_data = self->info.rgb->bus_info.spi->ops->spi_send_data; 
	
	if(is_sleep==1){
		//Sleep In
		HX8363_SpiWriteCmd(0x28);
		udelay(120000); 
		HX8363_SpiWriteCmd(0x10);
		udelay(10000); 
	}else{
		//Sleep Out
		HX8363_SpiWriteCmd(0x11);
		udelay(120000); 
		HX8363_SpiWriteCmd(0x29);
		udelay(10000); 
	}

	return 0;
}




static int32_t hx8363_set_window(struct panel_spec *self,
		uint16_t left, uint16_t top, uint16_t right, uint16_t bottom)
{
	uint32_t *test_data[4] = {0};
	spi_send_cmd_t spi_send_cmd = self->info.rgb->bus_info.spi->ops->spi_send_cmd; 
	spi_send_data_t spi_send_data = self->info.rgb->bus_info.spi->ops->spi_send_data; 
	spi_read_t spi_read = self->info.rgb->bus_info.spi->ops->spi_read;
#if 0

	LCD_PRINT("zxdbg add -hx8363_set_window: %d, %d, %d, %d\n",left, top, right, bottom);

	HX8363_SpiWriteCmd(0x2A00); 
	HX8363_SpiWriteData((left>>8));// set left address
	HX8363_SpiWriteData((left&0xff));
	HX8363_SpiWriteData((right>>8));// set right address
	HX8363_SpiWriteData((right&0xff));

	HX8363_SpiWriteCmd(0x2B00); 
	HX8363_SpiWriteData((top>>8));// set left address
	HX8363_SpiWriteData((top&0xff));
	HX8363_SpiWriteData((bottom>>8));// set bottom address
	HX8363_SpiWriteData((bottom&0xff));

//	HX8363_SpiWriteCmd(0x2C00);

	HX8363_SpiWriteCmd(0x2A00); 
	spi_read(test_data);
	spi_read(test_data+1);
	HX8363_SpiWriteCmd(0x2B00); 
	spi_read(test_data+2);
	spi_read(test_data+3);
#endif
	LCD_PRINT("zxdbg add -hx8363_read read: %x, %x, %x, %x\n",test_data[0], test_data[1], test_data[2], test_data[3]);

	return 0;
}
static int32_t hx8363_invalidate(struct panel_spec *self)
{
	LCD_PRINT("hx8363_invalidate\n");

	return self->ops->panel_set_window(self, 0, 0,
		self->width - 1, self->height - 1);
}



static int32_t hx8363_invalidate_rect(struct panel_spec *self,
				uint16_t left, uint16_t top,
				uint16_t right, uint16_t bottom)
{
	LCD_PRINT("hx8363_invalidate_rect \n");

	return self->ops->panel_set_window(self, left, top,
			right, bottom);
}

static int32_t hx8363_read_id(struct panel_spec *self)
{
	int32_t id  = 0x62;
	spi_send_cmd_t spi_send_cmd = self->info.rgb->bus_info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data = self->info.rgb->bus_info.spi->ops->spi_send_data;
	spi_read_t spi_read = self->info.rgb->bus_info.spi->ops->spi_read;
/*
	HX8363_SpiWriteCmd(0xB9); // SET password
	HX8363_SpiWriteData(0xFF); //
	HX8363_SpiWriteData(0x83); //
	HX8363_SpiWriteData(0x63); //

	HX8363_SpiWriteCmd(0xFE); // SET SPI READ INDEX
	HX8363_SpiWriteData(0xF4); // GETHXID
	HX8363_SpiWriteCmd(0xFF); // GET SPI READ

	spi_read(&id);

	id &= 0xff;
*/
	LCD_PRINT(" hx8363_read_id u-boot id = %x\n",id);
#ifndef CONFIG_SPX15
	return id;
#else
	return 0x63;
#endif
}

static struct panel_operations lcd_hx8363_rgb_spi_operations = {
	.panel_init = hx8363_init,
	.panel_set_window = hx8363_set_window,
	.panel_invalidate_rect= hx8363_invalidate_rect,
	.panel_invalidate = hx8363_invalidate,
	.panel_enter_sleep = hx8363_enter_sleep,
	.panel_readid          = hx8363_read_id
};

static struct timing_rgb lcd_hx8363_rgb_timing = {
#if 1
	.hfp = 30,//10,  /* unit: pixel */
	.hbp = 55, //6,
	.hsync = 10, //8,
	.vfp = 6, // 3, /*unit: line*/
	.vbp = 19, // 3,
	.vsync = 6, // 4,
#else
	.hfp = 15,//10,  /* unit: pixel */
	.hbp = 15,//6,
	.hsync = 10, //8,
	.vfp = 8, // 3, /*unit: line*/
	.vbp = 8, // 3,
	.vsync = 6, // 4,
#endif	
};

static struct spi_info lcd_hx8363_rgb_spi_info = {
	.ops = NULL,
};

static struct info_rgb lcd_hx8363_rgb_info = {
	.cmd_bus_mode  = SPRDFB_RGB_BUS_TYPE_SPI,
	.video_bus_width = 24, /*18,16*/
	.h_sync_pol = SPRDFB_POLARITY_NEG,
	.v_sync_pol = SPRDFB_POLARITY_NEG,
	.de_pol = SPRDFB_POLARITY_POS,
	.timing = &lcd_hx8363_rgb_timing,
	.bus_info = {
		.spi = &lcd_hx8363_rgb_spi_info,
	}
};

struct panel_spec lcd_panel_hx8363_rgb_spi_spec_viva = {
	.width = 480,
	.height = 800,
	.fps = 60,
	.type = LCD_MODE_RGB,
	.direction = LCD_DIRECT_NORMAL,
	.info = {
		.rgb = &lcd_hx8363_rgb_info
	},
	.ops = &lcd_hx8363_rgb_spi_operations,
};
