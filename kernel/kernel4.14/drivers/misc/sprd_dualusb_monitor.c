/*
 * File:shub_core.c
 *
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 */
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/input.h>
#include <linux/kthread.h>
#include <uapi/linux/sched/types.h>
#include <linux/sipc.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/input/mt.h>
#include <linux/soc/sprd/sprd_mpm.h>


//#define	DUALUSB_DEBUG
#define	DUALUSB_EVENT_PIPE		5
#define	DUALUSB_PREFIX			"[DualUsb_kthread]"
#define	DUALUSB_TASK_RT_PRIO	0
int power_pin = 0;
int keyboard_irq = 0;
int hall_pin = 0;
int irq_num = 0;
int hall_irq_num = 0;

struct sprd_pms  *pms;

/**
 * The Data format between the HOST and  device
 *------------------------------------------------------
 *|Magic Number|KeyCnt|   KEY 1 (8 Byte)       |... | KEY n (8 Byte)       | CRC   |
 *|          |      |{Type|Code|Value}|... |{Type|Code|Value}|  |
 *| 0xFD 0xFD   |1 Byte  |2Byte|2Byte|4Byte  |... |2Byte |2Byte|4Byte |2Byte|
 *------------------------------------------------------
 */
/* define encode and decode */
#define	KBD_MAGIC_NUM			0xFD
#define	KBD_MAGIC_NUM_SIZE		2
#define	KBD_KEY_NUM_SIZE		1
#define	KBD_ONE_KEY_SIZE		8
#define	KBD_CRC_SIZE			2
#define	KBD_MIN_PACKET_SIZE		(KBD_MAGIC_NUM_SIZE+KBD_KEY_NUM_SIZE+KBD_ONE_KEY_SIZE+KBD_CRC_SIZE)
#define	KEY_MAX_NUM				200
#define	DUALUSB_READ_BUF_MAX	2048 //related to KEY_MAX_NUM

#define	BOOT_STAGE				1
#define	NORMAL_STAGE			0

#define	RETRY_NUMBER			20

#define DUALUSB_SCREEN_MAX_X 	3000
#define DUALUSB_SCREEN_MAX_Y 	1320
#define DUALUSB_MAX_TPADNUM 	5

static /*const*/ unsigned int sprd_keycodes[] = {
	// 1. standard 104-key keyboard layout
	// 1.1 Function keypad area
	// 13:  1 -> 13
	KEY_ESC, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8,
	KEY_F9, KEY_F10, KEY_F11, KEY_F12,
	// 1.2 Typing keyboard area, or Main keyboard area
	// 14:  14  -> 27
	KEY_GRAVE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
	KEY_0, KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE,
	// 14:  28  -> 41
	KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_O, KEY_I,
	KEY_P, KEY_LEFTBRACE, KEY_RIGHTBRACE, KEY_BACKSLASH,
	// 13:  42  -> 54
	KEY_CAPSLOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K,
	KEY_L, KEY_SEMICOLON, KEY_APOSTROPHE, KEY_ENTER,
	// 12:  55 -> 66
	KEY_LEFTSHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M,
	KEY_COMMA, KEY_DOT, KEY_SLASH, KEY_RIGHTSHIFT,
	// 8:  67 -> 74
	KEY_LEFTCTRL, KEY_LEFTMETA, KEY_LEFTALT, KEY_SPACE, KEY_RIGHTALT,
	KEY_RIGHTMETA, KEY_COMPOSE, KEY_RIGHTCTRL,
	// 1.3 Control keyboard area
	// 3:  75 -> 77
	KEY_SYSRQ, KEY_SCROLLLOCK, KEY_PAUSE,
	// 6:  78 -> 83
	KEY_INSERT, KEY_HOME, KEY_PAGEUP, KEY_DELETE, KEY_END, KEY_PAGEDOWN,
	// 4:  84 -> 87
	KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT,
	// 1.4 Numeric keypad area
	// 5:  88 -> 92
	KEY_NUMLOCK, KEY_KPSLASH, KEY_KPASTERISK, KEY_KPMINUS, KEY_KPPLUS,
	// 12: 93 -> 104
	KEY_KP7, KEY_KP8, KEY_KP9, KEY_KP4, KEY_KP5, KEY_KP6, KEY_KP1, KEY_KP2,
	KEY_KP3, KEY_KP0, KEY_KPDOT, KEY_KPENTER,
	// 2. gpio_keys, for sprd gpio_keys
	// 3:  105 -> 107
	KEY_VOLUMEUP, KEY_VOLUMEDOWN, KEY_POWER,
	// 3. other keys
	// 108 -> End
	KEY_MUTE, KEY_HOMEPAGE, KEY_APPSELECT, KEY_PREVIOUSSONG, KEY_PLAYPAUSE, KEY_NEXTSONG, KEY_BRIGHTNESSDOWN,    KEY_BRIGHTNESSUP, 0
};

