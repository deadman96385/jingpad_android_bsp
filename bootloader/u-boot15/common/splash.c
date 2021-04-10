/*
 * Copyright (C) 2013, Boundary Devices <info@boundarydevices.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., http://www.fsf.org/about/contact/
 *
 */

#include <common.h>
#include <splash.h>
#include <lcd.h>

__weak int splash_screen_prepare(uchar *logo_part_name, u8 *addr)
{
	return 0;
}


#ifdef CONFIG_SPLASH_SCREEN_ALIGN
void splash_get_pos(int *x, int *y)
{
	char *s = getenv("splashpos");

	if (!s)
		return;

	if (s[0] == 'm')
		*x = BMP_ALIGN_CENTER;
	else
		*x = simple_strtol(s, NULL, 0);

	s = strchr(s + 1, ',');
	if (s != NULL) {
		if (s[1] == 'm')
			*y = BMP_ALIGN_CENTER;
		else
			*y = simple_strtol(s + 1, NULL, 0);
	}
}
#endif /* CONFIG_SPLASH_SCREEN_ALIGN */

#if defined(CONFIG_SPLASH_SCREEN) && defined(CONFIG_LCD)
int lcd_splash(uchar *logo_part_name)
{
	int x = 0, y = 0, ret;
	u8 *addr;
	u8 *s;

	s = getenv("splashimage");
	if (!s) {
		debugf("%s: failed to get env from splashimage\n");
		return -1;
	}
	addr = (u8 *) simple_strtoul(s, NULL, 16);

	ret = splash_screen_prepare(logo_part_name, addr);
	if (ret)
		return ret;

	splash_get_pos(&x, &y);

	return bmp_display(addr, x, y);
}

int splash_get_bpix(uchar *logo_part_name)
{
	u8 bpix;
	u8 bmp[128] = {0};

#ifndef CONFIG_ZEBU
	if (0 != common_raw_read(logo_part_name, (uint64_t)sizeof(bmp), (uint64_t)0, bmp)) {
		debug("failed to read logo partition:%s\n", logo_part_name);
		return -1;
	}
#else
	memcpy(bmp, 0xb0000000, (size_t)sizeof(bmp));
#endif

	bpix = bmp_get_bpix(bmp);
	if (bpix == 8 || bpix == 16 || bpix == 24 || bpix == 32) {
		panel_info.vl_bpix = bpix;
		debugf("get bmp bpix = %d\n", bpix);
	} else {
		panel_info.vl_bpix = 8;
		debugf("get bmp bpix format error! set default bpix = %d\n", panel_info.vl_bpix);
	}

	return 0;
}
#endif
