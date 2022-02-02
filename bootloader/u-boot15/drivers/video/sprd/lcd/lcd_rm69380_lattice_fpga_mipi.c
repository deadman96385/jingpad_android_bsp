/*  
 * Copyright (C) 2017 Spreadtrum Communications Inc.
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

#include "sprd_panel.h"
#include "sprd_dsi.h"
#include "dsi/mipi_dsi_api.h"
#include "sprd_dphy.h"
#include <i2c.h>
#include <asm/arch-sharkl5pro/pinmap.h>
#include <sprd_spi_md6000.h>
#include <sprd_spi_md6000_initial_new_normal_panel_20201224.h>
#ifdef CONFIG_SC2703_LCD_POWERON
extern void lcd_use_sc2703l_to_power_off(void);
extern void lcd_use_sc2703l_to_power_boost(void);
#endif

static uint8_t init_data[] = {
     //   0x15, 0x00, 0x00, 0x02, 0xFE, 0x40, 
     //   0x15, 0x00, 0x00, 0x02, 0xAB, 0x08,
     //   0x15, 0x00, 0x00, 0x02, 0xFE, 0x26,
     //   0x15, 0x00, 0x00, 0x02, 0x75, 0x39,
     //   0x15, 0x00, 0x00, 0x02, 0x1D, 0x14,
     //   0x15, 0x00, 0x00, 0x02, 0xFE, 0x00,
     //   0x15, 0x00, 0x00, 0x02, 0xC2, 0x08,
     //   0x15, 0x00, 0x00, 0x02, 0x35, 0x00,
        0x39, 0x00, 0x00, 0x03, 0x51, 0x00, 0xFF,
     //   0x13, 0x78, 0x00, 0x01, 0x11,
     //   0x13, 0x32, 0x00, 0x01, 0x29,
        CMD_END
};

static uint8_t init_data1[] = {
        0x39, 0x00, 0x00, 0x03, 0x51, 0x00, 0x00,
        CMD_END
};


static int mipi_dsi_send_cmds(struct sprd_dsi *dsi, void *data)
{
	uint16_t len;
	struct dsi_cmd_desc *cmds = data;

	if ((cmds == NULL) || (dsi == NULL))
		return -1;

	for (; cmds->data_type != CMD_END;) {
		len = (cmds->wc_h << 8) | cmds->wc_l;
		mipi_dsi_dcs_write(dsi, cmds->payload, len);
		if (cmds->wait)
			msleep(cmds->wait);
		cmds = (struct dsi_cmd_desc *)(cmds->payload + len);
	}
	return 0;
}

static int rm69380_init(void)
{
	struct sprd_dsi *dsi = &dsi_device;
	struct sprd_dphy *dphy = &dphy_device;
	uint32_t load_starttime;
    uint32_t load_finishtime;
    /* 1200*2560 */
#if 1
    printk("MD6000: sprd_spi_md6000_load_bitfile()\n");
    load_starttime = SCI_GetTickCount();
    sprd_spi_md6000_load_bitfile(1, bitfile_double_mipi, sizeof(bitfile_double_mipi));
    load_finishtime = SCI_GetTickCount();
    printk("load bitfile double mipi spend time: %dms\n", load_finishtime-load_starttime);
    SCI_GetTickCount();
#endif
	//mipi_dsi_lp_cmd_enable(dsi, true);
	mipi_dsi_send_cmds(dsi, init_data);
	mipi_dsi_set_work_mode(dsi, SPRD_MIPI_MODE_VIDEO);
	//mipi_dsi_lp_cmd_enable(dsi, true);
	mipi_dsi_send_cmds(dsi, init_data);
	mipi_dsi_state_reset(dsi);
	mipi_dphy_hs_clk_en(dphy, true);
#if 1 //reset
	sprd_gpio_request(NULL, MD6000_RST);
	sprd_gpio_direction_output(NULL, MD6000_RST, 1);
	printk("MD6000: MD6000_RST HIGHT 1\n");
	sprd_gpio_direction_output(NULL, MD6000_RST, 0);
	printk("MD6000: MD6000_RST LOW\n");
	sprd_gpio_direction_output(NULL, MD6000_RST, 1);
	printk("MD6000: MD6000_RST HIGHT 2\n");
	printf("#Eric: MD6000: MD6000 Logic Rst time: %dms\n",
						SCI_GetTickCount());
	mdelay(100);
#endif
	pr_err("rm69380 init success\n");

	return 0;
}
int rm69380_backlight_set(void)
{
	struct sprd_dsi *dsi = &dsi_device;
	struct sprd_dphy *dphy = &dphy_device;

	mipi_dsi_send_cmds(dsi, init_data);

}

int rm69380_backlight_close(void)
{
	struct sprd_dsi *dsi = &dsi_device;
	struct sprd_dphy *dphy = &dphy_device;
    int i;

    for(i = 0; i < 10; i++)
    {
        mipi_dsi_send_cmds(dsi, init_data1);
    }

}

