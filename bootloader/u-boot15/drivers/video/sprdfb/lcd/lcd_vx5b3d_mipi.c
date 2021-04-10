/* drivers/video/sprdfb/lcd_vx5b3d_mipi.c
 *
 * Support for 5b3d lvds LCD device
 *
 * Copyright (C) 2013 Spreadtrum
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
//#include <asm/arch/sprd_i2c.h>
#include <asm/arch/sci_types.h>
#include "sp8830_i2c.h"
//#include "sc8830_i2c_cfg.h"

#include "../sprdfb.h"

#define printk printf

#define  LCD_DEBUG
#ifdef LCD_DEBUG
#define LCD_PRINT printk
#else
#define LCD_PRINT(...)
#endif



struct bridge_ops {
	int32_t (*init)(struct panel_spec *self);
};

static struct bridge_ops b_ops = {
	.init = NULL,
};

#define ARRAY_SIZE(array) ( sizeof(array) / sizeof(array[0]))

#define I2CID_BRIDGE                3
#define I2C_BRIDGE_ADDR             0x64

#define GPIOID_BLIC_EN (214)
#define GPIOID_BRIDGE_EN  (233)  // We can't see this pin in the SCH provided by SS
#define GPIOID_BRIDGE_RST  (234)
#define GPIOID_LCD_3V3_EN  (152) // If this gpio not exist in HW, remove this defination

#define DELAY_CMD	(0xFFFF)  // This is a flag for delay

extern int sprd_gpio_direction_output(struct gpio_chip *chip, unsigned offset, int value);
extern int sprd_gpio_request(struct gpio_chip *chip, unsigned offset);

typedef struct I2C_Init_Code {
	uint16_t addr;
	uint32_t data;
};

static I2C_DEV i2c_dev_bridge = {
	.id = I2CID_BRIDGE,
	.freq = 400*1000,
	.bus = 2,
	.slave_addr = I2C_BRIDGE_ADDR*2,
	.reg_addr_num = 2,  // This is to decide the register byte number
	.check_ack = 1,
	.no_stop = 0,
};

struct I2C_Init_Code lvds_5b3d_init_data[] = {
	{0x700, 0x6C900040},
	{0x704, 0x0003040A},
	{0x70C, 0x00004604},
	{0x710, 0x054D000B},
	{0x714, 0x00000020},
	{0x718, 0x00000102},
	{0x71C, 0x00A8002F},
	{0x720, 0x00000000},

	{DELAY_CMD, 100},	/* For pll locking */
	{0x154, 0x00000000},
	{0x154, 0x80000000},
	{DELAY_CMD, 100},	/* For pll locking */

	{0x700, 0x6C900840},
	{0x70C, 0x00005E56},
	{0x718, 0x00000202},

	{0x154, 0x00000000},
	{0x154, 0x80000000},
	{DELAY_CMD, 100},	/* For pll locking */

	{0x37C, 0x00001063},
	{0x380, 0x82A86030},
	{0x384, 0x2861408B},
	{0x388, 0x00130285},
	{0x38C, 0x10630009},
	{0x394, 0x400B82A8},
	{0x600, 0x016CC78C},
	{0x604, 0x3FFFFFE0},
	{0x608, 0x00000D8C},
	{0x154, 0x00000000},
	{0x154, 0x80000000},
	{0x120, 0x00000005},
	{0x124, 0x1892C400},
	{0x128, 0x00102806},
	{0x12C, 0x00000062},
	{0x130, 0x00003C18},
	{0x134, 0x00000015},
	{0x138, 0x00FF8000},
	{0x13C, 0x00000000},

	/*PWM  100 % duty ration*/
	{0x114, 0x000c6302},

	/*backlight duty ratio control when device is first bring up.*/
	{0x160, 0x000007F8},
	{0x164, 0x000002A8},
	{0x138, 0x3fff0000},
	{0x15C, 0x00000005},

	{0x140, 0x00010000},
	/*Add for power consumtion*/
	{0x174, 0x00000000},
	/*end*/

	/*
	   slope = 2 / variance = 0x55550022
	   slope register [15,10]
	   */
	{0x404, 0x55550822},

	/*
	   To minimize the text effect
	   this value from 0xa to 0xf
	   */
	{0x418, 0x555502ff},

	/*
	   Disable brightnes issue Caused by IBC
	   read 4 bytes from address 0x410 to 0x413
	   0x15E50300 is read value for 0x410 register
	   0x5E50300= 0x15E50300 & 0xefffffff
	   */
	{0x410, 0x05E50300},
	/*...end*/
	{0x20C, 0x00000124},
	{0x21C, 0x00000000},
	{0x224, 0x00000007},
	{0x228, 0x00050001},
	{0x22C, 0x0000FF03},
	{0x230, 0x00000001},
	{0x234, 0xCA033E10},
	{0x238, 0x00000060},
	{0x23C, 0x82E86030},
	{0x244, 0x001E0285},
	{0x258, 0x00060062},
	/*vee strenght initialization*/
	{0x400, 0x00000000},
	{0x158, 0x00000000},
	{0x158, 0x00000001},

};



