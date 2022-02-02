/* sprd_spi_md6000.c */
#include <linux/spi/spi.h>
#include "sprd_spi_md6000.h"
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/of_gpio.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/regulator/consumer.h>

static struct spi_device *spi_dev;
bool cali_mode;
static void spi_md6000_write_data_bytes(unsigned char *data, int len);
static void spi_md6000_write_bitfile(char *tx_buf_cmd, unsigned cmd_len, char *tx_buf_data, unsigned data_len);
static struct gpio_desc *md6000_rst_gpio;
static struct gpio_desc *md6000_logicrst_gpio;
extern int sprd_write_pa(unsigned long paddr, const unsigned long or_val,
			 const unsigned int clear_msk);
static int boot_mode_check(char *str)
{
	if (str != NULL && !strncmp(str, "cali", strlen("cali")))
		cali_mode = true;
	else
		cali_mode = false;
	return 0;
}
__setup("androidboot.mode=", boot_mode_check);

static void sprd_spi_md6000_spi_init(void)
{
	spi_dev->max_speed_hz = spi_freq; 
	spi_dev->mode = spi_mode;
	spi_setup(spi_dev);	
	printk("MD6000: spi init complete!\n");
}

static void sprd_spi_md6000_seq_init(void)
{
	/* Shift in Key activation */
	unsigned char cmd_init[4] = {0xA4, 0xC6, 0xF4, 0x8A};

	/* Init sequence */
	gpiod_direction_output(md6000_rst_gpio, 0);
	mdelay(10);
	spi_md6000_write_data_bytes(cmd_init, 4);
        gpiod_direction_output(md6000_rst_gpio, 1);
	mdelay(10);
	printk("MD6000: sequence init complete!\n");
}
/*
static int sprd_spi_md6000_check_id(void)
{
        unsigned char read_dev_id[4] = {0};
        unsigned char cmd_chk_id[4] = {0xE0, 0x00, 0x00, 0x00};
//      unsigned int data_dev_id[4] = {0x01, 0x2C, 0x00, 0x43};

	spi_write_then_read(spi_dev, cmd_chk_id, 4, read_dev_id, 4);

        printk("MD6000: read id:{0x%02x, 0x%02x, 0x%02x, 0x%02x}\n",
                                        read_dev_id[0],
                                        read_dev_id[1],
                                        read_dev_id[2],
                                        read_dev_id[3]);
        return 0;
}
*/
static int sprd_spi_md6000_config(unsigned char *bitfile, int len)
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

	spi_md6000_write_data_bytes(cmd_tran_en, 4);
	mdelay(1);
	/* Enable Programming Mode */
	spi_md6000_write_data_bytes(cmd_prog_en, 4);
	mdelay(1);

	/* Erase the device */
	spi_md6000_write_data_bytes(cmd_erase_dev, 4);
	mdelay(10);

	/* Programe Fuse Map */
	spi_md6000_write_data_bytes(cmd_fuse_map1, 4);
	mdelay(10);
	spi_md6000_write_bitfile(cmd_fuse_map2, 4, bitfile, len);
	mdelay(10);

	spi_md6000_write_data_bytes(cmd_in_usercode, 4);
	mdelay(1);

	/* Read the status bit */
	spi_write_then_read(spi_dev, cmd_read_stat, 4, status, 8);
	//printk("MD6000: status=%x,%x,%x,%x\n", status[0], status[1],status[2],status[3]);
	stat = (long)(status[4] << 24 | status[5] << 16 
		   | status[6] << 8 | status[7]);
	if(stat & 0x3100){
		printk("MD6000: verify status register success,stat=%x\n",stat);
	}else{
		printk("MD6000: Load bitfile failed!\n");
		return -2;
	}

	//if(!(stat & MD6000_STAT_DONE) || stat & MD6000_STAT_FAIL) {
	//	printk("MD6000: Load bitfile failed!\n");
	//	return -2;
	//}
	//if(stat & MD6000_STAT_BUSY) {
	//	printk("MD6000: FPGA is busy now!\n");
	//	return -3;
	//}

	/* Exit Programming Mode */
	spi_md6000_write_data_bytes(cmd_exit_prog1, 4);
	mdelay(10);
	spi_md6000_write_data_bytes(cmd_exit_prog2, 4);
	return 0;
}


static void spi_md6000_write_data_bytes(unsigned char *data, int len)
{
	struct spi_transfer txfer;
	struct spi_message msg;
	memset(&txfer, 0, sizeof(txfer));
        spi_message_init(&msg);
        spi_message_add_tail(&txfer, &msg);

	txfer.len = len;
	txfer.tx_buf = data;
	txfer.speed_hz = 48000000;
	spi_sync(spi_dev, &msg);
}

