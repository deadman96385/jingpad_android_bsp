/*
 *****************************************************************************
 * Copyright (c) Imagination Technologies Ltd.
 *
 * The contents of this file are subject to the MIT license as set out below.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Alternatively, the contents of this file may be used under the terms of the
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above.
 *
 * If you wish to allow use of your version of this file only under the terms
 * of GPL, and not to allow others to use your version of this file under the
 * terms of the MIT license, indicate your decision by deleting the provisions
 * above and replace them with the notice and other provisions required by GPL
 * as set out in the file called "GPLHEADER" included in this distribution. If
 * you do not delete the provisions above, a recipient may use your version of
 * this file under the terms of either the MIT license or GPL.
 *
 * This License is also included in this distribution in the file called
 * "MIT_COPYING".
 *
 *****************************************************************************/

	

#include <linux/slab.h>
#include <asm/current.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/pm_runtime.h>

#include <uapi/img_mem_man.h>
#include <img_mem_man.h>
#include "vha_common.h"
#include "vha_plat.h"
#include "vha_chipdep.h"

static uint32_t default_mem_heap = IMG_MEM_MAN_HEAP_ID_INVALID;
module_param(default_mem_heap, uint, 0444);
MODULE_PARM_DESC(default_mem_heap,
		"default heap to use when allocating device memory, \
		when 'invalid' -> user requested id will be used.");

static void vha_session_pm_get(struct vha_session *session)
{
	struct vha_dev *vha = session->vha;

	mutex_lock(&session->pm_lock);

	pm_runtime_get_sync(vha->dev);
	session->pm_count++;

	mutex_unlock(&session->pm_lock);
}

static void vha_session_pm_put(struct vha_session *session)
{
	struct vha_dev *vha = session->vha;

	mutex_lock(&session->pm_lock);

	if (session->pm_count > 0) {
		pm_runtime_put(vha->dev);
		session->pm_count--;
	}

	mutex_unlock(&session->pm_lock);
}

static void vha_session_pm_release(struct vha_session *session)
{
	struct vha_dev *vha = session->vha;

	mutex_lock(&session->pm_lock);

	while (session->pm_count > 0) {
		dev_info(vha->dev, "%s pm_count is %d\n", __FUNCTION__, session->pm_count);
		pm_runtime_put(vha->dev);
		session->pm_count--;
	}

	mutex_unlock(&session->pm_lock);
}

static ssize_t vha_read(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	struct vha_session *session = file->private_data;
	struct vha_dev *vha = session->vha;
	struct miscdevice *miscdev = &vha->miscdev;
	struct vha_rsp *rsp;
	int ret;

	dev_dbg(miscdev->this_device, "%s: PID: %d, vha: %p, link: %p\n",
			__func__, task_pid_nr(current), vha, session);

	ret = mutex_lock_interruptible(&vha->lock);
	if (ret)
		return ret;

	while (list_empty(&session->rsps)) {
		mutex_unlock(&vha->lock);

		if (file->f_flags & O_NONBLOCK) {
			dev_dbg(miscdev->this_device,
				"%s: returning, no block!\n", __func__);
			return -EAGAIN;
		}
		dev_dbg(miscdev->this_device, "%s: going to sleep\n", __func__);
		if (wait_event_interruptible(session->wq,
						!list_empty(&session->rsps))) {
			dev_dbg(miscdev->this_device, "%s: signal\n", __func__);
			return -ERESTARTSYS;
		}

		dev_dbg(miscdev->this_device, "%s: woken up\n", __func__);

		ret = mutex_lock_interruptible(&vha->lock);
		if (ret)
			return -ERESTARTSYS;
	}

	if (list_empty(&session->rsps)) {
		ret = 0;
		goto out_unlock;
	}

	rsp = list_first_entry(&session->rsps, struct vha_rsp, list);
	if (rsp->size > count) {
		dev_warn(miscdev->this_device,
			"WARNING: unexpected read buffer size (%zd/%zd). "
			"Probably user space and kernel space are out of step\n",
			count, rsp->size);
		ret = -EINVAL;
		goto out_unlock;
	}

	ret = copy_to_user(buf, &rsp->user_rsp, rsp->size);
	if (ret) {
		ret = -EFAULT;
		goto out_unlock;
	}

	list_del(&rsp->list);
	mutex_unlock(&vha->lock);
	ret = rsp->size;

	print_hex_dump_debug("VHA RSP: ", DUMP_PREFIX_NONE,
				4, 4, (uint32_t *)&rsp->user_rsp,
				ALIGN(rsp->size, 4), false);

	kfree(rsp);

	return ret;

out_unlock:
	mutex_unlock(&vha->lock);
	return ret;
}

