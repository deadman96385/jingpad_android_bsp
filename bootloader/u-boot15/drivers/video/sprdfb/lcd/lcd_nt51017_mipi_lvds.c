/* drivers/video/sprdfb/lcd_nt51017_mipi_lvds.c
 *
 * Support for nt51017 lvds LCD device
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

//#define  LCD_DEBUG
#ifdef LCD_DEBUG
#define LCD_PRINT printk
#else
#define LCD_PRINT(...)
#endif

/***************** Important Macro! *****************/
/* For TI! ONLY ONE of the flowing marco can be defined! */
//#define LINES_ALL_RIGHT_TI
#define LINES_ONLY_CLK_RIGHT_TI

/* For CHIPONE! ONLY ONE of the flowing marco can be defined! */
//#ifdef CONFIG_SHARK_PAD_HW_V102  // 5735A-2 v1.0.2 & 5735C-1 v1.0.0
#if 1
#define LINES_ALL_WRONG_C1
#else  // 5735A-2 v1.0.1
#define LINES_ALL_RIGHT_C1
#endif
/***************** Important Macro! *****************/

struct bridge_ops {
	int32_t (*init)(struct panel_spec *self);
};

static struct bridge_ops b_ops = {
	.init = NULL,
};

#define ARRAY_SIZE(array) ( sizeof(array) / sizeof(array[0]))

#define I2CID_BRIDGE                2
#define I2C_NT50366_ADDR_WRITE      0x9E /* NT50366C 100_1111 0 */
#define I2C_NT51017_ADDR_WRITE      0xD0 /* NT51017 110_1000 0 */
#define I2C_BRIDGE_ADDR_WRITE0      0x58 /* 0101_100 0 ADDR=Low */
#define I2C_BRIDGE_ADDR_WRITE1      0x5A /* 0101_101 0 ADDR=High */
#define I2C_BRIDGE_ADDR             I2C_BRIDGE_ADDR_WRITE0

#define GPIOID_BRIDGE_EN  231
#define GPIOID_VDDPWR     232
#define GPIOID_ADDR       234 /* should modify pinmap */
#define GPIOID_LCDPWR     235

extern int sprd_gpio_direction_output(struct gpio_chip *chip, unsigned offset, int value);
extern int sprd_gpio_request(struct gpio_chip *chip, unsigned offset);

typedef struct I2C_Init_Code_tag {
	uint8_t addr;
	uint8_t val;
}I2C_Init_Code;

static I2C_DEV i2c_dev_bridge = {
	.id = I2CID_BRIDGE,
	.freq = 100*1000,
	.bus = 2,
	.slave_addr = I2C_BRIDGE_ADDR,
	.reg_addr_num = 1,
	.check_ack = 1,
	.no_stop = 0,
};

const static I2C_Init_Code lvds_init_data_ti[] = {
        {0x09, 0x00},
		{0x0A, 0x03},
		{0x0B, 0x18},
		{0x0D, 0x00},
		{0x10, 0x26},
		{0x11, 0x00},
		{0x12, 0x31},
		{0x13, 0x00},
#ifdef LINES_ALL_RIGHT_TI
		{0x18, 0x18},/* all the line is right */
#elif defined LINES_ONLY_CLK_RIGHT_TI
        {0x18, 0xF8},/* only clock line is right */
#endif
		{0x19, 0x0C},/* 0x00 */
		{0x1A, 0x03},
		{0x1B, 0x00},
		{0x20, 0x00},
		{0x21, 0x03},
		{0x22, 0x00},
		{0x23, 0x00},
		{0x24, 0x00},
		{0x25, 0x00},
		{0x26, 0x00},
		{0x27, 0x00},
		{0x28, 0x20},
		{0x29, 0x00},
		{0x2A, 0x00},
		{0x2B, 0x00},
		{0x2C, 0x04},/*0x04*/
		{0x2D, 0x00},
		{0x2E, 0x00},
		{0x2F, 0x00},
		{0x30, 0x04},/*0x04*/
		{0x31, 0x00},
		{0x32, 0x00},
		{0x33, 0x00},
		{0x34, 0x4C},
		{0x35, 0x00},
		{0x36, 0x00},
		{0x37, 0x00},
		{0x38, 0x00},
		{0x39, 0x00},
		{0x3A, 0x00},
		{0x3B, 0x00},
		{0x3C, 0x00},
		{0x3D, 0x00},
		{0x3E, 0x00},
};
const static I2C_Init_Code lvds_init_data_c1[] = {
        /*{0x10, 0x4E},add*/
        {0x20, 0x00},
		{0x21, 0x00},
		{0x22, 0x43},
		{0x23, 0x28},
		{0x24, 0x04},
		{0x25, 0x4C},
		{0x26, 0x00},
		{0x27, 0x12},
        {0x28, 0x04},/*0x02*/
		{0x29, 0x13},
		{0x2A, 0x01},
		{0x34, 0xF0},/*add*/
		{0x36, 0x50},/*add*/
		{0x86, 0x2B},
		{0xB5, 0xA0},
		{0x51, 0x20},
		{0x56, 0x92},
		{0x69, 0x1C},/*0x1F*/
		{0x6B, 0x22},
		{0x5C, 0xFF},
		{0xB6, 0x20},
#ifdef LINES_ALL_RIGHT_C1
        {0x13, 0x10},
#elif defined LINES_ONLY_CLK_RIGHT_C1
        {0x13, 0x1F},
#elif defined LINES_ALL_WRONG_C1
		{0x13, 0x5F},
#endif
		/*{0x10, 0x47},add*/
		/*{0x2A, 0x31},modify*/
		/*{0x2E, 0x40},add*/
		/*{0x2F, 0x40},add*/
		{0x09, 0x10},
		/*{0x7B, 0xF2},*/
        /*{0x7C, 0xF3},*/
};