static struct input_dev *sprdkbd_dev;
static struct input_dev *hall_dev;
static struct task_struct *thread;
static unsigned short error_num;
static unsigned char read_buf[DUALUSB_READ_BUF_MAX];
static unsigned char sipc_stage_flag; //filter the NODEV error during startup

static struct workqueue_struct *keyboard_wq;
static DEFINE_MUTEX(keyboard_lock);
static atomic_t keyboard_enable = ATOMIC_INIT(0);
static atomic_t keyboard_connect = ATOMIC_INIT(0);
static atomic_t pcie_lock_flag = ATOMIC_INIT(0);
static struct work_struct keyboard_connect_work;
static struct delayed_work keyboard_first_work;
static atomic_t hall_status_flag = ATOMIC_INIT(0);
static struct kobject *hall_ctrl_kobj = NULL;  

extern int panel_notifier_register(struct notifier_block *nb);
extern int panel_notifier_unregister(struct notifier_block *nb);

static int keyboard_panel_event(struct notifier_block *nb,
        unsigned long event, void *param)
{
	unsigned int pcie_flag;
	unsigned int enable;

	mutex_lock(&keyboard_lock);
    
	enable = atomic_read(&keyboard_enable);
	pcie_flag = atomic_read(&pcie_lock_flag);

	pr_info("%s: event = %ld pcie status %u keyboard connect %u\n ",
		__func__, event, pcie_flag, enable);

	if (!enable) {
		mutex_unlock(&keyboard_lock);
		return 0;
	}

	if (event == 2 && !pcie_flag) {
		sprd_pms_request_resource(pms, -1);
		atomic_set(&pcie_lock_flag, 1);
	} else if (event == 1 && pcie_flag) {
		sprd_pms_release_resource(pms);
		atomic_set(&pcie_lock_flag, 0);
	}

	mutex_unlock(&keyboard_lock);
	return 0;
}

static struct notifier_block keyboard_nb = {
        .notifier_call = keyboard_panel_event,
};

static ssize_t hall_sensor_status_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", atomic_read(&hall_status_flag));
}

static DEVICE_ATTR(hall_status, 0664, hall_sensor_status_show, NULL);   



static struct attribute *hall_sysfs_attrs[] = {
    &dev_attr_hall_status.attr,
    NULL,
};

static struct attribute_group hall_attr_group = {
    .attrs = hall_sysfs_attrs,
};

static int tp_sysfs_init(void)
{
    hall_ctrl_kobj = kobject_create_and_add("hall", NULL);
    if (!hall_ctrl_kobj){
        pr_err("Create tp_sysfs_init failed!\n");
        return -ENOMEM;
    }
    return sysfs_create_group(hall_ctrl_kobj, &hall_attr_group);
}


/**
 * Function :  kbd_checksum
 * Description :
 * it auto fill the encode head context in one packet
 * Parameters:
 * in_data : point the send data context
 * out_data : the one packet head address
 */
