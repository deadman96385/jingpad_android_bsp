
/*
 * Basic I2C functions
 *
 * Copyright (c) 2015 Texas Instruments
 *
 * This package is free software;  you can redistribute it and/or
 * modify it under the terms of the license found in the file
 * named COPYING that should have accompanied this file.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Author: liulanqing lanqing.liu@spreadtrum.com, Texas Instruments
 *
 * Adapted for sprd I2C
 */

#include <common.h>
#include <i2c.h>
#include <asm/arch/sprd_reg.h>
#include <asm/io.h>

#define I2C_CTL				(0x000)
#define I2C_ADDR_CFG		(0x004)
#define I2C_COUNT			(0x008)
#define I2C_RX				(0x00C)
#define I2C_TX				(0x010)
#define I2C_STATUS			(0x014)
#define I2C_HSMODE_CFG		(0x018)
#define I2C_VERSION			(0x01C)
#define ADDR_DVD0			(0x020)
#define ADDR_DVD1			(0x024)
#define ADDR_STA0_DVD		(0x028)
#define ADDR_RST			(0x02C)

/* I2C_CTL */
#define STP_EN				BIT(20)
#define FIFO_AF_LVL			(16)
#define FIFO_AE_LVL			(12)
#define I2C_DMA_EN			BIT(11)
#define FULL_INTEN			BIT(10)
#define EMPTY_INTEN			BIT(9)
#define I2C_DVD_OPT			BIT(8)
#define I2C_OUT_OPT			BIT(7)
#define I2C_TRIM_OPT		BIT(6)
#define I2C_HS_MODE			BIT(4)
#define I2C_MODE			BIT(3)
#define I2C_EN				BIT(2)
#define I2C_INT_EN			BIT(1)
#define I2C_START			BIT(0)

/* I2C_STATUS */
#define SDA_IN				BIT(21)
#define SCL_IN				BIT(20)
#define FIFO_FULL			BIT(4)
#define FIFO_EMPTY			BIT(3)
#define I2C_INT				BIT(2)
#define I2C_RX_ACK			BIT(1)
#define I2C_BUSY				BIT(0)

/* ADDR_RST */
#define I2C_RST				BIT(0)

#define CONFIG_SYS_SPRD_I2C_DEFAULT_SPEED	100000
#define I2C_SRC_CLK			26000000

#define I2C_FIFO_DEEP	 		15
#define I2C_FIFO_FULL_THLD		8
#define I2C_FIFO_EMPTY_THLD	2
#define I2C_DATA_STEP			8

#define I2C_TIMEOUT	1000
/* Absolutely safe for status update at 100 kHz I2C: */
#define I2C_WAIT	200
enum i2c_local {
	AON_I2C,
	AP_I2C
};

struct i2c_base_addr {
	unsigned long i2c_eb;
	unsigned long apb_base;
	void * i2c_base;
};

struct i2c_base_addr i2c_apb_bit[] = {
	BIT_AP_APB_I2C0_EB, REG_AP_APB_APB_EB, SPRD_I2C0_PHYS,
	BIT_AP_APB_I2C1_EB, REG_AP_APB_APB_EB, SPRD_I2C1_PHYS,
	BIT_AP_APB_I2C2_EB, REG_AP_APB_APB_EB, SPRD_I2C2_PHYS,
	#if defined(BIT_AP_APB_I2C3_EB)
	BIT_AP_APB_I2C3_EB, REG_AP_APB_APB_EB, SPRD_I2C3_PHYS,
	#else
	0,0,NULL,
	#endif
	#if defined(BIT_AP_APB_I2C4_EB)
	BIT_AP_APB_I2C4_EB, REG_AP_APB_APB_EB, SPRD_I2C4_PHYS,
	#endif
};

static unsigned long *sprd_get_base(struct i2c_adapter *adap)
{
	return i2c_apb_bit[adap->hwadapnr].i2c_base;
}

static void sprd_i2c_apb_enable(struct i2c_adapter *adap)
{
	unsigned int tmp;

	tmp = readl(i2c_apb_bit[adap->hwadapnr].apb_base);
	writel( tmp|(i2c_apb_bit[adap->hwadapnr].i2c_eb),
			i2c_apb_bit[adap->hwadapnr].apb_base);
}

static void sprd_i2c_apb_disable(struct i2c_adapter *adap)
{
	unsigned int tmp;
	tmp = readl(i2c_apb_bit[adap->hwadapnr].apb_base);
	writel( tmp& ~(i2c_apb_bit[adap->hwadapnr].i2c_eb),
			i2c_apb_bit[adap->hwadapnr].apb_base);

}

static void sprd_i2c_set_count(void *i2c_base, u32 count)
{
	writel(count, i2c_base + I2C_COUNT);
}

