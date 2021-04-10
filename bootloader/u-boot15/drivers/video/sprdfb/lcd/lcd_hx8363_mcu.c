/* drivers/video/sc8825/lcd_hx8363_mcu.c
 *
 * Support for nt35516 mipi LCD device
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

static int32_t hx8363_init(struct panel_spec *self)
{
	send_data_t send_cmd = self->info.mcu->ops->send_cmd;
	send_data_t send_data = self->info.mcu->ops->send_data;

	LCD_PRINT("hx8363_init\n");

	send_cmd(0xB9); // SET password
	send_data(0xFF); // 
	send_data(0x83); // 
	send_data(0x63); // 

	send_cmd(0xB0);//Enable internal oscillator
	send_data(0x01);
	send_data(0x0B);

	send_cmd(0xB1);
	send_data(0x01);
	send_data(0x00);
	send_data(0x44);
	send_data(0x08);
	send_data(0x01);
	send_data(0x11);
	send_data(0x11);
	send_data(0x36);
	send_data(0x3E);
	send_data(0x3F);
	send_data(0x3F);
	send_data(0x40);
	send_data(0x32);
	send_data(0x00);
	send_data(0xE6);
	send_data(0xE6);
	send_data(0xE6);
	send_data(0xE6);
	send_data(0xE6);

	send_cmd(0xB2); // SET DISP
	send_data(0x08); // 
	send_data(0x00); // 

	send_cmd(0xB4);
	send_data(0x00);//Column inversion
	send_data(0x18); 
	send_data(0x9C);
	send_data(0x08);
	send_data(0x18);
	send_data(0x04);
	send_data(0x72);//72

	send_cmd(0xB6);//Set_VCOM 
	send_data(0x1B); 

	send_cmd(0xCC);// SET Panel
	send_data(0x01); //

	LCD_DelayMS(5);

	send_cmd(0xE0); // SET Gamma
	send_data(0x00);
	send_data(0x05);
	send_data(0x07);
	send_data(0x0C);
	send_data(0x13);
	send_data(0x2F);
	send_data(0x0B);
	send_data(0x1D);
	send_data(0x86);
	send_data(0x0D);
	send_data(0x91);
	send_data(0x16);
	send_data(0x99);
	send_data(0x16);
	send_data(0x16);
	send_data(0x09);
	send_data(0x05);
	send_data(0x00);
	send_data(0x05);
	send_data(0x07);
	send_data(0x0C);
	send_data(0x13);
	send_data(0x2F);
	send_data(0x0B);
	send_data(0x1D);
	send_data(0x86);
	send_data(0x0D);
	send_data(0x91);
	send_data(0x16);
	send_data(0x99);
	send_data(0x16);
	send_data(0x16);
	send_data(0x09);
	send_data(0x05);

	send_cmd(0xC1); //COLMOD 
	send_data(0x01); // 
	//R
	send_data(0x07 );
	send_data(0x0A );
	send_data(0x1A );
	send_data(0x2F );
	send_data(0x3E );
	send_data(0x4A );
	send_data(0x52 );
	send_data(0x5A );
	send_data(0x62 );
	send_data(0x69 );
	send_data(0x70 );
	send_data(0x76 );
	send_data(0x7D );
	send_data(0x82 );
	send_data(0x86 );
	send_data(0x8C );
	send_data(0x93 );
	send_data(0x9A );
	send_data(0x9F );
	send_data(0xA4 );
	send_data(0xA9 );
	send_data(0xB0 );
	send_data(0xB6 );
	send_data(0xBB );
	send_data(0xC2 );
	send_data(0xC9 );
	send_data(0xCF );
	send_data(0xD7 );
	send_data(0xE0 );
	send_data(0xE7 );
	send_data(0xEF );
	send_data(0xF8 );
	send_data(0xFF );
	send_data(0x34 );
	send_data(0x1E );
	send_data(0x92 );
	send_data(0x9E );
	send_data(0x01 );
	send_data(0xE6 );
	send_data(0x08 );
	send_data(0x6F );
	send_data(0x02 );
	//G
	send_data(0x07 );
	send_data(0x0A );
	send_data(0x1A );
	send_data(0x2F );
	send_data(0x3E );
	send_data(0x4A );
	send_data(0x52 );
	send_data(0x5A );
	send_data(0x62 );
	send_data(0x69 );
	send_data(0x70 );
	send_data(0x76 );
	send_data(0x7D );
	send_data(0x82 );
	send_data(0x86 );
	send_data(0x8C );
	send_data(0x93 );
	send_data(0x9A );
	send_data(0x9F );
	send_data(0xA4 );
	send_data(0xA9 );
	send_data(0xB0 );
	send_data(0xB6 );
	send_data(0xBB );
	send_data(0xC2 );
	send_data(0xC9 );
	send_data(0xCF );
	send_data(0xD7 );
	send_data(0xE0 );
	send_data(0xE7 );
	send_data(0xEF );
	send_data(0xF8 );
	send_data(0xFF );
	send_data(0x34 );
	send_data(0x1E );
	send_data(0x92 );
	send_data(0x9E );
	send_data(0x01 );
	send_data(0xE6 );
	send_data(0x08 );
	send_data(0x6F );
	send_data(0x02 );
	//B
	send_data(0x07 );
	send_data(0x0A );
	send_data(0x1A );
	send_data(0x2F );
	send_data(0x3E );
	send_data(0x4A );
	send_data(0x52 );
	send_data(0x5A );
	send_data(0x62 );
	send_data(0x69 );
	send_data(0x70 );
	send_data(0x76 );
	send_data(0x7D );
	send_data(0x82 );
	send_data(0x86 );
	send_data(0x8C );
	send_data(0x93 );
	send_data(0x9A );
	send_data(0x9F );
	send_data(0xA4 );
	send_data(0xA9 );
	send_data(0xB0 );
	send_data(0xB6 );
	send_data(0xBB );
	send_data(0xC2 );
	send_data(0xC9 );
	send_data(0xCF );
	send_data(0xD7 );
	send_data(0xE0 );
	send_data(0xE7 );
	send_data(0xEF );
	send_data(0xF8 );
	send_data(0xFF );
	send_data(0x34 );
	send_data(0x1E );
	send_data(0x92 );
	send_data(0x9E );
	send_data(0x01 );
	send_data(0xE6 );
	send_data(0x08 );
	send_data(0x6F );
	send_data(0x02 );

	send_cmd(0x3A); //COLMOD 
	send_data(0x07); // 

	send_cmd(0x11);//Sleep Out 
	LCD_DelayMS(120);

	send_cmd(0xC2);// SET DISPIF 
	send_data(0x04); //24bit 
	send_cmd(0x35); //Tearing Effect 
	send_data(0x00); // 
	send_cmd(0x36);
	send_data(0x02); // 
	send_cmd(0x29); 
	LCD_DelayMS(10);
	send_cmd(0x2c);

    return 0;
}

static int32_t hx8363_enter_sleep(struct panel_spec *self, uint8_t is_sleep)
{
	send_data_t send_cmd = self->info.mcu->ops->send_cmd;
	send_data_t send_data = self->info.mcu->ops->send_data;

	if(is_sleep==1){
		//Sleep In
		send_cmd(0x28);
		LCD_DelayMS(120); 
		send_cmd(0x10);
		LCD_DelayMS(120); 
	}else{
		//Sleep Out
		send_cmd(0x11);
		LCD_DelayMS(120); 
		send_cmd(0x29);
		LCD_DelayMS(120); 
	}

	return 0;
}




static int32_t hx8363_set_window(struct panel_spec *self,
		uint16_t left, uint16_t top, uint16_t right, uint16_t bottom)
{
	send_data_t send_cmd = self->info.mcu->ops->send_cmd;
	send_data_t send_data = self->info.mcu->ops->send_data;

	LCD_PRINT("hx8363_set_window\n");

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

	send_cmd(0x2C); //Write data

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
	int32_t id  = 0;
	send_data_t send_cmd = self->info.mcu->ops->send_cmd;
	read_data_t read_data = self->info.mcu->ops->read_data;
	send_data_t send_data = self->info.mcu->ops->send_data;

	//Get ID
	//to be added here
/*
	int32_t   chip_id = 0;
	send_cmd(0xDA);
	chip_id = read_data();
	LCD_PRINT("hx8363_read_id1  0XDA = 0x%x!\n", chip_id);
	chip_id = read_data();
	LCD_PRINT("hx8363_read_id2  0XDA = 0x%x!\n", chip_id);
	send_cmd(0xDB);
	chip_id = read_data();
	LCD_PRINT("hx8363_read_id1  0XDB = 0x%x!\n", chip_id);
	chip_id = read_data();
	LCD_PRINT("hx8363_read_id2  0XDB = 0x%x!\n", chip_id);
	send_cmd(0xDC);
	chip_id = read_data();
	LCD_PRINT("hx8363_read_id1  0XDB = 0x%x!\n", chip_id);
	chip_id = read_data();
	LCD_PRINT("hx8363_read_id2  0XDC = 0x%x!\n", chip_id);
*/
	return 0x18; // id;
}

