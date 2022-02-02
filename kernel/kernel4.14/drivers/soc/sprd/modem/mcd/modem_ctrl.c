/*
 * Copyright (C) 2019 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/of_device.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/syscore_ops.h>
#include <linux/sipc.h>
#include <linux/gpio/consumer.h>
#include <linux/reboot.h>
#ifdef CONFIG_PCIE_PM_NOTIFY
#include <linux/pcie_notifier.h>
#endif
#include <linux/mdm_ctrl.h>

#include "../include/sprd_pcie_resource.h"

extern int sysdump_status;

enum {
	ROC1_SOC = 0,
	ORCA_SOC
};

static char *const mdm_stat[MDM_STAUS_CNT] = {
	"mdm_power_off", "mdm_power_on", "mdm_warm_reset", "mdm_cold_reset",
	"mdm_crash_cp", "mdm_cp_crash", "mdm_cp_poweroff"
};

#define REBOOT_MODEM_DELAY    1000
#define POWERREST_MODEM_DELAY 2000
#define RESET_MODEM_DELAY    2000
#define MAX_POWER_DOWN_WAIT_ORCA 5000
#define MAX_REOOT_WAIT_ORCA 1000

char cdev_name[] = "mdm_ctrl";

struct modem_ctrl_init_data {
	char *name;
	/* ap to cp gpio */
	struct gpio_desc *gpio_poweron;  /* Poweron, cold reset */
	struct gpio_desc *gpio_poweroff; /* power off, notify cp power off */
	struct gpio_desc *gpio_reset;    /* Reset modem, warm reset */
	struct gpio_desc *gpio_preset;   /* Pcie reset */
	struct gpio_desc *gpio_crash;    /* crash cp, notify cp crash */

	/* cp tp ap gpio */
	struct gpio_desc *gpio_poweroff_ack; /*cp  power off ack */
	struct gpio_desc *gpio_cppanic;      /*cp crash notify ap */

	u32 irq_poweroff;
	u32 irq_crash;
	u32 irq_poweroff_ack;
	u32 irq_cppanic;
	u32 modem_status;
	bool enable_cp_event;
};

struct modem_ctrl_device {
	struct modem_ctrl_init_data *init;
	int major;
	int minor;
	struct cdev cdev;
	struct device *dev;
	int soc_type;
};

static struct class *modem_ctrl_class;
static struct modem_ctrl_device *mcd_dev;
static unsigned long g_mcd_reboot_event;

/* modem control evnet notify  */
static ATOMIC_NOTIFIER_HEAD(modem_ctrl_chain);

int modem_ctrl_register_notifier(struct notifier_block *nb)
{
	return atomic_notifier_chain_register(&modem_ctrl_chain, nb);
}
EXPORT_SYMBOL(modem_ctrl_register_notifier);

void modem_ctrl_unregister_notifier(struct notifier_block *nb)
{
	atomic_notifier_chain_unregister(&modem_ctrl_chain, nb);
}
EXPORT_SYMBOL(modem_ctrl_unregister_notifier);

static void send_event_msg(struct kobject *kobj)
{
	char *msg[3];
	char buff[100];
	char mbuff[100];

	memset(mbuff, 0, sizeof(mbuff));
	if (!mcd_dev || !mcd_dev->init || !kobj)
		return;

	snprintf(buff, sizeof(buff), "MODEM_STAT=%d",
		 mcd_dev->init->modem_status);
	snprintf(mbuff, sizeof(mbuff), "MODEM_EVENT=%s",
		 mdm_stat[mcd_dev->init->modem_status]);
	msg[0] = buff;
	msg[1] = mbuff;
	msg[2] = NULL;
	kobject_uevent_env(kobj, KOBJ_CHANGE, msg);
	dev_info(mcd_dev->dev, "send %s %s to userspace\n", buff, mbuff);
}

