/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 *
 */

#include "sprdfb_chip_common.h"
#include "sprdfb.h"
#include "sprdfb_panel.h"

#ifdef LCM_SAME_IC_SUPPORT
#include <common.h>
#include <adc_drvapi.h>
#endif

#if defined(CONFIG_I2C) && defined(CONFIG_SPI)
extern struct panel_if_ctrl sprdfb_mcu_ctrl;
#endif
extern struct panel_if_ctrl sprdfb_rgb_ctrl;
extern struct panel_if_ctrl sprdfb_mipi_ctrl;
#ifdef CONFIG_SPI
extern struct panel_if_ctrl sprdfb_spi_ctrl;
#endif

extern struct panel_spec lcd_dummy_mipi_qvga_spec;
extern struct panel_spec lcd_dummy_mipi_spec;
extern struct panel_spec lcd_nt35510_mipi_spec;
extern struct panel_spec lcd_nt35516_mipi_spec;
extern struct panel_spec lcd_nt35516_mcu_spec;
extern struct panel_spec lcd_nt35516_rgb_spi_spec;
extern struct panel_spec lcd_otm8018b_mipi_spec;
extern struct panel_spec lcd_hx8363_mcu_spec;
extern struct panel_spec lcd_panel_hx8363_rgb_spi_spec;
extern struct panel_spec lcd_panel_hx8363_rgb_spi_spec_viva;
extern struct panel_spec lcd_s6d0139_spec;
extern struct panel_spec lcd_otm1283a_mipi_spec;
extern struct panel_spec lcd_ssd2075_mipi_spec;
extern struct panel_spec lcd_panel_st7789v;
extern struct panel_spec lcd_panel_sc7798_rgb_spi;
extern struct panel_spec lcd_hx8369b_mipi_spec;
extern struct panel_spec lcd_sd7798d_mipi_spec;
extern struct panel_spec lcd_nt35502_mipi_spec;
extern struct panel_spec lcd_panel_ili9341;
extern struct panel_spec lcd_panel_ili9486;
extern struct panel_spec lcd_panel_ili9486_rgb_spi;
extern struct panel_spec lcd_ili9486s1_mipi_spec;
extern struct panel_spec lcd_nt51017_mipi_lvds_spec;
extern struct panel_spec lcd_t8861_mipi_spec;
extern struct panel_spec lcd_hx8379a_mipi_spec;
extern struct panel_spec lcd_hx8379c_mipi_spec;
extern struct panel_spec lcd_hx8389c_mipi_spec;
extern struct panel_spec ili6150_lvds_spec;
extern struct panel_spec lcd_rm68180_mipi_spec;
extern struct panel_spec lcd_ili9806e_mipi_spec;
extern struct panel_spec lcd_ili9806e_2_mipi_spec;
extern struct panel_spec lcd_otm8019a_mipi_spec;
extern struct panel_spec lcd_otm1906c_mipi_spec;
extern struct panel_spec lcd_otm1901_mipi_spec;
extern struct panel_spec lcd_fl10802_mipi_spec;
extern struct panel_spec lcd_jd9161_mipi_spec;
extern struct panel_spec lcd_hx8369b_mipi_vivaltoVE_spec;
extern struct panel_spec lcd_vx5b3d_mipi_spec;
extern struct panel_spec lcd_hx8369b_grandneo_mipi_spec;
extern struct panel_spec lcd_hx8369b_tshark2_j3_mipi_spec;
extern struct panel_spec lcd_sd7798d_mipi_spec;
extern struct panel_spec lcd_s6d77a1_mipi_spec;
extern struct panel_spec lcd_nt51017_mipi_spec;
extern struct panel_spec lcd_hx8394d_mipi_spec;
extern struct panel_spec lcd_hx8394a_mipi_spec;
extern struct panel_spec lcd_nt35596h_mipi_spec;
extern struct panel_spec lcd_nt35596h_rdc_mipi_spec;
extern struct panel_spec lcd_s6d7aa0x62_mipi_spec;
extern struct panel_spec lcd_ams549hq01_mipi_spec;
extern struct panel_spec lcd_nt35596_mipi_spec;
extern struct panel_spec lcd_nt35597_mipi_spec;
extern struct panel_spec lcd_s6e3fa3_mipi_spec;
extern struct panel_spec lcd_ili9885_mipi_spec;
extern struct panel_spec lcd_nt35532_mipi_spec;
extern struct panel_spec lcd_nt35597_mipi_fpga_spec;
extern struct panel_spec lcd_ili9881c_mipi_spec;
extern struct panel_spec lcd_ili9881c_3lane_mipi_spec;
extern struct panel_spec lcd_ili9881c_weiyi_mipi_spec;
extern struct panel_spec lcd_nt35532_2_mipi_spec;
extern struct panel_spec lcd_st7701_mipi_spec;
extern struct panel_spec lcd_hx8399c_mipi_spec;
extern struct panel_spec lcd_otm1911_mipi_spec;
extern struct panel_spec lcd_jd9365_mipi_spec;
extern struct panel_spec lcd_gc9305_spi_spec;
extern struct panel_spec lcd_gc9306_spi_spec;
extern struct panel_spec lcd_st7789v2_spi_spec;
extern struct panel_spec lcd_dummy_spi_spec;
extern struct panel_spec lcd_jd9365_zgd_mipi_spec;
extern struct panel_spec lcd_jd9365_hf_mipi_spec;
extern struct panel_spec lcd_otm1289a_kd_mipi_spec;
extern struct panel_spec lcd_ili9881p_mipi_spec;
extern struct panel_spec lcd_ft8006m_mipi_spec;
extern struct panel_spec lcd_gc9503_jl_mipi_spec;
extern struct panel_spec lcd_st7701_zgd_mipi_spec;
extern struct panel_spec lcd_st7703_mipi_spec;

