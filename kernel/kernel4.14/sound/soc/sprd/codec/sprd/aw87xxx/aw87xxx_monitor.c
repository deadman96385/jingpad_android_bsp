/*
 * aw87xxx_monitor.c  aw87xxx pa module
 *
 * Copyright (c) 2020 AWINIC Technology CO., LTD
 *
 * Author: Alex <zhangpengbiao@awinic.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/power_supply.h>
#include <linux/of.h>
#include <linux/power_supply.h>
#include <linux/hrtimer.h>
#include <linux/i2c.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/firmware.h>
#include <linux/platform_device.h>
#include <linux/proc_fs.h>
#include <linux/io.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/dma-mapping.h>
#include <linux/gameport.h>
#include <linux/moduleparam.h>
#include <linux/mutex.h>
#include <linux/workqueue.h>
#include "aw87xxx.h"
#include "aw87xxx_monitor.h"

static const uint32_t PARAM_ID_INDEX_TABLE[][INDEX_PARAMS_ID_MAX] = {
	{
	 AFE_PARAM_ID_AWDSP_RX_PARAMS,
	 AFE_PARAM_ID_AWDSP_RX_SET_ENABLE,
	 AFE_PARAM_ID_AWDSP_TX_SET_ENABLE,
	 AFE_PARAM_ID_AWDSP_RX_VMAX_L,
	 AFE_PARAM_ID_AWDSP_RX_CALI_CFG_L,
	 AFE_PARAM_ID_AWDSP_RX_RE_L,
	 AFE_PARAM_ID_AWDSP_RX_NOISE_L,
	 AFE_PARAM_ID_AWDSP_RX_F0_L,
	 AFE_PARAM_ID_AWDSP_RX_REAL_DATA_L,
	 },
	{
	 AFE_PARAM_ID_AWDSP_RX_PARAMS,
	 AFE_PARAM_ID_AWDSP_RX_SET_ENABLE,
	 AFE_PARAM_ID_AWDSP_TX_SET_ENABLE,
	 AFE_PARAM_ID_AWDSP_RX_VMAX_R,
	 AFE_PARAM_ID_AWDSP_RX_CALI_CFG_R,
	 AFE_PARAM_ID_AWDSP_RX_RE_R,
	 AFE_PARAM_ID_AWDSP_RX_NOISE_R,
	 AFE_PARAM_ID_AWDSP_RX_F0_R,
	 AFE_PARAM_ID_AWDSP_RX_REAL_DATA_R,
	 },
};

static int mtk_spk_send_ipi_buf_to_dsp(void *data_buffer, int32_t data_size)
{
	int *ret = (int *)data_buffer;

	pr_info("%s enter 0x%x\n", __func__, ret[6]);

	return 0;
}

static int
mtk_spk_recv_ipi_buf_from_dsp(int8_t *buffer, int16_t size, int32_t *buf_len)
{
	pr_info("%s enter\n", __func__);
	return 0;
}

static DEFINE_MUTEX(g_msg_dsp_lock);

static int aw_get_params_id_by_index(int index, int32_t *params_id,
				     int32_t channel)
{
	if (index > INDEX_PARAMS_ID_MAX || channel > 1) {
		pr_err("%s: error: index is %d, channel %d\n",
		       __func__, index, channel);
		return -EINVAL;
	}
	*params_id = PARAM_ID_INDEX_TABLE[channel][index];
	return 0;
}

int aw_write_data_to_dsp(int index, void *data, int len, int32_t channel)
{
	int ret;
	int32_t param_id;
	uint32_t real_len;
	mtk_dsp_hdr_t *hdr = (mtk_dsp_hdr_t *) data;

	ret = aw_get_params_id_by_index(index, &param_id, channel);
	if (ret < 0)
		return ret;

	real_len = len + sizeof(mtk_dsp_hdr_t);

	hdr->params_id = param_id;
	hdr->type = MTK_DSP_MSG_TYPE_DATA;

	ret = mtk_spk_send_ipi_buf_to_dsp(data, real_len);
	if (ret < 0)
		return ret;

	return 0;
}

int aw_read_data_to_dsp(int index, void *data, int len, int32_t channel)
{
	int ret;
	int32_t param_id;
	uint32_t real_len = len;
	mtk_dsp_hdr_t hdr;

	ret = aw_get_params_id_by_index(index, &param_id, channel);
	if (ret < 0)
		return ret;

	mutex_lock(&g_msg_dsp_lock);
	hdr.type = MTK_DSP_MSG_TYPE_CMD;
	hdr.params_id = param_id;

	ret = mtk_spk_send_ipi_buf_to_dsp(&hdr, sizeof(mtk_dsp_hdr_t));
	if (ret < 0)
		goto failed;

	ret = mtk_spk_recv_ipi_buf_from_dsp(data, len, &real_len);
	if (ret < 0)
		goto failed;

	mutex_unlock(&g_msg_dsp_lock);
	return 0;

 failed:
	mutex_unlock(&g_msg_dsp_lock);
	return ret;
}

int aw_get_vmax_from_dsp(uint32_t *vmax, int32_t channel)
{
	if (channel >= 2) {
		pr_err("%s: algo only support double PA channel:%d unsupport\n",
		       __func__, channel);
		return -EINVAL;
	} else {
		return aw_read_data_to_dsp(INDEX_PARAMS_ID_RX_VMAX,
					   (void *)vmax, sizeof(uint32_t),
					   channel);
	}
}

int aw_set_vmax_to_dsp(uint32_t vmax, int32_t channel)
{
	uint32_t vmax_hdr[7] = { 0 };

	vmax_hdr[6] = vmax;

	if (channel >= 2) {
		pr_err("%s: algo only support double PA channel:%d unsupport\n",
		       __func__, channel);
		return -EINVAL;
	} else {
		return aw_write_data_to_dsp(INDEX_PARAMS_ID_RX_VMAX,
					    (void *)vmax_hdr, sizeof(uint32_t),
					    channel);
	}
}

/****************************************************************************
* aw87xxx get battery capacity
*****************************************************************************/
int aw87xxx_get_battery_capacity(struct aw87xxx *aw87xxx,
				 uint32_t *vbat_capacity)
{
	char name[] = "battery";
	int ret;
	union power_supply_propval prop = { 0 };
	struct power_supply *psy = NULL;

	aw_dev_info(aw87xxx->dev, "%s:enter\n", __func__);
	psy = power_supply_get_by_name(name);
	if (psy) {
		ret = power_supply_get_property(psy,
						POWER_SUPPLY_PROP_CAPACITY,
						&prop);
		if (ret < 0) {
			aw_dev_err(aw87xxx->dev,
				   "%s: get vbat capacity failed\n", __func__);
			return -EINVAL;
		}
		*vbat_capacity = prop.intval;
		aw_dev_info(aw87xxx->dev, "The percentage is %d\n",
			    *vbat_capacity);
	} else {
		aw_dev_err(aw87xxx->dev, "no struct power supply name :%s",
			   name);
		return -EINVAL;
	}
	return 0;
}