static void spi_md6000_write_bitfile(char *tx_buf_cmd, unsigned cmd_len, char *tx_buf_data, unsigned data_len)
{
	struct spi_message msg;
	struct spi_transfer t_cmd;
	struct spi_transfer t_data;

	memset(&t_cmd, 0, sizeof(struct spi_transfer));
	memset(&t_data, 0, sizeof(struct spi_transfer));
	spi_message_init(&msg);

	spi_message_add_tail(&t_cmd, &msg);

	t_cmd.tx_buf = tx_buf_cmd;
	t_cmd.len = cmd_len;
    t_cmd.bits_per_word = 8;
	t_cmd.speed_hz = 48000000;
	spi_sync(spi_dev, &msg);
	spi_message_add_tail(&t_data, &msg);
	t_data.tx_buf = tx_buf_data;
	t_data.len = data_len;
    t_data.bits_per_word = 8; 
	t_data.speed_hz = 48000000;

	spi_sync(spi_dev, &msg);
}

void spi_md6000_resume(void)
{
	gpio_direction_output(139, 1);
	gpio_free(139);
	sprd_write_pa(0x3243c104,0x10,0xffffffff);
	gpiod_direction_output(md6000_rst_gpio, 1);
    mdelay(5);
	gpiod_direction_output(md6000_rst_gpio, 0);
    mdelay(5);
	gpiod_direction_output(md6000_rst_gpio, 1);
}

void spi_md6000_suspend(void)
{
	sprd_write_pa(0x3243c104,0x30,0xffffffff);
	gpio_request(139, NULL);
	gpio_direction_output(139, 0);
	gpiod_direction_output(md6000_rst_gpio, 0);
}

int sprd_spi_md6000_load_bitfile(unsigned char *bitfile, int len)
{
	int ret;

	printk("MD6000: Load bitfile start\n");
	sprd_spi_md6000_spi_init();
	sprd_spi_md6000_seq_init();

	//sprd_spi_md6000_check_id();

	ret = sprd_spi_md6000_config(bitfile, len);
	if(ret) {
		printk("MD6000: Configuration failed!\n");
		return ret;
	}

	//printk("MD6000: Load bitfile successful!\n");
	//printk("MD6000: logic reset start!\n");
	//gpiod_direction_output(md6000_logicrst_gpio, 1);
	//gpiod_direction_output(md6000_logicrst_gpio, 0);
	//gpiod_direction_output(md6000_logicrst_gpio, 1);
	printk("MD6000: logic reset end!\n");
	return 0;
}

static int spi_md6000_probe(struct spi_device *spi)
{
      	//int ret;
	//struct voltage_supply vol_supply;
        printk("MD6000: probe function run\n");
	spi_dev = spi;
#if 0 //zhong
	vcc3v3 = regulator_get(NULL, "vddldo2");
        if (IS_ERR(vcc3v3) || !vcc3v3) {
        	printk("get md6000 3v3 failed, return!\n");
        	return -EFAULT;
    	}
    	regulator_set_voltage(vcc3v3, 3300000, 3300000);
    	ret = regulator_enable(vcc3v3);
	if(ret != 0)
		printk("md6000 %s: some error happen, fail to enable regulator!\n", __func__);
#endif
	md6000_rst_gpio = devm_gpiod_get(&spi->dev,"md6000rst", GPIOD_OUT_HIGH);
	if (IS_ERR(md6000_rst_gpio)) {
		pr_err("md6000_rst gpio invalid\n");
		return -EIO;
	}
    	md6000_logicrst_gpio = devm_gpiod_get(&spi->dev,"md6000logicrst", GPIOD_OUT_LOW);
	if (IS_ERR(md6000_logicrst_gpio)) {
		pr_err("md6000_logrst gpio invalid\n");
		return -EIO;
   	}
	if(cali_mode){
		printk("md6000 cali mode\n");
		spi_md6000_suspend();
	}

	return 0;
	
}

static const struct of_device_id spi_md6000_matchs[] = {
	{ .compatible = "md6000,spi", },
	{ }
};
MODULE_DEVICE_TABLE(of, spi_md6000_matchs);

static struct spi_driver spi_md6000_driver = {
	.probe		=spi_md6000_probe,
	.driver = {
		.name	="spi_md6000_drv",
		.owner	=THIS_MODULE,
		.of_match_table = spi_md6000_matchs,
	},
};
static int __init spi_md6000_init(void)
{
	spi_register_driver(&spi_md6000_driver);
	printk("md6000: register success\n");
	return 0;
}

static void spi_md6000_exit(void)
{
	spi_unregister_driver(&spi_md6000_driver);
}
late_initcall(spi_md6000_init);
module_exit(spi_md6000_exit);
