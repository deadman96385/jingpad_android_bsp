/*
 * SPRD external modem control driver in AP side.
 *
 * Copyright (C) 2019 Spreadtrum Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 of
 * the License as published by the Free Software Foundation.
 *
 * This program is used to control external modem in AP side for
 * Spreadtrum SoCs.
 */

#include <linux/cdev.h>
#include <linux/completion.h>
#include <linux/dmaengine.h>
#include <linux/dma-mapping.h>
#include <linux/dma/sprd-dma.h>
#include <linux/kernel.h>
#include <linux/mdm_ctrl.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/of_device.h>
#include <linux/of_dma.h>
#include <linux/of_address.h>
#include <linux/poll.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/sipc.h>
#include <linux/mfd/syscon.h>
#include <linux/regmap.h>
#include <linux/debugfs.h>
#include <linux/gpio/consumer.h>

#ifdef CONFIG_SPRD_PCIE_EP_DEVICE
#include <linux/soc/sprd/sprd_pcie_ep_device.h>
#include "../include/sprd_pcie_resource.h"
#endif

#include "sprd_modem_loader.h"

/* modem io cmd */
#define MODEM_MAGIC 'M'

#define MODEM_READ_LOCK_CMD _IO(MODEM_MAGIC, 0x1)
#define MODEM_READ_UNLOCK_CMD _IO(MODEM_MAGIC, 0x2)

#define MODEM_WRITE_LOCK_CMD _IO(MODEM_MAGIC, 0x3)
#define MODEM_WRITE_UNLOCK_CMD _IO(MODEM_MAGIC, 0x4)

#define MODEM_GET_LOAD_INFO_CMD _IOR(MODEM_MAGIC, 0x5, struct modem_load_info)
#define MODEM_SET_LOAD_INFO_CMD _IOW(MODEM_MAGIC, 0x6, struct modem_load_info)

#define MODEM_SET_READ_REGION_CMD _IOR(MODEM_MAGIC, 0x7, int)
#define MODEM_SET_WRITE_GEGION_CMD _IOW(MODEM_MAGIC, 0x8, int)

#ifdef CONFIG_SPRD_EXT_MODEM
#define MODEM_GET_REMOTE_FLAG_CMD _IOR(MODEM_MAGIC, 0x9, int)
#define MODEM_SET_REMOTE_FLAG_CMD _IOW(MODEM_MAGIC, 0xa, int)
#define MODEM_CLR_REMOTE_FLAG_CMD _IOW(MODEM_MAGIC, 0xb, int)
#endif

#define MODEM_STOP_CMD _IO(MODEM_MAGIC, 0xc)
#define MODEM_START_CMD _IO(MODEM_MAGIC, 0xd)
#define MODEM_ASSERT_CMD _IO(MODEM_MAGIC, 0xe)

#define MODEM_REBOOT_EXT_MODEM_CMD _IO(MODEM_MAGIC, 0xf)
#define MODEM_POWERON_EXT_MODEM_CMD _IO(MODEM_MAGIC, 0x10)
#define MODEM_POWEROFF_EXT_MODEM_CMD _IO(MODEM_MAGIC, 0x11)
#define MODEM_ENTER_SLEEP_CMD _IO(MODEM_MAGIC, 0x12)

#define	MODEM_READ_ALL_MEM 0xff
#define	MODEM_READ_MODEM_MEM 0xfe
#define RUN_STATE_INVALID 0xff

#define SRPD_DMA_MAX_SIZE	(0x400000)
#define SRPD_DMA_FAST_SIZE	(0x100000)

enum {
	SPRD_5G_MODEM_DP = 0,
	SPRD_5G_MODEM_PS,
	SPRD_5G_MODEM_NR_PHY,
	SPRD_5G_MODEM_V3_PHY,
	SPRD_5G_MODEM_CNT
};

enum {
	SPRD_4G_MODEM_PM = 0,
	SPRD_4G_MODEM_PUBCP,
	SPRD_4G_MODEM_CNT,
};

struct modem_data {
	char	*name;
	u32	dst;
};

#ifdef CONFIG_SPRD_EXT_MODEM
const struct ext_modem_operations *ext_modem_ops;
#endif

static const char *modem_ctrl_args[MODEM_CTRL_NR] = {
	"shutdown",
	"deepsleep",
	"corereset",
	"sysreset",
	"getstatus"
};

#ifdef CONFIG_SPRD_EXT_MODEM
/* the external modem, all comunacate with SIPC_ID_MINIAP */
static const struct modem_data modem_5g[SPRD_5G_MODEM_CNT] = {
	{"dpsys", SIPC_ID_MINIAP},
	{"modem", SIPC_ID_MINIAP},
	{"nrphy", SIPC_ID_MINIAP},
	{"v3phy", SIPC_ID_MINIAP}
};
#else
static const struct modem_data modem_5g[SPRD_5G_MODEM_CNT] = {
	{"dpsys", SIPC_ID_PM_SYS},
	{"modem", SIPC_ID_PSCP},
	{"nrphy", SIPC_ID_NR_PHY},
	{"v3phy", SIPC_ID_V3_PHY}
};
#endif

static const struct modem_data modem_4g[SPRD_4G_MODEM_CNT] = {
	{"pmsys", SIPC_ID_PM_SYS},
	{"pubcp", SIPC_ID_PSCP}
};

typedef int (*MODEM_PARSE_FUN)(struct modem_device *modem,
			       struct device_node *np);

static struct class *modem_class;

#ifdef CONFIG_SPRD_EXT_MODEM
static void modem_get_remote_flag(struct modem_device *modem)
{
	ext_modem_ops->get_remote_flag(modem);
	dev_dbg(modem->p_dev, "get remote flag = 0x%x!\n", modem->remote_flag);
}

static void modem_set_remote_flag(struct modem_device *modem, u8 b_clear)
{
	ext_modem_ops->set_remote_flag(modem, b_clear);
	dev_dbg(modem->p_dev, "set remote flag = 0x%x, b_clear = %d!\n",
		 modem->remote_flag, b_clear);
}

