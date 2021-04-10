/* drivers/video/sc8810/sc8810_lcd.h
 *
 * Spreadtrum LCD abstraction
 *
 * Copyright (C) 2010 Spreadtrum.com
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

#ifndef _SPRDFB_PANEL_H_
#define _SPRDFB_PANEL_H_

#include <linux/types.h>
#include <common.h>

#define LCD_DelayMS(ms)  udelay(1000*(ms))

/* LCD mode */
#define SPRDFB_I2C_WRITE_DELAY 0xffff


/* LCD mode */
#define LCD_MODE_MCU			0
#define LCD_MODE_RGB			1
#define LCD_MODE_DSI			2
#define LCD_MODE_LVDS			3

/* bus mode */
#define LCD_BUS_8080			0
#define LCD_BUS_6800			1
#define LCD_BUS_SPI			2

/* lcd directions */
#define LCD_DIRECT_NORMAL		0
#define LCD_DIRECT_ROT_90		1
#define LCD_DIRECT_ROT_180		2
#define LCD_DIRECT_ROT_270		3
#define LCD_DIRECT_MIR_H		4
#define LCD_DIRECT_MIR_V		5
#define LCD_DIRECT_MIR_HV		6

#define PIN_PWM0_MOD_VALUE 0x20

#define SPRD_PWM_BASE 			0x88000000
#define SPRD_PWM_REG(off) 		(SPRD_PWM_BASE + (off))
#define SPRD_PWM0_PRESCALE   	SPRD_PWM_REG(0x0000)
#define SPRD_PWM0_CNT 			SPRD_PWM_REG(0x0004)
#define SPRD_PWM0_TONE_DIV 	SPRD_PWM_REG(0x0008)
#define SPRD_PWM0_PAT_LOW 	SPRD_PWM_REG(0x000C)
#define SPRD_PWM0_PAT_HIG 	SPRD_PWM_REG(0x0010)

#define LCD_PWM_PRESCALE_VALUE 	0x01
#define LCD_PWM_MOD_VALUE 		0xFF
#define PWM_REG_MSK_VALUE			0xFFFF

#define LCD_PWM0_EN BIT_8


/* panel property */
/* lcdc refresh, TE on, double timing, partial update*/
#define PANEL_CAP_NORMAL               0x0

/* only not support partial update*/
#define PANEL_CAP_NOT_PARTIAL_UPDATE   0x1

/* write register, grame have the same timing */
#define PANEL_CAP_UNIQUE_TIMING        0x2

/* lcd not support TE */
#define PANEL_CAP_NOT_TEAR_SYNC        0x4

/* only do command/data register, such as some mono oled display device */
#define PANEL_CAP_MANUAL_REFRESH       0x8

enum{
	SPRDFB_PANEL_TYPE_MCU = 0,
	SPRDFB_PANEL_TYPE_RGB,
	SPRDFB_PANEL_TYPE_MIPI,
	SPRDFB_PANEL_TYPE_LVDS,
	SPRDFB_PANEL_TYPE_SPI,
	SPRDFB_PANEL_TYPE_LIMIT
};

enum{
	SPRDFB_POLARITY_POS = 0,
	SPRDFB_POLARITY_NEG,
	SPRDFB_POLARITY_LIMIT
};

enum{
	SPRDFB_RGB_BUS_TYPE_I2C = 0,
	SPRDFB_RGB_BUS_TYPE_SPI,
	SPRDFB_RGB_BUS_TYPE_LVDS,
	SPRDFB_RGB_BUG_TYPE_LIMIT
};

enum{
	SPRDFB_MIPI_MODE_CMD = 0,
	SPRDFB_MIPI_MODE_VIDEO,
	SPRDFB_MIPI_MODE_LIMIT
};

struct panel_spec;

typedef int32_t (*send_cmd_t)(uint32_t data);
typedef int32_t (*send_data_t)(uint32_t data);
typedef int32_t (*send_cmd_data_t)(uint32_t cmd, uint32_t data);
typedef uint32_t (*read_data_t)(void);


