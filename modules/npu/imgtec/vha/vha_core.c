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
#include <linux/device.h>
#include <linux/gfp.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>
#include <linux/jiffies.h>
#include <linux/list.h>
#include <linux/delay.h>
#include <linux/irq.h>
#include <linux/debugfs.h>

#include <uapi/vha.h>
#include "vha_common.h"
#include "vha_plat.h"
#include "vha_regs.h"

#ifdef KERNEL_DMA_FENCE_SUPPORT
#include <linux/dma-fence.h>
#include <linux/dma-fence-array.h>
#include <linux/sync_file.h>
#include <linux/file.h>
#include <linux/kernel.h>
#endif

#if !defined(HW_AX2) && !defined(HW_AX3)
#error No HW architecture series defined. Either HW_AX2 or HW_AX3 must be defined
#elseif defined(HW_AX2) && defined(HW_AX3)
#error Invalid HW architecture series define. Only one of HW_AX2 or HW_AX3 must be defined.
#endif

#define MIN_ONCHIP_MAP 1
#define MAX_ONCHIP_MAP 128

static uint32_t mmu_mode = 40;
module_param(mmu_mode, uint, 0444);
MODULE_PARM_DESC(mmu_mode,
	"MMU mode: 0=no-MMU, 1=direct (1:1) mappings or 40=40bit (default)");
static uint32_t mmu_ctx_default;
module_param(mmu_ctx_default, uint, 0444);
MODULE_PARM_DESC(mmu_ctx_default, "MMU default context id(0:31) to be used");
static uint32_t mmu_page_size;  /* 0-4kB */
module_param(mmu_page_size, uint, 0444);
MODULE_PARM_DESC(mmu_page_size,
	"MMU page size: 0-4kB, 1-16kB, 2-64kB, 3-256kB, 4-1MB; 5-2MB");

static bool no_clock_disable = false;
module_param(no_clock_disable, bool, 0444);
MODULE_PARM_DESC(no_clock_disable,
		"if Y, the core is not disabled when inactive, otherwise APM is used");
static int pm_delay = 0;
module_param(pm_delay, int, S_IRUSR | S_IRGRP);
MODULE_PARM_DESC(pm_delay, "Delay, in ms, before powering off the core that's idle");

static int freq_khz = -1;
module_param(freq_khz, int, 0444);
MODULE_PARM_DESC(freq_khz,
		"core frequency in kHz, -1=start self measurement during driver load, 0=use platform defined value");
static uint32_t hw_bypass;
module_param(hw_bypass, uint, 0444);
MODULE_PARM_DESC(hw_bypass,
		"Number of cnn kicks(segments) to be bypassed within the session, 0=none");
static uint32_t slc_bypass;
module_param(slc_bypass, uint, 0444);
MODULE_PARM_DESC(slc_bypass, "SLC bypass mode");
static uint32_t low_latency = VHA_LL_SW_KICK;
module_param(low_latency, uint, 0444);
MODULE_PARM_DESC(low_latency, "Low latency mode: 0-disabled, 1-sw kick, 2-self kick");

static bool zero_buffers;
module_param(zero_buffers, bool, 0444);
MODULE_PARM_DESC(zero_buffers, "fill every allocated buffer with zeros");

static unsigned long onchipmem_phys_start= ~0;
module_param(onchipmem_phys_start, ulong, 0444);
MODULE_PARM_DESC(onchipmem_phys_start,
	"Physical address of start of on-chip ram. '0xFs' means that ocm is disabled");
static uint32_t onchipmem_size;
module_param(onchipmem_size, uint, 0444);
MODULE_PARM_DESC(onchipmem_size,
	"Size of on-chip memory in bytes");

/* bringup test: force MMU fault with MMU base register */
static bool test_mmu_base_pf;
module_param(test_mmu_base_pf, bool, 0444);
MODULE_PARM_DESC(test_mmu_base_pf,
	"Bringup test: force MMU page fault on first access");

/* bringup test: do not map into the device after the Nth buffer */
static int32_t test_mmu_no_map_count = -1;
module_param(test_mmu_no_map_count, int, 0444);
MODULE_PARM_DESC(test_mmu_no_map_count,
	"Bringup test: force MMU page faults if count >= 0");

#ifdef VHA_SCF
static bool parity_disable = false;
module_param(parity_disable, bool, 0444);
MODULE_PARM_DESC(parity_disable,
		"if Y, the core parity feature will be disabled, if it is supported");
#endif

/* Fault inject parameter is only applicable when
 * kernel fault injection feature is enabled
 * in the kernel options -> CONFIG_FAULT_INJECTION=y
 * See Documentation/fault-injection/
 */
static bool fault_inject;
module_param(fault_inject, bool, 0444);
MODULE_PARM_DESC(fault_inject,
		"Enable fault injection. To be used with kernel fault injection feature");

/* Event observers, to be notified when significant events occur */
struct vha_observers vha_observers;

/* Driver context */
static struct {
	/* Available memory heaps. List of <struct vha_heap> */
	struct list_head heaps;
	/* heap id for all internal allocations */
	int internal_heap_id;

	/* Memory Management context for driver */
	struct mem_ctx *mem_ctx;

	/* List of associated <struct vha_dev> */
	struct list_head devices;

	unsigned int num_devs;

	int initialised;
} drv;

/* node for heaps list */
struct vha_heap {
	int id;
	struct list_head list;	/* Entry in <struct vha_drv:heaps> */
};

/* Helper structure for error definition */
struct vha_biterr {
	int e;
	uint32_t b;
	const char* s;
};
#define ERR_EVENT_DESC(b) VHA_CR_OS(VHA_EVENT_STATUS_VHA_##b##_EN), __stringify(b)

static void cmd_worker(struct work_struct *work);
static bool vha_is_busy(struct vha_dev *vha);
static void vha_sched_apm(struct vha_dev *vha, uint32_t delay_ms);


static const size_t mmu_page_size_kb_lut[] =
		{ 4096, 16384, 65536, 262144, 1048576, 2097152};

static void mmu_flush(const struct device *dev,
		struct vha_dev *vha, int ctx_id)
{
	uint64_t inval = VHA_CR_OS(MMU_CTRL_INVAL_PC_EN) |
				VHA_CR_OS(MMU_CTRL_INVAL_PD_EN) |
				VHA_CR_OS(MMU_CTRL_INVAL_PT_EN);

	/* No need to handle mmu cache, when core is already offline */
	if (vha->state == VHA_STATE_OFF)
		return;

#if defined(HW_AX3)
	IOPOLL64_PDUMP(0, 20, 150, (uint64_t)VHA_CR_OS(MMU_CTRL_INVAL_STATUS_PENDING_EN),
				VHA_CR_OS(MMU_CTRL_INVAL_STATUS));
#endif

	if (unlikely(ctx_id == VHA_INVALID_ID))
		inval |= VHA_CR_OS(MMU_CTRL_INVAL_ALL_CONTEXTS_EN);
	else {
		inval |= ctx_id << VHA_CR_OS(MMU_CTRL_INVAL_CONTEXT_SHIFT);
	}
	dev_dbg(dev, "%s: ctx_id:%d (0x%llx)\n", __func__, ctx_id, inval);

	img_pdump_printf("-- MMU invalidate TLB caches\n");
	IOWRITE64_PDUMP(inval, VHA_CR_OS(MMU_CTRL_INVAL));
}

/* this function is called from img_mmu, to handle cache issues */
static void mmu_callback(enum img_mmu_callback_type callback_type,
			int buf_id, void *data)
{
	struct vha_session *session = data;
	struct vha_dev *vha = session->vha;
	int ctx_id;

	if (!vha)
		return;

	for (ctx_id = 0; ctx_id < ARRAY_SIZE(session->mmu_ctxs); ctx_id++)
		mmu_flush(vha->dev, vha, session->mmu_ctxs[ctx_id].hw_id);
#if defined(VHA_MMU_MIRRORED_CTX_SUPPORT) && defined(HW_AX3)
	{
		/* Need to flush auxilary hw context */
		int hw_id = session->mmu_ctxs[VHA_MMU_REQ_MODEL_CTXID].hw_id +
				VHA_MMU_AUX_HW_CTX_SHIFT;
		mmu_flush(vha->dev, vha, hw_id);
	}
#endif
}

/* Calculate current timespan for the given timestamp */
static bool get_timespan_us(struct timespec *from, struct timespec *to, uint64_t *result)
{
	long long total = 0;

	if (!timespec_valid(from) || !timespec_valid(to))
		return false;

	if (timespec_compare(from, to) >= 0)
		return false;

	total = NSEC_PER_SEC * to->tv_sec +
				to->tv_nsec;
	total -= NSEC_PER_SEC * from->tv_sec +
			from->tv_nsec;
	do_div(total, 1000UL);
	*result = total;

	return true;
}

void vha_early_init(void)
{
	INIT_LIST_HEAD(&drv.heaps);
	drv.internal_heap_id = VHA_INVALID_ID;

	drv.mem_ctx = NULL;

	INIT_LIST_HEAD(&drv.devices);
}

/*
 * Lazy intialization of main driver context (when first core is probed)
 */
static int vha_init(struct vha_dev *vha,
			const struct heap_config heap_configs[], int heaps)
{
	struct device *dev = vha->dev;
	int ret, i;

	/* Initialise memory management component */
	for (i = 0; i < heaps; i++) {
		struct vha_heap *heap;

		dev_dbg(dev, "%s: adding heap of type %d\n",
			__func__, heap_configs[i].type);

		heap = kzalloc(sizeof(struct vha_heap), GFP_KERNEL);
		if (!heap) {
			ret = -ENOMEM;
			goto heap_add_failed;
		}

		ret = img_mem_add_heap(&heap_configs[i], &heap->id);
		if (ret < 0) {
			dev_err(dev, "%s: failed to init heap (type %d)!\n",
				__func__, heap_configs[i].type);
			kfree(heap);
			goto heap_add_failed;
		}
		list_add(&heap->list, &drv.heaps);

		/* Implicitly, first heap is used for internal allocations */
		if (drv.internal_heap_id < 0) {
			drv.internal_heap_id = heap->id;
			dev_dbg(dev, "%s: using heap %d for internal alloc\n",
				__func__, drv.internal_heap_id);
		}
	}

	if (vha->core_props.ocm_size_bytes && onchipmem_phys_start == ~0)
		dev_warn(dev, "%s: Onchip memory physical address not set!\n",
						__func__);

	/* OCM heap type is automatically appended */
	if (vha->core_props.ocm_size_bytes && onchipmem_phys_start != ~0) {
		struct heap_config heap_cfg;
		struct vha_heap *heap;

		memset(&heap_cfg, 0, sizeof(heap_cfg));
		heap_cfg.type = IMG_MEM_HEAP_TYPE_OCM;
		heap_cfg.options.ocm.phys = onchipmem_phys_start;
		heap_cfg.options.ocm.size = vha->core_props.ocm_size_bytes;

		dev_dbg(dev, "%s: adding heap of type %d\n",
				__func__, heap_cfg.type);

		heap = kzalloc(sizeof(struct vha_heap), GFP_KERNEL);
		if (!heap) {
			ret = -ENOMEM;
			goto heap_add_failed;
		}

		ret = img_mem_add_heap(&heap_cfg, &heap->id);
		if (ret < 0) {
			dev_err(dev, "%s: failed to init heap (type %d)!\n",
				__func__, heap_configs[i].type);
			kfree(heap);
			goto heap_add_failed;
		}
		list_add(&heap->list, &drv.heaps);
	}

	/* Do not proceed if internal heap not defined */
	if (drv.internal_heap_id < 0) {
		dev_err(dev, "%s: failed to locate heap for internal alloc\n",
			__func__);
		ret = -EINVAL;
		/* Loop registered heaps just for sanity */
		goto heap_add_failed;
	}

	/* Create memory management context for HW buffers */
	ret = img_mem_create_proc_ctx(&drv.mem_ctx);
	if (ret) {
		dev_err(dev, "%s: failed to create mem context (err:%d)!\n",
			__func__, ret);
		goto create_mem_context_failed;
	}

	drv.initialised = 1;

	dev_dbg(dev, "%s: vha drv init done\n", __func__);
	return 0;

create_mem_context_failed:
heap_add_failed:
	while (!list_empty(&drv.heaps)) {
		struct vha_heap *heap;

		heap = list_first_entry(&drv.heaps, struct vha_heap, list);
		list_del(&heap->list);
		img_mem_del_heap(heap->id);
		kfree(heap);
	}
	drv.internal_heap_id = VHA_INVALID_ID;
	return ret;
}

int vha_deinit(void)
{
	/* Destroy memory management context */
	if (drv.mem_ctx) {
		size_t mem_usage = img_mem_get_usage_max(drv.mem_ctx);
		uint32_t MB = mem_usage / (1024 * 1024);
		uint32_t bytes = mem_usage - (MB * (1024 * 1024));
		uint32_t kB = (bytes * 1000) / (1024 * 1024);

		pr_debug("%s: Total kernel memory used: %u.%u MB\n",
				__func__, MB, kB);

		img_mem_destroy_proc_ctx(drv.mem_ctx);
		drv.mem_ctx = NULL;
	}

	/* Deinitialize memory management component */
	while (!list_empty(&drv.heaps)) {
		struct vha_heap *heap;

		heap = list_first_entry(&drv.heaps, struct vha_heap, list);
		list_del(&heap->list);
		img_mem_del_heap(heap->id);
		kfree(heap);
	}
	drv.internal_heap_id = VHA_INVALID_ID;

	drv.initialised = 0;
	vha_pdump_deinit();
	return 0;
}

static void vha_dev_ready(struct vha_dev *vha)
{
#ifndef CONFIG_VHA_DUMMY
	if (!vha->is_ready)
		return;
#endif
	dev_dbg(vha->dev, "%s\n", __func__);

	vha_dev_wait(vha);

	/* Finally enable ALL events */
	img_pdump_printf("-- Enable ALL events\n");
	IOWRITE64_PDUMP(VHA_EVNTS_DEFAULT, VHA_CR_OS(VHA_EVENT_ENABLE));
	img_pdump_printf("-- Clear ALL events\n");
	IOWRITE64_PDUMP(VHA_EVNTS_DEFAULT, VHA_CR_OS(VHA_EVENT_CLEAR));
#ifdef HW_AX2
	img_pdump_printf("-- Clear CNN status\n");
	IOWRITE64_PDUMP(0, VHA_CR_OS(CNN_STATUS));
#endif
	img_pdump_printf("-- Clear MMU fault status\n");
	IOWRITE64_PDUMP(0, VHA_CR_OS(MMU_FAULT_STATUS1));
	img_pdump_printf("-- Clear SLC debug status\n");
	IOWRITE64_PDUMP(0, VHA_CR_SLC_STATUS_DEBUG);
	img_pdump_printf("-- Reset PERF counters\n");
	IOWRITE64_PDUMP(0, VHA_CR_PERF_RESET_FULL);
}

