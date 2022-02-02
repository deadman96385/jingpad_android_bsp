/*
 * Copyright (C) 2020 Spreadtrum Communications Inc.
 *
 */
#include <common.h>
#include <linux/types.h>
#include "sprd_panel.h"
#include "../../spi/sprd_spi.h"
#include <sprd_spi_md6000.h>

#define MD6000_DEBUG
struct spi_init_param md6000_spi_int_parm[] =
{
	{
		//sck_default,
		sck_default,
		tx_neg_edge,
		rx_neg_edge,
		tx_rx_msb,
		rx_tx_mode,
		master_mode,
		0x0,
		32000000
	},  //for spi m6000 fpga
};

static void sprd_spi_md6000_power(void)
{
	/* GPIO init */
	sprd_gpio_request(NULL, MD6000_RST);
	sprd_gpio_direction_output(NULL, MD6000_RST, 1);
	sprd_gpio_request(NULL, MD6000_VDD1V85);
	sprd_gpio_direction_output(NULL, MD6000_VDD1V85, 1);
	sprd_gpio_request(NULL, MD6000_VDD1V2);
	sprd_gpio_direction_output(NULL, MD6000_VDD1V2, 1);
	//sprd_gpio_request(NULL, MD6000_VDD3V3);
	//sprd_gpio_direction_output(NULL, MD6000_VDD3V3, 1);
	sprd_gpio_request(NULL, MD6000_LOGIC_RST);
	sprd_gpio_direction_output(NULL, MD6000_LOGIC_RST, 1);

	#ifdef MD6000_DEBUG
	printk("MD6000: GPIO value RST:[%d], VDD1V85:[%d],VDD1V2:[%d], LGC_RST:[%d]\n",
					sprd_gpio_get(NULL, MD6000_RST),
					sprd_gpio_get(NULL, MD6000_VDD1V85),
					sprd_gpio_get(NULL, MD6000_VDD1V2),
					sprd_gpio_get(NULL, MD6000_LOGIC_RST));
	#endif
	printk("MD6000: power complete!\n");
	return;
}

static void sprd_spi_md6000_spi_init(unsigned int spi_id)
{
	printk("MD6000: spi_id = %d\n", spi_id);
	/* SPI init */
	sprd_spi_enable(spi_id);
	sprd_spi_clk_set(spi_id, SPICLK_SEL_192M, 1);
	sprd_spi_init(md6000_spi_int_parm);
	sprd_spi_set_spi_mode(SPIMODE_4WIRE_8BIT_SDIO);
	sprd_spi_set_data_width(8);
	printk("MD6000: spi init complete!\n");
	return;
}

static int sprd_spi_md6000_seq_init(unsigned int spi_id)
{
	/* Shift in Key activation */
	unsigned char cmd_init[4] = {0xA4, 0xC6, 0xF4, 0x8A};

	/* Init sequence */

	sprd_gpio_set(NULL, MD6000_RST, 0);
	mdelay(10);
	sprd_spi_set_cs(0, TRUE);
	sprd_spi_write_data_bytes(cmd_init, 4, 0);
	sprd_spi_set_cs(0, FALSE);
	sprd_gpio_set(NULL, MD6000_RST, 1);
	//sprd_gpio_direction_output(NULL, MD6000_LOGIC_RST, 1);
	mdelay(10);
	printk("MD6000: sequence init complete!\n");
	return 0;
}

