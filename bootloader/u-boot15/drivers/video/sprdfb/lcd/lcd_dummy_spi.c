/* drivers/video/sc8810/lcd_dummy_spi.c
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
#define REG32(x)              (*((volatile uint32 *)(x)))
#define dummy_SpiWriteCmd(cmd) \
{ \
	spi_send_cmd((cmd & 0xFF));\
}

#define  dummy_SpiWriteData(data)\
{ \
	spi_send_data((data & 0xFF));\
}

#define  dummy_SpiRead(data,len)\
{ \
	spi_read(data,len);\
}
#define BGRA32toRBG565(b,g,r)		((((r>>3)&0x1f)<<11)|(((g>>2)&0x3f)<<5)|(((b>>3)&0x1f)<<0))
#define DUMMY_SPI_SPEED 		(48*1000*1000UL)
#define	SPI_MODE_0	(0|0)

static int32_t dummy_refresh(struct panel_spec *self,void *base)
{
	int i = 0;
	uint16_t *prgb = (uint16_t *)base;
	uint16_t rgb;
	LCD_PRINT("spi_dummy_freshbuffer\r\n");
	spi_send_cmd_t spi_send_cmd = self->info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data = self->info.spi->ops->spi_send_data;
	spi_read_t spi_read = self->info.spi->ops->spi_read;

	for(i = 0 ; i < 240*320;i++)
	{
		rgb = *prgb++;
		dummy_SpiWriteData(rgb>>8);
		dummy_SpiWriteData(rgb&0xff);
	}
	dummy_SpiWriteCmd(0x29);
	return 0;
}
static int32_t dummy_reset(void)
{
	LCD_PRINT("lcd_dummy_spi reset!\n");
}

static int32_t dummy_init(struct panel_spec *self)
{
	LCD_PRINT("lcd_dummy_spi init!\n");
	return 0xFFFF;
}

static int32_t dummy_enter_sleep(struct panel_spec *self, uint8_t is_sleep)
{
	return 0;
}



static int32_t dummy_set_window(struct panel_spec *self,
		uint16_t left, uint16_t top, uint16_t right, uint16_t bottom)
{
	return 0;
}
static int32_t dummy_invalidate(struct panel_spec *self)
{
	LCD_PRINT("dummy_invalidate\n");
	return 0;
}



static int32_t dummy_invalidate_rect(struct panel_spec *self,
				uint16_t left, uint16_t top,
				uint16_t right, uint16_t bottom)
{
	LCD_PRINT("dummy_invalidate_rect \n");

}
static int32_t dummy_read_id(struct panel_spec *self)
{
	LCD_PRINT("lcd_dummy_spi read id!\n");
	return 0xFFFF;

}

static struct panel_operations lcd_dummy_spi_operations = {
	.panel_init = dummy_init,
	.panel_set_window = dummy_set_window,
	.panel_invalidate_rect= dummy_invalidate_rect,
	.panel_invalidate = dummy_invalidate,
	.panel_enter_sleep = dummy_enter_sleep,
	.panel_readid          = dummy_read_id,
	.panel_refresh		=dummy_refresh,
	//.panel_reset = dummy_reset,
};

static struct info_spi lcd_dummy_spi_info = {
	.bus_num = 0,
	.cs = 0,
	.spi_mode = 1,
	.spi_pol_mode = SPI_MODE_0,
	.speed = DUMMY_SPI_SPEED,
};

struct panel_spec lcd_dummy_spi_spec = {
	.width = 240,
	.height = 320,
	.fps = 33,
	.type = SPRDFB_PANEL_TYPE_SPI,
	.direction = LCD_DIRECT_NORMAL,
	.info = {
		.spi = &lcd_dummy_spi_info
	},
	.ops = &lcd_dummy_spi_operations,
};
