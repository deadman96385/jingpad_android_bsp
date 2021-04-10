/* drivers/video/sc8810/lcd_ili9341.c
 *
 * Support for ili9341 LCD device
 *
 */

#include <asm/arch/sprd_lcd.h>

#define printk printf

#define  LCD_DEBUG
#ifdef LCD_DEBUG
#define LCD_PRINT printk
#else
#define LCD_PRINT(...)
#endif

static int32_t ili9341_init(struct panel_spec *self)
{
	send_data_t send_cmd = self->info.mcu->ops->send_cmd;
	send_data_t send_data = self->info.mcu->ops->send_data;

	LCD_PRINT("ili9341_init\n");

	//Power Setting
	send_cmd(0xCF);
	send_data(0x00);
	send_data(0xE1);
	send_data(0x30);

	send_cmd(0xED);
	send_data(0x64);
	send_data(0x03);
	send_data(0x12);
	send_data(0x81);

	send_cmd(0xCB);
	send_data(0x39);
	send_data(0x2C);
	send_data(0x00);
	send_data(0x34);
	send_data(0x02);

	send_cmd(0xF7);
	send_data(0x20);

	send_cmd(0xEA);
	send_data(0x00);
	send_data(0x00);

	send_cmd(0xC5);
	send_data(0x4C);
        send_data(0x2B);

	send_cmd(0xC7);
	send_data(0x00);

	send_cmd(0xC0);
	send_data(0x22);

	send_cmd(0xC1);
	send_data(0x11);

        //Initializing Sequence
	send_cmd(0x35);
	send_data(0x00);

	send_cmd(0x36);
	send_data(0x08);

	send_cmd(0x3A);
	send_data(0x05);

	send_cmd(0xF2);
	send_data(0x02);

	send_cmd(0xB6);
	send_data(0x01);
	send_data(0xC2);

	send_cmd(0xF6);
	send_data(0x01);
	send_data(0x10);
	send_data(0x00);

	send_cmd(0xB1);
	send_data(0x00);
	send_data(0x1A);

	send_cmd(0xB5);
	send_data(0x02);
	send_data(0x02);
	send_data(0x0A);
	send_data(0x14);

	send_cmd(0xE8);
	send_data(0x85);
	send_data(0x01);
	send_data(0x78);

        //Gamma Setting
	send_cmd(0xE0);
	send_data(0x0F);
	send_data(0x31);
	send_data(0x2F);
	send_data(0x0D);
	send_data(0x10);
	send_data(0x08);
	send_data(0x5F);
	send_data(0xB6);
	send_data(0x50);
	send_data(0x07);
	send_data(0x14);
	send_data(0x07);
	send_data(0x2A);
	send_data(0x1F);
	send_data(0x08);

	send_cmd(0xE1);
	send_data(0x00);
	send_data(0x0E);
	send_data(0x10);
	send_data(0x04);
	send_data(0x10);
	send_data(0x04);
	send_data(0x23);
	send_data(0x54);
	send_data(0x35);
	send_data(0x03);
	send_data(0x0B);
	send_data(0x09);
	send_data(0x20);
	send_data(0x2A);
	send_data(0x08);

	send_cmd(0xE2);
	send_data(0x00);
	send_data(0x00);
	send_data(0x00);
	send_data(0x00);
	send_data(0x00);
	send_data(0x00);
	send_data(0x00);
	send_data(0x00);
	send_data(0x00);
	send_data(0x00);
	send_data(0x00);
	send_data(0x00);
	send_data(0x00);
	send_data(0x00);
	send_data(0x00);
	send_data(0x00);

	send_cmd(0xE3);
	send_data(0x00);
	send_data(0x00);
	send_data(0x00);
	send_data(0x00);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x22);
	send_data(0x22);
	send_data(0x22);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x33);
	send_data(0x03);
	send_data(0x03);
	send_data(0x03);
	send_data(0x03);
	send_data(0x03);
	send_data(0x03);
	send_data(0x03);
	send_data(0x03);
	send_data(0x03);
	send_data(0x03);
	send_data(0x03);
	send_data(0x02);
	send_data(0x01);
	send_data(0x00);

#if 1
	send_cmd(0x11); // (SLPOUT)
	LCD_DelayMS(10); // 100ms
	send_cmd(0x29); // (DISPON)
	LCD_DelayMS(10); // 100ms