void sprdfb_panel_remove(struct sprdfb_device *dev);

static ushort colormap[256];

static struct panel_cfg panel_cfg[] = {
#if defined (CONFIG_FB_LCD_ILI9885_MIPI)
	{
		.lcd_id = 0x98,
		.panel = &lcd_ili9885_mipi_spec,
	},
#endif
#if defined (CONFIG_FB_LCD_NT35532_MIPI)
	{
		.lcd_id = 0x32,
		.panel = &lcd_nt35532_mipi_spec,
	},
#endif
#if defined (CONFIG_FB_LCD_NT35532_2_MIPI)
	{
		.lcd_id = 0x32,
		.panel = &lcd_nt35532_2_mipi_spec,
	},
#endif
#if defined (CONFIG_FB_LCD_OTM1911_MIPI)
{
		.lcd_id = 0x1911,
		.panel = &lcd_otm1911_mipi_spec,
	},
#endif
#if defined (CONFIG_FB_LCD_HX8399C_MIPI)
	{
		.lcd_id = 0x8399,
		.panel = &lcd_hx8399c_mipi_spec,
	},
#endif
#if defined (CONFIG_FB_LCD_ST7701_MIPI)
	{
		.lcd_id = 0x7701,
		.panel = &lcd_st7701_mipi_spec,
	},
#endif
#if defined (CONFIG_FB_LCD_HX8379C_MIPI_SHARKL_J1POPLTE)
		{
			.lcd_id = 0x8379,
			.panel = &lcd_hx8379c_mipi_spec,
		},
#endif

#ifdef CONFIG_FB_LCD_NT35510_MIPI
	{
		.lcd_id = 0x10,
		.panel = &lcd_nt35510_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_NT35516_MIPI
	{
		.lcd_id = 0x16,
		.panel = &lcd_nt35516_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_HX8394D_MIPI
	{
		.lcd_id = 0x8394,
		.panel = &lcd_hx8394d_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_NT35516_MCU
	{
		.lcd_id = 0x16,
		.panel = &lcd_nt35516_mcu_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_NT35516_RGB_SPI
	{
		.lcd_id = 0x16,
		.panel = &lcd_nt35516_rgb_spi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_OTM8018B_MIPI
	{
		.lcd_id = 0x18,
		.panel = &lcd_otm8018b_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_HX8363_MCU
	{
		.lcd_id = 0x18,
		.panel = &lcd_hx8363_mcu_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_VIVA_RGB_SPI
	{
		.lcd_id = 0x63,
		.panel = &lcd_panel_hx8363_rgb_spi_spec_viva,
	},
#endif

#ifdef CONFIG_FB_LCD_RM68180_MIPI
	{
		.lcd_id = 0x80,
		.panel = &lcd_rm68180_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_HX8363_RGB_SPI
	{
		.lcd_id = 0x84,
		.panel = &lcd_panel_hx8363_rgb_spi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_S6D0139
	{
		.lcd_id = 0x139,
		.panel = &lcd_s6d0139_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_OTM1283A_MIPI
	{
		.lcd_id = 0x1283,
		.panel = &lcd_otm1283a_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_SSD2075_MIPI
	{
		.lcd_id = 0x2075,
		.panel = &lcd_ssd2075_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_ST7789V_MCU
	{
		.lcd_id = 0x7789,
		.panel = &lcd_panel_st7789v,
	},
#endif

#ifdef CONFIG_FB_LCD_SC7798_RGB_SPI
	{
		.lcd_id = 0x7798,
		.panel = &lcd_panel_sc7798_rgb_spi,
	},
#endif

#if defined(CONFIG_FB_LCD_HX8369B_MIPI) || defined(CONFIG_FB_LCD_HX8369B_MIPI_COREPRIMELITE)|| defined(CONFIG_FB_LCD_HX8369B_MIPI_SHARKLS_Z3LTE) || defined(CONFIG_FB_LCD_HX8369B_MIPI_SHARKL_J1POPLTE)
	{
		.lcd_id = 0x8369,
		.panel = &lcd_hx8369b_mipi_spec,
	},
#endif

#if defined (CONFIG_FB_LCD_HX8369B_MIPI) ||defined (CONFIG_FB_LCD_HX8369B_MIPI_KIRAN3G)
	{
		.lcd_id = 0x8369,
		.panel = &lcd_hx8369b_mipi_spec,
	},
#endif

#if defined(CONFIG_FB_LCD_SD7798D_MIPI_COREPRIMELITE) || defined(CONFIG_FB_LCD_SD7798D_MIPI_SHARKLS_Z3LTE)
	{
		.lcd_id = 0x55b8f0,
		.panel = &lcd_sd7798d_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_NT35502_MIPI
	{
		.lcd_id = 0x8370,
		.panel = &lcd_nt35502_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_NT51017_MIPI
	{
		.lcd_id = 0x51017,
		.panel = &lcd_nt51017_mipi_spec,
	},
#endif


#ifdef CONFIG_FB_LCD_ILI9341
	{
		.lcd_id = 0x9341,
		.panel = &lcd_panel_ili9341,
	},
#endif

#ifdef CONFIG_FB_LCD_ILI9486
	{
		.lcd_id = 0x9486,
		.panel = &lcd_panel_ili9486,
	},
#endif

#ifdef CONFIG_FB_LCD_ILI9486_RGB_SPI
	{
		.lcd_id = 0x9486,
		.panel = &lcd_panel_ili9486_rgb_spi,
	},
#endif

#ifdef CONFIG_FB_LCD_ILI9486S1_MIPI
	{
		.lcd_id = 0x8370,
		.panel = &lcd_ili9486s1_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_HX8369B_MIPI_VIVALTO_VE
	{
		.lcd_id = 0x8369,
		.panel = &lcd_hx8369b_mipi_vivaltoVE_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_VX5B3D_MIPI
	{
		.lcd_id = 0x8282,
		.panel = &lcd_vx5b3d_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_GRANDNEO_MIPI
	{
		.lcd_id = 0x8369,
		.panel = &lcd_hx8369b_grandneo_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_TSHARK2_J3_MIPI
	{
		.lcd_id = 0x8369,
		.panel = &lcd_hx8369b_tshark2_j3_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_SD7798D_MIPI
	{
		.lcd_id = 0x55b8f0,
		.panel = &lcd_sd7798d_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_S6D77A1_MIPI_PIKEA_J1
	{
		.lcd_id = 0x55b810,
		.panel = &lcd_s6d77a1_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_NT51017_LVDS
	{
		.lcd_id = 0xC749,
		.panel = &lcd_nt51017_mipi_lvds_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_T8861_MIPI
	{
		.lcd_id = 0x04,
		.panel = &lcd_t8861_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_HX8379A_MIPI
	{
		.lcd_id = 0x8379,
		.panel = &lcd_hx8379a_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_HX8389C_MIPI
	{
		.lcd_id = 0x8389,
		.panel = &lcd_hx8389c_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_S6D7AA0X62_MIPI
	{
		.lcd_id = 0x6262,
		.panel = &lcd_s6d7aa0x62_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_ILI6150_LVDS
	{
		.lcd_id = 0x1806,
		.panel = &ili6150_lvds_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_ILI9806E_MIPI
{
    .lcd_id = 0x4,
    .panel = &lcd_ili9806e_mipi_spec,
},
#endif
#ifdef CONFIG_FB_LCD_ILI9806E_2_MIPI
{
    .lcd_id = 0x980602,
    .panel = &lcd_ili9806e_2_mipi_spec,
},
#endif
#ifdef CONFIG_FB_LCD_OTM8019A_MIPI
	{
		.lcd_id = 0x8019,
		.panel = &lcd_otm8019a_mipi_spec,
	},
#endif
#ifdef CONFIG_FB_LCD_OTM1906C_MIPI
	{
		.lcd_id = 0x1906,
		.panel = &lcd_otm1906c_mipi_spec,
	},
#endif
#ifdef CONFIG_FB_LCD_OTM1901_MIPI
	{
		.lcd_id = 0x1901,
		.panel = &lcd_otm1901_mipi_spec,
	},
#endif
#ifdef CONFIG_FB_LCD_FL10802_MIPI
	{
		.lcd_id = 0x1080,
		.panel = &lcd_fl10802_mipi_spec,
	},
#endif
#ifdef CONFIG_FB_LCD_JD9161_MIPI
	{
		.lcd_id = 0x916100,
		.panel = &lcd_jd9161_mipi_spec,
	},
#endif

#ifdef CONFIG_FB_LCD_HX8394D_MIPI
{
	.lcd_id = 0x8394,
	.panel = &lcd_hx8394d_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_HX8394A_MIPI
{
	.lcd_id = 0x8394,
	.panel = &lcd_hx8394a_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_NT35596H_MIPI
{
	.lcd_id = 0x96,
	.panel = &lcd_nt35596h_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_NT35596_MIPI
{
	.lcd_id = 0x96,
	.panel = &lcd_nt35596_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_NT35597_MIPI
{
	.lcd_id = 0x97,
	.panel = &lcd_nt35597_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_NT35597_MIPI_FPGA
{
	.lcd_id = 0x97,
	.panel = &lcd_nt35597_mipi_fpga_spec,
},
#endif

#ifdef CONFIG_FB_LCD_NT35596H_RDC_MIPI
{
	.lcd_id = 0x86,
	.panel = &lcd_nt35596h_rdc_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_AMS549HQ01_MIPI
{
	.lcd_id = 0x4010,
	.panel = &lcd_ams549hq01_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_S6E3FA3_MIPI
{
	.lcd_id = 0x400001,
	.panel = &lcd_s6e3fa3_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_ILI9881C_WEIYI_MIPI_L505
{
	.lcd_id = 0x988102,
	.panel = &lcd_ili9881c_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_JD9365_ZGD_MIPI_L505
{
	.lcd_id = 0x9365,
	.panel = &lcd_jd9365_zgd_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_JD9365_HF_MIPI_L505
{
	.lcd_id = 0x936502,
	.panel = &lcd_jd9365_hf_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_ILI9881C_WEIYI_MIPI
{
	.lcd_id = 0x988101,
	.panel = &lcd_ili9881c_weiyi_mipi_spec,
},
#endif
#ifdef CONFIG_FB_LCD_L505
{
	.lcd_id = 0x988103,
	.panel = &lcd_ili9881p_mipi_spec,
},
{
	.lcd_id = 0x8006,
	.panel = &lcd_ft8006m_mipi_spec,
},
#endif
#ifdef CONFIG_FB_LCD_OTM1289A_KD_MIPI_L505
{
	.lcd_id = 0x128902,
	.panel = &lcd_otm1289a_kd_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_ILI9881C_MIPI
{
	.lcd_id = 0x9881,
	.panel = &lcd_ili9881c_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_ILI9881C_3LANE_MIPI
{
	.lcd_id = 0x9881,
	.panel = &lcd_ili9881c_3lane_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_JD9161_FWVGA
{
	.lcd_id = 0x9161,
	.panel = &lcd_jd9161_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_JD9161_HLT_MIPI_WVGA
{
	.lcd_id = 0x91613,
	.panel = &lcd_jd9161_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_ST7703_BOE_MIPI_HD
{
	.lcd_id = 0x7703,
	.panel = &lcd_st7703_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_DUMMY_MIPI_QVGA
{
	.lcd_id = 0xFFFF,
	.panel = &lcd_dummy_mipi_qvga_spec,
},
#endif

#ifdef CONFIG_FB_LCD_JD9365_MIPI
{
	.lcd_id = 0x9365,
	.panel = &lcd_jd9365_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_GC9503_JL_MIPI_L701
{
	.lcd_id = 0x9503,
	.panel = &lcd_gc9503_jl_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_ST7701_ZGD_MIPI_L701
{
	.lcd_id = 0x77012,
	.panel = &lcd_st7701_zgd_mipi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_GC9305_SPI
{
	.lcd_id = 0x9305,
	.panel = &lcd_gc9305_spi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_GC9306_SPI
{
	.lcd_id = 0x9306,
	.panel = &lcd_gc9306_spi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_ST7789V2_SPI
{
	.lcd_id = 0x7789,
	.panel = &lcd_st7789v2_spi_spec,
},
#endif

#ifdef CONFIG_FB_LCD_DUMMY_SPI
{
	.lcd_id = 0xFFFF,
	.panel = &lcd_dummy_spi_spec,
},
#endif

{
	.lcd_id = 0xFFFF,
	.panel = &lcd_dummy_mipi_spec,
},
};

static int32_t panel_reset_dispc(struct panel_spec *self)
{
	dispc_write(1, DISPC_RSTN);
	mdelay(20);
	dispc_write(0, DISPC_RSTN);
	mdelay(20);
	dispc_write(1, DISPC_RSTN);
	mdelay(120);

	return 0;
}

static void panel_reset(struct sprdfb_device *dev)
{
	FB_PRINT("sprdfb: [%s]\n",__FUNCTION__);

	//clk/data lane enter LP
	if(NULL != dev->if_ctrl->panel_if_before_panel_reset){
		dev->if_ctrl->panel_if_before_panel_reset(dev);
		mdelay(5);
	}

	//reset panel
	if(NULL != dev->panel->ops->panel_reset){
		dev->panel->ops->panel_reset(dev->panel);
	}
}

static int panel_mount(struct sprdfb_device *dev, struct panel_spec *panel)
{
	uint16_t rval = 1;

	debugf("sprdfb: [%s], type = %d\n",__FUNCTION__, panel->type);

	switch(panel->type){
#ifdef CONFIG_SPI
	case SPRDFB_PANEL_TYPE_SPI:
		dev->if_ctrl = &sprdfb_spi_ctrl;
		break;
#endif
#if defined(CONFIG_I2C) && defined(CONFIG_SPI)
	case SPRDFB_PANEL_TYPE_MCU:
		dev->if_ctrl = &sprdfb_mcu_ctrl;
		break;
#endif
	case SPRDFB_PANEL_TYPE_RGB:
	case SPRDFB_PANEL_TYPE_LVDS:
		dev->if_ctrl = &sprdfb_rgb_ctrl;
		break;
#if ((!defined(CONFIG_SC7710G2)) && (!defined(CONFIG_SPX15)))
	case SPRDFB_PANEL_TYPE_MIPI:
		dev->if_ctrl = &sprdfb_mipi_ctrl;
		break;
#endif
	default:
		debugf("sprdfb: [%s]: erro panel type.(%d)",__FUNCTION__, panel->type);
		dev->if_ctrl = NULL;
		rval = 0 ;
		break;
	};

	if(NULL == dev->if_ctrl){
		return -1;
	}

	if(dev->if_ctrl->panel_if_check){
		rval = dev->if_ctrl->panel_if_check(panel);
	}

	if(0 == rval){
		errorf("sprdfb: [%s] check panel fail!\n", __FUNCTION__);
		dev->if_ctrl = NULL;
		return -1;
	}

	dev->panel = panel;

#ifndef CONFIG_FB_SWDISPC
	if(NULL == dev->panel->ops->panel_reset){
		dev->panel->ops->panel_reset = panel_reset_dispc;
	}
#endif

	dev->if_ctrl->panel_if_mount(dev);

	return 0;
}


int panel_init(struct sprdfb_device *dev)
{
	if((NULL == dev) || (NULL == dev->panel)){
		errorf("sprdfb: [%s]: Invalid param\n", __FUNCTION__);
		return -1;
	}

	FB_PRINT("sprdfb: [%s], type = %d\n",__FUNCTION__, dev->panel->type);

	if(NULL != dev->if_ctrl->panel_if_init){
		dev->if_ctrl->panel_if_init(dev);
	}
	return 0;
}

int panel_ready(struct sprdfb_device *dev)
{
	if((NULL == dev) || (NULL == dev->panel)){
		errorf("sprdfb: [%s]: Invalid param\n", __FUNCTION__);
		return -1;
	}

	FB_PRINT("sprdfb: [%s],  type = %d\n",__FUNCTION__, dev->panel->type);

	if(NULL != dev->if_ctrl->panel_if_ready){
		dev->if_ctrl->panel_if_ready(dev);
	}

	return 0;
}

#ifdef LCM_SAME_IC_SUPPORT
static int32_t LCM_SAME_IC_ADC_GetValue()
{
	int iLoop = 0, iTimes = 10;
	int32_t adc_value = 0, adc_value_all = 0;
	volatile int32_t adc_channel = 4;

	for (iLoop=0;iLoop<iTimes;iLoop++)
	{
		adc_value = ADC_GetValue(adc_channel, false);
		adc_value_all += adc_value;
		printf("LCM_SAME_IC_ADC_GetValue adc_value = %d\n", adc_value);
	}
	adc_value = adc_value_all/iTimes;
	printf("LCM_SAME_IC_ADC_GetValue adc_channel = %d, adc_value = %d\n", adc_channel, adc_value);

	return adc_value;
}
#endif

static struct panel_spec *adapt_panel_from_readid(struct sprdfb_device *dev)
{
	int id, i, ret, b_panel_reset=0;
	uint32_t id_adc;

	FB_PRINT("sprdfb: [%s]\n",__FUNCTION__);

	for(i = 0;i<(sizeof(panel_cfg))/(sizeof(panel_cfg[0]));i++) {
		debugf("sprdfb: [%s]: try panel 0x%x\n", __FUNCTION__, panel_cfg[i].lcd_id);
		ret = panel_mount(dev, panel_cfg[i].panel);
		if(ret < 0){
			errorf("sprdfb: panel_mount failed!\n");
			continue;
		}
		if(dev->ctrl->update_clk)
			dev->ctrl->update_clk(dev);
		panel_init(dev);
		if ((b_panel_reset==0) || (1 == dev->panel->is_need_reset))
		{
			panel_reset(dev);
			b_panel_reset=1;
		}
#ifdef LCM_SAME_IC_SUPPORT
		id_adc = LCM_SAME_IC_ADC_GetValue();	//10801=600,30k, 10802=300,10k
		save_lcd_adc_to_kernel(id_adc);
#endif
		id = dev->panel->ops->panel_readid(dev->panel);
		if(id == panel_cfg[i].lcd_id) {
			debugf("sprdfb: [%s]: LCD Panel 0x%x is attached!\n", __FUNCTION__, panel_cfg[i].lcd_id);

			if(NULL != dev->panel->ops->panel_init){
				dev->panel->ops->panel_init(dev->panel);		//zxdebug modify for LCD adaptor
			}

			save_lcd_id_to_kernel(id);
			panel_ready(dev);
			return panel_cfg[i].panel;
		} else {							//zxdbg for LCD adaptor
			errorf("sprdfb: [%s]: LCD Panel 0x%x attached fail!go next\n", __FUNCTION__, panel_cfg[i].lcd_id);
			sprdfb_panel_remove(dev);				//zxdebug modify for LCD adaptor
		}
	}

	errorf("sprdfb:  [%s]: final failed to attach LCD Panel!\n", __FUNCTION__);
	return NULL;
}

uint16_t sprdfb_panel_probe(struct sprdfb_device *dev)
{
	struct panel_spec *panel;

	if(NULL == dev){
		errorf("sprdfb: [%s]: Invalid param\n", __FUNCTION__);
		return -1;
	}

	FB_PRINT("sprdfb: [%s]\n",__FUNCTION__);

	/* can not be here in normal; we should get correct device id from uboot */
	panel = adapt_panel_from_readid(dev);

	if (panel) {
        /*To support different resolution in a u-boot.bin,change vl_row && vl_col for lcd_line_length
         * in common/lcd.c after reading panel id*/
        	panel_info.vl_row = panel->height;
        	panel_info.vl_col = panel->width;
#ifdef CONFIG_DSIH_INTER_PHY
	int dln_timer = 0x39;
	if (panel->info.mipi->dln_timer)
		dln_timer = panel->info.mipi->dln_timer;
	__raw_writel((dln_timer << 16)|(0x87 << 0), REG_DISP_AHB_DSI_CTRL);
	printf("panel->dln_timer=0x%x\n",panel->info.mipi->dln_timer);
#endif
		save_lcd_size_to_kernel(panel_info.vl_row, panel_info.vl_col);
		FB_PRINT("sprdfb: [%s] got panel\n", __FUNCTION__);
		return 0;
	}

	errorf("sprdfb: [%s] can not got panel\n", __FUNCTION__);

	return -1;
}

void sprdfb_panel_invalidate_rect(struct panel_spec *self,
				uint16_t left, uint16_t top,
				uint16_t right, uint16_t bottom)
{
	FB_PRINT("sprdfb: [%s]\n, (%d, %d, %d,%d)",__FUNCTION__, left, top, right, bottom);

	if(NULL != self->ops->panel_invalidate_rect){
		self->ops->panel_invalidate_rect(self, left, top, right, bottom);
	}
}

void sprdfb_panel_invalidate(struct panel_spec *self)
{
	FB_PRINT("sprdfb: [%s]\n",__FUNCTION__);

	if(NULL != self->ops->panel_invalidate){
		self->ops->panel_invalidate(self);
	}
}

void sprdfb_panel_before_refresh(struct sprdfb_device *dev)
{
	FB_PRINT("sprdfb: [%s]\n",__FUNCTION__);

	if(NULL != dev->if_ctrl->panel_if_before_refresh)
		dev->if_ctrl->panel_if_before_refresh(dev);
}

void sprdfb_panel_after_refresh(struct sprdfb_device *dev)
{
	FB_PRINT("sprdfb: [%s]\n",__FUNCTION__);

	if(NULL != dev->if_ctrl->panel_if_after_refresh)
		dev->if_ctrl->panel_if_after_refresh(dev);
}

void sprdfb_panel_remove(struct sprdfb_device *dev)
{
	FB_PRINT("sprdfb: [%s]\n",__FUNCTION__);

	if((NULL != dev->if_ctrl) && (NULL != dev->if_ctrl->panel_if_uninit)){
		dev->if_ctrl->panel_if_uninit(dev);
	}
	dev->panel = NULL;
}