static unsigned short kbd_checksum(unsigned char *data,
									unsigned short data_len)
{
	unsigned int sum = 0xFDFD; //the first 2 byte is 0xFDFD
	unsigned short n_add;

#ifdef DUALUSB_DEBUG
	pr_info(DUALUSB_PREFIX "*data=%02x, data_len=%d\n", *data, data_len);
#endif

	if (!data || data_len == 0)
		return 0;

	while (data_len > 2) {
		n_add = *data++;
		n_add <<= 8;
		n_add += *data++;
		sum += n_add;
		data_len -= 2;
	}
	if (data_len == 2) {
		n_add = *data++;
		n_add <<= 8;
		n_add += *data++;
		sum += n_add;
	} else {
		n_add = *data++;
		n_add <<= 8;
		sum += n_add;
	}
	/*The carry is 2 at most, so we need 2 additions at most. */
	sum = (sum & 0xffff) + (sum >> 16);
	sum = (sum & 0xffff) + (sum >> 16);

	return (unsigned short)(~sum);
}

void print_packet(unsigned char *packet, unsigned short packet_len)
{
	int i = 0;
	unsigned char *data_cur = packet;

	pr_info(DUALUSB_PREFIX "packet(%d): ", packet_len);
	for (i = 0; i < packet_len; i++)
		pr_info("%02x ", *data_cur++);
	pr_info("\n");
}

/**
 * Function:  kbd_parse_one_packet
 * Description :
 * Parse the input uart  data
 * Parameters :
 * stream : point the current  parse  data
 * UseData : point the uart buffer data
 * len       : the receive data length
 * Return :
 * TRUE     One  frame completed
 * FALSE    One  frame not completed
 * Negetive  Error
 */
