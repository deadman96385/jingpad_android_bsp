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
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/gfp.h>
#include <linux/moduleparam.h>
#include <linux/list.h>
#include <linux/debugfs.h>
#include <linux/uaccess.h>

#include <uapi/vha.h>
#include "vha_common.h"
#include "vha_plat.h"
#include "vha_regs.h"

static uint32_t cnn_crc_size_kB;
static uint32_t cnn_dbg_size_kB;
static bool cnn_dbg_pdump_enable = true;
module_param(cnn_crc_size_kB, uint, 0444);
module_param(cnn_dbg_size_kB, uint, 0444);
module_param(cnn_dbg_pdump_enable, bool, 0444);
MODULE_PARM_DESC(cnn_crc_size_kB, "size of hw CRC buffer");
MODULE_PARM_DESC(cnn_dbg_size_kB, "size of hw DEBUG buffer");
MODULE_PARM_DESC(cnn_dbg_pdump_enable,
	"DEBUG buffer is captured into pdump file");
static uint32_t cnn_crc_mode;
static uint32_t cnn_dbg_modes[2];
module_param(cnn_crc_mode, uint, 0444);
module_param_array(cnn_dbg_modes, uint, NULL, 0444);
MODULE_PARM_DESC(cnn_crc_mode,
	"CRC CONTROL: mode for CNN_CRC_ENABLE: 0=disable 1=stream 2=layer 3=pass");
MODULE_PARM_DESC(cnn_dbg_modes,
	"DEBUG CONTROL: modes for PERF and BAND_ENABLE: 0=disable 1=stream 2=layer 3=pass");

#ifdef HW_AX3
static uint32_t cnn_crc_mask = 0;
module_param(cnn_crc_mask, uint, 0444);
MODULE_PARM_DESC(cnn_crc_mask,
	"CRC MASK: 0=no mask 1=debug silicon 2-safety critical 3-reserved");
#endif

static uint32_t cnn_pdump_flush_dbg = 1;
module_param(cnn_pdump_flush_dbg, uint, 0444);
MODULE_PARM_DESC(cnn_pdump_flush_dbg,
	"PDUMP: flushing debug buffs: 0:session,1:stream(default)");

struct vha_reg {
	char *name;
	unsigned offset;
	uint64_t mask;
};

struct vha_regset {
	const struct vha_reg *regs;
	int nregs;
	void __iomem *base;
};

struct vha_dbgfs_ctx {
	struct dentry    *debugfs_dir;
	struct vha_regset regset;
	uint64_t          rtm_ctrl;
	uint64_t          ioreg_addr;
};


/* MMU PTE dump info */
struct vha_ptedump {
	struct vha_session *session;

	/* Actual address */
	uint64_t vaddr;
	/* Selected mmu sw context to be dumped */
	unsigned cur_cid;

	/* Configuration info */
	size_t page_size;
	size_t virt_size;
};

static void *vha_mmu_ptedump_start(struct seq_file *seq, loff_t *pos)
{
	struct vha_ptedump *ctx = seq->private;
	struct vha_session *session;

	if (!ctx)
		return NULL;

	session = ctx->session;
	if (!session)
		return NULL;

	/* Get mmu configuration info - the same one the tables were built with */
	img_mmu_get_conf(&ctx->page_size, &ctx->virt_size);
	ctx->vaddr = *pos * ctx->page_size;

	if (*pos == 0) {
		uint64_t pc_addr = img_mem_get_single_page(session->mem_ctx,
				session->mmu_ctxs[ctx->cur_cid-1].pc_bufid, 0);

		seq_printf(seq, "  Session hw_ctxid:%x -> PC addr:%#llx\n",
				session->mmu_ctxs[ctx->cur_cid-1].hw_id, pc_addr);
		seq_printf(seq, "    [ virtaddr ] [ physaddr ] [flags]\n");
	}

	return ctx;
}

static void *vha_mmu_ptedump_next(struct seq_file *seq, void *priv, loff_t *pos)
{
	struct vha_ptedump *ctx = priv;
	struct vha_session *session;

	if (!ctx)
		return NULL;

	session = ctx->session;

	(*pos)++;
	ctx->vaddr = *pos * ctx->page_size;
	if (ctx->vaddr <= (1ULL<<ctx->virt_size)-ctx->page_size)
		return ctx;

	if (ctx->cur_cid < ARRAY_SIZE(session->mmu_ctxs)) {
		/* Switch to next context & reset position */
		ctx->cur_cid++;
		*pos = 0;
		vha_mmu_ptedump_start(seq, pos);

		return ctx;
	}

	return NULL;
}

static int vha_mmu_ptedump_show(struct seq_file *seq, void *priv)
{
	struct vha_ptedump *ctx = priv;
	struct vha_session *session;
	phys_addr_t paddr;
	uint8_t flags;
	int ret = 0;

	if (!ctx)
		return -EINVAL;

	session = ctx->session;
	if (!session)
		return -EINVAL;

	if (ctx->vaddr > (1ULL<<ctx->virt_size)-ctx->page_size)
		return SEQ_SKIP;

	paddr = img_mmu_get_paddr(session->mmu_ctxs[ctx->cur_cid-1].ctx,
				ctx->vaddr, &flags);
	if (flags) {
		struct vha_buffer *buf = vha_find_bufvaddr(session, ctx->vaddr);
		seq_printf(seq, "    0x%010llx 0x%010llx 0x%04x (%s)\n",
					ctx->vaddr, paddr, flags, buf ? buf->name : "???");
	} else if (!(ctx->vaddr % 0x40000000)) {
		/*  Give some time to others, to avoid soft lockup warnings
		 *  Call yield() for every GB boundary of virtual address space */
		yield();
	}

	return ret;
}