static int modem_reboot_ext_modem(struct modem_device *modem, u8 b_reset)
{
#ifdef CONFIG_SPRD_PCIE_EP_DEVICE
	if (modem->modem_type == PCIE_MODEM)
		sprd_pcie_resource_reboot_ep(modem->modem_dst, false);
#endif

#ifdef CONFIG_SPRD_EXT_MODEM_POWER_CTRL
	return ext_modem_ops->reboot(modem, b_reset);
#else
	return 0;
#endif
}

static int modem_poweroff_ext_modem(struct modem_device *modem)
{
#ifdef CONFIG_SPRD_EXT_MODEM_POWER_CTRL
	return ext_modem_ops->poweroff(modem);
#else
	return 0;
#endif
}
#endif

static int modem_enter_sleep(struct modem_device *modem)
{
	int ret = sprd_mpm_disable_later_idle_for_sleep(modem->modem_dst);

	dev_info(modem->p_dev, "modem enter sleep, ret=%d!\n", ret);
	return ret;
}

static int modem_open(struct inode *inode, struct file *filp)
{
	struct modem_device *modem;

	modem = container_of(inode->i_cdev, struct modem_device, cdev);
	filp->private_data = modem;

	return 0;
}

static int modem_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static void modem_get_base_range(struct modem_device *modem,
				 phys_addr_t *p_base,
				 size_t *p_size, int b_read_region)
{
	phys_addr_t base = 0;
	size_t size = 0;
	u8 index;
	struct modem_region_info *region;

	index = b_read_region ? modem->read_region : modem->write_region;
	if (b_read_region) {
		switch (modem->read_region) {
		case MODEM_READ_ALL_MEM:
			base = modem->all_base;
			size = modem->all_size;
			break;

		case MODEM_READ_MODEM_MEM:
			base = modem->modem_base;
			size = modem->modem_size;
			break;

		default:
			if (index < modem->load->region_cnt) {
				region = &modem->load->regions[index];
				base = region->address;
				size = region->size;
			}
			break;
		}
	} else if (index < MAX_REGION_CNT) {
		region = &modem->load->regions[index];
		base = region->address;
		size = region->size;
	}

	dev_info(modem->p_dev, "get base 0x%llx, size = 0x%lx!\n", base, size);

	*p_base = base;
	*p_size = size;
}

static void *modem_map_memory(struct modem_device *modem, phys_addr_t start,
			      size_t size, size_t *map_size_ptr)
{
	size_t map_size = size;
	void *map;

	do {
		map_size = PAGE_ALIGN(map_size);
		if (map_size == 0)
			return NULL;

		map = modem_ram_vmap_nocache(modem->modem_type,
					     start, map_size);
		if (map) {
			if (map_size_ptr)
				*map_size_ptr = map_size;

			return map;
		}
		map_size /= 2;
	} while (map_size >= PAGE_SIZE);

	return NULL;
}

static int modem_request_pms(struct modem_device *modem, struct sprd_pms *pms)
{
	int ret;

	if (modem->modem_type == PCIE_MODEM &&
	    sprd_pcie_is_defective_chip()) {
		/* In this case, pcie need split bar,
		 * It has 2 times pcie scan action in host side boot process.
		 * After the first scan, the ep only have 2 bar can be used
		 * for memory map, the pcie resource is not completely ready.
		 * The api sprd_pms_request_resource(pms, -1) will return
		 * until the 2th scan action complete, and the ep will have
		 * 4 bar can be used for memory map. but the ep bar can only
		 * be split by the modem, so we can't used the commom api
		 * sprd_pms_wait_resource here.
		 * For workaroud this issue, we add a special api
		 * sprd_pcie_wait_load_resource, this api will return after
		 * the first pcie scan action, and in here we use it.
		 */
		sprd_pms_power_up(pms);
		ret = sprd_pcie_wait_load_resource(modem->modem_dst);
		dev_info(modem->p_dev,
			 "pms, wait load ret =%d\n", ret);
	} else {
		/* must request resource before read or write ep memory */
		ret = sprd_pms_request_resource(pms, -1);
	}

	return ret;
}

static int modem_rescan_pcie(struct modem_device *modem, struct sprd_pms *pms)
{
	int ret;
	int cnt = 10;

	sprd_pcie_resource_reboot_ep(modem->modem_dst, true);

	/* first, wait pcie resource. */
	ret = sprd_pcie_wait_load_resource(modem->modem_dst);
	if (ret != 0) {
		dev_info(modem->p_dev, "lock, wait load ret =%d\n", ret);
		return ret;
	}

	sprd_pms_power_up(pms);

	ret = -ETIME;
	/* than, wait ep ddr ready. */
	while (cnt--) {
		modem_get_remote_flag(modem);
		/* wait the ep set REMOTE_DDR_READY_FLAG. */
		if (modem->remote_flag & REMOTE_DDR_READY_FLAG) {
			ret = 0;
			break;
		}
		msleep(100);
	}
	sprd_pms_power_down(pms, false);

	return ret;
}

static void modem_dma_copy_complete(void *data)
{
	struct dma_copy_data *dma_ptr = data;

	dev_dbg(dma_ptr->p_dev, "%s dma copy complete!\n", dma_ptr->dma_name);
	complete(&dma_ptr->dma_comp);
}

static void modem_dma_free_mem(struct dma_copy_data *dma_ptr)
{
	if (dma_ptr && dma_ptr->buf_v) {
		dma_free_coherent(dma_ptr->p_dev, dma_ptr->dma_size,
				  dma_ptr->buf_v, dma_ptr->buf_p);
		dma_ptr->buf_v = NULL;
		dma_ptr->buf_p = 0;
		dma_ptr->dma_size = 0;
	}
}

