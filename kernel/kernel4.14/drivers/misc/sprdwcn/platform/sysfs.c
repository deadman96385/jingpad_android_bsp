/*
 * This file is part of wcn sysfs debug
 */

#include <linux/kobject.h>
#include <linux/slab.h>
#include <misc/wcn_bus.h>

#ifdef CONFIG_WCN_PCIE
#include "pcie.h"
#endif
#include "sysfs.h"
#include "wcn_boot.h"
#include "wcn_dbg.h"
#include "wcn_glb.h"
#include "wcn_procfs.h"

void sysfs_at_cmd_cb(struct marlin_device *mdev)
{
	complete(&mdev->sysfs_info.cmd_completion);
}

void wcn_notify_fw_error(struct marlin_device *mdev, unsigned char *buf)
{
	struct device *dev = &mdev->pdev->dev;
	char *envp[3] = {
		[0] = "SOURCE=wcnmarlin",
		[1] = "EVENT=FW_ERROR",
		[2] = NULL,
	};
	WCN_ERR("Notify about firmware error\n");
	kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, envp);
}

static int wcn_send_atcmd(struct marlin_device *mdev,
			  void *cmd, unsigned char cmd_len,
			  void *response, unsigned int *response_len)
{
	struct mbuf_t *head, *tail;
	int num = 1;
	int ret;
	unsigned long timeleft;
#ifdef CONFIG_WCN_PCIE
	/* dma_buf for dma */
	static struct dma_buf dma_buf;
	static int at_buf_flag;
	struct wcn_pcie_info *pcie_dev;
#else
	/* common buf for kmalloc */
	unsigned char *com_buf = NULL;
#endif

#ifdef CONFIG_WCN_PCIE
	pcie_dev = get_wcn_device_info();
	if (!pcie_dev) {
		WCN_ERR("%s:PCIE device link error\n", __func__);
		return -1;
	}
#endif
	mutex_lock(&mdev->sysfs_info.mutex);
	ret = sprdwcn_bus_list_alloc(0, &head, &tail, &num);
	if (ret || head == NULL || tail == NULL) {
		WCN_ERR("%s:%d mbuf_link_alloc fail\n", __func__, __LINE__);
		mutex_unlock(&mdev->sysfs_info.mutex);
		return -1;
	}

#ifdef CONFIG_WCN_PCIE
	if (at_buf_flag == 0) {
		ret = dmalloc(pcie_dev, &dma_buf, 128);
		if (ret != 0) {
			mutex_unlock(&mdev->sysfs_info.mutex);
			return -1;
		}
		at_buf_flag = 1;
	}
	head->buf = (unsigned char *)(dma_buf.vir);
	head->phy = (unsigned long)(dma_buf.phy);
	head->len = dma_buf.size;
	memset(head->buf, 0x0, head->len);
	memcpy(head->buf, cmd, cmd_len);
	head->next = NULL;
#else
	com_buf = kzalloc(128 + PUB_HEAD_RSV + 1, GFP_KERNEL);
	if (!com_buf) {
		mutex_unlock(&mdev->sysfs_info.mutex);
		return -ENOMEM;
	}
	memcpy(com_buf + PUB_HEAD_RSV, cmd, cmd_len);
	head->buf = com_buf;
	head->len = cmd_len;
	head->next = NULL;
#endif
	ret = sprdwcn_bus_push_list(0, head, tail, num);
	if (ret)
		WCN_INFO("sprdwcn_bus_push_list error=%d\n", ret);
	reinit_completion(&mdev->sysfs_info.cmd_completion);
	timeleft = wait_for_completion_timeout(&mdev->sysfs_info.cmd_completion,
					       3 * HZ);
	if (!timeleft) {
		WCN_ERR("%s,Timeout(%d sec),didn't get at cmd(%s) response\n",
			__func__, jiffies_to_msecs(3*HZ) / 1000, (char *)cmd);
		mutex_unlock(&mdev->sysfs_info.mutex);
		return -ETIMEDOUT;
	}
	if (!response) {
		mutex_unlock(&mdev->sysfs_info.mutex);
		return 0;
	}

	*response_len = mdev->sysfs_info.len;
	scnprintf(response, (size_t)mdev->sysfs_info.len, "%s\n",
		  (char *)mdev->sysfs_info.p);
	WCN_INFO("len=0x%x, buf=%s\n", *response_len, (char *)(response));
	mutex_unlock(&mdev->sysfs_info.mutex);

	return 0;
}

