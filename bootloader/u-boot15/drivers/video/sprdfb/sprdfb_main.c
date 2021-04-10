/******************************************************************************
 ** File Name:    sprdfb_main.h                                            *
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
#include <malloc.h>
#include <fdtdec.h>

#ifdef CONFIG_ROUND_CORNER_SUPPORT
#include "sprdfb_round_corner.h"
#endif

DECLARE_GLOBAL_DATA_PTR;

#define BMP_RESERVED_ADDR(p, sz) ((p) + ALIGN((sz), PAGE_SIZE))

extern int sprdfb_panel_probe(struct sprdfb_device *dev);
extern void sprdfb_panel_remove(struct sprdfb_device *dev);

#ifdef CONFIG_FB_SWDISPC
extern struct display_ctrl sprdfb_swdispc_ctrl;
#else
extern struct display_ctrl sprdfb_dispc_ctrl;
#endif
static struct sprdfb_device s_sprdfb_dev = {0};
static uint32_t lcd_id_to_kernel = 0;
static uint32_t lcd_width_to_kernel = 0;
static uint32_t lcd_hight_to_kernel = 0;
struct sprdfb_device *dev_cabc_bl =NULL;
static uint32_t lcd_adc_to_kernel = 0;
static int32_t is_lcd_enable = false;

uint32_t lcd_get_pixel_clock(void)
{
	return 0;
}

uint32_t lcd_get_bpix(void)
{
	return panel_info.vl_bpix;
}

void inline save_lcd_id_to_kernel(uint32_t id)
{
	lcd_id_to_kernel = id;
}

uint32_t inline load_lcd_id_to_kernel(void)
{
	return lcd_id_to_kernel;
}

void save_lcd_size_to_kernel(uint32_t width, uint32_t hight)
{
	lcd_width_to_kernel = width;
	lcd_hight_to_kernel = hight;
}

uint32_t load_lcd_width_to_kernel(void)
{
	return lcd_width_to_kernel;
}

uint32_t load_lcd_hight_to_kernel(void)
{
	return lcd_hight_to_kernel;
}

void save_lcd_adc_to_kernel(uint32_t id)
{
	lcd_adc_to_kernel = id;
}

uint32_t load_lcd_adc_to_kernel(void)
{
	return lcd_adc_to_kernel;
}

void *lcd_get_base_addr(void *lcd_base)
{
	return gd->fb_base;
}

static int real_refresh(struct sprdfb_device *dev)
{
	int32_t ret;

	FB_PRINT("sprdfb: [%s]\n", __FUNCTION__);

	if(NULL == dev->panel){
		errorf("sprdfb: [%s] fail (no panel!)\n", __FUNCTION__);
		return -1;
	}

	ret = dev->ctrl->refresh(dev);
	if (ret) {
		errorf("sprdfb: failed to refresh !!!!\n");
		return -1;
	}

	return 0;
}

static int sprdfb_probe(void *lcdbase)
{
	struct sprdfb_device *dev = &s_sprdfb_dev;
	const void *fdt_blob = gd->fdt_blob;
	int nodeoffset = fdt_path_offset(fdt_blob, "/ion");
	int phandle = 0;
	unsigned long base, size;


	debugf("sprdfb:[%s]\n", __FUNCTION__);
#ifndef CONFIG_ZEBU
	set_backlight(0);
#endif

#ifdef CONFIG_FB_SWDISPC
		dev->ctrl = &sprdfb_swdispc_ctrl;
#else
		dev->ctrl = &sprdfb_dispc_ctrl;
#endif
	if(dev->ctrl->early_init)
		dev->ctrl->early_init(dev);

	if (0 != sprdfb_panel_probe(dev)) {
		sprdfb_panel_remove(dev);
		if(dev->ctrl->uninit)
			dev->ctrl->uninit(dev);
		errorf("sprdfb: failed to probe\n");
		return -EFAULT;
	}

#ifdef CONFIG_FB_LOW_RES_SIMU
#if (defined LCD_DISPLAY_WIDTH) && (defined LCD_DISPLAY_HEIGHT)
	dev->display_width = LCD_DISPLAY_WIDTH;
	dev->display_height = LCD_DISPLAY_HEIGHT;
#else
	dev->display_width = dev->panel->width;
	dev->display_height = dev->panel->height;
#endif
#endif
	debugf("ion node offset = %d\n", nodeoffset);
	if (nodeoffset == -FDT_ERR_NOTFOUND)
		return -1;

	nodeoffset = fdt_subnode_offset(fdt_blob, nodeoffset, "heap@3");
	debugf("heap3 node offset = %d\n", nodeoffset);
	if (nodeoffset == -FDT_ERR_NOTFOUND)
		return -1;

	phandle = fdtdec_lookup_phandle(fdt_blob, nodeoffset, "memory-region");
	debugf("memory-region phandle = %d\n", phandle);
	if (phandle == -FDT_ERR_NOTFOUND)
		return -1;

	if (fdtdec_decode_region(fdt_blob, phandle, "reg", &base, &size)) {
		errorf("Failed to decode reg property \n");
		return -EINVAL;
	}
#ifdef CONFIG_SPRD_SOC_SP9853I
	gd->fb_base = base + (size / 4) * 2;
#else
	gd->fb_base = base + (size / 3) * 2;
#endif
	dev->smem_start = gd->fb_base;
	if(dev->ctrl->init)
		dev->ctrl->init(dev);
	dev_cabc_bl = dev;
	debugf("sprdfb:[%s]---\n", __FUNCTION__);
	return 0;
}

void lcd_disable(void)
{
	debugf("sprdfb: [%s]\n", __FUNCTION__);
	sprdfb_panel_remove(&s_sprdfb_dev);
	if(s_sprdfb_dev.ctrl->uninit)
		s_sprdfb_dev.ctrl->uninit(&s_sprdfb_dev);
}

#ifdef CONFIG_FB_SWDISPC
void lcd_refresh(void *base)
{
	if(!is_lcd_enable)
		return ;
	sprdfb_spi_flip(base);
}
#endif

void lcd_enable(void)
{
#ifdef CONFIG_ROUND_CORNER_SUPPORT
	struct sprdfb_device *dev = &s_sprdfb_dev;
	dispc_logo_show_corner(dev->panel->height, dev->panel->width, gd->fb_base);
	lcd_set_flush_dcache(TRUE);
	lcd_sync();
	debugf("dispc_logo_show_corner\n");
#endif
	debugf("sprdfb: [%s]\n", __FUNCTION__);
	real_refresh(&s_sprdfb_dev);
	is_lcd_enable = true;
}


void lcd_ctrl_init(void *lcdbase)
{
	int size;
	void *bmp;
	char *s;
	ulong addr;
	u32 bmp_header_size = 8192;

	sprdfb_probe(lcdbase);
	size = lcd_get_size(&lcd_line_length);
	size += bmp_header_size;
	bmp = malloc(size);
	if (!bmp) {
		errorf("sprdfb: %s: failed to alloc bmp space\n", __FUNCTION__);
		return;
	}
	setenv_hex("splashimage", (ulong)bmp);
	s = getenv("splashimage");
	if(s == NULL){
		errorf("sprdfb: splashimage addr is NULL\n");
		setenv("splashimage",NULL);
		free(bmp);
		return;
	}
	addr = simple_strtoul(s, NULL, 16);
	debugf("sprdfb: splashimage addr is 0x%p, fb size is 0x%x\n",
			(void *)addr, size);
	lcd_set_flush_dcache(TRUE);
	debugf("sprdfb:[%s]---\n", __FUNCTION__);
}

#ifdef CONFIG_LCD_INFO
#include <nand.h>
extern nand_info_t nand_info[];

void lcd_show_board_info(void)
{
    ulong dram_size, nand_size;
    int i;
    char temp[32];

    dram_size = 0;
    for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++)
      dram_size += gd->bd->bi_dram[i].size;
    nand_size = 0;
    for (i = 0; i < CONFIG_SYS_MAX_NAND_DEVICE; i++)
      nand_size += nand_info[i].size;

    lcd_printf("\n%s\n", U_BOOT_VERSION);
    lcd_printf("  %ld MB SDRAM, %ld MB NAND\n",
                dram_size >> 20,
                nand_size >> 20 );
    lcd_printf("  Board            : esd ARM9 \n");
    lcd_printf("  Mach-type        : %lu\n", gd->bd->bi_arch_number);
}
#endif /* CONFIG_LCD_INFO */

/* dummy function */
void lcd_setcolreg(ushort regno, ushort red, ushort green, ushort blue)
{
	return;
}

int32_t sprdfb_spi_refresh(struct sprdfb_device *dev)
{
	if(!dev->panel)
	{
		printf("sprdfb:sprdfb_refresh dev->panel is null\n");
		return -1;
	}
	dev->panel->ops->panel_invalidate(dev->panel);
	dev->panel->ops->panel_refresh(dev->panel,dev->smem_start);
	return 0;
}

int32_t sprdfb_spi_flip(void *base)
{
        struct sprdfb_device * dev = &s_sprdfb_dev;
        if(!dev->panel)
        {
                printf("sprdfb:sprdfb_refresh dev->panel is null\n");
                return -1;
        }
        dev->panel->ops->panel_invalidate(dev->panel);
        dev->panel->ops->panel_refresh(dev->panel,base);
        return 0;
}