static irqreturn_t cpcrashtriger_handler(int irq, void *dev_id)
{
	if (!mcd_dev || !mcd_dev->init)
		return IRQ_NONE;

	mcd_dev->init->modem_status = MDM_CP_CRASH;
	atomic_notifier_call_chain(&modem_ctrl_chain,
				   MDM_CP_CRASH, NULL);

	panic("ap notify.");
	return IRQ_HANDLED;
}

static irqreturn_t cppanictriger_handler(int irq, void *dev_id)
{
	if (!mcd_dev || !mcd_dev->init || !mcd_dev->init->enable_cp_event)
		return IRQ_NONE;

	mcd_dev->init->modem_status = MDM_CP_CRASH;
	atomic_notifier_call_chain(&modem_ctrl_chain, MDM_CP_CRASH, NULL);
	send_event_msg(&mcd_dev->dev->kobj);
	return IRQ_HANDLED;
}

static irqreturn_t cppoweroff_handler(int irq, void *dev_id)
{
	if (!mcd_dev || !mcd_dev->init)
		return IRQ_NONE;

	mcd_dev->init->modem_status = MDM_POWER_OFF;
	atomic_notifier_call_chain(&modem_ctrl_chain,
				   MDM_POWER_OFF, NULL);
	kernel_power_off();
	return IRQ_HANDLED;
}

static int request_gpio_to_irq(struct gpio_desc *cp_gpio,
			       struct modem_ctrl_device *mcd_dev)
{
	int ret = 0;

	if (!mcd_dev || !mcd_dev->init)
		return -EINVAL;

	ret = gpiod_to_irq(cp_gpio);
	if (ret < 0) {
		dev_err(mcd_dev->dev, "requset irq  %d failed\n", ret);
		return ret;
	}
	dev_dbg(mcd_dev->dev, "gpio to irq  %d\n", ret);

	if (cp_gpio == mcd_dev->init->gpio_cppanic) {
		mcd_dev->init->irq_cppanic = ret;
		ret = devm_request_threaded_irq(mcd_dev->dev,
						mcd_dev->init->irq_cppanic,
						NULL, cppanictriger_handler,
						IRQF_ONESHOT |
						IRQF_TRIGGER_FALLING,
						"cppanic_irq", mcd_dev);
		if (ret < 0) {
			dev_err(mcd_dev->dev,
				"can not request irq for panic\n");
			return ret;
		}
		enable_irq_wake(mcd_dev->init->irq_cppanic);
		return 0;
	}

	if (cp_gpio == mcd_dev->init->gpio_crash) {
		mcd_dev->init->irq_crash = ret;
		ret = devm_request_threaded_irq(mcd_dev->dev,
						mcd_dev->init->irq_crash,
						NULL, cpcrashtriger_handler,
						IRQF_ONESHOT | IRQF_TRIGGER_LOW,
						"cpcrash_irq", mcd_dev);
		if (ret < 0) {
			dev_err(mcd_dev->dev, "can not request irq for cp crash\n");
			return ret;
		}
		enable_irq_wake(mcd_dev->init->irq_crash);
		return 0;
	}

	if (cp_gpio == mcd_dev->init->gpio_poweroff) {
		mcd_dev->init->irq_poweroff = ret;
		ret = devm_request_threaded_irq(mcd_dev->dev,
						mcd_dev->init->irq_poweroff,
						NULL, cppoweroff_handler,
						IRQF_ONESHOT | IRQF_TRIGGER_LOW,
						"cppoweroff_irq", mcd_dev);
		if (ret < 0) {
			dev_err(mcd_dev->dev,
				"can not request irq for cppoweroff\n");
			return ret;
		}
		enable_irq_wake(mcd_dev->init->irq_poweroff);
		return 0;
	}

	return -EINVAL;
}

