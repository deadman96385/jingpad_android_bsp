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

extern struct panel_driver ft8006p_hlt_driver;
extern struct panel_driver ft8006p_huaxian_driver;
extern struct panel_driver dummy_mipi_driver;
extern struct panel_driver icnl9911_txd_driver;
extern struct panel_driver ili9881c_truly_driver;
extern struct panel_driver ili9881c_3lane_driver;
extern struct panel_driver ili9881c_skyworth_driver;
extern struct panel_driver st7701_boe_driver;
extern struct panel_driver st7701_coe_driver;
extern struct panel_driver nt35532_truly_driver;
extern struct panel_driver nt35695_truly_driver;
extern struct panel_driver nt35596_boe_driver;
extern struct panel_driver nt35597_boe_driver;
extern struct panel_driver nt35597_fpga_driver;
extern struct panel_driver jd9161_xxx_driver;
extern struct panel_driver jd9365z_king_driver;
extern struct panel_driver jd9366d_truly_driver;
extern struct panel_driver rm67191_edo_driver;
extern struct panel_driver r61350_truly_driver;
extern struct panel_driver td4310_truly_driver;

static struct panel_cfg supported_panel[] = {
#ifdef CONFIG_LCD_FT8006P_HLT_MIPI_HDP
	{
		.lcd_id = 0xf0,
		.drv = &ft8006p_hlt_driver,
	},
#endif
#ifdef CONFIG_LCD_FT8006P_HUAXIAN_MIPI_HDP
	{
		.lcd_id = 0xe0,
		.drv = &ft8006p_huaxian_driver,
	},
#endif
#ifdef CONFIG_LCD_ICNL9911_TXD_MIPI_HDP
        {
                .lcd_id = 0x9911,
                .drv = &icnl9911_txd_driver,
        },
#endif
#ifdef CONFIG_LCD_ILI9881C_TRULY_MIPI_HD
	{
		.lcd_id = 0x9881,
		.drv = &ili9881c_truly_driver,
	},
#endif
#ifdef CONFIG_LCD_ILI9881C_3LANE_MIPI_HD
	{
		.lcd_id = 0x9881,
		.drv = &ili9881c_3lane_driver,
	},
#endif
#ifdef CONFIG_LCD_ILI9881C_SKYWORTH_HD
	{
		.lcd_id = 0x98814,
		.drv = &ili9881c_skyworth_driver,
	},
#endif
#ifdef CONFIG_LCD_ST7701_BOE_MIPI_WVGA
	{
		.lcd_id = 0x7701,
		.drv = &st7701_boe_driver,
	},
#endif
#ifdef CONFIG_LCD_ST7701_COE_MIPI_WVGA
	{
		.lcd_id = 0x77011,
		.drv = &st7701_coe_driver,
	},
#endif
#ifdef CONFIG_LCD_NT35532_TRULY_MIPI_FHD
	{
		.lcd_id = 0x32,
		.drv = &nt35532_truly_driver,
	},
#endif
#ifdef CONFIG_LCD_NT35596_BOE_MIPI_FHD
	{
		.lcd_id = 0x96,
		.drv = &nt35596_boe_driver,
	},
#endif
#ifdef CONFIG_LCD_NT35597_BOE_MIPI_HD
	{
		.lcd_id = 0x97,
		.drv = &nt35597_boe_driver,
	},
#endif
#ifdef CONFIG_LCD_NT35597_FPGA_MIPI_2K
	{
		.lcd_id = 0x97,
		.drv = &nt35597_fpga_driver,
	},
#endif
#ifdef CONFIG_LCD_NT35695_TRULY_MIPI_FHD
	{
		.lcd_id = 0x35695,
		.drv = &nt35695_truly_driver,
	},
#endif
#ifdef CONFIG_LCD_JD9161_XXX_MIPI_WVGA
	{
		.lcd_id = 0x91612,
		.drv = &jd9161_xxx_driver,
	},
#endif
#ifdef CONFIG_LCD_JD9365Z_KING_MIPI_HDP
	{
		.lcd_id = 0x9365,
		.drv = &jd9365z_king_driver,
	},
#endif
#ifdef CONFIG_LCD_JD9366D_TRULY_MIPI_HDP
	{
		.lcd_id = 0x9366,
		.drv = &jd9366d_truly_driver,
	},
#endif
#ifdef CONFIG_LCD_RM67191_EDO_MIPI_FHD
	{
		.lcd_id = 0x67191,
		.drv = &rm67191_edo_driver,
	},
#endif
#ifdef CONFIG_LCD_R61350_TRULY_MIPI_HD
	{
		.lcd_id = 0x61350,
		.drv = &r61350_truly_driver,
	},
#endif
#ifdef CONFIG_LCD_TD4310_TRULY_MIPI_FHD
	{
		.lcd_id = 0x4310,
		.drv = &td4310_truly_driver,
	},
#endif
/* warning: the dummy lcd must be the last item in this array */
	{
		.lcd_id = 0xFFFF,
		.drv = &dummy_mipi_driver,
	},
};