static int sprd_i2c_send_stop(void *i2c_base, int stop)
{
	unsigned int tmp = readl(i2c_base + I2C_CTL);

	if (stop)
		writel(tmp & (~STP_EN),i2c_base + I2C_CTL);
	else
		writel(tmp | (STP_EN), i2c_base + I2C_CTL);

	return 0;
}

static int sprd_i2c_clear_start(void *i2c_base)
{
	unsigned int tmp = readl(i2c_base + I2C_CTL);

	writel(tmp & (~I2C_START), i2c_base + I2C_CTL);

	return 0;
}

static int sprd_i2c_clear_ack(void *i2c_base)
{
	unsigned int tmp = readl(i2c_base + I2C_STATUS);

	writel(tmp & (~I2C_RX_ACK), i2c_base+ I2C_STATUS);

	return 0;
}

static int sprd_i2c_clear_int(void *i2c_base)
{
	unsigned int tmp = readl(i2c_base + I2C_STATUS);

	writel(tmp & (~I2C_INT), i2c_base+ I2C_STATUS);

	return 0;
}

static void sprd_i2c_dump_reg(void *i2c_base)
{
	printf("I2C_CTL 	= 0x%x\n", readl(i2c_base + I2C_CTL));
	printf("I2C_ADDR_CFG 	= 0x%x\n", readl(i2c_base + I2C_ADDR_CFG));
	printf("I2C_COUNT = 0x%x\n", readl(i2c_base + I2C_COUNT));
	printf("I2C_STATUS = 0x%x\n", readl(i2c_base + I2C_STATUS));
	printf("ADDR_DVD0 = 0x%x\n", readl(i2c_base + ADDR_DVD0));
	printf("ADDR_DVD1 = 0x%x\n", readl(i2c_base + ADDR_DVD1));
	printf("ADDR_STA0_DVD = 0x%x\n", readl(i2c_base + ADDR_STA0_DVD));

	sprd_i2c_clear_start(i2c_base);
}

static void sprd_i2c_ctl_enable(void *i2c_base)
{
	unsigned int tmp;

	tmp = readl(i2c_base + I2C_CTL);
	writel(tmp | I2C_EN, i2c_base + I2C_CTL);
}

static void sprd_i2c_ctl_disable(void *i2c_base)
{
	unsigned int tmp;

	tmp = readl(i2c_base + I2C_CTL);
	writel(tmp & ~I2C_EN, i2c_base + I2C_CTL);
}

static int sprd_i2c_opt_start(void *i2c_base)
{
	int cmd = readl(i2c_base + I2C_CTL);

	writel(cmd | I2C_START, i2c_base + I2C_CTL);

	return 0;
}

static int sprd_wait_for_fifo_empty(void *i2c_base)
{
	int status;
	int timeout = I2C_TIMEOUT;

	status = readl(i2c_base+I2C_STATUS);
	while (!(status &(FIFO_EMPTY)) && timeout--)
		udelay(1);

	return status;
}

static int sprd_wait_for_data_ready(void *i2c_base)
{
	int status;
	int timeout = I2C_TIMEOUT;

	do {
		udelay(I2C_WAIT);
		status = readl(i2c_base+I2C_STATUS);
	} while (!((status &(I2C_INT))||status &(FIFO_FULL)) && timeout--);

	if (timeout <= 0) {
		printf("Timed out in wait_for_data_ready: status=%04x\n",
			status);
		sprd_i2c_dump_reg(i2c_base);
		return -1;
	}

	sprd_i2c_clear_int(i2c_base);
	return status;
}


static int sprd_wait_for_int(void *i2c_base)
{
	int status;
	int timeout = I2C_TIMEOUT;

	do {
		udelay(I2C_WAIT);
		status = readl(i2c_base+I2C_STATUS);
	} while (!(status &(I2C_INT)) && timeout--);

	if (timeout <= 0) {
		printf("Timed out in wait_for_int: status=%04x\n",
			status);
		sprd_i2c_dump_reg(i2c_base);
		return -1;
	}

	sprd_i2c_clear_int(i2c_base);
	return status;
}

static int sprd_wait_for_ack(void *i2c_base)
{
	int status;
	int timeout = I2C_TIMEOUT;

	do {
		udelay(I2C_WAIT);
		status = readl(i2c_base+I2C_STATUS);
	} while ((status &(I2C_RX_ACK)) && timeout--);

	if (timeout <= 0) {
		printf("Timed out in wait_for_ack: status=%04x\n",
			status);
		sprd_i2c_dump_reg(i2c_base);
		return -1;
	}

	sprd_i2c_clear_start(i2c_base);
	return status;
}