static unsigned int vha_poll(struct file *file, poll_table *wait)
{
	unsigned long req_events = poll_requested_events(wait);
	struct vha_session *session = file->private_data;
	struct vha_dev *vha = session->vha;
	struct miscdevice *miscdev = &vha->miscdev;
	unsigned int mask = 0;
	int ret;

	dev_dbg(miscdev->this_device, "%s: PID: %d, vha: %p, link: %p\n",
			__func__, task_pid_nr(current), vha, session);

	ret = mutex_lock_interruptible(&vha->lock);
	if (ret)
		return POLLERR;

	if (req_events & (POLLIN | POLLRDNORM)) {
		/* Register for event */
		poll_wait(file, &session->wq, wait);
		if (session->oom)
			mask = POLLERR;
		if (!list_empty(&session->rsps))
			mask = POLLIN | POLLRDNORM;
		/* if no response item available just return 0 */
	}

	mutex_unlock(&vha->lock);
	return mask;
}

/* read a message from user, and queue it up to be sent to hw */
static ssize_t vha_write(struct file *file, const char __user *buf,
		size_t size, loff_t *offset)
{
	struct vha_session *session = (struct vha_session *)file->private_data;
	struct vha_dev *vha = session->vha;
	struct miscdevice *miscdev = &vha->miscdev;
	int ret;
	struct vha_cmd *cmd;

	dev_dbg(miscdev->this_device,
		"%s: PID: %d, vha: %p, session: %p, size: %zu\n",
		__func__, task_pid_nr(current), vha, session, size);

#ifdef CONFIG_FAULT_INJECTION
	current->make_it_fail = vha->fault_inject;
#endif

	if (size < sizeof(struct vha_user_cmd)) {
		dev_err(miscdev->this_device, "%s: msg too small\n", __func__);
		return -EINVAL;
	}

	cmd = kzalloc(sizeof(*cmd) - sizeof(cmd->user_cmd) + size, GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	cmd->size = size;
	cmd->session = session;

	ret = copy_from_user(&cmd->user_cmd, buf, size);
	if (ret) {
		dev_err(miscdev->this_device, "%s: copy failed!\n", __func__);
		ret = -EFAULT;
		goto out_free_item;
	}

	ret = mutex_lock_interruptible(&vha->lock);
	if (ret)
		goto out_free_item;

	ret = vha_add_cmd(session, cmd);
	mutex_unlock(&vha->lock);
	if (ret)
		goto out_free_item;

	return size;

out_free_item:
	kfree(cmd);
	return ret;
}

static int vha_open(struct inode *inode, struct file *file)
{
	struct miscdevice  *miscdev = (struct miscdevice *)file->private_data;
	struct vha_dev     *vha = container_of(miscdev, struct vha_dev, miscdev);
	struct vha_session *session;
	int ret;

	dev_dbg(miscdev->this_device, "%s: PID: %d, vha: %p\n",
		__func__, task_pid_nr(current), vha);

#ifdef CONFIG_FAULT_INJECTION
	current->make_it_fail = vha->fault_inject;
#endif

	session = devm_kzalloc(miscdev->this_device, sizeof(struct vha_session),
		GFP_KERNEL);
	if (!session)
		return -ENOMEM;

	session->vha = vha;

	/* memory context for all buffers used by this session */
	ret = img_mem_create_proc_ctx(&session->mem_ctx);
	if (ret) {
		dev_err(miscdev->this_device, "%s: failed to create context!\n",
			__func__);
		devm_kfree(miscdev->this_device, session);
		return ret;
	}

	INIT_LIST_HEAD(&session->cmds);
	INIT_LIST_HEAD(&session->rsps);
	INIT_LIST_HEAD(&session->bufs);
	init_waitqueue_head(&session->wq);

	mutex_init(&session->pm_lock);

	file->private_data = session;
	pm_runtime_get_sync(vha->dev);

	ret = vha_add_session(session);
	if (ret) {
		img_mem_destroy_proc_ctx(session->mem_ctx);
		devm_kfree(miscdev->this_device, session);
		file->private_data = NULL;
	}
	pm_runtime_put(vha->dev);

	return ret;
}

static int vha_release(struct inode *inode, struct file *file)
{
	struct vha_session *session = (struct vha_session *)file->private_data;
	struct vha_dev     *vha     = session->vha;
	struct miscdevice  *miscdev = &vha->miscdev;

	dev_dbg(miscdev->this_device, "%s: PID: %d, vha: %p, session: %p\n",
		__func__, task_pid_nr(current), vha, session);

	vha_session_pm_get(session);

	vha_rm_session(session);
	img_mem_destroy_proc_ctx(session->mem_ctx);

	vha_session_pm_release(session);

	devm_kfree(miscdev->this_device, session);
	file->private_data = NULL;

	return 0;
}

static long vha_ioctl_get_core_props(struct vha_session *session,
					void __user *buf)
{
	struct vha_dev *vha = session->vha;
	struct miscdevice *miscdev = &vha->miscdev;

	dev_dbg(miscdev->this_device, "%s: session %p\n", __func__, session);

	if (copy_to_user(buf, &vha->core_props,
			sizeof(struct vha_core_props))) {
		dev_err(miscdev->this_device, "%s: copy to user failed!\n",
			__func__);
		return -EFAULT;
	}

	return 0;
}

static long vha_ioctl_query_heaps(struct vha_session *session, void __user *buf)
{
	struct vha_heaps_data data;
	int ret;
	int id, i = 0;

	memset(&data, 0, sizeof(data));

	for (id = IMG_MEM_MAN_MIN_HEAP; id <= IMG_MEM_MAN_MAX_HEAP &&
			i < VHA_MAX_HEAPS ; id++) {
		uint8_t type;
		uint32_t attrs;

		ret = img_mem_get_heap_info(id, &type, &attrs);
		if (!ret) {
			struct vha_heap_data *info = &data.heaps[i++];
			info->id = id;
			info->type = type;
			info->attributes = attrs;
		} else
			break;
	}
	if (copy_to_user(buf, &data, sizeof(data)))
		return -EFAULT;

	return 0;
}

static long vha_ioctl_alloc(struct vha_session *session, void __user *buf)
{
	struct vha_alloc_data data;
	struct vha_dev *vha = session->vha;
	int ret;

	if (copy_from_user(&data, buf, sizeof(data)))
		return -EFAULT;

	if (default_mem_heap != IMG_MEM_MAN_HEAP_ID_INVALID)
		data.heap_id = default_mem_heap;

	if (list_empty(&session->bufs))
		img_pdump_printf("-- ALLOC_BEGIN\n");

	ret = img_mem_alloc(session->vha->dev,
				session->mem_ctx, data.heap_id,
				(size_t)data.size, data.attributes, &data.buf_id);
	if (ret)
		return ret;

	ret = mutex_lock_interruptible(&vha->lock);
	if (ret) {
		img_mem_free(session->mem_ctx, data.buf_id);
		return ret;
	}

	ret = vha_add_buf(session, data.buf_id, (size_t)data.size,
			data.name, data.attributes);
	if (ret)
		goto out_free;

	if (copy_to_user(buf, &data, sizeof(struct vha_alloc_data)))
		goto out_rm_buf;

	mutex_unlock(&vha->lock);

	return 0;

out_rm_buf:
	vha_rm_buf(session, data.buf_id);
out_free:
	img_mem_free(session->mem_ctx, data.buf_id);

	mutex_unlock(&vha->lock);

	return -EFAULT;
}

static long vha_ioctl_import(struct vha_session *session, void __user *buf)
{
	struct vha_import_data data;
	struct vha_dev *vha = session->vha;
	int ret;

	if (copy_from_user(&data, buf, sizeof(data)))
		return -EFAULT;

	ret = img_mem_import(session->vha->dev, session->mem_ctx, data.heap_id,
					(size_t)data.size, data.attributes, data.buf_hnd,
					&data.buf_id);
	if (ret)
		return ret;

	ret = mutex_lock_interruptible(&vha->lock);
	if (ret) {
		img_mem_free(session->mem_ctx, data.buf_id);
		return ret;
	}

	ret = vha_add_buf(session, data.buf_id, (size_t)data.size,
				data.name, data.attributes);
	if (ret)
		goto out_free;

	if (copy_to_user(buf, &data, sizeof(struct vha_import_data)))
		goto out_rm_buf;

	mutex_unlock(&vha->lock);

	return 0;

out_rm_buf:
	vha_rm_buf(session, data.buf_id);
out_free:
	img_mem_free(session->mem_ctx, data.buf_id);

	mutex_unlock(&vha->lock);

	return -EFAULT;
}

static long vha_ioctl_export(struct vha_session *session, void __user *buf)
{
	struct vha_export_data data;
	int ret;

	if (copy_from_user(&data, buf, sizeof(data)))
		return -EFAULT;

	ret = img_mem_export(session->vha->dev, session->mem_ctx, data.buf_id,
					(size_t)data.size, data.attributes, &data.buf_hnd);
	if (ret)
		return ret;

	if (copy_to_user(buf, &data, sizeof(struct vha_export_data)))
		return -EFAULT;

	return 0;
}

static long vha_ioctl_free(struct vha_session *session, void __user *buf)
{
	struct vha_free_data data;
	struct vha_dev *vha = session->vha;
	struct miscdevice *miscdev = &vha->miscdev;
	int ret;

	if (copy_from_user(&data, buf, sizeof(data))) {
		dev_err(miscdev->this_device,
			"%s: copy_from_user error\n", __func__);
		return -EFAULT;
	}
	ret = mutex_lock_interruptible(&vha->lock);
	if (ret)
		return ret;
	img_pdump_printf("-- FREE_BEGIN\n");
	vha_rm_buf(session, data.buf_id);

	img_mem_free(session->mem_ctx, data.buf_id);
	img_pdump_printf("-- FREE_END\n");
	mutex_unlock(&vha->lock);

	return 0;
}

static long vha_ioctl_map_to_onchip(struct vha_session *session, void __user *buf)
{
	struct vha_map_to_onchip_data data;
	struct vha_dev *vha = session->vha;
	struct miscdevice *miscdev = &vha->miscdev;
	int ret = 0;

	if (copy_from_user(&data, buf, sizeof(data))) {
		dev_err(miscdev->this_device,
			"%s: copy_from_user error\n", __func__);
		return -EFAULT;
	}

	ret = vha_map_to_onchip(session, data.buf_id, data.virt_addr, data.page_size,
		data.num_pages, data.page_idxs, &data.map_id);

	if (copy_to_user(buf, &data, sizeof(data))) {
		dev_err(miscdev->this_device, "%s: copy to user failed!\n",
			__func__);
		return -EFAULT;
	}

	return ret;
}

static long vha_ioctl_map(struct vha_session *session, void __user *buf)
{
	struct vha_map_data data;
	struct vha_dev *vha = session->vha;
	struct miscdevice *miscdev = &vha->miscdev;
	int ret = 0;

	if (copy_from_user(&data, buf, sizeof(data))) {
		dev_err(miscdev->this_device,
			"%s: copy_from_user error\n", __func__);
		return -EFAULT;
	}

	vha_session_pm_get(session);
	ret = vha_map_buffer(session, data.buf_id,
				data.virt_addr, data.flags);
	vha_session_pm_put(session);

	return ret;
}

static long vha_ioctl_unmap(struct vha_session *session, void __user *buf)
{
	struct vha_unmap_data data;
	struct vha_dev *vha = session->vha;
	struct miscdevice *miscdev = &vha->miscdev;
	int ret = 0;

	if (copy_from_user(&data, buf, sizeof(data))) {
		dev_err(miscdev->this_device,
			"%s: copy_from_user error\n", __func__);
		return -EFAULT;
	}

	vha_session_pm_get(session);
	ret = vha_unmap_buffer(session, data.buf_id);
	vha_session_pm_put(session);

	return ret;
}

static long vha_ioctl_buf_status(struct vha_session *session, void __user *buf)
{
	struct vha_buf_status_data data;
	struct vha_dev *vha = session->vha;
	struct miscdevice *miscdev = &vha->miscdev;
	int ret;

	if (copy_from_user(&data, buf, sizeof(data))) {
		dev_err(miscdev->this_device,
			"%s: copy_from_user error\n", __func__);
		return -EFAULT;
	}

	ret = mutex_lock_interruptible(&vha->lock);
	if (ret)
		return ret;

	ret = vha_set_buf_status(session, data.buf_id, data.status, data.in_sync_fd);
	mutex_unlock(&vha->lock);

	return ret;
}

static long vha_ioctl_sync(struct vha_session *session, void __user *buf)
{
	struct vha_sync_data data;
	struct vha_dev *vha = session->vha;
	struct miscdevice *miscdev = &vha->miscdev;
	int ret = -EINVAL;

	if (copy_from_user(&data, buf, sizeof(data))) {
		dev_err(miscdev->this_device, "%s: copy_from_user error\n", __func__);
		return -EFAULT;
	}

#ifdef KERNEL_DMA_FENCE_SUPPORT
	ret = mutex_lock_interruptible(&vha->lock);
	if (ret)
		return ret;

	switch (data.op) {
		case VHA_SYNC_OP_CREATE_OUT:
			if (data.create_data.buf_id_count > VHA_SYNC_MAX_BUF_IDS) {
				dev_err(miscdev->this_device, "%s: too many buf_ids provided\n",
								__func__);
				ret = -EINVAL;
			} else
				ret = vha_create_output_sync(session, data.create_data.buf_id_count,
																		data.create_data.buf_ids);
			break;
		case VHA_SYNC_OP_MERGE_IN:
			if (data.merge_data.in_sync_fd_count > VHA_SYNC_MAX_IN_SYNC_FDS) {
				dev_err(miscdev->this_device, "%s: too many in_sync_fds provided\n",
								__func__);
				ret = -EINVAL;
			} else
				ret = vha_merge_input_syncs(session, data.merge_data.in_sync_fd_count,
																		data.merge_data.in_sync_fds);
			break;
		case VHA_SYNC_OP_RELEASE:
			if (data.release_data.buf_id_count > VHA_SYNC_MAX_BUF_IDS) {
				dev_err(miscdev->this_device, "%s: too many buf_ids provided\n",
								__func__);
				ret = -EINVAL;
			} else
				ret = vha_release_syncs(session, data.release_data.buf_id_count,
																data.release_data.buf_ids);
			break;
		default:
			break;
	}
	mutex_unlock(&vha->lock);

	if (ret < 0)
		data.sync_fd = VHA_SYNC_NONE;
	else {
		data.sync_fd = ret;
		ret = 0;
	}
#else
	data.sync_fd = VHA_SYNC_NONE;
	ret = -ENOSYS;
	dev_warn(miscdev->this_device, "%s: dma_fences not supported!\n", __func__);
#endif

	if (copy_to_user(buf, &data, sizeof(data))) {
		dev_err(miscdev->this_device, "%s: copy to user failed!\n", __func__);
		return -EFAULT;
	}

	return ret;
}

static long vha_ioctl_cancel(struct vha_session *session, void __user *buf)
{
	struct vha_cancel_data data;
	struct vha_dev *vha = session->vha;
	struct miscdevice *miscdev = &vha->miscdev;

	if (copy_from_user(&data, buf, sizeof(data))) {
		dev_err(miscdev->this_device,
			"%s: copy_from_user error\n", __func__);
		return -EFAULT;
	}

	return vha_rm_cmds(session, data.cmd_id, data.cmd_id_mask);
}

static long vha_ioctl_clk_ctrl(struct vha_session *session, void __user *buf)
{
	struct vha_clk_ctrl_data data;
	struct vha_dev *vha = session->vha;
	struct miscdevice *miscdev = &vha->miscdev;
	int ret = 0;

	if (copy_from_user(&data, buf, sizeof(data))) {
		dev_err(miscdev->this_device,
			"%s: copy_from_user error\n", __func__);
		return -EFAULT;
	}

	dev_info(vha->dev, "new_pm:fg_enable is %d\n", data.fg_enable);
	if (data.fg_enable)
		vha_session_pm_get(session);
	else
		vha_session_pm_put(session);

	return ret;
}

static long vha_ioctl(struct file *file, unsigned int code, unsigned long value)
{
	struct vha_session *session = (struct vha_session *)file->private_data;
	struct vha_dev *vha = session->vha;
	struct miscdevice *miscdev = &vha->miscdev;

	dev_dbg(miscdev->this_device, "%s: code: 0x%x, value: 0x%lx\n",
		__func__, code, value);

#ifdef CONFIG_FAULT_INJECTION
	current->make_it_fail = vha->fault_inject;
#endif

	switch (code) {
	case VHA_IOC_CORE_PROPS:
		return vha_ioctl_get_core_props(session, (void __user *)value);
	case VHA_IOC_CNN_PROPS:
		dev_err(miscdev->this_device, "%s: not yet implemented\n",
			__func__);
		return -EINVAL;
	case VHA_IOC_QUERY_HEAPS:
		return vha_ioctl_query_heaps(session, (void __user *)value);
	case VHA_IOC_ALLOC:
		return vha_ioctl_alloc(session, (void __user *)value);
	case VHA_IOC_IMPORT:
		return vha_ioctl_import(session, (void __user *)value);
	case VHA_IOC_EXPORT:
		return vha_ioctl_export(session, (void __user *)value);
	case VHA_IOC_FREE:
		return vha_ioctl_free(session, (void __user *)value);
	case VHA_IOC_VHA_MAP_TO_ONCHIP:
		return vha_ioctl_map_to_onchip(session, (void __user *)value);
	case VHA_IOC_VHA_MAP:
		return vha_ioctl_map(session, (void __user *)value);
	case VHA_IOC_VHA_UNMAP:
		return vha_ioctl_unmap(session, (void __user *)value);
	case VHA_IOC_BUF_STATUS:
		return vha_ioctl_buf_status(session, (void __user *)value);
	case VHA_IOC_SYNC:
		return vha_ioctl_sync(session, (void __user *)value);
	case VHA_IOC_CANCEL:
		return vha_ioctl_cancel(session, (void __user *)value);
	case VHA_IOC_CLK_CTRL:
		return vha_ioctl_clk_ctrl(session, (void __user *)value);
	default:
		dev_err(miscdev->this_device, "%s: code %#x unknown\n",
			__func__, code);
		return -EINVAL;
	}
}

static int vha_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct vha_session *session = (struct vha_session *)file->private_data;
	struct vha_dev *vha = session->vha;
	struct miscdevice *miscdev = &vha->miscdev;
	int buf_id = vma->vm_pgoff;

	dev_dbg(miscdev->this_device,
		"%s: PID: %d start %#lx end %#lx\n",
		__func__, task_pid_nr(current),
		vma->vm_start, vma->vm_end);

	dev_dbg(miscdev->this_device, "%s: PID: %d buf_id %d\n",
		__func__, task_pid_nr(current), buf_id);
	return img_mem_map_um(session->mem_ctx, buf_id, vma);
}