static void vha_mmu_ptedump_stop(struct seq_file *seq, void *priv)
{
	/* Nothing to do */
}

static const struct seq_operations vha_mmu_ptedump_sops = {
	.start = vha_mmu_ptedump_start,
	.next  = vha_mmu_ptedump_next,
	.show  = vha_mmu_ptedump_show,
	.stop  = vha_mmu_ptedump_stop
};

static int vha_mmu_ptedump_open(struct inode *inode, struct file *file)
{
	int ret;

	ret = seq_open(file, &vha_mmu_ptedump_sops);
	if (!ret) {
		struct vha_session *session;
		struct seq_file *seq;
		struct vha_ptedump *ctx;

		seq = file->private_data;

		session = inode->i_private;
		if (!session)
			return -EINVAL;

		ctx = kzalloc(sizeof(struct vha_ptedump), GFP_KERNEL);
		if (!ctx)
			return -ENOMEM;

		ctx->session = session;
		seq->private = ctx;
		ctx->cur_cid = 1;

		ret = mutex_lock_interruptible(&session->vha->lock);
	}

	return ret;
}

static int vha_mmu_ptedump_release(struct inode *inode, struct file *file)
{
	struct seq_file *seq = file->private_data;
	struct vha_session *session;
	struct vha_ptedump *ctx;

	if (!seq)
		return -EINVAL;

	ctx = seq->private;
	session = ctx->session;
	if (session)
		mutex_unlock(&session->vha->lock);

	kfree(ctx);

	return seq_release(inode, file);
}

static const struct file_operations vha_mmu_ptedump_fops = {
	.owner = THIS_MODULE,
	.open = vha_mmu_ptedump_open,
	.llseek  = seq_lseek,
	.release = vha_mmu_ptedump_release,
	.read    = seq_read,
};

static void *vha_buffer_dump_start(struct seq_file *seq, loff_t *pos)
{
    struct vha_session *session = seq->private;
    int ret;

    if (session == NULL) {
        pr_warn("Invalid VHA session pointer...\n");
        return  NULL;
    }

    if (list_empty(&session->bufs))
        return NULL;


    ret = mutex_lock_interruptible(&session->vha->lock);

    if (ret) {
        pr_warn("Error while trying to get vha lock (%d)...\n", ret);
        return  NULL;
    }


    seq_printf(seq, "Allocated buffers:\n");
    seq_printf(seq, "ID    Name       Size       Atributes  Status     Kptr              DevVirt     Inval?  Flush?\n");
    /*               6005  012345678  123456789  CUWSNM     SW filled            (null)  0x40002001  n       Y\n" */

    /* Then first buffer from it */
    return seq_list_start(&session->bufs, *pos);
}

static void *vha_buffer_dump_next(struct seq_file *seq, void *priv, loff_t *pos)
{
    struct vha_session *session = seq->private;
    return seq_list_next(priv, &session->bufs, pos);
}

static void vha_buffer_dump_stop(struct seq_file *seq, void *priv)
{
    struct vha_session *session = seq->private;
    mutex_unlock(&session->vha->lock);

    seq_printf(seq, "Attributes: Cached;Uncached;Writecombine;Secure;Nomap;Mmu\n");
}

static const char *BufferStatus[] = {
        "Unfilled ",
        "SW filled",
        "HW filled"
};


static int vha_buffer_dump_show(struct seq_file *seq, void *priv)
{
    const struct vha_buffer *buf = list_entry(priv, struct vha_buffer, list);

    /* ID    Name       Size       Atributes  Status     Kptr              DevVirt     Inval?  Flush? */
    seq_printf(seq, "%04u  %9s  %9ld  %c%c%c%c%c%c     %s  %p  0x%08llX  %c       %c\n",
               buf->id,
               buf->name,
               buf->size,
               (buf->attr & IMG_MEM_ATTR_CACHED)?'C':'.',
               (buf->attr & IMG_MEM_ATTR_UNCACHED)?'U':'.',
               (buf->attr & IMG_MEM_ATTR_WRITECOMBINE)?'W':'.',
               (buf->attr & IMG_MEM_ATTR_SECURE)?'S':'.',
               (buf->attr & IMG_MEM_ATTR_NOMAP)?'N':'.',
               (buf->attr & IMG_MEM_ATTR_MMU)?'M':'.',
               BufferStatus[buf->status],
               buf->kptr,
               buf->devvirt,
               (buf->inval)?'Y':'n',
               (buf->flush)?'Y':'n'
              );
    return 0;
}

static const struct seq_operations vha_buffer_dump_sops = {
        .start = vha_buffer_dump_start,
        .next  = vha_buffer_dump_next,
        .show  = vha_buffer_dump_show,
        .stop  = vha_buffer_dump_stop
};

static int vha_buffer_dump_open(struct inode *inode, struct file *file)
{
    struct seq_file *s;
    int err;

    err = seq_open(file, &vha_buffer_dump_sops);
    if (err)
        return err;

    s = file->private_data;

    /* i_private containt a pointer to the vha_session structure */
    s->private = inode->i_private;

    return 0;
}

static const struct file_operations vha_buffer_dump_fops = {
        .owner = THIS_MODULE,
        .open = vha_buffer_dump_open,
        .read    = seq_read,
        .llseek  = seq_lseek,
        .release = seq_release,
};

static ssize_t vha_session_mem_max_read(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	struct vha_session *session = file->private_data;
	char mem_usage[25] = { 0 };

	size_t size = snprintf(mem_usage, sizeof(mem_usage), "%ld\n",
			img_mem_get_usage_max(session->mem_ctx));

	return simple_read_from_buffer(buf, count, ppos, mem_usage, size);
}

