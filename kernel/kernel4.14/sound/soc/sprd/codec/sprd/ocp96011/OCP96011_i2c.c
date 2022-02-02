/*
 * ocp96011.c -- ocp96011 audio switch driver
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
#include <linux/delay.h>
#include "OCP96011-i2c.h"

//#define OCP96011_MODE_CTRL              1

#define OCP96011_SWITCH_USB             0
//#define OCP96011_SWITCH_HEADSET         2
//#define OCP96011_SWITCH_GND_MIC_SWAP    3
#define OCP96011_SWITCH_OFF             7

#define AS_DBG_TYPE_MODE              0

#define OCP96011_SWITCH_SETTINGS 0x04
#define OCP96011_SWITCH_CONTROL  0x05
#define OCP96011_SWITCH_STATUS1  0x07

enum {
	OCP96011_MODE_INVALID = -1,
	OCP96011_MODE_USB = 0,
	OCP96011_MODE_HEADSET,			
	OCP96011_MODE_GND_MIC_SWAP,
	OCP96011_MODE_OFF,
	OCP96011_MODE_MAX
};

struct ocp96011_data {
	struct i2c_client *i2c_client;
	int mode;
};

static struct ocp96011_data *ocp96011;
int switch_ctl;

static char* ocp96011_mode_string[OCP96011_SWITCH_OFF + 1] = {
	"USB",
	"Other",
	"Headset",
	"Swap gnd and mic",
	"All switches off",
	"All switches off",
	"All switches off",
	"Off"
};

static int ocp96011_write_reg(int reg, u8 value)
{
	int ret;
	struct i2c_client *client = ocp96011->i2c_client;
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

static int ocp96011_read_reg(int reg)
{
    int ret;
	struct i2c_client *client = ocp96011->i2c_client;
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

static bool OCP96011_update_settings(u32 switch_control, u32 switch_enable)
{
	int ret;
	ocp96011_write_reg(OCP96011_SWITCH_SETTINGS, 0x80);
	ret = ocp96011_write_reg(OCP96011_SWITCH_CONTROL, switch_control);
	/* OCP96011 chip hardware requirement */
	usleep_range(50, 55);
	ret |= ocp96011_write_reg(OCP96011_SWITCH_SETTINGS, switch_enable);
	return (ret < 0) ? false : true;
}

bool ocp96011_switch_to_usb(void) 
{
	int ret;
	ret  = OCP96011_update_settings(0x18, 0x98);
	return ret;
}

bool ocp96011_switch_to_headset(void)  
{
	int ret;

	ret = OCP96011_update_settings(0x00, 0x9F);
	return ret;
}

bool ocp96011_swap_gnd_mic(void) 
{
	int ret;
	int switch_control = 0;
	switch_control = ocp96011_read_reg(OCP96011_SWITCH_CONTROL);
	if ((switch_control & 0x07) == 0x07)
		switch_control = 0x0;
	else
		switch_control = 0x7;
	switch_ctl = switch_control;
	ret = OCP96011_update_settings(switch_control, 0x9F);
	return ret;

}

//add by zhong

bool ocp96011_swap_audio_sense(void)
{
	int ret;

	ret = OCP96011_update_settings(switch_ctl, 0x9F);
	return ret;
}
//end

bool ocp96011_switch_to_off(void)        
{
	int ret;
	ret  = OCP96011_update_settings(0x18, 0x98);
	return ret;
}

int ocp96011_get_switch_mode(void)
{
	int ret = ocp96011_read_reg(OCP96011_SWITCH_STATUS1);
	return ret;
}

EXPORT_SYMBOL(ocp96011_switch_to_usb);
EXPORT_SYMBOL(ocp96011_switch_to_headset);
EXPORT_SYMBOL(ocp96011_swap_gnd_mic);
EXPORT_SYMBOL(ocp96011_switch_to_off);
EXPORT_SYMBOL(ocp96011_get_switch_mode);
EXPORT_SYMBOL(ocp96011_swap_audio_sense);