static ssize_t wcn_sysfs_show_sleep_state(struct device *dev,
					  struct device_attribute *attr,
					  char *buf)
{
	return scnprintf(buf, PAGE_SIZE, "%s\n", "not support to read");
}

static ssize_t wcn_sysfs_store_sleep_state(struct device *dev,
					     struct device_attribute *attr,
					     const char *buf, size_t count)
{
	struct marlin_device *mdev = dev_get_drvdata(dev);
	unsigned long res;
	int ret;
	char a[64];

	ret = kstrtoul(buf, 10, &res);
	if (ret < 0) {
		WCN_ERR("incorrect value written to sleep\n");
		return -EINVAL;
	}

	if (res == 1) {
		/* close CP2 sleep function */
		scnprintf(a, (size_t)sizeof(a), "%s\n", "at+debug=1\r\n");
		wcn_send_atcmd(mdev, a, sizeof(a), NULL, NULL);
	} else if (res == 0) {
		/* open CP2 sleep function */
		scnprintf(a, (size_t)sizeof(a), "%s\n", "at+debug=0\r\n");
		wcn_send_atcmd(mdev, a, sizeof(a), NULL, NULL);
	} else {
		WCN_ERR("incorrect value written to sleep\n");
		return -EINVAL;
	}

	return count;
}

/* S_IRUGO | S_IWUSR */
static DEVICE_ATTR(sleep_state, 0644,
		   wcn_sysfs_show_sleep_state,
		   wcn_sysfs_store_sleep_state);

static ssize_t wcn_sysfs_show_sw_ver(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	ssize_t len = 0;
	struct marlin_device *mdev = dev_get_drvdata(dev);
	char a[] = "at+spatgetcp2info\r\n";

	/*
	 * len is 64bit, belows function 32bit, need assigned 0 to len,
	 * make sure high 32bit=0
	 */
	wcn_send_atcmd(mdev, a, sizeof(a), buf, (unsigned int *)&len);

	WCN_INFO("show:len=%zd, buf=%s\n", len, buf);
	/* because cp2 pass wrong len */
	len = strlen(buf);
	WCN_INFO("show:len=%zd\n", len);

	return len;
}

/* S_IRUGO */
static DEVICE_ATTR(sw_ver, 0444,
		   wcn_sysfs_show_sw_ver, NULL);

static ssize_t wcn_sysfs_read_fwlog(struct file *filp, struct kobject *kobj,
				    struct bin_attribute *bin_attr,
				    char *buffer, loff_t pos, size_t count)
{
	return 0;
}

/* S_IRUSR */
static const struct bin_attribute fwlog_attr = {
	.attr = {.name = "fwlog", .mode = 0400},
	.read = wcn_sysfs_read_fwlog,
};

static ssize_t wcn_sysfs_show_hw_ver(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct marlin_device *mdev  = dev_get_drvdata(dev);
	ssize_t len;

	len = PAGE_SIZE;
	mutex_lock(&mdev->sysfs_info.mutex);
	if (wcn_get_chip_name())
		len = snprintf(buf, len, "%s\n", wcn_get_chip_name());
	else
		/* len:4 */
		len = snprintf(buf, len, "n/a\n");
	mutex_unlock(&mdev->sysfs_info.mutex);

	return len;
}

static ssize_t wcn_sysfs_store_hw_ver(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	return count;
}

static DEVICE_ATTR(hw_ver, 0644,
		   wcn_sysfs_show_hw_ver,
		   wcn_sysfs_store_hw_ver);

static ssize_t wcn_sysfs_show_watchdog_state(struct device *dev,
					     struct device_attribute *attr,
					     char *buf)
{
	struct marlin_device *mdev  = dev_get_drvdata(dev);
	ssize_t len;

	len = PAGE_SIZE;
	mutex_lock(&mdev->sysfs_info.mutex);

	/* len:4 */
	len = snprintf(buf, len, "not support\n");
	mutex_unlock(&mdev->sysfs_info.mutex);

	return len;
}

static ssize_t wcn_sysfs_store_watchdog_state(struct device *dev,
					      struct device_attribute *attr,
					      const char *buf, size_t count)
{
	ssize_t len = 0;
	struct marlin_device *mdev = dev_get_drvdata(dev);
	char a[] = "at+cp2_enter_user=?\r\n";

	WCN_INFO("%s: buf=%s\n", __func__, buf);

	if (strncmp(buf, "1", 1) == 0) {
		scnprintf(a, (size_t)sizeof(a), "%s\n",
			  "at+cp2_enter_user=1\r\n");
		wcn_send_atcmd(mdev, a, sizeof(a), NULL, NULL);
	} else if (strncmp(buf, "0", 1) == 0) {
		scnprintf(a, (size_t)sizeof(a), "%s\n",
			  "at+cp2_enter_user=0\r\n");
		wcn_send_atcmd(mdev, a, sizeof(a), NULL, NULL);
	} else
		return -EINVAL;

	len = strlen(buf);
	WCN_INFO("show:len=%zd, count=%zd\n", len, count);

	return count;
}