static struct panel_operations lcd_hx8363_mcu_operations = {
	.panel_init = hx8363_init,
	.panel_set_window = hx8363_set_window,
	.panel_invalidate_rect= hx8363_invalidate_rect,
	.panel_invalidate = hx8363_invalidate,
	.panel_enter_sleep = hx8363_enter_sleep,
	.panel_readid          = hx8363_read_id
};

static struct timing_mcu lcd_hx8363_mcu_timing[] = {
[0] = {                    // read/write register timing
		.rcss = 15,  // 15ns
		.rlpw = 60,
		.rhpw = 60,
		.wcss = 10,
		.wlpw = 35,
		.whpw = 35,
	},
[1] = {                    // read/write gram timing
		.rcss = 15,  // 15ns
		.rlpw = 60,
		.rhpw = 60,
		.wcss = 0,
		.wlpw = 16,
		.whpw = 16,
	},
};

static struct info_mcu lcd_hx8363_mcu_info = {
	.bus_mode = LCD_BUS_8080,
	.bus_width = 24,
	.bpp = 24,
	.timing =lcd_hx8363_mcu_timing,
	.ops = NULL,
};

struct panel_spec lcd_hx8363_mcu_spec = {
	.width = 480,
	.height = 854,
	.type = LCD_MODE_MCU,
	.direction = LCD_DIRECT_NORMAL,
	.info = {.mcu = &lcd_hx8363_mcu_info},
	.ops = &lcd_hx8363_mcu_operations,
};