static int modem_gpios_init(struct modem_ctrl_device *mcd_dev, int soc_type)
{
	int ret;

	if (!mcd_dev || !mcd_dev->init)
		return -EINVAL;
	if (soc_type == ROC1_SOC) {
		gpiod_direction_input(mcd_dev->init->gpio_poweroff_ack);
		gpiod_direction_input(mcd_dev->init->gpio_cppanic);

		ret = request_gpio_to_irq(mcd_dev->init->gpio_cppanic,
					  mcd_dev);
		if (ret)
			return ret;

		/* IRQF_TRIGGER_LOW, default must set to high */
		gpiod_set_value_cansleep(mcd_dev->init->gpio_crash, 1);
		gpiod_set_value_cansleep(mcd_dev->init->gpio_poweroff, 1);
	} else {
		gpiod_direction_input(mcd_dev->init->gpio_crash);
		ret = request_gpio_to_irq(mcd_dev->init->gpio_crash,
					  mcd_dev);
		if (ret)
			return ret;

		gpiod_direction_input(mcd_dev->init->gpio_poweroff);
		ret = request_gpio_to_irq(mcd_dev->init->gpio_poweroff,
					  mcd_dev);
		if (ret)
			return ret;

		/* TRIGGER_FALLING, defaultmust  set to high */
		gpiod_set_value_cansleep(mcd_dev->init->gpio_poweroff_ack, 1);
		gpiod_set_value_cansleep(mcd_dev->init->gpio_cppanic, 1);
	}
	return 0;
}

void modem_ctrl_enable_cp_event(void)
{
	if (mcd_dev && mcd_dev->init)
		mcd_dev->init->enable_cp_event = true;
}

static void modem_ctrl_restore_crash_gpio(void)
{
	struct gpio_desc *gpiodesc = NULL;

	if (!mcd_dev || !mcd_dev->init)
		return;

	gpiodesc = mcd_dev->init->gpio_crash;

	if (gpiodesc && !IS_ERR(gpiodesc))
		gpiod_set_value_cansleep(gpiodesc, 1);
}

static void modem_ctrl_send_cmd_to_cp(int cmd)
{
	struct gpio_desc *gpiodesc = NULL;

	if (!mcd_dev || !mcd_dev->init)
		return;

	if (cmd == MDM_CTRL_POWER_OFF) {
		dev_info(mcd_dev->dev, "poweroff send to cp.\n");
		gpiodesc = mcd_dev->init->gpio_poweroff;
	} else if (cmd == MDM_CTRL_CRASH_MODEM) {
		dev_info(mcd_dev->dev, "crash send to cp.\n");
		gpiodesc = mcd_dev->init->gpio_crash;
	} else {
		return;
	}

	if (gpiodesc && !IS_ERR(gpiodesc))
		gpiod_set_value_cansleep(gpiodesc, 0);
}

static void modem_ctrl_send_cmd_to_ap(int cmd)
{
	struct gpio_desc *gpiodesc = NULL;
	int status;

	if (!mcd_dev || !mcd_dev->init)
		return;

	switch (cmd) {
	case MDM_CTRL_CP_PANIC:
		dev_info(mcd_dev->dev, "panic send to ap\n");
		gpiodesc = mcd_dev->init->gpio_cppanic;
		status = MDM_CP_CRASH;
		break;
	case MDM_CTRL_POWEROFF_ACK:
		gpiodesc = mcd_dev->init->gpio_poweroff_ack;
		dev_info(mcd_dev->dev, "poweroff send to ap\n");
		status = MDM_POWER_OFF;
		break;
	default:
		return;
	}

	mcd_dev->init->modem_status = status;

	if (gpiodesc && !IS_ERR(gpiodesc))
		gpiod_set_value_cansleep(gpiodesc, 0);
}