#if _OSID_ == 0 /* For HW_AX2 this is always true */
static void vha_dev_reset(struct vha_dev *vha)
{
	/* Perform reset procedure */
	img_pdump_printf("-- Set RESET bits\n");
	IOWRITE64_PDUMP(VHA_RESET_DEFAULT, VHA_CR_RESET_CTRL);
	/* poll for reset deassertion
	 * count=16, delay=256cycles
	 */
	img_pdump_printf("-- Wait for RESET deassertion\n");
	IOPOLL64_PDUMP(0, 16, 256, VHA_CR_RESET_CTRL_MASKFULL,
					VHA_CR_RESET_CTRL);
}
#endif

/* start the device */
static int vha_dev_start(struct vha_dev *vha)
{
	uint64_t __maybe_unused sys_clks = 0;
	uint64_t __maybe_unused main_clks = 0;
	int ret = 0;

	/* Cancel APM request if new inference comes */
	cancel_delayed_work(&vha->apm_dwork);

	if (vha->state == VHA_STATE_ON)
		return -1;

	dev_dbg(vha->dev, "%s\n", __func__);

/* Assuming OS0 is the privileged one */
#if _OSID_ == 0 /* For HW_AX2 this is always true */
	/////////////// POWER ON //////////////////////////
	img_pdump_printf("-- POWER_ON_BEGIN\n");
	/* Prepare device ...  */
	vha_dev_prepare(vha);
	/* Reset core */
	vha_dev_reset(vha);

	/* Always AUTO gating  when needed */
	sys_clks = VHA_SYS_CLOCKS_DEFAULT(AUTO);
	main_clks = VHA_MAIN_CLOCKS_DEFAULT(AUTO);
	/* Enable sys clocks ! */
	img_pdump_printf("-- Enable SYS clocks\n");
	IOWRITE64_PDUMP(sys_clks, VHA_CR_SYS_CLK_CTRL0);
	/* Enable main clocks ! */
	img_pdump_printf("-- Enable MAIN clocks\n");
	IOWRITE64_PDUMP(main_clks, VHA_CR_CLK_CTRL0);
	img_pdump_printf("-- POWER_ON_END\n");
	/* Call device specific setup */
	vha_dev_setup(vha);
	/////////////////////////////////////////////////////
#endif

	vha_dev_ready(vha);

	vha->state = VHA_STATE_ON;
	/* Remember the time hw is powered on */
	getnstimeofday(&vha->stats.hw_start);
	return ret;
}

/* stop the device */
static int vha_dev_stop(struct vha_dev *vha, bool reset)
{
	int ret = 0;

	if (vha->state == VHA_STATE_OFF)
		return -1;

	/* Cancel APM request if we are about to power off the core */
	cancel_delayed_work(&vha->apm_dwork);

	dev_dbg(vha->dev, "%s\n", __func__);
	/* Disable events at first */
	img_pdump_printf("-- Disable CNN events\n");
	IOWRITE64_PDUMP(0, VHA_CR_OS(VHA_EVENT_ENABLE));
	/* Clear the START bit !
	 * Note: It is stated that writing 0 to this bit has no effect,
	 * however in error cases, some hw blocks may start
	 * to process previous requests after turning on the clocks
	 * which was previously disabled */
	IOWRITE64_PDUMP(0, VHA_CR_OS(CNN_CONTROL));

	/* Disable core events */
	img_pdump_printf("-- Disable CORE events\n");
	IOWRITE64_PDUMP(0, VHA_CR_OS(VHA_EVENT_ENABLE));

	vha->is_ready = false;
/* Assuming OS0 is the privileged one */
#if _OSID_ == 0 /* For HW_AX2 this is always true */
	/////////////// POWER_OFF //////////////////////////
	img_pdump_printf("-- POWER_OFF_BEGIN\n");
	/* Reset core in case of error or pending inference */
	if (reset)
		vha_dev_reset(vha);

	/* If auto gating was turned on, wait for clocks idle state */
	img_pdump_printf("-- Wait for clocks IDLE state\n");
	IOPOLL64_PDUMP(0, 100, 1000,
			VHA_CR_CLK_STATUS0_MASKFULL,
			VHA_CR_CLK_STATUS0);
	/* Wait for MMU,CCM,RDI,XBAR  IDLE state */
	img_pdump_printf("-- Wait for memory bus interface IDLE state\n");
	IOPOLL64_PDUMP(0xFFFF, 100, 1000, VHA_CR_SLC_IDLE_MASKFULL,
			VHA_CR_SLC_IDLE);

	/* Finally disable clocks */
	img_pdump_printf("-- Disable MAIN clocks\n");
	IOWRITE64_PDUMP(0, VHA_CR_CLK_CTRL0); /* main */
	img_pdump_printf("-- Disable SYS clocks\n");
	IOWRITE64_PDUMP(0, VHA_CR_SYS_CLK_CTRL0); /* sys */
	img_pdump_printf("-- POWER_OFF_END\n");
#endif

	vha->state = VHA_STATE_OFF;
	/* Update the up time of the core */
	if (!vha->do_calibration) {
		uint64_t tmp = 0;
		struct timespec now;
		getnstimeofday(&now);
		if (get_timespan_us(&vha->stats.hw_start, &now, &tmp)) {
			do_div(tmp, 1000UL);
			vha->stats.uptime_ms += tmp;
			tmp = vha->stats.cnn_total_proc_us;
			if (vha->stats.uptime_ms) {
				do_div(tmp, vha->stats.uptime_ms);
				vha->stats.cnn_utilization = tmp;
			} else
				dev_dbg(vha->dev,
					"%s Too short execution time to calculate utilization!\n",
					__func__);
		} else
			WARN_ON(1);
	}

	vha->active_mmu_ctx = VHA_INVALID_ID;

	spin_lock_irq(&vha->irq_lock);
	vha->irq_status = 0;
	vha->irq_count = 0;
	vha->stream_count = 0;
	spin_unlock_irq(&vha->irq_lock);

	return ret;
}

/* Top half */
irqreturn_t vha_handle_irq(struct device *dev)
{
	struct vha_dev *vha = dev_get_drvdata(dev);
	int ret = IRQ_HANDLED;
	uint64_t status;

	if (!vha)
		return IRQ_NONE;

	status = IOREAD64(vha->reg_base, VHA_CR_OS(VHA_EVENT_STATUS));
	/* On fpga platform it is possible to get
	 * a spurious interrupt when the hw died
	 * Do not proceed, just throw a warning */
	if (status == VHA_DEAD_HW || status == ~0) {
		WARN_ONCE(1, "Hardware is dead!");
		return IRQ_NONE;
	}

	if (status & VHA_EVNTS_DEFAULT) {
		uint8_t count;
		/* clear the interrupt:
		 * best not to write pdump in interrupts */
		IOWRITE64(vha->reg_base, VHA_CR_OS(VHA_EVENT_CLEAR),
			status & VHA_EVNTS_DEFAULT);

		/* Read the stream count as single IRQ may be raised for multiple kicks */
		count = IOREAD64(vha->reg_base, VHA_CR_OS(CNN_STATUS)) &
					~VHA_CR_OS0_CNN_STATUS_STREAM_COUNT_CLRMSK;

		spin_lock(&vha->irq_lock);
		/* store the status to be processed later */
		vha->irq_status |= status;
		if (vha->low_latency == VHA_LL_SELF_KICK)
			/* Two separate IRQs may be raised for multiple kicks */
			vha->irq_count += count - vha->stream_count;
		else
			/* Only single IRQ may be raised otherwise ... */
			vha->irq_count = count - vha->stream_count;
		vha->stream_count = count;
		/* Record hw processing end timestamps */
		vha->stats.hw_proc_end_prev = vha->stats.hw_proc_end;
		getnstimeofday(&vha->stats.hw_proc_end);
		spin_unlock(&vha->irq_lock);

		ret = IRQ_WAKE_THREAD;
	} else
		return IRQ_NONE;

	dev_dbg(dev, "IRQ 0x%08llx\n", status);

	return ret;
}

/* notify the user space if a response msg is ready */
void vha_cmd_notify(struct vha_cmd *cmd)
{
	struct vha_session *session = cmd->session;
	struct vha_rsp *rsp = cmd->rsp;
	dev_dbg(session->vha->dev, "%s %p\n", __func__, cmd);

	if (rsp) {
		cmd->rsp = NULL;
		list_add_tail(&rsp->list, &session->rsps);
	}
	wake_up(&session->wq);
	/* we are done with this cmd, let's free it */
	list_del(&cmd->list);
	kfree(cmd);
}

static bool vha_rollback_cnn_cmds(struct vha_dev *vha)
{
	bool processing = false;
	/* Not processed commands are still on the pending list
	 * of each session, so just mark the hw pending lists as empty */
	if (vha->pendcmd[VHA_CNN_CMD].cmd) {
		vha->pendcmd[VHA_CNN_CMD].cmd->in_hw = false;
		vha->pendcmd[VHA_CNN_CMD].cmd->queued = false;
		vha->pendcmd[VHA_CNN_CMD].cmd = NULL;
		processing = true;
	}
	/* low_latency ...*/
	if (vha->queuedcmd[VHA_CNN_CMD].cmd) {
		vha->queuedcmd[VHA_CNN_CMD].cmd->in_hw = false;
		vha->queuedcmd[VHA_CNN_CMD].cmd->queued = false;
		vha->queuedcmd[VHA_CNN_CMD].cmd = NULL;
	}
	dev_dbg(vha->dev, "%s: (%d)\n", __func__, processing);

	return processing;
}

/*
 * handles the command (of given cmd_idx) already processed by the hw,
 * errors from VHA_CR_VHA_EVENT_STATUS (only for relevant cmd) should be
 * passed as err
 */
static bool vha_handle_cmd(struct vha_dev *vha, int cmd_idx, int status)
{
	struct vha_cmd *cmd = NULL;

	if (cmd_idx >= VHA_CMD_MAX)
		return false;

	cmd = vha->pendcmd[cmd_idx].cmd;
	if (unlikely(!cmd)) {
		dev_dbg(vha->dev, "No command. Probably it has been aborted\n");
		return false;
	}

	{
		uint64_t proc_time = 0;
		struct timespec *from = &cmd->hw_proc_start;
		struct timespec *to = &vha->stats.hw_proc_end;

		if (timespec_compare(&vha->stats.hw_proc_end_prev, &cmd->hw_proc_start) >= 0)
			from = &vha->stats.hw_proc_end_prev;

		if (get_timespan_us(from, to, &proc_time)) {
			vha->stats.last_proc_us = proc_time;
		} else {
			vha->stats.last_proc_us = 0;
		}
		/* Update cnn stats */
		vha_cnn_update_stats(vha);
	}

	if (cmd_idx == VHA_CNN_CMD)
		vha_cnn_cmd_completed(cmd, status);

	if (status) {
		/* Rollback any queued command ... */
		vha_rollback_cnn_cmds(vha);
		/* Notify immediately current command */
		vha_cmd_notify(cmd);

		return false;
	}

	if (vha->queuedcmd[cmd_idx].cmd)
		vha->pendcmd[cmd_idx].cmd = vha->queuedcmd[cmd_idx].cmd;
	else
		vha->pendcmd[cmd_idx].cmd = NULL;

	vha->queuedcmd[cmd_idx].cmd = NULL;
	dev_dbg(vha->dev,
			"%s: %p -> new pending %p\n",
			__func__, cmd, vha->pendcmd[cmd_idx].cmd);

	vha_cmd_notify(cmd);

	return true;
}

static void vha_measure_core_freq(struct vha_dev *vha)
{
	vha_dev_stop(vha, false);
	vha->do_calibration = false;

	if (vha->stats.last_proc_us) {
		uint64_t proc = vha->stats.last_proc_us;
		do_div(proc, 1000UL);
		if (proc) {
			uint64_t cycles = vha->calibration_cycles;
			do_div(cycles, proc);
			vha->freq_khz = cycles;
			dev_info(vha->dev,
			"%s: Measured core clock frequency[kHz]: %u\n",
			__func__, vha->freq_khz);
			return;
		}
	}

	dev_info(vha->dev,
		"%s: Can't measure core clock frequency!\n",
		__func__);
}

static bool vha_check_calibration(struct vha_dev *vha)
{
	if (vha->stats.last_proc_us) {
		/* Core may have been kicked to
		 * measure frequency */
		if (vha->do_calibration) {
			vha_measure_core_freq(vha);
			/* Something may have been scheduled in
			 * the middle so poke the worker */
			vha_chk_cmd_queues(vha, false);
			return true;
		}
	}

	return false;
}

static void do_mmu_ctx_setup(struct vha_dev *vha,
			uint8_t hw_id, int pc_bufid, uint32_t pc_baddr)
{
	img_pdump_printf("-- Setup MMU context:%d\n", hw_id);
	IOWRITE64_PDUMP(hw_id, VHA_CR_OS(MMU_CBASE_MAPPING_CONTEXT));

	if (!test_mmu_base_pf) {
		IOWRITE64(vha->reg_base, VHA_CR_OS(MMU_CBASE_MAPPING), pc_baddr);

		/* This is physical address so we need use MEM_OS0:BLOCK tag
		 * when pdump'ing. */
		img_pdump_printf("-- Setup MMU base address\n"
				"WRW "_PMEM_":$0 "_PMEM_":BLOCK_%d:0 -- 'PC'\n"
				"SHR "_PMEM_":$0 "_PMEM_":$0 %d\n"
				"WRW64 :REG:%#x "_PMEM_":$0\n", pc_bufid,
				IMG_MMU_PC_ADDR_SHIFT,
				VHA_CR_OS(MMU_CBASE_MAPPING));
		dev_dbg(vha->dev, "%s: setting hardware ctx id:%u\n", __func__, hw_id);
	} else
		dev_info(vha->dev, "Bringup test: force MMU base page fault\n");
}

