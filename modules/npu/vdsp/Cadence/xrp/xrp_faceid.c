/*
 * xrp_firmware: firmware manipulation for the XRP
 *
 * Copyright (c) 2015 - 2017 Cadence Design Systems, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Alternatively you can use and distribute this file under the terms of
 * the GNU General Public License version 2 or later.
 */

#include <linux/dma-mapping.h>
#include <linux/elf.h>
#include <linux/firmware.h>
#include <linux/highmem.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/io.h>
#include "xrp_address_map.h"
#include "vdsp_hw.h"
#include "xrp_internal.h"
#include "xrp_kernel_dsp_interface.h"
#include "xrp_faceid.h"
#include "vdsp_trusty.h"

#define SIGN_HEAD_SIZE (512)
#define SIGN_TAIL_SIZE (512)

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "sprd-vdsp: faceid %d %d %s : "\
        fmt, current->pid, __LINE__, __func__



static int sprd_alloc_faceid_weights_buffer(struct xvp *xvp,
		struct ion_buf *ion_buf,size_t size)
{
	int ret;
	ret = xvp->vdsp_mem_desc->ops->mem_alloc(xvp->vdsp_mem_desc,
						ion_buf,
						ION_HEAP_ID_MASK_VDSP,/*todo vdsp head id*/
						size);
	if(0 != ret) {
		pr_err("alloc weights failed\n");
		return -ENOMEM;
	}
	ret = xvp->vdsp_mem_desc->ops->mem_kmap(xvp->vdsp_mem_desc, ion_buf);
	if(0 != ret) {
		xvp->vdsp_mem_desc->ops->mem_free(xvp->vdsp_mem_desc, ion_buf);
		return -EFAULT;
	}
	//xvp->faceid_fw_viraddr = (void*)xvp->ion_faceid_fw.addr_k[0];
	ion_buf->dev = xvp->dev;
	pr_debug("faceid alloc addr_p %lx  vaddr:%lx,size %ld\n",
			ion_buf->addr_p[0] , ion_buf->addr_k[0],ion_buf->size[0]);
	return 0;

}
static int sprd_free_faceid_weights_buffer(struct xvp *xvp,
		struct ion_buf *ion_buf)
{
	unsigned long dst_viraddr = ion_buf->addr_k[0];
	if(dst_viraddr) {
		xvp->vdsp_mem_desc->ops->mem_kunmap(xvp->vdsp_mem_desc, ion_buf);
		xvp->vdsp_mem_desc->ops->mem_free(xvp->vdsp_mem_desc, ion_buf);
	}
	return 0;
}
#if 0
static int sprd_iommu_map_faceid_weights_buffer(struct xvp *xvp,struct ion_buf *ion_buf)
{
	int ret = -EFAULT;
	if(NULL == (void*)ion_buf->addr_k[0]) {
		pr_info("map faceid weights addr is NULL \n");
		return ret;
	}
	pr_info("ion_buf->addr_k[0] %lx\n",ion_buf->addr_k[0]);
	{
		ret = xvp->vdsp_mem_desc->ops->mem_iommu_map(xvp->vdsp_mem_desc, ion_buf , IOMMU_ALL);
		if(ret) {
			pr_info("%s map faceid fialed\n" , __func__);
			return ret;
		}
		//xvp->dsp_firmware_addr = xvp->ion_faceid_fw.iova[0];
	}
	pr_info("map faceid weights addr:%lx --> %lx\n",ion_buf->addr_k[0],ion_buf->iova[0]);

	return ret;
}
static int sprd_iommu_unmap_faceid_weights_buffer(struct xvp *xvp,struct ion_buf *ion_buf)
{
	int ret = -EFAULT;

	if(NULL == (void*)ion_buf->addr_k[0]) {
		pr_err("unmap faceid weights addr is NULL\n");
		return ret;
	}
	{
		ret = xvp->vdsp_mem_desc->ops->mem_iommu_unmap(xvp->vdsp_mem_desc, ion_buf, IOMMU_ALL);
		if(ret) {
			pr_err("%s unmap faceid weights buffer failed\n" , __func__);
			return ret;
		}
	}
	pr_info("%s :%lx\n" , __func__ ,ion_buf->addr_k[0]);
	return 0;
}
#endif
int sprd_faceid_request_algo_mem(struct xvp *xvp)
{
	int ret = sprd_alloc_faceid_weights_buffer(xvp,
				&xvp->faceid_pool.ion_fd_mem_pool,
				FACEID_FD_MEM_SIZE);
	if (ret < 0){
		pr_err("request fd mem fail\n");
		return ret;
	}

	ret = sprd_alloc_faceid_weights_buffer(xvp,
			&xvp->faceid_pool.ion_face_transfer,
			sizeof(FV_FAECINFO));
	if (ret < 0){
		sprd_free_faceid_weights_buffer(xvp,
				&xvp->faceid_pool.ion_fd_mem_pool);
		pr_err("request transfer mem fail\n");
		return ret;
	}
/*
	ret = sprd_alloc_faceid_weights_buffer(xvp,&xvp->faceid_pool.ion_flv_mem_pool,FACEID_FLV_MEM_SIZE);
	if (ret < 0){
		sprd_free_faceid_weights_buffer(xvp,&xvp->faceid_pool.ion_fd_mem_pool);
		sprd_free_faceid_weights_buffer(xvp,&xvp->faceid_pool.ion_fp_mem_pool);
		pr_info("request flv mem fail\n");
		return ret;
	}
	ret = sprd_alloc_faceid_weights_buffer(xvp,&xvp->faceid_pool.ion_fv_mem_pool,FACEID_FV_MEM_SIZE);
	if (ret < 0){
		sprd_free_faceid_weights_buffer(xvp,&xvp->faceid_pool.ion_fd_mem_pool);
		sprd_free_faceid_weights_buffer(xvp,&xvp->faceid_pool.ion_fp_mem_pool);
		sprd_free_faceid_weights_buffer(xvp,&xvp->faceid_pool.ion_flv_mem_pool);
		pr_info("request fv mem fail\n");
		return ret;
	}
*/
	return 0;
}