int kbd_parse_one_packet(struct input_dev *input,
								unsigned char *packet,
								unsigned short packet_len)
{
	unsigned char *data_cur = NULL, *data_flag = NULL;
	unsigned char key_num;
	unsigned short remain_len = 0, frame_remain_len = 0, flag_size = 0;
	unsigned short data_crc, crc_inframe_idx, crc_inframe;
	unsigned int type, code;
	int value, i;

	if (!atomic_read(&keyboard_enable))
		return -EINVAL;

	if (!packet || packet_len < KBD_MIN_PACKET_SIZE) {
		pr_err(DUALUSB_PREFIX "packet error, packet=%p, packet_len=%d\n",
			packet, packet_len);
		return -EINVAL;
	}

#ifdef DUALUSB_DEBUG
	print_packet(packet, packet_len);
#endif

	data_cur = packet;
	remain_len = packet_len;
	while (remain_len > 0) {
#ifdef DUALUSB_DEBUG
		pr_info(DUALUSB_PREFIX
			"search flag, remain_len=%d, data_cur=%p, *data_cur=%02x\n",
			remain_len, data_cur, *data_cur);
#endif
		// 1. search header flag {0xFD 0xFD}
		for (i = 0; i < remain_len; i++) {
			if (*data_cur == KBD_MAGIC_NUM) {
				flag_size++;
				//the magic number is 2 magic 0xFD, we got it
				if (flag_size == KBD_MAGIC_NUM_SIZE) {
					//data_flag point to flag
					data_flag = data_cur - (KBD_MAGIC_NUM_SIZE - 1);
					data_cur++; //data_cur point to key_num
					break;
				}
			}
			data_cur++;
		}
		flag_size = 0; //reset to 0 for next use
		if (i == remain_len) {
			pr_err(DUALUSB_PREFIX
				"not find the flag, remain_len=%d, data_cur=%p, *data_cur=%02x\n",
				remain_len, data_cur, *data_cur);
			//print the whole packet
			print_packet(packet, packet_len);
			return -EPROTO;
		}
		//remain_len point to the keys number byte
		remain_len -= (i + 1);

		// 2. get keys number
		key_num = *data_cur; //data_cur point to key_num
		if (key_num > KEY_MAX_NUM) {
			pr_err(DUALUSB_PREFIX "key_num=%d, error\n", key_num);
			//print the whole packet
			print_packet(packet, packet_len);
			//print the remain packet
			print_packet(data_cur, remain_len);
			return -EPROTO;
		}

		if (remain_len < (KBD_KEY_NUM_SIZE + key_num*KBD_ONE_KEY_SIZE + KBD_CRC_SIZE)) {
			pr_err(DUALUSB_PREFIX "key_num=%d, remain_len=%d, i=%d, error\n",
				key_num, remain_len, i);
			//print the whole packet
			print_packet(packet, packet_len);
			//print the remain packet
			print_packet(data_cur, remain_len);
			return -EPROTO;
		}
		// 3. check crcsum, data_cur point to key_num
		data_crc = kbd_checksum(data_cur, KBD_KEY_NUM_SIZE + key_num*KBD_ONE_KEY_SIZE);
		crc_inframe_idx = KBD_MAGIC_NUM_SIZE + KBD_KEY_NUM_SIZE + key_num*KBD_ONE_KEY_SIZE;
#ifdef DUALUSB_DEBUG
		pr_info(DUALUSB_PREFIX
			"remain_len=%d, key_num=%d, crc_inframe_idx=%d, data_crc=%04x\n",
			remain_len, key_num, crc_inframe_idx, data_crc);
#endif
		if ((crc_inframe_idx + 1) > (remain_len + KBD_MAGIC_NUM_SIZE)) {
			pr_err(DUALUSB_PREFIX "crc_inframe_idx=%d, remain_len=%d, error\n",
				crc_inframe_idx, remain_len);
			//print the whole packet
			print_packet(packet, packet_len);
			//print the remain packet
			print_packet(data_cur, remain_len);
			return -EPROTO;
		}
		crc_inframe = data_flag[crc_inframe_idx];
		crc_inframe <<= 8;
		crc_inframe |= data_flag[crc_inframe_idx+1];
		if (data_crc != crc_inframe) {
			pr_err(DUALUSB_PREFIX
				"checksum error, data_crc=0x%x, crc_inframe=0x%x\n",
				data_crc, crc_inframe);
			return -EPROTO;
		}

		// 4. keys handle
		data_cur++;
		frame_remain_len = key_num*KBD_ONE_KEY_SIZE;
		while (frame_remain_len >= KBD_ONE_KEY_SIZE) {
			type = *data_cur++;
			type <<= 8;
			type |= *data_cur++;
			code = *data_cur++;
			code <<= 8;
			code |= *data_cur++;
			value = *data_cur++;
			value <<= 8;
			value |= *data_cur++;
			value <<= 8;
			value |= *data_cur++;
			value <<= 8;
			value |= *data_cur++;
#ifdef DUALUSB_DEBUG
			pr_info(DUALUSB_PREFIX "report: type=%d, code=%d, value=%d\n",
				type, code, value);
#endif
			//call input report
			mutex_lock(&keyboard_lock);
			if (atomic_read(&keyboard_enable))
				input_event(sprdkbd_dev, type, code, value);
			mutex_unlock(&keyboard_lock);

			frame_remain_len -= KBD_ONE_KEY_SIZE;
		}
		if ((frame_remain_len > 0) && (frame_remain_len < KBD_ONE_KEY_SIZE)) {
			error_num++;
			pr_err(DUALUSB_PREFIX
				"handle data error, error_num=%d, frame_remain_len=%d\n",
				error_num, frame_remain_len);
			//print the whole packet
			print_packet(packet, packet_len);
			//print the remain packet
			print_packet(data_cur, remain_len);
			return -EPROTO;
		}

		//calculate the remaining length
		remain_len -= KBD_KEY_NUM_SIZE + key_num*KBD_ONE_KEY_SIZE + KBD_CRC_SIZE;
		if (remain_len > 0) {
			data_cur += 2; //data_cur point to next header flag
#ifdef DUALUSB_DEBUG
			pr_info(DUALUSB_PREFIX
				"remain_len=%d, data_cur=%p, *data_cur=%02x\n",
				remain_len, data_cur, *data_cur);
#endif
		}
	}

	return 0;
}

