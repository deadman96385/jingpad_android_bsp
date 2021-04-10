/******************************************************************************
 ** File Name:    sprdfb_dispc.c                                            *
 ** Author:                                                           *
 ** DATE:                                                           *
 ** Copyright:    2005 Spreatrum, Incoporated. All Rights Reserved.           *
 ** Description:                                                            *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                                         *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                                 *
 **
 ******************************************************************************/

#include "sprdfb_chip_common.h"
#include "sprdfb.h"
#include "sprdfb_panel.h"

#define WIDTH_ALIGN( value, base ) (((value) + ((base) - 1)) & ~((base) - 1))


static uint16_t		is_first_frame = 1;

extern void sprdfb_panel_before_refresh(struct sprdfb_device *dev);
extern void sprdfb_panel_after_refresh(struct sprdfb_device *dev);
extern void sprdfb_panel_invalidate(struct panel_spec *self);
extern void sprdfb_panel_invalidate_rect(struct panel_spec *self,
				uint16_t left, uint16_t top,
				uint16_t right, uint16_t bottom);

/* dispc soft reset */
static void dispc_reset(void)
{
	FB_PRINT("sprdfb:[%s]\n",__FUNCTION__);
	__raw_writel(__raw_readl(DISPC_AHB_SOFT_RST) | (BIT_DISPC_SOFT_RST), DISPC_AHB_SOFT_RST);
	udelay(10);
	__raw_writel(__raw_readl(DISPC_AHB_SOFT_RST) & (~(BIT_DISPC_SOFT_RST)), DISPC_AHB_SOFT_RST);
}

static inline void dispc_set_bg_color(uint32_t bg_color)
{
	FB_PRINT("sprdfb:[%s]\n",__FUNCTION__);

	dispc_write(bg_color, DISPC_BG_COLOR);
}

static inline void dispc_set_osd_ck(uint32_t ck_color)
{
	FB_PRINT("sprdfb:[%s]\n",__FUNCTION__);

	dispc_write(ck_color, DISPC_OSD_CK);
}

static void dispc_dithering_enable(uint16_t enable)
{
	FB_PRINT("sprdfb:[%s]\n",__FUNCTION__);
	if(enable){
		dispc_set_bits((1<<6), DISPC_CTRL);
	}else{
		dispc_clear_bits((1<<6), DISPC_CTRL);
	}
}

static void dispc_set_exp_mode(uint16_t exp_mode)
{
	uint32_t reg_val = dispc_read(DISPC_CTRL);

	FB_PRINT("sprdfb:[%s]\n",__FUNCTION__);

	reg_val &= ~(0x3 << 16);
	reg_val |= (exp_mode << 16);
	dispc_write(reg_val, DISPC_CTRL);
}

static void dispc_module_enable(void)
{
	FB_PRINT("sprdfb:[%s]\n",__FUNCTION__);
#if !((defined(CONFIG_SOC_SHARKLJ1)) || (defined(CONFIG_SC9833)) || (defined(CONFIG_SPRD_SOC_SP9853I)) || (defined(CONFIG_SOC_SHARKLE)) || (defined(CONFIG_SOC_PIKE2)) || (defined(CONFIG_SOC_SHARKL3)) || (defined(CONFIG_SPRD_SOC_ROC1)) || (defined(CONFIG_SPRD_SOC_SHARKL5)) || (defined(CONFIG_SPRD_SOC_SHARKL5PRO)))
	/*dispc module enable */
	dispc_write((1<<0), DISPC_CTRL);
#endif
	/*disable dispc INT*/
	dispc_write(0x0, DISPC_INT_EN);

	/* clear dispc INT */
	dispc_write(0x1F, DISPC_INT_CLR);
}

static inline int32_t  dispc_set_disp_size(struct sprdfb_device *dev)
{
	uint32_t reg_val;
	int width_strike;

	FB_PRINT("sprdfb:[%s]\n",__FUNCTION__);
	if (SPRDFB_MIPI_MODE_VIDEO == dev->panel->info.mipi->work_mode) {
#if defined(CONFIG_SC9860)
		width_strike = WIDTH_ALIGN(dev->panel->width, 16);
#else
		width_strike = WIDTH_ALIGN(dev->panel->width, 1);
#endif
		FB_PRINT("width_strike = %d\n", width_strike);
		reg_val = (width_strike & 0xfff)
			| ((dev->panel->height & 0xfff ) << 16);
	} else
		reg_val = (dev->panel->width & 0xfff)
			| ((dev->panel->height & 0xfff ) << 16);
	dispc_write(reg_val, DISPC_SIZE_XY);

	return 0;
}
enum {
	DPU_LAYER_FORMAT_YUV422,
	DPU_LAYER_FORMAT_YUV420,
	DPU_LAYER_FORMAT_ARGB888,
	DPU_LAYER_FORMAT_RGB565,
	DPU_LAYER_FORMAT_AFBC,
	DPU_LAYER_FORMAT_MAX_TYPES,
};