int sprd_faceid_release_algo_mem(struct xvp *xvp)
{
	sprd_free_faceid_weights_buffer(xvp,&xvp->faceid_pool.ion_fd_mem_pool);
	sprd_free_faceid_weights_buffer(xvp,&xvp->faceid_pool.ion_face_transfer);
	//sprd_free_faceid_weights_buffer(xvp,&xvp->faceid_pool.ion_flv_mem_pool);
	//sprd_free_faceid_weights_buffer(xvp,&xvp->faceid_pool.ion_fv_mem_pool);
	return 0;
}

int sprd_faceid_request_weights_fd_p(struct xvp *xvp)
{
	unsigned long dst = 0;
	int ret = request_firmware(&xvp->faceid_fw,
			"network_coeff_fd_p.bin", xvp->dev);

	if (ret < 0){
		pr_err("request fd p weights fail\n");
		return ret;
	}

	ret = sprd_alloc_faceid_weights_buffer(xvp,
			&xvp->faceid_pool.ion_fd_weights_p,
			xvp->faceid_fw->size);
	if (ret < 0)
	{
		pr_err("alloc fd p weights fail\n");
		return ret;
	}
	dst = xvp->faceid_pool.ion_fd_weights_p.addr_k[0];
	memcpy((void*)dst, xvp->faceid_fw->data, xvp->faceid_fw->size);

	release_firmware(xvp->faceid_fw);

	return ret;
}
int sprd_faceid_request_weights_fd_r(struct xvp *xvp)
{
	unsigned long dst = 0;
	int ret = request_firmware(&xvp->faceid_fw,
			"network_coeff_fd_r.bin", xvp->dev);

	if (ret < 0){
		pr_err("request fd r weights fail\n");
		return ret;
	}

	ret = sprd_alloc_faceid_weights_buffer(xvp,
			&xvp->faceid_pool.ion_fd_weights_r,
			xvp->faceid_fw->size);
	if (ret < 0)
	{
		pr_err("alloc fd r weights fail\n");
		return ret;
	}

	dst = xvp->faceid_pool.ion_fd_weights_r.addr_k[0];
	memcpy((void*)dst, xvp->faceid_fw->data, xvp->faceid_fw->size);

	release_firmware(xvp->faceid_fw);

	return ret;
}
int sprd_faceid_request_weights_fd_o(struct xvp *xvp)
{
	unsigned long dst = 0;
	int ret = request_firmware(&xvp->faceid_fw,
			"network_coeff_fd_o.bin", xvp->dev);

	if (ret < 0){
		pr_err("request fd o weights fail\n");
		return ret;
	}

	ret = sprd_alloc_faceid_weights_buffer(xvp,
			&xvp->faceid_pool.ion_fd_weights_o,
			xvp->faceid_fw->size);
	if (ret < 0)
	{
		pr_err("alloc fd o weights fail\n");
		return ret;
	}

	dst = xvp->faceid_pool.ion_fd_weights_o.addr_k[0];
	memcpy((void*)dst, xvp->faceid_fw->data, xvp->faceid_fw->size);

	release_firmware(xvp->faceid_fw);

	return ret;
}
int sprd_faceid_request_weights_fp(struct xvp *xvp)
{
	unsigned long dst = 0;

	int ret = request_firmware(&xvp->faceid_fw,
			"network_coeff_fp.bin", xvp->dev);

	if (ret < 0){
		pr_info("request fp weights fail\n");
		return ret;
	}

	ret = sprd_alloc_faceid_weights_buffer(xvp,
			&xvp->faceid_pool.ion_fp_weights,
			xvp->faceid_fw->size);
	if (ret < 0)
	{
		pr_err("alloc fp weights fail\n");
		return ret;
	}

	dst = xvp->faceid_pool.ion_fp_weights.addr_k[0];
	memcpy((void*)dst, xvp->faceid_fw->data, xvp->faceid_fw->size);

	release_firmware(xvp->faceid_fw);

	return ret;
}
int sprd_faceid_request_weights_flv(struct xvp *xvp)
{
	unsigned long dst = 0;
	int ret = request_firmware(&xvp->faceid_fw,
			"network_coeff_flv.bin", xvp->dev);

	if (ret < 0){
		pr_info("request flv weights fail\n");
		return ret;
	}

	ret = sprd_alloc_faceid_weights_buffer(xvp,
			&xvp->faceid_pool.ion_flv_weights,
			xvp->faceid_fw->size);
	if (ret < 0)
	{
		pr_err("alloc flv weights fail\n");
		return ret;
	}

	dst = xvp->faceid_pool.ion_flv_weights.addr_k[0];
	memcpy((void*)dst, xvp->faceid_fw->data, xvp->faceid_fw->size);

	release_firmware(xvp->faceid_fw);

	return ret;
}
int sprd_faceid_request_weights_fv(struct xvp *xvp)
{
	unsigned long dst = 0;
	int ret = request_firmware(&xvp->faceid_fw,
			"network_coeff_fv.bin", xvp->dev);

	if (ret < 0){
		pr_info("request fv weights fail\n");
		return ret;
	}

	ret = sprd_alloc_faceid_weights_buffer(xvp,
			&xvp->faceid_pool.ion_fv_weights,
			xvp->faceid_fw->size);
	if (ret < 0)
	{
		pr_err("alloc fv weights fail\n");
		return ret;
	}

	dst = xvp->faceid_pool.ion_fv_weights.addr_k[0];
	memcpy((void*)dst, xvp->faceid_fw->data, xvp->faceid_fw->size);

	release_firmware(xvp->faceid_fw);

	return ret;
}
int sprd_faceid_request_weights(struct xvp *xvp)
{
	sprd_faceid_request_weights_fd_p(xvp);
	sprd_faceid_request_weights_fd_r(xvp);
	sprd_faceid_request_weights_fd_o(xvp);
	sprd_faceid_request_weights_fp(xvp);
	sprd_faceid_request_weights_flv(xvp);
	sprd_faceid_request_weights_fv(xvp);
	sprd_faceid_request_algo_mem(xvp);
	//sprd_faceid_request_result_mem(xvp);
	return 0;
}
void sprd_faceid_release_weights(struct xvp *xvp)
{
	sprd_free_faceid_weights_buffer(xvp,
			&xvp->faceid_pool.ion_fd_weights_p);
	sprd_free_faceid_weights_buffer(xvp,
			&xvp->faceid_pool.ion_fd_weights_r);
	sprd_free_faceid_weights_buffer(xvp,
			&xvp->faceid_pool.ion_fd_weights_o);
	sprd_free_faceid_weights_buffer(xvp,
			&xvp->faceid_pool.ion_fp_weights);
	sprd_free_faceid_weights_buffer(xvp,
			&xvp->faceid_pool.ion_flv_weights);
	sprd_free_faceid_weights_buffer(xvp,
			&xvp->faceid_pool.ion_fv_weights);
	sprd_faceid_release_algo_mem(xvp);
	//sprd_faceid_release_result_mem(xvp);
}

