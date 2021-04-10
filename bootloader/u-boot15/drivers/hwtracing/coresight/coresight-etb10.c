/*
 * An ETB device/driver
 * Copyright (C) 2016 Spreadtrum Communication Inc
 * Author: Eric Long<eric.long@spreadtrum.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/sizes.h>
#include <asm/io.h>
#include <common.h>
#include <lcd.h>
#include <asm/arch/sprd_reg.h>

#ifdef SPRD_CORESIGHT_ETB
#define ETB_BASE					SPRD_CORESIGHT_ETB
#else
#define ETB_BASE					0x10003000
#endif

#define ETB_RAM_DEPTH_REG			0x004
#define ETB_STATUS_REG				0x00c
#define ETB_RAM_READ_DATA_REG		0x010
#define ETB_RAM_READ_POINTER		0x014
#define ETB_RAM_WRITE_POINTER		0x018
#define ETB_TRG						0x01c
#define ETB_CTL_REG					0x020
#define ETB_RWD_REG					0x024
#define ETB_FFSR					0x300
#define ETB_FFCR					0x304
#define ETB_ITMISCOP0				0xee0
#define ETB_ITTRFLINACK				0xee4
#define ETB_ITTRFLIN				0xee8
#define ETB_ITATBDATA0				0xeeC
#define ETB_ITATBCTR2				0xef0
#define ETB_ITATBCTR1				0xef4
#define ETB_ITATBCTR0				0xef8

#ifndef BIT
#define BIT(x) (1<<x)
#endif
/* register description */
/* STS - 0x00C */
#define ETB_STATUS_RAM_FULL			BIT(0)
/* CTL - 0x020 */
#define ETB_CTL_CAPT_EN				BIT(0)
/* FFCR - 0x304 */
#define ETB_FFCR_EN_FTC				BIT(0)
#define ETB_FFCR_FON_MAN			BIT(6)
#define ETB_FFCR_STOP_FI			BIT(12)
#define ETB_FFCR_STOP_TRIGGER		BIT(13)

#define ETB_FFCR_BIT				6
#define ETB_FFSR_BIT				1
#define ETB_FRAME_SIZE_WORDS		4

#define CORESIGHT_UNLOCK			0xc5acce55
#define CORESIGHT_LAR				0xfb0

unsigned char etb_dump_mem[SZ_32K] = {0};
u32 etb_buf_size;

static inline void CS_LOCK(u32 addr)
{
	do {
		/* Wait for things to settle */
		//mb();
		__raw_writel(0x0, addr + CORESIGHT_LAR);
	} while (0);
}
static inline void CS_UNLOCK(u32 addr)
{
	do {
		__raw_writel(CORESIGHT_UNLOCK, addr + CORESIGHT_LAR);
		/* Make sure everyone has seen this */
		//mb();
	} while (0);
}

void sprd_etb_hw_dis(void)
{
	u32 ffcr;
	CS_UNLOCK(ETB_BASE);

	ffcr = __raw_readl(ETB_BASE + ETB_FFCR);
	/* stop formatter when a stop has completed */
	ffcr |= ETB_FFCR_STOP_FI;
	__raw_writel(ffcr, ETB_BASE + ETB_FFCR);
	/* manually generate a flush of the system */
	ffcr |= ETB_FFCR_FON_MAN;
	__raw_writel(ffcr, ETB_BASE + ETB_FFCR);

	__raw_writel(0x0, ETB_BASE + ETB_CTL_REG);
	CS_LOCK(ETB_BASE);
}

void sprd_etb_dump (void)
{
	int i;
	unsigned char *buf_ptr = NULL;
	u32 read_data;
	u32 read_ptr, write_ptr;
	u32 frame_off, frame_endoff;

	buf_ptr = (unsigned char *)etb_dump_mem;
	if (buf_ptr == NULL) {
		lcd_printf("ETB buf_ptr NULL!\n");
		return;
	}

	CS_UNLOCK(ETB_BASE);

	read_ptr = __raw_readl(ETB_BASE + ETB_RAM_READ_POINTER);
	write_ptr = __raw_readl(ETB_BASE + ETB_RAM_WRITE_POINTER);
	etb_buf_size = __raw_readl(ETB_BASE + ETB_RAM_DEPTH_REG);

	frame_off = write_ptr % ETB_FRAME_SIZE_WORDS;
	frame_endoff = ETB_FRAME_SIZE_WORDS - frame_off;
	if (frame_off)
		write_ptr += frame_endoff;

	if ((__raw_readl(ETB_BASE + ETB_STATUS_REG) & ETB_STATUS_RAM_FULL) == 0)
		__raw_writel(0x0, ETB_BASE + ETB_RAM_READ_POINTER);
	else
		__raw_writel(write_ptr, ETB_BASE + ETB_RAM_READ_POINTER);

	for (i = 0; i < etb_buf_size; i++) {
		read_data = __raw_readl(ETB_BASE + ETB_RAM_READ_DATA_REG);
		*buf_ptr++ = read_data >> 0;
		*buf_ptr++ = read_data >> 8;
		*buf_ptr++ = read_data >> 16;
		*buf_ptr++ = read_data >> 24;
	}

	if (frame_off) {
		buf_ptr -= (frame_endoff * 4);
		for (i = 0; i < frame_endoff; i++) {
			*buf_ptr++ = 0x0;
			*buf_ptr++ = 0x0;
			*buf_ptr++ = 0x0;
			*buf_ptr++ = 0x0;
		}
	}

	__raw_writel(read_ptr, ETB_BASE + ETB_RAM_READ_POINTER);
	CS_LOCK(ETB_BASE);
}

