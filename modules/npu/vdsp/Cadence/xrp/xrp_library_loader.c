#include "xrp_library_loader.h"
#include "xt_library_loader.h"
#include "xrp_kernel_dsp_interface.h"
#include "xrp_kernel_defs.h"
#include <linux/vmalloc.h>
#include <linux/fs.h>
#include <linux/dma-mapping.h>
#include <linux/elf.h>
#include <linux/firmware.h>
#include <linux/highmem.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include "xrp_internal.h"
#include "xvp_main.h"
#include "xrp_library_loader.h"
#include "xt_library_loader.h"
#define LIBRARY_CMD_PIL_INFO_OFFSET   40
#define LIBRARY_CMD_LOAD_UNLOAD_INPUTSIZE 44

#define XRP_EXAMPLE_V3_NSID_INITIALIZER \
{0x73, 0x79, 0x73, 0x74, 0x65, 0x6d, 0x20, 0x63, \
        0x6d, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
#define LIBRARY_LOAD_UNLOAD_NSID (unsigned char [])XRP_EXAMPLE_V3_NSID_INITIALIZER

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "sprd-vdsp: library_loader %d %d %s : "\
        fmt, current->pid, __LINE__, __func__

static int32_t libinfo_list_size(const struct libinfo_list *list)
{
	if (list == NULL)
		return LIST_ERROR;
	return list->number;
}
static void* libinfo_alloc_element()
{
	struct loadlib_info *pnew = NULL;

	pnew = vmalloc(sizeof(struct loadlib_info));
	if (pnew != NULL)
		memset(pnew, 0, sizeof(struct loadlib_info));

	return pnew;
}
/*index start from 0*/
static int32_t libinfo_list_add(struct libinfo_list *list, void *element, int32_t pos)
{
	int i = 0;
	struct libinfo_node *new_node = NULL;
	struct libinfo_node *node = NULL;

	if (list == NULL)
		return LIST_ERROR;

	new_node = (struct libinfo_node *)vmalloc(sizeof(struct libinfo_node));
	if (new_node == NULL)
		return LIST_NO_MEM;
	memset(new_node, 0, sizeof(struct libinfo_node));
	new_node->element = element;

	if (list->number == 0){
		new_node->next = NULL;
		list->node = new_node;
		list->number++;
		return list->number;
	}
	if (pos < 0 || pos >= list->number)
		pos = list->number;

	node = list->node;
	if (pos == 0){
		new_node->next = list->node;
		list->node = new_node;
		list->number++;
		return list->number;
	}

	while (i + 1 < pos){
		i++;
		node = node->next;
	}
	if (pos == list->number){
		new_node->next = NULL;
		node->next = new_node;
		list->number++;
		return list->number;
	}
	new_node->next = node->next;
	node->next->next = new_node;
	list->number++;

	return list->number;
}

static void *libinfo_list_get(const struct libinfo_list *list, int32_t pos)
{
	int i = 0;
	struct libinfo_node *node = NULL;

	if (list == NULL)
		return NULL;
	if (pos < 0 || pos >= list->number)
		return NULL;
	node = list->node;
	while (i < pos){
		i++;
		node = node->next;
	}

	return node->element;
}

static int32_t libinfo_list_remove(struct libinfo_list *list, int32_t pos)
{
	int i = 0;
	struct libinfo_node *node = NULL;
	struct libinfo_node *del_node = NULL;

	if (list == NULL)
		return LIST_ERROR;
	if (pos < 0 || pos >= list->number)
		return LIST_ERROR;
	node = list->node;
	/*special case*/
	if (pos == 0){
		list->node = node->next;
		list->number--;
		if (node->element)
			vfree(node->element);
		vfree(node);
		return LIST_SUCCESS;
	}

	while (pos > i + 1){
		i++;
		node = node->next;
	}
	del_node = node->next;
	node->next = node->next->next;
	list->number--;
	if (del_node->element)
		vfree(del_node->element);
	vfree(del_node);

	return LIST_SUCCESS;
}
static xt_ptr xt_lib_memcpy(xt_ptr dest, const void * src, unsigned int n, void *user)
{
	memcpy(user, src, n);
	return 0;
}
static xt_ptr xt_lib_memset(xt_ptr s, int c, unsigned int n, void *user)
{
	memset(user, c, n);
	return 0;
}
static int32_t xrp_library_checkprocessing(struct xvp *xvp, const char *libname)
{
	int i;
	struct loadlib_info *libinfo = NULL;

	for (i = 0; i < libinfo_list_size(&(xvp->load_lib.lib_list)); i++) {
		libinfo = libinfo_list_get(&(xvp->load_lib.lib_list), i);
		if (libinfo->lib_state == XRP_LIBRARY_PROCESSING_CMD) {
			if (strcmp(libinfo->libname, libname) == 0)
				return 1;
		}
	}

	return 0;
}
static struct loadlib_info *xrp_library_getlibinfo(struct xvp *xvp, const char *libname)
{
	int i;
	struct loadlib_info *libinfo = NULL;

	for (i = 0; i < libinfo_list_size(&(xvp->load_lib.lib_list)); i++) {
		libinfo = libinfo_list_get(&(xvp->load_lib.lib_list), i);
		if (0 == strcmp(libinfo->libname, libname))
			break;
	}
	/*find and decrease*/
	if (i < libinfo_list_size(&(xvp->load_lib.lib_list)))
		return libinfo;
	else
		return NULL;
}

static int32_t xrp_library_load_internal(struct xvp *xvp, const char* buffer, const char *libname)
{
	unsigned int size;
	int32_t ret = 0;
	struct loadlib_info *new_element;
	unsigned int result;
	struct ion_buf *lib_ion_mem = NULL;
	struct ion_buf *libinfo_ion_mem = NULL;
	void *libback_buffer = NULL;
	void *kvaddr = NULL;
	void *kvaddr_libinfo = NULL;
	phys_addr_t kpaddr, kpaddr_libinfo;

	/*load library to ddr*/
	size = xtlib_pi_library_size((xtlib_packaged_library *)buffer);
	/*alloc ion buffer later*/
	lib_ion_mem = vmalloc(sizeof(struct ion_buf));
	if(NULL == lib_ion_mem) {
		pr_err("[ERROR]vmalloc fail,lib:%p,libinfo:%p\n", lib_ion_mem);
		return -ENOMEM;
	}
	libinfo_ion_mem = vmalloc(sizeof(struct ion_buf));
	if(NULL == libinfo_ion_mem) {
		pr_err("[ERROR]vmalloc fail,lib:%p,libinfo:%p\n", libinfo_ion_mem);
		ret = -ENOMEM;
		goto __load_internal_err0;
	}
	/*alloc lib ion buffer*/
	ret = xvp->vdsp_mem_desc->ops->mem_alloc(xvp->vdsp_mem_desc,
		lib_ion_mem,
		ION_HEAP_ID_MASK_SYSTEM,
		size);
	if (ret != 0) {
		ret = -ENOMEM;
		pr_err("[ERROR]alloc lib_ion_mem failed\n");
		goto __load_internal_err1;
	}
	lib_ion_mem->dev = xvp->dev;
	/*alloc libinfo ion buffer*/
	ret = xvp->vdsp_mem_desc->ops->mem_alloc(xvp->vdsp_mem_desc,
		libinfo_ion_mem,
		ION_HEAP_ID_MASK_SYSTEM,
		sizeof(xtlib_pil_info));
	if (ret != 0) {
		ret = -ENOMEM;
		pr_err("[ERROR]alloc libinfo_ion_mem failed\n");
		goto __load_internal_err2;
	}
	libinfo_ion_mem->dev = xvp->dev;
	ret = xvp->vdsp_mem_desc->ops->mem_kmap(xvp->vdsp_mem_desc, lib_ion_mem);
	if(ret != 0) {
		pr_err("[ERROR]mem_kmap lib_ion_mem failed\n");
		ret = -EINVAL;
		goto __load_internal_err3;
	}
	kvaddr = (void*)lib_ion_mem->addr_k[0];
	ret = xvp->vdsp_mem_desc->ops->mem_iommu_map(xvp->vdsp_mem_desc, lib_ion_mem, IOMMU_ALL);
	if(ret != 0) {
		pr_err("[ERROR] mem_iommu_map lib_ion_mem failed\n");
		ret = -EINVAL;
		goto __load_internal_err4;
	}
	kpaddr = lib_ion_mem->iova[0];

	ret = xvp->vdsp_mem_desc->ops->mem_kmap(xvp->vdsp_mem_desc, libinfo_ion_mem);
	if(ret != 0) {
		pr_err("[ERROR]mem_kmap libinfo_ion_mem failed\n");
		ret = -EINVAL;
		goto __load_internal_err5;
	}
	kvaddr_libinfo = (void*)libinfo_ion_mem->addr_k[0];
	ret = xvp->vdsp_mem_desc->ops->mem_iommu_map(xvp->vdsp_mem_desc, libinfo_ion_mem, IOMMU_ALL);
	if(ret != 0) {
		pr_err("[ERROR]mem_iommu_map libinfo_ion_mem failed\n");
		ret = -EINVAL;
		goto __load_internal_err6;
	}
	kpaddr_libinfo = libinfo_ion_mem->iova[0];
	pr_debug("buffer:%p, kpaddr:%lx, kvaddr:%p, (libinfo)kpaddr:%lx, kvaddr:%p\n",
		buffer, (unsigned long)kpaddr, kvaddr,
		(unsigned long)kpaddr_libinfo, kvaddr_libinfo);

	result = xtlib_host_load_pi_library((xtlib_packaged_library*)buffer, kpaddr,
		(xtlib_pil_info*)kvaddr_libinfo, xt_lib_memcpy, xt_lib_memset, kvaddr);
	if (result == 0){
		/*free ion buffer*/
		pr_err("[ERROR]xtlib_host_load_pi_library failed\n");
		ret = -EINVAL;
		goto __load_internal_err7;
	}

	libback_buffer = vmalloc(size);
	if (libback_buffer == NULL) {
		pr_err("[ERROR]vmalloc back buffer is NULL\n");
		ret = -ENOMEM;
		goto __load_internal_err7;
	}

	/*back up the code for reboot*/
	memcpy(libback_buffer, kvaddr, size);
	new_element = (struct loadlib_info*)libinfo_alloc_element();
	if (new_element == NULL) {
		/*free ion buffer*/
		pr_err("[ERROR]libinfo_alloc_element failed\n");
		ret = -ENOMEM;
		goto __load_internal_err8;
	}else {
		sprintf(new_element->libname, "%s", libname);
		/*may be change later*/
		new_element->address_start = 0;
		new_element->length = size;
		new_element->load_count = 0;
		new_element->ionhandle = lib_ion_mem;
		new_element->ion_phy = (phys_addr_t)kpaddr;
		new_element->ion_kaddr = kvaddr;
		new_element->pil_ionhandle = libinfo_ion_mem;
		new_element->pil_info = kpaddr_libinfo;
		new_element->pil_info_kaddr = kvaddr_libinfo;
		new_element->lib_state = XRP_LIBRARY_LOADING;
		new_element->code_back_kaddr = libback_buffer;
	}
	libinfo_list_add(&xvp->load_lib.lib_list, new_element,
		libinfo_list_size(&xvp->load_lib.lib_list));

	return 0;
__load_internal_err8:
	vfree(libback_buffer);
__load_internal_err7:
	xvp->vdsp_mem_desc->ops->mem_iommu_unmap(xvp->vdsp_mem_desc , libinfo_ion_mem , IOMMU_ALL);
__load_internal_err6:
	xvp->vdsp_mem_desc->ops->mem_kunmap(xvp->vdsp_mem_desc, libinfo_ion_mem);
__load_internal_err5:
	xvp->vdsp_mem_desc->ops->mem_iommu_unmap(xvp->vdsp_mem_desc, lib_ion_mem, IOMMU_ALL);
__load_internal_err4:
	xvp->vdsp_mem_desc->ops->mem_kunmap(xvp->vdsp_mem_desc, lib_ion_mem);
__load_internal_err3:
	xvp->vdsp_mem_desc->ops->mem_free(xvp->vdsp_mem_desc, libinfo_ion_mem);
__load_internal_err2:
	xvp->vdsp_mem_desc->ops->mem_free(xvp->vdsp_mem_desc, lib_ion_mem);
__load_internal_err1:
	vfree(libinfo_ion_mem);
__load_internal_err0:
	vfree(lib_ion_mem);
	return ret;
}
enum load_unload_flag xrp_check_load_unload(struct xvp *xvp, struct xrp_request *rq)
{
	__u32 indata_size;
	enum load_unload_flag load_flag = XRP_NOT_LOAD_UNLOAD;
	__u8 *tempbuffer = NULL;
	void *tempsrc = NULL;

	indata_size = rq->ioctl_queue.in_data_size;
	if (0 == strcmp(rq->nsid, LIBRARY_LOAD_UNLOAD_NSID)) {
		if (indata_size > XRP_DSP_CMD_INLINE_DATA_SIZE)
			tempsrc = (void*)(rq->ioctl_queue.in_data_addr);
		else
			tempsrc = rq->in_data;

		tempbuffer = vmalloc(indata_size);
		if (copy_from_user(tempbuffer, tempsrc, indata_size)) {
			vfree(tempbuffer);
			return -EFAULT;
		}
		load_flag = *tempbuffer;
		vfree(tempbuffer);
	}

	return load_flag;
}
#ifndef USE_RE_REGISTER_LIB
int32_t xrp_library_setall_missstate(struct xvp *xvp)
{
	int i;
	struct loadlib_info *libinfo = NULL;

	for (i = 0; i < libinfo_list_size(&(xvp->load_lib.lib_list)); i++) {
		libinfo = libinfo_list_get(&(xvp->load_lib.lib_list), i);
		libinfo->lib_state = XRP_LIBRARY_MISSED_STATE;
	}

	return 0;
}
#endif
static int32_t xrp_library_decrease(struct xvp *xvp, const char *libname)
{
	int i;
	struct loadlib_info *libinfo = NULL;

	for (i = 0; i < libinfo_list_size(&(xvp->load_lib.lib_list)); i++) {
		libinfo = libinfo_list_get(&(xvp->load_lib.lib_list), i);
		if (0 == strcmp(libinfo->libname, libname))
			break;
	}
	/*find and decrease*/
	if (i < libinfo_list_size(&(xvp->load_lib.lib_list)))
		libinfo->load_count--;
	else
		return -EINVAL;
	pr_debug("loadcount:%d libname:%s\n", libinfo->load_count, libname);

	return libinfo->load_count;
}
static int32_t xrp_library_increase(struct xvp *xvp, const char *libname)
{
	int i;
	struct loadlib_info *libinfo = NULL;

	for (i = 0; i < libinfo_list_size(&(xvp->load_lib.lib_list)); i++) {
		libinfo = libinfo_list_get(&(xvp->load_lib.lib_list), i);
		if (0 == strcmp(libinfo->libname, libname))
			break;
	}
	/*find and decrease*/
	if (i < libinfo_list_size(&(xvp->load_lib.lib_list)))
		libinfo->load_count++;
	else
		return -EINVAL;

	pr_debug("loadcount:%d, libname:%s\n", libinfo->load_count, libname);
	return libinfo->load_count;
}
int32_t xrp_library_decrelease(struct xvp *xvp, const char *libname)
{
	int i;
	int ret;
	struct loadlib_info *libinfo = NULL;

	/*decrease load_count*/
	for (i = 0; i < libinfo_list_size(&(xvp->load_lib.lib_list)); i++) {
		libinfo = libinfo_list_get(&(xvp->load_lib.lib_list), i);
		if (0 == strcmp(libinfo->libname, libname))
			break;
	}
	if (i < libinfo_list_size(&(xvp->load_lib.lib_list))) {
		if (libinfo->load_count != 0)
			libinfo->load_count--;
		pr_debug("load_count:%d, libname:%s\n", libinfo->load_count, libname);
		if (libinfo->load_count == 0) {
			xvp->vdsp_mem_desc->ops->mem_kunmap(xvp->vdsp_mem_desc,
				libinfo->ionhandle);
			xvp->vdsp_mem_desc->ops->mem_iommu_unmap(xvp->vdsp_mem_desc,
				libinfo->ionhandle, IOMMU_ALL);
			xvp->vdsp_mem_desc->ops->mem_free(xvp->vdsp_mem_desc,
				libinfo->ionhandle);
			vfree(libinfo->ionhandle);
			xvp->vdsp_mem_desc->ops->mem_kunmap(xvp->vdsp_mem_desc,
				libinfo->pil_ionhandle);
			xvp->vdsp_mem_desc->ops->mem_iommu_unmap(xvp->vdsp_mem_desc,
				libinfo->pil_ionhandle, IOMMU_ALL);
			xvp->vdsp_mem_desc->ops->mem_free(xvp->vdsp_mem_desc,
				libinfo->pil_ionhandle);
			vfree(libinfo->pil_ionhandle);
			if (libinfo->code_back_kaddr != NULL)
				vfree(libinfo->code_back_kaddr);
			/*remove this lib element*/
			libinfo_list_remove(&(xvp->load_lib.lib_list), i);
		}
		ret = 0; /*loaded*/
	}else {
		pr_err("[ERROR]not find lib [%s]\n", libname);
		ret = 1;
	}

	return ret;
}
static int32_t xrp_library_getloadunload_libname(struct xvp *xvp,
	struct xrp_request *rq, char *outlibname)
{
	__u32 indata_size;
	int32_t ret = 0;
	void *tempsrc = NULL;
	__u8 *tempbuffer = NULL;

	indata_size = rq->ioctl_queue.in_data_size;
	if (0 == strcmp(rq->nsid, LIBRARY_LOAD_UNLOAD_NSID)) {
		/*check libname*/
		if (indata_size > XRP_DSP_CMD_INLINE_DATA_SIZE)
			tempsrc = (void*)(rq->ioctl_queue.in_data_addr);
		else
			tempsrc = (void*)(rq->in_data);

		tempbuffer = vmalloc(indata_size);
		if (copy_from_user(tempbuffer, tempsrc, indata_size)) {
			pr_err("[ERROR]copy from user failed\n");
			ret = -EINVAL;
		}
		/*input_vir first byte is load or unload*/
		sprintf(outlibname, "%s", tempbuffer + 1);
		vfree(tempbuffer);
	}else {
		ret = -EINVAL;
	}
	pr_debug("outlibname:%s, ret:%d\n", outlibname, ret);

	return ret;
}
static int32_t xrp_library_kmap_ionbuf(struct ion_buf *ionbuf,
	__u8 **buffer, struct dma_buf **dmabuf)
{
	struct dma_buf *dma_buf;
	int32_t mapcount = 0;
	*buffer = NULL;

	if ((ionbuf == NULL) || (ionbuf->mfd[0] < 0)) {
		pr_err("[ERROR]ion dsp pool is NULL\n");
		return -EINVAL;
	}
	dma_buf = dma_buf_get(ionbuf->mfd[0]);
	if (IS_ERR_OR_NULL(dma_buf)) {
		pr_err("[ERROR]dma_buf_get fd:%d\n", ionbuf->mfd[0]);
		return -EINVAL;
	}
	/*workaround need to process later*/
	while ((*buffer == NULL) && (mapcount < 5)) {
		*buffer = sprd_ion_map_kernel(dma_buf, 0);
		mapcount++;
	}
	*dmabuf = dma_buf;
	/*buffer index 0 is input lib buffer*/
	pr_debug("[kmap]mfd:%d, dev:%p, map vaddr is:%p, mapcount:%d\n",
		ionbuf->mfd[0], ionbuf->dev, *buffer, mapcount);
	if (NULL == *buffer)
		return -EFAULT;

	return 0;
}
static int32_t xrp_library_kunmap_ionbuf(struct dma_buf *dmabuf)
{
	sprd_ion_unmap_kernel(dmabuf, 0);
	dma_buf_put(dmabuf);

	return 0;
}
static int32_t xrp_library_unload(struct xvp *xvp,
	struct xrp_request *rq, char *libname)
{
	int ret = 0;
	__u32 indata_size;
	__u8 *inputbuffer = NULL;
	struct dma_buf* dmabuf = NULL;
	struct loadlib_info *libinfo = NULL;

	indata_size = rq->ioctl_queue.in_data_size;
	if (0 == strcmp(rq->nsid, LIBRARY_LOAD_UNLOAD_NSID)
		&& (indata_size >= LIBRARY_CMD_LOAD_UNLOAD_INPUTSIZE)) {
		libinfo = xrp_library_getlibinfo(xvp, libname);
		if (libinfo != NULL) {
			ret = xrp_library_kmap_ionbuf(&rq->ion_in_buf, &inputbuffer, &dmabuf);
			if (ret != 0) {
				pr_err("[ERROR]xrp_library_kmap_ionbuf failed ret:%d\n", ret);
				return -EFAULT;
			}
			*((unsigned int*)((__u8 *)inputbuffer + 40)) = libinfo->pil_info;
			xrp_library_kunmap_ionbuf(dmabuf);
			wmb();
		}else {
			pr_err("[ERROR]libinfo null\n");
			ret = -EINVAL;
		}
	}else {
		pr_err("[ERROR]nsid is not unload\n");
		ret = -EINVAL;
	}
	pr_debug("unload nsid[%s], ret[%d]\n", rq->nsid, ret);

	return ret;
}
/* return value 0 is need load, 1 is loaded already*/
static int32_t xrp_library_load(struct xvp *xvp,
	struct xrp_request *rq, char *outlibname)
{
	__u32 indata_size;
	__u8 load_flag = 0;
	int32_t ret = 0;
	int i;
	void *tempsrc = NULL;
	__u8 *tempbuffer = NULL;
	struct loadlib_info *libinfo = NULL;
	__u8 *input_ptr = NULL;
	__u8 *libbuffer = NULL;
	__u8 *inputbuffer = NULL;
	char libname[64];
	struct dma_buf* dmabuf = NULL;

	indata_size = rq->ioctl_queue.in_data_size;

	/*check whether load cmd*/
	if (0 == strcmp(rq->nsid, LIBRARY_LOAD_UNLOAD_NSID)) {
		/*check libname*/
		if (indata_size > XRP_DSP_CMD_INLINE_DATA_SIZE)
			tempsrc = (void*)(rq->ioctl_queue.in_data_addr);
		else
			tempsrc = (void*)(rq->in_data);

		tempbuffer = vmalloc(indata_size);
		if (copy_from_user(tempbuffer, tempsrc, indata_size)) {
			pr_err("[ERROR]copy from user failed\n");
			vfree(tempbuffer);
			return -EFAULT;
		}
		input_ptr = tempbuffer;
		/*input_vir first byte is load or unload*/
		load_flag = *input_ptr;

		if (XRP_LOAD_LIB_FLAG == load_flag) {
			/*load*/
			sprintf(libname, "%s", input_ptr + 1);
			/*check whether loaded*/
			for (i = 0; i < libinfo_list_size(&(xvp->load_lib.lib_list)); i++) {
				libinfo = libinfo_list_get(&(xvp->load_lib.lib_list), i);
				if (0 == strcmp(libinfo->libname, libname))
					break;
			}
			if (i < libinfo_list_size(&(xvp->load_lib.lib_list))) {
				libinfo->load_count++;
				pr_debug("lib[%s]already loaded\n", libname);
				ret = 1;/*loaded*/
			}else {
				/*not loaded alloc libinfo node ,load internal*/
				ret = xrp_library_kmap_ionbuf(rq->ion_dsp_pool, &libbuffer, &dmabuf);
				if (ret != 0) {
					pr_err("[ERROR]kmap ionbuf failed\n");
					vfree(tempbuffer);
					return -EINVAL;
				}
				ret = xrp_library_load_internal(xvp, libbuffer, libname);
				if (ret != 0) {
					pr_err("[ERROR]xrp_library_load_internal ret:%d\n", ret);
					xrp_library_kunmap_ionbuf(dmabuf);
					vfree(tempbuffer);
					ret = -ENOMEM;
					return ret;
				}
				xrp_library_kunmap_ionbuf(dmabuf);
				/*
				re edit rq for register libname, input data:
				input[0] load unload flag
				input[1] ~input[32]-libname,
				input[LIBRARY_CMD_PIL_INFO_OFFSET]~input[43]-libinfo addr
				*/
				libinfo = xrp_library_getlibinfo(xvp, libname);
				if (NULL == libinfo) {
					pr_err("[ERROR]libinfo NULL\n");
					xrp_library_decrelease(xvp, libname);
					vfree(tempbuffer);
					ret = -ENOMEM;
					return ret;
				}else {
					*((uint32_t*)(input_ptr + LIBRARY_CMD_PIL_INFO_OFFSET)) =
						libinfo->pil_info;
					pr_debug("nsid:%s, loadflag:%d, libname:%s,"
						"pil_info:%x,indata_size:%d\n",
						rq->nsid, load_flag, libname,
						libinfo->pil_info, indata_size);
					sprintf(outlibname, "%s", libname);
				}
				ret = xrp_library_kmap_ionbuf(&rq->ion_in_buf, &inputbuffer,
					&dmabuf);
				if (ret != 0) {
					pr_err("[ERROR]kmap ionbuf failed\n");
					vfree(tempbuffer);
					xrp_library_decrelease(xvp, libname);
					return -EFAULT;
				}
				memcpy(inputbuffer, tempbuffer, indata_size);
				xrp_library_kunmap_ionbuf(dmabuf);
				wmb();
			}
		}else {
			pr_err("[ERROR]not load flag\n");
			ret = -EINVAL;
		}
		vfree(tempbuffer);
		return ret;
	}else{
		return 0;
	}
}
#if 1
int32_t xrp_library_release_all(struct xvp *xvp)
{
	struct loadlib_info *libinfo = NULL;

	mutex_lock(&xvp->load_lib.libload_mutex);
	while (0 != libinfo_list_size(&(xvp->load_lib.lib_list))) {
		libinfo = libinfo_list_get(&(xvp->load_lib.lib_list), 0);
		/*unmap iommu and release ion buffer*/
		if ((libinfo != NULL)) {
			xvp->vdsp_mem_desc->ops->mem_kunmap(xvp->vdsp_mem_desc,
				libinfo->ionhandle);
			xvp->vdsp_mem_desc->ops->mem_iommu_unmap(xvp->vdsp_mem_desc,
				libinfo->ionhandle, IOMMU_ALL);
			xvp->vdsp_mem_desc->ops->mem_free(xvp->vdsp_mem_desc,
				libinfo->ionhandle);
			vfree(libinfo->ionhandle);

			xvp->vdsp_mem_desc->ops->mem_kunmap(xvp->vdsp_mem_desc,
				libinfo->pil_ionhandle);
			xvp->vdsp_mem_desc->ops->mem_iommu_unmap(xvp->vdsp_mem_desc,
				libinfo->pil_ionhandle, IOMMU_ALL);
			xvp->vdsp_mem_desc->ops->mem_free(xvp->vdsp_mem_desc,
				libinfo->pil_ionhandle);
			vfree(libinfo->pil_ionhandle);
			if (libinfo->code_back_kaddr != NULL)
				vfree(libinfo->code_back_kaddr);
			libinfo_list_remove(&(xvp->load_lib.lib_list), 0);
			pr_debug("release ion handle, pil handle\n");
		}else {
			pr_err("libinfo is NULL may be error but also remove node\n");
			libinfo_list_remove(&(xvp->load_lib.lib_list), 0);
		}
	}
	mutex_unlock(&xvp->load_lib.libload_mutex);

	return 0;
}
#endif
#ifdef USE_RE_REGISTER_LIB
static int32_t xrp_register_libs(struct xvp *xvp , struct xrp_comm *comm)
{
	int i;
	int ret = 0;
	int realret = 0;
	__u8 *input_ptr = NULL;
	struct loadlib_info *libinfo = NULL;
	struct ion_buf input_ion_buf;
	phys_addr_t vdsp_addr;
	struct xrp_request rq;

	rq.ioctl_queue.flags = XRP_QUEUE_FLAG_NSID;
	rq.ioctl_queue.in_data_size = LIBRARY_CMD_LOAD_UNLOAD_INPUTSIZE;
	rq.ioctl_queue.out_data_size = 0;
	rq.ioctl_queue.buffer_size = 0;
	rq.ioctl_queue.in_data_addr = 0;
	rq.ioctl_queue.out_data_addr = 0;
	rq.ioctl_queue.buffer_addr = 0;
	rq.ioctl_queue.nsid_addr = 0;
	rq.n_buffers = 0;
	rq.buffer_mapping = NULL;
	rq.dsp_buffer = NULL;
	/*may change later*/
	rq.in_data_phys = 0;
	/*alloc input cmd ion buffer*/
	ret = sprd_vdsp_ion_alloc(&input_ion_buf, ION_HEAP_ID_MASK_SYSTEM,
		rq.ioctl_queue.in_data_size);
	if(ret != 0) {
		pr_err("alloc input_ion_buf failed\n");
		return -ENOMEM;
	}
	input_ion_buf.dev = xvp->dev;
	sprd_vdsp_kmap(&input_ion_buf);
	input_ptr = (void*)input_ion_buf.addr_k[0];
	sprd_vdsp_iommu_map(&input_ion_buf, IOMMU_ALL);
	vdsp_addr = input_ion_buf.iova[0];
	rq.in_data_phys = vdsp_addr;
	memset(rq.nsid, 0, sizeof(rq.nsid));
	sprintf(rq.nsid, "%s", LIBRARY_LOAD_UNLOAD_NSID);
	for (i = 0; i < libinfo_list_size(&(xvp->load_lib.lib_list)); i++) {
		libinfo = libinfo_list_get(&(xvp->load_lib.lib_list), i);
		if (libinfo->load_count > 0) {
			/*re send register cmd*/
			if (libinfo->code_back_kaddr == NULL) {
				realret = -1;
				pr_err("fail\n");
				break;
			}
			memcpy(libinfo->code_back_kaddr, libinfo->ion_kaddr,
				libinfo->length);
			input_ptr[0] = XRP_LOAD_LIB_FLAG;
			sprintf(input_ptr + 1, "%s", libinfo->libname);
			*((unsigned int*)(input_ptr + LIBRARY_CMD_PIL_INFO_OFFSET)) =
				libinfo->pil_info;
			sprd_fill_hw_request(comm->comm , &rq);
			xrp_send_device_irq(xvp);
			if(xvp->host_irq_mode)
				ret = xvp_complete_cmd_irq(xvp, comm, xrp_cmd_complete);
			else
				ret = xvp_complete_cmd_poll(xvp, comm, xrp_cmd_complete);

			xrp_panic_check(xvp);
			if(0 == ret)
				ret = sprd_complete_hw_request(comm->comm, &rq);
			if(ret != 0) {
				/*set invalid*/
				pr_err("re load lib:%s failed\n", libinfo->libname);
				libinfo->lib_state = XRP_LIBRARY_IDLE;
				realret = -1;
			}else {
				libinfo->lib_state = XRP_LIBRARY_LOADED;
				pr_debug("re load lib:%s ok\n", libinfo->libname);
			}
		}
	}
	sprd_vdsp_iommu_unmap(&input_ion_buf, IOMMU_ALL);
	sprd_vdsp_kunmap(&input_ion_buf);
	sprd_vdsp_ion_free(&input_ion_buf);

	return realret;
}
#endif
/*return value 0 is ok, other value is fail or no need process continue*/
int32_t xrp_pre_process_request(struct xvp *xvp, struct xrp_request *rq,
	enum load_unload_flag loadflag, char *libname)
{
	int32_t lib_result, load_count;
	struct loadlib_info *libinfo = NULL;

	if (loadflag == XRP_LOAD_LIB_FLAG) {
		lib_result = xrp_library_load(xvp, rq, libname);
		if (0 != lib_result) {
			/*has loaded needn't reload*/
			if (lib_result != 1) {
				pr_err("[ERROR]result:%d\n", lib_result);
				return -EFAULT;
			}else {
				pr_err("[ERROR]already loaded needn't reload\n");
				return -ENXIO;
			}
		}else {
			/*re-edit the rq for register*/
			pr_debug("Load libname:%s\n", libname);
			return 0;
		}
	}else if (loadflag == XRP_UNLOAD_LIB_FLAG) {
		lib_result = xrp_library_getloadunload_libname(xvp, rq, libname);
		if (lib_result == 0) {
			if (0 != xrp_library_checkprocessing(xvp, libname)) {
				pr_err("[ERROR]the same lib is processing invalid operation\n");
				return -EINVAL;
			}
			load_count = xrp_library_decrease(xvp, libname);
			libinfo = xrp_library_getlibinfo(xvp, libname);
			/*if not need unload, maybe count is not zero, return after unmap*/
			if (load_count > 0) {
				pr_debug("needn't unload because load count is not zero\n");
				return -ENXIO;
			}else if (0 == load_count){
#ifndef USE_RE_REGISTER_LIB
				if (libinfo != NULL) {
					if (libinfo->lib_state == XRP_LIBRARY_MISSED_STATE) {
						pr_debug("libname:%s is missed state, release here\n",
							libname);
						xrp_library_decrelease(xvp, libname);
						return -ENXIO;
					}
				}
#endif
				/*
				if need unload may be modify libinfo addr,
				only follow the default send cmd
				*/
				lib_result = xrp_library_unload(xvp, rq, libname);
				if (lib_result != 0) {
					pr_err("[ERROR]xrp_library_unload failed:%d\n", lib_result);
					xrp_library_increase(xvp , libname);
					return -EINVAL;
				}
			}else {
				pr_err("[ERROR]decrease count error:%d, libname:%s\n",
					load_count, libname);
				return -ENXIO;
			}
			if (libinfo != NULL)
				libinfo->lib_state = XRP_LIBRARY_UNLOADING;
			pr_debug("Unload libname:%s\n", libname);
			return 0;
		}else {
			pr_err("[ERROR]get libname error, libname:%s\n", libname);
			return -EINVAL;
		}
	}else {
		/*check whether libname unloading state, if unloading return*/
		libinfo = xrp_library_getlibinfo(xvp, rq->nsid);
		if (libinfo != NULL) {
			if (libinfo->lib_state != XRP_LIBRARY_LOADED) {
				pr_err("[ERROR]lib:%s, libstate is:%d not XRP_LIBRARY_LOADED\n",
					rq->nsid, libinfo->lib_state);
				return -EINVAL;
			}
			/*set processing libname*/
			libinfo->lib_state = XRP_LIBRARY_PROCESSING_CMD;
		}else {
			pr_err("libinfo null\n");
		}
		pr_debug("Command libname:%s\n", rq->nsid);
		return 0;
	}
}
int post_process_request(struct xvp *xvp, struct xrp_request *rq,
	const char* libname, enum load_unload_flag load_flag, int32_t resultflag)
{
	struct loadlib_info *libinfo = NULL;
	int32_t ret = 0;

	pr_debug("load_flag[%d], resultflag[%d]\n", load_flag, resultflag);
	if (load_flag == XRP_LOAD_LIB_FLAG) {
		if (0 == resultflag){
			xrp_library_increase(xvp, libname);
			libinfo = xrp_library_getlibinfo(xvp, libname);
			if (NULL != libinfo)
				libinfo->lib_state = XRP_LIBRARY_LOADED;
		}else {
			/*load failed release here*/
			xrp_library_decrelease(xvp, libname);
			pr_err("[ERROR]libname:%s, load failed, release\n", libname);
			ret = -EFAULT;
		}
	}else if (load_flag == XRP_UNLOAD_LIB_FLAG) {
		if (0 == resultflag) {
			libinfo = xrp_library_getlibinfo(xvp, libname);
			if (NULL != libinfo)
				libinfo->lib_state = XRP_LIBRARY_IDLE;
			pr_info("libname:%s, libstate XRP_LIBRARY_IDLE libinfo:%p\n", libname , libinfo);
		} else {
			xrp_library_increase(xvp , libname);
			pr_err("[ERROR]libname:%s, unload failed\n", libname);
			ret = -EFAULT;
		}
	}else {
		/*remove processing lib*/
		libinfo = xrp_library_getlibinfo(xvp, rq->nsid);
		if (libinfo != NULL) {
			if (libinfo->lib_state != XRP_LIBRARY_PROCESSING_CMD) {
				pr_err("[ERROR]lib:%s processing cmd, but state error\n",
					rq->nsid);
				ret = -EINVAL;
			}
			/*set processing libname*/
			libinfo->lib_state = XRP_LIBRARY_LOADED;
		}
		/*set processing lib state*/
		pr_debug("lib:%s, process cmd over\n", rq->nsid);
	}

	return ret;
}