static void dispc_layer_init(struct sprdfb_device *dev)
{
	uint32_t reg_val = 0;

	FB_PRINT("sprdfb:[%s]\n",__FUNCTION__);

	dispc_clear_bits((1<<0),DISPC_IMG_CTRL);
	dispc_clear_bits((1<<0),DISPC_OSD_CTRL);

	/******************* OSD layer setting **********************/

	/*enable OSD layer*/
	reg_val |= (1 << 0);

	/*disable  color key */

	/* alpha mode select  - block alpha*/
	reg_val |= (1 << 2);
#if defined(CONFIG_SPRD_SOC_SP9853I) || defined(CONFIG_SOC_PIKE2) || defined(CONFIG_SOC_SHARKLE) || defined(CONFIG_SOC_SHARKL3) || defined(CONFIG_SOC_ROC1) || defined(CONFIG_SOC_SHARKL5) || defined(CONFIG_SOC_SHARKL5PRO)
	if (panel_info.vl_bpix > 16)
		reg_val |= (DPU_LAYER_FORMAT_ARGB888 << 4);
	else
		reg_val |= (DPU_LAYER_FORMAT_RGB565 << 4);
	/* B0B1B2B3 */
	reg_val |= (0 << 8);
#else
	/* data format */
	/* RGB565 */
	reg_val |= (5 << 4);
	/* B2B3B0B1 */
	reg_val |= (2 << 8);
#endif

	dispc_write(reg_val, DISPC_OSD_CTRL);

	/* OSD layer alpha value */
	dispc_write(0xFF, DISPC_OSD_ALPHA);

	/* OSD layer size */
#ifdef CONFIG_FB_LOW_RES_SIMU
#ifndef CONFIG_SC8830
	if((0 != dev->panel->display_width)
	   && (0 != dev->panel->display_height)){
		reg_val = ( dev->panel->display_width& 0xfff)
			| ((dev->panel->display_height & 0xfff) << 16);
#else
	if((0 != dev->display_width) && (0 != dev->display_height)){
		reg_val = ( dev->display_width& 0xfff)
			| ((dev->display_height & 0xfff ) << 16);
#endif
	}else
 #endif
	reg_val = ( dev->panel->width& 0xfff)
		| ((dev->panel->height & 0xfff ) << 16);
	dispc_write(reg_val, DISPC_OSD_SIZE_XY);

	/* OSD layer start position */
	dispc_write(0, DISPC_OSD_DISP_XY);

	/* OSD layer pitch */
#ifdef CONFIG_FB_LOW_RES_SIMU
#ifndef CONFIG_SC8830

	if((0 != dev->panel->display_width) && (0 != dev->panel->display_height)){
		reg_val = ( dev->panel->display_width & 0xfff) ;
#else
	if((0 != dev->display_width) && (0 != dev->display_height)){
		reg_val = ( dev->display_width & 0xfff) ;

#endif
	}else
#endif
	reg_val = (dev->panel->width & 0xfff) ;
	dispc_write(reg_val, DISPC_OSD_PITCH);

	/*OSD base address*/
#if (defined(CONFIG_SOC_SHARKLJ1) || defined(CONFIG_SOC_SHARKLE) || defined(CONFIG_SOC_SHARKL3) || defined(CONFIG_SOC_ROC1) || defined(CONFIG_SOC_SHARKL5) || defined(CONFIG_SOC_SHARKL5PRO))
	dispc_write(dev->smem_start - 0x80000000, DISPC_OSD_BASE_ADDR);
#else
	dispc_write(dev->smem_start, DISPC_OSD_BASE_ADDR);
#endif
	/* OSD color_key value */
	dispc_set_osd_ck(0x0);

	/* DISPC workplane size */
	dispc_set_disp_size(dev);

	FB_PRINT("DISPC_OSD_CTRL: 0x%x\n", dispc_read(DISPC_OSD_CTRL));
	FB_PRINT("DISPC_OSD_ALPHA: 0x%x\n", dispc_read(DISPC_OSD_ALPHA));
	FB_PRINT("DISPC_OSD_SIZE_XY: 0x%x\n", dispc_read(DISPC_OSD_SIZE_XY));
	FB_PRINT("DISPC_OSD_DISP_XY: 0x%x\n", dispc_read(DISPC_OSD_DISP_XY));
	FB_PRINT("DISPC_OSD_PITCH: 0x%x\n", dispc_read(DISPC_OSD_PITCH));
	FB_PRINT("DISPC_OSD_BASE_ADDR: 0x%x\n", dispc_read(DISPC_OSD_BASE_ADDR));
}

static void dispc_update_clock(struct sprdfb_device *dev)
{
	uint32_t hpixels, vlines, need_clock, dividor;

	struct panel_spec* panel = dev->panel;
	struct info_mipi * mipi = panel->info.mipi;
	struct info_rgb* rgb = panel->info.rgb;

	FB_PRINT("sprdfb:[%s]\n", __FUNCTION__);

	if(0 == panel->fps){
		debugf("sprdfb: No panel->fps specified!\n");
		return;
	}

	if(LCD_MODE_DSI == dev->panel->type ){
		hpixels = panel->width + mipi->timing->hsync + mipi->timing->hbp + mipi->timing->hfp;
		vlines = panel->height + mipi->timing->vsync + mipi->timing->vbp + mipi->timing->vfp;
	} else if(LCD_MODE_RGB == dev->panel->type || dev->panel->type == LCD_MODE_LVDS){
		hpixels = panel->width + rgb->timing->hsync + rgb->timing->hbp + rgb->timing->hfp;
		vlines = panel->height + rgb->timing->vsync + rgb->timing->vbp + rgb->timing->vfp;
	} else{
		errorf("sprdfb:[%s] unexpected panel type!(%d)\n", __FUNCTION__, dev->panel->type);
		return;
	}

	need_clock = hpixels * vlines * panel->fps;
	dividor = SPRDFB_DPI_CLOCK_SRC/need_clock;
	if(SPRDFB_DPI_CLOCK_SRC - dividor*need_clock > (need_clock/2) ) {
		dividor += 1;
	}
	if((dividor<1) || (dividor > 0x100)){
		errorf("sprdfb:[%s]: Invliad dividor(%d)!Not update dpi clock!\n", __FUNCTION__, dividor);
		return;
	}

	dev->dpi_clock = SPRDFB_DPI_CLOCK_SRC / dividor;
	dispc_dpi_clk_set(DISPC_DPI_SEL_DEFAULT, (dividor-1));
	debugf("sprdfb:[%s] need_clock = %d, dividor = %d, dpi_clock = %d\n", __FUNCTION__, need_clock, dividor, dev->dpi_clock);
	dispc_print_clk();
}


#if defined(CONFIG_SPX15) || defined(CONFIG_SPX30G)
//#define GSP_IOMMU_WORKAROUND1
#endif

#ifdef GSP_IOMMU_WORKAROUND1

static void cycle_delay(uint32_t delay)
{
	while(delay--);
}

/*
func:gsp_iommu_workaround
desc:dolphin IOMMU workaround, configure GSP-IOMMU CTL REG before dispc_emc enable,
     including config IO base addr and enable gsp-iommu
warn:when dispc_emc disabled, reading ctl or entry register will hung up AHB bus .
     only 4-writting operations are allowed to exeute, over 4 ops will also hung uo AHB bus
     GSP module soft reset is not allowed , beacause it will clear gsp-iommu-ctrl register
*/
static void gsp_iommu_workaround(void)
{
	uint32_t emc_en_cfg = 0;
	uint32_t gsp_en_cfg = 0;
	#define REG_WRITE(reg,value)	(*(volatile uint32_t*)reg = value)
#ifdef CONFIG_SPX30G //tshark
	#define GSP_MMU_CTRL_BASE		(0x21408000)
#else//defined(CONFIG_SPX15) //dolphin
	#define GSP_MMU_CTRL_BASE		(0x21404000)
#endif

	emc_en_cfg = __raw_readl(DISPC_EMC_EN);
	gsp_en_cfg = __raw_readl(DISPC_AHB_EN);
	debugf("ytc:gsp_iommu_workaround: emc_eb_cfg:%x; gsp_eb_cfg:%x;\n", emc_en_cfg, gsp_en_cfg);
	REG_WRITE(DISPC_EMC_EN,emc_en_cfg & (~0x800)); // disable emc clk
	REG_WRITE(DISPC_AHB_EN,gsp_en_cfg | 0x8); // enable gsp
	cycle_delay(5); // delay for a while
	REG_WRITE(GSP_MMU_CTRL_BASE,0x10000001);//set iova base as 0x10000000, and enable gsp_iommu
	cycle_delay(5); // delay for a while
	debugf("ytc:gsp_iommu_workaround: %x, gsp_eb_cfg: %x\n", __raw_readl(DISPC_EMC_EN), __raw_readl(DISPC_AHB_EN));
	REG_WRITE(DISPC_AHB_EN,gsp_en_cfg); // restore gsp
	REG_WRITE(DISPC_EMC_EN,emc_en_cfg); // restore emc clk
}

#endif
static int32_t dispc_config_dsc_param(struct sprdfb_device *dev)
{
	uint32_t i;
	uint32_t dsc_ctrl = 0x0400;
	uint32_t dsc_regs_data[] = {
		/**
		* panel width is configured to 1440,
		* xmit delay is set to 475 and output bit is 8bit
		* slice width adn height:720,16
		* h/v porch > 0x20
		* */
		/*0x2000000b,
		0x0a0005a0,
		0x000000f0,
		0x07000f00,
		0x04604014,
		0x00a03205,
		0x306c81db, 0x000a0170, 0x04c50667, 0x12181800,
		0x003316b6, 0x382a1c0e, 0x69625446, 0x7b797770,
		0x00007e7d, 0x01000102, 0x09be0940, 0x19fa19fc,
		0x1a3819f8, 0x1ab61a78, 0x2b342af6, 0x3b742b74,
		0x00006bf4*/
		/**
		* panel width is configured to 1440,
		* xmit delay is set to 475 and output bit is 8bit
		* slice width adn height:720,16
		* h/v porch > 0x20
		* */
#ifdef CONFIG_SOC_IWHALE2
		0x2000010b,
#else
		0x2000000b,
#endif
		0x0a0005a0,
		0x000000f0,
		0x04096000,
		0x08204014,
		0x00800602,
		0x306c81db, 0x000ae4bd, 0x0008000a, 0x12181800,
		0x003316b6, 0x382a1c0e, 0x69625446, 0x7b797770,
		0x00007e7d, 0x01000102, 0x09be0940, 0x19fa19fc,
		0x1a3819f8, 0x1ab61a78, 0x2b342af6, 0x3b742b74,
		0x00006bf4
	};
	FB_PRINT("sprdfb:[%s] enter\n", __FUNCTION__);

	for(i=0; i < sizeof(dsc_regs_data)/sizeof(uint32_t); i++)
		dispc_write(dsc_regs_data[i], (dsc_ctrl + i*4));

	return 0;
}
static int32_t sprdfb_dispc_early_init(struct sprdfb_device *dev)
{
	FB_PRINT("sprdfb:[%s]\n", __FUNCTION__);

	dispc_early_configs();

#ifdef GSP_IOMMU_WORKAROUND1
	gsp_iommu_workaround();
#endif
	dispc_pll_clk_set(DISPC_PLL_SEL_DEFAULT, 0);
#if !(defined(CONFIG_SOC_IWHALE2) || defined(CONFIG_SPRD_SOC_SP9853I))
        dispc_dbi_clk_set(DISPC_DBI_SEL_DEFAULT, 0);
#endif
	dispc_dpi_clk_set(DISPC_DPI_SEL_DEFAULT, 0);

	dev->dpi_clock = SPRDFB_DPI_CLOCK_SRC / (DISPC_DPI_DIV_DEFAULT + 1);
#ifndef CONFIG_FPGA
	FB_PRINT("sprdfb:DISPC_PLL_SEL_CFG:0x%08x \n",__raw_readl(DISPC_PLL_SEL_CFG));
	FB_PRINT("sprdfb:DISPC_DPI_SEL_CFG:0x%08x \n",__raw_readl(DISPC_DPI_SEL_CFG));
	//FB_PRINT("sprdfb:REG_DISP_AHB_AHB_EB:%x \n",__raw_readl(REG_DISP_AHB_AHB_EB));
#endif
	dispc_reset();
	dispc_module_enable();
	is_first_frame = 1;

	return 0;
}


static int32_t sprdfb_dispc_init(struct sprdfb_device *dev)
{
	int32_t ret;
	struct panel_spec* panel = dev->panel;

	FB_PRINT("sprdfb:[%s]\n",__FUNCTION__);

	if (panel->is_need_dsc){
		ret = dispc_config_dsc_param(dev);
		if(ret) {
			FB_PRINT("sprdfb:dispc_config_dsc_param fail!\n");
			return -1;
		}
	}
#if !((defined(CONFIG_SOC_SHARKLE))|| (defined(CONFIG_SOC_SHARKLJ1)) || (defined(CONFIG_SC9833)) || (defined(CONFIG_SPRD_SOC_SP9853I)) || (defined(CONFIG_SOC_PIKE2)) || (defined(CONFIG_SOC_SHARKL3)) || (defined(CONFIG_SOC_ROC1)) || (defined(CONFIG_SOC_SHARKL5)) || (defined(CONFIG_SOC_SHARKL5PRO)))
	misc_noc_ctrl(REG_AON_APB_DISP_NOC_CTRL,
			dev->smem_start > 0x400000000 ? FULL_MODE : NORMAL_MODE,
			SIZE_64);
#endif
	/*set bg color*/
//	dispc_set_bg_color(0xFFFFFFFF);
	dispc_set_bg_color(0xFF);
#if !((defined(CONFIG_SOC_SHARKLE))||(defined(CONFIG_SOC_SHARKLJ1)) || (defined(CONFIG_SC9833)) || (defined(CONFIG_SPRD_SOC_SP9853I))|| (defined(CONFIG_SOC_PIKE2)) || (defined(CONFIG_SOC_SHARKL3)) || (defined(CONFIG_SOC_ROC1)) || (defined(CONFIG_SOC_SHARKL5)) || (defined(CONFIG_SOC_SHARKL5PRO)))
	/*enable dithering*/
	dispc_dithering_enable(1);
#endif
	/*use MSBs as img exp mode*/
	dispc_set_exp_mode(0x0);

	dispc_layer_init(dev);

//	dispc_update_clock(dev);

	if(SPRDFB_PANEL_IF_DPI == dev->panel_if_type){
		if(is_first_frame){
			/*set dpi register update only with SW*/
#if !((defined(CONFIG_SOC_SHARKLE))||(defined(CONFIG_SOC_SHARKLJ1)) || (defined(CONFIG_SC9833)) || (defined(CONFIG_SPRD_SOC_SP9853I)) || (defined(CONFIG_SOC_PIKE2)) || (defined(CONFIG_SOC_SHARKL3)) || (defined(CONFIG_SOC_ROC1)) || (defined(CONFIG_SOC_SHARKL5)) || (defined(CONFIG_SOC_SHARKL5PRO)))
			dispc_set_bits((1<<4), DISPC_DPI_CTRL);
#else
			dispc_set_bits((1<<4), DISPC_CTRL);
#endif
		}else{
			/*set dpi register update with SW & VSYNC*/
#if !((defined(CONFIG_SOC_SHARKLE))|| (defined(CONFIG_SOC_SHARKLJ1)) || (defined(CONFIG_SC9833)) || (defined(CONFIG_SPRD_SOC_SP9853I)) || (defined(CONFIG_SOC_PIKE2)) || (defined(CONFIG_SOC_SHARKL3)) || (defined(CONFIG_SOC_ROC1)) || (defined(CONFIG_SOC_SHARKL5)) || (defined(CONFIG_SOC_SHARKL5PRO)))
			dispc_clear_bits((1<<4), DISPC_DPI_CTRL);
#else
			dispc_clear_bits((1<<4), DISPC_CTRL);
#endif
		}
		/*enable dispc update done INT*/
//		dispc_write((1<<4), DISPC_INT_EN);
	}else{
		/* enable dispc DONE  INT*/
//		dispc_write((1<<0), DISPC_INT_EN);
	}
#if defined CONFIG_SC8830 || (defined CONFIG_SC9630)
		{/*for debug*/
			int32_t i;
			for(i=0x20800000;i<0x208000c0;i+=16){
				FB_PRINT("sprdfb: %x: 0x%x, 0x%x, 0x%x, 0x%x\n",
					 i, __raw_readl(i), __raw_readl(i+4),
					 __raw_readl(i+8), __raw_readl(i+12));
			}
			FB_PRINT("**************************************\n");
		}
#endif
	return 0;
}

static int32_t sprdfb_dispc_uninit(struct sprdfb_device *dev)
{
	FB_PRINT("sprdfb:[%s]\n",__FUNCTION__);

	__raw_bits_and(~(BIT_DISPC_AHB_EN), DISPC_AHB_EN);

	return 0;
}

static int32_t sprdfb_dispc_refresh (struct sprdfb_device *dev)
{
	uint32_t i;

	debugf("sprdfb:[%s]\n",__FUNCTION__);

	if(SPRDFB_PANEL_IF_DPI != dev->panel_if_type){
		sprdfb_panel_invalidate(dev->panel);
	}

	sprdfb_panel_before_refresh(dev);

	if(SPRDFB_PANEL_IF_DPI == dev->panel_if_type){
		/*dpi register update*/
#if !((defined(CONFIG_SOC_SHARKLE))|| (defined(CONFIG_SOC_SHARKLJ1)) || (defined(CONFIG_SC9833)) || (defined(CONFIG_SPRD_SOC_SP9853I)) || (defined(CONFIG_SOC_PIKE2)) || (defined(CONFIG_SOC_SHARKL3)) || (defined(CONFIG_SOC_ROC1)) || (defined(CONFIG_SOC_SHARKL5)))
		dispc_set_bits((1<<5), DISPC_DPI_CTRL);
#else
		dispc_set_bits((1<<5), DISPC_CTRL);
#endif
		if(is_first_frame){
			udelay(30);
			/*dpi register update with SW and VSync*/
#if !((defined(CONFIG_SOC_SHARKLE))|| (defined(CONFIG_SOC_SHARKLJ1)) || (defined(CONFIG_SC9833)) || (defined(CONFIG_SPRD_SOC_SP9853I)) || (defined(CONFIG_SOC_PIKE2)) || (defined(CONFIG_SOC_SHARKL3)) || (defined(CONFIG_SOC_ROC1)) || (defined(CONFIG_SOC_SHARKL5)))
			dispc_clear_bits((1<<4), DISPC_DPI_CTRL);
			/* start refresh */
			dispc_set_bits((1 << 4), DISPC_CTRL);
#else
			dispc_clear_bits((1<<4), DISPC_CTRL);
			/* start refresh */
			dispc_set_bits((1 << 0), DISPC_CTRL);
#endif
			is_first_frame = 0;
		}else{
			for(i=0;i<1000;i++){
				if(!(dispc_read(DISPC_INT_RAW) & (0x10))){
					udelay(100);
				}else{
					break;
				}
			}
			if(i >= 1000){
				errorf("sprdfb:[%s] wait dispc update  int time out!! (0x%x)\n", __FUNCTION__, dispc_read(DISPC_INT_RAW));
			}else{
				FB_PRINT("sprdfb:[%s] got dispc update int (0x%x)\n", __FUNCTION__, dispc_read(DISPC_INT_RAW));
			}
			dispc_set_bits((1<<5), DISPC_INT_CLR);
                   }
	}else{
		/* start refresh */
		dispc_set_bits((1 << 0), DISPC_CTRL);
		for(i=0;i<500;i++){
			if(0x1 != (dispc_read(DISPC_INT_RAW) & (1<<0))){
				udelay(1000);
			}else{
				break;
			}
		}
		if(i >= 1000){
			errorf("sprdfb:[%s] wait dispc done int time out!! (0x%x)\n", __FUNCTION__, dispc_read(DISPC_INT_RAW));
		}else{
			FB_PRINT("sprdfb:[%s] got dispc done int (0x%x)\n", __FUNCTION__, dispc_read(DISPC_INT_RAW));
		}
		dispc_set_bits((1<<0), DISPC_INT_CLR);
	}

	sprdfb_panel_after_refresh(dev);

	return 0;
}

struct display_ctrl sprdfb_dispc_ctrl = {
	.name		= "dispc",
	.early_init	= sprdfb_dispc_early_init,
	.init		= sprdfb_dispc_init,
	.uninit		= sprdfb_dispc_uninit,
	.refresh	= sprdfb_dispc_refresh,
	.update_clk     = dispc_update_clock,
};