void modem_ctrl_poweron_modem(int on)
{
	if (!mcd_dev || !mcd_dev->init)
		return;
	switch (on) {
	case MDM_CTRL_POWER_ON:
		if (!IS_ERR(mcd_dev->init->gpio_poweron)) {
			atomic_notifier_call_chain(&modem_ctrl_chain,
						   MDM_CTRL_POWER_ON, NULL);
			dev_info(mcd_dev->dev, "set modem_poweron: %d\n", on);
			gpiod_set_value_cansleep(mcd_dev->init->gpio_poweron,
						 1);
			/* Base the spec modem boot flow that need to wait 1s */
			msleep(REBOOT_MODEM_DELAY);
			mcd_dev->init->modem_status = MDM_CTRL_POWER_ON;
			send_event_msg(&mcd_dev->dev->kobj);
			gpiod_set_value_cansleep(mcd_dev->init->gpio_poweron,
						 0);
		}
		break;
	case MDM_CTRL_POWER_OFF:
		atomic_notifier_call_chain(&modem_ctrl_chain,
					   MDM_CTRL_POWER_OFF, NULL);
		/*
		 * sleep 500 ms for other module to do something
		 * before orca power down.
		 */
		msleep(500);
		modem_ctrl_send_cmd_to_cp(MDM_CTRL_POWER_OFF);
		mcd_dev->init->modem_status = MDM_CTRL_POWER_OFF;
		send_event_msg(&mcd_dev->dev->kobj);
		break;
	case MDM_CTRL_WARM_RESET:
		/* restore gpio crash before orca reset */
		modem_ctrl_restore_crash_gpio();
		if (!IS_ERR(mcd_dev->init->gpio_reset)) {
			atomic_notifier_call_chain(&modem_ctrl_chain,
						   MDM_CTRL_WARM_RESET, NULL);
			dev_dbg(mcd_dev->dev, "set warm reset: %d\n", on);
			gpiod_set_value_cansleep(mcd_dev->init->gpio_reset, 1);
			/* Base the spec modem that need to wait 2000ms */
			msleep(RESET_MODEM_DELAY);
			mcd_dev->init->modem_status = MDM_CTRL_WARM_RESET;
			send_event_msg(&mcd_dev->dev->kobj);
			gpiod_set_value_cansleep(mcd_dev->init->gpio_reset, 0);
		}
		break;
	case MDM_CTRL_COLD_RESET:
		/* restore gpio crash before orca reset */
		modem_ctrl_restore_crash_gpio();
		if (!IS_ERR(mcd_dev->init->gpio_poweron)) {
			mcd_dev->init->enable_cp_event = false;
			atomic_notifier_call_chain(&modem_ctrl_chain,
						   MDM_CTRL_COLD_RESET, NULL);
			dev_info(mcd_dev->dev, "modem_power reset: %d\n", on);
			gpiod_set_value_cansleep(mcd_dev->init->gpio_poweron,
						 1);
			/* Base the spec modem boot flow that need to wait 2s */
			msleep(POWERREST_MODEM_DELAY);
			mcd_dev->init->modem_status = MDM_CTRL_COLD_RESET;
			send_event_msg(&mcd_dev->dev->kobj);
			gpiod_set_value_cansleep(mcd_dev->init->gpio_poweron,
						 0);
		}
		break;
	case MDM_CTRL_CRASH_MODEM:
		modem_ctrl_send_cmd_to_cp(MDM_CTRL_CRASH_MODEM);
		break;
	default:
		dev_err(mcd_dev->dev, "cmd not support: %d\n", on);
		break;
	}
}

#if defined(CONFIG_DEBUG_FS)
static int modem_ctrl_debug_show(struct seq_file *m, void *private)
{
	dev_dbg(mcd_dev->dev, "%s\n", __func__);
	return 0;
}

static int modem_ctrl_debug_open(struct inode *inode, struct file *file)
{
	return single_open(file, modem_ctrl_debug_show, inode->i_private);
}