static DEVICE_ATTR(watchdog_state, 0644,
		   wcn_sysfs_show_watchdog_state,
		   wcn_sysfs_store_watchdog_state);

static ssize_t wcn_sysfs_show_armlog_status(struct device *dev,
					    struct device_attribute *attr,
					    char *buf)
{
	ssize_t len = 0;
	struct marlin_device *mdev = dev_get_drvdata(dev);
	char a[] = "at+armlog?\r\n";

	wcn_send_atcmd(mdev, a, sizeof(a), buf, (unsigned int *)&len);

	WCN_INFO("%s:len=%zd, buf=%s\n", __func__, len, buf);
	len = strlen(buf);
	WCN_INFO("show:len=%zd\n", len);

	return len;
}

static ssize_t wcn_sysfs_store_armlog_status(struct device *dev,
					     struct device_attribute *attr,
					     const char *buf, size_t count)
{
	struct marlin_device *mdev = dev_get_drvdata(dev);
	unsigned long res;
	int ret;
	char a[64];

	ret = kstrtoul(buf, 10, &res);
	if (ret < 0) {
		WCN_ERR("incorrect value written to sleep\n");
		return -EINVAL;
	}

	if (res == 1) {
		/* close CP2 sleep function */
		scnprintf(a, (size_t)sizeof(a), "%s\n", "at+armlog=1\r\n");
		wcn_send_atcmd(mdev, a, sizeof(a), NULL, NULL);
	} else if (res == 0) {
		/* open CP2 sleep function */
		scnprintf(a, (size_t)sizeof(a), "%s\n", "at+armlog=1\r\n");
		wcn_send_atcmd(mdev, a, sizeof(a), NULL, NULL);
	} else {
		WCN_ERR("incorrect value written to sleep\n");
		return -EINVAL;
	}

	return count;
}

static DEVICE_ATTR(armlog_status, 0644,
		   wcn_sysfs_show_armlog_status,
		   wcn_sysfs_store_armlog_status);

static ssize_t wcn_sysfs_show_loglevel(struct device *dev,
				       struct device_attribute *attr,
				       char *buf)
{
	ssize_t len = 0;
	struct marlin_device *mdev = dev_get_drvdata(dev);
	char a[] = "at+loglevel?\r\n";

	wcn_send_atcmd(mdev, a, sizeof(a), buf, (unsigned int *)&len);

	WCN_INFO("%s:len=%zd, buf=%s\n", __func__, len, buf);
	len = strlen(buf);
	WCN_INFO("show:len=%zd\n", len);

	return len;
}

static ssize_t wcn_sysfs_store_loglevel(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t count)
{
	struct marlin_device *mdev = dev_get_drvdata(dev);
	unsigned long res;
	int ret;
	char a[64];

	ret = kstrtoul(buf, 10, &res);
	if (ret < 0) {
		WCN_ERR("incorrect value written to sleep\n");
		return -EINVAL;
	}

	if (res < 6) {
		/* close CP2 sleep function */
		scnprintf(a, (size_t)sizeof(a), "%s%ld%s\n", "at+armlog=",
			  res, "\r\n");
		WCN_INFO("%s:buf=%s\n", __func__, a);
		wcn_send_atcmd(mdev, a, sizeof(a), NULL, NULL);
	} else {
		WCN_ERR("incorrect value written to sleep\n");
		return -EINVAL;
	}

	return count;
}

static DEVICE_ATTR(loglevel, 0644,
		   wcn_sysfs_show_loglevel,
		   wcn_sysfs_store_loglevel);

static ssize_t wcn_sysfs_show_reset_dump(struct device *dev,
					 struct device_attribute *attr,
					 char *buf)
{
	ssize_t len = PAGE_SIZE;

#ifdef CONFIG_WCN_USER
	len = snprintf(buf, len, "reset\n");
#else
	len = snprintf(buf, len, "dump\n");
#endif

	return len;
}

static ssize_t wcn_sysfs_store_reset_dump(struct device *dev,
					  struct device_attribute *attr,
					  const char *buf, size_t count)
{
	WCN_INFO("%s: buf=%s\n", __func__, buf);

	if (strncmp(buf, "reset", 5) == 0) {
		//TODO: define for next
		;
	} else if (strncmp(buf, "dump", 4) == 0) {
		//TODO: define for next
		;
	} else
		return -EINVAL;

	return count;
}

