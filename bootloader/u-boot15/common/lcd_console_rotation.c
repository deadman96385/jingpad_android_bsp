/*
 * (C) Copyright 2015
 * Bernecker & Rainer Industrieelektronik GmbH - http://www.br-automation.com
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <lcd.h>
#include <video_font.h>		/* Get font data, width and height */

static u16 *dst16, *src16;
static u32 *dst32, *src32;
static int bpix = 32;
static int fg_color, bg_color;

#define LCD_PUTC_XY90(dst, pixel) \
do { \
	int col, i; \
	uchar msk = 0x80; \
	uchar *pfont = video_fontdata + c * VIDEO_FONT_HEIGHT; \
	dst = (pixel *)pcons->fbbase + (x+1) * pcons->lcdsizex - y; \
	for (col = 0; col < VIDEO_FONT_WIDTH; ++col) { \
		for (i = 0; i < VIDEO_FONT_HEIGHT; ++i) \
			*dst-- = (*(pfont + i) & msk) ? fg_color : bg_color; \
		msk >>= 1; \
		dst += (pcons->lcdsizex + VIDEO_FONT_HEIGHT); \
	} \
} while(0)

#define CONSOLE_SETROW90(dst, pixel) \
do { \
	int i, j; \
	dst = (pixel *)pcons->fbbase + pcons->lcdsizex - row*VIDEO_FONT_HEIGHT+1; \
	for (j = 0; j < pcons->lcdsizey; j++) { \
		for (i = 0; i < VIDEO_FONT_HEIGHT; i++) \
			*dst-- = clr; \
		dst += (pcons->lcdsizex + VIDEO_FONT_HEIGHT); \
	} \
} while(0)

#define CONSOLE_MOVEROW90(dst, src, pixel) \
do { \
	int i, j; \
	dst = (pixel *)pcons->fbbase + pcons->lcdsizex - (rowdst*VIDEO_FONT_HEIGHT+1); \
	src = (pixel *)pcons->fbbase + pcons->lcdsizex - (rowsrc*VIDEO_FONT_HEIGHT+1); \
	for (j = 0; j < pcons->lcdsizey; j++) { \
		for (i = 0; i < VIDEO_FONT_HEIGHT; i++) \
			*dst-- = *src--; \
		src += (pcons->lcdsizex + VIDEO_FONT_HEIGHT); \
		dst += (pcons->lcdsizex + VIDEO_FONT_HEIGHT); \
	} \
} while(0)

#define LCD_PUTC_XY180(dst, pixel) \
do { \
	int i, row; \
	uchar bits; \
	dst = (pixel *)pcons->fbbase + pcons->lcdsizex + pcons->lcdsizey * pcons->lcdsizex - y * pcons->lcdsizex - (x+1); \
	for (row = 0; row < VIDEO_FONT_HEIGHT; row++) { \
		bits = video_fontdata[c * VIDEO_FONT_HEIGHT + row]; \
		for (i = 0; i < VIDEO_FONT_WIDTH; ++i) { \
			*dst-- = (bits & 0x80) ? fg_color : bg_color; \
			bits <<= 1; \
		} \
		dst -= (pcons->lcdsizex - VIDEO_FONT_WIDTH); \
	} \
} while(0)

#define CONSOLE_SETROW180(dst, pixel) \
do { \
	int i; \
	dst = (pixel *)pcons->fbbase + (pcons->rows-row-1) * VIDEO_FONT_HEIGHT * pcons->lcdsizex; \
	for (i = 0; i < (VIDEO_FONT_HEIGHT * pcons->lcdsizex); i++) \
		*dst++ = clr; \
} while(0)

#define CONSOLE_MOVEROW180(dst, src, pixel) \
do { \
	int i; \
	dst = (pixel *)pcons->fbbase + (pcons->rows-rowdst-1) * VIDEO_FONT_HEIGHT * pcons->lcdsizex; \
	src = (pixel *)pcons->fbbase + (pcons->rows-rowsrc-1) * VIDEO_FONT_HEIGHT * pcons->lcdsizex; \
	for (i = 0; i < (VIDEO_FONT_HEIGHT * pcons->lcdsizex); i++) \
		*dst++ = *src++; \
} while(0)

#define LCD_PUTC_XY270(dst, pixel) \
do { \
	int i, col; \
	uchar msk = 0x80; \
	uchar *pfont = video_fontdata + c * VIDEO_FONT_HEIGHT; \
	dst = (pixel *)pcons->fbbase + pcons->lcdsizey * pcons->lcdsizex - (x+1) * pcons->lcdsizex + y; \
	for (col = 0; col < VIDEO_FONT_WIDTH; ++col) { \
		for (i = 0; i < VIDEO_FONT_HEIGHT; ++i) \
			*dst++ = (*(pfont + i) & msk) ? fg_color : bg_color; \
		msk >>= 1; \
		dst -= (pcons->lcdsizex + VIDEO_FONT_HEIGHT); \
	} \
} while(0)