void vha_mmu_setup(struct vha_session *session)
{
	struct vha_dev *vha = session->vha;
	int ctx_id;

	for (ctx_id = 0; ctx_id < ARRAY_SIZE(session->mmu_ctxs); ctx_id++)
		dev_dbg(vha->dev,
				"%s: mode:%d session ctxid:%x active ctxid:%x\n",
				__func__, vha->mmu_mode,
				session->mmu_ctxs[ctx_id].id,
				vha->active_mmu_ctx);


	if (!vha->mmu_mode) {
		img_pdump_printf("-- MMU bypass ON\n");
		IOWRITE64_PDUMP(VHA_CR_OS(MMU_CTRL_BYPASS_EN),
			VHA_CR_OS(MMU_CTRL));
		return;
	}

	/* Using model context to track active context */
	if (session->mmu_ctxs[VHA_MMU_REQ_MODEL_CTXID].id == vha->active_mmu_ctx)
		return;

	img_pdump_printf("-- MMU_SETUP_BEGIN\n");

	for (ctx_id = 0; ctx_id < ARRAY_SIZE(session->mmu_ctxs); ctx_id++) {
		do_mmu_ctx_setup(vha, session->mmu_ctxs[ctx_id].hw_id,
				session->mmu_ctxs[ctx_id].pc_bufid,
				session->mmu_ctxs[ctx_id].pc_baddr);
		/* If there are multiple sessions using the same mmu hardware context
		 * we need to flush caches for the old context (id is the same).
		 * This will happen when number of processes is > VHA_MMU_MAX_HW_CTXS */
		if (vha->mmu_ctxs[session->mmu_ctxs[ctx_id].hw_id] > 1)
			mmu_flush(vha->dev, vha, session->mmu_ctxs[ctx_id].hw_id);
	}
#if defined(VHA_MMU_MIRRORED_CTX_SUPPORT) && defined(HW_AX3)
	{
		/* Need to program auxilary hw context to
		 * point the same page tables as base context */
		int hw_id = session->mmu_ctxs[VHA_MMU_REQ_MODEL_CTXID].hw_id +
				VHA_MMU_AUX_HW_CTX_SHIFT;
		do_mmu_ctx_setup(vha, hw_id,
				session->mmu_ctxs[VHA_MMU_REQ_MODEL_CTXID].pc_bufid,
				session->mmu_ctxs[VHA_MMU_REQ_MODEL_CTXID].pc_baddr);
		if (vha->mmu_ctxs[session->mmu_ctxs[VHA_MMU_REQ_MODEL_CTXID].hw_id] > 1)
			mmu_flush(vha->dev, vha, hw_id);
	}
#endif

	/* Using model context to track context change */
	vha->active_mmu_ctx = session->mmu_ctxs[VHA_MMU_REQ_MODEL_CTXID].id;
	dev_dbg(vha->dev, "%s: update ctx id active:%x pc:%#x\n",
			__func__, vha->active_mmu_ctx,
			session->mmu_ctxs[VHA_MMU_REQ_MODEL_CTXID].pc_baddr <<
			VHA_CR_OS(MMU_CBASE_MAPPING_BASE_ADDR_ALIGNSHIFT));

	img_pdump_printf("-- MMU_SETUP_END\n");
}

static void vha_mmu_status(struct vha_dev *vha)
{
	const char levels[][5] = {"PT", "PD", "PC", "BASE"};

	uint64_t status1 = IOREAD64(vha->reg_base,
		VHA_CR_OS(MMU_FAULT_STATUS1));
	uint64_t status2 = IOREAD64(vha->reg_base,
		VHA_CR_OS(MMU_FAULT_STATUS2));

	uint64_t addr = VHA_CR_GETBITS_OS(MMU_FAULT_STATUS1, ADDRESS, status1);
	uint8_t level = VHA_CR_GETBITS_OS(MMU_FAULT_STATUS1, LEVEL, status1);
	uint8_t req_id = VHA_CR_GETBITS_OS(MMU_FAULT_STATUS1, REQ_ID, status1);
	uint8_t ctx = VHA_CR_GETBITS_OS(MMU_FAULT_STATUS1, CONTEXT, status1);
	uint8_t rnw = VHA_CR_GETBITS_OS(MMU_FAULT_STATUS1, RNW, status1);
	uint8_t type = VHA_CR_GETBITS_OS(MMU_FAULT_STATUS1, TYPE, status1);
	uint8_t fault = VHA_CR_GETBITS_OS(MMU_FAULT_STATUS1, FAULT, status1);

	uint8_t bif_id = VHA_CR_GETBITS_OS(MMU_FAULT_STATUS2, BIF_ID, status2);
	uint8_t tlb_entry = VHA_CR_GETBITS_OS(MMU_FAULT_STATUS2, TLB_ENTRY, status2);
	uint8_t slc_bank = VHA_CR_GETBITS_OS(MMU_FAULT_STATUS2, BANK, status2);
	uint64_t mapping = 0;

	/* Select context and read current pc */
	IOWRITE64(vha->reg_base, VHA_CR_OS(MMU_CBASE_MAPPING_CONTEXT), ctx);
	mapping = IOREAD64(vha->reg_base, VHA_CR_OS(MMU_CBASE_MAPPING));

	/* false alarm ? */
	if (!fault)
		return;

	dev_dbg(vha->dev, "%s: MMU FAULT: s1:%llx s2:%llx\n",
			__func__, status1, status2);

	dev_warn(vha->dev, "%s: MMU fault while %s @ 0x%llx\n",
			__func__, (rnw) ? "reading" : "writing", addr << 4);
	dev_warn(vha->dev, "%s: level:%s Requestor:%x Context:%x Type:%s\n",
			__func__, levels[level], req_id, ctx,
			(type == 0) ? "VALID" :
			(type == 2) ? "READ-ONLY" :
			"UNKNOWN");
	dev_warn(vha->dev, "%s: bif_id:%x tlb_entry:%x slc_bank:%x\n",
			__func__, bif_id, tlb_entry, slc_bank);
	dev_warn(vha->dev, "%s: current mapping@context%d:%#llx\n",
			__func__, ctx,
			mapping <<
			VHA_CR_OS(MMU_CBASE_MAPPING_BASE_ADDR_ALIGNSHIFT));
}

static void vha_do_queued_cmd(struct vha_dev *vha, int cmd_idx)
{
	struct vha_cmd *cmd, *pend;

	cmd = vha->queuedcmd[cmd_idx].cmd;

	dev_dbg(vha->dev,
			"%s: queued %p pending %p\n",
			__func__, cmd, vha->pendcmd[cmd_idx].cmd);

	if (!cmd || (cmd &&
				((vha->low_latency == VHA_LL_DISABLED ||
				vha->low_latency == VHA_LL_SELF_KICK) ||
						!cmd->queued))) {
		dev_dbg(vha->dev, "%s: skipping!\n", __func__);
		return;
	}

	/* store actual pending command as it will be modified */
	pend = vha->pendcmd[cmd_idx].cmd;

	/* at this point we should be able to process the cmd */
	vha_do_cnn_cmd(cmd);

	/* restore pending */
	vha->pendcmd[cmd_idx].cmd = pend;
}

static int vha_report_failure(struct vha_dev *vha, uint64_t status,
		const struct vha_biterr bits[], int bits_size)
{
	int error = 0;
	int i;
	int cmdid = -1;

	if (vha->pendcmd[VHA_CNN_CMD].cmd)
		cmdid = vha->pendcmd[VHA_CNN_CMD].cmd->user_cmd.cmd_id;

	if (vha_observers.error)
		vha_observers.error(vha->id, cmdid, status);

	/* event status in human readable form */
	for (i = 0; i < bits_size; i++) {
		if (status & bits[i].b) {
			dev_err(vha->dev,
				" event status: %s\n",
				bits[i].s);
			/* convert from register bits into POSIX errno
			* if multiple errors, then arbitrary errno choice */
			error = bits[i].e;
		}
	}

	return error;
}

/* if vha event register reports CNN events, so handle them */
static int vha_handle_cnn_event(struct vha_dev *vha, uint64_t event_status)
{
	int err = 0;

	if (vha_check_calibration(vha))
		return 0;

	if (event_status & VHA_CNN_ERR_EVNTS) {
		static const struct vha_biterr err_bits[] = {
			{-ETIMEDOUT, ERR_EVENT_DESC(CNN0_MEM_WDT)},
#ifdef HW_AX2
			{-ETIMEDOUT, ERR_EVENT_DESC(CNN0_WDT)},
#endif
			{-EIO,       ERR_EVENT_DESC(CNN0_ERROR)}
		};

		err = vha_report_failure(vha,
				event_status, err_bits, ARRAY_SIZE(err_bits));

		vha_cnn_dump_status(vha);
	}

	/* Poke the hw if there were already
	 * command queued in the hw */
	if (!err)
		vha_do_queued_cmd(vha, VHA_CNN_CMD);
	/* Handle actual command */
	if (vha_handle_cmd(vha, VHA_CNN_CMD, err) == false)
		err = -ENOENT;

	return err;
}

/* Bottom half */
irqreturn_t vha_handle_thread_irq(struct device *dev)
{
	struct vha_dev *vha = dev_get_drvdata(dev);
	irqreturn_t ret = IRQ_HANDLED;
	uint64_t status;
	uint8_t count, c = 0;
	int err = 0;

	if (!vha)
		return IRQ_NONE;

	mutex_lock(&vha->lock);

	spin_lock_irq(&vha->irq_lock);
	status = vha->irq_status;
	vha->irq_status = 0;
	count = vha->irq_count;
	vha->irq_count = 0;
	if (!count) {
		uint64_t proc_time = 0;

		if (get_timespan_us(&vha->stats.hw_proc_start, &vha->stats.hw_proc_end,
					&proc_time)) {
			vha->stats.last_proc_us = proc_time;
		} else {
			vha->stats.last_proc_us = 0;
		}
	}
	spin_unlock_irq(&vha->irq_lock);
	/* Command may have been aborted before this handler is executed */
	if (!status) {
		mutex_unlock(&vha->lock);
		return ret;
	}

	dev_dbg(dev, "%s: status:%llx count:%d\n",
			__func__, status, count);

	do {
		if (status & VHA_CORE_EVNTS) {
			static const struct vha_biterr err_bits[] = {
				{-EIO,       ERR_EVENT_DESC(AXI_ERROR)},
				{-EFAULT,    ERR_EVENT_DESC(MMU_PAGE_FAULT)},
#ifdef HW_AX3
#ifdef VHA_SCF
				{-EIO,       ERR_EVENT_DESC(MMU_PARITY_ERROR)},
				{-EIO,       ERR_EVENT_DESC(PARITY_ERROR)},
				{-EIO,       ERR_EVENT_DESC(LOCKSTEP_ERROR)},
#endif
				{-ETIMEDOUT, ERR_EVENT_DESC(HL_WDT)},
				{-EIO,       ERR_EVENT_DESC(ERROR)}
#endif
			};

#ifdef HW_AX3
			if (vha->is_ready)
				if (vha_check_calibration(vha))
					break;

			if (status & VHA_EVENT_TYPE(READY)
					&& !vha->is_ready) {
				vha->is_ready = true;
				vha_dev_ready(vha);
				if (vha->do_calibration) {
					vha_cnn_gen_wdt(vha);
					break;
				} else
					vha_chk_cmd_queues(vha, true);
			}
#endif

			err = vha_report_failure(vha, status,
					err_bits, ARRAY_SIZE(err_bits));
			if (err) {
				dev_err(vha->dev, "NNA hw failure: %llx\n", status);
				dev_err(vha->dev, "   CLK_STATUS0:%llx ",
					IOREAD64(vha->reg_base, VHA_CR_CLK_STATUS0));
				dev_err(vha->dev, " VHA_EVENT_STATUS:%llx ", status);
			}

			if (status & VHA_EVENT_TYPE(MMU_PAGE_FAULT))
				/* dump mmu status */
				vha_mmu_status(vha);
		}

		/* If no core level error process cnn events */
		if (!err && status & VHA_CNN_EVNTS)
			err = vha_handle_cnn_event(vha, status);
#ifdef HW_AX3
		else if (status == VHA_EVENT_TYPE(ERROR)) {
			/* Resubmit command next time if no CNN error detected
			 * and only ERROR bit is set.
			 * That means other OS caused the error */
			vha_rollback_cnn_cmds(vha);
		}
#endif
		else if (err) { /* Core level error */
			if (vha_handle_cmd(vha, VHA_CNN_CMD, err) == false)
				err = -ENOENT;
		}

		c++;
	} while (c < count && !err);

	if (err) {
		vha->stats.total_failures += count;
		vha_dev_stop(vha, true);
		/* Check queues ... */
		vha_chk_cmd_queues(vha, true);
	} else {
		/* Run in BH context! */
		vha_chk_cmd_queues(vha, false);
	}
	vha->stats.cnn_kicks_completed += count;
	mutex_unlock(&vha->lock);

	return ret;
}

static void vha_try_stop(struct vha_dev *vha)
{
	if (!vha->do_calibration &&
			(vha->pendcmd[VHA_CNN_CMD].cmd == NULL &&
			vha->queuedcmd[VHA_CNN_CMD].cmd == NULL))
		vha_dev_stop(vha, false);
}

/*
 * A session represents a single device and a set of buffers
 * to be used for inferences.
 * If required, buffers will be allocated for hardware CRC and DEBUG.
 */