static int sprd_set_bus_speed(struct i2c_adapter *adap, int speed)
{
	void * i2c_base = sprd_get_base(adap);
	u32 APB_clk = I2C_SRC_CLK;
	u32 i2c_dvd = APB_clk / (4 * speed) - 1;
	u32 high = ((i2c_dvd << 1) * 2) / 5;
	u32 low = ((i2c_dvd << 1) * 3) / 5;
	u32 div0 = (high & 0xffff) << 16 | (low & 0xffff);
	u32 div1 =  (high & 0xffff0000) | ((low & 0xffff0000) >> 16);

	writel(div0, i2c_base + ADDR_DVD0);
	writel(div1, i2c_base + ADDR_DVD1);

	if (speed == 400000)
		writel(((6 * APB_clk) / 10000000),
			i2c_base + ADDR_STA0_DVD);
	else if (speed == 100000)
		writel(((4 * APB_clk) / 1000000),
			i2c_base + ADDR_STA0_DVD);
	return 0;
}

static int sprd_i2c_clear_irq(struct i2c_adapter *adap)
{
	void * i2c_base = sprd_get_base(adap);
	unsigned int tmp = readl(i2c_base + I2C_STATUS);

	writel(tmp & (~I2C_INT), i2c_base + I2C_STATUS);

	return 0;
}

static void
sprd_i2c_reset_fifo(struct i2c_adapter *adap)
{
	void * i2c_base = sprd_get_base(adap);

	writel(I2C_RST, i2c_base + ADDR_RST);
}

static int
sprd_i2c_opt_mode(void *i2c_base, int rw)
{
	int cmd = readl(i2c_base + I2C_CTL) & (~I2C_MODE);

	writel((cmd | rw << 3), i2c_base + I2C_CTL);

	return 0;
}

static void sprd_i2c_init(struct i2c_adapter *adap, int speed, int slaveadd)
{
	void * i2c_base = sprd_get_base(adap);
	unsigned int tmp = 0;

	sprd_i2c_apb_enable(adap);
	tmp = readl(i2c_base + I2C_CTL);
	tmp = tmp & ~(I2C_EN | I2C_TRIM_OPT | (0xF << FIFO_AF_LVL) |
		(0xF << FIFO_AE_LVL));
	tmp |= I2C_INT_EN;
	tmp	|=(I2C_FIFO_FULL_THLD << FIFO_AF_LVL) |
		(I2C_FIFO_EMPTY_THLD << FIFO_AE_LVL);
	writel(tmp, i2c_base + I2C_CTL);

	printf("i2c%d, %s() freq=%d\n", adap->hwadapnr, __func__, speed);

	sprd_set_bus_speed(adap,speed);
	sprd_i2c_reset_fifo(adap);
	sprd_i2c_clear_irq(adap);
	tmp = readl(i2c_base + I2C_CTL);
	writel(tmp | (I2C_EN), i2c_base + I2C_CTL);

	sprd_i2c_apb_disable(adap);
}

/*only buf mode */
static void sprd_flush_buf(struct i2c_adapter *adap)
{

}

static int sprd_i2c_probe(struct i2c_adapter *adap, uchar chip)
{
	int res = -1; /* default = fail */
	void * i2c_base = NULL;
	int cmd;

	i2c_base = sprd_get_base(adap);
	if (chip == adap->slaveaddr)
		return res;

	return 0;
}

static int sprd_i2c_write_byte(void *i2c_base, char *byte, int c)
{
	int i =0;

	for(i = 0; i < c; i++) {
		writel(byte[i], i2c_base + I2C_TX);
		//printf("sprd_i2c_write_byte =%x \n", byte[i]);
	}

	return 0;
}


static int sprd_i2c_read_byte(void *i2c_base, char *byte, int c)
{
	int i =0;

	for(i = 0; i < c; i++) {
		byte[i] = (unsigned char)(readl(i2c_base + I2C_RX));
		//printf("sprd_i2c_read_byte =%x \n", byte[i]);
	}
	return 0;
}

/* sprd_i2c_write : read data from device by i2c line
 *
 * @adap: description the sprd i2c controller.
 * @chip: slave addrs
 * @addr:    Memory (register) address within the chip
 * @alen:    Number of bytes to use for addr (typically 1, 2 for larger
 *              memories, 0 for register type devices with only one
 *              register)
 * @buffer:  Where to read/write the data
 * @len:     How many bytes to read/write
 * Author: liulanqing lanqing.liu@spreadtrum.com
 */