/*****************************************************
 * aw87xxx monitor control
*****************************************************/
void aw87xxx_monitor_stop(struct aw87xxx_monitor *monitor)
{
	struct aw87xxx *aw87xxx = container_of(monitor,
					       struct aw87xxx, monitor);

	aw_dev_info(aw87xxx->dev, "%s enter\n", __func__);

	if (hrtimer_active(&aw87xxx->monitor.timer)) {
		aw_dev_info(aw87xxx->dev, "%s: cancel monitor\n", __func__);
		hrtimer_cancel(&aw87xxx->monitor.timer);
	}

}

static int aw87xxx_monitor_start(struct aw87xxx_monitor *monitor)
{
	int timer_val = 0;
	struct aw87xxx *aw87xxx = container_of(monitor,
					       struct aw87xxx, monitor);

	aw_dev_info(aw87xxx->dev, "%s enter\n", __func__);

	timer_val = aw87xxx->monitor.timer_val;

	if (hrtimer_active(&aw87xxx->monitor.timer)) {
		aw_dev_dbg(aw87xxx->dev, "%s: monitor already start\n",
			   __func__);
	} else {
		aw_dev_dbg(aw87xxx->dev, "%s: start monitor, hrtimer = %d\n",
			   __func__, timer_val);
		hrtimer_start(&aw87xxx->monitor.timer,
			      ktime_set(timer_val / 1000,
					(timer_val % 1000) * 1000000),
			      HRTIMER_MODE_REL);
	}
	return 0;
}