int vha_add_session(struct vha_session *session)
{
	struct vha_dev *vha = session->vha;
	int ret;
	struct mmu_config mmu_config;
	int ctx_id;

	img_pdump_printf("-- OPEN_BEGIN\n");
	img_pdump_printf("-- VHA driver session started\n");
	ret = mutex_lock_interruptible(&vha->lock);
	if (ret)
		return ret;

#ifdef CONFIG_VHA_DUMMY
	if (list_empty(&vha->sessions) && !vha->do_calibration)
		vha_dev_start(vha);
#endif

	idr_init(&session->onchip_maps);

	memset(&mmu_config, 0, sizeof(mmu_config));
	/* Create a memory context for this session */
	if (vha->mmu_mode == 0)
		/* if mmu_mode==0, then MMU is disabled,
		 * so bypass the mmu hw layer,
		 * but still need do the buffer
		 * allocation through img_mem api
		 */
		mmu_config.bypass_hw = true;

#ifdef VHA_SCF
	/* Do not calculate parity when core does not support it,
	 * or we forced the core to disable it */
	if (vha->core_props.supported.parity &&
			!vha->parity_disable) {
		mmu_config.use_pte_parity = true;
		dev_dbg(vha->dev,
					"%s: Enabling MMU parity protection!\n",
					__func__);
	}
#endif

	mmu_config.addr_width = vha->core_props.mmu_width;
	mmu_config.alloc_attr = IMG_MEM_ATTR_MMU | /* Indicate MMU allocation */
		IMG_MEM_ATTR_WRITECOMBINE;
	mmu_config.page_size = mmu_page_size_kb_lut[vha->mmu_page_size];
	img_pdump_printf("-- MMU context: using %zukB MMU pages, %lukB CPU pages\n",
			mmu_page_size_kb_lut[vha->mmu_page_size]/1024, PAGE_SIZE/1024);

	for (ctx_id = 0; ctx_id < ARRAY_SIZE(session->mmu_ctxs); ctx_id++) {
		ret = img_mmu_ctx_create(vha->dev, &mmu_config,
					session->mem_ctx, vha->int_heap_id,
					mmu_callback, session,
					&session->mmu_ctxs[ctx_id].ctx);
		if (ret < 0) {
			dev_err(vha->dev, "%s: failed to create sw mmu context%d!\n",
				__func__, ctx_id);
			goto out_unlock;
		}

		if (vha->mmu_mode) {
			uint8_t hw_ctxid = 0;
			/* Store mmu context id */
			session->mmu_ctxs[ctx_id].id = ret;

			ret = img_mmu_get_pc(session->mmu_ctxs[ctx_id].ctx,
					&session->mmu_ctxs[ctx_id].pc_baddr,
					&session->mmu_ctxs[ctx_id].pc_bufid);
			if (ret) {
				dev_err(vha->dev, "%s: failed to get PC for context%d!\n",
						__func__, ctx_id);
				ret = -EFAULT;
				goto out_free_mmu_ctx;
			}
			/* Assign mmu hardware context */
			hw_ctxid = VHA_MMU_GET_CTXID(session);
			hw_ctxid += (VHA_MMU_AUX_HW_CTX_SHIFT*ctx_id);
			vha->mmu_ctxs[hw_ctxid]++;
			session->mmu_ctxs[ctx_id].hw_id = hw_ctxid;
		}
	}

	if (vha->core_props.ocm_size_bytes && onchipmem_phys_start != ~0) {
		/* OCM data is considered as IO (or shared)*/
		ret = img_mmu_init_cache(session->mmu_ctxs[VHA_MMU_REQ_IO_CTXID].ctx,
				onchipmem_phys_start, vha->core_props.ocm_size_bytes);
		if (ret < 0) {
			dev_err(vha->dev, "%s: failed to create init cache!\n",
					__func__);
			goto out_free_mmu_ctx;
		}
	}

	/* enable CRC and DEBUG registers */
	ret = vha_dbg_enable_hwbufs(session);
	if (ret)
		goto out_free_mmu_ctx;

	img_pdump_printf("-- OPEN_END\n");

	list_add_tail(&session->list, &vha->sessions);
	{
		struct vha_session *aux_head = list_prev_entry(session, list);
		list_add(&session->sched_list, &aux_head->sched_list);
	}

	dev_dbg(vha->dev,
			"%s: %p ctxid:%d\n", __func__, session,
			session->mmu_ctxs[VHA_MMU_REQ_MODEL_CTXID].id);

	mutex_unlock(&vha->lock);
	return ret;

out_free_mmu_ctx:
	for (ctx_id = 0; ctx_id < ARRAY_SIZE(session->mmu_ctxs); ctx_id++)
		if (session->mmu_ctxs[ctx_id].ctx)
			img_mmu_ctx_destroy(session->mmu_ctxs[ctx_id].ctx);
out_unlock:
	mutex_unlock(&vha->lock);
	return ret;
}

static void vha_clean_onchip_maps(struct vha_session *session, struct vha_buffer *buf)
{
	struct vha_onchip_map *onchip_map = NULL, *tmp = NULL;

	WARN_ON(!buf);
	WARN_ON(!session);

	list_for_each_entry_safe(onchip_map, tmp, &buf->onchip_maps, list) {
		idr_remove(&session->onchip_maps, onchip_map->mapid);
		list_del(&onchip_map->list);
		kfree(onchip_map);
	}
}

#ifdef KERNEL_DMA_FENCE_SUPPORT
static void _vha_rm_buf_fence(struct vha_session *session, struct vha_buffer *buf)
{
	struct vha_buf_sync_info *sync_info = &buf->sync_info;
	img_mem_remove_fence(session->mem_ctx, buf->id);
	if (sync_info->in_fence) {
		if (!dma_fence_is_signaled(sync_info->in_fence))
			dma_fence_remove_callback(sync_info->in_fence, &sync_info->in_sync_cb);
		if (sync_info->in_sync_file) {
			fput(sync_info->in_sync_file);
			sync_info->in_sync_file = NULL;
		}
		sync_info->in_sync_fd = VHA_SYNC_NONE;
		dma_fence_put(sync_info->in_fence);
		sync_info->in_fence = NULL;
		memset(&sync_info->in_sync_cb, 0, sizeof(struct dma_fence_cb));
	}
}
#endif

void vha_rm_session(struct vha_session *session)
{
	struct vha_dev *vha = session->vha;
	struct vha_session *cur_session, *tmp_session;
	struct vha_cmd *cur_cmd, *tmp_cmd;
	struct vha_rsp *cur_rsp, *tmp_rsp;
	struct vha_buffer *cur_buf, *tmp_buf;
	bool reschedule = false;
	bool pend_removed = false;
	bool queued_removed = false;
	int ctx_id;

	mutex_lock(&vha->lock);

	img_pdump_printf("-- CLOSE_BEGIN\n");

	/* Check if pend/queued commands will be removed. */
	if (vha->pendcmd[VHA_CNN_CMD].cmd &&
			vha->pendcmd[VHA_CNN_CMD].cmd->session == session) {
		dev_warn(vha->dev,
				"Removing a session while cnn cmd is still pending\n");
		pend_removed = true;
#ifdef CONFIG_VHA_DUMMY_SIMULATE_HW_PROCESSING_TIME
		cancel_delayed_work(&vha->dummy_dwork);
#endif
	}
	if (vha->queuedcmd[VHA_CNN_CMD].cmd &&
			vha->queuedcmd[VHA_CNN_CMD].cmd->session == session) {
		dev_warn(vha->dev,
				"Removing a session while cnn cmd is still queued\n");
		queued_removed = true;
	}

	/* Update session scheduling. */
	if (vha->queuedcmd[VHA_CNN_CMD].cmd &&
			(pend_removed && !queued_removed)) {
		if (vha->queuedcmd[VHA_CNN_CMD].cmd->session !=
					list_entry(&vha->sched_sessions, struct vha_session, sched_list))
			while(list_first_entry(&vha->sched_sessions, struct vha_session,
											sched_list) != vha->queuedcmd[VHA_CNN_CMD].cmd->session)
				list_rotate_left(&vha->sched_sessions);
	}

	/* Remove pend/queued commands if needed. */
	if (pend_removed || queued_removed) {
		vha_rollback_cnn_cmds(vha);
		reschedule = true;
	}

	/* Remove session related commands. */
	list_for_each_entry_safe(cur_cmd, tmp_cmd, &session->cmds, list) {
		/* rsp didn't make it to rsps list, free it now */
		kfree(cur_cmd->rsp);

		list_del(&cur_cmd->list);
		kfree(cur_cmd);
	}

	/* Remove responses for session related commands. */
	list_for_each_entry_safe(cur_rsp, tmp_rsp, &session->rsps, list) {
		dev_warn(vha->dev,
				"Removing a session while the rsp is still pending\n");
		list_del(&cur_rsp->list);
		kfree(cur_rsp);
	}

	/* Disable CRC and DEBUG capture. */
	vha_dbg_disable_hwbufs(session);

	list_for_each_entry_safe(cur_buf, tmp_buf, &session->bufs, list) {
		dev_warn(vha->dev,
				"Removing a session while the buffer wasn't freed\n");
#ifdef KERNEL_DMA_FENCE_SUPPORT
		_vha_rm_buf_fence(session, cur_buf);
#endif
		vha_clean_onchip_maps(session, cur_buf);
		list_del(&cur_buf->list);
		kfree(cur_buf);
	}

	/* Remove link from VHA's list. */
	list_for_each_entry_safe(cur_session, tmp_session,
				&vha->sessions, list) {
		if (cur_session == session)
			list_del(&cur_session->list);
	}
	list_for_each_entry_safe(cur_session, tmp_session,
				&vha->sched_sessions, sched_list) {
		if (cur_session == session)
			list_del(&cur_session->sched_list);
	}

	/* Reset hardware if required. */
	if ((list_empty(&vha->sessions) && !vha->do_calibration)
			|| reschedule)
		vha_dev_stop(vha, reschedule);

	/* Delete session's MMU memory contexts. */
	for (ctx_id = 0; ctx_id < ARRAY_SIZE(session->mmu_ctxs); ctx_id++) {
		img_mmu_ctx_destroy(session->mmu_ctxs[ctx_id].ctx);

		if (vha->mmu_mode) {
			uint8_t hw_ctxid = session->mmu_ctxs[ctx_id].hw_id;
			WARN_ON(!vha->mmu_ctxs[hw_ctxid]);
			if (vha->mmu_ctxs[hw_ctxid])
				vha->mmu_ctxs[hw_ctxid]--;
		}
	}

	/* Update mem stats - max memory usage in this session. */
	vha->stats.mem_usage_last = img_mem_get_usage_max(session->mem_ctx);
	{
		uint32_t MB = vha->stats.mem_usage_last / (1024 * 1024);
		uint32_t bytes = vha->stats.mem_usage_last -
			(MB * (1024 * 1024));
		uint32_t kB = (bytes * 1000) / (1024 * 1024);

		dev_dbg(vha->dev,
			"%s: Total user memory used in session: %u.%u MB\n",
			__func__, MB, kB);
	}

	img_pdump_printf("-- VHA driver session complete\n");
	img_pdump_printf("-- CLOSE_END\n");
	vha->active_mmu_ctx = VHA_INVALID_ID;
	mutex_unlock(&vha->lock);

	/* Reschedule once the session is removed. */
	if (reschedule)
		vha_chk_cmd_queues(vha, true);
}

static int vha_get_core_props(struct vha_dev *vha, struct vha_sys_data *sys_data)
{
	struct vha_core_props *props = &vha->core_props;
	int ret = 0;
	uint64_t ip_config;

	memset(props, 0, sizeof(*props));

#ifdef CONFIG_VHA_DUMMY
	/* Note: dummy dev always reads zeroes from registers */
	props->product_id  = 0x8070605040302010ULL;
	props->core_id  = (long)HW_SERIES << (int)VHA_CR_CORE_ID_BRANCH_ID_SHIFT;
	props->core_id += 0x010203040506ULL;   // provide a dummy core id
	props->num_dummy_devs  = 1;
#else
	props->product_id  = IOREAD64(vha->reg_base, VHA_CR_PRODUCT_ID);
	props->core_id  = IOREAD64(vha->reg_base, VHA_CR_CORE_ID);
#endif
	/*
	 * New mmu version 3 and onwards operates on 40bit physical & virtual addresses
	 */
	props->mmu_width = 40;

	/* HW from 1.1 onwards */
	ip_config = IOREAD64(vha->reg_base, VHA_CR_CORE_IP_CONFIG);
#ifdef HW_AX3
	props->mmu_ver = VHA_CR_GETBITS(CORE_IP_CONFIG, MMU_VERSION, ip_config);
#endif
	/* Mirage uses MMU version 3 hardware */
	if (!props->mmu_ver)
		props->mmu_ver = 3;
			;
	if (VHA_CR_GETBITS(CORE_IP_CONFIG, CNN_SUPPORTED, ip_config))
		props->num_cnn_devs = 1;
	if (VHA_CR_GETBITS(CORE_IP_CONFIG, RTM_SUPPORTED, ip_config))
		props->supported.rtm = 1;
#ifdef HW_AX3
	if (VHA_CR_GETBITS(CORE_IP_CONFIG, PARITY_REGISTERS, ip_config))
		props->supported.parity = 1;

#if defined(CONFIG_VHA_DUMMY) && defined(VHA_SCF)
	/* Force parity for pdump generation */
	props->supported.parity = 1;
#endif
#endif

	if ((props->num_dummy_devs == 0 && props->num_cnn_devs == 0)
		|| VHA_CR_GETBITS(CORE_ID, BRANCH_ID, props->core_id) != HW_SERIES) {
		ret = -EINVAL;
		dev_err(vha->dev, "%s: Wrong core configuration detected. "
			"Expected BVNC %d.x.x.x, got %llu.x.x.x. "
			"Maybe kernel module was built with wrong params.\n",
			__func__, HW_SERIES,
			VHA_CR_GETBITS(CORE_ID, BRANCH_ID, props->core_id));
	}

	props->soc_axi  = IOREAD64(vha->reg_base, VHA_CR_SOC_AXI);

	dev_info(vha->dev, "%s: Product id: %#llx\n",
			__func__, props->product_id);
	dev_info(vha->dev, "%s: Core id: %#llx\n",
			__func__, props->core_id);
	dev_info(vha->dev, "%s: MMU version:%d (%dbit)\n",
			__func__, props->mmu_ver, props->mmu_width);
	dev_dbg(vha->dev, "%s: supported: %#x\n",
			__func__, props->features);
	dev_dbg(vha->dev, "%s: soc_axi: %#llx\n",
			__func__, props->soc_axi);
	{
		uint64_t tmp = IOREAD64(vha->reg_base,
				VHA_CR_CORE_IP_INTEGRATOR_ID);
		dev_dbg(vha->dev, "%s: ip integrator id: %#llx\n",
				__func__, tmp);
		tmp = IOREAD64(vha->reg_base, VHA_CR_CORE_IP_CHANGELIST);
		dev_dbg(vha->dev, "%s: ip change list: %llu\n", __func__, tmp);
	}

	if (sys_data && sys_data->ocm_size_kb) {
		vha->core_props.ocm_size_bytes = sys_data->ocm_size_kb * 1024;
		/* User may wanted to limit OCM ... */
		if (onchipmem_size) {
			if(onchipmem_size < vha->core_props.ocm_size_bytes) {
				dev_warn(vha->dev, "%s:Limiting onchip memory to %u bytes (available:%u)\n",
						__func__, onchipmem_size, vha->core_props.ocm_size_bytes);
				vha->core_props.ocm_size_bytes = onchipmem_size;
			} else {
				dev_err(vha->dev, "%s: User defined onchip memory size exceeded (%u > %u))\n",
						__func__, onchipmem_size, vha->core_props.ocm_size_bytes);
			}
		}
	} else {
		vha->core_props.ocm_size_bytes = onchipmem_size;
	}

	dev_info(vha->dev, "%s: Total onchip memory: %u [kB]\n",
			__func__, vha->core_props.ocm_size_bytes / 1024);

	dev_info(vha->dev, "%s: Devices: DUMMY:%u CNN:%u\n",
			__func__, props->num_dummy_devs, props->num_cnn_devs);

	return ret;
}

