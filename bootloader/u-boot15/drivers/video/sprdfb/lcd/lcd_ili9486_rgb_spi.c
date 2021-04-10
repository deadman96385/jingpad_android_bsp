/* drivers/video/sc8810/lcd_ili9486_rgb_spi.c
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

#define ili9486_SpiWriteCmd(cmd) \
{ \
	spi_send_cmd((cmd & 0xFF));\
}

#define  ili9486_SpiWriteData(data)\
{ \
	spi_send_data((data & 0xFF));\
}

static int32_t ili9486_init(struct panel_spec *self)
{
    uint32_t test_data[8] = {0};
    uint32_t left = 0;
    uint32_t top = 0;
    uint32_t right = 480;
    uint32_t bottom = 854;
    uint32_t data = 0;
    spi_send_cmd_t spi_send_cmd = self->info.rgb->bus_info.spi->ops->spi_send_cmd;
    spi_send_data_t spi_send_data = self->info.rgb->bus_info.spi->ops->spi_send_data;
    spi_read_t spi_read = self->info.rgb->bus_info.spi->ops->spi_read;

    LCD_PRINT("ili9486_init\n");

    ili9486_SpiWriteCmd(0xC0);
    ili9486_SpiWriteData(0x15);
    ili9486_SpiWriteData(0x15);

    ili9486_SpiWriteCmd(0xC1);
    ili9486_SpiWriteData(0x42);

    ili9486_SpiWriteCmd(0xC2);
    ili9486_SpiWriteData(0x22);

    ili9486_SpiWriteCmd(0xC5);
    ili9486_SpiWriteData(0x00);
    ili9486_SpiWriteData(0x3A);

    //Display parameter setting
    ili9486_SpiWriteCmd(0x2A);
    ili9486_SpiWriteData(0x00);
    ili9486_SpiWriteData(0x00);
    ili9486_SpiWriteData(0x01);
    ili9486_SpiWriteData(0x3F);

    ili9486_SpiWriteCmd(0x2B);
    ili9486_SpiWriteData(0x00);
    ili9486_SpiWriteData(0x00);
    ili9486_SpiWriteData(0x01);
    ili9486_SpiWriteData(0xDF);

    ili9486_SpiWriteCmd(0x36);
    ili9486_SpiWriteData(0x08);

    ili9486_SpiWriteCmd(0x35);
    ili9486_SpiWriteData(0x00);

    ili9486_SpiWriteCmd(0x3A);
    ili9486_SpiWriteData(0x66);

    ili9486_SpiWriteCmd(0xB0);
    ili9486_SpiWriteData(0x80);

    ili9486_SpiWriteCmd(0xB4);
    ili9486_SpiWriteData(0x02);

    ili9486_SpiWriteCmd(0xB5);
    ili9486_SpiWriteData(0x0C);
    ili9486_SpiWriteData(0x08);
    ili9486_SpiWriteData(0x2C);
    ili9486_SpiWriteData(0x26);

    ili9486_SpiWriteCmd(0xB6);
    ili9486_SpiWriteData(0x20);//(0x32)//123,(0x20);
    ili9486_SpiWriteData(0x42);//0x42
    ili9486_SpiWriteData(0x3B);

    ili9486_SpiWriteCmd(0xB7);
    ili9486_SpiWriteData(0x07);

    ili9486_SpiWriteCmd(0xF9);
    ili9486_SpiWriteData(0x00);
    ili9486_SpiWriteData(0x08);

    //Gamma setting
    ili9486_SpiWriteCmd(0xE0);
    ili9486_SpiWriteData(0x1E);
    ili9486_SpiWriteData(0x21);
    ili9486_SpiWriteData(0x1F);
    ili9486_SpiWriteData(0x0C);
    ili9486_SpiWriteData(0x0B);
    ili9486_SpiWriteData(0x0C);
    ili9486_SpiWriteData(0x4E);
    ili9486_SpiWriteData(0xB9);
    ili9486_SpiWriteData(0x40);
    ili9486_SpiWriteData(0x07);
    ili9486_SpiWriteData(0x16);
    ili9486_SpiWriteData(0x06);
    ili9486_SpiWriteData(0x12);
    ili9486_SpiWriteData(0x12);
    ili9486_SpiWriteData(0x00);

    ili9486_SpiWriteCmd(0xE1);
    ili9486_SpiWriteData(0x1F);
    ili9486_SpiWriteData(0x2A);
    ili9486_SpiWriteData(0x25);
    ili9486_SpiWriteData(0x0C);
    ili9486_SpiWriteData(0x11);
    ili9486_SpiWriteData(0x09);
    ili9486_SpiWriteData(0x4C);
    ili9486_SpiWriteData(0x42);
    ili9486_SpiWriteData(0x35);
    ili9486_SpiWriteData(0x08);
    ili9486_SpiWriteData(0x09);
    ili9486_SpiWriteData(0x02);
    ili9486_SpiWriteData(0x26);
    ili9486_SpiWriteData(0x23);
    ili9486_SpiWriteData(0x00);

    ili9486_SpiWriteCmd(0xF8);
    ili9486_SpiWriteData(0x21);
    ili9486_SpiWriteData(0x07);
    ili9486_SpiWriteData(0x02);

    ili9486_SpiWriteCmd(0xE2);
    ili9486_SpiWriteData(0x00);
    ili9486_SpiWriteData(0x09);
    ili9486_SpiWriteData(0x09);
    ili9486_SpiWriteData(0x09);
    ili9486_SpiWriteData(0x09);
    ili9486_SpiWriteData(0x09);
    ili9486_SpiWriteData(0x09);
    ili9486_SpiWriteData(0x09);
    ili9486_SpiWriteData(0x09);
    ili9486_SpiWriteData(0x09);
    ili9486_SpiWriteData(0x09);
    ili9486_SpiWriteData(0x09);
    ili9486_SpiWriteData(0x09);
    ili9486_SpiWriteData(0x09);
    ili9486_SpiWriteData(0x09);
    ili9486_SpiWriteData(0x00);

    ili9486_SpiWriteCmd(0xE3);
    ili9486_SpiWriteData(0x00);
    ili9486_SpiWriteData(0x00);
    ili9486_SpiWriteData(0x00);

    ili9486_SpiWriteData(0x00);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x04);
    ili9486_SpiWriteData(0x00);

    ili9486_SpiWriteCmd(0xF4);
    ili9486_SpiWriteData(0x00);
    ili9486_SpiWriteData(0x00);
    ili9486_SpiWriteData(0x08);
    ili9486_SpiWriteData(0x91);
    ili9486_SpiWriteData(0x04);

    ili9486_SpiWriteCmd(0xF2);
    ili9486_SpiWriteData(0x18);
    ili9486_SpiWriteData(0xA3);
    ili9486_SpiWriteData(0x12);
    ili9486_SpiWriteData(0x02);
    ili9486_SpiWriteData(0x82);
    ili9486_SpiWriteData(0x32);
    ili9486_SpiWriteData(0xFF);
    ili9486_SpiWriteData(0x10);
    ili9486_SpiWriteData(0x00);

    ili9486_SpiWriteCmd(0xFC);
    ili9486_SpiWriteData(0x00);
    ili9486_SpiWriteData(0x00);
    ili9486_SpiWriteData(0x83);
#if 1
    //Display on
    ili9486_SpiWriteCmd(0x11); // (SLPOUT)

    LCD_DelayMS(120); // 100ms

    ili9486_SpiWriteCmd(0x29); // (DISPON)

    LCD_DelayMS(100); // 100ms
#else
	if (1) { //  for test the lcd
		int i;
		ili9486_SpiWriteCmd(0x2C); //Write data
		for (i = 0; i < 480*320/3; i++)
			ili9486_SpiWriteData(0xff);
		for (i = 0; i < 480*320/3; i++)
			ili9486_SpiWriteData(0xff00);
		for (i = 0; i < 480*320/3; i++)
			ili9486_SpiWriteData(0xff0000);
	}
	ili9486_SpiWriteCmd(0x29); //Display On
	LCD_DelayMS(120); //120ms
	ili9486_SpiWriteCmd(0x2C); //Write data
	LCD_DelayMS(1200); //120ms
#endif
	LCD_PRINT("ili9486_init: end\n");

	return 0;
}

static int32_t ili9486_enter_sleep(struct panel_spec *self, uint8_t is_sleep)
{
	spi_send_cmd_t spi_send_cmd = self->info.rgb->bus_info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data = self->info.rgb->bus_info.spi->ops->spi_send_data;

	if(is_sleep==1){
		//Sleep In
		ili9486_SpiWriteCmd(0x28);
		udelay(120000);
		ili9486_SpiWriteCmd(0x10);
		udelay(10000);
	}else{
		//Sleep Out
		ili9486_SpiWriteCmd(0x11);
		udelay(120000);
		ili9486_SpiWriteCmd(0x29);
		udelay(10000);
	}

	return 0;
}

static int32_t ili9486_set_window(struct panel_spec *self,
		uint16_t left, uint16_t top, uint16_t right, uint16_t bottom)
{
	uint32_t *test_data[4] = {0};
	spi_send_cmd_t spi_send_cmd = self->info.rgb->bus_info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data = self->info.rgb->bus_info.spi->ops->spi_send_data;
	spi_read_t spi_read = self->info.rgb->bus_info.spi->ops->spi_read;
	LCD_PRINT("zxdbg add -ili9486_read read: %x, %x, %x, %x\n",test_data[0], test_data[1], test_data[2], test_data[3]);

	return 0;
}
static int32_t ili9486_invalidate(struct panel_spec *self)
{
	LCD_PRINT("ili9486_invalidate\n");

	return self->ops->panel_set_window(self, 0, 0,
		self->width - 1, self->height - 1);
}



static int32_t ili9486_invalidate_rect(struct panel_spec *self,
				uint16_t left, uint16_t top,
				uint16_t right, uint16_t bottom)
{
	LCD_PRINT("ili9486_invalidate_rect \n");

	return self->ops->panel_set_window(self, left, top,
			right, bottom);
}

static int32_t ili9486_read_id(struct panel_spec *self)
{
#if 0
	int32_t id  = 0x62;
	spi_send_cmd_t spi_send_cmd = self->info.rgb->bus_info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data = self->info.rgb->bus_info.spi->ops->spi_send_data;
	spi_read_t spi_read = self->info.rgb->bus_info.spi->ops->spi_read;

	ili9486_SpiWriteCmd(0xDA); // SET password

	spi_read(&id);
	id &= 0xff;
#endif
	//LCD_PRINT(" ili9486_read_id u-boot id = %x\n",id);
#ifndef CONFIG_SPX15
	//return id;
#else
	return 0x9486;
#endif
}

static struct panel_operations lcd_ili9486_rgb_spi_operations = {
	.panel_init = ili9486_init,
	.panel_set_window = ili9486_set_window,
	.panel_invalidate_rect= ili9486_invalidate_rect,
	.panel_invalidate = ili9486_invalidate,
	.panel_enter_sleep = ili9486_enter_sleep,
	.panel_readid          = ili9486_read_id
};

static struct timing_rgb lcd_ili9486_rgb_timing = {
	.hfp = 30,//10,  /* unit: pixel */
	.hbp = 26, //6,
	.hsync = 4, //8,
	.vfp = 12, // 3, /*unit: line*/
	.vbp = 8, // 3,
	.vsync = 2, // 4,
};

static struct spi_info lcd_ili9486_rgb_spi_info = {
	.ops = NULL,
};

static struct info_rgb lcd_ili9486_rgb_info = {
	.cmd_bus_mode  = SPRDFB_RGB_BUS_TYPE_SPI,
	.video_bus_width = 18, /*18,16*/
	.h_sync_pol = SPRDFB_POLARITY_NEG,
	.v_sync_pol = SPRDFB_POLARITY_NEG,
	.de_pol = SPRDFB_POLARITY_POS,
	.timing = &lcd_ili9486_rgb_timing,
	.bus_info = {
		.spi = &lcd_ili9486_rgb_spi_info,
	}
};

struct panel_spec lcd_panel_ili9486_rgb_spi = {
	.width = 320,
	.height = 480,
	.fps = 61,
	.type = LCD_MODE_RGB,
	.direction = LCD_DIRECT_NORMAL,
	.info = {
		.rgb = &lcd_ili9486_rgb_info
	},
	.ops = &lcd_ili9486_rgb_spi_operations,
};