static size_t modem_dma_alloc(struct dma_copy_data *dma_ptr, size_t dma_size)
{
	size_t size = dma_size;
	size_t max_size;
	bool update_try_size = false;

	max_size = (dma_ptr->try_size > 0) ?
		dma_ptr->try_size : SRPD_DMA_MAX_SIZE;

	if (size > max_size) {
		size = max_size;
		update_try_size = true;
	}

	do {
		/* if size < PAGE_SIZE, don't copy with dma. */
		dev_dbg(dma_ptr->p_dev, "%s alloc size = 0x%lx!\n",
			dma_ptr->dma_name,
			(unsigned long)size);

		size = size & ~(PAGE_SIZE - 1);
		if (size == 0)
			break;

		dma_ptr->buf_v = dma_zalloc_coherent(dma_ptr->p_dev,
						     size,
						     &dma_ptr->buf_p,
						     GFP_KERNEL);
		if (dma_ptr->buf_v) {
			dma_ptr->dma_size = size;
			if (update_try_size)
				dma_ptr->try_size = size;
			return size;
		}

		if (size <= SRPD_DMA_FAST_SIZE)
			break;

		size -= SRPD_DMA_FAST_SIZE;
	} while (size > SRPD_DMA_FAST_SIZE);

	return 0;
}