static enum hrtimer_restart aw87xxx_monitor_timer_func(struct hrtimer *timer)
{
	struct aw87xxx *aw87xxx = container_of(timer,
					       struct aw87xxx, monitor.timer);

	aw_dev_dbg(aw87xxx->dev, "%s enter\n", __func__);

	schedule_work(&aw87xxx->monitor.work);

	return HRTIMER_NORESTART;
}

static int aw87xxx_vbat_monitor_update_vmax(struct aw87xxx *aw87xxx,
					    int vbat_vol)
{
	int ret = -1;
	int i = 0;
	uint32_t vmax_flag = 0;
	uint32_t vmax_set = 0;
	struct aw87xxx_monitor *monitor = NULL;

	monitor = &aw87xxx->monitor;

	for (i = 0; i < monitor->vmax_cfg->vmax_cfg_num; i++) {
		if (vbat_vol > monitor->vmax_cfg->vmax_cfg_total[i].min_thr) {
			vmax_set = monitor->vmax_cfg->vmax_cfg_total[i].vmax;
			vmax_flag = 1;
			aw_dev_dbg(aw87xxx->dev,
				   "%s: read setting vmax=0x%x, step[%d]: min_thr=%d\n",
				   __func__, vmax_set, i,
				   monitor->vmax_cfg->vmax_cfg_total[i].
				   min_thr);
			break;
		}
	}
	pr_info("%s:vmax_flag=%d\n", __func__, vmax_flag);
	if (vmax_flag) {
		if (monitor->pre_vmax != vmax_set) {
			ret = aw_set_vmax_to_dsp(vmax_set, aw87xxx->driver_num);
			if (ret) {
				aw_dev_err(aw87xxx->dev,
					   "%s: set dsp msg fail, ret=%d\n",
					   __func__, ret);
				return ret;
			} else {
				aw_dev_info(aw87xxx->dev,
					    "%s: set dsp vmax=0x%x sucess\n",
					    __func__, vmax_set);
				monitor->pre_vmax = vmax_set;
			}
		} else {
			aw_dev_info(aw87xxx->dev, "%s:vmax=0x%x no change\n",
				    __func__, vmax_set);
		}
	}
	return 0;
}

void aw87xxx_monitor_work_func(struct work_struct *work)
{
	int ret;
	uint32_t vbat_capacity;
	uint32_t ave_capacity;
	struct aw87xxx *aw87xxx = container_of(work,
					       struct aw87xxx, monitor.work);

	aw_dev_info(aw87xxx->dev, "%s: enter\n", __func__);

	ret = aw87xxx_get_battery_capacity(aw87xxx, &vbat_capacity);
	if (ret < 0)
		return;

	if (aw87xxx->monitor.timer_cnt < aw87xxx->monitor.timer_cnt_max) {
		aw87xxx->monitor.timer_cnt++;
		aw87xxx->monitor.vbat_sum += vbat_capacity;
	}
	if ((aw87xxx->monitor.timer_cnt == aw87xxx->monitor.timer_cnt_max) ||
	    (aw87xxx->monitor.first_entry == AW_FIRST_ENTRY)) {

		if (aw87xxx->monitor.first_entry == AW_FIRST_ENTRY)
			aw87xxx->monitor.first_entry = AW_NOT_FIRST_ENTRY;

		ave_capacity = aw87xxx->monitor.vbat_sum /
		    aw87xxx->monitor.timer_cnt;

		if (aw87xxx->monitor.custom_capacity)
			ave_capacity = aw87xxx->monitor.custom_capacity;

		aw_dev_info(aw87xxx->dev, "%s: get average capacity = %d\n",
			    __func__, ave_capacity);

		aw87xxx_vbat_monitor_update_vmax(aw87xxx, ave_capacity);

		aw87xxx->monitor.timer_cnt = 0;
		aw87xxx->monitor.vbat_sum = 0;
	}
	aw87xxx_monitor_start(&aw87xxx->monitor);
}