static DEVICE_ATTR(reset_dump, 0644,
		   wcn_sysfs_show_reset_dump,
		   wcn_sysfs_store_reset_dump);


/*
 * ud710_3h10:/sys/devices/platform/sprd-marlin3 # ls
 * sleep_state driver driver_override fwlog hw_pg_ver modalias of_node power
 * subsystem uevent
 */
int wcn_sysfs_init(struct marlin_device *mdev)
{
	int ret;

	/* Create sysfs file to control bt coex state */
	ret = device_create_file(&mdev->pdev->dev, &dev_attr_sleep_state);
	if (ret < 0) {
		WCN_ERR("failed to create sysfs file sleep_state\n");
		goto out;
	}

	/* Create sysfs file to get SW version */
	ret = device_create_file(&mdev->pdev->dev, &dev_attr_sw_ver);
	if (ret < 0) {
		WCN_ERR("failed to create sysfs file sw_ver\n");
		goto out_sleep_state;
	}

	/* Create sysfs file to get HW version(chipid) */
	ret = device_create_file(&mdev->pdev->dev, &dev_attr_hw_ver);
	if (ret < 0) {
		WCN_ERR("failed to create sysfs file hw_ver\n");
		goto out_sw_ver;
	}

	/* Create sysfs file to get watchdog status */
	ret = device_create_file(&mdev->pdev->dev, &dev_attr_watchdog_state);
	if (ret < 0) {
		WCN_ERR("failed to create sysfs file watchdog_state\n");
		goto out_hw_ver;
	}

	/* Create sysfs file to get/change armlog status */
	ret = device_create_file(&mdev->pdev->dev, &dev_attr_armlog_status);
	if (ret < 0) {
		WCN_ERR("failed to create sysfs file armlog_status\n");
		goto out_watchdog_state;
	}

	/* Create sysfs file to get/set loglevel */
	ret = device_create_file(&mdev->pdev->dev, &dev_attr_loglevel);
	if (ret < 0) {
		WCN_ERR("failed to create sysfs file armlog_status\n");
		goto out_armlog_status;
	}

	/*
	 * Create sysfs file to get TARGET_BUILD_VARIANT=userdebug for ap
	 * user: reset cp2
	 * userdebug: dumpmem
	 */
	ret = device_create_file(&mdev->pdev->dev, &dev_attr_reset_dump);
	if (ret < 0) {
		WCN_ERR("failed to create sysfs file userdebug\n");
		goto out_loglevel;
	}

	/* Create sysfs file for the FW log */
	ret = device_create_bin_file(&mdev->pdev->dev, &fwlog_attr);
	if (ret < 0) {
		WCN_ERR("failed to create sysfs file fwlog\n");
		goto out_reset_dump;
	}

	init_completion(&mdev->sysfs_info.cmd_completion);
	mutex_init(&mdev->sysfs_info.mutex);

	goto out;

out_reset_dump:
	device_remove_file(&mdev->pdev->dev, &dev_attr_reset_dump);

out_loglevel:
	device_remove_file(&mdev->pdev->dev, &dev_attr_loglevel);

out_armlog_status:
	device_remove_file(&mdev->pdev->dev, &dev_attr_armlog_status);

out_watchdog_state:
	device_remove_file(&mdev->pdev->dev, &dev_attr_watchdog_state);

out_hw_ver:
	device_remove_file(&mdev->pdev->dev, &dev_attr_hw_ver);

out_sw_ver:
	device_remove_file(&mdev->pdev->dev, &dev_attr_sw_ver);

out_sleep_state:
	device_remove_file(&mdev->pdev->dev, &dev_attr_sleep_state);

out:
	return ret;
}

void wcn_sysfs_free(struct marlin_device *mdev)
{
	device_remove_bin_file(&mdev->pdev->dev, &fwlog_attr);

	device_remove_file(&mdev->pdev->dev, &dev_attr_reset_dump);

	device_remove_file(&mdev->pdev->dev, &dev_attr_loglevel);

	device_remove_file(&mdev->pdev->dev, &dev_attr_armlog_status);

	device_remove_file(&mdev->pdev->dev, &dev_attr_watchdog_state);

	device_remove_file(&mdev->pdev->dev, &dev_attr_hw_ver);

	device_remove_file(&mdev->pdev->dev, &dev_attr_sw_ver);

	device_remove_file(&mdev->pdev->dev, &dev_attr_sleep_state);
}