static int sipc_dualusb_channel_read(struct input_dev *input)
{
	int nread, retry = 0;

#ifdef DUALUSB_DEBUG
	pr_info(DUALUSB_PREFIX "%s enter\n", __func__);
#endif

	do {
		nread = sbuf_read(SIPC_ID_MINIAP, SMSG_CH_PIPE,
						DUALUSB_EVENT_PIPE, (void *)read_buf,
						DUALUSB_READ_BUF_MAX - 1, -1);
		if (nread < 0) {
			retry++;
			msleep(1000);
			if ((nread != -ENODEV) || (sipc_stage_flag != BOOT_STAGE))
				pr_warn(DUALUSB_PREFIX "sbuf_read err, nread=%d, retry=%d\n",
					nread, retry);
			if (retry > RETRY_NUMBER)
				break;
		}
	} while (nread < 0);

	if (nread > 0) {
		sipc_stage_flag = NORMAL_STAGE;
		kbd_parse_one_packet(input, read_buf, nread);
		memset(read_buf, 0, sizeof(read_buf));
	} else {
		if ((nread != -ENODEV) || (sipc_stage_flag != BOOT_STAGE))
			pr_err(DUALUSB_PREFIX "can not get data, ret=%d\n", nread);
	}

	return nread;
}

static int sipc_dualusb_monitor_thread(void *data)
{
	struct sched_param param = {.sched_priority = DUALUSB_TASK_RT_PRIO };
	struct input_dev *input = data;

	pr_info(DUALUSB_PREFIX "%s enter\n", __func__);

	error_num = 0;
	sipc_stage_flag = BOOT_STAGE;
	sched_setscheduler(current, SCHED_RR, &param);
	set_current_state(TASK_RUNNING);
	do {
		sipc_dualusb_channel_read(input);
	} while (!kthread_should_stop());

	pr_err(DUALUSB_PREFIX "sipc_monitor_read_thread exit\n");
	return 0;
}

static int sprd_hall_register(void)
{
    int error;
    hall_dev = input_allocate_device();
    if(!hall_dev)
        return -ENOMEM;

	hall_dev->name = "Sprd Hall";
	hall_dev->phys = "sprdhall/input0";
	hall_dev->id.bustype = BUS_HOST;
	hall_dev->id.vendor = 0x0001;
	hall_dev->id.product = 0x0001;
	hall_dev->id.version = 0x0100;
	hall_dev->keycodesize = sizeof(unsigned char);
    __set_bit(EV_REP, hall_dev->evbit);
	input_set_capability(hall_dev, EV_KEY, KEY_POWER);
	input_set_capability(hall_dev, EV_KEY, KEY_HALL_UP);
    input_set_capability(hall_dev, EV_KEY, KEY_HALL_DOWN);

    error = input_register_device(hall_dev);
    if (error) {
		pr_warn("%s: sprd hall register input failed, %d\n",
			__func__, error);
		input_free_device(hall_dev);
		return error;
	}

    return 0;

}
static int sprd_keyboard_register(void)
{
	int error;
	int i;

	sprdkbd_dev = input_allocate_device();
	if (!sprdkbd_dev)
		return -ENOMEM;

	sprdkbd_dev->name = "Sprd Keyboard";
	sprdkbd_dev->phys = "sprdkbd/input0";
	sprdkbd_dev->id.bustype = BUS_HOST;
	sprdkbd_dev->id.vendor = 0x0001;
	sprdkbd_dev->id.product = 0x0001;
	sprdkbd_dev->id.version = 0x0100;
	sprdkbd_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP) | BIT_MASK(EV_ABS) | BIT_MASK(EV_SYN);
	sprdkbd_dev->keycode = sprd_keycodes;
	sprdkbd_dev->keycodesize = sizeof(unsigned char);
	sprdkbd_dev->keycodemax = ARRAY_SIZE(sprd_keycodes);

	for (i = 0; i < ARRAY_SIZE(sprd_keycodes); i++)
		if (sprd_keycodes[i])
			__set_bit(sprd_keycodes[i], sprdkbd_dev->keybit);
    __clear_bit(KEY_RESERVED, sprdkbd_dev->keybit);
    __set_bit(BTN_TOUCH, sprdkbd_dev->keybit);
    __set_bit(BTN_LEFT, sprdkbd_dev->keybit);
    input_set_abs_params(sprdkbd_dev, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
    input_set_abs_params(sprdkbd_dev, ABS_MT_WIDTH_MAJOR, 0, 255, 0, 0);
    input_set_abs_params(sprdkbd_dev, ABS_MT_POSITION_Y, 0, DUALUSB_SCREEN_MAX_Y, 0, 0);
    input_set_abs_params(sprdkbd_dev,ABS_MT_POSITION_X,0,DUALUSB_SCREEN_MAX_X,0,0);
    error = input_mt_init_slots(sprdkbd_dev, DUALUSB_MAX_TPADNUM, INPUT_MT_POINTER);
	if (error) {
		pr_err(DUALUSB_PREFIX "failed to input_mt_init_slots: %d\n", error);
	}
	input_set_capability(sprdkbd_dev, EV_MSC, MSC_SCAN);
	/* error check */
	error = input_register_device(sprdkbd_dev);
	if (error) {
		pr_warn("%s: sprd keyboard register input failed, %d\n",
			__func__, error);
		input_free_device(sprdkbd_dev);
		return error;
	}

	return 0;
}