#define CONSOLE_SETROW270(dst, pixel) \
do { \
	int i, j; \
	dst = (pixel *)pcons->fbbase + row*VIDEO_FONT_HEIGHT; \
	for (j = 0; j < pcons->lcdsizey; j++) { \
		for (i = 0; i < VIDEO_FONT_HEIGHT; i++) \
			*dst++ = clr; \
		dst += (pcons->lcdsizex - VIDEO_FONT_HEIGHT); \
	} \
} while(0)

#define CONSOLE_MOVEROW270(dst, src, pixel) \
do { \
	int i, j; \
	dst = (pixel *)pcons->fbbase + rowdst*VIDEO_FONT_HEIGHT; \
	src = (pixel *)pcons->fbbase + rowsrc*VIDEO_FONT_HEIGHT; \
	for (j = 0; j < pcons->lcdsizey; j++) { \
		for (i = 0; i < VIDEO_FONT_HEIGHT; i++) \
			*dst++ = *src++; \
		src += (pcons->lcdsizex - VIDEO_FONT_HEIGHT); \
		dst += (pcons->lcdsizex - VIDEO_FONT_HEIGHT); \
	} \
} while(0)


static void lcd_putc_xy90(struct console_t *pcons, ushort x, ushort y, char c)
{
	if (bpix > 16)
		LCD_PUTC_XY90(dst32, u32);
	else
		LCD_PUTC_XY90(dst16, u16);
}

static inline void console_setrow90(struct console_t *pcons, u32 row, int clr)
{
	if (bpix > 16)
		CONSOLE_SETROW90(dst32, u32);
	else
		CONSOLE_SETROW90(dst16, u16);
}

static inline void console_moverow90(struct console_t *pcons,
				      u32 rowdst, u32 rowsrc)
{
	if (bpix > 16)
		CONSOLE_MOVEROW90(dst32, src32, u32);
	else
		CONSOLE_MOVEROW90(dst16, src16, u16);
}

static void lcd_putc_xy180(struct console_t *pcons, ushort x, ushort y, char c)
{
	if (bpix > 16)
		LCD_PUTC_XY180(dst32, u32);
	else
		LCD_PUTC_XY180(dst16, u16);
}

static inline void console_setrow180(struct console_t *pcons, u32 row, int clr)
{
	if (bpix > 16)
		CONSOLE_SETROW180(dst32, u32);
	else
		CONSOLE_SETROW180(dst16, u16);
}

static inline void console_moverow180(struct console_t *pcons,
				      u32 rowdst, u32 rowsrc)
{
	if (bpix > 16)
		CONSOLE_MOVEROW180(dst32, src32, u32);
	else
		CONSOLE_MOVEROW180(dst16, src16, u16);
}

static void lcd_putc_xy270(struct console_t *pcons, ushort x, ushort y, char c)
{
	if (bpix > 16)
		LCD_PUTC_XY270(dst32, src32, u32);
	else
		LCD_PUTC_XY270(dst16, src16, u16);
}

static inline void console_setrow270(struct console_t *pcons, u32 row, int clr)
{
	if (bpix > 16)
		CONSOLE_SETROW270(dst32, u32);
	else
		CONSOLE_SETROW270(dst16, u16);
}

static inline void console_moverow270(struct console_t *pcons,
				     u32 rowdst, u32 rowsrc)
{
	if (bpix > 16)
		CONSOLE_MOVEROW270(dst32, src32, u32);
	else
		CONSOLE_MOVEROW270(dst16, src16, u16);
}

static void console_calc_rowcol_rot(struct console_t *pcons)
{
	if (pcons->lcdrot == 1 || pcons->lcdrot == 3)
		console_calc_rowcol(pcons, pcons->lcdsizey, pcons->lcdsizex);
	else
		console_calc_rowcol(pcons, pcons->lcdsizex, pcons->lcdsizey);
}

void lcd_init_console_rot(struct console_t *pcons)
{
	bpix = lcd_getbpix();
	fg_color = lcd_getfgcolor();
	bg_color = lcd_getbgcolor();

	if (pcons->lcdrot == 0) {
		return;
	} else if (pcons->lcdrot == 1) {
		pcons->fp_putc_xy = &lcd_putc_xy90;
		pcons->fp_console_moverow = &console_moverow90;
		pcons->fp_console_setrow = &console_setrow90;
	} else if (pcons->lcdrot == 2) {
		pcons->fp_putc_xy = &lcd_putc_xy180;
		pcons->fp_console_moverow = &console_moverow180;
		pcons->fp_console_setrow = &console_setrow180;
	} else if (pcons->lcdrot == 3) {
		pcons->fp_putc_xy = &lcd_putc_xy270;
		pcons->fp_console_moverow = &console_moverow270;
		pcons->fp_console_setrow = &console_setrow270;
	} else {
		printf("%s: invalid framebuffer rotation (%d)!\n",
		       __func__, pcons->lcdrot);
		return;
	}
	console_calc_rowcol_rot(pcons);
}