static int sprd_spi_md6000_check_id(unsigned int spi_id)
{
	int ret;
	unsigned char read_dev_id[4] = {0};
	/* Check the IDCODE */
	unsigned char cmd_chk_id[4] = {0xE0, 0x00, 0x00, 0x00};
	unsigned int data_dev_id[4] = {0x01, 0x0F, 0x00, 0x43};

	sprd_spi_set_cs(0, TRUE);
	sprd_spi_write_data_bytes(cmd_chk_id, 4, 0);
	ret = sprd_spi_read_data_bytes(read_dev_id, MD6000_ID_LEN, 0);
	sprd_spi_set_cs(0, FALSE);

	#ifdef MD6000_DEBUG
	printk("MD6000: ret = %d, read id:{0x%02x, 0x%02x, 0x%02x, 0x%02x}\n",
					ret,
					read_dev_id[0],
					read_dev_id[1],
					read_dev_id[2],
					read_dev_id[3]);
	#endif

	if(ret != MD6000_ID_LEN
	|| read_dev_id[0] != data_dev_id[0]
	|| read_dev_id[1] != data_dev_id[1]
	|| read_dev_id[2] != data_dev_id[2]
	|| read_dev_id[3] != data_dev_id[3]) {
		printk("MD6000: check id err, ret = %d\n", ret);
		return -1;
	}

	printk("MD6000: check id success!\n");
	return 0;
}