static int sprd_i2c_write(struct i2c_adapter *adap, uchar chip, uint addr,
			    int alen, uchar *buffer, int len)
{
	int i = 0;
	int res = 0;
	int last = 0;
	void *i2c_base = NULL;
	int send_len = 0;
	uchar *p_buf = buffer;

	sprd_i2c_apb_enable(adap);

	i2c_base = sprd_get_base(adap);
	sprd_i2c_reset_fifo(adap);
	writel(chip << 1, i2c_base + I2C_ADDR_CFG);
	sprd_i2c_opt_mode(i2c_base, 0);
	res = sprd_i2c_write_byte(i2c_base, &addr, 1);

	sprd_i2c_set_count(i2c_base, len+1);
	sprd_i2c_send_stop(i2c_base, 1);
	sprd_i2c_opt_start(i2c_base);

	while(len) {
		send_len = len < I2C_FIFO_DEEP ? len : I2C_FIFO_DEEP;
		res = sprd_i2c_write_byte(i2c_base, p_buf, send_len);
		len -= send_len;
		p_buf +=send_len;
		sprd_wait_for_fifo_empty(i2c_base);
	}
	res = sprd_wait_for_int(i2c_base);
	res = sprd_wait_for_ack(i2c_base);

	sprd_i2c_apb_disable(adap);
	return res;
}

/* sprd_i2c_read : read data from device by i2c line
 *
 * @adap: description the sprd i2c controller.
 * @chip: slave addrs
 * @addr:    Memory (register) address within the chip
 * @alen:    Number of bytes to use for addr (typically 1, 2 for larger
 *              memories, 0 for register type devices with only one
 *              register)
 * @buffer:  Where to read/write the data
 * @len:     How many bytes to read/write
 * Author: liulanqing lanqing.liu@spreadtrum.com
 */
static int sprd_i2c_read(struct i2c_adapter *adap, uchar chip, uint addr,
			   int alen, uchar *buffer, int len)
{
	int i = 0;
	int res = 0;
	int status = 0;
	int get_len = 0;
	void *i2c_base = NULL;
	uchar *p_buf = buffer;

	sprd_i2c_apb_enable(adap);

	i2c_base = sprd_get_base(adap);
	sprd_i2c_reset_fifo(adap);
	writel(chip << 1, i2c_base + I2C_ADDR_CFG);

	sprd_i2c_opt_mode(i2c_base, 0);
	res = sprd_i2c_write_byte(i2c_base, &addr, 1);
	sprd_i2c_set_count(i2c_base, 1);
	sprd_i2c_send_stop(i2c_base, 0);
	sprd_i2c_opt_start(i2c_base);
	res = sprd_wait_for_int(i2c_base);
	res = sprd_wait_for_ack(i2c_base);
	if(res < 0)
		goto disable_out;

	if (buffer == NULL) {
		printf("I2C read: NULL pointer buffer\n");
		res = -1;
		goto disable_out;
	}

	sprd_i2c_opt_mode(i2c_base, 1);
	sprd_i2c_set_count(i2c_base, len);
	sprd_i2c_send_stop(i2c_base, 1);
	sprd_i2c_opt_start(i2c_base);

	while (len){
		sprd_wait_for_data_ready(i2c_base);
		get_len = len < I2C_FIFO_DEEP ? len : I2C_FIFO_DEEP;
		res = sprd_i2c_read_byte(i2c_base,p_buf, get_len);
		len -= get_len;
		p_buf +=get_len;
	}

	sprd_i2c_clear_start(i2c_base);

disable_out:
	sprd_i2c_apb_disable(adap);
	return res;
}



U_BOOT_I2C_ADAP_COMPLETE(sprd_r8p0_i2c0, sprd_i2c_init, sprd_i2c_probe,
			 sprd_i2c_read, sprd_i2c_write, NULL,
			 CONFIG_SYS_SPRD_I2C_DEFAULT_SPEED,
			 NULL,
			 0)
U_BOOT_I2C_ADAP_COMPLETE(sprd_r8p0_i2c1, sprd_i2c_init, sprd_i2c_probe,
			 sprd_i2c_read, sprd_i2c_write, NULL,
			 CONFIG_SYS_SPRD_I2C_DEFAULT_SPEED,
			 NULL,
			 1)
U_BOOT_I2C_ADAP_COMPLETE(sprd_r8p0_i2c2, sprd_i2c_init, sprd_i2c_probe,
			 sprd_i2c_read, sprd_i2c_write, NULL,
			 CONFIG_SYS_SPRD_I2C_DEFAULT_SPEED,
			 NULL,
			 2)

#if defined(BIT_AP_APB_I2C3_EB)
U_BOOT_I2C_ADAP_COMPLETE(sprd_r8p0_i2c3, sprd_i2c_init, sprd_i2c_probe,
			 sprd_i2c_read, sprd_i2c_write, NULL,
			 CONFIG_SYS_SPRD_I2C_DEFAULT_SPEED,
			 NULL,
			 3)
#endif

#if defined(BIT_AP_APB_I2C4_EB)
U_BOOT_I2C_ADAP_COMPLETE(sprd_r8p0_i2c4, sprd_i2c_init, sprd_i2c_probe,
			 sprd_i2c_read, sprd_i2c_write, NULL,
			 CONFIG_SYS_SPRD_I2C_DEFAULT_SPEED,
			 NULL,
			 4)
#endif


