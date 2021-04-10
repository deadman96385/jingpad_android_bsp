
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
#include "sprd_i2c.h"

#define CONFIG_SYS_SPRD_I2C_DEFAULT_SPEED	100000
#define I2C_MAX_NUM				7

#define I2C_TIMEOUT	1000
/* Absolutely safe for status update at 100 kHz I2C: */
#define I2C_WAIT	200
enum i2c_local {
	AON_I2C,
	AP_I2C
};

struct i2c_base_addr {
	unsigned long bit_i2c_eb;
	void * i2c_base;
	enum i2c_local  local_base;
};

struct i2c_base_addr i2c_apb_bit[I2C_MAX_NUM] = {
	BIT_AP_APB_I2C0_EB,	SPRD_I2C0_PHYS, AP_I2C,
	BIT_AP_APB_I2C1_EB,	SPRD_I2C1_PHYS, AP_I2C,
	BIT_AP_APB_I2C2_EB,	SPRD_I2C2_PHYS, AP_I2C,
	BIT_AP_APB_I2C3_EB,	SPRD_I2C3_PHYS, AP_I2C,
	BIT_AP_APB_I2C4_EB,	SPRD_I2C4_PHYS, AP_I2C,
	BIT_I2C_EB,	SPRD_I2C_BASE,  AON_I2C,
	#ifdef CONFIG_SC9860
		BIT_AP_APB_I2C5_EB,	SPRD_I2C5_PHYS, AP_I2C,
	#endif
	};

static unsigned long *sprd_get_base(struct i2c_adapter *adap)
{
	return i2c_apb_bit[adap->hwadapnr].i2c_base;
}
static void sprd_i2c_hw_init(void *i2c_base)
{
	unsigned int tmp;

	tmp = readl(i2c_base + I2C_CTL);
	writel(tmp & ~I2C_CTL_IE, i2c_base + I2C_CTL);
	tmp = readl(i2c_base + I2C_CTL);
	writel(tmp & ~I2C_CTL_CMDBUF_EN, i2c_base + I2C_CTL);
	tmp = readl(i2c_base + I2C_CTL);
	writel(tmp  |I2C_CTL_IE|I2C_CTL_DUTY, i2c_base + I2C_CTL);
}

static void sprd_i2c_apb_enable(struct i2c_adapter *adap)
{
	unsigned int tmp;

	if (i2c_apb_bit[adap->hwadapnr].local_base) {
		tmp = readl(REG_AP_APB_APB_EB);
		writel( tmp|(i2c_apb_bit[adap->hwadapnr].bit_i2c_eb),
			REG_AP_APB_APB_EB);
	}
	else {
		tmp = readl(REG_AON_APB_APB_EB0);
		writel( tmp|(i2c_apb_bit[adap->hwadapnr].bit_i2c_eb),
			REG_AON_APB_APB_EB0);
	}
}

static void sprd_i2c_apb_disable(struct i2c_adapter *adap)
{
	unsigned int tmp;
	if (adap->hwadapnr  != 5) {
		tmp = readl(REG_AP_APB_APB_EB);
		writel( tmp&~(i2c_apb_bit[adap->hwadapnr].bit_i2c_eb),
			REG_AP_APB_APB_EB);
	}
	else {
		tmp = readl(REG_AON_APB_APB_EB0);
		writel( tmp&~(i2c_apb_bit[adap->hwadapnr].bit_i2c_eb),
			REG_AON_APB_APB_EB0);
	}

}

static void sprd_i2c_dump_reg(void *i2c_base)
{
	printf("I2C_CTL 	= 0x%x\n", readl(i2c_base + I2C_CTL));
	printf("I2C_CMD 	= 0x%x\n", readl(i2c_base + I2C_CMD));
	printf("I2C_CLKD0 = 0x%x\n", readl(i2c_base + I2C_CLKD0));
	printf("I2C_CLKD1 = 0x%x\n", readl(i2c_base + I2C_CLKD1));
	printf("I2C_RST = 0x%x\n", readl(i2c_base + I2C_RST));
	printf("I2C_CMD_BUF = 0x%x\n", readl(i2c_base + I2C_CMD_BUF));
	printf("I2C_CMD_BUF_CTL = 0x%x\n", readl(i2c_base + I2C_CMD_BUF_CTL));
}