static int sprd_spi_md6000_config(unsigned int spi_id, unsigned char *bitfile, int len)
{
	long stat;
	unsigned char status[8] = {0};

	/* Enable Programming Mode */
	unsigned char cmd_prog_en[4] = {0xC6, 0x00, 0x00, 0x00};
	/*Enable SRAM TRANSPARENT mode*/
	unsigned char cmd_tran_en[4] = {0x74, 0x00, 0x00, 0x00};
	/* Erase the device */
	unsigned char cmd_erase_dev[4] = {0x0E, 0x00, 0x00, 0x00};

	unsigned char cmd_in_usercode[4] = {0xC0, 0x00, 0x00, 0x00};
	/* Programe Fuse Map */
	unsigned char cmd_fuse_map1[4] = {0x46, 0x00, 0x00, 0x00};
	unsigned char cmd_fuse_map2[4] = {0x7A, 0x00, 0x00, 0x00};
	/* Read the status bit */
	unsigned char cmd_read_stat[4] = {0x3C, 0x00, 0x00, 0x00};
	/* Exit Programming Mode */
	unsigned char cmd_exit_prog1[4] = {0x26, 0x00, 0x00, 0x00};
	unsigned char cmd_exit_prog2[4] = {0xFF, 0xFF, 0xFF, 0xFF};

//3c
	sprd_spi_set_cs(0, TRUE);
	sprd_spi_write_data_bytes(cmd_read_stat, 4, 0);
	sprd_spi_read_data_bytes(status, 8, 0);
	sprd_spi_set_cs(0, FALSE);
	mdelay(1);

#if 0
	for(i=0;i<8;i++)
		printk("status[%d]=0x%x\n",i,status[i]);
#endif

	stat = (long)(status[0] << 56 | status[1] << 48
		   | status[2] << 40 | status[3] << 32 
		   | status[4] << 24 | status[5] << 16 
		   | status[6] << 8 | status[7]);
	if(stat & 0x20000){
		printk("MD6000: Check the Password error,stat=%x\n",stat);
		return -1;
	}
//74
	sprd_spi_set_cs(0, TRUE);
	sprd_spi_write_data_bytes(cmd_tran_en, 4, 0);
	sprd_spi_set_cs(0, FALSE);
	mdelay(1);
//3c
	sprd_spi_set_cs(0, TRUE);
	sprd_spi_write_data_bytes(cmd_read_stat, 4, 0);
	sprd_spi_read_data_bytes(status, 8, 0);
	sprd_spi_set_cs(0, FALSE);
	mdelay(1);
	stat = (long)(status[0] << 56 | status[1] << 48
		   | status[2] << 40 | status[3] << 32 
		   | status[4] << 24 | status[5] << 16 
		   | status[6] << 8 | status[7]);
	if(stat & 0x40){
		printk("MD6000: Check the SRAM Erase Lock seccess,stat=%x\n",stat);
	}
//3c
	sprd_spi_set_cs(0, TRUE);
	sprd_spi_write_data_bytes(cmd_read_stat, 4, 0);
	sprd_spi_read_data_bytes(status, 8, 0);
	sprd_spi_set_cs(0, FALSE);
	mdelay(1);
	stat = (long)(status[0] << 56 | status[1] << 48
		   | status[2] << 40 | status[3] << 32 
		   | status[4] << 24 | status[5] << 16 
		   | status[6] << 8 | status[7]);
	if(stat & 0x400){
		printk("MD6000: Check the SRAM Program Lock seccess,stat=%x\n",stat);
	}
//c6
	sprd_spi_set_cs(0, TRUE);
	sprd_spi_write_data_bytes(cmd_prog_en, 4, 0);
	sprd_spi_set_cs(0, FALSE);
	mdelay(1);
//0e
	sprd_spi_set_cs(0, TRUE);
	sprd_spi_write_data_bytes(cmd_erase_dev, 4, 0);
	sprd_spi_set_cs(0, FALSE);
	mdelay(10);
//3c
	sprd_spi_set_cs(0, TRUE);
	sprd_spi_write_data_bytes(cmd_read_stat, 4, 0);
	sprd_spi_read_data_bytes(status, 8, 0);
	sprd_spi_set_cs(0, FALSE);
	mdelay(1);
	stat = (long)(status[0] << 56 | status[1] << 48
		   | status[2] << 40 | status[3] << 32 
		   | status[4] << 24 | status[5] << 16 
		   | status[6] << 8 | status[7]);
	if(stat & 0x2100){
		printk("MD6000: Erase device error,stat=%x\n",stat);
		return -1;
	}
//46 7A
	sprd_spi_set_cs(0, TRUE);
	sprd_spi_write_data_bytes(cmd_fuse_map1, 4, 0);
	sprd_spi_set_cs(0, FALSE);
	sprd_spi_set_cs(0, TRUE);
	sprd_spi_write_data_bytes(cmd_fuse_map2, 4, 0);
	sprd_spi_write_data_bytes(bitfile, len, 0);
	sprd_spi_set_cs(0, FALSE);
	mdelay(50);
//c0
	sprd_spi_set_cs(0, TRUE);
	sprd_spi_write_data_bytes(cmd_in_usercode, 4, 0);
	sprd_spi_set_cs(0, FALSE);
	mdelay(1);
//3c
	sprd_spi_set_cs(0, TRUE);
	sprd_spi_write_data_bytes(cmd_read_stat, 4, 0);
	sprd_spi_read_data_bytes(status, 8, 0);
	sprd_spi_set_cs(0, FALSE);
	mdelay(1);
	stat = (long)(status[0] << 56 | status[1] << 48
		   | status[2] << 40 | status[3] << 32 
		   | status[4] << 24 | status[5] << 16 
		   | status[6] << 8 | status[7]);
	if(stat & 0xF003100){
		printk("MD6000: verify status register seccess,stat=%x\n",stat);
	}
//26 ff
	sprd_spi_set_cs(0, TRUE);
	sprd_spi_write_data_bytes(cmd_exit_prog1, 4, 0);
	sprd_spi_set_cs(0, FALSE);
	mdelay(10);
	sprd_spi_set_cs(0, TRUE);
	sprd_spi_write_data_bytes(cmd_exit_prog2, 4, 0);
	sprd_spi_set_cs(0, FALSE);
	return 0;
}

int sprd_spi_md6000_load_bitfile(unsigned int spi_id, unsigned char *bitfile, int len)
{
	int ret;

	printk("MD6000: Load bitfile start\n");
	//sprd_spi_md6000_power();
	sprd_spi_md6000_spi_init(spi_id);
	sprd_spi_md6000_seq_init(spi_id);
	ret = sprd_spi_md6000_check_id(spi_id);
	if(ret)
		return ret;

	ret = sprd_spi_md6000_config(spi_id, bitfile, len);
	if(ret) {
		printk("MD6000: Configuration failed!\n");
		return ret;
	}

	printk("MD6000: Load bitfile success!\n");

	return 0;
}