static int vha_alloc_common(struct vha_dev *vha)
{
#if 0
	/* Allocate so-called fault access page to be accessed
	 * in case of invalid MMU entry */
	img_pdump_printf("-- INIT_BEGIN\n");
	if (vha->mmu_mode) {
		uint64_t addr;
		int ret = img_mem_alloc(vha->dev, drv.mem_ctx,
			default_mem_heap, 4096, IMG_MEM_ATTR_WRITECOMBINE,
			&vha->fp_bufid);
		if (ret) {
			dev_err(vha->dev, "%s: failed to allocate fault access page!\n",
					__func__);
			return ret;
		}

		dev_dbg(vha->dev, "%s: fault access page allocated id:%d!\n",
					__func__, vha->fp_bufid);
		addr = img_mem_get_single_page(drv.mem_ctx, vha->fp_bufid, 0);
		/* Get the address that dev expects */
		addr = img_mem_get_dev_addr(drv.mem_ctx, vha->fp_bufid, addr);

		IOWRITE64(vha->reg_base, VHA_CR_MMU_FAULT_ACCESS, addr);
		/* This is physical address so we need use MEM_OS0:BLOCK tag
		 * when pdump'ing. */
		img_pdump_printf("-- Setup fault access page register\n"
			"WRW64 :REG:%#x "_PMEM_":BLOCK_%d:0 -- 'FAP'\n",
			VHA_CR_MMU_FAULT_ACCESS, vha->fp_bufid);
	}
	img_pdump_printf("-- INIT_END\n");
#endif
	return 0;
}

static ssize_t
BVNC_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct vha_dev *vha = dev_get_drvdata(dev);
	struct vha_core_props *props = &vha->core_props;

	return snprintf(buf, 4*6, "%hu.%hu.%hu.%hu\n",
			(unsigned short)(props->core_id >> 48),
			(unsigned short)(props->core_id >> 32),
			(unsigned short)(props->core_id >> 16),
			(unsigned short)props->core_id);
}

static DEVICE_ATTR_RO(BVNC);

static struct attribute *vha_sysfs_entries[] = {
	&dev_attr_BVNC.attr,
	NULL,
};

static const struct attribute_group vha_attr_group = {
	.name = NULL,     /* put in device directory */
	.attrs  = vha_sysfs_entries,
};

static void vha_sched_apm(struct vha_dev *vha, uint32_t delay_ms)
{
	unsigned long work_at = jiffies + msecs_to_jiffies(delay_ms);
	int ret;

	dev_dbg(vha->dev, "%s: %d\n", __func__, pm_delay);
	/*
	 * Try to queue the work.
	 */
	ret = schedule_delayed_work(&vha->apm_dwork,
								work_at - jiffies);
	if (ret) {
		/* Work is already in the queue
		 * Canceling & rescheduling might be problematic,
		 * so just modify it
		 */
		ret = mod_delayed_work(system_wq, &vha->apm_dwork,
								work_at - jiffies);
		if (!ret) {
			dev_err(vha->dev, "%s: failed to modify work!\n",
								__func__);
			WARN_ON(1);
		}
	}
}

static void vha_apm_worker(struct work_struct *work)
{
	struct vha_dev *vha = container_of(work, struct vha_dev, apm_dwork.work);

	mutex_lock(&vha->lock);
	dev_dbg(vha->dev, "%s: apm expired\n", __func__);
	vha_try_stop(vha);
	mutex_unlock(&vha->lock);
}

#ifdef CONFIG_VHA_DUMMY_SIMULATE_HW_PROCESSING_TIME
/* Simulating hw execution time by scheduling this delayed work. */
static void vha_dummy_worker(struct work_struct *work)
{
	struct vha_dev *vha = container_of(work, struct vha_dev, dummy_dwork.work);

	mutex_lock(&vha->lock);

	if (vha->pendcmd[VHA_CNN_CMD].cmd) {
		/* Record hw processing end timestamps */
		vha->stats.hw_proc_end_prev = vha->stats.hw_proc_end;
		getnstimeofday(&vha->stats.hw_proc_end);
		/* Handle current pending command */
		vha_handle_cnn_event(vha, VHA_CNN_CMPLT_EVNT);
		/* Schedule following commands */
		vha_chk_cmd_queues(vha, true);
	}

	mutex_unlock(&vha->lock);
}
#endif

int vha_add_dev(struct device *dev,
		const struct heap_config heap_configs[], const int heaps,
		void *plat_data, struct vha_sys_data *sys_data,
		void __iomem *reg_base, uint32_t reg_size)
{
	struct vha_dev *vha;
	int ret;

#ifdef CONFIG_FAULT_INJECTION
	current->make_it_fail = fault_inject;
#endif

	vha = devm_kzalloc(dev, sizeof(struct vha_dev), GFP_KERNEL);
	if (!vha)
		return -ENOMEM;

	dev_dbg(dev, "%s: allocated vha_dev @ %p\n", __func__, vha);
	vha->dev          = dev;
	vha->reg_base     = reg_base;
	vha->reg_size     = reg_size;
	vha->plat_data    = plat_data;
	vha->fault_inject = fault_inject;
	vha->hw_bypass    = hw_bypass;
	vha->low_latency  = low_latency;
	vha->mmu_mode     = mmu_mode;
	vha->mmu_ctx_default = mmu_ctx_default;
	vha->mmu_page_size = mmu_page_size;
#ifdef VHA_SCF
	vha->parity_disable  = parity_disable;
#endif
	vha->active_mmu_ctx = VHA_INVALID_ID;

	/* Read HW properties */
	ret = vha_get_core_props(vha, sys_data);
	if (ret) {
		dev_err(dev, "%s: could not get vha properties at %p\n",
			__func__, (__force void *)vha->reg_base);
		goto out_free_dev;
	}

	ret = vha_init(vha, heap_configs, heaps);
	if (ret) {
		dev_err(dev, "%s: main component initialisation failed!",
			__func__);
		goto out_free_dev;
	}

	vha->int_heap_id = drv.internal_heap_id;

	mutex_init(&vha->lock);
	spin_lock_init(&vha->irq_lock);
	INIT_LIST_HEAD(&vha->sessions);
	INIT_LIST_HEAD(&vha->sched_sessions);

	/* Initialise command data pump worker */
	INIT_WORK(&vha->worker, cmd_worker);

#ifdef CONFIG_VHA_DUMMY_SIMULATE_HW_PROCESSING_TIME
	/* Initialise hw processing time simulation worker */
	INIT_DELAYED_WORK(&vha->dummy_dwork, vha_dummy_worker);
#endif

	dev_set_drvdata(dev, vha);

	ret = vha_api_add_dev(dev, vha, drv.num_devs);
	if (ret) {
		dev_err(dev, "%s: failed to add UM node!", __func__);
		goto out_add_dev;
	}

	vha_dbg_init(vha);
	vha_pdump_init(vha);

	ret = vha_alloc_common(vha);
	if (ret) {
		dev_err(dev, "%s: failed to allocate common dev buffers!",
				__func__);
		goto out_alloc_common;
	}

	/* Add device to driver context */
	list_add(&vha->list, &drv.devices);
	drv.num_devs++;

	if (sysfs_create_group(&dev->kobj, &vha_attr_group))
		dev_err(dev, "failed to create sysfs entries\n");

	vha->freq_khz = freq_khz;
#ifndef CONFIG_VHA_DUMMY
	if (vha->freq_khz < 0)
		vha->do_calibration = true; /* ??? OS0 ? */

	if (vha->freq_khz <= 0)
		vha->freq_khz = VHA_CORE_CLOCK_MHZ * 1000;

	if (vha->do_calibration)
		dev_info(dev, "%s: Core freq[kHz]: to be calibrated",
				__func__);
	else
		dev_info(dev, "%s: Core freq[kHz]: %u",
				__func__, vha->freq_khz);
#else
#  ifdef CONFIG_VHA_DUMMY_SIMULATE_HW_PROCESSING_TIME
	vha->freq_khz = VHA_CORE_CLOCK_MHZ * 1000;
	dev_info(dev, "%s: Core freq[kHz]: %u (faked for DUMMY device)",
			__func__, vha->freq_khz);
#  endif
#endif

	INIT_DELAYED_WORK(&vha->apm_dwork, vha_apm_worker);

	return ret;
out_alloc_common:
	vha_api_rm_dev(dev, vha);
out_add_dev:
	dev_set_drvdata(dev, NULL);
	vha_deinit();
out_free_dev:
	devm_kfree(dev, vha);
	return ret;
}

static void vha_free_common(struct vha_dev *vha)
{
	if (vha->fp_bufid) {
		img_mem_free(drv.mem_ctx, vha->fp_bufid);
		vha->fp_bufid = VHA_INVALID_ID;
	}
}

void vha_rm_dev(struct device *dev)
{
	struct vha_dev *vha = dev_get_drvdata(dev);
	int ret;

	if (!vha) {
		pr_err("%s: vha ptr is invalid!\n", __func__);
		return;
	}

	if (dev != vha->dev) {
		pr_err("%s: vha->dev is not properly initialised! (%p!=%p)\n", __func__, dev, vha->dev);
		return;
	}

	flush_scheduled_work();
	cancel_delayed_work_sync(&vha->apm_dwork);
#ifdef CONFIG_VHA_DUMMY_SIMULATE_HW_PROCESSING_TIME
	cancel_delayed_work_sync(&vha->dummy_dwork);
#endif
	vha_free_common(vha);

	ret = vha_api_rm_dev(dev, vha);
	if (ret)
		dev_err(dev, "%s: failed to remove UM node!\n", __func__);

	list_del(&vha->sessions);
	list_del(&vha->sched_sessions);
	list_del(&vha->list);
	BUG_ON(!drv.num_devs--);
	sysfs_remove_group(&dev->kobj, &vha_attr_group);

	vha_dbg_deinit(vha);

	dev_set_drvdata(dev, NULL);

	devm_kfree(dev, vha);
}

/* performs device self test operations */
void vha_dev_calibrate(struct device *dev, uint32_t cycles)
{
	struct vha_dev *vha = dev_get_drvdata(dev);
	if (!vha) {
		WARN_ON(1);
		return;
	}

	mutex_lock(&vha->lock);
	if (vha->do_calibration) {
		vha->calibration_cycles = cycles;
		dev_info(dev, "%s: Starting core frequency measurement (%d)...",
				__func__, cycles);
		vha_dev_start(vha);
#ifdef HW_AX2
		vha_cnn_gen_wdt(vha);
#endif
	}
	mutex_unlock(&vha->lock);
}

/* map buffer into the device */
int vha_map_to_onchip(struct vha_session *session,
		uint32_t buf_id, uint64_t virt_addr, uint32_t page_size,
		unsigned int num_pages, uint32_t page_idxs[], uint32_t *mapid)
{
	struct vha_dev *vha = session->vha;
	struct vha_onchip_map *onchip_map = NULL;
	struct vha_buffer *buf = NULL;
	int map_id = *mapid;
	int ret = 0;
	int i = 0;

	ret = mutex_lock_interruptible(&vha->lock);
	if (ret)
		return ret;

	buf = vha_find_bufid(session, buf_id);
	if (!buf) {
		pr_err("%s: buffer id %d not found\n", __func__, buf_id);
		ret = -EINVAL;
		goto out_unlock;
	}

	if (map_id == 0) {
		onchip_map = kzalloc(sizeof(struct vha_onchip_map), GFP_KERNEL);
		if (!onchip_map) {
			ret = -ENOMEM;
			goto out_unlock;
		}

		map_id = idr_alloc(&session->onchip_maps, onchip_map,
					MIN_ONCHIP_MAP, MAX_ONCHIP_MAP, GFP_KERNEL);
		if (map_id < 0) {
			pr_err("%s: idr_alloc failed\n", __func__);
			ret = map_id;
			goto alloc_id_failed;
		}

		ret = img_mmu_map(session->mmu_ctxs[VHA_MMU_REQ_IO_CTXID].ctx,
				session->mem_ctx, buf_id,
				virt_addr, IMG_MMU_PTE_FLAG_NONE);
		if (ret) {
			dev_err(vha->dev, "%s: map failed!\n", __func__);
			ret = -EFAULT;
			goto mmu_map_failed;
		}

		onchip_map->devvirt = virt_addr;
		onchip_map->mapid = map_id;
		onchip_map->bufid = buf_id;
		list_add(&onchip_map->list, &buf->onchip_maps);

		*mapid = map_id;
	} else {
		onchip_map = idr_find(&session->onchip_maps, map_id);
		if (!onchip_map) {
			pr_err("%s: idr_find failed\n", __func__);
			ret = -EINVAL;
			goto out_unlock;
		}
	}

	for (i = 0; i < num_pages; i++) {
		ret = img_mmu_move_pg_to_cache(
				session->mmu_ctxs[VHA_MMU_REQ_IO_CTXID].ctx,
				session->mem_ctx, buf_id,
				onchip_map->devvirt, page_size, page_idxs[i]);
		if (ret) {
			dev_warn(vha->dev, "%s: moving a page to on chip ram failed!\n", __func__);
			goto out_unlock;
		}
	}

	dev_dbg(vha->dev, "%s: mapped buf %s (%u) to %#llx, num_pages: %d\n",
		__func__, buf->name, buf_id, virt_addr, num_pages);

	mutex_unlock(&vha->lock);
	return 0;

mmu_map_failed:
	idr_remove(&session->onchip_maps, map_id);
alloc_id_failed:
	kfree(onchip_map);
out_unlock:
	mutex_unlock(&vha->lock);
	return ret;
}

