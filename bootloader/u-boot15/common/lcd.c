/*
 * Common LCD routines
 *
 * (C) Copyright 2001-2002
 * Wolfgang Denk, DENX Software Engineering -- wd@denx.de
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/* #define DEBUG */
#include <config.h>
#include <common.h>
#include <command.h>
#include <env_callback.h>
#include <linux/types.h>
#include <stdio_dev.h>
#include <lcd.h>
#include <mapmem.h>
#include <watchdog.h>
#include <asm/unaligned.h>
#include <splash.h>
#include <asm/io.h>
#include <asm/unaligned.h>
#include <video_font.h>
#include "loader_common.h"

#ifdef CONFIG_LCD_LOGO
#include <bmp_logo.h>
#include <bmp_logo_data.h>
#if (CONSOLE_COLOR_WHITE >= BMP_LOGO_OFFSET)
#error Default Color Map overlaps with Logo Color Map
#endif
#endif

#ifdef CONFIG_SANDBOX
#include <asm/sdl.h>
#endif

#ifndef CONFIG_LCD_ALIGNMENT
#define CONFIG_LCD_ALIGNMENT PAGE_SIZE
#endif

#define RGB565_TO_INT16(rgb)  (rgb.blue >> 3 | rgb.green >> 2 << 5 | rgb.red >> 3 << 11)
#define PIXEL8_TO_INT16(index, table) 	(table[*index])
#define PIXEL16_TO_INT16(index, table)  (RGB565_TO_INT16(PIXEL8_TO_INT16(index, table)))
#define RGB16_TO_INT16(rgb)   (*rgb)
#define RGB24_TO_INT32(rgb)   (rgb->b | rgb->g << 8 | rgb->r << 16 | 0xff << 24)
#define RGB32_TO_INT32(rgb)   (rgb->b | rgb->g << 8 | rgb->r << 16 | rgb->a << 24)