/* Init SN65DSI83 */
static int32_t sn65dsi83_init(struct panel_spec *self)
{
	int32_t i = 0;
	int32 handle = 0;
	uint32 err_code = 0;
	
    uint8 ti_pll_en = lvds_init_data_ti[3].val | 0x01;               /* (CSR 0x0D.0) */
    uint8 ti_soft_reset = lvds_init_data_ti[0].val | 0x01;           /* (CSR 0x09.0) */

	mipi_set_lp_mode_t mipi_set_lp_mode = self->info.mipi->ops->mipi_set_lp_mode;/* u-boot\arch\arm\include\asm\arch\sprd_lcd.h */
	mipi_set_hs_mode_t mipi_set_hs_mode = self->info.mipi->ops->mipi_set_hs_mode;
	mipi_set_video_mode_t mipi_set_video_mode = self->info.mipi->ops->mipi_set_video_mode;

	LCD_PRINT("sn65dsi83_init\n");
	
    /* step 1 : All DSI into LP11*/
	mipi_set_lp_mode();

	/* step 2 : Set EN*/
	sprd_gpio_request(NULL, GPIOID_BRIDGE_EN);
	sprd_gpio_direction_output(NULL, GPIOID_BRIDGE_EN, 0);
	mdelay(30);
	sprd_gpio_direction_output(NULL, GPIOID_BRIDGE_EN, 1);

	/* step 3 : Delay*/
	mdelay(10);

    /* open i2c */
    handle = I2C_HAL_Open(&i2c_dev_bridge);
	
	/* step 4 : init CSR reg*/
	for(i=0; i<ARRAY_SIZE(lvds_init_data_ti); i++){
		err_code = I2C_HAL_Write(handle, &lvds_init_data_ti[i].addr, &lvds_init_data_ti[i].val, 1);
		LCD_PRINT("I2C Write Reg=0x%x, Val=0x%x, WriteBytes=%d\n",lvds_init_data_ti[i].addr, lvds_init_data_ti[i].val,err_code);
	}

	/* step 5 : Start the DSI video stream */
	mipi_set_hs_mode();
	mipi_set_video_mode();
	mdelay(5);

	/* step 6 : Set the PLL_EN bit(CSR 0x0D.0) */
	err_code = I2C_HAL_Write(handle, &lvds_init_data_ti[3].addr, &ti_pll_en, 1);
	LCD_PRINT("I2C Write Reg=0x%x, Val=0x%x, WriteBytes=%d\n",lvds_init_data_ti[3].addr, ti_pll_en,err_code);

	/* step 7 : Wait for the PLL_LOCK bit to be set(CSR 0x0A.7) */
	mdelay(5);
    
	/* step 8 : Set the SOFT_RESET bit (CSR 0x09.0) */
	err_code = I2C_HAL_Write(handle, &lvds_init_data_ti[0].addr, &ti_soft_reset, 1);
	LCD_PRINT("I2C Write Reg=0x%x, Val=0x%x, WriteBytes=%d\n",lvds_init_data_ti[0].addr, ti_soft_reset, err_code);

    /* close i2c */
	I2C_HAL_Close(handle);

    return 0;
}