static void sprd_i2c_ctl_enable(void *i2c_base)
{
	unsigned int tmp;

	tmp = readl(i2c_base + I2C_CTL);
	writel(tmp | I2C_CTL_EN, i2c_base + I2C_CTL);
}

static void sprd_i2c_ctl_disable(void *i2c_base)
{
	unsigned int tmp;

	tmp = readl(i2c_base + I2C_CTL);
	writel(tmp & ~I2C_CTL_EN, i2c_base + I2C_CTL);
}
static int sprd_wait_for_event(void *i2c_base)
{
	int status;
	int timeout = I2C_TIMEOUT;

	do {
		udelay(I2C_WAIT);
		status = readl(i2c_base+I2C_CTL);
	}
	while (!(status &(I2C_CTL_INT)) && timeout--);
	if (timeout <= 0) {
		printf("Timed out in wait_for_event: I2C_CTL_INT status=%04x\n",
			status);
		sprd_i2c_dump_reg(i2c_base);
		return -1;
	}

	timeout = I2C_TIMEOUT;
	do {
		udelay(I2C_WAIT);
		status = readl(i2c_base+I2C_CMD);
	} while ((status &(I2C_CMD_BUSY)) && timeout--);

	if (timeout <= 0) {
		printf("Timed out in wait_for_event: I2C_CMD_BUSY status=%04x\n",
			status);
		sprd_i2c_dump_reg(i2c_base);
		return -1;
	}

	timeout = I2C_TIMEOUT;
	do {
		udelay(I2C_WAIT);
		status = readl(i2c_base+I2C_CTL);
	} while ((status &(I2C_CTL_ACK ))&& timeout--);
	if (timeout <= 0) {
		printf("Timed out in wait_for_event: I2C_CTL_ACK status=%04x\n",
			status);
		sprd_i2c_dump_reg(i2c_base);
		return -1;
	}

	return status;
}

static int sprd_set_bus_speed(struct i2c_adapter *adap, int speed)
{
	unsigned int apb_clk;
	unsigned int i2c_div;
	void * i2c_base = NULL;

	apb_clk = 26000000;
	i2c_base = sprd_get_base(adap);
	i2c_div = apb_clk / (4 * speed) - 1;/*i2c freq*/

	sprd_i2c_ctl_disable(i2c_base);

	if (400000 == speed) {/*400K*/
		writel(0x0012000c,i2c_base + I2C_CLKD0);
		writel(0X10, i2c_base + I2C_STA_STO_DVD);
	} else {
		writel(((i2c_div & 0xffff) <<16 | (i2c_div & 0xffff)), i2c_base + I2C_CLKD0);
		writel(0X75, i2c_base + I2C_STA_STO_DVD);
	}
	writel((i2c_div >> 16 | (i2c_div & 0xffff0000)), i2c_base + I2C_CLKD1);
	sprd_i2c_ctl_enable(i2c_base);
}

static void sprd_i2c_init(struct i2c_adapter *adap, int speed, int slaveadd)
{
	unsigned int tmp;
	void * i2c_base = NULL;

	i2c_base = sprd_get_base(adap);

	sprd_i2c_apb_enable(adap);
	sprd_i2c_ctl_disable(i2c_base);
	sprd_i2c_hw_init(i2c_base);
	sprd_set_bus_speed(adap , speed);
	sprd_i2c_ctl_enable(i2c_base);

	writel(I2C_CMD_INT_ACK, i2c_base + I2C_CMD);
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

	cmd = (chip << 8) | I2C_CMD_WRITE;
	/* No data transfer, slave addr only */
	writel(cmd, i2c_base + I2C_CMD);

	res = sprd_wait_for_event(adap);
	if(res < 0)
		return res;

	return 0;
}

static int sprd_i2c_write_byte(void *i2c_base, char byte, int status)
{
	int res = 0;
	int cmd;

	cmd = (byte << 8) | status|I2C_CMD_INT_ACK;
	writel(cmd, i2c_base + 0x04);
	res = sprd_wait_for_event(i2c_base);

	if(res < 0)
		return res;

	return 0;
}