static int sprd_alloc_faceid_fwbuffer(struct xvp *xvp)
{
	int ret;

	ret = xvp->vdsp_mem_desc->ops->mem_alloc(xvp->vdsp_mem_desc,
		&xvp->ion_faceid_fw_sign,
		ION_HEAP_ID_MASK_VDSP,/*todo vdsp head id*/
		VDSP_FACEID_FIRMWIRE_SIZE);
	if(0 != ret) {
		pr_err("alloc sign fw buffer failed,ret %d\n",ret);
		return -ENOMEM;
	}
	ret = xvp->vdsp_mem_desc->ops->mem_kmap(xvp->vdsp_mem_desc,
			&xvp->ion_faceid_fw_sign);
	if(0 != ret) {
		xvp->vdsp_mem_desc->ops->mem_free(xvp->vdsp_mem_desc,
				&xvp->ion_faceid_fw_sign);
		pr_err("kmap fw buffer failed,ret %d\n",ret);
		return -EFAULT;
	}
	xvp->ion_faceid_fw_sign.dev = xvp->dev;

	ret = xvp->vdsp_mem_desc->ops->mem_alloc(xvp->vdsp_mem_desc,
			&xvp->ion_faceid_fw,
			ION_HEAP_ID_MASK_VDSP,/*todo vdsp head id*/
			VDSP_FACEID_FIRMWIRE_SIZE);
	if(0 != ret) {
		pr_err("alloc fw buffer failed,ret %d\n",ret);
		return -ENOMEM;
	}
	ret = xvp->vdsp_mem_desc->ops->mem_kmap(xvp->vdsp_mem_desc,
			&xvp->ion_faceid_fw);
	if(0 != ret) {
		xvp->vdsp_mem_desc->ops->mem_free(xvp->vdsp_mem_desc,
				&xvp->ion_faceid_fw);
		pr_err("kmap fw buffer failed,ret %d\n",ret);
		return -EFAULT;
	}
	xvp->firmware2_viraddr = (void*)xvp->ion_faceid_fw.addr_k[0];
	xvp->firmware2_phys = xvp->ion_faceid_fw.addr_p[0];
	xvp->ion_faceid_fw.dev = xvp->dev;
	pr_debug("%s vaddr:%p phyaddr %llX\n",
			__func__ , xvp->firmware2_viraddr,xvp->firmware2_phys);
	return 0;
}