/**********************************************************
 * aw873xx monitor attribute
***********************************************************/
static ssize_t aw87xxx_get_vbat(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	ssize_t len = 0;

	struct aw87xxx *aw87xxx = dev_get_drvdata(dev);
	len += snprintf(buf + len, PAGE_SIZE - len,
			"vbat capacity=%d\n", aw87xxx->monitor.custom_capacity);

	return len;
}

static ssize_t aw87xxx_set_vbat(struct device *dev,
				struct device_attribute *attr, const char *buf,
				size_t len)
{
	int ret = -1;
	uint32_t capacity;
	struct aw87xxx *aw87xxx = dev_get_drvdata(dev);

	if (len == 0)
		return 0;

	ret = kstrtouint(buf, 0, &capacity);
	if (ret < 0)
		return ret;
	aw_dev_info(aw87xxx->dev, "%s: set capacity = %d\n",
		    __func__, capacity);
	if (capacity >= AW87XXX_VBAT_CAPACITY_MIN &&
	    capacity <= AW87XXX_VBAT_CAPACITY_MAX)
		aw87xxx->monitor.custom_capacity = capacity;

	return len;
}

static ssize_t aw87xxx_get_vmax(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	ssize_t len = 0;
	uint32_t vmax_get = 0;
	int ret = -1;
	struct aw87xxx *aw87xxx = dev_get_drvdata(dev);

	ret = aw_get_vmax_from_dsp(&vmax_get, aw87xxx->driver_num);
	if (ret)
		aw_dev_err(aw87xxx->dev, "%s: get dsp vmax fail, ret = %d\n",
			   __func__, ret);
	else
		len += snprintf(buf + len, PAGE_SIZE - len,
				"get_vmax=0x%x\n", vmax_get);

	return len;
}

static ssize_t aw87xxx_set_vmax(struct device *dev,
				struct device_attribute *attr, const char *buf,
				size_t len)
{
	uint32_t vmax_set = 0;
	int ret = -1;
	struct aw87xxx *aw87xxx = dev_get_drvdata(dev);

	if (len == 0)
		return 0;

	ret = kstrtouint(buf, 0, &vmax_set);
	if (ret < 0)
		return ret;

	aw_dev_info(aw87xxx->dev, "%s: vmax_set=%d\n", __func__, vmax_set);

	ret = aw_set_vmax_to_dsp(vmax_set, aw87xxx->driver_num);
	if (ret)
		aw_dev_err(aw87xxx->dev, "%s: send dsp_msg error, ret = %d\n",
			   __func__, ret);

	mdelay(2);

	return len;
}

static ssize_t aw87xxx_get_monitor(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct aw87xxx *aw87xxx = dev_get_drvdata(dev);
	ssize_t len = 0;
	uint32_t local_enable;

	local_enable = aw87xxx->monitor.monitor_flag;
	len += snprintf(buf + len, PAGE_SIZE - len,
			"aw87xxx monitor enable: %d\n", local_enable);
	return len;
}

static ssize_t aw87xxx_set_monitor(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t count)
{
	struct aw87xxx *aw87xxx = dev_get_drvdata(dev);
	uint32_t enable = 0;
	int ret = -1;

	if (count == 0)
		return 0;

	ret = kstrtouint(buf, 0, &enable);
	if (ret < 0)
		return ret;

	aw_dev_info(aw87xxx->dev, "%s:monitor enable set =%d\n",
		    __func__, enable);
	aw87xxx->monitor.monitor_flag = enable;
	if (aw87xxx->monitor.monitor_flag &&
	    aw87xxx->current_mode != AW87XXX_RCV_MODE &&
	    aw87xxx->monitor.cfg_update_flag == AW87XXX_CFG_OK)
		aw87xxx_monitor_work_func(&aw87xxx->monitor.work);

	return count;
}

static ssize_t aw87xxx_get_vmax_time(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct aw87xxx *aw87xxx = dev_get_drvdata(dev);
	ssize_t len = 0;

	len += snprintf(buf + len, PAGE_SIZE - len,
			"aw87xxx_vmax_timer_val = %d\n",
			aw87xxx->monitor.timer_val);
	return len;
}