static int32_t vx5b3d_power()
{

#if 0
	if (!probe) {
		if (sprd_gpio_request(GPIOID_BRIDGE_EN, "BRIDGE_EN")) {
			printk("[%s] GPIO%d request failed!\n", "BRIDGE_EN", GPIOID_BRIDGE_EN);
			return 0;
		}
		else
			sprd_gpio_direction_output(NULL, GPIOID_BRIDGE_EN, 0);
#endif
#ifdef GPIOID_LCD_3V3_EN
		if (sprd_gpio_request(NULL,GPIOID_LCD_3V3_EN)){
			printk("sprdfb: LCD_3V3_EN GPIO%d request failed!\n", GPIOID_LCD_3V3_EN);
			return 0;
		}else{
			sprd_gpio_direction_output(NULL, GPIOID_LCD_3V3_EN, 1);
			sprd_gpio_set(NULL,GPIOID_LCD_3V3_EN, 1);
			mdelay(5);
		}
#endif
		if (sprd_gpio_request(NULL,GPIOID_BRIDGE_RST)){
			printk("sprdfb: BRIDGE_RST GPIO%d request failed!\n", GPIOID_BRIDGE_RST);
			return 0;
		}
		sprd_gpio_direction_output(NULL, GPIOID_BRIDGE_RST, 1);
		sprd_gpio_set(NULL,GPIOID_BRIDGE_RST, 1);
		mdelay(5);

		if (sprd_gpio_request(NULL,GPIOID_BLIC_EN)) {
			printk("sprdfb: BLIC_EN  GPIO%d request failed!\n", GPIOID_BLIC_EN);
			return 0;
		}
		sprd_gpio_direction_output(NULL, GPIOID_BLIC_EN, 1);
		sprd_gpio_set(NULL, GPIOID_BLIC_EN, 1);
		mdelay(5);

		if (sprd_gpio_request(NULL,GPIOID_BRIDGE_EN)){
			printk("sprdfb: BRIDGE_RST GPIO%d request failed!\n", GPIOID_BRIDGE_EN);
			return 0;
		}
		sprd_gpio_direction_output(NULL, GPIOID_BRIDGE_EN, 1);
		sprd_gpio_set(NULL,GPIOID_BRIDGE_EN, 1);
		mdelay(5);

		LCD_PRINT("zyun: 2\n");

#if 0
		lvds_1v8 = regulator_get(NULL,"vddsim1");
		if (IS_ERR(lvds_1v8)) {
			lvds_1v8 = NULL;
			pr_info("%s regulator 1v8 get failed!!\n", "vddsim1");
		} else {
			regulator_set_voltage(lvds_1v8, 1800000, 1800000);
			regulator_enable(lvds_1v8);
		}

		lvds_3v3 = regulator_get(NULL,"vddwifipa");
		if (IS_ERR(lvds_3v3)) {
			lvds_3v3 = NULL;
			pr_info("%s regulator 3v3 get failed!!\n", "vddwifipa");
		} else {
			regulator_set_voltage(lvds_3v3, 3300000, 3300000);
			regulator_enable(lvds_3v3);
		}
		probe = 1;
	}

#endif
	
}
#define CONTROL_BYTE_GEN       (0x09u)
#define GEN_QL_CSR_WRITE  {\
	CONTROL_BYTE_GEN, \
	0x29,  /* Data ID */\
	0x05,  /* Vendor Id 1 */\
	0x01,  /* Vendor Id 2 */\
	0x40,  /* Vendor Unique Command */\
	0x00,  /* Address LS */\
	0x00,  /* Address MS */\
	0x00,  /* data LS */\
	0x00, \
	0x00, \
	0x00,  /* data MS */\
}

int vx5b3d_i2c_write32_array(int32_t handle, struct I2C_Init_Code *b_data, int len)
{
	int i, ret;
	char buf[] = GEN_QL_CSR_WRITE;

	for (i = 0; i < len; i++) {
		if (b_data[i].addr == DELAY_CMD) {
			mdelay(b_data[i].data);
			continue;
		}
		memcpy(buf+5,(uint8 *)&(b_data[i].addr), 2);
		memcpy(buf+7,(uint8 *)&(b_data[i].data), 4);

		//ret = I2C_HAL_Write(handle,(uint8 *)&(b_data[i].addr), (uint8 *)&(b_data[i].data),4);
		ret = I2C_HAL_Write(handle, buf, buf+2,9);
//		LCD_PRINT("I2C Write, buf5-11 is: %x %x %x %x %x %x\n",  buf[5], buf[6],buf[7],buf[8],buf[9],buf[10]);
	}

	return ret;
}