static int ocp96011_switch_mode(int value)
{
	pr_info("set mode %d\n", value);
	switch (value) {
		case OCP96011_MODE_USB:
			ocp96011_switch_to_usb();
			break;
		case OCP96011_MODE_HEADSET:
			ocp96011_switch_to_headset();
			break;
		case OCP96011_MODE_GND_MIC_SWAP:
			ocp96011_swap_gnd_mic();
			break;
		case OCP96011_MODE_OFF:
			ocp96011_switch_to_off();
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
			value = ocp96011_get_switch_mode();
			if ((value >= OCP96011_SWITCH_USB) && (value <= OCP96011_SWITCH_OFF)) {
				mode = ocp96011_mode_string[value];
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
			ocp96011_switch_mode(value);
			break;
		default:
			pr_warn("%s: invalid type %d\n", __func__, type);
		    break;
	}
	return count;
}

#define ocp96011_DEVICE_SHOW(_name, _type) static ssize_t \
show_##_name(struct device *dev, \
			  struct device_attribute *attr, char *buf) \
{ \
	return sysfs_show(dev, attr, buf, _type); \
}

#define ocp96011_DEVICE_SET(_name, _type) static ssize_t \
set_##_name(struct device *dev, \
			 struct device_attribute *attr, \
			 const char *buf, size_t count) \
{ \
	return sysfs_set(dev, attr, buf, count, _type); \
}

#define ocp96011_DEVICE_SHOW_SET(name, type) \
ocp96011_DEVICE_SHOW(name, type) \
ocp96011_DEVICE_SET(name, type) \
static DEVICE_ATTR(name, S_IWUSR | S_IRUGO, show_##name, set_##name);

ocp96011_DEVICE_SHOW_SET(ocp96011_switch_mode, AS_DBG_TYPE_MODE);

static struct attribute *ocp96011_attrs[] = {
	&dev_attr_ocp96011_switch_mode.attr,
	NULL
};

static const struct attribute_group ocp96011_group = {
	.attrs = ocp96011_attrs,
};

static int ocp96011_i2c_probe(struct i2c_client *client,const struct i2c_device_id *id)
{
	struct ocp96011_data *priv;
	int ret = 0;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "%s: no support for i2c read/write"
				"byte data\n", __func__);
		return -EIO;
	}

	priv = devm_kzalloc(&client->dev, sizeof(struct ocp96011_data),
			GFP_KERNEL);
	if (priv == NULL)
		return -ENOMEM;
	priv->i2c_client = client;
	priv->mode       = OCP96011_MODE_INVALID;
	i2c_set_clientdata(client, priv);
	ocp96011 = priv;

	ret = sysfs_create_group(&client->dev.kobj, &ocp96011_group);
	if(ret) {
        pr_err("%s: create attr error %d\n", __func__, ret);
	}
	return ret;
}

static int ocp96011_i2c_remove(struct i2c_client *client)
{
    sysfs_remove_group(&client->dev.kobj, &ocp96011_group);
	return 0;
}

static struct of_device_id ocp96011_match_table[] = {
	{ .compatible = "audio,audioswitch", },
	{}
};

static const struct i2c_device_id ocp96011_id[] = {
	{ "ocp96011", 0 },
	{ },
};
MODULE_DEVICE_TABLE(i2c, ocp96011_id);

static struct i2c_driver ocp96011_i2c_driver = {
	.driver	= {
		.name	= "ocp96011-audioswitch",
		.of_match_table = ocp96011_match_table,
	},
	.probe		= ocp96011_i2c_probe,
	.remove		= ocp96011_i2c_remove,
	.id_table	= ocp96011_id,
};

static int __init ocp96011_init(void)
{
	return i2c_add_driver(&ocp96011_i2c_driver);
}

static void __exit ocp96011_exit(void)
{
	i2c_del_driver(&ocp96011_i2c_driver);
}

module_init(ocp96011_init);
module_exit(ocp96011_exit);

MODULE_DESCRIPTION("ocp96011 driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ocp96011-audioswitch");

