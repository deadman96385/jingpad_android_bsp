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

#include "vdsp_sipc.h"
#include "vdsp_sipc_priv.h"

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "VDSP_SMEM_INTERFACE: %d %d %s : "\
	fmt, current->pid, __LINE__, __func__


int vdsp_share_mem_alloc(struct vdsp_mem_desc *ctx,
			struct ion_buf *ion_buf,
			int heap_type,
			size_t size)
{
	int ret = -1;

	if (ctx && ctx->ops && ctx->ops->mem_alloc)
		ret = ctx->ops->mem_alloc(ctx, ion_buf, heap_type, size);

	return ret;
}
EXPORT_SYMBOL_GPL(vdsp_share_mem_alloc);

int vdsp_share_mem_free(struct vdsp_mem_desc *ctx,
		       struct ion_buf *ion_buf)
{
	int ret = -1;

	if (ctx && ctx->ops && ctx->ops->mem_free)
		ret = ctx->ops->mem_free(ctx, ion_buf);

	return ret;
}
EXPORT_SYMBOL_GPL(vdsp_share_mem_free);


int vdsp_share_mem_kmap(struct vdsp_mem_desc *ctx,
		       struct ion_buf *buf_info)
{
	int ret = -1;

	if (ctx && ctx->ops && ctx->ops->mem_kmap)
		ret = ctx->ops->mem_kmap(ctx, buf_info);

	return ret;
}
EXPORT_SYMBOL_GPL(vdsp_share_mem_kmap);


int vdsp_share_mem_unkmap(struct vdsp_mem_desc *ctx,
			 struct ion_buf *buf_info)
{
	int ret = -1;

	if (ctx && ctx->ops && ctx->ops->mem_kunmap)
		ret = ctx->ops->mem_kunmap(ctx, buf_info);

	return ret;
}
EXPORT_SYMBOL_GPL(vdsp_share_mem_unkmap);


int vdsp_share_mem_iommu_map(struct vdsp_mem_desc *ctx,
			    struct ion_buf *pfinfo, int idx)
{
	int ret = -1;

	if (ctx && ctx->ops && ctx->ops->mem_iommu_map)
		ret = ctx->ops->mem_iommu_map(ctx, pfinfo, idx);

	return ret;
}
EXPORT_SYMBOL_GPL(vdsp_share_mem_iommu_map);

int vdsp_share_mem_iommu_unmap(struct vdsp_mem_desc *ctx,
			      struct ion_buf *pfinfo, int idx)
{
	int ret = -1;

	if (ctx && ctx->ops && ctx->ops->mem_iommu_unmap)
		ret = ctx->ops->mem_iommu_unmap(ctx, pfinfo, idx);

	return ret;
}
EXPORT_SYMBOL_GPL(vdsp_share_mem_iommu_unmap);