static int sprd_i2c_read_byte(void *i2c_base, char *byte, int status)
{
	int res = 0;
	int cmd;

	cmd = (((unsigned int)(*byte)) << 8) | status;
	writel(cmd, i2c_base + I2C_CMD);
	res = sprd_wait_for_event(i2c_base);

	if (res < 0) {
		return res;
	}

	*byte = (unsigned char)(readl(i2c_base + I2C_CMD) >> 8);

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
	int status = 0;
	void *i2c_base = NULL;

	i2c_base = sprd_get_base(adap);
	sprd_i2c_write_byte(i2c_base,(chip<<1),I2C_CMD_START | I2C_CMD_WRITE);

	if (len < 0) {
		printf("I2C write: data len < 0\n");
		return  -1;
	}

	if (alen > 2) {
		printf("I2C write: addr len %d not supported\n", alen);
		return  -1;
	}

	if(alen != 0) {
			res = sprd_i2c_write_byte(i2c_base,addr,I2C_CMD_WRITE);
	}


	for(i = 0; (res == 0)&&(i < len);i++){
		if(i == len-1){
			status = status|I2C_CMD_STOP;
		}
		res = sprd_i2c_write_byte(i2c_base,*(buffer+i),status|I2C_CMD_WRITE);
	}
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
	void *i2c_base = NULL;

	i2c_base = sprd_get_base(adap);
	sprd_i2c_write(adap,chip,addr,alen,NULL,0);
	status = status|I2C_CMD_START | I2C_CMD_WRITE;
	res = sprd_i2c_write_byte(i2c_base,((chip<<1)|1),status);

	if (len < 0) {
		printf("I2C read: data len < 0\n");
		return  -1;
	}

	if (buffer == NULL) {
		printf("I2C read: NULL pointer passed\n");
		return  -1;
	}

	status = 0;
	for(i = 0; (res == 0)&&(i < len);i++){
		if(i == len-1){
			status = status|I2C_CMD_READ|I2C_CMD_STOP|I2C_CMD_TX_ACK;
		}
		res = sprd_i2c_read_byte(i2c_base,(buffer+i),status|I2C_CMD_READ|I2C_CMD_INT_ACK);
	}
	return res;
}



U_BOOT_I2C_ADAP_COMPLETE(sprd_r7p0_i2c0, sprd_i2c_init, sprd_i2c_probe,
			 sprd_i2c_read, sprd_i2c_write, NULL,
			 CONFIG_SYS_SPRD_I2C_DEFAULT_SPEED,
			 NULL,
			 0)

U_BOOT_I2C_ADAP_COMPLETE(sprd_r7p0_i2c1, sprd_i2c_init, sprd_i2c_probe,
			 sprd_i2c_read, sprd_i2c_write, NULL,
			 CONFIG_SYS_SPRD_I2C_DEFAULT_SPEED,
			 NULL,
			 1)
U_BOOT_I2C_ADAP_COMPLETE(sprd_r7p0_i2c2, sprd_i2c_init, sprd_i2c_probe,
			 sprd_i2c_read, sprd_i2c_write, NULL,
			 CONFIG_SYS_SPRD_I2C_DEFAULT_SPEED,
			 NULL,
			 2)
U_BOOT_I2C_ADAP_COMPLETE(sprd_r7p0_i2c3, sprd_i2c_init, sprd_i2c_probe,
			 sprd_i2c_read, sprd_i2c_write, NULL,
			 CONFIG_SYS_SPRD_I2C_DEFAULT_SPEED,
			 NULL,
			 3)
U_BOOT_I2C_ADAP_COMPLETE(sprd_r7p0_i2c4, sprd_i2c_init, sprd_i2c_probe,
			 sprd_i2c_read, sprd_i2c_write, NULL,
			 CONFIG_SYS_SPRD_I2C_DEFAULT_SPEED,
			 NULL,
			 4)
U_BOOT_I2C_ADAP_COMPLETE(sprd_r7p0_i2c5, sprd_i2c_init, sprd_i2c_probe,
			 sprd_i2c_read, sprd_i2c_write, NULL,
			 CONFIG_SYS_SPRD_I2C_DEFAULT_SPEED,
			 NULL,
			 5)
#ifdef CONFIG_SC9860
U_BOOT_I2C_ADAP_COMPLETE(sprd_r7p0_i2c6, sprd_i2c_init, sprd_i2c_probe,
			 sprd_i2c_read, sprd_i2c_write, NULL,
			 CONFIG_SYS_SPRD_I2C_DEFAULT_SPEED,
			 NULL,
			 6)
#endif