static const struct file_operations vha_session_mem_max_fops = {
	.owner = THIS_MODULE,
	.open = simple_open,
	.read = vha_session_mem_max_read,
};

static ssize_t vha_session_mem_max_curr(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	struct vha_session *session = file->private_data;
	char mem_usage[25] = { 0 };

	size_t size = snprintf(mem_usage, sizeof(mem_usage), "%ld\n",
			img_mem_get_usage_current(session->mem_ctx));

	return simple_read_from_buffer(buf, count, ppos, mem_usage, size);
}

static const struct file_operations vha_session_mem_curr_fops = {
	.owner = THIS_MODULE,
	.open = simple_open,
	.read = vha_session_mem_max_curr,
};

struct dbgfs_buf_info {
	struct vha_session *session;
	struct vha_buffer  *buf;
	struct dentry      *dbgfs;	/* file in debugfs */

};

/* debugfs read a buffer */
static ssize_t dbgfs_buf_read(struct file *file, char __user *user_buf,
			      size_t count, loff_t *ppos)
{
	struct dbgfs_buf_info *info = file->private_data;
	struct vha_buffer *buf = info->buf;
	struct vha_session *session = info->session;
	int ret;

	ret = mutex_lock_interruptible(&session->vha->lock);
	if (!ret) {
		if (buf->attr & IMG_MEM_ATTR_NOMAP) {
			ret = -ENOMEM;
			dev_err(session->vha->dev, "can't read non mappable buff %x\n (%d)",
				buf->id, ret);
			goto exit;
		}

		ret = img_mem_map_km(session->mem_ctx, buf->id);
		if (ret) {
			dev_err(session->vha->dev, "failed to map buff %x to km: %d\n",
				buf->id, ret);
			ret = -ENOMEM;
			goto exit;
		}
		buf->kptr = img_mem_get_kptr(session->mem_ctx, buf->id);

		ret = simple_read_from_buffer(user_buf, count, ppos,
				       buf->kptr, buf->size);
		if (ret < 0)
			dev_err(session->vha->dev, "failed to read buff %x to km: %d\n",
				buf->id, ret);

		if (img_mem_unmap_km(session->mem_ctx, buf->id))
			dev_err(session->vha->dev,
				"%s: failed to unmap buff %x from km: %d\n",
				__func__, buf->id, ret);
exit:
		buf->kptr = NULL;
		mutex_unlock(&session->vha->lock);
	}

	return ret;
}

static const struct file_operations dbgfs_buf_fops = {
	.read = dbgfs_buf_read,
	.open = simple_open,
	.llseek = default_llseek,
};

static void dbg_add_buf(struct vha_session *session, struct vha_buffer *buf)
{
	if (buf->name[0] && session->dbgfs) {
		char name[13] = { 0 };

		struct dbgfs_buf_info *info = kzalloc(sizeof(struct dbgfs_buf_info),
				GFP_KERNEL);

		if (!info) {
			dev_err(session->vha->dev, "%s: alloc info failed!\n", __func__);
			return;
		}

		snprintf(name, sizeof(name)-1, "%s.bin", buf->name);
		info->buf = buf;
		info->session = session;
		info->dbgfs = debugfs_create_file(name,
						 S_IRUGO, session->dbgfs,
						 info, &dbgfs_buf_fops);
		if (!info->dbgfs)
			dev_warn(session->vha->dev,
					 "%s: failed to debugfs entry for '%s'!\n",
					 __func__, name);
		buf->dbgfs_priv = (void*)info;
	}
}

static void dbg_rm_buf(struct vha_session *session, uint32_t buf_id)
{
	struct vha_buffer *buf = vha_find_bufid(session, buf_id);
	struct dbgfs_buf_info *info;

	info = (struct dbgfs_buf_info *)buf->dbgfs_priv;
	if (info) {
		/* remove debugfs directory. NULL is safe */
		debugfs_remove(info->dbgfs);
		kfree(info);
	}
	buf->dbgfs_priv = NULL;
}

/*
 * create buffers for CRC and DEBUG (PERF and BAND).
 * Configure the hardware to use them.
 * Buffers are mapped into device mmu on demand(when map=true)
 */
int vha_dbg_alloc_hwbuf(struct vha_session *session, size_t size,
			    struct vha_buffer **buffer,
			    const char *name, bool map)
{
	struct vha_dev *vha = session->vha;
	struct vha_buffer *buf;
	int buf_id, ret;
	uint32_t vaddr = 0;

	if (list_empty(&session->bufs))
		img_pdump_printf("-- ALLOC_BEGIN\n");

	ret = img_mem_alloc(vha->dev,
			session->mem_ctx,
			vha->int_heap_id,
			size,
			IMG_MEM_ATTR_WRITECOMBINE,
			&buf_id);
	if (ret)
		return ret;

	ret = vha_add_buf(session, buf_id, size,
			name, IMG_MEM_ATTR_WRITECOMBINE);
	if (ret) {
		dev_err(vha->dev, "%s: add failed!\n", __func__);
		goto out_add_failed;
	}

	buf = vha_find_bufid(session, buf_id);
	if (buf == NULL)
		goto out_no_buf;

	if (vha->mmu_mode) {
		ret = img_mmu_vaa_alloc(session->vaa_ctx,
				buf->size, &vaddr);
		if (ret) {
			dev_err(vha->dev, "%s: vaa alloc failed!\n", __func__);
			goto out_vaa_failed;
		}

		if (map) {
			ret = img_mmu_map(
					session->mmu_ctxs[VHA_MMU_REQ_IO_CTXID].ctx,
					session->mem_ctx, buf_id,
					vaddr, 0);
			if (ret) {
				dev_err(vha->dev,
						"%s: map failed!\n",
						__func__);
				goto out_map_failed;
			}

			buf->devvirt = vaddr;
			dev_dbg(vha->dev,
					"%s: mapped buf %s (%u) to %#llx:%zu\n",
				__func__,
				buf->name, buf_id,
				buf->devvirt, buf->size);
		}
	}

	*buffer = buf;

	return 0;

out_map_failed:
	img_mmu_vaa_free(session->vaa_ctx, buf->devvirt, buf->size);
out_vaa_failed:
out_no_buf:
	vha_rm_buf(session, buf->id);
out_add_failed:
	img_mem_free(session->mem_ctx, buf_id);
	return -EFAULT;
}

