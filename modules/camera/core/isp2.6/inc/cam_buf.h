/*
 * Copyright (C) 2017-2018 Spreadtrum Communications Inc.
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

#ifndef _CAM_BUF_H_
#define _CAM_BUF_H_

#include <linux/types.h>
#include <linux/device.h>
#include <linux/sprd_iommu.h>

#include "ion.h"
/* #include "ion_priv.h" */

#define CAM_BUF_NAME_LEN		32
#define CAM_BUF_CAHCED		(1 << 31)

enum cam_buf_type {
	CAM_BUF_NONE,
	CAM_BUF_USER,
	CAM_BUF_KERNEL,
};

enum {
	CAM_BUF_MAPPING_NULL = 0,
	CAM_BUF_MAPPING_DEV = (1 << 1),
	CAM_BUF_MAPPING_KERNEL = (1 << 2),
};

enum cam_iommudev_type {
	CAM_IOMMUDEV_ISP,
	CAM_IOMMUDEV_DCAM,
	CAM_IOMMUDEV_FD,
	CAM_IOMMUDEV_MAX,
};

struct camera_buf {
	char name[CAM_BUF_NAME_LEN];
	bool buf_sec;

	/* user buffer info */
	int32_t mfd[3];
	struct dma_buf *dmabuf_p[3];

	void *ionbuf[3]; /* for iommu map */
	uint32_t offset[3];
	size_t size[3];
	unsigned long addr_vir[3];
	unsigned long addr_k[3];
	unsigned long iova[3];
	struct device *dev; /* mapped device */
	enum cam_buf_type type;
	uint32_t mapping_state;
};

int cambuf_reg_iommudev(struct device *dev,
	enum cam_iommudev_type type);
int cambuf_unreg_iommudev(enum cam_iommudev_type type);
int get_iommu_status(enum cam_iommudev_type type);

int cambuf_get_ionbuf(struct camera_buf *buf_info);
int cambuf_put_ionbuf(struct camera_buf *buf_info);
int cambuf_iommu_map_single_page(
			struct camera_buf *buf_info,
			enum cam_iommudev_type type);
int cambuf_iommu_map(
			struct camera_buf *buf_info,
			enum cam_iommudev_type type);
int cambuf_iommu_unmap(
			struct camera_buf *buf_info);

int cambuf_kmap(struct camera_buf *buf_info);
int cambuf_kunmap(struct camera_buf *buf_info);

int  cambuf_alloc(struct camera_buf *buf_info,
		size_t size, size_t align, int iommu_enable);
int cambuf_free(struct camera_buf *buf_info);

int mdbg_check(void);
#endif /* _CAM_BUF_H_ */