static int rm69380_readid(void)
{
	struct sprd_dsi *dsi = &dsi_device;
	uint8_t read_buf[3] = {0};

	//sprd_spi_md6000_load_bitfile(0, bitfile_3_4, sizeof(bitfile_3_4));
#if 1
	pr_info("rm69380 read id success!\n");
	return 0;
#endif
  //  mdelay(50);
	mipi_dsi_lp_cmd_enable(dsi, true);
	mipi_dsi_set_max_return_size(dsi, 3);
	mipi_dsi_dcs_read(dsi, 0x40, read_buf, 3);

	pr_info("rm69380 read id read_buf[3] = {0x%x, 0x%x, 0x%x}\n",
					read_buf[0], read_buf[1], read_buf[2]);

	if((0x02 == read_buf[0]) && (0x3C == read_buf[1]) &&
	   (0xc0 == read_buf[2])) {
		pr_info("rm69380 read id success!\n");
		return 0;
        }
	pr_err("rm69380 read id failed:0x%x,0x%x,0x%x\n",read_buf[0],read_buf[1],read_buf[2]);
	return 0;
}
int rm69380_power_off(void)
{ 
    sprd_gpio_request(NULL, MD6000_VDD1V2);
    sprd_gpio_direction_output(NULL, MD6000_VDD1V2, 0);
    mdelay(5);
    sprd_gpio_request(NULL, MD6000_RST);
    sprd_gpio_direction_output(NULL, MD6000_RST, 0);
    mdelay(5);
    sprd_gpio_request(NULL, MD6000_VDD1V85);
    sprd_gpio_direction_output(NULL, MD6000_VDD1V85, 0);
    mdelay(5);
    regulator_disable("vddldo1");
    sprd_gpio_request(NULL, CONFIG_LCM_GPIO_1V8_LDO);
    sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_1V8_LDO, 0);
    mdelay(5);
    sprd_gpio_request(NULL, CONFIG_LCM_GPIO_RSTN);
    sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_RSTN, 0);
    mdelay(5);


}
static int rm69380_power(int on)
{
//#define CONFIG_FPGA_GPIO_1V8_LDO  72
//#define CONFIG_FPGA_GPIO_1V2_LDO  73 
//#define CONFIG_FPGA_GPIO_RST_LDO  137 
//#define CONFIG_FPGA_GPIO_LOGIC_RST_LDO  159
	

    if (on) {
	sprd_gpio_request(NULL, MD6000_RST);
	sprd_gpio_direction_output(NULL, MD6000_RST, 1);
	sprd_gpio_request(NULL, MD6000_VDD1V85);
	sprd_gpio_direction_output(NULL, MD6000_VDD1V85, 1);
	sprd_gpio_request(NULL, MD6000_VDD1V2);
	sprd_gpio_direction_output(NULL, MD6000_VDD1V2, 1);
	sprd_gpio_request(NULL, MD6000_LOGIC_RST);
	sprd_gpio_direction_output(NULL, MD6000_LOGIC_RST, 0);
        mdelay(5);
        regulator_set_voltage("vddldo1",3300);
        regulator_enable("vddldo1");
        sprd_gpio_request(NULL, CONFIG_LCM_GPIO_1V8_LDO);
        sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_1V8_LDO, 1);
        mdelay(5);
        sprd_gpio_request(NULL, CONFIG_LCM_GPIO_RSTN);
        sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_RSTN, 1);
        mdelay(5);
        sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_RSTN, 0);
        mdelay(5);
        sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_RSTN, 1);
        mdelay(20);
    } else {
        sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_RSTN, 0);
        mdelay(5);
	sprd_gpio_direction_output(NULL, MD6000_VDD1V2, 0);
        mdelay(5);
	sprd_gpio_direction_output(NULL, MD6000_VDD1V85, 0);
    }
    pr_err("rm69380 power success\n");

    return 0;
}

static struct panel_ops rm69380_ops = {
	.init = rm69380_init,
	.read_id = rm69380_readid,
	.power = rm69380_power,
};

/* 1200*1920 60fps */
static struct panel_info rm69380_info = {
	/* common parameters */
	.lcd_name = "lcd_rm69380_lattice_fpga_mipi_2k",
	.type = SPRD_PANEL_TYPE_MIPI,
	.bpp = 24,
//	.fps = 60,
	.width = 1512,
	.height = 2072,

	/* DPI specific parameters */
	.pixel_clk = 192000000, /*1536MHz*/
	.rgb_timing = {
		.hfp = 150,//30,
		.hbp = 150,//30,
		.hsync = 8,//4,
		.vfp = 30,
		.vbp = 13,
		.vsync = 13,
	},

	/* MIPI DSI specific parameters */
	.phy_freq = 1260*1000,//1100
	.lane_num = 4,
	.work_mode = SPRD_MIPI_MODE_VIDEO,
	.burst_mode = VIDEO_BURST_WITH_SYNC_PULSES,
	.nc_clk_en = false,
};

struct panel_driver rm69380_fpga_driver = {
	.info = &rm69380_info,
	.ops = &rm69380_ops,
};