static size_t modem_dma_copy(struct dma_copy_data *dma_ptr,
			  size_t dma_size,
			  dma_addr_t src_buf,
			  dma_addr_t dst_buf)
{
	enum dma_status dma_s = DMA_ERROR;
	struct dma_tx_state dma_tx_s;
	struct dma_async_tx_descriptor *tx;
	dma_cookie_t cookie;
	dma_cap_mask_t mask;

	dev_dbg(dma_ptr->p_dev, "%s dma copy! src_buf = 0x%lx, dst_buf = 0x%lx!\n",
		dma_ptr->dma_name,
		(unsigned long)src_buf,
		(unsigned long)dst_buf);

	dma_cap_zero(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	tx = dmaengine_prep_dma_memcpy(dma_ptr->dma_chn, dst_buf,
				       src_buf, dma_size, 0);
	if (!tx) {
		dev_err(dma_ptr->p_dev, "%s dma get descriptor failed!\n",
			dma_ptr->dma_name);
		return 0;
	}

	dev_dbg(dma_ptr->p_dev, "%s dma copy submit!\n", dma_ptr->dma_name);

	tx->callback = modem_dma_copy_complete;
	tx->callback_param = dma_ptr;
	cookie = dmaengine_submit(tx);
	if (dma_submit_error(cookie)) {
		dev_err(dma_ptr->p_dev, "%s submit failed!\n",
			dma_ptr->dma_name);
		return 0;
	}

	dma_async_issue_pending(dma_ptr->dma_chn);
	wait_for_completion_timeout(&dma_ptr->dma_comp, msecs_to_jiffies(3000));
	dma_s = dmaengine_tx_status(dma_ptr->dma_chn, cookie, &dma_tx_s);
	if (dma_s != DMA_COMPLETE) {
		dev_info(dma_ptr->p_dev, "%s dma transfer timeout dma_s = %d\n",
			 dma_ptr->dma_name,
			 dma_s);
		return 0;
	}

	dev_dbg(dma_ptr->p_dev, "%s dma copy done! size = 0x%lx!\n",
		dma_ptr->dma_name,
		(unsigned long)dma_size);

	return dma_size;
}

static ssize_t modem_read(struct file *filp,
			  char __user *buf, size_t count, loff_t *ppos)
{
	phys_addr_t base, addr, src_buf;
	size_t size, offset, copy_size, map_size, r, dma_size;
	void *vmem, *vmem_cpy;
	int ret;
	struct modem_device *modem = filp->private_data;
	struct dma_copy_data *dma_ptr = modem->read_dma;

	dev_dbg(modem->p_dev, "read, %s!\n", modem->modem_name);

	/* only get read lock task can be read */
	if (strcmp(current->comm, modem->rd_lock_name) != 0) {
		dev_err(modem->p_dev,  "read, task %s need get rd lock!\n",
			current->comm);
		return -EACCES;
	}

	/* first, set try size to max size. */
	if (*ppos == 0)
		dma_ptr->try_size = SRPD_DMA_MAX_SIZE;

	modem_get_base_range(modem, &base, &size, 1);
	offset = *ppos;
	dev_dbg(modem->p_dev, "read start, offset = 0x%lx, count = 0x%lx!\n",
		offset, count);

	if (size <= offset)
		return -EINVAL;

	if (dma_ptr) {
		dma_ptr->dma_chn = dma_request_slave_channel(dma_ptr->p_dev,
							     dma_ptr->dma_name);
		if (IS_ERR_OR_NULL(dma_ptr->dma_chn))
			dev_err(modem->p_dev, "%s request dma chan failed!\n",
				dma_ptr->dma_name);
	}

	count = min_t(size_t, size - offset, count);
	r = count;
	do {
		addr = base + offset + (count - r);
		ret = modem_request_pms(modem, modem->rd_pms);

#ifdef CONFIG_SPRD_EXT_MODEM
		/*
		 * pcie modem and b_rx is true and
		 * ret is -ETIME need rescan pcie.
		 */
		if (modem->modem_type == PCIE_MODEM &&
		    ret == -ETIME) {
			dev_info(modem->p_dev, "rescan pcie!");
			ret = modem_rescan_pcie(modem, modem->rd_pms);
		}
#endif

		if (ret)
			return ret;

		vmem = modem_map_memory(modem, addr, r, &map_size);
		if (!vmem) {
			dev_err(modem->p_dev,
				"read, Unable to map  base: 0x%llx\n", addr);
			sprd_pms_release_resource(modem->rd_pms);
			return -ENOMEM;
		}
		vmem_cpy = vmem;
		copy_size = min_t(size_t, r, map_size);

		/* if dma is ok, use dma copy. */
		if (dma_ptr && dma_ptr->dma_chn) {
			src_buf = addr;
#ifdef CONFIG_SPRD_PCIE_EP_DEVICE
			if (modem->modem_type == PCIE_MODEM)
				src_buf = sprd_ep_virtophy(PCIE_EP_MODEM, vmem);
#endif
			dma_size = modem_dma_alloc(dma_ptr, copy_size);
			if (dma_size > 0) {
				/* if dam copy succ, use dst buf to copy to user.*/
				dma_size = modem_dma_copy(dma_ptr, dma_size,
							  src_buf,
							  dma_ptr->buf_p);
				if (dma_size > 0) {
					vmem_cpy = dma_ptr->buf_v;
					copy_size = dma_size;
				} else {
					modem_dma_free_mem(dma_ptr);
					modem_ram_unmap(modem->modem_type, vmem);
					sprd_pms_release_resource(modem->rd_pms);
					dev_err(modem->p_dev, "DMA copy faied.\n");
					return -EFAULT;
				}
			}
		}

		if (unalign_copy_to_user(buf, vmem_cpy, copy_size)) {
			dev_err(modem->p_dev,
				"read, copy data from user err!\n");
			modem_dma_free_mem(dma_ptr);
			modem_ram_unmap(modem->modem_type, vmem);
			sprd_pms_release_resource(modem->rd_pms);
			return -EFAULT;
		}

		modem_dma_free_mem(dma_ptr);
		modem_ram_unmap(modem->modem_type, vmem);
		sprd_pms_release_resource(modem->rd_pms);
		r -= copy_size;
		buf += copy_size;
	} while (r > 0);

	if (dma_ptr && dma_ptr->dma_chn) {
		dma_release_channel(dma_ptr->dma_chn);
		dma_ptr->dma_chn = NULL;
	}

	*ppos += (count - r);
	dev_dbg(modem->p_dev, "read complete\n");

	return count - r;
}

static ssize_t modem_write(struct file *filp,
			   const char __user *buf,
			   size_t count, loff_t *ppos)
{
	phys_addr_t base, addr, dst_buf;
	size_t size, offset, copy_size, map_size, r, dma_size;
	void *vmem, *vmem_cpy;
	struct modem_device *modem = filp->private_data;
	int ret;
	struct dma_copy_data *dma_ptr = modem->write_dma;

	dev_dbg(modem->p_dev, "write, %s!\n", modem->modem_name);

	/* only get write lock task can be write */
	if (strcmp(current->comm, modem->wt_lock_name) != 0) {
		dev_err(modem->p_dev, "write, task %s need get wt lock!\n",
			current->comm);
		return -EACCES;
	}

	modem_get_base_range(modem, &base, &size, 0);
	offset = *ppos;
	dev_dbg(modem->p_dev, "write, offset 0x%lx, count = 0x%lx!\n",
		offset, count);

	if (size <= offset)
		return -EINVAL;

	if (dma_ptr) {
		dma_ptr->dma_chn = dma_request_slave_channel(dma_ptr->p_dev,
							     dma_ptr->dma_name);
		if (IS_ERR_OR_NULL(dma_ptr->dma_chn))
			dev_err(modem->p_dev, "%s request dma chan failed!\n",
				dma_ptr->dma_name);
	}

	count = min_t(size_t, size - offset, count);
	r = count;
	do {
		addr = base + offset + (count - r);
		ret = modem_request_pms(modem, modem->wt_pms);
		if (ret)
			return ret;

		vmem = modem_map_memory(modem, addr, r, &map_size);
		if (!vmem) {
			dev_err(modem->p_dev,
				"write, Unable to map  base: 0x%llx\n",
				addr);
			sprd_pms_release_resource(modem->wt_pms);
			return -ENOMEM;
		}
		vmem_cpy = vmem;
		copy_size = min_t(size_t, r, map_size);

		/* if dma is ok, alloc a dma buf to recv user data. */
		if (dma_ptr && dma_ptr->dma_chn) {
			dma_size = modem_dma_alloc(dma_ptr, copy_size);
			if (dma_size > 0) {
				copy_size = dma_size;
				vmem_cpy = dma_ptr->buf_v;
			}
		}

		if (unalign_copy_from_user(vmem_cpy, buf, copy_size)) {
			dev_err(modem->p_dev,
				"write, copy data from user err!\n");
			modem_dma_free_mem(dma_ptr);
			modem_ram_unmap(modem->modem_type, vmem);
			sprd_pms_release_resource(modem->wt_pms);
			return -EFAULT;
		}

			/* if dma is ok, use dma copy. */
		if (dma_ptr && dma_ptr->dma_chn && dma_size > 0) {
			dst_buf = addr;
#ifdef CONFIG_SPRD_PCIE_EP_DEVICE
			if (modem->modem_type == PCIE_MODEM)
				dst_buf = sprd_ep_virtophy(PCIE_EP_MODEM, vmem);
#endif
			/* if dam copy succ, use dst buf to copy to user.*/
			dma_size = modem_dma_copy(dma_ptr, dma_size,
						  dma_ptr->buf_p, dst_buf);
			if (dma_size != copy_size) {
				dev_err(modem->p_dev,
					"write, dma copy failed, copy with cpu!\n");
				memcpy(dma_ptr->buf_v, vmem, copy_size);
			}
		}
		modem_dma_free_mem(dma_ptr);
		modem_ram_unmap(modem->modem_type, vmem);
		sprd_pms_release_resource(modem->wt_pms);
		r -= copy_size;
		buf += copy_size;
	} while (r > 0);

	if (dma_ptr && dma_ptr->dma_chn) {
		dma_release_channel(dma_ptr->dma_chn);
		dma_ptr->dma_chn = NULL;
	}

	dev_dbg(modem->p_dev, "write complete!\n");

	*ppos += (count - r);
	return count - r;
}

static loff_t modem_lseek(struct file *filp, loff_t off, int whence)
{
	switch (whence) {
	case SEEK_SET:
		filp->f_pos = off;
		break;

	default:
		return -EINVAL;
	}
	return off;
}

static int modem_cmd_lock(struct file *filp,
			  struct modem_device *modem, int b_rx)
{
	struct mutex *mut; /* mutex point to rd_mutex or wt_mutex*/
	struct sprd_pms *pms;
	char *name;
	int ret;

	mut = b_rx ? &modem->rd_mutex : &modem->wt_mutex;
	pms = b_rx ? modem->rd_pms : modem->wt_pms;
	name = b_rx ? modem->rd_lock_name : modem->wt_lock_name;

	if (filp->f_flags & O_NONBLOCK) {
		if (!mutex_trylock(mut)) {
			dev_err(modem->p_dev, "lock, %s get lock %d busy!\n",
				current->comm, b_rx);
			return -EBUSY;
		}
	} else {
		mutex_lock(mut);
		dev_info(modem->p_dev, "lock, %s has get lock %d !\n",
			current->comm, b_rx);
	}

	ret = modem_request_pms(modem, pms);

#ifdef CONFIG_SPRD_EXT_MODEM
	/* pcie modem and b_rx is true and ret is -ETIME need rescan pcie. */
	if (modem->modem_type == PCIE_MODEM && b_rx && ret == -ETIME) {
		dev_info(modem->p_dev, "rescan pcie!");
		ret = modem_rescan_pcie(modem, pms);
	}
#endif

	if (ret < 0) {
		mutex_unlock(mut);
		return ret;
	}

	/* lock, cpy task to name */
	strcpy(name, current->comm);
	return 0;
}

static int modem_cmd_unlock(struct modem_device *modem, int b_rx)
{
	struct mutex *mut; /* mutex point to rd_mutex or wt_mutex*/
	struct sprd_pms *pms;
	char *name;

	mut = b_rx ? &modem->rd_mutex : &modem->wt_mutex;
	pms = b_rx ? modem->rd_pms : modem->wt_pms;
	name = b_rx ? modem->rd_lock_name : modem->wt_lock_name;

	if (strlen(name) == 0)
		/* means no lock, so don't unlock */
		return 0;

	/* release resource */
	sprd_pms_release_resource(pms);

	/* unlock, set name[0] to 0 */
	name[0] = 0;
	mutex_unlock(mut);

	dev_info(modem->p_dev,
		"unlock, %s has unlock %d!\n",
		current->comm, b_rx);

	return 0;
}

static int modem_get_something(struct modem_device *modem,
			       void *from,
			       unsigned int cmd,
			       unsigned long arg)
{
	if (strcmp(current->comm, modem->rd_lock_name) != 0) {
		dev_err(modem->p_dev, "get, task %s need get rd lock!\n",
			current->comm);
		return -EBUSY;
	}

	if (copy_to_user((void __user *)arg, from, _IOC_SIZE(cmd)))
		return -EFAULT;

	dev_dbg(modem->p_dev, "get, %s arg 0x%lx!\n", current->comm, arg);

	return 0;
}

static int modem_set_something(struct modem_device *modem,
			       void *to, unsigned int cmd, unsigned long arg)
{
	dev_dbg(modem->p_dev, "set, %s cmd 0x%x!\n", current->comm, cmd);

	if (strcmp(current->comm, modem->wt_lock_name) != 0) {
		dev_err(modem->p_dev, "set, task %s need get wt lock!\n",
		       current->comm);
		return -EBUSY;
	}

	if (copy_from_user(to, (void __user *)arg, _IOC_SIZE(cmd)))
		return -EFAULT;

	return 0;
}

static void modem_reg_ctrl(struct modem_device *modem, u32 index, int b_clear)
{
	struct regmap *map;
	u32 reg, mask, val;
	struct modem_ctrl *ctrl = modem->modem_ctrl;

	reg = ctrl->ctrl_reg[index];
	if (reg == MODEM_INVALID_REG)
		return;

	map = ctrl->ctrl_map[index];
	mask = ctrl->ctrl_mask[index];
	val = b_clear ? ~mask : mask;
	dev_dbg(modem->p_dev, "ctrl reg = 0x%x, mask =0x%x, val =0x%x\n",
		reg, mask, val);

	regmap_update_bits(map, reg, mask, val);
}

static void soc_modem_start(struct modem_device *modem)
{
	/* clear cp force shutdown */
	modem_reg_ctrl(modem, MODEM_CTRL_SHUT_DOWN, 1);

	/* clear cp force deep sleep */
	modem_reg_ctrl(modem, MODEM_CTRL_DEEP_SLEEP, 1);

	/* waiting for power on stably */
	msleep(50);

	/* clear sys reset */
	modem_reg_ctrl(modem, MODEM_CTRL_SYS_RESET, 1);

	/* clear core reset */
	modem_reg_ctrl(modem, MODEM_CTRL_CORE_RESET, 1);

	/* waiting for core reset release stably */
	msleep(50);

	dev_info(modem->p_dev, "%s start over\n", modem->modem_name);
}

static void soc_modem_stop(struct modem_device *modem)
{
	/* set core reset */
	modem_reg_ctrl(modem, MODEM_CTRL_CORE_RESET, 0);

	/* set sys reset */
	modem_reg_ctrl(modem, MODEM_CTRL_SYS_RESET, 0);

	/* waiting for core reset hold stably */
	msleep(50);

	/* set cp force deep sleep */
	modem_reg_ctrl(modem, MODEM_CTRL_DEEP_SLEEP, 0);

	/* set cp force shutdown */
	modem_reg_ctrl(modem, MODEM_CTRL_SHUT_DOWN, 0);

	/* waiting for power off stably */
	msleep(50);

	dev_info(modem->p_dev, "%s stop over\n", modem->modem_name);
}

static int modem_run(struct modem_device *modem, u8 b_run)
{
	dev_info(modem->p_dev, "%s run = %d!\n", modem->modem_name, b_run);

	if (modem->run_state == b_run)
		return -EINVAL;

	modem->run_state = b_run;

	if (modem->modem_type == SOC_MODEM) {
		if (b_run)
			soc_modem_start(modem);
		else
			soc_modem_stop(modem);
	}

	return 0;
}

static int modem_assert(struct modem_device *modem)
{
#ifdef CONFIG_SPRD_EXT_MODEM
	modem_ctrl_poweron_modem(MDM_CTRL_CRASH_MODEM);
	return 0;
#else
	return smsg_senddie(modem->modem_dst);
#endif
}

static long modem_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int ret = -EINVAL;
	int access = 0;
	int param = 0;
	u8 b_clear;

	struct modem_device *modem = (struct modem_device *)filp->private_data;

	dev_dbg(modem->p_dev, "ioctl, cmd=0x%x (%c nr=%d len=%d dir=%d)\n", cmd,
		_IOC_TYPE(cmd), _IOC_NR(cmd), _IOC_SIZE(cmd), _IOC_DIR(cmd));

	if (_IOC_DIR(cmd) & _IOC_READ)
		access = !access_ok(VERIFY_WRITE,
				 (void __user *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		access = !access_ok(VERIFY_READ,
				 (void __user *)arg, _IOC_SIZE(cmd));

	if (access) {
		dev_err(modem->p_dev, "ioctl, access isn't ok! ret=%d\n", ret);
		return -EFAULT;
	}

	dev_dbg(modem->p_dev, "ioctl, arg = 0x%lx!", arg);

	switch (cmd) {
	case MODEM_READ_LOCK_CMD:
		ret = modem_cmd_lock(filp, modem, 1);
		break;

	case MODEM_READ_UNLOCK_CMD:
		ret = modem_cmd_unlock(modem, 1);
		break;

	case MODEM_WRITE_LOCK_CMD:
		ret = modem_cmd_lock(filp, modem, 0);
		break;

	case MODEM_WRITE_UNLOCK_CMD:
		ret = modem_cmd_unlock(modem, 0);
		break;

	case MODEM_GET_LOAD_INFO_CMD:
		ret = modem_get_something(modem, modem->load,
			      cmd, arg);
		break;

	case MODEM_SET_LOAD_INFO_CMD:
		ret = modem_set_something(modem, modem->load,
					  cmd, arg);
		if (!ret) {
			modem->all_base = (phys_addr_t)modem->load->all_base;
			modem->all_size = (size_t)modem->load->all_size;
			modem->modem_base = (phys_addr_t)
					    modem->load->modem_base;
			modem->modem_size = (size_t)modem->load->modem_size;
		}
		break;

	case MODEM_SET_READ_REGION_CMD:
		ret = modem_set_something(modem,
					  &param,
					  cmd, arg);
		modem->read_region = (u8)param;
		break;

	case MODEM_SET_WRITE_GEGION_CMD:
		ret = modem_set_something(modem,
					  &param,
					  cmd, arg);
		modem->write_region = (u8)param;
		break;

#ifdef CONFIG_SPRD_EXT_MODEM
	case MODEM_GET_REMOTE_FLAG_CMD:
		modem_get_remote_flag(modem);
		param = (int)modem->remote_flag;
		ret = modem_get_something(modem,
					  &param,
					  cmd, arg);
		break;

	case MODEM_SET_REMOTE_FLAG_CMD:
	case MODEM_CLR_REMOTE_FLAG_CMD:
		b_clear = cmd == MODEM_CLR_REMOTE_FLAG_CMD ? 1 : 0;
		ret = modem_set_something(modem,
					  &param,
					  cmd, arg);
		if (ret == 0) {
			modem->remote_flag = param;
			modem_set_remote_flag(modem, b_clear);
			/* notify pcie res load done. */
			if (modem->remote_flag & MODEM_IMAGE_DONE_FLAG)
				sprd_pcie_img_load_done(modem->modem_dst);
		}
		break;

	case MODEM_REBOOT_EXT_MODEM_CMD:
		ret = modem_reboot_ext_modem(modem, 1);
		break;

	case MODEM_POWERON_EXT_MODEM_CMD:
		ret = modem_reboot_ext_modem(modem, 0);
		break;

	case MODEM_POWEROFF_EXT_MODEM_CMD:
		ret = modem_poweroff_ext_modem(modem);
		break;
#endif

	case MODEM_ENTER_SLEEP_CMD:
		ret = modem_enter_sleep(modem);
		break;

	case MODEM_STOP_CMD:
		ret = modem_run(modem, 0);
		break;

	case MODEM_START_CMD:
		ret = modem_run(modem, 1);
		break;

	case MODEM_ASSERT_CMD:
		ret = modem_assert(modem);
		break;

	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}

#ifdef CONFIG_COMPAT
static long modem_compat_ioctl(struct file *filp, unsigned int cmd,
			       unsigned long arg)
{
	return modem_ioctl(filp, cmd, (unsigned long)compat_ptr(arg));
}
#endif

static int modem_get_name_and_dst(struct modem_device *modem,
			       struct device_node *np)
{
	int modem_id;

	if (of_property_read_bool(np, "5g-modem-support")) {
		modem_id = of_alias_get_id(np, "nr-modem");
		if (modem_id == -ENODEV || modem_id >= SPRD_5G_MODEM_CNT) {
			dev_err(modem->p_dev, "fail to get id\n");
			return -ENODEV;
		}
		modem->modem_name = modem_5g[modem_id].name;
		modem->modem_dst = modem_5g[modem_id].dst;
	} else {
		modem_id = of_alias_get_id(np, "lte-modem");
		if (modem_id == -ENODEV || modem_id >= SPRD_4G_MODEM_CNT) {
			dev_err(modem->p_dev, "fail to get id\n");
			return -ENODEV;
		}
		modem->modem_name = modem_4g[modem_id].name;
		modem->modem_dst = modem_4g[modem_id].dst;
	}

	return 0;
}

static int pcie_modem_parse_dt(struct modem_device *modem,
			       struct device_node *np)
{
	int ret;

	modem->modem_type = PCIE_MODEM;

	ret = modem_get_name_and_dst(modem, np);
	if (ret)
		return ret;

#ifdef CONFIG_SPRD_EXT_MODEM_POWER_CTRL
	modem->modem_power = devm_gpiod_get(modem->p_dev,
					    "poweron",
					    GPIOD_OUT_HIGH);
	if (IS_ERR(modem->modem_power)) {
		dev_err(modem->p_dev, "get poweron gpio failed!\n");
		return PTR_ERR(modem->modem_power);
	}


	modem->modem_reset = devm_gpiod_get(modem->p_dev,
					    "reset",
					    GPIOD_OUT_HIGH);
	if (IS_ERR(modem->modem_reset)) {
		dev_err(modem->p_dev, "get reset gpio failed!\n");
		return PTR_ERR(modem->modem_reset);
	}
#endif

	return 0;
}

static int soc_modem_parse_dt(struct modem_device *modem,
			      struct device_node *np)
{
	int ret, cr_num;
	struct modem_ctrl *modem_ctl;
	u32 syscon_args[2];

	modem->modem_type = SOC_MODEM;

	ret = modem_get_name_and_dst(modem, np);
	if (ret)
		return ret;

	modem_ctl = devm_kzalloc(modem->p_dev,
				 sizeof(struct modem_ctrl),
				 GFP_KERNEL);
	if (!modem_ctl)
		return -ENOMEM;

	for (cr_num = 0; cr_num < MODEM_CTRL_NR; cr_num++) {
		/* get apb & pmu reg handle */
		modem_ctl->ctrl_map[cr_num] =
			syscon_regmap_lookup_by_name(np,
						     modem_ctrl_args[cr_num]);
		if (IS_ERR(modem_ctl->ctrl_map[cr_num])) {
			dev_err(modem->p_dev, "failed to find %s\n",
				modem_ctrl_args[cr_num]);
			return -EINVAL;
		}

		/**
		 * 1.get ctrl_reg offset, the ctrl-reg variable number, so need
		 * to start reading from the largest until success.
		 * 2.get ctrl_mask
		 */
		ret = syscon_get_args_by_name(np,
					      modem_ctrl_args[cr_num],
					      2,
					      (u32 *)syscon_args);
		if (ret == 2) {
			modem_ctl->ctrl_reg[cr_num] = syscon_args[0];
			modem_ctl->ctrl_mask[cr_num] = syscon_args[1];
		} else {
			dev_err(modem->p_dev, "failed to map ctrl reg\n");
			return -EINVAL;
		}
	}

	modem->modem_ctrl = modem_ctl;
	return 0;
}

#ifdef CONFIG_DEBUG_FS
static const struct file_operations modem_debug_fops;
static struct dentry *modem_root;

static void modem_debug_putline(struct seq_file *m, char c, int n)
{
	char buf[300];
	int i, max, len;

	/* buf will end with '\n' and 0 */
	max = ARRAY_SIZE(buf) - 2;
	len = n > max ? max : n;

	for (i = 0; i < len; i++)
		buf[i] = c;

	buf[i] = '\n';
	buf[i + 1] = 0;

	seq_puts(m, buf);
}

static int modem_debug_show(struct seq_file *m, void *private)
{
	u32 region_cnt, i;
	struct modem_region_info *regions;
	struct modem_device *modem = (struct modem_device *)m->private;

	region_cnt = modem->load->region_cnt;
	regions = modem->load->regions;

	modem_debug_putline(m, '*', 100);

	seq_printf(m, "%s info:\n", modem->modem_name);
	modem_debug_putline(m, '-', 80);
	seq_printf(m, "read_region: %d, write_region: %d\n",
		   modem->read_region, modem->write_region);
	seq_printf(m, "run_state: %d, remote_flag: %d\n",
		   modem->run_state, modem->remote_flag);
	seq_printf(m, "modem_base: 0x%llx, size: 0x%lx\n",
		   modem->modem_base, modem->modem_size);
	seq_printf(m, "all_base: 0x%llx, size: 0x%lx\n",
		   modem->all_base, modem->all_size);

	modem_debug_putline(m, '-', 80);
	seq_puts(m, "region list:\n");

	for (i = 0; i < region_cnt; i++)
		seq_printf(m, "region[%2d]:address=0x%llx, size=0x%lx, name=%s\n",
			   i,
			   (phys_addr_t)regions[i].address,
			   (size_t)regions[i].size,
			   regions[i].name);

	if (modem->modem_ctrl) {
		struct modem_ctrl *ctrl = modem->modem_ctrl;

		modem_debug_putline(m, '-', 80);
		seq_puts(m, "modem ctl info:\n");

		for (i = 0; i < MODEM_CTRL_NR; i++)
			seq_printf(m, "region[%2d]:reg=0x%x, mask=0x%x\n",
				   i,
				   ctrl->ctrl_reg[i],
				   ctrl->ctrl_mask[i]);
	}
	modem_debug_putline(m, '*', 100);

	return 0;
}

static int modem_debug_open(struct inode *inode, struct file *file)
{
	return single_open(file, modem_debug_show, inode->i_private);
}

static const struct file_operations modem_debug_fops = {
	.open = modem_debug_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static void modem_init_debugfs(struct modem_device *modem)
{
	modem->debug_file = debugfs_create_file(modem->modem_name, 0444,
				modem_root,
				modem,
				&modem_debug_fops);
}

static void modem_remove_debugfs(struct modem_device *modem)
{
	debugfs_remove(modem->debug_file);
}
#endif

static const struct file_operations modem_fops = {
	.open = modem_open,
	.release = modem_release,
	.llseek = modem_lseek,
	.read = modem_read,
	.write = modem_write,
	.unlocked_ioctl = modem_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = modem_compat_ioctl,
#endif
	.owner = THIS_MODULE
};

static const struct of_device_id modem_match_table[] = {
	{.compatible = "sprd,modem", .data = soc_modem_parse_dt},
	{.compatible = "sprd,pcie-modem", .data = pcie_modem_parse_dt},
	{ },
};

static void modem_alloc_dma(struct modem_device *modem,
			    const char *dma_name,
			    struct dma_copy_data **dma_pptr)
{
	struct dma_copy_data *dma_ptr;

	dma_ptr = devm_kzalloc(modem->p_dev, sizeof(*dma_ptr), GFP_KERNEL);
	if (dma_ptr) {
		dma_ptr->dma_name = dma_name;
		init_completion(&dma_ptr->dma_comp);
		*dma_pptr = dma_ptr;
		dma_ptr->p_dev = modem->p_dev;
	}
}

static void modem_init_dma(struct modem_device *modem,
			   struct device_node *np)
{
	const char *dma_name[2];

	/* get and init dma config. */
	if (of_property_read_string_array(np, "dma-names", dma_name, 2) < 2)
		return;

	dev_info(modem->p_dev, "dma_name[0]=%s, dma_name[1]=%s\n",
		 dma_name[0], dma_name[1]);

	modem_alloc_dma(modem, dma_name[0], &modem->read_dma);
	modem_alloc_dma(modem, dma_name[1], &modem->write_dma);
}

static int modem_probe(struct platform_device *pdev)
{
	struct modem_device *modem;
	int ret = 0;
	MODEM_PARSE_FUN dt_parse;
	struct device_node *np = pdev->dev.of_node;
	struct device *dev;

	modem = devm_kzalloc(&pdev->dev,
			     sizeof(struct modem_device),
			     GFP_KERNEL);
	if (!modem)
		return -ENOMEM;

	modem->p_dev = &pdev->dev;
	modem->run_state = RUN_STATE_INVALID;
	modem->load = devm_kzalloc(modem->p_dev,
				   sizeof(struct modem_load_info),
				   GFP_KERNEL);
	if (!modem->load)
		return -ENOMEM;

	dt_parse = of_device_get_match_data(modem->p_dev);
	if (!dt_parse) {
		dev_err(modem->p_dev, "cat't get parse fun!\n");
		return -EINVAL;
	}

	ret = dt_parse(modem, np);
	if (ret)
		return ret;

	modem_init_dma(modem, np);

	ret = alloc_chrdev_region(&modem->devid, 0, 1, modem->modem_name);
	if (ret != 0) {
		dev_err(modem->p_dev, "get name fail, ret = %d!\n", ret);
		return ret;
	}

	cdev_init(&modem->cdev, &modem_fops);
	ret = cdev_add(&modem->cdev, modem->devid, 1);
	if (ret != 0) {
		unregister_chrdev_region(modem->devid, 1);
		dev_err(modem->p_dev, "add dev fail, ret = %d!\n", ret);
		return ret;
	}

	dev = device_create(modem_class, NULL,
		      modem->devid,
		      NULL, "%s", modem->modem_name);
	if (IS_ERR(dev))
		dev_err(modem->p_dev, "device_create fail,ERRNO = %ld!\n",
			PTR_ERR(dev));

	mutex_init(&modem->rd_mutex);
	mutex_init(&modem->wt_mutex);
	snprintf(modem->rd_pms_name,
		 sizeof(modem->rd_pms_name), "%s-rd", modem->modem_name);
	snprintf(modem->wt_pms_name,
		 sizeof(modem->wt_pms_name), "%s-wt", modem->modem_name);
	modem->rd_pms = sprd_pms_create(modem->modem_dst,
					modem->rd_pms_name, false);
	if (!modem->rd_pms)
		pr_warn("create pms %s failed!\n", modem->rd_pms_name);

	modem->wt_pms = sprd_pms_create(modem->modem_dst,
					modem->wt_pms_name, false);
	if (!modem->rd_pms)
		pr_warn("create pms %s failed!\n", modem->wt_pms_name);

	platform_set_drvdata(pdev, modem);

#if defined(CONFIG_DEBUG_FS)
	modem_init_debugfs(modem);
#endif

	return 0;
}

static int  modem_remove(struct platform_device *pdev)
{
	struct modem_device *modem = platform_get_drvdata(pdev);

	if (modem) {
		sprd_pms_destroy(modem->rd_pms);
		sprd_pms_destroy(modem->wt_pms);
		mutex_destroy(&modem->rd_mutex);
		mutex_destroy(&modem->wt_mutex);
		device_destroy(modem_class, modem->devid);
		cdev_del(&modem->cdev);
		unregister_chrdev_region(modem->devid, 1);
#if defined(CONFIG_DEBUG_FS)
		modem_remove_debugfs(modem);
#endif
		platform_set_drvdata(pdev, NULL);
	}

	return 0;
}

static struct platform_driver modem_driver = {
	.driver = {
		.name = "modem",
		.of_match_table = modem_match_table,
	},
	.probe = modem_probe,
	.remove = modem_remove,
};

static int __init modem_init(void)
{
	modem_class = class_create(THIS_MODULE, "ext_modem");
	if (IS_ERR(modem_class))
		return PTR_ERR(modem_class);

#if defined(CONFIG_DEBUG_FS)
	modem_root = debugfs_create_dir("modem", NULL);
	if (IS_ERR(modem_root))
		return PTR_ERR(modem_root);
#endif

#ifdef CONFIG_SPRD_EXT_MODEM
	 modem_get_ext_modem_ops(&ext_modem_ops);
#endif

	return platform_driver_register(&modem_driver);
}

static void __exit modem_exit(void)
{
	class_destroy(modem_class);

#if defined(CONFIG_DEBUG_FS)
	debugfs_remove_recursive(modem_root);
#endif

	platform_driver_unregister(&modem_driver);
}

module_init(modem_init);
module_exit(modem_exit);

MODULE_AUTHOR("Wenping zhou");
MODULE_DESCRIPTION("External modem driver");
MODULE_LICENSE("GPL v2");