static int sprd_free_faceid_fwbuffer(struct xvp *xvp)
{
	pr_debug("vdsp fw vir addr:%p\n", xvp->firmware2_viraddr);
	if(xvp->firmware2_viraddr) {
		xvp->vdsp_mem_desc->ops->mem_kunmap(xvp->vdsp_mem_desc,
				&xvp->ion_faceid_fw_sign);
		xvp->vdsp_mem_desc->ops->mem_free(xvp->vdsp_mem_desc,
				&xvp->ion_faceid_fw_sign);

		xvp->vdsp_mem_desc->ops->mem_kunmap(xvp->vdsp_mem_desc,
				&xvp->ion_faceid_fw);
		xvp->vdsp_mem_desc->ops->mem_free(xvp->vdsp_mem_desc,
				&xvp->ion_faceid_fw);
		xvp->firmware2_viraddr = NULL;
	}
	return 0;
}
void sprd_release_faceid_firmware(struct xvp *xvp)
{
	release_firmware(xvp->firmware2_sign);
}
int sprd_request_faceid_firmware(struct xvp *xvp)
{
#if 0
	int ret = request_firmware(&xvp->firmware2, FACEID_FIRMWARE, xvp->dev);
#else
	int ret = request_firmware(&xvp->firmware2_sign, FACEID_FIRMWARE, xvp->dev);

	if (ret < 0)
	{
		pr_err("request firmware failed ret:%d\n" ,ret);
		return ret;
	}
#endif
	return ret;
}