#define BMP_TO_FB(dst, bits0, from, bits1, format, ...) \
do { \
	int i, j; \
	dst = (bits0 *)fb; \
	from = (bits1 *)bmap; \
	for (i = 0; i < height; ++i) { \
		for (j = 0; j < width; j++) { \
			*dst = format(from, ##__VA_ARGS__); \
			from++; \
			dst++; \
		} \
		from += bmp_width; \
		dst -= fb_width; \
	} \
} while(0)

#ifdef CONFIG_SC2703_LCD_POWERON
extern void lcd_use_sc2703l_to_power_on();
#endif

DECLARE_GLOBAL_DATA_PTR;

static int lcd_init(void *lcdbase);
static void lcd_logo(void);
static void lcd_setfgcolor(int color);
static void lcd_setbgcolor(int color);
#ifdef CONFIG_FB_SWDISPC
extern void lcd_refresh(void *base);
#endif

static int lcd_color_fg;
static int lcd_color_bg;
int lcd_line_length;
char lcd_is_enabled = 0;
static void *lcd_base;			/* Start of framebuffer memory	*/
static char lcd_flush_dcache;	/* 1 to flush dcache after each lcd update */

static uint16_t colormap[256];
__weak vidinfo_t panel_info = {
	.vl_bpix = 8,
	.cmap = colormap,
};

/* Flush LCD activity to the caches */
void lcd_sync(void)
{
	/*
	 * flush_dcache_range() is declared in common.h but it seems that some
	 * architectures do not actually implement it. Is there a way to find
	 * out whether it exists? For now, ARM is safe.
	 */
#if (defined(CONFIG_ARM) || defined(CONFIG_X86)) && !defined(CONFIG_SYS_DCACHE_OFF)
	int line_length;
	lcd_get_size(&line_length);

	if (lcd_flush_dcache)
		flush_dcache_range(lcd_base,
			(lcd_base + line_length * panel_info.vl_row));
#elif defined(CONFIG_SANDBOX) && defined(CONFIG_VIDEO_SANDBOX_SDL)
	static ulong last_sync;

	if (get_timer(last_sync) > 10) {
		sandbox_sdl_sync(lcd_base);
		last_sync = get_timer(0);
	}
#endif

#ifdef CONFIG_FB_SWDISPC
	lcd_refresh(lcd_base);
#endif

}

void lcd_set_flush_dcache(int flush)
{
	lcd_flush_dcache = (flush != 0);
}

static void lcd_stub_putc(struct stdio_dev *dev, const char c)
{
	lcd_putc(c);
}

static void lcd_stub_puts(struct stdio_dev *dev, const char *s)
{
	lcd_puts(s);
}

/* Small utility to check that you got the colours right */
#ifdef LCD_TEST_PATTERN

#define	N_BLK_VERT	2
#define	N_BLK_HOR	3

static int test_colors[N_BLK_HOR * N_BLK_VERT] = {
	CONSOLE_COLOR_RED,	CONSOLE_COLOR_GREEN,	CONSOLE_COLOR_YELLOW,
	CONSOLE_COLOR_BLUE,	CONSOLE_COLOR_MAGENTA,	CONSOLE_COLOR_CYAN,
};

static void test_pattern(void)
{
	ushort v_max  = panel_info.vl_row;
	ushort h_max  = panel_info.vl_col;
	ushort v_step = (v_max + N_BLK_VERT - 1) / N_BLK_VERT;
	ushort h_step = (h_max + N_BLK_HOR  - 1) / N_BLK_HOR;
	ushort v, h;
	uchar *pix = (uchar *)lcd_base;

	printf("[LCD] Test Pattern: %d x %d [%d x %d]\n",
		h_max, v_max, h_step, v_step);

	/* WARNING: Code silently assumes 8bit/pixel */
	for (v = 0; v < v_max; ++v) {
		uchar iy = v / v_step;
		for (h = 0; h < h_max; ++h) {
			uchar ix = N_BLK_HOR * iy + h / h_step;
			*pix++ = test_colors[ix];
		}
	}
}
#endif /* LCD_TEST_PATTERN */

/*
 * With most lcd drivers the line length is set up
 * by calculating it from panel_info parameters. Some
 * drivers need to calculate the line length differently,
 * so make the function weak to allow overriding it.
 */
__weak int lcd_get_size(int *line_length)
{
	int bpp = panel_info.vl_bpix >> 3;

	/* DPU support ARGB8888(4Byte) and RGB565(2Byte) */
	*line_length = (bpp > 2 ? 4 : 2) * panel_info.vl_col;
	return panel_info.vl_col * panel_info.vl_row * bpp;
}

/* dummy function */
__weak void lcd_setcolreg(ushort regno, ushort red, ushort green, ushort blue) {}

int drv_lcd_init(void)
{
	struct stdio_dev lcddev;
	int rc;

	/* if lcd is enabled, no need to init it again*/
	if (lcd_is_enabled)
		return 0;

#ifdef CONFIG_SC2703_LCD_POWERON
	lcd_use_sc2703l_to_power_on();
#endif

	lcd_base = map_sysmem(gd->fb_base, 0);

	lcd_init(lcd_base);

	/* Device initialization */
	memset(&lcddev, 0, sizeof(lcddev));

	strcpy(lcddev.name, "lcd");
	lcddev.ext   = 0;			/* No extensions */
	lcddev.flags = DEV_FLAGS_OUTPUT;	/* Output only */
	lcddev.putc  = lcd_stub_putc;		/* 'putc' function */
	lcddev.puts  = lcd_stub_puts;		/* 'puts' function */

	rc = stdio_register(&lcddev);

	return (rc == 0) ? 1 : rc;
}

void lcd_clear(void)
{
	int bg_color;
	char *s;
	ulong addr;
	static int do_splash = 1;
	u32 *ppix = lcd_base;
	u32 i;

#if LCD_BPP == LCD_COLOR8
	/* Setting the palette */
	lcd_setcolreg(CONSOLE_COLOR_BLACK, 0, 0, 0);
	lcd_setcolreg(CONSOLE_COLOR_RED, 0xFF, 0, 0);
	lcd_setcolreg(CONSOLE_COLOR_GREEN, 0, 0xFF, 0);
	lcd_setcolreg(CONSOLE_COLOR_YELLOW, 0xFF, 0xFF, 0);
	lcd_setcolreg(CONSOLE_COLOR_BLUE, 0, 0, 0xFF);
	lcd_setcolreg(CONSOLE_COLOR_MAGENTA, 0xFF, 0, 0xFF);
	lcd_setcolreg(CONSOLE_COLOR_CYAN, 0, 0xFF, 0xFF);
	lcd_setcolreg(CONSOLE_COLOR_GREY, 0xAA, 0xAA, 0xAA);
	lcd_setcolreg(CONSOLE_COLOR_WHITE, 0xFF, 0xFF, 0xFF);
#endif

#ifndef CONFIG_SYS_WHITE_ON_BLACK
	lcd_setfgcolor(CONSOLE_COLOR_BLACK2);
	lcd_setbgcolor(CONSOLE_COLOR_WHITE2);
	bg_color = CONSOLE_COLOR_WHITE2;
#else
	lcd_setfgcolor(CONSOLE_COLOR_WHITE2);
	lcd_setbgcolor(CONSOLE_COLOR_BLACK2);
	bg_color = CONSOLE_COLOR_BLACK2;
#endif	/* CONFIG_SYS_WHITE_ON_BLACK */

#ifdef	LCD_TEST_PATTERN
	test_pattern();
#else
	/* set framebuffer to background color */
	if (panel_info.vl_bpix <= 16)
		memset((char *)lcd_base, bg_color, lcd_line_length * panel_info.vl_row);
	else {
		for (i = 0; i < panel_info.vl_col * panel_info.vl_row; i++)
			*ppix++ = bg_color;
	}
#endif
	/* setup text-console */
	debug("[LCD] setting up console...\n");
	lcd_init_console(lcd_base,
			 panel_info.vl_col,
			 panel_info.vl_row,
			 panel_info.vl_rot);
}

static int do_lcd_clear(cmd_tbl_t *cmdtp, int flag, int argc,
			char *const argv[])
{
	lcd_clear();
	return 0;
}
U_BOOT_CMD(cls,	1, 1, do_lcd_clear, "clear screen", "");

static int lcd_init(void *lcdbase)
{
	//lcdbase will be probed from dts in lcd_ctrl_init, the value here is not correct
	/* Get logo bits/pixel, initialize panel_info.vl_bpix */
	splash_get_bpix(LOGO_PART);
	//debug("[LCD] Initializing LCD frambuffer at %p\n", lcdbase);
	lcd_ctrl_init(lcdbase);

	/*
	 * lcd_ctrl_init() of some drivers (i.e. bcm2835 on rpi) ignores
	 * the 'lcdbase' argument and uses custom lcd base address
	 * by setting up gd->fb_base. Check for this condition and fixup
	 * 'lcd_base' address.
	 */
	if (map_to_sysmem(lcdbase) != gd->fb_base)
		lcd_base = map_sysmem(gd->fb_base, 0);

	debug("[LCD] Using LCD frambuffer at %p\n", lcd_base);

	lcd_get_size(&lcd_line_length);
	lcd_is_enabled = 1;
	lcd_clear();

	/* Initialize the console */
	lcd_set_col(0);
#ifdef CONFIG_LCD_INFO_BELOW_LOGO
	lcd_set_row(7 + BMP_LOGO_HEIGHT / VIDEO_FONT_HEIGHT);
#else
	lcd_set_row(1);	/* leave 1 blank line below logo */
#endif

	return 0;
}

/*
 * This is called early in the system initialization to grab memory
 * for the LCD controller.
 * Returns new address for monitor, after reserving LCD buffer memory
 *
 * Note that this is running from ROM, so no write access to global data.
 */
ulong lcd_setmem(ulong addr)
{
	ulong size;
	int line_length;

	debug("LCD panel info: %d x %d, %d bit/pix\n", panel_info.vl_col,
		panel_info.vl_row, panel_info.vl_bpix);

	lcd_get_size(&line_length);
	size = line_length * panel_info.vl_row;

	/* Round up to nearest full page, or MMU section if defined */
	size = ALIGN(size, CONFIG_LCD_ALIGNMENT);
	addr = ALIGN(addr - CONFIG_LCD_ALIGNMENT + 1, CONFIG_LCD_ALIGNMENT);

	/* Allocate pages for the frame buffer. */
	addr -= size;

	debug("Reserving %ldk for LCD Framebuffer at: %08lx\n",
	      size >> 10, addr);

	return addr;
}

static void lcd_setfgcolor(int color)
{
	lcd_color_fg = color;
}

int lcd_getfgcolor(void)
{
	return lcd_color_fg;
}

static void lcd_setbgcolor(int color)
{
	lcd_color_bg = color;
}

int lcd_getbgcolor(void)
{
	return lcd_color_bg;
}

int lcd_getbpix(void)
{
	return panel_info.vl_bpix;
}

#ifdef CONFIG_LCD_LOGO
__weak void lcd_logo_set_cmap(void)
{
	int i;
	ushort *cmap = configuration_get_cmap();

	for (i = 0; i < ARRAY_SIZE(bmp_logo_palette); ++i)
		*cmap++ = bmp_logo_palette[i];
}

void lcd_logo_plot(int x, int y)
{
	ushort i, j;
	uchar *bmap = &bmp_logo_bitmap[0];
	unsigned bpix = panel_info.vl_bpix;
	uchar *fb = (uchar *)(lcd_base + y * lcd_line_length +
				x * lcd_line_length / panel_info.vl_col);
	ushort *fb16;

	debug("Logo: width %d  height %d  colors %d\n",
	      BMP_LOGO_WIDTH, BMP_LOGO_HEIGHT, BMP_LOGO_COLORS);

	if (bpix < 12) {
		WATCHDOG_RESET();
		lcd_logo_set_cmap();
		WATCHDOG_RESET();

		for (i = 0; i < BMP_LOGO_HEIGHT; ++i) {
			memcpy(fb, bmap, BMP_LOGO_WIDTH);
			bmap += BMP_LOGO_WIDTH;
			fb += panel_info.vl_col;
		}
	}
	else { /* true color mode */
		u16 col16;
		fb16 = (ushort *)fb;
		for (i = 0; i < BMP_LOGO_HEIGHT; ++i) {
			for (j = 0; j < BMP_LOGO_WIDTH; j++) {
				col16 = bmp_logo_palette[(bmap[j]-16)];
				fb16[j] =
					((col16 & 0x000F) << 1) |
					((col16 & 0x00F0) << 3) |
					((col16 & 0x0F00) << 4);
				}
			bmap += BMP_LOGO_WIDTH;
			fb16 += panel_info.vl_col;
		}
	}

	WATCHDOG_RESET();
	lcd_sync();
}
#else
static inline void lcd_logo_plot(int x, int y) {}
#endif /* CONFIG_LCD_LOGO */

#if defined(CONFIG_CMD_BMP) || defined(CONFIG_SPLASH_SCREEN)
#ifdef CONFIG_SPLASH_SCREEN_ALIGN
#define BMP_ALIGN_CENTER	0x7FFF

static void splash_align_axis(int *axis, unsigned long panel_size,
					unsigned long picture_size)
{
	unsigned long panel_picture_delta = panel_size - picture_size;
	unsigned long axis_alignment;

	if (*axis == BMP_ALIGN_CENTER)
		axis_alignment = panel_picture_delta / 2;
	else if (*axis < 0)
		axis_alignment = panel_picture_delta + *axis + 1;
	else
		return;

	*axis = max(0, (int)axis_alignment);
}
#endif

#ifdef CONFIG_LCD_BMP_RLE8
#define BMP_RLE8_ESCAPE		0
#define BMP_RLE8_EOL		0
#define BMP_RLE8_EOBMP		1
#define BMP_RLE8_DELTA		2

static void draw_unencoded_bitmap(ushort **fbp, uchar *bmap, ushort *cmap,
				  int cnt)
{
	while (cnt > 0) {
		*(*fbp)++ = cmap[*bmap++];
		cnt--;
	}
}

static void draw_encoded_bitmap(ushort **fbp, ushort c, int cnt)
{
	ushort *fb = *fbp;
	int cnt_8copy = cnt >> 3;

	cnt -= cnt_8copy << 3;
	while (cnt_8copy > 0) {
		*fb++ = c;
		*fb++ = c;
		*fb++ = c;
		*fb++ = c;
		*fb++ = c;
		*fb++ = c;
		*fb++ = c;
		*fb++ = c;
		cnt_8copy--;
	}
	while (cnt > 0) {
		*fb++ = c;
		cnt--;
	}
	*fbp = fb;
}

/*
 * Do not call this function directly, must be called from lcd_display_bitmap.
 */
static void lcd_display_rle8_bitmap(struct bmp_image *bmp, ushort *cmap,
				    uchar *fb, int x_off, int y_off)
{
	uchar *bmap;
	ulong width, height;
	ulong cnt, runlen;
	int x, y;
	int decode = 1;

	width = get_unaligned_le32(&bmp->header.width);
	height = get_unaligned_le32(&bmp->header.height);
	bmap = (uchar *)bmp + get_unaligned_le32(&bmp->header.data_offset);

	x = 0;
	y = height - 1;

	while (decode) {
		if (bmap[0] == BMP_RLE8_ESCAPE) {
			switch (bmap[1]) {
			case BMP_RLE8_EOL:
				/* end of line */
				bmap += 2;
				x = 0;
				y--;
				/* 16bpix, 2-byte per pixel, width should *2 */
				fb -= (width * 2 + lcd_line_length);
				break;
			case BMP_RLE8_EOBMP:
				/* end of bitmap */
				decode = 0;
				break;
			case BMP_RLE8_DELTA:
				/* delta run */
				x += bmap[2];
				y -= bmap[3];
				/* 16bpix, 2-byte per pixel, x should *2 */
				fb = (uchar *) (lcd_base + (y + y_off - 1)
					* lcd_line_length + (x + x_off) * 2);
				bmap += 4;
				break;
			default:
				/* unencoded run */
				runlen = bmap[1];
				bmap += 2;
				if (y < height) {
					if (x < width) {
						if (x + runlen > width)
							cnt = width - x;
						else
							cnt = runlen;
						draw_unencoded_bitmap(
							(ushort **)&fb,
							bmap, cmap, cnt);
					}
					x += runlen;
				}
				bmap += runlen;
				if (runlen & 1)
					bmap++;
			}
		} else {
			/* encoded run */
			if (y < height) {
				runlen = bmap[0];
				if (x < width) {
					/* aggregate the same code */
					while (bmap[0] == 0xff &&
					       bmap[2] != BMP_RLE8_ESCAPE &&
					       bmap[1] == bmap[3]) {
						runlen += bmap[2];
						bmap += 2;
					}
					if (x + runlen > width)
						cnt = width - x;
					else
						cnt = runlen;
					draw_encoded_bitmap((ushort **)&fb,
						cmap[bmap[1]], cnt);
				}
				x += runlen;
			}
			bmap += 2;
		}
	}
}
#endif

__weak void fb_put_byte(uchar **fb, uchar **from)
{
	*(*fb)++ = *(*from)++;
}

__weak void fb_put_word(uchar **fb, uchar **from)
{
	*(*fb)++ = *(*from)++;
	*(*fb)++ = *(*from)++;
}

__weak void lcd_set_cmap(struct bmp_image *bmp, unsigned colors)
{
	int i;
	struct bmp_color_table_entry cte;
	ushort *cmap = configuration_get_cmap();

	for (i = 0; i < colors; ++i) {
		cte = bmp->color_table[i];
		*cmap = (((cte.red)   << 8) & 0xf800) |
			(((cte.green) << 3) & 0x07e0) |
			(((cte.blue)  >> 3) & 0x001f);
#if defined(CONFIG_MPC823)
		cmap--;
#else
		cmap++;
#endif
	}
}

int lcd_display_bitmap(ulong bmp_image, int x, int y)
{
	u8 bmp_bpix;
	u16 width, height, bmp_width, fb_width, hdr_size;
	u32 colors;
	u8 *fb, *bmap, *bmap8;
	u16 *fb16, *bmap16, *cmap_base = NULL;
	u32 *fb32;
	rgb24_t *bmap24;
	rgb32_t *bmap32;
	struct bmp_image *bmp = (struct bmp_image *)map_sysmem(bmp_image, 0);
	struct bmp_color_table_entry *palette = bmp->color_table;

	if (!bmp || !(bmp->header.signature[0] == 'B' &&
		bmp->header.signature[1] == 'M')) {
		printf("Error: no valid bmp image at %lx\n", bmp_image);

		return 1;
	}

	width = get_unaligned_le32(&bmp->header.width);
	height = get_unaligned_le32(&bmp->header.height);
	bmp_bpix = get_unaligned_le16(&bmp->header.bit_count);
	hdr_size = get_unaligned_le16(&bmp->header.size);
	debug("hdr_size=%d, bmp_bpix=%d\n", hdr_size, bmp_bpix);

	/*
	 * We support displaying 8bpp BMPs on 16bpp LCDs
	 * and displaying 24bpp BMPs on 32bpp LCDs
	 * */
	if (bmp_bpix != 8 && bmp_bpix != 16 && bmp_bpix != 24 && bmp_bpix != 32) {
		printf ("Error: BMP %d bit/pixel mode not support!\n", bmp_bpix);

		return 1;
	}

	colors = 1 << bmp_bpix;
	debug("Display-bmp: %d x %d  with %d colors, bpix: %d\n",
	      width, height, colors, bmp_bpix);

	if (bmp_bpix == 8)
		lcd_set_cmap(bmp, colors);

#ifdef CONFIG_SPLASH_SCREEN_ALIGN
	splash_align_axis(&x, panel_info.vl_col, width);
	splash_align_axis(&y, panel_info.vl_row, height);
#endif /* CONFIG_SPLASH_SCREEN_ALIGN */

	if ((x + width) > panel_info.vl_col)
		width = panel_info.vl_col - x;
	if ((y + height) > panel_info.vl_row)
		height = panel_info.vl_row - y;

	bmap = (uchar *)bmp + get_unaligned_le32(&bmp->header.data_offset);
	fb   = (uchar *)(lcd_base + (y + height - 1) * lcd_line_length +
			x * (lcd_line_length / panel_info.vl_col));

	bmp_width = (width & 0x3 ? (width & ~0x3) + 4 : width) - width;
	fb_width = lcd_line_length / (bmp_bpix > 16 ? 4 : 2) + width;

	switch (bmp_bpix) {
	case 1:
	case 8:
		cmap_base = configuration_get_cmap();
#ifdef CONFIG_LCD_BMP_RLE8
		u32 compression = get_unaligned_le32(&bmp->header.compression);
		debug("compressed %d %d\n", compression, BMP_BI_RLE8);
		if (compression == BMP_BI_RLE8) {
			lcd_display_rle8_bitmap(bmp, cmap_base, fb, x, y);
			break;
		}
#endif
		if (cmap_base)
			BMP_TO_FB(fb16, u16, bmap8, u8, PIXEL8_TO_INT16, cmap_base);
		else
			BMP_TO_FB(fb16, u16, bmap8, u8, PIXEL16_TO_INT16, palette);
		break;
	case 16:
		BMP_TO_FB(fb16, u16, bmap16, u16, RGB16_TO_INT16);
		break;
	case 24:
		BMP_TO_FB(fb32, u32, bmap24, rgb24_t, RGB24_TO_INT32);
		break;
	case 32:
		BMP_TO_FB(fb32, u32, bmap32, rgb32_t, RGB32_TO_INT32);
		break;
	default:
		break;
	};

	lcd_sync();
	return 0;
}
#endif

static void lcd_logo(void)
{
	lcd_logo_plot(0, 0);

#ifdef CONFIG_LCD_INFO
	lcd_set_col(LCD_INFO_X / VIDEO_FONT_WIDTH);
	lcd_set_row(LCD_INFO_Y / VIDEO_FONT_HEIGHT);
	lcd_show_board_info();
#endif /* CONFIG_LCD_INFO */
}

#ifdef CONFIG_SPLASHIMAGE_GUARD
static int on_splashimage(const char *name, const char *value, enum env_op op,
	int flags)
{
	ulong addr;
	int aligned;

	if (op == env_op_delete)
		return 0;

	addr = simple_strtoul(value, NULL, 16);
	/* See README.displaying-bmps */
	aligned = (addr % 4 == 2);
	if (!aligned) {
		printf("Invalid splashimage value. Value must be 16 bit aligned, but not 32 bit aligned\n");
		return -1;
	}

	return 0;
}

U_BOOT_ENV_CALLBACK(splashimage, on_splashimage);
#endif

int lcd_get_pixel_width(void)
{
	return panel_info.vl_col;
}

int lcd_get_pixel_height(void)
{
	return panel_info.vl_row;
}