static ssize_t aw87xxx_set_vmax_time(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct aw87xxx *aw87xxx = dev_get_drvdata(dev);
	unsigned int timer_val = 0;
	int ret;

	ret = kstrtouint(buf, 0, &timer_val);
	if (ret < 0)
		return ret;
	pr_info("%s:timer_val =%d\n", __func__, timer_val);

	aw87xxx->monitor.timer_val = timer_val;

	return count;
}

static DEVICE_ATTR(vbat, S_IWUSR | S_IRUGO, aw87xxx_get_vbat, aw87xxx_set_vbat);
static DEVICE_ATTR(vmax, S_IWUSR | S_IRUGO, aw87xxx_get_vmax, aw87xxx_set_vmax);
static DEVICE_ATTR(monitor, S_IWUSR | S_IRUGO,
		   aw87xxx_get_monitor, aw87xxx_set_monitor);
static DEVICE_ATTR(vmax_time, S_IWUSR | S_IRUGO,
		   aw87xxx_get_vmax_time, aw87xxx_set_vmax_time);

static struct attribute *aw87xxx_monitor_attr[] = {
	&dev_attr_vbat.attr,
	&dev_attr_vmax.attr,
	&dev_attr_monitor.attr,
	&dev_attr_vmax_time.attr,
	NULL
};

static struct attribute_group aw87xxx_monitor_attr_group = {
	.attrs = aw87xxx_monitor_attr
};

/**********************************************************
 * aw87xxx monitor init
***********************************************************/
void aw87xxx_monitor_init(struct aw87xxx_monitor *monitor)
{
	int ret;
	struct aw87xxx *aw87xxx = container_of(monitor,
					       struct aw87xxx, monitor);

	aw_dev_info(aw87xxx->dev, "%s: enter\n", __func__);
	hrtimer_init(&monitor->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	monitor->timer.function = aw87xxx_monitor_timer_func;
	INIT_WORK(&monitor->work, aw87xxx_monitor_work_func);

	ret = sysfs_create_group(&aw87xxx->dev->kobj,
				 &aw87xxx_monitor_attr_group);
	if (ret < 0) {
		aw_dev_err(aw87xxx->dev,
			   "%s error creating monitor sysfs attr files\n",
			   __func__);
	}
}

void aw87xxx_parse_monitor_dt(struct aw87xxx_monitor *monitor)
{
	int ret;
	struct aw87xxx *aw87xxx = container_of(monitor,
					       struct aw87xxx, monitor);
	struct device_node *np = aw87xxx->dev->of_node;

	ret = of_property_read_u32(np, "monitor-flag", &monitor->monitor_flag);
	if (ret) {
		monitor->monitor_flag = AW87XXX_MONITOR_DEFAULT_FLAG;
		aw_dev_err(aw87xxx->dev,
			   "%s: monitor-flag get failed ,user default value!\n",
			   __func__);
	} else {
		aw_dev_info(aw87xxx->dev, "%s: monitor-flag = %d\n",
			    __func__, monitor->monitor_flag);
	}

	ret = of_property_read_u32(np, "monitor-timer-val",
				   &monitor->timer_val);
	if (ret) {
		monitor->timer_val = AW87XXX_MONITOR_DEFAULT_TIMER_VAL;
		aw_dev_err(aw87xxx->dev,
			   "%s: monitor-timer-val get failed,user default value!\n",
			   __func__);
	} else {
		aw_dev_info(aw87xxx->dev, "%s: monitor-timer-val = %d\n",
			    __func__, monitor->timer_val);
	}

	ret = of_property_read_u32(np, "monitor-timer-count-max",
				   &monitor->timer_cnt_max);
	if (ret) {
		monitor->timer_cnt_max = AW87XXX_MONITOR_DEFAULT_TIMER_COUNT;
		aw_dev_err(aw87xxx->dev,
			   "%s: monitor-timer-count-max get failed,user default config!\n",
			   __func__);
	} else {
		aw_dev_info(aw87xxx->dev, "%s: monitor-timer-count-max = %d\n",
			    __func__, monitor->timer_cnt_max);
	}
}