/* enable CNN_CRC and CNN_DEBUG capture into buffers */
int vha_dbg_enable_hwbufs(struct vha_session *session)
{
	struct vha_dev *vha = session->vha;
	struct vha_dbgfs_ctx *ctx =
			(struct vha_dbgfs_ctx *)vha->dbgfs_ctx;
	int ret;

	session->cnn_dbg.cnn_dbg_flush = cnn_pdump_flush_dbg;

	if (vha->mmu_mode &&
		((cnn_crc_mode > 0 && cnn_crc_size_kB > 0) ||
		 (cnn_dbg_size_kB > 0))) {
		ret = img_mmu_vaa_create(vha->dev,
				IMG_MEM_VA_HEAP1_BASE, IMG_MEM_VA_HEAP1_SIZE,
				&session->vaa_ctx);
		if (ret) {
			dev_err(vha->dev, "%s: failed to allocate vaa heap\n",
				__func__);
			return ret;
		}
	}

	/* Create debugfs dir and populate entries */
	if (ctx->debugfs_dir) {
		char name[15] = { 0 };

		snprintf(name, sizeof(name)-1, "%s%d",
				"session",
				session->mmu_ctxs[VHA_MMU_REQ_MODEL_CTXID].id);

		session->dbgfs =
			debugfs_create_dir(name, ctx->debugfs_dir);

		if (session->dbgfs) {
			if (!debugfs_create_file("pte_dump", S_IRUGO, session->dbgfs,
						session, &vha_mmu_ptedump_fops))
				dev_warn(vha->dev,
					"%s: failed to create pte_dump!\n",
					__func__);
			if (!debugfs_create_file("mem_usage_max", S_IRUGO, session->dbgfs,
						session, &vha_session_mem_max_fops))
				dev_warn(vha->dev,
					"%s: failed to create mem_usage_max!\n",
					__func__);
			if (!debugfs_create_file("mem_usage_curr", S_IRUGO, session->dbgfs,
						session, &vha_session_mem_curr_fops))
				dev_warn(vha->dev,
					"%s: failed to create mem_usage_curr!\n",
					__func__);

            if (!debugfs_create_file("buffer_dump", S_IRUGO, session->dbgfs,
                                     session, &vha_buffer_dump_fops))
                dev_warn(vha->dev,
                         "%s: failed to create buffer_dump!\n",
                         __func__);

		}
	}

	if (cnn_crc_mode > 0 && cnn_crc_size_kB > 0) {
		struct vha_buffer *buf;
		size_t size = cnn_crc_size_kB * 1024;

		ret = vha_dbg_alloc_hwbuf(session, size, &buf, "CRC", true);
		if (ret) {
			dev_err(vha->dev, "%s: failed to allocate buffer for CNN_CRC\n",
				__func__);
			goto out_disable;
		}
		session->cnn_dbg.cnn_crc_buf = buf;
		dbg_add_buf(session, buf);
	}

	if (cnn_dbg_size_kB > 0) {
		struct vha_buffer *buf;
		size_t size = cnn_dbg_size_kB * 1024;
		size_t max = VHA_CR_ALIGN_MAX_OS(CNN_DEBUG_SIZE, CNN_DEBUG_SIZE);

		if (size > max) {
			dev_warn(vha->dev, "warning: max cnn_dbg_size: %zx\n",
				 max);
			size = max;
		}
		ret = vha_dbg_alloc_hwbuf(session, size, &buf, "DBG", true);
		if (ret) {
			dev_err(vha->dev,
				"%s: failed to allocate buffer for CNN_DEBUG\n",
				__func__);
			goto out_disable;
		}
		session->cnn_dbg.cnn_dbg_buf = buf;
		dbg_add_buf(session, buf);
	}

	return 0;

out_disable:
	vha_dbg_disable_hwbufs(session);
	return ret;
}