#if 0
int Quicklogic_i2c_write32(u16 reg, u32 val)
{
	int status = 0;
	/*int write_size;*/
	char buf[] = GEN_QL_CSR_WRITE;

	if (g_client == NULL)	/* No global client pointer? */
		return -EIO;

	mutex_lock(&lock);

	buf[5] = (uint8_t)reg;  /* Address LS */
	buf[6] = (uint8_t)(reg >> 8);	/* Address MS */

	buf[7] = val & 0xff;
	buf[8] = (val >> 8) & 0xff;
	buf[9] = (val >> 16) & 0xff;
	buf[10] =(val >> 24) & 0xff;
	status = i2c_master_send(g_client, (char *)(&buf[0]), 11);

	if (status >= 0)
		status = 0;
	else {
		pr_info("%s, [0x%04x] -EIO\n", __func__, reg);
		status = -EIO;
	}

	udelay(10);
	mutex_unlock(&lock);

	return status;

}
#endif

static int32_t lvds_5b3d_init(struct panel_spec *self)
{
	int32_t handle = 0;
	int32_t len=ARRAY_SIZE(lvds_5b3d_init_data);

	/* open i2c */
	handle = I2C_HAL_Open(&i2c_dev_bridge);
	if(handle==-1)
		LCD_PRINT("sprdfb: hal open failed!%d\n",handle);

	vx5b3d_i2c_write32_array(handle,lvds_5b3d_init_data,len);

	I2C_HAL_Close(handle);

	return 0;
}


static int32_t lcd_5b3d_mipi_lvds_init(struct panel_spec *self)
{
	LCD_PRINT("zyun: 1\n");

	vx5b3d_power();  // TO pull up some GPIO
	lvds_5b3d_init(self);
}

static uint32_t vx5b3d_readid(struct panel_spec *self)
{
	int32_t j =0;
	uint8_t read_data[3] = {0};
	int32_t read_rtn = 0;
	uint8_t param[2] = {0};
	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_force_write_t mipi_force_write = self->info.mipi->ops->mipi_force_write;
	mipi_force_read_t mipi_force_read = self->info.mipi->ops->mipi_force_read;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	mipi_set_cmd_mode();
	mipi_eotp_set(0,0);

	for(j = 0; j < 4; j++){
		param[0] = 0x01;
		param[1] = 0x00;
		mipi_force_write(0x37, param, 2);
		read_rtn = mipi_force_read(0xda,1,&read_data[0]);

		read_rtn = mipi_force_read(0xdb,1,&read_data[1]);

		read_rtn = mipi_force_read(0xdc,1,&read_data[2]);


		//	if((0x55 == read_data[0])&&(0xbc == read_data[1])&&(0x90 == read_data[2])){
		LCD_PRINT("vx5b3d_readid readID, 0xda,0xdb,0xdc is 0x%x,0x%x,0x%x!\n",read_data[0],read_data[1],read_data[2]);
		printk("lcd_vx5b3d_mipi read id success!\n");
		return 0x8282;
		//		}
	}
	LCD_PRINT("vx5b3d_readid read id fail! 0xda,0xdb,0xdc is 0x%x,0x%x,0x%x!\n",read_data[0],read_data[1],read_data[2]);
	mipi_eotp_set(0,0);

	return 0;
}


static struct panel_operations lcd_vx5b3d_mipi_operations = {
	.panel_init = lcd_5b3d_mipi_lvds_init,
	.panel_readid = vx5b3d_readid,
};

static struct timing_rgb lcd_vx5b3d_mipi_timing = {
	.hfp = 123,
	.hbp = 100,
	.hsync = 120,
	.vfp = 13,
	.vbp = 10,
	.vsync = 10,
};

static struct info_mipi lcd_vx5b3d_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 24, /*18,16*/
	.lan_number = 4,
	.phy_feq = 480*1000,
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_vx5b3d_mipi_timing,
	.ops = NULL,
};
struct panel_spec lcd_vx5b3d_mipi_spec = {
	.width = 1024,
	.height = 600,
	.fps = 60,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.info = {
		.mipi = &lcd_vx5b3d_mipi_info
	},
	.ops = &lcd_vx5b3d_mipi_operations,
};