/* map buffer into the device */
int vha_map_buffer(struct vha_session *session,
		uint32_t buf_id, uint64_t virt_addr,
		uint32_t map_flags)
{
	struct vha_dev *vha = session->vha;
	uint32_t flags = IMG_MMU_PTE_FLAG_NONE;
	struct vha_buffer *buf = NULL;
	int ret;

	ret = mutex_lock_interruptible(&vha->lock);
	if (ret)
		return ret;

	if ((map_flags & (VHA_MAP_FLAG_READ_ONLY|VHA_MAP_FLAG_WRITE_ONLY)) ==
			(VHA_MAP_FLAG_READ_ONLY|VHA_MAP_FLAG_WRITE_ONLY)) {
		dev_err(vha->dev, "%s: invalid mapping flags combination: 0x%x\n",
			__func__, map_flags);
		ret = -EINVAL;
		goto out_unlock;
	}

	/* Convert permission flags to internal definitions */
	if (map_flags & VHA_MAP_FLAG_READ_ONLY)
		flags |= IMG_MMU_PTE_FLAG_READ_ONLY;

	/* Note: VHA_MAP_FLAG_WRITE_ONLY is not supported by the mmuv3 hw */

	/* Direct 1:1 mappings */
	if (vha->mmu_mode == 1) {
		uint64_t *phys = img_mem_get_page_array(session->mem_ctx,
						buf_id);
		WARN_ON(!phys);
		/* Override virtual address,
		 * only applicable for physically contiguous memory regions */
		if (phys && phys[0]) {
			virt_addr = phys[0];
			dev_dbg(vha->dev,
					"%s: using direct mapping!\n",
					__func__);
		} else {
			dev_err(vha->dev,
					"%s: not contiguous memory!\n",
					__func__);
		}
	}

	buf = vha_find_bufid(session, buf_id);

	/* force MMU fault after N buffer map operations */
	if (test_mmu_no_map_count != 0) {
		int ctx_id;
		if (map_flags & VHA_MAP_FLAG_MODEL) {
			ctx_id = VHA_MMU_REQ_MODEL_CTXID;
			buf->req_type = VHA_REQ_MODEL;
		} else if (map_flags & VHA_MAP_FLAG_IO) {
			ctx_id = VHA_MMU_REQ_IO_CTXID;
			buf->req_type = VHA_REQ_IO;
		} else {
			WARN_ONCE(1, "No requestor flags!");
			ctx_id = VHA_MMU_REQ_IO_CTXID;
			buf->req_type = VHA_REQ_IO;
		}
		ret = img_mmu_map(session->mmu_ctxs[ctx_id].ctx,
				session->mem_ctx, buf_id, virt_addr, flags);
		if (ret || buf == NULL) {
			dev_err(vha->dev, "%s: map failed!\n", __func__);
			goto out_unlock;
		}
		if (test_mmu_no_map_count >= 0)
			--test_mmu_no_map_count;
	} else
		dev_info(vha->dev, "Bringup test: MMU no map count = %d\n",
			test_mmu_no_map_count);

	buf->devvirt = virt_addr;
	dev_dbg(vha->dev, "%s: mapped buf %s (%u) to %#llx, flags: 0x%x\n",
		__func__, buf->name, buf_id, virt_addr, map_flags);

out_unlock:
	mutex_unlock(&vha->lock);
	return ret;
}

/* unmap buffer from the device */
int vha_unmap_buffer(struct vha_session *session,
		uint32_t buf_id)
{
	struct vha_dev *vha = session->vha;
	struct vha_buffer *buf = NULL;
	int ret;
	int ctx_id;

	ret = mutex_lock_interruptible(&vha->lock);
	if (ret)
		return ret;

	buf = vha_find_bufid(session, buf_id);

	if (buf->req_type == VHA_REQ_MODEL)
		ctx_id = VHA_MMU_REQ_MODEL_CTXID;
	else
		ctx_id = VHA_MMU_REQ_IO_CTXID;

	ret = img_mmu_unmap(session->mmu_ctxs[ctx_id].ctx,
				session->mem_ctx, buf_id);
	if (ret || buf == NULL) {
		dev_err(vha->dev, "%s: unmap failed!\n", __func__);
		goto out_unlock;
	}

	buf->devvirt = 0ULL;

	vha_clean_onchip_maps(session, buf);

	dev_dbg(vha->dev, "%s: unmapped buf %s(%u)\n",
		__func__, buf->name, buf_id);

out_unlock:
	mutex_unlock(&vha->lock);
	return ret;
}

/*
 * return either dev virtual address or physical address of buffer
 * phys address only applicable if contiguous memory
 * virtual address only if MMU enabled
 */
uint64_t vha_buf_addr(struct vha_session *session, struct vha_buffer *buf)
{
	struct vha_dev *vha = session->vha;

	if (vha->mmu_mode == 0) {
		uint64_t *phys;

		/* no-MMU mode */
		if (vha->reg_base == NULL)
			return 0; /* no-MMU: dummy hardware */

		phys = img_mem_get_page_array(session->mem_ctx, buf->id);
		if (phys)
			/*
			 * no-MMU: carveout memory
			 * Get the address that dev expects.
			 */
			return img_mem_get_dev_addr(session->mem_ctx,
						buf->id, phys[0]);

		dev_err(vha->dev, "%s: ERROR: buffer %x is not contiguous\n",
			__func__, buf->id);
		return 0; /* no-MMU: system memory */
	}

	/* mmu mode */
	if (buf == NULL)
		return 0;  /* error */

	return buf->devvirt; /* MMU mode: virt address */
}

struct vha_buffer *vha_find_bufid(const struct vha_session *session, uint32_t buf_id)
{
	struct vha_buffer *buf;

	list_for_each_entry(buf, &session->bufs, list) {
		if (buf_id == buf->id)
			return buf;
	}
	return NULL;
}

struct vha_buffer *vha_find_bufvaddr(const struct vha_session *session,
		uint64_t virt_addr)
{
	struct vha_buffer *buf;

	list_for_each_entry(buf, &session->bufs, list) {
		/* check if virtual address belongs to specific buffer */
		if (virt_addr >= buf->devvirt &&
				virt_addr < (buf->devvirt + buf->size))
			return buf;
	}
	return NULL;
}

/* when a buffer is allocated or imported, it is added to session.bufs */
int vha_add_buf(struct vha_session *session,
		uint32_t buf_id, size_t size, const char *name, enum img_mem_attr attr)
{
	struct vha_buffer *buf = kzalloc(sizeof(*buf), GFP_KERNEL);
	struct vha_dev *vha = session->vha;
	int ret = 0;

	dev_dbg(vha->dev, "%s buf '%.*s' id:%d\n", __func__,
		(int)(sizeof(buf->name))-1, name, buf_id);

	if (buf == NULL)
		return -ENOMEM;

	buf->id  = buf_id;
	buf->size   = size;
	strncpy(buf->name, name, sizeof(buf->name)-1);
	buf->attr = attr;
	buf->status = VHA_BUF_UNFILLED;
	buf->session = session;
#ifdef KERNEL_DMA_FENCE_SUPPORT
	buf->sync_info.in_sync_fd = VHA_SYNC_NONE;
#endif
	list_add(&buf->list, &session->bufs);
	INIT_LIST_HEAD(&buf->onchip_maps);
	img_pdump_printf("-- <-- New buffer name: %s\n", buf->name);

	if (zero_buffers && !(buf->attr & IMG_MEM_ATTR_NOMAP)) {
		ret = img_mem_map_km(session->mem_ctx, buf_id);
		if (ret) {
			dev_err(session->vha->dev, "failed to map buff %x to km: %d\n",
				buf_id, ret);
			ret = -EFAULT;
			goto out_err;
		}
		buf->kptr = img_mem_get_kptr(session->mem_ctx, buf_id);

		{
			void *ptr = buf->kptr;
			int max_chunk = 1 * 1024 * 1024;
			while (size) {
				int chunk_size = size > max_chunk ?
						max_chunk : size;
				pr_debug("memset buf chunk %d!\n", chunk_size);
				memset(ptr, 0, chunk_size);
				ptr += chunk_size;
				size -= chunk_size;
				schedule();
			}
		}
		ret = img_mem_unmap_km(session->mem_ctx, buf->id);
		if (ret) {
			dev_err(session->vha->dev,
				"%s: failed to unmap buff %x from km: %d\n",
				__func__, buf->id, ret);
			ret = -EFAULT;
			goto out_err;
		}
		buf->kptr = NULL;
	}

	return 0;

out_err:
	list_del(&buf->list);
	kfree(buf);
	return ret;
}

/* remove buffer from the session */
int vha_rm_buf(struct vha_session *session, uint32_t buf_id)
{
	struct vha_buffer *buf = vha_find_bufid(session, buf_id);

	dev_dbg(session->vha->dev, "%s buf_id:%d\n", __func__, buf_id);
	if (buf == NULL) {
		dev_err(session->vha->dev, "%s: could not find buf %x\n",
			__func__, buf_id);
		return -EINVAL;
	}

#ifdef KERNEL_DMA_FENCE_SUPPORT
	_vha_rm_buf_fence(session, buf);
#endif
	vha_clean_onchip_maps(session, buf);

	list_del(&buf->list);
	kfree(buf);

	return 0;
}

/* check all input buffers are filled and ready to go */
static bool vha_is_waiting_on_input_buffs(struct vha_session *session,
		struct vha_cmd *cmd)
{
	if (!cmd->inbufs_ready) {
		int i;

		for (i = 0; i < cmd->user_cmd.num_inbufs; i++) {
			struct vha_buffer *buf = vha_find_bufid(session, vha_cmd_inbuf(cmd, i));

			if (buf && buf->status == VHA_BUF_UNFILLED) {
				dev_dbg(session->vha->dev,
					"%s: cmd %u waiting for input "
					"buf %d to be ready\n",
					__func__,
					cmd->user_cmd.cmd_id,
					buf->id);
				return true;
			}
		}
	}

	cmd->inbufs_ready = true;
	return false;
}


static bool vha_is_busy(struct vha_dev *vha)
{
#ifndef CONFIG_VHA_DUMMY
	if (!vha->is_ready)
		return true;
#endif

	if (vha->low_latency != VHA_LL_DISABLED) {
		return vha->pendcmd[VHA_CNN_CMD].cmd != NULL ||
				vha->queuedcmd[VHA_CNN_CMD].cmd != NULL;
	}
	return vha->pendcmd[VHA_CNN_CMD].cmd != NULL;
}