int sprd_iommu_map_faceid_fwbuffer(struct xvp *xvp)
{
	int ret = -EFAULT;
	if(xvp->firmware2_viraddr == NULL) {
		pr_err("map faceid fw addr is NULL \n");
		return ret;
	}
	{
		ret = xvp->vdsp_mem_desc->ops->mem_iommu_map(xvp->vdsp_mem_desc,
				&xvp->ion_faceid_fw , IOMMU_ALL);
		if(ret) {
			pr_err("map faceid fw buffer failed\n");
			return ret;
		}
		xvp->dsp_firmware_addr = xvp->ion_faceid_fw.iova[0];
	}
	pr_debug("iomap:%p --> %lx\n",
			xvp->firmware2_viraddr,(unsigned long)xvp->dsp_firmware_addr);
	return ret;
}
int sprd_iommu_unmap_faceid_fwbuffer(struct xvp *xvp)
{
	int ret = -EFAULT;
	int ret1 = 0;

	if(xvp->firmware2_viraddr == NULL) {
		pr_err("unmap faceid fw addr is NULL\n");
		return ret;
	}
	{
		ret = xvp->vdsp_mem_desc->ops->mem_iommu_unmap(xvp->vdsp_mem_desc,
				&xvp->ion_faceid_fw , IOMMU_ALL);
		if(ret) {
			ret1 = -EFAULT;
			pr_err("unmap faceid fw fialed\n");
		}
	}

	pr_debug("unmap faceid fw :%p , ret:%d, ret1:%d\n",
	       xvp->firmware2_viraddr , ret , ret1);
	return ((ret!=0)||(ret1!=0)) ? -EFAULT : 0;
}
int sprd_iommu_map_faceid_ion(struct xvp *xvp,struct ion_buf *ion_buf,int fd)
{
	int ret;

	ion_buf->mfd[0] = fd;
	ion_buf->dev = xvp->dev;

	ret = xvp->vdsp_mem_desc->ops->mem_get_ionbuf(xvp->vdsp_mem_desc, ion_buf);
	if (ret) {
		pr_err("fail to get ion_buf\n");
		return -EFAULT;
	}
	ret = xvp->vdsp_mem_desc->ops->mem_iommu_map(xvp->vdsp_mem_desc,
			ion_buf, IOMMU_ALL);
	if (ret) {
		pr_err("fail to iommu map ion\n");
		return -EFAULT;
	}

	pr_debug("Get ion iova %X\n",(uint32_t)ion_buf->iova[0]);
	return 0;
}
int sprd_iommu_ummap_faceid_ion(struct xvp *xvp,struct ion_buf *ion_buf)
{
	int ret = -EFAULT;

	if(NULL == (void*)ion_buf->iova[0]) {
		pr_err("unmap faceid ion addr is NULL\n");
		return ret;
	}
	{
		ret = xvp->vdsp_mem_desc->ops->mem_iommu_unmap(xvp->vdsp_mem_desc,
				ion_buf, IOMMU_ALL);
		if(ret) {
			pr_err("unmap ion buffer failed\n");
			return ret;
		}
	}

	return 0;
}
int sprd_kernel_map_faceid_ion(struct xvp *xvp,
		struct ion_buf *ion_buf,int fd)
{
	int ret;

	ion_buf->mfd[0] = fd;
	ion_buf->dev = xvp->dev;

	ret = xvp->vdsp_mem_desc->ops->mem_get_ionbuf(xvp->vdsp_mem_desc,
			ion_buf);
	if (ret) {
		pr_err("fail to get ion_buf\n");
		return -EFAULT;
	}

	ret = xvp->vdsp_mem_desc->ops->mem_kmap(xvp->vdsp_mem_desc,
			ion_buf);
	if(0 != ret) {
		pr_err("fail to kmap ion_buf\n");
		return -EFAULT;
	}