static const struct file_operations vha_fops = {
	.owner          = THIS_MODULE,
	.read           = vha_read,
	.poll           = vha_poll,
	.write          = vha_write,
	.release        = vha_release,
	.open           = vha_open,
	.mmap           = vha_mmap,
	.unlocked_ioctl = vha_ioctl,
	.compat_ioctl   = vha_ioctl,
};

#define VHA_MAX_NODE_NAME 16

int vha_api_add_dev(struct device *dev, struct vha_dev *vha, unsigned int id)
{
	int ret;
	char *dev_name = NULL;

	if (!dev || !vha) {
		pr_err("%s: invalid params!\n", __func__);
		return -EINVAL;
	}
	dev_name = devm_kzalloc(dev, VHA_MAX_NODE_NAME, GFP_KERNEL);
	if (!dev_name)
		return -ENOMEM;

	snprintf(dev_name, VHA_MAX_NODE_NAME, "vha%d", id);

	dev_dbg(dev, "%s: trying to register misc dev %s...\n",
		__func__, dev_name);

	vha->miscdev.minor = MISC_DYNAMIC_MINOR;
	vha->miscdev.fops = &vha_fops;
	vha->miscdev.name = dev_name;
	vha->id = id;

	ret = misc_register(&vha->miscdev);
	if (ret) {
		dev_err(dev, "%s: failed to register VHA misc device\n",
			__func__);
		goto out_register;
	}

	dev_dbg(dev, "%s: misc dev registered successfully\n", __func__);

	return 0;

out_register:
	devm_kfree(dev, dev_name);

	return ret;
}

int vha_api_rm_dev(struct device *dev, struct vha_dev *vha)
{
	int ret = 0;

	if (!dev || !vha) {
		pr_err("%s: invalid params!\n", __func__);
		return -EINVAL;
	}

	dev_dbg(dev, "%s: trying to deregister VHA misc device\n", __func__);

	/* note: since linux v4.3, misc_deregister does not return errors */
	misc_deregister(&vha->miscdev);

	devm_kfree(dev, (void *)vha->miscdev.name);

	dev_dbg(dev, "%s: VHA misc dev deregistered: %d\n", __func__, ret);

	return ret;
}

static int __init vha_api_init(void)
{
	int ret;

	pr_debug("loading VHA module.\n");

	vha_early_init();

	ret = vha_plat_init();
	if (ret)
		pr_err("failed initialize VHA driver\n");

	return ret;
}

static void __exit vha_api_exit(void)
{
	int ret;

	pr_debug("unloading VHA module.\n");

	ret = vha_plat_deinit();
	if (ret)
		pr_err("failed to deinitialise VHA driver\n");
}

module_init(vha_api_init);
module_exit(vha_api_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Imagination");
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
MODULE_IMPORT_NS(IMG_MEM);
#endif
