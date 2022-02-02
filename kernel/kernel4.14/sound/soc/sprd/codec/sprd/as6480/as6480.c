/*
 * as6480.c -- as6480 audio switch driver
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/fs.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include "as6480.h"

#define AS6480_MODE_CTRL              1

#define AS6480_SWITCH_USB             0
#define AS6480_SWITCH_HEADSET         2
#define AS6480_SWITCH_GND_MIC_SWAP    3
#define AS6480_SWITCH_OFF             7

#define AS_DBG_TYPE_MODE              0

enum {
	AS6480_MODE_INVALID = -1,
	AS6480_MODE_USB = 0,
	AS6480_MODE_HEADSET,			
	AS6480_MODE_GND_MIC_SWAP,
	AS6480_MODE_OFF,
	AS6480_MODE_MAX
};

struct as6480_data {
	struct i2c_client *i2c_client;
	int mode;
};

static struct as6480_data *as6480;

static char* as6480_mode_string[AS6480_SWITCH_OFF + 1] = {
	"USB",
	"Other",
	"Headset",
	"Swap gnd and mic",
	"All switches off",
	"All switches off",
	"All switches off",
	"Off"
};

static int as6480_write_reg(int reg, u8 value)
{
	int ret;
	struct i2c_client *client = as6480->i2c_client;
    unsigned char block_data[2];
    struct i2c_msg msg[1] = {           
		{            
			.addr  = client->addr,            
			.flags = 0,            
			.len   = 2,            
			.buf   = block_data,          
		}        
    };  

	block_data[0] = (unsigned char)reg;        
	block_data[1] = (unsigned char)value;        
	ret = i2c_transfer(client->adapter, msg, 1);
    if (ret < 0)
        pr_err("%s:fail to write reg = %d, value=0x%x\n", __func__, reg, value);
	return ret;
}

static int as6480_read_reg(int reg)
{
    int ret;
	struct i2c_client *client = as6480->i2c_client;
    unsigned char block_data[2];
    struct i2c_msg msg[2] = { 
	    {
            .addr  = client->addr,
            .flags = 0,
            .len   = 1,
            .buf   = &block_data[0],
        },
	    {
            .addr = client->addr,
            .flags = I2C_M_RD | I2C_M_NOSTART,
            .len  = 1,
            .buf  = &block_data[1],
        }
    };
     
    block_data[0] = (unsigned char)reg;
    block_data[1] = 0;	
	ret = i2c_transfer(client->adapter, msg, 2);
	if (ret < 0)
        pr_err("%s:fail to read reg = %d, ret=%d\n", __func__, reg, ret);
	else
		ret = block_data[1];
    return ret;
}

bool as6480_switch_to_usb(void) 
{
	int ret;
	ret  = as6480_write_reg(AS6480_MODE_CTRL, AS6480_SWITCH_OFF);
	ret |= as6480_write_reg(AS6480_MODE_CTRL, AS6480_SWITCH_USB);
	return (ret < 0) ? false : true;
}

bool as6480_switch_to_headset(void)  
{
	int ret;
	ret  = as6480_write_reg(AS6480_MODE_CTRL, AS6480_SWITCH_OFF);
	ret |= as6480_write_reg(AS6480_MODE_CTRL, AS6480_SWITCH_HEADSET);
	return (ret < 0) ? false : true;
}

bool as6480_swap_gnd_mic(void) 
{
	int ret;
	int old_mode, new_mode;
	old_mode = as6480_read_reg(AS6480_MODE_CTRL);
	new_mode = (old_mode == AS6480_SWITCH_HEADSET) ? AS6480_SWITCH_GND_MIC_SWAP : AS6480_SWITCH_HEADSET;
	ret  = as6480_write_reg(AS6480_MODE_CTRL, AS6480_SWITCH_OFF);
    ret |= as6480_write_reg(AS6480_MODE_CTRL, new_mode);
	return (ret < 0) ? false : true;
}

bool as6480_switch_to_off(void)        
{
	int ret;
	ret = as6480_write_reg(AS6480_MODE_CTRL, AS6480_SWITCH_OFF);
	return (ret < 0) ? false : true;
}

int as6480_get_switch_mode(void)
{
	int ret = as6480_read_reg(AS6480_MODE_CTRL);
	return ret;
}

EXPORT_SYMBOL(as6480_switch_to_usb);
EXPORT_SYMBOL(as6480_switch_to_headset);
EXPORT_SYMBOL(as6480_swap_gnd_mic);
EXPORT_SYMBOL(as6480_switch_to_off);
EXPORT_SYMBOL(as6480_get_switch_mode);

static int as6480_switch_mode(int value)
{
	pr_info("set mode %d\n", value);
	switch (value) {
		case AS6480_MODE_USB:
			as6480_switch_to_usb();
			break;
		case AS6480_MODE_HEADSET:
			as6480_switch_to_headset();
			break;
		case AS6480_MODE_GND_MIC_SWAP:
			as6480_swap_gnd_mic();
			break;
		case AS6480_MODE_OFF:
			as6480_switch_to_off();
			break;
		default:
			pr_warn("Invalid mode %d\n", value);
			return -1;
	}
	return 0;
}

static ssize_t sysfs_show(struct device *dev,
			      struct device_attribute *attr,
			      char *buf, u32 type)
{
	int value = 0;
	char *mode = "Unknown mode";

	switch (type) {
		case AS_DBG_TYPE_MODE:
			value = as6480_get_switch_mode();
			if ((value >= AS6480_SWITCH_USB) && (value <= AS6480_SWITCH_OFF)) {
				mode = as6480_mode_string[value];
			} 
			break;
		default:
			pr_warn("%s: invalid type %d\n", __func__, type);
		    break;
	}
	return sprintf(buf, "%s\n", mode);
}

static ssize_t sysfs_set(struct device *dev,
			     struct device_attribute *attr,
			     const char *buf, size_t count, u32 type)
{
	int err;
	unsigned long value;

	err = kstrtoul(buf, 10, &value);
	if (err) {
		pr_warn("%s: get data of type %d failed\n", __func__, type);
		return err;
	}

	pr_info("%s: set type %d, data %ld\n", __func__, type, value);
	switch (type) {
		case AS_DBG_TYPE_MODE:
			as6480_switch_mode(value);
			break;
		default:
			pr_warn("%s: invalid type %d\n", __func__, type);
		    break;
	}
	return count;
}

#define as6480_DEVICE_SHOW(_name, _type) static ssize_t \
show_##_name(struct device *dev, \
			  struct device_attribute *attr, char *buf) \
{ \
	return sysfs_show(dev, attr, buf, _type); \
}

#define as6480_DEVICE_SET(_name, _type) static ssize_t \
set_##_name(struct device *dev, \
			 struct device_attribute *attr, \
			 const char *buf, size_t count) \
{ \
	return sysfs_set(dev, attr, buf, count, _type); \
}

#define as6480_DEVICE_SHOW_SET(name, type) \
as6480_DEVICE_SHOW(name, type) \
as6480_DEVICE_SET(name, type) \
static DEVICE_ATTR(name, S_IWUSR | S_IRUGO, show_##name, set_##name);

as6480_DEVICE_SHOW_SET(as6480_switch_mode, AS_DBG_TYPE_MODE);

static struct attribute *as6480_attrs[] = {
	&dev_attr_as6480_switch_mode.attr,
	NULL
};

static const struct attribute_group as6480_group = {
	.attrs = as6480_attrs,
};

static int as6480_i2c_probe(struct i2c_client *client,const struct i2c_device_id *id)
{
	struct as6480_data *priv;
	int ret = 0;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "%s: no support for i2c read/write"
				"byte data\n", __func__);
		return -EIO;
	}

	priv = devm_kzalloc(&client->dev, sizeof(struct as6480_data),
			GFP_KERNEL);
	if (priv == NULL)
		return -ENOMEM;
	priv->i2c_client = client;
	priv->mode       = AS6480_MODE_INVALID;
	i2c_set_clientdata(client, priv);
	as6480 = priv;

	ret = sysfs_create_group(&client->dev.kobj, &as6480_group);
	if(ret) {
        pr_err("%s: create attr error %d\n", __func__, ret);
	}
	return ret;
}

static int as6480_i2c_remove(struct i2c_client *client)
{
    sysfs_remove_group(&client->dev.kobj, &as6480_group);
	return 0;
}

static struct of_device_id as6480_match_table[] = {
	{ .compatible = "audio,audioswitch", },
	{}
};

static const struct i2c_device_id as6480_id[] = {
	{ "as6480", 0 },
	{ },
};
MODULE_DEVICE_TABLE(i2c, as6480_id);

static struct i2c_driver as6480_i2c_driver = {
	.driver	= {
		.name	= "as6480-audioswitch",
		.of_match_table = as6480_match_table,
	},
	.probe		= as6480_i2c_probe,
	.remove		= as6480_i2c_remove,
	.id_table	= as6480_id,
};

static int __init as6480_init(void)
{
	return i2c_add_driver(&as6480_i2c_driver);
}

static void __exit as6480_exit(void)
{
	i2c_del_driver(&as6480_i2c_driver);
}

module_init(as6480_init);
module_exit(as6480_exit);

MODULE_DESCRIPTION("as6480 driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:as6480-audioswitch");