/* prepare CRC and DEBUG data buffers */
void vha_dbg_prepare_hwbufs(struct vha_session *session)
{
	struct vha_dev *vha = session->vha;

	if (session->cnn_dbg.cnn_crc_buf) {
		struct vha_buffer *buf = session->cnn_dbg.cnn_crc_buf;
		uint64_t val64;

		/* enable CRC: address + mode */
		val64 = VHA_CR_SETBITS_OS(CNN_CRC_CONTROL, CNN_CRC_ENABLE,
				       cnn_crc_mode);
		img_pdump_printf("-- CRC_CONTROL=%u buf '%s' size=%zx\n",
				 cnn_crc_mode, buf->name, buf->size);
		IOWRITE_PDUMP_BUFADDR(session, buf, 0, VHA_CR_OS(CNN_CRC_ADDRESS));

		IOWRITE64_PDUMP(val64, VHA_CR_OS(CNN_CRC_CONTROL));

#ifdef HW_AX3
		img_pdump_printf("-- CRC_MASK=%#x\n", cnn_crc_mask);
		IOWRITE64_PDUMP(cnn_crc_mask, VHA_CR_OS(CNN_CRC_MASK_CTRL));
#endif
	}
	if (session->cnn_dbg.cnn_dbg_buf && cnn_dbg_pdump_enable) {
		struct vha_buffer *buf = session->cnn_dbg.cnn_dbg_buf;
		uint64_t val64;

		/* enable DEBUG: address, perf mode, band mode */
		img_pdump_printf("-- DEBUG_CONTROL=%u,%u buf '%s' size=%zx\n",
				 cnn_dbg_modes[0], cnn_dbg_modes[1],
				 buf->name, buf->size);
		IOWRITE_PDUMP_BUFADDR(session, buf, 0,
				      VHA_CR_OS(CNN_DEBUG_ADDRESS));
		val64 = VHA_CR_ALIGN_SETBITS_OS(CNN_DEBUG_SIZE,
					      CNN_DEBUG_SIZE,
					      buf->size);
		IOWRITE64_PDUMP(val64, VHA_CR_OS(CNN_DEBUG_SIZE));

		/* Set the CONTROL register only if requested */
		if (cnn_dbg_modes[0] > 0 || cnn_dbg_modes[1] > 0) {
			val64 = VHA_CR_SETBITS_OS(CNN_DEBUG_CONTROL,
				       CNN_PERF_ENABLE,
				       cnn_dbg_modes[0]);
			val64 |= VHA_CR_SETBITS_OS(CNN_DEBUG_CONTROL,
				       CNN_BAND_ENABLE,
				       cnn_dbg_modes[1]);
			IOWRITE64_PDUMP(val64, VHA_CR_OS(CNN_DEBUG_CONTROL));
		}
	}
}

/* flush CRC and DEBUG data buffers */
void vha_dbg_flush_hwbufs(struct vha_session *session, char checkpoint)
{
	if (session->cnn_dbg.cnn_dbg_flush != checkpoint)
		return;

	if (session->cnn_dbg.cnn_crc_buf) {
		struct vha_buffer *buf = session->cnn_dbg.cnn_crc_buf;
		/*
		 * TOBEDONE: calculate CRC buffer size based
		 * on num passes, num layers, etc
		 */
		img_pdump_printf("-- Save signatures\n");
		img_pdump_printf("IF CHECK_CRCS\n");
		img_pdump_printf("COM Checking CRCs ...\n");
		vha_pdump_sab_buf(session, PDUMP_CRC,
				  buf, 0, buf->size);
		img_pdump_printf("ELSE CHECK_CRCS\n");
		img_pdump_printf("COM Not checking CRCs!\n");
		img_pdump_printf("FI CHECK_CRCS\n");
	}
	if (session->cnn_dbg.cnn_dbg_buf && cnn_dbg_pdump_enable) {
		struct vha_buffer *buf = session->cnn_dbg.cnn_dbg_buf;
		struct vha_dev *vha = session->vha;
		/* read the size of the DEBUG buffer */
		uint64_t size = IOREAD64(vha->reg_base, VHA_CR_OS(CNN_DEBUG_STATUS));
		/*
		 * SAB the DBG buffer, even though "it is not deterministic"
		 */
		size = VHA_CR_GETBITS_OS(CNN_DEBUG_STATUS,
					    CNN_DEBUG_OFFSET,
					    size);
		img_pdump_printf("-- Save DEBUG info\n");
		vha_pdump_sab_buf(session, PDUMP_DBG, buf, 0, buf->size);
	}
}

void vha_dbg_hwbuf_cleanup(struct vha_session *session,
		struct vha_buffer *buf)
{
	struct vha_dev *vha = session->vha;

	if (vha->mmu_mode) {
		img_mmu_vaa_free(session->vaa_ctx, buf->devvirt, buf->size);
		img_mmu_unmap(session->mmu_ctxs[VHA_MMU_REQ_IO_CTXID].ctx,
				session->mem_ctx, buf->id);
	}
	dbg_rm_buf(session, buf->id);
	vha_rm_buf(session, buf->id);
	img_mem_free(session->mem_ctx, buf->id);
}

/* stop capturing CRC and DEBUG data and free the buffers */
void vha_dbg_disable_hwbufs(struct vha_session *session)
{
	struct vha_dev *vha = session->vha;

	/* Flush hw debug buffers */
	vha_dbg_flush_hwbufs(session, 0);

	if (session->cnn_dbg.cnn_crc_buf) {
		struct vha_buffer *buf = session->cnn_dbg.cnn_crc_buf;

		IOWRITE64_PDUMP(0, VHA_CR_OS(CNN_CRC_CONTROL));
		vha_dbg_hwbuf_cleanup(session, buf);
	}
	if (session->cnn_dbg.cnn_dbg_buf) {
		struct vha_buffer *buf = session->cnn_dbg.cnn_dbg_buf;
		/* read the size of the DEBUG buffer */
		uint64_t size = IOREAD64(vha->reg_base, VHA_CR_OS(CNN_DEBUG_STATUS));

		if (cnn_dbg_modes[0] > 0 || cnn_dbg_modes[1] > 0) {
			IOWRITE64_PDUMP(0, VHA_CR_OS(CNN_DEBUG_CONTROL));
			/* just give a hint in the pdump:
			 * dummy device returns 0 */
			img_pdump_printf(
					"-- POL64 :REG:%#x 0 0 0 1 1 -- DEBUG_STATUS=%llx\n",
					 VHA_CR_OS(CNN_DEBUG_STATUS),
				size);
		}
		vha_dbg_hwbuf_cleanup(session, buf);
	}

	if (vha->mmu_mode && session->vaa_ctx)
		img_mmu_vaa_destroy(session->vaa_ctx);

	/* remove debugfs directory. NULL is safe */
	debugfs_remove_recursive(session->dbgfs);
}