typedef int32_t (*mipi_set_cmd_mode_t)(void);
typedef int32_t (*mipi_set_video_mode_t)(void);
typedef int32_t (*mipi_set_lp_mode_t)(void);//LiWei
typedef int32_t (*mipi_set_hs_mode_t)(void);//LiWei
typedef int32_t (*mipi_gen_write_t)(uint8_t *param, uint16_t param_length);
typedef int32_t (*mipi_gen_read_t)(uint8_t *param, uint16_t param_length, uint8_t bytes_to_read, uint8_t *read_buffer);
typedef int32_t (*mipi_dcs_write_t)(uint8_t *param, uint16_t param_length);
typedef int32_t (*mipi_dcs_read_t)(uint8_t command, uint8_t bytes_to_read, uint8_t *read_buffer);
typedef	int32_t (*mipi_force_write_t)(uint8_t data_type, uint8_t *param, uint16_t param_length);	//add for LCD adapter
typedef	int32_t (*mipi_force_read_t)(uint8_t command, uint8_t bytes_to_read, uint8_t *read_buffer);
typedef   int32_t (*mipi_eotp_set_t)(uint8_t rx_en, uint8_t tx_en);

typedef int32_t (*i2c_write_8bits_t)(uint8_t addr, uint8_t reg, uint8_t val);
typedef int32_t (*i2c_read_8bits_t)(uint8_t addr, uint8_t reg, uint8_t *val);
typedef int32_t (*i2c_write_16bits_t)(uint8_t addr, uint16_t reg, BOOLEAN reg_is_8bit, uint16_t val, BOOLEAN val_is_8bit);
typedef int32_t (*i2c_read_16bits_t)(uint8_t addr, uint16_t reg, BOOLEAN reg_is_8bit, uint16_t *val, BOOLEAN val_is_8bit);
typedef int32_t (*i2c_write_burst_t)(uint8_t addr, uint8_t* buf, int num);

typedef void (*spi_send_cmd_t)(uint32_t cmd);
typedef void (*spi_send_data_t)(uint32_t data);
typedef void (*spi_read_t)(uint32_t *data, uint32_t len);
typedef void (*spi_clock_set_t)(unsigned int);

/* LCD operations */
struct panel_operations {
	int32_t (*panel_init)(struct panel_spec *self);
	int32_t (*panel_close)(struct panel_spec *self);
	int32_t (*panel_reset)(struct panel_spec *self);
	int32_t (*panel_refresh)(struct panel_spec *self,void *base);
	int32_t (*panel_enter_sleep)(struct panel_spec *self, uint8_t is_sleep);
	int32_t (*panel_set_contrast)(struct panel_spec *self, uint16_t contrast);
	int32_t (*panel_set_brightness)(struct panel_spec *self,
				uint16_t brightness);
	int32_t (*panel_set_window)(struct panel_spec *self,
				uint16_t left, uint16_t top,
				uint16_t right, uint16_t bottom);
	int32_t (*panel_invalidate)(struct panel_spec *self);
	int32_t (*panel_invalidate_rect)(struct panel_spec *self,
				uint16_t left, uint16_t top,
				uint16_t right, uint16_t bottom);
	int32_t (*panel_rotate_invalidate_rect)(struct panel_spec *self,
				uint16_t left, uint16_t top,
				uint16_t right, uint16_t bottom,
				uint16_t angle);
	int32_t (*panel_set_direction)(struct panel_spec *self, uint16_t direction);
	uint32_t (*panel_readid)(struct panel_spec *self);
};

/* MCU LCD specific properties */
struct timing_mcu {
	uint16_t rcss;
	uint16_t rlpw;
	uint16_t rhpw;
	uint16_t wcss;
	uint16_t wlpw;
	uint16_t whpw;
};

/* RGB LCD specific properties */
struct timing_rgb {
	uint16_t hfp;
	uint16_t hbp;
	uint16_t hsync;
	uint16_t vfp;
	uint16_t vbp;
	uint16_t vsync;
};

struct ops_mcu {
	int32_t (*send_cmd)(uint32_t cmd);
	int32_t (*send_cmd_data)(uint32_t cmd, uint32_t data);
	int32_t (*send_data)(uint32_t data);
	uint32_t (*read_data)(void);
};

