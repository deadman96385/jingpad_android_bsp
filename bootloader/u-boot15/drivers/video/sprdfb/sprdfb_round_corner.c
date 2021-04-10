/******************************************************************************
 ** File Name:    sprdfb_round_corner.c                                            *
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
#include "sprdfb_round_corner.h"

static unsigned int gdi_sqrt(unsigned int x)
{
	unsigned int root = 0;
	unsigned int seed = (1 << 30);
	while (seed > x) {
		seed >>= 2;
	}

	while (seed != 0) {
		if (x >= seed + root) {
			x -= seed + root;
			root += seed * 2;
		}
		root >>= 1;
		seed >>= 2;
	}

	return root;
}

void draw_sector(unsigned int *alpha, int width, int height,
		int center_x, int center_y,	int radius)
{
	int x = 0;
	int y = 0;
	int line = 0;
	unsigned int *puiAlpha = NULL;

	for (y = MAX(0, center_y + 1); y < MIN(center_y + radius * 707 / 1000 + 1,
				height); y++) {
		line = gdi_sqrt((radius * STEP) * (radius * STEP) - ((y - center_y) * STEP)
				* ((y - center_y) * STEP));
		puiAlpha = &alpha[y * width + center_x + line / STEP];
		if (center_x + line / STEP >= 0 && center_x + line / STEP < width) {
			*puiAlpha = (0xff - ((line % STEP) * 0x01)) << 24;
			puiAlpha++;
		}

		x = MAX(0, center_x + line / STEP + 1);
		puiAlpha = &alpha[y * width + x];
		for (; x < MIN(center_x + radius, width); x++) {
			*puiAlpha = (0xff - 0) << 24;
			puiAlpha++;
		}
	}

	for (x = MAX(0, center_x + 1); x < MIN(center_x + radius * 707 / 1000 + 1,
				width); x++) {
		line = gdi_sqrt((radius * STEP) * (radius * STEP) - ((x - center_x) * STEP)
				* ((x - center_x) * STEP));
		puiAlpha = &alpha[(center_y + line / STEP) * width + x];
		if (center_y + line / STEP >= 0 && center_y + line / STEP < height) {
			*puiAlpha = (0xff - ((line % STEP) * 0x01)) << 24;
			puiAlpha += width;
		}

		y = MAX(0, center_y + line / STEP + 1);
		puiAlpha = &alpha[y * width + x];
		for (; y < MIN(center_y + radius, height); y++) {
			*puiAlpha = (0xff - 0) << 24;
			puiAlpha += width;
		}
	}

	for (y = MAX(center_y + radius * 707 / 1000 + 1, 0); y < MIN(center_y + radius,
				height); y++) {
		x = MAX(center_x + radius * 707 / 1000 + 1, 0);
		puiAlpha = &alpha[y * width + x];
		for (; x < MIN(center_x + radius, width); x++) {
			*puiAlpha = (0xff - 0) << 24;
			puiAlpha++;
		}
	}
}

static void data_x_mirrored(unsigned int *dst, unsigned int *src, int width, int height)
{
	int i, j;
	unsigned *p = (unsigned *) src;
	unsigned *q = (unsigned *) dst;

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			q[i * width + width - 1 -j] = p[i * width + j];
		}
	}
}

static void data_y_mirrored(unsigned int *dst, unsigned int *src, int width, int height)
{
	int i, j;
	unsigned *p = (unsigned *) src;
	unsigned *q = (unsigned *) dst;

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			q[(height - 1 - i) * width + j] = p[i * width + j];
		}
	}
}

inline short argb_to_rgb565(unsigned int argb)
{
	int r, g, b;
	r = (argb & 0x00ff0000) >> 16;
	g = (argb & 0x0000ff00) >> 8;
	b = (argb & 0x000000ff) >> 0;

	return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}

inline short rgb565_premult(unsigned short rgb, char alpha)
{
	int r, g, b;
	r = (rgb >> 11) & 0x1f;
	g = (rgb >> 5) & 0x3f;
	b = (rgb >> 0) & 0x1f;

	return (((r * alpha) / 255) << 11)
		| (((g * alpha) / 255) << 5)
		| (b * alpha) / 255;
}

void dispc_corner_blending(int width, unsigned int *lower,
		unsigned int *upper, int sec_x, int sec_y)
{
	int i, j;
	int radius, alpha;
	int index_l, index_u;
	int logo_bpp = 16;
	unsigned char *fb_base = (unsigned char *)lower;
	unsigned short *p = (unsigned short *)fb_base;
	short temp;

	radius = CONFIG_CORNER_RADIUS;

	for (i = 0; i < radius; i++) {
		for (j = 0; j < radius; j++) {
			index_u = j + i * radius;
			index_l = sec_x + j + (sec_y + i) * width;
			alpha = (upper[index_u] & 0xff000000) >> 24;
			if (alpha) {
				temp = argb_to_rgb565(upper[index_u]);
				p[index_l] = alpha * temp / 255 + rgb565_premult(p[index_l], (255 - alpha));
			}
		}
	}
}

void dispc_logo_show_corner(int height, int width, unsigned int addr)
{
	unsigned int *corner_a = NULL;
	unsigned int *corner_b = NULL;
	unsigned int *logo_addr = NULL;
	int radius;

	radius = CONFIG_CORNER_RADIUS;
	logo_addr = addr;

	corner_a = (unsigned int *)malloc(radius * radius * 4);
	corner_b = (unsigned int *)malloc(radius * radius * 4);

	if(NULL == corner_a || NULL == corner_b) {
		FB_PRINT("fail to alloc memory.\n");
		return;
	}

	memset(corner_a, 0x00, radius * radius * 4);
	memset(corner_b, 0x00, radius * radius * 4);

	/* fill right_bottom in logo */
	draw_sector(corner_a, radius, radius, 0, 0, radius);
	dispc_corner_blending(width, logo_addr, corner_a, width - radius, height - radius);

	/* fill left_bottom in logo */
	data_x_mirrored(corner_b, corner_a, radius, radius);
	dispc_corner_blending(width, logo_addr, corner_b, 0, height - radius);

	/* fill left_top in logo */
	data_y_mirrored(corner_a, corner_b, radius, radius);
	dispc_corner_blending(width, logo_addr, corner_a, 0, 0);

	/* fill right_top in logo */
	data_x_mirrored(corner_b, corner_a, radius, radius);
	dispc_corner_blending(width, logo_addr, corner_b, width - radius, 0);

	free(corner_a);
	free(corner_b);
}