	pr_debug("kmap addr_p %lx  vaddr:%lx,size %ld\n",
			ion_buf->addr_p[0], ion_buf->addr_k[0],ion_buf->size[0]);
	return 0;
}
int sprd_kernel_unmap_faceid_ion(struct xvp *xvp,struct ion_buf *ion_buf)
{
	unsigned long dst_viraddr = ion_buf->addr_k[0];
	if(dst_viraddr) {
		xvp->vdsp_mem_desc->ops->mem_kunmap(xvp->vdsp_mem_desc, ion_buf);
	}
	return 0;
}
int sprd_faceid_sec_sign(struct xvp *xvp)
{
	bool ret;
	KBC_LOAD_TABLE_V  table;
	unsigned long mem_addr_p;
	size_t img_len;

	/*copy fw to continuous physical address*/
	memcpy((void*)xvp->ion_faceid_fw_sign.addr_k[0],(void*)xvp->firmware2_sign->data,xvp->firmware2_sign->size);

	xvp->firmware2.data = (void*)xvp->ion_faceid_fw_sign.addr_k[0] + SIGN_HEAD_SIZE;
	xvp->firmware2.size = xvp->firmware2_sign->size - SIGN_HEAD_SIZE - SIGN_TAIL_SIZE;

	ret = trusty_kernelbootcp_connect();
	if(!ret)
	{
		pr_err("bootcp connect fail\n");
		return -EACCES;
	}

	memset(&table, 0, sizeof(KBC_LOAD_TABLE_V));

	mem_addr_p = xvp->ion_faceid_fw_sign.addr_p[0];
	img_len = xvp->firmware2_sign->size;

	table.faceid_fw.img_addr = mem_addr_p;
	table.faceid_fw.img_len = img_len;

	pr_debug("fw sign paddr %lX size %zd\n",
			mem_addr_p,img_len);

	ret = kernel_bootcp_verify_vdsp(&table);
	if(!ret)
	{
		pr_err("bootcp verify fail\n");
		return -EACCES;
	}
#if 0
	ret = kernel_bootcp_unlock_ddr(&table);
	if(!ret)
	{
		pr_err("bootcp unlock ddr fail\n");
		return -EACCES;
	}
#endif
	trusty_kernelbootcp_disconnect();
	return 0;
}

int sprd_faceid_secboot_entry(struct xvp *xvp)
{
	bool ret;

	if(xvp->tee_con)
	{
		struct vdsp_msg msg;
		msg.vdsp_type = TA_CADENCE_VQ6;
		msg.msg_cmd = TA_FACEID_ENTER_SEC_MODE;
		ret = vdsp_set_sec_mode(&msg);
		if(!ret)
		{
			pr_err("Entry secure mode fail\n");
			return -EACCES;
		}
	}
	else
	{
		pr_err("vdsp tee connect fail\n");
		return -EACCES;
	}
	return 0;
}
int sprd_faceid_secboot_exit(struct xvp *xvp)
{
	bool ret;

	if(xvp->tee_con)
	{
		struct vdsp_msg msg;
		msg.vdsp_type = TA_CADENCE_VQ6;
		msg.msg_cmd = TA_FACEID_EXIT_SEC_MODE;
		ret = vdsp_set_sec_mode(&msg);
		if(!ret)
		{
			pr_err("Exit secure mode fail\n");
			return -EACCES;
		}
	}
	else
	{
		pr_err("vdsp tee connect fail\n");
		return -EACCES;
	}
	return 0;
}
int sprd_faceid_secboot_init(struct xvp *xvp)
{
	xvp->secmode = true;
	xvp->tee_con = vdsp_ca_connect();
	if(!xvp->tee_con)
	{
		pr_err("vdsp_ca_connect fail\n");
		return -EACCES;
	}
	return 0;
}
int sprd_faceid_secboot_deinit(struct xvp *xvp)
{
	bool ret;

	if(xvp->secmode)
	{
		xvp->secmode = false;
		if(xvp->tee_con)
		{
			struct vdsp_msg msg;
			msg.vdsp_type = TA_CADENCE_VQ6;
			msg.msg_cmd = TA_FACEID_EXIT_SEC_MODE;
			ret = vdsp_set_sec_mode(&msg);
			if(!ret)
				pr_err("sprd_faceid_sec_exit fail\n");

			vdsp_ca_disconnect();
			xvp->tee_con = false;
		}
	}
	return 0;
}

int sprd_faceid_init(struct xvp *xvp)
{
	int ret = 0;

	ret = sprd_alloc_faceid_fwbuffer(xvp);
	if(ret < 0)
		return ret;
	ret = sprd_request_faceid_firmware(xvp);
	if(ret < 0)
	{
		sprd_free_faceid_fwbuffer(xvp);
		return ret;
	}

	sprd_faceid_request_weights(xvp);
    return 0;
}
int sprd_faceid_deinit(struct xvp *xvp)
{
	sprd_release_faceid_firmware(xvp);
	sprd_free_faceid_fwbuffer(xvp);
	sprd_faceid_release_weights(xvp);
	return 0;
}