static void sprd_keyboard_unregister(void)
{
	input_unregister_device(sprdkbd_dev);
	sprdkbd_dev = NULL;
}

static void sprd_keyboard_connect_work(struct work_struct *work)
{
	unsigned int connect = atomic_read(&keyboard_connect);
	unsigned int enable = atomic_read(&keyboard_enable);
	unsigned int hall_status = atomic_read(&hall_status_flag);

	pr_info("%s: sprd keyboard status %u, connect %u, hall status %u\n",
			__func__, enable, connect, hall_status);

	if ((!connect && !enable) || (connect && !(!hall_status ^ enable))) {
		pr_warn("%s: sprd keyboard already %s, hall status %u\n",
			__func__, enable ? "enable" : "disable", hall_status);
		return;
	}

	mutex_lock(&keyboard_lock);
	if (connect && !hall_status) {
		if (sprd_keyboard_register()) {
			mutex_unlock(&keyboard_lock);
			return;
		}

		if (!atomic_read(&pcie_lock_flag)) {
			sprd_pms_request_resource(pms, -1);
			atomic_set(&pcie_lock_flag, 1);
		}

		atomic_set(&keyboard_enable, 1);
	} else {
		atomic_set(&keyboard_enable, 0);

		if (atomic_read(&pcie_lock_flag)) {
			atomic_set(&pcie_lock_flag, 0);
			sprd_pms_release_resource(pms);
		}

		sprd_keyboard_unregister();
	}
	mutex_unlock(&keyboard_lock);

	pr_info("%s: sprd keyboard %s success\n", __func__,
		atomic_read(&keyboard_enable) ? "enable" : "disable");
}

static irqreturn_t sprd_keyboard_isr(int irq, void *dev_id)
{

	if (gpio_get_value(keyboard_irq) == 0) {
		pr_info("%s: keyboard connect\n", __func__);

		atomic_set(&keyboard_connect, 1);
		queue_work(keyboard_wq, &keyboard_connect_work);
		irq_set_irq_type(irq_num, IRQF_TRIGGER_HIGH|IRQF_ONESHOT);
	} else if(gpio_get_value(keyboard_irq) == 1) {
		pr_info("%s: keyboard disconnect\n", __func__);

		atomic_set(&keyboard_connect, 0);
		queue_work(keyboard_wq, &keyboard_connect_work);
		irq_set_irq_type(irq_num, IRQF_TRIGGER_LOW|IRQF_ONESHOT);

	}

	return IRQ_HANDLED;
}

static irqreturn_t sprd_hall_isr(int irq, void *dev_id)
{


	if (gpio_get_value(hall_pin) == 0) {
		pr_info("%s: hall status 1\n", __func__);

		input_event(hall_dev, EV_KEY, KEY_HALL_DOWN, 1);
		input_sync(hall_dev);
		input_event(hall_dev, EV_KEY, KEY_HALL_DOWN, 0);
		input_sync(hall_dev);

		atomic_set(&hall_status_flag, 1);
		if (atomic_read(&keyboard_connect))
			queue_work(keyboard_wq, &keyboard_connect_work);
        } else if(gpio_get_value(hall_pin) == 1) {
		pr_info("%s: hall status 0\n", __func__);

		input_event(hall_dev, EV_KEY, KEY_HALL_UP, 1);
		input_sync(hall_dev);
		input_event(hall_dev, EV_KEY, KEY_HALL_UP, 0);
		input_sync(hall_dev);

		atomic_set(&hall_status_flag, 0);
		if (atomic_read(&keyboard_connect))
			queue_work(keyboard_wq, &keyboard_connect_work);
        }

        return IRQ_HANDLED;
}