static const struct file_operations modem_ctrl_debug_fops = {
	.open = modem_ctrl_debug_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

#endif /* CONFIG_DEBUG_FS */

static int modem_ctrl_open(struct inode *inode, struct file *filp)
{
	struct modem_ctrl_device *modem_ctrl;

	modem_ctrl = container_of(inode->i_cdev,
				  struct modem_ctrl_device, cdev);
	filp->private_data = modem_ctrl;
	dev_dbg(modem_ctrl->dev, "modem_ctrl: %s\n", __func__);
	return 0;
}

static int modem_ctrl_release(struct inode *inode, struct file *filp)
{
	struct modem_ctrl_device *modem_ctrl;

	modem_ctrl = container_of(inode->i_cdev,
				  struct modem_ctrl_device, cdev);
	dev_dbg(modem_ctrl->dev, "modem_ctrl: %s\n", __func__);

	return 0;
}

static ssize_t modem_ctrl_read(struct file *filp,
			       char __user *buf,
			       size_t count,
			       loff_t *ppos)
{
	char tmpbuf[30];
	int r;
	struct modem_ctrl_device *mcd_dev  = filp->private_data;

	if (!mcd_dev || !mcd_dev->init)
		return -EINVAL;

	r = snprintf(tmpbuf, sizeof(tmpbuf), "%s\n",
		     mdm_stat[mcd_dev->init->modem_status]);

	return simple_read_from_buffer(buf, count, ppos, tmpbuf, r);
}

static ssize_t modem_ctrl_write(struct file *filp,
				const char __user *buf,
				size_t count, loff_t *ppos)
{
	char sbuf[100];
	int ret;
	u32 mcd_cmd;
	struct modem_ctrl_device *mcd_dev  = filp->private_data;

	if (!mcd_dev)
		return -EINVAL;

	if (unalign_copy_from_user((void *)sbuf, buf, count)) {
		dev_err(mcd_dev->dev, "copy buf %s error\n", buf);
		return -EFAULT;
	}
	dev_dbg(mcd_dev->dev, "get info:%s", sbuf);
	sbuf[count - 1] = '\0';
	ret = kstrtouint(sbuf, 10, &mcd_cmd);
	if (ret) {
		dev_err(mcd_dev->dev, "Invalid input!\n");
		return ret;
	}

	if (mcd_dev->soc_type == ROC1_SOC) {
		if (mcd_cmd >= MDM_CTRL_POWER_OFF &&
		    mcd_cmd <= MDM_CTRL_CRASH_MODEM)
			modem_ctrl_poweron_modem(mcd_cmd);
		else
			dev_info(mcd_dev->dev, "cmd not support!\n");
	} else {
		modem_ctrl_send_cmd_to_ap(mcd_cmd);
	}
	return count;
}

static long modem_ctrl_ioctl(struct file *filp, unsigned int cmd,
			     unsigned long arg)
{

	if (!mcd_dev || mcd_dev->soc_type == ORCA_SOC)
		return -EINVAL;
	switch (cmd) {
	case MDM_CTRL_POWER_OFF:
		modem_ctrl_poweron_modem(MDM_CTRL_POWER_OFF);
		break;
	case MDM_CTRL_POWER_ON:
		modem_ctrl_poweron_modem(MDM_CTRL_POWER_ON);
		break;
	case MDM_CTRL_WARM_RESET:
		modem_ctrl_poweron_modem(MDM_CTRL_WARM_RESET);
		break;
	case MDM_CTRL_COLD_RESET:
		modem_ctrl_poweron_modem(MDM_CTRL_COLD_RESET);
		break;
	case MDM_CTRL_CRASH_MODEM:
		modem_ctrl_poweron_modem(MDM_CTRL_CRASH_MODEM);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}

static const struct file_operations modem_ctrl_fops = {
	.open		= modem_ctrl_open,
	.release	= modem_ctrl_release,
	.read		= modem_ctrl_read,
	.write		= modem_ctrl_write,
	.unlocked_ioctl	= modem_ctrl_ioctl,
	.owner		= THIS_MODULE,
	.llseek		= default_llseek,
};

static int modem_ctrl_parse_modem_dt(struct modem_ctrl_init_data **init,
			       struct device *dev)
{
	struct modem_ctrl_init_data *pdata = NULL;

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;
	pdata->name = cdev_name;

	/* Triger watchdog,assert,panic of orca */
	pdata->gpio_crash = devm_gpiod_get(dev, "cpwatchdog", GPIOD_IN);
	if (IS_ERR(pdata->gpio_crash))
		return PTR_ERR(pdata->gpio_crash);

	pdata->gpio_poweroff_ack = devm_gpiod_get(dev, "cpassert",
						  GPIOD_OUT_HIGH);
	if (IS_ERR(pdata->gpio_poweroff_ack))
		return PTR_ERR(pdata->gpio_poweroff_ack);

	pdata->gpio_cppanic = devm_gpiod_get(dev, "cppanic", GPIOD_OUT_HIGH);
	if (IS_ERR(pdata->gpio_cppanic))
		return PTR_ERR(pdata->gpio_cppanic);

	pdata->gpio_poweroff = devm_gpiod_get(dev, "cppoweroff", GPIOD_IN);
	if (IS_ERR(pdata->gpio_poweroff_ack))
		return PTR_ERR(pdata->gpio_poweroff);

	*init = pdata;
	return 0;
}

static int modem_ctrl_parse_dt(struct modem_ctrl_init_data **init,
			       struct device *dev)
{
	struct modem_ctrl_init_data *pdata;

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;
	pdata->name = cdev_name;
	pdata->gpio_poweron = devm_gpiod_get(dev, "poweron", GPIOD_OUT_LOW);
	if (IS_ERR(pdata->gpio_poweron))
		return PTR_ERR(pdata->gpio_poweron);

	pdata->gpio_reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(pdata->gpio_reset))
		return PTR_ERR(pdata->gpio_reset);

	/* Triger watchdog,assert,panic of orca */
	pdata->gpio_poweroff_ack = devm_gpiod_get(dev, "cpassert", GPIOD_IN);
	if (IS_ERR(pdata->gpio_poweroff_ack))
		return PTR_ERR(pdata->gpio_poweroff_ack);

	pdata->gpio_cppanic = devm_gpiod_get(dev, "cppanic", GPIOD_IN);
	if (IS_ERR(pdata->gpio_cppanic))
		return PTR_ERR(pdata->gpio_cppanic);

	pdata->gpio_crash = devm_gpiod_get(dev, "cpwatchdog", GPIOD_OUT_HIGH);
	if (IS_ERR(pdata->gpio_crash))
		return PTR_ERR(pdata->gpio_crash);

	pdata->gpio_poweroff = devm_gpiod_get(dev, "cppoweroff",
					      GPIOD_OUT_HIGH);
	if (IS_ERR(pdata->gpio_poweroff))
		return PTR_ERR(pdata->gpio_poweroff);

	pdata->modem_status = MDM_CTRL_POWER_OFF;
	*init = pdata;
	return 0;
}

static inline void
modem_ctrl_destroy_pdata(struct modem_ctrl_init_data **init)
{
	struct modem_ctrl_init_data *pdata = *init;

	pdata = NULL;
}

static int modem_ctrl_restart_handle(struct notifier_block *this,
				     unsigned long mode, void *cmd)
{
	if (!mcd_dev || mcd_dev->soc_type == ROC1_SOC)
		return NOTIFY_DONE;
	modem_ctrl_send_cmd_to_ap(MDM_CTRL_CP_PANIC);
	while (1)
		;
	return NOTIFY_DONE;
}

static struct notifier_block modem_ctrl_restart_handler = {
	.notifier_call = modem_ctrl_restart_handle,
	.priority = 150,
};

static int modem_ctrl_probe(struct platform_device *pdev)
{
	struct modem_ctrl_init_data *init = pdev->dev.platform_data;
	struct modem_ctrl_device *modem_ctrl_dev;
	dev_t devid;
	int rval;
	struct device *dev = &pdev->dev;

	modem_ctrl_dev = devm_kzalloc(dev, sizeof(*modem_ctrl_dev), GFP_KERNEL);
	if (!modem_ctrl_dev)
		return -ENOMEM;
	mcd_dev = modem_ctrl_dev;
	if (of_device_is_compatible(pdev->dev.of_node, "sprd,roc1-modem-ctrl"))
		modem_ctrl_dev->soc_type = ROC1_SOC;
	else
		modem_ctrl_dev->soc_type = ORCA_SOC;

	if (modem_ctrl_dev->soc_type == ROC1_SOC) {
		rval = modem_ctrl_parse_dt(&init, &pdev->dev);
		if (rval) {
			dev_err(dev,
				"Failed to parse modem_ctrl device tree, ret=%d\n",
				rval);
			return rval;
		}
	} else {
		rval = modem_ctrl_parse_modem_dt(&init, &pdev->dev);
		if (rval) {
			dev_err(dev,
				"Failed to parse modem_ctrl device tree, ret=%d\n",
				rval);
			return rval;
		}
	}

	dev_dbg(dev, "after parse device tree, name=%s soctype=%d\n",
		init->name,
		modem_ctrl_dev->soc_type);

	rval = alloc_chrdev_region(&devid, 0, 1, init->name);
	if (rval != 0) {
		dev_err(dev, "Failed to alloc modem_ctrl chrdev\n");
		goto  error3;
	}
	cdev_init(&modem_ctrl_dev->cdev, &modem_ctrl_fops);
	rval = cdev_add(&modem_ctrl_dev->cdev, devid, 1);
	if (rval != 0) {
		dev_err(dev, "Failed to add modem_ctrl cdev\n");
		goto error2;
	}

	modem_ctrl_dev->major = MAJOR(devid);
	modem_ctrl_dev->minor = MINOR(devid);
	modem_ctrl_dev->dev = device_create(modem_ctrl_class, NULL,
					    MKDEV(modem_ctrl_dev->major,
						  modem_ctrl_dev->minor),
					    NULL, "%s", init->name);
	if (!modem_ctrl_dev->dev) {
		dev_err(dev, "create dev failed\n");
		rval = -ENODEV;
		goto error1;
	}
	modem_ctrl_dev->init = init;
	platform_set_drvdata(pdev, modem_ctrl_dev);
	rval = modem_gpios_init(modem_ctrl_dev, modem_ctrl_dev->soc_type);
	if (rval) {
		dev_err(dev, "request gpios error\n");
		goto error0;
	}

	rval = register_restart_handler(&modem_ctrl_restart_handler);
	if (rval) {
		dev_err(dev, "cannot register restart handler err=%d\n", rval);
		goto error0;
	}
	return 0;
error0:
	device_destroy(modem_ctrl_class,
		       MKDEV(modem_ctrl_dev->major,
			     modem_ctrl_dev->minor));
error1:
	cdev_del(&modem_ctrl_dev->cdev);
error2:
	unregister_chrdev_region(devid, 1);
error3:
	modem_ctrl_destroy_pdata(&init);
	return rval;
}

static int modem_ctrl_remove(struct platform_device *pdev)
{
	struct modem_ctrl_device *modem_ctrl_dev = platform_get_drvdata(pdev);

	unregister_reboot_notifier(&modem_ctrl_restart_handler);
	device_destroy(modem_ctrl_class,
		       MKDEV(modem_ctrl_dev->major,
			     modem_ctrl_dev->minor));
	cdev_del(&modem_ctrl_dev->cdev);
	unregister_chrdev_region(MKDEV(modem_ctrl_dev->major,
				       modem_ctrl_dev->minor), 1);
	modem_ctrl_destroy_pdata(&modem_ctrl_dev->init);
	platform_set_drvdata(pdev, NULL);
	return 0;
}

static void modem_ctrl_shutdown(struct platform_device *pdev)
{
	pr_info("mcd: ctrl shutdown\n");

	/* orca do noting here. */
	if (!mcd_dev || mcd_dev->soc_type == ORCA_SOC)
		return;

	atomic_notifier_call_chain(&modem_ctrl_chain,
				   MDM_POWER_OFF, NULL);
	/*
	 * sleep 500 ms for other module to do something
	 * before orca power down.
	 */
	msleep(500);
}

static void modem_ctrl_core_shutdown(void)
{
	int cnt = 0, i = 0, max;
	int pre, state;
	bool recv_ack = false;
	struct gpio_desc *gpio_ack;

	if (!mcd_dev)
		return;

#ifdef CONFIG_SPRD_PCIE_EP_DEVICE
	/*  makesure the the ep power on. */
	if (!sprd_pcie_ep_power_on()) {
		pr_info("mcd: core shutdown ep not power on.\n");
		return;
	}
#endif

	/*
	 * SYS_POWER_OFF must wait more time to
	 * makesure the orca has shutdown.
	 */
	max = g_mcd_reboot_event == SYS_POWER_OFF ?
		MAX_POWER_DOWN_WAIT_ORCA : MAX_REOOT_WAIT_ORCA;

	gpio_ack = mcd_dev->init->gpio_poweroff_ack;
	pre = gpiod_get_value(gpio_ack);
	state = !pre;
	pr_debug("mcd: core shutdown...pre = %d\n", pre);

	if (mcd_dev->soc_type == ROC1_SOC) {
		modem_ctrl_send_cmd_to_cp(MDM_CTRL_POWER_OFF);

		/* timeout or recv orca ack. */
		for (cnt = 0; cnt < max; cnt++) {
			mdelay(1);
			if (pre != gpiod_get_value(gpio_ack)) {
				recv_ack = true;
				break;
			}
		}

		if (recv_ack) {
			/* timeout or orca ack gpio state has changed. */
			for (i = 0; i < 1000; i++) {
				mdelay(1);
				if (pre == gpiod_get_value(gpio_ack))
					break;
			}
			/*
			 * Although ack gpio state has changed,
			 * orca may still not completely powered off.
			 */
			mdelay(1000);
		} else {
			/*
			 * if cp can't respound, panic to avoid orca
			 * shutdown caused electricity leakage.
			 */
			if (g_mcd_reboot_event == SYS_POWER_OFF
			    && sysdump_status)
				panic("CP BLOCK!");
		}
	} else if (mcd_dev->soc_type == ORCA_SOC) {
		pr_info("mcd: put poweroff ack gpio to %d.\n", state);
		/* delay 100ms for roc1 detect it. */
		do {
			if (state != gpiod_get_value(gpio_ack))
				gpiod_set_value(gpio_ack, state);
			mdelay(1);
		} while (i++ < 100);
	}

	pr_info("mcd: core shutdown cnt=%d, i=%d.\n", cnt, i);
}

/*
 * Stop cpufreq at shutdown to make sure it isn't holding any locks
 * or mutexes when secondary CPUs are halted.
 */
static struct syscore_ops modem_ctrl_syscore_ops = {
	.shutdown = modem_ctrl_core_shutdown,
};

static const struct of_device_id modem_ctrl_match_table[] = {
	{.compatible = "sprd,roc1-modem-ctrl", },
	{.compatible = "sprd,orca-modem-ctrl", },
};

static struct platform_driver modem_ctrl_driver = {
	.driver = {
		.name = "modem_ctrl",
		.of_match_table = modem_ctrl_match_table,
	},
	.probe = modem_ctrl_probe,
	.remove = modem_ctrl_remove,
	.shutdown = modem_ctrl_shutdown,
};

static int mcd_reboot_event(struct notifier_block *nb,
			    unsigned long event, void *buf)
{
	g_mcd_reboot_event = event;

	return NOTIFY_OK;
}

static struct notifier_block mcd_notifier = {
	.notifier_call = mcd_reboot_event,
};

static int __init modem_ctrl_init(void)
{
	modem_ctrl_class = class_create(THIS_MODULE, "modem_ctrl");
	register_syscore_ops(&modem_ctrl_syscore_ops);
	register_reboot_notifier(&mcd_notifier);

	if (IS_ERR(modem_ctrl_class))
		return PTR_ERR(modem_ctrl_class);
	return platform_driver_register(&modem_ctrl_driver);
}

static void __exit modem_ctrl_exit(void)
{
	unregister_syscore_ops(&modem_ctrl_syscore_ops);
	unregister_reboot_notifier(&mcd_notifier);

	class_destroy(modem_ctrl_class);
	platform_driver_unregister(&modem_ctrl_driver);
}

module_init(modem_ctrl_init);
module_exit(modem_ctrl_exit);

MODULE_AUTHOR("Carl Gates");
MODULE_DESCRIPTION("sprd modem control device driver");
MODULE_LICENSE("GPL v2");