#else
	if (1) { //  for test the lcd
		int i;
		send_cmd(0x2C); //Write data
		for (i = 0; i < 240*320/3; i++)
			send_data(0xff);
		for (i = 0; i < 240*320/3; i++)
			send_data(0xff00);
		for (i = 0; i < 240*320/3; i++)
			send_data(0xff0000);
	}
        //Display on
	send_cmd(0x11); // (SLPOUT)
	LCD_DelayMS(120); // 100ms
	send_cmd(0x29); //Display On
	LCD_DelayMS(120); //120ms
	send_cmd(0x2C); //Write data
	LCD_DelayMS(1200); //120ms
#endif
	LCD_PRINT("ili9341_init: end\n");

	return 0;
}

static int32_t ili9341_set_window(struct panel_spec *self,
		uint16_t left, uint16_t top, uint16_t right, uint16_t bottom)
{
	send_data_t send_cmd = self->info.mcu->ops->send_cmd;
	send_data_t send_data = self->info.mcu->ops->send_data;

	LCD_PRINT("ili9341_set_window\n");

	send_cmd(0x2A); // col
	send_data((left >> 8));
	send_data((left & 0xFF));
	send_data((right >> 8));
	send_data((right & 0xFF));

	send_cmd(0x2B); // row
	send_data((top >> 8));
	send_data((top & 0xFF));
	send_data((bottom >> 8));
	send_data((bottom & 0xFF));

	send_cmd(0x2C);

	return 0;
}


static int32_t ili9341_invalidate(struct panel_spec *self)
{
	LCD_PRINT("ili9341_invalidate\n");

	return self->ops->panel_set_window(self, 0, 0,
			self->width-1, self->height-1);
}

static int32_t ili9341_invalidate_rect(struct panel_spec *self,
				uint16_t left, uint16_t top,
				uint16_t right, uint16_t bottom)
{

	LCD_PRINT("ili9341_invalidate_rect : (%d, %d, %d, %d)\n",left, top, right, bottom);


	return self->ops->panel_set_window(self, left, top,
			right, bottom);
}

static int32_t ili9341_set_direction(struct panel_spec *self, uint16_t direction)
{

	LCD_PRINT("ili9341_set_direction\n");
	return 0;
}

static int32_t ili9341_enter_sleep(struct panel_spec *self, uint8_t is_sleep)
{
	send_data_t send_cmd = self->info.mcu->ops->send_cmd;

	if(is_sleep) {
		//send_cmd(0x10);
		LCD_DelayMS(120);
	}
	else {
		//send_cmd(0x11);
		LCD_DelayMS(120);
	}
	return 0;
}

static int32_t ili9341_read_id(struct panel_spec *self)
{
	int32_t read_value = 0;
	send_data_t send_cmd = self->info.mcu->ops->send_cmd;
	read_data_t read_data = self->info.mcu->ops->read_data;

	send_cmd(0x04);

	read_data();
	read_value += read_data()<< 16;
	read_value += read_data()<< 8;
	read_value += read_data();

	LCD_PRINT("ili9341_read_id=%x\n",read_value);
    read_value = 0x9341;
	return read_value;
}

static struct panel_operations lcd_ili9341_operations = {
	.panel_init            = ili9341_init,
	.panel_set_window      = ili9341_set_window,
	.panel_invalidate      = ili9341_invalidate,
	//.lcd_invalidate_rect = ili9341_invalidate_rect,
	.panel_set_direction   = ili9341_set_direction,
	.panel_enter_sleep     = ili9341_enter_sleep,
	.panel_readid         = ili9341_read_id,
};

static struct timing_mcu lcd_ili9341_timing[] = {
	[0] = {
		.rcss = 25,
		.rlpw = 45,
		.rhpw = 90,
		.wcss = 30,
		.wlpw = 20,
		.whpw = 20,
	},
	[1] = {
		.rcss = 25,
		.rlpw = 45,
		.rhpw = 90,
		.wcss = 30,
		.wlpw = 20,
		.whpw = 20,
	}
};

static struct info_mcu lcd_ili9341_info = {
	.bus_mode = LCD_BUS_8080,
	.bus_width = 16,
	.bpp = 16,
	.timing = &lcd_ili9341_timing,
	.ops = NULL,
};

struct panel_spec lcd_panel_ili9341 = {
	.width = 240,
	.height = 320,
	.fps  = 60,
	.type = LCD_MODE_MCU,
	.direction = LCD_DIRECT_NORMAL,
	.info = {
                 .mcu = &lcd_ili9341_info
                },
	.ops = &lcd_ili9341_operations,
};