static void sprd_first_keyboard_connect_work(struct work_struct *work) 
{

    if (gpio_get_value(keyboard_irq) == 0) {
        printk("%s: keyboard connect\n", __func__);
        atomic_set(&keyboard_connect, 1);
        queue_work(keyboard_wq, &keyboard_connect_work);
//	sprd_pms_request_resource(pms, -1);
//        atomic_set(&pcie_lock_flag, 1);
    }

	panel_notifier_register(&keyboard_nb);
    irq_num = gpio_to_irq(keyboard_irq);
    hall_irq_num = gpio_to_irq(hall_pin);

    request_irq(irq_num,sprd_keyboard_isr,IRQF_TRIGGER_LOW | IRQF_ONESHOT, "sprd_keybd", NULL);
    request_irq(hall_irq_num,sprd_hall_isr,IRQF_TRIGGER_FALLING |IRQF_TRIGGER_RISING|IRQF_ONESHOT, "sprd_hall", NULL);

    enable_irq_wake(irq_num);
    disable_irq(irq_num);
    enable_irq(irq_num);
    enable_irq_wake(hall_irq_num);
    disable_irq(hall_irq_num);
    enable_irq(hall_irq_num);
}

static int __init sipc_kbd_monitor_init(void)
{
	int error;
	struct device_node *np;
#ifdef DUALUSB_DEBUG
	pr_info(DUALUSB_PREFIX "%s enter\n", __func__);
#endif

    /* input device register move to connect work */
    INIT_WORK(&keyboard_connect_work, sprd_keyboard_connect_work);
    INIT_DELAYED_WORK(&keyboard_first_work, sprd_first_keyboard_connect_work);
    schedule_delayed_work(&keyboard_first_work, 15 * HZ); 
    thread = kthread_run(sipc_dualusb_monitor_thread, NULL,
						"sipc_dualusb_monitor");
	if (IS_ERR(thread)) {
		error = PTR_ERR(thread);
		pr_err(DUALUSB_PREFIX "failed to create kthread: %d\n", error);
	}

    pms = sprd_pms_create(1,"keyboard_sipc",false);

	np = of_find_compatible_node(NULL, NULL, "sprd_keyboard");
	keyboard_irq = of_get_named_gpio(np, "keyboard-gpios", 0);
	power_pin = of_get_named_gpio(np, "power-gpios", 0);
	hall_pin = of_get_named_gpio(np, "hall-gpios", 0);
	printk("%s,%d,keyboard_irq = %d,power_pin = %d\n",__func__,__LINE__,keyboard_irq,power_pin);
	gpio_request(keyboard_irq, "keyboard_irq");
	gpio_request(power_pin, "keyboard_power");
	gpio_request(hall_pin, "hall");
	gpio_direction_input(keyboard_irq);
	gpio_direction_input(hall_pin);
	gpio_direction_output(power_pin, 1);

	keyboard_wq = create_singlethread_workqueue("keyboard_wq");

	sprd_hall_register();

	tp_sysfs_init();

#ifdef DUALUSB_DEBUG
	pr_info(DUALUSB_PREFIX "%s succ\n", __func__);
#endif
	return 0;
}


static void __exit sipc_kbd_monitor_exit(void)
{
	destroy_workqueue(keyboard_wq);
	pr_info(DUALUSB_PREFIX "%s\n", __func__);
}

module_init(sipc_kbd_monitor_init);
module_exit(sipc_kbd_monitor_exit);

MODULE_DESCRIPTION("Spreadtrum SIPC Monitor");
MODULE_AUTHOR("Peiming Li <peiming.li@spreadtrum.com>");
MODULE_LICENSE("GPL");
