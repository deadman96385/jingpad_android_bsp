/* drivers/video/sprdfb/lcd/lcd_st7789v2_spi.c
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
#define ST7789_SpiWriteCmd(cmd) \
{ \
	spi_send_cmd((cmd & 0xFF));\
}

#define  ST7789_SpiWriteData(data)\
{ \
	spi_send_data((data & 0xFF));\
}

#define  ST7789_SpiRead(data,len)\
{ \
	spi_read(data,len);\
}
#define BGRA32toRBG565(b,g,r)		((((r>>3)&0x1f)<<11)|(((g>>2)&0x3f)<<5)|(((b>>3)&0x1f)<<0))
#define LCM_GPIO_RSTN			(50)
#define ST7789_SPI_SPEED 		(48*1000*1000UL)
#define	SPI_MODE_0	(0|0)

static int32_t st7789_refresh(struct panel_spec *self,void *base)
{
	int i = 0;
	uint16_t *prgb = (uint16_t *)base;
	uint16_t rgb;
	LCD_PRINT("st7789_freshbuffer\r\n");
	spi_send_cmd_t spi_send_cmd = self->info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data = self->info.spi->ops->spi_send_data;
	spi_read_t spi_read = self->info.spi->ops->spi_read;

	for(i = 0 ; i < 240*320;i++)
	{
		rgb = *prgb++;
		ST7789_SpiWriteData(rgb>>8);
		ST7789_SpiWriteData(rgb&0xff);
	}
	ST7789_SpiWriteCmd(0x29);
	return 0;
}
static int32_t st7789_reset(void)
{
	static int32_t is_first_run = 1;
	if(is_first_run)
	{
		sprd_gpio_request(NULL,LCM_GPIO_RSTN);
		sprd_gpio_direction_output(NULL,LCM_GPIO_RSTN,1);
		is_first_run = 0;
	}
	sprd_gpio_set(NULL,LCM_GPIO_RSTN,1);
	mdelay(10);
	sprd_gpio_set(NULL,LCM_GPIO_RSTN,0);
	mdelay(10);
	sprd_gpio_set(NULL,LCM_GPIO_RSTN,1);
	mdelay(20);
}

static int32_t st7789_init(struct panel_spec *self)
{
	uint32_t data = 0;
	spi_send_cmd_t spi_send_cmd = self->info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data = self->info.spi->ops->spi_send_data;
	spi_read_t spi_read = self->info.spi->ops->spi_read;

	st7789_reset();

	ST7789_SpiWriteCmd(0x11);
	mdelay(120);

	ST7789_SpiWriteCmd(0x36);
	ST7789_SpiWriteData(0x00);

	ST7789_SpiWriteCmd(0x35);
	ST7789_SpiWriteData(0x00);

	ST7789_SpiWriteCmd(0x3a);
	ST7789_SpiWriteData(0x05);

	ST7789_SpiWriteCmd(0xb2);
	ST7789_SpiWriteData(0x0c);
	ST7789_SpiWriteData(0x0c);
	ST7789_SpiWriteData(0x00);
	ST7789_SpiWriteData(0x33);
	ST7789_SpiWriteData(0x33);

	ST7789_SpiWriteCmd(0xb7);
	ST7789_SpiWriteData(0x35);

	ST7789_SpiWriteCmd(0xbb);
	ST7789_SpiWriteData(0x35);

	ST7789_SpiWriteCmd(0xc0);
	ST7789_SpiWriteData(0x2c);

	ST7789_SpiWriteCmd(0xc2);
	ST7789_SpiWriteData(0x01);

	ST7789_SpiWriteCmd(0xc3);
	ST7789_SpiWriteData(0x11);

	ST7789_SpiWriteCmd(0xc4);
	ST7789_SpiWriteData(0x20);

	ST7789_SpiWriteCmd(0xc6);
	ST7789_SpiWriteData(0x0f);

	ST7789_SpiWriteCmd(0xd0);
	ST7789_SpiWriteData(0xa4);
	ST7789_SpiWriteData(0xa1);

	ST7789_SpiWriteCmd(0xe0);
	ST7789_SpiWriteData(0xd0);
	ST7789_SpiWriteData(0x00);
	ST7789_SpiWriteData(0x05);
	ST7789_SpiWriteData(0x0e);
	ST7789_SpiWriteData(0x15);
	ST7789_SpiWriteData(0x0d);
	ST7789_SpiWriteData(0x37);
	ST7789_SpiWriteData(0x43);
	ST7789_SpiWriteData(0x47);
	ST7789_SpiWriteData(0x09);
	ST7789_SpiWriteData(0x15);
	ST7789_SpiWriteData(0x12);
	ST7789_SpiWriteData(0x16);
	ST7789_SpiWriteData(0x19);

	ST7789_SpiWriteCmd(0xe1);
	ST7789_SpiWriteData(0xd0);
	ST7789_SpiWriteData(0x00);
	ST7789_SpiWriteData(0x05);
	ST7789_SpiWriteData(0x0d);
	ST7789_SpiWriteData(0x0c);
	ST7789_SpiWriteData(0x06);
	ST7789_SpiWriteData(0x2d);
	ST7789_SpiWriteData(0x44);
	ST7789_SpiWriteData(0x40);
	ST7789_SpiWriteData(0x0e);
	ST7789_SpiWriteData(0x1c);
	ST7789_SpiWriteData(0x18);
	ST7789_SpiWriteData(0x16);
	ST7789_SpiWriteData(0x19);

	ST7789_SpiWriteCmd(0x29);

	//ST7789_SpiWriteCmd(0x11);
	//mdelay(120);
//	ST7789_SpiWriteCmd(0x29);
//	ST7789_SpiWriteCmd(0x2c);

//	ST7789_SpiWriteCmd(0x29);
//	ST7789_SpiWriteCmd(0x2c);

	LCD_PRINT("st7789_init\n");
}

static int32_t st7789_enter_sleep(struct panel_spec *self, uint8_t is_sleep)
{
	spi_send_cmd_t spi_send_cmd = self->info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data = self->info.spi->ops->spi_send_data;
	spi_read_t spi_read = self->info.spi->ops->spi_read;

	if(is_sleep==1){
		//Sleep In
		ST7789_SpiWriteCmd(0x28);
		mdelay(120);
		ST7789_SpiWriteCmd(0x10);
		mdelay(10);
	}else{
		//Sleep Out
		ST7789_SpiWriteCmd(0x11);
		mdelay(120);
		ST7789_SpiWriteCmd(0x29);
		mdelay(10);
	}
	return 0;
}



static int32_t st7789_set_window(struct panel_spec *self,
		uint16_t left, uint16_t top, uint16_t right, uint16_t bottom)
{
	uint32_t *test_data[4] = {0};
	spi_send_cmd_t spi_send_cmd = self->info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data = self->info.spi->ops->spi_send_data;
	spi_read_t spi_read = self->info.spi->ops->spi_read;


	ST7789_SpiWriteCmd(0x2A);
	ST7789_SpiWriteData((left>>8));// set left address
	ST7789_SpiWriteData((left&0xff));
	ST7789_SpiWriteData((right>>8));// set right address
	ST7789_SpiWriteData((right&0xff));

	ST7789_SpiWriteCmd(0x2B);
	ST7789_SpiWriteData((top>>8));// set left address
	ST7789_SpiWriteData((top&0xff));
	ST7789_SpiWriteData((bottom>>8));// set bottom address
	ST7789_SpiWriteData((bottom&0xff));
	ST7789_SpiWriteCmd(0x2C);

	return 0;
}
static int32_t st7789_invalidate(struct panel_spec *self)
{
	LCD_PRINT("st7789_invalidate\n");

	return self->ops->panel_set_window(self, 0, 0,
		self->width - 1, self->height - 1);
}



static int32_t st7789_invalidate_rect(struct panel_spec *self,
				uint16_t left, uint16_t top,
				uint16_t right, uint16_t bottom)
{
	LCD_PRINT("st7789_invalidate_rect \n");

	return self->ops->panel_set_window(self, left, top,
			right, bottom);
}
static int32_t st7789_read_id(struct panel_spec *self)
{
	spi_send_cmd_t spi_send_cmd = self->info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data = self->info.spi->ops->spi_send_data;
	spi_read_t spi_read = self->info.spi->ops->spi_read;
	spi_clock_set_t spi_clock_set = self->info.spi->ops->spi_clock_set;
	uint32_t i=0;
	uint32_t lcm_id[4]={0};

	spi_clock_set(6000000);
	st7789_reset();
	for(i=0;i<4;i++){
		//ST7789_SpiWriteCmd(0xFE);
		//ST7789_SpiWriteCmd(0xEF);
		ST7789_SpiWriteCmd(0x04);
		ST7789_SpiRead(lcm_id,4);
		LCD_PRINT("sprdfb:st7789_read_id lcm id[0-3] = 0x%x %x %x %x\n",lcm_id[0],lcm_id[1],lcm_id[2],lcm_id[3]);
		if(lcm_id[1] == 0x85 && lcm_id[2] == 0x52)
		{
			spi_clock_set(24000000);
			return 0x7789;
		}
	}
	return 0x00;

}

static struct panel_operations lcd_st7789_spi_operations = {
	.panel_init = st7789_init,
	.panel_set_window = st7789_set_window,
	.panel_invalidate_rect= st7789_invalidate_rect,
	.panel_invalidate = st7789_invalidate,
	.panel_enter_sleep = st7789_enter_sleep,
	.panel_readid          = st7789_read_id,
	.panel_refresh		=st7789_refresh,
	//.panel_reset = st7789_reset,
};

static struct info_spi lcd_st7789_spi_info = {
	.bus_num = 0,
	.cs = 0,
	.cd_gpio = 138,
	.spi_mode = 1,
	.spi_pol_mode = SPI_MODE_0,
	.speed = ST7789_SPI_SPEED,
};

struct panel_spec lcd_st7789v2_spi_spec = {
	.width = 240,
	.height = 320,
	.fps = 33,
	.type = SPRDFB_PANEL_TYPE_SPI,
	.direction = LCD_DIRECT_NORMAL,
	.info = {
		.spi = &lcd_st7789_spi_info
	},
	.ops = &lcd_st7789_spi_operations,
};