/* returns true if the cmd queue is full */
static bool vha_is_queue_full(struct vha_dev *vha, struct vha_cmd *cmd)
{
	if (vha->low_latency != VHA_LL_DISABLED) {
#ifdef HW_AX3
		if ((vha->low_latency == VHA_LL_SELF_KICK)
				/* if current command we are trying to queue belongs to a different session than pending one */
				&& (vha->pendcmd[VHA_CNN_CMD].cmd != NULL && cmd != NULL &&
						vha->pendcmd[VHA_CNN_CMD].cmd->session != cmd->session)
				/* if session of the command we are trying to queue, shares the hw mmu ctx with the session of pending cmd */
				&& (cmd->session->mmu_ctxs[VHA_MMU_REQ_MODEL_CTXID].hw_id ==
						vha->pendcmd[VHA_CNN_CMD].cmd->session->mmu_ctxs[VHA_MMU_REQ_MODEL_CTXID].hw_id)
				/* Sanity if hw mmu ctx is really shared at this point */
				&& (vha->mmu_ctxs[cmd->session->mmu_ctxs[VHA_MMU_REQ_MODEL_CTXID].hw_id] > 1)
				) {
#else
		if (vha->low_latency == VHA_LL_SELF_KICK) {
			dev_warn(vha->dev, "%s: LL=2 not supported!\n", __func__);
#endif
			/* skip low latency mode */
			return vha->pendcmd[VHA_CNN_CMD].cmd != NULL;
		}

		return vha->pendcmd[VHA_CNN_CMD].cmd != NULL &&
					vha->queuedcmd[VHA_CNN_CMD].cmd != NULL;
	}
	return vha->pendcmd[VHA_CNN_CMD].cmd != NULL;
}

/* process the cmd if everything is ready */
static enum do_cmd_status vha_do_cmd(struct vha_cmd *cmd)
{
	struct vha_session *session = cmd->session;
	enum do_cmd_status cmd_status = CMD_OK;
	/* already submitted, wait until processed */
	if (cmd->in_hw)
		return CMD_IN_HW;

	/* check all input buffers are filled and ready to go */
	if (vha_is_waiting_on_input_buffs(session, cmd))
		return CMD_WAIT_INBUFS;

#ifndef CONFIG_VHA_DUMMY
	if (!session->vha->is_ready)
		return CMD_HW_BUSY;
#endif

	/* check hw availability (if needed) */
	if (vha_is_queue_full(session->vha, cmd))
		return CMD_HW_BUSY;

	if (cmd->user_cmd.cmd_type == VHA_CMD_CNN_SUBMIT &&
			!session->vha->stats.cnn_kicks)
		img_pdump_printf("-- ALLOC_END\n");

	/* at this point we should be able to process the cmd */
	cmd_status = vha_do_cnn_cmd(cmd);

	return cmd_status;
}

/* check if there is any work to be done */
static void cmd_worker(struct work_struct *work)
{
	struct vha_dev *vha = container_of(work, struct vha_dev, worker);
	struct vha_cmd *cmd, *tmp;
	struct vha_session *session, *wait_session = NULL;
	bool queued, in_hw;
	bool retry = false;
	bool retrying = false;
	enum do_cmd_status cmd_status = CMD_OK;

	dev_dbg(vha->dev, "%s\n", __func__);
	mutex_lock(&vha->lock);

	if (vha->do_calibration) {
		/* Postpone any worker tasks */
		dev_dbg(vha->dev, "%s Postpone worker task!\n", __func__);
		goto exit;
	}

	if (vha_is_queue_full(vha, NULL)) {
		/* Postpone worker task if command queue is full */
		dev_dbg(vha->dev, "%s Queue full. Postpone worker task!\n", __func__);
		goto exit;
	}

	do {
		list_for_each_entry(session, &vha->sched_sessions, sched_list) {
			list_for_each_entry_safe(cmd, tmp, &session->cmds, list) {
				/* Reset previous state. */
				queued = false;
				in_hw = false;
				/* For hw commands... */
				if (CMD_EXEC_ON_HW(cmd)) {
					if (!VHA_IS_DUMMY(vha)) {
						/* Start device. */
						vha_dev_start(vha);
					}
					/* Store previous state. */
					queued = cmd->queued;
					in_hw = cmd->in_hw;
				}
				/* Attempt to schedule command for execution. */
				cmd_status = vha_do_cmd(cmd);
				if (cmd_status == CMD_NOTIFIED) {
					continue;
				}
				/* For hw commands... */
				if (CMD_EXEC_ON_HW(cmd)) {
					/* For low latency processing... */
					if (vha->low_latency != VHA_LL_DISABLED) {
						if (cmd->in_hw) {
							if (!retrying) {
								/* Set for retrying in case nothing will be queued
								 * in this round */
								retry = true;
							} else {
								/* Retry only once. */
								retry = false;
								/* It's a retry round, so nothing was queued in the previous
								 * one. Check the command following the one in the hardware
								 * for this session then. */
								continue;
							}
							/* If command is already in hw, go to next session. */
							break;
						}
						if (!cmd->inbufs_ready) {
							/* If command is waiting for input buffers, set this session
							 * as a starting point for next scheduling round. */
							if (wait_session == NULL)
								wait_session = session;
							/* Go to the next session. */
							break;
						}
						if (cmd->queued != queued) {
							/* If command has just been queued, set following session
							 * as a starting point for the next scheduling round. */
							if (wait_session == NULL) {
								wait_session = list_next_entry(session, sched_list);
								if (&wait_session->sched_list == &vha->sched_sessions)
									wait_session = list_first_entry(&vha->sched_sessions,
																									struct vha_session,
																									sched_list);
							}
							/* Quit this scheduling round as there's no room for more
							 * commands to be scheduled. */
							goto skip_cmds;
						}
						if (cmd->queued == queued && cmd->in_hw == in_hw) {
							/* If command has neither been scheduled for execution nor queued,
							 * quit this scheduling round as there's no room for
							 * commands to be scheduled. */
							goto skip_cmds;
						}
					} else {
						/* For non low latency processing... */
						if (cmd->in_hw) {
							/* If command is already in hw, set following session
							 * as a starting point for the next scheduling round. */
							if (wait_session == NULL) {
								wait_session = list_next_entry(session, sched_list);
								if (&wait_session->sched_list == &vha->sched_sessions)
									wait_session = list_first_entry(&vha->sched_sessions,
																									struct vha_session,
																									sched_list);
							}
							/* Quit this scheduling round as there's no room for more
							 * commands to be scheduled. */
							goto skip_cmds;
						}
						if (!cmd->inbufs_ready) {
							/* If command is waiting for input buffers, set this session
							 * as a starting point for next scheduling round. */
							if (wait_session == NULL)
								wait_session = session;
							/* Go to the next session. */
							break;
						}
						if (cmd->in_hw == in_hw) {
							/* If command has not been scheduled for execution,
							 * quit this scheduling round as there's no room for
							 * commands to be scheduled. */
							goto skip_cmds;
						}
					}
				}
			}
		}
		retrying = true;
	} while (retry);

	if (!VHA_IS_DUMMY(vha)) {
		/* Schedule APM if needed */
		if (!vha_is_busy(vha) &&
				!no_clock_disable) {
			if (!pm_delay)
				vha_dev_stop(vha, false);
			else
				vha_sched_apm(vha, pm_delay);
		}
	}
skip_cmds:

	/* Set a starting point session for next scheduling round. */
	if (wait_session != NULL)
		session = wait_session;
	if (session != list_entry(&vha->sched_sessions, struct vha_session,
														sched_list))
		while(list_first_entry(&vha->sched_sessions, struct vha_session,
													sched_list) != session)
			list_rotate_left(&vha->sched_sessions);
exit:
	mutex_unlock(&vha->lock);
}

/* this is wrapper func for scheduling command worker task */
void vha_chk_cmd_queues(struct vha_dev *vha, bool threaded)
{
	dev_dbg(vha->dev, "%s threaded:%u\n", __func__, threaded);
	if (threaded) {
		/* If work has been already scheduled from other context,
		 * the below call does nothing (returns false).
		 * However the worker is only used as command data pump,
		 * so it is not necessary to do any kind of rescheduling,
		 * as it will be executed anyway!
		 */
		schedule_work(&vha->worker);  /* call asynchronously */
	} else {
		/* Direct calls must be always invoked
		 * with vha_dev.lock == locked
		 */
		BUG_ON(!mutex_is_locked(&vha->lock));
		mutex_unlock(&vha->lock);
		cmd_worker(&vha->worker);  /* call synchronously */
		mutex_lock(&vha->lock);
	}
}

#ifdef KERNEL_DMA_FENCE_SUPPORT
/* input buffer sync callback */
static void _vha_in_buf_sync_cb(struct dma_fence *fence,
		struct dma_fence_cb *cb)
{
	struct vha_buffer *buf = container_of(cb, struct vha_buffer, sync_info.in_sync_cb);

	vha_set_buf_status(buf->session, buf->id, VHA_BUF_FILLED_BY_SW, VHA_SYNC_NONE);
	fput(buf->sync_info.in_sync_file);
	dma_fence_put(fence);
	memset(&buf->sync_info, 0, sizeof(struct vha_buf_sync_info));
	buf->sync_info.in_sync_fd = VHA_SYNC_NONE;
}
#endif

/* set buffer status per user request: either filled or unfilled */
int vha_set_buf_status(struct vha_session *session,
		uint32_t buf_id, enum vha_buf_status status, int in_sync_fd)
{
	struct vha_buffer *buf = vha_find_bufid(session, buf_id);

	if (buf == NULL) {
		dev_err(session->vha->dev, "%s: invalid buf id:%d\n",
			__func__, buf_id);
		return -EINVAL;
	}

	dev_dbg(session->vha->dev, "%s: id:%d curr:%d new:%d\n",
			__func__, buf->id, buf->status, status);
	/* If buffer has been filled by HW,
	 * mark that it probably needs invalidation, not necessarily,
	 * as it can be the input for the next hw segment,
	 * and may not be mapped by the UM */
	if (buf->status == VHA_BUF_UNFILLED &&
			status == VHA_BUF_FILLED_BY_HW) {
		buf->inval = true;
#ifdef KERNEL_DMA_FENCE_SUPPORT
		buf->status = status;
#endif
	}

	/* If buffer has been filled by SW,
	 * mark that it needs flushing */
	if (buf->status == VHA_BUF_UNFILLED &&
			status == VHA_BUF_FILLED_BY_SW) {
		buf->flush = true;
#ifdef KERNEL_DMA_FENCE_SUPPORT
		if (in_sync_fd > 0) {
			if (buf->sync_info.in_sync_fd < 0) {
				int ret = 0;
				struct file *sync_file;
				struct dma_fence *fence;

				sync_file = fget(in_sync_fd);
				if (sync_file == NULL) {
					dev_err(session->vha->dev, "%s: could not get file for fd=%d and buf %d\n",
						__func__, in_sync_fd, buf_id);
					return -EINVAL;
				}

				fence = sync_file_get_fence(in_sync_fd);
				if (!fence) {
					fput(sync_file);
					dev_err(session->vha->dev, "%s: could not get fence for fd=%d and buf %d\n",
						__func__, in_sync_fd, buf_id);
					return -EINVAL;
				}

				ret = dma_fence_add_callback(fence, &buf->sync_info.in_sync_cb,
																		_vha_in_buf_sync_cb);
				if (ret) {
					if (dma_fence_is_signaled(fence)) {
						dma_fence_put(fence);
						buf->status = status;
					} else
						dev_err(session->vha->dev, "%s: could not set cb for fd=%d and buf %x\n",
										__func__, in_sync_fd, buf_id);
					fput(sync_file);
					return ret;
				}
				buf->sync_info.in_fence = fence;
				buf->sync_info.in_sync_file = sync_file;
				buf->sync_info.in_sync_fd = in_sync_fd;
			} else if (in_sync_fd != buf->sync_info.in_sync_fd) {
				dev_err(session->vha->dev, "%s: buf %d has already assigned sync file fd=%d\n",
					__func__, buf_id, in_sync_fd);
				return -EINVAL;
			}
		}
		else {
			img_mem_signal_fence(session->mem_ctx, buf->id);
			buf->status = status;
		}
#endif
	}

#ifdef KERNEL_DMA_FENCE_SUPPORT
	if (status != VHA_BUF_FILLED_BY_SW)
#endif
		buf->status = status;

	/* Poke the command queue only when filled by SW */
	if (status == VHA_BUF_FILLED_BY_SW) {
		/* We are already locked!
		 * Run in separate thread
		 */
		vha_chk_cmd_queues(session->vha, true);
	}
	return 0;
}

bool vha_buf_needs_inval(struct vha_session *session, uint32_t buf_id)
{
	struct vha_buffer *buf = vha_find_bufid(session, buf_id);
	bool inval;

	if (buf == NULL) {
		dev_err(session->vha->dev, "%s: invalid buf id:%d\n",
			__func__, buf_id);
		return false;
	}

	/* Buffer that has been allocated as HW access only
	 * does not need invalidation */
	if (buf->attr & (IMG_MEM_ATTR_NOMAP|IMG_MEM_ATTR_NOSYNC)) {
		dev_dbg(session->vha->dev, "%s: id:%d (skip)\n",
				__func__, buf->id);
		return false;
	}

	dev_dbg(session->vha->dev, "%s: id:%d (%d)\n",
			__func__, buf->id, buf->inval);

	inval = buf->inval;
	buf->inval = false;

	return inval;
}

bool vha_buf_needs_flush(struct vha_session *session, uint32_t buf_id)
{
	struct vha_buffer *buf = vha_find_bufid(session, buf_id);
	bool flush;

	if (buf == NULL) {
		dev_err(session->vha->dev, "%s: invalid buf id:%d\n",
			__func__, buf_id);
		return false;
	}
	dev_dbg(session->vha->dev, "%s: id:%d (%d)\n",
			__func__, buf->id, buf->flush);

	flush = buf->flush;
	buf->flush = false;

	return flush;
}

#ifdef KERNEL_DMA_FENCE_SUPPORT
struct vha_sync_cb_data {
	struct dma_fence_cb cb;
	union {
		struct sync_file *sync_file;
		struct file *file;
	};
};

static void _vha_out_sync_cb(struct dma_fence *fence, struct dma_fence_cb *cb)
{
	struct vha_sync_cb_data *cb_data =
			container_of(cb, struct vha_sync_cb_data, cb);
	fput(cb_data->sync_file->file);
	dma_fence_put(fence);
	kfree(cb_data);
}

int vha_create_output_sync(struct vha_session *session, uint32_t buf_id_count,
		uint32_t *buf_ids)
{
	int i;
	int ret = -ENOMEM;
	int sync_fd = VHA_SYNC_NONE;
	struct device *dev = session->vha->dev;
	struct dma_fence_array *fence_array = NULL;
	struct vha_sync_cb_data *cb_data = NULL;
	struct dma_fence **fences =
			(struct dma_fence **)kmalloc_array(sizeof(struct buffer_fence*),
																				buf_id_count, GFP_KERNEL);
	if (fences == NULL) {
		dev_err(dev, "%s: failed allocating fence container for %u buffers\n",
			__func__, buf_id_count);
		return -ENOMEM;
	}

	cb_data = kzalloc(sizeof(struct vha_sync_cb_data), GFP_KERNEL);
	if (cb_data == NULL) {
		dev_err(dev, "%s: failed allocating fence callback for %u buffers\n",
			__func__, buf_id_count);
		kfree(fences);
		return -ENOMEM;
	}

	for (i = 0; i < buf_id_count; i++) {
		fences[i] = img_mem_add_fence(session->mem_ctx, buf_ids[i]);
		if (!fences[i]) {
			dev_err(dev, "%s: failed allocating fence for buffer id=%u\n",
				__func__, buf_ids[i]);
			goto err_fences;
		}
	}

	fence_array = dma_fence_array_create(buf_id_count, fences,
									dma_fence_context_alloc(1), 1, false);
	if (fence_array == NULL) {
		dev_err(dev, "%s: failed allocating fence array for %u buffers\n",
			__func__, buf_id_count);
		goto err_fences;
	}

	cb_data->sync_file = sync_file_create(&fence_array->base);
	if (cb_data->sync_file == NULL) {
		dev_err(dev, "%s: failed creating sync file for %u buffers\n",
					__func__, buf_id_count);
		goto error_sf;
	}

	sync_fd = get_unused_fd_flags(O_CLOEXEC);
	if (sync_fd < 0) {
		dev_err(dev, "%s: failed creating file descriptor for %u buffers\n",
					__func__, buf_id_count);
		ret = sync_fd;
		goto error_fd;
	}

	ret = dma_fence_add_callback(&fence_array->base, &cb_data->cb,
															_vha_out_sync_cb);
	if (ret < 0) {
		dev_err(dev, "%s: failed adding callback file descriptor for %u buffers\n",
					__func__, buf_id_count);
		goto error_fd;
	}

	fd_install(sync_fd, cb_data->sync_file->file);
	fget(sync_fd);

	return sync_fd;

error_fd:
	fput(cb_data->sync_file->file);
	dma_fence_put(&fence_array->base);
error_sf:
	dma_fence_put(&fence_array->base);
err_fences:
	i--;
	for (; i >= 0; i--) {
		img_mem_remove_fence(session->mem_ctx, buf_ids[i]);
	}
	kfree(fences);
	kfree(cb_data);
	return ret;
}

/* input sync callback */
static void _vha_in_sync_cb(struct dma_fence *fence, struct dma_fence_cb *cb)
{
	struct vha_sync_cb_data *cb_data =
			container_of(cb, struct vha_sync_cb_data, cb);
	fput(cb_data->file);
	dma_fence_put(fence);
	kfree(cb_data);
}
/* merged input sync callback */
static void _vha_in_merged_sync_cb(struct dma_fence *fence,
		struct dma_fence_cb *cb)
{
	struct vha_sync_cb_data *cb_data =
			container_of(cb, struct vha_sync_cb_data, cb);
	fput(cb_data->sync_file->file);
	dma_fence_put(fence);
}

int vha_merge_input_syncs(struct vha_session *session, uint32_t in_sync_fd_count,
		int *in_sync_fds)
{
	struct device *dev = session->vha->dev;
	int i, actual_count = 0;
	int ret = -ENOMEM;
	int sync_fd = VHA_SYNC_NONE;
	struct dma_fence_array *fence_array = NULL;
	struct vha_sync_cb_data *cb_data = NULL;
	struct vha_sync_cb_data *in_sync_cbs = NULL;
	struct dma_fence **fences;
	void *dma_fence_mem;
	struct file *f;

	/* Special cases. */
	if (in_sync_fd_count == 0) {
		dev_err(dev, "%s: requested 0 sync_fds to merge\n", __func__);
		return -EINVAL;
	} else if (in_sync_fd_count == 1) {
		struct file *f;
		struct dma_fence *fence;
		f = fget(in_sync_fds[0]);
		if (f == NULL) {
			dev_err(dev, "%s: could not get file for input sync fd=%d\n",
							__func__, in_sync_fds[0]);
			return -EINVAL;
		}
		fence = sync_file_get_fence(in_sync_fds[0]);
		if (!fence) {
			fput(f);
			dev_err(dev, "%s: could not get fence for input sync fd=%d\n",
							__func__, in_sync_fds[0]);
			return -EINVAL;
		}
		cb_data = kmalloc(sizeof(struct vha_sync_cb_data), GFP_KERNEL);
		if (cb_data == NULL) {
			fput(f);
			dma_fence_put(fence);
			dev_err(dev, "%s: failed allocating callback data for input sync fd=%d\n",
							__func__, in_sync_fds[0]);
			return -ENOMEM;
		}
		if (dma_fence_add_callback(fence, &cb_data->cb, _vha_in_sync_cb)) {
			if (dma_fence_is_signaled(fence)) {
				dev_warn(dev, "%s: input sync fd=%d already signalled\n",
								__func__, in_sync_fds[0]);
				ret = -EINVAL;
			} else {
				dev_err(dev, "%s: could not add fence callback for input sync fd=%d\n",
								__func__, in_sync_fds[0]);
				ret = -EFAULT;
			}
			fput(f);
			dma_fence_put(fence);
			kfree(cb_data);
			return ret;
		}
		cb_data->file = f;
		return in_sync_fds[0];
	}

	dma_fence_mem =
			kmalloc_array(
					(sizeof(struct dma_fence*) + sizeof(struct vha_sync_cb_data)),
					in_sync_fd_count + sizeof(struct vha_sync_cb_data), GFP_KERNEL);
	if (dma_fence_mem == NULL) {
		dev_err(dev, "%s: failed allocating fence container for %u buffers\n",
						__func__, in_sync_fd_count);
		return -ENOMEM;
	}
	fences = (struct dma_fence**)dma_fence_mem;
	in_sync_cbs = (struct vha_sync_cb_data *)(dma_fence_mem +
										sizeof(struct dma_fence*) * in_sync_fd_count);
	cb_data = (struct vha_sync_cb_data *)(dma_fence_mem +
								(sizeof(struct dma_fence*) + sizeof(struct vha_sync_cb_data)) *
										in_sync_fd_count);

	for (i = 0; i < in_sync_fd_count; i++) {
		struct dma_fence *fence;
		f = fget(in_sync_fds[i]);
		if (f == NULL) {
			dev_warn(dev, "%s: could not get file for fd=%d; will not use it\n",
							__func__, in_sync_fds[i]);
			continue;
		}
		fence = sync_file_get_fence(in_sync_fds[i]);
		if (!fence) {
			fput(f);
			dev_warn(dev, "%s: could not get fence for fd=%d; will not use it\n",
							__func__, in_sync_fds[i]);
			continue;
		}
		if (dma_fence_add_callback(fence, &in_sync_cbs[actual_count].cb,
															_vha_in_sync_cb)) {
			if (dma_fence_is_signaled(fence)) {
				dev_warn(dev, "%s: input sync fd=%d already signalled\n",
								__func__, in_sync_fds[i]);
			} else {
				dev_err(dev, "%s: could not add fence callback for input sync fd=%d;"
								" will not use it\n", __func__, in_sync_fds[i]);
			}
			fput(f);
			dma_fence_put(fence);
			continue;
		}
		dma_fence_get(fence); /* should be freed in dma_fence_array_release() */
		in_sync_cbs[actual_count].file = f;
		fences[actual_count] = fence;
		actual_count++;
	}
	if (actual_count == 0) {
		dev_err(dev, "%s: failed merging input fences\n", __func__);
		kfree(dma_fence_mem);
		return -EINVAL;
	}

	fence_array = dma_fence_array_create(actual_count, fences,
									dma_fence_context_alloc(1), 1, false);
	if (fence_array == NULL) {
		dev_err(dev, "%s: failed allocating fence array for %u buffers\n",
						__func__, in_sync_fd_count);
		kfree(dma_fence_mem);
		return -ENOMEM;
	}

	cb_data->sync_file = sync_file_create(&fence_array->base);
	if (cb_data->sync_file == NULL) {
		dev_err(dev, "%s: failed creating sync file for %u buffers\n",
						__func__, in_sync_fd_count);
		goto error_sf;
	}

	sync_fd = get_unused_fd_flags(O_CLOEXEC);
	if (sync_fd < 0) {
		dev_err(dev, "%s: failed creating file descriptor for %u buffers\n",
						__func__, in_sync_fd_count);
		ret = sync_fd;
		goto error_fd;
	}

	ret = dma_fence_add_callback(&fence_array->base, &cb_data->cb,
															_vha_in_merged_sync_cb);
	if (ret < 0) {
		dev_err(dev, "%s: failed adding callback file descriptor for %u buffers\n",
						__func__, in_sync_fd_count);
		goto error_fd;
	}

	fd_install(sync_fd, cb_data->sync_file->file);
	fget(sync_fd);

	return sync_fd;

error_fd:
	fput(cb_data->sync_file->file);
	dma_fence_put(&fence_array->base);
error_sf:
	for (i = 0; i < actual_count; i++) {
		fput(in_sync_cbs[actual_count].file);
		dma_fence_put(fences[actual_count]);
	}
	dma_fence_put(&fence_array->base);
	return ret;
}

int vha_release_syncs(struct vha_session *session, uint32_t buf_id_count,
		uint32_t *buf_ids)
{
	struct device *dev = session->vha->dev;
	int i;

	for (i = 0; i < buf_id_count; i++) {
		struct vha_buffer *buf = vha_find_bufid(session, buf_ids[i]);
		if (buf == NULL) {
			dev_warn(dev, "%s: could not find buf %u\n", __func__, buf_ids[i]);
		} else {
			_vha_rm_buf_fence(session, buf);
		}
	}

	return 0;
}
#endif

/* validate and queue a message from a user
 * called with mutex locked */
int vha_add_cmd(struct vha_session *session, struct vha_cmd *cmd)
{
	uint32_t i;
	struct device *dev = session->vha->dev;
	struct vha_user_cmd *user_cmd = &cmd->user_cmd;
	/* number of words in vha_user_cmd->data[0] */
	uint32_t num_params = (cmd->size - sizeof(struct vha_user_cmd))/sizeof(uint32_t);

	if (user_cmd->num_inbufs > user_cmd->num_bufs
		|| user_cmd->num_bufs > num_params * sizeof(uint32_t)) {
		dev_err(dev, "%s: invalid number of buffers in message: in:%x total:%x>%lx\n",
			__func__, user_cmd->num_inbufs, user_cmd->num_bufs,
			num_params * sizeof(uint32_t));
		return -EINVAL;
	}

	if (user_cmd->num_bufs > VHA_MAX_ALT_ADDRS) {
		dev_err(dev, "%s: invalid number of buffers in message: %x max:%x\n",
			__func__, user_cmd->num_bufs, VHA_MAX_ALT_ADDRS);
		return -EINVAL;
	}

	/* check input and output buffers are valid */
	for (i = 0; i < user_cmd->num_bufs; i++) {
		uint32_t buf_id = user_cmd->data[i];

		if (vha_find_bufid(session, buf_id) == NULL) {
			dev_err(dev, "%s: unrecognised buf id[%u]:%x\n",
				__func__, i, buf_id);
			return -EINVAL;
		}
	}

	switch(cmd->user_cmd.cmd_type) {
	case VHA_CMD_CNN_SUBMIT:
		/* send out a event notifications when submit is enqueued */
		if (vha_observers.enqueued)
			vha_observers.enqueued(session->vha->id,
						cmd->user_cmd.cmd_id);
		break;
	case VHA_CMD_CNN_PDUMP_MSG:
		if (!img_pdump_enabled()) {
			kfree(cmd);
			/* Silently ignore this pdump message */
			return 0;
		}
	}
	/* add the command to the pending list */
	list_add_tail(&cmd->list, &session->cmds);
	dev_dbg(session->vha->dev,
			"%s: %p session:%p\n", __func__, cmd, session);

	/* We are already locked!
	 * Run in separate thread
	 */
	vha_chk_cmd_queues(session->vha, true);

	return 0;
}


int vha_rm_cmds(struct vha_session *session, uint32_t cmd_id,
		uint32_t cmd_id_mask)
{
	struct vha_dev *vha = session->vha;
	struct vha_cmd *cur_cmd, *tmp_cmd;
	struct vha_rsp *cur_rsp, *tmp_rsp;
	bool reschedule = false;
	bool respond = false;
	bool pend_removed = false;
	bool queued_removed = false;

	mutex_lock(&vha->lock);

	/* Check if pend/queued commands will be removed. */
	if (vha->pendcmd[VHA_CNN_CMD].cmd &&
			(vha->pendcmd[VHA_CNN_CMD].cmd->session == session) &&
			(vha->pendcmd[VHA_CNN_CMD].cmd->user_cmd.cmd_id & cmd_id_mask)
																																	== cmd_id) {
		pend_removed = true;
#ifdef CONFIG_VHA_DUMMY_SIMULATE_HW_PROCESSING_TIME
		cancel_delayed_work(&vha->dummy_dwork);
#endif
	}
	if (vha->queuedcmd[VHA_CNN_CMD].cmd &&
			(vha->queuedcmd[VHA_CNN_CMD].cmd->session == session) &&
			(vha->queuedcmd[VHA_CNN_CMD].cmd->user_cmd.cmd_id & cmd_id_mask)
																																	== cmd_id) {
		queued_removed = true;
	}

	/* Update session scheduling. */
	if (vha->queuedcmd[VHA_CNN_CMD].cmd &&
			(pend_removed && !queued_removed)) {
		if (vha->queuedcmd[VHA_CNN_CMD].cmd->session !=
					list_entry(&vha->sched_sessions, struct vha_session, sched_list))
			while(list_first_entry(&vha->sched_sessions, struct vha_session,
											sched_list) != vha->queuedcmd[VHA_CNN_CMD].cmd->session)
				list_rotate_left(&vha->sched_sessions);
	}

	/* Remove pend/queued commands if needed. */
	if (pend_removed || queued_removed) {
		vha_rollback_cnn_cmds(vha);
		reschedule = true;
	}

	/* Remove session related commands matching command id template. */
	list_for_each_entry_safe(cur_cmd, tmp_cmd, &session->cmds, list) {
		if ((cur_cmd->user_cmd.cmd_id & cmd_id_mask) == cmd_id) {

#ifdef KERNEL_DMA_FENCE_SUPPORT
			{
				struct vha_user_cnn_submit_cmd *cnn_cmd =
						(struct vha_user_cnn_submit_cmd *)&cur_cmd->user_cmd;
				int j;
				for (j = 0; j < (cnn_cmd->msg.num_bufs - 1); j++) {
					struct vha_buffer *buf = vha_find_bufid(session, cnn_cmd->bufs[j]);
					if (buf == NULL) {
						dev_warn(vha->dev, "%s: could not find buf %x\n", __func__,
										cnn_cmd->bufs[j]);
					} else {
						_vha_rm_buf_fence(session, buf);
					}
				}
			}
#endif

			/* rsp didn't make it to rsps list; free it now. */
			kfree(cur_cmd->rsp);

			list_del(&cur_cmd->list);
			kfree(cur_cmd);

			/* There were commands matching command id template in the list,
			 * so respond to wake user space. */
			respond = true;
		}
	}

	/* Remove responses for session related commands
	 * matching command id template. */
	list_for_each_entry_safe(cur_rsp, tmp_rsp, &session->rsps, list) {
		if ((cur_rsp->user_rsp.cmd_id & cmd_id_mask) == cmd_id) {
			list_del(&cur_rsp->list);
			kfree(cur_rsp);
			respond = true;
		}
	}

	/* Reset hardware if required. */
	if (reschedule)
		vha_dev_stop(vha, reschedule);

	/* Generate "cancel" response if any commands matching command id template
	 * were removed. */
	if (respond) {
		/* Calculate space for the response. */
		size_t sz = sizeof(struct vha_rsp)
			+ sizeof(struct vha_user_cnn_submit_rsp)
			- sizeof(struct vha_user_rsp);
		/* Allocate space for standard response. */
		struct vha_rsp *rsp = kzalloc(sz, GFP_KERNEL);
		if (rsp == NULL) {
			dev_crit(session->vha->dev,
					"Failed to allocate memory to notify cancel for cmds %x\n", cmd_id);
			session->oom = true;
		} else {
			rsp->size = sizeof(struct vha_user_cnn_submit_rsp);
			rsp->user_rsp.cmd_id = cmd_id;
			list_add_tail(&rsp->list, &session->rsps);
		}
		wake_up(&session->wq);
	}

	mutex_unlock(&vha->lock);

	/* Just return in case of oom. */
	if (session->oom)
		return -ENOMEM;

	/* Reschedule once all commands matching command id template are removed. */
	if (reschedule)
		vha_chk_cmd_queues(vha, true);

	return 0;
}

int vha_suspend_dev(struct device *dev)
{
	struct vha_dev *vha = dev_get_drvdata(dev);
	bool processing = false;

	mutex_lock(&vha->lock);
	dev_dbg(dev, "%s: taking a nap!\n", __func__);

	processing = vha_rollback_cnn_cmds(vha);
	/* Forcing hardware disable */
	vha_dev_stop(vha, processing);

	mutex_unlock(&vha->lock);

	return 0;
}

int vha_resume_dev(struct device *dev)
{
	struct vha_dev *vha = dev_get_drvdata(dev);

	mutex_lock(&vha->lock);
	dev_dbg(dev, "%s: waking up!\n", __func__);
	/* Call the worker */
	vha_chk_cmd_queues(vha, true);

	mutex_unlock(&vha->lock);

	return 0;
}

/*
 * register event observers.
 * only a SINGLE observer for each type of event.
 * unregister by passing NULL parameter
*/
void vha_observe_event_enqueue(void (*func)(uint32_t devid, uint32_t cmdid))
{
	if (vha_observers.enqueued)
		pr_warn("%s: vha_observer for ENQUEUED events is already set to '%pf'\n",
			__func__, vha_observers.enqueued);
	vha_observers.enqueued = func;
}
EXPORT_SYMBOL(vha_observe_event_enqueue);

void vha_observe_event_submit(void (*func)(uint32_t devid, uint32_t cmdid))
{
	if (func && vha_observers.submitted)
		pr_warn("%s: vha_observer for SUBMITTED events is already set to '%pf'\n",
			__func__, vha_observers.submitted);
	vha_observers.submitted = func;
}
EXPORT_SYMBOL(vha_observe_event_submit);

void vha_observe_event_complete(void (*func)(uint32_t devid,
							uint32_t cmdid,
							int status,
							uint64_t cycles,
							uint64_t mem_usage))
{
	if (func && vha_observers.completed)
		pr_warn("%s: vha_observer for COMPLETED events is already set to '%pf'\n",
			__func__, vha_observers.completed);
	vha_observers.completed = func;
}
EXPORT_SYMBOL(vha_observe_event_complete);

void vha_observe_event_error(void (*func)(uint32_t devid, uint32_t cmdid, uint64_t status))
{
	if (func && vha_observers.error)
		pr_warn("%s: vha_observer for ERROR events is already set to '%pf'\n",
			__func__, vha_observers.error);
	vha_observers.error = func;
}
EXPORT_SYMBOL(vha_observe_event_error);