static int _show_vha_regset(struct seq_file *s, void *data)
{
	struct vha_regset *regset = s->private;
	const struct vha_reg *reg = regset->regs;
	char str[150];
	int i;

	for (i = 0; i < regset->nregs; i++, reg++) {
		uint64_t val = IOREAD64(regset->base, reg->offset);
		sprintf(str, "%s(0x%04x) = 0x%016llx",
				reg->name, reg->offset, val);
		if (val & ~reg->mask)
			strcat(str, " Bogus register value detected !!!");
		strcat(str, "\n");
		seq_puts(s, str);
	}
	return 0;
}

static int _open_vha_regset(struct inode *inode, struct file *file)
{
	return single_open(file, _show_vha_regset, inode->i_private);
}

static const struct file_operations vha_regset_fops = {
	.open = _open_vha_regset,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

/* List of predefined registers to be shown in debugfs */
static const struct vha_reg vha_regs[] = {
#define REG_DESC(reg) VHA_CR_##reg, VHA_CR_##reg##_MASKFULL
#define REG_DESC_OS(reg) VHA_CR_OS(reg), VHA_CR_OS(reg##_MASKFULL)
	{"main_clocks_control  ", REG_DESC(CLK_CTRL0)},
	{"main_clocks_status   ", REG_DESC(CLK_STATUS0)},
	{"sys_clocks_control   ", REG_DESC(SYS_CLK_CTRL0)},
	{"sys_clocks_status    ", REG_DESC(SYS_CLK_STATUS0)},
	{"product_id           ", REG_DESC(PRODUCT_ID)},
	{"core_id              ", REG_DESC(CORE_ID)},
	{"soc_axi              ", REG_DESC(SOC_AXI)},
	{"integrator_id        ", REG_DESC(CORE_IP_INTEGRATOR_ID)},
	{"ip_changelist        ", REG_DESC(CORE_IP_CHANGELIST)},
	{"reset                ", REG_DESC(RESET_CTRL)},
	{"event_enable         ", REG_DESC_OS(VHA_EVENT_ENABLE)},
	{"event_status         ", REG_DESC_OS(VHA_EVENT_STATUS)},
	{"cnn_control          ", REG_DESC_OS(CNN_CONTROL)},
	{"cnn_status           ", REG_DESC_OS(CNN_STATUS)},
#ifdef HW_AX2
	{"cnn_wdt_cmpmatch     ", REG_DESC(CNN_WDT_COMPAREMATCH)},
	{"cnn_wdt_control      ", REG_DESC(CNN_WDT_CTRL)},
	{"cnn_wdt_timer        ", REG_DESC(CNN_WDT_TIMER)},
#endif
	{"cnn_mem_wdt_cmpmatch ", REG_DESC(CNN_MEM_WDT_COMPAREMATCH)},
	{"cnn_mem_wdt_control  ", REG_DESC(CNN_MEM_WDT_CTRL)},
	{"cnn_mem_wdt_timer    ", REG_DESC(CNN_MEM_WDT_TIMER)},
	{"mmu_control          ", REG_DESC_OS(MMU_CTRL)},
	{"mmu_context          ", REG_DESC_OS(MMU_CBASE_MAPPING_CONTEXT)},
	{"mmu_mapping          ", REG_DESC_OS(MMU_CBASE_MAPPING)},
	{"mmu_status           ", REG_DESC(MMU_STATUS)},
	{"mmu_fault_status1    ", REG_DESC_OS(MMU_FAULT_STATUS1)},
	{"mmu_fault_status2    ", REG_DESC_OS(MMU_FAULT_STATUS2)},
	{"slc_control          ", REG_DESC(SLC_CTRL)},
#if 0
	{"slc_bypass_control   ", REG_DESC(SLC_BYPASS_CTRL)},
#endif
	{"slc_status1          ", REG_DESC(SLC_STATUS1)},
	{"slc_status2          ", REG_DESC(SLC_STATUS2)},
	{"slc_status3          ", REG_DESC(SLC_STATUS3)},
	{"slc_idle             ", REG_DESC(SLC_IDLE)},
	{"bif_outstanding_read ", REG_DESC(BIF_OUTSTANDING_READ)},
#undef REG_DESC
};

static ssize_t vha_cnn_utilization_read(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	struct vha_dev *vha = file->private_data;
	char utilization[20] = { 0 };
	size_t bytes = 0;

	if (count < strlen(utilization))
		return -EINVAL;

	if (*ppos)
		return 0;

	snprintf(utilization, (int)sizeof(utilization)-1, "%d.%d[%%]\n",
			vha->stats.cnn_utilization / 10,
			vha->stats.cnn_utilization % 10);

	if (copy_to_user(buf, utilization,
			strlen(utilization))) {
		dev_err(vha->dev, "%s: cnn_utilization read: copy to user failed\n",
				__func__);
		return -EFAULT;
	}

	bytes = strlen(utilization);
	*ppos = bytes;

	return bytes;
}

static const struct file_operations vha_cnn_utilization_fops = {
	.owner = THIS_MODULE,
	.open = simple_open,
	.read = vha_cnn_utilization_read,
};

static ssize_t vha_cnn_last_cycles_read(struct file *file, char __user *buf, size_t len,
			     loff_t *ppos)
{
	struct vha_dev *vha = file->private_data;
	char cycles[16];
	size_t size;

#if defined(HW_AX2)
	/* For Mirage cnn_last_cycles holds a valid value only
	 * when we set WDT per segment */
	if ((vha->wdt_mode & VHA_CR_CNN_WDT_CTRL_CNN_WDT_CTRL_MASK) ==
				VHA_CR_CNN_WDT_CTRL_CNN_WDT_CTRL_KICK_PASS)
		size = snprintf(cycles, sizeof(cycles), "n/a\n");
	else
#elif defined(HW_AX3)
	/* For Aura cnn_last_cycles holds a valid value only
	 * when debug mode is turned on to collect performance data per segment */
	if (cnn_dbg_modes[0] != VHA_CR_CNN_DEBUG_CTRL_STREAM)
		size = snprintf(cycles, sizeof(cycles), "n/a\n");
	else
#endif
		size = snprintf(cycles, sizeof(cycles), "%lld\n",
				vha->stats.cnn_last_cycles);

	return simple_read_from_buffer(buf, len, ppos, cycles, size);
}

static const struct file_operations vha_cnn_last_cycles_fops = {
	.owner = THIS_MODULE,
	.open = simple_open,
	.read = vha_cnn_last_cycles_read,
};

static ssize_t vha_bvnc_read(struct file *file, char __user *buf, size_t len,
			     loff_t *ppos)
{
	struct vha_dev *vha = file->private_data;
	char bvnc[4*6];
	uint64_t core_id = IOREAD64(vha->reg_base, VHA_CR_CORE_ID);
	size_t size = snprintf(bvnc, sizeof(bvnc), "%hu.%hu.%hu.%hu\n",
		      (unsigned short)((core_id & 0xffff000000000000ULL) >> 48),
		      (unsigned short)((core_id & 0x0000ffff00000000ULL) >> 32),
		      (unsigned short)((core_id & 0x00000000ffff0000ULL) >> 16),
		      (unsigned short)((core_id & 0x000000000000ffffULL) >> 0));

	return simple_read_from_buffer(buf, len, ppos, bvnc, size);
}

static const struct file_operations vha_bvnc_fops = {
	.owner = THIS_MODULE,
	.open = simple_open,
	.read = vha_bvnc_read,
};

/* Real Time Monitor facilities.
 * It allows to peek hw internals. Please refer to TRM */
static ssize_t vha_rtm_read(struct file *file, char __user *buf, size_t len,
			     loff_t *ppos)
{
	struct vha_dev *vha = file->private_data;
	struct vha_dbgfs_ctx *ctx =
			(struct vha_dbgfs_ctx *)vha->dbgfs_ctx;
	int ret;
	char rtm[23];
	uint64_t rtm_data;

	ret = mutex_lock_interruptible(&vha->lock);
	if (!ret) {
		size_t size;

		/* Turn on all clocks forcefully */
		IOWRITE64(vha->reg_base, VHA_CR_SYS_CLK_CTRL0, VHA_SYS_CLOCKS_DEFAULT(ON));
		IOWRITE64(vha->reg_base, VHA_CR_CLK_CTRL0, VHA_MAIN_CLOCKS_DEFAULT(ON));

		/* Set up address of the signal */
		IOWRITE64(vha->reg_base, VHA_CR_RTM_CTRL,
			ctx->rtm_ctrl | VHA_CR_RTM_CTRL_RTM_ENABLE_EN);

		
		/* but N_OF_RTM_STAGES is not accessible by SW*/
		/* so waiting 1 ms for now */
		msleep(1);

		/* Read the data */
		rtm_data = IOREAD64(vha->reg_base, VHA_CR_RTM_DATA);
		size = snprintf(rtm, sizeof(rtm), "%#.8llx %#.8llx\n",
			ctx->rtm_ctrl, rtm_data);

		mutex_unlock(&vha->lock);

		return simple_read_from_buffer(buf, len, ppos, rtm, size);
	}

	return ret;
}

static const struct file_operations vha_rtm_fops = {
	.owner = THIS_MODULE,
	.open = simple_open,
	.read = vha_rtm_read,
};


/* Generic IO access facilities.
 * It allows read/write any register in the address space */
static ssize_t vha_ioreg_read(struct file *file, char __user *buf, size_t len,
			     loff_t *ppos)
{
	struct vha_dev *vha = file->private_data;
	struct vha_dbgfs_ctx *ctx =
			(struct vha_dbgfs_ctx *)vha->dbgfs_ctx;
	char data[32];
	uint64_t io_data;
	size_t size;

	if (ctx->ioreg_addr >= vha->reg_size) {
		dev_err(vha->dev,
				"%s: read attempt beyond reg space (%#llx >= %#llx)!\n",
				__func__, ctx->ioreg_addr, vha->reg_size);
		return -EINVAL;
	}
	/* Read the data */
	io_data = IOREAD64(vha->reg_base, ctx->ioreg_addr);

	size = snprintf(data, sizeof(data), "%#.8llx::%#.16llx\n",
			ctx->ioreg_addr, io_data);

	return simple_read_from_buffer(buf, len, ppos, data, size);
}

static ssize_t vha_ioreg_write(struct file *file, const char __user *buf,
		size_t len, loff_t *ppos)
{
	struct vha_dev *vha = file->private_data;
	struct vha_dbgfs_ctx *ctx =
			(struct vha_dbgfs_ctx *)vha->dbgfs_ctx;
	uint64_t io_data;
	int ret = kstrtou64_from_user(buf, len, 16, &io_data);
	if (ret)
		return ret;

	if (ctx->ioreg_addr >= vha->reg_size) {
		dev_err(vha->dev,
				"%s: write attempt beyond reg space (%#llx >= %#llx)!\n",
				__func__, ctx->ioreg_addr, vha->reg_size);
		return -EINVAL;
	}

	/* Write the data */
	IOWRITE64(vha->reg_base, ctx->ioreg_addr, io_data);

	return len;
}

static const struct file_operations vha_ioreg_fops = {
	.owner = THIS_MODULE,
	.open = simple_open,
	.read = vha_ioreg_read,
	.write = vha_ioreg_write,
};

static ssize_t vha_stats_reset_write(struct file *file, const char __user *buf,
	   size_t count, loff_t *ppos)
{
	struct vha_dev *vha = file->private_data;

	memset(&vha->stats, 0, sizeof(struct vha_stats));

	return count;
}

static const struct file_operations vha_stats_reset_fops = {
	.owner = THIS_MODULE,
	.write = vha_stats_reset_write,
	.open = simple_open,
};

void vha_dbg_init(struct vha_dev *vha)
{
	struct vha_dbgfs_ctx *ctx = devm_kzalloc(vha->dev,
			sizeof(struct vha_dbgfs_ctx), GFP_KERNEL);
	if (!ctx) {
		dev_err(vha->dev,
				"%s: Out of memory when creating debugfs context!\n",
				__func__);
		return;
	}

	/* Create userspace node */
	ctx->debugfs_dir = debugfs_create_dir(vha->miscdev.name, NULL);
	if (!ctx->debugfs_dir) {
		dev_warn(vha->dev,
				"%s: Probably debugfs not enabled in this kernel!\n",
				__func__);
		return;
	}

	/* and some registers for debug */
	if (vha->reg_base) {
		ctx->regset.regs = vha_regs;
		ctx->regset.nregs = ARRAY_SIZE(vha_regs);
		ctx->regset.base = vha->reg_base;
		if (!debugfs_create_file("regdump", S_IRUGO, ctx->debugfs_dir,
					&ctx->regset, &vha_regset_fops))
			dev_warn(vha->dev,
				"%s: failed to create regdump file!\n",
				__func__);
	}

#define VHA_DBGFS_CREATE(_type_, _name_, _vha_dev_member_) \
	{ \
			if (!debugfs_create_##_type_(_name_, \
				S_IRUGO, ctx->debugfs_dir, \
				&vha->_vha_dev_member_)) { \
				dev_warn(vha->dev, \
					"%s: failed to create %s dbg file!\n", \
					__func__, _name_); \
			} \
	}

	VHA_DBGFS_CREATE(u32, "core_freq_khz", freq_khz);
	VHA_DBGFS_CREATE(u32, "core_state", state);
	VHA_DBGFS_CREATE(u64, "core_uptime_ms", stats.uptime_ms);
	VHA_DBGFS_CREATE(u64, "core_last_proc_us", stats.last_proc_us);
	VHA_DBGFS_CREATE(u32, "cnn_kicks", stats.cnn_kicks);
	VHA_DBGFS_CREATE(u32, "cnn_queued_kicks", stats.cnn_queued_kicks);
	VHA_DBGFS_CREATE(u32, "cnn_kicks_completed", stats.cnn_kicks_completed);
	VHA_DBGFS_CREATE(u64, "cnn_total_proc_us", stats.cnn_total_proc_us);
	VHA_DBGFS_CREATE(u64, "cnn_last_proc_us", stats.cnn_last_proc_us);
	VHA_DBGFS_CREATE(u64, "cnn_avg_proc_us", stats.cnn_avg_proc_us);
	VHA_DBGFS_CREATE(u64, "cnn_last_est_proc_us", stats.cnn_last_est_proc_us);
	VHA_DBGFS_CREATE(u64, "cnn_avg_est_proc_us", stats.cnn_avg_est_proc_us);

	VHA_DBGFS_CREATE(u32, "mem_usage_last", stats.mem_usage_last);
	VHA_DBGFS_CREATE(u32, "total_failures", stats.total_failures);

#undef VHA_DBGFS_CREATE

	if (vha->core_props.supported.rtm) {
		if (!debugfs_create_u64("rtm_ctrl",
				S_IWUSR|S_IRUGO, ctx->debugfs_dir,
				&ctx->rtm_ctrl))
			dev_warn(vha->dev,
				"%s: failed to create rtm_ctrl dbg file!\n", __func__);

		if (!debugfs_create_file("rtm_data", S_IRUGO, ctx->debugfs_dir,
				vha, &vha_rtm_fops))
			dev_warn(vha->dev,
				"%s: failed to create debugfs file!\n", __func__);
	}

	if (!debugfs_create_u64("ioreg_addr",
			S_IWUSR|S_IRUGO, ctx->debugfs_dir,
			&ctx->ioreg_addr))
		dev_warn(vha->dev,
			"%s: failed to create ioreg_addr dbg file!\n", __func__);

	if (!debugfs_create_file("ioreg_data", S_IRUGO, ctx->debugfs_dir,
			vha, &vha_ioreg_fops))
		dev_warn(vha->dev,
			"%s: failed to create debugfs file!\n", __func__);

	if (!debugfs_create_file("cnn_utilization", S_IRUGO, ctx->debugfs_dir,
				vha, &vha_cnn_utilization_fops)
		|| !debugfs_create_file("cnn_last_cycles", S_IRUGO,
					ctx->debugfs_dir, vha, &vha_cnn_last_cycles_fops)
		|| !debugfs_create_file("stats_reset", S_IWUSR,
				ctx->debugfs_dir, vha, &vha_stats_reset_fops)
		|| !debugfs_create_file("BVNC", S_IRUGO, ctx->debugfs_dir,
					vha, &vha_bvnc_fops))
		dev_warn(vha->dev,
			"%s: failed to create debugfs file!\n",
			__func__);

	vha->dbgfs_ctx = (void *)ctx;
}

void vha_dbg_deinit(struct vha_dev *vha)
{
	struct vha_dbgfs_ctx *ctx =
			(struct vha_dbgfs_ctx *)vha->dbgfs_ctx;
	/* ctx->debugfs_dir==NULL is safe */
	debugfs_remove_recursive(ctx->debugfs_dir);
}

struct dentry* vha_dbg_get_sysfs(struct vha_dev *vha)
{
	struct vha_dbgfs_ctx *ctx =
			(struct vha_dbgfs_ctx *)vha->dbgfs_ctx;

	return ctx->debugfs_dir;
}