struct ops_i2c {
	int32_t (*i2c_write_8bits)(uint8_t addr, uint8_t reg, uint8_t val);
	int32_t (*i2c_read_8bits)(uint8_t addr, uint8_t reg, uint8_t *val);
	int32_t (*i2c_write_16bits)(uint8_t addr, uint16_t reg, BOOLEAN reg_is_8bit, uint16_t val, BOOLEAN val_is_8bit);
	int32_t (*i2c_read_16bits)(uint8_t addr, uint16_t reg, BOOLEAN reg_is_8bit, uint16_t *val, BOOLEAN val_is_8bit);
	int32_t (*i2c_write_burst)(uint8_t addr, uint8_t* buf, int num);
};

struct ops_spi{
	void (*spi_send_cmd)(uint32_t cmd);
	void (*spi_send_data)(uint32_t data);
	void (*spi_read)(uint32_t *data,uint32_t len);
	void (*spi_clock_set)(unsigned int);
};

struct ops_mipi{
	int32_t (*mipi_set_cmd_mode)(void);
	int32_t (*mipi_set_video_mode)(void);
	int32_t (*mipi_set_lp_mode)(void);
	int32_t (*mipi_set_hs_mode)(void);
	int32_t (*mipi_gen_write)(uint8_t *param, uint16_t param_length);
	int32_t (*mipi_gen_read)(uint8_t *param, uint16_t param_length, uint8_t bytes_to_read, uint8_t *read_buffer);
	int32_t (*mipi_dcs_write)(uint8_t *param, uint16_t param_length);
	int32_t (*mipi_dcs_read)(uint8_t command, uint8_t bytes_to_read, uint8_t *read_buffer);
	int32_t (*mipi_force_write)(uint8_t data_type, uint8_t *param, uint16_t param_length);				//add for LCD adapter
	int32_t (*mipi_force_read)(uint8_t command, uint8_t bytes_to_read, uint8_t *read_buffer);
	int32_t (*mipi_eotp_set)(uint8_t rx_en, uint8_t tx_en);
};

struct i2c_info{
	uint32_t i2c_addr;
	struct ops_i2c *ops;
};

struct spi_info{
	struct ops_spi *ops;
};

struct info_mipi {
	uint16_t work_mode; /*command_mode, video_mode*/
	uint16_t video_bus_width;
	uint32_t lan_number;
	uint32_t phy_feq;
	uint16_t h_sync_pol;
	uint16_t v_sync_pol;
	uint16_t de_pol;
	uint16_t te_pol; /*only for command_mode*/
	uint16_t color_mode_pol;
	uint16_t shut_down_pol;
	struct timing_rgb *timing;
	struct ops_mipi *ops;
#ifdef CONFIG_DSIH_INTER_PHY
	uint16_t dln_timer;
#endif
};

struct info_rgb {
	uint16_t cmd_bus_mode; /*spi, i2c*/
	uint16_t video_bus_width;
	uint16_t h_sync_pol;
	uint16_t v_sync_pol;
	uint16_t de_pol;
	struct timing_rgb *timing;
	union{
		struct i2c_info *i2c;
		struct spi_info *spi;
	}bus_info;
};

struct info_spi {
	uint16_t cmd_bus_mode;
	uint16_t bus_width;
	uint16_t bpp;
	uint16_t te_pol;
	uint16_t spi_mode; // 0,1,2,3
	uint16_t cd_gpio;
	uint32_t te_sync_delay;
	uint8_t bus_num;
	uint8_t spi_pol_mode;
	uint32_t speed;
	uint8_t cs;
	struct ops_spi *ops;
};

struct info_mcu {
	uint16_t bus_mode; /*8080, 6800*/
	uint16_t bus_width;
	uint16_t bpp;
	uint16_t te_pol;
	uint32_t te_sync_delay;
	struct timing_mcu *timing;
	struct ops_mcu *ops;
};


/* LCD abstraction */
struct panel_spec {
	uint32_t cap;
	uint16_t width;
	uint16_t height;
	uint32_t fps;
	uint16_t type; /*mcu, rgb, mipi*/
	uint16_t direction;
	uint16_t is_need_reset;
	uint16_t is_need_dsc;
	uint16_t non_continue_clk_en;
	union {
		struct info_mcu *mcu;
		struct info_spi *spi;
		struct info_rgb *rgb;
		struct info_mipi * mipi;
	} info;
	struct panel_operations *ops;
};

struct panel_cfg {
	uint32_t lcd_id;
	struct panel_spec *panel;
};

extern void LCD_SetBackLightBrightness( unsigned long  value);
#endif