static int32_t chipone_init(struct panel_spec *self)
{
    int32_t i = 0;
	int32 handle = 0;
	uint32 err_code = 0;

    sprd_gpio_request(NULL, GPIOID_BRIDGE_EN);
	sprd_gpio_direction_output(NULL, GPIOID_BRIDGE_EN, 1);
    mdelay(10);

    /* open i2c */
    handle = I2C_HAL_Open(&i2c_dev_bridge);
	
	/* init CSR reg*/
	for(i=0; i<ARRAY_SIZE(lvds_init_data_c1); i++){
		err_code = I2C_HAL_Write(handle, &lvds_init_data_c1[i].addr, &lvds_init_data_c1[i].val, 1);
		LCD_PRINT("I2C Write Reg=0x%x, Val=0x%x, WriteBytes=%d\n",lvds_init_data_c1[i].addr, lvds_init_data_c1[i].val,err_code);
	}

    /* close i2c */
	I2C_HAL_Close(handle);

    return 0;
}

static int32_t get_bridge_info(struct panel_spec *self)
{
	uint8_t reg = 0x00;
	uint8_t flag = 0xFF;
	int32 handle = 0;
	uint32 err_code = 0;

	sprd_gpio_request(NULL, GPIOID_BRIDGE_EN);
	sprd_gpio_direction_output(NULL, GPIOID_BRIDGE_EN, 0);
	mdelay(30);
	sprd_gpio_direction_output(NULL, GPIOID_BRIDGE_EN, 1);
	mdelay(5);

	sprd_gpio_request(NULL, GPIOID_ADDR);
	sprd_gpio_direction_output(NULL, GPIOID_ADDR, 0);//drive ADDR to low
	mdelay(5);

	/* open i2c */
    handle = I2C_HAL_Open(&i2c_dev_bridge);

	err_code = I2C_HAL_Read(handle, &reg, &flag, 1);
	if (0 == err_code) {
		printf("I2C Read Error! err_code=%d\n", err_code);
		return 1;
	}

	if (0x35 == flag){//TI
		b_ops.init = sn65dsi83_init;
		printf("sprdfb: MIPI to LVDS bridge is TI SN65DSI83!\n");
	} else if (0xC1 == flag) {//ChipOne
		b_ops.init = chipone_init;
		printf("sprdfb: MIPI to LVDS bridge is ChpOne!\n");
	} else {
		printf("sprdfb: Unknown bridge! flag=0x%x\n",flag);
		I2C_HAL_Close(handle);
		return 1;
	}

	/* close i2c */
	I2C_HAL_Close(handle);

	return 0;
}

static int32_t nt51017_mipi_lvds_init(struct panel_spec *self)
{	
	LCD_PRINT("lcd_nt51017_mipi_lvds_init\n");

	if (b_ops.init) {
		b_ops.init(self);
    }

	sprd_gpio_request(NULL, GPIOID_VDDPWR);
	sprd_gpio_direction_output(NULL, GPIOID_VDDPWR, 1);
	mdelay(5);

	sprd_gpio_request(NULL, GPIOID_LCDPWR);
	sprd_gpio_direction_output(NULL, GPIOID_LCDPWR, 1);
	mdelay(5);

	return 0;
}

static uint32_t nt51017_mipi_lvds_readid(struct panel_spec *self)
{
	LCD_PRINT("nt51017_mipi_lvds_readid\n");

	if(get_bridge_info(self)){
		printk("u-boot get bridge info fail!\n");
		return 0x00;
	}

    return 0xC749;/*51017*/
}

static struct panel_operations lcd_nt51017_mipi_lvds_operations = {
	.panel_init = nt51017_mipi_lvds_init,
	.panel_readid = nt51017_mipi_lvds_readid,
};

static struct timing_rgb lcd_nt51017_mipi_lvds_timing = {
	.hfp = 110,  /* unit: pixel */
	.hbp = 76,
	.hsync = 4,//4
	.vfp = 18, /*unit: line*/
	.vbp = 19,
	.vsync = 4,
};

static struct info_mipi lcd_nt51017_mipi_lvds_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 24, /*18,16*/
	.lan_number = 4,
	.phy_feq = 512*1000,/*494*/
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_nt51017_mipi_lvds_timing,
	.ops = NULL,
};

struct panel_spec lcd_nt51017_mipi_lvds_spec = {
	//.cap = PANEL_CAP_NOT_TEAR_SYNC,
	.width = 768,
	.height = 1024,
	.fps = 60,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.info = {
		.mipi = &lcd_nt51017_mipi_lvds_info
	},
	.ops = &lcd_nt51017_mipi_lvds_operations,
};




